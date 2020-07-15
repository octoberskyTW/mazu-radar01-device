/**
 *   @file  aoaprochwa_test_main.c
 *
 *   @brief
 *      Unit Test code for aoa processing.
 *
 *  \par
 *  NOTE:
 *      (C) Copyright 2018 Texas Instruments, Inc.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/* BIOS/XDC Include Files. */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Event.h>
#define DebugP_ASSERT_ENABLED 1
#include <ti/drivers/osal/DebugP.h>
#include <assert.h>
#include <ti/common/sys_common.h>
#include <ti/drivers/osal/SemaphoreP.h>
#include <ti/drivers/osal/MemoryP.h>
#include <ti/drivers/edma/edma.h>
#include <ti/drivers/esm/esm.h>
#include <ti/drivers/soc/soc.h>
#include <ti/utils/testlogger/logger.h>
#include <ti/utils/cycleprofiler/cycle_profiler.h> 
#include <ti/datapath/dpc/dpu/aoaproc/aoaprochwa.h>
#include <ti/utils/mathutils/mathutils.h>
#include <ti/utils/randomdatagenerator/gen_rand_data.h>



#define TEST_MAX_NUM_DOPPLER_BINS 512
#define TEST_MAX_NUM_RANGE_BIN  1024
#if (defined (SOC_XWR68XX))
#define TEST_MAX_RADAR_CUBE_SIZE  (48 * 1024 * 4)  //numchirps*numRange*numRx complex value
#endif

#if (defined (SOC_XWR18XX))
#define TEST_MAX_RADAR_CUBE_SIZE  (64 * 1024 * 4)  //numchirps*numRange*numRx complex value
#endif
#define TEST_AOA_FFTSIZE 64         /* 3D fft size */
#ifdef SUBSYS_MSS
#define TEST_MAX_NUM_CFARDETOBJ_DPU_LIST 276
#define TEST_MAX_NUM_CFARDETOBJ_DPU  276  //for Tx=2, >=256, for Tx=3, >=64
#define TEST_MAX_NUM_AOAPOINTCLOUD_LIST 276
#define TEST_MAX_NUM_PEAKS 2
#endif
#ifdef SUBSYS_DSS
#define  TEST_MAX_NUM_CFARDETOBJ_DPU_LIST   6    //must be even
#define TEST_MAX_NUM_CFARDETOBJ_DPU  276  
#define TEST_MAX_NUM_AOAPOINTCLOUD_LIST  5
#define TEST_MAX_NUM_PEAKS 1
#endif

#define TEST_MAX_NUM_CFARDETOBJ 5       //except for morepeak test, 3 tx 64, 2 tx 256
#define TEST_MAX_NUMVIRTUALANTE 12   /* maximum aoa number of receive antenna*/

#define DPC_OBJDET_RADAR_CUBE_DATABUF_BYTE_ALIGNMENT       (sizeof(int16_t))
#define MAX_PEAKIDX_ERROR 4
#define MAX_ELEVANGLE_ERROR 0.076f
#define MAX_LOCATION_ERROR 0.01f
#define MAX_HEATMAP_ERROR 2
#define TWOPEAK_POSITIVE_THRESHOLD 0.65f
#define TWOPEAK_NEGTIVE_THRESHOLD 0.95f
#define CUBADATA_PHASE_SHIFT 8.f
#define TEST_ANTENNA_LOOP 5   /* number of tx/rx combination */
#define TEST_DOPPLER_BIN_SIZE 9 // test doppler size covers from 2 to 512, tests for doppler bin = 1024 is added at the end */
#define TEST_RANGE_BIN_SIZE 7   //tested range bin size from 16 to 1024

#ifdef SUBSYS_MSS
#define TEST_AOA_DEBUG 0
#else
#define TEST_AOA_DEBUG 0 //for dsp, always disabled
#endif
#if TEST_AOA_DEBUG
uint32_t maxCubeSize = 0;
uint32_t testCaseId = 0;
#define TEST_AOA_DEBUG_RADARCUBADATA 0 //print out the radar cuba data
#define TEST_AOA_DEBUG_3DFFTIN 0
#define TEST_AOA_DEBUG_3DFFTOUT 0
#endif

#define PI 3.141592653589793

/* radar cube data */
#pragma DATA_SECTION(testRadarCube, ".l3ram");
#pragma DATA_ALIGN(testRadarCube,DPC_OBJDET_RADAR_CUBE_DATABUF_BYTE_ALIGNMENT);
cmplx16ImRe_t testRadarCube[TEST_MAX_RADAR_CUBE_SIZE];       //msb is real, lsb 16 is imag

#define MAX_NUM_TX_ANTENNAS 3
#define  SCRATCH_SIZE_BYTES (MAX_NUM_TX_ANTENNAS * DPU_AOAPROCHWA_NUM_ANGLE_BINS * sizeof(uint16_t))
#ifdef SUBSYS_MSS
#pragma DATA_SECTION(gScratchBuf, ".tcmb");
#endif
#ifdef SUBSYS_DSS
#pragma DATA_SECTION(gScratchBuf, ".l2data");
#endif
#pragma DATA_ALIGN(gScratchBuf, sizeof(uint32_t));
uint8_t gScratchBuf[2][SCRATCH_SIZE_BYTES];


/* cfar det obj */
#ifdef SUBSYS_MSS
#pragma DATA_SECTION(cfarDetObjList, ".tcmb");
#endif
#ifdef SUBSYS_DSS
#pragma DATA_SECTION(cfarDetObjList, ".l2data");
#endif
#pragma DATA_ALIGN(cfarDetObjList,DPU_AOAPROCHWA_CFAR_DET_LIST_BYTE_ALIGNMENT);
DPIF_CFARDetList cfarDetObjList[TEST_MAX_NUM_CFARDETOBJ_DPU_LIST];
DPIF_CFARDetList * pCfarDetObjList;

/* 2D FFT windowing coefficients */
#ifdef SUBSYS_MSS
#pragma DATA_SECTION(testDopplerWindow, ".tcmb");
int32_t testDopplerWindow[TEST_MAX_NUM_DOPPLER_BINS * 2];
#endif
#ifdef SUBSYS_DSS
#pragma DATA_SECTION(testDopplerWindow, ".l2data");
int32_t testDopplerWindow[TEST_MAX_NUM_DOPPLER_BINS];   //if -o3 is disabled, memory not fit
#endif
int32_t * pTestDopplerWindow; 



/* AOA DPU detected objects */
#ifdef SUBSYS_MSS
#pragma DATA_SECTION(aoaDetObj, ".tcmb");
#endif
#ifdef SUBSYS_DSS
#pragma DATA_SECTION(aoaDetObj, ".l2data");
#endif
#pragma DATA_ALIGN(aoaDetObj,DPU_AOAPROCHWA_POINT_CLOUD_CARTESIAN_BYTE_ALIGNMENT);
DPIF_PointCloudCartesian aoaDetObj[TEST_MAX_NUM_AOAPOINTCLOUD_LIST * TEST_MAX_NUM_PEAKS];
DPIF_PointCloudCartesian *pAoaDetObj;

 /* AOA DPU output side infor */
#ifdef SUBSYS_MSS
#pragma DATA_SECTION(aoaDetObjSideInfo, ".tcmb");
#endif
#ifdef SUBSYS_DSS
#pragma DATA_SECTION(aoaDetObjSideInfo, ".l2data");
#endif
#pragma DATA_ALIGN(aoaDetObjSideInfo, DPU_AOAPROCHWA_POINT_CLOUD_SIDE_INFO_BYTE_ALIGNMENT);
DPIF_PointCloudSideInfo aoaDetObjSideInfo[TEST_MAX_NUM_CFARDETOBJ_DPU * TEST_MAX_NUM_PEAKS];

/* AOA DPU heat map outout */
#ifdef SUBSYS_MSS
#pragma DATA_SECTION(staticHeatmap, ".tcmb");
#endif
#ifdef SUBSYS_DSS
#pragma DATA_SECTION(staticHeatmap, ".l2data");
#endif
#pragma DATA_ALIGN(staticHeatmap,DPU_AOAPROCHWA_AZIMUTH_STATIC_HEAT_MAP_BYTE_ALIGNMENT) ;  
cmplx16ImRe_t staticHeatmap[TEST_MAX_NUM_RANGE_BIN * 8]; //maximum azimvirtual antenna is 2*4

/* heat map references */
#ifdef SUBSYS_MSS
#pragma DATA_SECTION(staticHeatmapRef, ".tcmb");
#endif
#ifdef SUBSYS_DSS
#pragma DATA_SECTION(staticHeatmapRef, ".l2data");
#endif
cmplx16ImRe_t staticHeatmapRef[TEST_MAX_NUM_RANGE_BIN * 8]; //maximum azimvirtual antenna is 2*4

/* AOA DPU detected Azim peak index */
#ifdef SUBSYS_MSS
#pragma DATA_SECTION(aoaDetObjAzimIdx, ".tcmb");
#endif
#ifdef SUBSYS_DSS
#pragma DATA_SECTION(aoaDetObjAzimIdx, ".l2data");
#endif
uint8_t aoaDetObjAzimIdx[TEST_MAX_NUM_CFARDETOBJ_DPU *TEST_MAX_NUM_PEAKS];

/* AOA DPU detects Elev angle */
#ifdef SUBSYS_MSS
#pragma DATA_SECTION(aoaDetObjElevAngle, ".tcmb");
#endif
#ifdef SUBSYS_DSS
#pragma DATA_SECTION(aoaDetObjElevAngle, ".l2data");
#endif
#pragma DATA_ALIGN( aoaDetObjElevAngle, DPU_AOAPROCHWA_DET_OBJ_ELEVATION_ANGLE_BYTE_ALIGNMENT);
float aoaDetObjElevAngle[TEST_MAX_NUM_CFARDETOBJ_DPU *TEST_MAX_NUM_PEAKS];


/* EDMA resource partitioning */


#define EDMA_SHADOW_LNK_PARAM_BASE_ID                      EDMA_NUM_DMA_CHANNELS
#define DPU_AOA_PROC_EDMAIN_CH                             EDMA_TPCC0_REQ_FREE_4
#define DPU_AOA_PROC_EDMAIN_SHADOW                         (EDMA_SHADOW_LNK_PARAM_BASE_ID + 4U)
#define DPU_AOA_PROC_EDMAIN_EVENT_QUE                      0
#define DPU_AOA_PROC_EDMAIN_SIG_CH                         EDMA_TPCC0_REQ_FREE_8
#define DPU_AOA_PROC_EDMAIN_SIG_SHADOW                     (EDMA_SHADOW_LNK_PARAM_BASE_ID + 5U)
#define DPU_AOA_PROC_EDMAIN_SIG_EVENT_QUE                  0
#define DPU_AOA_PROC_EDMAOUT_CH                            EDMA_TPCC0_REQ_HWACC_2
#define DPU_AOA_PROC_EDMAOUT_SHADOW                        (EDMA_SHADOW_LNK_PARAM_BASE_ID + 6U)
#define DPU_AOA_PROC_EDMAOUT_EVENT_QUE                     0

/* EDMA general physical channels */
#define DPC_OBJDET_DPU_AOA_PROC_EDMAIN_PING_EVENT_QUE                 0
#define DPC_OBJDET_DPU_AOA_PROC_EDMAOUT_PING_EVENT_QUE                0
/* Event queues PONG path */
#define DPC_OBJDET_DPU_AOA_PROC_EDMAIN_PONG_EVENT_QUE                 0
#define DPC_OBJDET_DPU_AOA_PROC_EDMAOUT_PONG_EVENT_QUE                0

/* EDMA physical channels tied to HWA output events */
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_HWA_OUTPUT_CH_0                  EDMA_TPCC0_REQ_HWACC_4
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_HWA_OUTPUT_CH_1                  EDMA_TPCC0_REQ_HWACC_5

#define DPC_OBJDET_EDMA_SHADOW_BASE                                   EDMA_NUM_DMA_CHANNELS

#define DPC_OBJDET_DPU_AOA_PROC_EDMA_CH_0                             EDMA_TPCC0_REQ_DMMSW_INTR_18
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_CH_1                             EDMA_TPCC0_REQ_DMMSW_INTR_17
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_CH_2                             EDMA_TPCC0_REQ_DMMSW_INTR_16
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_CH_3                             EDMA_TPCC0_REQ_DMMSW_INTR_15

/* EDMA Param sets */
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_0                        (DPC_OBJDET_EDMA_SHADOW_BASE + 27)
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_1                        (DPC_OBJDET_EDMA_SHADOW_BASE + 28)
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_2                        (DPC_OBJDET_EDMA_SHADOW_BASE + 29)
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_3                        (DPC_OBJDET_EDMA_SHADOW_BASE + 30)
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_4                        (DPC_OBJDET_EDMA_SHADOW_BASE + 31)
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_5                        (DPC_OBJDET_EDMA_SHADOW_BASE + 32)
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_6                        (DPC_OBJDET_EDMA_SHADOW_BASE + 33)
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_7                        (DPC_OBJDET_EDMA_SHADOW_BASE + 34)
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_8                        (DPC_OBJDET_EDMA_SHADOW_BASE + 35)
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_9                        (DPC_OBJDET_EDMA_SHADOW_BASE + 36)
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_10                       (DPC_OBJDET_EDMA_SHADOW_BASE + 37)
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_11                       (DPC_OBJDET_EDMA_SHADOW_BASE + 38)



#if TEST_AOA_DEBUG    // DEBUG FOR MSS only
#pragma DATA_SECTION(fftDataInBuf, ".tcmb");
uint32_t fftDataInBuf[TEST_MAX_NUM_DOPPLER_BINS * 2];
#pragma DATA_SECTION(fftDataWindow, ".tcmb");
int32_t fftDataWindow[TEST_MAX_NUM_DOPPLER_BINS * 4];
#pragma DATA_SECTION(fftDataOutBuf, ".tcmb");
int32_t fftDataOutBuf[TEST_MAX_NUM_DOPPLER_BINS * 4];
#pragma DATA_SECTION(fft3dDataInBuf, ".tcmb");
int32_t fft3dDataInBuf[TEST_MAX_NUMVIRTUALANTE * 2];
#pragma DATA_SECTION(fft3dDataOutBuf, ".tcmb");
int32_t fft3dDataOutBuf[TEST_AOA_FFTSIZE * 4];   //first TEST_AOA_FFTSIZE azim fft out, next elev fft out 
#endif

/**
  * @brief
  * AOA DPU unit test test configuration structure.
  *
*/
typedef struct aoaProcDpuTestConfig_t {

    uint16_t numTxAntennas;     /*!< @brief number of Tx antenna */
    uint16_t numRxAntennas;     /*!< @brief number of Rx antenna */
    uint16_t numRangeBins;      /*!< @brief number of range bins */
    uint16_t numChirps;         /*!< @brief number of chirps, <= numDopplerBins */
    uint16_t numDopplerBins;    /*!< @brief number of doppler bins */
    uint16_t numCfarDetObj;     /*!< @brief number of cfar detected obj */
    uint16_t numAoaOutObj;      /*!< @brief number of AOA output reference */
    uint16_t cfarDetObjRangeIdx[TEST_MAX_NUM_CFARDETOBJ];         /*!< @brief range index for CFAR det objects */
    uint16_t cfarDetObjdopplerIdx[TEST_MAX_NUM_CFARDETOBJ];       /*!< @brief doppler index for CFAR det objects */
    int16_t  cfarDetObjDopplerRefIdx[TEST_MAX_NUM_CFARDETOBJ];    /*!< @brief signed doppler index for CFAR det objects */
    uint8_t  twoPeaksFlag;     /*!< @brief if 0, single peak angle for azim, if 1 2 peak angles for azim */
    uint8_t  heatMapFlag;      /*!< @brief turn on/off heat map checking in the tests, always ON for numRx > 1 */
    uint8_t  minmaxAngleFlag;  /*!< @brief if 0, min/max azim/elev angles are set to +/- 80 degree, if 1, they are set to 
                               min/max azim/elev based on the tests */
    int16_t minAzim;          /*!<  @brief minimun azim index in the test */ 
    int16_t maxAzim;          /*!<  @brief maximum azim index in the test */
    int16_t minElev, maxElev; /*!<  @brief minimum/maximum elev index in the test */

    uint8_t checkCfarDetObjFlag[TEST_MAX_NUM_CFARDETOBJ];   /*!<  @brief The cfar det object is detected or 
                                                            not detected in aoa dpu*/

    uint8_t  aoaNum3DfftPeaks[TEST_MAX_NUM_CFARDETOBJ];   /*!<  @brief number of azim peaks for every cfar det objects */

   /*!<  @brief azim peak index reference for every cfar det objects */
    int16_t  aoaSignedAzimPeakIdxRef[TEST_MAX_NUM_CFARDETOBJ * TEST_MAX_NUM_PEAKS];
    /*!<  @brief elev peak index reference for every cfar det objects */
    int16_t  aoaSignedElevPeakIdxRef[TEST_MAX_NUM_CFARDETOBJ * TEST_MAX_NUM_PEAKS];

    uint8_t winType;   /*!<  @brief if 0, rectange windowing, if 1, hanning windowing */
    uint8_t morePeaksFlag;  /*!<  @brief if 1, generates more than 64 peaks if tx=3, and more than 256 peaks if tx=2 
                                 if 0, maximum cfar det objects is defined as TEST_MAX_NUM_CFARDETOBJ*/
    uint8_t extVelocityFlag;  /*!<  @brief extension velocity flag, 0- extension velocity is disabled, 1 - enabled*/
    
} aoaProcDpuTestConfig_t;

SOC_Handle  socHandle;
EDMA_Handle edmaHandle;
HWA_Handle  hwaHandle;


MCPI_LOGBUF_INIT(128);

uint8_t finalResults;

DPU_AoAProcHWA_Config        aoaCfg;
DPU_AoAProcHWA_Handle        aoaProcHandle;
DPU_AoAProc_FovAoaCfg        aoaDynFovCfg;
DPU_AoAProc_compRxChannelBiasCfg aoaDynOutCompRxCfg;
DPU_AoAProc_MultiObjBeamFormingCfg aoaDynBmCfg;
DPU_AoAProcHWA_OutParams outAoaProc;
DPU_AoAProc_ExtendedMaxVelocityCfg  extMaxVelCfg;


aoaProcDpuTestConfig_t    aoaTestCfg;
uint32_t testCount;
 

/**
*  @b Description
*  @n
*  calculate modula value 
*
*  @retval None
*
*/
uint16_t test_modCalc(uint16_t value1, uint16_t value2)
{
    uint16_t result;
    result = value1 - value1 / value2 * value2;
    return result;
}

/**
*  @b Description
*  @n
*     Edma error call back function.
*
*  @retval None
*
*/
void MmwDemo_EDMA_errorCallbackFxn(EDMA_Handle handle, EDMA_errorInfo_t *errorInfo)
{
    DebugP_assert(0);
}

/**
*  @b Description
*  @n
*   Edma transfer control error call bac function.
*
*  @retval None
*
*/
void MmwDemo_EDMA_transferControllerErrorCallbackFxn(EDMA_Handle handle,
    EDMA_transferControllerErrorInfo_t *errorInfo)
{
    DebugP_assert(0);
}

/**
*  @b Description
*  @n
*    Initialize the HWA and EDMA.
*
*  @retval None
*
*/
void aoaProc_test_hwaEdmainit()
{
    uint8_t             edmaNumInstances;
    uint8_t             inst;
    EDMA_instanceInfo_t edmaInstanceInfo;
    EDMA_errorConfig_t  errorConfig;
    int32_t             errorCode;
    EDMA_errorInfo_t  EDMA_errorInfo;
    EDMA_transferControllerErrorInfo_t EDMA_transferControllerErrorInfo;


    /* Initialize the HWA */
    HWA_init();

    hwaHandle = HWA_open(0, socHandle, &errorCode);
    if (hwaHandle == NULL)
    {
      //  System_printf("HWA failed to open\n");
        DebugP_assert(0);
        return;
    }

    /* Initialize the EDMA */
    edmaNumInstances = EDMA_getNumInstances();
    for (inst = 0; inst < edmaNumInstances; inst++)
    {
        errorCode = EDMA_init(inst);
        if (errorCode != EDMA_NO_ERROR)
        {
       //     System_printf("Debug: EDMA instance %d initialization returned error %d\n", errorCode);
            DebugP_assert(0);
            return;
        }
    }
    memset(&EDMA_errorInfo, 0, sizeof(EDMA_errorInfo));
    memset(&EDMA_transferControllerErrorInfo, 0, sizeof(EDMA_transferControllerErrorInfo));

    edmaHandle = EDMA_open(0, &errorCode, &edmaInstanceInfo);
    if (edmaHandle == NULL)
    {
        System_printf("Error: Unable to open the EDMA Instance err:%d\n", errorCode);
        DebugP_assert(0);
        return;
    }

    errorConfig.isConfigAllEventQueues = true;
    errorConfig.isConfigAllTransferControllers = true;
    errorConfig.isEventQueueThresholdingEnabled = true;
    errorConfig.eventQueueThreshold = EDMA_EVENT_QUEUE_THRESHOLD_MAX;
    errorConfig.isEnableAllTransferControllerErrors = true;
    errorConfig.callbackFxn = MmwDemo_EDMA_errorCallbackFxn;
    errorConfig.transferControllerCallbackFxn = MmwDemo_EDMA_transferControllerErrorCallbackFxn;
    if ((errorCode = EDMA_configErrorMonitoring(edmaHandle, &errorConfig)) != EDMA_NO_ERROR)
    {
      //  System_printf("Error: EDMA_configErrorMonitoring() failed with errorCode = %d\n", errorCode);
        DebugP_assert(0);
        return;
    }

}

/**
*  @b Description
*  @n
*   Initialize the AOA DPU, Generates the AOA DPU handler.
*
*  @retval None
*
*/
void aoaProc_test_dpuInit()
{
    DPU_AoAProcHWA_InitParams   aoaInitParams;
    int32_t errorCode = 0;

    aoaInitParams.hwaHandle = hwaHandle;

    aoaProcHandle = DPU_AoAProcHWA_init(&aoaInitParams, &errorCode);
    if (aoaProcHandle == NULL)
    {
     //   System_printf("AOA DPU failed to initialize. Error %d.\n", errorCode);
        return;
    }
}

/**
*  @b Description
*  @n
*   Initialize the AOA DPU configuration structure for the parameters NOT change for every test.
*
*  @retval None
*
*/
void aoaProc_test_dpuConfig()
{
    DPU_AoAProcHWA_HW_Resources   * resPtr;
    DPU_AoAProcHWA_hwaAoAConfig  *aoaHwaCfgPtr;
    uint16_t ii;
    float realTemp, imagTemp;

    memset(&aoaCfg, 0, sizeof(aoaCfg));

    resPtr = &aoaCfg.res;

    resPtr->edmaHandle = edmaHandle;


    /* For Azimuth Heatmap ping/pong paths */
    resPtr->edmaHwa[0].in.channel = DPU_AOA_PROC_EDMAIN_CH;
    resPtr->edmaHwa[0].in.channelShadow = DPU_AOA_PROC_EDMAIN_SHADOW;
    resPtr->edmaHwa[0].in.eventQueue = DPU_AOA_PROC_EDMAIN_EVENT_QUE;
    resPtr->edmaHwa[0].inSignature.channel = DPU_AOA_PROC_EDMAIN_SIG_CH;
    resPtr->edmaHwa[0].inSignature.channelShadow = DPU_AOA_PROC_EDMAIN_SIG_SHADOW;
    resPtr->edmaHwa[0].inSignature.eventQueue = DPU_AOA_PROC_EDMAIN_SIG_EVENT_QUE;
    resPtr->edmaHwa[0].out.channel = DPU_AOA_PROC_EDMAOUT_CH;
    resPtr->edmaHwa[0].out.channelShadow = DPU_AOA_PROC_EDMAOUT_SHADOW;
    resPtr->edmaHwa[0].out.eventQueue = DPU_AOA_PROC_EDMAOUT_EVENT_QUE;

    resPtr->edmaHwa[1].in.channel = DPU_AOA_PROC_EDMAIN_CH + 1;
    resPtr->edmaHwa[1].in.channelShadow = DPU_AOA_PROC_EDMAIN_SHADOW + 3;
    resPtr->edmaHwa[1].in.eventQueue = DPU_AOA_PROC_EDMAIN_EVENT_QUE;
    resPtr->edmaHwa[1].inSignature.channel = DPU_AOA_PROC_EDMAIN_SIG_CH + 1;
    resPtr->edmaHwa[1].inSignature.channelShadow = DPU_AOA_PROC_EDMAIN_SIG_SHADOW + 3;
    resPtr->edmaHwa[1].inSignature.eventQueue = DPU_AOA_PROC_EDMAIN_SIG_EVENT_QUE;
    resPtr->edmaHwa[1].out.channel = DPU_AOA_PROC_EDMAOUT_CH + 1;
    resPtr->edmaHwa[1].out.channelShadow = DPU_AOA_PROC_EDMAOUT_SHADOW + 3;
    resPtr->edmaHwa[1].out.eventQueue = DPU_AOA_PROC_EDMAOUT_EVENT_QUE;

    /* For main data processing ping/pong paths */
    resPtr->edmaHwaExt[0].chIn.channel =               DPC_OBJDET_DPU_AOA_PROC_EDMA_CH_0;
    resPtr->edmaHwaExt[0].chIn.eventQueue =            DPC_OBJDET_DPU_AOA_PROC_EDMAIN_PING_EVENT_QUE;
    resPtr->edmaHwaExt[0].chOut.channel =              DPC_OBJDET_DPU_AOA_PROC_EDMA_HWA_OUTPUT_CH_0;
    resPtr->edmaHwaExt[0].chOut.eventQueue =           DPC_OBJDET_DPU_AOA_PROC_EDMAOUT_PING_EVENT_QUE;
    resPtr->edmaHwaExt[0].stage[0].paramIn =           DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_0;
    resPtr->edmaHwaExt[0].stage[0].paramInSignature =  DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_1;
    resPtr->edmaHwaExt[0].stage[0].paramOut =          DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_2;
    resPtr->edmaHwaExt[0].stage[1].paramIn =           DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_3;
    resPtr->edmaHwaExt[0].stage[1].paramInSignature =  DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_4;
    resPtr->edmaHwaExt[0].stage[1].paramOut =          DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_5;
    resPtr->edmaHwaExt[0].eventQueue = 0;

    resPtr->edmaHwaExt[1].chIn.channel =               DPC_OBJDET_DPU_AOA_PROC_EDMA_CH_1;
    resPtr->edmaHwaExt[1].chIn.eventQueue =            DPC_OBJDET_DPU_AOA_PROC_EDMAIN_PONG_EVENT_QUE;
    resPtr->edmaHwaExt[1].chOut.channel =              DPC_OBJDET_DPU_AOA_PROC_EDMA_HWA_OUTPUT_CH_1;
    resPtr->edmaHwaExt[1].chOut.eventQueue =           DPC_OBJDET_DPU_AOA_PROC_EDMAOUT_PONG_EVENT_QUE;
    resPtr->edmaHwaExt[1].stage[0].paramIn =           DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_6;
    resPtr->edmaHwaExt[1].stage[0].paramInSignature =  DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_7;
    resPtr->edmaHwaExt[1].stage[0].paramOut =          DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_8;
    resPtr->edmaHwaExt[1].stage[1].paramIn =           DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_9;
    resPtr->edmaHwaExt[1].stage[1].paramInSignature =  DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_10;
    resPtr->edmaHwaExt[1].stage[1].paramOut =          DPC_OBJDET_DPU_AOA_PROC_EDMA_VIRT_CH_11;
    resPtr->edmaHwaExt[1].eventQueue = 0;

    /* Allocate buffers for ping and pong paths: */
    for (ii = 0; ii < DPU_AOAPROCHWA_NUM_LOCAL_SCRATCH_BUFFERS; ii++)
    {
        resPtr->localScratchBuffer[ii] = gScratchBuf[ii];
    }

    aoaHwaCfgPtr = &resPtr->hwaCfg;

    aoaHwaCfgPtr->paramSetStartIdx = 0;
    aoaHwaCfgPtr->winRamOffset = 128; 


    resPtr->radarCube.datafmt = DPIF_RADARCUBE_FORMAT_1;
    resPtr->radarCube.data = testRadarCube;


    /* aoa output buffer set*/
    aoaCfg.res.detObjOutSideInfo = aoaDetObjSideInfo;
    aoaCfg.res.detObjOutMaxSize = TEST_MAX_NUM_CFARDETOBJ_DPU * TEST_MAX_NUM_PEAKS;
    aoaCfg.res.azimuthStaticHeatMap = staticHeatmap;
    aoaCfg.res.detObj2dAzimIdx = aoaDetObjAzimIdx;
    aoaCfg.res.detObjElevationAngle = aoaDetObjElevAngle;

    aoaCfg.dynCfg.fovAoaCfg = &aoaDynFovCfg;

    aoaDynOutCompRxCfg.rangeBias = 0.1;   
    
    realTemp = cosf(CUBADATA_PHASE_SHIFT / 180.f * PI);
    realTemp = realTemp * 32767;
    imagTemp = sin(CUBADATA_PHASE_SHIFT / 180.f * PI);
    imagTemp = imagTemp * (-32767);
    for (ii = 0; ii < TEST_MAX_NUMVIRTUALANTE; ii++)           //tx=3, rx =4, 3*4=12
    {
        aoaDynOutCompRxCfg.rxChPhaseComp[ii].real = (int16_t) (realTemp + 0.5);
        aoaDynOutCompRxCfg.rxChPhaseComp[ii].imag = (int16_t) (imagTemp - 0.5);

    }
    aoaCfg.dynCfg.compRxChanCfg = &aoaDynOutCompRxCfg;
   
    aoaDynBmCfg.enabled = false;        //default, will overwirte by each test
    aoaDynBmCfg.multiPeakThrsScal = TWOPEAK_POSITIVE_THRESHOLD;
    aoaCfg.dynCfg.multiObjBeamFormingCfg = &aoaDynBmCfg;

   // extMaxVelCfg.enabled = 1;
    aoaCfg.dynCfg.extMaxVelCfg = &extMaxVelCfg;
}

/**
*  @b Description
*  @n
*  set up the AOA DPU configuration structure based on each test configurations.
*
*  @retval None
*
*/
void Test_setProfile(aoaProcDpuTestConfig_t * testConfig)
{
    DPU_AoAProcHWA_StaticConfig * staticCfgPtr;
    uint16_t ii;
    int16_t interval;

    aoaCfg.res.cfarRngDopSnrList = pCfarDetObjList;
    staticCfgPtr = &aoaCfg.staticCfg;

    staticCfgPtr->numTxAntennas = testConfig->numTxAntennas;
    staticCfgPtr->numRxAntennas = testConfig->numRxAntennas;
    if (testConfig->numTxAntennas == 3)
    {
        staticCfgPtr->numVirtualAntAzim = 2 * testConfig->numRxAntennas;
        staticCfgPtr->numVirtualAntElev = testConfig->numRxAntennas;
    }
    else
    {
        staticCfgPtr->numVirtualAntAzim = testConfig->numTxAntennas * testConfig->numRxAntennas;
        staticCfgPtr->numVirtualAntElev = 0;
    }
    staticCfgPtr->numRangeBins = testConfig->numRangeBins;
    staticCfgPtr->numDopplerChirps = testConfig->numChirps;
    staticCfgPtr->numDopplerBins = testConfig->numDopplerBins;

    aoaCfg.res.hwaCfg.numParamSet =  DPU_AoAProcHWA_getNumHwaParamSets(staticCfgPtr->numTxAntennas, staticCfgPtr->numVirtualAntElev);

    /* hard code range step, and dopplerStep*/
    staticCfgPtr->rangeStep = 1.0f;
    staticCfgPtr->dopplerStep = 1.0f;
    aoaCfg.res.detObjOut = pAoaDetObj;

    aoaCfg.res.localScratchBufferSizeBytes = testConfig->numTxAntennas * DPU_AOAPROCHWA_NUM_ANGLE_BINS * sizeof(uint16_t);

    /* set up windowing for doppler fft*/
    aoaCfg.res.hwaCfg.winSym = HWA_FFT_WINDOW_SYMMETRIC;

    if (aoaCfg.res.hwaCfg.winSym == HWA_FFT_WINDOW_NONSYMMETRIC)
    {
        aoaCfg.res.hwaCfg.windowSize = testConfig->numChirps * sizeof(int32_t);
    }
    else
    {
        aoaCfg.res.hwaCfg.windowSize = (testConfig->numChirps + 1) / 2 * sizeof(int32_t);
    }

    aoaCfg.res.radarCube.dataSize = testConfig->numTxAntennas * testConfig->numRangeBins * testConfig->numDopplerBins * testConfig->numRxAntennas * 4;
    if (testConfig->numTxAntennas < 3)
        aoaCfg.res.azimuthStaticHeatMapSize = testConfig->numRangeBins * testConfig->numRxAntennas * testConfig->numTxAntennas;
    else
        aoaCfg.res.azimuthStaticHeatMapSize = testConfig->numRangeBins * testConfig->numRxAntennas * 2;

    if (!testConfig->morePeaksFlag)
    {
        for (ii = 0; ii < testConfig->numCfarDetObj; ii++)
        {
            pCfarDetObjList[ii].rangeIdx = testConfig->cfarDetObjRangeIdx[ii];
            pCfarDetObjList[ii].dopplerIdx = testConfig->cfarDetObjdopplerIdx[ii];
            pCfarDetObjList[ii].snr = 10;
            pCfarDetObjList[ii].noise = 10;
        }
    }
    else
    {
        interval = testConfig->numDopplerBins * (testConfig->numRangeBins - 1) / testConfig->numCfarDetObj;
        for (ii = 0; ii < testConfig->numCfarDetObj; ii++)
        {
            pCfarDetObjList[ii].rangeIdx = ii * interval / testConfig->numDopplerBins;
            pCfarDetObjList[ii].rangeIdx++;
            pCfarDetObjList[ii].dopplerIdx = test_modCalc(ii * interval, testConfig->numDopplerBins);
           
            pCfarDetObjList[ii].snr = 10;
            pCfarDetObjList[ii].noise = 10;
        }
    }
    aoaCfg.res.cfarRngDopSnrListSize = testConfig->numCfarDetObj;

    aoaDynBmCfg.multiPeakThrsScal = TWOPEAK_POSITIVE_THRESHOLD;
    if (testConfig->twoPeaksFlag)
    {
        aoaDynBmCfg.enabled = 1;
        if (testConfig->twoPeaksFlag == 2)
        {
            aoaDynBmCfg.multiPeakThrsScal = TWOPEAK_NEGTIVE_THRESHOLD;
        }
    }
    else
        aoaDynBmCfg.enabled = 0;
   
    /* dynamic set*/
    aoaCfg.dynCfg.prepareRangeAzimuthHeatMap = testConfig->heatMapFlag; 

    /* min and max angle */
    aoaDynFovCfg.minAzimuthDeg = -80.;
    aoaDynFovCfg.maxAzimuthDeg = 80.;
    aoaDynFovCfg.minElevationDeg = -80.;
    aoaDynFovCfg.maxElevationDeg = 80.;

    /* add velocity extension */
    extMaxVelCfg.enabled = testConfig->extVelocityFlag;
    
}

/**
*  @b Description
*  @n
*   If test is for min/max azim/elev angles, update the azim/elev references and AOA DPU configurations
*   by setting the min/max azim/elev angles to mim/max azim/elev used to generate radar cuba data.
*
*  @retval None
*
*/
void Test_updateProfile(aoaProcDpuTestConfig_t * testConfig)
{
    uint16_t ii;
    int16_t aoaSignPeakIdx;
    uint16_t count;
    float Wz;
    float scale;
    /* set the angle limts*/
    if (testConfig->minmaxAngleFlag == 2)
    {
        aoaDynFovCfg.minAzimuthDeg = asin(2.f * testConfig->minAzim / TEST_AOA_FFTSIZE) * 180 / PI;
        aoaDynFovCfg.maxAzimuthDeg = asin(2.f * testConfig->maxAzim / TEST_AOA_FFTSIZE) * 180 / PI;
        aoaDynFovCfg.minElevationDeg = asin(2.f * testConfig->minElev / TEST_AOA_FFTSIZE) * 180 / PI;
        aoaDynFovCfg.maxElevationDeg = asin(2.f * testConfig->maxElev / TEST_AOA_FFTSIZE) * 180 / PI;
    }
    else
    {
        aoaDynFovCfg.minAzimuthDeg = asin(2.f * testConfig->minAzim / TEST_AOA_FFTSIZE) * 180 / PI;
        aoaDynFovCfg.maxAzimuthDeg = 80.;
        aoaDynFovCfg.minElevationDeg = -80.;
        aoaDynFovCfg.maxElevationDeg = asin(2.f * testConfig->maxElev / TEST_AOA_FFTSIZE) * 180 / PI;

        testConfig->maxAzim = 32; // disable the max azim index
        testConfig->minElev = -32; //discalbe the min Elev index
    }

    /* update the reference */  
    count = 0;
    for (ii = 0; ii < testConfig->numCfarDetObj; ii++)
    {


        Wz = 1.f;
        scale = 1.f;
        if (testConfig->numTxAntennas == 3)   //check the elevation first
        {
            Wz = aoaCfg.res.detObjElevationAngle[ii];

            if (( Wz < (2.f * testConfig->minElev / 64.f)) || (Wz > (2.f * testConfig->maxElev / 64.f)))
            {
                testConfig->checkCfarDetObjFlag[ii] = 0; //skip this one
                continue; //no need to check the azim
            }
            //else continue check the azim
            scale = sqrt(1.f - Wz * Wz);
        }

		if (aoaCfg.res.detObj2dAzimIdx[ii] >= TEST_AOA_FFTSIZE / 2)
            aoaSignPeakIdx = aoaCfg.res.detObj2dAzimIdx[ii] - TEST_AOA_FFTSIZE;
        else
            aoaSignPeakIdx = aoaCfg.res.detObj2dAzimIdx[ii];

        if ((aoaSignPeakIdx < scale * testConfig->minAzim) || (aoaSignPeakIdx > scale * testConfig->maxAzim))
        {
              testConfig->checkCfarDetObjFlag[ii] = 0; //skip this one
        }
        else
        {
            testConfig->checkCfarDetObjFlag[ii] = 1; //keep this one
            count++;
        }
    }

    testConfig->numAoaOutObj = count;
}

/**
*  @b Description
*  @n
*       Set up the CFAR det objects with random range, doppler index and azim, elev peak index
*
*  @retval None
*
*/
void Test_aoaDpu_cfarListGen(aoaProcDpuTestConfig_t * testConfig)
{
    uint16_t ii, count;
    uint16_t randTempValue;
    uint16_t step, step1;
    uint16_t rangeIdx, dopplerIdx, tempValue, tempValue1;
    uint16_t azimTemp, elevTemp;
    int16_t minAzim, maxAzim;
    int16_t minElev, maxElev;

   // int16_t minElev, maxElev;

   // float angle;

    randTempValue = RandSimple();
    if (testConfig->twoPeaksFlag)
        testConfig->numCfarDetObj = test_modCalc(randTempValue, 2);
    else
        /* mod(rand, TEST_MAX_NUM_CFARDETOBJ)*/
        testConfig->numCfarDetObj = test_modCalc(randTempValue, TEST_MAX_NUM_CFARDETOBJ);
    testConfig->numCfarDetObj++; //at least there is 1 cfar det peak
    testConfig->numAoaOutObj = 0;
    if (testConfig->twoPeaksFlag)
    {
        for (ii = 0; ii < testConfig->numCfarDetObj; ii++)
        {
            randTempValue = RandSimple();
            testConfig->aoaNum3DfftPeaks[ii] = (randTempValue & 0x1) + 1;  
            testConfig->numAoaOutObj += testConfig->aoaNum3DfftPeaks[ii];
        }

    }
    else
    {
        for (ii = 0; ii < testConfig->numCfarDetObj; ii++)
        {
            testConfig->aoaNum3DfftPeaks[ii] = 1; //single peak
            testConfig->numAoaOutObj++;
        }

    }
    
    /* set up the range bin, and doppler bin */
    for (ii = 0; ii < testConfig->numCfarDetObj; ii++)
    {
        step = testConfig->numRangeBins * testConfig->numDopplerBins / testConfig->numCfarDetObj;
        step1 = step >> 1; //more seperate the peaks
        randTempValue = RandSimple();
        tempValue = step * ii + test_modCalc(randTempValue, step1);
        rangeIdx = test_modCalc(tempValue, testConfig->numRangeBins);
        if (rangeIdx == 0) //avoid range = 0;
            rangeIdx += 1;
        dopplerIdx = tempValue / testConfig->numRangeBins;
        testConfig->cfarDetObjRangeIdx[ii] = rangeIdx;
        testConfig->cfarDetObjdopplerIdx[ii] = dopplerIdx;
        testConfig->cfarDetObjDopplerRefIdx[ii] = testConfig->cfarDetObjdopplerIdx[ii];
        if (testConfig->cfarDetObjdopplerIdx[ii] >= testConfig->numDopplerBins/2)
        {
            testConfig->cfarDetObjDopplerRefIdx[ii] = testConfig->cfarDetObjDopplerRefIdx[ii] - testConfig->numDopplerBins;
        }

        testConfig->checkCfarDetObjFlag[ii] = 1;
    }

    /* set up the aoa azim phase */ 
    count = 0;
    minAzim = 32;
    maxAzim = -32;
    minElev = 32;
    maxElev = -32;
    for (ii = 0; ii < testConfig->numCfarDetObj; ii++)
    {
        randTempValue = RandSimple();
        azimTemp = test_modCalc(randTempValue, TEST_AOA_FFTSIZE); //dpu  uses 64 point fft for angle estimation

        if ((azimTemp <= 32) && (azimTemp >= 27))
            azimTemp -= 5;
        if ((azimTemp >= 32) && (azimTemp <= 37))
            azimTemp += 5;

        if (azimTemp >= TEST_AOA_FFTSIZE / 2)
            testConfig->aoaSignedAzimPeakIdxRef[count] = azimTemp - TEST_AOA_FFTSIZE;
        else
            testConfig->aoaSignedAzimPeakIdxRef[count] = azimTemp;
        


        if (testConfig->aoaSignedAzimPeakIdxRef[count] < minAzim)
        {
            minAzim = testConfig->aoaSignedAzimPeakIdxRef[count];
        }

        if (testConfig->aoaSignedAzimPeakIdxRef[count] > maxAzim)
        {
            maxAzim = testConfig->aoaSignedAzimPeakIdxRef[count];
        }


        if (testConfig->numTxAntennas == 3)   /* add the elevation angle*/
        {
            randTempValue = RandSimple();
            elevTemp = test_modCalc(randTempValue, TEST_AOA_FFTSIZE/2); //  -16<n<16, phase -pi/2<angle<pi/2
           
            //testConfig->aoaElevPeakIdxRef[count] = tempValue;
            if (elevTemp >= TEST_AOA_FFTSIZE / 4)
                testConfig->aoaSignedElevPeakIdxRef[count] = elevTemp - TEST_AOA_FFTSIZE / 2;
            else
                testConfig->aoaSignedElevPeakIdxRef[count] = elevTemp;

            if (testConfig->aoaSignedElevPeakIdxRef[count] < minElev)
            {
                minElev = testConfig->aoaSignedElevPeakIdxRef[count];
            }
            if (testConfig->aoaSignedElevPeakIdxRef[count] > maxElev)
            {
                maxElev = testConfig->aoaSignedElevPeakIdxRef[count];
            }
            
        }

        count++;

        if (testConfig->aoaNum3DfftPeaks[ii] > 1)   //two peask
        {
            tempValue1 = azimTemp + 23;  
            tempValue1 = test_modCalc(tempValue1, TEST_AOA_FFTSIZE);

            if ((tempValue1 >= TEST_AOA_FFTSIZE / 2)  && (tempValue1 < TEST_AOA_FFTSIZE / 2 + 5))
                tempValue1 += 5;

            if (tempValue1 >= TEST_AOA_FFTSIZE / 2)
                testConfig->aoaSignedAzimPeakIdxRef[count] = tempValue1 - TEST_AOA_FFTSIZE;
            else
                testConfig->aoaSignedAzimPeakIdxRef[count] = tempValue1;


            if (testConfig->numTxAntennas==3)
            {
                tempValue1 = elevTemp + 14;
                tempValue = test_modCalc(tempValue1, TEST_AOA_FFTSIZE/2);

                if (tempValue >= TEST_AOA_FFTSIZE / 4)
                    testConfig->aoaSignedElevPeakIdxRef[count] = tempValue - TEST_AOA_FFTSIZE/2;
                else
                    testConfig->aoaSignedElevPeakIdxRef[count] = tempValue;
            }
            count++;

        }
    }

    testConfig->minAzim = minAzim + 1;
    testConfig->maxAzim = maxAzim - 1;
    
    testConfig->minElev = minElev + 1;
    testConfig->maxElev = maxElev - 1;
  
}

/**
*  @b Description
*  @n
*   If test has more than 64/256 cfar det objects for tx=1,2/3, set up the azim peak index
*
*  @retval None
*
*/
int16_t Test_setAzim(uint16_t index)
{
    int16_t azimIdx;
    azimIdx = test_modCalc(index, 64);
    if ((azimIdx < 32) && (azimIdx > 27))
    {
        azimIdx = azimIdx - 5;
    }
    if ((azimIdx >= 32) && (azimIdx < 37))
    {
        azimIdx = azimIdx + 5;
    }

    if (azimIdx >= TEST_AOA_FFTSIZE / 2)
        azimIdx = azimIdx - TEST_AOA_FFTSIZE;
    return azimIdx;
}
/**
*  @b Description
*  @n
*   Generates the radar cuba data based on test configuration per test.
*
*  @retval None
*
*/
void Test_aoaDpu_cubaDataGen(aoaProcDpuTestConfig_t * testConfig)
{
    uint32_t ii, jj, kk, mm;
    uint32_t radarCubeIdx;
    float dopplerIncr, dopplerAngle;
    float real, imag, noiseRe, noiseIm;
    float realTemp, imagTemp;
    uint32_t txAntIdx;
    float var = 1;
    int32_t tempvalue;
    float amplitude; //signal amplitude
                     //float snr; //signal snr
    float noiseScale; //noiseScale^2 is noisevaraince
    uint16_t count;
    uint32_t rangeIdx;
    
    /* aoa azim phase */
    int32_t aoaAzimIdx1, aoaAzimIdx2;
    float aoaAzimAngle1, aoaAzimAngle2;

    /* aoa elev phase */
    int32_t aoaElevIdx1, aoaElevIdx2;
    float aoaElevAngle1, aoaElevAngle2;
    uint16_t numHeatmapAzimAnt;
    float winValue, realWin, imagWin;
    int32_t winTempValue;
    cmplx32ImRe_t  heatmapTemp;
    uint8_t heatmapScale;
    int16_t interval; 
    int16_t dopplerIdx;

    amplitude = 840.f;
    noiseScale = 60.f;

    
    /* generate the cuba data*/
#if  TEST_AOA_DEBUG
    if (testConfig->numRangeBins * testConfig->numDopplerBins * testConfig->numTxAntennas * testConfig->numRxAntennas > maxCubeSize)
    {
        maxCubeSize = testConfig->numRangeBins * testConfig->numDopplerBins * testConfig->numTxAntennas * testConfig->numRxAntennas;
        testCaseId =  testCount;
    }
#endif
    memset(testRadarCube, 0, sizeof(cmplx16ImRe_t) * testConfig->numRangeBins * testConfig->numDopplerBins * testConfig->numTxAntennas * testConfig->numRxAntennas);
    /* save the heatmap reference */
    if (testConfig->numTxAntennas == 3)
        numHeatmapAzimAnt = 2 * testConfig->numRxAntennas;
    else
        numHeatmapAzimAnt = testConfig->numTxAntennas * testConfig->numRxAntennas;
    memset(staticHeatmapRef, 0, sizeof(cmplx16ImRe_t) * testConfig->numRangeBins * numHeatmapAzimAnt);
    
 //   memset(heatmapTemp, 0, sizeof(cmplx32ImRe_t) * testConfig->numRangeBins* numHeatmapAzimAnt);

    
    /* generate the peak first */
    count = 0;
    interval = (testConfig->numRangeBins - 1) * testConfig->numDopplerBins / testConfig->numCfarDetObj;

    for (mm = 0; mm < testConfig->numCfarDetObj; mm++)
    {
        if (!testConfig->morePeaksFlag)
        {
            rangeIdx = testConfig->cfarDetObjRangeIdx[mm];
            dopplerIdx = testConfig->cfarDetObjDopplerRefIdx[mm];
            if (testConfig->extVelocityFlag)
            {
                if ((testConfig->numTxAntennas == 2) && (dopplerIdx != 0) && (mm&0x1))
                {
                   if (dopplerIdx > 0)
                   {
                        dopplerIdx = dopplerIdx - testConfig->numDopplerBins;
                   }
                   else
                   {
                        dopplerIdx = dopplerIdx + testConfig->numDopplerBins;
                   }
                }
                if ((testConfig->numTxAntennas == 3) && (dopplerIdx != 0))
                {
                    tempvalue = test_modCalc(mm, 3);  //0,1,2---> -1, 0, 1
                    dopplerIdx = dopplerIdx + (tempvalue - 1) * testConfig->numDopplerBins;
                }
                testConfig->cfarDetObjDopplerRefIdx[mm] = dopplerIdx; //update the reference, no need to recalculate
            }
            aoaAzimIdx1 = testConfig->aoaSignedAzimPeakIdxRef[count];      //signed 
            aoaElevIdx1 = 0;
            aoaAzimIdx2 = 0;
            aoaElevIdx2 = 0;
            if (testConfig->numTxAntennas == 3)
            {
                aoaElevIdx1 = testConfig->aoaSignedElevPeakIdxRef[count];
            }
            count++;
            if (testConfig->aoaNum3DfftPeaks[mm] == 2)
            {
                aoaAzimIdx2 = testConfig->aoaSignedAzimPeakIdxRef[count];

                if (testConfig->numTxAntennas == 3)
                {
                    aoaElevIdx2 = testConfig->aoaSignedElevPeakIdxRef[count];
                }
                count++;
            }
        }
        else
        {
            /* MUST MATCH WITH SETPROFILE*/
            rangeIdx = mm * interval / testConfig->numDopplerBins;
            rangeIdx++;   
            
            dopplerIdx = test_modCalc(mm * interval, testConfig->numDopplerBins);
            if (dopplerIdx >= testConfig->numDopplerBins / 2)
                dopplerIdx -= testConfig->numDopplerBins;
           
            aoaAzimIdx1 = Test_setAzim(mm);
            
            aoaElevIdx1 = aoaAzimIdx1 / 2;

        }
        for (ii = 0; ii < testConfig->numChirps; ii++) //chirp loop
        {
            for (txAntIdx = 0; txAntIdx < testConfig->numTxAntennas; txAntIdx++) //for tx antenna loop
            {
                for (jj = 0; jj < testConfig->numRxAntennas; jj++) //rx antenna loop
                {

                    dopplerIncr = 2.f * PI * dopplerIdx /testConfig->numDopplerBins/testConfig->numTxAntennas;
                    dopplerAngle = (ii * testConfig->numTxAntennas + txAntIdx) * dopplerIncr;  //increase every chirp
                    /* add the aoa phase */
                    if (txAntIdx < 2)   //for tx 0, 1, the delay is 0 1 2 3 4 5 6 7
                    {
                        aoaAzimAngle1 = 2.f * PI * (txAntIdx * testConfig->numRxAntennas + jj) * (float)aoaAzimIdx1 / (float)TEST_AOA_FFTSIZE;
                        aoaAzimAngle2 = 0.f;
                        if ((testConfig->aoaNum3DfftPeaks[mm] == 2) && (!testConfig->morePeaksFlag))
                            aoaAzimAngle2 = 2.f * PI * (txAntIdx * testConfig->numRxAntennas + jj)  * (float)aoaAzimIdx2 / (float)TEST_AOA_FFTSIZE;
                        
                        /* for tx 0, 1, no elev delay */
                        aoaElevAngle1 = 0.f;
                        aoaElevAngle2 = 0.f;
                    }
                    else //for tx == 2 numTx=3, azim delay is [ 2 3 4 5]
                    {
                        aoaAzimAngle1 = 2.f * PI * (2 + jj) * (float)aoaAzimIdx1 / (float)TEST_AOA_FFTSIZE;
                        aoaAzimAngle2 = 0.f;
                       if ((!testConfig->morePeaksFlag) && (testConfig->aoaNum3DfftPeaks[mm] == 2) )
                            aoaAzimAngle2 = 2.f * PI * (2 + jj)  * (float)aoaAzimIdx2 / (float)TEST_AOA_FFTSIZE;

                        aoaElevAngle1 = -2.f * PI * (float)aoaElevIdx1 / (float)TEST_AOA_FFTSIZE;
                        aoaElevAngle2 = 0.f;
                        if ((!testConfig->morePeaksFlag) && (testConfig->aoaNum3DfftPeaks[mm] == 2))
                            aoaElevAngle2 = -2.f * PI* (float)aoaElevIdx2 / (float)TEST_AOA_FFTSIZE;
                    }

                    real = amplitude * cosf(dopplerAngle + aoaAzimAngle1 + aoaElevAngle1);
                    imag = amplitude * sinf(dopplerAngle + aoaAzimAngle1 + aoaElevAngle1);

                    if ((!testConfig->morePeaksFlag) && (testConfig->aoaNum3DfftPeaks[mm] == 2))
                    {
                        real += (amplitude * 0.75f * cosf(dopplerAngle + aoaAzimAngle2 + aoaElevAngle2));
                        imag += (amplitude * 0.75f * sinf(dopplerAngle + aoaAzimAngle2 + aoaElevAngle2));
                    }

                    radarCubeIdx = txAntIdx * testConfig->numChirps * testConfig->numRxAntennas *  testConfig->numRangeBins;
                    radarCubeIdx += (ii * testConfig->numRxAntennas * testConfig->numRangeBins);
                    radarCubeIdx += (jj * testConfig->numRangeBins);
                    radarCubeIdx += rangeIdx;


                    tempvalue = (int32_t)MATHUTILS_ROUND_FLOAT(real);
                    MATHUTILS_SATURATE16(tempvalue);
                    testRadarCube[radarCubeIdx].real += (int16_t)tempvalue;
                    tempvalue = (int32_t)MATHUTILS_ROUND_FLOAT(imag);
                    MATHUTILS_SATURATE16(tempvalue);
                    testRadarCube[radarCubeIdx].imag += (int16_t)tempvalue;     //some peaks have same range bin, with different doppler bin

                }
            }
        }

    }


    heatmapScale = 0;
    if (testConfig->numDopplerBins == 2)
        heatmapScale = 1;      //reference right shift
    else if (testConfig->numDopplerBins == 4)
        heatmapScale = 2;
    else if (testConfig->numDopplerBins == 8)
        heatmapScale = 3;
    else if (testConfig->numDopplerBins == 16)
        heatmapScale = 4;
    else if (testConfig->numDopplerBins == 32)
        heatmapScale = 5;
    else if (testConfig->numDopplerBins == 64)
        heatmapScale = 6;
    else if (testConfig->numDopplerBins == 128)
        heatmapScale = 7;
    else if (testConfig->numDopplerBins == 256)
        heatmapScale = 8;
    else if (testConfig->numDopplerBins == 512)
        heatmapScale = 9;
    else if (testConfig->numDopplerBins == 1024)
        heatmapScale = 10;

    /* add the noise, and save the heatmap reference */
    for (txAntIdx = 0; txAntIdx < testConfig->numTxAntennas; txAntIdx++) //for tx antenna loop
    {
       for (jj = 0; jj < testConfig->numRxAntennas; jj++) //rx antenna loop
       {
           for (kk = 0; kk < testConfig->numRangeBins; kk++)
           {
               if ((txAntIdx == 0) || (txAntIdx == 1))
               {
                   heatmapTemp.real = 0;
                   heatmapTemp.imag = 0;
               }
                for (ii = 0; ii < testConfig->numChirps; ii++) //chirp loop
                {
                       /* get window coefficients in float */
                       if (testConfig->winType == 1) //check window type
                           winValue = 1.f;    //rec 
                       else
                           winValue = 0.5*(1.f - cos(2.f * PI_ * (float)ii / ((float)testConfig->numChirps - 1))); //hard code to hanning window


                   GaussianNoise(var, &noiseRe, &noiseIm);
                   //noise only
                   real = noiseScale * noiseRe;
                   imag = noiseScale * noiseIm;

                   radarCubeIdx = txAntIdx * testConfig->numChirps * testConfig->numRxAntennas *  testConfig->numRangeBins;
                   radarCubeIdx += (ii * testConfig->numRxAntennas * testConfig->numRangeBins);
                   radarCubeIdx += (jj * testConfig->numRangeBins);
                   radarCubeIdx += kk;

                   real += testRadarCube[radarCubeIdx].real;
                   imag += testRadarCube[radarCubeIdx].imag;

                   /* add a phase shift*/
                   realTemp = real;
                   imagTemp = imag;
#ifdef SUBSYS_MSS
                   real = realTemp * cosf(CUBADATA_PHASE_SHIFT / 180.f * PI) - imagTemp * sinf(CUBADATA_PHASE_SHIFT / 180.f * PI);
                   imag = realTemp * sinf(CUBADATA_PHASE_SHIFT / 180.f * PI) + imagTemp * cosf(CUBADATA_PHASE_SHIFT / 180.f * PI);
#endif
#ifdef SUBSYS_DSS
                   if (CUBADATA_PHASE_SHIFT)
                   {
                       real = realTemp * cosf(CUBADATA_PHASE_SHIFT / 180.f * PI) - imagTemp * sinf(CUBADATA_PHASE_SHIFT / 180.f * PI);
                       imag = realTemp * sinf(CUBADATA_PHASE_SHIFT / 180.f * PI) + imagTemp * cosf(CUBADATA_PHASE_SHIFT / 180.f * PI);
                   }
#endif


                   tempvalue = (int32_t)MATHUTILS_ROUND_FLOAT(real);
                   MATHUTILS_SATURATE16(tempvalue);
                   testRadarCube[radarCubeIdx].real = (int16_t)tempvalue;
                   tempvalue = (int32_t)MATHUTILS_ROUND_FLOAT(imag);
                   MATHUTILS_SATURATE16(tempvalue);
                   testRadarCube[radarCubeIdx].imag = (int16_t)tempvalue;

                   /* sum over all chirps after windowing */
                  // if (testConfig->numTxAntennas == 3)    //only accumulate tx0 and tx 1 data

                   if ((txAntIdx == 0) || (txAntIdx == 1))
                   {
                       realWin = winValue * realTemp; //with no phase shift for heatmap, will compensated back in the aoa dpu
                       imagWin = winValue * imagTemp;

                       winTempValue = (int32_t)MATHUTILS_ROUND_FLOAT(realWin);
                       //MATHUTILS_SATURATE16(winTempValue);
                       heatmapTemp.real += (int16_t)winTempValue;
                       winTempValue = (int32_t)MATHUTILS_ROUND_FLOAT(imagWin);
                       //MATHUTILS_SATURATE16(winTempValue);
                       heatmapTemp.imag += (int16_t)winTempValue;
                   }
               }/* end of chirp sum*/
                
                if ((txAntIdx == 0) || (txAntIdx == 1))
                {
                    staticHeatmapRef[kk * numHeatmapAzimAnt + txAntIdx * testConfig->numRxAntennas + jj].real = (int16_t)(heatmapTemp.real >> heatmapScale);
                    staticHeatmapRef[kk * numHeatmapAzimAnt + txAntIdx * testConfig->numRxAntennas + jj].imag = (int16_t)(heatmapTemp.imag >> heatmapScale);
                }
            }
        }
    }

   
}
#if TEST_AOA_DEBUG
/* input is 16I/16Q, output is 32 bits I and 32 bits Q*/
void Test_debug_2dWindowing(uint16_t numSamples)
{
    uint32_t ii;
    int32_t winCoef;
    uint32_t dataSample;
    int64_t realValue, imagValue;
    int64_t tempValue;

    for (ii = 0; ii < numSamples; ii++)
    {
        winCoef = (int32_t)testDopplerWindow[ii];
        dataSample = fftDataInBuf[ii];

        imagValue = (int64_t)((int16_t)(dataSample & 0x0000FFFF));      //lsb is imag
        tempValue = (imagValue * winCoef + 0x10000) >> 17;   //window coefficients is Q17 format
        fftDataWindow[ii * 2 + 1] = (int32_t)tempValue;       //imag is odd

        realValue = (int64_t)((int16_t)(dataSample >> 16));
        tempValue = (realValue * winCoef + 0x10000) >> 17;
        fftDataWindow[ii * 2] = (int32_t)tempValue;     //real is even
    }

    
}

void Test_debug_fft(int32_t * dataOut, int32_t * dataIn, uint32_t fftSize, uint32_t numAdcSamples)
{
    uint32_t ii, jj;
    float cosValue, sinValue;
    float cosStep, sinStep;
    float alpha;
    float realValueTemp, imagValueTemp;
    float realValue, imagValue;
    float inReal, inImag;
    int32_t outReal, outImag;
    float tempValue;
    uint16_t divValue;

    divValue = 0;
   
    //in 32 bits input, Real16/imag16
    for (ii = 0; ii < fftSize; ii++)
    {
        alpha = -2.f * ii * PI_ / (float)fftSize;
        cosValue = 1.f;
        sinValue = 0.f;
        cosStep = cos(alpha);
        sinStep = sin(alpha);
        //realValue = (float)((int16_t)(dataIn[0] >> 16));
        //imagValue = (float)((int16_t)(dataIn[0] & 0xFFFF));   //lsb at even
        realValue = (float)dataIn[0];
        imagValue = (float)dataIn[1];
        for (jj = 1; jj < numAdcSamples; jj++)
        {
            tempValue = cosValue;
            cosValue = cosValue * cosStep - sinValue * sinStep;
            sinValue = sinValue * cosStep + tempValue *sinStep;

            //inReal = (float)((int16_t)(dataIn[jj] >> 16));
            //inImag = (float)((int16_t)(dataIn[jj] & 0xFFFF));
            inReal = (float)dataIn[2 * jj];
            inImag = (float)dataIn[2 * jj + 1];

            realValueTemp = inReal * cosValue - inImag * sinValue;
            realValue += realValueTemp;
            imagValueTemp = inReal * sinValue + inImag * cosValue;
            imagValue += imagValueTemp;
        }
        /*match with hwa hardware */
        realValue = realValue / (float)(1 << divValue);
        outReal = (int32_t)MATHUTILS_ROUND_FLOAT(realValue);

        imagValue = imagValue / (float)(1 << divValue);
        outImag = (int32_t)MATHUTILS_ROUND_FLOAT(imagValue);

        dataOut[2 * ii] = outReal;    //out real is even
        dataOut[2 * ii + 1] = outImag; //out imag is odd
    }
}


void Test_debug_cubadataverify(aoaProcDpuTestConfig_t * testConfig)
{
    uint32_t ii, kk, jj, mm;
    uint16_t rangeIdx;
    uint32_t *cubePtr = (uint32_t *)testRadarCube;     //msb is real, lsb is imag
    uint32_t radarCubeIdx;
    float cosV, sinV, phase, cos2V, sin2V;
    float tempValue;
    
#if TEST_AOA_DEBUG_RADARCUBADATA

    /* print out the cuba data, */
    for (kk = 0; kk < testConfig->numRxAntennas; kk++)     //first rx antenna
    {
        //for (ii = 0; ii < testConfig->numRangeBins; ii++) //then range bin
        ii = testConfig->cfarDetObjRangeIdx[1];
        {
            for (mm = 0; mm < testConfig->numChirps; mm++)   //then chirp index
            {
                for (jj = 0; jj < testConfig->numTxAntennas; jj++)     //then tx antenna
                {
                    radarCubeIdx = jj * testConfig->numChirps * testConfig->numRxAntennas *  testConfig->numRangeBins;
                    radarCubeIdx += (mm * testConfig->numRxAntennas * testConfig->numRangeBins);
                    radarCubeIdx += (kk * testConfig->numRangeBins);
                    radarCubeIdx += ii;
                    System_printf("%d,%d,%d,", radarCubeIdx, testRadarCube[radarCubeIdx].real, testRadarCube[radarCubeIdx].imag);
                }
            }
            System_printf("\n");
        }
    }
#endif


    if (testConfig->numRxAntennas > 1)
    {
        //for (ii = 0; ii < testConfig->numCfarDetObj; ii++)
        ii = 1;
        {
            rangeIdx = testConfig->cfarDetObjRangeIdx[ii];

            if (testConfig->numTxAntennas >= 2)
            {
                /* exp(-j * 2 * pi*dopplerIdx / numTx / dopplerbin) */
                phase = -2.f * PI * (float)testConfig->cfarDetObjDopplerRefIdx[ii] / (float)testConfig->numTxAntennas / (float)testConfig->numDopplerBins;
                cosV = cosf(phase);
                sinV = sinf(phase);
                if (testConfig->numTxAntennas == 3)
                {
                    cos2V = cosf(2.f * phase);
                    sin2V = sinf(2.f * phase);
                }
            }

            for (kk = 0; kk < testConfig->numRxAntennas; kk++)    //all rx antenna
            {
                for (jj = 0; jj < testConfig->numTxAntennas; jj++) //all tx antenna
                {
                    for (mm = 0; mm < testConfig->numChirps; mm++) //all chirps
                    {
                        /* get the input data */

                        radarCubeIdx = jj * testConfig->numChirps * testConfig->numRxAntennas *  testConfig->numRangeBins;
                        radarCubeIdx += (mm * testConfig->numRxAntennas * testConfig->numRangeBins);
                        radarCubeIdx += (kk * testConfig->numRangeBins);
                        radarCubeIdx += rangeIdx;
                        fftDataInBuf[mm] = cubePtr[radarCubeIdx];

                    }
                    /* do the windowing fft */
                    Test_debug_2dWindowing(testConfig->numChirps); //16I/Q in, 32 I/Q out
                                                                   // if (testConfig->numDopplerBins < 8)
                                                                   // {
                                                                   //     Test_debug_fft(fftDataOutBuf, fftDataWindow, 8, testConfig->numChirps);   //minimum fft size is 8
                                                                   //     fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2] = fftDataOutBuf[testConfig->cfarDetObjdopplerIdx[ii] *(8/ testConfig->numChirps) * 2];
                                                                   //     fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2 + 1] = fftDataOutBuf[testConfig->cfarDetObjdopplerIdx[ii] * (8 / testConfig->numChirps) * 2 + 1];

                                                                   // }
                                                                   //else
                    {
                        Test_debug_fft(fftDataOutBuf, fftDataWindow, testConfig->numDopplerBins, testConfig->numChirps);

                        /* find the value corresponds the doppler index, should be the maximum */
                        fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2] = fftDataOutBuf[testConfig->cfarDetObjdopplerIdx[ii] * 2];
                        fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2 + 1] = fftDataOutBuf[testConfig->cfarDetObjdopplerIdx[ii] * 2 + 1];

                        if ((testConfig->numTxAntennas >= 2) && (jj == 1))   //numTx=2,3, tx=1 doppler compensation
                        {
                            /* compensate the second tx data by exp(-j*2*pi*dopplerIdx/numTx/dopplerbin) */
                            tempValue = (float)fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2] * cosV - (float)fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2 + 1] * sinV;
                            if (tempValue > 0)
                                fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2] = (int32_t)(tempValue + 0.5);
                            else
                                fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2] = (int32_t)(tempValue - 0.5);

                            tempValue = (float)fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2] * sinV + (float)fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2 + 1] * cosV;
                            if (tempValue > 0)
                                fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2 + 1] = (int32_t)(tempValue + 0.5);
                            else
                                fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2 + 1] = (int32_t)(tempValue - 0.5);



                        }
                        if ((testConfig->numTxAntennas == 3) && (jj == 2)) //numtx=3, tx=2, compensation
                        {
                            tempValue = (float)fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2] * cos2V - (float)fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2 + 1] * sin2V;
                            if (tempValue > 0)
                                fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2] = (int32_t)(tempValue + 0.5);
                            else
                                fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2] = (int32_t)(tempValue - 0.5);

                            tempValue = (float)fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2] * sin2V + (float)fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2 + 1] * cos2V;
                            if (tempValue > 0)
                                fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2 + 1] = (int32_t)(tempValue + 0.5);
                            else
                                fft3dDataInBuf[(jj * testConfig->numRxAntennas + kk) * 2 + 1] = (int32_t)(tempValue - 0.5);

                        }
                    }
                }
            }

            /* do the 3d fft*/
#if TEST_AOA_DEBUG_3DFFTIN
            for (mm = 0; mm < testConfig->numTxAntennas *testConfig->numRxAntennas; mm++)
            {
                System_printf("%d,%d\n", fft3dDataInBuf[2 * mm], fft3dDataInBuf[2 * mm + 1]);   //even is real, odd is imag
            }
            System_printf("\n");
#endif
            if (testConfig->numTxAntennas < 3)
            {
                Test_debug_fft(fft3dDataOutBuf, fft3dDataInBuf, TEST_AOA_FFTSIZE, testConfig->numTxAntennas*testConfig->numRxAntennas);
            }
            else if (testConfig->numTxAntennas == 3)
            {

                Test_debug_fft(fft3dDataOutBuf, fft3dDataInBuf, TEST_AOA_FFTSIZE, 8);

                Test_debug_fft(&fft3dDataOutBuf[TEST_AOA_FFTSIZE*2], &fft3dDataInBuf[8*2], TEST_AOA_FFTSIZE, 4);

            }
#if TEST_AOA_DEBUG_3DFFTOUT
            {
                uint64_t absValue;
                uint64_t maxAbsValue;
                uint16_t maxIdxAzim;

                maxAbsValue = 0;
                maxIdxAzim = 0;
                for (mm = 0; mm < TEST_AOA_FFTSIZE; mm++)
                {
                    // System_printf("%d,%d\n", fft3dDataOutBuf[2 * mm], fft3dDataOutBuf[2 * mm + 1]);
                    absValue = (int64_t)fft3dDataOutBuf[2 * mm] * fft3dDataOutBuf[2 * mm] + (int64_t)fft3dDataOutBuf[2 * mm + 1] * fft3dDataOutBuf[2 * mm + 1];
                    if (absValue > maxAbsValue)
                    {
                        maxIdxAzim = mm;
                        maxAbsValue = absValue;
                    }
                }
                System_printf("The azim peak idx is %d, ref = %d\n", maxIdxAzim, testConfig->aoaSignedAzimPeakIdxRef[ii]);
                if (testConfig->numTxAntennas == 3)
                {
                    /* find the elev * conj(azim)*/
                    int32_t elevReal, elevImag, azimReal, azimImag;
                    float realValue, imagValue;
                    float angleEst;
                    float angleCal;
                    azimReal = fft3dDataOutBuf[2 * maxIdxAzim];
                    azimImag = fft3dDataOutBuf[2 * maxIdxAzim + 1];

                    elevReal = fft3dDataOutBuf[2 * maxIdxAzim + 2 * TEST_AOA_FFTSIZE];
                    elevImag = fft3dDataOutBuf[2 * maxIdxAzim + 2 * TEST_AOA_FFTSIZE + 1];

                    realValue = (float) elevReal *  (float)azimReal + (float)elevImag * (float)azimImag;
                    imagValue = (float)azimReal *  (float)elevImag - (float)elevReal *(float)azimImag;

                    /* should be 2*2*pi*azimIdx/64 - 2*pi*elevIdx/32 */
                    angleEst = atan2(imagValue, realValue);
                    angleCal = 2.f * 2.f * PI * testConfig->aoaSignedAzimPeakIdxRef[ii] / 64.f- 2 * PI * testConfig->aoaSignedElevPeakIdxRef[ii] / 64.f;
                    if (angleCal < -2.f * PI)
                        angleCal += (2.f * PI);
                    if (angleCal > 2.f * PI)
                        angleCal -= (2.f * PI);

                    System_printf("the elev angle diff est = %f, cal = %f, diff = %f\n", angleEst, angleCal, fabs(angleCal - angleEst));
                    

                }

            }
#endif

        }
    }

}
#endif
/**
*  @b Description
*  @n
*   check the AOA DPU results with the reference.
*
*  @retval None
*
*/
void Test_printResults(aoaProcDpuTestConfig_t * testConfig)
{

    uint32_t ii, jj;
    uint32_t count, refCount;
    int16_t aoaSignPeakIdx;
    float x, y, z;
    uint8_t testPass = 1;
    float elevAngleRef;
    float elevAngleErr;
    uint16_t numAzimVirtualAnt;
    int16_t heapmapDiff;
    int16_t azimSignedPeakIdxRef;
    uint16_t rangeIdx;
    uint16_t interval;
    int16_t dopplerIdx;
    int16_t elevIdxRef;
    float range;
    
    interval = (testConfig->numRangeBins - 1) * testConfig->numDopplerBins / testConfig->numCfarDetObj;

    /* check the aoa output object number */
    if (testConfig->twoPeaksFlag == 2)
    {
        if ((outAoaProc.numAoADetectedPoints * 2)!= testConfig->numAoaOutObj)
        {
            System_printf("\nAOA output number is : aoaOut=%d, ref=%d\n", outAoaProc.numAoADetectedPoints, testConfig->numAoaOutObj);
            finalResults = 0;
            testPass = 0;
            if (testConfig->morePeaksFlag)
            {
                System_printf(" FAIL \n");
                return;
            }
        }
    }
    else
    {
        if (outAoaProc.numAoADetectedPoints != testConfig->numAoaOutObj)
        {
            System_printf("\nAOA output number is : aoaOut=%d, ref=%d\n", outAoaProc.numAoADetectedPoints, testConfig->numAoaOutObj);
            finalResults = 0;
            testPass = 0;
            if (testConfig->morePeaksFlag)
            {
                System_printf(" FAIL \n");
                return;
            }
        }
    }

    /* check the x,y,z*/
    if (testConfig->numTxAntennas * testConfig->numRxAntennas == 1)
    {
        for (ii = 0; ii < testConfig->numCfarDetObj; ii++) //no aoa, directly output the cfar result
        {
            if ((aoaCfg.res.detObjOut[ii].x != 0.f) || (aoaCfg.res.detObjOut[ii].z != 0.f) || (aoaCfg.res.detObjOut[ii].y != (float)testConfig->cfarDetObjRangeIdx[ii]))
            {
                
                if (testPass)
                    System_printf("\n");
                System_printf("AOA %d out x/y/z is : aoaOut=%d,%d,%d, ref=%d\n", ii, aoaCfg.res.detObjOut[ii].x, aoaCfg.res.detObjOut[ii].y, aoaCfg.res.detObjOut[ii].z, testConfig->cfarDetObjRangeIdx[ii]);
                finalResults = 0;
                testPass = 0;
                
            }
        }
    }
    else
    {
        /* check the x.y.z, and peakIdx*/
        count = 0;
        refCount = 0;
        for (ii = 0; ii < testConfig->numCfarDetObj; ii++) //check the peak index
        {


            if (!testConfig->morePeaksFlag)
            {
                if (testConfig->checkCfarDetObjFlag[ii] == 0)
                {
                    refCount++;
                    if (testConfig->aoaNum3DfftPeaks[ii] == 2)
                    {
                        refCount++;
                    }
                    continue; //skip this obj, it is deleted by min/max angle
                }
            }
            //else, more peaks case, alwarys check, no deleted 

			if (aoaCfg.res.detObj2dAzimIdx[count] >= TEST_AOA_FFTSIZE / 2)
                aoaSignPeakIdx = aoaCfg.res.detObj2dAzimIdx[count] - TEST_AOA_FFTSIZE;
            else
                aoaSignPeakIdx = aoaCfg.res.detObj2dAzimIdx[count];

            if (!testConfig->morePeaksFlag)
            {
                azimSignedPeakIdxRef = testConfig->aoaSignedAzimPeakIdxRef[refCount];
            }
            else
            {
                azimSignedPeakIdxRef = Test_setAzim(ii);
            }
            if (fabs(aoaSignPeakIdx - azimSignedPeakIdxRef) > MAX_PEAKIDX_ERROR)// && (fabs(aoaCfg.res.detObj2dAzimIdx[ii] - testConfig->aoaSignedAzimPeakIdxRef[count])))
            {
                
                if (testPass)
                    System_printf("\n");
                System_printf("Cfar Obj %d 1st peakIdx : aoaOut=%d, ref=%d\n", ii, aoaCfg.res.detObj2dAzimIdx[count], azimSignedPeakIdxRef);
                finalResults = 0;
                testPass = 0;
                
            }

            if (testConfig->numTxAntennas == 3)
            {
                if (!testConfig->morePeaksFlag)
                {
                    elevIdxRef = testConfig->aoaSignedElevPeakIdxRef[refCount];
                }
                else
                {
                    elevIdxRef = azimSignedPeakIdxRef / 2;
                }
                elevAngleRef = 2.f * elevIdxRef / (float)TEST_AOA_FFTSIZE;
                elevAngleErr = fabs(elevAngleRef - aoaCfg.res.detObjElevationAngle[count]);

                if (elevAngleErr > MAX_ELEVANGLE_ERROR)
                {
                    if (testPass)
                        System_printf("\n");
                    System_printf("Cfar obj %d 1st ElevAngle : aoaOut=%f, ref=%f, error=%f\n", ii, aoaCfg.res.detObjElevationAngle[ii], elevAngleRef, elevAngleErr);
                    finalResults = 0;
                    testPass = 0;
                }
            }
            /* x is range * sin */
            if (!testConfig->morePeaksFlag)
            {
                rangeIdx = testConfig->cfarDetObjRangeIdx[ii];
            }
            else
            {
                rangeIdx = ii * interval / testConfig->numDopplerBins;
                rangeIdx++;
            }
            range = (float)rangeIdx - aoaDynOutCompRxCfg.rangeBias;
            x = range * 2.f * (float)aoaSignPeakIdx / (float)TEST_AOA_FFTSIZE;
            if (testConfig->numTxAntennas == 3)
            {
                z = range * aoaCfg.res.detObjElevationAngle[count];
                y = sqrtf(range * range - x * x - z * z);
            }
            else 
            {
                z = 0.f;
                y = range * sqrtf(1.f - 4.f * (float)aoaSignPeakIdx * (float)aoaSignPeakIdx / (float)TEST_AOA_FFTSIZE / (float)TEST_AOA_FFTSIZE);

            }
           
            if ( (fabs(aoaCfg.res.detObjOut[count].x - x) > MAX_LOCATION_ERROR) ||
                 (fabs(aoaCfg.res.detObjOut[count].y - y) > MAX_LOCATION_ERROR) ||
                 (fabs(aoaCfg.res.detObjOut[count].z - z) > MAX_LOCATION_ERROR) )
            {
                if (testPass)
                    System_printf("\n");
                System_printf("cfar obj %d out 1st x/y/z is : aoaOut=%f,%f,%f, ref=%f,%f,%f\n", ii, aoaCfg.res.detObjOut[count].x, aoaCfg.res.detObjOut[count].y, aoaCfg.res.detObjOut[count].z, x,y,z);
                finalResults = 0;
                testPass = 0;
            }

            count++;
            refCount++;


            if ((!testConfig->morePeaksFlag) &&(testConfig->aoaNum3DfftPeaks[ii] == 2) )
            {
                if (testConfig->twoPeaksFlag == 1)
                {
                    if (aoaCfg.res.detObj2dAzimIdx[count] >= TEST_AOA_FFTSIZE / 2)
                        aoaSignPeakIdx = aoaCfg.res.detObj2dAzimIdx[count] - TEST_AOA_FFTSIZE;
                    else
                        aoaSignPeakIdx = aoaCfg.res.detObj2dAzimIdx[count];


                    if (fabs(aoaSignPeakIdx - testConfig->aoaSignedAzimPeakIdxRef[refCount]) > MAX_PEAKIDX_ERROR)// && (fabs(aoaCfg.res.detObj2dAzimIdx[ii] - testConfig->aoaSignedAzimPeakIdxRef[count])))
                    {

                        if (testPass)
                            System_printf("\n");
                        System_printf("Cfar obj %d 2rd peakIdx : aoaOut=%d, ref=%d\n", ii, aoaCfg.res.detObj2dAzimIdx[count], testConfig->aoaSignedAzimPeakIdxRef[refCount]);
                        finalResults = 0;
                        testPass = 0;

                    }

                    if (testConfig->numTxAntennas == 3)
                    {
                        elevAngleRef = 2.f * testConfig->aoaSignedElevPeakIdxRef[refCount] / (float)TEST_AOA_FFTSIZE;
                        elevAngleErr = fabs(elevAngleRef - aoaCfg.res.detObjElevationAngle[count]);

                        if (elevAngleErr > MAX_ELEVANGLE_ERROR)
                        {
                            if (testPass)
                                System_printf("\n");
                            System_printf("Cfar obj %d 2rd ElevAngle : aoaOut=%f, ref=%f, error=%f\n", ii, aoaCfg.res.detObjElevationAngle[ii], elevAngleRef, elevAngleErr);
                            finalResults = 0;
                            testPass = 0;
                        }
                    }
                    /* x is range * sin */
                    range = (float)testConfig->cfarDetObjRangeIdx[ii] - aoaDynOutCompRxCfg.rangeBias;
                    x = range * 2.f * (float)aoaSignPeakIdx / (float)TEST_AOA_FFTSIZE;
                    if (testConfig->numTxAntennas == 3)
                    {
                        z = range * aoaCfg.res.detObjElevationAngle[count];
                        y = sqrtf(range * range - x * x - z * z);
                    }
                    else
                    {
                        z = 0.f;
                        y = range * sqrtf(1.f - 4.f * (float)aoaSignPeakIdx * (float)aoaSignPeakIdx / (float)TEST_AOA_FFTSIZE / (float)TEST_AOA_FFTSIZE);
                    }

                    if ((fabs(aoaCfg.res.detObjOut[count].x - x) > MAX_LOCATION_ERROR) ||
                        (fabs(aoaCfg.res.detObjOut[count].y - y) > MAX_LOCATION_ERROR) ||
                        (fabs(aoaCfg.res.detObjOut[count].z - z) > MAX_LOCATION_ERROR))
                    {
                        if (testPass)
                            System_printf("\n");
                        System_printf("Cfar obj %d 2rd out x/y/z is : aoaOut=%f,%f,%f, ref=%f,%f,%f\n", ii, aoaCfg.res.detObjOut[count].x, aoaCfg.res.detObjOut[count].y, aoaCfg.res.detObjOut[count].z, x, y, z);
                        finalResults = 0;
                        testPass = 0;
                    }

                    count++;
                    refCount++;
                }
                else             //negtive two peak testing, one peak is not detected
                    refCount++; 
            }
        }


    }
    count = 0;
    for (ii = 0; ii < testConfig->numCfarDetObj; ii++) //no aoa, directly output the cfar result
    {

        if ((!testConfig->morePeaksFlag) && (!testConfig->checkCfarDetObjFlag[ii]))
        {
            continue;
        }
        if (!testConfig->morePeaksFlag)
        {
            dopplerIdx = testConfig->cfarDetObjDopplerRefIdx[ii];
        }
        else
        {
            dopplerIdx = test_modCalc(ii * interval, testConfig->numDopplerBins);
            if (dopplerIdx >= testConfig->numDopplerBins / 2)
                dopplerIdx -= testConfig->numDopplerBins;
        }
        if (aoaCfg.res.detObjOut[count].velocity != (float)dopplerIdx)
        {
            if (testPass)
                System_printf("\n");

            System_printf("Cfar obj %d 1st out vel is : aoaOut=%f, ref=%d\n", ii, aoaCfg.res.detObjOut[count].velocity, dopplerIdx);
            finalResults = 0;
            testPass = 0;
        }
        count++;
        if ((!testConfig->morePeaksFlag) && (testConfig->aoaNum3DfftPeaks[ii] == 2) && (testConfig->twoPeaksFlag == 1))
        {
            if (aoaCfg.res.detObjOut[count].velocity != (float)testConfig->cfarDetObjDopplerRefIdx[ii])
            {
                if (testPass)
                    System_printf("\n");
                System_printf("Cfar obj %d 2rd out vel is : aoaOut=%f, ref=%d\n", ii, aoaCfg.res.detObjOut[ii].velocity, testConfig->cfarDetObjDopplerRefIdx[ii]);
                finalResults = 0;
                testPass = 0;
            }
            count++;
        }
       
    }

    for (ii = 0; ii < outAoaProc.numAoADetectedPoints; ii++)
    {
       /* check some side information*/
       if ((aoaCfg.res.detObjOutSideInfo[ii].snr != 10.f) || (aoaCfg.res.detObjOutSideInfo[ii].noise != 10.f))
       {
           if (testPass)
               System_printf("\n");
            System_printf("AOA %d sideInfo is : aoaOut=%d,%d\n", ii, aoaCfg.res.detObjOutSideInfo[ii].snr, aoaCfg.res.detObjOutSideInfo[ii].noise);
            finalResults = 0;
            testPass = 0;
        }

    }

    /* add heatmap checking */
    if (testConfig->heatMapFlag)
    {
        if (testConfig->numTxAntennas == 3)
            numAzimVirtualAnt = 2 * testConfig->numRxAntennas;
        else
            numAzimVirtualAnt = testConfig->numTxAntennas * testConfig->numRxAntennas;

        for (ii = 0; ii < testConfig->numRangeBins; ii++)
        {
            for (jj = 0; jj < numAzimVirtualAnt; jj++)
            {
               
                heapmapDiff = abs(staticHeatmapRef[ii *numAzimVirtualAnt + jj].real - staticHeatmap[ii *numAzimVirtualAnt + jj].real );

                if (heapmapDiff > MAX_HEATMAP_ERROR)
                {
                    if (testPass)
                        System_printf("\n");
                    System_printf("heatmap bin %d, ant %d, ref=%d, aoa=%d, diff =%d real fail\n", ii, jj, staticHeatmapRef[ii *numAzimVirtualAnt + jj].real, staticHeatmap[ii *numAzimVirtualAnt + jj].real, heapmapDiff);
                    finalResults = 0;
                    testPass = 0;
                }

                heapmapDiff = abs(staticHeatmapRef[ii *numAzimVirtualAnt + jj].imag - staticHeatmap[ii *numAzimVirtualAnt + jj].imag );

                if (heapmapDiff > MAX_HEATMAP_ERROR)
                {
                    if (testPass)
                        System_printf("\n");
                    System_printf("heatmap bin %d, ant %d, ref=%d, aoa=%d diff = %d imag fail\n", ii, jj, staticHeatmapRef[ii *numAzimVirtualAnt + jj].imag, staticHeatmap[ii *numAzimVirtualAnt + jj].imag, heapmapDiff);
                    finalResults = 0;
                    testPass = 0;
                }

            }
        }
    }
    if (testPass)
    {
        System_printf(" PASS \n");
    }
    else
    {
        System_printf(" FAIL \n");
    }
    
    System_printf("\n");
}

/**
*  @b Description
*  @n
*     Generate 2D windowing coefficients. 
*
*  @retval None
*
*/
void Test_window2DCoef_gen(uint32_t numSamples, uint8_t winType, int32_t *winPtr)
{
    float ephyR, ephyI;
    float phi = 2 * PI_ / ((float)numSamples - 1);


    uint32_t ii;
    float a0;
    float winValue;
    int32_t winValueFixed;
    float cosValue, sinValue;
    float temp;


    cosValue = 1.f;
    sinValue = 0.f;

    ephyR = cos(phi);
    ephyI = sin(phi);
    a0 = 0.5f;


    if (winType == 1)
    {
        for (ii = 0; ii < numSamples; ii++)
        {
            winPtr[ii] = (1 << 17) - 1; //rec window, for debug
        }
    }
    else
    {
        /* hanning window */
        for (ii = 0; ii < numSamples; ii++)
        {
            winValue = a0 * (1.f - cosValue);       //0.5*(1-cos(2*pi*n/N-1))

            winValue = winValue * (1 << 17) + 0.5;     //Q17 format
            winValueFixed = (uint32_t)winValue;
            if (winValueFixed >= (1 << 17))
            {
                winValueFixed = (1 << 17) - 1;
            }
            temp = cosValue;
            cosValue = cosValue * ephyR - sinValue * ephyI;
            sinValue = temp * ephyI + sinValue * ephyR;

            //winPtr[ii] = (1<<17) - 1; //rec window, for debug
            winPtr[ii] = winValueFixed;
        }
    }

}

/**
*  @b Description
*  @n
*     test main task  : Generate the radar cuba data based on the test configuration, and generate the cfar detected
*                       object list. The cuba data and the detected object list are sent to AOA dpu. The DPU outputs
*                       the deteced object azimth and elevation angle, which are checked against the test configuration.
*                       If the differece is within the error threshold, the test is declared PASS, otherwise, it is declared
*                       FAIL. The tests cover 5 TX/RX antenna setups, 1/1, 1/2, 1/4, 2/4 and 3/4. 
*
*  @retval None
*
*/
void Test_task(UArg arg0, UArg arg1)
{
    uint32_t ii, jj, kk, kk1;
   
    char featureName[200];
    uint16_t numAntennas[TEST_ANTENNA_LOOP][2] = {
        /* numTx, numRx*/
        {1, 1},
        {1, 2},
        {1, 4},
        {2, 4},
        {3, 4}
    };
    
    uint32_t numDopplerBin[TEST_DOPPLER_BIN_SIZE] = {2, 4, 8, 16, 32, 64, 128, 256, 512};
    uint32_t numRangeBin[TEST_RANGE_BIN_SIZE] = { 16, 32, 64, 128, 256, 512, 1024 };
    uint32_t numTests;
    int32_t   retVal;
    uint16_t dopplerLoopStep;
    uint16_t numRangeBinSize;
    uint16_t idx;
    uint32_t maxNumChirps,mm;
    
    finalResults = 1;
    System_printf("...... Initialization ...... \n");

    /* hwa, edma, dpu inialization */
    aoaProc_test_hwaEdmainit();
    aoaProc_test_dpuInit();

    /* aoa dpu config*/
    aoaProc_test_dpuConfig();
    
    System_printf("aoa Proc DPU Test start ...... \n");
    
    /*for tx/rx1,1, only run 5 doppler size, each with 1 range bin size */
    numTests = TEST_ANTENNA_LOOP; 
    /* antenne combination * doppler size, 2 range bin size*/             
    numTests += (TEST_ANTENNA_LOOP - 1) * TEST_DOPPLER_BIN_SIZE * 2;
    /* for each doppler bin size, chirp even, odd, maximum */
    numTests = numTests * 3; 
    /*add doppler size = 1024 tests, for each tx/rx setting 1/2 and 1/4, add 3 tests with different range bin, and even, odd, 
    maximum chirp number if 2/4, 3/4 maximum chirp is limited to <512 due to DPU_AOAPROCHWA_EEXCEEDHWAMEM error, can not get to doppler bin = 1024 */
    numTests += (2 * 3);   
    printf("\n...... %d Tests to be run .......\n\n", numTests);

    testCount = 0;
    for (ii = 0; ii < TEST_ANTENNA_LOOP; ii++) /* antenna loop */
    {
        dopplerLoopStep = 1;
        numRangeBinSize = 2;
        if (ii == 0)
        {
            dopplerLoopStep = 2;
            numRangeBinSize = 1; //for 1tx, 1rx, 1 range bin size
        }
       
        for (jj = 0; jj < TEST_DOPPLER_BIN_SIZE; jj += dopplerLoopStep) /* doppler size loop*/
        {
            aoaTestCfg.numTxAntennas = numAntennas[ii][0];
            aoaTestCfg.numRxAntennas = numAntennas[ii][1];
            aoaTestCfg.numDopplerBins = numDopplerBin[jj];       //NOT TEST OVERSAMPLING

            maxNumChirps = 16384 / aoaTestCfg.numTxAntennas / aoaTestCfg.numRxAntennas / 4;
            if (maxNumChirps > aoaTestCfg.numDopplerBins)
                maxNumChirps = aoaTestCfg.numDopplerBins;

            for (mm = 0; mm < 3; mm++)
            {
                for (kk = 0; kk < numRangeBinSize; kk++) /* range bin size loop, random pick range bin size */
                {
                    /* randomly find the range bin sizes*/
                    if ((aoaTestCfg.numTxAntennas == 1)) //||( (aoaTestCfg.numTxAntennas == 2) &&(aoaTestCfg.numRangeBins==2)))
                    {
                        if (aoaTestCfg.numDopplerBins < 64)
                        {
                            kk1 = testCount + kk * 5;
                            kk1 = test_modCalc(kk1, TEST_RANGE_BIN_SIZE); 
                        }
                        else
                        {
                            kk1 = testCount + kk * ((11 - jj) / 2);
                            kk1 = test_modCalc(kk1, (11 - jj));  //maximum range size is 512,256,... for doppler size >=64
                        }
                    }
                    else if (aoaTestCfg.numTxAntennas == 2)
                    {
                        if (aoaTestCfg.numDopplerBins < 32)
                        {
                            if (aoaTestCfg.numDopplerBins == 2)
                                kk1 = testCount;
                            else
                                kk1 = testCount + kk * 4;
                            kk1 = test_modCalc(kk1, TEST_RANGE_BIN_SIZE);
                        }
                        else if (aoaTestCfg.numDopplerBins < 256)
                        {
                            kk1 = testCount + kk * ((11 - jj) / 2);
                            kk1 = test_modCalc(kk1, (11 - jj));  //maximum range size is 512,256,... for doppler size >=64
                        }
                        else  //jj = 8, 512
                        {
                            kk1 = testCount;
                            kk1 = test_modCalc(kk1, (10 - jj));  //maximum range size is 256,... for doppler size >=256
                        }
                    }
                    else // (aoaTestCfg.numTxAntennas == 3)
                    {
                        if (aoaTestCfg.numDopplerBins < 32)
                        {
                            if (aoaTestCfg.numDopplerBins < 8)
                                kk1 = testCount;
                            else if (aoaTestCfg.numDopplerBins == 16)
                                kk1 = testCount + 2;
                            else
                                kk1 = testCount + kk * 3;

                            kk1 = test_modCalc(kk1, TEST_RANGE_BIN_SIZE);
                        }
                        else if (aoaTestCfg.numDopplerBins < 128)
                        {
                            kk1 = testCount + kk * ((11 - jj) / 2);
                            kk1 = test_modCalc(kk1, (10 - jj));  //maximum range size is 256,... 
                        }
                        else if (aoaTestCfg.numDopplerBins < 512)
                        {
                            kk1 = testCount + kk * 13;
                            kk1 = test_modCalc(kk1, (10 - jj)); //maximum range size is 256,... 
                        }
                        else
                        {
                            kk1 = testCount;
                            kk1 = test_modCalc(kk1, (10 - jj));;  //maximum range size is 256,...
                        }
                    }

                    aoaTestCfg.numRangeBins = numRangeBin[kk1];

#if (defined (SOC_XWR68XX))
                    if (aoaTestCfg.numTxAntennas * aoaTestCfg.numRxAntennas * aoaTestCfg.numRangeBins * aoaTestCfg.numDopplerBins > TEST_MAX_RADAR_CUBE_SIZE)
                    {
                        aoaTestCfg.numRangeBins = numRangeBin[kk1 - 1];       //due to l3 memory in 68 
                    }
#endif
                    /* set up the number of chirps <= doppler bin size*/
                    if (aoaTestCfg.numDopplerBins == 2)
                        aoaTestCfg.numChirps = 2;
                    else if (aoaTestCfg.numDopplerBins == 4)
                        aoaTestCfg.numChirps = 3 + (mm & 0x1);
                    else if (aoaTestCfg.numDopplerBins == 8)
                        aoaTestCfg.numChirps = 8 - (mm & 0x3);
                    else if (aoaTestCfg.numDopplerBins == 16)
                        aoaTestCfg.numChirps = 16 - ((mm + kk) & 0x7);
                    else
                    {
                        if (mm == 0)
                        {
                            aoaTestCfg.numChirps = maxNumChirps;
                        }
                        else
                        {
                            aoaTestCfg.numChirps = maxNumChirps - (mm + kk) * 2 - (mm - 1) * 3;
                        }

                    }

                    /* multiple peaks */
                    aoaTestCfg.twoPeaksFlag = 0;
                    if ((aoaTestCfg.numTxAntennas * aoaTestCfg.numRxAntennas == 2) || (aoaTestCfg.numTxAntennas * aoaTestCfg.numRxAntennas == 1))
                    {
                        aoaTestCfg.twoPeaksFlag = 0;
                    }
                    else if ((testCount & 0x7) == 0)
                    {
                        aoaTestCfg.twoPeaksFlag = 1;
                        /* add several tests for two peaks, but set threshold high, so only sigle peak is detected */
#if (defined (SOC_XWR18XX))
                        if ((testCount == 104) || (testCount == 128) || (testCount == 192) || (testCount == 200) || (testCount == 216))
                        {
                            aoaTestCfg.twoPeaksFlag = 2;
                        }
#endif
#if (defined (SOC_XWR68XX))
                        if ((testCount == 104) || (testCount == 128) || (testCount == 192) || (testCount == 208) || (testCount == 216))
                        {
                            aoaTestCfg.twoPeaksFlag = 2;
                        }
#endif

                    }

                    //heat map
                    if (aoaTestCfg.numTxAntennas * aoaTestCfg.numRxAntennas == 1)
                        aoaTestCfg.heatMapFlag = false;
                    else
                        aoaTestCfg.heatMapFlag = true;

                    /* generate the windowing coefficients */
                    if (aoaTestCfg.numChirps == 2)
                    {
                        aoaTestCfg.winType = 1; //rec
                    }
                    else
                    {
                        aoaTestCfg.winType = 0;
                    }

                    /* generate the cfar det obj list */
                    pCfarDetObjList = &cfarDetObjList[0];
                    pAoaDetObj = &aoaDetObj[0];
                    Test_aoaDpu_cfarListGen(&aoaTestCfg);

                    /* check the min and max angle */
                    aoaTestCfg.minmaxAngleFlag = 0;
                    if ((aoaTestCfg.numCfarDetObj >= 4) && ((testCount & 0x3) <= 1) && (aoaTestCfg.numRxAntennas != 1))
                    {
                        aoaTestCfg.minmaxAngleFlag = aoaTestCfg.numCfarDetObj - 3;
                    }

                    /* check more peaks */
                    aoaTestCfg.morePeaksFlag = 0;
                    if ((!aoaTestCfg.minmaxAngleFlag) && (!aoaTestCfg.twoPeaksFlag))
                    {
                        if ((aoaTestCfg.numTxAntennas < 3) && (aoaTestCfg.numRxAntennas > 1) && (aoaTestCfg.numRangeBins * aoaTestCfg.numDopplerBins > 256) && ((testCount & 0x3) == 0))
                        {
                            if (aoaTestCfg.numRangeBins == 16)  //minimum range bin
                            {
                                if (aoaTestCfg.numDopplerBins > 32)
                                {
                                    aoaTestCfg.morePeaksFlag = 1;
                                }
                            }
                            else
                            {
                                aoaTestCfg.morePeaksFlag = 1;
                            }
                        }
                        if ((aoaTestCfg.numTxAntennas == 3) && (aoaTestCfg.numRangeBins * aoaTestCfg.numDopplerBins > 64) && ((testCount & 0x3) == 0))
                        {
                            aoaTestCfg.morePeaksFlag = 1;
                        }
                    }
#ifdef SUBSYS_DSS
                    /* for running on dsp, not enough memory for L2, move cfarobj list, and aoa output cloud point into L3,
					   limit cuba data size to 65536 in L2 */
                    if (aoaTestCfg.numRangeBins * aoaTestCfg.numDopplerBins * aoaTestCfg.numTxAntennas * aoaTestCfg.numRxAntennas > 65536)
                    {
                        aoaTestCfg.morePeaksFlag = 0;
                    }
#endif
                    if (aoaTestCfg.morePeaksFlag)
                    {
                        if (aoaTestCfg.numTxAntennas == 3)
                        {
                            aoaTestCfg.numCfarDetObj = 64 + test_modCalc(testCount, 20);
                            aoaTestCfg.numAoaOutObj = aoaTestCfg.numCfarDetObj; //no multiple peaks, and no min/max angles
                        }
                        else
                        {
                            aoaTestCfg.numCfarDetObj = 256 + test_modCalc(testCount, 22);
                            aoaTestCfg.numAoaOutObj = aoaTestCfg.numCfarDetObj; //no multiple peaks, and no min/max angles
                        }

                    }
                    /* add the extion velocity test*/
                    aoaTestCfg.extVelocityFlag = 0;   //ext velocity is disabled
                    if (aoaTestCfg.numTxAntennas > 1)
                    {
                        if ((!aoaTestCfg.minmaxAngleFlag) && (!aoaTestCfg.twoPeaksFlag))
                        {
                            aoaTestCfg.extVelocityFlag = 1;   //ext velocity is enabled
                            if ((aoaTestCfg.numTxAntennas == 2) && (aoaTestCfg.morePeaksFlag) && (aoaTestCfg.numDopplerBins == 4))
                            {
                                aoaTestCfg.extVelocityFlag = 0;
                            }
                        }
                    }
                    
                    System_printf("\nTest #%d  start\r\n", testCount);
                    
                    sprintf(featureName, "%s%d%s%d%s%d%s%d%s%d%s%d",
                        ":Tx", aoaTestCfg.numTxAntennas,
                        ":Rx", aoaTestCfg.numRxAntennas,
                        ":Chp", aoaTestCfg.numChirps,
                        ":D", aoaTestCfg.numDopplerBins,
                        ":R", aoaTestCfg.numRangeBins,
                        ":extVel", aoaTestCfg.extVelocityFlag);
                    
                    System_printf("Test feature : %s\n", featureName);

                    if (!aoaTestCfg.morePeaksFlag)
                    {
                        System_printf("CFAR Det Peaks: %d [", aoaTestCfg.numCfarDetObj);
                        for (idx = 0; idx < aoaTestCfg.numCfarDetObj - 1; idx++)
                        {
                            if (!aoaTestCfg.twoPeaksFlag)
                                System_printf("%d,%d,%d  ", aoaTestCfg.cfarDetObjRangeIdx[idx], aoaTestCfg.cfarDetObjDopplerRefIdx[idx], aoaTestCfg.aoaSignedAzimPeakIdxRef[idx]);
                            else
                                System_printf("%d,%d  ", aoaTestCfg.cfarDetObjRangeIdx[idx], aoaTestCfg.cfarDetObjDopplerRefIdx[idx]);
                        }
                        /* print the last one*/
                        if (!aoaTestCfg.twoPeaksFlag)
                            System_printf("%d,%d,%d]\n", aoaTestCfg.cfarDetObjRangeIdx[aoaTestCfg.numCfarDetObj - 1], aoaTestCfg.cfarDetObjDopplerRefIdx[aoaTestCfg.numCfarDetObj - 1], aoaTestCfg.aoaSignedAzimPeakIdxRef[aoaTestCfg.numCfarDetObj - 1]);
                        else
                            System_printf("%d,%d]\n", aoaTestCfg.cfarDetObjRangeIdx[aoaTestCfg.numCfarDetObj - 1], aoaTestCfg.cfarDetObjDopplerRefIdx[aoaTestCfg.numCfarDetObj - 1]);
                    }
                    else
                    {
                        System_printf("CFAR Det Peaks: %d \n", aoaTestCfg.numCfarDetObj);
                    }

                    /* generate 2D windowing coefficients */
                    pTestDopplerWindow = testDopplerWindow;
                    aoaCfg.res.hwaCfg.window = pTestDopplerWindow;
                    Test_window2DCoef_gen(aoaTestCfg.numChirps, aoaTestCfg.winType, pTestDopplerWindow);
                    /* generates the 1D fft output, radar cuba data */
                    Test_aoaDpu_cubaDataGen(&aoaTestCfg);
#if defined SUBSYS_MSS 
#if TEST_AOA_DEBUG
                    /* THIS IS FOR DEBUG */
                    Test_debug_cubadataverify(&aoaTestCfg);
#endif
#endif
#if defined SUBSYS_DSS
					//due to not enough memory for L2 on dsp, use L3 memory
                    if (aoaTestCfg.morePeaksFlag)
                    {
                        uint32_t tempSize;                                  
                        pAoaDetObj = (DPIF_PointCloudCartesian *)&testRadarCube[65536 +4];
                        tempSize = sizeof(DPIF_PointCloudCartesian) *  TEST_MAX_NUM_CFARDETOBJ_DPU;
                        tempSize = (tempSize + 3) / 4 * 4;
                        pCfarDetObjList = (DPIF_CFARDetList *)&testRadarCube[65536 + 4 + tempSize]; 

                    }
#endif
                    /* set up the AOA dpu configuration structure */
                    Test_setProfile(&aoaTestCfg);
                    /* clear the heat map memory */
                    memset(staticHeatmap, 0, sizeof(cmplx16ImRe_t)*TEST_MAX_NUM_RANGE_BIN * 8);
                    /* call aoa dpu configuration */
                    retVal = DPU_AoAProcHWA_config(aoaProcHandle, &aoaCfg);
                    if (retVal < 0)
                    {
                        if ((DPU_AOAPROCHWA_EEXCEEDHWAMEM) && (aoaTestCfg.numTxAntennas==3) && (aoaTestCfg.numDopplerBins==512))
                        {
                            /* not support 3x4, doppler is 512, not fit into 16k*/
                            System_printf("AOA DPU NOT SUPPORT, KNOWN ISSUE\n");
                            testCount++;
                            continue;
                        }
                        else
                        {
                            System_printf("AOA DPU failed to configure. Error %d.\n", retVal);
                            DebugP_assert(0);
                            return;
                        }
                    }

                    /* call aoa dpu process */
                    retVal = DPU_AoAProcHWA_process(aoaProcHandle, aoaTestCfg.numCfarDetObj, &outAoaProc);
                    if (retVal < 0)
                    {
                        System_printf("AOA DPU failed to run. Error %d.\n", retVal);
                        DebugP_assert(0);
                        return;
                    }

                    /* check the AOA DPU output */
                    
                    {
                        System_printf("Check the AOA output :  ");
                        Test_printResults(&aoaTestCfg);

                        /* run one more time for min/max angle checking */
                        if (aoaTestCfg.minmaxAngleFlag)
                        {
                            /* update test profile */
                            Test_updateProfile(&aoaTestCfg);

                            memset(staticHeatmap, 0, sizeof(cmplx16ImRe_t)*TEST_MAX_NUM_RANGE_BIN * 8);
                            retVal = DPU_AoAProcHWA_config(aoaProcHandle, &aoaCfg);
                            retVal = DPU_AoAProcHWA_process(aoaProcHandle, aoaTestCfg.numCfarDetObj, &outAoaProc);
                            System_printf("Check the AOA output with min/max angle sets :  ");
                            Test_printResults(&aoaTestCfg);       //check the results again with updated profiles

                        }

                        System_printf("Test #%d finished!\n\r", testCount);
                    }
                    
                    testCount++;
                } /*end of number of chirps */
            } /* end of range bin loop*/
        } /* end of doppler bin loop */
    }   /* end of antenna loop */
    
    /* add doppler size = 1024 test */
    for (ii = 1; ii < 3; ii++) /* antenna loop, test 1/2, 1/4 */
    {
        aoaTestCfg.numTxAntennas = numAntennas[ii][0];
        aoaTestCfg.numRxAntennas = numAntennas[ii][1];
        aoaTestCfg.numDopplerBins = 1024;
        //maxNumChirps = 16384 / aoaTestCfg.numTxAntennas / aoaTestCfg.numRxAntennas / 4;
        //if (maxNumChirps > aoaTestCfg.numDopplerBins)
            maxNumChirps = aoaTestCfg.numDopplerBins;
        for (mm = 0; mm < 3; mm++)
        {
           
            if (aoaTestCfg.numTxAntennas * aoaTestCfg.numRxAntennas == 2)
            {
                kk1 = test_modCalc(testCount, 4);    //1/2, maximum is 128 //max is 128
            }
            else if (aoaTestCfg.numTxAntennas * aoaTestCfg.numRxAntennas == 4)
            {
                kk1 = test_modCalc(testCount, 3);
            }
          //  else if (aoaTestCfg.numTxAntennas * aoaTestCfg.numRxAntennas == 8)
          //  {
           //     kk1 = test_modCalc(testCount, 2);
           // }
           // else
           //     kk1 = 0; //for tx*rx=12, max range bin size is 16
#if (defined (SOC_XWR68XX))
            if (kk1)
                kk1--;
#endif
            aoaTestCfg.numRangeBins = numRangeBin[kk1];
            aoaTestCfg.numChirps = maxNumChirps - ((testCount & 0x3) * 13);
            aoaTestCfg.twoPeaksFlag = 0;
            aoaTestCfg.heatMapFlag = true;
            aoaTestCfg.winType = testCount & 0x1;
            /* generate the cfar det obj list */
            pCfarDetObjList = &cfarDetObjList[0];
            pAoaDetObj = &aoaDetObj[0];
            Test_aoaDpu_cfarListGen(&aoaTestCfg);
            aoaTestCfg.minmaxAngleFlag = 0;
            aoaTestCfg.morePeaksFlag = 0;
            aoaTestCfg.extVelocityFlag = 0;    //only 1 tx,
            System_printf("\nTest #%d  start\r\n", testCount);
            sprintf(featureName, "%s%d%s%d%s%d%s%d%s%d%s%d",
                ":Tx", aoaTestCfg.numTxAntennas,
                ":Rx", aoaTestCfg.numRxAntennas,
                ":Chp", aoaTestCfg.numChirps,
                ":D", aoaTestCfg.numDopplerBins,
                ":R", aoaTestCfg.numRangeBins,
                ":extVel", aoaTestCfg.extVelocityFlag);
            System_printf("Test feature : %s\n", featureName);
            System_printf("CFAR Det Peaks: %d [", aoaTestCfg.numCfarDetObj);
            for (idx = 0; idx < aoaTestCfg.numCfarDetObj - 1; idx++)
            {
                if (!aoaTestCfg.twoPeaksFlag)
                    System_printf("%d,%d,%d  ", aoaTestCfg.cfarDetObjRangeIdx[idx], aoaTestCfg.cfarDetObjDopplerRefIdx[idx], aoaTestCfg.aoaSignedAzimPeakIdxRef[idx]);
                else
                    System_printf("%d,%d  ", aoaTestCfg.cfarDetObjRangeIdx[idx], aoaTestCfg.cfarDetObjDopplerRefIdx[idx]);
            }
            if (!aoaTestCfg.twoPeaksFlag)
                System_printf("%d,%d,%d]\n", aoaTestCfg.cfarDetObjRangeIdx[idx], aoaTestCfg.cfarDetObjDopplerRefIdx[idx], aoaTestCfg.aoaSignedAzimPeakIdxRef[idx]);
            else
                System_printf("%d,%d]\n", aoaTestCfg.cfarDetObjRangeIdx[idx], aoaTestCfg.cfarDetObjDopplerRefIdx[idx]);
            /* generate 2D windowing coefficients */
#if defined SUBSYS_MSS
            pTestDopplerWindow = testDopplerWindow;
            
#endif
#if defined SUBSYS_DSS
            pTestDopplerWindow = (int32_t *)&staticHeatmapRef[128 * 4];   
#endif
            aoaCfg.res.hwaCfg.window = pTestDopplerWindow;
            Test_window2DCoef_gen(aoaTestCfg.numChirps, aoaTestCfg.winType, pTestDopplerWindow);
            /* generates the 1D fft output, radar cuba data */
            Test_aoaDpu_cubaDataGen(&aoaTestCfg);
            /* set up the AOA dpu configuration structure */
            Test_setProfile(&aoaTestCfg);
#if TEST_AOA_DEBUG
            /* THIS IS FOR DEBUG */
           Test_debug_cubadataverify(&aoaTestCfg);
#endif
            /* clear the heat map memory */
            memset(staticHeatmap, 0, sizeof(cmplx16ImRe_t)*TEST_MAX_NUM_RANGE_BIN * 8);
            /* call aoa dpu configuration */
            retVal = DPU_AoAProcHWA_config(aoaProcHandle, &aoaCfg);
            if (retVal < 0)
            {
             //   System_printf("AOA DPU failed to configure. Error %d.\n", retVal);
                DebugP_assert(0);
                return;
            }
            retVal = DPU_AoAProcHWA_process(aoaProcHandle, aoaTestCfg.numCfarDetObj, &outAoaProc);
            if (retVal < 0)
            {
              //  System_printf("AOA DPU failed to run. Error %d.\n", retVal);
                DebugP_assert(0);
                return;
            }
            System_printf("Check the AOA output :  ");
            Test_printResults(&aoaTestCfg);
            testCount++;
        }
    }
    EDMA_close(edmaHandle);
    HWA_close(hwaHandle);
    retVal = DPU_AoAProcHWA_deinit(aoaProcHandle);
    if (retVal != 0)
    {
        System_printf("AOA DPU failed to deinit. Error %d.\n", retVal);
        DebugP_assert(0);
        return;
    }
    
#if  TEST_AOA_DEBUG
    System_printf("max cube size is %d, test id is %d\n", maxCubeSize, testCaseId);
#endif

    System_printf("----------------------------------------\n\n");
    if (finalResults == 1)
    {
        System_printf("All Tests PASSED!\n");
        MCPI_setFeatureTestResult("AOA_DPU", MCPI_TestResult_PASS);
    }
    else
    {
        System_printf("Test FAILED!\n");
        MCPI_setFeatureTestResult("AOA_DPU", MCPI_TestResult_FAIL);
    }

    System_printf("Test Finished\n");

    MCPI_setTestResult();

    /* Exit BIOS */
    BIOS_exit(0);

}

/**
*  @b Description
*  @n
*     test main function
*
*  @retval None
*
*/
int main (void)
{
    Task_Params taskParams;
    int32_t     errCode;
    SOC_Cfg     socCfg;

    /* Initialize test logger */
    MCPI_Initialize();

#ifdef SUBSYS_MSS
    /* Initialize the ESM: Dont clear errors as TI RTOS does it */
    ESM_init(0U);
#endif

    Cycleprofiler_init();

    /* Initialize the SOC confiugration: */
    memset ((void *)&socCfg, 0, sizeof(SOC_Cfg));

    /* Populate the SOC configuration: */
    socCfg.clockCfg = SOC_SysClock_INIT;

    /* Initialize the SOC Module: This is done as soon as the application is started
     * to ensure that the MPU is correctly configured. */
    socHandle = SOC_init (&socCfg, &errCode);
    if (socHandle == NULL)
    {
        printf ("Error: SOC Module Initialization failed [Error code %d]\n", errCode);
        DebugP_assert(0);
        return -1;
    }

    /* Initialize the Task Parameters. */
    Task_Params_init(&taskParams);
    taskParams.stackSize = 8*1024;
    Task_create(Test_task, &taskParams, NULL);

    /* Start BIOS */
    BIOS_start();
    
    return 0;
}


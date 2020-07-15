/**
 *   @file  aoaprocdsp_test_main.c
 *
 *   @brief
 *      Unit Test code for DSP aoa processing.
 *
 *  \par
 *  NOTE:
 *      (C) Copyright 2019 Texas Instruments, Inc.
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
#include <ti/datapath/dpc/dpu/aoaproc/aoaprocdsp.h>
#include <ti/utils/mathutils/mathutils.h>
#include <ti/utils/randomdatagenerator/gen_rand_data.h>


#define TEST_MAX_RADAR_CUBE_SIZE  (48 * 1024 * 4)  //numchirps*numRange*numRx complex value
#define TEST_MAX_NUM_DOPPLER_BINS 512


#if ( (defined (SOC_XWR68XX)) ||  (defined (SOC_XWR16XX)))
#define TEST_MAX_NUM_RANGE_BIN_HEATMAP  512
#endif

#if (defined (SOC_XWR18XX))
#define TEST_MAX_NUM_RANGE_BIN_HEATMAP  1024
#endif

#define TEST_AOA_FFTSIZE 64         /* 3D fft size */

#define TEST_MAX_NUM_CFARDETOBJ_DPU  6

#define TEST_MAX_NUM_CFARDETOBJ 5       //except for morepeak test, 3 tx 64, 2 tx 256
#if (defined (SOC_XWR16XX))
#define TEST_MAX_NUMVIRTUALANTE 8   /* maximum aoa number of receive antenna*/
#endif
#if ( (defined (SOC_XWR68XX)) ||  (defined (SOC_XWR18XX)))
#define TEST_MAX_NUMVIRTUALANTE 12   /* maximum aoa number of receive antenna*/
#endif


#define DPC_OBJDET_RADAR_CUBE_DATABUF_BYTE_ALIGNMENT       (sizeof(int16_t))
#define MAX_PEAKIDX_ERROR 4
#define MAX_ELEVANGLE_ERROR 0.076f
#define MAX_LOCATION_ERROR 0.01f
#define MAX_HEATMAP_ERROR 2
#define TWOPEAK_POSITIVE_THRESHOLD 0.60f
#define TWOPEAK_NEGTIVE_THRESHOLD 0.95f
#define CUBEDATA_PHASE_SHIFT 8.f
#define TEST_ANTENNA_LOOP 5   /* number of tx/rx combination */
#define TEST_DOPPLER_BIN_SIZE 6 
#define TEST_RANGE_BIN_SIZE 7   //tested range bin size from 16 to 512

#define TEST_AOA_DEBUG_RADARCUBEDATA 0 /*put 1 here if need to print out the radar cube data for debug*/

#define PI 3.141592653589793

/* radar cube data */
#pragma DATA_SECTION(testRadarCube, ".l3ram");
#pragma DATA_ALIGN(testRadarCube,DPC_OBJDET_RADAR_CUBE_DATABUF_BYTE_ALIGNMENT);
cmplx16ImRe_t testRadarCube[TEST_MAX_RADAR_CUBE_SIZE];       //msb is real, lsb 16 is imag

/* cfar det obj */
#pragma DATA_SECTION(cfarDetObjList, ".l2data");
#pragma DATA_ALIGN(cfarDetObjList,DPU_AOAPROCDSP_CFAR_DET_LIST_BYTE_ALIGNMENT);
DPIF_CFARDetList cfarDetObjList[TEST_MAX_NUM_CFARDETOBJ_DPU];

/* 2D FFT windowing coefficients */
#pragma DATA_SECTION(testDopplerWindow, ".l2data");
int32_t testDopplerWindow[TEST_MAX_NUM_DOPPLER_BINS];   //if -o3 is disabled, memory not fit
int32_t * pTestDopplerWindow; 

/* AOA DPU detected objects */
#pragma DATA_SECTION(aoaDetObj, ".l2data");
#pragma DATA_ALIGN(aoaDetObj,DPU_AOAPROCDSP_POINT_CLOUD_CARTESIAN_BYTE_ALIGNMENT);
DPIF_PointCloudCartesian aoaDetObj[TEST_MAX_NUM_CFARDETOBJ_DPU * 2];

 /* AOA DPU output side infor */
#pragma DATA_SECTION(aoaDetObjSideInfo, ".l2data");
#pragma DATA_ALIGN(aoaDetObjSideInfo, DPU_AOAPROCDSP_POINT_CLOUD_SIDE_INFO_BYTE_ALIGNMENT);
DPIF_PointCloudSideInfo aoaDetObjSideInfo[TEST_MAX_NUM_CFARDETOBJ_DPU * 2];

/* AOA DPU heat map outout */
#if (defined (SOC_XWR18XX))
#pragma DATA_SECTION(staticHeatmap, ".l3ram");
#endif
#if ( (defined (SOC_XWR68XX)) ||  (defined (SOC_XWR16XX)))
#pragma DATA_SECTION(staticHeatmap, ".l2data");
#endif
#pragma DATA_ALIGN(staticHeatmap,DPU_AOAPROCDSP_BUFFERS_BYTE_ALIGNMENT) ;  
cmplx16ImRe_t staticHeatmap[TEST_MAX_NUM_RANGE_BIN_HEATMAP * 8]; //maximum azimvirtual antenna is 2*4

/* heat map references */
#if (defined (SOC_XWR18XX))
#pragma DATA_SECTION(staticHeatmapRef, ".l3ram");
#endif
#if ( (defined (SOC_XWR68XX)) ||  (defined (SOC_XWR16XX)))
#pragma DATA_SECTION(staticHeatmapRef, ".l2data");
#endif
cmplx16ImRe_t staticHeatmapRef[TEST_MAX_NUM_RANGE_BIN_HEATMAP * 8]; //maximum azimvirtual antenna is 2*4

/* AOA DPU detected Azim peak index */
#pragma DATA_SECTION(aoaDetObjAzimIdx, ".l2data");
uint8_t aoaDetObjAzimIdx[TEST_MAX_NUM_CFARDETOBJ_DPU * 2];

/* AOA DPU detects Elev angle */
#pragma DATA_SECTION(aoaDetObjElevAngle, ".l2data");
#pragma DATA_ALIGN(aoaDetObjElevAngle, DPU_AOAPROCDSP_BUFFERS_BYTE_ALIGNMENT);
float aoaDetObjElevAngle[TEST_MAX_NUM_CFARDETOBJ_DPU * 2];

#pragma DATA_SECTION(aoapingPongBuf, ".l2data");
#pragma DATA_ALIGN(aoapingPongBuf, DPU_AOAPROCDSP_BUFFERS_BYTE_ALIGNMENT);
cmplx16ImRe_t aoapingPongBuf[TEST_MAX_NUM_DOPPLER_BINS * 2];

#pragma DATA_SECTION(aoaangleTwiddle32x32, ".l2data");
#pragma DATA_ALIGN(aoaangleTwiddle32x32, DPU_AOAPROCDSP_BUFFERS_BYTE_ALIGNMENT);
cmplx32ReIm_t aoaangleTwiddle32x32[DPU_AOAPROCDSP_NUM_ANGLE_BINS];

#pragma DATA_SECTION(aoatwiddle32x32, ".l2data");
#pragma DATA_ALIGN(aoatwiddle32x32, DPU_AOAPROCDSP_BUFFERS_BYTE_ALIGNMENT);
cmplx32ReIm_t aoatwiddle32x32[TEST_MAX_NUM_DOPPLER_BINS];

#pragma DATA_SECTION(aoascratch1Buff, ".l2data");
#pragma DATA_ALIGN(aoascratch1Buff, DPU_AOAPROCDSP_BUFFERS_BYTE_ALIGNMENT);
cmplx32ReIm_t aoascratch1Buff[TEST_MAX_NUM_DOPPLER_BINS];

#pragma DATA_SECTION(aoascratch2Buff, ".l2data");
#pragma DATA_ALIGN(aoascratch2Buff, DPU_AOAPROCDSP_BUFFERS_BYTE_ALIGNMENT);
cmplx32ReIm_t aoascratch2Buff[TEST_MAX_NUM_DOPPLER_BINS];

#pragma DATA_SECTION(aoaangleFftIn, ".l2data");
#pragma DATA_ALIGN(aoaangleFftIn, DPU_AOAPROCDSP_BUFFERS_BYTE_ALIGNMENT);
cmplx32ReIm_t aoaangleFftIn[DPU_AOAPROCDSP_NUM_ANGLE_BINS];

#pragma DATA_SECTION(aoaelevationFftOut, ".l2data");
#pragma DATA_ALIGN(aoaelevationFftOut, DPU_AOAPROCDSP_BUFFERS_BYTE_ALIGNMENT);
cmplx32ReIm_t aoaelevationFftOut[DPU_AOAPROCDSP_NUM_ANGLE_BINS];

/* EDMA resource partitioning */
#define EDMA_SHADOW_LNK_PARAM_BASE_ID                      EDMA_NUM_DMA_CHANNELS
#define DPU_AOA_PROC_EDMAPING_CH                           EDMA_TPCC0_REQ_FREE_4
#define DPU_AOA_PROC_EDMAPING_SHADOW                       (EDMA_SHADOW_LNK_PARAM_BASE_ID + 4U)
#define DPU_AOA_PROC_EDMAPING_EVENT_QUE                    0

#define DPU_AOA_PROC_EDMAPONG_CH                           EDMA_TPCC0_REQ_FREE_5
#define DPU_AOA_PROC_EDMAPONG_SHADOW                       (EDMA_SHADOW_LNK_PARAM_BASE_ID + 5U)
#define DPU_AOA_PROC_EDMAPONG_EVENT_QUE                    0



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
    int16_t minAzim;          /*!< @brief minimun azim index in the test */ 
    int16_t maxAzim;          /*!< @brief maximum azim index in the test */
    int16_t minElev, maxElev; /*!< @brief minimum/maximum elev index in the test */

    uint8_t checkCfarDetObjFlag[TEST_MAX_NUM_CFARDETOBJ];   /*!< @brief The cfar det object is detected or 
                                                            not detected in aoa dpu*/

    uint8_t  aoaNum3DfftPeaks[TEST_MAX_NUM_CFARDETOBJ];   /*!< @brief number of azim peaks for every cfar det objects */

   /*!< @brief azim peak index reference for every cfar det objects */
    int16_t  aoaSignedAzimPeakIdxRef[TEST_MAX_NUM_CFARDETOBJ_DPU * 2];
    /*!< @brief elev peak index reference for every cfar det objects */
    int16_t  aoaSignedElevPeakIdxRef[TEST_MAX_NUM_CFARDETOBJ_DPU * 2];

    uint8_t winType;   /*!< @brief if 0, rectange windowing, if 1, hanning windowing */
    uint8_t bpmFlag;  /*!< @brief for tx=2 only, if 0, no bpm, if 1 bpm */

    uint8_t extVelocityFlag;  /*!<  @brief extended velocity flag, 0- extended velocity is disabled, 1 - enabled*/
} aoaProcDpuTestConfig_t;

SOC_Handle  socHandle;
EDMA_Handle edmaHandle;


MCPI_LOGBUF_INIT(128);

uint8_t finalResults;

DPU_AoAProcDSP_Config        aoaCfg;
DPU_AoAProcDSP_Handle        aoaProcHandle;
DPU_AoAProc_FovAoaCfg        aoaDynFovCfg;
DPU_AoAProc_compRxChannelBiasCfg aoaDynOutCompRxCfg;
DPU_AoAProc_MultiObjBeamFormingCfg aoaDynBmCfg;
DPU_AoAProcDSP_OutParams outAoaProc;
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
*    Initialize the EDMA.
*
*  @retval None
*
*/
void aoaProc_test_Edmainit()
{
    uint8_t             edmaNumInstances;
    uint8_t             inst;
    EDMA_instanceInfo_t edmaInstanceInfo;
    EDMA_errorConfig_t  errorConfig;
    int32_t             errorCode;
    EDMA_errorInfo_t  EDMA_errorInfo;
    EDMA_transferControllerErrorInfo_t EDMA_transferControllerErrorInfo;



    /* Initialize the EDMA */
    edmaNumInstances = EDMA_getNumInstances();
    for (inst = 0; inst < edmaNumInstances; inst++)
    {
        errorCode = EDMA_init(inst);
        if (errorCode != EDMA_NO_ERROR)
        {
            System_printf("Debug: EDMA instance %d initialization returned error %d\n", errorCode);
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
    errorCode = EDMA_configErrorMonitoring(edmaHandle, &errorConfig);
    if (errorCode != EDMA_NO_ERROR)
    {
        System_printf("Error: EDMA_configErrorMonitoring() failed with errorCode = %d\n", errorCode);
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
    int32_t errorCode = 0;

    aoaProcHandle = DPU_AoAProcDSP_init(&errorCode);
    if (aoaProcHandle == NULL)
    {
        System_printf("AOA DPU failed to initialize. Error %d.\n", errorCode);
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
    DPU_AoAProcDSP_HW_Resources   * resPtr;
    uint16_t ii;
    float realTemp, imagTemp;

    memset(&aoaCfg, 0, sizeof(aoaCfg));

    resPtr = &aoaCfg.res;

    resPtr->edmaHandle = edmaHandle;
    
    resPtr->edmaPing.channel       = DPU_AOA_PROC_EDMAPING_CH;
    resPtr->edmaPing.channelShadow = DPU_AOA_PROC_EDMAPING_SHADOW;
    resPtr->edmaPing.eventQueue    = DPU_AOA_PROC_EDMAPING_EVENT_QUE;

    resPtr->edmaPong.channel       = DPU_AOA_PROC_EDMAPONG_CH;
    resPtr->edmaPong.channelShadow = DPU_AOA_PROC_EDMAPONG_SHADOW;
    resPtr->edmaPong.eventQueue    = DPU_AOA_PROC_EDMAPONG_EVENT_QUE;

    resPtr->radarCube.datafmt = DPIF_RADARCUBE_FORMAT_1;
    resPtr->radarCube.data = testRadarCube;


    /* aoa output buffer set*/
    aoaCfg.res.detObjOutSideInfo = aoaDetObjSideInfo;
    aoaCfg.res.detObjOutMaxSize = TEST_MAX_NUM_CFARDETOBJ_DPU;
    aoaCfg.res.azimuthStaticHeatMap = staticHeatmap;
    aoaCfg.res.detObj2dAzimIdx = aoaDetObjAzimIdx;
    aoaCfg.res.detObjElevationAngle = aoaDetObjElevAngle;
    
    /*internal buffers required by DPU*/
    aoaCfg.res.pingPongBuf       = aoapingPongBuf      ;
    aoaCfg.res.angleTwiddle32x32 = aoaangleTwiddle32x32;
    aoaCfg.res.twiddle32x32      = aoatwiddle32x32     ;
    aoaCfg.res.scratch1Buff      = aoascratch1Buff     ;
    aoaCfg.res.scratch2Buff      = aoascratch2Buff       ;
    aoaCfg.res.angleFftIn        = aoaangleFftIn       ;
    aoaCfg.res.elevationFftOut   = aoaelevationFftOut  ;

    /* sizes */
    aoaCfg.res.windowSize          = sizeof(int32_t) * TEST_MAX_NUM_DOPPLER_BINS;
    aoaCfg.res.pingPongSize        = 2 * sizeof(cmplx16ImRe_t) * TEST_MAX_NUM_DOPPLER_BINS;
    aoaCfg.res.angleTwiddleSize    = sizeof(cmplx32ReIm_t) * DPU_AOAPROCDSP_NUM_ANGLE_BINS;
    aoaCfg.res.twiddleSize         = sizeof(cmplx32ReIm_t) * TEST_MAX_NUM_DOPPLER_BINS;
    aoaCfg.res.scratch1Size        = sizeof(cmplx32ReIm_t) * TEST_MAX_NUM_DOPPLER_BINS;
    aoaCfg.res.scratch2Size        = sizeof(cmplx32ReIm_t) * TEST_MAX_NUM_DOPPLER_BINS;
    aoaCfg.res.angleFftInSize      = sizeof(cmplx32ReIm_t) * DPU_AOAPROCDSP_NUM_ANGLE_BINS;
    aoaCfg.res.elevationFftOutSize = sizeof(cmplx32ReIm_t) * DPU_AOAPROCDSP_NUM_ANGLE_BINS;

    aoaCfg.dynCfg.fovAoaCfg = &aoaDynFovCfg;

    aoaDynOutCompRxCfg.rangeBias = 0.1;   
    
    realTemp = cosf(CUBEDATA_PHASE_SHIFT / 180.f * PI);
    realTemp = realTemp * 32767;
    imagTemp = sin(CUBEDATA_PHASE_SHIFT / 180.f * PI);
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
    aoaCfg.dynCfg.staticClutterCfg.isEnabled = false;

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
    DPU_AoAProcDSP_StaticConfig * staticCfgPtr;
    uint16_t ii;
   
    aoaCfg.res.cfarRngDopSnrList = cfarDetObjList;
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

    /* hard code range step, and dopplerStep*/
    staticCfgPtr->rangeStep = 1.0f;
    staticCfgPtr->dopplerStep = 1.0f;
    aoaCfg.res.detObjOut = aoaDetObj;
    
    //hardcode BPM configuration for now
    staticCfgPtr->isBpmEnabled = testConfig->bpmFlag;

    aoaCfg.res.radarCube.dataSize = testConfig->numTxAntennas * testConfig->numRangeBins * testConfig->numDopplerBins * testConfig->numRxAntennas * 4;
    if (testConfig->numTxAntennas < 3)
        aoaCfg.res.azimuthStaticHeatMapSize = testConfig->numRangeBins * testConfig->numRxAntennas * testConfig->numTxAntennas;
    else
        aoaCfg.res.azimuthStaticHeatMapSize = testConfig->numRangeBins * testConfig->numRxAntennas * 2;

    {
        for (ii = 0; ii < testConfig->numCfarDetObj; ii++)
        {
            cfarDetObjList[ii].rangeIdx = testConfig->cfarDetObjRangeIdx[ii];
            cfarDetObjList[ii].dopplerIdx = testConfig->cfarDetObjdopplerIdx[ii];
            cfarDetObjList[ii].snr = 10;
            cfarDetObjList[ii].noise = 10;
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

    /* extended max velocity */
    extMaxVelCfg.enabled = testConfig->extVelocityFlag;
    
}

/**
*  @b Description
*  @n
*   If test is for min/max azim/elev angles, update the azim/elev references and AOA DPU configurations
*   by setting the min/max azim/elev angles to mim/max azim/elev used to generate radar cube data.
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
*   Generates the radar cube data based on test configuration per test.
*
*  @retval None
*
*/
void Test_aoaDpu_cubeDataGen(aoaProcDpuTestConfig_t * testConfig)
{
    uint32_t ii, jj, kk, mm;
    uint32_t radarCubeIdx;
    float dopplerIncr, dopplerAngle;
    float real = 0.f;
    float imag = 0.f;
    float noiseRe, noiseIm;
    float realTemp, imagTemp;

    float realBmpTemp[2] = { 0.f, 0.f };
    float imagBmpTemp[2] = { 0.f, 0.f };

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
    cmplx32ImRe_t  heatmapTemp;
    cmplx32ImRe_t  heatmapBmpTemp[2];
    
    int16_t dopplerIdx;

    amplitude = 500.f;
    noiseScale = 160.f;

    memset(testRadarCube, 0, sizeof(cmplx16ImRe_t) * testConfig->numRangeBins * testConfig->numDopplerBins * testConfig->numTxAntennas * testConfig->numRxAntennas);
    /* save the heatmap reference */
    if (testConfig->numTxAntennas == 3)
        numHeatmapAzimAnt = 2 * testConfig->numRxAntennas;
    else
        numHeatmapAzimAnt = testConfig->numTxAntennas * testConfig->numRxAntennas;
    memset(staticHeatmapRef, 0, sizeof(cmplx16ImRe_t) * testConfig->numRangeBins * numHeatmapAzimAnt);
    
    /* generate the peak first */
    count = 0;
    if (!testConfig->bpmFlag)
    {
        for (mm = 0; mm < testConfig->numCfarDetObj; mm++)
        {

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
                if (testConfig->numTxAntennas == 3)
                {
                    aoaElevIdx1 = testConfig->aoaSignedElevPeakIdxRef[count];
                }
                count++;
                aoaAzimIdx2 = 0;
                aoaElevIdx2 = 0;
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

            for (ii = 0; ii < testConfig->numChirps; ii++) //chirp loop
            {
                for (txAntIdx = 0; txAntIdx < testConfig->numTxAntennas; txAntIdx++) //for tx antenna loop
                {
                    for (jj = 0; jj < testConfig->numRxAntennas; jj++) //rx antenna loop
                    {

                        dopplerIncr = 2.f * PI * dopplerIdx / testConfig->numDopplerBins / testConfig->numTxAntennas;
                        dopplerAngle = (ii * testConfig->numTxAntennas + txAntIdx) * dopplerIncr;  //increase every chirp
                        /* add the aoa phase */
                        if (txAntIdx < 2)   //for tx 0, 1, the delay is 0 1 2 3 4 5 6 7
                        {
                            aoaAzimAngle1 = 2.f * PI * (txAntIdx * testConfig->numRxAntennas + jj) * (float)aoaAzimIdx1 / (float)TEST_AOA_FFTSIZE;
                            aoaAzimAngle2 = 0.f;
                            if ((testConfig->aoaNum3DfftPeaks[mm] == 2))
                                aoaAzimAngle2 = 2.f * PI * (txAntIdx * testConfig->numRxAntennas + jj)  * (float)aoaAzimIdx2 / (float)TEST_AOA_FFTSIZE;

                            /* for tx 0, 1, no elev delay */
                            aoaElevAngle1 = 0.f;
                            aoaElevAngle2 = 0.f;
                        }
                        else //for tx == 2 numTx=3, azim delay is [ 2 3 4 5]
                        {
                            aoaAzimAngle1 = 2.f * PI * (2 + jj) * (float)aoaAzimIdx1 / (float)TEST_AOA_FFTSIZE;
                            aoaAzimAngle2 = 0.f;
                            if (testConfig->aoaNum3DfftPeaks[mm] == 2)
                                aoaAzimAngle2 = 2.f * PI * (2 + jj)  * (float)aoaAzimIdx2 / (float)TEST_AOA_FFTSIZE;

                            aoaElevAngle1 = -2.f * PI * (float)aoaElevIdx1 / (float)TEST_AOA_FFTSIZE;
                            aoaElevAngle2 = 0.f;
                            if (testConfig->aoaNum3DfftPeaks[mm] == 2)
                                aoaElevAngle2 = -2.f * PI* (float)aoaElevIdx2 / (float)TEST_AOA_FFTSIZE;
                        }

                        real = amplitude * cosf(dopplerAngle + aoaAzimAngle1 + aoaElevAngle1);
                        imag = amplitude * sinf(dopplerAngle + aoaAzimAngle1 + aoaElevAngle1);

                        if (testConfig->aoaNum3DfftPeaks[mm] == 2)
                        {
                            real += (amplitude * 0.85f * cosf(dopplerAngle + aoaAzimAngle2 + aoaElevAngle2));
                            imag += (amplitude * 0.85f * sinf(dopplerAngle + aoaAzimAngle2 + aoaElevAngle2));
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

                        if (CUBEDATA_PHASE_SHIFT)
                        {
                            real = realTemp * cosf(CUBEDATA_PHASE_SHIFT / 180.f * PI) - imagTemp * sinf(CUBEDATA_PHASE_SHIFT / 180.f * PI);
                            imag = realTemp * sinf(CUBEDATA_PHASE_SHIFT / 180.f * PI) + imagTemp * cosf(CUBEDATA_PHASE_SHIFT / 180.f * PI);
                        }


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
                            tempvalue = (int32_t)MATHUTILS_ROUND_FLOAT(realTemp);     //with no phase shift
                                                                                      //MATHUTILS_SATURATE16(winTempValue);
                            heatmapTemp.real += (int16_t)tempvalue;
                            tempvalue = (int32_t)MATHUTILS_ROUND_FLOAT(imagTemp);
                            //MATHUTILS_SATURATE16(winTempValue);
                            heatmapTemp.imag += (int16_t)tempvalue;
                        }
                    }/* end of chirp sum*/
#if ((defined (SOC_XWR68XX)) ||  (defined (SOC_XWR16XX)))
                    if (testConfig->heatMapFlag)  //for 68xx, only generate the heapmap ref if heatmapflag is true
                    {
#endif
                        if ((txAntIdx == 0) || (txAntIdx == 1))
                        {
                            staticHeatmapRef[kk * numHeatmapAzimAnt + txAntIdx * testConfig->numRxAntennas + jj].real = (int16_t)(heatmapTemp.real / testConfig->numChirps);
                            staticHeatmapRef[kk * numHeatmapAzimAnt + txAntIdx * testConfig->numRxAntennas + jj].imag = (int16_t)(heatmapTemp.imag / testConfig->numChirps);
                        }
#if ((defined (SOC_XWR68XX)) ||  (defined (SOC_XWR16XX)))
                    }
#endif
                }
            }
        }


    }
    else   //bpm
    {
        for (mm = 0; mm < testConfig->numCfarDetObj; mm++)
        {
           rangeIdx = testConfig->cfarDetObjRangeIdx[mm];
           dopplerIdx = testConfig->cfarDetObjDopplerRefIdx[mm];
           aoaAzimIdx1 = testConfig->aoaSignedAzimPeakIdxRef[count];      //signed 
           aoaAzimIdx2 = 0; 
           count++;
           if (testConfig->aoaNum3DfftPeaks[mm] == 2)
           {
               aoaAzimIdx2 = testConfig->aoaSignedAzimPeakIdxRef[count];
               count++;
           }
           dopplerIncr = 2.f * PI * dopplerIdx / testConfig->numDopplerBins / testConfig->numTxAntennas;
           for (ii = 0; ii < testConfig->numChirps * testConfig->numTxAntennas; ii++) //chirp loop
           {
               dopplerAngle = ii * dopplerIncr;  //increase every chirp

               for (jj = 0; jj < testConfig->numRxAntennas; jj++) //rx antenna loop
               {
                   for (txAntIdx = 0; txAntIdx < testConfig->numTxAntennas; txAntIdx++) //for tx antenna loop
                   {
                  
                       //for tx 0, 1, the delay is 0 1 2 3 4 5 6 7
                       aoaAzimAngle1 = 2.f * PI * (txAntIdx * testConfig->numRxAntennas + jj) * (float)aoaAzimIdx1 / (float)TEST_AOA_FFTSIZE;
                       aoaAzimAngle2 = 0.f;
                       if ((testConfig->aoaNum3DfftPeaks[mm] == 2))
                           aoaAzimAngle2 = 2.f * PI * (txAntIdx * testConfig->numRxAntennas + jj)  * (float)aoaAzimIdx2 / (float)TEST_AOA_FFTSIZE;

                       /* for tx 0, 1, no elev delay */
                       aoaElevAngle1 = 0.f;
                       aoaElevAngle2 = 0.f;

                       if (txAntIdx == 0)
                       {
                           real = amplitude * cosf(dopplerAngle + aoaAzimAngle1 + aoaElevAngle1);
                           imag = amplitude * sinf(dopplerAngle + aoaAzimAngle1 + aoaElevAngle1);
                       }
                       else
                       {
                           if ((ii & 0x1) == 0)
                           {
                               real += amplitude * cosf(dopplerAngle + aoaAzimAngle1 + aoaElevAngle1);
                               imag += amplitude * sinf(dopplerAngle + aoaAzimAngle1 + aoaElevAngle1);
                           }
                           else
                           {
                               real -= amplitude * cosf(dopplerAngle + aoaAzimAngle1 + aoaElevAngle1);
                               imag -= amplitude * sinf(dopplerAngle + aoaAzimAngle1 + aoaElevAngle1);
                           }
                       }
                      
                   }
                   radarCubeIdx = (ii & 0x1) * testConfig->numChirps * testConfig->numRxAntennas *  testConfig->numRangeBins;
                   radarCubeIdx += ((ii / 2) * testConfig->numRxAntennas * testConfig->numRangeBins);
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

        /* add the noise, and save the heatmap reference */
        for (jj = 0; jj < testConfig->numRxAntennas; jj++) //rx antenna loop
        { 
            for (kk = 0; kk < testConfig->numRangeBins; kk++) // range bin
            {
                heatmapBmpTemp[0].real = 0;
                heatmapBmpTemp[0].imag = 0;
                heatmapBmpTemp[1].real = 0;
                heatmapBmpTemp[1].imag = 0;
                
                for (ii = 0; ii < testConfig->numChirps; ii++) //chirp loop
                {

                    for (txAntIdx = 0; txAntIdx < testConfig->numTxAntennas; txAntIdx++) //even or odd chirp
                    {
                        
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

                        /* before adding a phase shift*/
                        realBmpTemp[txAntIdx] = real;
                        imagBmpTemp[txAntIdx] = imag;

                        if (CUBEDATA_PHASE_SHIFT)
                        {
                            real = realBmpTemp[txAntIdx] * cosf(CUBEDATA_PHASE_SHIFT / 180.f * PI) - imagBmpTemp[txAntIdx] * sinf(CUBEDATA_PHASE_SHIFT / 180.f * PI);
                            imag = realBmpTemp[txAntIdx] * sinf(CUBEDATA_PHASE_SHIFT / 180.f * PI) + imagBmpTemp[txAntIdx] * cosf(CUBEDATA_PHASE_SHIFT / 180.f * PI);
                        }


                        tempvalue = (int32_t)MATHUTILS_ROUND_FLOAT(real);
                        MATHUTILS_SATURATE16(tempvalue);
                        testRadarCube[radarCubeIdx].real = (int16_t)tempvalue;
                        tempvalue = (int32_t)MATHUTILS_ROUND_FLOAT(imag);
                        MATHUTILS_SATURATE16(tempvalue);
                        testRadarCube[radarCubeIdx].imag = (int16_t)tempvalue;

                       
                    }/*end of even, odd chirp */

                    realTemp = realBmpTemp[0] + realBmpTemp[1];
                    imagTemp = imagBmpTemp[0] + imagBmpTemp[1];
                    realTemp = realTemp / 2;
                    imagTemp = imagTemp / 2;
                    tempvalue = (int32_t)MATHUTILS_ROUND_FLOAT(realTemp);     //with no phase shift
                    heatmapBmpTemp[0].real += (int16_t)tempvalue;
                    tempvalue = (int32_t)MATHUTILS_ROUND_FLOAT(imagTemp);
                    //MATHUTILS_SATURATE16(winTempValue);
                    heatmapBmpTemp[0].imag += (int16_t)tempvalue;
                
                    realTemp = realBmpTemp[0] - realBmpTemp[1];
                    imagTemp = imagBmpTemp[0] - imagBmpTemp[1];
                    realTemp = realTemp / 2;
                    imagTemp = imagTemp / 2;
                    tempvalue = (int32_t)MATHUTILS_ROUND_FLOAT(realTemp);     //with no phase shift
                    heatmapBmpTemp[1].real += (int16_t)tempvalue;
                    tempvalue = (int32_t)MATHUTILS_ROUND_FLOAT(imagTemp);
                    //MATHUTILS_SATURATE16(winTempValue);
                    heatmapBmpTemp[1].imag += (int16_t)tempvalue;
                    
                }//end of chirp

                staticHeatmapRef[kk * numHeatmapAzimAnt + 0 * testConfig->numRxAntennas + jj].real = (int16_t)(heatmapBmpTemp[0].real / testConfig->numChirps);
                staticHeatmapRef[kk * numHeatmapAzimAnt + 0 * testConfig->numRxAntennas + jj].imag = (int16_t)(heatmapBmpTemp[0].imag / testConfig->numChirps);
                staticHeatmapRef[kk * numHeatmapAzimAnt + 1 * testConfig->numRxAntennas + jj].real = (int16_t)(heatmapBmpTemp[1].real / testConfig->numChirps);
                staticHeatmapRef[kk * numHeatmapAzimAnt + 1 * testConfig->numRxAntennas + jj].imag = (int16_t)(heatmapBmpTemp[1].imag / testConfig->numChirps);

            }
        }
    }

#if TEST_AOA_DEBUG_RADARCUBEDATA
    if (testCount == 82) /*put here the test case number to be debugged*/
    {
    for (kk = 0; kk < testConfig->numRxAntennas; kk++)    //all rx antenna
    {
        for (jj = 0; jj < testConfig->numTxAntennas; jj++) //all tx antenna
        {
            for (mm = 0; mm < testConfig->numChirps; mm++) //all chirps
            {
                radarCubeIdx = jj * testConfig->numChirps * testConfig->numRxAntennas *  testConfig->numRangeBins;
                radarCubeIdx += (mm * testConfig->numRxAntennas * testConfig->numRangeBins);
                radarCubeIdx += (kk * testConfig->numRangeBins);
                radarCubeIdx += 15; //put here the rangeIdx of the object to be debugged.
                ///fftDataInBuf[mm] = testRadarCube[radarCubeIdx];
                printf("%d, %d,",testRadarCube[radarCubeIdx].real,testRadarCube[radarCubeIdx].imag);
            }
            printf("\n");
        }
    }
    }
#endif
}/*Test_aoaDpu_cubeDataGen*/

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
    
    int16_t dopplerIdx;
    int16_t elevIdxRef;
    float range;
    
    
    /* check the aoa output object number */
    if (testConfig->twoPeaksFlag == 2)
    {
        if ((outAoaProc.numAoADetectedPoints * 2)!= testConfig->numAoaOutObj)
        {
            System_printf("\nAOA output number is : aoaOut=%d, ref=%d\n", outAoaProc.numAoADetectedPoints, testConfig->numAoaOutObj);
            finalResults = 0;
            testPass = 0;
            
        }
    }
    else
    {
        if (outAoaProc.numAoADetectedPoints != testConfig->numAoaOutObj)
        {
            System_printf("\nAOA output number is : aoaOut=%d, ref=%d\n", outAoaProc.numAoADetectedPoints, testConfig->numAoaOutObj);
            finalResults = 0;
            testPass = 0;
            
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

            
            {
                azimSignedPeakIdxRef = testConfig->aoaSignedAzimPeakIdxRef[refCount];
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
                
                {
                    elevIdxRef = testConfig->aoaSignedElevPeakIdxRef[refCount];
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
           
            {
                rangeIdx = testConfig->cfarDetObjRangeIdx[ii];
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


            if (testConfig->aoaNum3DfftPeaks[ii] == 2) 
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

        if (!testConfig->checkCfarDetObjFlag[ii])
        {
            continue;
        }
        
        {
            dopplerIdx = testConfig->cfarDetObjDopplerRefIdx[ii];
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
        if ((testConfig->aoaNum3DfftPeaks[ii] == 2) && (testConfig->twoPeaksFlag == 1))
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
*     test main task  : Generate the radar cube data based on the test configuration, and generate the cfar detected
*                       object list. The cube data and the detected object list are sent to AOA dpu. The DPU outputs
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
    
    uint32_t numDopplerBin[TEST_DOPPLER_BIN_SIZE] = {16, 32, 64, 128, 256, 512};
    uint32_t numRangeBin[TEST_RANGE_BIN_SIZE] = { 16, 32, 64, 128, 256, 512, 1024 };
    uint32_t numTests;
    int32_t   retVal;
    uint16_t dopplerLoopStep;
    uint16_t numRangeBinSize;
    uint16_t idx;
    uint32_t maxNumChirps,mm;
    
    finalResults = 1;
    System_printf("...... Initialization ...... \n");

    /* edma, dpu inialization */
    aoaProc_test_Edmainit();
    aoaProc_test_dpuInit();

    /* aoa dpu config*/
    aoaProc_test_dpuConfig();
    
    System_printf("aoa Proc DPU Test start ...... \n");
    
    /*for tx/rx1,1, only run 3 doppler size, each with 1 range bin size */
    numTests = 9; 
    /* antenne combination * doppler size, 2 range bin size, for each doppler bin size, chirp even, odd, maximum */
#if (defined (SOC_XWR16XX))
    numTests += (TEST_ANTENNA_LOOP - 2) * TEST_DOPPLER_BIN_SIZE * 2 * 3;
#endif
#if ( (defined (SOC_XWR68XX)) ||  (defined (SOC_XWR18XX)))    
    numTests += (TEST_ANTENNA_LOOP - 1) * TEST_DOPPLER_BIN_SIZE * 2 * 3;
#endif
   
    printf("\n...... %d Tests to be run .......\n\n", numTests);

    testCount = 0;
#if (defined (SOC_XWR16XX))
    for (ii = 0; ii < TEST_ANTENNA_LOOP - 1; ii++) /* antenna loop, for 16xx, not support tx=3 */
    {
#endif
#if ( (defined (SOC_XWR68XX)) ||  (defined (SOC_XWR18XX)))
     for (ii = 0; ii < TEST_ANTENNA_LOOP; ii++) /* antenna loop */
     {
#endif
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
                        if (aoaTestCfg.numDopplerBins <= 16)
                        {
                            kk1 = testCount + kk * 5;
                            kk1 = test_modCalc(kk1, TEST_RANGE_BIN_SIZE); 
                        }
                        else
                        {
                            kk1 = testCount + kk * ((TEST_RANGE_BIN_SIZE + 1 - jj) / 2);
                            kk1 = test_modCalc(kk1, (TEST_RANGE_BIN_SIZE + 1 - jj));  
                        }
                    }
                    else 
                    {
                        kk1 = testCount + kk * ((TEST_RANGE_BIN_SIZE - 1 - jj) / 2);
                        kk1 = test_modCalc(kk1, (TEST_RANGE_BIN_SIZE - 1 - jj));  //maximum range size is 256,... 
                    }
                    aoaTestCfg.numRangeBins = numRangeBin[kk1];

                    /* set up the number of chirps <= doppler bin size*/
                    aoaTestCfg.numChirps = aoaTestCfg.numDopplerBins;
                    
                   if (aoaTestCfg.numDopplerBins == 16)
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
                    aoaTestCfg.numChirps = aoaTestCfg.numChirps / 4 * 4; //must be multiple of 4

                    /* multiple peaks */
                    aoaTestCfg.twoPeaksFlag = 0;
                    if (aoaTestCfg.numTxAntennas * aoaTestCfg.numRxAntennas > 2)
                    {
                        if ((testCount & 0x7) == 0)
                            aoaTestCfg.twoPeaksFlag = 1;
                        /* add several tests for two peaks, but set threshold high, so only sigle peak is detected */
                        if ((testCount == 56) || (testCount == 104)  || (testCount == 120)|| (testCount == 128))
                        {
                            aoaTestCfg.twoPeaksFlag = 2;
                        }
                    }
                   
                    /* heat map */
                    if (aoaTestCfg.numTxAntennas * aoaTestCfg.numRxAntennas == 1)
                        aoaTestCfg.heatMapFlag = false;
                    else
                        aoaTestCfg.heatMapFlag = true;
                    
#if (defined (SOC_XWR68XX))
                    if (((aoaTestCfg.numTxAntennas == 3)  || (aoaTestCfg.numTxAntennas * aoaTestCfg.numRxAntennas ==8)) & (aoaTestCfg.numRangeBins == 1024))    //due to memory, disable the heap map
                    {
                        aoaTestCfg.heatMapFlag = false;
                    }
                    
#endif
                    /* generate the windowing coefficients */
                    aoaTestCfg.winType = 0;    
                    
                    /* generate the cfar det obj list */
                    Test_aoaDpu_cfarListGen(&aoaTestCfg);

                    /* check the min and max angle */
                    aoaTestCfg.minmaxAngleFlag = 0;
                    if ((aoaTestCfg.numCfarDetObj >= 4) && ((testCount & 0x3) <= 1) && (aoaTestCfg.numRxAntennas != 1))
                    {
                        aoaTestCfg.minmaxAngleFlag = aoaTestCfg.numCfarDetObj - 3;
                    }
                    
                    aoaTestCfg.bpmFlag = 0;
                    if (aoaTestCfg.numTxAntennas == 2)
                    {
                        aoaTestCfg.bpmFlag = testCount & 0x1;
                    }

                    /* add the extended velocity test*/
                    aoaTestCfg.extVelocityFlag = 0;   //ext velocity is disabled
                    if (aoaTestCfg.numTxAntennas > 1)
                    {
                        if ((!aoaTestCfg.minmaxAngleFlag) && (!aoaTestCfg.twoPeaksFlag) && (!aoaTestCfg.bpmFlag))
                        {
                            aoaTestCfg.extVelocityFlag = 1;   //ext velocity is enabled
                            if ((aoaTestCfg.numTxAntennas == 2) && (aoaTestCfg.numDopplerBins == 4))
                            {
                                aoaTestCfg.extVelocityFlag = 0;
                            }
                        }
                    }

                    System_printf("\nTest #%d  start\r\n", testCount);
                    
                    sprintf(featureName, "%s%d%s%d%s%d%s%d%s%d%s%d%s%d",
                            ":Tx", aoaTestCfg.numTxAntennas,
                            ":Rx", aoaTestCfg.numRxAntennas,
                            ":Chp", aoaTestCfg.numChirps,
                            ":D", aoaTestCfg.numDopplerBins,
                            ":R", aoaTestCfg.numRangeBins,
                            ":bpm", aoaTestCfg.bpmFlag,
                            ":extVel", aoaTestCfg.extVelocityFlag);
                    System_printf("Test feature : %s\n", featureName);
                        
                    
                    {
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
                    }
                    

                     /* generate 2D windowing coefficients */
                     pTestDopplerWindow = testDopplerWindow;
                     aoaCfg.res.windowCoeff = pTestDopplerWindow;
                     Test_window2DCoef_gen(aoaTestCfg.numChirps, aoaTestCfg.winType, pTestDopplerWindow);
                     /* generates the 1D fft output, radar cube data */
                     Test_aoaDpu_cubeDataGen(&aoaTestCfg);
                     
                     /* set up the AOA dpu configuration structure */
                     Test_setProfile(&aoaTestCfg);
                     /* clear the heat map memory */
                     memset(staticHeatmap, 0, sizeof(cmplx16ImRe_t)*TEST_MAX_NUM_RANGE_BIN_HEATMAP * 8);
                     /* call aoa dpu configuration */
                     retVal = DPU_AoAProcDSP_config(aoaProcHandle, &aoaCfg);
                     if (retVal < 0)
                     {
                         System_printf("AOA DPU failed to configure. Error %d.\n", retVal);
                         DebugP_assert(0);
                         return;
                     }

                     /* call aoa dpu process */
                     retVal = DPU_AoAProcDSP_process(aoaProcHandle, aoaTestCfg.numCfarDetObj, &outAoaProc);
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
                        
                             memset(staticHeatmap, 0, sizeof(cmplx16ImRe_t)*TEST_MAX_NUM_RANGE_BIN_HEATMAP * 8);
                             retVal = DPU_AoAProcDSP_config(aoaProcHandle, &aoaCfg);
                             retVal = DPU_AoAProcDSP_process(aoaProcHandle, aoaTestCfg.numCfarDetObj, &outAoaProc);
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
    
    EDMA_close(edmaHandle);
    retVal = DPU_AoAProcDSP_deinit(aoaProcHandle);
    if (retVal != 0)
    {
        System_printf("AOA DPU failed to deinit. Error %d.\n", retVal);
        DebugP_assert(0);
        return;
    }
    

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


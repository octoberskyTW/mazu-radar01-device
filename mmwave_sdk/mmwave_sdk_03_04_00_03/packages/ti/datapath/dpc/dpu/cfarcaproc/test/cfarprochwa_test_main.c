/**
 *   @file  cfarprochwa_test_main.c
 *
 *   @brief
 *      Unit Test code for cfar hwa dpu processing.
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
#include <ti/datapath/dpc/dpu/cfarcaproc/cfarcaprochwa.h>
#include <ti/utils/mathutils/mathutils.h>
#include <ti/utils/randomdatagenerator/gen_rand_data.h>


#define TEST_MAX_DETMATRIX_SIZE   (1024 * 16)    //numRangeBin*numDopplerBin*sizeof(uint16_t) <=32k
#define TEST_CFAR_DATAIN_LEN 1024
#define TEST_MAX_NUM_CFARDETOBJ_DPU_LIST 300
#define TEST_DOPPLER_BIN_SIZE 10 // test doppler size covers from 2 to 1024
#define TEST_RANGE_BIN_SIZE 7   //tested range bin size from 16 to 1024
#define TEST_CFAR_WIN_LEN 6
#define TEST_CFAR_GUARD_LEN 7
#define TEST_NOISE_THRESHOLD  800

/**
* @brief
*  CFAR Detected object configuration structure for reference.
*
*/
typedef struct cfarDetObjRef_t
{
    uint16_t rangeIdx;      /*!< @brief detected object range index */
    uint16_t dopplerIdx;    /*!< @brief detected object doppler index */
    uint16_t peakAbs;       /*!< @brief detected object signal power */
    uint16_t noise;         /*!< @brief detected object noise power */

}cfarDetObjRef_t;

/* radar det matrix */
#pragma DATA_SECTION(testDetMatrix, ".l3ram");
uint16_t testDetMatrix[TEST_MAX_DETMATRIX_SIZE];

/* cfar dpu detected object output */
#pragma DATA_SECTION(cfarDetObjList, ".l3ram");
DPIF_CFARDetList cfarDetObjList[TEST_MAX_NUM_CFARDETOBJ_DPU_LIST];

/* cfar DPU internal buffer for doppler cfar is enabled, to save the detected objects*/
#pragma DATA_SECTION(cfarDopplerDetOutBitMask, ".l3ram");
#pragma DATA_ALIGN(cfarDopplerDetOutBitMask,DPU_CFARCAPROCHWA_DOPPLER_DET_OUT_BIT_MASK_BYTE_ALIGNMENT);
uint32_t cfarDopplerDetOutBitMask[512]; //1024*16/32*size(uint32_t)

/* the reference doppler cfar outputs*/
#pragma DATA_SECTION(cfarDopplerDetOutRef, ".l3ram");
uint8_t cfarDopplerDetOutRef[1024 * 16];

/* the reference cfar outputs*/
#pragma DATA_SECTION(cfarDetObjRef, ".l3ram");
cfarDetObjRef_t cfarDetObjRef[TEST_MAX_NUM_CFARDETOBJ_DPU_LIST];

/* for doppler and range cfar, fov commands*/
#pragma DATA_SECTION(cfarDetObjCheck, ".l3ram");
uint8_t cfarDetObjCheck[TEST_MAX_NUM_CFARDETOBJ_DPU_LIST];
uint32_t numDetPeaksRef;
uint32_t numCheckPeaksRef;

#ifdef SUBSYS_MSS
#pragma DATA_SECTION(cfarInputDataTemp, ".tcmb");
#endif
#ifdef SUBSYS_DSS
#pragma DATA_SECTION(cfarInputDataTemp, ".l2data");
#endif
uint16_t cfarInputDataTemp[TEST_CFAR_DATAIN_LEN];

SOC_Handle  socHandle;
EDMA_Handle edmaHandle;
HWA_Handle  hwaHandle;


/**
* @brief
*  CFAR reference configuration.
*
*/
typedef struct cfarConfig_Test
{
    uint8_t aveMode;      /*!< @brief CFAR mode =0, average, = 1: SO, =2: GO */
    uint8_t winLen;       /*!< @brief CFAR window length */
    uint8_t guardLen;     /*!< @brief CFAR guard length */
    uint8_t cyclicMode;   /*!< @brief CFAR cyclic mode =0: non-cyclic, = 1: cyclic mode */
    
}cfarConfig_Test;

/**
* @brief
*  CFAR DPU unit test test configuration structure.
*
*/
typedef struct cfarProcDpuTestConfig_t
{
    uint16_t numRangeBins;       /*!< @brief number of range bin */   
    uint16_t numDopplerBins;     /*!< @brief number of doppler bin */
    uint8_t dopplerCfarEnabled;  /*!< @brief Flag for dppler cfar enabled  or disabled */ 
    cfarConfig_Test cfarRangeCfg;  /*!< @brief cfar configuration for range bin */
    cfarConfig_Test cfarDopplerCfg; /*!< @brief cfar configuration for doppler bin */
    uint8_t cfarRangePeakPruning;   /*!< @brief peak group for range bin cfar */  
    uint8_t cfarDopplerPeakPruning;  /*!< @brief peak group for doppler bin cfar */
    uint8_t dpuControlFlag;          /*!< @brief CFAR dpu command 0-rangefov, 1-dopplerfov, 2-doppler cfar, 3-range cfar */

}cfarProcDpuTestConfig_t;


#define DPU_CFAR_PROC_EDMAIN_CH          EDMA_TPCC0_REQ_FREE_16
#define DPU_CFAR_PROC_EDMAIN_SHADOW      (EDMA_NUM_DMA_CHANNELS + 25U)
#define DPU_CFAR_PROC_EDMAIN_EVENT_QUE   0
#define DPU_CFAR_PROC_EDMAIN_SIG_CH          EDMA_TPCC0_REQ_FREE_17
#define DPU_CFAR_PROC_EDMAIN_SIG_SHADOW      (EDMA_NUM_DMA_CHANNELS + 26U)
#define DPU_CFAR_PROC_EDMAIN_SIG_EVENT_QUE   0


DPU_CFARCAProcHWA_Config cfarDpuCfg;
DPU_CFARCAProcHWA_Handle cfarDpuHandle;
DPU_CFARCAProc_CfarCfg cfarRangeCfg;
DPU_CFARCAProc_CfarCfg cfarDopplerCfg;
DPU_CFARCAProc_FovCfg fovRangeCfg;
DPU_CFARCAProc_FovCfg fovDopplerCfg;
int32_t hwaMemBankSize;
uint32_t hwaMemBankAddr[4];

cfarProcDpuTestConfig_t cfarTestCfg;
uint32_t numDetObjRef;
DPU_CFARCAProcHWA_OutParams cfarDpuOut;

MCPI_LOGBUF_INIT(512);

uint8_t finalResults;
uint32_t testCount; 


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
    HWA_MemInfo         hwaMemInfo;
    uint32_t ii;

    /* Initialize the HWA */
    HWA_init();

    hwaHandle = HWA_open(0, socHandle, &errorCode);
    if (hwaHandle == NULL)
    {
        System_printf("HWA failed to open\n");
        DebugP_assert(0);
        return;
    }

    errorCode = HWA_getHWAMemInfo(hwaHandle, &hwaMemInfo);
    if (errorCode != 0)
    {
        System_printf("HWA MEMINFOR get fails\n");
        DebugP_assert(0);
        return;
    }
    hwaMemBankSize = hwaMemInfo.bankSize;

    for (ii = 0; ii < hwaMemInfo.numBanks; ii++)
    {
        hwaMemBankAddr[ii] = hwaMemInfo.baseAddress + ii * hwaMemBankSize;
    }

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
    if ((errorCode = EDMA_configErrorMonitoring(edmaHandle, &errorConfig)) != EDMA_NO_ERROR)
    {
        System_printf("Error: EDMA_configErrorMonitoring() failed with errorCode = %d\n", errorCode);
        DebugP_assert(0);
        return;
    }

}


/**
*  @b Description
*  @n
*   Initialize the CFAR DPU configuration structure for the parameters NOT change for every test.
*
*  @retval None
*
*/
void cfarProc_test_dpuConfig()
{
    DPU_CFARCAProcHWA_HW_Resources *pHwRes;

    /* static config*/
    cfarDpuCfg.staticCfg.rangeStep = 1.f;
    cfarDpuCfg.staticCfg.dopplerStep = 1.f;

    /* cfar range configuration */
    fovRangeCfg.min = 0.f; 
    fovRangeCfg.max = 1025.f;
    fovDopplerCfg.min = -512.f;      //signed min, and max
    fovDopplerCfg.max = 512.f;

    cfarDpuCfg.dynCfg.cfarCfgDoppler = &cfarDopplerCfg;
    cfarDpuCfg.dynCfg.cfarCfgRange = &cfarRangeCfg;
    cfarDpuCfg.dynCfg.fovRange = &fovRangeCfg;
    cfarDpuCfg.dynCfg.fovDoppler = &fovDopplerCfg;

    /* hw resource*/
    pHwRes = &cfarDpuCfg.res;
    pHwRes->edmaHandle = edmaHandle;
    pHwRes->edmaHwaIn.channel = DPU_CFAR_PROC_EDMAIN_CH;
    pHwRes->edmaHwaIn.channelShadow = DPU_CFAR_PROC_EDMAIN_SHADOW;
    pHwRes->edmaHwaIn.eventQueue = DPU_CFAR_PROC_EDMAIN_EVENT_QUE;

    pHwRes->edmaHwaInSignature.channel = DPU_CFAR_PROC_EDMAIN_SIG_CH;
    pHwRes->edmaHwaInSignature.channelShadow = DPU_CFAR_PROC_EDMAIN_SIG_SHADOW;
    pHwRes->edmaHwaInSignature.eventQueue = DPU_CFAR_PROC_EDMAIN_SIG_EVENT_QUE;

    pHwRes->hwaCfg.numParamSet = 2U;
    pHwRes->hwaCfg.paramSetStartIdx = 0U; 

    pHwRes->detMatrix.datafmt = DPIF_DETMATRIX_FORMAT_1; 
    pHwRes->detMatrix.data = testDetMatrix;

    pHwRes->cfarRngDopSnrList = cfarDetObjList;
    pHwRes->cfarRngDopSnrListSize = TEST_MAX_NUM_CFARDETOBJ_DPU_LIST;

    pHwRes->hwaMemInp = (uint16_t *)hwaMemBankAddr[0];
    pHwRes->hwaMemInpSize = (hwaMemBankSize * 2) / sizeof(uint16_t);
    pHwRes->hwaMemOutDoppler = (DPU_CFARCAProcHWA_CfarDetOutput *)hwaMemBankAddr[2];
    pHwRes->hwaMemOutDopplerSize = hwaMemBankSize / sizeof(DPU_CFARCAProcHWA_CfarDetOutput);
    pHwRes->hwaMemOutRange = (DPU_CFARCAProcHWA_CfarDetOutput *)hwaMemBankAddr[3];
    pHwRes->hwaMemOutRangeSize = hwaMemBankSize / sizeof(DPU_CFARCAProcHWA_CfarDetOutput);
    pHwRes->cfarDopplerDetOutBitMask = cfarDopplerDetOutBitMask;

 }

/**
*  @b Description
*  @n
*       Implements CFAR detection, based on hwa CFAR engine described in Radar hardware accelerator
*
*  @retval the number of detected objets
*
*/
uint16_t test_cfar_ref(cfarConfig_Test * cfarConfig, int16_t length, uint16_t * inputData, uint16_t * outList, uint32_t *peakNoise)
{
    uint16_t count;
    uint16_t ii;
    uint16_t leftSide, rightSide;
    uint32_t rightSum, leftSum;
    uint32_t maxSum, minSum;
    uint16_t minScale, maxScale;
    uint32_t noiseValue;
    uint16_t totalWin;
    uint16_t guardLen;

    count = 0;
    minScale = 0;
    maxScale = 0;
    if (cfarConfig->aveMode == 0)
    {
        minScale = 1;  //average both left and right
        maxScale = 1;
    }
    else if (cfarConfig->aveMode == 1) //GO
    {
        minScale = 0;  
        maxScale = 1;  //average over max
    }
    else if (cfarConfig->aveMode == 2) //SO
    {
        minScale = 1;  //average over min
        maxScale = 0;
    }

    guardLen = cfarConfig->guardLen;
    totalWin = cfarConfig->winLen + cfarConfig->guardLen;

    leftSide = cfarConfig->winLen + cfarConfig->guardLen;
    rightSide = length - leftSide;
    
    rightSum = 0;
    leftSum = 0;
    for (ii = guardLen + 1; ii < totalWin + 1; ii++)
    {
        rightSum += inputData[ii];
    }

    /* check point 0*/
    if (!cfarConfig->cyclicMode)
    {
        noiseValue = rightSum / cfarConfig->winLen;
        if (inputData[0] > (noiseValue + TEST_NOISE_THRESHOLD))  //threshold
        {
            outList[count] = 0; //detect peak
            peakNoise[count] = noiseValue;
            count++;
        }
       
    }
    else
    {
        for (ii = length - totalWin; ii < length - guardLen; ii++)
        {
            leftSum += inputData[ii];
        }

        if (rightSum > leftSum)
        {
            maxSum = rightSum;
            minSum = leftSum;
        }
        else
        {
            maxSum = leftSum;
            minSum = rightSum;
        }

        noiseValue = (maxSum * maxScale + minSum * minScale) / (minScale + maxScale) / cfarConfig->winLen;
        if (inputData[0] >(noiseValue + TEST_NOISE_THRESHOLD))  //threshold
        {
            outList[count] = 0; //detect peak
            peakNoise[count] = noiseValue;
            count++;
        }

    }

    /* other points */
    if (!cfarConfig->cyclicMode)
    {
        for (ii = 1; ii < leftSide; ii++)
        {
            rightSum -= inputData[ii + guardLen];
            rightSum += inputData[ii + totalWin];

            noiseValue = rightSum / cfarConfig->winLen;
            if (inputData[ii] > (noiseValue + TEST_NOISE_THRESHOLD))  //threshold
            {
                outList[count] = ii; //detect peak
                peakNoise[count] = noiseValue;
                count++;
            }
        }
       
        /* prepare the left sum for point leftSide */
        for (ii = 0; ii < cfarConfig->winLen; ii++)
        {
             leftSum += inputData[ii];
        }

        if (leftSide < rightSide)
        {
             rightSum -= inputData[leftSide + guardLen];
             rightSum += inputData[leftSide + totalWin];
             if (rightSum > leftSum)
             {
                 maxSum = rightSum;
                 minSum = leftSum;
             }
             else
             {
                 maxSum = leftSum;
                 minSum = rightSum;
             }

             noiseValue = (maxSum * maxScale + minSum * minScale) / (minScale + maxScale) / cfarConfig->winLen;
             if (inputData[leftSide] > (noiseValue + TEST_NOISE_THRESHOLD))  //threshold
             {
                 outList[count] = leftSide; //detect peak
                 peakNoise[count] = noiseValue;
                 count++;
             }
        }
       
    }
    else // cyclic mode
    {
        for (ii = 1; ii < guardLen + 1; ii++)
        {
            rightSum -= inputData[ii + guardLen];
            rightSum += inputData[ii + totalWin];
            leftSum -= inputData[length - totalWin + ii - 1];
            leftSum += inputData[length - guardLen + ii - 1];

            if(rightSum > leftSum)
            {
                maxSum = rightSum;
                minSum = leftSum;
            }
            else
            {
                maxSum = leftSum;
                minSum = rightSum;
            }

            noiseValue = (maxSum * maxScale + minSum * minScale) / (minScale + maxScale) / cfarConfig->winLen;
            if (inputData[ii] >(noiseValue + TEST_NOISE_THRESHOLD))  //threshold
            {
                outList[count] = ii; //detect peak
                peakNoise[count] = noiseValue;
                count++;
            }
           
        }

        for (ii = guardLen + 1; ii < leftSide + 1; ii++)
        {
            rightSum -= inputData[ii + guardLen];
            rightSum += inputData[ii + totalWin];
            leftSum -= inputData[length - totalWin + ii - 1];
            leftSum += inputData[ii - guardLen - 1];

            if (rightSum > leftSum)
            {
                maxSum = rightSum;
                minSum = leftSum;
            }
            else
            {
                maxSum = leftSum;
                minSum = rightSum;
            }

            noiseValue = (maxSum * maxScale + minSum * minScale) / (minScale + maxScale) / cfarConfig->winLen;
            if (inputData[ii] >(noiseValue + TEST_NOISE_THRESHOLD))  //threshold
            {
                outList[count] = ii; //detect peak
                peakNoise[count] = noiseValue;
                count++;
            }
            
        }
    }

    /* middle part*/
    for (ii = leftSide + 1; ii < rightSide ; ii++)
    {
        rightSum -= inputData[ii + guardLen];
        rightSum += inputData[ii + totalWin];
        leftSum -= inputData[ii - totalWin - 1];
        leftSum += inputData[ii - guardLen - 1];

        if (rightSum > leftSum)
        {
            maxSum = rightSum;
            minSum = leftSum;
        }
        else
        {
            maxSum = leftSum;
            minSum = rightSum;
        }
        
        noiseValue = (maxSum * maxScale + minSum * minScale) / (minScale + maxScale) / cfarConfig->winLen;
        if (inputData[ii] >(noiseValue + TEST_NOISE_THRESHOLD))  //threshold
        {
            outList[count] = ii; //detect peak
            peakNoise[count] = noiseValue;
            count++;
        }
        
    }

    /* right edge */
    if (!cfarConfig->cyclicMode)
    {
        
        if (leftSide < rightSide)
        {
            for (ii = rightSide; ii < length; ii++)
            {
                leftSum -= inputData[ii - totalWin - 1];
                leftSum += inputData[ii - guardLen - 1];

                noiseValue = leftSum / cfarConfig->winLen;
                if (inputData[ii] > (noiseValue + TEST_NOISE_THRESHOLD))  //threshold
                {
                    outList[count] = ii; //detect peak
                    peakNoise[count] = noiseValue;
                    count++;
                }
             }
        }
        else if (leftSide == rightSide)
        {
           
            noiseValue = leftSum / cfarConfig->winLen;
            if (inputData[leftSide] > (noiseValue + TEST_NOISE_THRESHOLD))  //threshold
            {
                outList[count] = leftSide; //detect peak
                peakNoise[count] = noiseValue;
                count++;
            }

            for (ii = rightSide + 1; ii < length; ii++)
            {
                leftSum -= inputData[ii - totalWin - 1];
                leftSum += inputData[ii - guardLen - 1];

                noiseValue = leftSum / cfarConfig->winLen;
                if (inputData[ii] >(noiseValue + TEST_NOISE_THRESHOLD))  //threshold
                {
                    outList[count] = ii; //detect peak
                    peakNoise[count] = noiseValue;
                    count++;
                }

            }
        }
    }
    else
    {
        for (ii = rightSide; ii < length - guardLen; ii++)
        {
            leftSum -= inputData[ii - totalWin - 1];
            leftSum += inputData[ii - guardLen - 1];
            rightSum -= inputData[ii + guardLen];
            rightSum += inputData[ii + totalWin - length];

            if (rightSum > leftSum)
            {
                maxSum = rightSum;
                minSum = leftSum;
            }
            else
            {
                maxSum = leftSum;
                minSum = rightSum;
            }

            noiseValue = (maxSum * maxScale + minSum * minScale) / (minScale + maxScale) / cfarConfig->winLen;
            if (inputData[ii] >(noiseValue + TEST_NOISE_THRESHOLD))  //threshold
            {
                outList[count] = ii; //detect peak
                peakNoise[count] = noiseValue;
                count++;
            }
            
        }

        for (ii = length - guardLen; ii < length ; ii++)
        {
            leftSum -= inputData[ii - totalWin - 1];
            leftSum += inputData[ii - guardLen - 1];
            rightSum -= inputData[ii + guardLen - length];
            rightSum += inputData[ii + totalWin - length];

            if (rightSum > leftSum)
            {
                maxSum = rightSum;
                minSum = leftSum;
            }
            else
            {
                maxSum = leftSum;
                minSum = rightSum;
            }

            noiseValue = (maxSum * maxScale + minSum * minScale) / (minScale + maxScale) / cfarConfig->winLen;
            if (inputData[ii] >(noiseValue + TEST_NOISE_THRESHOLD))  //threshold
            {
                outList[count] = ii; //detect peak
                peakNoise[count] = noiseValue;
                count++;
            }
        }
    }
    return count;
    
}

#if defined(SOC_XWR68XX)     //68xx es2 version
/**
*  @b Description
*  @n
*       Implements peak grouping, based on hwa CFAR engine described in Radar hardware accelerator,
*       A peak is declared only if the cell under test is greater than or equal to its most immediate
*       neighboring cells to its left and right
*
*  @retval none
*
*/
void test_hwaPeakgroup_ref(uint16_t *inputData, uint16_t length, uint16_t numDetPeaks, uint16_t * peakIdx, uint8_t wrapFlag, uint8_t *peakAddFlag)
{
    uint16_t ii;
    uint16_t index;
    for (ii = 0; ii < numDetPeaks; ii++)
    {
        peakAddFlag[ii] = 0;
        index = peakIdx[ii];
        //no wrap around
        if (index == 0)
        {
            if (wrapFlag)
            {
                if ((inputData[index] >= inputData[index + 1]) & (inputData[index] >= inputData[length - 1]))
                {
                    peakAddFlag[ii] = 1;
                }
            }
            else  //no wrap around
            {
                if (inputData[index] >= inputData[index + 1]) //to match with hwa, only if > neighbour
                {
                    peakAddFlag[ii] = 1;
                }
            }

        }
        else if (index == length - 1)
        {
            if (wrapFlag)
            {
                if ((inputData[index] >= inputData[index - 1]) & (inputData[index] >= inputData[0]))
                {
                    peakAddFlag[ii] = 1;
                }
            }
            else
            {
                if (inputData[index] >= inputData[index - 1])
                {
                    peakAddFlag[ii] = 1;
                }
            }
        }
        else
        {
            if ((inputData[index] >= inputData[index + 1]) & (inputData[index] >= inputData[index - 1]))
            {
                peakAddFlag[ii] = 1;
            }

        }
    }
}
#endif
#if defined (SOC_XWR18XX)
/**
*  @b Description
*  @n
*       Implements peak grouping, based on hwa CFAR engine described in Radar hardware accelerator
*       A peak is declared only if the cell under test is greater than its most immediate
*       neighboring cells to its left and right
*  @retval none
*
*/
void test_hwaPeakgroup_ref(uint16_t *inputData, uint16_t length, uint16_t numDetPeaks, uint16_t * peakIdx, uint8_t wrapFlag , uint8_t *peakAddFlag)
{
    uint16_t ii;
    uint16_t index;
    for (ii = 0; ii < numDetPeaks; ii++)
    {
        peakAddFlag[ii] = 0;
        index = peakIdx[ii]; 
        //no wrap around
        if (index == 0)
        {
            if (wrapFlag)
            {
                if ((inputData[index] > inputData[index + 1]) & (inputData[index] > inputData[length - 1]))
                {
                    peakAddFlag[ii] = 1;
                }
            }
            else  //no wrap around
            {
                if (inputData[index] > inputData[index + 1]) //to match with hwa, only if > neighbour
                {
                    peakAddFlag[ii] = 1;
                }
            }
            
        }
        else if (index == length - 1)
        {
            if (wrapFlag)
            {
                if ((inputData[index] > inputData[index - 1]) & (inputData[index] > inputData[0]))
                {
                    peakAddFlag[ii] = 1;
                }
            }
            else
            {
                if (inputData[index] > inputData[index - 1])
                {
                    peakAddFlag[ii] = 1;
                }
            }
        }
        else
        {
            if ((inputData[index] > inputData[index + 1]) & (inputData[index] > inputData[index - 1]))
            {
                peakAddFlag[ii] = 1;
            }

        }
    }
}
#endif
/**
*  @b Description
*  @n
*       Implement the range bin cfar and both range bin + doppler bin cfar for generating test references.
*
*  @retval the number of detected objets
*
*/
void Test_gen_detobj_ref(cfarProcDpuTestConfig_t * testConfig)
{
    uint32_t ii, jj;
    uint16_t numDetPeaks;
    uint16_t peakIdx[TEST_MAX_NUM_CFARDETOBJ_DPU_LIST];
    uint32_t peakNoise[TEST_MAX_NUM_CFARDETOBJ_DPU_LIST];
    uint8_t peakAddFlag[TEST_MAX_NUM_CFARDETOBJ_DPU_LIST];
    uint16_t * dataInPtr;

    numDetPeaksRef = 0;

    if (!testConfig->dopplerCfarEnabled)  //doppler cfar is disabled
    {
        for (ii = 0; ii < testConfig->numDopplerBins; ii++)
        {
            for (jj = 0; jj < testConfig->numRangeBins; jj++)
            {
                cfarInputDataTemp[jj] = testDetMatrix[jj * testConfig->numDopplerBins + ii];
             }
            /* call cfar reference */
            numDetPeaks = test_cfar_ref(&testConfig->cfarRangeCfg, testConfig->numRangeBins, cfarInputDataTemp, peakIdx, peakNoise);

            if ((testConfig->cfarRangePeakPruning)  && (numDetPeaks))
            {
                /* call peak pruning ref */
                test_hwaPeakgroup_ref(cfarInputDataTemp, testConfig->numRangeBins, numDetPeaks, peakIdx, testConfig->cfarRangeCfg.cyclicMode, peakAddFlag);
            }
            
            if (numDetPeaksRef < TEST_MAX_NUM_CFARDETOBJ_DPU_LIST)
            {
                for (jj = 0; jj < numDetPeaks; jj++)
                {
                    if ((!testConfig->cfarRangePeakPruning) || ((testConfig->cfarRangePeakPruning) && peakAddFlag[jj]))
                    {
                        cfarDetObjRef[numDetPeaksRef].dopplerIdx = ii;
                        cfarDetObjRef[numDetPeaksRef].rangeIdx = peakIdx[jj];
                        cfarDetObjRef[numDetPeaksRef].noise = peakNoise[jj];
                        cfarDetObjRef[numDetPeaksRef].peakAbs = cfarInputDataTemp[peakIdx[jj]];
                        cfarDetObjCheck[numDetPeaksRef] = 1;
                        numDetPeaksRef++;
                        if (numDetPeaksRef >= TEST_MAX_NUM_CFARDETOBJ_DPU_LIST)
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
    else  //doppler cfar is enabled
    {
        memset(cfarDopplerDetOutRef, 0, testConfig->numDopplerBins * testConfig->numRangeBins * sizeof(uint8_t));
        for (ii = 0; ii < testConfig->numRangeBins; ii++)
        {
            dataInPtr = &testDetMatrix[ii * testConfig->numDopplerBins];
            /* call the cfar */
            numDetPeaks = test_cfar_ref(&testConfig->cfarDopplerCfg, testConfig->numDopplerBins, dataInPtr, peakIdx, peakNoise);
            if ((testConfig->cfarDopplerPeakPruning) && (numDetPeaks))
            {
                /* call peak pruning ref */
                test_hwaPeakgroup_ref(dataInPtr, testConfig->numDopplerBins, numDetPeaks, peakIdx, testConfig->cfarDopplerCfg.cyclicMode, peakAddFlag);
            }
            for (jj = 0; jj < numDetPeaks; jj++)
            {
                if ((!testConfig->cfarDopplerPeakPruning) || ((testConfig->cfarDopplerPeakPruning) && peakAddFlag[jj]))
                {
                    cfarDopplerDetOutRef[ii * testConfig->numDopplerBins + peakIdx[jj]] = 1;
                }
            }

        }

        /* do the range cfar */
        for (ii = 0; ii < testConfig->numDopplerBins; ii++)
        {
            for (jj = 0; jj < testConfig->numRangeBins; jj++)
            {
                cfarInputDataTemp[jj] = testDetMatrix[jj * testConfig->numDopplerBins + ii];
            }
            /* call cfar reference */
            numDetPeaks = test_cfar_ref(&testConfig->cfarRangeCfg, testConfig->numRangeBins, cfarInputDataTemp, peakIdx, peakNoise);

            if ((testConfig->cfarRangePeakPruning) && (numDetPeaks))
            {
                /* call peak pruning ref */
                test_hwaPeakgroup_ref(cfarInputDataTemp, testConfig->numRangeBins, numDetPeaks, peakIdx, testConfig->cfarRangeCfg.cyclicMode, peakAddFlag);
            }

            if (numDetPeaksRef < TEST_MAX_NUM_CFARDETOBJ_DPU_LIST)
            {
                for (jj = 0; jj < numDetPeaks; jj++)
                {
                    if ((!testConfig->cfarRangePeakPruning) || ((testConfig->cfarRangePeakPruning) && peakAddFlag[jj]))
                    {
                        if (cfarDopplerDetOutRef[peakIdx[jj] * testConfig->numDopplerBins + ii])
                        {
                            cfarDetObjRef[numDetPeaksRef].dopplerIdx = ii;
                            cfarDetObjRef[numDetPeaksRef].rangeIdx = peakIdx[jj];
                            cfarDetObjRef[numDetPeaksRef].noise = peakNoise[jj];
                            cfarDetObjRef[numDetPeaksRef].peakAbs = cfarInputDataTemp[peakIdx[jj]];
                            cfarDetObjCheck[numDetPeaksRef] = 1;
                            numDetPeaksRef++;
                            if (numDetPeaksRef > TEST_MAX_NUM_CFARDETOBJ_DPU_LIST)
                            {
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

/**
*  @b Description
*  @n
*  set up the AOA DPU configuration structure based on each test configurations.
*
*  @retval None
*
*/
void Test_setProfile(cfarProcDpuTestConfig_t * testConfig)
{
    /* cfar range configuration */
    fovRangeCfg.min = 0.f;
    fovRangeCfg.max = 1025.f;
    fovDopplerCfg.min = -512.f;      //signed min, and max
    fovDopplerCfg.max = 512.f;

    cfarDpuCfg.staticCfg.numDopplerBins = testConfig->numDopplerBins;
    cfarDpuCfg.staticCfg.numRangeBins = testConfig->numRangeBins;
    cfarDpuCfg.staticCfg.log2NumDopplerBins = mathUtils_floorLog2(testConfig->numDopplerBins);
    
    /* cfar range config*/
    cfarRangeCfg.thresholdScale = TEST_NOISE_THRESHOLD; // noiseVar + thresholdScale
    cfarRangeCfg.averageMode = testConfig->cfarRangeCfg.aveMode;
    cfarRangeCfg.winLen = testConfig->cfarRangeCfg.winLen;
    cfarRangeCfg.guardLen = testConfig->cfarRangeCfg.guardLen;
    if (cfarRangeCfg.averageMode == 0)//cfar average
    {
        cfarRangeCfg.noiseDivShift = mathUtils_floorLog2(testConfig->cfarRangeCfg.winLen * 2);  //the sum of noise divided by 2^noiseDivShift
    }
    else      //cfar so, or go
    {
        cfarRangeCfg.noiseDivShift = mathUtils_floorLog2(testConfig->cfarRangeCfg.winLen);  //the sum of noise divided by 2^noiseDivShift
    }
   
    cfarRangeCfg.cyclicMode = testConfig->cfarRangeCfg.cyclicMode;
    if (testConfig->cfarRangePeakPruning) //peak group is enabled
    {
        cfarRangeCfg.peakGroupingEn = 1;
        cfarRangeCfg.peakGroupingScheme = 1;
    }
    else
    {
        cfarRangeCfg.peakGroupingEn = 0;
        cfarRangeCfg.peakGroupingScheme = 0;
    }

    /* cfar doppler config */
    if (testConfig->dopplerCfarEnabled) //enabled the doppler cfar 
        cfarDopplerCfg.thresholdScale = TEST_NOISE_THRESHOLD; 
    else
        cfarDopplerCfg.thresholdScale = 0; //disable the doppler cfar

    cfarDopplerCfg.averageMode = testConfig->cfarDopplerCfg.aveMode;
    cfarDopplerCfg.winLen = testConfig->cfarDopplerCfg.winLen;
    cfarDopplerCfg.guardLen = testConfig->cfarDopplerCfg.guardLen;

    if (cfarDopplerCfg.averageMode == 0)
    {
        cfarDopplerCfg.noiseDivShift = mathUtils_floorLog2(testConfig->cfarDopplerCfg.winLen * 2);  //the sum of noise divided by 2^noiseDivShift
    }
    else
    {
        cfarDopplerCfg.noiseDivShift = mathUtils_floorLog2(testConfig->cfarDopplerCfg.winLen);  //the sum of noise divided by 2^noiseDivShift
    }

    cfarDopplerCfg.cyclicMode = testConfig->cfarDopplerCfg.cyclicMode;
    if (testConfig->cfarDopplerPeakPruning) //peak group is enabled
    {
        cfarDopplerCfg.peakGroupingEn = 1;
        cfarDopplerCfg.peakGroupingScheme = 1;
    }
    else
    {
        cfarDopplerCfg.peakGroupingEn = 0;
        cfarDopplerCfg.peakGroupingScheme = 0;
    }

    cfarDpuCfg.res.detMatrix.dataSize = testConfig->numDopplerBins * testConfig->numRangeBins * sizeof(uint16_t);
    cfarDpuCfg.res.cfarDopplerDetOutBitMaskSize = testConfig->numRangeBins * testConfig->numDopplerBins / 32;
}

/**
*  @b Description
*  @n
*  calculate modula value
*
*  @retval the modula value
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
*   randomly generate a table index, and returns the table elemenment based on the index
*
*  @retval one of table elemenet, with randonly generated index
*
*/
uint16_t test_setParam(uint16_t modValue, uint8_t * pTbl)
{
    uint16_t tempValue, index;
    uint16_t value;

    tempValue = RandSimple();
    index = test_modCalc(tempValue, modValue);
    if (pTbl == NULL)
    {
        return index;
    }
    else
    {
        value = pTbl[index];
        return value;
    }
}

/**
*  @b Description
*  @n
*   check the CFAR DPU results with the reference.
*
*  @retval None
*
*/
void Test_printResults()
{
    uint8_t testPass = 1;
    uint32_t ii;
    float noiseInDbRef;
    float snrInDbRef;
    int16_t temp;
    uint32_t peakIdx;
    
    if (numCheckPeaksRef != cfarDpuOut.numCfarDetectedPoints)
    {
        System_printf("\nCFAR output number is : cfarOut=%d, ref=%d\n", cfarDpuOut.numCfarDetectedPoints, numDetPeaksRef);
        finalResults = 0;
        testPass = 0;
    }
    peakIdx = 0;
    for (ii = 0; ii < numDetPeaksRef; ii++)
    {
        if (!cfarDetObjCheck[ii])
            continue;
        /* check range idx */
        if (cfarDetObjRef[ii].rangeIdx != cfarDetObjList[peakIdx].rangeIdx)
        {
            System_printf("\ndetObj %d rangeIdx is : cfarOut=%d, ref=%d\n", ii, cfarDetObjList[peakIdx].rangeIdx, cfarDetObjRef[ii].rangeIdx);
            finalResults = 0;
            testPass = 0;
        }
        /* check doppler Idx, not Signed*/
        if (cfarDetObjRef[ii].dopplerIdx != cfarDetObjList[peakIdx].dopplerIdx)
        {
            System_printf("\ndetObj %d doppler is : cfarOut=%d, ref=%d\n", ii, cfarDetObjList[peakIdx].dopplerIdx, cfarDetObjRef[ii].dopplerIdx);
            finalResults = 0;
            testPass = 0;
        }

        /* check the noise */
        noiseInDbRef = (float)cfarDetObjRef[ii].noise / 256.f * 6.f; //20/log10(2)=6
        temp = (int16_t)(noiseInDbRef * 10.f);

        if (temp != cfarDetObjList[peakIdx].noise)
        {
            System_printf("\ndetObj %d noiseVar is : cfarOut=%d, ref=%d\n", ii, cfarDetObjList[peakIdx].noise, temp);
            finalResults = 0;
            testPass = 0;
        }
        /* check the snr */
        snrInDbRef = ((float)cfarDetObjRef[ii].peakAbs - (float)cfarDetObjRef[ii].noise) / 256.f * 6.f;
        temp = (int16_t)(snrInDbRef * 10.f);

        if (temp != cfarDetObjList[peakIdx].snr)
        {
            System_printf("\ndetObj %d snr is : cfarOut=%d, ref=%d\n", ii, cfarDetObjList[peakIdx].snr, temp);
            finalResults = 0;
            testPass = 0;
        }
        peakIdx++;
    }/* end of det peak*/
    
    if (testPass)
    {
        System_printf(" PASS ");
    }
    else
    {
         System_printf(" FAIL ");
    }
}


/**
*  @b Description
*  @n
*   if either Cmd_FovRangeCfg, or Cmd_FovDopplerCfg command is tested, update the cfar detected objects by removing
*   the objectes outside of the range or dopple range.
*
*  @retval None
*
*/
void Test_update_detobj_ref(cfarProcDpuTestConfig_t * testConfig)
{
    uint32_t ii;
    int16_t signedDopplerIdx;
   
    if (testConfig->dpuControlFlag == 0) //range fov
    {
        for (ii = 0; ii < numDetPeaksRef; ii++)
        {
            if ((cfarDetObjRef[ii].rangeIdx < fovRangeCfg.min) || (cfarDetObjRef[ii].rangeIdx > fovRangeCfg.max))
            {
                cfarDetObjCheck[ii] = 0;
                numCheckPeaksRef --;
            }
        }

    }
    else if (testConfig->dpuControlFlag == 1)
    {
        for (ii = 0; ii < numDetPeaksRef; ii++)
        {
            signedDopplerIdx = cfarDetObjRef[ii].dopplerIdx;
            if (signedDopplerIdx >= (testConfig->numDopplerBins / 2))
            {
                signedDopplerIdx = signedDopplerIdx - testConfig->numDopplerBins;
            }
            if ((signedDopplerIdx < fovDopplerCfg.min) || (signedDopplerIdx > fovDopplerCfg.max))
            {
                cfarDetObjCheck[ii] = 0;
                numCheckPeaksRef--;
            }
        }
    }
}


/**
*  @b Description
*  @n
*   based on the dpu commands, test the DPU_CFARCAProcHWA_control function.
*
*  @retval None
*
*/
void test_dpu_control_cmd(cfarProcDpuTestConfig_t * testConfig)
{
    int32_t retVal;
    if (testConfig->dpuControlFlag == 0)
    {
        fovRangeCfg.min = testConfig->numRangeBins / 8.f;
        fovRangeCfg.max = testConfig->numRangeBins / 2.f;
        retVal = DPU_CFARCAProcHWA_control(cfarDpuHandle, DPU_CFARCAProcHWA_Cmd_FovRangeCfg, &fovRangeCfg, sizeof(DPU_CFARCAProc_FovCfg));
        if (retVal != 0)
        {
            System_printf("CFAR DPU FovRangeCfg control error \n");
            DebugP_assert(0);
            return;
        }
    }
    else if (testConfig->dpuControlFlag == 1)
    {
        fovDopplerCfg.min = -testConfig->numDopplerBins / 8.f;      //signed min, and max
        fovDopplerCfg.max = testConfig->numDopplerBins / 2.f;
        retVal = DPU_CFARCAProcHWA_control(cfarDpuHandle, DPU_CFARCAProcHWA_Cmd_FovDopplerCfg, &fovDopplerCfg, sizeof(DPU_CFARCAProc_FovCfg));
        if (retVal != 0)
        {
            System_printf("CFAR DPU FovDopplerCfg control error \n");
            DebugP_assert(0);
            return;
        }
    }
    else if (testConfig->dpuControlFlag == 2)
    {
        testConfig->cfarDopplerCfg.aveMode = test_modCalc(testConfig->cfarDopplerCfg.aveMode + 1, 3);
        testConfig->cfarDopplerCfg.cyclicMode = test_modCalc(testConfig->cfarDopplerCfg.cyclicMode + 1, 2);
        if (testConfig->cfarDopplerCfg.guardLen != 1)
            testConfig->cfarDopplerCfg.guardLen = testConfig->cfarDopplerCfg.guardLen - 1;
        if (testConfig->cfarDopplerCfg.winLen != 2)
            testConfig->cfarDopplerCfg.winLen = testConfig->cfarDopplerCfg.winLen / 2;
        Test_setProfile(testConfig);
        retVal = DPU_CFARCAProcHWA_control(cfarDpuHandle, DPU_CFARCAProcHWA_Cmd_CfarDopplerCfg, &cfarDopplerCfg, sizeof(DPU_CFARCAProc_CfarCfg));

        if (retVal != 0)
        {
            System_printf("CFAR DPU CfarDopplerCfg control error \n");
            DebugP_assert(0);
            return;
        }
    }
    else if (testConfig->dpuControlFlag == 3)
    {
        testConfig->cfarRangeCfg.aveMode = test_modCalc(testConfig->cfarRangeCfg.aveMode + 1, 3);
        if (testConfig->cfarRangeCfg.guardLen != 1)
            testConfig->cfarRangeCfg.guardLen = testConfig->cfarRangeCfg.guardLen - 1;
        if (testConfig->cfarRangeCfg.winLen != 2)
            testConfig->cfarRangeCfg.winLen = testConfig->cfarRangeCfg.winLen / 2;
        Test_setProfile(testConfig);
        retVal = DPU_CFARCAProcHWA_control(cfarDpuHandle, DPU_CFARCAProcHWA_Cmd_CfarRangeCfg, &cfarRangeCfg, sizeof(DPU_CFARCAProc_CfarCfg));

        if (retVal != 0)
        {
            System_printf("CFAR DPU CfarDopplerCfg control error \n");
            DebugP_assert(0);
            return;
        }
    }
 }


/**
*  @b Description
*  @n
*     test main task  : readin the det matrix from the binary test file, which is generated using matlab.
*                      a cfar reference generation function is developmented to generate cfar detected objects, 
*                      The reference detected objects are compared with the CFAR DPU outputs, if they are same,
*                      the test is declared PASS, otherwise, it is declared FAIL. 
*
*  @retval None
*
*/
void Test_task(UArg arg0, UArg arg1)
{
    uint32_t ii, jj, kk;
    char featureName[200];
    uint32_t numDopplerBin[TEST_DOPPLER_BIN_SIZE] = { 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
    uint32_t numRangeBin[TEST_RANGE_BIN_SIZE] = { 16, 32, 64, 128, 256, 512, 1024 };
    uint8_t cfarWinLen[TEST_CFAR_WIN_LEN] = { 2, 4, 8, 16, 32, 64 };
    uint8_t cfarGuardLen[TEST_CFAR_GUARD_LEN] = {1, 2, 3, 4, 5, 6, 7 };
    uint32_t numTests;
    uint32_t numTestsRange;
    DPU_CFARCAProcHWA_InitParams cfarDpuInitParams;
    int32_t errorCode;
    FILE * fileId;
    
    finalResults = 1;
    
    System_printf("...... Initialization ...... \n");
   
    /* hwa, edma, inialization */
    aoaProc_test_hwaEdmainit();

    /* configure cfar dpu */
    cfarProc_test_dpuConfig();

    System_printf("CFARCA Proc DPU Test start ...... \n");
    /* for doppler size = 2, 4, 8, 16 test range bin <=1024 */
    numTests = TEST_RANGE_BIN_SIZE * 4; 
    /* for doppler size = 32, test range bin <= 512 */
    numTests += (TEST_RANGE_BIN_SIZE - 1);
    /* for doppler size = 64, test range bin <= 256 */
    numTests += (TEST_RANGE_BIN_SIZE - 2);
    /* for doppler size = 128, test range bin <= 128 */
    numTests += (TEST_RANGE_BIN_SIZE - 3);
    /* for doppler size = 256, test range bin <= 64 */
    numTests += (TEST_RANGE_BIN_SIZE - 4);
    /* for doppler size = 512, test range bin <= 32 */
    numTests += (TEST_RANGE_BIN_SIZE - 5);
    /* for doppler size = 1024, test range bin <= 16 */
    numTests += (TEST_RANGE_BIN_SIZE - 6);

    /* for every rangebinxdopplerbin combination, run 4 tests*/
    numTests = numTests * 4;

    printf("\n...... %d Tests to be run .......\n\n", numTests);

    fileId = fopen("testdata\\cfardpu_test_data.bin", "rb");
    if (fileId == NULL)
    {
        System_printf("Error:  Cannot open cfardpu_test_data.bin !\n");
        exit(0);
    }
    
    testCount = 0;
    cfarDpuInitParams.hwaHandle = hwaHandle;
    cfarDpuHandle = DPU_CFARCAProcHWA_init(&cfarDpuInitParams, &errorCode);
    if (errorCode != 0)
    {
        System_printf("CFAR DPU INIT fail\n");
        DebugP_assert(0);
        goto exit;
    }

    for (ii = 0; ii < TEST_DOPPLER_BIN_SIZE; ii++)/* doppler bin loop*/
    {

        if (ii < 4)
        {
            numTestsRange = TEST_RANGE_BIN_SIZE;
        }
        else
        {
            numTestsRange = TEST_RANGE_BIN_SIZE - (ii - 3);
        }

        for (jj = 0; jj < numTestsRange; jj++) /* range bin loop */
        {
            cfarTestCfg.numDopplerBins = numDopplerBin[ii];
            cfarTestCfg.numRangeBins = numRangeBin[jj];
            /* read in the det matrix data*/
            fread(testDetMatrix, sizeof(uint16_t), cfarTestCfg.numDopplerBins * cfarTestCfg.numRangeBins, fileId);
           
            for (kk = 0; kk < 4; kk++)
            {
                System_printf("\nTest #%d  start\r\n", testCount);

                /* range config*/
                /* cfar mode*/
                cfarTestCfg.cfarRangeCfg.aveMode = (uint8_t )test_setParam(3, NULL);
                /*cyclic mode */
                cfarTestCfg.cfarRangeCfg.cyclicMode = 0; //for range cfar, NOT support cyclic mode = 1
                
                /* win length */
                if (cfarTestCfg.numRangeBins == 16)
                    cfarTestCfg.cfarRangeCfg.winLen = test_setParam(2, cfarWinLen); 
                else if (cfarTestCfg.numRangeBins == 32)
                    cfarTestCfg.cfarRangeCfg.winLen = test_setParam(2, cfarWinLen);
                else if (cfarTestCfg.numRangeBins == 64)
                    cfarTestCfg.cfarRangeCfg.winLen = test_setParam(3, cfarWinLen);
                else if (cfarTestCfg.numRangeBins == 128)
                    cfarTestCfg.cfarRangeCfg.winLen = test_setParam(4, cfarWinLen);
                else if (cfarTestCfg.numRangeBins >= 256)
                    cfarTestCfg.cfarRangeCfg.winLen = test_setParam(TEST_CFAR_WIN_LEN, cfarWinLen);

                 /*  guard length*/
                if (cfarTestCfg.numRangeBins == 16)
                    cfarTestCfg.cfarRangeCfg.guardLen = test_setParam(3,cfarGuardLen);
                else if (cfarTestCfg.numRangeBins == 32)
                    cfarTestCfg.cfarRangeCfg.guardLen = test_setParam(4, cfarGuardLen);
                else 
                    cfarTestCfg.cfarRangeCfg.guardLen = test_setParam(TEST_CFAR_GUARD_LEN, cfarGuardLen);
                
                /* peak group*/
                cfarTestCfg.cfarRangePeakPruning = test_setParam(2, NULL);
                

                /* doppler cfar enabled flag*/
                if (cfarTestCfg.numDopplerBins < 16)
                    cfarTestCfg.dopplerCfarEnabled = 0;
                else
                    cfarTestCfg.dopplerCfarEnabled = (uint8_t)test_setParam(2, NULL);
               
                /* doppler config*/
                if (!cfarTestCfg.dopplerCfarEnabled)   //disable the doppler cfar
                {
                    cfarTestCfg.cfarDopplerCfg.aveMode = 0;
                    cfarTestCfg.cfarDopplerCfg.cyclicMode = 0;
                    cfarTestCfg.cfarDopplerCfg.winLen = 0;
                    cfarTestCfg.cfarDopplerCfg.guardLen = 0;
                    cfarTestCfg.cfarDopplerPeakPruning = 0;

                }
                else
                {
                    /* cfar mode*/
                    cfarTestCfg.cfarDopplerCfg.aveMode = (uint8_t)test_setParam(3, NULL);
                    /*cyclic mode */
                    cfarTestCfg.cfarDopplerCfg.cyclicMode = (uint8_t)test_setParam(2, NULL);
                    
                    /* win length */
                    if (cfarTestCfg.numDopplerBins == 16)
                        cfarTestCfg.cfarDopplerCfg.winLen = test_setParam(2, cfarWinLen);
                    else if (cfarTestCfg.numDopplerBins == 32)
                        cfarTestCfg.cfarDopplerCfg.winLen = test_setParam(3, cfarWinLen);
                    else if (cfarTestCfg.numDopplerBins == 64)
                        cfarTestCfg.cfarDopplerCfg.winLen = test_setParam(4, cfarWinLen);
                    else if (cfarTestCfg.numDopplerBins == 128)
                        cfarTestCfg.cfarDopplerCfg.winLen = test_setParam(5, cfarWinLen);
                    else //if (cfarTestCfg.numDopplerBins == 256)
                        cfarTestCfg.cfarDopplerCfg.winLen = test_setParam(TEST_CFAR_WIN_LEN, cfarWinLen);

                    /*  guard length*/
                    if (cfarTestCfg.numDopplerBins == 16)
                        cfarTestCfg.cfarDopplerCfg.guardLen = test_setParam(3, cfarGuardLen);
                    else if (cfarTestCfg.numDopplerBins == 32)
                        cfarTestCfg.cfarDopplerCfg.guardLen = test_setParam(4, cfarGuardLen);
                    else
                        cfarTestCfg.cfarDopplerCfg.guardLen = test_setParam(TEST_CFAR_GUARD_LEN, cfarGuardLen);
                    /* peak group*/
                    cfarTestCfg.cfarDopplerPeakPruning = test_setParam(2, NULL);
                   
                }
                
                sprintf(featureName, "%s%d%s%d",
                    ":D ", cfarTestCfg.numDopplerBins,
                    ":R ", cfarTestCfg.numRangeBins);
                
                System_printf("Test feature : %s", featureName);

                if (cfarTestCfg.cfarRangeCfg.aveMode == 0)
                {
                    System_printf("  RangeCfar:: CA");
                }
                else if (cfarTestCfg.cfarRangeCfg.aveMode == 1)
                {
                    System_printf("  RangeCfar:: GO");
                }
                else if (cfarTestCfg.cfarRangeCfg.aveMode == 2)
                {
                    System_printf("  RangeCfar:: SO");
                }
                sprintf(featureName, "%s%d%s%d%s%d%s%d",
                    ":G", cfarTestCfg.cfarRangeCfg.guardLen,
                    ":W", cfarTestCfg.cfarRangeCfg.winLen,
                    ":Cyc", cfarTestCfg.cfarRangeCfg.cyclicMode,
                    ":grp", cfarTestCfg.cfarRangePeakPruning
                );
                
                System_printf("%s", featureName);
                

                if (cfarTestCfg.dopplerCfarEnabled)
                {
                    if (cfarTestCfg.cfarDopplerCfg.aveMode == 0)
                    {
                        System_printf("  DopplerCfar:: CA");
                    }
                    else if (cfarTestCfg.cfarDopplerCfg.aveMode == 1)
                    {
                        System_printf("  DopplerCfar:: GO");
                    }
                    else if (cfarTestCfg.cfarDopplerCfg.aveMode == 2)
                    {
                        System_printf("  DopplerCfar:: SO");
                    }
                    sprintf(featureName, "%s%d%s%d%s%d%s%d",
                        ":G", cfarTestCfg.cfarDopplerCfg.guardLen,
                        ":W", cfarTestCfg.cfarDopplerCfg.winLen,
                        ":Cyc", cfarTestCfg.cfarDopplerCfg.cyclicMode,
                        ":grp", cfarTestCfg.cfarDopplerPeakPruning);

                    System_printf(" %s", featureName);
                }
                System_printf("\n");
               
                Test_gen_detobj_ref(&cfarTestCfg);
                numCheckPeaksRef = numDetPeaksRef;

                Test_setProfile(&cfarTestCfg);

                errorCode = DPU_CFARCAProcHWA_config(cfarDpuHandle, &cfarDpuCfg);
                if (errorCode != 0)
                {
                    System_printf("CFAR DPU configure error %d\n", errorCode);
                    DebugP_assert(0);
                    goto exit;;
                }

                errorCode = DPU_CFARCAProcHWA_process(cfarDpuHandle, &cfarDpuOut);
                if (errorCode != 0)
                {
                    System_printf("CFAR DPU process error %d\n", errorCode);
                    DebugP_assert(0);
                    goto exit;;
                }
                /* check the results */
                System_printf("Check DPU Process output: ");
                Test_printResults();
                System_printf("\n");

                /* check the cfar command */
                if (((testCount & 0x3) == 0)  & (numCheckPeaksRef<TEST_MAX_NUM_CFARDETOBJ_DPU_LIST))
                {
                    if (cfarTestCfg.numDopplerBins > 16)
                    {
                        cfarTestCfg.dpuControlFlag = 1;   //doppler fov
                    }
                    else
                    {
                        cfarTestCfg.dpuControlFlag = 0;  //range fov
                    }
                }
                else if (((testCount & 0x3) == 1) & (numCheckPeaksRef<TEST_MAX_NUM_CFARDETOBJ_DPU_LIST))
                {
                    cfarTestCfg.dpuControlFlag = 0; //range fov
                }
                else if ((testCount & 0x3) == 2)
                {
                    cfarTestCfg.dpuControlFlag = 3; //range cfar
                }
                else
                {
                    if (cfarTestCfg.dopplerCfarEnabled)
                    {
                        cfarTestCfg.dpuControlFlag = 2;//doppler cfar
                    }
                    else
                    {
                        cfarTestCfg.dpuControlFlag = 3; //range cfar
                    }
                }
               
                if (cfarTestCfg.dpuControlFlag == 0)
                {
                    System_printf("Check DPU Cmd_FovRangeCfg output: ");
                }
                else if (cfarTestCfg.dpuControlFlag == 1)
                {
                    System_printf("Check DPU Cmd_FovDopplerCfg output: ");
                }
                else if (cfarTestCfg.dpuControlFlag == 2)
                {
                    System_printf("Check DPU Cmd_CfarDopplerCfg output: ");
                }
                else
                {
                    System_printf("Check DPU Cmd_CfarRangeCfg output: ");
                }
                test_dpu_control_cmd(&cfarTestCfg);
                if (cfarTestCfg.dpuControlFlag > 1) //cfar change, need to recalute the reference
                {
                    Test_gen_detobj_ref(&cfarTestCfg);
                    numCheckPeaksRef = numDetPeaksRef;
                }
                else   //update the previous results only
                {
                    Test_update_detobj_ref(&cfarTestCfg);
                }
                errorCode = DPU_CFARCAProcHWA_process(cfarDpuHandle, &cfarDpuOut);
                if (errorCode != 0)
                {
                    System_printf("CFAR DPU process error %d\n", errorCode);
                    DebugP_assert(0);
                    goto exit;
                }

                Test_printResults();
                
                System_printf("\n\n");

                testCount++;
            }  /* end of kk loop */
             
        }   /* end of range bin loop */
    } /* end of doppler bin loop */

    
    System_printf("----------------------------------------\n\n");
    if (finalResults == 1)
    {
        System_printf("All Tests PASSED!\n");
        MCPI_setFeatureTestResult("CFAR_DPU", MCPI_TestResult_PASS);
    }
    else
    {
        System_printf("Test FAILED!\n");
        MCPI_setFeatureTestResult("CFAR_DPU", MCPI_TestResult_FAIL);
    }

    System_printf("Test Finished\n");

    MCPI_setTestResult();

exit:
    if (fileId != NULL)
    {
        fclose(fileId);
    }
    EDMA_close(edmaHandle);
    HWA_close(hwaHandle);
    errorCode = DPU_CFARCAProcHWA_deinit(cfarDpuHandle);
    if (errorCode != 0)
    {
        System_printf("CFAR DPU DE_INIT fail\n");
        DebugP_assert(0);        
    }   
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


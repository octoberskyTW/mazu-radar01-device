/**
 *   @file  cfarcaprocdsp.c
 *
 *   @brief
 *      Implements Data path processing Unit using DSP.
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

/**************************************************************************
 *************************** Include Files ********************************
 **************************************************************************/

/* Standard Include Files. */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/* mmWave SDK drivers/common Include Files */
#include <ti/common/sys_common.h>
#include <ti/drivers/osal/SemaphoreP.h>
#include <ti/drivers/osal/MemoryP.h>
#include <ti/drivers/edma/edma.h>
#include <ti/drivers/esm/esm.h>
#include <ti/drivers/soc/soc.h>

/* Data Path Include Files */
#include <ti/datapath/dpedma/dpedma.h>
#include <ti/datapath/dpc/dpu/cfarcaproc/include/cfarcaprocdspinternal.h>
#include <ti/datapath/dpc/dpu/cfarcaproc/cfarcaprocdsp.h>
#include <ti/alg/mmwavelib/mmwavelib.h>

/**************************************************************************
 **************************** Internal Functions *******************************
 **************************************************************************/
static int32_t CFARCADSP_configEDMADopplerDomain
(
    DPU_CFARCAProcDSP_HW_Resources *pRes,
    DPU_CFARCAProcDSP_StaticConfig  *staticCfg
);
static int32_t CFARCADSP_configEDMARangeDomain
(
    EDMA_Handle         edmaHandle,
    DPEDMA_ChanCfg      *pEdmaChan,
    DPU_CFARCAProcDSP_StaticConfig *staticCfg,
    uint32_t            srcAddr,
    uint32_t            dstAddr
);
static void CFARCADSP_waitEDMATransComplete
(
    EDMA_Handle         edmaHandle,
    uint8_t             chId
);
static void CFARCADSP_fovConvertRange
(
    DPU_CFARCAProc_FovCfg    *fovRangeCfg,
    float                    rangeStep,
    DPU_CFARCAProc_FovIdxCfg *fovRangeIdxCfg
);
static void CFARCADSP_fovConvertDoppler
(
    DPU_CFARCAProc_FovCfg    *fovDopplerCfg,
    float                    dopplerStep,
    DPU_CFARCAProc_FovIdxCfg *fovDopplerIdxCfg
);
static void CFARCADSP_saveConfiguration
(
    CFARCADspObj * cfarDspObj,
    DPU_CFARCAProcDSP_Config *cfarDspCfg
);
static bool CFARCADSP_isObjectDetectedOnDopplerLine
(
    uint32_t dopplerIdx,
    uint32_t numDopplerBins,
    uint32_t numRangeBins,
    uint32_t *cfarDetOutBitMask
);
static void CFARCADSP_setCfarDetMaskLine
(
    uint32_t rangeInd,
    uint32_t dopplerInd,
    uint32_t numDopplerBins,
    uint32_t *cfarDetOutBitMask
);
static uint32_t CFARCADSP_peakGrouping
(
    CFARCADspObj      *cfarObj,
    uint16_t          numDetectedObjs
);
static int32_t CFARCADSP_processDopplerDomain
(
    CFARCADspObj    *cfarObj,
    uint8_t         peakGrpingEn,
    uint32_t        *waitingTime,
    int32_t         *errCode
);
static int32_t CFARCADSP_processRangeDomain
(
    CFARCADspObj    *cfarObj,
    uint8_t         peakGrpingEn,
    uint32_t        *waitingTime,
    uint32_t        numDetObjDoppler
);

static uint32_t CFARCADSP_cfarCadBwrap(const uint16_t inp[restrict],
                                uint16_t out[restrict], uint32_t len,
                                uint32_t const1, uint32_t const2,
                                uint32_t guardLen, uint32_t noiseLen,
                                uint16_t noise[restrict]);

static uint32_t CFARCADSP_cfarCadB_SOGO(const uint16_t inp[restrict],
                            uint16_t out[restrict], uint32_t len,
                            uint16_t cfartype,
                            uint32_t const1, uint32_t const2,
                            uint32_t guardLen, uint32_t noiseLen,
                            uint16_t noise[restrict]);

/**
 *  @b Description
 *  @n
 *      Configures EDMA in CFAR Doppler domain.Each tranfer copies all doppler
 *      bins, it repeats for all range bins in ping/pong manner.
 *
 *  @param[in] pRes         Pointer to hardware resources
 *  @param[in] staticCfg    Pointer to static configuration
 *
 *  \ingroup    DPU_CFARCAPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 *
 */
static int32_t CFARCADSP_configEDMADopplerDomain
(
    DPU_CFARCAProcDSP_HW_Resources *pRes,
    DPU_CFARCAProcDSP_StaticConfig  *staticCfg
)
{
    int32_t errorCode = EDMA_NO_ERROR;
    DPEDMA_syncACfg     syncACfg;

    /* Common EDMA setting between ping and pong */
    syncACfg.aCount      = staticCfg->numDopplerBins * sizeof(uint16_t);
    syncACfg.bCount      = (staticCfg->numRangeBins) /2;
    syncACfg.srcBIdx     = syncACfg.aCount * 2;
    syncACfg.dstBIdx     = 0;

    /* Ping source and destination setting */
    syncACfg.srcAddress  = (uint32_t)pRes->detMatrix.data;
    syncACfg.destAddress = (uint32_t)pRes->localDetMatrixBuffer;

    errorCode = DPEDMA_configSyncA_singleFrame(pRes->edmaHandle,
                                   &pRes->edmaInPing,
                                   NULL,
                                   &syncACfg,
                                   false, //isEventTriggered
                                   true,//isIntermediateTransferInterruptEnabled
                                   true,//isTransferCompletionEnabled
                                   NULL, //transferCompletionCallbackFxn
                                   NULL);//transferCompletionCallbackFxnArg
    if (errorCode != EDMA_NO_ERROR)
    {
        goto exit;
    }

    /* Pong source and destination setting */
    syncACfg.srcAddress  = (uint32_t)pRes->detMatrix.data + syncACfg.aCount;
    syncACfg.destAddress = (uint32_t)pRes->localDetMatrixBuffer + syncACfg.aCount;
    syncACfg.bCount      = (staticCfg->numRangeBins)/2;

    errorCode = DPEDMA_configSyncA_singleFrame(pRes->edmaHandle,
                                   &pRes->edmaInPong,
                                   NULL,
                                   &syncACfg,
                                   false, //isEventTriggered
                                   true,//isIntermediateTransferInterruptEnabled
                                   true,//isTransferCompletionEnabled
                                   NULL, //transferCompletionCallbackFxn
                                   NULL);//transferCompletionCallbackFxnArg
    if (errorCode != EDMA_NO_ERROR)
    {
        goto exit;
    }

exit:
    return(errorCode);
}

/**
 *  @b Description
 *  @n
 *      Configures EDMA in CFAR Range domain. It copies all range
 *      bins for one doppler Line.
 *
 *  @param[in] edmaHandle   EDMA driver handle
 *  @param[in] pEdmaChan    EDMA channel configuration
 *  @param[in] staticCfg    Pointer to static configuration
 *  @param[in] srcAddr      Source address of EDMA copy
 *  @param[in] dstAddr      Destination address of EDMA copy
 *
 *  \ingroup    DPU_CFARCAPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 *
 */
static int32_t CFARCADSP_configEDMARangeDomain
(
    EDMA_Handle         edmaHandle,
    DPEDMA_ChanCfg      *pEdmaChan,
    DPU_CFARCAProcDSP_StaticConfig *staticCfg,
    uint32_t            srcAddr,
    uint32_t            dstAddr
)
{
    int32_t errorCode = EDMA_NO_ERROR;
    DPEDMA_syncABCfg     syncABCfg;

    syncABCfg.aCount      = sizeof(uint16_t);
    syncABCfg.bCount      = staticCfg->numRangeBins;
    syncABCfg.cCount      = 1;
    syncABCfg.srcBIdx     = sizeof(uint16_t) * staticCfg->numDopplerBins;
    syncABCfg.dstBIdx     = sizeof(uint16_t);
    syncABCfg.srcCIdx     = 0;
    syncABCfg.dstCIdx     = 0;

    syncABCfg.srcAddress  = srcAddr;
    syncABCfg.destAddress  = dstAddr;

    errorCode = DPEDMA_configSyncAB(edmaHandle,
                                   pEdmaChan,
                                   NULL,
                                   &syncABCfg,
                                   false, //isEventTriggered
                                   true,//isIntermediateTransferInterruptEnabled
                                   true,//isTransferCompletionEnabled
                                   NULL, //transferCompletionCallbackFxn
                                   NULL);//transferCompletionCallbackFxnArg
    if (errorCode != EDMA_NO_ERROR)
    {
        goto exit;
    }

exit:
    return(errorCode);
}

/**
 *  @b Description
 *  @n
 *      Waits for EDMA channel to complete.
 *      This is a blocking function.
 *
 *  @param[in] edmaHandle   EDMA driver handle
 *  @param[in] chId         EDMA channel Id
 *
 *  \ingroup    DPU_CFARCAPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      None
 *
 */
static void CFARCADSP_waitEDMATransComplete
(
    EDMA_Handle         edmaHandle,
    uint8_t             chId
)
{
    volatile bool isTransferDone;
    do {
        if (EDMA_isTransferComplete(edmaHandle,
                                    (uint8_t) chId,
                                    (bool *)&isTransferDone) != EDMA_NO_ERROR)
        {
        }
    } while (isTransferDone == false);
}


/**
 *  @b Description
 *  @n  Adjust noiseDivShift for different CFAR averaging modes
 *
 *  @param[inout] pCfarCfg   CFAR CFG that needs adjustment
 *
 *  \ingroup    DPU_CFARCAPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      None
 *
 */
static void CFARCADSP_adjustCfarCfg
(
    DPU_CFARCAProc_CfarCfg    *pCfarCfg
)
{
    if (pCfarCfg->averageMode != 0)//cfar so, or go
    {
        /* For CAGO and CASO mode, lib function CFARCADSP_cfarCadB_SOGO expects 
         * noiseDivShift to be specified for both left and right window whereas 
         * IOCTL structure expects noiseDivShift to be specified for one side only.
         * Hence increment the shift by 1.
         */
        pCfarCfg->noiseDivShift = pCfarCfg->noiseDivShift + 1;
    }
}


/**
 *  @b Description
 *  @n  Convert range field of view meters to indices
 *
 *  @param[in] fovRangeCfg   Field of view configuration for range (units in meters)
 *  @param[in] rangeStep     Range resolution
 *  @param[out] fovRangeIdxCfg  Field of view configuration for range (range indices)
 *
 *
 *  \ingroup    DPU_CFARCAPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      None
 *
 */
static void CFARCADSP_fovConvertRange
(
    DPU_CFARCAProc_FovCfg    *fovRangeCfg,
    float                    rangeStep,
    DPU_CFARCAProc_FovIdxCfg *fovRangeIdxCfg
)
{
    fovRangeIdxCfg->minIdx = (int16_t) (fovRangeCfg->min / rangeStep + 0.5);
    fovRangeIdxCfg->maxIdx = (int16_t) (fovRangeCfg->max / rangeStep + 0.5);
}


/**
 *  @b Description
 *  @n  Convert Doppler field of view meters to indices
 *
 *  @param[in] fovDopplerCfg   Field of view configuration for Doppler (units in meters/sec)
 *  @param[in] dopplerStep     Doppler resolution
 *  @param[out] fovDopplerIdxCfg Field of view configuration for Doppler (doppler indices)
 *
 *
 *  \ingroup    DPU_CFARCAPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      None
 *
 */
static void CFARCADSP_fovConvertDoppler
(
    DPU_CFARCAProc_FovCfg    *fovDopplerCfg,
    float                    dopplerStep,
    DPU_CFARCAProc_FovIdxCfg *fovDopplerIdxCfg
)
{
    float doppler;

    doppler = (fovDopplerCfg->min / dopplerStep);
    if (doppler < 0.)
    {
        doppler -= .5;
    }
    else
    {
        doppler += .5;

    }
    fovDopplerIdxCfg->minIdx = (int16_t) doppler;

    doppler = (fovDopplerCfg->max / dopplerStep);
    if (doppler < 0.)
    {
        doppler -= .5;
    }
    else
    {
        doppler += .5;

    }
    fovDopplerIdxCfg->maxIdx = (int16_t) doppler;
}

/**
 *  @b Description
 *  @n  Saves configuration parameters to CFAR instance
 *
 *  @param[in] cfarDspObj   Pointer to CFAR DPU object
 *  @param[in] cfarDspCfg   Pointer to CFAR DPU configuration
 *
 *  \ingroup    DPU_CFARCAPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      None
 *
 */
static void CFARCADSP_saveConfiguration
(
    CFARCADspObj * cfarDspObj,
    DPU_CFARCAProcDSP_Config *cfarDspCfg
)
{
    cfarDspObj->staticCfg = cfarDspCfg->staticCfg;
    cfarDspObj->res = cfarDspCfg->res;
    cfarDspObj->cfarCfgDoppler = *cfarDspCfg->dynCfg.cfarCfgDoppler;
    cfarDspObj->cfarCfgRange = *cfarDspCfg->dynCfg.cfarCfgRange;
    cfarDspObj->staticCfg = cfarDspCfg->staticCfg;

    CFARCADSP_fovConvertDoppler(cfarDspCfg->dynCfg.fovDoppler,
                              cfarDspObj->staticCfg.dopplerStep,
                              &cfarDspObj->fovDoppler);

    CFARCADSP_fovConvertRange(cfarDspCfg->dynCfg.fovRange,
                            cfarDspObj->staticCfg.rangeStep,
                            &cfarDspObj->fovRange);
    CFARCADSP_adjustCfarCfg(&cfarDspObj->cfarCfgRange);
    CFARCADSP_adjustCfarCfg(&cfarDspObj->cfarCfgDoppler);
}

/**
 *  @b Description
 *  @n
 *     Checks if an object is detected at a doppler index.
 *
 *  @param[in] dopplerIdx           Doppler index
 *  @param[in] numDopplerBins       Number of Doppler bins (must be power of 2)
 *  @param[in] numRangeBins         Number of Range bins (must be power of 2)
 *  @param[in] cfarDetOutBitMask    Pointer to output bit mask (compressed list)
 *
 *  \ingroup    DPU_CFARCAPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      true     - Object found in CFAR detection bit mask
 *  @retval
 *      false    - Object not found in CFAR detection bit mask
 */
static bool CFARCADSP_isObjectDetectedOnDopplerLine
(
    uint32_t dopplerIdx,
    uint32_t numDopplerBins,
    uint32_t numRangeBins,
    uint32_t *cfarDetOutBitMask
)
{
    uint32_t bit, word;
    uint32_t bitIndex;
    uint32_t rangeIdx;
    bool   detected = false;

    for(rangeIdx = 0; rangeIdx < numRangeBins;rangeIdx++)
    {
        bitIndex = rangeIdx * numDopplerBins + dopplerIdx;
        word = bitIndex >> 5;
        bit = bitIndex & 31;
        if (cfarDetOutBitMask[word] & (1 << bit))
        {
           detected = true;
           break;
        }
    }
    return(detected);
}

/**
 *  @b Description
 *  @n
 *     Checks if an object is detected at a given range index and doppler index.
 *
 *  @param[in] rangeIdx             Range index
 *  @param[in] dopplerIdx           Doppler index
 *  @param[in] numDopplerBins       Number of Doppler bins
 *  @param[in] cfarDetOutBitMask    Pointer to output bit mask (compressed list)
 *
 *  \ingroup    DPU_CFARCAPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      true     - Object found in CFAR detection bit mask
 *  @retval
 *      false    - Object not found in CFAR detection bit mask
 */
static bool CFARCADSP_isObjectDetected
(
    uint32_t rangeIdx,
    uint32_t dopplerIdx,
    uint32_t numDopplerBins,
    uint32_t *cfarDetOutBitMask
)
{
    uint32_t bit, word;
    uint32_t bitIndex;
    bool   detected = false;

    bitIndex = rangeIdx * numDopplerBins + dopplerIdx;
    word = bitIndex >> 5;
    bit = bitIndex & 31;
    if (cfarDetOutBitMask[word] & (1 << bit))
    {
       detected = true;
    }
    return(detected);
}

/**
 *  @b Description
 *  @n
 *     Set bit mask if an object is detected with range/doppler index pair.
 *
 *  @param[in] rangeInd     Range index
 *  @param[in] dopplerInd   Doppler index
 *  @param[in] numDopplerBins       Number of Doppler bins (must be power of 2)
 *  @param[in] cfarDetOutBitMask    Pointer to output bit mask (compressed list)
 *
 *  \ingroup    DPU_CFARCAPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      None
 *
 */
static void CFARCADSP_setCfarDetMaskLine
(
    uint32_t rangeInd,
    uint32_t dopplerInd,
    uint32_t numDopplerBins,
    uint32_t *cfarDetOutBitMask
)
{
    uint32_t word;
    uint32_t bit;
    uint32_t bitIndex;

    bitIndex = rangeInd * numDopplerBins + dopplerInd;
    word = bitIndex >> 5;
    bit = bitIndex & 31;

    cfarDetOutBitMask[word] |= (0x1 << bit);
}


/* The following functions are from mmwavelib with additional output noise buffer.*/

/*!*****************************************************************************************************************
 * \brief
 * Function Name       :    CFARCADSP_cfarCadBwrap
 *
 * \par
 * <b>Description</b>  :    Performs a CFAR on an 16-bit unsigned input vector (CFAR-CA). The input values are assumed to be
 *                          in lograthimic scale. So the comparision between the CUT and the noise samples is additive
 *                          rather than multiplicative. Comparison is two-sided (wrap around when needed) for all CUTs.
 *
 * @param[in]               inp      : input array (16 bit unsigned numbers)
 * @param[out]              out      : output array with indices of detected peaks (zero based counting)
 * @param[in]               len      : number of elements in input array
 * @param[in]               const1,const2 : used to compare the Cell Under Test (CUT) to the sum of the noise cells:
 *                                          [noise sum /(2^(const2))] +const1 for two sided comparison.
 * @param[in]               guardLen : one sided guard length
 * @param[in]               noiseLen : one sided Noise length
 *
 * @param[out]              noise    : output array with each detected peak's noise floor (noise sum /(2^(const2)))
 *
 * @return                  Number of detected peaks (i.e length of out)
 *
 * @pre                     Input (inp) and Output (out) arrays are non-aliased.
 * @ingroup                 DPU_CFARCAPROC_INTERNAL_FUNCTION
 *
 * Cycles (cgt 8.1.3)       4*len + 169
 *******************************************************************************************************************
 */
static uint32_t CFARCADSP_cfarCadBwrap(const uint16_t inp[restrict],
                                uint16_t out[restrict], uint32_t len,
                                uint32_t const1, uint32_t const2,
                                uint32_t guardLen, uint32_t noiseLen,
                                uint16_t noise[restrict])
{
    uint32_t idx, idxLeftNext, idxLeftPrev, idxRightNext, idxRightPrev, outIdx;
    uint32_t idxCUT;
    uint32_t sum, sumLeft, sumRight;

    /*initializations */
    outIdx = 0U;
    sumLeft = 0U;
    sumRight = 0U;
    for (idx = 1U; idx <= noiseLen; idx++)
    {
        sumLeft += inp[len - guardLen - idx];
    }

    for (idx = 1U; idx <= noiseLen; idx++)
    {
        sumRight += inp[idx + guardLen];
    }

    /*CUT 0: */
    sum = sumLeft + sumRight;
    if ((uint32_t) inp[0] > ((sum >> const2) + const1))
    {
        out[outIdx] = 0U;
        noise[outIdx] = sum >> const2;
        outIdx++;
    }

    /* CUT 1 to guardLen: */
    idxLeftPrev = len - guardLen - noiseLen;    /*e.g. 32-4-8 = 20 */
    idxLeftNext = idxLeftPrev + noiseLen; /*e.g. 28 */
    idxRightPrev = 1U + guardLen;    /*e.g. 1+4=5 */
    idxRightNext = idxRightPrev + noiseLen;   /*e.g. 13 */
    for (idxCUT = 1U; idxCUT <= guardLen; idxCUT++)
    {
        sumLeft = (sumLeft + inp[idxLeftNext]) - inp[idxLeftPrev];
        idxLeftNext++;
        idxLeftPrev++;
        sumRight = (sumRight + inp[idxRightNext]) - inp[idxRightPrev];
        idxRightNext++;
        idxRightPrev++;
        sum = sumLeft + sumRight;
        if ((uint32_t) (inp[idxCUT]) > ((sum >> const2) + const1))
        {
            out[outIdx] = (uint16_t)idxCUT;
            noise[outIdx] = sum >> const2;
            outIdx++;
        }
    }

    /* CUT guardLen+1 to guardLen+noiseLen: e.g. CUT 5 to 12 */
    idxLeftNext = 0U;
    for (idxCUT = (guardLen + 1U); idxCUT <= (guardLen + noiseLen);
         idxCUT++)
    {
        sumLeft = (sumLeft + inp[idxLeftNext]) - inp[idxLeftPrev];
        idxLeftNext++;
        idxLeftPrev++;
        sumRight = (sumRight + inp[idxRightNext]) - inp[idxRightPrev];
        idxRightNext++;
        idxRightPrev++;
        sum = sumLeft + sumRight;
        if ((uint32_t) (inp[idxCUT]) > ((sum >> const2) + const1))
        {
            out[outIdx] = (uint16_t)idxCUT;
            noise[outIdx] = sum >> const2;
            outIdx++;
        }
    }

    /* CUTs in the middle. e.g. CUT 13 to 19 */
    idxLeftPrev = 0U;
    for (idxCUT = (guardLen + noiseLen + 1U);
         idxCUT < (len - (noiseLen + guardLen)); idxCUT++)
    {
        sumLeft = (sumLeft + inp[idxLeftNext]) - inp[idxLeftPrev];
        idxLeftNext++;
        idxLeftPrev++;
        sumRight = (sumRight + inp[idxRightNext]) - inp[idxRightPrev];
        idxRightNext++;
        idxRightPrev++;
        sum = sumLeft + sumRight; /*CFAR-CA */
        /*sum=(sumLeft>sumRight)?sumLeft:sumRight;//CFAR-CA-GO */
        if ((uint32_t) (inp[idxCUT]) > ((sum >> const2) + const1))
        {
            out[outIdx] = (uint16_t)idxCUT;
            noise[outIdx] = sum >> const2;
            outIdx++;
        }
    }

    /*********************************************************************************************/
    /* noiseLen number of CUTs before the last guardLen CUTs. e.g. CUT 20 to 27 */
    idxRightNext = 0U;
    for (idxCUT = (len - (noiseLen + guardLen));
         idxCUT < (len - guardLen); idxCUT++)
    {
        sumLeft = (sumLeft + inp[idxLeftNext]) - inp[idxLeftPrev];
        idxLeftNext++;
        idxLeftPrev++;
        sumRight = (sumRight + inp[idxRightNext]) - inp[idxRightPrev];
        idxRightNext++;
        idxRightPrev++;
        sum = sumLeft + sumRight;
        if ((uint32_t) (inp[idxCUT]) > ((sum >> const2) + const1))
        {
            out[outIdx] = (uint16_t)idxCUT;
            noise[outIdx] = sum >> const2;
            outIdx++;
        }
    }

    /* The last guardLen number of CUTs */
    idxRightPrev = 0U;
    for (idxCUT = (len - guardLen); idxCUT < len; idxCUT++)
    {
        sumLeft = (sumLeft + inp[idxLeftNext]) - inp[idxLeftPrev];
        idxLeftNext++;
        idxLeftPrev++;
        sumRight = (sumRight + inp[idxRightNext]) - inp[idxRightPrev];
        idxRightNext++;
        idxRightPrev++;
        sum = sumLeft + sumRight;
        if ((uint32_t) (inp[idxCUT]) > ((sum >> const2) + const1))
        {
            out[outIdx] = (uint16_t)idxCUT;
            noise[outIdx] = sum >> const2;
            outIdx++;
        }
    }

    return (outIdx);

}  /* CFARCADSP_cfarCadBwrap */


/*!*****************************************************************************************************************
 * \brief
 * Function Name       :    CFARCADSP_cfarCadB_SOGO
 *
 * \par
 * <b>Description</b>  :    Performs a CFAR on an 16-bit unsigned input vector. The input values are assumed to be
 *                          in lograthimic scale. So the comparision between the CUT and the noise samples is additive
 *                          rather than multiplicative. Supports CA, CA SO, and CA GO.
 *
 * @param[in]               inp         : input array (16 bit unsigned numbers)
 * @param[in]               out         : output array (indices of detected peaks (zero based counting))
 * @param[in]               len         : number of elements in input array
 * @param[in]               cfartype    : type of noise floor calculation when two sides of noise available.
 *                                        CFAR_CA; use sum of both sides then average.
 *                                        CFAR_CASO; use smaller of the left and right side.
 *                                        CFAR_CAGO; use greater of the left and right side.
 * @param[in]               const1,const2 : used to compare the Cell Under Test (CUT) to the sum of the noise cells:
 *                                          [noise sum /(2^(const2-1))]+const1 for one sided comparison
 *                                          (at the begining and end of the input vector).
 *                                          [noise sum /(2^(const2))]+const1 for two sided comparison
 * @param[in]               guardLen    : one sided guard length
 * @param[in]               noiseLen    : one sided noise length
 *
 * @param[out]              noise       : output array with each detected peak's noise floor estimate
 *
 * @return                  Number of detected peaks (i.e length of out)
 *
 * @pre                     Input (inp) and Output (out, noise) arrays are non-aliased.
 * @ingroup                 DPU_CFARCAPROC_INTERNAL_FUNCTION
 *
 * Cycles (cgt 8.1.3)       type CA: 4*len +111; type CASO: 4*len +114; type CAGO: 4*len +108
 *******************************************************************************************************************
 */
static uint32_t CFARCADSP_cfarCadB_SOGO(const uint16_t inp[restrict],
                            uint16_t out[restrict], uint32_t len,
                            uint16_t cfartype,
                            uint32_t const1, uint32_t const2,
                            uint32_t guardLen, uint32_t noiseLen,
                            uint16_t noise[restrict])
{
    uint32_t idx, idxLeftNext, idxLeftPrev, idxRightNext,
             idxRightPrev, outIdx, idxCUT;
    uint32_t sum, sumLeft, sumRight;

    /* initializations */
    outIdx = 0;
    sumLeft = 0;
    sumRight = 0;
    for (idx = 0; idx < noiseLen; idx++)
    {
        sumRight += inp[idx + guardLen + 1U];
    }

    /*********************************************************************************************/
    /* One-sided comparision for the first segment (for the first noiseLen+gaurdLen samples */
    idxCUT = 0;
    if ((uint32_t) inp[idxCUT] > ((sumRight >> (const2 - 1U)) + const1))
    {
        out[outIdx] = (uint16_t)idxCUT;
        noise[outIdx] = sumRight >> (const2-1U);
        outIdx++;
    }
    idxCUT++;

    idxLeftNext = 0;
    idxRightPrev = idxCUT + guardLen;
    idxRightNext = idxRightPrev + noiseLen;
    for (idx = 0; idx < (noiseLen + guardLen - 1U); idx++)
    {
        sumRight = (sumRight + inp[idxRightNext]) - inp[idxRightPrev];
        idxRightNext++;
        idxRightPrev++;

        if (idx < noiseLen)
        {
            sumLeft += inp[idxLeftNext];
            idxLeftNext++;
        }

        if ((uint32_t) inp[idxCUT] > ((sumRight >> (const2 - 1U)) + const1))
        {
            out[outIdx] = (uint16_t)idxCUT;
            noise[outIdx] = sumRight >> (const2-1U);
            outIdx++;
        }
        idxCUT++;
    }

    /*********************************************************************************************/
    /* Two-sided comparision for the middle segment */
    sumRight = (sumRight + inp[idxRightNext]) - inp[idxRightPrev];
    idxRightNext++;
    idxRightPrev++;

    if (cfartype == CFAR_CA)
    {
        sum = sumRight + sumLeft;
        if ((uint32_t) inp[idxCUT] > ((sum >> const2) + const1))
        {
            out[outIdx] = (uint16_t)idxCUT;
            noise[outIdx] = sum >> const2;
            outIdx++;
        }
        idxCUT++;

        idxLeftPrev = 0;
        for (idx = 0; idx < (len - 2U*(noiseLen + guardLen) - 1U); idx++)
        {
            sumLeft = (sumLeft + inp[idxLeftNext]) - inp[idxLeftPrev];
            sumRight = (sumRight + inp[idxRightNext]) - inp[idxRightPrev];
            idxLeftNext++;
            idxLeftPrev++;
            idxRightNext++;
            idxRightPrev++;
            sum = sumLeft + sumRight;

            if ((uint32_t) (inp[idxCUT]) > ((sum >> const2) + const1))
            {
                out[outIdx] = (uint16_t)idxCUT;
                noise[outIdx] = sum >> const2;
                outIdx++;
            }
            idxCUT++;
        }
    } /*CFAR_CA*/
    else if (cfartype == CFAR_CASO)
    {
        sum = (sumLeft < sumRight) ? sumLeft:sumRight;
        if ((uint32_t) inp[idxCUT] > ((sum >> (const2-1U)) + const1))
        {
            out[outIdx] = (uint16_t)idxCUT;
            noise[outIdx] = sum >> (const2-1U);
            outIdx++;
        }
        idxCUT++;

        idxLeftPrev = 0;
        for (idx = 0; idx < (len - 2U*(noiseLen + guardLen) - 1U); idx++)
        {
            sumLeft = (sumLeft + inp[idxLeftNext]) - inp[idxLeftPrev];
            sumRight = (sumRight + inp[idxRightNext]) - inp[idxRightPrev];
            idxLeftNext++;
            idxLeftPrev++;
            idxRightNext++;
            idxRightPrev++;

            sum = (sumLeft < sumRight) ? sumLeft:sumRight;

            if ((uint32_t) (inp[idxCUT]) > ((sum >> (const2-1U)) + const1))
            {
                out[outIdx] = (uint16_t)idxCUT;
                noise[outIdx] = sum >> (const2-1U);
                outIdx++;
            }
            idxCUT++;
        }
    } /*CFAR_CASO*/
    else /*CFAR_CAGO*/
    {
        sum = (sumLeft > sumRight) ? sumLeft:sumRight;
        if ((uint32_t) inp[idxCUT] > ((sum >> (const2-1U)) + const1))
        {
            out[outIdx] = (uint16_t)idxCUT;
            noise[outIdx] = sum >> (const2-1U);
            outIdx++;
        }
        idxCUT++;

        idxLeftPrev = 0;
        sum = sumLeft + sumRight;
        for (idx = 0; idx < (len - 2U*(noiseLen + guardLen) - 1U); idx++)
        {
            sumLeft = (sumLeft + inp[idxLeftNext]) - inp[idxLeftPrev];
            sumRight = (sumRight + inp[idxRightNext]) - inp[idxRightPrev];
            idxLeftNext++;
            idxLeftPrev++;
            idxRightNext++;
            idxRightPrev++;

            sum = (sumLeft > sumRight) ? sumLeft:sumRight;

            if ((uint32_t) (inp[idxCUT]) > ((sum >> (const2-1U)) + const1))
            {
                out[outIdx] = (uint16_t)idxCUT;
                noise[outIdx] = sum >> (const2-1U);
                outIdx++;
            }
            idxCUT++;
         }
    } /*CFAR_CAGO*/

    /*********************************************************************************************/
    /* One-sided comparision for the last segment (for the last noiseLen+gaurdLen samples) */
    for (idx = 0; idx < (noiseLen + guardLen); idx++)
    {
        sumLeft = (sumLeft + inp[idxLeftNext]) - inp[idxLeftPrev];
        idxLeftNext++;
        idxLeftPrev++;
        if ((uint32_t) inp[idxCUT] > ((sumLeft >> (const2 - 1U)) + const1))
        {
            out[outIdx] = (uint16_t)idxCUT;
            noise[outIdx] = sumLeft >> (const2-1U);
            outIdx++;
        }
        idxCUT++;
    }
    /*********************************************************************************************/

    return (outIdx);

}  /* CFARCADSP_cfarCadB_SOGO */

/**
 *  @b Description
 *  @n
 *     Peak grouping procesd
 *
 *  @param[in] cfarObj              Pointer to CFAR DPU object
 *  @param[in] numDetectedObjs      number of raw detected objects before peak grouping
 *
 *  \ingroup    DPU_CFARCAPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      Number of detected objects after peak grouping
 *
 */
static uint32_t CFARCADSP_peakGrouping
(
    CFARCADspObj      *cfarObj,
    uint16_t          numDetectedObjs
)
{
    uint16_t detIdx;
    uint16_t numPeakGrp = 0;
    uint16_t index;
    uint8_t scheme;

    if(cfarObj->cfarCfgRange.peakGroupingEn)
    {
        scheme = cfarObj->cfarCfgRange.peakGroupingScheme;
    }
    else
    {
        scheme = cfarObj->cfarCfgDoppler.peakGroupingScheme;
    }

    if (scheme == DPU_CFAR_PEAK_GROUPING_CFAR_PEAK_BASED)
    {
        numPeakGrp = mmwavelib_cfarPeakQualifiedInOrderPruning(cfarObj->detObjPeakIdxBuf,   /* output the peak index after the group */
                     cfarObj->detObjRangeIdxBuf, /* raw detection range index */
                     cfarObj->detObjDopplerIdxBuf, /* raw detection doppler index */
                     cfarObj->detObjPeakValBuf, /* raw detection peak value */
                     numDetectedObjs,       /* number of raw detection peaks */
                     cfarObj->staticCfg.numDopplerBins, /* number of doppler bins */
                     cfarObj->fovRange.maxIdx, /* maximum range bin */
                     cfarObj->fovRange.minIdx, /* minimum range bin */
                     cfarObj->cfarCfgDoppler.peakGroupingEn, /* doppler direction group */
                     cfarObj->cfarCfgRange.peakGroupingEn,  /* range direction group */
                     cfarObj->res.cfarRngDopSnrListSize/* maximum grouped peaks */
                    );

    }
    else if (scheme == DPU_CFAR_PEAK_GROUPING_DET_MATRIX_BASED)
    {
        numPeakGrp = mmwavelib_cfarPeakPruning (cfarObj->detObjPeakIdxBuf,
                     cfarObj->detObjRangeIdxBuf, /* raw detection range index */
                     cfarObj->detObjDopplerIdxBuf, /* raw detection doppler index */
                    numDetectedObjs,
                    (uint16_t *)cfarObj->res.detMatrix.data,
                    cfarObj->staticCfg.numDopplerBins, /* number of doppler bins */
                    cfarObj->fovRange.maxIdx, /* maximum range bin */
                    cfarObj->fovRange.minIdx, /* minimum range bin */
                    cfarObj->cfarCfgDoppler.peakGroupingEn, /* doppler direction group */
                    cfarObj->cfarCfgRange.peakGroupingEn,  /* range direction group */
                    cfarObj->res.cfarRngDopSnrListSize);
    }
    else
    {
        numPeakGrp = numDetectedObjs;
    }

    /* Based on the detObjPeakIdxBuf, construct detection list */
    for (index = 0; index < numPeakGrp; index ++)
    {
        float snrdB;

        detIdx = cfarObj->detObjPeakIdxBuf[index];
        cfarObj->res.cfarRngDopSnrList[index].rangeIdx = cfarObj->detObjRangeIdxBuf[detIdx];
        cfarObj->res.cfarRngDopSnrList[index].dopplerIdx = cfarObj->detObjDopplerIdxBuf[detIdx];
        cfarObj->res.cfarRngDopSnrList[index].noise = cfarObj->res.cfarRngDopSnrList[detIdx].noise;
        snrdB = CFARCADSP_CONV_PEAK_TO_LOG((float)cfarObj->detObjPeakValBuf[detIdx], DPIF_DETMATRIX_DATA_QFORMAT) - 
                    cfarObj->res.cfarRngDopSnrList[index].noise;
        cfarObj->res.cfarRngDopSnrList[index].snr = (int16_t)snrdB;
    }

    return(numPeakGrp);
}

/**
 *  @b Description
 *  @n
 *     CFAR processing in Doppler Domain.
 *
 *  @param[in] cfarObj          Pointer to CFAR DPU object
 *  @param[in] peakGrpingEn     Peak grouping enable flag
 *  @param[in] waitingTime      Pointer to waiting time involved during CFAR processing
 *  @param[in] errCode          Pointer to errCode to be populated during CFAR processing
 *
 *  \ingroup    DPU_CFARCAPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      Number of detected objects
 *
 */
static int32_t CFARCADSP_processDopplerDomain
(
    CFARCADspObj    *cfarObj,
    uint8_t         peakGrpingEn,
    uint32_t        *waitingTime,
    int32_t         *errCode
)
{
    uint32_t    numDetObjPerCfar;
    uint32_t    numDetObjDoppler = 0U;
    uint32_t    detIndex;
    uint16_t    rangeIdx;
    volatile uint32_t startTimeWait;

    /* Trigger both ping and pong channel */
    if ((*errCode = EDMA_startDmaTransfer(cfarObj->res.edmaHandle, cfarObj->res.edmaInPing.channel)) != EDMA_NO_ERROR)
    {
        goto exit;
    }
    if ((*errCode = EDMA_startDmaTransfer(cfarObj->res.edmaHandle, cfarObj->res.edmaInPong.channel)) != EDMA_NO_ERROR)
    {
        goto exit;
    }

    memset (cfarObj->res.cfarDopplerDetOutBitMask, 0x0, cfarObj->res.cfarDopplerDetOutBitMaskSize * sizeof(uint32_t));

    /* Loop through all range bins for CFAR detection */
    rangeIdx = 0;
    do
    {
        uint16_t *currDetMatrixBuffer;
        uint8_t edmaChannel;

        if(rangeIdx %2 == 0)
        {
            edmaChannel = cfarObj->res.edmaInPing.channel;
        }
        else
        {
            edmaChannel = cfarObj->res.edmaInPong.channel;
        }

        /* Calculate current local buffer base address */
        currDetMatrixBuffer = &cfarObj->res.localDetMatrixBuffer[cfarObj->staticCfg.numDopplerBins * (rangeIdx % 2)];

        /* Wait for EDMA transfer of current range line to complete */
        startTimeWait = Cycleprofiler_getTimeStamp();
        CFARCADSP_waitEDMATransComplete(cfarObj->res.edmaHandle, edmaChannel);
        *waitingTime += Cycleprofiler_getTimeStamp() - startTimeWait;

        /* CFAR-detecton on range line: search doppler peak among numDopplerBins samples */
        numDetObjPerCfar = CFARCADSP_cfarCadBwrap(
                currDetMatrixBuffer,
                cfarObj->res.cfarDetOutBuffer,
                cfarObj->staticCfg.numDopplerBins,
                cfarObj->cfarCfgDoppler.thresholdScale,
                cfarObj->cfarCfgDoppler.noiseDivShift,
                cfarObj->cfarCfgDoppler.guardLen,
                cfarObj->cfarCfgDoppler.winLen,
                cfarObj->detObjPeakIdxBuf);

        for (detIndex = 0; detIndex < numDetObjPerCfar; detIndex++)
        {
            uint16_t dopplerIndex;
            float noisedB;
            dopplerIndex = cfarObj->res.cfarDetOutBuffer[detIndex];

            /* Update detection bit mask */
            CFARCADSP_setCfarDetMaskLine(rangeIdx, dopplerIndex, cfarObj->staticCfg.numDopplerBins, cfarObj->res.cfarDopplerDetOutBitMask);

            /* Calculate noise and snr */
            noisedB = CFARCADSP_CONV_PEAK_TO_LOG((float)cfarObj->detObjPeakIdxBuf[detIndex], DPIF_DETMATRIX_DATA_QFORMAT);

            if (cfarObj->cfarCfgRange.thresholdScale > 0)
            {
                /* If RangeDomain CFAR is enabld, no need to save detected objects */
            }
            else
            {
                if(peakGrpingEn)
                {
                    cfarObj->detObjRangeIdxBuf[numDetObjDoppler] = rangeIdx;
                    cfarObj->detObjDopplerIdxBuf[numDetObjDoppler] = dopplerIndex;
                    cfarObj->detObjPeakValBuf[numDetObjDoppler] = currDetMatrixBuffer[dopplerIndex];
                    cfarObj->res.cfarRngDopSnrList[numDetObjDoppler].noise = (int16_t)noisedB;
                }
                else
                {
                    float snrdB;
                    snrdB = CFARCADSP_CONV_PEAK_TO_LOG((float)currDetMatrixBuffer[dopplerIndex], DPIF_DETMATRIX_DATA_QFORMAT) - noisedB;

                    /* Update detection list */
                    cfarObj->res.cfarRngDopSnrList[numDetObjDoppler].rangeIdx = rangeIdx;
                    cfarObj->res.cfarRngDopSnrList[numDetObjDoppler].dopplerIdx= dopplerIndex;
                    cfarObj->res.cfarRngDopSnrList[numDetObjDoppler].snr = snrdB;
                    cfarObj->res.cfarRngDopSnrList[numDetObjDoppler].noise = (int16_t)noisedB;
                }

                numDetObjDoppler ++;
                if(numDetObjDoppler >= cfarObj->res.cfarRngDopSnrListSize)
                {
                    /* Output is limited by cfarRngDopSnrList size */
                    goto exit;
                }
            }
        }
        rangeIdx++;

        /* Trigger next EDMA if it is not the last range Bins */
        if(rangeIdx < (cfarObj->staticCfg.numRangeBins - 1))
        {
            if ((*errCode = EDMA_startDmaTransfer(cfarObj->res.edmaHandle, edmaChannel)) != EDMA_NO_ERROR)
            {
                goto exit;
            }
        }
    }while(rangeIdx < cfarObj->staticCfg.numRangeBins);
exit:
    return numDetObjDoppler;
}

/**
 *  @b Description
 *  @n
 *     CFAR processing in Range Domain.
 *
 *  @param[in] cfarObj          Pointer to CFAR DPU object
 *  @param[in] peakGrpingEn     Peak grouping enable flag
 *  @param[in] waitingTime      Pointer to waiting time involved during CFAR processing
 *  @param[in] numDetObjDoppler  Number of detected object in doppler domain
 *
 *  \ingroup    DPU_CFARCAPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      Number of detected objects
 *
 */
static int32_t CFARCADSP_processRangeDomain
(
    CFARCADspObj    *cfarObj,
    uint8_t         peakGrpingEn,
    uint32_t        *waitingTime,
    uint32_t        numDetObjDoppler
)
{
    uint32_t            detIdx;
    uint32_t            numDetObjIndex = 0;
    volatile uint32_t   startTimeWait;
    uint32_t            dopplerLine;
    uint32_t            numDetObj;
    uint32_t            srcAddr;
    uint32_t            localBufferAddr;
    uint16_t            loopIndex = 0;
    uint16_t            oneDopplerBinSize;
    int16_t             dopplerSgnIdx;

    oneDopplerBinSize = cfarObj->staticCfg.numRangeBins * sizeof(uint16_t);

    /* Starting from first dopplerLine */
    dopplerLine = 0;

    do
    {
        /* Check if any bits are set for a particular doppler line */
        if(CFARCADSP_isObjectDetectedOnDopplerLine(dopplerLine,
                                               cfarObj->staticCfg.numDopplerBins,
                                               cfarObj->staticCfg.numRangeBins,
                                               cfarObj->res.cfarDopplerDetOutBitMask) == false)
        {
            /* No objects are found on doppler line , skip to next doppler line */
            dopplerLine++;
            continue;
        }

        dopplerSgnIdx = dopplerLine;
        if (dopplerSgnIdx >= (int32_t)(cfarObj->staticCfg.numDopplerBins>>1))
        {
           dopplerSgnIdx = dopplerSgnIdx - (int32_t)cfarObj->staticCfg.numDopplerBins;
        }

        /* Calculate source address in detMatrix for a doppler Line with detected objects */
        srcAddr = dopplerLine*sizeof(uint16_t) + (uint32_t)cfarObj->res.detMatrix.data;

        /* When loopIndex is even, use Ping buffer. Otherwise use pong buffer */
        localBufferAddr = (uint32_t)cfarObj->res.localDetMatrixBuffer + (loopIndex %2) *oneDopplerBinSize;

        /* Setup EDMA to bring in detection matrix for the dopplerLine */
        CFARCADSP_configEDMARangeDomain(cfarObj->res.edmaHandle,
                                            &cfarObj->res.edmaInPing,
                                            &cfarObj->staticCfg,
                                            srcAddr,
                                            localBufferAddr);

        if (( EDMA_startDmaTransfer(cfarObj->res.edmaHandle, cfarObj->res.edmaInPing.channel)) != EDMA_NO_ERROR)
        {
            goto exit;
        }

        /* Wait for DMA transfer of current dopple line to complete */
        startTimeWait = Cycleprofiler_getTimeStamp();
        CFARCADSP_waitEDMATransComplete(cfarObj->res.edmaHandle, cfarObj->res.edmaInPing.channel);
        *waitingTime += Cycleprofiler_getTimeStamp() - startTimeWait;

        /* Do CFAR search for range peak among numRangeBins samples for the doppler line*/
        numDetObj = CFARCADSP_cfarCadB_SOGO(
                (uint16_t *)localBufferAddr,
                cfarObj->res.cfarDetOutBuffer,
                cfarObj->staticCfg.numRangeBins,
                cfarObj->cfarCfgRange.averageMode,
                cfarObj->cfarCfgRange.thresholdScale,
                cfarObj->cfarCfgRange.noiseDivShift, 
                cfarObj->cfarCfgRange.guardLen,
                cfarObj->cfarCfgRange.winLen,
                cfarObj->detObjPeakIdxBuf);

        for(detIdx=0; detIdx <numDetObj; detIdx++)
        {
            if (numDetObjIndex < cfarObj->res.cfarRngDopSnrListSize)
            {
                uint16_t rangeIdx;
                uint16_t *cfarDetList = (uint16_t *)cfarObj->res.cfarDetOutBuffer;
                uint16_t *detMat = (uint16_t *)localBufferAddr;

                rangeIdx = cfarDetList[detIdx];

                /* Is the object in Doppler Domain as well? */
                if(CFARCADSP_isObjectDetected( rangeIdx,
                                               dopplerLine,
                                               cfarObj->staticCfg.numDopplerBins,
                                               cfarObj->res.cfarDopplerDetOutBitMask) == false)
                {
                    /* Object is not detected in Doppler domain, continue for next detected objects */
                    continue;
                }

                if ((rangeIdx >= cfarObj->fovRange.minIdx) &&
                   (rangeIdx <= cfarObj->fovRange.maxIdx) &&
                   (dopplerSgnIdx >= cfarObj->fovDoppler.minIdx) &&
                   (dopplerSgnIdx <= cfarObj->fovDoppler.maxIdx))
                {
                    float   noisedB;

                    /* Calculate noise */
                    noisedB = CFARCADSP_CONV_PEAK_TO_LOG((float)cfarObj->detObjPeakIdxBuf[detIdx], DPIF_DETMATRIX_DATA_QFORMAT);
                    if(peakGrpingEn)
                    {
                        cfarObj->detObjRangeIdxBuf[numDetObjIndex] = rangeIdx;
                        cfarObj->detObjDopplerIdxBuf[numDetObjIndex] = dopplerLine;
                        cfarObj->detObjPeakValBuf[numDetObjIndex] = detMat[rangeIdx];
                    }
                    else
                    {
                        float   snrdB;

                        snrdB = CFARCADSP_CONV_PEAK_TO_LOG((float)detMat[rangeIdx], DPIF_DETMATRIX_DATA_QFORMAT) - noisedB;

                        /* Update detection list */
                        cfarObj->res.cfarRngDopSnrList[numDetObjIndex].rangeIdx = rangeIdx;
                        cfarObj->res.cfarRngDopSnrList[numDetObjIndex].dopplerIdx = dopplerLine;
                        cfarObj->res.cfarRngDopSnrList[numDetObjIndex].snr = (int16_t)snrdB;
                    }
                    cfarObj->res.cfarRngDopSnrList[numDetObjIndex].noise = (int16_t)noisedB;

                    numDetObjIndex++;
                }
            }
            else
            {
                break;
            }
        }

        /* Current doppler line is completed , move on to next doppler line */
        loopIndex++;
        dopplerLine++;
    }while(dopplerLine<cfarObj->staticCfg.numDopplerBins);
exit:
    return(numDetObjIndex);
}

/**************************************************************************
 **************************** External Functions *******************************
 **************************************************************************/

/**
 *  @b Description
 *  @n
 *      The function is CFARCAProcDSP DPU initialization function. It allocates memory to store
 *  its internal data object and returns a handle if it executes successfully.
 *
 *  @param[in]  errCode                 Pointer to errCode generates from the API
 *
 *  \ingroup    DPU_CFARCAPROC_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - valid CFARCAProcDSP handle
 *  @retval
 *      Error       - NULL
 */
DPU_CFARCAProcDSP_Handle DPU_CFARCAProcDSP_init
(
    int32_t* errCode
)
{
    CFARCADspObj         *cfarDspObj = NULL;
    *errCode = 0;

    cfarDspObj = MemoryP_ctrlAlloc(sizeof(CFARCADspObj), 0);
    if (cfarDspObj == NULL)
    {
        *errCode = DPU_CFARCAPROCDSP_ENOMEM;
        goto exit;
    }

    /* Initialize memory */
    memset((void *)cfarDspObj, 0, sizeof(CFARCADspObj));

exit:
    return ((DPU_CFARCAProcDSP_Handle)cfarDspObj);
}

/**
 *  @b Description
 *  @n
 *      The function is CFARCAProcDSP DPU configuration function. It saves buffer pointer and configurations
 *  including system resources and configures EDMA for runtime cfar processing.
 *
 *  @pre    DPU_CFARCAProcDSP_init() has been called
 *
 *  @param[in]  handle                  CFARCAProcDSP DPU handle
 *  @param[in]  cfarcaCfg               Pointer to CFARCAProcDSP configuration data structure
 *
 *  \ingroup    DPU_CFARCAPROC_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 */
int32_t DPU_CFARCAProcDSP_config
(
   DPU_CFARCAProcDSP_Handle       handle,
   DPU_CFARCAProcDSP_Config       *cfarcaCfg
)
{
    int32_t  retVal = 0;
    CFARCADspObj *cfarDspObj = (CFARCADspObj *)handle;
    DPU_CFARCAProcDSP_HW_Resources *pRes = &cfarcaCfg->res;
    DPU_CFARCAProcDSP_StaticConfig *staticCfg = &cfarcaCfg->staticCfg;

    if(cfarDspObj == NULL)
    {
        retVal = DPU_CFARCAPROCDSP_EINVAL;
        goto exit;
    }

    /* Validate buffer pointer */
    if( (pRes->localDetMatrixBuffer == NULL) ||
       (pRes->cfarDetOutBuffer == NULL) ||
       (pRes->cfarDopplerDetOutBitMask == NULL) ||
       (pRes->cfarRngDopSnrList == NULL) ||
       (pRes->detMatrix.data == NULL))
    {
        retVal = DPU_CFARCAPROCDSP_EINVAL_EBUFFER_POINTER;
        goto exit;
    }

    /* Check if detection matrix format is supported. */
    if(pRes->detMatrix.datafmt != DPIF_DETMATRIX_FORMAT_1)
    {
        retVal = DPU_CFARCAPROCDSP_EINVAL__DET_MATRIX_FORMAT;
        goto exit;
    }

    if MEM_IS_NOT_ALIGN(pRes->detMatrix.data,
                         DPU_CFARCAPROCDSP_DET_MATRIX_BYTE_ALIGNMENT)
    {
        retVal = DPU_CFARCAPROCDSP_ENOMEMALIGN_DET_MATRIX;
        goto exit;
    }

    if MEM_IS_NOT_ALIGN(pRes->cfarRngDopSnrList,
                        DPU_CFARCAPROCDSP_CFAR_DET_LIST_BYTE_ALIGNMENT)
    {
        retVal = DPU_CFARCAPROCDSP_ENOMEMALIGN_CFAR_DET_LIST;
        goto exit;
    }

    if MEM_IS_NOT_ALIGN(pRes->cfarDopplerDetOutBitMask,
                        DPU_CFARCAPROCDSP_DOPPLER_DET_OUT_BIT_MASK_BYTE_ALIGNMENT)
    {
        retVal = DPU_CFARCAPROCDSP_ENOMEMALIGN_DOPPLER_DET_OUT_BIT_MASK;
        goto exit;
    }

    if MEM_IS_NOT_ALIGN(pRes->localDetMatrixBuffer,
                        DPU_CFARCAPROCDSP_DET_MATRIX_LOCAL_BYTE_ALIGNMENT)
    {
        retVal = DPU_CFARCAPROCDSP_ENOMEMALIGN_LOCAL_DETMATRIX;
        goto exit;
    }

    if MEM_IS_NOT_ALIGN(pRes->cfarDetOutBuffer,
                        DPU_CFARCAPROCDSP_CFAR_DETOUT_BYTE_ALIGNMENT)
    {
        retVal = DPU_CFARCAPROCDSP_ENOMEMALIGN_LOCAL_CFAR_DETOUT;
        goto exit;
    }

    if MEM_IS_NOT_ALIGN(pRes->cfarScrachBuffer,
                        DPU_CFARCAPROCDSP_SCRACHBUF_BYTE_ALIGNMENT)
    {
        retVal = DPU_CFARCAPROCDSP_ENOMEMALIGN_SCRATCH_BUFFER;
        goto exit;
    }

    /* Check if input scratch memory for bit mask is sufficient */
    if ((pRes->cfarDopplerDetOutBitMaskSize * 32U) <
                (staticCfg->numDopplerBins * staticCfg->numRangeBins))
    {
        retVal = DPU_CFARCAPROCDSP_ENOMEM__INSUFFICIENT_DOP_DET_OUT_BIT_MASK;
        goto exit;
    }

    /* Validating buffer size */
    if( (pRes->localDetMatrixBufferSize < MAX(staticCfg->numDopplerBins, staticCfg->numRangeBins) * sizeof(uint16_t) * 2U) ||
       (pRes->cfarDetOutBufferSize < MAX(staticCfg->numDopplerBins, staticCfg->numRangeBins) * sizeof(uint16_t)) ||
       (pRes->detMatrix.dataSize < staticCfg->numRangeBins * staticCfg->numDopplerBins * sizeof(uint16_t)))
    {
        retVal = DPU_CFARCAPROCDSP_EINVAL_EBUFFER_SIZE;
        goto exit;
    }

    /* Validate peak grouping parameters */
    if(((cfarcaCfg->dynCfg.cfarCfgRange->peakGroupingEn) &&
      (cfarcaCfg->dynCfg.cfarCfgRange->peakGroupingScheme != DPU_CFAR_PEAK_GROUPING_DET_MATRIX_BASED)) &&
      (cfarcaCfg->dynCfg.cfarCfgRange->peakGroupingScheme != DPU_CFAR_PEAK_GROUPING_CFAR_PEAK_BASED))
    {
        retVal = DPU_CFARCAPROCDSP_EINVAL;
        goto exit;
    }

    if(((cfarcaCfg->dynCfg.cfarCfgDoppler->peakGroupingEn) &&
      (cfarcaCfg->dynCfg.cfarCfgDoppler->peakGroupingScheme != DPU_CFAR_PEAK_GROUPING_DET_MATRIX_BASED)) &&
      (cfarcaCfg->dynCfg.cfarCfgDoppler->peakGroupingScheme != DPU_CFAR_PEAK_GROUPING_CFAR_PEAK_BASED))
    {
        retVal = DPU_CFARCAPROCDSP_EINVAL;
        goto exit;
    }

    CFARCADSP_saveConfiguration(cfarDspObj, cfarcaCfg);

    /* The scrach buffer will be used for peak grouping and cfar noise buffer */
    if((pRes->cfarScrachBuffer == NULL) ||
      (pRes->cfarScrachBufferSize < pRes->cfarRngDopSnrListSize * sizeof(uint16_t) * 4U ))
    {
        retVal = DPU_CFARCAPROCDSP_ENOMEM__INSUFFICIENT_SCRATCH_BUFFER;
        goto exit;
    }
    else
    {
        /* Internal scratch buffers for peak grouping and noise value */
        cfarDspObj->detObjRangeIdxBuf = (uint16_t *)pRes->cfarScrachBuffer;
        cfarDspObj->detObjDopplerIdxBuf = (uint16_t *)((uint32_t)pRes->cfarScrachBuffer + pRes->cfarRngDopSnrListSize * sizeof(uint16_t));
        cfarDspObj->detObjPeakValBuf = (uint16_t *)((uint32_t)cfarDspObj->detObjDopplerIdxBuf + pRes->cfarRngDopSnrListSize * sizeof(uint16_t));
        cfarDspObj->detObjPeakIdxBuf = (uint16_t *)((uint32_t)cfarDspObj->detObjPeakValBuf + pRes->cfarRngDopSnrListSize * sizeof(uint16_t));
    }

exit:
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      The function is CFARCAProcDSP DPU process function. It performs CFAR detection using DSP
 *
 *  @pre    DPU_CFARCAProcDSP_init() has been called
 *
 *  @param[in]  handle                  CFARCAProcDSP DPU handle
 *  @param[in]  outParams               DPU output parameters
 *
 *  \ingroup    DPU_CFARCAPROC_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success = 0
 *  @retval
 *      Error  != 0
 */
int32_t DPU_CFARCAProcDSP_process
(
    DPU_CFARCAProcDSP_Handle   handle,
    DPU_CFARCAProcDSP_OutParams  *outParams
)
{
    uint16_t            numObjs = 0;
    int32_t             retVal = 0;
    CFARCADspObj          *cfarDspObj;
    DPU_CFARCAProcDSP_HW_Resources *pRes;
    volatile uint32_t   startTime;
    uint32_t            waitTimeLocal = 0;
    uint8_t             peakGrpingEn = 0;

    if (handle == NULL)
    {
        retVal = DPU_CFARCAPROCDSP_EINVAL;
        goto exit;
    }

    cfarDspObj = (CFARCADspObj *)handle;
    pRes = &cfarDspObj->res;

    if ( (cfarDspObj->cfarCfgRange.peakGroupingEn) || (cfarDspObj->cfarCfgDoppler.peakGroupingEn))
    {
        peakGrpingEn = 1;
    }
    startTime = Cycleprofiler_getTimeStamp();

    /* CFARCA Peak search along doppler line */
    if (cfarDspObj->cfarCfgDoppler.thresholdScale > 0)
    {
        /* Configure EDMA */
        retVal = CFARCADSP_configEDMADopplerDomain(pRes, &cfarDspObj->staticCfg);
        if (retVal != 0)
        {
            goto exit;
        }

        numObjs = CFARCADSP_processDopplerDomain(cfarDspObj, peakGrpingEn, &waitTimeLocal, &retVal);
    }
    else
    {
        /* All bit mask is masked in case of no-doppler domain detection */
        memset((void *)pRes->cfarDopplerDetOutBitMask, 0xFF, pRes->cfarDopplerDetOutBitMaskSize * sizeof(uint32_t));
    }

    /* CFARCA Peak search along range line*/
    if (cfarDspObj->cfarCfgRange.thresholdScale > 0)
    {
        numObjs = CFARCADSP_processRangeDomain(cfarDspObj, peakGrpingEn, &waitTimeLocal, numObjs);
    }

    if (numObjs > pRes->cfarRngDopSnrListSize)
    {
        numObjs = pRes->cfarRngDopSnrListSize;
    }

    /* CFARCA peak Grouping */
    if ( (cfarDspObj->cfarCfgRange.peakGroupingEn) || (cfarDspObj->cfarCfgDoppler.peakGroupingEn))
    {
        numObjs = CFARCADSP_peakGrouping(cfarDspObj, numObjs);
    }

    cfarDspObj->numProcess++;

    outParams->numCfarDetectedPoints = numObjs;
    outParams->stats.waitTime = waitTimeLocal;
    outParams->stats.processingTime = Cycleprofiler_getTimeStamp() - startTime - waitTimeLocal;
    outParams->stats.numProcess = cfarDspObj->numProcess;
exit:
    return (retVal);
}

/**
 *  @b Description
 *  @n
 *      The function is CFARCAProcDSP DPU control function.
 *
 *  @pre     DPU_CFARCAProcDSP_init() has been called
 *
 *  @param[in]  handle           CFARCAProcDSP DPU handle
 *  @param[in]  cmd              CFARCAProcDSP DPU control command
 *  @param[in]  arg              CFARCAProcDSP DPU control argument pointer
 *  @param[in]  argSize          CFARCAProcDSP DPU control argument size
 *
 *  \ingroup    DPU_CFARCAPROC_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 */
int32_t DPU_CFARCAProcDSP_control
(
    DPU_CFARCAProcDSP_Handle handle,
    DPU_CFARCAProcDSP_Cmd cmd,
    void *arg,
    uint32_t argSize
)
{
    int32_t    retVal = 0;
    CFARCADspObj *cfarDspObj = (CFARCADspObj *)handle;

    /* Get rangeProc data object */
    if (cfarDspObj == NULL)
    {
        retVal = DPU_CFARCAPROCDSP_EINVAL;
        goto exit;
    }

    switch(cmd)
    {
        case DPU_CFARCAProcDSP_Cmd_CfarRangeCfg:
        {
            DPU_CFARCAProc_CfarCfg *cfarcaCfg = arg;
            if((argSize != sizeof(DPU_CFARCAProc_CfarCfg)) ||
               (arg == NULL))
            {
                retVal = DPU_CFARCAPROCDSP_EINVAL;
                goto exit;
            }
            else if( (cfarcaCfg->peakGroupingEn) &&
                   ((cfarcaCfg->peakGroupingScheme != DPU_CFAR_PEAK_GROUPING_DET_MATRIX_BASED) &&
                   (cfarcaCfg->peakGroupingScheme != DPU_CFAR_PEAK_GROUPING_CFAR_PEAK_BASED)))
            {
                retVal = DPU_CFARCAPROCDSP_EINVAL;
                goto exit;
            }
            else
            {
                /* Save configuration */
                memcpy((void *)&cfarDspObj->cfarCfgRange, arg, argSize);   
                CFARCADSP_adjustCfarCfg(&cfarDspObj->cfarCfgRange);
            }
        }
        break;
        case DPU_CFARCAProcDSP_Cmd_CfarDopplerCfg:
        {
            DPU_CFARCAProc_CfarCfg *cfarcaCfg = arg;
            if((argSize != sizeof(DPU_CFARCAProc_CfarCfg)) ||
               (arg == NULL))
            {
                retVal = DPU_CFARCAPROCDSP_EINVAL;
                goto exit;
            }
            else if( (cfarcaCfg->peakGroupingEn) &&
                   ((cfarcaCfg->peakGroupingScheme != DPU_CFAR_PEAK_GROUPING_DET_MATRIX_BASED) &&
                   (cfarcaCfg->peakGroupingScheme != DPU_CFAR_PEAK_GROUPING_CFAR_PEAK_BASED)))
            {
                retVal = DPU_CFARCAPROCDSP_EINVAL;
                goto exit;
            }
            else
            {
                /* Save configuration */
                memcpy((void *)&cfarDspObj->cfarCfgDoppler, arg, argSize);
                /* DPU assumes that Doppler is always CFAR-CA but following code
                   is added for generality */
                CFARCADSP_adjustCfarCfg(&cfarDspObj->cfarCfgDoppler);
            }
        }
        break;
        case DPU_CFARCAProcDSP_Cmd_FovRangeCfg:
        {
            if((argSize != sizeof(DPU_CFARCAProc_FovCfg)) ||
               (arg == NULL))
            {
                retVal = DPU_CFARCAPROCDSP_EINVAL;
                goto exit;
            }
            else
            {
                /* Save configuration */
                CFARCADSP_fovConvertRange(arg,
                                        cfarDspObj->staticCfg.rangeStep,
                                        &cfarDspObj->fovRange);
            }
        }
        break;
        case DPU_CFARCAProcDSP_Cmd_FovDopplerCfg:
        {
            if((argSize != sizeof(DPU_CFARCAProc_FovCfg)) ||
               (arg == NULL))
            {
                retVal = DPU_CFARCAPROCDSP_EINVAL;
                goto exit;
            }
            else
            {
                /* Save configuration */
                CFARCADSP_fovConvertDoppler(arg,
                                          cfarDspObj->staticCfg.dopplerStep,
                                          &cfarDspObj->fovDoppler);
            }
        }
        break;

        default:
            retVal = DPU_CFARCAPROCDSP_EINVAL;
            break;
    }
exit:
    return (retVal);
}

/**
 *  @b Description
 *  @n
 *      The function is CFARCAProcDSP DPU deinitialization function. It frees up the
 *   resources allocated during initialization.
 *
 *  @pre    DPU_CFARCAProcDSP_init() has been called
 *
 *  @param[in]  handle           CFARCAProcDSP DPU handle
 *
 *  \ingroup    DPU_CFARCAPROC_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 */
int32_t DPU_CFARCAProcDSP_deinit(DPU_CFARCAProcDSP_Handle handle)
{
    int32_t retVal = 0;
    if (handle == NULL)
    {
        retVal = DPU_CFARCAPROCDSP_EINVAL;
    }
    else
    {
        MemoryP_ctrlFree(handle, sizeof(CFARCADspObj));
    }
    return (retVal);
}

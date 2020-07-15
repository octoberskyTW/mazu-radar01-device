/**
 *   @file  dopplerprocdsp.c
 *
 *   @brief
 *      Implements Data path Doppler processing Unit using DSP.
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

/* mmWave SDK driver/common Include Files */
#include <ti/common/sys_common.h>
#include <ti/drivers/osal/SemaphoreP.h>
#include <ti/drivers/osal/MemoryP.h>
#include <ti/drivers/edma/edma.h>
#include <ti/drivers/esm/esm.h>
#include <ti/drivers/soc/soc.h>
#include <ti/alg/mmwavelib/mmwavelib.h>

/* Utils */
#include <ti/utils/mathutils/mathutils.h>

/* Data Path Include files */
#include <ti/datapath/dpedma/dpedma.h>
#include <ti/datapath/dpc/dpu/dopplerproc/dopplerprocdsp.h>
#include <ti/datapath/dpc/dpu/dopplerproc/include/dopplerprocdspinternal.h>

/* C64P dsplib (fixed point part for C674X) */
#include "DSP_fft32x32.h"

/*===========================================================
 *                    Internal Functions
 *===========================================================*/
/**
 *  @b Description
 *  @n
 *  Doppler DPU EDMA configuration.
 *  This implementation of doppler processing involves a Ping/Pong 
 *  mechanism, hence there are two sets of EDMA transfer.
 *
 *  @param[in] obj    - DPU obj
 *  @param[in] cfg    - DPU configuration
 *
 *  \ingroup    DPU_DOPPLERPROC_INTERNAL_FUNCTION
 *
 *  @retval EDMA error code, see EDMA API.
 */
static inline int32_t DPU_DopplerProcDSP_configEdma
(
    DPU_DopplerProcDSP_Obj      *obj,
    DPU_DopplerProcDSP_Config   *cfg
)
{
    int32_t             retVal = EDMA_NO_ERROR;
    uint16_t            sampleLenInBytes = sizeof(cmplx16ImRe_t);
    uint16_t            sizeOfDetMatrixElement = sizeof(uint16_t);
    DPEDMA_syncACfg     syncACfg;
    DPEDMA_syncABCfg    syncABCfg;
    cmplx16ImRe_t      *radarCubeBase;

    if(obj == NULL)
    {
        retVal = DPU_DOPPLERPROCDSP_EINVAL;
        goto exit;
    }
    
    radarCubeBase = (cmplx16ImRe_t *)obj->cfg.hwRes.radarCube.data;

    /******************************************************************************************
    *  PROGRAM DMA channel  to transfer data from Radar cube to input buffer (ping)
    ******************************************************************************************/   
    syncABCfg.srcAddress  = (uint32_t)(&radarCubeBase[0]);
    syncABCfg.destAddress = (uint32_t)(&obj->cfg.hwRes.pingPongBuf[0]);
    syncABCfg.aCount      = sampleLenInBytes;
    syncABCfg.bCount      = cfg->staticCfg.numDopplerChirps;
    syncABCfg.cCount      = 1;/*data for one virtual antenna transferred at a time*/
    syncABCfg.srcBIdx     = cfg->staticCfg.numRxAntennas * cfg->staticCfg.numRangeBins * sampleLenInBytes;
    syncABCfg.dstBIdx     = sampleLenInBytes;
    syncABCfg.srcCIdx     = 0U;    
    syncABCfg.dstCIdx     = 0U;

    retVal = DPEDMA_configSyncAB(cfg->hwRes.edmaCfg.edmaHandle,
                                 &cfg->hwRes.edmaCfg.edmaIn.ping,
                                 NULL,//chainingCfg: No chaining  
                                 &syncABCfg,
                                 false,//isEventTriggered
                                 true, //isIntermediateTransferCompletionEnabled
                                 true,//isTransferCompletionEnabled
                                 NULL, //transferCompletionCallbackFxn
                                 NULL);//transferCompletionCallbackFxnArg
                                 
    if (retVal != EDMA_NO_ERROR)
    {
        goto exit;
    }    
    
    /******************************************************************************************
    *  PROGRAM DMA channel  to transfer data from Radar cube to input buffer (pong)
     ******************************************************************************************/ 

    /* Transfer parameters are the same as ping, except for src/dst addresses */

    /*Ping/Pong srcAddress is reprogrammed in every iteration (except for first ping), therefore
      this srcAddress below will be reprogrammed during processing. In order to avoid recomputing here
      the first pong srcAddress, it will be hardcoded to a valid address (dummy).*/      
    syncABCfg.srcAddress  = (uint32_t)(&radarCubeBase[0]);/*dummy*/
    syncABCfg.destAddress = (uint32_t)(&obj->cfg.hwRes.pingPongBuf[cfg->staticCfg.numDopplerChirps]);

    retVal = DPEDMA_configSyncAB(cfg->hwRes.edmaCfg.edmaHandle,
                                 &cfg->hwRes.edmaCfg.edmaIn.pong,
                                 NULL,//chainingCfg: No chaining  
                                 &syncABCfg,
                                 false,//isEventTriggered
                                 true, //isIntermediateTransferCompletionEnabled
                                 true,//isTransferCompletionEnabled
                                 NULL, //transferCompletionCallbackFxn
                                 NULL);//transferCompletionCallbackFxnArg

    if (retVal != EDMA_NO_ERROR)
    {
        goto exit;
    }

    /******************************************************************************************
    *  PROGRAM DMA channel to transfer data from Doppler DPU internal buffers to Detection matrix
    ******************************************************************************************/    
    syncACfg.srcAddress  = (uint32_t)&obj->cfg.hwRes.sumAbsBuf[0U];
    syncACfg.destAddress = (uint32_t)cfg->hwRes.detMatrix.data;
    syncACfg.aCount      = cfg->staticCfg.numDopplerBins * sizeOfDetMatrixElement;
    syncACfg.bCount      = cfg->staticCfg.numRangeBins;
    syncACfg.srcBIdx     = 0U;
    syncACfg.dstBIdx     = cfg->staticCfg.numDopplerBins * sizeOfDetMatrixElement;
         
    retVal = DPEDMA_configSyncA_singleFrame(cfg->hwRes.edmaCfg.edmaHandle,
                                &cfg->hwRes.edmaCfg.edmaOut,
                                NULL,//chainingCfg: No chanining
                                &syncACfg,
                                false, //isEventTriggered
                                true,//isIntermediateTransferInterruptEnabled
                                true,//isTransferCompletionEnabled
                                NULL, //transferCompletionCallbackFxn
                                NULL);//transferCompletionCallbackFxnArg

    if (retVal != EDMA_NO_ERROR)
    {
        goto exit;
    }

exit:
    return(retVal);
} 

/**
 *  @b Description
 *  @n
 *      This function waits for an input (from radar cube to scratch buffer)
 *      EDMA transfer to complete.
 *
 *  @param[in]  obj         DPU object.
 *  @param[in]  pingPongId  Ping/pong ID
 *
 *  \ingroup    DPU_DOPPLERPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      Success     =0
 *  @retval
 *      Error       !=0
 */
static inline int32_t DPU_DopplerProcDSP_waitInData(DPU_DopplerProcDSP_Obj *obj, uint32_t pingPongId)
{
    /* wait until transfer done */
    volatile bool isTransferDone;
    uint8_t       chId;
    int32_t       retVal = 0;
    
    if(pingPongId == DPU_DOPPLERPROCDSP_PING_IDX)
    {
        chId = obj->cfg.hwRes.edmaCfg.edmaIn.ping.channel;
    }
    else
    {
        chId = obj->cfg.hwRes.edmaCfg.edmaIn.pong.channel;
    }
    do 
    {
        retVal = EDMA_isTransferComplete(obj->cfg.hwRes.edmaCfg.edmaHandle,
                                        chId,
                                        (bool *)&isTransferDone);
        if(retVal != EDMA_NO_ERROR)
        {
            return retVal;
        }
    } while (isTransferDone == false);
    
    return 0;
}

/**
 *  @b Description
 *  @n
 *      This function waits for an output (from scratch buffer to detection matrix)
 *      EDMA transfer to complete.
 *
 *  @param[in]  obj         DPU object.
 *
 *  \ingroup    DPU_DOPPLERPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      Success     =0
 *  @retval
 *      Error       !=0
 */
static inline int32_t DPU_DopplerProcDSP_waitTransDetMatrix(DPU_DopplerProcDSP_Obj *obj)
{
    /* wait until transfer done */
    volatile bool isTransferDone;
    uint8_t       chId;
    int32_t       retVal = 0;
    
    chId = obj->cfg.hwRes.edmaCfg.edmaOut.channel;
    
    do 
    {
        retVal = EDMA_isTransferComplete(obj->cfg.hwRes.edmaCfg.edmaHandle,
                                        chId,
                                        (bool *)&isTransferDone);
        if(retVal != EDMA_NO_ERROR)
        {
            return retVal;
        }
    } while (isTransferDone == false);
    
    return 0;

}

/*!************************************************************************************************
 * @brief               DPU_DopplerProcDSP_mult16x32cplx
 * \par
 * <b>Description</b>  : Multiply a 16-bit complex to a 32-bit complex symbol.
 *
 * @param[in]            xIQ : 16-bit complex value(16I|16Q packed in 32bits). ImRe format.
 * @param[in]            wQI : 32-bit complex value(32Q|32I packed in 64bits). ReIm format.
 * @param[out]           yQI : pointer to store output 32-bit complex value(32Q|32I). ReIm format.
 *
 * @return               void
 **************************************************************************************************
 */
static inline void DPU_DopplerProcDSP_mult16x32cplx(uint32_t xIQ, int64_t wQI, int64_t *yQI)
{
    int64_t  lltempa, lltempb;
    int32_t  wI, wQ, yI, yQ;

    wI      = (int32_t) _loll(wQI);
    wQ      = (int32_t) _hill(wQI);
    lltempa = _mpy2ir(xIQ, wI);
    lltempb = _mpy2ir(xIQ, wQ);
    yI      = _ssub((int32_t)_hill(lltempa), (int32_t)_loll(lltempb));
    yQ      = _sadd((int32_t)_hill(lltempb), (int32_t)_loll(lltempa));
    *yQI    = _itoll(yQ, yI);
}

/*!************************************************************************************************
 * @brief                DPU_DopplerProcDSP_compensationGetCoeff
 * \par
 * <b>Description</b>  : Get compensation coefficient for Doppler compensation, 
 *                       by reading the phase shift from the table using half of the
 *                       object Doppler index value. If the Doppler index is odd,
 *                       an extra half of the bin phase shift is added.
 *
 * @param[in]            dopplerIdx     : Doppler index of the object
 * @param[in]            numDopplerBins : Number of Doppler bins
 * @param[in]            dftSinCosTable : Table with cos/sin values exp(1j*2*pi*k/N)
 *                                        SIN in even position, COS in odd position,
 *                                        for k=0,...,N-1 where N is number of Doppler bins.
 * @param[in]            dftHalfBin     :  exp(1j*2*pi* 0.5 /N) (ImRe format)
 * @param[out]           coeff          : Pointer to store the compensation coefficient(ImRe format) 
 *
 * @return               void
 **************************************************************************************************
 */
static inline void DPU_DopplerProcDSP_compensationGetCoeff
(
    uint16_t dopplerIdx,
    uint16_t numDopplerBins,
    uint32_t *dftSinCosTable,
    uint32_t *dftHalfBin,
    uint32_t *coeff)
{
    uint32_t expDoppComp;
    int32_t  dopplerCompensationIdx = dopplerIdx;

    /*Divide Doppler index by 2*/
    if (dopplerCompensationIdx >= numDopplerBins/2)
    {
        dopplerCompensationIdx -=  numDopplerBins;
    }
    dopplerCompensationIdx = dopplerCompensationIdx >> 1;
    if (dopplerCompensationIdx < 0)
    {
        dopplerCompensationIdx +=  numDopplerBins;
    }
    expDoppComp = dftSinCosTable[dopplerCompensationIdx];
    /* Add half bin rotation if Doppler index was odd */
    if (dopplerIdx & 0x1)
    {
        expDoppComp = _cmpyr1(expDoppComp, *dftHalfBin);
    }
	*coeff = expDoppComp;
}

/*!************************************************************************************************
 * @brief                Static inlined function DPU_DopplerProcDSP_compensateSingleValue
 * \par
 * <b>Description</b>  : Compensation of Doppler phase shift in one symbol. 
 *                       The phase shift read from the table using half of the
 *                       object Doppler index value. If the Doppler index is odd,
 *                       an extra half of the bin phase shift is added.
 *                       Compensation coefficient(16I|16Q) is multiplied to all symbols.
 *
 * @param[in]            dopplerIdx     : Doppler index of the object
 * @param[in]            numDopplerBins : Number of Doppler bins
 * @param[in]            dftSinCosTable : Table with cos/sin values exp(1j*2*pi*k/N)
 *                                        SIN in even position, COS in odd position, (ImRe format)
 *                                        for k=0,...,N-1 where N is number of Doppler bins.
 * @param[in]            dftHalfBin     :  exp(1j*2*pi* 0.5 /N), ImRe format.
 * @param[in,out]        symbolPtr      : Pointer to symbol to be Doppler compensated
 *                                        (32Q|32I each) must be 64 bit aligned. ReIm format.
 *
 * @return               void

 **************************************************************************************************
 */
static inline void DPU_DopplerProcDSP_compensateSingleValue(uint16_t dopplerIdx,
                                    uint16_t numDopplerBins,
                                    uint32_t *dftSinCosTable,
                                    uint32_t *dftHalfBin,
                                    int64_t * symbolPtr)
{
    uint32_t doppCompCoeff;

    DPU_DopplerProcDSP_compensationGetCoeff(dopplerIdx,
                                        numDopplerBins,
                                        dftSinCosTable,
                                        dftHalfBin,
                                        &doppCompCoeff);

    DPU_DopplerProcDSP_mult16x32cplx(doppCompCoeff, symbolPtr[0], symbolPtr );
}

/**
 *  @b Description
 *  @n
 *      Computes log2Abs and accumulates for each dopple bin.
 *
 *  @param[in]  obj             DPU object.
 *  @param[in]  rxAntIdx        RX antenna index
 *  @param[in]  txAntIdx        TX antenna index
 *  @param[in]  rangeIdx        Range bin index
 *  @param[in]  *waitingTime    Waiting time statistics
 *  @param[in]  fftOutIndx      Index of FFT output buffer
 *
 *  \ingroup    DPU_DOPPLERPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      Not Applicable.
 */
static inline void DPU_DopplerProcDSP_log2AbsAccum
(
    DPU_DopplerProcDSP_Obj *obj,
    uint16_t               rxAntIdx, 
    uint16_t               txAntIdx, 
    uint16_t               rangeIdx, 
    uint32_t               *waitingTime, 
    uint16_t               fftOutIndx
)
{
    volatile uint32_t startTimeWait;
    uint32_t idx;
    uint16_t *log2AbsBuf = (uint16_t *)obj->cfg.hwRes.windowingLog2AbsBuf;

    mmwavelib_log2Abs32(
                (int32_t *) &obj->cfg.hwRes.fftOutBuf[fftOutIndx],
                log2AbsBuf,
                obj->cfg.staticCfg.numDopplerBins);
                
    /* Check if this is the first virtual antenna for this range bin*/
    if ((rxAntIdx == 0) && (txAntIdx == 0))
    {
        /*This is the first virtual antenna. Starting a new sum. */
        if (rangeIdx > 0)
        {
            /* check if previous  sumAbsBuf has been transferred */
            startTimeWait = Cycleprofiler_getTimeStamp();
            DPU_DopplerProcDSP_waitTransDetMatrix (obj);
            waitingTime += Cycleprofiler_getTimeStamp() - startTimeWait;
        }
        
        /* Start new sum*/
        for (idx = 0; idx < obj->cfg.staticCfg.numDopplerBins; idx++)
        {
            obj->cfg.hwRes.sumAbsBuf[idx] = log2AbsBuf[idx] >> obj->log2VirtAnt;
        }
    }
    else
    {
        /*Not the first virtual antenna. Accumulate.*/
        mmwavelib_accum16shift(log2AbsBuf, 
                               obj->cfg.hwRes.sumAbsBuf,
                               obj->log2VirtAnt,                               
                               obj->cfg.staticCfg.numDopplerBins);
    }
}

/**
 *  @b Description
 *  @n
 *      Generate Twiddle and Sin/Cos tables used by the DPU.
 *
 *  @param[in]  obj             DPU object.
 *  @param[in]  cfg             DPU configuration.
 *
 *  \ingroup    DPU_DOPPLERPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      Not Applicable.
 */ 
static inline void DPU_DopplerProcDSP_generateTables
(
    DPU_DopplerProcDSP_Obj      *obj,
    DPU_DopplerProcDSP_Config   *cfg
)
{
    uint32_t tblIdx;

    /* Generate twiddle factors for Doppler FFT. This is in ReIm format.*/
    mmwavelib_gen_twiddle_smallfft_32x32((int32_t *)cfg->hwRes.twiddle32x32, 
                                         cfg->staticCfg.numDopplerBins);

    /* Generate SIN/COS table for single point DFT */
    mmwavelib_dftSinCosTabelGen(cfg->staticCfg.numDopplerBins,
                               (uint32_t *)cfg->hwRes.dftSinCosTable);
                               
    /* Table starts from DFT size = 4*/                           
    tblIdx = 28 - _norm(cfg->staticCfg.numDopplerBins); 
    obj->dftHalfBin.imag = mmwavelib_dftHalfBinExpValue[tblIdx << 1];
    obj->dftHalfBin.real = mmwavelib_dftHalfBinExpValue[(tblIdx << 1) + 1];
}

/**
 *  @b Description
 *  @n
 *      Decodes BPM based on FFT output for ping and pong.
 *
 *  @param[in]  obj             DPU object.
 *  @param[in]  cfg             DPU configuration.
 *
 *  \ingroup    DPU_DOPPLERPROC_INTERNAL_FUNCTION
 *
 *  @retval
 *      Not Applicable.
 */ 
static inline void DPU_DopplerProcDSP_decode2TxBPM
(
    DPU_DopplerProcDSP_Obj      *obj,
    DPU_DopplerProcDSP_Config   *cfg
)
{
    cmplx32ReIm_t *bpmAPtr;
    cmplx32ReIm_t *bpmBPtr;
    int32_t       real, imag;
    uint16_t      idx;

    /*We now have Ping and Pong available.
      First do doppler compensation on Pong samples.
      Then do BPM decoding in place:
      A=S1+S2 (PING) 
      B=S1-S2 (PONG)
      Compute S1=(A+B)/2 and overwrite A with this value 
      Compute S2=(A-B)/2 and overwrite B with this value
      A is located in fftOutBuf positions = [0..(numDopplerBins-1)]
      B is located in fftOutBuf positions = [numDopplerBins..(2*numDopplerBins)]
    */                    
    bpmAPtr  = &cfg->hwRes.fftOutBuf[0];
    bpmBPtr  = &cfg->hwRes.fftOutBuf[cfg->staticCfg.numDopplerBins];
    for(idx = 0; idx < cfg->staticCfg.numDopplerBins; idx++)
    {
        /*doppler compensation on Pong*/
        DPU_DopplerProcDSP_compensateSingleValue(idx,
                                                 cfg->staticCfg.numDopplerBins,
                                                 (uint32_t *) cfg->hwRes.dftSinCosTable,
                                                 (uint32_t *) &obj->dftHalfBin,
                                                 (int64_t *) &bpmBPtr[idx]);
 
        /*decode BPM*/
        /*first make a copy of A*/
        real = bpmAPtr[idx].real;
        imag = bpmAPtr[idx].imag;
        /*compute S1 and store in A*/
        bpmAPtr[idx].real = (bpmAPtr[idx].real + bpmBPtr[idx].real)/2;
        bpmAPtr[idx].imag = (bpmAPtr[idx].imag + bpmBPtr[idx].imag)/2;
        /*compute S2 and store in B*/
        bpmBPtr[idx].real = (real - bpmBPtr[idx].real)/2;
        bpmBPtr[idx].imag = (imag - bpmBPtr[idx].imag)/2;
    }
}

/**
 *  @b Description
 *  @n
 *      This function implements static clutter removal.
 *
 *  @param[in]  cfg             DPU configuration.
 *  @param[in]  inputBuf        input buffer. Clutter removal algorithm will work on this data.
 *
 *  \ingroup    DPU_DOPPLERPROC_INTERNAL_FUNCTION
 *
 *  @retval N/A
 */
static inline void DPU_DopplerProcDSP_clutterRemoval
(
    DPU_DopplerProcDSP_Config   *cfg,
    cmplx16ImRe_t               *inputBuf
)
{
    uint32_t sumVal[2]={0};
    cmplx32ImRe_t *pSumVal  = (cmplx32ImRe_t *) sumVal;
    uint32_t meanVal = 0;
    cmplx16ImRe_t *pMeanVal = (cmplx16ImRe_t *) &meanVal;
    
    /*Mmwavelib API requires size to be multiple of 4, which is fine because DPU allows 
      only numDopplerChirps that is multiple of 4*/
    mmwavelib_vecsum((int16_t *) inputBuf,
                     (int32_t *) sumVal,
                     (int32_t)   cfg->staticCfg.numDopplerChirps);

    /*Divide by numDopplerChirps as the scratch buffer was padded to zero to make it a 
      multiple of 4 so it does not affect the average*/    
    pMeanVal->real = pSumVal->real / cfg->staticCfg.numDopplerChirps ;
    pMeanVal->imag = pSumVal->imag / cfg->staticCfg.numDopplerChirps ;
    
    /*Lib requires size to be multiple of 4*/
    mmwavelib_vecsubc((int16_t *) inputBuf,
                      (int16_t *) inputBuf,
                      (uint32_t)  meanVal,
                      (int32_t)   cfg->staticCfg.numDopplerChirps);
}

/*===========================================================
 *                    Doppler Proc External APIs
 *===========================================================*/

/**
 *  @b Description
 *  @n
 *      dopplerProc DPU init function. It allocates memory to store
 *  its internal data object and returns a handle if it executes successfully.
 *
 *  @param[out]  errCode Pointer to errCode generates by the API
 *
 *  \ingroup    DPU_DOPPLERPROC_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - valid handle
 *  @retval
 *      Error       - NULL
 */
DPU_DopplerProcDSP_Handle DPU_DopplerProcDSP_init
(
    int32_t                       *errCode
)
{
    DPU_DopplerProcDSP_Obj  *obj = NULL;

    *errCode       = 0;
    
    /* Allocate memory */
    obj = MemoryP_ctrlAlloc(sizeof(DPU_DopplerProcDSP_Obj), 0U);
    if(obj == NULL)
    {
        *errCode = DPU_DOPPLERPROCDSP_ENOMEM;
        goto exit;
    }

    /* Initialize memory */
    memset((void *)obj, 0U, sizeof(DPU_DopplerProcDSP_Obj));
   
exit:    
   return ((DPU_DopplerProcDSP_Handle)obj);
}

/**
  *  @b Description
  *  @n
  *   Doppler DPU configuration 
  *
  *  @param[in]   handle     DPU handle.
  *  @param[in]   cfg        Pointer to configuration parameters.
  *
  *  \ingroup    DPU_DOPPLERPROC_EXTERNAL_FUNCTION
  *
  *  @retval
  *      Success      = 0
  *  @retval
  *      Error       != 0 @ref DPU_DOPPLERPROC_ERROR_CODE
  */
int32_t DPU_DopplerProcDSP_config
(
    DPU_DopplerProcDSP_Handle    handle,
    DPU_DopplerProcDSP_Config    *cfg
)
{
    DPU_DopplerProcDSP_Obj   *obj;
    int32_t                  retVal = 0;

    obj = (DPU_DopplerProcDSP_Obj *)handle;
    if(obj == NULL)
    {
        retVal = DPU_DOPPLERPROCDSP_EINVAL;
        goto exit;
    }
    
    /* Validate params */
    if(!cfg ||
       !cfg->hwRes.edmaCfg.edmaHandle ||
       !cfg->hwRes.radarCube.data ||
       !cfg->hwRes.detMatrix.data ||
       !cfg->hwRes.pingPongBuf ||
       !cfg->hwRes.windowingLog2AbsBuf ||
       !cfg->hwRes.fftOutBuf ||
       !cfg->hwRes.sumAbsBuf ||
       !cfg->hwRes.dftSinCosTable ||
       !cfg->hwRes.twiddle32x32 ||
       !cfg->hwRes.windowCoeff
      )
    {
        retVal = DPU_DOPPLERPROCDSP_EINVAL;
        goto exit;
    }
    
    if(obj->inProgress == true)
    {
        retVal = DPU_DOPPLERPROCDSP_EINPROGRESS;
        goto exit;
    }

    /* Check if radar cube format is supported by DPU*/
    if(cfg->hwRes.radarCube.datafmt != DPIF_RADARCUBE_FORMAT_1)
    {
        retVal = DPU_DOPPLERPROCDSP_ECUBEFORMAT;
        goto exit;
    }

    /* Check if detection matrix format is supported by DPU*/
    if(cfg->hwRes.detMatrix.datafmt != DPIF_DETMATRIX_FORMAT_1)
    {
        retVal = DPU_DOPPLERPROCDSP_EDETMFORMAT;
        goto exit;
    }

    /* Check if number of doppler chirps is a multiple of 4*/
    if((cfg->staticCfg.numDopplerChirps & 3) != 0)
    {
        retVal = DPU_DOPPLERPROCDSP_ENUMDOPCHIRPS;
        goto exit;
    }

    /* Check if number of doppler bins is at least 16 (due to DSPLIB which requires size of FFT to be
       at least 16*/
    if(cfg->staticCfg.numDopplerBins < 16)
    {
        retVal = DPU_DOPPLERPROCDSP_ENUMDOPBINS;
        goto exit;
    }
       
    /* Check if DPU configuration is compatible with EDMA max jump size of (32K - 1)*/
    if(cfg->staticCfg.numRxAntennas * cfg->staticCfg.numRangeBins * sizeof(cmplx16ImRe_t) >= 32768)
    {
        retVal = DPU_DOPPLERPROCDSP_EEXCEEDMAXEDMA;
        goto exit;
    }
    
    /* Check if buffers provided by application have the correct alignment*/
    if (MEM_IS_NOT_ALIGN(cfg->hwRes.pingPongBuf        , DPU_DOPPLERPROCDSP_BUFFER_BYTE_ALIGNMENT)||
        MEM_IS_NOT_ALIGN(cfg->hwRes.windowingLog2AbsBuf, DPU_DOPPLERPROCDSP_BUFFER_BYTE_ALIGNMENT)|| 
        MEM_IS_NOT_ALIGN(cfg->hwRes.fftOutBuf          , DPU_DOPPLERPROCDSP_BUFFER_BYTE_ALIGNMENT)||
        MEM_IS_NOT_ALIGN(cfg->hwRes.sumAbsBuf          , DPU_DOPPLERPROCDSP_BUFFER_BYTE_ALIGNMENT)||
        MEM_IS_NOT_ALIGN(cfg->hwRes.dftSinCosTable     , DPU_DOPPLERPROCDSP_BUFFER_BYTE_ALIGNMENT)||
        MEM_IS_NOT_ALIGN(cfg->hwRes.twiddle32x32       , DPU_DOPPLERPROCDSP_BUFFER_BYTE_ALIGNMENT)||
        MEM_IS_NOT_ALIGN(cfg->hwRes.windowCoeff        , DPU_DOPPLERPROCDSP_BUFFER_BYTE_ALIGNMENT))        
    {
        retVal = DPU_DOPPLERPROCDSP_EBUFALIGNMENT;
        goto exit;
    }
    
    /* Check if detection matrix size is sufficient*/
    if(cfg->hwRes.detMatrix.dataSize < (cfg->staticCfg.numRangeBins *
                                        cfg->staticCfg.numDopplerBins * sizeof(uint16_t)))
    {
        retVal = DPU_DOPPLERPROCDSP_EDETMSIZE;
        goto exit;
    }

    /* Check window Size */
    if (cfg->hwRes.windowSize != cfg->staticCfg.numDopplerChirps * sizeof(int32_t) / 2U) 
    {
            retVal = DPU_DOPPLERPROCDSP_EWINDSIZE;
            goto exit;
    }

    /* check sizes for the scratch buffers provided by application */
    if((cfg->hwRes.pingPongSize < 2 * sizeof(cmplx16ImRe_t) * cfg->staticCfg.numDopplerChirps   ) ||
       (cfg->hwRes.windowingLog2AbsSize < sizeof(cmplx32ReIm_t) * cfg->staticCfg.numDopplerBins ) ||
       (cfg->hwRes.sumAbsSize < cfg->staticCfg.numDopplerBins * sizeof(uint16_t)                ) ||
       (cfg->hwRes.dftSinCosSize < cfg->staticCfg.numDopplerBins * sizeof(cmplx16ImRe_t)        ) ||
       (cfg->hwRes.twiddleSize < sizeof(cmplx32ReIm_t) * cfg->staticCfg.numDopplerBins          ))
    {
            retVal = DPU_DOPPLERPROCDSP_ESCRATCHSIZE;
            goto exit;
    }
    
    if(cfg->staticCfg.isBpmEnabled)
    {
        /* Check if TX antenna configuration is supported for BPM scheme.
           The only supported scheme for BPM uses both Azimuth TX antennas and no elevation TX antenna*/
        if(cfg->staticCfg.numTxAntennas != 2)
        {
                retVal = DPU_DOPPLERPROCDSP_EBPMCFG;
                goto exit;
        }
        
        /* Check if scratch buffer size is enough for BPM decoding*/
        if(cfg->hwRes.fftOutSize < 2 * cfg->staticCfg.numDopplerBins * sizeof(cmplx32ReIm_t))
        {
                retVal = DPU_DOPPLERPROCDSP_ESCRATCHSIZE;
                goto exit;
        }
    }
    else
    {
        if(cfg->hwRes.fftOutSize < cfg->staticCfg.numDopplerBins * sizeof(cmplx32ReIm_t))
        {
                retVal = DPU_DOPPLERPROCDSP_ESCRATCHSIZE;
                goto exit;
        }
    }

    /* Generate tables */
    DPU_DopplerProcDSP_generateTables(obj, cfg);
    
    /* Compute Log2 of numVirtualAntennas */
    obj->log2VirtAnt = (uint8_t) mathUtils_ceilLog2(cfg->staticCfg.numVirtualAntennas);

    /* Save necessary parameters to DPU object that will be used during Process time */
    memcpy((void *)&obj->cfg, (void *)cfg, sizeof(DPU_DopplerProcDSP_Config));

    /* Configure EDMA */
    retVal = DPU_DopplerProcDSP_configEdma(obj, cfg);
    if (retVal != 0)
    {
        goto exit;
    }
    
    obj->inProgress = false;
    
exit:
    return retVal;
}

 /**
  *  @b Description
  *  @n Doppler DPU process function. 
  *   
  *  @param[in]   handle     DPU handle.
  *  @param[out]  outParams  Output parameters.
  *
  *  \ingroup    DPU_DOPPLERPROC_EXTERNAL_FUNCTION
  *
  *  @retval
  *      Success     =0
  *  @retval
  *      Error      !=0 @ref DPU_DOPPLERPROC_ERROR_CODE
  */
int32_t DPU_DopplerProcDSP_process
(
    DPU_DopplerProcDSP_Handle    handle,
    DPU_DopplerProcDSP_OutParams *outParams
)
{
    DPU_DopplerProcDSP_Obj *obj;
    DPU_DopplerProcDSP_Config *cfg;
    uint16_t rxAntIdx, rangeIdx, txAntIdx; 
    uint16_t nextTransferRxIdx, nextTransferRangeIdx, nextTransferTxIdx; 
    uint16_t rxAntIdxBPMPreviousBuffer, txAntIdxBPMPreviousBuffer;
    uint32_t nextTransferIdx, waitingTime, pingPongIdx;
    volatile uint32_t startTime;
    volatile uint32_t startTimeWait;
    int32_t  *fftOutPtr;
    int32_t  retVal;
    uint8_t  channel;
    cmplx16ImRe_t  *inpDoppFftBuf;
    cmplx16ImRe_t  *radarCubeBase;
    cmplx32ReIm_t  *windowingOutBuf;
    
    retVal = 0;    
    waitingTime = 0;
    obj = (DPU_DopplerProcDSP_Obj *)handle;
    
    if (obj == NULL)
    {
        retVal = DPU_DOPPLERPROCDSP_EINVAL;
        goto exit;
    }    
    
    if(obj->inProgress == true)
    {
        retVal = DPU_DOPPLERPROCDSP_EINPROGRESS;
        goto exit;
    }
    else
    {
        obj->inProgress = true;
    }

    startTime = Cycleprofiler_getTimeStamp();
    
    radarCubeBase = (cmplx16ImRe_t *)obj->cfg.hwRes.radarCube.data; 
    cfg =  &obj->cfg;

    pingPongIdx = DPU_DOPPLERPROCDSP_PING_IDX;
    
    /* trigger first DMA */
    EDMA_startDmaTransfer(cfg->hwRes.edmaCfg.edmaHandle, cfg->hwRes.edmaCfg.edmaIn.ping.channel);

    for (rangeIdx = 0; rangeIdx < cfg->staticCfg.numRangeBins; rangeIdx++)
    {
        for (rxAntIdx = 0; rxAntIdx < cfg->staticCfg.numRxAntennas; rxAntIdx++)
        {
            for (txAntIdx = 0; txAntIdx < cfg->staticCfg.numTxAntennas; txAntIdx++)
            {
                /* verify that previous DMA has completed */
                startTimeWait = Cycleprofiler_getTimeStamp();
                DPU_DopplerProcDSP_waitInData (obj, pingPongIdx);
                waitingTime += Cycleprofiler_getTimeStamp() - startTimeWait;
                
                /*Find index in radar cube for next EDMA. 
                  Order from bringing data from radar cube is:
                  1. Next TX antennas for same range/RxAnt (to assure BPM can be decoded).
                  2. Next virtual antenna(which means next RxAnt for same TxAnt) 
                     for same range (to assure sum of all virtual antennas can be computed).
                  3. Next range.
                */  
                nextTransferTxIdx    = txAntIdx + 1;
                nextTransferRxIdx    = rxAntIdx;
                nextTransferRangeIdx = rangeIdx;
                
                if(nextTransferTxIdx == cfg->staticCfg.numTxAntennas)
                {
                   nextTransferTxIdx = 0;
                   nextTransferRxIdx++;
                   if(nextTransferRxIdx == cfg->staticCfg.numRxAntennas)
                   {
                       nextTransferRxIdx = 0;
                       nextTransferRangeIdx++;
                   }
                }
                
                nextTransferIdx = (nextTransferTxIdx * cfg->staticCfg.numRxAntennas * cfg->staticCfg.numDopplerChirps + 
                                   nextTransferRxIdx) * cfg->staticCfg.numRangeBins + nextTransferRangeIdx;
                
                /*Last computation happens when nextTransferRangeIdx reaches numRangeBins. 
                  This indicates that, the current virtual antenna is the last one for (numRangeBins-1). 
                  Therefore, do not trigger next EDMA.*/
                if(nextTransferRangeIdx < cfg->staticCfg.numRangeBins)
                {
                    /* kick off next DMA */
                    if (pingPongIdx == DPU_DOPPLERPROCDSP_PONG_IDX)
                    {
                        channel = cfg->hwRes.edmaCfg.edmaIn.ping.channel;
                    }
                    else
                    {
                        channel = cfg->hwRes.edmaCfg.edmaIn.pong.channel;
                    }
                    
                    retVal = EDMA_setSourceAddress(cfg->hwRes.edmaCfg.edmaHandle, channel,
                                         (uint32_t) &radarCubeBase[nextTransferIdx]);
                    if (retVal != 0)
                    {
                        goto exit;
                    }
                                         
                    EDMA_startDmaTransfer(cfg->hwRes.edmaCfg.edmaHandle, channel);
                }    
                
                inpDoppFftBuf = (cmplx16ImRe_t *) &cfg->hwRes.pingPongBuf[pingPongIdx * cfg->staticCfg.numDopplerChirps];
                
                /* Remove static clutter? */
                if (cfg->dynCfg.staticClutterCfg.isEnabled)
                {
                    DPU_DopplerProcDSP_clutterRemoval(cfg, inpDoppFftBuf);
                }
                
                /* The windowing output buffer is the input buffer for the Doppler FFT. 
                   It needs to be padded with zeroes if number of Doppler chirps is less than 
                   the number of Doppler bins.*/
                if(cfg->staticCfg.numDopplerBins > cfg->staticCfg.numDopplerChirps)
                {
                    windowingOutBuf = (cmplx32ReIm_t*)cfg->hwRes.windowingLog2AbsBuf;
                    memset((void*)(&windowingOutBuf[cfg->staticCfg.numDopplerChirps]), 0,
                           (cfg->staticCfg.numDopplerBins - cfg->staticCfg.numDopplerChirps) * sizeof(cmplx32ReIm_t));
                }

                /*Up to this point samples are in ImRe format, which is the radar cube format.
                  The windowing function will do IQ swap and the Doppler FFT is computed in
                  ReIm format.*/                                
                mmwavelib_windowing16x32_IQswap((int16_t *) inpDoppFftBuf,
                                                cfg->hwRes.windowCoeff,
                                                (int32_t *) cfg->hwRes.windowingLog2AbsBuf,
                                                cfg->staticCfg.numDopplerChirps); 
                                                
                /*From this point forward samples are in ReIm format. In particular, FFT, twiddle are all in ReIm format.*/                                

                if(cfg->staticCfg.isBpmEnabled)
                {
                    /*If BPM is enabled, the FFT output buffer stores 2 sets of 
                      doppler bins so that BPM decoding can be done later on.*/
                    fftOutPtr  = (int32_t *)&cfg->hwRes.fftOutBuf[pingPongIdx * cfg->staticCfg.numDopplerBins];
                }
                else
                {
                    /*If BPM is not enabled, the FFT output buffer stores 1 set of 
                      doppler bins.*/
                    fftOutPtr  = (int32_t *)&cfg->hwRes.fftOutBuf[0];
                }            

                /*DSPLIB notes for DSP_fft32x32():
                  Minimum FFT size is 16. Size must be power of 2. 
                  No scaling done in FFT computation.*/
                DSP_fft32x32((int32_t *)cfg->hwRes.twiddle32x32,
                             cfg->staticCfg.numDopplerBins,
                             (int32_t *)cfg->hwRes.windowingLog2AbsBuf,
                             fftOutPtr);

                if(cfg->staticCfg.isBpmEnabled)
                {
                    /*BPM is enabled.
                      Need both Ping and Pong to do the BPM decoding and then
                      do logAbsSum for the content of both buffers.*/
                    if (pingPongIdx == DPU_DOPPLERPROCDSP_PONG_IDX)
                    {
                        DPU_DopplerProcDSP_decode2TxBPM(obj, cfg);
                        
                        /*compute log2Abs and accumulate for PING*/
                        DPU_DopplerProcDSP_log2AbsAccum(obj, rxAntIdxBPMPreviousBuffer, 
                                                        txAntIdxBPMPreviousBuffer, rangeIdx, &waitingTime, 0);                
                                                        
                        /*compute log2Abs and accumulate for PONG*/
                        DPU_DopplerProcDSP_log2AbsAccum(obj, rxAntIdx, txAntIdx, rangeIdx, &waitingTime, 
                                                        cfg->staticCfg.numDopplerBins);                   
                    }
                    else
                    {
                        /*Record previous indexes to be used later when both ping and pong are available 
                          for BPM decoding.*/
                        rxAntIdxBPMPreviousBuffer = rxAntIdx;
                        txAntIdxBPMPreviousBuffer = txAntIdx;
                    }                    
                }
                else
                {                    
                    /*Not BPM*/
                    /*Compute log2Abs and accumulate*/                    
                    DPU_DopplerProcDSP_log2AbsAccum(obj, rxAntIdx, txAntIdx, rangeIdx, &waitingTime, 0);                
                }
                
                pingPongIdx ^= 1;
            }/*txAntIdx*/
        } /* rxAntIdx */

        /* populate the detection matrix */
        EDMA_startDmaTransfer(cfg->hwRes.edmaCfg.edmaHandle, cfg->hwRes.edmaCfg.edmaOut.channel);
    } /* for loop rangeIdx 0 to cfg->staticCfg.numRangeBins */
    
    /*Wait for last transfer to detection matrix to complete*/
    startTimeWait = Cycleprofiler_getTimeStamp();
    DPU_DopplerProcDSP_waitTransDetMatrix (obj);
    waitingTime += Cycleprofiler_getTimeStamp() - startTimeWait;

    /*Update stats*/
    outParams->stats.numProcess++;
    outParams->stats.processingTime = Cycleprofiler_getTimeStamp() - startTime - waitingTime;
    outParams->stats.waitTime = waitingTime;
    
exit:
    if (obj != NULL)
    {
        obj->inProgress = false;
    }    
    
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      This the DPU control function. 
 *
 *
 *  @param[in]  handle           DPU handle
 *  @param[in]  cmd              DPU control command
 *  @param[in]  arg              DPU control argument pointer
 *  @param[in]  argSize          DPU control argument size
 *
 *  \ingroup    DPU_DOPPLERPROC_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 */
int32_t DPU_DopplerProcDSP_control
(
    DPU_DopplerProcDSP_Handle   handle,
    DPU_DopplerProcDSP_Cmd      cmd,
    void*                       arg,
    uint32_t                    argSize
)
{
    int32_t                retVal = 0;
    DPU_DopplerProcDSP_Obj *obj;

    obj = (DPU_DopplerProcDSP_Obj *)handle;
    
    if (obj == NULL)
    {
        retVal = DPU_DOPPLERPROCDSP_EINVAL;
        goto exit;
    }    
    
    /* Check if control() is called during processing time */
    if(obj->inProgress == true)
    {
        retVal = DPU_DOPPLERPROCDSP_EINPROGRESS;
        goto exit;
    }

    /* Control command handling */
    switch(cmd)
    {
        case DPU_DopplerProcDSP_Cmd_staticClutterCfg:
        {            
            if((argSize != sizeof(DPU_DopplerProc_StaticClutterRemovalCfg)) ||
               (arg == NULL))
            {
                retVal = DPU_DOPPLERPROCDSP_EINVAL;
                goto exit;
            }
            else
            {
                /* Update the static clutter configuration. Nothing else needs to be done
                   as this flag is checked during DPU processing time to decide if static clutter
                   removal should be done.*/
                memcpy((void *)&obj->cfg.dynCfg.staticClutterCfg, (void *)arg, argSize);
            }
        }
        break;

        default:
            retVal = DPU_DOPPLERPROCDSP_ECMD;
            break;
    }
    
exit:
    return (retVal);
}

/**
  *  @b Description
  *  @n
  *  Doppler DPU deinit 
  *
  *  @param[in]   handle   DPU handle.
  *
  *  \ingroup    DPU_DOPPLERPROC_EXTERNAL_FUNCTION
  *
  *  @retval
  *      Success      =0
  *  @retval
  *      Error       !=0 @ref DPU_DOPPLERPROC_ERROR_CODE
  */
int32_t DPU_DopplerProcDSP_deinit(DPU_DopplerProcDSP_Handle handle)
{
    int32_t     retVal = 0;
    
    /* Free memory */
    if(handle == NULL)
    {
        retVal = DPU_DOPPLERPROCDSP_EINVAL;
    }
    else
    {
        MemoryP_ctrlFree(handle, sizeof(DPU_DopplerProcDSP_Obj));
    }
    
    return retVal;
}

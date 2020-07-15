/**
 *   @file  mmwdemo_rfparser.c
 *
 *   @brief
 *      Implements rf parser.
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

#ifdef MMWDEMO_RFPARSER_DBG
/* enable float extended format in BIOS cfg file using System.extendedFormats
   to able to print %f values */
#include <xdc/runtime/System.h>
#endif

/* mmWave SDK Include files */
#include <ti/common/sys_common.h>
#include <ti/demo/utils/mmwdemo_rfparser.h>

/* MATH utils library Include files */
#include <ti/utils/mathutils/mathutils.h>

/** @defgroup MMWDEMO_RFPARSER_INTERNAL       Mmwdemo RFparser Internal
 */

/**
@defgroup MMWDEMO_RFPARSER_INTERNAL_FUNCTION            RF Parser Internal Functions
@ingroup MMWDEMO_RFPARSER_INTERNAL
@brief
*   The section has a list of all internal API which are not exposed to the external
*   applications.
*/
/**
@defgroup MMWDEMO_RFPARSER_INTERNAL_DATA_STRUCTURE      RF Parser Internal Data Structures
@ingroup MMWDEMO_RFPARSER_INTERNAL
@brief
*   The section has a list of all internal data structures which are used internally
*   by the RF Parser module.
*/
/**
@defgroup MMWDEMO_RFPARSER_INTERNAL_DEFINITION          RF Parser Internal Definitions
@ingroup MMWDEMO_RFPARSER_INTERNAL
@brief
*   The section has a list of all internal definitions which are used internally
*   by the RF Parser.
*/


/** @addtogroup MMWDEMO_RFPARSER_INTERNAL_DEFINITION
 *
 @{ */

/*! Speed of light in m/s expressed in float */
#define MMWDEMO_RFPARSER_SPEED_OF_LIGHT_IN_METERS_PER_SEC (3.0e8)

/** @} */

/**
 * @brief
 *  Data Source Hardware configuration definition
 *
 * @details
 *  The structure describes the hardware related configuration for device and evm
 *
 *  \ingroup MMWDEMO_RFPARSER_INTERNAL_DATA_STRUCTURE
 */
typedef struct MmwDemo_RFParserHwAttr_t
{
    /**
     * @brief   ADC buffer size
     */
    uint32_t      adcBufSize;

    /**
     * @brief   Tx Antenna mask for elevation, antenna pattern specific
     */
    uint8_t       elevTxAntMask;

    /**
     * @brief   Tx Antenna mask for azimuth, antenna pattern specific
     */
    uint8_t       azimTxAntMask;
} MmwDemo_RFParserHwAttr;

/*================================================================
               RF Parser platform dependent params
 ================================================================*/
#ifdef SOC_XWR14XX
MmwDemo_RFParserHwAttr MmwDemo_RFParserHwCfg =
{
    SOC_XWR14XX_MSS_ADCBUF_SIZE,
    0x2,
    0x5
};
#endif

#ifdef SOC_XWR16XX
#ifdef SUBSYS_DSS
MmwDemo_RFParserHwAttr MmwDemo_RFParserHwCfg =
{
    SOC_ADCBUF_SIZE,
    0,
    0x3
};
#endif

#ifdef SUBSYS_MSS
MmwDemo_RFParserHwAttr MmwDemo_RFParserHwCfg =
{
    SOC_ADCBUF_SIZE,
    0,
    0x3
};
#endif

#endif

#ifdef SOC_XWR18XX

#ifdef SUBSYS_MSS
MmwDemo_RFParserHwAttr MmwDemo_RFParserHwCfg =
{
    SOC_ADCBUF_SIZE,
    0x2,
    0x5
};
#endif

#ifdef SUBSYS_DSS
MmwDemo_RFParserHwAttr MmwDemo_RFParserHwCfg = 
{
    SOC_ADCBUF_SIZE,
    0x2,
    0x5
};
#endif

#endif

#ifdef SOC_XWR68XX

#ifdef SUBSYS_MSS
MmwDemo_RFParserHwAttr MmwDemo_RFParserHwCfg =
{
    SOC_ADCBUF_SIZE,
    0x2,
    0x5
};
#endif

#ifdef SUBSYS_DSS
MmwDemo_RFParserHwAttr MmwDemo_RFParserHwCfg =
{
    SOC_ADCBUF_SIZE,
    0x2,
    0x5
};
#endif

#endif
/*================================================================
               RF Parser internal APIs
 ================================================================*/

/**
 *  @b Description
 *  @n
 *      Help Function to get frame period
 *
 *  @param[in] ctrlCfg       Handle to MMWave control configuration
 *  @param[in] subFrameIndx  Sub frame index
 *
 *  \ingroup MMWDEMO_RFPARSER_INTERNAL_FUNCTION
 *
 *  @retval
 *      Frame period
 */
static float MmwDemo_RFParser_getFramePeriod_ms(MMWave_CtrlCfg *ctrlCfg, uint8_t subFrameIndx)
{
    if (ctrlCfg->dfeDataOutputMode == MMWave_DFEDataOutputMode_ADVANCED_FRAME)
    {
        return(ctrlCfg->u.advancedFrameCfg.frameCfg.frameSeq.subFrameCfg[subFrameIndx].subFramePeriodicity * 0.000005f);
    }
    else
    {
        return((float)ctrlCfg->u.frameCfg.frameCfg.framePeriodicity * 0.000005f);
    }
}


/**
 *  @b Description
 *  @n
 *      Help Function to get chirp start Index
 *
 *  @param[in] ctrlCfg       Handle to MMWave control configuration
 *  @param[in] subFrameIndx  Sub frame index
 *
 *  \ingroup MMWDEMO_RFPARSER_INTERNAL_FUNCTION
 *
 *  @retval
 *      Chirp start index
 */
static uint16_t MmwDemo_RFParser_getChirpStartIdx(MMWave_CtrlCfg *ctrlCfg, uint8_t subFrameIndx)
{
    if (ctrlCfg->dfeDataOutputMode == MMWave_DFEDataOutputMode_ADVANCED_FRAME)
    {
        return(ctrlCfg->u.advancedFrameCfg.frameCfg.frameSeq.subFrameCfg[subFrameIndx].chirpStartIdx);
    }
    else
    {
        return(ctrlCfg->u.frameCfg.frameCfg.chirpStartIdx);
    }
}

/**
 *  @b Description
 *  @n
 *      Help Function to get chirp stop Index
 *
 *  @param[in] ctrlCfg       Handle to MMWave control configuration
 *  @param[in] subFrameIndx  Sub frame index
 *
 *  \ingroup MMWDEMO_RFPARSER_INTERNAL_FUNCTION
 *
 *  @retval
 *      Chirp stop index
 */
static uint16_t MmwDemo_RFParser_getChirpEndIdx(MMWave_CtrlCfg *ctrlCfg, uint8_t subFrameIndx)
{
    if (ctrlCfg->dfeDataOutputMode == MMWave_DFEDataOutputMode_ADVANCED_FRAME)
    {
        return(ctrlCfg->u.advancedFrameCfg.frameCfg.frameSeq.subFrameCfg[subFrameIndx].chirpStartIdx +
              (ctrlCfg->u.advancedFrameCfg.frameCfg.frameSeq.subFrameCfg[subFrameIndx].numOfChirps - 1));
    }
    else
    {
        return(ctrlCfg->u.frameCfg.frameCfg.chirpEndIdx);
    }
}

/**
 *  @b Description
 *  @n
 *      Help Function to get number of loops
 *
 *  @param[in] ctrlCfg       Handle to MMWave control configuration
 *  @param[in] subFrameIndx  Sub frame index
 *
 *  \ingroup MMWDEMO_RFPARSER_INTERNAL_FUNCTION
 *
 *  @retval
 *      Number of loops
 */
static uint16_t MmwDemo_RFParser_getNumLoops(MMWave_CtrlCfg *ctrlCfg, uint8_t subFrameIndx)
{
    if (ctrlCfg->dfeDataOutputMode == MMWave_DFEDataOutputMode_ADVANCED_FRAME)
    {
        return(ctrlCfg->u.advancedFrameCfg.frameCfg.frameSeq.subFrameCfg[subFrameIndx].numLoops);
    }
    else
    {
        return(ctrlCfg->u.frameCfg.frameCfg.numLoops);
    }
}

/**
 *  @b Description
 *  @n
 *      Help Function to get profile handle
 *
 *  @param[in] ctrlCfg          Handle to MMWave control configuration
 *  @param[in] profileLoopIdx   Profile index
 *
 *  \ingroup MMWDEMO_RFPARSER_INTERNAL_FUNCTION
 *
 *  @retval
 *      Profile handle
 */
static MMWave_ProfileHandle MmwDemo_RFParser_getProfileHandle(MMWave_CtrlCfg *ctrlCfg, uint32_t profileLoopIdx)
{
    if (ctrlCfg->dfeDataOutputMode == MMWave_DFEDataOutputMode_ADVANCED_FRAME)
    {
        return(ctrlCfg->u.advancedFrameCfg.profileHandle[profileLoopIdx]);
    }
    else
    {
        return(ctrlCfg->u.frameCfg.profileHandle[profileLoopIdx]);
    }
}

#ifdef USE_2D_AOA_DPU
/**
 *  @b Description
 *  @n
 *      Helper function that parses chirp Tx antenna configuration and extracts parameters
 *      needed for AoA configuration depending on the AoA DPU needs
 *
 *  @param[inout]   outParams               Pointer to parameters generated after parsing configuration
 *  @param[inout]   pFoundValidProfile      flag to indicate if this is valid profile; if not, advance to the next one
 *  @param[in]      frameTotalChirps        Total chirps in the frame (used for looping through validChirpTxEnBits)
 *  @param[in]      validChirpTxEnBits      Array of chirp's txEn bits. Dimension is provided by frameTotalChirps
 *  @param[in]      bpmEnabled              BPM flag, 0 -disabled, 1-enabled
 *
 *  \ingroup MMWDEMO_RFPARSER_INTERNAL_FUNCTION
 *
 *  @retval
 *      Success -   0
 *      Fail        <0, one of error codes @ref MMWDEMO_RFPARSER_ERROR_CODE
 */
static int32_t MmwDemo_RFParser_setAoAParams
(
    MmwDemo_RFParserOutParams  *outParams,
    bool                       *pFoundValidProfile,
    int16_t                     frameTotalChirps,
    uint16_t                   *validChirpTxEnBits,
    bool                        bpmEnabled
)
{
    uint32_t    chirpLoopIdx;
    bool        validProfileHasOneTxPerChirp = false;
    uint16_t    validProfileTxEn = 0;
    int32_t     retVal = 0;
    int32_t     i;

    
    /* for this antenna pattern we require that all Rx's are enabled */
    if (outParams->numRxAntennas != SYS_COMMON_NUM_RX_CHANNEL)
    {
        retVal = MMWDEMO_RFPARSER_EINVAL__NUM_RX_ANTENNAS;
        goto exit;
    }
    
    /* now loop through unique chirps and check if we found all of the ones
       needed for the frame and then determine the azimuth/elevation antenna
       configuration
     */
    if (*pFoundValidProfile==true) {
        for (chirpLoopIdx = 0; chirpLoopIdx < frameTotalChirps; chirpLoopIdx++)
        {
            bool        validChirpHasOneTxPerChirp = false;
            uint8_t     log2TxEn;
            uint16_t    chirpTxEn = validChirpTxEnBits[chirpLoopIdx];
            if (chirpTxEn == 0) {
                /* this profile doesn't have all the needed chirps */
                *pFoundValidProfile = false;
                break;
            }

            /* If only TX antenna is enabled, then its 0x1<< log2TxEn should equal chirpTxEn */
            log2TxEn = mathUtils_floorLog2(chirpTxEn);
            validChirpHasOneTxPerChirp = (chirpTxEn == (1 << log2TxEn));

            /* for this antenna pattern we require that only one Tx per chirp is enabled*/
            if (validChirpHasOneTxPerChirp != true)
            {
                /* this profile doesn't have chirps with one TxAnt enabled per Chirp */
                *pFoundValidProfile = false;
                break;
            }

            /* if this is the first chirp, record the chirp's
            MIMO config as profile's MIMO config. We dont handle intermix
            at this point */
            if (chirpLoopIdx == 0)
            {
                validProfileHasOneTxPerChirp = validChirpHasOneTxPerChirp;
            }
            /* check the chirp's MIMO config against Profile's MIMO config */
            if (validChirpHasOneTxPerChirp != validProfileHasOneTxPerChirp)
            {
                /* this profile doesnt have all chirps with same MIMO config */
                *pFoundValidProfile = false;
                break;
            }

            /* save the antennas actually enabled in this profile */
            validProfileTxEn |= chirpTxEn;
        }
    }

    /* found valid chirps for the frame; mark this profile valid */
    if (*pFoundValidProfile == true) {
        uint16_t        tempValidProfileTxEn=0;
        
        /* set Tx Antenna and Virtual antenna related config */
        outParams->numTxAntennas = 0;
        tempValidProfileTxEn = validProfileTxEn;
        while (tempValidProfileTxEn!=0) {
            if ((tempValidProfileTxEn&0x1)==0x1)
            {
                outParams->numTxAntennas++;
            }
            tempValidProfileTxEn=tempValidProfileTxEn>>1;
        }
        if (outParams->numTxAntennas > SYS_COMMON_NUM_TX_ANTENNAS)
        {
            retVal = MMWDEMO_RFPARSER_EINVAL_NUM_TX_ANTENNAS;
            goto exit;
        }
        outParams->numVirtualAntAzim = 0; // unused
        outParams->numVirtualAntElev = 0; // unused
        outParams->numVirtualAntennas = outParams->numTxAntennas * outParams->numRxAntennas;
        /* Sanity Check: Ensure that the number of antennas is within system limits */
        if ((outParams->numVirtualAntennas <= 0) ||
           (outParams->numVirtualAntennas > (SYS_COMMON_NUM_TX_ANTENNAS * SYS_COMMON_NUM_RX_CHANNEL)))
        {
            retVal = MMWDEMO_RFPARSER_EINVAL__NUM_VIRTUAL_ANTENNAS;
        }

        /* txAntOrder[] will be needed for Rx Channel Phase Measurement/Compensation routines */
        for (i = 0; i < outParams->numTxAntennas; i++)
        {
            outParams->txAntOrder[i] = mathUtils_floorLog2(validChirpTxEnBits[i]);
        }

        outParams->validProfileHasOneTxPerChirp = validProfileHasOneTxPerChirp;
    }
    
exit:
    return (retVal);    
}


#else
/**
 *  @b Description
 *  @n
 *      Helper function that parses chirp Tx antenna configuration and extracts parameters
 *      needed for AoA configuration depending on the AoA DPU needs
 *
 *  @param[inout]   outParams               Pointer to parameters generated after parsing configuration
 *  @param[inout]   pFoundValidProfile      flag to indicate if this is valid profile; if not, advance to the next one
 *  @param[in]      frameTotalChirps        Total chirps in the frame (used for looping through validChirpTxEnBits)
 *  @param[in]      validChirpTxEnBits      Array of chirp's txEn bits. Dimension is provided by frameTotalChirps
 *  @param[in]      bpmEnabled              BPM flag, 0 -disabled, 1-enabled
 *
 *  \ingroup MMWDEMO_RFPARSER_INTERNAL_FUNCTION
 *
 *  @retval
 *      Success -   0
 *      Fail        <0, one of error codes @ref MMWDEMO_RFPARSER_ERROR_CODE
 */
static int32_t MmwDemo_RFParser_setAoAParams
(
    MmwDemo_RFParserOutParams  *outParams,
    bool                       *pFoundValidProfile,
    int16_t                     frameTotalChirps,
    uint16_t                   *validChirpTxEnBits,
    bool                        bpmEnabled
)
{
    
    uint32_t    chirpLoopIdx;
    bool        validProfileHasOneTxPerChirp = false;
    uint16_t    validProfileTxEn = 0;
    int32_t     retVal = 0;
    bool        validProfileHasElevation = false;
    int32_t     i;
        

    /* now loop through unique chirps and check if we found all of the ones
       needed for the frame and then determine the azimuth/elevation antenna
       configuration
     */
    if (*pFoundValidProfile==true) {
        int16_t nonElevFirstChirpIdx = -1;
        for (chirpLoopIdx = 0; chirpLoopIdx < frameTotalChirps; chirpLoopIdx++)
        {
            bool validChirpHasElevation = false;
            bool validChirpHasOneTxPerChirp = false;
            uint16_t chirpTxEn = validChirpTxEnBits[chirpLoopIdx];
            if (chirpTxEn == 0) {
                /* this profile doesn't have all the needed chirps */
                *pFoundValidProfile = false;
                break;
            }

            /* check if this is an elevation TX chirp - if yes, it is assumed to be 4Rx, 3Tx case */
            validChirpHasElevation = (chirpTxEn == MmwDemo_RFParserHwCfg.elevTxAntMask);
            validProfileHasElevation |= validChirpHasElevation;

            /* if not, then check the MIMO config */
            if (!validChirpHasElevation)
            {
                uint8_t     log2TxEn;

                if(bpmEnabled)
                {   /* In case of BPM, check if both TX antennas are enabled*/
                    if(chirpTxEn != MmwDemo_RFParserHwCfg.azimTxAntMask)
                    {
                        /* The frame is configured as BPM but this chirp does not enable both TX antennas*/
                        *pFoundValidProfile = false;
#ifdef MMWDEMO_RFPARSER_DBG
                        System_printf("Bad BPM configuration. chirpTxEn=%d for chirp %d \n",chirpTxEn,chirpLoopIdx);
#endif
                        break;
                    }
                }
                else
                {
                    /* If only TX antenna is enabled, then its 0x1<< log2TxEn should equal chirpTxEn */
                    log2TxEn = mathUtils_floorLog2(chirpTxEn);
                    validChirpHasOneTxPerChirp = (chirpTxEn == (1 << log2TxEn));
                }

                /* if this is the first chirp without elevation, record the chirp's
                   MIMO config as profile's MIMO config. We dont handle intermix
                   at this point */
                if (nonElevFirstChirpIdx == -1) {
                    validProfileHasOneTxPerChirp = validChirpHasOneTxPerChirp;
                    nonElevFirstChirpIdx = chirpLoopIdx;
                }

                /* if this is the first chirp, record the chirp's
                   MIMO config as profile's MIMO config. We dont handle intermix
                   at this point */
                if (chirpLoopIdx == 0)
                {
                    validProfileHasOneTxPerChirp = validChirpHasOneTxPerChirp;
                }
                /* check the chirp's MIMO config against Profile's MIMO config */
                if (validChirpHasOneTxPerChirp != validProfileHasOneTxPerChirp)
                {
                    /* this profile doesnt have all chirps with same MIMO config */
                    *pFoundValidProfile = false;
                    break;
                }
            }

            /* save the antennas actually enabled in this profile */
            validProfileTxEn |= chirpTxEn;
        }
    }

    /* found valid chirps for the frame; mark this profile valid */
    if (*pFoundValidProfile == true) {
        uint32_t        numTxAntAzim = 0;
        uint32_t        numTxAntElev = 0;

        outParams->numTxAntennas = 0;
        if (validProfileHasElevation)
        {
            numTxAntElev = 1;
        }

        if (bpmEnabled == true)
        {
            /* BPM eanbled */
            numTxAntAzim = 2;
        }
        else if (validProfileHasOneTxPerChirp == true)
        {
            uint8_t log2TxEn;

            while(validProfileTxEn)
            {
                log2TxEn = mathUtils_floorLog2(validProfileTxEn);
                if ((0x1 << log2TxEn) & MmwDemo_RFParserHwCfg.azimTxAntMask)
                {
                    numTxAntAzim++;
                }
                validProfileTxEn &= ~(0x1<< log2TxEn);
            }
        }
        else /* i.e. SIMO case, all chirps have same one Tx antenna. */
        {
            /* in this case, for AOA, Tx Azimuth antenna is only 1. */
            if ((validProfileTxEn & MmwDemo_RFParserHwCfg.azimTxAntMask) != 0)
            {
                numTxAntAzim = 1;
            }
            else
            {
                numTxAntAzim = 0;
            }
        }

#ifdef MMWDEMO_RFPARSER_DBG
        System_printf("Azimuth Tx: %d (MIMO:%d), Elev Tx:%d\n",
                       numTxAntAzim,validProfileHasOneTxPerChirp,numTxAntElev);
#endif

        outParams->numTxAntennas = numTxAntAzim + numTxAntElev;
        if (outParams->numTxAntennas > SYS_COMMON_NUM_TX_ANTENNAS)
        {
            retVal = MMWDEMO_RFPARSER_EINVAL_NUM_TX_ANTENNAS;
            goto exit;
        }

        outParams->numVirtualAntAzim = numTxAntAzim * outParams->numRxAntennas;
        outParams->numVirtualAntElev = numTxAntElev * outParams->numRxAntennas;
        outParams->numVirtualAntennas = outParams->numVirtualAntAzim +
                                              outParams->numVirtualAntElev;

        /* Sanity Check: Ensure that the number of antennas is within system limits */
        if ((outParams->numVirtualAntennas <= 0) ||
           (outParams->numVirtualAntennas > (SYS_COMMON_NUM_TX_ANTENNAS * SYS_COMMON_NUM_RX_CHANNEL)))
        {
            retVal = MMWDEMO_RFPARSER_EINVAL__NUM_VIRTUAL_ANTENNAS;
        }

        /* txAntOrder[] will be needed for Rx Channel Phase Measurement/Compensation routines */
        if (validProfileHasOneTxPerChirp)
        {
            for (i = 0; i < outParams->numTxAntennas; i++)
            {
                outParams->txAntOrder[i] = mathUtils_floorLog2(validChirpTxEnBits[i]);
            }
        }
        else
        {
            for (i = 0; i < outParams->numTxAntennas; i++)
            {
                outParams->txAntOrder[i] = i;
            }
        }

        outParams->validProfileHasOneTxPerChirp = validProfileHasOneTxPerChirp;
        
#ifdef MMWDEMO_RFPARSER_DBG
        System_printf("Ant setting virtualAzim: %d , virtual Elev :%d\n",
                        outParams->numVirtualAntAzim, outParams->numVirtualAntElev);
#endif
    }
    
exit:
    return (retVal);        
}

#endif

/**
 *  @b Description
 *  @n
 *      Helper function that parses Profile, Chirp and Frame config and extracts parameters
 *      needed for processing chain configuration
 *
 *  @param[out] outParams      Pointer to parameters generated after parsing configuration
 *  @param[in]  subFrameIdx    Sub-frame index
 *  @param[in]  openCfg              Pointer to the MMWave Open configuration
 *  @param[in]  ctrlCfg              Pointer to the MMWave Control configuration
 *  @param[in]  rfFreqScaleFactor RF frequency scale factor, see SOC_getDeviceRFFreqScaleFactor API
 *                                in SOC driver
 *  @param[in]  bpmEnabled     BPM flag, 0 -disabled, 1-enabled
 *
 *  \ingroup MMWDEMO_RFPARSER_INTERNAL_FUNCTION
 *
 *  @retval
 *      Success -   0
 *      Fail        <0, one of error codes @ref MMWDEMO_RFPARSER_ERROR_CODE
 */
static int32_t MmwDemo_RFParser_parseCtrlConfig
(
    MmwDemo_RFParserOutParams  *outParams,
    uint8_t              subFrameIdx,
    MMWave_OpenCfg      *openCfg,
    MMWave_CtrlCfg      *ctrlCfg,
    float               rfFreqScaleFactor,
    bool                bpmEnabled
)
{
    uint16_t    frameChirpStartIdx;
    uint16_t    frameChirpEndIdx;
    int16_t     frameTotalChirps;
    uint32_t    profileLoopIdx, chirpLoopIdx;
    bool        foundValidProfile = false;
    uint16_t    channelTxEn = openCfg->chCfg.txChannelEn;
    uint8_t     channel;
    uint8_t     numRxAntennas;
    uint16_t    numLoops;
    int32_t     retVal = 0;
    int32_t     errCode;
    float       bandwidth, centerFreq, adcStart, slope, startFreq;

    /***********************************************
     * Sanity Check on ADC configuration
     ***********************************************/
    /* Only support 16 Bits ADC out bits */
    if(openCfg->adcOutCfg.fmt.b2AdcBits != 2U)
    {
        retVal = MMWDEMO_RFPARSER_ENOTSUPPORT__NON_16BITS_ADC;
        goto exit;
    }

    /* Only support complex ADC data format */
    if((openCfg->adcOutCfg.fmt.b2AdcOutFmt != 1U) &&
       (openCfg->adcOutCfg.fmt.b2AdcOutFmt != 2U))
    {
        retVal = MMWDEMO_RFPARSER_ENOTSUPPORT__NON_COMPLEX_ADC_FORMAT;
        goto exit;
    }

    /***********************************************
     * Parse openCfg
     ***********************************************/
    /* Find number of enabled channels */
    numRxAntennas = 0U;
    for (channel = 0U; channel < SYS_COMMON_NUM_RX_CHANNEL; channel++)
    {
        if(openCfg->chCfg.rxChannelEn & (0x1U << channel))
        {
            outParams->rxAntOrder[numRxAntennas] = channel;
            /* Track the number of receive channels: */
            numRxAntennas++;
        }
        else
        {
            outParams->rxAntOrder[channel] = 0U;
        }

        //add check to make sure lambda/2
        //check for rxAnt -= 1, 2, 4 and their limitations
    }
    outParams->numRxAntennas = numRxAntennas;



    /***********************************************
     * Parse frameCfg
     ***********************************************/
    /* Read frameCfg chirp start/stop index */
    frameChirpStartIdx  = MmwDemo_RFParser_getChirpStartIdx(ctrlCfg, subFrameIdx);
    frameChirpEndIdx    = MmwDemo_RFParser_getChirpEndIdx(ctrlCfg, subFrameIdx);
    numLoops            = MmwDemo_RFParser_getNumLoops(ctrlCfg, subFrameIdx);    
    outParams->framePeriod  =  MmwDemo_RFParser_getFramePeriod_ms(ctrlCfg, subFrameIdx);
    frameTotalChirps    = frameChirpEndIdx - frameChirpStartIdx + 1;

    /* TODO::Advance Frame only support one burst - chain limitation,  */
    if (ctrlCfg->dfeDataOutputMode == MMWave_DFEDataOutputMode_ADVANCED_FRAME)
    {
        if(ctrlCfg->u.advancedFrameCfg.frameCfg.frameSeq.subFrameCfg[subFrameIdx].numOfBurst != 1)
        {
            retVal = MMWDEMO_RFPARSER_ENOTSUPPORT__NON_ONE_NUMOFBURST_FOR_ADVANCED_FRAME;
            goto exit;
        }
    }

    /* since validChirpTxEnBits is static array of 32 */
    if(frameTotalChirps > 32U)
    {
        retVal = MMWDEMO_RFPARSER_ENOIMPL__NUM_UNIQUE_CHIRPS_MORE_THAN_32;
    }

    /* loop for profiles and find if it has valid chirps */
    /* we support only one profile in this processing chain */
    for (profileLoopIdx = 0;
        ((profileLoopIdx < MMWAVE_MAX_PROFILE) && (foundValidProfile == false));
        profileLoopIdx++)
    {
        uint32_t    mmWaveNumChirps = 0;
        uint16_t    validChirpTxEnBits[32]={0};
        MMWave_ProfileHandle profileHandle;

        profileHandle = MmwDemo_RFParser_getProfileHandle(ctrlCfg, profileLoopIdx);
        if (profileHandle == NULL)
            continue; /* skip this profile */

        /* get numChirps for this profile; skip error checking */
        retVal = MMWave_getNumChirps(profileHandle, &mmWaveNumChirps, &errCode);
        if (retVal != 0)
        {
            retVal = errCode;
            goto exit;
        }

        /* loop for chirps and find if it has valid chirps for the frame
           looping around for all chirps in a profile, in case
           there are duplicate chirps
         */
        for (chirpLoopIdx = 1; chirpLoopIdx <= mmWaveNumChirps; chirpLoopIdx++)
        {
            MMWave_ChirpHandle chirpHandle;
            retVal = MMWave_getChirpHandle(profileHandle, chirpLoopIdx, &chirpHandle, &errCode);
            if (retVal != 0)
            {
                retVal = errCode;
                goto exit;
            }
            /* get handle and read ChirpCfg */
            {
                rlChirpCfg_t chirpCfg;
                retVal = MMWave_getChirpCfg(chirpHandle, &chirpCfg, &errCode);
                if (retVal != 0)
                {
                    retVal = errCode;
                    goto exit;
                }
                {
                    uint16_t chirpTxEn = chirpCfg.txEnable;
                    /* do chirps fall in range and has valid antenna enabled */
                    if ((chirpCfg.chirpStartIdx >= frameChirpStartIdx) &&
                        (chirpCfg.chirpEndIdx <= frameChirpEndIdx) &&
                        ((chirpTxEn & channelTxEn) > 0))
                    {
                        uint16_t idx = 0;
                        for (idx = (chirpCfg.chirpStartIdx - frameChirpStartIdx);
                             idx <= (chirpCfg.chirpEndIdx - frameChirpStartIdx); idx++)
                        {
                            validChirpTxEnBits[idx] = chirpTxEn;
                            foundValidProfile = true;
                        }
                    }
                }
            }
        }

        /* now parse through all valid chirps, check if the profile is valid and then set the AoA related parameters */
        retVal = MmwDemo_RFParser_setAoAParams(outParams,
                                               &foundValidProfile,
                                               frameTotalChirps,
                                               validChirpTxEnBits,
                                               bpmEnabled);
        if (retVal != 0)
        {
            goto exit;
        }

        /* found valid chirps for the frame; set remaining parameters */
        if (foundValidProfile == true) {
            rlProfileCfg_t  profileCfg;
            
            outParams->validProfileIdx = profileLoopIdx;
            /* Get the profile configuration: */
            retVal = MMWave_getProfileCfg(profileHandle,&profileCfg, &errCode);
            if (retVal != 0)
            {
                retVal = errCode;
                goto exit;
            }
            
#ifndef MMW_ENABLE_NEGATIVE_FREQ_SLOPE
            /* Check frequency slope */
            if (profileCfg.freqSlopeConst < 0)
            {
                retVal = MMWDEMO_RFPARSER_ENOTSUPPORT__NEGATIVE_FREQ_SLOPE;
                goto exit;
            }
#endif
            /* set other parameters */
            outParams->numAdcSamples = profileCfg.numAdcSamples;
            outParams->numRangeBins = mathUtils_pow2roundup(outParams->numAdcSamples);
            outParams->numChirpsPerFrame = frameTotalChirps * numLoops;

            outParams->numDopplerChirps = outParams->numChirpsPerFrame/outParams->numTxAntennas;
            outParams->numDopplerBins = mathUtils_pow2roundup(outParams->numDopplerChirps);
            
            adcStart                        =   ((float)profileCfg.adcStartTimeConst * 10.f * 1.e-9);
            startFreq                       =   (float)profileCfg.startFreqConst/(float)(1U << 26)*rfFreqScaleFactor*(float)1e9;
            slope                           =   (float)profileCfg.freqSlopeConst * ((rfFreqScaleFactor*1e3*900.f)/(float)(1U << 26)) * 1e12;
            bandwidth                       =   (slope * outParams->numAdcSamples)/(profileCfg.digOutSampleRate * 1e3);            
            centerFreq                      =   startFreq + bandwidth * 0.5f + adcStart * slope;            
            outParams->chirpInterval        =   (float)(profileCfg.idleTimeConst + profileCfg.rampEndTime)/1000.*10*1.e-6;

            outParams->rangeStep            =   (MMWDEMO_RFPARSER_SPEED_OF_LIGHT_IN_METERS_PER_SEC * profileCfg.digOutSampleRate * 1e3) /
                                                (2.f * slope * outParams->numRangeBins);
            outParams->rangeResolution      =   (MMWDEMO_RFPARSER_SPEED_OF_LIGHT_IN_METERS_PER_SEC * profileCfg.digOutSampleRate * 1e3) /
                                                (2.f * slope * outParams->numAdcSamples);
            
            outParams->dopplerStep          =   MMWDEMO_RFPARSER_SPEED_OF_LIGHT_IN_METERS_PER_SEC /
                                                (2.f * outParams->numDopplerBins * outParams->numTxAntennas * 
                                                centerFreq * outParams->chirpInterval);            
            outParams->dopplerResolution    =   MMWDEMO_RFPARSER_SPEED_OF_LIGHT_IN_METERS_PER_SEC /
                                                (2.f * outParams->numChirpsPerFrame * centerFreq * outParams->chirpInterval);            
            
#ifdef MMWDEMO_RFPARSER_DBG        
            System_printf("Ant setting virtualAzim: %d , virtual Elev :%d\n",
                            outParams->numVirtualAntAzim, outParams->numVirtualAntElev);
            System_printf("startFreqConst: %d\n", profileCfg.startFreqConst);
            System_printf("rfFreqScaleFactor: %f\n", rfFreqScaleFactor);
            System_printf("bandwidth : %f GHz\n", bandwidth*1.e-9);
            System_printf("adcStartTimeConst: %d\n", profileCfg.adcStartTimeConst);
            System_printf("freqSlopeConst: %d\n", profileCfg.freqSlopeConst);
            System_printf("centerFreq: %f GHz\n", centerFreq*1.e-9);
            System_printf("dopplerStep: %f\n", outParams->dopplerStep);
            System_printf("adcStart: %f us\n", adcStart * 1e6);
            System_printf("slope: %f GHz\n", slope*1.e-9);
            System_printf("startFreq: %f GHz\n", startFreq*1.e-9);
#endif
            
        }
    }

    if (foundValidProfile == false)
    {
        retVal = MMWDEMO_RFPARSER_EINVAL__VALID_PROFILECFG_NOT_FOUND;
        goto exit;
    }

exit:
    return (retVal);
}

/**
 *  @b Description
 *  @n
 *      Helper function that parses ADCBuf configuration to be used to configure ADCBuf driver
 *
 *  @param[out] outParams      Pointer to parameters generated after parsing configuration
 *  @param[in]  adcBufCfg            Pointer to ADCBuf configuration
 *
 *  \ingroup MMWDEMO_RFPARSER_INTERNAL_FUNCTION
 *
 *  @retval
 *      Success -   0
 *      Fail        < 0, one of @ref MMWDEMO_RFPARSER_ERROR_CODE
 */
static int32_t MmwDemo_RFParser_parseADCBufCfg
(
    MmwDemo_RFParserOutParams   *outParams,
    MmwDemo_ADCBufCfg     *adcBufCfg
)
{
    uint16_t            numBytePerSample = 0;
    uint32_t            chirpThreshold;
    uint32_t            maxChirpThreshold;
    uint32_t            bytesPerChirp;
    int32_t             retVal = 0;

    /* Only support Complex */
    if (adcBufCfg->adcFmt != 0)
    {
        retVal = MMWDEMO_RFPARSER_ENOTSUPPORT__NONCOMPLEX_ADC_FORMAT;
        goto exit;
    }

    /* Complex dataFormat has 4 bytes */
    numBytePerSample = 4U;

    /* Calculate RX channel data size and make it align to 16 bytes */
    outParams->adcBufChanDataSize =  outParams->numAdcSamples * numBytePerSample;
    outParams->adcBufChanDataSize = (outParams->adcBufChanDataSize + 15U) / 16U * 16U;

    /* Calculate max possible chirp threshold */
    bytesPerChirp = outParams->adcBufChanDataSize * outParams->numRxAntennas;

    /* find maximum number of full chirps that can fit in the ADCBUF memory, while
       also being able to divide numChirpsPerFrame, we do not want remainder processing */
    maxChirpThreshold = MmwDemo_RFParserHwCfg.adcBufSize/ bytesPerChirp;
    if (maxChirpThreshold >= outParams->numChirpsPerFrame)
    {
        maxChirpThreshold = outParams->numChirpsPerFrame;
        if (maxChirpThreshold > SYS_COMMON_CQ_MAX_CHIRP_THRESHOLD)
        {
            /* If CQ monitor is enabled, then check max chirpthreshold */
            maxChirpThreshold = SYS_COMMON_CQ_MAX_CHIRP_THRESHOLD;
        }
    }
    else
    {
        /* Find largest divisor of numChirpsPerFrame no bigger than maxChirpThreshold */
        while (outParams->numChirpsPerFrame % maxChirpThreshold)
        {
            maxChirpThreshold--;
        }
    }

    /* ADCBuf control function requires argument alignment at 4 bytes boundary */
    chirpThreshold = adcBufCfg->chirpThreshold;

    /* if automatic, set to the calculated max */
    if (chirpThreshold == 0)
    {
        chirpThreshold = maxChirpThreshold;
    }
    else
    {
        if (chirpThreshold > maxChirpThreshold)
        {
#ifdef MMWDEMO_RFPARSER_DBG
            System_printf("Desired chirpThreshold %d higher than max possible of %d, setting to max\n",
                chirpThreshold, maxChirpThreshold);
#endif
            retVal = MMWDEMO_RFPARSER_EINVAL__CHIRP_THRESH_GREATER_THAN_MAX_ALLOWED;
            goto exit;
        }
        else
        {
            /* check for divisibility of the user provided threshold */
            if((outParams->numChirpsPerFrame % chirpThreshold) != 0)
            {
                retVal = MMWDEMO_RFPARSER_ENOTSUPPORT__NON_DIVISIBILITY_OF_CHIRP_THRESH;
                goto exit;
            }
            else
            {
                /* Chirp threshold has a valid configuration */
            }
        }
    }

#ifdef MMWDEMO_RFPARSER_DBG
    System_printf(" chirpThreshold %d max = %d, \n",
                  chirpThreshold, maxChirpThreshold);
#endif

    /* Save chirpThreshold */
    outParams->numChirpsPerChirpEvent = chirpThreshold;

exit:
    return (retVal);
}

/**************************************************************
 * Exposed APIs
 **************************************************************/

/**
 *  @b Description
 *  @n
 *      The function is used to parse chirp/profile configurations and 
 *  save configuration and derived parameter in datapath parameter structure.
 *
 *  @param[out] outParams      Pointer to parameters generated after parsing configuration
 *  @param[in]  subFrameIdx    Sub-frame index
 *  @param[in]  openCfg        Pointer to the MMWave Open configuration
 *  @param[in]  ctrlCfg        Pointer to the MMWave Control configuration
 *  @param[in]  adcBufCfg      Pointer to ADCBuf configuration
 *  @param[in]  rfFreqScaleFactor RF frequency scale factor, see SOC_getDeviceRFFreqScaleFactor API
 *  @param[in]  bpmEnable      BPM flag, 0 -disabled, 1-enabled
 *
 *  \ingroup MMWDEMO_RFPARSER_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - = 0
 *  @retval
 *      Error       - < 0, one of @ref MMWDEMO_RFPARSER_ERROR_CODE
 */
int32_t MmwDemo_RFParser_parseConfig
(
    MmwDemo_RFParserOutParams    *outParams,
    uint8_t              subFrameIdx,
    MMWave_OpenCfg       *openCfg,
    MMWave_CtrlCfg       *ctrlCfg,
    MmwDemo_ADCBufCfg    *adcBufCfg,
    float                rfFreqScaleFactor,
    bool                 bpmEnable
)
{
    int32_t retVal;

    if(subFrameIdx < RL_MAX_SUBFRAMES)
    {
        /* Parse the profile and chirp configs and get the valid number of TX Antennas */
        retVal = MmwDemo_RFParser_parseCtrlConfig(outParams, subFrameIdx,
                                                  openCfg, ctrlCfg, rfFreqScaleFactor, bpmEnable);

        if (retVal != 0)
        {
            goto exit;
        }
        retVal = MmwDemo_RFParser_parseADCBufCfg(outParams, adcBufCfg);
        if (retVal != 0)
        {
            goto exit;
        }
    }
    else
    {
        retVal = MMWDEMO_RFPARSER_EINVAL__NUM_SUBFRAMES;
    }

exit:
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      The function is used to get number of sub-frames from the input
 *      chirp/profile configuration.
 *
 *  @param[in]  ctrlCfg        Pointer to the MMWave Control configuration
 *
 *  \ingroup MMWDEMO_RFPARSER_EXTERNAL_FUNCTION
 *
 *  @retval  Number of Sub-frames
 */
uint8_t MmwDemo_RFParser_getNumSubFrames(MMWave_CtrlCfg *ctrlCfg)
{
    if(ctrlCfg->dfeDataOutputMode == MMWave_DFEDataOutputMode_ADVANCED_FRAME)
    {
        return (ctrlCfg->u.advancedFrameCfg.frameCfg.frameSeq.numOfSubFrames);
    }
    else
    {
        return (1);
    }
}

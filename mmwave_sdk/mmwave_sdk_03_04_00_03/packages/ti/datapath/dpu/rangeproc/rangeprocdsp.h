/*
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
 
/**
 *   @file  rangeprocdsp.h
 *
 *   @brief
 *      Implements Data path range FFT processing functionality on DSP.
 */
/**
 *  @page dpu_rangedsp RangeProcDSP
 * [TOC]
 *  @section toplevel_dsp Top Level Design
 *
 *  RangeProcDSP has 3 stages in its processing:
 *  - Bring in ADC data through dataIn EDMA channels
 *  - FFT processing using DSPlib/mmwavelib
 *  - Transfer FFT results to radar cube through dataOut EDMA channels
 *
 *  The following diagram shows the top level design for rangeProcDSP.\n
 *
 * @image html rangeprocdsp_toplevel.png "rangeProcDSP Top Level"
 *
 *
 *  @section config_dsp Data Interface Parameter Range
 *
 *  Here are the supported ADCBuf and radarCube interface configurations:
 *
 *  ADCBuf Data Interface
 *----------------------
 *
 *   Parameter | Supported value
 *  :----------|:----------------:
 *   dataFmt | DPIF_DATAFORMAT_COMPLEX16_IMRE  ONLY
 *   interleave|non-interleave ONLY
 *   numChirpsPerChirpEvent|As ADCBuf memory permit
 *   numRxAntennas|1, 2, 4
 *   numAdcSamples|64 - 2048 (even number only)
 *
 *
 *  Radar Cube Data Interface
 *----------------------
 *
 *   Parameter | Supported value
 *  :----------|:----------------:
 *   dataFmt | DPIF_DATAFORMAT_COMPLEX16_IMRE  ONLY
 *   layoutFmt | DPIF_RADARCUBE_FORMAT_1
 *   numTxAntennas|1, 2 and 3
 *   numRangeBins|64 - 2048
 *   numChirpsPerFrame|As ADCBuf and HWA memory permit
 *
 *
 *
 *  @section input_dsp Data Input
 *
 *  RangeProcDSP DPU transfers ADCBuf data through dataIn EDMA channels in ping/pong alternate order to FFT
 *  input scratch buffer - adcDataIn.
 *
 *
 *  @section output_dsp Data Output
 *
 *  RangeProcDSP DPU transfer FFT results in scratch buffer(fftOut1D) to radarCube through dataOut EDMA channels
 *  in ping/pong alternate order.
 *
 *
 *  @section process_dsp Data Processing
 *
 *  Range FFT processing is done by using DSPlib and mmwavelib APIs. FFT input data is stored in input scratch
 *  buffer - adcDataIn, its output data is stored in output scratch buffer - fftOut1D.
 *
 *  As shown in the following diagram, for every chirp event @ref DPU_RangeProcDSP_process is called to process
 *  the data in ADCBuf buffer.
 *  If the hardware resources or data interfaces are changed for next frame, @ref DPU_RangeProcDSP_config can be called before the next frame starts.
 *
 *  DC signal removal configuration  can be updated at inter-frame time before the next frame starts.
 *
 * @image html dsp_callflow.png "rangeProcDSP call flow"
 *
 *
 *  @subsection calibDC_Range_dsp Antenna coupling signature removal
 *
 *  This feature is controlled through configuration @ref DPU_RangeProc_CalibDcRangeSigCfg.
 *  The configuration can be sent to rangeProc DPU through API @ref DPU_RangeProcDSP_config. \n
 *  The configuration can also be updated at runtime through control command @ref DPU_RangeProcDSP_Cmd_dcRangeCfg.
 *
 *  DC signal calibration and compensation is operated on fftOut1D data buffer for every chirp event.
 *
 * @image html dsp_dcremoval.png "rangeProcDSP Antenna DC signal removal"
 *
 *
 *  @section details_dsp Use Cases
 *  
 *  @subsection dsp_usecase_overview General Information
 *
 *  This Section describes some of the internal implementation for a few use cases for different number of TX antenna.
 *
 *  Regardless of number of TX antennas, 2 input EDMA channels and 2 output EDMA channels are needed for range FFT to  work in ping/pong manner.
 *  Ping input channel brings data into Ping region of local memory "adcDataIn", pong channel brings data into pong region.
 *
 *  After FFT, for 2 TX antenna, ping results in local memory "fftout1D" are copied to TX1 region in radar cube. Pong results are copied to TX2 region in radar cube.\n
 *  For 3 TX antenna, ping always handles the odd chirp data, pong always handle even chirp data. Range FFT results are copied to radar cube in following format:\n
 *
 *          TX1 region holds data for chirp index = 3 * (dopplerChirpIdx - 1) +1
 *          TX2 region holds data for chirp index = 3 * (dopplerChirpIdx - 1) +2
 *          TX3 region holds data for chirp index = 3 * dopplerChirpIdx
 *
 *          chirp index is in range [1,numChirpsPerFrame]
 *          dopplerChirpIdx is in range [1, numDopplerChirps = numChirpsPerFrame/numTxAntennas]
 *
 *  @subsection dsp_usecase1 Non-Interleaved RX channel data(1 or 2 TX Antenna) -> DPIF_RADARCUBE_FORMAT_1
 *  
 *  This use case is for configuration with with 1 or 2 TX antenna(diagram shows 2 TX antenna) with format:@ref DPIF_RADARCUBE_FORMAT_1.
 *
 *   Input params | Setting
 *  :------------|:-----------:
 *  InterleaveMode | Non-Interleave
 *  RadarCube format|DPIF_RADARCUBE_FORMAT_1
 *  numTxAnt| 1, 2
 *
 * @image html dsp_2tx.png "2 TX Non-interleaved data input to DPIF_RADARCUBE_FORMAT_1"
 *
 *
 *  @subsection dsp_usecase2 Non-Interleaved RX channel data(3 TX Antenna) -> DPIF_RADARCUBE_FORMAT_1
 *  
 *  This use case is for configuration with with 3 TX antenna with format:@ref DPIF_RADARCUBE_FORMAT_1.
 *
 *   Input params | Setting
 *  :------------|:-----------:
 *  InterleaveMode | Non-Interleave
 *  RadarCube format|DPIF_RADARCUBE_FORMAT_1
 *  numTxAnt| 3
 *
 * @image html dsp_3tx.png "3TX Non-interleaved data input to DPIF_RADARCUBE_FORMAT_1"
 *
 *
 */

/**************************************************************************
 *************************** Include Files ********************************
 **************************************************************************/
#ifndef RANGEPROCDSP_H
#define RANGEPROCDSP_H

/* Standard Include Files. */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/* Data Path Include files */
#include <ti/datapath/dpedma/dpedma.h>

/* DPIF Components Include Files */
#include <ti/datapath/dpif/dpif_adcdata.h>
#include <ti/datapath/dpif/dpif_radarcube.h>

#include <ti/datapath/dpu/rangeproc/rangeproc_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup DPU_RANGEPROC_ERROR_CODE
 *  Base error code for the rangeProc DPU is defined in the
 *  \include ti/datapath/dpif/dp_error.h
 @{ */

/**
 * @brief   Error Code: Invalid argument
 */
#define DPU_RANGEPROCDSP_EINVAL                  (DP_ERRNO_RANGE_PROC_BASE-1)

/**
 * @brief   Error Code: Out of memory
 */
#define DPU_RANGEPROCDSP_ENOMEM                  (DP_ERRNO_RANGE_PROC_BASE-2)

/**
 * @brief   Error Code: Internal error
 */
#define DPU_RANGEPROCDSP_EINTERNAL               (DP_ERRNO_RANGE_PROC_BASE-3)

/**
 * @brief   Error Code: Not implemented
 */
#define DPU_RANGEPROCDSP_ENOTIMPL                (DP_ERRNO_RANGE_PROC_BASE-4)

/**
 * @brief   Error Code: Not implemented
 */
#define DPU_RANGEPROCDSP_EINPROGRESS             (DP_ERRNO_RANGE_PROC_BASE-5)

/**
 * @brief   Error Code: Invalid control command
 */
#define DPU_RANGEPROCDSP_ECMD                    (DP_ERRNO_RANGE_PROC_BASE-6)

/**
 * @brief   Error Code: Invalid buffer pointer
 */
#define DPU_RANGEPROCDSP_EBUFFER_POINTER         (DP_ERRNO_RANGE_PROC_BASE-7)

/**
 * @brief   Error Code: Invalid buffer size
 */
#define DPU_RANGEPROCDSP_EBUFFER_SIZE            (DP_ERRNO_RANGE_PROC_BASE-8)


/**
@}
*/

/*! Alignment for DC range signal mean buffer */
#define DPU_RANGEPROCDSP_DCRANGESIGMEAN_BYTE_ALIGNMENT_DSP 8U

/*! Alignment for adcDataIn buffer */
#define DPU_RANGEPROCDSP_ADCDATAIN_BYTE_ALIGNMENT_DSP 8U

/*! Alignment for fftOut1D buffer */
#define DPU_RANGEPROCDSP_FFTOUT_BYTE_ALIGNMENT_DSP 8U

/*! Alignment for twiddle16x16 buffer */
#define DPU_RANGEPROCDSP_TWIDDLEBUF_BYTE_ALIGNMENT_DSP 8U

/*! Alignment for window buffer */
#define DPU_RANGEPROCDSP_WINDOW_BYTE_ALIGNMENT_DSP 8U

/**
 * @brief
 *  RangeProc EDMA configuration
 *
 * @details
 *  The structure is used to hold the EDMA configuration needed for Range FFT
 *
 *  \ingroup DPU_RANGEPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_RangeProcDSP_EDMAConfig_t
{
    /*! @brief     EDMA Handle */
    EDMA_Handle         edmaHandle;

    /*! @brief     EDMA configuration for range FFT data In- ping */
    DPEDMA_ChanCfg      dataInPing;

    /*! @brief     EDMA configuration for range FFT data In- pong */
    DPEDMA_ChanCfg      dataInPong;

    /*! @brief     EDMA configuration for range FFT data Out- ping */
    DPEDMA_ChanCfg      dataOutPing;

    /*! @brief     EDMA configuration for range FFT data Out- pong */
    DPEDMA_ChanCfg      dataOutPong;
}DPU_RangeProcDSP_EDMAConfig;

/**
 * @brief
 *  RangeProcDSP hardware resources
 *
 * @details
 *  The structure is used to hold the hardware resources needed for Range FFT
 *
 *  \ingroup DPU_RANGEPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_RangeProcDSP_HW_Resources_t
{
    /*! @brief     EDMA configuration for rangeProc data Input */
    DPU_RangeProcDSP_EDMAConfig     edmaCfg;

    /*! @brief     Pointer to Calibrate DC Range signature buffer
                    The size of the buffer = DPU_RANGEPROC_SIGNATURE_COMP_MAX_BIN_SIZE *
                                        numTxAntenna * numRxAntenna * sizeof(cmplx32ImRe_t)
                    byte alignment Requirement = @ref DPU_RANGEPROCDSP_DCRANGESIGMEAN_BYTE_ALIGNMENT_DSP
     */
    cmplx32ImRe_t       *dcRangeSigMean;

    /*! @brief     DC range calibration scratch buffer size */
    uint32_t            dcRangeSigMeanSize;

    /*! @brief      Scratch buffer pointer for twiddle table for range FFT 
                    Size: sizeof(cmplx16ImRe_t) * numRangeBins
                    Byte alignment Requirement = @ref DPU_RANGEPROCDSP_TWIDDLEBUF_BYTE_ALIGNMENT_DSP
     */
    cmplx16ImRe_t       *twiddle16x16;

    /*! @brief      Size of the Scratch buffer for twiddle table */
    uint32_t            twiddleSize;

    /*! @brief      Scratch buffer pointer for symmetric window coefficients for range FFT 
                    Size: sizeof(int16_t) * numADCSamples / 2
                    Byte alignment Requirement = @ref DPU_RANGEPROCDSP_WINDOW_BYTE_ALIGNMENT_DSP
     */
    int16_t             *window;

    /*! @brief      Size of the Scratch buffer for window coefficients */
    uint32_t            windowSize;

    /*! @brief      Scratch buffer pointer for ADCbuf input samples
                    Size: 2 * sizeof(cmplx16ImRe_t) * numRangeBins
                    Byte alignment Requirement = @ref DPU_RANGEPROCDSP_ADCDATAIN_BYTE_ALIGNMENT_DSP
     */
    cmplx16ImRe_t       *adcDataIn;

    /*! @brief      Size of the Scratch buffer for ADCBuf input */
    uint32_t            adcDataInSize;

    /*! @brief      Scratch buffer pointer for range FFT output
                    Size: sizeof(cmplx16ImRe_t) * numRangeBins * numRxAntenna * 2
                    Byte alignment Requirement = @ref DPU_RANGEPROCDSP_FFTOUT_BYTE_ALIGNMENT_DSP
     */
    cmplx16ImRe_t       *fftOut1D;

    /*! @brief      Size of the Scratch buffer for range FFT output */
    uint32_t            fftOut1DSize;

    /*! @brief      Pointer to Radar Cube buffer interface */
    DPIF_RadarCube      radarCube;
}DPU_RangeProcDSP_HW_Resources;

/**
 * @brief
 *  RangeProcDSP dynamic configurations
 *
 * @details
 *  The structure is used to hold the dynamic configuration needed for Range FFT
 *
 *  \ingroup DPU_RANGEPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_RangeProcDSP_DynamicConfig_t
{
    /*! @brief      Pointer to Calibrate DC Range signature configuration */
    DPU_RangeProc_CalibDcRangeSigCfg *calibDcRangeSigCfg;
}DPU_RangeProcDSP_DynamicConfig;

/**
 * @brief
 *  RangeProcDSP dynamic configurations
 *
 * @details
 *  The structure is used to hold the static configuration needed for Range FFT
 *
 *  \ingroup DPU_RANGEPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_RangeProcDSP_StaticConfig_t
{
    /*! @brief  Number of transmit antennas */
    uint8_t             numTxAntennas;

    /*! @brief  Number of virtual antennas */
    uint8_t             numVirtualAntennas;

    /*! @brief  Number of range bins */
    uint16_t            numRangeBins;

    /*! @brief  Number of chirps per frame */
    uint16_t            numChirpsPerFrame;

    /*! @brief      Pointer to ADC buffer interface */
    DPIF_ADCBufData     ADCBufData;

    /*! @brief      Flag to reset dcRangeSigMean buffer
                     1 - to reset the dcRangeSigMean buffer and counter
                     0 - do not reset
     */
    uint8_t             resetDcRangeSigMeanBuffer;
}DPU_RangeProcDSP_StaticConfig;

/**
 * @brief
 *  rangeProcDSP configuration
 *
 * @details
 *  The structure is used to hold the configuration needed for Range FFT
 *
 *  \ingroup EXTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_RangeProcDSP_Config_t
{
    /*! @brief     Hardware resources required by the DPU */
    DPU_RangeProcDSP_HW_Resources   hwRes;

    /*! @brief      Static configuration */
    DPU_RangeProcDSP_StaticConfig   staticCfg;

    /*! @brief      Dynamic configuration */
    DPU_RangeProcDSP_DynamicConfig  dynCfg;
}DPU_RangeProcDSP_Config;

/**
 * @brief
 *  rangeProcDSP output parameters populated during rangeProc Processing time
 *
 * @details
 *  The structure is used to hold the output parameters for rangeProc
 *
 *  \ingroup DPU_RANGEPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_RangeProcDSP_OutParams_t
{
    /*! @brief      End of Chirp indication for rangeProcDSP */
    bool                endOfChirp;

    /*! @brief     rangeProc stats */
    DPU_RangeProc_stats  stats;
}DPU_RangeProcDSP_OutParams;

/**
 * @brief
 *  rangeProcDSP control command
 *
 * @details
 *  The enum defines the rangeProc supported run time command
 *
 *  \ingroup DPU_RANGEPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef enum DPU_RangeProcDSP_Cmd_e
{
    /*! @brief     Command to update configuration */
    DPU_RangeProcDSP_Cmd_dcRangeCfg
}DPU_RangeProcDSP_Cmd;

/**
 * @brief
 *  rangeProcDSP DPU Handle
 *
 *  \ingroup DPU_RANGEPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef void* DPU_RangeProcDSP_Handle ;

DPU_RangeProcDSP_Handle DPU_RangeProcDSP_init(int32_t       *errCode);

extern int32_t DPU_RangeProcDSP_config
(
    DPU_RangeProcDSP_Handle     handle,
    DPU_RangeProcDSP_Config*    pConfig
);

extern int32_t DPU_RangeProcDSP_process
(
    DPU_RangeProcDSP_Handle        handle,
    DPU_RangeProcDSP_OutParams     *outParams
);

extern int32_t DPU_RangeProcDSP_control
(
    DPU_RangeProcDSP_Handle handle,
    DPU_RangeProcDSP_Cmd    cmd,
    void*                   arg,
    uint32_t                argSize
);

extern int32_t DPU_RangeProcDSP_deinit(DPU_RangeProcDSP_Handle handle);

#ifdef __cplusplus
}
#endif

#endif

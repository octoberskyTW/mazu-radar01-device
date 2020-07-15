/**
 *   @file  cfarcaproccommon.h
 *
 *   @brief
 *      Implements Common definition across cfarcaProc DPU.
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

/** @mainpage CFARCA DPU
 * [TOC]
 *  @section cfarca_intro_section CFAR-CA DPU
 *
 * This DPU implements CFAR object detection from the Range/Doppler detection
 * matrix.
 *
 *
 *  CFARCA DPU includes two DPU implementations:
 *
 *   DPU         |  runs on cores
 *  :------------|:----------------
 *  cfarcaProcHWA|  R4F or DSP
 *  cfarcaProcDSP|     DSP
 *
 *  @section cfarca_hwa HWA-CFARCA DPU
 *
 * @subsection cfarcahwa_intro_section Introduction
 * This DPU implements CFAR object detection from the Range/Doppler detection
 * matrix using hardware accelerator (HWA).
 * CFAR detection is performed in both Range and Doppler domains. The DPU exports
 * the list of objects that are detected both in range and in Doppler domains.
 * A high level data flow is illustrated in figure below.
 *
 * @image html hwa_cfar_top_level.png "HWA-CFAR high level data flow"
 *
 * The following figure depicts the DPU implementation:
 *
 * @image html hwa_cfar.png "HWA-CFAR implementation"
 *
 * The input is detection matrix
 * as per the format @ref DPIF_DetMatrix @ref DPIF_DETMATRIX_FORMAT_1, the elements 
 * of this matrix are sum  of log2 magnitudes across received antennas of the 2D FFT.
 * This matrix must be no bigger than what can fit in M0+M1 memory (error checking
 * is done during @ref DPU_CFARCAProcHWA_config and violation will generate error code
 * @ref DPU_CFARCAPROCHWA_ENOMEM__DET_MATRIX_EXCEEDS_HWA_INP_MEM).
 *
 * The detection process is initiated by triggering input EDMA (@ref DPU_CFARCAProcHWA_HW_Resources::edmaHwaIn)
 * that copies detection matrix(@ref DPIF_DetMatrix)
 * from L3 memory to internal HWA memory (@ref DPU_CFARCAProcHWA_HW_Resources::hwaMemInp, typically
 * (M0+M1)). Signature EDMA (@ref DPU_CFARCAProcHWA_HW_Resources::edmaHwaInSignature)
 * then triggers HWA CFAR which is executed
 * with one param set that performs CFAR in Doppler domain.
 * The results are stored in HWA memory
 * (@ref DPU_CFARCAProcHWA_HW_Resources::hwaMemOutDoppler, typically M2) as a list with each element represented
 * as @ref DPU_CFARCAProcHWA_CfarDetOutput_t.
 * Upon completion, the CPU triggers the HWA CFAR in range domain with the results
 * directed to HWA memory (@ref DPU_CFARCAProcHWA_HW_Resources::hwaMemOutRange, typically in M3)
 * and then in parallel calculates
 * (@ref CFARHWA_convHwaCfarDetListToDetMask) the bit mask of detected points
 * and puts it in to the @ref DPU_CFARCAProcHWA_HW_Resources::cfarDopplerDetOutBitMask
 * that is allocated by the application (typically in core local memory).
 * The bit position in the array corresponding to element x[rangeIdx][dopplerIdx]
 * is calculated as shown in the figure above (expressions "word = , bit = ").
 *
 * After the HWA CFAR detection is completed, the CPU (@ref CFARHWA_cfarRange_AND_cfarDoppler)
 * takes detected objects from the range CFAR detection list (M3 memory) and
 * populates in the output list (@ref DPIF_CFARDetList_t)
 * if the following conditions are satisfied:
 * 1. The object is also detected in the Doppler domain (i.e. if the corresponding
 *    bit is set in the Doppler detection bit mask).
 * 2. The range and doppler indices are within those determined from the
 *    FOV configuration given by the application when issuing any of the following:
 *    - @ref DPU_CFARCAProcHWA_config (@ref DPU_CFARCAProcHWA_DynamicConfig::fovRange, @ref DPU_CFARCAProcHWA_DynamicConfig::fovDoppler)
 *    - @ref DPU_CFARCAProcHWA_control (@ref DPU_CFARCAProcHWA_Cmd_FovRangeCfg, @ref DPU_CFARCAProcHWA_Cmd_FovDopplerCfg).
 *
 * In this output list, side information of noise (from the range CFAR HWA processing)
 * and SNR is also populated for each of the generated points in this list. The
 * SNR is calculated using the noise (from range CFAR HWA) and the detection matrix
 * value corresponding to the detected range,doppler position.
 *
 * The HWA CFAR function can also perform peak grouping functionality. It (enable/disable)
 * is configured from the application when issuing @ref DPU_CFARCAProcHWA_config (@ref DPU_CFARCAProcHWA_DynamicConfig::cfarCfgRange,
 * @ref DPU_CFARCAProcHWA_DynamicConfig::cfarCfgDoppler) or when issuing @ref DPU_CFARCAProcHWA_control (@ref DPU_CFARCAProcHWA_Cmd_CfarRangeCfg,
 * @ref DPU_CFARCAProcHWA_Cmd_CfarDopplerCfg). These configurations also allow CFAR parameters
 * like threshold scale and window/guard lengths to be set. The CFAR detection processing in
 * the Doppler domain can be bypassed by setting doppler direction's detection threshold to zero.
 * In this case the peak grouping in the Doppler domain is unavailable.
 * @warning
 *   For xWR18xx: The HWA's peak grouping functionality declares peak if the cell
 *   under test is strictly greater than its most immediate neighboring cells.
 *   This implies that if neighbors were exactly identical, then a CFAR detected peak group
 *   corresponding to an object can result in no single peak being declared belonging
 *   to this group i.e the object that otherwise was declared detected by CFAR would
 *   be undetected due to peak grouping. The chance of neighbors being identical
 *   depends on how the input to the CFAR algorithm is generated and also the
 *   type of CFAR algorithm. For example, when the input to CFAR is
 *   coming from sum across virtual antennas of the log
 *   magnitude of 2D FFT, there is a chance of  having identical
 *   neighbor peaks because of the type of FFT windows used in range or
 *   doppler FFTs (wider main lobes may increase the chance),
 *   the nature of log function (more flattening at higher values),
 *   the approximations in the implementation of log and magnitude calculations,
 *   the degree of interpolation of FFTs (more interpolation may increase chance), etc.
 *   Users are advised to disable peak grouping functionality if this inversion
 *   in detectability is not acceptable for their application.
 *
 *
 * The HWA-CFAR timing diagram is illustrated in figure below.
 *
 * @image html hwa_cfar_timing.png "HWA-CFAR timing"
 *
 * @subsection cfarcahwa_apis CFARCA HWA APIs
 *
 * - @ref DPU_CFARCAProcHWA_init DPU initialization initialization function.
 * - @ref DPU_CFARCAProcHWA_config DPU configuration function. The configuration can only be done after
 *   the DPU has been initialized using @ref DPU_CFARCAProcHWA_init. *
 * - @ref DPU_CFARCAProcHWA_process DPU processing function. This will execute the CFAR detection
 *   algorithm using HWA. This processing can only be done after the DPU has been configured through.
 * - @ref DPU_CFARCAProcHWA_config. If the parameters used by this DPU do not
 *   change from one frame to the next, @ref DPU_CFARCAProcHWA_config can be called only once for the first
 *   frame and for every frame @ref DPU_CFARCAProcHWA_process can be executed without the need of reconfiguring the DPU.
 * - @ref DPU_CFARCAProcHWA_control DPU control function. It processes the following messages received from DPC:
 *      - @ref DPU_CFARCAProcHWA_Cmd_CfarRangeCfg,
 *      - @ref DPU_CFARCAProcHWA_Cmd_CfarDopplerCfg,
 *      - @ref DPU_CFARCAProcHWA_Cmd_FovRangeCfg,
 *      - @ref DPU_CFARCAProcHWA_Cmd_FovDopplerCfg
 *
 *  Full API details can be seen at @ref CFARCA_PROC_DPU_EXTERNAL
 *
 *  @section cfarca_dsp DSP-CFARCA DPU
 *
 * @subsection cfarcadsp_intro_section Introduction
 * This DPU implements CFAR object detection from the Range/Doppler detection
 * matrix using CFAR and Peak grouping algorithms running on DSP.
 * CFAR detection is performed in both Range and Doppler domains. The DPU exports
 * the list of objects that are detected both in range and in Doppler domains.
 * A high level data flow is illustrated in figure below.
 *
 * @image html dsp_cfar_top_level.png "DSP-CFAR high level data flow"
 * 
 * The size of detection objects list is defined by DPU_CFARCAProcDSP_HW_Resources_t::cfarRngDopSnrListSize.
 * When there is only doppler domain or range domain processing, it is possible that the detected objects are truncated due to this size limitation.
 * When both doppler domain and range domain processing are enabled, the ouput from doppler domain will be put in doppler detection bit mask array only,
 * hence it is not limited by the size. After range domain processing, the detection list is then populated. If there are too many detected objects, 
 * the list will be truncated to DPU_CFARCAProcDSP_HW_Resources_t::cfarRngDopSnrListSize.
 *
 * The following figure depicts the DPU implementation:
 *
 * @image html dsp_cfar.png "DSP-CFAR implementation"
 *
 * The input is range-doppler detection matrix
 * as per the format @ref DPIF_DetMatrix @ref DPIF_DETMATRIX_FORMAT_1, the elements
 * of this matrix are sum  of log2 magnitudes across received antennas of the 2D FFT.
 * 
 * The doppler domain detection process is initiated by triggering input EDMA (@ref DPU_CFARCAProcDSP_HW_Resources::edmaInPing and edmaInPong)
 * that copies detection matrix(@ref DPIF_DetMatrix) from L3 memory to local buffer (@ref DPU_CFARCAProcDSP_HW_Resources::localDetMatrixBuffer)
 * one range bin at a time in ping/pong manner.
 * It then executes CFARCA algorithm and generates cfarDopplerDetOutBitMask based on detection results.
 *
 * Upon completion of all range bins and whole cfarDopplerDetOutBitMask table is populated, the CPU starts CFAR in range domain for those doppler lines
 * that have detected objects as indicated by cfarDopplerDetOutBitMask.
 *
 * After the DSP CFAR detection is completed, if peak grouping is enabled, peak
 * grouping is performed and final detected objects list(@ref DPIF_CFARDetList_t) is populated.
 * @note Unlike the HWA CFAR case, the DSP implementation declares peak if peak under
 * evaluation is greater than *or equal to* the neighbors (CFAR qualified or not) so
 * the problem described earlier in HWA CFAR's peak grouping does not exist for this
 * DSP implementation.
 *
 *
 * Object is presented in the final list if the following conditions are satisfied:
 *  1. The object is detected in both Doppler and Range domain
 *  2. The range and doppler indices are within those determined from the
 *    FOV configuration given by the application when issuing any of the following:
 *    - @ref DPU_CFARCAProcDSP_config (@ref DPU_CFARCAProcDSP_DynamicConfig::fovRange, @ref DPU_CFARCAProcDSP_DynamicConfig::fovDoppler)
 *    - @ref DPU_CFARCAProcDSP_control (@ref DPU_CFARCAProcDSP_Cmd_FovRangeCfg, @ref DPU_CFARCAProcDSP_Cmd_FovDopplerCfg).
 *
 * In this output list, side information of noise and SNR is also populated for each of the generated points. The
 * SNR is calculated using the noise and the detection matrix value corresponding to the detected range,doppler position.
 *
 * If both CFAR doopler and range domain processing are enabled, then noise is taken from range domain processing.
 * If only one processing domain is enabled, the noise is from the enabed processing domain.
 * 
 * The CFAR processing and peak grouping can be enabled from dynamic configurations, such as:
 *  - @ref DPU_CFARCAProcDSP_DynamicConfig::cfarCfgRange,
 *  - @ref DPU_CFARCAProcDSP_DynamicConfig::cfarCfgDoppler.
 *
 * This can be done through:
 *  - @ref DPU_CFARCAProcDSP_config
 *  - @ref DPU_CFARCAProcDSP_control(@ref DPU_CFARCAProcDSP_Cmd_CfarRangeCfg, @ref DPU_CFARCAProcDSP_Cmd_CfarDopplerCfg).
 *
 * Additional parameters from the configuration also allow CFAR parameters
 * like threshold scale and window/guard lengths to be set. The CFAR detection processing in
 * the Doppler domain can be bypassed by setting doppler direction's detection threshold to zero.
 *
 * @subsection cfarcadsp_apis CFARCA DSP APIs
 *
 * - @ref DPU_CFARCAProcDSP_init DPU initialization function.
 * - @ref DPU_CFARCAProcDSP_config DPU configuration function. The configuration can only be done after
 * the DPU has been initialized using @ref DPU_CFARCAProcDSP_init.
 *
 * - @ref DPU_CFARCAProcDSP_process DPU processing function. This will execute the CFAR detection
 * algorithm using DSP. This processing can only be done after the DPU has been configured through
 * @ref DPU_CFARCAProcDSP_config. If the parameters used by this DPU do not
 * change from one frame to the next, @ref DPU_CFARCAProcDSP_config can be called only once for the first
 * frame and for every frame @ref DPU_CFARCAProcDSP_process can be executed without the need of reconfiguring the DPU.
 *
 * - @ref DPU_CFARCAProcDSP_control DPU control function. It processes the following messages received from DPC:
 *      - @ref DPU_CFARCAProcDSP_Cmd_CfarRangeCfg,
 *      - @ref DPU_CFARCAProcDSP_Cmd_CfarDopplerCfg,
 *      - @ref DPU_CFARCAProcDSP_Cmd_FovRangeCfg,
 *      - @ref DPU_CFARCAProcDSP_Cmd_FovDopplerCfg
 *
 *  Full API details can be seen at @ref CFARCA_PROC_DPU_EXTERNAL */


/** @defgroup CFARCA_PROC_DPU_EXTERNAL       cfarcaProc DPU External
 */

/**
@defgroup DPU_CFARCAPROC_EXTERNAL_FUNCTION            cfarcaProc DPU External Functions
@ingroup CFARCA_PROC_DPU_EXTERNAL
@brief
*   The section has a list of all the exported API which the applications need to
*   invoke in order to use the cfarcaProc DPU
*/
/**
@defgroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE      cfarcaProc DPU External Data Structures
@ingroup CFARCA_PROC_DPU_EXTERNAL
@brief
*   The section has a list of all the data structures which are exposed to the application
*/
/**
@defgroup DPU_CFARCAPROC_EXTERNAL_DEFINITIONS      cfarcaProc DPU External Definitions
@ingroup CFARCA_PROC_DPU_EXTERNAL
@brief
*   The section has a list of all the data structures which are exposed to the application
*/
/**
@defgroup DPU_CFARCAPROC_ERROR_CODE                   cfarcaProc DPU Error Codes
@ingroup CFARCA_PROC_DPU_EXTERNAL
@brief
*   The section has a list of all the error codes which are generated by the sampleProc DPU
*/

/**************************************************************************
 *************************** Include Files ********************************
 **************************************************************************/
#ifndef CFARCAROC_COMMON_H
#define CFARCAROC_COMMON_H

/* Standard Include Files. */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


#ifdef __cplusplus
extern "C" {
#endif


/*! @brief   CFAR detection in range domain */
#define DPU_CFAR_RANGE_DOMAIN   0

/*! * @brief   CFAR detection in Doppler domain */
#define DPU_CFAR_DOPPLER_DOMAIN 1

/*! @brief Peak grouping scheme of CFAR detected objects based on peaks of neighboring cells taken from detection matrix */
#define DPU_CFAR_PEAK_GROUPING_DET_MATRIX_BASED 1

/*! @brief Peak grouping scheme of CFAR detected objects based only on peaks of neighboring cells that are already detected by CFAR */
#define DPU_CFAR_PEAK_GROUPING_CFAR_PEAK_BASED  2

/*! @brief  Convert peak/noise value to log10 value in 0.1dB
       Since, val = log2(|.|)* 2^Qformat = log10(|.|) / log10(2) * 2^Qformat
       Equation: output = 1/0.1 * 10log10(|.|^2) = 10 * [ val * 20log10(2) / 2^Qformat ] = val * 6.0 / 2^Qformat * 10
 */
#define CFARCADSP_CONV_PEAK_TO_LOG(val, QFormat)        (val * 6.0 /(float)(1<<QFormat) * 10.0)

/**
 * @brief
 *  CFAR Configuration
 *
 * @details
 *  The structure contains the cfar configuration used in data path
 */
typedef struct DPU_CFARCAProc_CfarCfg_t
{
    /*! @brief    CFAR threshold scale */
    uint16_t       thresholdScale;

    /*! @brief    CFAR averagining mode 0-CFAR_CA, 1-CFAR_CAGO, 2-CFAR_CASO */
    uint8_t        averageMode;

    /*! @brief    CFAR noise averaging one sided window length */
    uint8_t        winLen;

    /*! @brief    CFAR one sided guard length*/
    uint8_t        guardLen;

    /*! @brief    CFAR cumulative noise sum divisor
                  CFAR_CA:
                        noiseDivShift should account for both left and right noise window
                        ex: noiseDivShift = ceil(log2(2 * winLen))
                  CFAR_CAGO/_CASO:
                        noiseDivShift should account for only one sided noise window
                        ex: noiseDivShift = ceil(log2(winLen))
     */
    uint8_t        noiseDivShift;

    /*! @brief    CFAR 0-cyclic mode disabled, 1-cyclic mode enabled */
    uint8_t        cyclicMode;

    /*! @brief    Peak grouping scheme 1-based on neighboring peaks from detection matrix
     *                                 2-based on on neighboring CFAR detected peaks.
     *            Scheme 2 is not supported on the HWA version (cfarcaprochwa.h) */
    uint8_t        peakGroupingScheme;

    /*! @brief     Peak grouping, 0- disabled, 1-enabled */
    uint8_t        peakGroupingEn;

} DPU_CFARCAProc_CfarCfg;

/**
 * @brief
 *  Data processing Unit statistics
 *
 * @details
 *  The structure is used to hold the statistics of the DPU 
 *
 *  \ingroup INTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_CFARCAProc_Stats_t
{
    /*! @brief total number of calls of DPU processing */
    uint32_t            numProcess;

    /*! @brief total processing time during all chirps in a frame excluding EDMA waiting time*/
    uint32_t            processingTime;

    /*! @brief total wait time for EDMA data transfer during all chirps in a frame*/
    uint32_t            waitTime;
}DPU_CFARCAProc_Stats;


/*!
 *  @brief    Field of view indices
 *
 *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef struct DPU_CFARCAProc_FovCfg_t
{
    /*! @brief Minimum value in meters for range, or meters/sec for doppler */
    float min;

    /*! @brief Maximum value in meters for range, or meters/sec for doppler */
    float max;
} DPU_CFARCAProc_FovCfg;


#ifdef __cplusplus
}
#endif

#endif 

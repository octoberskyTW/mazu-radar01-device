/**
 *   @file  dopplerprocdsp.h
 *
 *   @brief
 *      Implements Data path Doppler processing functionality.
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
#ifndef DOPPLERPROC_DSP_H
#define DOPPLERPROC_DSP_H

/* Standard Include Files. */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/* mmWave SDK Driver/Common Include Files */
//#include <ti/drivers/hwa/hwa.h>

/* DPIF Components Include Files */
#include <ti/datapath/dpif/dpif_detmatrix.h>
#include <ti/datapath/dpif/dpif_radarcube.h>

/* mmWave SDK Data Path Include Files */
#include <ti/datapath/dpif/dp_error.h>
#include <ti/datapath/dpc/dpu/dopplerproc/dopplerproccommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup DPU_DOPPLERPROC_ERROR_CODE
 *  Base error code for the dopplerProc DPU is defined in the
 *  \include ti/datapath/dpif/dp_error.h
 @{ */

/**
 * @brief   Error Code: Invalid argument
 */
#define DPU_DOPPLERPROCDSP_EINVAL                  (DP_ERRNO_DOPPLER_PROC_BASE-1)

/**
 * @brief   Error Code: Out of memory
 */
#define DPU_DOPPLERPROCDSP_ENOMEM                  (DP_ERRNO_DOPPLER_PROC_BASE-2)

/**
 * @brief   Error Code: DPU is in progress
 */
#define DPU_DOPPLERPROCDSP_EINPROGRESS             (DP_ERRNO_DOPPLER_PROC_BASE-3)

/**
 * @brief   Error Code: Semaphore creation failed
 */
#define DPU_DOPPLERPROCDSP_ESEMA                   (DP_ERRNO_DOPPLER_PROC_BASE-4)

/**
 * @brief   Error Code: Bad semaphore status 
 */
#define DPU_DOPPLERPROCDSP_ESEMASTATUS             (DP_ERRNO_DOPPLER_PROC_BASE-5)

/**
 * @brief   Error Code: Unsupported radar cube format 
 */
#define DPU_DOPPLERPROCDSP_ECUBEFORMAT             (DP_ERRNO_DOPPLER_PROC_BASE-6)

/**
 * @brief   Error Code: Unsupported detection matrix format 
 */
#define DPU_DOPPLERPROCDSP_EDETMFORMAT             (DP_ERRNO_DOPPLER_PROC_BASE-7)

/**
 * @brief   Error Code: Insufficient detection matrix size
 */
#define DPU_DOPPLERPROCDSP_EDETMSIZE               (DP_ERRNO_DOPPLER_PROC_BASE-8)

/**
 * @brief   Error Code: Wrong window size
 */
#define DPU_DOPPLERPROCDSP_EWINDSIZE               (DP_ERRNO_DOPPLER_PROC_BASE-9)

/**
 * @brief   Error Code: Bad alignment for input buffer 
 */
#define DPU_DOPPLERPROCDSP_EBUFALIGNMENT           (DP_ERRNO_DOPPLER_PROC_BASE-10)

/**
 * @brief   Error Code: Number of Doppler chirps is not a multiple of 4
 */
#define DPU_DOPPLERPROCDSP_ENUMDOPCHIRPS           (DP_ERRNO_DOPPLER_PROC_BASE-11)

/**
 * @brief   Error Code: Number of Doppler bins is less than 16
 */
#define DPU_DOPPLERPROCDSP_ENUMDOPBINS             (DP_ERRNO_DOPPLER_PROC_BASE-12)

/**
 * @brief   Error Code: Invalid control command
 */
#define DPU_DOPPLERPROCDSP_ECMD                    (DP_ERRNO_DOPPLER_PROC_BASE-13)

/**
 * @brief   Error Code: One of the provided scratch buffers has insufficient size
 */
#define DPU_DOPPLERPROCDSP_ESCRATCHSIZE            (DP_ERRNO_DOPPLER_PROC_BASE-14)

/**
 * @brief   Error Code: DPU configuration is invalid. It exceeds the maximum EDMA jump size of (32K - 1)
 */
#define DPU_DOPPLERPROCDSP_EEXCEEDMAXEDMA          (DP_ERRNO_DOPPLER_PROC_BASE-15)

/**
 * @brief   Error Code: Bad BPM configuration
 */
#define DPU_DOPPLERPROCDSP_EBPMCFG                 (DP_ERRNO_DOPPLER_PROC_BASE-16)

/**
@}
*/

/*! Alignment for all buffers required by DPU */
#define DPU_DOPPLERPROCDSP_BUFFER_BYTE_ALIGNMENT 8U

/*!
 *  @brief   Handle for Doppler Processing DPU.
 */
typedef void*  DPU_DopplerProcDSP_Handle;

/**
 * @brief
 *  dopplerProc DPU EDMA configuration parameters
 *
 * @details
 *  The structure is used to hold the EDMA configuration parameters
 *  for the Doppler Processing DPU
 *
 *  \ingroup DPU_DOPPLERPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_DopplerProcDSP_EdmaCfg_t
{
    /*! @brief  EDMA driver handle. */
    EDMA_Handle edmaHandle;
    
    /*! @brief  EDMA configuration for Input data (Radar cube -> internal memory). */
    DPU_DopplerProc_Edma edmaIn;
    
    /*! @brief  EDMA configuration for Output data (internal memory -> detection matrix). */
    DPEDMA_ChanCfg  edmaOut;
    
}DPU_DopplerProcDSP_EdmaCfg;

/**
 * @brief
 *  Doppler DPU HW configuration parameters
 *
 * @details
 *  The structure is used to hold the  HW configuration parameters
 *  for the Doppler DPU
 *
 *  \ingroup DPU_DOPPLERPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_DopplerProcDSP_HW_Resources_t
{
    /*! @brief  EDMA configuration */
    DPU_DopplerProcDSP_EdmaCfg edmaCfg;
   
    /*! @brief  Radar Cube */
    DPIF_RadarCube radarCube;
    
    /*! @brief  Detection matrix */
    DPIF_DetMatrix detMatrix;
            
    /*! @brief      Scratch buffer pointer for ping pong input from radar cube. \n
                    Size: 2 * sizeof(cmplx16ImRe_t) * numDopplerChirps \n
                    Byte alignment Requirement = @ref DPU_DOPPLERPROCDSP_BUFFER_BYTE_ALIGNMENT
     */
    cmplx16ImRe_t   *pingPongBuf;

    /*! @brief      Size of the Ping pong buffer */
    uint32_t        pingPongSize;
    
    /*! @brief      Windowing output and Log2Abs output buffers are overlayed in memory.
                    This is the scratch buffer pointer for windowing output and Log2Abs output. \n
                    Size: sizeof(cmplx32ReIm_t) * numDopplerBins = \n
                          MAX[(sizeof(cmplx32ReIm_t) * numDopplerBins), (sizeof(uint16_t) * numDopplerBins)]\n
                    Byte alignment Requirement = @ref DPU_DOPPLERPROCDSP_BUFFER_BYTE_ALIGNMENT
     */
    void            *windowingLog2AbsBuf;

    /*! @brief      Size of the windowingLog2Abs buffer */
    uint32_t        windowingLog2AbsSize;

    /*! @brief      Scratch buffer pointer for Doppler FFT output. \n
                    Size: \n
                         numDopplerBins * sizeof(cmplx32ReIm_t), if BPM is not enabled\n
                         numDopplerBins * sizeof(cmplx32ReIm_t) * numTxAntennas, if BPM is enabled\n
                    Byte alignment Requirement = @ref DPU_DOPPLERPROCDSP_BUFFER_BYTE_ALIGNMENT
     */
    cmplx32ReIm_t   *fftOutBuf;
    
    /*! @brief      Size of the FFT output buffer */
    uint32_t        fftOutSize;

    /*! @brief      Scratch buffer pointer for Accumulated sum of log2 absolute over the antennas. \n
                    Size: numDopplerBins * sizeof(uint16_t)\n
                    Byte alignment Requirement = @ref DPU_DOPPLERPROCDSP_BUFFER_BYTE_ALIGNMENT
     */
    uint16_t        *sumAbsBuf;
    
    /*! @brief      Size of the Accumulated sum of log2 buffer */
    uint32_t        sumAbsSize;


    /*! @brief      Scratch buffer pointer single point DFT coefficients. Data in this buffer needs to be preserved
                    (or recomputed) between frames. This buffer is populated by #DPU_DopplerProcDSP_config API. \n
                    Size: numDopplerBins * sizeof(cmplx16ImRe_t)\n
                    Byte alignment Requirement = @ref DPU_DOPPLERPROCDSP_BUFFER_BYTE_ALIGNMENT
     */
    cmplx16ImRe_t   *dftSinCosTable;
    
    /*! @brief      Size of the buffer for DFT Sin/Cos table */
    uint32_t        dftSinCosSize;
    
    /*! @brief      Pointer for twiddle table for Doppler FFT. Data in this buffer needs to be preserved
                    (or recomputed) between frames. This buffer is populated by #DPU_DopplerProcDSP_config API.   \n
                    Size: sizeof(cmplx32ReIm_t) * numDopplerBins\n
                    Byte alignment Requirement = @ref DPU_DOPPLERPROCDSP_BUFFER_BYTE_ALIGNMENT
     */
    cmplx32ReIm_t   *twiddle32x32;

    /*! @brief      Size of the buffer for twiddle table */
    uint32_t        twiddleSize;
  
    /*! @brief      Pointer for buffer with window coefficients. Data in this buffer needs to be preserved
                    (or recomputed) between frames. Window must be symmetric, therefore only numDopplerChirps / 2
                    coefficients are needed to determine the window. \n
                    Size: sizeof(int32_t) * numDopplerChirps / 2\n
                    Byte alignment Requirement = @ref DPU_DOPPLERPROCDSP_BUFFER_BYTE_ALIGNMENT
     */
    int32_t     *windowCoeff;

    /*!  @brief Doppler FFT window size in bytes.*/
    uint32_t    windowSize;

}DPU_DopplerProcDSP_HW_Resources;

/**
 * @brief
 *  Doppler DPU static configuration parameters
 *
 * @details
 *  The structure is used to hold the static configuration parameters
 *  \ingroup DPU_DOPPLERPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_DopplerProcDSP_StaticConfig_t
{
    /*! @brief  Number of transmit antennas */
    uint8_t     numTxAntennas;
    
    /*! @brief  Number of receive antennas */
    uint8_t     numRxAntennas;
    
    /*! @brief  Number of virtual antennas */
    uint8_t     numVirtualAntennas; 
    
    /*! @brief  Number of range bins */
    uint16_t    numRangeBins;
    
    /*! @brief  Number of Doppler chirps. Must be a multiple of 4. */
    uint16_t    numDopplerChirps;
    
    /*! @brief  Number of Doppler bins. */
    uint16_t    numDopplerBins;
    
    /*! @brief  Log2 of number of Doppler bins */
    uint8_t     log2NumDopplerBins;
        
    /*! @brief Flag that indicates if BPM is enabled. 
        BPM can only be enabled/disabled during configuration time.*/
    bool        isBpmEnabled;
    
}DPU_DopplerProcDSP_StaticConfig;

/**
 * @brief
 *  Static clutter removal configuration
 *
 * @details
 *  The structure contains the configuration for static clutter removal.
 *
 *  \ingroup DPU_DOPPLERPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_DopplerProc_StaticClutterRemovalCfg_t
{
    /*! @brief Flag that indicates if static clutter removal is enabled.*/
    bool  isEnabled;
}DPU_DopplerProc_StaticClutterRemovalCfg;

/**
 * @brief
 *  dopplerProc dynamic configuration
 *
 * @details
 *  The structure is used to hold the dynamic configuration for the DPU
 *
 *  \ingroup DPU_DOPPLERPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_DopplerProcDSP_DynamicConfig_t
{   
    /*! @brief Static clutter removal configuration.*/
    DPU_DopplerProc_StaticClutterRemovalCfg  staticClutterCfg;

}DPU_DopplerProcDSP_DynamicConfig;

/**
 * @brief
 *  dopplerProc DPU configuration parameters
 *
 * @details
 *  The structure is used to hold the configuration parameters
 *  for the Doppler Processing removal DPU
 *
 *  \ingroup DPU_DOPPLERPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_DopplerProcDSP_Config_t
{
    /*! @brief HW resources. */
    DPU_DopplerProcDSP_HW_Resources  hwRes;
    
    /*! @brief Static configuration. */
    DPU_DopplerProcDSP_StaticConfig  staticCfg;

    /*! @brief Dynamic configuration */
    DPU_DopplerProcDSP_DynamicConfig dynCfg;    
}DPU_DopplerProcDSP_Config;

/**
 * @brief
 *  DPU processing output parameters
 *
 * @details
 *  The structure is used to hold the output parameters DPU processing
 *
 *  \ingroup DPU_DOPPLERPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_DopplerProcDSP_OutParams_t
{
    /*! @brief DPU statistics */
    DPU_DopplerProc_Stats  stats;
}DPU_DopplerProcDSP_OutParams;

/**
 * @brief
 *  Doppler DPU control commands
 *
 * @details
 *  The enum defines the Doppler DPU supported run time command
 *
 *  \ingroup DPU_DOPPLERPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef enum DPU_DopplerProcDSP_Cmd_e
{
    /*! @brief Command to update static clutter removal configuration.
        The static clutter configuration @ref DPU_DopplerProc_StaticClutterRemovalCfg_t should
        be passed as argument for this command. */
    DPU_DopplerProcDSP_Cmd_staticClutterCfg
}DPU_DopplerProcDSP_Cmd;

DPU_DopplerProcDSP_Handle DPU_DopplerProcDSP_init(int32_t* errCode);
int32_t DPU_DopplerProcDSP_process(DPU_DopplerProcDSP_Handle handle, DPU_DopplerProcDSP_OutParams *outParams);
int32_t DPU_DopplerProcDSP_deinit(DPU_DopplerProcDSP_Handle handle);
int32_t DPU_DopplerProcDSP_config(DPU_DopplerProcDSP_Handle handle, DPU_DopplerProcDSP_Config *cfg);
int32_t DPU_DopplerProcDSP_control(DPU_DopplerProcDSP_Handle handle, DPU_DopplerProcDSP_Cmd cmd,
                                   void* arg, uint32_t argSize);


#ifdef __cplusplus
}
#endif

#endif

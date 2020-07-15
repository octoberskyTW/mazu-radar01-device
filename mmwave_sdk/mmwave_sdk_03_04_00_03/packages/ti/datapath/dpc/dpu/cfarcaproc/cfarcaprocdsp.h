/**
 *   @file  cfarcaprocdsp.h
 *
 *   @brief
 *      Implement CFARCA DPU using DSP
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
#ifndef CFARCA_PROC_DSP_H
#define CFARCA_PROC_DSP_H

/* Standard Include Files. */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/* mmWave SDK Driver/Common Include Files */
#include <ti/drivers/edma/edma.h>

#include <ti/drivers/osal/SemaphoreP.h>

/* Datapath files */
#include <ti/datapath/dpif/dpif_detmatrix.h>
#include <ti/datapath/dpif/dpif_pointcloud.h>
#include <ti/datapath/dpedma/dpedma.h>
#include <ti/datapath/dpif/dp_error.h>
#include <ti/datapath/dpc/dpu/cfarcaproc/cfarcaproccommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup DPU_CFARCAPROC_EXTERNAL_DEFINITIONS
 *
 @{ */

/*! @brief Alignment for memory allocation purpose of detection matrix.
 *         There is CPU access of detection matrix in the implementation.
 */
#define DPU_CFARCAPROCDSP_DET_MATRIX_BYTE_ALIGNMENT (sizeof(uint16_t))

/*! @brief Alignment for memory allocation purpose. There is CPU access of cfarRngDopSnrList
 *         in the implementation.
 */
#define DPU_CFARCAPROCDSP_CFAR_DET_LIST_BYTE_ALIGNMENT    DPIF_CFAR_DET_LIST_CPU_BYTE_ALIGNMENT

/*! @brief Alignment for memory allocation purpose. There is CPU access of localDetMatrixBuffer
 *         in the implementation.
 */
#define DPU_CFARCAPROCDSP_DET_MATRIX_LOCAL_BYTE_ALIGNMENT     DPIF_CFAR_DET_LIST_CPU_BYTE_ALIGNMENT

/*! @brief Alignment for memory allocation purpose. There is CPU access of cfarDetOutBuffer
 *         in the implementation.
 */
#define DPU_CFARCAPROCDSP_CFAR_DETOUT_BYTE_ALIGNMENT    (sizeof(uint16_t))

/*! @brief Alignment for memory allocation purpose. There is CPU access of cfarPeakGroupingBuffer
 *         in the implementation.
 */
#define DPU_CFARCAPROCDSP_SCRACHBUF_BYTE_ALIGNMENT    (sizeof(uint16_t))

/*! @brief Alignment for memory allocation purpose. There is CPU access of this buffer
 *         in the implementation.
 */
#define DPU_CFARCAPROCDSP_DOPPLER_DET_OUT_BIT_MASK_BYTE_ALIGNMENT    (sizeof(uint32_t))

/**
@}
*/

/** @addtogroup DPU_CFARCAPROC_ERROR_CODE
 *  Base error code for the cfarcaProc DPU is defined in the
 *  \include ti/datapath/dpif/dp_error.h
 @{ */

/**
 * @brief   Error Code: Invalid argument
 */
#define DPU_CFARCAPROCDSP_EINVAL                  (DP_ERRNO_CFARCA_PROC_BASE-1)

/**
 * @brief   Error Code: Invalid detection matrix format argument
 */
#define DPU_CFARCAPROCDSP_EINVAL__DET_MATRIX_FORMAT (DP_ERRNO_CFARCA_PROC_BASE-2)

/**
 * @brief   Error Code: Invalid buffer address
 */
#define DPU_CFARCAPROCDSP_EINVAL_EBUFFER_POINTER (DP_ERRNO_CFARCA_PROC_BASE-3)

/**
 * @brief   Error Code: Invalid buffer size
 */
#define DPU_CFARCAPROCDSP_EINVAL_EBUFFER_SIZE (DP_ERRNO_CFARCA_PROC_BASE-4)

/**
 * @brief   Error Code: Out of memory when allocating using MemoryP_osal
 */
#define DPU_CFARCAPROCDSP_ENOMEM                  (DP_ERRNO_CFARCA_PROC_BASE-10)

/**
 * @brief   Error Code: Memory not aligned for @ref DPU_CFARCAProcDSP_HW_Resources::localDetMatrixBuffer
 */
#define DPU_CFARCAPROCDSP_ENOMEMALIGN_LOCAL_DETMATRIX           (DP_ERRNO_CFARCA_PROC_BASE-11)

/**
  * @brief   Error Code: Memory not aligned for detection matrix (detMatrix.data)
  */
#define DPU_CFARCAPROCDSP_ENOMEMALIGN_DET_MATRIX                  (DP_ERRNO_CFARCA_PROC_BASE-12)

/**
 * @brief   Error Code: Memory not aligned for @ref DPU_CFARCAProcDSP_HW_Resources::cfarRngDopSnrList
 */
#define DPU_CFARCAPROCDSP_ENOMEMALIGN_CFAR_DET_LIST               (DP_ERRNO_CFARCA_PROC_BASE-13)

/**
 * @brief   Error Code: Memory not aligned for @ref DPU_CFARCAProcDSP_HW_Resources::cfarDetOutBuffer
 */
#define DPU_CFARCAPROCDSP_ENOMEMALIGN_LOCAL_CFAR_DETOUT                 (DP_ERRNO_CFARCA_PROC_BASE-14)

/**
 * @brief   Error Code: Memory not aligned for @ref DPU_CFARCAProcDSP_HW_Resources::cfarScrachBuffer
 */
#define DPU_CFARCAPROCDSP_ENOMEMALIGN_SCRATCH_BUFFER           (DP_ERRNO_CFARCA_PROC_BASE-15)

/**
 * @brief   Error Code: Memory not aligned for @ref DPU_CFARCAProcDSP_HW_Resources::cfarDopplerDetOutBitMask
 */
#define DPU_CFARCAPROCDSP_ENOMEMALIGN_DOPPLER_DET_OUT_BIT_MASK   (DP_ERRNO_CFARCA_PROC_BASE-16)

/**
 * @brief   Error Code: Insufficient memory allocated to @ref DPU_CFARCAProcDSP_HW_Resources::cfarDopplerDetOutBitMask.
 */
#define DPU_CFARCAPROCDSP_ENOMEM__INSUFFICIENT_DOP_DET_OUT_BIT_MASK  (DP_ERRNO_CFARCA_PROC_BASE-17)

/**
 * @brief   Error Code: Memory not aligned for @ref DPU_CFARCAProcDSP_HW_Resources::cfarScrachBuffer
 */
#define DPU_CFARCAPROCDSP_ENOMEM__INSUFFICIENT_SCRATCH_BUFFER    (DP_ERRNO_CFARCA_PROC_BASE-18)

/**
 * @brief   Error Code: Internal error
 */
#define DPU_CFARCAPROCDSP_EINTERNAL               (DP_ERRNO_CFARCA_PROC_BASE-20)

/**
 * @brief   Error Code: Not implemented
 */
#define DPU_CFARCAPROCDSP_ENOTIMPL                (DP_ERRNO_CFARCA_PROC_BASE-30)

 /**
 @}
 */

 /**
  * @brief
  *  cfarcaProcDSP runtime control command
  *
  * @details
  *  The enum defines the cfarcaProc supported run time command
  *
  *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
  */
 typedef enum DPU_CFARCAProcDSP_Cmd_e
 {

     /*! @brief Command to update CFAR configuration in range domain */
     DPU_CFARCAProcDSP_Cmd_CfarRangeCfg,

     /*! @brief Command to update CFAR configuration in Doppler domain */
     DPU_CFARCAProcDSP_Cmd_CfarDopplerCfg,

     /*! @brief Command to update field of view in range domain, minimum and maximum range limits */
     DPU_CFARCAProcDSP_Cmd_FovRangeCfg,

     /*! @brief Command to update field of view in Doppler domain, minimum and maximum Doppler limits */
     DPU_CFARCAProcDSP_Cmd_FovDopplerCfg
}DPU_CFARCAProcDSP_Cmd;


/**
 * @brief
 *  Hardware resources used for CFARCA implemented using DSP
 *
 *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef struct DPU_CFARCAProcDSP_HW_Resources_t
{
    /*! @brief     EDMA Handle */
    EDMA_Handle         edmaHandle;

    /*! @brief     EDMA configuration for CFAR data In Ping */
    DPEDMA_ChanCfg      edmaInPing;

    /*! @brief     EDMA configuration for CFAR data In Pong */
    DPEDMA_ChanCfg      edmaInPong;

    /*! @brief      Pointer to range/Doppler log2 magnitude detection matrix. The data buffer
     *              must be aligned to @ref DPU_CFARCAPROCDSP_DET_MATRIX_BYTE_ALIGNMENT */
    DPIF_DetMatrix      detMatrix;

    /*! @brief      Pointer to CFAR output list, must be aligned to
     *              @ref DPU_CFARCAPROCDSP_CFAR_DET_LIST_BYTE_ALIGNMENT */
    DPIF_CFARDetList    *cfarRngDopSnrList;

    /*! @brief      Number of elements of type DPIF_cfarDetList of CFAR output list */
    uint32_t            cfarRngDopSnrListSize;

    /*! @brief      Scratch memory for Doppler cfar detection bit mask. Must be aligned to
     *              @ref DPU_CFARCAPROCDSP_DOPPLER_DET_OUT_BIT_MASK_BYTE_ALIGNMENT */
    uint32_t            *cfarDopplerDetOutBitMask;

    /*! @brief      Number of elements of type uint32_t of scratch memory for bit mask
     *              of Doppler cfar detections.
     *              Must be >= (numRangeBins * numDoppplerBins) / 32 */
    uint32_t            cfarDopplerDetOutBitMaskSize;

    /*! @brief      Scratch buffer for detMatrix 
     *              @ref DPU_CFARCAPROCDSP_DET_MATRIX_LOCAL_BYTE_ALIGNMENT */
    uint16_t            *localDetMatrixBuffer;

    /*! @brief      Local detection matrix buffer size, must be 
     *              Max(numDopplerBins,numRangeBins) * sizeof(uint16_t) * 2 */
    uint32_t            localDetMatrixBufferSize;

    /*! @brief      Scratch buffer for cfar detection output 
     *              @ref DPU_CFARCAPROCDSP_DET_MATRIX_LOCAL_BYTE_ALIGNMENT */
    uint16_t            *cfarDetOutBuffer;

    /*! @brief      Scratch buffer size for cfar detection output,
     *              Max(numDopplerBins,numRangeBins) * sizeof(uint16_t) */
    uint32_t            cfarDetOutBufferSize;

    /*! @brief      Scratch buffer for Peak grouping
     *              @ref DPU_CFARCAPROCDSP_SCRACHBUF_BYTE_ALIGNMENT */
    uint16_t            *cfarScrachBuffer;

    /*! @brief      Scratch buffer size for cfar peak grouping.
     *              size = 4 * @ref cfarRngDopSnrListSize * sizeof(uint16_t) */
    uint32_t            cfarScrachBufferSize;
} DPU_CFARCAProcDSP_HW_Resources;

/**
 * @brief
 *  CFARCA DSP implementation dynamic configuration
 *
 * @details
 *  The structure is used to hold the dynamic configuration used for CFARCA Algorithm using DSP
 *
 *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef struct DPU_CFARCAProcDSP_DynamicConfig_t
{
    /*! @brief      CFAR configuration in range direction */
    DPU_CFARCAProc_CfarCfg *cfarCfgRange;

    /*! @brief      CFAR configuration in Doppler direction */
    DPU_CFARCAProc_CfarCfg *cfarCfgDoppler;

    /*! @brief      Field of view configuration in range domain */
    DPU_CFARCAProc_FovCfg *fovRange;

    /*! @brief      Field of view configuration in Doppler domain */
    DPU_CFARCAProc_FovCfg *fovDoppler;
} DPU_CFARCAProcDSP_DynamicConfig;

/**
 * @brief
 *  CFARCAProcDSP static configuration
 *
 * @details
 *  The structure is used to hold the static configuration used for CFARCA DSP implementation.
 *
 *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef struct DPU_CFARCAProcDSP_StaticConfig_t
{
    /*! @brief  Log2 of number of doppler bins */
    uint8_t     log2NumDopplerBins;

    /*! @brief  Number of range bins */
    uint16_t    numRangeBins;

    /*! @brief  Number of doppler bins */
    uint16_t    numDopplerBins;

    /*! @brief  Range conversion factor for FFT range index to meters */
    float       rangeStep;

    /*! @brief  Doppler conversion factor for Doppler FFT index to m/s */
    float       dopplerStep;
} DPU_CFARCAProcDSP_StaticConfig;

/**
 * @brief
 *  CFARCAProcDSP configuration
 *
 * @details
 *  The structure is used to hold the configuration used for CFARCA using DSP
 *
 *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef struct DPU_CFARCAProcDSP_Config_t
{
    /*! @brief  Hardware resources */
    DPU_CFARCAProcDSP_HW_Resources res;

    /*! @brief  Dynamic configuration */
    DPU_CFARCAProcDSP_DynamicConfig dynCfg;

    /*! @brief  Static configuration */
    DPU_CFARCAProcDSP_StaticConfig staticCfg;
}DPU_CFARCAProcDSP_Config;

/**
 * @brief
 *  Output parameters populated during Processing time
 *
 * @details
 *  The structure is used to hold the output parameters
 *
 *
 *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef struct DPU_CFARCAProcDSP_OutParams_t
{
    /*! @brief     CFARCAProc statistics */
    DPU_CFARCAProc_Stats    stats;

    /*! @brief      Number of CFAR detected points*/
    uint32_t                numCfarDetectedPoints;
}DPU_CFARCAProcDSP_OutParams;

/**
 * @brief
 *  CFARCADSP DPU Handle
 *
 *
 *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef void* DPU_CFARCAProcDSP_Handle;

DPU_CFARCAProcDSP_Handle DPU_CFARCAProcDSP_init
(
    int32_t*            errCode
);

int32_t DPU_CFARCAProcDSP_config
(
    DPU_CFARCAProcDSP_Handle      handle,
    DPU_CFARCAProcDSP_Config      *cfarDspCfg
);

int32_t DPU_CFARCAProcDSP_process
(
    DPU_CFARCAProcDSP_Handle   handle,
    DPU_CFARCAProcDSP_OutParams  *outParams
);

int32_t DPU_CFARCAProcDSP_control
(
    DPU_CFARCAProcDSP_Handle handle,
    DPU_CFARCAProcDSP_Cmd cmd,
    void *arg,
    uint32_t argSize
);

int32_t DPU_CFARCAProcDSP_deinit
(
    DPU_CFARCAProcDSP_Handle handle
);

#ifdef __cplusplus
}
#endif

#endif

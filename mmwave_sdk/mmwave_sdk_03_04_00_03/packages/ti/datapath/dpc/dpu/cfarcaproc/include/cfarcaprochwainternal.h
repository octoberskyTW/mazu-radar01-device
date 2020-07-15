/**
 *   @file  cfarcaprochwainternal.h
 *
 *   @brief
 *      Implements internal data structure for CFAR Processing with HWA.
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

/** @defgroup CFARCA_PROC_DPU_INTERNAL       cfarcaProc DPU Internal
 */

/**
@defgroup DPU_CFARCAPROC_INTERNAL_FUNCTION            cfarcaProc DPU Internal Functions
@ingroup CFARCA_PROC_DPU_INTERNAL
@brief
*   The section has a list of all internal API which are not exposed to the external
*   applications.
*/
/**
@defgroup DPU_CFARCAPROC_INTERNAL_DATA_STRUCTURE      cfarcaProc DPU Internal Data Structures
@ingroup CFARCA_PROC_DPU_INTERNAL
@brief
*   The section has a list of all internal data structures which are used internally
*   by the cfarcaProc DPU module.
*/
/**
@defgroup DPU_CFARCAPROC_INTERNAL_DEFINITION          cfarcaProc DPU Internal Definitions
@ingroup CFARCA_PROC_DPU_INTERNAL
@brief
*   The section has a list of all internal definitions which are used internally
*   by the cfarcaProc DPU.
*/


/**************************************************************************
 *************************** Include Files ********************************
 **************************************************************************/
#ifndef DPU_CFAR_HWA_H
#define DPU_CFAR_HWA_H

/* Standard Include Files. */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/* mmWave SDK Include Files */
#include <ti/utils/cycleprofiler/cycle_profiler.h>
#include <ti/datapath/dpc/dpu/cfarcaproc/cfarcaprochwa.h>
#include <ti/utils/mathutils/mathutils.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  @brief    Field of view indices as integers. For range domain values are [0
 *
 *  \ingroup DPU_CFARCAPROC_INTERNAL_DATA_STRUCTURE
 *
 */
typedef struct DPU_CFARCAProc_FovIdxCfg_t
{
    /*! Minimum Range or Doppler Bin index */
    int16_t minIdx;
    /*! Maximum Range or Doppler Bin index */
    int16_t maxIdx;
} DPU_CFARCAProc_FovIdxCfg;

/**
 * @brief
 *  HWA CFAR configuration
 *
 * @details
 *  The structure is used to hold the HWA configuration used for CFAR
 *
 *  \ingroup DPU_CFARCAPROC_INTERNAL_DATA_STRUCTURE
 */
typedef struct CFARHwaObj_t
{
    /*! @brief      number of detected objection from HWA */
    uint16_t                numHwaCfarObjs;

    /*! @brief HWA Handle */
    HWA_Handle  hwaHandle;

    /*! @brief Hardware resources */
    DPU_CFARCAProcHWA_HW_Resources res;

    /*! @brief     HWA Processing Done semaphore Handle */
    SemaphoreP_Handle    hwaDone_semaHandle;

    /*! @brief      CFAR configuration in range direction */
    DPU_CFARCAProc_CfarCfg   cfarCfgRange;

    /*! @brief      CFAR configuration in Doppler direction */
    DPU_CFARCAProc_CfarCfg   cfarCfgDoppler;

    /*! @brief      Field of view configuration in range domain */
    DPU_CFARCAProc_FovIdxCfg fovRange;

    /*! @brief      Field of view configuration in Doppler domain */
    DPU_CFARCAProc_FovIdxCfg fovDoppler;

    DPU_CFARCAProcHWA_StaticConfig staticCfg;

    /*! @brief total number of calls of DPU processing */
    uint32_t            numProcess;

}CFARHwaObj;



#ifdef __cplusplus
}
#endif

#endif /* DPU_CFAR_HWA_H */

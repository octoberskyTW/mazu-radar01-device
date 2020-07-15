/**
 *   @file  dopplerprocdspinternal.h
 *
 *   @brief
 *      Internal header file for Doppler DSP DPU.
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
#ifndef DOPPLERPROC_DSP_INTERNAL_H
#define DOPPLERPROC_DSP_INTERNAL_H

/* Standard Include Files. */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include <ti/utils/cycleprofiler/cycle_profiler.h>

/* DPIF Components Include Files */
#include <ti/datapath/dpif/dpif_detmatrix.h>
#include <ti/datapath/dpif/dpif_radarcube.h>

/* mmWave SDK Data Path Include Files */
#include <ti/datapath/dpif/dp_error.h>
#include <ti/datapath/dpc/dpu/dopplerproc/dopplerprocdsp.h>

#ifdef __cplusplus
extern "C" {
#endif


/*! Ping index used for EDMA-CPU processing parallelism */
#define DPU_DOPPLERPROCDSP_PING_IDX 0

/*! Pong index used for EDMA-CPU processing parallelism */
#define DPU_DOPPLERPROCDSP_PONG_IDX 1

/**
 * @brief
 *  dopplerProc DPU internal data Object
 *
 * @details
 *  The structure is used to hold dopplerProc internal data object
 *
 *  \ingroup DPU_DOPPLERPROC_INTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_DopplerProcDSP_Obj_t
{
    /*! @brief  DPU configuration parameters to be used during DPU process */
    DPU_DopplerProcDSP_Config cfg;
    
    /*! @brief DFT Half bin value for Doppler compensation.*/
    cmplx16ImRe_t dftHalfBin;

    /*! @brief Flag to indicate if DPU is in processing state */
    bool inProgress;

    /*! @brief Holds the value of Ceil(Log2(numVirtualAntennas))*/
    uint8_t log2VirtAnt;
}DPU_DopplerProcDSP_Obj;


#ifdef __cplusplus
}
#endif

#endif

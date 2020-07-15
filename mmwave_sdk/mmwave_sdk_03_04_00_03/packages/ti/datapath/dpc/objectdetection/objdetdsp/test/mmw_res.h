/**
 *   @file  mmw_res.h
 *
 *   @brief
 *      Defines partitioning of hardware resources (HWA, EDMA etc) among the
 *      DPCs and other components in the millimeter wave demo.
 *
 *  \par
 *  NOTE:
 *      (C) Copyright 2016 Texas Instruments, Inc.
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
#ifndef MMW_DEMO_RES_H
#define MMW_DEMO_RES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/drivers/edma/edma.h>
#include <ti/common/sys_common.h>

/*******************************************************************************
 * Resources for Object Detection DPC, currently the only DPC and hwa/edma
 * resource user in the demo.
 *******************************************************************************/
#define DPC_OBJDET_EDMA_SHADOW_BASE                                   EDMA_NUM_DMA_CHANNELS

/* Range DPU */
#define DPC_OBJDET_DPU_RANGEPROC_EDMA_INST_ID                         0
#define DPC_OBJDET_DPU_RANGEPROC_EDMAIN_PING_CH                       EDMA_TPCC0_REQ_FREE_0
#define DPC_OBJDET_DPU_RANGEPROC_EDMAIN_PING_SHADOW                   (DPC_OBJDET_EDMA_SHADOW_BASE + 0)
#define DPC_OBJDET_DPU_RANGEPROC_EDMAIN_PING_EVENT_QUE                0
#define DPC_OBJDET_DPU_RANGEPROC_EDMAIN_PONG_CH                       EDMA_TPCC0_REQ_FREE_1
#define DPC_OBJDET_DPU_RANGEPROC_EDMAIN_PONG_SHADOW                   (DPC_OBJDET_EDMA_SHADOW_BASE + 1)
#define DPC_OBJDET_DPU_RANGEPROC_EDMAIN_PONG_EVENT_QUE                0

#define DPC_OBJDET_DPU_RANGEPROC_EDMAOUT_PING_CH                      EDMA_TPCC0_REQ_FREE_2
#define DPC_OBJDET_DPU_RANGEPROC_EDMAOUT_PING_SHADOW                  (DPC_OBJDET_EDMA_SHADOW_BASE + 2)
#define DPC_OBJDET_DPU_RANGEPROC_EDMAOUT_PING_EVENT_QUE               0
#define DPC_OBJDET_DPU_RANGEPROC_EDMAOUT_PONG_CH                      EDMA_TPCC0_REQ_FREE_3
#define DPC_OBJDET_DPU_RANGEPROC_EDMAOUT_PONG_SHADOW                  (DPC_OBJDET_EDMA_SHADOW_BASE + 3)
#define DPC_OBJDET_DPU_RANGEPROC_EDMAOUT_PONG_EVENT_QUE               0


/* Doppler DPU */
#define DPC_OBJDET_DPU_DOPPLERPROC_EDMA_INST_ID                       0
#define DPC_OBJDET_DPU_DOPPLERPROC_EDMAIN_PING_CH                     EDMA_TPCC0_REQ_FREE_4
#define DPC_OBJDET_DPU_DOPPLERPROC_EDMAIN_PING_SHADOW                 (DPC_OBJDET_EDMA_SHADOW_BASE + 4)
#define DPC_OBJDET_DPU_DOPPLERPROC_EDMAIN_PING_EVENT_QUE              0

#define DPC_OBJDET_DPU_DOPPLERPROC_EDMAIN_PONG_CH                     EDMA_TPCC0_REQ_FREE_5
#define DPC_OBJDET_DPU_DOPPLERPROC_EDMAIN_PONG_SHADOW                 (DPC_OBJDET_EDMA_SHADOW_BASE + 5)
#define DPC_OBJDET_DPU_DOPPLERPROC_EDMAIN_PONG_EVENT_QUE              0

#define DPC_OBJDET_DPU_DOPPLERPROC_EDMAOUT_PING_CH                    EDMA_TPCC0_REQ_FREE_6
#define DPC_OBJDET_DPU_DOPPLERPROC_EDMAOUT_PING_SHADOW                (DPC_OBJDET_EDMA_SHADOW_BASE + 6)
#define DPC_OBJDET_DPU_DOPPLERPROC_EDMAOUT_PING_EVENT_QUE             0

#define DPC_OBJDET_DPU_DOPPLERPROC_EDMAOUT_PONG_CH                    EDMA_TPCC0_REQ_FREE_7
#define DPC_OBJDET_DPU_DOPPLERPROC_EDMAOUT_PONG_SHADOW                (DPC_OBJDET_EDMA_SHADOW_BASE + 7)
#define DPC_OBJDET_DPU_DOPPLERPROC_EDMAOUT_PONG_EVENT_QUE             0

#define DPC_OBJDET_DPU_DOPPLERPROC_EDMA_PING_SIG_CH                   EDMA_TPCC0_REQ_FREE_8
#define DPC_OBJDET_DPU_DOPPLERPROC_EDMA_PING_SIG_SHADOW               (DPC_OBJDET_EDMA_SHADOW_BASE + 8)
#define DPC_OBJDET_DPU_DOPPLERPROC_EDMA_PING_SIG_EVENT_QUE            0

#define DPC_OBJDET_DPU_DOPPLERPROC_EDMA_PONG_SIG_CH                   EDMA_TPCC0_REQ_FREE_9
#define DPC_OBJDET_DPU_DOPPLERPROC_EDMA_PONG_SIG_SHADOW               (DPC_OBJDET_EDMA_SHADOW_BASE + 9)
#define DPC_OBJDET_DPU_DOPPLERPROC_EDMA_PONG_SIG_EVENT_QUE            0

/* Static Clutter DPU */
#define DPC_OBJDET_DPU_STATIC_CLUTTER_PROC_EDMA_INST_ID               0
#define DPC_OBJDET_DPU_STATIC_CLUTTER_PROC_EDMAIN_PING_CH             EDMA_TPCC0_REQ_FREE_10
#define DPC_OBJDET_DPU_STATIC_CLUTTER_PROC_EDMAIN_PING_SHADOW         (DPC_OBJDET_EDMA_SHADOW_BASE + 10)
#define DPC_OBJDET_DPU_STATIC_CLUTTER_PROC_EDMAIN_PING_EVENT_QUE      0

#define DPC_OBJDET_DPU_STATIC_CLUTTER_PROC_EDMAIN_PONG_CH             EDMA_TPCC0_REQ_FREE_11
#define DPC_OBJDET_DPU_STATIC_CLUTTER_PROC_EDMAIN_PONG_SHADOW         (DPC_OBJDET_EDMA_SHADOW_BASE + 11)
#define DPC_OBJDET_DPU_STATIC_CLUTTER_PROC_EDMAIN_PONG_EVENT_QUE      0

#define DPC_OBJDET_DPU_STATIC_CLUTTER_PROC_EDMAOUT_PING_CH            EDMA_TPCC0_REQ_FREE_12
#define DPC_OBJDET_DPU_STATIC_CLUTTER_PROC_EDMAOUT_PING_SHADOW        (DPC_OBJDET_EDMA_SHADOW_BASE + 12)
#define DPC_OBJDET_DPU_STATIC_CLUTTER_PROC_EDMAOUT_PING_EVENT_QUE     0

#define DPC_OBJDET_DPU_STATIC_CLUTTER_PROC_EDMAOUT_PONG_CH            EDMA_TPCC0_REQ_FREE_13
#define DPC_OBJDET_DPU_STATIC_CLUTTER_PROC_EDMAOUT_PONG_SHADOW        (DPC_OBJDET_EDMA_SHADOW_BASE + 13)
#define DPC_OBJDET_DPU_STATIC_CLUTTER_PROC_EDMAOUT_PONG_EVENT_QUE     0

/* CFARCA DPU */
#define DPC_OBJDET_DPU_CFARCA_PROC_EDMA_INST_ID                       0

#define DPC_OBJDET_DPU_CFARCA_PROC_EDMA_PING_CH                       EDMA_TPCC0_REQ_FREE_14
#define DPC_OBJDET_DPU_CFARCA_PROC_EDMA_PING_SHADOW                   (DPC_OBJDET_EDMA_SHADOW_BASE + 14)
#define DPC_OBJDET_DPU_CFARCA_PROC_EDMA_PING_EVENT_QUE                0

#define DPC_OBJDET_DPU_CFARCA_PROC_EDMA_PONG_CH                       EDMA_TPCC0_REQ_FREE_15
#define DPC_OBJDET_DPU_CFARCA_PROC_EDMA_PONG_SHADOW                   (DPC_OBJDET_EDMA_SHADOW_BASE + 15)
#define DPC_OBJDET_DPU_CFARCA_PROC_EDMA_PONG_EVENT_QUE                0

/* AOA DPU */
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_INST_ID                          0

#define DPC_OBJDET_DPU_AOA_PROC_EDMA_PING_CH                          EDMA_TPCC0_REQ_FREE_16
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_PING_SHADOW                      (DPC_OBJDET_EDMA_SHADOW_BASE + 16)
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_PING_EVENT_QUE                   0

#define DPC_OBJDET_DPU_AOA_PROC_EDMA_PONG_CH                          EDMA_TPCC0_REQ_FREE_17
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_PONG_SHADOW                      (DPC_OBJDET_EDMA_SHADOW_BASE + 17)
#define DPC_OBJDET_DPU_AOA_PROC_EDMA_PONG_EVENT_QUE                   0

#ifdef __cplusplus
}
#endif

#endif /* MMW_DEMO_RES_H */


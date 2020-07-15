/**
 *   @file  antenna_geometry.h
 *
 *   @brief
 *
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
#ifndef ANTENNA_GEOMETRY_H
#define ANTENNA_GEOMETRY_H

/* Standard Include Files. */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

/* mmWave SDK drivers/common Include Files */
#include <ti/common/sys_common.h>
#include <ti/board/antenna_geometry.h>

/**
 * @brief Antenna offset position in vertical and horizontal directions
 *
 */
typedef struct ANTDEF_AntOffset_t {
    /*! @brief  antenna offset in horizontal direction (azimuth) expressed in Lambda/2 */
    int16_t azimuthOffset;

    /*! @brief  antenna offset in vertical direction (elevation) expressed in Lambda/2 */
    int16_t elevationOffset;
} ANTDEF_AntOffset;

/**
 * @brief Antenna offset positions in vertical and horizontal directions
 *
 */
typedef struct ANTDEF_AntGeometry_t {
    /*! @brief  Tx antenna positions */
    ANTDEF_AntOffset txAnt[SYS_COMMON_NUM_TX_ANTENNAS];

    /*! @brief  Rx antenna positions */
    ANTDEF_AntOffset rxAnt[SYS_COMMON_NUM_RX_CHANNEL];
} ANTDEF_AntGeometry;

extern ANTDEF_AntGeometry gAntDef;

#endif

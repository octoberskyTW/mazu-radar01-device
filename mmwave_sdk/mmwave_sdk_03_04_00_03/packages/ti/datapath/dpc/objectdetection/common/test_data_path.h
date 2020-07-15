/**
 *   @file  test_data_path.h
 *
 *   @brief   
 *      Helper file for testing DPC
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

#ifndef TEST_DATA_PATH_H_
#define TEST_DATA_PATH_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Standard Include Files. */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/* BIOS/XDC Include Files. */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <ti/common/sys_common.h>
#include <ti/drivers/edma/edma.h>
#include <ti/drivers/esm/esm.h>
#include <ti/drivers/soc/soc.h>
#include <ti/control/dpm/dpm.h>
#include <ti/drivers/osal/SemaphoreP.h>
#include <ti/control/mmwavelink/mmwavelink.h>

#include <ti/board/antenna_geometry.h>


/*!
 *  @brief    Detected object estimated parameters
 *
 */
typedef volatile struct ObjectDetection_Test_detectedObj_t
{
    uint16_t   rangeIdx;     /*!< @brief Range index */
    int16_t   dopplerIdx;   /*!< @brief Doppler index. Note that it is changed
                                 to signed integer in order to handle extended maximum velocity.
                                 Neagative values correspond to the object moving toward
                                 sensor, and positive values correspond to the
                                 object moving away from the sensor */
    int16_t detObj2dAzimIdx; /*!< @brief Detected objects azimuth index for debugging */
    int16_t detObj2dElevIdx; /*!< @brief Detected objects elevation index for debugging */
    float detObjElevationAngle; /*!< @brief Detected object elevation angle for debugging */

    uint16_t  peakVal;      /*!< @brief Peak value */
    int16_t  x;             /*!< @brief x - coordinate in meters. Q format depends on the range resolution */
    int16_t  y;             /*!< @brief y - coordinate in meters. Q format depends on the range resolution */
    int16_t  z;             /*!< @brief z - coordinate in meters. Q format depends on the range resolution */
} ObjectDetection_Test_detectedObj;

/**
 * @brief
 *  Data Path Information per subframe
 *
 * @details
 *  The structure is used to hold all the relevant information for
 *  the data path per subframe
 */
typedef struct ObjectDetection_Test_SubFrameParams_t
{
    /*! @brief   MultiObjectBeamForming en/dis */
    bool    multiObjBeamFormingCfgEnabled;

    /*! @brief   Number of receive channels */
    uint32_t numRxAntennas;

    /*! @brief number of transmit antennas */
    uint32_t numTxAntennas;

    /*! @brief number of virtual antennas */
    uint32_t numVirtualAntennas;

    /*! @brief number of virtual azimuth antennas */
    uint32_t numVirtualAntAzim;

    /*! @brief number of virtual elevation antennas */
    uint32_t numVirtualAntElev;

    /*! @brief number of ADC samples */
    uint32_t numAdcSamples;

    /*! @brief  rxChan offset in ADCBuf in number of samples */
    uint32_t rxChanOffsetInSamples;

    /*! @brief Rx antenna samples in ADC buffer: 0-noninterleaved 1-interleaved */
    uint8_t isInterleavedSampInAdcBuf;

    /*! @brief (tx1+tx2)/(tx1-tx2) BPM format: 0-Disabled 1-Enabled */
    uint8_t isBpmEnabled;

    /*! @brief number of range bins */
    uint32_t numRangeBins;

    /*! @brief number of chirps per frame */
    uint32_t numChirpsPerFrame;

    /*! @brief number of Doppler chirps */
    uint32_t numDopplerChirps;

    /*! @brief number of Doppler bins */
    uint32_t numDopplerBins;

    /*! @brief number of angle bins */
    uint32_t numAngleBins;
} ObjectDetection_Test_SubFrameParams;

#ifdef __cplusplus
}
#endif

#endif /* TEST_DATA_PATH_H_ */

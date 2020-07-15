/**
 *   @file  gen_frame_data.h
 *
 *   @brief   
 *      Generate test vector for testing data path
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

#ifndef GEN_FRAME_DATA_H_
#define GEN_FRAME_DATA_H_

#ifdef __cplusplus
extern "C" {
#endif

/* BIOS/XDC Include Files. */
#include <xdc/std.h>

#include "test_data_path.h"

#define MAX_NUM_GEN_TARGETS 35

#define MAX_NUM_OBJECTS 35

/**
 * @brief
 *  Unit test scene configuration: single object parameters
 *
 */
typedef struct sceneObject_t_ {
    uint32_t amplitude;      /*!< @brief Beat signal amplitude */
    int32_t azimPhyBin;     /*!< @brief Expected peak position in azimuth FFT output */
    uint32_t rngPhyBin;      /*!< @brief Expected peak position range FFT output */
    int32_t  doppPhyBin;     /*!< @brief Expected peak position Doppler FFT output */
    int32_t elevPhyBin;     /*!< @brief Expected peak position in elevation FFT output */
} sceneObject_t;

/**
 * @brief
 *  Unit test scene configuration: group of objects
 *
 */
typedef struct sceneConfig_t_ {
    int32_t  snrdB;                             /*!< @brief SNR in dB */
    uint32_t numTargets;                        /*!< @brief Number of objects in the scene */
    sceneObject_t sceneObj[MAX_NUM_OBJECTS];    /*!< @brief Array of scene objects */
} sceneConfig_t;

/*!
 *  @brief    Reference target parameters
 */
typedef struct targetObjStruc_t_
{
    /*! @brief Signal amplitude */
    float amplitude;
    /*! @brief  range phase */
    float rngPhy;
    /*! @brief  Doppler phase */
    float doppPhy;
    /*! @brief  azimuth phase */
    float azimPhy;
    /*! @brief  range phase increment */
    float rngPhyIncr;
    /*! @brief  Doppler phase increment */
    float doppPhyIncr;
    /*! @brief  Azimuth phase increment */
    float azimPhyIncr;
    /*! @brief  expected maximum position in range FFT */
    uint32_t rngPhyBin;
    /*! @brief  expected maximum position in Doppler FFT*/
    int32_t doppPhyBin;
    /*! @brief  expected maximum position in azimmuth FFT*/
    int32_t azimPhyBin;
    /*! @brief  expected maximum position in elevation FFT*/
    int32_t elevPhyBin;
    /*! @brief elevation phase increment*/
    float elevPhyIncr;
    /*! @brief 
      Variable used to store the azimuth phase of the non-elevation
      antennas that will be used in the elevation antenna due to the
      physical position of the elevation antenna with respect to the 
      non-elevation antennas.*/
    float azimPhyElevAntenna[4/*max num RX antennas*/];  
} targetObjStruc_t;

/*!
 *  @brief    Radar reference data generation parameters
 */
typedef struct genFrameStruc_t_
{
    /*! @brief Number of targets */
    uint32_t numTargets;

    /*! @brief chirp index */
    uint32_t chirpIndex;

    /*! @brief  chirp counter modulo number of Tx antennas */
    uint32_t chirpModNumTxAntCntr;

    /*! @brief  number of Tx antennas */
    uint32_t numTxAntennas;

    /*! @brief  Noise scale */
    float noiseScale;

    /*! @brief  snr in dB*/
    float snrdB;

    /*! @brief  array of reference target objects */
    targetObjStruc_t targetObj[MAX_NUM_GEN_TARGETS];
} genFrameStruc_t;

void initFrameData (ObjectDetection_Test_SubFrameParams *subFrameParams,
                    genFrameStruc_t *genFrmDataObj,
                    sceneConfig_t *sceneConfig);

void genChirpData (ObjectDetection_Test_SubFrameParams *subFrameParams,
                   genFrameStruc_t *frm,
                   uint8_t *outputBuffer,
                   uint16_t numChirps,
                   ANTDEF_AntGeometry *antDef);
#ifdef __cplusplus
}
#endif

#endif /* GEN_FRAME_DATA_H_ */

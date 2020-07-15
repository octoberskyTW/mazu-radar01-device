/**
 *   @file  gen_frame_data.c
 *
 *   @brief
 *      Radar test input generator.
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

/* Standard Include Files. */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include <ti/utils/mathutils/mathutils.h>

#include "gen_frame_data.h"

uint16_t RandSimple(void);
void GaussianNoise(float *NoiseVariance, float *pxn, float *pyn);

/*
 *  Generates Gausian distributed random number, with unit variance
 */
void GaussianNoise(
        float *NoiseVariance,
        float *pxn,
        float *pyn)
{

    float y, dx2, pi2, r, t, temp;
    static float pi = (float)3.1415926535897;
    uint16_t itemp1;
    float gauss_var;

    pi2 = 2.f * pi;
    gauss_var = * NoiseVariance/2; /* half per dimension */

    itemp1 = RandSimple();
    while(itemp1 == 0)
        itemp1 = RandSimple();
    r = (float)(itemp1)/32767.0f;

    temp = 2.f*gauss_var*(float)log(1./r);
    y = (float)sqrt(temp);

    itemp1 = RandSimple();
    t = (float)(itemp1)/32767.0f;

    dx2 = pi2*t;
    *pxn = y*(float)cos(dx2);
    *pyn = y*(float)sin(dx2);
}

/*
 *  Generates a random number 0 - 0x7fff
 */
uint16_t RandSimple(void)
{
    static int64_t next = 1;
    uint16_t ret2;

    next = (next * 16807) % 2147483647;
    ret2 = (uint16_t)(next & 0x7fff);

    return (ret2);
}


/*!
 * \brief
 * Function Name       :    genChirpData
 *
 * \par
 * <b>Description</b>  : Generates one chirp of reference data into adc buffer. Function is called per chirp.
 *
 * @param[in]      subFrameParams Pointer to sub-frame parameters structure
 *
 * @param[in]      frm Pointer to frame reference data structure
 *
 * @param[out]      outputBuffer   Pointer to buffer with generated samples. The samples are stored in cmplx16ImRe_t format.
 *
 * @param[in]      numChirps  Number of Chirps
 *
 * @param[in]      antDef   Pointer to antenna geometry definition.
 *
 * @return         void
 *
 */
void genChirpData(ObjectDetection_Test_SubFrameParams *subFrameParams,
                   genFrameStruc_t *frm,
                   uint8_t *outputBuffer,
                   uint16_t numChirps,
                   ANTDEF_AntGeometry *antDef)
{
    float noiseRe, noiseIm;
    float xRe, xIm;
    float var = 1;
    uint32_t rxAntIdx;
    uint32_t targIdx;
    uint32_t sampleIdx;
    int32_t elevIdx;
    int32_t azimIdx;
    targetObjStruc_t * pT;
    uint32_t idx;
    cmplx16ImRe_t * adcBuff = (cmplx16ImRe_t *) outputBuffer;
    uint32_t chirpIdx;
    float samplePhy;
    float doppPhy;
    float azimPhy;
    float elevPhy;

    if(adcBuff == NULL)
    {
        printf("\nError getChirpData. adcBuff not defined.\n");
        return;
    }

    memset ((uint8_t *) adcBuff, 0, subFrameParams->numRxAntennas * subFrameParams->numAdcSamples * sizeof(cmplx16ReIm_t) * numChirps );

    for(chirpIdx = 0; chirpIdx < numChirps; chirpIdx++)
    {
        for (rxAntIdx = 0; rxAntIdx < subFrameParams->numRxAntennas; rxAntIdx++)
        {
            elevIdx = antDef->txAnt[frm->chirpModNumTxAntCntr].elevationOffset + antDef->rxAnt[rxAntIdx].elevationOffset;
            azimIdx = antDef->txAnt[frm->chirpModNumTxAntCntr].azimuthOffset + antDef->rxAnt[rxAntIdx].azimuthOffset;

            for (sampleIdx = 0; sampleIdx < subFrameParams->numAdcSamples;  sampleIdx++)
            {
                GaussianNoise(&var, &noiseRe, &noiseIm);
                xRe = frm->noiseScale * noiseRe;
                xIm = frm->noiseScale * noiseIm;
                for (targIdx = 0; targIdx < frm->numTargets; targIdx++)
                {
                    pT = &frm->targetObj[targIdx];

                    samplePhy = pT->rngPhyIncr * sampleIdx;
                    azimPhy = pT->azimPhyIncr * azimIdx;
                    elevPhy = pT->elevPhyIncr * elevIdx;
                    doppPhy = pT->doppPhyIncr * frm->chirpIndex;

                    xRe  += pT->amplitude * cos(samplePhy + doppPhy + azimPhy + elevPhy);
                    xIm  += pT->amplitude * sin(samplePhy + doppPhy + azimPhy + elevPhy);
                }
                if (subFrameParams->isInterleavedSampInAdcBuf)
                {
                    /*samples are interleaved , multiple-chirp is not supported in generation */
                    idx = sampleIdx*subFrameParams->numRxAntennas + rxAntIdx;
                }
                else
                {
                    uint32_t oneChirpSampleSize;

                    oneChirpSampleSize = subFrameParams->numAdcSamples ;

                    /* 4 sample aligned */
                    oneChirpSampleSize = (oneChirpSampleSize + 3)/4 * 4;

                    /*samples are not interleaved (all samples for antenna[i] are sequential)*/
                    idx = rxAntIdx * subFrameParams->rxChanOffsetInSamples + chirpIdx * oneChirpSampleSize + sampleIdx;
                }
                adcBuff[idx].real = (int16_t) MATHUTILS_ROUND_FLOAT(xRe);
                adcBuff[idx].imag = (int16_t) MATHUTILS_ROUND_FLOAT(xIm);

            }

        }

        frm->chirpIndex++;
        frm->chirpModNumTxAntCntr++;

        if (frm->chirpModNumTxAntCntr == frm->numTxAntennas)
        {
            frm->chirpModNumTxAntCntr = 0;
        }
    }
}

/*!
 * \brief
 * Function Name       :    initFrameData
 *
 * \par
 * <b>Description</b>  : Initializes radar ADC reference data.
 *
 * @param[in]      subFrameParams Pointer to sub-frame parameters structure
 *
 * @param[out]      genFrmDataObj Pointer to frame reference data
 *
 * @param[in]      sceneConfig   Pointer to scene configuration
 *
 * @return         void
 *
 */
void initFrameData (ObjectDetection_Test_SubFrameParams *subFrameParams,
                    genFrameStruc_t *genFrmDataObj,
                    sceneConfig_t *sceneConfig)
{
    uint32_t i;
    uint32_t numRangeBins;
    float sigPower = 0.0;

    genFrmDataObj->numTargets = sceneConfig->numTargets;
    genFrmDataObj->snrdB = (float)sceneConfig->snrdB;

    for (i = 0; i < sceneConfig->numTargets; i++)
    {
        genFrmDataObj->targetObj[i].amplitude  = (float)sceneConfig->sceneObj[i].amplitude;
        genFrmDataObj->targetObj[i].azimPhyBin =  sceneConfig->sceneObj[i].azimPhyBin;
        genFrmDataObj->targetObj[i].elevPhyBin =  sceneConfig->sceneObj[i].elevPhyBin;
        genFrmDataObj->targetObj[i].rngPhyBin  = sceneConfig->sceneObj[i].rngPhyBin;
        genFrmDataObj->targetObj[i].doppPhyBin =  sceneConfig->sceneObj[i].doppPhyBin;
        sigPower += genFrmDataObj->targetObj[i].amplitude * genFrmDataObj->targetObj[i].amplitude;
        genFrmDataObj->targetObj[i].amplitude = genFrmDataObj->targetObj[i].amplitude;
    }

    genFrmDataObj->noiseScale =  sqrt(sigPower / pow(10., genFrmDataObj->snrdB/10.))  / sqrt(2.);


    genFrmDataObj->numTxAntennas = subFrameParams->numTxAntennas;
    genFrmDataObj->chirpIndex = 0;
    genFrmDataObj->chirpModNumTxAntCntr = 0;

    //Because of workaround for range DPU limitation (number of virtual antennas = 12 and range FFT size = 1024):
    if (subFrameParams->numRangeBins == 1022)
    {
        numRangeBins = 1024;
    }
    else
    {
        numRangeBins = subFrameParams->numRangeBins;
    }

    for (i=0; i < genFrmDataObj->numTargets; i++)
    {
        genFrmDataObj->targetObj[i].azimPhyIncr = 2 * PI_ * 
            genFrmDataObj->targetObj[i].azimPhyBin / (float) subFrameParams->numAngleBins;
        genFrmDataObj->targetObj[i].elevPhyIncr =  2 * PI_ *
            genFrmDataObj->targetObj[i].elevPhyBin / (float) subFrameParams->numAngleBins;
        genFrmDataObj->targetObj[i].rngPhyIncr = 2 * PI_ * 
            genFrmDataObj->targetObj[i].rngPhyBin / (float) numRangeBins;
        genFrmDataObj->targetObj[i].doppPhyIncr = 2 * PI_ * 
            genFrmDataObj->targetObj[i].doppPhyBin /((float) subFrameParams->numTxAntennas * (float) subFrameParams->numDopplerBins);
        genFrmDataObj->targetObj[i].azimPhy = 0;
        genFrmDataObj->targetObj[i].rngPhy = 0;
        genFrmDataObj->targetObj[i].doppPhy = 0;
    }
}


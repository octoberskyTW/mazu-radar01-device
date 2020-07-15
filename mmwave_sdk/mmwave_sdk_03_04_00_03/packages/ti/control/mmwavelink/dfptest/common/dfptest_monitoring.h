/*
 *   @file  dfptest_monitoring.h
 *
 *   @brief
 *      Header file for monitoring and calibration APIs
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

#ifndef DFPTESTMON_H
#define DFPTESTMON_H

#ifdef __cplusplus
extern "C" {
#endif

/*Maximum number of different monitoring reports*/
#define MMWAVELINK_TEST_MAX_NUM_MON 40
/*Analog monitoring*/
#define MMWAVELINK_TEST_MON_TEMP               0U
#define MMWAVELINK_TEST_MON_RX_GAIN_PH         1U
#define MMWAVELINK_TEST_MON_RX_NOISE_FIG       2U
#define MMWAVELINK_TEST_MON_RX_IF_STAGE        3U
#define MMWAVELINK_TEST_MON_TX0_POWER          4U
#define MMWAVELINK_TEST_MON_TX1_POWER          5U
#define MMWAVELINK_TEST_MON_TX2_POWER          6U
#define MMWAVELINK_TEST_MON_TX0_BALL_BRK       7U
#define MMWAVELINK_TEST_MON_TX1_BALL_BRK       8U
#define MMWAVELINK_TEST_MON_TX2_BALL_BRK       9U
#define MMWAVELINK_TEST_MON_TX_GAIN_PHASE      10U
#define MMWAVELINK_TEST_MON_TX0_BPM            11U
#define MMWAVELINK_TEST_MON_TX1_BPM            12U
#define MMWAVELINK_TEST_MON_TX2_BPM            13U
#define MMWAVELINK_TEST_MON_SYNTHESIZER_FREQ   14U
#define MMWAVELINK_TEST_MON_EXTERN_ANALOG_SIG  15U
#define MMWAVELINK_TEST_MON_TX0_INT_ANA_SIG    16U
#define MMWAVELINK_TEST_MON_TX1_INT_ANA_SIG    17U
#define MMWAVELINK_TEST_MON_TX2_INT_ANA_SIG    18U
#define MMWAVELINK_TEST_MON_INT_RX_SIG         19U
#define MMWAVELINK_TEST_MON_INT_PMCLKLO_SIG    20U 
#define MMWAVELINK_TEST_MON_INT_GPADC_SIG      21U
#define MMWAVELINK_TEST_MON_PLL_CONTROL_VOLT   22U
#define MMWAVELINK_TEST_MON_DCC_CLOCK_FREQ     23U
#define MMWAVELINK_TEST_MON_RX_IF_SATURATION   24U
#define MMWAVELINK_TEST_MON_RX_SIG_IMG_BAND    25U
#define MMWAVELINK_TEST_MON_RX_MIXER_INP_POWER 26U
#define MMWAVELINK_TEST_MAX_NUM_ANALOG_MON_REP (MMWAVELINK_TEST_MON_RX_MIXER_INP_POWER + 1)
/*Digital monitoring*/
#define MMWAVELINK_TEST_MON_DIG_LATENT_FAULT   30U
#define MMWAVELINK_TEST_MON_DIG_PERIODIC_REP   31U
/*Calibration*/
#define MMWAVELINK_TEST_CALIBRATION_REP        35U
/*Monitoring header*/
#define MMWAVELINK_TEST_MON_REPORT_HEADER    (MMWAVELINK_TEST_MAX_NUM_MON - 1)

/**/

int32_t MmwaveLink_setCalMonConfig (void);
int32_t MmwaveLink_setInitTimeCalibConfig (void);
int32_t MmwaveLink_setRunTimeCalibConfig (void);
int32_t MmwaveLink_setRfRxIfSatMonConfig (void);
int32_t MmwaveLink_setRfRxSigImgMonConfig (void);

int32_t MmwaveLink_monFeatureCfg(void);
int32_t MmwaveLink_genLatentFaultRep(uint32_t numberOfReports, bool printDebugInfo);

#ifdef __cplusplus
}
#endif

#endif

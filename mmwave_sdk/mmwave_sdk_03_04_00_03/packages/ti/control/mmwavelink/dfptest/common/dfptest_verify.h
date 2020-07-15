/*
 *   @file  dfptest_verify.h
 *
 *   @brief
 *      Header file for verification APIs
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

#ifndef DFPTESTVERIFY_H
#define DFPTESTVERIFY_H

#ifdef __cplusplus
extern "C" {
#endif

#define DFPTEST_MAX_TEMP 100
#define DFPTEST_MIN_TEMP 0 

#define DFPTEST_MAX_TXPOWER  10000
#define DFPTEST_MIN_TXPOWER -10000 

#define DFPTEST_MAX_EXTERNSIGVAL  10000
#define DFPTEST_MIN_EXTERNSIGVAL -10000 

#define DFPTEST_MAX_PLLVOLTVAL 0XFFFFFFFF

#define DFPTEST_MAX_DCCFREQVAL 0XFFFFFFFF

#define DFPTEST_MAX_LOOPBACK_POWER_RF1 0XFFFFFFFF
#define DFPTEST_MAX_LOOPBACK_POWER_RF2 0XFFFFFFFF
#define DFPTEST_MAX_LOOPBACK_POWER_RF3 0XFFFFFFFF

#define DFPTEST_MAX_RX_NOISE_POWER1 0XFFFFFFFF
#define DFPTEST_MAX_RX_NOISE_POWER2 0XFFFFFFFF

#define DFPTEST_MAX_RX_NOISE_FIG_VAL 0XFFFF
#define DFPTEST_MIN_RX_NOISE_FIG_VAL 0

#define DFPTEST_MAX_TX_REFL_COEFF_THRESH  32760
#define DFPTEST_MIN_TX_REFL_COEFF_THRESH  (-32760)

#define DFPTEST_MAX_GPADCREF1VAL 1024
#define DFPTEST_MAX_GPADCREF2VAL 1024

#define DFPTEST_MAX_FREQ_ERR_VAL  655000000
#define DFPTEST_MIN_FREQ_ERR_VAL  (-655000000)

void MmwaveLink_monitorReportCountInit (void);
void MmwaveLink_verifyTemperatureRep(rlMonTempReportData_t *rep);
void MmwaveLink_verifyRxGainPhRep(rlMonRxGainPhRep_t *rep);
void MmwaveLink_verifyRxNoiseFigRep(rlMonRxNoiseFigRep_t *rep);
void MmwaveLink_verifyRxIfStageRep(rlMonRxIfStageRep_t *rep);
void MmwaveLink_verifyTxPower(rlMonTxPowRep_t *rep, uint32_t txAntReportIndex);
void MmwaveLink_verifyTxBallBreak(rlMonTxBallBreakRep_t *rep, uint32_t txAntReportIndex);
void MmwaveLink_verifyTxGainPhaseRep(rlMonTxGainPhaMisRep_t *rep);
void MmwaveLink_verifyTxBpm(rlMonTxBpmRep_t *rep, uint32_t txAntReportIndex);
void MmwaveLink_verifyRfSynthFreqRep(rlMonSynthFreqRep_t *rep);
void MmwaveLink_verifyExtAnalogSigRep(rlMonExtAnaSigRep_t *rep);
void MmwaveLink_verifyRfTxIntAnaSignals(rlMonTxIntAnaSigRep_t *rep, uint32_t txAntReportIndex);
void MmwaveLink_verifyRxIntAnaSigRep(rlMonRxIntAnaSigRep_t *rep);
void MmwaveLink_verifyIntPmClkLoSigRep(rlMonPmclkloIntAnaSigRep_t *rep);
void MmwaveLink_verifyIntGpadcSigRep(rlMonGpadcIntAnaSigRep_t *rep);
void MmwaveLink_verifyPllControlRep(rlMonPllConVoltRep_t *rep);
void MmwaveLink_verifyDccClockFreqRep(rlMonDccClkFreqRep_t *rep);
void MmwaveLink_verifyRxMixInpPowerRep(rlMonRxMixrInPwrRep_t *rep);
void MmwaveLink_verifyDigLatFaultRep(rlDigLatentFaultReportData_t *rep);
void MmwaveLink_verifyDigPeriodicRep(rlDigPeriodicReportData_t *rep);
void MmwaveLink_verifyRepHeader(rlMonReportHdrData_t *rep);
void MmwaveLink_verifyRunTimeCalibRep(rlRfRunTimeCalibReport_t *rep);

int32_t MmwaveLink_verifyReportCount(void);

extern bool monTestPassFlag;

#ifdef __cplusplus
}
#endif

#endif

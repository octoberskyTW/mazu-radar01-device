/*
 *   @file  link_test.h
 *
 *   @brief
 *      Header file for link_test which test the mmWave Link API
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

/**************************************************************************
 *************************** Include Files ********************************
 **************************************************************************/

#ifndef LINKTEST_H
#define LINKTEST_H

#ifdef __cplusplus
extern "C" {
#endif

extern int32_t MmwaveLink_initLink (rlUInt8_t deviceType, rlUInt8_t platform);
extern int32_t MmwaveLink_getRfBootupStatus (void);
extern int32_t MmwaveLink_getVersion (void);
extern int32_t MmwaveLink_setChannelConfig (bool useInputRxConfig, rlUInt16_t rxChannelEn);
extern int32_t MmwaveLink_setAdcOutConfig (void);
extern int32_t MmwaveLink_setLowPowerModeConfig (void);
extern int32_t MmwaveLink_setHsiClk (void);
extern int32_t MmwaveLink_rfCalibration (void);
extern int32_t MmwaveLink_setProfileConfig (void);
extern int32_t MmwaveLink_getProfileConfig (void);
extern int32_t MmwaveLink_setChirpConfig (void);
extern int32_t MmwaveLink_setMultiChirpConfig (void);
extern int32_t MmwaveLink_setFrameConfig (bool useInputNumFrames, rlUInt16_t numFrames);
extern int32_t MmwaveLink_getFrameConfig (void);
extern int32_t MmwaveLink_sensorStart (void);
extern int32_t MmwaveLink_sensorStop (void);
extern int32_t MmwaveLink_rlCalibDataStore(void);
extern int32_t MmwaveLink_rlSetLoopBackBurstCfg(uint8_t loopBackType);
extern int32_t MmwaveLink_rlSetDynChirpCfg(void);
extern int32_t MmwaveLink_getDynChirpConfig (void);
extern int32_t MmwaveLink_rlSetDynPerChirpPhShifterCfg(void);
extern int32_t MmwaveLink_setAdvFrameConfig (void);
extern int32_t MmwaveLink_getAdvFrameConfig (void);
extern int32_t MmwaveLink_setBpmCommonConfig (void);
extern int32_t MmwaveLink_setBpmChirpConfig (void);
extern int32_t MmwaveLink_setContModeConfig (void);
extern int32_t MmwaveLink_enableContMode (uint8_t bEnable);
extern int32_t MmwaveLink_rfDynamicPowerSave (void);
extern int32_t MmwaveLink_setRfDevCfg (rlUInt32_t dirData);
extern int32_t MmwaveLink_setGpAdcConfig (void);
extern int32_t MmwaveLink_rfSetLdoBypassConfig (void);
extern int32_t MmwaveLink_progFilterConfig(void);
extern int32_t MmwaveLink_rlSetDynChirpEn(void);
extern int32_t MmwaveLink_RxMixerInPwrConfig (void);
extern int32_t mmwaveLink_triggerSubframe (void);
extern int32_t mmwaveLink_miscConfig(void);
extern int32_t mmwaveLink_perChirpPhaseShifterConfig(void);
extern int32_t mmwaveLink_dynPerChirpPhaseShifterConfig(void);
extern int32_t mmwaveLink_interRxGainConfig(void);
extern int32_t mmwaveLink_getTemperatureReport(void);
extern int32_t mmwaveLink_testSourceConfig(void);
extern int32_t mmwaveLink_getDieIdStaus(void);
extern int32_t mmwaveLink_PALoopBackConfig(int8_t loopBackEn);
extern int32_t mmwaveLink_PSLoopBackConfig(int8_t loopBackEn);
extern int32_t mmwaveLink_IFLoopBackConfig(int8_t loopBackEn);
extern int32_t mmwaveLink_RxGainTempLutConfig(void);
extern int32_t mmwaveLink_RxGainTempLutRead(void);
extern int32_t mmwaveLink_TxGainTempLutConfig(void);
extern int32_t mmwaveLink_TxGainTempLutRead(void);
extern int32_t mmwaveLink_calibDataStore(void);
extern int32_t mmwaveLink_calibDataRestore(void);
extern int32_t mmwaveLink_phShiftCalibDataStore(void);
extern int32_t mmwaveLink_phShiftCalibDataRestore(void);
extern int32_t mmwaveLink_getDfeRxStatisticsReport(void);
extern int8_t MmwaveLink_VerifyCQData(uint8_t coreType, uint8_t deviceType);
extern int8_t MmwaveLink_VerifyCPData(uint8_t coreType);
extern int MmwaveLink_CQedmaSetup(void);
extern void MmwaveLink_triggerEdmaTransfer();
extern int32_t mmwaveLink_configLinkCrc(rlCrcType_t    crcType);
extern int32_t mmwaveLink_configAckTimeout(rlUInt32_t ackTimeout);
extern int32_t MmwaveLink_negativeTest (void);
extern int32_t MmwaveLink_adcBufConfig(void);

#ifdef __cplusplus
}
#endif

#endif

/*
 *   @file  dfptest_setup.h
 *
 *   @brief
 *      The file contains functions for mmwavelink/BSS/RF configuration
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

#ifndef DFPTESTSETUP_H
#define DFPTESTSETUP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dfpTestMCB
{
    uint32_t         previousFttiCount;                  
    uint32_t         chirpCnt;               
    uint32_t         frameCnt;    
}dfpTestMCB_t;

int32_t MmwaveLink_initLink (rlUInt8_t deviceType, rlUInt8_t platform);
int32_t MmwaveLink_getRfBootupStatus (void);
int32_t MmwaveLink_getVersion (void);
int32_t MmwaveLink_setChannelConfig (void);
int32_t MmwaveLink_setAdcOutConfig (void);
int32_t MmwaveLink_setLowPowerModeConfig (void);
int32_t MmwaveLink_setHsiClk (void);
int32_t MmwaveLink_rfCalibration (void);
int32_t MmwaveLink_setProfileConfig (uint16_t numProfiles);
int32_t MmwaveLink_getProfileConfig (void);
int32_t MmwaveLink_setChirpConfig (uint16_t numChirpConfigs);
int32_t MmwaveLink_setMultiChirpConfig (void);
int32_t MmwaveLink_setFrameConfig (void);
int32_t MmwaveLink_getFrameConfig (void);
int32_t MmwaveLink_sensorStart (void);
int32_t MmwaveLink_sensorStop (void);
int32_t MmwaveLink_rlCalibDataStore(void);
int32_t MmwaveLink_rlSetLoopBackBurstCfg(uint8_t loopBackType);
int32_t MmwaveLink_rlSetDynChirpCfg(void);
int32_t MmwaveLink_getDynChirpConfig (void);
int32_t MmwaveLink_rlSetDynPerChirpPhShifterCfg(void);
int32_t MmwaveLink_setAdvFrameConfig (void);
int32_t MmwaveLink_getAdvFrameConfig (void);
int32_t MmwaveLink_setBpmCommonConfig (void);
int32_t MmwaveLink_setBpmChirpConfig (uint16_t numBpmChirpConfigs);
int32_t MmwaveLink_setContModeConfig (void);
int32_t MmwaveLink_enableContMode (uint8_t bEnable);
int32_t MmwaveLink_rfDynamicPowerSave (void);
int32_t MmwaveLink_setRfDevCfg (rlUInt32_t dirData);
int32_t MmwaveLink_setGpAdcConfig (void);
int32_t MmwaveLink_rfSetLdoBypassConfig (void);
int32_t MmwaveLink_progFilterConfig(void);
int32_t MmwaveLink_rlSetDynChirpEn(void);
int32_t MmwaveLink_RxMixerInPwrConfig (void);
int32_t mmwaveLink_triggerSubframe (void);
int32_t mmwaveLink_miscConfig(void);
int32_t mmwaveLink_perChirpPhaseShifterConfig(void);
int32_t mmwaveLink_dynPerChirpPhaseShifterConfig(void);
int32_t mmwaveLink_interRxGainConfig(void);
int32_t mmwaveLink_getTemperatureReport(void);
int32_t mmwaveLink_testSourceConfig(void);
int32_t mmwaveLink_getDieIdStaus(void);
int32_t mmwaveLink_PALoopBackConfig(int8_t loopBackEn);
int32_t mmwaveLink_PSLoopBackConfig(int8_t loopBackEn);
int32_t mmwaveLink_IFLoopBackConfig(int8_t loopBackEn);
int32_t mmwaveLink_RxGainTempLutConfig(void);
int32_t mmwaveLink_RxGainTempLutRead(void);
int32_t mmwaveLink_TxGainTempLutConfig(void);
int32_t mmwaveLink_TxGainTempLutRead(void);
int32_t mmwaveLink_calibDataStore(void);
int32_t mmwaveLink_calibDataRestore(void);
int32_t mmwaveLink_phShiftCalibDataStore(void);
int32_t mmwaveLink_phShiftCalibDataRestore(void);
int32_t mmwaveLink_getDfeRxStatisticsReport(void);
int8_t MmwaveLink_VerifyCQData(uint8_t coreType, uint8_t deviceType);
int8_t MmwaveLink_VerifyCPData(uint8_t coreType);
int MmwaveLink_CQedmaSetup(void);
void MmwaveLink_triggerEdmaTransfer();
int32_t mmwaveLink_configLinkCrc(rlCrcType_t    crcType);
int32_t mmwaveLink_configAckTimeout(rlUInt32_t ackTimeout);
int32_t MmwaveLink_negativeTest (void);
int32_t MmwaveLink_adcBufConfig(void);


#ifdef __cplusplus
}
#endif

#endif

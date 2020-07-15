/*
 *   @file  dfptest_config.c
 *
 *   @brief
 *      The file contains config variables used by the test bench
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

/* Standard Include Files. */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include <ti/common/sys_common.h>

#include <ti/control/mmwavelink/mmwavelink.h>
#include <ti/control/mmwavelink/dfptest/common/dfptest_config.h>

/**************** Variables that are not populated by the config ******************** 
*                 files and need to be manually set for each test                   *
*************************************************************************************/

/* Set which test to run */
uint32_t gTestNumber = 1;

/*
  -If this variable is set to zero, the number of frames given in the config files are not changed.
  -If this variable is greater than zero, it will overwrite the configured number of frames for all tests run
  with the value given here. This is useful if one wants to increase the test duration for tests with start/stop reconfig
  without having to create new config files for all the reconfig.
  */
uint16_t gNumberOfFrames = 0;

/*If this variable is set to true, the test bench disables the features that are not supported on IWR devices.
  Using this variable allows to run the same config file for AWR and IWR device. For AWR devices, set this to false.
  The features not supported on IWR are:
  - Periodic Digital and Analog Monitoring are not supported
*/
bool gIwrDeviceFlag = false;

/**************** Variables that are populated by the config ************************ 
*                 files for each test                                               *
*************************************************************************************/

/* Test bench configuration. Loaded from config file. */
dfpTestMiscCfg_t gTestMiscCfg;

/* Start stop configuration. Loaded from config file. */
dfpTestStartStopCfg_t gTestStartStopCfg;

/* mmwavelink/BSS configuration. All loaded from config file.*/
rlChanCfg_t chCfg;
rlAdcOutCfg_t adcOutCfgArgs;
rlLowPowerModeCfg_t lowPowerModeCfg;
rlDevHsiClk_t deviceHsiClk;
rlProfileCfg_t  profileCfg[DFPTEST_MAX_NUM_PROFCFG];
rlChirpCfg_t  chirpCfg[DFPTEST_MAX_NUM_CHIRPCFG];
rlDynChirpCfg_t dynChirpCfg[10];
rlRxSatMonConf_t rxSatMonCfg;
rlSigImgMonConf_t sigImgMonCfg;
rlFrameCfg_t  frameCfg;
rlRfCalMonTimeUntConf_t calMonTimeUnitConf;
rlRfCalMonFreqLimitConf_t freqLimit;
rlRfInitCalConf_t rfInitCalib;
rlRunTimeCalibConf_t runTimeCalib;
rlAdvFrameCfg_t advFrameCfg;
rlBpmCommonCfg_t bpmCommonCfg;
rlBpmChirpCfg_t bpmChirpCfg[DFPTEST_MAX_NUM_BPMCHIRPCFG];
rlContModeCfg_t contModeCfg;
rlContModeEn_t contModeEn;
rlDynPwrSave_t dynPwrSave;
rlGpAdcCfg_t gpAdcCfg;
rlRfLdoBypassCfg_t rfLdoBypassCfg;
rlMonAnaEnables_t monAnaEnables;
rlMonDigEnables_t monDigEnables;
rlDigMonPeriodicConf_t monDigPeriodicCfg;
rlTempMonConf_t tempMonCfg;
rlRxGainPhaseMonConf_t rxGainPhaseMonCfg;
rlRxNoiseMonConf_t rxNoiseMonCfg;
rlRxIfStageMonConf_t monRxIfStageCfg;
rlTxPowMonConf_t tx0PowMonCfg;
rlTxPowMonConf_t tx1PowMonCfg;
rlTxPowMonConf_t tx2PowMonCfg;
rlAllTxPowMonConf_t allTxPowMonCfg;
rlTxBallbreakMonConf_t tx0BallBreakMonCfg;
rlTxBallbreakMonConf_t tx1BallBreakMonCfg;
rlTxBallbreakMonConf_t tx2BallBreakMonCfg;
rlAllTxBallBreakMonCfg_t allTxBallbreakMonCfg;
rlTxGainPhaseMismatchMonConf_t txGainPhMisMatchMonCfg;
rlTxBpmMonConf_t tx0BpmMonCfg;
rlTxBpmMonConf_t tx1BpmMonCfg;
rlTxBpmMonConf_t tx2BpmMonCfg;
rlAllTxBpmMonConf_t allTxBpmMonCfg;
rlSynthFreqMonConf_t synthFreqMonCfg;
rlExtAnaSignalsMonConf_t extAnaSigMonCfg;
rlTxIntAnaSignalsMonConf_t tx0IntAnaSigMonCfg;
rlTxIntAnaSignalsMonConf_t tx1IntAnaSigMonCfg;
rlTxIntAnaSignalsMonConf_t tx2IntAnaSigMonCfg;
rlAllTxIntAnaSignalsMonConf_t allTxanaSigMonCfg;
rlRxIntAnaSignalsMonConf_t rxIntAnaSigMonCfg;
rlPmClkLoIntAnaSignalsMonConf_t pmClkLoIntAnaSigMonCfg;
rlGpadcIntAnaSignalsMonConf_t gpadcIntAnaSigMonCfg;
rlPllContrVoltMonConf_t pllConVoltMonCfg;
rlDualClkCompMonConf_t dualClkCompMonCfg;
rlRxMixInPwrMonConf_t rxMixInpwrMonCfg;
rlRfProgFiltConf_t progFiltCfg;
rlRfProgFiltCoeff_t progFiltCoef;
rlSubFrameStartCfg_t subFrameTrigCfg;
rlRfMiscConf_t miscCfg;
rlRfPhaseShiftCfg_t phaseShiftCfg[DFPTEST_MAX_NUM_PHASESHCFG];
rlDynPerChirpPhShftCfg_t dynPhaseShiftCfg[DFPTEST_MAX_NUM_DYNPHASESHCFG];
rlInterRxGainPhConf_t interRxGainPhCfg;
rlTestSource_t testSourceCfg;
rlTestSourceEnable_t testSourceEn;
rlRxGainTempLutReadReq_t rxGainTempLutReadCfg;
rlTxGainTempLutReadReq_t txGainTempLutReadCfg;


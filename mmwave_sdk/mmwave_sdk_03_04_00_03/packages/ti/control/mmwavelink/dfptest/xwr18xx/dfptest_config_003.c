/* ======================================================================
 *   Copyright (C) 2019 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file dfptest_config_003.c
 *
 *  \brief This test configures report mode 0 for all analog monitoring
 *  features. It verifies if the received reports match the behavior
 *  of the configured reporting mode.
 */

/**************************************************************************
 *************************** Include Files ********************************
 **************************************************************************/
 
/* Standard Include Files */
#include <stdio.h>
#include <stdbool.h>

/* mmWave SDK Include File */
#include <ti/control/mmwavelink/mmwavelink.h>

/* Link Test Include File */

#include <ti/control/mmwavelink/dfptest/common/dfptest_monitoring.h>
#include <ti/control/mmwavelink/dfptest/common/dfptest_config.h>

/**************************************************************************
 *************************** Test bench Global Definitions ***************************
 **************************************************************************/

dfpTestMiscCfg_t gTestMiscCfg_003 =
{

    .dig1TempSensor = true,
    .testAdvancedFrame = false,
    .numLatentFaultBeforeFrameStart = 100, //Also make sure that monDigEnables_00x has mask enabled otherwise report wont be generated
    .numLatentFaultAfterFrameStop  = 100, //Also make sure that monDigEnables_00x has mask enabled otherwise report wont be generated     
    .numChirpConfigs = 2, 
    .numBpmChirpConfigs = 3,
    .numProfiles = 4,
    .failFeatureMask = 0 //No induced failure        
};

dfpTestStartStopCfg_t gTestStartStopCfg_003 =
{
    .numStartStopNoReconfig = 1,
    .numStartStopReconfig = 0
};

/**************************************************************************
 *************************** Mmwavelink Global Structures*****************************
 **************************************************************************/
 
rlChanCfg_t chCfg_003  =
{
    .rxChannelEn = RX_CHANNEL_1_2_3_4_ENABLE, 
    .txChannelEn = TX_CHANNEL_1_2_3_ENABLE,
    .cascading   = 0x0,
    .cascadingPinoutCfg   = 0x0,
};

rlAdcOutCfg_t adcOutCfgArgs_003 =
{
    .fmt.b2AdcBits = ADC_BITS_16,
    .fmt.b2AdcOutFmt = ADC_FORMAT_CPMLEX_WITH_IMG_BAND,
    .fmt.b8FullScaleReducFctr = 0U,
    .reserved0  = 0x0,
    .reserved1  = 0x0,
};

rlLowPowerModeCfg_t lowPowerModeCfg_003 =
{
    .reserved  = 0x0,
    .lpAdcMode = LP_ADC_MODE_LOW_POWER,
};

rlDevHsiClk_t deviceHsiClk_003 =
{
    .hsiClk = 9,
    .reserved = 0x0,
};

rlProfileCfg_t  profileCfg_003[DFPTEST_MAX_NUM_PROFCFG] =
{
    {
        .profileId = 0,
        .pfVcoSelect = 0x0,
        .pfCalLutUpdate = 0x0,
        .startFreqConst = PROFILE_START_FREQ_VAL,
        .idleTimeConst = PROFILE_IDLE_TIME_VAL,
        .adcStartTimeConst = PROFILE_ADC_START_TIME_VAL,
        .rampEndTime = PROFILE_RAMP_END_TIME_VAL,
        .txOutPowerBackoffCode = PROFILE_TXOUT_POWER_BACKOFF,
        .txPhaseShifter = PROFILE_TXPHASESHIFTER_VAL,
        .freqSlopeConst = PROFILE_FREQ_SLOPE_VAL,
        .txStartTime = PROFILE_TX_START_TIME_VAL,
        .numAdcSamples = PROFILE_ADC_SAMPLE_VAL,
        .digOutSampleRate = PROFILE_DIGOUT_SAMPLERATE_VAL2,
        .hpfCornerFreq1 = PROFILE_HPFCORNER_FREQ1_VAL,
        .hpfCornerFreq2 = PROFILE_HPFCORNER_FREQ2_VAL,
        .txCalibEnCfg = 0x0,
        .rxGain = PROFILE_RX_GAIN_VAL,
        .reserved = 0x0
    },
    {
        .profileId = 1,
        .pfVcoSelect = 0x0,
        .pfCalLutUpdate = 0x0,
        .startFreqConst = PROFILE_START_FREQ_VAL,
        .idleTimeConst = PROFILE_IDLE_TIME_VAL,
        .adcStartTimeConst = PROFILE_ADC_START_TIME_VAL,
        .rampEndTime = PROFILE_RAMP_END_TIME_VAL,
        .txOutPowerBackoffCode = PROFILE_TXOUT_POWER_BACKOFF,
        .txPhaseShifter = PROFILE_TXPHASESHIFTER_VAL,
        .freqSlopeConst = PROFILE_FREQ_SLOPE_VAL,
        .txStartTime = PROFILE_TX_START_TIME_VAL,
        .numAdcSamples = PROFILE_ADC_SAMPLE_VAL,
        .digOutSampleRate = PROFILE_DIGOUT_SAMPLERATE_VAL2,
        .hpfCornerFreq1 = PROFILE_HPFCORNER_FREQ1_VAL,
        .hpfCornerFreq2 = PROFILE_HPFCORNER_FREQ2_VAL,
        .txCalibEnCfg = 0x0,
        .rxGain = PROFILE_RX_GAIN_VAL,
        .reserved = 0x0
    },
    {
        .profileId = 2,
        .pfVcoSelect = 0x0,
        .pfCalLutUpdate = 0x0,
        .startFreqConst = PROFILE_START_FREQ_VAL,
        .idleTimeConst = PROFILE_IDLE_TIME_VAL,
        .adcStartTimeConst = PROFILE_ADC_START_TIME_VAL,
        .rampEndTime = PROFILE_RAMP_END_TIME_VAL,
        .txOutPowerBackoffCode = PROFILE_TXOUT_POWER_BACKOFF,
        .txPhaseShifter = PROFILE_TXPHASESHIFTER_VAL,
        .freqSlopeConst = PROFILE_FREQ_SLOPE_VAL,
        .txStartTime = PROFILE_TX_START_TIME_VAL,
        .numAdcSamples = PROFILE_ADC_SAMPLE_VAL,
        .digOutSampleRate = PROFILE_DIGOUT_SAMPLERATE_VAL2,
        .hpfCornerFreq1 = PROFILE_HPFCORNER_FREQ1_VAL,
        .hpfCornerFreq2 = PROFILE_HPFCORNER_FREQ2_VAL,
        .txCalibEnCfg = 0x0,
        .rxGain = PROFILE_RX_GAIN_VAL,
        .reserved = 0x0
    },
    {
        .profileId = 3,
        .pfVcoSelect = 0x0,
        .pfCalLutUpdate = 0x0,
        .startFreqConst = PROFILE_START_FREQ_VAL,
        .idleTimeConst = PROFILE_IDLE_TIME_VAL,
        .adcStartTimeConst = PROFILE_ADC_START_TIME_VAL,
        .rampEndTime = PROFILE_RAMP_END_TIME_VAL,
        .txOutPowerBackoffCode = PROFILE_TXOUT_POWER_BACKOFF,
        .txPhaseShifter = PROFILE_TXPHASESHIFTER_VAL,
        .freqSlopeConst = PROFILE_FREQ_SLOPE_VAL,
        .txStartTime = PROFILE_TX_START_TIME_VAL,
        .numAdcSamples = PROFILE_ADC_SAMPLE_VAL,
        .digOutSampleRate = PROFILE_DIGOUT_SAMPLERATE_VAL2,
        .hpfCornerFreq1 = PROFILE_HPFCORNER_FREQ1_VAL,
        .hpfCornerFreq2 = PROFILE_HPFCORNER_FREQ2_VAL,
        .txCalibEnCfg = 0x0,
        .rxGain = PROFILE_RX_GAIN_VAL,
        .reserved = 0x0
    }
};

rlChirpCfg_t  chirpCfg_003[DFPTEST_MAX_NUM_CHIRPCFG] =
{
    {
        .chirpStartIdx = 0,
        .chirpEndIdx = 255U,
        .profileId = 0,
        .reserved = 0x0,
        .startFreqVar = CHIRP_START_FREQ_VAL,
        .freqSlopeVar= CHIRP_FREQ_SLOPE_VAL,
        .idleTimeVar = CHIRP_IDLE_TIME_VAL,
        .adcStartTimeVar = CHIRP_ADC_START_TIME_VAL,
        .txEnable = CHIRP_TX_1_CHANNEL_ENABLE
    },
    {
        .chirpStartIdx = 256U,
        .chirpEndIdx = 511U,
        .profileId = 1U,
        .reserved = 0x0,
        .startFreqVar = CHIRP_START_FREQ_VAL,
        .freqSlopeVar= CHIRP_FREQ_SLOPE_VAL,
        .idleTimeVar = CHIRP_IDLE_TIME_VAL,
        .adcStartTimeVar = CHIRP_ADC_START_TIME_VAL,
        .txEnable = CHIRP_TX_2_CHANNEL_ENABLE
    }
};

rlMonDigEnables_t monDigEnables_003 =
{
    .enMask = ((0 << 0)   | /*Enable all except the defeatured and reserved bits*/
         (1 << 1)   | 
         (0 << 2)   | 
         (1 << 3)   | 
         (0 << 4)   | 
         (0 << 5)   | 
         (1 << 6)   | 
         (0 << 7)   | 
         (1 << 8)   | 
         (1 << 9)   | 
         (1 << 10)  | 
         (1 << 11)  | 
         (0 << 12)  | 
         (0 << 13)  | 
         (0 << 14)  | 
         (0 << 15)  | 
         (1 << 16)  | 
         (1 << 17)  | 
         (0 << 18)  | 
         (1 << 19)  | 
         (1 << 20)  | 
         (0 << 21)  | 
         (0 << 22)  | 
         (0 << 23)  | 
         (1 << 24)  | 
         (1 << 25)  | 
         (0 << 26)  | 
         (0 << 27)  | 
         (0 << 28)  | 
         (0 << 29)  | 
         (0 << 30)  | 
         (0 << 31)),

    .testMode = 0
};

rlDigMonPeriodicConf_t monDigPeriodicCfg_003 =
{
    .reportMode = 0,
    .periodicEnableMask = 0xD
};    

rlMonAnaEnables_t monAnaEnables_003 = /*enable all analog monitors*/
{
    .enMask = ((1 << MMWAVELINK_TEST_MON_TEMP               ) |
               (1 << MMWAVELINK_TEST_MON_RX_GAIN_PH         ) |
               (1 << MMWAVELINK_TEST_MON_RX_NOISE_FIG       ) |
               (1 << MMWAVELINK_TEST_MON_RX_IF_STAGE        ) |
               (1 << MMWAVELINK_TEST_MON_TX0_POWER          ) |
               (1 << MMWAVELINK_TEST_MON_TX1_POWER          ) |
               (1 << MMWAVELINK_TEST_MON_TX2_POWER          ) |
               (1 << MMWAVELINK_TEST_MON_TX0_BALL_BRK       ) |
               (1 << MMWAVELINK_TEST_MON_TX1_BALL_BRK       ) |
               (1 << MMWAVELINK_TEST_MON_TX2_BALL_BRK       ) |
               (1 << MMWAVELINK_TEST_MON_TX_GAIN_PHASE      ) |
//               (1 << MMWAVELINK_TEST_MON_TX0_BPM            ) |
//               (1 << MMWAVELINK_TEST_MON_TX1_BPM            ) |
//               (1 << MMWAVELINK_TEST_MON_TX2_BPM            ) |
               (1 << MMWAVELINK_TEST_MON_SYNTHESIZER_FREQ   ) |
               (1 << MMWAVELINK_TEST_MON_EXTERN_ANALOG_SIG  ) |
               (1 << MMWAVELINK_TEST_MON_TX0_INT_ANA_SIG    ) |
               (1 << MMWAVELINK_TEST_MON_TX1_INT_ANA_SIG    ) |
               (1 << MMWAVELINK_TEST_MON_TX2_INT_ANA_SIG    ) |
               (1 << MMWAVELINK_TEST_MON_INT_RX_SIG         ) |
               (1 << MMWAVELINK_TEST_MON_INT_PMCLKLO_SIG    ) | 
               (1 << MMWAVELINK_TEST_MON_INT_GPADC_SIG      ) |
               (1 << MMWAVELINK_TEST_MON_PLL_CONTROL_VOLT   ) |
               (1 << MMWAVELINK_TEST_MON_DCC_CLOCK_FREQ     ) |
               /*(1 << MMWAVELINK_TEST_MON_RX_IF_SATURATION   ) | */
               /*(1 << MMWAVELINK_TEST_MON_RX_SIG_IMG_BAND    ) | */
               (1 << MMWAVELINK_TEST_MON_RX_MIXER_INP_POWER )),
               
    .ldoScEn = 0
};

rlRxSatMonConf_t rxSatMonCfg_003 =
{
    .profileIndx   = 0U,
    .satMonSel     = 3U,
    .reserved0     = 0U,
    .primarySliceDuration = 5U,
    .numSlices     = CQ_NUM_SLICES,
    .rxChannelMask = 0U,
    .reserved1     = 0U,
    .reserved2     = 0U,
    .reserved3     = 0U,
    .reserved4     = 0U
};

rlSigImgMonConf_t sigImgMonCfg_003 =
{
    .profileIndx = 0U,
    .numSlices   = CQ_NUM_SLICES,
    .timeSliceNumSamples = 8U,
    .reserved0   = 0U,
    .reserved1   = 0U
};

rlFrameCfg_t  frameCfg_003 =
{
    .reserved0 = 0x0,
    .chirpStartIdx = 0,
    .chirpEndIdx = 511U,//This frame uses both chirps
    .numLoops = FRAME_LOOP_COUNT,
    .numFrames = 10,
    .numAdcSamples = FRAME_ADC_SAMPLE_NUM,
    .framePeriodicity = FRAME_PRIODICITY_VAL,
    .triggerSelect = RL_FRAMESTRT_API_TRIGGER,
    .reserved1 = 0x0,
    .frameTriggerDelay = FRAME_TRIGGER_DELAY_VAL,
};


rlRfCalMonTimeUntConf_t calMonTimeUnitConf_003 =
{
    .calibMonTimeUnit = 1,
    .numOfCascadeDev = 1,
    .devId = 1,
    .reserved = 0
};

rlRfCalMonFreqLimitConf_t freqLimit_003 =
{
    .freqLimitLow = 760,
    .freqLimitHigh = 810,
    .reserved0 = 0,
    .reserved1 = 0
};

rlRfInitCalConf_t rfInitCalib_003 =
{
    .calibEnMask = 0x17F0, /* Enable All Init time Calibration */
    .reserved0 = 0,
    .reserved1 = 0,
    .reserved2 = 0,
    .reserved3 = 0
};

rlRunTimeCalibConf_t runTimeCalib_003 =
{
    .oneTimeCalibEnMask = 0x610,  /* Enable All Run time Calibration */
    .periodicCalibEnMask = 0x610, /* Enable All Run time Calibration */
    .calibPeriodicity = 10,
    .reportEn = 1,
    .reserved0 = 0,
    .reserved1 = 0
};

rlAdvFrameCfg_t advFrameCfg_003 =
{
        .frameSeq.numOfSubFrames = 4,
        .frameSeq.forceProfile = 0,
        .frameSeq.loopBackCfg = 0,
        .frameSeq.subFrameTrigger = 0,

        .frameSeq.subFrameCfg[0].forceProfileIdx = 0,
        .frameSeq.subFrameCfg[0].chirpStartIdx = 0,
        .frameSeq.subFrameCfg[0].numOfChirps = 64,
        .frameSeq.subFrameCfg[0].numLoops = 1,
        .frameSeq.subFrameCfg[0].burstPeriodicity = 8000000,
        .frameSeq.subFrameCfg[0].chirpStartIdxOffset = 0,
        .frameSeq.subFrameCfg[0].numOfBurst = 1,
        .frameSeq.subFrameCfg[0].numOfBurstLoops = 1,
        .frameSeq.subFrameCfg[0].reserved0 = 0,
        .frameSeq.subFrameCfg[0].subFramePeriodicity = 8000000,
        .frameSeq.subFrameCfg[0].reserved1 = 0,
        .frameSeq.subFrameCfg[0].reserved2 = 0,
        .frameSeq.subFrameCfg[1].forceProfileIdx = 0,
        .frameSeq.subFrameCfg[1].chirpStartIdx = 0,
        .frameSeq.subFrameCfg[1].numOfChirps = 64,
        .frameSeq.subFrameCfg[1].numLoops = 1,
        .frameSeq.subFrameCfg[1].burstPeriodicity = 8000000,
        .frameSeq.subFrameCfg[1].chirpStartIdxOffset = 0,
        .frameSeq.subFrameCfg[1].numOfBurst = 1,
        .frameSeq.subFrameCfg[1].numOfBurstLoops = 1,
        .frameSeq.subFrameCfg[1].reserved0 = 0,
        .frameSeq.subFrameCfg[1].subFramePeriodicity = 8000000,
        .frameSeq.subFrameCfg[1].reserved1 = 0,
        .frameSeq.subFrameCfg[1].reserved2 = 0,
        .frameSeq.subFrameCfg[2].forceProfileIdx = 0,
        .frameSeq.subFrameCfg[2].chirpStartIdx = 0,
        .frameSeq.subFrameCfg[2].numOfChirps = 64,
        .frameSeq.subFrameCfg[2].numLoops = 1,
        .frameSeq.subFrameCfg[2].burstPeriodicity = 8000000,
        .frameSeq.subFrameCfg[2].chirpStartIdxOffset = 0,
        .frameSeq.subFrameCfg[2].numOfBurst = 1,
        .frameSeq.subFrameCfg[2].numOfBurstLoops = 1,
        .frameSeq.subFrameCfg[2].reserved0 = 0,
        .frameSeq.subFrameCfg[2].subFramePeriodicity = 8000000,
        .frameSeq.subFrameCfg[2].reserved1 = 0,
        .frameSeq.subFrameCfg[2].reserved2 = 0,
        .frameSeq.subFrameCfg[3].forceProfileIdx = 0,
        .frameSeq.subFrameCfg[3].chirpStartIdx = 0,
        .frameSeq.subFrameCfg[3].numOfChirps = 64,
        .frameSeq.subFrameCfg[3].numLoops = 1,
        .frameSeq.subFrameCfg[3].burstPeriodicity = 8000000,
        .frameSeq.subFrameCfg[3].chirpStartIdxOffset = 0,
        .frameSeq.subFrameCfg[3].numOfBurst = 1,
        .frameSeq.subFrameCfg[3].numOfBurstLoops = 1,
        .frameSeq.subFrameCfg[3].reserved0 = 0,
        .frameSeq.subFrameCfg[3].subFramePeriodicity = 8000000,
        .frameSeq.subFrameCfg[3].reserved1 = 0,
        .frameSeq.subFrameCfg[3].reserved2 = 0,

        .frameSeq.numFrames = 10,
        .frameSeq.triggerSelect = 1,
        .frameSeq.frameTrigDelay = 0,
        .frameSeq.reserved0 = 0,
        .frameSeq.reserved1 = 0,

};

rlBpmCommonCfg_t bpmCommonCfg_003 =
{
    .mode.b2SrcSel = 0,
    .mode.b1Reserved0 = 0,
    .mode.b13Reserved1 = 0,
    .reserved0 = 0,
    .reserved1 = 0,
    .reserved2 = 0,
    .reserved3 = 0,
    .reserved4 = 0
};

rlBpmChirpCfg_t bpmChirpCfg_003[DFPTEST_MAX_NUM_BPMCHIRPCFG] =
{
    {
        .chirpStartIdx = 0,
        .chirpEndIdx = 0,
        .constBpmVal = 0,
        .reserved = 0x0
    },
    {
        .chirpStartIdx = 1,
        .chirpEndIdx = 1,
        .constBpmVal = 21,
        .reserved = 0x0
    },
    {
        .chirpStartIdx = 2,
        .chirpEndIdx = 2,
        .constBpmVal = 21,
        .reserved = 0x0
    }
};

rlContModeCfg_t contModeCfg_003 =
{
    .startFreqConst = 1435384036,
    .txOutPowerBackoffCode = 0,
    .txPhaseShifter = 0,
    .digOutSampleRate = 10000,
    .hpfCornerFreq1 = 0,
    .hpfCornerFreq2 = 0,
    .rxGain = 30,
    .vcoSelect = 0x0,
    .reserved  = 0x0
};

rlContModeEn_t contModeEn_003 =
{
    .contModeEn = 1,
    .reserved   = 0
};

rlDynPwrSave_t dynPwrSave_003 =
{
    .blkCfg   = 0x7,
    .reserved = 0
};

rlGpAdcCfg_t gpAdcCfg_003 =
{
    .enable = 0x3F,
    .bufferEnable = 0x3F,
    .numOfSamples[0].sampleCnt = 20,
    .numOfSamples[0].settlingTime = 3,
    .numOfSamples[1].sampleCnt = 14,
    .numOfSamples[1].settlingTime = 3,
    .numOfSamples[2].sampleCnt = 14,
    .numOfSamples[2].settlingTime = 3,
    .numOfSamples[3].sampleCnt = 14,
    .numOfSamples[3].settlingTime = 3,
    .numOfSamples[4].sampleCnt = 14,
    .numOfSamples[4].settlingTime = 3,
    .numOfSamples[5].sampleCnt = 14,
    .numOfSamples[5].settlingTime = 3,
    .numOfSamples[6].sampleCnt = 14,
    .numOfSamples[6].settlingTime = 3,
    .numOfSamples[7].sampleCnt = 14,
    .numOfSamples[7].settlingTime = 3,
    .numOfSamples[8].sampleCnt = 14,
    .numOfSamples[8].settlingTime = 3,
    .numOfSamples[9].sampleCnt = 14,
    .numOfSamples[9].settlingTime = 3,
    .numOfSamples[10].sampleCnt = 14,
    .numOfSamples[10].settlingTime = 3,
    .numOfSamples[11].sampleCnt = 14,
    .reserved = 0
};

rlRfLdoBypassCfg_t rfLdoBypassCfg_003 =
{
    .ldoBypassEnable   = 1,
    .supplyMonIrDrop   = 0,
    .ioSupplyIndicator = 0,
};

rlTempMonConf_t tempMonCfg_003 =
{
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .reserved0 = 0,
    .anaTempThreshMin = -10,
    .anaTempThreshMax = 90,
    .digTempThreshMin = -10,
    .digTempThreshMax = 90,
    .tempDiffThresh = 20,
    .reserved1 = 0,
    .reserved2 = 0,
};

rlRxGainPhaseMonConf_t rxGainPhaseMonCfg_003 =
{
    .profileIndx = 0,
    .rfFreqBitMask = HIGHEST_CENTER_LOWEST_RF_FRQ_IN_PROFILES_SWEEP_BW,
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .txSel = 1,
    .rxGainAbsThresh = 500,
    .rxGainMismatchErrThresh = 40,
    .rxGainFlatnessErrThresh = 500,
    .rxGainPhaseMismatchErrThresh = (30 * (1U << 16))/360U,
    .rxGainMismatchOffsetVal[0][0] = 0x1A,
    .rxGainMismatchOffsetVal[0][1] = 0x1A,
    .rxGainMismatchOffsetVal[0][2] = 0x1A,
    .rxGainMismatchOffsetVal[1][0] = 0x1A,
    .rxGainMismatchOffsetVal[1][1] = 0x1A,
    .rxGainMismatchOffsetVal[1][2] = 0x1A,
    .rxGainMismatchOffsetVal[2][0] = 0x1A,
    .rxGainMismatchOffsetVal[2][1] = 0x1A,
    .rxGainMismatchOffsetVal[2][2] = 0x1A,
    .rxGainMismatchOffsetVal[3][0] = 0x1A,
    .rxGainMismatchOffsetVal[3][1] = 0x1A,
    .rxGainMismatchOffsetVal[3][2] = 0x1A,
    .rxGainPhaseMismatchOffsetVal[0][0] = 0x1A,
    .rxGainPhaseMismatchOffsetVal[0][1] = 0x1A,
    .rxGainPhaseMismatchOffsetVal[0][2] = 0x1A,
    .rxGainPhaseMismatchOffsetVal[1][0] = 0x1A,
    .rxGainPhaseMismatchOffsetVal[1][1] = 0x1A,
    .rxGainPhaseMismatchOffsetVal[1][2] = 0x1A,
    .rxGainPhaseMismatchOffsetVal[2][0] = 0x1A,
    .rxGainPhaseMismatchOffsetVal[2][1] = 0x1A,
    .rxGainPhaseMismatchOffsetVal[2][2] = 0x1A,
    .rxGainPhaseMismatchOffsetVal[3][0] = 0x1A,
    .rxGainPhaseMismatchOffsetVal[3][1] = 0x1A,
    .rxGainPhaseMismatchOffsetVal[3][2] = 0x1A,
    .reserved0 = 0,
    .reserved1 = 0,
};

rlRxNoiseMonConf_t rxNoiseMonCfg_003 =
{
    .profileIndx = 0,//profileCfg.profileId,
    .rfFreqBitMask = HIGHEST_CENTER_LOWEST_RF_FRQ_IN_PROFILES_SWEEP_BW,
    .reserved0 = 0x0,
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .reserved1 = 0x0,
    .noiseThresh = 350,
    .reserved2 = 0x0,
};

rlRxIfStageMonConf_t monRxIfStageCfg_003 =
{
    .profileIndx = 1,
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .reserved0 = 0,
    .reserved1 = 0,
    .hpfCutoffErrThresh = 17,
    .lpfCutoffErrThresh = 100,
    .ifaGainErrThresh = 40,
    .reserved2 = 0,
};

rlTxPowMonConf_t tx0PowMonCfg_003 =
{
    .profileIndx = 0x1,
    .rfFreqBitMask = HIGHEST_CENTER_LOWEST_RF_FRQ_IN_PROFILES_SWEEP_BW,
    .reserved0 = 0x0,
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .reserved1 = 0x0,
    .txPowAbsErrThresh = 35,
    .txPowFlatnessErrThresh = 35,
    .reserved2 = 0x0,
    .reserved3 = 0x0,
};

rlTxPowMonConf_t tx1PowMonCfg_003 =
{
    .profileIndx = 0x0,
    .rfFreqBitMask = HIGHEST_CENTER_LOWEST_RF_FRQ_IN_PROFILES_SWEEP_BW,
    .reserved0 = 0x0,
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .reserved1 = 0x0,
    .txPowAbsErrThresh = 35,
    .txPowFlatnessErrThresh = 35,
    .reserved2 = 0x0,
    .reserved3 = 0x0,
};

rlTxPowMonConf_t tx2PowMonCfg_003 =
{
    .profileIndx = 0x1,
    .rfFreqBitMask = HIGHEST_CENTER_LOWEST_RF_FRQ_IN_PROFILES_SWEEP_BW,
    .reserved0 = 0x0,
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .reserved1 = 0x0,
    .txPowAbsErrThresh = 35,
    .txPowFlatnessErrThresh = 35,
    .reserved2 = 0x0,
    .reserved3 = 0x0,
};

rlAllTxPowMonConf_t allTxPowMonCfg_003 =
{
    .tx0PowrMonCfg = &tx0PowMonCfg_003,
    .tx1PowrMonCfg = &tx1PowMonCfg_003,
    .tx2PowrMonCfg = &tx2PowMonCfg_003,
};

rlTxBallbreakMonConf_t tx0BallBreakMonCfg_003 =
{
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .reserved0 = 0x0,
    .txReflCoeffMagThresh = -70,
    .reserved1 = 0x0,
    .reserved2 = 0x0,
};

rlTxBallbreakMonConf_t tx1BallBreakMonCfg_003 =
{
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .reserved0 = 0x0,
    .txReflCoeffMagThresh = -70,
    .reserved1 = 0x0,
    .reserved2 = 0x0,
};

rlTxBallbreakMonConf_t tx2BallBreakMonCfg_003 =
{
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .reserved0 = 0x0,
    .txReflCoeffMagThresh = -70,
    .reserved1 = 0x0,
    .reserved2 = 0x0,
};

rlAllTxBallBreakMonCfg_t allTxBallbreakMonCfg_003 =
{
    .tx0BallBrkMonCfg = &tx0BallBreakMonCfg_003,
    .tx1BallBrkMonCfg = &tx1BallBreakMonCfg_003,
    .tx2BallBrkMonCfg = &tx2BallBreakMonCfg_003,
};

rlTxGainPhaseMismatchMonConf_t txGainPhMisMatchMonCfg_003 =
{
    .profileIndx = 0x0,
    .rfFreqBitMask = HIGHEST_CENTER_LOWEST_RF_FRQ_IN_PROFILES_SWEEP_BW,
    .txEn = 0x7,
    .rxEn = 0xF,
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .reserved0  = 0x0,
    .txGainMismatchThresh = 200,
    .txPhaseMismatchThresh = (60 * (1 << 16))/360 ,
    .txGainMismatchOffsetVal[0][0] = 0x0,
    .txGainMismatchOffsetVal[0][1] = 0x0,
    .txGainMismatchOffsetVal[0][2] = 0x0,
    .txGainMismatchOffsetVal[1][0] = 0x0,
    .txGainMismatchOffsetVal[1][1] = 0x0,
    .txGainMismatchOffsetVal[1][2] = 0x0,
    .txGainMismatchOffsetVal[2][0] = 0x0,
    .txGainMismatchOffsetVal[2][1] = 0x0,
    .txGainMismatchOffsetVal[2][2] = 0x0,
    .txPhaseMismatchOffsetVal[0][0] = 0x0,
    .txPhaseMismatchOffsetVal[0][1] = 0x0,
    .txPhaseMismatchOffsetVal[0][2] = 0x0,
    .txPhaseMismatchOffsetVal[1][0] = 0x0,
    .txPhaseMismatchOffsetVal[1][1] = 0x0,
    .txPhaseMismatchOffsetVal[1][2] = 0x0,
    .txPhaseMismatchOffsetVal[2][0] = 0x0,
    .txPhaseMismatchOffsetVal[2][1] = 0x0,
    .txPhaseMismatchOffsetVal[2][2] = 0x0,
    .reserved1 = 0x0,
    .reserved2 = 0x0,
};

rlTxBpmMonConf_t tx0BpmMonCfg_003 =
{
    .profileIndx = 0x0,
    .phaseShifterMonCnfg = 0xC2,
    .phaseShifterMon1 = 0x06,
    .phaseShifterMon2 = 0x06,
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .rxEn = 0x1,
    .txBpmPhaseErrThresh = 0x1555,
    .txBpmAmplErrThresh = 30,
    .phaseShifterThreshMax = 40,
    .phaseShifterThreshMin = 0,
    .reserved = 0x0,
};

rlTxBpmMonConf_t tx1BpmMonCfg_003 =
{
    .profileIndx = 0x0,
    .phaseShifterMonCnfg = 0xC2,
    .phaseShifterMon1 = 0x06,
    .phaseShifterMon2 = 0x06,
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .rxEn = 0x1,
    .txBpmPhaseErrThresh = 0x1555,
    .txBpmAmplErrThresh = 30,
    .phaseShifterThreshMax = 40,
    .phaseShifterThreshMin = 0,
    .reserved = 0x0,
};

rlTxBpmMonConf_t tx2BpmMonCfg_003 =
{
    .profileIndx = 0x0,
    .phaseShifterMonCnfg = 0xC2,
    .phaseShifterMon1 = 0x06,
    .phaseShifterMon2 = 0x06,
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .rxEn = 0x1,
    .txBpmPhaseErrThresh = 0x1555,
    .txBpmAmplErrThresh = 30,
    .phaseShifterThreshMax = 40,
    .phaseShifterThreshMin = 0,
    .reserved = 0x0,
};

rlAllTxBpmMonConf_t allTxBpmMonCfg_003 =
{
    .tx0BpmMonCfg = &tx0BpmMonCfg_003,
    .tx1BpmMonCfg = &tx1BpmMonCfg_003,
    .tx2BpmMonCfg = &tx2BpmMonCfg_003,
};

rlSynthFreqMonConf_t synthFreqMonCfg_003 =
{
    .profileIndx = 1,
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .freqErrThresh = 2000,
    .monStartTime = 10,
    .reserved0 = 0,
    .reserved1 = 0,
    .reserved2 = 0,
};

rlExtAnaSignalsMonConf_t extAnaSigMonCfg_003 =
{
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .reserved0 = 0,
    .signalInpEnables = 0x3F,
    .signalBuffEnables = 0x1F,
    .signalSettlingTime[0] = 10,
    .signalSettlingTime[1] = 10,
    .signalSettlingTime[2] = 10,
    .signalSettlingTime[3] = 10,
    .signalSettlingTime[4] = 10,
    .signalSettlingTime[5] = 10,
    .signalThresh[0] = 0,
    .signalThresh[1] = 0,
    .signalThresh[2] = 0,
    .signalThresh[3] = 0,
    .signalThresh[4] = 0,
    .signalThresh[5] = 0,
    .signalThresh[6] = 200,
    .signalThresh[7] = 200,
    .signalThresh[8] = 200,
    .signalThresh[9] = 200,
    .signalThresh[10] = 200,
    .signalThresh[11] = 200,
    .reserved1 = 0,
    .reserved2 = 0,
    .reserved3 = 0,
};

rlTxIntAnaSignalsMonConf_t tx0IntAnaSigMonCfg_003 =
{
    .profileIndx = 1,
    .reportMode = MON_REPORT_MODE_PERIODIC_WITH_THRESHOLD_CHECK,/*mode zero not allowed for this monitor*/
    .reserved0 = 0,
    .reserved1 = 0,
};

rlTxIntAnaSignalsMonConf_t tx1IntAnaSigMonCfg_003 =
{
    .profileIndx = 1,
    .reportMode = MON_REPORT_MODE_PERIODIC_WITH_THRESHOLD_CHECK,/*mode zero not allowed for this monitor*/
    .reserved0 = 0,
    .reserved1 = 0,
};

rlTxIntAnaSignalsMonConf_t tx2IntAnaSigMonCfg_003 =
{
    .profileIndx = 0,
    .reportMode = MON_REPORT_MODE_PERIODIC_WITH_THRESHOLD_CHECK,/*mode zero not allowed for this monitor*/
    .reserved0 = 0,
    .reserved1 = 0,
};

rlAllTxIntAnaSignalsMonConf_t allTxanaSigMonCfg_003 =
{
    .tx0IntAnaSgnlMonCfg = &tx0IntAnaSigMonCfg_003,
    .tx1IntAnaSgnlMonCfg = &tx1IntAnaSigMonCfg_003,
    .tx2IntAnaSgnlMonCfg = &tx2IntAnaSigMonCfg_003,
};

rlRxIntAnaSignalsMonConf_t rxIntAnaSigMonCfg_003 =
{
    .profileIndx = 1,
    .reportMode = MON_REPORT_MODE_PERIODIC_WITH_THRESHOLD_CHECK,/*mode zero not allowed for this monitor*/
    .reserved0 = 0,
    .reserved1 = 0,
};

rlPmClkLoIntAnaSignalsMonConf_t pmClkLoIntAnaSigMonCfg_003 =
{
    .profileIndx = 0,
    .reportMode = MON_REPORT_MODE_PERIODIC_WITH_THRESHOLD_CHECK,/*mode zero not allowed for this monitor*/
    .sync20GSigSel = 1,
    .sync20GMinThresh = 0,
    .sync20GMaxThresh = 0xFF,
    .reserved0 = 0,
    .reserved1 = 0,
};

rlGpadcIntAnaSignalsMonConf_t gpadcIntAnaSigMonCfg_003 =
{
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .reserved0 = 0,
    .reserved1 = 0,
    .reserved2 = 0,
};

rlPllContrVoltMonConf_t pllConVoltMonCfg_003 =
{
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .reserved0 = 0,
    .signalEnables = 7,
    .reserved1 = 0,
};

rlDualClkCompMonConf_t dualClkCompMonCfg_003 =
{
    .reportMode = 0,
    .reserved0 = 10,
    .dccPairEnables = 63,
    .reserved1 = 0,
};

rlRxMixInPwrMonConf_t rxMixInpwrMonCfg_003 =
{
    .profileIndx = 0,
    .reportMode = MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK,
    .txEnable = 3,
    .reserved0 = 0,
    .thresholds = 0x2100,
    .reserved1 = 0,
    .reserved2 = 0,

};

rlRfProgFiltConf_t progFiltCfg_003 =
{
    .profileId = 0,
    .coeffStartIdx = 0,
    .progFiltLen = 14,
    .progFiltFreqShift = 100,
};

rlRfProgFiltCoeff_t progFiltCoef_003 =
{
    .coeffArray[0] = -876,
    .coeffArray[1] = -272,
    .coeffArray[2] = 1826,
    .coeffArray[3] = -395,
    .coeffArray[4] = -3672,
    .coeffArray[5] = 3336,
    .coeffArray[6] = 15976,
    .coeffArray[7] = 15976,
    .coeffArray[8] = 3336,
    .coeffArray[9] = -3672,
    .coeffArray[10] = -395,
    .coeffArray[11] = 1826,
    .coeffArray[12] = -272,
    .coeffArray[13] = -876,
};

rlSubFrameStartCfg_t subFrameTrigCfg_003 =
{
    .startCmd = 1,
    .reserved = 0,
};

rlRfMiscConf_t miscCfg_003 = 
{
    .miscCtl  = 1,
    .reserved = 0,
};

rlRfPhaseShiftCfg_t phaseShiftCfg_003[DFPTEST_MAX_NUM_PHASESHCFG] = 
{
    {
        .chirpStartIdx = 0,
        .chirpEndIdx   = 255,
        .tx0PhaseShift = 42,
        .tx1PhaseShift = 62,
        .tx2PhaseShift = 15,
        .reserved      = 0
    },
    {
        .chirpStartIdx = 256,
        .chirpEndIdx   = 511,
        .tx0PhaseShift = 63,
        .tx1PhaseShift = 50,
        .tx2PhaseShift = 25,
        .reserved      = 0
    },
};

rlDynPerChirpPhShftCfg_t dynPhaseShiftCfg_003[DFPTEST_MAX_NUM_DYNPHASESHCFG] = 
{
    {
        .reserved     = 0,
        .chirpSegSel  = 0,
        .phShiftPerTx = {{47, 1,  2},  {3,  4,  5},
                         {6,  7,  8},  {9,  10, 49},
                         {12, 13, 14}, {15, 16, 17},
                         {18, 48, 20}, {21, 22, 23},
                         {24, 25, 26}, {27, 28, 29},
                         {30, 31, 32}, {33, 34, 35},
                         {51, 37, 38}, {39, 40, 41},
                         {42, 42, 43}, {50, 45, 46}},
        .programMode  = 0
    },
    {
        .reserved     = 0,
        .chirpSegSel  = 1,
        .phShiftPerTx = {{0,  1,  2},  {3,  4,  56},
                         {6,  7,  8},  {9,  10, 11},
                         {12, 13, 14}, {15, 16, 17},
                         {18, 54, 20}, {21, 53, 23},
                         {24, 25, 26}, {27, 28, 29},
                         {57, 31, 32}, {33, 34, 35},
                         {52, 37, 38}, {39, 40, 41},
                         {42, 42, 43}, {44, 45, 46}},
        .programMode  = 0
    },
    {
        .reserved     = 0,
        .chirpSegSel  = 2,
        .phShiftPerTx = {{0, 61,  2},  {3,  4,  5},
                         {6,  7,  8},  {9,  10, 11},
                         {12, 13, 59}, {15, 16, 17},
                         {18, 19, 20}, {21, 22, 23},
                         {24, 25, 26}, {58, 28, 29},
                         {60, 31, 32}, {33, 34, 35},
                         {36, 37, 38}, {39, 40, 41},
                         {42, 42, 43}, {44, 62, 46}},
        .programMode  = 0
    },
    {
        .reserved     = 0,
        .chirpSegSel  = 3,
        .phShiftPerTx = {{50, 1,  2},  {3,  4,  5},
                         {6,  7,  8},  {49, 10, 11},
                         {12, 13, 14}, {15, 16, 48},
                         {47, 19, 20}, {21, 22, 23},
                         {24, 25, 26}, {27, 28, 29},
                         {30, 31, 32}, {33, 34, 35},
                         {36, 63, 38}, {39, 40, 41},
                         {42, 42, 43}, {44, 45, 46}},
        .programMode  = 0
    },
    {
        .reserved     = 0,
        .chirpSegSel  = 4,
        .phShiftPerTx = {{0, 51,  2},  {3,  4,  5},
                         {6,  7,  8},  {9,  10, 11},
                         {12, 13, 14}, {15, 16, 17},
                         {18, 19, 20}, {21, 22, 23},
                         {24, 25, 26}, {27, 28, 29},
                         {30, 31, 52}, {53, 34, 35},
                         {36, 37, 38}, {39, 40, 41},
                         {42, 42, 43}, {44, 45, 46}},
        .programMode  = 0
    },
    {
        .reserved     = 0,
        .chirpSegSel  = 5,
        .phShiftPerTx = {{0,  1,  2},  {3,  4,  55},
                         {6,  7,  8},  {9,  10, 11},
                         {12, 13, 54}, {15, 16, 17},
                         {18, 19, 20}, {21, 22, 23},
                         {24, 25, 26}, {27, 28, 29},
                         {30, 31, 32}, {33, 34, 35},
                         {36, 37, 38}, {39, 40, 41},
                         {42, 42, 43}, {44, 45, 46}},
        .programMode  = 0
    },
    {
        .reserved     = 0,
        .chirpSegSel  = 6,
        .phShiftPerTx = {{0,  1,  2}, {3,  4,  5},
                         {6,  7,  8}, {9,  10, 11},
                         {12, 13, 14}, {15, 16, 17},
                         {18, 19, 20}, {21, 22, 23},
                         {24, 25, 26}, {27, 28, 29},
                         {30, 31, 32}, {33, 34, 35},
                         {36, 37, 38}, {39, 40, 41},
                         {42, 42, 43}, {44, 45, 46}},
        .programMode  = 0
    },
    {
        .reserved     = 0,
        .chirpSegSel  = 7,
        .phShiftPerTx = {{0,  1,  2},  {3,  4,  5},
                         {6,  7,  8},  {9,  10, 11},
                         {56, 13, 14}, {15, 16, 17},
                         {18, 19, 20}, {21, 22, 23},
                         {24, 25, 26}, {57, 58, 29},
                         {30, 31, 32}, {33, 34, 35},
                         {36, 37, 38}, {39, 40, 41},
                         {42, 42, 43}, {44, 45, 46}},
        .programMode  = 0
    },
    {
        .reserved     = 0,
        .chirpSegSel  = 8,
        .phShiftPerTx = {{47, 48, 49}, {50, 51, 52},
                         {53, 54, 55}, {56, 57, 58},
                         {59, 60, 61}, {62, 63, 17},
                         {18, 19, 20}, {21, 22, 23},
                         {24, 25, 26}, {27, 28, 29},
                         {30, 31, 32}, {33, 34, 35},
                         {36, 37, 38}, {39, 40, 41},
                         {42, 42, 43}, {44, 45, 46}},
        .programMode  = 0
    },
    {
        .reserved     = 0,
        .chirpSegSel  = 9,
        .phShiftPerTx = {{0,  1,  2},  {3,  4,  5},
                         {6,  7,  8},  {9,  10, 11},
                         {12, 13, 14}, {15, 16, 17},
                         {18, 19, 20}, {21, 22, 23},
                         {24, 25, 26}, {27, 28, 29},
                         {30, 31, 32}, {33, 34, 35},
                         {36, 37, 38}, {39, 40, 41},
                         {42, 42, 43}, {44, 45, 46}},
        .programMode  = 0
    },
};

rlInterRxGainPhConf_t interRxGainPhCfg_003 = 
{
    .profileIndx     = 0,
    .reserved0       = 0,
    .reserved1       = 1,
    .digRxGain[0]    = 100,
    .digRxGain[1]    = 20,
    .digRxGain[2]    = 75,
    .digRxGain[3]    = 105,
    .digRxPhShift[0] = 25102,
    .digRxPhShift[1] = 102,
    .digRxPhShift[2] = 65535,
    .digRxPhShift[3] = 55201,
    .reserved2       = 0,
    .reserved3       = 0,
};

rlTestSource_t testSourceCfg_003 = 
{
    .testObj[0]      = {102, 2, 5698, 5, 8, 0, 100, 1256, 2589, 225, 2489, 12256, 112},
    .testObj[1]      = {10, 5, 0, 5, 5, 5, 255, 0, 216, 2251, 341, 556, 5112},
    .rxAntPos[0]     = {15, 15},
    .rxAntPos[1]     = {15, 15},
    .rxAntPos[2]     = {15, 15},
    .rxAntPos[3]     = {15, 15},
    .reserved0       = 0,
    .reserved1       = 0,
};

rlTestSourceEnable_t testSourceEn_003 = 
{
    .tsEnable  = 1,
    .reserved  = 0,
};

rlRxGainTempLutReadReq_t rxGainTempLutReadCfg_003 = 
{
    .profileIndx   = 0,
    .reserved0     = 0,
    .reserved1     = 0,
};

rlTxGainTempLutReadReq_t txGainTempLutReadCfg_003 = 
{
    .profileIndx   = 0,
    .reserved0     = 0,
    .reserved1     = 0,
};

void dfpTestLoadCfg_003(void)
{
    memcpy((void*)&gTestStartStopCfg     , (void*)&gTestStartStopCfg_003      , sizeof(gTestStartStopCfg));
    memcpy((void*)&gTestMiscCfg          , (void*)&gTestMiscCfg_003           , sizeof(gTestMiscCfg));
    memcpy((void*)&chCfg                 , (void*)&chCfg_003                  , sizeof(chCfg          ));
    memcpy((void*)&adcOutCfgArgs         , (void*)&adcOutCfgArgs_003          , sizeof(adcOutCfgArgs  ));
    memcpy((void*)&lowPowerModeCfg       , (void*)&lowPowerModeCfg_003        , sizeof(lowPowerModeCfg));
    memcpy((void*)&deviceHsiClk          , (void*)&deviceHsiClk_003           , sizeof(deviceHsiClk   ));
    memcpy((void*)&profileCfg[0]         , (void*)&profileCfg_003[0]          , sizeof(rlProfileCfg_t)*DFPTEST_MAX_NUM_PROFCFG);
    memcpy((void*)&chirpCfg[0]           , (void*)&chirpCfg_003[0]            , sizeof(rlChirpCfg_t)*DFPTEST_MAX_NUM_CHIRPCFG);
    memcpy((void*)&monDigEnables         , (void*)&monDigEnables_003          , sizeof(monDigEnables     ));
    memcpy((void*)&monDigPeriodicCfg     , (void*)&monDigPeriodicCfg_003      , sizeof(monDigPeriodicCfg     ));
    memcpy((void*)&monAnaEnables         , (void*)&monAnaEnables_003          , sizeof(monAnaEnables     ));
    memcpy((void*)&rxSatMonCfg           , (void*)&rxSatMonCfg_003            , sizeof(rxSatMonCfg       ));
    memcpy((void*)&sigImgMonCfg          , (void*)&sigImgMonCfg_003           , sizeof(sigImgMonCfg      ));
    memcpy((void*)&frameCfg              , (void*)&frameCfg_003               , sizeof(frameCfg          ));
    memcpy((void*)&calMonTimeUnitConf    , (void*)&calMonTimeUnitConf_003     , sizeof(calMonTimeUnitConf));
    memcpy((void*)&freqLimit             , (void*)&freqLimit_003              , sizeof(freqLimit         ));
    memcpy((void*)&rfInitCalib           , (void*)&rfInitCalib_003            , sizeof(rfInitCalib       ));
    memcpy((void*)&runTimeCalib          , (void*)&runTimeCalib_003           , sizeof(runTimeCalib      ));
    memcpy((void*)&advFrameCfg           , (void*)&advFrameCfg_003            , sizeof(advFrameCfg       ));
    memcpy((void*)&bpmCommonCfg          , (void*)&bpmCommonCfg_003           , sizeof(bpmCommonCfg      ));
    memcpy((void*)&bpmChirpCfg[0]        , (void*)&bpmChirpCfg_003[0]         , sizeof(rlBpmChirpCfg_t)*DFPTEST_MAX_NUM_BPMCHIRPCFG);   
    memcpy((void*)&contModeCfg           , (void*)& contModeCfg_003           , sizeof(contModeCfg           ));
    memcpy((void*)&contModeEn            , (void*)& contModeEn_003            , sizeof(contModeEn            ));
    memcpy((void*)&dynPwrSave            , (void*)& dynPwrSave_003            , sizeof(dynPwrSave            ));
    memcpy((void*)&gpAdcCfg              , (void*)& gpAdcCfg_003              , sizeof(gpAdcCfg              ));
    memcpy((void*)&rfLdoBypassCfg        , (void*)& rfLdoBypassCfg_003        , sizeof(rfLdoBypassCfg        ));
    memcpy((void*)&tempMonCfg            , (void*)& tempMonCfg_003            , sizeof(tempMonCfg            ));
    memcpy((void*)&rxGainPhaseMonCfg     , (void*)& rxGainPhaseMonCfg_003     , sizeof(rxGainPhaseMonCfg     ));
    memcpy((void*)&rxNoiseMonCfg         , (void*)& rxNoiseMonCfg_003         , sizeof(rxNoiseMonCfg         ));
    memcpy((void*)&monRxIfStageCfg       , (void*)& monRxIfStageCfg_003       , sizeof(monRxIfStageCfg       ));
    memcpy((void*)&tx0PowMonCfg          , (void*)& tx0PowMonCfg_003          , sizeof(tx0PowMonCfg          ));
    memcpy((void*)&tx1PowMonCfg          , (void*)& tx1PowMonCfg_003          , sizeof(tx1PowMonCfg          ));
    memcpy((void*)&tx2PowMonCfg          , (void*)& tx2PowMonCfg_003          , sizeof(tx2PowMonCfg          ));
    memcpy((void*)&allTxPowMonCfg        , (void*)& allTxPowMonCfg_003        , sizeof(allTxPowMonCfg        ));
    memcpy((void*)&tx0BallBreakMonCfg    , (void*)& tx0BallBreakMonCfg_003    , sizeof(tx0BallBreakMonCfg    ));
    memcpy((void*)&tx1BallBreakMonCfg    , (void*)& tx1BallBreakMonCfg_003    , sizeof(tx1BallBreakMonCfg    ));
    memcpy((void*)&tx2BallBreakMonCfg    , (void*)& tx2BallBreakMonCfg_003    , sizeof(tx2BallBreakMonCfg    ));
    memcpy((void*)&allTxBallbreakMonCfg  , (void*)& allTxBallbreakMonCfg_003  , sizeof(allTxBallbreakMonCfg  ));
    memcpy((void*)&txGainPhMisMatchMonCfg, (void*)& txGainPhMisMatchMonCfg_003, sizeof(txGainPhMisMatchMonCfg));
    memcpy((void*)&tx0BpmMonCfg          , (void*)& tx0BpmMonCfg_003          , sizeof(tx0BpmMonCfg          ));
    memcpy((void*)&tx1BpmMonCfg          , (void*)& tx1BpmMonCfg_003          , sizeof(tx1BpmMonCfg          ));
    memcpy((void*)&tx2BpmMonCfg          , (void*)& tx2BpmMonCfg_003          , sizeof(tx2BpmMonCfg          ));
    memcpy((void*)&allTxBpmMonCfg        , (void*)& allTxBpmMonCfg_003        , sizeof(allTxBpmMonCfg        ));
    memcpy((void*)&synthFreqMonCfg       , (void*)& synthFreqMonCfg_003       , sizeof(synthFreqMonCfg       ));
    memcpy((void*)&extAnaSigMonCfg       , (void*)& extAnaSigMonCfg_003       , sizeof(extAnaSigMonCfg       ));
    memcpy((void*)&tx0IntAnaSigMonCfg    , (void*)& tx0IntAnaSigMonCfg_003    , sizeof(tx0IntAnaSigMonCfg    ));
    memcpy((void*)&tx1IntAnaSigMonCfg    , (void*)& tx1IntAnaSigMonCfg_003    , sizeof(tx1IntAnaSigMonCfg    ));
    memcpy((void*)&tx2IntAnaSigMonCfg    , (void*)& tx2IntAnaSigMonCfg_003    , sizeof(tx2IntAnaSigMonCfg    ));
    memcpy((void*)&allTxanaSigMonCfg     , (void*)& allTxanaSigMonCfg_003     , sizeof(allTxanaSigMonCfg     ));
    memcpy((void*)&rxIntAnaSigMonCfg     , (void*)& rxIntAnaSigMonCfg_003     , sizeof(rxIntAnaSigMonCfg     ));
    memcpy((void*)&pmClkLoIntAnaSigMonCfg, (void*)& pmClkLoIntAnaSigMonCfg_003, sizeof(pmClkLoIntAnaSigMonCfg));
    memcpy((void*)&gpadcIntAnaSigMonCfg  , (void*)& gpadcIntAnaSigMonCfg_003  , sizeof(gpadcIntAnaSigMonCfg  ));
    memcpy((void*)&pllConVoltMonCfg      , (void*)& pllConVoltMonCfg_003      , sizeof(pllConVoltMonCfg      ));
    memcpy((void*)&dualClkCompMonCfg     , (void*)& dualClkCompMonCfg_003     , sizeof(dualClkCompMonCfg     ));
    memcpy((void*)&rxMixInpwrMonCfg      , (void*)& rxMixInpwrMonCfg_003      , sizeof(rxMixInpwrMonCfg      ));
    memcpy((void*)&progFiltCfg           , (void*)& progFiltCfg_003           , sizeof(progFiltCfg           ));
    memcpy((void*)&progFiltCoef          , (void*)& progFiltCoef_003          , sizeof(progFiltCoef          ));
    memcpy((void*)&subFrameTrigCfg       , (void*)& subFrameTrigCfg_003       , sizeof(subFrameTrigCfg       ));
    memcpy((void*)&miscCfg               , (void*)& miscCfg_003               , sizeof(miscCfg               ));    
    memcpy((void*)&phaseShiftCfg[0]      , (void*)&phaseShiftCfg_003[0]       , sizeof(rlRfPhaseShiftCfg_t)*DFPTEST_MAX_NUM_PHASESHCFG);
    memcpy((void*)&dynPhaseShiftCfg[0]   , (void*)&dynPhaseShiftCfg_003[0]    , sizeof(rlDynPerChirpPhShftCfg_t)*DFPTEST_MAX_NUM_DYNPHASESHCFG);
    memcpy((void*)&interRxGainPhCfg      , (void*)&interRxGainPhCfg_003       , sizeof(interRxGainPhCfg    ));
    memcpy((void*)&testSourceCfg         , (void*)&testSourceCfg_003          , sizeof(testSourceCfg       ));
    memcpy((void*)&testSourceEn          , (void*)&testSourceEn_003           , sizeof(testSourceEn        ));
    memcpy((void*)&rxGainTempLutReadCfg  , (void*)&rxGainTempLutReadCfg_003   , sizeof(rxGainTempLutReadCfg));
    memcpy((void*)&txGainTempLutReadCfg  , (void*)&txGainTempLutReadCfg_003   , sizeof(txGainTempLutReadCfg));
}

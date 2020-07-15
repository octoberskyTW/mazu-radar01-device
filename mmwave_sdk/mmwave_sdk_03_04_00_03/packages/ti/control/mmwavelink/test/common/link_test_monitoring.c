/*
 *   @file  link_test_monitoring.c
 *
 *   @brief
 *      Implements mmwavelink tests for monitoring and calibration APIs
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

/* BIOS/XDC Include Files. */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/heaps/HeapBuf.h>
#include <ti/sysbios/heaps/HeapMem.h>
#include <ti/sysbios/knl/Event.h>

/* mmWave SDK Include Files: */
#include <ti/common/sys_common.h>
#include <ti/control/mmwavelink/mmwavelink.h>
#include <ti/drivers/crc/crc.h>
#include <ti/control/mmwavelink/include/rl_driver.h>
#include <ti/utils/testlogger/logger.h>
/* ADCBUF Driver: */
#include <ti/drivers/adcbuf/ADCBuf.h>
#include <ti/utils/cycleprofiler/cycle_profiler.h>
#include <ti/control/mmwavelink/test/common/link_testcase_setting.h>
#include <ti/control/mmwavelink/test/common/link_test.h>
#include <ti/control/mmwavelink/test/common/link_test_monitoring.h>
#include <ti/control/mmwavelink/test/common/link_testcase_config.h>


extern bool gLinkEnableTx2;
extern uint32_t gRunTimeCalibStatus;
extern volatile uint32_t gLinkFrameCnt;
extern volatile uint32_t gLinkChirpCnt;

/**************************************************************************
 *************************** Global Variables *****************************
 **************************************************************************/
uint16_t monAeCnt [MMWAVELINK_TEST_MAX_NUM_MON] = { 0 };
uint16_t monFailRepCheck [MMWAVELINK_TEST_MAX_NUM_MON] = { 0 };
uint32_t anaMonEn = 0;
monitoringDataAe_t gMonDataAeStrct = { 0 };
uint32_t monTestCase;
bool     monTestPassFlag;

/**************************************************************************
 ************************** mmWave Link Functions *************************
 **************************************************************************/
/**
 *  @b Description
 *  @n
 *      Initialize monitoring report counters.
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_monitorReportCountInit (void)
{
    int32_t i;
    /* Reset Monitoring report counts & error report counts */
    for(i = 0; i < MMWAVELINK_TEST_MAX_NUM_MON; i++)
    {
        monFailRepCheck[i] = 0;
        monAeCnt[i] = 0;
    }
}

/**
 *  @b Description
 *  @n
 *      The function Sets the consolidated configuration of all analog monitoring excluding
 *      CQ & CP monitoring.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfAnaMonConfig (bool useInputMask, rlUInt32_t inputMask)
{
    int32_t  retVal;
    rlMonAnaEnables_t data;
    
    if(useInputMask)
    {
        data.enMask = inputMask;
    }
    else
    {
        /* Each bit(0-31) represents different analog monitor enable configuration */
        data.enMask = (1 << 0)   | \
            (1 << 1)   | \
            (1 << 2)   | \
            (1 << 3)   | \
            (1 << 4)   | \
            (1 << 5)   | \
            (0 << 6)   | \
            (1 << 7)   | \
            (1 << 8)   | \
            (0 << 9)   | \
            (1 << 10)  | \
            (1 << 11)  | \
            (1 << 12)  | \
            (0 << 13)  | \
            (1 << 14)  | \
            (1 << 15)  | \
            (1 << 16)  | \
            (1 << 17)  | \
            (0 << 18)  | \
            (1 << 19)  | \
            (1 << 20)  | \
            (1 << 21)  | \
            (1 << 22)  | \
            (1 << 23)  | \
            (0 << 24)  | \
            (0 << 25)  | \
            (1 << 26)  | \
            (0 << 27)  | \
            (0 << 28)  | \
            (0 << 29)  | \
            (0 << 30)  | \
            (0 << 31);
            
        if (gLinkEnableTx2 == true)
        {
            /* Enable TX2 monitors for AWR1843 */
            data.enMask |= (1 << 6)  | \
                           (1 << 9)  | \
                           (1 << 13) | \
                           (1 << 18);
        }
    }
        
    data.ldoScEn = 0;
    
    anaMonEn = data.enMask;
    
    /* Analog monitors enable */
    retVal = rlRfAnaMonConfig(RL_DEVICE_MAP_INTERNAL_BSS,&data);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfAnaMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished rlRfAnaMonConfig configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to Rx Mixer InPower monitoring.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_RxMixerInPwrConfig (void)
{
    int32_t         retVal;

    /* Set RX Mixer input power monitor configuration */
    retVal = rlRfRxMixerInPwrConfig(RL_DEVICE_MAP_INTERNAL_BSS,(rlRxMixInPwrMonConf_t*)&rxMixInpwrMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfRxMixerInPwrConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished Rx Mixer InPower configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to temperature monitoring.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfTempMonConfig (void)
{
    int32_t         retVal;
    /* Set Temperature monitor configuration */
    retVal = rlRfTempMonConfig(RL_DEVICE_MAP_INTERNAL_BSS,(rlTempMonConf_t*)&tempMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfTempMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished temperature monitoring configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets RX gain and phase monitoring config to device.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfRxGainPhaMonConfig (void)
{
    int32_t         retVal;
    /* Set RX Gain Phase monitor configuration */
    retVal = rlRfRxGainPhMonConfig(RL_DEVICE_MAP_INTERNAL_BSS,(rlRxGainPhaseMonConf_t*)&rxGainPhaseMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfRxGainPhMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished RX gain and phase monitoring configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to RX noise monitoring.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfRxNoiseMonConfig (void)
{
    int32_t         retVal;
    /* Set RX Noise monitor configuration */
    retVal = rlRfRxNoiseMonConfig(RL_DEVICE_MAP_INTERNAL_BSS,(rlRxNoiseMonConf_t*)&rxNoiseMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfRxNoiseMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished RX noise monitoring configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to RX IF filter attenuation monitoring.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfRxIfStageMonConfig (void)
{
    int32_t         retVal;
    /* Set RX IF Stage monitor configuration */
    retVal = rlRfRxIfStageMonConfig(RL_DEVICE_MAP_INTERNAL_BSS,(rlRxIfStageMonConf_t*)&monRxIfStageCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfRxIfStageMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished RX IF filter attenuation monitoring configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to TX power monitoring.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfTxPowMonConfig (void)
{
    int32_t         retVal;
    /* Set TX Power monitor configuration */
    retVal = rlRfTxPowrMonConfig(RL_DEVICE_MAP_INTERNAL_BSS,(rlAllTxPowMonConf_t*)&allTxPowMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfTxPowrMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished information related to TX Power monitor configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to TX ball break detection.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfTxBallbreakMonConfig (void)
{
    int32_t         retVal;
    /* Set TX Ballbreak monitor configuration */
    retVal = rlRfTxBallbreakMonConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlAllTxBallBreakMonCfg_t*)&allTxBallbreakMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfTxBallbreakMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished information related to TX power monitoring configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to TX gain and phase mismatch monitoring.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfTxGainPhaseMismatchMonConfig (void)
{
    int32_t         retVal;
    /* Set TX Gain Phase monitor configuration */
    retVal = rlRfTxGainPhaseMismatchMonConfig(RL_DEVICE_MAP_INTERNAL_BSS,(rlTxGainPhaseMismatchMonConf_t*)&txGainPhMisMatchMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfTxGainPhaseMismatchMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished information related to TX gain and phase mismatch monitoring configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to TX BPM monitoring.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfTxBpmMonConfig (void)
{
    int32_t retVal;
    /* Set TX BPM monitor configuration */
    retVal = rlRfTxBpmMonConfig(RL_DEVICE_MAP_INTERNAL_BSS,(rlAllTxBpmMonConf_t*)&allTxBpmMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfTxBpmMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished information related to TX BPM configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to synthesizer frequency.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfSynthFreqMonConfig (void)
{
    int32_t         retVal;
    /* Set Synth Freq monitor configuration */
    retVal = rlRfSynthFreqMonConfig(RL_DEVICE_MAP_INTERNAL_BSS,(rlSynthFreqMonConf_t*)&synthFreqMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfSynthFreqMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished information related to synthesizer frequency configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to external DC signals monitoring.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfExtAnaSignalsMonConfig (void)
{
    int32_t         retVal;

    /* Set External analog signal monitor configuration */
    retVal = rlRfExtAnaSignalsMonConfig(RL_DEVICE_MAP_INTERNAL_BSS,(rlExtAnaSignalsMonConf_t*)&extAnaSigMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfExtAnaSignalsMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished information related to external DC signals monitoring configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to TX Internal Analog Signals monitoring.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfTxIntAnaSignalMonConfig (void)
{
    int32_t         retVal;

    /* Set TX Internal analog signal monitor configuration */
    retVal = rlRfTxIntAnaSignalsMonConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlAllTxIntAnaSignalsMonConf_t*)&allTxanaSigMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfTxIntAnaSignalsMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished information related to TX Internal Analog Signals configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to RX Internal Analog Signals monitoring.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfRxIntAnaSignalMonConfig (void)
{
    int32_t         retVal;
    rlRxIntAnaSignalsMonConf_t rxIntAnaSgnlMonCfg = {0,2,0,0};

    /* Set RX Internal analog signal monitor configuration */
    retVal = rlRfRxIntAnaSignalsMonConfig(RL_DEVICE_MAP_INTERNAL_BSS, &rxIntAnaSgnlMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfRxIntAnaSignalsMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished information related to RX Internal Analog Signals configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to Power Management, Clock generation and LO distribution.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfPmClkLoIntAnaSignalsMonConfig (void)
{
    int32_t         retVal;
    /* Set PMCLKLO monitor configuration */
    retVal = rlRfPmClkLoIntAnaSignalsMonConfig(RL_DEVICE_MAP_INTERNAL_BSS,(rlPmClkLoIntAnaSignalsMonConf_t*)&pmClkLoIntAnaSigMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfPmClkLoIntAnaSignalsMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished information related to Power Management, Clock generation and LO distributioncon configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to GPADC Internal Analog Signals monitoring.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfGpadcIntAnaSignalsMonConfig (void)
{
    int32_t         retVal;
    /* Set GPADC internal analog signal monitor configuration */
    retVal = rlRfGpadcIntAnaSignalsMonConfig(RL_DEVICE_MAP_INTERNAL_BSS,(rlGpadcIntAnaSignalsMonConf_t*) &gpadcIntAnaSigMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfGpadcIntAnaSignalsMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished information related to GPADC Internal Analog Signals monitoring configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to APLL and Synthesizer's control voltage signals monitoring.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfPllContrlVoltMonConfig (void)
{
    int32_t         retVal;
    /* Set PLL control voltage monitor configuration */
    retVal = rlRfPllContrlVoltMonConfig(RL_DEVICE_MAP_INTERNAL_BSS,(rlPllContrVoltMonConf_t*)&pllConVoltMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfPllContrlVoltMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished information related to APLL and Synthesizer's control voltage signals monitoring configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to the DCC based clock frequency monitoring.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfDualClkCompMonConfig (void)
{
    int32_t         retVal;
    /* Set DCC monitor configuration */
    retVal = rlRfDualClkCompMonConfig(RL_DEVICE_MAP_INTERNAL_BSS,(rlDualClkCompMonConf_t*)&dualClkCompMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfDualClkCompMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished information related to the DCC based clock frequency monitoring configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to  RX saturation detector monitoring.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfRxIfSatMonConfig (void)
{
    int32_t         retVal;

    /* Set RX IF Stage monitor configuration */
    retVal = rlRfRxIfSatMonConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlRxSatMonConf_t*)&rxSatMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfRxIfSatMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished information related to  RX saturation detector monitoring configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets information related to signal and image band energy.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfRxSigImgMonConfig (void)
{
    int32_t         retVal;

    /* Set RX Signal image monitor configuration */
    retVal = rlRfRxSigImgMonConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlSigImgMonConf_t*)&sigImgMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfRxSigImgMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished information related to signal and image band energy configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to Configure digital monitors
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_digMonEnableConfig(bool useInputMask, rlUInt32_t inputMask)
{
    int32_t  retVal;
    rlMonDigEnables_t data = { 0 };
    
    if(useInputMask)
    {
        data.enMask = inputMask;
    }
    else
    {
        /* Each bit(0-31) represents different digital monitor enable configuration */
        data.enMask = (0 << 0)   | \
                      (1 << 1)   | \
                      (0 << 2)   | \
                      (1 << 3)   | \
                      (0 << 4)   | \
                      (0 << 5)   | \
                      (1 << 6)   | \
                      (1 << 7)   | \
                      (1 << 8)   | \
                      (1 << 9)   | \
                      (1 << 10)  | \
                      (1 << 11)  | \
                      (0 << 12)  | \
                      (0 << 13)  | \
                      (0 << 14)  | \
                      (0 << 15)  | \
                      (1 << 16)  | \
                      (1 << 17)  | \
                      (1 << 18)  | \
                      (1 << 19)  | \
                      (1 << 20)  | \
                      (0 << 21)  | \
                      (0 << 22)  | \
                      (0 << 23)  | \
                      (1 << 24)  | \
                      (1 << 25)  | \
                      (1 << 26)  | \
                      (0 << 27)  | \
                      (0 << 28)  | \
                      (0 << 29)  | \
                      (0 << 30)  | \
                      (0 << 31);
    }
    
    data.testMode = 0;
    /* Digital monitoring configuration */
    retVal = rlRfDigMonEnableConfig(RL_DEVICE_MAP_INTERNAL_BSS,&data);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfDigMonEnableConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished rlRfDigMonEnableConfig configurations to BSS\n");
    return 0;
};

int32_t MmwaveLink_rlRfDigMonPeriodicConfig (void)
{
    int32_t         retVal;
    rlDigMonPeriodicConf_t data = {0x0};
    data.reportMode = 0;
    data.periodicEnableMask = 0xD;

    /* Set Digital periodic monitor configuration */
    retVal = rlRfDigMonPeriodicConfig(RL_DEVICE_MAP_INTERNAL_BSS, &data);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfDigMonPeriodicConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished information related to  rlRfDigMonPeriodicConfig monitoring configurations to BSS\n");
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets the consolidated configuration of CQ & CP monitoring If analog monitors
 *      already enabled then function enable analog monitors(those enabled), CQ & CP monitors .
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfAnaMonConfigCq (void)
{
    int32_t  retVal;
    /* Each bit(0-31) represents different analog monitor enable configuration */
    rlMonAnaEnables_t data = { (0 << 0)   | \
                               (0 << 1)   | \
                               (0 << 2)   | \
                               (0 << 3)   | \
                               (0 << 4)   | \
                               (0 << 5)   | \
                               (0 << 6)   | \
                               (0 << 7)   | \
                               (0 << 8)   | \
                               (0 << 9)   | \
                               (0 << 10)  | \
                               (0 << 11)  | \
                               (0 << 12)  | \
                               (0 << 13)  | \
                               (0 << 14)  | \
                               (0 << 15)  | \
                               (0 << 16)  | \
                               (0 << 17)  | \
                               (0 << 18)  | \
                               (0 << 19)  | \
                               (0 << 20)  | \
                               (0 << 21)  | \
                               (0 << 22)  | \
                               (0 << 23)  | \
                               (1 << 24)  | \
                               (1 << 25)  | \
                               (0 << 26)  | \
                               (0 << 27)  | \
                               (0 << 28)  | \
                               (0 << 29)  | \
                               (0 << 30)  | \
                               (0 << 31)
                                ,0x0};
    data.enMask |= anaMonEn;
    anaMonEn = data.enMask;
    /* Set analog monitor enable configuration */
    retVal = rlRfAnaMonConfig(RL_DEVICE_MAP_INTERNAL_BSS,&data);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfAnaMonConfig retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished rlRfAnaMonConfig configurations to BSS\n");
    return 0;
}

int32_t MmwaveLink_CheckMonitoringReport(uint32_t frameCnt)
{
    int32_t failedMonRepCnt = 0;
    System_printf ("----------------------------------------------------\n");
    if(((anaMonEn >> MMWAVELINK_TEST_MON_TEMP) && 1U) == 1U)
    {
        if(monAeCnt[MMWAVELINK_TEST_MON_TEMP] < frameCnt)
        {
            System_printf("Missing: Temp monitor report missed, received %d out of %d \n", monAeCnt[MMWAVELINK_TEST_MON_TEMP],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if(((anaMonEn >> MMWAVELINK_TEST_MON_RX_GAIN_PH) && 1U) == 1U)
    {
        if(monAeCnt[MMWAVELINK_TEST_MON_RX_GAIN_PH] < frameCnt)
        {
            System_printf("Missing: Rx Gain Phase monitor report missed, received %d out of %d \n", monAeCnt[MMWAVELINK_TEST_MON_RX_GAIN_PH],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if(((anaMonEn >> 2U) && 1U) == 1U)
    {
        if(monAeCnt[2] < frameCnt)
        {
            System_printf("Missing: Rx Noise Fig monitor report missed, received %d out of %d \n", monAeCnt[2],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if(((anaMonEn >> 3U) && 1U) == 1U)
    {
        if(monAeCnt[3] < frameCnt)
        {
            System_printf("Missing: If stage monitor report missed, received %d out of %d \n", monAeCnt[3],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if(((anaMonEn >> 4U) && 1U) == 1U)
    {
        if(monAeCnt[4] < frameCnt)
        {
            System_printf("Missing: TX0 pow monitor report missed, received %d out of %d \n", monAeCnt[4],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if(((anaMonEn >> 5U) && 1U) == 1U)
    {
        if(monAeCnt[5] < frameCnt)
        {
            System_printf("Missing: TX1 pow monitor report missed, received %d out of %d \n", monAeCnt[5],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if (gLinkEnableTx2 == true)
    {
        if(((anaMonEn >> 6U) && 1U) == 1U)
        {
            if(monAeCnt[6] < frameCnt)
            {
                System_printf("Missing: TX2 pow monitor report missed, received %d out of %d \n", monAeCnt[6],frameCnt);
                failedMonRepCnt = -1;
            }
        }
    }
    if(((anaMonEn >> 7U) && 1U) == 1U)
    {
        if(monAeCnt[7] < frameCnt)
        {
            System_printf("Missing: TX0 ball break monitor report missed, received %d out of %d \n", monAeCnt[7],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if(((anaMonEn >> 8U) && 1U) == 1U)
    {
        if(monAeCnt[8] < frameCnt)
        {
            System_printf("Missing: TX1 ball break monitor report missed, received %d out of %d \n", monAeCnt[8],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if (gLinkEnableTx2 == true)
    {
        if(((anaMonEn >> 9U) && 1U) == 1U)
        {
            if(monAeCnt[9] < frameCnt)
            {
                System_printf("Missing: TX2 ball break monitor report missed, received %d out of %d \n", monAeCnt[9],frameCnt);
                failedMonRepCnt = -1;
            }
        }
    }
    if(((anaMonEn >> 10U) && 1U) == 1U)
    {
        if(monAeCnt[10] < frameCnt)
        {
            System_printf("Missing: TX Gain Ph Mismatch monitor report missed, received %d out of %d \n", monAeCnt[10],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if(((anaMonEn >> 11U) && 1U) == 1U)
    {
        if(monAeCnt[11] < frameCnt)
        {
            System_printf("Missing: TX0 bpm monitor report missed, received %d out of %d \n", monAeCnt[11],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if(((anaMonEn >> 12U) && 1U) == 1U)
    {
        if(monAeCnt[12] < frameCnt)
        {
            System_printf("Missing: TX1 bpm monitor report missed, received %d out of %d \n", monAeCnt[12],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if (gLinkEnableTx2 == true)
    {
        if(((anaMonEn >> 13U) && 1U) == 1U)
        {
            if(monAeCnt[13] < frameCnt)
            {
                System_printf("Missing: TX2 bpm monitor report missed, received %d out of %d \n", monAeCnt[13],frameCnt);
                failedMonRepCnt = -1;
            }
        }
    }
    if(((anaMonEn >> 14U) && 1U) == 1U)
    {
        if(monAeCnt[14] < frameCnt)
        {
            System_printf("Missing: Synth Freq monitor report missed, received %d out of %d \n", monAeCnt[14],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if(((anaMonEn >> 15U) && 1U) == 1U)
    {
        if(monAeCnt[15] < frameCnt)
        {
            System_printf("Missing: Ext Ana Sig monitor report missed, received %d out of %d \n", monAeCnt[15],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if(((anaMonEn >> 16U) && 1U) == 1U)
    {
        if(monAeCnt[16] < frameCnt)
        {
            System_printf("Missing: Int TX0 Sig monitor report missed, received %d out of %d \n", monAeCnt[16],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if(((anaMonEn >> 17U) && 1U) == 1U)
    {
        if(monAeCnt[17] < frameCnt)
        {
            System_printf("Missing: Int TX1 Sig monitor report missed, received %d out of %d \n", monAeCnt[17],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if (gLinkEnableTx2 == true)
    {
        if(((anaMonEn >> 18U) && 1U) == 1U)
        {
            if(monAeCnt[18] < frameCnt)
            {
                System_printf("Missing: Int TX2 Sig monitor report missed, received %d out of %d \n", monAeCnt[18],frameCnt);
                failedMonRepCnt = -1;
            }
        }
    }
    if(((anaMonEn >> 19U) && 1U) == 1U)
    {
        if(monAeCnt[19] < frameCnt)
        {
            System_printf("Missing: Int RX Sig monitor report missed, received %d out of %d \n", monAeCnt[19],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if(((anaMonEn >> 20U) && 1U) == 1U)
    {
        if(monAeCnt[20] < frameCnt)
        {
            System_printf("Missing: PMCLKLO Sig monitor report missed, received %d out of %d \n", monAeCnt[20],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if(((anaMonEn >> 21U) && 1U) == 1U)
    {
        if(monAeCnt[21] < frameCnt)
        {
            System_printf("Missing: Int Gpadc Sig monitor report missed, received %d out of %d \n", monAeCnt[21],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if(((anaMonEn >> 22U) && 1U) == 1U)
    {
        if(monAeCnt[22] < frameCnt)
        {
            System_printf("Missing: Pll Ctrl Volt monitor report missed, received %d out of %d \n", monAeCnt[22],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if(((anaMonEn >> 23U) && 1U) == 1U)
    {
        if(monAeCnt[23] < frameCnt)
        {
            System_printf("Missing: Dcc Clk Freq monitor report missed, received %d out of %d \n", monAeCnt[23],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if(((anaMonEn >> 26U) && 1U) == 1U)
    {
        if(monAeCnt[26] < frameCnt)
        {
            System_printf("Missing: RX Mix Input Pow monitor report missed, received %d out of %d \n", monAeCnt[24],frameCnt);
            failedMonRepCnt = -1;
        }
    }
    if(monAeCnt[27] < frameCnt)
    {
        System_printf("Missing: monitor header report missed, received %d out of %d \n", monAeCnt[0],frameCnt);
        failedMonRepCnt = -1;
    }
    if(monAeCnt[29] < frameCnt)
    {
        System_printf("Missing: Digital Periodic monitoring reports missed, received %d out of %d \n", monAeCnt[0],frameCnt);
        failedMonRepCnt = -1;
    }
    System_printf("\n");
    if(monFailRepCheck[MMWAVELINK_TEST_MON_TEMP] > 0)
    {
        System_printf ("Error: Temperature monitor report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[MMWAVELINK_TEST_MON_TEMP]);
        failedMonRepCnt = -1;
    }
    if(monFailRepCheck[2] > 0)
    {
        System_printf ("Error: Rx Noise Fig Report %d out of %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[2],monAeCnt[2]); 
        failedMonRepCnt = -1;
    }
    /* Dump the last cached value of Noise figure report */
    uint32_t nf_idx = 0;
    System_printf ("Info: Num Rx Noise Fig Reports : %d \n",monAeCnt[2]);
    System_printf ("Info: Rx Noise Fig Report last errorCode: %d \n",gMonDataAeStrct.monNoiseFigRep.errorCode);
    System_printf ("Info: Rx Noise Fig Report last NF fig value \n ");
    for (nf_idx = 0; nf_idx < 12; nf_idx++)
    {
        System_printf ("[%d]: %d ",nf_idx,gMonDataAeStrct.monNoiseFigRep.rxNoiseFigVal[nf_idx]);
    }
    System_printf ("\n");
    /* end of Noise figure report dump */

    if(monFailRepCheck[3] > 0)
    {
        System_printf ("Error: Rx IF Stage Report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[3]);
        failedMonRepCnt = -1;
    }
    if(monFailRepCheck[4] > 0)
    {
        System_printf ("Error: Rx TX0 Power report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[4]);
        failedMonRepCnt = -1;
    }
    if(monFailRepCheck[5] > 0)
    {
        System_printf ("Error: Rx TX1 Power report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[5]);
        failedMonRepCnt = -1;
    }
    if (gLinkEnableTx2 == true)
    {
        if(monFailRepCheck[6] > 0)
        {
            System_printf ("Error: Rx TX2 Power report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[6]);
            failedMonRepCnt = -1;
        }
    }
    if(monFailRepCheck[7] > 0)
    {
        System_printf ("Error: Rx TX0 Ballbreak report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[7]);
        failedMonRepCnt = -1;
    }
    if(monFailRepCheck[8] > 0)
    {
        System_printf ("Error: Rx TX1 Ballbreak report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[8]);
        failedMonRepCnt = -1;
    }
    if (gLinkEnableTx2 == true)
    {
        if(monFailRepCheck[9] > 0)
        {
            System_printf ("Error: Rx TX2 Ballbreak report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[9]);
            failedMonRepCnt = -1;
        }
    }
    if(monFailRepCheck[11] > 0)
    {
        System_printf ("Error: TX0 BPM report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[11]);
        failedMonRepCnt = -1;
    }
    if(monFailRepCheck[12] > 0)
    {
        System_printf ("Error: TX1 BPM report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[12]);
        failedMonRepCnt = -1;
    }
    if (gLinkEnableTx2 == true)
    {
        if(monFailRepCheck[13] > 0)
        {
            System_printf ("Error: TX2 BPM report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[13]);
            failedMonRepCnt = -1;
        }
    }
    if(monFailRepCheck[14] > 0)
    {
        System_printf ("Error: Synthesizeer freq report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[14]);
        failedMonRepCnt = -1;
    }
    if(monFailRepCheck[15] > 0)
    {
        System_printf ("Error: External Analog Signal monitoring report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[15]);
        failedMonRepCnt = -1;
    }
    if(monFailRepCheck[16] > 0)
    {
        System_printf ("Error: TX0 Internal Analog Signal report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[16]);
        failedMonRepCnt = -1;
    }
    if(monFailRepCheck[17] > 0)
    {
        System_printf ("Error: TX1 Internal Analog Signal report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[17]);
        failedMonRepCnt = -1;
    }
    if (gLinkEnableTx2 == true)
    {
        if(monFailRepCheck[18] > 0)
        {
            System_printf ("Error: TX2 Internal Analog Signal report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[18]);
            failedMonRepCnt = -1;
        }
    }
    if(monFailRepCheck[19] > 0)
    {
        System_printf ("Error: RX Internal Analog Signal report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[19]);
        failedMonRepCnt = -1;
    }
    if(monFailRepCheck[20] > 0)
    {
        System_printf ("Error: PMCLKLO Internal Analog Signal report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[20]);
        failedMonRepCnt = -1;
    }
    if(monFailRepCheck[21] > 0)
    {
        System_printf ("Error: GPADC Internal Analog Signal report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[21]);
        failedMonRepCnt = -1;
    }
    if(monFailRepCheck[22] > 0)
    {
        System_printf ("Error: PLL Control Volt report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[22]);
        failedMonRepCnt = -1;
    }
    if(monFailRepCheck[23] > 0)
    {
        System_printf ("Error: DCC CLK Freq report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[23]);
        failedMonRepCnt = -1;
    }
    if(monFailRepCheck[26] > 0)
    {
        System_printf ("Error: Rx Mixer InPower report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[26]);
        failedMonRepCnt = -1;
    }
    if(monFailRepCheck[28] > 0)
    {
        System_printf ("Error: Run Time Calibration report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[28]);
        failedMonRepCnt = -1;
    }
    if(monFailRepCheck[29] > 0)
    {
        System_printf ("Error: Digital Periodic Monitoring report %d times Failed. Status Flag : 0x0 \n",monFailRepCheck[26]);
        failedMonRepCnt = -1;
    }
    return failedMonRepCnt;
}

/**
 *  @b Description
 *  @n
 *      The function is used to set calib/monitoring configuration
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setCalMonConfig (void)
{
    int32_t         retVal;

    /* Set calib/monitoring time unit configuration */
    retVal = rlRfSetCalMonTimeUnitConfig(RL_DEVICE_MAP_INTERNAL_BSS,
                                     (rlRfCalMonTimeUntConf_t*)&calMonTimeUnitConf);
    if (retVal != 0)
    {
        System_printf ("Error: Unable to rlRfSetCalMonTimeUnitConfig [Error %d]\n", retVal);
        return -1;
    }
    /* Set calib/monitoring freq limits configuration */
    retVal = rlRfSetCalMonFreqLimitConfig(RL_DEVICE_MAP_INTERNAL_BSS,
                                     (rlRfCalMonFreqLimitConf_t*)&freqLimit);

    if (retVal != 0)
    {
        System_printf ("Error: Unable to rlRfSetCalMonFreqLimitConfig[Error %d]\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to set Init time calibration.
 *      using the mmWave link API.
 *
 *  @param  Enable/Disable Calibrations. 
 *          1 - Enable all calibrations. 0 - Disable all calibrations
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setInitTimeCalibConfig (int8_t enAllCalib)
{
    int32_t         retVal;
    rlRfInitCalConf_t data = { 0 };
    if (enAllCalib == 1)
    {
        data.calibEnMask = 0x1FF0;
    }
    else
    {
        data.calibEnMask = 0x0;
    }
    /* Enable/Disable calibrations */
    retVal = rlRfInitCalibConfig(RL_DEVICE_MAP_INTERNAL_BSS, &data);

    if (retVal != 0)
    {
        System_printf ("Error: Unable to rlRfInitCalibConfig [Error %d]\n", retVal);
        return -1;
    }

    return 0;
}


/**
 *  @b Description
 *  @n
 *      The function is used to set run time calibration.
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRunTimeCalibConfig (void)
{
    int32_t         retVal;

    /* Set Run time calibration configuration */
    retVal = rlRfRunTimeCalibConfig(RL_DEVICE_MAP_INTERNAL_BSS,
                                (rlRunTimeCalibConf_t*)&runTimeCalib);

    if (retVal != 0)
    {
        System_printf ("Error: Unable to rlRfRunTimeCalibConfig [Error %d]\n", retVal);
        return -1;
    }

    while(gRunTimeCalibStatus == 0U)
    {
        /* Sleep and poll again: */
        Task_sleep(1);
    }
    gRunTimeCalibStatus = 0U;

    return 0;
}
 
/**
 *  @b Description
 *  @n
 *      Print RF Monitoring Results
 *
 *  @retval
 *      Not applicable
 */
void MmwaveLink_printMonitoringResult()
{
    System_printf ("--------------Debug: Monitoring Report--------------\n");
    System_printf ("RL_RF_AE_MON_TEMPERATURE_REPORT_SB [0x%x] \n", gMonDataAeStrct.monTempReport.statusFlags);
    System_printf ("RL_RF_AE_MON_RX_GAIN_PHASE_REPORT [0x%x] \n", gMonDataAeStrct.monRxGainPhRep.statusFlags);
    System_printf ("RL_RF_AE_MON_RX_NOISE_FIG_REPORT [0x%x] \n", gMonDataAeStrct.monNoiseFigRep.statusFlags);
    System_printf ("RL_RF_AE_MON_RX_IF_STAGE_REPORT [0x%x] \n", gMonDataAeStrct.monRxIfStageRep.statusFlags);
    System_printf ("RL_RF_AE_MON_TX0_POWER_REPORT [0x%x] \n", gMonDataAeStrct.monTx0powRep.statusFlags);
    System_printf ("RL_RF_AE_MON_TX1_POWER_REPORT [0x%x] \n", gMonDataAeStrct.monTx1powRep.statusFlags);
    if (gLinkEnableTx2 == true)
    {
        System_printf ("RL_RF_AE_MON_TX2_POWER_REPORT [0x%x] \n", gMonDataAeStrct.monTx2powRep.statusFlags);
    }
    System_printf ("RL_RF_AE_MON_TX0_BALLBREAK_REPORT [0x%x] \n", gMonDataAeStrct.monTx0BallbreakRep.statusFlags);
    System_printf ("RL_RF_AE_MON_TX1_BALLBREAK_REPORT [0x%x] \n", gMonDataAeStrct.monTx1BallbreakRep.statusFlags);
    if (gLinkEnableTx2 == true)
    {
        System_printf ("RL_RF_AE_MON_TX2_BALLBREAK_REPORT [0x%x] \n", gMonDataAeStrct.monTx2BallbreakRep.statusFlags);
    }
    System_printf ("RL_RF_AE_MON_TX_GAIN_MISMATCH_REPORT [0x%x] \n", gMonDataAeStrct.monTxGainPhMisMatchRep.statusFlags);
    System_printf ("RL_RF_AE_MON_TX0_BPM_REPORT [0x%x] \n", gMonDataAeStrct.monTx0BpmRep.statusFlags);
    System_printf ("RL_RF_AE_MON_TX1_BPM_REPORT [0x%x] \n", gMonDataAeStrct.monTx1BpmRep.statusFlags);
    if (gLinkEnableTx2 == true)
    {
        System_printf ("RL_RF_AE_MON_TX2_BPM_REPORT [0x%x] \n", gMonDataAeStrct.monTx2BpmRep.statusFlags);
    }
    System_printf ("RL_RF_AE_MON_SYNTHESIZER_FREQ_REPORT [0x%x] \n", gMonDataAeStrct.monSynthFreqRep.statusFlags);
    System_printf ("RL_RF_AE_MON_EXT_ANALOG_SIG_REPORT [0x%x] \n", gMonDataAeStrct.monExtAnaSigRep.statusFlags);
    System_printf ("RL_RF_AE_MON_TX0_INT_ANA_SIG_REPORT [0x%x] \n", gMonDataAeStrct.monTx0IntAnaSigRep.statusFlags);
    System_printf ("RL_RF_AE_MON_TX1_INT_ANA_SIG_REPORT [0x%x] \n", gMonDataAeStrct.monTx1IntAnaSigRep.statusFlags);
    if (gLinkEnableTx2 == true)
    {
        System_printf ("RL_RF_AE_MON_TX2_INT_ANA_SIG_REPORT [0x%x] \n", gMonDataAeStrct.monTx2IntAnaSigRep.statusFlags);
    }
    System_printf ("RL_RF_AE_MON_RX_INT_ANALOG_SIG_REPORT [0x%x] \n", gMonDataAeStrct.monRxIntAnaSigRep.statusFlags);
    System_printf ("RL_RF_AE_MON_PMCLKLO_INT_ANA_SIG_REPORT [0x%x] \n", gMonDataAeStrct.monPmClkIntAnaSigRep.statusFlags);
    System_printf ("RL_RF_AE_MON_GPADC_INT_ANA_SIG_REPORT [0x%x] \n", gMonDataAeStrct.monGpadcIntAnaSigRep.statusFlags);
    System_printf ("RL_RF_AE_MON_PLL_CONTROL_VOLT_REPORT [0x%x] \n", gMonDataAeStrct.monPllConvVoltRep.statusFlags);
    System_printf ("RL_RF_AE_MON_DCC_CLK_FREQ_REPORT [0x%x] \n", gMonDataAeStrct.monDccClkFreqRep.statusFlags);
    System_printf ("RL_RF_AE_MON_RX_MIXER_IN_PWR_REPORT [0x%x] \n", gMonDataAeStrct.monRxMixrInPwrRep.statusFlags);
    System_printf ("----------------------------------------------------\n");
}
 
/**
 *  @b Description
 *  @n
 *      RF Monitoring Enable/Configuration function. Enables all monitoring in
 *      Radar SS
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_monitoring(void)
{
    /* Initialize monitoring counters */
    MmwaveLink_monitorReportCountInit();
    System_printf ("----------Debug: Monitoring Configuration-----------\n");
    /* Set mmWave digital monitor enable to the BSS */
    if (mmwaveLink_digMonEnableConfig(false, 0) < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link digital monitor Enable", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link digital monitor Enable", MCPI_TestResult_PASS);
    /* Set mmWave digital monitor periodic config to the BSS */
    if (MmwaveLink_rlRfDigMonPeriodicConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link digital monitor periodic Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link digital monitor periodic Config", MCPI_TestResult_PASS);
    /* Set mmWave Analog monitor config to the BSS */
    if (MmwaveLink_setRfAnaMonConfig(false, 0) < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link RF analog monitor Config", MCPI_TestResult_FAIL);
        return -1;
    }
    /* Set mmWave temperature monitor config to the BSS */
    if (MmwaveLink_setRfTempMonConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link RF temperature monitor Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link RF temperature monitor Config", MCPI_TestResult_PASS);

    /* Set mmWave RX gain and phase monitoring config to the BSS */
    if (MmwaveLink_setRfRxGainPhaMonConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link RF RX gain and phase monitor Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link RF RX gain and phase monitor Config", MCPI_TestResult_PASS);
    
    /* Set mmWave RX noise figure monitoring config to the BSS */
    if (MmwaveLink_setRfRxNoiseMonConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link RF RX noise monitor Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link RF RX noise monitor Config", MCPI_TestResult_PASS);
    
    /* Set mmWave RX If stage monitoring config to the BSS */
    if (MmwaveLink_setRfRxIfStageMonConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link RF RX IF stage monitor Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link RF RX IF stage monitor Config", MCPI_TestResult_PASS);
    
    /* Set mmWave TX Power monitoring config to the BSS */
    if (MmwaveLink_setRfTxPowMonConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link Tx power monitor Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link RF Tx power monitor Config", MCPI_TestResult_PASS);
    
    /* Set mmWave TX ball break monitoring config to the BSS */
    if (MmwaveLink_setRfTxBallbreakMonConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link Tx ballbreak monitor Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link RF Tx ballbreak monitor Config", MCPI_TestResult_PASS);
    
    /* Set mmWave TX Gain Phase mismatch monitoring config to the BSS */
    if (MmwaveLink_setRfTxGainPhaseMismatchMonConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link TX gain and phase mismatch monitor Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link RF TX gain and phase mismatch monitor Config", MCPI_TestResult_PASS);
    
    /* Set mmWave TX Bpm monitoring config to the BSS */
    if (MmwaveLink_setRfTxBpmMonConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link TX BPM monitor Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link RF TX BPM Config", MCPI_TestResult_PASS);
    
    /* Set mmWave Synth Frequency monitoring config to the BSS */
    if (MmwaveLink_setRfSynthFreqMonConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link Rf synth freq Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link Rf synth freq Config", MCPI_TestResult_PASS);
    
    /* Set mmWave Rf external analog signal config to the BSS */
    if (MmwaveLink_setRfExtAnaSignalsMonConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link Rf external analog signal Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link Rf external analog signal Config", MCPI_TestResult_PASS);
    
    /* Set mmWave TX internal analog signal config to the BSS */
    if (MmwaveLink_setRfTxIntAnaSignalMonConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link Rf TX internal analog signal Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link Rf TX internal analog signal Config", MCPI_TestResult_PASS);

    /* Set mmWave RXinternal analog signal config to the BSS */
    if (MmwaveLink_setRfRxIntAnaSignalMonConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link Rf RX internal analog signal Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link Rf RX internal analog signal Config", MCPI_TestResult_PASS);
    
    /* Set mmWave PMCLKLO internal analog signal monitoring config to the BSS */
    if (MmwaveLink_setRfPmClkLoIntAnaSignalsMonConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link Rf pm,clock  Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link Rf pm,clock Config", MCPI_TestResult_PASS);
    
    /* Set mmWave GPADC internal analog signal monitoring config to the BSS */
    if (MmwaveLink_setRfGpadcIntAnaSignalsMonConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link GPADC Internal Analog Signals Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link GPADC Internal Analog Signals Config", MCPI_TestResult_PASS);
    
    /* Set mmWave Pll control volt monitoring config to the BSS */
    if (MmwaveLink_setRfPllContrlVoltMonConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link MmwaveLink_setRfPllContrlVoltMonConfig Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link MmwaveLink_setRfPllContrlVoltMonConfig Config", MCPI_TestResult_PASS);
    
    /* Set mmWave Dual Clock monitoring config to the BSS */
    if (MmwaveLink_setRfDualClkCompMonConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link Dual Clk Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link Dual Clk Config", MCPI_TestResult_PASS);

    /* Set mmWave RX mixer input power monitoring config to the BSS */
    if (MmwaveLink_RxMixerInPwrConfig() < 0)
    {
        MCPI_setFeatureTestResult ("Set mmWave Link MmwaveLink_RxMixerInPwrConfig Config", MCPI_TestResult_FAIL);
        return -1;
    }
    MCPI_setFeatureTestResult ("Set mmWave Link MmwaveLink_RxMixerInPwrConfig Config", MCPI_TestResult_PASS);
    
    System_printf ("----------------------------------------------------\n");
    return 0;

}

/**
 *  @b Description
 *  @n
 *      Monitoring test 1
 *
 *  @retval
 *      Not Applicable.
 */
int32_t MmwaveLink_monTest1(uint8_t platformType, uint8_t platformCore)
{
    rlUInt32_t mask;
    
    /* Status variables */
    rlUInt16_t frameCount = 2;
    int32_t framePeriodicity = (FRAME_PRIODICITY_VAL*5)/1000000; 
    
    System_printf ("Debug: Starting MmwaveLink_monTest_1... \n");
    
    /* Populate global variables for this test*/
    monTestCase = MmwaveLink_monTest_1;
    monTestPassFlag = true;
    
    #if 1
    if (MmwaveLink_setChannelConfig(true, RX_CHANNEL_2_ENABLE) < 0)
    {
        return -1;
    }
    #else
    if (MmwaveLink_setChannelConfig(false, 0) < 0)
    {
        return -1;
    }
    #endif

    if (MmwaveLink_setAdcOutConfig() < 0)
    {
        return -1;
    }

    //check if this can be removed
    if(platformType == RL_AR_DEVICETYPE_16XX)
    {
        if (MmwaveLink_setLowPowerModeConfig() < 0)
        {
            return -1;
        }
    }

    if (MmwaveLink_setInitTimeCalibConfig(1) < 0)
    {
        return -1;
    }

    if (MmwaveLink_rfCalibration() < 0)
    {
        return -1;
    }

    //if (MmwaveLink_setInitTimeCalibConfig(0) < 0)
    //{
    //    return -1;
    //}
    //
    //if (MmwaveLink_rfCalibration() < 0)
    //{
    //    return -1;
    //}

    
    #if 0
    //see if this can be removed
    if (MmwaveLink_setGpAdcConfig() < 0)
    {
        return -1;
    }

    //needed ?
    /* Set LDO bypass configuration */
    if (MmwaveLink_rfSetLdoBypassConfig() < 0)
    {
        return -1;
    }
    #endif
    
    /* mmWave Link Calib/Monitoring config */
    if (MmwaveLink_setCalMonConfig() < 0)
    {
        return -1;
    }


    if (MmwaveLink_setProfileConfig() < 0)
    {
        return -1;
    }
            
    if (MmwaveLink_setChirpConfig() < 0)
    {
        return -1;
    }
    
    if (MmwaveLink_setFrameConfig(true, frameCount) < 0)
    {
        return -1;
    }
    

    /* configure AdcBuffer based on sample size and rx-channels */
    //need to update this
    MmwaveLink_adcBufConfig();


    #if 0
    /* mmWave RF Monitoring */
    if (MmwaveLink_monitoring() < 0)
    {
        return -1;
    }
    #else
    
    MmwaveLink_monitorReportCountInit();

    /*Disable all digital monitoring*/
    if (mmwaveLink_digMonEnableConfig(true, 0) < 0)
    {
        return -1;
    }

    mask = (1 << MMWAVELINK_TEST_MON_RX_GAIN_PH);
    if (MmwaveLink_setRfAnaMonConfig(true, mask) < 0)
    {
        return -1;
    }
    
    if (MmwaveLink_setRfRxGainPhaMonConfig() < 0)
    {
        return -1;
    }
    #endif

    
    /* Re-initialize chirp & frame interrupts count */
    gLinkFrameCnt = 0;
    gLinkChirpCnt = 0;

    System_printf ("Debug: Starting Sensor.. \n");
    if (MmwaveLink_sensorStart() < 0)
    {
        return -1;
    }
        
    /* wait till all frame interrupts are received */
    Task_sleep((framePeriodicity*(4*frameCount + 1))/4);

    /* wait for all chirp interrupts of current frame */
    while(gLinkChirpCnt != ((frameCfg.chirpEndIdx - frameCfg.chirpStartIdx + 1U)* frameCfg.numLoops));
    
    if(gLinkFrameCnt == frameCount)
    {
        System_printf("All frames received\n");
    }
    
    #if 0
    /*For advanced frame*/
    while(gLinkChirpCnt != advFrameCfg.frameSeq.subFrameCfg[advFrameCfg.frameSeq.numOfSubFrames-1U].numOfChirps);
    if(gLinkFrameCnt == (advFrameCfg.frameSeq.numFrames * advFrameCfg.frameSeq.numOfSubFrames))
    {
            System_printf("All frames received\n");
    }
    /* for advace frame, we get frame interrupt for each sub frame but monitoring report for each frame */
    resultMonitoringReport = MmwaveLink_CheckMonitoringReport(gLinkFrameCnt/(advFrameCfg.frameSeq.numOfSubFrames));
    #endif    

    /* Update global variables */
    gLinkFrameCnt = 0;
    gLinkChirpCnt = 0;
    
    /* Check Results  */
    if(monTestPassFlag == false)
    {
        return -1;
    }

    if(monAeCnt[MMWAVELINK_TEST_MON_RX_GAIN_PH] != frameCount)
    {
        System_printf("Error MmwaveLink_monTest_1: expected %d reports. Received %d.\n", frameCount, monAeCnt[MMWAVELINK_TEST_MON_RX_GAIN_PH]);
        return -1;
    }    

    return 0;
}


/**
 *  @b Description
 *  @n
 *      Enhanced tests focused on Monitoring and calibration APIs.
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_monAdvancedTest(uint8_t platformType, uint8_t platformCore)
{

    if(MmwaveLink_monTest1(platformType, platformCore) < 0)
    {
        MCPI_setFeatureTestResult ("MmwaveLink_monTest_1", MCPI_TestResult_FAIL);
    }
    else
    {
        MCPI_setFeatureTestResult ("MmwaveLink_monTest_1", MCPI_TestResult_PASS);
    }    
    
    monTestCase = MmwaveLink_monTest_none;

}


/**
 *  @b Description
 *  @n
 *      Verification of RX gain phase report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyRxGainPhRep(rlMonRxGainPhRep_t *rep)
{
    uint32_t i;
    
    monAeCnt[MMWAVELINK_TEST_MON_RX_GAIN_PH]++;
    
    if(rep->statusFlags == 0U)
    {
        monFailRepCheck[MMWAVELINK_TEST_MON_RX_GAIN_PH]++;
    }
    
#if 0
    System_printf("statusFlags      = %d\n",rep->statusFlags);
    System_printf("errorCode        = %d\n",rep->errorCode);
    System_printf("profIndex        = %d\n",rep->profIndex);
    System_printf("loopbackPowerRF1 = %d\n",rep->loopbackPowerRF1);
    System_printf("loopbackPowerRF2 = %d\n",rep->loopbackPowerRF2);
    System_printf("loopbackPowerRF3 = %d\n",rep->loopbackPowerRF3);
    for(i=0; i<12; i++)
        System_printf("rxGainVal[%d]    = 0x%x\n",i,rep->rxGainVal[i]);
    for(i=0; i<12; i++)
        System_printf("rxPhaseVal[%d]   = 0x%x\n",i,rep->rxPhaseVal[i]);
    System_printf("rxNoisePower1    = 0x%x\n",rep->rxNoisePower1);
    System_printf("rxNoisePower2    = 0x%x\n",rep->rxNoisePower2);
    System_printf("timeStamp        = %d\n",rep->timeStamp);
#endif    

    /*Now verify specific testcase data*/    
    if(monTestCase == MmwaveLink_monTest_1)
    {
        if(rep->errorCode != 0)
        {
            monTestPassFlag = false;
            System_printf("Error MmwaveLink_monTest_1: errorCode = %d\n",rep->errorCode);
        }    
        
        if(rep->profIndex != 0)
        {
            monTestPassFlag = false;
            System_printf("Error MmwaveLink_monTest_1: profIndex = %d\n",rep->profIndex);
        }    

        for(i=0; i<12; i++)
        {
            /* All reports (for RF1, RF2, RF3) must be zero except for RX channel 1*/
            if((i != 1) && (i != 5) && (i != 9))
            {            
                if(rep->rxGainVal[i] != 0)
                {
                    monTestPassFlag = false;
                    System_printf("Error MmwaveLink_monTest_1: rxGainVal[%d]    = 0x%x\n",i,rep->rxGainVal[i]);
                }
                if(rep->rxPhaseVal[i] != 0)
                {
                    monTestPassFlag = false;
                    System_printf("Error MmwaveLink_monTest_1: rxPhaseVal[%d]   = 0x%x\n",i,rep->rxPhaseVal[i]);
                }                
            }    
        }        
    }
}


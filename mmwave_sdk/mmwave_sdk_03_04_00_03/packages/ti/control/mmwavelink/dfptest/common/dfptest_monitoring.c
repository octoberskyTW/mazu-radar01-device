/*
 *   @file  dfptest_monitoring.c
 *
 *   @brief
 *      Implements testbench monitoring and calibration APIs
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
#include <ti/control/mmwavelink/dfptest/common/dfptest_setup.h>
#include <ti/control/mmwavelink/dfptest/common/dfptest_monitoring.h>
#include <ti/control/mmwavelink/dfptest/common/dfptest_config.h>
#include <ti/control/mmwavelink/dfptest/common/dfptest_verify.h>

/*Semaphore used to indicate if latent fault report was received. Internally used by the testbench*/
volatile uint32_t gLatentFaultReportReceived;


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
int32_t MmwaveLink_setRfAnaMonConfig (void)
{
    int32_t  retVal;
    
    /* Analog monitors enable */
    retVal = rlRfAnaMonConfig(RL_DEVICE_MAP_INTERNAL_BSS, &monAnaEnables);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfAnaMonConfig retVal=%d\n", retVal);
        return -1;
    }
    
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
    retVal = rlRfRxGainPhMonConfig(RL_DEVICE_MAP_INTERNAL_BSS, &rxGainPhaseMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfRxGainPhMonConfig retVal=%d\n", retVal);
        return -1;
    }
    
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
int32_t MmwaveLink_setRfRxIfStageMonConfig ()
{
    int32_t         retVal;
    
    /* Set RX IF Stage monitor configuration */
    retVal = rlRfRxIfStageMonConfig(RL_DEVICE_MAP_INTERNAL_BSS, &monRxIfStageCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfRxIfStageMonConfig retVal=%d\n", retVal);
        return -1;
    }
    
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
int32_t MmwaveLink_setRfSynthFreqMonConfig ()
{
    int32_t         retVal;
    
    /* Set Synth Freq monitor configuration */
    retVal = rlRfSynthFreqMonConfig(RL_DEVICE_MAP_INTERNAL_BSS, &synthFreqMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfSynthFreqMonConfig retVal=%d\n", retVal);
        return -1;
    }
    
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
int32_t MmwaveLink_setRfTxIntAnaSignalMonConfig ()
{
    int32_t         retVal;

    /* Set TX Internal analog signal monitor configuration */
    retVal = rlRfTxIntAnaSignalsMonConfig(RL_DEVICE_MAP_INTERNAL_BSS, &allTxanaSigMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfTxIntAnaSignalsMonConfig retVal=%d\n", retVal);
        return -1;
    }
    
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

    /* Set RX Internal analog signal monitor configuration */
    retVal = rlRfRxIntAnaSignalsMonConfig(RL_DEVICE_MAP_INTERNAL_BSS, &rxIntAnaSigMonCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfRxIntAnaSignalsMonConfig retVal=%d\n", retVal);
        return -1;
    }
    
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
int32_t mmwaveLink_digMonEnableConfig(void)
{
    int32_t  retVal;
    
    /* Digital monitoring configuration */
    retVal = rlRfDigMonEnableConfig(RL_DEVICE_MAP_INTERNAL_BSS, &monDigEnables);
    
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfDigMonEnableConfig retVal=%d\n", retVal);
        return -1;
    }
    
    return 0;
};

int32_t MmwaveLink_rlRfDigMonPeriodicConfig (void)
{
    int32_t         retVal;

    /* Set Digital periodic monitor configuration */
    retVal = rlRfDigMonPeriodicConfig(RL_DEVICE_MAP_INTERNAL_BSS, &monDigPeriodicCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfDigMonPeriodicConfig retVal=%d\n", retVal);
        return -1;
    }
    
    return 0;
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
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setInitTimeCalibConfig (void)
{
    int32_t         retVal;

    /* Enable/Disable calibrations */
    retVal = rlRfInitCalibConfig(RL_DEVICE_MAP_INTERNAL_BSS, &rfInitCalib);

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
        System_printf ("Error: rlRfRunTimeCalibConfig [Error %d]\n", retVal);
        return -1;
    }

    return 0;
}
 
/**
 *  @b Description
 *  @n
 *      Configure Analog monitoring features
 *
 *  @retval
 *      Not Applicable.
 */
int32_t MmwaveLink_monFeatureCfg(void)
{
    /*digital monitoring config*/
    if (MmwaveLink_rlRfDigMonPeriodicConfig() < 0)
    {
        return -1;
    }

    /* enable analog monitoring for the required features*/
    if (MmwaveLink_setRfAnaMonConfig() < 0)
    {
        return -1;
    }

    if(monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_TEMP))
    {
        if (MmwaveLink_setRfTempMonConfig() < 0)
        {
            return -1;
        }
    }
    
    if(monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_RX_GAIN_PH))
    {
        if (MmwaveLink_setRfRxGainPhaMonConfig() < 0)
        {
            return -1;
        }
    }
    
    if(monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_RX_NOISE_FIG))
    {
        if (MmwaveLink_setRfRxNoiseMonConfig() < 0)
        {
            return -1;
        }
    }
    
    if(monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_RX_IF_STAGE))
    {
        if (MmwaveLink_setRfRxIfStageMonConfig() < 0)
        {
            return -1;
        }
    }
        
    if((monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_TX0_POWER)) ||
       (monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_TX1_POWER)) ||
       (monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_TX2_POWER)))
    {
        if (MmwaveLink_setRfTxPowMonConfig() < 0)
        {
            return -1;
        }
    }

    if((monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_TX0_BALL_BRK)) ||
       (monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_TX1_BALL_BRK)) ||
       (monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_TX2_BALL_BRK)))
    {
        if (MmwaveLink_setRfTxBallbreakMonConfig() < 0)
        {
            return -1;
        }
    }
        
    if(monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_TX_GAIN_PHASE))
    {
        if (MmwaveLink_setRfTxGainPhaseMismatchMonConfig() < 0)
        {
            return -1;
        }
    }

    if((monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_TX0_BPM)) ||
       (monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_TX1_BPM)) ||
       (monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_TX2_BPM)))
    {
        if (MmwaveLink_setRfTxBpmMonConfig() < 0)
        {
            return -1;
        }
    }
       
    if(monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_SYNTHESIZER_FREQ))
    {
        if (MmwaveLink_setRfSynthFreqMonConfig() < 0)
        {
            return -1;
        }
    }
        
    if(monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_EXTERN_ANALOG_SIG))
    {
        if (MmwaveLink_setRfExtAnaSignalsMonConfig() < 0)
        {
            return -1;
        }
    }
        
    if((monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_TX0_INT_ANA_SIG)) ||
       (monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_TX1_INT_ANA_SIG)) ||
       (monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_TX2_INT_ANA_SIG)))
    {
        if (MmwaveLink_setRfTxIntAnaSignalMonConfig() < 0)
        {
            return -1;
        }
    }    
    
    if(monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_INT_RX_SIG))
    {
        if (MmwaveLink_setRfRxIntAnaSignalMonConfig() < 0)
        {
            return -1;
        }
    }
    
    if(monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_INT_PMCLKLO_SIG))
    {
        if (MmwaveLink_setRfPmClkLoIntAnaSignalsMonConfig() < 0)
        {
            return -1;
        }
    }

    if(monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_INT_GPADC_SIG))
    {
        if (MmwaveLink_setRfGpadcIntAnaSignalsMonConfig() < 0)
        {
            return -1;
        }
    }

    if(monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_PLL_CONTROL_VOLT))
    {
        if (MmwaveLink_setRfPllContrlVoltMonConfig() < 0)
        {
            return -1;
        }
    }

    if(monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_DCC_CLOCK_FREQ))
    {
        if (MmwaveLink_setRfDualClkCompMonConfig() < 0)
        {
            return -1;
        }
    }

    if(monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_RX_IF_SATURATION))
    {
        if (MmwaveLink_setRfRxIfSatMonConfig() < 0)
        {
            return -1;
        }
    }

    if(monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_RX_SIG_IMG_BAND))
    {
        if (MmwaveLink_setRfRxSigImgMonConfig() < 0)
        {
            return -1;
        }
    }

    if(monAnaEnables.enMask & (1 << MMWAVELINK_TEST_MON_RX_MIXER_INP_POWER))
    {
        if (MmwaveLink_RxMixerInPwrConfig() < 0)
        {
            return -1;
        }
    }

    return 0;
}
 
/**
 *  @b Description
 *  @n
 *      Function that generates N latent fault reports back to back. 
 *      This API waits until all reports are received.
 *
 *  @retval
 *      Not Applicable.
 */
int32_t MmwaveLink_genLatentFaultRep(uint32_t numberOfReports, bool printDebugInfo)
{
    int32_t i;
    uint32_t maxLatentFaultWait, latentFaultWait;
    
    maxLatentFaultWait = 0;
    for(i = 0; i < numberOfReports; i++)
    {
        gLatentFaultReportReceived = 0;
        if (mmwaveLink_digMonEnableConfig() < 0)
        {
            System_printf ("Error: Latent fault report failed to enable on iteration %d\n", i);
            return -1;
        }
        else
        {
            /* wait for latent fault report before calling API again */
            latentFaultWait = 0;
            while(gLatentFaultReportReceived == 0)
            {
                 Task_sleep(10);
                 latentFaultWait++;
            }
            
            if(latentFaultWait > maxLatentFaultWait)
            {
                maxLatentFaultWait = latentFaultWait;
            }
        }
    }
    
    if(printDebugInfo)
    {
        System_printf ("Debug: Received %d latent fault reports.\n",numberOfReports);
        System_printf ("Debug: Max latent fault wait = %d.\n",maxLatentFaultWait);
    }
    
    return 0;
}


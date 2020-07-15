/*
 *   @file  dfptest_common.c
 *
 *   @brief
 *      DFP test common framework code
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
#include <ti/utils/testlogger/logger.h>
#include <ti/utils/cycleprofiler/cycle_profiler.h>
#include <ti/control/mmwavelink/dfptest/common/dfptest_config.h>
#include <ti/control/mmwavelink/dfptest/common/dfptest_setup.h>
#include <ti/control/mmwavelink/dfptest/common/dfptest_monitoring.h>
#include <ti/control/mmwavelink/dfptest/common/dfptest_verify.h>

/**************************************************************************
 *************************** Global Variables *****************************
 **************************************************************************/
/*Test bench control block. Internally used by the testbench*/
dfpTestMCB_t gTestMCB;

/*Semaphore used to indicate sensor has stopped. Internally used by the testbench*/
Semaphore_Handle gSensorStopSem;

extern volatile uint8_t eDMADataTransferDone;

/**************************************************************************
 ************************** Funnctions            *************************
 **************************************************************************/


/**
 *  @b Description
 *  @n
 *      Interrupt handler callback for frame start ISR.
 *
 *  @retval
 *      Not Applicable.
 */
void Mmwavelink_frameInterrupCallBackFunc(uintptr_t arg)
{

    gTestMCB.chirpCnt = 0;

    /* increment Frame count */
    gTestMCB.frameCnt++;    

}

/**
 *  @b Description
 *  @n
 *      Interrupt handler callback for chirp available ISR.
 *
 *  @retval
 *      Not Applicable.
 */
void Mmwavelink_chirpAvailInterrupCallBackFunc(uintptr_t arg)
{
    
    /* increment the Chirp count for current frame */
    gTestMCB.chirpCnt++;

}

/*Initializes all config global variables to zero*/
void MmwaveLinkTest_initConfig(void)
{
    memset((void*)&gTestStartStopCfg     , 0 , sizeof(gTestStartStopCfg));
    memset((void*)&gTestMiscCfg          , 0 , sizeof(gTestMiscCfg));
    memset((void*)&chCfg                 , 0 , sizeof(chCfg          ));
    memset((void*)&adcOutCfgArgs         , 0 , sizeof(adcOutCfgArgs  ));
    memset((void*)&lowPowerModeCfg       , 0 , sizeof(lowPowerModeCfg));
    memset((void*)&deviceHsiClk          , 0 , sizeof(deviceHsiClk   ));
    memset((void*)&profileCfg[0]         , 0 , sizeof(rlProfileCfg_t)*DFPTEST_MAX_NUM_PROFCFG);
    memset((void*)&chirpCfg[0]           , 0 , sizeof(rlChirpCfg_t)*DFPTEST_MAX_NUM_CHIRPCFG);
    memset((void*)&monDigEnables         , 0 , sizeof(monDigEnables     ));
    memset((void*)&monDigPeriodicCfg     , 0 , sizeof(monDigPeriodicCfg     ));
    memset((void*)&monAnaEnables         , 0 , sizeof(monAnaEnables     ));
    memset((void*)&rxSatMonCfg           , 0 , sizeof(rxSatMonCfg       ));
    memset((void*)&sigImgMonCfg          , 0 , sizeof(sigImgMonCfg      ));
    memset((void*)&frameCfg              , 0 , sizeof(frameCfg          ));
    memset((void*)&calMonTimeUnitConf    , 0 , sizeof(calMonTimeUnitConf));
    memset((void*)&freqLimit             , 0 , sizeof(freqLimit         ));
    memset((void*)&rfInitCalib           , 0 , sizeof(rfInitCalib       ));
    memset((void*)&runTimeCalib          , 0 , sizeof(runTimeCalib      ));
    memset((void*)&advFrameCfg           , 0 , sizeof(advFrameCfg       ));
    memset((void*)&bpmCommonCfg          , 0 , sizeof(bpmCommonCfg      ));
    memset((void*)&bpmChirpCfg[0]        , 0 , sizeof(rlBpmChirpCfg_t)*DFPTEST_MAX_NUM_BPMCHIRPCFG);   
    memset((void*)&contModeCfg           , 0 , sizeof(contModeCfg           ));
    memset((void*)&contModeEn            , 0 , sizeof(contModeEn            ));
    memset((void*)&dynPwrSave            , 0 , sizeof(dynPwrSave            ));
    memset((void*)&gpAdcCfg              , 0 , sizeof(gpAdcCfg              ));
    memset((void*)&rfLdoBypassCfg        , 0 , sizeof(rfLdoBypassCfg        ));
    memset((void*)&tempMonCfg            , 0 , sizeof(tempMonCfg            ));
    memset((void*)&rxGainPhaseMonCfg     , 0 , sizeof(rxGainPhaseMonCfg     ));
    memset((void*)&rxNoiseMonCfg         , 0 , sizeof(rxNoiseMonCfg         ));
    memset((void*)&monRxIfStageCfg       , 0 , sizeof(monRxIfStageCfg       ));
    memset((void*)&tx0PowMonCfg          , 0 , sizeof(tx0PowMonCfg          ));
    memset((void*)&tx1PowMonCfg          , 0 , sizeof(tx1PowMonCfg          ));
    memset((void*)&tx2PowMonCfg          , 0 , sizeof(tx2PowMonCfg          ));
    memset((void*)&allTxPowMonCfg        , 0 , sizeof(allTxPowMonCfg        ));
    memset((void*)&tx0BallBreakMonCfg    , 0 , sizeof(tx0BallBreakMonCfg    ));
    memset((void*)&tx1BallBreakMonCfg    , 0 , sizeof(tx1BallBreakMonCfg    ));
    memset((void*)&tx2BallBreakMonCfg    , 0 , sizeof(tx2BallBreakMonCfg    ));
    memset((void*)&allTxBallbreakMonCfg  , 0 , sizeof(allTxBallbreakMonCfg  ));
    memset((void*)&txGainPhMisMatchMonCfg, 0 , sizeof(txGainPhMisMatchMonCfg));
    memset((void*)&tx0BpmMonCfg          , 0 , sizeof(tx0BpmMonCfg          ));
    memset((void*)&tx1BpmMonCfg          , 0 , sizeof(tx1BpmMonCfg          ));
    memset((void*)&tx2BpmMonCfg          , 0 , sizeof(tx2BpmMonCfg          ));
    memset((void*)&allTxBpmMonCfg        , 0 , sizeof(allTxBpmMonCfg        ));
    memset((void*)&synthFreqMonCfg       , 0 , sizeof(synthFreqMonCfg       ));
    memset((void*)&extAnaSigMonCfg       , 0 , sizeof(extAnaSigMonCfg       ));
    memset((void*)&tx0IntAnaSigMonCfg    , 0 , sizeof(tx0IntAnaSigMonCfg    ));
    memset((void*)&tx1IntAnaSigMonCfg    , 0 , sizeof(tx1IntAnaSigMonCfg    ));
    memset((void*)&tx2IntAnaSigMonCfg    , 0 , sizeof(tx2IntAnaSigMonCfg    ));
    memset((void*)&allTxanaSigMonCfg     , 0 , sizeof(allTxanaSigMonCfg     ));
    memset((void*)&rxIntAnaSigMonCfg     , 0 , sizeof(rxIntAnaSigMonCfg     ));
    memset((void*)&pmClkLoIntAnaSigMonCfg, 0 , sizeof(pmClkLoIntAnaSigMonCfg));
    memset((void*)&gpadcIntAnaSigMonCfg  , 0 , sizeof(gpadcIntAnaSigMonCfg  ));
    memset((void*)&pllConVoltMonCfg      , 0 , sizeof(pllConVoltMonCfg      ));
    memset((void*)&dualClkCompMonCfg     , 0 , sizeof(dualClkCompMonCfg     ));
    memset((void*)&rxMixInpwrMonCfg      , 0 , sizeof(rxMixInpwrMonCfg      ));
    memset((void*)&progFiltCfg           , 0 , sizeof(progFiltCfg           ));
    memset((void*)&progFiltCoef          , 0 , sizeof(progFiltCoef          ));
    memset((void*)&subFrameTrigCfg       , 0 , sizeof(subFrameTrigCfg       ));
    memset((void*)&miscCfg               , 0 , sizeof(miscCfg               ));    
    memset((void*)&phaseShiftCfg[0]      , 0 , sizeof(rlRfPhaseShiftCfg_t)*DFPTEST_MAX_NUM_PHASESHCFG);
    memset((void*)&dynPhaseShiftCfg[0]   , 0 , sizeof(rlDynPerChirpPhShftCfg_t)*DFPTEST_MAX_NUM_DYNPHASESHCFG);
    memset((void*)&interRxGainPhCfg      , 0 , sizeof(interRxGainPhCfg    ));
    memset((void*)&testSourceCfg         , 0 , sizeof(testSourceCfg       ));
    memset((void*)&testSourceEn          , 0 , sizeof(testSourceEn        ));
    memset((void*)&rxGainTempLutReadCfg  , 0 , sizeof(rxGainTempLutReadCfg));
    memset((void*)&txGainTempLutReadCfg  , 0 , sizeof(txGainTempLutReadCfg));

}

void MmwaveLink_loadConfig(bool loadStartStopConfig)
{
    dfpTestStartStopCfg_t localStartStopCfg;
    
    if(loadStartStopConfig == false)
    {
        /* Need to save startStop config to restore it after dfpTestLoadCfg_xxx() is executed*/ 
        localStartStopCfg = gTestStartStopCfg;
    }
    
    MmwaveLinkTest_initConfig();
    
    switch(gTestNumber)
    {
        case 1:
            dfpTestLoadCfg_001();
        break;    
        case 2:
            dfpTestLoadCfg_002();
        break;    
        case 3:
            dfpTestLoadCfg_003();
        break;    
        case 4:
            dfpTestLoadCfg_004();
        break;    
        case 5:
            dfpTestLoadCfg_005();
        break;    
        case 6:
            dfpTestLoadCfg_006();
        break;    
        case 7:
            dfpTestLoadCfg_007();
        break;    
        case 8:
            dfpTestLoadCfg_008();
        break;    
        case 9:
            dfpTestLoadCfg_009();
        break;    
        case 10:
            dfpTestLoadCfg_010();
        break;    
        default:
            System_printf("\n*********************\nError: test number %d not supported for this platform\n",gTestNumber);            
        break;
    }    
    
    /*overwrite number of frames to run*/
    if(gNumberOfFrames)
    {
        if(gTestMiscCfg.testAdvancedFrame)
        {
            advFrameCfg.frameSeq.numFrames = gNumberOfFrames;
        }
        else
        {
            frameCfg.numFrames = gNumberOfFrames;
        }
    }
    
    /*Disable features not supported for IWR devices*/
    if(gIwrDeviceFlag)
    {
        /*Disable digital monitoring*/
        monDigEnables.enMask = 0;
        /*Disable digital periodic monitoring */
        monDigPeriodicCfg.periodicEnableMask = 0;
        /*Disable analog monitoring*/
        monAnaEnables.enMask = 0;
    }
    
    if(loadStartStopConfig == false)
    {
        /* Need to restore start stop config*/ 
        gTestStartStopCfg = localStartStopCfg;
    }
}

void MmwaveLinkTest_initMCB(void)
{
    /* initialize test MCB*/
    memset(&gTestMCB, 0, sizeof(dfpTestMCB_t));
    gTestMCB.previousFttiCount = 0xFFFFFFFF;//ftticount starts with zero.
}

/**
 *  @b Description
 *  @n
 *      DFP test 
 *
 *  @retval
 *      Not Applicable.
 */
int32_t MmwaveLink_runDfpTest(uint8_t platformType, uint8_t platformCore)
{
    int32_t retVal = 0;
    
    monTestPassFlag = true;
    
    if (MmwaveLink_setChannelConfig() < 0)
    {
        return -1;
    }

    if (MmwaveLink_setAdcOutConfig() < 0)
    {
        return -1;
    }

    if(platformType == RL_AR_DEVICETYPE_16XX)
    {
        if (MmwaveLink_setLowPowerModeConfig() < 0)
        {
            return -1;
        }
    }

    if (MmwaveLink_setInitTimeCalibConfig() < 0)
    {
        return -1;
    }

    if (MmwaveLink_rfCalibration() < 0)
    {
        return -1;
    }

    if (MmwaveLink_setGpAdcConfig() < 0)
    {
        return -1;
    }

    if (MmwaveLink_rfSetLdoBypassConfig() < 0)
    {
        return -1;
    }
    
    /* mmWave Link Calib/Monitoring config */
    if (MmwaveLink_setCalMonConfig() < 0)
    {
        return -1;
    }

    if (MmwaveLink_setProfileConfig(gTestMiscCfg.numProfiles) < 0)
    {
        return -1;
    }

    if (MmwaveLink_getProfileConfig() < 0)
    {
        return -1;
    }
    
    if (MmwaveLink_setChirpConfig(gTestMiscCfg.numChirpConfigs) < 0)
    {
        return -1;
    }
    
    if(gTestMiscCfg.testAdvancedFrame == false)
    {
        if (MmwaveLink_setFrameConfig() < 0)
        {
            return -1;
        }
        if (MmwaveLink_getFrameConfig() < 0)
        {
            return -1;
        }
    } 
    else
    {
        if (MmwaveLink_setAdvFrameConfig() < 0)
        {
            return -1;
        }
        if (MmwaveLink_getAdvFrameConfig() < 0)
        {
            return -1;
        }
    } 
    
    /* configure AdcBuffer based on sample size and rx-channels */
    MmwaveLink_adcBufConfig();
    
    /* Configure BPM chirps if needed*/
    if(gTestMiscCfg.numBpmChirpConfigs > 0)
    {
        if (MmwaveLink_setBpmCommonConfig() < 0)
        {
            return -1;
        }

        if (MmwaveLink_setBpmChirpConfig(gTestMiscCfg.numBpmChirpConfigs) < 0)
        {
            return -1;
        }
    }

    /*configure monitors and calibration*/
    if(gIwrDeviceFlag == false)
    {
        if (MmwaveLink_monFeatureCfg() < 0)
        {
            return -1;
        }        
    }    

    /*Enable periodic calibration?*/
    if(runTimeCalib.calibPeriodicity > 0)
    {
        if (MmwaveLink_setRunTimeCalibConfig() < 0)
        {
            return -1;
        }
    }    
    
    /* Need to generate latent fault reports before sensor start? */   
    if((gTestMiscCfg.numLatentFaultBeforeFrameStart > 0) && (gIwrDeviceFlag == false))
    {
        if(MmwaveLink_genLatentFaultRep(gTestMiscCfg.numLatentFaultBeforeFrameStart, true) < 0)
        {
            return -1;
        }
    }    
    
    /* Initialize monitor report counters */
    MmwaveLink_monitorReportCountInit();
    
    System_printf ("Debug: Starting Sensor.. \n");
    
    if (MmwaveLink_sensorStart() < 0)
    {
        return -1;
    }
    
    /* wait for sensor stop */
    Semaphore_pend (gSensorStopSem, BIOS_WAIT_FOREVER);
    
    if(gTestMiscCfg.testAdvancedFrame == false)
    {
        if(gTestMCB.frameCnt == frameCfg.numFrames)
        {
            System_printf("All %d frames received.\n", gTestMCB.frameCnt);
        }
        else
        {
            retVal = -1;
            System_printf("Error: Expected %d frames. Received %d frames.\n", frameCfg.numFrames, gTestMCB.frameCnt);
        }
    }
    else
    {
        if(gTestMCB.frameCnt == (advFrameCfg.frameSeq.numFrames * advFrameCfg.frameSeq.numOfSubFrames))
        {
            System_printf("All %d frames received. Total of %d frame interrupts.\n", advFrameCfg.frameSeq.numFrames, gTestMCB.frameCnt);
        }
        else
        {
            retVal = -1;
            System_printf("Error: Expected %d frame interrupts (%d frames %d subframes). Received %d frame interrupts.\n", 
            advFrameCfg.frameSeq.numFrames * advFrameCfg.frameSeq.numOfSubFrames, 
            advFrameCfg.frameSeq.numFrames, advFrameCfg.frameSeq.numOfSubFrames, gTestMCB.frameCnt);
        }
    }        

    /* Need to generate latent fault reports after sensor stop? */   
    if((gTestMiscCfg.numLatentFaultAfterFrameStop > 0) && (gIwrDeviceFlag == false))
    {
        if(MmwaveLink_genLatentFaultRep(gTestMiscCfg.numLatentFaultAfterFrameStop, true) < 0)
        {
            return -1;
        }
    }   
    
    /* Check Results  */
    if(monTestPassFlag == false)
    {
        System_printf("Error: Test failed during real-time verification of monitoring reports: monTestPassFlag is false.\n");
        retVal = -1;
    }

    if(MmwaveLink_verifyReportCount() < 0)
    {
        return -1;
    }

    return retVal;
}

/**
 *  @b Description
 *  @n
 *      System Initialization Task which initializes the various
 *      components in the system.
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_startDfpTest(uint8_t platformType, uint8_t platformCore)
{
    uint32_t i;
    bool     startStopTestPassFlag = true;

    /* Setup and initialize the mmWave Link: */
    if (MmwaveLink_initLink (platformType, platformCore ) < 0)
    {
        System_printf("Error: mmWave Link Initialization\n");
        return;
    }

    /* Get radarSS bootup status */
    if (MmwaveLink_getRfBootupStatus () < 0)
    {
        System_printf("Error: Get radarSS bootup status");
        return;
    }

    /* Get mmWave Link Version: */
    if(MmwaveLink_getVersion() < 0)
    {
        System_printf("Error: Get mmWave Link Version");
        return;
    }

#ifdef SUBSYS_DSS
    /* mmWave Link set Async event configuration */
    if (MmwaveLink_setRfDevCfg(0xA) < 0)
    {
        System_printf("Error: Set Async event config", MCPI_TestResult_FAIL);
        return;
    }
#else
    /* mmWave Link set Async event configuration */
    if (MmwaveLink_setRfDevCfg(0x0) < 0)
    {
        System_printf("Error: Set Async event config", MCPI_TestResult_FAIL);
        return;
    }
#endif
    
    /* Load configuration. Needs to be done before HSI setting. */
    MmwaveLink_loadConfig(true);

    /* Set device HSI clock */
    if (MmwaveLink_setHsiClk() < 0)
    {
        System_printf("Error: Set HSI clock", MCPI_TestResult_FAIL);
        return;
    }

    System_printf ("Debug: Starting test number %d.\n", gTestNumber);

    MmwaveLinkTest_initMCB();
    if(MmwaveLink_runDfpTest(platformType, platformCore) < 0)
    {
        System_printf("--- Test %d result:\n", gTestNumber);
        MCPI_setFeatureTestResult ("Test", MCPI_TestResult_FAIL);
        startStopTestPassFlag = false;
    }
    else
    {
        System_printf("--- Test %d result:\n", gTestNumber);
        MCPI_setFeatureTestResult ("Test", MCPI_TestResult_PASS);
    }
    
    for(i = 0; i < gTestStartStopCfg.numStartStopNoReconfig; i++)
    { 
        System_printf ("------------------------------\n"); 
        System_printf ("Debug: Starting test number %d. No reconfiguration. Iteration number %d\n", gTestNumber, i+1);
    
        MmwaveLinkTest_initMCB();
        if(MmwaveLink_runDfpTest(platformType, platformCore) < 0)
        {
            System_printf("--- Test %d result:\n", gTestNumber);
            MCPI_setFeatureTestResult ("Test", MCPI_TestResult_FAIL);
            startStopTestPassFlag = false;
        }
        else
        {
            System_printf("--- Test %d result:\n", gTestNumber);
            MCPI_setFeatureTestResult ("Test", MCPI_TestResult_PASS);
        }
    }    

    if(gTestStartStopCfg.numStartStopReconfig >= 1)
    {
        System_printf ("------------------------------\n"); 
        System_printf ("Starting start/stop with reconfiguration\n");
    }    
    
    for(i = 0; i < gTestStartStopCfg.numStartStopReconfig; i++)
    {    
        if(i >= MMWAVELINK_TEST_MAX_NUM_STARTSTOP_RECONFIG)
        {
            System_printf("Error: Maximum number of reconfigurations is %d\n", MMWAVELINK_TEST_MAX_NUM_STARTSTOP_RECONFIG);
            return;
        }
        gTestNumber = gTestStartStopCfg.testNumberSwitchAfterStop[i];
        System_printf ("------------------------------\n"); 
        System_printf ("Debug: Starting test number %d. StartStop with reconfiguration, iteration number %d\n", gTestNumber, i+1);
        
        MmwaveLinkTest_initMCB();

        /*Load new config but retain the start/stop configuration from the original test*/
        MmwaveLink_loadConfig(false);
        
        if(MmwaveLink_runDfpTest(platformType, platformCore) < 0)
        {
            System_printf("--- Test %d (reconfig) result:\n", gTestNumber);
            MCPI_setFeatureTestResult ("Test", MCPI_TestResult_FAIL);
            startStopTestPassFlag = false;
        }
        else
        {
            System_printf("--- Test %d (reconfig) result:\n", gTestNumber);
            MCPI_setFeatureTestResult ("Test", MCPI_TestResult_PASS);
        }
    }    
    
    if((gTestStartStopCfg.numStartStopNoReconfig >= 1) || (gTestStartStopCfg.numStartStopReconfig >= 1))
    {
        System_printf ("------------------------------\n"); 
        System_printf("Start/Stop test ended.\n");
        System_printf("Number of start/stop without reconfiguration %d\n", gTestStartStopCfg.numStartStopNoReconfig);
        System_printf("Number of start/stop with    reconfiguration %d\n", gTestStartStopCfg.numStartStopReconfig);
        
        if(startStopTestPassFlag)
        {
            MCPI_setFeatureTestResult ("Start/Stop Test", MCPI_TestResult_PASS);
        }
        else
        {
            MCPI_setFeatureTestResult ("Start/Stop Test", MCPI_TestResult_FAIL);
        }        
    }

}

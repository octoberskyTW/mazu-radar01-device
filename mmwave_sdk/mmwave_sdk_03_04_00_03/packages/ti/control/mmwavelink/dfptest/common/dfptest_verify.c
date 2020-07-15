/*
 *   @file  dfptest_verify.c
 *
 *   @brief
 *      Implements DFP test verification functions
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

/**************************************************************************
 ************************** Globals *************************
 **************************************************************************/

extern dfpTestMCB_t gTestMCB;
extern volatile uint32_t gLatentFaultReportReceived; 

/*Holds number of reports received per monitoring feature. Internally used by the testbench*/
uint16_t monAeCnt [MMWAVELINK_TEST_MAX_NUM_MON] = { 0 };

/*Informs if test passed/failed during real-time validation of monitoring reports. Internally used by the testbench*/
bool     monTestPassFlag;

//#define DEBUG_VERIFY 

/**************************************************************************
 ************************** Functions *************************
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
        monAeCnt[i] = 0;
    }
}

int32_t MmwaveLink_verifyReportCount(void)
{
    uint32_t i, numRep;
    int32_t retVal = 0;
    char testname[64];
    uint8_t reportMode;
    
    if(gTestMiscCfg.testAdvancedFrame == false)
    {
        numRep = frameCfg.numFrames / calMonTimeUnitConf.calibMonTimeUnit;
    }
    else
    {
        /*From ICD: One FTTI can have multiple frames in legacy frame configuration or in advanced frame configuration
          - each frame can have multiple sub-frames and each sub-frame can have multiple bursts.*/
        numRep = advFrameCfg.frameSeq.numFrames / calMonTimeUnitConf.calibMonTimeUnit;
    }
    
    /* Check that for each enabled monitoring feature all reports have been received and
       no reports were generated for the features that were not enabled.*/
    for(i = 0; i < MMWAVELINK_TEST_MAX_NUM_MON; i++)
    {
        switch(i)
        {        
            case 0:
                 sprintf(&testname[0], "MON_TEMP");
                 reportMode = tempMonCfg.reportMode; 
            break;
            case 1:            
                sprintf(&testname[0],"MON_RX_GAIN_PH        "); 
                reportMode = rxGainPhaseMonCfg.reportMode; 
            break;
            case 2:            
                sprintf(&testname[0],"MON_RX_NOISE_FIG      "); 
                reportMode = rxNoiseMonCfg.reportMode; 
            break;
            case 3:            
                sprintf(&testname[0],"MON_RX_IF_STAGE       "); 
                reportMode = monRxIfStageCfg.reportMode; 
            break;
            case 4:            
                sprintf(&testname[0],"MON_TX0_POWER         "); 
                reportMode  = tx0PowMonCfg.reportMode;
            break;
            case 5:            
                sprintf(&testname[0],"MON_TX1_POWER         "); 
                reportMode  = tx1PowMonCfg.reportMode;
            break;
            case 6:            
                sprintf(&testname[0],"MON_TX2_POWER         "); 
                reportMode  = tx2PowMonCfg.reportMode;
            break;
            case 7:            
                sprintf(&testname[0],"MON_TX0_BALL_BRK      "); 
                reportMode = tx0BallBreakMonCfg.reportMode;
            break;
            case 8:            
                sprintf(&testname[0],"MON_TX1_BALL_BRK      "); 
                reportMode = tx1BallBreakMonCfg.reportMode;
            break;
            case 9:            
                sprintf(&testname[0],"MON_TX2_BALL_BRK      "); 
                reportMode = tx2BallBreakMonCfg.reportMode;
            break;
            case 10:            
                sprintf(&testname[0],"MON_TX_GAIN_PHASE     "); 
                reportMode = txGainPhMisMatchMonCfg.reportMode; 
            break;
            case 11:            
                sprintf(&testname[0],"MON_TX0_BPM           "); 
                reportMode = tx0BpmMonCfg.reportMode;
            break;
            case 12:            
                sprintf(&testname[0],"MON_TX1_BPM           "); 
                reportMode = tx1BpmMonCfg.reportMode;
            break;
            case 13:            
                sprintf(&testname[0],"MON_TX2_BPM           "); 
                reportMode = tx2BpmMonCfg.reportMode;
            break;
            case 14:            
                sprintf(&testname[0],"MON_SYNTHESIZER_FREQ  "); 
                reportMode = synthFreqMonCfg.reportMode; 
            break;
            case 15:            
                sprintf(&testname[0],"MON_EXTERN_ANALOG_SIG "); 
                reportMode = extAnaSigMonCfg.reportMode; 
            break;
            case 16:            
                sprintf(&testname[0],"MON_TX0_INT_ANA_SIG   "); 
                reportMode = tx0IntAnaSigMonCfg.reportMode;
            break;
            case 17:            
                sprintf(&testname[0],"MON_TX1_INT_ANA_SIG   "); 
                reportMode = tx1IntAnaSigMonCfg.reportMode;
            break;
            case 18:            
                sprintf(&testname[0],"MON_TX2_INT_ANA_SIG   "); 
                reportMode = tx2IntAnaSigMonCfg.reportMode;
            break;
            case 19:            
                sprintf(&testname[0],"MON_INT_RX_SIG        "); 
                reportMode = rxIntAnaSigMonCfg.reportMode; 
            break;
            case 20:            
                sprintf(&testname[0],"MON_INT_PMCLKLO_SIG   ");  
                reportMode = pmClkLoIntAnaSigMonCfg.reportMode; 
            break;
            case 21:            
                sprintf(&testname[0],"MON_INT_GPADC_SIG     "); 
                reportMode = gpadcIntAnaSigMonCfg.reportMode; 
            break;
            case 22:            
                sprintf(&testname[0],"MON_PLL_CONTROL_VOLT  "); 
                reportMode = pllConVoltMonCfg.reportMode; 
            break;
            case 23:            
                sprintf(&testname[0],"MON_DCC_CLOCK_FREQ    "); 
                reportMode = dualClkCompMonCfg.reportMode; 
            break;
            case 24:            
                sprintf(&testname[0],"MON_RX_IF_SATURATION  "); 
            break;
            case 25:            
                sprintf(&testname[0],"MON_RX_SIG_IMG_BAND   "); 
            break;
            case 26:            
                sprintf(&testname[0],"MON_RX_MIXER_INP_POWER"); 
                reportMode = rxMixInpwrMonCfg.reportMode; 
            break;
            default :            
                sprintf(&testname[0],"ERROR: UNDEFINED FEATURE"); 
            break;
        }    
    
        if(i < MMWAVELINK_TEST_MAX_NUM_ANALOG_MON_REP)
        {
            /* This IF covers all analog monitors */    
            if(monAnaEnables.enMask & (1 << i))
            {
                //printf("checking %d\n",i);
                if(reportMode == MON_REPORT_MODE_AT_FAILURE_ONLY)
                {
                    /*Is this test configured to fail this monitoring feature?*/
                    if(gTestMiscCfg.failFeatureMask & (1 << i))
                    {
                        if(monAeCnt[i] != numRep)
                        {
                            System_printf("Error Monitoring feature %s: expected %d reports (induced failure). Received %d.\n",testname , numRep, monAeCnt[i]);
                            retVal = -1;
                        }
                        else
                        {            
                            System_printf("[Debug]: Received %d reports for monitoring feature %s\n",monAeCnt[i], testname);
                        }
                    }
                    else
                    {
                        if(monAeCnt[i] != 0)
                        {
                            System_printf("Error Monitoring feature %s: expected 0 reports (reportMode = 1). Received %d.\n",
                                           testname , monAeCnt[i]);
                            retVal = -1;
                        }
                        else
                        {            
                            System_printf("[Debug]: Received Zero reports for monitoring feature %s\n", testname);
                        }
                    }    
                }
                else
                {
                    if(monAeCnt[i] != numRep)
                    {
                        System_printf("Error Monitoring feature %s: expected %d reports. Received %d.\n",testname , numRep, monAeCnt[i]);
                        retVal = -1;
                    }
                    else
                    {            
                        System_printf("[Debug]: Received %d reports for monitoring feature %s\n",monAeCnt[i], testname);
                    }
                }    
            }
            else
            {
                //printf("skip %d\n",i);
                /* This report was not enabled. */
                if(monAeCnt[i] != 0)
                {
                    System_printf("Error Analog Monitoring feature %s: expected zero reports. Received %d.\n", testname, monAeCnt[i]);
                    retVal = -1;
                }    
            }
        }    
        else if(i == MMWAVELINK_TEST_MON_REPORT_HEADER)
        {
            //printf("checking header %d\n",i);
            /* This is the report header. Should only be sent when at least one report is enabled*/
            if(monAnaEnables.enMask != 0)
            {
                if(monAeCnt[i] != numRep)
                {
                    System_printf("Error report header: expected %d reports. Received %d.\n", numRep, monAeCnt[i]);
                    retVal = -1;
                }
                else
                {            
                    System_printf("[Debug]: Received %d report headers.\n",monAeCnt[i]);
                }    
            }    
            else
            {
                /* No report was enabled. Should have not received any report header*/
                if(monAeCnt[i] != 0)
                {
                    System_printf("Error: report header received. But no report was enabled. Number of received reports %d\n", monAeCnt[i]);
                    retVal = -1;
                }
            } 
        }
        else if(i == MMWAVELINK_TEST_MON_DIG_LATENT_FAULT)
        {
            /* This is digital latent fault. */
            //printf("checking digital latent fault %d\n",i);
            if(monDigEnables.enMask != 0)
            {
                if(monAeCnt[i] != gTestMiscCfg.numLatentFaultAfterFrameStop)
                {
                    System_printf("Error Digital latent fault report: expected %d reports. Received %d.\n", 
                                  gTestMiscCfg.numLatentFaultAfterFrameStop, monAeCnt[i]);
                    retVal = -1;
                }
                else
                {            
                    System_printf("[Debug]: Received %d reports for Digital latent fault.\n",monAeCnt[i]);
                }    
            } 
            else
            {
                /* No digital report was enabled. Should have not received any report*/
                if(monAeCnt[i] != 0)
                {
                    System_printf("Error: Digital latent fault report received. But no digital report was enabled. Number of received reports %d\n", monAeCnt[i]);
                    retVal = -1;
                }
            } 
        }
        else if(i == MMWAVELINK_TEST_MON_DIG_PERIODIC_REP)
        {
            /* This is digital periodic report. */
            //printf("checking digital periodic report %d\n",i);
            if(monDigPeriodicCfg.periodicEnableMask != 0)
            {
                if(monAeCnt[i] != numRep)
                {
                    System_printf("Error Digital periodic report: expected %d reports. Received %d.\n", numRep, monAeCnt[i]);
                    retVal = -1;
                }
                else
                {            
                    System_printf("[Debug]: Received %d reports for Digital periodic report.\n",monAeCnt[i]);
                }    
            } 
            else
            {
                /* No digital report was enabled. Should have not received any report*/
                if(monAeCnt[i] != 0)
                {
                    System_printf("Error: Digital periodic report received. But no digital periodic report was enabled. Number of received reports %d\n", monAeCnt[i]);
                    retVal = -1;
                }
            } 
        }
        else if(i == MMWAVELINK_TEST_CALIBRATION_REP)
        {
            /* This is periodic calibration report. */
            System_printf("[Debug]: Received %d reports for periodic calibration.\n",monAeCnt[i]);
        } 
        else
        {
            //printf("checking remaining counters %d\n",i);
            /* This counter is not used, should not have any non-zero value. */
            if(monAeCnt[i] != 0)
            {
                System_printf("Error: expected zero counter on position %d. Counter value is %d.\n", i, monAeCnt[i]);
                retVal = -1;
            }    
        }
    }        
    
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      Checks the status flags of different reports
 *
 *  @retval
 *      Not Applicable.
 */
int32_t MmwaveLink_checkStatusFlag 
(
    char *verifyApiName, 
    rlUInt8_t  reportMode, 
    rlUInt16_t statusFlags, 
    rlUInt16_t expectedStatusWithoutThresholdCheck, 
    rlUInt16_t expectedStatusWithThresholdCheck,
    uint32_t   monitoringFeatureIndex
)
{
    if(reportMode == MON_REPORT_MODE_PERIODIC_WITHOUT_THRESHOLD_CHECK)
    {
        if(statusFlags != expectedStatusWithoutThresholdCheck)
        {
            monTestPassFlag = false;
            System_printf("Error: %s rep->statusFlags = 0x%x. Expected value is 0x%x. Frame number %d.\n", verifyApiName,
                          statusFlags, expectedStatusWithoutThresholdCheck, gTestMCB.frameCnt);
            return -1;              
        }
    }
    else if(reportMode == MON_REPORT_MODE_AT_FAILURE_ONLY)
    {
        /*Is this test configured to fail this monitoring feature?*/
        if(gTestMiscCfg.failFeatureMask & (1 << monitoringFeatureIndex ))
        {
            /*Check if status flag matches the expected induced failure*/
            if(statusFlags != gTestMiscCfg.failStatusFlag[monitoringFeatureIndex])
            {
                monTestPassFlag = false;
                System_printf("Error: %s rep->statusFlags = 0x%x. Expected value is 0x%x (induced failure). Frame number %d.\n",
                              verifyApiName, statusFlags, gTestMiscCfg.failStatusFlag[monitoringFeatureIndex], gTestMCB.frameCnt);
                return -1;
            }
        }
        else
        {
        
            System_printf("Error: %s Received report with rep->statusFlags = 0x%x. This is reportMode 1, no reports expected.  Frame number %d.\n", verifyApiName,
                          statusFlags, gTestMCB.frameCnt);
            return -1;
        }    
    }
    else if(reportMode == MON_REPORT_MODE_PERIODIC_WITH_THRESHOLD_CHECK)
    {

        /*Is this test configured to fail this monitoring feature?*/
        if(gTestMiscCfg.failFeatureMask & (1 << monitoringFeatureIndex ))
        {
            /*Check if status flag matches the expected induced failure*/
            if(statusFlags != gTestMiscCfg.failStatusFlag[monitoringFeatureIndex])
            {
                monTestPassFlag = false;
                System_printf("Error: %s rep->statusFlags = 0x%x. Expected value is 0x%x (induced failure). Frame number %d.\n",
                              verifyApiName, statusFlags, gTestMiscCfg.failStatusFlag[monitoringFeatureIndex], gTestMCB.frameCnt);
                return -1;
            }
        }
        else
        {
            if(statusFlags != expectedStatusWithThresholdCheck)
            {
                monTestPassFlag = false;
                System_printf("Error: %s rep->statusFlags = 0x%x. Expected value is 0x%x. Frame number %d.\n",
                              verifyApiName, statusFlags, expectedStatusWithThresholdCheck, gTestMCB.frameCnt);
                return -1;
            }
        }    
    }
    else
    {
        monTestPassFlag = false;
        System_printf("Error: %s reportMode = %d is invalid.  Frame number %d.\n", verifyApiName, reportMode, gTestMCB.frameCnt);
        return -1;
    }
    return 0;
}

/**
 *  @b Description
 *  @n
 *      Verification of Temperature report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyTemperatureRep(rlMonTempReportData_t *rep)
{
    uint32_t i;
    int32_t retVal;

    monAeCnt[MMWAVELINK_TEST_MON_TEMP]++;

    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyTemperatureRep\n");
    System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
    System_printf("errorCode     = %d\n",rep->errorCode);
    for(i=0; i<10; i++)
        System_printf("tempValues[%d]    = %d\n",i,rep->tempValues[i]);
    System_printf("timeStamp     = %d\n",rep->timeStamp);
    #endif

    retVal = MmwaveLink_checkStatusFlag ("MmwaveLink_verifyTemperatureRep", tempMonCfg.reportMode, 
                                        rep->statusFlags, 0, 0x1F, MMWAVELINK_TEST_MON_TEMP);

    if(retVal < 0)
    {
        System_printf("MmwaveLink_verifyTemperatureRep\n");
        System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
        System_printf("errorCode     = %d\n",rep->errorCode);
        for(i=0; i<10; i++)
            System_printf("tempValues[%d]    = %d\n",i,rep->tempValues[i]);
        System_printf("timeStamp     = %d\n",rep->timeStamp);
    }

    if(rep->errorCode != 0)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyTemperatureRep: errorCode = %d. Expected value is zero.\n",rep->errorCode);
    }    
    
    for(i=0; i<10; i++)
    {
        if(rep->tempValues[i] > DFPTEST_MAX_TEMP)
        {
            monTestPassFlag = false;
            System_printf("tempValues[%d] = %d exceeds the max allowed value %d.\n",i,rep->tempValues[i],DFPTEST_MAX_TEMP);
        }    
        if(rep->tempValues[i] < DFPTEST_MIN_TEMP)
        {
            monTestPassFlag = false;
            System_printf("tempValues[%d] = %d is lower than min allowed value %d.\n",i,rep->tempValues[i],DFPTEST_MIN_TEMP);
        }    
    }    
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
    uint8_t zeroIndex[12];
    int32_t retVal;
    
    monAeCnt[MMWAVELINK_TEST_MON_RX_GAIN_PH]++;
        
#ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyRxGainPhRep\n");
    System_printf("statusFlags      = 0x%x\n",rep->statusFlags);
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

    retVal = MmwaveLink_checkStatusFlag ("MmwaveLink_verifyRxGainPhRep", rxGainPhaseMonCfg.reportMode, 
                                        rep->statusFlags, 0, 0xF, MMWAVELINK_TEST_MON_RX_GAIN_PH);
                                
    if(retVal < 0)
    {
        System_printf("MmwaveLink_verifyRxGainPhRep\n");
        System_printf("statusFlags      = 0x%x\n",rep->statusFlags);
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
    }
    
    if(rep->errorCode != 0)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRxGainPhRep: errorCode = %d. Expeceted value is zero.\n",rep->errorCode);
    }    
    
    if(rep->profIndex != rxGainPhaseMonCfg.profileIndx)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRxGainPhRep: profIndex = %d. Expected value is %d\n",rep->profIndex, rxGainPhaseMonCfg.profileIndx);
    }    

    /* Bytes populated for each combination of RF and RX channel
    
                         RF1     RF2     RF3 \n
                 RX0     1:0     9:8     17:16 \n
                 RX1     3:2     11:10   19:18 \n
                 RX2     5:4     13:12   21:20 \n
                 RX3     7:6     15:14   23:22 \n
    */    
    
    memset((void*)zeroIndex, 1, 12 * sizeof(uint8_t));
    
    if(RX_CHANNEL_1_ENABLE & chCfg.rxChannelEn)
    {
        /*RX0 is enabled therefore do not need to check for zeroes for RX0.
          Note that the report comes as an array of 12 uint16*/
          
        if(rxGainPhaseMonCfg.rfFreqBitMask & 0x1)  
            zeroIndex[0]=0;//RF1 is enabled, so no need to check for zeros for RX0 and RF1
        if(rxGainPhaseMonCfg.rfFreqBitMask & 0x2)  
            zeroIndex[4]=0;
        if(rxGainPhaseMonCfg.rfFreqBitMask & 0x4)  
            zeroIndex[8]=0;
    }

    if(RX_CHANNEL_2_ENABLE & chCfg.rxChannelEn)
    {
        if(rxGainPhaseMonCfg.rfFreqBitMask & 0x1)  
            zeroIndex[1]=0;
        if(rxGainPhaseMonCfg.rfFreqBitMask & 0x2)  
            zeroIndex[5]=0;
        if(rxGainPhaseMonCfg.rfFreqBitMask & 0x4)  
            zeroIndex[9]=0;
    }

    if(RX_CHANNEL_3_ENABLE & chCfg.rxChannelEn)
    {
        if(rxGainPhaseMonCfg.rfFreqBitMask & 0x1)  
            zeroIndex[2]=0;
        if(rxGainPhaseMonCfg.rfFreqBitMask & 0x2)  
            zeroIndex[6]=0;
        if(rxGainPhaseMonCfg.rfFreqBitMask & 0x4)  
            zeroIndex[10]=0;
    }

    if(RX_CHANNEL_4_ENABLE & chCfg.rxChannelEn)
    {
        if(rxGainPhaseMonCfg.rfFreqBitMask & 0x1)  
            zeroIndex[3]=0;
        if(rxGainPhaseMonCfg.rfFreqBitMask & 0x2)  
            zeroIndex[7]=0;
        if(rxGainPhaseMonCfg.rfFreqBitMask & 0x4)  
            zeroIndex[11]=0;
    }
    
    for(i=0; i<12; i++)
    {
        if(zeroIndex[i])
        {         
            if(rep->rxGainVal[i] != 0)
            {
                monTestPassFlag = false;
                System_printf("Error MmwaveLink_verifyRxGainPhRep: rxGainVal[%d] = 0x%x. Expected value is zero.\n",i,rep->rxGainVal[i]);
            }
            if(rep->rxPhaseVal[i] != 0)
            {
                monTestPassFlag = false;
                System_printf("Error MmwaveLink_verifyRxGainPhRep: rxPhaseVal[%d] = 0x%x. Expected value is zero.\n",i,rep->rxPhaseVal[i]);
            }                
        }    
    }        

    if(rep->loopbackPowerRF1 > DFPTEST_MAX_LOOPBACK_POWER_RF1)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRxGainPhRep: loopbackPowerRF1 = %d is greater than max allowed value %d\n",
        rep->loopbackPowerRF1, DFPTEST_MAX_LOOPBACK_POWER_RF1);
    }    

    if(rep->loopbackPowerRF2 > DFPTEST_MAX_LOOPBACK_POWER_RF2)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRxGainPhRep: loopbackPowerRF2 = %d is greater than max allowed value %d\n",
        rep->loopbackPowerRF2, DFPTEST_MAX_LOOPBACK_POWER_RF2);
    }    

    if(rep->loopbackPowerRF3 > DFPTEST_MAX_LOOPBACK_POWER_RF3)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRxGainPhRep: loopbackPowerRF3 = %d is greater than max allowed value %d\n",
        rep->loopbackPowerRF3, DFPTEST_MAX_LOOPBACK_POWER_RF3);
    }    

    if(rep->rxNoisePower1 > DFPTEST_MAX_RX_NOISE_POWER1)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRxGainPhRep: rxNoisePower1 = %d is greater than max allowed value %d\n",
        rep->rxNoisePower1, DFPTEST_MAX_RX_NOISE_POWER1);
    }    

    if(rep->rxNoisePower2 > DFPTEST_MAX_RX_NOISE_POWER2)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRxGainPhRep: rxNoisePower2 = %d is greater than max allowed value %d\n",
        rep->rxNoisePower2, DFPTEST_MAX_RX_NOISE_POWER2);
    }    
    
}

/**
 *  @b Description
 *  @n
 *      Verification of RX noise figure report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyRxNoiseFigRep(rlMonRxNoiseFigRep_t *rep)
{
    int32_t retVal;
    uint32_t i;
    
    monAeCnt[MMWAVELINK_TEST_MON_RX_NOISE_FIG]++;

    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyRxNoiseFigRep\n");
    System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
    System_printf("errorCode     = %d\n",rep->errorCode);
    System_printf("profIndex     = %d\n",rep->profIndex);
    for(i=0; i<12; i++)
        System_printf("rxNoiseFigVal[%d]    = %d\n",i,rep->rxNoiseFigVal[i]);
    System_printf("timeStamp     = %d\n",rep->timeStamp);
    #endif

    retVal = MmwaveLink_checkStatusFlag ("MmwaveLink_verifyRxNoiseFigRep", rxNoiseMonCfg.reportMode, 
                                        rep->statusFlags, 0, 0x1, MMWAVELINK_TEST_MON_RX_NOISE_FIG);

    if(retVal < 0)
    {
        System_printf("MmwaveLink_verifyRxNoiseFigRep\n");
        System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
        System_printf("errorCode     = %d\n",rep->errorCode);
        System_printf("profIndex     = %d\n",rep->profIndex);
        for(i=0; i<12; i++)
            System_printf("rxNoiseFigVal[%d]    = %d\n",i,rep->rxNoiseFigVal[i]);
        System_printf("timeStamp     = %d\n",rep->timeStamp);
    }
                                        
    if(rep->errorCode != 0)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRxNoiseFigRep: errorCode = %d. Expected value is zero.\n",rep->errorCode);
    }    
    
    if(rep->profIndex != rxNoiseMonCfg.profileIndx)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRxNoiseFigRep: profIndex = %d. Expected value is %d\n",rep->profIndex, rxNoiseMonCfg.profileIndx);
    }    
    
    for(i=0; i<12; i++)
    {
        if(rep->rxNoiseFigVal[i] > DFPTEST_MAX_RX_NOISE_FIG_VAL)
        {
            monTestPassFlag = false;
            System_printf("Error MmwaveLink_verifyRxNoiseFigRep: rep->rxNoiseFigVal[%d] = %d is outside the valid range.\n",
                          i, rep->rxNoiseFigVal[i]);
        }
    }         
}                    

/**
 *  @b Description
 *  @n
 *      Verification of RX IF stage report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyRxIfStageRep(rlMonRxIfStageRep_t *rep)
{
    uint32_t i;
    uint8_t zeroIndex[8];
    int32_t retVal;

    monAeCnt[MMWAVELINK_TEST_MON_RX_IF_STAGE]++;

    #ifdef DEBUG_VERIFY    
    System_printf("MmwaveLink_verifyRxIfStageRep\n");
    System_printf("statusFlags      = 0x%x\n",rep->statusFlags);
    System_printf("errorCode        = %d\n",rep->errorCode);
    System_printf("profIndex        = %d\n",rep->profIndex);
    for(i=0; i<8; i++)
        System_printf("hpfCutOffFreqEr[%d]    = %d\n",i,rep->hpfCutOffFreqEr[i]);
    for(i=0; i<8; i++)
        System_printf("lpfCutOffFreqEr[%d]    = %d\n",i,rep->lpfCutOffFreqEr[i]);
    for(i=0; i<8; i++)
        System_printf("rxIfaGainErVal[%d]    = %d\n",i,rep->rxIfaGainErVal[i]);
    System_printf("ifGainExp        = %d\n",rep->ifGainExp);
    System_printf("timeStamp        = %d\n",rep->timeStamp);
    #endif

    retVal = MmwaveLink_checkStatusFlag ("MmwaveLink_verifyRxIfStageRep", monRxIfStageCfg.reportMode, 
                                        rep->statusFlags, 0, 0x7, MMWAVELINK_TEST_MON_RX_IF_STAGE);
                                
    if(retVal < 0)
    {
        System_printf("MmwaveLink_verifyRxIfStageRep\n");
        System_printf("statusFlags      = 0x%x\n",rep->statusFlags);
        System_printf("errorCode        = %d\n",rep->errorCode);
        System_printf("profIndex        = %d\n",rep->profIndex);
        for(i=0; i<8; i++)
            System_printf("hpfCutOffFreqEr[%d]    = %d\n",i,rep->hpfCutOffFreqEr[i]);
        for(i=0; i<8; i++)
            System_printf("lpfCutOffFreqEr[%d]    = %d\n",i,rep->lpfCutOffFreqEr[i]);
        for(i=0; i<8; i++)
            System_printf("rxIfaGainErVal[%d]    = %d\n",i,rep->rxIfaGainErVal[i]);
        System_printf("ifGainExp        = %d\n",rep->ifGainExp);
        System_printf("timeStamp        = %d\n",rep->timeStamp);
    }
    
    if(rep->errorCode != 0)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRxIfStageRep: errorCode = %d. Expected value is zero.\n",rep->errorCode);
    }    
    
    if(rep->profIndex != monRxIfStageCfg.profileIndx)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRxIfStageRep: profIndex = %d. Expected value is %d \n",rep->profIndex, monRxIfStageCfg.profileIndx);
    }    
    
    /*report is given in a uint8_ array with the following mapping
                      I channel   Q channel 
                 RX0     0           4 
                 RX1     1           5 
                 RX2     2           6 
                 RX3     3           7 
    */
    memset((void*)zeroIndex, 1, 8 * sizeof(uint8_t));
    
    if(RX_CHANNEL_1_ENABLE & chCfg.rxChannelEn)
    {
        /*RX0 is enabled therefore do not need to check for zeroes for RX0.
          Note that the report comes as an array of 12 uint16*/
        zeroIndex[0]=0;
        zeroIndex[4]=0;
    }

    if(RX_CHANNEL_2_ENABLE & chCfg.rxChannelEn)
    {
        zeroIndex[1]=0;
        zeroIndex[5]=0;
    }

    if(RX_CHANNEL_3_ENABLE & chCfg.rxChannelEn)
    {
        zeroIndex[2]=0;
        zeroIndex[6]=0;
    }

    if(RX_CHANNEL_4_ENABLE & chCfg.rxChannelEn)
    {
        zeroIndex[3]=0;
        zeroIndex[7]=0;
    }
    
    for(i = 0; i < 8; i++)
    {
        if(zeroIndex[i])
        {         
            if(rep->hpfCutOffFreqEr[i] != 0)
            {
                monTestPassFlag = false;
                System_printf("Error MmwaveLink_verifyRxIfStageRep: hpfCutOffFreqEr[%d] = 0x%x.  Expected value is zero.\n",i,rep->hpfCutOffFreqEr[i]);
            }
            if(rep->rxIfaGainErVal[i] != 0)
            {
                monTestPassFlag = false;
                System_printf("Error MmwaveLink_verifyRxIfStageRep: rxIfaGainErVal[%d] = 0x%x.  Expected value is zero.\n",i,rep->rxIfaGainErVal[i]);
            }                
        }    
    }        

}                    

/**
 *  @b Description
 *  @n
 *      Verification of TX power report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyTxPower(rlMonTxPowRep_t *rep, uint32_t txAntReportIndex)
{
    uint32_t antNum, i;
    uint8_t  expectedProfileIndex, reportMode, rfFreqBitMask;
    int32_t retVal;
    
    monAeCnt[txAntReportIndex]++;

    if(txAntReportIndex == MMWAVELINK_TEST_MON_TX0_POWER)
    {
        antNum = 0;
        expectedProfileIndex = tx0PowMonCfg.profileIndx;
        reportMode           = tx0PowMonCfg.reportMode;
        rfFreqBitMask        = tx0PowMonCfg.rfFreqBitMask;
    }    
    else if(txAntReportIndex == MMWAVELINK_TEST_MON_TX1_POWER)
    {
        antNum = 1;
        expectedProfileIndex = tx1PowMonCfg.profileIndx;
        reportMode           = tx1PowMonCfg.reportMode;
        rfFreqBitMask        = tx1PowMonCfg.rfFreqBitMask;
    }    
    else
    {
        antNum = 2;
        expectedProfileIndex = tx2PowMonCfg.profileIndx;
        reportMode           = tx2PowMonCfg.reportMode;
        rfFreqBitMask        = tx2PowMonCfg.rfFreqBitMask;
    }    

    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyTxPower\n");
    System_printf("TX antenna %d\n",antNum);
    System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
    System_printf("errorCode     = %d\n",rep->errorCode);
    System_printf("profIndex     = %d\n",rep->profIndex);
    for(i=0; i<3; i++)
        System_printf("txPowVal[%d]    = %d\n",i,rep->txPowVal[i]);
    System_printf("timeStamp     = %d\n",rep->timeStamp);    
    #endif

    retVal = MmwaveLink_checkStatusFlag ("MmwaveLink_verifyTxPower", reportMode, 
                                        rep->statusFlags, 0, 0x3, txAntReportIndex);

    if(retVal < 0)
    {
        System_printf("MmwaveLink_verifyTxPower\n");
        System_printf("TX antenna %d\n",antNum);
        System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
        System_printf("errorCode     = %d\n",rep->errorCode);
        System_printf("profIndex     = %d\n",rep->profIndex);
        for(i=0; i<3; i++)
            System_printf("txPowVal[%d]    = %d\n",i,rep->txPowVal[i]);
        System_printf("timeStamp     = %d\n",rep->timeStamp);    
    }

    if(rep->errorCode != 0)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyTxPower ant %d: errorCode = %d. Expected value is zero.\n",antNum, rep->errorCode);
    }    
    
    if(rep->profIndex != expectedProfileIndex)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyTxPower antenna %d: received profIndex = %d expected profIndex = %d\n",
        antNum, rep->profIndex, expectedProfileIndex);
    }    

    /* If a frequency band is not enabled, report should be zero 
                       RF1     RF2     RF3 \n
               TX      1:0     3:2     5:4 \n
    */
    for(i=0; i<3; i++)
    {
        if(!(rfFreqBitMask & (1 << i)))
        {
            /* i=0 ==> RF1 mon is not enabled, etc */
            if(rep->txPowVal[i] != 0)
            {
                System_printf("Error MmwaveLink_verifyTxPower antenna %d: received txPowVal = %d. Expected value is zero.\n",
                antNum, rep->txPowVal[i]);
            } 
        }
    }    
    
    
    for(i=0; i<3; i++)
    {
        if(rep->txPowVal[i] > DFPTEST_MAX_TXPOWER)
        {
            monTestPassFlag = false;
            System_printf("txPowVal[%d] = %d exceeds the max allowed value %d.\n",i,rep->txPowVal[i],DFPTEST_MAX_TXPOWER);
        }    
        if(rep->txPowVal[i] < DFPTEST_MIN_TXPOWER)
        {
            monTestPassFlag = false;
            System_printf("txPowVal[%d] = %d is lower than min allowed value %d.\n",i,rep->txPowVal[i],DFPTEST_MIN_TXPOWER);
        }    
    }    
    
}                    

/**
 *  @b Description
 *  @n
 *      Verification of TX Ball break report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyTxBallBreak(rlMonTxBallBreakRep_t *rep, uint32_t txAntReportIndex)
{
    uint32_t antNum;
    uint8_t  reportMode;
    int32_t  retVal;
    
    monAeCnt[txAntReportIndex]++;

    if(txAntReportIndex == MMWAVELINK_TEST_MON_TX0_BALL_BRK)
    {
        antNum = 0;
        reportMode = tx0BallBreakMonCfg.reportMode;
    }    
    else if(txAntReportIndex == MMWAVELINK_TEST_MON_TX1_BALL_BRK)
    {
        antNum = 1;
        reportMode = tx1BallBreakMonCfg.reportMode;
    }    
    else
    {
        antNum = 2;
        reportMode = tx2BallBreakMonCfg.reportMode;
    }    

    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyTxBallBreak\n");
    System_printf("TX antenna %d\n",antNum);
    System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
    System_printf("errorCode     = %d\n",rep->errorCode);
    System_printf("txReflCoefVal = %d\n",rep->txReflCoefVal);
    System_printf("timeStamp     = %d\n",rep->timeStamp);    
    #endif
    
    retVal = MmwaveLink_checkStatusFlag ("MmwaveLink_verifyTxBallBreak", reportMode, 
                                         rep->statusFlags, 0, 0x1, txAntReportIndex);
                                         
    if(retVal < 0)
    {
        System_printf("MmwaveLink_verifyTxBallBreak\n");
        System_printf("TX antenna %d\n",antNum);
        System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
        System_printf("errorCode     = %d\n",rep->errorCode);
        System_printf("txReflCoefVal = %d\n",rep->txReflCoefVal);
        System_printf("timeStamp     = %d\n",rep->timeStamp);    
    }
    
    if(rep->errorCode != 0)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyTxBallBreak ant %d: errorCode = %d. Expected value is zero.\n",antNum, rep->errorCode);
    }    
    
    if(rep->txReflCoefVal > DFPTEST_MAX_TX_REFL_COEFF_THRESH)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyTxBallBreak ant %d:txReflCoefVal = %d exceeds the max allowed value %d.\n", rep->txReflCoefVal, DFPTEST_MAX_TX_REFL_COEFF_THRESH);
    }    
    
    if(rep->txReflCoefVal < DFPTEST_MIN_TX_REFL_COEFF_THRESH)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyTxBallBreak ant %d:txReflCoefVal = %d is less than the min allowed value %d.\n", rep->txReflCoefVal, DFPTEST_MIN_TX_REFL_COEFF_THRESH);
    }    
}                    

void MmwaveLink_checkTxGainPhaseVal(rlMonTxGainPhaMisRep_t *rep, uint8_t index)
{
        if(rep->txGainVal[index] != 0)
        {
            monTestPassFlag = false;
            System_printf("Error MmwaveLink_verifyTxGainPhaseRep: received txGainVal[%d] = %d. Expected value is zero.\n",
            index, rep->txGainVal[index]);
        } 
        if(rep->txPhaVal[index] != 0)
        {
            monTestPassFlag = false;
            System_printf("Error MmwaveLink_verifyTxGainPhaseRep: received txPhaVal[%d] = %d. Expected value is zero.\n",
            index, rep->txPhaVal[index]);
        } 
}

/**
 *  @b Description
 *  @n
 *      Verification of TX gain phase report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyTxGainPhaseRep(rlMonTxGainPhaMisRep_t *rep)
{
    int32_t retVal;
    uint32_t i;
    
    monAeCnt[MMWAVELINK_TEST_MON_TX_GAIN_PHASE]++;

    #ifdef DEBUG_VERIFY    
    System_printf("MmwaveLink_verifyTxGainPhaseRep\n");
    System_printf("statusFlags      = 0x%x\n",rep->statusFlags);
    System_printf("errorCode        = %d\n",rep->errorCode);
    System_printf("profIndex        = %d\n",rep->profIndex);
    System_printf("timeStamp        = %d\n",rep->timeStamp);
    for(i=0; i<9; i++)
        System_printf("txGainVal[%d]    = %d\n",i,rep->txGainVal[i]);
    for(i=0; i<9; i++)
        System_printf("txPhaVal[%d]    = %d\n",i,rep->txPhaVal[i]);    
    #endif

    retVal = MmwaveLink_checkStatusFlag ("MmwaveLink_verifyTxGainPhaseRep", txGainPhMisMatchMonCfg.reportMode, 
                                        rep->statusFlags, 0, 0x3, MMWAVELINK_TEST_MON_TX_GAIN_PHASE);
                                
    if(retVal < 0)
    {
        System_printf("MmwaveLink_verifyTxGainPhaseRep\n");
        System_printf("statusFlags      = 0x%x\n",rep->statusFlags);
        System_printf("errorCode        = %d\n",rep->errorCode);
        System_printf("profIndex        = %d\n",rep->profIndex);
        System_printf("timeStamp        = %d\n",rep->timeStamp);
        for(i=0; i<9; i++)
            System_printf("txGainVal[%d]    = %d\n",i,rep->txGainVal[i]);
        for(i=0; i<9; i++)
            System_printf("txPhaVal[%d]    = %d\n",i,rep->txPhaVal[i]);    
    }
        
        if(rep->errorCode != 0)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyTxGainPhaseRep: errorCode = %d. Expected value is zero.\n",rep->errorCode);
    }    
    
    if(rep->profIndex != txGainPhMisMatchMonCfg.profileIndx)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyTxGainPhaseRep: profIndex = %d. Expected value is %d \n",rep->profIndex, txGainPhMisMatchMonCfg.profileIndx);
    }    

    /* Check if the corresponding TX channel and RF band is enabled. If not enabled, report must be zero.
                        RF1        RF2          RF3 \n
                TX0     1:0[0]     7:6  [3]   13:12 [6] \n
                TX1     3:2[1]     9:8  [4]   15:14 [7] \n
                TX2     5:4[2]     11:10[5]   17:16 [8] \n
    */
    
    if(!(txGainPhMisMatchMonCfg.txEn & 0x1))
    {    
        /*TX0 is not enabled*/
        MmwaveLink_checkTxGainPhaseVal(rep, 0);
        MmwaveLink_checkTxGainPhaseVal(rep, 3);
        MmwaveLink_checkTxGainPhaseVal(rep, 6);    
    }

    if(!(txGainPhMisMatchMonCfg.txEn & 0x2))
    {    
        /*TX1 is not enabled*/
        MmwaveLink_checkTxGainPhaseVal(rep, 1);
        MmwaveLink_checkTxGainPhaseVal(rep, 4);
        MmwaveLink_checkTxGainPhaseVal(rep, 7);    
    }

    if(!(txGainPhMisMatchMonCfg.txEn & 0x4))
    {    
        /*TX2 is not enabled*/
        MmwaveLink_checkTxGainPhaseVal(rep, 2);
        MmwaveLink_checkTxGainPhaseVal(rep, 5);
        MmwaveLink_checkTxGainPhaseVal(rep, 8);    
    }
    
    if(!(txGainPhMisMatchMonCfg.rfFreqBitMask & 0x1))
    {
        /*RF1 is not enabled*/
        MmwaveLink_checkTxGainPhaseVal(rep, 0);
        MmwaveLink_checkTxGainPhaseVal(rep, 1);
        MmwaveLink_checkTxGainPhaseVal(rep, 2);    
    }

    if(!(txGainPhMisMatchMonCfg.rfFreqBitMask & 0x2))
    {
        /*RF2 is not enabled*/
        MmwaveLink_checkTxGainPhaseVal(rep, 3);
        MmwaveLink_checkTxGainPhaseVal(rep, 4);
        MmwaveLink_checkTxGainPhaseVal(rep, 5);    
    }
    
    if(!(txGainPhMisMatchMonCfg.rfFreqBitMask & 0x4))
    {
        /*RF3 is not enabled*/
        MmwaveLink_checkTxGainPhaseVal(rep, 6);
        MmwaveLink_checkTxGainPhaseVal(rep, 7);
        MmwaveLink_checkTxGainPhaseVal(rep, 8);    
    }

}

/**
 *  @b Description
 *  @n
 *      Verification of TX BPM report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyTxBpm(rlMonTxBpmRep_t *rep, uint32_t txAntReportIndex)
{
    uint32_t antNum;
    uint8_t  expectedProfileIndex, reportMode;
    int32_t retVal;
    
    monAeCnt[txAntReportIndex]++;

    if(txAntReportIndex == MMWAVELINK_TEST_MON_TX0_BPM)
    {
        antNum = 0;
        expectedProfileIndex = tx0BpmMonCfg.profileIndx;
        reportMode           = tx0BpmMonCfg.reportMode;
    }    
    else if(txAntReportIndex == MMWAVELINK_TEST_MON_TX1_BPM)
    {
        antNum = 1;
        expectedProfileIndex = tx1BpmMonCfg.profileIndx;
        reportMode           = tx1BpmMonCfg.reportMode;
    }    
    else
    {
        antNum = 2;
        expectedProfileIndex = tx2BpmMonCfg.profileIndx;
        reportMode           = tx2BpmMonCfg.reportMode;
    }    

    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyTxBpm\n");
    System_printf("TX antenna %d\n",antNum);
    System_printf("statusFlags            = 0x%x\n",rep->statusFlags);
    System_printf("errorCode              = %d\n",rep->errorCode);
    System_printf("profIndex              = %d\n",rep->profIndex);
    System_printf("phaseShifterMonVal2Lsb = %d\n",rep->phaseShifterMonVal2Lsb);
    System_printf("phaseShifterMonVal2Msb = %d\n",rep->phaseShifterMonVal2Msb);
    System_printf("phaseShifterMonVal2    = %d in degrees\n",(rep->phaseShifterMonVal2Msb*(1<<8)+rep->phaseShifterMonVal2Lsb)*360/(1<<16));
    System_printf("phaseShifterMonVal1    = %d in degrees = %d\n",rep->phaseShifterMonVal1, (rep->phaseShifterMonVal1*360)/(1<<16));    
    System_printf("txBpmPhaDiff           = %d\n",rep->txBpmPhaDiff);
    System_printf("txBpmAmpDiff           = %d\n",rep->txBpmAmpDiff);
    System_printf("timeStamp              = %d\n",rep->timeStamp);
    #endif

    retVal = MmwaveLink_checkStatusFlag ("MmwaveLink_verifyTxBpm", reportMode, 
                                        rep->statusFlags, 0, 0x7, txAntReportIndex);

    if(retVal < 0)
    {
        System_printf("MmwaveLink_verifyTxBpm\n");
        System_printf("TX antenna %d\n",antNum);
        System_printf("statusFlags            = 0x%x\n",rep->statusFlags);
        System_printf("errorCode              = %d\n",rep->errorCode);
        System_printf("profIndex              = %d\n",rep->profIndex);
        System_printf("phaseShifterMonVal2Lsb = %d\n",rep->phaseShifterMonVal2Lsb);
        System_printf("phaseShifterMonVal2Msb = %d\n",rep->phaseShifterMonVal2Msb);
        System_printf("phaseShifterMonVal2    = %d in degrees\n",(rep->phaseShifterMonVal2Msb*(1<<8)+rep->phaseShifterMonVal2Lsb)*360/(1<<16));
        System_printf("phaseShifterMonVal1    = %d in degrees = %d\n",rep->phaseShifterMonVal1, (rep->phaseShifterMonVal1*360)/(1<<16));    
        System_printf("txBpmPhaDiff           = %d\n",rep->txBpmPhaDiff);
        System_printf("txBpmAmpDiff           = %d\n",rep->txBpmAmpDiff);
        System_printf("timeStamp              = %d\n",rep->timeStamp);
    }
                                        
    if(rep->errorCode != 0)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyTxBpm ant %d: errorCode = %d. Expected value is zero.\n",antNum, rep->errorCode);
    }    
    
    if(rep->profIndex != expectedProfileIndex)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyTxBpm antenna %d: received profIndex = %d expected profIndex = %d\n",
        antNum, rep->profIndex, expectedProfileIndex);
    }    
}    

/**
 *  @b Description
 *  @n
 *      Verification of RF synth freq report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyRfSynthFreqRep(rlMonSynthFreqRep_t *rep)
{
    int32_t retVal;

    monAeCnt[MMWAVELINK_TEST_MON_SYNTHESIZER_FREQ]++;

    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyRfSynthFreqRep\n");
    System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
    System_printf("errorCode     = %d\n",rep->errorCode);
    System_printf("profIndex     = %d\n",rep->profIndex);
    System_printf("maxFreqErVal  = %d\n",rep->maxFreqErVal);
    System_printf("freqFailCnt   = %d\n",rep->freqFailCnt);    
    System_printf("timeStamp     = %d\n",rep->timeStamp);
    #endif
    
    retVal = MmwaveLink_checkStatusFlag ("MmwaveLink_verifyRfSynthFreqRep", synthFreqMonCfg.reportMode, 
                                        rep->statusFlags, 0, 0x1, MMWAVELINK_TEST_MON_SYNTHESIZER_FREQ);

    if(retVal < 0)
    {
        System_printf("MmwaveLink_verifyRfSynthFreqRep\n");
        System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
        System_printf("errorCode     = %d\n",rep->errorCode);
        System_printf("profIndex     = %d\n",rep->profIndex);
        System_printf("maxFreqErVal  = %d\n",rep->maxFreqErVal);
        System_printf("freqFailCnt   = %d\n",rep->freqFailCnt);    
        System_printf("timeStamp     = %d\n",rep->timeStamp);
    }
    
    if(rep->errorCode != 0)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRfSynthFreqRep: errorCode = %d\n",rep->errorCode);
    }    
    
    if(rep->profIndex != synthFreqMonCfg.profileIndx)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRfSynthFreqRep: received profIndex = %d. Expected %d\n",rep->profIndex, synthFreqMonCfg.profileIndx);
    }    

    /*Is this test configured to fail this monitoring feature?*/
    if(gTestMiscCfg.failFeatureMask & (1 << MMWAVELINK_TEST_MON_SYNTHESIZER_FREQ ))
    {
        /*Test should fail*/
        if(rep->freqFailCnt == 0)
        {
            monTestPassFlag = false;
            System_printf("Error MmwaveLink_verifyRfSynthFreqRep: freqFailCnt = 0. Expected greater than zero because test is configured to fail.\n");
        }
    }
    else
    {    
        /*Test should pass*/
        if(rep->freqFailCnt != 0)
        {
            monTestPassFlag = false;
            System_printf("Error MmwaveLink_verifyRfSynthFreqRep: freqFailCnt = %d. Expected 0.\n",rep->freqFailCnt);
        }
    }       
    
    if(rep->maxFreqErVal > DFPTEST_MAX_FREQ_ERR_VAL)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRfSynthFreqRep: maxFreqErVal = %d exceeds the max allowed value %d.\n", rep->maxFreqErVal, DFPTEST_MAX_FREQ_ERR_VAL);
    }    
    
    if(rep->maxFreqErVal < DFPTEST_MIN_FREQ_ERR_VAL)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRfSynthFreqRep: maxFreqErVal = %d is less than the min allowed value %d.\n", rep->maxFreqErVal, DFPTEST_MIN_FREQ_ERR_VAL);
    }    
}                    

/**
 *  @b Description
 *  @n
 *      Verification of External Analog Signals report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyExtAnalogSigRep(rlMonExtAnaSigRep_t *rep)
{
    uint32_t i;
    int32_t retVal;

    monAeCnt[MMWAVELINK_TEST_MON_EXTERN_ANALOG_SIG]++;

    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyExtAnalogSigRep\n");
    System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
    System_printf("errorCode     = %d\n",rep->errorCode);
    System_printf("timeStamp     = %d\n",rep->timeStamp);
    for(i=0; i<6; i++)
        System_printf("extAnaSigVal[%d]    = %d\n",i,rep->extAnaSigVal[i]);
    #endif

    /* Configuration:
                     Bit Location  SIGNAL \n
                     0         ANALOGTEST1 \n
                     1         ANALOGTEST2 \n
                     2         ANALOGTEST3 \n
                     3         ANALOGTEST4 \n
                     4         ANAMUX \n
                     5         VSENSE \n
                     Others    RESERVED \n
    rlUInt8_t  signalInpEnables;
    
      Report:
      Status flags indicating pass fail results corresponding \n
                     to various threshold checks under this monitor. \n
                     Bit  STATUS_FLAG for monitor \n
                     0    STATUS_ANALOGTEST1 \n
                     1    STATUS_ANALOGTEST2 \n
                     2    STATUS_ANALOGTEST3 \n
                     3    STATUS_ANALOGTEST4 \n
                     4    STATUS_ANAMUX \n
                     5    STATUS_VSENSE \n
                     15:3 RESERVED \n
                     0 - FAIL or check wasn't done, 1 - PASS  \n
    rlUInt16_t statusFlags;
    */

    retVal = MmwaveLink_checkStatusFlag ("MmwaveLink_verifyExtAnalogSigRep", extAnaSigMonCfg.reportMode, 
                                        rep->statusFlags, 0, extAnaSigMonCfg.signalInpEnables, MMWAVELINK_TEST_MON_EXTERN_ANALOG_SIG);
                                
    if(retVal < 0)
    {
        System_printf("MmwaveLink_verifyExtAnalogSigRep\n");
        System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
        System_printf("errorCode     = %d\n",rep->errorCode);
        System_printf("timeStamp     = %d\n",rep->timeStamp);
        for(i=0; i<6; i++)
            System_printf("extAnaSigVal[%d]    = %d\n",i,rep->extAnaSigVal[i]);
    }
    
    if(rep->errorCode != 0)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyExtAnalogSigRep: errorCode = %d\n",rep->errorCode);
    }    
    
    for(i=0; i<6; i++)
    {
        if(rep->extAnaSigVal[i] > DFPTEST_MAX_EXTERNSIGVAL)
        {
            monTestPassFlag = false;
            System_printf("Error MmwaveLink_verifyExtAnalogSigRep:extAnaSigVal[%d] = %d exceeds the max allowed value %d.\n",i,rep->extAnaSigVal[i],DFPTEST_MAX_EXTERNSIGVAL);
        }    
        if(rep->extAnaSigVal[i] < DFPTEST_MIN_EXTERNSIGVAL)
        {
            monTestPassFlag = false;
            System_printf("Error MmwaveLink_verifyExtAnalogSigRep:extAnaSigVal[%d] = %d is lower than min allowed value %d.\n",i,rep->extAnaSigVal[i],DFPTEST_MIN_EXTERNSIGVAL);
        }    
    }    
    
}                    

/**
 *  @b Description
 *  @n
 *      Verification of RF synth freq report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyRfTxIntAnaSignals(rlMonTxIntAnaSigRep_t *rep, uint32_t txAntReportIndex)
{
    uint32_t antNum;
    uint8_t  expectedProfileIndex, reportMode;
    int32_t retVal;
    
    monAeCnt[txAntReportIndex]++;

    if(txAntReportIndex == MMWAVELINK_TEST_MON_TX0_INT_ANA_SIG)
    {
        antNum = 0;
        expectedProfileIndex = tx0IntAnaSigMonCfg.profileIndx;
        reportMode           = tx0IntAnaSigMonCfg.reportMode;
    }    
    else if(txAntReportIndex == MMWAVELINK_TEST_MON_TX1_INT_ANA_SIG)
    {
        antNum = 1;
        expectedProfileIndex = tx1IntAnaSigMonCfg.profileIndx;
        reportMode           = tx1IntAnaSigMonCfg.reportMode;
    }    
    else
    {
        antNum = 2;
        expectedProfileIndex = tx2IntAnaSigMonCfg.profileIndx;
        reportMode           = tx2IntAnaSigMonCfg.reportMode;
    }    

    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyRfTxIntAnaSignals\n");
    System_printf("TX antenna %d\n",antNum);
    System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
    System_printf("errorCode     = %d\n",rep->errorCode);
    System_printf("profIndex     = %d\n",rep->profIndex);
    System_printf("timeStamp     = %d\n",rep->timeStamp);
    #endif

    retVal = MmwaveLink_checkStatusFlag ("MmwaveLink_verifyRfTxIntAnaSignals", reportMode, 
                                       rep->statusFlags, 0, 0x3, txAntReportIndex);
                                       
    if(retVal < 0)
    {
        System_printf("MmwaveLink_verifyRfTxIntAnaSignals\n");
        System_printf("TX antenna %d\n",antNum);
        System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
        System_printf("errorCode     = %d\n",rep->errorCode);
        System_printf("profIndex     = %d\n",rep->profIndex);
        System_printf("timeStamp     = %d\n",rep->timeStamp);
    }
                                  
    if(rep->errorCode != 0)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRfTxIntAnaSignals ant %d: errorCode = %d. Expected value is zero.\n",antNum, rep->errorCode);
    }    
    
    if(rep->profIndex != expectedProfileIndex)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRfTxIntAnaSignals antenna %d: received profIndex = %d expected profIndex = %d\n",
        antNum, rep->profIndex, expectedProfileIndex);
    }    

    
}                    

/**
 *  @b Description
 *  @n
 *      Verification of RX internal Analog Signals report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyRxIntAnaSigRep(rlMonRxIntAnaSigRep_t *rep)
{
    int32_t retVal;

    monAeCnt[MMWAVELINK_TEST_MON_INT_RX_SIG]++;

    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyRxIntAnaSigRep\n");
    System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
    System_printf("errorCode     = %d\n",rep->errorCode);
    System_printf("profIndex     = %d\n",rep->profIndex);
    System_printf("timeStamp     = %d\n",rep->timeStamp);
    #endif
    
    retVal = MmwaveLink_checkStatusFlag ("MmwaveLink_verifyRxIntAnaSigRep", rxIntAnaSigMonCfg.reportMode, 
                                       /* Mask off reserved bits */(0xFF) & (rep->statusFlags), 0, 0xFF, 
                                       MMWAVELINK_TEST_MON_INT_RX_SIG);
                                  
    if(retVal < 0)
    {
        System_printf("MmwaveLink_verifyRxIntAnaSigRep\n");
        System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
        System_printf("errorCode     = %d\n",rep->errorCode);
        System_printf("profIndex     = %d\n",rep->profIndex);
        System_printf("timeStamp     = %d\n",rep->timeStamp);
    }
    
    if(rep->errorCode != 0)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRxIntAnaSigRep: errorCode = %d. Expected value is zero.\n",rep->errorCode);
    }    
    
    if(rep->profIndex != rxIntAnaSigMonCfg.profileIndx)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRxIntAnaSigRep: profIndex = %d. Expected value is %d \n",rep->profIndex, rxIntAnaSigMonCfg.profileIndx);
    }    
}                    

/**
 *  @b Description
 *  @n
 *      Verification of PM Signals report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyIntPmClkLoSigRep(rlMonPmclkloIntAnaSigRep_t *rep)
{
    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyIntPmClkLoSigRep\n");
    System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
    System_printf("errorCode     = %d\n",rep->errorCode);
    System_printf("profIndex     = %d\n",rep->profIndex);
    System_printf("sync20GPower  = %d\n",rep->sync20GPower);
    System_printf("timeStamp     = %d\n",rep->timeStamp);
    #endif
    
    /*b2 STATUS LVDS PMCLKLO:Use this status bit only if LVDS is used, else ignore this.
      Therefore, we are ignoring b2.
      Also ignore failure reports (in report mode 1) when only b2 is set as failed*/      
    if((pmClkLoIntAnaSigMonCfg.reportMode != MON_REPORT_MODE_AT_FAILURE_ONLY) ||
       ((pmClkLoIntAnaSigMonCfg.reportMode == MON_REPORT_MODE_AT_FAILURE_ONLY) && (rep->statusFlags != 0x3 /*only b2 failed*/)))
    {       
        monAeCnt[MMWAVELINK_TEST_MON_INT_PMCLKLO_SIG]++;
        MmwaveLink_checkStatusFlag ("MmwaveLink_verifyIntPmClkLoSigRep", pmClkLoIntAnaSigMonCfg.reportMode, 
                                   rep->statusFlags, 0, 0x3, MMWAVELINK_TEST_MON_INT_PMCLKLO_SIG);
    }   
    
    if(rep->errorCode != 0)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyIntPmClkLoSigRep: errorCode = %d. Expected value is zero.\n",rep->errorCode);
    }    
    
    if(rep->profIndex != pmClkLoIntAnaSigMonCfg.profileIndx)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyIntPmClkLoSigRep: profIndex = %d. Expected value is %d \n",rep->profIndex, pmClkLoIntAnaSigMonCfg.profileIndx);
    }    
    
}   
                 
/**
 *  @b Description
 *  @n
 *      Verification of GPADC Signals report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyIntGpadcSigRep(rlMonGpadcIntAnaSigRep_t *rep)
{
    int32_t retVal;
    
    monAeCnt[MMWAVELINK_TEST_MON_INT_GPADC_SIG]++;

    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyIntGpadcSigRep\n");
    System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
    System_printf("errorCode     = %d\n",rep->errorCode);
    System_printf("gpadcRef1Val  = %d\n",rep->gpadcRef1Val);
    System_printf("gpadcRef2Val  = %d\n",rep->gpadcRef2Val);
    System_printf("timeStamp     = %d\n",rep->timeStamp);
    #endif
    
    retVal = MmwaveLink_checkStatusFlag ("MmwaveLink_verifyIntGpadcSigRep", gpadcIntAnaSigMonCfg.reportMode, 
                                        rep->statusFlags, 0, 0x3, MMWAVELINK_TEST_MON_INT_GPADC_SIG);

    if(retVal < 0)
    {
        System_printf("MmwaveLink_verifyIntGpadcSigRep\n");
        System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
        System_printf("errorCode     = %d\n",rep->errorCode);
        System_printf("gpadcRef1Val  = %d\n",rep->gpadcRef1Val);
        System_printf("gpadcRef2Val  = %d\n",rep->gpadcRef2Val);
        System_printf("timeStamp     = %d\n",rep->timeStamp);
    }
    
    if(rep->errorCode != 0)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyIntGpadcSigRep: errorCode = %d. Expected value is zero.\n",rep->errorCode);
    }        
    
    if(rep->gpadcRef1Val > DFPTEST_MAX_GPADCREF1VAL)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyIntGpadcSigRep: gpadcRef1Val = %d is out of valid range.\n",rep->gpadcRef1Val);
    }        
    
    if(rep->gpadcRef2Val > DFPTEST_MAX_GPADCREF2VAL)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyIntGpadcSigRep: gpadcRef2Val = %d is out of valid range.\n",rep->gpadcRef2Val);
    }        

}        
            
/**
 *  @b Description
 *  @n
 *      Verification of PLL control report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyPllControlRep(rlMonPllConVoltRep_t *rep)
{
    uint16_t expectedStatus = 0;
    int32_t retVal;
    uint32_t i;
    
    monAeCnt[MMWAVELINK_TEST_MON_PLL_CONTROL_VOLT]++;

    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyPllControlRep\n");
    System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
    System_printf("errorCode     = %d\n",rep->errorCode);
    for(i=0; i<8; i++)
        System_printf("pllContVoltVal[%d]    = %d\n",i,rep->pllContVoltVal[i]);
    System_printf("timeStamp     = %d\n",rep->timeStamp);
    #endif

    /*expected value of status flag depends on what was enabled on signalEnables:
    signalEnables bitfields:
                            Bit Location   SIGNAL \n
                            0          APLL_VCTRL \n
                            1          SYNTH_VCO1_VCTRL \n
                            2          SYNTH_VCO2_VCTRL \n
                            
      Status flags indicating pass fail results corresponding to various threshold \n
                     checks under this monitor. \n
                     Bit      STATUS_FLAG for monitor \n
                     0        STATUS_APLL_VCTRL \n
                     1        STATUS_SYNTH_VCO1_VCTRL_MAX_ FREQ \n
                     2        STATUS_SYNTH_VCO1_VCTRL_MIN_ FREQ \n
                     3        STATUS_SYNTH_VCO1_SLOPE \n
                     4        STATUS_SYNTH_VCO2_VCTRL_MAX_ FREQ \n
                     5        STATUS_SYNTH_VCO2_VCTRL_MIN_ FREQ \n
                     6        STATUS_SYNTH_VCO2_SLOPE \n
                     15:7    RESERVED \n
                     0 - FAIL or check wasn't done, 1 - PASS \n
                        
    */
    if(pllConVoltMonCfg.signalEnables & 0x1)
    {
        expectedStatus += (1 << 0);
    }
    if(pllConVoltMonCfg.signalEnables & 0x2)
    {
        expectedStatus += (1 << 1);
        expectedStatus += (1 << 2);
        expectedStatus += (1 << 3);
    }
    if(pllConVoltMonCfg.signalEnables & 0x4)
    {
        expectedStatus += (1 << 4);
        expectedStatus += (1 << 5);
        expectedStatus += (1 << 6);
    }
    
    retVal = MmwaveLink_checkStatusFlag ("MmwaveLink_verifyPllControlRep", pllConVoltMonCfg.reportMode, 
                                        rep->statusFlags, 0, expectedStatus, MMWAVELINK_TEST_MON_PLL_CONTROL_VOLT);

    if(retVal < 0)
    {
        System_printf("MmwaveLink_verifyPllControlRep\n");
        System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
        System_printf("errorCode     = %d\n",rep->errorCode);
        for(i=0; i<8; i++)
            System_printf("pllContVoltVal[%d]    = %d\n",i,rep->pllContVoltVal[i]);
        System_printf("timeStamp     = %d\n",rep->timeStamp);
    }
    
    if(rep->errorCode != 0)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyPllControlRep: errorCode = %d. Expected value is zero.\n",rep->errorCode);
    }    
    
    /* From doxygen:
        i-index
                     Bytes   SIGNAL                              1 LSB \n
        0             1:0     APLL_VCTRL                          1mV  \n
        1             3:2     SYNTH_VCO1_VCTRL_MAX_ FREQ          1mV \n
        2             5:4     SYNTH_VCO1_VCTRL_MIN_ FREQ          1mV \n
        3             7:6     SYNTH_VCO1_SLOPE                    1MHz/V \n
        4             9:8     SYNTH_VCO2_VCTRL_MAX_ FREQ          1mV \n
        5             11:10   SYNTH_VCO2_VCTRL_MIN_ FREQ          1mV \n
        6             13:12   SYNTH_VCO2_SLOPE                    1MHz/V \n
        7             15:14   RESERVED                            RESERVED \n
                     Only the fields corresponding to the enabled monitors are valid.  \n
                     The failure thresholds are based on the following: \n
                     Valid VCTRL values are [140 to 1400] mV. \n
                     Valid VCO1_SLOPE values are [1760 to 2640] MHz/V. \n
                     Valid VCO2_SLOPE values are [3520 to 5280] MHz/V. \n
    */ 

    if(pllConVoltMonCfg.signalEnables & 0x1)
    {
        if((rep->pllContVoltVal[0] > 1400) || (rep->pllContVoltVal[0] < 140))
        {
            monTestPassFlag = false;
            System_printf("Error MmwaveLink_verifyPllControlRep: pllContVoltVal[0] = %d out of range.\n",rep->pllContVoltVal[0]);
        }
    }    
    
    if(pllConVoltMonCfg.signalEnables & 0x2)
    {
        if((rep->pllContVoltVal[1] > 1400) || (rep->pllContVoltVal[1] < 140))
        {
            monTestPassFlag = false;
            System_printf("Error MmwaveLink_verifyPllControlRep: pllContVoltVal[1] = %d out of range.\n",rep->pllContVoltVal[1]);
        }    
        
        if((rep->pllContVoltVal[2] > 1400) || (rep->pllContVoltVal[2] < 140))
        {
            monTestPassFlag = false;
            System_printf("Error MmwaveLink_verifyPllControlRep: pllContVoltVal[2] = %d out of range.\n",rep->pllContVoltVal[2]);
        }    
        
        if((rep->pllContVoltVal[3] > 2640) || (rep->pllContVoltVal[3] < 1760))
        {
            monTestPassFlag = false;
            System_printf("Error MmwaveLink_verifyPllControlRep: pllContVoltVal[3] = %d out of range.\n",rep->pllContVoltVal[3]);
        }    
    }    
        
    if(pllConVoltMonCfg.signalEnables & 0x4)
    {
        if((rep->pllContVoltVal[4] > 1400) || (rep->pllContVoltVal[4] < 140))
        {
            monTestPassFlag = false;
            System_printf("Error MmwaveLink_verifyPllControlRep: pllContVoltVal[4] = %d out of range.\n",rep->pllContVoltVal[4]);
        }    
        
        if((rep->pllContVoltVal[5] > 1400) || (rep->pllContVoltVal[5] < 140))
        {
            monTestPassFlag = false;
            System_printf("Error MmwaveLink_verifyPllControlRep: pllContVoltVal[5] = %d out of range.\n",rep->pllContVoltVal[5]);
        }    
        
        if((rep->pllContVoltVal[6] > 5280) || (rep->pllContVoltVal[6] < 3520))
        {
            monTestPassFlag = false;
            System_printf("Error MmwaveLink_verifyPllControlRep: pllContVoltVal[6] = %d out of range.\n",rep->pllContVoltVal[6]);
        }    
    }
}                    

/**
 *  @b Description
 *  @n
 *      Verification of DCC clock frequency report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyDccClockFreqRep(rlMonDccClkFreqRep_t *rep)
{
    uint32_t i, mask;

    monAeCnt[MMWAVELINK_TEST_MON_DCC_CLOCK_FREQ]++;

    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyDccClockFreqRep\n");
    System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
    System_printf("errorCode     = %d\n",rep->errorCode);
    for(i=0; i<8; i++)
        System_printf("freqMeasVal[%d]    = %d\n",i,rep->freqMeasVal[i]);
    System_printf("timeStamp     = %d\n",rep->timeStamp);
    #endif

    #if 0//failing in mode zero, JIRA opened MMWL-213
    MmwaveLink_checkStatusFlag ("MmwaveLink_verifyDccClockFreqRep", dualClkCompMonCfg.reportMode, 
                               rep->statusFlags, 0, dualClkCompMonCfg.dccPairEnables, MMWAVELINK_TEST_MON_DCC_CLOCK_FREQ);
    #endif                           

    /*print extra info in case of status flag error and threshold check (non-zero status flag)*/
    if((dualClkCompMonCfg.reportMode == MON_REPORT_MODE_PERIODIC_WITH_THRESHOLD_CHECK) &&
       (rep->statusFlags != dualClkCompMonCfg.dccPairEnables))
    {
        for(i = 0; i < 6; i++)
        {    
            mask = (1 << i);
            if((mask & rep->statusFlags) != (mask & dualClkCompMonCfg.dccPairEnables))
            {
                System_printf("Bit position %d (index starts from zero) received value is %d expected value is 0x%x\n", i,
                (mask & rep->statusFlags), (mask & dualClkCompMonCfg.dccPairEnables));
            }
        }
    }        

    if(rep->errorCode != 0)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyDccClockFreqRep: errorCode = %d. Expected value is zero.\n",rep->errorCode);
    }    
    
    for(i=0; i<8; i++)
    {
        if(rep->freqMeasVal[i] > DFPTEST_MAX_DCCFREQVAL)
        {
            monTestPassFlag = false;
            System_printf("Error MmwaveLink_verifyDccClockFreqRep: freqMeasVal[%d] = %d exceeds the max allowed value %d.\n",i,rep->freqMeasVal[i],DFPTEST_MAX_DCCFREQVAL);
        }    
    }        
    
}                    

/**
 *  @b Description
 *  @n
 *      Verification of RX mixer input power report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyRxMixInpPowerRep(rlMonRxMixrInPwrRep_t *rep)
{
    uint32_t i,mask;
    uint8_t zeroIndex[4];
    uint8_t *rxMixInVoltPtr;
    int32_t retVal;
    
    monAeCnt[MMWAVELINK_TEST_MON_RX_MIXER_INP_POWER]++;

    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyRxMixInpPowerRep\n");
    System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
    System_printf("errorCode     = %d\n",rep->errorCode);
    System_printf("profIndex     = %d\n",rep->profIndex);
    System_printf("rxMixInVolt   = %d\n",rep->rxMixInVolt);
    System_printf("timeStamp     = %d\n",rep->timeStamp);
    #endif
    
    /*From doxygen: Only the RX channels enabled in the static configuration APIs are monitored. */
    retVal = MmwaveLink_checkStatusFlag ("MmwaveLink_verifyRxMixInpPowerRep", rxMixInpwrMonCfg.reportMode, 
                                        rep->statusFlags, 0, chCfg.rxChannelEn, MMWAVELINK_TEST_MON_RX_MIXER_INP_POWER);

    if(retVal < 0)
    {
        System_printf("MmwaveLink_verifyRxMixInpPowerRep\n");
        System_printf("statusFlags   = 0x%x\n",rep->statusFlags);
        System_printf("errorCode     = %d\n",rep->errorCode);
        System_printf("profIndex     = %d\n",rep->profIndex);
        System_printf("rxMixInVolt   = %d\n",rep->rxMixInVolt);
        System_printf("timeStamp     = %d\n",rep->timeStamp);
    }
    
    /*Is this test configured to fail this monitoring feature?*/
    if(!(gTestMiscCfg.failFeatureMask & (1 << MMWAVELINK_TEST_MON_RX_MIXER_INP_POWER)))
    {
        /*print extra info in case of status flag error and threshold check (non-zero status flag)*/
        if((rxMixInpwrMonCfg.reportMode == MON_REPORT_MODE_PERIODIC_WITH_THRESHOLD_CHECK) &&
           (rep->statusFlags != chCfg.rxChannelEn))
        {
            for(i = 0; i < 6; i++)
            {    
                mask = (1 << i);
                if((mask & rep->statusFlags) != (mask & chCfg.rxChannelEn))
                {
                    System_printf("MmwaveLink_verifyRxMixInpPowerRep: Bit position %d (index starts from zero) received value is %d expected value is 0x%x\n", i,
                    (mask & rep->statusFlags), (mask & chCfg.rxChannelEn));
                }
            }
        }
    }        

    if(rep->errorCode != 0)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRxMixInpPowerRep: errorCode = %d. Expected value is zero.\n",rep->errorCode);
    }    
    
    if(rep->profIndex != rxMixInpwrMonCfg.profileIndx)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRxMixInpPowerRep: profIndex = %d. Expected value is %d \n",rep->profIndex, rxMixInpwrMonCfg.profileIndx);
    }    
    
     /*        Byte location \n
                Rx0  0  \n
                Rx1  1  \n
                Rx2  2  \n
                Rx3  3  \n
                1 LSB = 1800 mV/256, unsigned number \n
                Only the entries of enabled RX channels are valid. \n
     */
    memset((void*)zeroIndex, 1, 4 * sizeof(uint8_t));

    if(RX_CHANNEL_1_ENABLE & chCfg.rxChannelEn)
    {
        /*RX0 is enabled therefore do not need to check for zeroes for RX0.*/
        zeroIndex[0]=0;
    }
    if(RX_CHANNEL_2_ENABLE & chCfg.rxChannelEn)
    {
        zeroIndex[1]=0;
    }
    if(RX_CHANNEL_3_ENABLE & chCfg.rxChannelEn)
    {
        zeroIndex[2]=0;
    }
    if(RX_CHANNEL_4_ENABLE & chCfg.rxChannelEn)
    {
        zeroIndex[3]=0;
    }

    rxMixInVoltPtr = (uint8_t*)&(rep->rxMixInVolt);
    for(i = 0; i < 4; i++)
    {
        if(zeroIndex[i])
        {         
            if(rxMixInVoltPtr[i] != 0)
            {
                monTestPassFlag = false;
                System_printf("Error MmwaveLink_verifyRxMixInpPowerRep: rxMixInVolt = 0x%x.  Expected value for byte %d is zero.\n",
                              rep->rxMixInVolt, i);
            }
        }    
    }        
    
}                    

/**
 *  @b Description
 *  @n
 *      Verification of Digital latent fault report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyDigLatFaultRep(rlDigLatentFaultReportData_t *rep)
{
    uint32_t i, mask;
    monAeCnt[MMWAVELINK_TEST_MON_DIG_LATENT_FAULT]++;
    gLatentFaultReportReceived = 1;

    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyDigLatFaultRep\n");
    System_printf("digMonLatentFault   = 0x%x\n",rep->digMonLatentFault);
    #endif

    if(rep->digMonLatentFault != monDigEnables.enMask)
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyDigLatFaultRep: received report = 0x%x. Expected value is 0x%x.\n", rep->digMonLatentFault, monDigEnables.enMask);
        for(i = 0; i < 32; i++)
        {    
            mask = (1 << i);
            if((mask & rep->digMonLatentFault) != (mask & monDigEnables.enMask))
            {
                System_printf("Bit position %d (index starts from zero) received value is %d expected value is 0x%x\n", i,
                (mask & rep->digMonLatentFault), (mask & monDigEnables.enMask));
            }
        }
    }        
}                    


/**
 *  @b Description
 *  @n
 *      Verification of Digital periodic report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyDigPeriodicRep(rlDigPeriodicReportData_t *rep)
{
    uint32_t i, mask;
    monAeCnt[MMWAVELINK_TEST_MON_DIG_PERIODIC_REP]++;

    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyDigPeriodicRep\n");
    System_printf("digMonPeriodicStatus = 0x%x\n",rep->digMonPeriodicStatus);
    System_printf("timeStamp            = %d\n",rep->timeStamp);
    #endif

    /*only bits 0,2,3 are valid and BSS sends internal debug information in reserved bits,
      therefore, mask it with 0xD*/
    if((rep->digMonPeriodicStatus & 0xD) != (monDigPeriodicCfg.periodicEnableMask & 0xD))
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyDigPeriodicRep: received report = 0x%x. Expected value is 0x%x.\n", rep->digMonPeriodicStatus, monDigPeriodicCfg.periodicEnableMask);
        for(i = 0; i < 32; i++)
        {    
            mask = (1 << i);
            if((mask & (rep->digMonPeriodicStatus & 0xD)) != (mask & (monDigPeriodicCfg.periodicEnableMask & 0xD)))
            {
                System_printf("Bit position %d (index starts from zero) received value is %d expected value is 0x%x\n", i,
                (mask & rep->digMonPeriodicStatus), (mask & monDigPeriodicCfg.periodicEnableMask));
            }
        }
    }  
}                    

/**
 *  @b Description
 *  @n
 *      Verification of monitoring report header
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyRepHeader(rlMonReportHdrData_t *rep)
{
    monAeCnt[MMWAVELINK_TEST_MON_REPORT_HEADER]++;

    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyRepHeader\n");
    System_printf("fttiCount = %d\n",rep->fttiCount);
    System_printf("avgTemp   = %d\n",rep->avgTemp);
    #endif

    if(rep->fttiCount != (gTestMCB.previousFttiCount+1))
    {
        monTestPassFlag = false;
        System_printf("Error MmwaveLink_verifyRepHeader: fttiCount = %d previousFttiCount = %d. Increment should be 1.\n",rep->fttiCount, gTestMCB.previousFttiCount);
    }
    else
    {
        gTestMCB.previousFttiCount++;
    }    
    
}                    

/**
 *  @b Description
 *  @n
 *      Verification of runtime calibration report
 *
 *  @retval
 *      Not Applicable.
 */
void MmwaveLink_verifyRunTimeCalibRep(rlRfRunTimeCalibReport_t *rep)
{
    uint32_t enabledReports = 0;
    uint32_t reportedStatus, i;
    
    monAeCnt[MMWAVELINK_TEST_CALIBRATION_REP]++;

    #ifdef DEBUG_VERIFY
    System_printf("MmwaveLink_verifyRunTimeCalibRep\n");
    System_printf("calibErrorFlag    = 0x%x\n",rep->calibErrorFlag);
    System_printf("calibUpdateStatus = 0x%x\n",rep->calibUpdateStatus);
    System_printf("temperature       = %d\n",rep->temperature);
    System_printf("timeStamp         = %d\n",rep->timeStamp);
    #endif

/*
     Periodic calibration enable mask
     runTimeCalib.periodicCalibEnMask:    
     *            0:[Reserved]  \n
     *            1:[Reserved]  \n
     *            2:[Reserved]  \n
     *            3:[Reserved]  \n
     
     *            4: Enable LODIST calibration  \n
     *            5: [Reserved]  \n
     *            6: [Reserved]  \n
     *            7: [Reserved]  \n
     
     *            8: Enable PD_CALIBRATION_EN \n
     *            9: Enable TX Power calibration \n
     *            10:Enable RX gain calibration  \n
     *            11:[Reserved]  \n
     
     *            12:[Reserved]  \n
     *            31:13:[Reserved] \n


    Periodic calibration report:
    1 = calibration is passed, 0 = calibration is failed or not enabled/performed at \n
            least once. \n
            Bit: Calibration \n
            0: [Reserved] \n
            1: APLL tuning \n
            2: SYNTH VCO1 tuning \n
            3: SYNTH VCO2 tuning \n
            
            4: LODIST calibration \n
            5: [Reserved] \n
            6: [Reserved] \n
            7: [Reserved] \n
            
            8: PD calibration \n
            9: TX Power calibration \n
            10: RX gain calibration \n
            11: [Reserved] \n
            
            12: [Reserved] \n
            31:13: [Reserved] \n
     */
     
    enabledReports = runTimeCalib.periodicCalibEnMask;
    
    /*Mask off the reserved bits in the enable mask*/
    enabledReports = enabledReports & 0x710;
    
    /* APLL and SYNTH are always reported*/
    enabledReports |= (1 << 1) | (1 << 2) | (1 << 3);

    reportedStatus = rep->calibErrorFlag;
    
    /*Mask off the reserved bits in calibErrorFlag*/
    reportedStatus = reportedStatus & 0x71E;
    
    /*Check if any of the bits that were enabled returned zero which means failure.
      Should ignore extra bits set to one as this report can set to 1 (pass) bits that
      were enabled in the boot time calibration even if the bit is not enabled for 
      the periodic calibration.*/ 
    for(i = 0; i < 32; i++)
    {
        if(((enabledReports & (1 << i)) == 1) && ((reportedStatus & (1 << i)) == 0))
        {
             monTestPassFlag = false;
             System_printf("Error: MmwaveLink_verifyRunTimeCalibRep bit %d failed.\n", i);
             System_printf("periodicCalibEnMask =%d. Received calibErrorFlag = %d.\n",runTimeCalib.periodicCalibEnMask, rep->calibErrorFlag);
        }        
    }
    
}                    






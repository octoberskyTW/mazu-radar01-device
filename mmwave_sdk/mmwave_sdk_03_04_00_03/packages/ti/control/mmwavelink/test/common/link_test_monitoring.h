/*
 *   @file  link_test_monitoring.h
 *
 *   @brief
 *      Header file for monitoring and calibration APIs
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

#ifndef LINKTESTMON_H
#define LINKTESTMON_H

#ifdef __cplusplus
extern "C" {
#endif

/*Maximum number of different monitoring reports*/
#define MMWAVELINK_TEST_MAX_NUM_MON 40

#define MMWAVELINK_TEST_MON_TEMP       0U
#define MMWAVELINK_TEST_MON_RX_GAIN_PH 1U

/**/

#define MMWAVELINK_TESTCASE_1   1

/**
 * @brief
 *  Monitoring testcases
 *
 * @details
 *  Enumeration that describes the supported 
 *  monitoring testcases
 */
typedef enum MmwaveLink_monTest_e
{
    /**
     * @brief   This test enables only RX1 and checks if the 
     * corresponding reports are received only for RX1
     * Note RX is indexed from zero (RX0, RX1, RX2, RX3)
     */
    MmwaveLink_monTest_1     = 1,

    /**
     * @brief   
     */
    MmwaveLink_monTest_2,
    
    /**
     * @brief   
     */
    MmwaveLink_monTest_none

}MmwaveLink_monTest;



/* Monitoring Report Structures */
typedef struct monitoringDataAe
{
    rlMonTempReportData_t      monTempReport;
    rlMonRxGainPhRep_t         monRxGainPhRep;
    rlMonRxNoiseFigRep_t       monNoiseFigRep;
    rlMonRxIfStageRep_t        monRxIfStageRep;
    rlMonTxPowRep_t            monTx0powRep;
    rlMonTxPowRep_t            monTx1powRep;
    rlMonTxPowRep_t            monTx2powRep;
    rlMonTxBallBreakRep_t      monTx0BallbreakRep;
    rlMonTxBallBreakRep_t      monTx1BallbreakRep;
    rlMonTxBallBreakRep_t      monTx2BallbreakRep;
    rlMonTxGainPhaMisRep_t     monTxGainPhMisMatchRep;
    rlMonTxBpmRep_t            monTx0BpmRep;
    rlMonTxBpmRep_t            monTx1BpmRep;
    rlMonTxBpmRep_t            monTx2BpmRep;
    rlMonSynthFreqRep_t        monSynthFreqRep;
    rlMonExtAnaSigRep_t        monExtAnaSigRep;
    rlMonTxIntAnaSigRep_t      monTx0IntAnaSigRep;
    rlMonTxIntAnaSigRep_t      monTx1IntAnaSigRep;
    rlMonTxIntAnaSigRep_t      monTx2IntAnaSigRep;
    rlMonRxIntAnaSigRep_t      monRxIntAnaSigRep;
    rlMonPmclkloIntAnaSigRep_t monPmClkIntAnaSigRep;
    rlMonGpadcIntAnaSigRep_t   monGpadcIntAnaSigRep;
    rlMonPllConVoltRep_t       monPllConvVoltRep;
    rlMonDccClkFreqRep_t       monDccClkFreqRep;
    rlMonRxMixrInPwrRep_t      monRxMixrInPwrRep;
    rlRfInitComplete_t         monRfInit;
}monitoringDataAe_t;

int32_t MmwaveLink_setCalMonConfig (void);
int32_t MmwaveLink_setInitTimeCalibConfig (int8_t enAllCalib);
int32_t MmwaveLink_setRunTimeCalibConfig (void);
void MmwaveLink_printMonitoringResult(void);
int32_t MmwaveLink_CheckMonitoringReport(uint32_t frameCnt);
int32_t MmwaveLink_monitoring(void);
int32_t MmwaveLink_setRfAnaMonConfigCq (void);
int32_t MmwaveLink_setRfRxIfSatMonConfig (void);
int32_t MmwaveLink_setRfRxSigImgMonConfig (void);

void MmwaveLink_monAdvancedTest(uint8_t platformType, uint8_t platformCore);


void MmwaveLink_verifyRxGainPhRep(rlMonRxGainPhRep_t *rep);

#ifdef __cplusplus
}
#endif

#endif

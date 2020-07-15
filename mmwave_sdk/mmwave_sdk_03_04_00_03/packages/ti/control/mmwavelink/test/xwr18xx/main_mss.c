/*
 *   @file  main_mss.c
 *
 *   @brief
 *      This is the mmWave link unit test which executes on the R4 on
 *      the XWR18xx.
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
#include <ti/sysbios/family/arm/v7r/vim/Hwi.h>

/* mmWave SDK Include Files: */
#include <ti/common/sys_common.h>
#include <ti/drivers/pinmux/pinmux.h>
#include <ti/drivers/osal/DebugP.h>
#include <ti/drivers/esm/esm.h>
#include <ti/drivers/mailbox/mailbox.h>
#include <ti/drivers/adcbuf/ADCBuf.h>
#include <ti/drivers/soc/soc.h>
#include <ti/drivers/crc/crc.h>
#include <ti/control/mmwavelink/mmwavelink.h>
#include <ti/control/mmwavelink/include/rl_driver.h>
#include <ti/utils/testlogger/logger.h>

#include <ti/utils/cycleprofiler/cycle_profiler.h>
#include <ti/control/mmwavelink/test/common/link_testcase_setting.h>
#include <ti/control/mmwavelink/test/common/mmwavelink_test_common.h>

/**************************************************************************
 *************************** Global Variables *****************************
 **************************************************************************/

/**
 * @brief
 *  Initialize the MCPI Log Message Buffer
 */
MCPI_LOGBUF_INIT(9216);

/*RF Monitoring test, this doesn't include cq & cp test*/
bool gLinkMonitoringTest = true;

/*RF calibration test*/
bool gLinkCalibTest      = false;

/*RF Advance frame test*/
bool gLinkAdvanceFrameTest  = false;

/* CQ1 and CQ2 data verification test
    Here is the the flow to verify the CQ1 and CQ2 RAM data
   1. At end of last chirp of last frame application triggers eDMA to transfer CQ1 and CQ2 
      data of single chirp to L3 memory.
   2. After all other test completes application checks for CQ1 data reading from L3 memory. In good 
      condition signal data should be greater than image energy data for given time slices, if it is 
      not true then set error flag.
   3. CQ2 data verification is not covered in this application, but user can verify this by putting another
      EVM running countinous mode of frequency range which cause interference on EVM under test. In case 
      of any interference recieved on EVM under test, CQ2 data will have non-zero values.
*/
/* enable this flag to verify CQ data in this application */
bool cqDataVerifyTest = false;

/* RF Advance frame test
   Note: If gLinkContModeTest is enabled then gLinkMonitoringTest and gLinkCalibTest 
   must be disabled
*/
bool gLinkContModeTest  = false;

/* Dynaic Chirp configuration test */
bool gDynamicChirpTest  = false;

/*Binary phase modulation test*/
bool gLinkBpmEnableTest  = false;

/*RF program filter test*/
bool gLinkProgFiltTest  = false;


/* Sub frame trigger test. Valid when gLinkAdvanceFrameTest flag is enabled */
bool gLinkSubFrameTrigTest = false;

/*frame interrupt Semaphore  */
Semaphore_Handle gLinkFrameSem;
Semaphore_Params gLinkSemParams;


/*! @brief   ADCBUF handle */
ADCBuf_Handle             adcbufHandle;

/**************************************************************************
 ************************* mmWave Link Test Functions *********************
 **************************************************************************/

/**
 *  @b Description
 *  @n
 *      System Initialization Task which initializes the various
 *      components in the system.
 *
 *  @retval
 *      Not Applicable.
 */
static void MmwaveLink_initTask(UArg arg0, UArg arg1)
{
    /* Debug Message: */
    System_printf("Debug: Launched the mmwaveLink Initialization Task\n");

    /* Initialize the test logger framework: */
    MCPI_Initialize();

    /* Initialize the Mailbox */
    Mailbox_init(MAILBOX_TYPE_MSS);

    MmwaveLink_startTest(RL_AR_DEVICETYPE_18XX, RL_PLATFORM_MSS);

    /* Debug Message: */
    System_printf ("******************************************\n");
    System_printf ("Debug: MmwaveLink Test completed\n");
    System_printf ("******************************************\n");

    MCPI_setTestResult ();
    BIOS_exit(0);
    return;
}


/**
 *  @b Description
 *  @n
 *      Entry point into the mmWave Link Unit Test
 *
 *  @retval
 *      Not Applicable.
 */
int32_t main (void)
{
    Task_Params        taskParams;
    int32_t         errCode;
    SOC_Handle      socHandle;
    SOC_Cfg         socCfg;

    /* Initialize the ESM: */
    ESM_init(0U);
    SOC_SysIntListenerCfg    linkFrameCfg;

    /* Initialize the SOC confiugration: */
    memset ((void *)&socCfg, 0, sizeof(SOC_Cfg));

    /* Populate the SOC configuration: */
    socCfg.clockCfg = SOC_SysClock_INIT;

    /* Initialize the SOC Module: This is done as soon as the application is started
     * to ensure that the MPU is correctly configured. */
    socHandle = SOC_init (&socCfg, &errCode);
    if (socHandle == NULL)
    {
        System_printf ("Error: SOC Module Initialization failed [Error code %d]\n", errCode);
        return -1;
    }

    /* Wait for BSS powerup */
    if (SOC_waitBSSPowerUp(socHandle, &errCode) < 0)
    {
        /* Debug Message: */
        System_printf ("Debug: SOC_waitBSSPowerUp failed with Error [%d]\n", errCode);
        return 0;
    }
    ADCBuf_Params       ADCBufparams;
    /*****************************************************************************
     * Initialize ADCBUF driver
     *****************************************************************************/
    ADCBuf_init();

    /* ADCBUF Params initialize */
    ADCBuf_Params_init(&ADCBufparams);
    ADCBufparams.chirpThresholdPing = 1;
    ADCBufparams.chirpThresholdPong = 1;
    ADCBufparams.continousMode  = 0;
    ADCBufparams.socHandle      = socHandle;
    
    adcbufHandle = ADCBuf_open(0, &ADCBufparams);
    if (adcbufHandle == NULL)
    {
        System_printf("Error: Unable to open the ADCBUF Instance\n");
        return -1;
    }
    System_printf("Debug: ADCBUF Instance %p has been reopened successfully\n", adcbufHandle);
    
    Semaphore_Params_init(&gLinkSemParams);
    gLinkSemParams.mode  = Semaphore_Mode_BINARY;
    gLinkFrameSem = Semaphore_create(0, &gLinkSemParams, NULL);
    /* Register frame interrupt */
    memset((void *)&linkFrameCfg, 0 , sizeof(SOC_SysIntListenerCfg));
    linkFrameCfg.systemInterrupt    = SOC_XWR18XX_MSS_FRAME_START_INT;
    linkFrameCfg.listenerFxn        = Mmwavelink_frameInterrupCallBackFunc;
    linkFrameCfg.arg                = (uintptr_t)NULL;
    if ((SOC_registerSysIntListener(socHandle, &linkFrameCfg, &errCode)) == NULL)
    {
        System_printf("Error: Unable to register frame interrupt listener , error = %d\n", errCode);
        return -1;
    }
    
    /* Register chirp interrupt */
    memset((void *)&linkFrameCfg, 0 , sizeof(SOC_SysIntListenerCfg));
    linkFrameCfg.systemInterrupt    = SOC_XWR18XX_MSS_CHIRP_AVAIL_IRQ;
    linkFrameCfg.listenerFxn        = Mmwavelink_chirpAvailInterrupCallBackFunc;
    linkFrameCfg.arg                = (uintptr_t)NULL;
    if ((SOC_registerSysIntListener(socHandle, &linkFrameCfg, &errCode)) == NULL)
    {
        System_printf("Error: Unable to register chirp interrupt listener , error = %d\n", errCode);
        return -1;
    }
    
    Cycleprofiler_init();

    /* Debug Message: */
    System_printf ("******************************************\n");
    System_printf ("Debug: Launching the mmwaveLink\n");
    System_printf ("******************************************\n");

    /* Initialize the Task Parameters. */
    Task_Params_init(&taskParams);
    taskParams.priority = 5;
    Task_create(MmwaveLink_initTask, &taskParams, NULL);

    /* Start BIOS */
    BIOS_start();
    return 0;
}


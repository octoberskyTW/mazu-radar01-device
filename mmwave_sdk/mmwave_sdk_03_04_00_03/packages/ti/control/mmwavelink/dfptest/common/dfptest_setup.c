/*
 *   @file  dfptest_setup.c
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
#include <ti/drivers/edma/edma.h>

#ifdef SUBSYS_MSS
#include <ti/sysbios/family/arm/v7r/vim/Hwi.h>
#else
#include <ti/sysbios/family/c64p/Hwi.h>
#endif

/* mmWave SDK Include Files: */
#include <ti/common/sys_common.h>
#include <ti/drivers/mailbox/mailbox.h>
#include <ti/control/mmwavelink/mmwavelink.h>
#include <ti/drivers/crc/crc.h>
#include <ti/control/mmwavelink/include/rl_driver.h>
#include <ti/drivers/adcbuf/ADCBuf.h>

/* Test include files: */
#include <ti/control/mmwavelink/dfptest/common/dfptest_config.h>
#include <ti/control/mmwavelink/dfptest/common/dfptest_monitoring.h>
#include <ti/control/mmwavelink/dfptest/common/dfptest_verify.h>

#define EDMA_CHANNEL_CQ_DATA  EDMA_TPCC0_REQ_FREE_0
#define CQ1_RAM_ADDRESS       (0x21028800U)
#define L3_MEM_ADDRESS        (0x20000000U)

#define MSS_16xx_TEST_CQ1_L3_MEM_ADDRESS    (0x51000000U)
#define MSS_16xx_TEST_CQ2_L3_MEM_ADDRESS    (0x51000800U)
#define DSS_16xx_TEST_CQ1_L3_MEM_ADDRESS    (0x20000000U)
#define DSS_16xx_TEST_CQ2_L3_MEM_ADDRESS    (0x20000800U)

#define MSS_18xx_TEST_CQ1_L3_MEM_ADDRESS    (0x51000000U)
#define MSS_18xx_TEST_CQ2_L3_MEM_ADDRESS    (0x51000800U)
#define DSS_18xx_TEST_CQ1_L3_MEM_ADDRESS    (0x20000000U)
#define DSS_18xx_TEST_CQ2_L3_MEM_ADDRESS    (0x20000800U)

#define MSS_14xx_CQ_CFG_REG_ADDRESS         (0x5000046CU)
#define MSS_14xx_CHIRP_INFO_REG_ADDRESS     (0x52028000U)

/**************************************************************************
 *************************** Local Structures *****************************
 **************************************************************************/

/**
 * @brief
 *  Mmwave Link Master Control Block
 *
 * @details
 *  The structure is used to hold all the relevant information for the
 *  Mmwave Link.
 */
typedef struct MmwaveLink_MCB
{
    /**
     * @brief   Handle to the BSS Mailbox
     */
    Mbox_Handle              bssMailbox;

    /**
     * @brief   Semaphore handle for the mmWave Link
     */
    Semaphore_Handle            linkSemaphore;

    /**
     * @brief   mmWave Link Spawning function
     */
    RL_P_OSI_SPAWN_ENTRY        spawnFxn;

    /**
     * @brief   Status of the BSS:
     */
    volatile uint32_t           bssStatus;

    /**
     * @brief   Counter which tracks of the number of times the spawn function was
     * overrun.
     */
    uint32_t                    spawnOverrun;
    /**
     * @brief   Handle to the CRC Channel
     */
    CRC_Handle                  crcHandle;
}MmwaveLink_MCB;

/* Monitoring Report Structures */
typedef struct monitoringDataAe
{
    rlMonTempReportData_t         monTempReport;
    rlMonRxGainPhRep_t            monRxGainPhRep;
    rlMonRxNoiseFigRep_t          monNoiseFigRep;
    rlMonRxIfStageRep_t           monRxIfStageRep;
    rlMonTxPowRep_t               monTx0powRep;
    rlMonTxPowRep_t               monTx1powRep;
    rlMonTxPowRep_t               monTx2powRep;
    rlMonTxBallBreakRep_t         monTx0BallbreakRep;
    rlMonTxBallBreakRep_t         monTx1BallbreakRep;
    rlMonTxBallBreakRep_t         monTx2BallbreakRep;
    rlMonTxGainPhaMisRep_t        monTxGainPhMisMatchRep;
    rlMonTxBpmRep_t               monTx0BpmRep;
    rlMonTxBpmRep_t               monTx1BpmRep;
    rlMonTxBpmRep_t               monTx2BpmRep;
    rlMonSynthFreqRep_t           monSynthFreqRep;
    rlMonExtAnaSigRep_t           monExtAnaSigRep;
    rlMonTxIntAnaSigRep_t         monTx0IntAnaSigRep;
    rlMonTxIntAnaSigRep_t         monTx1IntAnaSigRep;
    rlMonTxIntAnaSigRep_t         monTx2IntAnaSigRep;
    rlMonRxIntAnaSigRep_t         monRxIntAnaSigRep;
    rlMonPmclkloIntAnaSigRep_t    monPmClkIntAnaSigRep;
    rlMonGpadcIntAnaSigRep_t      monGpadcIntAnaSigRep;
    rlMonPllConVoltRep_t          monPllConvVoltRep;
    rlMonDccClkFreqRep_t          monDccClkFreqRep;
    rlMonRxMixrInPwrRep_t         monRxMixrInPwrRep;
    rlRfInitComplete_t            monRfInit;
    rlDigLatentFaultReportData_t  monDigLatFaultRep;
    rlDigPeriodicReportData_t     monDigPeriodicRep;
    rlMonReportHdrData_t          monRepHeader;
    rlRfRunTimeCalibReport_t      calibRunTimeRep;
}monitoringDataAe_t;

/* Holds last received report for each monitoring feature */
monitoringDataAe_t gMonDataAeStrct = { 0 };

/**************************************************************************
 *************************** Extern Definitions ***************************
 **************************************************************************/
extern ADCBuf_Handle    adcbufHandle;
extern Semaphore_Handle gSensorStopSem;

/**************************************************************************
 *************************** Global Definitions ***************************
 **************************************************************************/

/* Global Variable for tracking information required by the mmWave Link */
MmwaveLink_MCB    gMmwaveLinkMCB;
uint32_t gInitTimeCalibStatus = 0U;
volatile uint32_t gFrameStartStatus = 0U;
volatile uint32_t gMmwlChecksumFailAsyncEvent = 0U;
volatile uint32_t gMmwlCrcFailAsyncEvent = 0U;
rlUInt8_t isGetGpAdcMeasData = 0U;

RL_P_EVENT_HANDLER g_MailboxInterruptFunc;

/* eDMA handler */
EDMA_Handle EdmaHandle;
/* Tag set based on eDMA data trasnfer done */
volatile uint8_t eDMADataTransferDone = 0U;

/* received GPAdc Data over Async Event */
rlRecvdGpAdcData_t rcvGpAdcData = {0};

/*! CQ MEMORY */
#pragma DATA_SECTION(gMmwCQ, ".cqdata");
uint8_t gMmwCQ [8*1024];

/* Negative test configuration structure */
typedef struct retryNegativeTest
{
    /* Type of corruption
       0 - No corruption
       1 - Checksum corruption
       2 - CRC corruption  */
    uint16_t corruptType;
    /* Event to corrupt
       0 - Command
       1 - Response
       2 - Async Event  */
    uint16_t corruptEvent;
}retryNegativeTest_t;


/* Async Event Enable and Direction configuration */
rlRfDevCfg_t rfDevCfg = {0};

/* Calibration Data storage */
rlCalibrationData_t calibData = { 0 };

/* Phase Shifter Calibration Data storage */
rlPhShiftCalibrationData_t phShiftCalibData = { 0 };
rlRxGainTempLutData_t rxGainTempLutData = { 0 };
rlTxGainTempLutData_t txGainTempLutData = { 0 };
retryNegativeTest_t   retryNegativeTestCfg = { 0 };
uint16_t hit_count = 0;
/**************************************************************************
 *************************** Extern Definitions ***************************
 **************************************************************************/
extern rlInt32_t Osal_mutexCreate(rlOsiMutexHdl_t* mutexHdl, rlInt8_t* name);
extern rlInt32_t Osal_mutexLock(rlOsiMutexHdl_t* mutexHdl, rlOsiTime_t timeout);
extern rlInt32_t Osal_mutexUnlock(rlOsiMutexHdl_t* mutexHdl);
extern rlInt32_t Osal_mutexDelete(rlOsiMutexHdl_t* mutexHdl);
extern rlInt32_t Osal_semCreate(rlOsiSemHdl_t* semHdl, rlInt8_t* name);
extern rlInt32_t Osal_semWait(rlOsiSemHdl_t* semHdl, rlOsiTime_t timeout);
extern rlInt32_t Osal_semSignal(rlOsiSemHdl_t* semHdl);
extern rlInt32_t Osal_semDelete(rlOsiSemHdl_t* semHdl);
extern rlInt32_t Osal_delay(rlUInt32_t delay);

/**************************************************************************
 ************************* Link Unit Test Functions ***********************
 **************************************************************************/

/**
 *  @b Description
 *  @n
 *      Mailbox registered function which is invoked on the reception of data
 *
 *  @retval
 *      Success - Communicate Interface Channel Handle
 *  @retval
 *      Error   - NULL
 */
static void MmwaveLink_mboxCallbackFxn (Mbox_Handle handle, Mailbox_Type remoteEndpoint)
{
    /* Indicate to the Radar Link that a message has been received. */
    g_MailboxInterruptFunc(0, NULL);
}

/**
 *  @b Description
 *  @n
 *      Radar Link Registered Callback function to open the communication
 *      interface channel
 *
 *  @retval
 *      Success - Communicate Interface Channel Handle
 *  @retval
 *      Error   - NULL
 */
static rlComIfHdl_t MmwaveLink_mboxOpen(rlUInt8_t deviceIndex, uint32_t flags)
{
    Mailbox_Config  cfg;
    int32_t         errCode;

    /* Initialize the mailbox configuration: */
    if(Mailbox_Config_init(&cfg) < 0)
    {
        System_printf("Error: Unable to initialize mailbox configuration\n");
        return NULL;
    }

    cfg.writeMode    = MAILBOX_MODE_POLLING;
    cfg.readMode     = MAILBOX_MODE_CALLBACK;
    cfg.readCallback = MmwaveLink_mboxCallbackFxn;

    /* Open the Mailbox to the BSS */
    gMmwaveLinkMCB.bssMailbox = Mailbox_open(MAILBOX_TYPE_BSS, &cfg, &errCode);
    if (gMmwaveLinkMCB.bssMailbox == NULL)
    {
        System_printf("Error: Unable to open the Mailbox Instance [Error code %d]\n", errCode);
        return NULL;
    }
    
    return gMmwaveLinkMCB.bssMailbox;
}

/**
 *  @b Description
 *  @n
 *      Radar Link Registered Callback function to close the communication
 *      interface channel
 *
 *  @retval
 *      Success - 0
 *  @retval
 *      Error   - <0
 */
static int32_t MmwaveLink_mboxClose(rlComIfHdl_t fd)
{
    int32_t errCode;

    /* Close the Mailbox */
    errCode = Mailbox_close ((Mbox_Handle)fd);
    if (errCode < 0)
        System_printf ("Error: Unable to close the BSS Mailbox [Error code %d]\n", errCode);

    return errCode;
}

/**
 *  @b Description
 *  @n
 *      Radar Link Registered Callback function to read data from the communication
 *      interface channel
 *
 *  @retval
 *      Success - 0
 *  @retval
 *      Error   - <0
 */
static int32_t MmwaveLink_mboxRead(rlComIfHdl_t fd, uint8_t* pBuff, uint16_t len)
{
    int32_t    status;
    
    status = Mailbox_read((Mbox_Handle)fd, pBuff, len);
    
    if (retryNegativeTestCfg.corruptType == 1)
    {
        if (retryNegativeTestCfg.corruptEvent == 1)
        {
            hit_count++;
            if (hit_count == 2)
            {
                pBuff[10] = ~(pBuff[14]);
                pBuff[11] = ~(pBuff[15]);
                retryNegativeTestCfg.corruptType = 0;
                hit_count = 0;
            }
        }
    }
    if (retryNegativeTestCfg.corruptType == 1)
    {
        if (retryNegativeTestCfg.corruptEvent == 2)
        {
            hit_count++;
            if (hit_count == 5)
            {
                pBuff[10] = ~(pBuff[14]);
                pBuff[11] = ~(pBuff[15]);
                retryNegativeTestCfg.corruptType = 0;
                hit_count = 0;
            }
        }
    }
    
    return status;
}

/**
 *  @b Description
 *  @n
 *      Radar Link Registered Callback function to write data to the communication
 *      interface channel
 *
 *  @retval
 *      Success - 0
 *  @retval
 *      Error   - <0
 */
static int32_t MmwaveLink_mboxWrite(rlComIfHdl_t fd, uint8_t* pBuff, uint16_t len)
{
    int32_t    status;
    /*
      Currently, the mmwavelink can not detect the error condition where it did not receive a mailbox layer ACK from BSS.

      For instance:
      - The mmwavelink may try to send a message before an ACK was received for the previous message.
      - The mmwavelink may try to resend a message that did not receive a mmwavelink layer ACK back from BSS. It is possible that the
      message did not receive a mailbox layer ACK as well from BSS.

      In either case, Mailbox_writeReset() has to be called before another message is sent to BSS.

      The mmwavelink has no hooks to call the Mailbox_writeReset().
      Therefore, a write reset is done if it is detected that a mailbox layer ACK was not received for the
      previous message (MAILBOX_ETXFULL).
     */
    if (retryNegativeTestCfg.corruptType == 1)
    {
        if (retryNegativeTestCfg.corruptEvent == 0)
        {
            hit_count++;
            if (hit_count == 1)
            {
                pBuff[14] = ~(pBuff[14]);
                pBuff[15] = ~(pBuff[15]);
                retryNegativeTestCfg.corruptType = 0;
                hit_count = 0;
            }
        }
    }
    status = Mailbox_write((Mbox_Handle)fd, pBuff, len);
    if(status == MAILBOX_ETXFULL)
    {
        Mailbox_writeReset((Mbox_Handle)fd);
        status = Mailbox_write((Mbox_Handle)fd, pBuff, len);
    }

    return status;
}

/**
 *  @b Description
 *  @n
 *      Radar Link Registered Callback function to power on the AR1XX Device
 *
 *  @retval
 *      Success - 0
 *  @retval
 *      Error   - <0
 */
static rlInt32_t MmwaveLink_enableDevice(rlUInt8_t deviceIndex)
{
    return 0;
}

/**
 *  @b Description
 *  @n
 *      Radar Link Registered Callback function to power off the AR1XX Device
 *
 *  @retval
 *      Success - 0
 *  @retval
 *      Error   - <0
 */
static rlInt32_t MmwaveLink_disableDevice(rlUInt8_t deviceIndex)
{
    return 0;
}

/**
 *  @b Description
 *  @n
 *      Radar Link Registered Callback function to mask the interrupts.
 *      In the case of Mailbox communication interface the driver will
 *      handle the interrupt management. This function is a dummy stub
 *
 *  @retval
 *      Not applicable
 */
static void MmwaveLink_maskHostIRQ(rlComIfHdl_t fd)
{
    return;
}

/**
 *  @b Description
 *  @n
 *      Radar Link Registered Callback function to umask the interrupts.
 *      In the case of the mailbox driver we will flush out and close the
 *      read buffer.
 *
 *  @retval
 *      Not applicable
 */
void MmwaveLink_unmaskHostIRQ(rlComIfHdl_t fd)
{
    Mailbox_readFlush((Mbox_Handle)fd);
}

/**
 *  @b Description
 *  @n
 *      Radar Link Registered Callback function to register the Interrupt Handler.
 *      In the case of the Mailbox the driver does the interrupt registeration and
 *      so this function is a dummy stub.
 *
 *  @retval
 *      Success - 0
 *  @retval
 *      Error   - <0
 */
static rlInt32_t MmwaveLink_registerInterruptHandler(rlUInt8_t deviceIndex, RL_P_EVENT_HANDLER pHandler, void* pValue)
{
    g_MailboxInterruptFunc = pHandler;
    return 0;
}

static void MmwaveLink_transferCompletionCallbackFxn(uintptr_t arg, uint8_t transferCompletionCode)
{
    /* set the TAG to indicate eDMA data transfer is done */
    eDMADataTransferDone++;
}

/* initialize eDMA module */
int32_t MmwaveLink_initEDMA(uint8_t instance)
{
    int32_t    retVal = 0;

    retVal = EDMA_init(instance);
    if (retVal != EDMA_NO_ERROR)
    {
        System_printf ("Debug: EDMA instance %d initialization returned error %d\n", instance, retVal);
        return -1;
    }
    System_printf ("Debug: EDMA instance %d has been initialized\n", instance);
    return 0;
}

/**
 *  @b Description
 *  @n
 *      Open EDMA driver Instance for ADCBUF data buffer copy.
 *
 *  @param[in]  instance
 *      EDMA driver instance.
 *
 *  @retval
 *      Success     - EDMA handle
 *      Fail        - NULL pointer
 */
static EDMA_Handle MmwaveLink_openEDMA(uint8_t instance)
{
    EDMA_errorInfo_t              EDMAErrorInfo;
    EDMA_transferControllerErrorInfo_t EDMATransferControllerErrorInfo;
    EDMA_Handle                   edmaHndle = NULL;
    EDMA_instanceInfo_t           instanceInfo;
    int32_t                       retVal = 0;

    memset(&EDMAErrorInfo, 0, sizeof(EDMAErrorInfo));
    memset(&EDMATransferControllerErrorInfo, 0, sizeof(EDMATransferControllerErrorInfo));

    /* Open the EDMA Instance */
    edmaHndle = EDMA_open(instance, &retVal, &instanceInfo);
    if (edmaHndle == NULL)
    {
        System_printf("Error: Unable to open the edma Instance(%d), errorCode = %d\n",instance, retVal);
        return NULL;
    }

    return edmaHndle;
}

/* configure eDMA channel to copy CQ data to L3 memory */
int32_t MmwaveLink_ConfigEdma(EDMA_Handle handle, uint8_t chId,
                                    uint32_t* pSrcAddress, uint32_t * pDestAddress,
                                    uint16_t aCount, uint16_t bCount, uint16_t cCount,
                                    uint16_t linkChId)
{
    EDMA_channelConfig_t config;
    int32_t errorCode = EDMA_NO_ERROR;

    config.channelId = chId;
    config.channelType = (uint8_t)EDMA3_CHANNEL_TYPE_DMA;
    config.paramId = chId;
    config.eventQueueId = 0;

    config.paramSetConfig.sourceAddress = (uint32_t) pSrcAddress;
    config.paramSetConfig.destinationAddress = (uint32_t) pDestAddress;

    config.paramSetConfig.aCount = aCount;
    config.paramSetConfig.bCount = bCount;
    config.paramSetConfig.cCount = cCount;
    config.paramSetConfig.bCountReload = config.paramSetConfig.bCount;

    config.paramSetConfig.sourceBindex = 0;
    config.paramSetConfig.destinationBindex = 0;

    config.paramSetConfig.sourceCindex = 0;
    config.paramSetConfig.destinationCindex = 0;

    config.paramSetConfig.linkAddress = EDMA_NULL_LINK_ADDRESS;
    config.paramSetConfig.transferType = (uint8_t)EDMA3_SYNC_A;
    config.paramSetConfig.transferCompletionCode = 0;
    config.paramSetConfig.sourceAddressingMode = (uint8_t) EDMA3_ADDRESSING_MODE_LINEAR;
    config.paramSetConfig.destinationAddressingMode = (uint8_t) EDMA3_ADDRESSING_MODE_LINEAR;

    /* don't care because of linear addressing modes above */
    config.paramSetConfig.fifoWidth = (uint8_t) EDMA3_FIFO_WIDTH_8BIT;

    config.paramSetConfig.isStaticSet = false;
    config.paramSetConfig.isEarlyCompletion = false;
    config.paramSetConfig.isFinalTransferInterruptEnabled = true;
    config.paramSetConfig.isIntermediateTransferInterruptEnabled = false;
    config.paramSetConfig.isFinalChainingEnabled = false;
    config.paramSetConfig.isIntermediateChainingEnabled = false;
    config.transferCompletionCallbackFxn = MmwaveLink_transferCompletionCallbackFxn;

    if ((errorCode = EDMA_configChannel(handle, &config, true)) != EDMA_NO_ERROR)
    {
        System_printf("Error: EDMA_configChannel() failed with error code = %d\n", errorCode);
    }
    return(errorCode);
}

/* Trigger eDMA transfer */
void MmwaveLink_triggerEdmaTransfer()
{
    EDMA_startDmaTransfer(EdmaHandle, EDMA_CHANNEL_CQ_DATA);
}

/* intialize and configure eDMA to copy CQ Data to L3 memory */
int MmwaveLink_CQedmaSetup(void)
{

    MmwaveLink_initEDMA(0);
    EdmaHandle = MmwaveLink_openEDMA(0);
    if(EdmaHandle == NULL)
    {
        System_printf("Error: MmwaveLink_CQedmaSetup() MmwaveLink_openEDMA failed with null handle.\n");
        return -1;
    }
    /* Configure eDMA */
    MmwaveLink_ConfigEdma(EdmaHandle, EDMA_CHANNEL_CQ_DATA,
                          (uint32_t *)CQ1_RAM_ADDRESS,
                          (uint32_t *)L3_MEM_ADDRESS,
                          0x1000, 1, 1, EDMA_NUM_DMA_CHANNELS);
    EDMA3EnableTransfer(EDMA_CC0_BASE_ADDRESS, EDMA_CHANNEL_CQ_DATA, EDMA3_TRIG_MODE_EVENT);
    return 0;
}


volatile int8_t cqTestStatus = -10;
volatile int8_t cpTestStatus = -10;

/**
 *  @b Description
 *  @n
 *      This function is to verify CQ1 and CQ2 RAM data for RX signal and image band monitor
 *      and saturation monitor for each slices which device has been configured.
 *
 *  @param : coreType- MSS or DSS core
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int8_t MmwaveLink_VerifyCQData(uint8_t coreType, uint8_t deviceType)
{
    unsigned char numSlices, i, maxByteLoc;
    volatile unsigned char *cq1MemLoc;
    volatile unsigned char *cq2MemLoc;
    uint32_t cqBaseAddr14xx = *(uint32_t*)(MSS_14xx_CQ_CFG_REG_ADDRESS);
    if (coreType == RL_PLATFORM_MSS)
    {
        if(deviceType == RL_AR_DEVICETYPE_14XX)
        {
            /* for 14xx test not transfering CQ data reading from CQ memory directly */
            cq1MemLoc = (unsigned char*) ((((cqBaseAddr14xx & 0x007F0000U) >> 16U)*0x10) + MSS_14xx_CHIRP_INFO_REG_ADDRESS);
            cq2MemLoc = (unsigned char*) ((((cqBaseAddr14xx & 0x7F000000U) >> 24U)*0x10) + MSS_14xx_CHIRP_INFO_REG_ADDRESS);
        }
        else if (deviceType == RL_AR_DEVICETYPE_16XX)
        {
            cq1MemLoc = (unsigned char*) (MSS_16xx_TEST_CQ1_L3_MEM_ADDRESS);
            cq2MemLoc = (unsigned char*) (MSS_16xx_TEST_CQ2_L3_MEM_ADDRESS);
        }
        else
        {
            cq1MemLoc = (unsigned char*) (MSS_18xx_TEST_CQ1_L3_MEM_ADDRESS);
            cq2MemLoc = (unsigned char*) (MSS_18xx_TEST_CQ2_L3_MEM_ADDRESS);
        }
    }
    else
    {
        if (deviceType == RL_AR_DEVICETYPE_16XX)
        {
            cq1MemLoc = (unsigned char*) (DSS_16xx_TEST_CQ1_L3_MEM_ADDRESS);
            cq2MemLoc = (unsigned char*) (DSS_16xx_TEST_CQ2_L3_MEM_ADDRESS);
        }
        else
        {
            cq1MemLoc = (unsigned char*) (DSS_18xx_TEST_CQ1_L3_MEM_ADDRESS);
            cq2MemLoc = (unsigned char*) (DSS_18xx_TEST_CQ2_L3_MEM_ADDRESS);
        }
    }

    /* CQ data will be available in CQ RAM which is a ping-pong memory when the CQ monitors are
       enabled. Currently supported CQ monitors are RL_RF_RX_SATURATION_MON_CONF_SB for CQ2 and
       RL_RF_RX_SIGIMG_MON_CONF_SB for CQ1. CQ data will be refreshed every chirp by the hardware.
       User has to ensure that before the next chirp finishes, the current chirps’ CQ data is either
       processed or transferred to a local memory for further processing.
     */

    /* check for timeSlice value for CQ1 and CQ2 as configured to device via
       rlRfRxIfSatMonConfig and rlRfRxSigImgMonConfig API */
    if (CQ_NUM_SLICES != cq1MemLoc[0])
    {
        cqTestStatus = -1;
    }
    else
    {
        numSlices = cq1MemLoc[0];
        /* get max byte location which application needs to
           read starting from numSlice in CQ1-RAM memory */
        maxByteLoc = (4*(numSlices+1)/2);
        for (i = 2; i < maxByteLoc; i+=2)
        {
            /* check if any signal band data is less than image band data for all
               primary and secondary slices, then set error  */
            if (((cq1MemLoc[i] / 2) * -1) < ((cq1MemLoc[i+1] /2)*-1))
            {
                cqTestStatus = -2;
                break;
            }
        }

        /* if conditions are not matched for all slices then set success */
        if (i == maxByteLoc)
        {
            cqTestStatus = 0;
        }

    }

    if (CQ_NUM_SLICES != cq2MemLoc[0])
    {
        cqTestStatus = -1;
    }
    else
    {
        numSlices = cq2MemLoc[0];
        for (i = 1; i < numSlices; i++)
        {
            /* check if any signal band data is less than image band data for all
               primary and secondary slices, then set error  */
            if (cq2MemLoc[i] != 0)
            {
                cqTestStatus = -2;
                break;
            }
        }

        /* if conditions are not matched for all slices then set success */
        if (i == numSlices)
        {
            cqTestStatus = 0;
        }

    }
    return cqTestStatus;
}

/**
 *  @b Description
 *  @n
 *      Verify Chirp parameters
 *      CP is Chirp Parameter information which is defined for each RX as follows
        Bit     Description
        11:0    Chirp number
                In legacy frame configuration, chirp number for starts from 1 and increments
                for each chirp within the frame and resets to 0 for the next frame.
                In advanced frame configuration chirp number starts from 1 and increments for
                each chirp within the burst and resets to 0 for the next burst.
        15:12    Reserved
        17:16    Channel number. The receive channel number which is encoded as
                00 – RX0
                01 – RX1
                10 – RX2
                11 – RX3
        21:18    Profile number. The profile number to which the chirp belongs
        31:22    Reserved
 *
 *  @param : coreType- MSS or DSS core
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int8_t MmwaveLink_VerifyCPData(uint8_t coreType)
{
    uint8_t cp0DataBuff[16] = {0};
    volatile uint16_t chirpNum, channelNum, profileId;

    if (coreType == RL_PLATFORM_MSS)
    {
        /* copy CP0 data to local buffer */
        memcpy((void*)&cp0DataBuff[0], (void*)0x52070020U, 16U);
    }
    else
    {
        /* copy CP0 data to local buffer */
       memcpy((void*)&cp0DataBuff[0], (void*)0x21070020U, 16U);
    }

    /* Please refer mmWaveLink or ICD for Chirp parameter (CP) information fields */
    chirpNum =  (((cp0DataBuff[3] & 0x0F)<< 8) | (cp0DataBuff[2]));
    channelNum = (cp0DataBuff[0] & 0x03);
    profileId =  ((cp0DataBuff[0] >> 2) & 0x0F);
    /* verify CP-0 data for channel 0 */
    if ((channelNum != 0U) || (profileId != chirpCfg[0].profileId) || \
         ((chirpNum + 1) != ((frameCfg.chirpEndIdx - frameCfg.chirpStartIdx + 1) * frameCfg.numLoops)))
    {
        cpTestStatus = -1;
    }
    else
    {
        cpTestStatus = 0;
    }

    chirpNum =  (((cp0DataBuff[7] & 0x0F)<< 8) | (cp0DataBuff[6]));
    channelNum = (cp0DataBuff[4] & 0x03);
    profileId =  ((cp0DataBuff[4] >> 2) & 0x0F);
    /* verify CP-0 data for channel 1 */
    if ((channelNum != 1U) || (profileId != chirpCfg[0].profileId) || \
        ((chirpNum + 1) != ((frameCfg.chirpEndIdx - frameCfg.chirpStartIdx + 1) * frameCfg.numLoops)))
    {
        cpTestStatus -=1;
    }
    else
    {
        cpTestStatus = 0;
    }

    return cpTestStatus;
}


/**
 *  @b Description
 *  @n
 *      Radar Link Registered Callback function to handle asynchronous events
 *
 *  @retval
 *      Success - 0
 *  @retval
 *      Error   - <0
 */
static void MmwaveLink_asyncEventHandler(uint8_t devIndex, uint16_t sbId, uint16_t sbLen, uint8_t *payload)
{
    uint16_t asyncSB = RL_GET_SBID_FROM_UNIQ_SBID(sbId);
    uint16_t msgId   = RL_GET_MSGID_FROM_SBID(sbId);

    /* Process the received message: */
    switch (msgId)
    {
        case RL_RF_ASYNC_EVENT_MSG:
        {
            /* Received Asychronous Message: */
            switch (asyncSB)
            {
                case RL_RF_AE_CPUFAULT_SB:
                {
                    rlCpuFault_t* rfCpuFault = (rlCpuFault_t*)payload;
                    System_printf ("Debug: CPU Fault has been detected\n");
                    System_printf ("Debug: Fault \n type: %d, lineNum: %d, LR: 0x%x \n"
                                    "PrevLR: 0x%x, spsr: 0x%x, sp: 0x%x, PC: 0x%x \n"
                                    "Status: 0x%x, Source: %d, AxiErrType: %d, AccType: %d, Recovery Type: %d \n",
                                    rfCpuFault->faultType,
                                    rfCpuFault->lineNum,
                                    rfCpuFault->faultLR,
                                    rfCpuFault->faultPrevLR,
                                    rfCpuFault->faultSpsr,
                                    rfCpuFault->faultSp,
                                    rfCpuFault->faultAddr,
                                    rfCpuFault->faultErrStatus,
                                    rfCpuFault->faultErrSrc,
                                    rfCpuFault->faultAxiErrType,
                                    rfCpuFault->faultAccType,
                                    rfCpuFault->faultRecovType);
                    break;
                }
                case RL_RF_AE_ESMFAULT_SB:
                {
                    System_printf ("Debug: ESM Fault. Group1:[0x%x] Group2:[0x%x]\n",
                    ((rlBssEsmFault_t*)payload)->esmGrp1Err, ((rlBssEsmFault_t*)payload)->esmGrp2Err);
                    break;
                }
                case RL_RF_AE_INITCALIBSTATUS_SB:
                {
                    gInitTimeCalibStatus = ((rlRfInitComplete_t*)payload)->calibStatus;
                    if(gInitTimeCalibStatus != 0U)
                    {
                        System_printf ("Debug: Init time calibration status [0x%x] \n", gInitTimeCalibStatus);
                    }
                    else
                    {
                        System_printf ("Error: All Init time calibrations Failed:\n");
                    }
                    break;
                }
                case RL_RF_AE_FRAME_TRIGGER_RDY_SB:
                {
                    gFrameStartStatus = 1U;
                    break;
                }
                case RL_RF_AE_MON_TIMING_FAIL_REPORT_SB:
                {
                    monTestPassFlag = false;
                    System_printf ("Debug: RL_RF_AE_MON_TIMING_FAIL_REPORT_SB received. timingFailCode=0x%x \n",
                                   ((rlCalMonTimingErrorReportData_t*)payload)->timingFailCode);
                    break;
                }
                case RL_RF_AE_RUN_TIME_CALIB_REPORT_SB:
                {
                    memcpy(&gMonDataAeStrct.calibRunTimeRep, payload, sizeof(rlRfRunTimeCalibReport_t));
                    MmwaveLink_verifyRunTimeCalibRep(&gMonDataAeStrct.calibRunTimeRep);
                    break;
                }
                case RL_RF_AE_MON_DIG_PERIODIC_REPORT_SB:
                {
                    memcpy(&gMonDataAeStrct.monDigPeriodicRep, payload, sizeof(rlDigPeriodicReportData_t));
                    MmwaveLink_verifyDigPeriodicRep(&gMonDataAeStrct.monDigPeriodicRep);
                    break;
                }
                case RL_RF_AE_MON_TEMPERATURE_REPORT_SB:
                {
                    memcpy(&gMonDataAeStrct.monTempReport, payload, sizeof(rlMonTempReportData_t));
                    MmwaveLink_verifyTemperatureRep(&gMonDataAeStrct.monTempReport);
                    break;
                }
                case RL_RF_AE_MON_RX_GAIN_PHASE_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monRxGainPhRep, payload, sizeof(rlMonRxGainPhRep_t));
                    MmwaveLink_verifyRxGainPhRep(&gMonDataAeStrct.monRxGainPhRep);                    
                    break;
                }
                case RL_RF_AE_MON_RX_NOISE_FIG_REPORT:
                {
                    /* stop updating the global cached value after first error so that we can dump the first failed case valus */
                    memcpy(&gMonDataAeStrct.monNoiseFigRep, payload, sizeof(rlMonRxNoiseFigRep_t));
                    MmwaveLink_verifyRxNoiseFigRep(&gMonDataAeStrct.monNoiseFigRep);
                    break;
                }
                case RL_RF_AE_MON_RX_IF_STAGE_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monRxIfStageRep, payload, sizeof(rlMonRxIfStageRep_t));
                    MmwaveLink_verifyRxIfStageRep(&gMonDataAeStrct.monRxIfStageRep);                    
                    break;
                }
                case RL_RF_AE_MON_TX0_POWER_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monTx0powRep, payload, sizeof(rlMonTxPowRep_t));
                    MmwaveLink_verifyTxPower(&gMonDataAeStrct.monTx0powRep, MMWAVELINK_TEST_MON_TX0_POWER);
                    break;
                }
                case RL_RF_AE_MON_TX1_POWER_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monTx1powRep, payload, sizeof(rlMonTxPowRep_t));
                    MmwaveLink_verifyTxPower(&gMonDataAeStrct.monTx1powRep, MMWAVELINK_TEST_MON_TX1_POWER);
                    break;
                }
                case RL_RF_AE_MON_TX2_POWER_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monTx2powRep, payload, sizeof(rlMonTxPowRep_t));
                    MmwaveLink_verifyTxPower(&gMonDataAeStrct.monTx2powRep, MMWAVELINK_TEST_MON_TX2_POWER);
                    break;
                }
                case RL_RF_AE_MON_TX0_BALLBREAK_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monTx0BallbreakRep, payload, sizeof(rlMonTxBallBreakRep_t));
                    MmwaveLink_verifyTxBallBreak(&gMonDataAeStrct.monTx0BallbreakRep, MMWAVELINK_TEST_MON_TX0_BALL_BRK);
                    break;
                }
                case RL_RF_AE_MON_TX1_BALLBREAK_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monTx1BallbreakRep, payload, sizeof(rlMonTxBallBreakRep_t));
                    MmwaveLink_verifyTxBallBreak(&gMonDataAeStrct.monTx1BallbreakRep, MMWAVELINK_TEST_MON_TX1_BALL_BRK);
                    break;
                }
                case RL_RF_AE_MON_REPORT_HEADER_SB:
                {
                    memcpy(&gMonDataAeStrct.monRepHeader, payload, sizeof(rlMonReportHdrData_t));
                    MmwaveLink_verifyRepHeader(&gMonDataAeStrct.monRepHeader);
                    break;
                }
                case RL_RF_AE_GPADC_MEAS_DATA_SB:
                {
                    isGetGpAdcMeasData = 1U;
                    memcpy(&rcvGpAdcData, payload, sizeof(rlRecvdGpAdcData_t));
                    break;
                }
                case RL_RF_AE_DIG_LATENTFAULT_REPORT_SB:
                {
                    memcpy(&gMonDataAeStrct.monDigLatFaultRep, payload, sizeof(rlDigLatentFaultReportData_t));
                    MmwaveLink_verifyDigLatFaultRep(&gMonDataAeStrct.monDigLatFaultRep);
                    break;
                }
                case RL_RF_AE_FRAME_END_SB:
                {
                    gFrameStartStatus = 0U;
                    Semaphore_post (gSensorStopSem);
                    System_printf ("Debug:  Frame Stop Async Event \n");
                    break;
                }
                case RL_RF_AE_ANALOG_FAULT_SB:
                {
                    System_printf ("Debug:  Analog Fault Async Event \n");
                    break;
                }
                default:
                {
                    System_printf ("Error: Asynchronous Event SB Id %d not handled with msg ID [0x%x] \n", asyncSB,msgId);
                    break;
                }
            }
            break;
        }
        case RL_RF_ASYNC_EVENT_1_MSG:
        {
            switch (asyncSB)
            {
                case RL_RF_AE_MON_TX2_BALLBREAK_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monTx2BallbreakRep, payload, sizeof(rlMonTxBallBreakRep_t));
                    MmwaveLink_verifyTxBallBreak(&gMonDataAeStrct.monTx2BallbreakRep, MMWAVELINK_TEST_MON_TX2_BALL_BRK);
                    break;
                }
                case RL_RF_AE_MON_TX_GAIN_MISMATCH_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monTxGainPhMisMatchRep, payload, sizeof(rlMonTxGainPhaMisRep_t));
                    MmwaveLink_verifyTxGainPhaseRep(&gMonDataAeStrct.monTxGainPhMisMatchRep);
                    break;
                }
                case RL_RF_AE_MON_TX0_BPM_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monTx0BpmRep, payload, sizeof(rlMonTxBpmRep_t));
                    MmwaveLink_verifyTxBpm(&gMonDataAeStrct.monTx0BpmRep, MMWAVELINK_TEST_MON_TX0_BPM);
                    break;
                }
                case RL_RF_AE_MON_TX1_BPM_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monTx1BpmRep, payload, sizeof(rlMonTxBpmRep_t));
                    MmwaveLink_verifyTxBpm(&gMonDataAeStrct.monTx1BpmRep, MMWAVELINK_TEST_MON_TX1_BPM);
                    break;
                }
                case RL_RF_AE_MON_TX2_BPM_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monTx2BpmRep, payload, sizeof(rlMonTxBpmRep_t));
                    MmwaveLink_verifyTxBpm(&gMonDataAeStrct.monTx2BpmRep, MMWAVELINK_TEST_MON_TX2_BPM);
                    break;
                }
                case RL_RF_AE_MON_SYNTHESIZER_FREQ_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monSynthFreqRep, payload, sizeof(rlMonSynthFreqRep_t));
                    MmwaveLink_verifyRfSynthFreqRep(&gMonDataAeStrct.monSynthFreqRep);
                    break;
                }
                case RL_RF_AE_MON_EXT_ANALOG_SIG_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monExtAnaSigRep, payload, sizeof(rlMonExtAnaSigRep_t));
                    MmwaveLink_verifyExtAnalogSigRep(&gMonDataAeStrct.monExtAnaSigRep);
                    break;
                }
                case RL_RF_AE_MON_TX0_INT_ANA_SIG_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monTx0IntAnaSigRep, payload, sizeof(rlMonTxIntAnaSigRep_t));
                    MmwaveLink_verifyRfTxIntAnaSignals(&gMonDataAeStrct.monTx0IntAnaSigRep, MMWAVELINK_TEST_MON_TX0_INT_ANA_SIG);
                    break;
                }
                case RL_RF_AE_MON_TX1_INT_ANA_SIG_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monTx1IntAnaSigRep, payload, sizeof(rlMonTxIntAnaSigRep_t));
                    MmwaveLink_verifyRfTxIntAnaSignals(&gMonDataAeStrct.monTx1IntAnaSigRep, MMWAVELINK_TEST_MON_TX1_INT_ANA_SIG);
                    break;
                }
                case RL_RF_AE_MON_TX2_INT_ANA_SIG_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monTx2IntAnaSigRep, payload, sizeof(rlMonTxIntAnaSigRep_t));
                    MmwaveLink_verifyRfTxIntAnaSignals(&gMonDataAeStrct.monTx2IntAnaSigRep, MMWAVELINK_TEST_MON_TX2_INT_ANA_SIG);
                    break;
                }
                case RL_RF_AE_MON_RX_INT_ANALOG_SIG_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monRxIntAnaSigRep, payload, sizeof(rlMonRxIntAnaSigRep_t));
                    MmwaveLink_verifyRxIntAnaSigRep(&gMonDataAeStrct.monRxIntAnaSigRep);
                    break;
                }
                case RL_RF_AE_MON_PMCLKLO_INT_ANA_SIG_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monPmClkIntAnaSigRep, payload, sizeof(rlMonPmclkloIntAnaSigRep_t));
                    MmwaveLink_verifyIntPmClkLoSigRep(&gMonDataAeStrct.monPmClkIntAnaSigRep);
                    break;
                }
                case RL_RF_AE_MON_GPADC_INT_ANA_SIG_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monGpadcIntAnaSigRep, payload, sizeof(rlMonGpadcIntAnaSigRep_t));
                    MmwaveLink_verifyIntGpadcSigRep(&gMonDataAeStrct.monGpadcIntAnaSigRep);
                    break;
                }
                case RL_RF_AE_MON_PLL_CONTROL_VOLT_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monPllConvVoltRep, payload, sizeof(rlMonPllConVoltRep_t));
                    MmwaveLink_verifyPllControlRep(&gMonDataAeStrct.monPllConvVoltRep);
                    break;
                }
                case RL_RF_AE_MON_DCC_CLK_FREQ_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monDccClkFreqRep, payload, sizeof(rlMonDccClkFreqRep_t));
                    MmwaveLink_verifyDccClockFreqRep(&gMonDataAeStrct.monDccClkFreqRep);
                    break;
                }
                case RL_RF_AE_MON_RX_MIXER_IN_PWR_REPORT:
                {
                    memcpy(&gMonDataAeStrct.monRxMixrInPwrRep, payload, sizeof(rlMonRxMixrInPwrRep_t));
                    MmwaveLink_verifyRxMixInpPowerRep(&gMonDataAeStrct.monRxMixrInPwrRep);
                    break;
                }
                default:
                {
                    System_printf ("Error: Asynchronous Event SB Id %d not handled with msg ID 0x%x\n", asyncSB,msgId);
                    break;
                }
            }
            break;
        }
        /* Async Event from MMWL */
        case RL_MMWL_ASYNC_EVENT_MSG:
        {
            switch (asyncSB)
            {
                case RL_MMWL_AE_MISMATCH_REPORT:
                {
                    int errTemp = *(int32_t*)payload;
                    /* CRC mismatched in the received Async-Event msg */
                    if (errTemp == RL_RET_CODE_CRC_FAILED)
                    {
                        gMmwlCrcFailAsyncEvent = 1U;
                    }
                    /* Checksum mismatched in the received msg */
                    else if (errTemp == RL_RET_CODE_CHKSUM_FAILED)
                    {
                        gMmwlChecksumFailAsyncEvent = 1U;
                    }
                    /* Polling to HostIRQ is timed out,
                    i.e. Device didn't respond to CNYS from the Host */
                    else if (errTemp == RL_RET_CODE_HOSTIRQ_TIMEOUT)
                    {
                        printf("HostIRQ polling timed out \n");
                    }
                    else
                    {
                        printf("mmWaveLink error \n");
                    }
                    break;
                }
                case RL_MMWL_AE_INTERNALERR_REPORT:
                {
                    System_printf("Error: RL_MMWL_AE_INTERNALERR_REPORT received\n");
                    break;
                }
            }    
        }
        default:
        {
            System_printf ("Error: Asynchronous message %d is NOT handled\n", msgId);
            break;
        }
    }
    return;
}

/**
 *  @b Description
 *  @n
 *      Radar Link Registered Callback function to call the function in a different context
 *      This function is invoked from the Interrupt context.
 *
 *  @retval
 *      Success - 0
 *  @retval
 *      Error   - <0
 */
static rlInt32_t MmwaveLink_spawn (RL_P_OSI_SPAWN_ENTRY pEntry, const void* pValue, uint32_t flags)
{
    /* Record the function which is to be spawned. */
    if (gMmwaveLinkMCB.spawnFxn != NULL)
        gMmwaveLinkMCB.spawnOverrun++;

    /* Record the entry to be spawned. */
    gMmwaveLinkMCB.spawnFxn = pEntry;

    /* Post the semaphore and wake up the link management task */
    Semaphore_post (gMmwaveLinkMCB.linkSemaphore);
    return 0;
}

/**
 *  @b Description
 *  @n
 *      Radar Link Registered Callback function to compute the CRC.
 *
 *  @retval
 *      Success - 0
 *  @retval
 *      Error   - <0
 */
static rlInt32_t MmwaveLink_computeCRC(rlUInt8_t* data, rlUInt32_t dataLen, rlUInt8_t crcType, rlUInt8_t* crc)
{
    CRC_SigGenCfg   signGenCfg;
    int32_t         errCode;
    uint64_t        signature;
    uint32_t        index;
    uint8_t*        ptrSignature;
    uint8_t         crcLength;

    /* Initialize the signature generation configuration */
    memset ((void *)&signGenCfg, 0, sizeof(CRC_SigGenCfg));

    /* Allocate a unique transaction id: */
    if (CRC_getTransactionId (gMmwaveLinkMCB.crcHandle, &signGenCfg.transactionId, &errCode) < 0)
    {
        System_printf ("Error: CRC Driver Get transaction id failed [Error code %d]\n", errCode);
        return -1;
    }

    /* Populate the signature generation configuration: */
    signGenCfg.ptrData = (uint8_t*)data;
    signGenCfg.dataLen = dataLen;

    /* Compute the signature for the specific data on Channel-1 */
    if (CRC_computeSignature (gMmwaveLinkMCB.crcHandle, &signGenCfg, &errCode) < 0)
    {
        System_printf ("Error: CRC Driver compute signature failed [Error code %d]\n", errCode);
        return -1;
    }

    /* Get the Signature for Channel */
    if (CRC_getSignature (gMmwaveLinkMCB.crcHandle, signGenCfg.transactionId, &signature, &errCode) < 0)
    {
        System_printf ("Error: CRC Driver get signature failed [Error code %d]\n", errCode);
        return -1;
    }

    /* Get the pointer to the CRC Signature: */
    ptrSignature = (uint8_t*)&signature;

    /* Determine the length of the CRC: */
    switch (crcType)
    {
        case RL_CRC_TYPE_16BIT_CCITT:
        {
            crcLength = 2;
            break;
        }
        case RL_CRC_TYPE_32BIT:
        {
            crcLength = 4;
            break;
        }
        case RL_CRC_TYPE_64BIT_ISO:
        {
            crcLength = 8;
            break;
        }
        default:
        {
            System_printf ("Error: Unknown CRC Type passed from mmWave Link: %d\n", crcType);
            return -1;
        }
    }

    /* Copy the CRC signature into CRC output array */
    for(index = 0U; index < crcLength; index++)
    {
        *(crc + index) = *(ptrSignature + index);
    }
    if (retryNegativeTestCfg.corruptType == 2)
    {
        if (retryNegativeTestCfg.corruptEvent == 0)
        {
            hit_count++;
            if (hit_count == 1)
            {
                *(crc + 0) = ~(*(crc + 0));
                hit_count = 0;
                retryNegativeTestCfg.corruptType = 0;
            }
        }
        if (retryNegativeTestCfg.corruptEvent == 1)
        {
            hit_count++;
            if (hit_count == 2)
            {
                *(crc + 0) = ~(*(crc + 0));
                hit_count = 0;
                retryNegativeTestCfg.corruptType = 0;
            }
        }
        if (retryNegativeTestCfg.corruptEvent == 2)
        {
            hit_count++;
            if (hit_count == 3)
            {
                *(crc + 0) = ~(*(crc + 0));
                hit_count = 0;
                retryNegativeTestCfg.corruptType = 0;
            }
        }
    }
    
    return 0;
}

/**
 *  @b Description
 *  @n
 *      This is the task which handles the mmWave Link communication
 *      messages between the BSS and MSS.
 *
 *  @retval
 *      Not Applicable.
 */
static void MmwaveLink_mmwaveLinkMgmtTask (UArg arg0, UArg arg1)
{
    RL_P_OSI_SPAWN_ENTRY    spawnFxn;
    uintptr_t               key;
    Semaphore_Params        semParams;

    /* Initialize the mmWave Link Semaphore: */
    Semaphore_Params_init(&semParams);
    semParams.mode  = Semaphore_Mode_BINARY;
    gMmwaveLinkMCB.linkSemaphore = Semaphore_create(0, &semParams, NULL);
    if (gMmwaveLinkMCB.linkSemaphore == NULL)
    {
        return;
    }

    /* Execute forever: */
    while (1)
    {
        /* Pending on the link semaphore */
        Semaphore_pend (gMmwaveLinkMCB.linkSemaphore, BIOS_WAIT_FOREVER);

        /* Critical Section: We record the spawn function which is to be executed */
        key = Hwi_disable();
        spawnFxn = gMmwaveLinkMCB.spawnFxn;
        gMmwaveLinkMCB.spawnFxn = NULL;
        Hwi_restore (key);

        /* Execute the spawn function: */
        if (spawnFxn != NULL)
        {
            spawnFxn (NULL);
        }
    }
}


/**
 *  @b Description
 *  @n
 *      The function is used to get and display the version information
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_getVersion (void)
{
    rlVersion_t verArgs;
    int32_t     retVal;
    /* currently patch binaries are available for AWR16 ES2.0 & IWR16 ES2.0 only*/
    int8_t rfPatchBuildVer, rfPatchDebugVer;

    /* Get the version string: */
    retVal = rlDeviceGetVersion(RL_DEVICE_MAP_INTERNAL_BSS, &verArgs);
    if (retVal != 0)
    {
        System_printf ("Error: Unable to get the device version from mmWave link [Error %d]\n", retVal);
        return -1;
    }

    /* Display the version information */
    System_printf ("RF H/W Version    : %02d.%02d\n",
                    verArgs.rf.hwMajor, verArgs.rf.hwMinor);
    System_printf ("RF F/W Version    : %02d.%02d.%02d.%02d.%02d.%02d.%02d\n",
                    verArgs.rf.fwMajor, verArgs.rf.fwMinor, verArgs.rf.fwBuild, verArgs.rf.fwDebug,
                    verArgs.rf.fwYear, verArgs.rf.fwMonth, verArgs.rf.fwDay);
    rfPatchDebugVer = ((verArgs.rf.patchBuildDebug) & 0x0F);
    rfPatchBuildVer = (((verArgs.rf.patchBuildDebug) & 0xF0) >> 4);

    System_printf ("RF F/W Patch Version : %02d.%02d.%02d.%02d.%02d.%02d.%02d\n",
                    verArgs.rf.patchMajor, verArgs.rf.patchMinor, rfPatchBuildVer, rfPatchDebugVer,
                    verArgs.rf.patchYear, verArgs.rf.patchMonth, verArgs.rf.patchDay);
    System_printf ("mmWaveLink Version: %02d.%02d.%02d.%02d\n",
                    verArgs.mmWaveLink.major, verArgs.mmWaveLink.minor,
                    verArgs.mmWaveLink.build, verArgs.mmWaveLink.debug);
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to initialize and setup the mmWave link
 *
 *  @retval
 *      Success - 0
 *  @retval
 *      Error   - <0
 */
int32_t MmwaveLink_initLink (rlUInt8_t deviceType, rlUInt8_t platform)
{
    Task_Params            taskParams;
    CRC_Config          crcCfg;
    rlClientCbs_t       RlApp_ClientCtx;
    int32_t             errCode;

    /* Initialize and populate the Mmwave Link MCB */
    memset ((void*)&gMmwaveLinkMCB, 0, sizeof(MmwaveLink_MCB));

    /*****************************************************************************
     * Start CRC driver:
     *****************************************************************************/

    /* Setup the default configuration: */
    CRC_initConfigParams(&crcCfg);

#if 1
    /*******************************************************************************
     * This is the configuration for the 16bit CRC Type:
     *******************************************************************************/
    crcCfg.channel  = CRC_Channel_CH1;
    crcCfg.mode     = CRC_Operational_Mode_FULL_CPU;
    crcCfg.type     = CRC_Type_16BIT;
    crcCfg.bitSwap  = CRC_BitSwap_MSB;
    crcCfg.byteSwap = CRC_ByteSwap_ENABLED;
    crcCfg.dataLen  = CRC_DataLen_16_BIT;
#endif
#if 0
    /*******************************************************************************
     * This is the configuration for the 32bit CRC Type:
     *******************************************************************************/
    crcCfg.channel  = CRC_Channel_CH1;
    crcCfg.mode     = CRC_Operational_Mode_FULL_CPU;
    crcCfg.type     = CRC_Type_32BIT;
    crcCfg.bitSwap  = CRC_BitSwap_LSB;
    crcCfg.byteSwap = CRC_ByteSwap_DISABLED;
    crcCfg.dataLen  = CRC_DataLen_32_BIT;
#endif
#if 0
    /*******************************************************************************
     * This is the configuration for the 64bit CRC Type:
     *******************************************************************************/
    crcCfg.channel  = CRC_Channel_CH1;
    crcCfg.mode     = CRC_Operational_Mode_FULL_CPU;
    crcCfg.type     = CRC_Type_64BIT;
    crcCfg.bitSwap  = CRC_BitSwap_MSB;
    crcCfg.byteSwap = CRC_ByteSwap_ENABLED;
    crcCfg.dataLen  = CRC_DataLen_32_BIT;
#endif

    /* Open the CRC Driver */
    gMmwaveLinkMCB.crcHandle = CRC_open (&crcCfg, &errCode);
    if (gMmwaveLinkMCB.crcHandle == NULL)
    {
        System_printf ("Error: Unable to open the CRC Channel [Error Code %d]\n", errCode);
        return -1;
    }
    System_printf("Debug: CRC Channel %p has been opened successfully\n", gMmwaveLinkMCB.crcHandle);

    /*****************************************************************************
     * Launch the Mmwave Link Tasks:
     *****************************************************************************/

    /* Initialize and Launch the mmWave Link Management Task: */
    Task_Params_init(&taskParams);
    taskParams.priority = 5;
    Task_create(MmwaveLink_mmwaveLinkMgmtTask, &taskParams, NULL);

    /*****************************************************************************
     * Initialize the mmWave Link: We need to have the link management task
     * operational to be able to process the SPAWN function.
     *****************************************************************************/

    /* Reset the client context: */
    memset ((void *)&RlApp_ClientCtx, 0, sizeof(rlClientCbs_t));

    RlApp_ClientCtx.ackTimeout  = 1000U;

    /* Setup the crc Type in the mmWave link and synchronize this with the
     * created CRC Channel. */
    if (crcCfg.type == CRC_Type_16BIT)
        RlApp_ClientCtx.crcType = RL_CRC_TYPE_16BIT_CCITT;
    else if (crcCfg.type == CRC_Type_32BIT)
        RlApp_ClientCtx.crcType = RL_CRC_TYPE_32BIT;
    else
        RlApp_ClientCtx.crcType = RL_CRC_TYPE_64BIT_ISO;

    /* Setup the platform on which the mmWave Link executes */
    RlApp_ClientCtx.platform  = platform;
    RlApp_ClientCtx.arDevType = deviceType;

    /* Initialize the Communication Interface API: */
    RlApp_ClientCtx.comIfCb.rlComIfOpen     = MmwaveLink_mboxOpen;
    RlApp_ClientCtx.comIfCb.rlComIfClose    = MmwaveLink_mboxClose;
    RlApp_ClientCtx.comIfCb.rlComIfRead     = MmwaveLink_mboxRead;
    RlApp_ClientCtx.comIfCb.rlComIfWrite    = MmwaveLink_mboxWrite;

    /* Initialize OSI Mutex Interface */
    RlApp_ClientCtx.osiCb.mutex.rlOsiMutexCreate = Osal_mutexCreate;
    RlApp_ClientCtx.osiCb.mutex.rlOsiMutexLock   = Osal_mutexLock;
    RlApp_ClientCtx.osiCb.mutex.rlOsiMutexUnLock = Osal_mutexUnlock;
    RlApp_ClientCtx.osiCb.mutex.rlOsiMutexDelete = Osal_mutexDelete;

    /* Initialize OSI Semaphore Interface */
    RlApp_ClientCtx.osiCb.sem.rlOsiSemCreate    = Osal_semCreate;
    RlApp_ClientCtx.osiCb.sem.rlOsiSemWait      = Osal_semWait;
    RlApp_ClientCtx.osiCb.sem.rlOsiSemSignal    = Osal_semSignal;
    RlApp_ClientCtx.osiCb.sem.rlOsiSemDelete    = Osal_semDelete;

    /* Initialize OSI Queue Interface */
    RlApp_ClientCtx.osiCb.queue.rlOsiSpawn      = MmwaveLink_spawn;

    /* Initialize OSI Timer Interface */
    RlApp_ClientCtx.timerCb.rlDelay             = NULL;

    /* Initialize the CRC Interface */
    RlApp_ClientCtx.crcCb.rlComputeCRC          = MmwaveLink_computeCRC;

    /* Initialize Device Control Interface */
    RlApp_ClientCtx.devCtrlCb.rlDeviceDisable            = MmwaveLink_disableDevice;
    RlApp_ClientCtx.devCtrlCb.rlDeviceEnable             = MmwaveLink_enableDevice;
    RlApp_ClientCtx.devCtrlCb.rlDeviceMaskHostIrq        = MmwaveLink_maskHostIRQ;
    RlApp_ClientCtx.devCtrlCb.rlDeviceUnMaskHostIrq      = MmwaveLink_unmaskHostIRQ;
    RlApp_ClientCtx.devCtrlCb.rlRegisterInterruptHandler = MmwaveLink_registerInterruptHandler;

    /* Initialize the Asynchronous Event Handler: */
    RlApp_ClientCtx.eventCb.rlAsyncEvent    = MmwaveLink_asyncEventHandler;

    /* Power on the Device */
    if (rlDevicePowerOn(1U, RlApp_ClientCtx) != 0)
    {
        System_printf("Error: Power on request to the BSS failed\n");
        return -1;
    }

    /* Power off the Device */
    if(rlDevicePowerOff()  != 0)
    {
        System_printf("Error: Power off request to the BSS failed\n");
        return -1;
    }

    /* Power on the Device again */
    if (rlDevicePowerOn(1U, RlApp_ClientCtx) != 0)
    {
        System_printf("Error: Second Power on request to the BSS failed\n");
        return -1;
    }
    
    return 0;
}

int32_t MmwaveLink_getRfBootupStatus (void)
{
    int32_t         retVal;
    rlRfBootStatusCfg_t statusCfg = {0};

    /* Get RF Boot status */
    retVal = rlGetRfBootupStatus(RL_DEVICE_MAP_INTERNAL_BSS, &statusCfg);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlGetRfBootupStatus retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to set/send mmWave Link Channel Configuration to the BSS.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setChannelConfig (void)
{
    int32_t         retVal;
    
    /* Set channel configuration */
    retVal = rlSetChannelConfig(RL_DEVICE_MAP_INTERNAL_BSS, &chCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: setChannelConfig retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Sets Loop Back burst configuration.
 *
 *  @param Type of loop back
 *         1 - IF Loop Backm, 2 - PS Loop Back, 3 - PA Loop Back, Others - No Loop Back
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_rlSetLoopBackBurstCfg(uint8_t loopBackType)
{
    int32_t         retVal;
    rlLoopbackBurst_t data ={ 0 };
    if ((loopBackType >=1) && (loopBackType <= 3))
    {
        data.loopbackSel = loopBackType;
    }
    else
    {
        data.loopbackSel = 0;
    }
    data.baseProfileIndx = 0;
    data.burstIndx = 0;
    data.freqConst = 1435384036U;
    data.slopeConst = -2077;
    data.txBackoff = 0;
    data.rxGain = 30;
    data.txEn = 0;
    data.bpmConfig = 0;
    data.digCorrDis = 0;
    data.ifLbFreq = 0;
    data.ifLbMag = 10;
    data.ps1PgaIndx = 10;
    data.ps2PgaIndx = 10;
    data.psLbFreq = 0;
    data.paLbFreq =100;

    /* Set Loop Back burst configuration */
    retVal = rlSetLoopBckBurstCfg(RL_DEVICE_MAP_INTERNAL_BSS, &data);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlSetLoopBckBurstCfg retVal=%d\n", retVal);
        return -1;
    }
    
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function Configure chirps dynamically.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_rlSetDynChirpCfg(void)
{
    int32_t         retVal;
    
    rlDynChirpCfg_t *dynChirpData[NUM_OF_DYNAMIC_CHIRP_CONFIG_SEG] = {(rlDynChirpCfg_t*)&dynChirpCfg[0], 
                                 (rlDynChirpCfg_t*)&dynChirpCfg[1],(rlDynChirpCfg_t*)&dynChirpCfg[2],
                                 (rlDynChirpCfg_t*)&dynChirpCfg[3]};

    /* Set Dynamic chirp configuration */
    retVal = rlSetDynChirpCfg(RL_DEVICE_MAP_INTERNAL_BSS, 4U, (rlDynChirpCfg_t**)&dynChirpData[0U]);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlSetDynChirpCfg retVal=%d\n", retVal);
        return -1;
    }
    return 0;
}

int32_t MmwaveLink_rlSetDynChirpEn(void)
{
    int32_t retVal;
    rlDynChirpEnCfg_t dynChirpEnCfg = {0};

    /* Dynamic chirp enable */
    retVal = rlSetDynChirpEn(RL_DEVICE_MAP_INTERNAL_BSS, &dynChirpEnCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlSetDynChirpEn retVal=%d\n", retVal);
        return -1;
    }
    return 0;
}

int32_t MmwaveLink_rlSetDynPerChirpPhShifterCfg(void)
{
    int32_t         retVal;
    rlDynPerChirpPhShftCfg_t data[1] ={ 0 };
    data[0].chirpSegSel = 20;

    /* Set Dynamic per chirp phase shifter configuration */
    retVal = rlSetDynPerChirpPhShifterCfg(RL_DEVICE_MAP_INTERNAL_BSS, 1, (rlDynPerChirpPhShftCfg_t**)&data);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlSetDynPerChirpPhShifterCfg retVal=%d\n", retVal);
        return -1;
    }
    
    return 0;
}


/**
 *  @b Description
 *  @n
 *      The function is used to set/send the Adc out configuration to the BSS.
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setAdcOutConfig (void)
{
    int32_t         retVal;

    /* Set ADC out configuration */
    retVal = rlSetAdcOutConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlAdcOutCfg_t*)&adcOutCfgArgs);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: setAdcOutConfig retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to set low power mode.
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setLowPowerModeConfig (void)
{
    int32_t         retVal;

    /* Set Low power mode configuration */
    retVal = rlSetLowPowerModeConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlLowPowerModeCfg_t*)&lowPowerModeCfg);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: setLowPowerMode retVal=%d\n", retVal);
        return -1;
    }

    System_printf("Debug: Finished setLowPowerMode\n");

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to test Set HSI clock API.
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setHsiClk (void)
{
    int32_t     retVal;

    /* Set HSI clock */
    retVal = rlDeviceSetHsiClk(RL_DEVICE_MAP_INTERNAL_BSS, (rlDevHsiClk_t*)&deviceHsiClk);
    if (retVal != 0)
    {
        System_printf ("Error: Unable to set HSI clock [Error %d]\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to test RF Init/Calibration API.
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_rfCalibration (void)
{
    int32_t     retVal;

    /* RF Initialization */
    retVal = rlRfInit(RL_DEVICE_MAP_INTERNAL_BSS);
    if (retVal != 0)
    {
        System_printf ("Error: Unable to start RF [Error %d]\n", retVal);
        return -1;
    }
    while(gInitTimeCalibStatus == 0U)
    {
        /* Sleep and poll again: */
        Task_sleep(1);
    }
    gInitTimeCalibStatus = 0U;
    System_printf("Debug: RF start successfully\n");

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to set Profile configuration.
 *      using the mmWave link API. 
 *      Note that this always configures numProfiles profiles.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setProfileConfig (uint16_t numProfiles)
{
    int32_t         retVal;
    
    if((numProfiles > 4) || (numProfiles == 0))
    {
        System_printf("Error: MmwaveLink_setProfileConfig numProfiles=%d is invalid\n", numProfiles);
        return -1;
    }

    /* Set Profile configuration */
    retVal = rlSetProfileConfig(RL_DEVICE_MAP_INTERNAL_BSS, numProfiles, (rlProfileCfg_t*)&profileCfg[0U]);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlSetProfileConfig retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to get Profile configuration.
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_getProfileConfig (void)
{
    int32_t         retVal, i;
    rlProfileCfg_t  getProfileData = { 0 };

    for(i = 0; i< gTestMiscCfg.numProfiles; i++)
    {
        /* Get profile configuration */
        retVal = rlGetProfileConfig(RL_DEVICE_MAP_INTERNAL_BSS, i, (rlProfileCfg_t*)&getProfileData);
    
        /* Check for mmWaveLink API call status */
        if(retVal != 0)
        {
            /* Error: Link reported an issue. */
            System_printf("Error: rlGetProfileConfig retVal=%d\n", retVal);
            return -1;
        }
        if((getProfileData.adcStartTimeConst != profileCfg[i].adcStartTimeConst) || \
           (getProfileData.digOutSampleRate != profileCfg[i].digOutSampleRate) || \
           (getProfileData.freqSlopeConst != profileCfg[i].freqSlopeConst) || \
           (getProfileData.hpfCornerFreq1 != profileCfg[i].hpfCornerFreq1) || \
           (getProfileData.hpfCornerFreq2 != profileCfg[i].hpfCornerFreq2) || \
           (getProfileData.idleTimeConst != profileCfg[i].idleTimeConst) || \
           (getProfileData.numAdcSamples != profileCfg[i].numAdcSamples) || \
           (getProfileData.profileId != profileCfg[i].profileId) || \
           (getProfileData.rampEndTime != profileCfg[i].rampEndTime) || \
           (getProfileData.rxGain != profileCfg[i].rxGain) || \
           (getProfileData.startFreqConst != profileCfg[i].startFreqConst) || \
           (getProfileData.txOutPowerBackoffCode != profileCfg[i].txOutPowerBackoffCode) || \
           (getProfileData.txPhaseShifter != profileCfg[i].txPhaseShifter) || \
           (getProfileData.txStartTime != profileCfg[i].txStartTime))
        {
            System_printf("Error: rlGetProfileConfig parameters not matched with configured parameters\n", retVal);
            retVal = -1;
        }
    }
    
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to set Chirp configuration.
 *      using the mmWave link API.
 *
 *      Note that this function sends numChirpConfigs chirp configs in one call.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setChirpConfig (uint16_t numChirpConfigs)
{
    int32_t         retVal;

    if(numChirpConfigs > DFPTEST_MAX_NUM_CHIRPCFG) 
    {
        System_printf("Error: MmwaveLink_setChirpConfig numChirpConfigs=%d. Max allowed value is %d\n", 
                      numChirpConfigs, DFPTEST_MAX_NUM_CHIRPCFG);
        return -1;
    }

    retVal = rlSetChirpConfig(RL_DEVICE_MAP_INTERNAL_BSS, numChirpConfigs, (rlChirpCfg_t*)&chirpCfg[0]);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlSetChirpConfig retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to set Multiple Chirp configurations.
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setMultiChirpConfig (void)
{
    int32_t         retVal;
    rlChirpCfg_t * multiChirpData[2] = {(rlChirpCfg_t*)&chirpCfg[0], (rlChirpCfg_t*)&chirpCfg[1]};

    /* Set multiple chirp configuration */
    retVal = rlSetMultiChirpCfg(RL_DEVICE_MAP_INTERNAL_BSS, 2U, &multiChirpData[0]);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlSetMultiChirpCfg retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

rlChirpCfg_t getChirpCfg[DFPTEST_MAX_NUM_CHIRPCFG] = {0};
/**
 *  @b Description
 *  @n
 *      The function is used to Get Chirp configuration.
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_getChirpConfig (uint16_t startIdx, uint16_t endIdx)
{
    int32_t retVal;
    
    if(endIdx - startIdx + 1 > DFPTEST_MAX_NUM_CHIRPCFG)
    {
        System_printf("Error: MmwaveLink_getChirpConfig number of chirps=%d exceeds DFPTEST_MAX_NUM_CHIRPCFG\n", endIdx - startIdx + 1);
        return -1;
    }

    /* Get chirp configuration */
    retVal = rlGetChirpConfig(RL_DEVICE_MAP_INTERNAL_BSS, startIdx, endIdx, &getChirpCfg[0]);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlGetChirpConfig retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to Get Chirp configuration.
 *      using the mmWave link API.
 *
 *  @param Configure type. 0 - Old configuration, 1 - New configuration
 *
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_getDynChirpConfig (void)
{
    int32_t retVal, i = 0,j = 0;
    uint16_t startIdx;

    if (dynChirpCfg[0].chirpRowSelect == 0x00)
    {
        startIdx = dynChirpCfg[0].chirpSegSel*16;
    }
    else
    {
        startIdx = dynChirpCfg[0].chirpSegSel*48;
    }
    
    retVal = MmwaveLink_getChirpConfig(startIdx, startIdx + 9);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlGetChirpConfig retVal=%d\n", retVal);
        return -1;
    }
    /* compare each chirpConfig parameters to lastly configured via rlDynChirpConfig API */
    while (i <= 9)
    {
        if (dynChirpCfg[0].chirpRowSelect == 0x00)
        {
            if ((getChirpCfg[i].profileId != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR1, 4, 0)) || \
                (getChirpCfg[i].freqSlopeVar != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR1, 6, 8)) || \
                (getChirpCfg[i].txEnable != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR1, 3, 16)) || \
                (getChirpCfg[i].startFreqVar != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR2, 23, 0)) || \
                (getChirpCfg[i].idleTimeVar != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR3, 12, 0)) || \
                (getChirpCfg[i].adcStartTimeVar != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR3, 12, 16)))
            {
                break;
            }
            i++;
        }
        else if (dynChirpCfg[0].chirpRowSelect == 0x10)
        {
            if ((getChirpCfg[i].profileId != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR1, 4, 0)) || \
                (getChirpCfg[i].freqSlopeVar != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR1, 6, 8)) || \
                (getChirpCfg[i].txEnable != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR1, 3, 16)))
            {
                break;
            }
            i++;
            if ((getChirpCfg[i].profileId != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR2, 4, 0)) || \
                (getChirpCfg[i].freqSlopeVar != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR2, 6, 8)) || \
                (getChirpCfg[i].txEnable != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR2, 3, 16)))
            {
                break;
            }
            i++;
            if ((getChirpCfg[i].profileId != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR3, 4, 0)) || \
                (getChirpCfg[i].freqSlopeVar != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR3, 6, 8)) || \
                (getChirpCfg[i].txEnable != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR3, 3, 16)))
            {
                break;
            }
            i++;
        }
        else if (dynChirpCfg[0].chirpRowSelect == 0x20)
        {
            if (getChirpCfg[i].startFreqVar != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR1, 23, 0))
            {
                break;
            }
            i++;
            if (getChirpCfg[i].startFreqVar != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR2, 23, 0))
            {
                break;
            }
            i++;
            if (getChirpCfg[i].startFreqVar != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR3, 23, 0))
            {
                break;
            }
            i++;
        }
        else if (dynChirpCfg[0].chirpRowSelect == 0x30)
        {
            if ((getChirpCfg[i].idleTimeVar != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR1, 12, 0)) || \
                (getChirpCfg[i].adcStartTimeVar != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR1, 12, 16)))
            {
                break;
            }
            i++;
            if ((getChirpCfg[i].idleTimeVar != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR2, 12, 0)) || \
                (getChirpCfg[i].adcStartTimeVar != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR2, 12, 16)))
            {
                break;
            }
            i++;
            if ((getChirpCfg[i].idleTimeVar != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR3, 12, 0)) || \
                (getChirpCfg[i].adcStartTimeVar != GET_BIT_VALUE(dynChirpCfg[0].chirpRow[j].chirpNR3, 12, 16)))
            {
                break;
            }
            i++;
        }
        j++;
    }
    if (i <= 9)
    {
        retVal = -1;
        System_printf("Error: Parameters are mismatched GetChirpConfig compare to dynChirpConfig\n");
    }
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to set Frame configuration.
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setFrameConfig (void)
{
    int32_t         retVal;

    /* Set frame configuration */
    retVal = rlSetFrameConfig(RL_DEVICE_MAP_INTERNAL_BSS, &frameCfg);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlSetFrameConfig retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to get Frame configuration.
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_getFrameConfig (void)
{
    int32_t         retVal;
    rlFrameCfg_t    frameData = { 0 };
    /* Get Frame configuration */
    retVal = rlGetFrameConfig(RL_DEVICE_MAP_INTERNAL_BSS, &frameData);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlGetFrameConfig retVal=%d\n", retVal);
        return -1;
    }

    if((frameData.chirpEndIdx != frameCfg.chirpEndIdx) || \
       (frameData.chirpStartIdx != frameCfg.chirpStartIdx) || \
       (frameData.framePeriodicity != frameCfg.framePeriodicity) || \
       (frameData.frameTriggerDelay != frameCfg.frameTriggerDelay) || \
       (frameData.numFrames != frameCfg.numFrames) || \
       (frameData.numLoops != frameCfg.numLoops) || \
       (frameData.triggerSelect != frameCfg.triggerSelect))
    {
        System_printf("Error: rlGetFrameConfig parameters not matched with configured parameters\n", retVal);
        retVal = -1;
    }
    
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to get Advance Frame configuration.
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_getAdvFrameConfig (void)
{
    int32_t            retVal;
    rlAdvFrameCfg_t    advFrameData = { 0 };
    /* Get Advance frame configuration */
    retVal = rlGetAdvFrameConfig(RL_DEVICE_MAP_INTERNAL_BSS, &advFrameData);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlGetAdvFrameConfig retVal=%d\n", retVal);
        return -1;
    }

    if((advFrameData.frameSeq.forceProfile != advFrameCfg.frameSeq.forceProfile) || \
       (advFrameData.frameSeq.frameTrigDelay != advFrameCfg.frameSeq.frameTrigDelay) || \
       (advFrameData.frameSeq.numFrames != advFrameCfg.frameSeq.numFrames) || \
       (advFrameData.frameSeq.numOfSubFrames != advFrameCfg.frameSeq.numOfSubFrames))
    {
        System_printf("Error: rlGetAdvFrameConfig parameters not matched with configured parameters\n", retVal);
        retVal = -1;
    }
    
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to test start sensor API.
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_sensorStart (void)
{
    int32_t     retVal;

    /* Trigger the frame */
    retVal = rlSensorStart(RL_DEVICE_MAP_INTERNAL_BSS);
    if (retVal != 0)
    {
        System_printf ("Error: Unable to start Sensor [Error %d]\n", retVal);
        return -1;
    }
    /* if frame start async event is enable by rlRfSetDeviceCfg API,
       then wait for Frame start async event */
    if ((rfDevCfg.aeControl & 0x1) == 0x0)
    {
        while(gFrameStartStatus == 0U)
        {
            /* Sleep and poll again: */
            Task_sleep(1);
        }
    }
    return 0;
}


/**
 *  @b Description
 *  @n
 *      The function is used to test stop sensor API.
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_sensorStop (void)
{
    int32_t     retVal;

    /* Stop the frame */
    retVal = rlSensorStop(RL_DEVICE_MAP_INTERNAL_BSS);
    if (retVal != 0)
    {
        if(retVal == RL_RET_CODE_FRAME_ALREADY_ENDED)
        {
            System_printf ("Debug: Frames are already stopped  [%d]\n", retVal);
            return 0;
        }
        System_printf ("Error: Unable to stop Sensor [Error %d]\n", retVal);
        return -1;
    }

    /* if frame stop async event is enable by rlRfSetDeviceCfg API,
        then wait for Frame stop async event */
    if ((rfDevCfg.aeControl & 0x2) == 0x0)
    {
        while(gFrameStartStatus == 1U)
        {
            /* Sleep and poll again: */
            Task_sleep(1);
        }
    }
    System_printf("Debug: Sensor stop successfully\n");

    return 0;
}


/**
 *  @b Description
 *  @n
 *      The function is used to set advance Frame configuration.
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setAdvFrameConfig (void)
{
    int32_t         retVal;

    /* Set advance frame configuration */
    retVal = rlSetAdvFrameConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlAdvFrameCfg_t*)&advFrameCfg);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlSetAdvFrameConfig retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}


/**
 *  @b Description
 *  @n
 *      The function is used to set Binary Phase Modulation Common configuration.
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setBpmCommonConfig (void)
{
    int32_t         retVal;

    /* Set BPM common configuration */
    retVal = rlSetBpmCommonConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlBpmCommonCfg_t*)&bpmCommonCfg);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlSetBpmCommonConfig retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to set Binary Phase Modulation Chirp configuration.
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setBpmChirpConfig (uint16_t numBpmChirpConfigs)
{
    int32_t         retVal, i;

    if(numBpmChirpConfigs > DFPTEST_MAX_NUM_BPMCHIRPCFG) 
    {
        System_printf("Error: MmwaveLink_setBpmChirpConfig numBpmChirpConfigs=%d. Max allowed value is %d\n", 
                      numBpmChirpConfigs, DFPTEST_MAX_NUM_BPMCHIRPCFG);
        return -1;
    }
    
    /* Set BPM chirp configuration */
    for(i=0; i<numBpmChirpConfigs; i++)
    {
        retVal = rlSetBpmChirpConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlBpmChirpCfg_t*)&bpmChirpCfg[i]);

        /* Check for mmWaveLink API call status */
        if(retVal != 0)
        {
            /* Error: Link reported an issue. */
            System_printf("Error: rlSetBpmChirpConfig retVal=%d\n", retVal);
            return -1;
        }
    }    

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to set Continous mode Configuration.
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setContModeConfig (void)
{
    int32_t         retVal;

    /* Set continue mode configuration */
    retVal = rlSetContModeConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlContModeCfg_t*)&contModeCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
    System_printf("Error: rlSetContModeConfig retVal=%d\n", retVal);
        return -1;
    }

    System_printf("Debug: Finished rlSetContModeConfig\n");

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to Enable/Disable Continous mode
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_enableContMode (uint8_t bEnable)
{
    int32_t         retVal;
    rlContModeEn_t contModeEnable;

    contModeEnable.contModeEn = bEnable;

    /* Enable Continous mode */
    retVal = rlEnableContMode(RL_DEVICE_MAP_INTERNAL_BSS, (rlContModeEn_t*)&contModeEnable);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlEnableContMode retVal=%d\n", retVal);
        return -1;
    }

    System_printf("Debug: Finished rlEnableContMode\n");

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to Configure dynamic power saving feature
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_rfDynamicPowerSave (void)
{
    int32_t         retVal;

    /* Set Dynamic power save configuration */
    retVal = rlRfDynamicPowerSave(RL_DEVICE_MAP_INTERNAL_BSS, (rlDynPwrSave_t*)&dynPwrSave);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
    System_printf("Error: rlRfDynamicPowerSave retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to Configure asynchronous event direction for device
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setRfDevCfg (rlUInt32_t dirData)
{
    int32_t         retVal;
    rfDevCfg.aeDirection = dirData; /* 0xa: BSS to DSS, 0: BSS to MSS */

    /* Set Device configuration */
    retVal = rlRfSetDeviceCfg(RL_DEVICE_MAP_INTERNAL_BSS, &rfDevCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfSetDeviceCfg retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to Configure GP ADC data parameters
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_setGpAdcConfig (void)
{
    int32_t         retVal;

    /* Set GPADC configuration */
    retVal = rlSetGpAdcConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlGpAdcCfg_t*)&gpAdcCfg);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlSetGpAdcConfig retVal=%d\n", retVal);
        return -1;
    }

    while(isGetGpAdcMeasData == 0U)
    {
        /* Sleep and poll again: */
        Task_sleep(1);
    }
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to Enables/Disables LDO bypass mode
 *      using the mmWave link API.
 *  @Note - This API is required to bypass LDO for specific board/PMIC configuration.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_rfSetLdoBypassConfig (void)
{
    int32_t         retVal;

    /* Set LDO bypass configuration */
    retVal = rlRfSetLdoBypassConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlRfLdoBypassCfg_t*)&rfLdoBypassCfg);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
    System_printf("Error: rlRfSetLdoBypassConfig retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}


/**
 *  @b Description
 *  @n
 *      The function is used to Enable External Programmable filter
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_progFilterConfig (void)
{
    int32_t         retVal;

    /* Set Programmable filter configuration */
    retVal = rlRfSetProgFiltConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlRfProgFiltConf_t*)&progFiltCfg);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfSetProgFiltConfig retVal=%d\n", retVal);
        return -1;
    }

    /* Set Programmable filter RAM coeffecients */
    retVal = rlRfSetProgFiltCoeffRam(RL_DEVICE_MAP_INTERNAL_BSS, (rlRfProgFiltCoeff_t*)&progFiltCoef);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfSetProgFiltCoeffRam retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

int32_t mmwaveLink_triggerSubframe (void)
{
    int32_t         retVal;

    /* trigger subframe */
    retVal = rlSetSubFrameStart(RL_DEVICE_MAP_INTERNAL_BSS, (rlSubFrameStartCfg_t*)&subFrameTrigCfg);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlSetSubFrameStart retVal=%d\n", retVal);
        return -1;
    }
    
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to Enable Misc feature such as per chirp phase shifter
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_miscConfig(void)
{
    int32_t         retVal;

    /* Set RF Misc configuration */
    retVal = rlRfSetMiscConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlRfMiscConf_t*)&miscCfg);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfSetMiscConfig retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to Configure static per chirp phase shifter
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_perChirpPhaseShifterConfig(void)
{
    int32_t         retVal;

    /* Set Phase shifter configuration */
    retVal = rlRfSetPhaseShiftConfig(RL_DEVICE_MAP_INTERNAL_BSS, 2U, (rlRfPhaseShiftCfg_t*)&phaseShiftCfg[0]);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfSetPhaseShiftConfig retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to Configure per chirp phase shifter dynamically
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_dynPerChirpPhaseShifterConfig(void)
{
    int32_t         retVal;
    rlDynPerChirpPhShftCfg_t *dynChirpData[NUM_OF_DYNAMIC_CHIRP_CONFIG_SEG] = {(rlDynPerChirpPhShftCfg_t*)&dynChirpCfg[0],
                             (rlDynPerChirpPhShftCfg_t*)&dynChirpCfg[1], (rlDynPerChirpPhShftCfg_t*)&dynChirpCfg[2],
                             (rlDynPerChirpPhShftCfg_t*)&dynChirpCfg[3]};

    /* Set Dynamic per chirp phase shifter configuration */
    retVal = rlSetDynPerChirpPhShifterCfg(RL_DEVICE_MAP_INTERNAL_BSS, 4U, (rlDynPerChirpPhShftCfg_t**)&dynChirpData[0U]);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlSetDynPerChirpPhShifterCfg retVal=%d\n", retVal);
        return -1;
    }
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to induce different gain/phase offsets on the different RXs, for
 *      inter-RX mismatch compensation using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_interRxGainConfig(void)
{
    int32_t         retVal;

    /* Set Inter RX Gain phase configuration */
    retVal = rlRfInterRxGainPhaseConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlInterRxGainPhConf_t*)&interRxGainPhCfg);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfInterRxGainPhaseConfig retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to reads Temperature information from all temperature
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_getTemperatureReport(void)
{
    int32_t         retVal;
    rlRfTempData_t tempData = { 0 };

    /* Get Temerature report */
    retVal = rlRfGetTemperatureReport(RL_DEVICE_MAP_INTERNAL_BSS, (rlRfTempData_t*)&tempData);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfGetTemperatureReport retVal=%d\n", retVal);
        return -1;
    }
    /* Display the temperature readings */
    System_printf ("Debug : Temerature readings\n");
    System_printf ("RX0 : %3d degree C, RX1 : %3d degree C, RX2 : %3d degree C, RX3 : %3d degree C\n",
                   tempData.tmpRx0Sens, tempData.tmpRx1Sens, tempData.tmpRx2Sens, tempData.tmpRx3Sens);
    System_printf ("TX0 : %3d degree C, TX1 : %3d degree C, TX2 : %3d degree C\n",
                   tempData.tmpTx0Sens, tempData.tmpTx1Sens, tempData.tmpTx2Sens);
    System_printf ("PM  : %3d degree C, DIG0: %3d degree C",
                   tempData.tmpPmSens, tempData.tmpDig0Sens);
    if (gTestMiscCfg.dig1TempSensor == true)
    {
        System_printf (", DIG1: %3d degree C", tempData.tmpDig1Sens);
    }
    System_printf ("\n");

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to configure Test Source
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_testSourceConfig(void)
{
    int32_t         retVal;

    /* Set Test source configuration */
    retVal = rlSetTestSourceConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlTestSource_t*)&testSourceCfg);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlSetTestSourceConfig retVal=%d\n", retVal);
        return -1;
    }
    
    retVal = rlTestSourceEnable(RL_DEVICE_MAP_INTERNAL_BSS, (rlTestSourceEnable_t*)&testSourceEn);
        if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlTestSourceEnable retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Finished rlTestSourceEnable\n");

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to read Die ID Status
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_getDieIdStaus(void)
{
    int32_t         retVal;
    rlRfDieIdCfg_t dieIdStatus = { 0 };

    /* Get Device DIE ID */
    retVal = rlGetRfDieId(RL_DEVICE_MAP_INTERNAL_BSS, &dieIdStatus);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlGetRfdieId retVal=%d\n", retVal);
        return -1;
    }
    System_printf("Debug: Die ID Status\n");
    System_printf("Lot no : %d, Wafer no: %d\nDie cordinates in wafer. X : %d , Y : %d\n",
                  dieIdStatus.lotNo, dieIdStatus.waferNo, dieIdStatus.devX, dieIdStatus.devY);

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to PA Loop Back Configuration
 *      using the mmWave link API.
 *
 *  @param : Loop Back Enable/Disable
 *           1 - Enable Loop back. 0 - Disable Loop Back
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_PALoopBackConfig(int8_t loopBackEn)
{
    int32_t         retVal;
    rlRfPALoopbackCfg_t data = { 0 };
    data.paLoopbackFreq = 50;
    data.paLoopbackEn = loopBackEn;

    /* Set PA Loop back configuration */
    retVal = rlRfSetPALoopbackConfig(RL_DEVICE_MAP_INTERNAL_BSS, &data);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfSetPALoopbackConfig retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to PS Loop Back Configuration
 *      using the mmWave link API.
 *
 *  @param : Loop Back Enable/Disable
 *           1 - Enable Loop back. 0 - Disable Loop Back
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_PSLoopBackConfig(int8_t loopBackEn)
{
    int32_t         retVal;
    rlRfPSLoopbackCfg_t data = { 0 };
    data.psLoopbackFreq = 2000;
    data.psLoopbackEn = loopBackEn;
    data.psLoopbackTxId = 1;
    data.pgaGainIndex = 23;

    /* Set PS Loop back configuration */
    retVal = rlRfSetPSLoopbackConfig(RL_DEVICE_MAP_INTERNAL_BSS, &data);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfSetPALoopbackConfig retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to IF Loop Back Configuration
 *      using the mmWave link API.
 *
 *  @param : Loop Back Enable/Disable
 *           1 - Enable Loop back. 0 - Disable Loop Back
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_IFLoopBackConfig(int8_t loopBackEn)
{
    int32_t         retVal;
    rlRfIFLoopbackCfg_t data = { 0 };
    data.ifLoopbackFreq = 5;
    data.ifLoopbackEn = loopBackEn;

    /* Set IF Loop back configuration */
    retVal = rlRfSetIFLoopbackConfig(RL_DEVICE_MAP_INTERNAL_BSS, &data);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfSetIFLoopbackConfig retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to RX Gain Temerature LUT Configuration
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_RxGainTempLutConfig(void)
{
    int32_t         retVal;

    /* Set RX Gain LUT */
    retVal = rlRxGainTempLutSet(RL_DEVICE_MAP_INTERNAL_BSS, (rlRxGainTempLutData_t*)&rxGainTempLutData);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRxGainTempLutSet retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to read RX Gain Temerature LUT data
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_RxGainTempLutRead(void)
{
    int32_t         retVal;

    /* Get RX Gain LUT */
    retVal = rlRxGainTempLutGet(RL_DEVICE_MAP_INTERNAL_BSS, (rlRxGainTempLutReadReq_t*)&rxGainTempLutReadCfg,
                                     (rlRxGainTempLutData_t*)&rxGainTempLutData);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRxGainTempLutGet retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to TX Gain Temerature LUT Configuration
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_TxGainTempLutConfig(void)
{
    int32_t         retVal;

    /* Set TX Gain LUT */
    retVal = rlTxGainTempLutSet(RL_DEVICE_MAP_INTERNAL_BSS, (rlTxGainTempLutData_t*)&txGainTempLutData);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlTxGainTempLutSet retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to read TX Gain Temerature LUT data
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_TxGainTempLutRead(void)
{
    int32_t         retVal;

    /* Get TX Gain LUT */
    retVal = rlTxGainTempLutGet(RL_DEVICE_MAP_INTERNAL_BSS, (rlTxGainTempLutReadReq_t*)&txGainTempLutReadCfg,
                                                            &txGainTempLutData);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlTxGainTempLutGet retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to read Calibration Data from device
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_calibDataStore(void)
{
    int32_t         retVal;

    /* Store calibration data */
    retVal = rlRfCalibDataStore(RL_DEVICE_MAP_INTERNAL_BSS, &calibData);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfCalibDataStore retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}


/**
 *  @b Description
 *  @n
 *      The function is used to configure link CRC type.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_configLinkCrc(rlCrcType_t    crcType)
{
    int32_t         retVal;

    retVal = rlDeviceConfigureCrc(crcType);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlDeviceConfigureCrc=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to configure link CRC type.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_configAckTimeout(rlUInt32_t ackTimeout)
{
    int32_t         retVal;

    retVal = rlDeviceConfigureAckTimeout(ackTimeout);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlDeviceConfigureAckTimeout=%d\n", retVal);
        return -1;
    }

    return 0;
}


/**
 *  @b Description
 *  @n
 *      The function is used to write Calibration Data to device using the mmWave link API
 *      which was stored previously using mmwaveLink_calibDataStore.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_calibDataRestore(void)
{
    int32_t         retVal;

    /* Restore calibration data */
    retVal = rlRfCalibDataRestore(RL_DEVICE_MAP_INTERNAL_BSS, &calibData);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfCalibDataRestore retVal=%d\n", retVal);
        return -1;
    }
    while(gInitTimeCalibStatus == 0U)
    {
        /* Sleep and poll again: */
        Task_sleep(1);
    }
    gInitTimeCalibStatus = 0U;

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to read Phase Shifter Calibration Data from device
 *      using the mmWave link API.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_phShiftCalibDataStore(void)
{
    int32_t         retVal;
    phShiftCalibData.PhShiftcalibChunk[0].txIndex = 0x0;
    phShiftCalibData.PhShiftcalibChunk[1].txIndex = 0x1;
    phShiftCalibData.PhShiftcalibChunk[2].txIndex = 0x2;
    /* Store Phase shifter calibration data */
    retVal = rlRfPhShiftCalibDataStore(RL_DEVICE_MAP_INTERNAL_BSS, &phShiftCalibData);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfPhShiftCalibDataStore retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to write Phase Shifter Calibration Data to device using the 
 *      mmWave link API which was stored previously using mmwaveLink_phShiftCalibDataStore.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_phShiftCalibDataRestore(void)
{
    int32_t         retVal;

    /* Restore Phase shifter calibration data */
    retVal = rlRfPhShiftCalibDataRestore(RL_DEVICE_MAP_INTERNAL_BSS, &phShiftCalibData);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfPhShiftCalibDataRestore retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}
/**
 *  @b Description
 *  @n
 *      The function is used to get RF Digital Front End Statistics
 *      using mmwaveLink_phShiftCalibDataStore.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t mmwaveLink_getDfeRxStatisticsReport(void)
{
    int32_t         retVal;
    rlDfeStatReport_t dfeStatReport = { 0 };

    /* Get RX DFE statistics report */
    retVal = rlRfDfeRxStatisticsReport(RL_DEVICE_MAP_INTERNAL_BSS, &dfeStatReport);

    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlRfDfeRxStatisticsReport retVal=%d\n", retVal);
        return -1;
    }

    return 0;
}


/**
 *  @b Description
 *  @n
 *      The function executes negative tests.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t MmwaveLink_negativeTest (void)
{
    int32_t  retVal;
    rlFwVersionParam_t rfVersionData = { 0 };

    /* Negative test 1 : Corrupt Response checksum */
    retryNegativeTestCfg.corruptType = 1;
    retryNegativeTestCfg.corruptEvent = 1;
    retVal = rlDeviceGetRfVersion(RL_DEVICE_MAP_INTERNAL_BSS, &rfVersionData);
    if (retVal == -7)
    {
        /* If application receive checksum mismatch error execute command again to get correct data */
        retVal = rlDeviceGetRfVersion(RL_DEVICE_MAP_INTERNAL_BSS, &rfVersionData);
    }
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: Response checksum corruption failed retVal=%d\n", retVal);
        return -1;
    }
    
    /* Negative test 2 : Corrupt async event checksum */
    retryNegativeTestCfg.corruptType = 1;
    retryNegativeTestCfg.corruptEvent = 2;
    /* Set GPADC configuration */
    retVal = rlSetGpAdcConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlGpAdcCfg_t*)&gpAdcCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlSetGpAdcConfig retVal=%d\n", retVal);
    }
    /* Corrupting checksum for async event, wait for mmwaveLink checksum fail report */
    while(gMmwlChecksumFailAsyncEvent == 0U)
    {
        /* Sleep and poll again: */
        Task_sleep(1);
    }
    gMmwlChecksumFailAsyncEvent = 0U;
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: Async-Event checksum corruption failed retVal=%d\n", retVal);
        return -1;
    }

    /* Negative test 3 : Corrupt async event CRC */
    retryNegativeTestCfg.corruptType = 2;
    retryNegativeTestCfg.corruptEvent = 2;
    /* Set GPADC configuration */
    retVal = rlSetGpAdcConfig(RL_DEVICE_MAP_INTERNAL_BSS, (rlGpAdcCfg_t*)&gpAdcCfg);
    /* Check for mmWaveLink API call status */
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: rlSetGpAdcConfig retVal=%d\n", retVal);
    }
    /* Corrupting CRC for async event, wait for mmwaveLink CRC fail report */
    while(gMmwlCrcFailAsyncEvent == 0U)
    {
        /* Sleep and poll again: */
        Task_sleep(1);
    }
    gMmwlCrcFailAsyncEvent = 0U;
    if(retVal != 0)
    {
        /* Error: Link reported an issue. */
        System_printf("Error: Async-Event CRC corruption failed retVal=%d\n", retVal);
        return -1;
    }
    return 0;
}

/**
 *  @b Description
 *  @n
 *      ADC Buffer configuration to receive chirp interrupt from mmWave 
 *      front end
 *      
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 *
 */
int32_t MmwaveLink_adcBufConfig()
{
    ADCBuf_dataFormat       dataFormat;
    ADCBuf_RxChanConf       rxChanConf;
    int32_t retVal;
    uint8_t      numBytePerSample, numRxChannel = 0, channel;
    uint32_t bufSizePerChan;
    extern rlChanCfg_t chCfg;
    extern rlProfileCfg_t  profileCfg[4];
    extern rlAdcOutCfg_t adcOutCfgArgs;

    /* Configure ADC buffer data format */
    if (adcOutCfgArgs.fmt.b2AdcOutFmt == ADC_FORMAT_REAL)
    {
        dataFormat.adcOutFormat       = 1U; /* 0 - Complex Data mode, 1 - Real data mode */
    }
    else
    {
        dataFormat.adcOutFormat       = 0U; /* 0 - Complex Data mode, 1 - Real data mode */
    }
    dataFormat.sampleInterleave   = 0U;
    dataFormat.channelInterleave  = 1U;

    retVal = ADCBuf_control(adcbufHandle, ADCBufMMWave_CMD_CONF_DATA_FORMAT, (void *)&dataFormat);
    if (retVal < 0)
    {
        System_printf("Error: ADCBufMMWave_CMD_CONF_DATA_FORMAT failed with [Error %d]\n", retVal);
    }
    
    /* Calculate the DMA transfer parameters */
    if (dataFormat.adcOutFormat == 0)
    {
        /* Complex dataFormat has 4 bytes */
        numBytePerSample =  4 ;
    }
    else
    {
        /* Real dataFormat has 2 bytes */
        numBytePerSample =  2 ;
    }
    
    /* Enable the receive channels */
    for (channel = 0; channel < SYS_COMMON_NUM_RX_CHANNEL; channel++)
    {
        /* Is the channel enabled? */
        if (chCfg.rxChannelEn & (0x1 << channel))
        {
            /* YES: Populate the receive channel configuration: */
            rxChanConf.channel = channel;

            /* Calculate ADCBuf size per channel */
            bufSizePerChan = profileCfg[0].numAdcSamples * numBytePerSample;

            /* Chirp Mode: */
            rxChanConf.offset = bufSizePerChan * numRxChannel;

            /* Offset is used in non-interleaved mode and it must be 16 bytes aligned. */
            if(rxChanConf.offset % 16)
            {
               // DebugP_assert(0);
            }

            /* Enable the channel: ADCBuf channel offset address is used for non-interleaved mode, the address must be 16 bytes aligned.*/
            retVal = ADCBuf_control(adcbufHandle, ADCBufMMWave_CMD_CHANNEL_ENABLE, (void *)&rxChanConf);
            if(retVal < 0)
            {
                System_printf("Error: ADCBufMMWave_CMD_CHANNEL_ENABLE failed for channel %d , offset = %x, with [Error %d]\n",
                               channel, rxChanConf.offset, retVal);
            }

            /* Track the number of receive channels: */
            numRxChannel++;
        }
    }
    
    return 0;
}


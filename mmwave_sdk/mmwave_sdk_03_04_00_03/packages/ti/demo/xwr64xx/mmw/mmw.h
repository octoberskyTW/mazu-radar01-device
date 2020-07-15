/**
 *   @file  mmw.h
 *
 *   @brief
 *      This is the main header file for the Millimeter Wave Demo
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
#ifndef MMW_DEMO_H
#define MMW_DEMO_H

#include <ti/common/mmwave_error.h>
#include <ti/drivers/uart/UART.h>
#include <ti/drivers/soc/soc.h>
#include <ti/control/mmwave/mmwave.h>
#include <ti/drivers/osal/DebugP.h>

#include <ti/demo/utils/mmwdemo_adcconfig.h>
#include <ti/demo/utils/mmwdemo_monitor.h>
#include <ti/sysbios/knl/Task.h>

#include <ti/demo/xwr64xx/mmw/mmw_config.h>
#include <ti/demo/xwr64xx/mmw/data_path.h>
#include <ti/demo/xwr64xx/mmw/mmw_lvds_stream.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! @brief For advanced frame config, below define means the configuration given is
 * global at frame level and therefore it is broadcast to all sub-frames.
 */
#define MMWDEMO_SUBFRAME_NUM_FRAME_LEVEL_CONFIG (-1)

/*! @brief CFAR threshold encoding factor
 */
#define MMWDEMO_CFAR_THRESHOLD_ENCODING_FACTOR (100.0)

/**
 * @defgroup configStoreOffsets     Offsets for storing CLI configuration
 * @brief    Offsets of config fields within the parent structures, note these offsets will be
 *           unique and hence can be used to differentiate the commands for processing purposes.
 * @{
 */
#define MMWDEMO_GUIMONSEL_OFFSET                 (offsetof(MmwDemo_SubFrameCfg, guiMonSel))
#define MMWDEMO_ADCBUFCFG_OFFSET                 (offsetof(MmwDemo_SubFrameCfg, adcBufCfg))
#define MMWDEMO_LVDSSTREAMCFG_OFFSET             (offsetof(MmwDemo_SubFrameCfg, lvdsStreamCfg))

#define MMWDEMO_SUBFRAME_DYNCFG_OFFSET           (offsetof(MmwDemo_SubFrameCfg, objDetDynCfg) + \
                                                  offsetof(MmwDemo_DPC_ObjDet_DynCfg, dynCfg))

#define MMWDEMO_CFARCFGRANGE_OFFSET              (MMWDEMO_SUBFRAME_DYNCFG_OFFSET + \
                                                  offsetof(DPC_ObjectDetection_DynCfg, cfarCfgRange))

#define MMWDEMO_CFARCFGDOPPLER_OFFSET            (MMWDEMO_SUBFRAME_DYNCFG_OFFSET + \
                                                  offsetof(DPC_ObjectDetection_DynCfg, cfarCfgDoppler))

#define MMWDEMO_FOVRANGE_OFFSET                  (MMWDEMO_SUBFRAME_DYNCFG_OFFSET + \
                                                  offsetof(DPC_ObjectDetection_DynCfg, fovRange))

#define MMWDEMO_FOVDOPPLER_OFFSET                (MMWDEMO_SUBFRAME_DYNCFG_OFFSET + \
                                                  offsetof(DPC_ObjectDetection_DynCfg, fovDoppler))

#define MMWDEMO_FOVAOA_OFFSET                    (MMWDEMO_SUBFRAME_DYNCFG_OFFSET + \
                                                  offsetof(DPC_ObjectDetection_DynCfg, fovAoaCfg))

#define MMWDEMO_EXTMAXVEL_OFFSET                 (MMWDEMO_SUBFRAME_DYNCFG_OFFSET + \
                                                  offsetof(DPC_ObjectDetection_DynCfg, extMaxVelCfg))

#define MMWDEMO_MULTIOBJBEAMFORMING_OFFSET       (MMWDEMO_SUBFRAME_DYNCFG_OFFSET + \
                                                  offsetof(DPC_ObjectDetection_DynCfg, multiObjBeamFormingCfg))

#define MMWDEMO_CALIBDCRANGESIG_OFFSET           (MMWDEMO_SUBFRAME_DYNCFG_OFFSET + \
                                                  offsetof(DPC_ObjectDetection_DynCfg, calibDcRangeSigCfg))

#define MMWDEMO_STATICCLUTTERREMOFVAL_OFFSET     (MMWDEMO_SUBFRAME_DYNCFG_OFFSET + \
                                                  offsetof(DPC_ObjectDetection_DynCfg, staticClutterRemovalCfg))
/** @}*/ /* configStoreOffsets */

/**
 * @brief
 *  Millimeter Wave Demo statistics
 *
 * @details
 *  The structure is used to hold the statistics information for the
 *  Millimeter Wave demo
 */
typedef struct MmwDemo_Stats_t
{
    /*! @brief   Counter which tracks the number of frame trigger events from BSS */
    uint64_t     frameTriggerReady;
    
    /*! @brief   Counter which tracks the number of failed calibration reports
     *           The event is triggered by an asynchronous event from the BSS */
    uint32_t     failedTimingReports;

    /*! @brief   Counter which tracks the number of calibration reports received
     *           The event is triggered by an asynchronous event from the BSS */
    uint32_t     calibrationReports;

     /*! @brief   Counter which tracks the number of sensor stop events received
      *           The event is triggered by an asynchronous event from the BSS */
    uint32_t     sensorStopped;
}MmwDemo_Stats;

/**
 * @brief Task handles storage structure
 */
typedef struct MmwDemo_TaskHandles_t
{
    /*! @brief   MMWAVE Control Task Handle */
    Task_Handle mmwaveCtrl;

    /*! @brief   ObjectDetection DPC related dpmTask */
    Task_Handle objDetDpmTask;

    /*! @brief   Demo init task */
    Task_Handle initTask;
} MmwDemo_taskHandles;

/**
 * @brief
 *  Millimeter Wave Demo Sensor State
 *
 * @details
 *  The enumeration is used to define the sensor states used in mmwDemo
 */
typedef enum MmwDemo_SensorState_e
{
    /*!  @brief Inital state after sensor is initialized.
     */
    MmwDemo_SensorState_INIT = 0,

    /*!  @brief Inital state after sensor is post RF init.
     */
    MmwDemo_SensorState_OPENED,

    /*!  @brief Indicates sensor is started */
    MmwDemo_SensorState_STARTED,

    /*!  @brief  State after sensor has completely stopped */
    MmwDemo_SensorState_STOPPED
}MmwDemo_SensorState;

/**
 * @brief Sub-frame config
 */
typedef struct MmwDemo_SubFrameCfg_t
{
    /*! @brief ADC buffer configuration storage */
    MmwDemo_ADCBufCfg adcBufCfg;

    /*! @brief Flag indicating if @ref adcBufCfg is pending processing. */
    uint8_t isAdcBufCfgPending : 1;

    /*! @brief  LVDS stream configuration */
    MmwDemo_LvdsStreamCfg lvdsStreamCfg;

    /*! @brief Flag indicating if @ref lvdsStreamCfg is pending processing. */
    uint8_t isLvdsStreamCfgPending : 1;

    /*! @brief GUI Monitor selection configuration storage from CLI */
    MmwDemo_GuiMonSel guiMonSel;

    /*! @brief Dynamic configuration storage for object detection DPC */
    MmwDemo_DPC_ObjDet_DynCfg objDetDynCfg;

    /*! @brief  Number of range FFT bins, this is at a minimum the next power of 2 of
                numAdcSamples. If range zoom is supported, this can be bigger than
                the minimum. */
    uint16_t    numRangeBins;

    /*! @brief  Number of Doppler FFT bins, this is at a minimum the next power of 2 of
                numDopplerChirps. If Doppler zoom is supported, this can be bigger
                than the minimum. */
    uint16_t    numDopplerBins;

    /*! @brief  ADCBUF will generate chirp interrupt event every this many chirps - chirpthreshold.
     *          This storage is needed for ADCBuf reconfiguration for sub-frame switching */
    uint8_t     numChirpsPerChirpEvent;

    /*! @brief  Number of bytes per RX channel, it is aligned to 16 bytes as
     *          required by ADCBuf driver. This storage is needed for ADCBuf
     *          reconfiguration for sub-frame switching  */
    uint32_t    adcBufChanDataSize;

    /*! @brief CQ signal & image band monitor buffer size */
    uint32_t    sigImgMonTotalSize;

    /*! @brief CQ RX Saturation monitor buffer size */
    uint32_t    satMonTotalSize;

    /*! @brief  Number of ADC samples */
    uint16_t    numAdcSamples;

    /*! @brief  Number of chirps per sub-frame */
    uint16_t    numChirpsPerSubFrame;
    
    /*! @brief  Number of virtual antennas */
    uint8_t     numVirtualAntennas; 
} MmwDemo_SubFrameCfg;

/*!
 * @brief
 * Structure holds stats information from data path.
 */
typedef struct MmwDemo_SubFrameStats_t
{
    /*! @brief   Frame processing stats */
    MmwDemo_output_message_stats    outputStats;

    /*! @brief Inter frame processing end time */
    uint32_t   interFrameProcessingEndTime;

    /*! @brief   Dynamic CLI configuration time in usec */
    uint32_t     pendingConfigProcTime;

    /*! @brief   SubFrame Preparation time in usec */
    uint32_t     subFramePreparationTime;

    /*! @brief DPC's sub-frame preparation time (for the next frame/sub-frame),
     *         this is only for debug purposes to be able to see all sub-frames
     *         switching time */
    uint32_t   objDetSubFramePreparationTime;
} MmwDemo_SubFrameStats;

/*!
 * @brief
 * Structure holds temperature information from Radar front end.
 *
 * @details
 *  The structure holds temperature stats information.
 */
typedef struct MmwDemo_temperatureStats_t
{

    /*! @brief   retVal from API rlRfTempData_t - can be used to know 
                 if values in temperatureReport are valid */
    int32_t        tempReportValid;

    /*! @brief   detailed temperature report - snapshot taken just 
                 before shipping data over UART */
    rlRfTempData_t temperatureReport;

} MmwDemo_temperatureStats;

/**
 * @brief
 *  Millimeter Wave Demo MCB
 *
 * @details
 *  The structure is used to hold all the relevant information for the
 *  Millimeter Wave demo
 */
typedef struct MmwDemo_MCB_t
{
    /*! @brief   Configuration which is used to execute the demo */
    MmwDemo_Cfg                 cfg;

    /*! * @brief   Handle to the SOC Module */
    SOC_Handle                  socHandle;

    /*! @brief   UART Logging Handle */
    UART_Handle                 loggingUartHandle;

    /*! @brief   UART Command Rx/Tx Handle */
    UART_Handle                 commandUartHandle;

    /*! @brief   This is the mmWave control handle which is used
     * to configure the BSS. */
    MMWave_Handle               ctrlHandle;

    /*! @brief   Data Path object */
    MmwDemo_DataPathObj         dataPathObj;

    /*! @brief   Demo Stats */
    MmwDemo_Stats               stats;

    /*! @brief   Semaphore handle to signal DPM started from DPM report function */
    Semaphore_Handle            DPMstartSemHandle;

    /*! @brief   Semaphore handle to signal DPM stopped from DPM report function. */
    Semaphore_Handle            DPMstopSemHandle;

    /*! @brief   Rf frequency scale factor, = 2.7 for 60GHz device, = 3.6 for 76GHz device */
    double                      rfFreqScaleFactor;

    /*! @brief    Task handle storage */
    MmwDemo_taskHandles taskHandles;

    /*! @brief    Sensor state */
    MmwDemo_SensorState sensorState;

    /*! @brief   Tracks the number of sensor start */
    uint32_t        sensorStartCount;

    /*! @brief   Tracks the number of sensor sop */
    uint32_t        sensorStopCount;

    /*! @brief sub-frame info */
    MmwDemo_SubFrameCfg subFrameCfg[RL_MAX_SUBFRAMES];

    /*! @brief sub-frame stats */
    MmwDemo_SubFrameStats subFrameStats[RL_MAX_SUBFRAMES];

    /*! @brief   CQ monitor configuration - Signal Image band data */
    rlSigImgMonConf_t           cqSigImgMonCfg[RL_MAX_PROFILES_CNT];

    /*! @brief   CQ monitor configuration - Saturation data */
    rlRxSatMonConf_t            cqSatMonCfg[RL_MAX_PROFILES_CNT];

    /*! @brief   Analog monitor bit mask */
    MmwDemo_AnaMonitorCfg       anaMonCfg;

    /*! @brief Flag indicating if @ref anaMonCfg is pending processing. */
    uint8_t isAnaMonCfgPending : 1;

    /*! @brief   this structure is used to hold all the relevant information
         for the mmw demo LVDS stream*/
    MmwDemo_LVDSStream_MCB_t    lvdsStream;

    /*! @brief   this structure is used to hold all the relevant information
         for the temperature report */
    MmwDemo_temperatureStats  temperatureStats;
} MmwDemo_MCB;

extern MmwDemo_MCB    gMmwMCB;

/* functions to handle the actions need to move the sensor state */
extern int32_t MmwDemo_openSensor(bool isFirstTimeOpen);
extern int32_t MmwDemo_configSensor(void);
extern int32_t MmwDemo_startSensor(void);
extern void MmwDemo_stopSensor(void);

/* functions to manage the dynamic configuration */
extern uint8_t MmwDemo_isAllCfgInPendingState(void);
extern uint8_t MmwDemo_isAllCfgInNonPendingState(void);
extern void MmwDemo_resetStaticCfgPendingState(void);
extern void MmwDemo_CfgUpdate(void *srcPtr, uint32_t offset, uint32_t size, int8_t subFrameNum);


/* Assert function*/
extern void _MmwDemo_debugAssert(int32_t expression, const char *file, int32_t line);

#define MmwDemo_debugAssert(expression) {                                      \
                                         _MmwDemo_debugAssert(expression,      \
                                                  __FILE__, __LINE__);         \
                                         DebugP_assert(expression);             \
                                        }
                                        
#ifdef __cplusplus
}
#endif

#endif /* MMW_DEMO_H */


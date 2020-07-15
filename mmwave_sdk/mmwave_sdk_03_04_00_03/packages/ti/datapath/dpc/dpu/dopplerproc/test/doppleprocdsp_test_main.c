/**
 *   @file  dopplerprocdsp_test_main.c
 *
 *   @brief
 *      Unit Test code for DSP doppler DPU.
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

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

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
#include <ti/sysbios/knl/Event.h>
#define DebugP_ASSERT_ENABLED 1
#include <ti/drivers/osal/DebugP.h>
#include <assert.h>
#include <ti/common/sys_common.h>
#include <ti/drivers/osal/SemaphoreP.h>
#include <ti/drivers/osal/MemoryP.h>
#include <ti/drivers/edma/edma.h>
#include <ti/drivers/esm/esm.h>
#include <ti/drivers/soc/soc.h>
#include <ti/utils/testlogger/logger.h>
#include <ti/utils/cycleprofiler/cycle_profiler.h> 
#include <ti/datapath/dpc/dpu/dopplerproc/dopplerprocdsp.h>
#include <ti/utils/mathutils/mathutils.h>
#include <ti/utils/randomdatagenerator/gen_rand_data.h>


/* EDMA resource partitioning */
#define EDMA_SHADOW_LNK_PARAM_BASE_ID       EDMA_NUM_DMA_CHANNELS

/* EDMA channels */
#define TEST_EDMA_DOPPLERPROC_IN_PING         EDMA_TPCC0_REQ_FREE_4
#define TEST_EDMA_DOPPLERPROC_IN_PONG         EDMA_TPCC0_REQ_FREE_5
#define TEST_EDMA_DOPPLERPROC_OUT             EDMA_TPCC0_REQ_FREE_6

/*EDMA shadow channels*/        
#define TEST_EDMA_DOPPLERPROC_IN_PING_SHADOW     (EDMA_SHADOW_LNK_PARAM_BASE_ID + 4U)
#define TEST_EDMA_DOPPLERPROC_IN_PONG_SHADOW     (EDMA_SHADOW_LNK_PARAM_BASE_ID + 5U)
#define TEST_EDMA_DOPPLERPROC_OUT_SHADOW         (EDMA_SHADOW_LNK_PARAM_BASE_ID + 6U)

#define TEST_MAX_NUM_DOPPLER_BINS 512
#define TEST_MAX_NUM_RANGE_BINS   1024

#if (defined (SOC_XWR18XX))
//1 Tx, 1, 2, 4 rx, the maximum size is 1024(range)*32(doppler)
//2 Tx, 2 rx, the maximum size is 1024(range)*32(doppler) , 4 rx, the maximum size is 1024(range)*16(doppler)
//3 tx, 4 rx, the maximum size is 1024(range)*16 (doppler)
#define TEST_MAX_RADAR_CUBE_SIZE  (48 * 1024 * 4)
#endif

#if (defined (SOC_XWR68XX))
#define TEST_MAX_RADAR_CUBE_SIZE  (42 * 1024 * 4)
#endif

#if (defined (SOC_XWR16XX))
#define TEST_MAX_RADAR_CUBE_SIZE  (42 * 1024 * 4)
#endif

/*cube */
#pragma DATA_SECTION(testRadarCube, ".l3ram");
#pragma DATA_ALIGN(testRadarCube, 8);
cmplx16ImRe_t testRadarCube[TEST_MAX_RADAR_CUBE_SIZE];       //msb is real, lsb 16 is imag

/*detection matrix size = numDopplerBins*numRangeBins */
#if (defined (SOC_XWR16XX))
#define TEST_MAX_DETMATRIX_SIZE    (32 * 1024)
#endif

#if (defined (SOC_XWR18XX))
#define TEST_MAX_DETMATRIX_SIZE    (64 * 1024)
#endif

#if (defined (SOC_XWR68XX))
#define TEST_MAX_DETMATRIX_SIZE    (32 * 1024)
#endif

//#pragma DATA_SECTION(calculatedDetMatrix, ".l2data");
#pragma DATA_SECTION(calculatedDetMatrix, ".l3ram");
#pragma DATA_ALIGN(calculatedDetMatrix, 8);
uint16_t calculatedDetMatrix[TEST_MAX_DETMATRIX_SIZE]; 

#pragma DATA_SECTION(testDopplerWindow, ".l2data");
#pragma DATA_ALIGN(testDopplerWindow, 8);
int32_t testDopplerWindow[TEST_MAX_NUM_DOPPLER_BINS];

#pragma DATA_SECTION(fftDataInBuf, ".l2data");
#pragma DATA_ALIGN(fftDataInBuf, 8);
uint32_t fftDataInBuf[TEST_MAX_NUM_DOPPLER_BINS];

#pragma DATA_SECTION(fftDataWindow, ".l2data");
#pragma DATA_ALIGN(fftDataWindow, 8);
int32_t fftDataWindow[TEST_MAX_NUM_DOPPLER_BINS * 2];

#pragma DATA_SECTION(fftDataOutBuf, ".l2data");
#pragma DATA_ALIGN(fftDataOutBuf, 8);
int32_t fftDataOutBuf[TEST_MAX_NUM_DOPPLER_BINS * 2];

/*Used for BPM decoding*/
#pragma DATA_SECTION(fftDataOutBuf1, ".l2data");
#pragma DATA_ALIGN(fftDataOutBuf1, 8);
int32_t fftDataOutBuf1[TEST_MAX_NUM_DOPPLER_BINS * 2];

#pragma DATA_SECTION(detMatRef, ".l2data");
#pragma DATA_ALIGN(detMatRef, 8);
uint16_t detMatRef[TEST_MAX_NUM_DOPPLER_BINS];  

#pragma DATA_SECTION(testDftSinCosTable, ".l2data");
#pragma DATA_ALIGN(testDftSinCosTable, 8);
cmplx16ImRe_t testDftSinCosTable[TEST_MAX_NUM_DOPPLER_BINS];

uint32_t testDftHalfBin;

#define PI 3.141592653589793

/*Log2() approximation is what is causing the major discrepancies 
  between reference data and DPU computation because the algorithm used by
  mmwavelib_log2Abs32() is very sensitive to small changes in the absValue
  which is the input to the log function: log2(absValue). Specially for small
  absValue values (small Doppler FFT output). For instance, in a case where 
  Reference absValue = 15 and DPU absValue = 9, the log2() approximation in Q8
  given by mmwavelib_log2Abs32() is around 180. 
  Also, the best approximation of the mmwavelib_log2Abs32() is to use a similar
  algorithm here instead of the C log2() function. The error is smaller and in general
  for typical values of absValue the error was observed to be almost always zero.
  Output of mmwavelib_log2Abs32() is in Q8, so a difference of 1 in the log computation
  between reference and DPU will be set as threshold. 
*/  
#define MAX_ERROR (1<<8) + (1<<7) //1.5 in Q8 format, 

/* Maximum error over all tests */
uint32_t gMaxError = 0;

/* Flag to check scratch buffer size*/
uint32_t gScratchNotEnough = 0;


/************************************************
  gTestCountStart:
  Set to zero to run all tests.
  Set to X to start from test number X.
*************************************************/  
uint32_t gTestCountStart = 0;

int gprint = 0;

void Test_compensateSingleValue(uint16_t dopplerIdx, uint16_t numDopplerBins, uint32_t *dftSinCosTable, uint32_t *dftHalfBin,int64_t * symbolPtr);
void Test_genTables(uint32_t numDopplerBins);

typedef struct dopplerProcDpuTestConfig {

    uint32_t numTxAntennas;
    uint32_t numRxAntennas;
    uint32_t numRangeBins;
    uint32_t numDopplerBins;
    uint32_t numChirps; //numChirps * numTxAnt = numChirps per frame
    uint32_t winType;   //0 - hanning window, 1 - rec window
    uint32_t isBPMEnabled;
}dopplerProcDpuTestConfig_t;

SOC_Handle  socHandle;
EDMA_Handle edmaHandle;

/* test configuration */
DPU_DopplerProcDSP_Config    dopplerProcDpuCfg;
DPU_DopplerProcDSP_Handle    dopplerProcDpuHandle;

DPU_DopplerProcDSP_OutParams outParams;
DPU_DopplerProc_StaticClutterRemovalCfg  clutter;

MCPI_LOGBUF_INIT(9216);

uint8_t finalResults;
uint8_t checkResults;


void MmwDemo_EDMA_errorCallbackFxn(EDMA_Handle handle, EDMA_errorInfo_t *errorInfo)
{
    DebugP_assert(0);
}

void MmwDemo_EDMA_transferControllerErrorCallbackFxn(EDMA_Handle handle,
    EDMA_transferControllerErrorInfo_t *errorInfo)
{
    checkResults = 0; 
    //while(1);
    DebugP_assert(0);
}

void dopplerProc_test_edmainit()
{
    uint8_t             edmaNumInstances;
    uint8_t             inst;
    EDMA_instanceInfo_t edmaInstanceInfo;
    EDMA_errorConfig_t  errorConfig;
    int32_t             errorCode;
    EDMA_errorInfo_t  EDMA_errorInfo;
    EDMA_transferControllerErrorInfo_t EDMA_transferControllerErrorInfo;

    /* Initialize the EDMA */
    edmaNumInstances = EDMA_getNumInstances();
    for (inst = 0; inst < edmaNumInstances; inst++)
    {
        errorCode = EDMA_init(inst);
        if (errorCode != EDMA_NO_ERROR)
        {
            System_printf("Debug: EDMA instance %d initialization returned error %d\n", errorCode);
            DebugP_assert(0);
            return;
        }
    }
    memset(&EDMA_errorInfo, 0, sizeof(EDMA_errorInfo));
    memset(&EDMA_transferControllerErrorInfo, 0, sizeof(EDMA_transferControllerErrorInfo));

    edmaHandle = EDMA_open(0, &errorCode, &edmaInstanceInfo);
    if (edmaHandle == NULL)
    {
        System_printf("Error: Unable to open the EDMA Instance err:%d\n", errorCode);
        DebugP_assert(0);
        return;
    }

    errorConfig.isConfigAllEventQueues = true;
    errorConfig.isConfigAllTransferControllers = true;
    errorConfig.isEventQueueThresholdingEnabled = true;
    errorConfig.eventQueueThreshold = EDMA_EVENT_QUEUE_THRESHOLD_MAX;
    errorConfig.isEnableAllTransferControllerErrors = true;
    errorConfig.callbackFxn = MmwDemo_EDMA_errorCallbackFxn;
    errorConfig.transferControllerCallbackFxn = MmwDemo_EDMA_transferControllerErrorCallbackFxn;
    if ((errorCode = EDMA_configErrorMonitoring(edmaHandle, &errorConfig)) != EDMA_NO_ERROR)
    {
        System_printf("Error: EDMA_configErrorMonitoring() failed with errorCode = %d\n", errorCode);
        DebugP_assert(0);
        return;
    }

}

void dopplerProc_test_dpuInit()
{
    int32_t errorCode;

    dopplerProcDpuHandle = DPU_DopplerProcDSP_init(&errorCode);
    if (dopplerProcDpuHandle == NULL)
    {
        System_printf("doppler DPU failed to initialize. Error %d.\n", errorCode);
        return;
    }
    System_printf("doppler DPU handle 0x%x.\n", (unsigned int)dopplerProcDpuHandle);  
}

void dopplerProc_test_dpuConfig()
{
    memset((void*)&dopplerProcDpuCfg, 0, sizeof(DPU_DopplerProcDSP_Config));

    dopplerProcDpuCfg.hwRes.edmaCfg.edmaHandle = edmaHandle;
    
    dopplerProcDpuCfg.dynCfg.staticClutterCfg.isEnabled = false;
            
    dopplerProcDpuCfg.hwRes.edmaCfg.edmaIn.ping.channel       = TEST_EDMA_DOPPLERPROC_IN_PING;
    dopplerProcDpuCfg.hwRes.edmaCfg.edmaIn.ping.channelShadow = TEST_EDMA_DOPPLERPROC_IN_PING_SHADOW;
    dopplerProcDpuCfg.hwRes.edmaCfg.edmaIn.ping.eventQueue    = 0;
    
    dopplerProcDpuCfg.hwRes.edmaCfg.edmaIn.pong.channel       = TEST_EDMA_DOPPLERPROC_IN_PONG;
    dopplerProcDpuCfg.hwRes.edmaCfg.edmaIn.pong.channelShadow = TEST_EDMA_DOPPLERPROC_IN_PONG_SHADOW;   
    dopplerProcDpuCfg.hwRes.edmaCfg.edmaIn.pong.eventQueue    = 0;
    
    dopplerProcDpuCfg.hwRes.edmaCfg.edmaOut.channel       = TEST_EDMA_DOPPLERPROC_OUT;
    dopplerProcDpuCfg.hwRes.edmaCfg.edmaOut.channelShadow = TEST_EDMA_DOPPLERPROC_OUT_SHADOW;
    dopplerProcDpuCfg.hwRes.edmaCfg.edmaOut.eventQueue    = 1;

    dopplerProcDpuCfg.hwRes.radarCube.datafmt = DPIF_RADARCUBE_FORMAT_1; //only format 1
    dopplerProcDpuCfg.hwRes.radarCube.data = (void *)testRadarCube;
    
    dopplerProcDpuCfg.hwRes.detMatrix.datafmt = DPIF_DETMATRIX_FORMAT_1;
    dopplerProcDpuCfg.hwRes.detMatrix.data = (void *)calculatedDetMatrix;       
}

/*Scratch buffer used for allocating some of the required DPU buffers*/
#define TEST_SCRATCHBUF_SIZE    0x4000U
#pragma DATA_SECTION(gScratchBuf, ".l1data"); 
//#pragma DATA_SECTION(gScratchBuf, ".l2data"); 
                     
#pragma DATA_ALIGN(gScratchBuf, 8);
uint8_t gScratchBuf[TEST_SCRATCHBUF_SIZE];

/*other buffers*/
#pragma DATA_SECTION(gtwiddle, ".l2data");
#pragma DATA_ALIGN(gtwiddle, 8);
cmplx32ReIm_t gtwiddle[TEST_MAX_NUM_DOPPLER_BINS]; 

#pragma DATA_SECTION(gsincos, ".l2data");
#pragma DATA_ALIGN(gsincos, 8);
cmplx16ImRe_t gsincos[TEST_MAX_NUM_DOPPLER_BINS]; 

/**
 *  @b Description
 *  @n
 *      Allocates the internal buffers from the scratch buffer provided
 *      by the application.
 *
 *  @param[in]  obj         DPU object.
 *  @param[in]  cfg         DPU configuration.
 *
 */
void dopplerProc_test_allocateBuffers
(
    DPU_DopplerProcDSP_StaticConfig * params,
    DPU_DopplerProcDSP_HW_Resources * hwResParams
)
{    
#define DOPPLER_DSP_ALIGN(x,a)  (((x)+((a)-1))&~((a)-1))
#define DOPPLER_DSP_MAX(x,y) ((x) > (y) ? (x) : (y))

/* below define is for debugging purposes, do not remove/change */
//#define NO_OVERLAY  /* do not overlay */

#ifdef NO_OVERLAY
#define DOPPLER_DSP_ALLOC_BUF(name, nameType, startAddr, alignment, size) \
        hwResParams->name = (nameType *) DOPPLER_DSP_ALIGN(prev_end, alignment); \
        prev_end = (uint32_t)hwResParams->name + (size) * sizeof(nameType);
#else
#define DOPPLER_DSP_ALLOC_BUF(name, nameType, startAddr, alignment, size) \
        hwResParams->name = (nameType *) DOPPLER_DSP_ALIGN(startAddr, alignment); \
        uint32_t name##_end = (uint32_t)hwResParams->name + (size) * sizeof(nameType);
#endif

   uint8_t  bpmFactor;
   uint32_t scratchStart = (uint32_t) &gScratchBuf[0];

    gScratchNotEnough = 0;
    
    /* When BPM is enabled, fftOutBuf needs to store data for all TX antennas
    so that BPM can be decoded after Doppler FFT.*/   
    if(params->isBpmEnabled)
    {
        bpmFactor = params->numTxAntennas;
    }
    else
    {
        /* No BPM*/
        bpmFactor = 1;
    }

    /* Allocation is as follows:
      pingPongBuf +  fftOutBuf + (windowingBuf | log2AbsBuf) + sumAbsBuf */
      
    /* Although scratch is not required to be initialized to 0, 
       it may help during debugging when viewing memory
       in CCS */
    memset((void *)scratchStart, 0, TEST_SCRATCHBUF_SIZE);    
      
#ifdef NO_OVERLAY
    uint32_t prev_end = scratchStart;
#endif

    DOPPLER_DSP_ALLOC_BUF(pingPongBuf, cmplx16ImRe_t,
        scratchStart, SYS_MEMORY_ALLOC_DOUBLE_WORD_ALIGN_DSP,
        2 * params->numDopplerChirps);
    
    DOPPLER_DSP_ALLOC_BUF(fftOutBuf, cmplx32ReIm_t,
        pingPongBuf_end, SYS_MEMORY_ALLOC_DOUBLE_WORD_ALIGN_DSP,
        bpmFactor * params->numDopplerBins); 

    DOPPLER_DSP_ALLOC_BUF(sumAbsBuf, uint16_t,
        fftOutBuf_end, SYS_MEMORY_ALLOC_DOUBLE_WORD_ALIGN_DSP,
        params->numDopplerBins);
        
    DOPPLER_DSP_ALLOC_BUF(windowingLog2AbsBuf, cmplx32ReIm_t,
        sumAbsBuf_end, SYS_MEMORY_ALLOC_DOUBLE_WORD_ALIGN_DSP,
        params->numDopplerBins);


    /* Check if scratch buffer was sufficient. Due to alignment requirements, allocation
       may have exceeded scratch size*/  
    System_printf("scratch: sizeUsed=%d total size=%d\n", (windowingLog2AbsBuf_end - scratchStart),TEST_SCRATCHBUF_SIZE);
    
    if((windowingLog2AbsBuf_end - scratchStart) > TEST_SCRATCHBUF_SIZE)
    {
        gScratchNotEnough = 1;
        System_printf("Error! (windowingLog2AbsBuf_end - scratchStart)=%d > scratch buffer size = %d\n",(windowingLog2AbsBuf_end - scratchStart),TEST_SCRATCHBUF_SIZE);
    }
    
    /*size of buffers*/
    hwResParams->pingPongSize=  2 * sizeof(cmplx16ImRe_t) * params->numDopplerChirps;
    hwResParams->windowingLog2AbsSize= sizeof(cmplx32ReIm_t) * params->numDopplerBins;
    hwResParams->fftOutSize= bpmFactor * params->numDopplerBins * sizeof(cmplx32ReIm_t);
    hwResParams->sumAbsSize= params->numDopplerBins * sizeof(uint16_t);

    /*Remaining buffers are allocated not from scratch*/
    hwResParams->dftSinCosTable = &gsincos[0];
    hwResParams->dftSinCosSize= params->numDopplerBins * sizeof(cmplx16ImRe_t);
    hwResParams->twiddle32x32 = &gtwiddle[0];
    hwResParams->twiddleSize = sizeof(cmplx32ReIm_t) * params->numDopplerBins;  
    hwResParams->windowCoeff = &testDopplerWindow[0];//use window generated by test code
    hwResParams->windowSize = sizeof(int32_t)*(params->numDopplerChirps / 2);

}

/* set up the doppler proc dpu configuration per test*/
void Test_setProfile(dopplerProcDpuTestConfig_t * testConfig)
{
    DPU_DopplerProcDSP_StaticConfig * params;
    DPU_DopplerProcDSP_HW_Resources * hwResParams;

    uint32_t ii;

    params = &dopplerProcDpuCfg.staticCfg;
    hwResParams = &dopplerProcDpuCfg.hwRes;
    
    params->isBpmEnabled = testConfig->isBPMEnabled; 
    params->numTxAntennas = testConfig->numTxAntennas;
    params->numRxAntennas = testConfig->numRxAntennas;
    params->numVirtualAntennas = testConfig->numTxAntennas * testConfig->numRxAntennas;
    params->numRangeBins = testConfig->numRangeBins;
    params->numDopplerChirps = testConfig->numChirps;
    params->numDopplerBins = testConfig->numDopplerBins;
    ii = 1;
    while ((1 << ii) < testConfig->numDopplerBins)
    {
        ii++;
    }
    params->log2NumDopplerBins = ii;

    /* cube */
    hwResParams->radarCube.dataSize = testConfig->numTxAntennas * testConfig->numRangeBins * testConfig->numChirps * testConfig->numRxAntennas * 4;
   /* output*/
    hwResParams->detMatrix.dataSize = testConfig->numRangeBins * testConfig->numDopplerBins * sizeof(int16_t);     //output is uint16

    /*Now fill in buffers*/    
    dopplerProc_test_allocateBuffers(params, hwResParams);
}

 /*
 * generates the cube data in format 1. for each range bin, it generates the exp signal with one peak. the peak 
   is at mod ((2*rangeBinIdx), numberofchirps);

 */
void Test_cubedata_gen(dopplerProcDpuTestConfig_t * testConfig)
{
    uint16_t ii, jj, kk;
    uint16_t numChirpsFrame;
    uint32_t radarCubeIdx;
    float amplitude; //signal amplitude
    float noiseScale; //noiseScale^2 is noisevaraince
    float dopplerIncr, dopplerAngle;
    float real, imag, noiseRe, noiseIm;
    uint32_t doppleBin;
    uint32_t txAntIdx;
    float var = 1;
    int32_t tempvalue;
    
    if (testConfig->numDopplerBins == 512)
    {
        amplitude = 25.f; // peak amplitude
        noiseScale = 620.f; // noise scale
    }
    else if (testConfig->numDopplerBins == 256)
    {
        amplitude = 25.f;
        noiseScale = 650.f;
    }
    else if (testConfig->numDopplerBins == 128)
    {
        amplitude = 50.f;
        noiseScale = 650.f;
    }
    else
    {
        amplitude = 60.f;
        noiseScale = 800.f;
    }
    
    numChirpsFrame = testConfig->numTxAntennas * testConfig->numChirps;

    /* generate radar cube 1D fft output*/
    for (ii = 0; ii < numChirpsFrame; ii++) //chirp loop
    {
        for (jj = 0; jj < testConfig->numRxAntennas; jj++) //rx antenna loop
        {
            for (kk = 0; kk < testConfig->numRangeBins; kk++)
            {
               
                if (testConfig->numChirps < 8)
                    /* peak is at mod (kk, numChirps) */
                    doppleBin = kk - kk/ testConfig->numChirps * testConfig->numChirps;
                else
                    /* peak is at mod (2*kk, numChirps) */
                    doppleBin = (2 * kk) - (2 * kk) / testConfig->numChirps * testConfig->numChirps;
                    
                dopplerIncr = 2.f * PI *  (float)doppleBin / (float)numChirpsFrame;
                dopplerAngle = ii * dopplerIncr;  //increase every chirp
                
                if (testConfig->numTxAntennas == 1)
                {
                    radarCubeIdx = ii * testConfig->numRxAntennas * testConfig->numRangeBins;
                    
                }
                else
                {
                    txAntIdx = ii - ii / testConfig->numTxAntennas * testConfig->numTxAntennas; //mod(ii, numTx)
                    radarCubeIdx = txAntIdx * testConfig->numChirps * testConfig->numRxAntennas * testConfig->numRangeBins;
                    radarCubeIdx += (ii / testConfig->numTxAntennas) * testConfig->numRxAntennas * testConfig->numRangeBins;
                }

                radarCubeIdx += jj * testConfig->numRangeBins;
                radarCubeIdx += kk;

                GaussianNoise(var, &noiseRe, &noiseIm);   
                real = amplitude * cosf(dopplerAngle) + noiseScale * noiseRe;
                imag = amplitude * sinf(dopplerAngle) + noiseScale * noiseIm;
                
                /*If BPM is enabled, need to add contribution from both TX antennas.*/
                if((testConfig->isBPMEnabled) && (testConfig->numTxAntennas == 2))
                {                
                    GaussianNoise(var, &noiseRe, &noiseIm);
                    /*even chirps combines TX(+ +), odd chirps combines TX(+ -) */
                    if(ii % 2 == 0)
                    {
                        real += amplitude * cosf(dopplerAngle) + noiseScale * noiseRe;
                        imag += amplitude * sinf(dopplerAngle) + noiseScale * noiseIm;
                    }
                    else
                    {
                        real -= amplitude * cosf(dopplerAngle) + noiseScale * noiseRe;
                        imag -= amplitude * sinf(dopplerAngle) + noiseScale * noiseIm;
                    }
                }
                
                tempvalue = (int32_t)MATHUTILS_ROUND_FLOAT(real);
                MATHUTILS_SATURATE16(tempvalue);
                testRadarCube[radarCubeIdx].real = (int16_t)tempvalue;
                tempvalue = (int32_t)MATHUTILS_ROUND_FLOAT(imag);
                MATHUTILS_SATURATE16(tempvalue);
                testRadarCube[radarCubeIdx].imag = (int16_t)tempvalue;

            }
        }/* end of rx antenna loop*/
    }//end of chirp loop
}

/* generates the rectangle and hanning window coefficients */
#define TEST_WINDOW_COEF_QFORMAT 19
void Test_window2DCoef_gen(uint32_t numSamples, uint8_t winType)
{
    float ephyR, ephyI;
    float phi = 2 * PI_ / ((float)numSamples - 1);
    uint32_t ii;
    float a0;
    float winValue;
    int32_t winValueFixed;
    float cosValue, sinValue ;
    float temp;
    
    
    cosValue = 1.f;
    sinValue = 0.f;    
    ephyR = cos(phi);         
    ephyI = sin(phi);   
    a0 = 0.5f;
    
//mmwavelib: w(n)=0.5*(1-cos(2*pi*n/(N-1))

    if (winType == 1)
    {
        for (ii = 0; ii < numSamples; ii++)
        {
            testDopplerWindow[ii] = (1 << TEST_WINDOW_COEF_QFORMAT) - 1; //rec window, for debug
        }
    }
    else
    {
        /* hanning window */
        for (ii = 0; ii < numSamples; ii++)
        {
            winValue = a0 * (1.f - cosValue);       //0.5*(1-cos(2*pi*n/N-1))

            winValue = winValue * (1 << TEST_WINDOW_COEF_QFORMAT) + 0.5;     
            winValueFixed = (uint32_t)winValue;
            if (winValueFixed >= (1 << TEST_WINDOW_COEF_QFORMAT))
            {
                winValueFixed = (1 << TEST_WINDOW_COEF_QFORMAT) - 1;
            }
            temp = cosValue;
            cosValue = cosValue * ephyR - sinValue * ephyI;
            sinValue = temp * ephyI + sinValue * ephyR;

            //testDopplerWindow[ii] = (1<<TEST_WINDOW_COEF_QFORMAT) - 1; //rec window, for debug
            testDopplerWindow[ii] = winValueFixed;
        }
    }

}

/*  calculates fft, input is 32 bits I/Q, output is also 32x32 bits I/Q*/
void Test_2Dfft_ref(int32_t * dataOut, int32_t * dataIn, uint32_t fftSize, uint32_t numChirps)
{
    uint32_t ii, jj;
    float cosValue, sinValue;
    float cosStep, sinStep;
    float alpha;
    float realValueTemp, imagValueTemp;
    float realValue, imagValue;
    float inReal, inImag;
    int32_t outReal, outImag;
    float tempValue;

    for (ii = 0; ii < fftSize; ii++)
    {
        alpha = -2.f * ii * PI_ / (float)fftSize;
        cosValue = 1.f;
        sinValue = 0.f;
        cosStep = cos(alpha);
        sinStep = sin(alpha);
        realValue = (float)dataIn[1];
        imagValue = (float)dataIn[0];
        for (jj = 1; jj < numChirps; jj++)//it is enough to sum only #chirps because it is padded with zeros from #chirps to #bins
        {
            tempValue = cosValue;
            cosValue = cosValue * cosStep - sinValue * sinStep;
            sinValue = sinValue * cosStep + tempValue *sinStep;

            inReal = (float)dataIn[2 * jj + 1];
            inImag = (float)dataIn[2 * jj];

            realValueTemp = inReal * cosValue - inImag * sinValue;
            realValue += realValueTemp;
            imagValueTemp = inReal * sinValue + inImag * cosValue;
            imagValue += imagValueTemp;
        }
        
        outReal = (int32_t)MATHUTILS_ROUND_FLOAT(realValue);        
        outImag = (int32_t)MATHUTILS_ROUND_FLOAT(imagValue);

        dataOut[2 * ii] = outReal;
        dataOut[2 * ii + 1] = outImag ;
    }
}

/*computes log2(absValue) and accumulates for each computed FFT*/
void Test_2Dfft_log2Accum(int32_t *fftDataOut, uint32_t fftSize, uint8_t numVirtAnt)
{
    uint32_t ii;
    int32_t fftoutR, fftoutI;
    double absValue, log2Value;
    uint16_t log2Temp;
    int32_t max,min;
    int8_t log2NumVirtAnt;
    
    if(numVirtAnt == 1)
    {
        log2NumVirtAnt = 0;
    }
    else if(numVirtAnt == 2)
    {
        log2NumVirtAnt = 1;
    }    
    else if(numVirtAnt == 4)
    {
        log2NumVirtAnt = 2;
    }    
    else if(numVirtAnt == 8)
    {
        log2NumVirtAnt = 3;
    }    
    else if(numVirtAnt == 12)
    {
        log2NumVirtAnt = 4;
    }    
    else 
    {
        DebugP_assert(0);
    }    
    
    /* abs, log2 sum*/
    for (ii = 0; ii < fftSize; ii++)
    {
      
        fftoutR = fftDataOut[2 * ii] ;
        fftoutI = fftDataOut[2 * ii + 1] ;

        //absValue = sqrt(((double)fftoutR * fftoutR + (double) fftoutI * fftoutI));
        
        /*In mmwavelib_log2Abs32() used by DPU:
            abs(a+j*b) is approximated using (max(|a|,|b|) + min(|a|,|b|)*3/8)*/

        if(fftoutR < 0) fftoutR = -fftoutR;
        if(fftoutI < 0) fftoutI = -fftoutI;
        
        if(fftoutR > fftoutI)
        {
            max = fftoutR;
            min = fftoutI;
        }
        else
        {
            max = fftoutI;
            min = fftoutR;
        }
        
        absValue = (double)max + (double)min*3/8; 
                
        #if 1
        if (absValue == 0)
            log2Value = 0;      
        else
            log2Value = log2(absValue);
            
        log2Value = log2Value  * 256.f;  //in Q 8 format 
        #else        
        //mimic mmwavelib log computation to decrease error
        uint8_t c_Log2LookUp[64] = {
                                    0, 6, 11, 17, 22, 28, 33, 38,
                                    44, 49, 54, 59, 63, 68, 73, 78,
                                    82, 87, 92, 96, 100, 105, 109, 113,
                                    118, 122, 126, 130, 134, 138, 142, 146,
                                    150, 154, 157, 161, 165, 169, 172, 176,
                                    179, 183, 186, 190, 193, 197, 200, 203,
                                    207, 210, 213, 216, 220, 223, 226, 229,
                                    232, 235, 238, 241, 244, 247, 250, 253
                                    };
        uint32_t log2Int, log2Fract;
        log2Int = 31U - _lmbd(1, absValue);
        if (absValue == 0)
        {
            log2Int = 0;
        }

        /* create a 6 bit fractional part */
        log2Fract = _extu(absValue, 32U - log2Int, 26U);

        /* compute the log2 by combining the integer and the fractional
         * part. */

        log2Value = (log2Int << 8U) + c_Log2LookUp[log2Fract];
        #endif
        
        
        if(log2Value >= (1 << 16))
        {
            /* detection matrix is uint16*/
            DebugP_assert(0);
        }

        #if 0
        if (log2Value >= 0)
            log2Temp = (uint16_t)(log2Value + 0.5);
        else
            log2Temp = (uint16_t)(log2Value - 0.5);
        #else
        log2Temp = (uint16_t)log2Value;
        #endif

        detMatRef[ii] += (log2Temp >> log2NumVirtAnt);
        if(detMatRef[ii] >= (1 << 16))
        {
            /* detection matrix is uint16*/
            DebugP_assert(0);
        }
    }
}

void Test_decode2TXBPM(int32_t *fftDataOutTx0, int32_t *fftDataOutTx1, uint32_t fftSize)
{
    cmplx32ReIm_t *bpmAPtr;
    cmplx32ReIm_t *bpmBPtr;
    int32_t       real, imag;
    uint16_t      idx;

    bpmAPtr  = (cmplx32ReIm_t *)fftDataOutTx0;
    bpmBPtr  = (cmplx32ReIm_t *)fftDataOutTx1;
    for(idx = 0; idx < fftSize; idx++)
    {
        /*doppler compensation on Pong*/
        Test_compensateSingleValue(idx,fftSize,
                                                 (uint32_t *) testDftSinCosTable,
                                                 &testDftHalfBin,
                                                 (int64_t *) &bpmBPtr[idx]);
        /*decode BPM*/
        /*first make a copy of A*/
        real = bpmAPtr[idx].real;
        imag = bpmAPtr[idx].imag;
        /*compute S1 and store in A*/
        bpmAPtr[idx].real = (bpmAPtr[idx].real + bpmBPtr[idx].real)/2;
        bpmAPtr[idx].imag = (bpmAPtr[idx].imag + bpmBPtr[idx].imag)/2;
        /*compute S2 and store in B*/
        bpmBPtr[idx].real = (real - bpmBPtr[idx].real)/2;
        bpmBPtr[idx].imag = (imag - bpmBPtr[idx].imag)/2;
    }
}

/* 
    Generates the reference for Doppler proc DPU. 
    it implements windowing 16bits I/Q input,  32 bits I/Q output
    fft calculation,
    abs calculation, 
    log2 calcuations is Q8 for DSP
*/
void Test_generateReference(dopplerProcDpuTestConfig_t * testConfig)
{
    uint32_t ii;
    int32_t winCoef;
    int64_t tempValue;    
    uint32_t dataSample;
    int64_t realValue, imagValue;
    uint32_t numSamples = testConfig->numChirps; 
    uint32_t fftSize = testConfig->numDopplerBins;
    static uint32_t txIndex = 0;//used for BPM only
    uint8_t numVirtAnt = testConfig->numTxAntennas * testConfig->numRxAntennas;
    
    /* windowing, input is 16x16 complex,  output is 32 bits    */
    
    //memset input buffer as it should be padded with zeros from numdopchirps to numdopbins if numdopbins > numdopchirps
    memset((void*)&fftDataWindow[0],0,sizeof(fftDataWindow));
    
    for (ii = 0; ii < numSamples; ii++)
    {
        winCoef = (int32_t)testDopplerWindow[ii];
        dataSample = fftDataInBuf[ii];
        imagValue = (int64_t)  ((int16_t)(dataSample & 0x0000FFFF));      //lsb is imag
        tempValue = imagValue * winCoef;
        
        /*Round by +- 0.5 in Q15 then convert to Q0*/
        if(tempValue > 0)
            tempValue = (tempValue + (1<<14)) >> 15;
        else
            tempValue = (tempValue - (1<<14)) >> 15;
        
        fftDataWindow[ii * 2] = (int32_t) tempValue;       //imag is even
        realValue = (int64_t) ((int16_t)(dataSample >> 16)) ;
        tempValue = realValue * winCoef;

        if(tempValue > 0)
            tempValue = (tempValue + (1<<14)) >> 15;
        else
            tempValue = (tempValue - (1<<14)) >> 15;

        fftDataWindow[ii * 2 + 1] = (int32_t)tempValue;     //real is odd
        //printf("coef=%d  realValue=%lld realValue * winCoef=%lld output=%d\n",winCoef,realValue,realValue * winCoef,(int32_t) tempValue);
    }
    
    if(testConfig->isBPMEnabled)
    {
        /*need to decode BPM*/
        if(txIndex == 0)
        {
            /* fft */
            Test_2Dfft_ref(fftDataOutBuf, fftDataWindow, fftSize, numSamples );
            /* Does not have data for both TX antennas, so can not decode BPM now.
               FFT output is saved in fftDataOutBuf and wait for next FFT to decode BPM*/
        }
        else
        {
            /* fft */
            Test_2Dfft_ref(fftDataOutBuf1, fftDataWindow, fftSize, numSamples );
            
            /* We have data for both TX antennas, so can decode BPM now*/           
            //decode bpm            
            Test_decode2TXBPM(fftDataOutBuf, fftDataOutBuf1, fftSize);
            
            //log2Acc
            Test_2Dfft_log2Accum(fftDataOutBuf, fftSize, numVirtAnt);
            Test_2Dfft_log2Accum(fftDataOutBuf1, fftSize, numVirtAnt);
        }
        
        txIndex++;
        if(txIndex == 2)
           txIndex = 0;
              
    }
    else//not BPM:
    {
        /* fft */
        Test_2Dfft_ref(fftDataOutBuf, fftDataWindow, fftSize, numSamples );
        
        #if 0   
        int ca;
        if(gprint)
        {
            printf("FFT out\n");
            for(ca=0;ca<64;ca++)
                printf("%d\n",fftDataOutBuf[ca]);        
        }    
        #endif
        
        Test_2Dfft_log2Accum(fftDataOutBuf, fftSize, numVirtAnt);
    }
}

/* check the results from dpu with the reference */
void Test_printResults(dopplerProcDpuTestConfig_t * testConfig)
{
    uint32_t ii;
    uint32_t jj, kk, mm;
    uint32_t radarCubeIdx;
    uint32_t numZeros;
    uint8_t testFlag;
    uint32_t max_ref, max_computed;
    int32_t maxError, error;
    float percentage, ratio;
    uint32_t *cubePtr = (uint32_t *)testRadarCube;     //msb is real, lsb is imag

    testFlag = 1;    
    maxError = -1;
    for (ii = 0; ii < testConfig->numRangeBins; ii++) //range bin
    { 
        /* for accumulation over all tx antenna and rx antenna*/
        memset((void *)detMatRef, 0, sizeof(detMatRef));
        numZeros = 0;
        /*need to be done in this order: outer loop RX, inner loop TX
          so that BPM can be decoded (both TX processing are done in sequence)*/
        for (kk = 0; kk < testConfig->numRxAntennas; kk++)
        {
            for (jj = 0; jj < testConfig->numTxAntennas; jj++)
            {            
                for (mm = 0; mm < testConfig->numChirps; mm++)
                {
                    radarCubeIdx = jj * testConfig->numChirps * testConfig->numRxAntennas *  testConfig->numRangeBins;
                    radarCubeIdx += (mm * testConfig->numRxAntennas * testConfig->numRangeBins);
                    radarCubeIdx += (kk * testConfig->numRangeBins);
                    radarCubeIdx += ii;

                    fftDataInBuf[mm] = cubePtr[radarCubeIdx];
                    //System_printf("%d,%d\n", testRadarCube[radarCubeIdx].real, testRadarCube[radarCubeIdx].imag);
                    
                }  /* end of doppler bin loop*/

                /* call reference generation */
                Test_generateReference(testConfig);
            } //end of rx antenna
        }//end of tx antenna

        /* verify the test results*/
        for (mm = 0; mm < testConfig->numDopplerBins; mm++)
        {
            /* dpu output is doppler, then range bin */
            error = abs((detMatRef[mm] - calculatedDetMatrix[ii * testConfig->numDopplerBins + mm]));
            
            if (error > MAX_ERROR)
            {
                System_printf("Rangebin = %d, DopplerBin = %d, DopplerSize = %d, Ref=%d, dpu=%d err= %d fail\n", 
                               ii, mm, testConfig->numDopplerBins, detMatRef[mm], calculatedDetMatrix[ii * testConfig->numDopplerBins + mm], error);
                finalResults = 0;
                testFlag = 0;
            }
            else
            {
                if(error > maxError)
                {
                    maxError = error;
                    max_computed = calculatedDetMatrix[ii * testConfig->numDopplerBins + mm];
                    max_ref = detMatRef[mm];
                    
                    if(maxError > gMaxError)
                    {
                        gMaxError = maxError;
                    }
                }
            }

            if (calculatedDetMatrix[ii * testConfig->numDopplerBins + mm] < 2)
                numZeros++;
            
       }

        if (numZeros > testConfig->numDopplerBins - 5)
        {
            System_printf("Rangebin = %d, DopplerSize = %d, all zero output, fail\n", ii, testConfig->numDopplerBins);
            finalResults = 0;
            testFlag = 0;
        }
    }//end of rangebin
    
    if (testFlag == 1)
    {
        percentage = (float)100*maxError/max_ref;
        ratio = (float)max_computed/max_ref;
        //System_printf() can not print float value
        printf("Test Pass maxError = %d RefVal = %d DpuVal = %d percentage = %.1f ratio = %.5f\n",
                      maxError, max_ref, max_computed, percentage, ratio);
    }
    else
    {
        System_printf("Test Fail\n");
    }
    System_printf("\n");
}

#define TEST_DOPP_BIN_ARRAY_SIZE 6
#define TEST_RANGE_BIN_ARRAY_SIZE 7
#define TEST_DOPP_CHIRP_ARRAY_SIZE 3
/*
    test main task
*/
void Test_task(UArg arg0, UArg arg1)
{
    uint32_t ii,jj,dopChirps;
    uint32_t numRangeBin[TEST_RANGE_BIN_ARRAY_SIZE] = {16, 32, 64, 128, 256, 512, 1024};
    uint32_t numDopplerBin[TEST_DOPP_BIN_ARRAY_SIZE] = {16, 32, 64, 128, 256, 512};
    uint32_t numDopplerChirpsToSubtractFromDopBin[TEST_DOPP_CHIRP_ARRAY_SIZE] = {0, 4, 12};//sets numdopplerChirps = numdopplerBins - {value}
    uint32_t numRxAnt[3] = {1, 2, 4};
    uint32_t numTxAnt[3] = {1, 2, 3};
    uint32_t txAntIdx, rxAntIdx;
    dopplerProcDpuTestConfig_t testConfig;
    char featureName[200];
    uint32_t startTime, bench2;
    int32_t   retVal;
    DPU_DopplerProcDSP_OutParams out;
    uint32_t testCount,bpmIdx,bpmTest;
    //uint32_t preNumChirps;
    uint32_t cubeSize, detSize;
    
    System_printf("...... Initialization ...... \n");

    finalResults = 1;
    
    /*edma, dpu inialization */
    dopplerProc_test_edmainit();
    dopplerProc_test_dpuInit();

    /* doppler dpu config*/
    dopplerProc_test_dpuConfig();

    testCount = 0;
    
    /* Test runs all combinations of [NumRxAnt,NumTxAnt,NumRangeBins,NumDopplerBins] such that it
       fits the detection matrix and radar cube sizes.
       It will test 3 cases for NumDopplerChirps:
       1. NumDopplerChirps = NumDopplerBins        
       2. NumDopplerChirps = NumDopplerBins - 4
       3. NumDopplerChirps = NumDopplerBins - 12
    */    
    for (txAntIdx = 0; txAntIdx < 3; txAntIdx++)        
    {
        for (rxAntIdx = txAntIdx; rxAntIdx < 3; rxAntIdx++) 
        {
            testConfig.numTxAntennas = numTxAnt[txAntIdx];
            testConfig.numRxAntennas = numRxAnt[rxAntIdx];

            for (ii = 0; ii < TEST_DOPP_BIN_ARRAY_SIZE; ii++) /* doppler bin loop, 16, 32, 64, 128, 256, 512 */
            {
                testConfig.numDopplerBins = numDopplerBin[ii];
                if(testConfig.numDopplerBins > TEST_MAX_NUM_DOPPLER_BINS)
                {
                    System_printf("testConfig.numDopplerBins (%d) > TEST_MAX_NUM_DOPPLER_BINS.\n", testConfig.numDopplerBins);
                    DebugP_assert(0);
                }    

                for (jj = 0; jj < TEST_RANGE_BIN_ARRAY_SIZE; jj++)
                {
                    testConfig.numRangeBins = numRangeBin[jj];
                    if(testConfig.numRangeBins > TEST_MAX_NUM_RANGE_BINS)
                    {
                        System_printf("testConfig.numRangeBins (%d) > TEST_MAX_NUM_RANGE_BINS.\n", testConfig.numRangeBins);
                        DebugP_assert(0);
                    }    
                    
                    checkResults = 1;
                
                    if ( (testCount & 0x7 )== 0) /* mod (8) ==0, set to rec window*/
                        testConfig.winType = 1;
                    else
                        testConfig.winType = 0; //hanning window
                
                    /*maximum cube size is when numdopChirps = numdopBins*/
                    cubeSize = testConfig.numRangeBins*testConfig.numDopplerBins*testConfig.numRxAntennas*testConfig.numTxAntennas;
                    detSize = testConfig.numRangeBins*testConfig.numDopplerBins;
                    
                    if((cubeSize <= TEST_MAX_RADAR_CUBE_SIZE) && (detSize <= TEST_MAX_DETMATRIX_SIZE))
                    {
                        for(dopChirps = 0; dopChirps < TEST_DOPP_CHIRP_ARRAY_SIZE; dopChirps++)
                        {
                            testConfig.numChirps = numDopplerBin[ii] - numDopplerChirpsToSubtractFromDopBin[dopChirps];
                            
                            if(testConfig.numTxAntennas == 2)
                                bpmTest = 1;//Run BPM only when num TX antennas = 2
                            else
                                bpmTest = 0;
                                
                            for(bpmIdx = 0; bpmIdx <= bpmTest; bpmIdx++)
                            {
                                testConfig.isBPMEnabled = bpmIdx;

                                /* generate the windowing factors*/
                                Test_window2DCoef_gen(testConfig.numChirps, testConfig.winType);
                                
                                /* generate tables */
                                Test_genTables(testConfig.numDopplerBins);
                                
                                if(testCount >= gTestCountStart)
                                {
                                    System_printf("Test #%d  start\n", testCount);
                                    Test_setProfile(&testConfig);
                                        
                                    sprintf(featureName, "%s%d%s%d%s%d%s%d%s%d%s%d",
                                        " Tx", testConfig.numTxAntennas,
                                        " Rx", testConfig.numRxAntennas,
                                        " Chirp", testConfig.numChirps,
                                        " R", testConfig.numRangeBins,
                                        " D", testConfig.numDopplerBins,
                                        " BPM_", testConfig.isBPMEnabled);
                                    
                                    System_printf("Test feature:%s\n", featureName);
                                    
                                    if(gScratchNotEnough)
                                    {
                                        System_printf("SKIPPING THIS TEST\n\n");
                                        continue;
                                    }    
                                    
                                    /* generate cube*/
                                    Test_cubedata_gen(&testConfig);
                                    
                                    /* call the doppler dpu*/
                                    startTime = Cycleprofiler_getTimeStamp();
                                    retVal = DPU_DopplerProcDSP_config(dopplerProcDpuHandle, &dopplerProcDpuCfg);
                                    if (retVal < 0)
                                    {
                                        System_printf("doppler DPU failed to configure. Error %d.\n", retVal);
                                        DebugP_assert(0);
                                        return;
                                    }
                                    //bench1 = Cycleprofiler_getTimeStamp() - startTime;
                                    
                                    //System_printf("Doppler DPU configured. Cycles = %d\n", bench1);
                                    
                                    startTime = Cycleprofiler_getTimeStamp();
                                    retVal = DPU_DopplerProcDSP_process(dopplerProcDpuHandle, &out);
                                    if (retVal < 0)
                                    {
                                        System_printf("doppler DPU failed to run. Error %d.\n", retVal);
                                        DebugP_assert(0);
                                        return;
                                    }
                                    bench2 = Cycleprofiler_getTimeStamp() - startTime;
                                    System_printf("Doppler DPU Process. Cycles = %d. \n", bench2);
                                    
                                    if (checkResults)
                                    {
                                        Test_printResults(&testConfig);
                                    }
                                    else
                                    {
                                        System_printf("Test #%d crashed.\r", testCount);
                                    }
                                }//if(testCount >= gTestCountStart)   
                                
                                testCount++;
                            }//for(bpmIdx...    
                        }//for(dopChirps...    
                    }    
                }
            }
        }
    }

    EDMA_close(edmaHandle);

    retVal = DPU_DopplerProcDSP_deinit(dopplerProcDpuHandle);
    if (retVal < 0)
    {
        System_printf("doppler DPU failed to deinit. Error %d.\n", retVal);
        DebugP_assert(0);
        return;
    }
    
    System_printf("----------------------------\n");
    System_printf("Run %d tests. Maximum error is %d\n",testCount, gMaxError);
    
    if (finalResults == 1)
    {
        System_printf("All Tests PASSED!\n");
        MCPI_setFeatureTestResult("doppler_DPU", MCPI_TestResult_PASS);
    }
    else
    {
        System_printf("Test FAILED!\n");
        MCPI_setFeatureTestResult("doppler_DPU", MCPI_TestResult_FAIL);
    }

    System_printf("Test Finished\n");
    MCPI_setTestResult();

    /* Exit BIOS */
    BIOS_exit(0);
}


int main (void)
{
    Task_Params taskParams;
    int32_t     errCode;
    SOC_Cfg     socCfg;

    /* Initialize test logger */
    MCPI_Initialize();

    Cycleprofiler_init();

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
        DebugP_assert(0);
        return -1;
    }

    /* Initialize the Task Parameters. */
    Task_Params_init(&taskParams);
    taskParams.stackSize = 8*1024;
    Task_create(Test_task, &taskParams, NULL);

    /* Start BIOS */
    BIOS_start();
    
    return 0;
}

//BPM util functions below
// * @param[in]            xIQ : 16-bit complex value(16I|16Q packed in 32bits).
// * @param[in]            wQI : 32-bit complex value(32Q|32I packed in 64bits).
// * @param[out]           yQI : pointer to store output 32-bit complex value(32Q|32I).
void Test_mult16x32cplx(uint32_t xIQ, int64_t wQI, int64_t *yQI)
{
    int16_t im, re;
    int32_t im1, re1;
    int32_t *out = (int32_t*)yQI;
    int32_t a,b;
    int64_t temp;
    
    re = (int16_t)((xIQ & 0xFFFF0000) >> 16);
    im = (int16_t)(xIQ & 0xFFFF);

    im1 = (int32_t)((wQI & 0xFFFFFFFF00000000) >> 32);
    re1 = (int32_t)(wQI & 0xFFFFFFFF);
    
    /*Computed as instruction MPY2IR:
    Performs two 16-bit by 32-bit multiplies. The upper and lower halves of src1 are treated
as 16-bit signed inputs. The value in src2 is treated as a 32-bit signed value. The
products are then rounded to a 32-bit result by adding the value 2^14 and then these sums
are right shifted by 15.*/

    /* Imaginary part: YQ computation*/
    temp = (int64_t)re * (int64_t)im1 + 0x4000;
    temp = temp >> 15;
    a = (int32_t)(temp&0xFFFFFFFF);

    temp = (int64_t)im * (int64_t)re1 + 0x4000;
    temp = temp >> 15;
    b = (int32_t)(temp&0xFFFFFFFF);

    out[1] = a + b;
    
    /* Real part: YI computation*/
    temp = (int64_t)re * (int64_t)re1 + 0x4000;
    temp = temp >> 15;
    a = (int32_t)(temp&0xFFFFFFFF);

    temp = (int64_t)im * (int64_t)im1 + 0x4000;
    temp = temp >> 15;
    b = (int32_t)(temp&0xFFFFFFFF);

    out[0] = a - b;
}

void Test_compensationGetCoeff
(
    uint16_t dopplerIdx,
    uint16_t numDopplerBins,
    uint32_t *dftSinCosTable,
    uint32_t *dftHalfBin,
    uint32_t *coeff)
{
    uint32_t expDoppComp;
    int32_t  dopplerCompensationIdx = dopplerIdx;

    /*Divide Doppler index by 2*/
    if (dopplerCompensationIdx >= numDopplerBins/2)
    {
        dopplerCompensationIdx -=  numDopplerBins;
    }
    dopplerCompensationIdx = dopplerCompensationIdx >> 1;
    if (dopplerCompensationIdx < 0)
    {
        dopplerCompensationIdx +=  numDopplerBins;
    }
    expDoppComp = dftSinCosTable[dopplerCompensationIdx];
    /* Add half bin rotation if Doppler index was odd */
    if (dopplerIdx & 0x1)
    {
        expDoppComp = _cmpyr1(expDoppComp, *dftHalfBin);
    }
	*coeff = expDoppComp;
}

void Test_compensateSingleValue(uint16_t dopplerIdx,
                                    uint16_t numDopplerBins,
                                    uint32_t *dftSinCosTable,
                                    uint32_t *dftHalfBin,
                                    int64_t * symbolPtr)
{
    uint32_t doppCompCoeff;

    Test_compensationGetCoeff(dopplerIdx,
                                        numDopplerBins,
                                        dftSinCosTable,
                                        dftHalfBin,
                                        &doppCompCoeff);

    Test_mult16x32cplx(doppCompCoeff, symbolPtr[0], symbolPtr );
}

/* int16 in Q15 format, imaginary in even, real in odd location */
#define ONE_Q15 (1<<15)
void gen_dftSinCosTable(uint32_t dftLength, int16_t *dftSinCosTable)
{
    uint32_t i;
    int32_t itemp;
    float temp;

    for (i = 0; i < dftLength; i++)
    {
        temp = ONE_Q15 * -sin(2*PI*i/dftLength);
        if (temp > 0)
        {
            temp = temp + 0.5;
        }
        else
        {
            temp = temp -0.5;
        }
        itemp = (int32_t) temp;

        if(itemp >= ONE_Q15)
        {
            itemp = ONE_Q15 - 1;
        }
        dftSinCosTable[2*i] =  (int16_t)itemp; /* imaginary in even */

        temp = ONE_Q15 * cos(2*PI*i/dftLength);
        if (temp > 0)
        {
            temp = temp + 0.5;
        }
        else
        {
            temp = temp -0.5;
        }
        itemp = (int32_t) temp;

        if(itemp >= ONE_Q15)
        {
            itemp = ONE_Q15 - 1;
        }
        dftSinCosTable[2*i+1] = (int16_t) itemp; /* real in odd */
    }
}

#define ROUND(x) ((x) < 0 ? ((x) - 0.5) : ((x) + 0.5) )

void Test_genTables(uint32_t numDopplerBins)
{
    float temp;
    cmplx16ImRe_t *dftHalfBin = (cmplx16ImRe_t *) &testDftHalfBin;

    /* Generate SIN/COS table for single point DFT */
    gen_dftSinCosTable(numDopplerBins,(int16_t *)testDftSinCosTable);
    
    temp = ONE_Q15 * - sinf(PI_/numDopplerBins);
    dftHalfBin->imag = (int32_t) ROUND(temp);
    
    temp = ONE_Q15 * cosf(PI_/numDopplerBins);
    dftHalfBin->real = (int32_t) ROUND(temp);
}



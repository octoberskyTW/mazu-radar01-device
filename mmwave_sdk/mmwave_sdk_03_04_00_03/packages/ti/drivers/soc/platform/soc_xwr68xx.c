/*!
 *   @file  soc_xwr68xx.c
 *
 *   @brief
 *      This is the XWR68xx Platform specific wrapper for the SOC module.
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
#include <stdint.h>
#include <string.h>
#include <ti/drivers/soc/soc.h>
#include <ti/common/sys_common.h>
#include <ti/drivers/soc/include/soc_internal.h>
#include <ti/drivers/osal/DebugP.h>


/**
 * @brief
 *  This defines the number of LUT entries for address translation.
 *  The contiguous address ranges are consolidated as much as possible
 *  to limit the time spent in lookup actions.
 *
 *  \ingroup SOC_DRIVER_INTERNAL_DEFINITION
 */
#define SOC_TRANSLATEADDR_NUM_ENTRIES   4

/**
 * @brief
 *  SOC Lookup table for address translation
 *
 * @details
 *  The structure is a lookup table for address translation
 *
 *  \ingroup SOC_DRIVER_INTERNAL_FUNCTION
 */
uint32_t SOC_TranslateAddr_LUT[SOC_TRANSLATEADDR_NUM_ENTRIES][SOC_TranslateAddr_LUT_Type_MAX] =
{
    /* MSS, EDMA, DSS, Size */
    {0x00000000U,0x40000000U,0x40000000U,0x0FFFFFFFU},      /* TCM memories, SW Buffer              */
    {0x50000000U,0x06000000U,0x02000000U,0x00FFFFFFU},      /* DSS register space                   */
    {0x51000000U,0x20000000U,0x20000000U,0x02FFFFFFU},      /* L3 memory,ADC/CQ/CP memory, HSRAM    */
    {0x577E0000U,0x107E0000U,0x007E0000U,0x0081FFFFU}       /* DSS L1/L2 memory                     */
};

/**
 *  @b Description
 *  @n
 *      This function translates the inAddr from one domain to the other
 *
 *  @param[in] inAddr
 *      input address that needs to be translated
 *  @param[in] direction
 *      hint on which domain to translate from and to
 *  @param[out] errCode
 *      Error code populated on error
 *
 *  \ingroup SOC_DRIVER_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - valid translated address and errCode is set to 0
 *  @retval
 *      Error       - SOC_TRANSLATEADDR_INVALID and errCode is set to SOC_EINVAL
 */
uint32_t SOC_translateAddress(uint32_t inAddr, SOC_TranslateAddr_Dir direction, int32_t* errCode)
{
    int32_t         retCode = SOC_EINVAL;
    uint32_t        outAddr = SOC_TRANSLATEADDR_INVALID;
    uint32_t        idx = 0;
    SOC_TranslateAddr_LUT_Type inAddrLUTtype,outAddrLUTtype;

    /* get the inAddr and outAddr domain */
    inAddrLUTtype = SOC_getInAddr_LUTType(direction);
    outAddrLUTtype = SOC_getOutAddr_LUTType(direction);

    if ((inAddrLUTtype != SOC_TranslateAddr_LUT_Type_INVALID) &&
        (outAddrLUTtype != SOC_TranslateAddr_LUT_Type_INVALID))
    {
        /* loop around the LUT to translate inAddr to outAddr */
        for (idx=0;idx<SOC_TRANSLATEADDR_NUM_ENTRIES;idx++)
        {
            /* skip entries where the address is invalid */
            if ((SOC_TranslateAddr_LUT[idx][inAddrLUTtype] == SOC_TRANSLATEADDR_INVALID) ||
                (SOC_TranslateAddr_LUT[idx][outAddrLUTtype] == SOC_TRANSLATEADDR_INVALID))
                continue;

            /* get the idx where inAddr falls */
            if ((inAddr >= SOC_TranslateAddr_LUT[idx][inAddrLUTtype]) &&
                (inAddr <= (SOC_TranslateAddr_LUT[idx][inAddrLUTtype]+
                            SOC_TranslateAddr_LUT[idx][SOC_TranslateAddr_LUT_Type_SIZE])))
            {
                /* found the entry; get the offset and add it to the outAddrLUTtype start address */
                outAddr = (inAddr - SOC_TranslateAddr_LUT[idx][inAddrLUTtype])+
                           SOC_TranslateAddr_LUT[idx][outAddrLUTtype];
                retCode = 0;
                break;
            }
        }
    }

    /* default is error condition, so no need to check the exhaustion of for loop here */
    if (errCode != NULL) {
        *errCode = retCode;
    }
    return outAddr;
}


/**
 *  @b Description
 *  @n
 *      This function is used to set the DSS Operational status for the mmWave
 *      module. This function should only be used by the mmWave module.
 *
 *  @param[in] handle
 *      Handle to the SOC Driver
 *  @param[in] state
 *      Operational State (1 is operational and 0 is not operational)
 *  @param[out] errCode
 *      Error code populated on error
 *
 *  \ingroup SOC_DRIVER_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 */
int32_t SOC_setMMWaveDSSLinkState(SOC_Handle handle, uint8_t state, int32_t* errCode)
{
    SOC_DriverMCB*      ptrSOCDriverMCB;
    int32_t             retVal = 0;

    /* Get the pointer to the SOC Driver Block: */
    ptrSOCDriverMCB = (SOC_DriverMCB*)handle;
    if (ptrSOCDriverMCB == NULL)
    {
        *errCode = SOC_EINVAL;
        retVal   = MINUS_ONE;
    }
    else
    {
        /* Set the operational status for the DSS */
        ptrSOCDriverMCB->ptrTopRCMRegs->SPARE1 = CSL_FINSR (ptrSOCDriverMCB->ptrTopRCMRegs->SPARE1,
                                                            17U,
                                                            17U,
                                                            (uint32_t)state);
    }
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      This function is used to check the DSS Operational status for the mmWave
 *      module. This function should only be used by the mmWave module.
 *
 *  @param[in] handle
 *      Handle to the SOC Driver
 *  @param[out] errCode
 *      Error code populated on error
 *
 *  \ingroup SOC_DRIVER_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Synchronized    -   1
 *  @retval
 *      Unsynchronized  -   0
 *  @retval
 *      Error           -   <0
 */
int32_t SOC_isMMWaveDSSOperational(SOC_Handle handle, int32_t* errCode)
{
    SOC_DriverMCB*      ptrSOCDriverMCB;
    int32_t             retVal = 0;

    /* Get the pointer to the SOC Driver Block: */
    ptrSOCDriverMCB = (SOC_DriverMCB*)handle;
    if (ptrSOCDriverMCB == NULL)
    {
        *errCode = SOC_EINVAL;
        retVal   = MINUS_ONE;
    }
    else
    {
        /* Get the operational status for the DSS */
        retVal = (int32_t)CSL_FEXTR (ptrSOCDriverMCB->ptrTopRCMRegs->SPARE1, 17U, 17U);
    }
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      This function is used to set the MSS Operational status for the mmWave
 *      module. This function should only be used by the mmWave module.
 *
 *  @param[in] handle
 *      Handle to the SOC Driver
 *  @param[in] state
 *      Operational State (1 is operational and 0 is not operational)
 *  @param[out] errCode
 *      Error code populated on error
 *
 *  \ingroup SOC_DRIVER_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 */
int32_t SOC_setMMWaveMSSLinkState(SOC_Handle handle, uint8_t state, int32_t* errCode)
{
    SOC_DriverMCB*      ptrSOCDriverMCB;
    int32_t             retVal = 0;

    /* Get the pointer to the SOC Driver Block: */
    ptrSOCDriverMCB = (SOC_DriverMCB*)handle;
    if (ptrSOCDriverMCB == NULL)
    {
        *errCode = SOC_EINVAL;
        retVal   = MINUS_ONE;
    }
    else
    {
        /* Set the operational status for the MSS */
        ptrSOCDriverMCB->ptrTopRCMRegs->SPARE1 = CSL_FINSR (ptrSOCDriverMCB->ptrTopRCMRegs->SPARE1,
                                                            16U,
                                                            16U,
                                                            (uint32_t)state);
    }
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      This function is used to check the MSS Operational status for the mmWave
 *      module. This function should only be used by the mmWave module.
 *
 *  @param[in] handle
 *      Handle to the SOC Driver
 *  @param[out] errCode
 *      Error code populated on error
 *
 *  \ingroup SOC_DRIVER_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Synchronized    -   1
 *  @retval
 *      Unsynchronized  -   0
 *  @retval
 *      Error           -   <0
 */
int32_t SOC_isMMWaveMSSOperational(SOC_Handle handle, int32_t* errCode)
{
    SOC_DriverMCB*      ptrSOCDriverMCB;
    int32_t             retVal = 0;

    /* Get the pointer to the SOC Driver Block: */
    ptrSOCDriverMCB = (SOC_DriverMCB*)handle;
    if (ptrSOCDriverMCB == NULL)
    {
        *errCode = SOC_EINVAL;
        retVal   = MINUS_ONE;
    }
    else
    {
        /* Get the operational status for the MSS */
        retVal = (int32_t)CSL_FEXTR (ptrSOCDriverMCB->ptrTopRCMRegs->SPARE1, 16U, 16U);
    }
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      This function is used to set the MSS Operational status of a
 *      module executing on the MSS.
 *
 *  @param[in] handle
 *      Handle to the SOC Driver
 *  @param[in] state
 *      Operational State (1 is operational and 0 is not operational)
 *  @param[out] errCode
 *      Error code populated on error
 *
 *  \ingroup SOC_DRIVER_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 */
int32_t SOC_setMSSLinkState(SOC_Handle handle, uint8_t state, int32_t* errCode)
{
    SOC_DriverMCB*      ptrSOCDriverMCB;
    int32_t             retVal = 0;

    /* Get the pointer to the SOC Driver Block: */
    ptrSOCDriverMCB = (SOC_DriverMCB*)handle;
    if (ptrSOCDriverMCB == NULL)
    {
        *errCode = SOC_EINVAL;
        retVal   = MINUS_ONE;
    }
    else
    {
        /* Set the operational status for the MSS */
        ptrSOCDriverMCB->ptrTopRCMRegs->SPARE1 = CSL_FINSR (ptrSOCDriverMCB->ptrTopRCMRegs->SPARE1,
                                                            18U,
                                                            18U,
                                                            (uint32_t)state);
    }
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      This function is used to check the MSS Operational status for the
 *      module.
 *
 *  @param[in] handle
 *      Handle to the SOC Driver
 *  @param[out] errCode
 *      Error code populated on error
 *
 *  \ingroup SOC_DRIVER_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Synchronized    -   1
 *  @retval
 *      Unsynchronized  -   0
 *  @retval
 *      Error           -   <0
 */
int32_t SOC_isMSSOperational(SOC_Handle handle, int32_t* errCode)
{
    SOC_DriverMCB*      ptrSOCDriverMCB;
    int32_t             retVal = 0;

    /* Get the pointer to the SOC Driver Block: */
    ptrSOCDriverMCB = (SOC_DriverMCB*)handle;
    if (ptrSOCDriverMCB == NULL)
    {
        *errCode = SOC_EINVAL;
        retVal   = MINUS_ONE;
    }
    else
    {
        /* Get the operational status for the MSS */
        retVal = (int32_t)CSL_FEXTR (ptrSOCDriverMCB->ptrTopRCMRegs->SPARE1, 18U, 18U);
    }
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      This function is used to set the DSS Operational status for the
 *      module.
 *
 *  @param[in] handle
 *      Handle to the SOC Driver
 *  @param[in] state
 *      Operational State (1 is operational and 0 is not operational)
 *  @param[out] errCode
 *      Error code populated on error
 *
 *  \ingroup SOC_DRIVER_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 */
int32_t SOC_setDSSLinkState(SOC_Handle handle, uint8_t state, int32_t* errCode)
{
    SOC_DriverMCB*      ptrSOCDriverMCB;
    int32_t             retVal = 0;

    /* Get the pointer to the SOC Driver Block: */
    ptrSOCDriverMCB = (SOC_DriverMCB*)handle;
    if (ptrSOCDriverMCB == NULL)
    {
        *errCode = SOC_EINVAL;
        retVal   = MINUS_ONE;
    }
    else
    {
        /* Set the operational status for the DSS */
        ptrSOCDriverMCB->ptrTopRCMRegs->SPARE1 = CSL_FINSR (ptrSOCDriverMCB->ptrTopRCMRegs->SPARE1,
                                                            19U,
                                                            19U,
                                                            (uint32_t)state);
    }
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      This function is used to check the DSS Operational status for the
 *      module.
 *
 *  @param[in] handle
 *      Handle to the SOC Driver
 *  @param[out] errCode
 *      Error code populated on error
 *
 *  \ingroup SOC_DRIVER_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Synchronized    -   1
 *  @retval
 *      Unsynchronized  -   0
 *  @retval
 *      Error           -   <0
 */
int32_t SOC_isDSSOperational(SOC_Handle handle, int32_t* errCode)
{
    SOC_DriverMCB*      ptrSOCDriverMCB;
    int32_t             retVal = 0;

    /* Get the pointer to the SOC Driver Block: */
    ptrSOCDriverMCB = (SOC_DriverMCB*)handle;
    if (ptrSOCDriverMCB == NULL)
    {
        *errCode = SOC_EINVAL;
        retVal   = MINUS_ONE;
    }
    else
    {
        /* Get the operational status for the MSS */
        retVal = (int32_t)CSL_FEXTR (ptrSOCDriverMCB->ptrTopRCMRegs->SPARE1, 19U, 19U);
    }
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      This function is used to bring watchdog(RTIB) out of reset
 *
 *  @param[in] handle
 *      Handle to the SOC Driver
 *  @param[out] errCode
 *      Error code populated on error
 *
 *  \ingroup SOC_DRIVER_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success         -   0
 *  @retval
 *      Error           -   <0
 */
int32_t SOC_enableWatchdog(SOC_Handle handle, int32_t* errCode)
{
    SOC_DriverMCB*      ptrSOCDriverMCB;
    int32_t             retVal = 0;

    /* Get the pointer to the SOC Driver Block: */
    ptrSOCDriverMCB = (SOC_DriverMCB*)handle;
    if (ptrSOCDriverMCB == NULL)
    {
        *errCode = SOC_EINVAL;
        retVal   = MINUS_ONE;
    }
    else
    {
        /* Bring Watchdog out of Reset only when it is in reset state */
        if(CSL_FEXTR(ptrSOCDriverMCB->ptrRCMRegs->SOFTRST3,
                                 SOFTRST3_WDTRST_BIT_END,
                                 SOFTRST3_WDTRST_BIT_START) != 0x0)
        {
            /* Bring watchdog out of reset */
            ptrSOCDriverMCB->ptrRCMRegs->SOFTRST3 = CSL_FINSR (ptrSOCDriverMCB->ptrRCMRegs->SOFTRST3,
                                                                SOFTRST3_WDTRST_BIT_END,
                                                                SOFTRST3_WDTRST_BIT_START,
                                                                0U);
        }
    }
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      This function is used to hold watchdog(RTIB) in reset
 *
 *  @param[in] handle
 *      Handle to the SOC Driver
 *  @param[out] errCode
 *      Error code populated on error
 *
 *  \ingroup SOC_DRIVER_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success         -   0
 *  @retval
 *      Error           -   <0
 */
int32_t SOC_disableWatchdog(SOC_Handle handle, int32_t* errCode)
{    
    SOC_DriverMCB*      ptrSOCDriverMCB;    
    int32_t             retVal = 0;     

    /* Get the pointer to the SOC Driver Block: */    
    ptrSOCDriverMCB = (SOC_DriverMCB*)handle;    
    if (ptrSOCDriverMCB == NULL)    
    {
        *errCode = SOC_EINVAL;
        retVal   = MINUS_ONE;
    }
    else
    {
        /* Put Watchdog into Reset */
        ptrSOCDriverMCB->ptrRCMRegs->SOFTRST3 = CSL_FINSR (ptrSOCDriverMCB->ptrRCMRegs->SOFTRST3, 
                                                            SOFTRST3_WDTRST_BIT_END, 
                                                            SOFTRST3_WDTRST_BIT_START, 
                                                            0xADU);
    }
    return retVal;
}

/**
 *  @b Description
 *  @n
 *      This function enables access to hardware accelerator config memory.
 *
 *  @param[in] handle
 *      Handle to the SOC Driver
 *  @param[out] errCode
 *      Error code populated on error
 *
 *  \ingroup SOC_DRIVER_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 */
int32_t SOC_enableHWA(SOC_Handle handle, int32_t* errCode)
{
    SOC_DriverMCB*      ptrSOCDriverMCB;
    int32_t                      retVal = 0;

    /* Get the pointer to the SOC Driver Block: */
    ptrSOCDriverMCB = (SOC_DriverMCB*)handle;
    if (ptrSOCDriverMCB == NULL)
    {
        *errCode = SOC_EINVAL;
        retVal   = -1;
    }
    else
    {
        ptrSOCDriverMCB->ptrDSSRegs->DSSMISC = CSL_FINSR (ptrSOCDriverMCB->ptrDSSRegs->DSSMISC,
                                                           DSSMISC_FFTACCSLVEN_BIT_END,
                                                           DSSMISC_FFTACCSLVEN_BIT_START, 7U);
    }
    return retVal;
}


/**
 *  @b Description
 *  @n
 *      This function ungates clock to various modules.
 *
 *  @param[in] handle
 *      Handle to the SOC Driver
 *  @param[in] module
 *      Peripheral Module Id
 *  @param[out] errCode
 *      Error code populated on error
 *
 *  \ingroup SOC_DRIVER_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 */
int32_t SOC_ungateClock(SOC_Handle handle, SOC_ModuleId module, int32_t* errCode)
{
#if 1
    SOC_DriverMCB*      ptrSOCDriverMCB;
    int32_t             retVal = 0;

    /* Get the pointer to the SOC Driver Block: */
    ptrSOCDriverMCB = (SOC_DriverMCB*)handle;
    if (ptrSOCDriverMCB == NULL)
    {
        *errCode = SOC_EINVAL;
        retVal   = -1;
    }
    else    
    {
        switch (module)
        {
            case SOC_MODULE_BSS:
            {
                volatile uint16_t   unhaltStatus;
                unhaltStatus = (uint16_t)CSL_FEXTR (ptrSOCDriverMCB->ptrTopRCMRegs->BSSCTL, 31U, 16U);
                /* do the following steps only if BSS is in halted state */
                if (unhaltStatus != 0x0) {
                    /* Remove Clock Gating for BSS : BSSCTL[15:8] := 0 */
                    ptrSOCDriverMCB->ptrTopRCMRegs->BSSCTL = CSL_FINSR(ptrSOCDriverMCB->ptrTopRCMRegs->BSSCTL, 
                                                                        15U, 8U, 0U);
                    
                    /* Remove PClock Gating for BSS : BSSCTL[23:16] := 0 */
                    ptrSOCDriverMCB->ptrTopRCMRegs->BSSCTL = CSL_FINSR(ptrSOCDriverMCB->ptrTopRCMRegs->BSSCTL,  
                                                                        23U, 16U, 0U);
                    
                    /* DeAssert BSS Reset : BSSCTL[7:0] := 0*/
                    ptrSOCDriverMCB->ptrTopRCMRegs->BSSCTL = CSL_FINSR(ptrSOCDriverMCB->ptrTopRCMRegs->BSSCTL,  
                                                                        7U, 0U, 0U);
                    
                    /* Set the upper 16 bit of SPARE0 [31:16] to 0 */
                    ptrSOCDriverMCB->ptrTopRCMRegs->SPARE0 = CSL_FINSR(ptrSOCDriverMCB->ptrTopRCMRegs->SPARE0,  
                                                                        31U, 16U, 0U);                        
                }  
                break;
            }
            case SOC_MODULE_CBUFF:
            {
                ptrSOCDriverMCB->ptrDSSRegs->DSSCLKGATE = CSL_FINSR (ptrSOCDriverMCB->ptrDSSRegs->DSSCLKGATE,
                                                            0U, 0U, 0U);
                break;
            }
            case SOC_MODULE_LVDS:
            {
                ptrSOCDriverMCB->ptrDSSRegs->DSSCLKGATE = CSL_FINSR (ptrSOCDriverMCB->ptrDSSRegs->DSSCLKGATE,
                                                            2U, 2U, 0U);
                break;
            }
            case SOC_MODULE_CQ:
            {
                ptrSOCDriverMCB->ptrDSSRegs->DSSCLKGATE = CSL_FINSR (ptrSOCDriverMCB->ptrDSSRegs->DSSCLKGATE,
                                                            3U, 3U, 0U);
                break;
            }
            default:
            {
                *errCode = SOC_EINVAL;
                retVal = MINUS_ONE;
                break;
            }
        }
    }
    return retVal;
#else
    return 0;
#endif
    
}



/**
 *  @b Description
 *  @n
 *      This function gates clock to various modules.
 *
 *  @param[in] handle
 *      Handle to the SOC Driver
 *  @param[in] module
 *      Peripheral Module Id
 *  @param[out] errCode
 *      Error code populated on error
 *
 *  \ingroup SOC_DRIVER_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 */
int32_t SOC_gateClock(SOC_Handle handle, SOC_ModuleId module, int32_t* errCode)
{
    SOC_DriverMCB*      ptrSOCDriverMCB;
    int32_t             retVal = 0;

    /* Get the pointer to the SOC Driver Block: */
    ptrSOCDriverMCB = (SOC_DriverMCB*)handle;
    if (ptrSOCDriverMCB == NULL)
    {
        *errCode = SOC_EINVAL;
        retVal   = -1;
    }
    else    
    {
        switch (module)
        {
            case SOC_MODULE_BSS:
            {
                volatile uint16_t   unhaltStatus;
                unhaltStatus = (uint16_t)CSL_FEXTR (ptrSOCDriverMCB->ptrTopRCMRegs->BSSCTL, 31U, 16U);
                /* do the following steps only if BSS is in halted state */
                if (unhaltStatus != 0x0) 
                {                    
                    /* PClock Gating for BSS : BSSCTL[23:16] := 0xAD */
                    ptrSOCDriverMCB->ptrTopRCMRegs->BSSCTL = CSL_FINSR(ptrSOCDriverMCB->ptrTopRCMRegs->BSSCTL,  
                                                                        23U, 16U, 0xADU);

                    /* Clock Gating for BSS : BSSCTL[15:8] := 0xAD */
                    ptrSOCDriverMCB->ptrTopRCMRegs->BSSCTL = CSL_FINSR(ptrSOCDriverMCB->ptrTopRCMRegs->BSSCTL, 
                                                                        15U, 8U, 0xADU);                    
                }  
                break;
            }
            case SOC_MODULE_CBUFF:
            {
                ptrSOCDriverMCB->ptrDSSRegs->DSSCLKGATE = CSL_FINSR (ptrSOCDriverMCB->ptrDSSRegs->DSSCLKGATE,
                                                            0U, 0U, 1U);
                break;
            }
            case SOC_MODULE_LVDS:
            {
                ptrSOCDriverMCB->ptrDSSRegs->DSSCLKGATE = CSL_FINSR (ptrSOCDriverMCB->ptrDSSRegs->DSSCLKGATE,
                                                            2U, 2U, 1U);
                break;
            }
            case SOC_MODULE_CQ:
            {
                ptrSOCDriverMCB->ptrDSSRegs->DSSCLKGATE = CSL_FINSR (ptrSOCDriverMCB->ptrDSSRegs->DSSCLKGATE,
                                                            3U, 3U, 1U);
                break;
            }
            default:
            {
                *errCode = SOC_EINVAL;
                retVal = MINUS_ONE;
                break;
            }
        }
    }
    return retVal;
}



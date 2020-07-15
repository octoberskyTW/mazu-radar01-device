/*
 * Copyright (c) 2017-2018, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== Cache.c ========
 */

#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Startup.h>

#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/family/arm/v8a/Mmu.h>

#include "package/internal/Cache.xdc.h"

/*
 *  ======== Cache_Module_startup ========
 */
Int Cache_Module_startup(Int status)
{
    /* Read L1D, L1P, L2 cache info registers for ROV */
    Cache_module->l1dInfo = Cache_getCacheLevelInfo(0);
    Cache_module->l1pInfo = Cache_getCacheLevelInfo(1);
    Cache_module->l2Info = Cache_getCacheLevelInfo(2);

    return (Startup_DONE);
}

/*
 *  ======== Cache_startup ========
 *  This function is registered as a resetFxn and is
 *  not a module startup function.
 *
 *  Enable cache early if Cache_enableCache == TRUE.
 */
Void Cache_startup()
{
    UInt enabled;

    enabled = Cache_getEnabled();

    /* disable the caches if anything is currently enabled */
    if (enabled) {
        Cache_disable(Cache_Type_ALL);
    }

    /* Set CPUECTLR.SMPEN bit to enable data coherency */
    Cache_enableSmp();

    if (Cache_enableCache) {
        Cache_enable(Cache_Type_ALL);
    }

    /* Init MMU module */
    Mmu_startup();
}

/*
 *  ======== Cache_disable ========
 *  Disable the cache(s) specified by the 'type' paramter.
 */
Void Cache_disable(Bits16 type)
{
    UInt enabled, hwiKey;

    /* only disable caches that are currently enabled */
    enabled = Cache_getEnabled();

    if (enabled & (type & (Cache_Type_L1D | Cache_Type_L2))) {
        /* Disable Interurpts */
        hwiKey = Hwi_disable();
        /* Disable L1D and L2 Cache */
        Cache_disableL1D();
        /* Ensure data cache written back and disabled */
        Cache_wait();
        /* Re-enable interrupts */
        Hwi_restore(hwiKey);
    }

    if (enabled & (type & Cache_Type_L1P)) {
        Cache_disableL1P();             /* Disable ICache */
    }
}

/*
 *  ======== Cache_enable ========
 *  Enable the cache(s) specified by the 'type' parameter.
 */
Void Cache_enable(Bits16 type)
{
    UInt disabled;

    /* only enable caches that are currently disabled */
    disabled = ~(Cache_getEnabled());

    if (disabled & (type & (Cache_Type_L1D | Cache_Type_L2))) {
        Cache_enableL1D();              /* Enable L1D and L2 Cache */
    }

    if (disabled & (type & Cache_Type_L1P)) {
        Cache_enableL1P();              /* Enable ICache */
    }
}

/*
 *  ======== Cache_inv ========
 *  Invalidate the range of memory within the specified starting address and
 *  byte count.  The range of addresses operated on gets rounded down to whole
 *  cache lines in each cache.  All cache lines in range are invalidated in
 *  the caches specified by the 'type' parameter.
 */
Void Cache_inv(Ptr blockPtr, SizeT byteCnt, Bits16 type, Bool wait)
{
    if (type & (Cache_Type_L1P | Cache_Type_L2P)) {
        Cache_invL1p(blockPtr, byteCnt, wait);
    }

    if (type & (Cache_Type_L1D | Cache_Type_L2D)) {
        Cache_invL1d(blockPtr, byteCnt, wait);
    }
}

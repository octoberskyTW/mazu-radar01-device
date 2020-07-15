/*
 *  Copyright (c) 2017, Texas Instruments Incorporated
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/*
 * ======== Pmu.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Startup.h>
#include <xdc/runtime/Assert.h>

#include <ti/sysbios/hal/Hwi.h>

#include "package/internal/Pmu.xdc.h"

/*
 *  ======== Pmu_Module_startup ========
 */
Int Pmu_Module_startup(Int phase)
{
    UInt32 counterMask;

    Pmu_module->numCounters = Pmu_getNumCounters();

    counterMask = (0x1 << Pmu_module->numCounters) - 1;

    /*
     * initCounters() Algorithm:
     * 1. Disable interrupt requests for all counters.
     * 2. Clear overflow status register
     * 3. Reset and enable all counters in Performance Monitors Control
     *    Register (PMCR).
     *
     * Note: Step 3 performs a a global enable and in order to enable each
     * individual counter, the corresponding PMCNTENSET bit needs to be set
     * using Pmu_startCounter() function.
     */
    Pmu_initCounters(counterMask);

    return (Startup_DONE);
}

/*
 *  ======== Pmu_clearOverflowStatus ========
 */
Void Pmu_clearOverflowStatus(UInt counterId)
{
    Assert_isTrue((counterId < Pmu_module->numCounters),
            Pmu_A_invalidCounterId);

    Pmu_clearOverflowStatusI(counterId);
}

/*
 *  ======== Pmu_configureCounter ========
 *
 *  Algorithm:
 *  1. Disable counter
 *  2. Set event type
 *  3. Enable/Disable interrupt
 *  4. Re-enable counter
 */
Void Pmu_configureCounter(UInt counterId, UInt eventNum, Bool interruptEnabled)
{
    UInt32 enableMask, counterMask;

    Assert_isTrue((counterId < Pmu_module->numCounters),
            Pmu_A_invalidCounterId);

    enableMask = Pmu_getEnabled();
    counterMask = 0x1 << counterId;

    if (enableMask & counterMask) {
        Pmu_stopCounterI(counterId);
    }

    Pmu_configureCounterI(counterId, eventNum);

    if (interruptEnabled) {
        Pmu_enableInterruptI(counterId);
    }
    else {
        Pmu_disableInterruptI(counterId);
    }

    if (enableMask & counterMask) {
        Pmu_startCounterI(counterId);
    }
}

/*
 *  ======== Pmu_disableInterrupt ========
 */
Void Pmu_disableInterrupt(UInt counterId)
{
    Assert_isTrue((counterId < Pmu_module->numCounters),
            Pmu_A_invalidCounterId);

    Pmu_disableInterruptI(counterId);
}

/*
 *  ======== Pmu_enableInterrupt ========
 */
Void Pmu_enableInterrupt(UInt counterId)
{
    Assert_isTrue((counterId < Pmu_module->numCounters),
            Pmu_A_invalidCounterId);

    Pmu_enableInterruptI(counterId);
}

/*
 *  ======== Pmu_getCount ========
 */
UInt32 Pmu_getCount(UInt counterId)
{
    Assert_isTrue((counterId < Pmu_module->numCounters),
            Pmu_A_invalidCounterId);

    return (Pmu_getCountI(counterId));
}

/*
 *  ======== Pmu_getOverflowStatus ========
 */
Bool Pmu_getOverflowStatus(UInt counterId)
{
    Assert_isTrue((counterId < Pmu_module->numCounters),
            Pmu_A_invalidCounterId);

    if (Pmu_getOverflowStatusI(counterId)) {
        return (TRUE);
    }
    else {
        return (FALSE);
    }
}

/*
 *  ======== Pmu_interruptHandler ========
 */
Void Pmu_interruptHandler(UArg arg)
{
    UInt32 overflowFlag = Pmu_getOverflowStatusReg();

    /* Acknowledge interrupt */
    Pmu_clearOverflowStatusReg(overflowFlag);

    if (Pmu_module->interruptFunc) {
        /* Call interrupt function */
        Pmu_module->interruptFunc(overflowFlag);
    }
}

/*
 *  ======== Pmu_resetCount ========
 */
Void Pmu_resetCount(UInt counterId)
{
    Assert_isTrue((counterId < Pmu_module->numCounters),
            Pmu_A_invalidCounterId);

    Pmu_resetCountI(counterId);
}

/*
 *  ======== Pmu_setCount ========
 */
Void Pmu_setCount(UInt counterId, UInt32 counterVal)
{
    Assert_isTrue((counterId < Pmu_module->numCounters),
            Pmu_A_invalidCounterId);

    Pmu_setCountI(counterId, counterVal);
}

/*
 *  ======== Pmu_setInterruptFunc ========
 */
Void Pmu_setInterruptFunc(Pmu_IntHandlerFuncPtr interruptFunc)
{
    Hwi_Params hwiParams;

    /* Set new interruptFunc */
    Pmu_module->interruptFunc = interruptFunc;

    /*
     * If interruptFunc is not null and a Hwi has not already been
     * created, create one.
     */
    if (interruptFunc && (!(Pmu_module->hwiHandle))) {
        Assert_isTrue(Pmu_intNum != (~0), Pmu_A_badIntNum);
        Hwi_Params_init(&hwiParams);
        Pmu_module->hwiHandle = Hwi_create(Pmu_intNum, Pmu_interruptHandler,
               &hwiParams, NULL);
    }
}

/*
 *  ======== Pmu_startCounter ========
 */
Void Pmu_startCounter(UInt counterId)
{
    Assert_isTrue((counterId < Pmu_module->numCounters),
            Pmu_A_invalidCounterId);

    Pmu_startCounterI(counterId);
}

/*
 *  ======== Pmu_stopCounter ========
 */
Void Pmu_stopCounter(UInt counterId)
{
    Assert_isTrue((counterId < Pmu_module->numCounters),
            Pmu_A_invalidCounterId);

    Pmu_stopCounterI(counterId);
}

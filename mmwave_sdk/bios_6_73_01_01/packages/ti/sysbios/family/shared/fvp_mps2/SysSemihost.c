/*
 * Copyright (c) 2017, Texas Instruments Incorporated
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
 *  ======== SysSemihost.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Startup.h>

#include <stdio.h>
#include <stdlib.h>

#include "package/internal/SysSemihost.xdc.h"

#define SemiHost_PutS 0x4
#define SemiHost_SWI  0xab

/*
 *  ======== SysSemihost_Module_startup ========
 */
Int SysSemihost_Module_startup(Int phase)
{
    return (Startup_DONE);
}

/*
 *  ======== SysSemihost_abort ========
 */
Void SysSemihost_abort(CString str)
{
    Char ch;

    if (str != NULL) {
        while ((ch = *str++) != '\0') {
            SysSemihost_putch(ch);
        }
    }
}

/*
 *  ======== SysSemihost_exit ========
 */
Void SysSemihost_exit(Int stat)
{
}

/*
 *  ======== SysSemihost_putch ========
 */
#if (defined(__GNUC__) && !defined(__ti__) && defined(__ARM_ARCH_8M_MAIN__))
Void __attribute__((naked)) SysSemihost_putch(Char ch)
{
    __asm__ __volatile__ (
        "sub  sp, sp, #4\n\t"
        "str  r0, [sp]\n\t"
        "mov  r1, sp\n\t"
        "movs r0, %0\n\t"
        "bkpt %1\n\t"
        "add  sp, sp, #4\n\t"
        "bx   lr"
        :: "I" (SemiHost_PutS), "I" (SemiHost_SWI)
    );
}
#elif (defined(__IAR_SYSTEMS_ICC__) && (__CORE__ == __ARM8M_MAINLINE__))
Void SysSemihost_putch(Char ch)
{
    Char localCh[2];

    localCh[0] = ch;
    localCh[1] = '\0';

    asm volatile (
        "mov  r1, %2\n\t"
        "movs r0, %0\n\t"
        "bkpt %1"
        :: "I" (SemiHost_PutS), "I" (SemiHost_SWI), "r" (&localCh[0])
        : "r0", "r1"
    );
}
#endif

/*
 *  ======== SysSemihost_flush ========
 */
Void SysSemihost_flush()
{
}

/*
 *  ======== SysSemihost_ready ========
 */
Bool SysSemihost_ready()
{
    return (TRUE);
}

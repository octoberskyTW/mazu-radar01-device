/* 
 *  Copyright (c) 2008-2017 Texas Instruments Incorporated
 *  This program and the accompanying materials are made available under the
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * */
/*
 *  ======== SysMin.c ========
 */

#include <xdc/runtime/Startup.h>
#include <xdc/runtime/Gate.h>

#include <string.h>

#include "package/internal/SysMin.xdc.h"

/*
 *  ======== SysMin_Module_startup ========
 */
Int SysMin_Module_startup(Int phase)
{
    if (SysMin_bufSize != 0U) {
        (void)memset(module->outbuf, 0, SysMin_bufSize);
    }
    return (Startup_DONE);
}

/*
 *  ======== SysMin_abort ========
 */
Void SysMin_abort(CString str)
{
    Char ch;

    if (SysMin_bufSize != 0U) {
        if (str != (CString)NULL) {
            ch = *str;
            str++;
            while (ch != '\0') {
                SysMin_putch(ch);
                ch = *str;
                str++;
            }
        }

        /* Only flush if configured to do so */
        if (SysMin_flushAtExit) {
            SysMin_flush();
        }
    }
}

/*
 *  ======== SysMin_exit ========
 */
Void SysMin_exit(Int stat)
{
    if ((SysMin_flushAtExit == TRUE) && (SysMin_bufSize != 0U)) {
        SysMin_flush();
    }
}

/*
 *  ======== SysMin_putch ========
 */
Void SysMin_putch(Char ch)
{
    IArg key;

    if (SysMin_bufSize != 0U) {

        key = Gate_enterSystem();

        module->outbuf[module->outidx] = ch;
        module->outidx++;
        if (module->outidx == (UInt)SysMin_bufSize) {
            module->outidx = 0;
            module->wrapped = TRUE;
        }

        Gate_leaveSystem(key);
    }
}

/*
 *  ======== SysMin_ready ========
 */
Bool SysMin_ready(Void)
{
    return (Bool)(SysMin_bufSize != 0U);
}

/*
 *  ======== SysMin_flush ========
 *  Called during SysMin_exit, System_exit or System_flush.
 */
Void SysMin_flush(Void)
{
    IArg key;

    key = Gate_enterSystem();

    /*
     *  If a wrap occured, we need to flush the "end" of the internal buffer
     *  first to maintain fifo character output order.
     */
    if (module->wrapped == TRUE) {
        SysMin_outputFunc(module->outbuf + module->outidx,
                          SysMin_bufSize - module->outidx);
    }

    SysMin_outputFunc(module->outbuf, module->outidx);
    module->outidx = 0;
    module->wrapped = FALSE;

    Gate_leaveSystem(key);
}
/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 7-31-2018 11:49:30; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


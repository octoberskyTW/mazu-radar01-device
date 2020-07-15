/* 
 *  Copyright (c) 2008-2018 Texas Instruments Incorporated
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
 *  ======== SysStd.c ========
 */

#include <xdc/std.h>

#include <stdio.h>
#include <stdlib.h>

#include "package/internal/SysStd.xdc.h"

/* IAR Normal dlib does not have file descriptor support */
#if defined(__IAR_SYSTEMS_ICC__) && !(_DLIB_FILE_DESCRIPTOR)
#define fflush(stdout) 0
#endif

/*
 *  ======== SysStd_abort ========
 */
Void SysStd_abort(CString str)
{
    Char ch;

    if (str != (CString)NULL) {
        ch = *str;
        str++;
        while (ch != '\0') {
            (void)putchar((Int)ch);
            ch = *str;
            str++;
        }
    }
    (void)fflush(stdout);
}

/*
 *  ======== SysStd_exit ========
 */
Void SysStd_exit(Int stat)
{
    (void)fflush(stdout);
}

/*
 *  ======== SysStd_putch ========
 */
Void SysStd_putch(Char ch)
{
    (void)putchar((Int)ch);
}

/*
 *  ======== SysStd_flush ========
 */
Void SysStd_flush(Void)
{
    (void)fflush(stdout);
}

/*
 *  ======== SysStd_ready ========
 */
Bool SysStd_ready(Void)
{
    return (TRUE);
}
/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 7-31-2018 11:49:30; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


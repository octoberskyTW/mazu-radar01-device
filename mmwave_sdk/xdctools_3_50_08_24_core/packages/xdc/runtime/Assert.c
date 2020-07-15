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
 *  ======== Assert.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/Text.h>
#include <xdc/runtime/Types.h>

#include "package/internal/Assert.xdc.h"

/*
 *  ======== raise ========
 */
Void Assert_raise(Types_ModuleId mod, CString file, Int line, Assert_Id id)
{
    String sep = (id != 0U) ? ": " : "";
    CString msg = (id != 0U && Text_isLoaded == TRUE) ?
        Text_ropeText((Text_RopeId)(id >> 16)) : "";

    Error_raiseX(NULL, mod, file, line,
        Assert_E_assertFailed, (IArg)sep, (IArg)msg);
}
/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 7-31-2018 11:49:29; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


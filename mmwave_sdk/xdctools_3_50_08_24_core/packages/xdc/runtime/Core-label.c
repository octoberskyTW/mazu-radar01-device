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
 *  ======== Core-label.c ========
 */

#include <string.h>

#include <xdc/runtime/Text.h>
#include <xdc/runtime/Types.h>

#include "package/internal/Core.xdc.h"

/*
 *  ======== Core_assignLabel ========
 */
Void Core_assignLabel(Types_Label *lab, Text_CordAddr iname, Bool named)
{
    String ns;

    lab->named = named;

    if (named == FALSE) {
        ns = Text_nameUnknown;
    }
    else if (iname == (Text_CordAddr)NULL) {
        ns = Text_nameEmpty;
    }
    else {
        ns = Text_cordText(iname);
        if (ns == (String)NULL) {
            ns = Text_nameStatic;
        }
    }

    lab->iname = ns;
}
/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 7-31-2018 11:49:29; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


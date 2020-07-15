/* 
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
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
 *  ======== GateH.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/IGateProvider.h>

#include "package/internal/GateH.xdc.h"

/*
 *  ======== GateH_enter ========
 */
IArg GateH_enter(IGateProvider_Handle gate)
{
    return (GateH_Proxy_enter(gate));
}

/*
 *  ======== GateH_leave ========
 */
Void GateH_leave(IGateProvider_Handle gate, IArg key)
{
    GateH_Proxy_leave(gate, key);
}
/*
 *  @(#) xdc.runtime.knl; 1, 0, 0,0; 7-31-2018 11:49:36; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


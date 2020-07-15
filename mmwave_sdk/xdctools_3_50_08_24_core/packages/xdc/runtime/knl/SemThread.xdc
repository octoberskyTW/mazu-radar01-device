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
 *  ======== SemThread.xdc ========
 */

import xdc.runtime.Error;
import xdc.runtime.knl.ISemaphore;
import xdc.runtime.knl.ISemThreadSupport;

/*!
 *  ======== SemThread ========
 *  SemThread Manager.
 *
 *  This module manages semaphores through its proxy ISemThreadSupport
 *  interface. It has a module wide config parameter 
 *  {@link #Proxy} which needs to be bound to an OS specific delegate before
 *  this module can be used.
 *
 *  Here is an example showing how the proxy is bound to an BIOS 6.x specific
 *  delegate.
 *
 *  @p(code)
 *  var SemThread = xdc.useModule('xdc.runtime.knl.SemThread');
 *  SemThread.Proxy = xdc.useModule('ti.sysbios.xdcruntime.SemThreadSupport');
 *  @p
 *
 *  Typically the package containing the delegates have a Settings module that 
 *  will bind all {@link xdc.runtime.knl} proxies. The following
 *  example sets up all the xdc.runtime.knl proxies.
 *
 *  @p(code)
 *  xdc.useModule("ti.sysbios.xdcruntime.Settings");
 *  @p
 */
@InstanceInitError      /* because initialization can fail */
@InstanceFinalize       /* have to SemThread_Proxy_delete(sem) on delete */

module SemThread inherits ISemaphore
{

    /*! Proxy that needs to be bound to an OS specific delegate. */
    proxy Proxy inherits ISemThreadSupport;

instance:

   /*!
    *  ======== create ========
    *  Create a SemThread object.
    *
    *  This function creates a new `SemThread` object which is initialized to
    *  count.
    *
    *  @param(count)    initial semaphore count
    */
    create(Int count);

internal:

    struct Instance_State {
        Proxy.Handle proxyHandle;
    }

}
/*
 *  @(#) xdc.runtime.knl; 1, 0, 0,0; 7-31-2018 11:49:36; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


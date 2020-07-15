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
 *  ======== ISemThreadSupport.xdc ========
 */

/*! 
 *  ======== ISemThreadSupport ========
 *  Interface for OS specific back-end.
 *
 *  The {@link xdc.runtime.knl} package contains modules that provide typical
 *  OS services. These xdc.runtime.knl modules require proxies to be
 *  bound to an OS specific delegate. This specifies the interface to 
 *  be implemented by the OS specific delegate for 
 *  {@link xdc.runtime.knl#SemThread} module.
 * 
 *  This interface adds the create() function.
 */
interface ISemThreadSupport inherits ISemaphore
{

instance:

   /*!
    *  ======== create ========
    *  Create a Semaphore object
    *
    *  This function creates a new Semaphore object which is initialized to
    *  count.
    *
    *  @param(count)    initial semaphore count
    */
    create(Int count);
}
/*
 *  @(#) xdc.runtime.knl; 1, 0, 0,0; 7-31-2018 11:49:36; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


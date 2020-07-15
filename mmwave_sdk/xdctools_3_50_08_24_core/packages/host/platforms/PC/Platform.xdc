/* 
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * */
/*
 *  ======== Platform.xdc ========
 */

package host.platforms.PC;

/*!
 *  ======== Platform ========
 *  Native PC platform support
 *
 *  This module implements xdc.platform.IPlatform and defines configuration
 *  parameters that correspond to this platform's Cpu's, Board's, etc.
 *
 *  The configuration parameters are initialized in this package's
 *  configuration script (package.cfg) and "bound" to the TCOM object
 *  model.  Once they are part of the model, these parameters are
 *  queried by a program's configuration script.
 *
 *  This particular platform has a single Cpu, and therefore, only
 *  declares a single CPU configuration object.  Multi-CPU platforms
 *  would declare multiple Cpu configuration parameters (one per
 *  platform CPU).
 */

metaonly module Platform inherits xdc.platform.IPlatform
{
    /*!
     *  ======== BOARD ========
     *  @_nodoc this structure (and CPU below) exists to satisfy the
     *  IPlatform interface requirements; these fields are largely
     *  unnecessary for host platforms.
     */
    readonly config xdc.platform.IPlatform.Board BOARD = {	
	id:		"0",
	boardName:	"intel-x86",
	boardFamily:	"intel-x86",
	boardRevision:	null
    };

    /*!
     *  ======== CPU ========
     *  @_nodoc 
     */
    readonly config xdc.platform.IExeContext.Cpu CPU = {	
	id:		"0",
	clockRate:	1000.0,
	catalogName:	"host.platforms.PC",
	deviceName:	"Intel80586",
	revision:	"",
    };

instance:
}
/*
 *  @(#) host.platforms.PC; 1, 0, 0,0; 7-31-2018 11:47:49; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


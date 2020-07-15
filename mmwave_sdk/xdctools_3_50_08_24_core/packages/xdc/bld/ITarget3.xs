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
 *  ======== ITarget.getRawVersion ========
 *  Default implementation for ITarget.getRawVersion()
 *
 *  This allows targets to not implement this method and have the build
 *  engine assume that all targets do implement this method.
 */
function getRawVersion()
{
    return ("0.0.0");
}

/*
 *  @(#) xdc.bld; 1, 0, 2,0; 7-31-2018 11:48:27; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


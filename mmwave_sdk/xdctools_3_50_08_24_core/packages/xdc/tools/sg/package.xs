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
function init()
{
    switch (String(environment['os.name'])) {
        case 'Linux':
            xdc.loadPackage('xdc.tools.sg.swt_linux');
            break;

        case 'SunOS':
            xdc.loadPackage('xdc.tools.sg.swt_solaris');
            break;

        case 'Mac OS X':
            xdc.loadPackage('xdc.tools.sg.swt_macos');
            break;

        default:
            xdc.loadPackage('xdc.tools.sg.swt_win32');
            break;
    }
}
/*
 *  @(#) xdc.tools.sg; 1, 0, 0,0; 7-31-2018 11:51:46; /db/ztree/library/trees/xdc/xdc-E10/imports/
 */


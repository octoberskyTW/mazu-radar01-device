/* 
 *  Copyright (c) 2014 Texas Instruments and others.
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
 *  ======== MSP430X_small.getRawVersion ========
 */
var checkVers =  true;

function getRawVersion()
{
    var result = this.$super.getRawVersion.$fxn.call(this);

    if (checkVers && parseFloat(result).toFixed(2) < 6.10) {
        for (var i in this.profiles) {
            /* Older toolchains have different naming conventions */
            var copts = this.profiles[i].compileOpts.copts;
            copts = copts.replace(/dl430xlsf/, "dl430xsf");
            this.profiles[i].compileOpts.copts = copts; 

            var linkOpts = this.profiles[i].linkOpts;
            linkOpts = linkOpts.replace(/dl430xlsf/, "dl430xsf");
            this.profiles[i].linkOpts = linkOpts;
        }
        checkVers = false;
    }

    return (result);
}
/*
 *  @(#) iar.targets.msp430; 1, 0, 0,0; 7-20-2018 13:58:48; /db/ztree/library/trees/xdctargets/xdctargets-r09/src/ xlibrary

 */


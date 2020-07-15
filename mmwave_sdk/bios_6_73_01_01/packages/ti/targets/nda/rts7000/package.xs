/* 
 *  Copyright (c) 2008-2016 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * */
function getLibs(prog)
{
    var libs = "lib/boot.a" + prog.build.target.suffix;
    if (prog.targetModules().length > 0 && this.Settings.bootOnly == false) {
        libs = "lib/" + this.$name + ".a" + prog.build.target.suffix + ";"
            + libs;
    }
    return (libs);
}

function getSects() {
    if (Program.targetModules().length == 0) {
        return ("ti/targets/nda/rts7000/link.xdt");
    }
    else {
        return (null);
    }
}
/*
 *  @(#) ti.targets.nda.rts7000; 1, 0, 0,0; 7-20-2018 14:28:28; /db/ztree/library/trees/xdctargets/xdctargets-r09/src/ xlibrary

 */


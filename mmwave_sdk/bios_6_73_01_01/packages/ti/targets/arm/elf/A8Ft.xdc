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
/*!
 *  @_nodoc
 *  ======== A8Ft.xdc ========
 *  Cortex A8 thumb2 little endian with floating point support (NEON) (ELF)
 */
metaonly module A8Ft inherits ti.targets.arm.elf.IA8 {
    override readonly config string name        = "A8Ft";
    override readonly config string suffix      = "ea8ft";
    override readonly config string rts         = "ti.targets.arm.rtsarm";

    override readonly config xdc.bld.ITarget.Model model = {
        endian: "little",
        codeModel: "thumb2",
        shortEnums: true
    };

    override readonly config xdc.bld.ITarget2.Command cc = {
        cmd:  "armcl -c",
        opts: "-mt --neon --endian=little -mv7A8 --abi=eabi"
    };

    override readonly config xdc.bld.ITarget2.Command asm = {
        cmd:  "armcl -c",
        opts: "-mt --neon --endian=little -mv7A8 --abi=eabi"
    };
}
/*
 *  @(#) ti.targets.arm.elf; 1, 0, 0,0; 7-20-2018 13:59:04; /db/ztree/library/trees/xdctargets/xdctargets-r09/src/ xlibrary

 */


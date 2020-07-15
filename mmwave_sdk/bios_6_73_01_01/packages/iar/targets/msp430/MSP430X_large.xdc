/* 
 *  Copyright (c) 2014-2016 Texas Instruments Incorporated
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
 *  ======== MSP430X_large ========
 *  IAR MSP430X little endian, large code model, large data model target.
 */

metaonly module MSP430X_large inherits ITarget
{
    override readonly config String name             = "MSP430X_large";
    override readonly config String suffix           = "r430XL";
    override readonly config String isa              = "430X";    
    override readonly config xdc.bld.ITarget.Model model = {
        endian: "little",
        codeModel: "large",
        dataModel: "large",
        shortEnums: true
    };

    /*!
     *  ======== cc ========
     *  The command used to compile C/C++ source files into object files
     *
     *  Defaults:
     *  @p(dlist)
     *      -`-e`
     *          enable compiler extensions so it's possible to get segment
     *          start addresses in C, via:
     *          @p(code)
     *              #pragma segment = "CSTACK"
     *              isrStack = __segment_begin("CSTACK");
     *          @p
     *      -`--core=430X`
     *          MSP430X architecture
     *      -`--data_model`
     *          Large data model for 430X core
     *  @p
     */
    override readonly config Command cc = {
        cmd: "icc430",
        opts: "-e --core=430X --data_model=large"
    };
   
    /*!
     *  ======== asm ========
     *  The command used to assembles assembly source files into object files
     *
     *  Defaults:
     *  @p(dlist)
     *      -`-v1`
     *          MSP430X architecture
     *      -`-D__LARGE_DATA_MODEL__`
     *          indicate that this is large model to assembly code; IAR does
     *          currently have any pre-defined macros for this purpose; we use
     *          this symbol because it is the same as that used by the TI
     *          compiler (so some degree of portability is possible).
     *  @p
     */
    override readonly config Command asm = {
        cmd: "a430",
        opts: "-v1 --data_model large --code_model large -D__LARGE_DATA_MODEL__ -DUSE_LARGE_CODE_MODEL=1"
    };

    /*!
     *  ======== profiles ========
     *  Standard options profiles for the IAR MSP430 tool-chain.
     */
    override config xdc.bld.ITarget.OptionSet profiles[string] = [
        ["debug", {
            compileOpts: {
                copts: "--debug --dlib_config $(rootDir)/lib/dlib/dl430xllfn.h",
            },
            linkOpts: "$(rootDir)/lib/dlib/dl430xllfn.r43",
        }],
        ["release", {
            compileOpts: {
                copts: "-Ohs --dlib_config $(rootDir)/lib/dlib/dl430xllfn.h",
            },
            linkOpts: "$(rootDir)/lib/dlib/dl430xllfn.r43",
        }],
        ["debug_full", {
            compileOpts: {
                copts: "--debug --dlib_config $(rootDir)/lib/dlib/dl430xllff.h",
            },
            linkOpts: "$(rootDir)/lib/dlib/dl430xllff.r43",
        }],
        ["release_full", {
            compileOpts: {
                copts: "-Ohs --dlib_config $(rootDir)/lib/dlib/dl430xllff.h",
            },
            linkOpts: "$(rootDir)/lib/dlib/dl430xllff.r43",
        }],

    ];

    override readonly config xdc.bld.ITarget.StdTypes stdTypes = {
        t_IArg          : { size: 4, align: 2 },
        t_Char          : { size: 1, align: 1 },
        t_Double        : { size: 4, align: 2 },
        t_Float         : { size: 4, align: 2 },
        t_Fxn           : { size: 4, align: 2 },
        t_Int           : { size: 2, align: 2 },
        t_Int8          : { size: 1, align: 1 },
        t_Int16         : { size: 2, align: 2 },
        t_Int32         : { size: 4, align: 2 },
        t_Long          : { size: 4, align: 2 },
        t_LDouble       : { size: 4, align: 2 },
        t_LLong         : { size: 8, align: 2 },
        t_Ptr           : { size: 4, align: 2 },
        t_Short         : { size: 2, align: 2 },
        t_Size          : { size: 4, align: 2 },
    };
}
/*
 *  @(#) iar.targets.msp430; 1, 0, 0,0; 7-20-2018 13:58:48; /db/ztree/library/trees/xdctargets/xdctargets-r09/src/ xlibrary

 */


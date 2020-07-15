/*
 * Copyright (c) 2016-2018, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== Mmu.xs ========
 */

var Mmu = null;
var Memory = null;

/*
 *  ======== module$meta$init ========
 */
function module$meta$init()
{
    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }

    Mmu = this;

    /* set fxntab default */
    Mmu.common$.fxntab = false;
}

/*
 *  ======== module$use ========
 */
function module$use()
{
    Memory = xdc.module('xdc.runtime.Memory');

    if (Mmu.initFunc == null) {
        Mmu.$logError("Mmu.initFunc must be set to a valid function.",
            Mmu, "initFunc");
    }

    switch (Mmu.granuleSize) {
        case Mmu.GranuleSize_4KB:
            Mmu.configInfo.granuleSizeBits = 12;
            break;
        case Mmu.GranuleSize_16KB:
            Mmu.configInfo.granuleSizeBits = 14;
            break;
        case Mmu.GranuleSize_64KB:
            Mmu.configInfo.granuleSizeBits = 16;
            break;
        default:
            Mmu.$logError("Invalid granule size.", Mmu, "granuleSize");
    }

    Mmu.configInfo.indexBits = Mmu.configInfo.granuleSizeBits - 3;
    Mmu.configInfo.tableLength = Mmu.granuleSize >> 3;
    Mmu.configInfo.tableOffset[3] = Mmu.configInfo.granuleSizeBits;
    Mmu.configInfo.tableOffset[2] = Mmu.configInfo.tableOffset[3] +
                                    Mmu.configInfo.indexBits;
    Mmu.configInfo.tableOffset[1] = Mmu.configInfo.tableOffset[2] +
                                    Mmu.configInfo.indexBits;
    Mmu.configInfo.tableOffset[0] = Mmu.configInfo.tableOffset[1] +
                                    Mmu.configInfo.indexBits;

    if (Mmu.configInfo.tableOffset[0] >= Mmu.PA_MAX_WIDTH) {
        Mmu.configInfo.noLevel0Table = true;
    }
    else {
        Mmu.configInfo.noLevel0Table = false;
    }

    Mmu.configInfo.indexMask = (1 << Mmu.configInfo.indexBits) - 1;
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(mod, params)
{
}

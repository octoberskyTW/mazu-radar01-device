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
 *  ======== Mmu.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Startup.h>

#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/family/arm/v8a/Cache.h>

#include "package/internal/Mmu.xdc.h"

#define Mmu_PADDR_MASK          0x0000FFFFFFFFFFFF

#define Mmu_GRANULE_SIZE_4KB    0x0000
#define Mmu_GRANULE_SIZE_16KB   0x8000
#define Mmu_GRANULE_SIZE_64KB   0x4000

#define Mmu_OUTER_SHAREABLE     0x2000
#define Mmu_OUTER_CACHEABLE     0x0400
#define Mmu_INNER_CACHEABLE     0x0100

#define Mmu_level1Table    ti_sysbios_family_arm_v8a_Mmu_level1Table
#define Mmu_tableArray     ti_sysbios_family_arm_v8a_Mmu_tableArray
#define Mmu_tableArraySlot ti_sysbios_family_arm_v8a_Mmu_tableArraySlot

extern UInt64 *Mmu_level1Table;
extern UInt64  Mmu_tableArray[];
extern UInt64  Mmu_tableArraySlot;

/*
 * TODO Pending work
 * =================
 *  - Add custom memset() for BIOS (name it differently). Copy implementation
 *    from RTS version.
 */

/*
 *  ======== Mmu_addBlockEntry ========
 */
Void Mmu_addBlockEntry(UInt8 level, UInt64 *tablePtr, UInt16 tableIdx,
    UInt64 paddr, Mmu_MapAttrs *mapAttrs)
{
    UInt64 desc;

    if (level == 3) {
        desc = 0x3;
    }
    else {
        desc = Mmu_DescriptorType_BLOCK;
    }

    desc |= ((UInt64)(mapAttrs->attrIndx & 0x7) << 2) |
            ((UInt64)(0x1 << 5)) |
            ((UInt64)(mapAttrs->accessPerm & 0x3) << 6) |
            ((UInt64)(mapAttrs->shareable & 0x3) << 8) |
            ((UInt64)(0x1) << 10) |  /* access flag */
            ((UInt64)(!(mapAttrs->global) & 0x1) << 11) | 
            ((UInt64)(paddr & ~((1 << Mmu_configInfo.tableOffset[level]) - 1))) |
            ((UInt64)(!(mapAttrs->privExecute) & 0x1) << 53) |
            ((UInt64)(!(mapAttrs->userExecute) & 0x1) << 54);

    tablePtr[tableIdx] = desc;
}

/*
 *  ======== Mmu_addTableEntry ========
 */
UInt64* Mmu_addTableEntry(UInt64 *tablePtr, UInt16 tableIdx,
    Mmu_MapAttrs *mapAttrs)
{
    UInt64 desc, *newTable;

    newTable = Mmu_allocTable();
    if (newTable == NULL) {
        return (NULL);
    }

    desc = ((UInt64)Mmu_DescriptorType_TABLE & 0x3) |
           ((UInt64)newTable & ~(Mmu_granuleSize - 1));
    tablePtr[tableIdx] = desc;

    return (newTable);
}

/*
 *  ======== Mmu_allocTable ========
 */
UInt64* Mmu_allocTable()
{
    UInt64 *table;
    UInt i, tableLen = (Mmu_granuleSize >> 3);

    if (Mmu_tableArraySlot == (~0)) {
        return (NULL);
    }

    table = &Mmu_tableArray[tableLen * Mmu_tableArraySlot];
    Mmu_tableArraySlot = *table;

    /* Zero-out level 1 table */
    for (i = 0; i < tableLen; i++) {
        /*
         * Use (i << 2) instead of 0 to init table, in order to force
         * compiler to not use memset() as an optimization
         */
        table[i] = (i << 2);
    }

    return (table);
}

/*
 *  ======== Mmu_disable ========
 *  Function to disable the MMU.
 */
Void Mmu_disable()
{
    UInt16 type;
    UInt   key;

    /* if MMU is alreay disabled, just return */
    if (!(Mmu_isEnabled())) {
        return;
    }
    
    key = Hwi_disable();

    /* get the current enabled bits */
    type = Cache_getEnabled();
    
    if (type & Cache_Type_L1D) {
        /* disable the L1 data cache */
        Cache_disable(Cache_Type_L1D);
    }
    
    if (type & Cache_Type_L1P) {
        /* disable L1P cache */
        Cache_disable(Cache_Type_L1P);
    }

    /* disables the MMU */
    Mmu_disableI();

    /* set cache back to initial settings */
    Cache_enable(type);

    Hwi_restore(key);
}

/*
 *  ======== Mmu_disableI ========
 */
Void Mmu_disableI()
{
    __asm__ __volatile__ (
        "mrs x0, SCTLR_EL1 \n\t"
        "bic x0, x0, #0x1 \n\t"
        "msr SCTLR_EL1, x0"
        ::: "x0", "memory"
    );
}

/*
 *  ======== Mmu_enable ========
 */
Void Mmu_enable()
{
    UInt16 type;
    UInt   key;

    /* if MMU is already enabled then just return */
    if (Mmu_isEnabled()) {
        return;
    }

    key = Hwi_disable();

    /* get the current enabled bits */
    type = Cache_getEnabled();
    
    if (type & Cache_Type_ALLP) {
        /* disable L1P cache */
        Cache_disable(Cache_Type_ALLP);
    }

    /* Invalidate entire TLB */
    Mmu_tlbInvAll();
    
    /* enables the MMU */
    Mmu_enableI();
    
    /* set cache back to initial settings */
    Cache_enable(type);

    Hwi_restore(key);
}

/*
 *  ======== Mmu_enableI ========
 */
Void Mmu_enableI()
{
    __asm__ __volatile__ (
        "mrs x0, SCTLR_EL1 \n\t"
        "orr x0, x0, #0x1 \n\t"
        "msr SCTLR_EL1, x0"
        ::: "x0", "memory"
    );
}

/*
 *  ======== Mmu_freeTable ========
 */
Void Mmu_freeTable(UInt64 *table)
{
    *table = Mmu_tableArraySlot;
    Mmu_tableArraySlot = (table - Mmu_tableArray) / (Mmu_granuleSize >> 3);
}

/*
 *  ======== Mmu_init ========
 */
Void Mmu_init(Ptr tableAddr)
{
    __asm__ __volatile__ (
        "msr TTBR0_EL1, %0"
        :: "r" (tableAddr)
        :
    );
}

/*
 *  ======== Mmu_initMapAttrs ========
 */
Void Mmu_initMapAttrs(Mmu_MapAttrs *attrs)
{
    /* Assert that attrs != NULL */
    Assert_isTrue(attrs != NULL, Mmu_A_nullPointer);

    attrs->accessPerm = Mmu_defaultMapAttrs.accessPerm;
    attrs->privExecute = Mmu_defaultMapAttrs.privExecute;
    attrs->userExecute = Mmu_defaultMapAttrs.userExecute;
    attrs->shareable = Mmu_defaultMapAttrs.shareable;
    attrs->attrIndx = Mmu_defaultMapAttrs.attrIndx;
    attrs->global = Mmu_defaultMapAttrs.global;
}

/*
 *  ======== Mmu_isEnabled ========
 */
Bool Mmu_isEnabled()
{
    Bool status;

    __asm__ __volatile__ (
        "mrs %0, SCTLR_EL1 \n\t"
        "and %0, %0, #0x1"
        : "+r" (status)
    );

    return (status);
}

/*
 *  ======== Mmu_map ========
 */
Bool Mmu_map(UInt64 vaddr, UInt64 paddr, SizeT size, Mmu_MapAttrs *mapAttrs)
{
    UInt key;
    Bool retStatus, enabled;

    /* Assert that mapAttrs != NULL */
    Assert_isTrue(mapAttrs != NULL, Mmu_A_nullPointer);

    /* Range check on vaddr and paddr */
    Assert_isTrue(vaddr <= Mmu_PADDR_MASK, Mmu_A_vaddrOutOfRange);
    Assert_isTrue(paddr <= Mmu_PADDR_MASK, Mmu_A_paddrOutOfRange);

    /* Alignment check on vaddr, paddr & size */
    Assert_isTrue((vaddr & (Mmu_granuleSize - 1)) == 0, Mmu_A_unalignedVaddr); 
    Assert_isTrue((paddr & (Mmu_granuleSize - 1)) == 0, Mmu_A_unalignedPaddr); 
    Assert_isTrue((size & (Mmu_granuleSize - 1)) == 0, Mmu_A_unalignedSize); 

    key = Hwi_disable();

    /* determine the current state of the MMU */
    enabled = Mmu_isEnabled();

    /* disable the MMU (if already disabled, does nothing) */
    Mmu_disable();

    if (Mmu_configInfo.noLevel0Table) {
        retStatus = Mmu_tableWalk(1, Mmu_level1Table, &vaddr, &paddr,
            &size, mapAttrs);
    }
    else {
        retStatus = Mmu_tableWalk(0, Mmu_level1Table, &vaddr, &paddr,
            &size, mapAttrs);
    }

    /* Ensure all translation table updates have been observed */
    __asm__ __volatile__ (
        "dsb sy"
        ::: "memory"
    );

    if (enabled) {
        /* if Mmu was enabled, then re-enable it */
        Mmu_enable();
    }

    Hwi_restore(key);

    return (retStatus);
}

/*
 *  ======== Mmu_readBlockEntry ========
 */
Void Mmu_readBlockEntry(UInt8 level, UInt64 *tablePtr, UInt16 tableIdx,
    UInt64 *paddr, Mmu_MapAttrs *mapAttrs)
{
    UInt64 desc;

    desc = tablePtr[tableIdx];

    mapAttrs->attrIndx = (desc >> 2) & 0x7;
    mapAttrs->accessPerm = (desc >> 6) & 0x3;
    mapAttrs->shareable = (desc >> 8) & 0x3;
    mapAttrs->global = !((desc >> 11) & 0x1);
    mapAttrs->privExecute = !((desc >> 53) & 0x1);
    mapAttrs->userExecute = !((desc >> 54) & 0x1);

    *paddr = desc & (UInt64)Mmu_PADDR_MASK &
        ~((1 << Mmu_configInfo.tableOffset[level]) - 1);
}

/*
 *  ======== Mmu_setMAIR ========
 */
Void Mmu_setMAIR(UInt8 idx, UInt8 attr)
{
    UInt key;

    key = Hwi_disable();

    /* Write attr to MAIRn register */
    Mmu_setMAIRAsm(idx, attr);

    /* Invalidate the entire TLB (broadcast to other cores) */
    Mmu_tlbInvAll();

    Hwi_restore(key);
}

/*
 *  ======== Mmu_setMAIRAsm ========
 */
Void Mmu_setMAIRAsm(UInt8 idx, UInt8 attr)
{
    __asm__ __volatile__ (
        "lsl %0, %0, #3 \n\t"   /* 8 X idx */
        "lslv %1, %1, %0 \n\t"  /* attr << (8 X idx) */
        "mov x0, #0xFF \n\t"
        "lslv x0, x0, %0 \n\t"
        "mrs %0, MAIR_EL1 \n\t"
        "bic %0, %0, x0 \n\t"
        "orr %0, %0, %1 \n\t"
        "msr MAIR_EL1, %0"
        : "+r" (idx), "+r" (attr)
        :: "x0"
    );
}

/*
 *  ======== Mmu_setTCR ========
 */
Void Mmu_setTCR(UInt64 tcr)
{
    __asm__ __volatile__ (
        "msr TCR_EL1, %0"
        :: "r" (tcr)
        :
    );
}

/*
 *  ======== Mmu_startup ========
 */
Void Mmu_startup()
{
    UInt64 tcr = 0;
    UInt i, tableLen = Mmu_configInfo.tableLength;

    /* Initialize MAIR */
    Mmu_setMAIR(0, Mmu_MAIR0);
    Mmu_setMAIR(1, Mmu_MAIR1);
    Mmu_setMAIR(2, Mmu_MAIR2);
    Mmu_setMAIR(3, Mmu_MAIR3);
    Mmu_setMAIR(4, Mmu_MAIR4);
    Mmu_setMAIR(5, Mmu_MAIR5);
    Mmu_setMAIR(6, Mmu_MAIR6);
    Mmu_setMAIR(7, Mmu_MAIR7);

    if (Mmu_granuleSize == Mmu_GranuleSize_4KB) {
        tcr = Mmu_GRANULE_SIZE_4KB;
    }
    else if (Mmu_granuleSize == Mmu_GranuleSize_16KB) {
        tcr = Mmu_GRANULE_SIZE_16KB;
    }
    else if (Mmu_granuleSize == Mmu_GranuleSize_64KB) {
        tcr = Mmu_GRANULE_SIZE_64KB;
    }

    /*
     * TCR config:
     *  - MMU tables reside in outer and inner write-back write-allocate
     *    cacheable memory
     *  - Physical address size is 48-bits wide
     *  - TTBR0 is used for translating VA 0 to (2^48 - 1)
     */
    tcr = tcr | ((UInt64)Mmu_PA_SIZE_ENCODING << 32) | Mmu_OUTER_SHAREABLE |
          Mmu_OUTER_CACHEABLE | Mmu_INNER_CACHEABLE | (64 - Mmu_PA_MAX_WIDTH);

    Mmu_setTCR(tcr);

    /* Initialize table array */
    for (i = 0; i < Mmu_tableArrayLen; i++) {
        Mmu_tableArray[tableLen * i] = i + 1;
    }
    Mmu_tableArray[tableLen * (i - 1)] = (~0);
    Mmu_tableArraySlot = 0;

    /* Allocate level1 Table */
    Mmu_level1Table = Mmu_allocTable();
    Mmu_init(Mmu_level1Table);

    /*
     * Call init function. This function is part of the application and will
     * add MMU mappings.
     */
    Mmu_initFunc();

    /* Invalidate entire TLB */
    Mmu_tlbInvAll();
    
    if (Mmu_enableMMU) {
        Mmu_enableI();
    }
}

/*
 *  ======== Mmu_tableWalk ========
 */
Bool Mmu_tableWalk(UInt8 level, UInt64 *tablePtr, UInt64 *vaddr, UInt64 *paddr,
    SizeT *size, Mmu_MapAttrs *mapAttrs)
{
    UInt64 desc;
    UInt16 tableIdx;
    SizeT  blockSize;
    Bool   retStatus;
    Bool   blockTranslation;
    UInt64 *nextLevelTablePtr;

    blockTranslation = TRUE;
    blockSize = 1 << Mmu_configInfo.tableOffset[level];
    if ((level == 0) ||
       ((level == 1) && (Mmu_granuleSize != Mmu_GranuleSize_4KB))) {
        blockTranslation = FALSE;
    }

    tableIdx = (*vaddr >> Mmu_configInfo.tableOffset[level]) &
        Mmu_configInfo.indexMask;

    while ((*size != 0) && (tableIdx < Mmu_configInfo.tableLength)) {
        desc = tablePtr[tableIdx];

        if (((desc & 0x3) == Mmu_DescriptorType_TABLE) && (level != 3)) {
            if ((blockTranslation == TRUE) && (*size >= blockSize) &&
                (*vaddr & (blockSize - 1) == 0)) {
                Mmu_addBlockEntry(level, tablePtr, tableIdx, *paddr, mapAttrs);
                *size = *size - blockSize;
                *vaddr = *vaddr + blockSize;
                *paddr = *paddr + blockSize;
                Mmu_freeTable((UInt64 *)(Mmu_PADDR_MASK & desc &
                    ~(UInt64)(Mmu_granuleSize - 1)));
            }
            else {
                nextLevelTablePtr = (UInt64 *)(Mmu_PADDR_MASK & desc &
                    ~(UInt64)(Mmu_granuleSize - 1));
                retStatus = Mmu_tableWalk(level + 1, nextLevelTablePtr,
                    vaddr, paddr, size, mapAttrs);
                if (!retStatus) {
                    return (FALSE);
                }
            }
        }
        else if (((desc & 0x3) != Mmu_DescriptorType_TABLE) || (level == 3)) {
            if ((level == 0) || ((level < 3) && (*size < blockSize)) ||
               ((*size >= blockSize) && ((*vaddr & (blockSize - 1)) != 0))) {
                UInt64 vaddrCopy = (*vaddr & (~(blockSize - 1)));
                UInt64 paddrCopy;
                Mmu_MapAttrs mapAttrsCopy;
                SizeT sizeCopy = blockSize;

                if ((desc & 0x3) == Mmu_DescriptorType_BLOCK) {
                    Mmu_readBlockEntry(level, tablePtr, tableIdx, &paddrCopy,
                        &mapAttrsCopy);
                }

                nextLevelTablePtr =
                    Mmu_addTableEntry(tablePtr, tableIdx, mapAttrs);
                if (nextLevelTablePtr == NULL) {
                    return (FALSE);
                }

                if ((desc & 0x3) == Mmu_DescriptorType_BLOCK) {
                    /*
                     * If old entry is a block entry, a new table entry is
                     * added and merged with the old block entry.
                     */
                    Mmu_tableWalk(level + 1, nextLevelTablePtr, &vaddrCopy,
                        &paddrCopy, &sizeCopy, &mapAttrsCopy);
                }

                retStatus = Mmu_tableWalk(level + 1, nextLevelTablePtr,
                    vaddr, paddr, size, mapAttrs);
                if (!retStatus) {
                    return (FALSE);
                }
            }
            else if ((blockTranslation == TRUE) && (*size >= blockSize)) {
                Mmu_addBlockEntry(level, tablePtr, tableIdx, *paddr, mapAttrs);
                *size = *size - blockSize;
                *vaddr = *vaddr + blockSize;
                *paddr = *paddr + blockSize;
            }
        }

        tableIdx++;
    }

    return (TRUE);
}

/*
 *  ======== Mmu_tlbInvAll ========
 */
Void Mmu_tlbInvAll()
{
    __asm__ __volatile__ (
        "tlbi vmalle1 \n\t"
        "dsb sy \n\t"
        "isb"
        ::: "memory"
    );
}

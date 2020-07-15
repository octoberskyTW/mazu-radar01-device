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
 *  ======== Mmu.xdc ========
 */

package ti.sysbios.family.arm.v8a;

/*!
 *  ======== Mmu ========
 *  Memory Management Unit (MMU) Manager
 *
 *  This module allows the ARM processor to map a 64-bit virtual address
 *  to a 48-bit physical address and enable/disable the MMU. It does this
 *  through translation tables in memory.
 *
 *  Every application must register a Mmu init function that contains calls
 *  to Mmu_map() to configure the MMU.
 *
 *  *.cfg:
 *  @p(code)
 *  var Mmu = xdc.useModule('ti.sysbios.family.arm.v8a.Mmu');
 *  Mmu.initFunc = "&InitMmu";
 *  @p
 *
 *  Example InitMmu() function for evmAM6x devices:
 *  @p(code)
 *  ...
 *
 *  Void InitMmu()
 *  {
 *      Bool ret;
 *      Mmu_MapAttrs attrs;
 *
 *      Mmu_initMapAttrs(&attrs);
 *
 *      // MAIR0 has a default memory type that is non-gathering and
 *      // non-reordering with no early write acknowledegement property.
 *      // In other words, strongly ordered memory type.
 *      attrs.attrIndx = Mmu_AttrIndx_MAIR0;
 *
 *      // Map GICv3 registers
 *      ret = Mmu_map(0x01800000, 0x01800000, 0x00100000, &attrs);
 *      if (!ret) {
 *          goto fail;
 *      }
 *
 *      // Map DMTimer registers
 *      ret = Mmu_map(0x02400000, 0x02400000, 0x000c0000, &attrs);
 *      if (!ret) {
 *          goto fail;
 *      }
 *
 *      // Map UART registers
 *      ret = Mmu_map(0x02800000, 0x02800000, 0x00001000, &attrs);
 *      if (!ret) {
 *          goto fail;
 *      }
 *
 *      // MAIR7 has a default attribute type of Inner and Outer
 *      // write-back cacheable
 *      attrs.attrIndx = Mmu_AttrIndx_MAIR7;
 *
 *      //Map MSMC SRAM
 *      ret = Mmu_map(0x70000000, 0x70000000, 0x00200000, &attrs);
 *      if (!ret) {
 *          goto fail;
 *      }
 *
 *      return;
 *  fail:
 *      System_printf("Mmu config failed.\n");
 *      while (1);
 *  }
 *
 *  @p
 */

@DirectCall
@Template ("./Mmu.xdt")

module Mmu
{
    const UInt8 PA_MAX_WIDTH = 48;

    /*
     * Default: 48-bits, 256TB
     */
    const UInt8 PA_SIZE_ENCODING = 0x5;

    // -------- ROV views --------

    //TBD

    /*!
     *  ======== AttrIndx ========
     *  Memory attribute register (MAIR) index
     *
     *  SYS/BIOS defines default values for MAIR register. See {@link #MAIR0},
     *  {@link #MAIR1}, {@link #MAIR2}, {@link #MAIR3}, {@link #MAIR4},
     *  {@link #MAIR5}, {@link #MAIR6} & {@link #MAIR7} for more info on the
     *  memory type defined by each MAIR register.
     */
    enum AttrIndx {
        AttrIndx_MAIR0 = 0,
        AttrIndx_MAIR1,
        AttrIndx_MAIR2,
        AttrIndx_MAIR3,
        AttrIndx_MAIR4,
        AttrIndx_MAIR5,
        AttrIndx_MAIR6,
        AttrIndx_MAIR7
    };

    /*!
     *  @_nodoc
     *  ======== DescriptorType ========
     *  Different descriptor type encodings:
     *  @p(blist)
     *  - Invalid or Fault entry (0b00 or 0b10)
     *  - Block descriptor entry (0b01)
     *  - Table descriptor entry (0b11)
     *  @p
     */
    enum DescriptorType {
        DescriptorType_INVALID0 = 0,   /*! Virtual address is unmapped     */
        DescriptorType_BLOCK = 1,      /*! Block descriptor                */
        DescriptorType_INVALID1 = 2,   /*! Virtual address is unmapped     */
        DescriptorType_TABLE = 3       /*! Next-level table address        */
    };

    /*!
     *  ======== GranuleSize ========
     *  Memory translation {@link #granuleSize} granule size
     */
    enum GranuleSize {
        GranuleSize_4KB = 0x1000,
        GranuleSize_16KB = 0x4000,
        GranuleSize_64KB = 0x10000
    };

    /*!
     *  ======== Shareable ========
     *  Shareability attribute
     */
    enum Shareable {
        Shareable_NONE = 0x0,
        Shareable_OUTER = 0x2,
        Shareable_INNER = 0x3
    };

    /*!
     *  ======== AccessPerm ========
     *  Access Permissions
     */
    enum AccessPerm {
        AccessPerm_PRIV_RW_USER_NONE = 0x0, /* Privileged Read/write (EL1),
                                               User no access (EL0) */
        AccessPerm_PRIV_RW_USER_RW = 0x1,   /* Privileged Read/write (EL1),
                                               User Read/write (EL0) */
        AccessPerm_PRIV_RO_USER_NONE = 0x2, /* Privileged Read only (EL1),
                                               User no access (EL0) */
        AccessPerm_PRIV_RO_USER_RO = 0x3    /* Privileged Read only (EL1),
                                               User Read only (EL0) */
    };

    /*! Mmu init function type definition. */
    typedef Void (*InitFuncPtr)(void);

    /*!
     *  ======== MapAttrs ========
     *  Structure containing attributes for memory map entry
     */
    struct MapAttrs {
        AccessPerm accessPerm;      /*! privileged & user access permissions  */
        Bool       privExecute;     /*! privileged execute permission         */
        Bool       userExecute;     /*! user execute permission               */
        Shareable  shareable;       /*! shareability field value 0-3          */
        AttrIndx   attrIndx;        /*! stage 1 memory attributes index field
                                        for the indicated MAIRn reg value 0-7 */
        Bool       global;          /*! global mmu entry ? (used by kernel
                                        when memory protection extensions are
                                        enabled)                              */
    };

    // Asserts

    /*!
     *  ======== A_nullPointer ========
     *  Assert raised when a pointer is null
     */
    config xdc.runtime.Assert.Id A_nullPointer  = {
        msg: "A_nullPointer: Pointer is null"
    };

    /*!
     *  ======== A_vaddrOutOfRange ========
     *  Assert raised when virtual address passed is out of range
     */
    config xdc.runtime.Assert.Id A_vaddrOutOfRange  = {
        msg: "A_vaddrOutOfRange: Virtual address is out of range"
    };

    /*!
     *  ======== A_paddrOutOfRange ========
     *  Assert raised when physical address passed is out of range
     */
    config xdc.runtime.Assert.Id A_paddrOutOfRange  = {
        msg: "A_paddrOutOfRange: Physical address is out of range"
    };

    /*!
     *  ======== A_unalignedVaddr ========
     *  Assert raised if unaligned virtual address passed to Mmu_map().
     */
    config xdc.runtime.Assert.Id A_unalignedVaddr =
        {msg: "A_unalignedVaddr: Virtual address not page aligned"};

    /*!
     *  ======== A_unalignedPaddr ========
     *  Assert raised if unaligned physical address passed to Mmu_map().
     */

    config xdc.runtime.Assert.Id A_unalignedPaddr =
        {msg: "A_unalignedPaddr: Physical address not page aligned"};

    /*!
     *  ======== A_unalignedSize ========
     *  Assert raised if unaligned size passed to Mmu_map().
     */
    config xdc.runtime.Assert.Id A_unalignedSize =
        {msg: "A_unalignedSize: Mmu mapping size not page aligned"};

    /*!
     *  ======== defaultMapAttrs ========
     *  default descriptor attributes structure
     */
    config MapAttrs defaultMapAttrs = {
        accessPerm: AccessPerm_PRIV_RW_USER_NONE,
        privExecute: true,
        userExecute: false,
        shareable: Shareable_OUTER,
        attrIndx: AttrIndx_MAIR0,
        global: true
    };

    /*!
     *  ======== enableMMU ========
     *  Configuration parameter to enable MMU.
     */
    config Bool enableMMU = true;

    /*!
     *  ======== granuleSize ========
     *  Memory translation granule size. Default is 4KB.
     *
     *  The granule size determines the smallest page size that can be
     *  mapped with the MMU.
     */
    config GranuleSize granuleSize = GranuleSize_4KB;

    /*!
     *  ======== MAIR0 ========
     *  Memory attribute 0.
     *
     *  Default is memory with non-gathering, non-reordering and no early write
     *  acknowledegement property.
     */
    config UInt8 MAIR0 = 0x00;

    /*!
     *  ======== MAIR1 ========
     *  Memory attribute 1
     *
     *  Default is memory with non-gathering, non-reordering and early write
     *  acknowledegement property.
     */
    config UInt8 MAIR1 = 0x04;

    /*!
     *  ======== MAIR2 ========
     *  Memory attribute 2
     *
     *  Default is memory with non-gathering, reordering and early write
     *  acknowledegement property.
     */
    config UInt8 MAIR2 = 0x08;

    /*!
     *  ======== MAIR3 ========
     *  Memory attribute 3
     *
     *  Default is memory with gathering, reordering and early write
     *  acknowledegement property.
     */
    config UInt8 MAIR3 = 0x0C;

    /*!
     *  ======== MAIR4 ========
     *  Memory attribute 4
     *
     *  Default is normal inner & outer non-cacheable memory.
     */
    config UInt8 MAIR4 = 0x44;

    /*!
     *  ======== MAIR5 ========
     *  Memory attribute 5
     *
     *  Default is normal outer non-cacheable, inner write-back cacheable
     *  non-transient memory.
     */
    config UInt8 MAIR5 = 0x4F;

    /*!
     *  ======== MAIR6 ========
     *  Memory attribute 6
     *
     *  Default is normal outer & inner write-through cacheable non-transient
     *  memory.
     */
    config UInt8 MAIR6 = 0xBB;

    /*!
     *  ======== MAIR7 ========
     *  Memory attribute 7
     *
     *  Default is normal outer and inner write-back cacheable non-transient
     *  memory.
     */
    config UInt8 MAIR7 = 0xFF;

    /*!
     *  ======== initFunc ========
     *  MMU init function pointer
     *
     *  This config param is initialized to point to an init function that
     *  will perform MMU configuration using the {@link #map} runtime APIs
     *  provided by this module. The init function is called before
     *  C initialization i.e. before the data section is initialized.
     *  Therefore, care must be taken to not rely on any initialized
     *  data variables.
     */
    config InitFuncPtr initFunc = null;

    /*!
     *  ======== tableArraySection ========
     *  Contains a table array and some state variables.
     *  This section is uninitialized.
     *
     *  Note: Memory containing the table array must be marked as inner &
     *  and outer shareable, and inner and outer write-back write-allocate
     *  cacheable.
     */
    metaonly config String tableArraySection =
        ".data.ti_sysbios_family_arm_v8a_Mmu_tableArray";

    /*!
     *  ======== tableArrayLen ========
     *  Length of array of MMU tables
     *
     *  MMU module allocates memory for MMU table from a table array.
     *  This config param controls number of MMU tables supported.
     *  Each table in the array is the size of the MMU table and aligned
     *  to the table's size.
     *
     *  @a(Note)
     *  MMU table size is same as translation granule size (see
     *  {@link #granuleSize})
     */
    config UInt tableArrayLen = 16;

    /*!
     *  ======== enable ========
     *  Enables the MMU.
     *
     *  If the MMU is already enabled, then simply return.
     *  Otherwise this function does the following:
     *  @p(blist)
     *  If the L1 program cache is enabled, invalidate all of L1
     *  program cache.
     *  @p
     *
     *  This function enables the MMU on the core it is called from.
     *
     *  @a(Note)
     *  This function does not change the L1 data/program cache settings.
     */
    Void enable();

    /*!
     *  ======== initMapAttrs() ========
     *  Initializes the map attribute structure
     *
     *  @param(attrs)      Pointer to map attribute struct
     */
    Void initMapAttrs(MapAttrs *descAttrs);

    /*!
     *  ======== isEnabled ========
     *  Determines if the MMU is enabled
     */
    Bool isEnabled();

    /*!
     *  ======== map ========
     *  Add a mapping to MMU table
     *
     *  This API adds a mapping for the given virtual and physical
     *  address to the MMU table and sets the memory attributes
     *  as per the attributes passed to the function.
     *
     *  This API internally disables interrupts before updating the
     *  MMU table. The interrupts may be disabled for a long period
     *  of time. It is therefore recommended to either call this
     *  API in the Mmu.initFunc or in main().
     *
     *  The smallest mapping size (page size) supported is determined
     *  by the {@link #granuleSize}. The largess mapping size supported
     *  is 2^{@link #PA_MAX_WIDTH}-1.
     *
     *  @param(vaddr)         Virtual address (aligned to {@link #granuleSize})
     *  @param(paddr)         Physical address (aligned to {@link #granuleSize})
     *  @param(size)          Region size (aligned to {@link #granuleSize})
     *  @param(attrs)         Memory region attributes
     *  @b(returns)           Status (True-success, False-failed)
     */
    Bool map(UInt64 vaddr, UInt64 paddr, SizeT size, MapAttrs *attrs);

    /*!
     *  ======== setMAIR ========
     *  Sets the memory attribute encoding in the MAIRn register.
     *
     *  MAIR provides the memory attribute encodings to the possible
     *  {@link #DescriptorAttrs attrIndx} values in a long-descriptor format
     *  translation table entry for stage 1 translations.
     *
     *  {@link #DescriptorAttrs attrIndx}[2:0] selects the ATTRn bit-field in
     *  the MAIR register.
     *
     *  Memory Attribute Indirection Register (MAIR) bit assignments:
     *  @p(code)
     *         --------------------------------------------------------------
     *        |63     |    56|55     |     48|47     |     40|39     |     32|
     *         --------------------------------------------------------------
     *  MAIR  |     ATTR7    |     ATTR6     |     ATTR5     |     ATTR4     |
     *         --------------------------------------------------------------
     *        |31     |    24|23     |     16|15     |      8|7      |      0|
     *         --------------------------------------------------------------
     *  MAIR  |     ATTR3    |     ATTR2     |     ATTR1     |     ATTR0     |
     *         --------------------------------------------------------------
     *  @p
     *
     *  SYS/BIOS has 8 MAIR config params (MAIR0, MAIR2, ...) that are
     *  initialized to default value. In order to have a custom memory
     *  attribute, a user can either change the MAIRn config param in
     *  the application's cfg script or call this runtime API.
     *
     *  For more details on MAIR encodings please refer
     *  {@link https://developer.arm.com/docs/ddi0487/latest/arm-architecture-reference-manual-armv8-for-armv8-a-architecture-profile v8A ARM Architecture Reference Manual}
     *
     *  @param(attrIndx)     Memory attribute index
     *  @param(attr)         Memory attribute encoding
     *
     *  @a(Note)
     *  This function only invalidates the TLB and does not flush the cache.
     *  If the cacheability attribute of a region of memory is changed by
     *  modifying the MAIR entry for the region, the application needs to
     *  flush and invalidate the region of memory from the cache.
     */
    Void setMAIR(UInt8 attrIndx, UInt8 attr);

    /*!
     *  @_nodoc
     *  ======== startup ========
     *  startup function to initialize MMU module
     */
    Void startup();

    /*!
     *  ======== tlbInvAll ========
     *  Invalidate entire TLB (both data and instruction)
     */
    Void tlbInvAll();

internal:

    /*
     *  ======== ConfigInfo ========
     */
    struct ConfigInfo {
        UInt64 indexMask;
        UInt32 tableLength;
        UInt8  tableOffset[4];
        UInt8  granuleSizeBits;
        UInt8  indexBits;
        Bool   noLevel0Table;
    };

    /*
     *  ======== disable ========
     */
    Void disable();

    /*
     *  ======== disableI ========
     */
    Void disableI();

    /*
     *  ======== enableI ========
     */
    Void enableI();

    /*
     *  ======== configInfo ========
     *  This is a const object that contains pre-initialized config info
     *  about the MMU. Goal is to save some computation time at runtime
     *  for config info that can be pre-computed.
     */
    config ConfigInfo configInfo;

    /*
     *  ======== addBlockEntry ========
     */
    Void addBlockEntry(UInt8 level, UInt64 *tablePtr, UInt16 tableIdx,
        UInt64 paddr, MapAttrs *attrs);

    /*
     *  ======== addTableEntry ========
     */
    UInt64* addTableEntry(UInt64 *tablePtr, UInt16 tableIdx, MapAttrs *attrs);

    /*
     *  ======== allocTable ========
     */
    UInt64* allocTable();

    /*
     *  ======== freeTable ========
     */
    Void freeTable(UInt64 *table);

    /*
     *  ======== init ========
     */
    Void init(Ptr tableAddr);

    /*
     *  ======== readBlockEntry ========
     */
    Void readBlockEntry(UInt8 level, UInt64 *tablePtr, UInt16 tableIdx,
        UInt64 *paddr, MapAttrs *attrs);

    /*
     *  ======== setMAIRAsm ========
     */
    Void setMAIRAsm(UInt8 attrIndx, UInt8 attr);

    /*
     *  ======== tableWalk ========
     */
    Bool tableWalk(UInt8 level, UInt64 *tablePtr, UInt64 *vaddr, UInt64 *paddr,
        SizeT *size, MapAttrs *attrs);

    /*
     *  ======== setTCR ========
     */
    Void setTCR(UInt64 regVal);

    /*! Module state */
    struct Module_State {
    }
}

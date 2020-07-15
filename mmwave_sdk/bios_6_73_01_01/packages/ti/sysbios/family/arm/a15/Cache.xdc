/*
 * Copyright (c) 2015, Texas Instruments Incorporated
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
 *  ======== Cache.xdc ========
 */

package ti.sysbios.family.arm.a15;

import xdc.rov.ViewInfo;

import xdc.runtime.Assert;

/*!
 *  ======== Cache ========
 *  ARM Cache Module
 *
 *  This module manages the data and instruction caches on Cortex A15
 *  processors.
 *  It provides a list of functions that perform cache operations.  The
 *  functions operate on a per cache line except for the 'All' functions
 *  which operate on the entire cache specified.  Any Address that is not
 *  aligned to a cache line gets rounded down to the address of
 *  the nearest cache line.
 *
 *  The L1 data and program caches as well as the L2 cache are enabled
 *  by default early during the startup sequence (prior to any
 *  Module_startup()s).
 *  Data caching requires the MMU to be enabled and the cacheable
 *  attribute of the section/page descriptor for a corresponding
 *  memory region to be enabled.
 *  Program caching does not require the MMU to be enabled and therefore
 *  occurs when the L1 program cache is enabled.
 *
 *  (See the {@link ti.sysbios.family.arm.a15.Mmu} module for information
 *   about the MMU.)
 *
 *  Note: The invalidate instruction is treated by A15 as a clean/invalidate
 *  instruction. Therefore, calls to Cache_inv()/Cache_invAll() will behave
 *  like Cache_wbInv()/Cache_wbInvAll() on A15.
 *
 *  Unconstrained Functions
 *  All functions
 *
 *  @p(html)
 *  <h3> Calling Context </h3>
 *  <table border="1" cellpadding="3">
 *    <colgroup span="1"></colgroup> <colgroup span="5" align="center">
 *    </colgroup>
 *
 *    <tr><th> Function                 </th><th>  Hwi   </th><th>  Swi   </th>
 *    <th>  Task  </th><th>  Main  </th><th>  Startup  </th></tr>
 *    <!--                               -->
 *    <tr><td> {@link #disable}     </td><td>   Y    </td><td>   Y    </td>
 *    <td>   Y    </td><td>   Y    </td><td>   Y    </td></tr>
 *    <tr><td> {@link #enable}      </td><td>   Y    </td><td>   Y    </td>
 *    <td>   Y    </td><td>   Y    </td><td>   Y    </td></tr>
 *    <tr><td> {@link #inv}         </td><td>   Y    </td><td>   Y    </td>
 *    <td>   Y    </td><td>   Y    </td><td>   Y    </td></tr>
 *    <tr><td> {@link #invL1dAll}   </td><td>   Y    </td><td>   Y    </td>
 *    <td>   Y    </td><td>   Y    </td><td>   Y    </td></tr>
 *    <tr><td> {@link #invL1pAll}   </td><td>   Y    </td><td>   Y    </td>
 *    <td>   Y    </td><td>   Y    </td><td>   Y    </td></tr>
 *    <tr><td> {@link #wait}        </td><td>   Y    </td><td>   Y    </td>
 *    <td>   Y    </td><td>   Y    </td><td>   Y    </td></tr>
 *    <tr><td> {@link #wb}          </td><td>   Y    </td><td>   Y    </td>
 *    <td>   Y    </td><td>   Y    </td><td>   Y    </td></tr>
 *    <tr><td> {@link #wbInv}       </td><td>   Y    </td><td>   Y    </td>
 *    <td>   Y    </td><td>   Y    </td><td>   Y    </td></tr>
 *    <tr><td> {@link #wbInvL1dAll} </td><td>   Y    </td><td>   Y    </td>
 *    <td>   Y    </td><td>   Y    </td><td>   Y    </td></tr>
 *    <tr><td> {@link #wbL1dAll}    </td><td>   Y    </td><td>   Y    </td>
 *    <td>   Y    </td><td>   Y    </td><td>   Y    </td></tr>
 *    <tr><td> {@link #load}       </td><td>   Y    </td><td>   Y     </td>
 *    <td>   Y    </td><td>   Y    </td><td>   Y    </td></tr>
 *    <tr><td colspan="6"> Definitions: <br />
 *       <ul>
 *         <li> <b>Hwi</b>: API is callable from a Hwi thread. </li>
 *         <li> <b>Swi</b>: API is callable from a Swi thread. </li>
 *         <li> <b>Task</b>: API is callable from a Task thread. </li>
 *         <li> <b>Main</b>: API is callable during any of these phases: </li>
 *           <ul>
 *             <li> In your module startup after this module is started
 *   (e.g. Cache_Module_startupDone() returns TRUE). </li>
 *             <li> During xdc.runtime.Startup.lastFxns. </li>
 *             <li> During main().</li>
 *             <li> During BIOS.startupFxns.</li>
 *           </ul>
 *         <li> <b>Startup</b>: API is callable during any of these phases:</li>
 *           <ul>
 *             <li> During xdc.runtime.Startup.firstFxns.</li>
 *             <li> In your module startup before this module is started
 *   (e.g. Cache_Module_startupDone() returns FALSE).</li>
 *           </ul>
 *       </ul>
 *    </td></tr>
 *
 *  </table>
 *  @p
 */

module Cache inherits ti.sysbios.interfaces.ICache
{
    /*!
     *  Size of L1 data cache Line in bytes
     */
    const UInt sizeL1dCacheLine = 64;

    /*!
     *  Size of L1 program cache Line in bytes
     */
    const UInt sizeL1pCacheLine = 64;

    /*!
     *  Size of L2 cache Line in bytes
     */
    const UInt sizeL2CacheLine = 64;

    /*!
     *  ======== ModView ========
     *  @_nodoc
     */
    metaonly struct CacheInfoView {
        String      cache;
        SizeT       cacheSize;
        SizeT       lineSize;
        UInt        ways;
        SizeT       waySize;
    };

    /*!
     *  ======== rovViewInfo ========
     *  @_nodoc
     */
    @Facet
    metaonly config ViewInfo.Instance rovViewInfo =
        ViewInfo.create({
            viewMap: [
                ['Cache Info',  { type: ViewInfo.MODULE_DATA,
                                  viewInitFxn: 'viewInitCacheInfo',
                                  structName: 'CacheInfoView'}]
            ]
        });

    /*! Asserted in Cache_lock */
    config Assert.Id A_badBlockLength = {
        msg: "A_badBlockLength: Block length too large. Must be <= L2 way size."
    };

    /*! Asserted in Cache_lock */
    config Assert.Id A_blockCrossesPage = {
        msg: "A_blockCrossesPage: Memory block crosses L2 way page boundary."
    };

    /*!
     *  Enable L1 and L2 data and program caches.
     *
     *  To enable a subset of the caches, set this parameter
     *  to 'false' and call Cache_enable() within main, passing it only
     *  the {@link Cache#Type Cache_Type(s)} to be enabled.
     *
     *  Data caching requires the MMU and the memory section/page
     *  descriptor cacheable attribute to be enabled.
     */
    config Bool enableCache = true;

    /*!
     *  ======== errata798870 ========
     *  Enable workaround for ARM errata 798870.
     *
     *  Errata 798870 brief description:
     *  A memory read can stall indefinitely in the L2 cache
     */
    config Bool errata798870 = false;

    /*!
     *  Enable Branch Prediction at startup, default is true.
     *
     *  This flag controls whether Branch Prediction should be automatically
     *  enabled or disabled during system startup.
     *
     *  @a(NOTE)
     *  Upon reset, the A15's Program Flow Prediction (Branch Prediction)
     *  feature is disabled.
     */
    config Bool branchPredictionEnabled = true;

    /*! @_nodoc
     *  ======== getEnabled ========
     *  Get the 'type' bitmask of cache(s) enabled.
     */
    Bits16 getEnabled();

    /*!
     *  ======== invL1dAll ========
     *  Invalidate all of L1 data cache.
     *
     *  This function should be used with caution.  In general, the
     *  L1 data cache may contain some stack variable or valid data
     *  that should not be invalidated.  This function should be used
     *  only when all contents of L1 data cache is unwanted.
     */
    Void invL1dAll();

    /*!
     *  ======== invL1pAll ========
     *  Invalidate all of L1 program cache.
     */
    Void invL1pAll();

    /*!
     *  ======== preLoad ========
     *  Loads a memory block into the L2 cache.
     *
     *  A block of memory is loaded into the L2 cache.
     *
     *  The memory block is loaded into cache one L2 cache line at time.
     *
     *  The byteCnt argument must be less than or equal to an L2 cache
     *  size. An assert is generated if this rule is violated.
     *
     *  Except for the normal L1 instruction cache behavior
     *  during code execution, the L1 instruction cache is
     *  unaffected by this API.
     *  The L1 data cache will be temporarily polluted by the contents
     *  of the referenced memory block.
     *
     *  @a(NOTE)
     *  Interrupts are disabled for the entire time the memory block
     *  is being loaded into cache. For this reason, use of this API
     *  is probably best at system intialization time
     *  (ie: within 'main()').
     *
     *  @param(blockPtr) start address of range to be loaded
     *  @param(byteCnt)  number of bytes to be loaded
     */
    Void preLoad(Ptr blockPtr, SizeT byteCnt);

    /*!
     *  ======== enableBP ========
     *  Enable Branch Prediction
     *
     *  Calling this API will enable branch prediction.
     *
     *  @a(NOTE)
     *  Upon reset, the A15's Program Flow Prediction (Branch Prediction)
     *  feature is disabled.
     */
    Void enableBP();

    /*!
     *  ======== disableBP ========
     *  Disable Branch Prediction
     *
     *  Calling this API will disable branch prediction.
     *
     *  @a(NOTE)
     *  Upon reset, the A15's Program Flow Prediction (Branch Prediction)
     *  feature is disabled.
     */
    Void disableBP();

    /*!
     *  @_nodoc
     *  ======== wbAllLoUIS ========
     *  Write back all caches to PoU for an Inner Shareable domain
     *
     *  This function writes back the data cache. There is no effect
     *  on program cache. All data cache lines are left valid.
     *
     *  On Cortex-A15, this function will write back the local CPU's
     *  L1 data cache. This API should be called with Hwis and/or Tasking
     *  disabled to guarantee the write back operation is complete.
     */
    Void wbAllLoUIS();

    /*!
     *  @_nodoc
     *  ======== wbInvAllLoUIS ========
     *  Write back invalidate all caches to PoU for an Inner Shareable domain
     *
     *  On Cortex-A15, this function will write back and invalidate the local
     *  CPU's L1 data cache. This API should be called with Hwis and/or Tasking
     *  disabled to guarantee the write back invalidate operation is complete.
     */
    Void wbInvAllLoUIS();

    /*!
     *  ======== invBPAll ========
     *  Invalidate all branch predictors
     *
     *  Invalidates all branch predictors on this core. If running in SMP mode,
     *  this operation is broadcast to all other cores.
     */
    Void invBPAll();

internal:

    /*
     *  ======== initModuleState ========
     *  Initializes the module state.
     *
     *  This function initializes module state fields like
     *  L1/L2 cache size and number of cache lines/sets. It
     *  is registered as a first function.
     */
    Void initModuleState();

    /*
     *  ======== startup ========
     *  startup function to enable cache early during climb-up
     */
    Void startup();

    /*
     *  ======== disableL1D ========
     *  Disable data cache
     *
     *  This function disables the L1 data cache before performing
     *  a "write back invalidate all" of data and instruction caches.
     *
     *  The L2 unified cache cannot be disabled on Cortex-A15.
     *  Disabling the L1 data cache effectively disables the L2 unified
     *  cache for all data caching purposes (on the current core in a
     *  Cortex-A15 multi-core system).
     */
    Void disableL1D();

    /*
     *  ======== disableL1P ========
     *  Disable instruction cache
     *
     *  This function disables the L1 instruction cache before
     *  performing a "invalidate all" of the whole instruction
     *  cache.
     *
     *  The L2 unified cache cannot be disabled on Cortex-A15.
     *  Disabling the L1 instruction cache effectively disables the
     *  L2 unified cache for all instruction caching purposes (on
     *  the current core in a Cortex-A15 multi-core system).
     */
    Void disableL1P();

    /*
     *  ======== enableL1D ========
     *  Enable data cache.
     *
     *  This function enables the L1 data cache.
     *
     *  Enabling the L1 data cache effectively enables the L2 unified
     *  cache for all data caching purposes (on the current core in a
     *  Cortex-A15 multi-core system).
     */
    Void enableL1D();

    /*
     *  ======== enableL1P ========
     *  Enable instruction cache.
     *
     *  This function enables the L1 instruction cache.
     *
     *  Enabling the L1 instruction cache effectively enables the
     *  L2 unified cache for all instruction caching purposes (on
     *  the current core in a Cortex-A15 multi-core system).
     *
     *  If the MMU is disabled and the L1 instruction cache is enabled,
     *  no new instructions will be cached in the L2 unified cache.
     *  However, code already cached in the L2 cache will be fetched.
     */
    Void enableL1P();

    /*
     *  ======== invL1d ========
     *  Invalidates range in L1 data cache.
     */
    Void invL1d(Ptr blockPtr, SizeT byteCnt, Bool wait);

    /*
     *  ======== invL1p ========
     *  Invalidates range in L1 program cache.
     */
    Void invL1p(Ptr blockPtr, SizeT byteCnt, Bool wait);

    /*
     *  ======== preFetch ========
     *  load a block of memory into the L2 cache.
     */
    Void preFetch(Ptr blockPtr, SizeT byteCnt);

    /*!
     *  ======== getL2AuxControlReg ========
     *  Get current L2 Aux Control register contents
     */
    Bits32 getL2AuxControlReg();

    /*
     *  ======== setL2AuxControlReg ========
     *  Write to L2ACTLR using ROM API
     *
     *  Note: This API is only for OMAP5 and J6 devices as Keystone 2
     *  devices do not support the same ROM API interface.
     */
    Void setL2AuxControlReg(Bits32 arg);

    /*
     *  ======== getCacheLevelInfo ========
     *  returns Cache Size Id Register of corresponding Cache level
     *
     *  level values
     *      0 = L1D
     *      1 = L1P
     *      2 = L2
     */
    Bits32 getCacheLevelInfo(UInt level);

    struct Module_State {
        Bits32  l1dInfo;
        Bits32  l1pInfo;
        Bits32  l2Info;
        SizeT   l2WaySize;
    }
}

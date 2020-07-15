/*
 * Copyright (c) 2017-2018, Texas Instruments Incorporated
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

package ti.sysbios.family.arm.v8a;

import xdc.rov.ViewInfo;

import xdc.runtime.Assert;

/*!
 *  ======== Cache ========
 *  ARM Cache Module
 *
 *  This module manages the data and instruction caches on ARMv8A
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
 *  (See the {@link ti.sysbios.family.arm.v8a.Mmu} module for information
 *   about the MMU.)
 *
 *  Note: The invalidate instruction is treated by A53/A57/A72 as a
 *  clean/invalidate instruction. Therefore, calls to Cache_inv()
 *  will behave like Cache_wbInv().
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
 *    <tr><td> {@link #invL1pAll}   </td><td>   Y    </td><td>   Y    </td>
 *    <td>   Y    </td><td>   Y    </td><td>   Y    </td></tr>
 *    <tr><td> {@link #wait}        </td><td>   Y    </td><td>   Y    </td>
 *    <td>   Y    </td><td>   Y    </td><td>   Y    </td></tr>
 *    <tr><td> {@link #wb}          </td><td>   Y    </td><td>   Y    </td>
 *    <td>   Y    </td><td>   Y    </td><td>   Y    </td></tr>
 *    <tr><td> {@link #wbAll}          </td><td>   Y    </td><td>   Y    </td>
 *    <td>   Y    </td><td>   Y    </td><td>   Y    </td></tr>
 *    <tr><td> {@link #wbInv}       </td><td>   Y    </td><td>   Y    </td>
 *    <td>   Y    </td><td>   Y    </td><td>   Y    </td></tr>
 *    <tr><td> {@link #wbInvAll}       </td><td>   Y    </td><td>   Y    </td>
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

@ModuleStartup

module Cache inherits ti.sysbios.interfaces.ICache
{
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

    /*! @_nodoc
     *  ======== getEnabled ========
     *  Get the 'type' bitmask of cache(s) enabled.
     */
    Bits16 getEnabled();

    /*!
     *  ======== invL1pAll ========
     *  Invalidate all of L1 program cache.
     */
    Void invL1pAll();

    /*!
     *  ======== wbAll ========
     *
     *  Performs a global write back by set/way of one or more levels of cache.
     *  The cache maintenance operations performed during this sequence are not
     *  broadcast to other CPUs within the same shareability domain. Unless all
     *  memory locations are regarded as non-cacheable on other CPUs, it is not
     *  possible to prevent locations from being allocated into the cache by
     *  other CPUs while this cache manintenance operation is in progress.
     */
    override Void wbAll();

    /*!
     *  ======== wbInvAll ========
     *
     *  Performs a global write back and invalidate by set/way of one or more
     *  levels of cache. The cache maintenance operations performed during this
     *  sequence are not broadcast to other CPUs within the same shareability
     *  domain. Unless all memory locations are regarded as non-cacheable by
     *  other CPUs, it is not possible to prevent locations from being
     *  allocated into the cache by other CPUs while this cache manintenance
     *  operation is in progress.
     */
    override Void wbInvAll();

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
     *  The L2 unified cache cannot be disabled on ARMv8A devices.
     *  Disabling the L1 data cache effectively disables the L2 unified
     *  cache for all data caching purposes (on the current core in a
     *  ARMv8A multi-core system).
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
     *  The L2 unified cache cannot be disabled on ARMv8A devices.
     *  Disabling the L1 instruction cache effectively disables the
     *  L2 unified cache for all instruction caching purposes (on
     *  the current core in a ARMv8A multi-core system).
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
     *  ARMv8A multi-core system).
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
     *  the current core in a ARMv8A multi-core system).
     *
     *  If the MMU is disabled and the L1 instruction cache is enabled,
     *  no new instructions will be cached in the L2 unified cache.
     *  However, code already cached in the L2 cache will be fetched.
     */
    Void enableL1P();

    /*
     *  ======== enableSmp ========
     *  Set CPUECTLR_EL1.SMPEN bit.
     */
    Void enableSmp();

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
    }
}

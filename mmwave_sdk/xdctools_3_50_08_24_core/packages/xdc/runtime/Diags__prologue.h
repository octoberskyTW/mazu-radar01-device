/* 
 *  Copyright (c) 2008-2017 Texas Instruments Incorporated
 *  This program and the accompanying materials are made available under the
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * */

#ifndef xdc_runtime_Diags__prologue__include
#define xdc_runtime_Diags__prologue__include

/*
 *  ======== Diags__prologue.h ========
 *
 *  This header defines Module__* symbols for every Module__* value used
 *  by the Diags module's headers.  This allows non-module code to
 *  use the Diags module.  These symbols are normally defined in
 *  module internal headers (i.e., package/internal/<mod>.xdc.h) and they
 *  define a "current module context".
 */
#include <xdc/runtime/Main.h>

/*
 * Only define these symbols for xdc.runtime.Main if this file is not one that
 * will be included in the Registry. This check ensures that Registry.h (which
 * similarly defines these Module__* symbols) can be included in any order
 * relative to other xdc.runtime headers.
 */
#ifndef Registry_CURDESC

/*
 *  ======== Module__DGSINCL ========
 *  The set of diags categories that are runtime controllable _or_ always on
 *
 *  This costant is computed at config time and enables us to eliminate
 *  expensive runtime time checks and unnecessary data (the module's diags
 *  mask) when whole program optimization is used.
 */
#undef Module__DGSINCL
#ifdef xdc_runtime_Main_Module__diagsIncluded__CR
#define Module__DGSINCL (*((CT__xdc_runtime_Main_Module__diagsIncluded*)(xdcRomConstPtr + xdc_runtime_Main_Module__diagsIncluded__R_offset)))
#else
#define Module__DGSINCL xdc_runtime_Main_Module__diagsIncluded__C
#endif

/*
 *  ======== Module__DGSENAB ========
 *  The set of diags categories that are _always_ enabled
 *
 *  This costant is computed at config time and enables us to eliminate
 *  expensive runtime time checks and unnecessary data (the module's diags
 *  mask) when whole program optimization is used.
 */
#undef Module__DGSENAB
#ifdef xdc_runtime_Main_Module__diagsEnabled__CR
#define Module__DGSENAB (*((CT__xdc_runtime_Main_Module__diagsEnabled*)(xdcRomConstPtr + xdc_runtime_Main_Module__diagsEnabled__R_offset)))
#else
#define Module__DGSENAB xdc_runtime_Main_Module__diagsEnabled__C
#endif

/*
 *  ======== Module__DGSMASK ========
 *  Pointer to the set of diags categories that are runtime controllable
 */
#undef Module__DGSMASK
#ifdef xdc_runtime_Main_Module__diagsMask__CR
#define Module__DGSMASK (*((CT__xdc_runtime_Main_Module__diagsMask*)(xdcRomConstPtr + xdc_runtime_Main_Module__diagsMask__R_offset)))
#else
#define Module__DGSMASK xdc_runtime_Main_Module__diagsMask__C
#endif

/*
 *  ======== Module__MID ========
 */
#undef Module__MID
#ifdef xdc_runtime_Main_Module__id__CR
#define Module__MID (*((CT__xdc_runtime_Main_Module__id*)(xdcRomConstPtr + xdc_runtime_Main_Module__id__R_offset)))
#else
#define Module__MID xdc_runtime_Main_Module__id__C
#endif

#endif
#endif
/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 7-31-2018 11:49:29; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


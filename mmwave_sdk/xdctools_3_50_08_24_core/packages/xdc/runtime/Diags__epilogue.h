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

#ifndef xdc_runtime_Diags__epilogue__include
#define xdc_runtime_Diags__epilogue__include

/*
 *  ======== xdc_runtime_Diags_query ========
 *  Returns true iff:
 *      1. the current module's included diags intersect evt's mask, and
 *      2. either the permanently enabled diags intersect evt's mask or
 *         the runtime controllable diags intersect evt's mask.
 *
 *  This macro relies on three "internal" macros which are defined in each
 *  module's internal header (e.g., package/internal/System.xdc.h):
 *      Module__DGSINCL - a const bit mask of bits that are _not_ ALWAYS_OFF
 *      Module__DGSENAB - a const bit mask of bits that are ALWAYS_ON
 *      Module__DGSMASK - a const pointer to a bit mask of currently enabled
 *                        diagnostics
 *  These macros reference module-specific variables generated at config
 *  time, when we know the value of these constants.
 *
 */
#define xdc_runtime_Diags_query(evt) \
    ((Module__DGSINCL & (evt)) != 0U \
        && ((Module__DGSENAB & (evt)) != 0U || (*Module__DGSMASK & (evt)) != 0U))

/*
 *  ======== xdc_runtime_Diags_getLevel ========
 *  Returns the event level set in the given diags mask. The level is a value
 *  stored using two bits of the diags mask.
 */
#define xdc_runtime_Diags_getLevel(mask) \
    (xdc_runtime_Diags_LEVEL & (mask))

/*
 *  ======== xdc_runtime_Diags_compareLevels ========
 *  The definition of the diags levels assigns the value '0' to the highest
 *  priority events and '3' to the lowest, so the comparison is done backwards.
 *  For example, for (LEVEL4 (0), LEVEL1 (3)) this must return false.
 */
#define xdc_runtime_Diags_compareLevels(levelA, levelB) \
    ((levelA) > (levelB))
#endif
/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 7-31-2018 11:49:29; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


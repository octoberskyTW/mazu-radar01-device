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

#ifndef xdc_runtime_Types__epilogue__include
#define xdc_runtime_Types__epilogue__include

/*
 *  ======== Types__epilogue.h ========
 *  Hand crafted macros for Types.xdc
 */

/*
 *  ======== xdc_runtime_Types_getEventId ========
 */
#define xdc_runtime_Types_getEventId(evt) (\
    (xdc_runtime_Types_RopeId)((evt) >> 16))

/*
 *  ======== xdc_runtime_Types_makeEvent ========
 */
#define xdc_runtime_Types_makeEvent(id, site) (\
    (xdc_runtime_Types_Event)((((Bits32) id) << 16U) | ((Bits32)(site) & 0x0000ffffU)))

/*
 *  ======== xdc_runtime_Types_getModuleId ========
 */
#define xdc_runtime_Types_getModuleId(evt) ((evt) & 0x0000ffffU)

#endif
/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 7-31-2018 11:49:30; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


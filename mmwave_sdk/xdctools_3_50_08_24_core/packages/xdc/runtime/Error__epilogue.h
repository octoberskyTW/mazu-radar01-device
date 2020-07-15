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

#ifndef xdc_runtime_Error__epilogue__include
#define xdc_runtime_Error__epilogue__include

/*
 *  ======== xdc_runtime_Error_raise ========
 *  Call underlying error handler with current module ID, file name, and
 *  line number.
 *
 *  Note use of xdc_FILE__ in lieu of __FILE__; this is done
 *  to prevent accumulation of file name strings in the application.  See
 *  xdc.h for details.
 */
#define xdc_runtime_Error_raise(eb, id, arg1, arg2) \
    xdc_runtime_Error_raiseX((eb), Module__MID, xdc_FILE__, __LINE__, \
        (id), (IArg)(arg1), (IArg)(arg2));

/*
 *  ======== xdc_runtime_Error_idToCode ========
 */
#define xdc_runtime_Error_idToCode(id) \
    (xdc_UInt16)((id) & 0x0000ffffU)

/*
 *  ======== xdc_runtime_Error_idToUid ========
 */
#define xdc_runtime_Error_idToUid(id) \
    (xdc_UInt16)((id) >> 16)

#define xdc_runtime_Error_ABORT NULL

extern xdc_runtime_Error_Block xdc_runtime_Error_IgnoreBlock;
#define xdc_runtime_Error_IGNORE (&xdc_runtime_Error_IgnoreBlock)

#endif
/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 7-31-2018 11:49:29; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


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
/*
 *  ======== Core-params.c ========
 */

#include <string.h>

#include <xdc/runtime/IInstance.h>
#include <xdc/runtime/Types.h>

#include "package/internal/Core.xdc.h"

/*
 *  ======== Core_assignParams ========
 */
Void Core_assignParams(Ptr dstPrms, CPtr srcPrms, SizeT mpsz, SizeT ipsz)
{
    Types_PrmsHdr *dHdr;
    const Types_PrmsHdr *sHdr;
    IInstance_Params *dIPrms;
    IInstance_Params *sIPrms;
    SizeT sz, sz2, isz2;

    sHdr = (const Types_PrmsHdr *)srcPrms;
    sIPrms = (IInstance_Params *)sHdr->instPrms;

    sz = mpsz - ipsz;           /* size of mod params beyond interface */
    isz2 = sIPrms->__size;
    sz2 = sHdr->size - isz2;

    (void)memcpy(dstPrms, srcPrms, sz2 < sz ? sz2 : sz);
    dHdr = (Types_PrmsHdr *)dstPrms;
    dHdr->size = mpsz;
    dHdr->self = dstPrms;       /* mark dstParams as initialized */
    dIPrms = (IInstance_Params *)((Char *)dstPrms + sz);
    dHdr->instPrms = (Char *)dstPrms + sz;

    (void)memcpy(dIPrms, sIPrms, isz2 < ipsz ? isz2 : ipsz);
    dIPrms->__size = ipsz;
 }
/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 7-31-2018 11:49:29; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


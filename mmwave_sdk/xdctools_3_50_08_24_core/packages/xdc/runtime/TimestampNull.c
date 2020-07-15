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
 *  ======== TimestampNull.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Types.h>

#include "package/internal/TimestampNull.xdc.h"

/*
 *  ======== TimestampNull_get32 ========
 */
Bits32 TimestampNull_get32(Void)
{
    return (~0U);
}

/*
 *  ======== TimestampNull_get64 ========
 */
Void TimestampNull_get64(Types_Timestamp64 *result)
{
    result->lo = ~0U;
    result->hi = ~0U;
}

/*
 *  ======== TimestampNull_getFreq ========
 */
Void TimestampNull_getFreq(Types_FreqHz *freq)
{
    freq->lo = 0U;
    freq->hi = 0U;
}
/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 7-31-2018 11:49:30; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


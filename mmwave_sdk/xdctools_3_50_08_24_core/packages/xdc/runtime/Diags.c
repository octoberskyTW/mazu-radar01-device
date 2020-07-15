/* 
 *  Copyright (c) 2008-2018 Texas Instruments Incorporated
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
 *  ======== Diags.c ========
 */
#include <xdc/std.h>
#include <xdc/runtime/Text.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Registry.h>

#include <string.h>

#include "package/internal/Diags.xdc.h"

#define MASKOPS "=+-"

/*
 *  ======== setMask ========
 */
Void Diags_setMask(CString src)
{
    const Diags_DictElem *de;
    Bits16 mask;
    UShort len;
    String ops;
    Char op;
    Char bc;
    Char *bcp;
    ptrdiff_t diff;
    Types_RegDesc *desc;

    for (;;) {

        /* find first/next op in the string src */
        ops = strpbrk(src, MASKOPS);
        if (ops == (String)NULL) {
            return;
        }

        /* if the module specification is "", return */
        diff = ops - src;
        len = (UShort)diff;  /* len = length of the module specification */
        if (len == 0U) {
            return;
        }

        /* get operation from ops string */
        bcp = ops;
        op = *bcp;    /* op = one of the ops in MASKOPS */
        bcp++;

        /* compute mask from ops string */
        mask = 0U;
        for (;;) {
            bc = *bcp;
            bcp++;
            if (bc == ';' || bc == '\0') {
                break;
            }
            else if (bc >= '1' && bc <= '8') {
                mask |= (Bits16)0x100U << ((UChar)bc - (UChar)'1');
            }
            else if (bc == 'L') {
                mask |= Diags_LIFECYCLE;
            }
            else if (bc == 'E') {
                mask |= Diags_ENTRY;
            }
            else if (bc == 'X') {
                mask |= Diags_EXIT;
            }
            else if (bc == 'A') {
                mask |= Diags_ASSERT;
            }
            else if (bc == 'I') {
                mask |= Diags_INTERNAL;
            }
            else if (bc == 'Z') {
                mask |= Diags_ANALYSIS;
            }
            else if (bc == 'F') {
                mask |= Diags_INFO;
            }
            else if (bc == 'S') {
                mask |= Diags_STATUS;
            }
            else {
                return;
            }
        }

        /* Check the registry for matching modules. */
        desc = NULL;
        for (;;) {
            /*
             * Find the next module in the registry matching the module
             * pattern. 'desc' is NULL the first time around, and marks
             * the previous module in each successive looop.
             */
            desc = Registry_findByNamePattern(src, len, desc);

            /* Break if no matching module was found. */
            if (desc == NULL) {
                break;
            }

            /* Update the module's mask */
            if (op == '+') {
                desc->mask |= mask;
            }
            else if (op == '-') {
                desc->mask &= ~mask;
            }
            else {
                desc->mask = mask;
            }
        }

        /* if set mask is disabled skip this part; this allows whole program
         * optimizers to remove this loop
         */
        if (Diags_setMaskEnabled == TRUE) {

            /* Only modules whose common$.nameModule parameter is set to 'true'
             * are found in the dictionary.
             * The operation 'ops' is applied to all matching modules.
             */
            for (de = Diags_dictBase; de->modId != 0U; de++) {

                /* set tmp = length of the module specification */
                UShort tmp = len;
                if (Text_matchRope(de->modId, src, &tmp) != -1) {
                    /* de->modId matches src[0 - len) */

                    /* apply mask to the matched module's mask */
                    if (op == '+') {
                        *de->maskAddr |= mask;
                    }
                    else if (op == '-') {
                        *de->maskAddr &= ~mask;
                    }
                    else {
                        *de->maskAddr = mask;
                    }
                }
            }
        }

        /* if we reached the end of the string, return */
        if (bc == '\0') {
            return;
        }

        /* otherwise, move src to end of the operation string and restart */
        src = bcp;
    }
}
/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 7-31-2018 11:49:29; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


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

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__ti__)

/*
 *  ======== Hwi_disable ========
 */
#define ti_sysbios_family_arm_v7r_keystone3_Hwi_disable() _disable_IRQ()

/*
 *  ======== Hwi_enable ========
 */
#define ti_sysbios_family_arm_v7r_keystone3_Hwi_enable() _enable_IRQ()

/*
 *  ======== Hwi_restore ========
 */
#define ti_sysbios_family_arm_v7r_keystone3_Hwi_restore(key) _restore_interrupts(key)

/*
 *  ======== Hwi_disableFIQ ========
 */
#define ti_sysbios_family_arm_v7r_keystone3_Hwi_disableFIQ() _disable_FIQ()

/*
 *  ======== Hwi_enableFIQ ========
 */
#define ti_sysbios_family_arm_v7r_keystone3_Hwi_enableFIQ() _enable_FIQ()

/*
 *  ======== Hwi_restoreFIQ ========
 */
#define ti_sysbios_family_arm_v7r_keystone3_Hwi_restoreFIQ(key) _restore_interrupts(key)

#endif

#ifdef __cplusplus
}
#endif

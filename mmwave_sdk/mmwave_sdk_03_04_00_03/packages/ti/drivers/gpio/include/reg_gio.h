/**
 *  @file    reg_gio.h
 *
 *  @brief
 *    This file gives register definitions of MSS_GIO module.
 *
 *  This file is auto-generated on 8/22/2019.
 *
 */

 /*
 *   (C) Copyright 2016, Texas Instruments Incorporated. - TI web address www.ti.com
 *---------------------------------------------------------------------------------------
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *
 *    Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT  OWNER OR CONTRIBUTORS
 *  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT,  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef REG_GIO_H
#define REG_GIO_H

/****************************************************************************************
 * INCLUDE FILES
 ****************************************************************************************/
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup GPIO_DRIVER_INTERNAL_DATA_STRUCTURE
 @{ */

/* Definition for field RESET in Register GIOGCR */
#define GIOGCR_RESET_BIT_START                              0U
#define GIOGCR_RESET_BIT_END                                0U

/* Definition for field NU0 in Register GIOGCR */
#define GIOGCR_NU0_BIT_START                                1U
#define GIOGCR_NU0_BIT_END                                  31U

/* Definition for field GIOPWDN in Register GIOPWDN */
#define GIOPWDN_GIOPWDN_BIT_START                           0U
#define GIOPWDN_GIOPWDN_BIT_END                             0U

/* Definition for field NU in Register GIOPWDN */
#define GIOPWDN_NU_BIT_START                                1U
#define GIOPWDN_NU_BIT_END                                  32U

/* Definition for field GIOINTDET_0 in Register GIOINTDET */
#define GIOINTDET_GIOINTDET_0_BIT_START                     0U
#define GIOINTDET_GIOINTDET_0_BIT_END                       7U

/* Definition for field GIOINTDET_1 in Register GIOINTDET */
#define GIOINTDET_GIOINTDET_1_BIT_START                     8U
#define GIOINTDET_GIOINTDET_1_BIT_END                       15U

/* Definition for field GIOINTDET_2 in Register GIOINTDET */
#define GIOINTDET_GIOINTDET_2_BIT_START                     16U
#define GIOINTDET_GIOINTDET_2_BIT_END                       23U

/* Definition for field GIOINTDET_3 in Register GIOINTDET */
#define GIOINTDET_GIOINTDET_3_BIT_START                     24U
#define GIOINTDET_GIOINTDET_3_BIT_END                       31U

/* Definition for field GIOPOL_0 in Register GIOPOL */
#define GIOPOL_GIOPOL_0_BIT_START                           0U
#define GIOPOL_GIOPOL_0_BIT_END                             7U

/* Definition for field GIOPOL_1 in Register GIOPOL */
#define GIOPOL_GIOPOL_1_BIT_START                           8U
#define GIOPOL_GIOPOL_1_BIT_END                             15U

/* Definition for field GIOPOL_2 in Register GIOPOL */
#define GIOPOL_GIOPOL_2_BIT_START                           16U
#define GIOPOL_GIOPOL_2_BIT_END                             23U

/* Definition for field GIOPOL_3 in Register GIOPOL */
#define GIOPOL_GIOPOL_3_BIT_START                           24U
#define GIOPOL_GIOPOL_3_BIT_END                             31U

/* Definition for field GIOENASET_0 in Register GIOENASET */
#define GIOENASET_GIOENASET_0_BIT_START                     0U
#define GIOENASET_GIOENASET_0_BIT_END                       7U

/* Definition for field GIOENASET_1 in Register GIOENASET */
#define GIOENASET_GIOENASET_1_BIT_START                     8U
#define GIOENASET_GIOENASET_1_BIT_END                       15U

/* Definition for field GIOENASET_2 in Register GIOENASET */
#define GIOENASET_GIOENASET_2_BIT_START                     16U
#define GIOENASET_GIOENASET_2_BIT_END                       23U

/* Definition for field GIOENASET_3 in Register GIOENASET */
#define GIOENASET_GIOENASET_3_BIT_START                     24U
#define GIOENASET_GIOENASET_3_BIT_END                       31U

/* Definition for field GIOENACLR_0 in Register GIOENACLR */
#define GIOENACLR_GIOENACLR_0_BIT_START                     0U
#define GIOENACLR_GIOENACLR_0_BIT_END                       7U

/* Definition for field GIOENACLR_1 in Register GIOENACLR */
#define GIOENACLR_GIOENACLR_1_BIT_START                     8U
#define GIOENACLR_GIOENACLR_1_BIT_END                       15U

/* Definition for field GIOENACLR_2 in Register GIOENACLR */
#define GIOENACLR_GIOENACLR_2_BIT_START                     16U
#define GIOENACLR_GIOENACLR_2_BIT_END                       23U

/* Definition for field GIOENACLR_3 in Register GIOENACLR */
#define GIOENACLR_GIOENACLR_3_BIT_START                     24U
#define GIOENACLR_GIOENACLR_3_BIT_END                       31U

/* Definition for field GIOLVLSET_0 in Register GIOLVLSET */
#define GIOLVLSET_GIOLVLSET_0_BIT_START                     0U
#define GIOLVLSET_GIOLVLSET_0_BIT_END                       7U

/* Definition for field GIOLVLSET_1 in Register GIOLVLSET */
#define GIOLVLSET_GIOLVLSET_1_BIT_START                     8U
#define GIOLVLSET_GIOLVLSET_1_BIT_END                       15U

/* Definition for field GIOLVLSET_2 in Register GIOLVLSET */
#define GIOLVLSET_GIOLVLSET_2_BIT_START                     16U
#define GIOLVLSET_GIOLVLSET_2_BIT_END                       23U

/* Definition for field GIOLVLSET_3 in Register GIOLVLSET */
#define GIOLVLSET_GIOLVLSET_3_BIT_START                     24U
#define GIOLVLSET_GIOLVLSET_3_BIT_END                       31U

/* Definition for field GIOLVLCLR_0 in Register GIOLVLCLR */
#define GIOLVLCLR_GIOLVLCLR_0_BIT_START                     0U
#define GIOLVLCLR_GIOLVLCLR_0_BIT_END                       7U

/* Definition for field GIOLVLCLR_1 in Register GIOLVLCLR */
#define GIOLVLCLR_GIOLVLCLR_1_BIT_START                     8U
#define GIOLVLCLR_GIOLVLCLR_1_BIT_END                       15U

/* Definition for field GIOLVLCLR_2 in Register GIOLVLCLR */
#define GIOLVLCLR_GIOLVLCLR_2_BIT_START                     16U
#define GIOLVLCLR_GIOLVLCLR_2_BIT_END                       23U

/* Definition for field GIOLVLCLR_3 in Register GIOLVLCLR */
#define GIOLVLCLR_GIOLVLCLR_3_BIT_START                     24U
#define GIOLVLCLR_GIOLVLCLR_3_BIT_END                       31U

/* Definition for field GIOFLG_0 in Register GIOFLG */
#define GIOFLG_GIOFLG_0_BIT_START                           0U
#define GIOFLG_GIOFLG_0_BIT_END                             7U

/* Definition for field GIOFLG_1 in Register GIOFLG */
#define GIOFLG_GIOFLG_1_BIT_START                           8U
#define GIOFLG_GIOFLG_1_BIT_END                             15U

/* Definition for field GIOFLG_2 in Register GIOFLG */
#define GIOFLG_GIOFLG_2_BIT_START                           16U
#define GIOFLG_GIOFLG_2_BIT_END                             23U

/* Definition for field GIOFLG_3 in Register GIOFLG */
#define GIOFLG_GIOFLG_3_BIT_START                           24U
#define GIOFLG_GIOFLG_3_BIT_END                             31U

/* Definition for field GIOOFFA in Register GIOOFFA */
#define GIOOFFA_GIOOFFA_BIT_START                           0U
#define GIOOFFA_GIOOFFA_BIT_END                             5U

/* Definition for field NU1 in Register GIOOFFA */
#define GIOOFFA_NU1_BIT_START                               6U
#define GIOOFFA_NU1_BIT_END                                 31U

/* Definition for field GIOOFFB in Register GIOOFFB */
#define GIOOFFB_GIOOFFB_BIT_START                           0U
#define GIOOFFB_GIOOFFB_BIT_END                             5U

/* Definition for field NU2 in Register GIOOFFB */
#define GIOOFFB_NU2_BIT_START                               6U
#define GIOOFFB_NU2_BIT_END                                 31U

/* Definition for field GIOEMUA in Register GIOEMUA */
#define GIOEMUA_GIOEMUA_BIT_START                           0U
#define GIOEMUA_GIOEMUA_BIT_END                             5U

/* Definition for field NU3 in Register GIOEMUA */
#define GIOEMUA_NU3_BIT_START                               6U
#define GIOEMUA_NU3_BIT_END                                 31U

/* Definition for field GIOEMUB in Register GIOEMUB */
#define GIOEMUB_GIOEMUB_BIT_START                           0U
#define GIOEMUB_GIOEMUB_BIT_END                             5U

/* Definition for field NU4 in Register GIOEMUB */
#define GIOEMUB_NU4_BIT_START                               6U
#define GIOEMUB_NU4_BIT_END                                 31U

/* Definition for field GIODIRA in Register GIODIRA */
#define GIODIRA_GIODIRA_BIT_START                           0U
#define GIODIRA_GIODIRA_BIT_END                             7U

/* Definition for field NU5 in Register GIODIRA */
#define GIODIRA_NU5_BIT_START                               8U
#define GIODIRA_NU5_BIT_END                                 31U

/* Definition for field GIODINA in Register GIODINA */
#define GIODINA_GIODINA_BIT_START                           0U
#define GIODINA_GIODINA_BIT_END                             7U

/* Definition for field NU11 in Register GIODINA */
#define GIODINA_NU11_BIT_START                              8U
#define GIODINA_NU11_BIT_END                                31U

/* Definition for field GIODOUTA in Register GIODOUTA */
#define GIODOUTA_GIODOUTA_BIT_START                         0U
#define GIODOUTA_GIODOUTA_BIT_END                           7U

/* Definition for field NU17 in Register GIODOUTA */
#define GIODOUTA_NU17_BIT_START                             8U
#define GIODOUTA_NU17_BIT_END                               31U

/* Definition for field GIODSETA in Register GIOSETA */
#define GIOSETA_GIODSETA_BIT_START                          0U
#define GIOSETA_GIODSETA_BIT_END                            7U

/* Definition for field NU23 in Register GIOSETA */
#define GIOSETA_NU23_BIT_START                              8U
#define GIOSETA_NU23_BIT_END                                31U

/* Definition for field GIODCLRA in Register GIOCLRA */
#define GIOCLRA_GIODCLRA_BIT_START                          0U
#define GIOCLRA_GIODCLRA_BIT_END                            7U

/* Definition for field NU29 in Register GIOCLRA */
#define GIOCLRA_NU29_BIT_START                              8U
#define GIOCLRA_NU29_BIT_END                                31U

/* Definition for field GIOPDRA in Register GIOPDRA */
#define GIOPDRA_GIOPDRA_BIT_START                           0U
#define GIOPDRA_GIOPDRA_BIT_END                             7U

/* Definition for field NU35 in Register GIOPDRA */
#define GIOPDRA_NU35_BIT_START                              8U
#define GIOPDRA_NU35_BIT_END                                31U

/* Definition for field GIOPULDISA in Register GIOPULDISA */
#define GIOPULDISA_GIOPULDISA_BIT_START                     0U
#define GIOPULDISA_GIOPULDISA_BIT_END                       7U

/* Definition for field NU in Register GIOPULDISA */
#define GIOPULDISA_NU_BIT_START                             8U
#define GIOPULDISA_NU_BIT_END                               31U

/* Definition for field GIOPSLA in Register GIOPSLA */
#define GIOPSLA_GIOPSLA_BIT_START                           0U
#define GIOPSLA_GIOPSLA_BIT_END                             7U

/* Definition for field NU35 in Register GIOPSLA */
#define GIOPSLA_NU35_BIT_START                              8U
#define GIOPSLA_NU35_BIT_END                                31U

/* Definition for field GIODIRB in Register GIODIRB */
#define GIODIRB_GIODIRB_BIT_START                           0U
#define GIODIRB_GIODIRB_BIT_END                             7U

/* Definition for field NU6 in Register GIODIRB */
#define GIODIRB_NU6_BIT_START                               8U
#define GIODIRB_NU6_BIT_END                                 31U

/* Definition for field GIODINB in Register GIODINB */
#define GIODINB_GIODINB_BIT_START                           0U
#define GIODINB_GIODINB_BIT_END                             7U

/* Definition for field NU12 in Register GIODINB */
#define GIODINB_NU12_BIT_START                              8U
#define GIODINB_NU12_BIT_END                                31U

/* Definition for field GIODOUTB in Register GIODOUTB */
#define GIODOUTB_GIODOUTB_BIT_START                         0U
#define GIODOUTB_GIODOUTB_BIT_END                           7U

/* Definition for field NU18 in Register GIODOUTB */
#define GIODOUTB_NU18_BIT_START                             8U
#define GIODOUTB_NU18_BIT_END                               31U

/* Definition for field GIODSETB in Register GIOSETB */
#define GIOSETB_GIODSETB_BIT_START                          0U
#define GIOSETB_GIODSETB_BIT_END                            7U

/* Definition for field NU24 in Register GIOSETB */
#define GIOSETB_NU24_BIT_START                              8U
#define GIOSETB_NU24_BIT_END                                31U

/* Definition for field GIODCLRB in Register GIOCLRB */
#define GIOCLRB_GIODCLRB_BIT_START                          0U
#define GIOCLRB_GIODCLRB_BIT_END                            7U

/* Definition for field NU30 in Register GIOCLRB */
#define GIOCLRB_NU30_BIT_START                              8U
#define GIOCLRB_NU30_BIT_END                                31U

/* Definition for field GIOPDRB in Register GIOPDRB */
#define GIOPDRB_GIOPDRB_BIT_START                           0U
#define GIOPDRB_GIOPDRB_BIT_END                             7U

/* Definition for field NU36 in Register GIOPDRB */
#define GIOPDRB_NU36_BIT_START                              8U
#define GIOPDRB_NU36_BIT_END                                31U

/* Definition for field GIOPULDISB in Register GIOPULDISB */
#define GIOPULDISB_GIOPULDISB_BIT_START                     0U
#define GIOPULDISB_GIOPULDISB_BIT_END                       7U

/* Definition for field NU36 in Register GIOPULDISB */
#define GIOPULDISB_NU36_BIT_START                           8U
#define GIOPULDISB_NU36_BIT_END                             31U

/* Definition for field GIOPSLB in Register GIOPSLB */
#define GIOPSLB_GIOPSLB_BIT_START                           0U
#define GIOPSLB_GIOPSLB_BIT_END                             7U

/* Definition for field NU36 in Register GIOPSLB */
#define GIOPSLB_NU36_BIT_START                              8U
#define GIOPSLB_NU36_BIT_END                                31U

/* Definition for field GIODIRC in Register GIODIRC */
#define GIODIRC_GIODIRC_BIT_START                           0U
#define GIODIRC_GIODIRC_BIT_END                             7U

/* Definition for field NU7 in Register GIODIRC */
#define GIODIRC_NU7_BIT_START                               8U
#define GIODIRC_NU7_BIT_END                                 31U

/* Definition for field GIODINC in Register GIODINC */
#define GIODINC_GIODINC_BIT_START                           0U
#define GIODINC_GIODINC_BIT_END                             7U

/* Definition for field NU13 in Register GIODINC */
#define GIODINC_NU13_BIT_START                              8U
#define GIODINC_NU13_BIT_END                                31U

/* Definition for field GIODOUTC in Register GIODOUTC */
#define GIODOUTC_GIODOUTC_BIT_START                         0U
#define GIODOUTC_GIODOUTC_BIT_END                           7U

/* Definition for field NU19 in Register GIODOUTC */
#define GIODOUTC_NU19_BIT_START                             8U
#define GIODOUTC_NU19_BIT_END                               31U

/* Definition for field GIODSETC in Register GIOSETC */
#define GIOSETC_GIODSETC_BIT_START                          0U
#define GIOSETC_GIODSETC_BIT_END                            7U

/* Definition for field NU25 in Register GIOSETC */
#define GIOSETC_NU25_BIT_START                              8U
#define GIOSETC_NU25_BIT_END                                31U

/* Definition for field GIODCLRC in Register GIOCLRC */
#define GIOCLRC_GIODCLRC_BIT_START                          0U
#define GIOCLRC_GIODCLRC_BIT_END                            7U

/* Definition for field NU31 in Register GIOCLRC */
#define GIOCLRC_NU31_BIT_START                              8U
#define GIOCLRC_NU31_BIT_END                                31U

/* Definition for field GIOPDRC in Register GIOPDRC */
#define GIOPDRC_GIOPDRC_BIT_START                           0U
#define GIOPDRC_GIOPDRC_BIT_END                             7U

/* Definition for field NU37 in Register GIOPDRC */
#define GIOPDRC_NU37_BIT_START                              8U
#define GIOPDRC_NU37_BIT_END                                31U

/* Definition for field GIOPULDISC in Register GIOPULDISC */
#define GIOPULDISC_GIOPULDISC_BIT_START                     0U
#define GIOPULDISC_GIOPULDISC_BIT_END                       7U

/* Definition for field NU37 in Register GIOPULDISC */
#define GIOPULDISC_NU37_BIT_START                           8U
#define GIOPULDISC_NU37_BIT_END                             31U

/* Definition for field GIOPSLC in Register GIOPSLC */
#define GIOPSLC_GIOPSLC_BIT_START                           0U
#define GIOPSLC_GIOPSLC_BIT_END                             7U

/* Definition for field NU37 in Register GIOPSLC */
#define GIOPSLC_NU37_BIT_START                              8U
#define GIOPSLC_NU37_BIT_END                                31U

/* Definition for field GIODIRD in Register GIODIRD */
#define GIODIRD_GIODIRD_BIT_START                           0U
#define GIODIRD_GIODIRD_BIT_END                             7U

/* Definition for field NU8 in Register GIODIRD */
#define GIODIRD_NU8_BIT_START                               8U
#define GIODIRD_NU8_BIT_END                                 31U

/* Definition for field GIODIND in Register GIODIND */
#define GIODIND_GIODIND_BIT_START                           0U
#define GIODIND_GIODIND_BIT_END                             7U

/* Definition for field NU14 in Register GIODIND */
#define GIODIND_NU14_BIT_START                              8U
#define GIODIND_NU14_BIT_END                                31U

/* Definition for field GIODOUTD in Register GIODOUTD */
#define GIODOUTD_GIODOUTD_BIT_START                         0U
#define GIODOUTD_GIODOUTD_BIT_END                           7U

/* Definition for field NU20 in Register GIODOUTD */
#define GIODOUTD_NU20_BIT_START                             8U
#define GIODOUTD_NU20_BIT_END                               31U

/* Definition for field GIODSETD in Register GIOSETD */
#define GIOSETD_GIODSETD_BIT_START                          0U
#define GIOSETD_GIODSETD_BIT_END                            7U

/* Definition for field NU26 in Register GIOSETD */
#define GIOSETD_NU26_BIT_START                              8U
#define GIOSETD_NU26_BIT_END                                31U

/* Definition for field GIODCLRD in Register GIOCLRD */
#define GIOCLRD_GIODCLRD_BIT_START                          0U
#define GIOCLRD_GIODCLRD_BIT_END                            7U

/* Definition for field NU32 in Register GIOCLRD */
#define GIOCLRD_NU32_BIT_START                              8U
#define GIOCLRD_NU32_BIT_END                                31U

/* Definition for field GIOPDRD in Register GIOPDRD */
#define GIOPDRD_GIOPDRD_BIT_START                           0U
#define GIOPDRD_GIOPDRD_BIT_END                             7U

/* Definition for field NU38 in Register GIOPDRD */
#define GIOPDRD_NU38_BIT_START                              8U
#define GIOPDRD_NU38_BIT_END                                31U

/* Definition for field GIOPULDISD in Register GIOPULDISD */
#define GIOPULDISD_GIOPULDISD_BIT_START                     0U
#define GIOPULDISD_GIOPULDISD_BIT_END                       7U

/* Definition for field NU38 in Register GIOPULDISD */
#define GIOPULDISD_NU38_BIT_START                           8U
#define GIOPULDISD_NU38_BIT_END                             31U

/* Definition for field GIOPSLD in Register GIOPSLD */
#define GIOPSLD_GIOPSLD_BIT_START                           0U
#define GIOPSLD_GIOPSLD_BIT_END                             7U

/* Definition for field NU38 in Register GIOPSLD */
#define GIOPSLD_NU38_BIT_START                              8U
#define GIOPSLD_NU38_BIT_END                                31U

/* Definition for field GIODIRE in Register GIODIRE */
#define GIODIRE_GIODIRE_BIT_START                           0U
#define GIODIRE_GIODIRE_BIT_END                             7U

/* Definition for field NU9 in Register GIODIRE */
#define GIODIRE_NU9_BIT_START                               8U
#define GIODIRE_NU9_BIT_END                                 31U

/* Definition for field GIODINE in Register GIODINE */
#define GIODINE_GIODINE_BIT_START                           0U
#define GIODINE_GIODINE_BIT_END                             7U

/* Definition for field NU15 in Register GIODINE */
#define GIODINE_NU15_BIT_START                              8U
#define GIODINE_NU15_BIT_END                                31U

/* Definition for field GIODOUTE in Register GIODOUTE */
#define GIODOUTE_GIODOUTE_BIT_START                         0U
#define GIODOUTE_GIODOUTE_BIT_END                           7U

/* Definition for field NU21 in Register GIODOUTE */
#define GIODOUTE_NU21_BIT_START                             8U
#define GIODOUTE_NU21_BIT_END                               31U

/* Definition for field GIODSETE in Register GIOSETE */
#define GIOSETE_GIODSETE_BIT_START                          0U
#define GIOSETE_GIODSETE_BIT_END                            7U

/* Definition for field NU27 in Register GIOSETE */
#define GIOSETE_NU27_BIT_START                              8U
#define GIOSETE_NU27_BIT_END                                31U

/* Definition for field GIODCLRE in Register GIOCLRE */
#define GIOCLRE_GIODCLRE_BIT_START                          0U
#define GIOCLRE_GIODCLRE_BIT_END                            7U

/* Definition for field NU33 in Register GIOCLRE */
#define GIOCLRE_NU33_BIT_START                              8U
#define GIOCLRE_NU33_BIT_END                                31U

/* Definition for field GIOPDRE in Register GIOPDRE */
#define GIOPDRE_GIOPDRE_BIT_START                           0U
#define GIOPDRE_GIOPDRE_BIT_END                             7U

/* Definition for field NU39 in Register GIOPDRE */
#define GIOPDRE_NU39_BIT_START                              8U
#define GIOPDRE_NU39_BIT_END                                31U

/* Definition for field GIOPULDISE in Register GIOPULDISE */
#define GIOPULDISE_GIOPULDISE_BIT_START                     0U
#define GIOPULDISE_GIOPULDISE_BIT_END                       7U

/* Definition for field NU39 in Register GIOPULDISE */
#define GIOPULDISE_NU39_BIT_START                           8U
#define GIOPULDISE_NU39_BIT_END                             31U

/* Definition for field GIOPSLE in Register GIOPSLE */
#define GIOPSLE_GIOPSLE_BIT_START                           0U
#define GIOPSLE_GIOPSLE_BIT_END                             7U

/* Definition for field NU39 in Register GIOPSLE */
#define GIOPSLE_NU39_BIT_START                              8U
#define GIOPSLE_NU39_BIT_END                                31U

/* Definition for field GIODIRF in Register GIODIRF */
#define GIODIRF_GIODIRF_BIT_START                           0U
#define GIODIRF_GIODIRF_BIT_END                             7U

/* Definition for field NU10 in Register GIODIRF */
#define GIODIRF_NU10_BIT_START                              8U
#define GIODIRF_NU10_BIT_END                                31U

/* Definition for field GIODINF in Register GIODINF */
#define GIODINF_GIODINF_BIT_START                           0U
#define GIODINF_GIODINF_BIT_END                             7U

/* Definition for field NU16 in Register GIODINF */
#define GIODINF_NU16_BIT_START                              8U
#define GIODINF_NU16_BIT_END                                31U

/* Definition for field GIODOUTF in Register GIODOUTF */
#define GIODOUTF_GIODOUTF_BIT_START                         0U
#define GIODOUTF_GIODOUTF_BIT_END                           7U

/* Definition for field NU22 in Register GIODOUTF */
#define GIODOUTF_NU22_BIT_START                             8U
#define GIODOUTF_NU22_BIT_END                               31U

/* Definition for field GIODSETF in Register GIOSETF */
#define GIOSETF_GIODSETF_BIT_START                          0U
#define GIOSETF_GIODSETF_BIT_END                            7U

/* Definition for field NU28 in Register GIOSETF */
#define GIOSETF_NU28_BIT_START                              8U
#define GIOSETF_NU28_BIT_END                                31U

/* Definition for field GIODCLRF in Register GIOCLRF */
#define GIOCLRF_GIODCLRF_BIT_START                          0U
#define GIOCLRF_GIODCLRF_BIT_END                            7U

/* Definition for field NU34 in Register GIOCLRF */
#define GIOCLRF_NU34_BIT_START                              8U
#define GIOCLRF_NU34_BIT_END                                31U

/* Definition for field GIOPDRF in Register GIOPDRF */
#define GIOPDRF_GIOPDRF_BIT_START                           0U
#define GIOPDRF_GIOPDRF_BIT_END                             7U

/* Definition for field NU40 in Register GIOPDRF */
#define GIOPDRF_NU40_BIT_START                              8U
#define GIOPDRF_NU40_BIT_END                                31U

/* Definition for field GIOPULDISF in Register GIOPULDISF */
#define GIOPULDISF_GIOPULDISF_BIT_START                     0U
#define GIOPULDISF_GIOPULDISF_BIT_END                       7U

/* Definition for field NU40 in Register GIOPULDISF */
#define GIOPULDISF_NU40_BIT_START                           8U
#define GIOPULDISF_NU40_BIT_END                             31U

/* Definition for field GIOPSLF in Register GIOPSLF */
#define GIOPSLF_GIOPSLF_BIT_START                           0U
#define GIOPSLF_GIOPSLF_BIT_END                             7U

/* Definition for field NU40 in Register GIOPSLF */
#define GIOPSLF_NU40_BIT_START                              8U
#define GIOPSLF_NU40_BIT_END                                31U

/* Definition for field GIODIRG in Register GIODIRG */
#define GIODIRG_GIODIRG_BIT_START                           0U
#define GIODIRG_GIODIRG_BIT_END                             7U

/* Definition for field NU9 in Register GIODIRG */
#define GIODIRG_NU9_BIT_START                               8U
#define GIODIRG_NU9_BIT_END                                 31U

/* Definition for field GIODING in Register GIODING */
#define GIODING_GIODING_BIT_START                           0U
#define GIODING_GIODING_BIT_END                             7U

/* Definition for field NU15 in Register GIODING */
#define GIODING_NU15_BIT_START                              8U
#define GIODING_NU15_BIT_END                                31U

/* Definition for field GIODOUTG in Register GIODOUTG */
#define GIODOUTG_GIODOUTG_BIT_START                         0U
#define GIODOUTG_GIODOUTG_BIT_END                           7U

/* Definition for field NU21 in Register GIODOUTG */
#define GIODOUTG_NU21_BIT_START                             8U
#define GIODOUTG_NU21_BIT_END                               31U

/* Definition for field GIODSETG in Register GIOSETG */
#define GIOSETG_GIODSETG_BIT_START                          0U
#define GIOSETG_GIODSETG_BIT_END                            7U

/* Definition for field NU27 in Register GIOSETG */
#define GIOSETG_NU27_BIT_START                              8U
#define GIOSETG_NU27_BIT_END                                31U

/* Definition for field GIODCLRG in Register GIOCLRG */
#define GIOCLRG_GIODCLRG_BIT_START                          0U
#define GIOCLRG_GIODCLRG_BIT_END                            7U

/* Definition for field NU33 in Register GIOCLRG */
#define GIOCLRG_NU33_BIT_START                              8U
#define GIOCLRG_NU33_BIT_END                                31U

/* Definition for field GIOPDRG in Register GIOPDRG */
#define GIOPDRG_GIOPDRG_BIT_START                           0U
#define GIOPDRG_GIOPDRG_BIT_END                             7U

/* Definition for field NU39 in Register GIOPDRG */
#define GIOPDRG_NU39_BIT_START                              8U
#define GIOPDRG_NU39_BIT_END                                31U

/* Definition for field GIOPULDISG in Register GIOPULDISG */
#define GIOPULDISG_GIOPULDISG_BIT_START                     0U
#define GIOPULDISG_GIOPULDISG_BIT_END                       7U

/* Definition for field NU39 in Register GIOPULDISG */
#define GIOPULDISG_NU39_BIT_START                           8U
#define GIOPULDISG_NU39_BIT_END                             31U

/* Definition for field GIOPSLG in Register GIOPSLG */
#define GIOPSLG_GIOPSLG_BIT_START                           0U
#define GIOPSLG_GIOPSLG_BIT_END                             7U

/* Definition for field NU39 in Register GIOPSLG */
#define GIOPSLG_NU39_BIT_START                              8U
#define GIOPSLG_NU39_BIT_END                                31U

/* Definition for field GIODIRH in Register GIODIRH */
#define GIODIRH_GIODIRH_BIT_START                           0U
#define GIODIRH_GIODIRH_BIT_END                             7U

/* Definition for field NU10 in Register GIODIRH */
#define GIODIRH_NU10_BIT_START                              8U
#define GIODIRH_NU10_BIT_END                                31U

/* Definition for field GIODINH in Register GIODINH */
#define GIODINH_GIODINH_BIT_START                           0U
#define GIODINH_GIODINH_BIT_END                             7U

/* Definition for field NU16 in Register GIODINH */
#define GIODINH_NU16_BIT_START                              8U
#define GIODINH_NU16_BIT_END                                31U

/* Definition for field GIODOUTH in Register GIODOUTH */
#define GIODOUTH_GIODOUTH_BIT_START                         0U
#define GIODOUTH_GIODOUTH_BIT_END                           7U

/* Definition for field NU22 in Register GIODOUTH */
#define GIODOUTH_NU22_BIT_START                             8U
#define GIODOUTH_NU22_BIT_END                               31U

/* Definition for field GIODSETH in Register GIOSETH */
#define GIOSETH_GIODSETH_BIT_START                          0U
#define GIOSETH_GIODSETH_BIT_END                            7U

/* Definition for field NU28 in Register GIOSETH */
#define GIOSETH_NU28_BIT_START                              8U
#define GIOSETH_NU28_BIT_END                                31U

/* Definition for field GIODCLRH in Register GIOCLRH */
#define GIOCLRH_GIODCLRH_BIT_START                          0U
#define GIOCLRH_GIODCLRH_BIT_END                            7U

/* Definition for field NU34 in Register GIOCLRH */
#define GIOCLRH_NU34_BIT_START                              8U
#define GIOCLRH_NU34_BIT_END                                31U

/* Definition for field GIOPDRH in Register GIOPDRH */
#define GIOPDRH_GIOPDRH_BIT_START                           0U
#define GIOPDRH_GIOPDRH_BIT_END                             7U

/* Definition for field NU40 in Register GIOPDRH */
#define GIOPDRH_NU40_BIT_START                              8U
#define GIOPDRH_NU40_BIT_END                                31U

/* Definition for field GIOPULDISH in Register GIOPULDISH */
#define GIOPULDISH_GIOPULDISH_BIT_START                     0U
#define GIOPULDISH_GIOPULDISH_BIT_END                       7U

/* Definition for field NU40 in Register GIOPULDISH */
#define GIOPULDISH_NU40_BIT_START                           8U
#define GIOPULDISH_NU40_BIT_END                             31U

/* Definition for field GIOPSLH in Register GIOPSLH */
#define GIOPSLH_GIOPSLH_BIT_START                           0U
#define GIOPSLH_GIOPSLH_BIT_END                             7U

/* Definition for field NU40 in Register GIOPSLH */
#define GIOPSLH_NU40_BIT_START                              8U
#define GIOPSLH_NU40_BIT_END                                31U

/* Definition for field GIOSRCA in Register GIOSRCA */
#define GIOSRCA_GIOSRCA_BIT_START                           0U
#define GIOSRCA_GIOSRCA_BIT_END                             7U

/* Definition for field NU35 in Register GIOSRCA */
#define GIOSRCA_NU35_BIT_START                              8U
#define GIOSRCA_NU35_BIT_END                                31U

/* Definition for field GIOSRCB in Register GIOSRCB */
#define GIOSRCB_GIOSRCB_BIT_START                           0U
#define GIOSRCB_GIOSRCB_BIT_END                             7U

/* Definition for field NU36 in Register GIOSRCB */
#define GIOSRCB_NU36_BIT_START                              8U
#define GIOSRCB_NU36_BIT_END                                31U

/* Definition for field GIOSRCC in Register GIOSRCC */
#define GIOSRCC_GIOSRCC_BIT_START                           0U
#define GIOSRCC_GIOSRCC_BIT_END                             7U

/* Definition for field NU37 in Register GIOSRCC */
#define GIOSRCC_NU37_BIT_START                              8U
#define GIOSRCC_NU37_BIT_END                                31U

/* Definition for field GIOSRCD in Register GIOSRCD */
#define GIOSRCD_GIOSRCD_BIT_START                           0U
#define GIOSRCD_GIOSRCD_BIT_END                             7U

/* Definition for field NU38 in Register GIOSRCD */
#define GIOSRCD_NU38_BIT_START                              8U
#define GIOSRCD_NU38_BIT_END                                31U

/* Definition for field GIOSRCE in Register GIOSRCE */
#define GIOSRCE_GIOSRCE_BIT_START                           0U
#define GIOSRCE_GIOSRCE_BIT_END                             7U

/* Definition for field NU39 in Register GIOSRCE */
#define GIOSRCE_NU39_BIT_START                              8U
#define GIOSRCE_NU39_BIT_END                                31U

/* Definition for field GIOSRCF in Register GIOSRCF */
#define GIOSRCF_GIOSRCF_BIT_START                           0U
#define GIOSRCF_GIOSRCF_BIT_END                             7U

/* Definition for field NU40 in Register GIOSRCF */
#define GIOSRCF_NU40_BIT_START                              8U
#define GIOSRCF_NU40_BIT_END                                31U

/* Definition for field GIOSRCG in Register GIOSRCG */
#define GIOSRCG_GIOSRCG_BIT_START                           0U
#define GIOSRCG_GIOSRCG_BIT_END                             7U

/* Definition for field NU39 in Register GIOSRCG */
#define GIOSRCG_NU39_BIT_START                              8U
#define GIOSRCG_NU39_BIT_END                                31U

/* Definition for field GIOSRCH in Register GIOSRCH */
#define GIOSRCH_GIOSRCH_BIT_START                           0U
#define GIOSRCH_GIOSRCH_BIT_END                             7U

/* Definition for field NU40 in Register GIOSRCH */
#define GIOSRCH_NU40_BIT_START                              8U
#define GIOSRCH_NU40_BIT_END                                31U




/**
 * @brief
 *  Only Ports A, B, C and D are capable of interrupts.
 *  This is a system limit on the GPIO IP Block.
 */
#define GPIO_MAX_INTERRUPT_PORT         4U

/**
 * @brief
 *  This is the maximum number of pins per GPIO port
 *  This is a system limit on the GPIO IP Block.
 */
#define GPIO_MAX_PINS_PER_PORT          8U

/**
 * @brief
 *  This is the maximum number of interrupts which can be supported.
 *  Only Ports A, B, C and D are capable of interrupts. Also since
 *  each port can have a maximum of 8 pins this is the maximum number
 *  of interrupts which can be supported
 *
 *  This is a system limit on the GPIO IP Block.
 */
#define GPIO_MAX_INTERRUPT              (GPIO_MAX_INTERRUPT_PORT * GPIO_MAX_PINS_PER_PORT)

/**
 * @brief
 *  This is used to define the number of GPIO ports which are available
 *  and this is device specific.
 */
#ifdef SOC_XWR14XX
#define GPIO_MAX_PORT                  4U
#endif
#if (defined(SOC_XWR16XX) || defined(SOC_XWR18XX) || defined(SOC_XWR68XX))
#define GPIO_MAX_PORT                  6U
#endif

/**
 * @brief
 *  GPIO Port Registers
 *
 * @details
 *  This structure defines the register overlay used for each
 *  GPIO Port.
 */
typedef volatile struct GIOPortRegs_t
{
    uint32_t    GIODIR;
    uint32_t    GIODIN;
    uint32_t    GIODOUT;
    uint32_t    GIODSET;
    uint32_t    GIODCLR;
    uint32_t    GIOPDR;
    uint32_t    GIOPULDIS;
    uint32_t    GIOPSL;
}GIOPortRegs;

/**
 * @struct GIORegs_t
 * @brief
 *   Module MSS_GIO Register Definition
 * @details
 *   This structure is used to access the MSS_GIO module registers.
 */
/**
 * @typedef GIORegs
 * @brief
 *   Module MSS_GIO Register Frame type Definition
 * @details
 *   This type is used to access the MSS_GIO module registers.
 */
typedef volatile struct GIORegs_t
{
    uint32_t    GIOGCR                             ;        /* Offset = 0x000 */
    uint32_t    GIOPWDN                            ;        /* Offset = 0x004 */
    uint32_t    GIOINTDET                          ;        /* Offset = 0x008 */
    uint32_t    GIOPOL                             ;        /* Offset = 0x00C */
    uint32_t    GIOENASET                          ;        /* Offset = 0x010 */
    uint32_t    GIOENACLR                          ;        /* Offset = 0x014 */
    uint32_t    GIOLVLSET                          ;        /* Offset = 0x018 */
    uint32_t    GIOLVLCLR                          ;        /* Offset = 0x01C */
    uint32_t    GIOFLG                             ;        /* Offset = 0x020 */
    uint32_t    GIOOFFA                            ;        /* Offset = 0x024 */
    uint32_t    GIOOFFB                            ;        /* Offset = 0x028 */
    uint32_t    GIOEMUA                            ;        /* Offset = 0x02C */
    uint32_t    GIOEMUB                            ;        /* Offset = 0x030 */

    /* NOTE: Modification done manually. The GPIO Port can be written as a structure
     * with N elements. The number of elements can be platform specific. This allows
     * the GPIO driver to work across multiple platforms */
#if 0
    uint32_t    GIODIRA                            ;        /* Offset = 0x034 */
    uint32_t    GIODINA                            ;        /* Offset = 0x038 */
    uint32_t    GIODOUTA                           ;        /* Offset = 0x03C */
    uint32_t    GIOSETA                            ;        /* Offset = 0x040 */
    uint32_t    GIOCLRA                            ;        /* Offset = 0x044 */
    uint32_t    GIOPDRA                            ;        /* Offset = 0x048 */
    uint32_t    GIOPULDISA                         ;        /* Offset = 0x04C */
    uint32_t    GIOPSLA                            ;        /* Offset = 0x050 */
    uint32_t    GIODIRB                            ;        /* Offset = 0x054 */
    uint32_t    GIODINB                            ;        /* Offset = 0x058 */
    uint32_t    GIODOUTB                           ;        /* Offset = 0x05C */
    uint32_t    GIOSETB                            ;        /* Offset = 0x060 */
    uint32_t    GIOCLRB                            ;        /* Offset = 0x064 */
    uint32_t    GIOPDRB                            ;        /* Offset = 0x068 */
    uint32_t    GIOPULDISB                         ;        /* Offset = 0x06C */
    uint32_t    GIOPSLB                            ;        /* Offset = 0x070 */
    uint32_t    GIODIRC                            ;        /* Offset = 0x074 */
    uint32_t    GIODINC                            ;        /* Offset = 0x078 */
    uint32_t    GIODOUTC                           ;        /* Offset = 0x07C */
    uint32_t    GIOSETC                            ;        /* Offset = 0x080 */
    uint32_t    GIOCLRC                            ;        /* Offset = 0x084 */
    uint32_t    GIOPDRC                            ;        /* Offset = 0x088 */
    uint32_t    GIOPULDISC                         ;        /* Offset = 0x08C */
    uint32_t    GIOPSLC                            ;        /* Offset = 0x090 */
    uint32_t    GIODIRD                            ;        /* Offset = 0x094 */
    uint32_t    GIODIND                            ;        /* Offset = 0x098 */
    uint32_t    GIODOUTD                           ;        /* Offset = 0x09C */
    uint32_t    GIOSETD                            ;        /* Offset = 0x0A0 */
    uint32_t    GIOCLRD                            ;        /* Offset = 0x0A4 */
    uint32_t    GIOPDRD                            ;        /* Offset = 0x0A8 */
    uint32_t    GIOPULDISD                         ;        /* Offset = 0x0AC */
    uint32_t    GIOPSLD                            ;        /* Offset = 0x0B0 */
    uint32_t    GIODIRE                            ;        /* Offset = 0x0B4 */
    uint32_t    GIODINE                            ;        /* Offset = 0x0B8 */
    uint32_t    GIODOUTE                           ;        /* Offset = 0x0BC */
    uint32_t    GIOSETE                            ;        /* Offset = 0x0C0 */
    uint32_t    GIOCLRE                            ;        /* Offset = 0x0C4 */
    uint32_t    GIOPDRE                            ;        /* Offset = 0x0C8 */
    uint32_t    GIOPULDISE                         ;        /* Offset = 0x0CC */
    uint32_t    GIOPSLE                            ;        /* Offset = 0x0D0 */
    uint32_t    GIODIRF                            ;        /* Offset = 0x0D4 */
    uint32_t    GIODINF                            ;        /* Offset = 0x0D8 */
    uint32_t    GIODOUTF                           ;        /* Offset = 0x0DC */
    uint32_t    GIOSETF                            ;        /* Offset = 0x0E0 */
    uint32_t    GIOCLRF                            ;        /* Offset = 0x0E4 */
    uint32_t    GIOPDRF                            ;        /* Offset = 0x0E8 */
    uint32_t    GIOPULDISF                         ;        /* Offset = 0x0EC */
    uint32_t    GIOPSLF                            ;        /* Offset = 0x0F0 */
    uint32_t    GIODIRG                            ;        /* Offset = 0x0F4 */
    uint32_t    GIODING                            ;        /* Offset = 0x0F8 */
    uint32_t    GIODOUTG                           ;        /* Offset = 0x0FC */
    uint32_t    GIOSETG                            ;        /* Offset = 0x100 */
    uint32_t    GIOCLRG                            ;        /* Offset = 0x104 */
    uint32_t    GIOPDRG                            ;        /* Offset = 0x108 */
    uint32_t    GIOPULDISG                         ;        /* Offset = 0x10C */
    uint32_t    GIOPSLG                            ;        /* Offset = 0x110 */
    uint32_t    GIODIRH                            ;        /* Offset = 0x114 */
    uint32_t    GIODINH                            ;        /* Offset = 0x118 */
    uint32_t    GIODOUTH                           ;        /* Offset = 0x11C */
    uint32_t    GIOSETH                            ;        /* Offset = 0x120 */
    uint32_t    GIOCLRH                            ;        /* Offset = 0x124 */
    uint32_t    GIOPDRH                            ;        /* Offset = 0x128 */
    uint32_t    GIOPULDISH                         ;        /* Offset = 0x12C */
    uint32_t    GIOPSLH                            ;        /* Offset = 0x130 */
#else
    GIOPortRegs portRegs[GPIO_MAX_PORT];
#endif
    uint32_t    GIOSRCA                            ;        /* Offset = 0x134 */
    uint32_t    GIOSRCB                            ;        /* Offset = 0x138 */
    uint32_t    GIOSRCC                            ;        /* Offset = 0x13C */
    uint32_t    GIOSRCD                            ;        /* Offset = 0x140 */
    uint32_t    GIOSRCE                            ;        /* Offset = 0x144 */
    uint32_t    GIOSRCF                            ;        /* Offset = 0x148 */
    uint32_t    GIOSRCG                            ;        /* Offset = 0x14C */
    uint32_t    GIOSRCH                            ;        /* Offset = 0x150 */
} GIORegs;

/**
@}
*/

#ifdef __cplusplus
}
#endif

#endif /* REG_GIO_H */
/* END OF REG_GIO_H */



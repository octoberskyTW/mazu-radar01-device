/*****************************************************************************/
/*  _STDINT.H                                                                */
/*                                                                           */
/* Copyright (c) 2018 Texas Instruments Incorporated                         */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/

/*-
 * SPDX-License-Identifier: BSD-2-Clause-NetBSD
 *
 * Copyright (c) 2001, 2002 Mike Barcroft <mike@FreeBSD.org>
 * Copyright (c) 2001 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Klaus Klein.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef _MACHINE__STDINT_H_
#define	_MACHINE__STDINT_H_

#pragma diag_push
/* 19.4 is issued for macros that are defined in terms of other macros. */
#pragma CHECK_MISRA("-19.4")

#if !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS)

/* The standard (C99 with TC1+TC2+TC3) now says "integer constant expressions,"
 * not "integer constants." Not all ICE are suitable for use in preprocessor
 * macros. Any test that uses INTn_C in a preprocessor macro is legal C99, but
 * not necessarily legal C99+TC1+TC2+TC3
 *
 * See Defect Report:
 * http://www.open-std.org/jtc1/sc22/wg14/www/docs/dr_209.htm
 *
 * Conclusion: In a pre-processor macro, UINT32_MAX may be used, but not
 * UINT32_C(1234) */
#define  INT8_C(c)  ((int_least8_t)(c))
#define UINT8_C(c)  ((uint_least8_t)(c))

#define  INT16_C(c) ((int_least16_t)(c))
#define UINT16_C(c) ((uint_least16_t)(c))

#define  INT32_C(c) ((int_least32_t)(c))
#define UINT32_C(c) ((uint_least32_t)(c))

#define  INT64_C(c) ((int_least64_t)(c))
#define UINT64_C(c) ((uint_least64_t)(c))

#define  INTMAX_C(c) ((intmax_t)(c))
#define UINTMAX_C(c) ((uintmax_t)(c))

#endif /* !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS) */

#if !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS)

/*
 * ISO/IEC 9899:1999
 * 7.18.2.1 Limits of exact-width integer types
 */
/* Minimum values of exact-width signed integer types. */
#define	INT8_MIN	(-0x7f-1)
#define	INT16_MIN	(-0x7fff-1)
#define	INT32_MIN	(-0x7fffffff-1)
#define	INT64_MIN	(-0x7fffffffffffffffLL-1)

/* Maximum values of exact-width signed integer types. */
#define	INT8_MAX	0x7f
#define	INT16_MAX	0x7fff
#define	INT32_MAX	0x7fffffff
#define	INT64_MAX	0x7fffffffffffffffLL

/* Maximum values of exact-width unsigned integer types. */
#define	UINT8_MAX	0xff
#define	UINT16_MAX	0xffff
#define	UINT32_MAX	0xffffffffU
#define	UINT64_MAX	0xffffffffffffffffULL

/*
 * ISO/IEC 9899:1999
 * 7.18.2.2  Limits of minimum-width integer types
 */
/* Minimum values of minimum-width signed integer types. */
#define	INT_LEAST8_MIN	INT8_MIN
#define	INT_LEAST16_MIN	INT16_MIN
#define	INT_LEAST32_MIN	INT32_MIN
#define	INT_LEAST64_MIN	INT64_MIN

/* Maximum values of minimum-width signed integer types. */
#define	INT_LEAST8_MAX	INT8_MAX
#define	INT_LEAST16_MAX	INT16_MAX
#define	INT_LEAST32_MAX	INT32_MAX
#define	INT_LEAST64_MAX	INT64_MAX

/* Maximum values of minimum-width unsigned integer types. */
#define	UINT_LEAST8_MAX	 UINT8_MAX
#define	UINT_LEAST16_MAX UINT16_MAX
#define	UINT_LEAST32_MAX UINT32_MAX
#define	UINT_LEAST64_MAX UINT64_MAX

/*
 * ISO/IEC 9899:1999
 * 7.18.2.3  Limits of fastest minimum-width integer types
 */
/* Minimum values of fastest minimum-width signed integer types. */
#define	INT_FAST8_MIN	INT32_MIN
#define	INT_FAST16_MIN	INT32_MIN
#define	INT_FAST32_MIN	INT32_MIN
#define	INT_FAST64_MIN	INT64_MIN

/* Maximum values of fastest minimum-width signed integer types. */
#define	INT_FAST8_MAX	INT32_MAX
#define	INT_FAST16_MAX	INT32_MAX
#define	INT_FAST32_MAX	INT32_MAX
#define	INT_FAST64_MAX	INT64_MAX

/* Maximum values of fastest minimum-width unsigned integer types. */
#define	UINT_FAST8_MAX	UINT32_MAX
#define	UINT_FAST16_MAX	UINT32_MAX
#define	UINT_FAST32_MAX	UINT32_MAX
#define	UINT_FAST64_MAX	UINT64_MAX

/*
 * ISO/IEC 9899:1999
 * 7.18.2.4  Limits of integer types capable of holding object pointers
 */
#define	INTPTR_MIN	INT32_MIN
#define	INTPTR_MAX	INT32_MAX
#define	UINTPTR_MAX	UINT32_MAX

/*
 * ISO/IEC 9899:1999
 * 7.18.2.5  Limits of greatest-width integer types
 */
#define	INTMAX_MIN	INT64_MIN
#define	INTMAX_MAX	INT64_MAX
#define	UINTMAX_MAX	UINT64_MAX

/*
 * ISO/IEC 9899:1999
 * 7.18.3  Limits of other integer types
 */
/* Limits of ptrdiff_t. */
#define	PTRDIFF_MIN	INT32_MIN
#define	PTRDIFF_MAX	INT32_MAX

/* Limits of sig_atomic_t. */
#define	SIG_ATOMIC_MIN	INT32_MIN
#define	SIG_ATOMIC_MAX	INT32_MAX

/* Limit of size_t. */
#define	SIZE_MAX	UINT32_MAX

/* Limits of wint_t. */
#define	WINT_MIN	0 /* wint_t is unsigned int for C6X */
#define	WINT_MAX	INT32_MAX

#endif /* !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS) */

#pragma diag_pop

#endif /* !_MACHINE__STDINT_H_ */

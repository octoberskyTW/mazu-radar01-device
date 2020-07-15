/*****************************************************************************/
/*  _CTYPE.H                                                                 */
/*                                                                           */
/* Copyright (c) 2017 Texas Instruments Incorporated                         */
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
 * SPDX-License-Identifier: BSD-2-Clause-FreeBSD
 *
 * Copyright (c) 2011 The FreeBSD Foundation
 * All rights reserved.
 *
 * This software was developed by David Chisnall under sponsorship from
 * the FreeBSD Foundation.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */


#if	(defined(_XLOCALE_WCTYPES) && !defined(_XLOCALE_WCTYPE_H)) || \
	(!defined(_XLOCALE_WCTYPES) && !defined(_XLOCALE_CTYPE_H))

#ifdef _XLOCALE_WCTYPES
#define _XLOCALE_WCTYPE_H
#else
#define _XLOCALE_CTYPE_H
#endif

#ifndef _LOCALE_T_DEFINED
#define _LOCALE_T_DEFINED
typedef struct	_xlocale *locale_t;
#endif

#ifndef _XLOCALE_INLINE
#define _XLOCALE_INLINE static __inline
#endif /* _XLOCALE_INLINE */

#ifdef _XLOCALE_WCTYPES

#define XLOCALE_ISCTYPE(fname, cat) \
		_XLOCALE_INLINE int isw##fname##_l(int, locale_t);\
		_XLOCALE_INLINE int isw##fname##_l(int __c, locale_t __l)\
                { return isw##fname(__c); }
#else
#define XLOCALE_ISCTYPE(__fname, __cat)                             \
		_XLOCALE_INLINE int is##__fname##_l(int, locale_t); \
		_XLOCALE_INLINE int is##__fname##_l(int __c, locale_t __l)\
		{ return is##__fname(__c); }
#endif

XLOCALE_ISCTYPE(alnum, _CTYPE_A|_CTYPE_D|_CTYPE_N)
XLOCALE_ISCTYPE(alpha, _CTYPE_A)
XLOCALE_ISCTYPE(blank, _CTYPE_B)
XLOCALE_ISCTYPE(cntrl, _CTYPE_C)
XLOCALE_ISCTYPE(digit, _CTYPE_D)
XLOCALE_ISCTYPE(graph, _CTYPE_G)
XLOCALE_ISCTYPE(lower, _CTYPE_L)
XLOCALE_ISCTYPE(print, _CTYPE_R)
XLOCALE_ISCTYPE(punct, _CTYPE_P)
XLOCALE_ISCTYPE(space, _CTYPE_S)
XLOCALE_ISCTYPE(upper, _CTYPE_U)
XLOCALE_ISCTYPE(xdigit, _CTYPE_X)
#undef XLOCALE_ISCTYPE

#ifdef _XLOCALE_WCTYPES
_XLOCALE_INLINE int towlower_l(int, locale_t);
_XLOCALE_INLINE int towupper_l(int, locale_t);

_XLOCALE_INLINE int towlower_l(int __c, locale_t __l)
{
   return towlower(__c);
}
_XLOCALE_INLINE int towupper_l(int __c, locale_t __l)
{
   return towupper(__c);
}

_XLOCALE_INLINE int
iswctype_l(wint_t __wc, wctype_t __charclass, locale_t __l)
{
   return iswctype(__wc, __charclass);
}

_XLOCALE_INLINE wctype_t
wctype_l(const char *property, locale_t __l)
{
   return wctype(property);
}

_XLOCALE_INLINE wint_t
towctrans_l(wint_t __wc, wctrans_t desc, locale_t __l)
{
   return towctrans(__wc, desc);
}

_XLOCALE_INLINE wctrans_t
wctrans_l(const char *__charclass, locale_t __l)
{
   return wctrans(__charclass);
}

#undef _XLOCALE_WCTYPES
#else
_XLOCALE_INLINE int tolower_l(int, locale_t);
_XLOCALE_INLINE int toupper_l(int, locale_t);

_XLOCALE_INLINE int tolower_l(int __c, locale_t __l)
{
   return tolower(__c);
}
_XLOCALE_INLINE int toupper_l(int __c, locale_t __l)
{
   return toupper(__c);
}
#endif
#endif /* (defined(_XLOCALE_WCTYPES) && !defined(_XLOCALE_WCTYPE_H)) || \
	(!defined(_XLOCALE_WCTYPES) && !defined(_XLOCALE_CTYPE_H)) */

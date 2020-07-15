/*****************************************************************************/
/*  NONE_MB.C                                                                */
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
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright 2013 Garrett D'Amore <garrett@damore.org>
 * Copyright 2010 Nexenta Systems, Inc.  All rights reserved.
 * Copyright (c) 2002-2004 Tim J. Robbins. All rights reserved.
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Paul Borman at Krystal Technologies.
 *
 * Copyright (c) 2011 The FreeBSD Foundation
 * All rights reserved.
 * Portions of this software were developed by David Chisnall
 * under sponsorship from the FreeBSD Foundation.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <xlocale_private.h>

int mbsinit(const mbstate_t *ps __unused)
{
   return 1;
}

int mbsinit_l(const mbstate_t *ps, locale_t l)
{
   return mbsinit(ps);
}

size_t
mbrtowc(wchar_t * __restrict pwc, const char * __restrict s, size_t n,
        mbstate_t * __restrict ps __unused)
{

	if (s == NULL)
		/* Reset to initial shift state (no-op) */
		return (0);
	if (n == 0)
		/* Incomplete multibyte sequence */
		return ((size_t)-2);
	if (pwc != NULL)
		*pwc = (unsigned char)*s;
	return (*s == '\0' ? 0 : 1);
}

size_t
mbrtowc_l(wchar_t * __restrict pwc, const char * __restrict s, size_t n,
          mbstate_t * __restrict ps, locale_t l __unused)
{
   return mbrtowc(pwc, s, n, ps);
}

size_t
wcrtomb(char * __restrict s, wchar_t wc,
        mbstate_t * __restrict ps __unused)
{
	if (s == NULL)
		/* Reset to initial shift state (no-op) */
		return (1);
	if (((int)wc) < 0 || wc > UCHAR_MAX) {
		errno = EILSEQ;
		return ((size_t)-1);
	}
	*s = (unsigned char)wc;
	return (1);
}

size_t
wcrtomb_l(char * __restrict s, wchar_t wc,
          mbstate_t * __restrict ps, locale_t l __unused)
{
   return wcrtomb(s, wc, ps);
}

size_t
mbsnrtowcs(wchar_t * __restrict dst, const char ** __restrict src,
           size_t nms, size_t len, mbstate_t * __restrict ps __unused)
{
	const char *s;
	size_t nchr;

	if (dst == NULL) {
		s = memchr(*src, '\0', nms);
		return (s != NULL ? s - *src : nms);
	}

	s = *src;
	nchr = 0;
	while (len-- > 0 && nms-- > 0) {
		if ((*dst++ = (unsigned char)*s++) == L'\0') {
			*src = NULL;
			return (nchr);
		}
		nchr++;
	}
	*src = s;
	return (nchr);
}

size_t
mbsnrtowcs_l(wchar_t * __restrict dst, const char ** __restrict src,
             size_t nms, size_t len, mbstate_t * __restrict ps,
             locale_t l __unused)
{
   return mbsnrtowcs(dst, src, nms, len, ps);
}


size_t
wcsnrtombs(char * __restrict dst, const wchar_t ** __restrict src,
           size_t nwc, size_t len, mbstate_t * __restrict ps __unused)
{
	const wchar_t *s;
	size_t nchr;

	if (dst == NULL) {
		for (s = *src; nwc > 0 && *s != L'\0'; s++, nwc--) {
			if (((int)*s) < 0 || *s > UCHAR_MAX) {
				errno = EILSEQ;
				return ((size_t)-1);
			}
		}
		return (s - *src);
	}

	s = *src;
	nchr = 0;
	while (len-- > 0 && nwc-- > 0) {
		if (((int)*s) < 0 || *s > UCHAR_MAX) {
			*src = s;
			errno = EILSEQ;
			return ((size_t)-1);
		}
		if ((*dst++ = *s++) == '\0') {
			*src = NULL;
			return (nchr);
		}
		nchr++;
	}
	*src = s;
	return (nchr);
}

size_t
wcsnrtombs_l(char * __restrict dst, const wchar_t ** __restrict src,
             size_t nwc, size_t len, mbstate_t * __restrict ps,
             locale_t l __unused)
{
   return wcsnrtombs(dst, src, nwc, len, ps);
}

size_t
mbrlen_l(const char * __restrict s, size_t n, mbstate_t * __restrict ps, locale_t locale)
{
   return mbrlen(s, n, ps);
}

size_t
mbrlen(const char * __restrict s, size_t n, mbstate_t * __restrict ps)
{
   /* Note that ps could be NULL, in which case we are supposed to use some
      "internal" mbstate_t object. FreeBSD uses the locale_t object to get that
      object. We do not worry about it because our mbrtowc functions doesn't use
      the ps argument. */
   return mbrtowc(NULL, s, n, ps);
}


size_t
mbsrtowcs_l(wchar_t * __restrict dst, const char ** __restrict src, size_t len,
    mbstate_t * __restrict ps, locale_t locale)
{
   return mbsrtowcs(dst, src, len, ps);
}

size_t
mbsrtowcs(wchar_t * __restrict dst, const char ** __restrict src, size_t len,
    mbstate_t * __restrict ps)
{
   return mbsnrtowcs(dst, src, SIZE_MAX, len, ps);
}


int
mbtowc_l(wchar_t * __restrict pwc, const char * __restrict s, size_t n, locale_t locale)
{
   return mbtowc(pwc, s, n);
}

int
mbtowc(wchar_t * __restrict pwc, const char * __restrict s, size_t n)
{
   size_t rval;

   if (s == NULL) {
      return (0);
   }

   rval = mbrtowc(pwc, s, n, NULL);
   switch (rval) {
      case (size_t)-2:
      errno = EILSEQ;
      /* FALLTHROUGH */
      case (size_t)-1:
      return (-1);
      default:
      return ((int)rval);
   }
}


size_t
wcsrtombs_l(char * __restrict dst, const wchar_t ** __restrict src, size_t len,
            mbstate_t * __restrict ps, locale_t locale)
{
   return wcsrtombs(dst, src, len, ps);
}

size_t
wcsrtombs(char * __restrict dst, const wchar_t ** __restrict src, size_t len,
          mbstate_t * __restrict ps)
{
   return wcsnrtombs(dst, src, SIZE_MAX, len, ps);
}

wint_t
btowc_l(int c, locale_t l)
{
   return btowc(c);
}

wint_t
btowc(int c)
{
   char cc;
   wchar_t wc;

   if (c == EOF)
      return (WEOF);
   /*
    * We expect mbrtowc() to return 0 or 1, hence the check for n > 1
    * which detects error return values as well as "impossible" byte
    * counts.
    */
   cc = (char)c;
   if (mbrtowc(&wc, &cc, 1, NULL) > 1)
      return (WEOF);
   return (wc);
}


int
wctob_l(wint_t c, locale_t locale)
{
   return wctob(c);
}

int
wctob(wint_t c)
{
   char buf[MB_LEN_MAX];
    if (c == WEOF || wcrtomb(buf, c, NULL) != 1)
      return (EOF);
   return ((unsigned char)*buf);
}

int mblen(const char* s, size_t n)
{
   if (s == NULL)
      return 0;

   int rval = mbrtowc(NULL, s, n, NULL);
   if (rval == (size_t)-1 || rval == (size_t)-2)
      return (-1);
   return ((int)rval);
}

int mblen_l(const char* s, size_t n, locale_t locale)
{
   return mblen(s, n);
}

int wctomb(char *s, wchar_t wchar)
{
   size_t rval;

   if (s == NULL) {
      return (0);
   }

   if ((rval = wcrtomb(s, wchar, NULL)) == (size_t)-1)
       return (-1);

   return ((int)rval);
}

int wctomb_l(char *s, wchar_t wchar, locale_t l)
{
   return wctomb(s, wchar);
}

size_t
mbstowcs(wchar_t * __restrict pwcs, const char * __restrict s, size_t n)
{
	const char *sp;
	sp = s;
	return (mbsnrtowcs(pwcs, &sp, SIZE_MAX, n, NULL));
}

size_t
mbstowcs_l(wchar_t * __restrict pwcs, const char * __restrict s, size_t n,
           locale_t l)
{
   return mbstowcs(pwcs, s, n);
}

size_t
wcstombs(char * __restrict s, const wchar_t * __restrict pwcs, size_t n)
{
	const wchar_t *pwcsp;
	pwcsp = pwcs;
	return (wcsnrtombs(s, &pwcsp, SIZE_MAX, n, NULL));
}
size_t
wcstombs_l(char * __restrict s, const wchar_t * __restrict pwcs, size_t n,
           locale_t l)
{
   return wcstombs(s, pwcs, n);
}

int ___mb_cur_max(void)
{
   return 1;
}

int ___mb_cur_max_l(locale_t locale)
{
   return ___mb_cur_max();
}

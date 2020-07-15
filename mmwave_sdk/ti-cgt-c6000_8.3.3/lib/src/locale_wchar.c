/*****************************************************************************/
/*  LOCALE_WCHAR.C                                                           */
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

#include <wchar.h>
#include <xlocale.h>

wint_t fputwc_l(wchar_t wc, FILE *f, locale_t l)
{
   return fputwc(wc, f);
}

wint_t fgetwc_l(FILE *f, locale_t l)
{
   return fgetwc(f);
}

wchar_t* fgetws_l(wchar_t* ws, int num, FILE* stream, locale_t l)
{
   return fgetws(ws, num, stream);
}

int fputws_l(const wchar_t* ws, FILE* stream, locale_t l)
{
   return fputws(ws, stream);
}

int vswprintf_l(wchar_t * __restrict ws, size_t n, locale_t l,
                const wchar_t * __restrict format, va_list ap)
{
   return vswprintf(ws, n, format, ap);
}

int vfwprintf_l(FILE * __restrict stream, locale_t l,
                const wchar_t * __restrict format, va_list ap)
{
   return vfwprintf(stream, format, ap);
}

int vfwscanf_l(FILE * __restrict stream, locale_t l,
               const wchar_t * __restrict format, va_list ap)
{
   return vfwscanf(stream, format, ap);
}

int wcscoll_l(const wchar_t* string1, const wchar_t* string2, locale_t l)
{
   return wcscoll(string1, string2);
}

size_t wcsxfrm_l(wchar_t* __restrict to,
                 const wchar_t * __restrict from,
                 size_t n, locale_t l)
{
   return wcsxfrm(to, from, n);
}

/*****************************************************************************/
/*  LOCALE_STDIO.C                                                           */
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

#include <stdio.h>
#include <xlocale.h>

int fprintf_l(FILE * __restrict _fp, locale_t locale, const char * __restrict _format, ...)
{
   va_list _ap;
   int rval;

   va_start(_ap, _format);
   rval = vfprintf_l(_fp, locale, _format, _ap);
   va_end(_ap);
   return rval;
}

int fscanf_l(FILE * __restrict _fp, locale_t locale,
             const char * __restrict _fmt, ...)
{
   int ret;
   va_list _ap;
   va_start(_ap, _fmt);
   ret = vfscanf(_fp, _fmt, _ap);
   va_end(_ap);
   return ret;
}

int scanf_l(locale_t locale, const char * __restrict _fmt, ...)
{
   int ret;
   va_list _ap;
   va_start(_ap, _fmt);
   ret = vscanf(_fmt, _ap);
   va_end(_ap);
   return ret;
}

int vfscanf_l(FILE * __restrict _fp, locale_t locale,
              const char * __restrict _fmt, va_list _ap)
{
   return vfscanf(_fp, _fmt, _ap);
}

int vscanf_l(locale_t locale, const char * __restrict _fmt, va_list _ap)
{
   return vscanf(_fmt, _ap);
}

int printf_l(locale_t locale, const char * __restrict _fmt, ...)
{
   int ret;
   va_list _ap;
   va_start(_ap, _fmt);
   ret = vprintf(_fmt, _ap);
   va_end(_ap);
   return ret;
}

int snprintf_l(char * __restrict _s, size_t _n, locale_t locale,
               const char * __restrict _fmt, ...)
{
   int ret;
   va_list _ap;
   va_start(_ap, _fmt);
   ret = vsnprintf(_s, _n, _fmt, _ap);
   va_end(_ap);
   return ret;
}

int sscanf_l(const char * __restrict _str, locale_t locale,
             const char * __restrict _fmt, ...)
{
   int ret;
   va_list _ap;

   va_start(_ap, _fmt);
   ret = vsscanf(_str, _fmt, _ap);
   va_end(_ap);
   return ret;
}

int vsscanf_l(const char * __restrict _str, locale_t locale,
              const char * __restrict _fmt, va_list _ap)
{
   return vsscanf(_str, _fmt, _ap);
}

int vfprintf_l(FILE * __restrict _fp, locale_t locale,
               const char * __restrict _fmt, va_list _ap)
{
   return vfprintf(_fp, _fmt, _ap);
}

int vprintf_l(locale_t locale, const char * __restrict _fmt, va_list _ap)
{
   return vprintf(_fmt, _ap);
}

int vsprintf_l(char * __restrict _str, locale_t locale,
               const char * __restrict _fmt, va_list _ap)
{
   return vsprintf(_str, _fmt, _ap);
}

int vsnprintf_l(char * __restrict _str, size_t _n, locale_t locale,
                const char * __restrict _fmt, va_list _ap)
{
   return vsnprintf(_str, _n, _fmt, _ap);
}

int vasprintf_l(char **dst, locale_t locale, const char *fmt, va_list ap)
{
   return vasprintf(dst, fmt, ap);
}

int sprintf_l(char * __restrict _string, locale_t locale,
              const char * __restrict _format, ...)
{
   va_list _ap;
   int rval;

   va_start(_ap, _format);
   rval = vsprintf(_string, _format, _ap);
   va_end(_ap);
   return rval;
}

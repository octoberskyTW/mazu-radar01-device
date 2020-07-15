/*****************************************************************************/
/*  LOCALE_STDLIB.C                                                          */
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

#include <stdlib.h>
#include <xlocale.h>

double atof_l(const char* st, locale_t locale)
{
   return atof(st);
}

int atoi_l(const char* st, locale_t locale)
{
   return atoi(st);
}

long atol_l(const char *st, locale_t locale)
{
   return atol(st);
}

long long atoll_l(const char* st, locale_t locale)
{
   return atoll(st);
}

double strtod_l(const char * st, char ** endptr, locale_t locale)
{
   return strtod(st, endptr);
}

float strtof_l(const char * st, char ** endptr, locale_t locale)
{
   return strtof(st, endptr);
}

long double strtold_l(const char * st, char ** endptr, locale_t locale)
{
   return strtold(st, endptr);
}

long long strtoll_l(const char* str, char ** endptr, int base,
                    locale_t locale)
{
   return strtoll(str, endptr, base);
}

unsigned long strtoul_l(const char* st, char ** endptr, int base, locale_t locale)
{
   return strtoul(st, endptr, base);
}

unsigned long long strtoull_l(const char* st, char ** endptr, int base,
                              locale_t locale)
{
   return strtoull(st, endptr, base);
}

long strtol_l(const char *st, char ** endptr, int base, locale_t locale)
{
   return strtol(st, endptr, base);
}

/****************************************************************************/
/*  strtod                                                                  */
/*                                                                          */
/* Copyright (c) 1993 Texas Instruments Incorporated                        */
/* http://www.ti.com/                                                       */
/*                                                                          */
/*  Redistribution and  use in source  and binary forms, with  or without   */
/*  modification,  are permitted provided  that the  following conditions   */
/*  are met:                                                                */
/*                                                                          */
/*     Redistributions  of source  code must  retain the  above copyright   */
/*     notice, this list of conditions and the following disclaimer.        */
/*                                                                          */
/*     Redistributions in binary form  must reproduce the above copyright   */
/*     notice, this  list of conditions  and the following  disclaimer in   */
/*     the  documentation  and/or   other  materials  provided  with  the   */
/*     distribution.                                                        */
/*                                                                          */
/*     Neither the  name of Texas Instruments Incorporated  nor the names   */
/*     of its  contributors may  be used to  endorse or  promote products   */
/*     derived  from   this  software  without   specific  prior  written   */
/*     permission.                                                          */
/*                                                                          */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS   */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT   */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT   */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT   */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    */
/*                                                                          */
/****************************************************************************/
#include <stdlib.h>
#include <ctype.h>
#include <float.h>
#include <errno.h>
#include <math.h>
#include <_ti_config.h>
#include <limits.h>

#if (DBL_MAX_10_EXP >= 256)
static const _DATA_ACCESS double powerof10[]  = { 1.e1, 1.e2, 1.e4, 1.e8,
						  1.e16, 1.e32, 1.e64, 1.e128,
						  1.e256};
#else
static const _DATA_ACCESS double powerof10[]  = { 1.e1, 1.e2, 1.e4, 1.e8,
						  1.e16, 1.e32};
#endif

static const _DATA_ACCESS double digits[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                                              10, 11, 12, 13, 14, 15 };

/*****************************************************************************/
/* strtod decomposes the input string into three parts:                      */
/* - an initial, possibly empty, sequence of white-space characters          */
/* - a subject sequence RESEMBLING a float constant or INF or NAN            */
/* - a final string of one or more unrecognized characters                   */
/*****************************************************************************/

_CODE_ACCESS double strtod(const char * __restrict st,
                           char ** __restrict endptr)
{
    double      result = 0;
    char        cp;
    const char *fst    = st;
    int         exp    = 0;               /* EXPONENT              */
    int         success  = 0;             /* SUCCESSFUL PARSE      */
    int         sign;
    double      base   = 10;

    /*-----------------------------------------------------------------------*/
    /* Skip any leading whitespace                                           */
    /*-----------------------------------------------------------------------*/
    while (_isspace(*fst)) ++fst;

    /*-----------------------------------------------------------------------*/
    /* Accept a optional plus or minus sign                                  */
    /*-----------------------------------------------------------------------*/
    if ((sign = ((cp = *fst) == '-')) || (cp == '+')) ++fst;

    /*-----------------------------------------------------------------------*/
    /* - INF or INFINITY, ignoring case                                      */
    /* - NAN or NAN<ncharseq>; we don't support the latter                   */
    /*-----------------------------------------------------------------------*/
    if (toupper(*fst) == 'I')
    {
        if (toupper(*++fst) == 'N' &&
            toupper(*++fst) == 'F')
        {
            success = 1;
            if (endptr) *endptr = (char*)fst+1;

            if (toupper(*++fst) == 'I' &&
                toupper(*++fst) == 'N' &&
                toupper(*++fst) == 'I' &&
                toupper(*++fst) == 'T' &&
                toupper(*++fst) == 'Y')
            {
                if (endptr) *endptr = (char*)fst+1;
            }

            return sign ? -INFINITY : INFINITY;
        }

        if (endptr) *endptr = (char*)st;
        return 0.0;
    }

    if (toupper(*fst) == 'N')
    {
        if (toupper(*++fst) == 'A' &&
            toupper(*++fst) == 'N')
        {
            success = 1;
            if (endptr) *endptr = (char*)fst+1;
            return NAN;
        }

        if (endptr) *endptr = (char*)st;
        return 0.0;
    }

    /*-----------------------------------------------------------------------*/
    /* - nonempty sequence of decimal digits, optionally containing a        */
    /*   decimal-point character, then an optional exponent part.            */
    /*-----------------------------------------------------------------------*/
    /* - a 0x or 0X, then a nonempty sequence of hexadecimal digits          */
    /*   optionally containing a decimal-point character, then an optional   */
    /*   binary exponent part                                                */
    /*-----------------------------------------------------------------------*/

    /*-----------------------------------------------------------------------*/
    /* Detect hexadecimal float values.  If the input is "0x", that's        */
    /* actually a valid parse: the answer is 0.0, and *endptr=='x'.  Before  */
    /* we commit to this being a hexadecimal float value, ensure that there  */
    /* is at least one hex digit following the "0x".                         */
    /*-----------------------------------------------------------------------*/
    if (*fst == '0' && toupper(fst[1]) == 'X' &&
        (_isxdigit(fst[2]) || (fst[2] == '.' && _isxdigit(fst[3]))))
    {
        fst += 2;
        base = 16;
    }

    /*-----------------------------------------------------------------------*/
    /* Accept nonempty sequence of decimal or hexidecimal digts, optionally  */
    /* containing a decimal-pointer character.  Decrement exp once per digit */
    /* seen after the decimal point.                                         */
    /*-----------------------------------------------------------------------*/
    int decimal_seen = 0;

    for (cp = *fst; (cp == '.' ||
                     (base == 10 && _isdigit(*fst)) ||
                     (base == 16 && _isxdigit(*fst))); cp = *++fst)
    {
        if (cp == '.')
        {
            if (decimal_seen)
            {
                break; /* no longer valid sequence */
            }
            else decimal_seen = 1;
        }
        else
        {
            result = result * base + (_isdigit(cp) ?
                                      digits[cp - '0'] :
                                      digits[10 + toupper(cp) - 'A']);
            if (decimal_seen) --exp;
            success = 1;
        }
    }

    /*-----------------------------------------------------------------------*/
    /* Negate result if sign seen                                            */
    /*-----------------------------------------------------------------------*/
    if (sign) result = -result;

    /*-----------------------------------------------------------------------*/
    /* For decimal, each decimal place represents a power of 10, as does the */
    /* decimal exponent.  However, for hexadecimal, each hexadecimal place   */
    /* represents a power of 16, but the decimal exponent represents powers  */
    /* of 2.  Scale the counted number of hexadecimal places accordingly.    */
    /*-----------------------------------------------------------------------*/
    if (base == 16) exp <<= 2;

    /*-----------------------------------------------------------------------*/
    /* Read in explicit exponent and calculate result exponent.              */
    /*-----------------------------------------------------------------------*/
    if (success &&
        ((base == 10 && toupper(*fst) == 'E') ||
         (base == 16 && toupper(*fst) == 'P')))
    {
       int exponent_sign_detected = 0;
       int explicit_exp = 0;

       if ((sign = ((cp = *++fst) == '-')) || cp == '+')
       {
          cp = *++fst;
          exponent_sign_detected = 1;
       }

       if (!_isdigit(cp))
       {
           /*----------------------------------------------------------------*/
           /* If the exponent turns out to be ill-formed, (e.g. "1.234empty" */
           /* or "1.234e+mpty") restore bogus exponent back onto returned    */
           /* string (endptr).                                               */
           /*----------------------------------------------------------------*/
           if (exponent_sign_detected) fst--;
           fst--;
       }
       else
           for (explicit_exp = 0; _isdigit(cp); cp = *++fst)
           {
               /* For IEEE, abs(DBL_MIN_EXP) < DBL_MAX_EXP */
               int value = (sign ? -explicit_exp : explicit_exp) + exp;
               if ((base == 10 && abs(value) > DBL_MAX_10_EXP) ||
                   (base == 16 && abs(value) > DBL_MAX_EXP))
               {
                   /* avoid integer overflow, but keep consuming digits! */
               }
               else
               {
                   explicit_exp *= 10;
                   explicit_exp += cp - '0';
               }
           }

       exp += sign ? -explicit_exp : explicit_exp;
    }

    /*-----------------------------------------------------------------------*/
    /* Scale by the exponent                                                 */
    /*-----------------------------------------------------------------------*/
    if (success && result != 0.0)
        if (base == 10)
        {
            /*---------------------------------------------------------------*/
            /* Adjust number by powers of ten specified by format and        */
            /* exponent.                                                     */
            /*---------------------------------------------------------------*/
            int count;
            if (exp > DBL_MAX_10_EXP)
            { errno = ERANGE; result = (result < 0) ? -HUGE_VAL : HUGE_VAL; }
            else if (exp < DBL_MIN_10_EXP)
            { errno = ERANGE; result = 0.0; }
            else if (exp < 0) {
                for (count = 0, exp = -exp; exp; count++, exp >>= 1)
                { if (exp & 1) result /= powerof10[count]; }
            }
            else {
                for (count = 0; exp; count++, exp >>= 1)
                { if (exp & 1) result *= powerof10[count]; }
            }
        }
        else result = ldexp(result, exp);

    if (endptr) *endptr = (char *)(success ? fst : st);
    return result;
}

#if FLT_MANT_DIG == DBL_MANT_DIG
float strtof(const char * __restrict st, char ** __restrict endptr) __attribute__((__alias__("strtod")));
#endif

#if LDBL_MANT_DIG == DBL_MANT_DIG
long double strtold(const char * __restrict st, char ** __restrict endptr) __attribute__((__alias__("strtod")));
#endif

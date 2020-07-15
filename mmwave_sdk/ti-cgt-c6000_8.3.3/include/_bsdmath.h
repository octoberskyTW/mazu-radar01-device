/*****************************************************************************/
/*  _BSDMATH.H                                                              */
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
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
#ifndef _TI_BSD_MATH_H_
#define	_TI_BSD_MATH_H_

#pragma diag_push
#pragma CHECK_MISRA("-6.3") /* standard types required for standard headers */
#pragma CHECK_MISRA("-12.7") /* bitwise operators not allowed on signed ints */
#pragma CHECK_MISRA("-16.4") /* identifiers in fn defn/decl identical??? fabs/fabsf */
#pragma CHECK_MISRA("-19.1") /* only comments and preproc before #include */
#pragma CHECK_MISRA("-19.7") /* macros required for implementation */
#pragma CHECK_MISRA("-20.1") /* standard headers must define standard names */
#pragma CHECK_MISRA("-20.2") /* standard headers must define standard names */

#if __has_include(<sys/_types.h>)
#include <sys/_types.h>
#include <machine/_limits.h>
#else
typedef unsigned long long __uint64_t;
#if defined(__TMS320C2000__) || defined(__MSP430__)
typedef unsigned long __uint32_t;
#define __INT_MAX 32767
#else
typedef unsigned __uint32_t;
#define __INT_MAX  2147483647
#endif
#endif

#if __has_include(<sys/cdefs.h>)
#include <sys/cdefs.h>
#else
#ifdef __cplusplus
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif
#endif

/*
 * ANSI/POSIX
 */

#define	FP_ILOGB0	(-__INT_MAX)
#define	FP_ILOGBNAN	(__INT_MAX)

#if defined(__ARM_FP) && defined(__ARM_FEATURE_FMA)
#if __ARM_FP & 0x4
#define	FP_FAST_FMAF	1
#endif

#if __ARM_FP & 0x8
#define	FP_FAST_FMA	1
#define	FP_FAST_FMAL	1
#endif
#endif

#ifdef __MATH_BUILTIN_RELOPS
#define	isgreater(x, y)		__builtin_isgreater((x), (y))
#define	isgreaterequal(x, y)	__builtin_isgreaterequal((x), (y))
#define	isless(x, y)		__builtin_isless((x), (y))
#define	islessequal(x, y)	__builtin_islessequal((x), (y))
#define	islessgreater(x, y)	__builtin_islessgreater((x), (y))
#define	isunordered(x, y)	__builtin_isunordered((x), (y))
#else
#define	isgreater(x, y)		(!isunordered((x), (y)) && (x) > (y))
#define	isgreaterequal(x, y)	(!isunordered((x), (y)) && (x) >= (y))
#define	isless(x, y)		(!isunordered((x), (y)) && (x) < (y))
#define	islessequal(x, y)	(!isunordered((x), (y)) && (x) <= (y))
#define	islessgreater(x, y)	(!isunordered((x), (y)) && \
					((x) > (y) || (y) > (x)))
#define	isunordered(x, y)	(isnan(x) || isnan(y))
#endif /* __MATH_BUILTIN_RELOPS */

/*
 * XOPEN/SVID
 */
#ifdef __BSD_VISIBLE
#define	M_E		2.7182818284590452354	/* e */
#define	M_LOG2E		1.4426950408889634074	/* log 2e */
#define	M_LOG10E	0.43429448190325182765	/* log 10e */
#define	M_LN2		0.69314718055994530942	/* log e2 */
#define	M_LN10		2.30258509299404568402	/* log e10 */
#define	M_PI		3.14159265358979323846	/* pi */
#define	M_PI_2		1.57079632679489661923	/* pi/2 */
#define	M_PI_4		0.78539816339744830962	/* pi/4 */
#define	M_1_PI		0.31830988618379067154	/* 1/pi */
#define	M_2_PI		0.63661977236758134308	/* 2/pi */
#define	M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
#define	M_SQRT2		1.41421356237309504880	/* sqrt(2) */
#define	M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */
#endif /* __BSD_VISIBLE */

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/* If --fp_mode=relaxed is used and VFP is enabled, use the hardware square  */
/* root directly instead of calling the sqrtx routine. This will not set     */
/* errno if the argument is negative.                                        */
/*                                                                           */
/* This is done by defining sqrt to _relaxed_sqrt to allow other translation */
/* units to use the normal sqrt routine under strict mode.                   */
/*---------------------------------------------------------------------------*/
#if !__TI_STRICT_FP_MODE__
#if __TI_HAS_BUILTIN_SQRT32
#pragma CHECK_MISRA("-19.4") /* macro defined to be an identifier is OK */
#pragma CHECK_MISRA("-8.1") /* function definition with no prototype visible */
#pragma CHECK_MISRA("-8.5") /* function definitions required */
#pragma CHECK_MISRA("-8.11") /* non-static function definition OK */

#pragma diag_suppress 1558 /* --float_operations_allowed checks */

#endif
#endif

/* Disable double_t and float_t for C28x because of Motorware (AY 2015) */
#ifndef __TMS320C28XX__
#define __TI_HAS_FLOAT_DBL_T 1
/* These typedefs depend on the value of FLT_EVAL_METHOD */
typedef	double	double_t;
typedef	float	float_t;
#endif

_CODE_ACCESS double      expm1(double x);
_CODE_ACCESS float       expm1f(float x);
_CODE_ACCESS long double expm1l(long double x);
_CODE_ACCESS int         ilogb(double x);
_CODE_ACCESS int         ilogbf(float x);
_CODE_ACCESS int         ilogbl(long double x);
_CODE_ACCESS double      logb(double x);
_CODE_ACCESS float       logbf(float x);
_CODE_ACCESS long double logbl(long double x);
_CODE_ACCESS double      scalbn(double x, int n);
_CODE_ACCESS float       scalbnf(float x, int n);
_CODE_ACCESS long double scalbnl(long double x, int n);
_CODE_ACCESS double      scalbln(double x, long n);
_CODE_ACCESS float       scalblnf(float x, long n);
_CODE_ACCESS long double scalblnl(long double x, long n);
_CODE_ACCESS double      cbrt(double x);
_CODE_ACCESS float       cbrtf(float x);
_CODE_ACCESS long double cbrtl(long double x);
_CODE_ACCESS double      erf(double x);
_CODE_ACCESS float       erff(float x);
_CODE_ACCESS long double erfl(long double x);
_CODE_ACCESS double      erfc(double x);
_CODE_ACCESS float       erfcf(float x);
_CODE_ACCESS long double erfcl(long double x);
_CODE_ACCESS double      lgamma(double x);
_CODE_ACCESS float       lgammaf(float x);
_CODE_ACCESS long double lgammal(long double x);
_CODE_ACCESS double      tgamma(double x);
_CODE_ACCESS float       tgammaf(float x);
_CODE_ACCESS long double tgammal(long double x);
_CODE_ACCESS double      nearbyint(double x);
_CODE_ACCESS float       nearbyintf(float x);
_CODE_ACCESS long double nearbyintl(long double x);
_CODE_ACCESS double      rint(double x);
_CODE_ACCESS float       rintf(float x);
_CODE_ACCESS long double rintl(long double x);
_CODE_ACCESS long        lrint(double x);
_CODE_ACCESS long        lrintf(float x);
_CODE_ACCESS long        lrintl(long double x);
_CODE_ACCESS long long   llrint(double x);
_CODE_ACCESS long long   llrintf(float x);
_CODE_ACCESS long long   llrintl(long double x);
_CODE_ACCESS long        lround(double x);
_CODE_ACCESS long        lroundf(float x);
_CODE_ACCESS long        lroundl(long double x);
_CODE_ACCESS long long   llround(double x);
_CODE_ACCESS long long   llroundf(float x);
_CODE_ACCESS long long   llroundl(long double x);
_CODE_ACCESS double      remainder(double x, double y);
_CODE_ACCESS float       remainderf(float x, float y);
_CODE_ACCESS long double remainderl(long double x, long double y);
_CODE_ACCESS double      remquo(double x, double y, int *quo);
_CODE_ACCESS float       remquof(float x, float y, int *quo);
_CODE_ACCESS long double remquol(long double x, long double y, int *quo);
_CODE_ACCESS double      nan(const char *tagp);
_CODE_ACCESS float       nanf(const char *tagp);
_CODE_ACCESS long double nanl(const char *tagp);
_CODE_ACCESS double      nextafter(double x, double y);
_CODE_ACCESS float       nextafterf(float x, float y);
_CODE_ACCESS long double nextafterl(long double x, long double y);
_CODE_ACCESS double      nexttoward(double x, long double y);
_CODE_ACCESS float       nexttowardf(float x, long double y);
_CODE_ACCESS long double nexttowardl(long double x, long double y);
_CODE_ACCESS double      fdim(double x, double y);
_CODE_ACCESS float       fdimf(float x, float y);
_CODE_ACCESS long double fdiml(long double x, long double y);
_CODE_ACCESS double      fmax(double x, double y);
_CODE_ACCESS float       fmaxf(float x, float y);
_CODE_ACCESS long double fmaxl(long double x, long double y);
_CODE_ACCESS double      fmin(double x, double y);
_CODE_ACCESS float       fminf(float x, float y);
_CODE_ACCESS long double fminl(long double x, long double y);
_CODE_ACCESS double      fma(double x, double y, double z);
_CODE_ACCESS float       fmaf(float x, float y, float z);
_CODE_ACCESS long double fmal(long double x, long double y, long double z);

#ifdef __cplusplus
    }
#endif

#if defined(_AEABI_PORTABILITY_LEVEL) && _AEABI_PORTABILITY_LEVEL != 0 && \
   !defined(_AEABI_PORTABLE)
#define _AEABI_PORTABLE
#endif

#pragma diag_pop

#endif /* !_TI_BSD_MATH_H_ */

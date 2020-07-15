/*****************************************************************************/
/* stdlib.h                                                                  */
/*                                                                           */
/* Copyright (c) 1993 Texas Instruments Incorporated                         */
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

#ifndef _STDLIB_H_
#define _STDLIB_H_

#if defined(__TMS320C2000__)
#if defined(__TMS320C28XX_CLA__)
#error "Header file <stdlib.h> not supported by CLA compiler"
#endif
#endif

#include <_ti_config.h>

#pragma diag_push
#pragma CHECK_MISRA("-6.3") /* standard types required for standard headers */
#pragma CHECK_MISRA("-8.5") /* need to define inline function */
#pragma CHECK_MISRA("-19.1") /* #includes required for implementation */
#pragma CHECK_MISRA("-19.7") /* need function-like macros */
#pragma CHECK_MISRA("-20.1") /* standard headers must define standard names */
#pragma CHECK_MISRA("-20.2") /* standard headers must define standard names */

/*---------------------------------------------------------------------------*/
/* Attributes are only available in relaxed ANSI mode.                       */
/*---------------------------------------------------------------------------*/
#ifndef __ATTRIBUTE
#if __TI_STRICT_ANSI_MODE__
#define __ATTRIBUTE(attr)
#else
#define __ATTRIBUTE(attr) __attribute__(attr)
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif /* !__cplusplus */

#pragma diag_push
#pragma CHECK_MISRA("-5.7") /* keep names intact */

typedef struct { int quot, rem; } div_t;

#ifndef __ARM_ARCH
typedef struct { long quot, rem; } ldiv_t;
#else /* __ARM_ARCH */
typedef struct { int quot, rem; } ldiv_t;
#endif /* __ARM_ARCH */

#if defined(__TMS320C55X__) || defined(__ARM_ARCH)      || \
    defined(_TMS320C6X)     || defined(__TMS320C2000__) || \
    defined(__ARP32__)      || defined(__MSP430__)      || \
    defined(__PRU__)        || defined(__C7000__)
#define _LLONG_AVAILABLE 1
typedef struct { long long quot, rem; } lldiv_t;
#endif

#pragma diag_pop

#if defined(_AEABI_PORTABILITY_LEVEL) && _AEABI_PORTABILITY_LEVEL != 0
extern int __aeabi_MB_CUR_MAX(void);
#define MB_CUR_MAX ( __aeabi_MB_CUR_MAX() )
#else
#define MB_CUR_MAX    1
#endif /* _AEABI_PORTABILITY_LEVEL */

#ifndef NULL
#define NULL          0
#endif

#ifndef _SIZE_T_DECLARED
#define _SIZE_T_DECLARED
# ifdef __clang__
typedef __SIZE_TYPE__ __SIZE_T_TYPE__;
# endif

typedef __SIZE_T_TYPE__ size_t;
#endif

#ifndef __cplusplus
#ifndef _WCHAR_T_DECLARED
#define _WCHAR_T_DECLARED
# ifdef __clang__
typedef __WCHAR_TYPE__ __WCHAR_T_TYPE__;
# endif

typedef __WCHAR_T_TYPE__ wchar_t;
#endif
#endif

#define EXIT_FAILURE  1
#define EXIT_SUCCESS  0

#define RAND_MAX      32767

#include <_ti_config.h>

/*---------------------------------------------------------------*/
/* NOTE - Normally, abs, labs, and fabs are expanded inline, so  */
/*        no formal definition is really required. However, ANSI */
/*        requires that they exist as separate functions, so     */
/*        they are supplied in the library.  The prototype is    */
/*        here mainly for documentation.                         */
/*---------------------------------------------------------------*/
#pragma diag_push
#pragma CHECK_MISRA("-16.4") /* false positives due to builtin declarations */
    _CODE_ACCESS  int       abs(int _val); 
    _CODE_ACCESS  long      labs(long _val);
#if defined(_LLONG_AVAILABLE)
    _CODE_ACCESS  long long llabs(long long _val);
#endif
#pragma diag_pop

    _CODE_ACCESS int       atoi(const char *_st);
    _CODE_ACCESS long      atol(const char *_st);
#if defined(_LLONG_AVAILABLE)
    _CODE_ACCESS long long atoll(const char *_st);
#endif
    _CODE_ACCESS char     *ltoa(long val, char * buffer, int radix);
          _IDECL double    atof(const char *_st);

    _CODE_ACCESS long      strtol(const char * __restrict _st,
                                  char ** __restrict _endptr, int _base);
    _CODE_ACCESS unsigned long strtoul(const char * __restrict _st,
                                       char ** __restrict _endptr, int _base);
#if defined(_LLONG_AVAILABLE)
    _CODE_ACCESS long long strtoll(const char * __restrict _st,
                                   char ** __restrict _endptr, int _base);
    _CODE_ACCESS unsigned long long strtoull(const char * __restrict _st,
                                             char ** __restrict _endptr,
					     int _base);
#endif
    _CODE_ACCESS float     strtof(const char * __restrict _st,
                                  char ** __restrict _endptr);
    _CODE_ACCESS double    strtod(const char * __restrict _st,
                                  char ** __restrict _endptr);
    _CODE_ACCESS long double strtold(const char * __restrict _st,
                                     char ** __restrict _endptr);
    
    _CODE_ACCESS int    rand(void);
    _CODE_ACCESS void   srand(unsigned _seed);
    
    _CODE_ACCESS void  *calloc(size_t _num, size_t _size)
               __ATTRIBUTE((malloc));
    _CODE_ACCESS void  *malloc(size_t _size)
               __ATTRIBUTE((malloc));
    _CODE_ACCESS void  *realloc(void *_ptr, size_t _size)
               __ATTRIBUTE((malloc));
    _CODE_ACCESS void   free(void *_ptr);
    _CODE_ACCESS void  *memalign(size_t _aln, size_t _size)
               __ATTRIBUTE((malloc));
    
    _TI_NORETURN _CODE_ACCESS void abort(void) _TI_NOEXCEPT_CPP14;

    typedef void (*__TI_atexit_fn)(void);
    _CODE_ACCESS int    atexit(__TI_atexit_fn _func) _TI_NOEXCEPT_CPP14;

    typedef int (*__TI_compar_fn)(const void *_a,const void *_b);
    _CODE_ACCESS void  *bsearch(const void *_key, const void *_base,
                                size_t _nmemb, size_t _size, 
                                __TI_compar_fn compar);
    _CODE_ACCESS void   qsort(void *_base, size_t _nmemb, size_t _size, 
                              __TI_compar_fn compar);

    _TI_NORETURN _CODE_ACCESS void exit(int _status);
#ifdef _TI_C99LIB
    _TI_NORETURN _CODE_ACCESS void _Exit(int _status);
#endif
    
    _CODE_ACCESS div_t  div(int _numer, int _denom);
    _CODE_ACCESS ldiv_t ldiv(long _numer, long _denom);
#if defined(_LLONG_AVAILABLE)
    _CODE_ACCESS lldiv_t lldiv(long long _numer, long long _denom);
#endif

    _CODE_ACCESS char  *getenv(const char *_string);
    _CODE_ACCESS int    system(const char *_name);

    _CODE_ACCESS int    mblen(const char *_s, size_t _n);
    _CODE_ACCESS size_t mbstowcs(wchar_t * __restrict _dest,
                                 const char * __restrict _src, size_t _n);
    _CODE_ACCESS int    mbtowc(wchar_t * __restrict _dest,
                               const char * __restrict _src, size_t _n);

    _CODE_ACCESS size_t wcstombs(char * __restrict _dest,
                                 const wchar_t * __restrict _src, size_t _n);
    _CODE_ACCESS int    wctomb(char *_s, wchar_t _wc);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */


#ifdef _INLINE

static __inline double atof(const char *_st) 
{
  return strtod(_st, (char **)0); 
}

#endif  /* _INLINE */

#ifdef __cplusplus
/*****************************************************************************/
/* If we leave these active when in relaxed ANSI mode, we get infinite       */
/* recursion due to changes in type matching.  See comment in                */
/* ansi/sys_predef.c line 4377 on why we specifically check the              */
/* __TI_STRICT_ANSI_MODE__ macro here and its relation to strict ANSI and    */
/* relaxed ANSI parser modes.                                                */
/*****************************************************************************/
#if __TI_STRICT_ANSI_MODE__
    _CODE_ACCESS inline int atexit(void (*func)(void)) _TI_NOEXCEPT_CPP14
        {
            return atexit((__TI_atexit_fn)func);
        }

    _CODE_ACCESS inline void  *bsearch(const void *_key, const void *_base,
                                       size_t _nmemb, size_t _size, 
                                       int (*compar)(const void *,const void *))
        {
            return bsearch(_key, _base, _nmemb, _size, (__TI_compar_fn)compar);
        }

    _CODE_ACCESS inline void   qsort(void *_base, size_t _nmemb, size_t _size, 
                                     int (*_compar)(const void *, const void *))
        {
            return qsort(_base, _nmemb, _size, (__TI_compar_fn)_compar);
        }
#endif
#endif

#pragma diag_pop

#if defined(_AEABI_PORTABILITY_LEVEL) && _AEABI_PORTABILITY_LEVEL != 0 && \
   !defined(_AEABI_PORTABLE)
#define _AEABI_PORTABLE
#endif

#endif  /* ! _STDLIB_H_ */

#pragma diag_push

/* C2000-specific additions to header implemented with #include */
#pragma CHECK_MISRA("-19.1")
#pragma CHECK_MISRA("-19.15")

#if defined(__TMS320C2000__)
#include <stdlibf.h>     /* far versions of stdlib fns */
#endif

/*----------------------------------------------------------------------------*/
/* If sys/cdefs.h is available, go ahead and include it. xlocale.h assumes    */
/* this file will have already included sys/cdefs.h.                          */
/*----------------------------------------------------------------------------*/
#if __has_include(<sys/cdefs.h>)
#include <sys/cdefs.h>
#endif

/*----------------------------------------------------------------------------*/
/* Include xlocale/_stdlib.h if xlocale.h has already been included. This     */
/* comes from FreeBSD's stdlib.h.                                             */
/*----------------------------------------------------------------------------*/
#ifdef _XLOCALE_H_
#include <sys/_types.h>
__BEGIN_DECLS
#include <xlocale/_stdlib.h>
__END_DECLS
#endif

#pragma diag_pop

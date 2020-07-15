/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++ Runtime                            - | \^/ | -      *
*                                                               \   /         *
*                                                             /  | |  \       *
* Copyright 1992-2017 Edison Design Group Inc.                   [_]          *
*                                                                             *
******************************************************************************/
/*
Redistribution and use in source and binary forms are permitted
provided that the above copyright notice and this paragraph are
duplicated in all source code forms.  The name of Edison Design
Group, Inc. may not be used to endorse or promote products derived
from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
Any use of this software is at the user's own risk.
*/

/*

c99_cmplex.c -- Runtime support for lowered complex operations in C99.
                This implementation is for demonstration and testing
                purposes only.  It is neither particularly efficient, nor
                particularly precise (numerically speaking).

*/

/* Include the definition of EXTERN_C. */
#include "basics.h"

typedef struct _Complex_float {
  /* Lowered representation of the C99 type "_Complex float". */
  float _Vals[2];
} _Complex_float;


typedef struct _Complex_double {
  /* Lowered representation of the C99 type "_Complex double". */
  double _Vals[2];
} _Complex_double;


typedef struct _Complex_long_double {
  /* Lowered representation of the C99 type "_Complex long double". */
  long double _Vals[2];
} _Complex_long_double;

#if __EDG_FLOAT80_ENABLING_POSSIBLE
typedef struct _Complex_float80 {
  /* Lowered representation of the C99 type with two __float80 entities. */
  __float80 _Vals[2];
} _Complex_float80;
#endif /* __EDG_FLOAT80_ENABLING_POSSIBLE */

#if __EDG_FLOAT128_ENABLING_POSSIBLE
typedef struct _Complex_float128 {
  /* Lowered representation of the C99 type with two __float128 entities. */
  __float128 _Vals[2];
} _Complex_float128;
#endif /* __EDG_FLOAT128_ENABLING_POSSIBLE */

/*
Compute -z in lowered representation.
*/
#define NEGATE(name, ret, param1)                                             \
EXTERN_C ret name(param1 z)                                                   \
{                                                                             \
  z._Vals[0] = -z._Vals[0];                                                   \
  z._Vals[1] = -z._Vals[1];                                                   \
  return z;                                                                   \
}  /* NEGATE */

/*
Compute the complex conjugate of z in lowered representation.
(This is currently only needed to support the GNU complex "~" operator.)
*/
#define CONJ(name, ret, param1)                                               \
EXTERN_C ret name(param1 z)                                                   \
{                                                                             \
  z._Vals[1] = -z._Vals[1];                                                   \
  return z;                                                                   \
}  /* CONJ */

/*
Compute z1+z2 in lowered representation.
*/
#define ADD(name, ret, param1, param2)                                        \
EXTERN_C ret name(param1 z1, param2 z2)                                       \
{                                                                             \
  ret r;                                                                      \
  r._Vals[0] = z1._Vals[0] + z2._Vals[0];                                     \
  r._Vals[1] = z1._Vals[1] + z2._Vals[1];                                     \
  return r;                                                                   \
}  /* ADD */

/*
Compute z1-z2 in lowered representation.
*/
#define SUBTRACT(name, ret, param1, param2)                                   \
EXTERN_C ret name(param1 z1, param2 z2)                                       \
{                                                                             \
  ret r;                                                                      \
  r._Vals[0] = z1._Vals[0] - z2._Vals[0];                                     \
  r._Vals[1] = z1._Vals[1] - z2._Vals[1];                                     \
  return r;                                                                   \
}  /* SUBTRACT */

/*
Compute z1*z2 in lowered representation.
*/
#define MULTIPLY(name, ret, param1, param2)                                   \
EXTERN_C ret name(param1 z1, param2 z2)                                       \
{                                                                             \
  ret r;                                                                      \
  r._Vals[0] = z1._Vals[0] * z2._Vals[0] - z1._Vals[1] * z2._Vals[1];         \
  r._Vals[1] = z1._Vals[0] * z2._Vals[1] + z1._Vals[1] * z2._Vals[0];         \
  return r;                                                                   \
}  /* MULTIPLY */

/*
Compute z1/z2 in lowered representation.
*/
#define DIVIDE(name, ret, param1, param2, temp_type)                          \
EXTERN_C ret name(param1 z1, param2 z2)                                       \
{                                                                             \
  ret r;                                                                      \
  temp_type d = z2._Vals[0] * z2._Vals[0] + z2._Vals[1] * z2._Vals[1];        \
  r._Vals[0] = (z1._Vals[0] * z2._Vals[0] + z1._Vals[1] * z2._Vals[1]) / d;   \
  r._Vals[1] = (z1._Vals[1] * z2._Vals[0] - z1._Vals[0] * z2._Vals[1]) / d;   \
  return r;                                                                   \
}  /* DIVIDE */

/*
Compute z1==z2 in lowered representation.
*/
#define EQ(name, ret, param1, param2)                                         \
EXTERN_C ret name(param1 z1, param2 z2)                                       \
{                                                                             \
  return z1._Vals[0] == z2._Vals[0] && z1._Vals[1] == z2._Vals[1];            \
}  /* EQ */

/*
Compute z1!=z2 in lowered representation.
*/
#define NE(name, ret, param1, param2)                                         \
EXTERN_C ret name(param1 z1, param2 z2)                                       \
{                                                                             \
  return z1._Vals[0] != z2._Vals[0] || z1._Vals[1] != z2._Vals[1];            \
}  /* NE */

/*
Adjust precision of complex value.
*/
#define CAST(name, ret, param1, cast_type)                                    \
EXTERN_C ret name(param1 z)                                                   \
{                                                                             \
  ret r;                                                                      \
  r._Vals[0] = (cast_type)z._Vals[0];                                         \
  r._Vals[1] = (cast_type)z._Vals[1];                                         \
  return r;                                                                   \
}  /* CAST */

/*
Promote imaginary value to complex value.
*/
#define ITOC(name, ret, param1)                                               \
EXTERN_C ret name(param1 j)                                                   \
{                                                                             \
  ret r;                                                                      \
  r._Vals[0] = (param1)0.0;                                                   \
  r._Vals[1] = (param1)j;                                                     \
  return r;                                                                   \
}  /* ITOC */

/*
Promote real value to complex value.
*/
#define RTOC(name, ret, param1)                                               \
EXTERN_C ret name(param1 j)                                                   \
{                                                                             \
  ret r;                                                                      \
  r._Vals[0] = (param1)j;                                                     \
  r._Vals[1] = (param1)0.0;                                                   \
  return r;                                                                   \
}  /* RTOC */

/*
Imaginary part of a complex value.
*/
#define CTOI(name, ret, param1)                                               \
EXTERN_C ret name(param1 z)                                                   \
{                                                                             \
  return z._Vals[1];                                                          \
}  /* CTOI */

/*
Real part of a complex value.
*/
#define CTOR(name, ret, param1)                                               \
EXTERN_C ret name(param1 z)                                                   \
{                                                                             \
  return z._Vals[0];                                                          \
}  /* CTOR */

/* Single precision (float) complex routines. */
NEGATE  (__c99_complex_float_negate, _Complex_float, _Complex_float)
CONJ    (__c99_complex_float_conj, _Complex_float, _Complex_float)
ADD     (__c99_complex_float_add, _Complex_float, _Complex_float,
                                  _Complex_float)
SUBTRACT(__c99_complex_float_subtract, _Complex_float, _Complex_float,
                                       _Complex_float)
MULTIPLY(__c99_complex_float_multiply, _Complex_float, _Complex_float,
                                       _Complex_float)
DIVIDE  (__c99_complex_float_divide, _Complex_float, _Complex_float,
                                     _Complex_float, float)
EQ      (__c99_complex_float_eq, int, _Complex_float, _Complex_float)
NE      (__c99_complex_float_ne, int, _Complex_float, _Complex_float)
ITOC    (__c99_ifloat_to_cfloat, _Complex_float, float)
RTOC    (__c99_float_to_cfloat, _Complex_float, float)
CTOI    (__c99_cfloat_to_ifloat, float, _Complex_float)
CTOR    (__c99_cfloat_to_float, float, _Complex_float)
CAST    (__c99_cfloat_to_cdouble, _Complex_double, _Complex_float, double)
CAST    (__c99_cfloat_to_clong_double, _Complex_long_double, _Complex_float,
                                       long double)
#if __EDG_FLOAT80_ENABLING_POSSIBLE
CAST    (__c99_cfloat_to_cfloat80, _Complex_float80, _Complex_float, __float80)
#endif /* __EDG_FLOAT80_ENABLING_POSSIBLE */
#if __EDG_FLOAT128_ENABLING_POSSIBLE
CAST    (__c99_cfloat_to_cfloat128, _Complex_float128, _Complex_float,
                                    __float128)
#endif /* __EDG_FLOAT128_ENABLING_POSSIBLE */

/* Double precision (double) complex routines. */
NEGATE  (__c99_complex_double_negate, _Complex_double, _Complex_double)
CONJ    (__c99_complex_double_conj, _Complex_double, _Complex_double)
ADD     (__c99_complex_double_add, _Complex_double, _Complex_double,
                                   _Complex_double)
SUBTRACT(__c99_complex_double_subtract, _Complex_double, _Complex_double,
                                        _Complex_double)
MULTIPLY(__c99_complex_double_multiply, _Complex_double, _Complex_double,
                                        _Complex_double)
DIVIDE  (__c99_complex_double_divide, _Complex_double, _Complex_double,
                                      _Complex_double, double)
EQ      (__c99_complex_double_eq, int, _Complex_double, _Complex_double)
NE      (__c99_complex_double_ne, int, _Complex_double, _Complex_double)
ITOC    (__c99_idouble_to_cdouble, _Complex_double, double)
RTOC    (__c99_double_to_cdouble, _Complex_double, double)
CTOI    (__c99_cdouble_to_idouble, double, _Complex_double)
CTOR    (__c99_cdouble_to_double, double, _Complex_double)
CAST    (__c99_cdouble_to_cfloat, _Complex_float, _Complex_double, float)
CAST    (__c99_cdouble_to_clong_double, _Complex_long_double, _Complex_double,
                                        long double)
#if __EDG_FLOAT80_ENABLING_POSSIBLE
CAST    (__c99_cdouble_to_cfloat80, _Complex_float80, _Complex_double,
                                    __float80)
#endif /* __EDG_FLOAT80_ENABLING_POSSIBLE */
#if __EDG_FLOAT128_ENABLING_POSSIBLE
CAST    (__c99_cdouble_to_cfloat128, _Complex_float128, _Complex_double,
                                     __float128)
#endif /* __EDG_FLOAT128_ENABLING_POSSIBLE */

/* Extended precision (long double) complex routines. */
NEGATE  (__c99_complex_long_double_negate, _Complex_long_double,
                                           _Complex_long_double)
CONJ    (__c99_complex_long_double_conj, _Complex_long_double,
                                         _Complex_long_double)
ADD     (__c99_complex_long_double_add, _Complex_long_double,
                                        _Complex_long_double,
                                        _Complex_long_double)
SUBTRACT(__c99_complex_long_double_subtract, _Complex_long_double,
                                             _Complex_long_double,
                                             _Complex_long_double)
MULTIPLY(__c99_complex_long_double_multiply, _Complex_long_double,
                                             _Complex_long_double,
                                             _Complex_long_double)
DIVIDE  (__c99_complex_long_double_divide, _Complex_long_double,
                                           _Complex_long_double,
                                           _Complex_long_double, long double)
EQ      (__c99_complex_long_double_eq, int, _Complex_long_double,
                                       _Complex_long_double)
NE      (__c99_complex_long_double_ne, int, _Complex_long_double,
                                       _Complex_long_double)
ITOC    (__c99_ilong_double_to_clong_double, _Complex_long_double, long double)
RTOC    (__c99_long_double_to_clong_double, _Complex_long_double, long double)
CTOI    (__c99_clong_double_to_ilong_double, long double, _Complex_long_double)
CTOR    (__c99_clong_double_to_long_double, long double, _Complex_long_double)
CAST    (__c99_clong_double_to_cfloat, _Complex_float, _Complex_long_double,
                                       float)
CAST    (__c99_clong_double_to_cdouble, _Complex_double, _Complex_long_double,
                                        double)
#if __EDG_FLOAT80_ENABLING_POSSIBLE
CAST    (__c99_clong_double_to_cfloat80, _Complex_float80,
                                         _Complex_long_double, __float80)
#endif /* __EDG_FLOAT80_ENABLING_POSSIBLE */
#if __EDG_FLOAT128_ENABLING_POSSIBLE
CAST    (__c99_clong_double_to_cfloat128, _Complex_float128,
                                          _Complex_long_double, __float128)
#endif /* __EDG_FLOAT128_ENABLING_POSSIBLE */

#if __EDG_FLOAT80_ENABLING_POSSIBLE
/* GCC-compatible __float80 complex routines. */
NEGATE  (__c99_complex_float80_negate, _Complex_float80, _Complex_float80)
CONJ    (__c99_complex_float80_conj, _Complex_float80, _Complex_float80)
ADD     (__c99_complex_float80_add, _Complex_float80, _Complex_float80,
                                    _Complex_float80)
SUBTRACT(__c99_complex_float80_subtract, _Complex_float80, _Complex_float80,
                                         _Complex_float80)
MULTIPLY(__c99_complex_float80_multiply, _Complex_float80, _Complex_float80,
                                         _Complex_float80)
DIVIDE  (__c99_complex_float80_divide, _Complex_float80, _Complex_float80,
                                       _Complex_float80, __float80)
EQ      (__c99_complex_float80_eq, int, _Complex_float80, _Complex_float80)
NE      (__c99_complex_float80_ne, int, _Complex_float80, _Complex_float80)
ITOC    (__c99_ifloat80_to_cfloat80, _Complex_float80, __float80)
RTOC    (__c99_float80_to_cfloat80, _Complex_float80, __float80)
CTOI    (__c99_cfloat80_to_ifloat80, __float80, _Complex_float80)
CTOR    (__c99_cfloat80_to_float80, __float80, _Complex_float80)
CAST    (__c99_cfloat80_to_cfloat, _Complex_float, _Complex_float80, float)
CAST    (__c99_cfloat80_to_cdouble, _Complex_double, _Complex_float80, double)
CAST    (__c99_cfloat80_to_clong_double, _Complex_long_double,
                                         _Complex_float80, long double)
#if __EDG_FLOAT128_ENABLING_POSSIBLE
CAST    (__c99_cfloat80_to_cfloat128, _Complex_float128, _Complex_float80,
                                      __float128)
#endif /* __EDG_FLOAT128_ENABLING_POSSIBLE */
#endif /* __EDG_FLOAT80_ENABLING_POSSIBLE */

#if __EDG_FLOAT128_ENABLING_POSSIBLE
/* GCC-compatible __float128 complex routines. */
NEGATE  (__c99_complex_float128_negate, _Complex_float128, _Complex_float128)
CONJ    (__c99_complex_float128_conj, _Complex_float128, _Complex_float128)
ADD     (__c99_complex_float128_add, _Complex_float128, _Complex_float128,
                                     _Complex_float128)
SUBTRACT(__c99_complex_float128_subtract, _Complex_float128, _Complex_float128,
                                          _Complex_float128)
MULTIPLY(__c99_complex_float128_multiply, _Complex_float128, _Complex_float128,
                                          _Complex_float128)
DIVIDE  (__c99_complex_float128_divide, _Complex_float128, _Complex_float128,
                                        _Complex_float128, __float128)
EQ      (__c99_complex_float128_eq, int, _Complex_float128, _Complex_float128)
NE      (__c99_complex_float128_ne, int, _Complex_float128, _Complex_float128)
ITOC    (__c99_ifloat128_to_cfloat128, _Complex_float128, __float128)
RTOC    (__c99_float128_to_cfloat128, _Complex_float128, __float128)
CTOI    (__c99_cfloat128_to_ifloat128, __float128, _Complex_float128)
CTOR    (__c99_cfloat128_to_float128, __float128, _Complex_float128)
CAST    (__c99_cfloat128_to_cfloat, _Complex_float, _Complex_float128, float)
CAST    (__c99_cfloat128_to_cdouble, _Complex_double, _Complex_float128,
                                     double)
CAST    (__c99_cfloat128_to_clong_double, _Complex_long_double,
                                          _Complex_float128, long double)
#if __EDG_FLOAT80_ENABLING_POSSIBLE
CAST    (__c99_cfloat128_to_cfloat80, _Complex_float80, _Complex_float128,
                                      __float80)
#endif /* __EDG_FLOAT80_ENABLING_POSSIBLE */
#endif /* __EDG_FLOAT128_ENABLING_POSSIBLE */

/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++ Runtime                            - | \^/ | -      *
*                                                               \   /         *
*                                                             /  | |  \       *
* Copyright 1992-2017 Edison Design Group Inc.                   [_]          *
*                                                                             *
******************************************************************************/

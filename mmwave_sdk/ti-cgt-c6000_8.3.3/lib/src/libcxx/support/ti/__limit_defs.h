// -*- C++ -*-
//===--------------------- support/ti/limits.h ----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_SUPPORT_TI_LIMIT_DEFS_H
#define _LIBCPP_SUPPORT_TI_LIMIT_DEFS_H

#include <__config>
#include <float.h>  // FP Limits

#define __DBL_DENORM_MIN__ (0.0)
#define __DBL_DIG__ DBL_DIG
#define __DBL_EPSILON__ DBL_EPSILON
#define __DBL_MANT_DIG__ DBL_MANT_DIG
#define __DBL_MAX__ DBL_MAX
#define __DBL_MAX_10_EXP__ DBL_MAX_10_EXP
#define __DBL_MAX_EXP__ DBL_MAX_EXP
#define __DBL_MIN__ DBL_MIN
#define __DBL_MIN_10_EXP__ DBL_MIN_10_EXP
#define __DBL_MIN_EXP__ DBL_MIN_EXP

#define __FLT_DENORM_MIN__ (0.0f)
#define __FLT_DIG__ FLT_DIG
#define __FLT_EPSILON__ FLT_EPSILON
#define __FLT_MANT_DIG__ FLT_MANT_DIG
#define __FLT_MAX__ FLT_MAX
#define __FLT_MAX_10_EXP__ FLT_MAX_10_EXP
#define __FLT_MAX_EXP__ FLT_MAX_EXP
#define __FLT_MIN__ FLT_MIN
#define __FLT_MIN_10_EXP__ FLT_MIN_10_EXP
#define __FLT_MIN_EXP__ FLT_MIN_EXP
#define __FLT_RADIX__ FLT_RADIX

#define __LDBL_DENORM_MIN__ (0.0l)
#define __LDBL_DIG__ LDBL_DIG
#define __LDBL_EPSILON__ LDBL_EPSILON
#define __LDBL_MANT_DIG__ LDBL_MANT_DIG
#define __LDBL_MAX__ LDBL_MAX
#define __LDBL_MAX_10_EXP__ LDBL_MAX_10_EXP
#define __LDBL_MAX_EXP__ LDBL_MAX_EXP
#define __LDBL_MIN__ LDBL_MIN
#define __LDBL_MIN_10_EXP__ LDBL_MIN_10_EXP
#define __LDBL_MIN_EXP__ LDBL_MIN_EXP

#endif // _LIBCPP_SUPPORT_TI_LIMITS_H

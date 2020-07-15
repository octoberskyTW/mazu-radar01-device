/* ======================================================================== *
 * MATHLIB -- TI Floating-Point Math Function Library                       *
 *                                                                          *
 *                                                                          *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/   *
 *                                                                          *
 *                                                                          *
 *  Redistribution and use in source and binary forms, with or without      *
 *  modification, are permitted provided that the following conditions      *
 *  are met:                                                                *
 *                                                                          *
 *    Redistributions of source code must retain the above copyright        *
 *    notice, this list of conditions and the following disclaimer.         *
 *                                                                          *
 *    Redistributions in binary form must reproduce the above copyright     *
 *    notice, this list of conditions and the following disclaimer in the   *
 *    documentation and/or other materials provided with the                *
 *    distribution.                                                         *
 *                                                                          *
 *    Neither the name of Texas Instruments Incorporated nor the names of   *
 *    its contributors may be used to endorse or promote products derived   *
 *    from this software without specific prior written permission.         *
 *                                                                          *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     *
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       *
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   *
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT    *
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT        *
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   *
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   *
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT     *
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   *
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    *
 * ======================================================================== */

/* ======================================================================= */
/* divsp_i.h - single precision floating point division                    */
/*              optimized inlined C implementation (w/ intrinsics)         */
/* ======================================================================= */

#ifndef DIVSP_I_
#define DIVSP_I_ 1

#include <ti/mathlib/src/common/common.h>

#ifndef __cplusplus         /* FOR PROTECTION PURPOSE - C++ NOT SUPPORTED. */
#pragma CODE_SECTION(divsp_i, ".text:optci");
#endif

static inline float divsp_i (float a, float b)
{
  float TWO  = 2.0;
  float Maxe = 3.402823466E+38;
  float X;

  X = _rcpsp(b);
  X = X*(TWO - b*X);
  X = X*(TWO - b*X);
  X = a*X;

  if (a == 0.0f) {     
    X = 0.0f;
  }
  
  if (_fabsf(b) > Maxe && _fabs(a) <= Maxe) {     
    X = 0.0f;
  }
  
  return (X);
}

#endif


/* ======================================================================== */
/*  End of file: divsp_i.h                                                  */
/* ======================================================================== */

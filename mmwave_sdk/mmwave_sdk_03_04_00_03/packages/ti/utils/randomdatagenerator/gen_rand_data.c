/**
 *   @file  gen_rand_data.c
 *
 *   @brief
 *      Generate random value.
 *
 *  \par
 *  NOTE:
 *      (C) Copyright 2016 Texas Instruments, Inc.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Standard Include Files. */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "gen_rand_data.h"

/**
*  @b Description
*  @n
*  Generates Gausian distributed random complex number, with specified variance
*
*  @param        [in]       NoiseVariance   : the specified noise variance.
*  @param        [out]      pxn             : generated complex value, real value.
*  @param        [out]      pyn             : generated complex value, imag value.
*
*  @retval None
*
*/
void GaussianNoise(
        float NoiseVariance,
        float *pxn,
        float *pyn)
{

    float y, dx2, pi2, r, t, temp;
    const float pi = (float)3.1415926535897;
    uint16_t itemp1;
    float gauss_var;

    pi2 = 2.f * pi;
    gauss_var = NoiseVariance/2; /* half per dimension */

    itemp1 = RandSimple();
    while(itemp1 == 0)
        itemp1 = RandSimple();
    r = (float)(itemp1)/32767.0f;

    temp = 2.f*gauss_var*(float)log(1./r);
    y = (float)sqrt(temp);

    itemp1 = RandSimple();
    t = (float)(itemp1)/32767.0f;

    dx2 = pi2*t;
    *pxn = y*(float)cos(dx2);
    *pyn = y*(float)sin(dx2);
}

/**
*  @b Description
*  @n
*    Generates a random number 0 - 0x7fff
*
*  @retval The generated random value in uint16_t.
*
*/
uint16_t RandSimple(void)
{
    static int64_t next = 1;
    uint16_t ret2;

    next = (next * 16807) % 2147483647;
    ret2 = (uint16_t)(next & 0x7fff);

    return (ret2);
}


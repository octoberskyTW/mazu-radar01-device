/*****************************************************************************/
/* copy_decompress_none.c                                                    */
/*                                                                           */
/* Copyright (c) 2006 Texas Instruments Incorporated                         */
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
/*                                                                           */
/* Copy routine used by compressed cinit copy table. Given an input buffer   */
/* with number of bytes followed by the data, this routine copies the data   */
/* to the output buffer.                                                     */
/*                                                                           */
/* NOTE:                                                                     */
/* 1. This routine could be used to copy uninitialized or initialized global */
/*    data space of a program. Hence this routine cannot define any global   */
/*    variable.                                                              */
/* 2. This routine will never be used to initialize stack space and hence    */
/*    all the variables are allocated to stack.                              */
/* 3. The calling application should ensure the output buffer is big         */
/*    enough to hold the uncompressed data.                                  */
/*                                                                           */
/*****************************************************************************/
#include <stddef.h>
#include <string.h> /* memcpy */

/*****************************************************************************/
/*                                                                           */
/* __TI_COPY_DECODE_NONE() - The input buffer has the number of byte to be   */
/*                           copied at the first 4-byte aligned address.     */
/*                           This is followed by the data to be copied. This */
/*                           routine copies this data to the outbuf.         */
/*                              |32-bit copy size|n-byte copy data |         */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* MSP copy tables can handle moving functions even in small data model +    */
/* large code model, where data pointers are not big enough to represent     */
/* function pointers.  This requires the EABI decompression functions        */
/* (SHARED/copy_*.c) to be changed to accept "far" pointers.  For this       */
/* memory model combination, the decompression functions are changed to use  */
/* "unsigned long" to represent function pointers, so function pointers      */
/* through which we call these functions also needs to have a prototype      */
/* accepting "unsigned long" instead of pointer types.  All other memory     */
/* model combinations use the same prototype that all the other targets use: */
/* two data pointer arguments.  Ultimately we use MSP peek/poke intrinsics   */
/* to read/write the "far" memory.                                           */
/*****************************************************************************/
#if defined(__MSP430__) && defined(__LARGE_CODE_MODEL__) && !defined(__LARGE_DATA_MODEL__)
typedef unsigned long recordsize_t;
typedef unsigned long pointer_t;
typedef unsigned long pointer_to_const_t;
#define READSZ(x) __data20_read_long(x)
#define WRITE8_ADV(x, c) __data20_write_char(x++, c)
void __memcpy_far(pointer_t, pointer_t, recordsize_t);
#else
#if defined(__MSP430__) && defined(__LARGE_CODE_MODEL__)
typedef       unsigned long  recordsize_t;
#else
typedef              size_t  recordsize_t;
#endif
typedef       unsigned char *pointer_t;
typedef const unsigned char *pointer_to_const_t;
#define READSZ(x) (*(recordsize_t *)x)
#define WRITE8_ADV(x, c) (*x++ = (c))
#endif

#pragma CODE_SECTION(__TI_decompress_none, ".text:decompress:none")

void __TI_decompress_none(pointer_to_const_t inbuf, pointer_t outbuf)
{
   /*------------------------------------------------------------------------*/
   /* inbuf will always be pointing one byte into the compressed data (the   */
   /* first byte was read by autoinit to figure out which decompression      */
   /* routine to use).  Align inbuf to a size_t boundary and read the number */
   /* of bytes to be copied.  Then call memcpy to copy that many bytes.      */
   /*------------------------------------------------------------------------*/
   pointer_t count_p = (pointer_t)inbuf + (__alignof__(recordsize_t) - 1);
   recordsize_t count = READSZ(count_p); count_p += sizeof(recordsize_t);

#if defined(__MSP430__) && defined(__LARGE_CODE_MODEL__) && !defined(__LARGE_DATA_MODEL__)
   __memcpy_far(outbuf, count_p, count);
#else
   memcpy(outbuf, (const unsigned char*)count_p, count);
#endif
}

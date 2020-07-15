/*****************************************************************************/
/* copy_zero_init.c                                                          */
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
/* Routine to initialize the output buffer with a zero. The input buffer has */
/* the number of bytes to zero initialize.                                   */
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
#include <string.h>
#include <stddef.h>

/*****************************************************************************/
/*                                                                           */
/* __TI_ZERO_INIT() - Zero initialize the output buffer. The number of bytes */
/*                    to initialize is given in the input buffer.            */
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

static __inline __attribute__((always_inline))
void __TI_zero_init_template(pointer_to_const_t inbuf, pointer_t outbuf,
                             int USE_MEMSET)
{
   /*------------------------------------------------------------------------*/
   /* inbuf will always be pointing one byte into the compressed data (the   */
   /* first byte was read by autoinit to figure out which decompression      */
   /* routine to use).  Align inbuf to a size_t boundary and read the number */
   /* of bytes to be set to zero.                                            */
   /*------------------------------------------------------------------------*/
   pointer_t count_p = (pointer_t)inbuf + (__alignof__(recordsize_t) - 1);
   recordsize_t count = READSZ(count_p);

   /*------------------------------------------------------------------------*/
   /* Zero initialize the output buffer.                                     */
   /*------------------------------------------------------------------------*/
   #if __MSP430__
      while(count--) WRITE8_ADV(outbuf, 0);
   #else

      if (USE_MEMSET)
         memset((void*)outbuf, 0, count);
      else
         while(count--) WRITE8_ADV(outbuf, 0);
   #endif
}

/******************************************************************************/
/* We cannot include specializations when virtual encoding is enabled.        */
/* Vritual encodings from all sections are stored in a single .encode section */
/* which may reference the .text sections. This means that if one .text       */
/* section in a file is referenced, all .text sections will be included in    */
/* the link. This breaks the specialization model which requires all          */
/* specializatinos to be in their own subsections and removeable by the       */
/* linker.                                                                    */
/******************************************************************************/
#if !defined(__VIRTUAL_ENCODING__)
__attribute__((section(".text:decompress:ZI:__TI_zero_init_nomemset"), used))
void __TI_zero_init_nomemset(pointer_to_const_t inbuf, pointer_t outbuf)
{
   __TI_zero_init_template(inbuf, outbuf, 0);
}
#endif

__attribute__((section(".text:decompress:ZI")))
void __TI_zero_init(pointer_to_const_t inbuf, pointer_t outbuf)
{
   __TI_zero_init_template(inbuf, outbuf, 1);
}

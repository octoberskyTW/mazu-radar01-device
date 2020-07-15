/*
 *  Copyright 2018 by Texas Instruments Incorporated.
 *
 */

/*****************************************************************************/
/* BOOT.C          - Initialize the MSP430 C runtime environment             */
/*                                                                           */
/* Copyright (c) 2003-2018, Texas Instruments Incorporated                   */
/* All rights reserved.                                                      */
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
#include <_lock.h>
#include "boot_hooks.h"

#include <xdc/runtime/Startup.h>
extern int xdc_runtime_Startup__RESETFXN__C;
extern void xdc_runtime_System_exit__E(int status);

/* this function is defined by link.xdt */
extern void ti_targets_msp430_rts430_noexit__I(int status);

#ifdef __TI_RTS_BUILD
/*---------------------------------------------------------------------------*/
/* __TI_default_c_int00 indicates that the default TI entry routine is being  */
/* used.  The linker makes assumptions about what exit does when this symbol */
/* is seen. This symbols should NOT be defined if a customized exit routine  */
/* is used.                                                                  */
/*---------------------------------------------------------------------------*/
__asm("__TI_default_c_int00 .set 1");
#endif

/*---------------------------------------------------------------------------*/
/* Allocate the memory for the system stack.  This section will be sized     */
/* by the linker.                                                            */
/*---------------------------------------------------------------------------*/
__attribute__((section(".stack")))
#if defined(__LARGE_DATA_MODEL__)
long _stack;
#else
int _stack;
#endif

__asm("\t.global _c_int00");
__asm("\t.global _reset_vector");
__asm("\t.sect   \".reset\"");
__asm("\t.align  2");
__asm("_reset_vector:\n\t.field _c_int00, 16");

/*---------------------------------------------------------------------------*/
/* Macro to initialize stack pointer.  Stack grows towards lower memory.     */
/*---------------------------------------------------------------------------*/
__asm("\t.global __STACK_END");
#if defined(__LARGE_DATA_MODEL__)
#define STACK_INIT() __asm("\t   MOVX.A\t   #__STACK_END,SP")
#else
#define STACK_INIT() __asm("\t   MOV.W\t    #__STACK_END,SP")
#endif

/*---------------------------------------------------------------------------*/
/* Macro for the declaration of _c_int00 and related routines.               */
/*---------------------------------------------------------------------------*/
#if defined(__LARGE_CODE_MODEL__)
#define CSTART_DECL __attribute__((section(".text:_isr"))) void __interrupt
#else
#define CSTART_DECL void __interrupt
#endif

/*---------------------------------------------------------------------------*/
/* Extern declarations.                                                      */
/*---------------------------------------------------------------------------*/
extern int  _args_main();
extern void exit(int status);
extern void _auto_init();
extern void __mpu_init(void);
extern int  main(int argc);

static __inline __attribute__((always_inline))
void _c_int00_template(int NEEDS_ARGS, int NEEDS_INIT, int NEEDS_MPU)
{
   STACK_INIT();

   /*------------------------------------------------------------------------*/
   /* Call hook configured into Startup_resetFxn                             */
   /*------------------------------------------------------------------------*/
   if (&xdc_runtime_Startup__RESETFXN__C == (int*)1) {
      xdc_runtime_Startup_reset__I();
   }

   if (NEEDS_MPU)
      __mpu_init();

   /*------------------------------------------------------------------------*/
   /* Allow for any application-specific low level initialization prior to   */
   /* initializing the C/C++ environment (global variable initialization,    */
   /* constructers).  If _system_pre_init() returns 0, then bypass C/C++     */
   /* initialization.  NOTE: BYPASSING THE CALL TO THE C/C++ INITIALIZATION  */
   /* ROUTINE MAY RESULT IN PROGRAM FAILURE.                                 */
   /*------------------------------------------------------------------------*/
   if(_system_pre_init() != 0)
   {
      if (NEEDS_INIT)
         _auto_init();
   }

   /*------------------------------------------------------------------------*/
   /* Handle any argc/argv arguments if supported by an MSP430 loader.       */
   /*------------------------------------------------------------------------*/
   if (NEEDS_ARGS)
      xdc_runtime_System_exit__E(_args_main());
   else
      xdc_runtime_System_exit__E(main(0));
}

CSTART_DECL _c_int00(void)
{
   _c_int00_template(1, 1, 0);
}

CSTART_DECL _c_int00_noargs(void)
{
   _c_int00_template(0, 1, 0);
}

CSTART_DECL _c_int00_noinit(void)
{
   _c_int00_template(1, 0, 0);
}

CSTART_DECL _c_int00_noinit_noargs(void)
{
   _c_int00_template(0, 0, 0);
}

CSTART_DECL _c_int00_mpu(void)
{
   _c_int00_template(1, 1, 1);
}

CSTART_DECL _c_int00_noargs_mpu(void)
{
   _c_int00_template(0, 1, 1);
}

CSTART_DECL _c_int00_noinit_mpu(void)
{
   _c_int00_template(1, 0, 1);
}

CSTART_DECL _c_int00_noinit_noargs_mpu(void)
{
   _c_int00_template(0, 0, 1);
}
/*
 *  @(#) ti.targets.msp430.rts430; 1, 0, 0,0; 7-20-2018 14:28:20; /db/ztree/library/trees/xdctargets/xdctargets-r09/src/ xlibrary

 */


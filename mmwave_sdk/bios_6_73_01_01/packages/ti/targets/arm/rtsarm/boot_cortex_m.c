/*
 *  Copyright 2018 by Texas Instruments Incorporated.
 *
 */

/*****************************************************************************/
/* BOOT_CORTEX_M.C   v1.0.0 - Initialize the ARM C runtime environment       */
/*                                                                           */
/* Copyright (c) 2017-2018 Texas Instruments Incorporated                    */
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
#include <stdint.h>

#include <xdc/runtime/System.h>

#ifdef __TI_RTS_BUILD
/*---------------------------------------------------------------------------*/
/* __TI_default_c_int00 indicates that the default TI entry routine is being  */
/* used.  The linker makes assumptions about what exit does when this symbol */
/* is seen. This symbols should NOT be defined if a customized exit routine  */
/* is used.                                                                  */
/*---------------------------------------------------------------------------*/
__asm("__TI_default_c_int00 .set 1");
#endif

/*----------------------------------------------------------------------------*/
/* Define the user mode stack. The size will be determined by the linker.     */
/*----------------------------------------------------------------------------*/
__attribute__((section(".stack")))
int __stack;

/*----------------------------------------------------------------------------*/
/* Linker defined symbol that will point to the end of the user mode stack.   */
/* The linker will enforce 8-byte alignment.                                  */
/*----------------------------------------------------------------------------*/
extern int __STACK_END;

/*----------------------------------------------------------------------------*/
/* Function declarations.                                                     */
/*----------------------------------------------------------------------------*/
__attribute__((weak)) extern void __mpu_init(void);
extern int _system_pre_init(void);
extern void __TI_auto_init(void);
extern void _args_main(void);
extern void exit(int);
extern int main();

/*----------------------------------------------------------------------------*/
/* Default boot routine for Cortex-M                                          */
/*----------------------------------------------------------------------------*/
static __inline __attribute__((always_inline))
void _c_int00_template(int NEEDS_ARGS, int NEEDS_INIT)
{
   // Initialize the stack pointer
   char* stack_ptr = (char*)&__STACK_END;
   __asm volatile ("MSR msp, %0" : : "r" (stack_ptr) : );

   // Initialize the FPU if building for floating point
   #ifdef __ARM_FP
   volatile uint32_t* cpacr = (volatile uint32_t*)0xE000ED88;
   *cpacr |= (0xf0 << 16);
   #endif

   __mpu_init();
   if (_system_pre_init())
   {
      if (NEEDS_INIT)
         __TI_auto_init();
   }

   if (NEEDS_ARGS) {
      _args_main();
      System_exit(0);
   }
   else {
      System_exit(main());
   }
}

/******************************************************************************/
/* Specializations                                                            */
/******************************************************************************/
__attribute__((section(".text:_c_int00"), used))
void _c_int00(void)
{
   _c_int00_template(1, 1);
}

__attribute__((section(".text:_c_int00_noargs"), used))
void _c_int00_noargs(void)
{
   _c_int00_template(0, 1);
}

__attribute__((section(".text:_c_int00_noinit"), used))
void _c_int00_noinit(void)
{
   _c_int00_template(1, 0);
}

__attribute__((section(".text:_c_int00_noinit_noargs"), used))
void _c_int00_noinit_noargs(void)
{
   _c_int00_template(0, 0);
}
/*
 *  @(#) ti.targets.arm.rtsarm; 1, 0, 0,0; 7-20-2018 14:27:53; /db/ztree/library/trees/xdctargets/xdctargets-r09/src/ xlibrary

 */


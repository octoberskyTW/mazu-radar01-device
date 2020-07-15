/*****************************************************************************/
/* _AUTO_INIT()          - Perform initialization of C variables.            */
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
#include "autoinit.h"
#include "boot_hooks.h"

extern void __tdeh_init();

#define WDTPW                (0x5A00)
#define WDTCNTCL             (0x0008)
#define WDTHOLD              (0x0080)
#define RESTORE_WDT(setting) (WDTPW | (0x00FF & (setting)) | WDTCNTCL)
#define HOLD_WDT             (WDTPW | WDTHOLD)

#if __ARM_ARCH
#define WDTCTL WDTCTL_SYM
#endif

extern volatile uint16_t WDTCTL;

/*****************************************************************************/
/* Standard top-level autoinit                                               */
/*****************************************************************************/
static __inline __attribute__((always_inline))
void __TI_auto_init_template(int RUN_BINIT, int RUN_PINIT,
                             volatile uint16_t* WDTCTL_ptr)
{
   if (RUN_BINIT)
    run_binit();

   uint16_t initial_WDT;
   if (WDTCTL_ptr)
   {
      initial_WDT = *WDTCTL_ptr;
      *WDTCTL_ptr = HOLD_WDT;
   }

   run_cinit();

   if (WDTCTL_ptr)
      *WDTCTL_ptr = RESTORE_WDT(initial_WDT);

    /*-----------------------------------------------------------------------*/
    /* Call the startup hook function.                                       */
    /*-----------------------------------------------------------------------*/
    _system_post_cinit();

#ifdef _TMS320C6X
   /*------------------------------------------------------------------------*/
   /* Initialize master thread's Thread-Local variables. The RTS library     */
   /* provides the function __TI_tls_init to initialize TLS block of a       */
   /* given thread.  The address of the newly allocated TLS Block of the     */
   /* thread is passed as input parameter to this routine. If NULL is passed */
   /* the master thread's TLS block allocated by the linker is initialized.  */
   /*------------------------------------------------------------------------*/
   __TI_tls_init(NULL);
#else
   /*------------------------------------------------------------------------*/
   /* For those targets that support table driven exception handling,        */
   /* initialize the global exception stack data structure here before       */
   /* calling C++ global constructors to prepare for the first exception.    */
   /*------------------------------------------------------------------------*/
   /* C6x will call __tdeh_init() from within __TI_tls_init() since each     */
   /* thread must set up its own private exception stack.                    */
   /*------------------------------------------------------------------------*/
#if defined(__TI_TABLE_DRIVEN_EXCEPTIONS)
    __tdeh_init();
#endif
#endif

    if (RUN_PINIT)
       run_pinit();
}

/******************************************************************************/
/* Specializations                                                            */
/******************************************************************************/
__attribute__((section(".text:__TI_auto_init"), used))
void AUTO_INIT(void)
{
   __TI_auto_init_template(1, 1, NULL);
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

__attribute__((section(".text:__TI_auto_init_nobinit"), used))
void __TI_auto_init_nobinit(void)
{
   __TI_auto_init_template(0, 1, NULL);
}

__attribute__((section(".text:__TI_auto_init_nopinit"), used))
void __TI_auto_init_nopinit(void)
{
   __TI_auto_init_template(1, 0, NULL);
}

__attribute__((section(".text:__TI_auto_init_nobinit_nopinit"), used))
void __TI_auto_init_nobinit_nopinit(void)
{
   __TI_auto_init_template(0, 0, NULL);
}

__attribute__((section(".text:__TI_auto_init_hold_wdt"), used))
void AUTO_INIT_HOLD_WDT(void)
{
   __TI_auto_init_template(1, 1, &WDTCTL);
}

__attribute__((section(".text:__TI_auto_init_nobinit_hold_wdt"), used))
void __TI_auto_init_nobinit_hold_wdt(void)
{
   __TI_auto_init_template(0, 1, &WDTCTL);
}

__attribute__((section(".text:__TI_auto_init_nopinit_hold_wdt"), used))
void __TI_auto_init_nopinit_hold_wdt(void)
{
   __TI_auto_init_template(1, 0, &WDTCTL);
}

__attribute__((section(".text:__TI_auto_init_nobinit_nopinit_hold_wdt"), used))
void __TI_auto_init_nobinit_nopinit_hold_wdt(void)
{
   __TI_auto_init_template(0, 0, &WDTCTL);
}

#endif

/*****************************************************************************/
/* C6x __TI_cpp_init symbol */
/*****************************************************************************/
#ifdef _TMS320C6X
void __TI_cpp_init(void) { run_pinit(); }
#endif

#ifdef __TI_RTS_BUILD
/*---------------------------------------------------------------------------*/
/* __TI_default_auto_init indicates that the default TI auto initialization  */
/* routine is being used.  The linker makes assumptions about how            */
/* initialization is being performed when this symbols is seen.  This symbol */
/* should NOT be defined if a customized auto initialization routine is used.*/
/*---------------------------------------------------------------------------*/
__asm("__TI_default_auto_init .set 1");
#endif

/****************************************************************************/
/*  chunk.h                                                                 */
/*                                                                          */
/* Copyright (c) 2007 Texas Instruments Incorporated                        */
/* http://www.ti.com/                                                       */
/*                                                                          */
/*  Redistribution and  use in source  and binary forms, with  or without   */
/*  modification,  are permitted provided  that the  following conditions   */
/*  are met:                                                                */
/*                                                                          */
/*     Redistributions  of source  code must  retain the  above copyright   */
/*     notice, this list of conditions and the following disclaimer.        */
/*                                                                          */
/*     Redistributions in binary form  must reproduce the above copyright   */
/*     notice, this  list of conditions  and the following  disclaimer in   */
/*     the  documentation  and/or   other  materials  provided  with  the   */
/*     distribution.                                                        */
/*                                                                          */
/*     Neither the  name of Texas Instruments Incorporated  nor the names   */
/*     of its  contributors may  be used to  endorse or  promote products   */
/*     derived  from   this  software  without   specific  prior  written   */
/*     permission.                                                          */
/*                                                                          */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS   */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT   */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT   */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT   */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    */
/*                                                                          */
/****************************************************************************/

#if 0
/*---------------------------------------------------------------------------*/
/* Pick the integer size on top of which REAL is to be implemented.          */
/*---------------------------------------------------------------------------*/
#endif

/* This assumes that some type will be either an exact fit or exactly*/
/* half the size of a REAL.*/

/* Should fix support elsewhere so we can allow "long long" to be chosen */

#if (BPint==BPREAL) || defined(__TMS320C6X__) || defined(__ARP32__) || \
                       defined(__PRU__)       || defined(__C7000__) || \
                       (defined(__TMS320C28XX_CLA__) && defined(__TI_EABI__))
   #define BPbigint BPint
   #define bigint int
   #define biguns unsigned
#elif (BPlong==BPREAL) || defined(__MSP430__)
   #define BPbigint BPlong
   #define bigint long
   #define biguns unsigned long
#elif (BPlonglong==BPREAL)
   #define BPbigint BPlonglong
   #define bigint long long
   #define biguns unsigned long long
#elif ((BPint*2)==BPREAL)
   #define BPbigint BPint
   #define bigint int
   #define biguns unsigned
#elif ((BPlong*2)==BPREAL)
   #define BPbigint BPlong
   #define bigint long
   #define biguns unsigned long
#else
#error "Sorry, no satisfactory integer type available."
#endif

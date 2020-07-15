/*****************************************************************************/
/*  LSEEK.C                                                                  */
/*                                                                           */
/* Copyright (c) 2017 Texas Instruments Incorporated                         */
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

/*****************************************************************************/
/*                                                                           */
/* IMPORTANT!                                                                */
/*                                                                           */
/*   For multi-threaded applications, _stream[] is a shared resource and     */
/*   copies of _stream[] will need to be made coherent between a given local */
/*   data cache(s) and shared memory. The data synchronization API functions */
/*   __TI_data_synch_INV() and __TI_data_synch_WBINV() are used when         */
/*   necessary to update the shared memory copy of the object and invalidate */
/*   the local data cache copy of the object before leaving a given critical */
/*   region.                                                                 */
/*                                                                           */
/*****************************************************************************/

#include <lowlev.h>

/*****************************************************************************/
/*  LSEEK() - lseek on an open device/file                                   */
/*****************************************************************************/
_CODE_ACCESS off_t lseek(int llv_fd, off_t offset, int origin)
{
   off_t result;

   if (llv_fd < 0 || llv_fd >= _NSTREAM) return -1;

   /*------------------------------------------------------------------------*/
   /* CALL FUNCTION FROM DEVICE TABLE TO PERFORM LSEEK FOR THIS DEVICE/FILE  */
   /*------------------------------------------------------------------------*/

   if (_stream[llv_fd].dev == NULL) 
   { 
      __TI_data_synch_INV(&_stream[llv_fd], sizeof(_stream[llv_fd]));
      return -1;
   }
   else
      result = (*(_stream[llv_fd].dev->LSEEK))
                                         (_stream[llv_fd].dfd, offset, origin);

   /*------------------------------------------------------------------------*/
   /* Invalidate both the device table entry that was referenced and the     */
   /* stream table entry associated with the input file descriptor (llv_fd). */
   /* It is possible (though unlikely) that the contents of the device table */
   /* entry and/or the stream table entry could be updated by another thread */
   /* before this thread accesses either of those objects again.             */
   /*------------------------------------------------------------------------*/
   __TI_data_synch_INV(_stream[llv_fd].dev, sizeof(_DEVICE));
   __TI_data_synch_INV(&_stream[llv_fd], sizeof(_stream[llv_fd]));

   return result;
}


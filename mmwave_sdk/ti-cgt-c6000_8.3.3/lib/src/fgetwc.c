/*****************************************************************************/
/*  FGETWC.C                                                                 */
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

#include <wchar.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************/
/* FGETWC - Get a wide character from stream                                 */
/*                                                                           */
/*   Barebones implementation: Calls through to fgetc.                       */
/*****************************************************************************/
_CODE_ACCESS wint_t fgetwc(FILE *f)
{
    return fgetc(f);
}

/*****************************************************************************/
/* FPUTWC - Put a wide character into the stream                             */
/*                                                                           */
/*   Barebones implementation: Put the wide character in if it is the same   */
/*   when converted to a normal character.                                   */
/*****************************************************************************/
_CODE_ACCESS wint_t fputwc(wchar_t wc, FILE *f)
{
    unsigned char c = wc;
    if (c != wc)
    {
       errno = EILSEQ;
       return WEOF;
    }

    return fputc(c, f);
}

/*****************************************************************************/
/* UNGETWC - Push wide character back into stream.                           */
/*                                                                           */
/*   Barebones implementation: Call through to ungetc.  If the character is  */
/*   not the same when converted to normal character, use '?' instead.       */
/*****************************************************************************/
_CODE_ACCESS wint_t ungetwc(wint_t wc, FILE *f)
{
    if (wc == WEOF) return WEOF;
    unsigned char c = wc;
    if (c != wc)
    {
       errno = EILSEQ;
       return WEOF;
    }

    return (ungetc(c, f) == EOF ? WEOF : wc);
}

/*****************************************************************************/
/* FWIDE - Set the orientation of the stream.                                */
/*                                                                           */
/*   Barebones implementation: return 0 indicating the stream has no         */
/*   orientation.                                                            */
/*****************************************************************************/
_CODE_ACCESS int fwide(FILE *f, int c)
{
    return 0;
}


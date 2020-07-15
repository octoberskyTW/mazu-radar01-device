/*****************************************************************************/
/*  memory.c       							     */
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
/*									     */
/*  IMPORTANT!!!                                                             */
/*									     */
/*  This module contains the functions which implement the dynamic memory    */
/*  management routines. The following assumptions/rules apply:              */
/*									     */
/*   1) Packets are allocated a minimum of MIN_BLOCK + BLOCK_OVERHEAD bytes. */
/*                                                                           */
/*   2) The size of the heap is set at link time, using the -heap flag       */
/*      The allocation and sizing of the heap is a cooperative effort        */
/*      involving the linker, this file, and "sysmem.c".                     */
/*                                                                           */
/*   3) The heap can be reset at any time by calling the function "minit"    */
/*                                                                           */
/*   4) For multi-threaded applications, the heap is considered a SHARED     */
/*      resource. RTS takes responsibility for ensuring single-threaded      */
/*      access to the packet free list via use of the __TI_LOCK_HEAP_ALLOC   */
/*      mutex. The RTS does not support coherency of dynamically allocated   */
/*      objects at this time (which includes the packet free list itself).   */
/*      It is anticipated that a multi-threaded application will use a       */
/*      shared heap memory system provided by the underlying runtime OS      */
/*      (instead of the RTS heap memory system).                             */
/*									     */
/*  The following items are defined in this module :			     */
/*    minit()	 : Function to initialize dynamic memory management	     */
/*    malloc()	 : Function to allocate memory from mem mgmt system.	     */
/*    calloc()	 : Allocate an clear memory from mem mgmt system.	     */
/*    realloc()  : Reallocate a packet					     */
/*    free()	 : Function to free allocated memory.			     */
/*    memalign() : Function to allocate aligned memory from mem mgmt system. */
/*---------------------------------------------------------------------------*/
/*    minsert()  : Insert a packet into free list, sorted by size	     */
/*    mremove()  : Remove a packet from the free list.			     */
/*    sys_free	 : Pointer to free list 				     */
/*									     */
/*****************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <_mutex.h>
#include <_data_synch.h>

/*---------------------------------------------------------------------------*/
/* MIN_BLOCK MUST BE A MULTIPLE OF THE SIZEOF (LARGE_TYPE)                   */
/*---------------------------------------------------------------------------*/
#define LARGE_TYPE      long double
#define MIN_BLOCK       sizeof(LARGE_TYPE)
#define BLOCK_OVERHEAD  MIN_BLOCK
#define BLOCK_USED      1
#define BLOCK_MASK      (MIN_BLOCK-1)

/*---------------------------------------------------------------------------*/
/* "PACKET" is the template for a data packet.  Packet size contains         */
/* the number of bytes allocated for the user, excluding the size required   */
/* for management of the packet (BLOCK_OVERHEAD bytes).  Packets are always  */
/* allocated memory in MIN_BLOCK byte chunks. The lowest order bit of the    */
/* size field is used to indicate whether the packet is free(0) or used(1).  */
/* The size_ptr field is used to manage the free list, and is a pointer      */
/* to the next element in the free list.  The free list is sorted by size.   */
/*---------------------------------------------------------------------------*/
typedef struct pack 
{
    size_t       packet_size;     /* number of bytes        */
    struct pack *size_ptr;        /* next elem in free list */
} PACKET;

/*---------------------------------------------------------------------------*/
/* __TI_SYSMEM_SIZE is a symbol whose *address* is set by the linker to the  */
/* size of the heap, via the -heap flag.                                     */
/*---------------------------------------------------------------------------*/
extern _DATA_ACCESS int __TI_SYSMEM_SIZE;          /* address = size of heap */
 
/*---------------------------------------------------------------------------*/
/* Define the heap memory area.  Note that allocated space is actually       */
/* (re)allocated in the linker.  The object must appear in the ".sysmem"     */
/* data section, and it must be aligned properly.                            */
/*---------------------------------------------------------------------------*/
__attribute__((section(".sysmem"),aligned(8)))
_DATA_ACCESS PACKET _sys_memory[1];

static int need_mem_init = 1;

/*---------------------------------------------------------------------------*/
/* SYS_FREE - This variable is a pointer to the free list.                   */
/*---------------------------------------------------------------------------*/
static PACKET *sys_free = _sys_memory;

/*---------------------------------------------------------------------------*/
/* Function declarations                                                     */
/*---------------------------------------------------------------------------*/
static void minsert(PACKET *);         /* insert a packet into the free list */
static void mremove(PACKET *);         /* delete packet from the free list   */

/*****************************************************************************/
/*                                                                           */
/*  HEAP_SIZE - The allocatable size of the heap before allocation           */
/*                                                                           */
/*****************************************************************************/
static inline size_t heap_size()
{
    return _symval(&__TI_SYSMEM_SIZE) - BLOCK_OVERHEAD;
}

/*****************************************************************************/
/*                                                                           */
/*  HEAP_START - The start of the allocatable heap memory                    */
/*                                                                           */
/*****************************************************************************/
static inline unsigned char *heap_start()
{
    return (unsigned char *)_sys_memory;
}

/*****************************************************************************/
/*                                                                           */
/*  HEAP_END - One byte beyond the end of the heap                           */
/*                                                                           */
/*****************************************************************************/
static inline unsigned char *heap_end()
{
    return (unsigned char *)&(heap_start()[heap_size()]);
}

/*****************************************************************************/
/*                                                                           */
/*  CHECK_ALLOC_SIZE - Verify that an allocation of the requested size is    */
/*                     possible without an overflow during the process.      */
/*                                                                           */
/*****************************************************************************/
inline static int check_alloc_size(size_t size)
{
    /*-----------------------------------------------------------------------*/
    /* Make sure the value of size is small enough that we will not overflow */
    /* the unsigned int type in the memory size calculations.  SDSCM00049633.*/
    /*-----------------------------------------------------------------------*/
    if (size > (UINT_MAX - BLOCK_OVERHEAD - BLOCK_MASK - 1))
        return 0;
    return 1;
}

/*****************************************************************************/
/*									     */
/*  MINSERT - Insert a packet into the free list.  This list is sorted by    */
/*	      size in increasing order. 				     */
/*									     */
/*---------------------------------------------------------------------------*/
/* NOTE: All calls to minsert() must occur inside a critical section that    */
/*       is guarded by the __TI_LOCK_HEAP_ALLOC resource mutex.              */
/*****************************************************************************/
static void minsert(PACKET *ptr)
{
    PACKET *current = (PACKET *) sys_free;
    PACKET *last    = NULL;

    /*-----------------------------------------------------------------------*/
    /* Check special case: empty free list.				     */
    /*-----------------------------------------------------------------------*/
    if (current == NULL)
    {
        sys_free      = ptr;
        ptr->size_ptr = NULL;
        return;
    }

    /*-----------------------------------------------------------------------*/
    /* Scan through list, looking for a larger packet.			     */
    /*-----------------------------------------------------------------------*/
    while (current && current->packet_size < ptr->packet_size)
    {
	last	= current;
	current = current->size_ptr;
    }

    /*-----------------------------------------------------------------------*/
    /* Link the new packet into the list. There are three cases :	     */
    /*	 The new pointer will either be the first, the last, or in the	     */
    /*	 middle somewhere.						     */
    /*-----------------------------------------------------------------------*/
    if (current == NULL) 	        /* ptr will be last in list          */
    {
        last->size_ptr = ptr;
        ptr->size_ptr  = NULL;
    }
    else if (last == NULL)	        /* ptr will be first in the list     */
    {
        ptr->size_ptr  = sys_free;
        sys_free       = ptr;
    }
    else			        /* ptr is in the middle of the list  */
    {
        ptr->size_ptr  = current;
        last->size_ptr = ptr;
    }
}

/*****************************************************************************/
/*									     */
/* MREMOVE - Remove an item from the free list. 			     */
/*									     */
/*---------------------------------------------------------------------------*/
/* NOTE: All calls to mremove() must occur inside a critical section that    */
/*       is guarded by the __TI_LOCK_HEAP_ALLOC resource mutex.              */
/*****************************************************************************/
static void mremove(PACKET *ptr)
{
    PACKET *current = sys_free;
    PACKET *last    = NULL;

    /*-----------------------------------------------------------------------*/
    /* Scan through list, looking for packet to remove                       */
    /*-----------------------------------------------------------------------*/
    while (current && current != ptr)
    {
	last	= current;
	current = current->size_ptr;
    }

    /*-----------------------------------------------------------------------*/
    /* Remove the packet from the list.   There are two cases :              */
    /*   The old pointer will either be the first, or not the first.         */
    /*-----------------------------------------------------------------------*/
    if      (current == NULL) sys_free       = NULL;          /* Not found   */
    else if (last    == NULL) sys_free       = ptr->size_ptr; /* 1st in list */
    else                      last->size_ptr = ptr->size_ptr; /* Mid of list */
}

#if 0
/*****************************************************************************/
/* NOTE: In a multi-threaded application that is using RTS heap allocation,  */
/*       we need to write-back the value of all elements on the packet free  */
/*       list before leaving a critical region. This ensures that the        */
/*       shared memory retains the latest up-to-date value of the packet     */
/*       free list.                                                          */
/*									     */
/*       Alternatively, we can require that heap memory be non-cacheable.    */
/*       In either solution, there is a performance penalty.                 */
/*****************************************************************************/

/*****************************************************************************/
/*									     */
/*  INV_PACKET_LIST - Clear any local copies of a free list packet.          */
/*									     */
/*****************************************************************************/
static void inv_packet_list(void)
{
   /*------------------------------------------------------------------------*/
   /* The RTS heap allocation maintains a list of free heap memory packets   */
   /* that is pointed to by 'sys_free'. Since this is a shared resource,     */
   /* the RTS takes on the responsibility of keeping all copies of the       */
   /* packet list in the system up-to-date.                                  */
   /*------------------------------------------------------------------------*/
   /* For each PACKET on the sys_free list, write-back and/or invalidate the */
   /* cache line that the PACKET resides on.                                 */
   /*------------------------------------------------------------------------*/
   PACKET *current = sys_free;
   PACKET *last    = NULL;

   while (current)
   {
      last = current;
      current = current->size_ptr;
      __TI_data_synch_INV(last, sizeof(PACKET));
   }
}

/*****************************************************************************/
/*									     */
/*  WB_INV_PACKET_LIST - Write-back (and invalidate) any local copies of a   */
/*                       free list packet.                                   */
/*									     */
/*****************************************************************************/
static void wb_inv_packet_list(void)
{
   /*------------------------------------------------------------------------*/
   /* The RTS heap allocation maintains a list of free heap memory packets   */
   /* that is pointed to by 'sys_free'. Since this is a shared resource,     */
   /* the RTS takes on the responsibility of keeping all copies of the       */
   /* packet list in the system up-to-date.                                  */
   /*------------------------------------------------------------------------*/
   /* For each PACKET on the sys_free list, write-back and/or invalidate the */
   /* cache line that the PACKET resides on.                                 */
   /*------------------------------------------------------------------------*/
   PACKET *current = sys_free;
   PACKET *last    = NULL;

   while (current)
   {
      last = current;
      current = current->size_ptr;
      __TI_data_synch_WBINV(last, sizeof(PACKET));
   }
}
#endif

/*****************************************************************************/
/*									     */
/*  MEMINIT - This function performs the initial setup of the heap.          */
/*									     */
/*---------------------------------------------------------------------------*/
/* NOTE: All calls to meminit() must occur inside a critical section that    */
/*       is guarded by the __TI_LOCK_HEAP_ALLOC resource mutex.              */
/*****************************************************************************/
static void meminit(void)
{
    sys_free              = (PACKET*)heap_start();
    sys_free->packet_size = heap_size();
    sys_free->size_ptr	  = NULL;
    need_mem_init = 0;
    __TI_data_synch_WBINV(&need_mem_init, sizeof(need_mem_init));
}

/*****************************************************************************/
/*									     */
/*  MINIT - This function is not used by the compiler or RTS, but may be     */
/*          called directly by the user.  If this function is called,        */
/*          the heap is put into an uninitialized state, and the next call   */
/*          to an allocation function will re-initialize the heap.           */
/*                                                                           */
/*          WARNING: It is dangerous to call this function.  It does not     */
/*          deal with any existing pointers your program may have, so those  */
/*          pointers will be pointing to invalid objects in the free list.   */
/*          This is particularly bad for C++ objects, which sometimes        */
/*          allocate their own storage using pointers you do not have access */
/*          to.  Furthermore, some global C++ objects have an associated     */
/*          guard bit indicating that the object has already been allocated; */
/*          this bit does not get cleared if you call minit, so those C++    */
/*          objects will no longer be valid and cannot be used.  In summary, */
/*          you should probably never call this function.                    */
/*									     */
/*****************************************************************************/
_CODE_ACCESS void minit(void)
{
    need_mem_init = 1;
    __TI_data_synch_WBINV(&need_mem_init, sizeof(need_mem_init)); 
}

/*****************************************************************************/
/*									     */
/*  MALLOC - Allocate a packet of a given size, and return a pointer to it.  */
/*	     This function only allocates in multiples of MIN_BLOCK bytes.   */
/*									     */
/*****************************************************************************/
_CODE_ACCESS void *malloc(size_t size)
{
    PACKET *current;
    size_t  newsize;
    size_t  oldsize;

    if (size == 0) return 0;

    if (check_alloc_size(size) == 0) return 0;

    newsize = (size + BLOCK_MASK) & ~BLOCK_MASK;

    /*-----------------------------------------------------------------------*/
    /* Critical region to protect accesses to packet free list that are made */
    /* by minsert() and/or mremove() (see note #4 in file header comment).   */
    /*-----------------------------------------------------------------------*/
    __TI_resource_lock(__TI_LOCK_HEAP_ALLOC);

    if (need_mem_init) meminit();
    else __TI_data_synch_INV(&need_mem_init, sizeof(need_mem_init)); 

    current = sys_free;

    /*-----------------------------------------------------------------------*/
    /* Scan through free list for packet large enough to contain packet      */
    /*-----------------------------------------------------------------------*/
    while (current && current->packet_size < newsize)
       current = current->size_ptr;

    if (!current) { __TI_resource_unlock(__TI_LOCK_HEAP_ALLOC); return 0; }
    
    oldsize = current->packet_size;	    /* Remember old size	     */
    mremove(current);		            /* Remove packet from free list  */

    /*-----------------------------------------------------------------------*/
    /* If packet is larger than needed, free extra space at end	             */
    /* by inserting remaining space into free list.			     */
    /*-----------------------------------------------------------------------*/
    if (oldsize - newsize >= (MIN_BLOCK + BLOCK_OVERHEAD))
    {
       PACKET *next = 
	       (PACKET *) ((char *) current + BLOCK_OVERHEAD + newsize);
 
       next->packet_size    = oldsize - newsize - BLOCK_OVERHEAD;
       minsert(next);
       current->packet_size = newsize;
    }

   current->packet_size |= BLOCK_USED;

   __TI_resource_unlock(__TI_LOCK_HEAP_ALLOC);

   return (char *)current + BLOCK_OVERHEAD;
}

/*****************************************************************************/
/*									     */
/*  CALLOC - Allocate a packet of a given size, set the data in the packet   */
/*	     to nulls, and return a pointer to it.			     */
/*									     */
/*****************************************************************************/
_CODE_ACCESS void *calloc(size_t num, size_t size)
{
    size_t esz = size * num;

    void *ptr = malloc(esz);

    if (ptr) memset(ptr, 0, esz);

    return ptr;
}

/*****************************************************************************/
/*									     */
/*  REALLOC - Reallocate a packet to a new size.			     */
/*									     */
/*****************************************************************************/
_CODE_ACCESS void *realloc(void *packet, size_t size)
{
    char    *pptr    = (char *) packet - BLOCK_OVERHEAD;
    size_t   newsize;
    size_t   oldsize;

    if (check_alloc_size(size) == 0) return 0;

    newsize = (size + BLOCK_MASK) & ~BLOCK_MASK;

    if (packet == 0)  return malloc(size);
    if (size   == 0)  { free(packet); return 0; }

    if (check_alloc_size(size) == 0) return 0;

    /*-----------------------------------------------------------------------*/
    /* Critical region to protect accesses to packet free list that are made */
    /* by minsert() and/or mremove() (see note #4 in file header comment).   */
    /*-----------------------------------------------------------------------*/
    __TI_resource_lock(__TI_LOCK_HEAP_ALLOC);

    oldsize = ((PACKET *)pptr)->packet_size;

    if (!(oldsize & BLOCK_USED))  
       { __TI_resource_unlock(__TI_LOCK_HEAP_ALLOC); return 0; }

    if (newsize == --oldsize)
       { __TI_resource_unlock(__TI_LOCK_HEAP_ALLOC); return packet; }

    /*-----------------------------------------------------------------------*/
    /* If new size is less than current size, truncate packet and return end */
    /* to free list		                                             */
    /*-----------------------------------------------------------------------*/
    if (newsize < oldsize)
    {
       if ((oldsize - newsize) >= (MIN_BLOCK + BLOCK_OVERHEAD)) 
       {
          ((PACKET *)pptr)->packet_size = newsize | BLOCK_USED;

          oldsize -= newsize + BLOCK_OVERHEAD;
          pptr    += newsize + BLOCK_OVERHEAD;
          ((PACKET *)pptr)->packet_size = oldsize | BLOCK_USED;
          free(pptr + BLOCK_OVERHEAD);
       }
       __TI_resource_unlock(__TI_LOCK_HEAP_ALLOC);
       return packet;
    }

    /*-----------------------------------------------------------------------*/
    /* If new size is bigger than current packet,		             */
    /*	1) check next packet in list, see if packet can be expanded          */
    /*	2) If not, move packet to new location. 		             */
    /*-----------------------------------------------------------------------*/
    else
    {
	PACKET *next = (PACKET *)(pptr + oldsize + BLOCK_OVERHEAD);
	int     temp;

	if (((unsigned char *)next < heap_end()) &&
           (!(next->packet_size & BLOCK_USED))                           &&
           ((temp = oldsize +next->packet_size +BLOCK_OVERHEAD -newsize) >= 0))
	{
	    mremove(next);
	    if (temp < MIN_BLOCK + BLOCK_OVERHEAD)
	    {
	       ((PACKET *)pptr)->packet_size = newsize + temp | BLOCK_USED;
	       __TI_resource_unlock(__TI_LOCK_HEAP_ALLOC);
	       return packet;
	    }

	    ((PACKET *)pptr)->packet_size = newsize | BLOCK_USED;
	    pptr += newsize + BLOCK_OVERHEAD;
	    ((PACKET *)pptr)->packet_size = temp - BLOCK_OVERHEAD;
	    minsert((PACKET *)pptr);
	    __TI_resource_unlock(__TI_LOCK_HEAP_ALLOC);
	    return packet;
	}
	else
	{
            /*---------------------------------------------------------------*/
	    /* Allocate new packet and move data into it. 	             */
            /*---------------------------------------------------------------*/
	    char *new = malloc(size);
	    if (new != 0) 
	    {
	       memcpy(new, packet, oldsize);
	       free(packet);
	    }
	    __TI_resource_unlock(__TI_LOCK_HEAP_ALLOC);
	    return new;
	}
    }
}

/*****************************************************************************/
/*									     */
/*  FREE - Return a packet allocated by malloc to free memory pool.	     */
/*	   Return 0 if successful, -1 if not successful.		     */
/*									     */
/*****************************************************************************/
_CODE_ACCESS void free(void *packet)
{
    char   *ptr = (char *)packet;
    PACKET *last;	      /* point to previous packet            */
    PACKET *current;	      /* pointer to this packet              */
    PACKET *next;	      /* pointer to next packet              */

    if (ptr == NULL) return;

    last = next = NULL;		      /* initialize pointers                 */
    ptr -= BLOCK_OVERHEAD;	      /* adjust point to beginning of packet */

    /*-----------------------------------------------------------------------*/
    /* Critical region to protect accesses to packet free list that are made */
    /* by minsert() and/or mremove() (see note #4 in file header comment).   */
    /*-----------------------------------------------------------------------*/
    __TI_resource_lock(__TI_LOCK_HEAP_ALLOC);

    current = _sys_memory;

    /*-----------------------------------------------------------------------*/
    /* Search for the pointer in the packet pointed to			     */
    /*-----------------------------------------------------------------------*/
    while (current < (PACKET *) ptr)
    {
        last    = current;
        current = (PACKET *)((char *)current + 
		  (current->packet_size & ~BLOCK_USED) + BLOCK_OVERHEAD);
    }

    /*-----------------------------------------------------------------------*/
    /* Check for pointer or packet errors.				     */
    /*-----------------------------------------------------------------------*/
    if ((current != (PACKET *) ptr) || (!(current->packet_size & BLOCK_USED)))
       { __TI_resource_unlock(__TI_LOCK_HEAP_ALLOC); return; }

    current->packet_size &= ~BLOCK_USED;   /* mark packet as free */

    /*-----------------------------------------------------------------------*/
    /* Get pointer to next packet in memory, if any.			     */
    /*-----------------------------------------------------------------------*/
    next = (PACKET *)((char *)current + BLOCK_OVERHEAD + current->packet_size);
    if (next > (PACKET *)heap_end())
	next = NULL;

    if (last && (last->packet_size & BLOCK_USED)) last = NULL;
    if (next && (next->packet_size & BLOCK_USED)) next = NULL;

    /*-----------------------------------------------------------------------*/
    /* Attempt to coalesce the three packets (previous, current, next)	     */
    /*-----------------------------------------------------------------------*/
    if (last && next)
    {
	mremove(last);
	mremove(next);
	last->packet_size += current->packet_size + next->packet_size + 
			     BLOCK_OVERHEAD + BLOCK_OVERHEAD;
	minsert(last);
	__TI_resource_unlock(__TI_LOCK_HEAP_ALLOC);
	return;
    }

    /*-----------------------------------------------------------------------*/
    /* Attempt to coalesce the current with last packet. (last, current)     */
    /*-----------------------------------------------------------------------*/
    if (last)
    {
        mremove(last);
        last->packet_size += current->packet_size + BLOCK_OVERHEAD;
        minsert(last);
        __TI_resource_unlock(__TI_LOCK_HEAP_ALLOC);
        return;
    }

    /*-----------------------------------------------------------------------*/
    /* Attempt to coalesce the current with next packet. (current, next)     */
    /*-----------------------------------------------------------------------*/
    if (next)
    {
        mremove(next);
        current->packet_size += next->packet_size + BLOCK_OVERHEAD;
        minsert(current);
        __TI_resource_unlock(__TI_LOCK_HEAP_ALLOC);
        return;
    }

    /*-----------------------------------------------------------------------*/
    /* No coalescence possible, just insert this packet into list	     */
    /*-----------------------------------------------------------------------*/
    minsert(current);
    __TI_resource_unlock(__TI_LOCK_HEAP_ALLOC);
}

/*****************************************************************************/
/*                                                                           */
/*  MEMALIGN - Allocate a packet of a given size, and on a given boundary.   */
/*                                                                           */
/*****************************************************************************/
_CODE_ACCESS void *memalign(size_t alignment, size_t size)
{
    PACKET       *aln_packet;
    PACKET       *current;
    size_t        newsize;
    size_t        aln_mask = alignment - 1;
    size_t        leftover = 0;
    char         *aln_start;
    char         *un_aln_start;

    if (size == 0) return 0;

    if (check_alloc_size(size) == 0) return 0;

    newsize = (size + BLOCK_MASK) & ~BLOCK_MASK;

    /*-----------------------------------------------------------------------*/
    /* Critical region to protect accesses to packet free list that are made */
    /* by minsert() and/or mremove() (see note #4 in file header comment).   */
    /*-----------------------------------------------------------------------*/
    __TI_resource_lock(__TI_LOCK_HEAP_ALLOC);

    if (need_mem_init) meminit();
    else __TI_data_synch_INV(&need_mem_init, sizeof(need_mem_init)); 

    current = sys_free;

    /*--------------------------------------------------------------------*/
    /* If alignment is not a power of two or is less than the default     */
    /* alignment of malloc, then simply return what malloc returns.       */
    /*--------------------------------------------------------------------*/
    if (alignment <= BLOCK_OVERHEAD || (alignment & (alignment-1))) 
       { __TI_resource_unlock(__TI_LOCK_HEAP_ALLOC); return malloc(size); }

    /*-----------------------------------------------------------------------*/
    /* Scan through free list for packet large enough to contain aligned     */
    /* packet                                                                */
    /*-----------------------------------------------------------------------*/
    for ( ; current ; current = current->size_ptr)
    {
        /*-------------------------------------------------------------------*/
        /* Start of usable portion of the current packet.                    */
        /*-------------------------------------------------------------------*/
        un_aln_start = (char *) current + BLOCK_OVERHEAD;

        /*-------------------------------------------------------------------*/
        /* First aligned address in usable portion of the current packet.    */
        /*-------------------------------------------------------------------*/
        aln_start = (char *) (((size_t) un_aln_start + aln_mask) & ~aln_mask);

        /*-------------------------------------------------------------------*/
        /* If the block is not already sufficiently aligned, we will slice a */
        /* small part of it from the beginning, which must be added to the   */
        /* free list.  Make sure that the pre block space is large enough    */
        /* to be a block of its own.  We want to keep the aligned address    */
        /* aligned, so increment the proposed start address by alignment.    */
        /*-------------------------------------------------------------------*/
        if (un_aln_start != aln_start)
            while ((char *)current+sizeof(PACKET) > aln_start - BLOCK_OVERHEAD)
                aln_start += alignment;

        /*-------------------------------------------------------------------*/
        /* Now we know where the actual packet will be if we use part of the */
        /* current packet.  Make sure it does not overlap the next packet.   */
        /*-------------------------------------------------------------------*/

        /*-------------------------------------------------------------------*/
        /* Actual start of the next packet (either free or in use).          */
        /*-------------------------------------------------------------------*/
        char *next_packet_start = un_aln_start + current->packet_size;

        /*-------------------------------------------------------------------*/
        /* End of proposed new packet.                                       */
        /*-------------------------------------------------------------------*/
        char *proposed_packet_end = aln_start + newsize;

        if (next_packet_start >= proposed_packet_end)
        {
            leftover = next_packet_start - proposed_packet_end;
            break;
        }
    }

    if (!current) 
       { __TI_resource_unlock(__TI_LOCK_HEAP_ALLOC); return 0; }

    /*-----------------------------------------------------------------------*/
    /* Setup new packet for aligned memory.                                  */
    /*-----------------------------------------------------------------------*/
    mremove(current);
    aln_packet              = (PACKET *) (aln_start - BLOCK_OVERHEAD);
    aln_packet->packet_size = newsize | BLOCK_USED;

    /*-----------------------------------------------------------------------*/
    /* Handle the free space before the aligned block.  If the original      */
    /* block was aligned, there won't be free space before the aligned block.*/
    /*-----------------------------------------------------------------------*/
    if (aln_start != un_aln_start) 
    {
	current->packet_size = (char *)aln_packet - un_aln_start;
	minsert(current);
    }

    /*-----------------------------------------------------------------------*/
    /* Handle the free space after the aligned block.  If it is large enough */
    /* to be a block of its own, then make it one.  Otherwise add the        */
    /* leftover size to the aligned block.                                   */
    /*-----------------------------------------------------------------------*/
    if (leftover >= BLOCK_OVERHEAD + MIN_BLOCK)
    {
       PACKET *next = (PACKET *) (aln_start + newsize);
       next->packet_size = leftover - BLOCK_OVERHEAD;
       minsert(next);
    }
    else aln_packet->packet_size += leftover;

    __TI_resource_unlock(__TI_LOCK_HEAP_ALLOC);
    return aln_start;
}

#ifdef MALLOC_DEBUG
/*****************************************************************************/
/*									     */
/*  MEMMAP -  Print dynamic memory allocation statistics                     */
/*									     */
/*****************************************************************************/
#include <stdio.h>
#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

_CODE_ACCESS void memmap()
{
    PACKET *current;

    /*-----------------------------------------------------------------------*/
    /* Critical region to protect accesses to packet free list while writing */
    /* heap memory usage stats (see note #4 in file header comment).         */
    /*-----------------------------------------------------------------------*/
    __TI_resource_lock(__TI_LOCK_HEAP_ALLOC);

    if (need_mem_init) meminit();
    else __TI_data_synch_INV(&need_mem_init, sizeof(need_mem_init)); 

    current = _sys_memory;

    int    free_block_num		= 0;
    size_t free_block_space	= 0;
    size_t free_block_max		= 0;
    int    used_block_num		= 0;
    size_t used_block_space	= 0;
    size_t used_block_max		= 0;

    /*-----------------------------------------------------------------------*/
    /* Loop through all packets                                              */
    /*-----------------------------------------------------------------------*/
    while (current < (PACKET *)heap_end())
    {
	size_t size = current->packet_size & ~BLOCK_USED;
        size_t used = current->packet_size & BLOCK_USED;

        printf(">> Used:%zu size:%zu addr:%p\n", used, size, current);

        if (used)
	{
	    used_block_num++;
	    used_block_space += size;
	    used_block_max   = MAX(used_block_max, size);
	}
	else
	{
	    free_block_num++;
	    free_block_space += size;
	    free_block_max   = MAX(free_block_max, size);
	}

        current = (PACKET *)((char *)current + size + BLOCK_OVERHEAD);
    }

    printf("fr_nm:%d fr_sp:%zu fr_mx:%zu "
           "us_nm:%d us_sp:%zu us_mx:%zu "
           "ovr:%zu\n\n", 
	    free_block_num, free_block_space, free_block_max,
	    used_block_num, used_block_space, used_block_max,
	    (free_block_num + used_block_num) * BLOCK_OVERHEAD);

    fflush(stdout);

    __TI_resource_unlock(__TI_LOCK_HEAP_ALLOC);
}
#endif

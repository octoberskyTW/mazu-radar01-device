/*****************************************************************************/
/* dtor_list.cpp                                                             */
/* Copyright (c) 1996      Texas Instruments Inc., all rights reserved       */
/*****************************************************************************/
/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++ Runtime                            - | \^/ | -      *
*                                                               \   /         *
*                                                             /  | |  \       *
* Copyright 1992-2017 Edison Design Group Inc.                   [_]          *
*                                                                             *
******************************************************************************/
/*
Redistribution and use in source and binary forms are permitted
provided that the above copyright notice and this paragraph are
duplicated in all source code forms.  The name of Edison Design
Group, Inc. may not be used to endorse or promote products derived
from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
Any use of this software is at the user's own risk.
*/
/*

dtor_list.c -- destruction list processing.

*/

#include "basics.h"
#include "runtime.h"
#pragma hdrstop
/*** START TI ADD ***/
/*
TI implementation of RTS uses __TI_LOCK_ATEXIT mutex to protect access to
needed_destruction_head, so include _mutex.h. The data synch API is also
used to maintain the consistency of the system-wide value for __TI_dtors_ptr,
so include _data_synch.h as well.
*/
#include <_mutex.h>
#include <_data_synch.h>
/*** END TI ADD ***/

/*** START TI REMOVE ***/
/*
TI implementation of RTS does not need the definition in static_init.h.
TI RTS only needs IA64_ABI part of this file.
*/
#if 0
#include "static_init.h"
#endif /* 0 */
/*** END TI REMOVE ***/
#include "dtor_list.h"

#if !defined(__EDG_IA64_ABI) || !SYSTEM_RUNTIME_HAS_IA64_SUPPORT || \
    !SYSTEM_RUNTIME_HAS_IA64_ATEXIT

/*
The list of static objects that require destruction.  An entry is
added to the front of this list each time a new destructible static
object is created.
*/
/*** START TI REPLACE ***/
static _DATA_ACCESS a_needed_destruction_ptr
		needed_destruction_head = NULL;
/*** END TI REPLACE ***/

#endif /* !defined(__EDG_IA64_ABI) || !SYSTEM_RUNTIME_HAS_IA64_SUPPORT
          !SYSTEM_RUNTIME_HAS_IA64_ATEXIT */

#if RUNTIME_DOES_THREAD_LOCAL_DESTRUCTIONS

/*
The list of thread_local objects that require destruction.  An entry is
added to the front of this list each time a new destructible thread_local
object is created.
*/
thread_local a_needed_destruction_ptr
                __thread_needed_destruction_head /* = NULL*/;

#endif /* RUNTIME_DOES_THREAD_LOCAL_DESTRUCTIONS */


/*** START TI ADD ***/
EXTERN_C void _DATA_ACCESS (*__TI_dtors_ptr)(int);
/*** END TI ADD ***/
#ifndef __EDG_IA64_ABI

void __process_destruction_list(a_needed_destruction_ptr *destruction_list)
/*
Go through the specified destructions list and perform the required
destructions.
*/
{
  a_needed_destruction_ptr      ndp;
  while (*destruction_list != NULL) {
    void        *object_ptr;
    /* Note that the value of *destruction_list may change
       during the execution of the destructor.  Consequently, the
       current entry is removed from the list before the destructor
       routine is called. */
    ndp = *destruction_list;
    *destruction_list = (*destruction_list)->next;
    object_ptr = ndp->object;
    /* Choose between a simple and complex destruction based on whether
       or not the object pointer is NULL. */
    if (object_ptr != NULL) {
      a_destructor_ptr  dp;
      /* Destroy the object by calling a destructor.  The flag value of 2
         indicates the object should be destroyed, but operator delete
         should not be called. */
      dp = (a_destructor_ptr)ndp->destruction_routine;
      (dp)(object_ptr, 2);
    } else {
      /* Destroy the object by calling a special function that will do the
         destruction of this specific object. */
      (ndp->destruction_routine)();
    }  /* if */
  }  /* while */
}  /* __process_destruction_list */


void __process_needed_destructions(void)
/*
Go through the needed destructions lists and perform the required
destructions (for the current thread as well as the process).
*/
{
#if RUNTIME_DOES_THREAD_LOCAL_DESTRUCTIONS
  /* thread_local destructions are performed first. */
  __process_destruction_list(&__thread_needed_destruction_head);
#endif /* RUNTIME_DOES_THREAD_LOCAL_DESTRUCTIONS */
  __process_destruction_list(&needed_destruction_head);
}  /* __process_needed_destructions */


/*** START TI ADD ***/
static void __TI_process_needed_destructions(int status)
/*
To match the expected signature of __TI_dtors_ptr, we need to have an integer
argument. Otherwise, jump straight to EDG's handler.
*/
{
  __process_needed_destructions();
}
/*** END TI ADD ***/


EXTERN_C void __already_marked_for_destruction()
/*
This routine is called when a needed destruction is recorded more than
once.  It simply calls abort.  The name is intended to describe the nature
of the problem to the user.
*/
{
  __abort_execution(ec_already_marked_for_destruction);
}

void __record_destruction_on_list(a_needed_destruction_ptr *destruction_list,
                                  a_needed_destruction_ptr ndp)
/*
Add ndp to the list pointed to by *destruction_list.
*/
{
  /* If the entry has already been put on the list, terminate the execution. */
  if (ndp->next != NULL || ndp == *destruction_list) {
    __already_marked_for_destruction();
  }  /* if */
  ndp->next = *destruction_list;
  *destruction_list = ndp;
}  /* __record_destruction_on_list */


EXTERN_C void __record_needed_destruction(a_needed_destruction_ptr ndp)
/*
Called when a static object has been constructed to register a
destruction that must be done at program termination.  ndp points to
a needed destruction entry that is to be added to the front of the
list of needed destructions.
*/
{
/*** START TI ADD ***/
  __TI_resource_lock(__TI_LOCK_ATEXIT);
  /* Register EDG's __process_needed_destructions so that we call it during
     exit(). We avoid calling it during exit() so that it's not linked if not
     needed. */
  __TI_dtors_ptr = __TI_process_needed_destructions;
  __TI_data_synch_WBINV(&__TI_dtors_ptr, sizeof(__TI_dtors_ptr));
/*** END TI ADD ***/
  __record_destruction_on_list(&needed_destruction_head, ndp);
/*** START TI ADD ***/
  __TI_data_synch_WBINV(&needed_destruction_head,
                        sizeof(needed_destruction_head));
  __TI_resource_unlock(__TI_LOCK_ATEXIT);
/*** END TI ADD ***/
}  /* __record_needed_destruction */

/*** START TI ADD ***/
EXTERN_C void __add_dtor(a_needed_destruction_ptr ndp)
/*
For backwards compatiblity, map __add_dtor back to __record_needed_destruction.
*/
{
  __record_needed_destruction(ndp);
}
/*** END TI ADD ***/

#if CFRONT_COMPATIBILITY_MODE
EXTERN_C void __std__needed_destruction_list(void)
/*
This routine is provided for use with a cfront runtime library, including
cfront startup and termination code.  This routine will be called by
the cfront static destruction routines and will ensure that any needed
destructions get done.  The sequence of the destructions will not
be standard conforming, but there is no way to get standard conforming
behavior when using the cfront termination routines.

This routine will only be used when munch is being used.  When patch
is being used, the link structure defined below will result in a call to
__process_needed_destructions.
*/
{
  __process_needed_destructions();
}  /* __std__needed_destruction_list */


/*
Define a link structure that will be used when patch is being used.
*/
struct a_link {
  a_link        *next;
  a_void_function_ptr
                ctor;
  a_void_function_ptr
                dtor;
};

/*** START TI REPLACE ***/
static _DATA_ACCESS_NEAR a_link __link =
                       {(a_link*)NULL,
/*** END TI REPLACE ***/
                        (a_void_function_ptr)NULL,
                        (a_void_function_ptr)__process_needed_destructions};


/*
This declaration is used to force the static definition of __link to be
put out (i.e., to make the compiler think that __link is actually used).
*/
/*** START TI REPLACE ***/
_DATA_ACCESS a_link*
    __dummy_variable_used_to_force_definition_of__link = &__link;
/*** END TI REPLACE ***/
#endif /* CFRONT_COMPATIBILITY_MODE */

#else /* defined(__EDG_IA64_ABI) */

#if !SYSTEM_RUNTIME_HAS_IA64_SUPPORT
/* Current versions of Linux already define these routines in the C runtime
   library, and if we attempt to redefine them here we end up with multiple
   versions of these symbols. */

/* The DSO handle.  Initialization to NULL indicates that this is the handle
   for the main program.  */
/*** START TI REPLACE ***/
_DATA_ACCESS_NEAR a_dso_handle __dso_handle;
/*** END TI REPLACE ***/

#endif /* !SYSTEM_RUNTIME_HAS_IA64_SUPPORT */

#if !SYSTEM_RUNTIME_HAS_IA64_ATEXIT || !SYSTEM_RUNTIME_HAS_IA64_THREAD_ATEXIT

void __finalize_destructions(a_needed_destruction_ptr *destruction_list,
                             a_dso_handle             dso_handle)
/*
Go through the specified destructions list and perform the required
destructions for the DSO indicated by dso_handle, or all destructions if
dso_handle is NULL.
*/
{
  a_needed_destruction_ptr *ndpp, ndp, old_head;

  ndpp = destruction_list;
  while (*ndpp != NULL) {
    ndp = *ndpp;
    /* Skip destructions that do not apply to this DSO. */
    if (dso_handle != NULL && ndp->dso_handle != dso_handle) {
      ndpp = &ndp->next;
      continue;
    }  /* if */
    /* Note that the value pointed to by destruction_list may change
       during the execution of the destructor.  Consequently, the
       current entry is removed from the list before the destructor
       routine is called. */
    *ndpp = ndp->next;
    old_head = *destruction_list;
    /* Call the routine. */
    (*ndp->destruction_routine)(ndp->object);
    /* Deallocate the entry. */
    free(ndp);
    /* If the head has changed, start at the beginning of the list
       again so that we can process the newly added destruction. */
    if (*destruction_list != old_head) {
      ndpp = destruction_list;
    }  /* if */
  }  /* while */
}  /* __finalize_destructions */


int __add_destruction_to_list(a_needed_destruction_ptr *destruction_list,
                              a_cxa_dtor_ptr           destruction_routine,
                              void                     *object,
                              a_dso_handle             dso_handle)
/*
Register an action to be taken at a later time (program termination,
DSO unload, or thread termination) by queuing the action (a call
to destruction_routine with object as its argument) on the specified
destruction list.  Return zero if the registration is successful, or non-zero
otherwise.
*/
{
  int                      success = TRUE;
  a_needed_destruction_ptr ndp;

  ndp = (a_needed_destruction_ptr)malloc(sizeof(a_needed_destruction));
  if (ndp == NULL) {
    success = FALSE;
  }  else {
/*** START TI ADD ***/
    /* Here in IA64_ABI mode, we do not need to register the destructor in
       any other place. The ndp below records all the destructors and the
       __cxa_finalize will walk through the list to call the destructors
       during exit.

       "__register_finalization_routine()" defined in static_init.c in
       EDGRTS release calls atexit() to record "__call_dtors" function.
       "__call_dtors" is a function in EDGRTS release corresponds to
       "__call_ctors" which is also from EDGRTS release. As TI RTS does not
       use "__call_ctors" to do static initialization, here it is also
       unnecessary to call "_call_dtors".

       For non IA64_ABI mode, we have our own way to record the destructors,
       details in __add_dtor() */

    /* REGISTER __cxa_ia64_exit() SO exit() WILL CALL IT.  __cxa_ia64_exit
       CALLS __cxa_finalize() TO CALL OF THE FUNCTIONS ON THE ATEXIT LIST
       THE USE OF __TI_dtors_ptr ALLOWS US TO AVOID LINKING IN
       call_dtors() IF IT ISN'T USED. */
    __TI_dtors_ptr = ABI_NAMESPACE::__cxa_ia64_exit;
    __TI_data_synch_WBINV(&__TI_dtors_ptr, sizeof(__TI_dtors_ptr));
/*** END TI ADD ***/
    ndp->object = object;
    ndp->destruction_routine = (a_destructor_ptr)destruction_routine;
    ndp->dso_handle = dso_handle;
    ndp->next = *destruction_list;
    *destruction_list = ndp;
  }  /* if */
  return !success;
}  /* __add_destruction_to_list */

#endif /* !SYSTEM_RUNTIME_HAS_IA64_ATEXIT || !SYSTEM_RUNTIME_HAS_IA64_... */
#if !SYSTEM_RUNTIME_HAS_IA64_ATEXIT

/*** START TI ADD ***/
void ABI_NAMESPACE::__cxa_ia64_exit(int status)
{
    ABI_NAMESPACE::__cxa_finalize((a_dso_handle)NULL);
}
/*** END TI ADD ***/

void ABI_NAMESPACE::__cxa_finalize(a_dso_handle dso_handle)
/*
Go through the needed destructions lists and perform the required
destructions for the DSO indicated by dso_handle, or all destructions if
dso_handle is NULL.
*/
{
#if RUNTIME_DOES_THREAD_LOCAL_DESTRUCTIONS
  /* Do thread_local destructions for the current thread first. */
  __finalize_destructions(&__thread_needed_destruction_head, dso_handle);
#endif /* RUNTIME_DOES_THREAD_LOCAL_DESTRUCTIONS */
  __finalize_destructions(&needed_destruction_head, dso_handle);
}  /* __cxa_finalize */

/*** START TI REPLACE ***/
/*
Renamed __cxa_atexit to __TI_atexit, __TI_atexit is invoked by both __cxa_atexit
and __aeabi_atexit (inline into both the functions)
*/
static inline int __TI_atexit(a_cxa_dtor_ptr   destruction_routine,
/*** END TI REPLACE ***/
                              void             *object,
                              a_dso_handle     dso_handle)
/*
Register an action to be taken at program termination (or DSO unload) time.
The action is the calling of destruction_routine with the object parameter.
If dso_handle is non-NULL, the action will be taken when __cxa_finalize
is called for the specific dso_handle value, or when __cxa_finalize
is called to process all objects (i.e., the __cxa_finally dso_handle has
a NULL value).  If dso_handle is NULL, the action will be taken only when
__cxa_finalize is called to process all objects.

This version of __cxa_atexit is only intended to be used when the
system's runtime does not include its own version of __cxa_atexit.  When
the system's runtime includes such a function, the system is responsible
for seeing that __cxa_finalize is invoked at program termination.  When
using our own version of this routine, we need to ensure that __cxa_finalize
is invoked at program termination.  This is accomplished by calling
__register_finalization_routine on the first invocation of this function.
Return zero if the registration is successful, or non-zero otherwise.
*/
{
/*** START TI ADD ***/
  __TI_resource_lock(__TI_LOCK_ATEXIT);
/*** END TI ADD ***/
/*** START TI REMOVE ***/
#if 0
  if (needed_destruction_head == NULL) __register_finalization_routine();
#endif /* 0 */
/*** END TI REMOVE ***/
/*** START TI REPLACE ***/
  int success = __add_destruction_to_list(&needed_destruction_head,
/*** END TI REPLACE ***/
                                   destruction_routine,
                                   object, dso_handle);
/*** START TI ADD ***/
  __TI_resource_unlock(__TI_LOCK_ATEXIT);
  return success;
/*** END TI ADD ***/
}  /* __TI_atexit */

/*** START TI ADD ***/
int ABI_NAMESPACE::__cxa_atexit(a_cxa_dtor_ptr    destruction_routine,
                                void             *object,
                                a_dso_handle      dso_handle)
{
    return __TI_atexit(destruction_routine, object, dso_handle);
}  /* __cxa_atexit */
/*** END TI ADD ***/

#endif /* !SYSTEM_RUNTIME_HAS_IA64_ATEXIT */

#endif /* defined(__EDG_IA64_ABI) */

/*** START TI ADD ***/
#if defined(__TI_EABI_SUPPORT__) || defined(__TI_EABI__)
EXTERN_C int atexit(void (*fun)()) _TI_NOEXCEPT_CPP14
{

   ABI_NAMESPACE::__cxa_atexit((a_cxa_dtor_ptr)fun, NULL, NULL);
   return 0;
}

#if defined(__TMS470__) && defined(__TI_EABI_SUPPORT__)
namespace __aeabiv1
{
extern "C" int __aeabi_atexit(void *object,
	                      void (*destroyer) (void *),
			      void *dso_handle)
{
    return __TI_atexit(destroyer, object, dso_handle);
}

} //namespace __aeabiv1
#endif /* defined(__TMS470__) && defined(__TI_EABI_SUPPORT__) */
#else /* !defined(__TI_EABI_SUPPORT__) && !defined(__TI_EABI__) */
/****************************************************************************/
/* __ATEXIT_FUNC_ID__ IS USED AS AN IDENTIFIER TO DISTINGUISH IF A DTOR_LIST*/
/* RECORDS A ATEXIT FUNCTION.                                               */
/****************************************************************************/
_DATA_ACCESS int __atexit_func_id__ = 0x1234;

/****************************************************************************/
/* STATICALLY ALLOCATE MEMORY FOR ATEXIT FUNCTION REGISTRATION (CQ20012)    */
/*--------------------------------------------------------------------------*/
/* NOTE: The C standard requires that the user may register at least 32     */
/*       functions via atexit(). If any additional atexit() calls are       */
/*       needed during the boot sequence or by any other RTS facility, then */
/*       the MAX_ATEXIT_FUN definition below must be updated accordingly    */
/*       and this comment adjusted to include those details.                */
/****************************************************************************/
#define MAX_ATEXIT_FUN 32
static _DATA_ACCESS int atexit_func_count = 0;
static _DATA_ACCESS a_needed_destruction atexit_func[MAX_ATEXIT_FUN];

/****************************************************************************/
/* ATEXIT - ATTEMPT TO REGISTER A FUNCTION FOR CALLING AT PROGRAM END       */
/*          THE GENERIC C++ ABI (IA64) REQUIRES USING THE CXA_ATEXIT        */
/*          MECHANISM TO IMPL ATEXIT. FUNCTION DEFINED IN VEC_NEWDEL.CPP    */
/****************************************************************************/
EXTERN_C int atexit(void (*fun)())
{
   int err_code = 1;

   /*-----------------------------------------------------------------------*/
   /* For multi-threaded applications, access to shared resources must be   */
   /* protected. In this case, both atexit_func_count and atexit_func[] are */
   /* shared resources that may be accessed and updated by this function.   */
   /* Use the __TI_LOCK_ATEXIT mutex to create a critical section and       */
   /* that the local copies of both atexit_func_count and atexit_func[] are */
   /* flushed to shared memory.                                             */
   /*-----------------------------------------------------------------------*/
   __TI_resource_lock(__TI_LOCK_ATEXIT);

   /*-----------------------------------------------------------------------*/
   /* We allow MAX_ATEXIT_FUN calls to atexit(); see the comment above the  */
   /* definition of MAX_ATEXIT_FUN for more details. BIOS has a specific    */
   /* request that we NOT use malloc here. If anyone requires additional    */
   /* atexit calls for use by RTS or OS, then the MAX_ATEXIT_FUN limit      */
   /* (above) must be adjusted and the library rebuilt (CQ20012, CQ20600).  */
   /*-----------------------------------------------------------------------*/
   if (atexit_func_count < MAX_ATEXIT_FUN)
   {
      /*--------------------------------------------------------------------*/
      /* Choose the next available entry for registering atexit functions.  */
      /*--------------------------------------------------------------------*/
      int allocated_entry = atexit_func_count++;

      /*--------------------------------------------------------------------*/
      /* Populate the allocated entry with the necessary details.           */
      /*--------------------------------------------------------------------*/
      atexit_func[allocated_entry].next                = NULL;
      atexit_func[allocated_entry].object              = &__atexit_func_id__;
      atexit_func[allocated_entry].destruction_routine = fun;

      /*--------------------------------------------------------------------*/
      /* Register the atexit function for processing at exit.               */
      /*--------------------------------------------------------------------*/
      __add_dtor(&(atexit_func[allocated_entry]));

      err_code = 0;
   }

   __TI_data_synch_WBINV(&atexit_func_count, sizeof(int));
   __TI_data_synch_WBINV(&atexit_func, sizeof(atexit_func));
   __TI_resource_unlock(__TI_LOCK_ATEXIT);

   return err_code;
}
#endif /* defined(__TI_EABI_SUPPORT__) || defined(__TI_EABI__) */
/*** END TI ADD ***/

/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++ Runtime                            - | \^/ | -      *
*                                                               \   /         *
*                                                             /  | |  \       *
* Copyright 1992-2017 Edison Design Group Inc.                   [_]          *
*                                                                             *
******************************************************************************/

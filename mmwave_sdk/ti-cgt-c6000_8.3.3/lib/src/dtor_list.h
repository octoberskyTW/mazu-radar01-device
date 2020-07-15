/*****************************************************************************/
/* dtor_list.h                                                               */
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

Declarations relating to dtor_list.c -- destruction list processing.

*/

#ifndef DTOR_LIST_H
#define DTOR_LIST_H 1
/*** START TI REMOVE ***/
/* TI implementation of RTS does not need the definition in main.h 
TI RTS only needs IA64_ABI part of this file. */
#if 0
#ifndef MAIN_H
#include "main.h"
#endif /* ifndef MAIN_H */
#endif
/*** END TI REMOVE ***/
/*
Data structure used to build a list of static object destructions
to be performed at the end of execution.  Entries are added to the
list each time a static object is created.  New objects are added
to the front of the list.
*/
typedef struct a_needed_destruction *a_needed_destruction_ptr;
typedef struct a_needed_destruction {
  a_needed_destruction_ptr
                next;
                        /* Pointer to the next entry in the list. */
  void          *object;
                        /* Pointer to the object to be destroyed if this
                           is a "simple" destruction, or a NULL pointer
                           if this is a "complex" destruction.  A simple
                           destruction is one that can be done with
                           a single call to the destructor passing an
                           object pointer and a destruction flag. */
#ifndef __EDG_IA64_ABI
  a_void_function_ptr
#else /* defined(__EDG_IA64_ABI) */
  a_destructor_ptr
#endif /* defined(__EDG_IA64_ABI) */
                destruction_routine;
                        /* For a simple destruction, this points to the
                           destructor to be called. For a complex destruction,
                           this is a pointer to a function that when called,
                           will call the necessary destructors. */
#ifdef __EDG_IA64_ABI
  a_dso_handle  dso_handle;
                        /* The DSO handle associated with this destruction, or
                           NULL if this destruction is associated with the
                           main program. */
#endif /* ifdef EDG_IA64_ABI */
} a_needed_destruction;

#ifndef __EDG_IA64_ABI
extern void __process_needed_destructions(void);

extern void __process_destruction_list(
                                   a_needed_destruction_ptr *destruction_list);

extern void __record_destruction_on_list(
                                    a_needed_destruction_ptr *destruction_list,
                                    a_needed_destruction_ptr ndp);

EXTERN_C void __record_needed_destruction(a_needed_destruction_ptr ndp);

EXTERN_C void __record_needed_thread_destruction(a_needed_destruction_ptr ndp);

#else /* ifdef __EDG_IA64_ABI */
#if !(SYSTEM_RUNTIME_HAS_IA64_ATEXIT && SYSTEM_RUNTIME_HAS_IA64_THREAD_ATEXIT)

extern void __finalize_destructions(a_needed_destruction_ptr *destruction_list,
                                    a_dso_handle             dso_handle);

extern int __add_destruction_to_list(
                              a_needed_destruction_ptr *destruction_list,
                              a_cxa_dtor_ptr           destruction_routine,
                              void                     *object,
                              a_dso_handle             dso_handle);
#endif /* !(SYSTEM_RUNTIME_HAS_IA64_ATEXIT && SYSTEM_RUNTIME_HAS_IA64_...) */
#endif /* ifndef __EDG_IA64_ABI */

#if RUNTIME_DOES_THREAD_LOCAL_DESTRUCTIONS
extern thread_local a_needed_destruction_ptr
                __thread_needed_destruction_head;
#endif /* RUNTIME_DOES_THREAD_LOCAL_DESTRUCTIONS */



#endif /* DTOR_LIST_H */


/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++ Runtime                            - | \^/ | -      *
*                                                               \   /         *
*                                                             /  | |  \       *
* Copyright 1992-2017 Edison Design Group Inc.                   [_]          *
*                                                                             *
******************************************************************************/

/*****************************************************************************/
/* vtbl.h                                                                    */
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

Virtual function table entry layout.

*/

#ifndef _VTBL_H
#define _VTBL_H

#ifndef __EDG_IA64_ABI
/*** START TI ADD ***/
struct a_vtbl_entry
{
   __EDG_DELTA_TYPE delta;      /* OFFSET TO GET TO THE COMPLETE OBJECT   */
   void           (*func)();    /* VIRTUAL FUNCTION TO BE CALLED          */
};
/*** END TI ADD ***/
/*** START TI REMOVE ***/
#if 0
struct a_vtbl_entry {
  __EDG_DELTA_TYPE
                delta;
                        /* Value to be added to the "this" pointer to adjust
                           it to point to the class for which the virtual
                           function is actually defined. */
  __EDG_VIRTUAL_FUNCTION_INDEX_TYPE
                index;
                        /* Index into the virtual function table.  Only
                           used in member function pointers, not present in
                           vtbl entries.  Cfront uses the same structure for
                           both member pointers and vtbl entries, so this is
                           present for cfront compatibility. */
  union {
    a_void_function_ptr
                ptr;
                        /* Pointer to the function to be called. */
    a_type_info_impl_ptr
                type_info_impl;
                        /* Pointer to the type information implementation
                           entry.  This is present in slot zero of the
                           virtual function table. */
  } function;
};
#endif
/*** END TI REMOVE ***/

#else /* defined(__EDG_IA64_ABI) */

typedef __EDG_IA64_VTABLE_ENTRY_TYPE a_vtbl_entry;

#endif /* defined(__EDG_IA64_ABI) */

typedef
/*** START TI ADD ***/
const
/*** END TI ADD ***/
a_vtbl_entry *a_vtbl_entry_ptr;

#endif /* ifndef _VTBL_H */


/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++ Runtime                            - | \^/ | -      *
*                                                               \   /         *
*                                                             /  | |  \       *
* Copyright 1992-2017 Edison Design Group Inc.                   [_]          *
*                                                                             *
******************************************************************************/

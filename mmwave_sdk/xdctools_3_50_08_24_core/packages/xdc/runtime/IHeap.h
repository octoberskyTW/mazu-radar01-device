/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-E10
 */

/*
 * ======== GENERATED SECTIONS ========
 *
 *     PROLOGUE
 *     INCLUDES
 *
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef xdc_runtime_IHeap__include
#define xdc_runtime_IHeap__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_IHeap__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_IHeap___VERS 200


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <xdc/runtime/package/package.defs.h>

#include <xdc/runtime/IModule.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct xdc_runtime_IHeap_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_IHeap_Fxns__ {
    const xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Ptr (*alloc)(void* inst, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb);
    xdc_Void (*free)(void* inst, xdc_Ptr block, xdc_SizeT size);
    xdc_Bool (*isBlocking)(void* inst);
    xdc_Void (*getStats)(void* inst, xdc_runtime_Memory_Stats* stats);
    xdc_runtime_Types_SysFxns2 __sfxns;
};
#ifndef xdc_runtime_IHeap_Module__BASE__CR

/* Interface__BASE__C */
__extern const xdc_runtime_Types_Base xdc_runtime_IHeap_Interface__BASE__C;
#else
#define xdc_runtime_IHeap_Interface__BASE__C (*((xdc_runtime_Types_Base *)(xdcRomConstPtr + xdc_runtime_IHeap_Interface__BASE__C_offset)))
#endif


/*
 * ======== FUNCTION STUBS ========
 */

/* create */
xdc__CODESECT(xdc_runtime_IHeap_create, "xdc_runtime_IHeap_create")
__extern xdc_runtime_IHeap_Handle xdc_runtime_IHeap_create(xdc_runtime_IHeap_Module mod, const xdc_runtime_IHeap_Params *prms, xdc_runtime_Error_Block *eb);

/* delete */
xdc__CODESECT(xdc_runtime_IHeap_delete, "xdc_runtime_IHeap_delete")
__extern xdc_Void xdc_runtime_IHeap_delete(xdc_runtime_IHeap_Handle *inst);

/* Handle_to_Module */
static inline xdc_runtime_IHeap_Module xdc_runtime_IHeap_Handle_to_Module(xdc_runtime_IHeap_Handle inst);
static inline xdc_runtime_IHeap_Module xdc_runtime_IHeap_Handle_to_Module(xdc_runtime_IHeap_Handle inst)
{
    return inst->__fxns;
}

/* Handle_label */
static inline xdc_runtime_Types_Label *xdc_runtime_IHeap_Handle_label(xdc_runtime_IHeap_Handle inst, xdc_runtime_Types_Label *lab);
static inline xdc_runtime_Types_Label *xdc_runtime_IHeap_Handle_label(xdc_runtime_IHeap_Handle inst, xdc_runtime_Types_Label *lab)
{
    return inst->__fxns->__sysp->__label(inst, lab);
}

/* Module_id */
static inline xdc_runtime_Types_ModuleId xdc_runtime_IHeap_Module_id(xdc_runtime_IHeap_Module mod);
static inline xdc_runtime_Types_ModuleId xdc_runtime_IHeap_Module_id(xdc_runtime_IHeap_Module mod)
{
    return mod->__sysp->__mid;
}

/* alloc */
static inline xdc_Ptr xdc_runtime_IHeap_alloc(xdc_runtime_IHeap_Handle inst, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block *eb);
static inline xdc_Ptr xdc_runtime_IHeap_alloc( xdc_runtime_IHeap_Handle inst, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block *eb )
{
    return inst->__fxns->alloc((void*)inst, size, align, eb);
}

/* free */
static inline xdc_Void xdc_runtime_IHeap_free(xdc_runtime_IHeap_Handle inst, xdc_Ptr block, xdc_SizeT size);
static inline xdc_Void xdc_runtime_IHeap_free( xdc_runtime_IHeap_Handle inst, xdc_Ptr block, xdc_SizeT size )
{
    inst->__fxns->free((void*)inst, block, size);
}

/* isBlocking */
static inline xdc_Bool xdc_runtime_IHeap_isBlocking(xdc_runtime_IHeap_Handle inst);
static inline xdc_Bool xdc_runtime_IHeap_isBlocking( xdc_runtime_IHeap_Handle inst )
{
    return inst->__fxns->isBlocking((void*)inst);
}

/* getStats */
static inline xdc_Void xdc_runtime_IHeap_getStats(xdc_runtime_IHeap_Handle inst, xdc_runtime_Memory_Stats *stats);
static inline xdc_Void xdc_runtime_IHeap_getStats( xdc_runtime_IHeap_Handle inst, xdc_runtime_Memory_Stats *stats )
{
    inst->__fxns->getStats((void*)inst, stats);
}


/*
 * ======== FUNCTION SELECTORS ========
 */

/* These functions return function pointers for module and instance functions.
 * The functions accept modules and instances declared as types defined in this
 * interface, but they return functions defined for the actual objects passed
 * as parameters. These functions are not invoked by any generated code or
 * XDCtools internal code.
 */

/* alloc_{FxnT,fxnP} */
typedef xdc_Ptr (*xdc_runtime_IHeap_alloc_FxnT)(xdc_Void *inst, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb);
static inline xdc_runtime_IHeap_alloc_FxnT xdc_runtime_IHeap_alloc_fxnP(xdc_runtime_IHeap_Handle inst);
static inline xdc_runtime_IHeap_alloc_FxnT xdc_runtime_IHeap_alloc_fxnP(xdc_runtime_IHeap_Handle inst)
{
    return (xdc_runtime_IHeap_alloc_FxnT)inst->__fxns->alloc;
}

/* free_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_IHeap_free_FxnT)(xdc_Void *inst, xdc_Ptr block, xdc_SizeT size);
static inline xdc_runtime_IHeap_free_FxnT xdc_runtime_IHeap_free_fxnP(xdc_runtime_IHeap_Handle inst);
static inline xdc_runtime_IHeap_free_FxnT xdc_runtime_IHeap_free_fxnP(xdc_runtime_IHeap_Handle inst)
{
    return (xdc_runtime_IHeap_free_FxnT)inst->__fxns->free;
}

/* isBlocking_{FxnT,fxnP} */
typedef xdc_Bool (*xdc_runtime_IHeap_isBlocking_FxnT)(xdc_Void *inst);
static inline xdc_runtime_IHeap_isBlocking_FxnT xdc_runtime_IHeap_isBlocking_fxnP(xdc_runtime_IHeap_Handle inst);
static inline xdc_runtime_IHeap_isBlocking_FxnT xdc_runtime_IHeap_isBlocking_fxnP(xdc_runtime_IHeap_Handle inst)
{
    return (xdc_runtime_IHeap_isBlocking_FxnT)inst->__fxns->isBlocking;
}

/* getStats_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_IHeap_getStats_FxnT)(xdc_Void *inst, xdc_runtime_Memory_Stats* stats);
static inline xdc_runtime_IHeap_getStats_FxnT xdc_runtime_IHeap_getStats_fxnP(xdc_runtime_IHeap_Handle inst);
static inline xdc_runtime_IHeap_getStats_FxnT xdc_runtime_IHeap_getStats_fxnP(xdc_runtime_IHeap_Handle inst)
{
    return (xdc_runtime_IHeap_getStats_FxnT)inst->__fxns->getStats;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef xdc_runtime_IHeap__top__
#undef __nested__
#endif

#endif /* xdc_runtime_IHeap__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_IHeap__nolocalnames)

#ifndef xdc_runtime_IHeap__localnames__done
#define xdc_runtime_IHeap__localnames__done

/* module prefix */
#define IHeap_Instance xdc_runtime_IHeap_Instance
#define IHeap_Handle xdc_runtime_IHeap_Handle
#define IHeap_Module xdc_runtime_IHeap_Module
#define IHeap_Params xdc_runtime_IHeap_Params
#define IHeap_alloc xdc_runtime_IHeap_alloc
#define IHeap_alloc_fxnP xdc_runtime_IHeap_alloc_fxnP
#define IHeap_alloc_FxnT xdc_runtime_IHeap_alloc_FxnT
#define IHeap_free xdc_runtime_IHeap_free
#define IHeap_free_fxnP xdc_runtime_IHeap_free_fxnP
#define IHeap_free_FxnT xdc_runtime_IHeap_free_FxnT
#define IHeap_isBlocking xdc_runtime_IHeap_isBlocking
#define IHeap_isBlocking_fxnP xdc_runtime_IHeap_isBlocking_fxnP
#define IHeap_isBlocking_FxnT xdc_runtime_IHeap_isBlocking_FxnT
#define IHeap_getStats xdc_runtime_IHeap_getStats
#define IHeap_getStats_fxnP xdc_runtime_IHeap_getStats_fxnP
#define IHeap_getStats_FxnT xdc_runtime_IHeap_getStats_FxnT
#define IHeap_Module_name xdc_runtime_IHeap_Module_name
#define IHeap_create xdc_runtime_IHeap_create
#define IHeap_delete xdc_runtime_IHeap_delete
#define IHeap_Handle_label xdc_runtime_IHeap_Handle_label
#define IHeap_Handle_to_Module xdc_runtime_IHeap_Handle_to_Module

#endif /* xdc_runtime_IHeap__localnames__done */
#endif
/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 7-31-2018 11:49:29; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


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

#ifndef xdc_runtime_knl_ISync__include
#define xdc_runtime_knl_ISync__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_knl_ISync__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_knl_ISync___VERS 200


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <xdc/runtime/knl/package/package.defs.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* WaitStatus */
enum xdc_runtime_knl_ISync_WaitStatus {
    xdc_runtime_knl_ISync_WaitStatus_ERROR = -1,
    xdc_runtime_knl_ISync_WaitStatus_TIMEOUT = 0,
    xdc_runtime_knl_ISync_WaitStatus_SUCCESS = 1
};
typedef enum xdc_runtime_knl_ISync_WaitStatus xdc_runtime_knl_ISync_WaitStatus;

/* Q_BLOCKING */
#define xdc_runtime_knl_ISync_Q_BLOCKING (1)

/* WAIT_FOREVER */
#define xdc_runtime_knl_ISync_WAIT_FOREVER (~(0))

/* NO_WAIT */
#define xdc_runtime_knl_ISync_NO_WAIT (0)


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct xdc_runtime_knl_ISync_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_knl_ISync_Fxns__ {
    const xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*query)(void* inst, xdc_Int qual);
    xdc_Void (*signal)(void* inst);
    xdc_Int (*wait)(void* inst, xdc_UInt timeout, xdc_runtime_Error_Block* eb);
    xdc_runtime_Types_SysFxns2 __sfxns;
};
#ifndef xdc_runtime_knl_ISync_Module__BASE__CR

/* Interface__BASE__C */
__extern const xdc_runtime_Types_Base xdc_runtime_knl_ISync_Interface__BASE__C;
#else
#define xdc_runtime_knl_ISync_Interface__BASE__C (*((xdc_runtime_Types_Base *)(xdcRomConstPtr + xdc_runtime_knl_ISync_Interface__BASE__C_offset)))
#endif


/*
 * ======== FUNCTION STUBS ========
 */

/* create */
xdc__CODESECT(xdc_runtime_knl_ISync_create, "xdc_runtime_knl_ISync_create")
__extern xdc_runtime_knl_ISync_Handle xdc_runtime_knl_ISync_create(xdc_runtime_knl_ISync_Module mod, const xdc_runtime_knl_ISync_Params *prms, xdc_runtime_Error_Block *eb);

/* delete */
xdc__CODESECT(xdc_runtime_knl_ISync_delete, "xdc_runtime_knl_ISync_delete")
__extern xdc_Void xdc_runtime_knl_ISync_delete(xdc_runtime_knl_ISync_Handle *inst);

/* Handle_to_Module */
static inline xdc_runtime_knl_ISync_Module xdc_runtime_knl_ISync_Handle_to_Module(xdc_runtime_knl_ISync_Handle inst);
static inline xdc_runtime_knl_ISync_Module xdc_runtime_knl_ISync_Handle_to_Module(xdc_runtime_knl_ISync_Handle inst)
{
    return inst->__fxns;
}

/* Handle_label */
static inline xdc_runtime_Types_Label *xdc_runtime_knl_ISync_Handle_label(xdc_runtime_knl_ISync_Handle inst, xdc_runtime_Types_Label *lab);
static inline xdc_runtime_Types_Label *xdc_runtime_knl_ISync_Handle_label(xdc_runtime_knl_ISync_Handle inst, xdc_runtime_Types_Label *lab)
{
    return inst->__fxns->__sysp->__label(inst, lab);
}

/* Module_id */
static inline xdc_runtime_Types_ModuleId xdc_runtime_knl_ISync_Module_id(xdc_runtime_knl_ISync_Module mod);
static inline xdc_runtime_Types_ModuleId xdc_runtime_knl_ISync_Module_id(xdc_runtime_knl_ISync_Module mod)
{
    return mod->__sysp->__mid;
}

/* query */
static inline xdc_Bool xdc_runtime_knl_ISync_query(xdc_runtime_knl_ISync_Handle inst, xdc_Int qual);
static inline xdc_Bool xdc_runtime_knl_ISync_query( xdc_runtime_knl_ISync_Handle inst, xdc_Int qual )
{
    return inst->__fxns->query((void*)inst, qual);
}

/* signal */
static inline xdc_Void xdc_runtime_knl_ISync_signal(xdc_runtime_knl_ISync_Handle inst);
static inline xdc_Void xdc_runtime_knl_ISync_signal( xdc_runtime_knl_ISync_Handle inst )
{
    inst->__fxns->signal((void*)inst);
}

/* wait */
static inline xdc_Int xdc_runtime_knl_ISync_wait(xdc_runtime_knl_ISync_Handle inst, xdc_UInt timeout, xdc_runtime_Error_Block *eb);
static inline xdc_Int xdc_runtime_knl_ISync_wait( xdc_runtime_knl_ISync_Handle inst, xdc_UInt timeout, xdc_runtime_Error_Block *eb )
{
    return inst->__fxns->wait((void*)inst, timeout, eb);
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

/* query_{FxnT,fxnP} */
typedef xdc_Bool (*xdc_runtime_knl_ISync_query_FxnT)(xdc_Void *inst, xdc_Int qual);
static inline xdc_runtime_knl_ISync_query_FxnT xdc_runtime_knl_ISync_query_fxnP(xdc_runtime_knl_ISync_Handle inst);
static inline xdc_runtime_knl_ISync_query_FxnT xdc_runtime_knl_ISync_query_fxnP(xdc_runtime_knl_ISync_Handle inst)
{
    return (xdc_runtime_knl_ISync_query_FxnT)inst->__fxns->query;
}

/* signal_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_knl_ISync_signal_FxnT)(xdc_Void *inst);
static inline xdc_runtime_knl_ISync_signal_FxnT xdc_runtime_knl_ISync_signal_fxnP(xdc_runtime_knl_ISync_Handle inst);
static inline xdc_runtime_knl_ISync_signal_FxnT xdc_runtime_knl_ISync_signal_fxnP(xdc_runtime_knl_ISync_Handle inst)
{
    return (xdc_runtime_knl_ISync_signal_FxnT)inst->__fxns->signal;
}

/* wait_{FxnT,fxnP} */
typedef xdc_Int (*xdc_runtime_knl_ISync_wait_FxnT)(xdc_Void *inst, xdc_UInt timeout, xdc_runtime_Error_Block* eb);
static inline xdc_runtime_knl_ISync_wait_FxnT xdc_runtime_knl_ISync_wait_fxnP(xdc_runtime_knl_ISync_Handle inst);
static inline xdc_runtime_knl_ISync_wait_FxnT xdc_runtime_knl_ISync_wait_fxnP(xdc_runtime_knl_ISync_Handle inst)
{
    return (xdc_runtime_knl_ISync_wait_FxnT)inst->__fxns->wait;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef xdc_runtime_knl_ISync__top__
#undef __nested__
#endif

#endif /* xdc_runtime_knl_ISync__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_knl_ISync__nolocalnames)

#ifndef xdc_runtime_knl_ISync__localnames__done
#define xdc_runtime_knl_ISync__localnames__done

/* module prefix */
#define ISync_Instance xdc_runtime_knl_ISync_Instance
#define ISync_Handle xdc_runtime_knl_ISync_Handle
#define ISync_Module xdc_runtime_knl_ISync_Module
#define ISync_WaitStatus xdc_runtime_knl_ISync_WaitStatus
#define ISync_Q_BLOCKING xdc_runtime_knl_ISync_Q_BLOCKING
#define ISync_WAIT_FOREVER xdc_runtime_knl_ISync_WAIT_FOREVER
#define ISync_NO_WAIT xdc_runtime_knl_ISync_NO_WAIT
#define ISync_WaitStatus_ERROR xdc_runtime_knl_ISync_WaitStatus_ERROR
#define ISync_WaitStatus_TIMEOUT xdc_runtime_knl_ISync_WaitStatus_TIMEOUT
#define ISync_WaitStatus_SUCCESS xdc_runtime_knl_ISync_WaitStatus_SUCCESS
#define ISync_Params xdc_runtime_knl_ISync_Params
#define ISync_query xdc_runtime_knl_ISync_query
#define ISync_query_fxnP xdc_runtime_knl_ISync_query_fxnP
#define ISync_query_FxnT xdc_runtime_knl_ISync_query_FxnT
#define ISync_signal xdc_runtime_knl_ISync_signal
#define ISync_signal_fxnP xdc_runtime_knl_ISync_signal_fxnP
#define ISync_signal_FxnT xdc_runtime_knl_ISync_signal_FxnT
#define ISync_wait xdc_runtime_knl_ISync_wait
#define ISync_wait_fxnP xdc_runtime_knl_ISync_wait_fxnP
#define ISync_wait_FxnT xdc_runtime_knl_ISync_wait_FxnT
#define ISync_Module_name xdc_runtime_knl_ISync_Module_name
#define ISync_create xdc_runtime_knl_ISync_create
#define ISync_delete xdc_runtime_knl_ISync_delete
#define ISync_Handle_label xdc_runtime_knl_ISync_Handle_label
#define ISync_Handle_to_Module xdc_runtime_knl_ISync_Handle_to_Module

#endif /* xdc_runtime_knl_ISync__localnames__done */
#endif
/*
 *  @(#) xdc.runtime.knl; 1, 0, 0,0; 7-31-2018 11:49:36; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


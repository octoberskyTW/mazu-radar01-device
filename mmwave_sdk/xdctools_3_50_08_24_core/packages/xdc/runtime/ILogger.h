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

#ifndef xdc_runtime_ILogger__include
#define xdc_runtime_ILogger__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_ILogger__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_ILogger___VERS 200


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <xdc/runtime/package/package.defs.h>

#include <xdc/runtime/IModule.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Types.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct xdc_runtime_ILogger_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_ILogger_Fxns__ {
    const xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*enable)(void* inst);
    xdc_Bool (*disable)(void* inst);
    xdc_Void (*write0)(void* inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid);
    xdc_Void (*write1)(void* inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1);
    xdc_Void (*write2)(void* inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2);
    xdc_Void (*write4)(void* inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4);
    xdc_Void (*write8)(void* inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4, xdc_IArg a5, xdc_IArg a6, xdc_IArg a7, xdc_IArg a8);
    xdc_runtime_Types_SysFxns2 __sfxns;
};
#ifndef xdc_runtime_ILogger_Module__BASE__CR

/* Interface__BASE__C */
__extern const xdc_runtime_Types_Base xdc_runtime_ILogger_Interface__BASE__C;
#else
#define xdc_runtime_ILogger_Interface__BASE__C (*((xdc_runtime_Types_Base *)(xdcRomConstPtr + xdc_runtime_ILogger_Interface__BASE__C_offset)))
#endif


/*
 * ======== FUNCTION STUBS ========
 */

/* create */
xdc__CODESECT(xdc_runtime_ILogger_create, "xdc_runtime_ILogger_create")
__extern xdc_runtime_ILogger_Handle xdc_runtime_ILogger_create(xdc_runtime_ILogger_Module mod, const xdc_runtime_ILogger_Params *prms, xdc_runtime_Error_Block *eb);

/* delete */
xdc__CODESECT(xdc_runtime_ILogger_delete, "xdc_runtime_ILogger_delete")
__extern xdc_Void xdc_runtime_ILogger_delete(xdc_runtime_ILogger_Handle *inst);

/* Handle_to_Module */
static inline xdc_runtime_ILogger_Module xdc_runtime_ILogger_Handle_to_Module(xdc_runtime_ILogger_Handle inst);
static inline xdc_runtime_ILogger_Module xdc_runtime_ILogger_Handle_to_Module(xdc_runtime_ILogger_Handle inst)
{
    return inst->__fxns;
}

/* Handle_label */
static inline xdc_runtime_Types_Label *xdc_runtime_ILogger_Handle_label(xdc_runtime_ILogger_Handle inst, xdc_runtime_Types_Label *lab);
static inline xdc_runtime_Types_Label *xdc_runtime_ILogger_Handle_label(xdc_runtime_ILogger_Handle inst, xdc_runtime_Types_Label *lab)
{
    return inst->__fxns->__sysp->__label(inst, lab);
}

/* Module_id */
static inline xdc_runtime_Types_ModuleId xdc_runtime_ILogger_Module_id(xdc_runtime_ILogger_Module mod);
static inline xdc_runtime_Types_ModuleId xdc_runtime_ILogger_Module_id(xdc_runtime_ILogger_Module mod)
{
    return mod->__sysp->__mid;
}

/* enable */
static inline xdc_Bool xdc_runtime_ILogger_enable(xdc_runtime_ILogger_Handle inst);
static inline xdc_Bool xdc_runtime_ILogger_enable( xdc_runtime_ILogger_Handle inst )
{
    return inst->__fxns->enable((void*)inst);
}

/* disable */
static inline xdc_Bool xdc_runtime_ILogger_disable(xdc_runtime_ILogger_Handle inst);
static inline xdc_Bool xdc_runtime_ILogger_disable( xdc_runtime_ILogger_Handle inst )
{
    return inst->__fxns->disable((void*)inst);
}

/* write0 */
static inline xdc_Void xdc_runtime_ILogger_write0(xdc_runtime_ILogger_Handle inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid);
static inline xdc_Void xdc_runtime_ILogger_write0( xdc_runtime_ILogger_Handle inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid )
{
    inst->__fxns->write0((void*)inst, evt, mid);
}

/* write1 */
static inline xdc_Void xdc_runtime_ILogger_write1(xdc_runtime_ILogger_Handle inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1);
static inline xdc_Void xdc_runtime_ILogger_write1( xdc_runtime_ILogger_Handle inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1 )
{
    inst->__fxns->write1((void*)inst, evt, mid, a1);
}

/* write2 */
static inline xdc_Void xdc_runtime_ILogger_write2(xdc_runtime_ILogger_Handle inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2);
static inline xdc_Void xdc_runtime_ILogger_write2( xdc_runtime_ILogger_Handle inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2 )
{
    inst->__fxns->write2((void*)inst, evt, mid, a1, a2);
}

/* write4 */
static inline xdc_Void xdc_runtime_ILogger_write4(xdc_runtime_ILogger_Handle inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4);
static inline xdc_Void xdc_runtime_ILogger_write4( xdc_runtime_ILogger_Handle inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4 )
{
    inst->__fxns->write4((void*)inst, evt, mid, a1, a2, a3, a4);
}

/* write8 */
static inline xdc_Void xdc_runtime_ILogger_write8(xdc_runtime_ILogger_Handle inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4, xdc_IArg a5, xdc_IArg a6, xdc_IArg a7, xdc_IArg a8);
static inline xdc_Void xdc_runtime_ILogger_write8( xdc_runtime_ILogger_Handle inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4, xdc_IArg a5, xdc_IArg a6, xdc_IArg a7, xdc_IArg a8 )
{
    inst->__fxns->write8((void*)inst, evt, mid, a1, a2, a3, a4, a5, a6, a7, a8);
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

/* enable_{FxnT,fxnP} */
typedef xdc_Bool (*xdc_runtime_ILogger_enable_FxnT)(xdc_Void *inst);
static inline xdc_runtime_ILogger_enable_FxnT xdc_runtime_ILogger_enable_fxnP(xdc_runtime_ILogger_Handle inst);
static inline xdc_runtime_ILogger_enable_FxnT xdc_runtime_ILogger_enable_fxnP(xdc_runtime_ILogger_Handle inst)
{
    return (xdc_runtime_ILogger_enable_FxnT)inst->__fxns->enable;
}

/* disable_{FxnT,fxnP} */
typedef xdc_Bool (*xdc_runtime_ILogger_disable_FxnT)(xdc_Void *inst);
static inline xdc_runtime_ILogger_disable_FxnT xdc_runtime_ILogger_disable_fxnP(xdc_runtime_ILogger_Handle inst);
static inline xdc_runtime_ILogger_disable_FxnT xdc_runtime_ILogger_disable_fxnP(xdc_runtime_ILogger_Handle inst)
{
    return (xdc_runtime_ILogger_disable_FxnT)inst->__fxns->disable;
}

/* write0_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_ILogger_write0_FxnT)(xdc_Void *inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid);
static inline xdc_runtime_ILogger_write0_FxnT xdc_runtime_ILogger_write0_fxnP(xdc_runtime_ILogger_Handle inst);
static inline xdc_runtime_ILogger_write0_FxnT xdc_runtime_ILogger_write0_fxnP(xdc_runtime_ILogger_Handle inst)
{
    return (xdc_runtime_ILogger_write0_FxnT)inst->__fxns->write0;
}

/* write1_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_ILogger_write1_FxnT)(xdc_Void *inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1);
static inline xdc_runtime_ILogger_write1_FxnT xdc_runtime_ILogger_write1_fxnP(xdc_runtime_ILogger_Handle inst);
static inline xdc_runtime_ILogger_write1_FxnT xdc_runtime_ILogger_write1_fxnP(xdc_runtime_ILogger_Handle inst)
{
    return (xdc_runtime_ILogger_write1_FxnT)inst->__fxns->write1;
}

/* write2_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_ILogger_write2_FxnT)(xdc_Void *inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2);
static inline xdc_runtime_ILogger_write2_FxnT xdc_runtime_ILogger_write2_fxnP(xdc_runtime_ILogger_Handle inst);
static inline xdc_runtime_ILogger_write2_FxnT xdc_runtime_ILogger_write2_fxnP(xdc_runtime_ILogger_Handle inst)
{
    return (xdc_runtime_ILogger_write2_FxnT)inst->__fxns->write2;
}

/* write4_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_ILogger_write4_FxnT)(xdc_Void *inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4);
static inline xdc_runtime_ILogger_write4_FxnT xdc_runtime_ILogger_write4_fxnP(xdc_runtime_ILogger_Handle inst);
static inline xdc_runtime_ILogger_write4_FxnT xdc_runtime_ILogger_write4_fxnP(xdc_runtime_ILogger_Handle inst)
{
    return (xdc_runtime_ILogger_write4_FxnT)inst->__fxns->write4;
}

/* write8_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_ILogger_write8_FxnT)(xdc_Void *inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4, xdc_IArg a5, xdc_IArg a6, xdc_IArg a7, xdc_IArg a8);
static inline xdc_runtime_ILogger_write8_FxnT xdc_runtime_ILogger_write8_fxnP(xdc_runtime_ILogger_Handle inst);
static inline xdc_runtime_ILogger_write8_FxnT xdc_runtime_ILogger_write8_fxnP(xdc_runtime_ILogger_Handle inst)
{
    return (xdc_runtime_ILogger_write8_FxnT)inst->__fxns->write8;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef xdc_runtime_ILogger__top__
#undef __nested__
#endif

#endif /* xdc_runtime_ILogger__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_ILogger__nolocalnames)

#ifndef xdc_runtime_ILogger__localnames__done
#define xdc_runtime_ILogger__localnames__done

/* module prefix */
#define ILogger_Instance xdc_runtime_ILogger_Instance
#define ILogger_Handle xdc_runtime_ILogger_Handle
#define ILogger_Module xdc_runtime_ILogger_Module
#define ILogger_Params xdc_runtime_ILogger_Params
#define ILogger_enable xdc_runtime_ILogger_enable
#define ILogger_enable_fxnP xdc_runtime_ILogger_enable_fxnP
#define ILogger_enable_FxnT xdc_runtime_ILogger_enable_FxnT
#define ILogger_disable xdc_runtime_ILogger_disable
#define ILogger_disable_fxnP xdc_runtime_ILogger_disable_fxnP
#define ILogger_disable_FxnT xdc_runtime_ILogger_disable_FxnT
#define ILogger_write0 xdc_runtime_ILogger_write0
#define ILogger_write0_fxnP xdc_runtime_ILogger_write0_fxnP
#define ILogger_write0_FxnT xdc_runtime_ILogger_write0_FxnT
#define ILogger_write1 xdc_runtime_ILogger_write1
#define ILogger_write1_fxnP xdc_runtime_ILogger_write1_fxnP
#define ILogger_write1_FxnT xdc_runtime_ILogger_write1_FxnT
#define ILogger_write2 xdc_runtime_ILogger_write2
#define ILogger_write2_fxnP xdc_runtime_ILogger_write2_fxnP
#define ILogger_write2_FxnT xdc_runtime_ILogger_write2_FxnT
#define ILogger_write4 xdc_runtime_ILogger_write4
#define ILogger_write4_fxnP xdc_runtime_ILogger_write4_fxnP
#define ILogger_write4_FxnT xdc_runtime_ILogger_write4_FxnT
#define ILogger_write8 xdc_runtime_ILogger_write8
#define ILogger_write8_fxnP xdc_runtime_ILogger_write8_fxnP
#define ILogger_write8_FxnT xdc_runtime_ILogger_write8_FxnT
#define ILogger_Module_name xdc_runtime_ILogger_Module_name
#define ILogger_delete xdc_runtime_ILogger_delete
#define ILogger_Handle_label xdc_runtime_ILogger_Handle_label
#define ILogger_Handle_to_Module xdc_runtime_ILogger_Handle_to_Module

#endif /* xdc_runtime_ILogger__localnames__done */
#endif
/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 7-31-2018 11:49:29; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


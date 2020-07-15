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

#ifndef xdc_runtime_ISystemSupport__include
#define xdc_runtime_ISystemSupport__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_ISystemSupport__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_ISystemSupport___VERS 200


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/package/package.defs.h>

#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_ISystemSupport_Fxns__ {
    const xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Void (*abort)(xdc_CString str);
    xdc_Void (*exit)(xdc_Int stat);
    xdc_Void (*flush)(void);
    xdc_Void (*putch)(xdc_Char ch);
    xdc_Bool (*ready)(void);
    xdc_runtime_Types_SysFxns2 __sfxns;
};
#ifndef xdc_runtime_ISystemSupport_Module__BASE__CR

/* Interface__BASE__C */
__extern const xdc_runtime_Types_Base xdc_runtime_ISystemSupport_Interface__BASE__C;
#else
#define xdc_runtime_ISystemSupport_Interface__BASE__C (*((xdc_runtime_Types_Base *)(xdcRomConstPtr + xdc_runtime_ISystemSupport_Interface__BASE__C_offset)))
#endif


/*
 * ======== FUNCTION STUBS ========
 */

/* Module_id */
static inline xdc_runtime_Types_ModuleId xdc_runtime_ISystemSupport_Module_id(xdc_runtime_ISystemSupport_Module mod);
static inline xdc_runtime_Types_ModuleId xdc_runtime_ISystemSupport_Module_id(xdc_runtime_ISystemSupport_Module mod)
{
    return mod->__sysp->__mid;
}

/* abort */
static inline xdc_Void xdc_runtime_ISystemSupport_abort(xdc_runtime_ISystemSupport_Module mod, xdc_CString str);
static inline xdc_Void xdc_runtime_ISystemSupport_abort( xdc_runtime_ISystemSupport_Module mod, xdc_CString str )
{
    mod->abort(str);
}

/* exit */
static inline xdc_Void xdc_runtime_ISystemSupport_exit(xdc_runtime_ISystemSupport_Module mod, xdc_Int stat);
static inline xdc_Void xdc_runtime_ISystemSupport_exit( xdc_runtime_ISystemSupport_Module mod, xdc_Int stat )
{
    mod->exit(stat);
}

/* flush */
static inline xdc_Void xdc_runtime_ISystemSupport_flush(xdc_runtime_ISystemSupport_Module mod);
static inline xdc_Void xdc_runtime_ISystemSupport_flush( xdc_runtime_ISystemSupport_Module mod )
{
    mod->flush();
}

/* putch */
static inline xdc_Void xdc_runtime_ISystemSupport_putch(xdc_runtime_ISystemSupport_Module mod, xdc_Char ch);
static inline xdc_Void xdc_runtime_ISystemSupport_putch( xdc_runtime_ISystemSupport_Module mod, xdc_Char ch )
{
    mod->putch(ch);
}

/* ready */
static inline xdc_Bool xdc_runtime_ISystemSupport_ready(xdc_runtime_ISystemSupport_Module mod);
static inline xdc_Bool xdc_runtime_ISystemSupport_ready( xdc_runtime_ISystemSupport_Module mod )
{
    return mod->ready();
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

/* abort_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_ISystemSupport_abort_FxnT)(xdc_CString str);
static inline xdc_runtime_ISystemSupport_abort_FxnT xdc_runtime_ISystemSupport_abort_fxnP(xdc_runtime_ISystemSupport_Module mod);
static inline xdc_runtime_ISystemSupport_abort_FxnT xdc_runtime_ISystemSupport_abort_fxnP(xdc_runtime_ISystemSupport_Module mod)
{
    return (xdc_runtime_ISystemSupport_abort_FxnT)mod->abort;
}

/* exit_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_ISystemSupport_exit_FxnT)(xdc_Int stat);
static inline xdc_runtime_ISystemSupport_exit_FxnT xdc_runtime_ISystemSupport_exit_fxnP(xdc_runtime_ISystemSupport_Module mod);
static inline xdc_runtime_ISystemSupport_exit_FxnT xdc_runtime_ISystemSupport_exit_fxnP(xdc_runtime_ISystemSupport_Module mod)
{
    return (xdc_runtime_ISystemSupport_exit_FxnT)mod->exit;
}

/* flush_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_ISystemSupport_flush_FxnT)(void);
static inline xdc_runtime_ISystemSupport_flush_FxnT xdc_runtime_ISystemSupport_flush_fxnP(xdc_runtime_ISystemSupport_Module mod);
static inline xdc_runtime_ISystemSupport_flush_FxnT xdc_runtime_ISystemSupport_flush_fxnP(xdc_runtime_ISystemSupport_Module mod)
{
    return (xdc_runtime_ISystemSupport_flush_FxnT)mod->flush;
}

/* putch_{FxnT,fxnP} */
typedef xdc_Void (*xdc_runtime_ISystemSupport_putch_FxnT)(xdc_Char ch);
static inline xdc_runtime_ISystemSupport_putch_FxnT xdc_runtime_ISystemSupport_putch_fxnP(xdc_runtime_ISystemSupport_Module mod);
static inline xdc_runtime_ISystemSupport_putch_FxnT xdc_runtime_ISystemSupport_putch_fxnP(xdc_runtime_ISystemSupport_Module mod)
{
    return (xdc_runtime_ISystemSupport_putch_FxnT)mod->putch;
}

/* ready_{FxnT,fxnP} */
typedef xdc_Bool (*xdc_runtime_ISystemSupport_ready_FxnT)(void);
static inline xdc_runtime_ISystemSupport_ready_FxnT xdc_runtime_ISystemSupport_ready_fxnP(xdc_runtime_ISystemSupport_Module mod);
static inline xdc_runtime_ISystemSupport_ready_FxnT xdc_runtime_ISystemSupport_ready_fxnP(xdc_runtime_ISystemSupport_Module mod)
{
    return (xdc_runtime_ISystemSupport_ready_FxnT)mod->ready;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef xdc_runtime_ISystemSupport__top__
#undef __nested__
#endif

#endif /* xdc_runtime_ISystemSupport__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_ISystemSupport__nolocalnames)

#ifndef xdc_runtime_ISystemSupport__localnames__done
#define xdc_runtime_ISystemSupport__localnames__done

/* module prefix */
#define ISystemSupport_Module xdc_runtime_ISystemSupport_Module
#define ISystemSupport_abort xdc_runtime_ISystemSupport_abort
#define ISystemSupport_abort_fxnP xdc_runtime_ISystemSupport_abort_fxnP
#define ISystemSupport_abort_FxnT xdc_runtime_ISystemSupport_abort_FxnT
#define ISystemSupport_exit xdc_runtime_ISystemSupport_exit
#define ISystemSupport_exit_fxnP xdc_runtime_ISystemSupport_exit_fxnP
#define ISystemSupport_exit_FxnT xdc_runtime_ISystemSupport_exit_FxnT
#define ISystemSupport_flush xdc_runtime_ISystemSupport_flush
#define ISystemSupport_flush_fxnP xdc_runtime_ISystemSupport_flush_fxnP
#define ISystemSupport_flush_FxnT xdc_runtime_ISystemSupport_flush_FxnT
#define ISystemSupport_putch xdc_runtime_ISystemSupport_putch
#define ISystemSupport_putch_fxnP xdc_runtime_ISystemSupport_putch_fxnP
#define ISystemSupport_putch_FxnT xdc_runtime_ISystemSupport_putch_FxnT
#define ISystemSupport_ready xdc_runtime_ISystemSupport_ready
#define ISystemSupport_ready_fxnP xdc_runtime_ISystemSupport_ready_fxnP
#define ISystemSupport_ready_FxnT xdc_runtime_ISystemSupport_ready_FxnT
#define ISystemSupport_Module_name xdc_runtime_ISystemSupport_Module_name

#endif /* xdc_runtime_ISystemSupport__localnames__done */
#endif
/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 7-31-2018 11:49:29; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


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
 *     CREATE ARGS
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
 *     CONVERTORS
 *     SYSTEM FUNCTIONS
 *
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef xdc_runtime_knl_SemThread__include
#define xdc_runtime_knl_SemThread__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_knl_SemThread__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_knl_SemThread___VERS 200


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <xdc/runtime/knl/package/package.defs.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/knl/ISemaphore.h>
#include <xdc/runtime/knl/ISemThreadSupport.h>
#include <xdc/runtime/knl/package/SemThread_Proxy.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* PendStatus */
typedef xdc_runtime_knl_ISemaphore_PendStatus xdc_runtime_knl_SemThread_PendStatus;

/* FOREVER */
#define xdc_runtime_knl_SemThread_FOREVER (~(0))

/* Mode */
typedef xdc_runtime_knl_ISemaphore_Mode xdc_runtime_knl_SemThread_Mode;

/* PendStatus_ERROR */
#define xdc_runtime_knl_SemThread_PendStatus_ERROR xdc_runtime_knl_ISemaphore_PendStatus_ERROR

/* PendStatus_TIMEOUT */
#define xdc_runtime_knl_SemThread_PendStatus_TIMEOUT xdc_runtime_knl_ISemaphore_PendStatus_TIMEOUT

/* PendStatus_SUCCESS */
#define xdc_runtime_knl_SemThread_PendStatus_SUCCESS xdc_runtime_knl_ISemaphore_PendStatus_SUCCESS

/* Mode_COUNTING */
#define xdc_runtime_knl_SemThread_Mode_COUNTING xdc_runtime_knl_ISemaphore_Mode_COUNTING

/* Mode_BINARY */
#define xdc_runtime_knl_SemThread_Mode_BINARY xdc_runtime_knl_ISemaphore_Mode_BINARY


/*
 * ======== CREATE ARGS ========
 */

/* Args__create */
typedef struct xdc_runtime_knl_SemThread_Args__create {
    xdc_Int count;
} xdc_runtime_knl_SemThread_Args__create;


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_knl_SemThread_Module__diagsEnabled;
__extern __FAR__ const CT__xdc_runtime_knl_SemThread_Module__diagsEnabled xdc_runtime_knl_SemThread_Module__diagsEnabled__C;
#ifdef xdc_runtime_knl_SemThread_Module__diagsEnabled__CR
#define xdc_runtime_knl_SemThread_Module__diagsEnabled__C (*((CT__xdc_runtime_knl_SemThread_Module__diagsEnabled*)(xdcRomConstPtr + xdc_runtime_knl_SemThread_Module__diagsEnabled__C_offset)))
#else
#define xdc_runtime_knl_SemThread_Module__diagsEnabled (xdc_runtime_knl_SemThread_Module__diagsEnabled__C)
#endif

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_knl_SemThread_Module__diagsIncluded;
__extern __FAR__ const CT__xdc_runtime_knl_SemThread_Module__diagsIncluded xdc_runtime_knl_SemThread_Module__diagsIncluded__C;
#ifdef xdc_runtime_knl_SemThread_Module__diagsIncluded__CR
#define xdc_runtime_knl_SemThread_Module__diagsIncluded__C (*((CT__xdc_runtime_knl_SemThread_Module__diagsIncluded*)(xdcRomConstPtr + xdc_runtime_knl_SemThread_Module__diagsIncluded__C_offset)))
#else
#define xdc_runtime_knl_SemThread_Module__diagsIncluded (xdc_runtime_knl_SemThread_Module__diagsIncluded__C)
#endif

/* Module__diagsMask */
typedef xdc_Bits16 *CT__xdc_runtime_knl_SemThread_Module__diagsMask;
__extern __FAR__ const CT__xdc_runtime_knl_SemThread_Module__diagsMask xdc_runtime_knl_SemThread_Module__diagsMask__C;
#ifdef xdc_runtime_knl_SemThread_Module__diagsMask__CR
#define xdc_runtime_knl_SemThread_Module__diagsMask__C (*((CT__xdc_runtime_knl_SemThread_Module__diagsMask*)(xdcRomConstPtr + xdc_runtime_knl_SemThread_Module__diagsMask__C_offset)))
#else
#define xdc_runtime_knl_SemThread_Module__diagsMask (xdc_runtime_knl_SemThread_Module__diagsMask__C)
#endif

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_knl_SemThread_Module__gateObj;
__extern __FAR__ const CT__xdc_runtime_knl_SemThread_Module__gateObj xdc_runtime_knl_SemThread_Module__gateObj__C;
#ifdef xdc_runtime_knl_SemThread_Module__gateObj__CR
#define xdc_runtime_knl_SemThread_Module__gateObj__C (*((CT__xdc_runtime_knl_SemThread_Module__gateObj*)(xdcRomConstPtr + xdc_runtime_knl_SemThread_Module__gateObj__C_offset)))
#else
#define xdc_runtime_knl_SemThread_Module__gateObj (xdc_runtime_knl_SemThread_Module__gateObj__C)
#endif

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_knl_SemThread_Module__gatePrms;
__extern __FAR__ const CT__xdc_runtime_knl_SemThread_Module__gatePrms xdc_runtime_knl_SemThread_Module__gatePrms__C;
#ifdef xdc_runtime_knl_SemThread_Module__gatePrms__CR
#define xdc_runtime_knl_SemThread_Module__gatePrms__C (*((CT__xdc_runtime_knl_SemThread_Module__gatePrms*)(xdcRomConstPtr + xdc_runtime_knl_SemThread_Module__gatePrms__C_offset)))
#else
#define xdc_runtime_knl_SemThread_Module__gatePrms (xdc_runtime_knl_SemThread_Module__gatePrms__C)
#endif

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_knl_SemThread_Module__id;
__extern __FAR__ const CT__xdc_runtime_knl_SemThread_Module__id xdc_runtime_knl_SemThread_Module__id__C;
#ifdef xdc_runtime_knl_SemThread_Module__id__CR
#define xdc_runtime_knl_SemThread_Module__id__C (*((CT__xdc_runtime_knl_SemThread_Module__id*)(xdcRomConstPtr + xdc_runtime_knl_SemThread_Module__id__C_offset)))
#else
#define xdc_runtime_knl_SemThread_Module__id (xdc_runtime_knl_SemThread_Module__id__C)
#endif

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_knl_SemThread_Module__loggerDefined;
__extern __FAR__ const CT__xdc_runtime_knl_SemThread_Module__loggerDefined xdc_runtime_knl_SemThread_Module__loggerDefined__C;
#ifdef xdc_runtime_knl_SemThread_Module__loggerDefined__CR
#define xdc_runtime_knl_SemThread_Module__loggerDefined__C (*((CT__xdc_runtime_knl_SemThread_Module__loggerDefined*)(xdcRomConstPtr + xdc_runtime_knl_SemThread_Module__loggerDefined__C_offset)))
#else
#define xdc_runtime_knl_SemThread_Module__loggerDefined (xdc_runtime_knl_SemThread_Module__loggerDefined__C)
#endif

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_knl_SemThread_Module__loggerObj;
__extern __FAR__ const CT__xdc_runtime_knl_SemThread_Module__loggerObj xdc_runtime_knl_SemThread_Module__loggerObj__C;
#ifdef xdc_runtime_knl_SemThread_Module__loggerObj__CR
#define xdc_runtime_knl_SemThread_Module__loggerObj__C (*((CT__xdc_runtime_knl_SemThread_Module__loggerObj*)(xdcRomConstPtr + xdc_runtime_knl_SemThread_Module__loggerObj__C_offset)))
#else
#define xdc_runtime_knl_SemThread_Module__loggerObj (xdc_runtime_knl_SemThread_Module__loggerObj__C)
#endif

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_knl_SemThread_Module__loggerFxn0;
__extern __FAR__ const CT__xdc_runtime_knl_SemThread_Module__loggerFxn0 xdc_runtime_knl_SemThread_Module__loggerFxn0__C;
#ifdef xdc_runtime_knl_SemThread_Module__loggerFxn0__CR
#define xdc_runtime_knl_SemThread_Module__loggerFxn0__C (*((CT__xdc_runtime_knl_SemThread_Module__loggerFxn0*)(xdcRomConstPtr + xdc_runtime_knl_SemThread_Module__loggerFxn0__C_offset)))
#else
#define xdc_runtime_knl_SemThread_Module__loggerFxn0 (xdc_runtime_knl_SemThread_Module__loggerFxn0__C)
#endif

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_knl_SemThread_Module__loggerFxn1;
__extern __FAR__ const CT__xdc_runtime_knl_SemThread_Module__loggerFxn1 xdc_runtime_knl_SemThread_Module__loggerFxn1__C;
#ifdef xdc_runtime_knl_SemThread_Module__loggerFxn1__CR
#define xdc_runtime_knl_SemThread_Module__loggerFxn1__C (*((CT__xdc_runtime_knl_SemThread_Module__loggerFxn1*)(xdcRomConstPtr + xdc_runtime_knl_SemThread_Module__loggerFxn1__C_offset)))
#else
#define xdc_runtime_knl_SemThread_Module__loggerFxn1 (xdc_runtime_knl_SemThread_Module__loggerFxn1__C)
#endif

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_knl_SemThread_Module__loggerFxn2;
__extern __FAR__ const CT__xdc_runtime_knl_SemThread_Module__loggerFxn2 xdc_runtime_knl_SemThread_Module__loggerFxn2__C;
#ifdef xdc_runtime_knl_SemThread_Module__loggerFxn2__CR
#define xdc_runtime_knl_SemThread_Module__loggerFxn2__C (*((CT__xdc_runtime_knl_SemThread_Module__loggerFxn2*)(xdcRomConstPtr + xdc_runtime_knl_SemThread_Module__loggerFxn2__C_offset)))
#else
#define xdc_runtime_knl_SemThread_Module__loggerFxn2 (xdc_runtime_knl_SemThread_Module__loggerFxn2__C)
#endif

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_knl_SemThread_Module__loggerFxn4;
__extern __FAR__ const CT__xdc_runtime_knl_SemThread_Module__loggerFxn4 xdc_runtime_knl_SemThread_Module__loggerFxn4__C;
#ifdef xdc_runtime_knl_SemThread_Module__loggerFxn4__CR
#define xdc_runtime_knl_SemThread_Module__loggerFxn4__C (*((CT__xdc_runtime_knl_SemThread_Module__loggerFxn4*)(xdcRomConstPtr + xdc_runtime_knl_SemThread_Module__loggerFxn4__C_offset)))
#else
#define xdc_runtime_knl_SemThread_Module__loggerFxn4 (xdc_runtime_knl_SemThread_Module__loggerFxn4__C)
#endif

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_knl_SemThread_Module__loggerFxn8;
__extern __FAR__ const CT__xdc_runtime_knl_SemThread_Module__loggerFxn8 xdc_runtime_knl_SemThread_Module__loggerFxn8__C;
#ifdef xdc_runtime_knl_SemThread_Module__loggerFxn8__CR
#define xdc_runtime_knl_SemThread_Module__loggerFxn8__C (*((CT__xdc_runtime_knl_SemThread_Module__loggerFxn8*)(xdcRomConstPtr + xdc_runtime_knl_SemThread_Module__loggerFxn8__C_offset)))
#else
#define xdc_runtime_knl_SemThread_Module__loggerFxn8 (xdc_runtime_knl_SemThread_Module__loggerFxn8__C)
#endif

/* Object__count */
typedef xdc_Int CT__xdc_runtime_knl_SemThread_Object__count;
__extern __FAR__ const CT__xdc_runtime_knl_SemThread_Object__count xdc_runtime_knl_SemThread_Object__count__C;
#ifdef xdc_runtime_knl_SemThread_Object__count__CR
#define xdc_runtime_knl_SemThread_Object__count__C (*((CT__xdc_runtime_knl_SemThread_Object__count*)(xdcRomConstPtr + xdc_runtime_knl_SemThread_Object__count__C_offset)))
#else
#define xdc_runtime_knl_SemThread_Object__count (xdc_runtime_knl_SemThread_Object__count__C)
#endif

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_knl_SemThread_Object__heap;
__extern __FAR__ const CT__xdc_runtime_knl_SemThread_Object__heap xdc_runtime_knl_SemThread_Object__heap__C;
#ifdef xdc_runtime_knl_SemThread_Object__heap__CR
#define xdc_runtime_knl_SemThread_Object__heap__C (*((CT__xdc_runtime_knl_SemThread_Object__heap*)(xdcRomConstPtr + xdc_runtime_knl_SemThread_Object__heap__C_offset)))
#else
#define xdc_runtime_knl_SemThread_Object__heap (xdc_runtime_knl_SemThread_Object__heap__C)
#endif

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_knl_SemThread_Object__sizeof;
__extern __FAR__ const CT__xdc_runtime_knl_SemThread_Object__sizeof xdc_runtime_knl_SemThread_Object__sizeof__C;
#ifdef xdc_runtime_knl_SemThread_Object__sizeof__CR
#define xdc_runtime_knl_SemThread_Object__sizeof__C (*((CT__xdc_runtime_knl_SemThread_Object__sizeof*)(xdcRomConstPtr + xdc_runtime_knl_SemThread_Object__sizeof__C_offset)))
#else
#define xdc_runtime_knl_SemThread_Object__sizeof (xdc_runtime_knl_SemThread_Object__sizeof__C)
#endif

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_knl_SemThread_Object__table;
__extern __FAR__ const CT__xdc_runtime_knl_SemThread_Object__table xdc_runtime_knl_SemThread_Object__table__C;
#ifdef xdc_runtime_knl_SemThread_Object__table__CR
#define xdc_runtime_knl_SemThread_Object__table__C (*((CT__xdc_runtime_knl_SemThread_Object__table*)(xdcRomConstPtr + xdc_runtime_knl_SemThread_Object__table__C_offset)))
#else
#define xdc_runtime_knl_SemThread_Object__table (xdc_runtime_knl_SemThread_Object__table__C)
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct xdc_runtime_knl_SemThread_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_runtime_knl_ISemaphore_Mode mode;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct xdc_runtime_knl_SemThread_Struct {
    const xdc_runtime_knl_SemThread_Fxns__ *__fxns;
    xdc_runtime_knl_SemThread_Proxy_Handle f0;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_knl_SemThread_Fxns__ {
    const xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Int (*pend)(xdc_runtime_knl_SemThread_Handle inst, xdc_UInt timeout, xdc_runtime_Error_Block* eb);
    xdc_Bool (*post)(xdc_runtime_knl_SemThread_Handle inst, xdc_runtime_Error_Block* eb);
    xdc_runtime_Types_SysFxns2 __sfxns;
};
#ifndef xdc_runtime_knl_SemThread_Module__FXNS__CR

/* Module__FXNS__C */
__extern const xdc_runtime_knl_SemThread_Fxns__ xdc_runtime_knl_SemThread_Module__FXNS__C;
#else
#define xdc_runtime_knl_SemThread_Module__FXNS__C (*(xdcRomConstPtr + xdc_runtime_knl_SemThread_Module__FXNS__C_offset))
#endif


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define xdc_runtime_knl_SemThread_Module_startup( state ) (-1)

/* Instance_init__E */
xdc__CODESECT(xdc_runtime_knl_SemThread_Instance_init__E, "xdc_runtime_knl_SemThread_Instance_init")
__extern xdc_Int xdc_runtime_knl_SemThread_Instance_init__E(xdc_runtime_knl_SemThread_Object *obj, xdc_Int count, const xdc_runtime_knl_SemThread_Params *prms, xdc_runtime_Error_Block *eb);

/* Instance_finalize__E */
xdc__CODESECT(xdc_runtime_knl_SemThread_Instance_finalize__E, "xdc_runtime_knl_SemThread_Instance_finalize")
__extern void xdc_runtime_knl_SemThread_Instance_finalize__E(xdc_runtime_knl_SemThread_Object *obj, int ec);

/* create */
xdc__CODESECT(xdc_runtime_knl_SemThread_create, "xdc_runtime_knl_SemThread_create")
__extern xdc_runtime_knl_SemThread_Handle xdc_runtime_knl_SemThread_create( xdc_Int count, const xdc_runtime_knl_SemThread_Params *prms, xdc_runtime_Error_Block *eb);

/* construct */
xdc__CODESECT(xdc_runtime_knl_SemThread_construct, "xdc_runtime_knl_SemThread_construct")
__extern void xdc_runtime_knl_SemThread_construct(xdc_runtime_knl_SemThread_Struct *obj, xdc_Int count, const xdc_runtime_knl_SemThread_Params *prms, xdc_runtime_Error_Block *eb);

/* delete */
xdc__CODESECT(xdc_runtime_knl_SemThread_delete, "xdc_runtime_knl_SemThread_delete")
__extern void xdc_runtime_knl_SemThread_delete(xdc_runtime_knl_SemThread_Handle *instp);

/* destruct */
xdc__CODESECT(xdc_runtime_knl_SemThread_destruct, "xdc_runtime_knl_SemThread_destruct")
__extern void xdc_runtime_knl_SemThread_destruct(xdc_runtime_knl_SemThread_Struct *obj);

/* Handle__label__S */
xdc__CODESECT(xdc_runtime_knl_SemThread_Handle__label__S, "xdc_runtime_knl_SemThread_Handle__label__S")
__extern xdc_runtime_Types_Label *xdc_runtime_knl_SemThread_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(xdc_runtime_knl_SemThread_Module__startupDone__S, "xdc_runtime_knl_SemThread_Module__startupDone__S")
__extern xdc_Bool xdc_runtime_knl_SemThread_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(xdc_runtime_knl_SemThread_Object__create__S, "xdc_runtime_knl_SemThread_Object__create__S")
__extern xdc_Ptr xdc_runtime_knl_SemThread_Object__create__S( xdc_CPtr aa, const xdc_UChar *pa, xdc_SizeT psz, xdc_runtime_Error_Block *eb );

/* Object__delete__S */
xdc__CODESECT(xdc_runtime_knl_SemThread_Object__delete__S, "xdc_runtime_knl_SemThread_Object__delete__S")
__extern xdc_Void xdc_runtime_knl_SemThread_Object__delete__S( xdc_Ptr instp );

/* Object__get__S */
xdc__CODESECT(xdc_runtime_knl_SemThread_Object__get__S, "xdc_runtime_knl_SemThread_Object__get__S")
__extern xdc_Ptr xdc_runtime_knl_SemThread_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(xdc_runtime_knl_SemThread_Object__first__S, "xdc_runtime_knl_SemThread_Object__first__S")
__extern xdc_Ptr xdc_runtime_knl_SemThread_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(xdc_runtime_knl_SemThread_Object__next__S, "xdc_runtime_knl_SemThread_Object__next__S")
__extern xdc_Ptr xdc_runtime_knl_SemThread_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(xdc_runtime_knl_SemThread_Params__init__S, "xdc_runtime_knl_SemThread_Params__init__S")
__extern xdc_Void xdc_runtime_knl_SemThread_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* pend__E */
#define xdc_runtime_knl_SemThread_pend xdc_runtime_knl_SemThread_pend__E
xdc__CODESECT(xdc_runtime_knl_SemThread_pend__E, "xdc_runtime_knl_SemThread_pend")
__extern xdc_Int xdc_runtime_knl_SemThread_pend__E( xdc_runtime_knl_SemThread_Handle __inst, xdc_UInt timeout, xdc_runtime_Error_Block *eb );

/* post__E */
#define xdc_runtime_knl_SemThread_post xdc_runtime_knl_SemThread_post__E
xdc__CODESECT(xdc_runtime_knl_SemThread_post__E, "xdc_runtime_knl_SemThread_post")
__extern xdc_Bool xdc_runtime_knl_SemThread_post__E( xdc_runtime_knl_SemThread_Handle __inst, xdc_runtime_Error_Block *eb );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_knl_ISemaphore_Module xdc_runtime_knl_SemThread_Module_upCast(void);
static inline xdc_runtime_knl_ISemaphore_Module xdc_runtime_knl_SemThread_Module_upCast(void)
{
    return (xdc_runtime_knl_ISemaphore_Module)&xdc_runtime_knl_SemThread_Module__FXNS__C;
}

/* Module_to_xdc_runtime_knl_ISemaphore */
#define xdc_runtime_knl_SemThread_Module_to_xdc_runtime_knl_ISemaphore xdc_runtime_knl_SemThread_Module_upCast

/* Handle_upCast */
static inline xdc_runtime_knl_ISemaphore_Handle xdc_runtime_knl_SemThread_Handle_upCast(xdc_runtime_knl_SemThread_Handle i);
static inline xdc_runtime_knl_ISemaphore_Handle xdc_runtime_knl_SemThread_Handle_upCast(xdc_runtime_knl_SemThread_Handle i)
{
    return (xdc_runtime_knl_ISemaphore_Handle)i;
}

/* Handle_to_xdc_runtime_knl_ISemaphore */
#define xdc_runtime_knl_SemThread_Handle_to_xdc_runtime_knl_ISemaphore xdc_runtime_knl_SemThread_Handle_upCast

/* Handle_downCast */
static inline xdc_runtime_knl_SemThread_Handle xdc_runtime_knl_SemThread_Handle_downCast(xdc_runtime_knl_ISemaphore_Handle i);
static inline xdc_runtime_knl_SemThread_Handle xdc_runtime_knl_SemThread_Handle_downCast(xdc_runtime_knl_ISemaphore_Handle i)
{
    xdc_runtime_knl_ISemaphore_Handle i2 = (xdc_runtime_knl_ISemaphore_Handle)i;
    return ((const void*)i2->__fxns == (const void*)&xdc_runtime_knl_SemThread_Module__FXNS__C) ? (xdc_runtime_knl_SemThread_Handle)i : (xdc_runtime_knl_SemThread_Handle)NULL;
}

/* Handle_from_xdc_runtime_knl_ISemaphore */
#define xdc_runtime_knl_SemThread_Handle_from_xdc_runtime_knl_ISemaphore xdc_runtime_knl_SemThread_Handle_downCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define xdc_runtime_knl_SemThread_Module_startupDone() xdc_runtime_knl_SemThread_Module__startupDone__S()

/* Object_heap */
#define xdc_runtime_knl_SemThread_Object_heap() xdc_runtime_knl_SemThread_Object__heap__C

/* Module_heap */
#define xdc_runtime_knl_SemThread_Module_heap() xdc_runtime_knl_SemThread_Object__heap__C

/* Module_id */
static inline CT__xdc_runtime_knl_SemThread_Module__id xdc_runtime_knl_SemThread_Module_id(void);
static inline CT__xdc_runtime_knl_SemThread_Module__id xdc_runtime_knl_SemThread_Module_id( void ) 
{
    return xdc_runtime_knl_SemThread_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_knl_SemThread_Module_hasMask(void);
static inline xdc_Bool xdc_runtime_knl_SemThread_Module_hasMask(void)
{
    return (xdc_Bool)(xdc_runtime_knl_SemThread_Module__diagsMask__C != (CT__xdc_runtime_knl_SemThread_Module__diagsMask)NULL);
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_knl_SemThread_Module_getMask(void);
static inline xdc_Bits16 xdc_runtime_knl_SemThread_Module_getMask(void)
{
    return (xdc_runtime_knl_SemThread_Module__diagsMask__C != (CT__xdc_runtime_knl_SemThread_Module__diagsMask)NULL) ? *xdc_runtime_knl_SemThread_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void xdc_runtime_knl_SemThread_Module_setMask(xdc_Bits16 mask);
static inline xdc_Void xdc_runtime_knl_SemThread_Module_setMask(xdc_Bits16 mask)
{
    if (xdc_runtime_knl_SemThread_Module__diagsMask__C != (CT__xdc_runtime_knl_SemThread_Module__diagsMask)NULL) {
        *xdc_runtime_knl_SemThread_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void xdc_runtime_knl_SemThread_Params_init(xdc_runtime_knl_SemThread_Params *prms);
static inline void xdc_runtime_knl_SemThread_Params_init( xdc_runtime_knl_SemThread_Params *prms ) 
{
    if (prms != NULL) {
        xdc_runtime_knl_SemThread_Params__init__S(prms, NULL, sizeof(xdc_runtime_knl_SemThread_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void xdc_runtime_knl_SemThread_Params_copy(xdc_runtime_knl_SemThread_Params *dst, const xdc_runtime_knl_SemThread_Params *src);
static inline void xdc_runtime_knl_SemThread_Params_copy(xdc_runtime_knl_SemThread_Params *dst, const xdc_runtime_knl_SemThread_Params *src) 
{
    if (dst != NULL) {
        xdc_runtime_knl_SemThread_Params__init__S(dst, (const void *)src, sizeof(xdc_runtime_knl_SemThread_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define xdc_runtime_knl_SemThread_Object_count() xdc_runtime_knl_SemThread_Object__count__C

/* Object_sizeof */
#define xdc_runtime_knl_SemThread_Object_sizeof() xdc_runtime_knl_SemThread_Object__sizeof__C

/* Object_get */
static inline xdc_runtime_knl_SemThread_Handle xdc_runtime_knl_SemThread_Object_get(xdc_runtime_knl_SemThread_Instance_State *oarr, int i);
static inline xdc_runtime_knl_SemThread_Handle xdc_runtime_knl_SemThread_Object_get(xdc_runtime_knl_SemThread_Instance_State *oarr, int i) 
{
    return (xdc_runtime_knl_SemThread_Handle)xdc_runtime_knl_SemThread_Object__get__S(oarr, i);
}

/* Object_first */
static inline xdc_runtime_knl_SemThread_Handle xdc_runtime_knl_SemThread_Object_first(void);
static inline xdc_runtime_knl_SemThread_Handle xdc_runtime_knl_SemThread_Object_first(void)
{
    return (xdc_runtime_knl_SemThread_Handle)xdc_runtime_knl_SemThread_Object__first__S();
}

/* Object_next */
static inline xdc_runtime_knl_SemThread_Handle xdc_runtime_knl_SemThread_Object_next(xdc_runtime_knl_SemThread_Object *obj);
static inline xdc_runtime_knl_SemThread_Handle xdc_runtime_knl_SemThread_Object_next(xdc_runtime_knl_SemThread_Object *obj)
{
    return (xdc_runtime_knl_SemThread_Handle)xdc_runtime_knl_SemThread_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *xdc_runtime_knl_SemThread_Handle_label(xdc_runtime_knl_SemThread_Handle inst, xdc_runtime_Types_Label *lab);
static inline xdc_runtime_Types_Label *xdc_runtime_knl_SemThread_Handle_label(xdc_runtime_knl_SemThread_Handle inst, xdc_runtime_Types_Label *lab)
{
    return xdc_runtime_knl_SemThread_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String xdc_runtime_knl_SemThread_Handle_name(xdc_runtime_knl_SemThread_Handle inst);
static inline xdc_String xdc_runtime_knl_SemThread_Handle_name(xdc_runtime_knl_SemThread_Handle inst)
{
    xdc_runtime_Types_Label lab;
    return xdc_runtime_knl_SemThread_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline xdc_runtime_knl_SemThread_Handle xdc_runtime_knl_SemThread_handle(xdc_runtime_knl_SemThread_Struct *str);
static inline xdc_runtime_knl_SemThread_Handle xdc_runtime_knl_SemThread_handle(xdc_runtime_knl_SemThread_Struct *str)
{
    return (xdc_runtime_knl_SemThread_Handle)str;
}

/* struct */
static inline xdc_runtime_knl_SemThread_Struct *xdc_runtime_knl_SemThread_struct(xdc_runtime_knl_SemThread_Handle inst);
static inline xdc_runtime_knl_SemThread_Struct *xdc_runtime_knl_SemThread_struct(xdc_runtime_knl_SemThread_Handle inst)
{
    return (xdc_runtime_knl_SemThread_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef xdc_runtime_knl_SemThread__top__
#undef __nested__
#endif

#endif /* xdc_runtime_knl_SemThread__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(xdc_runtime_knl_SemThread__internalaccess))

#ifndef xdc_runtime_knl_SemThread__include_state
#define xdc_runtime_knl_SemThread__include_state

/* Object */
struct xdc_runtime_knl_SemThread_Object {
    const xdc_runtime_knl_SemThread_Fxns__ *__fxns;
    xdc_runtime_knl_SemThread_Proxy_Handle proxyHandle;
};

#endif /* xdc_runtime_knl_SemThread__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_knl_SemThread__nolocalnames)

#ifndef xdc_runtime_knl_SemThread__localnames__done
#define xdc_runtime_knl_SemThread__localnames__done

/* module prefix */
#define SemThread_Instance xdc_runtime_knl_SemThread_Instance
#define SemThread_Handle xdc_runtime_knl_SemThread_Handle
#define SemThread_Module xdc_runtime_knl_SemThread_Module
#define SemThread_Object xdc_runtime_knl_SemThread_Object
#define SemThread_Struct xdc_runtime_knl_SemThread_Struct
#define SemThread_PendStatus xdc_runtime_knl_SemThread_PendStatus
#define SemThread_FOREVER xdc_runtime_knl_SemThread_FOREVER
#define SemThread_Mode xdc_runtime_knl_SemThread_Mode
#define SemThread_Instance_State xdc_runtime_knl_SemThread_Instance_State
#define SemThread_PendStatus_ERROR xdc_runtime_knl_SemThread_PendStatus_ERROR
#define SemThread_PendStatus_TIMEOUT xdc_runtime_knl_SemThread_PendStatus_TIMEOUT
#define SemThread_PendStatus_SUCCESS xdc_runtime_knl_SemThread_PendStatus_SUCCESS
#define SemThread_Mode_COUNTING xdc_runtime_knl_SemThread_Mode_COUNTING
#define SemThread_Mode_BINARY xdc_runtime_knl_SemThread_Mode_BINARY
#define SemThread_Params xdc_runtime_knl_SemThread_Params
#define SemThread_pend xdc_runtime_knl_SemThread_pend
#define SemThread_post xdc_runtime_knl_SemThread_post
#define SemThread_Module_name xdc_runtime_knl_SemThread_Module_name
#define SemThread_Module_id xdc_runtime_knl_SemThread_Module_id
#define SemThread_Module_startup xdc_runtime_knl_SemThread_Module_startup
#define SemThread_Module_startupDone xdc_runtime_knl_SemThread_Module_startupDone
#define SemThread_Module_hasMask xdc_runtime_knl_SemThread_Module_hasMask
#define SemThread_Module_getMask xdc_runtime_knl_SemThread_Module_getMask
#define SemThread_Module_setMask xdc_runtime_knl_SemThread_Module_setMask
#define SemThread_Object_heap xdc_runtime_knl_SemThread_Object_heap
#define SemThread_Module_heap xdc_runtime_knl_SemThread_Module_heap
#define SemThread_construct xdc_runtime_knl_SemThread_construct
#define SemThread_create xdc_runtime_knl_SemThread_create
#define SemThread_handle xdc_runtime_knl_SemThread_handle
#define SemThread_struct xdc_runtime_knl_SemThread_struct
#define SemThread_Handle_label xdc_runtime_knl_SemThread_Handle_label
#define SemThread_Handle_name xdc_runtime_knl_SemThread_Handle_name
#define SemThread_Instance_init xdc_runtime_knl_SemThread_Instance_init
#define SemThread_Object_count xdc_runtime_knl_SemThread_Object_count
#define SemThread_Object_get xdc_runtime_knl_SemThread_Object_get
#define SemThread_Object_first xdc_runtime_knl_SemThread_Object_first
#define SemThread_Object_next xdc_runtime_knl_SemThread_Object_next
#define SemThread_Object_sizeof xdc_runtime_knl_SemThread_Object_sizeof
#define SemThread_Params_copy xdc_runtime_knl_SemThread_Params_copy
#define SemThread_Params_init xdc_runtime_knl_SemThread_Params_init
#define SemThread_Instance_finalize xdc_runtime_knl_SemThread_Instance_finalize
#define SemThread_delete xdc_runtime_knl_SemThread_delete
#define SemThread_destruct xdc_runtime_knl_SemThread_destruct
#define SemThread_Module_upCast xdc_runtime_knl_SemThread_Module_upCast
#define SemThread_Module_to_xdc_runtime_knl_ISemaphore xdc_runtime_knl_SemThread_Module_to_xdc_runtime_knl_ISemaphore
#define SemThread_Handle_upCast xdc_runtime_knl_SemThread_Handle_upCast
#define SemThread_Handle_to_xdc_runtime_knl_ISemaphore xdc_runtime_knl_SemThread_Handle_to_xdc_runtime_knl_ISemaphore
#define SemThread_Handle_downCast xdc_runtime_knl_SemThread_Handle_downCast
#define SemThread_Handle_from_xdc_runtime_knl_ISemaphore xdc_runtime_knl_SemThread_Handle_from_xdc_runtime_knl_ISemaphore

/* proxies */
#include <xdc/runtime/knl/package/SemThread_Proxy.h>

#endif /* xdc_runtime_knl_SemThread__localnames__done */
#endif
/*
 *  @(#) xdc.runtime.knl; 1, 0, 0,0; 7-31-2018 11:49:36; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


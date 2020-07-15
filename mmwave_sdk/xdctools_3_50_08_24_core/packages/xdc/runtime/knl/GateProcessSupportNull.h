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

#ifndef xdc_runtime_knl_GateProcessSupportNull__include
#define xdc_runtime_knl_GateProcessSupportNull__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_knl_GateProcessSupportNull__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_knl_GateProcessSupportNull___VERS 200


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <xdc/runtime/knl/package/package.defs.h>

#include <xdc/runtime/knl/IGateProcessSupport.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Q_BLOCKING */
#define xdc_runtime_knl_GateProcessSupportNull_Q_BLOCKING (1)

/* Q_PREEMPTING */
#define xdc_runtime_knl_GateProcessSupportNull_Q_PREEMPTING (2)

/* GETREFCOUNT_FAILED */
#define xdc_runtime_knl_GateProcessSupportNull_GETREFCOUNT_FAILED (-1)


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_knl_GateProcessSupportNull_Module__diagsEnabled;
__extern __FAR__ const CT__xdc_runtime_knl_GateProcessSupportNull_Module__diagsEnabled xdc_runtime_knl_GateProcessSupportNull_Module__diagsEnabled__C;
#ifdef xdc_runtime_knl_GateProcessSupportNull_Module__diagsEnabled__CR
#define xdc_runtime_knl_GateProcessSupportNull_Module__diagsEnabled__C (*((CT__xdc_runtime_knl_GateProcessSupportNull_Module__diagsEnabled*)(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Module__diagsEnabled__C_offset)))
#else
#define xdc_runtime_knl_GateProcessSupportNull_Module__diagsEnabled (xdc_runtime_knl_GateProcessSupportNull_Module__diagsEnabled__C)
#endif

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_knl_GateProcessSupportNull_Module__diagsIncluded;
__extern __FAR__ const CT__xdc_runtime_knl_GateProcessSupportNull_Module__diagsIncluded xdc_runtime_knl_GateProcessSupportNull_Module__diagsIncluded__C;
#ifdef xdc_runtime_knl_GateProcessSupportNull_Module__diagsIncluded__CR
#define xdc_runtime_knl_GateProcessSupportNull_Module__diagsIncluded__C (*((CT__xdc_runtime_knl_GateProcessSupportNull_Module__diagsIncluded*)(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Module__diagsIncluded__C_offset)))
#else
#define xdc_runtime_knl_GateProcessSupportNull_Module__diagsIncluded (xdc_runtime_knl_GateProcessSupportNull_Module__diagsIncluded__C)
#endif

/* Module__diagsMask */
typedef xdc_Bits16 *CT__xdc_runtime_knl_GateProcessSupportNull_Module__diagsMask;
__extern __FAR__ const CT__xdc_runtime_knl_GateProcessSupportNull_Module__diagsMask xdc_runtime_knl_GateProcessSupportNull_Module__diagsMask__C;
#ifdef xdc_runtime_knl_GateProcessSupportNull_Module__diagsMask__CR
#define xdc_runtime_knl_GateProcessSupportNull_Module__diagsMask__C (*((CT__xdc_runtime_knl_GateProcessSupportNull_Module__diagsMask*)(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Module__diagsMask__C_offset)))
#else
#define xdc_runtime_knl_GateProcessSupportNull_Module__diagsMask (xdc_runtime_knl_GateProcessSupportNull_Module__diagsMask__C)
#endif

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_knl_GateProcessSupportNull_Module__gateObj;
__extern __FAR__ const CT__xdc_runtime_knl_GateProcessSupportNull_Module__gateObj xdc_runtime_knl_GateProcessSupportNull_Module__gateObj__C;
#ifdef xdc_runtime_knl_GateProcessSupportNull_Module__gateObj__CR
#define xdc_runtime_knl_GateProcessSupportNull_Module__gateObj__C (*((CT__xdc_runtime_knl_GateProcessSupportNull_Module__gateObj*)(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Module__gateObj__C_offset)))
#else
#define xdc_runtime_knl_GateProcessSupportNull_Module__gateObj (xdc_runtime_knl_GateProcessSupportNull_Module__gateObj__C)
#endif

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_knl_GateProcessSupportNull_Module__gatePrms;
__extern __FAR__ const CT__xdc_runtime_knl_GateProcessSupportNull_Module__gatePrms xdc_runtime_knl_GateProcessSupportNull_Module__gatePrms__C;
#ifdef xdc_runtime_knl_GateProcessSupportNull_Module__gatePrms__CR
#define xdc_runtime_knl_GateProcessSupportNull_Module__gatePrms__C (*((CT__xdc_runtime_knl_GateProcessSupportNull_Module__gatePrms*)(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Module__gatePrms__C_offset)))
#else
#define xdc_runtime_knl_GateProcessSupportNull_Module__gatePrms (xdc_runtime_knl_GateProcessSupportNull_Module__gatePrms__C)
#endif

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_knl_GateProcessSupportNull_Module__id;
__extern __FAR__ const CT__xdc_runtime_knl_GateProcessSupportNull_Module__id xdc_runtime_knl_GateProcessSupportNull_Module__id__C;
#ifdef xdc_runtime_knl_GateProcessSupportNull_Module__id__CR
#define xdc_runtime_knl_GateProcessSupportNull_Module__id__C (*((CT__xdc_runtime_knl_GateProcessSupportNull_Module__id*)(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Module__id__C_offset)))
#else
#define xdc_runtime_knl_GateProcessSupportNull_Module__id (xdc_runtime_knl_GateProcessSupportNull_Module__id__C)
#endif

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerDefined;
__extern __FAR__ const CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerDefined xdc_runtime_knl_GateProcessSupportNull_Module__loggerDefined__C;
#ifdef xdc_runtime_knl_GateProcessSupportNull_Module__loggerDefined__CR
#define xdc_runtime_knl_GateProcessSupportNull_Module__loggerDefined__C (*((CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerDefined*)(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Module__loggerDefined__C_offset)))
#else
#define xdc_runtime_knl_GateProcessSupportNull_Module__loggerDefined (xdc_runtime_knl_GateProcessSupportNull_Module__loggerDefined__C)
#endif

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerObj;
__extern __FAR__ const CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerObj xdc_runtime_knl_GateProcessSupportNull_Module__loggerObj__C;
#ifdef xdc_runtime_knl_GateProcessSupportNull_Module__loggerObj__CR
#define xdc_runtime_knl_GateProcessSupportNull_Module__loggerObj__C (*((CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerObj*)(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Module__loggerObj__C_offset)))
#else
#define xdc_runtime_knl_GateProcessSupportNull_Module__loggerObj (xdc_runtime_knl_GateProcessSupportNull_Module__loggerObj__C)
#endif

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn0;
__extern __FAR__ const CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn0 xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn0__C;
#ifdef xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn0__CR
#define xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn0__C (*((CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn0*)(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn0__C_offset)))
#else
#define xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn0 (xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn0__C)
#endif

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn1;
__extern __FAR__ const CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn1 xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn1__C;
#ifdef xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn1__CR
#define xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn1__C (*((CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn1*)(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn1__C_offset)))
#else
#define xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn1 (xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn1__C)
#endif

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn2;
__extern __FAR__ const CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn2 xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn2__C;
#ifdef xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn2__CR
#define xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn2__C (*((CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn2*)(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn2__C_offset)))
#else
#define xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn2 (xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn2__C)
#endif

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn4;
__extern __FAR__ const CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn4 xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn4__C;
#ifdef xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn4__CR
#define xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn4__C (*((CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn4*)(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn4__C_offset)))
#else
#define xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn4 (xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn4__C)
#endif

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn8;
__extern __FAR__ const CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn8 xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn8__C;
#ifdef xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn8__CR
#define xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn8__C (*((CT__xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn8*)(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn8__C_offset)))
#else
#define xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn8 (xdc_runtime_knl_GateProcessSupportNull_Module__loggerFxn8__C)
#endif

/* Object__count */
typedef xdc_Int CT__xdc_runtime_knl_GateProcessSupportNull_Object__count;
__extern __FAR__ const CT__xdc_runtime_knl_GateProcessSupportNull_Object__count xdc_runtime_knl_GateProcessSupportNull_Object__count__C;
#ifdef xdc_runtime_knl_GateProcessSupportNull_Object__count__CR
#define xdc_runtime_knl_GateProcessSupportNull_Object__count__C (*((CT__xdc_runtime_knl_GateProcessSupportNull_Object__count*)(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Object__count__C_offset)))
#else
#define xdc_runtime_knl_GateProcessSupportNull_Object__count (xdc_runtime_knl_GateProcessSupportNull_Object__count__C)
#endif

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_knl_GateProcessSupportNull_Object__heap;
__extern __FAR__ const CT__xdc_runtime_knl_GateProcessSupportNull_Object__heap xdc_runtime_knl_GateProcessSupportNull_Object__heap__C;
#ifdef xdc_runtime_knl_GateProcessSupportNull_Object__heap__CR
#define xdc_runtime_knl_GateProcessSupportNull_Object__heap__C (*((CT__xdc_runtime_knl_GateProcessSupportNull_Object__heap*)(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Object__heap__C_offset)))
#else
#define xdc_runtime_knl_GateProcessSupportNull_Object__heap (xdc_runtime_knl_GateProcessSupportNull_Object__heap__C)
#endif

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_knl_GateProcessSupportNull_Object__sizeof;
__extern __FAR__ const CT__xdc_runtime_knl_GateProcessSupportNull_Object__sizeof xdc_runtime_knl_GateProcessSupportNull_Object__sizeof__C;
#ifdef xdc_runtime_knl_GateProcessSupportNull_Object__sizeof__CR
#define xdc_runtime_knl_GateProcessSupportNull_Object__sizeof__C (*((CT__xdc_runtime_knl_GateProcessSupportNull_Object__sizeof*)(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Object__sizeof__C_offset)))
#else
#define xdc_runtime_knl_GateProcessSupportNull_Object__sizeof (xdc_runtime_knl_GateProcessSupportNull_Object__sizeof__C)
#endif

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_knl_GateProcessSupportNull_Object__table;
__extern __FAR__ const CT__xdc_runtime_knl_GateProcessSupportNull_Object__table xdc_runtime_knl_GateProcessSupportNull_Object__table__C;
#ifdef xdc_runtime_knl_GateProcessSupportNull_Object__table__CR
#define xdc_runtime_knl_GateProcessSupportNull_Object__table__C (*((CT__xdc_runtime_knl_GateProcessSupportNull_Object__table*)(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Object__table__C_offset)))
#else
#define xdc_runtime_knl_GateProcessSupportNull_Object__table (xdc_runtime_knl_GateProcessSupportNull_Object__table__C)
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct xdc_runtime_knl_GateProcessSupportNull_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_Int key;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct xdc_runtime_knl_GateProcessSupportNull_Struct {
    const xdc_runtime_knl_GateProcessSupportNull_Fxns__ *__fxns;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_knl_GateProcessSupportNull_Fxns__ {
    const xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*query)(xdc_Int qual);
    xdc_IArg (*enter)(xdc_runtime_knl_GateProcessSupportNull_Handle inst);
    xdc_Void (*leave)(xdc_runtime_knl_GateProcessSupportNull_Handle inst, xdc_IArg key);
    xdc_Int (*getReferenceCount)(xdc_runtime_knl_GateProcessSupportNull_Handle inst, xdc_runtime_Error_Block* err);
    xdc_runtime_Types_SysFxns2 __sfxns;
};
#ifndef xdc_runtime_knl_GateProcessSupportNull_Module__FXNS__CR

/* Module__FXNS__C */
__extern const xdc_runtime_knl_GateProcessSupportNull_Fxns__ xdc_runtime_knl_GateProcessSupportNull_Module__FXNS__C;
#else
#define xdc_runtime_knl_GateProcessSupportNull_Module__FXNS__C (*(xdcRomConstPtr + xdc_runtime_knl_GateProcessSupportNull_Module__FXNS__C_offset))
#endif


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define xdc_runtime_knl_GateProcessSupportNull_Module_startup( state ) (-1)

/* Instance_init__E */
xdc__CODESECT(xdc_runtime_knl_GateProcessSupportNull_Instance_init__E, "xdc_runtime_knl_GateProcessSupportNull_Instance_init")
__extern xdc_Void xdc_runtime_knl_GateProcessSupportNull_Instance_init__E(xdc_runtime_knl_GateProcessSupportNull_Object *obj, const xdc_runtime_knl_GateProcessSupportNull_Params *prms);

/* create */
xdc__CODESECT(xdc_runtime_knl_GateProcessSupportNull_create, "xdc_runtime_knl_GateProcessSupportNull_create")
__extern xdc_runtime_knl_GateProcessSupportNull_Handle xdc_runtime_knl_GateProcessSupportNull_create( const xdc_runtime_knl_GateProcessSupportNull_Params *prms, xdc_runtime_Error_Block *eb);

/* construct */
xdc__CODESECT(xdc_runtime_knl_GateProcessSupportNull_construct, "xdc_runtime_knl_GateProcessSupportNull_construct")
__extern void xdc_runtime_knl_GateProcessSupportNull_construct(xdc_runtime_knl_GateProcessSupportNull_Struct *obj, const xdc_runtime_knl_GateProcessSupportNull_Params *prms);

/* delete */
xdc__CODESECT(xdc_runtime_knl_GateProcessSupportNull_delete, "xdc_runtime_knl_GateProcessSupportNull_delete")
__extern void xdc_runtime_knl_GateProcessSupportNull_delete(xdc_runtime_knl_GateProcessSupportNull_Handle *instp);

/* destruct */
xdc__CODESECT(xdc_runtime_knl_GateProcessSupportNull_destruct, "xdc_runtime_knl_GateProcessSupportNull_destruct")
__extern void xdc_runtime_knl_GateProcessSupportNull_destruct(xdc_runtime_knl_GateProcessSupportNull_Struct *obj);

/* Handle__label__S */
xdc__CODESECT(xdc_runtime_knl_GateProcessSupportNull_Handle__label__S, "xdc_runtime_knl_GateProcessSupportNull_Handle__label__S")
__extern xdc_runtime_Types_Label *xdc_runtime_knl_GateProcessSupportNull_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(xdc_runtime_knl_GateProcessSupportNull_Module__startupDone__S, "xdc_runtime_knl_GateProcessSupportNull_Module__startupDone__S")
__extern xdc_Bool xdc_runtime_knl_GateProcessSupportNull_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(xdc_runtime_knl_GateProcessSupportNull_Object__create__S, "xdc_runtime_knl_GateProcessSupportNull_Object__create__S")
__extern xdc_Ptr xdc_runtime_knl_GateProcessSupportNull_Object__create__S( xdc_CPtr aa, const xdc_UChar *pa, xdc_SizeT psz, xdc_runtime_Error_Block *eb );

/* Object__delete__S */
xdc__CODESECT(xdc_runtime_knl_GateProcessSupportNull_Object__delete__S, "xdc_runtime_knl_GateProcessSupportNull_Object__delete__S")
__extern xdc_Void xdc_runtime_knl_GateProcessSupportNull_Object__delete__S( xdc_Ptr instp );

/* Object__get__S */
xdc__CODESECT(xdc_runtime_knl_GateProcessSupportNull_Object__get__S, "xdc_runtime_knl_GateProcessSupportNull_Object__get__S")
__extern xdc_Ptr xdc_runtime_knl_GateProcessSupportNull_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(xdc_runtime_knl_GateProcessSupportNull_Object__first__S, "xdc_runtime_knl_GateProcessSupportNull_Object__first__S")
__extern xdc_Ptr xdc_runtime_knl_GateProcessSupportNull_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(xdc_runtime_knl_GateProcessSupportNull_Object__next__S, "xdc_runtime_knl_GateProcessSupportNull_Object__next__S")
__extern xdc_Ptr xdc_runtime_knl_GateProcessSupportNull_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(xdc_runtime_knl_GateProcessSupportNull_Params__init__S, "xdc_runtime_knl_GateProcessSupportNull_Params__init__S")
__extern xdc_Void xdc_runtime_knl_GateProcessSupportNull_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* query__E */
#define xdc_runtime_knl_GateProcessSupportNull_query xdc_runtime_knl_GateProcessSupportNull_query__E
xdc__CODESECT(xdc_runtime_knl_GateProcessSupportNull_query__E, "xdc_runtime_knl_GateProcessSupportNull_query")
__extern xdc_Bool xdc_runtime_knl_GateProcessSupportNull_query__E( xdc_Int qual );

/* enter__E */
#define xdc_runtime_knl_GateProcessSupportNull_enter xdc_runtime_knl_GateProcessSupportNull_enter__E
xdc__CODESECT(xdc_runtime_knl_GateProcessSupportNull_enter__E, "xdc_runtime_knl_GateProcessSupportNull_enter")
__extern xdc_IArg xdc_runtime_knl_GateProcessSupportNull_enter__E( xdc_runtime_knl_GateProcessSupportNull_Handle __inst );

/* leave__E */
#define xdc_runtime_knl_GateProcessSupportNull_leave xdc_runtime_knl_GateProcessSupportNull_leave__E
xdc__CODESECT(xdc_runtime_knl_GateProcessSupportNull_leave__E, "xdc_runtime_knl_GateProcessSupportNull_leave")
__extern xdc_Void xdc_runtime_knl_GateProcessSupportNull_leave__E( xdc_runtime_knl_GateProcessSupportNull_Handle __inst, xdc_IArg key );

/* getReferenceCount__E */
#define xdc_runtime_knl_GateProcessSupportNull_getReferenceCount xdc_runtime_knl_GateProcessSupportNull_getReferenceCount__E
xdc__CODESECT(xdc_runtime_knl_GateProcessSupportNull_getReferenceCount__E, "xdc_runtime_knl_GateProcessSupportNull_getReferenceCount")
__extern xdc_Int xdc_runtime_knl_GateProcessSupportNull_getReferenceCount__E( xdc_runtime_knl_GateProcessSupportNull_Handle __inst, xdc_runtime_Error_Block *err );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_knl_IGateProcessSupport_Module xdc_runtime_knl_GateProcessSupportNull_Module_upCast(void);
static inline xdc_runtime_knl_IGateProcessSupport_Module xdc_runtime_knl_GateProcessSupportNull_Module_upCast(void)
{
    return (xdc_runtime_knl_IGateProcessSupport_Module)&xdc_runtime_knl_GateProcessSupportNull_Module__FXNS__C;
}

/* Module_to_xdc_runtime_knl_IGateProcessSupport */
#define xdc_runtime_knl_GateProcessSupportNull_Module_to_xdc_runtime_knl_IGateProcessSupport xdc_runtime_knl_GateProcessSupportNull_Module_upCast

/* Handle_upCast */
static inline xdc_runtime_knl_IGateProcessSupport_Handle xdc_runtime_knl_GateProcessSupportNull_Handle_upCast(xdc_runtime_knl_GateProcessSupportNull_Handle i);
static inline xdc_runtime_knl_IGateProcessSupport_Handle xdc_runtime_knl_GateProcessSupportNull_Handle_upCast(xdc_runtime_knl_GateProcessSupportNull_Handle i)
{
    return (xdc_runtime_knl_IGateProcessSupport_Handle)i;
}

/* Handle_to_xdc_runtime_knl_IGateProcessSupport */
#define xdc_runtime_knl_GateProcessSupportNull_Handle_to_xdc_runtime_knl_IGateProcessSupport xdc_runtime_knl_GateProcessSupportNull_Handle_upCast

/* Handle_downCast */
static inline xdc_runtime_knl_GateProcessSupportNull_Handle xdc_runtime_knl_GateProcessSupportNull_Handle_downCast(xdc_runtime_knl_IGateProcessSupport_Handle i);
static inline xdc_runtime_knl_GateProcessSupportNull_Handle xdc_runtime_knl_GateProcessSupportNull_Handle_downCast(xdc_runtime_knl_IGateProcessSupport_Handle i)
{
    xdc_runtime_knl_IGateProcessSupport_Handle i2 = (xdc_runtime_knl_IGateProcessSupport_Handle)i;
    return ((const void*)i2->__fxns == (const void*)&xdc_runtime_knl_GateProcessSupportNull_Module__FXNS__C) ? (xdc_runtime_knl_GateProcessSupportNull_Handle)i : (xdc_runtime_knl_GateProcessSupportNull_Handle)NULL;
}

/* Handle_from_xdc_runtime_knl_IGateProcessSupport */
#define xdc_runtime_knl_GateProcessSupportNull_Handle_from_xdc_runtime_knl_IGateProcessSupport xdc_runtime_knl_GateProcessSupportNull_Handle_downCast

/* Module_upCast2 */
static inline xdc_runtime_knl_IGateThreadSupport_Module xdc_runtime_knl_GateProcessSupportNull_Module_upCast2(void);
static inline xdc_runtime_knl_IGateThreadSupport_Module xdc_runtime_knl_GateProcessSupportNull_Module_upCast2(void)
{
    return (xdc_runtime_knl_IGateThreadSupport_Module)&xdc_runtime_knl_GateProcessSupportNull_Module__FXNS__C;
}

/* Module_to_xdc_runtime_knl_IGateThreadSupport */
#define xdc_runtime_knl_GateProcessSupportNull_Module_to_xdc_runtime_knl_IGateThreadSupport xdc_runtime_knl_GateProcessSupportNull_Module_upCast2

/* Handle_upCast2 */
static inline xdc_runtime_knl_IGateThreadSupport_Handle xdc_runtime_knl_GateProcessSupportNull_Handle_upCast2(xdc_runtime_knl_GateProcessSupportNull_Handle i);
static inline xdc_runtime_knl_IGateThreadSupport_Handle xdc_runtime_knl_GateProcessSupportNull_Handle_upCast2(xdc_runtime_knl_GateProcessSupportNull_Handle i)
{
    return (xdc_runtime_knl_IGateThreadSupport_Handle)i;
}

/* Handle_to_xdc_runtime_knl_IGateThreadSupport */
#define xdc_runtime_knl_GateProcessSupportNull_Handle_to_xdc_runtime_knl_IGateThreadSupport xdc_runtime_knl_GateProcessSupportNull_Handle_upCast2

/* Handle_downCast2 */
static inline xdc_runtime_knl_GateProcessSupportNull_Handle xdc_runtime_knl_GateProcessSupportNull_Handle_downCast2(xdc_runtime_knl_IGateThreadSupport_Handle i);
static inline xdc_runtime_knl_GateProcessSupportNull_Handle xdc_runtime_knl_GateProcessSupportNull_Handle_downCast2(xdc_runtime_knl_IGateThreadSupport_Handle i)
{
    xdc_runtime_knl_IGateThreadSupport_Handle i2 = (xdc_runtime_knl_IGateThreadSupport_Handle)i;
    return ((const void*)i2->__fxns == (const void*)&xdc_runtime_knl_GateProcessSupportNull_Module__FXNS__C) ? (xdc_runtime_knl_GateProcessSupportNull_Handle)i : (xdc_runtime_knl_GateProcessSupportNull_Handle)NULL;
}

/* Handle_from_xdc_runtime_knl_IGateThreadSupport */
#define xdc_runtime_knl_GateProcessSupportNull_Handle_from_xdc_runtime_knl_IGateThreadSupport xdc_runtime_knl_GateProcessSupportNull_Handle_downCast2

/* Module_upCast3 */
static inline xdc_runtime_IGateProvider_Module xdc_runtime_knl_GateProcessSupportNull_Module_upCast3(void);
static inline xdc_runtime_IGateProvider_Module xdc_runtime_knl_GateProcessSupportNull_Module_upCast3(void)
{
    return (xdc_runtime_IGateProvider_Module)&xdc_runtime_knl_GateProcessSupportNull_Module__FXNS__C;
}

/* Module_to_xdc_runtime_IGateProvider */
#define xdc_runtime_knl_GateProcessSupportNull_Module_to_xdc_runtime_IGateProvider xdc_runtime_knl_GateProcessSupportNull_Module_upCast3

/* Handle_upCast3 */
static inline xdc_runtime_IGateProvider_Handle xdc_runtime_knl_GateProcessSupportNull_Handle_upCast3(xdc_runtime_knl_GateProcessSupportNull_Handle i);
static inline xdc_runtime_IGateProvider_Handle xdc_runtime_knl_GateProcessSupportNull_Handle_upCast3(xdc_runtime_knl_GateProcessSupportNull_Handle i)
{
    return (xdc_runtime_IGateProvider_Handle)i;
}

/* Handle_to_xdc_runtime_IGateProvider */
#define xdc_runtime_knl_GateProcessSupportNull_Handle_to_xdc_runtime_IGateProvider xdc_runtime_knl_GateProcessSupportNull_Handle_upCast3

/* Handle_downCast3 */
static inline xdc_runtime_knl_GateProcessSupportNull_Handle xdc_runtime_knl_GateProcessSupportNull_Handle_downCast3(xdc_runtime_IGateProvider_Handle i);
static inline xdc_runtime_knl_GateProcessSupportNull_Handle xdc_runtime_knl_GateProcessSupportNull_Handle_downCast3(xdc_runtime_IGateProvider_Handle i)
{
    xdc_runtime_IGateProvider_Handle i2 = (xdc_runtime_IGateProvider_Handle)i;
    return ((const void*)i2->__fxns == (const void*)&xdc_runtime_knl_GateProcessSupportNull_Module__FXNS__C) ? (xdc_runtime_knl_GateProcessSupportNull_Handle)i : (xdc_runtime_knl_GateProcessSupportNull_Handle)NULL;
}

/* Handle_from_xdc_runtime_IGateProvider */
#define xdc_runtime_knl_GateProcessSupportNull_Handle_from_xdc_runtime_IGateProvider xdc_runtime_knl_GateProcessSupportNull_Handle_downCast3


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define xdc_runtime_knl_GateProcessSupportNull_Module_startupDone() xdc_runtime_knl_GateProcessSupportNull_Module__startupDone__S()

/* Object_heap */
#define xdc_runtime_knl_GateProcessSupportNull_Object_heap() xdc_runtime_knl_GateProcessSupportNull_Object__heap__C

/* Module_heap */
#define xdc_runtime_knl_GateProcessSupportNull_Module_heap() xdc_runtime_knl_GateProcessSupportNull_Object__heap__C

/* Module_id */
static inline CT__xdc_runtime_knl_GateProcessSupportNull_Module__id xdc_runtime_knl_GateProcessSupportNull_Module_id(void);
static inline CT__xdc_runtime_knl_GateProcessSupportNull_Module__id xdc_runtime_knl_GateProcessSupportNull_Module_id( void ) 
{
    return xdc_runtime_knl_GateProcessSupportNull_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_knl_GateProcessSupportNull_Module_hasMask(void);
static inline xdc_Bool xdc_runtime_knl_GateProcessSupportNull_Module_hasMask(void)
{
    return (xdc_Bool)(xdc_runtime_knl_GateProcessSupportNull_Module__diagsMask__C != (CT__xdc_runtime_knl_GateProcessSupportNull_Module__diagsMask)NULL);
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_knl_GateProcessSupportNull_Module_getMask(void);
static inline xdc_Bits16 xdc_runtime_knl_GateProcessSupportNull_Module_getMask(void)
{
    return (xdc_runtime_knl_GateProcessSupportNull_Module__diagsMask__C != (CT__xdc_runtime_knl_GateProcessSupportNull_Module__diagsMask)NULL) ? *xdc_runtime_knl_GateProcessSupportNull_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void xdc_runtime_knl_GateProcessSupportNull_Module_setMask(xdc_Bits16 mask);
static inline xdc_Void xdc_runtime_knl_GateProcessSupportNull_Module_setMask(xdc_Bits16 mask)
{
    if (xdc_runtime_knl_GateProcessSupportNull_Module__diagsMask__C != (CT__xdc_runtime_knl_GateProcessSupportNull_Module__diagsMask)NULL) {
        *xdc_runtime_knl_GateProcessSupportNull_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void xdc_runtime_knl_GateProcessSupportNull_Params_init(xdc_runtime_knl_GateProcessSupportNull_Params *prms);
static inline void xdc_runtime_knl_GateProcessSupportNull_Params_init( xdc_runtime_knl_GateProcessSupportNull_Params *prms ) 
{
    if (prms != NULL) {
        xdc_runtime_knl_GateProcessSupportNull_Params__init__S(prms, NULL, sizeof(xdc_runtime_knl_GateProcessSupportNull_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void xdc_runtime_knl_GateProcessSupportNull_Params_copy(xdc_runtime_knl_GateProcessSupportNull_Params *dst, const xdc_runtime_knl_GateProcessSupportNull_Params *src);
static inline void xdc_runtime_knl_GateProcessSupportNull_Params_copy(xdc_runtime_knl_GateProcessSupportNull_Params *dst, const xdc_runtime_knl_GateProcessSupportNull_Params *src) 
{
    if (dst != NULL) {
        xdc_runtime_knl_GateProcessSupportNull_Params__init__S(dst, (const void *)src, sizeof(xdc_runtime_knl_GateProcessSupportNull_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define xdc_runtime_knl_GateProcessSupportNull_Object_count() xdc_runtime_knl_GateProcessSupportNull_Object__count__C

/* Object_sizeof */
#define xdc_runtime_knl_GateProcessSupportNull_Object_sizeof() xdc_runtime_knl_GateProcessSupportNull_Object__sizeof__C

/* Object_get */
static inline xdc_runtime_knl_GateProcessSupportNull_Handle xdc_runtime_knl_GateProcessSupportNull_Object_get(xdc_runtime_knl_GateProcessSupportNull_Instance_State *oarr, int i);
static inline xdc_runtime_knl_GateProcessSupportNull_Handle xdc_runtime_knl_GateProcessSupportNull_Object_get(xdc_runtime_knl_GateProcessSupportNull_Instance_State *oarr, int i) 
{
    return (xdc_runtime_knl_GateProcessSupportNull_Handle)xdc_runtime_knl_GateProcessSupportNull_Object__get__S(oarr, i);
}

/* Object_first */
static inline xdc_runtime_knl_GateProcessSupportNull_Handle xdc_runtime_knl_GateProcessSupportNull_Object_first(void);
static inline xdc_runtime_knl_GateProcessSupportNull_Handle xdc_runtime_knl_GateProcessSupportNull_Object_first(void)
{
    return (xdc_runtime_knl_GateProcessSupportNull_Handle)xdc_runtime_knl_GateProcessSupportNull_Object__first__S();
}

/* Object_next */
static inline xdc_runtime_knl_GateProcessSupportNull_Handle xdc_runtime_knl_GateProcessSupportNull_Object_next(xdc_runtime_knl_GateProcessSupportNull_Object *obj);
static inline xdc_runtime_knl_GateProcessSupportNull_Handle xdc_runtime_knl_GateProcessSupportNull_Object_next(xdc_runtime_knl_GateProcessSupportNull_Object *obj)
{
    return (xdc_runtime_knl_GateProcessSupportNull_Handle)xdc_runtime_knl_GateProcessSupportNull_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *xdc_runtime_knl_GateProcessSupportNull_Handle_label(xdc_runtime_knl_GateProcessSupportNull_Handle inst, xdc_runtime_Types_Label *lab);
static inline xdc_runtime_Types_Label *xdc_runtime_knl_GateProcessSupportNull_Handle_label(xdc_runtime_knl_GateProcessSupportNull_Handle inst, xdc_runtime_Types_Label *lab)
{
    return xdc_runtime_knl_GateProcessSupportNull_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String xdc_runtime_knl_GateProcessSupportNull_Handle_name(xdc_runtime_knl_GateProcessSupportNull_Handle inst);
static inline xdc_String xdc_runtime_knl_GateProcessSupportNull_Handle_name(xdc_runtime_knl_GateProcessSupportNull_Handle inst)
{
    xdc_runtime_Types_Label lab;
    return xdc_runtime_knl_GateProcessSupportNull_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline xdc_runtime_knl_GateProcessSupportNull_Handle xdc_runtime_knl_GateProcessSupportNull_handle(xdc_runtime_knl_GateProcessSupportNull_Struct *str);
static inline xdc_runtime_knl_GateProcessSupportNull_Handle xdc_runtime_knl_GateProcessSupportNull_handle(xdc_runtime_knl_GateProcessSupportNull_Struct *str)
{
    return (xdc_runtime_knl_GateProcessSupportNull_Handle)str;
}

/* struct */
static inline xdc_runtime_knl_GateProcessSupportNull_Struct *xdc_runtime_knl_GateProcessSupportNull_struct(xdc_runtime_knl_GateProcessSupportNull_Handle inst);
static inline xdc_runtime_knl_GateProcessSupportNull_Struct *xdc_runtime_knl_GateProcessSupportNull_struct(xdc_runtime_knl_GateProcessSupportNull_Handle inst)
{
    return (xdc_runtime_knl_GateProcessSupportNull_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef xdc_runtime_knl_GateProcessSupportNull__top__
#undef __nested__
#endif

#endif /* xdc_runtime_knl_GateProcessSupportNull__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(xdc_runtime_knl_GateProcessSupportNull__internalaccess))

#ifndef xdc_runtime_knl_GateProcessSupportNull__include_state
#define xdc_runtime_knl_GateProcessSupportNull__include_state

/* Object */
struct xdc_runtime_knl_GateProcessSupportNull_Object {
    const xdc_runtime_knl_GateProcessSupportNull_Fxns__ *__fxns;
};

#endif /* xdc_runtime_knl_GateProcessSupportNull__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_knl_GateProcessSupportNull__nolocalnames)

#ifndef xdc_runtime_knl_GateProcessSupportNull__localnames__done
#define xdc_runtime_knl_GateProcessSupportNull__localnames__done

/* module prefix */
#define GateProcessSupportNull_Instance xdc_runtime_knl_GateProcessSupportNull_Instance
#define GateProcessSupportNull_Handle xdc_runtime_knl_GateProcessSupportNull_Handle
#define GateProcessSupportNull_Module xdc_runtime_knl_GateProcessSupportNull_Module
#define GateProcessSupportNull_Object xdc_runtime_knl_GateProcessSupportNull_Object
#define GateProcessSupportNull_Struct xdc_runtime_knl_GateProcessSupportNull_Struct
#define GateProcessSupportNull_Q_BLOCKING xdc_runtime_knl_GateProcessSupportNull_Q_BLOCKING
#define GateProcessSupportNull_Q_PREEMPTING xdc_runtime_knl_GateProcessSupportNull_Q_PREEMPTING
#define GateProcessSupportNull_GETREFCOUNT_FAILED xdc_runtime_knl_GateProcessSupportNull_GETREFCOUNT_FAILED
#define GateProcessSupportNull_Instance_State xdc_runtime_knl_GateProcessSupportNull_Instance_State
#define GateProcessSupportNull_Params xdc_runtime_knl_GateProcessSupportNull_Params
#define GateProcessSupportNull_query xdc_runtime_knl_GateProcessSupportNull_query
#define GateProcessSupportNull_enter xdc_runtime_knl_GateProcessSupportNull_enter
#define GateProcessSupportNull_leave xdc_runtime_knl_GateProcessSupportNull_leave
#define GateProcessSupportNull_getReferenceCount xdc_runtime_knl_GateProcessSupportNull_getReferenceCount
#define GateProcessSupportNull_Module_name xdc_runtime_knl_GateProcessSupportNull_Module_name
#define GateProcessSupportNull_Module_id xdc_runtime_knl_GateProcessSupportNull_Module_id
#define GateProcessSupportNull_Module_startup xdc_runtime_knl_GateProcessSupportNull_Module_startup
#define GateProcessSupportNull_Module_startupDone xdc_runtime_knl_GateProcessSupportNull_Module_startupDone
#define GateProcessSupportNull_Module_hasMask xdc_runtime_knl_GateProcessSupportNull_Module_hasMask
#define GateProcessSupportNull_Module_getMask xdc_runtime_knl_GateProcessSupportNull_Module_getMask
#define GateProcessSupportNull_Module_setMask xdc_runtime_knl_GateProcessSupportNull_Module_setMask
#define GateProcessSupportNull_Object_heap xdc_runtime_knl_GateProcessSupportNull_Object_heap
#define GateProcessSupportNull_Module_heap xdc_runtime_knl_GateProcessSupportNull_Module_heap
#define GateProcessSupportNull_construct xdc_runtime_knl_GateProcessSupportNull_construct
#define GateProcessSupportNull_create xdc_runtime_knl_GateProcessSupportNull_create
#define GateProcessSupportNull_handle xdc_runtime_knl_GateProcessSupportNull_handle
#define GateProcessSupportNull_struct xdc_runtime_knl_GateProcessSupportNull_struct
#define GateProcessSupportNull_Handle_label xdc_runtime_knl_GateProcessSupportNull_Handle_label
#define GateProcessSupportNull_Handle_name xdc_runtime_knl_GateProcessSupportNull_Handle_name
#define GateProcessSupportNull_Instance_init xdc_runtime_knl_GateProcessSupportNull_Instance_init
#define GateProcessSupportNull_Object_count xdc_runtime_knl_GateProcessSupportNull_Object_count
#define GateProcessSupportNull_Object_get xdc_runtime_knl_GateProcessSupportNull_Object_get
#define GateProcessSupportNull_Object_first xdc_runtime_knl_GateProcessSupportNull_Object_first
#define GateProcessSupportNull_Object_next xdc_runtime_knl_GateProcessSupportNull_Object_next
#define GateProcessSupportNull_Object_sizeof xdc_runtime_knl_GateProcessSupportNull_Object_sizeof
#define GateProcessSupportNull_Params_copy xdc_runtime_knl_GateProcessSupportNull_Params_copy
#define GateProcessSupportNull_Params_init xdc_runtime_knl_GateProcessSupportNull_Params_init
#define GateProcessSupportNull_Instance_State xdc_runtime_knl_GateProcessSupportNull_Instance_State
#define GateProcessSupportNull_delete xdc_runtime_knl_GateProcessSupportNull_delete
#define GateProcessSupportNull_destruct xdc_runtime_knl_GateProcessSupportNull_destruct
#define GateProcessSupportNull_Module_upCast xdc_runtime_knl_GateProcessSupportNull_Module_upCast
#define GateProcessSupportNull_Module_to_xdc_runtime_knl_IGateProcessSupport xdc_runtime_knl_GateProcessSupportNull_Module_to_xdc_runtime_knl_IGateProcessSupport
#define GateProcessSupportNull_Handle_upCast xdc_runtime_knl_GateProcessSupportNull_Handle_upCast
#define GateProcessSupportNull_Handle_to_xdc_runtime_knl_IGateProcessSupport xdc_runtime_knl_GateProcessSupportNull_Handle_to_xdc_runtime_knl_IGateProcessSupport
#define GateProcessSupportNull_Handle_downCast xdc_runtime_knl_GateProcessSupportNull_Handle_downCast
#define GateProcessSupportNull_Handle_from_xdc_runtime_knl_IGateProcessSupport xdc_runtime_knl_GateProcessSupportNull_Handle_from_xdc_runtime_knl_IGateProcessSupport
#define GateProcessSupportNull_Module_upCast2 xdc_runtime_knl_GateProcessSupportNull_Module_upCast2
#define GateProcessSupportNull_Module_to_xdc_runtime_knl_IGateThreadSupport xdc_runtime_knl_GateProcessSupportNull_Module_to_xdc_runtime_knl_IGateThreadSupport
#define GateProcessSupportNull_Handle_upCast2 xdc_runtime_knl_GateProcessSupportNull_Handle_upCast2
#define GateProcessSupportNull_Handle_to_xdc_runtime_knl_IGateThreadSupport xdc_runtime_knl_GateProcessSupportNull_Handle_to_xdc_runtime_knl_IGateThreadSupport
#define GateProcessSupportNull_Handle_downCast2 xdc_runtime_knl_GateProcessSupportNull_Handle_downCast2
#define GateProcessSupportNull_Handle_from_xdc_runtime_knl_IGateThreadSupport xdc_runtime_knl_GateProcessSupportNull_Handle_from_xdc_runtime_knl_IGateThreadSupport
#define GateProcessSupportNull_Module_upCast3 xdc_runtime_knl_GateProcessSupportNull_Module_upCast3
#define GateProcessSupportNull_Module_to_xdc_runtime_IGateProvider xdc_runtime_knl_GateProcessSupportNull_Module_to_xdc_runtime_IGateProvider
#define GateProcessSupportNull_Handle_upCast3 xdc_runtime_knl_GateProcessSupportNull_Handle_upCast3
#define GateProcessSupportNull_Handle_to_xdc_runtime_IGateProvider xdc_runtime_knl_GateProcessSupportNull_Handle_to_xdc_runtime_IGateProvider
#define GateProcessSupportNull_Handle_downCast3 xdc_runtime_knl_GateProcessSupportNull_Handle_downCast3
#define GateProcessSupportNull_Handle_from_xdc_runtime_IGateProvider xdc_runtime_knl_GateProcessSupportNull_Handle_from_xdc_runtime_IGateProvider

#endif /* xdc_runtime_knl_GateProcessSupportNull__localnames__done */
#endif
/*
 *  @(#) xdc.runtime.knl; 1, 0, 0,0; 7-31-2018 11:49:36; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


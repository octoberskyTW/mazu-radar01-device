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
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef xdc_runtime_Types__include
#define xdc_runtime_Types__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_Types__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_Types___VERS 200


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types__prologue.h>
#include <xdc/runtime/package/package.defs.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* ModuleId */
typedef xdc_Bits16 xdc_runtime_Types_ModuleId;

/* DiagsMask */
typedef xdc_Bits16 xdc_runtime_Types_DiagsMask;

/* Event */
typedef xdc_Bits32 xdc_runtime_Types_Event;

/* EventId */
typedef xdc_runtime_Types_Event xdc_runtime_Types_EventId;

/* CordAddr__ */
struct xdc_runtime_Types_CordAddr__;

/* CordAddr */
typedef xdc_runtime_Types_CordAddr__ *xdc_runtime_Types_CordAddr;

/* GateRef__ */
struct xdc_runtime_Types_GateRef__;

/* GateRef */
typedef xdc_runtime_Types_GateRef__ *xdc_runtime_Types_GateRef;

/* RopeId */
typedef xdc_Bits16 xdc_runtime_Types_RopeId;

/* CreatePolicy */
enum xdc_runtime_Types_CreatePolicy {
    xdc_runtime_Types_STATIC_POLICY,
    xdc_runtime_Types_CREATE_POLICY,
    xdc_runtime_Types_DELETE_POLICY
};
typedef enum xdc_runtime_Types_CreatePolicy xdc_runtime_Types_CreatePolicy;

/* OutputPolicy */
enum xdc_runtime_Types_OutputPolicy {
    xdc_runtime_Types_COMMON_FILE,
    xdc_runtime_Types_SEPARATE_FILE,
    xdc_runtime_Types_NO_FILE
};
typedef enum xdc_runtime_Types_OutputPolicy xdc_runtime_Types_OutputPolicy;

/* Label */
struct xdc_runtime_Types_Label {
    xdc_Ptr handle;
    xdc_runtime_Types_ModuleId modId;
    xdc_String iname;
    xdc_Bool named;
};

/* Site */
struct xdc_runtime_Types_Site {
    xdc_runtime_Types_ModuleId mod;
    xdc_CString file;
    xdc_Int line;
};

/* Timestamp64 */
struct xdc_runtime_Types_Timestamp64 {
    xdc_Bits32 hi;
    xdc_Bits32 lo;
};

/* FreqHz */
struct xdc_runtime_Types_FreqHz {
    xdc_Bits32 hi;
    xdc_Bits32 lo;
};

/* RegDesc */
struct xdc_runtime_Types_RegDesc {
    xdc_runtime_Types_RegDesc *next;
    xdc_CString modName;
    xdc_runtime_Types_ModuleId id;
    xdc_runtime_Types_DiagsMask mask;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* LogEvent */
typedef xdc_Bits32 xdc_runtime_Types_LogEvent;

/* LoggerFxn0 */
typedef xdc_Void (*xdc_runtime_Types_LoggerFxn0)(xdc_Ptr arg1, xdc_runtime_Types_LogEvent arg2, xdc_runtime_Types_ModuleId arg3);

/* LoggerFxn1 */
typedef xdc_Void (*xdc_runtime_Types_LoggerFxn1)(xdc_Ptr arg1, xdc_runtime_Types_LogEvent arg2, xdc_runtime_Types_ModuleId arg3, xdc_IArg arg4);

/* LoggerFxn2 */
typedef xdc_Void (*xdc_runtime_Types_LoggerFxn2)(xdc_Ptr arg1, xdc_runtime_Types_LogEvent arg2, xdc_runtime_Types_ModuleId arg3, xdc_IArg arg4, xdc_IArg arg5);

/* LoggerFxn4 */
typedef xdc_Void (*xdc_runtime_Types_LoggerFxn4)(xdc_Ptr arg1, xdc_runtime_Types_LogEvent arg2, xdc_runtime_Types_ModuleId arg3, xdc_IArg arg4, xdc_IArg arg5, xdc_IArg arg6, xdc_IArg arg7);

/* LoggerFxn8 */
typedef xdc_Void (*xdc_runtime_Types_LoggerFxn8)(xdc_Ptr arg1, xdc_runtime_Types_LogEvent arg2, xdc_runtime_Types_ModuleId arg3, xdc_IArg arg4, xdc_IArg arg5, xdc_IArg arg6, xdc_IArg arg7, xdc_IArg arg8, xdc_IArg arg9, xdc_IArg arg10, xdc_IArg arg11);

/* Vec */
struct xdc_runtime_Types_Vec {
    xdc_Int len;
    xdc_Ptr arr;
};

/* Link */
struct xdc_runtime_Types_Link {
    xdc_runtime_Types_Link *next;
    xdc_runtime_Types_Link *prev;
};

/* InstHdr */
struct xdc_runtime_Types_InstHdr {
    xdc_runtime_Types_Link link;
};

/* PrmsHdr */
struct xdc_runtime_Types_PrmsHdr {
    xdc_SizeT size;
    xdc_Ptr self;
    xdc_Ptr modFxns;
    xdc_Ptr instPrms;
};

/* Base */
struct xdc_runtime_Types_Base {
    const xdc_runtime_Types_Base *base;
};

/* SysFxns2 */
struct xdc_runtime_Types_SysFxns2 {
    xdc_Ptr (*__create)(xdc_CPtr arg1, const xdc_UChar* arg2, xdc_SizeT arg3, xdc_runtime_Error_Block* arg4);
    xdc_Void (*__delete)(xdc_Ptr arg1);
    xdc_runtime_Types_Label *(*__label)(xdc_Ptr arg1, xdc_runtime_Types_Label* arg2);
    xdc_runtime_Types_ModuleId __mid;
};


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_Types_Module__diagsEnabled;
__extern __FAR__ const CT__xdc_runtime_Types_Module__diagsEnabled xdc_runtime_Types_Module__diagsEnabled__C;
#ifdef xdc_runtime_Types_Module__diagsEnabled__CR
#define xdc_runtime_Types_Module__diagsEnabled__C (*((CT__xdc_runtime_Types_Module__diagsEnabled*)(xdcRomConstPtr + xdc_runtime_Types_Module__diagsEnabled__C_offset)))
#else
#define xdc_runtime_Types_Module__diagsEnabled (xdc_runtime_Types_Module__diagsEnabled__C)
#endif

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_Types_Module__diagsIncluded;
__extern __FAR__ const CT__xdc_runtime_Types_Module__diagsIncluded xdc_runtime_Types_Module__diagsIncluded__C;
#ifdef xdc_runtime_Types_Module__diagsIncluded__CR
#define xdc_runtime_Types_Module__diagsIncluded__C (*((CT__xdc_runtime_Types_Module__diagsIncluded*)(xdcRomConstPtr + xdc_runtime_Types_Module__diagsIncluded__C_offset)))
#else
#define xdc_runtime_Types_Module__diagsIncluded (xdc_runtime_Types_Module__diagsIncluded__C)
#endif

/* Module__diagsMask */
typedef xdc_Bits16 *CT__xdc_runtime_Types_Module__diagsMask;
__extern __FAR__ const CT__xdc_runtime_Types_Module__diagsMask xdc_runtime_Types_Module__diagsMask__C;
#ifdef xdc_runtime_Types_Module__diagsMask__CR
#define xdc_runtime_Types_Module__diagsMask__C (*((CT__xdc_runtime_Types_Module__diagsMask*)(xdcRomConstPtr + xdc_runtime_Types_Module__diagsMask__C_offset)))
#else
#define xdc_runtime_Types_Module__diagsMask (xdc_runtime_Types_Module__diagsMask__C)
#endif

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_Types_Module__gateObj;
__extern __FAR__ const CT__xdc_runtime_Types_Module__gateObj xdc_runtime_Types_Module__gateObj__C;
#ifdef xdc_runtime_Types_Module__gateObj__CR
#define xdc_runtime_Types_Module__gateObj__C (*((CT__xdc_runtime_Types_Module__gateObj*)(xdcRomConstPtr + xdc_runtime_Types_Module__gateObj__C_offset)))
#else
#define xdc_runtime_Types_Module__gateObj (xdc_runtime_Types_Module__gateObj__C)
#endif

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_Types_Module__gatePrms;
__extern __FAR__ const CT__xdc_runtime_Types_Module__gatePrms xdc_runtime_Types_Module__gatePrms__C;
#ifdef xdc_runtime_Types_Module__gatePrms__CR
#define xdc_runtime_Types_Module__gatePrms__C (*((CT__xdc_runtime_Types_Module__gatePrms*)(xdcRomConstPtr + xdc_runtime_Types_Module__gatePrms__C_offset)))
#else
#define xdc_runtime_Types_Module__gatePrms (xdc_runtime_Types_Module__gatePrms__C)
#endif

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_Types_Module__id;
__extern __FAR__ const CT__xdc_runtime_Types_Module__id xdc_runtime_Types_Module__id__C;
#ifdef xdc_runtime_Types_Module__id__CR
#define xdc_runtime_Types_Module__id__C (*((CT__xdc_runtime_Types_Module__id*)(xdcRomConstPtr + xdc_runtime_Types_Module__id__C_offset)))
#else
#define xdc_runtime_Types_Module__id (xdc_runtime_Types_Module__id__C)
#endif

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_Types_Module__loggerDefined;
__extern __FAR__ const CT__xdc_runtime_Types_Module__loggerDefined xdc_runtime_Types_Module__loggerDefined__C;
#ifdef xdc_runtime_Types_Module__loggerDefined__CR
#define xdc_runtime_Types_Module__loggerDefined__C (*((CT__xdc_runtime_Types_Module__loggerDefined*)(xdcRomConstPtr + xdc_runtime_Types_Module__loggerDefined__C_offset)))
#else
#define xdc_runtime_Types_Module__loggerDefined (xdc_runtime_Types_Module__loggerDefined__C)
#endif

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_Types_Module__loggerObj;
__extern __FAR__ const CT__xdc_runtime_Types_Module__loggerObj xdc_runtime_Types_Module__loggerObj__C;
#ifdef xdc_runtime_Types_Module__loggerObj__CR
#define xdc_runtime_Types_Module__loggerObj__C (*((CT__xdc_runtime_Types_Module__loggerObj*)(xdcRomConstPtr + xdc_runtime_Types_Module__loggerObj__C_offset)))
#else
#define xdc_runtime_Types_Module__loggerObj (xdc_runtime_Types_Module__loggerObj__C)
#endif

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_Types_Module__loggerFxn0;
__extern __FAR__ const CT__xdc_runtime_Types_Module__loggerFxn0 xdc_runtime_Types_Module__loggerFxn0__C;
#ifdef xdc_runtime_Types_Module__loggerFxn0__CR
#define xdc_runtime_Types_Module__loggerFxn0__C (*((CT__xdc_runtime_Types_Module__loggerFxn0*)(xdcRomConstPtr + xdc_runtime_Types_Module__loggerFxn0__C_offset)))
#else
#define xdc_runtime_Types_Module__loggerFxn0 (xdc_runtime_Types_Module__loggerFxn0__C)
#endif

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_Types_Module__loggerFxn1;
__extern __FAR__ const CT__xdc_runtime_Types_Module__loggerFxn1 xdc_runtime_Types_Module__loggerFxn1__C;
#ifdef xdc_runtime_Types_Module__loggerFxn1__CR
#define xdc_runtime_Types_Module__loggerFxn1__C (*((CT__xdc_runtime_Types_Module__loggerFxn1*)(xdcRomConstPtr + xdc_runtime_Types_Module__loggerFxn1__C_offset)))
#else
#define xdc_runtime_Types_Module__loggerFxn1 (xdc_runtime_Types_Module__loggerFxn1__C)
#endif

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_Types_Module__loggerFxn2;
__extern __FAR__ const CT__xdc_runtime_Types_Module__loggerFxn2 xdc_runtime_Types_Module__loggerFxn2__C;
#ifdef xdc_runtime_Types_Module__loggerFxn2__CR
#define xdc_runtime_Types_Module__loggerFxn2__C (*((CT__xdc_runtime_Types_Module__loggerFxn2*)(xdcRomConstPtr + xdc_runtime_Types_Module__loggerFxn2__C_offset)))
#else
#define xdc_runtime_Types_Module__loggerFxn2 (xdc_runtime_Types_Module__loggerFxn2__C)
#endif

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_Types_Module__loggerFxn4;
__extern __FAR__ const CT__xdc_runtime_Types_Module__loggerFxn4 xdc_runtime_Types_Module__loggerFxn4__C;
#ifdef xdc_runtime_Types_Module__loggerFxn4__CR
#define xdc_runtime_Types_Module__loggerFxn4__C (*((CT__xdc_runtime_Types_Module__loggerFxn4*)(xdcRomConstPtr + xdc_runtime_Types_Module__loggerFxn4__C_offset)))
#else
#define xdc_runtime_Types_Module__loggerFxn4 (xdc_runtime_Types_Module__loggerFxn4__C)
#endif

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_Types_Module__loggerFxn8;
__extern __FAR__ const CT__xdc_runtime_Types_Module__loggerFxn8 xdc_runtime_Types_Module__loggerFxn8__C;
#ifdef xdc_runtime_Types_Module__loggerFxn8__CR
#define xdc_runtime_Types_Module__loggerFxn8__C (*((CT__xdc_runtime_Types_Module__loggerFxn8*)(xdcRomConstPtr + xdc_runtime_Types_Module__loggerFxn8__C_offset)))
#else
#define xdc_runtime_Types_Module__loggerFxn8 (xdc_runtime_Types_Module__loggerFxn8__C)
#endif

/* Object__count */
typedef xdc_Int CT__xdc_runtime_Types_Object__count;
__extern __FAR__ const CT__xdc_runtime_Types_Object__count xdc_runtime_Types_Object__count__C;
#ifdef xdc_runtime_Types_Object__count__CR
#define xdc_runtime_Types_Object__count__C (*((CT__xdc_runtime_Types_Object__count*)(xdcRomConstPtr + xdc_runtime_Types_Object__count__C_offset)))
#else
#define xdc_runtime_Types_Object__count (xdc_runtime_Types_Object__count__C)
#endif

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_Types_Object__heap;
__extern __FAR__ const CT__xdc_runtime_Types_Object__heap xdc_runtime_Types_Object__heap__C;
#ifdef xdc_runtime_Types_Object__heap__CR
#define xdc_runtime_Types_Object__heap__C (*((CT__xdc_runtime_Types_Object__heap*)(xdcRomConstPtr + xdc_runtime_Types_Object__heap__C_offset)))
#else
#define xdc_runtime_Types_Object__heap (xdc_runtime_Types_Object__heap__C)
#endif

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_Types_Object__sizeof;
__extern __FAR__ const CT__xdc_runtime_Types_Object__sizeof xdc_runtime_Types_Object__sizeof__C;
#ifdef xdc_runtime_Types_Object__sizeof__CR
#define xdc_runtime_Types_Object__sizeof__C (*((CT__xdc_runtime_Types_Object__sizeof*)(xdcRomConstPtr + xdc_runtime_Types_Object__sizeof__C_offset)))
#else
#define xdc_runtime_Types_Object__sizeof (xdc_runtime_Types_Object__sizeof__C)
#endif

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_Types_Object__table;
__extern __FAR__ const CT__xdc_runtime_Types_Object__table xdc_runtime_Types_Object__table__C;
#ifdef xdc_runtime_Types_Object__table__CR
#define xdc_runtime_Types_Object__table__C (*((CT__xdc_runtime_Types_Object__table*)(xdcRomConstPtr + xdc_runtime_Types_Object__table__C_offset)))
#else
#define xdc_runtime_Types_Object__table (xdc_runtime_Types_Object__table__C)
#endif


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define xdc_runtime_Types_Module_startup( state ) (-1)

/* Module__startupDone__S */
xdc__CODESECT(xdc_runtime_Types_Module__startupDone__S, "xdc_runtime_Types_Module__startupDone__S")
__extern xdc_Bool xdc_runtime_Types_Module__startupDone__S( void );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define xdc_runtime_Types_Module_startupDone() xdc_runtime_Types_Module__startupDone__S()

/* Object_heap */
#define xdc_runtime_Types_Object_heap() xdc_runtime_Types_Object__heap__C

/* Module_heap */
#define xdc_runtime_Types_Module_heap() xdc_runtime_Types_Object__heap__C

/* Module_id */
static inline CT__xdc_runtime_Types_Module__id xdc_runtime_Types_Module_id(void);
static inline CT__xdc_runtime_Types_Module__id xdc_runtime_Types_Module_id( void ) 
{
    return xdc_runtime_Types_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_Types_Module_hasMask(void);
static inline xdc_Bool xdc_runtime_Types_Module_hasMask(void)
{
    return (xdc_Bool)(xdc_runtime_Types_Module__diagsMask__C != (CT__xdc_runtime_Types_Module__diagsMask)NULL);
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_Types_Module_getMask(void);
static inline xdc_Bits16 xdc_runtime_Types_Module_getMask(void)
{
    return (xdc_runtime_Types_Module__diagsMask__C != (CT__xdc_runtime_Types_Module__diagsMask)NULL) ? *xdc_runtime_Types_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void xdc_runtime_Types_Module_setMask(xdc_Bits16 mask);
static inline xdc_Void xdc_runtime_Types_Module_setMask(xdc_Bits16 mask)
{
    if (xdc_runtime_Types_Module__diagsMask__C != (CT__xdc_runtime_Types_Module__diagsMask)NULL) {
        *xdc_runtime_Types_Module__diagsMask__C = mask;
    }
}


/*
 * ======== EPILOGUE ========
 */

#include <xdc/runtime/Types__epilogue.h>

#ifdef xdc_runtime_Types__top__
#undef __nested__
#endif

#endif /* xdc_runtime_Types__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(xdc_runtime_Types__internalaccess))

#ifndef xdc_runtime_Types__include_state
#define xdc_runtime_Types__include_state


#endif /* xdc_runtime_Types__include_state */

#endif

/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_Types__nolocalnames)

#ifndef xdc_runtime_Types__localnames__done
#define xdc_runtime_Types__localnames__done

/* module prefix */
#define Types_ModuleId xdc_runtime_Types_ModuleId
#define Types_DiagsMask xdc_runtime_Types_DiagsMask
#define Types_Event xdc_runtime_Types_Event
#define Types_EventId xdc_runtime_Types_EventId
#define Types_CordAddr__ xdc_runtime_Types_CordAddr__
#define Types_CordAddr xdc_runtime_Types_CordAddr
#define Types_GateRef__ xdc_runtime_Types_GateRef__
#define Types_GateRef xdc_runtime_Types_GateRef
#define Types_RopeId xdc_runtime_Types_RopeId
#define Types_CreatePolicy xdc_runtime_Types_CreatePolicy
#define Types_OutputPolicy xdc_runtime_Types_OutputPolicy
#define Types_Label xdc_runtime_Types_Label
#define Types_Site xdc_runtime_Types_Site
#define Types_Timestamp64 xdc_runtime_Types_Timestamp64
#define Types_FreqHz xdc_runtime_Types_FreqHz
#define Types_RegDesc xdc_runtime_Types_RegDesc
#define Types_LogEvent xdc_runtime_Types_LogEvent
#define Types_LoggerFxn0 xdc_runtime_Types_LoggerFxn0
#define Types_LoggerFxn1 xdc_runtime_Types_LoggerFxn1
#define Types_LoggerFxn2 xdc_runtime_Types_LoggerFxn2
#define Types_LoggerFxn4 xdc_runtime_Types_LoggerFxn4
#define Types_LoggerFxn8 xdc_runtime_Types_LoggerFxn8
#define Types_Vec xdc_runtime_Types_Vec
#define Types_Link xdc_runtime_Types_Link
#define Types_InstHdr xdc_runtime_Types_InstHdr
#define Types_PrmsHdr xdc_runtime_Types_PrmsHdr
#define Types_Base xdc_runtime_Types_Base
#define Types_SysFxns2 xdc_runtime_Types_SysFxns2
#define Types_STATIC_POLICY xdc_runtime_Types_STATIC_POLICY
#define Types_CREATE_POLICY xdc_runtime_Types_CREATE_POLICY
#define Types_DELETE_POLICY xdc_runtime_Types_DELETE_POLICY
#define Types_COMMON_FILE xdc_runtime_Types_COMMON_FILE
#define Types_SEPARATE_FILE xdc_runtime_Types_SEPARATE_FILE
#define Types_NO_FILE xdc_runtime_Types_NO_FILE
#define Types_getEventId xdc_runtime_Types_getEventId
#define Types_getModuleId xdc_runtime_Types_getModuleId
#define Types_makeEvent xdc_runtime_Types_makeEvent
#define Types_Module_name xdc_runtime_Types_Module_name
#define Types_Module_id xdc_runtime_Types_Module_id
#define Types_Module_startup xdc_runtime_Types_Module_startup
#define Types_Module_startupDone xdc_runtime_Types_Module_startupDone
#define Types_Module_hasMask xdc_runtime_Types_Module_hasMask
#define Types_Module_getMask xdc_runtime_Types_Module_getMask
#define Types_Module_setMask xdc_runtime_Types_Module_setMask
#define Types_Object_heap xdc_runtime_Types_Object_heap
#define Types_Module_heap xdc_runtime_Types_Module_heap

#endif /* xdc_runtime_Types__localnames__done */
#endif
/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 7-31-2018 11:49:30; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


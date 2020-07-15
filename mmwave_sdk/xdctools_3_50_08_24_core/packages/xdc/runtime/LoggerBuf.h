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

#ifndef xdc_runtime_LoggerBuf__include
#define xdc_runtime_LoggerBuf__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_LoggerBuf__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_LoggerBuf___VERS 200


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <xdc/runtime/package/package.defs.h>

#include <xdc/runtime/IFilterLogger.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/ITimestampClient.h>
#include <xdc/runtime/ILogger.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/package/LoggerBuf_TimestampProxy.h>
#include <xdc/runtime/package/LoggerBuf_Module_GateProxy.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* BufType */
enum xdc_runtime_LoggerBuf_BufType {
    xdc_runtime_LoggerBuf_BufType_CIRCULAR,
    xdc_runtime_LoggerBuf_BufType_FIXED
};
typedef enum xdc_runtime_LoggerBuf_BufType xdc_runtime_LoggerBuf_BufType;


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* FULL */
#define xdc_runtime_LoggerBuf_FULL (-1)

/* WRAP */
#define xdc_runtime_LoggerBuf_WRAP (0)

/* NEXT */
#define xdc_runtime_LoggerBuf_NEXT (1)

/* Entry */
struct xdc_runtime_LoggerBuf_Entry {
    xdc_runtime_Types_Timestamp64 tstamp;
    xdc_Bits32 serial;
    xdc_runtime_Types_Event evt;
    xdc_IArg arg1;
    xdc_IArg arg2;
    xdc_IArg arg3;
    xdc_IArg arg4;
};

/* Instance_State */
typedef xdc_runtime_LoggerBuf_Entry __T1_xdc_runtime_LoggerBuf_Instance_State__entryArr;
typedef xdc_runtime_LoggerBuf_Entry *ARRAY1_xdc_runtime_LoggerBuf_Instance_State__entryArr;
typedef const xdc_runtime_LoggerBuf_Entry *CARRAY1_xdc_runtime_LoggerBuf_Instance_State__entryArr;
typedef ARRAY1_xdc_runtime_LoggerBuf_Instance_State__entryArr __TA_xdc_runtime_LoggerBuf_Instance_State__entryArr;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_LoggerBuf_Module__diagsEnabled;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__diagsEnabled xdc_runtime_LoggerBuf_Module__diagsEnabled__C;
#ifdef xdc_runtime_LoggerBuf_Module__diagsEnabled__CR
#define xdc_runtime_LoggerBuf_Module__diagsEnabled__C (*((CT__xdc_runtime_LoggerBuf_Module__diagsEnabled*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_Module__diagsEnabled__C_offset)))
#else
#define xdc_runtime_LoggerBuf_Module__diagsEnabled (xdc_runtime_LoggerBuf_Module__diagsEnabled__C)
#endif

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_LoggerBuf_Module__diagsIncluded;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__diagsIncluded xdc_runtime_LoggerBuf_Module__diagsIncluded__C;
#ifdef xdc_runtime_LoggerBuf_Module__diagsIncluded__CR
#define xdc_runtime_LoggerBuf_Module__diagsIncluded__C (*((CT__xdc_runtime_LoggerBuf_Module__diagsIncluded*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_Module__diagsIncluded__C_offset)))
#else
#define xdc_runtime_LoggerBuf_Module__diagsIncluded (xdc_runtime_LoggerBuf_Module__diagsIncluded__C)
#endif

/* Module__diagsMask */
typedef xdc_Bits16 *CT__xdc_runtime_LoggerBuf_Module__diagsMask;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__diagsMask xdc_runtime_LoggerBuf_Module__diagsMask__C;
#ifdef xdc_runtime_LoggerBuf_Module__diagsMask__CR
#define xdc_runtime_LoggerBuf_Module__diagsMask__C (*((CT__xdc_runtime_LoggerBuf_Module__diagsMask*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_Module__diagsMask__C_offset)))
#else
#define xdc_runtime_LoggerBuf_Module__diagsMask (xdc_runtime_LoggerBuf_Module__diagsMask__C)
#endif

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_LoggerBuf_Module__gateObj;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__gateObj xdc_runtime_LoggerBuf_Module__gateObj__C;
#ifdef xdc_runtime_LoggerBuf_Module__gateObj__CR
#define xdc_runtime_LoggerBuf_Module__gateObj__C (*((CT__xdc_runtime_LoggerBuf_Module__gateObj*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_Module__gateObj__C_offset)))
#else
#define xdc_runtime_LoggerBuf_Module__gateObj (xdc_runtime_LoggerBuf_Module__gateObj__C)
#endif

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_LoggerBuf_Module__gatePrms;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__gatePrms xdc_runtime_LoggerBuf_Module__gatePrms__C;
#ifdef xdc_runtime_LoggerBuf_Module__gatePrms__CR
#define xdc_runtime_LoggerBuf_Module__gatePrms__C (*((CT__xdc_runtime_LoggerBuf_Module__gatePrms*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_Module__gatePrms__C_offset)))
#else
#define xdc_runtime_LoggerBuf_Module__gatePrms (xdc_runtime_LoggerBuf_Module__gatePrms__C)
#endif

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_LoggerBuf_Module__id;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__id xdc_runtime_LoggerBuf_Module__id__C;
#ifdef xdc_runtime_LoggerBuf_Module__id__CR
#define xdc_runtime_LoggerBuf_Module__id__C (*((CT__xdc_runtime_LoggerBuf_Module__id*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_Module__id__C_offset)))
#else
#define xdc_runtime_LoggerBuf_Module__id (xdc_runtime_LoggerBuf_Module__id__C)
#endif

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_LoggerBuf_Module__loggerDefined;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__loggerDefined xdc_runtime_LoggerBuf_Module__loggerDefined__C;
#ifdef xdc_runtime_LoggerBuf_Module__loggerDefined__CR
#define xdc_runtime_LoggerBuf_Module__loggerDefined__C (*((CT__xdc_runtime_LoggerBuf_Module__loggerDefined*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_Module__loggerDefined__C_offset)))
#else
#define xdc_runtime_LoggerBuf_Module__loggerDefined (xdc_runtime_LoggerBuf_Module__loggerDefined__C)
#endif

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_LoggerBuf_Module__loggerObj;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__loggerObj xdc_runtime_LoggerBuf_Module__loggerObj__C;
#ifdef xdc_runtime_LoggerBuf_Module__loggerObj__CR
#define xdc_runtime_LoggerBuf_Module__loggerObj__C (*((CT__xdc_runtime_LoggerBuf_Module__loggerObj*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_Module__loggerObj__C_offset)))
#else
#define xdc_runtime_LoggerBuf_Module__loggerObj (xdc_runtime_LoggerBuf_Module__loggerObj__C)
#endif

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_LoggerBuf_Module__loggerFxn0;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__loggerFxn0 xdc_runtime_LoggerBuf_Module__loggerFxn0__C;
#ifdef xdc_runtime_LoggerBuf_Module__loggerFxn0__CR
#define xdc_runtime_LoggerBuf_Module__loggerFxn0__C (*((CT__xdc_runtime_LoggerBuf_Module__loggerFxn0*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_Module__loggerFxn0__C_offset)))
#else
#define xdc_runtime_LoggerBuf_Module__loggerFxn0 (xdc_runtime_LoggerBuf_Module__loggerFxn0__C)
#endif

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_LoggerBuf_Module__loggerFxn1;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__loggerFxn1 xdc_runtime_LoggerBuf_Module__loggerFxn1__C;
#ifdef xdc_runtime_LoggerBuf_Module__loggerFxn1__CR
#define xdc_runtime_LoggerBuf_Module__loggerFxn1__C (*((CT__xdc_runtime_LoggerBuf_Module__loggerFxn1*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_Module__loggerFxn1__C_offset)))
#else
#define xdc_runtime_LoggerBuf_Module__loggerFxn1 (xdc_runtime_LoggerBuf_Module__loggerFxn1__C)
#endif

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_LoggerBuf_Module__loggerFxn2;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__loggerFxn2 xdc_runtime_LoggerBuf_Module__loggerFxn2__C;
#ifdef xdc_runtime_LoggerBuf_Module__loggerFxn2__CR
#define xdc_runtime_LoggerBuf_Module__loggerFxn2__C (*((CT__xdc_runtime_LoggerBuf_Module__loggerFxn2*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_Module__loggerFxn2__C_offset)))
#else
#define xdc_runtime_LoggerBuf_Module__loggerFxn2 (xdc_runtime_LoggerBuf_Module__loggerFxn2__C)
#endif

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__xdc_runtime_LoggerBuf_Module__loggerFxn4;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__loggerFxn4 xdc_runtime_LoggerBuf_Module__loggerFxn4__C;
#ifdef xdc_runtime_LoggerBuf_Module__loggerFxn4__CR
#define xdc_runtime_LoggerBuf_Module__loggerFxn4__C (*((CT__xdc_runtime_LoggerBuf_Module__loggerFxn4*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_Module__loggerFxn4__C_offset)))
#else
#define xdc_runtime_LoggerBuf_Module__loggerFxn4 (xdc_runtime_LoggerBuf_Module__loggerFxn4__C)
#endif

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__xdc_runtime_LoggerBuf_Module__loggerFxn8;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Module__loggerFxn8 xdc_runtime_LoggerBuf_Module__loggerFxn8__C;
#ifdef xdc_runtime_LoggerBuf_Module__loggerFxn8__CR
#define xdc_runtime_LoggerBuf_Module__loggerFxn8__C (*((CT__xdc_runtime_LoggerBuf_Module__loggerFxn8*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_Module__loggerFxn8__C_offset)))
#else
#define xdc_runtime_LoggerBuf_Module__loggerFxn8 (xdc_runtime_LoggerBuf_Module__loggerFxn8__C)
#endif

/* Object__count */
typedef xdc_Int CT__xdc_runtime_LoggerBuf_Object__count;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Object__count xdc_runtime_LoggerBuf_Object__count__C;
#ifdef xdc_runtime_LoggerBuf_Object__count__CR
#define xdc_runtime_LoggerBuf_Object__count__C (*((CT__xdc_runtime_LoggerBuf_Object__count*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_Object__count__C_offset)))
#else
#define xdc_runtime_LoggerBuf_Object__count (xdc_runtime_LoggerBuf_Object__count__C)
#endif

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__xdc_runtime_LoggerBuf_Object__heap;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Object__heap xdc_runtime_LoggerBuf_Object__heap__C;
#ifdef xdc_runtime_LoggerBuf_Object__heap__CR
#define xdc_runtime_LoggerBuf_Object__heap__C (*((CT__xdc_runtime_LoggerBuf_Object__heap*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_Object__heap__C_offset)))
#else
#define xdc_runtime_LoggerBuf_Object__heap (xdc_runtime_LoggerBuf_Object__heap__C)
#endif

/* Object__sizeof */
typedef xdc_SizeT CT__xdc_runtime_LoggerBuf_Object__sizeof;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Object__sizeof xdc_runtime_LoggerBuf_Object__sizeof__C;
#ifdef xdc_runtime_LoggerBuf_Object__sizeof__CR
#define xdc_runtime_LoggerBuf_Object__sizeof__C (*((CT__xdc_runtime_LoggerBuf_Object__sizeof*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_Object__sizeof__C_offset)))
#else
#define xdc_runtime_LoggerBuf_Object__sizeof (xdc_runtime_LoggerBuf_Object__sizeof__C)
#endif

/* Object__table */
typedef xdc_Ptr CT__xdc_runtime_LoggerBuf_Object__table;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_Object__table xdc_runtime_LoggerBuf_Object__table__C;
#ifdef xdc_runtime_LoggerBuf_Object__table__CR
#define xdc_runtime_LoggerBuf_Object__table__C (*((CT__xdc_runtime_LoggerBuf_Object__table*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_Object__table__C_offset)))
#else
#define xdc_runtime_LoggerBuf_Object__table (xdc_runtime_LoggerBuf_Object__table__C)
#endif

/* filterByLevel */
typedef xdc_Bool CT__xdc_runtime_LoggerBuf_filterByLevel;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_filterByLevel xdc_runtime_LoggerBuf_filterByLevel__C;
#ifdef xdc_runtime_LoggerBuf_filterByLevel__CR
#define xdc_runtime_LoggerBuf_filterByLevel (*((CT__xdc_runtime_LoggerBuf_filterByLevel*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_filterByLevel__C_offset)))
#else
#ifdef xdc_runtime_LoggerBuf_filterByLevel__D
#define xdc_runtime_LoggerBuf_filterByLevel (xdc_runtime_LoggerBuf_filterByLevel__D)
#else
#define xdc_runtime_LoggerBuf_filterByLevel (xdc_runtime_LoggerBuf_filterByLevel__C)
#endif
#endif

/* E_badLevel */
typedef xdc_runtime_Error_Id CT__xdc_runtime_LoggerBuf_E_badLevel;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_E_badLevel xdc_runtime_LoggerBuf_E_badLevel__C;
#ifdef xdc_runtime_LoggerBuf_E_badLevel__CR
#define xdc_runtime_LoggerBuf_E_badLevel (*((CT__xdc_runtime_LoggerBuf_E_badLevel*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_E_badLevel__C_offset)))
#else
#define xdc_runtime_LoggerBuf_E_badLevel (xdc_runtime_LoggerBuf_E_badLevel__C)
#endif

/* enableFlush */
typedef xdc_Bool CT__xdc_runtime_LoggerBuf_enableFlush;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_enableFlush xdc_runtime_LoggerBuf_enableFlush__C;
#ifdef xdc_runtime_LoggerBuf_enableFlush__CR
#define xdc_runtime_LoggerBuf_enableFlush (*((CT__xdc_runtime_LoggerBuf_enableFlush*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_enableFlush__C_offset)))
#else
#ifdef xdc_runtime_LoggerBuf_enableFlush__D
#define xdc_runtime_LoggerBuf_enableFlush (xdc_runtime_LoggerBuf_enableFlush__D)
#else
#define xdc_runtime_LoggerBuf_enableFlush (xdc_runtime_LoggerBuf_enableFlush__C)
#endif
#endif

/* statusLogger */
typedef xdc_runtime_ILogger_Handle CT__xdc_runtime_LoggerBuf_statusLogger;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_statusLogger xdc_runtime_LoggerBuf_statusLogger__C;
#ifdef xdc_runtime_LoggerBuf_statusLogger__CR
#define xdc_runtime_LoggerBuf_statusLogger (*((CT__xdc_runtime_LoggerBuf_statusLogger*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_statusLogger__C_offset)))
#else
#define xdc_runtime_LoggerBuf_statusLogger (xdc_runtime_LoggerBuf_statusLogger__C)
#endif

/* level1Mask */
typedef xdc_runtime_Diags_Mask CT__xdc_runtime_LoggerBuf_level1Mask;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_level1Mask xdc_runtime_LoggerBuf_level1Mask__C;
#ifdef xdc_runtime_LoggerBuf_level1Mask__CR
#define xdc_runtime_LoggerBuf_level1Mask (*((CT__xdc_runtime_LoggerBuf_level1Mask*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_level1Mask__C_offset)))
#else
#ifdef xdc_runtime_LoggerBuf_level1Mask__D
#define xdc_runtime_LoggerBuf_level1Mask (xdc_runtime_LoggerBuf_level1Mask__D)
#else
#define xdc_runtime_LoggerBuf_level1Mask (xdc_runtime_LoggerBuf_level1Mask__C)
#endif
#endif

/* level2Mask */
typedef xdc_runtime_Diags_Mask CT__xdc_runtime_LoggerBuf_level2Mask;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_level2Mask xdc_runtime_LoggerBuf_level2Mask__C;
#ifdef xdc_runtime_LoggerBuf_level2Mask__CR
#define xdc_runtime_LoggerBuf_level2Mask (*((CT__xdc_runtime_LoggerBuf_level2Mask*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_level2Mask__C_offset)))
#else
#ifdef xdc_runtime_LoggerBuf_level2Mask__D
#define xdc_runtime_LoggerBuf_level2Mask (xdc_runtime_LoggerBuf_level2Mask__D)
#else
#define xdc_runtime_LoggerBuf_level2Mask (xdc_runtime_LoggerBuf_level2Mask__C)
#endif
#endif

/* level3Mask */
typedef xdc_runtime_Diags_Mask CT__xdc_runtime_LoggerBuf_level3Mask;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_level3Mask xdc_runtime_LoggerBuf_level3Mask__C;
#ifdef xdc_runtime_LoggerBuf_level3Mask__CR
#define xdc_runtime_LoggerBuf_level3Mask (*((CT__xdc_runtime_LoggerBuf_level3Mask*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_level3Mask__C_offset)))
#else
#ifdef xdc_runtime_LoggerBuf_level3Mask__D
#define xdc_runtime_LoggerBuf_level3Mask (xdc_runtime_LoggerBuf_level3Mask__D)
#else
#define xdc_runtime_LoggerBuf_level3Mask (xdc_runtime_LoggerBuf_level3Mask__C)
#endif
#endif

/* level4Mask */
typedef xdc_runtime_Diags_Mask CT__xdc_runtime_LoggerBuf_level4Mask;
__extern __FAR__ const CT__xdc_runtime_LoggerBuf_level4Mask xdc_runtime_LoggerBuf_level4Mask__C;
#ifdef xdc_runtime_LoggerBuf_level4Mask__CR
#define xdc_runtime_LoggerBuf_level4Mask (*((CT__xdc_runtime_LoggerBuf_level4Mask*)(xdcRomConstPtr + xdc_runtime_LoggerBuf_level4Mask__C_offset)))
#else
#ifdef xdc_runtime_LoggerBuf_level4Mask__D
#define xdc_runtime_LoggerBuf_level4Mask (xdc_runtime_LoggerBuf_level4Mask__D)
#else
#define xdc_runtime_LoggerBuf_level4Mask (xdc_runtime_LoggerBuf_level4Mask__C)
#endif
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct xdc_runtime_LoggerBuf_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_UInt numEntries;
    xdc_runtime_LoggerBuf_BufType bufType;
    xdc_Bool exitFlush;
    xdc_runtime_IHeap_Handle bufHeap;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct xdc_runtime_LoggerBuf_Struct {
    const xdc_runtime_LoggerBuf_Fxns__ *__fxns;
    xdc_runtime_IHeap_Handle f0;
    __TA_xdc_runtime_LoggerBuf_Instance_State__entryArr f1;
    xdc_runtime_LoggerBuf_Entry *f2;
    xdc_runtime_LoggerBuf_Entry *f3;
    xdc_runtime_LoggerBuf_Entry *f4;
    xdc_Bits32 f5;
    xdc_UInt16 f6;
    xdc_Int8 f7;
    xdc_Bool f8;
    xdc_Bool f9;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct xdc_runtime_LoggerBuf_Fxns__ {
    const xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*enable)(xdc_runtime_LoggerBuf_Handle inst);
    xdc_Bool (*disable)(xdc_runtime_LoggerBuf_Handle inst);
    xdc_Void (*write0)(xdc_runtime_LoggerBuf_Handle inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid);
    xdc_Void (*write1)(xdc_runtime_LoggerBuf_Handle inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1);
    xdc_Void (*write2)(xdc_runtime_LoggerBuf_Handle inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2);
    xdc_Void (*write4)(xdc_runtime_LoggerBuf_Handle inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4);
    xdc_Void (*write8)(xdc_runtime_LoggerBuf_Handle inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4, xdc_IArg a5, xdc_IArg a6, xdc_IArg a7, xdc_IArg a8);
    xdc_Void (*setFilterLevel)(xdc_runtime_LoggerBuf_Handle inst, xdc_runtime_Diags_Mask mask, xdc_runtime_Diags_EventLevel filterLevel);
    xdc_runtime_Diags_Mask (*getFilterLevel)(xdc_runtime_LoggerBuf_Handle inst, xdc_runtime_Diags_EventLevel level);
    xdc_runtime_Types_SysFxns2 __sfxns;
};
#ifndef xdc_runtime_LoggerBuf_Module__FXNS__CR

/* Module__FXNS__C */
__extern const xdc_runtime_LoggerBuf_Fxns__ xdc_runtime_LoggerBuf_Module__FXNS__C;
#else
#define xdc_runtime_LoggerBuf_Module__FXNS__C (*(xdcRomConstPtr + xdc_runtime_LoggerBuf_Module__FXNS__C_offset))
#endif


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define xdc_runtime_LoggerBuf_Module_startup xdc_runtime_LoggerBuf_Module_startup__E
xdc__CODESECT(xdc_runtime_LoggerBuf_Module_startup__E, "xdc_runtime_LoggerBuf_Module_startup")
__extern xdc_Int xdc_runtime_LoggerBuf_Module_startup__E( xdc_Int state );
xdc__CODESECT(xdc_runtime_LoggerBuf_Module_startup__F, "xdc_runtime_LoggerBuf_Module_startup")
__extern xdc_Int xdc_runtime_LoggerBuf_Module_startup__F( xdc_Int state );

/* Instance_init__E */
xdc__CODESECT(xdc_runtime_LoggerBuf_Instance_init__E, "xdc_runtime_LoggerBuf_Instance_init")
__extern xdc_Int xdc_runtime_LoggerBuf_Instance_init__E(xdc_runtime_LoggerBuf_Object *obj, const xdc_runtime_LoggerBuf_Params *prms, xdc_runtime_Error_Block *eb);

/* Instance_finalize__E */
xdc__CODESECT(xdc_runtime_LoggerBuf_Instance_finalize__E, "xdc_runtime_LoggerBuf_Instance_finalize")
__extern void xdc_runtime_LoggerBuf_Instance_finalize__E(xdc_runtime_LoggerBuf_Object *obj, int ec);

/* create */
xdc__CODESECT(xdc_runtime_LoggerBuf_create, "xdc_runtime_LoggerBuf_create")
__extern xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_create( const xdc_runtime_LoggerBuf_Params *prms, xdc_runtime_Error_Block *eb);

/* construct */
xdc__CODESECT(xdc_runtime_LoggerBuf_construct, "xdc_runtime_LoggerBuf_construct")
__extern void xdc_runtime_LoggerBuf_construct(xdc_runtime_LoggerBuf_Struct *obj, const xdc_runtime_LoggerBuf_Params *prms, xdc_runtime_Error_Block *eb);

/* delete */
xdc__CODESECT(xdc_runtime_LoggerBuf_delete, "xdc_runtime_LoggerBuf_delete")
__extern void xdc_runtime_LoggerBuf_delete(xdc_runtime_LoggerBuf_Handle *instp);

/* destruct */
xdc__CODESECT(xdc_runtime_LoggerBuf_destruct, "xdc_runtime_LoggerBuf_destruct")
__extern void xdc_runtime_LoggerBuf_destruct(xdc_runtime_LoggerBuf_Struct *obj);

/* Handle__label__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Handle__label__S, "xdc_runtime_LoggerBuf_Handle__label__S")
__extern xdc_runtime_Types_Label *xdc_runtime_LoggerBuf_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Module__startupDone__S, "xdc_runtime_LoggerBuf_Module__startupDone__S")
__extern xdc_Bool xdc_runtime_LoggerBuf_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Object__create__S, "xdc_runtime_LoggerBuf_Object__create__S")
__extern xdc_Ptr xdc_runtime_LoggerBuf_Object__create__S( xdc_CPtr aa, const xdc_UChar *pa, xdc_SizeT psz, xdc_runtime_Error_Block *eb );

/* Object__delete__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Object__delete__S, "xdc_runtime_LoggerBuf_Object__delete__S")
__extern xdc_Void xdc_runtime_LoggerBuf_Object__delete__S( xdc_Ptr instp );

/* Object__get__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Object__get__S, "xdc_runtime_LoggerBuf_Object__get__S")
__extern xdc_Ptr xdc_runtime_LoggerBuf_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Object__first__S, "xdc_runtime_LoggerBuf_Object__first__S")
__extern xdc_Ptr xdc_runtime_LoggerBuf_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Object__next__S, "xdc_runtime_LoggerBuf_Object__next__S")
__extern xdc_Ptr xdc_runtime_LoggerBuf_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(xdc_runtime_LoggerBuf_Params__init__S, "xdc_runtime_LoggerBuf_Params__init__S")
__extern xdc_Void xdc_runtime_LoggerBuf_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* enable__E */
#define xdc_runtime_LoggerBuf_enable xdc_runtime_LoggerBuf_enable__E
xdc__CODESECT(xdc_runtime_LoggerBuf_enable__E, "xdc_runtime_LoggerBuf_enable")
__extern xdc_Bool xdc_runtime_LoggerBuf_enable__E( xdc_runtime_LoggerBuf_Handle __inst );

/* disable__E */
#define xdc_runtime_LoggerBuf_disable xdc_runtime_LoggerBuf_disable__E
xdc__CODESECT(xdc_runtime_LoggerBuf_disable__E, "xdc_runtime_LoggerBuf_disable")
__extern xdc_Bool xdc_runtime_LoggerBuf_disable__E( xdc_runtime_LoggerBuf_Handle __inst );

/* write0__E */
#define xdc_runtime_LoggerBuf_write0 xdc_runtime_LoggerBuf_write0__E
xdc__CODESECT(xdc_runtime_LoggerBuf_write0__E, "xdc_runtime_LoggerBuf_write0")
__extern xdc_Void xdc_runtime_LoggerBuf_write0__E( xdc_runtime_LoggerBuf_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid );

/* write1__E */
#define xdc_runtime_LoggerBuf_write1 xdc_runtime_LoggerBuf_write1__E
xdc__CODESECT(xdc_runtime_LoggerBuf_write1__E, "xdc_runtime_LoggerBuf_write1")
__extern xdc_Void xdc_runtime_LoggerBuf_write1__E( xdc_runtime_LoggerBuf_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1 );

/* write2__E */
#define xdc_runtime_LoggerBuf_write2 xdc_runtime_LoggerBuf_write2__E
xdc__CODESECT(xdc_runtime_LoggerBuf_write2__E, "xdc_runtime_LoggerBuf_write2")
__extern xdc_Void xdc_runtime_LoggerBuf_write2__E( xdc_runtime_LoggerBuf_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2 );

/* write4__E */
#define xdc_runtime_LoggerBuf_write4 xdc_runtime_LoggerBuf_write4__E
xdc__CODESECT(xdc_runtime_LoggerBuf_write4__E, "xdc_runtime_LoggerBuf_write4")
__extern xdc_Void xdc_runtime_LoggerBuf_write4__E( xdc_runtime_LoggerBuf_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4 );

/* write8__E */
#define xdc_runtime_LoggerBuf_write8 xdc_runtime_LoggerBuf_write8__E
xdc__CODESECT(xdc_runtime_LoggerBuf_write8__E, "xdc_runtime_LoggerBuf_write8")
__extern xdc_Void xdc_runtime_LoggerBuf_write8__E( xdc_runtime_LoggerBuf_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4, xdc_IArg a5, xdc_IArg a6, xdc_IArg a7, xdc_IArg a8 );

/* setFilterLevel__E */
#define xdc_runtime_LoggerBuf_setFilterLevel xdc_runtime_LoggerBuf_setFilterLevel__E
xdc__CODESECT(xdc_runtime_LoggerBuf_setFilterLevel__E, "xdc_runtime_LoggerBuf_setFilterLevel")
__extern xdc_Void xdc_runtime_LoggerBuf_setFilterLevel__E( xdc_runtime_LoggerBuf_Handle __inst, xdc_runtime_Diags_Mask mask, xdc_runtime_Diags_EventLevel filterLevel );

/* getFilterLevel__E */
#define xdc_runtime_LoggerBuf_getFilterLevel xdc_runtime_LoggerBuf_getFilterLevel__E
xdc__CODESECT(xdc_runtime_LoggerBuf_getFilterLevel__E, "xdc_runtime_LoggerBuf_getFilterLevel")
__extern xdc_runtime_Diags_Mask xdc_runtime_LoggerBuf_getFilterLevel__E( xdc_runtime_LoggerBuf_Handle __inst, xdc_runtime_Diags_EventLevel level );

/* flushAll__E */
#define xdc_runtime_LoggerBuf_flushAll xdc_runtime_LoggerBuf_flushAll__E
xdc__CODESECT(xdc_runtime_LoggerBuf_flushAll__E, "xdc_runtime_LoggerBuf_flushAll")
__extern xdc_Void xdc_runtime_LoggerBuf_flushAll__E( void );

/* flushAllInternal__E */
#define xdc_runtime_LoggerBuf_flushAllInternal xdc_runtime_LoggerBuf_flushAllInternal__E
xdc__CODESECT(xdc_runtime_LoggerBuf_flushAllInternal__E, "xdc_runtime_LoggerBuf_flushAllInternal")
__extern xdc_Void xdc_runtime_LoggerBuf_flushAllInternal__E( xdc_Int stat );

/* reset__E */
#define xdc_runtime_LoggerBuf_reset xdc_runtime_LoggerBuf_reset__E
xdc__CODESECT(xdc_runtime_LoggerBuf_reset__E, "xdc_runtime_LoggerBuf_reset")
__extern xdc_Void xdc_runtime_LoggerBuf_reset__E( xdc_runtime_LoggerBuf_Handle __inst );

/* flush__E */
#define xdc_runtime_LoggerBuf_flush xdc_runtime_LoggerBuf_flush__E
xdc__CODESECT(xdc_runtime_LoggerBuf_flush__E, "xdc_runtime_LoggerBuf_flush")
__extern xdc_Void xdc_runtime_LoggerBuf_flush__E( xdc_runtime_LoggerBuf_Handle __inst );

/* getNextEntry__E */
#define xdc_runtime_LoggerBuf_getNextEntry xdc_runtime_LoggerBuf_getNextEntry__E
xdc__CODESECT(xdc_runtime_LoggerBuf_getNextEntry__E, "xdc_runtime_LoggerBuf_getNextEntry")
__extern xdc_Int xdc_runtime_LoggerBuf_getNextEntry__E( xdc_runtime_LoggerBuf_Handle __inst, xdc_runtime_Log_EventRec *evtRec );

/* filterOutEvent__I */
#define xdc_runtime_LoggerBuf_filterOutEvent xdc_runtime_LoggerBuf_filterOutEvent__I
xdc__CODESECT(xdc_runtime_LoggerBuf_filterOutEvent__I, "xdc_runtime_LoggerBuf_filterOutEvent")
__extern xdc_Bool xdc_runtime_LoggerBuf_filterOutEvent__I( xdc_runtime_Diags_Mask mask );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_IFilterLogger_Module xdc_runtime_LoggerBuf_Module_upCast(void);
static inline xdc_runtime_IFilterLogger_Module xdc_runtime_LoggerBuf_Module_upCast(void)
{
    return (xdc_runtime_IFilterLogger_Module)&xdc_runtime_LoggerBuf_Module__FXNS__C;
}

/* Module_to_xdc_runtime_IFilterLogger */
#define xdc_runtime_LoggerBuf_Module_to_xdc_runtime_IFilterLogger xdc_runtime_LoggerBuf_Module_upCast

/* Handle_upCast */
static inline xdc_runtime_IFilterLogger_Handle xdc_runtime_LoggerBuf_Handle_upCast(xdc_runtime_LoggerBuf_Handle i);
static inline xdc_runtime_IFilterLogger_Handle xdc_runtime_LoggerBuf_Handle_upCast(xdc_runtime_LoggerBuf_Handle i)
{
    return (xdc_runtime_IFilterLogger_Handle)i;
}

/* Handle_to_xdc_runtime_IFilterLogger */
#define xdc_runtime_LoggerBuf_Handle_to_xdc_runtime_IFilterLogger xdc_runtime_LoggerBuf_Handle_upCast

/* Handle_downCast */
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_Handle_downCast(xdc_runtime_IFilterLogger_Handle i);
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_Handle_downCast(xdc_runtime_IFilterLogger_Handle i)
{
    xdc_runtime_IFilterLogger_Handle i2 = (xdc_runtime_IFilterLogger_Handle)i;
    return ((const void*)i2->__fxns == (const void*)&xdc_runtime_LoggerBuf_Module__FXNS__C) ? (xdc_runtime_LoggerBuf_Handle)i : (xdc_runtime_LoggerBuf_Handle)NULL;
}

/* Handle_from_xdc_runtime_IFilterLogger */
#define xdc_runtime_LoggerBuf_Handle_from_xdc_runtime_IFilterLogger xdc_runtime_LoggerBuf_Handle_downCast

/* Module_upCast2 */
static inline xdc_runtime_ILogger_Module xdc_runtime_LoggerBuf_Module_upCast2(void);
static inline xdc_runtime_ILogger_Module xdc_runtime_LoggerBuf_Module_upCast2(void)
{
    return (xdc_runtime_ILogger_Module)&xdc_runtime_LoggerBuf_Module__FXNS__C;
}

/* Module_to_xdc_runtime_ILogger */
#define xdc_runtime_LoggerBuf_Module_to_xdc_runtime_ILogger xdc_runtime_LoggerBuf_Module_upCast2

/* Handle_upCast2 */
static inline xdc_runtime_ILogger_Handle xdc_runtime_LoggerBuf_Handle_upCast2(xdc_runtime_LoggerBuf_Handle i);
static inline xdc_runtime_ILogger_Handle xdc_runtime_LoggerBuf_Handle_upCast2(xdc_runtime_LoggerBuf_Handle i)
{
    return (xdc_runtime_ILogger_Handle)i;
}

/* Handle_to_xdc_runtime_ILogger */
#define xdc_runtime_LoggerBuf_Handle_to_xdc_runtime_ILogger xdc_runtime_LoggerBuf_Handle_upCast2

/* Handle_downCast2 */
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_Handle_downCast2(xdc_runtime_ILogger_Handle i);
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_Handle_downCast2(xdc_runtime_ILogger_Handle i)
{
    xdc_runtime_ILogger_Handle i2 = (xdc_runtime_ILogger_Handle)i;
    return ((const void*)i2->__fxns == (const void*)&xdc_runtime_LoggerBuf_Module__FXNS__C) ? (xdc_runtime_LoggerBuf_Handle)i : (xdc_runtime_LoggerBuf_Handle)NULL;
}

/* Handle_from_xdc_runtime_ILogger */
#define xdc_runtime_LoggerBuf_Handle_from_xdc_runtime_ILogger xdc_runtime_LoggerBuf_Handle_downCast2


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define xdc_runtime_LoggerBuf_Module_startupDone() xdc_runtime_LoggerBuf_Module__startupDone__S()

/* Object_heap */
#define xdc_runtime_LoggerBuf_Object_heap() xdc_runtime_LoggerBuf_Object__heap__C

/* Module_heap */
#define xdc_runtime_LoggerBuf_Module_heap() xdc_runtime_LoggerBuf_Object__heap__C

/* Module_id */
static inline CT__xdc_runtime_LoggerBuf_Module__id xdc_runtime_LoggerBuf_Module_id(void);
static inline CT__xdc_runtime_LoggerBuf_Module__id xdc_runtime_LoggerBuf_Module_id( void ) 
{
    return xdc_runtime_LoggerBuf_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool xdc_runtime_LoggerBuf_Module_hasMask(void);
static inline xdc_Bool xdc_runtime_LoggerBuf_Module_hasMask(void)
{
    return (xdc_Bool)(xdc_runtime_LoggerBuf_Module__diagsMask__C != (CT__xdc_runtime_LoggerBuf_Module__diagsMask)NULL);
}

/* Module_getMask */
static inline xdc_Bits16 xdc_runtime_LoggerBuf_Module_getMask(void);
static inline xdc_Bits16 xdc_runtime_LoggerBuf_Module_getMask(void)
{
    return (xdc_runtime_LoggerBuf_Module__diagsMask__C != (CT__xdc_runtime_LoggerBuf_Module__diagsMask)NULL) ? *xdc_runtime_LoggerBuf_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void xdc_runtime_LoggerBuf_Module_setMask(xdc_Bits16 mask);
static inline xdc_Void xdc_runtime_LoggerBuf_Module_setMask(xdc_Bits16 mask)
{
    if (xdc_runtime_LoggerBuf_Module__diagsMask__C != (CT__xdc_runtime_LoggerBuf_Module__diagsMask)NULL) {
        *xdc_runtime_LoggerBuf_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void xdc_runtime_LoggerBuf_Params_init(xdc_runtime_LoggerBuf_Params *prms);
static inline void xdc_runtime_LoggerBuf_Params_init( xdc_runtime_LoggerBuf_Params *prms ) 
{
    if (prms != NULL) {
        xdc_runtime_LoggerBuf_Params__init__S(prms, NULL, sizeof(xdc_runtime_LoggerBuf_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void xdc_runtime_LoggerBuf_Params_copy(xdc_runtime_LoggerBuf_Params *dst, const xdc_runtime_LoggerBuf_Params *src);
static inline void xdc_runtime_LoggerBuf_Params_copy(xdc_runtime_LoggerBuf_Params *dst, const xdc_runtime_LoggerBuf_Params *src) 
{
    if (dst != NULL) {
        xdc_runtime_LoggerBuf_Params__init__S(dst, (const void *)src, sizeof(xdc_runtime_LoggerBuf_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define xdc_runtime_LoggerBuf_Object_count() xdc_runtime_LoggerBuf_Object__count__C

/* Object_sizeof */
#define xdc_runtime_LoggerBuf_Object_sizeof() xdc_runtime_LoggerBuf_Object__sizeof__C

/* Object_get */
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_Object_get(xdc_runtime_LoggerBuf_Instance_State *oarr, int i);
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_Object_get(xdc_runtime_LoggerBuf_Instance_State *oarr, int i) 
{
    return (xdc_runtime_LoggerBuf_Handle)xdc_runtime_LoggerBuf_Object__get__S(oarr, i);
}

/* Object_first */
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_Object_first(void);
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_Object_first(void)
{
    return (xdc_runtime_LoggerBuf_Handle)xdc_runtime_LoggerBuf_Object__first__S();
}

/* Object_next */
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_Object_next(xdc_runtime_LoggerBuf_Object *obj);
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_Object_next(xdc_runtime_LoggerBuf_Object *obj)
{
    return (xdc_runtime_LoggerBuf_Handle)xdc_runtime_LoggerBuf_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *xdc_runtime_LoggerBuf_Handle_label(xdc_runtime_LoggerBuf_Handle inst, xdc_runtime_Types_Label *lab);
static inline xdc_runtime_Types_Label *xdc_runtime_LoggerBuf_Handle_label(xdc_runtime_LoggerBuf_Handle inst, xdc_runtime_Types_Label *lab)
{
    return xdc_runtime_LoggerBuf_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String xdc_runtime_LoggerBuf_Handle_name(xdc_runtime_LoggerBuf_Handle inst);
static inline xdc_String xdc_runtime_LoggerBuf_Handle_name(xdc_runtime_LoggerBuf_Handle inst)
{
    xdc_runtime_Types_Label lab;
    return xdc_runtime_LoggerBuf_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_handle(xdc_runtime_LoggerBuf_Struct *str);
static inline xdc_runtime_LoggerBuf_Handle xdc_runtime_LoggerBuf_handle(xdc_runtime_LoggerBuf_Struct *str)
{
    return (xdc_runtime_LoggerBuf_Handle)str;
}

/* struct */
static inline xdc_runtime_LoggerBuf_Struct *xdc_runtime_LoggerBuf_struct(xdc_runtime_LoggerBuf_Handle inst);
static inline xdc_runtime_LoggerBuf_Struct *xdc_runtime_LoggerBuf_struct(xdc_runtime_LoggerBuf_Handle inst)
{
    return (xdc_runtime_LoggerBuf_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef xdc_runtime_LoggerBuf__top__
#undef __nested__
#endif

#endif /* xdc_runtime_LoggerBuf__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(xdc_runtime_LoggerBuf__internalaccess))

#ifndef xdc_runtime_LoggerBuf__include_state
#define xdc_runtime_LoggerBuf__include_state

/* Module_State */
struct xdc_runtime_LoggerBuf_Module_State {
    xdc_runtime_Diags_Mask level1;
    xdc_runtime_Diags_Mask level2;
    xdc_runtime_Diags_Mask level3;
};

/* Module__state__V */
#ifndef xdc_runtime_LoggerBuf_Module__state__VR
extern struct xdc_runtime_LoggerBuf_Module_State__ xdc_runtime_LoggerBuf_Module__state__V;
#else
#define xdc_runtime_LoggerBuf_Module__state__V (*((struct xdc_runtime_LoggerBuf_Module_State__*)(xdcRomStatePtr + xdc_runtime_LoggerBuf_Module__state__V_offset)))
#endif

/* Object */
struct xdc_runtime_LoggerBuf_Object {
    const xdc_runtime_LoggerBuf_Fxns__ *__fxns;
    xdc_runtime_IHeap_Handle bufHeap;
    __TA_xdc_runtime_LoggerBuf_Instance_State__entryArr entryArr;
    xdc_runtime_LoggerBuf_Entry *curEntry;
    xdc_runtime_LoggerBuf_Entry *endEntry;
    xdc_runtime_LoggerBuf_Entry *readEntry;
    xdc_Bits32 serial;
    xdc_UInt16 numEntries;
    xdc_Int8 advance;
    xdc_Bool enabled;
    xdc_Bool flush;
};

#endif /* xdc_runtime_LoggerBuf__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(xdc_runtime_LoggerBuf__nolocalnames)

#ifndef xdc_runtime_LoggerBuf__localnames__done
#define xdc_runtime_LoggerBuf__localnames__done

/* module prefix */
#define LoggerBuf_Instance xdc_runtime_LoggerBuf_Instance
#define LoggerBuf_Handle xdc_runtime_LoggerBuf_Handle
#define LoggerBuf_Module xdc_runtime_LoggerBuf_Module
#define LoggerBuf_Object xdc_runtime_LoggerBuf_Object
#define LoggerBuf_Struct xdc_runtime_LoggerBuf_Struct
#define LoggerBuf_BufType xdc_runtime_LoggerBuf_BufType
#define LoggerBuf_FULL xdc_runtime_LoggerBuf_FULL
#define LoggerBuf_WRAP xdc_runtime_LoggerBuf_WRAP
#define LoggerBuf_NEXT xdc_runtime_LoggerBuf_NEXT
#define LoggerBuf_Entry xdc_runtime_LoggerBuf_Entry
#define LoggerBuf_Module_State xdc_runtime_LoggerBuf_Module_State
#define LoggerBuf_Instance_State xdc_runtime_LoggerBuf_Instance_State
#define LoggerBuf_BufType_CIRCULAR xdc_runtime_LoggerBuf_BufType_CIRCULAR
#define LoggerBuf_BufType_FIXED xdc_runtime_LoggerBuf_BufType_FIXED
#define LoggerBuf_filterByLevel xdc_runtime_LoggerBuf_filterByLevel
#define LoggerBuf_E_badLevel xdc_runtime_LoggerBuf_E_badLevel
#define LoggerBuf_enableFlush xdc_runtime_LoggerBuf_enableFlush
#define LoggerBuf_statusLogger xdc_runtime_LoggerBuf_statusLogger
#define LoggerBuf_level1Mask xdc_runtime_LoggerBuf_level1Mask
#define LoggerBuf_level2Mask xdc_runtime_LoggerBuf_level2Mask
#define LoggerBuf_level3Mask xdc_runtime_LoggerBuf_level3Mask
#define LoggerBuf_level4Mask xdc_runtime_LoggerBuf_level4Mask
#define LoggerBuf_Params xdc_runtime_LoggerBuf_Params
#define LoggerBuf_enable xdc_runtime_LoggerBuf_enable
#define LoggerBuf_disable xdc_runtime_LoggerBuf_disable
#define LoggerBuf_write0 xdc_runtime_LoggerBuf_write0
#define LoggerBuf_write1 xdc_runtime_LoggerBuf_write1
#define LoggerBuf_write2 xdc_runtime_LoggerBuf_write2
#define LoggerBuf_write4 xdc_runtime_LoggerBuf_write4
#define LoggerBuf_write8 xdc_runtime_LoggerBuf_write8
#define LoggerBuf_setFilterLevel xdc_runtime_LoggerBuf_setFilterLevel
#define LoggerBuf_getFilterLevel xdc_runtime_LoggerBuf_getFilterLevel
#define LoggerBuf_flushAll xdc_runtime_LoggerBuf_flushAll
#define LoggerBuf_flushAllInternal xdc_runtime_LoggerBuf_flushAllInternal
#define LoggerBuf_reset xdc_runtime_LoggerBuf_reset
#define LoggerBuf_flush xdc_runtime_LoggerBuf_flush
#define LoggerBuf_getNextEntry xdc_runtime_LoggerBuf_getNextEntry
#define LoggerBuf_Module_name xdc_runtime_LoggerBuf_Module_name
#define LoggerBuf_Module_id xdc_runtime_LoggerBuf_Module_id
#define LoggerBuf_Module_startup xdc_runtime_LoggerBuf_Module_startup
#define LoggerBuf_Module_startupDone xdc_runtime_LoggerBuf_Module_startupDone
#define LoggerBuf_Module_hasMask xdc_runtime_LoggerBuf_Module_hasMask
#define LoggerBuf_Module_getMask xdc_runtime_LoggerBuf_Module_getMask
#define LoggerBuf_Module_setMask xdc_runtime_LoggerBuf_Module_setMask
#define LoggerBuf_Object_heap xdc_runtime_LoggerBuf_Object_heap
#define LoggerBuf_Module_heap xdc_runtime_LoggerBuf_Module_heap
#define LoggerBuf_construct xdc_runtime_LoggerBuf_construct
#define LoggerBuf_create xdc_runtime_LoggerBuf_create
#define LoggerBuf_handle xdc_runtime_LoggerBuf_handle
#define LoggerBuf_struct xdc_runtime_LoggerBuf_struct
#define LoggerBuf_Handle_label xdc_runtime_LoggerBuf_Handle_label
#define LoggerBuf_Handle_name xdc_runtime_LoggerBuf_Handle_name
#define LoggerBuf_Instance_init xdc_runtime_LoggerBuf_Instance_init
#define LoggerBuf_Object_count xdc_runtime_LoggerBuf_Object_count
#define LoggerBuf_Object_get xdc_runtime_LoggerBuf_Object_get
#define LoggerBuf_Object_first xdc_runtime_LoggerBuf_Object_first
#define LoggerBuf_Object_next xdc_runtime_LoggerBuf_Object_next
#define LoggerBuf_Object_sizeof xdc_runtime_LoggerBuf_Object_sizeof
#define LoggerBuf_Params_copy xdc_runtime_LoggerBuf_Params_copy
#define LoggerBuf_Params_init xdc_runtime_LoggerBuf_Params_init
#define LoggerBuf_Instance_finalize xdc_runtime_LoggerBuf_Instance_finalize
#define LoggerBuf_delete xdc_runtime_LoggerBuf_delete
#define LoggerBuf_destruct xdc_runtime_LoggerBuf_destruct
#define LoggerBuf_Module_upCast xdc_runtime_LoggerBuf_Module_upCast
#define LoggerBuf_Module_to_xdc_runtime_IFilterLogger xdc_runtime_LoggerBuf_Module_to_xdc_runtime_IFilterLogger
#define LoggerBuf_Handle_upCast xdc_runtime_LoggerBuf_Handle_upCast
#define LoggerBuf_Handle_to_xdc_runtime_IFilterLogger xdc_runtime_LoggerBuf_Handle_to_xdc_runtime_IFilterLogger
#define LoggerBuf_Handle_downCast xdc_runtime_LoggerBuf_Handle_downCast
#define LoggerBuf_Handle_from_xdc_runtime_IFilterLogger xdc_runtime_LoggerBuf_Handle_from_xdc_runtime_IFilterLogger
#define LoggerBuf_Module_upCast2 xdc_runtime_LoggerBuf_Module_upCast2
#define LoggerBuf_Module_to_xdc_runtime_ILogger xdc_runtime_LoggerBuf_Module_to_xdc_runtime_ILogger
#define LoggerBuf_Handle_upCast2 xdc_runtime_LoggerBuf_Handle_upCast2
#define LoggerBuf_Handle_to_xdc_runtime_ILogger xdc_runtime_LoggerBuf_Handle_to_xdc_runtime_ILogger
#define LoggerBuf_Handle_downCast2 xdc_runtime_LoggerBuf_Handle_downCast2
#define LoggerBuf_Handle_from_xdc_runtime_ILogger xdc_runtime_LoggerBuf_Handle_from_xdc_runtime_ILogger

/* proxies */
#include <xdc/runtime/package/LoggerBuf_TimestampProxy.h>

/* proxies */
#include <xdc/runtime/package/LoggerBuf_Module_GateProxy.h>

#endif /* xdc_runtime_LoggerBuf__localnames__done */
#endif
/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 7-31-2018 11:49:29; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


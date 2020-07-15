/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-E00
 */

/*
 * ======== GENERATED SECTIONS ========
 *
 *     PROLOGUE
 *     INCLUDES
 *
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
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

#ifndef ti_sysbios_family_arm_a15_Cache__include
#define ti_sysbios_family_arm_a15_Cache__include

#ifndef __nested__
#define __nested__
#define ti_sysbios_family_arm_a15_Cache__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sysbios_family_arm_a15_Cache___VERS 200


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/sysbios/family/arm/a15/package/package.defs.h>

#include <xdc/runtime/Assert.h>
#include <ti/sysbios/interfaces/ICache.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Type */
typedef ti_sysbios_interfaces_ICache_Type ti_sysbios_family_arm_a15_Cache_Type;

/* sizeL1dCacheLine */
#define ti_sysbios_family_arm_a15_Cache_sizeL1dCacheLine (64)

/* sizeL1pCacheLine */
#define ti_sysbios_family_arm_a15_Cache_sizeL1pCacheLine (64)

/* sizeL2CacheLine */
#define ti_sysbios_family_arm_a15_Cache_sizeL2CacheLine (64)

/* Type_L1P */
#define ti_sysbios_family_arm_a15_Cache_Type_L1P ti_sysbios_interfaces_ICache_Type_L1P

/* Type_L1D */
#define ti_sysbios_family_arm_a15_Cache_Type_L1D ti_sysbios_interfaces_ICache_Type_L1D

/* Type_L1 */
#define ti_sysbios_family_arm_a15_Cache_Type_L1 ti_sysbios_interfaces_ICache_Type_L1

/* Type_L2P */
#define ti_sysbios_family_arm_a15_Cache_Type_L2P ti_sysbios_interfaces_ICache_Type_L2P

/* Type_L2D */
#define ti_sysbios_family_arm_a15_Cache_Type_L2D ti_sysbios_interfaces_ICache_Type_L2D

/* Type_L2 */
#define ti_sysbios_family_arm_a15_Cache_Type_L2 ti_sysbios_interfaces_ICache_Type_L2

/* Type_ALLP */
#define ti_sysbios_family_arm_a15_Cache_Type_ALLP ti_sysbios_interfaces_ICache_Type_ALLP

/* Type_ALLD */
#define ti_sysbios_family_arm_a15_Cache_Type_ALLD ti_sysbios_interfaces_ICache_Type_ALLD

/* Type_ALL */
#define ti_sysbios_family_arm_a15_Cache_Type_ALL ti_sysbios_interfaces_ICache_Type_ALL


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sysbios_family_arm_a15_Cache_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_Module__diagsEnabled ti_sysbios_family_arm_a15_Cache_Module__diagsEnabled__C;
#ifdef ti_sysbios_family_arm_a15_Cache_Module__diagsEnabled__CR
#define ti_sysbios_family_arm_a15_Cache_Module__diagsEnabled__C (*((CT__ti_sysbios_family_arm_a15_Cache_Module__diagsEnabled*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Module__diagsEnabled__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_Module__diagsEnabled (ti_sysbios_family_arm_a15_Cache_Module__diagsEnabled__C)
#endif

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_family_arm_a15_Cache_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_Module__diagsIncluded ti_sysbios_family_arm_a15_Cache_Module__diagsIncluded__C;
#ifdef ti_sysbios_family_arm_a15_Cache_Module__diagsIncluded__CR
#define ti_sysbios_family_arm_a15_Cache_Module__diagsIncluded__C (*((CT__ti_sysbios_family_arm_a15_Cache_Module__diagsIncluded*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Module__diagsIncluded__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_Module__diagsIncluded (ti_sysbios_family_arm_a15_Cache_Module__diagsIncluded__C)
#endif

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sysbios_family_arm_a15_Cache_Module__diagsMask;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_Module__diagsMask ti_sysbios_family_arm_a15_Cache_Module__diagsMask__C;
#ifdef ti_sysbios_family_arm_a15_Cache_Module__diagsMask__CR
#define ti_sysbios_family_arm_a15_Cache_Module__diagsMask__C (*((CT__ti_sysbios_family_arm_a15_Cache_Module__diagsMask*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Module__diagsMask__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_Module__diagsMask (ti_sysbios_family_arm_a15_Cache_Module__diagsMask__C)
#endif

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_family_arm_a15_Cache_Module__gateObj;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_Module__gateObj ti_sysbios_family_arm_a15_Cache_Module__gateObj__C;
#ifdef ti_sysbios_family_arm_a15_Cache_Module__gateObj__CR
#define ti_sysbios_family_arm_a15_Cache_Module__gateObj__C (*((CT__ti_sysbios_family_arm_a15_Cache_Module__gateObj*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Module__gateObj__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_Module__gateObj (ti_sysbios_family_arm_a15_Cache_Module__gateObj__C)
#endif

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_family_arm_a15_Cache_Module__gatePrms;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_Module__gatePrms ti_sysbios_family_arm_a15_Cache_Module__gatePrms__C;
#ifdef ti_sysbios_family_arm_a15_Cache_Module__gatePrms__CR
#define ti_sysbios_family_arm_a15_Cache_Module__gatePrms__C (*((CT__ti_sysbios_family_arm_a15_Cache_Module__gatePrms*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Module__gatePrms__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_Module__gatePrms (ti_sysbios_family_arm_a15_Cache_Module__gatePrms__C)
#endif

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_family_arm_a15_Cache_Module__id;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_Module__id ti_sysbios_family_arm_a15_Cache_Module__id__C;
#ifdef ti_sysbios_family_arm_a15_Cache_Module__id__CR
#define ti_sysbios_family_arm_a15_Cache_Module__id__C (*((CT__ti_sysbios_family_arm_a15_Cache_Module__id*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Module__id__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_Module__id (ti_sysbios_family_arm_a15_Cache_Module__id__C)
#endif

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_family_arm_a15_Cache_Module__loggerDefined;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_Module__loggerDefined ti_sysbios_family_arm_a15_Cache_Module__loggerDefined__C;
#ifdef ti_sysbios_family_arm_a15_Cache_Module__loggerDefined__CR
#define ti_sysbios_family_arm_a15_Cache_Module__loggerDefined__C (*((CT__ti_sysbios_family_arm_a15_Cache_Module__loggerDefined*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Module__loggerDefined__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_Module__loggerDefined (ti_sysbios_family_arm_a15_Cache_Module__loggerDefined__C)
#endif

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_family_arm_a15_Cache_Module__loggerObj;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_Module__loggerObj ti_sysbios_family_arm_a15_Cache_Module__loggerObj__C;
#ifdef ti_sysbios_family_arm_a15_Cache_Module__loggerObj__CR
#define ti_sysbios_family_arm_a15_Cache_Module__loggerObj__C (*((CT__ti_sysbios_family_arm_a15_Cache_Module__loggerObj*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Module__loggerObj__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_Module__loggerObj (ti_sysbios_family_arm_a15_Cache_Module__loggerObj__C)
#endif

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_family_arm_a15_Cache_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_Module__loggerFxn0 ti_sysbios_family_arm_a15_Cache_Module__loggerFxn0__C;
#ifdef ti_sysbios_family_arm_a15_Cache_Module__loggerFxn0__CR
#define ti_sysbios_family_arm_a15_Cache_Module__loggerFxn0__C (*((CT__ti_sysbios_family_arm_a15_Cache_Module__loggerFxn0*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Module__loggerFxn0__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_Module__loggerFxn0 (ti_sysbios_family_arm_a15_Cache_Module__loggerFxn0__C)
#endif

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_family_arm_a15_Cache_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_Module__loggerFxn1 ti_sysbios_family_arm_a15_Cache_Module__loggerFxn1__C;
#ifdef ti_sysbios_family_arm_a15_Cache_Module__loggerFxn1__CR
#define ti_sysbios_family_arm_a15_Cache_Module__loggerFxn1__C (*((CT__ti_sysbios_family_arm_a15_Cache_Module__loggerFxn1*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Module__loggerFxn1__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_Module__loggerFxn1 (ti_sysbios_family_arm_a15_Cache_Module__loggerFxn1__C)
#endif

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_family_arm_a15_Cache_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_Module__loggerFxn2 ti_sysbios_family_arm_a15_Cache_Module__loggerFxn2__C;
#ifdef ti_sysbios_family_arm_a15_Cache_Module__loggerFxn2__CR
#define ti_sysbios_family_arm_a15_Cache_Module__loggerFxn2__C (*((CT__ti_sysbios_family_arm_a15_Cache_Module__loggerFxn2*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Module__loggerFxn2__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_Module__loggerFxn2 (ti_sysbios_family_arm_a15_Cache_Module__loggerFxn2__C)
#endif

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_family_arm_a15_Cache_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_Module__loggerFxn4 ti_sysbios_family_arm_a15_Cache_Module__loggerFxn4__C;
#ifdef ti_sysbios_family_arm_a15_Cache_Module__loggerFxn4__CR
#define ti_sysbios_family_arm_a15_Cache_Module__loggerFxn4__C (*((CT__ti_sysbios_family_arm_a15_Cache_Module__loggerFxn4*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Module__loggerFxn4__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_Module__loggerFxn4 (ti_sysbios_family_arm_a15_Cache_Module__loggerFxn4__C)
#endif

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_family_arm_a15_Cache_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_Module__loggerFxn8 ti_sysbios_family_arm_a15_Cache_Module__loggerFxn8__C;
#ifdef ti_sysbios_family_arm_a15_Cache_Module__loggerFxn8__CR
#define ti_sysbios_family_arm_a15_Cache_Module__loggerFxn8__C (*((CT__ti_sysbios_family_arm_a15_Cache_Module__loggerFxn8*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Module__loggerFxn8__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_Module__loggerFxn8 (ti_sysbios_family_arm_a15_Cache_Module__loggerFxn8__C)
#endif

/* Object__count */
typedef xdc_Int CT__ti_sysbios_family_arm_a15_Cache_Object__count;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_Object__count ti_sysbios_family_arm_a15_Cache_Object__count__C;
#ifdef ti_sysbios_family_arm_a15_Cache_Object__count__CR
#define ti_sysbios_family_arm_a15_Cache_Object__count__C (*((CT__ti_sysbios_family_arm_a15_Cache_Object__count*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Object__count__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_Object__count (ti_sysbios_family_arm_a15_Cache_Object__count__C)
#endif

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_family_arm_a15_Cache_Object__heap;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_Object__heap ti_sysbios_family_arm_a15_Cache_Object__heap__C;
#ifdef ti_sysbios_family_arm_a15_Cache_Object__heap__CR
#define ti_sysbios_family_arm_a15_Cache_Object__heap__C (*((CT__ti_sysbios_family_arm_a15_Cache_Object__heap*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Object__heap__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_Object__heap (ti_sysbios_family_arm_a15_Cache_Object__heap__C)
#endif

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_family_arm_a15_Cache_Object__sizeof;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_Object__sizeof ti_sysbios_family_arm_a15_Cache_Object__sizeof__C;
#ifdef ti_sysbios_family_arm_a15_Cache_Object__sizeof__CR
#define ti_sysbios_family_arm_a15_Cache_Object__sizeof__C (*((CT__ti_sysbios_family_arm_a15_Cache_Object__sizeof*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Object__sizeof__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_Object__sizeof (ti_sysbios_family_arm_a15_Cache_Object__sizeof__C)
#endif

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_family_arm_a15_Cache_Object__table;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_Object__table ti_sysbios_family_arm_a15_Cache_Object__table__C;
#ifdef ti_sysbios_family_arm_a15_Cache_Object__table__CR
#define ti_sysbios_family_arm_a15_Cache_Object__table__C (*((CT__ti_sysbios_family_arm_a15_Cache_Object__table*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Object__table__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_Object__table (ti_sysbios_family_arm_a15_Cache_Object__table__C)
#endif

/* A_badBlockLength */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_family_arm_a15_Cache_A_badBlockLength;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_A_badBlockLength ti_sysbios_family_arm_a15_Cache_A_badBlockLength__C;
#ifdef ti_sysbios_family_arm_a15_Cache_A_badBlockLength__CR
#define ti_sysbios_family_arm_a15_Cache_A_badBlockLength (*((CT__ti_sysbios_family_arm_a15_Cache_A_badBlockLength*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_A_badBlockLength__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_A_badBlockLength (ti_sysbios_family_arm_a15_Cache_A_badBlockLength__C)
#endif

/* A_blockCrossesPage */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_family_arm_a15_Cache_A_blockCrossesPage;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_A_blockCrossesPage ti_sysbios_family_arm_a15_Cache_A_blockCrossesPage__C;
#ifdef ti_sysbios_family_arm_a15_Cache_A_blockCrossesPage__CR
#define ti_sysbios_family_arm_a15_Cache_A_blockCrossesPage (*((CT__ti_sysbios_family_arm_a15_Cache_A_blockCrossesPage*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_A_blockCrossesPage__C_offset)))
#else
#define ti_sysbios_family_arm_a15_Cache_A_blockCrossesPage (ti_sysbios_family_arm_a15_Cache_A_blockCrossesPage__C)
#endif

/* enableCache */
typedef xdc_Bool CT__ti_sysbios_family_arm_a15_Cache_enableCache;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_enableCache ti_sysbios_family_arm_a15_Cache_enableCache__C;
#ifdef ti_sysbios_family_arm_a15_Cache_enableCache__CR
#define ti_sysbios_family_arm_a15_Cache_enableCache (*((CT__ti_sysbios_family_arm_a15_Cache_enableCache*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_enableCache__C_offset)))
#else
#ifdef ti_sysbios_family_arm_a15_Cache_enableCache__D
#define ti_sysbios_family_arm_a15_Cache_enableCache (ti_sysbios_family_arm_a15_Cache_enableCache__D)
#else
#define ti_sysbios_family_arm_a15_Cache_enableCache (ti_sysbios_family_arm_a15_Cache_enableCache__C)
#endif
#endif

/* errata798870 */
typedef xdc_Bool CT__ti_sysbios_family_arm_a15_Cache_errata798870;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_errata798870 ti_sysbios_family_arm_a15_Cache_errata798870__C;
#ifdef ti_sysbios_family_arm_a15_Cache_errata798870__CR
#define ti_sysbios_family_arm_a15_Cache_errata798870 (*((CT__ti_sysbios_family_arm_a15_Cache_errata798870*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_errata798870__C_offset)))
#else
#ifdef ti_sysbios_family_arm_a15_Cache_errata798870__D
#define ti_sysbios_family_arm_a15_Cache_errata798870 (ti_sysbios_family_arm_a15_Cache_errata798870__D)
#else
#define ti_sysbios_family_arm_a15_Cache_errata798870 (ti_sysbios_family_arm_a15_Cache_errata798870__C)
#endif
#endif

/* branchPredictionEnabled */
typedef xdc_Bool CT__ti_sysbios_family_arm_a15_Cache_branchPredictionEnabled;
__extern __FAR__ const CT__ti_sysbios_family_arm_a15_Cache_branchPredictionEnabled ti_sysbios_family_arm_a15_Cache_branchPredictionEnabled__C;
#ifdef ti_sysbios_family_arm_a15_Cache_branchPredictionEnabled__CR
#define ti_sysbios_family_arm_a15_Cache_branchPredictionEnabled (*((CT__ti_sysbios_family_arm_a15_Cache_branchPredictionEnabled*)(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_branchPredictionEnabled__C_offset)))
#else
#ifdef ti_sysbios_family_arm_a15_Cache_branchPredictionEnabled__D
#define ti_sysbios_family_arm_a15_Cache_branchPredictionEnabled (ti_sysbios_family_arm_a15_Cache_branchPredictionEnabled__D)
#else
#define ti_sysbios_family_arm_a15_Cache_branchPredictionEnabled (ti_sysbios_family_arm_a15_Cache_branchPredictionEnabled__C)
#endif
#endif


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_sysbios_family_arm_a15_Cache_Fxns__ {
    const xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Void (*enable)(xdc_Bits16 type);
    xdc_Void (*disable)(xdc_Bits16 type);
    xdc_Void (*inv)(xdc_Ptr blockPtr, xdc_SizeT byteCnt, xdc_Bits16 type, xdc_Bool wait);
    xdc_Void (*wb)(xdc_Ptr blockPtr, xdc_SizeT byteCnt, xdc_Bits16 type, xdc_Bool wait);
    xdc_Void (*wbInv)(xdc_Ptr blockPtr, xdc_SizeT byteCnt, xdc_Bits16 type, xdc_Bool wait);
    xdc_Void (*wbAll)(void);
    xdc_Void (*wbInvAll)(void);
    xdc_Void (*wait)(void);
    xdc_runtime_Types_SysFxns2 __sfxns;
};
#ifndef ti_sysbios_family_arm_a15_Cache_Module__FXNS__CR

/* Module__FXNS__C */
__extern const ti_sysbios_family_arm_a15_Cache_Fxns__ ti_sysbios_family_arm_a15_Cache_Module__FXNS__C;
#else
#define ti_sysbios_family_arm_a15_Cache_Module__FXNS__C (*(xdcRomConstPtr + ti_sysbios_family_arm_a15_Cache_Module__FXNS__C_offset))
#endif


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sysbios_family_arm_a15_Cache_Module_startup( state ) (-1)

/* Module__startupDone__S */
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_Module__startupDone__S, "ti_sysbios_family_arm_a15_Cache_Module__startupDone__S")
__extern xdc_Bool ti_sysbios_family_arm_a15_Cache_Module__startupDone__S( void );

/* enable__E */
#define ti_sysbios_family_arm_a15_Cache_enable ti_sysbios_family_arm_a15_Cache_enable__E
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_enable__E, "ti_sysbios_family_arm_a15_Cache_enable")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_enable__E( xdc_Bits16 type );

/* disable__E */
#define ti_sysbios_family_arm_a15_Cache_disable ti_sysbios_family_arm_a15_Cache_disable__E
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_disable__E, "ti_sysbios_family_arm_a15_Cache_disable")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_disable__E( xdc_Bits16 type );

/* inv__E */
#define ti_sysbios_family_arm_a15_Cache_inv ti_sysbios_family_arm_a15_Cache_inv__E
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_inv__E, "ti_sysbios_family_arm_a15_Cache_inv")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_inv__E( xdc_Ptr blockPtr, xdc_SizeT byteCnt, xdc_Bits16 type, xdc_Bool wait );

/* wb__E */
#define ti_sysbios_family_arm_a15_Cache_wb ti_sysbios_family_arm_a15_Cache_wb__E
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_wb__E, "ti_sysbios_family_arm_a15_Cache_wb")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_wb__E( xdc_Ptr blockPtr, xdc_SizeT byteCnt, xdc_Bits16 type, xdc_Bool wait );

/* wbInv__E */
#define ti_sysbios_family_arm_a15_Cache_wbInv ti_sysbios_family_arm_a15_Cache_wbInv__E
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_wbInv__E, "ti_sysbios_family_arm_a15_Cache_wbInv")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_wbInv__E( xdc_Ptr blockPtr, xdc_SizeT byteCnt, xdc_Bits16 type, xdc_Bool wait );

/* wbAll__E */
#define ti_sysbios_family_arm_a15_Cache_wbAll ti_sysbios_family_arm_a15_Cache_wbAll__E
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_wbAll__E, "ti_sysbios_family_arm_a15_Cache_wbAll")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_wbAll__E( void );

/* wbInvAll__E */
#define ti_sysbios_family_arm_a15_Cache_wbInvAll ti_sysbios_family_arm_a15_Cache_wbInvAll__E
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_wbInvAll__E, "ti_sysbios_family_arm_a15_Cache_wbInvAll")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_wbInvAll__E( void );

/* wait__E */
#define ti_sysbios_family_arm_a15_Cache_wait ti_sysbios_family_arm_a15_Cache_wait__E
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_wait__E, "ti_sysbios_family_arm_a15_Cache_wait")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_wait__E( void );

/* getEnabled__E */
#define ti_sysbios_family_arm_a15_Cache_getEnabled ti_sysbios_family_arm_a15_Cache_getEnabled__E
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_getEnabled__E, "ti_sysbios_family_arm_a15_Cache_getEnabled")
__extern xdc_Bits16 ti_sysbios_family_arm_a15_Cache_getEnabled__E( void );

/* invL1dAll__E */
#define ti_sysbios_family_arm_a15_Cache_invL1dAll ti_sysbios_family_arm_a15_Cache_invL1dAll__E
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_invL1dAll__E, "ti_sysbios_family_arm_a15_Cache_invL1dAll")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_invL1dAll__E( void );

/* invL1pAll__E */
#define ti_sysbios_family_arm_a15_Cache_invL1pAll ti_sysbios_family_arm_a15_Cache_invL1pAll__E
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_invL1pAll__E, "ti_sysbios_family_arm_a15_Cache_invL1pAll")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_invL1pAll__E( void );

/* preLoad__E */
#define ti_sysbios_family_arm_a15_Cache_preLoad ti_sysbios_family_arm_a15_Cache_preLoad__E
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_preLoad__E, "ti_sysbios_family_arm_a15_Cache_preLoad")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_preLoad__E( xdc_Ptr blockPtr, xdc_SizeT byteCnt );

/* enableBP__E */
#define ti_sysbios_family_arm_a15_Cache_enableBP ti_sysbios_family_arm_a15_Cache_enableBP__E
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_enableBP__E, "ti_sysbios_family_arm_a15_Cache_enableBP")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_enableBP__E( void );

/* disableBP__E */
#define ti_sysbios_family_arm_a15_Cache_disableBP ti_sysbios_family_arm_a15_Cache_disableBP__E
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_disableBP__E, "ti_sysbios_family_arm_a15_Cache_disableBP")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_disableBP__E( void );

/* wbAllLoUIS__E */
#define ti_sysbios_family_arm_a15_Cache_wbAllLoUIS ti_sysbios_family_arm_a15_Cache_wbAllLoUIS__E
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_wbAllLoUIS__E, "ti_sysbios_family_arm_a15_Cache_wbAllLoUIS")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_wbAllLoUIS__E( void );

/* wbInvAllLoUIS__E */
#define ti_sysbios_family_arm_a15_Cache_wbInvAllLoUIS ti_sysbios_family_arm_a15_Cache_wbInvAllLoUIS__E
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_wbInvAllLoUIS__E, "ti_sysbios_family_arm_a15_Cache_wbInvAllLoUIS")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_wbInvAllLoUIS__E( void );

/* invBPAll__E */
#define ti_sysbios_family_arm_a15_Cache_invBPAll ti_sysbios_family_arm_a15_Cache_invBPAll__E
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_invBPAll__E, "ti_sysbios_family_arm_a15_Cache_invBPAll")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_invBPAll__E( void );

/* initModuleState__I */
#define ti_sysbios_family_arm_a15_Cache_initModuleState ti_sysbios_family_arm_a15_Cache_initModuleState__I
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_initModuleState__I, "ti_sysbios_family_arm_a15_Cache_initModuleState")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_initModuleState__I( void );

/* startup__I */
#define ti_sysbios_family_arm_a15_Cache_startup ti_sysbios_family_arm_a15_Cache_startup__I
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_startup__I, "ti_sysbios_family_arm_a15_Cache_startup")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_startup__I( void );

/* disableL1D__I */
#define ti_sysbios_family_arm_a15_Cache_disableL1D ti_sysbios_family_arm_a15_Cache_disableL1D__I
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_disableL1D__I, "ti_sysbios_family_arm_a15_Cache_disableL1D")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_disableL1D__I( void );

/* disableL1P__I */
#define ti_sysbios_family_arm_a15_Cache_disableL1P ti_sysbios_family_arm_a15_Cache_disableL1P__I
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_disableL1P__I, "ti_sysbios_family_arm_a15_Cache_disableL1P")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_disableL1P__I( void );

/* enableL1D__I */
#define ti_sysbios_family_arm_a15_Cache_enableL1D ti_sysbios_family_arm_a15_Cache_enableL1D__I
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_enableL1D__I, "ti_sysbios_family_arm_a15_Cache_enableL1D")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_enableL1D__I( void );

/* enableL1P__I */
#define ti_sysbios_family_arm_a15_Cache_enableL1P ti_sysbios_family_arm_a15_Cache_enableL1P__I
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_enableL1P__I, "ti_sysbios_family_arm_a15_Cache_enableL1P")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_enableL1P__I( void );

/* invL1d__I */
#define ti_sysbios_family_arm_a15_Cache_invL1d ti_sysbios_family_arm_a15_Cache_invL1d__I
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_invL1d__I, "ti_sysbios_family_arm_a15_Cache_invL1d")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_invL1d__I( xdc_Ptr blockPtr, xdc_SizeT byteCnt, xdc_Bool wait );

/* invL1p__I */
#define ti_sysbios_family_arm_a15_Cache_invL1p ti_sysbios_family_arm_a15_Cache_invL1p__I
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_invL1p__I, "ti_sysbios_family_arm_a15_Cache_invL1p")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_invL1p__I( xdc_Ptr blockPtr, xdc_SizeT byteCnt, xdc_Bool wait );

/* preFetch__I */
#define ti_sysbios_family_arm_a15_Cache_preFetch ti_sysbios_family_arm_a15_Cache_preFetch__I
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_preFetch__I, "ti_sysbios_family_arm_a15_Cache_preFetch")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_preFetch__I( xdc_Ptr blockPtr, xdc_SizeT byteCnt );

/* getL2AuxControlReg__I */
#define ti_sysbios_family_arm_a15_Cache_getL2AuxControlReg ti_sysbios_family_arm_a15_Cache_getL2AuxControlReg__I
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_getL2AuxControlReg__I, "ti_sysbios_family_arm_a15_Cache_getL2AuxControlReg")
__extern xdc_Bits32 ti_sysbios_family_arm_a15_Cache_getL2AuxControlReg__I( void );

/* setL2AuxControlReg__I */
#define ti_sysbios_family_arm_a15_Cache_setL2AuxControlReg ti_sysbios_family_arm_a15_Cache_setL2AuxControlReg__I
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_setL2AuxControlReg__I, "ti_sysbios_family_arm_a15_Cache_setL2AuxControlReg")
__extern xdc_Void ti_sysbios_family_arm_a15_Cache_setL2AuxControlReg__I( xdc_Bits32 arg );

/* getCacheLevelInfo__I */
#define ti_sysbios_family_arm_a15_Cache_getCacheLevelInfo ti_sysbios_family_arm_a15_Cache_getCacheLevelInfo__I
xdc__CODESECT(ti_sysbios_family_arm_a15_Cache_getCacheLevelInfo__I, "ti_sysbios_family_arm_a15_Cache_getCacheLevelInfo")
__extern xdc_Bits32 ti_sysbios_family_arm_a15_Cache_getCacheLevelInfo__I( xdc_UInt level );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sysbios_interfaces_ICache_Module ti_sysbios_family_arm_a15_Cache_Module_upCast(void);
static inline ti_sysbios_interfaces_ICache_Module ti_sysbios_family_arm_a15_Cache_Module_upCast(void)
{
    return (ti_sysbios_interfaces_ICache_Module)&ti_sysbios_family_arm_a15_Cache_Module__FXNS__C;
}

/* Module_to_ti_sysbios_interfaces_ICache */
#define ti_sysbios_family_arm_a15_Cache_Module_to_ti_sysbios_interfaces_ICache ti_sysbios_family_arm_a15_Cache_Module_upCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sysbios_family_arm_a15_Cache_Module_startupDone() ti_sysbios_family_arm_a15_Cache_Module__startupDone__S()

/* Object_heap */
#define ti_sysbios_family_arm_a15_Cache_Object_heap() ti_sysbios_family_arm_a15_Cache_Object__heap__C

/* Module_heap */
#define ti_sysbios_family_arm_a15_Cache_Module_heap() ti_sysbios_family_arm_a15_Cache_Object__heap__C

/* Module_id */
static inline CT__ti_sysbios_family_arm_a15_Cache_Module__id ti_sysbios_family_arm_a15_Cache_Module_id(void);
static inline CT__ti_sysbios_family_arm_a15_Cache_Module__id ti_sysbios_family_arm_a15_Cache_Module_id( void ) 
{
    return ti_sysbios_family_arm_a15_Cache_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sysbios_family_arm_a15_Cache_Module_hasMask(void);
static inline xdc_Bool ti_sysbios_family_arm_a15_Cache_Module_hasMask(void)
{
    return (xdc_Bool)(ti_sysbios_family_arm_a15_Cache_Module__diagsMask__C != (CT__ti_sysbios_family_arm_a15_Cache_Module__diagsMask)NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sysbios_family_arm_a15_Cache_Module_getMask(void);
static inline xdc_Bits16 ti_sysbios_family_arm_a15_Cache_Module_getMask(void)
{
    return (ti_sysbios_family_arm_a15_Cache_Module__diagsMask__C != (CT__ti_sysbios_family_arm_a15_Cache_Module__diagsMask)NULL) ? *ti_sysbios_family_arm_a15_Cache_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sysbios_family_arm_a15_Cache_Module_setMask(xdc_Bits16 mask);
static inline xdc_Void ti_sysbios_family_arm_a15_Cache_Module_setMask(xdc_Bits16 mask)
{
    if (ti_sysbios_family_arm_a15_Cache_Module__diagsMask__C != (CT__ti_sysbios_family_arm_a15_Cache_Module__diagsMask)NULL) {
        *ti_sysbios_family_arm_a15_Cache_Module__diagsMask__C = mask;
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sysbios_family_arm_a15_Cache__top__
#undef __nested__
#endif

#endif /* ti_sysbios_family_arm_a15_Cache__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sysbios_family_arm_a15_Cache__internalaccess))

#ifndef ti_sysbios_family_arm_a15_Cache__include_state
#define ti_sysbios_family_arm_a15_Cache__include_state

/* Module_State */
struct ti_sysbios_family_arm_a15_Cache_Module_State {
    xdc_Bits32 l1dInfo;
    xdc_Bits32 l1pInfo;
    xdc_Bits32 l2Info;
    xdc_SizeT l2WaySize;
};

/* Module__state__V */
#ifndef ti_sysbios_family_arm_a15_Cache_Module__state__VR
extern struct ti_sysbios_family_arm_a15_Cache_Module_State__ ti_sysbios_family_arm_a15_Cache_Module__state__V;
#else
#define ti_sysbios_family_arm_a15_Cache_Module__state__V (*((struct ti_sysbios_family_arm_a15_Cache_Module_State__*)(xdcRomStatePtr + ti_sysbios_family_arm_a15_Cache_Module__state__V_offset)))
#endif

#endif /* ti_sysbios_family_arm_a15_Cache__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sysbios_family_arm_a15_Cache__nolocalnames)

#ifndef ti_sysbios_family_arm_a15_Cache__localnames__done
#define ti_sysbios_family_arm_a15_Cache__localnames__done

/* module prefix */
#define Cache_Type ti_sysbios_family_arm_a15_Cache_Type
#define Cache_sizeL1dCacheLine ti_sysbios_family_arm_a15_Cache_sizeL1dCacheLine
#define Cache_sizeL1pCacheLine ti_sysbios_family_arm_a15_Cache_sizeL1pCacheLine
#define Cache_sizeL2CacheLine ti_sysbios_family_arm_a15_Cache_sizeL2CacheLine
#define Cache_Module_State ti_sysbios_family_arm_a15_Cache_Module_State
#define Cache_Type_L1P ti_sysbios_family_arm_a15_Cache_Type_L1P
#define Cache_Type_L1D ti_sysbios_family_arm_a15_Cache_Type_L1D
#define Cache_Type_L1 ti_sysbios_family_arm_a15_Cache_Type_L1
#define Cache_Type_L2P ti_sysbios_family_arm_a15_Cache_Type_L2P
#define Cache_Type_L2D ti_sysbios_family_arm_a15_Cache_Type_L2D
#define Cache_Type_L2 ti_sysbios_family_arm_a15_Cache_Type_L2
#define Cache_Type_ALLP ti_sysbios_family_arm_a15_Cache_Type_ALLP
#define Cache_Type_ALLD ti_sysbios_family_arm_a15_Cache_Type_ALLD
#define Cache_Type_ALL ti_sysbios_family_arm_a15_Cache_Type_ALL
#define Cache_A_badBlockLength ti_sysbios_family_arm_a15_Cache_A_badBlockLength
#define Cache_A_blockCrossesPage ti_sysbios_family_arm_a15_Cache_A_blockCrossesPage
#define Cache_enableCache ti_sysbios_family_arm_a15_Cache_enableCache
#define Cache_errata798870 ti_sysbios_family_arm_a15_Cache_errata798870
#define Cache_branchPredictionEnabled ti_sysbios_family_arm_a15_Cache_branchPredictionEnabled
#define Cache_enable ti_sysbios_family_arm_a15_Cache_enable
#define Cache_disable ti_sysbios_family_arm_a15_Cache_disable
#define Cache_inv ti_sysbios_family_arm_a15_Cache_inv
#define Cache_wb ti_sysbios_family_arm_a15_Cache_wb
#define Cache_wbInv ti_sysbios_family_arm_a15_Cache_wbInv
#define Cache_wbAll ti_sysbios_family_arm_a15_Cache_wbAll
#define Cache_wbInvAll ti_sysbios_family_arm_a15_Cache_wbInvAll
#define Cache_wait ti_sysbios_family_arm_a15_Cache_wait
#define Cache_getEnabled ti_sysbios_family_arm_a15_Cache_getEnabled
#define Cache_invL1dAll ti_sysbios_family_arm_a15_Cache_invL1dAll
#define Cache_invL1pAll ti_sysbios_family_arm_a15_Cache_invL1pAll
#define Cache_preLoad ti_sysbios_family_arm_a15_Cache_preLoad
#define Cache_enableBP ti_sysbios_family_arm_a15_Cache_enableBP
#define Cache_disableBP ti_sysbios_family_arm_a15_Cache_disableBP
#define Cache_wbAllLoUIS ti_sysbios_family_arm_a15_Cache_wbAllLoUIS
#define Cache_wbInvAllLoUIS ti_sysbios_family_arm_a15_Cache_wbInvAllLoUIS
#define Cache_invBPAll ti_sysbios_family_arm_a15_Cache_invBPAll
#define Cache_Module_name ti_sysbios_family_arm_a15_Cache_Module_name
#define Cache_Module_id ti_sysbios_family_arm_a15_Cache_Module_id
#define Cache_Module_startup ti_sysbios_family_arm_a15_Cache_Module_startup
#define Cache_Module_startupDone ti_sysbios_family_arm_a15_Cache_Module_startupDone
#define Cache_Module_hasMask ti_sysbios_family_arm_a15_Cache_Module_hasMask
#define Cache_Module_getMask ti_sysbios_family_arm_a15_Cache_Module_getMask
#define Cache_Module_setMask ti_sysbios_family_arm_a15_Cache_Module_setMask
#define Cache_Object_heap ti_sysbios_family_arm_a15_Cache_Object_heap
#define Cache_Module_heap ti_sysbios_family_arm_a15_Cache_Module_heap
#define Cache_Module_upCast ti_sysbios_family_arm_a15_Cache_Module_upCast
#define Cache_Module_to_ti_sysbios_interfaces_ICache ti_sysbios_family_arm_a15_Cache_Module_to_ti_sysbios_interfaces_ICache

#endif /* ti_sysbios_family_arm_a15_Cache__localnames__done */
#endif

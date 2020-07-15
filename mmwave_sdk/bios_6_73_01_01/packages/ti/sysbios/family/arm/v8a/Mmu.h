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

#ifndef ti_sysbios_family_arm_v8a_Mmu__include
#define ti_sysbios_family_arm_v8a_Mmu__include

#ifndef __nested__
#define __nested__
#define ti_sysbios_family_arm_v8a_Mmu__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sysbios_family_arm_v8a_Mmu___VERS 200


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/sysbios/family/arm/v8a/package/package.defs.h>

#include <xdc/runtime/IModule.h>
#include <xdc/runtime/Assert.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* PA_MAX_WIDTH */
#define ti_sysbios_family_arm_v8a_Mmu_PA_MAX_WIDTH (48)

/* PA_SIZE_ENCODING */
#define ti_sysbios_family_arm_v8a_Mmu_PA_SIZE_ENCODING (0x5)

/* AttrIndx */
enum ti_sysbios_family_arm_v8a_Mmu_AttrIndx {
    ti_sysbios_family_arm_v8a_Mmu_AttrIndx_MAIR0 = 0,
    ti_sysbios_family_arm_v8a_Mmu_AttrIndx_MAIR1,
    ti_sysbios_family_arm_v8a_Mmu_AttrIndx_MAIR2,
    ti_sysbios_family_arm_v8a_Mmu_AttrIndx_MAIR3,
    ti_sysbios_family_arm_v8a_Mmu_AttrIndx_MAIR4,
    ti_sysbios_family_arm_v8a_Mmu_AttrIndx_MAIR5,
    ti_sysbios_family_arm_v8a_Mmu_AttrIndx_MAIR6,
    ti_sysbios_family_arm_v8a_Mmu_AttrIndx_MAIR7
};
typedef enum ti_sysbios_family_arm_v8a_Mmu_AttrIndx ti_sysbios_family_arm_v8a_Mmu_AttrIndx;

/* DescriptorType */
enum ti_sysbios_family_arm_v8a_Mmu_DescriptorType {
    ti_sysbios_family_arm_v8a_Mmu_DescriptorType_INVALID0 = 0,
    ti_sysbios_family_arm_v8a_Mmu_DescriptorType_BLOCK = 1,
    ti_sysbios_family_arm_v8a_Mmu_DescriptorType_INVALID1 = 2,
    ti_sysbios_family_arm_v8a_Mmu_DescriptorType_TABLE = 3
};
typedef enum ti_sysbios_family_arm_v8a_Mmu_DescriptorType ti_sysbios_family_arm_v8a_Mmu_DescriptorType;

/* GranuleSize */
enum ti_sysbios_family_arm_v8a_Mmu_GranuleSize {
    ti_sysbios_family_arm_v8a_Mmu_GranuleSize_4KB = 0x1000,
    ti_sysbios_family_arm_v8a_Mmu_GranuleSize_16KB = 0x4000,
    ti_sysbios_family_arm_v8a_Mmu_GranuleSize_64KB = 0x10000
};
typedef enum ti_sysbios_family_arm_v8a_Mmu_GranuleSize ti_sysbios_family_arm_v8a_Mmu_GranuleSize;

/* Shareable */
enum ti_sysbios_family_arm_v8a_Mmu_Shareable {
    ti_sysbios_family_arm_v8a_Mmu_Shareable_NONE = 0x0,
    ti_sysbios_family_arm_v8a_Mmu_Shareable_OUTER = 0x2,
    ti_sysbios_family_arm_v8a_Mmu_Shareable_INNER = 0x3
};
typedef enum ti_sysbios_family_arm_v8a_Mmu_Shareable ti_sysbios_family_arm_v8a_Mmu_Shareable;

/* AccessPerm */
enum ti_sysbios_family_arm_v8a_Mmu_AccessPerm {
    ti_sysbios_family_arm_v8a_Mmu_AccessPerm_PRIV_RW_USER_NONE = 0x0,
    ti_sysbios_family_arm_v8a_Mmu_AccessPerm_PRIV_RW_USER_RW = 0x1,
    ti_sysbios_family_arm_v8a_Mmu_AccessPerm_PRIV_RO_USER_NONE = 0x2,
    ti_sysbios_family_arm_v8a_Mmu_AccessPerm_PRIV_RO_USER_RO = 0x3
};
typedef enum ti_sysbios_family_arm_v8a_Mmu_AccessPerm ti_sysbios_family_arm_v8a_Mmu_AccessPerm;

/* InitFuncPtr */
typedef xdc_Void (*ti_sysbios_family_arm_v8a_Mmu_InitFuncPtr)(xdc_Void );

/* MapAttrs */
struct ti_sysbios_family_arm_v8a_Mmu_MapAttrs {
    ti_sysbios_family_arm_v8a_Mmu_AccessPerm accessPerm;
    xdc_Bool privExecute;
    xdc_Bool userExecute;
    ti_sysbios_family_arm_v8a_Mmu_Shareable shareable;
    ti_sysbios_family_arm_v8a_Mmu_AttrIndx attrIndx;
    xdc_Bool global;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* ConfigInfo */
typedef xdc_UInt8 __T1_ti_sysbios_family_arm_v8a_Mmu_ConfigInfo__tableOffset;
typedef xdc_UInt8 ARRAY1_ti_sysbios_family_arm_v8a_Mmu_ConfigInfo__tableOffset[4];
typedef xdc_UInt8 CARRAY1_ti_sysbios_family_arm_v8a_Mmu_ConfigInfo__tableOffset[4];
typedef CARRAY1_ti_sysbios_family_arm_v8a_Mmu_ConfigInfo__tableOffset __TA_ti_sysbios_family_arm_v8a_Mmu_ConfigInfo__tableOffset;
struct ti_sysbios_family_arm_v8a_Mmu_ConfigInfo {
    xdc_UInt64 indexMask;
    xdc_UInt32 tableLength;
    __TA_ti_sysbios_family_arm_v8a_Mmu_ConfigInfo__tableOffset tableOffset;
    xdc_UInt8 granuleSizeBits;
    xdc_UInt8 indexBits;
    xdc_Bool noLevel0Table;
};


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sysbios_family_arm_v8a_Mmu_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_Module__diagsEnabled ti_sysbios_family_arm_v8a_Mmu_Module__diagsEnabled__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__diagsEnabled__CR
#define ti_sysbios_family_arm_v8a_Mmu_Module__diagsEnabled__C (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__diagsEnabled*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__diagsEnabled__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_Module__diagsEnabled (ti_sysbios_family_arm_v8a_Mmu_Module__diagsEnabled__C)
#endif

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_family_arm_v8a_Mmu_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_Module__diagsIncluded ti_sysbios_family_arm_v8a_Mmu_Module__diagsIncluded__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__diagsIncluded__CR
#define ti_sysbios_family_arm_v8a_Mmu_Module__diagsIncluded__C (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__diagsIncluded*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__diagsIncluded__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_Module__diagsIncluded (ti_sysbios_family_arm_v8a_Mmu_Module__diagsIncluded__C)
#endif

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask__CR
#define ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask__C (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask (ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask__C)
#endif

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_family_arm_v8a_Mmu_Module__gateObj;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_Module__gateObj ti_sysbios_family_arm_v8a_Mmu_Module__gateObj__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__gateObj__CR
#define ti_sysbios_family_arm_v8a_Mmu_Module__gateObj__C (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__gateObj*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__gateObj__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_Module__gateObj (ti_sysbios_family_arm_v8a_Mmu_Module__gateObj__C)
#endif

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_family_arm_v8a_Mmu_Module__gatePrms;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_Module__gatePrms ti_sysbios_family_arm_v8a_Mmu_Module__gatePrms__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__gatePrms__CR
#define ti_sysbios_family_arm_v8a_Mmu_Module__gatePrms__C (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__gatePrms*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__gatePrms__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_Module__gatePrms (ti_sysbios_family_arm_v8a_Mmu_Module__gatePrms__C)
#endif

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_family_arm_v8a_Mmu_Module__id;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_Module__id ti_sysbios_family_arm_v8a_Mmu_Module__id__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__id__CR
#define ti_sysbios_family_arm_v8a_Mmu_Module__id__C (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__id*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__id__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_Module__id (ti_sysbios_family_arm_v8a_Mmu_Module__id__C)
#endif

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerDefined;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerDefined ti_sysbios_family_arm_v8a_Mmu_Module__loggerDefined__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__loggerDefined__CR
#define ti_sysbios_family_arm_v8a_Mmu_Module__loggerDefined__C (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerDefined*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__loggerDefined__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_Module__loggerDefined (ti_sysbios_family_arm_v8a_Mmu_Module__loggerDefined__C)
#endif

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerObj;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerObj ti_sysbios_family_arm_v8a_Mmu_Module__loggerObj__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__loggerObj__CR
#define ti_sysbios_family_arm_v8a_Mmu_Module__loggerObj__C (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerObj*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__loggerObj__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_Module__loggerObj (ti_sysbios_family_arm_v8a_Mmu_Module__loggerObj__C)
#endif

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn0 ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn0__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn0__CR
#define ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn0__C (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn0*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn0__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn0 (ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn0__C)
#endif

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn1 ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn1__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn1__CR
#define ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn1__C (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn1*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn1__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn1 (ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn1__C)
#endif

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn2 ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn2__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn2__CR
#define ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn2__C (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn2*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn2__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn2 (ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn2__C)
#endif

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn4 ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn4__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn4__CR
#define ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn4__C (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn4*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn4__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn4 (ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn4__C)
#endif

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn8 ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn8__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn8__CR
#define ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn8__C (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn8*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn8__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn8 (ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn8__C)
#endif

/* Object__count */
typedef xdc_Int CT__ti_sysbios_family_arm_v8a_Mmu_Object__count;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_Object__count ti_sysbios_family_arm_v8a_Mmu_Object__count__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_Object__count__CR
#define ti_sysbios_family_arm_v8a_Mmu_Object__count__C (*((CT__ti_sysbios_family_arm_v8a_Mmu_Object__count*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Object__count__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_Object__count (ti_sysbios_family_arm_v8a_Mmu_Object__count__C)
#endif

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_family_arm_v8a_Mmu_Object__heap;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_Object__heap ti_sysbios_family_arm_v8a_Mmu_Object__heap__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_Object__heap__CR
#define ti_sysbios_family_arm_v8a_Mmu_Object__heap__C (*((CT__ti_sysbios_family_arm_v8a_Mmu_Object__heap*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Object__heap__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_Object__heap (ti_sysbios_family_arm_v8a_Mmu_Object__heap__C)
#endif

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_family_arm_v8a_Mmu_Object__sizeof;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_Object__sizeof ti_sysbios_family_arm_v8a_Mmu_Object__sizeof__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_Object__sizeof__CR
#define ti_sysbios_family_arm_v8a_Mmu_Object__sizeof__C (*((CT__ti_sysbios_family_arm_v8a_Mmu_Object__sizeof*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Object__sizeof__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_Object__sizeof (ti_sysbios_family_arm_v8a_Mmu_Object__sizeof__C)
#endif

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_family_arm_v8a_Mmu_Object__table;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_Object__table ti_sysbios_family_arm_v8a_Mmu_Object__table__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_Object__table__CR
#define ti_sysbios_family_arm_v8a_Mmu_Object__table__C (*((CT__ti_sysbios_family_arm_v8a_Mmu_Object__table*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Object__table__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_Object__table (ti_sysbios_family_arm_v8a_Mmu_Object__table__C)
#endif

/* A_nullPointer */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_family_arm_v8a_Mmu_A_nullPointer;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_A_nullPointer ti_sysbios_family_arm_v8a_Mmu_A_nullPointer__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_A_nullPointer__CR
#define ti_sysbios_family_arm_v8a_Mmu_A_nullPointer (*((CT__ti_sysbios_family_arm_v8a_Mmu_A_nullPointer*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_A_nullPointer__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_A_nullPointer (ti_sysbios_family_arm_v8a_Mmu_A_nullPointer__C)
#endif

/* A_vaddrOutOfRange */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_family_arm_v8a_Mmu_A_vaddrOutOfRange;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_A_vaddrOutOfRange ti_sysbios_family_arm_v8a_Mmu_A_vaddrOutOfRange__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_A_vaddrOutOfRange__CR
#define ti_sysbios_family_arm_v8a_Mmu_A_vaddrOutOfRange (*((CT__ti_sysbios_family_arm_v8a_Mmu_A_vaddrOutOfRange*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_A_vaddrOutOfRange__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_A_vaddrOutOfRange (ti_sysbios_family_arm_v8a_Mmu_A_vaddrOutOfRange__C)
#endif

/* A_paddrOutOfRange */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_family_arm_v8a_Mmu_A_paddrOutOfRange;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_A_paddrOutOfRange ti_sysbios_family_arm_v8a_Mmu_A_paddrOutOfRange__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_A_paddrOutOfRange__CR
#define ti_sysbios_family_arm_v8a_Mmu_A_paddrOutOfRange (*((CT__ti_sysbios_family_arm_v8a_Mmu_A_paddrOutOfRange*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_A_paddrOutOfRange__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_A_paddrOutOfRange (ti_sysbios_family_arm_v8a_Mmu_A_paddrOutOfRange__C)
#endif

/* A_unalignedVaddr */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_family_arm_v8a_Mmu_A_unalignedVaddr;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_A_unalignedVaddr ti_sysbios_family_arm_v8a_Mmu_A_unalignedVaddr__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_A_unalignedVaddr__CR
#define ti_sysbios_family_arm_v8a_Mmu_A_unalignedVaddr (*((CT__ti_sysbios_family_arm_v8a_Mmu_A_unalignedVaddr*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_A_unalignedVaddr__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_A_unalignedVaddr (ti_sysbios_family_arm_v8a_Mmu_A_unalignedVaddr__C)
#endif

/* A_unalignedPaddr */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_family_arm_v8a_Mmu_A_unalignedPaddr;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_A_unalignedPaddr ti_sysbios_family_arm_v8a_Mmu_A_unalignedPaddr__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_A_unalignedPaddr__CR
#define ti_sysbios_family_arm_v8a_Mmu_A_unalignedPaddr (*((CT__ti_sysbios_family_arm_v8a_Mmu_A_unalignedPaddr*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_A_unalignedPaddr__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_A_unalignedPaddr (ti_sysbios_family_arm_v8a_Mmu_A_unalignedPaddr__C)
#endif

/* A_unalignedSize */
typedef xdc_runtime_Assert_Id CT__ti_sysbios_family_arm_v8a_Mmu_A_unalignedSize;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_A_unalignedSize ti_sysbios_family_arm_v8a_Mmu_A_unalignedSize__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_A_unalignedSize__CR
#define ti_sysbios_family_arm_v8a_Mmu_A_unalignedSize (*((CT__ti_sysbios_family_arm_v8a_Mmu_A_unalignedSize*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_A_unalignedSize__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_A_unalignedSize (ti_sysbios_family_arm_v8a_Mmu_A_unalignedSize__C)
#endif

/* defaultMapAttrs */
typedef ti_sysbios_family_arm_v8a_Mmu_MapAttrs CT__ti_sysbios_family_arm_v8a_Mmu_defaultMapAttrs;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_defaultMapAttrs ti_sysbios_family_arm_v8a_Mmu_defaultMapAttrs__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_defaultMapAttrs__CR
#define ti_sysbios_family_arm_v8a_Mmu_defaultMapAttrs (*((CT__ti_sysbios_family_arm_v8a_Mmu_defaultMapAttrs*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_defaultMapAttrs__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_defaultMapAttrs (ti_sysbios_family_arm_v8a_Mmu_defaultMapAttrs__C)
#endif

/* enableMMU */
typedef xdc_Bool CT__ti_sysbios_family_arm_v8a_Mmu_enableMMU;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_enableMMU ti_sysbios_family_arm_v8a_Mmu_enableMMU__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_enableMMU__CR
#define ti_sysbios_family_arm_v8a_Mmu_enableMMU (*((CT__ti_sysbios_family_arm_v8a_Mmu_enableMMU*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_enableMMU__C_offset)))
#else
#ifdef ti_sysbios_family_arm_v8a_Mmu_enableMMU__D
#define ti_sysbios_family_arm_v8a_Mmu_enableMMU (ti_sysbios_family_arm_v8a_Mmu_enableMMU__D)
#else
#define ti_sysbios_family_arm_v8a_Mmu_enableMMU (ti_sysbios_family_arm_v8a_Mmu_enableMMU__C)
#endif
#endif

/* granuleSize */
typedef ti_sysbios_family_arm_v8a_Mmu_GranuleSize CT__ti_sysbios_family_arm_v8a_Mmu_granuleSize;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_granuleSize ti_sysbios_family_arm_v8a_Mmu_granuleSize__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_granuleSize__CR
#define ti_sysbios_family_arm_v8a_Mmu_granuleSize (*((CT__ti_sysbios_family_arm_v8a_Mmu_granuleSize*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_granuleSize__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_granuleSize (ti_sysbios_family_arm_v8a_Mmu_granuleSize__C)
#endif

/* MAIR0 */
typedef xdc_UInt8 CT__ti_sysbios_family_arm_v8a_Mmu_MAIR0;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_MAIR0 ti_sysbios_family_arm_v8a_Mmu_MAIR0__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_MAIR0__CR
#define ti_sysbios_family_arm_v8a_Mmu_MAIR0 (*((CT__ti_sysbios_family_arm_v8a_Mmu_MAIR0*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_MAIR0__C_offset)))
#else
#ifdef ti_sysbios_family_arm_v8a_Mmu_MAIR0__D
#define ti_sysbios_family_arm_v8a_Mmu_MAIR0 (ti_sysbios_family_arm_v8a_Mmu_MAIR0__D)
#else
#define ti_sysbios_family_arm_v8a_Mmu_MAIR0 (ti_sysbios_family_arm_v8a_Mmu_MAIR0__C)
#endif
#endif

/* MAIR1 */
typedef xdc_UInt8 CT__ti_sysbios_family_arm_v8a_Mmu_MAIR1;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_MAIR1 ti_sysbios_family_arm_v8a_Mmu_MAIR1__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_MAIR1__CR
#define ti_sysbios_family_arm_v8a_Mmu_MAIR1 (*((CT__ti_sysbios_family_arm_v8a_Mmu_MAIR1*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_MAIR1__C_offset)))
#else
#ifdef ti_sysbios_family_arm_v8a_Mmu_MAIR1__D
#define ti_sysbios_family_arm_v8a_Mmu_MAIR1 (ti_sysbios_family_arm_v8a_Mmu_MAIR1__D)
#else
#define ti_sysbios_family_arm_v8a_Mmu_MAIR1 (ti_sysbios_family_arm_v8a_Mmu_MAIR1__C)
#endif
#endif

/* MAIR2 */
typedef xdc_UInt8 CT__ti_sysbios_family_arm_v8a_Mmu_MAIR2;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_MAIR2 ti_sysbios_family_arm_v8a_Mmu_MAIR2__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_MAIR2__CR
#define ti_sysbios_family_arm_v8a_Mmu_MAIR2 (*((CT__ti_sysbios_family_arm_v8a_Mmu_MAIR2*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_MAIR2__C_offset)))
#else
#ifdef ti_sysbios_family_arm_v8a_Mmu_MAIR2__D
#define ti_sysbios_family_arm_v8a_Mmu_MAIR2 (ti_sysbios_family_arm_v8a_Mmu_MAIR2__D)
#else
#define ti_sysbios_family_arm_v8a_Mmu_MAIR2 (ti_sysbios_family_arm_v8a_Mmu_MAIR2__C)
#endif
#endif

/* MAIR3 */
typedef xdc_UInt8 CT__ti_sysbios_family_arm_v8a_Mmu_MAIR3;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_MAIR3 ti_sysbios_family_arm_v8a_Mmu_MAIR3__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_MAIR3__CR
#define ti_sysbios_family_arm_v8a_Mmu_MAIR3 (*((CT__ti_sysbios_family_arm_v8a_Mmu_MAIR3*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_MAIR3__C_offset)))
#else
#ifdef ti_sysbios_family_arm_v8a_Mmu_MAIR3__D
#define ti_sysbios_family_arm_v8a_Mmu_MAIR3 (ti_sysbios_family_arm_v8a_Mmu_MAIR3__D)
#else
#define ti_sysbios_family_arm_v8a_Mmu_MAIR3 (ti_sysbios_family_arm_v8a_Mmu_MAIR3__C)
#endif
#endif

/* MAIR4 */
typedef xdc_UInt8 CT__ti_sysbios_family_arm_v8a_Mmu_MAIR4;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_MAIR4 ti_sysbios_family_arm_v8a_Mmu_MAIR4__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_MAIR4__CR
#define ti_sysbios_family_arm_v8a_Mmu_MAIR4 (*((CT__ti_sysbios_family_arm_v8a_Mmu_MAIR4*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_MAIR4__C_offset)))
#else
#ifdef ti_sysbios_family_arm_v8a_Mmu_MAIR4__D
#define ti_sysbios_family_arm_v8a_Mmu_MAIR4 (ti_sysbios_family_arm_v8a_Mmu_MAIR4__D)
#else
#define ti_sysbios_family_arm_v8a_Mmu_MAIR4 (ti_sysbios_family_arm_v8a_Mmu_MAIR4__C)
#endif
#endif

/* MAIR5 */
typedef xdc_UInt8 CT__ti_sysbios_family_arm_v8a_Mmu_MAIR5;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_MAIR5 ti_sysbios_family_arm_v8a_Mmu_MAIR5__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_MAIR5__CR
#define ti_sysbios_family_arm_v8a_Mmu_MAIR5 (*((CT__ti_sysbios_family_arm_v8a_Mmu_MAIR5*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_MAIR5__C_offset)))
#else
#ifdef ti_sysbios_family_arm_v8a_Mmu_MAIR5__D
#define ti_sysbios_family_arm_v8a_Mmu_MAIR5 (ti_sysbios_family_arm_v8a_Mmu_MAIR5__D)
#else
#define ti_sysbios_family_arm_v8a_Mmu_MAIR5 (ti_sysbios_family_arm_v8a_Mmu_MAIR5__C)
#endif
#endif

/* MAIR6 */
typedef xdc_UInt8 CT__ti_sysbios_family_arm_v8a_Mmu_MAIR6;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_MAIR6 ti_sysbios_family_arm_v8a_Mmu_MAIR6__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_MAIR6__CR
#define ti_sysbios_family_arm_v8a_Mmu_MAIR6 (*((CT__ti_sysbios_family_arm_v8a_Mmu_MAIR6*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_MAIR6__C_offset)))
#else
#ifdef ti_sysbios_family_arm_v8a_Mmu_MAIR6__D
#define ti_sysbios_family_arm_v8a_Mmu_MAIR6 (ti_sysbios_family_arm_v8a_Mmu_MAIR6__D)
#else
#define ti_sysbios_family_arm_v8a_Mmu_MAIR6 (ti_sysbios_family_arm_v8a_Mmu_MAIR6__C)
#endif
#endif

/* MAIR7 */
typedef xdc_UInt8 CT__ti_sysbios_family_arm_v8a_Mmu_MAIR7;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_MAIR7 ti_sysbios_family_arm_v8a_Mmu_MAIR7__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_MAIR7__CR
#define ti_sysbios_family_arm_v8a_Mmu_MAIR7 (*((CT__ti_sysbios_family_arm_v8a_Mmu_MAIR7*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_MAIR7__C_offset)))
#else
#ifdef ti_sysbios_family_arm_v8a_Mmu_MAIR7__D
#define ti_sysbios_family_arm_v8a_Mmu_MAIR7 (ti_sysbios_family_arm_v8a_Mmu_MAIR7__D)
#else
#define ti_sysbios_family_arm_v8a_Mmu_MAIR7 (ti_sysbios_family_arm_v8a_Mmu_MAIR7__C)
#endif
#endif

/* initFunc */
typedef ti_sysbios_family_arm_v8a_Mmu_InitFuncPtr CT__ti_sysbios_family_arm_v8a_Mmu_initFunc;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_initFunc ti_sysbios_family_arm_v8a_Mmu_initFunc__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_initFunc__CR
#define ti_sysbios_family_arm_v8a_Mmu_initFunc (*((CT__ti_sysbios_family_arm_v8a_Mmu_initFunc*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_initFunc__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_initFunc (ti_sysbios_family_arm_v8a_Mmu_initFunc__C)
#endif

/* tableArrayLen */
typedef xdc_UInt CT__ti_sysbios_family_arm_v8a_Mmu_tableArrayLen;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_tableArrayLen ti_sysbios_family_arm_v8a_Mmu_tableArrayLen__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_tableArrayLen__CR
#define ti_sysbios_family_arm_v8a_Mmu_tableArrayLen (*((CT__ti_sysbios_family_arm_v8a_Mmu_tableArrayLen*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_tableArrayLen__C_offset)))
#else
#ifdef ti_sysbios_family_arm_v8a_Mmu_tableArrayLen__D
#define ti_sysbios_family_arm_v8a_Mmu_tableArrayLen (ti_sysbios_family_arm_v8a_Mmu_tableArrayLen__D)
#else
#define ti_sysbios_family_arm_v8a_Mmu_tableArrayLen (ti_sysbios_family_arm_v8a_Mmu_tableArrayLen__C)
#endif
#endif

/* configInfo */
typedef ti_sysbios_family_arm_v8a_Mmu_ConfigInfo CT__ti_sysbios_family_arm_v8a_Mmu_configInfo;
__extern __FAR__ const CT__ti_sysbios_family_arm_v8a_Mmu_configInfo ti_sysbios_family_arm_v8a_Mmu_configInfo__C;
#ifdef ti_sysbios_family_arm_v8a_Mmu_configInfo__CR
#define ti_sysbios_family_arm_v8a_Mmu_configInfo (*((CT__ti_sysbios_family_arm_v8a_Mmu_configInfo*)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_configInfo__C_offset)))
#else
#define ti_sysbios_family_arm_v8a_Mmu_configInfo (ti_sysbios_family_arm_v8a_Mmu_configInfo__C)
#endif


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sysbios_family_arm_v8a_Mmu_Module_startup( state ) (-1)

/* Module__startupDone__S */
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_Module__startupDone__S, "ti_sysbios_family_arm_v8a_Mmu_Module__startupDone__S")
__extern xdc_Bool ti_sysbios_family_arm_v8a_Mmu_Module__startupDone__S( void );

/* enable__E */
#define ti_sysbios_family_arm_v8a_Mmu_enable ti_sysbios_family_arm_v8a_Mmu_enable__E
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_enable__E, "ti_sysbios_family_arm_v8a_Mmu_enable")
__extern xdc_Void ti_sysbios_family_arm_v8a_Mmu_enable__E( void );

/* initMapAttrs__E */
#define ti_sysbios_family_arm_v8a_Mmu_initMapAttrs ti_sysbios_family_arm_v8a_Mmu_initMapAttrs__E
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_initMapAttrs__E, "ti_sysbios_family_arm_v8a_Mmu_initMapAttrs")
__extern xdc_Void ti_sysbios_family_arm_v8a_Mmu_initMapAttrs__E( ti_sysbios_family_arm_v8a_Mmu_MapAttrs *descAttrs );

/* isEnabled__E */
#define ti_sysbios_family_arm_v8a_Mmu_isEnabled ti_sysbios_family_arm_v8a_Mmu_isEnabled__E
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_isEnabled__E, "ti_sysbios_family_arm_v8a_Mmu_isEnabled")
__extern xdc_Bool ti_sysbios_family_arm_v8a_Mmu_isEnabled__E( void );

/* map__E */
#define ti_sysbios_family_arm_v8a_Mmu_map ti_sysbios_family_arm_v8a_Mmu_map__E
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_map__E, "ti_sysbios_family_arm_v8a_Mmu_map")
__extern xdc_Bool ti_sysbios_family_arm_v8a_Mmu_map__E( xdc_UInt64 vaddr, xdc_UInt64 paddr, xdc_SizeT size, ti_sysbios_family_arm_v8a_Mmu_MapAttrs *attrs );

/* setMAIR__E */
#define ti_sysbios_family_arm_v8a_Mmu_setMAIR ti_sysbios_family_arm_v8a_Mmu_setMAIR__E
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_setMAIR__E, "ti_sysbios_family_arm_v8a_Mmu_setMAIR")
__extern xdc_Void ti_sysbios_family_arm_v8a_Mmu_setMAIR__E( xdc_UInt8 attrIndx, xdc_UInt8 attr );

/* startup__E */
#define ti_sysbios_family_arm_v8a_Mmu_startup ti_sysbios_family_arm_v8a_Mmu_startup__E
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_startup__E, "ti_sysbios_family_arm_v8a_Mmu_startup")
__extern xdc_Void ti_sysbios_family_arm_v8a_Mmu_startup__E( void );

/* tlbInvAll__E */
#define ti_sysbios_family_arm_v8a_Mmu_tlbInvAll ti_sysbios_family_arm_v8a_Mmu_tlbInvAll__E
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_tlbInvAll__E, "ti_sysbios_family_arm_v8a_Mmu_tlbInvAll")
__extern xdc_Void ti_sysbios_family_arm_v8a_Mmu_tlbInvAll__E( void );

/* disable__I */
#define ti_sysbios_family_arm_v8a_Mmu_disable ti_sysbios_family_arm_v8a_Mmu_disable__I
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_disable__I, "ti_sysbios_family_arm_v8a_Mmu_disable")
__extern xdc_Void ti_sysbios_family_arm_v8a_Mmu_disable__I( void );

/* disableI__I */
#define ti_sysbios_family_arm_v8a_Mmu_disableI ti_sysbios_family_arm_v8a_Mmu_disableI__I
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_disableI__I, "ti_sysbios_family_arm_v8a_Mmu_disableI")
__extern xdc_Void ti_sysbios_family_arm_v8a_Mmu_disableI__I( void );

/* enableI__I */
#define ti_sysbios_family_arm_v8a_Mmu_enableI ti_sysbios_family_arm_v8a_Mmu_enableI__I
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_enableI__I, "ti_sysbios_family_arm_v8a_Mmu_enableI")
__extern xdc_Void ti_sysbios_family_arm_v8a_Mmu_enableI__I( void );

/* addBlockEntry__I */
#define ti_sysbios_family_arm_v8a_Mmu_addBlockEntry ti_sysbios_family_arm_v8a_Mmu_addBlockEntry__I
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_addBlockEntry__I, "ti_sysbios_family_arm_v8a_Mmu_addBlockEntry")
__extern xdc_Void ti_sysbios_family_arm_v8a_Mmu_addBlockEntry__I( xdc_UInt8 level, xdc_UInt64 *tablePtr, xdc_UInt16 tableIdx, xdc_UInt64 paddr, ti_sysbios_family_arm_v8a_Mmu_MapAttrs *attrs );

/* addTableEntry__I */
#define ti_sysbios_family_arm_v8a_Mmu_addTableEntry ti_sysbios_family_arm_v8a_Mmu_addTableEntry__I
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_addTableEntry__I, "ti_sysbios_family_arm_v8a_Mmu_addTableEntry")
__extern xdc_UInt64 *ti_sysbios_family_arm_v8a_Mmu_addTableEntry__I( xdc_UInt64 *tablePtr, xdc_UInt16 tableIdx, ti_sysbios_family_arm_v8a_Mmu_MapAttrs *attrs );

/* allocTable__I */
#define ti_sysbios_family_arm_v8a_Mmu_allocTable ti_sysbios_family_arm_v8a_Mmu_allocTable__I
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_allocTable__I, "ti_sysbios_family_arm_v8a_Mmu_allocTable")
__extern xdc_UInt64 *ti_sysbios_family_arm_v8a_Mmu_allocTable__I( void );

/* freeTable__I */
#define ti_sysbios_family_arm_v8a_Mmu_freeTable ti_sysbios_family_arm_v8a_Mmu_freeTable__I
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_freeTable__I, "ti_sysbios_family_arm_v8a_Mmu_freeTable")
__extern xdc_Void ti_sysbios_family_arm_v8a_Mmu_freeTable__I( xdc_UInt64 *table );

/* init__I */
#define ti_sysbios_family_arm_v8a_Mmu_init ti_sysbios_family_arm_v8a_Mmu_init__I
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_init__I, "ti_sysbios_family_arm_v8a_Mmu_init")
__extern xdc_Void ti_sysbios_family_arm_v8a_Mmu_init__I( xdc_Ptr tableAddr );

/* readBlockEntry__I */
#define ti_sysbios_family_arm_v8a_Mmu_readBlockEntry ti_sysbios_family_arm_v8a_Mmu_readBlockEntry__I
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_readBlockEntry__I, "ti_sysbios_family_arm_v8a_Mmu_readBlockEntry")
__extern xdc_Void ti_sysbios_family_arm_v8a_Mmu_readBlockEntry__I( xdc_UInt8 level, xdc_UInt64 *tablePtr, xdc_UInt16 tableIdx, xdc_UInt64 *paddr, ti_sysbios_family_arm_v8a_Mmu_MapAttrs *attrs );

/* setMAIRAsm__I */
#define ti_sysbios_family_arm_v8a_Mmu_setMAIRAsm ti_sysbios_family_arm_v8a_Mmu_setMAIRAsm__I
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_setMAIRAsm__I, "ti_sysbios_family_arm_v8a_Mmu_setMAIRAsm")
__extern xdc_Void ti_sysbios_family_arm_v8a_Mmu_setMAIRAsm__I( xdc_UInt8 attrIndx, xdc_UInt8 attr );

/* tableWalk__I */
#define ti_sysbios_family_arm_v8a_Mmu_tableWalk ti_sysbios_family_arm_v8a_Mmu_tableWalk__I
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_tableWalk__I, "ti_sysbios_family_arm_v8a_Mmu_tableWalk")
__extern xdc_Bool ti_sysbios_family_arm_v8a_Mmu_tableWalk__I( xdc_UInt8 level, xdc_UInt64 *tablePtr, xdc_UInt64 *vaddr, xdc_UInt64 *paddr, xdc_SizeT *size, ti_sysbios_family_arm_v8a_Mmu_MapAttrs *attrs );

/* setTCR__I */
#define ti_sysbios_family_arm_v8a_Mmu_setTCR ti_sysbios_family_arm_v8a_Mmu_setTCR__I
xdc__CODESECT(ti_sysbios_family_arm_v8a_Mmu_setTCR__I, "ti_sysbios_family_arm_v8a_Mmu_setTCR")
__extern xdc_Void ti_sysbios_family_arm_v8a_Mmu_setTCR__I( xdc_UInt64 regVal );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sysbios_family_arm_v8a_Mmu_Module_startupDone() ti_sysbios_family_arm_v8a_Mmu_Module__startupDone__S()

/* Object_heap */
#define ti_sysbios_family_arm_v8a_Mmu_Object_heap() ti_sysbios_family_arm_v8a_Mmu_Object__heap__C

/* Module_heap */
#define ti_sysbios_family_arm_v8a_Mmu_Module_heap() ti_sysbios_family_arm_v8a_Mmu_Object__heap__C

/* Module_id */
static inline CT__ti_sysbios_family_arm_v8a_Mmu_Module__id ti_sysbios_family_arm_v8a_Mmu_Module_id(void);
static inline CT__ti_sysbios_family_arm_v8a_Mmu_Module__id ti_sysbios_family_arm_v8a_Mmu_Module_id( void ) 
{
    return ti_sysbios_family_arm_v8a_Mmu_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sysbios_family_arm_v8a_Mmu_Module_hasMask(void);
static inline xdc_Bool ti_sysbios_family_arm_v8a_Mmu_Module_hasMask(void)
{
    return (xdc_Bool)(ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask__C != (CT__ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask)NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_sysbios_family_arm_v8a_Mmu_Module_getMask(void);
static inline xdc_Bits16 ti_sysbios_family_arm_v8a_Mmu_Module_getMask(void)
{
    return (ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask__C != (CT__ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask)NULL) ? *ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_sysbios_family_arm_v8a_Mmu_Module_setMask(xdc_Bits16 mask);
static inline xdc_Void ti_sysbios_family_arm_v8a_Mmu_Module_setMask(xdc_Bits16 mask)
{
    if (ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask__C != (CT__ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask)NULL) {
        *ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask__C = mask;
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sysbios_family_arm_v8a_Mmu__top__
#undef __nested__
#endif

#endif /* ti_sysbios_family_arm_v8a_Mmu__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sysbios_family_arm_v8a_Mmu__internalaccess))

#ifndef ti_sysbios_family_arm_v8a_Mmu__include_state
#define ti_sysbios_family_arm_v8a_Mmu__include_state

/* Module_State */
struct ti_sysbios_family_arm_v8a_Mmu_Module_State {
};

/* Module__state__V */
#ifndef ti_sysbios_family_arm_v8a_Mmu_Module__state__VR
extern struct ti_sysbios_family_arm_v8a_Mmu_Module_State__ ti_sysbios_family_arm_v8a_Mmu_Module__state__V;
#else
#define ti_sysbios_family_arm_v8a_Mmu_Module__state__V (*((struct ti_sysbios_family_arm_v8a_Mmu_Module_State__*)(xdcRomStatePtr + ti_sysbios_family_arm_v8a_Mmu_Module__state__V_offset)))
#endif

#endif /* ti_sysbios_family_arm_v8a_Mmu__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sysbios_family_arm_v8a_Mmu__nolocalnames)

#ifndef ti_sysbios_family_arm_v8a_Mmu__localnames__done
#define ti_sysbios_family_arm_v8a_Mmu__localnames__done

/* module prefix */
#define Mmu_PA_MAX_WIDTH ti_sysbios_family_arm_v8a_Mmu_PA_MAX_WIDTH
#define Mmu_PA_SIZE_ENCODING ti_sysbios_family_arm_v8a_Mmu_PA_SIZE_ENCODING
#define Mmu_AttrIndx ti_sysbios_family_arm_v8a_Mmu_AttrIndx
#define Mmu_DescriptorType ti_sysbios_family_arm_v8a_Mmu_DescriptorType
#define Mmu_GranuleSize ti_sysbios_family_arm_v8a_Mmu_GranuleSize
#define Mmu_Shareable ti_sysbios_family_arm_v8a_Mmu_Shareable
#define Mmu_AccessPerm ti_sysbios_family_arm_v8a_Mmu_AccessPerm
#define Mmu_InitFuncPtr ti_sysbios_family_arm_v8a_Mmu_InitFuncPtr
#define Mmu_MapAttrs ti_sysbios_family_arm_v8a_Mmu_MapAttrs
#define Mmu_ConfigInfo ti_sysbios_family_arm_v8a_Mmu_ConfigInfo
#define Mmu_Module_State ti_sysbios_family_arm_v8a_Mmu_Module_State
#define Mmu_AttrIndx_MAIR0 ti_sysbios_family_arm_v8a_Mmu_AttrIndx_MAIR0
#define Mmu_AttrIndx_MAIR1 ti_sysbios_family_arm_v8a_Mmu_AttrIndx_MAIR1
#define Mmu_AttrIndx_MAIR2 ti_sysbios_family_arm_v8a_Mmu_AttrIndx_MAIR2
#define Mmu_AttrIndx_MAIR3 ti_sysbios_family_arm_v8a_Mmu_AttrIndx_MAIR3
#define Mmu_AttrIndx_MAIR4 ti_sysbios_family_arm_v8a_Mmu_AttrIndx_MAIR4
#define Mmu_AttrIndx_MAIR5 ti_sysbios_family_arm_v8a_Mmu_AttrIndx_MAIR5
#define Mmu_AttrIndx_MAIR6 ti_sysbios_family_arm_v8a_Mmu_AttrIndx_MAIR6
#define Mmu_AttrIndx_MAIR7 ti_sysbios_family_arm_v8a_Mmu_AttrIndx_MAIR7
#define Mmu_DescriptorType_INVALID0 ti_sysbios_family_arm_v8a_Mmu_DescriptorType_INVALID0
#define Mmu_DescriptorType_BLOCK ti_sysbios_family_arm_v8a_Mmu_DescriptorType_BLOCK
#define Mmu_DescriptorType_INVALID1 ti_sysbios_family_arm_v8a_Mmu_DescriptorType_INVALID1
#define Mmu_DescriptorType_TABLE ti_sysbios_family_arm_v8a_Mmu_DescriptorType_TABLE
#define Mmu_GranuleSize_4KB ti_sysbios_family_arm_v8a_Mmu_GranuleSize_4KB
#define Mmu_GranuleSize_16KB ti_sysbios_family_arm_v8a_Mmu_GranuleSize_16KB
#define Mmu_GranuleSize_64KB ti_sysbios_family_arm_v8a_Mmu_GranuleSize_64KB
#define Mmu_Shareable_NONE ti_sysbios_family_arm_v8a_Mmu_Shareable_NONE
#define Mmu_Shareable_OUTER ti_sysbios_family_arm_v8a_Mmu_Shareable_OUTER
#define Mmu_Shareable_INNER ti_sysbios_family_arm_v8a_Mmu_Shareable_INNER
#define Mmu_AccessPerm_PRIV_RW_USER_NONE ti_sysbios_family_arm_v8a_Mmu_AccessPerm_PRIV_RW_USER_NONE
#define Mmu_AccessPerm_PRIV_RW_USER_RW ti_sysbios_family_arm_v8a_Mmu_AccessPerm_PRIV_RW_USER_RW
#define Mmu_AccessPerm_PRIV_RO_USER_NONE ti_sysbios_family_arm_v8a_Mmu_AccessPerm_PRIV_RO_USER_NONE
#define Mmu_AccessPerm_PRIV_RO_USER_RO ti_sysbios_family_arm_v8a_Mmu_AccessPerm_PRIV_RO_USER_RO
#define Mmu_A_nullPointer ti_sysbios_family_arm_v8a_Mmu_A_nullPointer
#define Mmu_A_vaddrOutOfRange ti_sysbios_family_arm_v8a_Mmu_A_vaddrOutOfRange
#define Mmu_A_paddrOutOfRange ti_sysbios_family_arm_v8a_Mmu_A_paddrOutOfRange
#define Mmu_A_unalignedVaddr ti_sysbios_family_arm_v8a_Mmu_A_unalignedVaddr
#define Mmu_A_unalignedPaddr ti_sysbios_family_arm_v8a_Mmu_A_unalignedPaddr
#define Mmu_A_unalignedSize ti_sysbios_family_arm_v8a_Mmu_A_unalignedSize
#define Mmu_defaultMapAttrs ti_sysbios_family_arm_v8a_Mmu_defaultMapAttrs
#define Mmu_enableMMU ti_sysbios_family_arm_v8a_Mmu_enableMMU
#define Mmu_granuleSize ti_sysbios_family_arm_v8a_Mmu_granuleSize
#define Mmu_MAIR0 ti_sysbios_family_arm_v8a_Mmu_MAIR0
#define Mmu_MAIR1 ti_sysbios_family_arm_v8a_Mmu_MAIR1
#define Mmu_MAIR2 ti_sysbios_family_arm_v8a_Mmu_MAIR2
#define Mmu_MAIR3 ti_sysbios_family_arm_v8a_Mmu_MAIR3
#define Mmu_MAIR4 ti_sysbios_family_arm_v8a_Mmu_MAIR4
#define Mmu_MAIR5 ti_sysbios_family_arm_v8a_Mmu_MAIR5
#define Mmu_MAIR6 ti_sysbios_family_arm_v8a_Mmu_MAIR6
#define Mmu_MAIR7 ti_sysbios_family_arm_v8a_Mmu_MAIR7
#define Mmu_initFunc ti_sysbios_family_arm_v8a_Mmu_initFunc
#define Mmu_tableArrayLen ti_sysbios_family_arm_v8a_Mmu_tableArrayLen
#define Mmu_configInfo ti_sysbios_family_arm_v8a_Mmu_configInfo
#define Mmu_enable ti_sysbios_family_arm_v8a_Mmu_enable
#define Mmu_initMapAttrs ti_sysbios_family_arm_v8a_Mmu_initMapAttrs
#define Mmu_isEnabled ti_sysbios_family_arm_v8a_Mmu_isEnabled
#define Mmu_map ti_sysbios_family_arm_v8a_Mmu_map
#define Mmu_setMAIR ti_sysbios_family_arm_v8a_Mmu_setMAIR
#define Mmu_startup ti_sysbios_family_arm_v8a_Mmu_startup
#define Mmu_tlbInvAll ti_sysbios_family_arm_v8a_Mmu_tlbInvAll
#define Mmu_Module_name ti_sysbios_family_arm_v8a_Mmu_Module_name
#define Mmu_Module_id ti_sysbios_family_arm_v8a_Mmu_Module_id
#define Mmu_Module_startup ti_sysbios_family_arm_v8a_Mmu_Module_startup
#define Mmu_Module_startupDone ti_sysbios_family_arm_v8a_Mmu_Module_startupDone
#define Mmu_Module_hasMask ti_sysbios_family_arm_v8a_Mmu_Module_hasMask
#define Mmu_Module_getMask ti_sysbios_family_arm_v8a_Mmu_Module_getMask
#define Mmu_Module_setMask ti_sysbios_family_arm_v8a_Mmu_Module_setMask
#define Mmu_Object_heap ti_sysbios_family_arm_v8a_Mmu_Object_heap
#define Mmu_Module_heap ti_sysbios_family_arm_v8a_Mmu_Module_heap

#endif /* ti_sysbios_family_arm_v8a_Mmu__localnames__done */
#endif

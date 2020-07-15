/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-E00
 */

#ifndef ti_sysbios_family_arm_v8a_Mmu__INTERNAL__
#define ti_sysbios_family_arm_v8a_Mmu__INTERNAL__

#ifndef ti_sysbios_family_arm_v8a_Mmu__internalaccess
#define ti_sysbios_family_arm_v8a_Mmu__internalaccess
#endif

#include <ti/sysbios/family/arm/v8a/Mmu.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* enable */
#undef ti_sysbios_family_arm_v8a_Mmu_enable
#define ti_sysbios_family_arm_v8a_Mmu_enable ti_sysbios_family_arm_v8a_Mmu_enable__E

/* initMapAttrs */
#undef ti_sysbios_family_arm_v8a_Mmu_initMapAttrs
#define ti_sysbios_family_arm_v8a_Mmu_initMapAttrs ti_sysbios_family_arm_v8a_Mmu_initMapAttrs__E

/* isEnabled */
#undef ti_sysbios_family_arm_v8a_Mmu_isEnabled
#define ti_sysbios_family_arm_v8a_Mmu_isEnabled ti_sysbios_family_arm_v8a_Mmu_isEnabled__E

/* map */
#undef ti_sysbios_family_arm_v8a_Mmu_map
#define ti_sysbios_family_arm_v8a_Mmu_map ti_sysbios_family_arm_v8a_Mmu_map__E

/* setMAIR */
#undef ti_sysbios_family_arm_v8a_Mmu_setMAIR
#define ti_sysbios_family_arm_v8a_Mmu_setMAIR ti_sysbios_family_arm_v8a_Mmu_setMAIR__E

/* startup */
#undef ti_sysbios_family_arm_v8a_Mmu_startup
#define ti_sysbios_family_arm_v8a_Mmu_startup ti_sysbios_family_arm_v8a_Mmu_startup__E

/* tlbInvAll */
#undef ti_sysbios_family_arm_v8a_Mmu_tlbInvAll
#define ti_sysbios_family_arm_v8a_Mmu_tlbInvAll ti_sysbios_family_arm_v8a_Mmu_tlbInvAll__E

/* disable */
#define Mmu_disable ti_sysbios_family_arm_v8a_Mmu_disable__I

/* disableI */
#define Mmu_disableI ti_sysbios_family_arm_v8a_Mmu_disableI__I

/* enableI */
#define Mmu_enableI ti_sysbios_family_arm_v8a_Mmu_enableI__I

/* addBlockEntry */
#define Mmu_addBlockEntry ti_sysbios_family_arm_v8a_Mmu_addBlockEntry__I

/* addTableEntry */
#define Mmu_addTableEntry ti_sysbios_family_arm_v8a_Mmu_addTableEntry__I

/* allocTable */
#define Mmu_allocTable ti_sysbios_family_arm_v8a_Mmu_allocTable__I

/* freeTable */
#define Mmu_freeTable ti_sysbios_family_arm_v8a_Mmu_freeTable__I

/* init */
#define Mmu_init ti_sysbios_family_arm_v8a_Mmu_init__I

/* readBlockEntry */
#define Mmu_readBlockEntry ti_sysbios_family_arm_v8a_Mmu_readBlockEntry__I

/* setMAIRAsm */
#define Mmu_setMAIRAsm ti_sysbios_family_arm_v8a_Mmu_setMAIRAsm__I

/* tableWalk */
#define Mmu_tableWalk ti_sysbios_family_arm_v8a_Mmu_tableWalk__I

/* setTCR */
#define Mmu_setTCR ti_sysbios_family_arm_v8a_Mmu_setTCR__I

/* Module_startup */
#undef ti_sysbios_family_arm_v8a_Mmu_Module_startup
#define ti_sysbios_family_arm_v8a_Mmu_Module_startup ti_sysbios_family_arm_v8a_Mmu_Module_startup__E

/* Instance_init */
#undef ti_sysbios_family_arm_v8a_Mmu_Instance_init
#define ti_sysbios_family_arm_v8a_Mmu_Instance_init ti_sysbios_family_arm_v8a_Mmu_Instance_init__E

/* Instance_finalize */
#undef ti_sysbios_family_arm_v8a_Mmu_Instance_finalize
#define ti_sysbios_family_arm_v8a_Mmu_Instance_finalize ti_sysbios_family_arm_v8a_Mmu_Instance_finalize__E

/* module */
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__state__VR
#define Mmu_module ((ti_sysbios_family_arm_v8a_Mmu_Module_State *)(xdcRomStatePtr + ti_sysbios_family_arm_v8a_Mmu_Module__state__V_offset))
#define module ((ti_sysbios_family_arm_v8a_Mmu_Module_State *)(xdcRomStatePtr + ti_sysbios_family_arm_v8a_Mmu_Module__state__V_offset))
#else
#define Mmu_module ((ti_sysbios_family_arm_v8a_Mmu_Module_State *)(xdc__MODOBJADDR__(ti_sysbios_family_arm_v8a_Mmu_Module__state__V)))
#if !defined(__cplusplus) ||!defined(ti_sysbios_family_arm_v8a_Mmu__cplusplus)
#define module ((ti_sysbios_family_arm_v8a_Mmu_Module_State *)(xdc__MODOBJADDR__(ti_sysbios_family_arm_v8a_Mmu_Module__state__V)))
#endif
#endif

/* per-module runtime symbols */
#undef Module__MID
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__id__CR
#define Module__MID (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__id *)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__id__C_offset)))
#else
#define Module__MID ti_sysbios_family_arm_v8a_Mmu_Module__id__C
#endif

#undef Module__DGSINCL
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__diagsIncluded__CR
#define Module__DGSINCL (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__diagsIncluded *)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__diagsIncluded__C_offset)))
#else
#define Module__DGSINCL ti_sysbios_family_arm_v8a_Mmu_Module__diagsIncluded__C
#endif

#undef Module__DGSENAB
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__diagsEnabled__CR
#define Module__DGSENAB (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__diagsEnabled *)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__diagsEnabled__C_offset)))
#else
#define Module__DGSENAB ti_sysbios_family_arm_v8a_Mmu_Module__diagsEnabled__C
#endif

#undef Module__DGSMASK
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask__CR
#define Module__DGSMASK (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask *)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask__C_offset)))
#else
#define Module__DGSMASK ti_sysbios_family_arm_v8a_Mmu_Module__diagsMask__C
#endif

#undef Module__LOGDEF
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__loggerDefined__CR
#define Module__LOGDEF (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerDefined *)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__loggerDefined__C_offset)))
#else
#define Module__LOGDEF ti_sysbios_family_arm_v8a_Mmu_Module__loggerDefined__C
#endif

#undef Module__LOGOBJ
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__loggerObj__CR
#define Module__LOGOBJ ti_sysbios_family_arm_v8a_Mmu_Module__loggerObj__R
#define Module__LOGOBJ (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerObj *)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__loggerObj__C_offset)))
#else
#define Module__LOGOBJ ti_sysbios_family_arm_v8a_Mmu_Module__loggerObj__C
#endif

#undef Module__LOGFXN0
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn0__CR
#define Module__LOGFXN0 (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn0 *)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn0__C_offset)))
#else
#define Module__LOGFXN0 ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn0__C
#endif

#undef Module__LOGFXN1
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn1__CR
#define Module__LOGFXN1 (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn1 *)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn1__C_offset)))
#else
#define Module__LOGFXN1 ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn1__C
#endif

#undef Module__LOGFXN2
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn2__CR
#define Module__LOGFXN2 (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn2 *)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn2__C_offset)))
#else
#define Module__LOGFXN2 ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn2__C
#endif

#undef Module__LOGFXN4
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn4__CR
#define Module__LOGFXN4 (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn4 *)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn4__C_offset)))
#else
#define Module__LOGFXN4 ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn4__C
#endif

#undef Module__LOGFXN8
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn8__CR
#define Module__LOGFXN8 (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn8 *)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn8__C_offset)))
#else
#define Module__LOGFXN8 ti_sysbios_family_arm_v8a_Mmu_Module__loggerFxn8__C
#endif

#undef Module__G_OBJ
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__gateObj__CR
#define Module__G_OBJ (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__gateObj *)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__gateObj__C_offset)))
#else
#define Module__G_OBJ ti_sysbios_family_arm_v8a_Mmu_Module__gateObj__C
#endif

#undef Module__G_PRMS
#ifdef ti_sysbios_family_arm_v8a_Mmu_Module__gatePrms__CR
#define Module__G_PRMS (*((CT__ti_sysbios_family_arm_v8a_Mmu_Module__gatePrms *)(xdcRomConstPtr + ti_sysbios_family_arm_v8a_Mmu_Module__gatePrms__C_offset)))
#else
#define Module__G_PRMS ti_sysbios_family_arm_v8a_Mmu_Module__gatePrms__C
#endif

#undef Module__GP_create
#define Module__GP_create ti_sysbios_family_arm_v8a_Mmu_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sysbios_family_arm_v8a_Mmu_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sysbios_family_arm_v8a_Mmu_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sysbios_family_arm_v8a_Mmu_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sysbios_family_arm_v8a_Mmu_Module_GateProxy_query


#endif /* ti_sysbios_family_arm_v8a_Mmu__INTERNAL____ */

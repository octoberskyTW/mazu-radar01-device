/* 
 *  Copyright (c) 2008-2017 Texas Instruments Incorporated
 *  This program and the accompanying materials are made available under the
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * */

#ifndef xdc_runtime_Gate__prologue__include
#define xdc_runtime_Gate__prologue__include

#include <xdc/runtime/Main.h>

typedef xdc_runtime_Types_GateRef xdc_runtime_Gate_Ref;

#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_Main_Module__gateObj__C

#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_Main_Module__gatePrms__C

#undef Module__GP_create
#define Module__GP_create xdc_runtime_Main_Module_GateProxy_create

#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_Main_Module_GateProxy_delete

#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_Main_Module_GateProxy_enter

#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_Main_Module_GateProxy_leave

#undef Module__GP_query
#define Module__GP_query xdc_runtime_Main_Module_GateProxy_query

#endif
/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 7-31-2018 11:49:29; /db/ztree/library/trees/xdc/xdc-E10/src/packages/
 */


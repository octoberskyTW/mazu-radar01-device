/*
 * Copyright (c) 2017-2018, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== Pmu.xs ========
 */

var Hwi = null;
var Pmu = null;
var catalogName;

/*
 * ======== getAsmFiles ========
 * return the array of assembly language files associated
 * with targetName (ie Program.build.target.$name)
 */
function getAsmFiles(targetName)
{
    switch(targetName) {
        case "gnu.targets.arm.A53F":
            return (["Pmu_asm_gnu.sv8A"]);
            break;

        default:
            return (null);
	    break;
    }
}

if (xdc.om.$name == "cfg") {
    var deviceTable = {
        "ti.catalog.arm.cortexa53": {
            "SIMMAXWELL": {
                intNum  : 23
            }
        }
    };

    deviceTable["ti.catalog.arm.cortexa53"]["SIMFLEMING"] =
        deviceTable["ti.catalog.arm.cortexa53"]["SIMMAXWELL"];
    deviceTable["ti.catalog.arm.cortexa53"]["AM65X"] =
        deviceTable["ti.catalog.arm.cortexa53"]["SIMMAXWELL"];
}

/*
 *  ======== deviceSupportCheck ========
 *  Check validity of device
 */
function deviceSupportCheck()
{
    /* look for exact match first */
    for (deviceName in deviceTable[catalogName]) {
        if (deviceName == Program.cpu.deviceName) {
            return deviceName;
        }
    }

    /* now look for a wildcard match */
    for (deviceName in deviceTable[catalogName]) {
        if (Program.cpu.deviceName.match(deviceName)) {
            return deviceName;
        }
    }

    return null;
}

/*
 *  ======== module$meta$init ========
 */
function module$meta$init()
{
    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }

    this.$private.getAsmFiles = getAsmFiles;

    Pmu = this;

    catalogName = Program.cpu.catalogName;
    var device = deviceSupportCheck();

    if (device) {
        Pmu.intNum = deviceTable[catalogName][device].intNum;
    }
}

/*
 *  ======== module$use ========
 */
function module$use()
{
    Hwi = xdc.useModule("ti.sysbios.hal.Hwi");
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(mod, params)
{
    mod.numCounters = 0;
    mod.interruptFunc = Pmu.interruptFunc;

    if ((Pmu.intNum == (~0)) && (mod.interruptFunc != null)) {
        Pmu.$logError("PMU interrupt number not known. Cannot create a Hwi " +
                "and register callback interrupt function. Please specify " +
                "interrupt number in the *.cfg file using Pmu.intNum config " +
                "param.", Pmu);
    }

    if (mod.interruptFunc != null) {
        var hwiParams = new Hwi.Params();
        mod.hwiHandle = Hwi.create(Pmu.intNum, Pmu.interruptHandler, hwiParams);
    }
    else {
        mod.hwiHandle = null;
    }
}

/*
 *  ======== viewInitPmuInfo ========
 */
function viewInitPmuInfo(view)
{
    var Program = xdc.useModule('xdc.rov.Program');
    var Pmu = xdc.useModule('ti.sysbios.family.arm.v8a.Pmu');

    try {
        var pmuRawView = Program.scanRawView('ti.sysbios.family.arm.v8a.Pmu');
    }
    catch (e) {
        return null;
    }
    try {
        var modState = Program.fetchStruct(Pmu.Module_State$fetchDesc,
                             pmuRawView.modState.$addr);
    }
    catch (e) {
        return null;
    }

    var pmuView =
        Program.newViewStruct('ti.sysbios.family.arm.v8a.Pmu', 'Pmu Info');

    pmuView.numEventCounters = modState.numCounters;

    var pmuList = new Array();

    pmuList[0] = pmuView;

    view.elements = pmuList;

    return (view);
}

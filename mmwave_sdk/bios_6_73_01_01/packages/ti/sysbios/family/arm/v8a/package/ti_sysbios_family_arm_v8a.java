/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-E00
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class ti_sysbios_family_arm_v8a
{
    static final String VERS = "@(#) xdc-E00\n";

    static final Proto.Elm $$T_Bool = Proto.Elm.newBool();
    static final Proto.Elm $$T_Num = Proto.Elm.newNum();
    static final Proto.Elm $$T_Str = Proto.Elm.newStr();
    static final Proto.Elm $$T_Obj = Proto.Elm.newObj();

    static final Proto.Fxn $$T_Met = new Proto.Fxn(null, null, 0, -1, false);
    static final Proto.Map $$T_Map = new Proto.Map($$T_Obj);
    static final Proto.Arr $$T_Vec = new Proto.Arr($$T_Obj);

    static final XScriptO $$DEFAULT = Value.DEFAULT;
    static final Object $$UNDEF = Undefined.instance;

    static final Proto.Obj $$Package = (Proto.Obj)Global.get("$$Package");
    static final Proto.Obj $$Module = (Proto.Obj)Global.get("$$Module");
    static final Proto.Obj $$Instance = (Proto.Obj)Global.get("$$Instance");
    static final Proto.Obj $$Params = (Proto.Obj)Global.get("$$Params");

    static final Object $$objFldGet = Global.get("$$objFldGet");
    static final Object $$objFldSet = Global.get("$$objFldSet");
    static final Object $$proxyGet = Global.get("$$proxyGet");
    static final Object $$proxySet = Global.get("$$proxySet");
    static final Object $$delegGet = Global.get("$$delegGet");
    static final Object $$delegSet = Global.get("$$delegSet");

    Scriptable xdcO;
    Session ses;
    Value.Obj om;

    boolean isROV;
    boolean isCFG;

    Proto.Obj pkgP;
    Value.Obj pkgV;

    ArrayList<Object> imports = new ArrayList<Object>();
    ArrayList<Object> loggables = new ArrayList<Object>();
    ArrayList<Object> mcfgs = new ArrayList<Object>();
    ArrayList<Object> icfgs = new ArrayList<Object>();
    ArrayList<String> inherits = new ArrayList<String>();
    ArrayList<Object> proxies = new ArrayList<Object>();
    ArrayList<Object> sizes = new ArrayList<Object>();
    ArrayList<Object> tdefs = new ArrayList<Object>();

    void $$IMPORTS()
    {
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.interfaces");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.hal");
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.family.arm.gicv3");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sysbios.family.arm.v8a", new Value.Obj("ti.sysbios.family.arm.v8a", pkgP));
    }

    void Cache$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Cache.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sysbios.family.arm.v8a.Cache", new Value.Obj("ti.sysbios.family.arm.v8a.Cache", po));
        pkgV.bind("Cache", vo);
        // decls 
        om.bind("ti.sysbios.family.arm.v8a.Cache.Type", om.findStrict("ti.sysbios.interfaces.ICache.Type", "ti.sysbios.family.arm.v8a"));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Cache$$CacheInfoView", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v8a.Cache.CacheInfoView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Cache$$Module_State", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v8a.Cache.Module_State", new Proto.Str(spo, false));
    }

    void Core$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Core.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sysbios.family.arm.v8a.Core", new Value.Obj("ti.sysbios.family.arm.v8a.Core", po));
        pkgV.bind("Core", vo);
        // decls 
    }

    void Mmu$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Mmu.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sysbios.family.arm.v8a.Mmu", new Value.Obj("ti.sysbios.family.arm.v8a.Mmu", po));
        pkgV.bind("Mmu", vo);
        // decls 
        om.bind("ti.sysbios.family.arm.v8a.Mmu.AttrIndx", new Proto.Enm("ti.sysbios.family.arm.v8a.Mmu.AttrIndx"));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.DescriptorType", new Proto.Enm("ti.sysbios.family.arm.v8a.Mmu.DescriptorType"));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.GranuleSize", new Proto.Enm("ti.sysbios.family.arm.v8a.Mmu.GranuleSize"));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.Shareable", new Proto.Enm("ti.sysbios.family.arm.v8a.Mmu.Shareable"));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.AccessPerm", new Proto.Enm("ti.sysbios.family.arm.v8a.Mmu.AccessPerm"));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Mmu$$MapAttrs", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v8a.Mmu.MapAttrs", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Mmu$$ConfigInfo", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v8a.Mmu.ConfigInfo", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Mmu$$Module_State", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v8a.Mmu.Module_State", new Proto.Str(spo, false));
    }

    void Pmu$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Pmu.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sysbios.family.arm.v8a.Pmu", new Value.Obj("ti.sysbios.family.arm.v8a.Pmu", po));
        pkgV.bind("Pmu", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Pmu$$PmuInfoView", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v8a.Pmu.PmuInfoView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Pmu$$Module_State", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v8a.Pmu.Module_State", new Proto.Str(spo, false));
    }

    void TaskSupport$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.TaskSupport.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sysbios.family.arm.v8a.TaskSupport", new Value.Obj("ti.sysbios.family.arm.v8a.TaskSupport", po));
        pkgV.bind("TaskSupport", vo);
        // decls 
    }

    void Timer$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Timer.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sysbios.family.arm.v8a.Timer", new Value.Obj("ti.sysbios.family.arm.v8a.Timer", po));
        pkgV.bind("Timer", vo);
        // decls 
        om.bind("ti.sysbios.family.arm.v8a.Timer.StartMode", om.findStrict("ti.sysbios.interfaces.ITimer.StartMode", "ti.sysbios.family.arm.v8a"));
        om.bind("ti.sysbios.family.arm.v8a.Timer.RunMode", om.findStrict("ti.sysbios.interfaces.ITimer.RunMode", "ti.sysbios.family.arm.v8a"));
        om.bind("ti.sysbios.family.arm.v8a.Timer.Status", om.findStrict("ti.sysbios.interfaces.ITimer.Status", "ti.sysbios.family.arm.v8a"));
        om.bind("ti.sysbios.family.arm.v8a.Timer.PeriodType", om.findStrict("ti.sysbios.interfaces.ITimer.PeriodType", "ti.sysbios.family.arm.v8a"));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Timer$$BasicView", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v8a.Timer.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Timer$$ModuleView", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v8a.Timer.ModuleView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Timer$$Instance_State", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v8a.Timer.Instance_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Timer$$Module_State", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v8a.Timer.Module_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sysbios.family.arm.v8a.Timer.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Timer$$Object", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v8a.Timer.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.Timer$$Params", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v8a.Timer.Params", new Proto.Str(po, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.Handle", insP);
        if (isROV) {
            om.bind("ti.sysbios.family.arm.v8a.Timer.Object", om.findStrict("ti.sysbios.family.arm.v8a.Timer.Instance_State", "ti.sysbios.family.arm.v8a"));
        }//isROV
    }

    void TimestampProvider$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.TimestampProvider.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sysbios.family.arm.v8a.TimestampProvider", new Value.Obj("ti.sysbios.family.arm.v8a.TimestampProvider", po));
        pkgV.bind("TimestampProvider", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v8a.TimestampProvider$$Module_View", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v8a.TimestampProvider.Module_View", new Proto.Str(spo, false));
    }

    void Cache$$CONSTS()
    {
        // module Cache
        om.bind("ti.sysbios.family.arm.v8a.Cache.enable", new Extern("ti_sysbios_family_arm_v8a_Cache_enable__E", "xdc_Void(*)(xdc_Bits16)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.disable", new Extern("ti_sysbios_family_arm_v8a_Cache_disable__E", "xdc_Void(*)(xdc_Bits16)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.inv", new Extern("ti_sysbios_family_arm_v8a_Cache_inv__E", "xdc_Void(*)(xdc_Ptr,xdc_SizeT,xdc_Bits16,xdc_Bool)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.wb", new Extern("ti_sysbios_family_arm_v8a_Cache_wb__E", "xdc_Void(*)(xdc_Ptr,xdc_SizeT,xdc_Bits16,xdc_Bool)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.wbInv", new Extern("ti_sysbios_family_arm_v8a_Cache_wbInv__E", "xdc_Void(*)(xdc_Ptr,xdc_SizeT,xdc_Bits16,xdc_Bool)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.wait", new Extern("ti_sysbios_family_arm_v8a_Cache_wait__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.getEnabled", new Extern("ti_sysbios_family_arm_v8a_Cache_getEnabled__E", "xdc_Bits16(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.invL1pAll", new Extern("ti_sysbios_family_arm_v8a_Cache_invL1pAll__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.wbAll", new Extern("ti_sysbios_family_arm_v8a_Cache_wbAll__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.wbInvAll", new Extern("ti_sysbios_family_arm_v8a_Cache_wbInvAll__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.initModuleState", new Extern("ti_sysbios_family_arm_v8a_Cache_initModuleState__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.startup", new Extern("ti_sysbios_family_arm_v8a_Cache_startup__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.disableL1D", new Extern("ti_sysbios_family_arm_v8a_Cache_disableL1D__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.disableL1P", new Extern("ti_sysbios_family_arm_v8a_Cache_disableL1P__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.enableL1D", new Extern("ti_sysbios_family_arm_v8a_Cache_enableL1D__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.enableL1P", new Extern("ti_sysbios_family_arm_v8a_Cache_enableL1P__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.enableSmp", new Extern("ti_sysbios_family_arm_v8a_Cache_enableSmp__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.invL1d", new Extern("ti_sysbios_family_arm_v8a_Cache_invL1d__I", "xdc_Void(*)(xdc_Ptr,xdc_SizeT,xdc_Bool)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.invL1p", new Extern("ti_sysbios_family_arm_v8a_Cache_invL1p__I", "xdc_Void(*)(xdc_Ptr,xdc_SizeT,xdc_Bool)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Cache.getCacheLevelInfo", new Extern("ti_sysbios_family_arm_v8a_Cache_getCacheLevelInfo__I", "xdc_Bits32(*)(xdc_UInt)", true, false));
    }

    void Core$$CONSTS()
    {
        // module Core
        om.bind("ti.sysbios.family.arm.v8a.Core.getId", new Extern("ti_sysbios_family_arm_v8a_Core_getId__E", "xdc_UInt(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Core.interruptCore", new Extern("ti_sysbios_family_arm_v8a_Core_interruptCore__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Core.lock", new Extern("ti_sysbios_family_arm_v8a_Core_lock__E", "xdc_IArg(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Core.unlock", new Extern("ti_sysbios_family_arm_v8a_Core_unlock__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Core.hwiDisable", new Extern("ti_sysbios_family_arm_v8a_Core_hwiDisable__E", "xdc_UInt(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Core.hwiEnable", new Extern("ti_sysbios_family_arm_v8a_Core_hwiEnable__E", "xdc_UInt(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Core.hwiRestore", new Extern("ti_sysbios_family_arm_v8a_Core_hwiRestore__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Core.getClusterId", new Extern("ti_sysbios_family_arm_v8a_Core_getClusterId__E", "xdc_UInt(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Core.getRevisionNumber", new Extern("ti_sysbios_family_arm_v8a_Core_getRevisionNumber__E", "xdc_UInt8(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Core.reset", new Extern("ti_sysbios_family_arm_v8a_Core_reset__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Core.disableCaches", new Extern("ti_sysbios_family_arm_v8a_Core_disableCaches__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Core.getGicrBaseAddr", new Extern("ti_sysbios_family_arm_v8a_Core_getGicrBaseAddr__I", "xdc_Ptr(*)(xdc_Ptr)", true, false));
    }

    void Mmu$$CONSTS()
    {
        // module Mmu
        om.bind("ti.sysbios.family.arm.v8a.Mmu.PA_MAX_WIDTH", 48L);
        om.bind("ti.sysbios.family.arm.v8a.Mmu.PA_SIZE_ENCODING", 0x5L);
        om.bind("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR0", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR0", xdc.services.intern.xsr.Enum.intValue(0L)+0));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR1", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR1", xdc.services.intern.xsr.Enum.intValue(om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR0", "ti.sysbios.family.arm.v8a"))+1));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR2", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR2", xdc.services.intern.xsr.Enum.intValue(om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR0", "ti.sysbios.family.arm.v8a"))+2));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR3", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR3", xdc.services.intern.xsr.Enum.intValue(om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR0", "ti.sysbios.family.arm.v8a"))+3));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR4", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR4", xdc.services.intern.xsr.Enum.intValue(om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR0", "ti.sysbios.family.arm.v8a"))+4));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR5", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR5", xdc.services.intern.xsr.Enum.intValue(om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR0", "ti.sysbios.family.arm.v8a"))+5));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR6", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR6", xdc.services.intern.xsr.Enum.intValue(om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR0", "ti.sysbios.family.arm.v8a"))+6));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR7", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR7", xdc.services.intern.xsr.Enum.intValue(om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR0", "ti.sysbios.family.arm.v8a"))+7));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.DescriptorType_INVALID0", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.DescriptorType", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.DescriptorType_INVALID0", xdc.services.intern.xsr.Enum.intValue(0L)+0));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.DescriptorType_BLOCK", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.DescriptorType", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.DescriptorType_BLOCK", xdc.services.intern.xsr.Enum.intValue(1L)+0));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.DescriptorType_INVALID1", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.DescriptorType", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.DescriptorType_INVALID1", xdc.services.intern.xsr.Enum.intValue(2L)+0));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.DescriptorType_TABLE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.DescriptorType", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.DescriptorType_TABLE", xdc.services.intern.xsr.Enum.intValue(3L)+0));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.GranuleSize_4KB", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.GranuleSize", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.GranuleSize_4KB", xdc.services.intern.xsr.Enum.intValue(0x1000L)+0));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.GranuleSize_16KB", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.GranuleSize", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.GranuleSize_16KB", xdc.services.intern.xsr.Enum.intValue(0x4000L)+0));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.GranuleSize_64KB", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.GranuleSize", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.GranuleSize_64KB", xdc.services.intern.xsr.Enum.intValue(0x10000L)+0));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.Shareable_NONE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.Shareable", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.Shareable_NONE", xdc.services.intern.xsr.Enum.intValue(0x0L)+0));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.Shareable_OUTER", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.Shareable", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.Shareable_OUTER", xdc.services.intern.xsr.Enum.intValue(0x2L)+0));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.Shareable_INNER", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.Shareable", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.Shareable_INNER", xdc.services.intern.xsr.Enum.intValue(0x3L)+0));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.AccessPerm_PRIV_RW_USER_NONE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AccessPerm", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.AccessPerm_PRIV_RW_USER_NONE", xdc.services.intern.xsr.Enum.intValue(0x0L)+0));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.AccessPerm_PRIV_RW_USER_RW", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AccessPerm", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.AccessPerm_PRIV_RW_USER_RW", xdc.services.intern.xsr.Enum.intValue(0x1L)+0));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.AccessPerm_PRIV_RO_USER_NONE", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AccessPerm", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.AccessPerm_PRIV_RO_USER_NONE", xdc.services.intern.xsr.Enum.intValue(0x2L)+0));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.AccessPerm_PRIV_RO_USER_RO", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AccessPerm", "ti.sysbios.family.arm.v8a"), "ti.sysbios.family.arm.v8a.Mmu.AccessPerm_PRIV_RO_USER_RO", xdc.services.intern.xsr.Enum.intValue(0x3L)+0));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.enable", new Extern("ti_sysbios_family_arm_v8a_Mmu_enable__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.initMapAttrs", new Extern("ti_sysbios_family_arm_v8a_Mmu_initMapAttrs__E", "xdc_Void(*)(ti_sysbios_family_arm_v8a_Mmu_MapAttrs*)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.isEnabled", new Extern("ti_sysbios_family_arm_v8a_Mmu_isEnabled__E", "xdc_Bool(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.map", new Extern("ti_sysbios_family_arm_v8a_Mmu_map__E", "xdc_Bool(*)(xdc_UInt64,xdc_UInt64,xdc_SizeT,ti_sysbios_family_arm_v8a_Mmu_MapAttrs*)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.setMAIR", new Extern("ti_sysbios_family_arm_v8a_Mmu_setMAIR__E", "xdc_Void(*)(xdc_UInt8,xdc_UInt8)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.startup", new Extern("ti_sysbios_family_arm_v8a_Mmu_startup__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.tlbInvAll", new Extern("ti_sysbios_family_arm_v8a_Mmu_tlbInvAll__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.disable", new Extern("ti_sysbios_family_arm_v8a_Mmu_disable__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.disableI", new Extern("ti_sysbios_family_arm_v8a_Mmu_disableI__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.enableI", new Extern("ti_sysbios_family_arm_v8a_Mmu_enableI__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.addBlockEntry", new Extern("ti_sysbios_family_arm_v8a_Mmu_addBlockEntry__I", "xdc_Void(*)(xdc_UInt8,xdc_UInt64*,xdc_UInt16,xdc_UInt64,ti_sysbios_family_arm_v8a_Mmu_MapAttrs*)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.addTableEntry", new Extern("ti_sysbios_family_arm_v8a_Mmu_addTableEntry__I", "xdc_UInt64*(*)(xdc_UInt64*,xdc_UInt16,ti_sysbios_family_arm_v8a_Mmu_MapAttrs*)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.allocTable", new Extern("ti_sysbios_family_arm_v8a_Mmu_allocTable__I", "xdc_UInt64*(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.freeTable", new Extern("ti_sysbios_family_arm_v8a_Mmu_freeTable__I", "xdc_Void(*)(xdc_UInt64*)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.init", new Extern("ti_sysbios_family_arm_v8a_Mmu_init__I", "xdc_Void(*)(xdc_Ptr)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.readBlockEntry", new Extern("ti_sysbios_family_arm_v8a_Mmu_readBlockEntry__I", "xdc_Void(*)(xdc_UInt8,xdc_UInt64*,xdc_UInt16,xdc_UInt64*,ti_sysbios_family_arm_v8a_Mmu_MapAttrs*)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.setMAIRAsm", new Extern("ti_sysbios_family_arm_v8a_Mmu_setMAIRAsm__I", "xdc_Void(*)(xdc_UInt8,xdc_UInt8)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.tableWalk", new Extern("ti_sysbios_family_arm_v8a_Mmu_tableWalk__I", "xdc_Bool(*)(xdc_UInt8,xdc_UInt64*,xdc_UInt64*,xdc_UInt64*,xdc_SizeT*,ti_sysbios_family_arm_v8a_Mmu_MapAttrs*)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Mmu.setTCR", new Extern("ti_sysbios_family_arm_v8a_Mmu_setTCR__I", "xdc_Void(*)(xdc_UInt64)", true, false));
    }

    void Pmu$$CONSTS()
    {
        // module Pmu
        om.bind("ti.sysbios.family.arm.v8a.Pmu.setInterruptFunc", new Extern("ti_sysbios_family_arm_v8a_Pmu_setInterruptFunc__E", "xdc_Void(*)(xdc_Void(*)(xdc_UArg))", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.startCounter", new Extern("ti_sysbios_family_arm_v8a_Pmu_startCounter__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.stopCounter", new Extern("ti_sysbios_family_arm_v8a_Pmu_stopCounter__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.resetCount", new Extern("ti_sysbios_family_arm_v8a_Pmu_resetCount__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.setCount", new Extern("ti_sysbios_family_arm_v8a_Pmu_setCount__E", "xdc_Void(*)(xdc_UInt,xdc_UInt32)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.configureCounter", new Extern("ti_sysbios_family_arm_v8a_Pmu_configureCounter__E", "xdc_Void(*)(xdc_UInt,xdc_UInt,xdc_Bool)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.enableInterrupt", new Extern("ti_sysbios_family_arm_v8a_Pmu_enableInterrupt__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.disableInterrupt", new Extern("ti_sysbios_family_arm_v8a_Pmu_disableInterrupt__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.clearOverflowStatus", new Extern("ti_sysbios_family_arm_v8a_Pmu_clearOverflowStatus__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.getCount", new Extern("ti_sysbios_family_arm_v8a_Pmu_getCount__E", "xdc_UInt32(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.getNumCounters", new Extern("ti_sysbios_family_arm_v8a_Pmu_getNumCounters__E", "xdc_UInt(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.getOverflowStatus", new Extern("ti_sysbios_family_arm_v8a_Pmu_getOverflowStatus__E", "xdc_Bool(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.getEnabled", new Extern("ti_sysbios_family_arm_v8a_Pmu_getEnabled__E", "xdc_UInt32(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.startCounterI", new Extern("ti_sysbios_family_arm_v8a_Pmu_startCounterI__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.stopCounterI", new Extern("ti_sysbios_family_arm_v8a_Pmu_stopCounterI__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.resetCountI", new Extern("ti_sysbios_family_arm_v8a_Pmu_resetCountI__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.setCountI", new Extern("ti_sysbios_family_arm_v8a_Pmu_setCountI__E", "xdc_Void(*)(xdc_UInt,xdc_UInt32)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.enableInterruptI", new Extern("ti_sysbios_family_arm_v8a_Pmu_enableInterruptI__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.disableInterruptI", new Extern("ti_sysbios_family_arm_v8a_Pmu_disableInterruptI__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.clearOverflowStatusI", new Extern("ti_sysbios_family_arm_v8a_Pmu_clearOverflowStatusI__E", "xdc_Void(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.getCountI", new Extern("ti_sysbios_family_arm_v8a_Pmu_getCountI__E", "xdc_UInt32(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.getOverflowStatusI", new Extern("ti_sysbios_family_arm_v8a_Pmu_getOverflowStatusI__E", "xdc_UInt32(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.configureCounterI", new Extern("ti_sysbios_family_arm_v8a_Pmu_configureCounterI__I", "xdc_Void(*)(xdc_UInt,xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.clearOverflowStatusReg", new Extern("ti_sysbios_family_arm_v8a_Pmu_clearOverflowStatusReg__I", "xdc_Void(*)(xdc_UInt32)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.getOverflowStatusReg", new Extern("ti_sysbios_family_arm_v8a_Pmu_getOverflowStatusReg__I", "xdc_UInt32(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.initCounters", new Extern("ti_sysbios_family_arm_v8a_Pmu_initCounters__I", "xdc_Void(*)(xdc_UInt32)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Pmu.interruptHandler", new Extern("ti_sysbios_family_arm_v8a_Pmu_interruptHandler__I", "xdc_Void(*)(xdc_UArg)", true, false));
    }

    void TaskSupport$$CONSTS()
    {
        // module TaskSupport
        om.bind("ti.sysbios.family.arm.v8a.TaskSupport.start", new Extern("ti_sysbios_family_arm_v8a_TaskSupport_start__E", "xdc_Ptr(*)(xdc_Ptr,xdc_Void(*)(xdc_Void),xdc_Void(*)(xdc_Void),xdc_runtime_Error_Block*)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.TaskSupport.swap", new Extern("ti_sysbios_family_arm_v8a_TaskSupport_swap__E", "xdc_Void(*)(xdc_Ptr*,xdc_Ptr*)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.TaskSupport.checkStack", new Extern("ti_sysbios_family_arm_v8a_TaskSupport_checkStack__E", "xdc_Bool(*)(xdc_Char*,xdc_SizeT)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.TaskSupport.stackUsed", new Extern("ti_sysbios_family_arm_v8a_TaskSupport_stackUsed__E", "xdc_SizeT(*)(xdc_Char*,xdc_SizeT)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.TaskSupport.getStackAlignment", new Extern("ti_sysbios_family_arm_v8a_TaskSupport_getStackAlignment__E", "xdc_UInt(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.TaskSupport.getDefaultStackSize", new Extern("ti_sysbios_family_arm_v8a_TaskSupport_getDefaultStackSize__E", "xdc_SizeT(*)(xdc_Void)", true, false));
    }

    void Timer$$CONSTS()
    {
        // module Timer
        om.bind("ti.sysbios.family.arm.v8a.Timer.MAX_PERIOD", 0x00FFFFFFFFFFFFFFL);
        om.bind("ti.sysbios.family.arm.v8a.Timer.NUM_TIMER_DEVICES", 2L);
        om.bind("ti.sysbios.family.arm.v8a.Timer.getNumTimers", new Extern("ti_sysbios_family_arm_v8a_Timer_getNumTimers__E", "xdc_UInt(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.getStatus", new Extern("ti_sysbios_family_arm_v8a_Timer_getStatus__E", "ti_sysbios_interfaces_ITimer_Status(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.startup", new Extern("ti_sysbios_family_arm_v8a_Timer_startup__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.oneShotStub", new Extern("ti_sysbios_family_arm_v8a_Timer_oneShotStub__E", "xdc_Void(*)(xdc_UArg)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.periodicStub", new Extern("ti_sysbios_family_arm_v8a_Timer_periodicStub__E", "xdc_Void(*)(xdc_UArg)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.getHandle", new Extern("ti_sysbios_family_arm_v8a_Timer_getHandle__E", "ti_sysbios_family_arm_v8a_Timer_Handle(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.initDevice", new Extern("ti_sysbios_family_arm_v8a_Timer_initDevice__I", "xdc_Void(*)(ti_sysbios_family_arm_v8a_Timer_Object*)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.postInit", new Extern("ti_sysbios_family_arm_v8a_Timer_postInit__I", "xdc_Int(*)(ti_sysbios_family_arm_v8a_Timer_Object*,xdc_runtime_Error_Block*)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.checkOverflow", new Extern("ti_sysbios_family_arm_v8a_Timer_checkOverflow__I", "xdc_Bool(*)(xdc_UInt64,xdc_UInt64)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.readPhyCtrl", new Extern("ti_sysbios_family_arm_v8a_Timer_readPhyCtrl__I", "xdc_UInt32(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.readPhyCnt", new Extern("ti_sysbios_family_arm_v8a_Timer_readPhyCnt__I", "xdc_Void(*)(xdc_UInt64*)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.writePhyCtrl", new Extern("ti_sysbios_family_arm_v8a_Timer_writePhyCtrl__I", "xdc_Void(*)(xdc_UInt32)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.writePhyCmpVal", new Extern("ti_sysbios_family_arm_v8a_Timer_writePhyCmpVal__I", "xdc_Void(*)(xdc_UInt64*)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.readVirtCtrl", new Extern("ti_sysbios_family_arm_v8a_Timer_readVirtCtrl__I", "xdc_UInt32(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.readVirtCnt", new Extern("ti_sysbios_family_arm_v8a_Timer_readVirtCnt__I", "xdc_Void(*)(xdc_UInt64*)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.tickReconfigSmp", new Extern("ti_sysbios_family_arm_v8a_Timer_tickReconfigSmp__I", "xdc_Void(*)(xdc_UArg)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.writeVirtCtrl", new Extern("ti_sysbios_family_arm_v8a_Timer_writeVirtCtrl__I", "xdc_Void(*)(xdc_UInt32)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.Timer.writeVirtCmpVal", new Extern("ti_sysbios_family_arm_v8a_Timer_writeVirtCmpVal__I", "xdc_Void(*)(xdc_UInt64*)", true, false));
    }

    void TimestampProvider$$CONSTS()
    {
        // module TimestampProvider
        om.bind("ti.sysbios.family.arm.v8a.TimestampProvider.get32", new Extern("ti_sysbios_family_arm_v8a_TimestampProvider_get32__E", "xdc_Bits32(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.TimestampProvider.get64", new Extern("ti_sysbios_family_arm_v8a_TimestampProvider_get64__E", "xdc_Void(*)(xdc_runtime_Types_Timestamp64*)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.TimestampProvider.getFreq", new Extern("ti_sysbios_family_arm_v8a_TimestampProvider_getFreq__E", "xdc_Void(*)(xdc_runtime_Types_FreqHz*)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.TimestampProvider.initCCNT", new Extern("ti_sysbios_family_arm_v8a_TimestampProvider_initCCNT__I", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v8a.TimestampProvider.get64I", new Extern("ti_sysbios_family_arm_v8a_TimestampProvider_get64I__I", "xdc_UInt64(*)(xdc_Void)", true, false));
    }

    void Cache$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Core$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Mmu$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Pmu$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void TaskSupport$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Timer$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sysbios$family$arm$v8a$Timer$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sysbios.family.arm.v8a.Timer.create() called before xdc.useModule('ti.sysbios.family.arm.v8a.Timer')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.id, inst.$args.tickFxn, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sysbios.family.arm.v8a.Timer$$create", new Proto.Fxn(om.findStrict("ti.sysbios.family.arm.v8a.Timer.Module", "ti.sysbios.family.arm.v8a"), om.findStrict("ti.sysbios.family.arm.v8a.Timer.Instance", "ti.sysbios.family.arm.v8a"), 3, 2, false));
                        fxn.addArg(0, "id", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF);
                        fxn.addArg(1, "tickFxn", new Proto.Adr("xdc_Void(*)(xdc_UArg)", "PFv"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sysbios.family.arm.v8a.Timer.Params", "ti.sysbios.family.arm.v8a"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sysbios$family$arm$v8a$Timer$$create = function( id, tickFxn, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sysbios.family.arm.v8a.Timer'];\n");
                sb.append("var __inst = xdc.om['ti.sysbios.family.arm.v8a.Timer.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sysbios.family.arm.v8a']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {id:id, tickFxn:tickFxn});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sysbios.family.arm.v8a.Timer'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [id, tickFxn]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sysbios.family.arm.v8a.Timer'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sysbios.family.arm.v8a.Timer$$construct", new Proto.Fxn(om.findStrict("ti.sysbios.family.arm.v8a.Timer.Module", "ti.sysbios.family.arm.v8a"), null, 4, 2, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sysbios.family.arm.v8a.Timer$$Object", "ti.sysbios.family.arm.v8a"), null);
                        fxn.addArg(1, "id", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF);
                        fxn.addArg(2, "tickFxn", new Proto.Adr("xdc_Void(*)(xdc_UArg)", "PFv"), $$UNDEF);
                        fxn.addArg(3, "__params", (Proto)om.findStrict("ti.sysbios.family.arm.v8a.Timer.Params", "ti.sysbios.family.arm.v8a"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sysbios$family$arm$v8a$Timer$$construct = function( __obj, id, tickFxn, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sysbios.family.arm.v8a.Timer'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {id:id, tickFxn:tickFxn});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sysbios.family.arm.v8a.Timer'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sysbios.family.arm.v8a.Timer'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void TimestampProvider$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Cache$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Core$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Mmu$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Pmu$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TaskSupport$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Timer$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void TimestampProvider$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Cache$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v8a.Cache.Module_State", "ti.sysbios.family.arm.v8a");
        sizes.clear();
        sizes.add(Global.newArray("l1dInfo", "UInt32"));
        sizes.add(Global.newArray("l1pInfo", "UInt32"));
        sizes.add(Global.newArray("l2Info", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v8a.Cache.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v8a.Cache.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v8a.Cache.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void Core$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Mmu$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.MapAttrs", "ti.sysbios.family.arm.v8a");
        sizes.clear();
        sizes.add(Global.newArray("accessPerm", "Nti.sysbios.family.arm.v8a.Mmu.AccessPerm;;0x0;0x1;0x2;0x3"));
        sizes.add(Global.newArray("privExecute", "UShort"));
        sizes.add(Global.newArray("userExecute", "UShort"));
        sizes.add(Global.newArray("shareable", "Nti.sysbios.family.arm.v8a.Mmu.Shareable;;0x0;0x2;0x3"));
        sizes.add(Global.newArray("attrIndx", "Nti.sysbios.family.arm.v8a.Mmu.AttrIndx;;0;;;;;;;"));
        sizes.add(Global.newArray("global", "UShort"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v8a.Mmu.MapAttrs']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v8a.Mmu.MapAttrs']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v8a.Mmu.MapAttrs'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.ConfigInfo", "ti.sysbios.family.arm.v8a");
        sizes.clear();
        sizes.add(Global.newArray("indexMask", "UInt64"));
        sizes.add(Global.newArray("tableLength", "UInt32"));
        sizes.add(Global.newArray("tableOffset", "A4;UInt8"));
        sizes.add(Global.newArray("granuleSizeBits", "UInt8"));
        sizes.add(Global.newArray("indexBits", "UInt8"));
        sizes.add(Global.newArray("noLevel0Table", "UShort"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v8a.Mmu.ConfigInfo']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v8a.Mmu.ConfigInfo']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v8a.Mmu.ConfigInfo'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.Module_State", "ti.sysbios.family.arm.v8a");
        sizes.clear();
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v8a.Mmu.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v8a.Mmu.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v8a.Mmu.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void Pmu$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v8a.Pmu.Module_State", "ti.sysbios.family.arm.v8a");
        sizes.clear();
        sizes.add(Global.newArray("numCounters", "UInt"));
        sizes.add(Global.newArray("hwiHandle", "UPtr"));
        sizes.add(Global.newArray("interruptFunc", "UFxn"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v8a.Pmu.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v8a.Pmu.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v8a.Pmu.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void TaskSupport$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Timer$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v8a.Timer.Instance_State", "ti.sysbios.family.arm.v8a");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("staticInst", "UShort"));
        sizes.add(Global.newArray("id", "TInt"));
        sizes.add(Global.newArray("runMode", "Nti.sysbios.interfaces.ITimer.RunMode;;;;"));
        sizes.add(Global.newArray("startMode", "Nti.sysbios.interfaces.ITimer.StartMode;;;"));
        sizes.add(Global.newArray("period", "UInt64"));
        sizes.add(Global.newArray("periodType", "Nti.sysbios.interfaces.ITimer.PeriodType;;;"));
        sizes.add(Global.newArray("intNum", "UInt"));
        sizes.add(Global.newArray("arg", "UIArg"));
        sizes.add(Global.newArray("tickFxn", "UFxn"));
        sizes.add(Global.newArray("extFreq", "Sxdc.runtime.Types;FreqHz"));
        sizes.add(Global.newArray("hwi", "UPtr"));
        sizes.add(Global.newArray("prevThreshold", "UInt64"));
        sizes.add(Global.newArray("nextThreshold", "UInt64"));
        sizes.add(Global.newArray("savedCurrCount", "UInt64"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v8a.Timer.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v8a.Timer.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v8a.Timer.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v8a.Timer.Module_State", "ti.sysbios.family.arm.v8a");
        sizes.clear();
        sizes.add(Global.newArray("availMask", "UInt"));
        sizes.add(Global.newArray("handles", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v8a.Timer.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v8a.Timer.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v8a.Timer.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void TimestampProvider$$SIZES()
    {
        Proto.Str so;
        Object fxn;

    }

    void Cache$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sysbios/family/arm/v8a/Cache.xs");
        om.bind("ti.sysbios.family.arm.v8a.Cache$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Cache.Module", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Cache.Module", om.findStrict("ti.sysbios.interfaces.ICache.Module", "ti.sysbios.family.arm.v8a"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sysbios.family.arm.v8a"), $$UNDEF, "wh");
            po.addFld("enableCache", $$T_Bool, true, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Cache$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Cache$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Cache$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Cache$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct Cache.CacheInfoView
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Cache$$CacheInfoView", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Cache.CacheInfoView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("cache", $$T_Str, $$UNDEF, "w");
                po.addFld("cacheSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("lineSize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
                po.addFld("ways", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("waySize", Proto.Elm.newCNum("(xdc_SizeT)"), $$UNDEF, "w");
        // struct Cache.Module_State
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Cache$$Module_State", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Cache.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("l1dInfo", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("l1pInfo", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
                po.addFld("l2Info", Proto.Elm.newCNum("(xdc_Bits32)"), $$UNDEF, "w");
    }

    void Core$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sysbios/family/arm/v8a/Core.xs");
        om.bind("ti.sysbios.family.arm.v8a.Core$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Core.Module", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Core.Module", om.findStrict("ti.sysbios.interfaces.ICore.Module", "ti.sysbios.family.arm.v8a"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("id", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "w");
            po.addFld("baseClusterId", Proto.Elm.newCNum("(xdc_UInt)"), 0L, "w");
            po.addFld("numCores", Proto.Elm.newCNum("(xdc_UInt)"), 1L, "w");
            po.addFld("bootMaster", $$T_Bool, true, "wh");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Core$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Core$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Core$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Core$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
    }

    void Mmu$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sysbios/family/arm/v8a/Mmu.xs");
        om.bind("ti.sysbios.family.arm.v8a.Mmu$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.Module", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Mmu.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.sysbios.family.arm.v8a"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("PA_MAX_WIDTH", Proto.Elm.newCNum("(xdc_UInt8)"), 48L, "rh");
                po.addFld("PA_SIZE_ENCODING", Proto.Elm.newCNum("(xdc_UInt8)"), 0x5L, "rh");
        if (isCFG) {
            po.addFld("A_nullPointer", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sysbios.family.arm.v8a"), Global.newObject("msg", "A_nullPointer: Pointer is null"), "w");
            po.addFld("A_vaddrOutOfRange", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sysbios.family.arm.v8a"), Global.newObject("msg", "A_vaddrOutOfRange: Virtual address is out of range"), "w");
            po.addFld("A_paddrOutOfRange", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sysbios.family.arm.v8a"), Global.newObject("msg", "A_paddrOutOfRange: Physical address is out of range"), "w");
            po.addFld("A_unalignedVaddr", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sysbios.family.arm.v8a"), Global.newObject("msg", "A_unalignedVaddr: Virtual address not page aligned"), "w");
            po.addFld("A_unalignedPaddr", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sysbios.family.arm.v8a"), Global.newObject("msg", "A_unalignedPaddr: Physical address not page aligned"), "w");
            po.addFld("A_unalignedSize", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sysbios.family.arm.v8a"), Global.newObject("msg", "A_unalignedSize: Mmu mapping size not page aligned"), "w");
            po.addFld("defaultMapAttrs", (Proto)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.MapAttrs", "ti.sysbios.family.arm.v8a"), Global.newObject("accessPerm", om.find("ti.sysbios.family.arm.v8a.Mmu.AccessPerm_PRIV_RW_USER_NONE"), "privExecute", true, "userExecute", false, "shareable", om.find("ti.sysbios.family.arm.v8a.Mmu.Shareable_OUTER"), "attrIndx", om.find("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR0"), "global", true), "w");
            po.addFld("enableMMU", $$T_Bool, true, "w");
            po.addFld("granuleSize", (Proto)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.GranuleSize", "ti.sysbios.family.arm.v8a"), om.find("ti.sysbios.family.arm.v8a.Mmu.GranuleSize_4KB"), "w");
            po.addFld("MAIR0", Proto.Elm.newCNum("(xdc_UInt8)"), 0x00L, "w");
            po.addFld("MAIR1", Proto.Elm.newCNum("(xdc_UInt8)"), 0x04L, "w");
            po.addFld("MAIR2", Proto.Elm.newCNum("(xdc_UInt8)"), 0x08L, "w");
            po.addFld("MAIR3", Proto.Elm.newCNum("(xdc_UInt8)"), 0x0CL, "w");
            po.addFld("MAIR4", Proto.Elm.newCNum("(xdc_UInt8)"), 0x44L, "w");
            po.addFld("MAIR5", Proto.Elm.newCNum("(xdc_UInt8)"), 0x4FL, "w");
            po.addFld("MAIR6", Proto.Elm.newCNum("(xdc_UInt8)"), 0xBBL, "w");
            po.addFld("MAIR7", Proto.Elm.newCNum("(xdc_UInt8)"), 0xFFL, "w");
            po.addFld("initFunc", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"), null, "w");
            po.addFld("tableArraySection", $$T_Str, ".data.ti_sysbios_family_arm_v8a_Mmu_tableArray", "wh");
            po.addFld("tableArrayLen", Proto.Elm.newCNum("(xdc_UInt)"), 16L, "w");
            po.addFld("configInfo", (Proto)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.ConfigInfo", "ti.sysbios.family.arm.v8a"), $$DEFAULT, "w");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Mmu$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Mmu$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Mmu$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Mmu$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // typedef Mmu.InitFuncPtr
        om.bind("ti.sysbios.family.arm.v8a.Mmu.InitFuncPtr", new Proto.Adr("xdc_Void(*)(xdc_Void)", "PFv"));
        // struct Mmu.MapAttrs
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Mmu$$MapAttrs", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Mmu.MapAttrs", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("accessPerm", (Proto)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AccessPerm", "ti.sysbios.family.arm.v8a"), $$UNDEF, "w");
                po.addFld("privExecute", $$T_Bool, $$UNDEF, "w");
                po.addFld("userExecute", $$T_Bool, $$UNDEF, "w");
                po.addFld("shareable", (Proto)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.Shareable", "ti.sysbios.family.arm.v8a"), $$UNDEF, "w");
                po.addFld("attrIndx", (Proto)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx", "ti.sysbios.family.arm.v8a"), $$UNDEF, "w");
                po.addFld("global", $$T_Bool, $$UNDEF, "w");
        // struct Mmu.ConfigInfo
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Mmu$$ConfigInfo", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Mmu.ConfigInfo", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("indexMask", Proto.Elm.newCNum("(xdc_UInt64)"), $$UNDEF, "w");
                po.addFld("tableLength", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("tableOffset", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt8)"), false, xdc.services.intern.xsr.Enum.intValue(4L)), $$DEFAULT, "w");
                po.addFld("granuleSizeBits", Proto.Elm.newCNum("(xdc_UInt8)"), $$UNDEF, "w");
                po.addFld("indexBits", Proto.Elm.newCNum("(xdc_UInt8)"), $$UNDEF, "w");
                po.addFld("noLevel0Table", $$T_Bool, $$UNDEF, "w");
        // struct Mmu.Module_State
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Mmu$$Module_State", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Mmu.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
    }

    void Pmu$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sysbios/family/arm/v8a/Pmu.xs");
        om.bind("ti.sysbios.family.arm.v8a.Pmu$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Pmu.Module", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Pmu.Module", om.findStrict("xdc.runtime.IModule.Module", "ti.sysbios.family.arm.v8a"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("intNum", Proto.Elm.newCNum("(xdc_UInt)"), (Global.eval("~0")), "w");
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sysbios.family.arm.v8a"), $$UNDEF, "wh");
            po.addFld("A_badIntNum", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sysbios.family.arm.v8a"), Global.newObject("msg", "A_badIntNum: Set PMU interrupt number using Pmu.intNum config param."), "w");
            po.addFld("A_invalidCounterId", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sysbios.family.arm.v8a"), Global.newObject("msg", "A_invalidCounterId: Invalid PMU counter Id passed."), "w");
            po.addFld("interruptFunc", new Proto.Adr("xdc_Void(*)(xdc_UArg)", "PFv"), null, "wh");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Pmu$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Pmu$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Pmu$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Pmu$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // typedef Pmu.IntHandlerFuncPtr
        om.bind("ti.sysbios.family.arm.v8a.Pmu.IntHandlerFuncPtr", new Proto.Adr("xdc_Void(*)(xdc_UArg)", "PFv"));
        // struct Pmu.PmuInfoView
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Pmu$$PmuInfoView", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Pmu.PmuInfoView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("numEventCounters", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
        // struct Pmu.Module_State
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Pmu$$Module_State", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Pmu.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("numCounters", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("hwiHandle", (Proto)om.findStrict("ti.sysbios.hal.Hwi.Handle", "ti.sysbios.family.arm.v8a"), $$UNDEF, "w");
                po.addFld("interruptFunc", new Proto.Adr("xdc_Void(*)(xdc_UArg)", "PFv"), $$UNDEF, "w");
    }

    void TaskSupport$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sysbios/family/arm/v8a/TaskSupport.xs");
        om.bind("ti.sysbios.family.arm.v8a.TaskSupport$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.TaskSupport.Module", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.TaskSupport.Module", om.findStrict("ti.sysbios.interfaces.ITaskSupport.Module", "ti.sysbios.family.arm.v8a"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
            po.addFld("defaultStackSize", Proto.Elm.newCNum("(xdc_SizeT)"), 2048L, "r");
            po.addFld("stackAlignment", Proto.Elm.newCNum("(xdc_UInt)"), 16L, "r");
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.TaskSupport$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.TaskSupport$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.TaskSupport$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.TaskSupport$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "stackUsed$view");
                if (fxn != null) po.addFxn("stackUsed$view", (Proto.Fxn)om.findStrict("ti.sysbios.interfaces.ITaskSupport$$stackUsed$view", "ti.sysbios.family.arm.v8a"), fxn);
                fxn = Global.get(cap, "getCallStack$view");
                if (fxn != null) po.addFxn("getCallStack$view", (Proto.Fxn)om.findStrict("ti.sysbios.interfaces.ITaskSupport$$getCallStack$view", "ti.sysbios.family.arm.v8a"), fxn);
    }

    void Timer$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sysbios/family/arm/v8a/Timer.xs");
        om.bind("ti.sysbios.family.arm.v8a.Timer$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Timer.Module", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Timer.Module", om.findStrict("ti.sysbios.interfaces.ITimer.Module", "ti.sysbios.family.arm.v8a"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("ANY", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~0"), "rh");
                po.addFld("MAX_PERIOD", Proto.Elm.newCNum("(xdc_UInt64)"), 0x00FFFFFFFFFFFFFFL, "rh");
                po.addFld("NUM_TIMER_DEVICES", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
            po.addFld("supportsDynamic", $$T_Bool, true, "wh");
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sysbios.family.arm.v8a"), $$UNDEF, "wh");
            po.addFld("E_invalidTimer", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v8a"), Global.newObject("msg", "E_invalidTimer: Invalid Timer Id %d"), "w");
            po.addFld("E_notAvailable", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v8a"), Global.newObject("msg", "E_notAvailable: Timer not available %d"), "w");
            po.addFld("E_invalidHwiMask", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v8a"), Global.newObject("msg", "E_InvalidMask: Mask in hwiParams cannot enable self"), "w");
            po.addFld("E_cannotSupport", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v8a"), Global.newObject("msg", "E_cannotSupport: Timer cannot support requested period %d"), "w");
            po.addFld("intNumDef", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt)"), false, xdc.services.intern.xsr.Enum.intValue(2L)), $$DEFAULT, "w");
            po.addFld("anyMask", Proto.Elm.newCNum("(xdc_UInt)"), 0x3L, "w");
            po.addFld("availMask", Proto.Elm.newCNum("(xdc_UInt)"), 0x3L, "w");
            po.addFld("intFreq", (Proto)om.findStrict("xdc.runtime.Types.FreqHz", "ti.sysbios.family.arm.v8a"), $$DEFAULT, "w");
            po.addFld("vlabErrata", $$T_Bool, false, "w");
            po.addFld("startupNeeded", Proto.Elm.newCNum("(xdc_UInt)"), false, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sysbios.family.arm.v8a.Timer$$create", "ti.sysbios.family.arm.v8a"), Global.get("ti$sysbios$family$arm$v8a$Timer$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sysbios.family.arm.v8a.Timer$$construct", "ti.sysbios.family.arm.v8a"), Global.get("ti$sysbios$family$arm$v8a$Timer$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Timer$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Timer$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Timer$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Timer$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Timer$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.Timer$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "viewGetCurrentClockTick");
                if (fxn != null) po.addFxn("viewGetCurrentClockTick", (Proto.Fxn)om.findStrict("ti.sysbios.interfaces.ITimer$$viewGetCurrentClockTick", "ti.sysbios.family.arm.v8a"), fxn);
                fxn = Global.get(cap, "getFreqMeta");
                if (fxn != null) po.addFxn("getFreqMeta", (Proto.Fxn)om.findStrict("ti.sysbios.interfaces.ITimer$$getFreqMeta", "ti.sysbios.family.arm.v8a"), fxn);
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Timer.Instance", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Timer.Instance", om.findStrict("ti.sysbios.interfaces.ITimer.Instance", "ti.sysbios.family.arm.v8a"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("ANY", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~0"), "rh");
                po.addFld("MAX_PERIOD", Proto.Elm.newCNum("(xdc_UInt64)"), 0x00FFFFFFFFFFFFFFL, "rh");
                po.addFld("NUM_TIMER_DEVICES", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
            po.addFld("hwiParams", new Proto.Adr("ti_sysbios_family_arm_gicv3_Hwi_Params*", "PS"), null, "w");
            po.addFld("period64", Proto.Elm.newCNum("(xdc_UInt64)"), 0L, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sysbios.family.arm.v8a"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Timer$$Params", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Timer.Params", om.findStrict("ti.sysbios.interfaces.ITimer$$Params", "ti.sysbios.family.arm.v8a"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("ANY", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~0"), "rh");
                po.addFld("MAX_PERIOD", Proto.Elm.newCNum("(xdc_UInt64)"), 0x00FFFFFFFFFFFFFFL, "rh");
                po.addFld("NUM_TIMER_DEVICES", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
        if (isCFG) {
            po.addFld("hwiParams", new Proto.Adr("ti_sysbios_family_arm_gicv3_Hwi_Params*", "PS"), null, "w");
            po.addFld("period64", Proto.Elm.newCNum("(xdc_UInt64)"), 0L, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sysbios.family.arm.v8a"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Timer$$Object", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Timer.Object", om.findStrict("ti.sysbios.family.arm.v8a.Timer.Instance", "ti.sysbios.family.arm.v8a"));
        // struct Timer.BasicView
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Timer$$BasicView", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Timer.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("halTimerHandle", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("label", $$T_Str, $$UNDEF, "w");
                po.addFld("id", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("startMode", $$T_Str, $$UNDEF, "w");
                po.addFld("runMode", $$T_Str, $$UNDEF, "w");
                po.addFld("period", $$T_Str, $$UNDEF, "w");
                po.addFld("periodType", $$T_Str, $$UNDEF, "w");
                po.addFld("intNum", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("tickFxn", new Proto.Arr($$T_Str, false), $$DEFAULT, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("extFreq", $$T_Str, $$UNDEF, "w");
                po.addFld("hwiHandle", $$T_Str, $$UNDEF, "w");
                po.addFld("prevThreshold", $$T_Str, $$UNDEF, "w");
                po.addFld("nextThreshold", $$T_Str, $$UNDEF, "w");
                po.addFxn("$xml", $$T_Met, Global.get("$$xml"));
        // struct Timer.ModuleView
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Timer$$ModuleView", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Timer.ModuleView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("availMask", $$T_Str, $$UNDEF, "w");
        // struct Timer.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Timer$$Instance_State", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Timer.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("staticInst", $$T_Bool, $$UNDEF, "w");
                po.addFld("id", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("runMode", (Proto)om.findStrict("ti.sysbios.interfaces.ITimer.RunMode", "ti.sysbios.family.arm.v8a"), $$UNDEF, "w");
                po.addFld("startMode", (Proto)om.findStrict("ti.sysbios.interfaces.ITimer.StartMode", "ti.sysbios.family.arm.v8a"), $$UNDEF, "w");
                po.addFld("period", Proto.Elm.newCNum("(xdc_UInt64)"), $$UNDEF, "w");
                po.addFld("periodType", (Proto)om.findStrict("ti.sysbios.interfaces.ITimer.PeriodType", "ti.sysbios.family.arm.v8a"), $$UNDEF, "w");
                po.addFld("intNum", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("tickFxn", new Proto.Adr("xdc_Void(*)(xdc_UArg)", "PFv"), $$UNDEF, "w");
                po.addFld("extFreq", (Proto)om.findStrict("xdc.runtime.Types.FreqHz", "ti.sysbios.family.arm.v8a"), $$DEFAULT, "w");
                po.addFld("hwi", (Proto)om.findStrict("ti.sysbios.family.arm.gicv3.Hwi.Handle", "ti.sysbios.family.arm.v8a"), $$UNDEF, "w");
                po.addFld("prevThreshold", Proto.Elm.newCNum("(xdc_UInt64)"), $$UNDEF, "w");
                po.addFld("nextThreshold", Proto.Elm.newCNum("(xdc_UInt64)"), $$UNDEF, "w");
                po.addFld("savedCurrCount", Proto.Elm.newCNum("(xdc_UInt64)"), $$UNDEF, "w");
        // struct Timer.Module_State
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Timer$$Module_State", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.Timer.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("availMask", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("handles", new Proto.Arr((Proto)om.findStrict("ti.sysbios.family.arm.v8a.Timer.Handle", "ti.sysbios.family.arm.v8a"), false), $$DEFAULT, "w");
    }

    void TimestampProvider$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sysbios/family/arm/v8a/TimestampProvider.xs");
        om.bind("ti.sysbios.family.arm.v8a.TimestampProvider$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.TimestampProvider.Module", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.TimestampProvider.Module", om.findStrict("ti.sysbios.interfaces.ITimestamp.Module", "ti.sysbios.family.arm.v8a"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
        if (isCFG) {
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.TimestampProvider$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.TimestampProvider$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.TimestampProvider$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v8a.TimestampProvider$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "getFreqMeta");
                if (fxn != null) po.addFxn("getFreqMeta", (Proto.Fxn)om.findStrict("ti.sysbios.interfaces.ITimestamp$$getFreqMeta", "ti.sysbios.family.arm.v8a"), fxn);
        // struct TimestampProvider.Module_View
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.TimestampProvider$$Module_View", "ti.sysbios.family.arm.v8a");
        po.init("ti.sysbios.family.arm.v8a.TimestampProvider.Module_View", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("$xml", $$T_Met, Global.get("$$xml"));
    }

    void Cache$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Cache", "ti.sysbios.family.arm.v8a");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v8a.Cache.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Cache$$Module_State", "ti.sysbios.family.arm.v8a");
    }

    void Core$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Core", "ti.sysbios.family.arm.v8a");
    }

    void Mmu$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Mmu", "ti.sysbios.family.arm.v8a");
        vo.bind("MapAttrs$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v8a.Mmu.MapAttrs", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Mmu$$MapAttrs", "ti.sysbios.family.arm.v8a");
        vo.bind("ConfigInfo$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v8a.Mmu.ConfigInfo", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Mmu$$ConfigInfo", "ti.sysbios.family.arm.v8a");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v8a.Mmu.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Mmu$$Module_State", "ti.sysbios.family.arm.v8a");
    }

    void Pmu$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Pmu", "ti.sysbios.family.arm.v8a");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v8a.Pmu.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Pmu$$Module_State", "ti.sysbios.family.arm.v8a");
    }

    void TaskSupport$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v8a.TaskSupport", "ti.sysbios.family.arm.v8a");
    }

    void Timer$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Timer", "ti.sysbios.family.arm.v8a");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Timer$$Instance_State", "ti.sysbios.family.arm.v8a");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v8a.Timer.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Timer$$Instance_State", "ti.sysbios.family.arm.v8a");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v8a.Timer.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Timer$$Module_State", "ti.sysbios.family.arm.v8a");
        po.bind("handles$fetchDesc", Global.newObject("type", "xdc.rov.support.ScalarStructs.S_Ptr", "isScalar", true));
    }

    void TimestampProvider$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v8a.TimestampProvider", "ti.sysbios.family.arm.v8a");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sysbios.family.arm.v8a.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sysbios.family.arm.v8a"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sysbios/family/arm/v8a/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sysbios.family.arm.v8a"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sysbios.family.arm.v8a"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sysbios.family.arm.v8a"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sysbios.family.arm.v8a"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sysbios.family.arm.v8a"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sysbios.family.arm.v8a"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sysbios.family.arm.v8a", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sysbios.family.arm.v8a");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sysbios.family.arm.v8a.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sysbios.interfaces", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sysbios.family.arm.v8a'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sysbios.family.arm.v8a$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sysbios.family.arm.v8a$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sysbios.family.arm.v8a$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/debug/ti.sysbios.family.arm.v8a.aa53fg',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/debug/ti.sysbios.family.arm.v8a.aa53fg', {target: 'gnu.targets.arm.A53F', suffix: 'a53fg'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Cache$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Cache", "ti.sysbios.family.arm.v8a");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Cache.Module", "ti.sysbios.family.arm.v8a");
        vo.init2(po, "ti.sysbios.family.arm.v8a.Cache", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sysbios.family.arm.v8a.Cache$$capsule", "ti.sysbios.family.arm.v8a"));
        vo.bind("$package", om.findStrict("ti.sysbios.family.arm.v8a", "ti.sysbios.family.arm.v8a"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        mcfgs.add("Module__diagsEnabled");
        icfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        icfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        icfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        icfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        icfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        icfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        icfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        icfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn0");
        icfgs.add("Module__loggerFxn0");
        mcfgs.add("Module__loggerFxn1");
        icfgs.add("Module__loggerFxn1");
        mcfgs.add("Module__loggerFxn2");
        icfgs.add("Module__loggerFxn2");
        mcfgs.add("Module__loggerFxn4");
        icfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        icfgs.add("Module__loggerFxn8");
        mcfgs.add("Object__count");
        icfgs.add("Object__count");
        mcfgs.add("Object__heap");
        icfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        icfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        icfgs.add("Object__table");
        vo.bind("Type", om.findStrict("ti.sysbios.interfaces.ICache.Type", "ti.sysbios.family.arm.v8a"));
        vo.bind("CacheInfoView", om.findStrict("ti.sysbios.family.arm.v8a.Cache.CacheInfoView", "ti.sysbios.family.arm.v8a"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v8a.Cache.CacheInfoView", "ti.sysbios.family.arm.v8a"));
        mcfgs.add("enableCache");
        vo.bind("Module_State", om.findStrict("ti.sysbios.family.arm.v8a.Cache.Module_State", "ti.sysbios.family.arm.v8a"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v8a.Cache.Module_State", "ti.sysbios.family.arm.v8a"));
        vo.bind("Type_L1P", om.findStrict("ti.sysbios.interfaces.ICache.Type_L1P", "ti.sysbios.family.arm.v8a"));
        vo.bind("Type_L1D", om.findStrict("ti.sysbios.interfaces.ICache.Type_L1D", "ti.sysbios.family.arm.v8a"));
        vo.bind("Type_L1", om.findStrict("ti.sysbios.interfaces.ICache.Type_L1", "ti.sysbios.family.arm.v8a"));
        vo.bind("Type_L2P", om.findStrict("ti.sysbios.interfaces.ICache.Type_L2P", "ti.sysbios.family.arm.v8a"));
        vo.bind("Type_L2D", om.findStrict("ti.sysbios.interfaces.ICache.Type_L2D", "ti.sysbios.family.arm.v8a"));
        vo.bind("Type_L2", om.findStrict("ti.sysbios.interfaces.ICache.Type_L2", "ti.sysbios.family.arm.v8a"));
        vo.bind("Type_ALLP", om.findStrict("ti.sysbios.interfaces.ICache.Type_ALLP", "ti.sysbios.family.arm.v8a"));
        vo.bind("Type_ALLD", om.findStrict("ti.sysbios.interfaces.ICache.Type_ALLD", "ti.sysbios.family.arm.v8a"));
        vo.bind("Type_ALL", om.findStrict("ti.sysbios.interfaces.ICache.Type_ALL", "ti.sysbios.family.arm.v8a"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sysbios.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sysbios.family.arm.v8a")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("enable", om.findStrict("ti.sysbios.family.arm.v8a.Cache.enable", "ti.sysbios.family.arm.v8a"));
        vo.bind("disable", om.findStrict("ti.sysbios.family.arm.v8a.Cache.disable", "ti.sysbios.family.arm.v8a"));
        vo.bind("inv", om.findStrict("ti.sysbios.family.arm.v8a.Cache.inv", "ti.sysbios.family.arm.v8a"));
        vo.bind("wb", om.findStrict("ti.sysbios.family.arm.v8a.Cache.wb", "ti.sysbios.family.arm.v8a"));
        vo.bind("wbInv", om.findStrict("ti.sysbios.family.arm.v8a.Cache.wbInv", "ti.sysbios.family.arm.v8a"));
        vo.bind("wait", om.findStrict("ti.sysbios.family.arm.v8a.Cache.wait", "ti.sysbios.family.arm.v8a"));
        vo.bind("getEnabled", om.findStrict("ti.sysbios.family.arm.v8a.Cache.getEnabled", "ti.sysbios.family.arm.v8a"));
        vo.bind("invL1pAll", om.findStrict("ti.sysbios.family.arm.v8a.Cache.invL1pAll", "ti.sysbios.family.arm.v8a"));
        vo.bind("wbAll", om.findStrict("ti.sysbios.family.arm.v8a.Cache.wbAll", "ti.sysbios.family.arm.v8a"));
        vo.bind("wbInvAll", om.findStrict("ti.sysbios.family.arm.v8a.Cache.wbInvAll", "ti.sysbios.family.arm.v8a"));
        vo.bind("initModuleState", om.findStrict("ti.sysbios.family.arm.v8a.Cache.initModuleState", "ti.sysbios.family.arm.v8a"));
        vo.bind("startup", om.findStrict("ti.sysbios.family.arm.v8a.Cache.startup", "ti.sysbios.family.arm.v8a"));
        vo.bind("disableL1D", om.findStrict("ti.sysbios.family.arm.v8a.Cache.disableL1D", "ti.sysbios.family.arm.v8a"));
        vo.bind("disableL1P", om.findStrict("ti.sysbios.family.arm.v8a.Cache.disableL1P", "ti.sysbios.family.arm.v8a"));
        vo.bind("enableL1D", om.findStrict("ti.sysbios.family.arm.v8a.Cache.enableL1D", "ti.sysbios.family.arm.v8a"));
        vo.bind("enableL1P", om.findStrict("ti.sysbios.family.arm.v8a.Cache.enableL1P", "ti.sysbios.family.arm.v8a"));
        vo.bind("enableSmp", om.findStrict("ti.sysbios.family.arm.v8a.Cache.enableSmp", "ti.sysbios.family.arm.v8a"));
        vo.bind("invL1d", om.findStrict("ti.sysbios.family.arm.v8a.Cache.invL1d", "ti.sysbios.family.arm.v8a"));
        vo.bind("invL1p", om.findStrict("ti.sysbios.family.arm.v8a.Cache.invL1p", "ti.sysbios.family.arm.v8a"));
        vo.bind("getCacheLevelInfo", om.findStrict("ti.sysbios.family.arm.v8a.Cache.getCacheLevelInfo", "ti.sysbios.family.arm.v8a"));
        vo.bind("$$fxntab", Global.newArray("ti_sysbios_family_arm_v8a_Cache_Module__startupDone__E", "ti_sysbios_family_arm_v8a_Cache_enable__E", "ti_sysbios_family_arm_v8a_Cache_disable__E", "ti_sysbios_family_arm_v8a_Cache_inv__E", "ti_sysbios_family_arm_v8a_Cache_wb__E", "ti_sysbios_family_arm_v8a_Cache_wbInv__E", "ti_sysbios_family_arm_v8a_Cache_wait__E", "ti_sysbios_family_arm_v8a_Cache_getEnabled__E", "ti_sysbios_family_arm_v8a_Cache_invL1pAll__E", "ti_sysbios_family_arm_v8a_Cache_wbAll__E", "ti_sysbios_family_arm_v8a_Cache_wbInvAll__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Cache", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Cache");
    }

    void Core$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Core", "ti.sysbios.family.arm.v8a");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Core.Module", "ti.sysbios.family.arm.v8a");
        vo.init2(po, "ti.sysbios.family.arm.v8a.Core", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sysbios.family.arm.v8a.Core$$capsule", "ti.sysbios.family.arm.v8a"));
        vo.bind("$package", om.findStrict("ti.sysbios.family.arm.v8a", "ti.sysbios.family.arm.v8a"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        mcfgs.add("Module__diagsEnabled");
        icfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        icfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        icfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        icfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        icfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        icfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        icfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        icfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn0");
        icfgs.add("Module__loggerFxn0");
        mcfgs.add("Module__loggerFxn1");
        icfgs.add("Module__loggerFxn1");
        mcfgs.add("Module__loggerFxn2");
        icfgs.add("Module__loggerFxn2");
        mcfgs.add("Module__loggerFxn4");
        icfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        icfgs.add("Module__loggerFxn8");
        mcfgs.add("Object__count");
        icfgs.add("Object__count");
        mcfgs.add("Object__heap");
        icfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        icfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        icfgs.add("Object__table");
        mcfgs.add("numCores");
        mcfgs.add("id");
        mcfgs.add("baseClusterId");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sysbios.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sysbios.family.arm.v8a")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("getId", om.findStrict("ti.sysbios.family.arm.v8a.Core.getId", "ti.sysbios.family.arm.v8a"));
        vo.bind("interruptCore", om.findStrict("ti.sysbios.family.arm.v8a.Core.interruptCore", "ti.sysbios.family.arm.v8a"));
        vo.bind("lock", om.findStrict("ti.sysbios.family.arm.v8a.Core.lock", "ti.sysbios.family.arm.v8a"));
        vo.bind("unlock", om.findStrict("ti.sysbios.family.arm.v8a.Core.unlock", "ti.sysbios.family.arm.v8a"));
        vo.bind("hwiDisable", om.findStrict("ti.sysbios.family.arm.v8a.Core.hwiDisable", "ti.sysbios.family.arm.v8a"));
        vo.bind("hwiEnable", om.findStrict("ti.sysbios.family.arm.v8a.Core.hwiEnable", "ti.sysbios.family.arm.v8a"));
        vo.bind("hwiRestore", om.findStrict("ti.sysbios.family.arm.v8a.Core.hwiRestore", "ti.sysbios.family.arm.v8a"));
        vo.bind("getClusterId", om.findStrict("ti.sysbios.family.arm.v8a.Core.getClusterId", "ti.sysbios.family.arm.v8a"));
        vo.bind("getRevisionNumber", om.findStrict("ti.sysbios.family.arm.v8a.Core.getRevisionNumber", "ti.sysbios.family.arm.v8a"));
        vo.bind("reset", om.findStrict("ti.sysbios.family.arm.v8a.Core.reset", "ti.sysbios.family.arm.v8a"));
        vo.bind("disableCaches", om.findStrict("ti.sysbios.family.arm.v8a.Core.disableCaches", "ti.sysbios.family.arm.v8a"));
        vo.bind("getGicrBaseAddr", om.findStrict("ti.sysbios.family.arm.v8a.Core.getGicrBaseAddr", "ti.sysbios.family.arm.v8a"));
        vo.bind("$$fxntab", Global.newArray("ti_sysbios_family_arm_v8a_Core_Module__startupDone__E", "ti_sysbios_family_arm_v8a_Core_getId__E", "ti_sysbios_family_arm_v8a_Core_interruptCore__E", "ti_sysbios_family_arm_v8a_Core_lock__E", "ti_sysbios_family_arm_v8a_Core_unlock__E", "ti_sysbios_family_arm_v8a_Core_hwiDisable__E", "ti_sysbios_family_arm_v8a_Core_hwiEnable__E", "ti_sysbios_family_arm_v8a_Core_hwiRestore__E", "ti_sysbios_family_arm_v8a_Core_getClusterId__E", "ti_sysbios_family_arm_v8a_Core_getRevisionNumber__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Core", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Core");
    }

    void Mmu$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Mmu", "ti.sysbios.family.arm.v8a");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Mmu.Module", "ti.sysbios.family.arm.v8a");
        vo.init2(po, "ti.sysbios.family.arm.v8a.Mmu", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sysbios.family.arm.v8a.Mmu$$capsule", "ti.sysbios.family.arm.v8a"));
        vo.bind("$package", om.findStrict("ti.sysbios.family.arm.v8a", "ti.sysbios.family.arm.v8a"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        mcfgs.add("Module__diagsEnabled");
        icfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        icfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        icfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        icfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        icfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        icfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        icfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        icfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn0");
        icfgs.add("Module__loggerFxn0");
        mcfgs.add("Module__loggerFxn1");
        icfgs.add("Module__loggerFxn1");
        mcfgs.add("Module__loggerFxn2");
        icfgs.add("Module__loggerFxn2");
        mcfgs.add("Module__loggerFxn4");
        icfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        icfgs.add("Module__loggerFxn8");
        mcfgs.add("Object__count");
        icfgs.add("Object__count");
        mcfgs.add("Object__heap");
        icfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        icfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        icfgs.add("Object__table");
        vo.bind("AttrIndx", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx", "ti.sysbios.family.arm.v8a"));
        vo.bind("DescriptorType", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.DescriptorType", "ti.sysbios.family.arm.v8a"));
        vo.bind("GranuleSize", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.GranuleSize", "ti.sysbios.family.arm.v8a"));
        vo.bind("Shareable", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.Shareable", "ti.sysbios.family.arm.v8a"));
        vo.bind("AccessPerm", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AccessPerm", "ti.sysbios.family.arm.v8a"));
        vo.bind("InitFuncPtr", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.InitFuncPtr", "ti.sysbios.family.arm.v8a"));
        vo.bind("MapAttrs", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.MapAttrs", "ti.sysbios.family.arm.v8a"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v8a.Mmu.MapAttrs", "ti.sysbios.family.arm.v8a"));
        mcfgs.add("A_nullPointer");
        mcfgs.add("A_vaddrOutOfRange");
        mcfgs.add("A_paddrOutOfRange");
        mcfgs.add("A_unalignedVaddr");
        mcfgs.add("A_unalignedPaddr");
        mcfgs.add("A_unalignedSize");
        mcfgs.add("defaultMapAttrs");
        mcfgs.add("enableMMU");
        mcfgs.add("granuleSize");
        mcfgs.add("MAIR0");
        mcfgs.add("MAIR1");
        mcfgs.add("MAIR2");
        mcfgs.add("MAIR3");
        mcfgs.add("MAIR4");
        mcfgs.add("MAIR5");
        mcfgs.add("MAIR6");
        mcfgs.add("MAIR7");
        mcfgs.add("initFunc");
        mcfgs.add("tableArrayLen");
        vo.bind("ConfigInfo", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.ConfigInfo", "ti.sysbios.family.arm.v8a"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v8a.Mmu.ConfigInfo", "ti.sysbios.family.arm.v8a"));
        mcfgs.add("configInfo");
        icfgs.add("configInfo");
        vo.bind("Module_State", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.Module_State", "ti.sysbios.family.arm.v8a"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v8a.Mmu.Module_State", "ti.sysbios.family.arm.v8a"));
        vo.bind("AttrIndx_MAIR0", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR0", "ti.sysbios.family.arm.v8a"));
        vo.bind("AttrIndx_MAIR1", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR1", "ti.sysbios.family.arm.v8a"));
        vo.bind("AttrIndx_MAIR2", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR2", "ti.sysbios.family.arm.v8a"));
        vo.bind("AttrIndx_MAIR3", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR3", "ti.sysbios.family.arm.v8a"));
        vo.bind("AttrIndx_MAIR4", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR4", "ti.sysbios.family.arm.v8a"));
        vo.bind("AttrIndx_MAIR5", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR5", "ti.sysbios.family.arm.v8a"));
        vo.bind("AttrIndx_MAIR6", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR6", "ti.sysbios.family.arm.v8a"));
        vo.bind("AttrIndx_MAIR7", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AttrIndx_MAIR7", "ti.sysbios.family.arm.v8a"));
        vo.bind("DescriptorType_INVALID0", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.DescriptorType_INVALID0", "ti.sysbios.family.arm.v8a"));
        vo.bind("DescriptorType_BLOCK", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.DescriptorType_BLOCK", "ti.sysbios.family.arm.v8a"));
        vo.bind("DescriptorType_INVALID1", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.DescriptorType_INVALID1", "ti.sysbios.family.arm.v8a"));
        vo.bind("DescriptorType_TABLE", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.DescriptorType_TABLE", "ti.sysbios.family.arm.v8a"));
        vo.bind("GranuleSize_4KB", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.GranuleSize_4KB", "ti.sysbios.family.arm.v8a"));
        vo.bind("GranuleSize_16KB", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.GranuleSize_16KB", "ti.sysbios.family.arm.v8a"));
        vo.bind("GranuleSize_64KB", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.GranuleSize_64KB", "ti.sysbios.family.arm.v8a"));
        vo.bind("Shareable_NONE", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.Shareable_NONE", "ti.sysbios.family.arm.v8a"));
        vo.bind("Shareable_OUTER", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.Shareable_OUTER", "ti.sysbios.family.arm.v8a"));
        vo.bind("Shareable_INNER", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.Shareable_INNER", "ti.sysbios.family.arm.v8a"));
        vo.bind("AccessPerm_PRIV_RW_USER_NONE", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AccessPerm_PRIV_RW_USER_NONE", "ti.sysbios.family.arm.v8a"));
        vo.bind("AccessPerm_PRIV_RW_USER_RW", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AccessPerm_PRIV_RW_USER_RW", "ti.sysbios.family.arm.v8a"));
        vo.bind("AccessPerm_PRIV_RO_USER_NONE", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AccessPerm_PRIV_RO_USER_NONE", "ti.sysbios.family.arm.v8a"));
        vo.bind("AccessPerm_PRIV_RO_USER_RO", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.AccessPerm_PRIV_RO_USER_RO", "ti.sysbios.family.arm.v8a"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sysbios.family.arm.v8a")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("enable", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.enable", "ti.sysbios.family.arm.v8a"));
        vo.bind("initMapAttrs", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.initMapAttrs", "ti.sysbios.family.arm.v8a"));
        vo.bind("isEnabled", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.isEnabled", "ti.sysbios.family.arm.v8a"));
        vo.bind("map", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.map", "ti.sysbios.family.arm.v8a"));
        vo.bind("setMAIR", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.setMAIR", "ti.sysbios.family.arm.v8a"));
        vo.bind("startup", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.startup", "ti.sysbios.family.arm.v8a"));
        vo.bind("tlbInvAll", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.tlbInvAll", "ti.sysbios.family.arm.v8a"));
        vo.bind("disable", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.disable", "ti.sysbios.family.arm.v8a"));
        vo.bind("disableI", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.disableI", "ti.sysbios.family.arm.v8a"));
        vo.bind("enableI", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.enableI", "ti.sysbios.family.arm.v8a"));
        vo.bind("addBlockEntry", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.addBlockEntry", "ti.sysbios.family.arm.v8a"));
        vo.bind("addTableEntry", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.addTableEntry", "ti.sysbios.family.arm.v8a"));
        vo.bind("allocTable", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.allocTable", "ti.sysbios.family.arm.v8a"));
        vo.bind("freeTable", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.freeTable", "ti.sysbios.family.arm.v8a"));
        vo.bind("init", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.init", "ti.sysbios.family.arm.v8a"));
        vo.bind("readBlockEntry", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.readBlockEntry", "ti.sysbios.family.arm.v8a"));
        vo.bind("setMAIRAsm", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.setMAIRAsm", "ti.sysbios.family.arm.v8a"));
        vo.bind("tableWalk", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.tableWalk", "ti.sysbios.family.arm.v8a"));
        vo.bind("setTCR", om.findStrict("ti.sysbios.family.arm.v8a.Mmu.setTCR", "ti.sysbios.family.arm.v8a"));
        vo.bind("$$fxntab", Global.newArray("ti_sysbios_family_arm_v8a_Mmu_Module__startupDone__E", "ti_sysbios_family_arm_v8a_Mmu_enable__E", "ti_sysbios_family_arm_v8a_Mmu_initMapAttrs__E", "ti_sysbios_family_arm_v8a_Mmu_isEnabled__E", "ti_sysbios_family_arm_v8a_Mmu_map__E", "ti_sysbios_family_arm_v8a_Mmu_setMAIR__E", "ti_sysbios_family_arm_v8a_Mmu_startup__E", "ti_sysbios_family_arm_v8a_Mmu_tlbInvAll__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_nullPointer", "A_vaddrOutOfRange", "A_paddrOutOfRange", "A_unalignedVaddr", "A_unalignedPaddr", "A_unalignedSize"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Mmu.xdt");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        vo.bind("TEMPLATE$", "./Mmu.xdt");
        pkgV.bind("Mmu", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Mmu");
    }

    void Pmu$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Pmu", "ti.sysbios.family.arm.v8a");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Pmu.Module", "ti.sysbios.family.arm.v8a");
        vo.init2(po, "ti.sysbios.family.arm.v8a.Pmu", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sysbios.family.arm.v8a.Pmu$$capsule", "ti.sysbios.family.arm.v8a"));
        vo.bind("$package", om.findStrict("ti.sysbios.family.arm.v8a", "ti.sysbios.family.arm.v8a"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        mcfgs.add("Module__diagsEnabled");
        icfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        icfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        icfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        icfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        icfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        icfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        icfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        icfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn0");
        icfgs.add("Module__loggerFxn0");
        mcfgs.add("Module__loggerFxn1");
        icfgs.add("Module__loggerFxn1");
        mcfgs.add("Module__loggerFxn2");
        icfgs.add("Module__loggerFxn2");
        mcfgs.add("Module__loggerFxn4");
        icfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        icfgs.add("Module__loggerFxn8");
        mcfgs.add("Object__count");
        icfgs.add("Object__count");
        mcfgs.add("Object__heap");
        icfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        icfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        icfgs.add("Object__table");
        mcfgs.add("intNum");
        vo.bind("IntHandlerFuncPtr", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.IntHandlerFuncPtr", "ti.sysbios.family.arm.v8a"));
        vo.bind("PmuInfoView", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.PmuInfoView", "ti.sysbios.family.arm.v8a"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v8a.Pmu.PmuInfoView", "ti.sysbios.family.arm.v8a"));
        mcfgs.add("A_badIntNum");
        mcfgs.add("A_invalidCounterId");
        vo.bind("Module_State", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.Module_State", "ti.sysbios.family.arm.v8a"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v8a.Pmu.Module_State", "ti.sysbios.family.arm.v8a"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sysbios.family.arm.v8a")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("setInterruptFunc", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.setInterruptFunc", "ti.sysbios.family.arm.v8a"));
        vo.bind("startCounter", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.startCounter", "ti.sysbios.family.arm.v8a"));
        vo.bind("stopCounter", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.stopCounter", "ti.sysbios.family.arm.v8a"));
        vo.bind("resetCount", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.resetCount", "ti.sysbios.family.arm.v8a"));
        vo.bind("setCount", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.setCount", "ti.sysbios.family.arm.v8a"));
        vo.bind("configureCounter", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.configureCounter", "ti.sysbios.family.arm.v8a"));
        vo.bind("enableInterrupt", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.enableInterrupt", "ti.sysbios.family.arm.v8a"));
        vo.bind("disableInterrupt", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.disableInterrupt", "ti.sysbios.family.arm.v8a"));
        vo.bind("clearOverflowStatus", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.clearOverflowStatus", "ti.sysbios.family.arm.v8a"));
        vo.bind("getCount", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.getCount", "ti.sysbios.family.arm.v8a"));
        vo.bind("getNumCounters", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.getNumCounters", "ti.sysbios.family.arm.v8a"));
        vo.bind("getOverflowStatus", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.getOverflowStatus", "ti.sysbios.family.arm.v8a"));
        vo.bind("getEnabled", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.getEnabled", "ti.sysbios.family.arm.v8a"));
        vo.bind("startCounterI", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.startCounterI", "ti.sysbios.family.arm.v8a"));
        vo.bind("stopCounterI", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.stopCounterI", "ti.sysbios.family.arm.v8a"));
        vo.bind("resetCountI", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.resetCountI", "ti.sysbios.family.arm.v8a"));
        vo.bind("setCountI", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.setCountI", "ti.sysbios.family.arm.v8a"));
        vo.bind("enableInterruptI", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.enableInterruptI", "ti.sysbios.family.arm.v8a"));
        vo.bind("disableInterruptI", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.disableInterruptI", "ti.sysbios.family.arm.v8a"));
        vo.bind("clearOverflowStatusI", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.clearOverflowStatusI", "ti.sysbios.family.arm.v8a"));
        vo.bind("getCountI", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.getCountI", "ti.sysbios.family.arm.v8a"));
        vo.bind("getOverflowStatusI", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.getOverflowStatusI", "ti.sysbios.family.arm.v8a"));
        vo.bind("configureCounterI", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.configureCounterI", "ti.sysbios.family.arm.v8a"));
        vo.bind("clearOverflowStatusReg", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.clearOverflowStatusReg", "ti.sysbios.family.arm.v8a"));
        vo.bind("getOverflowStatusReg", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.getOverflowStatusReg", "ti.sysbios.family.arm.v8a"));
        vo.bind("initCounters", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.initCounters", "ti.sysbios.family.arm.v8a"));
        vo.bind("interruptHandler", om.findStrict("ti.sysbios.family.arm.v8a.Pmu.interruptHandler", "ti.sysbios.family.arm.v8a"));
        vo.bind("$$fxntab", Global.newArray("ti_sysbios_family_arm_v8a_Pmu_Module__startupDone__E", "ti_sysbios_family_arm_v8a_Pmu_setInterruptFunc__E", "ti_sysbios_family_arm_v8a_Pmu_startCounter__E", "ti_sysbios_family_arm_v8a_Pmu_stopCounter__E", "ti_sysbios_family_arm_v8a_Pmu_resetCount__E", "ti_sysbios_family_arm_v8a_Pmu_setCount__E", "ti_sysbios_family_arm_v8a_Pmu_configureCounter__E", "ti_sysbios_family_arm_v8a_Pmu_enableInterrupt__E", "ti_sysbios_family_arm_v8a_Pmu_disableInterrupt__E", "ti_sysbios_family_arm_v8a_Pmu_clearOverflowStatus__E", "ti_sysbios_family_arm_v8a_Pmu_getCount__E", "ti_sysbios_family_arm_v8a_Pmu_getNumCounters__E", "ti_sysbios_family_arm_v8a_Pmu_getOverflowStatus__E", "ti_sysbios_family_arm_v8a_Pmu_getEnabled__E", "ti_sysbios_family_arm_v8a_Pmu_startCounterI__E", "ti_sysbios_family_arm_v8a_Pmu_stopCounterI__E", "ti_sysbios_family_arm_v8a_Pmu_resetCountI__E", "ti_sysbios_family_arm_v8a_Pmu_setCountI__E", "ti_sysbios_family_arm_v8a_Pmu_enableInterruptI__E", "ti_sysbios_family_arm_v8a_Pmu_disableInterruptI__E", "ti_sysbios_family_arm_v8a_Pmu_clearOverflowStatusI__E", "ti_sysbios_family_arm_v8a_Pmu_getCountI__E", "ti_sysbios_family_arm_v8a_Pmu_getOverflowStatusI__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray("A_badIntNum", "A_invalidCounterId"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Pmu", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Pmu");
    }

    void TaskSupport$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v8a.TaskSupport", "ti.sysbios.family.arm.v8a");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.TaskSupport.Module", "ti.sysbios.family.arm.v8a");
        vo.init2(po, "ti.sysbios.family.arm.v8a.TaskSupport", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sysbios.family.arm.v8a.TaskSupport$$capsule", "ti.sysbios.family.arm.v8a"));
        vo.bind("$package", om.findStrict("ti.sysbios.family.arm.v8a", "ti.sysbios.family.arm.v8a"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        mcfgs.add("Module__diagsEnabled");
        icfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        icfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        icfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        icfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        icfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        icfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        icfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        icfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn0");
        icfgs.add("Module__loggerFxn0");
        mcfgs.add("Module__loggerFxn1");
        icfgs.add("Module__loggerFxn1");
        mcfgs.add("Module__loggerFxn2");
        icfgs.add("Module__loggerFxn2");
        mcfgs.add("Module__loggerFxn4");
        icfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        icfgs.add("Module__loggerFxn8");
        mcfgs.add("Object__count");
        icfgs.add("Object__count");
        mcfgs.add("Object__heap");
        icfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        icfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        icfgs.add("Object__table");
        vo.bind("FuncPtr", om.findStrict("ti.sysbios.interfaces.ITaskSupport.FuncPtr", "ti.sysbios.family.arm.v8a"));
        mcfgs.add("defaultStackSize");
        mcfgs.add("stackAlignment");
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sysbios.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sysbios.family.arm.v8a")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("start", om.findStrict("ti.sysbios.family.arm.v8a.TaskSupport.start", "ti.sysbios.family.arm.v8a"));
        vo.bind("swap", om.findStrict("ti.sysbios.family.arm.v8a.TaskSupport.swap", "ti.sysbios.family.arm.v8a"));
        vo.bind("checkStack", om.findStrict("ti.sysbios.family.arm.v8a.TaskSupport.checkStack", "ti.sysbios.family.arm.v8a"));
        vo.bind("stackUsed", om.findStrict("ti.sysbios.family.arm.v8a.TaskSupport.stackUsed", "ti.sysbios.family.arm.v8a"));
        vo.bind("getStackAlignment", om.findStrict("ti.sysbios.family.arm.v8a.TaskSupport.getStackAlignment", "ti.sysbios.family.arm.v8a"));
        vo.bind("getDefaultStackSize", om.findStrict("ti.sysbios.family.arm.v8a.TaskSupport.getDefaultStackSize", "ti.sysbios.family.arm.v8a"));
        vo.bind("$$fxntab", Global.newArray("ti_sysbios_family_arm_v8a_TaskSupport_Module__startupDone__E", "ti_sysbios_family_arm_v8a_TaskSupport_start__E", "ti_sysbios_family_arm_v8a_TaskSupport_swap__E", "ti_sysbios_family_arm_v8a_TaskSupport_checkStack__E", "ti_sysbios_family_arm_v8a_TaskSupport_stackUsed__E", "ti_sysbios_family_arm_v8a_TaskSupport_getStackAlignment__E", "ti_sysbios_family_arm_v8a_TaskSupport_getDefaultStackSize__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 0);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("TaskSupport", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TaskSupport");
    }

    void Timer$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Timer", "ti.sysbios.family.arm.v8a");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Timer.Module", "ti.sysbios.family.arm.v8a");
        vo.init2(po, "ti.sysbios.family.arm.v8a.Timer", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sysbios.family.arm.v8a.Timer$$capsule", "ti.sysbios.family.arm.v8a"));
        vo.bind("Instance", om.findStrict("ti.sysbios.family.arm.v8a.Timer.Instance", "ti.sysbios.family.arm.v8a"));
        vo.bind("Params", om.findStrict("ti.sysbios.family.arm.v8a.Timer.Params", "ti.sysbios.family.arm.v8a"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sysbios.family.arm.v8a.Timer.Params", "ti.sysbios.family.arm.v8a")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sysbios.family.arm.v8a.Timer.Handle", "ti.sysbios.family.arm.v8a"));
        vo.bind("$package", om.findStrict("ti.sysbios.family.arm.v8a", "ti.sysbios.family.arm.v8a"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        mcfgs.add("Module__diagsEnabled");
        icfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        icfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        icfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        icfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        icfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        icfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        icfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        icfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn0");
        icfgs.add("Module__loggerFxn0");
        mcfgs.add("Module__loggerFxn1");
        icfgs.add("Module__loggerFxn1");
        mcfgs.add("Module__loggerFxn2");
        icfgs.add("Module__loggerFxn2");
        mcfgs.add("Module__loggerFxn4");
        icfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        icfgs.add("Module__loggerFxn8");
        mcfgs.add("Object__count");
        icfgs.add("Object__count");
        mcfgs.add("Object__heap");
        icfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        icfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        icfgs.add("Object__table");
        vo.bind("FuncPtr", om.findStrict("ti.sysbios.interfaces.ITimer.FuncPtr", "ti.sysbios.family.arm.v8a"));
        vo.bind("StartMode", om.findStrict("ti.sysbios.interfaces.ITimer.StartMode", "ti.sysbios.family.arm.v8a"));
        vo.bind("RunMode", om.findStrict("ti.sysbios.interfaces.ITimer.RunMode", "ti.sysbios.family.arm.v8a"));
        vo.bind("Status", om.findStrict("ti.sysbios.interfaces.ITimer.Status", "ti.sysbios.family.arm.v8a"));
        vo.bind("PeriodType", om.findStrict("ti.sysbios.interfaces.ITimer.PeriodType", "ti.sysbios.family.arm.v8a"));
        vo.bind("BasicView", om.findStrict("ti.sysbios.family.arm.v8a.Timer.BasicView", "ti.sysbios.family.arm.v8a"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v8a.Timer.BasicView", "ti.sysbios.family.arm.v8a"));
        vo.bind("ModuleView", om.findStrict("ti.sysbios.family.arm.v8a.Timer.ModuleView", "ti.sysbios.family.arm.v8a"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v8a.Timer.ModuleView", "ti.sysbios.family.arm.v8a"));
        mcfgs.add("E_invalidTimer");
        mcfgs.add("E_notAvailable");
        mcfgs.add("E_invalidHwiMask");
        mcfgs.add("E_cannotSupport");
        mcfgs.add("intNumDef");
        mcfgs.add("anyMask");
        mcfgs.add("availMask");
        mcfgs.add("intFreq");
        mcfgs.add("vlabErrata");
        mcfgs.add("startupNeeded");
        icfgs.add("startupNeeded");
        vo.bind("Instance_State", om.findStrict("ti.sysbios.family.arm.v8a.Timer.Instance_State", "ti.sysbios.family.arm.v8a"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v8a.Timer.Instance_State", "ti.sysbios.family.arm.v8a"));
        vo.bind("Module_State", om.findStrict("ti.sysbios.family.arm.v8a.Timer.Module_State", "ti.sysbios.family.arm.v8a"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v8a.Timer.Module_State", "ti.sysbios.family.arm.v8a"));
        vo.bind("StartMode_AUTO", om.findStrict("ti.sysbios.interfaces.ITimer.StartMode_AUTO", "ti.sysbios.family.arm.v8a"));
        vo.bind("StartMode_USER", om.findStrict("ti.sysbios.interfaces.ITimer.StartMode_USER", "ti.sysbios.family.arm.v8a"));
        vo.bind("RunMode_CONTINUOUS", om.findStrict("ti.sysbios.interfaces.ITimer.RunMode_CONTINUOUS", "ti.sysbios.family.arm.v8a"));
        vo.bind("RunMode_ONESHOT", om.findStrict("ti.sysbios.interfaces.ITimer.RunMode_ONESHOT", "ti.sysbios.family.arm.v8a"));
        vo.bind("RunMode_DYNAMIC", om.findStrict("ti.sysbios.interfaces.ITimer.RunMode_DYNAMIC", "ti.sysbios.family.arm.v8a"));
        vo.bind("Status_INUSE", om.findStrict("ti.sysbios.interfaces.ITimer.Status_INUSE", "ti.sysbios.family.arm.v8a"));
        vo.bind("Status_FREE", om.findStrict("ti.sysbios.interfaces.ITimer.Status_FREE", "ti.sysbios.family.arm.v8a"));
        vo.bind("PeriodType_MICROSECS", om.findStrict("ti.sysbios.interfaces.ITimer.PeriodType_MICROSECS", "ti.sysbios.family.arm.v8a"));
        vo.bind("PeriodType_COUNTS", om.findStrict("ti.sysbios.interfaces.ITimer.PeriodType_COUNTS", "ti.sysbios.family.arm.v8a"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sysbios.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sysbios.family.arm.v8a")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", om.has("ti.sysbios.family.arm.v8a.Timer$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sysbios$family$arm$v8a$Timer$$__initObject"));
        }//isCFG
        vo.bind("getNumTimers", om.findStrict("ti.sysbios.family.arm.v8a.Timer.getNumTimers", "ti.sysbios.family.arm.v8a"));
        vo.bind("getStatus", om.findStrict("ti.sysbios.family.arm.v8a.Timer.getStatus", "ti.sysbios.family.arm.v8a"));
        vo.bind("startup", om.findStrict("ti.sysbios.family.arm.v8a.Timer.startup", "ti.sysbios.family.arm.v8a"));
        vo.bind("oneShotStub", om.findStrict("ti.sysbios.family.arm.v8a.Timer.oneShotStub", "ti.sysbios.family.arm.v8a"));
        vo.bind("periodicStub", om.findStrict("ti.sysbios.family.arm.v8a.Timer.periodicStub", "ti.sysbios.family.arm.v8a"));
        vo.bind("getHandle", om.findStrict("ti.sysbios.family.arm.v8a.Timer.getHandle", "ti.sysbios.family.arm.v8a"));
        vo.bind("initDevice", om.findStrict("ti.sysbios.family.arm.v8a.Timer.initDevice", "ti.sysbios.family.arm.v8a"));
        vo.bind("postInit", om.findStrict("ti.sysbios.family.arm.v8a.Timer.postInit", "ti.sysbios.family.arm.v8a"));
        vo.bind("checkOverflow", om.findStrict("ti.sysbios.family.arm.v8a.Timer.checkOverflow", "ti.sysbios.family.arm.v8a"));
        vo.bind("readPhyCtrl", om.findStrict("ti.sysbios.family.arm.v8a.Timer.readPhyCtrl", "ti.sysbios.family.arm.v8a"));
        vo.bind("readPhyCnt", om.findStrict("ti.sysbios.family.arm.v8a.Timer.readPhyCnt", "ti.sysbios.family.arm.v8a"));
        vo.bind("writePhyCtrl", om.findStrict("ti.sysbios.family.arm.v8a.Timer.writePhyCtrl", "ti.sysbios.family.arm.v8a"));
        vo.bind("writePhyCmpVal", om.findStrict("ti.sysbios.family.arm.v8a.Timer.writePhyCmpVal", "ti.sysbios.family.arm.v8a"));
        vo.bind("readVirtCtrl", om.findStrict("ti.sysbios.family.arm.v8a.Timer.readVirtCtrl", "ti.sysbios.family.arm.v8a"));
        vo.bind("readVirtCnt", om.findStrict("ti.sysbios.family.arm.v8a.Timer.readVirtCnt", "ti.sysbios.family.arm.v8a"));
        vo.bind("tickReconfigSmp", om.findStrict("ti.sysbios.family.arm.v8a.Timer.tickReconfigSmp", "ti.sysbios.family.arm.v8a"));
        vo.bind("writeVirtCtrl", om.findStrict("ti.sysbios.family.arm.v8a.Timer.writeVirtCtrl", "ti.sysbios.family.arm.v8a"));
        vo.bind("writeVirtCmpVal", om.findStrict("ti.sysbios.family.arm.v8a.Timer.writeVirtCmpVal", "ti.sysbios.family.arm.v8a"));
        vo.bind("$$fxntab", Global.newArray("ti_sysbios_family_arm_v8a_Timer_Handle__label__E", "ti_sysbios_family_arm_v8a_Timer_Module__startupDone__E", "ti_sysbios_family_arm_v8a_Timer_Object__create__E", "ti_sysbios_family_arm_v8a_Timer_Object__delete__E", "ti_sysbios_family_arm_v8a_Timer_Object__get__E", "ti_sysbios_family_arm_v8a_Timer_Object__first__E", "ti_sysbios_family_arm_v8a_Timer_Object__next__E", "ti_sysbios_family_arm_v8a_Timer_Params__init__E", "ti_sysbios_family_arm_v8a_Timer_getNumTimers__E", "ti_sysbios_family_arm_v8a_Timer_getStatus__E", "ti_sysbios_family_arm_v8a_Timer_startup__E", "ti_sysbios_family_arm_v8a_Timer_getMaxTicks__E", "ti_sysbios_family_arm_v8a_Timer_setNextTick__E", "ti_sysbios_family_arm_v8a_Timer_start__E", "ti_sysbios_family_arm_v8a_Timer_stop__E", "ti_sysbios_family_arm_v8a_Timer_setPeriod__E", "ti_sysbios_family_arm_v8a_Timer_setPeriodMicroSecs__E", "ti_sysbios_family_arm_v8a_Timer_getPeriod__E", "ti_sysbios_family_arm_v8a_Timer_getCount__E", "ti_sysbios_family_arm_v8a_Timer_getFreq__E", "ti_sysbios_family_arm_v8a_Timer_getFunc__E", "ti_sysbios_family_arm_v8a_Timer_setFunc__E", "ti_sysbios_family_arm_v8a_Timer_trigger__E", "ti_sysbios_family_arm_v8a_Timer_getExpiredCounts__E", "ti_sysbios_family_arm_v8a_Timer_getExpiredTicks__E", "ti_sysbios_family_arm_v8a_Timer_getCurrentTick__E", "ti_sysbios_family_arm_v8a_Timer_oneShotStub__E", "ti_sysbios_family_arm_v8a_Timer_periodicStub__E", "ti_sysbios_family_arm_v8a_Timer_getHandle__E", "ti_sysbios_family_arm_v8a_Timer_reconfig__E", "ti_sysbios_family_arm_v8a_Timer_setPeriod64__E", "ti_sysbios_family_arm_v8a_Timer_setPeriodMicroSecs64__E", "ti_sysbios_family_arm_v8a_Timer_getPeriod64__E", "ti_sysbios_family_arm_v8a_Timer_getCount64__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray("E_invalidTimer", "E_notAvailable", "E_invalidHwiMask", "E_cannotSupport"));
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sysbios.family.arm.v8a.Timer.Object", "ti.sysbios.family.arm.v8a"));
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Timer", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Timer");
    }

    void TimestampProvider$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v8a.TimestampProvider", "ti.sysbios.family.arm.v8a");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v8a.TimestampProvider.Module", "ti.sysbios.family.arm.v8a");
        vo.init2(po, "ti.sysbios.family.arm.v8a.TimestampProvider", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sysbios.family.arm.v8a.TimestampProvider$$capsule", "ti.sysbios.family.arm.v8a"));
        vo.bind("$package", om.findStrict("ti.sysbios.family.arm.v8a", "ti.sysbios.family.arm.v8a"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        mcfgs.add("Module__diagsEnabled");
        icfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        icfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        icfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        icfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        icfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        icfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        icfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        icfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn0");
        icfgs.add("Module__loggerFxn0");
        mcfgs.add("Module__loggerFxn1");
        icfgs.add("Module__loggerFxn1");
        mcfgs.add("Module__loggerFxn2");
        icfgs.add("Module__loggerFxn2");
        mcfgs.add("Module__loggerFxn4");
        icfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        icfgs.add("Module__loggerFxn8");
        mcfgs.add("Object__count");
        icfgs.add("Object__count");
        mcfgs.add("Object__heap");
        icfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        icfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        icfgs.add("Object__table");
        vo.bind("Module_View", om.findStrict("ti.sysbios.family.arm.v8a.TimestampProvider.Module_View", "ti.sysbios.family.arm.v8a"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v8a.TimestampProvider.Module_View", "ti.sysbios.family.arm.v8a"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sysbios.interfaces");
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sysbios.family.arm.v8a")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 0);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", 1);
        }//isCFG
        vo.bind("get32", om.findStrict("ti.sysbios.family.arm.v8a.TimestampProvider.get32", "ti.sysbios.family.arm.v8a"));
        vo.bind("get64", om.findStrict("ti.sysbios.family.arm.v8a.TimestampProvider.get64", "ti.sysbios.family.arm.v8a"));
        vo.bind("getFreq", om.findStrict("ti.sysbios.family.arm.v8a.TimestampProvider.getFreq", "ti.sysbios.family.arm.v8a"));
        vo.bind("initCCNT", om.findStrict("ti.sysbios.family.arm.v8a.TimestampProvider.initCCNT", "ti.sysbios.family.arm.v8a"));
        vo.bind("get64I", om.findStrict("ti.sysbios.family.arm.v8a.TimestampProvider.get64I", "ti.sysbios.family.arm.v8a"));
        vo.bind("$$fxntab", Global.newArray("ti_sysbios_family_arm_v8a_TimestampProvider_Module__startupDone__E", "ti_sysbios_family_arm_v8a_TimestampProvider_get32__E", "ti_sysbios_family_arm_v8a_TimestampProvider_get64__E", "ti_sysbios_family_arm_v8a_TimestampProvider_getFreq__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("TimestampProvider", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("TimestampProvider");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
            Object srcP = ((XScriptO)om.findStrict("xdc.runtime.IInstance", "ti.sysbios.family.arm.v8a")).findStrict("PARAMS", "ti.sysbios.family.arm.v8a");
            Scriptable dstP;

            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sysbios.family.arm.v8a.Timer", "ti.sysbios.family.arm.v8a")).findStrict("PARAMS", "ti.sysbios.family.arm.v8a");
            Global.put(dstP, "instance", srcP);
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sysbios.family.arm.v8a.Cache", "ti.sysbios.family.arm.v8a"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sysbios.family.arm.v8a.Core", "ti.sysbios.family.arm.v8a"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sysbios.family.arm.v8a.Mmu", "ti.sysbios.family.arm.v8a"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sysbios.family.arm.v8a.Pmu", "ti.sysbios.family.arm.v8a"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sysbios.family.arm.v8a.TaskSupport", "ti.sysbios.family.arm.v8a"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sysbios.family.arm.v8a.Timer", "ti.sysbios.family.arm.v8a"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sysbios.family.arm.v8a.TimestampProvider", "ti.sysbios.family.arm.v8a"));
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Cache", "ti.sysbios.family.arm.v8a");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Cache Info", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE_DATA"), "viewInitFxn", "viewInitCacheInfo", "structName", "CacheInfoView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Pmu", "ti.sysbios.family.arm.v8a");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Pmu Info", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE_DATA"), "viewInitFxn", "viewInitPmuInfo", "structName", "PmuInfoView")})}))));
        }//isCFG
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v8a.Timer", "ti.sysbios.family.arm.v8a");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")}), Global.newArray(new Object[]{"Module", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE"), "viewInitFxn", "viewInitModule", "structName", "ModuleView")})}))));
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sysbios.family.arm.v8a.Cache")).bless();
        ((Value.Obj)om.getv("ti.sysbios.family.arm.v8a.Core")).bless();
        ((Value.Obj)om.getv("ti.sysbios.family.arm.v8a.Mmu")).bless();
        ((Value.Obj)om.getv("ti.sysbios.family.arm.v8a.Pmu")).bless();
        ((Value.Obj)om.getv("ti.sysbios.family.arm.v8a.TaskSupport")).bless();
        ((Value.Obj)om.getv("ti.sysbios.family.arm.v8a.Timer")).bless();
        ((Value.Obj)om.getv("ti.sysbios.family.arm.v8a.TimestampProvider")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sysbios.family.arm.v8a")).add(pkgV);
    }

    public void exec( Scriptable xdcO, Session ses )
    {
        this.xdcO = xdcO;
        this.ses = ses;
        om = (Value.Obj)xdcO.get("om", null);

        Object o = om.geto("$name");
        String s = o instanceof String ? (String)o : null;
        isCFG = s != null && s.equals("cfg");
        isROV = s != null && s.equals("rov");

        $$IMPORTS();
        $$OBJECTS();
        Cache$$OBJECTS();
        Core$$OBJECTS();
        Mmu$$OBJECTS();
        Pmu$$OBJECTS();
        TaskSupport$$OBJECTS();
        Timer$$OBJECTS();
        TimestampProvider$$OBJECTS();
        Cache$$CONSTS();
        Core$$CONSTS();
        Mmu$$CONSTS();
        Pmu$$CONSTS();
        TaskSupport$$CONSTS();
        Timer$$CONSTS();
        TimestampProvider$$CONSTS();
        Cache$$CREATES();
        Core$$CREATES();
        Mmu$$CREATES();
        Pmu$$CREATES();
        TaskSupport$$CREATES();
        Timer$$CREATES();
        TimestampProvider$$CREATES();
        Cache$$FUNCTIONS();
        Core$$FUNCTIONS();
        Mmu$$FUNCTIONS();
        Pmu$$FUNCTIONS();
        TaskSupport$$FUNCTIONS();
        Timer$$FUNCTIONS();
        TimestampProvider$$FUNCTIONS();
        Cache$$SIZES();
        Core$$SIZES();
        Mmu$$SIZES();
        Pmu$$SIZES();
        TaskSupport$$SIZES();
        Timer$$SIZES();
        TimestampProvider$$SIZES();
        Cache$$TYPES();
        Core$$TYPES();
        Mmu$$TYPES();
        Pmu$$TYPES();
        TaskSupport$$TYPES();
        Timer$$TYPES();
        TimestampProvider$$TYPES();
        if (isROV) {
            Cache$$ROV();
            Core$$ROV();
            Mmu$$ROV();
            Pmu$$ROV();
            TaskSupport$$ROV();
            Timer$$ROV();
            TimestampProvider$$ROV();
        }//isROV
        $$SINGLETONS();
        Cache$$SINGLETONS();
        Core$$SINGLETONS();
        Mmu$$SINGLETONS();
        Pmu$$SINGLETONS();
        TaskSupport$$SINGLETONS();
        Timer$$SINGLETONS();
        TimestampProvider$$SINGLETONS();
        $$INITIALIZATION();
    }
}

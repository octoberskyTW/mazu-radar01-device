/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-E10
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class host_platforms_macos
{
    static final String VERS = "@(#) xdc-E10\n";

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
        Global.callFxn("loadPackage", xdcO, "xdc.platform");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("host.platforms.macos.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("host.platforms.macos", new Value.Obj("host.platforms.macos", pkgP));
    }

    void Platform$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("host.platforms.macos.Platform.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("host.platforms.macos.Platform", new Value.Obj("host.platforms.macos.Platform", po));
        pkgV.bind("Platform", vo);
        // decls 
        om.bind("host.platforms.macos.Platform.Board", om.findStrict("xdc.platform.IPlatform.Board", "host.platforms.macos"));
        om.bind("host.platforms.macos.Platform.Memory", om.findStrict("xdc.platform.IPlatform.Memory", "host.platforms.macos"));
        // insts 
        Object insP = om.bind("host.platforms.macos.Platform.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("host.platforms.macos.Platform$$Object", new Proto.Obj());
        om.bind("host.platforms.macos.Platform.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("host.platforms.macos.Platform$$Params", new Proto.Obj());
        om.bind("host.platforms.macos.Platform.Params", new Proto.Str(po, true));
    }

    void Intel80586$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("host.platforms.macos.Intel80586.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("host.platforms.macos.Intel80586", new Value.Obj("host.platforms.macos.Intel80586", po));
        pkgV.bind("Intel80586", vo);
        // decls 
        // insts 
        Object insP = om.bind("host.platforms.macos.Intel80586.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("host.platforms.macos.Intel80586$$Object", new Proto.Obj());
        om.bind("host.platforms.macos.Intel80586.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("host.platforms.macos.Intel80586$$Params", new Proto.Obj());
        om.bind("host.platforms.macos.Intel80586.Params", new Proto.Str(po, true));
    }

    void Platform$$CONSTS()
    {
        // module Platform
    }

    void Intel80586$$CONSTS()
    {
        // module Intel80586
    }

    void Platform$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("host.platforms.macos.Platform$$create", new Proto.Fxn(om.findStrict("host.platforms.macos.Platform.Module", "host.platforms.macos"), om.findStrict("host.platforms.macos.Platform.Instance", "host.platforms.macos"), 2, 1, false));
                fxn.addArg(0, "name", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("host.platforms.macos.Platform.Params", "host.platforms.macos"), Global.newObject());
        sb = new StringBuilder();
        sb.append("host$platforms$macos$Platform$$create = function( name, __params ) {\n");
            sb.append("var __mod = xdc.om['host.platforms.macos.Platform'];\n");
            sb.append("var __inst = xdc.om['host.platforms.macos.Platform.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['host.platforms.macos']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {name:name});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.externalMemoryMap = __mod.PARAMS.externalMemoryMap;\n");
            sb.append("__inst.customMemoryMap = __mod.PARAMS.customMemoryMap;\n");
            sb.append("__inst.renameMap = __mod.PARAMS.renameMap;\n");
            sb.append("__inst.dataMemory = __mod.PARAMS.dataMemory;\n");
            sb.append("__inst.codeMemory = __mod.PARAMS.codeMemory;\n");
            sb.append("__inst.stackMemory = __mod.PARAMS.stackMemory;\n");
            sb.append("__inst.sectMap = __mod.PARAMS.sectMap;\n");
            sb.append("__inst.peripherals = __mod.PARAMS.peripherals;\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [name]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("host.platforms.macos.Platform$$construct", new Proto.Fxn(om.findStrict("host.platforms.macos.Platform.Module", "host.platforms.macos"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("host.platforms.macos.Platform$$Object", "host.platforms.macos"), null);
                fxn.addArg(1, "name", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("host.platforms.macos.Platform.Params", "host.platforms.macos"), Global.newObject());
        sb = new StringBuilder();
        sb.append("host$platforms$macos$Platform$$construct = function( __obj, name, __params ) {\n");
            sb.append("var __mod = xdc.om['host.platforms.macos.Platform'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {name:name});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.externalMemoryMap = __mod.PARAMS.externalMemoryMap;\n");
            sb.append("__inst.customMemoryMap = __mod.PARAMS.customMemoryMap;\n");
            sb.append("__inst.renameMap = __mod.PARAMS.renameMap;\n");
            sb.append("__inst.dataMemory = __mod.PARAMS.dataMemory;\n");
            sb.append("__inst.codeMemory = __mod.PARAMS.codeMemory;\n");
            sb.append("__inst.stackMemory = __mod.PARAMS.stackMemory;\n");
            sb.append("__inst.sectMap = __mod.PARAMS.sectMap;\n");
            sb.append("__inst.peripherals = __mod.PARAMS.peripherals;\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Intel80586$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("host.platforms.macos.Intel80586$$create", new Proto.Fxn(om.findStrict("host.platforms.macos.Intel80586.Module", "host.platforms.macos"), om.findStrict("host.platforms.macos.Intel80586.Instance", "host.platforms.macos"), 2, 1, false));
                fxn.addArg(0, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("host.platforms.macos.Intel80586.Params", "host.platforms.macos"), Global.newObject());
        sb = new StringBuilder();
        sb.append("host$platforms$macos$Intel80586$$create = function( revision, __params ) {\n");
            sb.append("var __mod = xdc.om['host.platforms.macos.Intel80586'];\n");
            sb.append("var __inst = xdc.om['host.platforms.macos.Intel80586.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['host.platforms.macos']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.peripherals = __mod.PARAMS.peripherals;\n");
            sb.append("__inst.deviceHeader = __mod.PARAMS.deviceHeader;\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [revision]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("host.platforms.macos.Intel80586$$construct", new Proto.Fxn(om.findStrict("host.platforms.macos.Intel80586.Module", "host.platforms.macos"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("host.platforms.macos.Intel80586$$Object", "host.platforms.macos"), null);
                fxn.addArg(1, "revision", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("host.platforms.macos.Intel80586.Params", "host.platforms.macos"), Global.newObject());
        sb = new StringBuilder();
        sb.append("host$platforms$macos$Intel80586$$construct = function( __obj, revision, __params ) {\n");
            sb.append("var __mod = xdc.om['host.platforms.macos.Intel80586'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {revision:revision});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.cpuCore = __mod.PARAMS.cpuCore;\n");
            sb.append("__inst.cpuCoreRevision = __mod.PARAMS.cpuCoreRevision;\n");
            sb.append("__inst.minProgUnitSize = __mod.PARAMS.minProgUnitSize;\n");
            sb.append("__inst.minDataUnitSize = __mod.PARAMS.minDataUnitSize;\n");
            sb.append("__inst.dataWordSize = __mod.PARAMS.dataWordSize;\n");
            sb.append("__inst.peripherals = __mod.PARAMS.peripherals;\n");
            sb.append("__inst.deviceHeader = __mod.PARAMS.deviceHeader;\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Platform$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Intel80586$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Platform$$SIZES()
    {
    }

    void Intel80586$$SIZES()
    {
    }

    void Platform$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "host/platforms/macos/Platform.xs");
        om.bind("host.platforms.macos.Platform$$capsule", cap);
        po = (Proto.Obj)om.findStrict("host.platforms.macos.Platform.Module", "host.platforms.macos");
        po.init("host.platforms.macos.Platform.Module", om.findStrict("xdc.platform.IPlatform.Module", "host.platforms.macos"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("BOARD", (Proto)om.findStrict("xdc.platform.IPlatform.Board", "host.platforms.macos"), Global.newObject("id", "0", "boardName", "intel-x86", "boardFamily", "intel-x86", "boardRevision", null), "rh");
        po.addFld("CPU", (Proto)om.findStrict("xdc.platform.IExeContext.Cpu", "host.platforms.macos"), Global.newObject("id", "0", "clockRate", 1000.0, "catalogName", "host.platforms.macos", "deviceName", "Intel80586", "revision", ""), "rh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("host.platforms.macos.Platform$$create", "host.platforms.macos"), Global.get("host$platforms$macos$Platform$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("host.platforms.macos.Platform$$construct", "host.platforms.macos"), Global.get("host$platforms$macos$Platform$$construct"));
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("host.platforms.macos.Platform$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("host.platforms.macos.Platform$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("host.platforms.macos.Platform$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("host.platforms.macos.Platform$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("host.platforms.macos.Platform.Instance", "host.platforms.macos");
        po.init("host.platforms.macos.Platform.Instance", om.findStrict("xdc.platform.IPlatform.Instance", "host.platforms.macos"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                fxn = Global.get(cap, "getCpuDataSheet");
                if (fxn != null) po.addFxn("getCpuDataSheet", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCpuDataSheet", "host.platforms.macos"), fxn);
                fxn = Global.get(cap, "getCreateArgs");
                if (fxn != null) po.addFxn("getCreateArgs", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCreateArgs", "host.platforms.macos"), fxn);
                fxn = Global.get(cap, "getExeContext");
                if (fxn != null) po.addFxn("getExeContext", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExeContext", "host.platforms.macos"), fxn);
                fxn = Global.get(cap, "getExecCmd");
                if (fxn != null) po.addFxn("getExecCmd", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExecCmd", "host.platforms.macos"), fxn);
                fxn = Global.get(cap, "getLinkTemplate");
                if (fxn != null) po.addFxn("getLinkTemplate", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getLinkTemplate", "host.platforms.macos"), fxn);
        po = (Proto.Obj)om.findStrict("host.platforms.macos.Platform$$Params", "host.platforms.macos");
        po.init("host.platforms.macos.Platform.Params", om.findStrict("xdc.platform.IPlatform$$Params", "host.platforms.macos"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po = (Proto.Obj)om.findStrict("host.platforms.macos.Platform$$Object", "host.platforms.macos");
        po.init("host.platforms.macos.Platform.Object", om.findStrict("host.platforms.macos.Platform.Instance", "host.platforms.macos"));
                fxn = Global.get(cap, "getCpuDataSheet");
                if (fxn != null) po.addFxn("getCpuDataSheet", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCpuDataSheet", "host.platforms.macos"), fxn);
                fxn = Global.get(cap, "getCreateArgs");
                if (fxn != null) po.addFxn("getCreateArgs", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCreateArgs", "host.platforms.macos"), fxn);
                fxn = Global.get(cap, "getExeContext");
                if (fxn != null) po.addFxn("getExeContext", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExeContext", "host.platforms.macos"), fxn);
                fxn = Global.get(cap, "getExecCmd");
                if (fxn != null) po.addFxn("getExecCmd", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExecCmd", "host.platforms.macos"), fxn);
                fxn = Global.get(cap, "getLinkTemplate");
                if (fxn != null) po.addFxn("getLinkTemplate", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getLinkTemplate", "host.platforms.macos"), fxn);
    }

    void Intel80586$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "host/platforms/macos/Intel80586.xs");
        om.bind("host.platforms.macos.Intel80586$$capsule", cap);
        po = (Proto.Obj)om.findStrict("host.platforms.macos.Intel80586.Module", "host.platforms.macos");
        po.init("host.platforms.macos.Intel80586.Module", om.findStrict("xdc.platform.ICpuDataSheet.Module", "host.platforms.macos"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFxn("create", (Proto.Fxn)om.findStrict("host.platforms.macos.Intel80586$$create", "host.platforms.macos"), Global.get("host$platforms$macos$Intel80586$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("host.platforms.macos.Intel80586$$construct", "host.platforms.macos"), Global.get("host$platforms$macos$Intel80586$$construct"));
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("host.platforms.macos.Intel80586$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("host.platforms.macos.Intel80586$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("host.platforms.macos.Intel80586$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("host.platforms.macos.Intel80586$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("host.platforms.macos.Intel80586.Instance", "host.platforms.macos");
        po.init("host.platforms.macos.Intel80586.Instance", om.findStrict("xdc.platform.ICpuDataSheet.Instance", "host.platforms.macos"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("cpuCore", $$T_Str, "586", "wh");
        po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
        po.addFld("minProgUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("minDataUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("dataWordSize", Proto.Elm.newCNum("(xdc_Int)"), 4L, "wh");
        po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "host.platforms.macos")), Global.newArray(new Object[]{}), "wh");
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "host.platforms.macos"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "host.platforms.macos"), fxn);
        po = (Proto.Obj)om.findStrict("host.platforms.macos.Intel80586$$Params", "host.platforms.macos");
        po.init("host.platforms.macos.Intel80586.Params", om.findStrict("xdc.platform.ICpuDataSheet$$Params", "host.platforms.macos"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("cpuCore", $$T_Str, "586", "wh");
        po.addFld("cpuCoreRevision", $$T_Str, "1.0", "wh");
        po.addFld("minProgUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("minDataUnitSize", Proto.Elm.newCNum("(xdc_Int)"), 1L, "wh");
        po.addFld("dataWordSize", Proto.Elm.newCNum("(xdc_Int)"), 4L, "wh");
        po.addFld("memMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "host.platforms.macos")), Global.newArray(new Object[]{}), "wh");
        po = (Proto.Obj)om.findStrict("host.platforms.macos.Intel80586$$Object", "host.platforms.macos");
        po.init("host.platforms.macos.Intel80586.Object", om.findStrict("host.platforms.macos.Intel80586.Instance", "host.platforms.macos"));
                fxn = Global.get(cap, "getMemoryMap");
                if (fxn != null) po.addFxn("getMemoryMap", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getMemoryMap", "host.platforms.macos"), fxn);
                fxn = Global.get(cap, "getRegisterSet");
                if (fxn != null) po.addFxn("getRegisterSet", (Proto.Fxn)om.findStrict("xdc.platform.ICpuDataSheet$$getRegisterSet", "host.platforms.macos"), fxn);
    }

    void Platform$$ROV()
    {
    }

    void Intel80586$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("host.platforms.macos.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "host.platforms.macos"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "host/platforms/macos/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "host.platforms.macos"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "host.platforms.macos"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "host.platforms.macos"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "host.platforms.macos"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "host.platforms.macos"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "host.platforms.macos"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "host.platforms.macos", Value.DEFAULT, false);
        pkgV.bind("$name", "host.platforms.macos");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "host.platforms.macos.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.platform", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['host.platforms.macos'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('host.platforms.macos$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['host.platforms.macos$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['host.platforms.macos$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Platform$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("host.platforms.macos.Platform", "host.platforms.macos");
        po = (Proto.Obj)om.findStrict("host.platforms.macos.Platform.Module", "host.platforms.macos");
        vo.init2(po, "host.platforms.macos.Platform", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("host.platforms.macos.Platform$$capsule", "host.platforms.macos"));
        vo.bind("Instance", om.findStrict("host.platforms.macos.Platform.Instance", "host.platforms.macos"));
        vo.bind("Params", om.findStrict("host.platforms.macos.Platform.Params", "host.platforms.macos"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("host.platforms.macos.Platform.Params", "host.platforms.macos")).newInstance());
        vo.bind("$package", om.findStrict("host.platforms.macos", "host.platforms.macos"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("Board", om.findStrict("xdc.platform.IPlatform.Board", "host.platforms.macos"));
        tdefs.add(om.findStrict("xdc.platform.IPlatform.Board", "host.platforms.macos"));
        vo.bind("Memory", om.findStrict("xdc.platform.IPlatform.Memory", "host.platforms.macos"));
        tdefs.add(om.findStrict("xdc.platform.IPlatform.Memory", "host.platforms.macos"));
        vo.bind("MemoryMap", om.findStrict("xdc.platform.IPlatform.MemoryMap", "host.platforms.macos"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.platform");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "host.platforms.macos")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("host.platforms.macos.Platform$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("host.platforms.macos.Platform.Object", "host.platforms.macos"));
        pkgV.bind("Platform", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Platform");
    }

    void Intel80586$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("host.platforms.macos.Intel80586", "host.platforms.macos");
        po = (Proto.Obj)om.findStrict("host.platforms.macos.Intel80586.Module", "host.platforms.macos");
        vo.init2(po, "host.platforms.macos.Intel80586", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("host.platforms.macos.Intel80586$$capsule", "host.platforms.macos"));
        vo.bind("Instance", om.findStrict("host.platforms.macos.Intel80586.Instance", "host.platforms.macos"));
        vo.bind("Params", om.findStrict("host.platforms.macos.Intel80586.Params", "host.platforms.macos"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("host.platforms.macos.Intel80586.Params", "host.platforms.macos")).newInstance());
        vo.bind("$package", om.findStrict("host.platforms.macos", "host.platforms.macos"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.platform");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "host.platforms.macos")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("host.platforms.macos.Intel80586$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("host.platforms.macos.Intel80586.Object", "host.platforms.macos"));
        pkgV.bind("Intel80586", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Intel80586");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("host.platforms.macos.Platform", "host.platforms.macos"));
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("host.platforms.macos.Intel80586", "host.platforms.macos"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("host.platforms.macos.Platform")).bless();
        ((Value.Obj)om.getv("host.platforms.macos.Intel80586")).bless();
        ((Value.Arr)om.findStrict("$packages", "host.platforms.macos")).add(pkgV);
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
        Platform$$OBJECTS();
        Intel80586$$OBJECTS();
        Platform$$CONSTS();
        Intel80586$$CONSTS();
        Platform$$CREATES();
        Intel80586$$CREATES();
        Platform$$FUNCTIONS();
        Intel80586$$FUNCTIONS();
        Platform$$SIZES();
        Intel80586$$SIZES();
        Platform$$TYPES();
        Intel80586$$TYPES();
        if (isROV) {
            Platform$$ROV();
            Intel80586$$ROV();
        }//isROV
        $$SINGLETONS();
        Platform$$SINGLETONS();
        Intel80586$$SINGLETONS();
        $$INITIALIZATION();
    }
}

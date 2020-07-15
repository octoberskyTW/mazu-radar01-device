/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-D21
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class ti_platforms_evmTI814X
{
    static final String VERS = "@(#) xdc-D21\n";

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
        Global.callFxn("loadPackage", xdcO, "ti.catalog.c6000");
        Global.callFxn("loadPackage", xdcO, "ti.catalog.arm.cortexm3");
        Global.callFxn("loadPackage", xdcO, "ti.catalog.arm.cortexa8");
        Global.callFxn("loadPackage", xdcO, "xdc.platform");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.platforms.evmTI814X.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.platforms.evmTI814X", new Value.Obj("ti.platforms.evmTI814X", pkgP));
    }

    void Platform$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.platforms.evmTI814X.Platform.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.platforms.evmTI814X.Platform", new Value.Obj("ti.platforms.evmTI814X.Platform", po));
        pkgV.bind("Platform", vo);
        // decls 
        om.bind("ti.platforms.evmTI814X.Platform.Board", om.findStrict("xdc.platform.IPlatform.Board", "ti.platforms.evmTI814X"));
        om.bind("ti.platforms.evmTI814X.Platform.Memory", om.findStrict("xdc.platform.IPlatform.Memory", "ti.platforms.evmTI814X"));
        // insts 
        Object insP = om.bind("ti.platforms.evmTI814X.Platform.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.platforms.evmTI814X.Platform$$Object", new Proto.Obj());
        om.bind("ti.platforms.evmTI814X.Platform.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("ti.platforms.evmTI814X.Platform$$Params", new Proto.Obj());
        om.bind("ti.platforms.evmTI814X.Platform.Params", new Proto.Str(po, true));
    }

    void Platform$$CONSTS()
    {
        // module Platform
    }

    void Platform$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("ti.platforms.evmTI814X.Platform$$create", new Proto.Fxn(om.findStrict("ti.platforms.evmTI814X.Platform.Module", "ti.platforms.evmTI814X"), om.findStrict("ti.platforms.evmTI814X.Platform.Instance", "ti.platforms.evmTI814X"), 2, 1, false));
                fxn.addArg(0, "name", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("ti.platforms.evmTI814X.Platform.Params", "ti.platforms.evmTI814X"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$platforms$evmTI814X$Platform$$create = function( name, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.platforms.evmTI814X.Platform'];\n");
            sb.append("var __inst = xdc.om['ti.platforms.evmTI814X.Platform.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['ti.platforms.evmTI814X']);\n");
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
        fxn = (Proto.Fxn)om.bind("ti.platforms.evmTI814X.Platform$$construct", new Proto.Fxn(om.findStrict("ti.platforms.evmTI814X.Platform.Module", "ti.platforms.evmTI814X"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.platforms.evmTI814X.Platform$$Object", "ti.platforms.evmTI814X"), null);
                fxn.addArg(1, "name", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("ti.platforms.evmTI814X.Platform.Params", "ti.platforms.evmTI814X"), Global.newObject());
        sb = new StringBuilder();
        sb.append("ti$platforms$evmTI814X$Platform$$construct = function( __obj, name, __params ) {\n");
            sb.append("var __mod = xdc.om['ti.platforms.evmTI814X.Platform'];\n");
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

    void Platform$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Platform$$SIZES()
    {
    }

    void Platform$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/platforms/evmTI814X/Platform.xs");
        om.bind("ti.platforms.evmTI814X.Platform$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.platforms.evmTI814X.Platform.Module", "ti.platforms.evmTI814X");
        po.init("ti.platforms.evmTI814X.Platform.Module", om.findStrict("xdc.platform.IPlatform.Module", "ti.platforms.evmTI814X"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("BOARD", (Proto)om.findStrict("xdc.platform.IPlatform.Board", "ti.platforms.evmTI814X"), Global.newObject("id", "0", "boardName", "evmTI814X", "boardFamily", "evmTI814X", "boardRevision", null), "rh");
        po.addFld("GEM", (Proto)om.findStrict("xdc.platform.IExeContext.Cpu", "ti.platforms.evmTI814X"), Global.newObject("id", "0", "clockRate", 500.0, "catalogName", "ti.catalog.c6000", "deviceName", "TMS320TI814X", "revision", ""), "rh");
        po.addFld("DSS", (Proto)om.findStrict("xdc.platform.IExeContext.Cpu", "ti.platforms.evmTI814X"), Global.newObject("id", "1", "clockRate", 200.0, "catalogName", "ti.catalog.arm.cortexm3", "deviceName", "TMS320TI814X", "revision", "1.0"), "rh");
        po.addFld("GPP", (Proto)om.findStrict("xdc.platform.IExeContext.Cpu", "ti.platforms.evmTI814X"), Global.newObject("id", "2", "clockRate", 600.0, "catalogName", "ti.catalog.arm.cortexa8", "deviceName", "TMS320TI814X", "revision", "1.0"), "rh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("ti.platforms.evmTI814X.Platform$$create", "ti.platforms.evmTI814X"), Global.get("ti$platforms$evmTI814X$Platform$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.platforms.evmTI814X.Platform$$construct", "ti.platforms.evmTI814X"), Global.get("ti$platforms$evmTI814X$Platform$$construct"));
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.platforms.evmTI814X.Platform$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.platforms.evmTI814X.Platform$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.platforms.evmTI814X.Platform$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.platforms.evmTI814X.Platform$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("ti.platforms.evmTI814X.Platform.Instance", "ti.platforms.evmTI814X");
        po.init("ti.platforms.evmTI814X.Platform.Instance", om.findStrict("xdc.platform.IPlatform.Instance", "ti.platforms.evmTI814X"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("externalMemoryMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.platforms.evmTI814X")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DDR3_HOST", Global.newObject("comment", "DDR3 Memory reserved for use by the A8", "name", "DDR3_HOST", "base", 0x80000000L, "len", 0x0B000000L)}), Global.newArray(new Object[]{"DDR3_DSP", Global.newObject("comment", "DDR3 Memory reserved for use by the C674", "name", "DDR3_DSP", "base", 0x8B000000L, "len", 0x02000000L)}), Global.newArray(new Object[]{"DDR3_SR1", Global.newObject("comment", "DDR3 Memory reserved for use by SharedRegion 1", "name", "DDR3_SR1", "base", 0x8D000000L, "len", 0x00C00000L)}), Global.newArray(new Object[]{"DDR3_HDVPSS", Global.newObject("comment", "DDR3 Memory reserved for use by HDVPSS", "name", "DDR3_HDVPSS", "base", 0x8DC00000L, "len", 0x00200000L)}), Global.newArray(new Object[]{"DDR3_V4L2", Global.newObject("comment", "DDR3 Memory reserved for use by V4L2", "name", "DDR3_V4L2", "base", 0x8DE00000L, "len", 0x00200000L)}), Global.newArray(new Object[]{"DDR3_SR0", Global.newObject("comment", "DDR3 Memory reserved for use by SharedRegion 0", "name", "DDR3_SR0", "base", 0x8E000000L, "len", 0x01000000L)}), Global.newArray(new Object[]{"DDR3_M3", Global.newObject("comment", "DDR3 Memory reserved for use by the M3 core", "name", "DDR3_M3", "base", 0x8F000000L, "len", 0x01000000L)})}), "rh");
        po.addFld("l1PMode", $$T_Str, "32k", "wh");
        po.addFld("l1DMode", $$T_Str, "32k", "wh");
        po.addFld("l2Mode", $$T_Str, "0k", "wh");
                fxn = Global.get(cap, "getCpuDataSheet");
                if (fxn != null) po.addFxn("getCpuDataSheet", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCpuDataSheet", "ti.platforms.evmTI814X"), fxn);
                fxn = Global.get(cap, "getCreateArgs");
                if (fxn != null) po.addFxn("getCreateArgs", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCreateArgs", "ti.platforms.evmTI814X"), fxn);
                fxn = Global.get(cap, "getExeContext");
                if (fxn != null) po.addFxn("getExeContext", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExeContext", "ti.platforms.evmTI814X"), fxn);
                fxn = Global.get(cap, "getExecCmd");
                if (fxn != null) po.addFxn("getExecCmd", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExecCmd", "ti.platforms.evmTI814X"), fxn);
                fxn = Global.get(cap, "getLinkTemplate");
                if (fxn != null) po.addFxn("getLinkTemplate", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getLinkTemplate", "ti.platforms.evmTI814X"), fxn);
        po = (Proto.Obj)om.findStrict("ti.platforms.evmTI814X.Platform$$Params", "ti.platforms.evmTI814X");
        po.init("ti.platforms.evmTI814X.Platform.Params", om.findStrict("xdc.platform.IPlatform$$Params", "ti.platforms.evmTI814X"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("externalMemoryMap", new Proto.Map((Proto)om.findStrict("xdc.platform.IPlatform.Memory", "ti.platforms.evmTI814X")), Global.newArray(new Object[]{Global.newArray(new Object[]{"DDR3_HOST", Global.newObject("comment", "DDR3 Memory reserved for use by the A8", "name", "DDR3_HOST", "base", 0x80000000L, "len", 0x0B000000L)}), Global.newArray(new Object[]{"DDR3_DSP", Global.newObject("comment", "DDR3 Memory reserved for use by the C674", "name", "DDR3_DSP", "base", 0x8B000000L, "len", 0x02000000L)}), Global.newArray(new Object[]{"DDR3_SR1", Global.newObject("comment", "DDR3 Memory reserved for use by SharedRegion 1", "name", "DDR3_SR1", "base", 0x8D000000L, "len", 0x00C00000L)}), Global.newArray(new Object[]{"DDR3_HDVPSS", Global.newObject("comment", "DDR3 Memory reserved for use by HDVPSS", "name", "DDR3_HDVPSS", "base", 0x8DC00000L, "len", 0x00200000L)}), Global.newArray(new Object[]{"DDR3_V4L2", Global.newObject("comment", "DDR3 Memory reserved for use by V4L2", "name", "DDR3_V4L2", "base", 0x8DE00000L, "len", 0x00200000L)}), Global.newArray(new Object[]{"DDR3_SR0", Global.newObject("comment", "DDR3 Memory reserved for use by SharedRegion 0", "name", "DDR3_SR0", "base", 0x8E000000L, "len", 0x01000000L)}), Global.newArray(new Object[]{"DDR3_M3", Global.newObject("comment", "DDR3 Memory reserved for use by the M3 core", "name", "DDR3_M3", "base", 0x8F000000L, "len", 0x01000000L)})}), "rh");
        po.addFld("l1PMode", $$T_Str, "32k", "wh");
        po.addFld("l1DMode", $$T_Str, "32k", "wh");
        po.addFld("l2Mode", $$T_Str, "0k", "wh");
        po = (Proto.Obj)om.findStrict("ti.platforms.evmTI814X.Platform$$Object", "ti.platforms.evmTI814X");
        po.init("ti.platforms.evmTI814X.Platform.Object", om.findStrict("ti.platforms.evmTI814X.Platform.Instance", "ti.platforms.evmTI814X"));
                fxn = Global.get(cap, "getCpuDataSheet");
                if (fxn != null) po.addFxn("getCpuDataSheet", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCpuDataSheet", "ti.platforms.evmTI814X"), fxn);
                fxn = Global.get(cap, "getCreateArgs");
                if (fxn != null) po.addFxn("getCreateArgs", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCreateArgs", "ti.platforms.evmTI814X"), fxn);
                fxn = Global.get(cap, "getExeContext");
                if (fxn != null) po.addFxn("getExeContext", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExeContext", "ti.platforms.evmTI814X"), fxn);
                fxn = Global.get(cap, "getExecCmd");
                if (fxn != null) po.addFxn("getExecCmd", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExecCmd", "ti.platforms.evmTI814X"), fxn);
                fxn = Global.get(cap, "getLinkTemplate");
                if (fxn != null) po.addFxn("getLinkTemplate", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getLinkTemplate", "ti.platforms.evmTI814X"), fxn);
    }

    void Platform$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.platforms.evmTI814X.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.platforms.evmTI814X"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "ti.platforms.evmTI814X", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.platforms.evmTI814X");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.platforms.evmTI814X.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.catalog.c6000", Global.newArray()));
        imports.add(Global.newArray("ti.catalog.arm.cortexm3", Global.newArray()));
        imports.add(Global.newArray("ti.catalog.arm.cortexa8", Global.newArray()));
        imports.add(Global.newArray("xdc.platform", Global.newArray(1, 0, 1)));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.platforms.evmTI814X'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.platforms.evmTI814X$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.platforms.evmTI814X$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.platforms.evmTI814X$$stat$root'];\n");
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

        vo = (Value.Obj)om.findStrict("ti.platforms.evmTI814X.Platform", "ti.platforms.evmTI814X");
        po = (Proto.Obj)om.findStrict("ti.platforms.evmTI814X.Platform.Module", "ti.platforms.evmTI814X");
        vo.init2(po, "ti.platforms.evmTI814X.Platform", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.platforms.evmTI814X.Platform$$capsule", "ti.platforms.evmTI814X"));
        vo.bind("Instance", om.findStrict("ti.platforms.evmTI814X.Platform.Instance", "ti.platforms.evmTI814X"));
        vo.bind("Params", om.findStrict("ti.platforms.evmTI814X.Platform.Params", "ti.platforms.evmTI814X"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.platforms.evmTI814X.Platform.Params", "ti.platforms.evmTI814X")).newInstance());
        vo.bind("$package", om.findStrict("ti.platforms.evmTI814X", "ti.platforms.evmTI814X"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("Board", om.findStrict("xdc.platform.IPlatform.Board", "ti.platforms.evmTI814X"));
        tdefs.add(om.findStrict("xdc.platform.IPlatform.Board", "ti.platforms.evmTI814X"));
        vo.bind("Memory", om.findStrict("xdc.platform.IPlatform.Memory", "ti.platforms.evmTI814X"));
        tdefs.add(om.findStrict("xdc.platform.IPlatform.Memory", "ti.platforms.evmTI814X"));
        vo.bind("MemoryMap", om.findStrict("xdc.platform.IPlatform.MemoryMap", "ti.platforms.evmTI814X"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.platform");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.platforms.evmTI814X")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.platforms.evmTI814X.Platform$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.platforms.evmTI814X.Platform.Object", "ti.platforms.evmTI814X"));
        pkgV.bind("Platform", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Platform");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.platforms.evmTI814X.Platform", "ti.platforms.evmTI814X"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.platforms.evmTI814X.Platform")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.platforms.evmTI814X")).add(pkgV);
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
        Platform$$CONSTS();
        Platform$$CREATES();
        Platform$$FUNCTIONS();
        Platform$$SIZES();
        Platform$$TYPES();
        if (isROV) {
            Platform$$ROV();
        }//isROV
        $$SINGLETONS();
        Platform$$SINGLETONS();
        $$INITIALIZATION();
    }
}

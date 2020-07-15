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

public class ti_targets_arm_clang
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
        Global.callFxn("loadPackage", xdcO, "xdc.bld");
        Global.callFxn("loadPackage", xdcO, "ti.targets");
        Global.callFxn("loadPackage", xdcO, "ti.targets.arm.elf");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.targets.arm.clang.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.targets.arm.clang", new Value.Obj("ti.targets.arm.clang", pkgP));
    }

    void M33F$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.targets.arm.clang.M33F.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.targets.arm.clang.M33F", new Value.Obj("ti.targets.arm.clang.M33F", po));
        pkgV.bind("M33F", vo);
        // decls 
        om.bind("ti.targets.arm.clang.M33F.Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.clang"));
        om.bind("ti.targets.arm.clang.M33F.DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.clang"));
        om.bind("ti.targets.arm.clang.M33F.Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.clang"));
        om.bind("ti.targets.arm.clang.M33F.CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.clang"));
        om.bind("ti.targets.arm.clang.M33F.OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.clang"));
        om.bind("ti.targets.arm.clang.M33F.CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.clang"));
        om.bind("ti.targets.arm.clang.M33F.LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.clang"));
        om.bind("ti.targets.arm.clang.M33F.ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.clang"));
        om.bind("ti.targets.arm.clang.M33F.CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.clang"));
        om.bind("ti.targets.arm.clang.M33F.TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.clang"));
        om.bind("ti.targets.arm.clang.M33F.StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.clang"));
        om.bind("ti.targets.arm.clang.M33F.Command", om.findStrict("xdc.bld.ITarget2.Command", "ti.targets.arm.clang"));
        om.bind("ti.targets.arm.clang.M33F.Options", om.findStrict("xdc.bld.ITarget2.Options", "ti.targets.arm.clang"));
    }

    void M33F$$CONSTS()
    {
        // module M33F
    }

    void M33F$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void M33F$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void M33F$$SIZES()
    {
    }

    void M33F$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/targets/arm/clang/M33F.xs");
        om.bind("ti.targets.arm.clang.M33F$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.targets.arm.clang.M33F.Module", "ti.targets.arm.clang");
        po.init("ti.targets.arm.clang.M33F.Module", om.findStrict("ti.targets.arm.elf.IArm.Module", "ti.targets.arm.clang"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("name", $$T_Str, "M33F", "rh");
        po.addFld("suffix", $$T_Str, "m33f", "rh");
        po.addFld("isa", $$T_Str, "v8M", "rh");
        po.addFld("rts", $$T_Str, "ti.targets.arm.rtsarm", "rh");
        po.addFld("platform", $$T_Str, "ti.platforms.cortexM:MTL1_VSOC:1", "wh");
        po.addFld("stdInclude", $$T_Str, "ti/targets/arm/clang/std.h", "wh");
        po.addFld("model", (Proto)om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.clang"), Global.newObject("endian", "little", "codeModel", "thumb2", "shortEnums", true), "rh");
        po.addFld("cc", (Proto)om.findStrict("xdc.bld.ITarget2.Command", "ti.targets.arm.clang"), Global.newObject("cmd", "tiarmclang -c", "opts", "-mcpu=cortex-m33 -mfloat-abi=hard -mfpu=fpv5-sp-d16"), "rh");
        po.addFld("asm", (Proto)om.findStrict("xdc.bld.ITarget2.Command", "ti.targets.arm.clang"), Global.newObject("cmd", "tiarmclang -c -x assembler-with-cpp -mno-default-build-attributes", "opts", "-mcpu=cortex-m33 -mfloat-abi=hard -mfpu=fpv5-sp-d16"), "rh");
        po.addFld("lnk", (Proto)om.findStrict("xdc.bld.ITarget2.Command", "ti.targets.arm.clang"), Global.newObject("cmd", "tiarmclang", "opts", "-mcpu=cortex-m33 -mfloat-abi=hard -mfpu=fpv5-sp-d16"), "rh");
        po.addFld("ccOpts", (Proto)om.findStrict("xdc.bld.ITarget2.Options", "ti.targets.arm.clang"), Global.newObject("prefix", "", "suffix", ""), "wh");
        po.addFld("ccConfigOpts", (Proto)om.findStrict("xdc.bld.ITarget2.Options", "ti.targets.arm.clang"), Global.newObject("prefix", "$(ccOpts.prefix)", "suffix", "$(ccOpts.suffix)"), "wh");
        po.addFld("asmOpts", (Proto)om.findStrict("xdc.bld.ITarget2.Options", "ti.targets.arm.clang"), Global.newObject("prefix", "", "suffix", ""), "wh");
        po.addFld("lnkOpts", (Proto)om.findStrict("xdc.bld.ITarget2.Options", "ti.targets.arm.clang"), Global.newObject("prefix", "-Wl,-q -Wl,-u,_c_int00", "suffix", "-Wl,-w -Wl,-c -Wl,-m,$(XDCCFGDIR)/$@.map -l $(rootDir)/lib/generic/libc.a"), "wh");
        po.addFld("vers", (Proto)om.findStrict("xdc.bld.ITarget2.Command", "ti.targets.arm.clang"), Global.newObject("cmd", "tiarmclang", "opts", "--version"), "rh");
        po.addFld("includeOpts", $$T_Str, "", "wh");
        po.addFld("profiles", new Proto.Map((Proto)om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.clang")), Global.newArray(new Object[]{Global.newArray(new Object[]{"debug", Global.newObject("compileOpts", Global.newObject("copts", "-gdwarf-3", "defs", "-D_DEBUG_=1"), "linkOpts", "-gdwarf-3")}), Global.newArray(new Object[]{"release", Global.newObject("compileOpts", Global.newObject("copts", " -O2 "), "linkOpts", " ")})}), "wh");
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.targets.arm.clang.M33F$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.targets.arm.clang.M33F$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.targets.arm.clang.M33F$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
                fxn = Global.get(cap, "archive");
                if (fxn != null) po.addFxn("archive", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$archive", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "compile");
                if (fxn != null) po.addFxn("compile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$compile", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "scompile");
                if (fxn != null) po.addFxn("scompile", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$scompile", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "link");
                if (fxn != null) po.addFxn("link", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$link", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "getVersion");
                if (fxn != null) po.addFxn("getVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getVersion", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "getISAChain");
                if (fxn != null) po.addFxn("getISAChain", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$getISAChain", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "findSuffix");
                if (fxn != null) po.addFxn("findSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$findSuffix", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "selectSuffix");
                if (fxn != null) po.addFxn("selectSuffix", (Proto.Fxn)om.findStrict("xdc.bld.ITarget$$selectSuffix", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "genConstCustom");
                if (fxn != null) po.addFxn("genConstCustom", (Proto.Fxn)om.findStrict("xdc.bld.ITarget2$$genConstCustom", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "genVisibleData");
                if (fxn != null) po.addFxn("genVisibleData", (Proto.Fxn)om.findStrict("xdc.bld.ITarget2$$genVisibleData", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "genVisibleFxns");
                if (fxn != null) po.addFxn("genVisibleFxns", (Proto.Fxn)om.findStrict("xdc.bld.ITarget2$$genVisibleFxns", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "genVisibleLibFxns");
                if (fxn != null) po.addFxn("genVisibleLibFxns", (Proto.Fxn)om.findStrict("xdc.bld.ITarget2$$genVisibleLibFxns", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "getRawVersion");
                if (fxn != null) po.addFxn("getRawVersion", (Proto.Fxn)om.findStrict("xdc.bld.ITarget3$$getRawVersion", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "asmName");
                if (fxn != null) po.addFxn("asmName", (Proto.Fxn)om.findStrict("ti.targets.ITarget$$asmName", "ti.targets.arm.clang"), fxn);
    }

    void M33F$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.targets.arm.clang.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.targets.arm.clang"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/targets/arm/clang/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.targets.arm.clang"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.targets.arm.clang"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.targets.arm.clang", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.targets.arm.clang");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.targets.arm.clang.");
        pkgV.bind("$vers", Global.newArray(1, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("xdc.bld", Global.newArray()));
        imports.add(Global.newArray("ti.targets", Global.newArray()));
        imports.add(Global.newArray("ti.targets.arm.elf", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.targets.arm.clang'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.targets.arm.clang$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.targets.arm.clang$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.targets.arm.clang$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void M33F$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.targets.arm.clang.M33F", "ti.targets.arm.clang");
        po = (Proto.Obj)om.findStrict("ti.targets.arm.clang.M33F.Module", "ti.targets.arm.clang");
        vo.init2(po, "ti.targets.arm.clang.M33F", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.targets.arm.clang.M33F$$capsule", "ti.targets.arm.clang"));
        vo.bind("$package", om.findStrict("ti.targets.arm.clang", "ti.targets.arm.clang"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("Model", om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.clang"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Model", "ti.targets.arm.clang"));
        vo.bind("DebugGen", om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.clang"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.DebugGen", "ti.targets.arm.clang"));
        vo.bind("Extension", om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.clang"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.Extension", "ti.targets.arm.clang"));
        vo.bind("CompileOptions", om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.clang"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileOptions", "ti.targets.arm.clang"));
        vo.bind("OptionSet", om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.clang"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.OptionSet", "ti.targets.arm.clang"));
        vo.bind("CompileGoal", om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.clang"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CompileGoal", "ti.targets.arm.clang"));
        vo.bind("LinkGoal", om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.clang"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.LinkGoal", "ti.targets.arm.clang"));
        vo.bind("ArchiveGoal", om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.clang"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.ArchiveGoal", "ti.targets.arm.clang"));
        vo.bind("CommandSet", om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.clang"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.CommandSet", "ti.targets.arm.clang"));
        vo.bind("StringArray", om.findStrict("xdc.bld.ITarget.StringArray", "ti.targets.arm.clang"));
        vo.bind("TypeInfo", om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.clang"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.TypeInfo", "ti.targets.arm.clang"));
        vo.bind("StdTypes", om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.clang"));
        tdefs.add(om.findStrict("xdc.bld.ITarget.StdTypes", "ti.targets.arm.clang"));
        vo.bind("Command", om.findStrict("xdc.bld.ITarget2.Command", "ti.targets.arm.clang"));
        tdefs.add(om.findStrict("xdc.bld.ITarget2.Command", "ti.targets.arm.clang"));
        vo.bind("Options", om.findStrict("xdc.bld.ITarget2.Options", "ti.targets.arm.clang"));
        tdefs.add(om.findStrict("xdc.bld.ITarget2.Options", "ti.targets.arm.clang"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.targets.arm.elf");
        inherits.add("ti.targets");
        inherits.add("xdc.bld");
        inherits.add("xdc.bld");
        inherits.add("xdc.bld");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.targets.arm.clang")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.targets.arm.clang.M33F$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "xdc/bld/stddefs.xdt");
        atmap.seal("length");
        pkgV.bind("M33F", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("M33F");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.targets.arm.clang.M33F", "ti.targets.arm.clang"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.targets.arm.clang.M33F")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.targets.arm.clang")).add(pkgV);
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
        M33F$$OBJECTS();
        M33F$$CONSTS();
        M33F$$CREATES();
        M33F$$FUNCTIONS();
        M33F$$SIZES();
        M33F$$TYPES();
        if (isROV) {
            M33F$$ROV();
        }//isROV
        $$SINGLETONS();
        M33F$$SINGLETONS();
        $$INITIALIZATION();
    }
}

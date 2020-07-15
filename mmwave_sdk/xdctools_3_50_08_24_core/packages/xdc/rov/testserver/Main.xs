/* --COPYRIGHT--,EPL
 *  Copyright (c) 2016-2018 Texas Instruments Incorporated
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * --/COPYRIGHT--*/

var pw;
var Support = xdc.module("xdc.rov.testserver.Support");

var logFile = java.lang.System.getenv("XDC_ROV_TESTSERVER_LOG");

var debug = {
    init: function() {
        if (logFile != null && this.debugfile == null) {
            if (logFile == "-") {
                this.debugfile = java.lang.System.out;
            }
            else {
                var fos = new java.io.FileOutputStream(logFile, true);
                this.debugfile = new java.io.PrintStream(fos);
            }
        }
    },
    println: function(msg) {
        if (this.debugfile != null && this.verbose > 0) {
            this.debugfile.println(msg);
        }
    },
    flush: function() {
        if (this.debugfile != null) {
            this.debugfile.flush();
        }
    },
    close: function() {
        if (this.debugfile != null) {
            this.debugfile.flush();
            if (logFile != "-") {
                this.debugfile.close();
                this.debugfile = null;
            }
        }
    },
    stop: function() {
        if (this.debugfile != null) {
            this.debugfile.flush();
            this.debugfile = null;
        }
    }
};

/*
 *  ======== progress ========
 */
function getProgress(v)
{
    return function progress(msg) {
        if (v > 0) {
            pw.println("Working: " + msg);
            pw.flush();
        }
    }
}

/*
 *  ======== run ========
 */
function run(cmdr, args)
{
    debug.init();
    debug.println("\nstarting the " + this.$package + " ...");
    debug.println("    package path: " + xdc.curPath());

    pw = new java.io.PrintWriter(java.lang.System.out);
    var isr  = new java.io.InputStreamReader(java.lang.System.in);
    var br = new java.io.BufferedReader(isr);

    debug.println("executable: " + this.executable);
    debug.println("port: " + this.port);

    /* Turning on Program debug */
    if (this.verbose > 1) {
        xdc.jre.java.lang.System.setProperty("xdc.rov.traceEnable", "true");
    }

    if (java.io.File(this.executable).exists()) {
        var msg = "OK";
        debug.println("starting ROV model ...");
        var tokens = [];
        tokens[0] = "comm=DSLite:0:" + this.port;
        try {
            Support.startModel(this.executable, tokens, debug,
                getProgress(this.verbose));
        }
        catch (e) {
            var emsg = String(e).replace(
                                /JavaException:.*java.lang.Exception/g, "");
            msg = "Error: Failed to start ROV using '" + tokens
                + "':" + emsg;
        }
    }
    else {
        msg = "Error: The executable file '" + this.executable
            + "' doesn't exist";
    }
    pw.println(msg);
    pw.flush();

    var line;

    /* HACK to work around HW bug (LPRFTOOLS-292) */
//    xdc.global["DISABLE_READ_RTC"] = true; /* remove or set to false to remove the workaround */

    while (true) {
        print("waiting for a request ... (enter h for help)");

        /* close debug to allow log file deletion while
         * we wait for commands
         */
        debug.close();

        /* get next command */
        line = br.readLine();

        /* re-open log file (if necessary) */
        debug.init();
        debug.println("***" + line + "***");
        if (line == null) {
            break; /* input stream was closed, so we exit */
        }
        line = String(line);

        var start = java.lang.System.currentTimeMillis();

        /* execute new command */
        if (line == "e") {
            pw.println("OK");
            debug.println("Exiting " + this.$module.$name);
            break;
        }
        else if (line == "h") {
            pw.println("l             - lists available views");
            pw.println("v Module View - displays the specified view");
            pw.println("r             - run the executable");
            pw.println("p             - pause the executable");
            pw.println("e             - exit");
            pw.flush();
        }
        else if (line == "r") {
            Support.advance();
        }
        else if (line == "p") {
            Support.pause();
        }
        else if (line == "l") {
            var views = getViews();
            var ret = JSON.stringify(views);
            for (var prop in views) {
                pw.println("Module: " + prop);
                pw.print("    Views: ");
                for (var prop2 in views[prop].viewTabs) {
                    pw.print("    " + views[prop].viewTabs[prop2].name);
                }
                pw.println();
                pw.println();
            }
            pw.flush();
        }
        else if (line.indexOf("v ") == 0) {
            /* Requests for views are supplied as "v Module View"
             * strings.
             */
            var st1 = line.indexOf(" ");
            var st2 = line.indexOf(" ", st1 + 1);
            var mod = line.split(" ", 3)[1];
            var view = line.slice(st2 + 1);
            print("selected view: " + view);
            if (view == "undefined" || view == "null") {
                debug.println("Error: undefined or null view requested");
                view = "Raw";
            }
            var ret = getView(mod, view);
            if (typeof ret == "object") { /* this includes null */
                ret = Support.stringify(ret, "");
            }
            if (ret == undefined) {
                ret = "Error: " + mod
                      + " returned undefined for the view " + view;
            }

            pw.println(ret);
            pw.flush();
            debug.println(getStatusLines("Target errors detected:\n", "    "));
        }

        /* log time to execute command */
        debug.println("    ***" + line + "*** completed in "
            + (java.lang.System.currentTimeMillis() - start) + " ms");
    }

    /* exit this server */
    debug.println("exiting ROV server (" + this.$module.$name + ") ...");
    debug.close();

    br.close();
    pw.close();
    Support.close();

    /* explicitly exit: needed to work around a bug (probably in the
     * web socket library) that prevents the JVM from exiting due to
     * non-daemon thread created as part of the socket connection which
     * is not closed.
     */
    java.lang.System.exit(0);
}

/*
 *  ======== getViews ========
 *  The list of modules and views is returned as a map of arrays, where
 *  keys are module names and values are arrays of the structures:
 *  [{name:"view1", type:"view1_type"}, ... ,{name:"viewN", type:"viewN_type}]
 */
function getViews()
{
    var Program = xdc.module("xdc.rov.Program");
    var ret = {};

    debug.println("Generating the list of available views ...");
    for (var i = 0; i < Program.moduleNames.length; i++) {
        var modName = Program.moduleNames[i];
        var mod = Program.getModuleDesc(modName);
        var viewArgs = getViewArgs(mod);

        if (mod.loadFailed) {
            debug.println("module " + modName
                          + " failed to load: " + mod.loadFailedMsg);
            continue; /* skip modules that can't be found */
        }
        var tabs = Program.getSupportedTabs(modName);
        var tabArray = [];
        for (var j = 0; j < tabs.length; j++) {
            var viewtype = String(tabs[j].type);
            var tabName = tabs[j].name;
            tabArray[j] = {
                name:    tabName,
                type:    viewtype.substr(viewtype.lastIndexOf('.') + 1),
                columns: getViewColumns(modName, tabName, viewtype),
                argsId:  getViewArgsId(mod, tabName)
            };
        }

        var mviews = {viewArgs: viewArgs, viewTabs: tabArray};

        //debug.println(mod.name + " views: " + JSON.stringify(mviews,null,2));
        ret[modName] = mviews;
    }

    return (ret);
}

/*
 *  ======== getViewArgs ========
 *  Get a module-specific hashtable of argument descriptions
 *
 *  This hashtable is indexed by the value of the argsId property in
 *  a specific ROV tab for the module mod.
 */
function getViewArgs(mod)
{
    var result = {};

    if (mod.viewInfo && "argsMap" in mod.viewInfo) {
        var argsMap = mod.viewInfo.argsMap;
        for (var i = 0; i < argsMap.length; i++) {
            var argsRec = argsMap[i];
            var key = argsMap.$keys[i];
            var val = {
                description: argsRec.description,
                args: []
            };
            for (var j = 0; j < argsRec.args.length; j++) {
                var arg = argsRec.args[j];
                val.args.push({
                    name: arg.name,
                    type: arg.type,
                    value: arg.defaultValue
                });
            }
            result[key] = val;
        }
        if (false && argsMap.length > 0) {
            debug.println(mod.name + ".viewArgs: "
                          + JSON.stringify(result, null, 2));
        }
    }

    return (result);
}

/*
 *  ======== getViewArgsId ========
 *  Get the id/key into the module-specific viewArgs hashtable
 */
function getViewArgsId(mod, tabName)
{
    if (mod.viewInfo) {
        var view = mod.viewInfo.viewMap[tabName];
        if (view != null) {
            //debug.println("module " + mod.name + ":"
            //    + tabName + ".argsId = " + view.argsName);
            return (view.argsName);
        }
        else {
            /* if tabName is "Raw", view == null */
        }
    }

    return undefined;
}

/*
 *  ======== getViewColumns ========
 */
function getViewColumns(modName, tabName, tabType)
{
    var cols = [];

    if (tabType == "xdc.rov.ViewInfo.INSTANCE"
        || tabType == "xdc.rov.ViewInfo.MODULE") {
        /* address is not declared as part of module and instance views */
        cols = ["address"];
    }

    var mod = Program.getModuleDesc(modName);
    if (mod.cfg == null) {
        /* pure C module */
        var structName = mod.viewInfo.viewMap[tabName].structName;
        var dummy = new mod.useMod.$capsule[structName];
        for (var prop in dummy) {
            cols.push(prop);
        }
        return (cols);
    }

    if (tabName != "Raw") {
        var dummy = Program.newViewStruct(modName, tabName);
        for (var n in dummy) {
            cols.push(n);
        }
    }

    return (cols);
}

/*
 *  ======== getView ========
 */
function getView(mod, view)
{
    Program.resetMods();
    try {
        var viewType = Program.getViewType(mod, view);
        debug.println("Fetching " + mod + "." + view + " of type " + viewType);
        var ViewInfo = xdc.useModule("xdc.rov.ViewInfo");

        switch (String(viewType)) {
            case String(ViewInfo.MODULE):
                return (Program.scanModuleView(mod, view));
                break;
            case String(ViewInfo.INSTANCE):
                return (Program.scanInstanceView(mod, view));
                break;
            case String(ViewInfo.INSTANCE_DATA):
                return (Program.scanInstanceDataView(mod, view));
                break;
            case String(ViewInfo.MODULE_DATA):
                return (Program.scanModuleDataView(mod, view));
                break;
            case String(ViewInfo.RAW):
                return (Program.scanRawView(mod));
                break;
            case String(ViewInfo.TREE_TABLE):
                return (Program.scanTreeTableView(mod, view));
                break;
            case String(ViewInfo.TREE):
                return (Program.scanTreeView(mod, view));
                break;
            default:
                throw (new Error("Undefined view type: " + viewType));
                break;
        }
    }
    catch (e) {
        var msg = e.message;
        if (msg == null) {
            msg = String(e);
        }
        msg += getStatusLines("\n");
        debug.println("Fetch " + mod + "." + view + " of type " + viewType
              + " failed: " + msg);
        return ("Error: " + msg);
    }
}

/*
 *  ======== getStatusLines ========
 */
function getStatusLines(prefix, indent)
{
    prefix = prefix != null ? prefix : "";
    indent = indent != null ? indent : "";

    var result = "";
    var errs = Program.getStatusTable();
    for (var i = 0; i < errs.length; i++) {
        var e = errs[i];
        if (i == 0) result = prefix;
        result += indent + e.mod + ':' + e.tab + ':' + e.field
              + " (" + e.inst + "): " + e.message + '\n';
    }
    return (result);
}

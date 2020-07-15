/*
 *  ======== instance$meta$init ========
 *  Takes a handle to an Elf parser, which serves as the symbol table.
 */
function instance$meta$init(elf)
{
    this.$$bind('$symTab', elf);
}

/*
 *  ======== getSymbolValue ========
 *  This function returns the address of the requested symbol
 */
function getSymbolValue(symbolName)
{
    var Program = xdc.useModule('xdc.rov.Program');

    var val = this.$symTab.getSymbolValue(symbolName);

    if (val == -1) {
        Program.debugPrint("Failed to find symbol: '" + symbolName + "'!");
    }

    return (val);
}

/*
 *  ======== lookupDataSymbol ========
 *  This function returns an array of symbols that have the specified value.
 */
function lookupDataSymbol(addr)
{
    return (this.$symTab.lookupDataSymbol(addr));
}

/*
 *  ======== lookupFuncName ========
 *  Lookup the function name(s) at a given address.
 */
function lookupFuncName(addr)
{
    return (this.$symTab.lookupFuncName(addr));
}

/*
 *  ======== getISA ========
 */
function getISA()
{
    return (this.$symTab.getISA());
}

/*
 *  ======== getJavaImp ========
 */
function getJavaImp()
{
    throw new Error("getJavaImp called from:\n" + xdc.whereami());
}

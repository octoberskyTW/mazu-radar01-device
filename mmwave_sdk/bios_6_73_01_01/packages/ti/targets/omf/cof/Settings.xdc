/*
 *  Copyright 2018 by Texas Instruments Incorporated.
 *
 */

/*
 *  ======== Settings.xdc ========
 *
 */


/*!
 *  ======== Settings ========
 *  Allows selection between TI and MOTOROLA cof libraries.
 */
metaonly module Settings {

    /*! 
     * Mode: {TI, MOTOROLA}. 
     *
     * TI. The function getLibs() returns cof_ti.lib libraries.
     *
     * MOTOROLA. The function getLibs() returns cof_mot.lib libraries.
     */
    enum Mode {TI, MOTOROLA};

    /*! 
     * Determines the libraries contributed by this package. 
     * 
     * Default is TI
     */
    config Mode mode = TI;

}
/*
 *  @(#) ti.targets.omf.cof; 1,0,0,0; 7-20-2018 14:28:34; /db/ztree/library/trees/xdctargets/xdctargets-r09/src/ xlibrary

 */


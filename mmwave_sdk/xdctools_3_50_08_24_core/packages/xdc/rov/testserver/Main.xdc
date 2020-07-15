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

/*!
 *  ======== Main.xdc ========
 *  The xdc.rov.testserver displays ROV views to clients on the command line.
 *  The server expects that a CCS debugger is already started and an application
 *  is loaded.
 *
 *  The DSlite port must be known at the time the server is started. Therefore,
 *  when starting CCS, the environment variable TI_DS_WEBSOCKET_PORT must be set
 *  and that same port number must be supplied to xdc.rov.testserver.
 *
 *  Commands:
 *
 *  Start the server -
 *      xs xdc.rov.testserver --exec <full path> --port <port_number>
 *
 *  Get a list of Modules and Tabs
 *      l
 *
 *  Get a Module's View
 *      v Module View
 *
 *  Issue the command "Run" to the debugger
 *      r
 *
 *  Issue the command "Pause" to the debugger
 *      p
 *
 *  Exit xdc.rov.testserver
 *      e
 *
 */
metaonly module Main inherits xdc.tools.ICmd {

    override config String usage[] = [
        ' ',
        'Usage',
        '[--exec <executable>]',
        '[--port <DSLite Websocket port>]',
        '[-v <debug level>]',
        '[--help]',
        ' ',
    ];

instance:

    /*!
     *  ======== exec ========
     *
     *  Executable to run ROV on
     *
     */
    @CommandOption('exec')
    config String executable = "";

    /*!
     *  ======== port ========
     *
     *  DSLite port
     *
     *  Corresponds to the value in the environment variable
     *  TI_DS_WEBSOCKET_PORT. The variable must be set at the time CCS is
     *  started.
     */
    @CommandOption('port')
    config UInt port;

    /*!
     *  ======== verbose ========
     *
     *  Defines the amount of debug info
     *
     */
    @CommandOption('v')
    config UInt verbose = 0;
}

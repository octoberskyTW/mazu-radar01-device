# README for xdc.rov.testserver
-------------------------------

## Purpose
----------
The xdc.rov.testserver displays on the command line the conent of ROV views and a requested amount of debug information. The ROV views are displayed in the JSON format, exactly as they are sent to the ROV GUI display in CCS.

The test server expects that a CCS debugger is already started and an application
is loaded. There are no checks that verify that the executable loaded in the debugger and the executable supplied to the test server on the command line are the same application. It is the user's responsibility to ensure that the same executable is supplied to both.

The DSlite port number must also be supplied at the test server's command line. The easist way to have that port number available is to set the environment variable TI_DS_WEBSOCKET_PORT to a specific number (55000, for example) when starting CCS. Then, when starting the test server that same number is supplied as a parameter.

## Usage
--------
* Start the server -
      xs xdc.rov.testserver --exec `<full path>` --port `<DSLite port_number>` [-v `<debug level>`]

## Interactive Commands
-----------------------
* Get a list of Modules and Tabs

    `l`

* Get a Module's View

    `v Module View`

* Issue the command "Run" to the debugger

    `r`

* Issue the command "Pause" to the debugger

    `p`

* Exit xdc.rov.testserver

    `e`

## Example
----------
C:/temp>C:/ti/xdctools_3_50_05_12_core/xs --xdcpath=C:/ti/simplelink_msp432p4_sdk_1_60_00_12/kernel/tirtos/packages xdc.rov.testserver --exec C:/Users/a0868339/workspace_v7_3/timerled_MSP_EXP432P401R_tirtos_ccs/Debug/timerled_MSP_EXP432P401R_tirtos_ccs.out --port 55000

waiting for a request ... (enter h for help)  
`l`  

```javascript
Module: C.SPI  
    Views:     Instances    Attributes

Module: ti.sysbios.BIOS`
    Views:     Module    Scan for errors...    Raw

Module: ti.sysbios.family.arm.m3.Hwi
    Views:     Basic    Detailed    Module    Exception    Raw

Module: ti.sysbios.family.arm.msp432.Timer
    Views:     Basic    Device    Module    Raw
...
```

waiting for a request ... (enter h for help)  
`v C.SPI Instances`  

```javascript
{
   "elements": [
        {
            "address": "0x20008540",
            "address": "0x20008540",
            "transferComplete": "0x0",
            "transferMode": "SPI_MODE_BLOCKING",
            "spiMode": "SPI_MASTER",
            "isOpen": "false",
            "bitRate": "0",
            "clockPhase": "0",
            "clockPolarity": "0",
            "perfConstraintMask": "0",
            "dmaHandle": "0x0"
        },
        {
            "address": "0x20008588",
            "address": "0x20008588",
            "transferComplete": "0x0",
            "transferMode": "SPI_MODE_BLOCKING",
            "spiMode": "SPI_MASTER",
            "isOpen": "false",
            "bitRate": "0",
            "clockPhase": "0",
            "clockPolarity": "0",
            "perfConstraintMask": "0",
            "dmaHandle": "0x0"
        },
        {
            "address": "0x200085d0",
            "address": "0x200085d0",
            "transferComplete": "0x0",
            "transferMode": "SPI_MODE_BLOCKING",
            "spiMode": "SPI_MASTER",
            "isOpen": "false",
            "bitRate": "0",
            "clockPhase": "0",
            "clockPolarity": "0",
            "perfConstraintMask": "0",
            "dmaHandle": "0x0"
        },
        {
            "address": "0x20008618",
            "address": "0x20008618",
            "transferComplete": "0x0",
            "transferMode": "SPI_MODE_BLOCKING",
            "spiMode": "SPI_MASTER",
            "isOpen": "false",
            "bitRate": "0",
            "clockPhase": "0",
            "clockPolarity": "0",
            "perfConstraintMask": "0",
            "dmaHandle": "0x0"
        }
    ]
}
```

waiting for a request ... (enter h for help)  
`e`

OK  
C:/temp>


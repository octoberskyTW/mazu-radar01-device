#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /home/jake/Workspace/mazu-radar01-device/mmwave_sdk/bios_6_73_01_01/packages;/home/jake/Workspace/mazu-radar01-device/mmwave_sdk/mmwave_sdk_03_04_00_03/packages
override XDCROOT = /home/jake/Workspace/mazu-radar01-device/mmwave_sdk/xdctools_3_50_08_24_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /home/jake/Workspace/mazu-radar01-device/mmwave_sdk/bios_6_73_01_01/packages;/home/jake/Workspace/mazu-radar01-device/mmwave_sdk/mmwave_sdk_03_04_00_03/packages;/home/jake/Workspace/mazu-radar01-device/mmwave_sdk/xdctools_3_50_08_24_core/packages;..
HOSTOS = Linux
endif

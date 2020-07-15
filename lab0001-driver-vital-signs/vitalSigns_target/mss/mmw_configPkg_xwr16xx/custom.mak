## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,er4ft linker.cmd package/cfg/mss_mmw_per4ft.oer4ft

# To simplify configuro usage in makefiles:
#     o create a generic linker command file name 
#     o set modification times of compiler.opt* files to be greater than
#       or equal to the generated config header
#
linker.cmd: package/cfg/mss_mmw_per4ft.xdl
	$(SED) 's"^\"\(package/cfg/mss_mmw_per4ftcfg.cmd\)\"$""\"/home/jake/Workspace/mazu-radar01-device/lab0001-driver-vital-signs/vitalSigns_target/mss/mmw_configPkg_xwr16xx/\1\""' package/cfg/mss_mmw_per4ft.xdl > $@
	-$(SETDATE) -r:max package/cfg/mss_mmw_per4ft.h compiler.opt compiler.opt.defs

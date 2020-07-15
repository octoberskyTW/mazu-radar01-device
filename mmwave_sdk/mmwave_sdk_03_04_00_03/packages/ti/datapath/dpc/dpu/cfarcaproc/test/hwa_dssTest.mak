###################################################################################
# CFAR PROC Test
###################################################################################
.PHONY: cfarHwaDssTest cfarHwaDssTestClean

###################################################################################
# Setup the VPATH:
###################################################################################
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/cfarcaproc/test
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/utils/randomdatagenerator
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/utils/mathutils/src

###################################################################################
# The cfar PROC Test requires additional libraries
###################################################################################
HWACFARPROC_DSS_TEST_STD_LIBS = $(C674_COMMON_STD_LIB)								\
           				-llibedma_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) 		\
           				-llibhwa_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)       \
                        -llibtestlogger_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) \
						-llibcfarcaproc_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) \
						-llibdpedma_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)
HWACFARPROC_DSS_TEST_LOC_LIBS = $(C674_COMMON_LOC_LIB)								\
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/edma/lib 	\
           				-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/hwa/lib    \
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/utils/testlogger/lib \
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/cfarcaproc/lib \
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpedma/lib


###################################################################################
# Unit Test Files
###################################################################################
HWACFARPROC_DSS_TEST_CFG	 	 = test/dss.cfg
HWACFARPROC_DSS_TEST_CMD       = $(MMWAVE_SDK_INSTALL_PATH)/ti/platform/$(MMWAVE_SDK_DEVICE_TYPE)
HWACFARPROC_DSS_TEST_CONFIGPKG = test/c674_configPkg_$(MMWAVE_SDK_DEVICE_TYPE)
HWACFARPROC_DSS_TEST_MAP       = test/$(MMWAVE_SDK_DEVICE_TYPE)_cfarprochwa_dss.map
HWACFARPROC_DSS_TEST_OUT       = test/$(MMWAVE_SDK_DEVICE_TYPE)_cfarprochwa_dss.$(C674_EXE_EXT)
HWACFARPROC_DSS_TEST_BIN       = test/$(MMWAVE_SDK_DEVICE_TYPE)_cfarprochwa_dss.bin
HWACFARPROC_DSS_TEST_APP_CMD   = test/dss_cfarproc_linker.cmd
HWACFARPROC_DSS_TEST_SOURCES   = cfarprochwa_test_main.c \
								gen_rand_data.c \
								mathutils.c 
								

HWACFARPROC_DSS_TEST_DEPENDS 	 = $(addprefix $(PLATFORM_OBJDIR)/, $(HWACFARPROC_DSS_TEST_SOURCES:.c=.$(C674_DEP_EXT)))
HWACFARPROC_DSS_TEST_OBJECTS 	 = $(addprefix $(PLATFORM_OBJDIR)/, $(HWACFARPROC_DSS_TEST_SOURCES:.c=.$(C674_OBJ_EXT)))

OPTIMIZE_FOR_SPEED_OPTIONS := -o1 -o2 -o3 -O1 -O2 -O3


###################################################################################
# RTSC Configuration:
###################################################################################
hwaDssRTSC: $(HWACFARPROC_DSS_TEST_CFG)
	@echo 'Configuring RTSC packages...'
	$(XS) --xdcpath="$(XDCPATH)" xdc.tools.configuro $(C674_XSFLAGS) -o $(HWACFARPROC_DSS_TEST_CONFIGPKG) $(HWACFARPROC_DSS_TEST_CFG)
	@echo 'Finished configuring packages'
	@echo ' '

###################################################################################
# Build Unit Test:
###################################################################################
cfarHwaDssTest: BUILD_CONFIGPKG=$(HWACFARPROC_DSS_TEST_CONFIGPKG)
cfarHwaDssTest: C674_CFLAGS += --cmd_file=$(BUILD_CONFIGPKG)/compiler.opt
cfarHwaDssTest: C674_CFLAGS := $(filter-out $(OPTIMIZE_FOR_SPEED_OPTIONS),$(C674_CFLAGS))
cfarHwaDssTest: buildDirectories hwaDssRTSC $(HWACFARPROC_DSS_TEST_OBJECTS)
	$(C674_LD) $(C674_LDFLAGS) $(HWACFARPROC_DSS_TEST_LOC_LIBS) $(HWACFARPROC_DSS_TEST_STD_LIBS) \
   -l$(HWACFARPROC_DSS_TEST_CONFIGPKG)/linker.cmd --map_file=$(HWACFARPROC_DSS_TEST_MAP)   \
    $(HWACFARPROC_DSS_TEST_OBJECTS) $(PLATFORM_C674X_LINK_CMD) $(HWACFARPROC_DSS_TEST_APP_CMD) \
	$(C674_LD_RTS_FLAGS) -o $(HWACFARPROC_DSS_TEST_OUT)
	@echo '******************************************************************************'
	@echo 'Built the CFAR proc DSP Unit Test '
	@echo '******************************************************************************'

###################################################################################
# Cleanup Unit Test:
###################################################################################
cfarHwaDssTestClean:
	@echo 'Cleaning the cfar PROC DSP Unit Test objects'
	@$(DEL) $(HWACFARPROC_DSS_TEST_OBJECTS) $(HWACFARPROC_DSS_TEST_OUT) $(HWACFARPROC_DSS_TEST_BIN)
	@$(DEL) $(HWACFARPROC_DSS_TEST_MAP) $(HWACFARPROC_DSS_TEST_DEPENDS)
	@echo 'Cleaning the cfar PROC DSP Unit RTSC package'
	@$(DEL) $(HWACFARPROC_DSS_TEST_CONFIGPKG)
	@$(DEL) $(PLATFORM_OBJDIR)

###################################################################################
# Dependency handling
###################################################################################
-include $(HWACFARPROC_DSS_TEST_DEPENDS)


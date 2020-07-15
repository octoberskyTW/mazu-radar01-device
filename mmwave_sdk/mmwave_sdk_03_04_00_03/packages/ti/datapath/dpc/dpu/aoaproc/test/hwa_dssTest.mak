###################################################################################
# AOA PROC Test
###################################################################################
.PHONY: aoaHwaDssTest aoaHwaDssTestClean

###################################################################################
# Setup the VPATH:
###################################################################################
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/aoaproc/test
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/utils/randomdatagenerator
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/utils/mathutils/src

###################################################################################
# The AOA PROC Test requires additional libraries
###################################################################################
HWAAOAPROC_DSS_TEST_STD_LIBS = $(C674_COMMON_STD_LIB)								\
           				-llibedma_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) 		\
           				-llibhwa_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)       \
                        -llibtestlogger_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) \
						-llibaoaproc_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) \
						-llibdpedma_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)
HWAAOAPROC_DSS_TEST_LOC_LIBS = $(C674_COMMON_LOC_LIB)								\
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/edma/lib 	\
           				-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/hwa/lib    \
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/utils/testlogger/lib \
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/aoaproc/lib \
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpedma/lib


###################################################################################
# Unit Test Files
###################################################################################
HWAAOAPROC_DSS_TEST_CFG	 	 = test/dss.cfg
HWAAOAPROC_DSS_TEST_CMD       = $(MMWAVE_SDK_INSTALL_PATH)/ti/platform/$(MMWAVE_SDK_DEVICE_TYPE)
HWAAOAPROC_DSS_TEST_CONFIGPKG = test/c674_configPkg_$(MMWAVE_SDK_DEVICE_TYPE)
HWAAOAPROC_DSS_TEST_MAP       = test/$(MMWAVE_SDK_DEVICE_TYPE)_aoaprochwa_dss.map
HWAAOAPROC_DSS_TEST_OUT       = test/$(MMWAVE_SDK_DEVICE_TYPE)_aoaprochwa_dss.$(C674_EXE_EXT)
HWAAOAPROC_DSS_TEST_BIN       = test/$(MMWAVE_SDK_DEVICE_TYPE)_aoaprochwa_dss.bin
HWAAOAPROC_DSS_TEST_APP_CMD   = test/dss_aoaproc_linker.cmd
HWAAOAPROC_DSS_TEST_SOURCES   = aoaprochwa_test_main.c \
								gen_rand_data.c \
								     mathutils.c 
								

HWAAOAPROC_DSS_TEST_DEPENDS 	 = $(addprefix $(PLATFORM_OBJDIR)/, $(HWAAOAPROC_DSS_TEST_SOURCES:.c=.$(C674_DEP_EXT)))
HWAAOAPROC_DSS_TEST_OBJECTS 	 = $(addprefix $(PLATFORM_OBJDIR)/, $(HWAAOAPROC_DSS_TEST_SOURCES:.c=.$(C674_OBJ_EXT)))

OPTIMIZE_FOR_SPEED_OPTIONS := -o1 -o2 -o3 -O1 -O2 -O3


###################################################################################
# RTSC Configuration:
###################################################################################
hwaDssRTSC: $(HWAAOAPROC_DSS_TEST_CFG)
	@echo 'Configuring RTSC packages...'
	$(XS) --xdcpath="$(XDCPATH)" xdc.tools.configuro $(C674_XSFLAGS) -o $(HWAAOAPROC_DSS_TEST_CONFIGPKG) $(HWAAOAPROC_DSS_TEST_CFG)
	@echo 'Finished configuring packages'
	@echo ' '

###################################################################################
# Build Unit Test:
###################################################################################
aoaHwaDssTest: BUILD_CONFIGPKG=$(HWAAOAPROC_DSS_TEST_CONFIGPKG)
aoaHwaDssTest: C674_CFLAGS += --cmd_file=$(BUILD_CONFIGPKG)/compiler.opt
aoaHwaDssTest: C674_CFLAGS := $(filter-out $(OPTIMIZE_FOR_SPEED_OPTIONS),$(C674_CFLAGS))
aoaHwaDssTest: buildDirectories hwaDssRTSC $(HWAAOAPROC_DSS_TEST_OBJECTS)
	$(C674_LD) $(C674_LDFLAGS) $(HWAAOAPROC_DSS_TEST_LOC_LIBS) $(HWAAOAPROC_DSS_TEST_STD_LIBS) \
   -l$(HWAAOAPROC_DSS_TEST_CONFIGPKG)/linker.cmd --map_file=$(HWAAOAPROC_DSS_TEST_MAP)   \
    $(HWAAOAPROC_DSS_TEST_OBJECTS) $(PLATFORM_C674X_LINK_CMD) $(HWAAOAPROC_DSS_TEST_APP_CMD) \
	$(C674_LD_RTS_FLAGS) -o $(HWAAOAPROC_DSS_TEST_OUT)
	@echo '******************************************************************************'
	@echo 'Built the aoa proc DSP Unit Test '
	@echo '******************************************************************************'

###################################################################################
# Cleanup Unit Test:
###################################################################################
aoaHwaDssTestClean:
	@echo 'Cleaning the AOA PROC DSP Unit Test objects'
	@$(DEL) $(HWAAOAPROC_DSS_TEST_OBJECTS) $(HWAAOAPROC_DSS_TEST_OUT) $(HWAAOAPROC_DSS_TEST_BIN)
	@$(DEL) $(HWAAOAPROC_DSS_TEST_MAP) $(HWAAOAPROC_DSS_TEST_DEPENDS)
	@echo 'Cleaning the AOA PROC DSP Unit RTSC package'
	@$(DEL) $(HWAAOAPROC_DSS_TEST_CONFIGPKG)
	@$(DEL) $(PLATFORM_OBJDIR)

###################################################################################
# Dependency handling
###################################################################################
-include $(HWAAOAPROC_DSS_TEST_DEPENDS)


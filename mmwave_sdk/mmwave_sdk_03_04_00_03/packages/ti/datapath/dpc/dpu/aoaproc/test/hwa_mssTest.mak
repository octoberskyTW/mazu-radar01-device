###################################################################################
# aoa PROC Test
###################################################################################
.PHONY: aoaHwaMssTest aoaHwaMssTestClean

###################################################################################
# Setup the VPATH:
###################################################################################
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/aoaproc/test
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/utils/randomdatagenerator
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/utils/mathutils/src

###################################################################################
# The AOA PROC Test requires additional libraries
###################################################################################
HWAAOAPROC_TEST_STD_LIBS = $(R4F_COMMON_STD_LIB)								\
           				-llibedma_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT) 		\
           				-llibhwa_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)       \
                        -llibtestlogger_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT) \
						-llibaoaproc_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT) \
						-llibdpedma_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)
HWAAOAPROC_TEST_LOC_LIBS = $(R4F_COMMON_LOC_LIB)								\
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/edma/lib 	\
           				-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/hwa/lib    \
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/utils/testlogger/lib \
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/aoaproc/lib \
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpedma/lib


###################################################################################
# Unit Test Files
###################################################################################
HWAAOAPROC_TEST_CFG	 	 = test/mss.cfg
HWAAOAPROC_TEST_CMD       = $(MMWAVE_SDK_INSTALL_PATH)/ti/platform/$(MMWAVE_SDK_DEVICE_TYPE)
HWAAOAPROC_TEST_CONFIGPKG = test/mss_configPkg_$(MMWAVE_SDK_DEVICE_TYPE)
HWAAOAPROC_TEST_MAP       = test/$(MMWAVE_SDK_DEVICE_TYPE)_aoaprochwa_mss.map
HWAAOAPROC_TEST_OUT       = test/$(MMWAVE_SDK_DEVICE_TYPE)_aoaprochwa_mss.$(R4F_EXE_EXT)
HWAAOAPROC_TEST_BIN       = test/$(MMWAVE_SDK_DEVICE_TYPE)_aoaprochwa_mss.bin
HWAAOAPROC_TEST_APP_CMD   = test/mss_aoaproc_linker.cmd
HWAAOAPROC_TEST_SOURCES   = aoaprochwa_test_main.c \
								gen_rand_data.c \
								 mathutils.c 
								
                                   
OPTIMIZE_FOR_SPEED_OPTIONS := -o1 -o2 -o3 -O1 -O2 -O3

HWAAOAPROC_TEST_DEPENDS 	 = $(addprefix $(PLATFORM_OBJDIR)/, $(HWAAOAPROC_TEST_SOURCES:.c=.$(R4F_DEP_EXT)))
HWAAOAPROC_TEST_OBJECTS 	 = $(addprefix $(PLATFORM_OBJDIR)/, $(HWAAOAPROC_TEST_SOURCES:.c=.$(R4F_OBJ_EXT)))

###################################################################################
# RTSC Configuration:
###################################################################################
aoahwaMssRTSC: $(R4_CFG)
	@echo 'Configuring RTSC packages...'
	$(XS) --xdcpath="$(XDCPATH)" xdc.tools.configuro $(R4F_XSFLAGS) -o $(HWAAOAPROC_TEST_CONFIGPKG) $(HWAAOAPROC_TEST_CFG)
	@echo 'Finished configuring packages'
	@echo ' '

###################################################################################
# Build Unit Test:
###################################################################################
aoaHwaMssTest: BUILD_CONFIGPKG=$(HWAAOAPROC_TEST_CONFIGPKG)
aoaHwaMssTest: R4F_CFLAGS += --cmd_file=$(BUILD_CONFIGPKG)/compiler.opt
aoaHwaMssTest: R4F_CFLAGS := $(filter-out $(OPTIMIZE_FOR_SPEED_OPTIONS),$(R4F_CFLAGS))
aoaHwaMssTest: buildDirectories aoahwaMssRTSC $(HWAAOAPROC_TEST_OBJECTS)
	$(R4F_LD) $(R4F_LDFLAGS) $(HWAAOAPROC_TEST_LOC_LIBS) $(HWAAOAPROC_TEST_STD_LIBS) -l$(HWAAOAPROC_TEST_CONFIGPKG)/linker.cmd --map_file=$(HWAAOAPROC_TEST_MAP) $(HWAAOAPROC_TEST_OBJECTS) \
	$(PLATFORM_R4F_LINK_CMD) $(HWAAOAPROC_TEST_APP_CMD) $(R4F_LD_RTS_FLAGS) -o $(HWAAOAPROC_TEST_OUT)
	@echo '******************************************************************************'
	@echo 'Built the aoa proc R4 Unit Test '
	@echo '******************************************************************************'

###################################################################################
# Cleanup Unit Test:
###################################################################################
aoaHwaMssTestClean:
	@echo 'Cleaning the AOA PROC R4 Unit Test objects'
	@$(DEL) $(HWAAOAPROC_TEST_OBJECTS) $(HWAAOAPROC_TEST_OUT) $(HWAAOAPROC_TEST_BIN)
	@$(DEL) $(HWAAOAPROC_TEST_MAP) $(HWAAOAPROC_TEST_DEPENDS)
	@echo 'Cleaning the AOA PROC R4 Unit RTSC package'
	@$(DEL) $(HWAAOAPROC_TEST_CONFIGPKG)
	@$(DEL) $(PLATFORM_OBJDIR)

###################################################################################
# Dependency handling
###################################################################################
-include $(HWAAOAPROC_TEST_DEPENDS)


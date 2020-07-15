###################################################################################
# cfar PROC Test
###################################################################################
.PHONY: cfarHwaMssTest cfarHwaMssTestClean

###################################################################################
# Setup the VPATH:
###################################################################################
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/cfarcaproc/test
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/utils/randomdatagenerator
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/utils/mathutils/src

###################################################################################
# The CFAR PROC Test requires additional libraries
###################################################################################
HWACFARPROC_TEST_STD_LIBS = $(R4F_COMMON_STD_LIB)								\
           				-llibedma_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT) 		\
           				-llibhwa_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)       \
                        -llibtestlogger_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT) \
						-llibcfarcaproc_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT) \
						-llibdpedma_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)
HWACFARPROC_TEST_LOC_LIBS = $(R4F_COMMON_LOC_LIB)								\
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/edma/lib 	\
           				-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/hwa/lib    \
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/utils/testlogger/lib \
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/cfarcaproc/lib \
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpedma/lib


###################################################################################
# Unit Test Files
###################################################################################
HWACFARPROC_TEST_CFG	 	 = test/mss.cfg
HWACFARPROC_TEST_CMD       = $(MMWAVE_SDK_INSTALL_PATH)/ti/platform/$(MMWAVE_SDK_DEVICE_TYPE)
HWACFARPROC_TEST_CONFIGPKG = test/mss_configPkg_$(MMWAVE_SDK_DEVICE_TYPE)
HWACFARPROC_TEST_MAP       = test/$(MMWAVE_SDK_DEVICE_TYPE)_cfarprochwa_mss.map
HWACFARPROC_TEST_OUT       = test/$(MMWAVE_SDK_DEVICE_TYPE)_cfarprochwa_mss.$(R4F_EXE_EXT)
HWACFARPROC_TEST_BIN       = test/$(MMWAVE_SDK_DEVICE_TYPE)_cfarprochwa_mss.bin
HWACFARPROC_TEST_APP_CMD   = test/mss_cfarproc_linker.cmd
HWACFARPROC_TEST_SOURCES   = cfarprochwa_test_main.c \
							 gen_rand_data.c \
							 mathutils.c 
								
                                   
OPTIMIZE_FOR_SPEED_OPTIONS := -o1 -o2 -o3 -O1 -O2 -O3

HWACFARPROC_TEST_DEPENDS 	 = $(addprefix $(PLATFORM_OBJDIR)/, $(HWACFARPROC_TEST_SOURCES:.c=.$(R4F_DEP_EXT)))
HWACFARPROC_TEST_OBJECTS 	 = $(addprefix $(PLATFORM_OBJDIR)/, $(HWACFARPROC_TEST_SOURCES:.c=.$(R4F_OBJ_EXT)))

###################################################################################
# RTSC Configuration:
###################################################################################
cfarhwaMssRTSC: $(R4_CFG)
	@echo 'Configuring RTSC packages...'
	$(XS) --xdcpath="$(XDCPATH)" xdc.tools.configuro $(R4F_XSFLAGS) -o $(HWACFARPROC_TEST_CONFIGPKG) $(HWACFARPROC_TEST_CFG)
	@echo 'Finished configuring packages'
	@echo ' '

###################################################################################
# Build Unit Test:
###################################################################################
cfarHwaMssTest: BUILD_CONFIGPKG=$(HWACFARPROC_TEST_CONFIGPKG)
cfarHwaMssTest: R4F_CFLAGS += --cmd_file=$(BUILD_CONFIGPKG)/compiler.opt
cfarHwaMssTest: R4F_CFLAGS := $(filter-out $(OPTIMIZE_FOR_SPEED_OPTIONS),$(R4F_CFLAGS))
cfarHwaMssTest: buildDirectories cfarhwaMssRTSC $(HWACFARPROC_TEST_OBJECTS)
	$(R4F_LD) $(R4F_LDFLAGS) $(HWACFARPROC_TEST_LOC_LIBS) $(HWACFARPROC_TEST_STD_LIBS) -l$(HWACFARPROC_TEST_CONFIGPKG)/linker.cmd --map_file=$(HWACFARPROC_TEST_MAP) $(HWACFARPROC_TEST_OBJECTS) \
	$(PLATFORM_R4F_LINK_CMD) $(HWACFARPROC_TEST_APP_CMD) $(R4F_LD_RTS_FLAGS) -o $(HWACFARPROC_TEST_OUT)
	@echo '******************************************************************************'
	@echo 'Built the cfar proc R4 Unit Test '
	@echo '******************************************************************************'

###################################################################################
# Cleanup Unit Test:
###################################################################################
cfarHwaMssTestClean:
	@echo 'Cleaning the CFAR PROC R4 Unit Test objects'
	@$(DEL) $(HWACFARPROC_TEST_OBJECTS) $(HWACFARPROC_TEST_OUT) $(HWACFARPROC_TEST_BIN)
	@$(DEL) $(HWACFARPROC_TEST_MAP) $(HWACFARPROC_TEST_DEPENDS)
	@echo 'Cleaning the CFAR PROC R4 Unit RTSC package'
	@$(DEL) $(HWACFARPROC_TEST_CONFIGPKG)
	@$(DEL) $(PLATFORM_OBJDIR)

###################################################################################
# Dependency handling
###################################################################################
-include $(HWACFARPROC_TEST_DEPENDS)


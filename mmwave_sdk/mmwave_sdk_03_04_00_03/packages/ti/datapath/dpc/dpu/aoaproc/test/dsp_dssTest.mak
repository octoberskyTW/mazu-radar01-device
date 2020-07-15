###################################################################################
# AOA PROC Test
###################################################################################
.PHONY: aoaDspDssTest aoaDspDssTestClean

###################################################################################
# Setup the VPATH:
###################################################################################
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/aoaproc/test
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/utils/randomdatagenerator
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/utils/mathutils/src

###################################################################################
# The AOA PROC Test requires additional libraries
###################################################################################
DSPAOAPROC_DSS_TEST_STD_LIBS = $(C674_COMMON_STD_LIB)								\
           				-llibedma_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) 		\
                        -llibtestlogger_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) \
						-llibaoaproc_dsp_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) \
               			-ldsplib.ae64P	\
                        -llibmmwavealg_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) \
                        -lmathlib.$(C674_LIB_EXT)
                        
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
DSPAOAPROC_DSS_TEST_STD_LIBS +=	-llibdpedma_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) 
else
DSPAOAPROC_DSS_TEST_STD_LIBS +=	-llibdpedma_base_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) 
endif                        
                        
DSPAOAPROC_DSS_TEST_LOC_LIBS = $(C674_COMMON_LOC_LIB)								\
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/edma/lib 	\
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/utils/testlogger/lib \
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/aoaproc/lib \
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpedma/lib \
              			-i$(C64Px_DSPLIB_INSTALL_PATH)/packages/ti/dsplib/lib \
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/alg/mmwavelib/lib \
                        -i$(C674x_MATHLIB_INSTALL_PATH)/packages/ti/mathlib/lib


###################################################################################
# Unit Test Files
###################################################################################
DSPAOAPROC_DSS_TEST_CFG	 	 = test/dss.cfg
DSPAOAPROC_DSS_TEST_CMD       = $(MMWAVE_SDK_INSTALL_PATH)/ti/platform/$(MMWAVE_SDK_DEVICE_TYPE)
DSPAOAPROC_DSS_TEST_CONFIGPKG = test/c674_configPkg_$(MMWAVE_SDK_DEVICE_TYPE)
DSPAOAPROC_DSS_TEST_MAP       = test/$(MMWAVE_SDK_DEVICE_TYPE)_aoaprocdsp_dss.map
DSPAOAPROC_DSS_TEST_OUT       = test/$(MMWAVE_SDK_DEVICE_TYPE)_aoaprocdsp_dss.$(C674_EXE_EXT)
DSPAOAPROC_DSS_TEST_BIN       = test/$(MMWAVE_SDK_DEVICE_TYPE)_aoaprocdsp_dss.bin
DSPAOAPROC_DSS_TEST_APP_CMD   = test/dss_aoaproc_linker.cmd
DSPAOAPROC_DSS_TEST_SOURCES   = aoaprocdsp_test_main.c \
								gen_rand_data.c \
								mathutils.c 

DSPAOAPROC_DSS_TEST_DEPENDS 	 = $(addprefix $(PLATFORM_OBJDIR)/, $(DSPAOAPROC_DSS_TEST_SOURCES:.c=.$(C674_DEP_EXT)))
DSPAOAPROC_DSS_TEST_OBJECTS 	 = $(addprefix $(PLATFORM_OBJDIR)/, $(DSPAOAPROC_DSS_TEST_SOURCES:.c=.$(C674_OBJ_EXT)))

OPTIMIZE_FOR_SPEED_OPTIONS := -o1 -o2 -o3 -O1 -O2 -O3


###################################################################################
# RTSC Configuration:
###################################################################################
dspDssRTSC: $(DSPAOAPROC_DSS_TEST_CFG)
	@echo 'Configuring RTSC packages...'
	$(XS) --xdcpath="$(XDCPATH)" xdc.tools.configuro $(C674_XSFLAGS) -o $(DSPAOAPROC_DSS_TEST_CONFIGPKG) $(DSPAOAPROC_DSS_TEST_CFG)
	@echo 'Finished configuring packages'
	@echo ' '

###################################################################################
# Build Unit Test:
###################################################################################
aoaDspDssTest: BUILD_CONFIGPKG=$(DSPAOAPROC_DSS_TEST_CONFIGPKG)
aoaDspDssTest: C674_CFLAGS += --cmd_file=$(BUILD_CONFIGPKG)/compiler.opt
aoaDspDssTest: C674_CFLAGS := $(filter-out $(OPTIMIZE_FOR_SPEED_OPTIONS),$(C674_CFLAGS))
aoaDspDssTest: buildDirectories dspDssRTSC $(DSPAOAPROC_DSS_TEST_OBJECTS)
	$(C674_LD) $(C674_LDFLAGS) $(DSPAOAPROC_DSS_TEST_LOC_LIBS) $(DSPAOAPROC_DSS_TEST_STD_LIBS) \
   -l$(DSPAOAPROC_DSS_TEST_CONFIGPKG)/linker.cmd --map_file=$(DSPAOAPROC_DSS_TEST_MAP)   \
    $(DSPAOAPROC_DSS_TEST_OBJECTS) $(PLATFORM_C674X_LINK_CMD) $(DSPAOAPROC_DSS_TEST_APP_CMD) \
	$(C674_LD_RTS_FLAGS) -o $(DSPAOAPROC_DSS_TEST_OUT)
	@echo '******************************************************************************'
	@echo 'Built the DSP aoa proc Unit Test '
	@echo '******************************************************************************'

###################################################################################
# Cleanup Unit Test:
###################################################################################
aoaDspDssTestClean:
	@echo 'Cleaning the AOA PROC DSP Unit Test objects'
	@$(DEL) $(DSPAOAPROC_DSS_TEST_OBJECTS) $(DSPAOAPROC_DSS_TEST_OUT) $(DSPAOAPROC_DSS_TEST_BIN)
	@$(DEL) $(DSPAOAPROC_DSS_TEST_MAP) $(DSPAOAPROC_DSS_TEST_DEPENDS)
	@echo 'Cleaning the AOA PROC DSP Unit RTSC package'
	@$(DEL) $(DSPAOAPROC_DSS_TEST_CONFIGPKG)
	@$(DEL) $(PLATFORM_OBJDIR)

###################################################################################
# Dependency handling
###################################################################################
-include $(DSPAOAPROC_DSS_TEST_DEPENDS)


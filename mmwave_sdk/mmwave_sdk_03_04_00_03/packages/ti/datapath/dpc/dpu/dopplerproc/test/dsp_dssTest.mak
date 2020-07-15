###################################################################################
# DSP DOPPLER PROC Test 
###################################################################################
.PHONY: dspDssTest dspDssTestClean

###################################################################################
# Setup the VPATH:
###################################################################################
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/dopplerproc/test
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/utils/mathutils/src
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/utils/randomdatagenerator

###################################################################################
# The DOPPLER PROC Test requires additional libraries
###################################################################################
DSPDOPPLERPROC_DSS_TEST_STD_LIBS = $(C674_COMMON_STD_LIB)								\
           				-llibedma_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) 		\
                        -llibtestlogger_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) \
						-llibdopplerproc_dsp_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) \
               			-ldsplib.ae64P	\
                        -llibmmwavealg_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) 
                        
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
DSPDOPPLERPROC_DSS_TEST_STD_LIBS +=	-llibdpedma_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) 
else
DSPDOPPLERPROC_DSS_TEST_STD_LIBS +=	-llibdpedma_base_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) 
endif                        
                        
DSPDOPPLERPROC_DSS_TEST_LOC_LIBS = $(C674_COMMON_LOC_LIB)								\
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/edma/lib 	\
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/utils/testlogger/lib \
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/dopplerproc/lib \
						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpedma/lib \
              			-i$(C64Px_DSPLIB_INSTALL_PATH)/packages/ti/dsplib/lib \
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/alg/mmwavelib/lib


###################################################################################
# Unit Test Files
###################################################################################
DSPDOPPLERPROC_DSS_TEST_CFG	 	 = test/dss.cfg
DSPDOPPLERPROC_DSS_TEST_CMD       = $(MMWAVE_SDK_INSTALL_PATH)/ti/platform/$(MMWAVE_SDK_DEVICE_TYPE)
DSPDOPPLERPROC_DSS_TEST_CONFIGPKG = test/c674_configPkg_$(MMWAVE_SDK_DEVICE_TYPE)
DSPDOPPLERPROC_DSS_TEST_MAP       = test/$(MMWAVE_SDK_DEVICE_TYPE)_dopplerprocdsp_dss.map
DSPDOPPLERPROC_DSS_TEST_OUT       = test/$(MMWAVE_SDK_DEVICE_TYPE)_dopplerprocdsp_dss.$(C674_EXE_EXT)
DSPDOPPLERPROC_DSS_TEST_BIN       = test/$(MMWAVE_SDK_DEVICE_TYPE)_dopplerprocdsp_dss.bin
DSPDOPPLERPROC_DSS_TEST_APP_CMD   = test/dss_dopplerproc_linker.cmd
DSPDOPPLERPROC_DSS_TEST_SOURCES   = doppleprocdsp_test_main.c \
									gen_rand_data.c \
								    mathutils.c 
								

DSPDOPPLERPROC_DSS_TEST_DEPENDS 	 = $(addprefix $(PLATFORM_OBJDIR)/, $(DSPDOPPLERPROC_DSS_TEST_SOURCES:.c=.$(C674_DEP_EXT)))
DSPDOPPLERPROC_DSS_TEST_OBJECTS 	 = $(addprefix $(PLATFORM_OBJDIR)/, $(DSPDOPPLERPROC_DSS_TEST_SOURCES:.c=.$(C674_OBJ_EXT)))

OPTIMIZE_FOR_SPEED_OPTIONS := -o1 -o2 -o3 -O1 -O2 -O3


###################################################################################
# RTSC Configuration:
###################################################################################
dspDssRTSC: $(DSPDOPPLERPROC_DSS_TEST_CFG)
	@echo 'Configuring RTSC packages...'
	$(XS) --xdcpath="$(XDCPATH)" xdc.tools.configuro $(C674_XSFLAGS) -o $(DSPDOPPLERPROC_DSS_TEST_CONFIGPKG) $(DSPDOPPLERPROC_DSS_TEST_CFG)
	@echo 'Finished configuring packages'
	@echo ' '

###################################################################################
# Build Unit Test:
###################################################################################
dspDssTest: BUILD_CONFIGPKG=$(DSPDOPPLERPROC_DSS_TEST_CONFIGPKG)
dspDssTest: C674_CFLAGS += --cmd_file=$(BUILD_CONFIGPKG)/compiler.opt
dspDssTest: C674_CFLAGS := $(filter-out $(OPTIMIZE_FOR_SPEED_OPTIONS),$(C674_CFLAGS))
dspDssTest: buildDirectories dspDssRTSC $(DSPDOPPLERPROC_DSS_TEST_OBJECTS)
	$(C674_LD) $(C674_LDFLAGS) $(DSPDOPPLERPROC_DSS_TEST_LOC_LIBS) $(DSPDOPPLERPROC_DSS_TEST_STD_LIBS) \
   -l$(DSPDOPPLERPROC_DSS_TEST_CONFIGPKG)/linker.cmd --map_file=$(DSPDOPPLERPROC_DSS_TEST_MAP)   \
    $(DSPDOPPLERPROC_DSS_TEST_OBJECTS) $(PLATFORM_C674X_LINK_CMD) $(DSPDOPPLERPROC_DSS_TEST_APP_CMD) \
	$(C674_LD_RTS_FLAGS) -o $(DSPDOPPLERPROC_DSS_TEST_OUT)
	@echo '******************************************************************************'
	@echo 'Built the DSP doppler proc Unit Test '
	@echo '******************************************************************************'

###################################################################################
# Cleanup Unit Test:
###################################################################################
dspDssTestClean:
	@echo 'Cleaning the DOPPLER PROC DSP Unit Test objects'
	@$(DEL) $(DSPDOPPLERPROC_DSS_TEST_OBJECTS) $(DSPDOPPLERPROC_DSS_TEST_OUT) $(DSPDOPPLERPROC_DSS_TEST_BIN)
	@$(DEL) $(DSPDOPPLERPROC_DSS_TEST_MAP) $(DSPDOPPLERPROC_DSS_TEST_DEPENDS)
	@echo 'Cleaning the DOPPLER PROC DSP Unit RTSC package'
	@$(DEL) $(DSPDOPPLERPROC_DSS_TEST_CONFIGPKG)
	@$(DEL) $(PLATFORM_OBJDIR)

###################################################################################
# Dependency handling
###################################################################################
-include $(DSPDOPPLERPROC_DSS_TEST_DEPENDS)


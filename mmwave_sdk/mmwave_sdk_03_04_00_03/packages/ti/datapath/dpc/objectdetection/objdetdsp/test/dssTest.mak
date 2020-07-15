###################################################################################
# Object Detection DPC Test
###################################################################################
.PHONY: dssTest dssTestClean

###################################################################################
# Setup the VPATH:
###################################################################################
vpath %.c $(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/objectdetection/common \
			src \
			test \
          $(MMWAVE_SDK_INSTALL_PATH)/ti/board \

###################################################################################
# The Object Detection DPC Test requires additional libraries
###################################################################################
OBJECTDETECTION_TEST_DSS_STD_LIBS = $(C674_COMMON_STD_LIB)			\
                        -llibedma_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) 	\
                        -llibtestlogger_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) \
                        -ldsplib.ae64P	\
                        -lmathlib.$(C674_LIB_EXT) 				\
                        -llibmailbox_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)	\
                        -llibmmwavealg_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) \
                        -llibdpm_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) \
                        -llibmathutils.$(C674_LIB_EXT) \
                        -llibosal_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT) \
                        -llibrangeproc_dsp_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)     \
                        -llibdopplerproc_dsp_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)   \
                        -llibaoaproc_dsp_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)       \
                        -llibcfarcaproc_dsp_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)

ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
OBJECTDETECTION_TEST_DSS_STD_LIBS += -llibdpedma_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)
else
OBJECTDETECTION_TEST_DSS_STD_LIBS += -llibdpedma_base_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)
endif

OBJECTDETECTION_TEST_DSS_LOC_LIBS = $(C674_COMMON_LOC_LIB)			\
			-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/edma/lib 	\
			-i$(MMWAVE_SDK_INSTALL_PATH)/ti/alg/mmwavelib/lib 	\
			-i$(MMWAVE_SDK_INSTALL_PATH)/ti/utils/testlogger/lib 	\
			-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/mailbox/lib	\
			-i$(MMWAVE_SDK_INSTALL_PATH)/ti/control/dpm/lib 	\
			-i$(MMWAVE_SDK_INSTALL_PATH)/ti/utils/mathutils/lib 	\
			-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/osal/lib    	\
			-i$(C674x_MATHLIB_INSTALL_PATH)/packages/ti/mathlib/lib \
			-i$(C64Px_DSPLIB_INSTALL_PATH)/packages/ti/dsplib/lib \
			-i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpu/rangeproc/lib          \
			-i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/dopplerproc/lib    \
			-i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/aoaproc/lib        \
			-i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpedma/lib                 \
			-i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/cfarcaproc/lib

###################################################################################
# Unit Test Files
###################################################################################
OBJECTDETECTION_TEST_DSS_CFG       = test/dss.cfg
OBJECTDETECTION_TEST_DSS_CMD       = $(MMWAVE_SDK_INSTALL_PATH)/ti/platform/$(MMWAVE_SDK_DEVICE_TYPE)
OBJECTDETECTION_TEST_DSS_CONFIGPKG = test/dss_configPkg_$(MMWAVE_SDK_DEVICE_TYPE)
OBJECTDETECTION_TEST_DSS_MAP       = test/$(MMWAVE_SDK_DEVICE_TYPE)_objectdetection_test_dss.map
OBJECTDETECTION_TEST_DSS_OUT       = test/$(MMWAVE_SDK_DEVICE_TYPE)_objectdetection_test_dss.$(C674_EXE_EXT)
OBJECTDETECTION_TEST_DSS_APP_CMD   = test/$(MMWAVE_SDK_DEVICE_TYPE)_dss_objectdetection_test_linker.cmd
OBJECTDETECTION_TEST_DSS_SOURCES   = main.c \
                                 objectdetection.c \
                                 gen_frame_data.c \
                                 antenna_geometry.c \

OBJECTDETECTION_TEST_DSS_DEPENDS 	 = $(addprefix $(PLATFORM_OBJDIR)/, $(OBJECTDETECTION_TEST_DSS_SOURCES:.c=.$(C674_DEP_EXT)))
OBJECTDETECTION_TEST_DSS_OBJECTS 	 = $(addprefix $(PLATFORM_OBJDIR)/, $(OBJECTDETECTION_TEST_DSS_SOURCES:.c=.$(C674_OBJ_EXT)))

###################################################################################
# RTSC Configuration:
###################################################################################
dssRTSC: $(OBJECTDETECTION_TEST_DSS_CFG)
	@echo 'Configuring RTSC packages...'
	$(XS) --xdcpath="$(XDCPATH)" xdc.tools.configuro $(C674_XSFLAGS) -o $(OBJECTDETECTION_TEST_DSS_CONFIGPKG) $(OBJECTDETECTION_TEST_DSS_CFG)
	@echo 'Finished configuring packages'
	@echo ' '

###################################################################################
# Build Unit Test:
###################################################################################
dssTest: BUILD_CONFIGPKG=$(OBJECTDETECTION_TEST_DSS_CONFIGPKG)
dssTest: C674_CFLAGS += --cmd_file=$(BUILD_CONFIGPKG)/compiler.opt \
                        --define=APP_RESOURCE_FILE="<mmw_res.h>" \
                        -i$(C674x_MATHLIB_INSTALL_PATH)/packages \

dssTest: buildDirectories dssRTSC $(OBJECTDETECTION_TEST_DSS_OBJECTS)
	    $(C674_LD) $(C674_LDFLAGS) $(OBJECTDETECTION_TEST_DSS_LOC_LIBS) $(OBJECTDETECTION_TEST_DSS_STD_LIBS) \
		-l$(OBJECTDETECTION_TEST_DSS_CONFIGPKG)/linker.cmd --map_file=$(OBJECTDETECTION_TEST_DSS_MAP) \
		$(OBJECTDETECTION_TEST_DSS_OBJECTS) \
		$(PLATFORM_C674X_LINK_CMD) $(OBJECTDETECTION_TEST_DSS_APP_CMD) $(C674_LD_RTS_FLAGS) -o $(OBJECTDETECTION_TEST_DSS_OUT)
	@echo '******************************************************************************'
	@echo 'Built the Object Detection DPC C674 Unit Test '
	@echo '******************************************************************************'

###################################################################################
# Cleanup Unit Test:
###################################################################################
dssTestClean:
	@echo 'Cleaning the Object Detection DPC C674 Unit Test objects'
	@$(DEL) $(OBJECTDETECTION_TEST_DSS_OBJECTS) $(OBJECTDETECTION_TEST_DSS_OUT) $(OBJECTDETECTION_TEST_DSS_BIN)
	@$(DEL) $(OBJECTDETECTION_TEST_DSS_MAP) $(OBJECTDETECTION_TEST_DSS_DEPENDS)
	@echo 'Cleaning the Object Detection DPC C674 Unit RTSC package'
	@$(DEL) $(OBJECTDETECTION_TEST_DSS_CONFIGPKG)
	@$(DEL) $(PLATFORM_OBJDIR)

###################################################################################
# Dependency handling
###################################################################################
-include $(OBJECTDETECTION_TEST_DSS_DEPENDS)


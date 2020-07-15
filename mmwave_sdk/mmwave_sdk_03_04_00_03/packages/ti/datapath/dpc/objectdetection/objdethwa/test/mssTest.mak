###################################################################################
# Object Detection DPC Test
###################################################################################
.PHONY: mssTest mssTestClean

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
OBJECTDETECTION_TEST_STD_LIBS = $(R4F_COMMON_STD_LIB)					\
                        -llibedma_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT) 	\
                        -llibhwa_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)       \
                        -llibtestlogger_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT) \
                        -llibmailbox_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)		\
                        -llibdpm_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT) \
                        -llibmathutils.$(R4F_LIB_EXT) \
                        -llibosal_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT) \
                        -llibrangeproc_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)     \
                        -llibdopplerproc_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)   \
                        -llibcfarcaproc_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)    \
                        -llibstaticclutterproc_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT) \
                        -llibdpedma_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)

ifeq ($(MMWAVE_SDK_LIB_BUILD_OPTION),AOP)
OBJECTDETECTION_TEST_STD_LIBS += -llibaoa2dproc_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)
else
OBJECTDETECTION_TEST_STD_LIBS += -llibaoaproc_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)
endif
                        

OBJECTDETECTION_TEST_LOC_LIBS = $(R4F_COMMON_LOC_LIB)					\
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/edma/lib 	\
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/hwa/lib    	\
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/utils/testlogger/lib \
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/mailbox/lib	   	\
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/control/dpm/lib \
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/utils/mathutils/lib \
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/osal/lib    \
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpu/rangeproc/lib          \
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/dopplerproc/lib    \
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/cfarcaproc/lib     \
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/staticclutterproc/lib  \
                        -i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpedma/lib

ifeq ($(MMWAVE_SDK_LIB_BUILD_OPTION),AOP)
OBJECTDETECTION_TEST_LOC_LIBS += -i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/aoa2dproc/lib
else
OBJECTDETECTION_TEST_LOC_LIBS += -i$(MMWAVE_SDK_INSTALL_PATH)/ti/datapath/dpc/dpu/aoaproc/lib
endif

###################################################################################
# Unit Test Files
###################################################################################
OBJECTDETECTION_TEST_CFG       = test/mss.cfg
OBJECTDETECTION_TEST_CMD       = $(MMWAVE_SDK_INSTALL_PATH)/ti/platform/$(MMWAVE_SDK_DEVICE_TYPE)
OBJECTDETECTION_TEST_CONFIGPKG = test/mss_configPkg_$(MMWAVE_SDK_DEVICE_TYPE)$(MMWAVE_SDK_LIB_BUILD_OPTION)
OBJECTDETECTION_TEST_MAP       = test/$(MMWAVE_SDK_DEVICE_TYPE)$(MMWAVE_SDK_LIB_BUILD_OPTION)_objectdetection_test_mss.map
OBJECTDETECTION_TEST_OUT       = test/$(MMWAVE_SDK_DEVICE_TYPE)$(MMWAVE_SDK_LIB_BUILD_OPTION)_objectdetection_test_mss.$(R4F_EXE_EXT)
OBJECTDETECTION_TEST_APP_CMD   = test/mss_objectdetection_test_linker.cmd
OBJECTDETECTION_TEST_SOURCES   = main.c \
                                 objectdetection.c \
                                 gen_frame_data.c \
                                 antenna_geometry.c \

OBJECTDETECTION_TEST_DEPENDS 	 = $(addprefix $(PLATFORM_OBJDIR)/, $(OBJECTDETECTION_TEST_SOURCES:.c=.$(R4F_DEP_EXT)))
OBJECTDETECTION_TEST_OBJECTS 	 = $(addprefix $(PLATFORM_OBJDIR)/, $(OBJECTDETECTION_TEST_SOURCES:.c=.$(R4F_OBJ_EXT)))

###################################################################################
# RTSC Configuration:
###################################################################################
mssRTSC: $(R4_CFG)
	@echo 'Configuring RTSC packages...'
	$(XS) --xdcpath="$(XDCPATH)" xdc.tools.configuro $(R4F_XSFLAGS) -o $(OBJECTDETECTION_TEST_CONFIGPKG) $(OBJECTDETECTION_TEST_CFG)
	@echo 'Finished configuring packages'
	@echo ' '

###################################################################################
# Build Unit Test:
###################################################################################
# For 68xx, we cannot use the 68xx demo resource file as its object detection
# spans HWA and DSP, so we choose 64xx for this device type
ifeq ($(MMWAVE_SDK_DEVICE_TYPE), xwr68xx)
    APP_RESOURCE_FILE_DEVICE_TYPE = xwr64xx
else
    APP_RESOURCE_FILE_DEVICE_TYPE = $(MMWAVE_SDK_DEVICE_TYPE)
endif 

mssTest: BUILD_CONFIGPKG=$(OBJECTDETECTION_TEST_CONFIGPKG)
mssTest: R4F_CFLAGS += --cmd_file=$(BUILD_CONFIGPKG)/compiler.opt \
                       --define=APP_RESOURCE_FILE="<ti/demo/$(APP_RESOURCE_FILE_DEVICE_TYPE)/mmw/mmw_res.h>" \
                       --define=DebugP_LOG_ENABLED
ifeq ($(MMWAVE_SDK_LIB_BUILD_OPTION),AOP)
mssTest: R4F_CFLAGS += --define=XWR68XX_AOP_ANTENNA_PATTERN \
                       --define=USE_2D_AOA_DPU 
endif
                       
mssTest: buildDirectories mssRTSC $(OBJECTDETECTION_TEST_OBJECTS)
	$(R4F_LD) $(R4F_LDFLAGS) $(OBJECTDETECTION_TEST_LOC_LIBS) $(OBJECTDETECTION_TEST_STD_LIBS) -l$(OBJECTDETECTION_TEST_CONFIGPKG)/linker.cmd --map_file=$(OBJECTDETECTION_TEST_MAP) $(OBJECTDETECTION_TEST_OBJECTS) \
	$(PLATFORM_R4F_LINK_CMD) $(OBJECTDETECTION_TEST_APP_CMD) $(R4F_LD_RTS_FLAGS) -o $(OBJECTDETECTION_TEST_OUT)
	@echo '******************************************************************************'
	@echo 'Built the Object Detection DPC R4F Unit Test '
	@echo '******************************************************************************'

###################################################################################
# Cleanup Unit Test:
###################################################################################
mssTestClean:
	@echo 'Cleaning the Object Detection DPC R4F Unit Test objects'
	@$(DEL) $(OBJECTDETECTION_TEST_OBJECTS) $(OBJECTDETECTION_TEST_OUT) $(OBJECTDETECTION_TEST_BIN)
	@$(DEL) $(OBJECTDETECTION_TEST_MAP) $(OBJECTDETECTION_TEST_DEPENDS)
	@echo 'Cleaning the Object Detection DPC R4F Unit RTSC package'
	@$(DEL) $(OBJECTDETECTION_TEST_CONFIGPKG)
	@$(DEL) $(PLATFORM_OBJDIR)

###################################################################################
# Dependency handling
###################################################################################
-include $(OBJECTDETECTION_TEST_DEPENDS)


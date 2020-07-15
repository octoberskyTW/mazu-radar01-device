###################################################################################
# mmWave Link DFP Test on MSS Makefile
###################################################################################
.PHONY: dfpmssTest dfpmssTestClean

###################################################################################
# Setup the VPATH:
###################################################################################
vpath %.c src
vpath %.c dfptest/$(MMWAVE_SDK_DEVICE_TYPE)
vpath %.c dfptest/common

###################################################################################
# The mmWave Link DFP Test requires additional libraries
###################################################################################
MMWAVE_DFP_MSS_UNIT_TEST_STD_LIBS = $(R4F_COMMON_STD_LIB)									\
		   						-llibpinmux_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT) 		\
		   						-llibcrc_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)			\
		   						-llibmailbox_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)		\
		   						-llibtestlogger_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)		\
		   						-llibadcbuf_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)    \
                                -llibedma_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)    \
		   						-llibmmwavelink_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)
MMWAVE_DFP_MSS_UNIT_TEST_LOC_LIBS = $(R4F_COMMON_LOC_LIB) 									\
		   						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/pinmux/lib 		\
		   						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/adcbuf/lib	   \
		   						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/crc/lib			\
		   						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/mailbox/lib		\
		   						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/utils/testlogger/lib	\
		   						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/edma/lib		\
		   						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/control/mmwavelink/lib

###################################################################################
# DFP Test Files
###################################################################################
MMWAVE_DFP_MSS_UNIT_TEST_CFG		 = dfptest/$(MMWAVE_SDK_DEVICE_TYPE)/mss.cfg
MMWAVE_DFP_MSS_UNIT_TEST_CMD		 = $(MMWAVE_SDK_INSTALL_PATH)/ti/platform/$(MMWAVE_SDK_DEVICE_TYPE)
MMWAVE_DFP_MSS_UNIT_TEST_CONFIGPKG	 = dfptest/$(MMWAVE_SDK_DEVICE_TYPE)/mss_configPkg_$(MMWAVE_SDK_DEVICE_TYPE)
MMWAVE_DFP_MSS_UNIT_TEST_MAP		 = dfptest/$(MMWAVE_SDK_DEVICE_TYPE)/$(MMWAVE_SDK_DEVICE_TYPE)_dfptest_mss.map
MMWAVE_DFP_MSS_UNIT_TEST_OUT		 = dfptest/$(MMWAVE_SDK_DEVICE_TYPE)/$(MMWAVE_SDK_DEVICE_TYPE)_dfptest_mss.$(R4F_EXE_EXT)
MMWAVE_DFP_MSS_UNIT_TEST_BIN		 = dfptest/$(MMWAVE_SDK_DEVICE_TYPE)/$(MMWAVE_SDK_DEVICE_TYPE)_dfptest_mss.bin
MMWAVE_DFP_MSS_UNIT_TEST_APP_CMD	 = dfptest/$(MMWAVE_SDK_DEVICE_TYPE)/mss_link_linker.cmd
MMWAVE_DFP_MSS_UNIT_TEST_SOURCES	 = main_dfp_mss.c dfptest_setup.c dfptest_monitoring.c \
                                   osi_tirtos.c dfptest_common.c \
                                   dfptest_verify.c dfptest_config.c \
                                   dfptest_config_001.c \
                                   dfptest_config_002.c \
                                   dfptest_config_003.c \
                                   dfptest_config_004.c \
                                   dfptest_config_005.c \
                                   dfptest_config_006.c \
                                   dfptest_config_007.c \
                                   dfptest_config_008.c \
                                   dfptest_config_009.c \
                                   dfptest_config_010.c 
MMWAVE_DFP_MSS_UNIT_TEST_DEPENDS	 = $(addprefix $(PLATFORM_OBJDIR)/, $(MMWAVE_DFP_MSS_UNIT_TEST_SOURCES:.c=.$(R4F_DEP_EXT)))
MMWAVE_DFP_MSS_UNIT_TEST_OBJECTS	 = $(addprefix $(PLATFORM_OBJDIR)/, $(MMWAVE_DFP_MSS_UNIT_TEST_SOURCES:.c=.$(R4F_OBJ_EXT)))

###################################################################################
# RTSC Configuration:
###################################################################################
dfpmssRTSC: $(R4_CFG)
	@echo 'Configuring RTSC packages...'
	$(XS) --xdcpath="$(XDCPATH)" xdc.tools.configuro $(R4F_XSFLAGS) -o $(MMWAVE_DFP_MSS_UNIT_TEST_CONFIGPKG) $(MMWAVE_DFP_MSS_UNIT_TEST_CFG)
	@echo 'Finished configuring packages'
	@echo ' '

###################################################################################
# Build DFP Test:
###################################################################################
dfpmssTest: BUILD_CONFIGPKG=$(MMWAVE_DFP_MSS_UNIT_TEST_CONFIGPKG)
dfpmssTest: R4F_CFLAGS += --cmd_file=$(BUILD_CONFIGPKG)/compiler.opt
dfpmssTest: buildDirectories dfpmssRTSC $(MMWAVE_DFP_MSS_UNIT_TEST_OBJECTS)
	$(R4F_LD) $(R4F_LDFLAGS) $(MMWAVE_DFP_MSS_UNIT_TEST_LOC_LIBS) $(MMWAVE_DFP_MSS_UNIT_TEST_STD_LIBS) 	\
	-l$(MMWAVE_DFP_MSS_UNIT_TEST_CONFIGPKG)/linker.cmd --map_file=$(MMWAVE_DFP_MSS_UNIT_TEST_MAP) 		\
	$(MMWAVE_DFP_MSS_UNIT_TEST_OBJECTS) $(PLATFORM_R4F_LINK_CMD) $(MMWAVE_DFP_MSS_UNIT_TEST_APP_CMD) 	\
	$(R4F_LD_RTS_FLAGS) -o $(MMWAVE_DFP_MSS_UNIT_TEST_OUT)
	@echo '******************************************************************************'
	@echo 'Built the Link MSS DFP Test '
	@echo '******************************************************************************'

###################################################################################
# Cleanup DFP Test:
###################################################################################
dfpmssTestClean:
	@echo 'Cleaning the Link MSS DFP Test objects'
	@$(DEL) $(MMWAVE_DFP_MSS_UNIT_TEST_OBJECTS) $(MMWAVE_DFP_MSS_UNIT_TEST_OUT) $(MMWAVE_DFP_MSS_UNIT_TEST_BIN)
	@$(DEL) $(MMWAVE_DFP_MSS_UNIT_TEST_MAP) $(MMWAVE_DFP_MSS_UNIT_TEST_DEPENDS)
	@echo 'Cleaning the Link MSS Unit RTSC package'
	@$(DEL) $(MMWAVE_DFP_MSS_UNIT_TEST_CONFIGPKG)
	@$(DEL) $(PLATFORM_OBJDIR)

###################################################################################
# Dependency handling
###################################################################################
-include $(MMWAVE_DFP_MSS_UNIT_TEST_DEPENDS)


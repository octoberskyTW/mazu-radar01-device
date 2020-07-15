###################################################################################
# mmWave Link DFP Test on DSS Makefile
###################################################################################
.PHONY: dfpdssTest dfpdssTestClean

###################################################################################
# Setup the VPATH:
###################################################################################
vpath %.c src
vpath %.c dfptest/$(MMWAVE_SDK_DEVICE_TYPE)
vpath %.c dfptest/common

###################################################################################
# The UART DFP test requires additional libraries
###################################################################################
MMWAVE_DFP_DSS_TEST_STD_LIBS = $(C674_COMMON_STD_LIB)									\
		   						-llibcrc_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)			\
		   						-llibmailbox_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)		\
		   						-llibtestlogger_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)	\
		   						-llibadcbuf_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)    \
                                -llibedma_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)    \
		   						-llibmmwavelink_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)
MMWAVE_DFP_DSS_TEST_LOC_LIBS = $(C674_COMMON_LOC_LIB)									\
		   						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/crc/lib			\
		   						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/mailbox/lib		\
		   						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/adcbuf/lib	   \
		   						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/drivers/edma/lib	   \
		   						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/utils/testlogger/lib	\
		   						-i$(MMWAVE_SDK_INSTALL_PATH)/ti/control/mmwavelink/lib

###################################################################################
# DFP Test Files
###################################################################################
MMWAVE_DFP_DSS_TEST_CFG	      = dfptest/$(MMWAVE_SDK_DEVICE_TYPE)/dss.cfg
MMWAVE_DFP_DSS_TEST_CMD       = $(MMWAVE_SDK_INSTALL_PATH)/ti/platform/$(MMWAVE_SDK_DEVICE_TYPE)
MMWAVE_DFP_DSS_TEST_CONFIGPKG = dfptest/$(MMWAVE_SDK_DEVICE_TYPE)/dss_configPkg_$(MMWAVE_SDK_DEVICE_TYPE)
MMWAVE_DFP_DSS_TEST_MAP       = dfptest/$(MMWAVE_SDK_DEVICE_TYPE)/$(MMWAVE_SDK_DEVICE_TYPE)_dfptest_dss.map
MMWAVE_DFP_DSS_TEST_OUT       = dfptest/$(MMWAVE_SDK_DEVICE_TYPE)/$(MMWAVE_SDK_DEVICE_TYPE)_dfptest_dss.$(C674_EXE_EXT)
MMWAVE_DFP_DSS_TEST_BIN       = dfptest/$(MMWAVE_SDK_DEVICE_TYPE)/$(MMWAVE_SDK_DEVICE_TYPE)_dfptest_dss.bin
MMWAVE_DFP_DSS_TEST_APP_CMD   = dfptest/$(MMWAVE_SDK_DEVICE_TYPE)/dss_link_linker.cmd
MMWAVE_DFP_DSS_TEST_SOURCES   = main_dfp_dss.c dfptest_setup.c dfptest_monitoring.c \
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
MMWAVE_DFP_DSS_TEST_DEPENDS   = $(addprefix $(PLATFORM_OBJDIR)/, $(MMWAVE_DFP_DSS_TEST_SOURCES:.c=.$(C674_DEP_EXT)))
MMWAVE_DFP_DSS_TEST_OBJECTS   = $(addprefix $(PLATFORM_OBJDIR)/, $(MMWAVE_DFP_DSS_TEST_SOURCES:.c=.$(C674_OBJ_EXT)))

###################################################################################
# RTSC Configuration:
###################################################################################
dfpdssRTSC:
	@echo 'Configuring RTSC packages...'
	$(XS) --xdcpath="$(XDCPATH)" xdc.tools.configuro $(C674_XSFLAGS) -o $(MMWAVE_DFP_DSS_TEST_CONFIGPKG) $(MMWAVE_DFP_DSS_TEST_CFG)
	@echo 'Finished configuring packages'
	@echo ' '

###################################################################################
# Build DFP Test:
###################################################################################
dfpdssTest: BUILD_CONFIGPKG=$(MMWAVE_DFP_DSS_TEST_CONFIGPKG)
dfpdssTest: C674_CFLAGS += --cmd_file=$(BUILD_CONFIGPKG)/compiler.opt
dfpdssTest: buildDirectories dfpdssRTSC $(MMWAVE_DFP_DSS_TEST_OBJECTS)
	$(C674_LD) $(C674_LDFLAGS) $(MMWAVE_DFP_DSS_TEST_LOC_LIBS) $(MMWAVE_DFP_DSS_TEST_STD_LIBS) 						\
	-l$(MMWAVE_DFP_DSS_TEST_CONFIGPKG)/linker.cmd --map_file=$(MMWAVE_DFP_DSS_TEST_MAP) $(MMWAVE_DFP_DSS_TEST_OBJECTS) 	\
	$(PLATFORM_C674X_LINK_CMD) $(MMWAVE_DFP_DSS_TEST_APP_CMD) $(C674_LD_RTS_FLAGS) -lrts6740_elf.lib -o $(MMWAVE_DFP_DSS_TEST_OUT)
	@echo '******************************************************************************'
	@echo 'Built the Link DSS DFP Test'
	@echo '******************************************************************************'

###################################################################################
# Cleanup DFP Test:
###################################################################################
dfpdssTestClean:
	@echo 'Cleaning the Link DSS DFP Test objects'
	@$(DEL) $(MMWAVE_DFP_DSS_TEST_OBJECTS) $(MMWAVE_DFP_DSS_TEST_OUT)
	@$(DEL) $(MMWAVE_DFP_DSS_TEST_BIN) $(MMWAVE_DFP_DSS_TEST_DEPENDS)
	@$(DEL) $(MMWAVE_DFP_DSS_TEST_MAP)
	@echo 'Cleaning the Link DSS DFP RTSC package'
	@$(DEL) $(MMWAVE_DFP_DSS_TEST_CONFIGPKG)
	@$(DEL) $(PLATFORM_OBJDIR)

###################################################################################
# Dependency handling
###################################################################################
-include $(MMWAVE_DFP_DSS_TEST_DEPENDS)


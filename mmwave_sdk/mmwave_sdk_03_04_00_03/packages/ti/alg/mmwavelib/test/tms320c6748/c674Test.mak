###################################################################################
#	mmwavelib Unit Test on c674 Makefile
###################################################################################
.PHONY: c674Test c674TestClean

###################################################################################
# Setup the VPATH:
###################################################################################
vpath %.c test/
vpath %.c $(C64Px_DSPLIB_INSTALL_PATH)/packages/ti/dsplib/src/DSP_fft16x16/c64P
vpath %.c $(C64Px_DSPLIB_INSTALL_PATH)/packages/ti/dsplib/src/DSP_fft32x32/c64P

###################################################################################
# Unit Test Files
###################################################################################
MMWAVELIB_UNIT_TEST_MAP		 = test/tms320c6748/mmwavelib_c674test.map
MMWAVELIB_UNIT_TEST_OUT		 = test/tms320c6748/mmwavelib_c674test.$(C674_EXE_EXT)
MMWAVELIB_UNIT_TEST_APP_CMD	 = test/tms320c6748/c674mmwavelib_linker.cmd

MMWAVELIB_UNIT_TEST_SOURCES  = 	lib_unittest.c\
					            gen_twiddle_fft16x16.c\
					            gen_twiddle_fft32x32.c
			    
# Compiler Flags for DSP Builds:
C674_CFLAGS  += -i$(C64Px_DSPLIB_INSTALL_PATH)/packages/ti/dsplib/src/DSP_fft16x16/c64P	\
				 -i$(C64Px_DSPLIB_INSTALL_PATH)/packages/ti/dsplib/src/DSP_fft32x32/c64P	
			    
MMWAVELIB_UNIT_TEST_DEPENDS   = $(addprefix $(PLATFORM_OBJDIR)/, $(MMWAVELIB_UNIT_TEST_SOURCES:.c=.$(C674_DEP_EXT)))
MMWAVELIB_UNIT_TEST_OBJECTS   = $(addprefix $(PLATFORM_OBJDIR)/, $(MMWAVELIB_UNIT_TEST_SOURCES:.c=.$(C674_OBJ_EXT)))


###################################################################################
# Additional libraries which are required to build the Unit Test:
###################################################################################
#STD_LIBS = -llibmmwavelib_$(MMWAVE_SDK_DEVICE_TYPE).$(DSP_LIB_EXT)    \
#           -ldsplib.lib    \
#LOC_LIBS = -i$(C64Px_DSPLIB_INSTALL_PATH)/packages/ti/dsplib/lib    \
#           -i$(MMWAVE_SDK_INSTALL_PATH)/ti/alg/mmwavelib/lib

C674_LDFLAGS  +=  -i$(C64Px_DSPLIB_INSTALL_PATH)/packages/ti/dsplib/lib    \
                 -i$(MMWAVE_SDK_INSTALL_PATH)/ti/alg/mmwavelib/lib   \
			     -i$(MMWAVE_SDK_INSTALL_PATH)/ti/utils/testlogger/lib    \
                 -llibmmwavealg_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)    \
				 -llibtestlogger_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)   \
                 -ldsplib.ae64P 
###################################################################################
# Build Unit Test:
###################################################################################
#c674Test: BUILD_CONFIGPKG=$(C674_CONFIGPKG)
#c674Test:	DSP_CFLAGS += --cmd_file=$(BUILD_CONFIGPKG)/compiler.opt
c674Test: $(MMWAVELIB_UNIT_TEST_OBJECTS)
	$(C674_LD) $(C674_LDFLAGS) -l$(MMWAVELIB_UNIT_TEST_APP_CMD) --map_file=$(MMWAVELIB_UNIT_TEST_MAP) $(MMWAVELIB_UNIT_TEST_OBJECTS) \
	 -o $(MMWAVELIB_UNIT_TEST_OUT)
	@echo '******************************************************************************'
	@echo 'Built the mmwavelib Unit Test OUT'
	@echo '******************************************************************************'

###################################################################################
# Cleanup Unit Test:
###################################################################################
c674TestClean:
	@echo 'Cleaning the Test objects'
	@$(DEL) $(MMWAVELIB_UNIT_TEST_OBJECTS) $(MMWAVELIB_UNIT_TEST_OUT) $(MMWAVELIB_UNIT_TEST_DEPENDS)

# Dependency handling
-include $(MMWAVELIB_UNIT_TEST_DEPENDS)


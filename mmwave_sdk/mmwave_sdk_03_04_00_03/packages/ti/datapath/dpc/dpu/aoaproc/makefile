##################################################################################
# aoaproc makefile
##################################################################################
# The following needs to be before any makefile inclusion
MAKEFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
MODULE_NAME := $(notdir $(patsubst %/,%,$(dir $(MAKEFILE_PATH))))

include $(MMWAVE_SDK_INSTALL_PATH)/ti/common/mmwave_sdk.mak

##################################################################################
# SOC Specific Test Targets
##################################################################################
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr16xx xwr18xx xwr68xx), )
include ./aoaproclib.mak

# HWA applicable only to specific platforms
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
include ./test/hwa_mssTest.mak 
include ./test/hwa_dssTest.mak
endif

# DSP applicable to all devices with DSP
include ./test/dsp_dssTest.mak

###################################################################################
# Standard Targets which need to be implemented by each mmWave SDK module. This
# plugs into the release scripts.
###################################################################################
.PHONY: all clean lib libClean test testClean help

##################################################################################
# Build/Clean the library 
##################################################################################

# This builds the lib
lib: aoaprocLib

# This cleans the lib
libClean: aoaprocLibClean

##################################################################################
# Test targets which are device specific
#   Build the MSS and DSS Unit Test
##################################################################################
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
test: aoaHwaMssTest aoaHwaDssTest aoaDspDssTest
testClean: aoaHwaMssTestClean aoaHwaDssTestClean aoaDspDssTestClean
else
test: aoaDspDssTest
testClean: aoaDspDssTestClean
endif

# Clean: This cleans all the objects
clean: libClean testClean

# Build everything
all: lib test

# Help: This displays the MAKEFILE Usage.
help:
	@echo '****************************************************************************************'
	@echo '* Makefile Targets for aoaproc'
	@echo 'all               -> Build lib and all unit tests'
	@echo 'clean             -> Clean out all the objects'
	@echo 'lib               -> Build the Driver only'
	@echo 'libClean          -> Clean the Driver Library only'
	@echo 'aoaHwaMssTest     -> Build the MSS Unit test for HWA AOA Proc test'
	@echo 'aoaHwaMssTestClean-> Clean the MSS Unit test for HWA AOA Proc test'
	@echo 'aoaHwaDssTest     -> Build the DSS Unit test for HWA AOA Proc test'
	@echo 'aoaHwaDssTestClean-> Clean the DSS Unit test for HWA AOA Proc test'
	@echo 'test              -> Build both DSS and MSS Unit test for HWA AOA Proc test'
	@echo 'testClean         -> Clean both DSS and MSS Unit test for HWA AOA Proc test'
	@echo 'aoaDspDssTest     -> Build the DSS Unit test for DSP AOA Proc test'
	@echo 'aoaDspDssTestClean-> Clean the DSS Unit test for DSP AOA Proc test'
	@echo '****************************************************************************************'
else
# For some reason the .DEFAULT does not seem to work for lib, test
.PHONY: lib

lib test .DEFAULT:
	@echo "Error: $(MODULE_NAME) is not supported on $(MMWAVE_SDK_DEVICE) !!!"
endif


###################################################################################
# mmWave Demo Level makefile
###################################################################################
ifeq ($(CCS_MAKEFILE_BASED_BUILD), 1)
ifeq ($(OS),Windows_NT)
include $(MMWAVE_SDK_INSTALL_PATH)/scripts/windows/setenv.mak
else
include $(MMWAVE_SDK_INSTALL_PATH)/scripts/unix/setenv.mak
endif
endif


include $(MMWAVE_SDK_INSTALL_PATH)/ti/common/mmwave_sdk.mak
include ./mmw.mak

###################################################################################
# Standard Targets which need to be implemented by each mmWave SDK module. This
# plugs into the release scripts.
###################################################################################
.PHONY: all clean
.NOTPARALLEL:

# This builds all the supported demos
all:
	$(MAKE) -s MMWAVE_SDK_LIB_BUILD_OPTION=AOP mmwDemo
	$(MAKE) -s mmwDemo

# Clean: This cleans all the objects
clean: 
	$(MAKE) -s MMWAVE_SDK_LIB_BUILD_OPTION=AOP mmwDemoClean
	$(MAKE) -s mmwDemoClean


# Help: This displays the MAKEFILE Usage.
help:
	@echo '****************************************************************************************'
	@echo '* Makefile Targets for the DEMO '
	@echo 'all             -> Builds the mmw Demo '
	@echo 'clean           -> Cleans the mmw Demo'
	@echo '****************************************************************************************'


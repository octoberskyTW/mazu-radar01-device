###################################################################################
# dopplerproc Library Makefile
###################################################################################
.PHONY: dopplerprocLib dopplerprocLibClean

###################################################################################
# Setup the VPATH:
###################################################################################
vpath %.c src

###################################################################################
# Library Source Files:
###################################################################################
# HWA applicable only to specific platforms
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
DOPPLERPROC_HWA_LIB_SOURCES = dopplerprochwa.c
endif
DOPPLERPROC_DSP_LIB_SOURCES = dopplerprocdsp.c 			

###################################################################################
# Library objects
#     Build for R4 and DSP
###################################################################################
# HWA applicable only to specific platforms
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
DOPPLERPROC_HWA_R4F_DRV_LIB_OBJECTS  = $(addprefix $(PLATFORM_OBJDIR)/, $(DOPPLERPROC_HWA_LIB_SOURCES:.c=.$(R4F_OBJ_EXT)))
DOPPLERPROC_HWA_C674_DRV_LIB_OBJECTS = $(addprefix $(PLATFORM_OBJDIR)/, $(DOPPLERPROC_HWA_LIB_SOURCES:.c=.$(C674_OBJ_EXT)))
endif

DOPPLERPROC_DSP_C674_DRV_LIB_OBJECTS = $(addprefix $(PLATFORM_OBJDIR)/, $(DOPPLERPROC_DSP_LIB_SOURCES:.c=.$(C674_OBJ_EXT)))

###################################################################################
# Library Dependency:
###################################################################################
# HWA applicable only to specific platforms
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
DOPPLERPROC_HWA_R4F_DRV_DEPENDS  = $(addprefix $(PLATFORM_OBJDIR)/, $(DOPPLERPROC_HWA_LIB_SOURCES:.c=.$(R4F_DEP_EXT)))
DOPPLERPROC_HWA_C674_DRV_DEPENDS = $(addprefix $(PLATFORM_OBJDIR)/, $(DOPPLERPROC_HWA_LIB_SOURCES:.c=.$(C674_DEP_EXT)))
endif

DOPPLERPROC_DSP_C674_DRV_DEPENDS = $(addprefix $(PLATFORM_OBJDIR)/, $(DOPPLERPROC_DSP_LIB_SOURCES:.c=.$(C674_DEP_EXT)))

###################################################################################
# Library Names:
###################################################################################
# HWA applicable only to specific platforms
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
DOPPLERPROC_HWA_R4F_DRV_LIB  = lib/libdopplerproc_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)
DOPPLERPROC_HWA_C674_DRV_LIB = lib/libdopplerproc_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)
endif

DOPPLERPROC_DSP_C674_DRV_LIB = lib/libdopplerproc_dsp_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)

###################################################################################
# Library Build:
#     - Build the R4 & DSP Library
###################################################################################
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
dopplerprocHWALib: buildDirectories $(DOPPLERPROC_HWA_R4F_DRV_LIB_OBJECTS) $(DOPPLERPROC_HWA_C674_DRV_LIB_OBJECTS)
	if [ ! -d "lib" ]; then mkdir lib; fi
	echo "Archiving $@"
	$(R4F_AR) $(R4F_AR_OPTS) $(DOPPLERPROC_HWA_R4F_DRV_LIB) $(DOPPLERPROC_HWA_R4F_DRV_LIB_OBJECTS)
	$(C674_AR) $(C674_AR_OPTS) $(DOPPLERPROC_HWA_C674_DRV_LIB) $(DOPPLERPROC_HWA_C674_DRV_LIB_OBJECTS)
endif

dopplerprocDSPLib: C674_CFLAGS += -i$(C674x_MATHLIB_INSTALL_PATH)/packages \
								-i$(C64Px_DSPLIB_INSTALL_PATH)/packages/ti/dsplib/src/DSP_fft32x32/c64P
dopplerprocDSPLib: buildDirectories $(DOPPLERPROC_DSP_C674_DRV_LIB_OBJECTS)
	if [ ! -d "lib" ]; then mkdir lib; fi
	echo "Archiving $@"
	$(C674_AR) $(C674_AR_OPTS) $(DOPPLERPROC_DSP_C674_DRV_LIB) $(DOPPLERPROC_DSP_C674_DRV_LIB_OBJECTS)

ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
dopplerprocLib: dopplerprocHWALib dopplerprocDSPLib
else
dopplerprocLib: dopplerprocDSPLib
endif

###################################################################################
# Clean the Libraries
###################################################################################
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
dopplerprocHWALibClean:
	@echo 'Cleaning the HWA dopplerproc Library Objects'
	@$(DEL) $(DOPPLERPROC_HWA_R4F_DRV_LIB_OBJECTS) $(DOPPLERPROC_HWA_R4F_DRV_LIB)
	@$(DEL) $(DOPPLERPROC_HWA_C674_DRV_LIB_OBJECTS) $(DOPPLERPROC_HWA_C674_DRV_LIB)
	@$(DEL) $(DOPPLERPROC_HWA_R4F_DRV_DEPENDS) $(DOPPLERPROC_HWA_C674_DRV_DEPENDS)
	@$(DEL) $(PLATFORM_OBJDIR)
endif

dopplerprocDSPLibClean:
	@echo 'Cleaning the dopplerproc DSP Library Objects'
	@$(DEL) $(DOPPLER_DSP_C674_DRV_LIB_OBJECTS) $(DOPPLER_DSP_C674_DRV_LIB)
	@$(DEL) $(DOPPLER_DSP_C674_DRV_DEPENDS)
	@$(DEL) $(PLATFORM_OBJDIR)

ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
dopplerprocLibClean: dopplerprocHWALibClean dopplerprocDSPLibClean
else
dopplerprocLibClean: dopplerprocDSPLibClean
endif

###################################################################################
# Dependency handling
###################################################################################
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
-include $(DOPPLERPROC_HWA_R4F_DRV_DEPENDS)
-include $(DOPPLERPROC_HWA_C674_DRV_DEPENDS)
endif
-include $(DOPPLERPROC_DSP_C674_DRV_DEPENDS)


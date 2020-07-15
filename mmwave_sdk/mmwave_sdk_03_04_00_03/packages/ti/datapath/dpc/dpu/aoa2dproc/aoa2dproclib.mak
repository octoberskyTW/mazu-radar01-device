###################################################################################
# aoa2dproc Library Makefile
###################################################################################
.PHONY: aoa2dprocLib aoa2dprocLibClean

###################################################################################
# Setup the VPATH:
###################################################################################
vpath %.c src

###################################################################################
# Library Source Files:
###################################################################################
# HWA applicable only to specific platforms
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
AOA2DPROC_HWA_LIB_SOURCES = aoa2dprochwa.c
endif

###################################################################################
# Library objects
#     Build for R4
###################################################################################
# HWA applicable only to specific platforms
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
AOA2DPROC_HWA_R4F_DRV_LIB_OBJECTS  = $(addprefix $(PLATFORM_OBJDIR)/, $(AOA2DPROC_HWA_LIB_SOURCES:.c=.$(R4F_OBJ_EXT)))
AOA2DPROC_HWA_C674_DRV_LIB_OBJECTS = $(addprefix $(PLATFORM_OBJDIR)/, $(AOA2DPROC_HWA_LIB_SOURCES:.c=.$(C674_OBJ_EXT)))
endif


###################################################################################
# Library Dependency:
###################################################################################
# HWA applicable only to specific platforms
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
AOA2DPROC_HWA_R4F_DRV_DEPENDS  = $(addprefix $(PLATFORM_OBJDIR)/, $(AOA2DPROC_HWA_LIB_SOURCES:.c=.$(R4F_DEP_EXT)))
AOA2DPROC_HWA_C674_DRV_DEPENDS = $(addprefix $(PLATFORM_OBJDIR)/, $(AOA2DPROC_HWA_LIB_SOURCES:.c=.$(C674_DEP_EXT)))
endif


###################################################################################
# Library Names:
###################################################################################
# HWA applicable only to specific platforms
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
AOA2DPROC_HWA_R4F_DRV_LIB  = lib/libaoa2dproc_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)
AOA2DPROC_HWA_C674_DRV_LIB = lib/libaoa2dproc_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)
endif

###################################################################################
# Library Build:
#     - Build the R4 & DSP Library
###################################################################################
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
aoa2dprocHWALib: buildDirectories $(AOA2DPROC_HWA_R4F_DRV_LIB_OBJECTS) $(AOA2DPROC_HWA_C674_DRV_LIB_OBJECTS)
	if [ ! -d "lib" ]; then mkdir lib; fi
	echo "Archiving $@"
	$(R4F_AR) $(R4F_AR_OPTS) $(AOA2DPROC_HWA_R4F_DRV_LIB) $(AOA2DPROC_HWA_R4F_DRV_LIB_OBJECTS)	
	$(C674_AR) $(C674_AR_OPTS) $(AOA2DPROC_HWA_C674_DRV_LIB) $(AOA2DPROC_HWA_C674_DRV_LIB_OBJECTS)

aoa2dprocLib: aoa2dprocHWALib 
endif

###################################################################################
# Clean the Libraries
###################################################################################
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
aoa2dprocHWALibClean:
	@echo 'Cleaning the aoa2dproc Library Objects'
	@$(DEL) $(AOA2DPROC_HWA_R4F_DRV_LIB_OBJECTS) $(AOA2DPROC_HWA_R4F_DRV_LIB)
	@$(DEL) $(AOA2DPROC_HWA_C674_DRV_LIB_OBJECTS) $(AOA2DPROC_HWA_C674_DRV_LIB)
	@$(DEL) $(AOA2DPROC_HWA_R4F_DRV_DEPENDS) $(AOA2DPROC_HWA_C674_DRV_DEPENDS)
	@$(DEL) $(PLATFORM_OBJDIR)

aoa2dprocLibClean: aoa2dprocHWALibClean 
endif

###################################################################################
# Dependency handling
###################################################################################
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
-include $(AOA2DPROC_HWA_R4F_DRV_DEPENDS)
-include $(AOA2DPROC_HWA_C674_DRV_DEPENDS)
endif



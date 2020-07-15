###################################################################################
# cfarcaproc Library Makefile
###################################################################################
.PHONY: cfarcaprocLib cfarcaprocLibClean

###################################################################################
# Setup the VPATH:
###################################################################################
vpath %.c src

###################################################################################
# Library Source Files:
###################################################################################
CFARCAPROC_HWA_LIB_SOURCES = cfarcaprochwa.c
CFARCAPROC_DSP_LIB_SOURCES = cfarcaprocdsp.c

###################################################################################
# Library objects
#     Build for R4 and DSP
###################################################################################
CFARCAPROC_HWA_R4F_DRV_LIB_OBJECTS  = $(addprefix $(PLATFORM_OBJDIR)/, $(CFARCAPROC_HWA_LIB_SOURCES:.c=.$(R4F_OBJ_EXT)))
CFARCAPROC_HWA_C674_DRV_LIB_OBJECTS = $(addprefix $(PLATFORM_OBJDIR)/, $(CFARCAPROC_HWA_LIB_SOURCES:.c=.$(C674_OBJ_EXT)))
CFARCAPROC_DSP_C674_DRV_LIB_OBJECTS = $(addprefix $(PLATFORM_OBJDIR)/, $(CFARCAPROC_DSP_LIB_SOURCES:.c=.$(C674_OBJ_EXT)))

###################################################################################
# Library Dependency:
###################################################################################
CFARCAPROC_HWA_R4F_DRV_DEPENDS  = $(addprefix $(PLATFORM_OBJDIR)/, $(CFARCAPROC_HWA_LIB_SOURCES:.c=.$(R4F_DEP_EXT)))
CFARCAPROC_HWA_C674_DRV_DEPENDS = $(addprefix $(PLATFORM_OBJDIR)/, $(CFARCAPROC_HWA_LIB_SOURCES:.c=.$(C674_DEP_EXT)))
CFARCAPROC_DSP_C674_DRV_DEPENDS = $(addprefix $(PLATFORM_OBJDIR)/, $(CFARCAPROC_DSP_LIB_SOURCES:.c=.$(C674_DEP_EXT)))

###################################################################################
# Library Names:
###################################################################################
CFARCAPROC_HWA_R4F_DRV_LIB  = lib/libcfarcaproc_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(R4F_LIB_EXT)
CFARCAPROC_HWA_C674_DRV_LIB = lib/libcfarcaproc_hwa_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)
CFARCAPROC_DSP_C674_DRV_LIB = lib/libcfarcaproc_dsp_$(MMWAVE_SDK_DEVICE_TYPE).$(C674_LIB_EXT)

###################################################################################
# Library Build:
#     - Build the R4 & DSP Library
###################################################################################
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
cfarcaprocHWALib: buildDirectories $(CFARCAPROC_HWA_R4F_DRV_LIB_OBJECTS) $(CFARCAPROC_HWA_C674_DRV_LIB_OBJECTS)
	if [ ! -d "lib" ]; then mkdir lib; fi
	echo "Archiving $@"
	$(R4F_AR) $(R4F_AR_OPTS) $(CFARCAPROC_HWA_R4F_DRV_LIB) $(CFARCAPROC_HWA_R4F_DRV_LIB_OBJECTS)
	$(C674_AR) $(C674_AR_OPTS) $(CFARCAPROC_HWA_C674_DRV_LIB) $(CFARCAPROC_HWA_C674_DRV_LIB_OBJECTS)
endif
cfarcaprocDSPLib: C674_CFLAGS += -i$(C674x_MATHLIB_INSTALL_PATH)/packages

cfarcaprocDSPLib: buildDirectories $(CFARCAPROC_DSP_C674_DRV_LIB_OBJECTS)
	if [ ! -d "lib" ]; then mkdir lib; fi
	echo "Archiving $@"
	$(C674_AR) $(C674_AR_OPTS) $(CFARCAPROC_DSP_C674_DRV_LIB) $(CFARCAPROC_DSP_C674_DRV_LIB_OBJECTS)

ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
cfarcaprocLib: cfarcaprocHWALib cfarcaprocDSPLib
else
cfarcaprocLib: cfarcaprocDSPLib
endif
###################################################################################
# Clean the Libraries
###################################################################################
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
cfarcaprocHWALibClean:
	@echo 'Cleaning the cfarcaproc Library Objects'
	@$(DEL) $(CFARCAPROC_HWA_R4F_DRV_LIB_OBJECTS) $(CFARCAPROC_HWA_R4F_DRV_LIB)
	@$(DEL) $(CFARCAPROC_HWA_C674_DRV_LIB_OBJECTS) $(CFARCAPROC_HWA_C674_DRV_LIB)
	@$(DEL) $(CFARCAPROC_HWA_R4F_DRV_DEPENDS) $(CFARCAPROC_HWA_C674_DRV_DEPENDS)
	@$(DEL) $(PLATFORM_OBJDIR)
endif
cfarcaprocDSPLibClean:
	@echo 'Cleaning the cfarcaproc Library Objects'
	@$(DEL) $(CFARCAPROC_DSP_C674_DRV_LIB_OBJECTS) $(CFARCAPROC_DSP_C674_DRV_LIB)
	@$(DEL) $(CFARCAPROC_DSP_C674_DRV_DEPENDS)
	@$(DEL) $(PLATFORM_OBJDIR)

ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
cfarcaprocLibClean: cfarcaprocHWALibClean cfarcaprocDSPLibClean
endif

cfarcaprocLibClean: cfarcaprocDSPLibClean

###################################################################################
# Dependency handling
###################################################################################
ifneq ($(filter $(MMWAVE_SDK_DEVICE_TYPE),xwr18xx xwr68xx), )
-include $(CFARCAPROC_HWA_R4F_DRV_DEPENDS)
-include $(CFARCAPROC_HWA_C674_DRV_DEPENDS)
endif
-include $(CFARCAPROC_DSP_C674_DRV_DEPENDS)

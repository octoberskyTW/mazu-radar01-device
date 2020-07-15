##############################################################################
#
#
# Makefile for C6000 run-time support library version 8.3.3
#
#
##############################################################################
#
# This Makefile is automatically-generated: you usually should not edit it. 
#
##############################################################################


##############################################################################
#
# This Makefile is specific to compiler RTS library version 8.3.3.  
# The format is subject to change without notice.  This Makefile is intended
# for use with mklib, which understands which 'make' variables to set to build
# each distinct version of the RTS library.
#
# This Makefile uses GNU make language extensions.
#
##############################################################################

##############################################################################
#
# GROUPS
#
# The source files are set up in a modular fashion using "groups."  Groups
# represent major feature clusters, and usually specify source files which
# implement that feature.  When building a library which needs a particular
# feature, the group which represents that feature is "activated" by setting a
# 'make' variable.  This variable can be set directly by the user, or may be
# inferred from the setting of other variables.  Groups (and the files they
# contain) not needed for a certain library are not activated.  Some groups
# are always activated.  Groups which are not always activated are enclosed in
# an "ifeq" testing the corresponding 'make' variable (the name of the
# variable is the name of the group).
#
# Groups can specify any kind of source file (e.g. C, C++, assembly), but do
# not list header files, or source files included from other source files.
# This Makefile is focused on how to build the object files, not listing all
# of the necessary files.  Some groups do not list any source files; these
# groups may still carry information such as extra options to use when that
# group is active, or may activate other groups.  Some groups exist only to be
# tested as part of the activation condition of other groups.
#
# Groups can specify extra compiler options to use when that group is active.
# These can be options intended for all targets (UNIVERSAL_FLAGS), such as the
# CPU version, or can be intended only for a certain type of files (CPP_FLAGS)
# (e.g. the option "--exceptions")
#
##############################################################################

##############################################################################
#
# OPTIONS
#
# You can append or override some options through 'make' variables specified
# on the command line.  Not all options can be changed this way, and some
# options are dangerous to use in a Makefile (e.g. "--skip_assembler").
# Options added by groups below should not be altered; if the option is
# undesired, you're probably building the wrong library.  For example, if you
# don't want "--exceptions", you shouldn't be using EXCEPTIONS=1.
#
# You can append options to the standard list by using EXTRA_FLAGS.  This is
# useful for enabling debugging support or activating silicon errata
# workarounds:
#
# gmake LIB=some.lib EXTRA_FLAGS="-g"
#
##############################################################################

##############################################################################
# Available libraries
#
# You can build each 8.3.3 library using the appropriate command:
#
# gmake library LIB=rts64plus_elf.lib C64P=1
# gmake library LIB=rts64plus_elf_eh.lib EABI_TDEH=1 C64P=1 EXCEPTIONS=1
# gmake library LIB=rts64plus_elf_mt.lib C64P=1 MT=1
# gmake library LIB=rts64plus_elf_mt_eh.lib EABI_TDEH=1 MT=1 C64P=1 EXCEPTIONS=1
# gmake library LIB=rts64pluse_elf.lib BIG_ENDIAN=1 C64P=1
# gmake library LIB=rts64pluse_elf_eh.lib BIG_ENDIAN=1 EXCEPTIONS=1 EABI_TDEH=1 C64P=1
# gmake library LIB=rts64pluse_elf_mt.lib MT=1 C64P=1 BIG_ENDIAN=1
# gmake library LIB=rts64pluse_elf_mt_eh.lib C64P=1 EABI_TDEH=1 MT=1 EXCEPTIONS=1 BIG_ENDIAN=1
# gmake library LIB=rts6600_elf.lib C6600=1
# gmake library LIB=rts6600_elf_eh.lib C6600=1 EABI_TDEH=1 EXCEPTIONS=1
# gmake library LIB=rts6600_elf_mt.lib MT=1 C6600=1
# gmake library LIB=rts6600_elf_mt_eh.lib EABI_TDEH=1 C6600=1 MT=1 EXCEPTIONS=1
# gmake library LIB=rts6600e_elf.lib C6600=1 BIG_ENDIAN=1
# gmake library LIB=rts6600e_elf_eh.lib C6600=1 EABI_TDEH=1 BIG_ENDIAN=1 EXCEPTIONS=1
# gmake library LIB=rts6600e_elf_mt.lib MT=1 C6600=1 BIG_ENDIAN=1
# gmake library LIB=rts6600e_elf_mt_eh.lib EXCEPTIONS=1 BIG_ENDIAN=1 EABI_TDEH=1 C6600=1 MT=1
# gmake library LIB=rts6740_elf.lib C6740=1
# gmake library LIB=rts6740_elf_eh.lib EABI_TDEH=1 C6740=1 EXCEPTIONS=1
# gmake library LIB=rts6740_elf_mt.lib MT=1 C6740=1
# gmake library LIB=rts6740_elf_mt_eh.lib EXCEPTIONS=1 C6740=1 EABI_TDEH=1 MT=1
# gmake library LIB=rts6740e_elf.lib BIG_ENDIAN=1 C6740=1
# gmake library LIB=rts6740e_elf_eh.lib C6740=1 BIG_ENDIAN=1 EXCEPTIONS=1 EABI_TDEH=1
# gmake library LIB=rts6740e_elf_mt.lib MT=1 BIG_ENDIAN=1 C6740=1
# gmake library LIB=rts6740e_elf_mt_eh.lib C6740=1 BIG_ENDIAN=1 EXCEPTIONS=1 MT=1 EABI_TDEH=1
##############################################################################

ifdef CMD_FILE
 -include $(CMD_FILE)
endif
#-----------------------------------------------------------------------------
# Basic definitions
#-----------------------------------------------------------------------------
ifeq (y,$(shell [ -e $(CGT_BIN)/cl6x ] && echo y))
  CC = $(CGT_BIN)/cl6x
else
  CC = cl6x
endif
ifeq (y,$(shell [ -e $(CGT_BIN)/ar6x ] && echo y))
  AR = $(CGT_BIN)/ar6x
else
  AR = ar6x
endif
CD = cd

#-----------------------------------------------------------------------------
# Group TARGET
#-----------------------------------------------------------------------------
UNIVERSAL_FLAGS += -mo --mem_model:data=far --no_visible_enums

TARGET_C_SOURCE = \
	boot.c \
	dtos.c \
	gsmfuncs.c \
	gsmvars.c \
	imath40.c \
	imath64.c \
	llshift.c \
	lltoa.c \
	memcpy62.c \
	mpyll.c \
	memset.c \
	outprof.c \
	pprof_cio.c \
	pprof_user.c \
	autoinit.c \
	pre_init.c \
	startup.c \
	cpy_tbl.c \
	copy_zero_init.c \
	copy_decompress_none.c \
	copy_decompress_rle.c \
	copy_decompress_lzss.c

C_SOURCE += $(TARGET_C_SOURCE)


TARGET_LINASM_SOURCE = \
	negll.sa

LINASM_SOURCE += $(TARGET_LINASM_SOURCE)


#-----------------------------------------------------------------------------
# Group GENERIC_MATH_LIBRARY_DOUBLE_IS_64
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group GENERIC_MATH_FUNDAMENTAL_DOUBLE_IS_64
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group GENERIC_MATH_LIBRARY_FLOAT
#-----------------------------------------------------------------------------

GENERIC_MATH_LIBRARY_FLOAT_C_SOURCE = \
	absf.c \
	acosf.c \
	acoshf.c \
	acot2f.c \
	acotf.c \
	acothf.c \
	asinf.c \
	asinhf.c \
	atanf.c \
	atan2f.c \
	atanhf.c \
	ceilf.c \
	cosf.c \
	coshf.c \
	cotf.c \
	cothf.c \
	exp10f.c \
	exp2f.c \
	expf.c \
	fabsf.c \
	floorf.c \
	fmodf.c \
	fpclassifyf.c \
	frexpf.c \
	isfinitef.c \
	isinff.c \
	isnanf.c \
	isnormalf.c \
	ldexpf.c \
	log10f.c \
	log2f.c \
	logf.c \
	modff.c \
	powif.c \
	powf.c \
	roundf.c \
	rsqrtf.c \
	sinf.c \
	sinhf.c \
	sqrtf.c \
	tanf.c \
	tanhf.c \
	truncf.c

C_SOURCE += $(GENERIC_MATH_LIBRARY_FLOAT_C_SOURCE)


#-----------------------------------------------------------------------------
# Group GENERIC_MATH_LIBRARY_DOUBLE
#-----------------------------------------------------------------------------

GENERIC_MATH_LIBRARY_DOUBLE_C_SOURCE = \
	absd.c \
	acos.c \
	acosh.c \
	acot.c \
	acot2.c \
	acoth.c \
	asin.c \
	asinh.c \
	atan.c \
	atan2.c \
	atanh.c \
	ceil.c \
	cos.c \
	cosh.c \
	cot.c \
	coth.c \
	exp.c \
	exp10.c \
	exp2.c \
	fabs.c \
	floor.c \
	fmod.c \
	fpclassify.c \
	frexp.c \
	isfinite.c \
	isinf.c \
	isnan.c \
	isnormal.c \
	ldexp.c \
	log.c \
	log10.c \
	log2.c \
	modf.c \
	pow.c \
	powi.c \
	round.c \
	rsqrt.c \
	sin.c \
	sinh.c \
	sqrt.c \
	tan.c \
	tanh.c \
	trunc.c \
	signbit.c

C_SOURCE += $(GENERIC_MATH_LIBRARY_DOUBLE_C_SOURCE)


#-----------------------------------------------------------------------------
# Group GENERIC_MATH_FUNDAMENTAL_FLOAT
#-----------------------------------------------------------------------------

GENERIC_MATH_FUNDAMENTAL_FLOAT_C_SOURCE = \
	addf.c \
	cmpf.c \
	eqlf.c \
	gef.c \
	gtf.c \
	lef.c \
	ltf.c \
	neqlf.c \
	cvtdf.c \
	divf.c \
	fixfi.c \
	fixfli.c \
	fixflli.c \
	fixfu.c \
	fixful.c \
	fixfull.c \
	fltif.c \
	fltlif.c \
	fltllif.c \
	fltuf.c \
	fltulf.c \
	fltullf.c \
	frcaddf.c \
	frcdivf.c \
	frcmpyf.c \
	frcmpyf_div.c \
	mpyf.c \
	negf.c \
	renormf.c \
	subf.c

C_SOURCE += $(GENERIC_MATH_FUNDAMENTAL_FLOAT_C_SOURCE)


#-----------------------------------------------------------------------------
# Group LIBCXX_CPP
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group GENERIC_MATH_FUNDAMENTAL_DOUBLE
#-----------------------------------------------------------------------------

GENERIC_MATH_FUNDAMENTAL_DOUBLE_C_SOURCE = \
	addd.c \
	cmpd.c \
	eqld.c \
	ged.c \
	gtd.c \
	led.c \
	ltd.c \
	neqld.c \
	cvtfd.c \
	divd.c \
	fixdi.c \
	fixdli.c \
	fixdlli.c \
	fixdu.c \
	fixdul.c \
	fixdull.c \
	fltid.c \
	fltlid.c \
	fltllid.c \
	fltud.c \
	fltuld.c \
	fltulld.c \
	frcaddd.c \
	frcdivd.c \
	frcmpyd.c \
	frcmpyd_div.c \
	mpyd.c \
	negd.c \
	renormd.c \
	subd.c

C_SOURCE += $(GENERIC_MATH_FUNDAMENTAL_DOUBLE_C_SOURCE)


#-----------------------------------------------------------------------------
# Group GENERIC_MATH_COMMON_64BIT
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group EDG_GENERIC_C
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group FULL_WCHAR
#-----------------------------------------------------------------------------
FULL_WCHAR_FLAGS += -DSTRIP_FBSDID -D_XOPEN_SOURCE=700 --diag_suppress=188

FULL_WCHAR_C_SOURCE = \
	wcstof.c \
	wcstod.c \
	wcstold.c \
	wcstol.c \
	wcstoul.c \
	wcstoll.c \
	wcstoull.c \
	wcstoimax.c \
	wcstoumax.c \
	wcsftime.c \
	fwprintf.c \
	fwscanf.c \
	swprintf.c \
	swscanf.c \
	vwprintf.c \
	vwscanf.c \
	wprintf.c \
	wscanf.c \
	wcscat.c \
	wcschr.c \
	wcscmp.c \
	wcscpy.c \
	wcscspn.c \
	wcsdup.c \
	wcslen.c \
	wcsncat.c \
	wcsncmp.c \
	wcsncpy.c \
	wcspbrk.c \
	wcsrchr.c \
	wcsspn.c \
	wcsstr.c \
	wcstok.c \
	wmemchr.c \
	wmemcpy.c \
	wmemcmp.c \
	wmemmove.c \
	wmemset.c \
	none_mb.c \
	fgetwc.c \
	fgetws.c \
	fputws.c \
	vfwprintf.c \
	vfwscanf.c \
	vswprintf.c \
	vswscanf.c \
	wcscoll.c \
	wcsxfrm.c

#-----------------------------------------------------------------------------
# Group GENERIC_MATH_COMMON_32BIT
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group GENERIC_MATH_COMMON_FLOAT
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group GENERIC_MATH_COMMON_DOUBLE
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group TSPA_C99_COMPLEX
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group XLOCALE
#-----------------------------------------------------------------------------
XLOCALE_FLAGS += -DSTRIP_FBSDID -D_XOPEN_SOURCE=700 --diag_suppress=188

XLOCALE_C_SOURCE = \
	xlocale.c \
	locale_inttypes.c \
	locale_stdio.c \
	locale_stdlib.c \
	locale_string.c \
	locale_strings.c \
	locale_time.c \
	locale_wchar.c

#-----------------------------------------------------------------------------
# Group EXCEPTIONS
#-----------------------------------------------------------------------------
ifeq ($(EXCEPTIONS),1)
CPP_FLAGS += --exceptions
endif


#-----------------------------------------------------------------------------
# Group C6740
#-----------------------------------------------------------------------------
ifeq ($(C6740),1)
VECTOR_TYPES=1
UNIVERSAL_FLAGS += -mv6740 --no_parallel_loads
endif


#-----------------------------------------------------------------------------
# Group GENERIC_C
#-----------------------------------------------------------------------------

GENERIC_C_C_SOURCE = \
	ecvt.c \
	exit.c \
	fcvt.c \
	memory.c \
	_data_synch.c \
	_lock.c \
	_ltoa.c \
	_mutex.c \
	_pthread.c \
	add_device.c \
	args_main.c \
	asctime.c \
	assert.c \
	atof.c \
	atoi.c \
	atol.c \
	atoll.c \
	bcmp.c \
	bcopy.c \
	bsearch.c \
	bzero.c \
	clearerr.c \
	clock.c \
	close.c \
	common_exit.c \
	ctime_.c \
	ctime64.c \
	ctype.c \
	defs.c \
	difftime.c \
	difftime64.c \
	ffs.c \
	gmtime.c \
	gmtime64.c \
	index.c \
	isalnum.c \
	isalpha.c \
	isascii.c \
	iscntrl.c \
	isdigit.c \
	isgraph.c \
	islower.c \
	isprint.c \
	ispunct.c \
	isspace.c \
	isupper.c \
	isxdigit.c \
	localtim.c \
	localtim64.c \
	lseek.c \
	ltoa.c \
	memccpy.c \
	memchr.c \
	memcmp.c \
	memmov.c \
	mktime.c \
	mktime64.c \
	open.c \
	perror.c \
	qsort.c \
	rand.c \
	read.c \
	remove.c \
	remove_device.c \
	rename.c \
	rewind.c \
	rindex.c \
	setlocale.c \
	strcasecmp.c \
	strcat.c \
	strchr.c \
	strcmp.c \
	strcoll.c \
	strcpy.c \
	strcspn.c \
	strdup.c \
	strerror.c \
	strftime.c \
	strlen.c \
	strncasecmp.c \
	strncat.c \
	strncmp.c \
	strncpy.c \
	strpbrk.c \
	strrchr.c \
	strspn.c \
	strstr.c \
	strtod.c \
	strtof.c \
	strtok.c \
	strtol.c \
	strtold.c \
	strtoll.c \
	strtoul.c \
	strtoull.c \
	strtoimax.c \
	strtoumax.c \
	strxfrm.c \
	time.c \
	time64.c \
	tmpfile.c \
	tmpnam.c \
	tmzone.c \
	toascii.c \
	tolower.c \
	toupper.c \
	hostclock.c \
	hostclose.c \
	hostgetenv.c \
	hostlseek.c \
	hostopen.c \
	hostread.c \
	hostrename.c \
	hosttime.c \
	hostunlink.c \
	hostwrite.c \
	trgmsg.c \
	unlink.c \
	wctype.c \
	write.c \
	signal.c

C_SOURCE += $(GENERIC_C_C_SOURCE)


#-----------------------------------------------------------------------------
# Group GENERIC_MATH_LIBRARY_COMMON
#-----------------------------------------------------------------------------
UNIVERSAL_FLAGS += -D__TI_USING_GENERIC_MATH

#-----------------------------------------------------------------------------
# Group FREEBSD_C99_COMPLEX
#-----------------------------------------------------------------------------
FREEBSD_C99_COMPLEX_C_FLAGS += --c99

#-----------------------------------------------------------------------------
# Group C64P
#-----------------------------------------------------------------------------
ifeq ($(C64P),1)
VECTOR_TYPES=1
UNIVERSAL_FLAGS += -mv64+ --no_parallel_loads
endif


#-----------------------------------------------------------------------------
# Group GENERIC_MATH_COMMON
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group C6XABI
#-----------------------------------------------------------------------------
UNIVERSAL_FLAGS += --abi=eabi

C6XABI_C_SOURCE = \
	weak_return.c \
	divrem.c \
	tls.c

C_SOURCE += $(C6XABI_C_SOURCE)


C6XABI_CPP_SOURCE = \
	tdeh_pr_c6000.cpp

CPP_SOURCE += $(C6XABI_CPP_SOURCE)


C6XABI_ASM_SOURCE = \
	tdeh_uwentry_c6000.asm \
	tls_get_tp.asm

ASM_SOURCE += $(C6XABI_ASM_SOURCE)


#-----------------------------------------------------------------------------
# Group FREEBSD_MATH_GENERIC_SUPPLEMENT
#-----------------------------------------------------------------------------

FREEBSD_MATH_GENERIC_SUPPLEMENT_C_SOURCE = \
	ti_fenv.c \
	ti_fmax.c \
	ti_nan.c

C_SOURCE += $(FREEBSD_MATH_GENERIC_SUPPLEMENT_C_SOURCE)


#-----------------------------------------------------------------------------
# Group LIBCXX_CPP_LIB
#-----------------------------------------------------------------------------
LIBCXX_CPP_LIB_FLAGS += -D_LIBCPP_BUILDING_LIBRARY --preinclude __config_site
UNIVERSAL_FLAGS += -D_TI_USING_LIBCXX

LIBCXX_CPP_LIB_CPP_SOURCE = \
	libcxx/algorithm.cpp \
	libcxx/bind.cpp \
	libcxx/chrono.cpp \
	libcxx/condition_variable.cpp \
	libcxx/debug.cpp \
	libcxx/exception.cpp \
	libcxx/functional.cpp \
	libcxx/hash.cpp \
	libcxx/ios.cpp \
	libcxx/memory.cpp \
	libcxx/mutex.cpp \
	libcxx/new.cpp \
	libcxx/random.cpp \
	libcxx/regex.cpp \
	libcxx/stdexcept.cpp \
	libcxx/string.cpp \
	libcxx/strstream.cpp \
	libcxx/system_error.cpp \
	libcxx/typeinfo.cpp \
	libcxx/utility.cpp \
	libcxx/valarray.cpp \
	libcxx/variant.cpp \
	libcxx/vector.cpp

#-----------------------------------------------------------------------------
# Group C6600
#-----------------------------------------------------------------------------
ifeq ($(C6600),1)
VECTOR_TYPES=1
UNIVERSAL_FLAGS += -mv6600
endif


#-----------------------------------------------------------------------------
# Group LIBCXX_CPP_NO_LTO
#-----------------------------------------------------------------------------
LIBCXX_CPP_NO_LTO_FLAGS += -o3

LIBCXX_CPP_NO_LTO_CPP_SOURCE = \
	libcxx/iostream.cpp \
	libcxx/locale.cpp

#-----------------------------------------------------------------------------
# Group GENERIC_C_SIZE_OPTIMIZED
#-----------------------------------------------------------------------------
GENERIC_C_SIZE_OPTIMIZED_FLAGS += -mf3

GENERIC_C_SIZE_OPTIMIZED_C_SOURCE = \
	printf.c \
	fprintf.c \
	_printfi.c \
	_printfi_min.c \
	_printfi_nf.c \
	_printfi_vector.c \
	snprintf.c \
	sprintf.c \
	vfprintf.c \
	vprintf.c \
	vsnprintf.c \
	vsprintf.c \
	_scanfi.c \
	_scanfi_min.c \
	_scanfi_nf.c \
	fscanf.c \
	sscanf.c \
	fclose.c \
	feof.c \
	ferror.c \
	fflush.c \
	fgetc.c \
	fgetpos.c \
	fgets.c \
	fopen.c \
	fputc.c \
	fputs.c \
	fread.c \
	fseek.c \
	fsetpos.c \
	ftell.c \
	fwrite.c \
	_bufread.c \
	_io_perm.c \
	getenv.c \
	getdevice.c \
	setbuf.c \
	setvbuf.c \
	ungetc.c

#-----------------------------------------------------------------------------
# Group GENERIC_MATH_LIBRARY_INTEGER
#-----------------------------------------------------------------------------

GENERIC_MATH_LIBRARY_INTEGER_C_SOURCE = \
	div.c \
	ldiv.c \
	lldiv.c

C_SOURCE += $(GENERIC_MATH_LIBRARY_INTEGER_C_SOURCE)


#-----------------------------------------------------------------------------
# Group BIG_ENDIAN
#-----------------------------------------------------------------------------
ifeq ($(BIG_ENDIAN),1)
UNIVERSAL_FLAGS += -me
endif


#-----------------------------------------------------------------------------
# Group FREEBSD_FENV
#-----------------------------------------------------------------------------

FREEBSD_FENV_C_SOURCE = \
	fenv.c

C_SOURCE += $(FREEBSD_FENV_C_SOURCE)


#-----------------------------------------------------------------------------
# Group FREEBSD_SUPPLEMENTAL_C
#-----------------------------------------------------------------------------

FREEBSD_SUPPLEMENTAL_C_C_SOURCE = \
	asprintf.c \
	vasprintf.c

C_SOURCE += $(FREEBSD_SUPPLEMENTAL_C_C_SOURCE)


#-----------------------------------------------------------------------------
# Group FREEBSD_C99_COMPLEX_32_BIT
#-----------------------------------------------------------------------------
FREEBSD_C99_COMPLEX_32_BIT_C_FLAGS += --c99

FREEBSD_C99_COMPLEX_32_BIT_C_SOURCE = \
	catrigf.c \
	k_expf.c \
	s_carg.c \
	s_cargf.c \
	s_cargl.c \
	s_ccoshf.c \
	s_cexpf.c \
	s_cimag.c \
	s_cimagf.c \
	s_cimagl.c \
	s_conj.c \
	s_conjf.c \
	s_conjl.c \
	s_cproj.c \
	s_cprojf.c \
	s_cprojl.c \
	s_creal.c \
	s_crealf.c \
	s_creall.c \
	s_csinhf.c \
	s_csqrtf.c \
	s_ctanhf.c \
	w_cabs.c \
	w_cabsf.c \
	w_cabsl.c \
	s_log1pf.c \
	e_hypotf.c \
	s_copysignf.c

#-----------------------------------------------------------------------------
# Group FREEBSD_MACHINE
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group FREEBSD_C99_COMPLEX_64_BIT
#-----------------------------------------------------------------------------
FREEBSD_C99_COMPLEX_64_BIT_C_FLAGS += --c99

FREEBSD_C99_COMPLEX_64_BIT_C_SOURCE = \
	catrig.c \
	k_exp.c \
	s_ccosh.c \
	s_cexp.c \
	s_csinh.c \
	s_csqrt.c \
	s_ctanh.c \
	s_log1p.c \
	e_hypot.c \
	s_copysign.c

#-----------------------------------------------------------------------------
# Group EDG_CPP_SUPPLEMENTAL
#-----------------------------------------------------------------------------
EDG_CPP_SUPPLEMENTAL_CPP_FLAGS += --building_runtime -DCHECKING=0

EDG_CPP_SUPPLEMENTAL_CPP_SOURCE = \
	exception.c \
	bad_alloc.c

#-----------------------------------------------------------------------------
# Group GENERIC_OPTIONS
#-----------------------------------------------------------------------------
ASM_FLAGS += 
CPP_FLAGS += --rtti -fg
UNIVERSAL_FLAGS += -c --ti_lib --keep_unneeded_types=false --diag_warning=225 --quiet -O3

#-----------------------------------------------------------------------------
# Group CLASSIC_MATH_LIBRARY_INTEGER
#-----------------------------------------------------------------------------

CLASSIC_MATH_LIBRARY_INTEGER_C_SOURCE = \
	abs.c \
	labs.c \
	llabs.c \
	imaxabs.c \
	imaxdiv.c

C_SOURCE += $(CLASSIC_MATH_LIBRARY_INTEGER_C_SOURCE)


#-----------------------------------------------------------------------------
# Group GENERIC_EDG
#-----------------------------------------------------------------------------
GENERIC_EDG_CPP_FLAGS += --building_runtime -DCHECKING=0

GENERIC_EDG_CPP_SOURCE = \
	dtor_list.c \
	error.c \
	guard.c \
	memzero.c \
	newhandler.c \
	pure_virt.c \
	rtti.c \
	typeinfo.c \
	vars.c \
	vec_cctor.c \
	vec_newdel.c \
	vla_alloc.c

#-----------------------------------------------------------------------------
# Group LIBCXX_EXT_INCLUDES
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group EDG_C99_COMPLEX_HELPER
#-----------------------------------------------------------------------------
EDG_C99_COMPLEX_HELPER_CPP_FLAGS += --building_runtime -DCHECKING=0

EDG_C99_COMPLEX_HELPER_CPP_SOURCE = \
	c99_complex.c

#-----------------------------------------------------------------------------
# Group VECTOR_TYPES
#-----------------------------------------------------------------------------
C_FLAGS += --vectypes

VECTOR_TYPES_C_SOURCE = \
	c6x_veclib.c

C_SOURCE += $(VECTOR_TYPES_C_SOURCE)


#-----------------------------------------------------------------------------
# Group CLASSIC_CPP_MATH_OVERLOADS
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group LIBCXXABI_CPP_LIB
#-----------------------------------------------------------------------------
LIBCXXABI_CPP_LIB_FLAGS += --preinclude __config_site

LIBCXXABI_CPP_LIB_CPP_SOURCE = \
	stdlib_exception.cpp \
	stdlib_typeinfo.cpp

#-----------------------------------------------------------------------------
# Group OPENBSD_C99_COMPLEX
#-----------------------------------------------------------------------------
OPENBSD_C99_COMPLEX_C_FLAGS += --c99

OPENBSD_C99_COMPLEX_C_SOURCE = \
	s_clog.c \
	s_clogf.c \
	s_clogl.c \
	s_cpow.c \
	s_cpowf.c \
	s_cpowl.c

#-----------------------------------------------------------------------------
# Group LIBCXX_BUILD_SUPPORT_RUNTIME_HEADERS
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT
#-----------------------------------------------------------------------------
FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT_C_FLAGS += --c99

FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT_C_SOURCE = \
	s_cbrtf.c \
	s_erff.c \
	s_expm1f.c \
	s_fdim.c \
	e_lgammaf.c \
	e_lgammaf_r.c \
	s_logbf.c \
	s_ilogbf.c \
	s_scalbln.c \
	s_tgammaf.c \
	s_rintf.c \
	e_remainderf.c \
	s_remquof.c \
	s_nextafterf.c \
	s_nexttowardf.c \
	s_fmaf.c \
	s_nearbyint.c \
	s_llrint.c \
	s_llrintf.c \
	s_llrintl.c \
	s_lrint.c \
	s_lrintf.c \
	s_lrintl.c \
	s_llround.c \
	s_llroundf.c \
	s_llroundl.c \
	s_lround.c \
	s_lroundf.c \
	s_lroundl.c \
	k_cosf.c \
	k_sinf.c \
	k_tanf.c

#-----------------------------------------------------------------------------
# Group LIBCXX_BUILD_INCLUDE_HEADERS
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group C6000
#-----------------------------------------------------------------------------
ifneq ($(VENC),1)
C6000=1
endif


C6000_ASM_SOURCE = \
	divi.asm \
	divu.asm \
	memcpy64.asm \
	remi.asm \
	remu.asm \
	strasg.asm

ASM_SOURCE += $(C6000_ASM_SOURCE)


#-----------------------------------------------------------------------------
# Group CLASSIC_ERRNO
#-----------------------------------------------------------------------------

CLASSIC_ERRNO_C_SOURCE = \
	errno.c

C_SOURCE += $(CLASSIC_ERRNO_C_SOURCE)


#-----------------------------------------------------------------------------
# Group FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT
#-----------------------------------------------------------------------------
FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT_C_FLAGS += --c99

FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT_C_SOURCE = \
	b_exp.c \
	b_log.c \
	s_cbrt.c \
	s_erf.c \
	s_expm1.c \
	e_lgamma.c \
	e_lgamma_r.c \
	s_logb.c \
	s_ilogb.c \
	b_tgamma.c \
	s_rint.c \
	e_remainder.c \
	s_remquo.c \
	s_nextafter.c \
	s_fma.c \
	k_cos.c \
	k_sin.c \
	k_tan.c

#-----------------------------------------------------------------------------
# Group EABI_TDEH
#-----------------------------------------------------------------------------
ifeq ($(C6XABI),1)
ifeq ($(EXCEPTIONS),1)
EABI_TDEH=1
endif
endif

ifeq ($(EABI_TDEH),1)
CPP_FLAGS += --extern_c_can_throw
UNIVERSAL_FLAGS += -D__TI_TABLE_DRIVEN_EXCEPTIONS
EABI_TDEH_CPP_FLAGS += --building_runtime -DCHECKING=0

EABI_TDEH_CPP_SOURCE = \
	tdeh_unwinder.cpp \
	tdeh_cpp_abi.cpp \
	tdeh_pr_common.cpp \
	tdeh_init.cpp
endif


#-----------------------------------------------------------------------------
# Group XLOCALE_HEADERS
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group NOT_VENC_ASM
#-----------------------------------------------------------------------------
ifneq ($(VENC),1)
NOT_VENC_ASM=1
endif


NOT_VENC_ASM_ASM_SOURCE = \
	push.asm \
	call_stub.asm \
	setjmp.asm

ASM_SOURCE += $(NOT_VENC_ASM_ASM_SOURCE)


#-----------------------------------------------------------------------------
# Group FREEBSD_SYS_HEADERS
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group LIBCXX_TI_INCLUDE_HEADERS
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group MT
#-----------------------------------------------------------------------------
ifeq ($(MT),1)
UNIVERSAL_FLAGS += --multithread --use_libc_tls -D__TI_SHARED_DATA_SYNCHRONIZATION -D__TI_RECURSIVE_RESOURCE_MUTEXES
endif


#-----------------------------------------------------------------------------
# Group EABI
#-----------------------------------------------------------------------------
EABI_CPP_FLAGS += --building_runtime -DCHECKING=0

EABI_CPP_SOURCE = \
	decode.c

#-----------------------------------------------------------------------------
# Group FREEBSD_C99_COMPLEX_COMMON
#-----------------------------------------------------------------------------


EABI_CPP_OBJS_1 = $(patsubst %.c,$(OBJ)/%.c.obj,$(EABI_CPP_SOURCE))
$(EABI_CPP_OBJS_1): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(EABI_FLAGS) $(CPP_FLAGS) $(EABI_CPP_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

LIBCXX_CPP_LIB_CPP_OBJS_2 = $(patsubst %.cpp,$(OBJ)/%.cpp.obj,$(LIBCXX_CPP_LIB_CPP_SOURCE))
$(LIBCXX_CPP_LIB_CPP_OBJS_2): $(OBJ)/%.cpp.obj: %.cpp
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(LIBCXX_CPP_LIB_FLAGS) $(CPP_FLAGS) $(LIBCXX_CPP_LIB_CPP_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

EABI_TDEH_CPP_OBJS_3 = $(patsubst %.cpp,$(OBJ)/%.cpp.obj,$(EABI_TDEH_CPP_SOURCE))
$(EABI_TDEH_CPP_OBJS_3): $(OBJ)/%.cpp.obj: %.cpp
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(EABI_TDEH_FLAGS) $(CPP_FLAGS) $(EABI_TDEH_CPP_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT_C_OBJS_4 = $(patsubst %.c,$(OBJ)/%.c.obj,$(FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT_C_SOURCE))
$(FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT_C_OBJS_4): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT_FLAGS) $(C_FLAGS) $(FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT_C_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT_C_OBJS_5 = $(patsubst %.c,$(OBJ)/%.c.obj,$(FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT_C_SOURCE))
$(FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT_C_OBJS_5): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT_FLAGS) $(C_FLAGS) $(FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT_C_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

OPENBSD_C99_COMPLEX_C_OBJS_6 = $(patsubst %.c,$(OBJ)/%.c.obj,$(OPENBSD_C99_COMPLEX_C_SOURCE))
$(OPENBSD_C99_COMPLEX_C_OBJS_6): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(OPENBSD_C99_COMPLEX_FLAGS) $(C_FLAGS) $(OPENBSD_C99_COMPLEX_C_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

LIBCXXABI_CPP_LIB_CPP_OBJS_7 = $(patsubst %.cpp,$(OBJ)/%.cpp.obj,$(LIBCXXABI_CPP_LIB_CPP_SOURCE))
$(LIBCXXABI_CPP_LIB_CPP_OBJS_7): $(OBJ)/%.cpp.obj: %.cpp
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(LIBCXXABI_CPP_LIB_FLAGS) $(CPP_FLAGS) $(LIBCXXABI_CPP_LIB_CPP_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

EDG_C99_COMPLEX_HELPER_CPP_OBJS_8 = $(patsubst %.c,$(OBJ)/%.c.obj,$(EDG_C99_COMPLEX_HELPER_CPP_SOURCE))
$(EDG_C99_COMPLEX_HELPER_CPP_OBJS_8): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(EDG_C99_COMPLEX_HELPER_FLAGS) $(CPP_FLAGS) $(EDG_C99_COMPLEX_HELPER_CPP_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

GENERIC_EDG_CPP_OBJS_9 = $(patsubst %.c,$(OBJ)/%.c.obj,$(GENERIC_EDG_CPP_SOURCE))
$(GENERIC_EDG_CPP_OBJS_9): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(GENERIC_EDG_FLAGS) $(CPP_FLAGS) $(GENERIC_EDG_CPP_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

FULL_WCHAR_C_OBJS_10 = $(patsubst %.c,$(OBJ)/%.c.obj,$(FULL_WCHAR_C_SOURCE))
$(FULL_WCHAR_C_OBJS_10): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(FULL_WCHAR_FLAGS) $(C_FLAGS) $(FULL_WCHAR_C_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

EDG_CPP_SUPPLEMENTAL_CPP_OBJS_11 = $(patsubst %.c,$(OBJ)/%.c.obj,$(EDG_CPP_SUPPLEMENTAL_CPP_SOURCE))
$(EDG_CPP_SUPPLEMENTAL_CPP_OBJS_11): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(EDG_CPP_SUPPLEMENTAL_FLAGS) $(CPP_FLAGS) $(EDG_CPP_SUPPLEMENTAL_CPP_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

FREEBSD_C99_COMPLEX_64_BIT_C_OBJS_12 = $(patsubst %.c,$(OBJ)/%.c.obj,$(FREEBSD_C99_COMPLEX_64_BIT_C_SOURCE))
$(FREEBSD_C99_COMPLEX_64_BIT_C_OBJS_12): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(FREEBSD_C99_COMPLEX_64_BIT_FLAGS) $(C_FLAGS) $(FREEBSD_C99_COMPLEX_64_BIT_C_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

FREEBSD_C99_COMPLEX_32_BIT_C_OBJS_13 = $(patsubst %.c,$(OBJ)/%.c.obj,$(FREEBSD_C99_COMPLEX_32_BIT_C_SOURCE))
$(FREEBSD_C99_COMPLEX_32_BIT_C_OBJS_13): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(FREEBSD_C99_COMPLEX_32_BIT_FLAGS) $(C_FLAGS) $(FREEBSD_C99_COMPLEX_32_BIT_C_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

GENERIC_C_SIZE_OPTIMIZED_C_OBJS_14 = $(patsubst %.c,$(OBJ)/%.c.obj,$(GENERIC_C_SIZE_OPTIMIZED_C_SOURCE))
$(GENERIC_C_SIZE_OPTIMIZED_C_OBJS_14): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(GENERIC_C_SIZE_OPTIMIZED_FLAGS) $(C_FLAGS) $(GENERIC_C_SIZE_OPTIMIZED_C_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

LIBCXX_CPP_NO_LTO_CPP_OBJS_15 = $(patsubst %.cpp,$(OBJ)/%.cpp.obj,$(LIBCXX_CPP_NO_LTO_CPP_SOURCE))
$(LIBCXX_CPP_NO_LTO_CPP_OBJS_15): $(OBJ)/%.cpp.obj: %.cpp
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(LIBCXX_CPP_NO_LTO_FLAGS) $(CPP_FLAGS) $(LIBCXX_CPP_NO_LTO_CPP_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

XLOCALE_C_OBJS_16 = $(patsubst %.c,$(OBJ)/%.c.obj,$(XLOCALE_C_SOURCE))
$(XLOCALE_C_OBJS_16): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(XLOCALE_FLAGS) $(C_FLAGS) $(XLOCALE_C_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

ASM_OBJS_17 = $(patsubst %.asm,$(OBJ)/%.asm.obj,$(ASM_SOURCE))
$(ASM_OBJS_17): $(OBJ)/%.asm.obj: %.asm
	$(CC) $< $(EXTRA_FLAGS) $(STANDARD_FLAGS) $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(UNIVERSAL_FLAGS) $(ASM_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ)
	$(CC) $< $(EXTRA_FLAGS) $(STANDARD_FLAGS) $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(UNIVERSAL_FLAGS) $(ASM_FLAGS) -I$(INC) -fr $(OBJ) -fs $(OBJ) -ft $(OBJ) --asm_dependency=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

CPP_OBJS_18 = $(patsubst %.cpp,$(OBJ)/%.cpp.obj,$(CPP_SOURCE))
$(CPP_OBJS_18): $(OBJ)/%.cpp.obj: %.cpp
	$(CC) $< $(EXTRA_FLAGS) $(STANDARD_FLAGS) $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(UNIVERSAL_FLAGS) $(CPP_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

C_OBJS_19 = $(patsubst %.c,$(OBJ)/%.c.obj,$(C_SOURCE))
$(C_OBJS_19): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(STANDARD_FLAGS) $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(UNIVERSAL_FLAGS) $(C_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ) -ppa -ppd=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

LINASM_OBJS_20 = $(patsubst %.sa,$(OBJ)/%.sa.obj,$(LINASM_SOURCE))
$(LINASM_OBJS_20): $(OBJ)/%.sa.obj: %.sa
	$(CC) $< $(EXTRA_FLAGS) $(STANDARD_FLAGS) $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(UNIVERSAL_FLAGS) $(C_FLAGS) -I$(INC) -fe $@ -fs $(OBJ) -ft $(OBJ)
	$(CC) $< $(EXTRA_FLAGS) $(STANDARD_FLAGS) $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(UNIVERSAL_FLAGS) $(C_FLAGS) -I$(INC) -fr $(OBJ) -fs $(OBJ) -ft $(OBJ) --asm_dependency=$(OBJ)/$(basename $(@F)).pp
	@$(CP_CMD) $(OBJ)/$(basename $(@F)).pp $(OBJ)/$(basename $(@F)).P
	@$(SED_CMD) -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OBJ)/$(basename $(@F)).pp >> $(OBJ)/$(basename $(@F)).P
	@$(RM_CMD) -f $(OBJ)/$(basename $(@F)).pp

ALL_OBJS = $(EABI_CPP_OBJS_1) $(LIBCXX_CPP_LIB_CPP_OBJS_2) $(EABI_TDEH_CPP_OBJS_3) $(FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT_C_OBJS_4) $(FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT_C_OBJS_5) $(OPENBSD_C99_COMPLEX_C_OBJS_6) $(LIBCXXABI_CPP_LIB_CPP_OBJS_7) $(EDG_C99_COMPLEX_HELPER_CPP_OBJS_8) $(GENERIC_EDG_CPP_OBJS_9) $(FULL_WCHAR_C_OBJS_10) $(EDG_CPP_SUPPLEMENTAL_CPP_OBJS_11) $(FREEBSD_C99_COMPLEX_64_BIT_C_OBJS_12) $(FREEBSD_C99_COMPLEX_32_BIT_C_OBJS_13) $(GENERIC_C_SIZE_OPTIMIZED_C_OBJS_14) $(LIBCXX_CPP_NO_LTO_CPP_OBJS_15) $(XLOCALE_C_OBJS_16) $(ASM_OBJS_17) $(CPP_OBJS_18) $(C_OBJS_19) $(LINASM_OBJS_20)
RELATIVE_EABI_CPP_OBJS_1 := $(foreach obj,$(EABI_CPP_OBJS_1),$(subst $(OBJ)/,,$(obj)))
RELATIVE_LIBCXX_CPP_LIB_CPP_OBJS_2 := $(foreach obj,$(LIBCXX_CPP_LIB_CPP_OBJS_2),$(subst $(OBJ)/,,$(obj)))
RELATIVE_EABI_TDEH_CPP_OBJS_3 := $(foreach obj,$(EABI_TDEH_CPP_OBJS_3),$(subst $(OBJ)/,,$(obj)))
RELATIVE_FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT_C_OBJS_4 := $(foreach obj,$(FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT_C_OBJS_4),$(subst $(OBJ)/,,$(obj)))
RELATIVE_FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT_C_OBJS_5 := $(foreach obj,$(FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT_C_OBJS_5),$(subst $(OBJ)/,,$(obj)))
RELATIVE_OPENBSD_C99_COMPLEX_C_OBJS_6 := $(foreach obj,$(OPENBSD_C99_COMPLEX_C_OBJS_6),$(subst $(OBJ)/,,$(obj)))
RELATIVE_LIBCXXABI_CPP_LIB_CPP_OBJS_7 := $(foreach obj,$(LIBCXXABI_CPP_LIB_CPP_OBJS_7),$(subst $(OBJ)/,,$(obj)))
RELATIVE_EDG_C99_COMPLEX_HELPER_CPP_OBJS_8 := $(foreach obj,$(EDG_C99_COMPLEX_HELPER_CPP_OBJS_8),$(subst $(OBJ)/,,$(obj)))
RELATIVE_GENERIC_EDG_CPP_OBJS_9 := $(foreach obj,$(GENERIC_EDG_CPP_OBJS_9),$(subst $(OBJ)/,,$(obj)))
RELATIVE_FULL_WCHAR_C_OBJS_10 := $(foreach obj,$(FULL_WCHAR_C_OBJS_10),$(subst $(OBJ)/,,$(obj)))
RELATIVE_EDG_CPP_SUPPLEMENTAL_CPP_OBJS_11 := $(foreach obj,$(EDG_CPP_SUPPLEMENTAL_CPP_OBJS_11),$(subst $(OBJ)/,,$(obj)))
RELATIVE_FREEBSD_C99_COMPLEX_64_BIT_C_OBJS_12 := $(foreach obj,$(FREEBSD_C99_COMPLEX_64_BIT_C_OBJS_12),$(subst $(OBJ)/,,$(obj)))
RELATIVE_FREEBSD_C99_COMPLEX_32_BIT_C_OBJS_13 := $(foreach obj,$(FREEBSD_C99_COMPLEX_32_BIT_C_OBJS_13),$(subst $(OBJ)/,,$(obj)))
RELATIVE_GENERIC_C_SIZE_OPTIMIZED_C_OBJS_14 := $(foreach obj,$(GENERIC_C_SIZE_OPTIMIZED_C_OBJS_14),$(subst $(OBJ)/,,$(obj)))
RELATIVE_LIBCXX_CPP_NO_LTO_CPP_OBJS_15 := $(foreach obj,$(LIBCXX_CPP_NO_LTO_CPP_OBJS_15),$(subst $(OBJ)/,,$(obj)))
RELATIVE_XLOCALE_C_OBJS_16 := $(foreach obj,$(XLOCALE_C_OBJS_16),$(subst $(OBJ)/,,$(obj)))
RELATIVE_ASM_OBJS_17 := $(foreach obj,$(ASM_OBJS_17),$(subst $(OBJ)/,,$(obj)))
RELATIVE_CPP_OBJS_18 := $(foreach obj,$(CPP_OBJS_18),$(subst $(OBJ)/,,$(obj)))
RELATIVE_C_OBJS_19 := $(foreach obj,$(C_OBJS_19),$(subst $(OBJ)/,,$(obj)))
RELATIVE_LINASM_OBJS_20 := $(foreach obj,$(LINASM_OBJS_20),$(subst $(OBJ)/,,$(obj)))

-include $(ALL_OBJS:.obj=.P)

library: $(ALL_OBJS)
	@echo "Creating library $(LIB)"
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_EABI_CPP_OBJS_1)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_LIBCXX_CPP_LIB_CPP_OBJS_2)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_EABI_TDEH_CPP_OBJS_3)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT_C_OBJS_4)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT_C_OBJS_5)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_OPENBSD_C99_COMPLEX_C_OBJS_6)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_LIBCXXABI_CPP_LIB_CPP_OBJS_7)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_EDG_C99_COMPLEX_HELPER_CPP_OBJS_8)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_GENERIC_EDG_CPP_OBJS_9)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_FULL_WCHAR_C_OBJS_10)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_EDG_CPP_SUPPLEMENTAL_CPP_OBJS_11)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_FREEBSD_C99_COMPLEX_64_BIT_C_OBJS_12)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_FREEBSD_C99_COMPLEX_32_BIT_C_OBJS_13)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_GENERIC_C_SIZE_OPTIMIZED_C_OBJS_14)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_LIBCXX_CPP_NO_LTO_CPP_OBJS_15)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_XLOCALE_C_OBJS_16)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_ASM_OBJS_17)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_CPP_OBJS_18)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_C_OBJS_19)
	$(CD) $(OBJ); $(AR) -qa $(LIB) $(RELATIVE_LINASM_OBJS_20)

info:
	@echo EABI_CPP_OBJS_1 $(EABI_CPP_OBJS_1)
	@echo LIBCXX_CPP_LIB_CPP_OBJS_2 $(LIBCXX_CPP_LIB_CPP_OBJS_2)
	@echo EABI_TDEH_CPP_OBJS_3 $(EABI_TDEH_CPP_OBJS_3)
	@echo FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT_C_OBJS_4 $(FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT_C_OBJS_4)
	@echo FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT_C_OBJS_5 $(FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT_C_OBJS_5)
	@echo OPENBSD_C99_COMPLEX_C_OBJS_6 $(OPENBSD_C99_COMPLEX_C_OBJS_6)
	@echo LIBCXXABI_CPP_LIB_CPP_OBJS_7 $(LIBCXXABI_CPP_LIB_CPP_OBJS_7)
	@echo EDG_C99_COMPLEX_HELPER_CPP_OBJS_8 $(EDG_C99_COMPLEX_HELPER_CPP_OBJS_8)
	@echo GENERIC_EDG_CPP_OBJS_9 $(GENERIC_EDG_CPP_OBJS_9)
	@echo FULL_WCHAR_C_OBJS_10 $(FULL_WCHAR_C_OBJS_10)
	@echo EDG_CPP_SUPPLEMENTAL_CPP_OBJS_11 $(EDG_CPP_SUPPLEMENTAL_CPP_OBJS_11)
	@echo FREEBSD_C99_COMPLEX_64_BIT_C_OBJS_12 $(FREEBSD_C99_COMPLEX_64_BIT_C_OBJS_12)
	@echo FREEBSD_C99_COMPLEX_32_BIT_C_OBJS_13 $(FREEBSD_C99_COMPLEX_32_BIT_C_OBJS_13)
	@echo GENERIC_C_SIZE_OPTIMIZED_C_OBJS_14 $(GENERIC_C_SIZE_OPTIMIZED_C_OBJS_14)
	@echo LIBCXX_CPP_NO_LTO_CPP_OBJS_15 $(LIBCXX_CPP_NO_LTO_CPP_OBJS_15)
	@echo XLOCALE_C_OBJS_16 $(XLOCALE_C_OBJS_16)
	@echo ASM_OBJS_17 $(ASM_OBJS_17)
	@echo CPP_OBJS_18 $(CPP_OBJS_18)
	@echo C_OBJS_19 $(C_OBJS_19)
	@echo LINASM_OBJS_20 $(LINASM_OBJS_20)
	@echo ASM_FLAGS $(ASM_FLAGS)
	@echo CPP_FLAGS $(CPP_FLAGS)
	@echo C_FLAGS $(C_FLAGS)
	@echo EABI_CPP_FLAGS $(EABI_CPP_FLAGS)
	@echo EABI_FLAGS $(EABI_FLAGS)
	@echo EABI_TDEH_CPP_FLAGS $(EABI_TDEH_CPP_FLAGS)
	@echo EABI_TDEH_FLAGS $(EABI_TDEH_FLAGS)
	@echo EDG_C99_COMPLEX_HELPER_CPP_FLAGS $(EDG_C99_COMPLEX_HELPER_CPP_FLAGS)
	@echo EDG_C99_COMPLEX_HELPER_FLAGS $(EDG_C99_COMPLEX_HELPER_FLAGS)
	@echo EDG_CPP_SUPPLEMENTAL_CPP_FLAGS $(EDG_CPP_SUPPLEMENTAL_CPP_FLAGS)
	@echo EDG_CPP_SUPPLEMENTAL_FLAGS $(EDG_CPP_SUPPLEMENTAL_FLAGS)
	@echo EXTRA_FLAGS $(EXTRA_FLAGS)
	@echo FREEBSD_C99_COMPLEX_32_BIT_C_FLAGS $(FREEBSD_C99_COMPLEX_32_BIT_C_FLAGS)
	@echo FREEBSD_C99_COMPLEX_32_BIT_FLAGS $(FREEBSD_C99_COMPLEX_32_BIT_FLAGS)
	@echo FREEBSD_C99_COMPLEX_64_BIT_C_FLAGS $(FREEBSD_C99_COMPLEX_64_BIT_C_FLAGS)
	@echo FREEBSD_C99_COMPLEX_64_BIT_FLAGS $(FREEBSD_C99_COMPLEX_64_BIT_FLAGS)
	@echo FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT_C_FLAGS $(FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT_C_FLAGS)
	@echo FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT_FLAGS $(FREEBSD_MATH_GENERIC_SUPPLEMENT_32_BIT_FLAGS)
	@echo FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT_C_FLAGS $(FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT_C_FLAGS)
	@echo FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT_FLAGS $(FREEBSD_MATH_GENERIC_SUPPLEMENT_64_BIT_FLAGS)
	@echo FULL_WCHAR_C_FLAGS $(FULL_WCHAR_C_FLAGS)
	@echo FULL_WCHAR_FLAGS $(FULL_WCHAR_FLAGS)
	@echo GENERIC_C_SIZE_OPTIMIZED_C_FLAGS $(GENERIC_C_SIZE_OPTIMIZED_C_FLAGS)
	@echo GENERIC_C_SIZE_OPTIMIZED_FLAGS $(GENERIC_C_SIZE_OPTIMIZED_FLAGS)
	@echo GENERIC_EDG_CPP_FLAGS $(GENERIC_EDG_CPP_FLAGS)
	@echo GENERIC_EDG_FLAGS $(GENERIC_EDG_FLAGS)
	@echo LIBCXXABI_CPP_LIB_CPP_FLAGS $(LIBCXXABI_CPP_LIB_CPP_FLAGS)
	@echo LIBCXXABI_CPP_LIB_FLAGS $(LIBCXXABI_CPP_LIB_FLAGS)
	@echo LIBCXX_CPP_LIB_CPP_FLAGS $(LIBCXX_CPP_LIB_CPP_FLAGS)
	@echo LIBCXX_CPP_LIB_FLAGS $(LIBCXX_CPP_LIB_FLAGS)
	@echo LIBCXX_CPP_NO_LTO_CPP_FLAGS $(LIBCXX_CPP_NO_LTO_CPP_FLAGS)
	@echo LIBCXX_CPP_NO_LTO_FLAGS $(LIBCXX_CPP_NO_LTO_FLAGS)
	@echo OPENBSD_C99_COMPLEX_C_FLAGS $(OPENBSD_C99_COMPLEX_C_FLAGS)
	@echo OPENBSD_C99_COMPLEX_FLAGS $(OPENBSD_C99_COMPLEX_FLAGS)
	@echo STANDARD_FLAGS $(STANDARD_FLAGS)
	@echo UNIVERSAL_FLAGS $(UNIVERSAL_FLAGS)
	@echo XLOCALE_C_FLAGS $(XLOCALE_C_FLAGS)
	@echo XLOCALE_FLAGS $(XLOCALE_FLAGS)

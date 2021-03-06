#
# Makefile for xboot
# Create by: Jianjun Jiang <8192542@qq.com>
#

#
# You must pass CROSS_COMPILE and PLATFORM variable.
#
CROSS_COMPILE	?=
PLATFORM		?=

#
# Get platform information about ARCH and MACH from PLATFORM variable.
#
ifeq ($(words $(subst -, , $(PLATFORM))), 2)
ARCH		:= $(word 1, $(subst -, , $(PLATFORM)))
MACH		:= mach-$(word 2, $(subst -, , $(PLATFORM)))
else
ARCH		:= x64
MACH		:= mach-sandbox
endif

#
# System environment variable.
#
ifneq (,$(findstring Linux, $(shell uname -s)))
HOSTOS		:= linux
else
HOSTOS		:= windows
endif

#
# Load default variables.
#
ASFLAGS		:= -g -ggdb -Wall -O0
CFLAGS		:= -g -ggdb -Wall -O0
CXXFLAGS	:= -g -ggdb -Wall -O0
LDFLAGS		:= -T arch/$(ARCH)/$(MACH)/xboot.ld -nostdlib
MCFLAGS		:=

LIBDIRS		:=
LIBS 		:=
INCDIRS		:=
SRCDIRS		:=

#
# Override default variables.
#
sinclude arch/$(ARCH)/$(MACH)/xboot.mk

#
# Modify default variables.
#
ifeq ($(strip $(ARCH)), arm32)
DEFINES		+=	-D__ARM32__
endif
ifeq ($(strip $(ARCH)), arm64)
DEFINES		+=	-D__ARM64__
endif
ifeq ($(strip $(ARCH)), x64)
DEFINES		+=	-D__X64__
endif

ASFLAGS		+= 	-ffreestanding -std=gnu99 $(DEFINES)
CFLAGS		+=	-ffreestanding -std=gnu99 $(DEFINES)
CXXFLAGS	+=	-ffreestanding -std=gnu99 $(DEFINES)

#
# Add necessary directory for INCDIRS and SRCDIRS.
#
INCDIRS		+=	include										\
				arch/$(ARCH)/include						\
				arch/$(ARCH)/$(MACH)/include

SRCDIRS		+=	arch/$(ARCH)/lib/cpu						\
				arch/$(ARCH)/lib							\
				arch/$(ARCH)/$(MACH)						\
				arch/$(ARCH)/$(MACH)/driver					\
				lib/libc									\
				lib/libc/charset							\
				lib/libc/crypto								\
				lib/libc/ctype								\
				lib/libc/environ							\
				lib/libc/errno								\
				lib/libc/exit								\
				lib/libc/filter								\
				lib/libc/locale								\
				lib/libc/malloc								\
				lib/libc/path								\
				lib/libc/stdio								\
				lib/libc/stdlib								\
				lib/libc/string								\
				lib/libc/time								\
				lib/libm/$(ARCH)							\
				lib/libm									\
				lib/libx									\
				init										\
				kernel										\
				kernel/core									\
				kernel/shell								\
				kernel/command								\
				kernel/time									\
				kernel/fs									\
				kernel/fs/vfs								\
				kernel/fs/ramfs								\
				kernel/fs/sysfs								\
				kernel/fs/arfs								\
				kernel/fs/tarfs								\
				kernel/fs/cpiofs							\
				kernel/fs/fatfs								\
				kernel/xfs									\
				driver/adc									\
				driver/audio								\
				driver/battery								\
				driver/block								\
				driver/block/partition						\
				driver/block/romdisk						\
				driver/buzzer								\
				driver/clk									\
				driver/clockevent							\
				driver/clocksource							\
				driver/console								\
				driver/dac									\
				driver/dma									\
				driver/framebuffer							\
				driver/gmeter								\
				driver/gpio									\
				driver/hygrometer							\
				driver/i2c									\
				driver/input								\
				driver/input/rc								\
				driver/interrupt							\
				driver/laserscan							\
				driver/led									\
				driver/light								\
				driver/motor								\
				driver/nvmem								\
				driver/pwm									\
				driver/regulator							\
				driver/reset								\
				driver/rng									\
				driver/rtc									\
				driver/sd									\
				driver/servo								\
				driver/spi									\
				driver/stepper								\
				driver/thermometer							\
				driver/uart									\
				driver/vibrator								\
				driver/watchdog								\
				framework									\
				framework/base64							\
				framework/display							\
				framework/event								\
				framework/hardware							\
				framework/lang								\
				framework/stopwatch

#
# Add external library
#
INCDIRS		+= 	external/json-parser-1.1.0
SRCDIRS		+=	external/json-parser-1.1.0

INCDIRS		+= 	external/libfdt-1.4.2
SRCDIRS		+=	external/libfdt-1.4.2

INCDIRS		+= 	external/zlib-1.2.11
SRCDIRS		+=	external/zlib-1.2.11

INCDIRS		+= 	external/libpng-1.6.32
SRCDIRS		+=	external/libpng-1.6.32

INCDIRS		+= 	external/lua-5.3.4
SRCDIRS		+=	external/lua-5.3.4

INCDIRS		+= 	external/lua-cjson-2.1.0
SRCDIRS		+=	external/lua-cjson-2.1.0

INCDIRS		+= 	external/pixman-0.34.0 \
				external/pixman-0.34.0/$(ARCH)
SRCDIRS		+=	external/pixman-0.34.0 \
				external/pixman-0.34.0/$(ARCH)

INCDIRS		+= 	external/cairo-1.14.10
SRCDIRS		+=	external/cairo-1.14.10

INCDIRS		+= 	external/freetype-2.4.11/include \
				external/freetype-2.4.11/src/base \
				external/freetype-2.4.11/src/raster	\
				external/freetype-2.4.11/src/smooth	\
				external/freetype-2.4.11/src/cff \
				external/freetype-2.4.11/src/cid \
				external/freetype-2.4.11/src/pfr \
				external/freetype-2.4.11/src/sfnt \
				external/freetype-2.4.11/src/truetype \
				external/freetype-2.4.11/src/type1 \
				external/freetype-2.4.11/src/type42 \
				external/freetype-2.4.11/src/winfonts \
				external/freetype-2.4.11/src/autofit \
				external/freetype-2.4.11/src/cache \
				external/freetype-2.4.11/src/gxvalid \
				external/freetype-2.4.11/src/otvalid \
				external/freetype-2.4.11/src/psaux \
				external/freetype-2.4.11/src/pshinter \
				external/freetype-2.4.11/src/psnames
SRCDIRS		+=	external/freetype-2.4.11/src/base \
				external/freetype-2.4.11/src/raster \
				external/freetype-2.4.11/src/smooth \
				external/freetype-2.4.11/src/cff \
				external/freetype-2.4.11/src/cid \
				external/freetype-2.4.11/src/pfr \
				external/freetype-2.4.11/src/sfnt \
				external/freetype-2.4.11/src/truetype \
				external/freetype-2.4.11/src/type1 \
				external/freetype-2.4.11/src/type42 \
				external/freetype-2.4.11/src/winfonts \
				external/freetype-2.4.11/src/autofit \
				external/freetype-2.4.11/src/cache \
				external/freetype-2.4.11/src/gxvalid \
				external/freetype-2.4.11/src/otvalid \
				external/freetype-2.4.11/src/psaux \
				external/freetype-2.4.11/src/pshinter \
				external/freetype-2.4.11/src/psnames

INCDIRS		+=	external/chipmunk-7.0.2/include
SRCDIRS		+=	external/chipmunk-7.0.2/src

#
# You shouldn't need to change anything below this point.
#
AS			:=	$(CROSS_COMPILE)gcc -x assembler-with-cpp
CC			:=	$(CROSS_COMPILE)gcc
CXX			:=	$(CROSS_COMPILE)g++
LD			:=	$(CROSS_COMPILE)ld
AR			:=	$(CROSS_COMPILE)ar
OC			:=	$(CROSS_COMPILE)objcopy
OD			:=	$(CROSS_COMPILE)objdump
MKDIR		:=	mkdir -p
CP			:=	cp -af
RM			:=	rm -fr
CD			:=	cd
FIND		:=	find
CPIO		:=	cpio -o -H newc --quiet

#
# Xboot variables
#
X_ASFLAGS	:=	$(MCFLAGS) $(ASFLAGS)
X_CFLAGS	:=	$(MCFLAGS) $(CFLAGS)
X_CXXFLAGS	:=	$(MCFLAGS) $(CXXFLAGS)
X_LDFLAGS	:=	$(LDFLAGS)
X_LIBS		:=	$(LIBS) -lgcc

X_OUT		:=	../output
X_NAME		:=	$(patsubst %, $(X_OUT)/%, xboot)
X_INCDIRS	:=	$(patsubst %, -I %, $(INCDIRS))
X_LIBDIRS	:=	$(patsubst %, -L %, $(LIBDIRS))
X_SRCDIRS	:=	$(patsubst %, %, $(SRCDIRS))
X_OBJDIRS	:=	$(patsubst %, .obj/%, $(X_SRCDIRS))

X_SFILES	:=	$(foreach dir, $(X_SRCDIRS), $(wildcard $(dir)/*.S))
X_CFILES	:=	$(foreach dir, $(X_SRCDIRS), $(wildcard $(dir)/*.c))
X_CPPFILES	:=	$(foreach dir, $(X_SRCDIRS), $(wildcard $(dir)/*.cpp))

X_SDEPS		:=	$(patsubst %, .obj/%, $(X_SFILES:.S=.o.d))
X_CDEPS		:=	$(patsubst %, .obj/%, $(X_CFILES:.c=.o.d))
X_CPPDEPS	:=	$(patsubst %, .obj/%, $(X_CPPFILES:.cpp=.o.d))
X_DEPS		:=	$(X_SDEPS) $(X_CDEPS) $(X_CPPDEPS)

X_SOBJS		:=	$(patsubst %, .obj/%, $(X_SFILES:.S=.o))
X_COBJS		:=	$(patsubst %, .obj/%, $(X_CFILES:.c=.o))
X_CPPOBJS	:=	$(patsubst %, .obj/%, $(X_CPPFILES:.cpp=.o)) 
X_OBJS		:=	$(X_SOBJS) $(X_COBJS) $(X_CPPOBJS)

#
# Module variables
#
M_ASFLAGS	:=	$(DEFINES) $(MODULE_ASFLAGS)
M_CFLAGS	:=	$(DEFINES) $(MODULE_CFLAGS)
M_CXXFLAGS	:=	$(DEFINES) $(MODULE_CXXFLAGS)
M_LDFLAGS	:=	$(MODULE_LDFLAGS) -shared -nostdlib -fPIC
M_LIBS		:=	$(MODULE_LIB_LINKS) -lgcc

M_NAME		:= 	$(patsubst %, $(M)/%, $(MODULE_NAME))
M_INCDIRS	:=	$(X_INCDIRS) $(patsubst %, -I $(M)/%, $(MODULE_INCLUDE_DIRS))
M_LIBDIRS	:=	$(X_LIBDIRS) $(patsubst %, -L $(M)/%, $(MODULE_LIB_SEARCH_DIRS))
M_SRCDIRS	:=	$(patsubst %, $(M)/%, $(MODULE_SOURCE_DIRS))
M_OBJDIRS	:=	$(patsubst %, %, $(M_SRCDIRS))

M_SFILES	:=	$(foreach dir, $(M_SRCDIRS), $(wildcard $(dir)/*.S))
M_CFILES	:=	$(foreach dir, $(M_SRCDIRS), $(wildcard $(dir)/*.c))
M_CPPFILES	:=	$(foreach dir, $(M_SRCDIRS), $(wildcard $(dir)/*.cpp))

M_SDEPS		:=	$(M_SFILES:.S=.o.d)
M_CDEPS		:=	$(M_CFILES:.c=.o.d)
M_CPPDEPS	:=	$(M_CPPFILES:.cpp=.o.d)
M_DEPS		:=	$(M_SDEPS) $(M_CDEPS) $(M_CPPDEPS)

M_SOBJS		:=	$(M_SFILES:.S=.o)
M_COBJS		:=	$(M_CFILES:.c=.o)
M_CPPOBJS	:=	$(M_CPPFILES:.cpp=.o)
M_OBJS		:=	$(M_SOBJS) $(M_COBJS) $(M_CPPOBJS)

VPATH		:=	$(X_OBJDIRS) $(M_OBJDIRS)
.PHONY:	all clean xbegin xend xclean module mclean

#
# Xboot rules
#
all : xbegin $(X_NAME) xend

$(X_NAME) : $(X_OBJS)
	@echo [LD] Linking $@
	@$(CC) $(X_LDFLAGS) $(X_LIBDIRS) -Wl,--cref,-Map=$@.map $^ -o $@ $(X_LIBS)
	@echo [OC] Objcopying $@.bin
	@$(OC) -v -O binary $@ $@.bin

$(X_SOBJS) : .obj/%.o : %.S
	@echo [AS] $<
	@$(AS) $(X_ASFLAGS) $(X_INCDIRS) -c $< -o $@
	@$(AS) $(X_ASFLAGS) -MD -MP -MF $@.d $(X_INCDIRS) -c $< -o $@

$(X_COBJS) : .obj/%.o : %.c
	@echo [CC] $<
	@$(CC) $(X_CFLAGS) $(X_INCDIRS) -c $< -o $@
	@$(CC) $(X_CFLAGS) -MD -MP -MF $@.d $(X_INCDIRS) -c $< -o $@

$(X_CPPOBJS) : .obj/%.o : %.cpp
	@echo [CXX] $<
	@$(CXX) $(X_CXXFLAGS) $(X_INCDIRS) -c $< -o $@	
	@$(CXX) $(X_CXXFLAGS) -MD -MP -MF $@.d $(X_INCDIRS) -c $< -o $@

clean: xclean
	@$(RM) $(X_OBJDIRS) $(X_OUT)
	@echo Clean xboot complete.

#
# Module rules
#
module : $(M_NAME)

$(M_NAME) : $(M_OBJS)
	@echo [M][AR] Archiving $@.a
	@$(AR) -rcs $@.a $(M_OBJS)
	@echo [M][LD] Linking $@.so
	@$(CC) $(M_LDFLAGS) $(M_LIBDIRS) -Wl,--cref,-Map=$@.map $^ -o $@.so $(M_LIBS)

$(M_SOBJS) : %.o : %.S
	@echo [M][AS] $<
	@$(AS) $(M_ASFLAGS) $(M_INCDIRS) -c $< -o $@
	@$(AS) $(M_ASFLAGS) -MD -MP -MF $@.d $(M_INCDIRS) -c $< -o $@

$(M_COBJS) : %.o : %.c
	@echo [M][CC] $<
	@$(CC) $(M_CFLAGS) $(M_INCDIRS) -c $< -o $@
	@$(CC) $(M_CFLAGS) -MD -MP -MF $@.d $(M_INCDIRS) -c $< -o $@

$(M_CPPOBJS) : %.o : %.cpp
	@echo [M][CXX] $<
	@$(CXX) $(M_CXXFLAGS) $(M_INCDIRS) -c $< -o $@	
	@$(CXX) $(M_CXXFLAGS) -MD -MP -MF $@.d $(M_INCDIRS) -c $< -o $@

mclean:
	@$(RM) $(M_DEPS) $(M_OBJS) $(M_NAME).a $(M_NAME).so $(M_NAME).map
	@echo Clean module complete.

#
# Include the dependency files, should be place the last of makefile
#
sinclude $(shell $(MKDIR) $(X_OBJDIRS) $(X_OUT)						\
			&& $(RM) .obj/romdisk									\
			&& $(RM) .obj/romdisk.cpio								\
			&& $(RM) .obj/init/version.o							\
			&& $(RM) .obj/driver/block/romdisk/data.o				\
			&& $(CP) romdisk .obj									\
			&& $(CP) arch/$(ARCH)/$(MACH)/romdisk .obj				\
			&& $(CD) .obj/romdisk									\
			&& $(FIND) . -not -name . | $(CPIO) > ../romdisk.cpio	\
			&& $(CD) ../..)											\
			$(X_DEPS) $(M_DEPS)

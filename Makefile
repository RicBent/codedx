#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

export CC	:=	clang
export CXX	:=	clang++
export AS	:=	clang
export OBJDUMP	:=	llvm-objdump
export LD	:= 	arm-none-eabi-ld


#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing header files
#---------------------------------------------------------------------------------
TARGET		:=	subsdk0
BUILD		:=	build
SOURCES		:=	source
INCLUDES	:=	include


#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH		:=	--target=armv7l-none-eabihf -mabi=aapcs-linux -mcpu=cortex-a57 -mfpu=crypto-neon-fp-armv8 -mfloat-abi=hard -fPIC
	
CFLAGS		:=	$(ARCH) $(INCLUDE) -nostdlib

CXXFLAGS	:=	$(CFLAGS) -fno-rtti -fno-exceptions -fpermissive

ASFLAGS		:=	$(ARCH)

LDFLAGS		:=	-pie -T $(LINKERSCRIPT) -T $(MAIN_SYMBOLS) -T $(SDK_SYMBOLS)


#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export LINKERSCRIPT	:=	$(CURDIR)/linker.ld

export MAIN_SYMBOLS	:=	$(CURDIR)/main.ld

export SDK_SYMBOLS	:=	$(CURDIR)/sdk.ld

export OUTPUT		:=	$(CURDIR)/$(TARGET)

export VPATH		:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir))

export DEPSDIR		:=	$(CURDIR)/$(BUILD)

CFILES			:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES			:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))


export OFILES		:=	$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

export INCLUDE		:=	$(foreach dir,$(INCLUDES),-iquote $(CURDIR)/$(dir)) \
					-I$(CURDIR)/$(BUILD)


.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile
 
#---------------------------------------------------------------------------------
clean:
	@rm -fr $(BUILD) $(TARGET).elf $(TARGET).sym

#---------------------------------------------------------------------------------
else
 
#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------

all: $(OUTPUT).sym

$(OUTPUT).sym : $(OUTPUT).elf
	$(OBJDUMP) -t $< > $@
	@echo Symbol table written to $(notdir $@)

#---------------------------------------------------------------------------------
%.elf: $(OFILES)	
	@echo Linking $(notdir $@)
	$(LD) $(LDFLAGS) $(OFILES) -o $@

#---------------------------------------------------------------------------------
%.o: %.cpp
	@echo $(notdir $<)
	$(CXX) -MMD -MP -MF $(DEPSDIR)/$*.d $(CXXFLAGS) -c $< -o $@ $(ERROR_FILTER)
	
#---------------------------------------------------------------------------------
%.o: %.c
	@echo $(notdir $<)
	$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d $(CFLAGS) -c $< -o $@ $(ERROR_FILTER)
	
#---------------------------------------------------------------------------------
%.o: %.s
	@echo $(notdir $<)
	$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d -x assembler-with-cpp $(ASFLAGS) -c $< -o $@ $(ERROR_FILTER)

-include $(DEPSDIR)/*.d
 
#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------

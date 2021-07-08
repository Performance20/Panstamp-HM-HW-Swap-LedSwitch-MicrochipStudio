################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../Fhem\ Template


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../klappe.cpp \
../regtable.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
klappe.o \
regtable.o

OBJS_AS_ARGS +=  \
klappe.o \
regtable.o

C_DEPS +=  \
klappe.d \
regtable.d

C_DEPS_AS_ARGS +=  \
klappe.d \
regtable.d

OUTPUT_FILE_PATH +=Klappe.elf

OUTPUT_FILE_PATH_AS_ARGS +=Klappe.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+=  \
C:/Users/Helge/source/repos/Performance20/Panstamp-AskSinnHW-Swap-Katzenklappe-MicrochipStudio/SwapKatzenklappe/ArduinoCore/Release\ OHNE\ Bootloader/libArduinoCore.a

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./klappe.o: .././klappe.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DF_CPU=8000000L -DARDUINO=108013 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR -DNDEBUG  -I"..\\..\ArduinoCore\include" -I"..\\..\ArduinoCore\include\core" -I"..\\..\ArduinoCore\include\variants\eightanaloginputs" -I"..\\..\ArduinoCore\include\variants\standard" -I"..\\..\ArduinoCore\include\libraries\SWAP" -I"..\\..\ArduinoCore\include\libraries\Panstamp" -I"..\\..\ArduinoCore\include\libraries\as5600" -I"..\\..\ArduinoCore\include\libraries\Wire" -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\include"  -Os -fno-threadsafe-statics -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -w -mmcu=atmega328p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\gcc\dev\atmega328p" -c -std=gnu++11 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./regtable.o: .././regtable.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DF_CPU=8000000L -DARDUINO=108013 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR -DNDEBUG  -I"..\\..\ArduinoCore\include" -I"..\\..\ArduinoCore\include\core" -I"..\\..\ArduinoCore\include\variants\eightanaloginputs" -I"..\\..\ArduinoCore\include\variants\standard" -I"..\\..\ArduinoCore\include\libraries\SWAP" -I"..\\..\ArduinoCore\include\libraries\Panstamp" -I"..\\..\ArduinoCore\include\libraries\as5600" -I"..\\..\ArduinoCore\include\libraries\Wire" -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\include"  -Os -fno-threadsafe-statics -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -w -mmcu=atmega328p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\gcc\dev\atmega328p" -c -std=gnu++11 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR8/GNU Linker : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Klappe.map" -Wl,--start-group -Wl,-lm -Wl,-lArduinoCore  -Wl,--end-group -Wl,-L"C:\Users\Helge\source\repos\PERFOR~1\PA1137~1\SWAPKA~1\ARDUIN~1\RELEAS~1"  -Wl,--gc-sections -mmcu=atmega328p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\gcc\dev\atmega328p" -Os  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "Klappe.elf" "Klappe.hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Klappe.elf" "Klappe.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Klappe.elf" > "Klappe.lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "Klappe.elf" "Klappe.srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "Klappe.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Klappe.elf" "Klappe.a" "Klappe.hex" "Klappe.lss" "Klappe.eep" "Klappe.map" "Klappe.srec" "Klappe.usersignatures"
	
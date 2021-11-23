# Makefile for Demo application
PROJECT_NAME = Out
# Microcontroller specific
MCU = atmega32a
# Input Frequency 
F_CPU = 16000000
#Flashing board port
COMPORT= COM4

#Output folder name
output_folder = OUT

#includes of project
INCLUDES += $(wildcard includes/*.h)

#sources of project
SOURCES +=  $(wildcard sources/*.c)

#objects of project
OBJECTS += $(patsubst sources/%.c, $(output_folder)/%.o, $(SOURCES))

#Compiler 
CC = gcc.exe
#Linker
LD = ld.exe
#Assembler
AS = as.exe
#Object Dump
DMP =objdump.exe
#Object copy
CPY = objcopy.exe
#Object size
SIZ = size.exe

#Compiller flags
CFLAGS = -Wall -O1 -mmcu=$(MCU) -DF_CPU=$(F_CPU) -D__AVR_ATmega32A__ -funsigned-char -funsigned-bitfields -ffunction-sections -fdata-sections -Iincludes/
LDFLAGS = -mmcu=atmega32a -Wl,-Map,$(output_folder)/$(PROJECT_NAME).map  -gc-sections 

#Compiling all .c files and generates .o files
$(output_folder)/%.o: sources/%.c 
	@echo Compiling: $<
	$(CC)  $(CFLAGS) -c $<  -o $@

#Assembling all .s files and generates .o files
#$(output_folder)/%.o: src/%.s $(INCLUDES)
#	@echo Compiling: $<
#	@$(CC)  $(CFLAGS) -c $< -o $@

#Compiling trigger and linking objects
linking: $(OBJECTS)
	@echo Linking objects: $(OBJECTS)  ...
	$(CC) $(LDFLAGS) -o $(output_folder)/$(PROJECT_NAME).elf $(OBJECTS)
	@echo $(PROJECT_NAME).elf file has been generated !

flash:
	@../../tools/and-load.exe -c $(COMPORT) -h $(output_folder)/$(PROJECT_NAME).hex

#Create output folder
create_output:
	@echo Start building ...
ifneq ($(wildcard $(output_folder)),$(output_folder))
	@mkdir $(output_folder)
endif


#Trigger of entire build procces
.PHONY: all	
all: create_output generate
	@echo Build successfully done !

generate: linking 
#Display object sections size	
	@$(SIZ) $(output_folder)/$(PROJECT_NAME).elf
#Generate dump file
	@$(DMP) -h -S $(output_folder)/$(PROJECT_NAME).elf > $(output_folder)/$(PROJECT_NAME).lst
	@echo $(PROJECT_NAME).lst file has been generated !
#Generate hex file
	@$(CPY) -O ihex $(output_folder)/$(PROJECT_NAME).elf $(output_folder)/$(PROJECT_NAME).hex
	@echo $(PROJECT_NAME).hex file has been generated !

#Clean output folder
clean:
	@rm -rf $(output_folder)
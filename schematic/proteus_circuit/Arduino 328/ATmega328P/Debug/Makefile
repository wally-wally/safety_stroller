###############################################################################
# Makefile for project 
###############################################################################

## General options
PROJECT = 
MCU = ATmega328P
COMPILER = "Arduino AVR"
TARGET = Debug
SHELL = C:\WINDOWS\system32\cmd.exe

## Tools general options
APPFLAGS=-C pro328 -N atmega328p -F 8000000
CCFLAGS=-Wall -gdwarf-2 -fsigned-char -MD -MP -DF_CPU=8000000 -I arduino -I .. -DARDUINO=105 @arduino/libs.inc -O1 -mmcu=atmega328p
LDFLAGS=-Wl,--gc-sections -mmcu=atmega328p

## Processing Tools
APP=mksketch
CC=avr-gcc
ASM=avr-gcc
LD=avr-gcc
#  C:/Users/parksh/Desktop/321/Arduino 328/ATmega328P/Debug/Debug.elf: TOOL=LD
#  Post: $(OBJ) avr-objcopy -O ihex -R .eeprom "./Debug.elf" "./Debug.hex"
#  Post: $(OBJ) avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O ihex "./Debug.elf" "./Debug.eep" || exit 0 
#     C:/Users/parksh/Desktop/321/Arduino 328/ATmega328P/Debug/main.o: TOOL=CC
#        C:/Users/parksh/Desktop/321/Arduino 328/ATmega328P/Debug/main.cpp: TOOL=APP
#        Post: make -f arduino/Makefile
#        Post: $(APP) -O main.cpp ../main.ino
#           C:/Users/parksh/Desktop/321/Arduino 328/ATmega328P/main.ino

# Build tree:
all:	Debug

Debug:	Debug.elf

Debug.elf:	main.o 
	$(LD) $(LDFLAGS)  -o "./Debug.elf" "main.o" arduino/arduino.a
	$(OBJ) avr-objcopy -O ihex -R .eeprom "./Debug.elf" "./Debug.hex"
	$(OBJ) avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O ihex "./Debug.elf" "./Debug.eep" || exit 0 

main.o:	main.cpp 
	$(CC) $(CCFLAGS)  -o "main.o" -c "main.cpp"

main.cpp:	../main.ino 
	$(APP) $(APPFLAGS)  ../main.ino
	make -f arduino/Makefile
	$(APP) -O main.cpp ../main.ino

# tidy - delete all temporary files which are not involved in the target generation
tidy:
	rm -rf ./main.d
	rm -rf main.arduino/arduino.a
	rm -rf main.-r arduino/*.o
	rm -rf main.-r arduino/*.d

# cleanup - delete all generated files
clean:	tidy
	rm -rf Debug.elf
	rm -rf main.o
	rm -rf main.cpp


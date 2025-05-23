MCU = atmega328p
F_CPU = 16000000UL
CC = /home/piush/avr-toolchain/bin/avr-g++
OBJCOPY = /home/piush/avr-toolchain/bin/avr-objcopy

INCLUDES = -I/home/piush/avr-toolchain/avr/include
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall $(INCLUDES)

TARGET = ./tmp/main_avr
SRC = ./src/main_avr.cpp

all:
	$(CC) $(CFLAGS) -o $(TARGET).elf $(SRC)
	$(OBJCOPY) -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex

flash:
	avrdude -c arduino -p $(MCU) -P /dev/ttyACM0 -b 115200 -U flash:w:$(TARGET).hex

clean:
	rm -f ./tmp/*.elf ./tmp/*.hex

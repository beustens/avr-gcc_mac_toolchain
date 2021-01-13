TARGET = project
MCU = attiny814
DEVICE = tiny814
# clock settings applied in main.c
CLOCK = 2000000
PROGRAMMER = /dev/tty.usbserial-A50285BI

SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(MCU)

# compiling and linking, target is the finished hex file
all: $(TARGET).hex

# compile source files to object files
.c.o:
	$(COMPILE) -c $< -o $@

# link the object files together
$(TARGET).elf: $(OBJECTS)
	$(COMPILE) $(OBJECTS) -o $(TARGET).elf

# convert elf file to hex file
$(TARGET).hex: $(TARGET).elf
	avr-objcopy -j .text -j .data -j .rodata -O ihex $(TARGET).elf $(TARGET).hex

# flash (call make flash), requires pyupdi installed
flash: $(TARGET).hex
	python3 -m updi.pyupdi -d $(DEVICE) -c $(PROGRAMMER) -f "$(shell pwd)/$(TARGET).hex"

clean:
	rm -f $(TARGET).hex $(TARGET).elf $(OBJECTS)
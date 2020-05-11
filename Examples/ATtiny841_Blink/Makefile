TARGET		= project
MCU			= attiny841
DEVICE		= t841
CLOCK		= 1000000
PROGRAMMER	= -c stk500 -P /dev/cu.SLAB_USBtoUART
SOURCES		= main.c
FUSES		= -U hfuse:w:0xdf:m -U lfuse:w:0x62:m

OBJECTS = $(SOURCES:.c=.o)
AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
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
	avr-objcopy -O ihex -j .data -j .text $(TARGET).elf $(TARGET).hex
	
# flashing and post processing (must be called from user via "make flash" e. g.)
flash: all
	$(AVRDUDE) -U flash:w:$(TARGET).hex:i

fuse:
	$(AVRDUDE) $(FUSES)

clean:
	rm -f $(TARGET).hex $(TARGET).elf $(OBJECTS)
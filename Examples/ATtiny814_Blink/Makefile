TARGET		= project
CLOCK		= 2000000 # configured in main
SOURCES		= main.c

OBJECTS = $(SOURCES:.c=.o)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -D__AVR_DEVICE_NAME__=attiny814 -D__AVR_DEV_LIB_NAME__=tn814

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

clean:
	rm -f $(TARGET).hex $(TARGET).elf $(OBJECTS)
TARGET		= project
MCU			= attiny841
DEVICE		= t841
CLOCK		= 128000
PROGRAMMER	= -c stk500 -P /dev/cu.SLAB_USBtoUART
SOURCE		= main
FUSES		= -U hfuse:w:0xdf:m -U lfuse:w:0xe4:m -U efuse:w:0xbf:m # use ULP oscillator (128 KHz) without clock divide

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(MCU)

# just do all the usual stuff consecutive
all:
	# compile
	$(COMPILE) -c $(SOURCE).c -o $(SOURCE).o
	# link
	$(COMPILE) $(SOURCE).o -o $(TARGET).elf
	# hex
	avr-objcopy -O ihex -j .data -j .text $(TARGET).elf $(TARGET).hex
	# flash
	$(AVRDUDE) -U flash:w:$(TARGET).hex:i
	# clean
	rm -f $(TARGET).hex $(TARGET).elf $(SOURCE).o

# this is only executed if called via "make fuse"
fuse:
	$(AVRDUDE) $(FUSES)
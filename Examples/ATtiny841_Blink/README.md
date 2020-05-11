# How to
Assuming you have a STK500 compatible AVR ISP programmer such as the *mySmartUSB light*, connect the ISP pins to the corresponding pins on the microcontroller. By default, on the Attiny841:
- VCC: Pin 1
- RESET: Pin 4
- MOSI: Pin 7
- MISO: Pin 8
- SCK: Pin 9
- GND: Pin 14

Connect a LED in series with a 1k resistor between Pin 2 (PB0) and GND.

With the programmer connected to the computer, check its name with `ls /dev/cu.*` and modify the line `PROGRAMMER	= -c stk500 -P /dev/cu.SLAB_USBtoUART` in the [make file](Makefile) accordingly.

Make sure the **AVRToolchain/bin/** path is in your systems `PATH` variable.

From inside this directory, call `make flash clean`. This should compile the source code, flash the result to the microcontroller and remove the compiled files afterwards.

Note that depending on your programmer, you might have to connect an additional power supply (3 or 5 V) to your microcontroller to the see the LED blinking.
# Prerequisites
- avr-gcc toolchain installed
- download [pyupdi](https://github.com/mraardvark/pyupdi)
- get a FTDI USB-to-UART adapter, connect its RX and TX with a 4.7k resistor and connect RX with the RESET pin of the microcontroller. Connect 5V to the VCC pin and GND to the GND pin

![programmer connected](docs/Programmer.jpg)

# Compile and flash
1. in the project directory, run `make`
2. the pyupdi directory, run `python3 pyupdi.py -d tiny814 -c /dev/tty.usbserial-A50285BI -f ../path/to/ATtiny814_Blink/project.hex`
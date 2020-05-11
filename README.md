# AVR-GCC toolchain for macOS
The toolchain provides 64-bit binaries and libraries to programm 8-bit microcontrollers from Atmel. It supports macOS 10.15 (Catalina), which does not run 32-bit binaries anymore.

## Credits
This project is basically just a snapshot of the AVR toolchain in the [Arduino 1.8.12 IDE](https://www.arduino.cc/en/Main/Software), located in */Applications/Arduino.app/Contents/Java/hardware/tools/avr*, but with a slight change to **avrdude** to use *../etc/avrdude.conf* instead of the hard-coded default path.

## How to install
Simply clone/download this project and modify your systems `PATH` variable to look in its *bin/* directory, so either 
- add `export PATH="$PATH:[this directory path]/AVRToolchain/bin"` to your *~/.bash_profile* (if you use bash) or *~/.zprofile* (if you use zshell)

or
- add `[this directory path]/AVRToolchain/bin` to */private/etc/paths*

where [this directory path] have to be replaced by the actual path of the downloaded project.
Close and re-open the Terminal and you should by able to call `avr-gcc` and `avrdude`.

## Example projects
In [Examples](Examples), blinking LED projects with brief documentation for the ATtiny841 and the ATtiny814 microcontrollers can be found.
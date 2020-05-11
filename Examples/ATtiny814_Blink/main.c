#include <avr/io.h>
#include <util/delay.h>

int main() {
	// disable protection to configure clock frequency
	CCP = CCP_IOREG_gc;
	
	// configure CPU frequency
	CLKCTRL.MCLKCTRLA = CLKCTRL_CLKSEL_OSC20M_gc; // use 20 MHz internal clock as source
	CLKCTRL.MCLKCTRLB = CLKCTRL_PDIV_10X_gc | CLKCTRL_PEN_bm; // divide by 10 and enable divider
	
	// configure IO for driving LED
	PORTB.DIR = PIN0_bm;
	
	// main program loop
	while(1) {
		_delay_ms(500);
		// toggle LED pin
		PORTB.OUT ^= PIN0_bm;
	}
	return 0;
}
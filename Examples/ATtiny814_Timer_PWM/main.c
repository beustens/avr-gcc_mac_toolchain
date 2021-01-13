#include <avr/io.h>
#include <stdint.h>

// prototypes
void configClock();
void configTCA();

int main() {
	// setup
	configClock();
	configTCA();
	
	// main program loop
	while (1) {
		;
	}
	return 0;
}

void configClock() {
	// configure CPU frequency to 2MHz
	CCP = CCP_IOREG_gc; // disable protection to configure clock frequency
	CLKCTRL.MCLKCTRLA = CLKCTRL_CLKSEL_OSC20M_gc; // use 20 MHz internal clock as source
	CCP = CCP_IOREG_gc; // disable protection to configure clock frequency
	CLKCTRL.MCLKCTRLB = CLKCTRL_PDIV_10X_gc | CLKCTRL_PEN_bm; // divide by 10 and enable divider
}

void configTCA() {
	// enable compare channel 0 | 1 | set single-slope PWM mode
	TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_CMP1EN_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc;
	
	// disable event counting
	TCA0.SINGLE.EVCTRL &= ~(TCA_SINGLE_CNTEI_bm);

	// PORTB as output (why?)
	PORTB.DIR = PIN0_bm | PIN1_bm;

	// set PWM frequency and duty cycle
	TCA0.SINGLE.PER = 20000; // period
	TCA0.SINGLE.CMP0 = 2000; // pulse length, low duty cycle on PB0
	TCA0.SINGLE.CMP1 = 15000; // pulse length, high duty cycle on PB1

	// set clock source (sys_clk/2) | start timer
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV2_gc | TCA_SINGLE_ENABLE_bm;
}
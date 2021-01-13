#include <avr/io.h>
#include <stdint.h>

// defines
#define REF_MV 5000
#define ADC_SHIFT_DIV64 6

// prototypes
void configClock();
void configGPIO();
void configADC();
uint16_t readADC();
uint16_t readmV();

int main() {
	// setup
	configClock();
	configGPIO();
	configADC();
	
	// main program loop
	while (1) {
		uint16_t throttle = readmV();
		if (throttle < 100) PORTB.OUT = PIN0_bm;
		if (throttle > 900) PORTB.OUT = PIN1_bm;
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

void configGPIO() {
	PORTB.DIR = PIN0_bm | PIN1_bm; // PB0 and PB1 as output
}

void configADC() {
	// configure to accumulate 64 10bit samples proportional VDD at PA3 per read

	// Disable digital input buffer
	PORTA.PIN3CTRL &= ~PORT_ISC_gm;
	PORTA.PIN3CTRL |= PORT_ISC_INPUT_DISABLE_gc;
	
	// Disable pull-up resistor
	PORTA.PIN3CTRL &= ~PORT_PULLUPEN_bm;

	// CLK_PER divided by 4 | VDD reference
	ADC0.CTRLC = ADC_PRESC_DIV4_gc | ADC_REFSEL_VDDREF_gc;
	
	// ADC Enable: enabled | 10-bit mode
	ADC0.CTRLA = ADC_ENABLE_bm | ADC_RESSEL_10BIT_gc;
	
	// Select ADC channel
	ADC0.MUXPOS  = ADC_MUXPOS_AIN3_gc;

	// Set the accumulator mode to accumulate 64 samples
	ADC0.CTRLB = ADC_SAMPNUM_ACC64_gc;
}

uint16_t readADC() {
	// Start ADC conversion
	ADC0.COMMAND = ADC_STCONV_bm;
	
	// Wait until ADC conversion done
	while ( !(ADC0.INTFLAGS & ADC_RESRDY_bm) );
	
	// Clear the interrupt flag by writing 1
	ADC0.INTFLAGS = ADC_RESRDY_bm;
	
	return ADC0.RES;
}

uint16_t readmV() {
	// average multiple ADC reads
	uint16_t adcVal = readADC();
	adcVal = adcVal >> ADC_SHIFT_DIV64;

	// convert to mV
	uint16_t mV = (uint32_t)adcVal*REF_MV/1024;
	return mV;
}
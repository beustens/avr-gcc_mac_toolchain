#include <avr/io.h> // for pin definitions
#include <stdint.h> // for data types
#include <util/delay.h>	// for _delay_ms

// defines
#define ADC_CHN 1 // (PA1) input for measuring IR phototransistor voltage
#define IR_OUT_PIN PA2 // output for IR LED
#define SIG_OUT_PIN PB0 // output to signalize proximity
#define N_AVR 64 // number of ADC read samples to average
#define THRESH 2 // ADC value threshold to detect proximity
#define OUT_TIME 100 // minimum time in ms to output signal

// functions
void configGPIO() {
	// output pins
	DDRA = (1 << IR_OUT_PIN);
	DDRB = (1 << SIG_OUT_PIN);
}

void configADC() {
	// ADC setup
	//ADMUXB = 0; // select reference voltage VCC (all registers are initially set to zero anyway)
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1); // ADC clock prescale 8
	ADCSRA |= (1 << ADEN); // enable ADC
	// dummy conversion (dry run)
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC));
	(void) ADCH;
}

uint16_t readADC(uint8_t chan) {
	uint16_t adcVal = 0;
	ADMUXA = chan; // select channel for input (see datasheet p. 2 which channel is on each pin)
	ADCSRA |= (1 << ADSC); // start conversion
	// wait until the conversion is finished
	while (ADCSRA & (1 << ADSC));
	// load values into adcVal
	adcVal = ADCL;
	adcVal += (ADCH << 8);
	return adcVal;
}

uint16_t getPhotoLevel() {
	// average multiple ADC reads
	uint16_t val = 0;
	for (uint8_t i = 0; i < N_AVR; i++) {
		val += readADC(ADC_CHN);
	}
	val /= N_AVR;
	return val;
}

// main program
int main() {
	// init
	configGPIO();
	configADC();
	
	while (1) {
		// measure photo transistor voltage level with IR LED on
		PORTA |= (1 << IR_OUT_PIN);
		uint16_t onLevel = getPhotoLevel();

		// measure photo transistor voltage level with IR LED off
		PORTA &= ~(1 << IR_OUT_PIN);
		uint16_t offLevel = getPhotoLevel();

		// compare values
		if (onLevel < offLevel-THRESH) {
			PORTB |= (1 << SIG_OUT_PIN);
			_delay_ms(OUT_TIME);
		} else {
			PORTB &= ~(1 << SIG_OUT_PIN);
		}
	}
}
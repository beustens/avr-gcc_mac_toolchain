#include <avr/io.h>
#include <util/delay.h>

int main() {
	DDRB = 1 << PB0;
	while(1) {
		_delay_ms(500);
		PORTB ^= 1 << PB0;
	}
	return 0;
}
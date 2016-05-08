#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

void Timer3_Init(){

	cli();//stop interrupts

	DDRC |= (1 << DDC6);
	// PB5

	ICR3 = 1251;
	// set TOP to 50 Hz

	OCR3A = 7;
	// set PWM for 12% duty cycle @ 16bit

	//OCR1B = 0xBFFF;
	// set PWM for 75% duty cycle @ 16bit

	TCCR3A |= (1 << COM3A1) | (1 << COM3B1);
	// set non-inverting mode

	TCCR3A |= (1 << WGM31);
	TCCR3B |= (1 << WGM32) | (1 << WGM33);
	// set Fast PWM mode using ICR1 as TOP

	TCCR3B |= (1 << CS32);
	// START the timer with 256 prescaler

	sei();//allow interrupts

}

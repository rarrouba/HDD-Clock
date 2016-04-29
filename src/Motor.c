
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

void Timer1_Init(){

	cli();//stop interrupts

	DDRB |= (1 << DDB5);
	// PB5

	ICR1 = 1249;
	// set TOP to 16bit (50 Hz)

	OCR1A = 7;
	// set PWM for 12% duty cycle @ 16bit

	//OCR1B = 0xBFFF;
	// set PWM for 75% duty cycle @ 16bit

	TCCR1A |= (1 << COM1A1) | (1 << COM1B1);
	// set non-inverting mode

	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	// set Fast PWM mode using ICR1 as TOP 

	TCCR1B |= (1 << CS12);
	// START the timer with prescaler 8

	sei();//allow interrupts

}

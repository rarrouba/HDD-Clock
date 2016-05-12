#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>



char KnopESC = 0;

void Timer1_Motor_Init(){

	EICRB |= (1<< ISC51) | (1<< ISC50);
	EIMSK |= (1<< INT5);
	SREG = 0b10000000;

	cli();//stop interrupts

	DDRB |= (1 << DDB5);
	// PB5

	ICR1 = 1251;
	// set TOP to 50 Hz

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
	// START the timer with 256 prescaler

	sei();//allow interrupts

}


void Opstart_ESC(){

	OCR1A = 156;
	while(!KnopESC){
		_delay_ms(0);
	}
	OCR1A = 56;
	_delay_ms(4000);
	OCR1A = 7;


}

ISR(INT5_vect)  // knop Zuiden
{
	KnopESC = 1;

}

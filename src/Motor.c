
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>


uint8_t count = 0;
// 0°  => 0.388ms
//90°  => 1.264ms
//180°  => 2.140ms
void Timer1_init()
{
	cli();//stop interrupts
	
		  TCCR1A = 0;// set entire TCCR1A register to 0
		  TCCR1B = 0;// same for TCCR1B
		  TCNT1  = 0;//initialize counter value to 0
		  // set compare match register for (20 ms-1.264ms)*2 increments
		  OCR1A = 37471;
		  // turn on CTC mode
		  TCCR1B |= (1 << WGM12);
		  // Set CS10 and CS12 bits for 8 prescaler
		  TCCR1B |= (1 << CS01) ;
		  // enable timer compare interrupt
		  TIMSK1 |= (1 << OCIE1A);
		  
		sei();//allow interrupts
}


int main (void)
{
	DDRB |= (1<<1);


	Timer1_init();





   while(1)
    {

	}



}

ISR(TIMER1_COMPA_vect)
{
		count++;
	    if (count % 2 == 0){

	    	PORTB &= (0<<DDB1);
		//(20 ms-1.264ms)*2 increments
	    	OCR1A = 37471;

		}

		else{
		PORTB |= (1<<DDB1);
		//(1.264ms)*2 increments
		OCR1A = 2527;


		}



}



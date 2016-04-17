
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>


uint8_t count = 0;
int graden =0;
int ocrStap = 20;
int beginOCRh = 1199;
int beginOCRl = 38799;

void Timer1_init()
{
	cli();//stop interrupts

		//set timer1 interrupt at 1Hz

		  TCCR1A = 0;// set entire TCCR1A register to 0
		  TCCR1B = 0;// same for TCCR1B
		  TCNT1  = 0;//initialize counter value to 0
		  // set compare match register for 416hz increments
		  OCR1A = 37471;// = (16*10^6) / (1*1024) - 1 (must be <65536)
		  // turn on CTC mode
		  TCCR1B |= (1 << WGM12);
		  // Set CS10 and CS12 bits for 1 prescaler
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

	    	OCR1A = 37471;

		}

		else{
			  PORTB |= (1<<DDB1);

				  OCR1A = 2527;


		}



}



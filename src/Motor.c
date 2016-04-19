
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

// 0°  => 0.388ms
//90°  => 1.264ms
//180°  => 2.140ms

uint8_t count = 0;
int OCRTotaal = 39998;
int OCR0m6s = 1199;
int OCR0m5s = 999;
int OCR1ms = 1999;
int OCR2ms = 3999;
int OCR1m5s = 2999;
int OCRHuidig = 999;
unsigned char knopGedrukt = 1;



void Timer1_init()
{
	cli();//stop interrupts

		//set timer1 interrupt at 1Hz

		  TCCR1A = 0;// set entire TCCR1A register to 0
		  TCCR1B = 0;// same for TCCR1B
		  TCNT1  = 0;//initialize counter value to 0
		  // set compare match register for 416hz increments
		  OCR1A = OCRTotaal-OCR1ms;// = (16*10^6) / (1*1024) - 1 (must be <65536)
		  // turn on CTC mode
		  TCCR1B |= (1 << WGM12);
		  // Set CS10 and CS12 bits for 1 prescaler
		  TCCR1B |= (1 << CS01) ;
		  // enable timer compare interrupt
		  TIMSK1 |= (1 << OCIE1A);




		sei();//allow interrupts
}


void INT_init()
{
	DDRE = 0b00001111;
	PORTE = 0b11110000;
	EIMSK = 0xF0;
	EICRB = 0xAA;
	SREG = 0b10000000;
}

int main (void)
{
	_delay_ms(2000);
	DDRB |= (1<<1);


	Timer1_init();
	INT_init();



   while(1)
    {

	}



}

ISR(TIMER1_COMPA_vect)
{
	count++;
		    if (count % 2 == 0){

		    if(knopGedrukt) PORTB &= (0<<DDB1);
			//(20 ms-1.264ms)*2 increments
		    	OCR1A = OCRTotaal-OCRHuidig;
		    //knopGedrukt=0;
			}

			else{
			if(knopGedrukt)  PORTB |= (1<<DDB1);
			//(1.264ms)*2 increments
			OCR1A = OCRHuidig;
			if(OCRHuidig<OCR2ms){
			OCRHuidig+=16;
			}

			else{
				OCRHuidig=OCR2ms;
			}
			}

}

ISR(INT4_vect)   // knop Westen
	{
		OCRHuidig = OCR1ms;
	}

ISR(INT5_vect)  // knop Zuiden
	{
	OCRHuidig = OCR1m5s;

	}
ISR(INT6_vect) // knop Oosten
	{
	OCRHuidig = OCR2ms;

	}
ISR(INT7_vect) // knop Noorden
	{
		if(knopGedrukt){
			knopGedrukt =0;
		}

		else{

			knopGedrukt = 1;
		}
	}



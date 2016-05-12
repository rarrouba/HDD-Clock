#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "HeaderFiles/dwenguinoBoard.h"
#include "HeaderFiles/dwenguinoLCD.h"

int tijdMotor = 0;  // moet in main opgeroepen kunnen worden


void Timer3_Init(){


	DDRD |= (0 << DDD3);		// PIN for PCINT0
	PORTD |= (1 << DDD3);		// Pull-Up
	EICRA |= (1<< ISC31);
	EIMSK |= (1<< INT3);
	SREG = 0b10000000;


	cli();//stop interrupts





		//set timer1 interrupt at 1Hz

		  TCCR3A = 0;// set entire TCCR1A register to 0
		  TCCR3B = 0;// same for TCCR1B

		  TCNT3  = 0;//initialize counter value to 0
		  OCR3A = 0;//
		  OCR3B = 0;

		  // turn on Normal mode
		  TCCR3B |= (0 << WGM30) | (0 << WGM31) | (0 << WGM32)| (0 << WGM31);

		  // Set CS10 and CS12 bits for 1024 prescaler => 15,625 kHz = freq Timer1
		  TCCR3B |= (1 << CS32) | (1 << CS30);

		  // Falling edge trigger with input capture
		  TCCR3B |= (0 << ICES3);

		  // input capture interrupt enable
		  TIMSK3 |=  (1 << ICIE3)| (1 << TOIE3);




	sei();//allow interrupts

}

ISR(INT3_vect)  // IR_Sensor triggered
{
   tijdMotor = ICR3;      // save duration of last revolution
   TCNT3 = 0;       // restart timer for next revolution
}

ISR(TIMER3_OVF_vect)    // counter overflow/timeout
   { tijdMotor = 0;

   }



void LCDSnelheid(){

	clearLCD();
	  setCursorLCD(0, 0);

	_delay_ms(50);

	if(tijdMotor>0){

		printIntToLCD(15625/tijdMotor,1,4);

	}
	else{
		printCharToLCD(78,1,4);

	}
}


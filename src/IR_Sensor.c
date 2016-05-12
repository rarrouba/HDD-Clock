#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "HeaderFiles/dwenguinoBoard.h"
#include "HeaderFiles/dwenguinoLCD.h"

int tijdMotor = 0;  // moet in main opgeroepen kunnen worden


void Timer1_Init(){


	DDRB |= (0 << DDB0);		// PIN for PCINT0
	PORTB |= (1 << DDB0);		// Pull-Up
	EICRA |= (1<< ISC01);
	PCMSK0 |= (1<< PCINT0);
	PCICR |= (1<< PCIE0);

	cli();//stop interrupts





		//set timer1 interrupt at 1Hz

		  TCCR1A = 0;// set entire TCCR1A register to 0
		  TCCR1B = 0;// same for TCCR1B

		  TCNT1  = 0;//initialize counter value to 0
		  OCR1A = 0;//
		  OCR1B = 0;

		  // turn on Normal mode
		  TCCR1B |= (0 << WGM10) | (0 << WGM11) | (0 << WGM12)| (0 << WGM11);

		  // Set CS10 and CS12 bits for 1024 prescaler => 15,625 kHz = freq Timer1
		  TCCR1B |= (1 << CS12) | (1 << CS10);

		  // Falling edge trigger with input capture
		  TCCR1B |= (0 << ICES1);

		  // input capture interrupt enable
		  TIMSK1 |=  (1 << ICIE1)| (1 << TOIE1);




	sei();//allow interrupts

}

ISR(PCINT0_vect)  // IR_Sensor triggered
{
   tijdMotor = ICR1;      // save duration of last revolution
   TCNT1 = 0;       // restart timer for next revolution
}

ISR(TIMER1_OVF_vect)    // counter overflow/timeout
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

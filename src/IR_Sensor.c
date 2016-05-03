#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "HeaderFiles/dwenguinoBoard.h"
#include "HeaderFiles/dwenguinoLCD.h"

int tijdMotor = 0;  // moet in main opgeroepen kunnen worden


void Timer3_Init(){


	DDRC |= (0 << DDC7);		// PIN for ICP3
	PORTC |= (1 << DDC7);		// Pull-Up


	cli();//stop interrupts

		//set timer1 interrupt at 1Hz

		  TCCR3A = 0;// set entire TCCR3A register to 0
		  TCCR3B = 0;// same for TCCR3B

		  TCNT3  = 0;//initialize counter value to 0
		  OCR3A = 0;//
		  OCR3B = 0;

		  // turn on Normal mode
		  TCCR3B |= (0 << WGM30) | (0 << WGM31) | (0 << WGM32)| (0 << WGM33);

		  // Set CS10 and CS12 bits for 1024 prescaler => 15,625 kHz = freq Timer3
		  TCCR3B |= (1 << CS12) | (1 << CS10);

		  // Falling edge trigger with input capture
		  TCCR3B |= (0 << ICES3);

		  // input capture interrupt enable
		  TIMSK3 |=  (1 << ICIE3)| (1 << TOIE3);




	sei();//allow interrupts

}

ISR(TIMER3_CAPT_vect)  // IR_Sensor triggered
{
   tijdMotor = ICR3;      // save duration of last revolution
   TCNT1 = 0;       // restart timer for next revolution
}

ISR(TIMER3_OVF_vect)    // counter overflow/timeout
   { tijdMotor = 0;

   }

void LCDSnelheid(){
	clearLCD();
	setCursorLCD(0, 0);
	printIntToLCD(15625/tijdMotor,0,0);
}

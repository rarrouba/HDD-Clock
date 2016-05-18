/*
 * IR_Sensor.c
 *
 *  Created on: 2-mei.-2016
 *      Author: Redouane
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "HeaderFiles/dwenguinoBoard.h"
#include "HeaderFiles/dwenguinoLCD.h"
#include "IR_Sensor.h"

int tijdMotor = 0;  // moet in main opgeroepen kunnen worden

void Timer3_Init(){			// methode die timer 3 initialiseert om de snelheid van de motor te meten via de IR-sensor


	DDRD |= (0 << DDD3);		// Pin als input declaren 
	PORTD |= (1 << DDD3);		// Pull-Up 
	EICRA |= (1<< ISC31);		// trigger bij dalende flank
	EIMSK |= (1<< INT3);		// activeren van interrupt 3 
	SREG = 0b10000000;		// activeren van de interrupts


	cli();//stop interrupts


		  TCCR3A = 0;// hele register op 0 zetten
		  TCCR3B = 0;// ook TCCR3B

		  TCNT3  = 0;// counter waarde op 0 inittialiseren
		  OCR3A = 0;
		  OCR3B = 0;

		  //  Normal mode
		  TCCR3B |= (0 << WGM30) | (0 << WGM31) | (0 << WGM32)| (0 << WGM31);

		  //   CS32 bits voor 256 prescaler => 62,5 kHz = freq Timer3
		  TCCR3B |= (1 << CS32);

		  // overflow interrupt enable
		  TIMSK3 |=  (1 << TOIE3) ;




	sei();// interrupts enable

}

ISR(INT3_vect)  // IR_Sensor triggered
{
   tijdMotor = TCNT3;      // opslaan tijd van laatste toer
   TCNT3 = 0;       // restart timer voor volgende toer
}

ISR(TIMER3_OVF_vect)    // counter overflow/timeout
   { tijdMotor = 0;

   }
   




void LCDSnelheid(){		// methode die wordt gebruikt bij het debuggen om de snelheid van de schijf te weten

	clearLCD();
	  setCursorLCD(0, 0);

	_delay_ms(50);

	if(tijdMotor>0){

		printIntToLCD(62500/tijdMotor,1,4);

	}
	else{
		printCharToLCD(78,1,4);

	}
}


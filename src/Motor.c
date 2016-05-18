#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>



char KnopESC = 0;
long secondesT1 = 0;  // secondes 1/50

int SecondesT1(unsigned int nummer){
	secondesT1= secondesT1-nummer;
	return secondesT1;
}


void Timer1_Motor_Init(){	// methode die timer 1 initialiseert om het PWM signaal voor de ESC te genereren

	

	cli();//stop interrupts

	DDRB |= (1 << DDB5); // Pin B5 als output, die wordt gebruikt voor OCR1A
	
	ICR1 = 4999;// TOP op 50 Hz zetten

	OCR1A = 250; // PWM met ca 1 % duty cycle

	TCCR1A |= (1 << COM1A1) ; // overschrijven van poort functionaliteit met OCnA output

	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	// zet Fast PWM mode aan met ICR1 als TOP

	TCCR1B |= (1 << CS10) | (1 << CS11);
	// start de timer met 64 prescaler
	TIMSK1 |=  (1 << TOIE1) ;

	sei();//toestaan interrupts

}

ISR(TIMER1_OVF_vect){
	secondesT1++;


}


void Opstart_ESC(){			// methode die de opstart sequentie voorziet van de ESC, die in de datasheet wordt uitgelegd

/* Voor onze ESC is een specifieke opstart procedure nodig vooraleer deze kan worden gebruikt om de motor aan te sturen. 
   Er wordt een max signaal (duty cycle van 10%) gestuurd. De motor wordt dan aangesloten op de voeding. Als men een dubbele pieptoon
   hoort, moet er op de knop (S) gedrukt worden. Op dat moment zal de duty cycle veranden naar het minimum (4,5%). Daarna zal men weer een
   dubbele toon horen gevolgd door een melodietje. De ESC kan nu worden gebruikt om de motor aan testuren */


	EICRB |= (1<< ISC51) | (1<< ISC50);	// stijgende flank detectie
	EIMSK |= (1<< INT5);			// interrupt 5 voor de knop S
	SREG = 0b10000000;			// globale interrupt enable
	
	OCR1A = 125;				// maximaal signaal voor ESC
	while(!KnopESC){			// zolang de knop niet ingedrukt zal signaal niet veranderen
		_delay_ms(0);
	}
	OCR1A = 56;				// minimaal signaal voor ESC
	_delay_ms(4000);			// wachten op het melodietje
	OCR1A = 7;


}

ISR(INT5_vect)  // knop Zuiden			
{
	KnopESC = 1;

}




void Timer0_Init(){

	cli();//stop interrupts






			  TCCR0A = 0;// hele register op 0 zetten
		          TCCR0B = 0;// ook TCCR0B

			  TCNT0  = 0;// counter waarde op 0 inittialiseren
			  OCR0A = 5; // 1/16 tijd van één toer
			  
			  // CTC mode aanzetten
			  TCCR0B |=  (1 << WGM02);
			  // //  CS00 en CS02 bits voor 1024 prescaler
			  TCCR0B |= (1 << CS02) | (1 << CS00);

			  // compare match interrupt enable
			  TIMSK0 |= (1 << OCIE0A) ;




	sei();//toestaan interrupts


}

ISR(TIMER0_COMPA_vect){			// compare match A interrupt

	PrintSegmentOK();
}



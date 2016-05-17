#define LED_STRIP_PORT PORTB
#define LED_STRIP_DDR  DDRB
#define LED_STRIP_PIN  1
#define segments 16

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Ledstrip.h"
#include "LEDfunctie.h"
#include "HeaderFiles/dwenguinoBoard.h"
#include "HeaderFiles/dwenguinoLCD.h"

char Dflt[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//NUMBERS
char Zero[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 };
char One[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 };
char Two[16] = { 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1 };
char Three[16] = { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1 };
char Four[16] = { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1 };
char Five[16] = { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 };
char Six[16] = { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1 };
char Seven[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 };
char Eight[16] = { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
char Nine[16] = { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 };

//characters
char A[16] = { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1 };
char B[16] = { 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1 };
char C[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1 };
char D[16] = { 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 };
char E[16] = { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1 };
char F[16] = { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1 };
char G[16] = { 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1 };
char H[16] = { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0 };
char I[16] = { 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1 };
char J[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0 };
char K[16] = { 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0 };
char L[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 };
char M[16] = { 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 };
char N[16] = { 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 };
char O[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 };
char P[16] = { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1 };
char Q[16] = { 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 };
char R[16] = { 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1 };
char S[16] = { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 };
char T[16] = { 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 };
char U[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0 };
char V[16] = { 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 };
char W[16] = { 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 };
char X[16] = { 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char Y[16] = { 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0 };
char Z[16] = { 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1 };

char barunder[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 };
char barmiddle[16] = { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
char barupper[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 };

char DubbleDot[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 };
int main() {
	initBoard();
	initLCD();
	backlightOn();
	clearLCD();
	Timer3_Init();
	while(1)
	{
		LCDSnelheid();
		_delay_ms(500);
	}
		//MakeCircle(A, Dflt, Dflt, Dflt, Dflt, Dflt, Dflt, Dflt, Dflt, Dflt,
			//	Dflt, Dflt, Dflt, Dflt, Dflt, Dflt);

}
char* Decode(char i);
void Stopwatch() {
// dit is een methode dat een stopwatch op de harddrive doet verschijnen
//in het totaal moeten 6 getallen worden weergegeven
// ieder getal is gelinkt aan een counter, deze zijn hieronder gedeclareerd
	char secondenE = 0; //counter dat de eenheden van de seconden bijhoudt
	char secondenT = 0; //counter dat de tientallen van de seconden bijhoudt
//de volgende counters zijn analoog opgebouwd als deze voor de seconden
	char minutenE = 0;
	char minutenT = 0;
	char urenE = 0;
	char urenT = 0;
	char AsecondenE[16];
	char AsecondenT[16];
	char AminutenE[16];
	char AminutenT[16];
	char AurenE[16];
	char AurenT[16];
	while (1) {
		char* pSecondenE = Decode(secondenE);
		char* pSecondenT = Decode(secondenT);
		char* pMinutenE = Decode(minutenE);
		char* pMinutenT = Decode(minutenT);
		char* pUrenE = Decode(urenE);
		char* pUrenT = Decode(urenT);
		for (int i = 0; i < segments; i++) {
			AsecondenE[i] = *(pSecondenE + i);
		}
		for (int i = 0; i < segments; i++) {
			AsecondenT[i] = *(pSecondenT + i);
		}
		for (int i = 0; i < segments; i++) {
			AminutenE[i] = *(pMinutenE + i);
		}
		for (int i = 0; i < segments; i++) {
			AminutenT[i] = *(pMinutenT + i);
		}
		for (int i = 0; i < segments; i++) {
			AurenE[i] = *(pUrenE + i);
		}
		for (int i = 0; i < segments; i++) {
			AurenT[i] = *(pUrenT + i);
		}
		MakeCircle(AminutenT, AminutenE, DubbleDot, AsecondenT, AsecondenE,
				Dflt, Dflt, Dflt, Dflt, Dflt, Dflt, Dflt, Dflt, AurenT, AurenE,
				DubbleDot);

	}
//when timer ticks
	secondenE++;
	if (secondenE == 10) {
		secondenE = 0;
		secondenT++;
		if (secondenT == 6) {
			secondenT = 0;
			minutenE++;
			if (minutenE == 10) {
				minutenE = 0;
				minutenT++;
				if (minutenT == 6) {
					minutenT = 0;
					urenE++;
					if (urenE == 10) {
						urenE = 0;
						urenT++;
					}
				}
			}
		}
	}

}

char* Decode(char i) {
//deze methode decodeerd een getalwaarde naar de segmenten die moeten belicht worden op de hard disk
	switch (i) {
	case 0:
		return Zero;
		break;
	case 1:
		return One;
		break;
	case 2:
		return Two;
		break;
	case 3:
		return Three;
		break;
	case 4:
		return Four;
		break;
	case 5:
		return Five;
		break;
	case 6:
		return Six;
		break;
	case 7:
		return Seven;
		break;
	case 8:
		return Eight;
		break;
	case 9:
		return Nine;
		break;
	default:
		return Dflt;
		break;
	}
}

void MakeCircle(char Array0[16], char Array1[16], char Array2[16],
		char Array3[16], char Array4[16], char Array5[16], char Array6[16],
		char Array7[16], char Array8[16], char Array9[16], char Array10[16],
		char Array11[16], char Array12[16], char Array13[16], char Array14[16],
		char Array15[16]) {
//deze methode stelt de een dataelement van het type fullcircle in om dan doorgestuurd te worden naar
//de LED strip, dus eigenlijk het genereren van een jagged array
	char jagged[16][16];
	for (int i = 0; i < 16; i++) {
		jagged[0][i] = Array0[i];
	}
	for (int i = 0; i < 16; i++) {
		jagged[1][i] = Array1[i];
	}
	for (int i = 0; i < 16; i++) {
		jagged[2][i] = Array2[i];
	}
	for (int i = 0; i < 16; i++) {
		jagged[3][i] = Array3[i];
	}
	for (int i = 0; i < 16; i++) {
		jagged[4][i] = Array4[i];
	}
	for (int i = 0; i < 16; i++) {
		jagged[5][i] = Array5[i];
	}
	for (int i = 0; i < 16; i++) {
		jagged[6][i] = Array6[i];
	}
	for (int i = 0; i < 16; i++) {
		jagged[7][i] = Array7[i];
	}
	for (int i = 0; i < 16; i++) {
		jagged[8][i] = Array8[i];
	}
	for (int i = 0; i < 16; i++) {
		jagged[9][i] = Array9[i];
	}
	for (int i = 0; i < 16; i++) {
		jagged[10][i] = Array10[i];
	}
	for (int i = 0; i < 16; i++) {
		jagged[11][i] = Array11[i];
	}
	for (int i = 0; i < 16; i++) {
		jagged[12][i] = Array12[i];
	}
	for (int i = 0; i < 16; i++) {
		jagged[13][i] = Array13[i];
	}
	for (int i = 0; i < 16; i++) {
		jagged[14][i] = Array14[i];
	}
	for (int i = 0; i < 16; i++) {
		jagged[15][i] = Array15[i];
	}
	//de jagged array wordt meteen doorgestuurd naar de LED's
	PrintCircle(jagged);
}

//void Spinningcircle() {
////deze methode genereerd een circel met een gaatje in die rond draait
//	MakeCircle(Dflt, barmiddle, barmiddle, barmiddle, barmiddle, barmiddle,
//			barmiddle, barmiddle, barmiddle, barmiddle, barmiddle, barmiddle,
//			barmiddle, barmiddle, barmiddle, barmiddle);
//	circle.array1 = Dflt;
//	circle.array0 = barmiddle;
////timer ticks
//	circle.array2 = Dflt;
//	circle.array1 = barmiddle;
////timer ticks
//	circle.array3 = Dflt;
//	circle.array2 = barmiddle;
////timer ticks
//	circle.array4 = Dflt;
//	circle.array3 = barmiddle;
////timer ticks
//	circle.array5 = Dflt;
//	circle.array4 = barmiddle;
////timer ticks
//	circle.array6 = Dflt;
//	circle.array5 = barmiddle;
////timer ticks
//	circle.array7 = Dflt;
//	circle.array6 = barmiddle;
////timer ticks
//	circle.array8 = Dflt;
//	circle.array7 = barmiddle;
////timer ticks
//	circle.array9 = Dflt;
//	circle.array8 = barmiddle;
////timer ticks
//	circle.array10 = Dflt;
//	circle.array9 = barmiddle;
////timer ticks
//	circle.array11 = Dflt;
//	circle.array10 = barmiddle;
////timer ticks
//	circle.array12 = Dflt;
//	circle.array11 = barmiddle;
////timer ticks
//	circle.array13 = Dflt;
//	circle.array12 = barmiddle;
////timer ticks
//	circle.array14 = Dflt;
//	circle.array13 = barmiddle;
////timer ticks
//	circle.array15 = Dflt;
//	circle.array14 = barmiddle;
////timer ticks
//	circle.array0 = Dflt;
//	circle.array15 = barmiddle;
//}
int tijdMotor;
void Timer1_Init(){


	DDRD |= (0 << DDD4);		// PIN for ICP1
	PORTD |= (1 << DDD4);		// Pull-Up


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



ISR(TIMER1_CAPT_vect)  // IR_Sensor triggered
{
	tijdMotor = ICR1;      // save duration of last revolution
	TCNT1 = 0;       // restart timer for next revolution
}

/*ISR(PCINT6){
	tijdMotor = ICR1;      // save duration of last revolution
	TCNT1 = 0;
}*/

ISR(TIMER1_OVF_vect)    // counter overflow/timeout
{
	tijdMotor = 0;

}

void LCDSnelheid(){

	clearLCD();
	_delay_ms(50);

	if(tijdMotor>0){

		printIntToLCD(15625/tijdMotor,1,4);

	}
	else{
		printCharToLCD(78,1,4);

	}
}


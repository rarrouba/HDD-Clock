/*
 * LEDfunctie.c
 *
 *  Created on: 26-apr.-2016
 *      Author: Mattijs
 */

#include "LEDfunctie.h"
#include "Ledstrip.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//alle tekens worden hier gedeclareerd.
//iedere positie in de array stelt een LEDsegment voor (in de bijlage vindt
//je welke positie voor welk segment staat.

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

char Send[16];

//de leds worden aangestuurd met een array van 16 variabelen van het type
//grd_color
grb_color colors[16];
// met onderstaande struct wordt een kleur gekozen
grb_color Color = { 255, 0, 0 };
//wanneer de led niet moet oplichten wordt de volgende grb_color doorgestuurd
grb_color Blank = { 0, 0, 0 };

//deze methode kan voor ieder segment 1 teken printen voor 1 toer van de schijf
//op positie 0 van de array staat het character dat op positie 0 van de schijf moet tevoorschijn komen(zie bijlage)
void PrintCircle(char characters[16]) {
	for (int omw = 0; omw < 16; omw++) {
//voor 1/16 van een omwenteling
// onder deze lijn wordt voor ieder
//-------------------------------------
		// stel dat omw=0 (zero-based) dan wordt hier onder na gegaan voor ieder segment of de led van dat segment moet branden
		// voor het eerste zestiende deel van een omwenteling
		for (int i = 0; i < 16; i++) {
			switch (characters[i]) {
			case 0:
				Send[i] = Zero[omw];
				break;
			case 1:
				Send[i] = One[omw];
				break;
			case 2:
				Send[i] = Two[omw];
				break;
			case 3:
				Send[i] = Three[omw];
				break;
			case 4:
				Send[i] = Four[omw];
				break;
			case 5:
				Send[i] = Five[omw];
				break;
			case 6:
				Send[i] = Six[omw];
				break;
			case 7:
				Send[i] = Seven[omw];
				break;
			case 8:
				Send[i] = Eight[omw];
				break;
			case 9:
				Send[i] = Nine[omw];
				break;
			default:
				Send[i] = 0;
				break;
			}
		}
		for (int i = 0; i < 16; i++) {
			if (Send[i] == 0) {
				colors[i] = Blank;
			} else {
				colors[i] = Color;
			}
		}
		led_strip_write(colors, 16);
//------------------------------------------
	}
}
void Level1() {

}

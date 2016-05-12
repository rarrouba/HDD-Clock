

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "HeaderFiles/Ledstrip.h"
#include "HeaderFiles/dwenguinoBoard.h"
#include "HeaderFiles/dwenguinoLCD.h"


#define LED_COUNT 16
grb_color colors[LED_COUNT];


int main()
{
	//IR sensor
	initBoard();
	initLCD();
	backlightOn();
	clearLCD();
	
	
	//motor
	Timer1_Motor_Init();
	Opstart_ESC();
	for (int i = 0; i < 140; i++)
    {
		OCR1A ++ ;
		_delay_ms(20);
	}
	Timer3_Init();


  unsigned int count = 0;

  while(1)
  {
	  LCDSnelheid();


  }


}

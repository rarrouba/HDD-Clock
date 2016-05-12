

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
	Timer1_Init();
	
	//motor
	INT_init();
	Timer1_Motor_Init();
	Opstart_ESC();
	for (int i = 0; i < 140; i++)
    {
		OCR1A ++ ;
		_delay_ms(20);
	}
	for (int i = 0; i < 140; i++)
    {
		OCR3A ++ ;
		_delay_ms(20);

	}
	Timer3_Init();


  unsigned int count = 0;
  grb_color colorsSet[] = {(grb_color){  0,0, 0 },(grb_color){  127,255, 0 },(grb_color){  255,255, 0 },(grb_color){  255,127, 0 }, (grb_color){  255,0, 0 },(grb_color){  255,0, 127 },(grb_color){  255,0, 255 },(grb_color){  127,0, 255 },(grb_color){ 0, 0, 255 },(grb_color){ 0, 127, 255 },(grb_color){ 0, 255, 255 },(grb_color){ 0, 255, 127 },(grb_color){  0,255, 0 },(grb_color){  127,255, 0 },(grb_color){  255,255, 0 },(grb_color){  255,127, 0 }, (grb_color){  255,0, 0 },(grb_color){  255,0, 127 },(grb_color){  255,0, 255 }};

  while(1)
  {
	  LCDSnelheid();
	  unsigned int i;
	  for(i = 0; i < LED_COUNT; i++)
	  {

		  colors[i] = colorsSet[(i+count)%LED_COUNT];
	  }

	  led_strip_write(colors, LED_COUNT);
	  count++;
	  count = (count)%LED_COUNT;
      _delay_ms(500);

  }


}

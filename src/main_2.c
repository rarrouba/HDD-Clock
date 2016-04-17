#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "HeaderFiles/dwenguinoLCD.h"
#include "HeaderFiles/dwenguinoBoard.h"

int main_2(void) {
  DDRB = 0xFF;
  DDRA = 0xFF;
  TIMSK1 = 0xFF;
  OCR1A = 255;
  TCCR1B = 0x01;
  TCNT0 = 0x00;
  SREG = 0xFF;
while (1) {
	SET_BIT_HIGH(PORTB, 0);
	PORTA = 0xFF;
    PORTB = 0x0F;
	PORTD = 0xFF;
	_delay_ms(80);

 }
}



ISR(TIMER1_OVF_vect) {
 PORTB = 0xFF;
}

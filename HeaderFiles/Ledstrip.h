/*
 * Ledstrip.h
 *
 *  Created on: 15-apr.-2016
 *      Author: Redouane
 */

//properties
#ifndef SRC_LEDSTRIP_H_
#define SRC_LEDSTRIP_H_
#define LED_STRIP_PORT PORTB
#define LED_STRIP_DDR  DDRB
#define LED_STRIP_PIN  1

// Structures
typedef struct grb_color
{
	unsigned char green,red, blue;
}grb_color;

//function(s)
void __attribute__((noinline)) led_strip_write(grb_color * colors, unsigned int count);


#endif /* SRC_LEDSTRIP_H_ */

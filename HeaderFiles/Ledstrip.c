/*
 * Ledstrip.c
 *
 *  Created on: 15-apr.-2016
 *      Author: Redouane
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Ledstrip.h"
typedef struct grb_color;


void __attribute__((noinline)) led_strip_write(grb_color * colors, unsigned int count)
{
  LED_STRIP_PORT &= ~(1<<LED_STRIP_PIN);
  LED_STRIP_DDR |= (1<<LED_STRIP_PIN);

  cli();
  while(count--)
  {

    asm volatile(

        "ld __tmp_reg__, %a0+\n"
        "rcall send_led_strip_byte%=\n"  // groen
    	"ld __tmp_reg__, %a0+\n"

        "rcall send_led_strip_byte%=\n"  // rood
        "ld __tmp_reg__, %a0+\n"

    	"rcall send_led_strip_byte%=\n"  // blauw
        "rjmp led_strip_asm_end%=\n"

        "send_led_strip_byte%=:\n"
        "rcall send_led_strip_bit%=\n"  // (bit 7).
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"
        "rcall send_led_strip_bit%=\n"  // (bit 0).
        "ret\n"


        "send_led_strip_bit%=:\n"

        "sbi %2, %3\n"                           // Drive the line high.


        "rol __tmp_reg__\n"                      // Rotate left through carry.



        "nop\n" "nop\n"


        "brcs .+2\n" "cbi %2, %3\n"              // If the bit to send is 0, drive the line low now.



        "nop\n" 								//"nop\n" "nop\n" "nop\n" "nop\n"


        "brcc .+2\n" "cbi %2, %3\n"              // If the bit to send is 1, drive the line low now.

        "ret\n"
        "led_strip_asm_end%=: "
        : "=b" (colors)
        : "0" (colors),
          "I" (_SFR_IO_ADDR(LED_STRIP_PORT)),
          "I" (LED_STRIP_PIN)
    );


  }
  sei();
  _delay_us(15);
}

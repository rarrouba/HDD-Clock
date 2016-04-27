
#define LED_STRIP_PORT PORTB
#define LED_STRIP_DDR  DDRB
#define LED_STRIP_PIN  1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


typedef struct grb_color
{
  unsigned char green,red, blue;
} grb_color;


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

#define LED_COUNT 16
grb_color colors[LED_COUNT];


int main()
{
	
	
  Timer1_Init();
  for (int i = 0; i < 150; i++)
	{
		OCR1A ++ ;
		_delay_ms(20);

	}

  unsigned int count = 0;
  grb_color colorsSet[] = {(grb_color){  0,0, 0 },(grb_color){  127,255, 0 },(grb_color){  255,255, 0 },(grb_color){  255,127, 0 }, (grb_color){  255,0, 0 },(grb_color){  255,0, 127 },(grb_color){  255,0, 255 },(grb_color){  127,0, 255 },(grb_color){ 0, 0, 255 },(grb_color){ 0, 127, 255 },(grb_color){ 0, 255, 255 },(grb_color){ 0, 255, 127 },(grb_color){  0,255, 0 },(grb_color){  127,255, 0 },(grb_color){  255,255, 0 },(grb_color){  255,127, 0 }, (grb_color){  255,0, 0 },(grb_color){  255,0, 127 },(grb_color){  255,0, 255 }};

  while(1)
  {
	  unsigned int i;
	  for(i = 0; i < LED_COUNT; i++)
	  {

		  colors[i] = colorsSet[(i+count)%LED_COUNT];
	  }

	  led_strip_write(colors, LED_COUNT);
	  count++;
	  count = (count)%LED_COUNT;
      _delay_ms(50);

  }
}

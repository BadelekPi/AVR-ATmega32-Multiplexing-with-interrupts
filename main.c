#include <avr/io.h>
#include <avr/interrupt.h>
#include "d_led.h"



int main(void)
{
    d_led_init();
	cy1=1;
	cy2=4;
	cy3=9;
	cy4=5;
	
	sei();
    while (1) 
    {
		
    }
}

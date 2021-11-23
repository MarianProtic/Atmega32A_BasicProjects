#include "Timer.h"
#include "button.h"
#include "afisare.h"
#include "os.h"

#include<avr/io.h>
#include<stdint.h>
#include <avr/interrupt.h>



int main (void)
{

	sei();
	InitializarePorturiAfisareDigiti();
	OsInit();
	OsStart();
	while(1)
	{
//		if((PINA & (1<<PINA0))==0)
//		{
//			PORTD ^= 0xFF;
//		}
	}
	return 0;
}

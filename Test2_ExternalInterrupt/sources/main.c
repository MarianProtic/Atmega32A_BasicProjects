#include<avr/io.h>
#include<stdint.h>
#include <avr/interrupt.h>

int ValoarePort = 0x01;


void InitInt0(void)
{
	GICR |= (1<<INT0); //External Interrupt Request 0 Enable
	MCUCR |= (1<<ISC00) | (1<<ISC01); //The rising edge of INT0 generates an interrupt request
}


ISR(INT0_vect) //SREG_I
{


			if(ValoarePort == 0xFF);
			else
				ValoarePort = ((ValoarePort * 2) + 1);
			PORTC =~ ValoarePort;
}

void InitInt1(void)
{
	GICR |= (1<<INT1);
	MCUCR |= (1<<ISC11) | (1<<ISC10);
}

ISR(INT1_vect)
{
			ValoarePort = ((ValoarePort - 1) / 2);
			if(ValoarePort == 0xFF)
				ValoarePort = 0xFF;
			PORTC =~ ValoarePort;
}



int main (void)
{
	/* Initialization code */
	DDRD = 0x00;
	PORTD = 0xFF;

	DDRC= 0xFF;
	PORTC = 0xFF;



	InitInt0();
	InitInt1();
	sei();
	while(1)
	{
		/* Nothing to do */
	}
	return 0;
}


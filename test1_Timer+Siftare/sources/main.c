#include<avr/io.h>
#include<stdint.h>
#include <avr/interrupt.h>


    int Incrementare = 0;
    int Decrementare = 1;
    int TipSiftare = 4;
    int ValoarePort = 0x01;
void InitTimer0(void)
{
	TCCR0 |= (1<<CS02) | (1<<CS00); //prescale 1024
	TIMSK |= (1<<TOIE0);
	TCNT0 = 99;
}

void InitTimer1(void)
{
	TCCR1A = 0x00;
	TCCR1B |= (1<<CS12); //prescaler 256
	TIMSK |= (1<<TOIE1);
	//TCNT1L = 0x9E;
	//TCNT1H = 0x58; //65536-25000 = 40536
	//PORTC=0xFF;
}

ISR(TIMER1_OVF_vect)
{
	TCNT1 = 34000;

	if(ValoarePort == 0x01)
		TipSiftare = Decrementare;

	if(ValoarePort == 0x80)
		TipSiftare = Incrementare;

	if(TipSiftare == Incrementare)
		ValoarePort = ValoarePort>>1;

	if(TipSiftare == Decrementare)
		ValoarePort = ValoarePort<<1;

	PORTC =~ ValoarePort;

	//PORTC =~ PORTC;
}

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 99;
	PORTB = ~PORTB;
}


int main (void)
{
	/* Initialization code */
	DDRB=0xFF; //iesire
	PORTB = 0xFF;

	DDRC = 0xFF;
	PORTC = 0xFF;


	sei();
    InitTimer0();
    InitTimer1();



	while(1)
	{

		/* Nothing to do */
	}
	return 0;
}


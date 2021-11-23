#include<avr/io.h>
#include<stdint.h>
#include <avr/interrupt.h>



int index = 0;
int IndexSec = 0;
int IndexZecSec = 0;
int FlagDouazeciMS = 0;
int IndexMiliSec = 0;
int IndexZecMiliSec = 0;
uint16_t cifra[10] = { 0x81, 0xCF, 0x92, 0x86, 0xCC, 0xA4, 0xA0, 0x8F, 0x80, 0x84 }; //0,1,2,3,4,5,6,7,8,9
uint16_t digit[4] = { 0xFE, 0xFD, 0xFB, 0xF7};//pin0,pin1,pin2,pin3


void InitTimer1(void)
{
	TCCR1B |=  (1<<CS12); //prescaler 256
	TIMSK |= (1<<TOIE1); //overflow enable
	TCNT1 = 3000; //1s
}
void InitTimer0(void)
{
	TCCR0 |= (1<<CS02); //prescaler 256
	TIMSK |= (1<<TOIE0); //overflow enable
	TCNT0 = 131; // 2 ms
}
ISR(TIMER0_OVF_vect) //2 ms
{

	PORTC = digit[index];



	if(index == 0)
		PORTB = cifra[IndexZecSec];
	if(index == 1)
		PORTB = cifra[IndexSec];
	if(index == 2)
		PORTB = cifra[IndexZecMiliSec];
	if(index == 3)
		PORTB = cifra[IndexMiliSec];


	index++;

	if(index == 4)
		index = 0;


	FlagDouazeciMS++; //2 ms
	if(FlagDouazeciMS == 10) //20 ms
	{
		FlagDouazeciMS = 0;
		IndexMiliSec = IndexMiliSec+2;
		if(IndexMiliSec == 10)
			{
				IndexMiliSec = 0;
				IndexZecMiliSec = IndexZecMiliSec+2;
				if(IndexZecMiliSec == 10)
					IndexZecMiliSec = 0;
			}
	}


}
ISR(TIMER1_OVF_vect) //1s
{
	IndexSec++;
	if(IndexSec == 10)
	{
		IndexSec = 0;
		IndexZecSec++;
		if(IndexZecSec == 6)
			IndexZecSec = 0;
	}

}

int main (void)
{
	/* Initialization code */
	DDRC = 0xFF;
	PORTC = 0xFF;

	DDRB = 0xFF;
	PORTB = 0xFF;

	InitTimer1();
	InitTimer0();
	sei();
	while(1)
	{
		/* Nothing to do */
	}
	return 0;
}


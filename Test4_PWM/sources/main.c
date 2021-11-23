#include<avr/io.h>
#include<stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int StareButon1 = 0;
int StareButon2 = 0;

void InitInterrupExtern0()
{
	GICR |= (1<<INT0); 					//External Interrupt Request 0 Enable
	MCUCR |= (1<<ISC00) | (1<<ISC01); 	//Intrerupere activa pe rising
}
void InitTimer0()
{
	GICR |= (1<<INT0); 							//External Interrupt Request 0 Enable
	TCNT0 = 100;									// 100 - 256 --> 10ms
	TIMSK |= (1<<TOIE0); 							//Overflow Interrupt Enable
	TCCR0 |= (1<<CS02) | (1<<CS00); 				//prescaler 1024
}
void InitInterrupExtern1()
{
	GICR |= (1<<INT1);
	MCUCR |= (1<<ISC10) | (1<<ISC11);

}

void InitPWM()
{
	OCR0 = 115;							//set PWM "1"
	TCCR0 |= (1<<WGM01) | (1<<WGM00);				//Enable Fast PWM
	TCCR0 |= (1<<COM01) | (1<<COM00); 				//SET OC0 on Compare Match
	TCCR0 |= (1<<CS02) | (1<<CS00); 				//prescaler 1024
}

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 100;
	if(OCR0 < TCNT0)
		OCR0 = TCNT0 + 10;
	if(OCR0 > 255)
		OCR0 = 255 - 10;
}

ISR(INT0_vect) //SREG_I
{
	OCR0 = OCR0 + 10;
}
ISR(INT1_vect)
{
	OCR0 = OCR0 - 10;
}
int main (void)
{
	/* Initialization code */
	cli();

	DDRB = 0xFF; //DDRB |= 0b00010000; //Pin PB3 iesire
	PORTB = 0x00;

	DDRD = 0x00;
	PORTD = 0xFF;

	InitTimer0();
	InitPWM();
	InitInterrupExtern0();
	InitInterrupExtern1();

	sei();

	while(1)
	{
		/* Nothing to do */
	}
	return 0;
}


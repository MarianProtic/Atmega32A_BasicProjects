#include<avr/io.h>
#include<stdint.h>
#include <avr/interrupt.h>

void InitTimer0(void)
{
	TCCR0 |= (1<<CS02) | (1<<CS00); //prescale 1024
	TIMSK |= (1<<TOIE0);
	TCNT0 = 99;
}

ISR(TIMER0_OVF_vect)
{
	PORTC = 0xFF;
}
int InitADC(void)
{
	ADMUX |= (1<<REFS0); //Vref = Avcc
	ADMUX |= (1<<MUX0); //ADC input --> ADC1
	ADCSRA |= (1<<ADEN); //enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //prescaler 128
}

int ReadADC(int ch)
{
	ch = ch&0b00000111;
	ADMUX |= ch;

	ADCSRA |= (1<<ADSC); //single conversion
	while(!(ADCSRA & (1<<ADIF)));//waiting for ADIF, conversion complete
	ADCSRA|=(1<<ADIF); // clearing of ADIF, it is done by writing 1 to it
	return(ADC);
}

/*int LED()
{
	if(ADC >= 256)
	{
		PORTC &= 0x01;
		if(ADC >= 512)
		{
			PORTC &= 3;
			if(PORTC >= 768)
			{
				PORTC &= 7;
			}
		}
	}

}*/
int main (void)
{
	/* Initialization code */
	DDRA = 0x00;
	PORTA = 0xFF;

	DDRB = 0x00;
	PORTB = 0xFF;

	DDRC = 0xFF;
	PORTC = 0xFF;

	//int ValoareADC;
	InitADC();
	InitTimer0();
	sei();
	while(1)
	{
		/* Nothing to do */

		//LED(ADC);
		ReadADC(0);
			if(ADC > 768)
				PORTC = 0b11111100;
			if(ADC > 512 && ADC <= 768)
				PORTC = 0b11110011;
			if(ADC > 256 && ADC <= 512)
				PORTC = 0b11001111;
			if( ADC <= 256)
				PORTC = 0b00111111;


	}
	return 0;
}


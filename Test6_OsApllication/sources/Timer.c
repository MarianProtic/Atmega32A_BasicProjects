

#include<Timer.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include<stdint.h>



void timer1_init()
{
	TCNT1 = 0;
	TCCR1A = 0x00;
	/* Set Timer 1 for 16us resolution equivalent to 256 prescaler value */
	TCCR1B = 0x04;
}

//void InitTimer1(void)
//{
//	TCCR1B |=  (1<<CS12); //prescaler 256
//	TIMSK |= (1<<TOIE1); //overflow enable
//	TCNT1 = 3000; //1s
//}
void InitTimer0(void)
{
	TCCR0 |= (1<<CS02); //prescaler 256
	TIMSK |= (1<<TOIE0); //overflow enable
	TCNT0 = 131; // 2 ms
}
ISR(TIMER0_OVF_vect) //2 ms
{

}
ISR(TIMER1_OVF_vect) //1s
{

}

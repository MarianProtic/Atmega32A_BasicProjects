/*
 * afisare.c
 *
 *  Created on: Aug 23, 2019
 *      Author: uic25511
 */
#include<avr/io.h>
#include<stdint.h>
#include "ceas.h"
#include "button.h"

void AfisareSecunde (void)
{
	if(index1 == 0)
		PORTB = cifra[IndexZecSec];
	if(index1 == 1)
	{
		PORTB = cifra[IndexSec];
		PORTB = (PORTB & 0x7F);
	}
	if(index1 == 2)
		PORTB = cifra[IndexZecMiliSec];
	if(index1 == 3)
		PORTB = cifra[IndexMiliSec];
}

	void AfisareOra(void)
	{
		if(index1 == 0)
			PORTB = cifra[IndexZecOre];
		if(index1 == 1)
		{
			PORTB = cifra[IndexOre];
			PORTB = PORTB & 0x7F;
		}

		if(index1 == 2)
			PORTB = cifra[IndexZecMinute];
		if(index1 == 3)
			PORTB = cifra[IndexMinute];
	}

void AfisareDigiti (void)
{

	PORTB = 0xFF;
	PORTC = digit[index1];

	check_buttons();
	press_button();


	if (flag == 0)
	{
		AfisareSecunde();
	}
	else
	{
		AfisareOra();
	}
	index1++;
	if(index1 == 4)
		index1 = 0;
}



void InitializarePorturiAfisareDigiti(void)
{
	DDRC = 0xFF;
	PORTC = 0xFF;

	DDRB = 0xFF;
	PORTB = 0xFF;

	DDRD = 0x00;
	PORTD = 0xFF;

	DDRA = 0xFF;
	PORTA = 0xFF;
}

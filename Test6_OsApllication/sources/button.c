/*
 * button.c
 *
 *  Created on: Aug 23, 2019
 *      Author: uic25511
 */
#include "button.h"
#include "afisare.h"
#include <avr/interrupt.h>
#include <avr/io.h>

int flag = 0;
volatile uint8_t button_down[8];
volatile uint8_t button_state[8];
volatile uint8_t debounce_counter[8];



void check_buttons(void)
{
	for (uint8_t pin = 0; pin < 8; pin++)
	{
		// citim valoarea pinul
		uint8_t pin_current_state = (~PIND >> pin) & 1;

		// butonul trece intr-o noua stare
		if (pin_current_state != button_state[pin])
		{
			// incrementam counterul
			debounce_counter[pin]++;

			// butonul se afla in noua stare de 4 verificari
			if (debounce_counter[pin] > 4)
			{
				// schimbam starea butonului
				button_state[pin] = pin_current_state;

				// daca butonul a fost apasat activam evenimentul
				if (button_state[pin] == PRESSED)
				{
					button_down[pin] = PRESSED;
				}
			}
		}
		else
		{
			// daca butonul este in aceeasi stare resetam counterul
			debounce_counter[pin] = 0;
		}
	}
}

uint8_t is_button_pressed(uint8_t btn)
{
	if (button_down[btn] == PRESSED)
	{
		button_down[btn] = RELEASED;
		return PRESSED;
	}
	else
	{
		return RELEASED;
	}
}
void press_button(void)
{
    if(is_button_pressed(BUTTON1))
	{
    	//AfisareSecunde();
    	flag=0;
	}
    if(is_button_pressed(BUTTON2))
  	{
    	//AfisareOra();
    	flag=1;
  	}
}

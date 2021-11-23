

#ifndef INCLUDES_BUTTON_H_
#define INCLUDES_BUTTON_H_

#include<avr/io.h>


#define BUTTON1		0
#define BUTTON2 	1
#define BUTTON3 	2

#define PRESSED			0x01
#define RELEASED		0x00

//extern volatile uint16_t counter;

//extern uint8_t is_button_pressed(uint8_t btn);
extern void check_buttons();
extern void press_button();
extern int flag;



#endif /* INCLUDES_BUTTON_H_ */

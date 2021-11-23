#include"os.h"
#include"Timer.h"
#include "button.h"
#include "ceas.h"
#include "afisare.h"

#include<avr/io.h>
#include <stdint.h>
#include<avr/interrupt.h>


Task Tasks[OS_NUMBER_OF_TASKS];

void Task1ms(void);
void Task10ms(void);
void Task100ms(void);
void Task1000ms(void);

static void OsConfigureTask(uint8_t TaskNo, uint16_t period, void *ptrtfunc, uint16_t offset)
{
	Tasks[TaskNo].function=ptrtfunc;
	Tasks[TaskNo].period=period;
	Tasks[TaskNo].offset=offset;
	Tasks[TaskNo].last_tick=0;
	Tasks[TaskNo].state=OS_TASK_SUSPENDED;
}

void OsInit(void)
{
	OsConfigureTask(OS_TASK_1MS,OS_MS_TO_TICKS(1),&Task1ms,0);
	OsConfigureTask(OS_TASK_10MS,OS_MS_TO_TICKS(10),&Task10ms,19);
	OsConfigureTask(OS_TASK_100MS,OS_MS_TO_TICKS(100),&Task100ms,37);
	OsConfigureTask(OS_TASK_1000MS,OS_MS_TO_TICKS(1000),&Task1000ms,56);
}

void OsStart(void)
{
	uint8_t TaskIndex;
	timer1_init();
	sei();
	while(1)
	{
		for(TaskIndex=0; TaskIndex<OS_NUMBER_OF_TASKS; TaskIndex++)
		{
			if(Tasks[TaskIndex].state == OS_TASK_SUSPENDED)
			{
				if(Tasks[TaskIndex].offset<=TCNT1)
				{
					Tasks[TaskIndex].last_tick = TCNT1;
					Tasks[TaskIndex].state = OS_TASK_READY;
				}
			}
			else
			{
				if((TCNT1 - Tasks[TaskIndex].last_tick) >= Tasks[TaskIndex].period)
				{
					Tasks[TaskIndex].last_tick = TCNT1;
					Tasks[TaskIndex].function();
				}
			}
		}
	}
}

void Task1ms(void)
{

	IncrementareMiliSec();
	AfisareDigiti();
	//PORTD = 0x00;

}

void Task10ms(void)
{

	//PORTD ^= 0xFF;
}

void Task100ms(void)
{
	//PORTD ^= 0xFF;
}

void Task1000ms(void)
{

	IncrementareSecunde();

	//PORTD ^= 0xFF;
	//PORTA ^= 0xFF;
}

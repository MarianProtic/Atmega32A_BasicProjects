/*
 * ceas.c
 *
 *  Created on: Aug 23, 2019
 *      Author: uic25511
 */
//#include"ceas.h"
#include "afisare.h"
#include<stdint.h>
int index1 = 0;
int IndexMiliSec = 0;
int IndexZecMiliSec = 0;
int IndexSec = 0;
int IndexZecSec = 0;
int IndexMinute = 0;
int IndexZecMinute = 0;
int IndexOre = 0;
int IndexZecOre = 0;

int IndexSecPentruMinute = 0;


int cifra[10] = { 0x81, 0xCF, 0x92, 0x86, 0xCC, 0xA4, 0xA0, 0x8F, 0x80, 0x84 }; //0,1,2,3,4,5,6,7,8,9
int digit[4] = { 0xFE, 0xFD, 0xFB, 0xF7};//pin0,pin1,pin2,pin3
int FlagDouazeciMS = 0;


void IndexMinPentruOre(void)
{
	IndexOre++;
	if(IndexOre == 10)
	{
		IndexOre = 0;
		IndexZecOre++;

	}
	if((IndexOre == 4) && (IndexZecOre == 2))
	{
		IndexOre = 0;
		IndexZecOre = 0;
	}
}

void IncrementareOreSiMinute(void)
{
	IndexSecPentruMinute = 0;
	IndexMinute++;
	if(IndexMinute == 10)
	{
		IndexZecMinute++;
		IndexMinute = 0;
	}
	if(IndexZecMinute == 6)
	{
		IndexZecMinute = 0;
		IndexMinPentruOre();
	}

}

void IncrementareSecunde(void)
{
	IndexSec++;
	IndexSecPentruMinute++;
	if(IndexSecPentruMinute == 60)
		IncrementareOreSiMinute();
	if(IndexSec == 10)
	{
		IndexSec = 0;
		IndexZecSec++;
		if(IndexZecSec == 6)
			IndexZecSec = 0;
	}
}


 void IncrementareMiliSec(void)
 {
		FlagDouazeciMS++;
		if(FlagDouazeciMS == 20)
		{
			IndexMiliSec = IndexMiliSec+2;
			if(IndexMiliSec == 10)
			{
				IndexMiliSec = 0;
				IndexZecMiliSec++;
				if(IndexZecMiliSec == 10)
					IndexZecMiliSec = 0;
			}
			AfisareDigiti();
			FlagDouazeciMS = 0;
		}

 }

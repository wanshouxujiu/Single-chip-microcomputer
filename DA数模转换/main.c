#include <REGX52.H>
#include "Timer.h"
#include "Nixie.h"
#include "another.h"

sbit DA = P2^1;

unsigned char num1,num2;
unsigned char i;

void DA_PWM()
{
	if(num1 <= num2)
	{
		DA = 1;
	}
	else
	{
		DA = 0;
	}
	if(num1 == 50)
	{
		num1 = 0;
	}
}

void main()
{
	Timer0_Init();
	
	while(1)
	{
		for(i = 0; i < 100; i++)
		{
			num2 = i;
			Delay(10);
		}
		for(i = 100; i > 0; i--)
		{
			num2 = i;
			Delay(10);
		}
	}
}

void Timer0_Routine() interrupt 1
{
	TH0 = 0xFF;
	TL0 = 0xA4;
	num1++;
	DA_PWM();
}
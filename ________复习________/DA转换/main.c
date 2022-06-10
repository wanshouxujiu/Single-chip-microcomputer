#include <REGX52.H>
#include "Timer0.h"
#include "Delay.h"

sbit DAC_PWM = P2^1;      //DA转换这里还是用PWM，只不过多了个滤波电容

unsigned char Num, HighNum, Limit = 50;

void LED_PWM()
{
	Num++;
	if(Num <= HighNum)
	{
		DAC_PWM = 0;
	}
	else
	{
		DAC_PWM = 1;
		if(Num > Limit)
		{
			Num = 0;
		}
	}
}

void main()
{
	Timer0_Init();
	
	while(1)
	{
		while(HighNum < 50)
		{
			HighNum++;
			Delay(10);
		}
		while(HighNum > 0)
		{
			HighNum--;
			Delay(10);
		}
	}
}

void Timer0_Rountine () interrupt 1
{
	TH0 = 65500 / 256;      //频率调高一点
	TL0 = 65500 % 256;
	LED_PWM();
}
#include <REGX52.H>
#include "Timer.h"
#include "Nixie.h"
#include "another.h"

sbit Motor = P1^0;

unsigned char num1,num2,Keynum,Speed;

void Motor_PWM()
{
	if(num1 <= num2)
	{
		Motor = 1;        //由电路图得知，输出1电机通电
	}
	else
	{
		Motor = 0;
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
		Keynum = key();
		if(Keynum == 1)
		{
			Speed++;
			Speed %= 4;
			if(Speed == 0){num2 = 0;}
			if(Speed == 1){num2 = 20;}
			if(Speed == 2){num2 = 35;}
			if(Speed == 3){num2 = 50;}
		}
		Nixie(1,Speed);
	}
}

void Timer0_Routine() interrupt 1
{
	TH0 = 0xFF;
	TL0 = 0xA4;
	num1++;
	Motor_PWM();
}
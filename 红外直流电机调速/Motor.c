#include <REGX52.H>
#include "Timer1.h"

sbit Motor = P1^0;

unsigned char num1,num2;

void Motor_Init()
{
	Timer1_Init();
}

void Motor_SetSpeed(unsigned char Speed)
{
	num2 = Speed;
}

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

void Timer1_Routine() interrupt 3
{
	TH1 = 0xFF;
	TL1 = 0xA4;
	num1++;
	Motor_PWM();
}
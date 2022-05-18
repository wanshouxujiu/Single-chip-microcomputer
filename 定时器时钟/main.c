#include <REGX52.H>
#include "Timer.h"
#include "LCD1602.h"
#include "another.h"

//unsigned char Sec=0, Min=0, Hour=0;
//Sec = Min = Hour = 0; 这个编译器不支持这样写
void main()
{
	unsigned char Sec=0, Min=0, Hour=0;
	Timer0_Init();
	LCD_Init();
	LCD_ShowString(1,1,"Clock:");
	LCD_ShowString(2,1,"  :  :");
	while(1)
	{
		LCD_ShowNum(2,1,Hour,2);
		LCD_ShowNum(2,4,Min,2);
		LCD_ShowNum(2,7,Sec,2);
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0count = 0;
	TH0 = 64535 / 256;
	TL0 = 64535 % 256 + 1;
	T0count++;
	if(T0count >= 1000)
	{
		T0count = 0;
		Sec++;
		if(Sec == 60)
		{
			Sec = 0;
			Min++;
			if(Min == 60)
			{
				Min = 0;
				Hour++;
				if(Hour == 24)Hour = 0;
			}
		}
	}
}
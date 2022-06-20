#include <REGX52.H>
#include "DS18B20.h"
#include "LCD1602.h"
#include "Delay.h"

float T;

void main()
{
	LCD_Init();
	DS18B20_ConvertT();
	Delay(1000);
	while(1)
	{
		DS18B20_ConvertT();
		T = DS18B20_ReadT();
		if(T < 0)
		{
			LCD_ShowChar(1,1,'-');
			T = -T;
		}
		else
		{
			LCD_ShowChar(1,1,'+');
		}
		LCD_ShowNum(1,2,T,3);
		LCD_ShowChar(1,5,'.');
		LCD_ShowNum(1,6,(unsigned long)(T*10000)%10000,4);
	}
}
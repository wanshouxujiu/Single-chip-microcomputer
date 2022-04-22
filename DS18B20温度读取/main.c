#include <REGX52.H>
#include "LCD1602.h"
#include "DS18B20.h"
#include "another.h"

float T;

void main()
{
	LCD_Init();
	DS18B20_ConvertT();    //先进行一次转换，否则显示上次的温度
	Delay(1000);           //转换需要时间，精度越高，时间越长
	LCD_ShowString(1,1,"Temperature:");
	while(1)
	{
		DS18B20_ConvertT();
		T = DS18B20_ReadT();
		if(T<0)
		{
			LCD_ShowChar(2,1,'-');    //LCD函数无法显示float
			T = -T;
		}
		else
		{
			LCD_ShowChar(2,1,'+');
		}
		LCD_ShowNum(2,2,T,3);    //小数自动截掉
		LCD_ShowChar(2,5,'.');
		LCD_ShowNum(2,6,(unsigned long)(T*10000)%10000,4);
	}
}
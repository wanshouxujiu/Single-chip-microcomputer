#include <REGX52.H>
#include "DS18B20.h"
#include "LCD1602.h"
#include "Delay.h"
#include "AT24C02.h"
#include "Key.h"
#include "Timer0.h"


unsigned char KeyNum,ChoiceTem;
unsigned char Tem_H,Tem_L;
float T;

void main()
{
	Tem_H = AT24C02_ReadByte(0);
	Tem_L = AT24C02_ReadByte(1);
	LCD_Init();
	Timer0_Init();
	DS18B20_ConvertT();
	Delay(1000);
	
	LCD_ShowString(2,1,"H:   L:   ");
	
	while(1)
	{
		KeyNum = Key();
		DS18B20_ConvertT();
		T = DS18B20_ReadT();
		
		//温度报警
		if(KeyNum)
		{
			if(KeyNum == 1)
			{
				if(ChoiceTem == 0)
				{
					Tem_H++;
				}
				else
				{
					if(Tem_L < Tem_H)
					{
						Tem_L++;
					}
				}
			}
			if(KeyNum == 2)
			{
				if(ChoiceTem == 0)
				{
					if(Tem_H > Tem_L)
					{
						Tem_H--;
					}
				}
				else
				{
					Tem_L--;
				}
			}
			if(KeyNum == 3)
			{
				ChoiceTem++;
				ChoiceTem %= 2;
			}
			if(KeyNum == 4)
			{
				AT24C02_WriteByte(0,Tem_H);
				Delay(5);                      //写入时间
				AT24C02_WriteByte(1,Tem_L);
				Delay(5);
			}
		}
		if(T > Tem_H)
		{
			LCD_ShowString(2,13,"OV:H");
		}
		else if(T < Tem_L)
		{
			LCD_ShowString(2,13,"OV:L");
		}
		else
		{
			LCD_ShowString(2,13,"    ");
		}
		//温度显示
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
		LCD_ShowNum(2,3,Tem_H,2);
		LCD_ShowNum(2,8,Tem_L,2);
	}
}

void Timer0_Rountine () interrupt 1
{
	static unsigned char Count = 0;
	TH0 = 64613 / 256;   //1ms(11.0592M)
	TL0 = 64613 % 256;
	Count++;
	if(Count == 20)
	{
		Count = 0;
		Key_Timer0();
	}
}
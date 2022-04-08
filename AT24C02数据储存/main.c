#include <REGX52.H>
#include "LCD1602.h"
#include "another.h"
#include "AT24C02.h"

unsigned char Data, KeyNum;
unsigned int Num;

void main()
{
	LCD_Init();
	LCD_ShowNum(1,1,Num,5);
	while(1)
	{
		KeyNum = key();
		if(KeyNum == 1)
		{
			Num++;
			LCD_ShowNum(1,1,Num,5);
		}
		if(KeyNum == 2)
		{
			Num--;
			LCD_ShowNum(1,1,Num,5);
		}
		if(KeyNum == 3)
		{
			AT24C02_WriteByte(0,Num%256); //地址0~255都可以
			Delay(5);                     //芯片电气特性有说明，写入时间最长5ms
			AT24C02_WriteByte(1,Num/256);
			Delay(5);
			LCD_ShowString(2,1,"Write OK");
			Delay(1000);
			LCD_ShowString(2,1,"        ");
		}
		if(KeyNum == 4)
		{
			Num = AT24C02_ReadByte(0);
			Num |= AT24C02_ReadByte(1)<<8;
			LCD_ShowNum(1,1,Num,5);
			LCD_ShowString(2,1,"Read OK");
			Delay(1000);
			LCD_ShowString(2,1,"       ");
		}
	}
}
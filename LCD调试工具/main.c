#include <REGX52.H>
#include "LCD1602.H"
#include "MatrixKey.h"

	void Delay(unsigned int xms)		//@12.000MHz
{
	while(xms--)
	{
		unsigned char i, j;

		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}

void main()
{
//	LCD_INit();
//	LCD_ShowChar(1,1,'a');
//	LCD_ShowString(1,3,"Hello");
//	LCD_ShowNum(1,9,123,3);
//	LCD_ShowSignedNum(1,13,-66,2);
//	LCD_ShowHexNum(2,1,0xA8,2);
//	LCD_ShowBinNum(2,4,0xAA,8);
	int num1 = 0;
	LCD_INit();
	while(1)
	{
		Delay(1000);
		num1++;
		LCD_ShowNum(1,1,num1,3);
	}
}
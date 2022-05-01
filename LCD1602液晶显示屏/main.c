#include <REGX52.H>
#include <LCD1602.H>
#include <intrins.H>

void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 129;
	k = 119;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void main()
{
	LCD_Init();
	LCD_ShowChar(1,1,'A');
	LCD_ShowString(1,3,"Hello");
	LCD_ShowNum(1,9,66,2);
	LCD_ShowSignedNum(1,12,-88,2);
	LCD_ShowHexNum(2,1,0xA5,2);
	LCD_ShowBinNum(2,4,165,8);
	LCD_ShowChar(2,13,0xDF);
	LCD_ShowChar(2,14,'C');
	LCD_ShowString(1,3,"Welcom to China");
	while(1)
	{
		Delay500ms();
		LCD_WriteCommand(0x18);
	}
}
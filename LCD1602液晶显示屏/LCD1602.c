#include <REGX52.H>
#include <intrins.H>

sbit LCD_RS = P2^6;
sbit LCD_RW = P2^5;
sbit LCD_E = P2^7;
#define LCD_DataPort P0

void LCD_Delay()		//@11.0592MHz   1ms
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void LCD_WriteCommand(unsigned char commend)
{
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_DataPort = commend;
	LCD_E = 1;
	LCD_Delay();            //写入需要时间
	LCD_E = 0;
	LCD_Delay();
}

void LCD_WriteData(unsigned char Data)
{
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_DataPort = Data;
	LCD_E = 1;
	LCD_Delay();
	LCD_E = 0;
	LCD_Delay();
}

void LCD_Init()
{
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x0C);
	LCD_WriteCommand(0x06);  //写入一个数据光标自动加1
	LCD_WriteCommand(0x01);
}

void LCD_SetCursor(unsigned char Line,Column)
{
	if(Line == 1)
	{
		LCD_WriteCommand((Column-1) | 0x80);   //地址高位为0，但固定为1
	}
	else
	{
		LCD_WriteCommand((Column-1+0x40) | 0x80);
	}
}

void LCD_ShowChar(unsigned char Line,Column,Char)
{
	LCD_SetCursor(Line,Column);
	LCD_WriteData(Char);
}

void LCD_ShowString(unsigned char Line,Column,unsigned char* String)
{
	unsigned char i = 0;
	
	LCD_SetCursor(Line,Column);
	for(i = 0; String[i] != '\0'; i++)
	{
		LCD_WriteData(String[i]);
	}
}

int LCD_Pow(int X, int Y)  //次方
{
	unsigned char i = 0;
	int Result = 1;
	for(i = 0; i < Y; i++)
	{
		Result *= X;
	}
	return Result;
}

void LCD_ShowNum(unsigned char Line,Column,unsigned int Number,unsigned char Lenth)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i = Lenth; i > 0; i--)
	{
		LCD_WriteData('0'+Number/LCD_Pow(10,i-1)%10);  //把每一位剥为字符显示
	}
}

void LCD_ShowSignedNum(unsigned char Line,Column,int Number,unsigned char Lenth)
{
	unsigned char i = 0;
	unsigned int Number1 = 0;
	LCD_SetCursor(Line,Column);
	if(Number >= 0)
	{
		LCD_WriteData('+');
		Number1 = Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1 = -Number;
	}
	for(i = Lenth; i > 0; i--)
	{
		LCD_WriteData('0'+Number1/LCD_Pow(10,i-1)%10);
	}
}

void LCD_ShowHexNum(unsigned char Line,Column,unsigned int Number,unsigned char Lenth)
{
	unsigned char i = 0;
	unsigned char HNum = 0;
	LCD_SetCursor(Line,Column);
	for(i = Lenth; i > 0; i--)
	{
		HNum = Number/LCD_Pow(16,i-1)%16;
		if(HNum < 10)
		{
			LCD_WriteData('0'+HNum);
		}
		else
		{
			LCD_WriteData('A' + HNum - 10);
		}
	}
}

void LCD_ShowBinNum(unsigned char Line,Column,unsigned int Number,unsigned char Lenth)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i = Lenth; i > 0; i--)
	{
		LCD_WriteData('0'+Number/LCD_Pow(2,i-1)%2);
	}
}
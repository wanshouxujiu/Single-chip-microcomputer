#include <REGX52.H>
#include "Delay.h"

sbit RCK = P3^5;    //RCLk
sbit SCK = P3^6;    //SRCLK
sbit SER = P3^4;    //SER

void MatrixLED_Init()
{
	SCK = 0;
	RCK = 0;
}

void _74hc595_WriteBYte(unsigned char Byte) //控制行
{
	unsigned char i = 0;
	for(i = 0; i < 8; i++)
	{
		SER = Byte & (0x80>>i);
		//从数据最高位开始每一位输入，且对于bit位非零即真
		SCK = 1;
		SCK = 0;
	}
	RCK = 1;
	RCK = 0;
}

//Column为要选择的行，Data是这一列
void MatrixLED_ShowCilumn(unsigned char Column,Data) 
{
	_74hc595_WriteBYte(Data);
	P0 = ~(0x80 >> Column);    //控制行
	Delay(1);                  //增加通电时间，增加亮度
	P0 = 0xFF;                 //位选清零
}

#include <REGX52.H>
#include "Delay.h"

sbit RCK = P3^5;    //RCLk
sbit SCK = P3^6;    //SRCLK
sbit SER = P3^4;    //SER

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

void main()
{
	SCK = 0;
	RCK = 0;
	while(1)
	{
		MatrixLED_ShowCilumn(0,0x3C);  //逐列扫描
		MatrixLED_ShowCilumn(1,0x42);
		MatrixLED_ShowCilumn(2,0xA9);
		MatrixLED_ShowCilumn(3,0x85);
		MatrixLED_ShowCilumn(4,0x85);
		MatrixLED_ShowCilumn(5,0xA9);
		MatrixLED_ShowCilumn(6,0x42);
		MatrixLED_ShowCilumn(7,0x3C);
	}
}
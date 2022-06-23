#include <REGX52.H>

#define YEAR         0x8C
#define MONTH        0x88
#define DATE         0x86
#define HOUR         0x84
#define MINUTES      0x82
#define SECONDS      0x80
#define WP           0x8E

sbit SCLK = P3^6;
sbit IO = P3^4;
sbit CE = P3^5;

unsigned char Time[] = {22,4,22,2,59,55};

void DS1302_Init()
{
	SCLK = 0;
	CE = 0;
}

void DS1302_WriteByte(unsigned char Command ,Data)
{
	unsigned char i = 0;
	
	CE = 1;
	for(i = 0; i< 8; i++)
	{
		IO = Command & (0x01<<i);
		SCLK = 1;
		SCLK = 0;
	}
	for(i = 0; i< 8; i++)
	{
		IO = Data & (0x01<<i);
		SCLK = 1;
		SCLK = 0;
	}
	CE = 0;
}

unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i = 0,Data = 0;
	
	Command |= 0x01;
	CE = 1;
	for(i = 0; i< 8; i++)
	{
		IO = Command & (0x01<<i);
//		SCLK = 1;
//		if(i != 7)SCLK = 0;
		SCLK = 0;
		SCLK = 1;
	}
	
	IO = 0;
	for(i = 0; i< 8; i++)
	{
		SCLK = 1;
		SCLK = 0;
		if(IO)
		{
			Data |= (0x01<<i);
		}
	}
	CE = 0;
	return Data;
}

void DS1302_SetTime()
{
	DS1302_WriteByte(WP,0x00);
	DS1302_WriteByte(YEAR,Time[0]/10*16+Time[0]%10);
	DS1302_WriteByte(MONTH,Time[1]/10*16+Time[1]%10);
	DS1302_WriteByte(DATE,Time[2]/10*16+Time[2]%10);
	DS1302_WriteByte(HOUR,Time[3]/10*16+Time[3]%10);
	DS1302_WriteByte(MINUTES,Time[4]/10*16+Time[4]%10);
	DS1302_WriteByte(SECONDS,Time[5]/10*16+Time[5]%10);
	DS1302_WriteByte(WP,0x80);
}

void DS1302_ReadTime()
{
	Time[0] = DS1302_ReadByte(YEAR)/16*10+DS1302_ReadByte(YEAR)%16;
	Time[1] = DS1302_ReadByte(MONTH)/16*10+DS1302_ReadByte(MONTH)%16;
	Time[2] = DS1302_ReadByte(DATE)/16*10+DS1302_ReadByte(DATE)%16;
	Time[3] = DS1302_ReadByte(HOUR)/16*10+DS1302_ReadByte(HOUR)%16;
	Time[4] = DS1302_ReadByte(MINUTES)/16*10+DS1302_ReadByte(MINUTES)%16;
	Time[5] = DS1302_ReadByte(SECONDS)/16*10+DS1302_ReadByte(SECONDS)%16;
}
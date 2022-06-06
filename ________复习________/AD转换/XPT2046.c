#include <REGX52.H>

sbit XPT2046_DOUT = P3^7;
sbit XPT2046_DIN = P3^4;
sbit XPT2046_CS = P3^5;
sbit XPT2046_DCLK = P3^6;

unsigned int XPT2046_ReadAD(unsigned char Command)
{
	unsigned int ADValue = 0;
	unsigned char i = 0;
	
	XPT2046_CS = 0;
	for(i = 0; i < 8; i++)
	{
		XPT2046_DIN = Command & (0x80>>i);
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
	}
	for(i = 0; i < 16; i++)
	{
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
		if(XPT2046_DOUT == 1)
		{
			ADValue |= (0x8000>>i);
		}
	}
	XPT2046_CS = 1;
	if(Command & 0x08)
	{
		return ADValue>>8;  //8位分辨率
	}
	else
	{
		return ADValue>>4;  //12位
	}
}
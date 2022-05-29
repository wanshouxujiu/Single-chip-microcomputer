#include <REGX52.H>

void Timer1_Init()
{
	TMOD &= 0x0F;
	TMOD |= 0x10;
	TF1 = 0;
	TR1 = 1;
	TH1 = 64535 / 256;
	TL1 = 64535 % 256 + 1;
	ET1 = 1;
	EA = 1;
	PT1 = 0;
}
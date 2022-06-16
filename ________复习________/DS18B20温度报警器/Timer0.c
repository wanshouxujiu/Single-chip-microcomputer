#include <REGX52.H>

void Timer0_Init()
{
	TMOD |= 0x0F;
	TMOD &= 0xF1;
	ET0 = 1;
	EA = 1;
	PT0 = 0;
	TF0 = 0;
	TH0 = 64613 / 256;   //1ms(11.0592M)
	TL0 = 64613 % 256;
	TR0 = 1;
}

//void Timer0_Rountine () interrupt 1
//{
//	
//}
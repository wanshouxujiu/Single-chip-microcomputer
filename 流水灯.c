#include <STC89C5xRC.H>
#include <intrins.h>

void Delay200ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 2;
	j = 134;
	k = 20;
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
	while(1)
	{
		P2 = 0xfe;//1111 1110
		Delay200ms();
		P2 = 0xfd;
		Delay200ms();
		P2 = 0xfb;
		Delay200ms();
		P2 = 0xf7;
		Delay200ms();
		P2 = 0xef;
		Delay200ms();
		P2 = 0xdf;
		Delay200ms();
		P2 = 0xbf;
		Delay200ms();
		P2 = 0x7f;
		Delay200ms();
	}
}

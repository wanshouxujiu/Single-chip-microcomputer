#include <REGX52.H>
#include <intrins.h>

void Delay(unsigned int xms)		//@11.0592MHz
{
	while(xms--)
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
}

unsigned char key()
{
	if(P3_1 == 0){Delay(20);while(P3_1 == 0);Delay(20);return 1;}
	if(P3_0 == 0){Delay(20);while(P3_0 == 0);Delay(20);return 2;}
	if(P3_2 == 0){Delay(20);while(P3_2 == 0);Delay(20);return 3;}
	if(P3_3 == 0){Delay(20);while(P3_3 == 0);Delay(20);return 4;}
	return 0;
}
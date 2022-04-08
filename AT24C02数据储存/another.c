#include <REGX52.H>

void Delay(unsigned int xms)		//@12.000MHz
{
	while(xms--)
	{
		unsigned char i, j;

		i = 2;
		j = 239;
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
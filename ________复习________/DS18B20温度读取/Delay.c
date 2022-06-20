#include <intrins.H>


void Delay(unsigned char xms)		//@11.0592MHz  1ms
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

#include <REGX52.H>

sbit LED = P2^0;

void Delayus(unsigned char X)  //~5us
{
	while(X--)
	{
		unsigned char i;
		i = 2;
		while (--i);
	}
}

void main()
{
	unsigned char Time = 0,t = 0;
	while(1)
	{
		for(Time = 0; Time < 50; Time++)    //50档亮度
		{
			for(t = 0; t <= 30; t++)    //每个亮度维持30次
			{
				LED = 0;
				Delayus(Time);
				LED = 1;
				Delayus(50 - Time);
			}
		}
		for(Time = 50; Time > 0; Time--)
		{
			for(t = 0; t <= 30; t++)
			{
				LED = 0;
				Delayus(Time);
				LED = 1;
				Delayus(50 - Time);
			} 
		}
	}
}
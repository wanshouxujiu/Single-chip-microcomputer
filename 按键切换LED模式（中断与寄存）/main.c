#include <REGX52.H>
#include "Timer.h"
#include "another.h"
#include <INTRINS.H>
	
unsigned char KeyNum = 0; //因为中断函数需要用到这两个变量，所以拿到上面
unsigned char LEDMode = 0;
//void Timer0_Init();

void main()
{
	P2 = 0xfe;
	Timer0_Init();
	while(1)
	{
		KeyNum = key();
		if(KeyNum == 1)
		{
			LEDMode++;
			if(LEDMode >= 2)LEDMode = 0;
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0count = 0;
	TH0 = 64535 / 256;
	TL0 = 64535 % 256 + 1;
	T0count++;
	if(T0count >= 500)
	{
		T0count = 0;
		if(LEDMode == 0)P2 = _crol_(P2,1);
		if(LEDMode == 1)P2 = _cror_(P2,1);
	}
}
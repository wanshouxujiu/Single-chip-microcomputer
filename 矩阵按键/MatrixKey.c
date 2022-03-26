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

unsigned char MatrixKey()
{
	unsigned char KeyNum = 0;
	
	P1 = 0xFF;
	P1_3 = 0;  //下面的while会让你按下不放时不显示数字
	if(P1_7 == 0){Delay(20);while(P1_7 == 0);Delay(20);KeyNum = 1;}
	if(P1_6 == 0){Delay(20);while(P1_6 == 0);Delay(20);KeyNum = 5;}
	if(P1_5 == 0){Delay(20);while(P1_5 == 0);Delay(20);KeyNum = 9;}
	if(P1_4 == 0){Delay(20);while(P1_4 == 0);Delay(20);KeyNum = 13;}
	
	P1 = 0xFF;
	P1_2 = 0;
	if(P1_7 == 0){Delay(20);while(P1_7 == 0);Delay(20);KeyNum = 2;}
	if(P1_6 == 0){Delay(20);while(P1_6 == 0);Delay(20);KeyNum = 6;}
	if(P1_5 == 0){Delay(20);while(P1_5 == 0);Delay(20);KeyNum = 10;}
	if(P1_4 == 0){Delay(20);while(P1_4 == 0);Delay(20);KeyNum = 14;}
	
	P1 = 0xFF;
	P1_1 = 0;
	if(P1_7 == 0){Delay(20);while(P1_7 == 0);Delay(20);KeyNum = 3;}
	if(P1_6 == 0){Delay(20);while(P1_6 == 0);Delay(20);KeyNum = 7;}
	if(P1_5 == 0){Delay(20);while(P1_5 == 0);Delay(20);KeyNum = 11;}
	if(P1_4 == 0){Delay(20);while(P1_4 == 0);Delay(20);KeyNum = 15;}
	
	P1 = 0xFF;
	P1_0 = 0;
	if(P1_7 == 0){Delay(20);while(P1_7 == 0);Delay(20);KeyNum = 4;}
	if(P1_6 == 0){Delay(20);while(P1_6 == 0);Delay(20);KeyNum = 8;}
	if(P1_5 == 0){Delay(20);while(P1_5 == 0);Delay(20);KeyNum = 12;}
	if(P1_4 == 0){Delay(20);while(P1_4 == 0);Delay(20);KeyNum = 16;}
	
	return KeyNum;
}
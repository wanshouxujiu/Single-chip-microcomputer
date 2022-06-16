#include <REGX52.H>
#include "Delay.h"

unsigned char KeyNum1;

unsigned char Key()
{
	unsigned char Tmp = KeyNum1;
	KeyNum1 = 0;
	return Tmp;
}

unsigned char Key_Num()
{
	if(P3_1 == 0){return 1;}
	if(P3_0 == 0){return 2;}
	if(P3_2 == 0){return 3;}
	if(P3_3 == 0){return 4;}
	return 0;
}

void Key_Timer0()
{
	static unsigned char Now_KeyNum = 0,Last_KeyNum = 0;
	Last_KeyNum = Now_KeyNum;
	Now_KeyNum = Key_Num();
	if(Last_KeyNum == 1 && Now_KeyNum == 0)
	{
		KeyNum1 = 1;
	}
	if(Last_KeyNum == 2 && Now_KeyNum == 0)
	{
		KeyNum1 = 2;
	}
	if(Last_KeyNum == 3 && Now_KeyNum == 0)
	{
		KeyNum1 = 3;
	}
	if(Last_KeyNum == 4 && Now_KeyNum == 0)
	{
		KeyNum1 = 4;
	}
}
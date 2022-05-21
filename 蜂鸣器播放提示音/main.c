#include <REGX52.H>
#include "another.h"
#include "Beep.h"

unsigned char KeyNum;
unsigned char NixieTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void Nixie(unsigned char Loaction,Number) //输列和数字
{
	switch(Loaction)
	{
		case 1:P2_4 = 1;P2_3 = 1;P2_2 = 1;break;
		case 2:P2_4 = 1;P2_3 = 1;P2_2 = 0;break;
		case 3:P2_4 = 1;P2_3 = 0;P2_2 = 1;break;
		case 4:P2_4 = 1;P2_3 = 0;P2_2 = 0;break;
		case 5:P2_4 = 0;P2_3 = 1;P2_2 = 1;break;
		case 6:P2_4 = 0;P2_3 = 1;P2_2 = 0;break;
		case 7:P2_4 = 0;P2_3 = 0;P2_2 = 1;break;
		case 8:P2_4 = 0;P2_3 = 0;P2_2 = 0;break;
	}
	P0 = NixieTable[Number];
//	Delay(1);  //芯片速度太快，容易这次显示信号还没送出，就把下一次的全灭信号送出了
//	P0 = 0x00; //消隐，覆盖上一次输出的数据，因为芯片速度太快，容易把上一次的数据送到这次
}

void main()
{
	while(1)
	{
		KeyNum = key();
		if(KeyNum)
		{
			Beep_Time(1000);
			Nixie(1,KeyNum);
		}
	}
}
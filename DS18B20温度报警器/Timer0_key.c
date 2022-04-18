#include <REGX52.H>

unsigned char Key_KeyNumber;

unsigned char Timer0_Key()
{
	unsigned char Temp = 0;
	Temp = Key_KeyNumber;
	Key_KeyNumber = 0;
	return Temp;
}

unsigned char key_GetState()
{
	if(P3_1 == 0){return 1;}
	if(P3_0 == 0){return 2;}
	if(P3_2 == 0){return 3;}
	if(P3_3 == 0){return 4;}
	return 0;
}

void Key_Loop()
{
	static unsigned char NowState = 0, LastState = 0;
	LastState = NowState;
	NowState = Key_GetState();
	if(LastState==0 && NowState == 1)    //按下反应
	{
		Key_KeyNumber = 1;
	}
	if(LastState==2 && NowState == 0)    //松开反应
	{
		Key_KeyNumber = 2;
	}
	if(LastState==3 && NowState == 0)
	{
		Key_KeyNumber = 3;
	}
	if(LastState==4 && NowState == 0)
	{
		Key_KeyNumber = 4;
	}
}
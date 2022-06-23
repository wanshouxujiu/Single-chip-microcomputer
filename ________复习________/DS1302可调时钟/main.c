#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"


unsigned char KeyNum,SetNum,TimerDelay,Mode;

void SetShowTime()
{
	if(TimerDelay == 1 && SetNum == 0){LCD_ShowString(1,1,"  ");}
	else{LCD_ShowNum(1,1,Time[0],2);}
	if(TimerDelay == 1 && SetNum == 1){LCD_ShowString(1,4,"  ");}
	else{LCD_ShowNum(1,4,Time[1],2);}
	if(TimerDelay == 1 && SetNum == 2){LCD_ShowString(1,7,"  ");}
	else{LCD_ShowNum(1,7,Time[2],2);}
	if(TimerDelay == 1 && SetNum == 3){LCD_ShowString(2,1,"  ");}
	else{LCD_ShowNum(2,1,Time[3],2);}
	if(TimerDelay == 1 && SetNum == 4){LCD_ShowString(2,4,"  ");}
	else{LCD_ShowNum(2,4,Time[4],2);}
	if(TimerDelay == 1 && SetNum == 5){LCD_ShowString(2,7,"  ");}
	else{LCD_ShowNum(2,7,Time[5],2);}
}

void ShowTime()
{
	DS1302_ReadTime();
	LCD_ShowNum(1,1,Time[0],2);
	LCD_ShowNum(1,4,Time[1],2);
	LCD_ShowNum(1,7,Time[2],2);
	LCD_ShowNum(2,1,Time[3],2);
	LCD_ShowNum(2,4,Time[4],2);
	LCD_ShowNum(2,7,Time[5],2);
}

void main()
{
	DS1302_Init();
	LCD_Init();
	Timer0_Init();
	
	LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
	DS1302_SetTime();
	while(1)
	{
		KeyNum = Key();
		if(KeyNum)
		{
			if(KeyNum == 1)
			{
				Mode++;
				if(Mode == 2)
				{
					Mode = 0;
					DS1302_SetTime();
					SetNum = 0;
				}
			}
			if(KeyNum == 2)
			{
				SetNum++;
				SetNum %= 6;
				LCD_ShowNum(2,15,SetNum,2);
			}
			if(KeyNum == 3)
			{
				switch(SetNum)
				{
					case 0:Time[0]++;if(Time[0] == 100){Time[0] = 0;}break;
					case 1:Time[1]++;if(Time[1] == 13){Time[1] = 1;}break;
					case 2:
					Time[2]++;
					if(Time[1] == 1 || Time[1] == 3 || Time[1] == 5 || Time[1] == 7 || 
						Time[1] == 8 || Time[1] == 10 || Time[1] == 12)
					{
						if(Time[2] == 32){Time[2] = 1;}
					}
					if(Time[1] == 4 || Time[1] == 6 || Time[1] == 9 || Time[1] == 11)
					{
						if(Time[2] == 31){Time[2] = 1;}
					}
					if(Time[1] == 2)
					{
						if(Time[0]%4 == 0)
						{
							if(Time[2] > 28){Time[2] = 1;}
						}
						else
						{
							if(Time[2] > 28){Time[2] = 1;}
						}
					}
					break;
					case 3:Time[3]++;if(Time[3]>23) {Time[3]=0;}break;
					case 4:Time[4]++;if(Time[4]>59) {Time[4]=0;}break;
					case 5:Time[5]++;if(Time[5]>59) {Time[5]=0;}break;
				}
			}
			if(KeyNum == 4)
			{
				Time[SetNum]--;    //时间减
				if(Time[0]<0) {Time[0]=99;}
				if(Time[1]<1) {Time[1]=12;}
				if(Time[1]==1 || Time[1]==3 || Time[1]==5 || Time[1]==7 ||
				Time [1]==8 || Time[1]==10 || Time [1]==12)
				{
					if (Time [2]<1) {Time[2]=31;}
					if (Time [2]>31) {Time[2]=1;}
				}
				else if(Time[1]==4 || Time[1]==6 || Time[1]==9 || Time[1]==11)
				{
					if (Time [2]<1) {Time[2]=30;}
					if (Time [2]>30) {Time[2]=1;}
				}
				else if(Time[1] == 2)
				{
					if(Time[0] % 4 == 0)
					{
						if (Time[2]<1) {Time[2]=29;}
						if (Time[2]>29) {Time[2]=1;}
					}
					else
					{
						if (Time[2]<1) {Time[2]=28;}
						if (Time[2]>28) {Time[2]=1;}
					}
				}
				if(Time[3]<0) {Time[3]=23;}
				if(Time[4]<0) {Time[4]=59;}
				if(Time[5]<0) {Time[5]=59;}
			}
		}
		switch(Mode)
		{
			case 0:ShowTime();break;
			case 1:SetShowTime();break;
		}
	}
}

void Timer0_Rountine () interrupt 1
{
	static unsigned int count = 0;
	TH0 = 64613 / 256;   //1ms(11.0592M)
	TL0 = 64613 % 256;
	count++;
	if(count == 500)
	{
		count = 0;
		TimerDelay++;
		TimerDelay %= 2;
	}
}
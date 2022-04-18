#include <REGX52.H>
#include <another.H>
#include <AT24C02.H>
#include <DS18B20.H>
#include <LCD1602.H>

float T,TShow;
char TLow,THigh;
unsigned char KeyNum;

void main()
{
	DS18B20_ConvertT();    //先进行一次转换，否则显示上次的温度
	Delay(1000);           //转换需要时间，精度越高，时间越长
	THigh = AT24C02_ReadByte(0);
	TLow = AT24C02_ReadByte(1);
	if(THigh>125 || TLow <-55 || THigh<=TLow)
	{
		THigh = 30;
		TLow = -10;
	}
	LCD_Init();
	LCD_ShowString(1,1,"T:");
	LCD_ShowString(2,1,"TH:");
	LCD_ShowString(2,9,"TL:");
	LCD_ShowSignedNum(2,4,THigh,3);
	LCD_ShowSignedNum(2,12,TLow,3);
	Timer0_Init();
	while(1)
	{
		KeyNum = Timer0_key();
		/*温度读取*/
		DS18B20_ConvertT();
		T = DS18B20_ReadT();
		if(T < 0)
		{
			LCD_ShowChar(1,3,'-');
			TShow = -T;
		}
		else
		{
			LCD_ShowChar(1,3,'+');
			TShow = T;
		}
		LCD_ShowNum(1,4,TShow,3);
		LCD_ShowChar(1,7,'.');
		LCD_ShowNum(1,8,(unsigned long)(TShow*100)%100,2);
		
		/*阈值及判断*/
		if(KeyNum)
		{
			if(KeyNum == 1 && THigh<125)
			{
				THigh++;
			}
			if(KeyNum == 2 && THigh>TLow+1)
			{
				THigh--;
			}
			if(KeyNum == 3 && TLow<THigh-1)
			{
				TLow++;
			}
			if(KeyNum == 4 && TLow>-55)
			{
				TLow--;
			}
			LCD_ShowSignedNum(2,4,THigh,3);
			LCD_ShowSignedNum(2,12,TLow,3);
			AT24C02_WriteByte(0,THigh);
			Delay(5);
			AT24C02_WriteByte(1,TLow);
			Delay(5);
		}
		if(T > THigh)
		{
			LCD_ShowString(1,13,"OV:H");
		}
		else if(T < TLow)
		{
			LCD_ShowString(1,13,"OV:L");
		}
		else
		{
			LCD_ShowString(1,13,"    ");
		}
	}
}

void Timer0_Routine() interrupt 1    //中断对单总线通信有干扰
{
	static unsigned int T0count1 = 0, T0count2, T0count3;
	TL0 = 0x18;
	TH0 = 0xFC;
	T0count1++;
	if(T0count1 >= 20)
	{
		T0count1 = 0;
		Key_Loop();
	}
}
#include <STC89C5xRC.H>
	
//=========================按下点亮=====================

//void main()
//{
//	while(1)
//	{
//		if(P31 == 0)
//		{
//			P20 = 0;
//		}
//		else
//		{
//			P20 = 1;
//		}
//	}
//}	

//=====================按下显示二进制===================

//	void Delay(unsigned int xms)		//@12.000MHz
//{
//	while(xms--)
//	{
//		unsigned char i, j;

//		i = 2;
//		j = 239;
//		do
//		{
//			while (--j);
//		} while (--i);
//	}
//}

//void main()
//{
//	unsigned char num1 = 0;
//	while(1)
//	{
//		if(P31 == 0)
//		{
//			Delay(20);	//按下消抖
//			while(P31 == 0)
//			{
//			
//			}
//			Delay(20);	//松开消抖
//			num1++;
//			P2 = ~num1;
//		}
//	}
//}

//======================按下位移======================

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

unsigned char num1 = 0;	//num1为几就移几位

void main()
{
	P2 = ~(0x01);
	while(1)
	{
		if(P31 == 0)
		{
			Delay(20);
			while(P31 == 0);
			Delay(20);
			
			num1++;
			if(num1 > 7)
			 num1 = 0;
			
			P2 = ~(0x01 << num1);
		}
				
		if(P30 == 0)
		{
			Delay(20);
			while(P30 == 0);
			Delay(20);
			
			num1--;
			
			if(num1 > 7)
			 num1 = 7;
			
			P2 = ~(0x01 << num1);
		}
	}
}

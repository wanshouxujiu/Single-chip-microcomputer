#include "LCD1602.H"
#include "MatrixKey.h"

void main()
{
	unsigned char KeyNum = 0;
	unsigned int Password = 0;
	unsigned char count = 0;
	
	LCD_INit();
	while(1)
	{
		KeyNum = MatrixKey();
		
		if(0 < KeyNum && KeyNum <= 10 && count < 4)  //没有if会显示后立刻刷新bh
		{
				Password *= 10;
				Password += KeyNum % 10;
				LCD_ShowNum(1,1,Password,4);
				count++;
		}
		if(KeyNum == 11 && Password == 2345)
		{
			LCD_ShowString(1,14,"OK "); //输入正确
		}
		if(KeyNum == 11 && Password != 2345)
		{
			LCD_ShowString(1,14,"ERR"); //输入错误
			Password = 0;               //密码清零
			count = 0;
			LCD_ShowNum(1,1,Password,4);
		}
		if(KeyNum == 12) //清零
		{
			Password = 0;
			count = 0;
			LCD_ShowNum(1,1,Password,4);
		}
	} 
}
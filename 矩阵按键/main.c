#include "LCD1602.H"
#include "MatrixKey.h"

void main()
{
	unsigned char KeyNum = 0;
	LCD_INit();
	while(1)
	{
		KeyNum = MatrixKey();
		if(KeyNum)  //没有if会显示后立刻刷新
		{
			LCD_ShowNum(1,1,KeyNum,2);
		}
	}
}
#include <REGX52.H>
#include "another.H"
#include "LCD1602.H"
#include "IR.H"

unsigned char Num;
unsigned char Address;
unsigned char Command;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"ADDR  CMD  NUM");
	LCD_ShowString(2,1,"00    00   000");
	IR_Init();
	
	while(1)
	{
		if(IR_GetDataFlag() || IR_GetRepeatFlag())
		{
			Address = IR_GetAddress();
			Command = IR_GetCommand();
			
			LCD_ShowHexNum(2,1,Address,2);
			LCD_ShowHexNum(2,7,Command,2);
			
			if(Command == 0x15)
			{
				Num++;
			}
			else if(Command == 0x09)
			{
				Num--;
			}
			LCD_ShowNum(2,12,Num,3);
		}
	}
}

//void Int0_Routine() interrupt 0
//{
//	
//}
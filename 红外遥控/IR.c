#include <REGX52.H>
#include <Int0.H>
#include <Timer0_num.H>

unsigned int IR_Time;            //高低电平计时(计时器：一个1为1.085us)
unsigned char IR_State;          //阶段(状态标志)

unsigned char IR_Data[4];        //数据接收
unsigned char IR_pData;          //移位计数

unsigned char IR_DataFlag;       //收到标志
unsigned char IR_RepeatFlag;     //重复发送标志
unsigned char IR_Address;        //地址码
unsigned char IR_Command;        //命令码

void IR_Init()
{
	Timer0_Init();
	Int0_Init();
}

unsigned char IR_GetDataFlag()      //查询：数据是否接收
{
	if(IR_DataFlag)
	{
		IR_DataFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IR_GetRepeatFlag()    //查询：是否重复
{
	if(IR_RepeatFlag)
	{
		IR_RepeatFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IR_GetAddress()       //查询：地址码
{
	return IR_Address;
}

unsigned char IR_GetCommand()       //查询：命令
{
	return IR_Command;
}

void Int0_Routine() interrupt 0
{
	if(IR_State == 0)
	{
		Timer0_SetCounter(0);
		Timer0_Run(1);
		IR_State = 1;
	}
	else if(IR_State == 1)
	{
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		if(IR_Time>12442-500 && IR_Time<12442+500)
		{
			IR_State = 2;
		}
		else if(IR_Time>10368-500 && IR_Time<10368+500)
		{
			IR_RepeatFlag = 1;
			Timer0_Run(0);
			IR_State = 0;
		}
		else
		{
			IR_State = 1;
		}
	}
	else if(IR_State == 2)  //开始数据接收
	{
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		if(IR_Time>1032-500 && IR_Time<1032+500)    //数据为0时
		{
			IR_Data[IR_pData/8] &= ~(0x01<<(IR_pData%8)); //32位数据切分4个char
			IR_pData++;
		}
		else if(IR_Time>2074-500 && IR_Time<2074+500)   //数据为1时
		{
			IR_Data[IR_pData/8] |= (0x01<<(IR_pData%8));
			IR_pData++;
		}
		else
		{
			IR_pData = 0;
			IR_State = 1;
		}
		if(IR_pData >= 32)
		{
			IR_pData = 0;
			if((IR_Data[0] == ~IR_Data[1]) && (IR_Data[2] == ~IR_Data[3]))
			{
				IR_Address = IR_Data[0];
				IR_Command = IR_Data[2];
				IR_DataFlag = 1;
			}
			Timer0_Run(0);
			IR_State = 0;
		}
	}
}
#include <REGX52.H>

//命令字
#define DS1302_SECOND        0x80    //由手册得知写命令
#define DS1302_MINUTE        0x82
#define DS1302_HOUR          0x84
#define DS1302_DATE          0x86
#define DS1302_MONTH         0x88
#define DS1302_DAY           0x8A
#define DS1302_YEAR          0x8C
#define DS1302_WP            0x8E

sbit DS1302_SCLk = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

char DS1302_Time[] = {22,3,19,22,22,00,6};  //时间初始化数组

void DS1302_WriteByte(unsigned char Command,Data)
{
	unsigned char i = 0;
	DS1302_CE = 1;
	
	for(i = 0; i < 8; i++)
	{
		DS1302_IO = Command & (0x01<<i);
		DS1302_SCLk = 1;
		DS1302_SCLk = 0;    //紧接着置零，DS1302时序来得及
	}
	for(i = 0; i < 8; i++)
	{
		DS1302_IO = Data & (0x01<<i);
		DS1302_SCLk = 1;
		DS1302_SCLk = 0;
	}
	DS1302_CE = 0;
}

unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i = 0,Data = 0x00;
	DS1302_CE = 1;
	Command |= 0x01;    //读的命令字最低位始终为1，所以加上1
	
	for(i = 0; i < 8; i++)
	{
		DS1302_IO = Command & (0x01<<i);
		DS1302_SCLk = 0;    //为了让脉冲停留在第8个脉冲的高电平
		DS1302_SCLk = 1;
	}
	
	DS1302_IO = 0;
	for(i = 0; i < 8; i++)
	{
		DS1302_SCLk = 1;
		DS1302_SCLk = 0;    //开始放出数据，且最后置为0
		if(DS1302_IO)
		{
			Data |= (0x01<<i);
		}
	}
	DS1302_CE = 0;
	return Data;
}

void DS1302_int()
{
	DS1302_CE = 0;
	DS1302_SCLk = 0;
}

void DS1302_SetTime()    //写入时间，（BCD码转换）
{
	DS1302_WriteByte(DS1302_WP,0x00);
	DS1302_WriteByte(DS1302_YEAR,DS1302_Time[0]/10*16 + DS1302_Time[0]%10);
	DS1302_WriteByte(DS1302_MONTH,DS1302_Time[1]/10*16 + DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,DS1302_Time[2]/10*16 + DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,DS1302_Time[3]/10*16 + DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_Time[4]/10*16 + DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5]/10*16 + DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_Time[6]/10*16 + DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80);
}

void DS1302_ReadTime()    //读取时间，（BCD码转换）
{
	unsigned char tmp = 0;
	tmp = DS1302_ReadByte(DS1302_YEAR);
	DS1302_Time[0] = tmp/16*10 + tmp%16;
	tmp = DS1302_ReadByte(DS1302_MONTH);
	DS1302_Time[1] = tmp/16*10 + tmp%16;
	tmp = DS1302_ReadByte(DS1302_DATE);
	DS1302_Time[2] = tmp/16*10 + tmp%16;
	tmp = DS1302_ReadByte(DS1302_HOUR);
	DS1302_Time[3] = tmp/16*10 + tmp%16;
	tmp = DS1302_ReadByte(DS1302_MINUTE);
	DS1302_Time[4] = tmp/16*10 + tmp%16;
	tmp = DS1302_ReadByte(DS1302_SECOND);
	DS1302_Time[5] = tmp/16*10 + tmp%16;
	tmp = DS1302_ReadByte(DS1302_DAY);
	DS1302_Time[6] = tmp/16*10 + tmp%16;
}
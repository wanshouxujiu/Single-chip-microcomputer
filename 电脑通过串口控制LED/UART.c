#include <REGX52.H>

void UART_Init() //4800bps @11.0592MHz
{
	PCON |= 0x80;      //波特率加倍
	SCON |= 0x50;      //8位数据，可变波特率（模式选择）
	TMOD &= 0x0F;      //定时器1
	TMOD |= 0x20;      //八位自动重装模式
	TL1 = 0xF4;        //设置定时器1初始值，可去除？
	TH1 = 0xF4;        //设置定时器1重载值
	ET1 = 0;           //禁止定时器1中断
	TR1 = 1;
	EA = 1;
	ES = 1;
}
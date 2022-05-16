#include <REGX52.H>
#include "anther.h"
#include "UART.h"

void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while(TI == 0); //类似消抖？
	TI = 0; //由手册得知每次请求中断后必须置回1
}

void main()
{
	UART_Init();
	while(1)
	{
		
	}
}

void UART_Routine() interrupt 4 //接收到数据跳到这执行
{
	if(RI == 1)
	{
		P2 = ~SBUF;                 //取反是因为0导通，好写
		UART_SendByte(SBUF);        //在这里面发送不会再次引起中断？不会，这里是电脑那边的中断。
		RI = 0;
	}
}
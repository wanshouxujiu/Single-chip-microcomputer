#include <REGX52.H>
#include "another.h"
#include "UART.h"

unsigned char sec = 0;

void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while(TI == 0); //等待数据被电脑拿走
	TI = 0; //由手册得知每次请求中断后必须置回1
}

void main()
{
	UART_Init();
	while(1)
	{
		UART_SendByte(sec); //第一次没收到是因为发送完后才打开了串口
		sec++;
		Delay(1000);
	}
}
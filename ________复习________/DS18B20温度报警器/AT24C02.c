#include <REGX52.H>
#include "IIC.H"

#define WORD_ADDRESS 0xA0

void AT24C02_WriteByte(unsigned char Address,Data)
{
	IIC_Start();
	IIC_SendByte(WORD_ADDRESS);  //硬件地址
	IIC_ReceiveAck();            //暂不处理
	IIC_SendByte(Address);       //数据地址
	IIC_ReceiveAck();
	IIC_SendByte(Data);          //数据
	IIC_ReceiveAck();
	IIC_Stop();
}

unsigned char AT24C02_ReadByte(unsigned char Address)
{
	unsigned char Data;
	
	IIC_Start();
	IIC_SendByte(WORD_ADDRESS);  //硬件地址
	IIC_ReceiveAck();            //暂不处理
	IIC_SendByte(Address);       //数据地址
	IIC_ReceiveAck();
	
	IIC_Start();
	IIC_SendByte(WORD_ADDRESS | 0x01);  //硬件地址
	IIC_ReceiveAck();
	Data = IIC_ReceiveByte();
	IIC_SendAck(1);                     //1就停止接收了
	IIC_Stop();
	
	return Data;
}
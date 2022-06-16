#include <REGX52.H>

sbit SCL = P2^1;
sbit SDA = P2^0;

//起始
void IIC_Start()
{
	SDA = 1;
	SCL = 1;
	SDA = 0;
	SCL = 0;
}

//终止
void IIC_Stop()
{
	SCL = 0;
	SDA = 0;
	SCL = 1;
	SDA = 1;
}

//发送数据
void IIC_SendByte(unsigned char Data)
{
	unsigned char i = 0;
	for(i = 0; i < 8; i++)
	{
		SDA = Data & (0x80>>i);      //注意高低位
		SCL = 1;
		SCL = 0;
	}
}

//接收数据
unsigned char IIC_ReceiveByte()
{
	unsigned char Data = 0,i = 0;
	
	SDA = 1;
	for(i = 0; i < 8; i++)
	{
		SCL = 1;
		if(SDA)
		{
			Data |= (0x80>>i);          //注意高低位
		}
		SCL = 0;
	}
	return Data;
}

//发应答
void IIC_SendAck(bit Ack)
{
	SDA = Ack;
	SCL = 1;
	SCL = 0;
}

//收应答
bit IIC_ReceiveAck()
{
	bit Ack = 0;
	SDA = 1;           //释放控制权
	SCL = 1;
	Ack = SDA;
	SCL = 0;
	
	return Ack;
}
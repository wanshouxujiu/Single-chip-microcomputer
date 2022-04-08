#include <REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

//起始
void I2C_Start()
{
	I2C_SDA = 1;
	I2C_SCL = 1;
	I2C_SDA = 0;   //SCL高电平时拉低
	I2C_SCL = 0;
}

//终止
void I2C_Stop()
{
	I2C_SDA = 0;
	I2C_SCL = 1;
	I2C_SDA = 1;
}

//发送数据
void I2C_SendByte(unsigned char Byte) //考虑电气特性（高电平最少持续时间）
{
	unsigned char i = 0;
	for(i = 0; i < 8; i++)
	{
		I2C_SDA = Byte & (0x80>>i); //高位在前
		I2C_SCL = 1;
		I2C_SCL = 0;
	}
}

//读数据
unsigned char I2C_ReceiveByte()
{
	unsigned char i = 0, Byte = 0;
	
	I2C_SDA = 1;    //释放控制权
	
	for(i = 0; i < 8; i++)
	{
		I2C_SCL = 1;
		if(I2C_SDA)
		{
			Byte |= (0x80>>i);
		}
		I2C_SCL = 0;
	}
	
	return Byte;
}

//发送应答
void I2C_SendAck(bit AckBit)    //bit类型为C51拓展类型
{
	I2C_SDA = AckBit;
	I2C_SCL = 1;
	I2C_SDA = 0;
}

//收应答
bit I2C_ReceiveAck()
{
	bit AckBit;
	I2C_SDA = 1;
	I2C_SCL = 1;
	AckBit = I2C_SDA;
	I2C_SCL = 0;
	
	return AckBit;
}
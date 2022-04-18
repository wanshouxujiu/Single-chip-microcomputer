#include <REGX52.H>
#include <intrins.h>

sbit OneWire_DQ = P3^7;

//起始（初始化）
unsigned char OneWire_Init()
{
	unsigned char i = 0;
	unsigned char AckBit;
	EA = 0;                         //屏蔽中断
	OneWire_DQ = 1;
	OneWire_DQ = 0;
	_nop_();i = 230;while (--i);    //Delay 500us,可以去看看软件延时5us（11.0592，Y1指令集）
	OneWire_DQ = 1;
	_nop_();i = 32;while (--i);     //Delay 70us,用于释放总线
	AckBit = OneWire_DQ;            //读取应答
	_nop_();i = 230;while (--i);
	EA = 1;
	return AckBit;
}

//发送一位Bit
void Onewire_SendBit(unsigned char Bit)
{
	unsigned char i = 0;
	EA = 0;
	OneWire_DQ = 0;
	i = 4;while (--i);          //Dealy 10us,因为如果发送1，需要先延时1~15us
	OneWire_DQ = Bit;
	_nop_();i = 22;while (--i); //再Dealy 50us,因为如果发送0，需要保持60~120us
	OneWire_DQ = 1;
	EA = 1;
}

//接收一位Bit
unsigned char Onewire_ReceiveBit()
{
	unsigned char i = 0;
	unsigned char Bit = 0;
	EA = 0;
	OneWire_DQ = 0;
	i = 2;while (--i);          //Delay 5us  //释放和下拉都需要时间
	OneWire_DQ = 1;
	i = 2;while (--i);          //Delay 5us  //释放和下拉都需要时间
	Bit = OneWire_DQ;
	_nop_();i = 22;while (--i); //Delay 50us,保证时间片大于60us
	EA = 1;
	return Bit;
}

//发送一个Byte
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i = 0;
	for(i = 0; i < 8; i++)
	{
		Onewire_SendBit(Byte & (0x01<<i));
	}
}

//接收一个Byte
unsigned char OneWire_ReceiveByte()
{
	unsigned char Byte = 0;
	unsigned char i = 0;
	for(i = 0; i < 8; i++)
	{
		if(Onewire_ReceiveBit())
		{
			Byte |= (0x01<<i);
		}
	}
	return Byte;
}
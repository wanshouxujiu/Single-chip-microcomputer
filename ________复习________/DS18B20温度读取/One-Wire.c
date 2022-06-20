#include <REGX52.H>

sbit OneWire_DQ = P3^7;

//起始
unsigned char OneWire_Start()
{
	unsigned char i,AckBit;
	OneWire_DQ = 1;
	OneWire_DQ = 0;
	i = 221;while (--i);      //480us
	OneWire_DQ = 1;
	i = 29;while (--i);       //65us
	AckBit = OneWire_DQ;
	i = 221;while (--i);      //480us,等待从机
	
	return AckBit;
}

////发送bit
//void Onewire_SendBit(unsigned char Bit)
//{
//	unsigned char i;
//	OneWire_DQ = 0;
//	i = 4;while (--i);          //Dealy 10us,因为如果发送1，需要先延时1~15us
//	OneWire_DQ = Bit;
//	i = 23;while (--i); //再Dealy 50us,因为如果发送0，需要保持60~120us
//	OneWire_DQ = 1;
//}

////发送Byte
//void OneWire_Sendbyte(unsigned char Data)
//{
//	unsigned char j;
//	for(j = 0; j < 8; j++)
//	{
//		Onewire_SendBit(Data & 0x01<<j);
//	}
//}

//发送byte 失败
void OneWire_Sendbyte(unsigned char Data)
{
	unsigned char j,i;
	for(j = 0; j < 8; j++)
	{
		OneWire_DQ = 0;
		i = 4;while (--i);          //Dealy 10us,因为如果发送1，需要先延时1~15us
		OneWire_DQ = (Data & (0x01<<j))?1:0;
		i = 23;while (--i); //再Dealy 50us,因为如果发送0，需要保持60~120us
		OneWire_DQ = 1;
	}
}

//接收Byte
unsigned char OneWire_Receivebyte()
{
	unsigned char i,j,Data = 0;
	for(j = 0; j < 8; j++)
	{
		OneWire_DQ = 0;
		i = 2;while (--i);            //5us
		OneWire_DQ = 1;
		i = 4;while (--i);            //10us
		if(OneWire_DQ)
		{
			Data |= (0x01<<j);
		}
		i = 21;while (--i);           //45us
	}
	return Data;
}
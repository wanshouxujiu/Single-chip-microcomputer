#include <REGX52.H>
#include <OneWire.h>

#define DS18B20_SKIP_ROM          0xCC
#define DS18B20_CONVERT_T         0x44
#define DS18B20_READ_SCARTCHPAD   0xBE

void DS18B20_ConvertT()
{
	OneWire_Init();
	Onewire_SendByte(DS18B20_SKIP_ROM);
	Onewire_SendByte(DS18B20_CONVERT_T);
}

float DS18B20_ReadT()
{
	unsigned char TLSB = 0,TMSB = 0;
	int Temp;
	float T;
	OneWire_Init();
	Onewire_SendByte(DS18B20_SKIP_ROM);
	Onewire_SendByte(DS18B20_READ_SCARTCHPAD);
	TLSB = Onewire_ReceiveByte();
	TMSB = Onewire_ReceiveByte();
	Temp = (TMSB<<8) | TLSB;
	T = Temp/16.0;
	return T;
}
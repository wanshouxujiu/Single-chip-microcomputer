#include <REGX52.H>
#include "One-Wire.h"

#define DS18B20_SKIP_ROM            0xCC    //跳过ROM指令
#define DS18B20_CONVERT_T           0x44    //温度变化
#define DS18B20_READ_SCRATCHPAD     0xBE    //读暂存器

void DS18B20_ConvertT()
{
	OneWire_Start();
	OneWire_Sendbyte(DS18B20_SKIP_ROM);
	OneWire_Sendbyte(DS18B20_CONVERT_T);
}

float DS18B20_ReadT()
{
	unsigned char LByte,MByte;
	int Tmp = 0;
	float T = 0;
	OneWire_Start();
	OneWire_Sendbyte(DS18B20_SKIP_ROM);
	OneWire_Sendbyte(DS18B20_READ_SCRATCHPAD);
	LByte = OneWire_Receivebyte();
	MByte = OneWire_Receivebyte();
	Tmp = (MByte<<8) | LByte; //int类型2byte，把补码放进去正好自动转换正负
	T = Tmp/16.0;                 //放入浮点类型并转为正确大小
	
	return T;
}
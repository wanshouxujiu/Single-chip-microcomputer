#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__

unsigned char OneWire_Start();
void OneWire_Sendbyte(unsigned char Data);
unsigned char OneWire_Receivebyte();

#endif
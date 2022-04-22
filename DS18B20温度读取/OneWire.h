#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__

unsigned char OneWire_Init();
void Onewire_SendBit(unsigned char Bit);
unsigned char OneWire_ReceiveBit();
void Onewire_SendByte(unsigned char Byte);
unsigned char OneWire_ReceiveByte();

#endif
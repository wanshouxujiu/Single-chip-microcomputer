#ifndef __IIC_H__
#define __IIC_H__

void IIC_Start();
void IIC_Stop();
void IIC_SendByte(unsigned char Data);
unsigned char IIC_ReceiveByte();
void IIC_SendAck(bit Ack);
bit IIC_ReceiveAck();

#endif
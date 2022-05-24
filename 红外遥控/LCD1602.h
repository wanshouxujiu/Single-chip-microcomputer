#ifndef __LCD1602_H__
#define __LCD1602_H__

void LCD_Init();
void LCD_WriteCommand(unsigned char commend);
void LCD_ShowChar(unsigned char Line,Column,Char);
void LCD_ShowString(unsigned char Line,Column,unsigned char* String);
void LCD_ShowNum(unsigned char Line,Column,unsigned int Number,unsigned char Lenth);
void LCD_ShowSignedNum(unsigned char Line,Column,int Number,unsigned char Lenth);
void LCD_ShowHexNum(unsigned char Line,Column,unsigned int Number,unsigned char Lenth);
void LCD_ShowBinNum(unsigned char Line,Column,unsigned int Number,unsigned char Lenth);

#endif
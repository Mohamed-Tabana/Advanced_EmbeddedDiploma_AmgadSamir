/*
 * LCD.c
 *
 *  Created on: Sep 28, 2023
 *      Author: Mohamed TABANA
 */


#include "LCD.h"
extern PinConfig_t LCD_RS;
extern PinConfig_t LCD_EN;
extern PinConfig_t LCD_D4;
extern PinConfig_t LCD_D5;
extern PinConfig_t LCD_D6;
extern PinConfig_t LCD_D7;

#if LCD_MODE == _4_BIT
void LCD_Init(void){
	STK_Delay_ms(50);
	LCD_writeInstruction(0x02);
	LCD_writeInstruction(0x28); // screen on - 4 bit mode
	LCD_writeInstruction(0x0C); // screen FULL - Cursor OFF (0F/0E)
	LCD_writeInstruction(0x01); // clear Screen
	STK_Delay_ms(1);
	LCD_writeInstruction(0x06); // SHIFT TO RIGHT - NO SHIFT
}
void LCD_writeInstruction(uint8_t ins){
	GPIO_vSetOutputPinValue(LCD_RS.PIN_Port,LCD_RS.PIN_Number,OUTPUT_LOW);
	GPIO_vSetOutputPinValue(LCD_D7.PIN_Port,LCD_D7.PIN_Number,READ_BIT(ins,7));
	GPIO_vSetOutputPinValue(LCD_D6.PIN_Port,LCD_D6.PIN_Number,READ_BIT(ins,6));
	GPIO_vSetOutputPinValue(LCD_D5.PIN_Port,LCD_D5.PIN_Number,READ_BIT(ins,5));
	GPIO_vSetOutputPinValue(LCD_D4.PIN_Port,LCD_D4.PIN_Number,READ_BIT(ins,4));
	GPIO_vSetOutputPinValue(LCD_EN.PIN_Port,LCD_EN.PIN_Number,OUTPUT_HIGH);
	STK_Delay_ms(1);

	GPIO_vSetOutputPinValue(LCD_EN.PIN_Port,LCD_EN.PIN_Number,OUTPUT_LOW);
	STK_Delay_ms(1);
	GPIO_vSetOutputPinValue(LCD_D7.PIN_Port,LCD_D7.PIN_Number,READ_BIT(ins,3));
	GPIO_vSetOutputPinValue(LCD_D6.PIN_Port,LCD_D6.PIN_Number,READ_BIT(ins,2));
	GPIO_vSetOutputPinValue(LCD_D5.PIN_Port,LCD_D5.PIN_Number,READ_BIT(ins,1));
	GPIO_vSetOutputPinValue(LCD_D4.PIN_Port,LCD_D4.PIN_Number,READ_BIT(ins,0));
	GPIO_vSetOutputPinValue(LCD_EN.PIN_Port,LCD_EN.PIN_Number,OUTPUT_HIGH);
	STK_Delay_ms(1);
	GPIO_vSetOutputPinValue(LCD_EN.PIN_Port,LCD_EN.PIN_Number,OUTPUT_LOW);
	STK_Delay_ms(1);
}
void LCD_WriteData(uint8_t data)
{
	GPIO_vSetOutputPinValue(LCD_RS.PIN_Port,LCD_RS.PIN_Number,OUTPUT_HIGH);
	GPIO_vSetOutputPinValue(LCD_D7.PIN_Port,LCD_D7.PIN_Number,READ_BIT(data,7));
	GPIO_vSetOutputPinValue(LCD_D6.PIN_Port,LCD_D6.PIN_Number,READ_BIT(data,6));
	GPIO_vSetOutputPinValue(LCD_D5.PIN_Port,LCD_D5.PIN_Number,READ_BIT(data,5));
	GPIO_vSetOutputPinValue(LCD_D4.PIN_Port,LCD_D4.PIN_Number,READ_BIT(data,4));
	GPIO_vSetOutputPinValue(LCD_EN.PIN_Port,LCD_EN.PIN_Number,OUTPUT_HIGH);
	STK_Delay_ms(1);

	GPIO_vSetOutputPinValue(LCD_EN.PIN_Port,LCD_EN.PIN_Number,OUTPUT_LOW);
	STK_Delay_ms(1);
	GPIO_vSetOutputPinValue(LCD_D7.PIN_Port,LCD_D7.PIN_Number,READ_BIT(data,3));
	GPIO_vSetOutputPinValue(LCD_D6.PIN_Port,LCD_D6.PIN_Number,READ_BIT(data,2));
	GPIO_vSetOutputPinValue(LCD_D5.PIN_Port,LCD_D5.PIN_Number,READ_BIT(data,1));
	GPIO_vSetOutputPinValue(LCD_D4.PIN_Port,LCD_D4.PIN_Number,READ_BIT(data,0));
	GPIO_vSetOutputPinValue(LCD_EN.PIN_Port,LCD_EN.PIN_Number,OUTPUT_HIGH);
	STK_Delay_ms(1);
	GPIO_vSetOutputPinValue(LCD_EN.PIN_Port,LCD_EN.PIN_Number,OUTPUT_LOW);
	STK_Delay_ms(1);

}

#endif

void LCD_Clear(void){
	LCD_writeInstruction(0x01);
}

void LCD_WriteChar(uint8_t ch)
{
	LCD_WriteData(ch);
}
void LCD_WriteNumber(int32_t num)
{
	uint8_t flag=0;
	uint8_t digit[8];
	uint8_t i;
	if(num<0)
	{
		flag=1;
	}
	if(num==0)
	{
		LCD_WriteChar('0');
	}
	if(flag==1){
		num=num*-1;
	}
	for(i=0;num;i++)
	{
	digit[i] =num%10+'0';
	num=num/10;
	}
	if(flag==1)
	{
		LCD_WriteChar('-');
	}
	for(;i>0;i--)
	{
		LCD_WriteChar(digit[i-1]);
	}
}
void LCD_WriteBinary(uint8_t num)
{
	LCD_WriteChar('0');
	LCD_WriteChar('b');
	for(uint8_t i =0;i<8;i++)
	{
		LCD_WriteNumber( (num>>(7-i)) & 1);
	}
}
void LCD_WriteHex(uint16_t num)
{
	uint8_t Remainder[8];
	uint8_t i=0;
	for(i=0;num !=0;i++)
	{
		if(num%16 >9)
		{
			Remainder[i]=((num%16)-10)+'A';
		}
		else
		{
			Remainder[i]=num%16;
		}
		num=num/16;
	}
	LCD_WriteChar('0');
	LCD_WriteChar('x');
	for(;i>0;i--)
	{
		if(Remainder[i-1]<10)
		{
		LCD_WriteNumber(Remainder[i-1]);
		}
		else
		{
		LCD_WriteChar(Remainder[i-1]);
		}
	}


}
void LCD_SetCursor(uint8_t line,uint8_t cell)
{
	if(line==0)
	{
		LCD_writeInstruction(0x80 | cell);
	}
	else if(line==1)
	{
		LCD_writeInstruction(0x80 | 0x40 |cell);
	}

}
void LCD_WriteString(uint8_t* str)
{
	for(uint8_t i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
}
void LCD_WriteNumber_4D(uint16_t num)
{
	LCD_WriteNumber((num%10000)/1000);
	LCD_WriteNumber((num%1000)/100);
	LCD_WriteNumber((num%100)/10);
	LCD_WriteNumber((num%10)/1);
}
void LCD_createPattern(uint8_t* pattern,uint8_t address)
{
	LCD_writeInstruction(0x40|(address*8));
	for(uint8_t i=0 ;i<8;i++)
	{
	LCD_WriteData(pattern[i]);
	}
	LCD_writeInstruction(0x80);
}
void LCD_SetCursorClear(uint8_t line, uint8_t cell,uint8_t numOfCells)
{
	LCD_SetCursor(line,cell);
	for(uint8_t i=0;i<numOfCells;i++)
	{
		LCD_WriteChar(' ');
	}
	LCD_SetCursor(line,cell);
}
void LCD_SetCursorWriteString(uint8_t line, uint8_t cell,uint8_t* str)
{
	LCD_SetCursor(line,cell);
	LCD_WriteString(str);
}

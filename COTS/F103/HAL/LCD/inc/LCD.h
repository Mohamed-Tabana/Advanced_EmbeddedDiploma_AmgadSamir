/*
 * LCD.h
 *
 *  Created on: Sep 28, 2023
 *      Author: Mohamed TABANA
 */

#ifndef LCD_H_
#define LCD_H_

#include "GPIO_int.h"
#include "SysTick_int.h"

#define _4_BIT 1
#define LCD_MODE _4_BIT


void LCD_Init(void);
void LCD_writeInstruction(uint8_t ins);
void LCD_WriteData(uint8_t data);
void LCD_Clear(void);

void LCD_WriteChar(uint8_t ch);
void LCD_WriteNumber(int32_t num);
void LCD_WriteBinary(uint8_t num);
void LCD_WriteHex(uint16_t num);
void LCD_SetCursor(uint8_t line,uint8_t cell);
void LCD_WriteString(uint8_t* str);
void LCD_WriteNumber_4D(uint16_t num);
void LCD_createPattern(uint8_t* pattern,uint8_t address);
void LCD_SetCursorClear(uint8_t line, uint8_t cell,uint8_t numOfCells);
void LCD_SetCursorWriteString(uint8_t line, uint8_t cell,uint8_t* str);

#endif /* LCD_H_ */

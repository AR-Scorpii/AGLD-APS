#ifndef __PERI_LCD_H__
#define __PERI_LCD_H__

#include <stdint.h>
#include "../mcu/spi.h"
#include "../mcu/delay.h"
// #include "lcd_char.h"
#ifdef _DEBUG
#include <stdio.h>
#endif

typedef struct LCD_Char_Mono16_s
{
    char character;
    uint8_t w;
    uint8_t h;
    uint8_t mask[16];
} LCD_Char_Mono16_t; 

/**
 * CONNECTION: 
 * CS   -   P1.1
 * SDA  -   P1.3/MOSI
 * SCL  -   P1.5/SCLK
 * RST  -   P1.6
 * DC   -   P1.7
 */

// #define LCD_WIDTH       160u
// #define LCD_HEIGHT      128u
// #define LCD_OFFSET_X    0u
// #define LCD_OFFSET_Y    0u

typedef enum LCD_Rot_e
{
    LCD_Rot_0   = 0x06,
    LCD_Rot_90  = 0x05,
    LCD_Rot_180 = 0x00,
    LCD_Rot_270 = 0x03
} LCD_Rot_t;

void LCD_CmdSend(uint8_t);
void LCD_DatSend(uint8_t);
void LCD_D16Send(uint16_t);

void LCD_Reset(void);
void LCD_Init(LCD_Rot_t);

void LCD_WindowSet(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
void LCD_Fill(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color);
uint8_t LCD_CharDisplay(uint8_t x, uint8_t y, char dat, uint8_t fontsize, uint16_t color);
uint8_t LCD_CharOverride(uint8_t x, uint8_t y, char dat, uint8_t fontsize, uint16_t color, uint16_t background);
void LCD_StrOverride(uint8_t x, uint8_t y, char * dat, uint8_t fontsize, uint16_t color, uint16_t background);

#endif
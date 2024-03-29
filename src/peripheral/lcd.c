#include "lcd.h"

uint8_t LCD_WIDTH = 160u;
uint8_t LCD_HEIGHT = 128u;
uint8_t LCD_OFFSET_X = 0u;
uint8_t LCD_OFFSET_Y = 0u;

CODE LCD_Char_Mono16_t LCD_Char_Mono16[37] = 
{
    {' ', 8, 16, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
    {'0', 8, 16, {0x00,0x38,0x6C,0xC6,0x82,0x82,0xE2,0xB2,0x9A,0x8E,0x82,0x82,0xC6,0x6C,0x38,0x00}}, 
    {'1', 8, 16, {0x00,0x30,0x3C,0x36,0x32,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x00}}, 
    {'2', 8, 16, {0x00,0x38,0x6C,0xC6,0x80,0xC0,0xC0,0x60,0x30,0x18,0x0C,0x04,0x06,0x06,0xFE,0x00}}, 
    {'3', 8, 16, {0x00,0x38,0x6C,0xC6,0xC0,0xC0,0x60,0x38,0x60,0xC0,0x80,0x82,0xC6,0xEC,0x78,0x00}}, 
    {'4', 8, 16, {0x00,0x60,0x20,0x30,0x10,0x18,0x08,0x6C,0x64,0x66,0xFE,0x60,0x60,0x60,0x60,0x00}}, 
    {'5', 8, 16, {0x00,0xFE,0x06,0x06,0x06,0x06,0x7E,0x6E,0xC6,0x80,0x80,0x80,0xC6,0x6C,0x38,0x00}}, 
    {'6', 8, 16, {0x00,0x30,0x10,0x18,0x08,0x0C,0x3C,0x6E,0xC6,0x82,0x82,0x82,0xC6,0x6C,0x38,0x00}}, 
    {'7', 8, 16, {0x00,0xFE,0xC0,0xC0,0x40,0x60,0x60,0x20,0x20,0x30,0x10,0x10,0x18,0x18,0x08,0x00}}, 
    {'8', 8, 16, {0x00,0x38,0x6C,0xC6,0xC6,0x44,0x6C,0x38,0x38,0x6C,0xC6,0x82,0xC6,0xEE,0x7C,0x00}}, 
    {'9', 8, 16, {0x00,0x38,0x6C,0xC6,0x82,0x82,0xC6,0xC6,0xFC,0x40,0x60,0x20,0x30,0x10,0x18,0x00}}, 
    {'A', 8, 16, {0x00,0x10,0x38,0x28,0x28,0x28,0x28,0x6C,0x44,0x44,0x7C,0x44,0xC6,0xC6,0x82,0x00}}, 
    {'B', 8, 16, {0x00,0x3E,0x66,0xC6,0xC6,0xC6,0x46,0x3E,0x66,0xC6,0x86,0x86,0xC6,0x66,0x3E,0x00}}, 
    {'C', 8, 16, {0x00,0x38,0x6C,0xC6,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0xC6,0x6C,0x38,0x00}}, 
    {'D', 8, 16, {0x00,0x3E,0x66,0xC6,0x86,0x86,0x86,0x86,0x86,0x86,0x86,0x86,0xC6,0x66,0x3E,0x00}}, 
    {'E', 8, 16, {0x00,0xFE,0x06,0x06,0x06,0x06,0x06,0x7E,0x06,0x06,0x06,0x06,0x06,0x06,0xFE,0x00}}, 
    {'F', 8, 16, {0x00,0xFC,0x04,0x04,0x04,0x04,0x04,0x7C,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00}}, 
    {'G', 8, 16, {0x00,0x38,0x6C,0xC6,0x02,0x02,0x02,0xF2,0xC2,0xC2,0xC2,0xC2,0xC6,0xAE,0xBC,0x00}}, 
    {'H', 8, 16, {0x00,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xFE,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x00}}, 
    {'I', 8, 16, {0x00,0xFE,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xFE,0x00}}, 
    {'J', 8, 16, {0x00,0x70,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x42,0x66,0x3C,0x00}}, 
    {'K', 8, 16, {0x00,0xC6,0x46,0x66,0x36,0x36,0x1E,0x1E,0x1E,0x16,0x36,0x26,0x66,0x46,0xC6,0x00}}, 
    {'L', 8, 16, {0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0xFC,0x00}}, 
    {'M', 8, 16, {0x00,0xC6,0xC6,0xC6,0xC6,0xAA,0xAA,0xAA,0xAA,0x92,0x92,0x82,0x82,0x82,0x82,0x00}}, 
    {'N', 8, 16, {0x00,0xC6,0xC6,0xCE,0xCA,0xCA,0xDE,0xD6,0xD6,0xF6,0xA6,0xA6,0xE6,0xC6,0xC6,0x00}}, 
    {'O', 8, 16, {0x00,0x38,0x6C,0xC6,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0xC6,0x6C,0x38,0x00}}, 
    {'P', 8, 16, {0x00,0x7E,0xE6,0xC6,0x86,0x86,0x86,0xC6,0x7E,0x06,0x06,0x06,0x06,0x06,0x06,0x00}}, 
    {'Q', 8, 16, {0x00,0x38,0x6C,0xC6,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0xC6,0xC6,0x7C,0x10}}, 
    {'R', 8, 16, {0x00,0x3E,0x66,0xC6,0x86,0x86,0xC6,0xC6,0x7E,0x36,0x26,0x66,0x46,0xC6,0x86,0x00}}, 
    {'S', 8, 16, {0x00,0x38,0x6C,0xC6,0x06,0x06,0x04,0x18,0x70,0x40,0xC0,0x80,0xC6,0x6E,0x3C,0x00}}, 
    {'T', 8, 16, {0x00,0xFE,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00}}, 
    {'U', 8, 16, {0x00,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x6C,0x38,0x00}}, 
    {'V', 8, 16, {0x00,0x82,0xC6,0xC6,0x44,0x44,0x44,0x44,0x6C,0x28,0x28,0x28,0x28,0x38,0x10,0x00}}, 
    {'W', 8, 16, {0x00,0x82,0x82,0x82,0x82,0x92,0x92,0x92,0xEE,0x6C,0x6C,0x6C,0x6C,0x6C,0x6C,0x00}}, 
    {'X', 8, 16, {0x00,0xC6,0xC6,0x44,0x6C,0x28,0x38,0x10,0x10,0x38,0x28,0x6C,0x44,0xC6,0xC6,0x00}}, 
    {'Y', 8, 16, {0x00,0x82,0xC6,0x44,0x44,0x6C,0x28,0x38,0x38,0x10,0x10,0x10,0x10,0x10,0x10,0x00}}, 
    {'Z', 8, 16, {0x00,0xFE,0xC0,0x40,0x60,0x20,0x30,0x30,0x18,0x18,0x08,0x0C,0x04,0x06,0xFE,0x00}}
};

void LCD_CmdSend(uint8_t cmd)
{
    P17 = 0;
    P11 = 0;

    SPI_CharSend(cmd);

    P11 = 1;
}

void LCD_DatSend(uint8_t dat)
{
    P17 = 1;
    P11 = 0;

    SPI_CharSend(dat);

    P11 = 1;
}

void LCD_D16Send(uint16_t dat)
{
    P17 = 1;
    P11 = 0;

    SPI_CharSend((dat & 0xFF00) >> 8);
    SPI_CharSend((dat & 0x00FF));

    P11 = 1;
}

void LCD_Reset(void)
{
    // RESET
    P16 = 1;
    delay_ms(50);
    P16 = 0;
    delay_ms(50);
    P16 = 1;
    delay_ms(50);
}

void LCD_Init(LCD_Rot_t rot)
{
    SPI_Init(SPI_PinSet_1, SPI_Speed_Divider_2);
    P11 = 1;

    LCD_Reset();

    LCD_CmdSend(0x11);//Sleep exit 
    delay_ms(120);

    //ST7735R Frame Rate
    LCD_CmdSend(0xB1); 
    LCD_DatSend(0x01); 
    LCD_DatSend(0x2C); 
    LCD_DatSend(0x2D); 
    LCD_CmdSend(0xB2); 
    LCD_DatSend(0x01); 
    LCD_DatSend(0x2C); 
    LCD_DatSend(0x2D); 
    LCD_CmdSend(0xB3); 
    LCD_DatSend(0x01); 
    LCD_DatSend(0x2C); 
    LCD_DatSend(0x2D); 
    LCD_DatSend(0x01); 
    LCD_DatSend(0x2C); 
    LCD_DatSend(0x2D); 	
    LCD_CmdSend(0xB4); //Column inversion 
    LCD_DatSend(0x07); 	
    //ST7735R Power Sequence
    LCD_CmdSend(0xC0); 
    LCD_DatSend(0xA2); 
    LCD_DatSend(0x02); 
    LCD_DatSend(0x84); 
    LCD_CmdSend(0xC1); 
    LCD_DatSend(0xC5); 
    LCD_CmdSend(0xC2); 
    LCD_DatSend(0x0A); 
    LCD_DatSend(0x00); 
    LCD_CmdSend(0xC3); 
    LCD_DatSend(0x8A); 
    LCD_DatSend(0x2A); 
    LCD_CmdSend(0xC4); 
    LCD_DatSend(0x8A); 
    LCD_DatSend(0xEE); 
    LCD_CmdSend(0xC5); //VCOM 
    LCD_DatSend(0x0E); 	
    LCD_CmdSend(0x36); //MX, MY, RGB mode 
    LCD_DatSend(0xC0); 
    //ST7735R Gamma Sequence
    LCD_CmdSend(0xe0); 
    LCD_DatSend(0x0f); 
    LCD_DatSend(0x1a); 
    LCD_DatSend(0x0f); 
    LCD_DatSend(0x18); 
    LCD_DatSend(0x2f); 
    LCD_DatSend(0x28); 
    LCD_DatSend(0x20); 
    LCD_DatSend(0x22); 
    LCD_DatSend(0x1f); 
    LCD_DatSend(0x1b); 
    LCD_DatSend(0x23); 
    LCD_DatSend(0x37); 
    LCD_DatSend(0x00); 	
    LCD_DatSend(0x07); 
    LCD_DatSend(0x02); 
    LCD_DatSend(0x10); 
    LCD_CmdSend(0xe1); 
    LCD_DatSend(0x0f); 
    LCD_DatSend(0x1b); 
    LCD_DatSend(0x0f); 
    LCD_DatSend(0x17); 
    LCD_DatSend(0x33); 
    LCD_DatSend(0x2c); 
    LCD_DatSend(0x29); 
    LCD_DatSend(0x2e); 
    LCD_DatSend(0x30); 
    LCD_DatSend(0x30); 
    LCD_DatSend(0x39); 
    LCD_DatSend(0x3f); 
    LCD_DatSend(0x00); 
    LCD_DatSend(0x07); 
    LCD_DatSend(0x03); 
    LCD_DatSend(0x10);  	
    LCD_CmdSend(0x2a);
    LCD_DatSend(0x00);
    LCD_DatSend(0x00);
    LCD_DatSend(0x00);
    LCD_DatSend(0x7f);
    LCD_CmdSend(0x2b);
    LCD_DatSend(0x00);
    LCD_DatSend(0x00);
    LCD_DatSend(0x00);
    LCD_DatSend(0x9f);
    LCD_CmdSend(0xF0); //Enable test command  
    LCD_DatSend(0x01); 
    LCD_CmdSend(0xF6); //Disable ram power save mode 
    LCD_DatSend(0x00); 	
    LCD_CmdSend(0x3A); //65k mode 
    LCD_DatSend(0x05); 
    LCD_CmdSend(0x29); //display on	

    // horizontal
    LCD_CmdSend(0x36);
    LCD_DatSend((rot << 5) | (0x01 << 3)); // RGB

    switch (rot)
    {
        case LCD_Rot_0:
            LCD_WIDTH       = 128u;
            LCD_HEIGHT      = 160u;
            LCD_OFFSET_X    = 0u;
            LCD_OFFSET_Y    = 0u;
            break;
        case LCD_Rot_90:
            LCD_WIDTH       = 160u;
            LCD_HEIGHT      = 128u;
            LCD_OFFSET_X    = 0u;
            LCD_OFFSET_Y    = 0u;
            break;
        case LCD_Rot_180:
            LCD_WIDTH       = 128u;
            LCD_HEIGHT      = 160u;
            LCD_OFFSET_X    = 0u;
            LCD_OFFSET_Y    = 0u;
            break;
        case LCD_Rot_270:
            LCD_WIDTH       = 160u;
            LCD_HEIGHT      = 128u;
            LCD_OFFSET_X    = 0u;
            LCD_OFFSET_Y    = 0u;
            break;
        default:
            LCD_WIDTH       = 128u;
            LCD_HEIGHT      = 160u;
            LCD_OFFSET_X    = 0u;
            LCD_OFFSET_Y    = 0u;
            break;
    }

#   ifdef _DEBUG
    printf("[LCD] inited\n");
#   endif
}

void LCD_WindowSet(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
    LCD_CmdSend(0x2Au);	
    LCD_DatSend(0x00u);
    LCD_DatSend(x+LCD_OFFSET_X);		
    LCD_DatSend(0x00u);
    LCD_DatSend(x+w+LCD_OFFSET_X-1);

    LCD_CmdSend(0x2Bu);	
    LCD_DatSend(0x00u);
    LCD_DatSend(y+LCD_OFFSET_Y);
    LCD_DatSend(0x00u);
    LCD_DatSend(y+h+LCD_OFFSET_Y-1);
}

void LCD_Fill(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color)
{

// #   ifdef _DEBUG
//     printf("[LCD] filling area (x,y,w,h)=(%d,%d,%d,%d)\n", x, y, w, h);
// #   endif

    LCD_WindowSet(x, y, w, h);

    LCD_CmdSend(0x2Cu);
    for (uint16_t cy = y; cy <= y+h; cy++)
    {
        for (uint16_t cx = x; cx <= x+w; cx++)
        {
            LCD_D16Send(color);
        }
    }

    // LCD_WindowSet(0, 0, LCD_WIDTH, LCD_HEIGHT);
    // LCD_CmdSend(0x2Cu);
}

uint8_t LCD_CharDisplay(uint8_t x, uint8_t y, char dat, uint8_t fontsize, uint16_t color)
{
    uint8_t tmp[16] = {0x00};
    uint8_t rtn = 0;

    for (uint8_t i = 0; i < 37; i++)
    {
        if (dat == LCD_Char_Mono16[i].character)
        {
            rtn = LCD_Char_Mono16[i].w;

            for (uint8_t j = 0; j < fontsize; j++)
            {
                tmp[j] = LCD_Char_Mono16[i].mask[j];
            }
            break;
        }
    }

// #   ifdef _DEBUG
//     printf("[LCD] displaying character <%c> at (x,y)=(%d,%d)\n", dat, x, y);
// #   endif

    for (uint16_t cy = 0; cy < 16; cy++)
    {
        for (uint16_t cx = 0; cx < 8; cx++)
        {
            if ((tmp[cy] & (0x01<<cx)) != 0)
            {
                LCD_WindowSet(x+cx, y+cy, 1, 1);
                LCD_CmdSend(0x2Cu);
                LCD_D16Send(color);
            }
        }
    }

    return rtn;
}

uint8_t LCD_CharOverride(uint8_t x, uint8_t y, char dat, uint8_t fontsize, uint16_t color, uint16_t background)
{
    uint8_t tmp[16] = {0x00};
    uint8_t rtn = 0;

    for (uint8_t i = 0; i < 37; i++)
    {
        if (dat == LCD_Char_Mono16[i].character)
        {
            rtn = LCD_Char_Mono16[i].w;

            for (uint8_t j = 0; j < fontsize; j++)
            {
                tmp[j] = LCD_Char_Mono16[i].mask[j];
            }
            break;
        }
    }
    
// #   ifdef _DEBUG
//     printf("[LCD] displaying character <%c> at (x,y)=(%d,%d)\n", dat, x, y);
// #   endif

    LCD_WindowSet(x, y, 8, 16);

    LCD_CmdSend(0x2Cu);
    for (uint16_t cy = 0; cy < 16; cy++)
    {
        for (uint16_t cx = 0; cx < 8; cx++)
        {
            if ((tmp[cy] & (0x01<<cx)) != 0)
            {
                LCD_D16Send(color);
            }
            else
            {
                LCD_D16Send(background);
            }
        }
    }

    return rtn;
}

void LCD_StrOverride(uint8_t x, uint8_t y, char * dat, uint8_t fontsize, uint16_t color, uint16_t background)
{
    uint8_t i = 0;
    uint8_t cx = x;
    
// #   ifdef _DEBUG
//     printf("[LCD] displaying string <%s> at (x,y)=(%d,%d)\n", dat, x, y);
// #   endif

    while (dat[i] != 0x00)
    {
        uint8_t dx = LCD_CharOverride(cx, y, dat[i], fontsize, color, background);
        cx += dx;
        i++;
    }
}
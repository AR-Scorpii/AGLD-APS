#ifndef __MCU_SPI_H__
#define __MCU_SPI_H__

#include "../../inc/stc8h.h"

typedef enum SPI_PinSet_e
{
                            // SS           MOSI    MISO    SCLK
    SPI_PinSet_1    = 0x00, // P1.2/P5.4    P1.3    P1.4    P1.5
    SPI_PinSet_2    = 0x01, // P2.2         P2.3    P2.4    P2.5
    SPI_PinSet_3    = 0x02, // P5.4         P4.0    P4.1    P4.3
    SPI_PinSet_4    = 0x03  // P3.5         P3.4    P3.3    P3.2
} SPI_PinSet_t;

typedef enum SPI_Speed_e
{
    SPI_Speed_Divider_4     = 0x00,
    SPI_Speed_Divider_8     = 0x01,
    SPI_Speed_Divider_16    = 0x02,
    SPI_Speed_Divider_2     = 0x03
} SPI_Speed_t;

void SPI_Init(SPI_PinSet_t, SPI_Speed_t);
void SPI_CharSend(char);



#endif
#include "spi.h"

void SPI_Init(SPI_PinSet_t pin, SPI_Speed_t speed)
{
    P_SW1 = (P_SW1 & ~0x0C) | (pin << 2); 

    // SPI init
    SPCTL = 0xD0 | speed;
    SPSTAT = 0xC0;
}

void SPI_CharSend(char dat)
{
    SPDAT = dat;
    while (!(SPSTAT & 0x80));
    SPSTAT = 0xC0;
}
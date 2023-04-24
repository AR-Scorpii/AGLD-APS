#include "delay.h"

void delay_ms(uint16_t ms)
{
    do
    {
        uint32_t i = FOSC / 10000;
        while (--i);
    } while (--ms);
}
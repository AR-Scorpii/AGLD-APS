#include "motor.h"

cuint8_t MOT_Phase[] = {0x33, 0x66, 0xCC, 0x99};

void MOT_Init(void)
{
    // ADC_Init();
}

uint8_t MOT_AtPosOn(void)
{
    uint16_t m = ADC_Sample(ADC_Channel_P05);
#   ifdef _DEBUG
    printf("[MOT] ADC value: %u\n", m);
#   endif
    if (m > 3072)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t MOT_AtPosOff(void)
{
    uint16_t m = ADC_Sample(ADC_Channel_P06);
#   ifdef _DEBUG
    printf("[MOT] ADC value: %u\n", m);
#   endif
    if (m > 3072)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t MOT_Move(MOT_Mov_t dir, uint8_t status)
{
    switch (dir)
    {
        case MOT_Mov_Clockwise:
            status --;
            status %= 4;
            break;
        case MOT_Mov_CounterClockwise:
            status ++;
            status %= 4;
        default: break;
    }

    // P2 = MOT_Phase[status];
    // P23 = ((MOT_Phase[status] & 0x08));
    P45 = ((MOT_Phase[status] & 0x08) >> 3);
    P27 = ((MOT_Phase[status] & 0x04) >> 2);
    P26 = ((MOT_Phase[status] & 0x02) >> 1);
    P25 = ((MOT_Phase[status] & 0x01) >> 0);
    // P25 = ((MOT_Phase[status] & 0x10) >> 4);
    // P26 = ((MOT_Phase[status] & 0x20) >> 5);
    // P27 = ((MOT_Phase[status] & 0x40) >> 6);
    // P45 = ((MOT_Phase[status] & 0x80) >> 7);
#   ifdef _DEBUG
    NOP(1);
    printf("[MOT] status: %u(%2X) - %d%d%d%d\n", status, MOT_Phase[status], P45, P27, P26, P25);
#   endif
    return status;
}

uint8_t MOT_On(uint8_t status)
{
    while (MOT_AtPosOn() == 0)
    {
#       ifdef _DEBUG
        printf("[MOT] status: %u\n", status);
#       endif
        status = MOT_Move(MOT_Mov_CounterClockwise, status); 
        delay_ms(50);
    }
    
    return status;
}

uint8_t MOT_Off(uint8_t status)
{
    while (MOT_AtPosOff() == 0)
    {
#       ifdef _DEBUG
        printf("[MOT] status: %u\n", status);
#       endif
        status = MOT_Move(MOT_Mov_Clockwise, status); 
        delay_ms(100);
    }

    return status;
}
#ifndef __PERI_MOTOR_H__
#define __PERI_MOTOR_H__

#ifdef _DEBUG
#include <stdio.h>
#endif

#include "../mcu/adc.h"
#include "../mcu/delay.h"

typedef enum MOT_Mov_e
{
    MOT_Mov_Clockwise           = 0,
    MOT_Mov_CounterClockwise    = 1
}MOT_Mov_t;

void MOT_Init(void);

uint8_t MOT_AtPosOn(void);
uint8_t MOT_AtPosOff(void);
uint8_t MOT_Move(MOT_Mov_t, uint8_t);
uint8_t MOT_On(uint8_t);
uint8_t MOT_Off(uint8_t);

#endif
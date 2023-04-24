#ifndef __MCU_PWM_H__
#define __MCU_PWM_H__

#include "../../inc/stc8h.h"

extern cuint32_t FOSC;

typedef enum PWM_x_e
{
    PWMA = 0x00FF,
    PWMB = 0x5500
}PWM_x_t;

typedef enum PWM_n_e
{
    PWM1  = 0x0001, PWMA_1  = 0x0001,
    PWM1N = 0x0002, PWMA_1N = 0x0002,
    PWM2  = 0x0004, PWMA_2  = 0x0004,
    PWM2N = 0x0008, PWMA_2N = 0x0008,
    PWM3  = 0x0010, PWMA_3  = 0x0010,
    PWM3N = 0x0020, PWMA_3N = 0x0020,
    PWM4  = 0x0040, PWMA_4  = 0x0040,
    PWM4N = 0x0080, PWMA_4N = 0x0080,
    PWM5  = 0x0100, PWMB_5  = 0x0100,
    PWM6  = 0x0400, PWMB_6  = 0x0400,
    PWM7  = 0x1000, PWMB_7  = 0x1000,
    PWM8  = 0x4000, PWMB_8  = 0x4000
}PWM_n_t;

typedef enum PWM_Polarity_e
{
    PWM_Polarity_HighActive = 0x00 << 1,
    PWM_Polarity_LowActive  = 0x01 << 1
}PWM_Polarity_t;

typedef enum PWM_Mode_e
{
    PWM_Mode_Freeze          = 0x00 << 4,
    PWM_Mode_PulseHigh       = 0x01 << 4,
    PWM_Mode_PulseLow        = 0x02 << 4,
    PWM_Mode_Invertor        = 0x03 << 4,
    PWM_Mode_ForceLow        = 0x04 << 4,
    PWM_Mode_ForceHigh       = 0x05 << 4,
    PWM_Mode_PwmSmallerLow   = 0x06 << 4,
    PWM_Mode_PwmSmallerHigh  = 0x07 << 4
}PWM_Mode_t;

void PWM_xInit(PWM_x_t x);
void PWM_xDeinit(PWM_x_t x);
void PWM_nInit(PWM_n_t n, PWM_Polarity_t polarity, PWM_Mode_t mode);
void PWM_nDeinit(PWM_n_t n);

void PWM_xArrSet(PWM_x_t x, uint16_t arr);
uint16_t PWM_xArrGet(PWM_x_t x);
void PWM_xFreqSet(PWM_x_t x, uint16_t freq);

void PWM_nCcrSet(PWM_n_t n, uint16_t ccr);
uint16_t PWM_nCcrGet(PWM_n_t n);
void PWM_nDutySet(PWM_n_t n, uint8_t duty);


#endif
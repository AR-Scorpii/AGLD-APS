#include "buzzer.h"

void BUZ_Init(void)
{
#   if defined BUZ_ON_P23
    PWMB_PS = 0x00;
    // PWMB_CCER2 = 0x00;
    // PWMB_CCMR4 = 0x60;
    // PWMB_CCER2 = 0x10;
    // PWMB_ENO = 0x40;
    PWM_nInit(PWM8, PWM_Polarity_HighActive, PWM_Mode_PwmSmallerLow);
#   endif
#   if defined BUZ_ON_P24
    PWMA_PS = 0x10;
    PWM_nInit(PWM3, PWM_Polarity_HighActive, PWM_Mode_PwmSmallerLow);
#   endif
}

void BUZ_Start(void)
{
#   if defined BUZ_ON_P23
    // PWMB_BKR = 0x80;
    // PWMB_CR1 = 0x01;
    PWM_xInit(PWMB);
#   endif
#   if defined BUZ_ON_P24
    PWM_xInit(PWMA);
#   endif
}

void BUZ_Stop(void)
{
#   if defined BUZ_ON_P23
    PWM_xDeinit(PWMB);
#   endif
#   if defined BUZ_ON_P24
    PWM_xDeinit(PWMA);
#   endif
}

void BUZ_Freq(uint16_t freq)
{
#   if defined BUZ_ON_P23
    PWM_xFreqSet(PWMB ,freq);
    PWM_nDutySet(PWM8, 50);
#   endif
#   if defined BUZ_ON_P24
    PWM_xFreqSet(PWMA ,freq);
    PWM_nDutySet(PWM3, 50);
#   endif

}

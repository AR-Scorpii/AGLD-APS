#ifndef __PERI_BUZZER_H__
#define __PERI_BUZZER_H__

#include "../../inc/stc8h.h"
#include "../mcu/pwm.h"

// #define BUZ_ON_P23
#define BUZ_ON_P24

void BUZ_Init(void);
void BUZ_Start(void);
void BUZ_Stop(void);
void BUZ_Freq(uint16_t note);

#endif
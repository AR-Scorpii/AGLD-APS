#ifndef __MCU_EEPROM_H__
#define __MCU_EEPROM_H__

#include "../../inc/stc8h.h"

extern cuint32_t FOSC;

void EEP_Init(void);
void EEP_SetTps(void);
void EEP_Trig(void);
void EEP_Idle(void);
uint8_t EEP_Read(uint16_t);
uint8_t EEP_ReadC(uint16_t);
void EEP_Write(uint16_t, uint8_t);
void EEP_Erase(uint8_t);

#endif
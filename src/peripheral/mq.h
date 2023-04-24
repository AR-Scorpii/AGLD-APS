#ifndef __PERI_MQ_H__
#define __PERI_MQ_H__

#include <math.h>

#ifdef _DEBUG
#include <stdio.h>
#endif

#include "../mcu/adc.h"
#include "../mcu/mdu.h"

void MQ_Init(void);
uint32_t MQ_ResistGet(void);
uint16_t MQ_ConcGet(void);

#endif
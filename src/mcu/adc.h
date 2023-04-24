#ifndef __MCU_ADC_H__
#define __MCU_ADC_H__

#include "../../inc/stc8h.h"

typedef enum ADC_Channel_e
{
    ADC_Channel_0     = 0x00,     ADC_Channel_P10   = 0x00, 
    ADC_Channel_1     = 0x01,     ADC_Channel_P11   = 0x01, 
    ADC_Channel_2     = 0x02,     ADC_Channel_P54   = 0x02,     ADC_Channel_P12   = 0x02, 
    ADC_Channel_3     = 0x03,     ADC_Channel_P13   = 0x03, 
    ADC_Channel_4     = 0x04,     ADC_Channel_P14   = 0x04, 
    ADC_Channel_5     = 0x05,     ADC_Channel_P15   = 0x05, 
    ADC_Channel_6     = 0x06,     ADC_Channel_P16   = 0x06, 
    ADC_Channel_7     = 0x07,     ADC_Channel_P17   = 0x07, 
    ADC_Channel_8     = 0x08,     ADC_Channel_P00   = 0x08, 
    ADC_Channel_9     = 0x09,     ADC_Channel_P01   = 0x09, 
    ADC_Channel_10    = 0x0A,     ADC_Channel_P02   = 0x0A, 
    ADC_Channel_11    = 0x0B,     ADC_Channel_P03   = 0x0B, 
    ADC_Channel_12    = 0x0C,     ADC_Channel_P04   = 0x0C, 
    ADC_Channel_13    = 0x0D,     ADC_Channel_P05   = 0x0D, 
    ADC_Channel_14    = 0x0E,     ADC_Channel_P06   = 0x0E, 
    ADC_Channel_Ref   = 0x0F
} ADC_Channel_t;

uint16_t ADC_BgvGet(void);
void ADC_Init(void);
uint16_t ADC_Sample(ADC_Channel_t);

#endif
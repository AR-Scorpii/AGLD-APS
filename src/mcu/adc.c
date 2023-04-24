#include "adc.h"

uint16_t ADC_BgvGet(void)
{
    uint16_t bgv;
    uint8_t * bgv_ptr;

    bgv_ptr = (cuint8_t *)0xFDF7;
    bgv = (*bgv_ptr) << 8;
    bgv_ptr = (cuint8_t *)0xFDF8;
    bgv |= (*bgv_ptr);

    if ((bgv < 1100) || (bgv > 1300))
    {
        bgv = 1190;
    }

    return bgv;
}

void ADC_Init(void)
{
    EAXSFR();

    // configure ADC internal timing
    // ADCTIM = 0xBF; // 1011,1111
    // ADCTIM = 0x2A;
    ADCTIM = 0x2F;

    // set ADC clock
    ADCCFG = 0x20;

    // enable ADC power
    ADC_CONTR = 0x80;
}

uint16_t ADC_Sample(ADC_Channel_t channel)
{
    ADC_RES = 0x00;
    ADC_RESL = 0x00;

    ADC_CONTR = (0xC0 | (channel & 0x0F));
    NOP(4);
    
    while (!(ADC_CONTR & 0x20));
    ADC_CONTR &= ~0x20;

    uint16_t val = (ADC_RES << 8) + ADC_RESL;
    return val;
}
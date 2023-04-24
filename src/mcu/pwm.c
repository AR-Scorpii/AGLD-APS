#include "pwm.h"

void PWM_xInit(PWM_x_t x)
{
    if ((x & PWMA) != 0)
    {
        PWMA_BKR |= 0x80;
        PWMA_CR1 |= 0x01;
    }
    if ((x & PWMB) != 0)
    {
        PWMB_BKR |= 0x80;
        PWMB_CR1 |= 0x01;
    }
}

void PWM_xDeinit(PWM_x_t x)
{
    if ((x & PWMA) != 0)
    {
        PWMA_BKR &= ~0x80;
        PWMA_CR1 &= ~0x01;
    }
    if ((x & PWMB) != 0)
    {
        PWMB_BKR &= ~0x80;
        PWMB_CR1 &= ~0x01;
    }
}

void PWM_nInit(PWM_n_t n, PWM_Polarity_t polarity, PWM_Mode_t mode)
{
    // disable channel
    if (n & PWM1 ) PWMA_CCER1 &= (~0x01); 
    if (n & PWM1N) PWMA_CCER1 &= (~0x04); 
    if (n & PWM2 ) PWMA_CCER1 &= (~0x10); 
    if (n & PWM2N) PWMA_CCER1 &= (~0x40); 
    if (n & PWM3 ) PWMA_CCER2 &= (~0x10); 
    if (n & PWM3N) PWMA_CCER2 &= (~0x10); 
    if (n & PWM4 ) PWMA_CCER2 &= (~0x40); 
    if (n & PWM4N) PWMA_CCER2 &= (~0x40); 
    if (n & PWM5 ) PWMB_CCER1 &= (~0x01); 
    if (n & PWM6 ) PWMB_CCER1 &= (~0x10); 
    if (n & PWM7 ) PWMB_CCER2 &= (~0x01); 
    if (n & PWM8 ) PWMB_CCER2 &= (~0x10); 
    // switch (n)
    // {
    //     case PWM1:  PWMA_CCER1 &= (~0x01); break;
    //     case PWM1N: PWMA_CCER1 &= (~0x04); break;
    //     case PWM2:  PWMA_CCER1 &= (~0x10); break;
    //     case PWM2N: PWMA_CCER1 &= (~0x40); break;
    //     case PWM3:  PWMA_CCER2 &= (~0x10); break;
    //     case PWM3N: PWMA_CCER2 &= (~0x10); break;
    //     case PWM4:  PWMA_CCER2 &= (~0x40); break;
    //     case PWM4N: PWMA_CCER2 &= (~0x40); break;
    //     case PWM5:  PWMB_CCER1 &= (~0x01); break;
    //     case PWM6:  PWMB_CCER1 &= (~0x10); break;
    //     case PWM7:  PWMB_CCER2 &= (~0x01); break;
    //     case PWM8:  PWMB_CCER2 &= (~0x10); break;
    //     default: break;
    // }

    // configure mode
    if (n & (PWM1|PWM1N))   PWMA_CCMR1 = (mode | 0x08);
    if (n & (PWM2|PWM2N))   PWMA_CCMR2 = (mode | 0x08);
    if (n & (PWM3|PWM3N))   PWMA_CCMR3 = (mode | 0x08);
    if (n & (PWM4|PWM4N))   PWMA_CCMR4 = (mode | 0x08);
    if (n &  PWM5       )   PWMB_CCMR1 = (mode | 0x08);
    if (n &  PWM6       )   PWMB_CCMR2 = (mode | 0x08);
    if (n &  PWM7       )   PWMB_CCMR3 = (mode | 0x08);
    if (n &  PWM8       )   PWMB_CCMR4 = (mode | 0x08);
    // switch (n)
    // {
    //     case PWM1:  
    //     case PWM1N: PWMA_CCMR1 = (mode | 0x08); break;
    //     case PWM2:  
    //     case PWM2N: PWMA_CCMR2 = (mode | 0x08); break;
    //     case PWM3:  
    //     case PWM3N: PWMA_CCMR3 = (mode | 0x08); break;
    //     case PWM4:  
    //     case PWM4N: PWMA_CCMR4 = (mode | 0x08); break;
    //     case PWM5:  PWMB_CCMR1 = (mode | 0x08); break;
    //     case PWM6:  PWMB_CCMR2 = (mode | 0x08); break;
    //     case PWM7:  PWMB_CCMR3 = (mode | 0x08); break;
    //     case PWM8:  PWMB_CCMR4 = (mode | 0x08); break;
    //     default: break;
    // }

    // enable channel
    if (n & PWM1 )  PWMA_CCER1 = (PWMA_CCER1 & (~0x03) | ((polarity | 0x01) << 0));
    if (n & PWM1N)  PWMA_CCER1 = (PWMA_CCER1 & (~0x0C) | ((polarity | 0x01) << 2));
    if (n & PWM2 )  PWMA_CCER1 = (PWMA_CCER1 & (~0x30) | ((polarity | 0x01) << 4));
    if (n & PWM2N)  PWMA_CCER1 = (PWMA_CCER1 & (~0xC0) | ((polarity | 0x01) << 6));
    if (n & PWM3 )  PWMA_CCER2 = (PWMA_CCER2 & (~0x03) | ((polarity | 0x01) << 0));
    if (n & PWM3N)  PWMA_CCER2 = (PWMA_CCER2 & (~0x0C) | ((polarity | 0x01) << 2));
    if (n & PWM4 )  PWMA_CCER2 = (PWMA_CCER2 & (~0x30) | ((polarity | 0x01) << 4));
    if (n & PWM4N)  PWMA_CCER2 = (PWMA_CCER2 & (~0xC0) | ((polarity | 0x01) << 6));
    if (n & PWM5 )  PWMB_CCER1 = (PWMB_CCER1 & (~0x03) | ((polarity | 0x01) << 0));
    if (n & PWM6 )  PWMB_CCER1 = (PWMB_CCER1 & (~0x30) | ((polarity | 0x01) << 4));
    if (n & PWM7 )  PWMB_CCER2 = (PWMB_CCER2 & (~0x03) | ((polarity | 0x01) << 0));
    if (n & PWM8 )  PWMB_CCER2 = (PWMB_CCER2 & (~0x30) | ((polarity | 0x01) << 4));
    // switch (n)
    // {
    //     case PWM1:  PWMA_CCER1 = (PWMA_CCER1 & (~0x03) | ((polarity | 0x01) << 0)); break;
    //     case PWM1N: PWMA_CCER1 = (PWMA_CCER1 & (~0x0C) | ((polarity | 0x01) << 2)); break;
    //     case PWM2:  PWMA_CCER1 = (PWMA_CCER1 & (~0x30) | ((polarity | 0x01) << 4)); break;
    //     case PWM2N: PWMA_CCER1 = (PWMA_CCER1 & (~0xC0) | ((polarity | 0x01) << 6)); break;
    //     case PWM3:  PWMA_CCER2 = (PWMA_CCER2 & (~0x03) | ((polarity | 0x01) << 0)); break;
    //     case PWM3N: PWMA_CCER2 = (PWMA_CCER2 & (~0x0C) | ((polarity | 0x01) << 2)); break;
    //     case PWM4:  PWMA_CCER2 = (PWMA_CCER2 & (~0x30) | ((polarity | 0x01) << 4)); break;
    //     case PWM4N: PWMA_CCER2 = (PWMA_CCER2 & (~0xC0) | ((polarity | 0x01) << 6)); break;
    //     case PWM5:  PWMB_CCER1 = (PWMB_CCER1 & (~0x03) | ((polarity | 0x01) << 0)); break;
    //     case PWM6:  PWMB_CCER1 = (PWMB_CCER1 & (~0x30) | ((polarity | 0x01) << 4)); break;
    //     case PWM7:  PWMB_CCER2 = (PWMB_CCER2 & (~0x03) | ((polarity | 0x01) << 0)); break;
    //     case PWM8:  PWMB_CCER2 = (PWMB_CCER2 & (~0x30) | ((polarity | 0x01) << 4)); break;
    //     default: break;
    // }
    
    // enable output
    PWMA_ENO |= (n & PWMA);
    PWMB_ENO |= (n & PWMB) >> 8;
}

void PWM_nDeinit(PWM_n_t n)
{
    PWMA_ENO &= ~(n & PWMA);
    PWMB_ENO &= ~((n & PWMB) >> 8);
}

void PWM_xArrSet(PWM_x_t x, uint16_t arr)
{
    if ((x & PWMA) != 0)
    {
        PWMA_ARRH = (arr & 0xFF00) >> 8;
        PWMA_ARRL = (arr & 0x00FF);
    }
    if ((x & PWMB) != 0)
    {
        PWMB_ARRH = (arr & 0xFF00) >> 8;
        PWMB_ARRL = (arr & 0x00FF);
    }
}

uint16_t PWM_xArrGet(PWM_x_t x)
{
    uint16_t rtn = 0;

    switch (x)
    {
        case PWMA: rtn = (PWMA_ARRH << 8) + PWMA_ARRL; break;
        case PWMB: rtn = (PWMB_ARRH << 8) + PWMB_ARRL; break;
        default: break;
    }

    return rtn;
}

void PWM_xFreqSet(PWM_x_t x, uint16_t freq)
{
    uint16_t arr = 0;
    if (freq != 0)
    {
        if ((FOSC / freq) < 0x00010000)
        {
            arr = (FOSC / freq) & 0xFFFF;
        }
        else
        {
            arr = 0xFFFF;
        }
    }
    else
    {
        arr = 0;
    }

    // disable clock pre-scaler
    switch (x)
    {
    case PWMA:
        PWMA_PSCRH = 0x00;
        PWMA_PSCRL = 0x00;
        break;
    case PWMB:
        PWMB_PSCRH = 0x00;
        PWMB_PSCRL = 0x00;
        break;
    default:
        break;
    }

    PWM_xArrSet(x, arr);
}

void PWM_nCcrSet(PWM_n_t n, uint16_t ccr)
{
    switch (n)
    {
    case PWM1:
        PWMA_CCR1H = ((ccr / 2) & 0xFF00) >> 8;
        PWMA_CCR1L = ((ccr / 2) & 0x00FF);
        break;
    case PWM2:
        PWMA_CCR2H = ((ccr / 2) & 0xFF00) >> 8;
        PWMA_CCR2L = ((ccr / 2) & 0x00FF);
        break;
    case PWM3:
        PWMA_CCR3H = ((ccr / 2) & 0xFF00) >> 8;
        PWMA_CCR3L = ((ccr / 2) & 0x00FF);
        break;
    case PWM4:
        PWMA_CCR4H = ((ccr / 2) & 0xFF00) >> 8;
        PWMA_CCR4L = ((ccr / 2) & 0x00FF);
        break;
    case PWM5:
        PWMB_CCR5H = ((ccr / 2) & 0xFF00) >> 8;
        PWMB_CCR5L = ((ccr / 2) & 0x00FF);
        break;
    case PWM6:
        PWMB_CCR6H = ((ccr / 2) & 0xFF00) >> 8;
        PWMB_CCR6L = ((ccr / 2) & 0x00FF);
        break;
    case PWM7:
        PWMB_CCR7H = ((ccr / 2) & 0xFF00) >> 8;
        PWMB_CCR7L = ((ccr / 2) & 0x00FF);
        break;
    case PWM8:
        PWMB_CCR8H = ((ccr / 2) & 0xFF00) >> 8;
        PWMB_CCR8L = ((ccr / 2) & 0x00FF);
        break;
    default:
        break;
    }
}

uint16_t PWM_nCcrGet(PWM_n_t n)
{
    uint16_t rtn = 0;

    switch (n)
    {
        case PWM1: rtn = (PWMA_CCR1H << 8) + PWMA_CCR1L; break;
        case PWM2: rtn = (PWMA_CCR2H << 8) + PWMA_CCR2L; break;
        case PWM3: rtn = (PWMA_CCR3H << 8) + PWMA_CCR3L; break;
        case PWM4: rtn = (PWMA_CCR4H << 8) + PWMA_CCR4L; break;
        case PWM5: rtn = (PWMB_CCR5H << 8) + PWMB_CCR5L; break;
        case PWM6: rtn = (PWMB_CCR6H << 8) + PWMB_CCR6L; break;
        case PWM7: rtn = (PWMB_CCR7H << 8) + PWMB_CCR7L; break;
        case PWM8: rtn = (PWMB_CCR8H << 8) + PWMB_CCR8L; break;
        default: break;
    }

    return rtn;
}

void PWM_nDutySet(PWM_n_t n, uint8_t duty)
{
    uint32_t ccr; // ccr = arr * duty%
    if ((n & PWMA) != 0)
    {
        ccr = PWM_xArrGet(PWMA) * duty / 100;
        if ((ccr & 0xFFFF0000ul) != 0)
        {
            ccr = 0xFFFF;
        }
        PWM_nCcrSet(n, ccr);
    }
    if ((n & PWMB) != 0)
    {
        ccr = PWM_xArrGet(PWMB) * duty / 100;
        if ((ccr & 0xFFFF0000ul) != 0)
        {
            ccr = 0xFFFF;
        }
        PWM_nCcrSet(n, ccr);
    }
}

#include "eeprom.h"

#define EEP_OFFSET      0xFE00

void EEP_Init(void)
{
    // set operation waiting time
    EEP_SetTps();
    
}

void EEP_SetTps(void)
{
    // set operation waiting time
    if (FOSC <= 12000000ul)
    {
        IAP_TPS = 12;
    }
    else if (FOSC <= 24000000ul)
    {
        IAP_TPS = 24;
    }
    else if (FOSC <= 48000000ul)
    {
        IAP_TPS = 48;
    }
    else
    {
        IAP_TPS = 63;
    }
}

void EEP_Trig(void)
{
    // to operate EEPROM, must write 0x5A and 0xA5 to IAP_TRIG in order after 
    // configuring command, address and data
    IAP_TRIG = 0x5A;
    IAP_TRIG = 0xA5;
}

void EEP_Idle(void)
{
    // turn iap off
    IAP_CONTR = 0;
    
    // clean register
    IAP_CMD = 0;
    IAP_TRIG = 0;
    IAP_ADDRH = 0x80;
    IAP_ADDRL = 0x00;
}

uint8_t EEP_Read(uint16_t addr)
{
    char dat;

    IAP_CONTR = 0x80;
    EEP_SetTps();
    IAP_CMD = 1;
    IAP_ADDRL = (addr & 0x00FF);
    IAP_ADDRH = (addr & 0xFF00) >> 8;

    EEP_Trig();
    NOP1();

    dat = IAP_DATA;

    EEP_Idle();

    return dat;
}

uint8_t EEP_ReadC(uint16_t addr)
{
    cuint8_t * dat = (addr + EEP_OFFSET);
    if ((*dat) < '0' || (*dat) > '9')
    {
        return '0';
    }
    else
    {
        return (*dat);
    }
}

void EEP_Write(uint16_t addr, uint8_t dat)
{
    IAP_CONTR = 0x80;
    EEP_SetTps();
    IAP_CMD = 2;
    IAP_ADDRL = addr;
    IAP_ADDRH = addr >> 8;
    IAP_DATA = dat;

    EEP_Trig();
    NOP1();

    EEP_Idle();
}

void EEP_Erase(uint8_t bank)
{
    IAP_CONTR = 0x80;
    EEP_SetTps();
    IAP_CMD = 3;
    IAP_ADDRL = 0x00;
    IAP_ADDRH = 2 * bank;

    EEP_Trig();
    NOP1();

    EEP_Idle();
}
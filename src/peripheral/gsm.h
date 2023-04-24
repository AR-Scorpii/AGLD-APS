#ifndef __PERI_GSM_H__
#define __PERI_GSM_H__

#ifdef _DEBUG
#include <stdio.h>
#endif

#include "../../inc/stc8h.h"

#include "../mcu/delay.h"
#include "../mcu/uart.h"

typedef enum GSM_Stat_e
{
    GSM_Stat_OK                 = 0x00,
    GSM_Stat_UnconnectedModule  = 0x01,
    GSM_Stat_UnconnectedCard    = 0x02,
    GSM_Stat_UnsupportedCard    = 0x04
} GSM_Stat_t;

uint8_t strfind(char *, char *);

void GSM_StrSend(char *);

GSM_Stat_t GSM_Init(void);
GSM_Stat_t GSM_SmsSend(char *, char *);


#endif
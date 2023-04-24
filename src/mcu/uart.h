#ifndef __MCU_UART_H__
#define __MCU_UART_H__

#ifdef _DEBUG
#include <stdio.h>
#endif

#include "../../inc/stc8h.h"

extern cuint32_t FOSC;

#define UART_TIMVAL(BAUD)   (65536 - FOSC / BAUD / 4)

typedef enum UART_e
{
    UART1 = 0x01,
    UART2 = 0x04,
    UART3 = 0x10,
    UART4 = 0x40
}UART_t;

void UART_ClkInit(void);
void UART_Init(UART_t);

void UART_CharSend(UART_t, char);
void UART_StrSend(UART_t, char *);

void UART_BufferClean(UART_t);

#endif
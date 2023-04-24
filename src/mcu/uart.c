#include "uart.h"

uint8_t UART_BusyFlag = 0;

static cuint8_t UART_STCISPCMD[] = "@STCISP#";
uint8_t UART_IspCmdIndex = 0;

uint8_t UART_RPtr2 = 0;
xuint8_t UART_Buffer2[64];

void UART_1_Isr(void)       INTERRUPT(UART1_VECTOR)
{
    uint8_t dat;

    if (TI)
    {
        TI = 0;
        UART_BusyFlag &= ~UART1;
    }
    if (RI)
    {
        RI = 0;
        dat = SBUF;
        if (dat == UART_STCISPCMD[UART_IspCmdIndex])
        {
            UART_IspCmdIndex++;
            if (UART_STCISPCMD[UART_IspCmdIndex] == '\0')
            {
                IAP_CONTR = 0x60;
            }
        }
        else
        {
            UART_IspCmdIndex = 0;
            if (dat == UART_STCISPCMD[UART_IspCmdIndex])
            {
                UART_IspCmdIndex++;
            }
        }
    }
}

void UART_2_Isr(void)       INTERRUPT(UART2_VECTOR)
{
    if (S2CON & 0x02)
    {
        S2CON &= ~0x02;
        UART_BusyFlag &= ~UART2;
    }
    if (S2CON & 0x01)
    {
        S2CON &= ~0x01;
        UART_Buffer2[UART_RPtr2++] = S2BUF;
        UART_RPtr2 &= sizeof(UART_Buffer2) / sizeof(xuint8_t) - 1;
    }
}

void UART_ClkInit(void)
{
    T2L = (UART_TIMVAL(115200) & 0x00FF);
    T2H = (UART_TIMVAL(115200) & 0xFF00) >> 8;
    AUXR = (AUXR & ~0x1C | 0x14);
}

void UART_Init(UART_t uart)
{
    UART_ClkInit();

    if (uart & UART1)
    {
        SCON |= 0x50;
        AUXR |= 0x11;

        ES = 1; 
        EA = 1;

#       ifdef _DEBUG
        printf("[UART] UART1 inited\n");
#       endif
    }
    if (uart & UART2)
    {
        P_SW2 |= 0x01;
        
        S2CON = 0x10;

        IE2 |= 0x01;
        EA = 1;

#       ifdef _DEBUG
        printf("[UART] UART2 inited\n");
#       endif
    }
}

void UART_CharSend(UART_t uart, char dat)
{
    while (UART_BusyFlag & uart);
    UART_BusyFlag |= uart;
    switch (uart)
    {
        case UART1: SBUF = dat; break;
        case UART2: S2BUF = dat; break;
        case UART3: S3BUF = dat; break;
        case UART4: S4BUF = dat; break;
        default: break;
    }
}

void UART_StrSend(UART_t uart, char *p)
{
    while (*p)
    {
        UART_CharSend(uart, *p++);
    }
}

void UART_BufferClean(UART_t uart)
{
    switch (uart)
    {
    case UART2:
        for (uint8_t i = 0; i < sizeof(UART_Buffer2); i++)
        {
            UART_Buffer2[i] = 0;
        }
        UART_RPtr2 = 0;
        break;
    default:
        break;
    }
}

#ifdef _DEBUG
int putchar (int c)
{
    UART_CharSend(UART1, c);
    return c;
}
#endif
#include "gsm.h"

extern uint8_t UART_RPtr2;
extern xuint8_t UART_Buffer2[64];

#define STRFIND_NOTFOUND    255

uint8_t strfind(char * str, char * sub)
{
    uint8_t subindex = 0;
    for (uint8_t i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == sub[subindex])
        {
            if (sub[subindex+1] == '\0')
            {
                return (i - subindex);
            }
            subindex++;
        }
        else
        {
            subindex = 0;
            if (str[i] == sub[subindex])
            {
                subindex++;
            }
        }
    }

    return STRFIND_NOTFOUND;
}

void GSM_StrSend(char * command)
{
    UART_BufferClean(UART2);

    UART_StrSend(UART2, command);
#   ifdef _DEBUG
    printf("[GSM] addressed command: %s\n", command);
#   endif

    delay_ms(1000);
}

GSM_Stat_t GSM_Init(void)
{
    UART_Init(UART2);

    // check connection
    // should reply "OK"
    GSM_StrSend("AT\r\n");
#   ifdef _DEBUG
    printf("[GSM] AT return: %s\n", UART_Buffer2);
#   endif
    if (strfind(UART_Buffer2, "OK") == STRFIND_NOTFOUND)
    {
#       ifdef _DEBUG
        printf("[GSM] error: module not detected\n");
#       endif
        return GSM_Stat_UnconnectedModule;
    }

    // check card insertion
    // should reply "+CPIN: READY" "OK"
    GSM_StrSend("AT+CPIN?\r\n");
#   ifdef _DEBUG
    printf("[GSM] AT+CPIN? return: %s\n", UART_Buffer2);
#   endif
    if (strfind(UART_Buffer2, "READY") == STRFIND_NOTFOUND)
    {
#       ifdef _DEBUG
        printf("[GSM] error: card not detected\n");
#       endif
        return GSM_Stat_UnconnectedCard;
    }

    // check card registration
    GSM_StrSend("AT+CREG?\r\n");
#   ifdef _DEBUG
    printf("[GSM] AT+CREG? return: %s\n", UART_Buffer2);
#   endif

    // check signal intensity
    GSM_StrSend("AT+CSQ\r\n");
#   ifdef _DEBUG
    printf("[GSM] AT+CSQ return: %s\n", UART_Buffer2);
#   endif

#   ifdef _DEBUG
    printf("[GSM] inited\n");
#   endif
    return GSM_Stat_OK;
}

GSM_Stat_t GSM_SmsSend(char * number, char * text)
{
    GSM_StrSend("AT\r\n");
#   ifdef _DEBUG
    printf("[GSM] AT return: %s\n", UART_Buffer2);
#   endif
    if (strfind(UART_Buffer2, "OK") == STRFIND_NOTFOUND)
    {
#       ifdef _DEBUG
        printf("[GSM] error: module not detected\n");
#       endif
        return GSM_Stat_UnconnectedModule;
    }

    GSM_StrSend("AT+CMGF=1\r\n");
#   ifdef _DEBUG
    printf("[GSM] AT+CMGF=1 return: %s\n", UART_Buffer2);
#   endif

    UART_BufferClean(UART2);
    UART_StrSend(UART2, "AT+CMGS=\"");
    uint8_t gsmflag = 0;
    for (uint8_t i = 0; number[i] != '\0'; i++)
    {
        if (gsmflag == 0)
        {
            if (number[i] == '0')
            {
                // do nothing here
            }
            else
            {
                gsmflag = 1;
                UART_CharSend(UART2, number[i]);
            }
        }
        else
        {
            UART_CharSend(UART2, number[i]);
        }
    }
    UART_StrSend(UART2, "\"\r\n");
    delay_ms(3000);
#   ifdef _DEBUG
    printf("[GSM] AT+CMGS has: %s\n", UART_Buffer2);
#   endif
    if (strfind(UART_Buffer2, ">") == STRFIND_NOTFOUND)
    {
#       ifdef _DEBUG
        printf("[GSM] error: unexpected error in command AT+CMGS\n");
#       endif
        return GSM_Stat_UnsupportedCard;
    }

    UART_BufferClean(UART2);
    UART_StrSend(UART2, text);
    UART_StrSend(UART2, "\x1A\r\n");
    delay_ms(10000);
#   ifdef _DEBUG
    printf("[GSM] AT+CMGS return: %s\n", UART_Buffer2);
#   endif
    if (strfind(UART_Buffer2, "CMGS") == STRFIND_NOTFOUND)
    {
#       ifdef _DEBUG
        printf("[GSM] error: unexpected error in command AT+CMGS\n");
#       endif
        return GSM_Stat_UnsupportedCard;
    }

    return GSM_Stat_OK;
}

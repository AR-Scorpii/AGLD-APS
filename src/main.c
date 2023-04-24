#include <stdint.h>
#include <stdlib.h>
#ifdef _DEBUG
#include <stdio.h>
#endif

#include "../inc/stc8h.h"

#include "mcu/ioconf.h"
#include "mcu/uart.h"
#include "mcu/eeprom.h"
#include "peripheral/buzzer.h"
#include "peripheral/mq.h"
#include "peripheral/lcd.h"
#include "peripheral/gsm.h"
#include "peripheral/motor.h"


/**** macrons and global variables ********************************************/
// main clock frequency
// cuint32_t FOSC = 11059200ul; // 11.0592 MHz
cuint32_t FOSC = 22118400ul; // 22.1184 MHz

#define MAIN_BTN_FUNC   0x80
#define MAIN_BTN_DEC    0x08
#define MAIN_BTN_INC    0x04
#define MAIN_BTN_R      0x02
#define MAIN_BTN_L      0x01

#define MAIN_ACTFLAG_GSM        0x08
#define MAIN_ACTFLAG_BUZZER     0x04
#define MAIN_ACTFLAG_MOTOR      0x03

#define MAIN_GASFLAG_SETMODIFY  0x80
#define MAIN_GASFLAG_DETCYCLE   0x0E
#define MAIN_GASFLAG_STATUS     0x01

#define MAIN_DISPFLAG_CURXPOS   0xF0
#define MAIN_DISPFLAG_CURLINE   0x0C
#define MAIN_DISPFLAG_PREVPG    0x02
#define MAIN_DISPFLAG_PG        0x01

iuint8_t MAIN_Btn = 0x00;


/**** interrupts **************************************************************/
/**
 * Interrupt function prototypes MUST be located in the same source file as the 
 * main function. See SDCC manual section 3.8. 
 */
// UART1 interrupt service routine
extern void UART_1_Isr(void)                INTERRUPT(UART1_VECTOR);    // 4
extern void UART_2_Isr(void)                INTERRUPT(UART2_VECTOR);    // 8
void LVD_Isr()                              INTERRUPT(LVD_VECTOR)       // 6
{
    // low voltage detected (i.e. power-off)
    PCON &= ~0x20;

    MOT_Off(0);
}

void P0_Isr(void)                           INTERRUPT(P0INT_VECTOR)     // 37
{
    MAIN_Btn |= P0INTF;
    P0INTF = 0x00;
}

/**** misc ********************************************************************/
void __ultoa_tiny(uint32_t num, char * c)
{
    uint8_t index = 0;
    uint8_t flag = 0;
    for (uint32_t base = 1000000000ul; base >= 10; base /= 10)
    {
        if (flag == 0 && num / base == 0)
        {
            continue;
        }
        else
        {
            flag = 1;
            c[index] = '0' + num / base;
            num %= base;
            index++;
        }
    }
    c[index] = '0' + num;
}

typedef enum num_modification_dir_e
{
    num_modification_dir_veri,
    num_modification_dir_inc,
    num_modification_dir_dec,
    num_modification_dir_cycinc,
    num_modification_dir_cycdec
}num_modification_dir_t;

uint8_t num_modification(uint8_t num, num_modification_dir_t direction)
{
    switch (direction)
    {
        case num_modification_dir_inc:      num++;
                                            if (num > '9')
                                            {
                                                num = '9';
                                            }
                                            break;
        case num_modification_dir_dec:      num--;
                                            if (num < '0')
                                            {
                                                num = '0';
                                            }
                                            break;
        case num_modification_dir_cycinc:   num++;
                                            if (num > '9')
                                            {
                                                num = '0';
                                            }
                                            break;
        case num_modification_dir_cycdec:   num--;
                                            if (num < '0')
                                            {
                                                num = '9';
                                            }
                                            break;
        case num_modification_dir_veri: 
        default:                            if (num < '0' || num > '9')
                                            {
                                                num = '0';
                                            }
                                            break;
    }

    return num;
}


/**** main function ***********************************************************/
int main(void)
{

/*  initialization ************************************************************/

    IO_Init();

    EAXSFR();
#   ifdef _DEBUG
    MCLKOCR = 0x01; // MCLK output at P5.4
#   endif

    UART_Init(UART1);
#   ifdef _DEBUG
    printf("[MAIN] starting\n");
#   endif
    
    /* user interface */
    LCD_Init(LCD_Rot_90);
    LCD_Fill(0, 0, 160, 128, 0x0000);

    // button interrupt
    // P0INTE = 0x8F;
    P0INTE = MAIN_BTN_L | MAIN_BTN_R | MAIN_BTN_DEC | MAIN_BTN_INC | MAIN_BTN_FUNC;
    P0INTF = 0x00;
    P0IM0 = 0x00;
    // P0IM1 = 0x8F;
    P0IM1 = MAIN_BTN_L | MAIN_BTN_R | MAIN_BTN_DEC | MAIN_BTN_INC | MAIN_BTN_FUNC;
    EA = 1;

    /* sensor */
    MQ_Init();

    /* actuator */
    BUZ_Init();
    GSM_Init();
    MOT_Init();

    // RSTCFG = 0x03;
    // ELVD = 1;
    // EA = 1;

/*  variable ******************************************************************/

    // should be loaded from EEPROM
    // EEPROM arrangement: 
    //    0 1 2 3 4 5 6 7 8 9 A B C D E F
    // 00 P P P P P P P P P P P P P P P P
    // 01 0 0 H H H H H 0 0 L L L L L 0 0
    // (P = phone number, H = thresH, L = thresL, 0 = 0x00)
    xuint8_t MAIN_NumberStr[17] = "0000000000000000";
    for (uint8_t i = 0; i < 16; i++)
    {
        MAIN_NumberStr[i] = EEP_ReadC(i);
    }
    xuint8_t MAIN_ThresStrH[6] = "01500";
    for (uint8_t i = 0; i < 5; i++)
    {
        MAIN_ThresStrH[i] = EEP_ReadC(0x12+i);
    }
    xuint8_t MAIN_ThresStrL[6] = "01000";
    for (uint8_t i = 0; i < 5; i++)
    {
        MAIN_ThresStrL[i] = EEP_ReadC(0x19+i);
    }
    xuint16_t MAIN_ThresH   = (MAIN_ThresStrH[0] - '0') * 10000 \
                            + (MAIN_ThresStrH[1] - '0') * 1000  \
                            + (MAIN_ThresStrH[2] - '0') * 100   \
                            + (MAIN_ThresStrH[3] - '0') * 10    \
                            + (MAIN_ThresStrH[4] - '0');
    xuint16_t MAIN_ThresL   = (MAIN_ThresStrL[0] - '0') * 10000 \
                            + (MAIN_ThresStrL[1] - '0') * 1000  \
                            + (MAIN_ThresStrL[2] - '0') * 100   \
                            + (MAIN_ThresStrL[3] - '0') * 10    \
                            + (MAIN_ThresStrL[4] - '0');

    // b3: gsm flag
    // b2: buz flag
    // b1-0: motor flag
    iuint8_t MAIN_ActFlag = 0;

    // b7: setting modified
    // b3-1: detection cycle count
    // b0: status: 0 - normal, 1 - leakage
    iuint8_t MAIN_GasFlag = 0;

    // b7-4: cursor xpos
    // b3-2: cursor line
    // b1: previous page
    // b0: page: 0 - main, 1 - setting
    iuint8_t MAIN_DispFlag = MAIN_DISPFLAG_PREVPG;

    // GSM_SmsSend(MAIN_NumberStr, "Hello World: GSM Inited.");

#   ifdef _DEBUG
    printf("[MAIN] turning on valve\n");
#   endif
    LCD_StrOverride(0, 0, "INITING...", 16, 0xFFFF, 0x0000);
    MAIN_ActFlag |= (MAIN_ActFlag & ~MAIN_ACTFLAG_MOTOR) | MOT_On(MAIN_ActFlag & MAIN_ACTFLAG_MOTOR);
    LCD_Fill(0, 0, 160, 128, 0x0000);
#   ifdef _DEBUG
    printf("[MAIN] inited\n");
#   endif

/*  main loop *****************************************************************/

    while (1)
    {
#       ifdef _DEBUG
        printf("[MAIN] new loop\n");
#       endif

/*      gas concentration and action determination ****************************/

        // uint32_t gasConcR = MQ_ResistGet();
        uint16_t gasConc = MQ_ConcGet();

        if ((MAIN_GasFlag & MAIN_GASFLAG_STATUS) == 0x00)
        {
            // normal

            if ((MAIN_ActFlag & MAIN_ACTFLAG_BUZZER) == MAIN_ACTFLAG_BUZZER)
            {
                BUZ_Stop();
                MAIN_ActFlag ^= MAIN_ACTFLAG_BUZZER;
            }
            
            if (gasConc > MAIN_ThresH)
            {
                if ((MAIN_GasFlag & MAIN_GASFLAG_DETCYCLE) < MAIN_GASFLAG_DETCYCLE)
                {
                    MAIN_GasFlag += 0x02;
                }
                else
                {
                    MAIN_ActFlag = 0;
                    MAIN_GasFlag |= 0x01;
                }
            }
        }
        else
        {
            // in gas leakage

            if (MOT_AtPosOff() == 0)
            {
                MAIN_ActFlag = (MAIN_ActFlag & ~MAIN_ACTFLAG_MOTOR) | MOT_Move(MOT_Mov_Clockwise, MAIN_ActFlag & MAIN_ACTFLAG_MOTOR); 
                delay_ms(10);
            }

            if ((MAIN_ActFlag & MAIN_ACTFLAG_BUZZER) == 0)
            {
                BUZ_Freq(880);
                BUZ_Start();
                MAIN_ActFlag |= MAIN_ACTFLAG_BUZZER;
            }

            if ((MAIN_ActFlag & MAIN_ACTFLAG_GSM) == 0)
            {
                GSM_SmsSend(MAIN_NumberStr, "Gas leakage detected!");
                MAIN_ActFlag |= MAIN_ACTFLAG_GSM;
            }
            
            if (gasConc < MAIN_ThresL)
            {
                if ((MAIN_GasFlag & MAIN_GASFLAG_DETCYCLE) < MAIN_GASFLAG_DETCYCLE)
                {
                    MAIN_GasFlag += 0x02;
                }
                else
                {
                    MAIN_GasFlag &= 0xFE;
                }
            }
        }

/*      graphical user interface **********************************************/
        
        /* page swap check */

        if ((MAIN_Btn & MAIN_BTN_FUNC) != 0x00)
        {
            if ((MAIN_DispFlag & (MAIN_DISPFLAG_PREVPG | MAIN_DISPFLAG_PG)) != 0x03)
            {
                MAIN_DispFlag ^= MAIN_DISPFLAG_PG;
            }
            else
            {
                // in settings page
                MAIN_DispFlag += 0x04;
                if ((MAIN_DispFlag & MAIN_DISPFLAG_CURLINE) >= MAIN_DISPFLAG_CURLINE)
                {
                    MAIN_DispFlag ^= MAIN_DISPFLAG_PG;
                    // MAIN_DispFlag = 0x02;
                    if (MAIN_GasFlag & MAIN_GASFLAG_SETMODIFY)
                    {
                        EEP_Erase(0);
                        for (uint8_t i = 0; i < 16; i++)
                        {
                            EEP_Write(i, MAIN_NumberStr[i]);
                        }
                        EEP_Write(0x10, 0);
                        EEP_Write(0x11, 0);
                        for (uint8_t i = 0; i < 5; i++)
                        {
                            EEP_Write(0x12+i, MAIN_ThresStrH[i]);
                        }
                        EEP_Write(0x17, 0);
                        EEP_Write(0x18, 0);
                        for (uint8_t i = 0; i < 5; i++)
                        {
                            EEP_Write(0x19+i, MAIN_ThresStrL[i]);
                        }
                        EEP_Write(0x1E, 0);
                        EEP_Write(0x1F, 0);

                        MAIN_GasFlag ^= MAIN_GASFLAG_SETMODIFY;
                    }
                }
            }
            
            MAIN_Btn &= ~MAIN_BTN_FUNC;
        }

#       ifdef _DEBUG
        printf("[MAIN] pg det - btn: %02X, dispflag: %02X\n", MAIN_Btn, MAIN_DispFlag);
#       endif

        if (((MAIN_DispFlag & MAIN_DISPFLAG_PREVPG)>>1) != (MAIN_DispFlag & MAIN_DISPFLAG_PG))
        {
            // page change action detected, clean the screen
            LCD_Fill(0, 0, 160, 128, 0x0000);

            // locate page and clean cursor
            // MAIN_DispFlag = ((MAIN_DispFlag & 0x01) | ((MAIN_DispFlag & 0x01) << 1));
            switch ((MAIN_DispFlag & MAIN_DISPFLAG_PG))
            {
                case 0x00:  MAIN_DispFlag = 0x00; break;
                case 0x01:  MAIN_DispFlag = 0x03; break;
                default:    MAIN_DispFlag = 0x00; break;
            }

            // display item names
            if ((MAIN_DispFlag & MAIN_DISPFLAG_PG) == 0)
            {
                // main page
                LCD_StrOverride(0, 0, "GAS CONCENTRATION", 16, 0xFFFF, 0x0000);
            }
            else
            {
                // settings page
                LCD_StrOverride(0, 0, "PHONE NUMBER", 16, 0xFFFF, 0x0000);
                LCD_StrOverride(0, 32, "THRESHOLD HIGH", 16, 0xFFFF, 0x0000);
                LCD_StrOverride(0, 64, "THRESHOLD LOW", 16, 0xFFFF, 0x0000);
            }
        }
        
        /* data demonstration */

        if ((MAIN_DispFlag & MAIN_DISPFLAG_PG) == 0)
        {
            // on main page

            char gasConcStr[6] = {0x00}; 
            // __ultoa(gasConc, gasConcStr, 10);
            __ultoa_tiny(gasConc, gasConcStr);
            // LCD_StrOverride(0, 0, "GAS CONCENTRATION", 16, 0xFFFF, 0x0000);
            LCD_Fill(0, 16, 160, 16, 0x0000);
            LCD_StrOverride(0, 16, gasConcStr, 16, 0xFFFF, 0x0000);
#           ifdef _DEBUG
            printf("[MAIN] gasConcStr=%s\n", gasConcStr);
            // printf("[MAIN] gasConcR=%ld, gasConcRStr=%s\n", gasConcR, gasConcStr);
#           endif

            uint32_t a = 0x0003FFFF;
            while (a--);
        } // end of main page
        else
        {
            // on settings page

            // phone number
            LCD_StrOverride(0, 16, MAIN_NumberStr, 16, 0xFFFF, 0x0000);

            // threshold
            LCD_StrOverride(0, 48, MAIN_ThresStrH, 16, 0xFFFF, 0x0000);
            LCD_StrOverride(0, 80, MAIN_ThresStrL, 16, 0xFFFF, 0x0000);

#           ifdef _DEBUG
            printf("[MAIN] set - number: %s\n", MAIN_NumberStr);
            printf("[MAIN] set - thresH: %s\n", MAIN_ThresStrH);
            printf("[MAIN] set - thresL: %s\n", MAIN_ThresStrL);
#           endif


#           ifdef _DEBUG
            printf("[MAIN] set - btn: %02X, dispflag: %02X\n", MAIN_Btn, MAIN_DispFlag);
#           endif
            // cursor movement
            if (MAIN_Btn & MAIN_BTN_L)
            {
                MAIN_DispFlag -= 0x10;
            }
            if (MAIN_Btn & MAIN_BTN_R)
            {
                MAIN_DispFlag += 0x10;
            }
            MAIN_Btn &= ~(MAIN_BTN_L | MAIN_BTN_R);
#           ifdef _DEBUG
            printf("[MAIN] cursor 1 - btn: %02X, dispflag: %02X\n", MAIN_Btn, MAIN_DispFlag);
#           endif

            uint8_t line = (MAIN_DispFlag & MAIN_DISPFLAG_CURLINE) >> 2;
            switch (line)
            {
                case 0x00:  break;
                case 0x01:  if ((MAIN_DispFlag & MAIN_DISPFLAG_CURXPOS) > 0x50)
                            {
                                MAIN_DispFlag = (0x40 | (MAIN_DispFlag & 0x0F));
                            }
                            else if ((MAIN_DispFlag & MAIN_DISPFLAG_CURXPOS) == 0x50)
                            {
                                MAIN_DispFlag = ((MAIN_DispFlag & 0x0F));
                            }
                            break;
                case 0x02:  if ((MAIN_DispFlag & MAIN_DISPFLAG_CURXPOS) > 0x50)
                            {
                                MAIN_DispFlag = (0x40 | (MAIN_DispFlag & 0x0F));
                            }
                            else if ((MAIN_DispFlag & MAIN_DISPFLAG_CURXPOS) == 0x50)
                            {
                                MAIN_DispFlag = ((MAIN_DispFlag & 0x0F));
                            }
                            break;
                default:    break;
            }
            uint8_t xpos = (MAIN_DispFlag & MAIN_DISPFLAG_CURXPOS) >> 4;
#           ifdef _DEBUG
            printf("[MAIN] cursor 2 - btn: %02X, dispflag: %02X, line: %02X, xpos: %02X\n", MAIN_Btn, MAIN_DispFlag, line, xpos);
#           endif
            
            // value modification
            if (MAIN_Btn & (MAIN_BTN_INC | MAIN_BTN_DEC)) // key pressed
            {
                MAIN_GasFlag |= MAIN_GASFLAG_SETMODIFY;

                if (MAIN_Btn & MAIN_BTN_DEC)
                {
                    switch (line)
                    {
                        case 0x00:  MAIN_NumberStr[xpos] = num_modification(MAIN_NumberStr[xpos], num_modification_dir_cycdec);
                                    break;
                        case 0x01:  MAIN_ThresStrH[xpos] = num_modification(MAIN_ThresStrH[xpos], num_modification_dir_cycdec);
                                    break;
                        case 0x02:  MAIN_ThresStrL[xpos] = num_modification(MAIN_ThresStrL[xpos], num_modification_dir_cycdec);
                                    break;
                        default: break;
                    }
                }

                if (MAIN_Btn & MAIN_BTN_INC)
                {
                    switch (line)
                    {
                        case 0x00:  MAIN_NumberStr[xpos] = num_modification(MAIN_NumberStr[xpos], num_modification_dir_cycinc);
                                    break;
                        case 0x01:  MAIN_ThresStrH[xpos] = num_modification(MAIN_ThresStrH[xpos], num_modification_dir_cycinc);
                                    break;
                        case 0x02:  MAIN_ThresStrL[xpos] = num_modification(MAIN_ThresStrL[xpos], num_modification_dir_cycinc);
                                    break;
                        default: break;
                    }
                }

                MAIN_Btn &= ~0x0C;
            }

            // cursor display
            switch (line)
            {
                case 0x00:  LCD_CharOverride(xpos*8, 16, MAIN_NumberStr[xpos], 16, 0x001F, 0x0000); break;
                case 0x01:  LCD_CharOverride(xpos*8, 48, MAIN_ThresStrH[xpos], 16, 0x001F, 0x0000); break;
                case 0x02:  LCD_CharOverride(xpos*8, 80, MAIN_ThresStrL[xpos], 16, 0x001F, 0x0000); break;
                default: break;
            }

            uint32_t a = 0x0001FFFF;
            while (a--);

        } // end of settings page

    } // end of main loop

} // end of main function
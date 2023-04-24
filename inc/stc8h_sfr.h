/**
 * @file        stc8h_sfr.h
 * 
 * @brief       The special function register (SFR) definitions for STC8H series 
 *              microcontroller. 
 * 
 * @copyright   This is modified from STC official codes. The copyright belongs
 *              to STC. 
 */

#ifndef     __STC8H_SFR_H__
#define     __STC8H_SFR_H__

#include "ccd/ccd.h"

SFR(P0, 0x80);
SBIT(P00, 0x80, 0); SBIT(P0_0, 0x80, 0);
SBIT(P01, 0x80, 1); SBIT(P0_1, 0x80, 1);
SBIT(P02, 0x80, 2); SBIT(P0_2, 0x80, 2);
SBIT(P03, 0x80, 3); SBIT(P0_3, 0x80, 3);
SBIT(P04, 0x80, 4); SBIT(P0_4, 0x80, 4);
SBIT(P05, 0x80, 5); SBIT(P0_5, 0x80, 5);
SBIT(P06, 0x80, 6); SBIT(P0_6, 0x80, 6);
SBIT(P07, 0x80, 7); SBIT(P0_7, 0x80, 7);

SFR(SP, 0x81);
SFR(DPL, 0x82);
SFR(DPH, 0x83);
SFR(S4CON, 0x84);
SFR(S4BUF, 0x85);
SFR(PCON, 0x87);

SFR(TCON,  0x88);
SBIT(TF1, 0x88, 7);
SBIT(TR1, 0x88, 6);
SBIT(TF0, 0x88, 5);
SBIT(TR0, 0x88, 4);
SBIT(IE1, 0x88, 3);
SBIT(IT1, 0x88, 2);
SBIT(IE0, 0x88, 1);
SBIT(IT0, 0x88, 0);

SFR(TMOD, 0x89);
SFR(TL0, 0x8A);
SFR(TL1, 0x8B);
SFR(TH0, 0x8C);
SFR(TH1, 0x8D);
SFR(AUXR, 0x8E);
SFR(INTCLKO, 0x8F);

SFR(P1, 0x90);
SBIT(P10, 0x90, 0); SBIT(P1_0, 0x90, 0);
SBIT(P11, 0x90, 1); SBIT(P1_1, 0x90, 1);
SBIT(P12, 0x90, 2); SBIT(P1_2, 0x90, 2);
SBIT(P13, 0x90, 3); SBIT(P1_3, 0x90, 3);
SBIT(P14, 0x90, 4); SBIT(P1_4, 0x90, 4);
SBIT(P15, 0x90, 5); SBIT(P1_5, 0x90, 5);
SBIT(P16, 0x90, 6); SBIT(P1_6, 0x90, 6);
SBIT(P17, 0x90, 7); SBIT(P1_7, 0x90, 7);

SFR(P1M1, 0x91);
SFR(P1M0, 0x92);
SFR(P0M1, 0x93);
SFR(P0M0, 0x94);
SFR(P2M1, 0x95);
SFR(P2M0, 0x96);

SFR(SCON, 0x98);
SBIT(SM0, 0x98, 7);
SBIT(SM1, 0x98, 6);
SBIT(SM2, 0x98, 5);
SBIT(REN, 0x98, 4);
SBIT(TB8, 0x98, 3);
SBIT(RB8, 0x98, 2);
SBIT(TI,  0x98, 1);
SBIT(RI,  0x98, 0);

SFR(SBUF, 0x99);
SFR(S2CON, 0x9A);
SFR(S2BUF, 0x9B);
SFR(IRCBAND, 0x9D);
SFR(LIRTRIM, 0x9E);
SFR(IRTRIM, 0x9F);

SFR(P2, 0xA0);
SBIT(P20, 0xA0, 0); SBIT(P2_0, 0xA0, 0);
SBIT(P21, 0xA0, 1); SBIT(P2_1, 0xA0, 1);
SBIT(P22, 0xA0, 2); SBIT(P2_2, 0xA0, 2);
SBIT(P23, 0xA0, 3); SBIT(P2_3, 0xA0, 3);
SBIT(P24, 0xA0, 4); SBIT(P2_4, 0xA0, 4);
SBIT(P25, 0xA0, 5); SBIT(P2_5, 0xA0, 5);
SBIT(P26, 0xA0, 6); SBIT(P2_6, 0xA0, 6);
SBIT(P27, 0xA0, 7); SBIT(P2_7, 0xA0, 7);

SFR(P_SW1, 0xA2);

SFR(IE, 0xA8);
SBIT(EA,   0xA8, 7);
SBIT(ELVD, 0xA8, 6);
SBIT(EADC, 0xA8, 5);
SBIT(ES,   0xA8, 4);
SBIT(ET1,  0xA8, 3);
SBIT(EX1,  0xA8, 2);
SBIT(ET0,  0xA8, 1);
SBIT(EX0,  0xA8, 0);

SFR(SADDR, 0xA9);
SFR(WKTCL, 0xAA);
SFR(WKTCH, 0xAB);
SFR(S3CON, 0xAC);
SFR(S3BUF, 0xAD);
SFR(TA, 0xAE);
SFR(IE2, 0xAF);

SFR(P3, 0xB0);
SBIT(P30, 0xB0, 0); SBIT(P3_0, 0xB0, 0);
SBIT(P31, 0xB0, 1); SBIT(P3_1, 0xB0, 1);
SBIT(P32, 0xB0, 2); SBIT(P3_2, 0xB0, 2);
SBIT(P33, 0xB0, 3); SBIT(P3_3, 0xB0, 3);
SBIT(P34, 0xB0, 4); SBIT(P3_4, 0xB0, 4);
SBIT(P35, 0xB0, 5); SBIT(P3_5, 0xB0, 5);
SBIT(P36, 0xB0, 6); SBIT(P3_6, 0xB0, 6);
SBIT(P37, 0xB0, 7); SBIT(P3_7, 0xB0, 7);

SFR(P3M1, 0xB1);
SFR(P3M0, 0xB2);
SFR(P4M1, 0xB3);
SFR(P4M0, 0xB4);
SFR(IP2, 0xB5);
SFR(IP2H, 0xB6);
SFR(IPH, 0xB7);

SFR(IP, 0xB8);
SBIT(PPCA, 0xB8, 7);
SBIT(PLVD, 0xB8, 6);
SBIT(PADC, 0xB8, 5);
SBIT(PS,   0xB8, 4);
SBIT(PT1,  0xB8, 3);
SBIT(PX1,  0xB8, 2);
SBIT(PT0,  0xB8, 1);
SBIT(PX0,  0xB8, 0);

SFR(SADEN, 0xB9);
SFR(P_SW2, 0xBA);
SFR(ADC_CONTR, 0xBC);
SFR(ADC_RES, 0xBD);
SFR(ADC_RESL, 0xBE);

SFR(P4, 0xC0);
SBIT(P40, 0xC0, 0); SBIT(P4_0, 0xC0, 0);
SBIT(P41, 0xC0, 1); SBIT(P4_1, 0xC0, 1);
SBIT(P42, 0xC0, 2); SBIT(P4_2, 0xC0, 2);
SBIT(P43, 0xC0, 3); SBIT(P4_3, 0xC0, 3);
SBIT(P44, 0xC0, 4); SBIT(P4_4, 0xC0, 4);
SBIT(P45, 0xC0, 5); SBIT(P4_5, 0xC0, 5);
SBIT(P46, 0xC0, 6); SBIT(P4_6, 0xC0, 6);
SBIT(P47, 0xC0, 7); SBIT(P4_7, 0xC0, 7);

SFR(WDT_CONTR, 0xC1);
SFR(IAP_DATA, 0xC2);
SFR(IAP_ADDRH, 0xC3);
SFR(IAP_ADDRL, 0xC4);
SFR(IAP_CMD, 0xC5);
SFR(IAP_TRIG, 0xC6);
SFR(IAP_CONTR, 0xC7);

SFR(P5, 0xC8);
SBIT(P50, 0xC8, 0); SBIT(P5_0, 0xC8, 0);
SBIT(P51, 0xC8, 1); SBIT(P5_1, 0xC8, 1);
SBIT(P52, 0xC8, 2); SBIT(P5_2, 0xC8, 2);
SBIT(P53, 0xC8, 3); SBIT(P5_3, 0xC8, 3);
SBIT(P54, 0xC8, 4); SBIT(P5_4, 0xC8, 4);
SBIT(P55, 0xC8, 5); SBIT(P5_5, 0xC8, 5);
SBIT(P56, 0xC8, 6); SBIT(P5_6, 0xC8, 6);
SBIT(P57, 0xC8, 7); SBIT(P5_7, 0xC8, 7);

SFR(P5M1, 0xC9);
SFR(P5M0, 0xCA);
SFR(P6M1, 0xCB);
SFR(P6M0, 0xCC);
SFR(SPSTAT, 0xCD);
SFR(SPCTL, 0xCE);
SFR(SPDAT, 0xCF);

SFR(PSW, 0xD0);
SBIT(CY, 0xD0, 7);
SBIT(AC, 0xD0, 6);
SBIT(F0, 0xD0, 5);
SBIT(RS1, 0xD0, 4);
SBIT(RS0, 0xD0, 3);
SBIT(OV, 0xD0, 2);
SBIT(F1, 0xD0, 1);
SBIT(P, 0xD0, 0);

SFR(T4T3M, 0xD1);
SFR(T4H, 0xD2);
SFR(T4L, 0xD3);
SFR(T3H, 0xD4);
SFR(T3L, 0xD5);
SFR(T2H, 0xD6);
SFR(T2L, 0xD7);

SFR(USBCLK, 0xDC);
SFR(ADCCFG, 0xDE);
SFR(IP3, 0xDF);

SFR(ACC, 0xE0);
SFR(P7M1, 0xE1);
SFR(P7M0, 0xE2);
SFR(DPS, 0xE3);
SFR(DPL1, 0xE4);
SFR(DPH1, 0xE5);
SFR(CMPCR1, 0xE6);
SFR(CMPCR2, 0xE7);

SFR(P6, 0xE8);
SBIT(P60, 0xE8, 0); SBIT(P6_0, 0xE8, 0);
SBIT(P61, 0xE8, 1); SBIT(P6_1, 0xE8, 1);
SBIT(P62, 0xE8, 2); SBIT(P6_2, 0xE8, 2);
SBIT(P63, 0xE8, 3); SBIT(P6_3, 0xE8, 3);
SBIT(P64, 0xE8, 4); SBIT(P6_4, 0xE8, 4);
SBIT(P65, 0xE8, 5); SBIT(P6_5, 0xE8, 5);
SBIT(P66, 0xE8, 6); SBIT(P6_6, 0xE8, 6);
SBIT(P67, 0xE8, 7); SBIT(P6_7, 0xE8, 7);

SFR(USBDAT, 0xEC);
SFR(IP3H, 0xEE);
SFR(AUXINTIF, 0xEF);

SFR(B, 0xF0);
SFR(USBCON, 0xF4);
SFR(IAP_TPS, 0xF5);

SFR(P7, 0xF8);
SBIT(P70, 0xF8, 0); SBIT(P7_0, 0xF8, 0);
SBIT(P71, 0xF8, 1); SBIT(P7_1, 0xF8, 1);
SBIT(P72, 0xF8, 2); SBIT(P7_2, 0xF8, 2);
SBIT(P73, 0xF8, 3); SBIT(P7_3, 0xF8, 3);
SBIT(P74, 0xF8, 4); SBIT(P7_4, 0xF8, 4);
SBIT(P75, 0xF8, 5); SBIT(P7_5, 0xF8, 5);
SBIT(P76, 0xF8, 6); SBIT(P7_6, 0xF8, 6);
SBIT(P77, 0xF8, 7); SBIT(P7_7, 0xF8, 7);

SFR(USBADR, 0xFC);
SFR(RSTCFG, 0xFF);

#endif
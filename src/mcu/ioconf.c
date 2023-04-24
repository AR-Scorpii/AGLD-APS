#include "ioconf.h"

void IO_Init(void)
{
    P0M0 = 0x00; 
    P0M1 = 0x70; 

    P1M0 = 0x00; 
    P1M1 = 0x00; 

    // P2M0 = 0x00; 
    // P2M0 = 0xEF; 
    P2M0 = 0xE0; 
    P2M1 = 0x00; 

    P3M0 = 0x00; 
    P3M1 = 0x00; 

    // P4M0 = 0x00; 
    P4M0 = 0x20; 
    P4M1 = 0x00; 

    P5M0 = 0x00; 
    P5M1 = 0x00;

    EAXSFR();
    P0PU = 0x8F; 
}
/**
 * @file        stc8h_int.h
 * 
 * @brief       The interrupt vector list for STC8H series microcontroller. 
 * 
 * @copyright   This is modified from STC official codes. The copyright belongs
 *              to STC. 
 */
#ifndef     __STC8H_INT_H__
#define     __STC8H_INT_H__

/////////////////////////////////////////////////
//Interrupt Vector
/////////////////////////////////////////////////

#define     INT0_VECTOR             0       //0003H
#define     TMR0_VECTOR             1       //000BH
#define     INT1_VECTOR             2       //0013H
#define     TMR1_VECTOR             3       //001BH
#define     UART1_VECTOR            4       //0023H
#define     ADC_VECTOR              5       //002BH
#define     LVD_VECTOR              6       //0033H
#define     UART2_VECTOR            8       //0043H
#define     SPI_VECTOR              9       //004BH
#define     INT2_VECTOR             10      //0053H
#define     INT3_VECTOR             11      //005BH
#define     TMR2_VECTOR             12      //0063H
#define     USER_VECTOR             13      //006BH
#define     INT4_VECTOR             16      //0083H
#define     UART3_VECTOR            17      //008BH
#define     UART4_VECTOR            18      //0093H
#define     TMR3_VECTOR             19      //009BH
#define     TMR4_VECTOR             20      //00A3H
#define     CMP_VECTOR              21      //00ABH
#define     I2C_VECTOR              24      //00C3H
#define     USB_VECTOR              25      //00CBH
#define     PWMA_VECTOR             26      //00D3H
#define     PWMB_VECTOR             27      //00DBH

#define     TKSU_VECTOR             35      //011BH
#define     RTC_VECTOR              36      //0123H
#define     P0INT_VECTOR            37      //012BH
#define     P1INT_VECTOR            38      //0133H
#define     P2INT_VECTOR            39      //013BH
#define     P3INT_VECTOR            40      //0143H
#define     P4INT_VECTOR            41      //014BH
#define     P5INT_VECTOR            42      //0153H
#define     P6INT_VECTOR            43      //015BH
#define     P7INT_VECTOR            44      //0163H
#define     DMA_M2M_VECTOR          47      //017BH
#define     DMA_ADC_VECTOR          48      //0183H
#define     DMA_SPI_VECTOR          49      //018BH
#define     DMA_UR1T_VECTOR         50      //0193H
#define     DMA_UR1R_VECTOR         51      //019BH
#define     DMA_UR2T_VECTOR         52      //01A3H
#define     DMA_UR2R_VECTOR         53      //01ABH
#define     DMA_UR3T_VECTOR         54      //01B3H
#define     DMA_UR3R_VECTOR         55      //01BBH
#define     DMA_UR4T_VECTOR         56      //01C3H
#define     DMA_UR4R_VECTOR         57      //01CBH
#define     DMA_LCM_VECTOR          58      //01D3H
#define     LCM_VECTOR              59      //01DBH

#endif
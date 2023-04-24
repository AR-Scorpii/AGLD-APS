/**
 * @file    regredirect.h
 * 
 * @brief   This file overlaps the register position definitions to enable
 *          cross-compiler compiling. This includes SFR, SBIT, DATA, IDATA, 
 *          PDATA, XDATA and CODE. Corresponding data types are defined. 
 *          Functions of endian swap are provided. 
 * @note    All SFRs should be re-written since the definition method varies. 
 */

#ifndef     __CCD_REGREDIRECT_H__
#define     __CCD_REGREDIRECT_H__

/**** SFRs ********************************************************************/
#if defined __SDCC
    /* compiler is SDCC */
#   define SFR(NAME, POS)       __sfr __at (POS) NAME
#   define SBIT(NAME, POS, BIT) __sbit __at (POS+BIT) NAME
#elif defined __C51__
    /* compiler is Keil C51 */
#   define SFR(NAME, POS)       sfr NAME = POS
#   define SBIT(NAME, POS, BIT) sbit NAME = POS^BIT
#else
    /* unspecified compilers, VIEW ONLY */
#   define SFR(NAME, POS)       unsigned char __attribute__((at(POS))) NAME
#   define SBIT(NAME, POS, BIT) unsigned char __attribute__((at(POS))) NAME
#endif

/**** reg location-compatibility definitions **********************************/
// general purpose
#if defined __SDCC
    /* compiler is SDCC */
#   define DATA     __data
#   define IDATA    __idata
#   define PDATA    __pdata
#   define XDATA    __xdata
#   define CODE     __code
#elif defined __C51__
    /* compiler is Keil C51 */
#   define DATA     data
#   define IDATA    idata
#   define PDATA    pdata
#   define XDATA    xdata
#   define CODE     code
#else
    /* unspecified compilers, VIEW ONLY */
#   define DATA
#   define IDATA
#   define PDATA
#   define XDATA
#   define CODE
#endif
// translation
#if defined __SDCC
    /* compiler is SDCC */
#   define data     __data
#   define idata    __idata
#   define pdata    __pdata
#   define xdata    __xdata
#   define code     __code
#elif defined __C51__
    /* compiler is Keil C51 */
#   define __data   data
#   define __idata  idata
#   define __pdata  pdata
#   define __xdata  xdata
#   define __code  code
#else
    /* unspecified compilers, VIEW ONLY */
#   define data
#   define idata
#   define pdata
#   define xdata
#   define code
#   define __data
#   define __idata
#   define __pdata
#   define __xdata
#   define __code
#endif

/**** data types **************************************************************/
#if defined __SDCC
#   include <stdint.h>
#else
    typedef unsigned char       uint8_t;
    typedef unsigned short int  uint16_t;
    typedef unsigned long int   uint32_t;
#endif

typedef XDATA uint8_t   xuint8_t;
typedef XDATA uint16_t  xuint16_t;
typedef XDATA uint32_t  xuint32_t;
typedef IDATA uint8_t   iuint8_t;
typedef IDATA uint16_t  iuint16_t;
typedef IDATA uint32_t  iuint32_t;
typedef PDATA uint8_t   puint8_t;
typedef PDATA uint16_t  puint16_t;
typedef PDATA uint32_t  puint32_t;
typedef CODE  uint8_t   cuint8_t;
typedef CODE  uint16_t  cuint16_t;
typedef CODE  uint32_t  cuint32_t;

// note that Keil C51 is big endian while the SDCC is little endian! 
#define ENDIANSWAP32(X) ( ((X & 0xFF000000l) >> 24) + ((X & 0x00FF0000l) >>  8) \
                        + ((X & 0x0000FF00l) <<  8) + ((X & 0x000000FFl) << 24) )
#define ENDIANSWAP16(X) ( ((X & 0xFF00) >> 8) + ((X & 0x00FF) << 8) )

#endif
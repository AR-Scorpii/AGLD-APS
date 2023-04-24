#ifndef __MCU_MDU_H__
#define __MCU_MDU_H__

#include "../../inc/stc8h.h"

typedef enum MDU_ValFmt_e
{
    MDU_ValFmt_3to0,
    MDU_ValFmt_1to0,
    MDU_ValFmt_5to4
} MDU_ValFmt_t;

/** 
 * MDU
 * MODE FUNC    DESC
 * 1    RS      [MD3,MD2,MD1,MD0] >>= SC
 * 2    LS      [MD3,MD2,MD1,MD0] <<= SC
 * 3    LALIGN  do left shift s.t. ([MD3,MD2,MD1,MD0] << SC) has the highest bit 1
 * 4    MUL     [MD3,MD2,MD1,MD0]               = [MD1,MD0] * [MD5,MD4]
 * 5    DIV16   [MD1,MD0] ... [MD5,MD4]         = [MD1,MD0] / [MD5,MD4]
 * 6    DIV32   [MD3,MD2,MD1,MD0] ... [MD5,MD4] = [MD3,MD2,MD1,MD0] / [MD5,MD4]
 */
typedef enum MDU_Alg_e
{
    MDU_Alg_RShift  = 1 << 5,
    MDU_Alg_LShift  = 2 << 5,
    MDU_Alg_LAlign  = 3 << 5,
    MDU_Alg_Mul     = 4 << 5,
    MDU_Alg_Div16   = 5 << 5,
    MDU_Alg_Div32   = 6 << 5
} MDU_Alg_t;

void MDU_Reset(void);

void MDU_ValSet(MDU_ValFmt_t, uint32_t);
uint32_t MDU_ValGet(MDU_ValFmt_t);

void MDU_Calc(MDU_Alg_t);

// uint32_t MDU_Calc_RShift(uint32_t, uint8_t);
// uint32_t MDU_Calc_LShift(uint32_t, uint8_t);
// uint32_t MDU_Calc_LAligh(uint32_t);
// uint32_t MDU_Calc_Mul(uint16_t, uint16_t);
// uint16_t MDU_Calc_Div16(uint16_t, uint16_t);
// uint32_t MDU_Calc_Div32(uint32_t, uint16_t);

#endif
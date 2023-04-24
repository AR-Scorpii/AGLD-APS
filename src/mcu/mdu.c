#include "mdu.h"

void MDU_Reset(void)
{
    OPCON |= 0x02;
    while (OPCON & 0x02);
}

void MDU_ValSet(MDU_ValFmt_t fmt, uint32_t val)
{
    switch (fmt)
    {
        case MDU_ValFmt_3to0: 
            MD3 = (val & 0xFF000000) >> 24;
            MD2 = (val & 0x00FF0000) >> 16;
            MD1 = (val & 0x0000FF00) >> 8;
            MD0 = (val & 0x000000FF);
            break;
        case MDU_ValFmt_1to0:
            MD1 = (val & 0x0000FF00) >> 8;
            MD0 = (val & 0x000000FF);
            break;
        case MDU_ValFmt_5to4:
            MD5 = (val & 0x0000FF00) >> 8;
            MD4 = (val & 0x000000FF);
            break;
        default:
            break;
    }
}

uint32_t MDU_ValGet(MDU_ValFmt_t fmt)
{
    uint32_t mdu_md3 = MD3; 
    uint32_t mdu_md2 = MD2; 
    uint32_t mdu_md1 = MD1; 
    uint32_t mdu_md0 = MD0; 
    uint32_t mdu_md5 = MD5; 
    uint32_t mdu_md4 = MD4;
    uint32_t val = 0;

    switch (fmt)
    {
        case MDU_ValFmt_3to0: 
            val = (mdu_md3 << 24) + (mdu_md2 << 16) + (mdu_md1 << 8) + mdu_md0;
            break;
        case MDU_ValFmt_1to0:
            val = (mdu_md1 << 8) + mdu_md0;
            break;
        case MDU_ValFmt_5to4:
            val = (mdu_md5 << 8) + mdu_md4;
            break;
        default:
            val = 0;
            break;
    }

    return val;
}

void MDU_Calc(MDU_Alg_t alg)
{
    ARCON = (ARCON & ~0xE0) | alg;
    OPCON = 0x01;           // start
    while (OPCON & 0x01);   // done!
}
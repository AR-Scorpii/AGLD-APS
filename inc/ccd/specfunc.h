/**
 * @file    specfunc.h
 * 
 * @brief   This file contains the approaches of INTERRUPT and NOP. 
 */
#ifndef     __CCD_SPECFUNC_H__
#define     __CCD_SPECFUNC_H__

/**** interrupt ***************************************************************/
// general purpose
#if defined __SDCC
    /* compiler is SDCC */
#   define INTERRUPT(N)     __interrupt N
#elif defined __C51__
    /* compiler is Keil C51 */
#   define INTERRUPT(N)     interrupt N
#else
    /* unspecified compilers, VIEW ONLY */
#   define INTERRUPT(N)
#endif
// translation
#if defined __SDCC
    /* compiler is SDCC */
#   define interrupt        __interrupt
#elif defined __C51__
    /* compiler is Keil C51 */
#   define __interrupt      interrupt
#else
    /* unspecified compilers, VIEW ONLY */
#   define interrupt
#   define __interrupt
#endif

/**** nop *********************************************************************/
#if defined __SDCC
    /* compiler is SDCC */
#   define NOP_DEF()        __asm__("nop")
#elif defined __C51__
    /* compiler is Keil C51 */
#   define NOP_DEF()        _nop_()
#else
    /* unspecified compilers, VIEW ONLY */
#   define NOP_DEF()
#endif
#define NOP1()      NOP_DEF()
#define NOP2()      NOP1(); NOP1()
#define NOP3()      NOP2(); NOP1()
#define NOP4()      NOP3(); NOP1()
#define NOP5()      NOP4(); NOP1()
#define NOP6()      NOP5(); NOP1()
#define NOP7()      NOP6(); NOP1()
#define NOP8()      NOP7(); NOP1()
#define NOP9()      NOP8(); NOP1()
#define NOP10()     NOP9(); NOP1()
#define NOP11()     NOP10(); NOP1()
#define NOP12()     NOP11(); NOP1()
#define NOP13()     NOP12(); NOP1()
#define NOP14()     NOP13(); NOP1()
#define NOP15()     NOP14(); NOP1()
#define NOP16()     NOP15(); NOP1()
#define NOP17()     NOP16(); NOP1()
#define NOP18()     NOP17(); NOP1()
#define NOP19()     NOP18(); NOP1()
#define NOP20()     NOP19(); NOP1()
#define NOP21()     NOP20(); NOP1()
#define NOP22()     NOP21(); NOP1()
#define NOP23()     NOP22(); NOP1()
#define NOP24()     NOP23(); NOP1()
#define NOP25()     NOP24(); NOP1()
#define NOP26()     NOP25(); NOP1()
#define NOP27()     NOP26(); NOP1()
#define NOP28()     NOP27(); NOP1()
#define NOP29()     NOP28(); NOP1()
#define NOP30()     NOP29(); NOP1()
#define NOP31()     NOP30(); NOP1()
#define NOP32()     NOP31(); NOP1()
#define NOP33()     NOP32(); NOP1()
#define NOP34()     NOP33(); NOP1()
#define NOP35()     NOP34(); NOP1()
#define NOP36()     NOP35(); NOP1()
#define NOP37()     NOP36(); NOP1()
#define NOP38()     NOP37(); NOP1()
#define NOP39()     NOP38(); NOP1()
#define NOP40()     NOP39(); NOP1()
#define NOP(N)      NOP##N()

#endif
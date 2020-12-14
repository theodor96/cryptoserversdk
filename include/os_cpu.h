/**************************************************************************************************
 *
 *  Description : Public definition for inlining CPU instructions and access CPU registers
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco IS GmbH
 *
 **************************************************************************************************/
#ifndef __OS_CPU_H_PUB_INCLUDED__
#define __OS_CPU_H_PUB_INCLUDED__

#ifdef CS2_SDK
  #define asm(a)
  #define cregister
#endif

unsigned int  os_cpu_dp_get (void);
void          os_cpu_dp_set (unsigned int);
unsigned int  os_cpu_sp_get (void);

#ifndef CS2_SDK

  unsigned int _extu    (unsigned int, unsigned int, unsigned int);
  int          _ext     (int, unsigned int, unsigned int);
  unsigned int _set     (unsigned int, unsigned int, unsigned int);
  unsigned int _clr     (unsigned int, unsigned int, unsigned int);
  unsigned int _extur   (unsigned int, int);
  int          _extr    (int, int);
  unsigned int _setr    (unsigned int, int);
  unsigned int _clrr    (unsigned int, int);
  int          _sshl    (int, unsigned int);
  int          _add2    (int, int);
  int          _sub2    (int, int);
  unsigned int _subc    (unsigned int, unsigned int);
  unsigned int _lmbd    (unsigned int, unsigned int);
  int          _abs     (int);
  unsigned int _norm    (int);
  int          _smpy    (int, int);
  int          _smpyhl  (int, int);
  int          _smpylh  (int, int);
  int          _smpyh   (int, int);
  int          _mpy     (int, int);
  int          _mpyus   (unsigned int, int);
  int          _mpysu   (int, unsigned int);
  unsigned int _mpyu    (unsigned int, unsigned int);
  int          _mpyhl   (int, int);
  int          _mpyhuls (unsigned int, int);
  int          _mpyhslu (int, unsigned int);
  unsigned int _mpyhlu  (unsigned int, unsigned int);
  int          _mpylh   (int, int);
  int          _mpyluhs (unsigned int, int);
  int          _mpylshu (int, unsigned int);
  unsigned int _mpylhu  (unsigned int, unsigned int);
  int          _mpyh    (int, int);
  int          _mpyhus  (unsigned int, int);
  int          _mpyhsu  (int, unsigned int);
  unsigned int _mpyhu   (unsigned int, unsigned int);

  extern cregister volatile unsigned int AMR;
  extern cregister volatile unsigned int CSR;
  extern cregister volatile unsigned int IFR;
  extern cregister volatile unsigned int ISR;
  extern cregister volatile unsigned int ICR;
  extern cregister volatile unsigned int IER;
  extern cregister volatile unsigned int ISTP;
  extern cregister volatile unsigned int IRP;
  extern cregister volatile unsigned int NRP;
#else
  /**********************************************************************************************
   *
   * ATTENTION: START OF HOST SECTION
   *
   **********************************************************************************************/
  #define _extu(a,b,c)    (((a) << (b)) >> (c))

  #define _mpy(a,b)       ((int) ( (short) (a) *  (short) (b) ) )
  #define _mpyu(a,b)      ((unsigned int) ( ((unsigned int)(unsigned short) (a)) *  (unsigned short) (b) ) )
  #define _mpyhl(a,b)     ((int) ( (short) (( (unsigned int) (a) & 0x0FFFF0000u) >> 16) *  (short) (b) ) )
  #define _mpyhlu(a,b)    ((unsigned int) ( ((unsigned int)(unsigned short) (( (unsigned int) (a) & 0x0FFFF0000u) >> 16)) *  (unsigned short) (b) ) )
  #define _mpylh(a,b)     ((int) ( (short) (( (unsigned int) (b) & 0x0FFFF0000u) >> 16) *  (short) (a) ) )
  #define _mpylhu(a,b)    ((unsigned int) ( ((unsigned int)(unsigned short) (( (unsigned int) (b) & 0x0FFFF0000u) >> 16)) *  (unsigned short) (a) ) )
  #define _mpyh(a,b)      ((int) ( (short) (( (unsigned int) (a) & 0x0FFFF0000u) >> 16) \
                                 * (short) (( (unsigned int) (b) & 0x0FFFF0000u) >> 16) ) )
  #define _mpyhu(a,b)     ((unsigned int) ( ((unsigned int)(unsigned short) (( (unsigned int) (a) & 0x0FFFF0000u) >> 16)) \
                                 * (unsigned short) (( (unsigned int) (b) & 0x0FFFF0000u) >> 16) ) )

  #ifdef OSYS_win
    static _inline unsigned int _lmbd
  #else
    static inline unsigned int _lmbd
  #endif
  (
    unsigned int bit,
    unsigned int src
  )  
  {
    unsigned int reply = 0;
    unsigned int mask = 0x80000000;

    if ((bit & 1) == 0)
      src = ~src;

    while (mask)
    {
      if (src & mask)
        break;

      reply += 1;

      mask >>= 1;
    }

    return (reply);
  }
  #endif

#endif /* __OS_CPU_H_PUB_INCLUDED__ */

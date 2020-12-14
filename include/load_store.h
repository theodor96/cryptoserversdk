  /*****************************************************************************
 *                                                                           
 *  Filename    : load_store.h                                               
 *                                                                           
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco 
 *
 * !!! Master location of this file is "fs/cs2/lib/util_src"
 *
 *****************************************************************************/
#ifndef __LOAD_STORE_H_INCLUDED__
#define __LOAD_STORE_H_INCLUDED__

#ifdef CS2_SDK
  #if defined(OSYS_win) || defined(WIN32)
    #define _LD_ST_INLINE _inline
  #else
    #define _LD_ST_INLINE static inline
  #endif
#else
  #define _LD_ST_INLINE inline
#endif

_LD_ST_INLINE void store_int1(unsigned int val,unsigned char *x)
{
  *x   = (unsigned char)val;
}

_LD_ST_INLINE void store_int2(unsigned int val,unsigned char *x)
{
  *x++ = (unsigned char)(val >> 8);
  *x   = (unsigned char)val;
}
  
_LD_ST_INLINE void store_int3(unsigned int val,unsigned char *x)
{
  *x++ = (unsigned char)(val >> 16);
  *x++ = (unsigned char)(val >> 8);
  *x   = (unsigned char)val;
}

#ifdef _TMS320C6400

_LD_ST_INLINE void store_int4(unsigned int val,unsigned char *x)
{
  _mem4(x) = val;
}

#else

_LD_ST_INLINE void store_int4(unsigned int val,unsigned char *x)
{
  *x++ = (unsigned char)(val >> 24);
  *x++ = (unsigned char)(val >> 16);
  *x++ = (unsigned char)(val >> 8);
  *x   = (unsigned char)val;
}

#endif

_LD_ST_INLINE unsigned int load_int1(const unsigned char *x)
{
  return x[0];
}

_LD_ST_INLINE unsigned int load_int2(const unsigned char *x)
{
  return( (x[0] << 8) + x[1] );
}

_LD_ST_INLINE unsigned int load_int3(const unsigned char *x)
{
  return( (x[0] << 16) + (x[1] << 8) + x[2] );
}

#ifdef _TMS320C6400

_LD_ST_INLINE unsigned int load_int4(const unsigned char *x)
{
  return(_mem4_const(x));
}

#else

_LD_ST_INLINE unsigned int load_int4(const unsigned char *x)
{
  return( (x[0] << 24) + (x[1] << 16) + (x[2] << 8) + x[3] );
}

#endif

_LD_ST_INLINE unsigned int load_int(const unsigned char *x, int len)
{
  switch (len)
  {    
    case 1: return *x;
    case 2: return load_int2(x);
    case 3: return load_int3(x);
    case 4: return load_int4(x);
  }
  return 0;
}

#undef _LD_ST_INLINE


#ifdef CS2_SDK

#define _load_int2(x)      load_int2(x)
#define _load_int4(x)      load_int4(x)

#define _store_int2(v,x)   store_int2(v,x)
#define _store_int4(v,x)   store_int4(v,x)

#else

#define _load_int2(x)      (*((unsigned short *)(x)))
#define _load_int4(x)      (*((unsigned int *)(x)))

#define _store_int2(v,x)   (*((unsigned short *)(x))) = (v)
#define _store_int4(v,x)   (*((unsigned int *)(x))) = (v)

#endif


#endif /* __LOAD_STORE_H_INCLUDED__ */

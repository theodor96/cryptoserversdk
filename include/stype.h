/*****************************************************************************
 *
 *  Filename    : sytpe.h
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 * 
 * !!! Master location of this file is "fs/cs2/lib/util_src"
 *                                                                           
 *****************************************************************************/
#ifndef __STYPE_H_INCLUDED__
#define __STYPE_H_INCLUDED__

#ifdef CS2_SDK
  #ifndef MDL_GLOBAL
  #define MDL_GLOBAL
  #endif

  #define MDL_CONST       const

  #define FILE_GLOBAL     static
  #define FILE_CONST      static const

  #ifndef FAR
  #define FAR
  #endif             

  #define INIT_AUTO
  #define INIT_STAT       static const

  #define LOCAL_STAT      static

#if defined(OSYS_win) || defined (WIN32)
  #define INLINE          _inline 
#else
  #define INLINE          inline
#endif

  #define RESTRICT

  #define INTERRUPT
#else

  #ifndef MDL_GLOBAL
  #define MDL_GLOBAL      far
  #endif

  #define MDL_CONST       const far

  #define FILE_GLOBAL     static far
  #define FILE_CONST      static const far

  #ifndef FAR
  #define FAR             far
  #endif

  #define INIT_AUTO       far
  #define INIT_STAT       static const far

  #define LOCAL_STAT      static far

  #define INLINE          inline

  #define RESTRICT        restrict
  
  #define INTERRUPT       interrupt

#endif /* CS2_SDK */


#endif /* __STYPE_H_INCLUDED__ */

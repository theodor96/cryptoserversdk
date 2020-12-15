/**************************************************************************************************
 *
 *  Description : Functions used to handle a ASCII strings
 *                Public header file
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 **************************************************************************************************/
#ifndef __OS_STR_H_PUB_INCLUDED__
#define __OS_STR_H_PUB_INCLUDED__

#include "os.h"

#include "stdarg.h"

typedef void (T_PUTCC)(int c);

/*************************************************************************************************
 * Structure definitions
 *************************************************************************************************/
typedef struct _os_str_public_interface
{
  char* (*_p_os_str_cat ) (      char*, const char*);
  char* (*_p_os_str_chr ) (const char*,       char);
  int   (*_p_os_str_cmp ) (const char*, const char*);
  void  (*_p_os_str_cpy ) (      char*, const char*);
  unsigned int (*_p_os_str_len ) (const char*);
  char* (*_p_os_str_nchr) (const char*,       char,  unsigned int);
  int   (*_p_os_str_ncmp) (const char*, const char*, unsigned int);
  void  (*_p_os_str_ncpy) (      char*, const char*, unsigned int);
  char* (*_p_os_str_nstr) (const char*, const char*, unsigned int);
  char* (*_p_os_str_rchr) (const char*,       char);
  char* (*_p_os_str_str ) (const char*, const char*);
  int   (*_p_os_str_match)(unsigned char *str,unsigned char *pattern);
  void  (*_p_os_str_vcprintf)(T_PUTCC *put, unsigned char *p_str, va_list ap);
  // new as of SMOS 5.1.0.0
  int   (*_p_os_str_snprintf)(unsigned char *buf, unsigned int ct, char *format, ...);
  int   (*_p_os_str_split)(unsigned char *p_buf, unsigned int l_buf, char sep, unsigned int *p_nvalues, unsigned char ***ppp_values);
}
T_OS_STR_TABLE_PUB;

#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

  /*** C-style linking of the modules ***********************************************************
   * This section contains the C-style function prototypes. It is active when the modules are
   * linked together using the linker or a shared library (i.e., in the SDK). It is also used
   * for the module itself.
   **********************************************************************************************/
  extern char* os_str_cat  (      char* p_str1, const char* p_str2);
  extern char* os_str_chr  (const char* p_str,        char  c);
  extern int   os_str_cmp  (const char* p_str1, const char* p_str2);
  extern void  os_str_cpy  (      char* p_dst,  const char* p_src );
  extern unsigned int   os_str_len  (const char* p_str);
  extern char* os_str_nchr (const char* p_str,        char  c,      unsigned int cnt);
  extern int   os_str_ncmp (const char* p_str1, const char* p_str2, unsigned int cnt);
  extern void  os_str_ncpy (      char* p_dst,  const char* p_src,  unsigned int cnt);
  extern char* os_str_nstr (const char* p_str1, const char* p_str2, unsigned int cnt);
  extern char* os_str_rchr (const char* p_str,        char  c);
  extern char* os_str_str  (const char* p_str1, const char* p_str2);
  extern int   os_str_match(unsigned char *str,unsigned char *pattern);
  extern void  os_str_vcprintf(T_PUTCC *put, unsigned char *p_str, va_list ap);
  extern int   os_str_snprintf(unsigned char *buf, unsigned int ct, char *format, ...);
  extern int   os_str_split(unsigned char *p_buf, unsigned int l_buf, char sep, unsigned int *p_nvalues, unsigned char ***ppp_values);

#else
  /*** SMOS linking of the modules **************************************************************
   * This section is active when dynamic loading/linking of the modules using the Module Loader
   * is in effect.
   **********************************************************************************************/

  /************************************************************************************************
   * macros to use the public interface and global data of key server module
   ************************************************************************************************/
  #define _P_OS_STR  ((T_OS_STR_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_str))

  #define os_str_cat      _P_OS_STR->_p_os_str_cat
  #define os_str_chr      _P_OS_STR->_p_os_str_chr
  #define os_str_cmp      _P_OS_STR->_p_os_str_cmp
  #define os_str_cpy      _P_OS_STR->_p_os_str_cpy
  #define os_str_len      _P_OS_STR->_p_os_str_len
  #define os_str_nchr     _P_OS_STR->_p_os_str_nchr
  #define os_str_ncmp     _P_OS_STR->_p_os_str_ncmp
  #define os_str_ncpy     _P_OS_STR->_p_os_str_ncpy
  #define os_str_nstr     _P_OS_STR->_p_os_str_nstr
  #define os_str_rchr     _P_OS_STR->_p_os_str_rchr
  #define os_str_str      _P_OS_STR->_p_os_str_str
  #define os_str_match    _P_OS_STR->_p_os_str_match
  #define os_str_vcprintf _P_OS_STR->_p_os_str_vcprintf
  #define os_str_snprintf _P_OS_STR->_p_os_str_snprintf
  #define os_str_split    _P_OS_STR->_p_os_str_split

#endif /* defined(_OS_C_INT_) || defined(_ALWAYS_C_INT_) */

/* --- BEGIN ERROR CODES --- */
#define E_OS_STR                          0xB0000A    // string section
#define E_OS_STR_MALLOC                   0xB0000A01  // memory allocation failed

/* --- END ERROR CODES --- */

#endif

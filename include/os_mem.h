/**************************************************************************************************
 *
 *  Description : Memory Management
 *                Public header file
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 **************************************************************************************************/
#ifndef __OS_MEM_H_PUB_INCLUDED__
#define __OS_MEM_H_PUB_INCLUDED__

#include "os.h"
#ifdef _TMS320C6400
#include <string.h>
#endif

/************************************************************************************************
 * define memory types
 ************************************************************************************************/
typedef enum
{
  OS_MEM_TYPE_ID,                              // memory type is internal data RAM
  OS_MEM_TYPE_KC,                              // obsolete
  OS_MEM_TYPE_SD,                              // memory type is SDRAM

  OS_MEM_NUM_MEM_TYPES                         // must be the last entry
}
T_OS_MEM_TYPE;

#define OS_MEM_TYPE_SECURE   OS_MEM_TYPE_ID    // general name for secure protected space

/**********************************************************************************************
 * define macros to clear memory areas
 **********************************************************************************************/
#define   os_mem_clr(a,b)  os_mem_set(a,0,b)

/**********************************************************************************************
 * define structure for memory info
 **********************************************************************************************/
typedef struct
{
  unsigned int   used_blocks;
  unsigned int   used_bytes;
  unsigned int   free_blocks;
  unsigned int   free_bytes;
  unsigned int   free_largest_area;
}
T_OS_MEM_INFO;

/**********************************************************************************************
 * define structure for memory trace
 **********************************************************************************************/
typedef struct
{
  unsigned int tag;
  const char   *file;
  unsigned int line;
  unsigned int size[2];
}
T_OS_MEM_BLOCK;


/*************************************************************************************************
 * Structure definitions
 *************************************************************************************************/
typedef struct _os_mem_public_interface
{
  void          (*_p_os_mem_and      ) (const void*, const void*, void*, unsigned int);
  int           (*_p_os_mem_cmp      ) (const void*, const void*, unsigned int);
  void          (*_p_os_mem_cpy      ) (void*, const void*, unsigned int);
  void          (*_p_os_mem_del      ) (void*);
  void*         (*_p_os_mem_new      ) (unsigned int size, T_OS_MEM_TYPE mem_type);
  void*         (*_p_os_mem_sys_new  ) (unsigned int size, T_OS_MEM_TYPE mem_type);
  void          (*_p_os_mem_set      ) (void*, unsigned char, unsigned int);
  void          (*_p_os_mem_xor      ) (const void*, const void*, void*, unsigned int);
  void          *dumy;
  void          (*_p_os_mem_del_set  ) (void*, unsigned char);
  int           (*_p_os_mem_info     ) (T_OS_MEM_TYPE mem_type, T_OS_MEM_INFO *p_info);
  int           (*_p_os_mem_check    ) (void *p_mem, unsigned int *p_size);
  T_OS_MEM_TYPE (*_p_os_mem_get_type ) (void *);
  // new as of SMOS 4.2.0.0
  void*         (*_p_os_mem_new_tag  ) (unsigned int size, T_OS_MEM_TYPE mem_type, const char *file, unsigned int line);
  int           (*_p_os_mem_trace    ) (T_OS_MEM_BLOCK *p_mem_list, unsigned int max_cnt, unsigned int *p_cnt);
  // new as of SMOS 5.0.0.0
  int           (*_p_os_mem_scmp     ) (const void *mem1, const void *mem2, unsigned int len1, unsigned int len2);
  int           (*_p_os_mem_tst      ) (void *mem, int ch, unsigned int len);
  // new as of SMOS 5.5.5.0
  int           (*_p_os_mem_cmp_ti   ) (const void *mem1, const void *mem2, int len);
}
T_OS_MEM_TABLE_PUB;

#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

  /*** C-style linking of the modules ***********************************************************
   * This section contains the C-style function prototypes. It is active when the modules are
   * linked together using the linker or a shared library. It is also used
   * for the module itself.
   **********************************************************************************************/
  #define               os_mem_cmp       memcmp
  #define               os_mem_cpy       memcpy
  #define               os_mem_set       memset

  extern void           os_mem_and       (const void *p_op1, const void *p_op2, void* p_dst, unsigned int cnt);
  extern void           os_mem_del       (void *p_mem);
  extern void           os_mem_del       (void *p_mem);
  extern void           *os_mem_new      (unsigned int size, T_OS_MEM_TYPE mem_type);
  extern void           os_mem_xor       (const void *p_op1, const void *p_op2, void *p_dst, unsigned int cnt);
  extern void           os_mem_del_set   (void *p_mem, unsigned char value);
  extern void           os_mem_init      (void);
  extern int            os_mem_info      (T_OS_MEM_TYPE mem_type, T_OS_MEM_INFO *p_info);
  extern int            os_mem_check     (void *p_mem, unsigned int *p_size);
  extern T_OS_MEM_TYPE  os_mem_get_type  (void *p_mem);
  // new as of SMOS 4.2.0.0
  extern void           *os_mem_new_tag  (unsigned int size, T_OS_MEM_TYPE mem_type, const char *file, unsigned int line);
  extern int            os_mem_trace     (T_OS_MEM_BLOCK *p_mem_list, unsigned int max_cnt, unsigned int *p_cnt);
  // new as of SMOS 5.0.0.0
  extern int            os_mem_scmp      (const void *mem1, const void *mem2, unsigned int len1, unsigned int len2);
  extern int            os_mem_tst       (void *mem, int ch, unsigned int len);
  // new as of SMOS 5.5.5.0
  extern int            os_mem_cmp_ti    (const void *mem1, const void *mem2, int len);

#else
  /*** smos linking of the modules **************************************************************
   * This section is active when dynamic loading/linking of the modules using the Module Loader
   * is in effect.
   **********************************************************************************************/

  /************************************************************************************************
   * macros to use the public interface and global data of smos memory management
   ************************************************************************************************/
  #define _P_OS_MEM  ((T_OS_MEM_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_mem))

  #define os_mem_and            _P_OS_MEM->_p_os_mem_and
  #define os_mem_cmp            _P_OS_MEM->_p_os_mem_cmp
  #define os_mem_cpy            _P_OS_MEM->_p_os_mem_cpy
  #define os_mem_del            _P_OS_MEM->_p_os_mem_del
#ifdef MEM_TRACE
  #define os_mem_new(size,type) _P_OS_MEM->_p_os_mem_new_tag((size),(type),__FILE__,__LINE__)
#else
  #define os_mem_new            _P_OS_MEM->_p_os_mem_new
#endif
  #define os_mem_sys_new        _P_OS_MEM->_p_os_mem_sys_new
  #define os_mem_set            _P_OS_MEM->_p_os_mem_set
  #define os_mem_xor            _P_OS_MEM->_p_os_mem_xor
  #define os_mem_del_set        _P_OS_MEM->_p_os_mem_del_set
  #define os_mem_info           _P_OS_MEM->_p_os_mem_info
  #define os_mem_get_type       _P_OS_MEM->_p_os_mem_get_type
  #define os_mem_check          _P_OS_MEM->_p_os_mem_check
  // new as of SMOS 4.2.0.0
  #define os_mem_new_tag        _P_OS_MEM->_p_os_mem_new_tag
  #define os_mem_trace          _P_OS_MEM->_p_os_mem_trace
  // new as of SMOS 5.0.0.0
  #define os_mem_smcp           _P_OS_MEM->_p_os_mem_scmp
  #define os_mem_tst            _P_OS_MEM->_p_os_mem_tst
  // new as of SMOS 5.5.5.0
  #define os_mem_cmp_ti         _P_OS_MEM->_p_os_mem_cmp_ti


#endif /* defined(_OS_C_INT_) || defined(_ALWAYS_C_INT_) */

/************************************************************************************************
 * define error codes
 ************************************************************************************************/

/* --- BEGIN ERROR CODES --- */

#define E_OS_MEM                           0xB00009     // memory section

#define E_OS_MEM_BAD_TYPE                  0xB0000901   // illegal memory type
#define E_OS_MEM_CORR                      0xB0000902   // corrupted memory structure
#define E_OS_MEM_BUF_SIZE                  0xB0000903   // buffer size too small
#define E_OS_MEM_BAD_ADDR                  0xB0000904   // bad memory address

/* --- END ERROR CODES --- */


#endif /* ifndef __OS_MEM_H_PUB_INCLUDED__ */

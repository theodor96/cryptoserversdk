/**************************************************************************************************
 *
 *  Description : Public definitions for FIFO function module
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Georg Weber
 *                Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 **************************************************************************************************/
#ifndef __OS_FIFO_H_PUB_INCLUDED__
#define __OS_FIFO_H_PUB_INCLUDED__

#include "os.h"
#include "os_mem.h"

#define OS_TASK_NO_WAIT      0xFFFFFFFF

/*************************************************************************************************
 * Structure definitions
 *************************************************************************************************/
typedef struct _os_fifo_public_interface
{
  void           (*_p_os_fifo_del         ) (void*);
  unsigned int   (*_p_os_fifo_get_cnt     ) (void*);
  unsigned int   (*_p_os_fifo_get_cnt_free) (void*);
  void           *dumy1;
  void           *dumy2;
  void           *(*_p_os_fifo_new         ) (unsigned int, T_OS_MEM_TYPE);
  void           *dumy3;
  int            (*_p_os_fifo_rd          ) (void*, void**, unsigned int);
  int            (*_p_os_fifo_wr          ) (void*, void*, unsigned int);
} T_OS_FIFO_TABLE_PUB;

#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

  extern void          os_fifo_del          (void* p_fifo);
  extern unsigned int  os_fifo_get_cnt      (void* p_fifo);
  extern unsigned int  os_fifo_get_cnt_free (void* p_fifo);
  extern void          *os_fifo_new         (unsigned int size, T_OS_MEM_TYPE mem_type);
  extern int           os_fifo_rd           (void* p_fifo, void** p_data, unsigned int dly_cnt);
  extern int           os_fifo_wr           (void* p_fifo, void*  data,   unsigned int dly_cnt);

#else
  /*** smos linking of the modules **************************************************************
   * This section is active when dynamic loading/linking of the modules using the Module Loader
   * is in effect.
   **********************************************************************************************/

  /************************************************************************************************
   * macros to use the public interface and global data of key server module
   ************************************************************************************************/
  #define _P_OS_FIFO  ((T_OS_FIFO_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_fifo))

  #define os_fifo_del           _P_OS_FIFO->_p_os_fifo_del
  #define os_fifo_get_cnt       _P_OS_FIFO->_p_os_fifo_get_cnt
  #define os_fifo_get_cnt_free  _P_OS_FIFO->_p_os_fifo_get_cnt_free
  #define os_fifo_new           _P_OS_FIFO->_p_os_fifo_new
  #define os_fifo_rd            _P_OS_FIFO->_p_os_fifo_rd
  #define os_fifo_wr            _P_OS_FIFO->_p_os_fifo_wr

#endif /* defined(_OS_C_INT_) || defined(_ALWAYS_C_INT_) */

#endif

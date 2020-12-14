/**************************************************************************************************
 *
 *  Description : Semaphores
 *                Public header file
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 **************************************************************************************************/
#ifndef __OS_SEMA_H_PUB_INCLUDED__
#define __OS_SEMA_H_PUB_INCLUDED__

#include "os_mem.h"
#include "os.h"

// public interface
typedef struct _os_sema_public_interface
{
  void  (*_p_os_sema_del)(void *p_sema);
  void *(*_p_os_sema_new)(T_OS_MEM_TYPE mem_type);
  int   (*_p_os_sema_req)(void *p_sema, unsigned int dly_cnt);
  void  (*_p_os_sema_rls)(void *p_sema);
}
T_OS_SEMA_TABLE_PUB;

#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

  extern void  os_sema_del(void *p_sema);
  extern void *os_sema_new(T_OS_MEM_TYPE mem_type);
  extern int   os_sema_req(void *p_sema, unsigned int dly_cnt);
  extern void  os_sema_rls(void *p_sema);

#else
  /*** smos linking of the modules **************************************************************
   * This section is active when dynamic loading/linking of the modules using the Module Loader
   * is in effect.
   **********************************************************************************************/

  /************************************************************************************************
   * macros to use the public interface and global data of key server module
   ************************************************************************************************/
  #define _P_OS_SEMA  ((T_OS_SEMA_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_sema))

  #define os_sema_del _P_OS_SEMA->_p_os_sema_del
  #define os_sema_new _P_OS_SEMA->_p_os_sema_new
  #define os_sema_req _P_OS_SEMA->_p_os_sema_req
  #define os_sema_rls _P_OS_SEMA->_p_os_sema_rls

#endif /* defined(_OS_C_INT_) || defined(_ALWAYS_C_INT_) */


#endif


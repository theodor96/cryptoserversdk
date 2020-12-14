/**************************************************************************************************
 *
 *  Description : Timer Functions
 *                Public header file
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 **************************************************************************************************/
#ifndef __OS_TMR_H_PUB_INCLUDED__
#define __OS_TMR_H_PUB_INCLUDED__

#include "os_mem.h"
#include "os.h"

/************************************************************************************************
 * define possible timer resolutions
 ************************************************************************************************/
typedef enum
{
  OS_TMR_RES_10ms,                           /* Timer with a resolution of  10 milliseconds   */
  OS_TMR_RES_100ms,                          /* Timer with a resolution of 100 milliseconds   */
  OS_TMR_RES_1s,                             /* Timer with a resolution of   1 second         */
  OS_TMR_RES_1min,                           /* Timer with a resolution of   1 minute         */
  OS_TMR_RES_1h,                             /* Timer with a resolution of   1 hour           */
  OS_TMR_RES_1d,                             /* Timer with a resolution of   1 day            */

  OS_TMR_RES_COUNT                           /* Number of timers used                         */
}
T_OS_TMR_RES;


/*************************************************************************************************
 * Structure definitions
 *************************************************************************************************/
typedef struct _os_tmr_public_interface
{
  void         (*_p_os_tmr_adjust     ) (void* , unsigned int );
  void         (*_p_os_tmr_del        ) (void*                );
  int          (*_p_os_tmr_expired    ) (void*                );
  void        *(*_p_os_tmr_new        ) (unsigned int, unsigned int, void*, T_OS_TMR_RES, T_OS_MEM_TYPE);
  void         (*_p_os_tmr_start      ) (void* , unsigned int);
  void         (*_p_os_tmr_stop       ) (void*                );
  unsigned int (*_p_os_tmr_cnt_get    ) (void*                );
  void         (*_p_os_tmr_get_clk    ) (unsigned int *,unsigned int *);
} 
T_OS_TMR_TABLE_PUB;

#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

  /*** C-style linking of the modules ***********************************************************
   * This section contains the C-style function prototypes. It is active when the modules are
   * linked together using the linker or a shared library (i.e., in the SDK). It is also used
   * for the module itself.
   **********************************************************************************************/
  extern void  os_tmr_adjust     (void* p_tmr, unsigned int tmr_value);
  extern void  os_tmr_del        (void* p_tmr);
  extern int   os_tmr_expired    (void* p_tmr);
  extern void *os_tmr_new        (unsigned int tmr_value, unsigned int event, void* task_id,
                                  T_OS_TMR_RES resolution, T_OS_MEM_TYPE mem_type);
  extern void  os_tmr_start      (void* p_tmr,  unsigned int tmr_value);
  extern void  os_tmr_stop       (void* p_tmr);
  extern unsigned int  os_tmr_cnt_get    (void* p_tmr);
  extern void  os_tmr_task_id_del(void* p_task_id);
  extern void  os_tmr_get_clk    (unsigned int *p_sec,unsigned int *p_frac);
#else
  /*** smos linking of the modules **************************************************************
   * This section is active when dynamic loading/linking of the modules using the Module Loader
   * is in effect.
   **********************************************************************************************/

  /************************************************************************************************
   * macros to use the public interface and global data of key server module
   ************************************************************************************************/
  #define _P_OS_TMR  ((T_OS_TMR_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_tmr))

  #define os_tmr_adjust       _P_OS_TMR->_p_os_tmr_adjust
  #define os_tmr_del          _P_OS_TMR->_p_os_tmr_del
  #define os_tmr_expired      _P_OS_TMR->_p_os_tmr_expired
  #define os_tmr_new          _P_OS_TMR->_p_os_tmr_new
  #define os_tmr_start        _P_OS_TMR->_p_os_tmr_start
  #define os_tmr_stop         _P_OS_TMR->_p_os_tmr_stop
  #define os_tmr_cnt_get      _P_OS_TMR->_p_os_tmr_cnt_get
  #define os_tmr_get_clk      _P_OS_TMR->_p_os_tmr_get_clk

#endif /* defined(_OS_C_INT_) || defined(_ALWAYS_C_INT_) */

#endif

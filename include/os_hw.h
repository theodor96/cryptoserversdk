/**************************************************************************************************
 *
 *  Description : Hardware dependent types and definitions
 *                Public header file
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco IS GmbH
 *
 **************************************************************************************************/
#ifndef __OS_HW_H_PUB_INCLUDED__
#define __OS_HW_H_PUB_INCLUDED__

#include <os.h>

typedef enum
{
   OS_HW_TMR_NUM0
  ,OS_HW_TMR_NUM1
  ,OS_HW_TMR_NUM2
#ifdef _TMS320C6457
  ,OS_HW_TMR_NUM3
#endif
}
T_OS_HW_TMR_NUM;


// modes for os_hw_panic:
#define OS_HW_PANIC_HALT      0
#define OS_HW_PANIC_REBOOT    1

/*************************************************************************************************
 * Structure definitions
 *************************************************************************************************/
typedef struct _os_hw_public_interface
{
  unsigned int(*_p_os_hw_get_cpu_frequency) (void);
  void        (*_p_os_hw_tmr_init)  (T_OS_HW_TMR_NUM tmr_nr, unsigned int cycle_cnt, void (*p_irq_fct) (void));
  void        (*_p_os_hw_delay_clk) (unsigned int);
  void        (*_p_os_hw_delay_tps) (unsigned int);
  void        (*_p_os_hw_panic)     (int,unsigned short);
  unsigned int(*_p_os_hw_get_clk)   (void);
  void        (*_p_os_hw_dma_cpy)   (unsigned int *dst,unsigned int *src,int ct);
  void        (*_p_os_hw_delay_ns)  (unsigned int);
}
T_OS_HW_TABLE_PUB;

#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

  extern unsigned int os_hw_get_cpu_frequency (void);
  extern void         os_hw_tmr_init(T_OS_HW_TMR_NUM tmr_nr, unsigned int cycle_cnt, void (*p_irq_fct) (void));
  extern void         delay0(unsigned int);
  extern void         os_hw_delay_tps(unsigned int);
  extern void         os_hw_panic(int mode,unsigned short reason);
  extern unsigned int os_hw_get_clk(void);
  extern void         os_hw_dma_cpy(unsigned int *dst,unsigned int *src,int ct);
  extern void         os_hw_delay_ns(unsigned int);

#else

  #define _P_OS_HW  ((T_OS_HW_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_hw))

  #define os_hw_get_cpu_frequency _P_OS_HW->_p_os_hw_get_cpu_frequency
  #define os_hw_tmr_init          _P_OS_HW->_p_os_hw_tmr_init
  #define os_hw_delay_clk         _P_OS_HW->_p_os_hw_delay_clk
  #define os_hw_delay_tps         _P_OS_HW->_p_os_hw_delay_tps
  #define os_hw_panic             _P_OS_HW->_p_os_hw_panic
  #define os_hw_get_clk           _P_OS_HW->_p_os_hw_get_clk
  #define os_hw_dma_copy          _P_OS_HW->_p_os_hw_dma_cpy
  #define os_hw_delay_ns          _P_OS_HW->_p_os_hw_delay_ns

#endif

#endif


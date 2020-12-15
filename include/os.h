 /**************************************************************************************************
 *
 *  Description : Public definitions for all SMOS header files
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 **************************************************************************************************/
#ifndef __OS_H_PUB_INCLUDED__
#define __OS_H_PUB_INCLUDED__

#include "stype.h"

typedef struct _os_public_interface_and_data
{
  const void  *p_data;
  const void  *p_rfu1;
  const void  *p_os_i2c;                       /* pointer to os_i2c.h   function pointer table  */
  const void  *p_os_crypt;                     /* pointer to os_crypt.h function pointer table  */
  const void  *p_os_dev;                       /* pointer to os_dev.h   function pointer table  */
  const void  *p_os_rtc;                       /* pointer to os_rtc.h   function pointer table  */
  const void  *p_os_fifo;                      /* pointer to os_fifo.h  function pointer table  */
  const void  *p_os_file;                      /* pointer to os_file.h  function pointer table  */
  const void  *p_os_irq;                       /* pointer to os_irq.h   function pointer table  */
  const void  *p_os_link;                      /* pointer to os_link.h  function pointer table  */
  const void  *p_os_log;                       /* pointer to os_log.h   function pointer table  */
  const void  *p_os_mdl;                       /* pointer to os_mdl.h   function pointer table  */
  const void  *p_os_mem;                       /* pointer to os_mem.h   function pointer table  */
  const void  *p_os_sema;                      /* pointer to os_sema.h  function pointer table  */
  const void  *p_os_audit;                     /* pointer to os_audit.h function pointer table  */
  const void  *p_os_str;                       /* pointer to os_str.h   function pointer table  */
  const void  *p_rfu3;
  const void  *p_rfu4;
  const void  *p_os_task;                      /* pointer to os_task.h  function pointer table  */
  const void  *p_os_tmr;                       /* pointer to os_tmr.h   function pointer table  */
  const void  *p_os_sens;                      /* pointer to os_sens.h  function pointer table  */
  const void  *p_os_pci;                       /* pointer to os_pci.h   function pointer table  */
  const void  *p_os_hw;                        /* pointer to os_hw.h    function pointer table  */
  const void  *p_os_usb;                       /* pointer to os_usb.h   function pointer table  */  
  const void  *p_os_cfg;                       /* pointer to os_cfg.h   function pointer table  */
}
T_OS_TABLE_PUB;


/************************************************************************************************
 * define constant for the module handling, alias is module handle
 ************************************************************************************************/
typedef void*    T_OS_MDL_HDL;                 /* address of the jump table to access the       */
                                               /* module public function interface and data     */

#if !defined(_SMOS_C_INT_) && !defined(_ALWAYS_C_INT_)

extern T_OS_MDL_HDL MDL_GLOBAL P_SMOS;

#endif

/* Error Codes:  (0xB0000000 | (CMDS_MDL_ID << 16) | (errno))  */

/* --- BEGIN ERROR CODES --- */

#define E_OS                              0xB000          // CryptoServer module SMOS

#define E_OS_PNC_0                        0xB00050        // panic message
#define E_OS_PNC_BL                       0xB0005001      // Can't start bootloader (CRC)
#define E_OS_PNC_SDRAM                    0xB0005002      // Can't start bootloader (SDRAM error)
#define E_OS_PNC_PCI                      0xB000500B      // PCI interface closed
#define E_OS_PNC_MEMORY                   0xB000500C      // memory corruption detected

#define E_OS_PNC_3                        0xB00053        // shutdown message
#define E_OS_PNC_HIGH_TEMP                0xB0005306      // High temperature
#define E_OS_PNC_RESET_ALARM              0xB000530A      // Alarm reseted
#define E_OS_PNC_CLEAR                    0xB000530E      // CryptoServer cleared
#define E_OS_PNC_HALT                     0xB0005344      // CryptoServer halted


/* --- END ERROR CODES --- */


#endif /* __OS_H_PUB_INCLUDED__ */

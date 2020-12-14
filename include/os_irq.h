/**************************************************************************************************
 *
 *  Description : Interrupts
 *                Public header file
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco IS GmbH
 *
 **************************************************************************************************/
#ifndef __OS_IRQ_H_PUB_INCLUDED__
#define __OS_IRQ_H_PUB_INCLUDED__

#include "os.h"

// Define values to select an interrupt source in the interrupt multiplexer registers.
#ifdef _TMS320C6457
  #define OS_IRQ_SEL_TINT0_LO     4     // Timer 0 lower counter interrupt
  #define OS_IRQ_SEL_TINT0_HI     5     // Timer 0 higher counter interrupt
  #define OS_IRQ_SEL_TINT1_LO     6     // Timer 1 lower counter interrupt
  #define OS_IRQ_SEL_TINT1_HI     7     // Timer 1 higher counter interrupt

  #define OS_IRQ_SEL_GPIO9        9     // External interrupt 0  (used for PCI)
  #define OS_IRQ_SEL_GPIO10       10    // External interrupt 1
  #define OS_IRQ_SEL_GPIO11       11    // External interrupt 2
  #define OS_IRQ_SEL_GPIO12       12    // External interrupt 3  (used for USB)
  #define OS_IRQ_SEL_GPIO13       13    // SPI_RDY

#else
  #define OS_IRQ_SEL_DSPINT       0x00000000uL
  #define OS_IRQ_SEL_TINT0        0x00000001uL
  #define OS_IRQ_SEL_TINT1        0x00000002uL
  #define OS_IRQ_SEL_SD_INT       0x00000003uL
  #define OS_IRQ_SEL_EXT_INT4     0x00000004uL
  #define OS_IRQ_SEL_EXT_INT5     0x00000005uL
  #define OS_IRQ_SEL_EXT_INT6     0x00000006uL
  #define OS_IRQ_SEL_EXT_INT7     0x00000007uL
  #define OS_IRQ_SEL_DMA_INT0     0x00000008uL
  #define OS_IRQ_SEL_XINT0        0x0000000CuL
  #define OS_IRQ_SEL_RINT0        0x0000000DuL
  #define OS_IRQ_SEL_XINT1        0x0000000EuL
  #define OS_IRQ_SEL_RINT1        0x0000000FuL
  #define OS_IRQ_SEL_XINT2        0x00000011uL
  #define OS_IRQ_SEL_RINT2        0x00000012uL
  #define OS_IRQ_SEL_TINT2        0x00000013uL
#endif

// Define values to select an interrupt source for the additional IRQs (Model 2000 + 2064 only)
#ifndef _TMS320C6457
  #define OS_IRQ_SEL_CPLD_FLAG     0x100
  #define OS_IRQ_SEL_CPLD_MASK     0x01F

  #define OS_IRQ_SEL_PCI_MBI       0x100
  #define OS_IRQ_SEL_PCI_MBO       0x101
  #define OS_IRQ_SEL_PCI_BIST      0x104
  #define OS_IRQ_SEL_UARTA         0x105
  #define OS_IRQ_SEL_UARTB         0x106
#endif

// Structure definitions
typedef struct _os_irq_public_interface
{
  void         (*_p_os_irq_clear  ) (unsigned int);
  void         (*_p_os_irq_disable) (unsigned int);
  void         (*_p_os_irq_enable ) (unsigned int);
  unsigned int (*_p_os_irq_off    ) (void);
  void         (*_p_os_irq_on     ) (unsigned int);
  void         (*_p_os_irq_vec_rmv) (unsigned int);
  void         (*_p_os_irq_vec_set) (void (*)(void), unsigned int);
}
T_OS_IRQ_TABLE_PUB;

#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

  /*** C-style linking of the modules ***********************************************************
   * This section contains the C-style function prototypes. It is active when the modules are
   * linked together using the linker or a shared library (i.e., in the SDK). It is also used
   * for the module itself.
   **********************************************************************************************/
  extern void         os_irq_clear   (unsigned int irq_sel);
  extern void         os_irq_disable (unsigned int irq_sel);
  extern void         os_irq_enable  (unsigned int irq_sel);
  extern unsigned int os_irq_off     (void);
  extern void         os_irq_on      (unsigned int irq_status);
  extern void         os_irq_vec_rmv (unsigned int irq_sel);
  extern void         os_irq_vec_set (void (*p_irq_fct)(void), unsigned int irq_sel);

  extern void         os_irq_init    (void);

#else
  /*** smos linking of the modules **************************************************************
   * This section is active when dynamic loading/linking of the modules using the Module Loader
   * is in effect.
   **********************************************************************************************/

  /************************************************************************************************
   * macros to use the public interface and global data of key server module
   ************************************************************************************************/
  #define _P_OS_IRQ  ((T_OS_IRQ_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_irq))

  #define os_irq_clear    _P_OS_IRQ->_p_os_irq_clear
  #define os_irq_disable  _P_OS_IRQ->_p_os_irq_disable
  #define os_irq_enable   _P_OS_IRQ->_p_os_irq_enable
  #define os_irq_off      _P_OS_IRQ->_p_os_irq_off
  #define os_irq_on       _P_OS_IRQ->_p_os_irq_on
  #define os_irq_vec_rmv  _P_OS_IRQ->_p_os_irq_vec_rmv
  #define os_irq_vec_set  _P_OS_IRQ->_p_os_irq_vec_set

#endif /* defined(_OS_C_INT_) || defined(_ALWAYS_C_INT_) */

#endif

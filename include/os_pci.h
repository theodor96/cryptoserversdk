/**************************************************************************************************
 *
 *  Description : PCI driver
 *                Public header file
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 **************************************************************************************************/
#ifndef __OS_PCI_H_PUB_INCLUDED__
#define __OS_PCI_H_PUB_INCLUDED__

typedef struct _os_pci_public_interface
{
  int             (*_p_os_pci_open            ) (void);
  int             (*_p_os_pci_get_request     ) (unsigned int *);
  int             (*_p_os_pci_recv            ) (unsigned char *,unsigned int);
  int             (*_p_os_pci_cancel          ) (unsigned int);
  int             (*_p_os_pci_send            ) (unsigned char *,unsigned int);
  int             (*_p_os_pci_close           ) (void);
}
T_OS_PCI_TABLE_PUB;

#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

  extern void     os_pci_init         (void);
  extern int      os_pci_open         (void);
  extern int      os_pci_get_request  (unsigned int *);
  extern int      os_pci_recv         (unsigned char *,unsigned int);
  extern int      os_pci_cancel       (unsigned int);
  extern int      os_pci_send         (unsigned char *,unsigned int);
  extern int      os_pci_close        (void);
  extern void     os_pci_panic_message(unsigned int);
  extern void     os_pci_stop         (unsigned int);  
  extern void     os_pci_signal       (unsigned int code);
#else
    
  #define _P_OS_PCI   ((T_OS_PCI_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_pci))

  #define os_pci_open             _P_OS_PCI->_p_os_pci_open
  #define os_pci_get_request      _P_OS_PCI->_p_os_pci_get_request
  #define os_pci_recv             _P_OS_PCI->_p_os_pci_recv
  #define os_pci_cancel           _P_OS_PCI->_p_os_pci_cancel
  #define os_pci_send             _P_OS_PCI->_p_os_pci_send
  #define os_pci_close            _P_OS_PCI->_p_os_pci_close

#endif /* defined(_OS_C_INT_) || defined(_ALWAYS_C_INT_) */


/* Error Codes:  (0xB0000000 | (CMDS_MDL_ID << 16) | (errno))  */

/* --- BEGIN ERROR CODES --- */

#define E_OS_PCI                          0xB00010        // PCI section

#define E_OS_PCI_DMA_TMOUT                0xB0001000      // DMA timeout
#define E_OS_PCI_CANCEL                   0xB0001001      // request canceled
#define E_OS_PCI_MBR_RD_TMOUT             0xB0001002      // MBR read timeout
#define E_OS_PCI_MBR_WR_TMOUT             0xB0001003      // MBR write timeout
#define E_OS_PCI_MBR_CMD                  0xB0001004      // bad MBR command
#define E_OS_PCI_RX_CRC                   0xB0001005      // rx crc error
#define E_OS_PCI_NOT_IMPL                 0xB0001006      // function not implememted
#define E_OS_PCI_SHUTDOWN                 0xB0001007      // shutdown request received
#define E_OS_PCI_MEM                      0xB0001008      // memory allocation failed
#define E_OS_PCI_SEQCT                    0xB0001009      // bad sequence counter
#define E_OS_PCI_RD_TMOUT                 0xB000100A      // read timeout
#define E_OS_PCI_WR_TMOUT                 0xB000100B      // write timeout
#define E_OS_PCI_LENERR                   0xB000100C      // block length error
#define E_OS_PCI_SOCKET                   0xB000100D      // socket error
#define E_OS_PCI_STATE                    0xB000100E      // bad state for receive
#define E_OS_PCI_TIMEOUT                  0xB000100F      // timeout

/* --- END ERROR CODES --- */


#endif /* __OS_PCI_H_PUB_INCLUDED__ */

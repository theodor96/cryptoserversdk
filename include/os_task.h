/**************************************************************************************************
 *
 *  Description : Task Scheduler
 *                Public header file
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco IS GmbH
 *
 **************************************************************************************************/
#ifndef __OS_TASK_H_PUB_INCLUDED__
#define __OS_TASK_H_PUB_INCLUDED__

#include "os.h"
#include "os_mem.h"
#include "os_link.h"

/* --- BEGIN ERROR CODES --- */

#define E_OS_TASK                          0xB00006    // task section

#define E_OS_TASK_STACK_OVL                0xB0000601  // stack overflow
#define E_OS_TASK_STACK_CORR               0xB0000602  // stack corrupted
#define E_OS_TASK_BUFSIZE                  0xB0000603  // buffer size to small
#define E_OS_TASK_MALLOC                   0xB0000604  // memory allocation failed

/* --- END ERROR CODES --- */


/************************************************************************************************
 * define events
 ************************************************************************************************/

// Serial Line
#define OS_TASK_EV_SL_TX          0x00000001   // UART byte transmit event
#define OS_TASK_EV_SL_RX          0x00000002   // UART byte receive event

// Task Wait Queue
#define OS_TASK_EV_QUEUE_RDY      0x00000010

// Module Initialization
#define OS_TASK_EV_MDL_SUCCEED    0x00000020   // the selected module terminates with the reached state
#define OS_TASK_EV_MDL_ERROR      0x00000040   // the selected module terminates due a system timeout or an error

// USB (Se Series)
#define OS_TASK_EV_USB_SIE1MSG    0x00000100   // SIE mailbox message
#define OS_TASK_EV_USB_SIE2MSG    0x00000200   // SIE mailbox message
#define OS_TASK_EV_USB_MBX_OUT    0x00000400   // mailbox message

// USB (CSe + Se2 Series)
#define OS_TASK_EV_USB0_TDL_RDY   0x00000100   // Execution of TDL0 ready
#define OS_TASK_EV_USB1_TDL_RDY   0x00000200   // Execution of TDL1 ready
#define OS_TASK_EV_USB0_CONNECT   0x00000400   // USB port 0 connect event
#define OS_TASK_EV_USB1_CONNECT   0x00000800   // USB port 1 connect event

// Sensory Controller
#define OS_TASK_EV_SPI_MSP        0x00001000   // MSP ready event

// public definition of a task control block
struct t_os_task_tcb;
typedef struct t_os_task_tcb T_OS_TASK_TCB;

/************************************************************************************************
 * define task parameter structure
 ************************************************************************************************/
typedef struct
{
  const char     *p_name;                      // task name
  unsigned int   nr;                           // task number
  char           prior;                        // task priority
  unsigned int   stack_size;                   // size of stack in bytes
  void           *p_init;                      // parameter will be passed in A4
  void           (*p_task) (void*);            // start address of task
  T_OS_MEM_TYPE  mem_type_tcb;                 // memory type for task control block
  T_OS_MEM_TYPE  mem_type_stack;               // memory type for stack
}
T_OS_TASK_PAR;

/************************************************************************************************
 * task info structure
 ************************************************************************************************/
typedef struct
{
  unsigned int  size;                           // sizeof(T_OS_TASK_INFO)
  unsigned int  state;                          // OS_TASK_STATE_XXX
  const char    *p_name;                        // task name
  char          prior;                          // task priority
  unsigned int  dly_cnt;                        // number of timer ticks until timeout
  unsigned int  event_got;                      // bit list for reveiced events
  unsigned int  event_list;                     // bit list with events the task waits for
  int           error;                          // task global error code added
  unsigned int  stack_size;                     // initial stack size
  unsigned int  stack_min;                      // maximum stack size used ever
}
T_OS_TASK_INFO;

#define OS_TASK_STATE_READY   0
#define OS_TASK_STATE_DELAY   1
#define OS_TASK_STATE_WAIT    2

/************************************************************************************************
 * define public constants
 ************************************************************************************************/
#define OS_TASK_NAME_LEN     16
#define OS_TASK_ID_INVALID   0
#define OS_TASK_HZ           25                          // ticks per second

typedef struct _os_task_public_interface
{
  void            (*_p_os_task_del            ) (T_OS_TASK_TCB *p_tcb, void *dummy);
  void            (*_p_os_task_dly            ) (unsigned int dly_cnt);
  unsigned int    (*_p_os_task_dly_wait       ) (unsigned int dly_cnt, unsigned int event_list);
  void            (*_p_os_task_event_flush    ) (T_OS_TASK_TCB *p_tcb, unsigned int event_list);
  unsigned short  (*_p_os_task_event_get_cnt  ) (T_OS_TASK_TCB *p_tcb, unsigned int event);
  void            (*_p_os_task_event_rls      ) (T_OS_TASK_TCB *p_tcb, unsigned int event, unsigned short cnt);
  T_OS_TASK_TCB*  (*_p_os_task_id_get         ) (void);
  T_OS_TASK_TCB*  (*_p_os_task_new            ) (const T_OS_TASK_PAR *p_par);
  char            (*_p_os_task_prior_set      ) (T_OS_TASK_TCB *p_tcb, char prior);
  T_OS_TASK_TCB*  (*_p_os_task_queue_wakeup   ) (T_OS_LINK_HEAD *p_head);
  int             (*_p_os_task_queue_wait     ) (T_OS_LINK_HEAD *p_head, unsigned int dly_cnt);
  unsigned int    (*_p_os_task_wait           ) (unsigned int event_list);
  void            (*_p_os_task_wakeup         ) (T_OS_TASK_TCB *p_tcb, unsigned int event);
  int             (*_p_os_task_errno_get      ) (void);
  void            (*_p_os_task_errno_set      ) (int error);
  void            (*_p_os_task_global_data_set) (void *p_data);
  void*           (*_p_os_task_global_data_get) (T_OS_TASK_TCB *p_tcb);
  int             (*_p_os_task_check_stack    ) (unsigned int *p_actual_free, unsigned int *p_minimum_free);
  // new as of SMOS 4.2.0.0
  int             (*_p_os_task_info           ) (T_OS_TASK_INFO *p_task_list, unsigned int max_cnt, unsigned int *p_cnt);
}
T_OS_TASK_TABLE_PUB;

#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

  extern void           os_task_del             (T_OS_TASK_TCB *p_tcb, void *dummy);
  extern void           os_task_dly             (unsigned int dly_cnt);
  extern unsigned int   os_task_dly_wait        (unsigned int dly_cnt, unsigned int event_list);
  extern void           os_task_event_flush     (T_OS_TASK_TCB *p_tcb, unsigned int event_list);
  extern unsigned short os_task_event_get_cnt   (T_OS_TASK_TCB *p_tcb, unsigned int event);
  extern void           os_task_event_rls       (T_OS_TASK_TCB *p_tcb, unsigned int event, unsigned short cnt);
  extern T_OS_TASK_TCB* os_task_id_get          (void);
  extern T_OS_TASK_TCB* os_task_new             (const T_OS_TASK_PAR *p_par);
  extern char           os_task_prior_set       (T_OS_TASK_TCB *p_tcb, char prior);
  extern T_OS_TASK_TCB* os_task_queue_wakeup    (T_OS_LINK_HEAD *p_head);
  extern int            os_task_queue_wait      (T_OS_LINK_HEAD *p_head, unsigned int dly_cnt);
  extern unsigned int   os_task_wait            (unsigned int event_list);
  extern void           os_task_wakeup          (T_OS_TASK_TCB *p_tcb, unsigned int event);
  extern int            os_task_errno_get       (void);
  extern void           os_task_errno_set       (int error);
  extern void           os_task_global_data_set (void *p_data);
  extern void*          os_task_global_data_get (T_OS_TASK_TCB *p_tcb);
  extern int            os_task_check_stack     (unsigned int *p_actual_free, unsigned int *p_minimum_free);
  // new as of SMOS 4.2.0.0
  extern int            os_task_info            (T_OS_TASK_INFO *p_task_list, unsigned int max_cnt, unsigned int *p_cnt);

#else
  /*** smos linking of the modules **************************************************************
   * This section is active when dynamic loading/linking of the modules using the Module Loader
   * is in effect.
   **********************************************************************************************/

  /************************************************************************************************
   * macros to use the public interface and global data of key server module
   ************************************************************************************************/
  #define _P_OS_TASK  ((T_OS_TASK_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_task))

  #define os_task_del              _P_OS_TASK->_p_os_task_del
  #define os_task_dly              _P_OS_TASK->_p_os_task_dly
  #define os_task_dly_wait         _P_OS_TASK->_p_os_task_dly_wait
  #define os_task_event_flush      _P_OS_TASK->_p_os_task_event_flush
  #define os_task_event_get_cnt    _P_OS_TASK->_p_os_task_event_get_cnt
  #define os_task_event_rls        _P_OS_TASK->_p_os_task_event_rls
  #define os_task_id_get           _P_OS_TASK->_p_os_task_id_get
  #define os_task_new              _P_OS_TASK->_p_os_task_new
  #define os_task_prior_set        _P_OS_TASK->_p_os_task_prior_set
  #define os_task_queue_wakeup     _P_OS_TASK->_p_os_task_queue_wakeup
  #define os_task_queue_wait       _P_OS_TASK->_p_os_task_queue_wait
  #define os_task_wait             _P_OS_TASK->_p_os_task_wait
  #define os_task_wakeup           _P_OS_TASK->_p_os_task_wakeup
  #define os_task_errno_get        _P_OS_TASK->_p_os_task_errno_get
  #define os_task_errno_set        _P_OS_TASK->_p_os_task_errno_set
  #define os_task_global_data_set  _P_OS_TASK->_p_os_task_global_data_set
  #define os_task_global_data_get  _P_OS_TASK->_p_os_task_global_data_get
  #define os_task_check_stack      _P_OS_TASK->_p_os_task_check_stack
  // new as of SMOS 4.2.0.0
  #define os_task_info             _P_OS_TASK->_p_os_task_info

#endif /* defined(_OS_C_INT_) || defined(_ALWAYS_C_INT_) */

#ifdef CS2_SDK
  #if defined(OSYS_win) || defined(WIN32)
    #include "windows.h"

    typedef DWORD                       T_OS_TASK_TLS_HDL;

    #define os_task_tls_create(p_hdl)   (((*p_hdl) = TlsAlloc()) == TLS_OUT_OF_INDEXES ? GetLastError() : 0)
    #define os_task_tls_delete(hdl)     TlsFree((hdl))

    #define os_task_tls_set(hdl,value)  (TlsSetValue((hdl),(value)) == 0 ? GetLastError() : 0)
    #define os_task_tls_get(hdl)        TlsGetValue((hdl))

  #else
    #ifndef _GNU_SOURCE
    #define _GNU_SOURCE
    #endif
    #include "pthread.h"

    typedef pthread_key_t               T_OS_TASK_TLS_HDL;

    #define os_task_tls_create(p_hdl)   pthread_key_create(p_hdl, NULL);
    #define os_task_tls_delete(hdl)     pthread_key_delete((hdl))

    #define os_task_tls_set(hdl,value)  pthread_setspecific((hdl),(value))
    #define os_task_tls_get(hdl)        pthread_getspecific((hdl))

  #endif

#else
  typedef int                           T_OS_TASK_TLS_HDL;

  #define os_task_tls_create(p_hdl)     (void)(p_hdl)
  #define os_task_tls_delete(hdl)

  #define os_task_tls_set(hdl,value)
  #define os_task_tls_get(hdl)
#endif

#endif

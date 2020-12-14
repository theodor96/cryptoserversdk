/**************************************************************************************************
 *
 *  Description : Logging
 *                Public header file
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 **************************************************************************************************/
#ifndef __OS_LOG_H_PUB_INCLUDED__
#define __OS_LOG_H_PUB_INCLUDED__

#include "os.h"

typedef struct _os_log_public_interface
{
  int  (*_p_os_log_entry_write) (const unsigned char  creator_id,
                                 const unsigned char  type,
                                 const int            reason_code,
                                 const char           *p_text,
                                 const unsigned int   data_len,
                                 const void           *p_data );
  void (*_p_os_log_print)(unsigned char *p_str, ...);
  void (*_p_os_log_xprint)(char *p_txt,void *p_data,int len);
  void (*_p_os_log_get_boot)(unsigned char **pp_boot_log,unsigned int *p_l_boot_log);
}
T_OS_LOG_TABLE_PUB;

#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)
  /*** C-style linking of the modules ***********************************************************
   * This section contains the C-style function prototypes. It is active when the modules are
   * linked together using the linker or a shared library (i.e., in the SDK). It is also used
   * for the module itself.
   **********************************************************************************************/

  extern int os_log_entry_write
  (
    const unsigned char  creator_id,    // I - ID of the creator of the logbook entry
    const unsigned char  type,          // I - identifier for the type of logbook entry that should be written
    const int            reason_code,   // I - reason code for the logbook entry.
    const char           *p_text,       // I - ptr to a string with additional data for that should be written into the logbook  entry. Can be NULL
    const unsigned int   data_len,      // I -
    const void           *p_data        // I - ptr to a byte buffer with additional data that should be written into the logbook entry. Can be NULL
  );

  extern void os_log_print(unsigned char *p_str, ...);
  extern void os_log_xprint(char *p_txt,void *p_data,int len);
  extern void os_log_get_boot(unsigned char **pp_boot_log,unsigned int *p_l_boot_log);

#else
  /*** SMOS linking of the modules **************************************************************
   * This section is active when dynamic loading/linking of the modules using the Module Loader
   * is in effect.
   **********************************************************************************************/
  #define _P_OS_LOG  ((T_OS_LOG_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_log))

  #define os_log_entry_write         _P_OS_LOG->_p_os_log_entry_write
  #define os_log_print               _P_OS_LOG->_p_os_log_print
  #define os_log_xprint              _P_OS_LOG->_p_os_log_xprint
  #define os_log_get_boot            _P_OS_LOG->_p_os_log_get_boot

#endif /* defined(_OS_C_INT_) || defined(_ALWAYS_C_INT_) */


/************************************************************************************************
 * MACROS
 ************************************************************************************************/

// the following macros are for entries that are always made, regardless of OS_LOG_DEBUG setting
#define OS_LOG_TYPE_ERROR_FATAL          0x01
#define OS_LOG_TYPE_ERROR                0x02
#define OS_LOG_TYPE_WARNING              0x03
#define OS_LOG_TYPE_INFO                 0x05

#define OS_LOG_ENTRY_INFO(creator, reason, p_text, data_len, p_data)  \
        os_log_entry_write(creator, OS_LOG_TYPE_INFO, reason, p_text, data_len, p_data)
#define OS_LOG_ENTRY_WARNING(creator, reason, p_text, data_len, p_data)  \
        os_log_entry_write(creator, OS_LOG_TYPE_WARNING, reason, p_text, data_len, p_data)
#define OS_LOG_ENTRY_ERROR(creator, reason, p_text, data_len, p_data)  \
        os_log_entry_write(creator, OS_LOG_TYPE_ERROR, reason, p_text, data_len, p_data)
#define OS_LOG_ENTRY_ERROR_FATAL(creator, reason, p_text, data_len, p_data)  \
        os_log_entry_write(creator, OS_LOG_TYPE_ERROR_FATAL, reason, p_text, data_len, p_data)


#endif /* __OS_LOG_H_PUB_INCLUDED__ */

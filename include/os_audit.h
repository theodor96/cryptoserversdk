/**************************************************************************************************
 *
 *  Description : Audit Logging
 *                Public header file
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 **************************************************************************************************/
#ifndef __OS_AUDIT_PUB_INCLUDED__
#define __OS_AUDIT_PUB_INCLUDED__

#include "os.h"
#include "stdarg.h"

// audit classes
#define OS_AUDIT_CLASS_FIRMWARE       0x00000001  // default
#define OS_AUDIT_CLASS_USER           0x00000002  // default
#define OS_AUDIT_CLASS_TIME           0x00000004  // default
#define OS_AUDIT_CLASS_STARTUP        0x00000008  // default
#define OS_AUDIT_CLASS_AUDIT          0x00000010  // default
#define OS_AUDIT_CLASS_MBK            0x00000020  // default
#define OS_AUDIT_CLASS_KEY            0x00000040
#define OS_AUDIT_CLASS_AUTH_SUCCESS   0x00000080
#define OS_AUDIT_CLASS_AUTH_FAILED    0x00000100  // default
#define OS_AUDIT_CLASS_BACKUP_RESTORE 0x00000200  // default
#define OS_AUDIT_CLASS_SYSTEM         0x00000400  // default

#define OS_AUDIT_CLASS_CUSTOM_MASK    0x7F000000  // mask for custom audit classes
#define OS_AUDIT_CLASS_RESERVED       0x80000000  // reserved, do not use
#define OS_AUDIT_CLASS_ALWAYS         (0xffffffff)

// audit management operations (os_audit_manage)
enum
{
  OS_AUDIT_MANOP_LOG_READ = 1,
  OS_AUDIT_MANOP_LOG_CLEAR,
  OS_AUDIT_MANOP_CFG_GET,
  OS_AUDIT_MANOP_CFG_SET,
  OS_AUDIT_MANOP_CFG_READ,
  OS_AUDIT_MANOP_CFG_WRITE,
  OS_AUDIT_MANOP_LOG_READ_FILE,
  OS_AUDIT_MANOP_LOG_CLEAR_FILES,
  OS_AUDIT_MANOP_LOG_INFO
};

// audit log parameter on os_audit_manage [OS_AUDIT_MANOP_LOG_READ]
typedef struct
{
  unsigned char *p_data;
  unsigned int  len;
}
T_OS_AUDIT_LOG;

// configuration item parameter on os_audit_manage [OS_AUDIT_MANOP_CFG_GET/SET]
typedef struct
{
  unsigned int  id;
  unsigned int  ivalue;
}
T_OS_AUDIT_CFG_ITEM;

// config item ids
#define OS_AUDIT_CFG_FILE_MAX     1
#define OS_AUDIT_CFG_FILE_ROTATE  2
#define OS_AUDIT_CFG_FILE_SIZE    3
#define OS_AUDIT_CFG_CLASS_MASK   4

// info structure returned by os_audit_info
typedef struct
{
  unsigned int  version;          // struct version (:= OS_AUDIT_INFO_VERSION)  
    
  unsigned int  record_size_max;  // usable record size 
    
  unsigned int  file_first;       // first file number
  unsigned int  file_no;          // current file number
  unsigned int  file_size;        // current file size
  
  unsigned int  file_size_max;
  unsigned char file_count_max;
  unsigned char file_rotate;
}
T_OS_AUDIT_INFO;

#define OS_AUDIT_INFO_VERSION   2

typedef struct _os_audit_public_interface
{
  int  (*_p_os_audit_write)(unsigned int mclass,unsigned char *p_str, ...);
  int  (*_p_os_audit_read)(unsigned int file_no,unsigned int *p_len,unsigned char *p_data);
  int  (*_p_os_audit_clear)(unsigned int leave);
  int  (*_p_os_audit_write_ex)(unsigned int mclass,unsigned int l_uinfo,unsigned char *p_uinfo,unsigned char *p_str,va_list);
  int  (*_p_os_audit_cfg_read) (T_OS_AUDIT_CFG_ITEM **pp_cfg, unsigned int *p_cnt);
  int  (*_p_os_audit_cfg_write)(T_OS_AUDIT_CFG_ITEM *p_cfg, unsigned int cnt);
  // new interface as of SMOS 5.4.0.0
  int  (*_p_os_audit_open)  (const char *basename, void **p_hdl);
  int  (*_p_os_audit_close) (void *hdl);
  int  (*_p_os_audit_entry) (void *hdl, unsigned int mclass, unsigned int l_extra, unsigned char *p_extra, unsigned char *format, va_list ap);
  int  (*_p_os_audit_print) (void *hdl, unsigned int mclass, unsigned char *format, ...);
  int  (*_p_os_audit_manage)(void *hdl, unsigned int manop, void *param, unsigned int *value);
  // new as of SMOS 5.6.0.0
  int  (*_p_os_audit_read_file)(unsigned int *file_no, unsigned int *p_len, unsigned char *p_data);
  // new as of SMOS 5.6.1.0
  int  (*_p_os_audit_clear_files)(unsigned int *file_max, unsigned int *file_min);
  // new as of SMOS 5.6.3.0
  int  (*_p_os_audit_info)(T_OS_AUDIT_INFO *p_info);
}
T_OS_AUDIT_TABLE_PUB;


#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

void os_audit_init(void);
int  os_audit_write(unsigned int mclass,unsigned char *p_str,...);
int  os_audit_read(unsigned int file_no,unsigned int *p_len, unsigned char *p_data);
int  os_audit_clear(unsigned int leave);
int  os_audit_write_ex(unsigned int mclass,unsigned int l_uinfo,unsigned char *p_uinfo,unsigned char *p_str,va_list);
int  os_audit_sys(unsigned int len, unsigned char *data);
int  os_audit_cfg_read (T_OS_AUDIT_CFG_ITEM **pp_cfg, unsigned int *p_cnt);
int  os_audit_cfg_write(T_OS_AUDIT_CFG_ITEM *p_cfg, unsigned int cnt);
// new interface as of SMOS 5.4.0.0
int  os_audit_open  (const char *basename, void **p_hdl);
int  os_audit_close (void *hdl);
int  os_audit_entry (void *hdl, unsigned int mclass, unsigned int l_extra, unsigned char *p_extra, unsigned char *format, va_list ap);
int  os_audit_print (void *hdl, unsigned int mclass, unsigned char *format, ...);
int  os_audit_manage(void *hdl, unsigned int idx, void *param, unsigned int *value);
// new as of SMOS 5.6.0.0
int  os_audit_read_file(unsigned int *file_no, unsigned int *p_len, unsigned char *p_data);
// new as of SMOS 5.6.1.0
int  os_audit_clear_files(unsigned int *file_max, unsigned int *file_min);
// new as of SMOS 5.6.3.0
int  os_audit_info(T_OS_AUDIT_INFO *p_info);

#else

#define _P_OS_AUDIT  ((T_OS_AUDIT_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_audit))

#define os_audit_write              _P_OS_AUDIT->_p_os_audit_write
#define os_audit_read               _P_OS_AUDIT->_p_os_audit_read
#define os_audit_clear              _P_OS_AUDIT->_p_os_audit_clear
#define os_audit_write_ex           _P_OS_AUDIT->_p_os_audit_write_ex
#define os_audit_cfg_read           _P_OS_AUDIT->_p_os_audit_cfg_read
#define os_audit_cfg_write          _P_OS_AUDIT->_p_os_audit_cfg_write
// new interface as of SMOS 5.4.0.0
#define os_audit_open               _P_OS_AUDIT->_p_os_audit_open
#define os_audit_close              _P_OS_AUDIT->_p_os_audit_close
#define os_audit_entry              _P_OS_AUDIT->_p_os_audit_entry
#define os_audit_print              _P_OS_AUDIT->_p_os_audit_print
#define os_audit_manage             _P_OS_AUDIT->_p_os_audit_manage
// new as of SMOS 5.6.0.0
#define os_audit_read_file          _P_OS_AUDIT->_p_os_audit_read_file
// new as of SMOS 5.6.1.0
#define os_audit_clear_files        _P_OS_AUDIT->_p_os_audit_clear_files
// new as of SMOS 5.6.3.0
#define os_audit_info               _P_OS_AUDIT->_p_os_audit_info

#endif /* defined(_OS_C_INT_) || defined(_ALWAYS_C_INT_) */


/* --- BEGIN ERROR CODES --- */

#define E_OS_AUDIT                        0xB00007        // AUDIT section

#define E_OS_AUDIT_EXIST                  0xB0000700      // Audit file does not exist
#define E_OS_AUDIT_FULL                   0xB0000701      // Audit files full
#define E_OS_AUDIT_FSFULL                 0xB0000702      // File system full
#define E_OS_AUDIT_BUFF_TOO_SMALL         0xB0000703      // Buffer too small
#define E_OS_AUDIT_MALLOC                 0xB0000704      // Memory allocation failed
#define E_OS_AUDIT_CFG_ITEM               0xB0000705      // Invalid configuration item
#define E_OS_AUDIT_CFG_RANGE              0xB0000706      // Configuration value out of range
#define E_OS_AUDIT_PARAM                  0xB0000707      // Invalid parameter value
#define E_OS_AUDIT_INVALID_HANDLE         0xB0000708      // Invalid audit handle
#define E_OS_AUDIT_CFG_LOCKED             0xB0000709      // Audit configuration is locked
#define E_OS_AUDIT_ALREADY_EXIST          0xB000070A      // Audit file already exist

/* --- END ERROR CODES --- */



#endif /* __OS_AUDIT_H_PUB_INCLUDED__ */

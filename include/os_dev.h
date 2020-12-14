/**************************************************************************************************
 *
 *  Description : Device File System (obsolete)
 *
 *  Project     : SMOS
 *                Public header file
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco IS GmbH
 *
 **************************************************************************************************/
#ifndef __OS_DEV_H_PUB_INCLUDED__
#define __OS_DEV_H_PUB_INCLUDED__

/************************************************************************************************
 * mode flag definition and other constants
 ************************************************************************************************/
#define OS_DEV_READ                 1
#define OS_DEV_WRITE                2
#define OS_DEV_READ_WRITE           (OS_DEV_WRITE | OS_DEV_READ)

#define OS_DEV_HANDLE               int
#define OS_DEV_INVALID_HANDLE       -1

/************************************************************************************************
 * error codes set in global process variable errno or replied
 ************************************************************************************************/

/* --- BEGIN ERROR CODES --- */
#define E_OS_DEV                           0xB00002    // device section

#define E_OS_DEV_NO_DEVICE                 0xB000020B  // no serial device available
#define E_OS_DEV_NO_SUCH_FUNCTION          0xB000020A  // no private module function
#define E_OS_DEV_NO_MEM                    0xB0000209  // can't allocate memory space
#define E_OS_DEV_DATA_INVALID              0xB0000207  // corrupted data
#define E_OS_DEV_HDL_INVALID               0xB0000206  // session handle not allowed
#define E_OS_DEV_PARAMETER_INVALID         0xB0000205  // passed parameter illegal
#define E_OS_DEV_MODE_INVALID              0xB0000204  // illegal mode of operation
#define E_OS_DEV_NAME_INVALID              0xB0000203  // illegal device name length or characterset
#define E_OS_DEV_ALREADY_OPEN              0xB0000202  // device is used by an other session
#define E_OS_DEV_ERR                       0xB0000201  // notifies if an error occurs during operation

/* --- END ERROR CODES --- */


/*************************************************************************************************
 * Structure definitions
 *************************************************************************************************/
typedef struct _os_dev_public_interface
{
  void *dumy1;
  void *dumy2;
  OS_DEV_HANDLE  (*_p_os_dev_open ) (const char *, unsigned int);
  int            (*_p_os_dev_read ) (OS_DEV_HANDLE, void*, unsigned int);
  int            (*_p_os_dev_write) (OS_DEV_HANDLE, const void*, unsigned int);
  int            (*_p_os_dev_ioctl) (OS_DEV_HANDLE, void*);
  int            (*_p_os_dev_close) (OS_DEV_HANDLE);
}
T_OS_DEV_TABLE_PUB;

#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

/************************************************************************************************
 * function prototypes for input output handling
 ************************************************************************************************/
OS_DEV_HANDLE os_dev_open  (const char * p_dev_name,unsigned int flg_mode);
int           os_dev_read  (OS_DEV_HANDLE hdl,void* p_buf,unsigned int cnt);
int           os_dev_write (OS_DEV_HANDLE hdl,const void* p_buf,unsigned int cnt);
int           os_dev_ioctl (OS_DEV_HANDLE hdl,void* p_data);
int           os_dev_close (OS_DEV_HANDLE hdl);

#else
  /*** smos linking of the modules **************************************************************
   * This section is active when dynamic loading/linking of the modules using the Module Loader
   * is in effect.
   **********************************************************************************************/

/************************************************************************************************
 * macros to use the public interface and global data of key server module
 ************************************************************************************************/
#define _P_OS_DEV  ((T_OS_DEV_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_dev))

#define os_dev_open                  _P_OS_DEV->_p_os_dev_open
#define os_dev_read                  _P_OS_DEV->_p_os_dev_read
#define os_dev_write                 _P_OS_DEV->_p_os_dev_write
#define os_dev_ioctl                 _P_OS_DEV->_p_os_dev_ioctl
#define os_dev_close                 _P_OS_DEV->_p_os_dev_close

#endif /* defined(_OS_C_INT_) || defined(_ALWAYS_C_INT_) */

#endif

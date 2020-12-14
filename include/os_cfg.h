/**************************************************************************************************
 *
 *  Description : Configuration Parser
 *
 *  Project     : SMOS
 *                Public header file
 *
 *  Author(s)   : Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 **************************************************************************************************/
#ifndef __OS_CFG_PUB_INCLUDED__
#define __OS_CFG_PUB_INCLUDED__ 

/******************************************************************************
 *
 * Definitions
 *
 ******************************************************************************/
#define OS_CFG_HANDLE void*
 
#define OS_CFG_INVALID_HANDLE  NULL

#define OS_CFG_GLOBAL_SECT     NULL

#define OS_CFG_FIND_FIRST       0
#define OS_CFG_FIND_NEXT        1

/******************************************************************************
 *
 * public interface
 *
 ******************************************************************************/
typedef struct _os_cfg_public_interface 
{
  int (*_p_os_cfg_open)       (const char *filename, OS_CFG_HANDLE *p_hdl);
  int (*_p_os_cfg_close)      (OS_CFG_HANDLE hdl);
  int (*_p_os_cfg_get_value)  (OS_CFG_HANDLE hdl, const char *section, char const *key, unsigned char **pp_val, unsigned int *p_l_val);
  int (*_p_os_cfg_find)       (OS_CFG_HANDLE hdl, unsigned int flags, const char *section, unsigned char **pp_key, unsigned int *p_l_key, unsigned char **pp_val, unsigned int *p_l_val);
}
T_OS_CFG_TABLE_PUB;

#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)
  extern int os_cfg_open      (const char *filename, OS_CFG_HANDLE *p_hdl);
  extern int os_cfg_close     (OS_CFG_HANDLE hdl);  
  extern int os_cfg_get_value (OS_CFG_HANDLE hdl, const char *section, const char *key, unsigned char **pp_val, unsigned int *p_l_val);
  extern int os_cfg_find      (OS_CFG_HANDLE hdl, unsigned int flags, const char *section, unsigned char **pp_key, unsigned int *p_l_key, unsigned char **pp_val, unsigned int *p_l_val);  
  extern int os_cfg_get_int   (OS_CFG_HANDLE hdl, const char *section, const char *key, int def);
  
#else
  #define _P_OS_CFG   ((T_OS_CFG_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_cfg))
  
  #define os_cfg_open       _P_OS_CFG->_p_os_cfg_open
  #define os_cfg_close      _P_OS_CFG->_p_os_cfg_close
  #define os_cfg_get_value  _P_OS_CFG->_p_os_cfg_get_value
  #define os_cfg_find       _P_OS_CFG->_p_os_cfg_find
  
#endif

/* --- BEGIN ERROR CODES --- */
#define E_OS_CFG                          0xB0000B    // Config section
#define E_OS_CFG_MALLOC                   0xB0000B01  // memory allocation failed
#define E_OS_CFG_INVALID_PARAM            0xB0000B02  // invalid parameter
#define E_OS_CFG_INVALID_HDL              0xB0000B03  // invalid handle

#define E_OS_CFG_BAD                      0xB0000B04  // bad config file
#define E_OS_CFG_SECT_NOT_FOUND           0xB0000B05  // section not found
#define E_OS_CFG_ITEM_NOT_FOUND           0xB0000B06  // item not found


/* --- END ERROR CODES --- */

#endif

/**************************************************************************************************
 *
 *  Description : Functions related to firmware modules
 *                Public header file
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 **************************************************************************************************/
#ifndef __OS_MDL_H_PUB_INCLUDED__
#define __OS_MDL_H_PUB_INCLUDED__

#include "os.h"

/* Error Codes:  (0xB0000000 | (CMDS_MDL_ID << 16) | (errno))  */

/* --- BEGIN ERROR CODES --- */

#define E_OS_MDL                           0xB00008    // MDL section

#define E_OS_MDL_MEM_ALLOC                 0xB0000801  // Error during memory allocation
#define E_OS_MDL_PARA_INVALID              0xB0000802  // Invalid input parameter
#define E_OS_MDL_EXIST                     0xB0000803  // module already exists
#define E_OS_MDL_TABLE                     0xB0000804  // module table full
#define E_OS_MDL_PARAMETER                 0xB0000805  // illegall parameter passed
#define E_OS_MDL_EVENT                     0xB0000806  // event not reached
#define E_OS_MDL_NOT_FOUND                 0xB0000807  // module not found
#define E_OS_MDL_WRITE                     0xB0000808  // can't write module to SDRAM directory
#define E_OS_MDL_SLF_BAD                   0xB0000809  // bad signed licence file
#define E_OS_MDL_BL_INI                    0xB000080A  // can't read boot loader configuration file
#define E_OS_MDL_SLF_FOUND                 0xB000080B  // SLF parameter not found
#define E_OS_MDL_MTC_INV                   0xB000080C  // invalid MTC file
#define E_OS_MDL_MMC_INV                   0xB000080D  // invalid MMC file
#define E_OS_MDL_NO_MTC_SIG                0xB000080E  // No MTC signature present
#define E_OS_MDL_CFG_FOUND                 0xB000080F  // Config parameter not found
#define E_OS_MDL_HW_TYPE                   0xB0000810  // Module does not match hardware type
#define E_OS_MDL_MSC_INV                   0xB0000811  // invalid MSC file
#define E_OS_MDL_MSC_VERIFY_FAILED         0xB0000812  // MSC verification failed
#define E_OS_MDL_NOT_SUPP                  0xB0000813  // Function not supported
#define E_OS_MDL_NOT_AVAILABLE             0xB0000814  // Function not available
#define E_OS_MDL_CORRUPT                   0xB0000815  // corrupted module section

/* --- END ERROR CODES --- */


typedef int T_MDL_START_FCT
(
  T_OS_MDL_HDL     p_smos,
  int              dumy,
  void             *p_coff_mem
);

// other constants
#define OS_MDL_NAME_LEN             16          // size of the module name including the terminating 0 passed to os_mdl_link_new

// initialization levels
#define OS_MDL_INIT_NONE            0           // The init of the module has not started yet.
#define OS_MDL_INIT_INTERNAL        1           // The module has finished its internal initial.
#define OS_MDL_INIT_DEP_OK          2           // The module has successfully completed the check of dependencies on other modules.
#define OS_MDL_INIT_OK              3           // The initialization of the module is complete.
                                                //  Possible calls to services from other modules are done successfully.
#define OS_MDL_INIT_FAILED          4           // The initialization of the module failed. Services provided by this module are not available.
#define OS_MDL_INACTIVE             5           // Module is not installed. Functionality not available.
#define OS_MDL_SUSPENDED            6           // Module is suspended

// CPU types
#define OS_MDL_CPU_TYPE_C62         0x00        // module was compile for C6200 architecture
#define OS_MDL_CPU_TYPE_C64         0x01        // module was compile for C6400 architecture
#define OS_MDL_CPU_TYPE_C64PLUS     0x02        // module was compile for C64plus architecture
#define OS_MDL_CPU_TYPE_SIM_WIN     0x0A        // module was compile for Windows simulator
#define OS_MDL_CPU_TYPE_SIM_LINUX   0x0B        // module was compile for Linux simulator

// Module types
#define OS_MDL_MDL_TYPE_CS2_COFF    0x01
#define OS_MDL_MDL_TYPE_SIM_DLL     0x02
#define OS_MDL_MDL_TYPE_SIM_SO      0x03

// Hardware types
#define OS_MDL_HW_TYPE_CS2000       0x00
#define OS_MDL_HW_TYPE_CS2064       0x01
#define OS_MDL_HW_TYPE_CS2086       0x02
#define OS_MDL_HW_TYPE_CS2057       0x03
#define OS_MDL_HW_TYPE_CS5          0x05

// backward compatibility
#define  OS_MDL_CPU_TYPE_SDK        OS_MDL_CPU_TYPE_SIM_WIN
#define  OS_MDL_CPU_TYPE_SIM        OS_MDL_CPU_TYPE_SIM_LINUX


typedef struct _os_mdl_public_interface
{
  T_OS_MDL_HDL (*_p_os_mdl_link_pub)     (const char *p_name, const unsigned int version);
  int          (*_p_os_mdl_link_new)     (const char *p_mdl_name, const unsigned int mdl_version, const unsigned short mdl_id, void *p_coff_mem, void *p_global);
  void         (*_p_os_mdl_state_set)    (unsigned short module_id, const unsigned int state);
  int          (*_p_os_mdl_state_wait)   (const char *p_name, unsigned int state);
  int          (*_p_os_mdl_name_get)     (unsigned short module_id, char *p_mdl_name, unsigned int *p_mdl_version);
  void         (*_p_os_mdl_shutdown)     (void);
  int          (*_p_os_mdl_slf_param_get)(char *p_name, unsigned char **pp_value, unsigned int *p_len);
  int          (*_p_os_mdl_list)         (const unsigned int tab_id, char *p_mdl_name, unsigned int *p_mdl_version, unsigned short *p_mdl_id, unsigned int *p_mdl_state);
  int          (*_p_os_mdl_mdl_unpack)   (char *,void **,unsigned int *,unsigned int *); // obsolete
  void         (*_p_os_mdl_cpu_set)      (unsigned short module_id, const unsigned int cpu);
  int          (*_p_os_mdl_cpu_get)      (unsigned short module_id, unsigned int *p_cpu_type);
  int          (*_p_os_mdl_cfg_find)     (unsigned int  l_cfg, unsigned char *p_cfg, unsigned char *p_name, unsigned char **pp_value, unsigned int *p_len);
  int          (*_p_os_mdl_unpack)       (char *, unsigned char **, unsigned int *, unsigned char **, unsigned int *, unsigned char **, unsigned int *, unsigned int *); // obsolete
  // new as of SMOS 5.5.3.0
  int          (*_p_os_mdl_check)        (unsigned short module_id);
  int          (*_p_os_mdl_check_all)    (unsigned int flags);
}
T_OS_MDL_TABLE_PUB;

#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

  /*** C-style linking of the modules ***********************************************************
   * This section contains the C-style function prototypes. It is active when the modules are
   * linked together using the linker or a shared library (i.e., in the SDK). It is also used
   * for the module itself.
   **********************************************************************************************/
   T_OS_MDL_HDL os_mdl_link_pub      (const char *p_name, const unsigned int version);
   int          os_mdl_link_new      (const char *p_mdl_name, const unsigned int mdl_version, const unsigned short mdl_id, void *p_coff_mem, void *p_global);
   void         os_mdl_state_set     (unsigned short module_id, const unsigned int state);
   int          os_mdl_state_wait    (const char *p_name, unsigned int state);
   int          os_mdl_name_get      (unsigned short module_id, char *p_mdl_name, unsigned int *p_mdl_version);
   void         os_mdl_shutdown      (void);
   int          os_mdl_slf_param_get (char *p_name, unsigned char **pp_value, unsigned int *p_len);
   int          os_mdl_list          (const unsigned int tab_id, char *p_mdl_name, unsigned int *p_mdl_version, unsigned short *p_mdl_id, unsigned int *p_mdl_state);
   void         os_mdl_cpu_set       (unsigned short module_id, const unsigned int cpu);
   int          os_mdl_cpu_get       (unsigned short module_id, unsigned int *p_cpu_type);
   int          os_mdl_cfg_find      (unsigned int l_cfg, unsigned char *p_cfg, unsigned char *p_name, unsigned char **pp_value, unsigned int *p_len);
   // new as of SMOS 5.5.3.0
   int          os_mdl_check         (unsigned short module_id);
   int          os_mdl_check_all     (unsigned int flags);

   // obsolete as of SMOS3
   int          os_mdl_mdl_unpack    (char *, void **, unsigned int *, unsigned int *);
   int          os_mdl_unpack        (char *, unsigned char **, unsigned int *, unsigned char **, unsigned int *, unsigned char **, unsigned int *, unsigned int *);

#else
  /*** smos linking of the modules **************************************************************
   * This section is active when dynamic loading/linking of the modules using the Module Loader
   * is in effect.
   **********************************************************************************************/

  /************************************************************************************************
   * macros to use the public interface and global data of key server module
   ************************************************************************************************/
  #define _P_OS_MDL  ((T_OS_MDL_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_mdl))

  #define os_mdl_link_pub        _P_OS_MDL->_p_os_mdl_link_pub
  #define os_mdl_link_new        _P_OS_MDL->_p_os_mdl_link_new
  #define os_mdl_state_set       _P_OS_MDL->_p_os_mdl_state_set
  #define os_mdl_state_wait      _P_OS_MDL->_p_os_mdl_state_wait
  #define os_mdl_name_get        _P_OS_MDL->_p_os_mdl_name_get
  #define os_mdl_shutdown        _P_OS_MDL->_p_os_mdl_shutdown
  #define os_mdl_list            _P_OS_MDL->_p_os_mdl_list
  #define os_mdl_slf_param_get   _P_OS_MDL->_p_os_mdl_slf_param_get
  #define os_mdl_cpu_set         _P_OS_MDL->_p_os_mdl_cpu_set
  #define os_mdl_cpu_get         _P_OS_MDL->_p_os_mdl_cpu_get
  #define os_mdl_cfg_find        _P_OS_MDL->_p_os_mdl_cfg_find
  // new as of SMOS 5.5.3.0
  #define os_mdl_check           _P_OS_MDL->_p_os_mdl_check
  #define os_mdl_check_all       _P_OS_MDL->_p_os_mdl_check_all

  // obsolete as of SMOS3
  #define os_mdl_mdl_unpack      _P_OS_MDL->_p_os_mdl_mdl_unpack
  #define os_mdl_unpack          _P_OS_MDL->_p_os_mdl_unpack

#endif /* defined(_OS_C_INT_) || defined(_ALWAYS_C_INT_) */

#endif

/**************************************************************************************************
 *
 *  Description : File System
 *
 *  Project     : SMOS
 *                Public header file
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 **************************************************************************************************/
#ifndef __OS_FILE_H_PUB_INCLUDED__
#define __OS_FILE_H_PUB_INCLUDED__

#include "stype.h"

/************************************************************************************************
 * constants for file handling with names and handles
 ************************************************************************************************/
#define  OS_FILE_HANDLE         int             // handle to open file
#define  OS_FILE_INVALID_HANDLE (-1)            // illegal handle
#define  OS_FILE_PATH_LB_MAX    32              // max. file and path name length

// file name length
#define  OS_FILE_NAME_LB_MAX    (OS_FILE_PATH_LB_MAX / 2)

/************************************************************************************************
 * flags indicating the existence and the access mode of a file (obsolete)
 ************************************************************************************************/
#define  OS_FILE_EXIST              0
#define  OS_FILE_EXIST_WRITE        0
#define  OS_FILE_EXIST_READ         0
#define  OS_FILE_EXIST_RDWR         0

/************************************************************************************************
 * modes for file opening
 ************************************************************************************************/
#define  OS_FILE_O_RD_ONLY          0x0000      // file read only
#define  OS_FILE_O_WR_ONLY          0x0001      // file write only
#define  OS_FILE_O_RDWR             0x0002      // file read and write operations allowed
#define  OS_FILE_O_NOP              0x0003      // no read / write operations allowed
#define  OS_FILE_O_APPEND           0x0008      // set the file pointer to the end of the file
#define  OS_FILE_O_CREATE           0x0100      // Creates and opens a new file
#define  OS_FILE_O_CCREATE          0x0200      // Creates file, if not exists
  
#define  OS_FILE_O_WRITE_PROTECT    0x010000    // File cannot be deleted / modified
#define  OS_FILE_O_NODEL_ON_CLEAR   0x020000    // Don't delete file on CryptoServer Clear
#define  OS_FILE_O_NODEL_ON_ALARM   0x040000    // Don't delete file on ALARM
#define  OS_FILE_O_SYSTEM           0x080000    // system file

#define  OS_FILE_O_TEXT             0           // obsolete
#define  OS_FILE_O_BINARY           0           // obsolete

/**********************************************************************************************
 * device names
 **********************************************************************************************/
#define  OS_FILE_FLASH              "FLASH\\"   // the public directory
#define  OS_FILE_SYS                "SYS\\"     // the system directory path
#define  OS_FILE_NVRAM              "NVRAM\\"   // the directory of NVRAM storage location


/************************************************************************************************
 * file information structure for file find operations
 ************************************************************************************************/
typedef struct
{
  unsigned int  flg_attrib;                     // attributes
  unsigned int  time_create;                    // unused
  unsigned int  size;                           // size of the file
  char          name[OS_FILE_NAME_LB_MAX];      // file name without path information
}
T_OS_FILE_INFO;


/************************************************************************************************
 * information structures to be used with os_file_info
 ************************************************************************************************/

// disk geometry information structure
typedef struct
{
  unsigned int  size;                           // sizeof(T_OS_FILE_GEOM_INFO)
  unsigned int  npages;                         // total number of pages in device
  unsigned int  ppb;                            // pages per block
  unsigned int  fs_start;                       // number of first page of filesystem
  unsigned int  fs_npages;                      // number of pages in filesystem
}
T_OS_FILE_GEOM_INFO;

// memory information information structure
typedef struct
{  
  unsigned int  max_size;                       // the total memory size
  unsigned int  used_size;                      // the used memory size
  unsigned int  free_size;                      // the free memory size
  unsigned int  available_size;                 // the available memory size after optimization
}
T_OS_FILE_MEM_INFO;

// file allocation table information structure
typedef struct
{
  unsigned int  size;                           // sizeof(T_OS_FILE_FAT_INFO)
  unsigned int  npages;                         // number of pages
  unsigned char *pages;                         // FAT list (one char per page)
}
T_OS_FILE_FAT_INFO;

// file statistics information structure
typedef struct
{
  unsigned int size;                            // sizeof(T_OS_FILE_STATS)
  unsigned int nread;                           // number of pages read
  unsigned int nread_sp;                        // number of spare pages read
  unsigned int nwrite;                          // number of pages written
  unsigned int nupdate;                         // number of pages updated
  unsigned int nformat;                         // number of pages formated
        
  struct ecc_stats_t        
  {       
    unsigned int nuncorr;                       // number uncorrectable ecc errors
    unsigned int ndata;                         // number corrected data bits
    unsigned int necc;                          // number corrected ecc bits
  }       
  ecc[2];                                       // 0: SPARE 1: PAGE
        
  struct bb_stats_t       
  {       
    unsigned int nbad[2];                       // number of bad blocks [total/new]
  }
  bb;
}
T_OS_FILE_STATS;

// modes for os_file_info
#define OS_FILE_GEOM_INFO 0
#define OS_FILE_MEM_INFO  1
#define OS_FILE_FAT_INFO  2
#define OS_FILE_STATS     3


/************************************************************************************************
 * information structure to be used with os_file_scan
 ************************************************************************************************/
typedef struct
{
  unsigned int  size;                           // sizeof(T_OS_FILE_SCAN_INFO)
  unsigned int  nfiles;                         // number of files in file table

  struct files_t
  {
    unsigned int   inode;
    char           name[OS_FILE_NAME_LB_MAX];   // file name without path information
    unsigned short state;                       // state of file descriptor page
    unsigned short npages;                      // number of data pages belonging to this file
    unsigned short ncorrupt;                    // number of corrupted data pages
    unsigned char  rfu[2];
  }
  *files;                                       // file table (memory allocation)
}
T_OS_FILE_SCAN_INFO;

#define OF_FILE_STATE_ECC_SPARE   1             // ECC error on spare page
#define OF_FILE_STATE_ECC_PAGE    2             // ECC error on page data

/************************************************************************************************
 * error codes
 ************************************************************************************************/

/* --- BEGIN ERROR CODES --- */

#define E_OS_FILE                          0xB00005    // file section

#define E_OS_FILE_INIT                     0xB0000501  // file system not initialized
#define E_OS_FILE_ALREADY_OPEN             0xB0000502  // the file is already opened
#define E_OS_FILE_ILL_NAME                 0xB0000503  // file name is not allowed
#define E_OS_FILE_ILL_ATTRIB               0xB0000504  // invalid open mode
#define E_OS_FILE_NO_SUCH_PATH             0xB0000505  // the directory does not exist
#define E_OS_FILE_NO_SUCH_FILE             0xB0000506  // the file does not exist
#define E_OS_FILE_EXIST                    0xB0000507  // the file doesn't / already exists
#define E_OS_FILE_ILL_PARAM                0xB0000508  // invalid parameter
#define E_OS_FILE_NOT_OPEN                 0xB000050A  // the file isn't open for access mode
#define E_OS_FILE_ILL_POS                  0xB000050B  // position offset not allowed
#define E_OS_FILE_NO_MEM                   0xB000050C  // no more memory space available
#define E_OS_FILE_NO_TABLE                 0xB000050D  // no bad block table
#define E_OS_FILE_MAGIC                    0xB000050E  // invalid magic tag
#define E_OS_FILE_FF_BUSY                  0xB0000510  // flash file device is still busy
#define E_OS_FILE_FF_FAILED                0xB0000511  // flash file device replies an error
#define E_OS_FILE_FF_ADDRESS               0xB0000513  // illegal page address
#define E_OS_FILE_ECC                      0xB0000514  // page parity error
#define E_OS_FILE_RDONLY                   0xB0000515  // file system is read only
#define E_OS_FILE_HANDLE                   0xB0000516  // bad file handle
#define E_OS_FILE_NO_SPACE                 0xB0000517  // file system full
#define E_OS_FILE_TABLE_FULL               0xB0000518  // file table full
#define E_OS_FILE_CORR                     0xB0000519  // file corrupted
#define E_OS_FILE_EXDEV                    0xB000051A  // different file systems
#define E_OS_FILE_BAD_FSTYPE               0xB000051B  // bad file system type, can't mount
#define E_OS_FILE_BAD_BAD                  0xB000051C  // too many bad blocks, giving up
#define E_OS_FILE_FF_BAD                   0xB000051D  // detected bad block in flash file
#define E_OS_FILE_GEOMETRY                 0xB000051E  // bad flash page geometry
#define E_OS_FILE_HDL_TOOMANY              0xB000051F  // too many open file handles

/* --- END ERROR CODES --- */

// old definitions for compatibility:
#define E_FILE_NO_TABLE                    E_OS_FILE_NO_TABLE
#define E_FILE_NO_MEM                      E_OS_FILE_NO_MEM
#define E_FILE_ILL_POS                     E_OS_FILE_ILL_POS
#define E_FILE_NOT_OPEN                    E_OS_FILE_NOT_OPEN
#define E_FILE_EXIST                       E_OS_FILE_EXIST
#define E_FILE_NO_SUCH_FILE                E_OS_FILE_NO_SUCH_FILE
#define E_FILE_NO_SUCH_PATH                E_OS_FILE_NO_SUCH_PATH
#define E_FILE_ILL_ATTRIB                  E_OS_FILE_ILL_ATTRIB
#define E_FILE_ILL_NAME                    E_OS_FILE_ILL_NAME
#define E_FILE_ALREADY_OPEN                E_OS_FILE_ALREADY_OPEN


/*************************************************************************************************
 * Public interface
 *************************************************************************************************/
typedef struct _os_file_public_interface
{
  void            *dumy;
  OS_FILE_HANDLE (*_p_os_file_open       ) (const char*, unsigned int);
  int            (*_p_os_file_read       ) (OS_FILE_HANDLE, void*, unsigned int);
  int            (*_p_os_file_write      ) (OS_FILE_HANDLE, const void*, unsigned int);
  int            (*_p_os_file_close      ) (OS_FILE_HANDLE);
  int            (*_p_os_file_pos        ) (OS_FILE_HANDLE, unsigned int);
  int            (*_p_os_file_pos_relativ) (OS_FILE_HANDLE, int);
  int            (*_p_os_file_length     ) (OS_FILE_HANDLE);
  int            (*_p_os_file_rename     ) (const char*, char*);
  OS_FILE_HANDLE (*_p_os_file_find_first ) (const char*, T_OS_FILE_INFO*);
  int            (*_p_os_file_find_next  ) (OS_FILE_HANDLE, T_OS_FILE_INFO*);
  void           (*_p_os_file_find_close ) (OS_FILE_HANDLE);
  int            (*_p_os_file_access     ) (const char*, unsigned int);
  int            (*_p_os_file_unlink     ) (const char*);
  int            (*_p_os_file_flush      ) (OS_FILE_HANDLE);
  int            (*_p_os_file_mem_info   ) (T_OS_FILE_MEM_INFO* ,const char*);
  int            (*_p_os_file_hash_bl    ) (int rfu,unsigned char *hash);
  // new as of SMOS 4.2.0.0
  int            (*_p_os_file_info       ) (const char *path, int mode, void *p_info);
  int            (*_p_os_file_scan       ) (const char *path, T_OS_FILE_SCAN_INFO *p_info);
}
T_OS_FILE_TABLE_PUB;

#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

// function prototypes used by SMOS (internal)
int            os_file_init          (void);
void           os_file_log_errors    (void);
OS_FILE_HANDLE os_file_open          (const char *p_filename, unsigned int oflags);
int            os_file_read          (OS_FILE_HANDLE hdl, void *p_buf, unsigned int cnt);
int            os_file_write         (OS_FILE_HANDLE hdl, const void *p_buf, unsigned int cnt);
int            os_file_close         (OS_FILE_HANDLE hdl);
int            os_file_pos           (OS_FILE_HANDLE hdl,unsigned int cnt);
int            os_file_pos_relativ   (OS_FILE_HANDLE hdl,int cnt);
int            os_file_length        (OS_FILE_HANDLE hdl);
int            os_file_flush         (OS_FILE_HANDLE hdl);
int            os_file_rename        (const char *p_oldfilename, char *p_newfilename);
OS_FILE_HANDLE os_file_find_first    (const char *p_file_spec, T_OS_FILE_INFO *p_file_info);
int            os_file_find_next     (OS_FILE_HANDLE  hdl,T_OS_FILE_INFO* p_file_info);
void           os_file_find_close    (OS_FILE_HANDLE hdl);
int            os_file_access        (const char* p_file_spec,unsigned int mode);
int            os_file_unlink        (const char* p_filename);
int            os_file_mem_info      (T_OS_FILE_MEM_INFO* p_info, const char *p_locate);
void           os_file_close_all     (void);
int            os_file_hash_bl       (int rfu, unsigned char *hash);
// new as of SMOS 4.2.0.0
int            os_file_info          (const char *path, int mode, void *p_info);
int            os_file_scan          (const char *path, T_OS_FILE_SCAN_INFO *p_info);

#else

/************************************************************************************************
 * macros to use the public interface and global data of key server module
 ************************************************************************************************/
#define _P_OS_FILE  ((T_OS_FILE_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_file))

#define os_file_open         _P_OS_FILE->_p_os_file_open
#define os_file_read         _P_OS_FILE->_p_os_file_read
#define os_file_write        _P_OS_FILE->_p_os_file_write
#define os_file_close        _P_OS_FILE->_p_os_file_close
#define os_file_pos          _P_OS_FILE->_p_os_file_pos
#define os_file_pos_relativ  _P_OS_FILE->_p_os_file_pos_relativ
#define os_file_length       _P_OS_FILE->_p_os_file_length
#define os_file_flush        _P_OS_FILE->_p_os_file_flush
#define os_file_rename       _P_OS_FILE->_p_os_file_rename
#define os_file_find_first   _P_OS_FILE->_p_os_file_find_first
#define os_file_find_next    _P_OS_FILE->_p_os_file_find_next
#define os_file_find_close   _P_OS_FILE->_p_os_file_find_close
#define os_file_access       _P_OS_FILE->_p_os_file_access
#define os_file_unlink       _P_OS_FILE->_p_os_file_unlink
#define os_file_mem_info     _P_OS_FILE->_p_os_file_mem_info
#define os_file_hash_bl      _P_OS_FILE->_p_os_file_hash_bl
// new as of SMOS 4.2.0.0
#define os_file_info         _P_OS_FILE->_p_os_file_info
#define os_file_scan         _P_OS_FILE->_p_os_file_scan

#endif // defined(_OS_C_INT_) || defined(_ALWAYS_C_INT_)


#endif  // __OS_FILE_H_PUB_INCLUDED__

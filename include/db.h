/*****************************************************************************
 *
 *  $File Identification                    $
 *  $Filename          : db.h               $
 *  $Module version    : x.x.x.x            $
 *  $Module name       : DB                 $
 *  $Release Date      : DD.MM.YYYY         $
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Utimaco AG
 *
 *  Description : Global header file of CryptoServer module DB
 *                Must be included in every CryptoServer software that uses
 *                functions of this module
 *
 *****************************************************************************/
#ifndef __DB_H_PUB_INCLUDED__
#define __DB_H_PUB_INCLUDED__


#include <os_mdl.h>


/* module identification: */

#define DB_MDL_ID          0x88                       /* ID of the module           */
#define DB_MDL_NAME        "DB"                       /* Name of the module         */
#ifdef CS2_SDK
# define DB_MDL_NAMEX      "Database module (SDK)"    /* Long name of the module    */
# else
#   ifdef DEBUG
#     define DB_MDL_NAMEX  "Database module (DEBUG)"  /* Long name of the module    */
#   else
#     define DB_MDL_NAMEX  "Database module"          /* Long name of the module    */
# endif
#endif
#define DB_MDL_VERSION     0x01030205                 /* Version of the module      */

typedef struct db DB;

// modes for db_find():
#define DB_EQUAL          0
#define DB_GTEQ           1
#define DB_GREATER        2

#define DB_LOCK           0x10

#define DB_ONLY_VOLATILE  0x20
#define DB_ONLY_PERMANENT 0x40


// modes for db_open():
#define DB_RDONLY         0
#define DB_RDWR           1
#define DB_CREAT          2

#define DB_NO_SECRET      0x10


// Header lengths for a db_open() call with DB_CREAT set 
#define DB_FILE_HEADER_LB  20                    /* Length in Bytes of the database file header   */
#define DB_REC_HEADER_LB    8                    /* Length in Bytes of a record header            */

typedef struct
{
    unsigned int tag;
    int keylen;
    int maxsize;
} 
DB_INFO;

#define DB_INFO_TAG     (0x8a5b3c00 + sizeof(DB_INFO))

// modes for db_release():
#define DB_UNLOCK       0
#define DB_FREE         1

// flags for db_insert2():
#define DB_PERMANENT    0
#define DB_VOLATILE     1

// info structure for db_mem_info
typedef struct
{
    unsigned int used;   
    unsigned int free;
} 
DB_MEM_INFO;

/* public interface: */
typedef struct
{
    void   *p_data;
    int    (*p_start)(T_OS_MDL_HDL, void *, void *);
    int    (*p_stop)(void);
    int    (*p_pre_replace)(void);
    int    (*p_pre_delete)(void);
    void   *p_dumy;
    const void *p_module_info;
    int    (*p_open)(const char *,int,const DB_INFO *,DB **);
    int    (*p_close)(DB *);
    int    (*p_drop)(const char *);
    int    (*p_find)(DB *,int,void *,unsigned int *,void **,unsigned int *,void **);
    int    (*p_insert)(DB *,const void *,unsigned int,const void *,unsigned int,const void *);
    int    (*p_update)(DB *,const void *,unsigned int,const void *,unsigned int,const void *);
    int    (*p_delete)(DB *,const void *);
    int    (*p_release)(DB *,const void *,int);
    int    (*p_insert2)(DB *,int,const void *,unsigned int,const void *,unsigned int,const void *);
    int    (*p_suspend)(DB *,int);
    int    (*p_mem_info)(DB *,DB_MEM_INFO *);
    int    (*p_get_info)(DB *,DB_INFO *);
    int    (*p_open_ex)(const char *, int, const DB_INFO *, DB **, void *, void *);
} T_DB_TABLE_PUB;

#ifdef _DB_C_INT_

/* function prototypes used by the module (internal) */
int db_start(T_OS_MDL_HDL,void *,void *);
int db_stop(void);
int db_pre_replace(void);
int db_pre_delete(void);
int db_open(const char *,int,const DB_INFO *p_info,DB **);
int db_open_ex(const char *,int,const DB_INFO *p_info,DB **, void *, void *); // do not use
int db_close(DB *);
int db_drop(const char *);
int db_find(DB *,int,void *,unsigned int *,void **,unsigned int *,void **);
int db_insert(DB *,const void *,unsigned int,const void *,unsigned int,const void *);
int db_update(DB *,const void *,unsigned int,const void *,unsigned int,const void *);
int db_delete(DB *,const void *);
int db_release(DB *,const void *,int);
int db_insert2(DB *,int,const void *,unsigned int,const void *,unsigned int,const void *);
int db_suspend(DB *,int);
int db_mem_info(DB *,DB_MEM_INFO *);
int db_get_info(DB *, DB_INFO *);

#else

/* external interface to be used by other modules */
extern MDL_GLOBAL T_OS_MDL_HDL P_DB;

#define _P_DB  ((T_DB_TABLE_PUB *)P_DB)         /* shortcut */

#define P_db_data         (_P_DB->_p_data);

#define db_start          _P_DB->p_start
#define db_stop           _P_DB->p_stop
#define db_pre_replace    _P_DB->p_pre_replace
#define db_pre_delete     _P_DB->p_pre_delete

#define db_open           _P_DB->p_open
#define db_open_ex        _P_DB->p_open_ex
#define db_close          _P_DB->p_close
#define db_drop           _P_DB->p_drop
#define db_find           _P_DB->p_find
#define db_insert         _P_DB->p_insert
#define db_update         _P_DB->p_update
#define db_delete         _P_DB->p_delete
#define db_release        _P_DB->p_release
#define db_insert2        _P_DB->p_insert2
#define db_suspend        _P_DB->p_suspend
#define db_mem_info       _P_DB->p_mem_info
#define db_get_info       _P_DB->p_get_info

#endif /* _DB_C_INT_ */


/* Error Codes:  (0xB0000000 | (DB_MDL_ID << 16) | (errno))  */

/* --- BEGIN ERROR CODES --- */

#define E_DB                0xB088          // CryptoServer Database Module  
#define E_DB_NO_MEM         0xB0880001      // memory allocation failed
#define E_DB_BAD_MKEY       0xB0880002      // bad master encryption key 
#define E_DB_NO_SPACE       0xB0880003      // no space in database
#define E_DB_NOT_FOUND      0xB0880004      // record not found
#define E_DB_EXISTS         0xB0880005      // record already exists
#define E_DB_NO_CACHE       0xB0880006      // no space in cache
#define E_DB_COR_FILE       0xB0880007      // corrupted database file
#define E_DB_REC_CRC        0xB0880008      // record CRC error
#define E_DB_BAD_NAME       0xB0880009      // bad database name
#define E_DB_BAD_HANDLE     0xB088000A      // bad database handle
#define E_DB_FILE_TYPE      0xB088000B      // bad file type of database file
#define E_DB_BAD_INFO       0xB088000D      // bad info structure
#define E_DB_IN_USE         0xB088000E      // database in use
#define E_DB_LENGTH         0xB088000F      // bad data length
#define E_DB_HDL_CONF       0xB0880011      // database handle confused
#define E_DB_INCONS         0xB0880012      // internal inconsistency    
#define E_DB_SMOSVER        0xB0880013      // SMOS version is too old
#define E_DB_BAD_PARAM      0xB0880014      // Bad parameter (e.g. NULL pointer)

#define E_DB_DATALEN        0xB0881000      // bad length of command block
#define E_DB_FILE_ERR       0xB0881001      // io error on database file   
#define E_DB_NOT_OPEN       0xB0881002      // test database not open      
#define E_DB_CORR_HDL       0xB0881003      // db handle corrupted    
#define E_DB_CORR_NODE      0xB0881004      // db node corrupted    
#define E_DB_CORR_CACHE     0xB0881005      // db cache corrupted    


/* --- END ERROR CODES --- */


#endif /* __DB_H_PUB_INCLUDED__ */

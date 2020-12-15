/**************************************************************************************************
 *
 * $File Identification                    $
 * $Filename          : util.h             $
 * $Module version    : x.x.x.x            $
 * $Module name       : UTIL               $
 * $Release Date      : DD.MM.YYYY         $
 *
 * Author             : Dipl. Ing. Sven Kaltschmidt
 *                      Utimaco IS GmbH
 *
 * Description        : Global header file of CryptoServer module UTIL
 *
 *
 **************************************************************************************************/
#ifndef _UTIL_H_PUB_INCLUDED__
#define _UTIL_H_PUB_INCLUDED__

#include "os_mdl.h"


//-----------------------------------------------------------------------------
// Error Codes:  (0xB0000000 | (UTIL_MDL_ID << 16) | (errno))
//-----------------------------------------------------------------------------

// --- BEGIN ERROR CODES ---
#define E_UTIL                          0xB086          // CryptoServer module UTIL
#define E_UTIL_RTC_OPEN                 0xB0860001      // Error opening RTC Device
#define E_UTIL_RTC_IOCTL                0xB0860002      // RTC: IOCTL Error
#define E_UTIL_RTC_READ                 0xB0860003      // RTC: Read Error
#define E_UTIL_RTC_WRITE                0xB0860004      // RTC: Write Error
#define E_UTIL_RTC_CLOSE                0xB0860005      // Error closing RTC Device

#define E_UTIL_TIME_WRONG_FORMAT        0xB0860006      // Wrong Time Format
#define E_UTIL_TIME_NULL_POINTER        0xB0860007      // Null Pointer given

#define E_UTIL_FILE_OPEN                0xB0860008      // File Open Error
#define E_UTIL_FILE_READ                0xB0860009      // File Read Error
#define E_UTIL_FILE_CLOSE               0xB086000A      // File Close Error

#define E_UTIL_RND_NULL_POINTER         0xB086000B      // Null Pointer given
#define E_UTIL_RND_FAILED               0xB086000C      // Random Number Generator failed

#define E_UTIL_MALLOC                   0xB086000D      // Error allocating Memory
#define E_UTIL_INVAL                    0xB086000E      // invalid argument
#define E_UTIL_NOT_SUPPORTED            0xB086000F      // function not supported

#define E_UTIL_RND_KAT                  0xB0860010      // Known answer test failed
#define E_UTIL_RND_INIT                 0xB0860011      // Random Number Generator is not initialized
#define E_UTIL_RND_PARAMETER            0xB0860012      // Bad Parameter
#define E_UTIL_RND_SEC_STRENGTH         0xB0860013      // Given security strength not supported
#define E_UTIL_RND_REQ                  0xB0860014      // Max number of requested randombits per call exceeded
#define E_UTIL_RND_PRED_RESISTANCE      0xB0860015      // prediction resistance not supported for current handle

#define E_UTIL_TIME_RTC_POWER_FAILED    0xB0860020      // RTC has lost power
#define E_UTIL_TIME_NOT_INIT            0xB0860021      // RTC is not initialized (RTC has to be set)

#define E_UTIL_LINK_SMOS                0xB086FC00      // SMOS Version does not match
// --- END ERROR CODES ---


//-----------------------------------------------------------------------------
// RTC
//-----------------------------------------------------------------------------
typedef struct
{
    int  year;         // 0 .. 99
    int  month;        // 1 .. 12
    int  day;          // 1 .. 31
    int  hour;         // 0 .. 23
    int  minute;       // 0 .. 59
    int  second;       // 0 .. 59
    int  fraction;     // 0 .. TIME_RESOLUTION-1
}
TIME_STR;

#define TIME_ASC_CENTURY  0x80 // mode parameter

//-----------------------------------------------------------------------------
// Hardware Identifikation
//-----------------------------------------------------------------------------
typedef struct
{
  struct                                                  // 16 Bytes used by the hardware
  {
    unsigned int hw_ver;                                  // Version of the Hardware
    struct
    {
      unsigned char crc;
      unsigned char serial[6];
      unsigned char family;
    }            uid;                                     // UID of the chip
    unsigned int bl_ver;                                  // Version of the Boot-Loader
  }
  dev;

  struct{ unsigned char b [16];} adm1;                    // 16 Bytes stored during production key loading
  struct{ unsigned char b [16];} adm2;                    // 16 Bytes stored during initialization key loading
  struct{ unsigned char b [16];} adm3;                    // 16 Bytes stored during initialization key change
}
T_UTIL_EID;


//-----------------------------------------------------------------------------
// module identification:
//-----------------------------------------------------------------------------
#define UTIL_MDL_ID          0x86                        // ID of the module
#define UTIL_MDL_NAME        "UTIL"                      // Abbreviation of the module
#ifdef CS2_SDK
    #define UTIL_MDL_NAMEX   "Utility Module SDK"        // Long name of the module
#else
  #ifdef DEBUG
    #define UTIL_MDL_NAMEX   "Utility Module DEBUG"      // Long name of the module
  #else
    #define UTIL_MDL_NAMEX   "Utility Module"            // Long name of the module
  #endif
#endif
#define UTIL_MDL_VERSION     0x03000600                  // Version of the module

//-----------------------------------------------------------------------------
// public interface:
//-----------------------------------------------------------------------------
typedef struct
{
  void   *p_data;
  int    (*p_start)(T_OS_MDL_HDL, void *, void*);
  int    (*p_stop)(void);
  int    (*p_pre_replace)(void);
  int    (*p_pre_delete)(void);
  void   *p_dumy;
  const void *p_module_info;
  // time
  int    (*p_get_time)(unsigned int*, unsigned int*);
  int    (*p_set_time)(unsigned int);
  int    (*p_time_to_str)(unsigned int, unsigned int, TIME_STR*);
  int    (*p_str_to_time)(TIME_STR*, unsigned int*, unsigned int*);
  int    (*p_str_to_asc)(TIME_STR*, int, char*);
  int    (*p_asc_to_str)(int, char*, TIME_STR*);
  int    (*p_get_str_time)(TIME_STR*);
  int    (*p_set_str_time)(TIME_STR*);
  // random
  int    (*p_init_pseudo_rnd)(void);
  int    (*p_pseudo_rnd)(unsigned char*, unsigned int);
  int    (*p_get_real_rnd)(unsigned char*, unsigned int);
  // Util EID
  T_UTIL_EID *p_util_eid;
  // time ex
  int    (*p_set_time_ex)(unsigned int, unsigned int);
  int    (*p_get_time_cal)(int *);
  int    (*p_set_time_cal)(int);
  //
  int    (*p_util_mem_cmp_ti)(const void*, const void*, unsigned int);
}
T_UTIL_TABLE_PUB;


#ifdef _UTIL_C_INT_
  //-----------------------------------------------------------------------------
  // function prototypes used by the module (internal)
  //-----------------------------------------------------------------------------
  int  util_start(T_OS_MDL_HDL,void *,void *);
  int  util_stop(void);
  int  util_pre_replace(void);
  int  util_pre_delete(void);
  // time
  int  util_get_time(unsigned int *p_sec, unsigned int *p_msec);
  int  util_set_time(unsigned int sec);
  int  util_time_to_str(unsigned int sec, unsigned int msec, TIME_STR *p_ts);
  int  util_str_to_time(TIME_STR *p_ts, unsigned int *p_sec, unsigned int *p_msec);
  int  util_str_to_asc(TIME_STR *p_ts, int mode, char *p_atime);
  int  util_asc_to_str(int len, char *p_atime, TIME_STR *p_ts);
  int  util_get_str_time(TIME_STR *p_ts);
  int  util_set_str_time(TIME_STR *p_ts);
  // random
  int  util_init_pseudo_rnd(void);
  int  util_get_pseudo_rnd(unsigned char *p_rnd, unsigned int len);
  int  util_get_real_rnd(unsigned char *p_rnd, unsigned int len);
  // time ex
  int  util_set_time_ex(unsigned int sec, unsigned int msec);
  int  util_get_time_cal(int *cal);
  int  util_set_time_cal(int cal);
  //
  int util_mem_cmp_ti(const void *pa, const void *pb, unsigned int len);
#else
  //-----------------------------------------------------------------------------
  // external interface to be used by other modules
  //-----------------------------------------------------------------------------
  extern MDL_GLOBAL T_OS_MDL_HDL P_UTIL;

  #define _P_UTIL  ((T_UTIL_TABLE_PUB *)P_UTIL)         // shortcut

  #define P_util_data           (_P_UTIL->_p_data);

  #define util_start            _P_UTIL->p_start
  #define util_stop             _P_UTIL->p_stop
  #define util_pre_replace      _P_UTIL->p_pre_replace
  #define util_pre_delete       _P_UTIL->p_pre_delete
  // time
  #define util_get_time         _P_UTIL->p_get_time
  #define util_set_time         _P_UTIL->p_set_time
  #define util_time_to_str      _P_UTIL->p_time_to_str
  #define util_str_to_time      _P_UTIL->p_str_to_time
  #define util_str_to_asc       _P_UTIL->p_str_to_asc
  #define util_asc_to_str       _P_UTIL->p_asc_to_str
  #define util_get_str_time     _P_UTIL->p_get_str_time
  #define util_set_str_time     _P_UTIL->p_set_str_time

  // random
  #define util_init_pseudo_rnd  _P_UTIL->p_init_pseudo_rnd
  #define util_get_pseudo_rnd   _P_UTIL->p_pseudo_rnd
  #define util_get_real_rnd     _P_UTIL->p_get_real_rnd

  #define P_util_eid            _P_UTIL->p_util_eid

  // time ex
  #define util_set_time_ex      _P_UTIL->p_set_time_ex

  #define util_get_time_cal     _P_UTIL->p_get_time_cal
  #define util_set_time_cal     _P_UTIL->p_set_time_cal

  //
  #define util_mem_cmp_ti       _P_UTIL->p_util_mem_cmp_ti

#endif // _UTIL_C_INT_



#endif // _UTIL_H_PUB_INCLUDED__

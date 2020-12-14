/**************************************************************************************************
 *
 *  Description : Real Time Clock
 *                Public header file
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 **************************************************************************************************/
#ifndef __OS_RTC_PUB_INCLUDED__
#define __OS_RTC_PUB_INCLUDED__

#include "os.h"

typedef struct _os_rtc_public_interface
{
  int  (*_p_os_rtc_get)(unsigned int *,unsigned int *);
  int  (*_p_os_rtc_set)(unsigned int,unsigned int);
  int  (*_p_os_rtc_cal_get)(int *);
  int  (*_p_os_rtc_cal_set)(int);

}
T_OS_RTC_TABLE_PUB;


#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

extern int os_rtc_init(void);
extern int os_rtc_get(unsigned int *p_sec, unsigned int *p_msec);
extern int os_rtc_set(unsigned int sec, unsigned int msec);
extern int os_rtc_cal_get(int *cal);
extern int os_rtc_cal_set(int cal);

#else

#define _P_OS_RTC    ((T_OS_RTC_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_rtc))

#define os_rtc_get                 _P_OS_RTC->_p_os_rtc_get
#define os_rtc_set                 _P_OS_RTC->_p_os_rtc_set
#define os_rtc_cal_get             _P_OS_RTC->_p_os_rtc_cal_get
#define os_rtc_cal_set             _P_OS_RTC->_p_os_rtc_cal_set

#endif /* defined(_OS_C_INT_) || defined(_ALWAYS_C_INT_) */



/* --- BEGIN ERROR CODES --- */

#define E_OS_RTC                          0xB00011        // RTC section

#define E_OS_RTC_FAIL                     0xB0001100      // RTC failed
#define E_OS_RTC_NOT_INIT                 0xB0001101      // RTC not initialized
#define E_OS_RTC_PARAM                    0xB0001102      // Bad parameter

/* --- END ERROR CODES --- */



#endif /* __OS_RTC_H_PUB_INCLUDED__ */

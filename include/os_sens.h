/**************************************************************************************************
 *
 *  Description : Sensory Controller
 *                Public header file
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 **************************************************************************************************/
#ifndef __OS_SENS_PUB_INCLUDED__
#define __OS_SENS_PUB_INCLUDED__

#include "os.h"

// type values for os_sens_info() function
#define OS_SENS_ALARM           0
#define OS_SENS_TEMP            2
#define OS_SENS_BAT_INT         3
#define OS_SENS_BAT_EXT         4
#define OS_SENS_BOOT_MDL        5
#define OS_SENS_ERR_CNT         10
    
#define OS_SENS_BAT_LOW         0x8000
#define OS_SENS_BAT_MASK        0x7FFF

// alarm bits
#define ALARM_STATE_TEMP_LOW    0x00000001
#define ALARM_STATE_POWER_FAIL  0x00000002
#define ALARM_STATE_TEMP_HIGH   0x00000004
#define ALARM_STATE_FOIL_INNER  0x00000008
#define ALARM_STATE_FOIL_OUTER  0x00000010
#define ALARM_STATE_POWER_HIGH  0x00000020
#define ALARM_STATE_POWER_LOW   0x00000040
#define ALARM_STATE_EXT_ERASE   0x00000080

#define ALARM_STATE_FACT_RESET  0x00010000
#define ALARM_STATE_SENS_ERR    0x00020000
#define ALARM_STATE_MK_ERR      0x00040000

#define ALARM_STATE_PRESENT     0x80000000

typedef struct _os_sens_public_interface
{
  int (*_p_os_sens_info)(int type, int *value);
  int (*_p_os_sens_reset_alarm)(void);
  int (*_p_os_sens_erase)(unsigned int flag);
}
T_OS_SENS_TABLE_PUB;


#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

  int  os_sens_info(int type, int *value);
  int  os_sens_reset_alarm(void);
  int  os_sens_erase(unsigned int flag);

#else

  #define _P_OS_SENS    ((T_OS_SENS_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_sens))

  #define os_sens_info                _P_OS_SENS->_p_os_sens_info
  #define os_sens_reset_alarm         _P_OS_SENS->_p_os_sens_reset_alarm
  #define os_sens_erase               _P_OS_SENS->_p_os_sens_erase

#endif /* defined(_OS_C_INT_) || defined(_ALWAYS_C_INT_) */

/* --- BEGIN ERROR CODES --- */

#define E_OS_SENS                          0xB00001        // SENS section

#define E_OS_SENS_WRITE_ERR                0xB0000100      // Sensory write error
#define E_OS_SENS_READ_ERR                 0xB0000101      // Sensory read error
#define E_OS_SENS_BAD_TYPE                 0xB0000102      // Bad info type
#define E_OS_SENS_MEM_ALLOC                0xB0000103      // Error during memory allocation
#define E_OS_SENS_IO_ERR                   0xB0000104      // Sensory I/O error
#define E_OS_SENS_MK_CORR                  0xB0000105      // Corrupted Master Key
//#define E_OS_SENS_NACK                     0xB0000106      // Sensory error answer
#define E_OS_SENS_NO_ALARM                 0xB0000107      // CryptoServer not in alarm state
#define E_OS_SENS_READ_TIMEOUT             0xB0000108      // Sensory read timeout
#define E_OS_SENS_ALARM_PRESENT            0xB0000109      // Alarm still present, can't reset
#define E_OS_SENS_MSP_TIMEOUT              0xB000010A      // Controller: read timeout
#define E_OS_SENS_MSP_CMD                  0xB000010B      // Controller: bad command
#define E_OS_SENS_MSP_ADDR                 0xB000010C      // Controller: bad address
#define E_OS_SENS_MSP_DATA                 0xB000010D      // Controller: bad data
#define E_OS_SENS_MSP_CRC                  0xB000010E      // Controller: bad CRC
#define E_OS_SENS_BAD_CRC                  0xB000010F      // Bad CRC in answer

// new for SMOS-4
#define E_OS_SENS_PARAM                    0xB0000110      // Invalid parameter
#define E_OS_SENS_BUF_SIZE                 0xB0000111      // Buffer size too small
#define E_OS_SENS_ANSW_LEN                 0xB0000112      // Invalid length of answer data
#define E_OS_SENS_JOB_STATE                0xB0000113      // Invalid job state
#define E_OS_SENS_LOCKED                   0xB0000114      // Sensory controller is locked

#define E_OS_SENS_CTRL                     0xB000013       // Sensory Controller section
#define E_OS_SENS_CTRL_NACK                0xB0000130      // unknown error code
#define E_OS_SENS_CTRL_TIMEOUT             0xB0000131      // timeout
#define E_OS_SENS_CTRL_CMD                 0xB0000132      // bad command
#define E_OS_SENS_CTRL_ADDR                0xB0000133      // bad address
#define E_OS_SENS_CTRL_DATA                0xB0000134      // bad data
#define E_OS_SENS_CTRL_CRC                 0xB0000135      // bad CRC
#define E_OS_SENS_CTRL_I2C                 0xB0000136      // I2C error
#define E_OS_SENS_CTRL_BUSY                0xB0000137      // currently busy


/* --- END ERROR CODES --- */



#endif /* __OS_SENS_H_PUB_INCLUDED__ */

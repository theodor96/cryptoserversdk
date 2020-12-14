/**************************************************************************************************
 *
 * $File Identification                    $
 * $Filename          : dev_sl.h           $
 * $Module version    : x.x.x.x            $
 * $Module name       : SMOS               $
 * $Release Date      : DD.MM.YYYY         $
 *
 * description:
 *   public type definitions, constants and functions of serial line interface
 *
 * history:
 * initials |    date    | activity
 * ---------+------------+------------------------------------------------------------------------
 *   DBR    | 14.11.2000 | file rebuild, to make device independend for the SMOS
 *   DBR    | 16.03.2001 | new name convention
 *   RHE    | 27.02.2003 | definitions for flow control added
 *
 **************************************************************************************************/

#ifndef __DEV_SL_H_PUB_INCLUDED__
  #define __DEV_SL_H_PUB_INCLUDED__

  /************************************************************************************************
   * control parameters of serial line used to adjust a serial line channel of the DUART
   ************************************************************************************************/
  typedef enum dev_slctrl
  {
    DEV_SL_CTRL_SPEED = 0,
    DEV_SL_CTRL_PARITY,
    DEV_SL_CTRL_STOPBITS,
    DEV_SL_CTRL_FLOW_CTRL,
    DEV_SL_CTRL_TIMEOUT,
    DEV_SL_CTRL_TIMEOUT_READ,
    DEV_SL_CTRL_TIMEOUT_WRITE,
    DEV_SL_CTRL_DATABITS,
    DEV_SL_CTRL_RESET,
    DEV_SL_CTRL_WAKEUP,
    DEV_SL_CTRL_FLUSH,
    DEV_SL_CTRL_LINE,
    DEV_SL_CTRL_RD_SESSION_TIMEOUT,
    DEV_SL_CTRL_WR_SESSION_TIMEOUT,
    DEV_SL_CTRL_EOT
  } T_DEV_SL_CTRL;

  #define  DEV_SL_CTRL_READ_CNF      0x80000000  /* in combination with this flag the device      */
                                                 /* returns the wanted setting                    */
  /************************************************************************************************
   * definitions of valid baudrate settings
   ************************************************************************************************/
  #define DEV_SL_BR_50                50
  #define DEV_SL_BR_110               110
  #define DEV_SL_BR_300               300
  #define DEV_SL_BR_1200              1200
  #define DEV_SL_BR_2400              2400
  #define DEV_SL_BR_4800              4800
  #define DEV_SL_BR_9600              9600     
  #define DEV_SL_BR_19200             19200         
  #define DEV_SL_BR_38400             38400            
  #define DEV_SL_BR_57600             57600           
  #define DEV_SL_BR_115200            115200

  /************************************************************************************************
   * definitions other valid settings
   ************************************************************************************************/
  #define DEV_SL_NO_PARITY            0
  #define DEV_SL_EVEN_PARITY          1
  #define DEV_SL_ODD_PARITY           2

  #define DEV_SL_1_STOPBIT            0
  #define DEV_SL_15_STOPBIT           1 
  #define DEV_SL_2_STOPBIT            2 

  #define DEV_SL_5_DATABITS           0
  #define DEV_SL_6_DATABITS           1
  #define DEV_SL_7_DATABITS           2
  #define DEV_SL_8_DATABITS           3

  #define DEV_SL_NO_FLOWCTL           0
  #define DEV_SL_RTSCTS               1
  #define DEV_SL_XON_XOFF             2

  #define DEV_SL_TXBF                 1
  #define DEV_SL_RXBF                 2

  #define DEV_SL_DTR_ON               0
  #define DEV_SL_DTR_OFF              1

  /************************************************************************************************
   * io control structure definition to adjust the serial line device
   ************************************************************************************************/
  typedef struct ioctl
  {
    T_DEV_SL_CTRL  parameter;                    /* which kind of adjustment                      */
    unsigned int   value;                        /* the value write into..                        */
  } T_DEV_SL_IOCTL;
 
 
 /**************************************************************************************************
  * error codes of SL
  **************************************************************************************************/
 /* --- BEGIN ERROR CODES --- */

  #define E_OS_DEV_SL                        0xB00003    /* serial device section */

  #define E_OS_DEV_SL_BAD_HDL                0xB0000301  /* bad handle                                    */
  #define E_OS_DEV_SL_ALREADY_OPEN           0xB0000302  /* device already open                           */
  #define E_OS_DEV_SL_READ                   0xB000030D  /* read error on serial line                     */
  #define E_OS_DEV_SL_INVALID_PARAM          0xB000030E  /* parameter to be modified is invalid           */
  #define E_OS_DEV_SL_PARAM_VAL              0xB0000310  /* invalid parameter value to set control of SL   */
  #define E_OS_DEV_SL_TIMEOUT                0xB0000311  /* timeout while reading char from serial line   */
  #define E_OS_DEV_SL_PARITY_ERR             0xB0000312  /* parity error                                  */
  #define E_OS_DEV_SL_OVERRUN                0xB0000313  /* receiver over-run                             */
  #define E_OS_DEV_SL_FRAME                  0xB0000314  /* receiver frame error                          */
  #define E_OS_DEV_SL_NO_DATA                0xB0000315  /* no data ready to read                         */

 /* --- END ERROR CODES --- */


  /* old definitions for compatibility: */

  #define E_DEV_SL_READ                E_OS_DEV_SL_READ
  #define E_DEV_SL_INVALID_PARAM       E_OS_DEV_SL_INVALID_PARAM
  #define E_DEV_SL_PARAM_VAL           E_OS_DEV_SL_PARAM_VAL
  #define E_DEV_SL_TIMEOUT             E_OS_DEV_SL_TIMEOUT



#endif

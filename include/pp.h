/*****************************************************************************
 *
 *  Description : PinPAD driver
 *                Global header file
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 *****************************************************************************/
#ifndef __PP_H_PUB_INCLUDED__
#define __PP_H_PUB_INCLUDED__

#include <os_mdl.h>

/******************************************************************************
 *
 * module identification:
 *
 ******************************************************************************/
#define PP_MDL_ID          0x82
#define PP_MDL_NAME        "PP"

#ifdef CS2_SDK
  #define PP_MDL_NAMEX     "PIN pad Driver (SDK)"
#else
  #ifdef DEBUG
    #define PP_MDL_NAMEX   "PIN pad Driver (DEBUG)"
  #else
    #define PP_MDL_NAMEX   "PIN pad Driver"
  #endif
#endif

#define PP_MDL_VERSION     0x01030203

/******************************************************************************
 *
 * definitions
 *
 ******************************************************************************/
// flags for output functions
#define PP_CLEAR                  1
#define PP_APPEND                 2

// flags for input functions
#define PP_INVISIBLE              1
#define PP_NOT_EMPTY              2
#define PP_HEX                    4
#define PP_GET_KEY                8

// pinpad types
#define PP_TYPE_SAFEPAD           0
#define PP_TYPE_CARDMAN8630       1     // not longer supported
#define PP_TYPE_ACR80             2     // not longer supported
#define PP_TYPE_AUTO1             3
#define PP_TYPE_CYBERJACK         4
#define PP_TYPE_CYBERJACK_ONE     5

#define PP_TYPE_DEFAULT           PP_TYPE_AUTO1

// display message codes
#define PP_TXT_INSERT_CARD        0
#define PP_TXT_ENTER_PIN          1
#define PP_TXT_ENTER_NEW_PIN      2
#define PP_TXT_REPEAT_ENTRY       3
#define PP_TXT_BAD_REPETITION     4
#define PP_TXT_CONFIRM            5

// standard key codes for flag PP_GET_KEY
#define PP_KEY_CODE_0             0
#define PP_KEY_CODE_1             1
#define PP_KEY_CODE_2             2
#define PP_KEY_CODE_3             3
#define PP_KEY_CODE_4             4
#define PP_KEY_CODE_5             5
#define PP_KEY_CODE_6             6
#define PP_KEY_CODE_7             7
#define PP_KEY_CODE_8             8
#define PP_KEY_CODE_9             9

#define PP_KEY_CODE_CANCEL        0x0A
#define PP_KEY_CODE_OK            0x0B
#define PP_KEY_CODE_CLEAR         0x0C
#define PP_KEY_CODE_ASTERIK       0x0D
#define PP_KEY_CODE_SHIFT_DOWN    0x0E
#define PP_KEY_CODE_SHIFT_UP      0x0F

// key codes for CP/8
#define SP_KEY_STOP               0x10
#define SP_KEY_CORR               0x11
#define SP_KEY_OK                 0x12

// smartcard states
#define PP_SC_REMOVED             0
#define PP_SC_INSERTED            1
#define PP_SC_POWERED             2

/******************************************************************************
 *
 * public interface:
 *
 ******************************************************************************/
typedef struct
{
  void *p_data;
  int  (*p_start)();
  int  (*p_stop)(void);
  int  (*p_pre_replace)(void);
  int  (*p_pre_delete)(void);
  void *p_dumy;
  const void *p_module_info;

  int  (*p_open)(void);
  int  (*p_display)(int,int,int,char *);
  int  (*p_getkey)(int,char *);
  int  (*p_getstr)(int,int,int,int,int,char *,int *);
  void (*p_close)(void);
  int  (*p_card_apdu)(int,unsigned char *,int *,unsigned char *,unsigned int *);
  int  (*p_card_reset)(unsigned char *,int *);
  int  (*p_card_unload)(void);
  int  (*p_gethexdata)(int,int,int,int,int,unsigned char *);
  int  (*p_set_type)(int, int);
  int  type;
  int  (*p_output)(const char *text);
  int  (*p_request)(const char *text, unsigned int timeout);

  int  (*p_input)(const char *text,
                  unsigned int flags,
                  unsigned int timeout,
                  unsigned int l_input,
                  unsigned char *p_input,
                  unsigned int *p_l_input);

  int  (*p_pin_verify)(unsigned int  timeout,
                       unsigned int  l_apdu,
                       unsigned char *p_apdu,
                       unsigned int  pos,
                       unsigned int  l_pin,
                       unsigned char *p_pin,
                       unsigned int  *p_sw);

  int  (*p_pin_change)(unsigned int  timeout,
                       unsigned int  l_apdu,
                       unsigned char *p_apdu,
                       unsigned int  pos,
                       unsigned int  l_pin_old,
                       unsigned char *p_pin_old,
                       unsigned int  l_pin_new,
                       unsigned char *p_pin_new,
                       unsigned int  *p_sw);

  // new as of version 1.3.1.1
  int  (*p_slot_stat)(unsigned int *p_slot_stat);
}
T_PP_TABLE_PUB;

#ifdef _PP_C_INT_

/******************************************************************************
 *
 * function prototypes used by the module (internal)
 *
 ******************************************************************************/
int  pp_start(T_OS_MDL_HDL,void *,void *);
int  pp_pre_replace(void);
int  pp_pre_delete(void);

#define pp_open           Module_pub.p_open
#define pp_display        Module_pub.p_display
#define pp_getkey         Module_pub.p_getkey
#define pp_getstr         Module_pub.p_getstr
#define pp_close          Module_pub.p_close
#define pp_card_apdu      Module_pub.p_card_apdu
#define pp_card_reset     Module_pub.p_card_reset
#define pp_card_unload    Module_pub.p_card_unload
#define pp_gethexdata     Module_pub.p_gethexdata
#define pp_cur_type       Module_pub.type
#define pp_output         Module_pub.p_output
#define pp_input          Module_pub.p_input
#define pp_request        Module_pub.p_request
#define pp_pin_verify     Module_pub.p_pin_verify
#define pp_pin_change     Module_pub.p_pin_change
// new as of version 1.3.1.0
#define pp_slot_stat      Module_pub.p_slot_stat

#else

/******************************************************************************
 *
 * external interface to be used by other modules
 *
 ******************************************************************************/

extern MDL_GLOBAL T_OS_MDL_HDL P_PP;

#define _P_PP  ((T_PP_TABLE_PUB *)P_PP)         // shortcut

#define P_pp_data         (_P_PP->_p_data);

#define pp_start          _P_PP->p_start
#define pp_pre_replace    _P_PP->p_pre_replace
#define pp_pre_delete     _P_PP->p_pre_delete
#define pp_open           _P_PP->p_open
#define pp_output         _P_PP->p_output
#define pp_input          _P_PP->p_input
#define pp_request        _P_PP->p_request
#define pp_close          _P_PP->p_close
#define pp_card_apdu      _P_PP->p_card_apdu
#define pp_card_reset     _P_PP->p_card_reset
#define pp_card_unload    _P_PP->p_card_unload
#define pp_set_type       _P_PP->p_set_type
#define pp_cur_type       _P_PP->type           // do not modify type directly!!! (use pp_set_type instead)
#define pp_pin_verify     _P_PP->p_pin_verify
#define pp_pin_change     _P_PP->p_pin_change
// new as of version 1.3.1.0
#define pp_slot_stat      _P_PP->p_slot_stat

// obsolete functions:
#define pp_display        _P_PP->p_display
#define pp_getkey         _P_PP->p_getkey
#define pp_getstr         _P_PP->p_getstr
#define pp_gethexdata     _P_PP->p_gethexdata

#endif /* _PP_C_INT_ */


/* Error Codes:  (0xB0000000 | (PP_MDL_ID << 16) | (errno))  */

/* --- BEGIN ERROR CODES --- */

#define E_PP                            0xB082          // CryptoServer module PP, PIN pad driver

#define E_PP_ABORT                      0xB0820001      // timeout, or operation aborted by user
#define E_PP_LEN                        0xB0820002      // command block too long
#define E_PP_WRITE_TIMEOUT              0xB0820003      // timeout while writing to PIN pad
#define E_PP_BUFSIZE                    0xB0820004      // answer buffer too small
#define E_PP_READ_TIMEOUT               0xB0820005      // timeout while reading from PIN pad
#define E_PP_IO                         0xB0820006      // IO error
#define E_PP_NOT_OPEN                   0xB0820007      // connection not open
#define E_PP_INVAL                      0xB0820008      // invalid parameter
#define E_PP_BAD_RAPDU                  0xB0820009      // bad RAPDU from smartcard
#define E_PP_NO_CARD                    0xB082000A      // no smartcard in reader
#define E_PP_BAD_TYPE                   0xB082000B      // bad PIN pad type specified
#define E_PP_DATALEN                    0xB082000C      // bad length of command block
#define E_PP_PROT                       0xB082000D      // protocol error
#define E_PP_KEY_TIMEOUT                0xB082000E      // timeout while waiting for key input
#define E_PP_RESET_TIMEOUT              0xB082000F      // timeout while waiting for card insertation
#define E_PP_PIN_REPETITION             0xB0820010      // bad repetition of PIN entry
#define E_PP_NOT_SUPPORTED              0xB0820011      // function is not supported
#define E_PP_PARAM                      0xB0820012      // invalid parameter
#define E_PP_ACCESS_DENIED              0xB0820013      // access denied
#define E_PP_BAD_INPUT                  0xB0820014      // bad input
#define E_PP_CARD_TIMEOUT               0xB0820015      // no response from smartcard
#define E_PP_READER_NOT_CONNECTED       0xB0820016      // no supported smartcard reader connected
#define E_PP_CC_BLOCKED                 0xB0820017      // not allowed in CC Endorsed Mode

#define E_PP_PPERR                      0xB08201        // PIN pad error
#define E_PP_CCID                       0xB08202        // CCID Error


/* --- END ERROR CODES --- */


#endif /* __PP_H_PUB_INCLUDED__ */

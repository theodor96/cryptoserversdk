//--------------------------------------------------------------------------------------------------
//
//  $File Identification                    $
//  $Filename          : sc.h               $
//  $Module version    : x.x.x.X            $
//  $Module name       : SC                 $
//  $Release Date      : DD.MM.YYYY         $
//
//  Autor         : Dipl. Ing. Thomas Ley
//                  Utimaco IS GmbH
//
//  Description   : Global header file of CryptoServer module SC
//                  Must be included in every CryptoServer software that uses
//                  functions of this module
//
//  History :
//  Date       | Version |                 Action                                          | Author
//  -----------+---------+-----------------------------------------------------------------+--------
//  26.04.2001 |         | Creation                                                        |  T.Ley
//--------------------------------------------------------------------------------------------------
#ifndef __SC_H_PUB_INCLUDED__
#define __SC_H_PUB_INCLUDED__

#include "os_mdl.h"
#include "os_mem.h"
#include "stype.h"

#ifdef DEBUG
    #include "cmds.h"
#endif
#ifdef DEBUG2
    #define debug_xprint(x,y,z)     cmds_xprint(x,y,z)
#else
    #define debug_xprint(x,y,z)
#endif

//-----------------------------------------------------------------------------
// module identification:
//-----------------------------------------------------------------------------
#define SC_MDL_ID            0x85            // ID of the module
#define SC_MDL_NAME          "SC"            // Short name of the module
#ifdef CS2_SDK
#define SC_MDL_NAMEX       "Smartcard module (SDK)"    // Long name of the module
#else
#ifdef DEBUG
#define SC_MDL_NAMEX     "Smartcard module (DEBUG)"
#else
#define SC_MDL_NAMEX     "Smartcard module"
#endif
#endif
#define SC_MDL_VERSION       0x01020005      // Version of the module

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
//Use the following defines for the sc module of a version <= 1.0.0.5
//for the later hash module, this defines are deprecated. From version 1.1.0.0
//on one can use all defines from the hash module.
#define SC_HASH_SHA1            1
#define SC_HASH_RIPEMD160       2
#define SC_HASH_MD5             3
#define SC_HASH_MD2             4

// data types
typedef struct
{
    int            mode;                    // mode of the smartcard
    int            cardType;                // Type of card
    unsigned char  appl_name[16];           // application name (AID of DF)
    unsigned int   appl_name_len;           // length of application name
    unsigned short id_test;                 // test file, to verify card type
    unsigned char  pwd_no;                  // ref.no. of PIN file
    unsigned short id_pubkey;               // file id of public key file
    unsigned short id_pubEC;                // file id of public key file for EC
    unsigned short id_cert;                 // file id of certificate file
    unsigned char  id_key;                  // ref.no. of key for secure messaging
    unsigned short id_pin;                  // ref.no. of PIN file
    unsigned short sfi_info;                // SFI of key info file
    unsigned short sfi_key;                 // SFI of key file
    unsigned short sfi_gdo;                 // SFI of the gdo file
}
T_SC_PARAM;

//old structure for signature cards. Now only needed as sonstant return
typedef struct
{
    unsigned char  appl_name[16];           // application name (AID of DF)
    unsigned int   appl_name_len;           // length of application name
    unsigned short id_test;                 // test file, to verify card type
    unsigned char  pwd_no;                  // ref.no. of PIN file
    unsigned short id_pubkey;               // file id of public key file
    unsigned short id_cert;                 // file id of certificate file
    unsigned int   sig_flags;               // flags for signature generation (padding, ...)
}
T_SC_SIG_PARAM;

//old structure for applicaton data. Now only needed as sonstant return
typedef struct
{
    unsigned char  appl_name[16];           // application name (AID of DF)
    unsigned int   appl_name_len;           // length of application name
    unsigned char  sm_key_id;               // ref.no. of key for secure messaging
    unsigned char  pwd_no;                  // ref.no. of PIN file
    unsigned char  sfi_info;                // SFI of key info file
    unsigned char  sfi_key;                 // SFI of key file
}
T_SC_APPL_DATA_DES_KMGM;
#define SC_APPL_TYPE_DES_KMGM   0

//-----------------------------------------------------------------------------
// public interface:
//-----------------------------------------------------------------------------
typedef struct
{
    void   *p_data;
    int    (*p_start)();
    int    (*p_stop)(void);
    int    (*p_pre_replace)(void);
    int    (*p_pre_delete)(void);
    void   *p_dumy;
    const void   *p_module_info;

    int (*p_open)             ( unsigned char*, unsigned int, int, unsigned char*, int* );
    int (*p_close)            ();
    int (*p_login)            ( int, int* );
    int (*p_read_rec)         ( int, int, unsigned int, int, unsigned char*, int* );
    int (*p_update_rec)       ( int, int, int, unsigned char*, unsigned int, int* );
    int (*p_read_gdo)         ( unsigned char*, int* );
    int (*p_change_pwd)       ( int, int* );
    int (*p_load_ess)         ( int, unsigned char* );
    int (*p_personalize)      ( unsigned int, unsigned char*, int*, int* );
    int (*p_sign)             ( int, unsigned char*, unsigned int*, unsigned char*, int* );
    int (*p_get_pubkey)       ( int, unsigned int*, unsigned char*, unsigned int*, unsigned char*, int* );
    int (*p_get_cert)         ( int, unsigned int*, unsigned char*, int* );
    void *(*p_get_appl_data)  ( unsigned int);
    int (*p_open_sig)         ( unsigned char *,T_SC_SIG_PARAM const **,int * );
    int (*p_login_password)   ( unsigned char*, int, int* );
    int (*p_change_pwd_extern)( unsigned char*, int, unsigned char*, int, int* );
    // int (*p_get_pubEC)        ( unsigned int*, unsigned char*, unsigned int*, unsigned char*, int* );
}
T_SC_TABLE_PUB;

#ifdef _SC_C_INT_
//-----------------------------------------------------------------------------
// function prototypes used by the module (internal)
//-----------------------------------------------------------------------------
int sc_start(T_OS_MDL_HDL,void *,void *);
int sc_stop(void);
int sc_pre_replace(void);
int sc_pre_delete(void);

int sc_open( unsigned char*, unsigned int, int, unsigned char*, int* );
int sc_close();
int sc_login( int, int* );
int sc_read_rec( int, int, unsigned int, int, unsigned char*, int* );
int sc_update_rec( int, int, int, unsigned char*, unsigned int, int* );
int sc_read_gdo( unsigned char*, int* );
int sc_change_pwd( int, int* );
int sc_load_ess( int, unsigned char* );
int sc_personalize( unsigned int, unsigned char*, int*, int* );
int sc_sign( int, unsigned char*, unsigned int*, unsigned char*, int* );
int sc_get_pubkey( int, unsigned int*, unsigned char*, unsigned int*, unsigned char*, int* );
int sc_get_cert( int, unsigned int*, unsigned char*, int* );
void *sc_get_appl_data(unsigned int);
int sc_open_sig(unsigned char *,T_SC_SIG_PARAM const **,int *);
int sc_login_password( unsigned char*, int, int*);
int sc_change_pwd_extern( unsigned char*, int, unsigned char*, int, int* );
// int sc_get_pubEC( unsigned int*, unsigned char*, unsigned int*, unsigned char*, int* );
#else
//-----------------------------------------------------------------------------
// external interface to be used by other modules
//-----------------------------------------------------------------------------
extern MDL_GLOBAL T_OS_MDL_HDL P_SC;

#define _P_SC ((T_SC_TABLE_PUB *)P_SC)         // shortcut

#define P_sc_data            (_P_SC->_p_data);

#define sc_start             _P_SC->p_start
#define sc_stop              _P_SC->p_stop
#define sc_sync              _P_SC->p_sync
#define sc_pre_replace       _P_SC->p_pre_replace
#define sc_pre_delete        _P_SC->p_pre_delete

#define sc_open              _P_SC->p_open
#define sc_close             _P_SC->p_close
#define sc_login             _P_SC->p_login
#define sc_read_rec          _P_SC->p_read_rec
#define sc_update_rec        _P_SC->p_update_rec
#define sc_read_gdo          _P_SC->p_read_gdo
#define sc_change_pwd        _P_SC->p_change_pwd
#define sc_load_ess          _P_SC->p_load_ess
#define sc_personalize       _P_SC->p_personalize
#define sc_sign              _P_SC->p_sign
#define sc_get_pubkey        _P_SC->p_get_pubkey
#define sc_get_cert          _P_SC->p_get_cert
#define sc_get_appl_data     _P_SC->p_get_appl_data
#define sc_open_sig          _P_SC->p_open_sig
#define sc_login_password    _P_SC->p_login_password
#define sc_change_pwd_extern _P_SC->p_change_pwd_extern
// #define sc_get_pubEC         _P_SC->p_get_pubEC

#endif //_SC_C_INT_

//-----------------------------------------------------------------------------
// Error Codes:  (0xB0000000 | (SC_MDL_ID << 16) | (errno))
//-----------------------------------------------------------------------------
// --- BEGIN ERROR CODES ---
#define E_SC                    0xB085              // CryptoServer Module SC
#define E_SC_APDU_SELECT        0xB0850002          // Card Error from "select" Command
#define E_SC_APDU_IAUTH         0xB0850003          // Card Error from "internal auth." Command
#define E_SC_BAD_KEY            0xB0850004          // Wrong SM Key
#define E_SC_APDU_MSE           0xB0850006          // Card Error from "mse" Command
#define E_SC_APDU_READREC       0xB0850007          // Card Error from "read record" Command
#define E_SC_RECLEN             0xB0850008          // Bad Record Length
#define E_SC_NO_RECORD          0xB0850009          // Record not Found
#define E_SC_NO_FILE            0xB085000A          // File not Found
#define E_SC_DENIED             0xB085000B          // Access Denid
#define E_SC_BAD_PARAM          0xB085000C          // Bad Parameter: SFI, REC#
#define E_SC_DATALEN            0xB085000D          // Bad Data Length
#define E_SC_SM                 0xB085000E          // Bad Tag for SM
#define E_SC_APDU_UPDREC        0xB085000F          // Card Error from "update record" Command
#define E_SC_APDU_CHGPWD        0xB0850010          // Card Error from "chg. passw." Command
#define E_SC_NO_PWDFILE         0xB0850011          // Pasword File not Found
#define E_SC_BAD_PDATA          0xB0850012          // Bad Personalization Data
#define E_SC_APDU_PERS          0xB0850013          // Card Error while Personalizing
#define E_SC_APDU_GETSKEY       0xB0850014          // Card Error from "get sessionkey" Command
#define E_SC_NO_APPL            0xB0850015          // Application not Found
#define E_SC_APDU_READBIN       0xB0850016          // Card Error from "read binary" Command
#define E_SC_BAD_PIN_LEN        0xB0850017          // Bad PIN Length
#define E_SC_MEM                0xB0850018          // Memory Allocation Error
#define E_SC_APDU_PSO           0xB0850019          // Card Error from "pso" Command
#define E_SC_BAD_CERT           0xB085001A          // Bad Certificate Format
#define E_SC_APDU_GETDATA       0xB085001B          // Card Error from "get data" Command
#define E_SC_NOT_IMPLEMENTED    0xB085001D          // This Action is not Implmented on the Found Card Type
#define E_SC_INVALID_PIN        0xB085001E          // Invalid Pin
#define E_SC_NOT_SUPPORTED      0xB085001F          // Signing Supported until 48 Byte (Possible Hashes md5, ripemd160, sha1, sha224)
#define E_SC_WRONG_CARD_MODE    0xB0850020          // Wrong Command for Card Application
#define E_SC_HASH_SIZE          0xB0850021          // Hash Size Bigger than 40% of the Key Size
#define E_SC_NOPEN_OR_UNKNOWN   0xB0850022          // Card not Opened Before or Unknown Card
//unused Error Codes in actual Version
#define E_SC_APPL_NAME          0xB0850001          // Bad Length of Application Name
#define E_SC_APDU_VERPWD        0xB0850005          // Card Error from "ver. passw." Command
#define E_SC_BAD_APPLTYPE       0xB085001C          // Unknown Application Type
// --- END ERROR CODES ---

#endif //__SC_H_PUB_INCLUDED__


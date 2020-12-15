/**************************************************************************************************
 *
 * $File Identification                    $
 * $Filename          : post.h             $
 * $Module version    : x.x.x.x            $
 * $Module name       : POST               $
 * $Release Date      : DD.MM.YYYY         $
 *
 * Author             : Eugen Pek
 *                      Utimaco IS GmbH
 *
 * Description        : Global header file of CryptoServer module POST
 *
 **************************************************************************************************/
#ifndef __POST_H_PUB_INCLUDED__
  #define __POST_H_PUB_INCLUDED__

#include "os_mdl.h"
#include "os_log.h"
#include "os_audit.h"

#include "aes.h"
#include "ecdsa.h"
#include "eca.h"
#include "hash.h"
#include "vrsa.h"
#include "dsa.h"
#include "vdes.h"

#include "cmds.h"

//-----------------------------------------------------------------------------
// module identification:
//-----------------------------------------------------------------------------
#define POST_MDL_ID          0x04                         // ID of the module
#define POST_MDL_NAME        "POST"                       // Abbreviation of the module
#ifdef CS2_SDK
  #define POST_MDL_NAMEX     "POST Module SDK"            // Long name of the module
#else
  #ifdef DEBUG
    #define POST_MDL_NAMEX   "POST Module DBG"            // Long name of the module
  #else
    #define POST_MDL_NAMEX   "POST Module"                // Long name of the module
  #endif
#endif
#define POST_MDL_VERSION     0x01000200                   // Version of the module  (d.x.d.d)

#define TESTID_AES           0x00000001
#define TESTID_ECDSA         0x00000002
#define TESTID_HASH          0x00000003                   // HASH and KDF
#define TESTID_HMAC          0x00000004
#define TESTID_RSA           0x00000005
#define TESTID_DSA           0x00000006
#define TESTID_DES           0x00000007

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
  const void *p_module_info;

  int    (*p_post_poweron_selftests)(void);
  int    (*p_post_selftest)(int testid);

}
T_POST_TABLE_PUB;

#ifdef _POST_C_INT_
  //-----------------------------------------------------------------------------
  // function prototypes used by the module (internal)
  //----------------------------------------------------------------------------- 
  int  post_start(T_OS_MDL_HDL,void *,void *);
  int  post_stop(void);
  int  post_pre_replace(void);
  int  post_pre_delete(void);

  int  post_poweron_selftests(void);
  int  post_selftest(int testid);

#else
  //-----------------------------------------------------------------------------
  // external interface to be used by other modules
  //-----------------------------------------------------------------------------
  extern MDL_GLOBAL T_OS_MDL_HDL P_POST;

  #define _P_POST ((T_POST_TABLE_PUB *)P_POST)     // shortcut

  #define post_start         _P_POST->p_start
  #define post_stop          _P_POST->p_stop
  #define post_pre_replace   _P_POST->p_pre_replace
  #define post_pre_delete    _P_POST->p_pre_delete  
  
  #define post_poweron_selftests  _P_POST->p_post_poweron_selftests
  #define post_selftest      _P_POST->p_post_selftest

#endif // _POST_C_INT_

//-----------------------------------------------------------------------------
// Error Codes:  (0xB0000000 | (POST_MDL_ID << 16) | (errno))
//-----------------------------------------------------------------------------

// --- BEGIN ERROR CODES ---

#define E_POST                            0xB004          // CryptoServer module POST

#define E_POST_INVALID_PARAM              0xB0040010      // Invalid parameter in utility section
#define E_POST_INVALID_TESTID             0xB0040011      // Invalid testid passed to post_selftest function

#define E_POST_UTL_TEST_FAILED            0xB0040070      // known answer tests for (internally used only) utility functions failed
#define E_POST_AES_ENC_KAT_FAILED         0xB0040071      // known answer test for AES encrypt/decrypt failed
#define E_POST_AES_MAC_KAT_FAILED         0xB0040072      // known answer test for AES CBC-MAC failed
#define E_POST_AES_CMAC_KAT_FAILED        0xB0040073      // known answer test for AES CMAC failed
#define E_POST_AES_GCM_KAT_FAILED         0xB0040074      // known answer test for AES GCM failed
#define E_POST_AES_GMAC_KAT_FAILED        0xB0040075      // known answer test for AES GMAC failed
#define E_POST_AES_OFB_KAT_FAILED         0xB0040076      // known answer test for AES OFB failed
#define E_POST_ECDSA_PCT_FAILED           0xB0040077      // pair-wise consistency test of ECDSA failed
#define E_POST_ECC_CDH_KAT_FAILED         0xB0040078      // known answer test for ECC CDH failed
#define E_POST_HASH_KAT_FAILED            0xB0040079      // known answer test of HASH failed
#define E_POST_HMAC_KAT_FAILED            0xB004007A      // known answer test for HMAC failed
#define E_POST_ALGO_TEST_PARAM            0xB004007B      // invalid parameter in algo test function call
#define E_POST_KDF_800108_KAT_FAILED      0xB004007C      // known answer test for KDF_800108 failed
#define E_POST_RSA_SIGN_KAT_FAILED        0xB004007D      // known answer test for RSA sign/verify failed
#define E_POST_RSA_ENC_PCT_FAILED         0xB004007E      // pair-wise consistency test for RSA encrypt/decrypt failed
#define E_POST_DSA_SIGN_PCT_FAILED        0xB004007F      // pair-wise consistency test for DSA sign/verify failed
#define E_POST_DES_KAT_FAILED             0xB0040080      // known answer test of DES failed
#define E_POST_RSA_ENC_KAT_FAILED         0xB0040081      // known answer test for RSA encrypt/decrypt failed
#define E_POST_KDF_X9_42_KAT_FAILED       0xB0040082      // known answer test for KDF ANSI X9.42 failed
#define E_POST_KDF_X9_63_KAT_FAILED       0xB0040083      // known answer test for KDF ANSI X9.63 failed
#define E_POST_KDF_SP800_56A_KAT_FAILED   0xB0040084      // known answer test for KDF NIST SP 800-56A failed
#define E_POST_DSA_DH_KAT_FAILED          0xB0040085      // known answer test for DH primitive failed
#define E_POST_ECDSA_TR03111_KAT_FAILED   0xB0040086      // known answer test for ECDSA TR03111 primitive failed
#define E_POST_ECDH_KAT_FAILED            0xB0040087      // known answer test for ECDH primitive failed
#define E_POST_KDF_TLS12_KAT_FAILED       0xB0040088      // known answer test for TLS1.2 KDF failed

// --- END ERROR CODES ---

#endif // __POST_H_PUB_INCLUDED__

/*****************************************************************************
 *
 *  $File Identification                    $
 *  $Filename          : vdes.h             $
 *  $Module version    : x.x.x.x            $
 *  $Module name       : VDES               $
 *  $Release Date      : DD.MM.YYYY         $
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Utimaco AG
 *
 *  Description : Global header file of CS2000 module VDES
 *                Must be included in every CS2000 software that uses
 *                functions of this module
 *
 *  History     :
 *  Date       |                 Action                          |  Author
 *  -----------|-------------------------------------------------|---------
 *  26.04.2001 | Creation                                        |  R.H.
 *  04.11.2002 | Added define for ISO hash length                |  CHB
 *  20.04.2004 | new flag VDES_USE_PSEUDO_RND                    |  R.H.
 *****************************************************************************/
#ifndef __VDES_H_PUB_INCLUDED__
  #define __VDES_H_PUB_INCLUDED__

#include <os_mdl.h>
#include <os_mem.h>

#include <stype.h>

/* module identification: */

#define VDES_MDL_ID          0x81            /* ID of the module          */
#define VDES_MDL_NAME        "VDES"          /* Short name of the module  */

#ifdef CS2_SDK
  #define VDES_MDL_NAMEX     "DES Module SDK"      /* Long name of the module   */
#else
  #ifdef DEBUG
    #define VDES_MDL_NAMEX   "DES Module DEBUG"      /* Long name of the module   */
  #else
    #define VDES_MDL_NAMEX   "DES Module"          /* Long name of the module   */
  #endif
#endif

#define VDES_MDL_VERSION   0x01000A00            /* Version of the module     */



typedef struct
{
    int    flags;                                // type of key: single, triple or extended triple DES
    int    error;
    int    key[96];
} VDES_KEY;


/*************************************************************************************************
 * define modes for DES core
 * The 16 MSB contains the offset that is used to access the next working key. This bits are used
 * signed offset.
 * The 16 LSB contains the number of rounds performed by the DES core.
 *************************************************************************************************/
#define DES_MODE_ENCRYPT       ((int) 0x00020010) /* select single DES encryption                */
#define DES_MODE_DECRYPT       ((int) 0xFFFE0010) /* select single DES decryption                */

#define DES_MODE_ENCRYPT3      ((int) 0x00020030) /* select tripple DES encryption               */
#define DES_MODE_DECRYPT3      ((int) 0xFFFE0030) /* select tripple DES decryption               */


// definitions for flags:
#define VDES_SINGLE_DES        ((int) 0x00000010) // 1
#define VDES_TRIPLE_DES        ((int) 0x00000030) // 2
#define VDES_EXT_TRIPLE_DES    ((int) 0x00000030) // 3

// length definitions
#define VDES_KEY_LEN           8
#define VDES_ISO_HASH_LB      16                 /* Length of the ISO hash value, calculated by
                                                  * this module                                   */

// definitions for mode parameter
#define VDES_ENC               ((int) 0x00020000) // 1     // encryption
#define VDES_DEC               ((int) 0xFFFE0000) // 0     // decryption
#define VDES_ECB               ((int) 0x00002000) // 2     // ECB mode
#define VDES_CBC               ((int) 0x00004000) // 4     // CBC mode
#define VDES_CFB1              ((int) 0x00006000) // 6     // CFB1 mode
#define VDES_MODE_MASK         ((int) 0x0000F000) // the nibble used for the different DES-modes


// padding mechanisms
#define VDES_PAD_PKCS           0x100
#define VDES_PAD_ISO7816        0x200
#define VDES_PAD_ISO10126       0x300

// flags for vdes_gen_key
#define VDES_USE_REAL_RND      0       // use read random number generator for key generation
#define VDES_USE_PSEUDO_RND    0x100   // use pseudo random number generator for key generation



/* public interface: */

extern MDL_GLOBAL unsigned char *p_global_sec_mem;

typedef struct
{
    void   *p_data;
    int    (*p_start)();    // T_OS_MDL_HDL, void*, void*);
    int    (*p_stop)(void);
    int    (*p_pre_replace)(void);
    int    (*p_pre_delete)(void);
    void   *p_dumy;
    const void   *p_module_info;

    VDES_KEY** p_global_key;
    VDES_KEY** p_os_mkv;

    int (*p_mkkey)         ( int keylen, unsigned char* p_key, VDES_KEY* p_key_buff, VDES_KEY** pp_key_buff );
    VDES_KEY* (*p_pkey)    ( int keylen, unsigned char* p_key, VDES_KEY* p_key_buff );
    int (*p_free)          ( VDES_KEY* p_key_buff );
    int (*p_keyerror)      ( VDES_KEY* p_key_buff );
    int (*p_chk_key)       ( int keylen, unsigned char* p_key );
    int (*p_set_odd_parity)( int len, unsigned char* p_data );
    int (*p_gen_key )      ( int keylen, unsigned char* p_key );
    int (*p_ecb)           ( VDES_KEY* p_key_buff, int mode, unsigned int len, unsigned char* p_data_in, unsigned char* p_data_out );
    int (*p_cbc)           ( VDES_KEY* p_key_buff, int mode, unsigned char* p_iv_in, unsigned int len, unsigned char* p_data_in,
                             unsigned char* p_data_out, unsigned char* p_iv_out );
    int (*p_cfb1)          ( VDES_KEY* p_key_buff, int mode, unsigned char* p_iv_in, unsigned int len, unsigned char* p_data_in,
                             unsigned char* p_data_out, unsigned char* p_iv_out );
    int (*p_vdes)          ( VDES_KEY* p_key_buff, int mode, unsigned char* p_iv_in, unsigned int len, unsigned char* p_data_in,
                             unsigned char* p_data_out, unsigned char* p_iv_out );
    int (*p_iso_hash)      ( unsigned int len, unsigned char* p_data, unsigned char pad_value, unsigned char* p_iv,
                             unsigned char* p_hash );
    int (*p_mac)           ( VDES_KEY* p_key_buff, unsigned int len, unsigned char* p_data, unsigned char pad_value,
                             unsigned char* p_iv, unsigned char* p_mac );
    int (*p_cbc_rmac)      ( VDES_KEY* p_key_buff, unsigned int len, unsigned char* p_data, unsigned char pad_value,
                             unsigned char* p_iv, unsigned char* p_mac );
    int (*p_cfb_rmac)      ( VDES_KEY* p_key_buff, unsigned int len, unsigned char* p_data, unsigned char pad_value,
                             unsigned char* p_iv, unsigned char* p_mac );
    int (*p_cbc_pad)       ( VDES_KEY* p_key_buff,int mode, unsigned char* p_iv_in,unsigned int len,unsigned char* p_data_in,
                             unsigned int pad,unsigned char* p_data_out );
    int (*p_vdes_cbc_xpad) ( VDES_KEY *p_key_buff, int mode, unsigned int padding, unsigned char *p_iv_in,
                             unsigned int len, unsigned char *p_data_in, unsigned char *p_data_out);
    int (*p_vdes_padding_length) (unsigned int padding, unsigned int l_data, unsigned char *p_data, unsigned int *p_l_pad);
    int (*p_vdes_unpad)    ( unsigned int padding, unsigned int *p_l_data, unsigned char *p_data);

} T_VDES_TABLE_PUB;



#ifdef _VDES_C_INT_

/* function prototypes used by the module (internal) */

int  vdes_start(T_OS_MDL_HDL,void *,void *);
int  vdes_stop(void);
int  vdes_pre_replace(void);
int  vdes_pre_delete(void);

int vdes_mkkey( int keylen, unsigned char* p_key, VDES_KEY* p_key_buff, VDES_KEY** pp_key_buff );
VDES_KEY* vdes_pkey( int keylen, unsigned char* p_key, VDES_KEY* p_key_buff );
int vdes_free ( VDES_KEY* p_key_buff );
int vdes_keyerror( VDES_KEY* p_key_buff );
int vdes_chk_key( int keylen, unsigned char* p_key );
int vdes_set_odd_parity( int len, unsigned char* p_data );
int vdes_gen_key( int keylen, unsigned char* p_key );
int vdes_ecb( VDES_KEY* p_key_buff, int mode, unsigned int len, unsigned char* p_data_in, unsigned char* p_data_out );
int vdes_cbc( VDES_KEY* p_key_buff, int mode, unsigned char* p_iv_in, unsigned int len, unsigned char* p_data_in,
              unsigned char* p_data_out, unsigned char* p_iv_out );
int vdes_cfb1( VDES_KEY* p_key_buff, int mode, unsigned char* p_iv_in, unsigned int len, unsigned char* p_data_in,
               unsigned char* p_data_out, unsigned char* p_iv_out );
int vdes( VDES_KEY* p_key_buff, int mode, unsigned char* p_iv_in, unsigned int len, unsigned char* p_data_in,
          unsigned char* p_data_out, unsigned char* p_iv_out );
int vdes_iso_hash( unsigned int len, unsigned char* p_data, unsigned char pad_value, unsigned char* p_iv,
                   unsigned char*  p_hash );
int vdes_mac( VDES_KEY* p_key_buff, unsigned int len, unsigned char* p_data, unsigned char pad_value,
              unsigned char*  p_iv, unsigned char* p_mac );
int vdes_cbc_rmac( VDES_KEY* p_key_buff, unsigned int len, unsigned char* p_data, unsigned char pad_value,
              unsigned char*  p_iv, unsigned char* p_mac );
int vdes_cfb_rmac( VDES_KEY* p_key_buff, unsigned int len, unsigned char* p_data, unsigned char pad_value,
                   unsigned char*  p_iv, unsigned char* p_mac );
int vdes_cbc_pad( VDES_KEY* p_key_buff,int mode, unsigned char* p_iv_in,unsigned int len, unsigned char* p_data_in,
                  unsigned int pad,unsigned char* p_data_out );
int vdes_cbc_xpad       (VDES_KEY *p_key_buff, int mode, unsigned int padding, unsigned char *p_iv_in,
                         unsigned int len, unsigned char *p_data_in, unsigned char *p_data_out);
int vdes_padding_length (unsigned int padding, unsigned int l_data, 
                         unsigned char *p_data, unsigned int *p_l_pad);
int vdes_unpad          (unsigned int padding, unsigned int *p_l_data, unsigned char *p_data);

#else

/* external interface to be used by other modules */

extern MDL_GLOBAL T_OS_MDL_HDL P_VDES;

#define _P_VDES ((T_VDES_TABLE_PUB *)P_VDES)         /* shortcut */

#define P_vdes_data         (_P_VDES->_p_data);

#define vdes_start          _P_VDES->p_start
#define vdes_stop           _P_VDES->p_stop
#define vdes_pre_replace    _P_VDES->p_pre_replace
#define vdes_pre_delete     _P_VDES->p_pre_delete

#define vdes_p_global_key   (*(_P_VDES->p_global_key))
#define vdes_p_os_mkv       (*(_P_VDES->p_os_mkv))

#define vdes_mkkey          _P_VDES->p_mkkey
#define vdes_pkey           _P_VDES->p_pkey
#define vdes_free           _P_VDES->p_free
#define vdes_keyerror       _P_VDES->p_keyerror
#define vdes_chk_key        _P_VDES->p_chk_key
#define vdes_set_odd_parity _P_VDES->p_set_odd_parity
#define vdes_gen_key        _P_VDES->p_gen_key
#define vdes_ecb            _P_VDES->p_ecb
#define vdes_cbc            _P_VDES->p_cbc
#define vdes_cfb1           _P_VDES->p_cfb1
#define vdes                _P_VDES->p_vdes
#define vdes_iso_hash       _P_VDES->p_iso_hash
#define vdes_mac            _P_VDES->p_mac
#define vdes_cbc_rmac       _P_VDES->p_cbc_rmac
#define vdes_cfb_rmac       _P_VDES->p_cfb_rmac
#define vdes_cbc_pad        _P_VDES->p_cbc_pad
#define vdes_cbc_xpad       _P_VDES->p_vdes_cbc_xpad
#define vdes_padding_length _P_VDES->p_vdes_padding_length
#define vdes_unpad          _P_VDES->p_vdes_unpad

#endif /* _VDES_C_INT_ */


/*******************************************************************************
 * vdes_calc_pad_len - calculate length of the resulting encrypted byte stream
 ******************************************************************************/
static INLINE int vdes_calc_pad_len(unsigned int padding, unsigned int len)
{
  if(padding <= 0xff)
    return((len % 8) ? (len + 8 - (len % 8)) : len);
  else
    return((len % 8) ? (len + 8 - (len % 8)) : len + 8);
}


/* Error Codes:  (0xB0000000 | (VDES_MDL_ID << 16) | (errno))  */

/* --- BEGIN ERROR CODES --- */
#define E_VDES                          0xB081          // CryptoServer module VDES
#define E_VDES_DATA_LEN                 0xB0810001      // length of data is not a multiple of 8 bytes
#define E_VDES_KEY_LEN                  0xB0810002      // length of key is not 8, 16, or 24
#define E_VDES_MEM                      0xB0810003      // cannot allocate memory
#define E_VDES_WEAK                     0xB0810004      // key is weak
#define E_VDES_SEMI_WEAK                0xB0810005      // key is semi-weak
#define E_VDES_SHORT_KEY                0xB0810006      // two of the 8byte key parts are identical
#define E_VDES_MODE                     0xB0810007      // mode is unknown
#define E_VDES_READ_MASTER_KEY          0xB0810008      // could not get local Master Key
#define E_VDES_PAD_TYPE                 0xB0810009      // unknown padding mechanism
#define E_VDES_PAD                      0xB081000A      // invalid padding
#define E_VDES_PARAM                    0xB081000B      // invalid parameter
#define E_VDES_POSSIBLY_WEAK            0xB081000C      // key is possibly weak
//Now FIPS in in CXI implemented #define E_VDES_KEY_LEN_FIPS           0xB081000D      // ERASED
#define E_VDES_ZERO_LENGTH              0xB081000E      // Zero length not allowed

/* --- END ERROR CODES --- */


/**************************************************************************************************
 * Macros to simplify treatment of DES keys used only once
 **************************************************************************************************/

#define vdes_1ecb( kl, k, m, l, din, dout ) \
    vdes_ecb( vdes_pkey( kl, k, vdes_p_global_key ), m, l, din, dout )

#define vdes_1cbc( kl, k, m, iv_in, l, din, dout, iv_out ) \
    vdes_cbc( vdes_pkey( kl, k, vdes_p_global_key ), m, iv_in, l, din, dout, iv_out )

#define vdes_1cfb1( kl, k, m, iv_in, l, din, dout, iv_out ) \
    vdes_cfb1( vdes_pkey( kl, k, vdes_p_global_key ), m, iv_in, l, din, dout, iv_out )

#define vdes_1( kl, k, m, iv_in, l, din, dout, iv_out ) \
    vdes( vdes_pkey( kl, k, vdes_p_global_key ), m, iv_in, l, din, dout, iv_out )

#define vdes_1mac( kl, k, l, din, pad, iv_in, mac ) \
    vdes_mac( vdes_pkey( kl, k, vdes_p_global_key ), l, din, pad, iv_in, mac )

#define vdes_1cbc_rmac( kl, k, l, din, pad, iv_in, mac ) \
    vdes_cbc_rmac( vdes_pkey( kl, k, vdes_p_global_key ), l, din, pad, iv_in, mac )

#define vdes_1cfb_rmac( kl, k, l, din, pad, iv_in, mac ) \
    vdes_cfb_rmac( vdes_pkey( kl, k, vdes_p_global_key ), l, din, pad, iv_in, mac )

#define vdes_1cbc_pad( kl, k, m, iv_in, l, din, pad, dout ) \
    vdes_cbc_pad( vdes_pkey( kl, k, vdes_p_global_key ), m, iv_in, l, din, pad, dout )

#define vdes_1cbc_xpad( kl, k, m, iv_in, l, din, pad, dout ) \
      vdes_cbc_xpad( vdes_pkey( kl, k, vdes_p_global_key ), m, pad, iv_in, l, din, dout )

/* --- END MAKROS --- */


#endif /* __VDES_H_PUB_INCLUDED__ */

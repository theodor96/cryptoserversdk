/*****************************************************************************
 *
 *  $File Identification                    $
 *  $Filename          : aes.h              $
 *  $Module version    : x.x.x.x            $
 *  $Module name       : AES                $
 *  $Release Date      : DD.MM.YYYY         $
 *
 *  Author      : Dipl.Inf.(FH) Ralf Vennemann
 *                Emilio Pastor Mira
 *                Utimaco IS GmbH
 *****************************************************************************/

#ifndef __AES_H_PUB_INCLUDED__
  #define __AES_H_PUB_INCLUDED__

#include "os_mdl.h"
#include "os_mem.h"

#include "stype.h"



/* module identification: */

#define AES_MDL_ID          0x8B            /* ID of the module          */
#define AES_MDL_NAME        "AES"          /* Short name of the module  */

#ifdef CS2_SDK
  #define AES_MDL_NAMEX     "AES Module SDK"      /* Long name of the module   */
#else
  #ifdef DEBUG
    #define AES_MDL_NAMEX   "AES Module DEBUG"      /* Long name of the module   */
  #else
    #define AES_MDL_NAMEX   "AES Module"          /* Long name of the module   */
  #endif
#endif

#define AES_MDL_VERSION   0x01040200           /* Version of the module     */


/* public interface: */


// definitions for mode parameter
//*******************//
//Version 1.1.0
#define AES_CMAC_AD           ((int) 0x00100000) // 1     // CM hash of the associated data
#define AES_CMAC_DATA         ((int) 0x00200000) // 2     // CM hash of the data
#define AES_CMAC_END          ((int) 0x00400000) // 4     // Last call of the function to compute the final authentication Tag
#define AES_CMAC_ADDATA       ((int) 0x00300000) // 3     // CM hash of the associated data and the data
#define AES_CMAC_ADEND        ((int) 0x00500000) // 5     // CM hash of the associated data and computation the final authentication tag
#define AES_CMAC_DATAEND      ((int) 0x00600000) // 6     // CM hash of the data and computation of the final authentication tag
#define AES_CMAC_ALL          ((int) 0x00700000) // 7     // All the data is delivered, compuatation of the authentication tag
#define AES_CMAC_MASK         ((int) 0x00F00000) //the nibble used for the different use of Counter Mode Hash
//#define AES_GMAC
#define AES_NOENC             ((int) 0x00000000) // 0o     // encryption


//*******************//
#define AES_ENC               ((int) 0x00020000) // 2     // encryption
#define AES_DEC               ((int) 0x00040000) // 4     // decryption
#define AES_CRYPT_MASK        ((int) 0x000F0000) // the nibble used for de-/encryption mode
#define AES_ECB               ((int) 0x00002000) // 2     // ECB  mode
#define AES_CBC               ((int) 0x00004000) // 4     // CBC  mode
#define AES_CFB1              ((int) 0x00006000) // 6     // CFB1 mode
#define AES_OFB               ((int) 0x00008000) // 8     // OFB  mode
#define AES_MODE_MASK         ((int) 0x0000F000) // the nibble used for the different AES-modes


#define AES_MAX_ROUNDS  14    // maximum rounds for 256 bit keys
#define AES_BLOCK_SIZE  16    // block size used for each de-/encryption round
#define DIV_BY_BLOCK_SIZE(x)  (x >> 4)   // x / 16   ATTENTION!  AES_BLOCK_SIZE has to be 16 !!!
#define MOD_BY_BLOCK_SIZE(x)  (x & 0x0f) // x % 16   ATTENTION!  AES_BLOCK_SIZE has to be 16 !!!


// padding mechanisms
#define AES_PAD_PKCS           0x100
#define AES_PAD_ISO7816        0x200
#define AES_PAD_ISO10126       0x300


// flags for aes_gen_key
#define AES_USE_REAL_RND      0       // use read random number generator for key generation
#define AES_USE_PSEUDO_RND    0x100   // use pseudo random number generator for key generation

// defines for AES key wrap 
#define AES_KEYWRAP_BLOCK_SIZE 8
#define AES_KEYWRAP_ICV_LEN 8
#define AES_KEYWRAP_PAD_ICV_LEN 4

typedef struct
{
    int    flags;                               // type of key, mode, number of rounds
    int    error;
    unsigned int  rd_key[4 * (AES_MAX_ROUNDS + 1)];
} AES_KEY;



typedef struct 
{ 
	unsigned char counter0[AES_BLOCK_SIZE]; 
    unsigned char block[AES_BLOCK_SIZE]; 
	unsigned int  totad_len;
	unsigned int  totdata_len;
	unsigned int  counter_ad;
	unsigned int  counter_data;
    unsigned char tag_len;
	unsigned char res_used;
    unsigned char checksize_for_version;

}T_aes_ccm_state;
#define SIZE_AD_STATE_T sizeof(T_aes_ccm_state)

extern MDL_GLOBAL unsigned char *p_global_sec_mem;


typedef struct
{
    void   *p_data;
    int    (*p_start)(T_OS_MDL_HDL p_smos,void *dumy,void *p_coff_mem);    // T_OS_MDL_HDL, void*, void*);
    int    (*p_stop)(void);
    int    (*p_pre_replace)(void);
    int    (*p_pre_delete)(void);
    void   *p_dumy;
    const void   *p_module_info;

    AES_KEY **p_global_key;

    int (*p_mkkey)        ( int keylen, unsigned char* p_key, int mode, AES_KEY* p_key_buff, AES_KEY** pp_key_buff );
    AES_KEY* (*p_pkey)    ( int keylen, unsigned char* p_key, int mode, AES_KEY* p_key_buff );
    int (*p_free)         ( AES_KEY* p_key_buff );
    int (*p_keyerror)     ( AES_KEY* p_key_buff );
    int (*p_gen_key )     ( int keylen, unsigned char* p_key );
    int (*p_ecb)          ( AES_KEY* p_key_buff, int mode, unsigned int len, unsigned char* p_data_in, unsigned char* p_data_out );
    int (*p_cbc)          ( AES_KEY* p_key_buff, int mode, unsigned char* p_iv_in, unsigned int len, unsigned char* p_data_in,
                             unsigned char* p_data_out, unsigned char* p_iv_out );
    int (*p_cbc_pad)      ( AES_KEY* p_key_buff, int mode, unsigned char* p_iv_in, unsigned int len, unsigned char* p_data_in,
                             unsigned char pad, unsigned char* p_data_out );
    int (*p_cfb1)         ( AES_KEY*      p_key_buff, int mode, unsigned char* p_iv_in, unsigned int len, unsigned char* p_data_in,
                             unsigned char* p_data_out, unsigned char* p_iv_out );
    int (*p_aes)          ( AES_KEY* p_key_buff, int mode, unsigned char* p_iv_in, unsigned int len, unsigned char* p_data_in,
                             unsigned char* p_data_out, unsigned char* p_iv_out );
    int (*p_mac)          ( AES_KEY* p_key_buff, unsigned int len, unsigned char* p_data, unsigned char pad_value,
                             unsigned char* p_iv, unsigned char* p_mac );
    int (*p_aes_cbc_xpad) ( AES_KEY *p_key_buff, int mode, unsigned int padding, unsigned char *p_iv_in,
                             unsigned int len, unsigned char *p_data_in, unsigned char *p_data_out);
    int (*p_aes_padding_length) (unsigned int padding, unsigned int l_data, unsigned char *p_data, unsigned int *p_l_pad);
    int (*p_aes_unpad)    ( unsigned int padding, unsigned int *p_l_data, unsigned char *p_data);

    AES_KEY **p_os_mkv_enc;
    AES_KEY **p_os_mkv_dec;
    int (*p_cmac)         ( AES_KEY* p_key_buff, unsigned int len, unsigned char* p_data, unsigned char* p_mac );
    
	//COUNTER Modes included in v1.1.0   
    // DEPRECATED aes_gcm and aes_gcm_prepare_j0
	int (*p_aes_gcm)(int mode, unsigned char *p_in_buff, unsigned char *p_out_buff, unsigned char *p_ad, unsigned char *p_j0, AES_KEY *p_key_buff, unsigned char *p_tag, unsigned char *p_j0_out, unsigned int data_len, unsigned int ad_len);
	int (*p_aes_gcm_prepare_j0)(unsigned char *p_j0, unsigned char *p_iv, AES_KEY *p_key_buff, unsigned int iv_len);

    //COUNTER Modes included in v1.2.0           
    int (*p_aes_cmac_ex)( AES_KEY* p_key_buff, unsigned int mode, unsigned int len, unsigned char* p_data, unsigned char* p_mac);
    int (*p_aes_ofb     )( AES_KEY* p_key_buff, unsigned int mode,unsigned char *p_iv_in, unsigned int len, unsigned char *p_data_in, unsigned char *p_data_out, unsigned char *p_iv_out);
  
    //COUNTER Mode CCM included in v1.2.4       
    // DEPRECATED aes_ccm and aes_ccm_init      
    int (*p_aes_ccm)(int mode, unsigned char *p_in_buff, unsigned char *p_out_buff, unsigned char *p_ad, AES_KEY  *p_key_buff, unsigned char *p_tag,	unsigned int buff_len, unsigned int ad_len, T_aes_ccm_state *p_ccm_state);
    int (*p_aes_ccm_init)(unsigned char *p_iv, unsigned char *p_tag, AES_KEY *p_key_buff, unsigned int iv_len, unsigned int data_len, unsigned int ad_len, unsigned int tag_len, T_aes_ccm_state *p_ccm_state);

    //moved from CXI in v1.3.8
    int (*p_aes_ctr)(AES_KEY *p_key_buff, unsigned int mode, unsigned int cbits, const unsigned char *p_iv_in, unsigned int len, const unsigned char *p_data_in, unsigned char *p_data_out, unsigned char *p_iv_out);

    // new CCM and GCM interface in V1.4.0
    int (*p_aes_ccm_init_sl)(AES_KEY *p_key_buf, unsigned int l_nonce, unsigned int l_ad, unsigned int l_data, unsigned int l_tag, unsigned char *p_ctr, unsigned char *p_hash, unsigned int  *pl_first_ad);
    int (*p_aes_ccm_ad)(AES_KEY *p_key_buf, unsigned int l_total_ad, unsigned int l_ad, const unsigned char *p_ad, unsigned char *p_hash);
    int (*p_aes_ccm_data)(AES_KEY *p_key_buf, int mode, unsigned int l_data, const unsigned char *p_data_in, unsigned char *p_ctr, unsigned char *p_hash, unsigned char *p_data_out);
    int (*p_aes_ccm_final)(AES_KEY *p_key_buf, int mode, unsigned char *p_ctr, unsigned char *p_hash, unsigned int l_tag, unsigned char *p_tag);
    int (*p_aes_gcm_init)(AES_KEY *p_key_buf, unsigned int l_iv, unsigned char *p_iv, unsigned char *p_ctr);
    int (*p_aes_gcm_ad)(AES_KEY *p_key_buf, unsigned int l_ad, const unsigned char *p_ad, unsigned char *p_hash);
    int (*p_aes_gcm_data)(AES_KEY *p_key_buf, int mode, unsigned int l_data, const unsigned char *p_data_in, unsigned char *p_ctr, unsigned char *p_hash, unsigned char *p_data_out);
    int (*p_aes_gcm_final)(AES_KEY *p_key_buf, int mode, unsigned int l_ad, unsigned int l_data, unsigned char *p_init_ctr, unsigned char *p_hash, unsigned int l_tag, unsigned char *p_tag);
    int (*p_aes_key_wrap)(const AES_KEY *p_kek, int mode, const unsigned char *p_data_in, unsigned int data_in_len,  unsigned char *p_data_out, unsigned int *p_data_out_len, const unsigned char *p_icv, unsigned int icv_len);
    int (*p_aes_key_wrap_pad)(const AES_KEY *p_kek, int mode, const unsigned char *p_data_in, unsigned int data_in_len,  unsigned char *p_data_out, unsigned int *p_data_out_len, const unsigned char *p_icv, unsigned int icv_len);
} T_AES_TABLE_PUB;



#ifdef _AES_C_INT_
/* function prototypes used by the module (internal) */
void INLINE inc_function(unsigned char *inc);

int  aes_start(T_OS_MDL_HDL,void *,void *);
int  aes_stop(void);
int  aes_pre_replace(void);
int  aes_pre_delete(void);

int aes_mkkey( int keylen, unsigned char* p_key, int mode, AES_KEY* p_key_buff, AES_KEY** pp_key_buff );
AES_KEY* aes_pkey( int keylen, unsigned char* p_key, int mode, AES_KEY* p_key_buff );
int aes_free ( AES_KEY* p_key_buff );
int aes_keyerror( AES_KEY* p_key_buff );
int aes_gen_key( int keylen, unsigned char* p_key );
int aes_ecb( AES_KEY* p_key_buff, int mode, unsigned int len, unsigned char* p_data_in, unsigned char* p_data_out );
int aes_cbc( AES_KEY* p_key_buff, int mode, unsigned char* p_iv_in, unsigned int len, unsigned char* p_data_in,
              unsigned char* p_data_out, unsigned char* p_iv_out );
int aes_cbc_pad( AES_KEY* p_key_buff, int mode, unsigned char* p_iv_in, unsigned int len, unsigned char* p_data_in,
              unsigned char pad, unsigned char* p_data_out );
int aes_cfb1( AES_KEY*      p_key_buff, int mode, unsigned char* p_iv_in, unsigned int len, unsigned char* p_data_in,
               unsigned char* p_data_out, unsigned char* p_iv_out );
int aes( AES_KEY* p_key_buff, int mode, unsigned char* p_iv_in, unsigned int len, unsigned char* p_data_in,
          unsigned char* p_data_out, unsigned char* p_iv_out );
int aes_mac( AES_KEY* p_key_buff, unsigned int len, unsigned char* p_data, unsigned char pad_value,
              unsigned char*  p_iv, unsigned char* p_mac );
int aes_cbc_xpad       (AES_KEY *p_key_buff, int mode, unsigned int padding, unsigned char *p_iv_in,
                         unsigned int len, unsigned char *p_data_in, unsigned char *p_data_out);
int aes_padding_length (unsigned int padding, unsigned int l_data,
                         unsigned char *p_data, unsigned int *p_l_pad);
int aes_unpad          (unsigned int padding, unsigned int *p_l_data, unsigned char *p_data);
int aes_cmac( AES_KEY* p_key_buff, unsigned int len, unsigned char* p_data, unsigned char* p_mac );

//V1.1.0
// deprecated functions "aes_gcm" and "aes_gcm_prepare_j0" are removed 

//V1.2.0
int aes_cmac_ex( AES_KEY* p_key_buff, unsigned int mode, unsigned int len, unsigned char* p_data, unsigned char* p_mac);
int aes_ofb     ( AES_KEY* p_key_buff, unsigned int mode,unsigned char *p_iv_in, unsigned int len, unsigned char *p_data_in, unsigned char *p_data_out, unsigned char *p_iv_out);

//COUNTER Mode CCM included in v1.3.4.0           
// deprecated functions "aes_ccm" and "aes_ccm_init" are removed

//V1.3.8.0 - moved from CXI
int aes_ctr(AES_KEY *p_key_buff, unsigned int mode, unsigned int cbits, const unsigned char *p_iv_in, unsigned int len, const unsigned char *p_data_in, unsigned char *p_data_out, unsigned char *p_iv_out);

//V1.4.0.0
int aes_ccm_init_sl(AES_KEY *p_key_buf, unsigned int l_nonce, unsigned int l_ad, unsigned int l_data, unsigned int l_tag, unsigned char *p_ctr, unsigned char *p_hash, unsigned int  *pl_first_ad);
int aes_ccm_ad(AES_KEY *p_key_buf, unsigned int l_total_ad, unsigned int l_ad, const unsigned char *p_ad, unsigned char *p_hash);
int aes_ccm_data(AES_KEY *p_key_buf, int mode, unsigned int l_data, const unsigned char *p_data_in, unsigned char *p_ctr, unsigned char *p_hash, unsigned char *p_data_out);
int aes_ccm_final(AES_KEY *p_key_buf, int mode, unsigned char *p_ctr, unsigned char *p_hash, unsigned int l_tag, unsigned char *p_tag);
int aes_gcm_init(AES_KEY *p_key_buf, unsigned int l_iv, unsigned char *p_iv, unsigned char *p_ctr);
int aes_gcm_ad(AES_KEY *p_key_buf, unsigned int l_ad, const unsigned char *p_ad, unsigned char *p_hash);
int aes_gcm_data(AES_KEY *p_key_buf, int mode, unsigned int l_data, const unsigned char *p_data_in, unsigned char *p_ctr, unsigned char *p_hash, unsigned char *p_data_out);
int aes_gcm_final(AES_KEY *p_key_buf, int mode, unsigned int l_ad, unsigned int l_data, unsigned char *p_init_ctr, unsigned char *p_hash, unsigned int l_tag, unsigned char *p_tag);

// AES KW / KWP
int aes_key_wrap(const AES_KEY *p_kek, int mode, const unsigned char *p_data_in, unsigned int data_in_len,  unsigned char *p_data_out, unsigned int *p_data_out_len, const unsigned char *p_icv, unsigned int icv_len);
int aes_key_wrap_pad(const AES_KEY *p_kek, int mode, const unsigned char *p_data_in, unsigned int data_in_len,  unsigned char *p_data_out, unsigned int *p_data_out_len, const unsigned char *p_icv, unsigned int icv_len);
#else

/* external interface to be used by other modules */

extern MDL_GLOBAL T_OS_MDL_HDL P_AES;

#define _P_AES ((T_AES_TABLE_PUB *)P_AES)         /* shortcut */

#define P_aes_data         (_P_AES->_p_data);

#define aes_start          _P_AES->p_start
#define aes_stop           _P_AES->p_stop
#define aes_pre_replace    _P_AES->p_pre_replace
#define aes_pre_delete     _P_AES->p_pre_delete

#define aes_p_global_key   (*(_P_AES->p_global_key))
#define aes_p_os_mkv_enc   (*(_P_AES->p_os_mkv_enc))
#define aes_p_os_mkv_dec   (*(_P_AES->p_os_mkv_dec))

#define aes_mkkey          _P_AES->p_mkkey
#define aes_pkey           _P_AES->p_pkey
#define aes_free           _P_AES->p_free
#define aes_keyerror       _P_AES->p_keyerror
#define aes_gen_key        _P_AES->p_gen_key
#define aes_ecb            _P_AES->p_ecb
#define aes_cbc            _P_AES->p_cbc
#define aes_cbc_pad        _P_AES->p_cbc_pad
#define aes_cfb1           _P_AES->p_cfb1
#define aes                _P_AES->p_aes
#define aes_mac            _P_AES->p_mac
#define aes_cbc_xpad       _P_AES->p_aes_cbc_xpad
#define aes_padding_length _P_AES->p_aes_padding_length
#define aes_unpad          _P_AES->p_aes_unpad
#define aes_cmac           _P_AES->p_cmac
//Version 1.1.0
// deprecated functions "aes_gcm" and "aes_gcm_prepare_j0" are removed

//Version 1.2.0
#define aes_cmac_ex        _P_AES->p_aes_cmac_ex
#define aes_ofb            _P_AES->p_aes_ofb

//Version 1.3.4
// deprecated functions "aes_ccm" and "aes_ccm_init" are removed

//Version 1.3.8
#define aes_ctr            _P_AES->p_aes_ctr

//Version 1.4.0
#define aes_ccm_init_sl    _P_AES->p_aes_ccm_init_sl
#define aes_ccm_ad         _P_AES->p_aes_ccm_ad
#define aes_ccm_data       _P_AES->p_aes_ccm_data
#define aes_ccm_final      _P_AES->p_aes_ccm_final
#define aes_gcm_init       _P_AES->p_aes_gcm_init   
#define aes_gcm_ad         _P_AES->p_aes_gcm_ad
#define aes_gcm_data       _P_AES->p_aes_gcm_data
#define aes_gcm_final      _P_AES->p_aes_gcm_final

// KW / KWP
#define aes_key_wrap       _P_AES->p_aes_key_wrap
#define aes_key_wrap_pad   _P_AES->p_aes_key_wrap_pad

#endif /* _AES_C_INT_ */

/*******************************************************************************
 * aes_calc_pad_len - calculate length of the resulting encrypted byte stream
 ******************************************************************************/
static INLINE int aes_calc_pad_len(unsigned int padding, unsigned int len)
{
  if(padding <= 0xff)
    return((len % 16) ? (len + 16 - (len % 16)) : len);
  else
    return((len % 16) ? (len + 16 - (len % 16)) : len + 16);
}



/* Error Codes:  (0xB0000000 | (AES_MDL_ID << 16) | (errno))  */

/* --- BEGIN ERROR CODES --- */
#define E_AES                          0xB08B          // CryptoServer module AES
#define E_AES_DATA_LEN                 0xB08B0001      // length of data is not a multiple of 16 bytes
#define E_AES_KEY_LEN                  0xB08B0002      // length of key is not 16, 24, or 32
#define E_AES_MEM                      0xB08B0003      // cannot allocate memory
#define E_AES_MODE                     0xB08B0004      // mode is unknown
#define E_AES_CFB1_DEC_MODE            0xB08B0005      // For cfb1 decryption the key must always prepared for encryption
#define E_AES_PAD_TYPE                 0xB08B0006      // unknown padding mechanism
#define E_AES_PAD                      0xB08B0007      // invalid padding
#define E_AES_PARAM                    0xB08B0008      // invalid parameter
#define E_AES_READ_MASTER_KEY          0xB08B0009      // could not get local Master Key
#define E_AES_MODE_MISMATCH            0xB08B000A      // mode of prepared key does not match mode parameter
// FIPS is now in CXI implemented  #define E_AES_FIPS_MODE_NA             0xB08B000B      // the execution of this function in fips mode is not allowed
#define E_AES_ZERO_LEN                 0xB08B000C      // Zero data length is not allowed
#define E_AES_CTR_OVERFLOW             0xB08B000D      // Overflow of block counter in CTR chaining mode
#define E_AES_TAG_VERIFICATION         0xB08B000E      // Tag verification on CCM/GCM decrypt failed
#define E_AES_KEYWRAP                  0xB08B000F      // Verification AES keywrap/-unwrap failed

/* --- END ERROR CODES --- */


/**************************************************************************************************
 * Macros to simplify treatment of AES keys used only once
 **************************************************************************************************/

#define aes_1ecb( kl, k, m, l, din, dout ) \
    aes_ecb( aes_pkey( kl, k, m, aes_p_global_key ), m, l, din, dout )
 
#define aes_1cbc( kl, k, m, iv_in, l, din, dout, iv_out ) \
    aes_cbc( aes_pkey( kl, k, m, aes_p_global_key ), m, iv_in, l, din, dout, iv_out )

#define aes_1cbc_pad( kl, k, m, iv_in, l, din, pad, dout) \
    aes_cbc_pad( aes_pkey( kl, k, m, aes_p_global_key ), m, iv_in, l, din, pad, dout)

#define aes_1cbc_xpad( kl, k, m, pad, iv_in, l, din, dout) \
    aes_cbc_xpad( aes_pkey( kl, k, m, aes_p_global_key ), m, pad, iv_in, l, din, dout)
    
// for CFB1 and OFB always use AES_ENC to prepare the key
#define aes_1( kl, k, m, iv_in, l, din, dout, iv_out ) \
    aes( aes_pkey( kl, k, ((m & AES_MODE_MASK) == AES_CFB1 || (m & AES_MODE_MASK) == AES_OFB) ? AES_ENC : m, aes_p_global_key ), m, iv_in, l, din, dout, iv_out )

#define aes_1cfb1( kl, k, m, iv_in, l, din, dout, iv_out ) \
    aes_cfb1( aes_pkey( kl, k, AES_ENC, aes_p_global_key ), m, iv_in, l, din, dout, iv_out )

#define aes_1mac( kl, k, l, din, pad, iv_in, mac ) \
    aes_mac( aes_pkey( kl, k, AES_ENC, aes_p_global_key ), l, din, pad, iv_in, mac )

#define aes_1cmac( kl, k, l, din, mac ) \
    aes_cmac( aes_pkey( kl, k, AES_ENC, aes_p_global_key ), l, din, mac )

////Version 1.1.0

//Version 1.2.0
#define aes_1cmac_ex( kl, k, l, din, mac, flag ) \
    aes_cmac_ex( aes_pkey( kl, k, AES_ENC, aes_p_global_key ), flag, l, din, mac )

#define aes_1ofb( kl, k, m, iv_in, l, din, dout, iv_out ) \
    aes_ofb( aes_pkey( kl, k, AES_ENC, aes_p_global_key ), m, iv_in, l, din, dout, iv_out )

//Version 1.3.8
#define aes_1ctr( kl, k, m, cbits, iv_in, l, din, dout, iv_out ) \
    aes_ctr( aes_pkey( kl, k, AES_ENC, aes_p_global_key ), m, cbits, iv_in, l, din, dout, iv_out )


/* --- END MAKROS --- */


#endif /* __AES_H_PUB_INCLUDED__ */

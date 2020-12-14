/**************************************************************************************************
 *
 *  Description : Cryptographic Functions
 *                Public header file
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 **************************************************************************************************/
#ifndef __OS_CRYPT_PUB_INCLUDED__
#define __OS_CRYPT_PUB_INCLUDED__

#include "os.h"

/* --- BEGIN ERROR CODES --- */

#define E_OS_CRYPT                         0xB00013    // CRYPT section

#define E_OS_CRYPT_MEM_ALLOC               0xB0001301  // Error during memory allocation
#define E_OS_CRYPT_PARA_INVALID            0xB0001302  // Invalid input parameter
#define E_OS_CRYPT_MK_READ                 0xB0001303  // Error reading master key
#define E_OS_CRYPT_NO_MK                   0xB0001304  // no internal access to CS2 master key
#define E_OS_CRYPT_MK_CORR                 0xB0001305  // CS2 master key corrupted
#define E_OS_CRYPT_MK_WRITE                0xB0001306  // Error updating master key
#define E_OS_CRYPT_NOT_SUPP                0xB0001307  // Function not supported
#define E_OS_CRYPT_RND_FAIL                0xB0001308  // Random number generator failed
#define E_OS_CRYPT_SHA512_KAT              0xB0001309  // SHA-512 Known Answer Test failed

#define E_OS_CRYPT_RND_TMOUT               0xB0001310  // Random number generator timeout
#define E_OS_CRYPT_RND_KAT                 0xB0001311  // Known answer test failed
#define E_OS_CRYPT_RND_INIT                0xB0001312  // Random Number Generator is not initialized
#define E_OS_CRYPT_RND_SEC_STRENGTH        0xB0001313  // Given security strength not supported
#define E_OS_CRYPT_RND_REQ                 0xB0001314  // Max number of requested randombits per call exceeded
#define E_OS_CRYPT_RND_PRED_RESISTANCE     0xB0001315  // Prediction resistance not supported for current handle
#define E_OS_CRYPT_RND_RESEED              0xB0001316  // Random Number Generator needs to be reseeded

/* --- END ERROR CODES --- */


/******************************************************************************
 *
 * Definitions
 *
 ******************************************************************************/
#if defined(_TMS320C6400) || defined(CS2_SDK)
  #define OS_CRYPT_MK_LB  32
#else
  #define OS_CRYPT_MK_LB  24
#endif

#define OS_CRYPT_DES_ENCRYPT       ((int) 0x00020010) // select single DES encryption
#define OS_CRYPT_DES_DECRYPT       ((int) 0xFFFE0010) // select single DES decryption

#define OS_CRYPT_DES_ENCRYPT3      ((int) 0x00020030) // select tripple DES encryption
#define OS_CRYPT_DES_DECRYPT3      ((int) 0xFFFE0030) // select tripple DES decryption

typedef struct
{
  unsigned int   len;
  unsigned char  *p_data;
}
OS_CRYPT_DATA_CHUNK;

#if defined(_TMS320C6400) || defined(CS2_SDK)

#define SHA_LBLOCK  16
#define SHA512_CBLOCK (SHA_LBLOCK*8)  // SHA-512 treats input data as a contiguous array of 64 bit wide big-endian values.

#ifdef OSYS_win
  typedef unsigned __int64   u64;
#else
  typedef unsigned long long u64;
#endif

typedef struct
{
  u64        h[8];
  u64        Nl,Nh;
  union {
    u64           d[SHA_LBLOCK];
    unsigned char p[SHA512_CBLOCK];
  }
  u;
  unsigned int num,md_len;
}
SHA512_CTX;

#define DRBG_REAL    0 // flag for use of real-hdl
#define DRBG_PSEUDO  1 // flag for use of pseudo hdl

#endif

/******************************************************************************
 *
 * Type definitions
 *
 ******************************************************************************/
typedef struct _os_crypt_public_interface
{
  int             (*_p_os_crypt_mkv_get) (const unsigned char*, unsigned int, unsigned char**);
  unsigned int *  (*_p_os_crypt_des_sbox_get) (void);
  int             (*_p_os_crypt_sha1)(unsigned int,OS_CRYPT_DATA_CHUNK *,unsigned char *);
  int             (*_p_os_crypt_rsa)(unsigned int,const unsigned char *,unsigned int,
                                     const unsigned char *,unsigned int,const unsigned char *,
                                     unsigned int,unsigned char *,unsigned int *);
  void            (*_p_os_crypt_des)(unsigned char *,unsigned char *,unsigned int *,const unsigned int *,int);
  void            (*_p_os_crypt_des_key_gen)(unsigned char *,unsigned int *,int);
  int             (*_p_os_crypt_dumy)(unsigned char *);
  void            (*_p_os_crypt_sha1_core)(unsigned char *p_data, unsigned char *p_iv, unsigned char *p_hash);
#if defined(_TMS320C6400) || defined(CS2_SDK)
  int             (*_p_os_crypt_sha512)(int mode, unsigned int len, unsigned char *p_data,
                                        SHA512_CTX *p_info, unsigned char *p_hash);
  int             (*_p_os_crypt_cipher512)(unsigned int,unsigned char *,int,unsigned int,
                                           unsigned char *,unsigned int,unsigned char *,unsigned char *);
  int             (*_p_os_crypt_real_rnd)(unsigned char *p_rnd, unsigned int len);
  int             (*_p_os_crypt_drbg_rnd)(unsigned int flag, unsigned char *p_rnd, unsigned int len);
  int             (*_p_os_crypt_drbg_reseed)(unsigned int flag);

  // functions for FIPS algorithm test (DEBUG version of SMOS only)
  int             (*_p_os_crypt_drbg_hash_generate)(unsigned int flag, unsigned int  n_req,
                                                    unsigned int  l_add_in, unsigned char *p_add_in,
                                                    unsigned char *p_out);

  int             (*_p_os_crypt_drbg_hash_instantiate)(unsigned int flag, unsigned int l_entr, unsigned char *p_entr,
                                                       unsigned int l_nonce, unsigned char *p_nonce,
                                                       unsigned int  l_pers, unsigned char *p_pers);

  int             (*_p_os_crypt_drbg_hash_reseed)(unsigned int flag, unsigned int  l_entr, unsigned char *p_entr,
                                                  unsigned int  l_add_in, unsigned char *p_add_in);
#endif
  // new as of SMOS 5.6.1.0
  int             (*_p_os_crypt_drbg_reseed_2ndentropy)(unsigned int flag, unsigned int len, const void *p_2ndentropy);
}
T_OS_CRYPT_TABLE_PUB;

#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

  /*** C-style linking of the modules ***********************************************************
   * This section contains the C-style function prototypes. It is active when the modules are
   * linked together using the linker or a shared library (i.e., in the SDK). It is also used
   * for the module itself.
   **********************************************************************************************/
  extern int          os_crypt_mkv_get      (const unsigned char*, unsigned int, unsigned char**);
  extern unsigned int *os_crypt_des_sbox_get (void);
  extern int          os_crypt_sha1         (unsigned int,OS_CRYPT_DATA_CHUNK *,unsigned char *);
  extern int          os_crypt_rsa(unsigned int,const unsigned char *,unsigned int,const unsigned char *,
                                   unsigned int,const unsigned char *,unsigned int,unsigned char *,
                                   unsigned int *);
  extern void         os_crypt_des(unsigned char *,unsigned char *,unsigned int *,const unsigned int *,int);
  extern void         os_crypt_des_key_gen(unsigned char *,unsigned int *,int);

  extern int          os_crypt_mk_swap_read(unsigned char *);
  extern int          os_crypt_dumy(unsigned char *);
  extern void         os_hash_sha160_blk_proc(unsigned char *,unsigned char *,unsigned char *);
  extern int          os_crypt_init(void);
#if defined(_TMS320C6400) || defined(CS2_SDK)
  extern int          os_crypt_sha512_kat(void);
  extern int          os_crypt_sha512(int, unsigned int, unsigned char *, SHA512_CTX *, unsigned char *);
  extern int          os_crypt_cipher512(unsigned int,unsigned char *,int,unsigned int,
                                         unsigned char *,unsigned int,unsigned char *,unsigned char *);
  extern int          os_crypt_real_rnd(unsigned char *p_rnd, unsigned int len);

  extern int          os_crypt_drbg_hash_generate(unsigned int flag, unsigned int  n_req,
                                                  unsigned int  l_add_in, unsigned char *p_add_in,
                                                  unsigned char *p_out);

  extern int          os_crypt_drbg_hash_instantiate(unsigned int flag, unsigned int l_entr, unsigned char *p_entr,
                                                     unsigned int l_nonce, unsigned char *p_nonce,
                                                     unsigned int  l_pers, unsigned char *p_pers);

  extern int          os_crypt_drbg_hash_reseed(unsigned int flag, unsigned int  l_entr, unsigned char *p_entr,
                                                unsigned int  l_add_in, unsigned char *p_add_in);
#endif
  // new as of SMOS 5.6.1.0
  extern int          os_crypt_drbg_reseed_2ndentropy(unsigned int flag, unsigned int len, const void *p_2ndentropy);

#else
  /*** smos linking of the modules **************************************************************
   * This section is active when dynamic loading/linking of the modules using the Module Loader
   * is in effect.
   **********************************************************************************************/

  /************************************************************************************************
   * macros to use the public interface and global data of key server module
   ************************************************************************************************/
  #define _P_OS_CRYPT  ((T_OS_CRYPT_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_crypt))

  #define os_crypt_mkv_get                _P_OS_CRYPT->_p_os_crypt_mkv_get
  #define os_crypt_des_sbox_get           _P_OS_CRYPT->_p_os_crypt_des_sbox_get
  #define os_crypt_sha1                   _P_OS_CRYPT->_p_os_crypt_sha1
  #define os_crypt_rsa                    _P_OS_CRYPT->_p_os_crypt_rsa
  #define os_crypt_des                    _P_OS_CRYPT->_p_os_crypt_des
  #define os_crypt_des_key_gen            _P_OS_CRYPT->_p_os_crypt_des_key_gen
  #define os_crypt_mk_swap_read           _P_OS_CRYPT->_p_os_crypt_dumy
  #define os_crypt_sha1_core              _P_OS_CRYPT->_p_os_crypt_sha1_core
  #define os_crypt_sha512                 _P_OS_CRYPT->_p_os_crypt_sha512
  #define os_crypt_cipher512              _P_OS_CRYPT->_p_os_crypt_cipher512
  #define os_crypt_real_rnd               _P_OS_CRYPT->_p_os_crypt_real_rnd
  #define os_crypt_drbg_rnd               _P_OS_CRYPT->_p_os_crypt_drbg_rnd
  #define os_crypt_drbg_reseed            _P_OS_CRYPT->_p_os_crypt_drbg_reseed

#ifdef DEBUG
  #define os_crypt_drbg_hash_generate     _P_OS_CRYPT->_p_os_crypt_drbg_hash_generate
  #define os_crypt_drbg_hash_instantiate  _P_OS_CRYPT->_p_os_crypt_drbg_hash_instantiate
  #define os_crypt_drbg_hash_reseed       _P_OS_CRYPT->_p_os_crypt_drbg_hash_reseed
#endif

  // new as of SMOS 5.6.1.0
  #define os_crypt_drbg_reseed_2ndentropy  _P_OS_CRYPT->_p_os_crypt_drbg_reseed_2ndentropy

#endif /* defined(_OS_C_INT_) || defined(_ALWAYS_C_INT_) */

#endif

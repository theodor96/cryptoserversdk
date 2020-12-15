/******************************************************************************
 *
 *  $File Identification                    $
 *  $Filename          : hash.h             $
 *  $Module version    : x.x.x.x            $
 *  $Module name       : HASH               $
 *  $Release Date      : DD.MM.YYYY         $
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Utimaco IS GmbH
 *
 *  Description : Global header file of CS2000 module HASH
 *                Must be included in every CS2000 software that uses
 *                functions of this module
 *
 *  History     :
 *  Date       | Version |                 Action                      | Author
 *  -----------+---------+---------------------------------------------+--------
 *  26.04.2001 |         | Creation                                    |  R.H.
 *  05.11.2001 |         | Addapted to Cryptoserver 2000               |  Stefan Gohmann
 *  05.12.2002 |         | hash() function renamed to hash_hash()      |  R.H.
 *  26.18.2004 | 1.0.1.0 | sha224 and sha256 added                     |  R.H.
 *  08.12.2005 | 1.0.2.0 | MD5 added                                   |  RVE
 *  03.02.2006 | 1.0.3.0 | SHA384 + SHA512 added (CS2064)              |  RVE
 *  27.07.2006 | 1.0.4.1 | structure alignment on CS2000               |  RHE
 *  29.11.2007 | 1.0.5.3 | hash_get_oid(), hash_get_info()             |  RHE
 ******************************************************************************/
#ifndef __HASH_H_PUB_INCLUDED__
  #define __HASH_H_PUB_INCLUDED__

#include "os_mdl.h"

/* Error Codes:  (0xB0000000 | (HASH_MDL_ID << 16) | (errno))  */

/* --- BEGIN ERROR CODES --- */
#define E_HASH                0xB089          /* CryptoServer module HASH */

#define E_HASH_MEM            0xB0890001      /* Memory Error */
#define E_HASH_PARAMETER      0xB0890002      /* Illegal Parameter */
#define E_HASH_LEN            0xB0890003      /* Illegal Length */
#define E_HASH_MODE           0xB0890004      /* Illegal Mode */
#define E_HASH_FUNCTION       0xB0890005      /* Function not supported */
//#define E_HASH_MODE_FIPS      0xB0890006      /* Mode not permitted in FIPS mode */

/* --- END ERROR CODES --- */

  
/* mode parameter */
#define HASH_CONT                       0x00000001

/* hash algo */
#define HASH_SHA1                       0x00000010
#define HASH_RMD160                     0x00000020
#define HASH_SHA224                     0x00000030
#define HASH_SHA256                     0x00000040
#define HASH_MD5                        0x00000050
#define HASH_SHA384                     0x00000060
#define HASH_SHA512                     0x00000070
#define HASH_SHA3_224                   0x00000080
#define HASH_SHA3_256                   0x00000090
#define HASH_SHA3_384                   0x000000A0
#define HASH_SHA3_512                   0x000000B0
#define HASH_SHAKE128                   0x000000C0
#define HASH_SHAKE256                   0x000000D0
#define HASH_RAW_SHAKE128               0x000000E0
#define HASH_RAW_SHAKE256               0x000000F0
#define HASH_ALGO                       0x000000F0

/* kdf prf parameter */
#define KDF_PRF_MASK                    0x00000F00
#define KDF_PRF_HMAC                    0x00000100
#define KDF_PRF_CMAC                    0x00000200 //Reserved for future used (not yet implemented)

/* kdf mod parameter */
#define KDF_MOD_MASK                    0x0000F000
#define KDF_MOD_CM                      0x00001000 //Reserved for future used (not yet implemented)
#define KDF_MOD_2PIPELINE               0x00002000 //Reserved for future used (not yet implemented)
#define KDF_MOD_FEEDBACK                0x00003000 
 
/*-----------------------------------------------------------------------------
   module identification:
  ---------------------------------------------------------------------------*/

#define HASH_MDL_ID          0x89                        /* ID of the module */
#define HASH_MDL_NAME        "HASH"                      /* Abbreviation of the module */
#ifdef CS2_SDK
  #define HASH_MDL_NAMEX     "Hash Module SDK"           /* Long name of the module */
#else
  #ifdef DEBUG
    #define HASH_MDL_NAMEX   "Hash Module DEBUG"         /* Long name of the module */
  #else
    #define HASH_MDL_NAMEX   "Hash Module"               /* Long name of the module */
  #endif
#endif
#define HASH_MDL_VERSION     0x01000d00                  /* Version of the module */


/*-----------------------------------------------------------------------------
 public interface:
  ---------------------------------------------------------------------------*/

/* The RIPEMD-160 block size and message digest sizes, in bytes */
#define RIPEMD160_DATASIZE      64
#define RIPEMD160_DIGESTSIZE    20

/* The structure for storing RIPEMD-160 info */
typedef struct
{
    unsigned int    digest[5];                /* Message digest */
    unsigned int    countLo, countHi;         /* 64-bit bit count */
    unsigned char   data[RIPEMD160_DATASIZE]; /* RIPEMD-160 data buffer */
}
HASH_RMD160_INFO;


/* The SHA block size and message digest sizes, in bytes */
#define SHA_DATASIZE    64
#define SHA_DIGESTSIZE  20

/* The structure for storing SHA info */
typedef struct
{
    unsigned char digest[20];                   /* Message digest */
    unsigned int  countLo, countHi;             /* 64-bit bit count */
    unsigned char dataBuffer[ SHA_DATASIZE ];   /* Byte buffer for data */
}
HASH_SHA1_INFO;


/* The SHA224+256 message digest sizes, in bytes */
#define SHA224_DIGESTSIZE       28
#define SHA256_DIGESTSIZE       32

/* The structure for storing SHA info */
typedef struct
{
  unsigned int count[2];
  unsigned int state[8];
  unsigned char buf[128];
}
HASH_SHA256_INFO;

typedef HASH_SHA256_INFO HASH_SHA224_INFO;



/* The SHA384+512 message digest sizes, in bytes */
#define SHA384_DIGESTSIZE  48
#define SHA512_DIGESTSIZE  64

#ifdef WIN32
  typedef  unsigned __int64 SHA_LONG64;
#elif _TMS320C6200
  typedef unsigned long SHA_LONG64;
#else
  typedef unsigned long long SHA_LONG64;
#endif

#define SHA_LBLOCK  16
#define SHA512_CBLOCK (SHA_LBLOCK*8)

typedef struct {
  SHA_LONG64 h[8];
  SHA_LONG64 Nl,Nh;
  union {
    SHA_LONG64    d[SHA_LBLOCK];
    unsigned char p[SHA512_CBLOCK];
  } u;
  unsigned int num,md_len;
} HASH_SHA512_INFO;


typedef HASH_SHA512_INFO HASH_SHA384_INFO;


typedef struct {
  SHA_LONG64    state[25];
  unsigned char buf[168];            /* buffer for incomplete data blocks, big enough for SHAKE128's data rate */
  unsigned int  cnt;                 /* length of buffered incomplete data block in bytes */
} HASH_SHA3_INFO;

/* SHA3 digest sizes in bytes */
#define SHA3_224_DIGESTSIZE   28
#define SHA3_256_DIGESTSIZE   32
#define SHA3_384_DIGESTSIZE   48
#define SHA3_512_DIGESTSIZE   64


/* The MD5 message digest sizes, in bytes */
#define MD5_DIGESTSIZE       16

/* The structure for storing MD5 info */
typedef struct 
{
    unsigned int  count[2];          /* message length in bits, lsw first */
    unsigned int  abcd[4];           /* digest buffer */
    unsigned char buf[64];           /* accumulate block */
} 
HASH_MD5_INFO;


/* The structure for storing infos */
typedef union
{
    HASH_SHA1_INFO   sha1_info;
    HASH_SHA224_INFO sha224_info;
    HASH_SHA256_INFO sha256_info;
    HASH_RMD160_INFO rmd160_info;
    HASH_MD5_INFO    md5_info;
    HASH_SHA384_INFO sha384_info;
    HASH_SHA512_INFO sha512_info;
    HASH_SHA3_INFO   sha3_info;
}
HASH_INFO;


/* The structure storing HMAC info */
typedef struct
{
  int           hash_algo;      // hash algorithm
  HASH_INFO     ihash;          // inner hash
  HASH_INFO     ohash;          // outer hash
}
HASH_HMAC_INFO;


typedef struct
{
    // Standard Function
    void *p_data;
    int  (*p_start)(T_OS_MDL_HDL,void *, void*);
    int  (*p_stop)(void);
    int  (*p_pre_replace)(void);
    int  (*p_pre_delete)(void);
    void *p_dumy;
    const void *p_module_info;
    // Hash Functions
    int  (*p_hash_hash)    (int mode, unsigned int len, unsigned char *p_data,void *p_info, unsigned char *p_hash,unsigned int *p_l_hash);
    int  (*p_hash_sha1)    (int mode, unsigned int len, unsigned char *p_data, HASH_SHA1_INFO   *p_info, unsigned char *p_hash);
    int  (*p_hash_rmd160)  (int mode, unsigned int len, unsigned char *p_data, HASH_RMD160_INFO *p_info, unsigned char *p_hash);
    int  (*p_hash_sha224)  (int mode, unsigned int len, unsigned char *p_data, HASH_SHA224_INFO *p_info, unsigned char *p_hash);
    int  (*p_hash_sha256)  (int mode, unsigned int len, unsigned char *p_data, HASH_SHA256_INFO *p_info, unsigned char *p_hash);
    int  (*p_hash_md5)     (int mode, unsigned int len, unsigned char *p_data, HASH_MD5_INFO    *p_info, unsigned char *p_hash);
    int  (*p_hash_sha384)  (int mode, unsigned int len, unsigned char *p_data, HASH_SHA384_INFO *p_info, unsigned char *p_hash);
    int  (*p_hash_sha512)  (int mode, unsigned int len, unsigned char *p_data, HASH_SHA512_INFO *p_info, unsigned char *p_hash);
    int  (*p_hash_hmac)  (int mode, unsigned int l_key, unsigned char *p_key, unsigned int l_data, unsigned char *p_data, HASH_HMAC_INFO *p_info, unsigned char *p_hash, unsigned int *p_l_hash);
    int  (*p_hash_get_oid)(int algorithm, unsigned int *p_l_oid, unsigned char **pp_oid);
    int  (*p_hash_get_info)(int algorithm, unsigned int *p_hlen,unsigned int *p_l_oid, unsigned char **pp_oid);
    int  (*p_hash_kdf_sp800108)(int algorithm, unsigned int l_ki, unsigned char* ki, unsigned int l_iv, unsigned char* iv, unsigned int l_fixdat, unsigned char* fixdat, unsigned int length, unsigned char  **pp_ko);
    int  (*p_hash_sha3_224)(int mode, unsigned int len, unsigned char *p_data, HASH_SHA3_INFO   *p_info, unsigned char *p_hash);
    int  (*p_hash_sha3_256)(int mode, unsigned int len, unsigned char *p_data, HASH_SHA3_INFO   *p_info, unsigned char *p_hash);
    int  (*p_hash_sha3_384)(int mode, unsigned int len, unsigned char *p_data, HASH_SHA3_INFO   *p_info, unsigned char *p_hash);
    int  (*p_hash_sha3_512)(int mode, unsigned int len, unsigned char *p_data, HASH_SHA3_INFO   *p_info, unsigned char *p_hash);
    int  (*p_hash_shake128)(int mode, unsigned int len, unsigned char *p_data, HASH_SHA3_INFO   *p_info, unsigned int l_hash, unsigned char *p_hash);
    int  (*p_hash_shake256)(int mode, unsigned int len, unsigned char *p_data, HASH_SHA3_INFO   *p_info, unsigned int l_hash, unsigned char *p_hash);
    int  (*p_hash_raw_shake128)(int mode, unsigned int len, unsigned char *p_data, HASH_SHA3_INFO *p_info, unsigned int l_hash, unsigned char *p_hash);
    int  (*p_hash_raw_shake256)(int mode, unsigned int len, unsigned char *p_data, HASH_SHA3_INFO *p_info, unsigned int l_hash, unsigned char *p_hash);
} T_HASH_TABLE_PUB;


#ifdef _HASH_C_INT_
  /* function prototypes used by the module (internal) */
  int  hash_start(T_OS_MDL_HDL,void *,void *);
  int  hash_stop(void);
  int  hash_pre_replace(void);
  int  hash_pre_delete(void);
  // Hash Functions
  int  hash_hash    (int mode, unsigned int len, unsigned char *p_data, void *p_info, unsigned char *p_hash,unsigned int *p_l_hash);
  int  hash_sha1    (int mode, unsigned int len, unsigned char *p_data, HASH_SHA1_INFO   *p_info, unsigned char *p_hash);
  int  hash_sha224  (int mode, unsigned int len, unsigned char *p_data, HASH_SHA224_INFO *p_info, unsigned char *p_hash);
  int  hash_sha256  (int mode, unsigned int len, unsigned char *p_data, HASH_SHA256_INFO *p_info, unsigned char *p_hash);
  int  hash_rmd160  (int mode, unsigned int len, unsigned char *p_data, HASH_RMD160_INFO *p_info, unsigned char *p_hash);
  int  hash_md5     (int mode, unsigned int len, unsigned char *p_data, HASH_MD5_INFO    *p_info, unsigned char *p_hash);
  int  hash_sha384  (int mode, unsigned int len, unsigned char *p_data, HASH_SHA384_INFO *p_info, unsigned char *p_hash);
  int  hash_sha512  (int mode, unsigned int len, unsigned char *p_data, HASH_SHA512_INFO *p_info, unsigned char *p_hash);
  int  hash_hmac(int mode, unsigned int l_key, unsigned char *p_key, unsigned int l_data, unsigned char *p_data,
                 HASH_HMAC_INFO *p_info, unsigned char *p_hash, unsigned int *p_l_hash);
  int  hash_get_oid(int algorithm, unsigned int *p_l_oid, unsigned char **pp_oid);
  int  hash_get_info(int algorithm, unsigned int *p_hlen,unsigned int *p_l_oid, unsigned char **pp_oid);
  int  hash_kdf_sp800108(int algorithm, unsigned int l_ki, unsigned char* ki, unsigned int l_iv, unsigned char* iv, unsigned int l_fixdat, unsigned char* fixdat, unsigned int length, unsigned char  **pp_ko);
  int  hash_sha3_224(int mode, unsigned int len, unsigned char *p_data, HASH_SHA3_INFO   *p_info, unsigned char *p_hash);
  int  hash_sha3_256(int mode, unsigned int len, unsigned char *p_data, HASH_SHA3_INFO   *p_info, unsigned char *p_hash);
  int  hash_sha3_384(int mode, unsigned int len, unsigned char *p_data, HASH_SHA3_INFO   *p_info, unsigned char *p_hash);
  int  hash_sha3_512(int mode, unsigned int len, unsigned char *p_data, HASH_SHA3_INFO   *p_info, unsigned char *p_hash);
  int  hash_shake128(int mode, unsigned int len, unsigned char *p_data, HASH_SHA3_INFO   *p_info, unsigned int l_hash, unsigned char *p_hash);
  int  hash_shake256(int mode, unsigned int len, unsigned char *p_data, HASH_SHA3_INFO   *p_info, unsigned int l_hash, unsigned char *p_hash);
  int  hash_raw_shake128(int mode, unsigned int len, unsigned char *p_data, HASH_SHA3_INFO *p_info, unsigned int l_hash, unsigned char *p_hash);
  int  hash_raw_shake256(int mode, unsigned int len, unsigned char *p_data, HASH_SHA3_INFO *p_info, unsigned int l_hash, unsigned char *p_hash);


#else
  /* external interface to be used by other modules */

  extern MDL_GLOBAL T_OS_MDL_HDL P_HASH;

  #define _P_HASH  ((T_HASH_TABLE_PUB *)P_HASH)         /* shortcut */

  #define P_hash_data         (_P_HASH->_p_data);

  #define hash_start          _P_HASH->p_start
  #define hash_stop           _P_HASH->p_stop
  #define hash_pre_replace    _P_HASH->p_pre_replace
  #define hash_pre_delete     _P_HASH->p_pre_delete
  #define hash_hash           _P_HASH->p_hash_hash
  #define hash_sha1           _P_HASH->p_hash_sha1
  #define hash_sha224         _P_HASH->p_hash_sha224
  #define hash_sha256         _P_HASH->p_hash_sha256
  #define hash_rmd160         _P_HASH->p_hash_rmd160
  #define hash_md5            _P_HASH->p_hash_md5
  #define hash_sha384         _P_HASH->p_hash_sha384
  #define hash_sha512         _P_HASH->p_hash_sha512
  #define hash_hmac           _P_HASH->p_hash_hmac
  #define hash_get_oid        _P_HASH->p_hash_get_oid
  #define hash_get_info       _P_HASH->p_hash_get_info
  #define hash_kdf_sp800108   _P_HASH->p_hash_kdf_sp800108
  #define hash_sha3_224       _P_HASH->p_hash_sha3_224
  #define hash_sha3_256       _P_HASH->p_hash_sha3_256
  #define hash_sha3_384       _P_HASH->p_hash_sha3_384
  #define hash_sha3_512       _P_HASH->p_hash_sha3_512
  #define hash_shake128       _P_HASH->p_hash_shake128
  #define hash_shake256       _P_HASH->p_hash_shake256
  #define hash_raw_shake128   _P_HASH->p_hash_raw_shake128
  #define hash_raw_shake256   _P_HASH->p_hash_raw_shake256

#endif /* _HASH_C_INT_ */



#endif /* __HASH_H_PUB_INCLUDED__ */

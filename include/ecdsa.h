/*****************************************************************************
 *
 *  $File Identification                    $
 *  $Filename          : ecdsa.h            $
 *  $Module version    : x.x.x.x            $
 *  $Module name       : ECDSA              $
 *  $Release Date      : DD.MM.YYYY         $
 *
 *  Author(s)   : Rainer Herbertz
 *                Utimaco IS GmbH
 *
 *  Description : Global header file of CS2000 module ECDSA
 *
 *  History     :
 *  Date       |                 Action                          |  Author
 *  -----------|-------------------------------------------------|---------
 *  21.03.2006 | Creation                                        |  R.H.
 *****************************************************************************/


#ifndef __ECDSA_H_PUB_INCLUDED__
  #define __ECDSA_H_PUB_INCLUDED__

#include "os_mdl.h"
#include "eca.h"

/* module identification: */

#define ECDSA_MDL_ID          0x9C                /* ID of the module                             */
#define ECDSA_MDL_NAME      "ECDSA"               /* Short name of the module                     */

#ifdef CS2_SDK
    #define ECDSA_MDL_NAMEX "ECDSA Module SDK"    /* Long name of the module                      */
#else
    #ifdef DEBUG
    #define ECDSA_MDL_NAMEX "ECDSA Module DEBUG"  /* Long name of the module                      */
    #else
    #define ECDSA_MDL_NAMEX "ECDSA Module"        /* Long name of the module                      */
    #endif
#endif

#define ECDSA_MDL_VERSION   0x01011600            /* Version of the module                        */


/* flags for ecdsa_keygen */

// ECDSA_MODE_REAL_RND        0x00000000          // definition see "flags for ecdsa_sign"
// ECDSA_MODE_PSEUDO_RND      0x00000001          // definition see "flags for ecdsa_sign"
#define ECDSA_FMT_UNCOMP      ECA_FMT_UNCOMP      // uncompressed format
#define ECDSA_FMT_COMP        ECA_FMT_COMP        // compressed format


/* flags for ecdsa_sign: */

// input parameter 'flags'
#define ECDSA_MODE_REAL_RND   0x00000000          /* use real random generator                    */
#define ECDSA_MODE_PSEUDO_RND 0x00000001          /* use pseudo random generator                  */

// bitwise OR with input parameter 'l_hash'
#define ECDSA_HASH_MODE_X9_62 0x00000000
#define ECDSA_HASH_MODE_BSI   0x00010000

/* flags for ecdsa_sign_edwards: */

#define ECDSA_MODE_INIT       0x00000100          /* init-flag for long messages (RFC8032-EdDSA)  */
#define ECDSA_MODE_CONT       0x00000200          /* continuous-flag             (RFC8032-EdDSA)  */
#define ECDSA_MODE_FINAL      0x00000400          /* final-flag                  (RFC8032-EdDSA)  */

#define ECDSA_PRE_HASH        0x00001000          /* ph-flag                     (RFC8032-EdDSA)  */

/* flags for ecdsa_verify_edwards: */

// ECDSA_MODE_INIT            0x00000100          // definition see "flags for ecdsa_sign"
// ECDSA_MODE_CONT            0x00000200          // definition see "flags for ecdsa_sign"        
// ECDSA_MODE_FINAL           0x00000400          // definition see "flags for ecdsa_sign"

// ECDSA_PRE_HASH             0x00001000          // definition see "flags for ecdsa_sign"

/* flags for ecdsa_dh + ecdsa_dh_gen: */
 
#define ECDSA_KDF_CT_NIST     0x00000800         /* use a counter and place it in front of the    */
                                                 /* data to be hashed                             */
#define ECDSA_KDF_HASH_R      0x00001000                                                                              
#define ECDSA_KDF_CT          0x00002000         /* use a counter and place it between the shared */
                                                 /* secret and the optional shared info of the    */
                                                 /* data to be hashed                             */
#define ECDSA_KDF_COF         0x00004000
#define ECDSA_KDF_RAW         0x00008000
             

/* flags for ecies crypt_algo and mac_algo: */
/*                                                                                                   */
/*crypt_algo:                                 +---  AES Mode                                         */
/*                                algo  ----+ |                                                      */
/*                                 RFU  ---+| | ++- AES keylen                                       */
/*Bit31: Compat.Mode to vrsn < 1.1.3.0  --+|| | ||                                                   */
/*                                        ||| | ||                                                   */
/*                                      0xnnnnnnnn                                                   */
/*                                                                                                   */
/*mac_algo:                                  ++----- if HMAC/MAC1: keylen (optional)                 */
/*                    algo (AES/HMAC)  -----+|| +--- if HMAC/MAC1: Hash algo (4 bit)                 */
/*                                          ||| |                                                    */
/*                     if MAC1: maclen  --++||| ++-- if AESMac: keylen  (8 bit)                      */
/*                                        ||||| ||                                                   */
/*                                      0xnnnnnnnn                                                   */

#define ECDSA_ECIES_ALGO_MASK           0x00F00000                      /*algo mask for crypt and mac*/
#define ECDSA_ECIES_XOR                 0x00000000                      /* algo = XOR                */
#define ECDSA_ECIES_AES                 0x00100000                      /* algo = AES                */
#define ECDSA_ECIES_DES                 0x00200000                      /* algo = DES                */
#define ECDSA_ECIES_HMAC                0x00300000                      /* algo = HMAC               */
#define ECDSA_ECIES_MAC1                0x00400000                      /* algo = (subset) MAC1      */
#define ECDSA_ECIES_COMPAT_MODE         0x80000000  /* crypt_algo only: for decryption of data       */
                                                    /* that was encrypted by ecdsa vrsn < 1.1.3.0    */

#define ECDSA_ECIES_AES_LEN_MASK        0x000000FF                      /* aes keylen mask           */
#define ECDSA_ECIES_AES_KEYLEN128       0x00000010                      /* aes keylen mask           */
#define ECDSA_ECIES_AES_KEYLEN192       0x00000018                      /* aes keylen mask           */
#define ECDSA_ECIES_AES_KEYLEN256       0x00000020                      /* aes keylen mask           */


/* flags for ecies mac_algo only: */

#define ECDSA_ECIES_HMAC_ALGO_MASK      0x000000F0                      /* hash type as defined in hash.h */
#define ECDSA_ECIES_HMAC_KEYLEN_MASK    0x000FF000                      /*mackey len, if != hash size*/
#define ECDSA_ECIES_HMAC_KEYLEN_USEDEF  0x00000000                      /*mackey len, if != hash size*/
#define ECDSA_ECIES_MAC1_MACLEN_MASK    0xFF000000                      /* mac/digest len, if ECDSA_ECIES_MAC1 */
#define ECDSA_ECIES_MAC1_MACLEN_USEDEF  0x00000000                      /* Use default maclen = keylen */
#define ECDSA_ECIES_MAC1_MACLEN_SHIFT   24                              /* shift count of mac/digest len */
#define ECDSA_ECIES_MAC1_MACLEN_MIN     4                               /* minimal MAC1 digest len (32Bit)*/

/* MAC1-SHA256-128  ( ( (128U/8) << ECDSA_ECIES_MAC1_MACLEN_SHIFT ) | ECDSA_ECIES_MAC1 | HASH_SHA256 ) */
#define ECDSA_ECIES_MAC1_SHA256_128     0x10400040

/* MAC1-SHA384-192( ( (192U/8) << ECDSA_ECIES_MAC1_MACLEN_SHIFT ) | ECDSA_ECIES_MAC1 | HASH_SHA384 ) */
#define ECDSA_ECIES_MAC1_SHA384_192     0x18400060

/* MAC1-SHA384-192( ( (256U/8) << ECDSA_ECIES_MAC1_MACLEN_SHIFT ) | ECDSA_ECIES_MAC1 | HASH_SHA512 ) */
#define ECDSA_ECIES_MAC1_SHA512_256     0x20400070

/* maximum number of signatures inside a bulk signature: */
#define ECDSA_BULK_MAX 16


/* public interface: */

typedef struct
{
    void   *p_data;
    int    (*p_start)(T_OS_MDL_HDL, void*, void*);
    int    (*p_stop)(void);
    int    (*p_pre_replace)(void);
    int    (*p_pre_delete)(void);
    void   *p_dumy;
    const void   *p_module_info;

    int (*p_sign)(
        ECDP           *dp,         // (I) domain parameter (curve)
        unsigned int   flags,       // (I) ECDSA_MODE_REAL / PSEUDO_RND
        unsigned int   l_x,         // (I) Length of private key
        unsigned char  *p_x,        // (I) Pointer to private key
        unsigned int   l_hash,      // (I) Length of hash value
        unsigned char  *p_hash,     // (I) Pointer to hash value
        unsigned int   *p_l_sign,   // (I/O) Size of buffer / length of signature
        unsigned char  *p_sign      // (O) Pointer to signature
        );

    int (*p_verify)(
        ECDP           *dp,         // (I) domain parameter (curve)
        unsigned int   l_y,         // (I) Length of public key
        unsigned char  *p_y,        // (I) Pointer to public key
        ECPCP          *p_pcP,      // (I) precalculated public key (optional)
        unsigned int   l_hash,      // (I) Length of hash value
        unsigned char  *p_hash,     // (I) Pointer to hash value
        unsigned int   l_sign_r,    // (I) Length of signature / part r of signature
        unsigned char  *p_sign_r,   // (I) Pointer to signature / part r of signature
        unsigned int   l_sign_s,    // (I) Length of part s of signature
        unsigned char  *p_sign_s    // (I) Pointer to part s of signature (or NULL)
        );

    void (*p_free_pcpk)(ECPCP *p_pcp);

    int (*p_calc_pcpk)(
        ECDP           *dp,         // (I) domain parameter
        unsigned int   l_y,         // (I) Length of public key
        unsigned char  *p_y,        // (I) Pointer to public key
        ECPCP          **pp_pcp     // (O) precalculated public key
        );

    int (*p_keygen)(
        ECDP           *dp,         // (I) domain parameter (curve)
        unsigned int   flags,       // (I) ECDSA_MODE_REAL / PSEUDO_RND, ECA_FMT_...
        unsigned int   *p_l_x,      // (O) length of private key
        unsigned char  **pp_x,      // (O) private key
        unsigned int   *p_l_y,      // (O) length of public key
        unsigned char  **pp_y       // (O) public key
        );

    int (*p_keychk)(
        ECDP           *dp,         // (I) domain parameter (curve)
        unsigned int   l_x,         // (I) Length of private key
        unsigned char  *p_x,        // (I) Pointer to private key
        unsigned int   l_y,         // (I) Length of public key
        unsigned char  *p_y         // (I) Pointer to public key
        );

    int    (*p_sign_decode)(unsigned int l_sign, unsigned char* p_sign,
                            unsigned int *p_l_r, unsigned char **pp_r,
                            unsigned int *p_l_s, unsigned char **pp_s );
    int    (*p_sign_encode)(unsigned int l_r, unsigned char *p_r,
                            unsigned int l_s, unsigned char *p_s,
                            unsigned int *p_l_sign, unsigned char *p_sign );

    int    (*p_key_decode)(unsigned int,unsigned char *,void *,unsigned int *,unsigned char **,
                           unsigned int *,unsigned char **,unsigned int *,unsigned char **);
    int    (*p_key_encode)(unsigned int,unsigned char *,unsigned int,unsigned char *,
                           unsigned int,unsigned char *,void *,unsigned int *,unsigned char *);

    int    (*p_dh)(ECDP *dp, unsigned int l_r, unsigned char *p_r, unsigned int l_x,
                   unsigned char *p_x, unsigned int l_y, unsigned char *p_y,
                   unsigned int flags, unsigned int l_secret, unsigned char *p_secret);

    int    (*p_dh_gen)(ECDP *dp, unsigned int l_y, unsigned char *p_y, ECPCP *p_pcP,unsigned int  flags,
                       unsigned int l_secret, unsigned char *p_secret, unsigned int *p_l_r, unsigned char **pp_r);

    int    (*p_dh_ex)(ECDP *dp, unsigned int l_r, unsigned char *p_r, unsigned int l_x,
                   unsigned char *p_x, unsigned int l_y, unsigned char *p_y,
                   unsigned int flags, unsigned int l_shsec, unsigned char *p_shsec,
                   unsigned int l_secret, unsigned char *p_secret);

    int    (*p_dh_gen_ex)(ECDP *dp, unsigned int l_y, unsigned char *p_y, ECPCP *p_pcP,unsigned int  flags,
                          unsigned int l_shsec, unsigned char *p_shsec,
                          unsigned int l_secret, unsigned char *p_secret,
                          unsigned int *p_l_r, unsigned char **pp_r);

    int    (*p_ecies_encrypt)(ECDP *dp, unsigned int l_y, unsigned char *p_y, ECPCP *p_pcP, unsigned int ecdsa_keyflags,
                              unsigned int dh_mode, unsigned int hash_algo, unsigned int crypt_algo, unsigned int mac_algo,
                              unsigned int l_shsec1, unsigned char *p_shsec1,
                              unsigned int l_shsec2, unsigned char *p_shsec2,
                              unsigned int l_indat, unsigned char *p_indat,
                              unsigned int *p_l_outdat, unsigned char **pp_outdat);

    int    (*p_ecies_decrypt)(ECDP *dp, unsigned int l_x, unsigned char *p_x,
                              unsigned int dh_mode, unsigned int hash_algo, unsigned int crypt_algo, unsigned int mac_algo,
                              unsigned int l_shsec1, unsigned char *p_shsec1,
                              unsigned int l_shsec2, unsigned char *p_shsec2,
                              unsigned int l_indat, unsigned char *p_indat,
                              unsigned int *p_l_outdat, unsigned char **pp_outdat);

    int    (*p_bulk_sign)( ECDP *dp, unsigned int flags, unsigned int l_x, unsigned char *p_x
                        , unsigned int ct, unsigned int l_hash[], unsigned char *p_hash[]
                        , unsigned int l_sign, unsigned char  *p_sign[]);                                                      

    int    (*p_ecdsa_tokengen)(ECDP* const dp, unsigned int flags, unsigned int* const p_l_x,
                            unsigned char* const p_x, unsigned int* const p_l_y, unsigned char* const p_y);

    int(*p_sign_edwards)(
		ECDP           *p_dp,       // (I) domain parameter (curve)
		unsigned int   flags,       // (I) ECDSA_MODE_REAL / PSEUDO_RND  / ECDSA_MODE_INIT / CONT / FINAL
		unsigned int   l_x,         // (I) Length of private key
		unsigned char  *p_x,        // (I) Pointer to private key
		unsigned int   l_y,         // (I) Length of public key
		unsigned char  *p_y,        // (I) Pointer to public key
		unsigned int   l_msg,       // (I) Length of message
		unsigned char  *p_msg,      // (I) Pointer to message
		unsigned int   l_c,         // (I) Length of context (RFC8032, max. 255B)
		unsigned char  *p_c,        // (I) Pointer to context 
		void           *p_info1,    // (I/O) signature's intermediate hash info 1
		void           *p_info2,    // (I/O) signature's intermediate hash info 2
		unsigned int   *p_l_sign,   // (I/O) Size of buffer / length of signature
		unsigned char  *p_sign      // (O) Pointer to signature
		);

    int(*p_verify_edwards)(
		ECDP           *p_dp,       // (I) domain parameter (curve)
		unsigned int   flags,       // (I) ECDSA_MODE_INIT / CONT / FINAL 
		unsigned int   l_y,         // (I) Length of public key
		unsigned char  *p_y,        // (I) Pointer to public key
		unsigned int   l_msg,       // (I) Length of message
		unsigned char  *p_msg,      // (I) Pointer to message
		unsigned int   l_c,         // (I) Length of context (RFC8032, max. 255B)
		unsigned char  *p_c,        // (I) Pointer to context 
		unsigned int   l_sign_r,    // (I) Length of signature / part r of signature
		unsigned char  *p_sign_r,   // (I) Pointer to signature / part r of signature
		unsigned int   l_sign_s,    // (I) Length of part s of signature
		unsigned char  *p_sign_s,   // (I) Pointer to part s of signature (or NULL) 
		void           *p_reserved, // (I) place holder (future use), set to NULL 
		void           *p_info      // (I/O) verification's intermediate hash info     
		);

    int(*p_key_encode_rfc8410)(
        unsigned int   l_x,         // (I)   Length of private key 
        unsigned char  *p_x,        // (I)   Pointer to private key 
        unsigned int   *p_l_key,    // (I/O) Size of buffer / Length of key
        unsigned char  *p_key       // (O)   encoded key
    );

    int(*p_key_decode_rfc8410)(
        unsigned int   l_key,       // (I) Length of ASN.1 coded key
        unsigned char  *p_key,      // (I) Pointer to ASN.1 coded key
        unsigned int   *p_l_x,      // (O) Length of private key
        unsigned char  **pp_x       // (O) Pointer to private key
        );

    int (*p_ecdsa_agree_secret_tr03111)(
        ECDP           *p_dp,            // (I) Domain parameter (curve)
        unsigned int    l_y,             // (I) Length of public key
        unsigned char  *p_y,             // (I) Pointer to public key
        unsigned int    l_x,             // (I) Length private key
        unsigned char  *p_x,             // (I) Pointer to private key
        unsigned int    l_secret_point,  // (I) Size of secret_point
        unsigned char  *p_secret_point,  // (O) Generated secret point
        unsigned int    l_secret_value,  // (I) Size of secret value
        unsigned char  *p_secret_value   // (O) (optional) generated secret value
        );
} T_ECDSA_TABLE_PUB;



#ifdef _ECDSA_C_INT_

/* function prototypes used by the module (internal) */

int  ecdsa_start( T_OS_MDL_HDL, void*, void *);
int  ecdsa_pre_replace(void);
int  ecdsa_pre_delete(void);

int ecdsa_sign(
    ECDP           *dp,         // (I) domain parameter (curve)
    unsigned int   flags,       // (I) ECDSA_MODE_REAL / PSEUDO_RND
    unsigned int   l_x,         // (I) Length of private key
    unsigned char  *p_x,        // (I) Pointer to private key
    unsigned int   l_hash,      // (I) Length of hash value
    unsigned char  *p_hash,     // (I) Pointer to hash value
    unsigned int   *p_l_sign,   // (I/O) Size of buffer / length of signature
    unsigned char  *p_sign      // (O) Pointer to signature
    );

int ecdsa_verify(
    ECDP           *dp,         // (I) domain parameter (curve)
    unsigned int   l_y,         // (I) Length of public key
    unsigned char  *p_y,        // (I) Pointer to public key
    ECPCP          *p_pcP,      // (I) precalculated public key (optional)
    unsigned int   l_hash,      // (I) Length of hash value
    unsigned char  *p_hash,     // (I) Pointer to hash value
    unsigned int   l_sign_r,    // (I) Length of signature / part r of signature
    unsigned char  *p_sign_r,   // (I) Pointer to signature / part r of signature
    unsigned int   l_sign_s,    // (I) Length of part s of signature
    unsigned char  *p_sign_s    // (I) Pointer to part s of signature (or NULL)
    );

void ecdsa_free_pcpk(ECPCP *p_pcp);

int ecdsa_calc_pcpk(
    ECDP           *dp,         // (I) domain parameter
    unsigned int   l_y,         // (I) Length of public key
    unsigned char  *p_y,        // (I) Pointer to public key
    ECPCP          **pp_pcp     // (O) precalculated public key
    );

int ecdsa_keygen(
    ECDP           *dp,         // (I) domain parameter (curve)
    unsigned int   flags,       // (I) ECDSA_MODE_REAL / PSEUDO_RND, ECA_FMT_...
    unsigned int   *p_l_x,      // (O) length of private key
    unsigned char  **pp_x,      // (O) private key
    unsigned int   *p_l_y,      // (O) length of public key
    unsigned char  **pp_y       // (O) public key
    );

int ecdsa_keychk(
    ECDP           *dp,         // (I) domain parameter (curve)
    unsigned int   l_x,         // (I) Length of private key
    unsigned char  *p_x,        // (I) Pointer to private key
    unsigned int   l_y,         // (I) Length of public key
    unsigned char  *p_y         // (I) Pointer to public key
    );

int ecdsa_sign_decode(
    unsigned int   l_sign,      // (I) Length of signature
    unsigned char* p_sign,      // (I) Pointer to prime signature
    unsigned int   *p_l_r,      // (O) Length of part r
    unsigned char  **pp_r,      // (O) Pointer to part r
    unsigned int   *p_l_s,      // (O) Length of part s
    unsigned char  **pp_s       // (O) Pointer to part s
    );

int ecdsa_sign_encode(
    unsigned int   l_r,         // (I)   Length of part r
    unsigned char  *p_r,        // (I)   Pointer to part r
    unsigned int   l_s,         // (I)   Length of part s
    unsigned char  *p_s,        // (I)   Pointer to part s
    unsigned int   *p_l_sign,   // (I/O) Length of signature
    unsigned char  *p_sign      // (O)   Pointer to signature
    );

int ecdsa_key_decode(
    unsigned int   l_key,       // (I) Length of ASN.1 coded key
    unsigned char  *p_key,      // (I) Pointer to ASN.1 coded key
    void           *rfu,        //     must be NULL
    unsigned int   *p_l_x,      // (O) Length of private key
    unsigned char  **pp_x,      // (O) Pointer to private key
    unsigned int   *p_l_y,      // (O) Length of public key (or 0)
    unsigned char  **pp_y,      // (O) Pointer to public key (or NULL)
    unsigned int   *p_l_oid,    // (O) Length of OID (or 0)
    unsigned char  **pp_oid     // (O) Pointer to object identifier (or NULL)
    );

int ecdsa_key_encode(
    unsigned int   l_x,         // (I)   Length of private key
    unsigned char  *p_x,        // (I)   Pointer to private key
    unsigned int   l_y,         // (I)   Length of public key (or 0)
    unsigned char  *p_y,        // (I)   Pointer to public key (or NULL)
    unsigned int   l_oid,       // (I)   Length of OID (or 0)
    unsigned char  *p_oid,      // (I)   Pointer to object identifier (or NULL)
    void           *rfu,        //       must be NULL
    unsigned int   *p_l_key,    // (I/O) Size of buffer / Length of key
    unsigned char  *p_key       // (O)   encoded key
    );

int ecdsa_dh(
    ECDP           *dp,         // (I) domain parameter (curve)
    unsigned int   l_r,         // (I) Length of public key
    unsigned char  *p_r,        // (I) Pointer to public key
    unsigned int   l_x,         // (I) Length of private key
    unsigned char  *p_x,        // (I) Pointer to private key
    unsigned int   l_y,         // (I) Length of public key for KDF
    unsigned char  *p_y,        // (I) Pointer to public key for KDF
    unsigned int   flags,       // (I) rnd_mode, hash_algo, hash_r
    unsigned int   l_secret,    // (I) Length of generated secret value
    unsigned char  *p_secret    // (O) generated secret value
    );

int ecdsa_dh_ex(
    ECDP           *dp,         // (I) domain parameter (curve)
    unsigned int   l_r,         // (I) Length of public key
    unsigned char  *p_r,        // (I) Pointer to public key
    unsigned int   l_x,         // (I) Length of private key
    unsigned char  *p_x,        // (I) Pointer to private key
    unsigned int   l_y,         // (I) Length of public key for KDF
    unsigned char  *p_y,        // (I) Pointer to public key for KDF
    unsigned int   flags,       // (I) rnd_mode, hash_algo, hash_r
    unsigned int   l_shsec,     // (I) Length of shared secret
    unsigned char  *p_shsec,    // (I) Shared secret
    unsigned int   l_secret,    // (I) Length of generated secret value
    unsigned char  *p_secret    // (O) generated secret value
    );

int ecdsa_dh_gen(
    ECDP           *dp,         // (I) domain parameter (curve)
    unsigned int   l_y,         // (I) Length of public key Q
    unsigned char  *p_y,        // (I) Pointer to public key Q
    ECPCP          *p_pcP,      // (I) precalculated public key (optional)
    unsigned int   flags,       // (I) rnd_mode, hash_algo, hash_r
    unsigned int   l_secret,    // (I) Length of generated secret value
    unsigned char  *p_secret,   // (O) generated secret value
    unsigned int   *p_l_r,      // (O) length of temp. public key
    unsigned char  **pp_r       // (O) temp. public key
    );

int ecdsa_dh_gen_ex(
    ECDP           *dp,         // (I) domain parameter (curve)
    unsigned int   l_y,         // (I) Length of public key Q
    unsigned char  *p_y,        // (I) Pointer to public key Q
    ECPCP          *p_pcP,      // (I) precalculated public key (optional)
    unsigned int   flags,       // (I) rnd_mode, hash_algo, hash_r
    unsigned int   l_shsec,     // (I) Length of shared secret
    unsigned char  *p_shsec,    // (I) Shared secret
    unsigned int   l_secret,    // (I) Length of generated secret value
    unsigned char  *p_secret,   // (O) generated secret value
    unsigned int   *p_l_r,      // (O) length of temp. public key
    unsigned char  **pp_r       // (O) temp. public key
    );

int ecdsa_ecies_encrypt(
    ECDP           *dp,                        // (I) domain parameter (curve)         "Q"
    unsigned int   l_y,                        // (I) Length of public key Q           "Q"
    unsigned char  *p_y,                       // (I) Pointer to public key Q          "Q"
    ECPCP          *p_pcP,                     // (I) precalculated public key (optional)
    unsigned int   ecdsa_keyflags,             // (I) rnd_mode, format of generated public key
    unsigned int   dh_mode,                    // (I) flag for kdf-mode (ECDSA_KDF_COF)
    unsigned int   hash_algo,                  // (I) flag to specify the hash algorithm
    unsigned int   crypt_algo,                 // (I) encryption algorithm: if AES: xored with mode and keylen
    unsigned int   mac_algo,                   // (I) flag to specify the mac algorithm
    unsigned int   l_shsec1,                   // (I) Length of shared secret
    unsigned char  *p_shsec1,                  // (I) Shared secret                    "SharedData1"
    unsigned int   l_shsec2,                   // (I) Length of shared secret
    unsigned char  *p_shsec2,                  // (I) Shared secret                    "SharedData2"
    unsigned int   l_indat,                    // (I) Length of data to be encrypted
    unsigned char  *p_indat,                   // (I) Data to be encrypted             "EncData"
    unsigned int   *p_l_outdat,                // (O) Length of the output bit string
    unsigned char  **pp_outdat                 // (O) Output bit string                "EncData"
    );

int ecdsa_ecies_decrypt(
    ECDP           *dp,                        // (I) domain parameter (curve)         "d"
    unsigned int   l_x,                        // (I) Length of private key d          "d"
    unsigned char  *p_x,                       // (I) Pointer to private key d         "d"
    unsigned int   dh_mode,                    // (I) flag for kdf-mode (ECDSA_KDF_COF)
    unsigned int   hash_algo,                  // (I) flag to specify the hash algorithm
    unsigned int   crypt_algo,                 // (I) flag to specify the encryption algorithm
    unsigned int   mac_algo,                   // (I) flag to specify the mac algorithm
    unsigned int   l_shsec1,                   // (I) Length of shared secret
    unsigned char  *p_shsec1,                  // (I) Shared secret                    "SharedData1"
    unsigned int   l_shsec2,                   // (I) Length of shared secret
    unsigned char  *p_shsec2,                  // (I) Shared secret                    "SharedData2"
    unsigned int   l_indat,                    // (I) Length of data to be decrypted
    unsigned char  *p_indat,                   // (I) Data to be decrypted             "QE||MaskedEncData||MacTag"
    unsigned int   *p_l_outdat,                // (O) Length of the output bit string
    unsigned char  **pp_outdat                 // (O) Output bit string                "EncData"
    );

int ecdsa_bulk_sign( ECDP           *dp          // (I) domain parameter (curve)
                   , unsigned int   flags        // (I) ECDSA_MODE_REAL / PSEUDO_RND
                   , unsigned int   l_x          // (I) Length of private key
                   , unsigned char  *p_x         // (I) Pointer to private key
                   , unsigned int   ct           // (I) number of data elements
                   , unsigned int   l_hash[]     // (I) Length of hash value
                   , unsigned char  *p_hash[]    // (I) Pointer to hash value
                   , unsigned int   l_sign       // (I/O) Size of buffer / length of signature(s)
                   , unsigned char  *p_sign[]);  // (O) Pointer to signature(s)

int ecdsa_tokengen(
    ECDP* const          dp,         // (I) domain parameter (curve)
    unsigned int         flags,      // (I) ECDSA_MODE_REAL / PSEUDO_RND, ECA_FMT_...
    unsigned int* const  p_l_x,      // (I) length of private key buffer
    unsigned char* const p_x,        // (I/O) private key buffer
    unsigned int* const  p_l_y,      // (I) length of public key buffer
    unsigned char* const p_y         // (I/O) public key buffer
    );

int ecdsa_sign_edwards(
	ECDP           *p_dp,       // (I) domain parameter (curve)
	unsigned int   flags,       // (I) ECDSA_MODE_REAL / PSEUDO_RND  / ECDSA_MODE_INIT / CONT / FINAL
	unsigned int   l_x,         // (I) Length of private key
	unsigned char  *p_x,        // (I) Pointer to private key
	unsigned int   l_y,         // (I) Length of public key
	unsigned char  *p_y,        // (I) Pointer to public key
	unsigned int   l_msg,       // (I) Length of message
	unsigned char  *p_msg,      // (I) Pointer to message
	unsigned int   l_c,         // (I) Length of context (RFC8032, max. 255B)
	unsigned char  *p_c,        // (I) Pointer to context 
	void           *p_info1,    // (I/O) signature's intermediate hash info 1
	void           *p_info2,    // (I/O) signature's intermediate hash info 2
	unsigned int   *p_l_sign,   // (I/O) Size of buffer / length of signature
	unsigned char  *p_sign      // (O) Pointer to signature
);

int ecdsa_verify_edwards(
	ECDP           *p_dp,       // (I) domain parameter (curve)
	unsigned int   flags,       // (I) ECDSA_MODE_INIT / CONT / FINAL 
	unsigned int   l_y,         // (I) Length of public key
	unsigned char  *p_y,        // (I) Pointer to public key
	unsigned int   l_msg,       // (I) Length of message
	unsigned char  *p_msg,      // (I) Pointer to message
	unsigned int   l_c,         // (I) Length of context (RFC8032, max. 255B)
	unsigned char  *p_c,        // (I) Pointer to context 
	unsigned int   l_sign_r,    // (I) Length of signature / part r of signature
	unsigned char  *p_sign_r,   // (I) Pointer to signature / part r of signature
	unsigned int   l_sign_s,    // (I) Length of part s of signature
	unsigned char  *p_sign_s,   // (I) Pointer to part s of signature (or NULL) 
	void           *p_reserved, // (I) place holder (future use), set to NULL 
	void           *p_info      // (I/O) verification's intermediate hash info     
);

int ecdsa_key_encode_rfc8410(
    unsigned int   l_x,         // (I)   Length of private key 
    unsigned char  *p_x,        // (I)   Pointer to private key 
    unsigned int   *p_l_key,    // (I/O) Size of buffer / Length of key
    unsigned char  *p_key       // (O)   encoded key
);

int ecdsa_key_decode_rfc8410(
    unsigned int   l_key,       // (I) Length of ASN.1 coded key
    unsigned char  *p_key,      // (I) Pointer to ASN.1 coded key
    unsigned int   *p_l_x,      // (O) Length of private key
    unsigned char  **pp_x       // (O) Pointer to private key
    );

int ecdsa_agree_secret_tr03111(
    ECDP           *p_dp,            // (I) Domain parameter (curve)
    unsigned int    l_y,             // (I) Length of public key
    unsigned char  *p_y,             // (I) Pointer to public key
    unsigned int    l_x,             // (I) Length private key
    unsigned char  *p_x,             // (I) Pointer to private key
    unsigned int    l_secret_point,  // (I) Size of secret_point
    unsigned char  *p_secret_point,  // (O) Generated secret point
    unsigned int    l_secret_value,  // (I) Size of secret value
    unsigned char  *p_secret_value   // (O) (optional) generated secret value
);

#else

/* external interface to be used by other modules */

extern MDL_GLOBAL T_OS_MDL_HDL P_ECDSA;

#define _P_ECDSA ((T_ECDSA_TABLE_PUB *)P_ECDSA)     /* shortcut */

#define ecdsa_start          _P_ECDSA->p_start

#define ecdsa_sign           _P_ECDSA->p_sign
#define ecdsa_verify         _P_ECDSA->p_verify
#define ecdsa_keygen         _P_ECDSA->p_keygen
#define ecdsa_keychk         _P_ECDSA->p_keychk
#define ecdsa_calc_pcpk      _P_ECDSA->p_calc_pcpk
#define ecdsa_free_pcpk      _P_ECDSA->p_free_pcpk
#define ecdsa_sign_decode    _P_ECDSA->p_sign_decode
#define ecdsa_sign_encode    _P_ECDSA->p_sign_encode
#define ecdsa_key_encode     _P_ECDSA->p_key_encode
#define ecdsa_key_decode     _P_ECDSA->p_key_decode
#define ecdsa_dh             _P_ECDSA->p_dh
#define ecdsa_dh_gen         _P_ECDSA->p_dh_gen
#define ecdsa_dh_ex          _P_ECDSA->p_dh_ex
#define ecdsa_dh_gen_ex      _P_ECDSA->p_dh_gen_ex
#define ecdsa_ecies_encrypt  _P_ECDSA->p_ecies_encrypt
#define ecdsa_ecies_decrypt  _P_ECDSA->p_ecies_decrypt
#define ecdsa_bulk_sign      _P_ECDSA->p_bulk_sign
#define ecdsa_tokengen       _P_ECDSA->p_ecdsa_tokengen
#define ecdsa_sign_edwards           _P_ECDSA->p_sign_edwards
#define ecdsa_verify_edwards         _P_ECDSA->p_verify_edwards
#define ecdsa_key_encode_rfc8410     _P_ECDSA->p_key_encode_rfc8410
#define ecdsa_key_decode_rfc8410     _P_ECDSA->p_key_decode_rfc8410
#define ecdsa_agree_secret_tr03111   _P_ECDSA->p_ecdsa_agree_secret_tr03111
#endif /* _ECDSA_C_INT_ */




/* Error Codes:  (0xB0000000 | (ECDSA_MDL_ID << 16) | (errno))  */

/* --- BEGIN ERROR CODES --- */

#define E_ECDSA                        0xB09C     /* CryptoServer module ECDSA                    */
#define E_ECDSA_MEM                    0xB09C0001 /* cannot allocate memory                       */
#define E_ECDSA_R_S_IS_NULL            0xB09C0002 /* null component in signature (r,s)            */
#define E_ECDSA_INV_FLAG               0xB09C0003 /* value for flags is invalid                   */
#define E_ECDSA_BAD_KEY                0xB09C0004 /* private and public key do not correspond     */
#define E_ECDSA_BAD_PKEY               0xB09C0005 /* bad public key                               */
#define E_ECDSA_BAD_SKEY               0xB09C0006 /* bad private key                              */
#define E_ECDSA_VERIFY_FAILED          0xB09C0007 /* signature verification failed                */
#define E_ECDSA_BAD_SIGN_FMT           0xB09C0008 /* bad format of signature                      */
#define E_ECDSA_NO_ASN1                0xB09C0009 /* no ASN.1 module loaded                       */
#define E_ECDSA_BUFF_TOO_SMALL         0xB09C000A /* buffer for result is to small                */
#define E_ECDSA_BAD_KEY_FMT            0xB09C000B /* malformed ASN.1 coded key pair               */
#define E_ECDSA_ECIES_PARAM            0xB09C000C /* bad parameter                                */
#define E_ECDSA_ECIES_MAC_CHECK        0xB09C000D /* mac check of ecies encrypted data failed     */
#define E_ECDSA_NO_AES                 0xB09C000E /* no AES module loaded                         */
#define E_ECDSA_KEYGEN_TEST            0xB09C000F /* pairwise consistency check failed on keygen  */
#define E_ECDSA_ZERO_LEN               0xB09C0010 /* Zero length not allowed                      */
#define E_ECDSA_NO_SEC_MODE            0xB09C0011 /* secure mode of curve not available           */
#define E_ECDSA_BULK_MAX               0xB09C0012 /* count of signatures per command exceeds limit*/
#define E_ECDSA_BAD_HASH_ALGO          0xB09C0013 /* bad hash algorithm                           */
#define E_ECDSA_BAD_MAC1_MAC_LEN       0xB09C0014 /* bad MAC1 mac/digest length (<4 or >default)  */
#define E_ECDSA_NO_DEFAULT_LEN         0xB09C0015 /* No default length for hash algorithm (SHAKE*)*/
#define E_ECDSA_BAD_PARAM              0xB09C0016 /* bad input parameter                          */
#define E_ECDSA_WRONG_DATA_SIZE        0xB09C0017 /* memory size mismatch                         */
#define E_ECDSA_NOT_SUPP               0xB09C0018 /* not supported                                */ 
#define E_ECDSA_OBSOLETE               0xB09C0019 /* function obsolete                            */
#define E_ECDSA_ALL_ZERO               0xB09C001A /* all-zero result                              */
#define E_ECDSA_KGEN_FAILED            0xB09C001B /* key generation failed                        */

/* --- END ERROR CODES --- */





#endif /* __ECDSA_H_PUB_INCLUDED__ */

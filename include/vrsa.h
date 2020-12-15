/*****************************************************************************
 *
 *  $File Identification                    $
 *  $Filename          : vrsa.h             $
 *  $Module version    : x.x.x.x            $
 *  $Module name       : VRSA               $
 *  $Release Date      : DD.MM.YYYY         $
 *
 *  Author(s)   : Rudolf Winschuh
 *                Rainer Herbertz
 *                Utimaco AG
 *
 *  Description : Global header file of CS2000 module VRSA
 *                Must be included in every CS2000 software that uses
 *                functions of this module
 *
 *  History     :
 *  Date       |                 Action                          |  Author
 *  -----------|-------------------------------------------------|---------
 *  26.04.2001 | Creation                                        |  R.W.
 *  26.09.2003 | Function for Blinding added                     |  R.H.
 *  27.01.2004 | New Funktion vrsa_chk_size()                    |  R.H.
 *  09.01.2006 | Added OAEP padding                              |  RVE
 *****************************************************************************/


#ifndef __VRSA_H_PUB_INCLUDED__
  #define __VRSA_H_PUB_INCLUDED__

#include "os_mdl.h"


/* module identification: */

#define VRSA_MDL_ID          0x84                /* ID of the module                             */
#define VRSA_MDL_NAME        "VRSA"              /* Short name of the module                     */

#ifdef CS2_SDK
    #define VRSA_MDL_NAMEX   "RSA Module SDK"    /* Long name of the module                      */
#else
    #ifdef DEBUG
    #define VRSA_MDL_NAMEX   "RSA Module DEBUG"  /* Long name of the module                      */
    #else
    #define VRSA_MDL_NAMEX   "RSA Module"        /* Long name of the module                      */
    #endif
#endif
                                                 /* Version of the module                        */
#define VRSA_MDL_VERSION     0x01030700


/* flags for vrsa_tcrypt: */

#define VRSA_MODE_PUBLIC     0x01                /* do a public key operation                    */
#define VRSA_MODE_PRIVATE    0x02                /* do a private key operation                   */

/* defines for blinding mechanisms                                                                */

#define VRSA_BLIND_NO_BL        0                /* use no blinding                               */
#define VRSA_BLIND_BME_BL       1                /* blind basis, modulus and exponent             */

/* flags for vrsa_xgen: */

#define VRSA_MODE_REAL_RND     0x00                /* use real random generator                     */
#define VRSA_MODE_PSEUDO_RND   0x01                /* use pseudo random generator                   */

#define VRSA_MODE_PROB_PRIME   0x00                /* generate probably prime's                     */
#define VRSA_MODE_PROV_PRIME   0x02                /* generate proven prime's                       */
#define VRSA_MODE_ANSI_PRIME   0x04                /* generate probably prime's (ANSI X9.31)        */
#define VRSA_MODE_FIPS_PRIME   0x08                /* generate probably prime with conditions based
                                                    on auxiliary probable primes (FIPS 186-4)       */
#define VRSA_MODE_MASK         0x0e                /* mask for mode                                 */

#define VRSA_FLAG_P_GREATER_Q  0x10                /* determines p-q-relation in final key          */

/* flags for vrsa_x9_31_sign + vrsa_x9_31_verify: */

#define VRSA_MODE_RAW(len)   (0x10000 | (len))



/* flags indicating the components of a RSA key token */

#define VRSA_KC_MOD          0x01                /* modulus of RSA key                           */
#define VRSA_KC_EXP          0x02                /* Exponent (public exponent)                   */
#define VRSA_KC_EXP2         0x04                /* Second exponent (secret)                     */
#define VRSA_KC_P            0x08                /* Prime p                                      */
#define VRSA_KC_Q            0x10                /* Prime q                                      */
#define VRSA_KC_U            0x20                /* u  := (1 / q) mod p                          */
#define VRSA_KC_DP           0x40                /* dP := d mod (p - 1)                          */
#define VRSA_KC_DQ           0x80                /* dQ := d mod (q - 1)                          */
#define VRSA_KC_END          0x00                /* end-mark of parameter list                   */
                                                 /* of function vrsa_mk_token                    */
#define VRSA_KC_ALL          0xFF
#define VRSA_KC_PUB          ( VRSA_KC_MOD | VRSA_KC_EXP )
#define VRSA_KC_PRV          ( VRSA_KC_P | VRSA_KC_Q | VRSA_KC_U | VRSA_KC_DP | VRSA_KC_DQ | VRSA_KC_EXP2 )
#define VRSA_KC_PRV_SHORTCUT ( VRSA_KC_P | VRSA_KC_Q | VRSA_KC_U | VRSA_KC_DP | VRSA_KC_DQ )



#define vrsa_get_bl_size(x)     (((*(x) & 0xffff) << 3) + 4)


/* public interface: */

typedef struct
{
    void   *p_data;
    int    (*p_start)(T_OS_MDL_HDL,void *, void*);
    int    (*p_stop)(void);
    int    (*p_pre_replace)(void);
    int    (*p_pre_delete)(void);
    void   *p_dumy;
    const void   *p_module_info;

    int    (*p_scrypt)( unsigned int l_mod, unsigned char* p_mod, unsigned int l_exp, unsigned char* p_exp,
                        unsigned int l_data, unsigned char* p_data, unsigned int l_max_res, unsigned int* p_l_res,
                        unsigned char* p_res );
    int    (*p_xcrypt)( unsigned int l_p, unsigned char* p_p, unsigned int l_q, unsigned char* p_q,
                        unsigned int l_u, unsigned char* p_u, unsigned int l_dp, unsigned char* p_dp,
                        unsigned int l_dq, unsigned char* p_dq, unsigned int l_data, unsigned char* p_data,
                        unsigned int l_max_res, unsigned int*  p_l_res, unsigned char* p_res );
    int    (*p_tcrypt)( unsigned char* p_keyt, int flags, unsigned int l_data, unsigned char* p_data,
                        unsigned int l_max_res, unsigned int* p_l_res, unsigned char* p_res );
    int    (*p_xgen)  ( unsigned int size, unsigned int pq_diff, unsigned int mode,
                        unsigned int  l_exp, unsigned char* p_exp,
                        unsigned int* p_l_mod, unsigned char* p_mod, unsigned int* p_l_exp2, unsigned char* p_exp2,
                        unsigned int* p_l_p, unsigned char* p_p, unsigned int* p_l_q, unsigned char* p_q,
                        unsigned int* p_l_u, unsigned char* p_u, unsigned int* p_l_dp, unsigned char* p_dp,
                        unsigned int* p_l_dq, unsigned char* p_dq );
    int    (*p_tgen)  ( unsigned int size, unsigned int pq_diff, unsigned int mode,
                        unsigned int l_exp, unsigned char* p_exp,
                        int flags, unsigned char** pp_pubkeyt, unsigned char** pp_seckeyt );
    int    (*p_get_comp)( int component, unsigned char* p_keyt, unsigned int* p_l_component, unsigned char** pp_component );
    int    (*p_mk_token)( unsigned char** pp_keyt, int memtype, ... );
    int    (*p_get_size)( unsigned char* keyt );
    int    (*p_dumy1)   (void);
    int    (*p_tchk)  ( unsigned char* p_keyt, int flags );
    int    (*p_pkcs1_sign)( unsigned char *p_keyt, int hash_algo, unsigned char *p_hash, unsigned int l_max_sign,
                            unsigned int *p_l_sign, unsigned char *p_sign );
    int    (*p_pkcs1_verify)( unsigned char *p_keyt, int hash_algo, unsigned char *p_hash, unsigned int l_sign,
                              unsigned char *p_sign );
    int    (*p_xget_keysize)( unsigned int l_p, unsigned char *p_p, unsigned int l_q, unsigned char *p_q,
                              unsigned int *keysize );
    int    (*p_tget_keysize)( unsigned char *p_keytoken, unsigned int *keysize );
    int    (*p_xchk)  (unsigned int l_mod, unsigned char* p_mod, unsigned int l_exp, unsigned char* p_exp,
                       unsigned int l_exp2, unsigned char* p_exp2,
                       unsigned int l_p, unsigned char* p_p, unsigned int l_q, unsigned char* p_q,
                       unsigned int l_u, unsigned char* p_u, unsigned int l_dp, unsigned char* p_dp,
                       unsigned int l_dq, unsigned char* p_dq );
    int    (*p_tchk2) ( unsigned char* p_keyt1, unsigned char* p_keyt2, int flags );
    int    (*p_tcrypt2)( unsigned char* p_keyt1, unsigned char* p_keyt2, int flags,
                         unsigned int l_data, unsigned char* p_data,
                         unsigned int l_max_res, unsigned int* p_l_res, unsigned char* p_res );
    int    (*p_bv_xgen)(unsigned int,unsigned int,unsigned char*,
                        unsigned int,unsigned char*,unsigned int,unsigned char*,
                        unsigned int,unsigned char*,unsigned int **);
    int    (*p_bv_tgen)(unsigned int mode,unsigned char  *p_keyt1,
                        unsigned char  *p_keyt2,unsigned int **pp_bv);
    int    (*p_scrypt_bl)( unsigned int l_mod, unsigned char* p_mod, unsigned int l_exp, unsigned char* p_exp,
                           unsigned int l_data, unsigned char* p_data, unsigned int l_max_res, unsigned int* p_l_res,
                           unsigned char* p_res, unsigned int *p_bv );
    int    (*p_xcrypt_bl)( unsigned int l_p, unsigned char* p_p, unsigned int l_q, unsigned char* p_q,
                           unsigned int l_u, unsigned char* p_u, unsigned int l_dp, unsigned char* p_dp,
                           unsigned int l_dq, unsigned char* p_dq, unsigned int l_data, unsigned char* p_data,
                           unsigned int l_max_res, unsigned int*  p_l_res, unsigned char* p_res,
                           unsigned int *p_bv );
    int    (*p_tcrypt_bl)( unsigned char* p_keyt, int flags, unsigned int l_data, unsigned char* p_data,
                           unsigned int l_max_res, unsigned int* p_l_res, unsigned char* p_res,
                           unsigned int *p_bv );
    int    (*p_tcrypt2_bl)( unsigned char* p_keyt1, unsigned char* p_keyt2, int flags,
                            unsigned int l_data, unsigned char* p_data,
                            unsigned int l_max_res, unsigned int* p_l_res, unsigned char* p_res,
                            unsigned int *p_bv );
    int    (*p_pkcs1_sign_bl)( unsigned char *p_keyt, int hash_algo, unsigned char *p_hash, unsigned int l_max_sign,
                               unsigned int *p_l_sign, unsigned char *p_sign, unsigned int *p_bv );
    int    (*p_x9_31_sign)( unsigned char *p_keyt, int hash_algo, unsigned char *p_hash, unsigned int l_max_sign,
                            unsigned int *p_l_sign, unsigned char *p_sign );
    int    (*p_x9_31_verify)( unsigned char *p_keyt, int hash_algo, unsigned char *p_hash, unsigned int l_sign,
                              unsigned char *p_sign );
    int    (*p_x9_31_sign_bl)( unsigned char *p_keyt, int hash_algo, unsigned char *p_hash, unsigned int l_max_sign,
                               unsigned int *p_l_sign, unsigned char *p_sign, unsigned int *p_bv );
    int    (*p_pkcs1_encrypt)( unsigned char *p_keyt,unsigned int l_data,unsigned char *p_data,
                               unsigned int l_max_crypto,unsigned int *p_l_crypto,unsigned char *p_crypto);
    int    (*p_pkcs1_decrypt)( unsigned char *p_keyt,unsigned int l_crypto,unsigned char *p_crypto,
                               unsigned int *p_l_data,unsigned char **pp_data);
    int    (*p_pkcs1_decrypt_bl)( unsigned char *p_keyt,unsigned int l_crypto,unsigned char *p_crypto,
                                  unsigned int *p_l_data,unsigned char **pp_data, unsigned int *p_bv);
    int    (*p_chk_size)( unsigned char* keyt, unsigned int max, unsigned int *p_len );

    int    (*p_vrsa_pkcs1_eme_oaep_encrypt)(unsigned char *p_keyt, int hash_algo, int mgf_hash, unsigned int l_label,
                                            unsigned char *p_label,unsigned int l_data, unsigned char *p_data,
                                            unsigned int l_max_res, unsigned int *p_l_res, unsigned char *p_res);
    int    (*p_vrsa_pkcs1_eme_oaep_decrypt)(unsigned char *p_keyt, int hash_algo, int mgf_hash,  unsigned int l_label,
                                            unsigned char *p_label, unsigned int l_enc_data, unsigned char *p_enc_data,
                                            unsigned int l_max_data, unsigned int *p_l_data, unsigned char *p_data);
    int    (*p_vrsa_pkcs1_pss_sign)        (unsigned char *p_keyt, int hash_algo, int mgf_hash, unsigned int l_hash,
                                            unsigned char *p_hash, unsigned int l_salt, unsigned int l_max_sign,
                                            unsigned int *p_l_sign, unsigned char *p_sign);
    int    (*p_vrsa_pkcs1_pss_verify)      (unsigned char *p_keyt, int hash_algo, int mgf_hash, unsigned int l_hash,
                                            unsigned char *p_hash, unsigned int l_salt, unsigned int l_sign,
                                            unsigned char *p_sign);
    int    (*p_vrsa_pkcs1_eme_oaep_decrypt_bl)(unsigned char *p_keyt, int hash_algo, int mgf_hash,  unsigned int l_label,
                                            unsigned char *p_label, unsigned int l_enc_data, unsigned char *p_enc_data,
                                            unsigned int l_max_data, unsigned int *p_l_data, unsigned char *p_data,
                                            unsigned int *p_bv);
    int    (*p_vrsa_pkcs1_pss_sign_bl)     (unsigned char *p_keyt, int hash_algo, int mgf_hash, unsigned int l_hash,
                                            unsigned char *p_hash, unsigned int l_salt, unsigned int l_max_sign,
                                            unsigned int *p_l_sign, unsigned char *p_sign, unsigned int *p_bv);
    int    (*p_vrsa_calc_xkey)             (unsigned int mode, unsigned int l_exp, unsigned char* p_exp,
                                            unsigned int l_p, unsigned char* p_p, unsigned int l_q, unsigned char* p_q,
                                            unsigned int* p_l_mod, unsigned char* p_mod, unsigned int* p_l_exp2, unsigned char* p_exp2,
                                            unsigned int* p_l_u, unsigned char* p_u, unsigned int*  p_l_dp, unsigned char* p_dp,
                                            unsigned int*  p_l_dq, unsigned char* p_dq);
    int    (*p_bulk_tcrypt)                (unsigned char *p_keyt,unsigned int flags,unsigned int ct,unsigned int l_data[],
                                            unsigned char *data_in[], unsigned int l_out,unsigned char *data_out[]);
    int    (*p_bulk_pkcs1_sign)            (unsigned char *p_keyt,int hash_algo,unsigned int ct,unsigned char  *p_hash[],
                                            unsigned int l_out,unsigned char  *data_out[]);
    int    (*p_xcrypt_blind)               ( unsigned int l_p, unsigned char* p_p, unsigned int l_q
                                           , unsigned char* p_q, unsigned int l_u, unsigned char* p_u
                                           , unsigned int l_dp, unsigned char* p_dp, unsigned int l_dq
                                           , unsigned char* p_dq, unsigned int l_data, unsigned char* p_data
                                           , unsigned int l_max_res, unsigned int*  p_l_res, unsigned char* p_res );
    int    (*p_scrypt_blind)               ( unsigned int l_mod, unsigned char* p_mod, unsigned int l_exp, unsigned char* p_exp
                                           , unsigned int l_data, unsigned char* p_data, unsigned int l_max_res, unsigned int* p_l_res
                                           , unsigned char* p_res );
    int    (*p_tcrypt_blind)               ( unsigned char* p_keyt, int flags, unsigned int l_data
                                           , unsigned char* p_data, unsigned int l_max_res
                                           , unsigned int* p_l_res, unsigned char* p_res);
    int    (*p_tcrypt2_blind)              ( unsigned char* p_keyt1, unsigned char* p_keyt2
                                           , int flags, unsigned int l_data, unsigned char* p_data
                                           , unsigned int l_max_res, unsigned int* p_l_res
                                           , unsigned char* p_res);

    int    (*p_scrypt_ex)( unsigned int l_mod, unsigned char* p_mod, unsigned int l_exp, unsigned char* p_exp
                         , unsigned int l_data, unsigned char* p_data, void *p_bl, unsigned int l_max_res
                         , unsigned int* p_l_res, unsigned char* p_res );
    int    (*p_xcrypt_ex)( unsigned int l_p, unsigned char* p_p, unsigned int l_q, unsigned char* p_q
                         , unsigned int l_u, unsigned char* p_u, unsigned int l_dp, unsigned char* p_dp
                         , unsigned int l_dq, unsigned char* p_dq, unsigned int l_data, unsigned char* p_data
                         , void *p_bl, unsigned int l_max_res, unsigned int*  p_l_res, unsigned char* p_res );
    int    (*p_tcrypt_ex)( unsigned char* p_keyt, int flags, unsigned int l_data, unsigned char* p_data
                         , void *p_bl, unsigned int l_max_res, unsigned int* p_l_res, unsigned char* p_res );
    int    (*p_tcrypt2_ex)( unsigned char* p_keyt1, unsigned char* p_keyt2, int flags
                          , unsigned int l_data, unsigned char* p_data
                          , void *p_bl, unsigned int l_max_res, unsigned int* p_l_res, unsigned char* p_res );
    int    (*p_pkcs1_sign_ex)( unsigned char *p_keyt, int hash_algo, unsigned char *p_hash, void *p_bl
                             , unsigned int l_max_sign, unsigned int *p_l_sign, unsigned char *p_sign );
    int    (*p_x9_31_sign_ex)( unsigned char *p_keyt, int hash_algo, unsigned char *p_hash, void *p_bl
                             , unsigned int l_max_sign, unsigned int *p_l_sign, unsigned char *p_sign );
    int    (*p_pkcs1_decrypt_ex)( unsigned char *p_keyt,unsigned int l_crypto,unsigned char *p_crypto
                                , void *p_bl, unsigned int *p_l_data, unsigned char **pp_data);
    int    (*p_pkcs1_eme_oaep_decrypt_ex)( unsigned char *p_keyt, int hash_algo, int mgf_hash,  unsigned int l_label
                                              , unsigned char *p_label, unsigned int l_enc_data, unsigned char *p_enc_data
                                              , void *p_bl, unsigned int l_max_data, unsigned int *p_l_data, unsigned char *p_data);
    int    (*p_pkcs1_pss_sign_ex)( unsigned char *p_keyt, int hash_algo, int mgf_hash, unsigned int l_hash
                                      , unsigned char *p_hash, unsigned int l_salt, void *p_bl
                                      , unsigned int l_max_sign, unsigned int *p_l_sign, unsigned char *p_sign);
   int     (*p_vrsa_tokengen) ( const unsigned int size, unsigned int pq_diff, const unsigned int mode, unsigned int l_exp,
                                unsigned char* p_exp, int flags, unsigned int* const p_l_pubkeyt, unsigned char* const p_pubkeyt,
                                unsigned int* p_l_seckeyt, unsigned char* const p_seckeyt);

} T_VRSA_TABLE_PUB;



#ifdef _VRSA_C_INT_

/* function prototypes used by the module (internal) */

int  vrsa_start(T_OS_MDL_HDL,void *,void *);
int  vrsa_pre_replace(void);
int  vrsa_pre_delete(void);

int vrsa_scrypt( unsigned int l_mod, unsigned char* p_mod, unsigned int l_exp, unsigned char* p_exp,
                 unsigned int l_data, unsigned char* p_data, unsigned int l_max_res, unsigned int* p_l_res,
                 unsigned char* p_res );
int vrsa_xcrypt( unsigned int l_p,  unsigned char* p_p,  unsigned int l_q,    unsigned char* p_q,
                 unsigned int l_u,  unsigned char* p_u,  unsigned int l_dp,   unsigned char* p_dp,
                 unsigned int l_dq, unsigned char* p_dq, unsigned int l_data, unsigned char* p_data,
                 unsigned int l_max_res, unsigned int*  p_l_res, unsigned char* p_res );
int vrsa_tcrypt( unsigned char* p_keyt, int flags, unsigned int l_data, unsigned char* p_data,
                 unsigned int l_max_res, unsigned int* p_l_res, unsigned char* p_res );
int vrsa_tcrypt2( unsigned char* p_keyt1, unsigned char* p_keyt2, int flags,
                  unsigned int l_data, unsigned char* p_data,
                  unsigned int l_max_res, unsigned int* p_l_res, unsigned char* p_res );
int vrsa_xgen( unsigned int  size,    unsigned int pq_diff, unsigned int mode,
               unsigned int  l_exp,   unsigned char* p_exp,
               unsigned int* p_l_mod, unsigned char* p_mod, unsigned int* p_l_exp2, unsigned char* p_exp2,
               unsigned int* p_l_p,   unsigned char* p_p,   unsigned int* p_l_q,    unsigned char* p_q,
               unsigned int* p_l_u,   unsigned char* p_u,   unsigned int* p_l_dp,   unsigned char* p_dp,
               unsigned int* p_l_dq,  unsigned char* p_dq );
int vrsa_tgen( unsigned int  size,    unsigned int pq_diff, unsigned int mode,
               unsigned int  l_exp,    unsigned char* p_exp,
               int flags, unsigned char** pp_pubkeyt, unsigned char** pp_seckeyt );
int vrsa_get_comp ( int component, unsigned char* p_keyt, unsigned int* p_l_component, unsigned char** pp_component );
int vrsa_mk_token ( unsigned char** pp_keyt, int memtype, ... );
int vrsa_get_size ( unsigned char* p_keyt );
int vrsa_chk_size ( unsigned char* p_keyt, unsigned int max, unsigned int *p_len);
int vrsa_xchk ( unsigned int l_mod, unsigned char* p_mod, unsigned int l_exp, unsigned char* p_exp,
                unsigned int l_exp2, unsigned char* p_exp2,
                unsigned int l_p, unsigned char* p_p, unsigned int   l_q, unsigned char* p_q,
                unsigned int   l_u, unsigned char* p_u, unsigned int   l_dp, unsigned char* p_dp,
                unsigned int   l_dq, unsigned char* p_dq );
int vrsa_tchk ( unsigned char* p_keyt, int flags );
int vrsa_tchk2 ( unsigned char* p_keyt1, unsigned char* p_keyt2, int flags );
int vrsa_pkcs1_sign( unsigned char *p_keyt, int hash_algo, unsigned char *p_hash, unsigned int l_max_sign,
                     unsigned int *p_l_sign, unsigned char *p_sign );
int vrsa_pkcs1_sign_bl( unsigned char *p_keyt, int hash_algo, unsigned char *p_hash, unsigned int l_max_sign,
                        unsigned int *p_l_sign, unsigned char *p_sign, unsigned int *p_bv );
int vrsa_pkcs1_verify( unsigned char *p_keyt, int hash_algo, unsigned char *p_hash, unsigned int l_sign,
                       unsigned char *p_sign );
int vrsa_xget_keysize( unsigned int l_p, unsigned char *p_p, unsigned int l_q, unsigned char *p_q,
                       unsigned int *keysize );
int vrsa_tget_keysize( unsigned char *p_keytoken, unsigned int *keysize );

int vrsa_bv_xgen(unsigned int,unsigned int,unsigned char*,
                 unsigned int,unsigned char*,unsigned int,unsigned char*,
                 unsigned int,unsigned char*,unsigned int **);

int vrsa_bv_tgen(unsigned int mode,unsigned char  *p_keyt1,
                 unsigned char  *p_keyt2,unsigned int **pp_bv);

int vrsa_scrypt_bl( unsigned int l_mod, unsigned char* p_mod, unsigned int l_exp, unsigned char* p_exp,
                    unsigned int l_data, unsigned char* p_data, unsigned int l_max_res, unsigned int* p_l_res,
                    unsigned char* p_res, unsigned int *);

int vrsa_xcrypt_bl( unsigned int l_p,  unsigned char* p_p,  unsigned int l_q,    unsigned char* p_q,
                    unsigned int l_u,  unsigned char* p_u,  unsigned int l_dp,   unsigned char* p_dp,
                    unsigned int l_dq, unsigned char* p_dq, unsigned int l_data, unsigned char* p_data,
                    unsigned int l_max_res, unsigned int*  p_l_res, unsigned char* p_res, unsigned int *);

int vrsa_tcrypt_bl( unsigned char* p_keyt, int flags, unsigned int l_data, unsigned char* p_data,
                    unsigned int l_max_res, unsigned int* p_l_res, unsigned char* p_res,
                    unsigned int *p_bv );
int vrsa_tcrypt2_bl( unsigned char* p_keyt1, unsigned char* p_keyt2, int flags,
                     unsigned int l_data, unsigned char* p_data,
                     unsigned int l_max_res, unsigned int* p_l_res, unsigned char* p_res,
                     unsigned int *p_bv );
int vrsa_x9_31_sign( unsigned char *p_keyt, int hash_algo, unsigned char *p_hash, unsigned int l_max_sign,
                     unsigned int *p_l_sign, unsigned char *p_sign );
int vrsa_x9_31_sign_bl( unsigned char *p_keyt, int hash_algo, unsigned char *p_hash, unsigned int l_max_sign,
                        unsigned int *p_l_sign, unsigned char *p_sign, unsigned int *p_bv );
int vrsa_x9_31_verify( unsigned char *p_keyt, int hash_algo, unsigned char *p_hash, unsigned int l_sign,
                       unsigned char *p_sign );
int vrsa_pkcs1_encrypt( unsigned char *p_keyt,unsigned int l_data,unsigned char *p_data,
                        unsigned int l_max_crypto,unsigned int *p_l_crypto,unsigned char *p_crypto);
int vrsa_pkcs1_decrypt( unsigned char *p_keyt,unsigned int l_crypto,unsigned char *p_crypto,
                        unsigned int *p_l_data,unsigned char **pp_data);
int vrsa_pkcs1_decrypt_bl( unsigned char *p_keyt,unsigned int l_crypto,unsigned char *p_crypto,
                           unsigned int *p_l_data,unsigned char **pp_data,unsigned int *p_bv);
int vrsa_pkcs1_eme_oaep_encrypt( unsigned char *p_keyt, int hash_algo, int mgf_hash,  unsigned int l_label,
                                 unsigned char *p_label, unsigned int l_data, unsigned char *p_data,
                                 unsigned int l_max_res, unsigned int *p_l_res, unsigned char *p_res);
int vrsa_pkcs1_eme_oaep_decrypt( unsigned char *p_keyt, int hash_algo, int mgf_hash, unsigned int l_label,
                                 unsigned char *p_label, unsigned int l_enc_data, unsigned char *p_enc_data,
                                 unsigned int l_max_data, unsigned int *p_l_data, unsigned char   *p_data);
int vrsa_pkcs1_pss_sign        ( unsigned char *p_keyt, int hash_algo, int mgf_hash, unsigned int l_hash,
                                 unsigned char *p_hash, unsigned int l_salt, unsigned int l_max_sign,
                                 unsigned int *p_l_sign, unsigned char *p_sign);
int vrsa_pkcs1_pss_verify      ( unsigned char *p_keyt, int hash_algo, int mgf_hash, unsigned int l_hash,
                                 unsigned char *p_hash, unsigned int l_salt, unsigned int l_sign,
                                 unsigned char *p_sign);
int vrsa_pkcs1_eme_oaep_decrypt_bl(unsigned char *p_keyt, int hash_algo, int mgf_hash,  unsigned int l_label,
                                 unsigned char *p_label, unsigned int l_enc_data, unsigned char *p_enc_data,
                                 unsigned int l_max_data, unsigned int *p_l_data, unsigned char *p_data,
                                 unsigned int *p_bv);
int vrsa_pkcs1_pss_sign_bl     ( unsigned char *p_keyt, int hash_algo, int mgf_hash, unsigned int l_hash,
                                 unsigned char *p_hash, unsigned int l_salt, unsigned int l_max_sign,
                                 unsigned int *p_l_sign, unsigned char *p_sign, unsigned int *p_bv);
int vrsa_calc_xkey             ( unsigned int mode, unsigned int l_exp, unsigned char* p_exp,
                                 unsigned int l_p, unsigned char* p_p, unsigned int l_q, unsigned char* p_q,
                                 unsigned int* p_l_mod, unsigned char* p_mod, unsigned int* p_l_exp2, unsigned char* p_exp2,
                                 unsigned int* p_l_u, unsigned char* p_u, unsigned int*  p_l_dp, unsigned char* p_dp,
                                 unsigned int*  p_l_dq, unsigned char* p_dq);
int vrsa_bulk_tcrypt           ( unsigned char *p_keyt,unsigned int flags,unsigned int ct,unsigned int l_data[],
                                 unsigned char *data_in[], unsigned int l_out,unsigned char *data_out[]);
int vrsa_bulk_pkcs1_sign       ( unsigned char *p_keyt,int hash_algo,unsigned int ct,unsigned char  *p_hash[],
                                 unsigned int l_out,unsigned char  *data_out[]);
int vrsa_xcrypt_blind          ( unsigned int l_p, unsigned char* p_p, unsigned int l_q
                               , unsigned char* p_q, unsigned int l_u, unsigned char* p_u
                               , unsigned int l_dp, unsigned char* p_dp, unsigned int l_dq
                               , unsigned char* p_dq, unsigned int l_data, unsigned char* p_data
                               , unsigned int l_max_res, unsigned int* p_l_res, unsigned char* p_res);
int vrsa_scrypt_blind          ( unsigned int l_mod, unsigned char* p_mod, unsigned int l_exp
                               , unsigned char* p_exp, unsigned int l_data, unsigned char* p_data
                               , unsigned int l_max_res, unsigned int* p_l_res, unsigned char* p_res);
int vrsa_tcrypt_blind          ( unsigned char* p_keyt, int flags, unsigned int l_data
                               , unsigned char* p_data, unsigned int l_max_res
                               , unsigned int* p_l_res, unsigned char* p_res);
int vrsa_tcrypt2_blind         ( unsigned char* p_keyt1, unsigned char* p_keyt2, int flags
                               , unsigned int l_data, unsigned char* p_data, unsigned int l_max_res
                               , unsigned int* p_l_res, unsigned char* p_res);

int vrsa_scrypt_ex             ( unsigned int l_mod, unsigned char* p_mod, unsigned int l_exp, unsigned char* p_exp
                               , unsigned int l_data, unsigned char* p_data, void *p_bl, unsigned int l_max_res
                               , unsigned int* p_l_res, unsigned char* p_res );
int vrsa_xcrypt_ex             ( unsigned int l_p, unsigned char* p_p, unsigned int l_q, unsigned char* p_q
                               , unsigned int l_u, unsigned char* p_u, unsigned int l_dp, unsigned char* p_dp
                               , unsigned int l_dq, unsigned char* p_dq, unsigned int l_data, unsigned char* p_data
                               , void *p_bl, unsigned int l_max_res, unsigned int*  p_l_res, unsigned char* p_res );
int vrsa_tcrypt_ex             ( unsigned char* p_keyt, int flags, unsigned int l_data, unsigned char* p_data
                               , void *p_bl, unsigned int l_max_res, unsigned int* p_l_res, unsigned char* p_res );
int vrsa_tcrypt2_ex            ( unsigned char* p_keyt1, unsigned char* p_keyt2, int flags
                               , unsigned int l_data, unsigned char* p_data, void *p_bl
                               , unsigned int l_max_res, unsigned int* p_l_res, unsigned char* p_res );
int vrsa_pkcs1_sign_ex         ( unsigned char *p_keyt, int hash_algo, unsigned char *p_hash, void *p_bl
                               , unsigned int l_max_sign, unsigned int *p_l_sign, unsigned char *p_sign );
int vrsa_x9_31_sign_ex         ( unsigned char *p_keyt, int hash_algo, unsigned char *p_hash, void *p_bl
                               , unsigned int l_max_sign, unsigned int *p_l_sign, unsigned char *p_sign );
int vrsa_pkcs1_decrypt_ex      ( unsigned char *p_keyt,unsigned int l_crypto,unsigned char *p_crypto
                               , void *p_bl, unsigned int *p_l_data, unsigned char **pp_data );
int vrsa_pkcs1_eme_oaep_decrypt_ex  ( unsigned char *p_keyt, int hash_algo, int mgf_hash,  unsigned int l_label
                                    , unsigned char *p_label, unsigned int l_enc_data, unsigned char *p_enc_data
                                    , void *p_bl, unsigned int l_max_data, unsigned int *p_l_data, unsigned char *p_data);
int vrsa_pkcs1_pss_sign_ex     ( unsigned char *p_keyt, int hash_algo, int mgf_hash, unsigned int l_hash
                               , unsigned char *p_hash, unsigned int l_salt, void *p_bl
                               , unsigned int l_max_sign, unsigned int *p_l_sign, unsigned char *p_sign);
int vrsa_tokengen                ( const unsigned int size, unsigned int pq_diff, const unsigned int mode, unsigned int l_exp,
                                   unsigned char* p_exp, int flags, unsigned int* const p_l_pubkeyt, unsigned char* const p_pubkeyt,
                                   unsigned int* const p_l_seckeyt, unsigned char* const p_seckeyt);

#else

/* external interface to be used by other modules */

extern MDL_GLOBAL T_OS_MDL_HDL P_VRSA;

#define _P_VRSA ((T_VRSA_TABLE_PUB *)P_VRSA)     /* shortcut                                     */

#define vrsa_scrypt                      _P_VRSA->p_scrypt
#define vrsa_xcrypt                      _P_VRSA->p_xcrypt
#define vrsa_tcrypt                      _P_VRSA->p_tcrypt
#define vrsa_tcrypt2                     _P_VRSA->p_tcrypt2
#define vrsa_xgen                        _P_VRSA->p_xgen
#define vrsa_tgen                        _P_VRSA->p_tgen
#define vrsa_get_comp                    _P_VRSA->p_get_comp
#define vrsa_mk_token                    _P_VRSA->p_mk_token
#define vrsa_get_size                    _P_VRSA->p_get_size
#define vrsa_chk_size                    _P_VRSA->p_chk_size
#define vrsa_xchk                        _P_VRSA->p_xchk
#define vrsa_tchk                        _P_VRSA->p_tchk
#define vrsa_tchk2                       _P_VRSA->p_tchk2
#define vrsa_pkcs1_sign                  _P_VRSA->p_pkcs1_sign
#define vrsa_pkcs1_sign_bl               _P_VRSA->p_pkcs1_sign_bl
#define vrsa_pkcs1_verify                _P_VRSA->p_pkcs1_verify
#define vrsa_xget_keysize                _P_VRSA->p_xget_keysize
#define vrsa_tget_keysize                _P_VRSA->p_tget_keysize
#define vrsa_bv_xgen                     _P_VRSA->p_bv_xgen
#define vrsa_bv_tgen                     _P_VRSA->p_bv_tgen
#define vrsa_scrypt_bl                   _P_VRSA->p_scrypt_bl
#define vrsa_xcrypt_bl                   _P_VRSA->p_xcrypt_bl
#define vrsa_tcrypt_bl                   _P_VRSA->p_tcrypt_bl
#define vrsa_tcrypt2_bl                  _P_VRSA->p_tcrypt2_bl
#define vrsa_x9_31_sign                  _P_VRSA->p_x9_31_sign
#define vrsa_x9_31_sign_bl               _P_VRSA->p_x9_31_sign_bl
#define vrsa_x9_31_verify                _P_VRSA->p_x9_31_verify
#define vrsa_pkcs1_encrypt               _P_VRSA->p_pkcs1_encrypt
#define vrsa_pkcs1_decrypt               _P_VRSA->p_pkcs1_decrypt
#define vrsa_pkcs1_decrypt_bl            _P_VRSA->p_pkcs1_decrypt_bl
#define vrsa_pkcs1_eme_oaep_encrypt      _P_VRSA->p_vrsa_pkcs1_eme_oaep_encrypt
#define vrsa_pkcs1_eme_oaep_decrypt      _P_VRSA->p_vrsa_pkcs1_eme_oaep_decrypt
#define vrsa_pkcs1_eme_oaep_decrypt_bl   _P_VRSA->p_vrsa_pkcs1_eme_oaep_decrypt_bl
#define vrsa_pkcs1_pss_sign              _P_VRSA->p_vrsa_pkcs1_pss_sign
#define vrsa_pkcs1_pss_sign_bl           _P_VRSA->p_vrsa_pkcs1_pss_sign_bl
#define vrsa_pkcs1_pss_verify            _P_VRSA->p_vrsa_pkcs1_pss_verify
#define vrsa_calc_xkey                   _P_VRSA->p_vrsa_calc_xkey
#define vrsa_bulk_tcrypt                 _P_VRSA->p_bulk_tcrypt
#define vrsa_bulk_pkcs1_sign             _P_VRSA->p_bulk_pkcs1_sign
#define vrsa_xcrypt_blind                _P_VRSA->p_xcrypt_blind
#define vrsa_scrypt_blind                _P_VRSA->p_scrypt_blind
#define vrsa_tcrypt_blind                _P_VRSA->p_tcrypt_blind
#define vrsa_tcrypt2_blind               _P_VRSA->p_tcrypt2_blind
#define vrsa_scrypt_ex                   _P_VRSA->p_scrypt_ex
#define vrsa_xcrypt_ex                   _P_VRSA->p_xcrypt_ex
#define vrsa_tcrypt_ex                   _P_VRSA->p_tcrypt_ex
#define vrsa_tcrypt2_ex                  _P_VRSA->p_tcrypt2_ex
#define vrsa_pkcs1_sign_ex               _P_VRSA->p_pkcs1_sign_ex
#define vrsa_x9_31_sign_ex               _P_VRSA->p_x9_31_sign_ex
#define vrsa_pkcs1_decrypt_ex            _P_VRSA->p_pkcs1_decrypt_ex
#define vrsa_pkcs1_eme_oaep_decrypt_ex   _P_VRSA->p_pkcs1_eme_oaep_decrypt_ex
#define vrsa_pkcs1_pss_sign_ex           _P_VRSA->p_pkcs1_pss_sign_ex
#define vrsa_tokengen                    _P_VRSA->p_vrsa_tokengen



#endif /* _VRSA_C_INT_ */




/* Error Codes:  (0xB0000000 | (VRSA_MDL_ID << 16) | (errno))  */

/* --- BEGIN ERROR CODES --- */

#define E_VRSA                        0xB084     /* CryptoServer module VRSA                     */
#define E_VRSA_MEM                    0xB0840001 /* cannot allocate memory                       */
#define E_VRSA_BUFF_TOO_SMALL         0xB0840002 /* buffer for result is to small                */
#define E_VRSA_BAD_DATA               0xB0840003 /* bad raw data value                           */
#define E_VRSA_BAD_MODULUS            0xB0840004 /* modulus is not p * q                         */
#define E_VRSA_BAD_U                  0xB0840009 /* u is not (1/q) mod p                         */
#define E_VRSA_BAD_DP                 0xB084000A /* dp is not d mod (p-1)                        */
#define E_VRSA_BAD_DQ                 0xB084000B /* dq is not d mod (q-1)                        */
#define E_VRSA_NO_KEYTOKEN            0xB084000C /* byte string is not a keytoken                */
#define E_VRSA_NO_COMP                0xB084000D /* component is not a member of this key token  */
#define E_VRSA_DOUBLE_COMP            0xB084000E /* component is already a member of this key token  */
#define E_VRSA_INVALID_FLAG           0xB084000F /* value for flags is invalid                   */
#define E_VRSA_HASH_ALGO              0xB0840010 /* Invalid hash algorithm                       */
#define E_VRSA_VERIFY_FAILED          0xB0840011 /* Signature verification failed                */
#define E_VRSA_KEY_TOO_SMALL          0xB0840012 /* Key length too small                         */
#define E_VRSA_PQDIFF_TOO_LARGE       0xB0840013 /* Value of pq_diff is too large                */
#define E_VRSA_MOD_TOO_SMALL          0xB0840014 /* modulus to small                             */
#define E_VRSA_BAD_KEY                0xB0840015 /* bad key components P and Q                   */
#define E_VRSA_DATA_LEN               0xB0840016 /* data size too big (greater than modulus)     */
#define E_VRSA_MISS_COMP              0xB0840017 /* missing component in key token               */
#define E_VRSA_INV_PARAM              0xB0840018 /* invalid parameter                            */
#define E_VRSA_BAD_PEXP               0xB0840019 /* gcd(p-1,e) != 1 or gcd(q-1,e) != 1           */
#define E_VRSA_BAD_SEXP               0xB084001A /* d * e != 1 mod (p-1)(q-1)                    */
#define E_VRSA_OBSOLETE               0xB084001B /* function obsolete                            */
#define E_VRSA_KGEN_FAILED            0xB084001C /* key generation failed                        */
#define E_VRSA_BAD_BLINDING           0xB084001D /* invalid blinding value                       */
#define E_VRSA_BVGEN_FAILED           0xB084001E /* blinding value generation failed             */
#define E_VRSA_DECRYPT_FAILED         0xB084001F /* PKCS#1 decryption failed                     */
#define E_VRSA_INV_PEXP               0xB0840020 /* invalid public exponent                      */
#define E_VRSA_KEYT_LEN               0xB0840021 /* bad length of key token                      */
#define E_VRSA_ENCODING               0xB0840022 /* PKCS#1 encoding error                        */
#define E_VRSA_PAIRWISE_CONSISTENCY   0xB0840023 /* The pairwise consistency test failed !       */
#define E_VRSA_FUNC_NOT_AVAILABLE     0xB0840024 /* Function is not available                    */
#define E_VRSA_BAD_BLINDING_MECH      0xB0840025 /* Blinding mechanism unknown                   */
#define E_VRSA_INP_BUFF_TOO_SMALL     0xB0840026 /* input buffer length too small                */

#define E_VRSA_BAD_KEYT               0xB0840100 /* bad key token in command string              */
#define E_VRSA_RND_SYNC               0xB0840101 /* random number request does not match (FIPS test) */
//#define E_VRSA_KEY_TOO_SMALL_FIPS     0xB0840102 /* Key length too small (FIPS140)               */
//#define E_VRSA_KEY_TOO_SMALL_CC       0xB0840103 /* Key length too small (CC)                    */

/* --- END ERROR CODES --- */


#define E_VRSA_MESSAGE_TOO_LONG       E_VRSA_KEY_TOO_SMALL /* Message too long as of PKCS#1 v2.1           */


#endif /* __VRSA_H_PUB_INCLUDED__ */


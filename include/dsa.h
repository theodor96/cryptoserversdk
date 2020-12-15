/*****************************************************************************
 *
 *  $File Identification                    $
 *  $Filename          : dsa.h              $
 *  $Module version    : x.x.x.x            $
 *  $Module name       : DSA                $
 *  $Release Date      : DD.MM.YYYY         $
 *
 *  Author(s)   : Rainer Herbertz
 *                Utimaco AG
 *
 *  Description : Global header file of CryptoServer module DSA
 *                Must be included in every CryptoServer software that uses
 *                functions of this module
 *
 *  History     :
 *  Date       |                 Action                          |  Author
 *  -----------|-------------------------------------------------|---------
 *  25.03.2005 | Creation                                        |  R.H.
 *****************************************************************************/


#ifndef __DSA_H_PUB_INCLUDED__
  #define __DSA_H_PUB_INCLUDED__

#include "os_mdl.h"


/* module identification: */

#define DSA_MDL_ID          0x8D                /* ID of the module                             */
#define DSA_MDL_NAME        "DSA"               /* Short name of the module                     */

#ifdef CS2_SDK
    #define DSA_MDL_NAMEX   "DSA Module SDK"    /* Long name of the module                      */
#else
    #ifdef DEBUG
    #define DSA_MDL_NAMEX   "DSA Module DEBUG"  /* Long name of the module                      */
    #else
    #define DSA_MDL_NAMEX   "DSA Module"        /* Long name of the module                      */
    #endif
#endif
                                                 /* Version of the module                        */
#define DSA_MDL_VERSION     0x01020500



/* flags for dsa_xgen: */

#define DSA_MODE_REAL_RND   0x00                /* use real random generator                    */
#define DSA_MODE_PSEUDO_RND 0x01                /* use pseudo random generator                  */

#define DSA_MODE_PROB_PRIME 0x00                /* generate probably prime's                    */
#define DSA_MODE_PROV_PRIME 0x02                /* generate proven prime's                      */
#define DSA_MODE_MASK       0x0e                /* mask for mode                                */


/* flags indicating the functioning standard (original, fips 186-4) */

//#define DSA_MODE_STD_MASK        0x00000100
//#define DSA_MODE_STD_FIPS186_4   0x00000100

/* flags indicating the hash function for generating p and q (fips 186-4) they relate to the cxi module code*/

#define DSA_MODE_HASH_SHA1         0x00000010    //!< SHA1
#define DSA_MODE_HASH_SHA224       0x00000030    //!< SHA224
#define DSA_MODE_HASH_SHA256       0x00000040    //!< SHA256
#define DSA_MODE_HASH_SHA384       0x00000060    //!< SHA384
#define DSA_MODE_HASH_SHA512       0x00000070    //!< SHA512

#define DSA_MODE_HASH_SHA3_224     0x00000080    //!< SHA3-224
#define DSA_MODE_HASH_SHA3_256     0x00000090    //!< SHA3-256
#define DSA_MODE_HASH_SHA3_384     0x000000A0    //!< SHA3-384
#define DSA_MODE_HASH_SHA3_512     0x000000B0    //!< SHA3-512
                                                      
#define DSA_MODE_HASH_MASK         0x000000F0    

/* flags for dsa_dh + dsa_dh_gen: */

#define DSA_KDF_CT           0x1000
#define DSA_KDF_RAW          0x2000

/* maximal seed length for FIPS186 */
#define MAX_SEED_LENGTH      120000

/* flags indicating the components of a DSA parameter token */

#define DSA_PC_P            0x01                /* Prime p                                      */
#define DSA_PC_Q            0x02                /* Prime q                                      */
#define DSA_PC_G            0x04                /* Generator g                                  */
#define DSA_PC_Y            0x08                /* Public key y                                 */
#define DSA_PC_END          0x00                /* end-mark of parameter list                   */
                                                /* of function dsa_mk_token                     */
#define DSA_PC_ALL          0x0F


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

    int    (*p_chk_size)( unsigned char* keyt, unsigned int max, unsigned int *p_len );
    int    (*p_get_comp)( int component, unsigned char* p_keyt, unsigned int* p_l_component, unsigned char** pp_component );
    int    (*p_mk_token)( unsigned char** pp_keyt, ... );
    int    (*p_xkeygen)( unsigned int flags, unsigned int l_p, unsigned char* p_p, unsigned int l_q, unsigned char* p_q,
                         unsigned int l_g, unsigned char* p_g, unsigned char* p_x, unsigned char* p_y );
    int    (*p_tkeygen)( unsigned int flags, unsigned char *p_tok,
                         unsigned int *p_l_x, unsigned char* p_x,
                         unsigned int *p_l_y, unsigned char* p_y );
    int    (*p_xsign)( unsigned int flags, unsigned int l_p, unsigned char* p_p, unsigned int l_q, unsigned char* p_q,
                       unsigned int l_g, unsigned char* p_g, unsigned int l_x, unsigned char* p_x,
                       unsigned int l_hash, unsigned char* p_hash,
                       unsigned int *p_l_sign, unsigned char* p_sign );
    int    (*p_tsign)( unsigned int flags, unsigned char *p_tok, unsigned int l_x, unsigned char* p_x,
                       unsigned int l_hash, unsigned char* p_hash,
                       unsigned int *p_l_sign, unsigned char* p_sign );
    int    (*p_xchk)( unsigned int l_p, unsigned char* p_p, unsigned int l_q, unsigned char* p_q,
                      unsigned int l_g, unsigned char* p_g, unsigned int l_x, unsigned char* p_x,
                      unsigned int l_y, unsigned char* p_y );
    int    (*p_tchk)( unsigned char* p_tok, unsigned int l_x, unsigned char* p_x, unsigned int l_y, unsigned char* p_y );
    int    (*p_xgen)( unsigned int psize, unsigned int qsize, unsigned int mode, unsigned int* p_l_p, unsigned char* p_p,
                      unsigned int* p_l_q, unsigned char* p_q, unsigned char* p_g );
    int    (*p_tgen)( unsigned int psize, unsigned int qsize, unsigned int mode, unsigned char** pp_tok );
    int    (*p_xverify)( unsigned int l_p, unsigned char* p_p, unsigned int l_q, unsigned char* p_q,
                         unsigned int l_g, unsigned char* p_g, unsigned int l_y, unsigned char* p_y,
                         unsigned int l_hash, unsigned char* p_hash,
                         unsigned int l_sign_r, unsigned char* p_sign_r,
                         unsigned int l_sign_s, unsigned char* p_sign_s );
    int    (*p_tverify)( unsigned char *p_tok, unsigned int l_y, unsigned char* p_y,
                         unsigned int l_hash, unsigned char* p_hash,
                         unsigned int l_sign_r, unsigned char* p_sign_r,
                         unsigned int l_sign_s, unsigned char* p_sign_s );
    int    (*p_sign_decode)(unsigned int l_sign, unsigned char* p_sign,
                            unsigned int *p_l_r, unsigned char **pp_r,
                            unsigned int *p_l_s, unsigned char **pp_s );
    int    (*p_sign_encode)(unsigned int l_r, unsigned char *p_r,
                            unsigned int l_s, unsigned char *p_s,
                            unsigned int *p_l_sign, unsigned char *p_sign );
    int    (*p_tkeygen2)(unsigned int flags, unsigned char *p_tok, unsigned char **pp_tok,
                         unsigned int *p_l_x, unsigned char *p_x );
    int    (*p_dh)(
                unsigned int   l_p,         
                unsigned char  *p_p,        
                unsigned int   l_x,         
                unsigned char  *p_x,        
                unsigned int   l_y,         
                unsigned char  *p_y,        
                unsigned int   flags,       
                unsigned int   l_shsec,     
                unsigned char  *p_shsec,    
                unsigned int   l_secret,    
                unsigned char  *p_secret    
                );
    int    (*p_dh_gen)(
                unsigned int   l_p,         
                unsigned char  *p_p,        
                unsigned int   l_g,         
                unsigned char  *p_g,        
                unsigned int   l_y,         
                unsigned char  *p_y,        
                unsigned int   flags,       
                unsigned int   l_shsec,     
                unsigned char  *p_shsec,    
                unsigned int   l_secret,    
                unsigned char  *p_secret,   
                unsigned char  **pp_r       
                );
    int    (*p_dh_chk)(
                unsigned int   l_p,         
                unsigned char  *p_p,        
                unsigned int   l_g,         
                unsigned char  *p_g,        
                unsigned int   l_x,
                unsigned char  *p_x         
                );
    int    (*p_xgen_fips186_2)(
                unsigned int   psize,          
                unsigned int   qsize,           
                unsigned int   mode,          
                unsigned int*  p_l_seed,       
                unsigned char* p_seed_in,          
                unsigned char* p_seed_out,          
                unsigned int*  p_l_h,    
                unsigned char* p_h,        
                unsigned int*  counter,
                unsigned int*  p_l_p,      
                unsigned char* p_p,          
                unsigned int*  p_l_q,   
                unsigned char* p_q,    
                unsigned char* p_g
                );    
        int (*p_dsa_pq_gen) (
            unsigned int   psize,          
            unsigned int   qsize,          
            unsigned int   mode,           
            unsigned int*  p_l_seed,       
            unsigned char* p_seed_in,      
            unsigned char* p_seed_out,     
            unsigned int   retries,        
            unsigned int*  p_counter_p,      
            unsigned int*  p_l_p,          
            unsigned char* p_p,            
            unsigned int*  p_l_q,          
            unsigned char* p_q             
            );
        int (*p_dsa_g_gen) (
            unsigned int   mode,            
            unsigned int   l_seed,       
            unsigned char* p_seed_in,       
            unsigned char  index,        
            unsigned int   l_p,       
            unsigned char* p_p,            
            unsigned int   l_q,          
            unsigned char* p_q,            
            unsigned char* p_g             
            );
        int (*p_pq_chk) (
            unsigned int   psize,       
            unsigned int   qsize,    
            unsigned int   mode,        
            unsigned int   l_seed,    
            unsigned char* p_seed_in,    
            unsigned int   counter_p,   
            unsigned int   l_p,        
            unsigned char* p_p,          
            unsigned int   l_q,      
            unsigned char* p_q         
            );
        int (*p_g_chk) (
            unsigned int   mode,          
            unsigned int   l_seed,       
            unsigned char* p_seed_in,    
            unsigned char  index,               
            unsigned int   l_p,          
            unsigned char* p_p,       
            unsigned int   l_q,         
            unsigned char* p_q,           
            unsigned char* p_g              
            );
        int (*p_xgen_fips186_4) (
            unsigned int   psize,           
            unsigned int   qsize,           
            unsigned int   mode,           
            unsigned int*  p_l_seed,       
            unsigned char* p_seed_in,       
            unsigned char* p_seed_out,      
            unsigned int   retries,     
            unsigned char  index,              
            unsigned int*  counter_p,        
            unsigned int*  p_l_p,      
            unsigned char* p_p,             
            unsigned int*  p_l_q,       
            unsigned char* p_q,            
            unsigned char* p_g              
            );
        int (*p_pqg_chk_fips186_4) (
            unsigned int   psize,        
            unsigned int   qsize,       
            unsigned int   mode,       
            unsigned int   l_seed,  
            unsigned char* p_seed_in,     
            unsigned char  index,
            unsigned int   counter_p,         
            unsigned int   l_p,           
            unsigned char* p_p,
            unsigned int   l_q,
            unsigned char* p_q,  
            unsigned char* p_g   
            );

} T_DSA_TABLE_PUB;



#ifdef _DSA_C_INT_

/* function prototypes used by the module (internal) */

int  dsa_start(T_OS_MDL_HDL,void *,void *);
int  dsa_pre_replace(void);
int  dsa_pre_delete(void);

int dsa_get_comp (
    int             component,              // (I)  One of the DSA_KC_... macros,
                                            //      defining the component to be extractet from the token.
    unsigned char*  p_keyt,                 // (I)  Pointer to the DSA key token.
    unsigned int*   p_l_component,          // (O)  Length of the key component.
    unsigned char** pp_component            // (O)  A pointer to the key component is
    );                                      //      stored here, pointing into the key token.

int dsa_mk_token (
    unsigned char** pp_keyt,                // (O) pointer to the generated key token
    ...
    );

int dsa_chk_size(
    unsigned char   *p_keyt,                // (I) The key token which length is to calculate.
    unsigned int    max,                    // (I) Size of the input data p_keyt
    unsigned int    *p_len                  // (O) the length of the key token in bytes
    );

int dsa_xkeygen(
    unsigned int   flags,       // (I) DSA_MODE_REAL / PSEUDO_RND
    unsigned int   l_p,         // (I) Length of prime P of DSA parameter
    unsigned char* p_p,         // (I) Pointer to prime P.
    unsigned int   l_q,         // (I) Length of prime Q of DSA parameter
    unsigned char* p_q,         // (I) Pointer to prime Q.
    unsigned int   l_g,         // (I) Length of generator G of DSA parameter
    unsigned char* p_g,         // (I) Pointer to G
    unsigned char* p_x,         // (O) Pointer to private key (length is l_q)
    unsigned char* p_y          // (O) Pointer to public key (length is l_p)
    );

int dsa_tkeygen(
    unsigned int   flags,       // (I)   DSA_MODE_REAL / PSEUDO_RND
    unsigned char  *p_tok,      // (I)   Pointer to parameter token
    unsigned int   *p_l_x,      // (I/O) Size of buffer / length of private key
    unsigned char  *p_x,        // (O)   Pointer to private key
    unsigned int   *p_l_y,      // (I/O) Size of buffer / length of public key
    unsigned char  *p_y         // (O)   Pointer to public key
    );

int dsa_xsign(
    unsigned int   flags,       // (I) DSA_MODE_REAL / PSEUDO_RND
    unsigned int   l_p,         // (I) Length of prime P of DSA parameter
    unsigned char* p_p,         // (I) Pointer to prime P.
    unsigned int   l_q,         // (I) Length of prime Q of DSA parameter
    unsigned char* p_q,         // (I) Pointer to prime Q.
    unsigned int   l_g,         // (I) Length of generator G of DSA parameter
    unsigned char* p_g,         // (I) Pointer to G
    unsigned int   l_x,         // (I) Length of private key
    unsigned char* p_x,         // (I) Pointer to private key
    unsigned int   l_hash,      // (I) Length of hash value
    unsigned char* p_hash,      // (I) Pointer to hash value
    unsigned int   *p_l_sign,   // (I/O) Size of buffer / length of signature
    unsigned char* p_sign       // (O) Pointer to signature (length is 2 * l_q)
    );

int dsa_tsign(
    unsigned int   flags,       // (I)   DSA_MODE_REAL / PSEUDO_RND
    unsigned char  *p_tok,      // (I)   Pointer to parameter token
    unsigned int   l_x,         // (I)   Length of private key
    unsigned char* p_x,         // (I)   Pointer to private key
    unsigned int   l_hash,      // (I)   Length of hash value
    unsigned char* p_hash,      // (I)   Pointer to hash value
    unsigned int   *p_l_sign,   // (I/O) Size of buffer / length of signature
    unsigned char* p_sign       // (O)   Pointer to signature
    );

int dsa_xchk (
    unsigned int   l_p,         // (I) Length of prime P of DSA parameter
    unsigned char* p_p,         // (I) Pointer to prime P.
    unsigned int   l_q,         // (I) Length of prime Q of DSA parameter
    unsigned char* p_q,         // (I) Pointer to prime Q.
    unsigned int   l_g,         // (I) Length of generator G of DSA parameter
    unsigned char* p_g,         // (I) Pointer to G
    unsigned int   l_x,         // (I) Length of private key
    unsigned char* p_x,         // (I) Pointer to private key or NULL
    unsigned int   l_y,         // (I) Length of public key
    unsigned char* p_y          // (I) Pointer to public key or NULL
    );

int dsa_tchk (
    unsigned char* p_tok,       // (I) Pointer to the DSA token.
    unsigned int   l_x,         // (I) Length of private key
    unsigned char* p_x,         // (I) Pointer to private key or NULL
    unsigned int   l_y,         // (I) Length of public key
    unsigned char* p_y          // (I) Pointer to public key or NULL
    );

int dsa_xgen (
    unsigned int   psize,           // (I) Length of prime P be generated in bits.
    unsigned int   qsize,           // (I) Length of prime Q be generated in bits.
    unsigned int   mode,            // (I) DSA_MODE_REAL / PSEUDO_RND
    unsigned int*  p_l_p,           // (O) Length of generated prime P
    unsigned char* p_p,             // (O) prime P
    unsigned int*  p_l_q,           // (O) Length of generated prime Q
    unsigned char* p_q,             // (O) prime Q
    unsigned char* p_g              // (O) generator G (length is l_p)
    );

int dsa_tgen(
    unsigned int    psize,          // (I) Length of prime P be generated in bits.
    unsigned int    qsize,          // (I) Length of prime Q be generated in bits.
    unsigned int    mode,           // (I) DSA_MODE_REAL / PSEUDO_RND
    unsigned char** pp_tok          // (O)  Pointer to generated token
    );

int dsa_xverify(
    unsigned int   l_p,         // (I) Length of prime P of DSA parameter
    unsigned char* p_p,         // (I) Pointer to prime P.
    unsigned int   l_q,         // (I) Length of prime Q of DSA parameter
    unsigned char* p_q,         // (I) Pointer to prime Q.
    unsigned int   l_g,         // (I) Length of generator G of DSA parameter
    unsigned char* p_g,         // (I) Pointer to G
    unsigned int   l_y,         // (I) Length of public key
    unsigned char* p_y,         // (I) Pointer to public key
    unsigned int   l_hash,      // (I) Length of hash value
    unsigned char* p_hash,      // (I) Pointer to hash value
    unsigned int   l_sign_r,    // (I) Length of signature / part r of signature
    unsigned char* p_sign_r,    // (I) Pointer to signature / part r of signature
    unsigned int   l_sign_s,    // (I) Length of part s of signature
    unsigned char* p_sign_s     // (I) Pointer to part s of signature (or NULL)
    );

int dsa_tverify(
    unsigned char  *p_tok,      // (I) Pointer to parameter token
    unsigned int   l_y,         // (I) Length of private key
    unsigned char* p_y,         // (I) Pointer to private key
    unsigned int   l_hash,      // (I) Length of hash value
    unsigned char* p_hash,      // (I) Pointer to hash value
    unsigned int   l_sign_r,    // (I) Length of signature / part r of signature
    unsigned char* p_sign_r,    // (I) Pointer to signature / part r of signature
    unsigned int   l_sign_s,    // (I) Length of part s of signature
    unsigned char* p_sign_s     // (I) Pointer to part s of signature (or NULL)
    );

int dsa_sign_decode(
    unsigned int   l_sign,      // (I) Length of signature
    unsigned char* p_sign,      // (I) Pointer to prime signature
    unsigned int   *p_l_r,      // (O) Length of part r
    unsigned char  **pp_r,      // (O) Pointer to part r
    unsigned int   *p_l_s,      // (O) Length of part s
    unsigned char  **pp_s       // (O) Pointer to part s
    );

int dsa_sign_encode(
    unsigned int   l_r,         // (I)   Length of part r
    unsigned char  *p_r,        // (I)   Pointer to part r
    unsigned int   l_s,         // (I)   Length of part s
    unsigned char  *p_s,        // (I)   Pointer to part s
    unsigned int   *p_l_sign,   // (I/O) Length of signature
    unsigned char  *p_sign      // (O)   Pointer to signature
    );

int dsa_tkeygen2(
    unsigned int   flags,       // (I)   DSA_MODE_REAL / PSEUDO_RND
    unsigned char  *p_tok,      // (I)   Pointer to input token
    unsigned char  **pp_tok,    // (O)   Pointer to output token
    unsigned int   *p_l_x,      // (I/O) Size of buffer / length of private key
    unsigned char  *p_x         // (O)   Pointer to private key
    );

int dsa_dh(
    unsigned int   l_p,         // (I) Length of prime P of DSA parameter
    unsigned char  *p_p,        // (I) Pointer to prime P.
    unsigned int   l_x,         // (I) Length of private key
    unsigned char  *p_x,        // (I) Pointer to private key
    unsigned int   l_y,         // (I) Length of public key
    unsigned char  *p_y,        // (I) Pointer to public key
    unsigned int   flags,       // (I) rnd_mode, hash_algo, hash_r
    unsigned int   l_shsec,     // (I) Length of shared secret
    unsigned char  *p_shsec,    // (I) Shared secret
    unsigned int   l_secret,    // (I) Length of generated secret value
    unsigned char  *p_secret    // (O) generated secret value
    );

int dsa_dh_gen(
    unsigned int   l_p,         // (I) Length of prime P of DSA parameter
    unsigned char  *p_p,        // (I) Pointer to prime P.
    unsigned int   l_g,         // (I) Length of generator G of DSA parameter
    unsigned char  *p_g,        // (I) Pointer to G
    unsigned int   l_y,         // (I) Length of public key 
    unsigned char  *p_y,        // (I) Pointer to public key 
    unsigned int   flags,       // (I) rnd_mode, hash_algo
    unsigned int   l_shsec,     // (I) Length of shared secret
    unsigned char  *p_shsec,    // (I) Shared secret
    unsigned int   l_secret,    // (I) Length of generated secret value
    unsigned char  *p_secret,   // (O) generated secret value
    unsigned char  **pp_r       // (O) temp. public key (length is l_p)
    );

int dsa_dh_chk(
    unsigned int   l_p,         // (I) Length of prime P of DH parameter
    unsigned char  *p_p,        // (I) Pointer to prime P.
    unsigned int   l_g,         // (I) Length of generator G of DH parameter
    unsigned char  *p_g,        // (I) Pointer to G
    unsigned int   l_x,         // (I) Length of the key
    unsigned char  *p_x         // (I) Pointer to the key 
    );


//v 1.1.0
int dsa_xgen_fips186_2 (
    unsigned int   psize,           // (I) Length of prime P be generated in bits.
    unsigned int   qsize,           // (I) Length of prime Q be generated in bits.
    unsigned int   mode,            // (I) DSA_MODE_REAL / PSEUDO_RND && hash
    unsigned int*  p_l_seed,        // (I/O) Input seed length in bytes  
    unsigned char* p_seed_in,       // (I) Input seed from with the prime is (possibly) generated
    unsigned char* p_seed_out,      // (O) Input seed from with the prime is (possibly) generated
    unsigned int*  p_l_h,           // (O) Length of generated h
    unsigned char* p_h,             // (O) prime h
    unsigned int*  counter,         // (I/O) number of tries to get p    
    unsigned int*  p_l_p,           // (O) Length of generated prime P
    unsigned char* p_p,             // (O) prime P
    unsigned int*  p_l_q,           // (O) Length of generated prime Q
    unsigned char* p_q,             // (O) prime Q
    unsigned char* p_g              // (O) generator G (length is l_p)
    );
//v 1.2.0
int dsa_pq_gen (
    unsigned int   psize,           // (I) Length of prime P be generated in bits.
    unsigned int   qsize,           // (I) Length of prime Q be generated in bits.
    unsigned int   mode,            // (I) (DSA_MODE_REAL || PSEUDO_RND) && (hash function) 
    unsigned int*  p_l_seed,        // (I/O) I: Buffersize, O: Seed length in bytes
    unsigned char* p_seed_in,       // (O) (optional) seed for prime genereation
    unsigned char* p_seed_out,      // (O) (optional) seed used to prime generation
    unsigned int   retries,         // (I) Number of times that the original seed can be incremented
    unsigned int*  counter_p,       // (I/O) number of tries to get p
    unsigned int*  p_l_p,           // (O) Length of generated prime P
    unsigned char* p_p,             // (O) prime P
    unsigned int*  p_l_q,           // (O) Length of generated prime Q
    unsigned char* p_q              // (O) prime Q
    );
int dsa_g_gen (
    unsigned int   mode,            // (I) (hash function) 
    unsigned int   l_seed,          // (I) seed length in bytes  
    unsigned char* p_seed_in,       // (I) Input seed for prime generation
    unsigned char  index,           // (I) 8 bits tag to differentiate between possible generation processes. See [FIPS 186-4].
    unsigned int   l_p,             // (I) Length of generated prime P
    unsigned char* p_p,             // (I) prime P
    unsigned int   l_q,             // (I) Length of generated prime Q
    unsigned char* p_q,             // (I) prime Q
    unsigned char* p_g              // (O) generator G (lenusgth is l_p)
    );
int dsa_pq_chk (
    unsigned int   psize,           // (I) Length of prime P be generated in bits.
    unsigned int   qsize,           // (I) Length of prime Q be generated in bits.
    unsigned int   mode,            // (I) (hash function) 
    unsigned int   l_seed,          // (I) Input seed length in bytes  
    unsigned char* p_seed_in,       // (I) Input seed for prime generation
    unsigned int   counter_p,       // (I) number of tries to get p
    unsigned int   l_p,             // (I) Length of generated prime P
    unsigned char* p_p,             // (I) prime P
    unsigned int   l_q,             // (I) Length of generated prime Q
    unsigned char* p_q              // (I) prime Q
    );
int dsa_g_chk (
    unsigned int   mode,            // (I) (hash function)
    unsigned int   l_seed,          // (I) Input seed length in bytes  
    unsigned char* p_seed_in,       // (I) Input seed for prime generation
    unsigned char  index,           // (I) 8 bits tag to differentiate between possible generation processes. See [FIPS 186-4].
    unsigned int   l_p,             // (I) Length of generated prime P
    unsigned char* p_p,             // (I) prime P
    unsigned int   l_q,             // (I) Length of generated prime Q
    unsigned char* p_q,             // (I) prime Q
    unsigned char* p_g              // (I) prime Q
    );
int dsa_xgen_fips186_4 (
    unsigned int   psize,           // (I) Length of prime P be generated in bits.
    unsigned int   qsize,           // (I) Length of prime Q be generated in bits.
    unsigned int   mode,            // (I) (DSA_MODE_REAL || PSEUDO_RND) && (hash function)
    unsigned int*  p_l_seed,        // (I/O) I: Buffersize, O: Seed length in bytes
    unsigned char* p_seed_in,       // (I) (optional) start seed for prime generation
    unsigned char* p_seed_out,      // (O) (optional) seed from which the primes were generated 
    unsigned int   retries,         // (I) Number of times that the original seed can be incremented
    unsigned char  h,               // (I)8 bits tag to differentiate between possible generation processes. See [FIPS 186-4].
    unsigned int*  p_counter_p,     // (I/O) number of tries to get p    
    unsigned int*  p_l_p,           // (O) Length of generated prime P
    unsigned char* p_p,             // (O) prime P
    unsigned int*  p_l_q,           // (O) Length of generated prime Q
    unsigned char* p_q,             // (O) prime Q
    unsigned char* p_g              // (O) generator G (length is l_p)
    );
int dsa_pqg_chk_fips186_4 (
    unsigned int   psize,           // (I) Length of prime P be generated in bits.
    unsigned int   qsize,           // (I) Length of prime Q be generated in bits.
    unsigned int   mode,            // (I) (DSA_MODE_REAL || PSEUDO_RND) && (hash function) && fips mode
    unsigned int   l_seed,          // (I) seed length in bytes  
    unsigned char* p_seed_in,       // (I) Input seed for prime generation
    unsigned char  index,           // (I) 8 bits tag to differentiate between possible generation processes. See [FIPS 186-4].
    unsigned int   counter_p,       // (I) number of tries to get p
    unsigned int   l_p,             // (I) Length of generated prime P
    unsigned char* p_p,             // (I) prime P
    unsigned int   l_q,             // (I) Length of generated prime Q
    unsigned char* p_q,             // (I) prime Q
    unsigned char* p_g              // (I) generator G (length is l_p)
    );
#else

/* external interface to be used by other modules */

extern MDL_GLOBAL T_OS_MDL_HDL P_DSA;

#define _P_DSA ((T_DSA_TABLE_PUB *)P_DSA)     /* shortcut */

#define dsa_start          _P_DSA->p_start
#define dsa_stop           _P_DSA->p_stop

#define dsa_get_comp       _P_DSA->p_get_comp
#define dsa_mk_token       _P_DSA->p_mk_token
#define dsa_chk_size       _P_DSA->p_chk_size
#define dsa_xkeygen        _P_DSA->p_xkeygen
#define dsa_tkeygen        _P_DSA->p_tkeygen
#define dsa_tkeygen2       _P_DSA->p_tkeygen2
#define dsa_xsign          _P_DSA->p_xsign
#define dsa_tsign          _P_DSA->p_tsign
#define dsa_xchk           _P_DSA->p_xchk
#define dsa_tchk           _P_DSA->p_tchk
#define dsa_xgen           _P_DSA->p_xgen
#define dsa_tgen           _P_DSA->p_tgen
#define dsa_xverify        _P_DSA->p_xverify
#define dsa_tverify        _P_DSA->p_tverify
#define dsa_sign_decode    _P_DSA->p_sign_decode
#define dsa_sign_encode    _P_DSA->p_sign_encode
#define dsa_dh             _P_DSA->p_dh
#define dsa_dh_gen         _P_DSA->p_dh_gen
#define dsa_dh_chk         _P_DSA->p_dh_chk
#define dsa_xgen_fips186_2 _P_DSA->p_xgen_fips186_2
//v 1.2.0

#define dsa_pq_gen                  _P_DSA->p_dsa_pq_gen
#define dsa_g_gen                   _P_DSA->p_dsa_g_gen
#define dsa_pq_chk                  _P_DSA->p_pq_chk
#define dsa_g_chk                   _P_DSA->p_g_chk
#define dsa_xgen_fips186_4          _P_DSA->p_xgen_fips186_4
#define dsa_pqg_chk_fips186_4       _P_DSA->p_pqg_chk_fips186_4


#endif /* _DSA_C_INT_ */


/* Error Codes:  (0xB0000000 | (DSA_MDL_ID << 16) | (errno))  */

/* --- BEGIN ERROR CODES --- */

#define E_DSA                        0xB08D     /* CryptoServer module DSA                      */
#define E_DSA_MEM                    0xB08D0001 /* cannot allocate memory                       */
#define E_DSA_P_TOO_SMALL            0xB08D0002 /* prime P is too small                         */
#define E_DSA_Q_TOO_SMALL            0xB08D0003 /* prime Q is too small                         */
#define E_DSA_GEN_FAILED             0xB08D0004 /* domain parameter generation failed           */
#define E_DSA_BAD_G                  0xB08D0005 /* invalid generator value G                    */
#define E_DSA_BAD_PRIMES             0xB08D0006 /* bad primes P and Q                           */
#define E_DSA_NO_KEYTOKEN            0xB08D0007 /* byte string is not a keytoken                */
#define E_DSA_NO_COMP                0xB08D0008 /* component is not a member of this token      */
#define E_DSA_DOUBLE_COMP            0xB08D0009 /* component is already a member of this token  */
#define E_DSA_INVALID_FLAG           0xB08D000A /* value for flags is invalid                   */
#define E_DSA_HASH_LEN               0xB08D000B /* wrong hash value length                      */
#define E_DSA_BAD_KEY                0xB08D000C /* private and public key do not correspond     */
#define E_DSA_INV_PARAM              0xB08D000D /* invalid parameter                            */
#define E_DSA_BAD_PKEY               0xB08D000E /* bad public key                               */
#define E_DSA_BAD_SKEY               0xB08D000F /* bad private key                              */
#define E_DSA_KEYT_LEN               0xB08D0010 /* bad length of key token                      */
#define E_DSA_VERIFY_FAILED          0xB08D0011 /* signature verification failed                */
#define E_DSA_BAD_SIGN_FMT           0xB08D0012 /* bad format of signature                      */
#define E_DSA_NO_ASN1                0xB08D0013 /* no ASN.1 module loaded                       */
#define E_DSA_BUFF_TOO_SMALL         0xB08D0014 /* buffer for result is to small                */
#define E_DSA_KEYGEN_TEST            0xB08D0015 /* pairwise consistency check failed on keygen  */
// FIPS restrictions are not in CXI #define E_DSA_P_TOO_SMALL_FIPS       0xB08D0016 /* prime P < 1024 bit not allowed in FIPS mode  */
// FIPS restrictions are not in CXI #define E_DSA_Q_TOO_SMALL_FIPS       0xB08D0017 /* prime Q < 160 bit not allowed in FIPS mode   */
#define E_DSA_ZERO_LEN               0xB08D0018 /* Zero length not allowed                      */
#define E_DSA_Q_TOO_BIG              0xB08D0023 /* prime Q is too big                           */
#define E_DSA_NOT_SUPPORTED          0xB08D0030 /* The function called is no longer supported   */


#define E_DSA_BAD_KEYT               0xB08D0100 /* bad key token in command string              */

/* --- END ERROR CODES --- */





#endif /* __DSA_H_PUB_INCLUDED__ */

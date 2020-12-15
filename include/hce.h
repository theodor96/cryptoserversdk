#ifndef __HCE_H_PUB_INCLUDED__
#define __HCE_H_PUB_INCLUDED__

#include "os_mdl.h"
#include "stype.h"

// ----------------------------------------------------------------------------
// module identification
// ----------------------------------------------------------------------------
#define HCE_MDL_ID            0x0A
#define HCE_MDL_NAME          "HCE"
#ifdef CS2_SDK
  #define HCE_MDL_NAMEX       "Hardware Crypto Engine (SDK)"
#else
  #ifdef DEBUG
    #define HCE_MDL_NAMEX     "Hardware Crypto Engine (DEBUG)"
  #else
    #define HCE_MDL_NAMEX     "Hardware Crypto Engine"
  #endif
#endif
#define HCE_MDL_VERSION       0x02030002

// ----------------------------------------------------------------------------
// public interface
// ----------------------------------------------------------------------------
typedef struct
{
  unsigned int  gx_len;
  void          *p_gx;                // (I)  base point Gx
  unsigned int  gy_len;                       
  void          *p_gy;                // (I)  base point Gy
  unsigned int  p_len;                        
  void          *p_p;                 // (I)  prime p
  unsigned int  n_len;                        
  void          *p_n;                 // (I)  order n
}
T_HCE_DP;

typedef struct
{  
  unsigned int  len;
  void          *buf;
}
T_HCE_PCR;

typedef struct
{
  void        *p_data;
  int         (*p_start)();
  int         (*p_stop)(void);
  int         (*p_pre_replace)(void);
  int         (*p_pre_delete)(void);
  void        *p_dumy;
  const void  *p_module_info;

  int (*p_rsa)(
    unsigned int  flags,              // (I)  HCE_BYTE_XXX
    unsigned int  l_mod,              // (I)  length of modulus
    void          *p_mod,             // (I)  modulus
    unsigned int  l_exp,              // (I)  length of exponent
    void          *p_exp,             // (I)  exponent
    unsigned int  nitems,             // (I)  number of data elements
    unsigned int  l_data[],           // (I)  length of data
    void          *data_in[],         // (I)  data
    unsigned int  l_out,              // (I)  size of output buffer(s)
    void          *data_out[]         // (O)  result
  );

  int (*p_rsa_crt)(
    unsigned int  flags,              // (I)  HCE_BYTE_XXX
    unsigned int  l_p,                // (I) length of prime P
    void          *p_p,               // (I) prime P
    unsigned int  l_q,                // (I) length of prime Q
    void          *p_q,               // (I) prime Q
    unsigned int  l_u,                // (I) length of U
    void          *p_u,               // (I) U
    unsigned int  l_dp,               // (I) length of subprime dP
    void          *p_dp,              // (I) subprime dP
    unsigned int  l_dq,               // (I) length of subprime dQ
    void          *p_dq,              // (I) subprime dQ
    unsigned int  nitems,             // (I) number of data elements
    unsigned int  l_data[],           // (I) length of data
    void          *data_in[],         // (I) data
    unsigned int  l_out,              // (I) size of output buffer(s)
    void          *data_out[]         // (O) result
  );

  // new as of 2.1.0.0
  int (*p_info)(
    unsigned int  type,               // (I)  HCE_INFO_XXX
    void          *p_info             // (O)  pointer to info structure 
  );

  int (*p_ec_point_mul)(
    unsigned int  flags,              // (I)  HCE_BYTE_XXX
    T_HCE_DP      *p_dp,              // (I)  domain parameters (base point G, prime P)  
    T_HCE_PCR     *p_pcr,             // (IO) precomputed reciprocal of p or NULL
    unsigned int  nitems,             // (I)  number of data elements
    unsigned int  l_data[],           // (I)  length of data (scalar value / secret key)
    void          *data_in[],         // (I)  data
    unsigned int  l_out,              // (I)  size of output buffer(s)
    void          *data_out[]         // (O)  result
  );

  int (*p_ec_sign)(
    unsigned int  flags,              // (I)  HCE_BYTE_XXX
    T_HCE_DP      *p_dp,              // (I)  domain parameters (base point G, prime P, order N)  
    T_HCE_PCR     p_pcr[2],           // (IO) precomputed reciprocals of p and n or NULL
    unsigned int  d_len,              // (I)  length of private key        
    void          *p_d,               // (I)  private key    
    unsigned int  nitems,             // (I)  number of ephemeral key / data elements
    unsigned int  l_k[],              // (I)  length of ephermeral keys
    void          *k[],               // (I)  ephermeral keys
    unsigned int  l_data[],           // (I)  length of data / hash
    void          *data_in[],         // (I)  data
    unsigned int  l_out,              // (I)  size of output buffer(s)
    void          *data_out[]         // (O)  result
  );
  
  // new as of 2.2.0.0
  int (*p_ec_verify)(
    unsigned int  flags,              // (I)  HCE_BYTE_XXX
    T_HCE_DP      *p_dp,              // (I)  domain parameters (base point G, prime P, order N)  
    T_HCE_PCR     p_pcr[2],           // (IO) precomputed reciprocals of p and n or NULL
    unsigned int  qx_len,             // (I)  length of X
    void          *p_qx,              // (I)  public key X
    unsigned int  qy_len,             // (I)  length of Y
    void          *p_qy,              // (I)  public key Y
    unsigned int  r_len,              // (I)  length of signature r
    void          *p_r,               // (I)  signature r
    unsigned int  s_len,              // (I)  length of signature s
    void          *p_s,               // (I)  signature s
    unsigned int  l_data,             // (I)  length of data / hash
    void          *data_in,           // (I)  data
    unsigned int  l_out,              // (I)  size of output buffer
    void          *data_out           // (O)  result
  );
  
  // new as of 2.3.0.0
  int (*p_rsa2)(
    unsigned int  flags,              // (I)  HCE_BYTE_XXX
    unsigned int  l_mod,              // (I)  length of modulus
    void          *p_mod,             // (I)  modulus
    unsigned int  l_exp,              // (I)  length of exponent
    void          *p_exp,             // (I)  exponent
    T_HCE_PCR     *p_pcr,             // (IO) precomputed reciprocal of modulus or NULL
    unsigned int  nitems,             // (I)  number of data elements
    unsigned int  l_data[],           // (I)  length of data
    void          *data_in[],         // (I)  data
    unsigned int  l_out,              // (I)  size of output buffer(s)
    void          *data_out[]         // (O)  result
  );
  
  int (*p_rsa_crt2)(
    unsigned int  flags,              // (I)  HCE_BYTE_XXX
    unsigned int  l_p,                // (I) length of prime P
    void          *p_p,               // (I) prime P
    unsigned int  l_q,                // (I) length of prime Q
    void          *p_q,               // (I) prime Q
    unsigned int  l_u,                // (I) length of U
    void          *p_u,               // (I) U
    unsigned int  l_dp,               // (I) length of subprime dP
    void          *p_dp,              // (I) subprime dP
    unsigned int  l_dq,               // (I) length of subprime dQ
    void          *p_dq,              // (I) subprime dQ
    T_HCE_PCR     p_pcr[2],           // (IO) precomputed reciprocals of p and q or NULL
    unsigned int  nitems,             // (I) number of data elements
    unsigned int  l_data[],           // (I) length of data
    void          *data_in[],         // (I) data
    unsigned int  l_out,              // (I) size of output buffer(s)
    void          *data_out[]         // (O) result
  );
  
}
T_HCE_TABLE_PUB;

// flags
#define HCE_BYTE_MODULUS              0x0001  // RSA modulus
#define HCE_BYTE_EXPONENT             0x0002  // RSA exponent
#define HCE_BYTE_DATA                 0x0004  // input or result data
#define HCE_BYTE_PRIMES               0x0008  // RSA prime or CRT values

#define HCE_CHECK_DATA                0x0010

#define HCE_BYTE_DP                   0x0020  // EC domain parameter (Gx, Gy, p, n, k)
#define HCE_BYTE_KEY                  0x0040  // EC private or public key (d, Qx, Qy)

// info types
#define HCE_INFO_GET_ACC_TYPE         1
#define HCE_INFO_LIST_CURVES          2
#define HCE_INFO_GET_KEY_SIZES        3

// accelerator types
typedef unsigned int T_HCE_ACC_TYPE;

#define HCE_ACC_TYPE_NONE             0
#define HCE_ACC_TYPE_BCM              1
#define HCE_ACC_TYPE_XR8204           2
#define HCE_ACC_TYPE_EXAR             2   // compatibility
#define HCE_ACC_TYPE_XR9200           3

// supported curves
typedef struct
{
  unsigned int ncurves;
  char **names;
}
T_HCE_INFO_EC_CURVES;

// supported key sizes in bits
typedef struct
{
  unsigned int min;
  unsigned int max;
}
T_HCE_INFO_KEY_SIZES;


#ifdef _HCE_C_INT_
// ----------------------------------------------------------------------------
// function prototypes used by the module (internal)
// ----------------------------------------------------------------------------
extern int hce_start(T_OS_MDL_HDL p_smos, void *dumy, void *p_coff_mem);
extern int hce_stop(void);
extern int hce_pre_replace(void);
extern int hce_pre_delete(void);

#else
// ----------------------------------------------------------------------------
// public interface to be used by other modules
// ----------------------------------------------------------------------------
extern MDL_GLOBAL T_OS_MDL_HDL P_HCE;

#define _P_HCE ((T_HCE_TABLE_PUB *)P_HCE)

#define P_hce_data          (_P_HCE->_p_data);

#define hce_start           _P_HCE->p_start
#define hce_stop            _P_HCE->p_stop
#define hce_pre_replace     _P_HCE->p_pre_replace
#define hce_pre_delete      _P_HCE->p_pre_delete

#define hce_rsa             _P_HCE->p_rsa
#define hce_rsa_crt         _P_HCE->p_rsa_crt
// new as of 2.1.0.0
#define hce_info            _P_HCE->p_info
#define hce_ec_point_mul    _P_HCE->p_ec_point_mul
#define hce_ec_sign         _P_HCE->p_ec_sign
// new as of 2.2.0.0
#define hce_ec_verify       _P_HCE->p_ec_verify
// new as of 2.3.0.0
#define hce_rsa2            _P_HCE->p_rsa2
#define hce_rsa_crt2        _P_HCE->p_rsa_crt2

#endif

// ----------------------------------------------------------------------------
// Error Codes:  (0xB0000000 | (HCE_MDL_ID << 16) | (errno))
// ----------------------------------------------------------------------------

/* --- BEGIN ERROR CODES --- */

#define E_HCE                          0xB00A           // CryptoServer module HCE
#define E_HCE_MEM                      0xB00A0001       // memory allocation failed
#define E_HCE_PCI_MASTER               0xB00A0002       // PCI master access error (DSP)
#define E_HCE_KEY_SIZE                 0xB00A0003       // key size not supported
#define E_HCE_EXP_SIZE                 0xB00A0004       // exponent greater modulus
#define E_HCE_TIMEOUT                  0xB00A0005       // hardware engine timeout
#define E_HCE_RESULT_SIZE              0xB00A0006       // result too big for buffer
#define E_HCE_PRIME_SIZE               0xB00A0007       // illegal sizes of prime
#define E_HCE_DATA_LEN                 0xB00A0008       // data size too big (greater than modulus)
#define E_HCE_SELFTST_FAIL             0xB00A0009       // Self-test failed
#define E_HCE_NO_LNA                   0xB00A000A       // Module LNA not found
#define E_HCE_DMA                      0xB00A000B       // PCI DMA master access error
#define E_HCE_NO_DRIVER                0xB00A000C       // No driver module found
#define E_HCE_DRIVER_INCOMPATIBLE      0xB00A000D       // Driver does not allow routing from HCE to driver.
#define E_HCE_PARAM_INVALID            0xB00A000E       // invalid parameter
#define E_HCE_NOT_SUPPORTED            0xB00A000F       // function is not supported
#define E_HCE_VERIFY_FAILED            0xB00A0010       // Signature verification failed

#define E_HCE_SYSTEM_ERR               0xB00A8          // System error (errno)

//#define E_HCE_ENGN_ERR                 0xB00A80       // hardware engine error

/* --- END ERROR CODES --- */

#endif

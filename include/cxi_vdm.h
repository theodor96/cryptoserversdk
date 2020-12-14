#ifndef __CXI_VDM_H__
#define __CXI_VDM_H__

#include <aes.h>
#include <vdes.h>
#include <eca.h>
#include <cxi.h>

typedef unsigned char* T_VDM_PTR;

// buffer
typedef struct
{
  T_VDM_PTR CONST pBuf;
  unsigned int    len;
} T_VDM_BUF;

// key type
typedef enum {
  VDM_TYPE_GENERIC_SECRET = 0,
  VDM_TYPE_DES         = 1,
  VDM_TYPE_AES         = 2,
  VDM_TYPE_RSA         = 3,
  VDM_TYPE_ECC         = 4,
  VDM_TYPE_DSA         = 5,
  VDM_TYPE_CUSTOM      = 6
} T_VDM_TYPE;

// key external or internal differentiation
typedef enum {
  VDM_INTERNAL_KEY = 0,
  VDM_EXTERNAL_KEY = 1
} T_VDM_EXT_OR_INT_KEY;

// mechanism
typedef struct {
  unsigned int Type;
  T_VDM_BUF    Param;
} T_VDM_MECH;

#define VDM_FLAG_LEN (1)

// key
typedef struct
{
  CONST T_VDM_TYPE      type;
  unsigned int          size;  // key size in bits

  union
  {
    struct
    {
      AES_KEY* CONST    p_enc;
      AES_KEY* CONST    p_dec;
    } AES;

    struct
    {
      VDES_KEY* CONST   p_enc;
      VDES_KEY* CONST   p_dec;
    } DES;

    struct
    {
      CONST T_VDM_BUF   pub_exp;
    } RSA;

    struct
    {
      ECDP* CONST p_dp;
    } ECC;

    struct
    {
      CONST T_VDM_BUF p;
      CONST T_VDM_BUF q;
      CONST T_VDM_BUF g;
    } DSA;

    struct
    {
      CONST unsigned int algo;
      CONST T_VDM_EXT_OR_INT_KEY ext_or_int;
    } CUSTOM;
  }
  comp;

  T_VDM_BUF     pub_token;
  T_VDM_BUF     priv_token;

  T_VDM_BUF     pub_data;

} T_VDM_KEY;



// VDM callback function for C_Encrypt, C_EncryptUpdate or C_Decrypt, C_DecryptUpdate
typedef int (*fctCrypt)  (const T_VDM_MECH* const pMech,
                          const unsigned int      flags,
                          const T_VDM_KEY* const  pKey,
                          const T_VDM_BUF* const  pDataIn,
                          const T_VDM_BUF* const  pStateIn,
                                T_VDM_BUF* const  pDataOut,
                                T_VDM_BUF* const  pStateOut);

// VDM callback function for C_Sign, C_SignUpdate
typedef int (*fctSign)   (const T_VDM_MECH* const pMech,
                          const unsigned int      flags,
                          const T_VDM_KEY* const  pKey,
                          const T_VDM_BUF* const  pDataIn,
                          const T_VDM_BUF* const  pStateIn,
                                T_VDM_BUF* const  pResultOut);

// VDM callback function for C_Verify, C_VerifyUpdate
typedef int (*fctVerify) (const T_VDM_MECH* const pMech,
                          const unsigned int      flags,
                          const T_VDM_KEY* const  pKey,
                          const T_VDM_BUF* const  pDataIn,
                          const T_VDM_BUF* const  pSigIn,
                          const T_VDM_BUF* const  pStateIn,
                                T_VDM_BUF* const  pStateOut);

// VDM callback function for C_Digest, C_DigestUpdate, C_DigestKey
typedef int (*fctDigest) (const T_VDM_MECH* const pMech,
                          const unsigned int      flags,
                          const T_VDM_BUF* const  pDataIn,
                          const T_VDM_BUF* const  pStateIn,
                                T_VDM_BUF* const  pResultOut);

// VDM callback function for C_GenerateKey or C_GenerateKeyPair
typedef int (*fctGenKey) (const T_VDM_MECH* const pMech,
                                T_VDM_KEY* const  pKey);

// VDM callback function for C_Derive
typedef int (*fctDerive) (const T_VDM_MECH* const pMech,
                          const T_VDM_KEY* const  pBaseKey,
                                T_VDM_KEY* const  pKey);

// VDM callback function for C_Wrap
typedef int (*fctWrap)   (const T_VDM_MECH* const pMech,
                          const T_VDM_KEY* const  pWrappingKey,
                          const T_VDM_KEY* const  pKey,
                                T_VDM_BUF* const  pWrappedKey);

// VDM callback function for C_Unwrap
typedef int (*fctUnwrap) (const T_VDM_MECH* const pMech,
                          const T_VDM_KEY* const  pUnwrappingKey,
                          const T_VDM_BUF* const  pWrappedKey,
                                T_VDM_KEY* const  pKey);

// VDM callback function for C_DestroyObject
typedef int (*fctDelKey) (const T_VDM_KEY* const  pKey);

typedef enum
{
  VDM_FCT_ENCRYPT,
  VDM_FCT_DECRYPT,
  VDM_FCT_SIGN,
  VDM_FCT_VERIFY,
  VDM_FCT_DIGEST,
  VDM_FCT_GENKEY,
  VDM_FCT_DERIVE,
  VDM_FCT_WRAP,
  VDM_FCT_UWRAP,
  VDM_FCT_DELKEY
} T_VDM_FCT_TYPE;

typedef union {
    fctCrypt   Encrypt;
    fctCrypt   Decrypt;
    fctSign    Sign;
    fctVerify  Verify;
    fctDigest  Digest;
    fctGenKey  GenKey;
    fctDerive  Derive;
    fctWrap    Wrap;
    fctUnwrap  Unwrap;
    fctDelKey  DelKey;
} T_VDM_CB_FCT;

#define VDM_PRIORITY_DEFAULT (0)

struct vdmCallback
{
  T_VDM_FCT_TYPE fctType;
  T_VDM_CB_FCT   cbFct;
};


#endif //__CXI_VDM_H__

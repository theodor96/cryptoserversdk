/**************************************************************************************************
 *
 * $File Identification                    $
 * $Filename          : cxi.h              $
 * $Module version    : x.x.x.x            $
 * $Module name       : CXI                $
 * $Release Date      : DD.MM.YYYY         $
 *
 * Author             : Dipl. Ing. Sven Kaltschmidt
 *                      Utimaco IS GmbH
 *
 * Description        : CryptoServer CXI Interface
 *                      Public interface
 *
 **************************************************************************************************/

#ifndef FW_INCLUDE_CXI_H_
#define FW_INCLUDE_CXI_H_

#include "cxi_defs.h"

#include <hash.h>
#include <db.h>
#include <os_mem.h>

/******************************************************************************
 *
 * module identification
 *
 ******************************************************************************/
#define CXI_MDL_ID          0x68                              // ID of the module
#define CXI_MDL_NAME        "CXI"                             // Abbreviation of the module
#ifdef CS2_SDK
  #define CXI_MDL_NAMEX     "Crypto eXtended Interf.SDK"      // Long name of the module
#else
  #ifdef DEBUG
    #define CXI_MDL_NAMEX   "Crypto.eXtended Interf.DBG"      // Long name of the module
  #else
    #define CXI_MDL_NAMEX   "Crypto.eXtended Interf."         // Long name of the module
  #endif
#endif
#define CXI_MDL_VERSION     0x02040201                        // Version of the module  (d.x.d.d)


/******************************************************************************
 *
 * Error Codes:  (0xB0000000 | (CXI_MDL_ID << 16) | (errno))
 *
 ******************************************************************************/
// --- BEGIN ERROR CODES ---

#define E_CXI                                       0xB068        // CryptoServer module CXI
// general errors
#define E_CXI_MALLOC                                0xB0680000    // memory allocation error
#define E_CXI_PERMISSION_DENIED                     0xB0680001    // permission denied
#define E_CXI_BUF_SIZE                              0xB0680002    // buffer size too small
#define E_CXI_NOT_SUPPORTED                         0xB0680003    // function not supported
#define E_CXI_MBK_NOT_LOADED                        0xB0680004    // MBK firmware module not loaded
#define E_CXI_INVALID_PARAM_TAG                     0xB0680005    // invalid parameter tag
#define E_CXI_INVALID_PARAM_LEN                     0xB0680006    // invalid parameter length
#define E_CXI_INVALID_PARAM_VAL                     0xB0680007    // invalid parameter value
#define E_CXI_INVALID_FLAGS                         0xB0680008    // invalid flags
#define E_CXI_SFC_RFU                               0xB0680009    // SFC is reserved for further use
#define E_CXI_INTERNAL                              0xB068000A    // an internal error occured
#define E_CXI_MBK_TYPE                              0xB068000B    // invalid MBK key type
#define E_CXI_VALIDITY_PERIOD                       0xB068000C    // validity period has expired
#define E_CXI_SMOS_VERSION                          0xB068000D    // SMOS version is too old
// property
#define E_CXI_PROP_ABSENT                           0xB0680010    // property has to be absent
#define E_CXI_PROP_UNKNOWN                          0xB0680011    // unknown property
#define E_CXI_PROP_NOT_FOUND                        0xB0680012    // property not found
#define E_CXI_PROP_EXISTS                           0xB0680013    // property already exists
#define E_CXI_PROP_READONLY                         0xB0680014    // property is read-only
#define E_CXI_PROP_PROTECTED                        0xB0680015    // property is protected
#define E_CXI_PROP_TAG                              0xB0680016    // invalid property tag
#define E_CXI_PROP_VAL                              0xB0680017    // invalid property value
#define E_CXI_PROP_LEN                              0xB0680018    // invalid property length
#define E_CXI_PROP_SENSITIVE                        0xB0680019    // property is sensitive
#define E_CXI_PROP_COMPARE                          0xB068001A    // property doesn't match given template
#define E_CXI_PROP_LOCAL_ONLY                       0xB068001B    // property only valid for objects in a group
// key
#define E_CXI_KEY_INVALID_ALGO                      0xB0680020    // invalid key algo
#define E_CXI_KEY_INVALID_SIZE                      0xB0680021    // invalid key size
#define E_CXI_KEY_INVALID_TAG                       0xB0680022    // invalid key tag
#define E_CXI_KEY_INVALID_COMP                      0xB0680023    // invalid key component
#define E_CXI_KEY_BLOB_FORMAT                       0xB0680024    // invalid format of key blob
#define E_CXI_KEY_TYPE                              0xB0680025    // invalid key type
#define E_CXI_KEY_BLOB_MAC                          0xB0680026    // invalid mac of key blob
#define E_CXI_KEY_INVALID_NAME                      0xB0680027    // invalid key name
#define E_CXI_KEY_INVALID_TOKEN                     0xB0680028    // invalid key token
#define E_CXI_KEY_MISSING_COMP                      0xB0680029    // missing key component
#define E_CXI_KEY_EXTERNAL_ONLY                     0xB068002A    // configuration only allows external keys
#define E_CXI_KEY_EXPORT_DENIED                     0xB068002B    // key export is denied
#define E_CXI_KEY_IMPORT_DENIED                     0xB068002C    // key import is denied
#define E_CXI_KEY_MECH_NOT_ALLOWED                  0xB068002D    // mechanism not allowed
#define E_CXI_KEY_INVALID_BLEN                      0xB068002E    // invalid block length
#define E_CXI_KEY_USAGE                             0xB068002F    // illegal key usage
// crypt
#define E_CXI_CRYPT_PADDING                         0xB0680030    // invalid padding
#define E_CXI_CRYPT_MECH                            0xB0680031    // invalid mechanism
#define E_CXI_CRYPT_IV_LEN                          0xB0680032    // invalid IV length
#define E_CXI_CRYPT_SIGN_VERIFY                     0xB0680033    // signature verification failed
#define E_CXI_CRYPT_DATA_LEN                        0xB0680034    // invalid data length
#define E_CXI_CRYPT_MECH_PARA                       0xB0680035    // invalid mechanism parameter
// item
#define E_CXI_ITEM_NOT_FOUND                        0xB0680040    // item not found
#define E_CXI_ITEM_TAG                              0xB0680041    // invalid item tag
#define E_CXI_ITEM_LEN                              0xB0680042    // invalid item length
#define E_CXI_ITEM_VAL                              0xB0680043    // invalid item value
#define E_CXI_ITEM_COUNT                            0xB0680044    // invalid number of items
// file
#define E_CXI_FILE_SIZE                             0xB0680050    // invalid file size
// misc extended internal interface
#define E_CXI_ABORT_ENUM                            0xB0680060    // enumeration was aborted
#define E_CXI_INVALID_IN_PARAM                      0xB0680061    // invalid input parameter
#define E_CXI_INTERNAL_INPUT_ONLY                   0xB0680062    // external input objects not allowed
#define E_CXI_OVERWRITE                             0xB0680063    // Overwrite in this context not available
// VDM
#define E_CXI_VDM_CB_NOT_REGISTERED                 0xB0680070    // callback not registered
#define E_CXI_VDM_MECH_NOT_HANDLED                  0xB0680071    // VDM mech not handled
#define E_CXI_VDM_CB_DATA_INCONSISTENT              0xB0680072    // VDM cb produced more data than allocated
#define E_CXI_VDM_CB_STATE_INVALID                  0xB0680073    // VDM cb returns not expected state buffer
#define E_CXI_VDM_CB_BUF_LEN_ZERO                   0xB0680074    // VDM cb returns a zero length buffer
// backup blob
#define E_CXI_BB_WRONG_MBK                          0xB0680080    // key blob encrypted with different MBK
#define E_CXI_BB_TBK_PASSPHRASE                     0xB0680081    // wrong TBK passphrase for this key blob
// FIPS
#define E_CXI_FIPS                                  0xB06801      // FIPS mode
#define E_CXI_FIPS_BLOCKED                          0xB0680100    // function not available in FIPS mode
#define E_CXI_FIPS_MECH                             0xB0680101    // mechanism not supported in FIPS mode
#define E_CXI_FIPS_OBJ_TYPE                         0xB0680102    // object type not available in FIPS mode
#define E_CXI_FIPS_ALGO                             0xB0680103    // algorithm not available in FIPS mode
#define E_CXI_FIPS_KEY_SIZE                         0xB0680104    // key size not allowed in FIPS mode
#define E_CXI_FIPS_KEY_IMPORT                       0xB0680105    // clear text key import not allowed in FIPS mode
#define E_CXI_FIPS_KEY_EXPORT                       0xB0680106    // clear text key export not allowed in FIPS mode
#define E_CXI_FIPS_PROP                             0xB0680107    // property not available in FIPS mode
#define E_CXI_NO_FIPS_CURVE                         0xB0680108    // Curve not available in FIPS mode
#define E_CXI_FIPS_KEY_USAGE                        0xB0680109    // Key usage is restricted in FIPS mode
#define E_CXI_FIPS_USAGE_NOT_SET                    0xB0680110    // initial FIPS usage must be set
#define E_CXI_FIPS_PAD_MECH_WRONG                   0xB0680111    // wrong padding mechanism set in FIPS mode
//SECURE
#define E_CXI_SECURE                                0xB06802      // SECURE
#define E_CXI_SECURE_PROP_DECRYPT                   0xB0680200    // decrypt property true not allowed
#define E_CXI_SECURE_PROP_ENCRYPT                   0xB0680201    // encrypt property true not allowed
#define E_CXI_SECURE_PROP_ALWAYS_SENSITIVE_FALSE    0xB0680202    // always sensitive property false not allowed
#define E_CXI_SECURE_PROP_SENSITIVE_FALSE           0xB0680203    // sensitive property false not allowed
#define E_CXI_SECURE_PROP_WRAP                      0xB0680204    // wrap property true not allowed
#define E_CXI_SECURE_PUBLIC_WRAPPING                0xB0680205    // cannot use public keys for wrapping
#define E_CXI_SECURE_PROP_CHECK_VALUE               0xB0680206    // check value missing or invalid
// CC
#define E_CXI_CC                                    0xB06803      // CC mode
#define E_CXI_CC_BLOCKED                            0xB0680300    // function not available in CC mode
#define E_CXI_CC_MECH                               0xB0680301    // mechanism not available in CC mode
#define E_CXI_CC_ALGO                               0xB0680302    // algorithm not available in CC mode
#define E_CXI_CC_PADDING                            0xB0680303    // padding mode not available in CC mode
#define E_CXI_CC_KEY_SIZE                           0xB0680304    // key size invalid in CC mode
#define E_CXI_CC_KEY_PROP                           0xB0680305    // key property invalid in CC mode
#define E_CXI_CC_MECH_PARA                          0xB0680306    // mechanism parameter invalid in CC mode
#define E_CXI_CC_EXTERNAL_KEYS                      0xB0680307    // external keys not available in CC mode
#define E_CXI_CC_KEY_BLOCKED                        0xB0680308    // too many key authorization failures
#define E_CXI_CC_KEY_NOT_INITIALISED                0xB0680309    // key must be initialized before use
#define E_CXI_CC_KEY_NOT_AUTHORISED                 0xB068030A    // key must be authorized before use
#define E_CXI_CC_KEY_AUTH_FAILED                    0xB068030B    // key authorization failed
#define E_CXI_CC_KEY_AUTH_PUBLIC                    0xB068030C    // key authorization not supported for public keys
#define E_CXI_CC_KEY_NOT_BLOCKED                    0xB068030D    // key is not blocked as expected
#define E_CXI_CC_ASSIGNED_KEY_PUBLIC                0xB068030E    // only secret and private keys can be assigned keys
#define E_CXI_CC_ASSIGNED_KEY_EXPORT                0xB068030F    // assigned keys may not be copied, exported or imported
#define E_CXI_CC_OVERWRITE                          0xB0680310    // overwrite flag not available in CC mode
#define E_CXI_CC_IMPORT_PLAIN                       0xB0680311    // clear text import of secret/private keys not allowed in CC mode
#define E_CXI_CC_EXPORT_PLAIN                       0xB0680312    // clear text export of secret/private keys not allowed in CC mode
#define E_CXI_CC_KEY_ALREADY_INITIALISED            0xB0680313    // key is already initialized
#define E_CXI_CC_KRAD_INTEGRITY_FAILED              0xB0680314    // invalid signature over public key
#define E_CXI_CC_MS_SECRET_BLOB                     0xB0680315    // import/export of CSP/CNG secret/private keys not supported in CC mode

// --- END ERROR CODES ---

/******************************************************************************
 *
 * types
 *
 ******************************************************************************/

typedef void T_CXI_DB;

typedef struct
{
  unsigned int  prop;
  unsigned int  l_value;
  unsigned char *p_value;
}
T_CXI_PROP;

typedef struct
{
  unsigned char *p_exp;
  unsigned int  l_exp;
  unsigned char *p_mod;
  unsigned int  l_mod;
  unsigned char *p_p;
  unsigned int  l_p;
  unsigned char *p_q;
  unsigned int  l_q;
  unsigned char *p_dp;
  unsigned int  l_dp;
  unsigned char *p_dq;
  unsigned int  l_dq;
  unsigned char *p_u;
  unsigned int  l_u;
  unsigned char *p_exp2;
  unsigned int  l_exp2;
}
T_CXI_RSA_COMP;

typedef struct
{
  unsigned char *p_curve;
  unsigned int  l_curve;
  unsigned char *p_pub;
  unsigned int  l_pub;
  unsigned char *p_sec;
  unsigned int  l_sec;
}
T_CXI_ECC_COMP;

typedef struct
{
  unsigned char *p_p;
  unsigned int  l_p;
  unsigned char *p_q;
  unsigned int  l_q;
  unsigned char *p_g;
  unsigned int  l_g;
  unsigned char *p_pub;
  unsigned int  l_pub;
  unsigned char *p_sec;
  unsigned int  l_sec;
}
T_CXI_DSA_COMP;

typedef struct
{
  unsigned char *p_val;
  unsigned int  l_val;
}
T_CXI_SYM_COMP;

typedef struct
{
  unsigned int algo;
  union
  {
    T_CXI_RSA_COMP rsa;
    T_CXI_ECC_COMP ecc;
    T_CXI_DSA_COMP dsa;
    T_CXI_SYM_COMP sym;
  }
  u;
}
T_CXI_KEY_COMP;


typedef struct vdmCallback T_CXI_VDM_CB;

typedef struct __CXI_CTX T_CXI_CTX;

typedef struct _CXI_INFO T_CXI_INFO;
typedef struct _CXI_ATTR T_CXI_ATTR;
typedef struct _CXI_ATTRSET T_CXI_ATTRSET;
typedef struct _CXI_ITEM T_CXI_ITEM;
typedef struct _CXI_MECH T_CXI_MECH;
typedef struct _CXI_DP_FIPS_PARA T_CXI_DP_FIPS_PARA;

/******************************************************************************
 *
 * public interface
 *
 ******************************************************************************/
typedef struct
{
  // Standard Functions
  void   *p_data;
  int    (*p_start)(T_OS_MDL_HDL, void*, void*);
  int    (*p_stop)(void);
  int    (*p_pre_replace)(void);
  int    (*p_pre_delete)(void);
  void   *dumy;
  const void *p_module_info;

  // LEGACY public functions BEGIN

  int (*p_cxi_int_key_import)
  (
    unsigned int    flags,              // I: CXI_FLAG_KEY_VOLATILE | CXI_FLAG_KEY_OVERWRITE
    T_CXI_PROP      *p_prop_tab,        // I: property list
    unsigned int    nprops,             // I: number of elements
    T_CXI_KEY_COMP  *p_key_comp         // I: key components
  );

  int (*p_cxi_int_key_export)
  (
    unsigned int    flags,              // I:  rfu
    T_CXI_PROP      *p_prop_tab,        // IO: property list
    unsigned int    nprops,             // I:  number of elements
    T_CXI_KEY_COMP  *p_key_comp         // IO: key components (has to be freed by cxi_int_free_key_comp)
  );

  int (*p_cxi_int_free_key_comp)
  (
    T_CXI_KEY_COMP *p_key_comp          // I: key components
  );

  // new as of 2.1.1.0
  int (*p_cxi_int_key_import_ex)
  (
    unsigned int    flags,              // I: CXI_FLAG_KEY_VOLATILE | CXI_FLAG_KEY_OVERWRITE | CXI_FLAG_KEY_EXTERNAL
    T_CXI_PROP      *p_prop_tab,        // I: property list
    unsigned int    nprops,             // I: number of elements
    T_CXI_KEY_COMP  *p_key_comp,        // I: key components
    unsigned char   **pp_key_obj,       // O: key object (key blob in case of flags & CXI_FLAG_KEY_EXTERNAL, key handle otherwise). Memory allocation!
    unsigned int    *p_l_key_obj        // O: length of key object
  );

  int (*p_cxi_int_key_export_ex)
  (
    unsigned int    flags,              // I:  rfu
    unsigned char   *p_key_obj,         // I:  key object (either key blob or key handle) or NULL if key is identified by p_id parameter
    unsigned int    l_key_obj,          // I:  length of key object
    T_CXI_PROP      *p_id,              // I:  list of properties that identify the database key (name/group/specifier). Ignored if p_key_obj != NULL
    unsigned int    nids,               // I:  number of elements in property list
    T_CXI_PROP      *p_prop_tab,        // IO: list of properties to be retrieved (empty values on function entry, filled by the function).
    unsigned int    nprops,             // I:  number of elements in property list
    T_CXI_KEY_COMP  *p_key_comp         // IO: key components (has to be freed by cxi_int_free_key_comp)
  );

  // LEGACY public functions END

  // NEW LIBRARY public functions BEGIN

  int (*p_cxi_int_cxidb_alloc)
  (
    DB *p_db, // if NULL, a database of the given name will be opened
    char* psz_db_name, // if NULL, the default name will be used
    T_CXI_DB **p_p_cxidb, // pointer to a pointer that will receive the allocated handle
    char *kuu_name
  );

  void (*p_cxi_int_cxidb_free)
  (
    T_CXI_DB **p_p_cxidb // pointer to the pointer to be freed.
  );

  int (*p_cxi_int_item_alloc)
  (
    unsigned int size,
    T_OS_MEM_TYPE type,
    T_CXI_ITEM *p_ba
  );

  void (*p_cxi_int_item_free)
  (
    T_CXI_ITEM *p_ba
  );

  void (*p_cxi_int_attrset_free)
  (
    T_CXI_ATTRSET *p_attrset
  );

  int (*p_cxi_int_attrset_copy)
  (
    const T_CXI_ATTRSET *p_attrset_src,
    const T_CXI_ATTR* p_attr_src,
    T_CXI_ATTRSET *p_attrset_dst
  );

  int (*p_cxi_int_attr_type)
  (
    unsigned int attr_id,
    unsigned int *p_type
  );

  const T_CXI_PROP *(*p_cxi_int_attr_map)
  (
    const char *name,
    int id
  );

  int (*p_cxi_int_attr_set)
  (
    T_CXI_ATTRSET *p_attrset,
    unsigned int attr_id,
    unsigned char *p_val,
    unsigned int len
  );

  int (*p_cxi_int_attr_exists)
  (
    T_CXI_ATTRSET *p_attrset,
    unsigned int attr_id
  );

  int (*p_cxi_int_attr_get_byte_buffer)
  (
    T_CXI_ATTRSET *p_attrset,
    unsigned int attr_id,
    unsigned char *p_buf,
    unsigned int  *p_len
  );

  int (*p_cxi_int_attr_set_int)
  (
    T_CXI_ATTRSET *p_ttrset,
    unsigned int attr_id,
    unsigned int val
  );

  int (*p_cxi_int_attr_get_int)
  (
    T_CXI_ATTRSET *p_attrset,
    unsigned int attr_id,
    unsigned int *p_val
  );

  int (*p_cxi_int_attr_set_bool)
  (
    T_CXI_ATTRSET *p_attrset,
    unsigned int attr_id,
    unsigned char val
  );

  int (*p_cxi_int_attr_get_bool)
  (
    T_CXI_ATTRSET *p_attrset,
    unsigned int attr_id,
    unsigned char *p_val
  );

  int (*p_cxi_int_attr_set_date)
  (
    T_CXI_ATTRSET *p_attrset,
    unsigned int attr_id,
    unsigned int time
  );

  int (*p_cxi_int_attr_get_date)
  (
    T_CXI_ATTRSET *p_attrset,
    unsigned int attr_id,
    unsigned int *p_time
  );

  // NEW LIBRARY public functions END

  // EXTENDED INTERNAL API public functions BEGIN

  int (*p_cxi_int_get_info)
  (
    T_CXI_CTX* const p_ctx,
    T_CXI_INFO* p_info
  );

  int (*p_cxi_int_key_dsa_xgen)
  (
    T_CXI_CTX* const p_ctx,
    T_CXI_MECH *p_mech,
    unsigned int psize,
    unsigned int qsize,
    unsigned char *p_p,
    unsigned char *p_q,
    unsigned char *p_g
  );

  int (*p_cxi_int_key_backup)
  (
    T_CXI_CTX* const p_ctx,
    T_CXI_ITEM *p_key,
    T_CXI_ITEM *p_res_blob
  );

  int (*p_cxi_int_key_restore)
  (
    T_CXI_CTX* const p_ctx,
    unsigned int flags,
    T_CXI_ITEM *p_blob,
    T_CXI_ATTRSET *p_attrset,
    T_CXI_ITEM *p_res_key
  );

  int (*p_cxi_int_key_list)
  (
    T_CXI_CTX* const p_ctx,
    unsigned char* p_skey,
    T_CXI_ATTRSET *p_filter_attrset,
    unsigned int *p_n_key_attrset,
    T_CXI_ATTRSET *p_key_attrset
  );

  int (*p_cxi_int_key_generate)
  (
    T_CXI_CTX* const p_ctx,
    unsigned int flags,
    T_CXI_MECH *p_mech,
    T_CXI_ATTRSET *p_key_attrset,
    T_CXI_ITEM *p_res_key
  );

  int (*p_cxi_int_key_open)
  (
    T_CXI_CTX* const p_ctx,
    unsigned int flags,
    T_CXI_ATTRSET *p_key_attrset,
    T_CXI_ITEM *p_res_key
  );

  int (*p_cxi_int_key_delete)
  (
    T_CXI_CTX* const p_ctx,
    T_CXI_ITEM *p_key,
    T_CXI_ATTRSET *p_attrset
  );

  int (*p_cxi_int_key_prop_get)
  (
    T_CXI_CTX* const p_ctx,
    T_CXI_ITEM* p_key,
    T_CXI_ATTRSET *p_attrset_desired,
    T_CXI_ATTRSET *p_attrset_output
  );

  int (*p_cxi_int_key_prop_set)
  (
    T_CXI_CTX* const p_ctx,
    T_CXI_ITEM* p_key,
    T_CXI_ATTRSET *p_attrset,
    T_CXI_ITEM* p_res_key
  );

  int (*p_cxi_int_key_export_ext)
  (
    T_CXI_CTX* const p_ctx,
    unsigned int type,
    T_CXI_MECH *p_mech,
    T_CXI_ITEM *p_key,
    T_CXI_ITEM *p_kek,
    T_CXI_ITEM *p_res_blob
  );

  int (*p_cxi_int_key_import_ext)
  (
    T_CXI_CTX* const p_ctx,
    unsigned int flags,
    unsigned int type,
    T_CXI_MECH *p_mech,
    T_CXI_ATTRSET *p_attrset,
    T_CXI_ITEM *p_blob,
    T_CXI_ITEM *p_kek,
    T_CXI_ITEM *p_res_key
  );

  int (*p_cxi_int_hash_compute)
  (
    T_CXI_CTX* const p_ctx,
    unsigned int flags,
    T_CXI_ITEM *p_key,
    T_CXI_MECH *p_mech,
    T_CXI_ITEM *p_secret,
    T_CXI_ITEM *p_data,
    T_CXI_ITEM *p_prepend,
    T_CXI_ITEM *p_append,
    T_CXI_ITEM *p_hash,
    unsigned int *p_hash_size,
    T_CXI_ITEM *p_res
  );

  int (*p_cxi_int_crypt)
  (
    T_CXI_CTX* const p_ctx,
    unsigned int flags,
    T_CXI_ITEM *p_key,
    T_CXI_MECH *p_mech,
    const unsigned int nitems,
    T_CXI_ITEM *p_data_in,
    unsigned int *p_size_out,
    T_CXI_ITEM *p_data_out,
    T_CXI_ITEM *p_iv_out,
    T_CXI_ITEM *p_at_out,
    T_CXI_ITEM *p_ic_out,
    T_CXI_ITEM *p_ii_out,
    T_CXI_ITEM *p_tk_out,
    T_CXI_ITEM *p_ti_out
  );

  int (*p_cxi_int_sign)
  (
    T_CXI_CTX* const p_ctx,
    unsigned int flags,
    T_CXI_ITEM *p_key,
    T_CXI_MECH *p_mech,
    unsigned int nitems,
    T_CXI_ITEM *p_data_in,
    unsigned int *p_size_out,
    T_CXI_ITEM *p_data_out,
    T_CXI_ITEM *p_ii_out
  );

  int (*p_cxi_int_verify)
  (
    T_CXI_CTX* const p_ctx,
    unsigned int flags,
    T_CXI_ITEM *p_key,
    T_CXI_MECH *p_mech,
    T_CXI_ITEM *p_data_in,
    T_CXI_ITEM *p_sign_in,
    unsigned int *p_size_out,
    T_CXI_ITEM *p_data_out
  );

  int (*p_cxi_int_secret_agree)
  (
    T_CXI_CTX* const p_ctx,
    unsigned int flags,
    T_CXI_MECH *p_mech,
    T_CXI_ITEM *p_key_prv,
    T_CXI_ITEM *p_key_pub,
    T_CXI_ITEM *p_secret_out
  );

  int (*p_cxi_int_key_derive)
  (
    T_CXI_CTX* const p_ctx,
    unsigned int flags,
    T_CXI_ITEM *p_key,
    T_CXI_MECH *p_mech,
    T_CXI_ATTRSET *p_attrset,
    T_CXI_ITEM *p_res_key
  );

  int (*p_cxi_int_key_dsa_pqgen)
  (
    T_CXI_CTX* const p_ctx,
    T_CXI_MECH *p_mech,
    T_CXI_DP_FIPS_PARA *p_dp_fips_para,
    unsigned int psize,
    unsigned int qsize,
    T_CXI_ITEM *p_seed_out,
    T_CXI_ITEM *p_p_out,
    T_CXI_ITEM *p_q_out
  );

  int (*p_cxi_int_key_dsa_ggen)
  (
    T_CXI_CTX* const p_ctx,
    T_CXI_DP_FIPS_PARA *p_dp_fips_para,
    unsigned int l_p,
    unsigned char *p_p,
    unsigned int l_q,
    unsigned char *p_q,
    unsigned char *p_g
  );

  int (*p_cxi_int_key_split)
  (
    T_CXI_CTX* const p_ctx,
    T_CXI_ITEM *p_key,
    unsigned int nitems,
    unsigned int const *flags,
    unsigned int const *offset,
    T_CXI_ATTRSET *p_attrset,
    T_CXI_ITEM *p_res_key
  );

  // EXTENDED INTERNAL API public functions END

  int (*p_cxi_int_register_vdm)
  (
    T_CXI_VDM_CB* pVDMCallback,
    char          priority
  );
}
T_CXI_TABLE_PUB;

#ifdef _CXI_C_INT_
  // LEGACY public functions BEGIN

  //-----------------------------------------------------------------------------
  // function prototypes used by the module (internal)
  //-----------------------------------------------------------------------------
  // Standard Functions
  int  cxi_start(T_OS_MDL_HDL, void*, void*);
  int  cxi_stop(void);
  int  cxi_pre_replace(void);
  int  cxi_pre_delete(void);

  extern int cxi_int_free_key_comp
  (
    T_CXI_KEY_COMP *p_key_comp          // I: key components
  );

  // new as of 2.1.1.0
  extern int cxi_int_key_import_ex
  (
    unsigned int    flags,              // I: CXI_FLAG_KEY_VOLATILE | CXI_FLAG_KEY_OVERWRITE | CXI_FLAG_KEY_EXTERNAL
    T_CXI_PROP      *p_prop_tab,        // I: property list
    unsigned int    nprops,             // I: number of elements
    T_CXI_KEY_COMP  *p_key_comp,        // I: key components
    unsigned char   **pp_key_obj,       // O: key object (key blob in case of flags & CXI_FLAG_KEY_EXTERNAL, key handle otherwise). Memory allocation!
    unsigned int    *p_l_key_obj        // O: length of key object
  );

  extern int cxi_int_key_export_ex
  (
    unsigned int    flags,              // I:  rfu
    unsigned char   *p_key_obj,         // I:  key object (either key blob or key handle) or NULL if key is identified by p_id parameter
    unsigned int    l_key_obj,          // I:  length of key object
    T_CXI_PROP      *p_id,              // I:  list of properties that identify the database key (name/group/specifier). Ignored if p_key_obj != NULL
    unsigned int    nids,               // I:  number of elements in property list
    T_CXI_PROP      *p_prop_tab,        // IO: list of properties to be retrieved (empty values on function entry, filled by the function).
    unsigned int    nprops,             // I:  number of elements in property list
    T_CXI_KEY_COMP  *p_key_comp         // IO: key components (has to be freed by cxi_int_free_key_comp)
  );

  // LEGACY public functions END

  // NEW LIBRARY public functions BEGIN

  extern int cxi_int_cxidb_alloc(
    DB *p_db,
    char* psz_db_name,
    T_CXI_DB **p_p_cxidb,
    char *kuu_name
  );

  extern void cxi_int_cxidb_free(
    T_CXI_DB **p_p_cxidb
  );

  extern int cxi_int_item_alloc
  (
    unsigned int size,
    T_OS_MEM_TYPE type,
    T_CXI_ITEM *p_item
  );

  extern void cxi_int_item_free
  (
    T_CXI_ITEM *p_item
  );

  extern void cxi_int_attrset_free
  (
    T_CXI_ATTRSET *p_attrset
  );

  extern int cxi_int_attrset_copy
  (
    const T_CXI_ATTRSET *p_attrset_src,
    const T_CXI_ATTR* p_attr,
    T_CXI_ATTRSET *p_attrset_dst
  );

  extern int cxi_int_attr_type
  (
    unsigned int attr_id,
    unsigned int *p_type
  );

  extern const T_CXI_PROP *cxi_int_attr_map
  (
    const char *name,
    int id
  );

  extern int cxi_int_attr_set
  (
    T_CXI_ATTRSET *p_attrset,
    unsigned int attr_id,
    unsigned char *p_val,
    unsigned int len
  );

  extern int cxi_int_attr_exists
  (
    T_CXI_ATTRSET *p_attrset,
    unsigned int attr_id
  );

  extern int cxi_int_attr_get_byte_buffer(
    T_CXI_ATTRSET *p_attrset,
    unsigned int attr_id,
    unsigned char *p_buf,
    unsigned int  *p_len
  );

  extern int cxi_int_attr_set_int
  (
    T_CXI_ATTRSET *p_attrset,
    unsigned int attr_id,
    unsigned int val
  );

  extern int cxi_int_attr_get_int
  (
    T_CXI_ATTRSET *p_attrset,
    unsigned int attr_id,
    unsigned int *p_val
  );

  extern int cxi_int_attr_set_bool
  (
    T_CXI_ATTRSET *p_attrset,
    unsigned int attr_id,
    unsigned char val
  );

  extern int cxi_int_attr_get_bool
  (
    T_CXI_ATTRSET *p_attrset,
    unsigned int attr_id,
    unsigned char *p_val
  );

  extern int cxi_int_attr_set_date
  (
    T_CXI_ATTRSET *p_attrset,
    unsigned int attr_id,
    unsigned int time
  );

  extern int cxi_int_attr_get_date
  (
    T_CXI_ATTRSET *p_attrset,
    unsigned int attr_id,
    unsigned int *p_time
  );

  // NEW LIBRARY public functions END

  // EXTENDED INTERNAL API public functions BEGIN

#include "cxi_eii.h"

  // EXTENDED INTERNAL API public functions END
  extern int cxi_int_register_vdm
  (
    T_CXI_VDM_CB* pVDMCallback,
    char          priority
  );
#else
  //-----------------------------------------------------------------------------
  // external interface to be used by other modules
  //-----------------------------------------------------------------------------
  extern MDL_GLOBAL T_OS_MDL_HDL        P_CXI;

  #define _P_CXI                        ((T_CXI_TABLE_PUB *)P_CXI)         // shortcut

  #define P_cxi_data                    (_P_CXI->_p_data);

  #define CONST const

  // LEGACY public functions BEGIN

  // Standard Functions
  #define cxi_start                     _P_CXI->p_start
  #define cxi_stop                      _P_CXI->p_stop
  #define cxi_pre_replace               _P_CXI->p_pre_replace
  #define cxi_pre_delete                _P_CXI->p_pre_delete

  // Specific Functions
  #define cxi_int_free_key_comp         _P_CXI->p_cxi_int_free_key_comp
  // new as of 2.1.1.0
  #define cxi_int_key_import_ex         _P_CXI->p_cxi_int_key_import_ex
  #define cxi_int_key_export_ex         _P_CXI->p_cxi_int_key_export_ex

  // new as of 3.0.0.1
  // NEW LIBRARY public functions BEGIN

  #define cxi_int_cxidb_alloc           _P_CXI->p_cxi_int_cxidb_alloc
  #define cxi_int_cxidb_free            _P_CXI->p_cxi_int_cxidb_free
  #define cxi_int_item_alloc            _P_CXI->p_cxi_int_item_alloc
  #define cxi_int_item_free             _P_CXI->p_cxi_int_item_free
  #define cxi_int_attrset_free          _P_CXI->p_cxi_int_attrset_free
  #define cxi_int_attrset_copy          _P_CXI->p_cxi_int_attrset_copy
  #define cxi_int_attr_type             _P_CXI->p_cxi_int_attr_type
  #define cxi_int_attr_map              _P_CXI->p_cxi_int_attr_map
  #define cxi_int_attr_set              _P_CXI->p_cxi_int_attr_set
  #define cxi_int_attr_exists           _P_CXI->p_cxi_int_attr_exists
  #define cxi_int_attr_get_byte_buffer  _P_CXI->p_cxi_int_attr_get_byte_buffer
  #define cxi_int_attr_set_int          _P_CXI->p_cxi_int_attr_set_int
  #define cxi_int_attr_get_int          _P_CXI->p_cxi_int_attr_get_int
  #define cxi_int_attr_set_bool         _P_CXI->p_cxi_int_attr_set_bool
  #define cxi_int_attr_get_bool         _P_CXI->p_cxi_int_attr_get_bool
  #define cxi_int_attr_set_date         _P_CXI->p_cxi_int_attr_set_date
  #define cxi_int_attr_get_date         _P_CXI->p_cxi_int_attr_get_date

  // NEW LIBRARY public functions END

  // EXTENDED INTERNAL API public functions BEGIN

  #define cxi_int_get_info              _P_CXI->p_cxi_int_get_info
  #define cxi_int_key_dsa_xgen          _P_CXI->p_cxi_int_key_dsa_xgen
  #define cxi_int_key_backup            _P_CXI->p_cxi_int_key_backup
  #define cxi_int_key_restore           _P_CXI->p_cxi_int_key_restore
  #define cxi_int_key_list              _P_CXI->p_cxi_int_key_list
  #define cxi_int_key_generate          _P_CXI->p_cxi_int_key_generate
  #define cxi_int_key_open              _P_CXI->p_cxi_int_key_open
  #define cxi_int_key_delete            _P_CXI->p_cxi_int_key_delete
  #define cxi_int_key_prop_get          _P_CXI->p_cxi_int_key_prop_get
  #define cxi_int_key_prop_set          _P_CXI->p_cxi_int_key_prop_set
  #define cxi_int_key_export_ext        _P_CXI->p_cxi_int_key_export_ext
  #define cxi_int_key_import_ext        _P_CXI->p_cxi_int_key_import_ext
  #define cxi_int_hash_compute          _P_CXI->p_cxi_int_hash_compute
  #define cxi_int_crypt                 _P_CXI->p_cxi_int_crypt
  #define cxi_int_sign                  _P_CXI->p_cxi_int_sign
  #define cxi_int_verify                _P_CXI->p_cxi_int_verify
  #define cxi_int_secret_agree          _P_CXI->p_cxi_int_secret_agree
  #define cxi_int_key_derive            _P_CXI->p_cxi_int_key_derive
  #define cxi_int_key_dsa_pqgen         _P_CXI->p_cxi_int_key_dsa_pqgen
  #define cxi_int_key_dsa_ggen          _P_CXI->p_cxi_int_key_dsa_ggen
  #define cxi_int_key_split             _P_CXI->p_cxi_int_key_split
  // EXTENDED INTERNAL API public functions END

  #define cxi_int_register_vdm          _P_CXI->p_cxi_int_register_vdm

#endif // _CXI_C_INT_

#endif // FW_INCLUDE_CXI_H_

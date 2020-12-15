/**************************************************************************************************
 *
 * $File Identification                    $
 * $Filename          : mbk.h              $
 * $Module version    : 2.0.0.0            $
 * $Module name       : MBK                $
 * $Release Date      : 27.11.2006         $
 *
 * Author             : Dipl. Ing. Sven Kaltschmidt
 *                      Utimaco IS GmbH
 *
 * Description        : CryptoServer Module MBK
 *                      Global header file
 *                       
 **************************************************************************************************/
#ifndef __MBK_H_PUB_INCLUDED__
#define __MBK_H_PUB_INCLUDED__

#include "os_mdl.h"
#include "util.h"
#include "vdes.h"
#include "aes.h"

//-----------------------------------------------------------------------------
// module identification:  
//-----------------------------------------------------------------------------
#define MBK_MDL_ID          0x96                          // ID of the module            
#define MBK_MDL_NAME        "MBK"                         // Abbreviation of the module                            
#ifdef CS2_SDK                                            
  #define MBK_MDL_NAMEX     "Master Backup Key Module SDK"   // Long name of the module                               
#else
  #ifdef DEBUG
    #define MBK_MDL_NAMEX   "Master Backup Key Mod DBG"      // Long name of the module                               
  #else                                                       
    #define MBK_MDL_NAMEX   "Master Backup Key Module"       // Long name of the module  
  #endif                               
#endif
#define MBK_MDL_VERSION     0x02040100                    // Version of the module  (d.x.d.d)     

//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------

#define MBK_DB_MAX_KEYS               ( 256 )

// flags values for all functions
#define MBK_FLG_HASH_SHOW             0x00000001      // show hash value instead of typing it in
#define MBK_FLG_OW                    0x00000002      // overwrite existing key without verification
#define MBK_FLG_HASH_SET_LB           0x00000040      // set hash verification length (default: 3)
#define MBK_FLG_KEY_SHOW              0x00000080      // show clear text characters instead of '*'
#define MBK_FLG_NO_HASH_VERIFY        0x00000100      // don't verify key hash
#define MBK_FLG_KEY_TYPE_AES          0x00000200      // generate / import AES key instead of DES key

#define MBK_MAC_FLG_SET_N(n)          (((n) & 0xFF) << 24)  // sets number of key shares
#define MBK_MAC_FLG_SET_K(k)          (((k) & 0xFF) << 16)  // sets number of key shares required

#define MBK_MAC_FLG_HASH_SET_LB(lb)   (MBK_FLG_IMP_PP_HASH_SET_LB | ((lb) & 0xF) << 2) 


// ver_rec_no values for the function 'mbk_import_sc()'
#define MBK_SC_REC_SAME               0x00            // old key record is the same as for the new key
#define MBK_SC_VER_PP                 0xff            // old key to be verified has to be keyed in at the pinpad

// info structure returned by 'mbk_sc_info()'
#define MBK_NAME_LB                   8               // Maximum length of a MBK name

#define MBK_INFO_TYPE_1ST             0x00            // 1st key part
#define MBK_INFO_TYPE_2ND             0x01            // 2nd key part
#define MBK_INFO_TYPE_DES             0x00            // DES key
#define MBK_INFO_TYPE_AES             0x02            // AES key
#define MBK_INFO_TYPE_KEY_SHARE       0x04            // part of key set

//
#define MBK_SYM_ENCDEC_MODE_0         ( 0 )
#define MBK_SYM_MAC_MODE_0            ( 0 )

typedef struct
{
  unsigned int    rec_nr;	                            // record number on smartcard
  unsigned char   name[MBK_NAME_LB];                  // key name
  unsigned int    type;                               // key type (MBK_INFO_TYPE_1ST / MBK_INFO_TYPE_2ND)
  TIME_STR        ts_gen;                             // structure contains generation date and time
  unsigned char   hash[8];                            // part of key hash
}
T_MBK_SC_INFO;

typedef struct
{
  unsigned char name[8];
  unsigned char type;       // MBK_INFO_TYPE_2ND | MBK_INFO_TYPE_AES | MBK_INFO_TYPE_KEY_SHARE
  unsigned char dt[6];
  unsigned char key_len;
  unsigned char hash[16];
  unsigned char n;
  unsigned char k; 
  unsigned char id;         // x-value of key share 
}
T_MBK_KEY_INFO;

typedef struct 
{
    unsigned int l;
    unsigned int h;
} T_MBK_CACHE_HANDLE;

#define MBK_INVALIDATE_CACHE_HANDLE( p, l ) os_mem_set( (p), 0, (l) )

typedef struct 
{
    const unsigned char *p_kdf_iv;     // I: Pointer to IV parameter of KDF SP800108 (can be NULL)
    unsigned int l_kdf_iv;             // I: Length of IV parameter of KDF SP800108
    const unsigned char *p_kdf_fixdat; // I: String used for key derivation. This will by used by CXI as the string for TBK derivation
    unsigned int l_kdf_fixdat;         // I: This will be used by CXI as the string for TBK derivation
    const unsigned char *p_cbc_iv_inp; // I: Pointer to CBC IV vector for AES-CBC operation (can be NULL. If so, the IV will be initialized to all zero)
    unsigned int l_cbc_iv_inp;         // I: Length of the CBC IV. Must be either 0, if p_cbc_iv is NULL, or greater or equal to AES_BLOCK_SIZE
    unsigned char *p_cbc_iv_out;       // O: Pointer to CBC IV vector to receive the resulting IV after the  AES-CBC operation (can be NULL)
    unsigned int l_cbc_iv_out;         // I: Length of the buffer to receive the resulting IV after AES-CBC operation.
    void *p_cache_handle;              // I: Pointer to a cache handle (or NULL if caching is disabled)
    unsigned int l_cache_handle;       // I: Length of structure pointed to by p_cache_handle
} T_MBK_SYM_ENCDEC_MODE_0_INFO;

typedef struct 
{
    const unsigned char *p_kdf_iv;      // I: Pointer to IV parameter of KDF SP800108 (can be NULL)
    unsigned int l_kdf_iv;              // I: Length of IV parameter of KDF SP800108
    const unsigned char *p_kdf_fixdat;  // I: String used for key derivation. This will by used by CXI as the string for TBK derivation
    unsigned int l_kdf_fixdat;          // I: This will be used by CXI as the string for TBK derivation
    const unsigned char *p_mac_iv_inp;  // I: Pointer to MAC IV vector for AES-CMAC operation (can be NULL. If so, the IV will be initialized to all zero)
    unsigned int l_mac_iv_inp;          // I: Length of the MAC IV. Must be either 0, if p_cbc_iv is NULL, or greater or equal to /* TBD */
    void *p_cache_handle;               // I: Pointer to a cache handle (or NULL if caching is disabled)
    unsigned int l_cache_handle;        // I: Length of structure pointed to by p_cache_handle
    // FYI: In case of AES-CMAC / MBK_SYM_MAC_MODE_0 the resulting IV is in p_mac_out
} T_MBK_SYM_MAC_MODE_0_INFO;

// some definitions due to backward compatibility
#define MBK_FLG_IMP_PP_HASH_SHOW          MBK_FLG_HASH_SHOW     
#define MBK_FLG_IMP_PP_OW                 MBK_FLG_OW            
#define MBK_FLG_IMP_PP_HASH_SET_LB        MBK_FLG_HASH_SET_LB   
#define MBK_FLG_IMP_PP_KEY_SHOW           MBK_FLG_KEY_SHOW      
#define MBK_FLG_IMP_PP_NO_HASH_VERIFY     MBK_FLG_NO_HASH_VERIFY
#define MBK_FLG_IMP_PP_KEY_TYPE_AES       MBK_FLG_KEY_TYPE_AES  
                                          
#define MBK_SC_OWR                        0xfe

// sub function codes of the external interface (Module ID = 0x96)
#define MBK_EXT_SFC_TEST                  0
#define MBK_EXT_SFC_PERS                  1
#define MBK_EXT_SFC_LIST_KEYS             2
#define MBK_EXT_SFC_GEN_KEK               3
#define MBK_EXT_SFC_GENERATE              4
#define MBK_EXT_SFC_IMPORT                5

// sub function codes of the 2nd external interface (Module ID = 0x69)
#define MBK_EI_SFC_IMPORT_PP              0
#define MBK_EI_SFC_IMPORT_DES_SC          1
#define MBK_EI_SFC_IMPORT_AES_SC          2
#define MBK_EI_SFC_GENERATE_DES_SC        3
#define MBK_EI_SFC_GENERATE_AES_SC        4
#define MBK_EI_SFC_SC_INFO                5
#define MBK_EI_SFC_SC_COPY                6
#define MBK_EI_SFC_SC_CHG_PIN             7
#define MBK_EI_SFC_KEY_PP_2_SC            8
#define MBK_EI_SFC_GEN_DES_KEY_SHARES     9
#define MBK_EI_SFC_GEN_AES_KEY_SHARES     10                                         

// pp_app bit mask definitions for the funtion mbk_ei_register()
#define MBK_EI_PP_REG_IMP_PP              0x00000001      // "Import MBK from PINPad",
#define MBK_EI_PP_REG_IMP_DES_SC          0x00000002      // "Import DES MBK from smartcard",
#define MBK_EI_PP_REG_IMP_AES_SC          0x00000004      // "Import AES MBK from smartcard",
#define MBK_EI_PP_REG_GEN_DES_SC          0x00000008      // "Generate DES MBK on smartcard",
#define MBK_EI_PP_REG_GEN_AES_SC          0x00000010      // "Generate AES MBK on smartcard",
#define MBK_EI_PP_REG_SC_INFO             0x00000020      // "List MBKs on smartcard",
#define MBK_EI_PP_REG_SC_COPY             0x00000040      // "Copy MBK smartcard",
#define MBK_EI_PP_REG_SC_CHG_PIN          0x00000080      // "Change MBK smartcard PIN",
#define MBK_EI_PP_REG_KEY_PP_2_SC         0x00000100      // "Import MBK from PINPad and write to SC"
#define MBK_EI_PP_REG_GEN_DES_KEY_SHARES  0x00000200      // "Generate DES Key Shares and store on SC"
#define MBK_EI_PP_REG_GEN_AES_KEY_SHARES  0x00000400      // "Generate AES Key Shares and store on SC"

// default database slots
#define MBK_EI_KEY_NO_DES                 0
#define MBK_EI_KEY_NO_TMP                 1
#define MBK_EI_KEY_NO_AES                 3
                                          
// default key names                      
#define MBK_EI_DES_KEY_NAME               "EIDESKEY"
#define MBK_EI_AES_KEY_NAME               "EIAESKEY"
                                          
// default smartcard records              
#define MBK_EI_REC_NO_DES                 1
#define MBK_EI_REC_NO_AES                 15


//-----------------------------------------------------------------------------
// public interface:  
//-----------------------------------------------------------------------------
typedef struct
{  
  void   *p_data;
  int    (*p_start)(T_OS_MDL_HDL, void*, void*);
  int    (*p_stop)(void);  
  int    (*p_pre_replace)(void);
  int    (*p_pre_delete)(void);
  void   *p_dumy1;
  
  int (*p_mbk_import_pp)            // ! obsolete, use mbk_import_pp_ex instead
  (
    unsigned int  key_no,           // I: database slot number to store key at (0..3)
    unsigned int  ver_rec_no,       // I: smartcard record the old key is read from (1..16)
                                    //    or manual entry at the pinpad (0)
    unsigned int  flags             // I: function behaviour (see doc)
  );
  
  int (*p_mbk_import_sc)            // ! obsolete, use mbk_import_sc_ex instead
  (
    unsigned int  key_no,           // I: database slot number to store key at (0..3)
    unsigned int  rec_no,           // I: smartcard record number to read the new key from (1..16)
    unsigned int  ver_rec_no,       // I: smartcard record number to read the old key from (1..16)
                                    //    or smartcard records numbers are the same (MBK_SC_REC_SAME)
                                    //    or old key is keyed in at the pinpad (MBK_SC_VER_PP)
                                    //    or overwrite key without verification (MBK_SC_OWR)
    unsigned int  *p_key_lb,        // O: length of key
    unsigned char *p_key_name       // O: name of key read (8 bytes)
  );  
  
  int (*p_mbk_generate_sc)          // ! obsolete, use mbk_generate_sc_ex instead
  (
    unsigned int  rec_no,           // I: smartcard record number to store key at                                           
    unsigned int  key_lb,           // I: desired key length 
    unsigned char *p_key_name       // I: key name on the smartcard
  );

  int (*p_mbk_get_key)              // ! obsolete, use mbk_get_key_ex instead
  (
    unsigned int  key_no,           // I: key slot with requested key data
    unsigned int  *p_key_len,       // O: pointer to key length in bytes
    unsigned char **pp_key          // O: address of pointer to key data
  );

  int (*p_mbk_get_vkey)             // ! obsolete, use mbk_get_key_ex instead
  (
    unsigned int key_no,            // I: key slot with requested key data
    VDES_KEY     **pp_keyt          // O: address of pointer to VDES structure
  );  

  int (*p_mbk_sc_info)
  (
    unsigned int   *p_nentries,     // O: pointer to number of entries found
    T_MBK_SC_INFO  **pp_mbk_sc_info // O: address of pointer to array with information 
                                    //    structures for all keys found
  );

  int (*p_mbk_sc_copy)(void);
  int (*p_mbk_sc_chg_pin)(void);

  int (*p_mbk_write_sc)             // ! obsolete, use mbk_write_sc_ex instead
  (
    unsigned int  rec_no,           // I: smartcard record number to store key at
    unsigned int  key_len,          // I: key length
    unsigned char *p_key,           // I: pointer to key
    unsigned char *p_key_name       // I: key name on the smartcard
  );
  
  int (*p_mbk_get_aes_key)          // ! obsolete, use mbk_get_key_ex instead
  (
    unsigned int key_no,            // I: key slot with requested key data
    unsigned int mode,              // I: mode of the requested key (AES_ENC or AES_DEC)
    AES_KEY      **pp_keyt          // O: address of pointer to AES structure
  );

  int (*p_mbk_ei_register)
  (
    unsigned int mask_pp_app        // I: bit mask of desired pinpad applications
  );

  int (*p_mbk_ei_ctl)               // I: obsolete, do not longer use
  (
    unsigned int param,             // I: parameter to be set
    void         *p_value           // I: pointer to parameter value
  );
  
  const void  *p_module_info;

  // new for version 2
  int (*p_mbk_import_pp_ex)
  (
    unsigned int  key_no,           // I: database slot number to store key at (0..3)
    unsigned int  ver_rec_no,       // I: smartcard record the old key is read from (1..16)
                                    //    or manual entry at the pinpad (0)
    unsigned int  flags,            // I: function behaviour (see doc)
    unsigned int  key_len           // I: desired key length    
  );

  int (*p_mbk_import_sc_ex)
  (
    unsigned int  key_no,           // I: database slot number to store key at (0..3)
    unsigned int  rec_no,           // I: smartcard record number to read the new key from (1..16)
    unsigned int  ver_rec_no,       // I: smartcard record number to read the old key from (1..16)
                                    //    or smartcard records numbers are the same (MBK_SC_REC_SAME)
                                    //    or old key is keyed in at the pinpad (MBK_SC_VER_PP)                                  
    unsigned int  flags,            // I: control flags
    unsigned int  *p_key_len,       // O: length of key
    unsigned char *p_key_name       // O: name of key read (8 bytes)
  );
  
  int (*p_mbk_generate_sc_ex)
  (
    unsigned int  rec_no,           // I: smartcard record number to store key at
    unsigned int  flags,            // I: control flags
    unsigned int  key_len,          // I: desired key length 
    unsigned char *p_key_name       // I: key name on the smartcard    
  );

  int (*p_mbk_write_sc_ex)
  (
    unsigned int  rec_no,           // I: smartcard record number to store key at
    unsigned int  flags,            // I: control flags
    unsigned int  key_len,          // I: key length
    unsigned char *p_key,           // I: pointer to key
    unsigned char *p_key_name       // I: key name on the smartcard
  );  

  int (*p_mbk_get_key_ex)
  (
    unsigned int  key_no,           // I: key slot with requested key data
    unsigned int  *p_type,          // O: key type (AES / DES)
    unsigned int  *p_key_len,       // O: key length in bytes
    unsigned char **pp_key,         // O: key data
    void          **pp_enc_keyt,    // O: encryption token  (VDES_KEY / AES_KEY)
    void          **pp_dec_keyt     // O: decryption token  (NULL / AES_KEY)
  );

  // new for version 2.1
  int (*p_mbk_ks_split)
  (
    unsigned int  l_secret,         // I: length of secret (e.g. key)
    unsigned char *p_secret,        // I: secret (e.g. key) to be split into shares
    unsigned int  k,                // I: number of shares needed to reconstruct secret
    unsigned int  n,                // I: number of shares to be created  
    unsigned int  l_share,          // I: length of shares (== length of prime)
    unsigned char *p_sx,            // O: pointer to array of x-values, caller allocated array of size n
    unsigned char *p_sy             // O: pointer to array of y-values, caller allocated array of size n * l_share
  );

  int (*p_mbk_ks_combine)
  (
    unsigned int  k,                // I: number of shares given
    unsigned int  l_share,          // I: length of shares (== length of prime)
    unsigned char *p_sx,            // I: pointer to array of x-values
    unsigned char *p_sy,            // I: pointer to array of y-values
    unsigned int  l_secret,         // I: expected length of secret
    unsigned char *p_secret         // O: combined secret (e.g. key)
  );

  // new for version 2.2.0.0
  int (*p_mbk_get_key_info)
  (
    unsigned int    key_no,         // I: key slot with requested key data
    T_MBK_KEY_INFO  *p_key_info     // O: key info structure
  );
  
  int (*p_mbk_derive_mac_key)
  (
    unsigned int   *p_algo,       // O: algorithm of mac key (MBK_INFO_TYPE_DES or MBK_INFO_TYPE_AES)
    unsigned int   *l_mac,        // O: length of derived mac key
    unsigned char  *der_mac_key   // O: address of pointer to mac key (caller allocates memory)
  );

  int (*p_mbk_derive_crypt_key)
  (
    unsigned int   *p_algo,         // O: algorithm of crypt key (MBK_INFO_TYPE_DES or MBK_INFO_TYPE_AES)
    unsigned int   *l_crypt,        // O: length of derived crypt key
    unsigned char  *der_crypt_key   // O: address of pointer to crypt key (caller allocates memory)
  );

  // new for version 2.3.0.0
  int (*p_mbk_derive_key_sp800108)
  (
    unsigned int    key_no,         // I: master backup key slot to derive a key from.
    unsigned int    mode,           // I: KDF SP800108 mode. 
    unsigned int    mac_algo,       // I: KDF SP800108 mac algorithm
    unsigned int    hash_algo,      // I: KDF SP800108 hash_algorithm
    unsigned char*  p_iv,           // I: KDF SP800108 initial vector
    unsigned int    l_iv,           // I: KDF SP800108 length of initial vector
    unsigned char*  p_fixdat,       // I: KDF SP800108 fixed input data
    unsigned int    l_fixdat,       // I: KDF SP800108 length of fixed input data 
    unsigned int    l_key,          // I: KDF SP800108 length of requested derived key
    unsigned char*  p_key           // O: pointer to buffer (at least l_key bytes in size) to received the derived key
  );

  // new for version 2.4.0.0
  int (*p_mbk_sym_encrypt)
  (
        const unsigned int key_no,          // I: MBK key number (Slot) used to derive the key
        const unsigned int mode_select,     // I: Mode of operation (See below)
        const void *_p_mode_info,           // I: Pointer to additional data needed to define the mode (See below)
        const unsigned int l_mode_info,     // I: Length of additional data provided to define the mode (See below)
        const unsigned char *p_data_inp,    // I: Pointer to input data buffer
        const unsigned int l_data_inp,      // I: Length of input data buffer
        unsigned char *p_data_out,          // I/O: Pointer to output buffer. The function writes the encrypted data into this buffer
        unsigned int *p_l_data_out          // I/O: Max size of output buffer. The function stores the length of the encrypted data here
  );
  
  int (*p_mbk_sym_decrypt)
  (
        const unsigned int key_no,          // I: MBK key number (Slot) used to derive the key
        const unsigned int mode_select,     // I: Mode of operation (See below)
        const void *_p_mode_info,           // I: Pointer to additional data needed to define the mode (See below)
        const unsigned int l_mode_info,     // I: Length of additional data provided to define the mode (See below)
        const unsigned char *p_data_inp,    // I: Pointer to input data buffer
        const unsigned int l_data_inp,      // I: Length of input data buffer
        unsigned char *p_data_out,          // I/O: Pointer to output buffer. The function writes the decrypted data into this buffer
        unsigned int *p_l_data_out          // I/O: Max size of output buffer. The function stores the length of the decrypted data here
  );

  int (*p_mbk_sym_mac)
  (
        const unsigned int key_no,          // I: MBK key number (Slot) used to derive the key
        const unsigned int mode_select,     // I: Mode of operation (See below)
        const void *_p_mode_info,           // I: Pointer to additional data needed to define the mode (See below)
        const unsigned int l_mode_info,     // I: Length of additional data provided to define the mode (See below)
        const unsigned char *p_data_inp,    // I: Pointer to input data buffer
        const unsigned int l_data_inp,      // I: Length of input data buffer
        unsigned char *p_mac_out,           // I/O: Pointer to mac buffer. The function writes the mac into this buffer
        unsigned int *p_l_mac_out           // I/O: Max size of mac buffer. The function stores the length of the mac here
  );

} 
T_MBK_TABLE_PUB;


#ifdef _MBK_C_INT_  
  //-----------------------------------------------------------------------------
  // function prototypes used by the module (internal)
  //-----------------------------------------------------------------------------
  
  // plain import  
  int mbk_import
  (
    unsigned int  key_no,           // I: database slot number to store key at (0..3)
    unsigned int  flags,            // I: control flags
    unsigned int  key_len,          // I: key length    
    unsigned char *p_key_raw        // I: pointer to key  
  );
  
  // import from PinPad
  int mbk_import_pp
  (
    unsigned int  key_no,           // I: database slot number to store key at (0..3)
    unsigned int  ver_rec_no,       // I: smartcard record the old key is read from (1..16)
                                    //    or manual entry at the pinpad (0)
    unsigned int  flags             // I: function behaviour (see doc)
  );

  int mbk_import_pp_ex
  (
    unsigned int  key_no,           // I: database slot number to store key at (0..3)
    unsigned int  ver_rec_no,       // I: smartcard record the old key is read from (1..16)
                                    //    or manual entry at the pinpad (0)  
    unsigned int  flags,            // I: function behaviour (see doc)
    unsigned int  key_len           // I: desired key length
  );
  
  // import from smartcard
  int mbk_import_sc
  (
    unsigned int  key_no,           // I: database slot number to store key at (0..3)
    unsigned int  rec_no,           // I: smartcard record number to read the new key from (1..16)
    unsigned int  ver_rec_no,       // I: smartcard record number to read the old key from (1..16)
                                    //    or smartcard records numbers are the same (MBK_SC_REC_SAME)
                                    //    or old key is keyed in at the pinpad (MBK_SC_VER_PP)
                                    //    or overwrite key without verification (MBK_SC_OWR)
    unsigned int  *p_key_lb,        // O: length of key
    unsigned char *p_key_name       // O: name of key read (8 bytes)
  );

  int mbk_import_sc_ex
  (
    unsigned int  key_no,           // I: database slot number to store key at (0..3)
    unsigned int  rec_no,           // I: smartcard record number to read the new key from (1..16)
    unsigned int  ver_rec_no,       // I: smartcard record number to read the old key from (1..16)
                                    //    or smartcard records numbers are the same (MBK_SC_REC_SAME)
                                    //    or old key is keyed in at the pinpad (MBK_SC_VER_PP)                                  
    unsigned int  flags,            // I: control flags
    unsigned int  *p_key_lb,        // O: length of key
    unsigned char *p_key_name       // O: name of key read (8 bytes)
  );
  
  // generate on smartcard
  int mbk_generate_sc
  (
    unsigned int  rec_no,           // I: smartcard record number to store key at                                           
    unsigned int  key_lb,           // I: desired key length 
    unsigned char *p_key_name       // I: key name on the smartcard
  );

  int mbk_generate_sc_ex
  (
    unsigned int  rec_no,           // I: smartcard record number to store key at
    unsigned int  flags,            // I: control flags
    unsigned int  key_len,          // I: desired key length 
    unsigned char *p_key_name       // I: key name on the smartcard  
  );

  // write to smartcard
  int mbk_write_sc
  (
    unsigned int  rec_no,           // I: smartcard record number to store key at
    unsigned int  key_len,          // I: key length
    unsigned char *p_key,           // I: pointer to key
    unsigned char *p_key_name       // I: key name on the smartcard
  );

  int mbk_write_sc_ex
  (
    unsigned int  rec_no,           // I: smartcard record number to store key at
    unsigned int  flags,            // I: control flags
    unsigned int  key_len,          // I: key length
    unsigned char *p_key,           // I: pointer to key
    unsigned char *p_key_name       // I: key name on the smartcard
  );

  // get key functions
  int mbk_get_key
  (
    unsigned int  key_no,           // I: key slot with requested key data
    unsigned int  *p_key_len,       // O: pointer to key length in bytes
    unsigned char **pp_key          // O: address of pointer to key data
  );

  int mbk_get_vkey
  (
    unsigned int key_no,            // I: key slot with requested key data
    VDES_KEY     **pp_keyt          // O: address of pointer to VDES structure
  );    

  int mbk_get_aes_key
  (
    unsigned int key_no,            // I: key slot with requested key data
    unsigned int mode,              // I: mode of the requested key (AES_ENC or AES_DEC)
    AES_KEY      **pp_keyt          // O: address of pointer to AES structure
  );

  int mbk_get_key_ex
  (
    unsigned int  key_no,           // I: key slot with requested key data
    unsigned int  *p_type,          // O: key type (AES / DES)
    unsigned int  *p_key_len,       // O: key length in bytes
    unsigned char **pp_key,         // O: key data
    void          **pp_enc_keyt,    // O: encryption token  (VDES_KEY / AES_KEY)
    void          **pp_dec_keyt     // O: decryption token  (NULL / AES_KEY)
  );

  int mbk_get_key_info
  (
    unsigned int    key_no,         // I: key slot with requested key data
    T_MBK_KEY_INFO  *p_key_info     // O: key info structure
  );

  // management functions
  int mbk_sc_info
  (
    unsigned int   *p_nentries,     // O: pointer to number of entries found
    T_MBK_SC_INFO  **pp_mbk_sc_info // O: address of pointer to array with information 
                                    //    structures for all keys found
  );

  int mbk_sc_copy(void);
  int mbk_sc_chg_pin(void);  

  int mbk_derive_mac_key
  (
    unsigned int   *p_algo,       // O: algorithm of mac key (MBK_INFO_TYPE_DES or MBK_INFO_TYPE_AES)
    unsigned int   *l_mac,        // O: length of derived mac key
    unsigned char  *der_mac_key   // O: address of pointer to mac key (caller allocates memory)
  );

  int mbk_derive_crypt_key
  (
    unsigned int   *p_algo,         // O: algorithm of crypt key (MBK_INFO_TYPE_DES or MBK_INFO_TYPE_AES)
    unsigned int   *l_crypt,        // O: length of derived crypt key
    unsigned char  *der_crypt_key   // O: address of pointer to crypt key (caller allocates memory)
  );  

  // new for version 2.3.0.0
  
  int mbk_derive_key_sp800108  
  (
    unsigned int    key_no,         // I: master backup key slot to derive a key from.
    unsigned int    mode,           // I: KDF SP800108 mode. 
    unsigned int    mac_algo,       // I: KDF SP800108 mac algorithm
    unsigned int    hash_algo,      // I: KDF SP800108 hash_algorithm
    unsigned char*  p_iv,           // I: KDF SP800108 initial vector
    unsigned int    l_iv,           // I: KDF SP800108 length of initial vector
    unsigned char*  p_fixdat,       // I: KDF SP800108 fixed input data
    unsigned int    l_fixdat,       // I: KDF SP800108 length of fixed input data 
    unsigned int    l_key,          // I: KDF SP800108 length of requested derived key
    unsigned char*  p_key           // O: pointer to buffer (at least l_key bytes in size) to received the derived key
  );
  
  // new for version 2.4.0.0
  int mbk_sym_encrypt
  (
        const unsigned int key_no,          // I: MBK key number (Slot) used to derive the key
        const unsigned int mode_select,     // I: Mode of operation (See below)
        const void *_p_mode_info,           // I: Pointer to additional data needed to define the mode (See below)
        const unsigned int l_mode_info,     // I: Length of additional data provided to define the mode (See below)
        const unsigned char *p_data_inp,    // I: Pointer to input data buffer
        const unsigned int l_data_inp,      // I: Length of input data buffer
        unsigned char *p_data_out,          // I/O: Pointer to output buffer. The function writes the encrypted data into this buffer
        unsigned int *p_l_data_out          // I/O: Max size of output buffer. The function stores the length of the encrypted data here
  );
  
  int mbk_sym_decrypt
  (
        const unsigned int key_no,          // I: MBK key number (Slot) used to derive the key
        const unsigned int mode_select,     // I: Mode of operation (See below)
        const void *_p_mode_info,           // I: Pointer to additional data needed to define the mode (See below)
        const unsigned int l_mode_info,     // I: Length of additional data provided to define the mode (See below)
        const unsigned char *p_data_inp,    // I: Pointer to input data buffer
        const unsigned int l_data_inp,      // I: Length of input data buffer
        unsigned char *p_data_out,          // I/O: Pointer to output buffer. The function writes the decrypted data into this buffer
        unsigned int *p_l_data_out          // I/O: Max size of output buffer. The function stores the length of the decrypted data here
  );

  int mbk_sym_mac
  (
        const unsigned int key_no,          // I: MBK key number (Slot) used to derive the key
        const unsigned int mode_select,     // I: Mode of operation (See below)
        const void *_p_mode_info,           // I: Pointer to additional data needed to define the mode (See below)
        const unsigned int l_mode_info,     // I: Length of additional data provided to define the mode (See below)
        const unsigned char *p_data_inp,    // I: Pointer to input data buffer
        const unsigned int l_data_inp,      // I: Length of input data buffer
        unsigned char *p_mac_out,           // I/O: Pointer to mac buffer. The function writes the mac into this buffer
        unsigned int *p_l_mac_out           // I/O: Max size of mac buffer. The function stores the length of the mac here
  );
#else
  //-----------------------------------------------------------------------------
  // public interface to be used by other modules  
  //-----------------------------------------------------------------------------
  extern MDL_GLOBAL T_OS_MDL_HDL P_MBK;

  #define _P_MBK  ((T_MBK_TABLE_PUB *)P_MBK)         // shortcut  

  #define P_mbk_data                (_P_MBK->_p_data);
                                    
  #define mbk_start                 _P_MBK->p_start
  #define mbk_stop                  _P_MBK->p_stop  
  #define mbk_pre_replace           _P_MBK->p_pre_replace
  #define mbk_pre_delete            _P_MBK->p_pre_delete  
                                    
  #define mbk_import_pp             _P_MBK->p_mbk_import_pp     // obsolete
  #define mbk_import_sc             _P_MBK->p_mbk_import_sc     // obsolete
  #define mbk_generate_sc           _P_MBK->p_mbk_generate_sc   // obsolete
  #define mbk_get_key               _P_MBK->p_mbk_get_key       // obsolete
  #define mbk_get_vkey              _P_MBK->p_mbk_get_vkey      // obsolete
  #define mbk_sc_info               _P_MBK->p_mbk_sc_info
  #define mbk_sc_copy               _P_MBK->p_mbk_sc_copy
  #define mbk_sc_chg_pin            _P_MBK->p_mbk_sc_chg_pin
  #define mbk_write_sc              _P_MBK->p_mbk_write_sc      // obsolete
  #define mbk_get_aes_key           _P_MBK->p_mbk_get_aes_key
        
  #define mbk_ei_register           _P_MBK->p_mbk_ei_register  
                                    
  // new for version 2      
  #define mbk_import_pp_ex          _P_MBK->p_mbk_import_pp_ex
  #define mbk_import_sc_ex          _P_MBK->p_mbk_import_sc_ex
  #define mbk_generate_sc_ex        _P_MBK->p_mbk_generate_sc_ex
  #define mbk_write_sc_ex           _P_MBK->p_mbk_write_sc_ex
  #define mbk_get_key_ex            _P_MBK->p_mbk_get_key_ex
        
  // new for version 2.1        
  #define mbk_ks_split              _P_MBK->p_mbk_ks_split
  #define mbk_ks_combine                  _P_MBK->p_mbk_ks_combine

  // new for version 2.2
  #define mbk_get_key_info          _P_MBK->p_mbk_get_key_info
  
  #define mbk_derive_mac_key        _P_MBK->p_mbk_derive_mac_key
  #define mbk_derive_crypt_key      _P_MBK->p_mbk_derive_crypt_key
    
  // new for version 2.3.0.0
  #define mbk_derive_key_sp800108   _P_MBK->p_mbk_derive_key_sp800108

  // new for version 2.4.0.0
  #define mbk_sym_encrypt           _P_MBK->p_mbk_sym_encrypt
  #define mbk_sym_decrypt           _P_MBK->p_mbk_sym_decrypt
  #define mbk_sym_mac               _P_MBK->p_mbk_sym_mac

#endif


//-----------------------------------------------------------------------------
// Error Codes:  (0xB0000000 | (MBK_MDL_ID << 16) | (errno))
//-----------------------------------------------------------------------------

// --- BEGIN ERROR CODES ---  
#define E_MBK                       0xB096      // CryptoServer module MBK                       
                                                
#define E_MBK_PARA                  0xB0960001  // Parameter mismatch                            
#define E_MBK_DB_NO_SERVICE         0xB0960002  // MBK database is suspended                     
#define E_MBK_NULL_PTR              0xB0960003  // Unexpected null pointer                       
#define E_MBK_PERMISSION            0xB0960004  // Permission denied                             
#define E_MBK_ISO_HASH_FAIL         0xB0960005  // ISO hash check of key failed                  
#define E_MBK_IG_KEY_TYPES_NM       0xB0960006  // Key types do not match                        
#define E_MBK_IG_KEY_DATE_NM        0xB0960007  // Key generation date do not match              
#define E_MBK_IG_KEY_TIME_NM        0xB0960008  // Key generation time do not match              
#define E_MBK_IG_KEY_NAME_NM        0xB0960009  // Key names do not match                        
#define E_MBK_EX_KEY_CHK_FAIL       0xB096000a  // Verify of existing master key failed          
#define E_MBK_SLOT_EMPTY            0xB096000b  // Slot is empty                                 
#define E_MBK_KEY_NO                0xB096000c  // Slot number not valid                         
#define E_MBK_REC_NO                0xB096000d  // Record number not valid                       
#define E_MBK_KEY_LB                0xB096000e  // Key length not valid                          
#define E_MBK_TIME_WRONG_FORMAT     0xB096000f  // Wrong format in time structure detected       
#define E_MBK_BCD_LB                0xB0960010  // BCD coded time length mismatch                
#define E_MBK_KEY_NAME              0xB0960011  // No key name or NULL pointer for key name      
#define E_MBK_ACTION_CANCELED       0xB0960012  // Action canceled by user                       
#define E_MBK_MODE_INV              0xB0960013  // Invalid mode for AES key passed               
#define E_MBK_DB_VERSION            0xB0960014  // Both versions of the MBK database exists      
#define E_MBK_EI_PARA_SET_EXT       0xB0960015  // External parameter already set from extern and overwrite flag is not set                 
#define E_MBK_AES_NA                0xB0960016  // The AES Module is not available               
#define E_MBK_KEY_TYPE              0xB0960017  // Invalid key type
// new for version 2                
#define E_MBK_ALLOC                 0xB0960018  // memory allocation failed
#define E_MBK_BAD_DB_FORMAT         0xB0960019  // bad database format
#define E_MBK_RECORD_EMPTY          0xB096001A  // smartcard record is empty
#define E_MBK_SC_EMPTY              0xB096001B  // smartcard only contains empty records
#define E_MBK_SEMA_REQ              0xB096001C  // unable to require semaphore
#define E_MBK_MAX_KEK               0xB096001D  // maximum numbers of key exchange keys reached
#define E_MBK_FLAGS_INV             0xB096001E  // invalid flags value
#define E_MBK_INFO_LB               0xB096001F  // info length not valid
#define E_MBK_KEY_EXISTS            0xB0960020  // key alread exists
#define E_MBK_SHARE_LB              0xB0960021  // invalid length of key share
#define E_MBK_SHARE_CNT             0xB0960022  // invalid number of key shares
#define E_MBK_ECA_NA                0xB0960023  // the ECA module is not available
#define E_MBK_IG_KEY_SHARE_CNT_NM   0xB0960024  // number of key shares doesn't match
#define E_MBK_KEY_ID_INV            0xB0960025  // invalid key ID 
#define E_MBK_KEY_ID_SAME           0xB0960026  // multiple occurence of same key ID 
#define E_MBK_KEK_NOT_FOUND         0xB0960027  // no kek found with given hash
#define E_MBK_NOT_SUPPORTED         0xB0960028  // function is not supported 
#define E_MBK_NO_PP                 0xB0960029  // no PIN pad module found
#define E_MBK_NO_SC                 0xB096002A  // no smartcard module found
//#define E_MBK_FIPS_BLOCKED          0xB096002B  // function not available in FIPS mode
//#define E_MBK_CC_BLOCKED            0xB096002C  // not allowed in CC Endorsed Mode
//#define E_MBK_DEPRECATED            0xB096002D  // function is deprecated
#define E_MBK_LENGTH                0xB096002E  // The length of a parameter is wrong
#define E_MBK_OVER_UNDER_FLOW       0xB096002F  // A computation overflowed or underflowed
// --- END ERROR CODES ---  


#endif // __MBK_H_PUB_INCLUDED__  

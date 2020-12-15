/*****************************************************************************
 *
 *  $File Identification                    $
 *  $Filename          : asn1.h             $
 *  $Module version    : x.x.x.x            $
 *  $Module name       : ASN1               $
 *  $Release Date      : DD.MM.YYYY         $
 *
 *  Author(s)   : Dipl. Inf. (FH) stefan Gohmann
 *                Utimaco IS GmbH
 *
 *  Description : Global header file of CS2000 module ASN1
 *                Must be included in every CS2000 software that uses
 *                functions of this module
 *
 *  History     :
 *  Date       |                 Action                  |  Author
 *  ***********|*****************************************|*******************
 *  05.11.2001 | Creation                                |  Stefan Gohmann
 *  13.08.2002 | Some asn1 tags added, and tag numbers   |  Ralf Vennemann
 *             | for SEQUENCE and SET corrected          |
 *****************************************************************************/
#ifndef __ASN1_H_PUB_INCLUDED__
  #define __ASN1_H_PUB_INCLUDED__

#include "os_mdl.h"
#include "os_mem.h"



/*****************************************************************************-
   module identification:
  ****************************************************************************/

#define ASN1_MDL_ID          0x91                        /* ID of the module */
#define ASN1_MDL_NAME        "ASN1"                      /* Abbreviation of the module */
#ifdef CS2_SDK
  #define ASN1_MDL_NAMEX     "Asn1 Module SDK"           /* Long name of the module */
#else
  #ifdef DEBUG
    #define ASN1_MDL_NAMEX   "Asn1 Module DEBUG"         /* Long name of the module */
  #else
    #define ASN1_MDL_NAMEX   "Asn1 Module"               /* Long name of the module */
  #endif
#endif
#define ASN1_MDL_VERSION     0x01000307                  /* Version of the module */



typedef struct
{
  unsigned int    tag;      /* tag, type and class of ASN.1 item   */
  unsigned int    len;      /* data length of item                 */
  unsigned char   *p_data;  /* pointer to data                     */
  unsigned short  raw_off;  /* offset to raw item                  */
  unsigned short  nitems;   /* number of items of structured type  */
} ASN1_ITEM;




/* contruct a tag: */

#define ASN_TAG(cla,type,num)   ((cla)|(type)|((num) << 3))

/* extract from a tag: */

#define ASN_NUM_OF(tag)     ((tag) >> 3)
#define ASN_CLASS_OF(tag)   ((tag) & 7)

/* definitions for 'class': */

#define ASN_UNIVERSAL     0
#define ASN_APPLICATION   2
#define ASN_CONTEXT       4
#define ASN_PRIVATE       6

/* definitions for 'type': */

#define ASN_PRIMITIV      0
#define ASN_STRUCT        1

#define ASN_IS_STRUCT(tag)      (((tag) & ASN_STRUCT) != 0)

/* some tags: */

#define ASN_SE(n)               ASN_TAG(ASN_CONTEXT,ASN_STRUCT,(n))   // structured element (e.g. [0] = 0xA0)
#define ASN_PE(n)               ASN_TAG(ASN_CONTEXT,ASN_PRIMITIV,(n)) // primitive element (e.g. [0] = 0x80)

#define ASN_EOC                 ASN_TAG(ASN_CONTEXT,ASN_STRUCT,0)     // end of contents octet, structured
#define ASN_BOOLEAN             ASN_TAG(ASN_UNIVERSAL,ASN_PRIMITIV,1)
#define ASN_INTEGER             ASN_TAG(ASN_UNIVERSAL,ASN_PRIMITIV,2)
#define ASN_BIT_STRING          ASN_TAG(ASN_UNIVERSAL,ASN_PRIMITIV,3)
#define ASN_OCTET_STRING        ASN_TAG(ASN_UNIVERSAL,ASN_PRIMITIV,4)
#define ASN_NULL                ASN_TAG(ASN_UNIVERSAL,ASN_PRIMITIV,5)
#define ASN_OBJECT_ID           ASN_TAG(ASN_UNIVERSAL,ASN_PRIMITIV,6)
#define ASN_ENUMERATED          ASN_TAG(ASN_UNIVERSAL,ASN_PRIMITIV,0x0A)
#define ASN_UTF8STRING          ASN_TAG(ASN_UNIVERSAL,ASN_PRIMITIV,0x0C)
#define ASN_SEQUENCE            ASN_TAG(ASN_UNIVERSAL,ASN_STRUCT,0x10)
#define ASN_SET                 ASN_TAG(ASN_UNIVERSAL,ASN_STRUCT,0x11)
#define ASN_PRINTABLE_STRING    ASN_TAG(ASN_UNIVERSAL,ASN_PRIMITIV,0x13)
#define ASN_TELETEXT_STRING     ASN_TAG(ASN_UNIVERSAL,ASN_PRIMITIV,0x14)
#define ASN_IA5STRING           ASN_TAG(ASN_UNIVERSAL,ASN_PRIMITIV,0x16)
#define ASN_UTCTIME             ASN_TAG(ASN_UNIVERSAL,ASN_PRIMITIV,0x17)
#define ASN_GENERALIZEDTIME     ASN_TAG(ASN_UNIVERSAL,ASN_PRIMITIV,0x18)
#define ASN_ANY                 ASN_TAG(ASN_UNIVERSAL,ASN_PRIMITIV,0xfffff)


// ASN_BOOLEAN types:
#define ASN_TRUE                "\xff"
#define ASN_FALSE               "\x00"


// flags for asn1_encode:
#define ASN_TAGS_ONLY           1       // encode only tags, not the data
#define ASN_LONG_LENGTH         2       // use always long form of length field
#define ASN_USE_PREFIX          4       // insert prefix before data field


// flags for asn1_decode:
#define ASN_TOP_LEVEL_ONLY      1       // decode only top level of ASN1 structure
#define ASN_LEVEL_MASK          0xff
#define ASN_RAW_OFFSET          0x100   // fill in also the raw offset (between l_data and tag)


// flags for asn1_rsa_zka_to_tok:
#define ASN1_RSA_KC_MIN   0x100 // get all components that are available in the given ASN.1 stream


/******************************************************************************
 public interface:
  ****************************************************************************/

typedef struct
{
  /* Standard Function */
  void *p_data;
  int  (*p_start)(T_OS_MDL_HDL,void *, void*);
  int  (*p_stop)(void);
  int  (*p_pre_replace)(void);
  int  (*p_pre_delete)(void);
  void *dumy;
  const void *p_module_info;
  /* Asn1 Functions */
  int (*p_asn1_rsa_zka_to_tok)( unsigned int flag,
                                unsigned int  zka_data_len,
                                unsigned char *p_zka_data,
                                T_OS_MEM_TYPE,
                                unsigned char  **pp_keyt);
  int (*p_asn1_rsa_tok_to_zka)( unsigned int flag1,
                                unsigned char  *p_keyt1,
                                unsigned int flag2,
                                unsigned char  *p_keyt2,
                                int flag, T_OS_MEM_TYPE memtype,
                                unsigned int  *p_zka_data_len,
                                unsigned char **pp_zka_data);
  int (*p_asn1_encode)        ( ASN1_ITEM *p_tab,
                                unsigned int nitems,
                                int flag,
                                unsigned char **pp_data,
                                unsigned int *p_size);
  int (*p_asn1_decode)        ( unsigned char *p_data,
                                unsigned int size,
                                int flag,
                                ASN1_ITEM *p_tab,
                                unsigned int *tab_len );
  int (*p_asn1_find_item)     ( ASN1_ITEM *p_item,
                                unsigned char *p_path,
                                int *p_npath,
                                ASN1_ITEM **pp_entry);
  int (*p_asn1_rsa_pkcs1_to_tok)( unsigned int flag,
                                unsigned int  pkcs1_data_len,
                                unsigned char *p_pkcs1_data,
                                T_OS_MEM_TYPE,
                                unsigned char  **pp_keyt);
  int (*p_asn1_rsa_tok_to_pkcs1)(unsigned int type,
                                unsigned char  *p_keyt1,
                                unsigned char  *p_keyt2,
                                T_OS_MEM_TYPE memtype,
                                unsigned int  *p_pkcs1_data_len,
                                unsigned char **pp_pkcs1_data);
  int (*p_asn1_find_object)   ( unsigned char *p_oid,
                                unsigned int  l_oid,
                                ASN1_ITEM     *p_item,
                                ASN1_ITEM     **pp_found);
  int (*p_asn1_get_item)      ( unsigned int  l_data,
                                unsigned char *p_data,
                                ASN1_ITEM     *p_item);
} T_ASN1_TABLE_PUB;


#ifdef _ASN1_C_INT_
  /* function prototypes used by the module (internal) */
  int  asn1_start(T_OS_MDL_HDL,void *,void *);
  int  asn1_stop(void);
  int  asn1_pre_replace(void);
  int  asn1_pre_delete(void);
  // Asn1 Functions
  int asn1_rsa_zka_to_tok(unsigned int flag,
                          unsigned int  zka_data_len,
                          unsigned char *p_zka_data,
                          T_OS_MEM_TYPE memtype,
                          unsigned char **pp_keyt);
  int asn1_rsa_tok_to_zka(unsigned int flag1,
                          unsigned char  *p_keyt1,
                          unsigned int flag2,
                          unsigned char  *p_keyt2,
                          int flag, T_OS_MEM_TYPE memtype,
                          unsigned int  *p_zka_data_len,
                          unsigned char **pp_zka_data);
  int asn1_encode        (ASN1_ITEM *p_tab,
                          unsigned int nitems,
                          int flag,
                          unsigned char **pp_data,
                          unsigned int *p_size);
  int asn1_decode        (unsigned char *p_data,
                          unsigned int size,
                          int flag,
                          ASN1_ITEM *p_tab,
                          unsigned int *tab_len );
  int asn1_find_item     (ASN1_ITEM *p_item,
                          unsigned char *p_path,
                          int *p_npath,
                          ASN1_ITEM **pp_entry);
  int asn1_find_object   (unsigned char *p_oid,
                          unsigned int  l_oid,
                          ASN1_ITEM     *p_item,
                          ASN1_ITEM     **pp_found);
  int asn1_get_item      (unsigned int  l_data,
                          unsigned char *p_data,
                          ASN1_ITEM     *p_item);
  int asn1_rsa_pkcs1_to_tok(unsigned int flag,
                          unsigned int  pkcs1_data_len,
                          unsigned char *p_pkcs1_data,
                          T_OS_MEM_TYPE memtype,
                          unsigned char **pp_keyt);
  int asn1_rsa_tok_to_pkcs1(unsigned int type,
                          unsigned char  *p_keyt1,
                          unsigned char  *p_keyt2,
                          T_OS_MEM_TYPE memtype,
                          unsigned int  *p_pkcs1_data_len,
                          unsigned char **pp_pkcs1_data);
#else
  /* external interface to be used by other modules */

  extern MDL_GLOBAL T_OS_MDL_HDL P_ASN1;

  #define _P_ASN1         ((T_ASN1_TABLE_PUB *)P_ASN1)         /* shortcut */

  #define P_asn1_data     (_P_ASN1->_p_data);

  #define asn1_rsa_zka_to_tok   _P_ASN1->p_asn1_rsa_zka_to_tok
  #define asn1_rsa_tok_to_zka   _P_ASN1->p_asn1_rsa_tok_to_zka
  #define asn1_encode           _P_ASN1->p_asn1_encode
  #define asn1_decode           _P_ASN1->p_asn1_decode
  #define asn1_find_item        _P_ASN1->p_asn1_find_item
  #define asn1_find_object      _P_ASN1->p_asn1_find_object
  #define asn1_get_item         _P_ASN1->p_asn1_get_item
  #define asn1_rsa_pkcs1_to_tok _P_ASN1->p_asn1_rsa_pkcs1_to_tok
  #define asn1_rsa_tok_to_pkcs1 _P_ASN1->p_asn1_rsa_tok_to_pkcs1

#endif /* _ASN1_C_INT_ */



/* Error Codes:  (0xB0000000 | (ASN1_MDL_ID << 16) | (errno))  */

/* --- BEGIN ERROR CODES --- */

#define E_ASN1                0xB091          /* CryptoServer module ASN1               */
#define E_ASN1_MEM            0xB0910001      /* Memory Error                           */
#define E_ASN1_FLAG           0xB0910002      /* Parameter flag is incorrect            */
#define E_ASN1_TAB_OVL        0xB0910003      /* ASN1_ITEM table overflow               */
#define E_ASN1_BAD_ZKA        0xB0910004      /* bad ZKA format                         */
#define E_ASN1_DATASIZE       0xB0910005      /* ASN1 data overrun                      */
#define E_ASN1_TAGSIZE        0xB0910006      /* tag too big                            */
#define E_ASN1_INDEF_LEN      0xB0910007      /* indefinite length not supportet        */
#define E_ASN1_LENSIZE        0xB0910008      /* lenght field too big                   */
#define E_ASN1_STACK_OVL      0xB0910009      /* internal stack overflow                */
#define E_ASN1_NOT_FOUND      0xB091000A      /* item not found                         */
#define E_ASN1_BUFF_OVL       0xB091000B      /* ASN1 buffer overflow                   */
#define E_ASN1_ITEMCOUNT      0xB091000C      /* bad value of 'nitems' in ITEM table    */
#define E_ASN1_BADTAG         0xB091000D      /* zero tag                               */
#define E_ASN1_BAD_PKCS1      0xB091000E      /* bad PKCS#1 format                      */
#define E_ASN1_DECODE_ERR     0xB091000F      /* decoding error                         */
#define E_ASN1_SIZE_EXCEEDED  0xB0910010      /* calculated size exceeds given datasize */

/* --- END ERROR CODES --- */

#endif /* __ASN1_H_PUB_INCLUDED__ */


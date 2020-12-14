/*****************************************************************************
 *
 *  $File Identification                    $
 *  $Filename          : eca.h              $
 *  $Module version    : x.x.x.x            $
 *  $Module name       : ECA                $
 *  $Release Date      : DD.MM.YYYY         $
 *
 *  Author(s)   : Rainer Herbertz
 *                Utimaco AG
 *
 *  Description : Global header file of CS2000 module ECA
 *                (Elliptic Curve Aritmetic)
 *
 *  History     :
 *  Date       |                 Action                          |  Author
 *  -----------|-------------------------------------------------|---------
 *  14.12.2005 | Creation                                        |  R.H.
 *  15.09.2008 | eca_dp_set_algo()                               |  R.H.
 *  19.12.2008 | eca_dp_unregister()                             |  R.H.
 *****************************************************************************/


#ifndef __ECA_H_PUB_INCLUDED__
  #define __ECA_H_PUB_INCLUDED__

#include <os_mdl.h>
#include <stype.h>


// module identification:

#define ECA_MDL_ID           0x8F            /* ID of the module           */
#define ECA_MDL_NAME         "ECA"           /* Short name of the module   */

#ifdef CS2_SDK
    #define ECA_MDL_NAMEX       "Elliptic Curve Arith. (SDK)"  /* Long name of the module    */
#else
  #ifdef DEBUG
    #define ECA_MDL_NAMEX       "Elliptic Curve Arith. (DEBUG)"
  #else
    #define ECA_MDL_NAMEX       "Elliptic Curve Arith."
  #endif
#endif
#define ECA_MDL_VERSION      0x01010e02         /* Version of the module      */


// flags for eca_int_rnd():

#define ECA_MODE_REAL_RND   0x00                /* use real random generator                    */
#define ECA_MODE_PSEUDO_RND 0x01                /* use pseudo random generator                  */


// flags for eca_point2fmto():

#define ECA_FMT_UNCOMP      4                   // uncompressed format
#define ECA_FMT_COMP        2                   // compressed format
#define ECA_FMT_MASK        6
#define ECA_FMT_X           8                   // x coordinate only


// flags for eca_point_get_len():

#define ECA_LB_INTERN       1                   // internal length in bytes
#define ECA_LB_UNCOMP       ECA_FMT_UNCOMP      // length of uncompressed format in bytes
#define ECA_LB_COMP         ECA_FMT_COMP        // length of compressed format in bytes
#define ECA_LB_X            8                   // length x coordinate in bytes


// flags for eca_dp_get_info():

#define ECA_DP_NAME         1                   // name of curve
#define ECA_DP_OID          2                   // OID of curve
#define ECA_DP_ORDER_INT    3                   // order of curve (internal format)
#define ECA_DP_SIZE         4                   // size of curve (bits)
#define ECA_DP_MODE         5                   // flags associated with curve (see line 118)
#define ECA_DP_G            6                   // pointer to generator point G and its memory size
#define ECA_DP_P            7                   // pointer to prime P and its memory size
#define ECA_DP_NE           8                   // effektive length of field elements in fword
#define ECA_DP_A            9                   // domain parameter A of curve
#define ECA_DP_B           10                   // domain parameter B of curve


#define ECA_SC_BL_LEN 2             // size of scalar blinding value in fwords

// data types:

typedef unsigned int       fword;
#define ECA_WORD_BITS      32
#define ECA_LEN(b)     (((b)+sizeof(fword)-1) / sizeof(fword))

typedef struct ecdp_t ECDP;

typedef struct ecpcp_t ECPCP;


typedef struct
{
    unsigned short      n;          // length of field elements in bytes
    unsigned short      flags;
    unsigned char const *p;         // modulus: prime p or irreducible polymon
    unsigned char const *a;         // elliptic curve parameter a
    unsigned char const *b;         // elliptic curve parameter b
    unsigned char const *Gx;        // x coordinate of generator point
    unsigned char const *Gy;        // y coordinate of generator point
    unsigned int        l_r;        // length of order in bytes
    unsigned char const *r;         // order
    unsigned int        cof;        // cofactor
    char          const *name;      // name of curve
    unsigned short      l_oid;      // length of OID
    unsigned char const *oid;       // object identifier
    unsigned short      la;         // length of a (optional)
    unsigned short      lb;         // length of b (optional)
    unsigned short      lGx;        // length of Gx (optional)
    unsigned short      lGy;        // length of Gy (optional)
} EC_DOMAIN_PARAM;

// flags:
#define ECF_GFTYPE_MASK         1
#define ECF_GFp_FIELD           0
#define ECF_GF2m_FIELD          1
#define ECF_A_IS_MINUS_3        2            // for prime  fields
#define ECF_A_IS_ONE            2            // for binary fields
#define ECF_A_IS_NULL           4
#define ECF_COORDINATE_MASK     0x70         // coordinate type mask, see below                                                  
#define ECF_CMP_MASK            0x7F
#define ECF_SECURE_ALGO         0x80
#define ECF_VAR_LENGTH          0x4000
#define ECF_STATIC_NAME         0x8000
#define ECF_TEMP                0x1000

// ECF_COORDINATE_MASK options: 
// indicates in which form curve parameters a, b, Gx, Gy are given / registered
// !! CURRENTLY the ECA module ONLY supports point arithmetics in short Weierstrass form !!
#define ECF_SHORT_WEIERSTRASS   0x00         //   Short Weierstrass form: 
                                             //      prime field F(p>3) : y^2 = x^3 + a*x + b
                                             //      binary field F(2^m): y^2 + x*y = x^3 + a*x + b, b!=0
#define ECF_MONTGOMERY          0x10         //   Montgomery form:
                                             //      prime field F(p>3): a*y^2 = x^3 + b*x^2 + x
#define ECF_TWISTED_EDWARDS     0x20         //   Twisted Edwards form: 
                                             //      prime field F(p>3): a*x^2 + y^2 = 1 + b*x^2*y^2  


// public interface:

typedef struct
{
    void   *p_data;
    int    (*p_start)();
    int    (*p_stop)(void);
    int    (*p_pre_replace)(void);
    int    (*p_pre_delete)(void);
    void   *p_dumy;
    const void   *p_module_info;

    int    (*p_dp_register)(EC_DOMAIN_PARAM const *,ECDP **);
    int    (*p_dp_find_name)(char const *name,ECDP **p_dp);
    int    (*p_dp_find_oid)(unsigned int,unsigned char const *,ECDP **);
    int    (*p_dp_get_info)(ECDP *,int,unsigned int *,unsigned char **);
    void   (*p_btow)(unsigned int,unsigned char const *,fword *);
    void   (*p_wtob)(fword *,unsigned int,unsigned char *);
    unsigned int (*p_point_get_len)(ECDP *,int);
    int    (*p_point_mul_G)(ECDP *,unsigned int,fword *,fword *);
    int    (*p_point_mul_G_P)(ECDP *,unsigned int,fword *,unsigned int,fword *,fword *,fword *);
    int    (*p_point_mul_G_pcP)(ECDP *,unsigned int,fword *,unsigned int,fword *,ECPCP *,fword *);
    int    (*p_fmto2point)(ECDP *dp,unsigned int,unsigned char const *x,fword *pt);
    int    (*p_point2fmto)(ECDP *dp,fword *pt,int flag,unsigned char *x);
    int    (*p_int_get_wlen)(ECDP *);
    int    (*p_int_get_blen)(ECDP *);
    int    (*p_int_add)(ECDP *,fword *,fword *,fword *);
    int    (*p_int_mul)(ECDP *,fword *, fword *, fword *);
    int    (*p_int_div)(ECDP *, fword *, fword *, fword *);
    int    (*p_int_mod)(ECDP *, unsigned int, fword *, fword *);
    int    (*p_int_rnd)(ECDP *, unsigned int, fword *);
    int    (*p_point2int)(ECDP *, fword *, fword *);
    int    (*p_b2int)(ECDP *,unsigned int,unsigned char const *,fword *);
    int    (*p_point_precalc)(ECDP *dp,fword *a,ECPCP **pp_pcp);
    void   (*p_pcp_free)(ECPCP *p_pcp);
    int    (*p_int_get_cof)(ECDP *,fword *);
    int    (*p_dp_a2s)(unsigned int,unsigned char *,EC_DOMAIN_PARAM *);
    int    (*p_point_check)(ECDP *,fword *);
    int    (*p_dp_register_asn1)(unsigned int,unsigned char *,const char *,unsigned int,
                                 unsigned char *,unsigned int,ECDP **);
    int    (*p_dp_find_asn1)(unsigned int,unsigned char *,ECDP **);
    int    (*p_int_register)(unsigned int,unsigned char *,ECDP **p_dp);
    int    (*p_hash2int)(ECDP *,unsigned int,unsigned char const *,fword *);
    int    (*p_int_sub)(ECDP *,fword *,fword *,fword *);
    int    (*p_hash2int_m)(ECDP *,unsigned int,unsigned char const *,fword *);
    int    (*p_dp_set_algo)(ECDP *,unsigned int);
    void   (*p_dp_unregister)(ECDP *dp);
    int    (*p_point_bl_get)( ECDP *, fword **, fword **);
    void   (*p_point_bl_clr)( void);
    int    (*p_point_add) (ECDP *,fword *,fword *,fword *);
} T_ECA_TABLE_PUB;



#ifdef _ECA_C_INT_

// function prototypes used by the module (internal)

int  eca_start(T_OS_MDL_HDL,void *,void *);
int  eca_stop(void);
int  eca_pre_replace(void);
int  eca_pre_delete(void);

int eca_dp_register
(
    EC_DOMAIN_PARAM const *ecdp,    // (I)    domain parameter
    ECDP                  **p_dp    // (O)    pointer to ECDP structure
);

void eca_dp_unregister(
    ECDP            *dp         // (I) domain parameter
    );

int eca_dp_find_name
(
    char const  *name,    // (I)    name
    ECDP        **p_dp    // (O)    pointer to ECDP structure
);

int eca_dp_find_oid(
    unsigned int         l_oid,    // (I) Length of OID
    unsigned char const  *p_oid,   // (I) object identifier
    ECDP                 **p_dp    // (O) pointer to ECDP structure
    );

int eca_dp_get_info(
    ECDP            *dp,        // (I) domain parameter
    int             flag,       // (I) type of info requested
    unsigned int    *p_len,     // (O) length of value
    unsigned char   **pp_val    // (O) value
    );

void eca_btow
(
    unsigned int   lb,          // (I)    length of octet string
    unsigned char const *b,     // (I)    octet string
    fword          *w           // (O)    fword string
);

void eca_wtob
(
    fword          *w,          // (I)    fword string
    unsigned int   lb,          // (I)    length of octet string
    unsigned char  *b           // (O)    octet string
);

unsigned int eca_point_get_len(ECDP *,int);

int eca_point_mul_G
(
    ECDP           *dp,         // (I)    domain parameter
    unsigned int   l_scalar,    // (I)    scalar length
    fword          *scalar,     // (I)    scalar
    fword          *result      // (O)    result (x, y), size n (each)
);

int eca_point_mul_G_P
(
    ECDP           *dp,         // (I)    domain parameter
    unsigned int   l_sc_g,      // (I)    scalar length
    fword          *sc_g,       // (I)    scalar for G
    unsigned int   l_sc_p,      // (I)    scalar length
    fword          *sc_p,       // (I)    scalar for P
    fword          *p_P,        // (I)    point P (x, y)
    fword          *result      // (O)    result (x, y), size n (each)
);

int eca_point_mul_G_pcP(
    ECDP           *dp,         // (I)    domain parameter
    unsigned int   l_sc_g,      // (I)    scalar length
    fword          *sc_g,       // (I)    scalar for G
    unsigned int   l_sc_p,      // (I)    scalar length
    fword          *sc_p,       // (I)    scalar for P
    ECPCP          *p_pcP,      // (I)    precalculated point P
    fword          *result      // (O)    result (x, y), size n (each)
    );

int eca_fmto2point(
    ECDP                *dp,    // (I)    domain parameter
    unsigned int        lx,     // (I)    length of octet string
    unsigned char const *x,     // (I)    octet string
    fword               *pt     // (O)    point (x, y), size n (each)
    );

int eca_point2fmto(
    ECDP                *dp,    // (I)    domain parameter
    fword               *pt,    // (I)    point (x, y), size n (each)
    int                 flag,   // (I)    compressed / uncompressed format
    unsigned char       *x      // (O)    octet string
    );

int eca_point_check(
    ECDP           *dp,         // (I)  domain parameter
    fword          *pt          // (I)  point to check (x, y)
    );

int eca_int_get_wlen(ECDP *);

int eca_int_get_blen(ECDP *);

int eca_int_add(
    ECDP            *dp,        // (I)    domain parameter
    fword           *a,         // (I)    first operand
    fword           *b,         // (I)    second operand
    fword           *r          // (O)    result
    );

int eca_int_sub(
    ECDP            *dp,        // (I)    domain parameter
    fword           *a,         // (I)    first operand
    fword           *b,         // (I)    second operand
    fword           *r          // (O)    result
    );

int eca_int_mul(
    ECDP            *dp,        // (I)    domain parameter
    fword           *a,         // (I)    first operand
    fword           *b,         // (I)    second operand
    fword           *r          // (O)    result
    );

int eca_int_div(
    ECDP            *dp,        // (I)    domain parameter
    fword           *a,         // (I)    operand 1 or NULL (if a = 1)
    fword           *b,         // (I)    operand 2
    fword           *r          // (O)    result (length order.n)
    );

int eca_int_mod(
    ECDP            *dp,        // (I)    domain parameter
    unsigned int    la,         // (I)    length of operand
    fword           *a,         // (I)    operand
    fword           *r          // (O)    result (length order.n)
    );

int eca_int_rnd(
    ECDP            *dp,        // (I)    domain parameter
    unsigned int    flags,      // (I)    real / pseudo random
    fword           *r          // (O)    result (length order.n)
    );

int eca_point2int(
    ECDP            *dp,        // (I)    domain parameter
    fword           *point,     // (I)    operand (length n)
    fword           *r          // (O)    result (length order.n)
    );

int eca_b2int(
    ECDP                *dp,    // (I)    domain parameter
    unsigned int        lb,     // (I)    length of octet string
    unsigned char const *b,     // (I)    octet string
    fword               *w      // (O)    fword string
    );

int eca_hash2int(
    ECDP                *dp,    // (I)    domain parameter
    unsigned int        lh,     // (I)    length of hash value
    unsigned char const *h,     // (I)    hash value
    fword               *w      // (O)    fword string
    );

int eca_hash2int_m(
    ECDP                *dp,    // (I)    domain parameter
    unsigned int        lh,     // (I)    length of hash value
    unsigned char const *h,     // (I)    hash value
    fword               *w      // (O)    fword string
    );

int eca_int_get_cof(
    ECDP            *dp,        // (I)    domain parameter
    fword           *r          // (O)    result (length order.n)
    );

int eca_int_register(
    unsigned int     l_prime,   // (I) length of prime in bytes
    unsigned char    *p_prime,  // (I) prime (must have a multiple of 32 bits)
    ECDP             **p_dp     // (O) pointer to ECDP structure
    );

int eca_point_precalc
(
    ECDP           *dp,         // (I)    domain parameter
    fword          *a,          // (I)    point  (x, y)
    ECPCP          **pp_pcp     // (O)    precalculated point
);

void eca_pcp_free(ECPCP *p_pcp);


int eca_dp_a2s
(
    unsigned int    l_ecdp,   // (I)    length of ASN.1 structure
    unsigned char   *p_ecdp,  // (I)    ASN.1 struct
    EC_DOMAIN_PARAM *ecdp     // (O)    domain parameter
);

int eca_dp_register_asn1
(
    unsigned int    l_ecdp,   // (I)    length of ASN.1 structure
    unsigned char   *p_ecdp,  // (I)    ASN.1 struct
    const char      *p_name,  // (I)    Name of curve
    unsigned int    l_oid,    // (I)    length of OID
    unsigned char   *p_oid,   // (I)    OID
    unsigned int    flags,    // (I)
    ECDP            **p_dp    // (O)    pointer to ECDP structure
);

int eca_dp_find_asn1
(
    unsigned int    l_ecdp,   // (I)    length of ASN.1 structure
    unsigned char   *p_ecdp,  // (I)    ASN.1 struct
    ECDP            **p_dp    // (O)    pointer to ECDP structure
);

int eca_dp_set_algo
(
    ECDP            *p_dp,    // (I/O)  pointer to ECDP structure
    unsigned int    flags     // (I)    ECF_SECURE_ALGO or 0
);

int _dp_chk_cofactor(
    ECDP            *p_dp     // (I)  pointer to ECDP structure
);

int eca_point_bl_get( ECDP *dp              // (I)    domain parameter
                    , fword **wx            // (O)    x coordinate of q (mod n)
                    , fword **wk_inv);      // (O)    k^-1

void eca_point_bl_clr( void);

int eca_point_add(
    ECDP           *dp,          // (I)    domain parameter
    fword          *a,           // (I)    operand (x, y), size n (each)
    fword          *b,           // (I)    operand (x, y), size n (each)
    fword          *r            // (O)    result  (x, y), size n (each)
);

#else

// external interface to be used by other modules

extern MDL_GLOBAL T_OS_MDL_HDL P_ECA;

#define _P_ECA ((T_ECA_TABLE_PUB *)P_ECA)         /* shortcut */

#define P_eca_data          (_P_ECA->_p_data);

#define eca_start           _P_ECA->p_start
#define eca_stop            _P_ECA->p_stop
#define eca_pre_replace     _P_ECA->p_pre_replace
#define eca_pre_delete      _P_ECA->p_pre_delete

#define eca_dp_register     _P_ECA->p_dp_register
#define eca_dp_register_asn1 _P_ECA->p_dp_register_asn1
#define eca_dp_unregister   _P_ECA->p_dp_unregister
#define eca_dp_find_name    _P_ECA->p_dp_find_name
#define eca_dp_find_oid     _P_ECA->p_dp_find_oid
#define eca_dp_find_asn1    _P_ECA->p_dp_find_asn1
#define eca_dp_get_info     _P_ECA->p_dp_get_info
#define eca_dp_set_algo     _P_ECA->p_dp_set_algo
#define eca_dp_a2s          _P_ECA->p_dp_a2s
#define eca_btow            _P_ECA->p_btow
#define eca_wtob            _P_ECA->p_wtob
#define eca_point_get_len   _P_ECA->p_point_get_len
#define eca_point_mul_G     _P_ECA->p_point_mul_G
#define eca_point_mul_G_P   _P_ECA->p_point_mul_G_P
#define eca_point_mul_G_pcP _P_ECA->p_point_mul_G_pcP
#define eca_fmto2point      _P_ECA->p_fmto2point
#define eca_point2fmto      _P_ECA->p_point2fmto
#define eca_int_get_wlen    _P_ECA->p_int_get_wlen
#define eca_int_get_blen    _P_ECA->p_int_get_blen
#define eca_int_add         _P_ECA->p_int_add
#define eca_int_sub         _P_ECA->p_int_sub
#define eca_int_mul         _P_ECA->p_int_mul
#define eca_int_div         _P_ECA->p_int_div
#define eca_int_mod         _P_ECA->p_int_mod
#define eca_int_rnd         _P_ECA->p_int_rnd
#define eca_int_get_cof     _P_ECA->p_int_get_cof
#define eca_int_register    _P_ECA->p_int_register
#define eca_point2int       _P_ECA->p_point2int
#define eca_b2int           _P_ECA->p_b2int
#define eca_hash2int        _P_ECA->p_hash2int
#define eca_hash2int_m      _P_ECA->p_hash2int_m
#define eca_point_precalc   _P_ECA->p_point_precalc
#define eca_pcp_free        _P_ECA->p_pcp_free
#define eca_point_check     _P_ECA->p_point_check
#define eca_point_bl_get    _P_ECA->p_point_bl_get
#define eca_point_bl_clr    _P_ECA->p_point_bl_clr
#define eca_point_add       _P_ECA->p_point_add

#endif /* _ECA_C_INT_ */


static INLINE void eca_cpy(fword * RESTRICT d,fword * RESTRICT s,unsigned int len)
{
    while(len-- > 0) *d++ = *s++;
}



/* Error Codes:  (0xB0000000 | (ECA_MDL_ID << 16) | (errno))  */

/* --- BEGIN ERROR CODES --- */

#define E_ECA                          0xB08F          // CryptoServer module ECA
#define E_ECA_MEM                      0xB08F0001      // can't alloc memory
#define E_ECA_NOT_SUPP                 0xB08F0002      // not supported
#define E_ECA_BAD_PARAM                0xB08F0003      // bad parameter
#define E_ECA_NOT_FOUND                0xB08F0004      // curve not found
#define E_ECA_EXISTS                   0xB08F0005      // curve already registered
#define E_ECA_TOO_BIG                  0xB08F0006      // input number too big
#define E_ECA_INFINITE                 0xB08F0007      // point at infinity
#define E_ECA_PCP_INCOMP               0xB08F0008      // incompatible precalculated point
#define E_ECA_LEN                      0xB08F0009      // bad length of argument
#define E_ECA_BAD_TAG                  0xB08F000A      // bad tag of point
#define E_ECA_NO_SQRT                  0xB08F000B      // no square root found
#define E_ECA_NO_NON_RESIDUE           0xB08F000C      // non-residue could not be found
#define E_ECA_NO_ASN1                  0xB08F000D      // no ASN.1 module found
#define E_ECA_ECDP_DECODE              0xB08F000E      // error decoding ASN.1 EC domain parameter
#define E_ECA_BAD_POINT                0xB08F000F      // bad value of EC point
#define E_ECA_BAD_VALUE                0xB08F0010      // bad value of EC domain parameter
#define E_ECA_ECDP_DIFFER              0xB08F0011      // EC domain parameters differ
#define E_ECA_BAD_DOMAIN_PARA          0xB08F0012      // invalid domain parameter
#define E_ECA_BAD_POLYNOM              0xB08F0013      // invalid irreducible polynomial
//#define E_ECA_NO_FIPS_CURVE            0xB08F0014      // curve not available in FIPS mode
//#define E_ECA_NO_FIPS_FUNCTION         0xB08F0015      // function not available in FIPS mode
#define E_ECA_NO_SECURE_CURVE          0xB08F0016      // Curve not secure for CC standards
#define E_ECA_BL_TBL                   0xB08F0017      // table of precalculated values empty/inconsistent
#define E_ECA_DIV0                     0xB08F0018      // division by zero       
#define E_ECA_NO_INVERSE               0xB08F0019      // inverse doesn't exist

#define E_ECA_ARG_LEN                  0xB08F0101      // bad argument length
#define E_ECA_INT                      0xB08F0102      // internal error
#define E_ECA_OBSOLETE                 0xB08F0103      // function obsolete

/* --- END ERROR CODES --- */



#endif /* __ECA_H_PUB_INCLUDED__ */

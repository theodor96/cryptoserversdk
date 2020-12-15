/*****************************************************************************
 *
 *  $File Identification                    $
 *  $Filename          : lna.h              $
 *  $Module version    : x.x.x.x            $
 *  $Module name       : LNA                $
 *  $Release Date      : DD.MM.YYYY         $
 *
 *  Author(s)   : Rainer Herbertz
 *                Utimaco AG
 *
 *  Description : Global header file of CS2000 module LNA
 *                Must be included in every CS2000 software that uses
 *                functions of this module
 *
 *  History     :
 *  Date       |                 Action                          |  Author
 *  -----------|-------------------------------------------------|---------
 *  18.12.2001 | Creation                                        |  R.H.
 *****************************************************************************/


#ifndef __LNA_H_PUB_INCLUDED__
  #define __LNA_H_PUB_INCLUDED__

#include "os_mdl.h"
#include "stype.h"


/* module identification: */

#define LNA_MDL_ID           0x8E            /* ID of the module           */
#define LNA_MDL_NAME         "LNA"           /* Short name of the module   */

#ifdef CS2_SDK
    #define LNA_MDL_NAMEX       "Long Number Arithmetic (SDK)"  /* Long name of the module    */
#else
    #ifdef DEBUG
    #define LNA_MDL_NAMEX       "Long Number Arithmetic (DEBUG)"
    #else
    #define LNA_MDL_NAMEX       "Long Number Arithmetic"
    #endif
#endif
#define LNA_MDL_VERSION      0x01020407       /* Version of the module      */


/* data types: */

typedef unsigned int       lword;

#define LNA_LEN(b)     (((b)+sizeof(lword)-1) / sizeof(lword))



/* public interface: */

typedef struct
{
    void   *p_data;
    int    (*p_start)();
    int    (*p_stop)(void);
    int    (*p_pre_replace)(void);
    int    (*p_pre_delete)(void);
    void   *p_dumy;
    const void   *p_module_info;

    unsigned int (*p_wlen)(unsigned int lw,lword *w);
    void   (*p_btow)(unsigned int lb,unsigned char *b,lword *w);
    void   (*p_wtob)(unsigned int lw,lword *w,unsigned int lb,unsigned char *b);
    int    (*p_cmp_eq)(unsigned int,lword *,unsigned int,lword *);
    int    (*p_cmp)(unsigned int,lword *,unsigned int,lword *);
    int    (*p_add)(unsigned int,lword *,unsigned int,lword *,unsigned int *,lword *);
    int    (*p_inc)(unsigned int,lword *);
    int    (*p_sub)(unsigned int,lword *,unsigned int,lword *,lword *);
    int    (*p_dec)(unsigned int la,lword *);
    int    (*p_mul)(unsigned int,lword *,unsigned int,lword *,lword *);
    int    (*p_sqr)(unsigned int,lword *,lword *);
    int    (*p_mod)(unsigned int,lword *,unsigned int *,lword *);
    int    (*p_mod_s)(unsigned int,lword *,unsigned int *,lword *);
    int    (*p_div)(unsigned int la,lword *,unsigned int,lword *,unsigned int *,lword *,
                    unsigned int *,lword *);
    void   (*p_shr)(unsigned int,unsigned int,lword *);
    void   (*p_shl)(unsigned int,unsigned int,lword *);
    void   (*p_shl_cpy)(unsigned int,unsigned int,lword *,lword *);
    unsigned int (*p_norm)(unsigned int,lword *);
    int    (*p_exp)(unsigned int,lword *,unsigned int,unsigned int,unsigned char *,
                    unsigned int,lword *,lword *);
    int    (*p_euclid)(unsigned int,lword *,unsigned int,lword *,lword *);
    int    (*p_gcd)(unsigned int,lword *,unsigned int,lword *,unsigned int *,lword *);
    unsigned int (*p_bitlen)(unsigned int lw,lword *w);
    int    (*p_mod_1)(lword,unsigned int,lword *,lword *);
    int    (*p_exp2)(unsigned int,lword *,unsigned int,unsigned int,lword *,
                     unsigned int,lword *,lword *);
    int    (*p_prime_test_mr)(unsigned int,lword *,unsigned int,unsigned int,int *);
    int    (*p_gen_prob_prime)(unsigned int,unsigned int,unsigned int,lword,
                               int (*rnd)(unsigned char *,unsigned int),lword *);
    unsigned short const *p_prime_tab;
    int    (*p_gen_prov_prime)(unsigned int,unsigned int,
                               int (*rnd)(unsigned char *,unsigned int),lword *);
    int    (*p_exp_mg)(unsigned int,lword *,unsigned int,unsigned char *,
                       unsigned int,lword *,lword *);
    int    (*p_exp2_mg)(unsigned int,lword *,unsigned int,lword *,
                        unsigned int,lword *,lword *);
    int    (*p_prime_test_lucas)(unsigned int,lword *,int *);
    int    (*p_gen_ansi_prime)(unsigned int,unsigned int,
                               int (*rnd)(unsigned char *,unsigned int),lword *);

    int    (*p_gen_ansi_prime_ex)(unsigned int,unsigned int,
                                  int (*rnd)(unsigned char *,unsigned int),
                                  unsigned int,lword *,
                                  lword *);
    int    (*p_gen_prob_prime_aux_prob)(unsigned int,unsigned int,
                                  int (*rnd)(unsigned char *,unsigned int),
                                  unsigned int,lword *,unsigned int,unsigned int,
                                  lword *);
    int    (*p_mod_exp_mg)(unsigned int,unsigned int,lword *,unsigned int,unsigned char *,
                           unsigned int,lword *,lword *);
    int    (*p_mod_exp2_mg)(unsigned int,unsigned int,lword *,unsigned int,lword *,
                            unsigned int,lword *,lword *);
} T_LNA_TABLE_PUB;



#ifdef _LNA_C_INT_

/* function prototypes used by the module (internal) */

int  lna_start(T_OS_MDL_HDL,void *,void *);
int  lna_stop(void);
int  lna_pre_replace(void);
int  lna_pre_delete(void);

unsigned int lna_wlen(unsigned int lw,lword *w);
unsigned int lna_bitlen(unsigned int lw,lword *w);
void lna_btow(unsigned int lb,unsigned char *b,lword *w);
void lna_wtob(unsigned int lw,lword *w,unsigned int lb,unsigned char *b);

int lna_cmp_eq(
    unsigned int   la,          // (I)    length of first operand
    lword          *a,          // (I)    first operand
    unsigned int   lb,          // (I)    length of second operand
    lword          *b           // (I)    second operand
    );

int lna_cmp(
    unsigned int   la,          // (I)    length of first operand
    lword          *a,          // (I)    first operand
    unsigned int   lb,          // (I)    length of second operand
    lword          *b           // (I)    second operand
    );

int lna_add(
    unsigned int   la,          // (I)    length of first operand
    lword          *a,          // (I)    first operand
    unsigned int   lb,          // (I)    length of second operand
    lword          *b,          // (I)    second operand
    unsigned int   *lr,         // (I/O)  length of result
    lword          *r           // (O)    result
    );

int lna_inc(
    unsigned int   la,          // (I)    length of operand
    lword          *a           // (I/O)  operand
    );

int lna_sub(
    unsigned int   la,          // (I)    length of first operand
    lword          *a,          // (I)    first operand
    unsigned int   lb,          // (I)    length of second operand
    lword          *b,          // (I)    second operand
    lword          *r           // (O)    result
    );

int lna_dec(
    unsigned int   la,          // (I)    length of operand
    lword          *a           // (I/O)  operand
    );

int lna_mul(
    unsigned int   la,          // (I)    length of first operand
    lword          *a,          // (I)    first operand
    unsigned int   lb,          // (I)    length of second operand
    lword          *b,          // (I)    second operand
    lword          *r           // (O)    result (length is la+lb)
    );

int lna_sqr(
    unsigned int   la,          // (I)    length of first operand
    lword          *a,          // (I)    first operand
    lword          *r           // (O)    result (length is 2*la)
    );

int lna_mod(
    unsigned int   ln,          // (I)    length of modulus (divisor)
    lword          *n,          // (I)    modulus (divisor)
    unsigned int   *p_la,       // (I/O)  length of dividend / remainder
    lword          *a           // (I/O)  divident / remainder
    );

int lna_mod_s(
    unsigned int   ln,          // (I)    length of modulus (divisor)
    lword          *n,          // (I)    modulus (divisor)
    unsigned int   *p_la,       // (I/O)  length of dividend / remainder
    lword          *a           // (I/O)  divident / remainder
    );

int lna_mod_1(
    lword          n,           // (I)  modulus (divisor)
    unsigned int   la,          // (I)  length of dividend / remainder
    lword          *a,          // (I)  divident
    lword          *r           // (O)  remainder
    );

int lna_div(
    unsigned int   la,          // (I)    length of dividend
    lword          *a,          // (I)    divident
    unsigned int   ln,          // (I)    length of modulus (divisor)
    lword          *n,          // (I)    modulus (divisor)
    unsigned int   *p_l_q,      // (I/O)  length of quotient
    lword          *q,          // (O)    quotient
    unsigned int   *p_l_r,      // (I/O)  length of remainder
    lword          *r           // (O)    remainder
    );

void lna_shr(
    unsigned int   ct,          // (I)    bit count
    unsigned int   la,          // (I)    length of operand
    lword          *a           // (I/O)  operand
    );

void lna_shl(
    unsigned int   ct,          // (I)    bit count
    unsigned int   la,          // (I)    length of operand
    lword          *a           // (I/O)  operand
    );

void lna_shl_cpy(
    unsigned int   ct,          // (I)    bit count
    unsigned int   ls,          // (I)    length of operand
    lword          *s,          // (I)    source
    lword          *d           // (O)    destination (length: ls + 1)
    );

unsigned int lna_norm(
    unsigned int   la,          // (I)    length of operand
    lword          *a           // (I/O)  operand
    );

int lna_exp(
    unsigned int   ln,          // (I)    length of modulus
    lword          *n,          // (I/O)  modulus / normalized modulus
    unsigned int   s,           // (I)    normalization count of modulus
    unsigned int   le,          // (I)    length of exponent in bytes
    unsigned char  *e,          // (I)    exponent
    unsigned int   la,          // (I)    length of data
    lword          *a,          // (I)    data
    lword          *r           // (O)    result (length is ln)
    );

int lna_exp2(
    unsigned int   ln,          // (I)    length of modulus
    lword          *n,          // (I)    modulus
    unsigned int   s,           // (I)    normalization count of modulus
    unsigned int   le,          // (I)    length of exponent
    lword          *e,          // (I)    exponent
    unsigned int   la,          // (I)    length of data
    lword          *a,          // (I)    data
    lword          *r           // (O)    result (length is ln)
    );

int lna_euclid(
    unsigned int   ln,          // (I)    length of modulus
    lword          *n,          // (I)    modulus
    unsigned int   ld,          // (I)    length of data
    lword          *d,          // (I)    data
    lword          *c           // (O)    result (length is ln)
    );

int lna_gcd(
    unsigned int   la,          // (I)    length of first number
    lword          *a,          // (I)    first number
    unsigned int   lb,          // (I)    length of second number
    lword          *b,          // (I)    second number
    unsigned int   *lr,         // (I/O)  length of result
    lword          *r           // (O)    result
    );

int lna_prime_test_mr(
    unsigned int   ln,                              // (I)    length of number in words
    lword          *num,                            // (I)    number to be tested
    unsigned int   td_ct,                           // (I)    trial division count
    unsigned int   base_ct,                         // (I)    number of bases (rounds)
    int            *fail                            // (O)    != 0, if num is a composite integer
    );                                              //        0, if num may be a prime

int lna_gen_prob_prime(
    unsigned int   len,                             // (I)    length of prime in bits
    unsigned int   td_ct,                           // (I)    trial divison counter
    unsigned int   base_ct,                         // (I)    # of bases for MR-test
    lword          mask,                            // (I)    mask for high order bits
    int            (*rnd)(unsigned char *,unsigned int),     // (I)    random function
    lword          *p                               // (O)    prime
    );

int lna_gen_prov_prime(
    unsigned int   len,                             // (I)    length of prime in bits
    unsigned int   hbits,                           // (I)    number of high bits set
    int            (*rnd)(unsigned char *,unsigned int),     // (I)    random function
    lword          *p                               // (O)    prime
    );

int lna_exp_mg(
    unsigned int   ln,          // (I)    length of modulus
    lword          *n,          // (I)    modulus
    unsigned int   le,          // (I)    length of exponent in bytes
    unsigned char  *e,          // (I)    exponent
    unsigned int   la,          // (I)    length of data
    lword          *a,          // (I)    data
    lword          *r           // (O)    result (length is ln)
    );

int lna_exp2_mg(
    unsigned int   ln,          // (I)    length of modulus
    lword          *n,          // (I)    modulus
    unsigned int   le,          // (I)    length of exponent in bytes
    lword          *e,          // (I)    exponent
    unsigned int   la,          // (I)    length of data
    lword          *a,          // (I)    data
    lword          *r           // (O)    result (length is ln)
    );

int lna_prime_test_lucas(
    unsigned int   ln,                              // (I)    length of number in bytes
    lword          *num,                            // (I)    number to be tested
    int            *fail                            // (O)    != 0, if num is a composite integer
    );                                              //        0, if num may be a prime

int lna_gen_ansi_prime(
    unsigned int   len,                             // (I)    length of prime in bits
    unsigned int   td_ct,                           // (I)    trial divison counter
    int            (*rnd)(unsigned char *,unsigned int),     // (I)    random function
    lword          *p                               // (O)    prime
    );

int lna_gen_ansi_prime_ex(
    unsigned int   len,                             // (I)    length of prime in bits
    unsigned int   td_ct,                           // (I)    trial divison counter
    int            (*rnd)(unsigned char *,unsigned int),     // (I)    random function
    unsigned       l_e,                             // (I)    length of e
    lword          *e,                              // (I)    p will be relative prime to e
    lword          *p                               // (O)    prime
    );

int lna_gen_prob_prime_aux_prob(
    unsigned int   len,                             // (I)    length of prime in bits
    unsigned int   td_ct,                           // (I)    trial divison counter
    int            (*rnd)(unsigned char *,unsigned int),     // (I)    random function
    unsigned       l_e,                             // (I)    length of e
    lword          *e,                              // (I)    p will be relative prime to e
    unsigned int   p1_bits,                         // (I)    length of Xp1 in bits
    unsigned int   p2_bits,                         // (I)    length of Xp2 in bits
    lword          *p                               // (O)    prime
    );

int lna_mod_exp_mg(
    unsigned int   hce_use,         // (I)    use HCE functions ( optional/refused )
    unsigned int   ln,          // (I)    length of modulus
    lword          *n,          // (I)    modulus
    unsigned int   le,          // (I)    length of exponent in bytes
    unsigned char  *e,          // (I)    exponent
    unsigned int   la,          // (I)    length of data
    lword          *a,          // (I)    data
    lword          *r           // (O)    result (length is ln)
    );

int lna_mod_exp2_mg(
    unsigned int   hce_use,     // (I)    use HCE functions ( optional/refused )
    unsigned int   ln,          // (I)    length of modulus
    lword          *n,          // (I)    modulus
    unsigned int   le,          // (I)    length of exponent in bytes
    lword          *e,          // (I)    exponent
    unsigned int   la,          // (I)    length of data
    lword          *a,          // (I)    data
    lword          *r           // (O)    result (length is ln)
    );

extern MDL_CONST unsigned short lna_prime_tab[];

#else

/* external interface to be used by other modules */

extern MDL_GLOBAL T_OS_MDL_HDL P_LNA;

#define _P_LNA ((T_LNA_TABLE_PUB *)P_LNA)         /* shortcut */

#define P_lna_data         (_P_LNA->_p_data);

#define lna_start          _P_LNA->p_start
#define lna_stop           _P_LNA->p_stop
#define lna_pre_replace    _P_LNA->p_pre_replace
#define lna_pre_delete     _P_LNA->p_pre_delete

#define lna_wlen           _P_LNA->p_wlen
#define lna_bitlen         _P_LNA->p_bitlen
#define lna_btow           _P_LNA->p_btow
#define lna_wtob           _P_LNA->p_wtob
#define lna_cmp_eq         _P_LNA->p_cmp_eq
#define lna_cmp            _P_LNA->p_cmp
#define lna_add            _P_LNA->p_add
#define lna_inc            _P_LNA->p_inc
#define lna_sub            _P_LNA->p_sub
#define lna_dec            _P_LNA->p_dec
#define lna_mul            _P_LNA->p_mul
#define lna_sqr            _P_LNA->p_sqr
#define lna_mod            _P_LNA->p_mod
#define lna_mod_s          _P_LNA->p_mod_s
#define lna_mod_1          _P_LNA->p_mod_1
#define lna_div            _P_LNA->p_div
#define lna_shr            _P_LNA->p_shr
#define lna_shl            _P_LNA->p_shl
#define lna_shl_cpy        _P_LNA->p_shl_cpy
#define lna_norm           _P_LNA->p_norm
#define lna_exp            _P_LNA->p_exp
#define lna_exp2           _P_LNA->p_exp2
#define lna_euclid         _P_LNA->p_euclid
#define lna_gcd            _P_LNA->p_gcd
#define lna_prime_test_mr  _P_LNA->p_prime_test_mr
#define lna_gen_prob_prime _P_LNA->p_gen_prob_prime
#define lna_gen_prov_prime _P_LNA->p_gen_prov_prime
#define lna_prime_tab      _P_LNA->p_prime_tab
#define lna_exp_mg         _P_LNA->p_exp_mg
#define lna_exp2_mg        _P_LNA->p_exp2_mg
#define lna_prime_test_lucas _P_LNA->p_prime_test_lucas
#define lna_gen_ansi_prime _P_LNA->p_gen_ansi_prime
#define lna_gen_ansi_prime_ex _P_LNA->p_gen_ansi_prime_ex
#define lna_gen_prob_prime_aux_prob _P_LNA->p_gen_prob_prime_aux_prob
#define lna_mod_exp_mg     _P_LNA->p_mod_exp_mg
#define lna_mod_exp2_mg    _P_LNA->p_mod_exp2_mg


#endif /* _LNA_C_INT_ */


static INLINE void lna_cpy(lword *d,lword *s,unsigned int len)
{
    while(len-- > 0) *d++ = *s++;
}

static INLINE void lna_even(unsigned int len,lword *x)
{
    (void)len;
    *x &= ~1;
}


static INLINE void lna_odd(unsigned int len,lword *x)
{
    (void)len;
    *x |= 1;
}


#define LNA_LUCAS_TEST      0x10000

/* --- defines for HCE use in montgomeries modular exponentiation                                 */
#define LNA_OPT_HCE         0x00                 /* optional use of HCE allowed                   */
#define LNA_NO_HCE          0x01                 /* use of HCE not allowed                        */

/* Error Codes:  (0xB0000000 | (LNA_MDL_ID << 16) | (errno))  */

/* --- BEGIN ERROR CODES --- */

#define E_LNA                          0xB08E          // CryptoServer module LNA
#define E_LNA_OVL                      0xB08E0001      // result overflow
#define E_LNA_NEG                      0xB08E0002      // result negativ
#define E_LNA_MOD_LEN                  0xB08E0003      // modulus too short
#define E_LNA_DATA_LEN                 0xB08E0004      // data greater than modulus
#define E_LNA_MEM                      0xB08E0005      // can't alloc memory
#define E_LNA_EXP0                     0xB08E0006      // exponent is 0
#define E_LNA_DIV0                     0xB08E0007      // division by zero
#define E_LNA_NUM_LEN                  0xB08E0008      // number too short
#define E_LNA_PARAM                    0xB08E0009      // bad parameter
#define E_LNA_NOT_FOUND                0xB08E000A      // no prime found
#define E_LNA_MOD_EVEN                 0xB08E000B      // modulus is even

#define E_LNA_RESOVL                   0xB08E0100      // result overflow
#define E_LNA_ARG_LEN                  0xB08E0101      // bad argument length
#define E_LNA_INT                      0xB08E0102      // internal error while generating prime

/* --- END ERROR CODES --- */



#endif /* __LNA_H_PUB_INCLUDED__ */

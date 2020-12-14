/*****************************************************************************
 *
 *  $File Identification                    $
 *  $Filename          : cmds.h             $
 *  $Module version    : x.x.x.x            $
 *  $Module name       : CMDS               $
 *  $Release Date      : DD.MM.YYYY         $
 *
 *  Author(s)   : Dipl. Inf. Rainer Herbertz
 *                Utimaco AG
 *
 *  Description : Global header file of CryptoServer module CMDS
 *
 *  History     :
 *  Date       |                 Action                          |  Author
 *  -----------|-------------------------------------------------|---------
 *  14.05.2001 | Creation                                        |  R.H.
 *  02.09.2002 | vprint added                                    |  T.L.
 *  02.04.2003 | new functions cmds_add/list/del/change_user()   |  R.H.
 *  18.12.2003 | new functions cmds_login/logoff_user()          |  R.H.
 *  19.04.2003 | new function cmds_critical_error()              |  R.H.
 *  20.04.2004 | new Get_session key modes                       |  R.H.
 *  16.02.2007 | new functions: cmds_add_user_ex(),              |  R.H.
 *             |      cmds_get_user_info(), cmds_gen_sessionkey()|  R.H.
 *  27.03.2007 | new auth mechanisms HMAC_PWD + ECDSA            |  R.H.
 *             | new sessionkey mechanism ECDH                   |  R.H.
 *****************************************************************************/


#ifndef __CMDS_H_PUB_INCLUDED__
#define __CMDS_H_PUB_INCLUDED__

#include <os_mdl.h>
#include <os_cfg.h>
#include <stdarg.h>


/* module identification: */

#define CMDS_MDL_ID          0x83                          /* ID of the module          */
#define CMDS_MDL_NAME        "CMDS"                        /* Short name of the module  */
#ifdef CS2_SDK
  #define CMDS_MDL_NAMEX       "Command Scheduler (SDK)"
#else
  #ifdef DEBUG
    #define CMDS_MDL_NAMEX       "Command Scheduler (DEBUG)"
  #else
    #define CMDS_MDL_NAMEX       "Command Scheduler"
  #endif
#endif
#define CMDS_MDL_VERSION     0x03060402                    /* Version of the module     */

/* types: */


typedef unsigned int   T_CMDS_PERM;            /* authentication state      */

#define check_permission(handle,group,value)    ((((handle)->perm >> ((group) << 2)) & 0x0f) < (value))


#ifdef _CMDS_C_INT_

typedef struct t_mem_blk T_CMDS_HANDLE;        /* definition for internal use             */

#else

typedef struct t_mem_blk                       /* definition for the outside world        */
{
    T_CMDS_PERM      perm;                     /* authentication state of command         */
    int              dumy[1];
} T_CMDS_HANDLE;

#endif


// definition for function tables:

typedef int        T_CMDS_FCT(T_CMDS_HANDLE *,int,unsigned char *);
typedef T_CMDS_FCT *P_CMDS_FCT;


// definition for cmds_list_user():

typedef struct
{
    unsigned char name[8];      // name of user
    T_CMDS_PERM   perm;         // permission mask
    unsigned char mech;         // auth. mechanism
    unsigned char flags;        // user flags
    unsigned char att;          // attributes present
} T_CMDS_USER;


// user flags:

#define CMDS_UFLG_LOGIN     1     // allow static login
#define CMDS_UFLG_SM        2     // allow secure messaging, even without authentication
#define CMDS_UFLG_SM_AUTH   4     // allow secure messaging only with authentication
#define CMDS_UFLG_TMP       0x80  // temporary user


// AUTH mechanisms

#define CMDS_MECH_RSA_SIGN   0                // signature authentication
#define CMDS_MECH_CLR_PWD    1                // clear password authentication
#define CMDS_MECH_SHA1_PWD   2                // SHA-1 hashed password authentication
#define CMDS_MECH_RSA_SC     3                // smartcard signature authentication
#define CMDS_MECH_HMAC_PWD   4                // HMAC password authentication
#define CMDS_MECH_ECDSA      5                // ECDSA authentication


// Session key mechanisms

#define CMDS_MECH_SM_AES        2
#define CMDS_MECH_SM_AES_CMAC   3


// Get session key modes

#define CMDS_MODE_SM_DH         3
#define CMDS_MODE_SM_ECDH       5
#define CMDS_MODE_SM_DH_MA_RSA  6

#define CMDS_MODE_SM_FAST       0x80


// definition for cmds_get_auth_state():

typedef struct
{
    T_CMDS_PERM     perm;       // permission mask
    unsigned short  name_count;
    unsigned short  name_len;
    unsigned char   names[1];
} T_CMDS_AUTH_STATE;


// definition for cmds_check_auth_state():

typedef struct
{
    unsigned char   name[8];
    T_CMDS_PERM     perm;
} T_CMDS_AUTH_LIST;



/* public interface: */

typedef struct
{
    void   *p_data;
    int    (*p_start)(T_OS_MDL_HDL, void *, void*);
    int    (*p_stop)(void);
    int    (*p_pre_replace)(void);
    int    (*p_pre_delete)(void);
    void   *p_dumy;
    const void *p_module_info;

    void   (*p_print)(unsigned char *,...);
    void   (*p_xprint)(char *,void *,int);
    int    (*p_register)(int,int,const P_CMDS_FCT []);
    int    (*p_unregister)(int);
    int    (*p_alloc_answ)(T_CMDS_HANDLE *,int,unsigned char **);
    int    (*p_scanf)(int,unsigned char *,char *,int,void *);
    int    (*p_register_ppapp)(int,int,char *,unsigned int,unsigned char *);
    int    (*p_unregister_ppapp)(int,int);
    void   (*p_vprint)(unsigned char *,va_list);
    int    (*p_get_user_token)(unsigned char *,unsigned char **);
    int    (*p_add_user)(unsigned char *,T_CMDS_PERM,unsigned char,
                         unsigned char,unsigned int,unsigned char *);
    int    (*p_del_user)(unsigned char *);
    int    (*p_change_user)(unsigned char *,unsigned int,unsigned char *);
    int    (*p_list_user)(unsigned int *,T_CMDS_USER **);
    int    (*p_alloc_eansw)(T_CMDS_HANDLE *,int,unsigned char **);
    int    (*p_logoff_user)(unsigned char *,T_CMDS_PERM);
    int    (*p_login_user)(unsigned char *,T_CMDS_PERM);
    int    (*p_critical_error)(int);
    int    (*p_get_auth_state)(T_CMDS_HANDLE *p_hdl,T_CMDS_AUTH_STATE **pp_state);
    int    (*p_add_user_ex)(unsigned int,unsigned char *,T_CMDS_PERM,unsigned char,unsigned char,
                            unsigned int,unsigned char *,unsigned int,unsigned char *,unsigned char *);
    int    (*p_get_user_info)(unsigned int,unsigned char *,unsigned char,unsigned int *,unsigned char *);
    int    (*p_gen_sessionkey)(unsigned int,unsigned int,unsigned int,unsigned char *,unsigned char *,
                               unsigned char *,unsigned char *,unsigned int *,unsigned char *);
    int    (*p_match_user_att)(unsigned char *,unsigned char,unsigned int,
                               unsigned char *p_prop[],T_CMDS_PERM *);
    int    (*p_check_auth_state)(T_CMDS_HANDLE *,unsigned char,unsigned int,
                                 unsigned char *p_prop[],unsigned int *,
                                 T_CMDS_AUTH_LIST *,T_CMDS_PERM *);
    int    (*p_backup_user)(unsigned char *p_name,unsigned int *p_l_len,unsigned char **pp_bckup);
    int    (*p_restore_user)(unsigned int l_bckup,unsigned char *p_bckup);
    int    (*p_get_sessionkey)(T_CMDS_HANDLE *,unsigned char *,unsigned int *,unsigned char *key);
    int    (*p_audit_write)(unsigned int  mclass,T_CMDS_HANDLE *p_hdl,unsigned char *p_str,...);
    int    (*p_erase)(void);
    int    (*p_set_max_auth_fails)(unsigned char);
    int    (*p_get_max_auth_fails)(void);
    int    (*p_set_admin_mode)(char mode);
    int    (*p_set_startup_mode)(char mode);
    int    (*p_get_startup_mode)(void);

    int    (*p_get_fc)(T_CMDS_HANDLE *, int *, int *);
    int    (*p_gen_sessionkey_ex)(unsigned int,unsigned int,unsigned int,unsigned char *,unsigned int,unsigned char *,
                               unsigned char *,unsigned char *,unsigned int *,unsigned char *,unsigned char *);
    int    (*p_cmds_signed_cfg_open)(const char* basename, const int name_len, OS_CFG_HANDLE *p_hdl);
} T_CMDS_TABLE_PUB;


#ifdef _CMDS_C_INT_


/* function prototypes used by the module (internal) */

int  cmds_start(T_OS_MDL_HDL,void *,void *);
int  cmds_stop(void);
int  cmds_pre_replace(void);
int  cmds_pre_delete(void);

void cmds_vprint(unsigned char *,va_list);
void cmds_print(unsigned char *,...);
void cmds_xprint(char *,void *,int);
int  cmds_audit_write(unsigned int  mclass,T_CMDS_HANDLE *p_hdl,unsigned char *p_str,...);
int  cmds_auth_audit_write(unsigned int  mclass,T_CMDS_HANDLE *p_hdl,unsigned char *p_str,...);

int  cmds_register(int,int,const P_CMDS_FCT[]);
int  cmds_unregister(int);
int  cmds_alloc_answ(T_CMDS_HANDLE *,int,unsigned char **);
int  cmds_scanf(int,unsigned char *,char *,int,void *);
int  cmds_register_ppapp(int,int,char *,unsigned int,unsigned char *);
int  cmds_unregister_ppapp(int,int);
int  cmds_get_user_token(unsigned char *,unsigned char **);
int  cmds_alloc_eansw(T_CMDS_HANDLE *,int,unsigned char **);
int  cmds_critical_error(int);

int cmds_add_user_ex(
    unsigned int  l_username,       // (I) length of username
    unsigned char *username,        // (I) name of user
    T_CMDS_PERM   perm,             // (I) permission mask
    unsigned char mech,             // (I) auth. mechanism
    unsigned char uflags,           // (I) user flags
    unsigned int  l_token,          // (I) length of user token
    unsigned char *p_token,         // (I) user token
    unsigned int  l_att,            // (I) length of user attributes
    unsigned char *p_att,           // (I) user attributes
    unsigned char *p_name           // (O) short username
    );

int cmds_get_user_info(
    unsigned int  l_name,       // (I)   length of name
    unsigned char *p_name,      // (I)   name of user (short or long name)
    unsigned char type,         // (I)   type of requested information
    unsigned int  *p_l_val,     // (I/O) buffer size / length of value returned
    unsigned char *p_val        // (O)   value returned
    );

int cmds_del_user(unsigned char *username);
int cmds_change_user(unsigned char *username,unsigned int l_token,unsigned char *p_token);
int cmds_list_user(unsigned int *p_nuser,T_CMDS_USER **pp_user);
int cmds_logoff_user(unsigned char *,T_CMDS_PERM);
int cmds_login_user(unsigned char *,T_CMDS_PERM);
int cmds_get_auth_state(T_CMDS_HANDLE *p_hdl,T_CMDS_AUTH_STATE **pp_state);


int cmds_gen_sessionkey(
    unsigned int     mode,      // (I)   session key mode
    unsigned int     mech,      // (I)   session key mechanism
    unsigned int     l_param,   // (I)   length of parameter
    unsigned char    *p_param,  // (I)   parameter (e.g. user name or DH parameter)
    unsigned char    *p_mode,   // (O)   session key mode
    unsigned char    *p_seq_ct, // (O)   sequence counter (16 bytes)
    unsigned char    *p_skey,   // (O)   sessionkey (clear)
    unsigned int     *p_l_ekey, // (I/O) sizeof buffer / size of encrypted key
    unsigned char    *p_ekey    // (O)   encrypted key
    );

int cmds_gen_sessionkey_ex(
    unsigned int     mode,        // (I)   session key mode
    unsigned int     mech,        // (I)   session key mechanism
    unsigned int     l_param,     // (I)   length of parameter
    unsigned char    *p_param,    // (I)   parameter (e.g. user name or DH parameter)
    unsigned int     session_id,  // (I)   ID of current session
    unsigned char    *p_mode,     // (O)   session key mode
    unsigned char    *p_seq_ct,   // (O)   sequence counter (16 bytes)
    unsigned char    *p_skey,     // (O)   session key for encryption (clear)
    unsigned int     *p_l_ekey,   // (I/O) sizeof buffer / size of encrypted key
    unsigned char    *p_ekey,     // (O)   encrypted key
    unsigned char    *p_mkey      // (0)   session key for MAC (clear)
    );

int cmds_match_user_att(
    unsigned char *p_name,      // (I)   name of user (8 byte)
    unsigned char type,         // (I)   type of attribute
    unsigned int  def_flags,    // (I)   bit vector of default flags
    unsigned char *p_prop[],    // (I)   property list
    T_CMDS_PERM   *p_perm       // (O)   permission
    );

int cmds_check_auth_state(
    T_CMDS_HANDLE       *p_hdl,       // (I)   handle to current command
    unsigned char       type,         // (I)   type of attribute
    unsigned int        def_flags,    // (I)   bit vector of default flags
    unsigned char       *p_prop[],    // (I)   property list
    unsigned int        *p_tabsize,   // (I/O) number of entrys, I: buffer size, O: filled size
    T_CMDS_AUTH_LIST    *p_state,     // (O)   table of states
    T_CMDS_PERM         *p_perm       // (O)   overall permission
    );

int cmds_get_sessionkey(
    T_CMDS_HANDLE       *p_hdl,       // (I)   handle to current command
    unsigned char       *type,        // (O)   type of key (CMDS_MECH_SM_...)
    unsigned int        *len,         // (I/O) size of buffer / length of key
    unsigned char       *key          // (O)   session key
    );

int cmds_backup_user(unsigned char *p_name,unsigned int *p_l_len,unsigned char **pp_bckup);
int cmds_restore_user(unsigned int l_bckup,unsigned char *p_bckup);
int cmds_erase(void);
int cmds_set_max_auth_fails(unsigned char max_auth_fails);
int cmds_get_max_auth_fails(void);
int cmds_set_admin_mode(unsigned char mode);
int cmds_set_startup_mode(unsigned char mode);
int cmds_get_startup_mode(void);
int cmds_eval_startup_mode (void);

// DO NOT USE !
int cmds_get_fc(
    T_CMDS_HANDLE       *p_hdl,       // (I)   handle to current command
    int                 *p_fc,        // (O)   a Function Code for this handle
    int                 *p_sfc        // (O)   a Sub-Function Code for this handle
    );

int cmds_signed_cfg_open(const char *basename, const int name_len, OS_CFG_HANDLE *p_hdl);

#else


/* external interface to be used by other modules */

extern MDL_GLOBAL T_OS_MDL_HDL P_CMDS;

#define _P_CMDS  ((T_CMDS_TABLE_PUB *)P_CMDS)         /* shortcut */

#define P_cmds_data             (_P_CMDS->_p_data);

#define cmds_start              _P_CMDS->p_start
#define cmds_stop               _P_CMDS->p_stop
#define cmds_pre_replace        _P_CMDS->p_pre_replace
#define cmds_pre_delete         _P_CMDS->p_pre_delete

#define cmds_vprint             _P_CMDS->p_vprint
#define cmds_print              _P_CMDS->p_print
#define cmds_xprint             _P_CMDS->p_xprint
#define cmds_audit_write        _P_CMDS->p_audit_write

#define cmds_register           _P_CMDS->p_register
#define cmds_unregister         _P_CMDS->p_unregister

#define cmds_alloc_answ         _P_CMDS->p_alloc_answ
#define cmds_scanf              _P_CMDS->p_scanf
#define cmds_alloc_eansw        _P_CMDS->p_alloc_eansw

#define cmds_register_ppapp     _P_CMDS->p_register_ppapp
#define cmds_unregister_ppapp   _P_CMDS->p_unregister_ppapp

#define cmds_get_user_token     _P_CMDS->p_get_user_token

#define cmds_add_user_ex        _P_CMDS->p_add_user_ex
#define cmds_del_user           _P_CMDS->p_del_user
#define cmds_erase              _P_CMDS->p_erase
#define cmds_change_user        _P_CMDS->p_change_user
#define cmds_list_user          _P_CMDS->p_list_user
#define cmds_logoff_user        _P_CMDS->p_logoff_user
#define cmds_login_user         _P_CMDS->p_login_user
#define cmds_get_auth_state     _P_CMDS->p_get_auth_state
#define cmds_check_auth_state   _P_CMDS->p_check_auth_state
#define cmds_get_user_info      _P_CMDS->p_get_user_info
#define cmds_match_user_att     _P_CMDS->p_match_user_att
#define cmds_backup_user        _P_CMDS->p_backup_user
#define cmds_restore_user       _P_CMDS->p_restore_user

#define cmds_gen_sessionkey     _P_CMDS->p_gen_sessionkey
#define cmds_get_sessionkey     _P_CMDS->p_get_sessionkey

#define cmds_critical_error     _P_CMDS->p_critical_error

#define cmds_set_max_auth_fails _P_CMDS->p_set_max_auth_fails
#define cmds_get_max_auth_fails _P_CMDS->p_get_max_auth_fails

#define cmds_set_admin_mode     _P_CMDS->p_set_admin_mode
#define cmds_set_startup_mode   _P_CMDS->p_set_startup_mode
#define cmds_get_startup_mode   _P_CMDS->p_get_startup_mode

#define cmds_get_fc             _P_CMDS->p_get_fc
#define cmds_gen_sessionkey_ex  _P_CMDS->p_gen_sessionkey_ex
#define cmds_signed_cfg_open    _P_CMDS->p_cmds_signed_cfg_open
#endif /* _CMDS_C_INT_ */



/* Error Codes:  (0xB0000000 | (CMDS_MDL_ID << 16) | (errno))  */

/* --- BEGIN ERROR CODES --- */
#define E_CMDS                            0xB083          // CryptoServer module CMDS, Command scheduler

#define E_CMDS_DENIED                     0xB0830001      // permission denied
#define E_CMDS_NO_MEM                     0xB0830002      // can't alloc memory
#define E_CMDS_INVAL                      0xB0830003      // invalid parameter
#define E_CMDS_IN_USE                     0xB0830004      // module id already in use
#define E_CMDS_BAD_FC                     0xB0830005      // bad function code (module ID)
#define E_CMDS_BAD_SFC                    0xB0830006      // function doesn't exist
#define E_CMDS_BAD_NAME                   0xB0830007      // invalid user name
#define E_CMDS_DATA_LEN                   0xB0830008      // illegal length of command block
#define E_CMDS_TASK_ERR                   0xB0830009      // can't create task
#define E_CMDS_BAD_TAG                    0xB083000A      // bad tag of command block
#define E_CMDS_FMT_LEN                    0xB083000B      // bad length within format string (scanf)
#define E_CMDS_BAD_CMD                    0xB083000C      // bad format of command block
#define E_CMDS_BAD_OUT                    0xB083000D      // bad parameter structure (scanf)
#define E_CMDS_BAD_FMT                    0xB083000E      // bad format string (scanf)
#define E_CMDS_USER_EXISTS                0xB083000F      // user already exists
#define E_CMDS_BAD_MECH                   0xB0830010      // invalid mechanism
#define E_CMDS_NO_DB                      0xB0830011      // no DB module present
#define E_CMDS_BAD_AUTH_CMD               0xB0830012      // invalid AUTH layer command
#define E_CMDS_AUTH_FAILED                0xB0830013      // authentication failed
#define E_CMDS_NO_VRSA                    0xB0830014      // no VRSA module present
#define E_CMDS_BAD_PERM                   0xB0830015      // bad permission mask
#define E_CMDS_NO_USER                    0xB0830016      // unknown user
#define E_CMDS_BAD_ATT                    0xB0830017      // bad user attributes
#define E_CMDS_LOGOFF_FAILED              0xB083001B      // logoff failed
#define E_CMDS_USER_ACTIVE                0xB083001C      // logged in user can't be deleted
#define E_CMDS_BAD_TOKEN                  0xB083001D      // bad user token (key or password)
#define E_CMDS_NO_VDES                    0xB083001E      // no VDES module present
#define E_CMDS_NO_UTIL                    0xB083001F      // no UTIL module present
#define E_CMDS_NO_HASH                    0xB0830020      // no HASH module present
#define E_CMDS_SM_FAILED                  0xB0830021      // secure messaging failed
#define E_CMDS_SM_EXPIRED                 0xB0830022      // secure messaging session expired
#define E_CMDS_SM_ID                      0xB0830023      // invalid secure messaging ID
#define E_CMDS_BF_OVL                     0xB0830024      // internal buffer overflow

#define E_CMDS_FIPS_INIT                  0xB0830025      // FIPS140 initialization failed

#define E_CMDS_USER_MODE                  0xB0830026      // mode does not match user
#define E_CMDS_BAD_MODE                   0xB0830027      // invalid mode
#define E_CMDS_BAD_SIZE                   0xB0830028      // illegal answer buffer size
#define E_CMDS_NO_MBK                     0xB0830029      // no MBK module present
#define E_CMDS_INVAL_BCK                  0xB083002A      // invalid backup data
#define E_CMDS_BAD_UDB_ENTRY              0xB083002B      // bad entry in user DB (internal error)
#define E_CMDS_BUFF_SIZE                  0xB083002C      // buffer size too small
#define E_CMDS_NO_MBK_KEY                 0xB083002D      // no MBK key found
#define E_CMDS_MBK_TYPE                   0xB083002E      // MBK type does not match
#define E_CMDS_NO_AES                     0xB083002F      // no AES module present
#define E_CMDS_NO_HMAC                    0xB0830030      // no HMAC algorithm available
#define E_CMDS_NO_ECC                     0xB0830031      // no ECC algorithm available
#define E_CMDS_ALARM                      0xB0830032      // ALARM state
#define E_CMDS_BAD_INITKEY                0xB0830033      // bad file 'init.key'
#define E_CMDS_ADMIN_AMPUTATION           0xB0830034      // One Admin authenticated via keyfile or smartcard must remain
#define E_CMDS_USER_FLAG_NOT_ALLOWED      0xB0830035      // user flag not allowed
#define E_CMDS_SM_PERM_DIFF               0xB0830036      // permissions of users of same session must not differ
#define E_CMDS_NVRAM                      0xB0830037      // error acessing NVRAM
#define E_CMDS_AUTH_FAIL_CNT_EXCEEDED     0xB0830038      // too many unsuccessful authentication tries

#define E_CMDS_PARAM_FIPS                 0xB0830039      // parameter not valid in FIPS mode
#define E_CMDS_DENIED_FIPS                0xB083003A      // authentication mandatory in FIPS mode
#define E_CMDS_BAD_MECH_FIPS              0xB083003B      // mechanism not allowed in FIPS mode
#define E_CMDS_BAD_ATT_FIPS               0xB083003C      // user attributes not allowed in FIPS mode
#define E_CMDS_BAD_USER_FLAG_FIPS         0xB083003D      // user flag not allowed in FIPS mode

#define E_CMDS_MAX_AUTH_USER_REACHED      0xB083003E      // maximum of logged in/authenticated users reached

#define E_CMDS_SM_MISSING_FIPS            0xB083003F      // authentication without secure messaging not allowed in FIPS mode
// #define E_CMDS_LOGIN_FIPS                 0xB0830040      // static login not allowed in FIPS mode
#define E_CMDS_AUTH_FIPS_ESTATE           0xB0830041      // authentication not available in FIPS error state
#define E_CMDS_FIPS_BLOCKED               0xB0830042      // function not available in FIPS mode
// #define E_CMDS_FIPS_ERROR_STATE           0xB0830043      // function not available in FIPS error state
#define E_CMDS_ADMIN_BAD_FUNC             0xB0830044      // function is blocked in Administration Mode

#define E_CMDS_MAX_AUTH_FAIL_READ         0xB0830046      // file for MaxAuthFailures corrupted
#define E_CMDS_ERROR_STATE                0xB0830047      // function not available in error state

#define E_CMDS_LOGIN_CC                   0xB0830050      // static login not allowed in CC mode
#define E_CMDS_AUTH_CC_ESTATE             0xB0830051      // authentication not available in CC error state
#define E_CMDS_CC_BLOCKED                 0xB0830052      // function not available in CC mode
#define E_CMDS_CC_ERROR_STATE             0xB0830053      // function not available in CC error state
#define E_CMDS_CC_INIT                    0xB0830054      // CC-CMS initialization failed
#define E_CMDS_BAD_PERM_CC                0xB0830055      // permissions must not overlap in CC mode
#define E_CMDS_CC_MISSING                 0xB0830056      // cc-cms.msc module missing in flash
#define E_CMDS_BAD_TOKEN_CC               0xB0830057      // RSA token < 1024 bit not allowed in CC mode

#define E_CMDS_PARAM_CC                   0xB0830059      // parameter not valid in CC mode
#define E_CMDS_DENIED_CC                  0xB083005A      // authentication mandatory in CC mode
#define E_CMDS_BAD_MECH_CC                0xB083005B      // mechanism not allowed in CC mode
#define E_CMDS_BAD_ATT_CC                 0xB083005C      // user attributes not allowed in CC mode
#define E_CMDS_BAD_USER_FLAG_CC           0xB083005D      // user flag not allowed in CC mode
#define E_CMDS_SM_MISSING_CC              0xB083005F      // authentication without secure messaging not allowed in CC mode

#define E_CMDS_SM_DH_BAD_PARAM            0xB0830060      // DH parameter from host for sessionkey is weak
#define E_CMDS_SFC_DISABLED               0xB0830061      // This function is not available in this HSM configuration
#define E_CMDS_HASH_VERS                  0xB0830062      // wrong version of HASH module
#define E_CMDS_CHALLENGE_LEN              0xB0830063      // illegal challenge length requested
#define E_CMDS_SM_MA_ALARM                0xB0830064      // Mutual Authentication not available in alarm state
#define E_CMDS_BAD_SM_MODE                0xB0830065      // requested Secure Messaging mode not supported anymore
#define E_CMDS_BAD_AUTH_MECH              0xB0830066      // user's authentication mechanism not supported anymore
#define E_CMDS_STATIC_LOGIN               0xB0830067      // Static Login not supported anymore

#define E_CMDS_CC_SM_MA                   0xB0830070      // Mutual Authentication must be activated in CC mode
#define E_CMDS_CC_HIGH_PERM               0xB0830071      // user permission level must not exceed 3 in CC mode

#define E_CMDS_SM_SESS_CLOSED             0xB0830072      // secure messaging session is closed

#define E_CMDS_CC_MDL_MISSING             0xB0830073      // firmware module required for CC mode is missing
#define E_CMDS_CC_MDL_INIT_FAILED         0xB0830074      // firmware module required for CC mode failed to initialize
#define E_CMDS_CC_MDL_VERSION             0xB0830075      // firmware module has incorrect version for CC mode
/* --- END ERROR CODES --- */


#endif /* __CMDS_H_PUB_INCLUDED__ */

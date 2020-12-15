/**************************************************************************************************
 *
 * $File Identification                    $
 * $Filename          : adm.h              $
 * $Module version    : x.x.x.x            $
 * $Module name       : ADM                $
 * $Release Date      : DD.MM.YYYY         $
 *
 * Description        : Global header file of CryptoServer module ADM (Administration Module).
 *
 *
 **************************************************************************************************/
#ifndef __ADM_H_PUB_INCLUDED__
#define __ADM_H_PUB_INCLUDED__

#include "os_mdl.h"
#include "cmds.h"


//-----------------------------------------------------------------------------
// module identification:
//-----------------------------------------------------------------------------
//#define ADM_MDL_ID          0x87                            // ID of the module //see adm_sfc.h
#define ADM_MDL_NAME        "ADM"                           // Abbreviation of the module
#ifdef CS2_SDK
  #define ADM_MDL_NAMEX     "Administration Module SDK"     // Long name of the module
#else
  #ifdef DEBUG
    #define ADM_MDL_NAMEX   "Administration Module DEBUG"   // Long name of the module
  #else
    #define ADM_MDL_NAMEX   "Administration Module"         // Long name of the module
  #endif
#endif
#define ADM_MDL_VERSION     0x03001B02                      // Version of the module


//-----------------------------------------------------------------------------
// public interface:
//-----------------------------------------------------------------------------
typedef struct
{
  void   *p_data;
  int    (*p_start)(T_OS_MDL_HDL, void *, void*);
  int    (*p_stop)(void);
  int    (*p_pre_replace)(void);
  int    (*p_pre_delete)(void);
  void   *dumy;
  const void *p_module_info;

  int    (*p_set_time)(unsigned int sec, unsigned int msec);
  int    (*p_mdl_decrypt_all)(void);
  int    (*p_file_load_chunked)(T_CMDS_HANDLE* p_hdl, unsigned int single_chunk, unsigned int part, unsigned char *p_path, unsigned int  l_data, unsigned char *p_data);
  int    (*p_sig_verify)(unsigned int  key_type, unsigned int  hash_algo, unsigned char *p_data, unsigned int  l_data, unsigned char *p_sig, unsigned int  l_sig);
}
T_ADM_TABLE_PUB;


#ifdef _ADM_C_INT_

  int  adm_start(T_OS_MDL_HDL,void *,void *);
  int  adm_stop(void);
  int  adm_pre_replace(void);
  int  adm_pre_delete(void);

  int  adm_mdl_decrypt_all(void);
  int  adm_file_load_chunked(T_CMDS_HANDLE* p_hdl, unsigned int single_chunk, unsigned int part, unsigned char *p_path, unsigned int  l_data, unsigned char *p_data);
  
  /* do not use adm_sig_verify */
  int  adm_sig_verify(unsigned int  key_type, unsigned int  hash_algo, unsigned char *p_data, unsigned int  l_data, unsigned char *p_sig, unsigned int  l_sig);

#else
  //-----------------------------------------------------------------------------
  // external interface to be used by other modules
  //-----------------------------------------------------------------------------
  extern MDL_GLOBAL T_OS_MDL_HDL P_ADM;

  #define _P_ADM  ((T_ADM_TABLE_PUB *)P_ADM)         // shortcut

  #define P_adm_data             (_P_ADM->_p_data);

  #define adm_start              _P_ADM->p_start
  #define adm_stop               _P_ADM->p_stop
  #define adm_pre_replace        _P_ADM->p_pre_replace
  #define adm_pre_delete         _P_ADM->p_pre_delete

  #define adm_set_time           _P_ADM->p_set_time
  #define adm_mdl_decrypt_all    _P_ADM->p_mdl_decrypt_all
  #define adm_file_load_chunked  _P_ADM->p_file_load_chunked
  #define adm_sig_verify         _P_ADM->p_sig_verify
#endif



#endif // __ADM_H_PUB_INCLUDED__

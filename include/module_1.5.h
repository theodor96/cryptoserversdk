/*****************************************************************************
 *                                                                           
 *  Filename    : module.h                                                     
 *                                                                           
 *  Author(s)   : Dipl. Inf. Rainer Herbertz                                 
 *                Utimaco AG                                                 
 *                                                                           
 *  Description : Definitions for CS2000 modules                    
 *                                                                           
 *  History     :                                                            
 *  Date       |                 Action                          |  Author   
 *  -----------|-------------------------------------------------|---------  
 *  26.04.2001 | Creation                                        |  R.H.     
 *  27.02.2002 | Version 0.4                                     |  R.H.     
 *  04.11.2002 | Change to Version 1.0                           |  R.H.     
 *  19.09.2003 | Version 1.1                                     |  R.H.     
 *  12.11.2004 | Version 1.2                                     |  R.H.
 *  23.01.2007 | Version 1.3: module_wait_ext()                  |  R.H.
 *  04.07.2008 | Version 1.4: module_init_terminate              |  R.H.
 *  17.06.2013 | Version 1.5: set CPU type for CSe [2]           |  S.K.
 *****************************************************************************/
#ifndef __MODULE_H_PUB_INCLUDED__
#define __MODULE_H_PUB_INCLUDED__

#include <os_mdl.h>
#include <cs2_macro.h>
#include <stdio.h>

#define MODULE_INIT_C <module_init_1.5.c>

typedef struct
{
  unsigned char  tag[8];
  unsigned char  abbr[12];
  unsigned int   id;
  unsigned int   version;
  char           name[32];
} 
T_MODULE_INFO;

#define MODULE_INFO_TAG  { 0xA3, 0x07, 0x55, 0x2E, 0xD3, 0x44, 0xD5, 0xBA }

typedef struct
{
  T_OS_MDL_HDL   *p_mdl_hdl;
  unsigned char  name[13];
  unsigned int   version;
  int            flags;
} 
T_MODULE_LINK_TAB;

#define MODULE_OPTIONAL    1
#define MODULE_DEFER_WAIT  2

// function prototypes:
int  module_start(void*);
void module_init_failed(int err);
void module_init_terminate(int err, int state);
int  module_wait_ext(void);

// Error Codes:
#define E_MODULE_ERR_SMOS     (0xB000FC00 | (MDL_ID_TYP(Module_info.id) << 16))
#define E_MODULE_ERR_TASK     (0xB000FD00 | (MDL_ID_TYP(Module_info.id) << 16))
#define E_MODULE_ERR_LINK(ct) (0xB000FE00 | (MDL_ID_TYP(Module_info.id) << 16) | ct)
#define E_MODULE_ERR_WAIT(ct) (0xB000FF00 | (MDL_ID_TYP(Module_info.id) << 16) | ct)

#endif /* __MODULE_H_PUB_INCLUDED__ */

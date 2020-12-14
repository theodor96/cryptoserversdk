/*****************************************************************************
 *                                                                           
 *  Filename    : module_init.c                                                     
 *                                                                           
 *  Author(s)   : Dipl. Inf. Rainer Herbertz                                 
 *                Utimaco AG                                                 
 *                                                                           
 *  Description : Initialization functions for a CryptoServer module                    
 *                To be included in <name>_global.c
 *                                                                           
 *  History     :                                                            
 *  Date       |                 Action                          |  Author   
 *  -----------|-------------------------------------------------|---------  
 *  26.04.2001 | Creation                                        |  R.H.     
 *  27.02.2002 | Version 0.4                                     |  R.H.     
 *  14.03.2002 | Version 0.5                                     |  R.H.     
 *  04.07.2002 | Patch: MODULE_INIT_TASK_STACK_MEM               |  R.H.     
 *  13.08.2002 | Bug-Fix: MODULE_INIT_TASK_STACK_MEM             |  R.H.     
 *  04.11.2002 | Change to Version 1.0                           |  R.H.     
 *  19.09.2003 | Version 1.1                                     |  R.H.     
 *  12.11.2004 | Version 1.2                                     |  R.H.
 *  23.01.2007 | Version 1.3: module_wait_ext()                  |  R.H.
 *  04.07.2008 | Version 1.4: module_init_terminate              |  R.H.
 *  17.06.2013 | Version 1.5: set CPU type for CSe [2]           |  S.K.
 *****************************************************************************/
#include <os_task.h>
#include <os_mdl.h>
#include <os_log.h>
#include <os_mem.h>


#if defined(MODULE_NEEDS_EXT_REFS) || defined(MODULE_INIT_TASK_FUNCTION) || defined(MODULE_HAS_EXT_INTERFACE)
  #define START_INIT_TASK

  static FAR void *P_init_task;

  void module_init(void *);

  #ifndef MODULE_INIT_TASK_PRIO
    #define MODULE_INIT_TASK_PRIO 0
  #endif

  #ifndef MODULE_INIT_TASK_NAME
    #define MODULE_INIT_TASK_NAME "INIT_TASK"
  #endif

#endif


#define MDL_ID_TYP(x) ((unsigned short)CS2_BIG_ENDIAN_TO_U32(x))


//-----------------------------------------------------------------------------
// module_start
//-----------------------------------------------------------------------------
int module_start(void *p_coff_mem)
{
  int reply;

#ifdef START_INIT_TASK
  // template of task param. for the init task
  static const FAR T_OS_TASK_PAR task_par = { MODULE_INIT_TASK_NAME,
                                              OS_TASK_ID_INVALID,
                                              MODULE_INIT_TASK_PRIO,
  #ifdef MODULE_INIT_TASK_STACK_SIZE    
                                              MODULE_INIT_TASK_STACK_SIZE+0x1000,
  #else
                                              0x1000,
  #endif
                                              NULL,
                                              module_init,
                                              OS_MEM_TYPE_SD,
  #ifdef MODULE_INIT_TASK_STACK_MEM
                                              MODULE_INIT_TASK_STACK_MEM
  #else
                                              OS_MEM_TYPE_SD 
  #endif
                                            };

  P_init_task = NULL;
#endif

  // register module at SMOS
  if ((reply = os_mdl_link_new(Module_info.abbr,
                               CS2_BIG_ENDIAN_TO_U32(Module_info.version),
                               MDL_ID_TYP(Module_info.id),
                               p_coff_mem, (void *)&Module_pub)) != 0)
  {
    os_log_print("FATAL: can't register module %s (0x%x) at SMOS\n", Module_info.abbr,MDL_ID_TYP(Module_info.id));
    return(reply);
  }

#ifdef _TMS320C6457
  os_mdl_cpu_set(MDL_ID_TYP(Module_info.id),2);
#else  
  #ifdef _TMS320C6400
    os_mdl_cpu_set(MDL_ID_TYP(Module_info.id),1);

    #if defined(MODULE_NEEDS_SMOS_VER) && (MODULE_NEEDS_SMOS_VER < 0x02000000)
      #undef MODULE_NEEDS_SMOS_VER
    #endif

  #endif
#endif

#ifdef MODULE_NEEDS_SMOS_VER
  // check SMOS version
  reply = 0;
  os_mdl_name_get(0,NULL,&reply);
  if (reply < MODULE_NEEDS_SMOS_VER)
  {
    os_mdl_state_set(MDL_ID_TYP(Module_info.id), OS_MDL_INIT_FAILED);
    os_log_print("FATAL: module %s needs SMOS version >= %08X\n", Module_info.abbr,MODULE_NEEDS_SMOS_VER);
    return(E_MODULE_ERR_SMOS);
  }
#endif


#ifdef START_INIT_TASK
  // start init task
  if ((P_init_task = os_task_new(&task_par)) == NULL)
  {
    os_mdl_state_set(MDL_ID_TYP(Module_info.id), OS_MDL_INIT_FAILED);
    return(E_MODULE_ERR_TASK);
  }
#else
  // no init task will be started 
  os_mdl_state_set(MDL_ID_TYP(Module_info.id), OS_MDL_INIT_OK);
#endif  

  return(0);
}

//-----------------------------------------------------------------------------
// module_init_terminate
//-----------------------------------------------------------------------------
void module_init_terminate(int err, int state)
{
  os_mdl_state_set(MDL_ID_TYP(Module_info.id), state);

#ifdef START_INIT_TASK
  if (P_init_task != NULL)
  {
    // delete init task
    os_task_del(P_init_task, NULL);
    P_init_task = NULL;
  }
#endif

  if (err)
  {
    os_log_print("FATAL: initializing of module 0x%02x (%s) failed, err = %X\n", MDL_ID_TYP(Module_info.id),Module_info.abbr,err);
  }
}

//-----------------------------------------------------------------------------
// module_init_failed
//-----------------------------------------------------------------------------
void module_init_failed(int err)
{
  module_init_terminate(err, OS_MDL_INIT_FAILED);
}

//-----------------------------------------------------------------------------
// module_init
//-----------------------------------------------------------------------------
#ifdef START_INIT_TASK
  void  module_init(void *p_data)
  {
    int                         err = 0;

#ifdef MODULE_NEEDS_EXT_REFS
    int                         ct;
    const T_MODULE_LINK_TAB     *p_mod;           // pointer to module link table
  
    os_mdl_state_set(MDL_ID_TYP(Module_info.id), OS_MDL_INIT_INTERNAL);

    ct = 0;
    for (p_mod = Module_link_tab;err == 0 && p_mod->p_mdl_hdl != NULL;p_mod++,ct++)
    {
      if ((*p_mod->p_mdl_hdl = os_mdl_link_pub(p_mod->name,p_mod->version)) == NULL)
      {
        if ((p_mod->flags & MODULE_OPTIONAL) == 0)
        {
          err = E_MODULE_ERR_LINK(ct);
          os_log_print("module %s can't find module %s (%08x)\n", Module_info.abbr,p_mod->name,p_mod->version);
        }
      }
    }
          
    os_mdl_state_set(MDL_ID_TYP(Module_info.id), OS_MDL_INIT_DEP_OK);

    ct = 0;
    
    for (p_mod = Module_link_tab; err == 0 && p_mod->p_mdl_hdl != NULL; p_mod++,ct++)
    {
      if (  *p_mod->p_mdl_hdl == NULL 
         || (p_mod->flags & MODULE_DEFER_WAIT) != 0
         )
        continue;

      if(os_mdl_state_wait(p_mod->name, OS_MDL_INIT_OK) != 0)
      {
        if ((p_mod->flags & MODULE_OPTIONAL) == 0)
        {
          err = E_MODULE_ERR_WAIT(ct);
          os_log_print("module %s waiting for module %s (%08x) failed\n", Module_info.abbr,p_mod->name,p_mod->version);
        }
        else 
        {
          *p_mod->p_mdl_hdl = NULL;
        }
      }
    }
#endif

    if (  err == 0
#ifdef MODULE_INIT_TASK_FUNCTION
       && (err = MODULE_INIT_TASK_FUNCTION()) == 0
#endif
       )
    {
      os_mdl_state_set(MDL_ID_TYP(Module_info.id), OS_MDL_INIT_OK);

#ifdef MODULE_HAS_EXT_INTERFACE 
      if (cmds_register(MDL_ID_TYP(Module_info.id),
                        sizeof(Module_func_tab) / sizeof(T_CMDS_FCT *),
                        Module_func_tab) != 0)
      {
        os_log_print("module %s can't register external functions\n",Module_info.abbr);
      }
      else
#endif
      {
        os_log_print("module 0x%02x (%s) initialized successfully\n", MDL_ID_TYP(Module_info.id),Module_info.abbr);
      }
    }
    else
    {
      os_mdl_state_set(MDL_ID_TYP(Module_info.id), OS_MDL_INIT_FAILED);
      os_log_print("FATAL: module 0x%02x (%s) initialization failed (err = %x)\n", MDL_ID_TYP(Module_info.id),Module_info.abbr,err);
    }

    P_init_task = NULL;    
    os_task_del(os_task_id_get(), NULL);              // delete init task
  }
#endif // #ifdef START_INIT_TASK


#ifdef MODULE_NEEDS_EXT_WAIT
  //-----------------------------------------------------------------------------
  // module_wait_ext
  //-----------------------------------------------------------------------------
  int module_wait_ext(void)
  {
    int err = 0;
    int ct = 0;
    const T_MODULE_LINK_TAB *p_mod;          

    for (p_mod = Module_link_tab; p_mod->p_mdl_hdl != NULL; p_mod++, ct++)
    {
      if (  *p_mod->p_mdl_hdl == NULL 
         || (p_mod->flags & MODULE_DEFER_WAIT) == 0
         ) 
        continue;

      if (os_mdl_state_wait(p_mod->name, OS_MDL_INIT_OK) != 0)
      {
        if ((p_mod->flags & MODULE_OPTIONAL) == 0)
        {
          err = E_MODULE_ERR_WAIT(ct);
          os_log_print("module %s waiting for module %s (%08x) failed\n", Module_info.abbr,p_mod->name,p_mod->version);
        }
        
        *p_mod->p_mdl_hdl = NULL;
      }
    }

    return(err);
  }
#endif // #ifdef MODULE_NEEDS_EXT_WAIT


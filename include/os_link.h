/**************************************************************************************************
 *
 *  Description : Double linked lists
 *                Public header file
 *
 *  Project     : SMOS
 *
 *  Author(s)   : Georg Weber
 *                Yves Jaeger
 *                Georg Greven
 *                Dipl. Inf. Rainer Herbertz
 *                Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 **************************************************************************************************/
#ifndef __OS_LINK_H_PUB_INCLUDED__
#define __OS_LINK_H_PUB_INCLUDED__

/************************************************************************************************
 * define structure of the head of a double linked list
 ************************************************************************************************/
typedef struct
{
  struct _T_OS_LINK *p_first;                 // address of the first element of the list  
  struct _T_OS_LINK *p_last;                  // address of the last  element of the list  
  unsigned int      cnt;                      // number of linked elements                 
  void              *p_user;                  // user defined address (used to return the address of the structure where the head is embedded to
}
T_OS_LINK_HEAD;

/************************************************************************************************
 * define structure of element of a double linked list
 ************************************************************************************************/
typedef struct _T_OS_LINK
{
  struct _T_OS_LINK *p_next;                   // address of the next element of the list
  struct _T_OS_LINK *p_prev;                   // address of the previous element of the list
  T_OS_LINK_HEAD    *p_owner;                  // address of the head of the list owning the element
  void              *p_user;                   // user defined address (used to return the address of the structure where the head is embedded to
}
T_OS_LINK;

/*************************************************************************************************
 * Macros
 *************************************************************************************************/
#define os_link_del_elem(p_link)        os_link_rmv((p_link)->p_owner, p_link)
#define os_link_del_head(x)
#define os_link_get_cnt(p_head)         ((p_head)->cnt)
#define os_link_get_first(p_head)       ((p_head)->p_first)
#define os_link_get_last(p_head)        ((p_head)->p_last)
#define os_link_get_next(p_link)        ((p_link)->p_next)
#define os_link_get_owner(p_link)       ((p_link)->p_owner)
#define os_link_get_prev(p_link)        ((p_link)->p_prev)
#define os_link_get_user(p_link)        ((p_link)->p_user)
#define os_link_get_user_head(p_head)   ((p_head)->p_user)

/*************************************************************************************************
 * Structure definitions
 *************************************************************************************************/
typedef struct _os_link_public_interface
{
  void            *dumy1;
  void            *dumy2;
  void            *dumy3;
  void            *dumy4;
  void            *dumy5;
  void            *dumy6;
  void            *dumy7;
  void            *dumy8;
  void            *dumy9;
  void            *dumy10;
  void            (*_p_os_link_ins      ) (T_OS_LINK_HEAD*, T_OS_LINK*, T_OS_LINK*);
  void            (*_p_os_link_mov      ) (T_OS_LINK_HEAD*, T_OS_LINK*, T_OS_LINK_HEAD*, T_OS_LINK*);
  void            (*_p_os_link_new_elem ) (T_OS_LINK_HEAD*, T_OS_LINK*, void*);
  void            (*_p_os_link_new_head ) (T_OS_LINK_HEAD*, void*);
  T_OS_LINK      *(*_p_os_link_rmv      ) (T_OS_LINK_HEAD*, T_OS_LINK*);
}
T_OS_LINK_TABLE_PUB;

#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

  /*** C-style linking of the modules ***********************************************************
   * This section contains the C-style function prototypes. It is active when the modules are
   * linked together using the linker or a shared library (i.e., in the SDK). It is also used
   * for the module itself.
   **********************************************************************************************/
  void            os_link_ins     (T_OS_LINK_HEAD *p_head, T_OS_LINK *p_link, T_OS_LINK *p_prev);
  void            os_link_mov     (T_OS_LINK_HEAD *p_head_src, T_OS_LINK *p_link, T_OS_LINK_HEAD *p_head_dst, T_OS_LINK *p_prev);
  void            os_link_new_elem(T_OS_LINK_HEAD *p_head, T_OS_LINK *p_link, void *p_user);
  void            os_link_new_head(T_OS_LINK_HEAD *p_head, void *p_user);
  T_OS_LINK      *os_link_rmv     (T_OS_LINK_HEAD *p_head, T_OS_LINK *p_link);

#else
  /*** smos linking of the modules **************************************************************
   * This section is active when dynamic loading/linking of the modules using the Module Loader
   * is in effect.
   **********************************************************************************************/

  /************************************************************************************************
   * macros to use the public interface and global data of key server module
   ************************************************************************************************/
  #define _P_OS_LINK  ((T_OS_LINK_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_link))

  #define os_link_ins            _P_OS_LINK->_p_os_link_ins
  #define os_link_mov            _P_OS_LINK->_p_os_link_mov
  #define os_link_new_elem       _P_OS_LINK->_p_os_link_new_elem
  #define os_link_new_head       _P_OS_LINK->_p_os_link_new_head
  #define os_link_rmv            _P_OS_LINK->_p_os_link_rmv

#endif /* defined(_OS_C_INT_) || defined(_ALWAYS_C_INT_) */

#endif

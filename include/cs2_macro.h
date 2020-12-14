/**************************************************************************************************
 *
 * $File Identification                    $
 * $Filename          : cs2_macro.h        $
 * $Module version    : x.x.x.x            $
 * $Module name       : SMOS               $
 * $Release Date      : DD.MM.YYYY         $
 *
 * description:
 *   Useful macros for the CS2 software modules
 *
 *
 * history:
 * initials |    date    | activity
 * ---------+------------+------------------------------------------------------------------------
 *   DWE    | 26.04.2000 | file created by usage of csd_macros.h from project CSD
 *   RHE    | 06.08.2002 | 
 *
 **************************************************************************************************/

#ifndef   __CS2_MACRO_H_PUB_INCLUDED__
#  define __CS2_MACRO_H_PUB_INCLUDED__

  /************************************************************************************************
   * this macro returns the maximal index + 1 of an array
   ************************************************************************************************/
#  define CS2_ARRAY_LEN(a) ( sizeof (a) / sizeof (*(a)) )
  
  /************************************************************************************************
   * this macro rounds x up to the next y boundary (y is 2^n)
   ************************************************************************************************/
#  define CS2_ALIGN(x,y)     (((x) + ((y) - 1)) & ~((y) - 1))

  /************************************************************************************************
   * This macro returns TRUE, if the pointer is aligned to a specific boundary 
   * else FALSE is returned
   ************************************************************************************************/
#  define     CS2_PTR_ALG_VAL(ptr, alg)                      \
                  ((((UPTR) (ptr)) & ((alg) - 1) ) == 0)

  /************************************************************************************************
   * This macro returns TRUE, if the pointer is aligned to its specific boundary 
   * else FALSE is returned
   ************************************************************************************************/
#  define     CS2_PTR_ALG(ptr) CS2_PTR_ALG_VAL ( (ptr), sizeof (*ptr))

  /************************************************************************************************
   * This macro returns TRUE, if the pointer is valid (!= NULL) AND aligned to a specific
	 * boundary else FALSE is returned
   ************************************************************************************************/
#  define     CS2_IS_PTR_ALG(ptr, alg)                       \
                (                                            \
                  ((        (ptr)                != NULL) && \
                  ((((UPTR) (ptr)) & ((alg) - 1) ) == 0   ))   \
							  )
 
  /************************************************************************************************
   * This macro returns TRUE, if the pointer is valid (!= NULL) AND aligned to its specific
	 * boundary (only valid for int*, unsigned int*, short* and unsigned short*) else FALSE is returned
   ************************************************************************************************/
#  define     CS2_IS_PTR_OK(ptr) CS2_IS_PTR_ALG ( (ptr), sizeof (*ptr))


  /************************************************************************************************
   * this macro converts a double word in memory from Big Endian to Little Endian, and vice versa.
   * The parameter a is the address of the dword.
   * OSI 15. 3. 00
   ************************************************************************************************/
#  define CS2_ENDIAN_SWAP_U32(a) ( ( ((unsigned int)(a) & 0xFF000000) >> 24 ) \
                                 | ( ((unsigned int)(a) & 0x00FF0000) >>  8 ) \
                                 | ( ((unsigned int)(a) & 0x0000FF00) <<  8 ) \
                                 | ( ((unsigned int)(a) & 0x000000FF) << 24 ) \
                                 )

  /************************************************************************************************
   * this macro converts a word in memory from Big Endian to Little Endian, and vice versa.
   * The parameter a is the address of the dword.
   * OSI 15. 3. 00
   ************************************************************************************************/
#  define CS2_ENDIAN_SWAP_U16(a) ( (unsigned short) ( ( ((unsigned short)(a) & 0xFF00) >>  8 ) \
                                         | ( ((unsigned short)(a) & 0x00FF) <<  8 ) \
                                 )       )

  /************************************************************************************************
   * This macros does a conversions into little or big endian. Dependent from the defined endianess 
   * a real conversion or nothing is done
   * The parameters are unsigned int, unsigned short, unsigned int* or unsigned short* (see macro name).
   * DWE 02.08.2000
   ************************************************************************************************/

#ifdef CS2_SDK

#    define CS2_U32_TO_BIG_ENDIAN(a)                CS2_ENDIAN_SWAP_U32(a)
#    define CS2_U32_TO_LITTLE_ENDIAN(a)             ((unsigned int)(a))

#    define CS2_U16_TO_BIG_ENDIAN(a)                CS2_ENDIAN_SWAP_U16(a)
#    define CS2_U16_TO_LITTLE_ENDIAN(a)             ((unsigned short)(a))

#    define CS2_BIG_ENDIAN_TO_U32(a)                CS2_ENDIAN_SWAP_U32(a)
#    define CS2_LITTLE_ENDIAN_TO_U32(a)             ((unsigned int)(a))

#    define CS2_BIG_ENDIAN_TO_U16(a)                CS2_ENDIAN_SWAP_U16(a)
#    define CS2_LITTLE_ENDIAN_TO_U16(a)             ((unsigned short)(a))

#else

#    define CS2_U32_TO_BIG_ENDIAN(a)                ((unsigned int)(a))
#    define CS2_U32_TO_LITTLE_ENDIAN(a)             CS2_ENDIAN_SWAP_U32(a)

#    define CS2_U16_TO_BIG_ENDIAN(a)                ((unsigned short)(a))
#    define CS2_U16_TO_LITTLE_ENDIAN(a)             CS2_ENDIAN_SWAP_U16(a)

#    define CS2_BIG_ENDIAN_TO_U32(a)                ((unsigned int)(a))
#    define CS2_LITTLE_ENDIAN_TO_U32(a)             CS2_ENDIAN_SWAP_U32(a)

#    define CS2_BIG_ENDIAN_TO_U16(a)                ((unsigned short)(a))
#    define CS2_LITTLE_ENDIAN_TO_U16(a)             CS2_ENDIAN_SWAP_U16(a)

#endif



  /************************************************************************************************
   * Cute way of swapping two variables's contents. Seen in Bruce Schneier's book.
   * OSI 15. 3. 00
   ************************************************************************************************/
#  define CS2_SWAP(x,y)   ((x)^=(y), (y)^=(x), (x)^=(y)) 
  
  /************************************************************************************************
   * define a macro to get a pointer of an item located behind the structure to which "p_var"
   * points to. The type of the item is specified by the parameter "type"
   ************************************************************************************************/
#  define CS2_DATA_GET(type,p_var) ((type) (void*) ((p_var)+1))

  /************************************************************************************************
   * define a macro to generate 32-bit character constants
   * CS2_TAG_CREATE ('1','2','3','4') creates the value 0x31323334
   ************************************************************************************************/
#  define CS2_TAG_CREATE(a,b,c,d)  CS2_U32_TO_BIG_ENDIAN ( (((unsigned int) (a)) << 24) \
                                                         | (((unsigned int) (b)) << 16) \
                                                         | (((unsigned int) (c)) <<  8) \
                                                         | (((unsigned int) (d)) <<  0) \
                                                       )

#  define CS2_TAG_CREATE_BE(a,b,c,d)                     ( (((unsigned int) (a)) << 24) \
                                                         | (((unsigned int) (b)) << 16) \
                                                         | (((unsigned int) (c)) <<  8) \
                                                         | (((unsigned int) (d)) <<  0) \
                                                         )
     

#endif /*  __CS2_MACRO_H_PUB_INCLUDED__ */

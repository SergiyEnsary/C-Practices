//
// Created by sergiy on 1/22/21.
//
/** **/
#if !defined(HDR)
#define HDR
/* contents of hdr.h go here */
#endif

/** **/
#if SYSTEM == SYSV
    #define HDR "sysv.h"
#elif SYSTEM == BSD
    #define HDR "bsd.h"
#elif SYSTEM == MSDOS
    #define HDR "msdos.h"
#else
    #define HDR "default.h"
#endif
#include HDR

/** **/
#ifndef HDR
#define HDR
/* contents of hdr.h go here */
#endif
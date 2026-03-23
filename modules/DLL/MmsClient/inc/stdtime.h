/*****************************************************************************/
/* SISCO SOFTWARE MODULE HEADER **********************************************/
/*****************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,            */
/*            2005 All Rights Reserved                                       */
/*                                                                           */
/* MODULE NAME : stdtime.h                                                   */
/* PRODUCT(S)  : Standard Time Management Library                            */
/*                                                                           */
/* MODULE DESCRIPTION:                                                       */
/*   Header file for Standard Time Management Library Functions              */
/*                                                                           */
/*   Note:  most functions a produce a return-code value STDTIME_RC.         */
/*   the return code is zero if successful, otherwise it is a structured     */
/*   value in which the low-order 10 bits enumerates an error reason,        */
/*   and the upper 20 bits enumerates the high-level and low-level           */
/*   functions where the error was detected.                                 */
/*                                                                           */
/* MODIFICATION LOG:                                                         */
/*   Date    Who  Rev  Comments                                              */
/* --------  ---  ---  ----------------------------------------------------- */
/* 03/18/07  RLH   10  Remove tabs from source code inadvertantly added.     */
/* 03/16/07  RLH   09  Normalize struct tm, SYSTEMTIME, and STDTIME_FIELDS   */
/*                     after rounding is applied; no rounding for formatting */
/*                     functions.                                            */
/* 02/16/07  RLH   08  Clean up minor warnings under Linux                   */
/* 01/10/07  RLH   07  Add TruncStdTimeString functions                      */
/* 11/29/06  RLH   06  Correction to STDTIME_TIME_T64_ENABLED setting        */
/* 10/18/06  RLH   05  Enhanced capabilities for timezone rules              */
/* 10/27/06  RLH   04  Change STDTIME_RET, STDTIME_IF, STDTIME_IFNOT macros  */
/* 09/13/06  RLH   03  Ensure local time conversions work when TZ not set    */
/* 06/07/06  RLH   02  Numerous features added, see stdtime.doc              */
/* 01/18/06  RLH   01  Created                                               */
/*****************************************************************************/

#ifndef _STDTIME_H_7583ECB2_DB3F_48B3_8A97_2D1D2A38C84A_
#define _STDTIME_H_7583ECB2_DB3F_48B3_8A97_2D1D2A38C84A_


#undef STDTIME_MSVC6
#undef STDTIME_MSVC7
#undef STDTIME_MSVC8

#ifdef _MSC_VER

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif


#if   (_MSC_VER >= 1400)
#define STDTIME_MSVC8
#elif (_MSC_VER >= 1300)
#define STDTIME_MSVC7
#elif (_MSC_VER >= 1200)
#define STDTIME_MSVC6
#endif


#if 0

#if   (_MSC_VER >= 1400)
#pragma comment(lib, "stdtimelib.lib")
#elif (_MSC_VER >= 1300)
#pragma comment(lib, "stdtimelib.lib")
#elif (_MSC_VER >= 1200)
#pragma comment(lib, "stdtimelib.lib")
#endif

#endif /* 0 */


#endif /* _MSC_VER */

/* to test for STDTIME library being used */
#undef  STDTIME_DEFINED
#define STDTIME_DEFINED     1

/*****************************************************************************/
/*  LIBRARY HEADERS                                                          */
/*****************************************************************************/

/* UNICODE or ANSI, but not both */

#if defined(STDTIME_UNICODE) && defined(STDTIME_ANSI)
#error Both STDTIME_UNICODE and STDTIME_ANSI defined
#undef STDTIME_UNICODE
#endif

/* UNICODE or _UNICODE implies STDTIME_UNICODE, but not if ANSI defined */

#if (!defined(STDTIME_UNICODE)) && (!defined(STDTIME_ANSI))
#if defined(UNICODE) || defined(_UNICODE)
#define STDTIME_UNICODE
#endif
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/timeb.h>


/*****************************************************************************/
/* <time.t> with support for gmtime_r and localtime_r if possible            */
/*****************************************************************************/

#undef  STDTIME_REENTRANT_GMTIME_LOCALTIME

#undef  STDTIME_DEFINED_LINUX__USE_POSIX
#if defined(linux)
#define STDTIME_REENTRANT_GMTIME_LOCALTIME
#ifndef                      __USE_POSIX
#define                      __USE_POSIX
#define STDTIME_DEFINED_LINUX__USE_POSIX
#endif
#endif

#undef  STDTIME_DEFINED_SOLARIS_REENTRANT
#if defined(sun)
#define STDTIME_REENTRANT_GMTIME_LOCALTIME
#ifndef                        _REENTRANT
#define                        _REENTRANT
#define STDTIME_DEFINED_SOLARIS_REENTRANT
#endif
#endif

#undef  STDTIME_DEFINED_SOLARIS_POSIX_PTHREAD_SEMANTICS
#if defined(sun)
#ifndef                        _POSIX_PTHREAD_SEMANTICS
#define                        _POSIX_PTHREAD_SEMANTICS
#define STDTIME_DEFINED_SOLARIS_POSIX_PTHREAD_SEMANTICS
#endif
#endif

#undef  STDTIME_DEFINED_AIX_THREAD_SAFE
#if defined(_AIX)
#define STDTIME_REENTRANT_GMTIME_LOCALTIME
#ifndef                    _THREAD_SAFE
#define                    _THREAD_SAFE
#define STDTIME_DEFINED_AIX_THREAD_SAFE
#endif
#endif

#undef  STDTIME_DEFINED_DEC_UNIX_REENTRANT
#if defined(__alpha) && !defined(__VMS)
#define STDTIME_REENTRANT_GMTIME_LOCALTIME
#ifndef                         _REENTRANT
#define                         _REENTRANT
#define STDTIME_DEFINED_DEC_UNIX_REENTRANT
#endif
#endif


#include <time.h>


#if defined(sun)
struct tm * gmtime_r    (const time_t * pTimeT, struct tm * pStructTm);
struct tm * localtime_r (const time_t * pTimeT, struct tm * pStructTm);
#endif


/* clean up macro namespace */

#ifdef  STDTIME_DEFINED_LINUX__USE_POSIX
#undef  STDTIME_DEFINED_LINUX__USE_POSIX
#undef                       __USE_POSIX
#endif

#ifdef  STDTIME_DEFINED_SOLARIS_REENTRANT
#undef  STDTIME_DEFINED_SOLARIS_REENTRANT
#undef                         _REENTRANT
#endif

#ifdef  STDTIME_DEFINED_SOLARIS_POSIX_PTHREAD_SEMANTICS
#undef  STDTIME_DEFINED_SOLARIS_POSIX_PTHREAD_SEMANTICS
#undef                         _POSIX_PTHREAD_SEMANTICS
#endif

#ifdef  STDTIME_DEFINED_DEC_UNIX_REENTRANT
#undef  STDTIME_DEFINED_DEC_UNIX_REENTRANT
#undef                          _REENTRANT
#endif

#ifdef  STDTIME_DEFINED_AIX_THREAD_SAFE
#undef  STDTIME_DEFINED_AIX_THREAD_SAFE
#undef                     _THREAD_SAFE
#endif


/*****************************************************************************/
/*  support _T notation on non-Windows platforms                             */
/*****************************************************************************/

#if (!defined(_T)) && (!defined(__T))
#ifdef STDTIME_UNICODE
#define __T(x) L##x
#define _T(x)  __T(x)
#else
#define __T(x) x
#define _T(x)  x
#endif
#endif /* not defined _T and __T */

#include "stdtime_config.h"


/*****************************************************************************/
/*  determine if "stdtime_timezone_csv.h" file is "merged" or not.           */
/*                                                                           */
/*  the csv file gets "merged" if there is no comma separating one line      */
/*  from the next.  a "merged" file is the normal format for a csv data      */
/*  file, but when used as part of a C program, the lack of a comma causes   */
/*  the last string value on one line to get concatenated by the compiler    */
/*  to the first string value on the next line.  we need to know if the      */
/*  file is "merged" or "unmerged" to know how to 'undo' the merging.        */
/*                                                                           */
/*  an unmerged file is easier and faster to process, while a merged file    */
/*  maintains source compatibility with the original Boost.org timezone      */
/*  database file from which it originated.                                  */
/*                                                                           */
/*****************************************************************************/

#if defined(STDTIME_MERGED_CSV) && defined(STDTIME_UNMERGED_CSV)
#error Both STDTIME_MERGED_CSV and STDTIME_UNMERGED_CSV defined
#undef STDTIME_UNMERGED_CSV
#endif

#if !defined(STDTIME_MERGED_CSV) && !defined(STDTIME_UNMERGED_CSV)
#define STDTIME_MERGED_CSV /* default */
#endif


/*****************************************************************************/
/*  determine how GMT is converted to local time, and vice-versa.            */
/*                                                                           */
/*  using a system API for a definition of what "local" is will be faster,   */
/*  but if the SYSTEMTIMEZONE or TZ environment variable does not agree      */
/*  with the OS's understanding of what "local" is, there will be a          */
/*  conflict.  if the time library is likely to be used for a non-local      */
/*  time zone, defining STDTIME_LOCAL_USES_TZDB is necessary.                */
/*  otherwise, define STDTIME_LOCAL_USES_SYSAPI for speed.                   */
/*                                                                           */
/*****************************************************************************/

#if defined(STDTIME_LOCAL_USES_TZDB) && defined(STDTIME_LOCAL_USES_SYSAPI)
#error Both STDTIME_LOCAL_USES_TZDB and STDTIME_LOCAL_USES_SYSAPI defined
#undef STDTIME_LOCAL_USES_SYSAPI
#endif

#if !defined(STDTIME_LOCAL_USES_TZDB) && !defined(STDTIME_LOCAL_USES_SYSAPI)
#define STDTIME_LOCAL_USES_SYSAPI  /* default */
#endif


/*****************************************************************************/
/*  C++ ONLY ENABLED OR DISABLED                                             */
/*                                                                           */
/*  use StdTimeConfig.h to set STDTIME_CPP_ONLY_ENABLED/DISABLED             */
/*****************************************************************************/


#ifdef __cplusplus

#if defined(STDTIME_CPP_ONLY_ENABLED) && defined(STDTIME_CPP_ONLY_DISABLED)
#error Both STDTIME_CPP_ONLY_ENABLED and STDTIME_CPP_ONLY_DISABLED defined
#undef STDTIME_CPP_ONLY_ENABLED
#endif

#if !defined(STDTIME_CPP_ONLY_ENABLED) && !defined(STDTIME_CPP_ONLY_DISABLED)
#define STDTIME_CPP_ONLY_ENABLED  /* default */
#endif

#else /* not __cplusplus */

#undef STDTIME_CPP_ONLY_ENABLED
#undef STDTIME_CPP_ONLY_DISABLED
#define STDTIME_CPP_ONLY_DISABLED

#endif /* __cplusplus */


/* StdTimeW32.h needs the bool definition */


#define STDTIME_BOOL        int
#define STDTIME_TRUE        1
#define STDTIME_FALSE       0

typedef int32_t             STDTIME_RC;

/* STDTIME return codes are divided as follows: */
/*  2 bits unused */
/* 10 bits = highest level function where error detected */
/* 10 bits =  lowest level function where error detected */
/* 10 bits = error reason code (nature of problem) */


/* create error code enumeration from enum_stdtime_func.h */
/* this is done by temporary macro and include file */

#define STDTIME_ENUM_FUNC(x)  STDTIME_FUNC__##x,

enum
  {
  STDTIME_FUNC__0000,       /* dummy 0 entry */
#include "stdtime_enum_func.h"
  STDTIME_FUNC__SIZE
  };

/* temporary macro has served its purpose, so undefine it */
#undef  STDTIME_ENUM_FUNC


/* now redefine macro for main purpose, to declare 'rc' and 'func' */
/* within each function that returns a STDTIME_RC return code. */


#define STDTIME_ENUM_FUNC(x)                                                  \
  STDTIME_RC rc;                                                              \
  STDTIME_RC func;                                                            \
  rc = -1;                                                                    \
  func = (STDTIME_RC) STDTIME_FUNC__##x;


/* create error code enumeration from enum_stdtime_err.h */
/* this is done by temporary macro and include file */

#define STDTIME_ENUM_ERR(x)   STDTIME_ERR__##x,

enum
  {
  STDTIME_ERR__0000,        /* dummy 0 entry */
#include "stdtime_enum_err.h"
  STDTIME_ERR__SIZE
  };

/* temporary macro has served its purpose, so undefine it */
#undef  STDTIME_ENUM_ERR


#define STDTIME_10_BITS     0x3FF
#define STDTIME_20_BITS     0xFFFFF

#define STDTIME_OK          0
#define STDTIME_RET(x)      return StdTimeRet (func, x)

#define STDTIME_RET_RC      STDTIME_RET(rc)
#define STDTIME_RET_OK      return STDTIME_OK

#define STDTIME_EC(x)       ((func << 10) | (STDTIME_ERR__##x))

#define STDTIME_RET_EC(x)   STDTIME_RET(STDTIME_EC(x))

#include "stdtime_quadlib.h"
#include "stdtime_w32.h"


#ifdef  __cplusplus
extern "C" {
#endif


/*****************************************************************************/
/*  TYPES AND STRUCTURES                                                     */
/*****************************************************************************/


#if defined(_MSC_VER) && defined(_WCHAR_T_DEFINED)
typedef wchar_t             STDTIME_WCHAR;
#elif defined(sun) && defined(_WCHAR_T)
typedef wchar_t             STDTIME_WCHAR;
#else
typedef unsigned short      STDTIME_WCHAR;
#endif


#ifdef STDTIME_UNICODE
#define STDTIME_TCHAR       STDTIME_WCHAR
#else
#define STDTIME_TCHAR       char
#endif /* STDTIME_UNICODE */


#ifndef STDTIME_TIME_T64_WIN
#if defined(_TIME_T_DEFINED) && defined(_WIN64)
#define STDTIME_TIME_T64_WIN
#endif
#endif

#ifndef STDTIME_TIME_T64_WIN
#ifdef _TIME64_T_DEFINED
#define STDTIME_TIME_T64_WIN
#endif
#endif


#ifndef STDTIME_TIME_T64_ENABLED
#ifdef STDTIME_TIME_T64_WIN
#define STDTIME_TIME_T64_ENABLED
#endif
#endif


#ifdef STDTIME_TIME_T64_ENABLED
#ifdef STDTIME_TIME_T64_WIN

#ifdef _TIME64_T_DEFINED
typedef __time64_t          STDTIME_WIN_TIME_T;
#else
typedef time_t              STDTIME_WIN_TIME_T;
#endif /* _TIME64_T_DEFINED */

#else /* not STDTIME_TIME_T64_WIN */
typedef QUADLIB_I64N        STDTIME_WIN_TIME_T;
#endif /* STDTIME_TIME_T64_WIN */




#else /* not STDTIME_TIME_T64_ENABLED */
typedef time_t              STDTIME_WIN_TIME_T;
#endif /* STDTIME_TIME_T64_ENABLED */


#define STDTIME_SCALE_NSEC  100     /* only 1 digit of nsec precision */
#define STDTIME_PREC_NSEC   10      /* only 1 digit of nsec precision */

#define STDTIME_WIN_EPOCH_YEAR      1601
#define STDTIME_UNIX_EPOCH_YEAR     1970
#define STDTIME_DST_CUTOFF_YEAR     1945

#define STDTIME_YEAR_MIN    STDTIME_WIN_EPOCH_YEAR    /* base/epoch year */
#define STDTIME_YEAR_MAX    9999    /* to avoid overflow in STDTIME_STRING */

#define STDTIME_INVALID             {0,0}
#define STDTIME_FIELDS_INVALID      {0,0,0,0,0,0,0,0,0}
#define STDTIME_STRING_INVALID      {0}
#define STDTIME_HEXSTR_INVALID      {0}

#define STDTIME_SPAN_INVALID    QUADLIB_I64_MAX

#define STDTIME_DELTA_DAY_MAX (8400*366)


#define STDTIME_DELTA_INVALID { 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF,           \
    0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF }                       /**/


/* an invalid span exceeds +/- 2,656,281,600,000,000,000 */
/* which is 8400*366 days in terms of 100-nanosecond intervals */
/* the pos value in hex is 24DD 020A A768 0000 */
/* the neg value in hex is DB22 FDF5 5898 0000 */

#define STDTIME_SPAN_MAX_HI     0x24DD020A
#define STDTIME_SPAN_MAX_LO     0xA7680000

#define STDTIME_SPAN_MIN_HI     0xDB22FDF5
#define STDTIME_SPAN_MIN_LO     0x58980000

#define STDTIME_ERR         (-2)
#define STDTIME_LT          (-1)
#define STDTIME_EQ          0
#define STDTIME_GT          1

#ifdef HOST_LITTLE_ENDIAN

#define STDTIME_INIT(hi,lo) {lo,hi}

typedef struct
  {
  int32_t                   lo;
  int32_t                   hi;
  }
STDTIME;

#else /* HOST_BIG_ENDIAN */

#define STDTIME_INIT(hi,lo) {hi,lo}

typedef struct
  {
  int32_t                   hi;
  int32_t                   lo;
  }
STDTIME;

#endif /* HOST_LITTLE_ENDIAN */


typedef struct
  {
  int32_t                   year;
  int32_t                   mon;
  int32_t                   day;
  int32_t                   hour;
  int32_t                   min;
  int32_t                   sec;
  int32_t                   msec;   /* milliseconds     */
  int32_t                   usec;   /* microseconds     */
  int32_t                   nsec;   /* nanoseconds      */
  }
STDTIME_FIELDS;


typedef struct
  {
  int32_t                   day;
  int32_t                   hour;
  int32_t                   min;
  int32_t                   sec;
  int32_t                   msec;
  int32_t                   usec;
  int32_t                   nsec;
  }
STDTIME_DELTA;


typedef struct
  {
  QUADLIB_I64               value;
  }
STDTIME_SPAN;


/*                                1         2         3        */
/*                      0123456789012345678901234567890123456  */
/* STRING format:       yyyy-mm-ddThh:mi:ss.fffffff#           */
/* TZO format:                                     +hh:mm:ss#  */
/*                                                 0123456789  */

#define STDTIME_STRING_DATE_LEN     10
#define STDTIME_STRING_TIME_LEN     8
#define STDTIME_STRING_FRAC_LEN     7

#define STDTIME_STRING_DATE_POS     0
#define STDTIME_STRING_TIME_POS     11
#define STDTIME_STRING_FRAC_POS     20

#define STDTIME_STRING_DLM_D1       4
#define STDTIME_STRING_DLM_D2       7
#define STDTIME_STRING_DLM_S1       10
#define STDTIME_STRING_DLM_T1       13
#define STDTIME_STRING_DLM_T2       16
#define STDTIME_STRING_DLM_F1       19

#define STDTIME_STRING_LEN          27
#define STDTIME_TZO_LEN             9
#define STDTIME_STRING_MAXLEN       (STDTIME_STRING_LEN+STDTIME_TZO_LEN)


typedef struct
  {
  char                      str [STDTIME_TZO_LEN + 1];
  }
STDTIME_TZOA;


typedef struct
  {
  STDTIME_WCHAR             str [STDTIME_TZO_LEN + 1];
  }
STDTIME_TZOW;

/* embTzo represents an 'embedded' timezone offset, a suffix to the time */
/* string 'str' in STDTIME_STRINGA and STDTIME_STRINGW. */
/* embTzo may be a null string, the letter Z or an offset like -05:00 */

/* extTzo represents an 'external' timezone offset, created as an output */
/* value by the STDTIME library.  the library creates, but does not */
/* directly use, the extTzo field. */

typedef struct
  {
  char                      str  [STDTIME_STRING_LEN];
  char                      embTzo [STDTIME_TZO_LEN + 1];
  STDTIME_TZOA              extTzo; /* external TimeZone Offset */
  }
STDTIME_STRINGA;


typedef struct
  {
  STDTIME_WCHAR             str  [STDTIME_STRING_LEN];
  STDTIME_WCHAR             embTzo [STDTIME_TZO_LEN + 1];
  STDTIME_TZOW              extTzo; /* external TimeZone Offset */
  }
STDTIME_STRINGW;


#ifdef STDTIME_UNICODE
#define STDTIME_STRING      STDTIME_STRINGW
#define STDTIME_TZO         STDTIME_TZOW
#else
#define STDTIME_STRING      STDTIME_STRINGA
#define STDTIME_TZO         STDTIME_TZOA
#endif /* STDTIME_UNICODE */


#define STDTIME_HEXSTR_LEN  16

/* HEXSTR format:           HHHHHHHHLLLLLLLL */
/* (high word, low word)    0123456789012345 */


typedef struct
  {
  char                      str [STDTIME_HEXSTR_LEN+1];
  }
STDTIME_HEXSTRA;


typedef struct
  {
  STDTIME_WCHAR             str [STDTIME_HEXSTR_LEN+1];
  }
STDTIME_HEXSTRW;


typedef struct
  {
  STDTIME_WIN_TIME_T        t;
  }
STDTIME_TIMETYPE;

#define STDTIME_API_MKTIME  mktime


#ifdef STDTIME_UNICODE
#define STDTIME_HEXSTR      STDTIME_HEXSTRW
#else
#define STDTIME_HEXSTR      STDTIME_HEXSTRA
#endif /* STDTIME_UNICODE */


#ifndef STDTIME_UNICODE_SUBSTITUTE_CHAR
#define STDTIME_UNICODE_SUBSTITUTE_CHAR '\x1A'
#endif


/* Round/Trunc field selectors */

#define STDTIME_FIELD_DAY   0
#define STDTIME_FIELD_HOUR  1
#define STDTIME_FIELD_MIN   2
#define STDTIME_FIELD_SEC   3
#define STDTIME_FIELD_MSEC  4
#define STDTIME_FIELD_USEC  5
#define STDTIME_FIELD_NSEC  6


#define STDTIME_ERRCODE_LEN  27

/* an error code has the form   0xNNNNNNNN = HHHH.LLLL.RRRR#  */
/*                              0123456789012345678901234567  */
/* this holds a raw hex RC value, and the RC as subfields     */

#define STDTIME_ERRMSG_LEN  80

typedef struct
  {
  char                      errcode [STDTIME_ERRCODE_LEN+1];
  char                      hilevel [STDTIME_ERRMSG_LEN+1];
  char                      lolevel [STDTIME_ERRMSG_LEN+1];
  char                      reason  [STDTIME_ERRMSG_LEN+1];
  }
STDTIME_ERRMSGA;


typedef struct
  {
  STDTIME_WCHAR             errcode [STDTIME_ERRCODE_LEN+1];
  STDTIME_WCHAR             hilevel [STDTIME_ERRMSG_LEN+1];
  STDTIME_WCHAR             lolevel [STDTIME_ERRMSG_LEN+1];
  STDTIME_WCHAR             reason  [STDTIME_ERRMSG_LEN+1];
  }
STDTIME_ERRMSGW;


#ifdef STDTIME_UNICODE
#define STDTIME_ERRMSG      STDTIME_ERRMSGW
#else
#define STDTIME_ERRMSG      STDTIME_ERRMSGA
#endif /* STDTIME_UNICODE */


#define STDTIME_IF(x)       ((rc=(x)) == STDTIME_OK)
#define STDTIME_IFNOT(x)    ((rc=(x)) != STDTIME_OK)


/*** helper function to assemble a STDTIME return code ***********************/

STDTIME_RC                  StdTimeRet (
  const STDTIME_RC          /*I*/ func,
  const STDTIME_RC          /*I*/ ec);


/*** unicode strcpy functions ************************************************/


STDTIME_WCHAR *             Wchar_StdTime_StrcpyWW (
  STDTIME_WCHAR *           /*O*/ pTarget,
  const STDTIME_WCHAR *     /*I*/ pSource);

STDTIME_WCHAR *             Wchar_StdTime_StrncpyWW (
  STDTIME_WCHAR *           /*O*/ pTarget,
  const STDTIME_WCHAR *     /*I*/ pSource,
  size_t                    /*I*/ nLength);


/*** StdTime/StdTimeFields conversions ***************************************/


STDTIME_RC                  StdTimeToStdTimeFields (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);

STDTIME_RC                  StdTimeFieldsToStdTime (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME *                 /*O*/ pStdTime);


/*** StdTime/external conversions ********************************************/


STDTIME_RC                  StdTimeToStdTimeStringA (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_STRINGA *         /*O*/ pStdTimeString);

STDTIME_RC                  StdTimeToStdTimeStringW (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_STRINGW *         /*O*/ pStdTimeString);

STDTIME_RC                  StdTimeToStdTimeHexStrA (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_HEXSTRA *         /*O*/ pStdTimeHexStr);

STDTIME_RC                  StdTimeToStdTimeHexStrW (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_HEXSTRW *         /*O*/ pStdTimeHexStr);

#ifdef STDTIME_UNICODE
#define StdTimeToStdTimeString  StdTimeToStdTimeStringW
#define StdTimeToStdTimeHexStr  StdTimeToStdTimeHexStrW
#else
#define StdTimeToStdTimeString  StdTimeToStdTimeStringA
#define StdTimeToStdTimeHexStr  StdTimeToStdTimeHexStrA
#endif /* STDTIME_UNICODE */


/*** external/StdTime conversions ********************************************/


STDTIME_RC                  StdTimeStringAToStdTime (
  const STDTIME_STRINGA *   /*I*/ pStdTimeString,
  STDTIME *                 /*O*/ pStdTime);

STDTIME_RC                  StdTimeStringWToStdTime (
  const STDTIME_STRINGW *   /*I*/ pStdTimeString,
  STDTIME *                 /*O*/ pStdTime);

STDTIME_RC                  StdTimeHexStrAToStdTime (
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStr,
  STDTIME *                 /*O*/ pStdTime);

STDTIME_RC                  StdTimeHexStrWToStdTime (
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStr,
  STDTIME *                 /*O*/ pStdTime);


#ifdef STDTIME_UNICODE
#define StdTimeStringToStdTime          StdTimeStringWToStdTime
#define StdTimeHexStrToStdTime          StdTimeHexStrWToStdTime
#else
#define StdTimeStringToStdTime          StdTimeStringAToStdTime
#define StdTimeHexStrToStdTime          StdTimeHexStrAToStdTime
#endif /* STDTIME_UNICODE */


/*** StdTimeFields/external conversions **************************************/


STDTIME_RC                  StdTimeFieldsToStdTimeStringA (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_STRINGA *         /*O*/ pStdTimeString);

STDTIME_RC                  StdTimeFieldsToStdTimeStringW (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_STRINGW *         /*O*/ pStdTimeString);

STDTIME_RC                  StdTimeFieldsToStdTimeHexStrA (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_HEXSTRA *         /*O*/ pStdTimeHexStr);

STDTIME_RC                  StdTimeFieldsToStdTimeHexStrW (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_HEXSTRW *         /*O*/ pStdTimeHexStr);


#ifdef STDTIME_UNICODE
#define StdTimeFieldsToStdTimeString StdTimeFieldsToStdTimeStringW
#define StdTimeFieldsToStdTimeHexStr StdTimeFieldsToStdTimeHexStrW
#else
#define StdTimeFieldsToStdTimeString StdTimeFieldsToStdTimeStringA
#define StdTimeFieldsToStdTimeHexStr StdTimeFieldsToStdTimeHexStrA
#endif /* STDTIME_UNICODE */


/*** external/StdTimeFields conversions **************************************/


STDTIME_RC                  StdTimeStringAToStdTimeFields (
  const STDTIME_STRINGA *   /*I*/ pStdTimeString,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);

STDTIME_RC                  StdTimeStringWToStdTimeFields (
  const STDTIME_STRINGW *   /*I*/ pStdTimeString,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);

STDTIME_RC                  StdTimeHexStrAToStdTimeFields (
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStr,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);

STDTIME_RC                  StdTimeHexStrWToStdTimeFields (
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStr,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


#ifdef STDTIME_UNICODE
#define StdTimeStringToStdTimeFields    StdTimeStringWToStdTimeFields
#define StdTimeHexStrToStdTimeFields    StdTimeHexStrWToStdTimeFields
#else
#define StdTimeStringToStdTimeFields    StdTimeStringAToStdTimeFields
#define StdTimeHexStrToStdTimeFields    StdTimeHexStrAToStdTimeFields
#endif /* STDTIME_UNICODE */


/*** StdTimeString/StdTimeHexStr conversions *********************************/


STDTIME_RC                  StdTimeStringAToStdTimeHexStrA (
  const STDTIME_STRINGA *   /*I*/ pStdTimeString,
  STDTIME_HEXSTRA *         /*O*/ pStdTimeHexStr);

STDTIME_RC                  StdTimeStringWToStdTimeHexStrW (
  const STDTIME_STRINGW *   /*I*/ pStdTimeString,
  STDTIME_HEXSTRW *         /*O*/ pStdTimeHexStr);

STDTIME_RC                  StdTimeHexStrAToStdTimeStringA (
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStr,
  STDTIME_STRINGA *         /*O*/ pStdTimeString);

STDTIME_RC                  StdTimeHexStrWToStdTimeStringW (
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStr,
  STDTIME_STRINGW *         /*O*/ pStdTimeString);


#define StdTimeStringToStdTimeHexStrW StdTimeStringWToStdTimeHexStrW
#define StdTimeHexStrToStdTimeStringW StdTimeHexStrWToStdTimeStringW

#define StdTimeStringToStdTimeHexStrA StdTimeStringAToStdTimeHexStrA
#define StdTimeHexStrToStdTimeStringA StdTimeHexStrAToStdTimeStringA


#ifdef STDTIME_UNICODE
#define StdTimeStringToStdTimeHexStr StdTimeStringWToStdTimeHexStrW
#define StdTimeHexStrToStdTimeString StdTimeHexStrWToStdTimeStringW
#else
#define StdTimeStringToStdTimeHexStr StdTimeStringAToStdTimeHexStrA
#define StdTimeHexStrToStdTimeString StdTimeHexStrAToStdTimeStringA
#endif /* STDTIME_UNICODE */


/*** StdTime to/from Local ***************************************************/


STDTIME_RC                  StdTimeToLocalStdTime (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME *                 /*O*/ pStdTimeLocal);

STDTIME_RC                  LocalStdTimeToStdTime (
  const STDTIME *           /*I*/ pStdTimeLocal,
  STDTIME *                 /*O*/ pStdTime);


/*** StdTimeFields to/from Local *********************************************/


STDTIME_RC                  StdTimeFieldsToLocalStdTimeFields (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_FIELDS *          /*O*/ pStdTimeFieldsLocal);

STDTIME_RC                  LocalStdTimeFieldsToStdTimeFields (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFieldsLocal,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** StdTimeString to/from Local *********************************************/


STDTIME_RC                  StdTimeStringAToLocalStdTimeStringA (
  const STDTIME_STRINGA *   /*I*/ pStdStdTimeString,
  STDTIME_STRINGA *         /*O*/ pLocStdTimeString);

STDTIME_RC                  StdTimeStringWToLocalStdTimeStringW (
  const STDTIME_STRINGW *   /*I*/ pStdStdTimeString,
  STDTIME_STRINGW *         /*O*/ pLocStdTimeString);

STDTIME_RC                  LocalStdTimeStringAToStdTimeStringA (
  const STDTIME_STRINGA *   /*I*/ pLocStdTimeString,
  STDTIME_STRINGA *         /*O*/ pStdStdTimeString);

STDTIME_RC                  LocalStdTimeStringWToStdTimeStringW (
  const STDTIME_STRINGW *   /*I*/ pLocStdTimeString,
  STDTIME_STRINGW *         /*O*/ pStdStdTimeString);


#define StdTimeStringToLocalStdTimeStringW StdTimeStringWToLocalStdTimeStringW
#define LocalStdTimeStringToStdTimeStringW LocalStdTimeStringWToStdTimeStringW

#define StdTimeStringToLocalStdTimeStringA StdTimeStringAToLocalStdTimeStringA
#define LocalStdTimeStringToStdTimeStringA LocalStdTimeStringAToStdTimeStringA


#ifdef STDTIME_UNICODE
#define StdTimeStringToLocalStdTimeString StdTimeStringWToLocalStdTimeStringW
#define LocalStdTimeStringToStdTimeString LocalStdTimeStringWToStdTimeStringW
#else
#define StdTimeStringToLocalStdTimeString StdTimeStringAToLocalStdTimeStringA
#define LocalStdTimeStringToStdTimeString LocalStdTimeStringAToStdTimeStringA
#endif /* STDTIME_UNICODE */


/*** StdTimeHexStr to/from Local *********************************************/


STDTIME_RC                  StdTimeHexStrAToLocalStdTimeHexStrA (
  const STDTIME_HEXSTRA *   /*I*/ pStdStdTimeHexStr,
  STDTIME_HEXSTRA *         /*O*/ pLocStdTimeHexStr);

STDTIME_RC                  StdTimeHexStrWToLocalStdTimeHexStrW (
  const STDTIME_HEXSTRW *   /*I*/ pStdStdTimeHexStr,
  STDTIME_HEXSTRW *         /*O*/ pLocStdTimeHexStr);

STDTIME_RC                  LocalStdTimeHexStrAToStdTimeHexStrA (
  const STDTIME_HEXSTRA *   /*I*/ pLocStdTimeHexStr,
  STDTIME_HEXSTRA *         /*O*/ pStdStdTimeHexStr);

STDTIME_RC                  LocalStdTimeHexStrWToStdTimeHexStrW (
  const STDTIME_HEXSTRW *   /*I*/ pLocStdTimeHexStr,
  STDTIME_HEXSTRW *         /*O*/ pStdStdTimeHexStr);


#define StdTimeHexStrToLocalStdTimeHexStrW StdTimeHexStrWToLocalStdTimeHexStrW
#define LocalStdTimeHexStrToStdTimeHexStrW LocalStdTimeHexStrWToStdTimeHexStrW

#define StdTimeHexStrToLocalStdTimeHexStrA StdTimeHexStrAToLocalStdTimeHexStrA
#define LocalStdTimeHexStrToStdTimeHexStrA LocalStdTimeHexStrAToStdTimeHexStrA


#ifdef STDTIME_UNICODE
#define StdTimeHexStrToLocalStdTimeHexStr StdTimeHexStrWToLocalStdTimeHexStrW
#define LocalStdTimeHexStrToStdTimeHexStr LocalStdTimeHexStrWToStdTimeHexStrW
#else
#define StdTimeHexStrToLocalStdTimeHexStr StdTimeHexStrAToLocalStdTimeHexStrA
#define LocalStdTimeHexStrToStdTimeHexStr LocalStdTimeHexStrAToStdTimeHexStrA
#endif /* STDTIME_UNICODE */


/*** Get (current UTC/GMT time) functions ************************************/


STDTIME_RC                  GetStdTime (
  STDTIME *                 /*O*/ pStdTime);

STDTIME_RC                  GetStdTimeFields (
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);

STDTIME_RC                  GetStdTimeStringA (
  STDTIME_STRINGA *         /*O*/ pStdTimeString);

STDTIME_RC                  GetStdTimeStringW (
  STDTIME_STRINGW *         /*O*/ pStdTimeString);

STDTIME_RC                  GetStdTimeHexStrA (
  STDTIME_HEXSTRA *         /*O*/ pStdTimeHexStr);

STDTIME_RC                  GetStdTimeHexStrW (
  STDTIME_HEXSTRW *         /*O*/ pStdTimeHexStr);


#ifdef STDTIME_UNICODE
#define GetStdTimeString    GetStdTimeStringW
#define GetStdTimeHexStr    GetStdTimeHexStrW
#else
#define GetStdTimeString    GetStdTimeStringA
#define GetStdTimeHexStr    GetStdTimeHexStrA
#endif /* STDTIME_UNICODE */


/*** GetLocal (current time) functions ***************************************/


STDTIME_RC                  GetLocalStdTime (
  STDTIME *                 /*O*/ pStdTime);

STDTIME_RC                  GetLocalStdTimeFields (
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);

STDTIME_RC                  GetLocalStdTimeStringA (
  STDTIME_STRINGA *         /*O*/ pStdTimeString);

STDTIME_RC                  GetLocalStdTimeStringW (
  STDTIME_STRINGW *         /*O*/ pStdTimeString);

STDTIME_RC                  GetLocalStdTimeHexStrA (
  STDTIME_HEXSTRA *         /*O*/ pStdTimeHexStr);

STDTIME_RC                  GetLocalStdTimeHexStrW (
  STDTIME_HEXSTRW *         /*O*/ pStdTimeHexStr);


#ifdef STDTIME_UNICODE
#define GetLocalStdTimeString GetLocalStdTimeStringW
#define GetLocalStdTimeHexStr GetLocalStdTimeHexStrW
#else
#define GetLocalStdTimeString GetLocalStdTimeStringA
#define GetLocalStdTimeHexStr GetLocalStdTimeHexStrA
#endif /* STDTIME_UNICODE */


/*** validation functions ****************************************************/


STDTIME_RC                  ValidStdTime (
  const STDTIME *           /*I*/ pStdTime);

STDTIME_RC                  ValidStdTimeFields (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields);

STDTIME_RC                  ValidStdTimeStringA (
  const STDTIME_STRINGA *   /*I*/ pStdTimeString);

STDTIME_RC                  ValidStdTimeStringW (
  const STDTIME_STRINGW *   /*I*/ pStdTimeString);

STDTIME_RC                  ValidStdTimeHexStrA (
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStr);

STDTIME_RC                  ValidStdTimeHexStrW (
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStr);

STDTIME_RC                  ValidStdTimeDelta (
  const STDTIME_DELTA *     /*I*/ pDelta);

STDTIME_RC                  ValidStdTimeSpan (
  const STDTIME_SPAN *      /*I*/ pSpan);


#ifdef STDTIME_UNICODE
#define ValidStdTimeString  ValidStdTimeStringW
#define ValidStdTimeHexStr  ValidStdTimeHexStrW
#else
#define ValidStdTimeString  ValidStdTimeStringA
#define ValidStdTimeHexStr  ValidStdTimeHexStrA
#endif /* STDTIME_UNICODE */


/*** Format functions ********************************************************/


STDTIME_RC                  FormatStdTimeA (
  char *                    /*O*/ pTarget,
  size_t                    /*I*/ nMaxsize,
  const char *              /*I*/ pFormat,
  const STDTIME *           /*I*/ pStdTime);


STDTIME_RC                  FormatStdTimeW (
  STDTIME_WCHAR *           /*O*/ pTarget,
  size_t                    /*I*/ nMaxsize,
  const STDTIME_WCHAR *     /*I*/ pFormat,
  const STDTIME *           /*I*/ pStdTime);


STDTIME_RC                  FormatStdTimeFieldsA (
  char *                    /*O*/ pTarget,
  size_t                    /*I*/ nMaxsize,
  const char *              /*I*/ pFormat,
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields);


STDTIME_RC                  FormatStdTimeFieldsW (
  STDTIME_WCHAR *           /*O*/ pTarget,
  size_t                    /*I*/ nMaxsize,
  const STDTIME_WCHAR *     /*I*/ pFormat,
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields);


STDTIME_RC                  FormatStdTimeStringA (
  char *                    /*O*/ pTarget,
  size_t                    /*I*/ nMaxsize,
  const char *              /*I*/ pFormat,
  const STDTIME_STRINGA *   /*I*/ pStdTimeString);


STDTIME_RC                  FormatStdTimeStringW (
  STDTIME_WCHAR *           /*O*/ pTarget,
  size_t                    /*I*/ nMaxsize,
  const STDTIME_WCHAR *     /*I*/ pFormat,
  const STDTIME_STRINGW *   /*I*/ pStdTimeString);


STDTIME_RC                  FormatStdTimeHexStrA (
  char *                    /*O*/ pTarget,
  size_t                    /*I*/ nMaxsize,
  const char *              /*I*/ pFormat,
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStr);


STDTIME_RC                  FormatStdTimeHexStrW (
  STDTIME_WCHAR *           /*O*/ pTarget,
  size_t                    /*I*/ nMaxsize,
  const STDTIME_WCHAR *     /*I*/ pFormat,
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStr);


STDTIME_RC                  TrimStdTimeStringA (
  STDTIME_STRINGA *         /*IO*/ pStdTimeString,
  int32_t                   /*I*/ nSize);


STDTIME_RC                  TrimStdTimeStringW (
  STDTIME_STRINGW *         /*IO*/ pStdTimeString,
  int32_t                   /*I*/ nSize);


STDTIME_RC                  TruncStdTimeStringA (
  STDTIME_STRINGA *         /*IO*/ pStdTimeString,
  int32_t                   /*I*/ nSize);


STDTIME_RC                  TruncStdTimeStringW (
  STDTIME_STRINGW *         /*IO*/ pStdTimeString,
  int32_t                   /*I*/ nSize);


#ifdef STDTIME_UNICODE
#define FormatStdTime       FormatStdTimeW
#define FormatStdTimeFields FormatStdTimeFieldsW
#define FormatStdTimeString FormatStdTimeStringW
#define FormatStdTimeHexStr FormatStdTimeHexStrW

#define TrimStdTimeString   TrimStdTimeStringW
#define TruncStdTimeString  TruncStdTimeStringW

#else
#define FormatStdTime       FormatStdTimeA
#define FormatStdTimeFields FormatStdTimeFieldsA
#define FormatStdTimeString FormatStdTimeStringA
#define FormatStdTimeHexStr FormatStdTimeHexStrA

#define TrimStdTimeString   TrimStdTimeStringA
#define TruncStdTimeString  TruncStdTimeStringA

#endif /* STDTIME_UNICODE */


/*** delimiter functions *****************************************************/


STDTIME_RC                  SetStdTimeStringDelimitersA (
  const char *              /*I*/ pDelimiters);

STDTIME_RC                  SetStdTimeStringDelimitersW (
  const STDTIME_WCHAR *     /*I*/ pDelimiters);

STDTIME_RC                  RepairStdTimeStringA (
  STDTIME_STRINGA *         /*O*/ pStdTimeString);

STDTIME_RC                  RepairStdTimeStringW (
  STDTIME_STRINGW *         /*O*/ pStdTimeString);

STDTIME_RC                  DelimitStdTimeStringA (
  STDTIME_STRINGA *         /*O*/ pStdTimeString,
  const char *              /*I*/ pDelim);

STDTIME_RC                  DelimitStdTimeStringW (
  STDTIME_STRINGW *         /*O*/ pStdTimeString,
  const STDTIME_WCHAR *     /*I*/ pDelim);


#ifdef STDTIME_UNICODE
#define SetStdTimeStringDelimiters      SetStdTimeStringDelimitersW
#define RepairStdTimeString             RepairStdTimeStringW
#define DelimitStdTimeString            DelimitStdTimeStringW
#else
#define SetStdTimeStringDelimiters      SetStdTimeStringDelimitersA
#define RepairStdTimeString             RepairStdTimeStringA
#define DelimitStdTimeString            DelimitStdTimeStringA
#endif /* STDTIME_UNICODE */


/*** AddFraction adjustment function *****************************************/


STDTIME_RC                  StdTimeFields_AddFraction (
  STDTIME_FIELDS *          /*IO*/ pStdTimeFields,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec);


/*** AddSpan functions *******************************************************/


STDTIME_RC                  StdTime_AddSpan (
  STDTIME *                 /*IO*/ pStdTime,
  const STDTIME_SPAN *      /*I*/  pSpan);

STDTIME_RC                  StdTimeFields_AddSpan (
  STDTIME_FIELDS *          /*IO*/ pStdTimeFields,
  const STDTIME_SPAN *      /*I*/  pSpan);

STDTIME_RC                  StdTimeStringA_AddSpan (
  STDTIME_STRINGA *         /*IO*/ pStdTimeString,
  const STDTIME_SPAN *      /*I*/  pSpan);

STDTIME_RC                  StdTimeStringW_AddSpan (
  STDTIME_STRINGW *         /*IO*/ pStdTimeString,
  const STDTIME_SPAN *      /*I*/  pSpan);

STDTIME_RC                  StdTimeHexStrA_AddSpan (
  STDTIME_HEXSTRA *         /*IO*/ pStdTimeHexStr,
  const STDTIME_SPAN *      /*I*/  pSpan);

STDTIME_RC                  StdTimeHexStrW_AddSpan (
  STDTIME_HEXSTRW *         /*IO*/ pStdTimeHexStr,
  const STDTIME_SPAN *      /*I*/  pSpan);


#ifdef STDTIME_UNICODE
#define StdTimeString_AddSpan       StdTimeStringW_AddSpan
#define StdTimeHexStr_AddSpan       StdTimeHexStrW_AddSpan
#else
#define StdTimeString_AddSpan       StdTimeStringA_AddSpan
#define StdTimeHexStr_AddSpan       StdTimeHexStrA_AddSpan
#endif /* STDTIME_UNICODE */


/*** SubSpan functions *******************************************************/


STDTIME_RC                  StdTime_SubSpan (
  STDTIME *                 /*IO*/ pStdTime,
  const STDTIME_SPAN *      /*I*/  pSpan);

STDTIME_RC                  StdTimeFields_SubSpan (
  STDTIME_FIELDS *          /*IO*/ pStdTimeFields,
  const STDTIME_SPAN *      /*I*/  pSpan);

STDTIME_RC                  StdTimeStringA_SubSpan (
  STDTIME_STRINGA *         /*IO*/ pStdTimeString,
  const STDTIME_SPAN *      /*I*/  pSpan);

STDTIME_RC                  StdTimeStringW_SubSpan (
  STDTIME_STRINGW *         /*IO*/ pStdTimeString,
  const STDTIME_SPAN *      /*I*/  pSpan);

STDTIME_RC                  StdTimeHexStrA_SubSpan (
  STDTIME_HEXSTRA *         /*IO*/ pStdTimeHexStr,
  const STDTIME_SPAN *      /*I*/  pSpan);

STDTIME_RC                  StdTimeHexStrW_SubSpan (
  STDTIME_HEXSTRW *         /*IO*/ pStdTimeHexStr,
  const STDTIME_SPAN *      /*I*/  pSpan);


#ifdef STDTIME_UNICODE
#define StdTimeString_SubSpan       StdTimeStringW_SubSpan
#define StdTimeHexStr_SubSpan       StdTimeHexStrW_SubSpan
#else
#define StdTimeString_SubSpan       StdTimeStringA_SubSpan
#define StdTimeHexStr_SubSpan       StdTimeHexStrA_SubSpan
#endif /* STDTIME_UNICODE */


/*** GetSpan functions *******************************************************/


STDTIME_RC                  StdTime_GetSpan (
  const STDTIME *           /*I*/ pStdTimeOne,
  const STDTIME *           /*I*/ pStdTimeTwo,
  STDTIME_SPAN *            /*O*/ pSpan);

STDTIME_RC                  StdTimeFields_GetSpan (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFieldsOne,
  const STDTIME_FIELDS *    /*I*/ pStdTimeFieldsTwo,
  STDTIME_SPAN *            /*O*/ pSpan);

STDTIME_RC                  StdTimeStringA_GetSpan (
  const STDTIME_STRINGA *   /*I*/ pStdTimeStringOne,
  const STDTIME_STRINGA *   /*I*/ pStdTimeStringTwo,
  STDTIME_SPAN *            /*O*/ pSpan);

STDTIME_RC                  StdTimeStringW_GetSpan (
  const STDTIME_STRINGW *   /*I*/ pStdTimeStringOne,
  const STDTIME_STRINGW *   /*I*/ pStdTimeStringTwo,
  STDTIME_SPAN *            /*O*/ pSpan);

STDTIME_RC                  StdTimeHexStrA_GetSpan (
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStrOne,
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStrTwo,
  STDTIME_SPAN *            /*O*/ pSpan);

STDTIME_RC                  StdTimeHexStrW_GetSpan (
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStrOne,
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStrTwo,
  STDTIME_SPAN *            /*O*/ pSpan);


#ifdef STDTIME_UNICODE
#define StdTimeString_GetSpan       StdTimeStringW_GetSpan
#define StdTimeHexStr_GetSpan       StdTimeHexStrW_GetSpan
#else
#define StdTimeString_GetSpan       StdTimeStringA_GetSpan
#define StdTimeHexStr_GetSpan       StdTimeHexStrA_GetSpan
#endif /* STDTIME_UNICODE */


/*** AddDelta functions ******************************************************/

STDTIME_RC                  StdTime_AddDelta (
  STDTIME *                 /*IO*/ pStdTime,
  const STDTIME_DELTA *     /*I*/  pDelta);

STDTIME_RC                  StdTimeFields_AddDelta (
  STDTIME_FIELDS *          /*IO*/ pStdTimeFields,
  const STDTIME_DELTA *     /*I*/  pDelta);

STDTIME_RC                  StdTimeStringA_AddDelta (
  STDTIME_STRINGA *         /*IO*/ pStdTimeString,
  const STDTIME_DELTA *     /*I*/  pDelta);

STDTIME_RC                  StdTimeStringW_AddDelta (
  STDTIME_STRINGW *         /*IO*/ pStdTimeString,
  const STDTIME_DELTA *     /*I*/  pDelta);

STDTIME_RC                  StdTimeHexStrA_AddDelta (
  STDTIME_HEXSTRA *         /*IO*/ pStdTimeHexStr,
  const STDTIME_DELTA *     /*I*/  pDelta);

STDTIME_RC                  StdTimeHexStrW_AddDelta (
  STDTIME_HEXSTRW *         /*IO*/ pStdTimeHexStr,
  const STDTIME_DELTA *     /*I*/  pDelta);


#ifdef STDTIME_UNICODE
#define StdTimeString_AddDelta      StdTimeStringW_AddDelta
#define StdTimeHexStr_AddDelta      StdTimeHexStrW_AddDelta
#else
#define StdTimeString_AddDelta      StdTimeStringA_AddDelta
#define StdTimeHexStr_AddDelta      StdTimeHexStrA_AddDelta
#endif /* STDTIME_UNICODE */


/*** SubDelta functions ******************************************************/


STDTIME_RC                  StdTime_SubDelta (
  STDTIME *                 /*IO*/ pStdTime,
  const STDTIME_DELTA *     /*I*/  pDelta);

STDTIME_RC                  StdTimeFields_SubDelta (
  STDTIME_FIELDS *          /*IO*/ pStdTimeFields,
  const STDTIME_DELTA *     /*I*/  pDelta);

STDTIME_RC                  StdTimeStringA_SubDelta (
  STDTIME_STRINGA *         /*IO*/ pStdTimeString,
  const STDTIME_DELTA *     /*I*/  pDelta);

STDTIME_RC                  StdTimeStringW_SubDelta (
  STDTIME_STRINGW *         /*IO*/ pStdTimeString,
  const STDTIME_DELTA *     /*I*/  pDelta);

STDTIME_RC                  StdTimeHexStrA_SubDelta (
  STDTIME_HEXSTRA *         /*IO*/ pStdTimeHexStr,
  const STDTIME_DELTA *     /*I*/  pDelta);

STDTIME_RC                  StdTimeHexStrW_SubDelta (
  STDTIME_HEXSTRW *         /*IO*/ pStdTimeHexStr,
  const STDTIME_DELTA *     /*I*/  pDelta);


#ifdef STDTIME_UNICODE
#define StdTimeString_SubDelta      StdTimeStringW_SubDelta
#define StdTimeHexStr_SubDelta      StdTimeHexStrW_SubDelta
#else
#define StdTimeString_SubDelta      StdTimeStringA_SubDelta
#define StdTimeHexStr_SubDelta      StdTimeHexStrA_SubDelta
#endif /* STDTIME_UNICODE */


/*** GetDelta functions ******************************************************/


STDTIME_RC                  StdTime_GetDelta (
  const STDTIME *           /*I*/ pStdTimeOne,
  const STDTIME *           /*I*/ pStdTimeTwo,
  STDTIME_DELTA *           /*O*/ pDelta);

STDTIME_RC                  StdTimeFields_GetDelta (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFieldsOne,
  const STDTIME_FIELDS *    /*I*/ pStdTimeFieldsTwo,
  STDTIME_DELTA *           /*O*/ pDelta);

STDTIME_RC                  StdTimeStringA_GetDelta (
  const STDTIME_STRINGA *   /*I*/ pStdTimeStringOne,
  const STDTIME_STRINGA *   /*I*/ pStdTimeStringTwo,
  STDTIME_DELTA *           /*O*/ pDelta);

STDTIME_RC                  StdTimeStringW_GetDelta (
  const STDTIME_STRINGW *   /*I*/ pStdTimeStringOne,
  const STDTIME_STRINGW *   /*I*/ pStdTimeStringTwo,
  STDTIME_DELTA *           /*O*/ pDelta);

STDTIME_RC                  StdTimeHexStrA_GetDelta (
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStrOne,
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStrTwo,
  STDTIME_DELTA *           /*O*/ pDelta);

STDTIME_RC                  StdTimeHexStrW_GetDelta (
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStrOne,
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStrTwo,
  STDTIME_DELTA *           /*O*/ pDelta);


#ifdef STDTIME_UNICODE
#define StdTimeString_GetDelta      StdTimeStringW_GetDelta
#define StdTimeHexStr_GetDelta      StdTimeHexStrW_GetDelta
#else
#define StdTimeString_GetDelta      StdTimeStringA_GetDelta
#define StdTimeHexStr_GetDelta      StdTimeHexStrA_GetDelta
#endif /* STDTIME_UNICODE */


/*** Delta/Span conversion functions *****************************************/


STDTIME_RC                  StdTimeDeltaToStdTimeSpan (
  const STDTIME_DELTA *     /*I*/ pDelta,
  STDTIME_SPAN *            /*O*/ pSpan);

STDTIME_RC                  StdTimeSpanToStdTimeDelta (
  const STDTIME_SPAN *      /*I*/ pSpan,
  STDTIME_DELTA *           /*O*/ pDelta);


/*** Delta/Span sign-related functions ***************************************/


int32_t                     SgnStdTimeDelta (
  const STDTIME_DELTA *     /*I*/ pDelta);

STDTIME_RC                  AbsStdTimeDelta (
  STDTIME_DELTA *           /*IO*/ pDelta);

STDTIME_RC                  NegStdTimeDelta (
  STDTIME_DELTA *           /*IO*/ pDelta);


int32_t                     SgnStdTimeSpan (
  const STDTIME_SPAN *      /*I*/ pSpan);

STDTIME_RC                  AbsStdTimeSpan (
  STDTIME_SPAN *            /*IO*/ pSpan);

STDTIME_RC                  NegStdTimeSpan (
  STDTIME_SPAN *            /*IO*/ pSpan);


/*** Compare functions *******************************************************/


int32_t                     CompareStdTime (
  const STDTIME *           /*I*/ pStdTimeOne,
  const STDTIME *           /*I*/ pStdTimeTwo);

int32_t                     CompareStdTimeFields (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFieldsOne,
  const STDTIME_FIELDS *    /*I*/ pStdTimeFieldsTwo);

int32_t                     CompareStdTimeStringA (
  const STDTIME_STRINGA *   /*I*/ pStdTimeStringOne,
  const STDTIME_STRINGA *   /*I*/ pStdTimeStringTwo);

int32_t                     CompareStdTimeStringW (
  const STDTIME_STRINGW *   /*I*/ pStdTimeStringOne,
  const STDTIME_STRINGW *   /*I*/ pStdTimeStringTwo);

int32_t                     CompareStdTimeHexStrA (
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStrOne,
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStrTwo);

int32_t                     CompareStdTimeHexStrW (
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStrOne,
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStrTwo);


#ifdef STDTIME_UNICODE
#define CompareStdTimeString CompareStdTimeStringW
#define CompareStdTimeHexStr CompareStdTimeHexStrW
#else
#define CompareStdTimeString CompareStdTimeStringA
#define CompareStdTimeHexStr CompareStdTimeHexStrA
#endif /* STDTIME_UNICODE */


/*** FileTime functions ******************************************************/


STDTIME_RC                  StdTimeToFileTime (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_FILETIME *    /*O*/ pFileTime);


STDTIME_RC                  FileTimeToStdTime (
  const STDTIME_WIN_FILETIME *  /*I*/ pFileTime,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToFileTime (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_FILETIME *    /*O*/ pFileTime);


STDTIME_RC                  FileTimeToStdTimeFields (
  const STDTIME_WIN_FILETIME *  /*I*/ pFileTime,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


STDTIME_RC                  StdTimeHexStrAToFileTime (
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStr,
  STDTIME_WIN_FILETIME *    /*O*/ pFileTime);


STDTIME_RC                  StdTimeHexStrWToFileTime (
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStr,
  STDTIME_WIN_FILETIME *    /*O*/ pFileTime);


STDTIME_RC                  FileTimeToStdTimeHexStrA (
  const STDTIME_WIN_FILETIME *  /*I*/ pFileTime,
  STDTIME_HEXSTRA *         /*O*/ pStdTimeHexStr);


STDTIME_RC                  FileTimeToStdTimeHexStrW (
  const STDTIME_WIN_FILETIME *  /*I*/ pFileTime,
  STDTIME_HEXSTRW *         /*O*/ pStdTimeHexStr);


#ifdef STDTIME_UNICODE
#define StdTimeHexStrToFileTime StdTimeHexStrWToFileTime
#define FileTimeToStdTimeHexStr FileTimeToStdTimeHexStrW
#else
#define StdTimeHexStrToFileTime StdTimeHexStrAToFileTime
#define FileTimeToStdTimeHexStr FileTimeToStdTimeHexStrA
#endif /* STDTIME_UNICODE */


/*** SystemTimeEx functions **************************************************/


STDTIME_RC                  StdTimeToSystemTimeEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_SYSTEMTIME *  /*O*/ pSystemTime,
  int32_t *                 /*O*/ pUsec, /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  SystemTimeExToStdTime (
  const STDTIME_WIN_SYSTEMTIME * /*I*/ pSystemTime,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToSystemTimeEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_SYSTEMTIME *  /*O*/ pSystemTime,
  int32_t *                 /*O*/ pUsec, /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  SystemTimeExToStdTimeFields (
  const STDTIME_WIN_SYSTEMTIME * /*I*/ pSystemTime,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** SystemTime functions ****************************************************/


STDTIME_RC                  StdTimeToSystemTime (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_SYSTEMTIME *  /*O*/ pSystemTime);


STDTIME_RC                  SystemTimeToStdTime (
  const STDTIME_WIN_SYSTEMTIME * /*I*/ pSystemTime,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToSystemTime (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_SYSTEMTIME *  /*O*/ pSystemTime);


STDTIME_RC                  SystemTimeToStdTimeFields (
  const STDTIME_WIN_SYSTEMTIME * /*I*/ pSystemTime,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** Udate functions *********************************************************/


STDTIME_RC                  StdTimeToUdateEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_UDATE *       /*O*/ pUdate,
  int32_t *                 /*O*/ pUsec,
  int32_t *                 /*O*/ pNsec);


STDTIME_RC                  UdateExToStdTime (
  const STDTIME_WIN_UDATE * /*I*/ pUdate,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToUdateEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_UDATE *       /*O*/ pUdate,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  UdateExToStdTimeFields (
  const STDTIME_WIN_UDATE * /*I*/ pUdate,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


STDTIME_RC                  StdTimeToUdate (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_UDATE *       /*O*/ pUdate);


STDTIME_RC                  UdateToStdTime (
  const STDTIME_WIN_UDATE * /*I*/ pUdate,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToUdate (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_UDATE *       /*O*/ pUdate);


STDTIME_RC                  UdateToStdTimeFields (
  const STDTIME_WIN_UDATE * /*I*/ pUdate,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** DbTimeStamp functions ***************************************************/


STDTIME_RC                  StdTimeToDbTimeStamp (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DBTIMESTAMP * /*O*/ pDbTimeStamp);


STDTIME_RC                  DbTimeStampToStdTime (
  const STDTIME_WIN_DBTIMESTAMP * /*I*/ pDbTimeStamp,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToDbTimeStamp (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DBTIMESTAMP * /*O*/ pDbTimeStamp);


STDTIME_RC                  DbTimeStampToStdTimeFields (
  const STDTIME_WIN_DBTIMESTAMP * /*I*/ pDbTimeStamp,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** StructTmEx functions ****************************************************/


STDTIME_RC                  StdTimeToStructTmEx (
  const STDTIME *           /*I*/ pStdTime,
  struct tm *               /*O*/ pStructTm,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  StructTmExToStdTime (
  const struct tm *         /*I*/ pStructTm,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToStructTmEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  struct tm *               /*O*/ pStructTm,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  StructTmExToStdTimeFields (
  const struct tm *         /*I*/ pStructTm,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** StructTm functions ******************************************************/


STDTIME_RC                  StdTimeToStructTm (
  const STDTIME *           /*I*/ pStdTime,
  struct tm *               /*O*/ pStructTm);


STDTIME_RC                  StructTmToStdTime (
  const struct tm *         /*I*/ pStructTm,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToStructTm (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  struct tm *               /*O*/ pStructTm);


STDTIME_RC                  StructTmToStdTimeFields (
  const struct tm *         /*I*/ pStructTm,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** TimeTypeEx functions ****************************************************/


STDTIME_RC                  StdTimeToTimeTypeEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_TIMETYPE *        /*O*/ pTimeT,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  TimeTypeExToStdTime (
  const STDTIME_TIMETYPE *  /*I*/ pTimeT,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToTimeTypeEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_TIMETYPE *        /*O*/ pTimeT,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  TimeTypeExToStdTimeFields (
  const STDTIME_TIMETYPE *  /*I*/ pTimeT,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** TimeType functions ******************************************************/


STDTIME_RC                  StdTimeToTimeType (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_TIMETYPE *        /*O*/ pTimeT);


STDTIME_RC                  TimeTypeToStdTime (
  const STDTIME_TIMETYPE *  /*I*/ pTimeT,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToTimeType (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_TIMETYPE *        /*O*/ pTimeT);


STDTIME_RC                  TimeTypeToStdTimeFields (
  const STDTIME_TIMETYPE *  /*I*/ pTimeT,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** Constructor-like functions **********************************************/


STDTIME                     StdTime (
  int32_t                   /*I*/ hi,
  int32_t                   /*I*/ lo);


STDTIME_FIELDS              StdTimeFields (
  int32_t                   /*I*/ year,
  int32_t                   /*I*/ mon,
  int32_t                   /*I*/ day,
  int32_t                   /*I*/ hour,
  int32_t                   /*I*/ min,
  int32_t                   /*I*/ sec,
  int32_t                   /*I*/ msec,
  int32_t                   /*I*/ usec,
  int32_t                   /*I*/ nsec);


STDTIME_STRINGA             StdTimeStringA (
  const char *              /*I*/ str);


STDTIME_STRINGW             StdTimeStringW (
  const STDTIME_WCHAR *     /*I*/ str);


STDTIME_HEXSTRA             StdTimeHexStrA (
  const char *              /*I*/ str);


STDTIME_HEXSTRW             StdTimeHexStrW (
  const STDTIME_WCHAR *     /*I*/ str);


#ifdef STDTIME_UNICODE
#define StdTimeString       StdTimeStringW
#define StdTimeHexStr       StdTimeHexStrW
#else
#define StdTimeString       StdTimeStringA
#define StdTimeHexStr       StdTimeHexStrA
#endif /* STDTIME_UNICODE */


STDTIME_DELTA               StdTimeDelta (
  int32_t                   /*I*/ day,
  int32_t                   /*I*/ hour,
  int32_t                   /*I*/ min,
  int32_t                   /*I*/ sec,
  int32_t                   /*I*/ msec,
  int32_t                   /*I*/ usec,
  int32_t                   /*I*/ nsec);


STDTIME_SPAN                StdTimeSpan (
  QUADLIB_I64               /*I*/ value);


/*** Initializer functions ***************************************************/


STDTIME                     ZeroStdTime ();
STDTIME_FIELDS              ZeroStdTimeFields ();
STDTIME_DELTA               ZeroStdTimeDelta ();
STDTIME_SPAN                ZeroStdTimeSpan ();

STDTIME_STRINGA             ZeroStdTimeStringA ();
STDTIME_STRINGW             ZeroStdTimeStringW ();

STDTIME_HEXSTRA             ZeroStdTimeHexStrA ();
STDTIME_HEXSTRW             ZeroStdTimeHexStrW ();

STDTIME_TZOA                ZeroStdTimeTzoA ();
STDTIME_TZOW                ZeroStdTimeTzoW ();

STDTIME_ERRMSGA             ZeroStdTimeErrMsgA ();
STDTIME_ERRMSGW             ZeroStdTimeErrMsgW ();

#ifdef STDTIME_UNICODE
#define ZeroStdTimeString   ZeroStdTimeStringW
#define ZeroStdTimeHexStr   ZeroStdTimeHexStrW
#define ZeroStdTimeTzo      ZeroStdTimeTzoW
#define ZeroStdTimeErrMsg   ZeroStdTimeErrMsgW
#else
#define ZeroStdTimeString   ZeroStdTimeStringA
#define ZeroStdTimeHexStr   ZeroStdTimeHexStrA
#define ZeroStdTimeTzo      ZeroStdTimeTzoA
#define ZeroStdTimeErrMsg   ZeroStdTimeErrMsgA
#endif /* STDTIME_UNICODE */

/* initializers for outside types use 'StdTimeApi' prefix */

STDTIME_TIMETYPE            StdTimeApiZeroTimeType ();
STDTIME_WIN_FILETIME        StdTimeApiZeroFileTime ();
STDTIME_WIN_SYSTEMTIME      StdTimeApiZeroSystemTime ();
STDTIME_WIN_DBTIMESTAMP     StdTimeApiZeroDbTimeStamp ();
STDTIME_WIN_UDATE           StdTimeApiZeroUdate ();
struct tm                   StdTimeApiZeroStructTm ();


/*****************************************************************************/
/*  NORMALIZE, ROUND, TRUNC                                                  */
/*****************************************************************************/


STDTIME_RC                  NormalizeStdTimeDelta (
  STDTIME_DELTA *           /*IO*/ pDelta);


STDTIME_RC                  TruncStdTimeDelta (
  STDTIME_DELTA *           /*IO*/ pDelta,
  int32_t                   /*I*/  field);


STDTIME_RC                  RoundStdTimeDelta (
  STDTIME_DELTA *           /*IO*/ pDelta,
  int32_t                   /*I*/  field);


/*** convenience calendar functions ******************************************/


STDTIME_RC                  StdTimeGetDayofWeekAndYear (
  int32_t                   /*I*/ nYear,
  int32_t                   /*I*/ nMon,
  int32_t                   /*I*/ nDayofMon,
  int32_t *                 /*O*/ pDayofWeek,
  int32_t *                 /*O*/ pDayofYear);


int32_t                     StdTimeYearIsLeap (
  int32_t                   /*I*/ year);


int32_t                     StdTimeDaysInYearMon (
  int32_t                   /*I*/ year,
  int32_t                   /*I*/ mon);


/*** HpDateEx functions ******************************************************/


STDTIME_RC                  StdTimeToHpDateEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  HpDateExToStdTime (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToHpDateEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  HpDateExToStdTimeFields (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** HpDate functions ********************************************************/


STDTIME_RC                  StdTimeToHpDate (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DATE *        /*O*/ pDate);


STDTIME_RC                  HpDateToStdTime (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToHpDate (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DATE *        /*O*/ pDate);


STDTIME_RC                  HpDateToStdTimeFields (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** DateEx functions ********************************************************/


STDTIME_RC                  StdTimeToDateEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  DateExToStdTime (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToDateEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  DateExToStdTimeFields (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** Date functions ***************************************************/


STDTIME_RC                  StdTimeToDate (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DATE *        /*O*/ pDate);


STDTIME_RC                  DateToStdTime (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToDate (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DATE *        /*O*/ pDate);


STDTIME_RC                  DateToStdTimeFields (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** HpVariantEx functions ***************************************************/


STDTIME_RC                  StdTimeToHpVariantEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_VARIANT *     /*O*/ pVariant,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  HpVariantExToStdTime (
  const STDTIME_WIN_VARIANT * /*I*/ pVariant,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToHpVariantEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_VARIANT *     /*O*/ pVariant,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  HpVariantExToStdTimeFields (
  const STDTIME_WIN_VARIANT * /*I*/ pVariant,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** HpVariant functions *****************************************************/


STDTIME_RC                  StdTimeToHpVariant (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_VARIANT *     /*O*/ pVariant);


STDTIME_RC                  HpVariantToStdTime (
  const STDTIME_WIN_VARIANT * /*I*/ pVariant,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToHpVariant (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_VARIANT *     /*O*/ pVariant);


STDTIME_RC                  HpVariantToStdTimeFields (
  const STDTIME_WIN_VARIANT * /*I*/ pVariant,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** VariantEx functions *****************************************************/


STDTIME_RC                  StdTimeToVariantEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_VARIANT *     /*O*/ pVariant,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  VariantExToStdTime (
  const STDTIME_WIN_VARIANT * /*I*/ pVariant,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToVariantEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_VARIANT *     /*O*/ pVariant,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  VariantExToStdTimeFields (
  const STDTIME_WIN_VARIANT * /*I*/ pVariant,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** Variant functions ***************************************************/


STDTIME_RC                  StdTimeToVariant (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_VARIANT *     /*O*/ pVariant);


STDTIME_RC                  VariantToStdTime (
  const STDTIME_WIN_VARIANT * /*I*/ pVariant,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToVariant (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_VARIANT *     /*O*/ pVariant);


STDTIME_RC                  VariantToStdTimeFields (
  const STDTIME_WIN_VARIANT * /*I*/ pVariant,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** TIMEZONE CONVERSION DEFINITIONS *****************************************/


/*****************************************************************************/
/*                                                                           */
/*  Access the timezone database file from Boost.org as a C table.           */
/*  The Boost file is a comma-separated-value (csv) file.  This is similar   */
/*  to a list of strings in an array of char pointers.  However, the last    */
/*  value on each line has no trailing comma.  This causes the C compiler to */
/*  concatenate the last value of one line with the first value of the next  */
/*  line.  This reduces the number of values per line by one, and merges     */
/*  together two unrelated field values.  However, it is desirable to use    */
/*  the Boost file unmodified, so we have to account for this.               */
/*                                                                           */
/*  Each line in the Boost timezone file has 11 fields.  Since field 11 has  */
/*  no trailing comma, when used as a C string-array initializer, field 11   */
/*  of one line is concatenated with field 1 of the next line.               */
/*                                                                           */
/*  To undo this, the following steps are taken:                             */
/*                                                                           */
/*  1.  The first 10 fields (column headings) of the table are ignored.      */
/*                                                                           */
/*  2.  Field 1 is a timezone ID, such as "America/Chicago".  The beginning  */
/*      of a timezone ID may be found by locating the first '/' of a field,  */
/*      then the last uppercase letter that preceded the '/' is the start    */
/*      of the ID field.                                                     */
/*                                                                           */
/*  3.  Field 11 is the DST end time, normally of the format "+00:00:00".    */
/*      If the field starts with '+', '-' or a digit, the end of the field   */
/*      is found by scanning forward until a character that is neither a     */
/*      digit nor ':' is found.                                              */
/*                                                                           */
/*  4.  In terms of C string values, the timezone database file appears as:  */
/*                                                                           */
/*      10: [ column-heading 1 thru column-heading 10 of data line 1 ]       */
/*                                                                           */
/*      1: [ column-heading 11 + field 1       of data line 2 ]              */
/*      9: [ field 2 thru field 10             of data line 2 ]              */
/*                                                                           */
/*      1: [ field 11 of data line 2 + field 1 of data line 3 ]              */
/*      9: [ field 2 thru field 10             of data line 3 ]              */
/*                                                                           */
/*      ...                                                                  */
/*                                                                           */
/*      1: [ field 11 of data line 378 + field 1 of data line 379 ]          */
/*      9: [ field 2 thru field 10               of data line 379 ]          */
/*                                                                           */
/*      1: [ field 11                            of data line 379 ]          */
/*      9: [ dummy field 2 thru dummy field 10   of data line 380 ]          */
/*                                                                           */
/*      It may be seen that the first 10 fields are skipped, and the         */
/*      repeating values are grouped by 10, plus one at the end.             */
/*                                                                           */
/*  5.  By padding the initialization with 9 null strings, a structure       */
/*      containing 10 char pointers can be defined, to make references to    */
/*      to individual fields easier.  The actual number of data lines is     */
/*      2 less than the apparent number.  Example:                           */
/*                                                                           */
/*          380 - (column-heading line) - (dummy last line) = 378            */
/*                                                                           */
/*  6.  The usable array ranges from [1] to [378].  Entry 0 is not used,     */
/*      and entry 379 is only used to grab the DST END TIME for entry 378.   */
/*                                                                           */
/*  6.  The field that has the combined value of field 11 + field 1 is       */
/*      called the 'merged' field, and must be split apart to get 1 and 11.  */
/*                                                                           */
/*  7.  Field 1 would have been the ID, and field 11 would have been the     */
/*      DST END TIME if the merging had not taken place.                     */
/*                                                                           */
/*  8.  The numbers 378, 379, 380 above are only example values in effect    */
/*      when this code was written, and are subject to change.               */
/*                                                                           */
/*  9.  The above considerations apply only if the file is merged, as        */
/*      indicated by the STDTIME_MERGED_CSV define.  if it is unmerged,      */
/*      the file looks like a simple list of strings and is accessed         */
/*      accordingly, without having to parse and unmerge any fields.         */
/*                                                                           */
/*****************************************************************************/


enum
  {
  STDTIME_TZ_MERGED,                /* field 11+1 */
  STDTIME_TZ_STD_ABBR,              /* field 2 */
  STDTIME_TZ_STD_NAME,              /* field 3 */
  STDTIME_TZ_DST_ABBR,              /* field 4 */
  STDTIME_TZ_DST_NAME,              /* field 5 */
  STDTIME_TZ_GMT_TO_LOC_OFFSET,     /* field 6 */
  STDTIME_TZ_STD_TO_DST_OFFSET,     /* field 7 */
  STDTIME_TZ_DST_START_RULE,        /* field 8 */
  STDTIME_TZ_DST_START_TIME,        /* field 9 */
  STDTIME_TZ_DST_END_RULE,          /* field 10 */
  STDTIME_TZ_FIELD_COUNT,           /* value of 10 */

  STDTIME_TZ_ID                     = STDTIME_TZ_MERGED,        /* field 1 */
  STDTIME_TZ_DST_END_TIME           = STDTIME_TZ_FIELD_COUNT    /* field 11 */
  };


typedef struct
  {

#ifdef STDTIME_MERGED_CSV
  char *                    pField [STDTIME_TZ_FIELD_COUNT];
#else
  char *                    pField [STDTIME_TZ_FIELD_COUNT+1];
#endif

  }
STDTIME_TZ_DEF;


/* if the csv file is merged, we have to create a dummy last line */
/* and STDTIME_TZ_LINE_COUNT must not count that.  if the file is unmerged */
/* there is no dummy line */


#ifdef STDTIME_MERGED_CSV
#define STDTIME_TZ_LINE_COUNT                                                 \
  ((sizeof(Pvt_StdTimeTz_Def) / sizeof(Pvt_StdTimeTz_Def[0])) - 1)         /**/
#else
#define STDTIME_TZ_LINE_COUNT                                                 \
  (sizeof(Pvt_StdTimeTz_Def) / sizeof(Pvt_StdTimeTz_Def[0]))               /**/
#endif


#define STDTIME_TZ_LINE_MAX     (STDTIME_TZ_LINE_COUNT-1)

#define STDTIME_TZ_FLD_SIZE     40      /* max width of any field */
#define STDTIME_TZ_FLD_MAX      (STDTIME_TZ_FLD_SIZE-1)

#define STDTIME_TZ_ABBR_SIZE    12      /* max width of a zone abbr */
#define STDTIME_TZ_ABBR_MAX     (STDTIME_TZ_ABBR_SIZE-1)

/* first field of STDTIME_TZTRAN renamed from pZoneAbbr to pZoneAlias */
/* to make it more generic, and to support Windows timezone names without */
/* making yet another struct definition. */

typedef struct
  {
  char *                    pZoneAlias;
  char *                    pZoneID;
  }
STDTIME_TZTRAN;

#define STDTIME_TZ_RULE_LAST    5
#define STDTIME_TZ_RULE_EXACT   6
#define STDTIME_TZ_RULE_LBOUND  7
#define STDTIME_TZ_RULE_MAX_DAY_ORDINAL 7

/*****************************************************************************/
/*  structure to define day of year when a STD/DST transition occurs         */
/*****************************************************************************/

typedef struct
  {
  int32_t                   dayOrdinal;     /* 1:4 = 1st to 4th, 5 = last    */
                                            /* 6 = exact, 7 = lower bound    */

  int32_t                   dayOfWeek;      /* 0:6  = Sun:Sat                */
  int32_t                   mon;            /* 1:12 = Jan:Dec                */
  int32_t                   dayOfMonth;     /* if exact day, or lower bound  */
  }
STDTIME_TZ_RULE;

/*****************************************************************************/
/*  structure to define TZ time value or time offset.                        */
/*  if sign == 0, other fields are zero.                                     */
/*  hour, min, sec are always >= 0.                                          */
/*****************************************************************************/

typedef struct
  {
  int32_t                   sign;           /* +1, 0 or -1 */
  int32_t                   hour;
  int32_t                   min;
  int32_t                   sec;
  }
STDTIME_TZ_TIME;


typedef struct
  {
  char                      zoneID  [STDTIME_TZ_FLD_SIZE];
  char                      stdAbbr [STDTIME_TZ_ABBR_SIZE];
  char                      dstAbbr [STDTIME_TZ_ABBR_SIZE];

  STDTIME_TZ_TIME           gmtToLocOffset;
    /* add this value to GMT to get LOC time */

  STDTIME_TZ_TIME           stdToDstOffset;
    /* add this value to STD to get DST time */

  STDTIME_TZ_RULE           dstStartRule;
    /* day of year when DST starts */

  STDTIME_TZ_TIME           dstStartTime;
    /* time of day when DST starts */

  STDTIME_TZ_RULE           dstEndRule;
    /* day of year when DST ends */

  STDTIME_TZ_TIME           dstEndTime;
    /* time of day when DST ends */

  STDTIME_BOOL              dstInEffect;
    /* set to STDTIME_TRUE  if fall-back transition hour is DST */
    /* set to STDTIME_FALSE if fall-back transition hour is STD */
  }
STDTIMEZONE_INFO;

#define STDTIMEZONE_INFO_ZERO {"","","",{0},{0},{0},{0},{0},{0},0}


/*****************************************************************************/
/*  structure to define a 'fix table' for alternate timezone rules           */
/*****************************************************************************/

#define STDTIME_FIX_TZ_GROUP_SIZE   8
#define STDTIME_FIX_TZ_REGION_SIZE  8

typedef struct
  {
  char                      group [STDTIME_FIX_TZ_GROUP_SIZE+1];
  char                      region[STDTIME_FIX_TZ_REGION_SIZE+1];
  int32_t                   yearLo;
  int32_t                   yearHi;
  STDTIME_TZ_RULE           dstStartRule;
  STDTIME_TZ_TIME           dstStartTime;
  STDTIME_TZ_RULE           dstEndRule;
  STDTIME_TZ_TIME           dstEndTime;
  }
STDTIME_FIX_TZ_RULES;

/*****************************************************************************/
/*  structure defining an array of strings to hold a user-provided list of   */
/*  values equivalent to what is found on a line in the Boost.org timezone   */
/*  database file.  this avoids the need to create a comma-separated list of */
/*  values, and provides a common interface between the two representations. */
/*****************************************************************************/

#define STDTIMEZONE_DATA_FLD_SIZE 40    /* max width of any field */
#define STDTIMEZONE_DATA_FLD_MAX (STDTIMEZONE_DATA_FLD_SIZE-1)
#define STDTIMEZONE_DATA_FLD_COUNT 11

typedef char                STDTIMEZONE_DATA_FIELD
                              [STDTIMEZONE_DATA_FLD_SIZE];

typedef struct
  {
    STDTIMEZONE_DATA_FIELD  tzField [STDTIMEZONE_DATA_FLD_COUNT];
  }
STDTIMEZONE_DATA;


/*** TIMEZONE CONVERSION FUNCTIONS *******************************************/


/*** StdTime to/from Zoned ***************************************************/


STDTIME_RC                  StdTimeToZonedStdTime (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME *           /*I*/ pStdTime,
  STDTIME *                 /*O*/ pStdTimeZoned);

STDTIME_RC                  ZonedStdTimeToStdTime (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME *           /*I*/ pStdTimeZoned,
  STDTIME *                 /*O*/ pStdTime);


/*** StdTimeFields to/from Zoned *********************************************/


STDTIME_RC                  StdTimeFieldsToZonedStdTimeFields (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_FIELDS *          /*O*/ pStdTimeFieldsZoned);

STDTIME_RC                  ZonedStdTimeFieldsToStdTimeFields (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_FIELDS *    /*I*/ pStdTimeFieldsZoned,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** StdTimeString to/from Zoned *********************************************/


STDTIME_RC                  StdTimeStringAToZonedStdTimeStringA (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_STRINGA *   /*I*/ pStdStdTimeString,
  STDTIME_STRINGA *         /*O*/ pLocStdTimeString);

STDTIME_RC                  StdTimeStringWToZonedStdTimeStringW (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_STRINGW *   /*I*/ pStdStdTimeString,
  STDTIME_STRINGW *         /*O*/ pLocStdTimeString);

STDTIME_RC                  ZonedStdTimeStringAToStdTimeStringA (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_STRINGA *   /*I*/ pLocStdTimeString,
  STDTIME_STRINGA *         /*O*/ pStdStdTimeString);

STDTIME_RC                  ZonedStdTimeStringWToStdTimeStringW (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_STRINGW *   /*I*/ pLocStdTimeString,
  STDTIME_STRINGW *         /*O*/ pStdStdTimeString);


#define StdTimeStringToZonedStdTimeStringW StdTimeStringWToZonedStdTimeStringW
#define ZonedStdTimeStringToStdTimeStringW ZonedStdTimeStringWToStdTimeStringW

#define StdTimeStringToZonedStdTimeStringA StdTimeStringAToZonedStdTimeStringA
#define ZonedStdTimeStringToStdTimeStringA ZonedStdTimeStringAToStdTimeStringA


#ifdef STDTIME_UNICODE
#define StdTimeStringToZonedStdTimeString StdTimeStringWToZonedStdTimeStringW
#define ZonedStdTimeStringToStdTimeString ZonedStdTimeStringWToStdTimeStringW
#else
#define StdTimeStringToZonedStdTimeString StdTimeStringAToZonedStdTimeStringA
#define ZonedStdTimeStringToStdTimeString ZonedStdTimeStringAToStdTimeStringA
#endif /* STDTIME_UNICODE */


/*** StdTimeHexStr to/from Zoned *********************************************/


STDTIME_RC                  StdTimeHexStrAToZonedStdTimeHexStrA (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_HEXSTRA *   /*I*/ pStdStdTimeHexStr,
  STDTIME_HEXSTRA *         /*O*/ pLocStdTimeHexStr);

STDTIME_RC                  StdTimeHexStrWToZonedStdTimeHexStrW (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_HEXSTRW *   /*I*/ pStdStdTimeHexStr,
  STDTIME_HEXSTRW *         /*O*/ pLocStdTimeHexStr);

STDTIME_RC                  ZonedStdTimeHexStrAToStdTimeHexStrA (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_HEXSTRA *   /*I*/ pLocStdTimeHexStr,
  STDTIME_HEXSTRA *         /*O*/ pStdStdTimeHexStr);

STDTIME_RC                  ZonedStdTimeHexStrWToStdTimeHexStrW (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_HEXSTRW *   /*I*/ pLocStdTimeHexStr,
  STDTIME_HEXSTRW *         /*O*/ pStdStdTimeHexStr);


#define StdTimeHexStrToZonedStdTimeHexStrW StdTimeHexStrWToZonedStdTimeHexStrW
#define ZonedStdTimeHexStrToStdTimeHexStrW ZonedStdTimeHexStrWToStdTimeHexStrW

#define StdTimeHexStrToZonedStdTimeHexStrA StdTimeHexStrAToZonedStdTimeHexStrA
#define ZonedStdTimeHexStrToStdTimeHexStrA ZonedStdTimeHexStrAToStdTimeHexStrA


#ifdef STDTIME_UNICODE
#define StdTimeHexStrToZonedStdTimeHexStr StdTimeHexStrWToZonedStdTimeHexStrW
#define ZonedStdTimeHexStrToStdTimeHexStr ZonedStdTimeHexStrWToStdTimeHexStrW
#else
#define StdTimeHexStrToZonedStdTimeHexStr StdTimeHexStrAToZonedStdTimeHexStrA
#define ZonedStdTimeHexStrToStdTimeHexStr ZonedStdTimeHexStrAToStdTimeHexStrA
#endif /* STDTIME_UNICODE */


/*** timezone support functions **********************************************/


STDTIME_RC                  TranslateStdTimeZoneName (
  const char *              /*I*/ pZoneName,
  char *                    /*O*/ pZoneID);

STDTIME_RC                  TranslateStdTimeWinZoneName (
  const char *              /*I*/ pZoneName,
  char *                    /*O*/ pZoneID);

STDTIME_RC                  StdTimeZoneDataToInfo (
  const STDTIMEZONE_DATA *  /*I*/ pTzData,
  STDTIMEZONE_INFO *        /*O*/ pTzInfo);

STDTIME_RC                  GetStdTimeZoneInfo (
  const char *              /*I*/ pZoneName,
  STDTIMEZONE_INFO *        /*O*/ pZoneInfo);

STDTIME_RC                  ReadStdTimeZoneInfo (
  const char *              /*I*/ pFileName,
  const char *              /*I*/ pZoneName,
  STDTIMEZONE_INFO *        /*O*/ pZoneInfo);

STDTIME_RC                  StdTimeZoneDayOfRule (
  int32_t                   /*I*/ year,
  const STDTIME_TZ_RULE *   /*I*/ pRule,
  int32_t *                 /*O*/ pDay);

STDTIME_RC                  StdTimeTzTimeToDelta (
  const STDTIME_TZ_TIME *   /*I*/ pTzTime,
  STDTIME_DELTA *           /*O*/ pDelta);

STDTIME_RC                  StdTimeApiZonedFileTimeToFileTime (
  const STDTIMEZONE_INFO *      /*I*/ pZoneInfo,
  const STDTIME_WIN_FILETIME *  /*I*/ pLocFileTime,
  STDTIME_WIN_FILETIME *        /*O*/ pGmtFileTime);

STDTIME_RC                  StdTimeApiFileTimeToZonedFileTime (
  const STDTIMEZONE_INFO *      /*I*/ pZoneInfo,
  const STDTIME_WIN_FILETIME *  /*I*/ pGmtFileTime,
  STDTIME_WIN_FILETIME *        /*O*/ pLocFileTime);

STDTIME_RC                  StdTimeApiZonedFileTimeIsDST (
  const STDTIMEZONE_INFO *      /*I*/ pZoneInfo,
  const STDTIME_WIN_FILETIME *  /*I*/ pLocFileTime,
  STDTIME_BOOL *                /*O*/ pDstFlag);

STDTIME_RC                  StdTimeApiFileTimeIsDST (
  const STDTIMEZONE_INFO *      /*I*/ pZoneInfo,
  const STDTIME_WIN_FILETIME *  /*I*/ pGmtFileTime,
  STDTIME_BOOL *                /*O*/ pDstFlag);


/*** timezone-offset support functions ***************************************/


STDTIME_RC                  StdTimeStringAToTzoA (
  const STDTIME_STRINGA *   /*I*/ pStdTimeString,
  STDTIME_TZOA *            /*O*/ pTzo);

STDTIME_RC                  StdTimeStringWToTzoW (
  const STDTIME_STRINGW *   /*I*/ pStdTimeString,
  STDTIME_TZOW *            /*O*/ pTzo);


STDTIME_RC                  TzoAToStdTimeStringA (
  const STDTIME_TZOA *      /*I*/ pTzo,
  STDTIME_STRINGA *         /*O*/ pStdTimeString);

STDTIME_RC                  TzoWToStdTimeStringW (
  const STDTIME_TZOW *      /*I*/ pTzo,
  STDTIME_STRINGW *         /*O*/ pStdTimeString);


STDTIME_RC                  ValidStdTimeTzoA (
  const STDTIME_TZOA *      /*I*/ pTzo);

STDTIME_RC                  ValidStdTimeTzoW (
  const STDTIME_TZOW *      /*I*/ pTzo);


STDTIME_RC                  NormalizeStdTimeTzoA (
  STDTIME_TZOA *            /*I*/ pTzo);

STDTIME_RC                  NormalizeStdTimeTzoW (
  STDTIME_TZOW *            /*I*/ pTzo);


STDTIME_RC                  GetLocalStdTimeTzoA (
  STDTIME_TZOA *            /*O*/ pTzo);

STDTIME_RC                  GetLocalStdTimeTzoW (
  STDTIME_TZOW *            /*O*/ pTzo);


#define StdTimeStringToTzoW     StdTimeStringWToTzoW
#define TzoToStdTimeStringW     TzoWToStdTimeStringW

#define StdTimeStringToTzoA     StdTimeStringAToTzoA
#define TzoToStdTimeStringA     TzoAToStdTimeStringA


#ifdef STDTIME_UNICODE
#define StdTimeStringToTzo      StdTimeStringWToTzoW
#define TzoToStdTimeString      TzoWToStdTimeStringW
#define ValidStdTimeTzo         ValidStdTimeTzoW
#define NormalizeStdTimeTzo     NormalizeStdTimeTzoW
#define GetLocalStdTimeTzo      GetLocalStdTimeTzoW
#else
#define StdTimeStringToTzo      StdTimeStringAToTzoA
#define TzoToStdTimeString      TzoAToStdTimeStringA
#define ValidStdTimeTzo         ValidStdTimeTzoA
#define NormalizeStdTimeTzo     NormalizeStdTimeTzoA
#define GetLocalStdTimeTzo      GetLocalStdTimeTzoA
#endif /* STDTIME_UNICODE */


/*** error message decoding functions ****************************************/


STDTIME_RC                  StdTimeRcToErrMsgA (
  const STDTIME_RC          /*I*/ stdTimeRc,
  STDTIME_ERRMSGA *         /*O*/ pErrMsg);


STDTIME_RC                  StdTimeRcToErrMsgW (
  const STDTIME_RC          /*I*/ stdTimeRc,
  STDTIME_ERRMSGW *         /*O*/ pErrMsg);


#ifdef STDTIME_UNICODE
#define StdTimeRcToErrMsg   StdTimeRcToErrMsgW
#else
#define StdTimeRcToErrMsg   StdTimeRcToErrMsgA
#endif /* STDTIME_UNICODE */


/*** normalization functions; primarily private functions ********************/


STDTIME_RC                  Rc_NormalizeStdTimeFields (
  STDTIME_FIELDS *          pFields);

STDTIME_RC                  Rc_StdTime_NormalizeSystemTimeEx (
  STDTIME_WIN_SYSTEMTIME *  /*IO*/ pSystemTime,
  int32_t *                 /*IO*/ pUsec,
  int32_t *                 /*IO*/ pNsec);

STDTIME_RC                  Rc_StdTime_NormalizeStructTmEx (
  struct tm *               /*IO*/ pStructTm,
  int32_t *                 /*IO*/ pMsec,
  int32_t *                 /*IO*/ pUsec,
  int32_t *                 /*IO*/ pNsec);


/*****************************************************************************/
/*  END                                                                      */
/*****************************************************************************/


#ifdef  __cplusplus
}
#endif


#endif /* _STDTIME_H_7583ECB2_DB3F_48B3_8A97_2D1D2A38C84A_ */


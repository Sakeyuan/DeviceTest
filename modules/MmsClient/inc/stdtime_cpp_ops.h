/*****************************************************************************/
/* SISCO SOFTWARE MODULE HEADER **********************************************/
/*****************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,            */
/*            2005 All Rights Reserved                                       */
/*                                                                           */
/* MODULE NAME : stdtime_cpp_ops.h                                           */
/* PRODUCT(S)  : Standard Time Management Library                            */
/*                                                                           */
/* MODULE DESCRIPTION:                                                       */
/*   Header file for Standard Time C++ operator functions                    */
/*                                                                           */
/*   These inline operators may be used to simplify comparison and time-     */
/*   difference operations when compiled under C++.  This file is included   */
/*   by stdtime_cppsvcs.h, and may be directly included for non-Windows      */
/*   C++ applications, or where only the comparisons are needed.             */
/*                                                                           */
/* MODIFICATION LOG:                                                         */
/*   Date    Who  Rev  Comments                                              */
/* --------  ---  ---  ----------------------------------------------------- */
/* 06/07/06  RLH   01  Created                                               */
/*****************************************************************************/


#ifndef _STDTIME_CPP_OPS_H_2E336D0C_4C7D_47D9_AA08_FBB17EFAA7E5_
#define _STDTIME_CPP_OPS_H_2E336D0C_4C7D_47D9_AA08_FBB17EFAA7E5_

#ifndef __cplusplus
#error StdTime C++ Operators must be compiled in C++ mode
#endif

/*****************************************************************************/
/*  COMPARISON                                                               */
/*****************************************************************************/

#define GEN_STDTIME_COMPARE_OPS(stdTimeType,stdTimeFunc)                      \
                                                                              \
inline bool operator > (const stdTimeType & a, const stdTimeType & b)         \
  {                                                                           \
  return stdTimeFunc (&a, &b) == STDTIME_GT;                                  \
  }                                                                           \
                                                                              \
inline bool operator < (const stdTimeType & a, const stdTimeType & b)         \
  {                                                                           \
  return stdTimeFunc (&a, &b) == STDTIME_LT;                                  \
  }                                                                           \
                                                                              \
inline bool operator == (const stdTimeType & a, const stdTimeType & b)        \
  {                                                                           \
  return stdTimeFunc (&a, &b) == STDTIME_EQ;                                  \
  }                                                                           \
                                                                              \
inline bool operator >= (const stdTimeType & a, const stdTimeType & b)        \
  {                                                                           \
  return stdTimeFunc (&a, &b) >= STDTIME_EQ;                                  \
  }                                                                           \
                                                                              \
inline bool operator <= (const stdTimeType & a, const stdTimeType & b)        \
  {                                                                           \
  /* since STDTIME_ERR (-2) could be returned, we need to check */            \
  /* explicit values to do this correctly                       */            \
                                                                              \
  int result = (int) stdTimeFunc (&a, &b);                                    \
                                                                              \
  return (result == STDTIME_LT) || (result == STDTIME_EQ);                    \
  }                                                                           \
                                                                              \
inline bool operator != (const stdTimeType & a, const stdTimeType & b)        \
  {                                                                           \
  return stdTimeFunc (&a, &b) != STDTIME_EQ;                                  \
  }                                                                          //

GEN_STDTIME_COMPARE_OPS (STDTIME, CompareStdTime)
GEN_STDTIME_COMPARE_OPS (STDTIME_FIELDS, CompareStdTimeFields)
GEN_STDTIME_COMPARE_OPS (STDTIME_STRINGA, CompareStdTimeStringA)
GEN_STDTIME_COMPARE_OPS (STDTIME_STRINGW, CompareStdTimeStringW)
GEN_STDTIME_COMPARE_OPS (STDTIME_HEXSTRA, CompareStdTimeHexStrA)
GEN_STDTIME_COMPARE_OPS (STDTIME_HEXSTRW, CompareStdTimeHexStrW)


#endif /* _STDTIME_CPP_OPS_H_2E336D0C_4C7D_47D9_AA08_FBB17EFAA7E5_ */


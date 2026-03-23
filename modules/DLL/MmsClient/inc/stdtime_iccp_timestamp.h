/*****************************************************************************/
/* SISCO SOFTWARE MODULE HEADER **********************************************/
/*****************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,            */
/*            2006 All Rights Reserved                                       */
/*                                                                           */
/* MODULE NAME : stdtime_iccp_timestamp.h                                    */
/* PRODUCT(S)  : Standard Time Management Library                            */
/*                                                                           */
/* MODULE DESCRIPTION:                                                       */
/*   Support for ICCP TIMESTAMP (aka "TIMESTAMP_EX")                         */
/*                                                                           */
/* NOTE:                                                                     */
/*   STDTIME refers to a "TIMESTAMP_EX" value as an "ICCP TIMESTAMP", but    */
/*   *without* the "_EX" suffix on the name.  This was done because STDTIME  */
/*   already uses the "Ex" notation to mean "extra fields", and the two      */
/*   uses would have been confusing.  We need to avoid the possibility of a  */
/*   name like "StdTimeToTimeStampExEx" which would have been confusing and  */
/*   hard to understand and document.                                        */
/*                                                                           */
/* NOTE:                                                                     */
/*   A "standard" ICCP "TimeStamp" is a simple 32-bit time_t value.          */
/*                                                                           */
/* MODIFICATION LOG:                                                         */
/*   Date    Who  Rev  Comments                                              */
/* --------  ---  ---  ----------------------------------------------------- */
/* 10/05/06  RLH   01  Created                                               */
/*****************************************************************************/

#ifdef  __cplusplus
extern "C" {
#endif

/* TIMESTAMP_EX definition in \mmslite\inc\mi.h */

#ifdef MI_DEFS_INCLUDED

#define STDTIME_ICCP_TIMESTAMP      TIMESTAMP_EX

#else

typedef struct
  {
  int32_t  GMTBasedS;       /* time_t offset of seconds since 1970-01-01 */
  int16_t  Milliseconds;    /* msec value: 0 to 999 */
  } STDTIME_ICCP_TIMESTAMP;

#endif


/*** MmsTimeOfDay6 initialization function ***********************************/

STDTIME_ICCP_TIMESTAMP      StdTimeApiZeroIccpTimeStamp ();


/*** IccpTimeStampEx functions ***********************************************/


STDTIME_RC                  StdTimeToIccpTimeStampEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_ICCP_TIMESTAMP *  /*O*/ pIccpTimeStamp,
  int32_t *                 /*O*/ pUsec, /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  IccpTimeStampExToStdTime (
  const STDTIME_ICCP_TIMESTAMP * /*I*/ pIccpTimeStamp,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToIccpTimeStampEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_ICCP_TIMESTAMP *  /*O*/ pIccpTimeStamp,
  int32_t *                 /*O*/ pUsec, /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  IccpTimeStampExToStdTimeFields (
  const STDTIME_ICCP_TIMESTAMP * /*I*/ pIccpTimeStamp,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** IccpTimeStamp functions *************************************************/


STDTIME_RC                  StdTimeToIccpTimeStamp (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_ICCP_TIMESTAMP *  /*O*/ pIccpTimeStamp);


STDTIME_RC                  IccpTimeStampToStdTime (
  const STDTIME_ICCP_TIMESTAMP * /*I*/ pIccpTimeStamp,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToIccpTimeStamp (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_ICCP_TIMESTAMP *  /*O*/ pIccpTimeStamp);


STDTIME_RC                  IccpTimeStampToStdTimeFields (
  const STDTIME_ICCP_TIMESTAMP * /*I*/ pIccpTimeStamp,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


#ifdef  __cplusplus
}
#endif


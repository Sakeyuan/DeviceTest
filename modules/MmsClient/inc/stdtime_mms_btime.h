/*****************************************************************************/
/* SISCO SOFTWARE MODULE HEADER **********************************************/
/*****************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,            */
/*            2006 All Rights Reserved                                       */
/*                                                                           */
/* MODULE NAME : stdtime_mms_btime.h                                         */
/* PRODUCT(S)  : Standard Time Management Library                            */
/*                                                                           */
/* MODULE DESCRIPTION:                                                       */
/*   Support for MMS Btime4, BTime6 and BTOD conversions to/from STDTIME     */
/*                                                                           */
/* MODIFICATION LOG:                                                         */
/*   Date    Who  Rev  Comments                                              */
/* --------  ---  ---  ----------------------------------------------------- */
/* 10/05/06  RLH   01  Created                                               */
/*****************************************************************************/

#ifdef  __cplusplus
extern "C" {
#endif

#if defined(ASN1R_INCLUDED) && defined(MMS_BTOD4) && defined(MMS_BTOD6)
#define STDTIME_MMS_TIMEOFDAY6  MMS_BTIME6
#define STDTIME_MMS_BTOD        MMS_BTOD
#define STDTIME_MMS_BTOD4       MMS_BTOD4
#define STDTIME_MMS_BTOD6       MMS_BTOD6

#else

typedef struct
  {
  int32_t                   ms;     /* milliseconds since midnight */
  int32_t                   day;    /* days since January 1, 1984 */
  }
STDTIME_MMS_TIMEOFDAY6;


#define STDTIME_MMS_BTOD4   4
#define STDTIME_MMS_BTOD6   6

typedef struct
  {
  int                       form;   /* MMS_BTOD6, MMS_BTOD4      */
  int32_t                   ms;     /* milliseconds since midnight */
  int32_t                   day;    /* days since January 1, 1984 */
  }
STDTIME_MMS_BTOD;


#endif


#if defined(ASN1R_INCLUDED) && defined(MMS_BTIME4_DEFINED)
#define STDTIME_MMS_TIMEOFDAY4  MMS_BTIME4

#else

typedef struct
  {
  int32_t                   ms;     /* milliseconds since midnight */
  }
STDTIME_MMS_TIMEOFDAY4;

#endif


/*** MmsTimeOfDay4/6 initialization functions ********************************/

STDTIME_MMS_TIMEOFDAY4      StdTimeApiZeroMmsTimeOfDay4 ();

STDTIME_MMS_TIMEOFDAY6      StdTimeApiZeroMmsTimeOfDay6 ();

STDTIME_MMS_BTOD            StdTimeApiZeroMmsBtod ();


/*** MmsTimeOfDay4Ex functions ***********************************************/


STDTIME_RC                  StdTimeToMmsTimeOfDay4Ex (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_MMS_TIMEOFDAY4 *  /*O*/ pMmsTimeOfDay4,
  int32_t *                 /*O*/ pUsec, /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  MmsTimeOfDay4ExToStdTime (
  const STDTIME_MMS_TIMEOFDAY4 * /*I*/ pMmsTimeOfDay4,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToMmsTimeOfDay4Ex (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_MMS_TIMEOFDAY4 *  /*O*/ pMmsTimeOfDay4,
  int32_t *                 /*O*/ pUsec, /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  MmsTimeOfDay4ExToStdTimeFields (
  const STDTIME_MMS_TIMEOFDAY4 * /*I*/ pMmsTimeOfDay4,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** MmsTimeOfDay4 functions *************************************************/


STDTIME_RC                  StdTimeToMmsTimeOfDay4 (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_MMS_TIMEOFDAY4 *  /*O*/ pMmsTimeOfDay4);


STDTIME_RC                  MmsTimeOfDay4ToStdTime (
  const STDTIME_MMS_TIMEOFDAY4 * /*I*/ pMmsTimeOfDay4,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToMmsTimeOfDay4 (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_MMS_TIMEOFDAY4 *  /*O*/ pMmsTimeOfDay4);


STDTIME_RC                  MmsTimeOfDay4ToStdTimeFields (
  const STDTIME_MMS_TIMEOFDAY4 * /*I*/ pMmsTimeOfDay4,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** MmsTimeOfDay6Ex functions ***********************************************/


STDTIME_RC                  StdTimeToMmsTimeOfDay6Ex (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_MMS_TIMEOFDAY6 *  /*O*/ pMmsTimeOfDay6,
  int32_t *                 /*O*/ pUsec, /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  MmsTimeOfDay6ExToStdTime (
  const STDTIME_MMS_TIMEOFDAY6 * /*I*/ pMmsTimeOfDay6,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToMmsTimeOfDay6Ex (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_MMS_TIMEOFDAY6 *  /*O*/ pMmsTimeOfDay6,
  int32_t *                 /*O*/ pUsec, /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  MmsTimeOfDay6ExToStdTimeFields (
  const STDTIME_MMS_TIMEOFDAY6 * /*I*/ pMmsTimeOfDay6,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** MmsTimeOfDay6 functions *************************************************/


STDTIME_RC                  StdTimeToMmsTimeOfDay6 (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_MMS_TIMEOFDAY6 *  /*O*/ pMmsTimeOfDay6);


STDTIME_RC                  MmsTimeOfDay6ToStdTime (
  const STDTIME_MMS_TIMEOFDAY6 * /*I*/ pMmsTimeOfDay6,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToMmsTimeOfDay6 (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_MMS_TIMEOFDAY6 *  /*O*/ pMmsTimeOfDay6);


STDTIME_RC                  MmsTimeOfDay6ToStdTimeFields (
  const STDTIME_MMS_TIMEOFDAY6 * /*I*/ pMmsTimeOfDay6,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** MmsBtodEx functions *****************************************************/


STDTIME_RC                  StdTimeToMmsBtodEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_MMS_BTOD *        /*O*/ pMmsBtod,
  int32_t *                 /*O*/ pUsec, /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  MmsBtodExToStdTime (
  const STDTIME_MMS_BTOD *  /*I*/ pMmsBtod,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToMmsBtodEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_MMS_BTOD *        /*O*/ pMmsBtod,
  int32_t *                 /*O*/ pUsec, /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  MmsBtodExToStdTimeFields (
  const STDTIME_MMS_BTOD *  /*I*/ pMmsBtod,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** MmsBtod functions *******************************************************/


STDTIME_RC                  StdTimeToMmsBtod (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_MMS_BTOD *        /*O*/ pMmsBtod);


STDTIME_RC                  MmsBtodToStdTime (
  const STDTIME_MMS_BTOD *  /*I*/ pMmsBtod,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToMmsBtod (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_MMS_BTOD *        /*O*/ pMmsBtod);


STDTIME_RC                  MmsBtodToStdTimeFields (
  const STDTIME_MMS_BTOD * /*I*/ pMmsBtod,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);

#ifdef  __cplusplus
}
#endif


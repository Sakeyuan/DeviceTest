/*****************************************************************************/
/* SISCO SOFTWARE MODULE HEADER **********************************************/
/*****************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,            */
/*            2005 All Rights Reserved                                       */
/*                                                                           */
/* MODULE NAME : stdtime_cppsvcs.h                                           */
/* PRODUCT(S)  : Standard Time Management Library                            */
/*                                                                           */
/* MODULE DESCRIPTION:                                                       */
/*   Header file for Standard Time C++ Services for Windows                  */
/*                                                                           */
/*   Note: these functions a produce a return-code value STDTIME_RC.         */
/*   the return code is zero if successful, otherwise it is a structured     */
/*   value in which the low-order 10 bits enumerates an error reason,        */
/*   and the upper 20 bits enumerates the high-level and low-level           */
/*   functions where the error was detected.                                 */
/*                                                                           */
/* MODIFICATION LOG:                                                         */
/*   Date    Who  Rev  Comments                                              */
/* --------  ---  ---  ----------------------------------------------------- */
/* 06/07/06  RLH   02  Numerous features added, see stdtime.doc              */
/* 05/12/06  RLH   01  Created                                               */
/*****************************************************************************/


#ifndef _STDTIME_CPPSVCS_H_AE9AF131_55E1_4EF1_A1FE_ACB15F28A6D4_
#define _STDTIME_CPPSVCS_H_AE9AF131_55E1_4EF1_A1FE_ACB15F28A6D4_


#ifndef __cplusplus
#error StdTime C++ Services for Windows must be compiled in C++ mode
#endif

#if (!defined(_WIN32)) || (!defined(_MSC_VER))
#error StdTime C++ Services for Windows only supported on Windows platform
#endif

#define STDTIME_CPPSVCS_DEFINED

#include "stdtime.h"

#ifndef QUADLIB_DISABLED
#error StdTime C++ Services for Windows requires QUADLIB_DISABLED
#endif

#ifndef QUADLIB_NATIVE64_ENABLED
#error StdTime C++ Services for Windows requires QUADLIB_NATIVE64_ENABLED
#endif


/*****************************************************************************/
/*  DETERMINE CONFIGURATION                                                  */
/*****************************************************************************/


#undef STDTIME_CPP_OK


#undef STDTIME_CPP_CTIME_ENABLED
#undef STDTIME_CPP_CTIMESPAN_ENABLED
#undef STDTIME_CPP_CFILETIME_ENABLED
#undef STDTIME_CPP_CFILETIMESPAN_ENABLED


#ifdef __ATLTIME_H__
#define STDTIME_CPP_OK
#define STDTIME_CPP_CTIME_ENABLED
#define STDTIME_CPP_CTIMESPAN_ENABLED
#define STDTIME_CPP_CFILETIME_ENABLED
#define STDTIME_CPP_CFILETIMESPAN_ENABLED


#elif (defined(__AFX_H__)) && (_MSC_VER < 1300)
#define STDTIME_CPP_OK
#define STDTIME_CPP_CTIME_ENABLED
#define STDTIME_CPP_CTIMESPAN_ENABLED


#endif /* __ATLTIME_H__ */


#undef STDTIME_CPP_COLEDATETIME_ENABLED
#undef STDTIME_CPP_COLEDATETIMESPAN_ENABLED


#ifdef __ATLCOMTIME_H__
#define STDTIME_CPP_OK
#define STDTIME_CPP_COLEDATETIME_ENABLED
#define STDTIME_CPP_COLEDATETIMESPAN_ENABLED
#endif /* __ATLCOMTIME_H__ */


#undef STDTIME_CPP_CCOMDATE_ENABLED
#undef STDTIME_CPP_CCOMSPAN_ENABLED


#ifdef __COMDATE_H__
#define STDTIME_CPP_OK
#define STDTIME_CPP_CCOMDATE_ENABLED
#define STDTIME_CPP_CCOMSPAN_ENABLED


#endif /* __COMDATE_H__ */


#ifndef STDTIME_CPP_OK
#error StdTime C++ Services for Windows found no class definition include files
#endif


/*****************************************************************************/
/*** TIME FUNCTIONS **********************************************************/
/*****************************************************************************/


/*** CTimeEx functions *******************************************************/


#ifdef STDTIME_CPP_CTIME_ENABLED


STDTIME_RC                  StdTimeToCTimeEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_TIMETYPE *        /*O*/ pCTime,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  CTimeExToStdTime (
  const STDTIME_TIMETYPE *  /*I*/ pCTime,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToCTimeEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_TIMETYPE *        /*O*/ pCTime,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  CTimeExToStdTimeFields (
  const STDTIME_TIMETYPE *  /*I*/ pCTime,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** CTime functions *********************************************************/


STDTIME_RC                  StdTimeToCTime (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_TIMETYPE *        /*O*/ pCTime);


STDTIME_RC                  CTimeToStdTime (
  const STDTIME_TIMETYPE *  /*I*/ pCTime,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToCTime (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_TIMETYPE *        /*O*/ pCTime);


STDTIME_RC                  CTimeToStdTimeFields (
  const STDTIME_TIMETYPE *  /*I*/ pCTime,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


#endif /* STDTIME_CPP_CTIME_ENABLED */


/*** CFileTime functions *****************************************************/


#ifdef STDTIME_CPP_CFILETIME_ENABLED


STDTIME_RC                  StdTimeToCFileTime (
  const STDTIME *           /*I*/ pStdTime,
  CFileTime *               /*O*/ pCFileTime);


STDTIME_RC                  CFileTimeToStdTime (
  const CFileTime *         /*I*/ pCFileTime,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToCFileTime (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  CFileTime *               /*O*/ pCFileTime);


STDTIME_RC                  CFileTimeToStdTimeFields (
  const CFileTime *         /*I*/ pCFileTime,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


#endif /* STDTIME_CPP_CFILETIME_ENABLED */


/*** HpCOleDateTimeEx functions **********************************************/


#ifdef STDTIME_CPP_COLEDATETIME_ENABLED


STDTIME_RC                  StdTimeToHpCOleDateTimeEx (
  const STDTIME *           /*I*/ pStdTime,
  COleDateTime *            /*O*/ pCOleDateTime,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  HpCOleDateTimeExToStdTime (
  const COleDateTime *      /*I*/ pCOleDateTime,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToHpCOleDateTimeEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  COleDateTime *            /*O*/ pCOleDateTime,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  HpCOleDateTimeExToStdTimeFields (
  const COleDateTime *      /*I*/ pCOleDateTime,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** HpCOleDateTime functions ************************************************/


STDTIME_RC                  StdTimeToHpCOleDateTime (
  const STDTIME *           /*I*/ pStdTime,
  COleDateTime *            /*O*/ pCOleDateTime);


STDTIME_RC                  HpCOleDateTimeToStdTime (
  const COleDateTime *      /*I*/ pCOleDateTime,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToHpCOleDateTime (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  COleDateTime *            /*O*/ pCOleDateTime);


STDTIME_RC                  HpCOleDateTimeToStdTimeFields (
  const COleDateTime *      /*I*/ pCOleDateTime,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** COleDateTimeEx functions ************************************************/


STDTIME_RC                  StdTimeToCOleDateTimeEx (
  const STDTIME *           /*I*/ pStdTime,
  COleDateTime *            /*O*/ pCOleDateTime,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  COleDateTimeExToStdTime (
  const COleDateTime *      /*I*/ pCOleDateTime,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToCOleDateTimeEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  COleDateTime *            /*O*/ pCOleDateTime,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  COleDateTimeExToStdTimeFields (
  const COleDateTime *      /*I*/ pCOleDateTime,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** COleDateTime functions **************************************************/


STDTIME_RC                  StdTimeToCOleDateTime (
  const STDTIME *           /*I*/ pStdTime,
  COleDateTime *            /*O*/ pCOleDateTime);


STDTIME_RC                  COleDateTimeToStdTime (
  const COleDateTime *      /*I*/ pCOleDateTime,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToCOleDateTime (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  COleDateTime *            /*O*/ pCOleDateTime);


STDTIME_RC                  COleDateTimeToStdTimeFields (
  const COleDateTime *      /*I*/ pCOleDateTime,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


#endif /* STDTIME_CPP_COLEDATETIME_ENABLED */


/*** HpCComDateEx functions **************************************************/


#ifdef STDTIME_CPP_CCOMDATE_ENABLED


STDTIME_RC                  StdTimeToHpCComDateEx (
  const STDTIME *           /*I*/ pStdTime,
  CComDATE *                /*O*/ pCComDate,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  HpCComDateExToStdTime (
  const CComDATE *          /*I*/ pCComDate,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToHpCComDateEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  CComDATE *                /*O*/ pCComDate,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  HpCComDateExToStdTimeFields (
  const CComDATE *          /*I*/ pCComDate,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** HpCComDate functions ****************************************************/


STDTIME_RC                  StdTimeToHpCComDate (
  const STDTIME *           /*I*/ pStdTime,
  CComDATE *                /*O*/ pCComDate);


STDTIME_RC                  HpCComDateToStdTime (
  const CComDATE *          /*I*/ pCComDate,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToHpCComDate (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  CComDATE *                /*O*/ pCComDate);


STDTIME_RC                  HpCComDateToStdTimeFields (
  const CComDATE *          /*I*/ pCComDate,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** CComDateEx functions ****************************************************/


STDTIME_RC                  StdTimeToCComDateEx (
  const STDTIME *           /*I*/ pStdTime,
  CComDATE *                /*O*/ pCComDate,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  CComDateExToStdTime (
  const CComDATE *          /*I*/ pCComDate,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToCComDateEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  CComDATE *                /*O*/ pCComDate,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  CComDateExToStdTimeFields (
  const CComDATE *          /*I*/ pCComDate,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** CComDate functions ******************************************************/


STDTIME_RC                  StdTimeToCComDate (
  const STDTIME *           /*I*/ pStdTime,
  CComDATE *                /*O*/ pCComDate);


STDTIME_RC                  CComDateToStdTime (
  const CComDATE *          /*I*/ pCComDate,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToCComDate (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  CComDATE *                /*O*/ pCComDate);


STDTIME_RC                  CComDateToStdTimeFields (
  const CComDATE *          /*I*/ pCComDate,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


#endif /* STDTIME_CPP_CCOMDATE_ENABLED */


/*****************************************************************************/
/*** CComDate / DATE FUNCTIONS ***********************************************/
/*****************************************************************************/

/* because CComDATE defines an operator & that returns a pointer to a DATE,  */
/* the usual calling sequences won't work.  so, we define CComDATE functions */
/* that take a pointer to DATE, so we won't need type casting to call them.  */


/*** HpCComDateEx / DATE functions *******************************************/


#ifdef STDTIME_CPP_CCOMDATE_ENABLED


STDTIME_RC                  StdTimeToHpCComDateEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  HpCComDateExToStdTime (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToHpCComDateEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  HpCComDateExToStdTimeFields (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** HpCComDate / DATE functions *********************************************/


STDTIME_RC                  StdTimeToHpCComDate (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DATE *        /*O*/ pDate);


STDTIME_RC                  HpCComDateToStdTime (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToHpCComDate (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DATE *        /*O*/ pDate);


STDTIME_RC                  HpCComDateToStdTimeFields (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** CComDateEx / DATE functions *********************************************/


STDTIME_RC                  StdTimeToCComDateEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  CComDateExToStdTime (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToCComDateEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  CComDateExToStdTimeFields (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** CComDate / DATE functions ***********************************************/


STDTIME_RC                  StdTimeToCComDate (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DATE *        /*O*/ pDate);


STDTIME_RC                  CComDateToStdTime (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToCComDate (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DATE *        /*O*/ pDate);


STDTIME_RC                  CComDateToStdTimeFields (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


#endif /* STDTIME_CPP_CCOMDATE_ENABLED */




/*****************************************************************************/
/*** SPAN FUNCTIONS **********************************************************/
/*****************************************************************************/


/*** CTimeSpanEx functions ***************************************************/


#ifdef STDTIME_CPP_CTIMESPAN_ENABLED


STDTIME_RC                  StdTimeToCTimeSpanEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_TIMETYPE *        /*O*/ pCTimeSpan,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  CTimeSpanExToStdTime (
  const STDTIME_TIMETYPE *  /*I*/ pCTimeSpan,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToCTimeSpanEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_TIMETYPE *        /*O*/ pCTimeSpan,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  CTimeSpanExToStdTimeFields (
  const STDTIME_TIMETYPE *  /*I*/ pCTimeSpan,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** CTimeSpan functions *****************************************************/


STDTIME_RC                  StdTimeToCTimeSpan (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_TIMETYPE *        /*O*/ pCTimeSpan);


STDTIME_RC                  CTimeSpanToStdTime (
  const STDTIME_TIMETYPE *  /*I*/ pCTimeSpan,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToCTimeSpan (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_TIMETYPE *        /*O*/ pCTimeSpan);


STDTIME_RC                  CTimeSpanToStdTimeFields (
  const STDTIME_TIMETYPE *  /*I*/ pCTimeSpan,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


#endif /* STDTIME_CPP_CTIMESPAN_ENABLED */


/*** CFileTimeSpan functions *************************************************/


#ifdef STDTIME_CPP_CFILETIMESPAN_ENABLED


STDTIME_RC                  StdTimeToCFileTimeSpan (
  const STDTIME *           /*I*/ pStdTime,
  CFileTimeSpan *           /*O*/ pCFileTimeSpan);


STDTIME_RC                  CFileTimeSpanToStdTime (
  const CFileTimeSpan *     /*I*/ pCFileTimeSpan,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToCFileTimeSpan (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  CFileTimeSpan *           /*O*/ pCFileTimeSpan);


STDTIME_RC                  CFileTimeSpanToStdTimeFields (
  const CFileTimeSpan *     /*I*/ pCFileTimeSpan,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


#endif /* STDTIME_CPP_CFILETIMESPAN_ENABLED */


/*** HpCOleDateTimeSpanEx functions ******************************************/


#ifdef STDTIME_CPP_COLEDATETIMESPAN_ENABLED


STDTIME_RC                  StdTimeToHpCOleDateTimeSpanEx (
  const STDTIME *           /*I*/ pStdTime,
  COleDateTimeSpan *        /*O*/ pCOleDateTimeSpan,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  HpCOleDateTimeSpanExToStdTime (
  const COleDateTimeSpan *  /*I*/ pCOleDateTimeSpan,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToHpCOleDateTimeSpanEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  COleDateTimeSpan *        /*O*/ pCOleDateTimeSpan,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  HpCOleDateTimeSpanExToStdTimeFields (
  const COleDateTimeSpan *  /*I*/ pCOleDateTimeSpan,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** HpCOleDateTimeSpan functions ********************************************/


STDTIME_RC                  StdTimeToHpCOleDateTimeSpan (
  const STDTIME *           /*I*/ pStdTime,
  COleDateTimeSpan *        /*O*/ pCOleDateTimeSpan);


STDTIME_RC                  HpCOleDateTimeSpanToStdTime (
  const COleDateTimeSpan *  /*I*/ pCOleDateTimeSpan,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToHpCOleDateTimeSpan (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  COleDateTimeSpan *        /*O*/ pCOleDateTimeSpan);


STDTIME_RC                  HpCOleDateTimeSpanToStdTimeFields (
  const COleDateTimeSpan *  /*I*/ pCOleDateTimeSpan,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** COleDateTimeSpanEx functions ********************************************/


STDTIME_RC                  StdTimeToCOleDateTimeSpanEx (
  const STDTIME *           /*I*/ pStdTime,
  COleDateTimeSpan *        /*O*/ pCOleDateTimeSpan,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  COleDateTimeSpanExToStdTime (
  const COleDateTimeSpan *  /*I*/ pCOleDateTimeSpan,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToCOleDateTimeSpanEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  COleDateTimeSpan *        /*O*/ pCOleDateTimeSpan,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  COleDateTimeSpanExToStdTimeFields (
  const COleDateTimeSpan *  /*I*/ pCOleDateTimeSpan,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** COleDateTimeSpan functions **********************************************/


STDTIME_RC                  StdTimeToCOleDateTimeSpan (
  const STDTIME *           /*I*/ pStdTime,
  COleDateTimeSpan *        /*O*/ pCOleDateTimeSpan);


STDTIME_RC                  COleDateTimeSpanToStdTime (
  const COleDateTimeSpan *  /*I*/ pCOleDateTimeSpan,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToCOleDateTimeSpan (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  COleDateTimeSpan *        /*O*/ pCOleDateTimeSpan);


STDTIME_RC                  COleDateTimeSpanToStdTimeFields (
  const COleDateTimeSpan *  /*I*/ pCOleDateTimeSpan,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


#endif /* STDTIME_CPP_COLEDATETIMESPAN_ENABLED */


/*** HpCComSpanEx functions **************************************************/


#ifdef STDTIME_CPP_CCOMSPAN_ENABLED


STDTIME_RC                  StdTimeToHpCComSpanEx (
  const STDTIME *           /*I*/ pStdTime,
  CComSpan *                /*O*/ pCComSpan,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  HpCComSpanExToStdTime (
  const CComSpan *          /*I*/ pCComSpan,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToHpCComSpanEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  CComSpan *                /*O*/ pCComSpan,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  HpCComSpanExToStdTimeFields (
  const CComSpan *          /*I*/ pCComSpan,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** HpCComSpan functions ****************************************************/


STDTIME_RC                  StdTimeToHpCComSpan (
  const STDTIME *           /*I*/ pStdTime,
  CComSpan *                /*O*/ pCComSpan);


STDTIME_RC                  HpCComSpanToStdTime (
  const CComSpan *          /*I*/ pCComSpan,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToHpCComSpan (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  CComSpan *                /*O*/ pCComSpan);


STDTIME_RC                  HpCComSpanToStdTimeFields (
  const CComSpan *          /*I*/ pCComSpan,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** CComSpanEx functions ****************************************************/


STDTIME_RC                  StdTimeToCComSpanEx (
  const STDTIME *           /*I*/ pStdTime,
  CComSpan *                /*O*/ pCComSpan,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  CComSpanExToStdTime (
  const CComSpan *          /*I*/ pCComSpan,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToCComSpanEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  CComSpan *                /*O*/ pCComSpan,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec); /* optional */


STDTIME_RC                  CComSpanExToStdTimeFields (
  const CComSpan *          /*I*/ pCComSpan,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


/*** CComSpan functions ******************************************************/


STDTIME_RC                  StdTimeToCComSpan (
  const STDTIME *           /*I*/ pStdTime,
  CComSpan *                /*O*/ pCComSpan);


STDTIME_RC                  CComSpanToStdTime (
  const CComSpan *          /*I*/ pCComSpan,
  STDTIME *                 /*O*/ pStdTime);


STDTIME_RC                  StdTimeFieldsToCComSpan (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  CComSpan *                /*O*/ pCComSpan);


STDTIME_RC                  CComSpanToStdTimeFields (
  const CComSpan *          /*I*/ pCComSpan,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields);


#endif /* STDTIME_CPP_CCOMSPAN_ENABLED */


#endif /* _STDTIME_CPPSVCS_H_AE9AF131_55E1_4EF1_A1FE_ACB15F28A6D4_ */


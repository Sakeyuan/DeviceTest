/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	1997, All Rights Reserved					*/
/*									*/
/*			PROPRIETARY AND CONFIDENTIAL			*/
/*									*/
/* MODULE NAME : cosp_log.h						*/
/* PRODUCT(S)  : MOSI Stack (over TP4)					*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*		This header file contains logging macros for COSP.	*/
/*	Note:	To compile logging functions use the DEBUG_SISCO define	*/
/*		in the project make file.				*/
/*									*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 09/13/99  MDE    05     Added SD_CONST modifiers			*/
/* 10/08/98  MDE    04     Migrated to updated SLOG interface		*/
/* 05/27/97  JRB  7.00     MMSEASE 7.0 release.				*/
/* 04/24/97  JRB    03     Added NO-DEBUG version of COSP_LOG_ERRH.	*/
/* 03/20/97  EJV    02     Enhanced logging.				*/
/* 02/13/97  EJV    01     Created					*/
/************************************************************************/
#ifndef COSP_LOG_INCLUDED
#define COSP_LOG_INCLUDED

#include "slog.h"

#ifdef __cplusplus
extern "C" {
#endif


/* NOTE: COSP log masks and acse_debug_sel are defined in acse2usr.h */


#if defined(DEBUG_SISCO)

  /* this number will identify the log entry as COSP log */

extern SD_CONST ST_CHAR *SD_CONST _cosp_err_logstr;
extern SD_CONST ST_CHAR *SD_CONST _cosp_dec_logstr;
extern SD_CONST ST_CHAR *SD_CONST _cosp_dec_hex_logstr;
extern SD_CONST ST_CHAR *SD_CONST _cosp_enc_logstr;
extern SD_CONST ST_CHAR *SD_CONST _cosp_enc_hex_logstr;

  /*--------------------------------------------*/
  /* hard errors logging			*/
  /*--------------------------------------------*/

  #define COSP_LOG_ERR0(a) {\
	if (acse_debug_sel & COSP_LOG_ERR)\
	  _slog (sLogCtrl,_cosp_err_logstr,thisFileName,__LINE__,a);\
	}
  #define COSP_LOG_ERR1(a,b) {\
	if (acse_debug_sel & COSP_LOG_ERR)\
	  _slog (sLogCtrl,_cosp_err_logstr,thisFileName,__LINE__,a,b);\
	}
  #define COSP_LOG_ERR2(a,b,c) {\
	if (acse_debug_sel & COSP_LOG_ERR)\
	  _slog (sLogCtrl,_cosp_err_logstr,thisFileName,__LINE__,a,b,c);\
	}
  #define COSP_LOG_ERR3(a,b,c,d) {\
	if (acse_debug_sel & COSP_LOG_ERR)\
	  _slog (sLogCtrl,_cosp_err_logstr,thisFileName,__LINE__,a,b,c,d);\
	}
  /* continuation macros */
  #define COSP_LOG_ERRC0(a) {\
	if (acse_debug_sel & COSP_LOG_ERR)\
	  _slogc (sLogCtrl,a);\
	}
  #define COSP_LOG_ERRC1(a,b) {\
	if (acse_debug_sel & COSP_LOG_ERR)\
	  _slogc (sLogCtrl,a,b);\
	}
  #define COSP_LOG_ERRC2(a,b,c) {\
	if (acse_debug_sel & COSP_LOG_ERR)\
	  _slogc (sLogCtrl,a,b,c);\
	}
  /* hex logging */
  #define COSP_LOG_ERRH(a,b) {\
	if (acse_debug_sel & COSP_LOG_ERR)\
	  _slogHex (sLogCtrl,a,b);\
	}

  /*--------------------------------------------*/
  /* SS-user req and rsp logging		*/
  /*--------------------------------------------*/

  #define COSP_LOG_ENC0(a) {\
	if (acse_debug_sel & COSP_LOG_ENC)\
	  _slog (sLogCtrl,_cosp_enc_logstr,thisFileName,__LINE__,a);\
	}
  #define COSP_LOG_ENC1(a,b) {\
	if (acse_debug_sel & COSP_LOG_ENC)\
	  _slog (sLogCtrl,_cosp_enc_logstr,thisFileName,__LINE__,a,b);\
	}
  #define COSP_LOG_ENC2(a,b,c) {\
	if (acse_debug_sel & COSP_LOG_ENC)\
	  _slog (sLogCtrl,_cosp_enc_logstr,thisFileName,__LINE__,a,b,c);\
	}
  #define COSP_LOG_ENC3(a,b,c,d) {\
	if (acse_debug_sel & COSP_LOG_ENC)\
	  _slog (sLogCtrl,_cosp_enc_logstr,thisFileName,__LINE__,a,b,c,d);\
	}
  #define COSP_LOG_ENC4(a,b,c,d,e) {\
	if (acse_debug_sel & COSP_LOG_ENC)\
	  _slog (sLogCtrl,_cosp_enc_logstr,thisFileName,__LINE__,a,b,c,d,e);\
	}
  /* continuation macros */
  #define COSP_LOG_ENCC0(a) {\
	if (acse_debug_sel & COSP_LOG_ENC)\
	  _slogc (sLogCtrl,a);\
	}
  #define COSP_LOG_ENCC1(a,b) {\
	if (acse_debug_sel & COSP_LOG_ENC)\
	  _slogc (sLogCtrl,a,b);\
	}
  /* hex logging */
  #define COSP_LOG_ENCH(a,b) {\
	if (acse_debug_sel & COSP_LOG_ENC_HEX)\
	  _slogHex (sLogCtrl,a,b);\
	}

  /*--------------------------------------------*/
  /* SS-user ind and cnf logging		*/
  /*--------------------------------------------*/

  #define COSP_LOG_DEC0(a) {\
	if (acse_debug_sel & COSP_LOG_DEC)\
	  _slog (sLogCtrl,_cosp_dec_logstr,thisFileName,__LINE__,a);\
	}
  #define COSP_LOG_DEC1(a,b) {\
	if (acse_debug_sel & COSP_LOG_DEC)\
	  _slog (sLogCtrl,_cosp_dec_logstr,thisFileName,__LINE__,a,b);\
	}
  #define COSP_LOG_DEC2(a,b,c) {\
	if (acse_debug_sel & COSP_LOG_DEC)\
	  _slog (sLogCtrl,_cosp_dec_logstr,thisFileName,__LINE__,a,b,c);\
	}
  #define COSP_LOG_DEC3(a,b,c,d) {\
	if (acse_debug_sel & COSP_LOG_DEC)\
	  _slog (sLogCtrl,_cosp_dec_logstr,thisFileName,__LINE__,a,b,c,d);\
	}
  #define COSP_LOG_DEC4(a,b,c,d,e) {\
	if (acse_debug_sel & COSP_LOG_DEC)\
	  _slog (sLogCtrl,_cosp_dec_logstr,thisFileName,__LINE__,a,b,c,d,e);\
	}
  /* continuation macros */
  #define COSP_LOG_DECC0(a) {\
	if (acse_debug_sel & COSP_LOG_DEC)\
	  _slogc (sLogCtrl,a);\
	}
  #define COSP_LOG_DECC1(a,b) {\
	if (acse_debug_sel & COSP_LOG_DEC)\
	  _slogc (sLogCtrl,a,b);\
	}
  /* hex logging */
  #define COSP_LOG_DECH(a,b) {\
	if (acse_debug_sel & COSP_LOG_DEC_HEX)\
	  _slogHex (sLogCtrl,a,b);\
	}
#else
  /*--------------------------------------------*/
  /* hard errors logging			*/
  /*--------------------------------------------*/

  #define COSP_LOG_ERR0(a)
  #define COSP_LOG_ERR1(a,b)
  #define COSP_LOG_ERR2(a,b,c)
  #define COSP_LOG_ERR3(a,b,c,d)
  #define COSP_LOG_ERRC0(a)
  #define COSP_LOG_ERRC1(a,b)
  #define COSP_LOG_ERRC2(a,b,c)
  #define COSP_LOG_ERRH(a,b)

  /*--------------------------------------------*/
  /* SS-user req and rsp logging		*/
  /*--------------------------------------------*/

  #define COSP_LOG_ENC0(a)
  #define COSP_LOG_ENC1(a,b)
  #define COSP_LOG_ENC2(a,b,c)
  #define COSP_LOG_ENC3(a,b,c,d)
  #define COSP_LOG_ENC4(a,b,c,d,e)
  #define COSP_LOG_ENCC0(a)
  #define COSP_LOG_ENCC1(a,b)
  #define COSP_LOG_ENCH(a,b)

  /*--------------------------------------------*/
  /* SS-user ind and cnf logging		*/
  /*--------------------------------------------*/

  #define COSP_LOG_DEC0(a)
  #define COSP_LOG_DEC1(a,b)
  #define COSP_LOG_DEC2(a,b,c)
  #define COSP_LOG_DEC3(a,b,c,d)
  #define COSP_LOG_DEC4(a,b,c,d,e)
  #define COSP_LOG_DECC0(a)
  #define COSP_LOG_DECC1(a,b)
  #define COSP_LOG_DECH(a,b)

#endif


#ifdef __cplusplus
}
#endif

#endif  /* end of 'already included' 	*/

/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*      	      2003 - 2004, All Rights Reserved.		        */
/*									*/
/* MODULE NAME : mmslusec.h						*/
/* PRODUCT(S)  : MMS-EASE Lite with LITESECURE				*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/* 		Prototypes for Security related user functions.		*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 01/20/04  EJV     03    ulFreeAssocSecurity: del cc param.		*/
/* 01/06/04  EJV     02    Merged with  MMS-EASE mms_usec.h.		*/
/* 07/08/03  EJV     01    Adopted from MMS-EASE mms_usec.h.		*/
/************************************************************************/
#ifndef MMS_USEC_H
#define MMS_USEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------*/
/* NOTE: The MMS-EASE Lite Secured applications (Client, Server) 	*/
/*	 are designed to work with Security Toolkit for MMS-EASE Lite	*/
/*	 (LITESECURE-000-001).						*/
/*----------------------------------------------------------------------*/

#if defined(S_SEC_ENABLED)

#include "acseauth.h"
#include "ssec.h"


ST_RET ulSetSecurityCalling (ST_CHAR            *locArName,
			    ST_CHAR            *remArName,
			    S_SEC_LOC_AR      **locArSecOut,
			    S_SEC_REM_AR      **remArSecOut,
                            ACSE_AUTH_INFO     *locAuthInfo,
                            S_SEC_ENCRYPT_CTRL *encryptCtrl);
ST_RET ulCheckSecureAssocConf (MVL_NET_INFO *cc);
ST_RET ulCheckSecureAssocInd (MVL_NET_INFO *cc, ACSE_AUTH_INFO *rspAuthInfo);
ST_RET ulFreeAssocSecurity (ACSE_AUTH_INFO *authInfo);
ST_RET ulCheckSecurityConfiguration (ST_VOID);

#endif /* defined(S_SEC_ENABLED) */

#ifdef __cplusplus
}
#endif

#endif  /* MMS_USEC_H */

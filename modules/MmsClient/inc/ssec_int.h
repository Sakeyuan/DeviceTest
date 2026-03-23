/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*      (c) Copyright Systems Integration Specialists Company, Inc.,    */
/*      	 2003 - 2003, All Rights Reserved                       */
/*                                                                      */
/* MODULE NAME : ssec_int.h	                                        */
/* PRODUCT(S)  :                                                        */
/*                                                                      */
/* MODULE DESCRIPTION :                                                 */
/*	This module contains internal security functions, defines,...	*/
/*	that are not exposed to user.					*/
/*	It also contains function that are passing GEN_SOCK parameter.	*/
/*	Having these protos in ssec.h caused compile conflicts in	*/
/*	project using old gensock.h					*/
/*                                                                      */
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :                            */
/*                                                                      */
/* MODIFICATION LOG :                                                   */
/*  Date     Who   Rev     Comments                                     */
/* --------  ---  ------   -------------------------------------------  */
/* 08/25/03  EJV    01     Moved protos with GEN_SOCK from ssec.h	*/
/************************************************************************/

#ifndef SSEC_INT_INCLUDED
#define SSEC_INT_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "gensock2.h"


/* internal functions for secure socket interface */
ST_RET setGenSockSSL (GEN_SOCK_CONFIG *sockCfg);
ST_RET sSecGetCipherSuite (GEN_SOCK *pSock, ST_INT *cipherSuiteOut);
ST_RET sSecGetCertId (GEN_SOCK *pSock, ST_INT *cfgIdOut);
ST_RET sSecGetCertCtrl (GEN_SOCK *pSock, S_CERT_CTRL **certCtrlOut);


/************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* SSEC_INT_INCLUDED */
/************************************************************************/

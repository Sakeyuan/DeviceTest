/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	1997, All Rights Reserved					*/
/*									*/
/*			PROPRIETARY AND CONFIDENTIAL			*/
/*									*/
/* MODULE NAME : copp.h 						*/
/* PRODUCT(S)  :							*/
/*									*/
/* MODULE DESCRIPTION :							*/
/*	COPP internal header file.					*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev     Comments					*/
/* --------  ---  ------   -------------------------------------------  */
/* 12/11/01  JRB    04     Convert to use ASN1R.			*/
/* 02/20/98  JRB    03     Chg abort_reason to ST_INT8 too.		*/
/* 12/22/97  JRB    02     Use ST_INT8.					*/
/* 05/27/97  JRB   7.00    MMSEASE 7.0 release.				*/
/* 03/05/97  JRB    01     Created.					*/
/************************************************************************/

#ifndef COPP_INCLUDED
#define COPP_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "copp_usr.h"
#include "copp_log.h"

	/*======================================================*/
	/*	C O N N E C T I O N   S T A T E S		*/
	/*======================================================*/

/* Valid states, the first IDLE state must be 0) */
#define	COPP_STATE_IDLE			0
#define	COPP_STATE_AWAIT_CPA		1
#define	COPP_STATE_AWAIT_CON_RSP	2
#define	COPP_STATE_CONNECTED		3

	/*======================================================*/
	/*	PRESENTATION INTERNAL FUNCTIONS			*/
	/*======================================================*/

/* Function to encode and send ARP PPDU.				*/
ST_VOID copp_p_abort_req (ACSE_CONN *acse_conn, ST_INT8 abort_reason, ST_INT8 event_id);
ST_VOID START_p_user_data (ASN1_DEC_CTXT *aCtx);

	/*======================================================*/
	/*	PRESENTATION INTERNAL VARIABLES			*/
	/*======================================================*/

extern ST_UCHAR only_loc_psel [];	/* Local len & PSEL	*/
extern ST_BOOLEAN p_user_data_is_outer;	/* Is P-User-data outermost constr?*/
					/* SD_TRUE or SD_FALSE		*/

/************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* COPP_INCLUDED */
/************************************************************************/


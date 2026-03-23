/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	1997-2001, All Rights Reserved					*/
/*									*/
/*			PROPRIETARY AND CONFIDENTIAL			*/
/*									*/
/* MODULE NAME : copp_usr.h 						*/
/* PRODUCT(S)  :							*/
/*									*/
/* MODULE DESCRIPTION :							*/
/*	COPP user header file.						*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev     Comments					*/
/* --------  ---  ------   -------------------------------------------  */
/* 12/11/01  JRB    05     Convert to use ASN1R.			*/
/* 08/13/98  JRB    04     Lint cleanup.				*/
/* 06/17/98  JRB    03     Add error codes.				*/
/* 05/27/97  JRB   7.00    MMSEASE 7.0 release.				*/
/* 03/19/97  JRB    02     Add "CALLING" support.  General cleanup.	*/
/* 03/05/97  JRB    01     Created.					*/
/************************************************************************/

#ifndef COPP_USR_INCLUDED
#define COPP_USR_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

	/*======================================================*/
	/*	PRESENTATION USER DEFINES			*/
	/*							*/
	/*======================================================*/
/* Defines used for encoded values of "Provider-reason".		*/
/* Used in encode/decode of CPR (Connect Presentation Reject PPDU).	*/
#define PROV_REASON_NOT_SPECIFIED	0
#define PROV_REASON_CONGESTION		1
#define PROV_REASON_LOCAL_LIMIT		2
#define PROV_REASON_CALLED_PRES_ADDR	3
#define PROV_REASON_VERSION		4
#define PROV_REASON_DEFAULT_CONTEXT	5
#define PROV_REASON_USER_DATA		6
#define PROV_REASON_NO_PSAP		7

/* Defines for P-CONNECT.cnf result parameter		*/
#define	P_CON_RESULT_ACCEPT		0
#define P_CON_RESULT_USER_REJ		1
#define P_CON_RESULT_PROVIDER_REJ	2

	/*======================================================*/
	/*	PRESENTATION ERROR CODES			*/
	/*							*/
	/*======================================================*/

/* NOTE: Values begin from E_COPP (found in glberror.h).		*/

/* COPP general errors */
#define	COPP_ERR_INV_PSEL	0x3101	/* Invalid local PSEL		*/
#define	COPP_ERR_INV_STATE	0x3102	/* Invalid connect state	*/

	/*======================================================*/
	/*	PRESENTATION GLOBAL VARIABLES			*/
	/*							*/
	/*======================================================*/
extern ST_CHAR expected_pdv_pci;
extern ST_UCHAR *pdv_data_ptr;
extern ST_INT pdv_data_len;

	/*======================================================*/
	/*	PRESENTATION PROVIDER FUNCTIONS			*/
	/*							*/
	/*	Called by user to encode and send		*/
	/*	Presentation PDUs.				*/
	/*======================================================*/

/************************************************************************/
/*			copp_con_req					*/
/* P-Connect Request.							*/
/************************************************************************/
ST_RET copp_con_req (ST_LONG copp_bind_id, ACSE_CONN *acse_conn, PRES_ADDR *rem_addr);

/************************************************************************/
/*			copp_rel_req					*/
/* P-Release Request.							*/
/************************************************************************/
ST_RET copp_rel_req (ACSE_CONN *acse_conn);

/************************************************************************/
/*			copp_con_rsp_pos				*/
/* P-Connect Accept.							*/
/************************************************************************/
ST_RET copp_con_rsp_pos (ACSE_CONN *acse_conn);

/************************************************************************/
/*			copp_con_rsp_neg				*/
/* P-Connect Reject.							*/
/* If "provider_reason" < 0, this is "user-reject", else this is	*/
/* "provider-reject" and the value of "provider_reason" will be		*/
/* encoded in the "Provider-reason" parameter of the PPDU.		*/
/************************************************************************/
ST_RET copp_con_rsp_neg (ACSE_CONN *acse_conn, ST_INT provider_reason);

/************************************************************************/
/*			copp_rel_rsp_pos				*/
/* P-Release Positive Response.						*/
/************************************************************************/
ST_RET copp_rel_rsp_pos (ACSE_CONN *acse_conn);

/************************************************************************/
/*			copp_u_abort_req				*/
/* P-U-Abort Request.							*/
/************************************************************************/
ST_RET copp_u_abort_req (ACSE_CONN *acse_conn);

/************************************************************************/
/*			copp_data_req					*/
/* P-Data Request.							*/
/************************************************************************/
ST_RET copp_data_req (ACSE_CONN *acse_conn);


	/*======================================================*/
	/*	PRESENTATION USER FUNCTIONS			*/
	/*							*/
	/*	Called by Presentation to pass decoded		*/
	/*	Presentation PDUs up to user.			*/
	/*======================================================*/

/************************************************************************/
/*			u_copp_con_cnf					*/
/* P-CONNECT.cnf (Connect Confirm).					*/
/* Parameters:								*/
/*	acse_conn	Pointer to connection info			*/
/*	result		P_CON_RESULT_ACCEPT, P_CON_RESULT_USER_REJ or	*/
/*			P_CON_RESULT_PROVIDER_REJ			*/
/*	reason		Provider-reason (if result=P_CON_RESULT_PROVIDER_REJ)*/
/************************************************************************/
ST_VOID u_copp_con_cnf (ACSE_CONN *acse_conn, ST_INT result, ST_INT reason);

/************************************************************************/
/*			u_copp_rel_cnf_pos				*/
/* P-RELEASE.cnf+ (POSITIVE Release Confirm).				*/
/************************************************************************/
ST_VOID u_copp_rel_cnf_pos (ACSE_CONN *acse_conn);

/************************************************************************/
/*			u_copp_con_ind					*/
/* P-Connect Indication.						*/
/************************************************************************/
ST_VOID u_copp_con_ind (ST_LONG user_bind_id, ACSE_CONN *acse_conn);

/************************************************************************/
/*			u_copp_rel_ind					*/
/* P-Release Indication.						*/
/************************************************************************/
ST_VOID u_copp_rel_ind (ACSE_CONN *acse_conn);

/************************************************************************/
/*			u_copp_p_abort_ind				*/
/* P-P-Abort Indication.						*/
/************************************************************************/
ST_VOID u_copp_p_abort_ind (ACSE_CONN *acse_conn, ST_INT reason);

/************************************************************************/
/*			u_copp_u_abort_ind				*/
/* P-U-Abort Indication.						*/
/************************************************************************/
ST_VOID u_copp_u_abort_ind (ACSE_CONN *acse_conn);

/************************************************************************/
/*			u_copp_data_ind					*/
/* P-Data Indication.							*/
/************************************************************************/
ST_VOID u_copp_data_ind (ACSE_CONN *acse_conn);

/************************************************************************/
/*			START_pdv_list					*/
/* ASN.1 decode function that may be used by Presentation-user		*/
/* (i.e. ACSE) for decoding a "PDV-list" (same encoding as "EXTERNAL").	*/
/************************************************************************/
ST_VOID START_pdv_list (ASN1_DEC_CTXT *aCtx);

/************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* COPP_USR_INCLUDED */
/************************************************************************/


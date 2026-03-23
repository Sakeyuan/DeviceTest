#include "glbtypes.h"
#include "sysincs.h"
#include "signal.h"
#include "mmsdefs.h"
#include "mms_pvmd.h"
#include "mms_pvar.h"
#include "mms_vvar.h"
#include "mms_err.h"
#include "mms_pcon.h"
#include "asn1defs.h"
#include "mmsop_en.h"

#include "mvl_acse.h"
#include "mvl_log.h"
#include "tp4api.h"
#include "clntobj.h"
#include "client.h"
#include "interface.h"


#define		TIMEOUT_SECONDS		15




/************************************************************************/
/* For debug version, use a static pointer to avoid duplication of 	*/
/* __FILE__ strings.							*/
/************************************************************************/
#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif


/************************************************************************/
/************************************************************************/
//extern	HWND	mainWnd;
extern	func_rpt_process	rpt_process;		//报告处理回调函数


ST_BOOLEAN stopWait = SD_FALSE;

ST_VOID doCommService()
{
#if defined (MOSI)		/* If stack is MOSI, use events		*/
    wait_any_event (1000);	/* Wait 1000 milliseconds		*/
    while (mvl_comm_serve ())	/* Perform communications service 	*/
	{				/* Loop until "mvl_comm_serve" returns 0*/
	}
#else
    mvl_comm_serve ();		/* Perform communications service 	*/
#endif
}

ST_RET waitReqDone(MVL_REQ_PEND *req, ST_INT timeout)
{
	int ret = 0;

	ST_DOUBLE stopTime = sGetMsTime() + (ST_DOUBLE) timeout * 1000.0;

	while (req->done == SD_FALSE)		/* wait until done	*/
    {
		if (timeout != 0  &&  sGetMsTime() > stopTime)
		{
			req->result = MVL_ERR_USR_TIMEOUT;
			ret = -20;	//超时
			break;
		}

		if( stopWait )	/* stop waiting	*/
		{
			stopWait = SD_FALSE;
			req->result = SD_FAILURE;
			ret = -10;	//中止
			break;
		}

		Sleep(20);
//		doCommService ();	/* wait for events if possible & call mvl_comm_serve*/
	}

	//if (ret == 0 && req->result != 0) ret = -99;
	if (ret == 0 && req->result != 0)
	{
		if (req->event)
			ret = -100 - req->event->u.mms.pdu[req->event->u.mms.pdu_len - 1];
		else
			ret = -99;
	}

	return ret;
}

//连接61850服务器
MVL_NET_INFO *connectToServer(ST_CHAR *serverARName)
{
	ST_RET ret;
	INIT_INFO			callingInitInfo;
	INIT_INFO			initRespInfo;
	MVL_NET_INFO		*clientNetInfo = NULL;
	MVL_REQ_PEND		*reqCtrl;
	ACSE_AUTH_INFO		*authInfo = NULL;		// conn authentication info
	S_SEC_ENCRYPT_CTRL	*encryptCtrl = NULL;	// conn enctryption info
	
	callingInitInfo.mms_p_context_pres = SD_TRUE;
	callingInitInfo.max_segsize_pres = SD_TRUE;
	callingInitInfo.max_segsize = mvl_cfg_info->max_msg_size;
	callingInitInfo.maxreq_calling = 1;
	callingInitInfo.maxreq_called = 1;
	callingInitInfo.max_nest_pres = SD_TRUE;
	callingInitInfo.max_nest = 5;
	callingInitInfo.mms_detail_pres = SD_TRUE;
	callingInitInfo.version = 1;
	callingInitInfo.num_cs_init = 0;
	callingInitInfo.core_position = 0;
	callingInitInfo.param_supp[0] = m_param[0];
	callingInitInfo.param_supp[1] = m_param[1];
	memcpy (callingInitInfo.serv_supp, m_service_resp,11);
	
	ret = mvla_initiate_req_ex (serverARName, &callingInitInfo, &initRespInfo, 
		&clientNetInfo, &reqCtrl, authInfo, encryptCtrl);
	
	if( ret == SD_SUCCESS )
    {
		ret = waitReqDone (reqCtrl, TIMEOUT_SECONDS * 2);  /* need to wait longer on connect */
    }
	
	if( ret != SD_SUCCESS )	clientNetInfo = NULL;
	
	mvl_free_req_ctrl (reqCtrl);
	return clientNetInfo;
}

//断开61850服务器
ST_RET disconnectFromServer(MVL_NET_INFO *clientNetInfo)
{
	MVL_REQ_PEND *reqCtrl;
	
	mvla_concl (clientNetInfo, &reqCtrl);
	waitReqDone (reqCtrl, TIMEOUT_SECONDS);
	mvl_free_req_ctrl (reqCtrl);
	return (SD_SUCCESS);
}
/************************************************************************/



/************************************************************************/
/*			u_mvl_connect_ind_ex				*/
/*----------------------------------------------------------------------*/
/* This function is called when a remote node has connected to us. We	*/
/* can look at the assReqInfo to see who it is (assuming that the 	*/
/* AP-Titles are used), or at the cc->rem_init_info to see initiate 	*/
/* request parameters.							*/
/************************************************************************/
extern ST_ACSE_AUTH u_mvl_connect_ind_ex (MVL_NET_INFO *cc, INIT_INFO *init_info,
                   ACSE_AUTH_INFO *req_auth_info, ACSE_AUTH_INFO *rsp_auth_info)
{
	ST_RET ret = ACSE_AUTH_SUCCESS;

	#if defined(S_SEC_ENABLED)
	/* this Client will reject the connection since there is no security	*/
	/* checking code in place (see Server for sample)			*/
	ret = ACSE_DIAG_NO_REASON;
	#elif defined(ACSE_AUTH_ENABLED)
	/* this Client will reject the connection since there is no password	*/
	/* checking code in place (see Server for sample)			*/
	ret = ACSE_DIAG_NO_REASON;
	#endif

	return (ret);
}

/************************************************************************/
/*			u_mvl_connect_cnf_ex   				*/
/*----------------------------------------------------------------------*/
/* This function is called when we have received an initiate response.	*/
/* Depending on the server's authentication scheme, we may have been 	*/
/* sent responding authentication that we can pull out of the response 	*/
/* PDU.									*/
/************************************************************************/

ST_ACSE_AUTH u_mvl_connect_cnf_ex (MVL_NET_INFO *cc, AARE_APDU *ass_rsp_info)
{
	ST_RET ret = ACSE_AUTH_SUCCESS;

	#if defined(S_SEC_ENABLED)
	/* check security parameters of the Associate Confirm			*/
	ret = ulCheckSecureAssocConf (cc);
	#elif defined(ACSE_AUTH_ENABLED)
	{
	ACSE_AUTH_INFO *rsp_auth_info;

	rsp_auth_info = &ass_rsp_info->auth_info;

	if(rsp_auth_info->auth_pres == SD_TRUE)
	{
		/* Looks like we have some authentication to look at, simply print  */
		/* the password and continue as normal.				*/
		if(rsp_auth_info->mech_type == ACSE_AUTH_MECH_PASSWORD)
		{
			printf("\nPassword recieved from peer: %s\n", rsp_auth_info->u.pw_auth.password);
		}
		/* We were sent a mechanism we don't support, let's reject the 	*/
		/* the connection with the appropriate diagnostic.			*/
		else
		{
			ret = ACSE_DIAG_AUTH_MECH_NAME_NOT_RECOGNIZED;
		}
	}
	else
	{
		/* Hmm... looks like we weren't sent any authentication even though */
		/* we require it. Let's reject with the appropriate diagnostic.	*/
		ret = ACSE_DIAG_AUTH_REQUIRED;
	}
	}
	#endif /* defined(ACSE_AUTH_ENABLED) */

	/* to accept the confirm ACSE_AUTH_SUCCESS need to be returned	*/
	return (ret);
}


/************************************************************************/
/*			disc_ind_fun					*/
/************************************************************************/
/* This function is called when connection is terminated.		*/

#if 0
static ST_VOID disc_ind_fun (MVL_NET_INFO *cc, ST_INT discType)
{
	/* Free up rcb_info if necessary.	*/
	if (cc->user_info)
	{
		rcb_info_destroy ((RCB_RPT *)cc->user_info);
		cc->user_info=NULL;
	}

	cc->rem_vmd = NULL;
}
#endif

#if (MMS_IDENT_EN & RESP_EN)
/************************************************************************/
/*			u_mvl_ident_ind					*/
/************************************************************************/
IDENT_RESP_INFO identify_response_info;

ST_VOID u_mvl_ident_ind (MVL_IND_PEND *indCtrl)
{
#if 0	/* enable this to print when Ind received		*/
	printf ("\n Identify Indication received.");
#endif
	indCtrl->u.ident.resp_info = &identify_response_info;
	mplas_ident_resp (indCtrl);
}
#endif	/* #if (MMS_IDENT_EN & RESP_EN)	*/


#if (MMS_FOPEN_EN & RESP_EN)
/************************************************************************/
/*			u_mvl_fopen_ind					*/
/************************************************************************/
ST_VOID u_mvl_fopen_ind (MVL_IND_PEND *indCtrl)
{
	FILE *fp;
	FOPEN_RESP_INFO resp_info;
	struct stat  stat_buf;

	fp = fopen (indCtrl->u.fopen.filename, "rb");	/* CRITICAL: use "b" flag for binary transfer*/
	if (fp == NULL)
	{
		_mplas_err_resp (indCtrl,11,6);		/* File-access denied	*/
		return;
	}
	if (fseek (fp, indCtrl->u.fopen.init_pos, SEEK_SET))
	{
		_mplas_err_resp (indCtrl,11,5);		/* Position invalid	*/
		return;
	}

	/* WARNING: this only works if (FILE *) is a 32-bit pointer.		*/
	resp_info.frsmid = (ST_INT32) fp;

	if (fstat (fileno (fp), &stat_buf))
	{					/* Can't get file size or time	*/
		_mplas_err_resp (indCtrl,11,0);	/* File Problem, Other		*/
		return;
	}
	else
	{
		resp_info.ent.fsize    = stat_buf.st_size;
		resp_info.ent.mtimpres = SD_TRUE;
		resp_info.ent.mtime    = stat_buf.st_mtime;
	}

	indCtrl->u.fopen.resp_info = &resp_info;
	mplas_fopen_resp (indCtrl);
}
#endif 	/* MMS_FOPEN_EN & RESP_EN	*/

#if (MMS_FREAD_EN & RESP_EN)
/************************************************************************/
/*			u_mvl_fread_ind					*/
/************************************************************************/
ST_VOID u_mvl_fread_ind (MVL_IND_PEND *indCtrl)
{
	FILE *fp;
	ST_UCHAR *tmp_buf;
	MVLAS_FREAD_CTRL *fread_ctrl = &indCtrl->u.fread;
	FREAD_RESP_INFO resp_info;

	fp = (FILE *) fread_ctrl->req_info->frsmid;
	/* Do NOT read more than "max_size".				*/
	tmp_buf = (ST_UCHAR *) chk_malloc (fread_ctrl->max_size);

	resp_info.fd_len = fread (tmp_buf, 1, fread_ctrl->max_size, fp);
	if (resp_info.fd_len == 0  &&  ferror (fp))
	{
		_mplas_err_resp (indCtrl, 3, 0);
		return;
	}

	resp_info.filedata = tmp_buf;
	if (resp_info.fd_len == fread_ctrl->max_size)
		resp_info.more_follows = SD_TRUE;
	else
		resp_info.more_follows = SD_FALSE;

	fread_ctrl->resp_info = &resp_info;
	mplas_fread_resp (indCtrl);
	chk_free (tmp_buf);		/* Temporary buffer	*/
}
#endif	/* #if (MMS_FREAD_EN & RESP_EN)	*/

#if (MMS_FCLOSE_EN & RESP_EN)
/************************************************************************/
/*			u_mvl_fclose_ind				*/
/************************************************************************/
ST_VOID u_mvl_fclose_ind (MVL_IND_PEND *indCtrl)
{
	FILE *fp;
	MVLAS_FCLOSE_CTRL *fclose_ctrl = &indCtrl->u.fclose;

	fp = (FILE *) fclose_ctrl->req_info->frsmid;

	if (fclose (fp))
		_mplas_err_resp (indCtrl, 11, 0);	/* File problem, other	*/
	else
		mplas_fclose_resp (indCtrl);
}
#endif	/* #if (MMS_FCLOSE_EN & RESP_EN)	*/


/************************************************************************/
/*                       named_var_read					*/
/* Read a single named variable.					*/
/*   scope = VMD_SPEC, DOM_SPEC, or AA_SPEC				*/
/* CRITICAL: the local variable "parse_info" is written indirectly 	*/
/*           from waitReqDone when the response is received. The call	*/
/*           to "waitReqDone" MUST NOT be moved outside this function.	*/
/************************************************************************/
ST_RET named_var_read (MVL_NET_INFO *net_info, ST_CHAR *varName,
		ST_INT scope, ST_CHAR *domName,
		ST_INT type_id, ST_VOID *dataDest, ST_INT timeOut)
{
	ST_INT num_data;
	ST_CHAR buffer[512];
	MVL_READ_RESP_PARSE_INFO parse_info;
	READ_REQ_INFO *req_info;
	VARIABLE_LIST *vl;
	ST_INT ret;
	MVL_REQ_PEND *reqCtrl;

	/* Create a read request info struct  */
	req_info = (READ_REQ_INFO *) buffer;
	req_info->spec_in_result = SD_FALSE;
	req_info->va_spec.var_acc_tag = VAR_ACC_VARLIST;
	req_info->va_spec.num_of_variables = 1;
	vl = (VARIABLE_LIST *) (req_info + 1);

	vl->alt_access_pres = SD_FALSE;
	vl->var_spec.var_spec_tag = VA_SPEC_NAMED;
	vl->var_spec.vs.name.object_tag = scope;	/* set scope	*/
	if (scope == DOM_SPEC)
	vl->var_spec.vs.name.domain_id = domName;	/* set domain name	*/
	vl->var_spec.vs.name.obj_name.vmd_spec = varName;

	num_data = 1;     /* Number of named variables returned		*/

	/* IMPORTANT: start with clean structure, then set appropriate elements.*/
	memset (&parse_info, 0, sizeof (parse_info));
	parse_info.dest = dataDest;
	parse_info.type_id = type_id;
	parse_info.descr_arr = SD_FALSE;

	/* Send read request. */
	ret = mvla_read_variables (net_info, req_info, num_data, &parse_info, &reqCtrl);

	/* If request sent successfully, wait for reply.	*/
	if (ret == SD_SUCCESS)
		ret = waitReqDone (reqCtrl, timeOut);
	else
		ret = -2;

	if (ret == SD_SUCCESS)	/* response received OK.	*/
	{
		if( parse_info.result != SD_SUCCESS )	/* return single variable result	*/
		{
			ret = -100 - reqCtrl->event->u.mms.pdu[reqCtrl->event->u.mms.pdu_len - 1];
		}
	}

	mvl_free_req_ctrl (reqCtrl);
	return (ret);
}

/************************************************************************/
/*			named_var_write					*/
/* Write a single named variable.					*/
/*   scope = VMD_SPEC, DOM_SPEC, or AA_SPEC				*/
/* CRITICAL: the local variable "wr_info" is written indirectly 	*/
/*           from waitReqDone when the response is received. The call	*/
/*           to "waitReqDone" MUST NOT be moved outside this function.	*/
/************************************************************************/
ST_RET named_var_write (MVL_NET_INFO *netInfo, ST_CHAR *varName,
		ST_INT scope, ST_CHAR *domName,
		ST_INT type_id,	ST_VOID *dataSrc, ST_INT timeOut)
{
	ST_CHAR buffer[512];
	MVL_WRITE_REQ_INFO *wr_info;
	WRITE_REQ_INFO *req_info;
	VARIABLE_LIST *vl;
	ST_RET ret;
	MVL_REQ_PEND *reqCtrl;

	req_info = (WRITE_REQ_INFO *) buffer;
	req_info->num_of_data = 1;
	req_info->va_spec.var_acc_tag = VAR_ACC_VARLIST;
	req_info->va_spec.num_of_variables = 1;
	vl = (VARIABLE_LIST *) (req_info + 1);

	vl->alt_access_pres = SD_FALSE;
	vl->var_spec.var_spec_tag = VA_SPEC_NAMED;
	vl->var_spec.vs.name.object_tag = scope;	/* set scope	*/
	if (scope == DOM_SPEC)
	vl->var_spec.vs.name.domain_id = domName;	/* set domain name	*/
	vl->var_spec.vs.name.obj_name.vmd_spec = varName;

	/* Alloc array of structs. Here only one var so alloc one struct.	*/
	/* To read multiple vars, allocate more.				*/
	/* CRITICAL: response code writes to this struct. Do not free until	*/
	/*           response received.					*/
	wr_info = chk_calloc (1, sizeof (MVL_WRITE_REQ_INFO));

	wr_info->local_data = dataSrc;
	wr_info->type_id = type_id;
	wr_info->arr = SD_FALSE;

	/* Send write request.	*/
	ret = mvla_write_variables (netInfo, req_info, 1, wr_info, &reqCtrl);

	/* If request sent successfully, wait for response.	*/
	if (ret == SD_SUCCESS)
		ret = waitReqDone (reqCtrl, timeOut);
	else
		ret = -2;

	if (ret == SD_SUCCESS)	/* response received OK.	*/
	{
		if( wr_info->result != SD_SUCCESS )	/* return single variable result	*/
		{
			ret = -100 - reqCtrl->event->u.mms.pdu[reqCtrl->event->u.mms.pdu_len - 1];
		}
	}

	mvl_free_req_ctrl (reqCtrl);
	chk_free (wr_info);
	return (ret);
}

ST_RET named_var_write_multi (MVL_NET_INFO *netInfo, WR_INFO *wrInfo, ST_INT varCount,
						ST_INT scope, ST_CHAR *domName, ST_INT timeOut)
{
    MVL_REQ_PEND        *reqCtrl;
    WRITE_REQ_INFO      *req_info;
    VARIABLE_LIST       *vl;
    MVL_WRITE_REQ_INFO  *wr_info, *wr_info1;

	ST_CHAR buffer[512];
	ST_RET ret;
	ST_INT i;


	req_info = (WRITE_REQ_INFO *) buffer;
	req_info->num_of_data = varCount;
    req_info->va_spec.var_acc_tag = VAR_ACC_VARLIST;
	req_info->va_spec.num_of_variables = varCount;

    vl = (VARIABLE_LIST *) (req_info + 1);
	wr_info = chk_calloc (varCount, sizeof (MVL_WRITE_REQ_INFO));
	wr_info1 = wr_info;

	for (i = 0; i < varCount; i++)
	{
		vl->alt_access_pres = SD_FALSE;
		vl->var_spec.var_spec_tag = VA_SPEC_NAMED;
		vl->var_spec.vs.name.object_tag = scope;
		if (scope == DOM_SPEC)
			vl->var_spec.vs.name.domain_id = domName;

		vl->var_spec.vs.name.obj_name.vmd_spec = wrInfo[i].var_name;
		vl++;
		
		wr_info1->local_data = wrInfo[i].data_src;
		wr_info1->type_id = wrInfo[i].type_id;
		wr_info1->arr = SD_FALSE;
		wr_info1++;
	}

	ret = mvla_write_variables (netInfo, req_info, varCount, wr_info, &reqCtrl);
	
	/* If request sent successfully, wait for response.	*/
	if (ret == SD_SUCCESS)
		ret = waitReqDone (reqCtrl, timeOut);
	else
		ret = -2;
	
	if (ret == SD_SUCCESS)	/* response received OK.	*/
	{
		if( wr_info->result != SD_SUCCESS )	/* return single variable result	*/
		{
			ret = -100 - reqCtrl->event->u.mms.pdu[reqCtrl->event->u.mms.pdu_len - 1];
		}
	}
	
	mvl_free_req_ctrl (reqCtrl);
	chk_free (wr_info);
	return (ret);
}

ST_INT asn1_get_length(ST_UCHAR *r_asn1buf, ST_INT *ptr)
{
	ST_UCHAR tmpByte;
	ST_INT len = 0;
	ST_INT offset = 0;
	
	tmpByte = *r_asn1buf;
	if(tmpByte & 0x80)
	{
		tmpByte &= 0x7f;
		r_asn1buf += tmpByte;
		if(tmpByte == 0x01)
		{
			len = (ST_UCHAR)(*(r_asn1buf + 1));
			offset=2;
		}
		else if(tmpByte == 0x02)
		{
			*((ST_UCHAR *)&len) = *(r_asn1buf + 1);
			*((ST_UCHAR *)&len + 1) = *(r_asn1buf + 2);
			offset=3;
		}
	}
	else
	{
		len = (ST_UCHAR)(*r_asn1buf);
		offset = 1;
	}
	*ptr = len;
	return offset;
}

ST_INT asn1_get_vstr (ST_UCHAR * r_asn1buf, ST_UCHAR *vstr_ptr, ST_INT maxchars, ST_INT len)
{
	ST_INT  accepted_chars;
	if (maxchars != 0  &&  len > maxchars)
		accepted_chars = maxchars;	/* truncated */
	else
		accepted_chars = len;
	memcpy (vstr_ptr, r_asn1buf, accepted_chars);
	*(vstr_ptr + accepted_chars) = 0;
	return accepted_chars;
}

ST_INT asn1_get_bitstr (ST_UCHAR * r_asn1buf, ST_UCHAR *bit_ptr, ST_INT max_bits, ST_INT len)
{
	ST_INT unused_bits;
	ST_INT used_bits;
	ST_INT accepted_bits;
	
	unused_bits = *r_asn1buf++;
	if(max_bits == 10)
		unused_bits = 6;
	
	/* Return error code for bad unused-bits value.	*/
	if(unused_bits>7 || unused_bits<0)
		return 0;
	if(len == 1)
	{
		bit_ptr[0] = 0;
		return 0;
	}
	else
	{
		used_bits = ((len-1)*8 - unused_bits); /* Compute # data bits.	*/
		
		/* If caller imposed a limit, truncate. */
		if (max_bits != 0  &&  used_bits > max_bits)
			accepted_bits = max_bits;	/* truncated */
		else
			accepted_bits = used_bits;
		
		/* Copy bitstring to user buffer */
		bstrcpy (bit_ptr, r_asn1buf, accepted_bits);
		return accepted_bits;
	}
}

//遥信遥测报告处理
ST_VOID u_mvl_info_rpt_1(MVL_COMM_EVENT *event)
{
	ST_INT		j, k, cnt, len, offset, numDsVar;
	ST_UCHAR	*cptr;

	ST_CHAR		RptID[MAX_NAME_LEN];
	ST_CHAR		DataSetName[MAX_NAME_LEN];
	ST_UINT16	OptFldsData;		/* ptr to data part of OptFlds bvstring	*/
	ST_UINT8	InclusionData[100];	/* ptr to Inclusion bstring	*/
	ST_UCHAR	reasonCode;
	
	RPT_INFO	rpt_info[50];

	INFO_REQ_INFO *info_ptr;
	ACCESS_RESULT *ar_ptr;


	if( !rpt_process ) return;

	info_ptr = (INFO_REQ_INFO *) event->u.mms.dec_rslt.data_ptr; 
	ar_ptr = info_ptr->acc_rslt_list;

	cptr = ar_ptr->va_data.data;
	
	/* Copy RptID from Report */
	if(cptr[0] == 0x8a)
	{
		offset = asn1_get_length(ar_ptr->va_data.data+1, &len);
		asn1_get_vstr (ar_ptr->va_data.data+1+offset, (ST_UCHAR*)RptID, sizeof(RptID)-1, len);
		cptr += 1+len+offset;
	}
	
	/* Go to the OptFlds */
	if(cptr[0] == 0x84)
	{
		offset = asn1_get_length(cptr+1, &len);
		asn1_get_bitstr(cptr+1+offset, (ST_UCHAR*)&OptFldsData, 10, len);
		cptr += 1+len+offset;
	} else
		return;
	
	/* NOTE: Don't change initial entries in "info_va". Add these right after "OptFlds".*/
	if (BSTR_BIT_GET(&OptFldsData, OPTFLD_BITNUM_SQNUM))
	{
		offset = asn1_get_length(cptr+1, &len);
		cptr += 1+len+offset;
	}
	
	if (BSTR_BIT_GET(&OptFldsData, OPTFLD_BITNUM_TIMESTAMP))
	{
		offset = asn1_get_length(cptr+1, &len);
		cptr += 1+len+offset;
	}
	
	if (BSTR_BIT_GET(&OptFldsData, OPTFLD_BITNUM_DATSETNAME))
	{
		offset = asn1_get_length(cptr+1, &len);
		if(cptr[0] == 0x8a)
		{
			asn1_get_vstr (cptr+1+offset, (ST_UCHAR*)DataSetName, sizeof(DataSetName)-1, len);
		}
		cptr += 1+len+offset;
	}
	
	if (BSTR_BIT_GET (&OptFldsData, OPTFLD_BITNUM_BUFOVFL))
	{
		offset = asn1_get_length(cptr+1, &len);
		cptr += 1+len+offset;
	}
	
	if (BSTR_BIT_GET(&OptFldsData, OPTFLD_BITNUM_ENTRYID))
	{
		offset = asn1_get_length(cptr+1, &len);
		cptr += 1+len+offset;
	}
	
	if (BSTR_BIT_GET(&OptFldsData, OPTFLD_BITNUM_CONFREV))
	{
		offset = asn1_get_length(cptr+1, &len);
		cptr += 1+len+offset;
	}
	
	if (BSTR_BIT_GET (&OptFldsData,OPTFLD_BITNUM_SUBSEQNUM))
	{
		offset = asn1_get_length(cptr+1, &len);
		cptr += 1+len+offset;
		offset = asn1_get_length(cptr+1, &len);
		cptr += 1+len+offset;
	}
	
	// Perform 2nd decode (up through "Inclusion")
	if(cptr[0] == 0x84)
	{
		offset = asn1_get_length(cptr+1, &len);
		numDsVar = asn1_get_bitstr (cptr+1+offset, InclusionData, 800, len);
		cptr += 1+len+offset;
	}
	else return;

	if (BSTR_BIT_GET(&OptFldsData, OPTFLD_BITNUM_DATAREF))
	{
		for (j = 0; j < numDsVar; ++j)
		{
			if( BSTR_BIT_GET (InclusionData, j) )
			{
				offset = asn1_get_length(cptr+1, &len);
				cptr += 1+len+offset;
			}
		}
	}

	memset(rpt_info, 0, sizeof(rpt_info));
	k = 0;

	for (j = 0; j < numDsVar; ++j)
	{
		if( BSTR_BIT_GET (InclusionData, j) )
		{
			offset = asn1_get_length(cptr+1, &len);
			if (k < 50)
			{
				asn1_get_vstr(cptr+1+offset, rpt_info[k].dataBuf, sizeof(rpt_info[k].dataBuf), len);
				memcpy(rpt_info[k].dataRef, RptID, sizeof(rpt_info[k].dataRef));
				rpt_info[k].dataLen = len;
				rpt_info[k].dsmID = j;
				k++;
			}
			cptr += 1+len+offset;
		}
	}
	
	cnt = k;
	k = 0;

	if (BSTR_BIT_GET(&OptFldsData, OPTFLD_BITNUM_REASON))
	{
		for (j = 0; j < numDsVar; ++j)
		{
			if( BSTR_BIT_GET (InclusionData, j) )
			{
				offset = asn1_get_length(cptr+1, &len);
				if(cptr[0] == 0x84)
				{
					asn1_get_bitstr(cptr+1+offset, &reasonCode, 6, len);
				}
				cptr += 1+len+offset;
			
				if (k < cnt)
				{
					rpt_info[k].code = reasonCode;
					k++;
				}
			}
		}
	}

	rpt_process(1, rpt_info, cnt);
}

//遥控报告处理
ST_VOID u_mvl_info_rpt_2(MVL_COMM_EVENT *event)
{
	ST_INT j, k;

	INFO_REQ_INFO *info_ptr;
	VAR_ACC_SPEC *va_spec;
	ACCESS_RESULT *ar_ptr;
	VARIABLE_LIST *vl;
	ST_INT num_va;
	OBJECT_NAME *vobj;
	ST_CHAR *name;

	RPT_INFO rpt_info[2];

	info_ptr = (INFO_REQ_INFO *) event->u.mms.dec_rslt.data_ptr;
	va_spec = &info_ptr->va_spec;
	ar_ptr = info_ptr->acc_rslt_list;
	vl = (VARIABLE_LIST *) (info_ptr + 1);
	num_va = info_ptr->num_of_acc_result;

	memset(rpt_info, 0, sizeof(rpt_info));
	
	for (j = 0; j < num_va; j++)
	{
		if (vl->var_spec.var_spec_tag == VA_SPEC_NAMED)
		{
			vobj = &vl->var_spec.vs.name;
			name = vobj->obj_name.vmd_spec;

			if (!strcmp (name, "LastApplError"))
			{
				k = 0;
				rpt_info[k].code = 1;
			}
			else
			{
				k = 1;
				sprintf(rpt_info[k].dataRef, "%s/%s", vobj->domain_id, name);
			}

			memcpy(rpt_info[k].dataBuf, ar_ptr->va_data.data, ar_ptr->va_data.len);
			rpt_info[k].dataLen = ar_ptr->va_data.len;
		}

		vl++;
		ar_ptr++;
	}

	rpt_process(2, rpt_info, 2);
}

/************************************************************************/
/* 			u_mvl_info_rpt_ind				*/
/************************************************************************/
ST_VOID u_mvl_info_rpt_ind (MVL_COMM_EVENT *event)
{
	INFO_REQ_INFO *info_ptr;
	VAR_ACC_SPEC *va_spec;
	OBJECT_NAME *vobj;
	ST_CHAR *name;

	info_ptr = (INFO_REQ_INFO *) event->u.mms.dec_rslt.data_ptr;
	va_spec = &info_ptr->va_spec;

	if (va_spec->var_acc_tag == VAR_ACC_NAMEDLIST)
	{
		vobj = &va_spec->vl_name;
		name = vobj->obj_name.vmd_spec;

		if (!strcmp (name, "RPT"))
		{
			u_mvl_info_rpt_1(event);
		}
	}
	else if (va_spec->var_acc_tag == VAR_ACC_VARLIST)
	{
		u_mvl_info_rpt_2(event);
	}
}

/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	2003 - 2003, All Rights Reserved				*/
/*									*/
/* MODULE NAME : client.h						*/
/* PRODUCT(S)  : MMSEASE-LITE						*/
/*									*/
/* MODULE DESCRIPTION :							*/
/*	Defines for sample "client" application.			*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 12/17/03  JRB     02    61850-8-1 FDIS changes:			*/
/*			   Add ConfRev to RCB_DATA & RCB_VAR.		*/
/*			   Chg bvstring9 to bvstring10 for OptFlds.	*/
/* 10/09/03  JRB     01    New						*/
/************************************************************************/

/* Defines required by Foundry generated code.				*/
/* Default values defined in "mvl_defs.h" but we don't like the defaults*/
/* so we undefine and redefine them here.				*/


//#define MESSAGE_RPT_INFO	0x40A


#undef MVL_NUM_DYN_DOMS
#undef MVL_NUM_DYN_VMD_VARS
#undef MVL_NUM_DYN_VMD_NVLS
#undef MVL_NUM_DYN_JOUS
#undef MVL_NUM_DYN_DOM_VARS
#undef MVL_NUM_DYN_DOM_NVLS
#undef MVL_NUM_DYN_AA_VARS
#undef MVL_NUM_DYN_AA_NVLS
#undef MVLU_NUM_DYN_TYPES

#define MVL_NUM_DYN_DOMS	10
#define MVL_NUM_DYN_VMD_VARS	100
#define MVL_NUM_DYN_VMD_NVLS	10
#define MVL_NUM_DYN_JOUS	10
#define MVL_NUM_DYN_DOM_VARS	100
#define MVL_NUM_DYN_DOM_NVLS	10
#define MVL_NUM_DYN_AA_VARS	10
#define MVL_NUM_DYN_AA_NVLS	10
#define MVLU_NUM_DYN_TYPES	200	/* important for UCA	*/

/* Struct to store common type ids needed for IEC/UCA Reports.	*/
typedef struct
  {
  ST_INT mmsbool;	/* named so not confused with C++ 'bool' type	*/
  ST_INT int8u;		/* for SqNum			*/
  ST_INT int16u;
  ST_INT int32u;	/* for IntgPd			*/
  ST_INT vstring65;	/* for RptID & ObjectReference	*/
  ST_INT btime6;	/* for EntryTime		*/
  ST_INT ostring8;	/* for EntryID			*/
  ST_INT vstring32;	/* for RptId			*/
  ST_INT bvstring6;	/* for TrgOps (IEC)		*/
  ST_INT bvstring8;	/* for OptFlds,TrgOps (UCA)	*/
  ST_INT bvstring10;	/* for OptFlds (IEC)		*/
  ST_INT bstr6;		/* for Reason (IEC)		*/
  ST_INT bstr8;		/* for Reason (UCA)		*/
  ST_INT bstr9;		/* for Writing OptFlds (IEC). Can't write all 10 bits.*/
  } RPT_TYPEIDS;

typedef struct
  {
  ST_CHAR    RptID[66];		
  struct     /* BVstring */	
    {				
    ST_INT16 len_1;		
    ST_UCHAR data_1[2];		/* BVstring9 - need 2 bytes	*/
    } OptFlds;			
  ST_UINT8  SqNum;		
  MMS_BTIME6 TimeOfEntry;
  ST_CHAR    DatSetNa[66];
  ST_BOOLEAN BufOvfl;
  ST_UINT16 SubSeqNum;
  ST_BOOLEAN MoreSegmentsFollow;
  ST_UINT8 EntryID [8];		/* ostring8			*/
  ST_UINT32 ConfRev;
  ST_UINT8 *Inclusion;		/* ptr to bitstring		*/
				/* Must alloc appropriate size	*/
				/* buffer for bitstring.	*/
  ST_CHAR *dataRefName;		/* ptr to array of dataRefName	*/
  MMS_BVSTRING *Reason;		/* ptr to array of Reason bitstrings	*/
				/* WARNING: this only works for variable*/
				/* len bitstring up to 8 bits. 		*/
  } RCB_DATA;		

typedef struct
  {
  MVL_VAR_ASSOC *  RptID;
  MVL_VAR_ASSOC *  OptFlds;
  MVL_VAR_ASSOC *  SqNum;
  MVL_VAR_ASSOC *  TimeOfEntry;
  MVL_VAR_ASSOC *  DatSetNa;
  MVL_VAR_ASSOC *  BufOvfl;
  MVL_VAR_ASSOC *  SubSeqNum;
  MVL_VAR_ASSOC *  MoreSegmentsFollow;
  MVL_VAR_ASSOC *  EntryID;
  MVL_VAR_ASSOC *  ConfRev;
  MVL_VAR_ASSOC *  Inclusion;
  MVL_VAR_ASSOC ** dataRefName;	/* array of ptrs	*/
  MVL_VAR_ASSOC ** dataValue;	/* array of ptrs	*/
  MVL_VAR_ASSOC ** Reason;	/* array of ptrs	*/
  } RCB_VAR;

typedef struct
  {
  DBL_LNK link;		/* allows linked list of this struct	*/
  ST_INT numDsVar;	/* num variables in rpt dataset	*/
  ST_INT *typeIdArr;	/* array of type ids	*/
  ST_INT InclusionTypeid;	/*Type ID for Inclusion Bitstring*/
  RCB_DATA rcb_data;
  RCB_VAR rcb_var;
  } RCB_RPT;


typedef struct
{
	ST_CHAR *var_name;
	ST_INT type_id;
	ST_VOID *data_src;
} WR_INFO;


/************************************************************************/
/* Global variables.							*/
/************************************************************************/
/* NONE	*/

/************************************************************************/
/* Function prototypes.							*/
/************************************************************************/
ST_RET waitReqDone (MVL_REQ_PEND *req, ST_INT timeout);
ST_VOID doCommService (ST_VOID);


ST_RET rpt_typeids_find (RPT_TYPEIDS *rpt_typeids);

RCB_RPT *rcb_info_create (MVL_NET_INFO *net_info, ST_CHAR *domName,
	ST_CHAR *rcbName, RPT_TYPEIDS *rpt_typeids, ST_INT timeOut);
ST_VOID rcb_info_destroy (RCB_RPT *rcb_info);

ST_RET rcb_enable (MVL_NET_INFO *netInfo, ST_CHAR *domName,
	ST_CHAR *rcbName, ST_UCHAR *OptFlds, ST_UCHAR *TrgOps,
	ST_UINT32 IntgPd, RPT_TYPEIDS *rpt_typeids, ST_INT timeOut);


/* Simple functions to read/write a single variable.	*/
ST_RET named_var_read (MVL_NET_INFO *net_info, ST_CHAR *varName,
		ST_INT scope, ST_CHAR *domName,
		ST_INT type_id, ST_VOID *dataDest, ST_INT timeOut);
ST_RET named_var_write (MVL_NET_INFO *netInfo, ST_CHAR *varName,
		ST_INT scope, ST_CHAR *domName,
		ST_INT type_id,	ST_VOID *dataSrc, ST_INT timeOut);

ST_RET named_var_write_multi (MVL_NET_INFO *netInfo, WR_INFO *wrInfo, ST_INT varCount,
							  ST_INT scope, ST_CHAR *domName, ST_INT timeOut);

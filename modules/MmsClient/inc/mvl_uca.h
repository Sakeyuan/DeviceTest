/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*      	1994 - 2002, All Rights Reserved		        */
/*									*/
/* MODULE NAME : mvl_uca.h   						*/
/* PRODUCT(S)  : MMSEASE-LITE						*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*	NONE								*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 03/07/07  JRB     31    Add mvlu_get_leaf_val_int_any.		*/
/* 02/26/07  JRB     30	   initSboCtrl: add use_ms_timer arg.		*/
/*			   MVL_SBO_CTRL: add millisecond timer support.	*/
/* 02/13/07  JRB     29    mvl61850_get_rcb: del unused net_info arg.	*/
/*			   Add scan timers to MVL_RPT_CTRL. Add helper fct*/
/* 11/30/06  JRB     28    Fix *_brcb_entryid_init so user can call it.	*/
/* 11/21/06  JRB     27    Add mvl61850_ctl_lastapplerror_send.		*/
/*			   Move ..LAST_APPL_ERROR def to mvl_defs.h.	*/
/* 10/10/06  JRB     26    Add mvlu_set_leaf_param_name2.		*/
/* 09/27/06  MDE     25	   Added MMSOP_RDWR_USR_HANDLED for IOS		*/
/* 08/09/06  JRB     24	   MVL61850_BRCB_CTRL, BUFLIST_ENTRY: big changes.*/
/*			   Add mvl61850_create(free)_rpt_ctrl,		*/
/*			    mvl61850_rpt_service,			*/
/*			    mvl61850_rpt_dataset_create(destroy).	*/
/*			   Chg EntryID storage from ST_INT to Ostring.	*/
/*			   Del obsolete MVLU_RPT_VA_CTRL.		*/
/*			   Chg/add/del several internal report functions.*/
/*			   Add vstring129 to MVLU_RPT_TYPEIDS.		*/
/* 08/09/06  JRB     23    Fix MVL61850_MAX_OBJREF_LEN per Tissue 141.	*/
/* 03/27/06  JRB     22    Add more mvlu_get_leaf_* functions.		*/
/* 09/12/05  JRB     21    Add mvl61850_ctl_chk_sbow.			*/
/* 07/11/05  JRB     20    Add more "mvl61850_ctl_*" functions.		*/
/* 06/27/05  JRB     19	   Del mvlu_rpt_nvl_add/destroy.		*/
/* 06/27/05  JRB     18    _mvlu_get_rd_rcb: add (MVLU_RPT_CLIENT **) arg.*/
/*			   MVL61850_BRCB_CTRL: Add lastSentEntryID.	*/
/* 05/27/05  CRM     17    Add mvlu_rpt_destroy_scan_ctrl.		*/
/* 05/09/05  JRB     16    Define MVLU_LEAF_FUN_LOOKUP_ENABLE by default*/
/* 12/09/04  JRB     15    Add "MVL61850_CTLMODEL_*" defines.		*/
/*			   Add MVL61850_LAST_APPL.. struct.		*/
/*			   Add mvlu_trim_branch_name, mvlu_find_comp_type,*/
/*			    mvlu_get_leaf_val_*.			*/
/*			   Add mvl61850_ctl_chk_sbo, mvl61850_ctl_chk_state.*/
/*			   Add initSboCtrl.				*/
/* 09/20/04  JRB     14    More SBO changes for IEC 61850.		*/
/* 08/30/04  JRB     13    Add mvlu_sbo_chk_* prototypes.		*/
/* 07/06/04  JRB     12    Add mvlu_rpt_create_scan_ctrl2 proto.	*/
/* 06/30/04  JRB     11	   Add "prim_num", "prim_offset_base" to	*/
/*			   MVLU_RD_VA_CTRL, MVLU_WR_VA_CTRL.		*/
/*			   Del global var mvluUseStaticData.		*/
/*			   Del SCL parsing functions & related structs:	*/
/*			    mvl61850_ln_create_start, mvl61850_do_create,*/
/*			    mvl61850_da_create, mvl61850_ln_create_finish,*/
/*			    & mvl61850_ln_destroy. New SCL standard	*/
/*			    makes these obsolete.			*/
/* 05/13/04  JRB     10    Add SqNumInt16u to MVLU_BASRCB.		*/
/*			   Add define MVL61850_MAX_OBJREF_LEN.	*/
/* 04/20/04  JRB     09    Add TRGOPS_BITNUM_* defines.			*/
/* 12/17/03  JRB     08    61850-8-1 FDIS changes:			*/
/*			   MVLU_BASRCB: Add TimeofEntry for 61850 BRCB.	*/
/*			   Add OPTFLD_BITNUM_CONFREV = 8.		*/
/*			   Chg OPTFLD_BITNUM_SUBSEQNUM from 8 to 9.	*/
/*			   Increase MVLU_MAX_RPT_OPTS to 11.		*/
/* 04/22/03  JRB     07    Add comments to dynamic 61850 type functs.	*/
/* 04/17/03  JRB     06    Add mvlu_setup_scan_read.			*/
/* 04/04/03  JRB     05    Fix integrity/GI scan code so multiple	*/
/*			   concurrent scans don't corrupt one another.	*/
/*			   u_mvlu_rpt_scan_done deleted.		*/
/* 03/13/03  JRB     04    Add funcs for 61850 dynamic type creation.	*/
/*			   Add 61850 URCB support.			*/
/*			   MVLU_RPT_TYPEIDS: Use clearer member names.	*/
/*			   MVLU_RPT_CTRL: Del inclusion_data & all	*/
/*			     MVL_VAR_ASSOC vars.			*/
/*			   MVLU_BASRCB: Add "Resv".			*/
/*			   ucaName: Chg from ptr to array.		*/
/*			   mvlu_proc_rt_type: Chg to use RUNTIME_CTRL.	*/
/*			   TrgOps: Chg to Bvstring (variable len).	*/
/*			   MVLU_RPT_CLIENT: add/delete members.		*/
/*			   Add mvlu_integrity_timeout funct.		*/
/* 12/17/02  JRB     03    Chg prefix to "MVLU_STR:"			*/
/*			   Del all *typeId globals, use MVLU_RPT_TYPEIDS*/
/* 12/14/02  JRB     02    Chg mvlu_create_rpt_ctrl, mvlu_send_report args*/
/*			   Add mvlu_integrity_scan_* functions.		*/
/*			   Add callback funct u_mvlu_rpt_time_get.	*/
/*			   Chg OptFlds to BVstring9, add "bitnum" defines*/
/*			   Add defs, protos, etc. fof IEC-61850.	*/
/*			   Add ConfRev, EntryID to MVLU_BASRCB		*/
/*			   Add scan_read_ind to MVLU_RPT_CLIENT		*/
/*			   Add MVLU_RPT_TYPEIDS				*/
/*			   Del rptTim_data, rptTim_va, rptTim_typeId	*/
/*			   Del outDat_data, outDat_va, outDat_typeId	*/
/* 12/10/02  JRB     01    Created from defs moved here from mvl_defs.h	*/
/************************************************************************/
#ifndef MVL_UCA_INCLUDED
#define MVL_UCA_INCLUDED

#include "mvl_defs.h"	/* This uses many common MVL definitions.	*/

#ifdef __cplusplus
extern "C" {
#endif

/* Max number of mandatory and optional variables in IEC/UCA report.
 * IEC & UCA share RPT code, so max must accomodate both.
 * Includes RptID, OptFlds, SqNum, RptTim, OutDat (DataSetNa),
 * & InclusionBitstring (plus BufOvfl, SubSeqNum, MoreSegmentsFollow,
 * EntryId, & ConfRev for IEC only).
 */
#define MVLU_MAX_RPT_OPTS	11

#define MVL61850_MAX_OBJREF_LEN	129	/* NOTE: according to Tissue 141*/
#define MVL61850_MAX_RPTID_LEN	65

/* Defines for IEC 61850 control model.	*/
#define MVL61850_CTLMODEL_STATUS_ONLY		0
#define MVL61850_CTLMODEL_DIRECT_NORMAL		1
#define MVL61850_CTLMODEL_SBO_NORMAL		2
#define MVL61850_CTLMODEL_DIRECT_ENHANCED	3
#define MVL61850_CTLMODEL_SBO_ENHANCED		4

/************************************************************************/
/* UCA SPECIFIC DATA ELEMENTS */
/************************************************************************/

typedef struct mvlu_rd_va_ctrl
  {
  MVL_IND_PEND *indCtrl;
  MVLAS_RD_VA_CTRL *rdVaCtrl;       // 客户端读写的数据(层次可能比leaf高)va信息
  RUNTIME_TYPE *rt;                 // 读写leaf的rt信息
#if defined(MVL_UCA)
#if defined(MVL_XNAME)
  ST_CHAR xName[MAX_IDENT_LEN+1];   // 读写leaf的全名称
#endif
  ST_CHAR *primData;                // 读写leaf的SISCO数据地址
  ST_RTREF primRef;
  ST_UINT prim_num;		/* index to data*/  // 读写leaf在DATA_MAP中的索引
  ST_UINT prim_offset_base;	/* mem offset from start of "base" var	*/
#endif	/* defined(MVL_UCA)	*/
  } MVLU_RD_VA_CTRL;

typedef struct mvlu_wr_va_ctrl
  {
  MVL_IND_PEND *indCtrl;
  MVLAS_WR_VA_CTRL *wrVaCtrl;
  RUNTIME_TYPE *rt;
#if defined(MVL_UCA)
#if defined(MVL_XNAME)
  ST_CHAR xName[MAX_IDENT_LEN+1];
#endif
  ST_CHAR *primData;
  ST_RTREF primRef;
  ST_UINT prim_num;		/* index to data	*/
  ST_UINT prim_offset_base;	/* mem offset from start of "base" var	*/
#endif	/* defined(MVL_UCA)	*/
  } MVLU_WR_VA_CTRL;

ST_VOID mvlu_wr_prim_done (MVLU_WR_VA_CTRL *mvluWrVaCtrl, ST_RET rc);
ST_VOID mvlu_rd_prim_done (MVLU_RD_VA_CTRL *mvluRdVaCtrl, ST_RET rc);
ST_VOID mvlu_read_ind (MVL_IND_PEND *indCtrl);

/* These function pointers are invoked to initialize the va->data 	*/
/* element for each VariableAssociation required to handle the MMS 	*/
/* indication.								*/

extern ST_VOID(*mvluAsyncWrIndFun)(struct mvlu_wr_va_ctrl *mvluWrVaCtrl);

/* Alternate leaf handler function pointers				*/
extern ST_VOID (*u_mvlu_leaf_rd_ind_fun)(MVLU_RD_VA_CTRL *mvluRdVaCtrl);
extern ST_VOID (*u_mvlu_leaf_wr_ind_fun)(MVLU_WR_VA_CTRL *mvluWrVaCtrl);

/* Finding and setting leaf access parameters */
RUNTIME_TYPE *mvlu_find_rt_leaf (ST_INT type_id, ST_CHAR *leafName);

#define MVLU_SET_RD_FUN	0x01
#define MVLU_SET_WR_FUN	0x02
#define MVLU_SET_REF	0x04
#define MVLU_SET_ALL	(MVLU_SET_RD_FUN | MVLU_SET_WR_FUN | MVLU_SET_REF)

ST_RET mvlu_set_leaf_param (ST_INT setFlags, ST_CHAR *leafName,
  			     ST_RTINT rdIndFunIndex, ST_RTINT wrIndFunIndex,
  			     ST_RTREF ref);


/************************************************************************/
/************************************************************************/
/* Leaf Access Function Tables. To be supplied by the user.		*/

/* Comment the following line out to compile out the Foundry supplied	*/
/* Leaf Access function pointer tables, so custom tables can be used	*/
/*#define MVLU_USR_FUN_TBLS		*/

/* Remove this MVLU_LEAF_FUN_LOOKUP_ENABLE define to save memory,
 * but ONLY IF NOT mapping leaf functions at run-time (i.e. not calling
 * mvlu_set_leaf_param_name or mvlu_find_rd(wr)_ind_fun_index).
 * NOTE: this define is required if SCL configuration is used.
 */
#define MVLU_LEAF_FUN_LOOKUP_ENABLE

typedef struct
  {
#if defined MVLU_LEAF_FUN_LOOKUP_ENABLE
 ST_CHAR *fun_name;
#endif
  ST_VOID (*fun_ptr) (MVLU_RD_VA_CTRL *rdCtrl);
  } MVLU_RD_FUN_INFO;
extern MVLU_RD_FUN_INFO mvluRdFunInfoTbl[];
extern ST_INT mvluNumRdFunEntries;

typedef struct
  {
#if defined MVLU_LEAF_FUN_LOOKUP_ENABLE
  ST_CHAR *fun_name;
#endif
  ST_VOID (*fun_ptr) (MVLU_WR_VA_CTRL *wrCtrl);
  } MVLU_WR_FUN_INFO;
extern MVLU_WR_FUN_INFO mvluWrFunInfoTbl[];
extern ST_INT mvluNumWrFunEntries;

/* Useful for flexible initialization of leaf function tables */
#if defined MVLU_LEAF_FUN_LOOKUP_ENABLE
#define _MVLU_LEAF_FUN_INIT(_funName) #_funName, _funName
#else
#define _MVLU_LEAF_FUN_INIT(_funName) _funName
#endif
ST_RTINT mvlu_find_rd_ind_fun_index (ST_CHAR *funName);
ST_RTINT mvlu_find_wr_ind_fun_index (ST_CHAR *funName);


/************************************************************************/

ST_RET mvlu_set_leaf_param_name (ST_INT setFlags, ST_CHAR *leafName,
				 ST_CHAR *rdIndFunName, ST_CHAR *wrIndFunName,
				 ST_CHAR *refString);
ST_RET mvlu_set_leaf_param_name2 (ST_INT base_var_type_id,
	ST_INT setFlags,
	ST_CHAR *leafName,
	ST_CHAR *rdIndFunName,
	ST_CHAR *wrIndFunName,
	ST_CHAR *refString);
ST_RET mvlu_load_xml_leaf_file (ST_CHAR *fileName);
ST_RET u_mvlu_resolve_leaf_ref (ST_CHAR *leafName, ST_INT *setFlags,
				ST_CHAR *refText, ST_RTREF *refOut);

/* Prefix to use in XML LAP file, or when calling "mvlu_set_leaf_param_name"
 * if you want a quoted string to be saved as the Reference.
 * Following this is the string to be saved.
 * This is used for SBO select, in which case the saved string must be
 * the name of the protected element. Foundry and the sample "reference
 * resolve leaf" function look for this prefix.
 */
#define MVLU_STRING_REF_PREFIX "MVLU_STR:"

/* Internal */
ST_VOID _mvlu_null_read_ind (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID _mvlu_null_write_ind (MVLU_WR_VA_CTRL *mvluWrVaCtrl);



typedef struct
  {
  ST_CHAR ucaName [MAX_IDENT_LEN+1];
  RUNTIME_TYPE *rt;
  ST_INT sortedNum;
  ST_INT rtIndex;
  } MVLU_UCA_NAME_CTRL;

ST_RET mvlu_proc_rt_type (ST_CHAR *typeName, RUNTIME_CTRL *rtCtrl,
			  MVLU_UCA_NAME_CTRL **ucaNamesOut);

/************************************************************************/
/************************************************************************/
/* UCA REPORT CONTROL */
/************************************************************************/

#define MVLU_RPT_NUM_VA_DATA_BUF  3

/* TrgOpsvalues, also used as Reason values */
#define MVLU_TRGOPS_DATA	0x40
#define MVLU_TRGOPS_QUALITY	0x20
#define MVLU_TRGOPS_FREEZE	0x10
#define MVLU_TRGOPS_INTEGRITY	0x08	/* Bit 4	*/
#define MVLU_TRGOPS_GI		0x04	/* Bit 5	*/

/* OptFlds bit masks */
#define MVLU_SQNUM_MASK		0x40
#define MVLU_RPTTIM_MASK	0x20
#define MVLU_REASONS_MASK	0x10
#define MVLU_OUTDAT_MASK	0x08

/* TrgOps bit numbers for IEC-61850.					*/
/* Use "bit" macros (BSTR_BIT_*) to access each individual bit.		*/
#define TRGOPS_BITNUM_RESERVED			0
#define TRGOPS_BITNUM_DATA_CHANGE		1	/* "dchg" in some specs	*/
#define TRGOPS_BITNUM_QUALITY_CHANGE		2	/* "qchg" in some specs	*/
#define TRGOPS_BITNUM_DATA_UPDATE		3	/* "dupd" in some specs	*/
#define TRGOPS_BITNUM_INTEGRITY			4	/* "period" in 61850-6	*/
#define TRGOPS_BITNUM_GENERAL_INTERROGATION	5

/* OptFlds bit numbers for IEC-61850.					*/
/* Use "bit" macros (BSTR_BIT_*) to access each individual bit.		*/
/* NOTE: DATSETNAME in IEC-61850 same as OUTDAT in UCA.			*/
/* NOTE: bit numbers 1 thru 4 correspond to the masks MVLU_SQNUM_MASK,	*/
/*       MVLU_RPTTIM_MASK, MVLU_REASONS_MASK, MVLU_OUTDAT_MASK above.	*/
/*	 Bit masks don't work well beyond 8 bits.			*/
#define OPTFLD_BITNUM_RESERVED		0
#define OPTFLD_BITNUM_SQNUM		1
#define OPTFLD_BITNUM_TIMESTAMP		2
#define OPTFLD_BITNUM_REASON		3
#define OPTFLD_BITNUM_DATSETNAME	4
#define OPTFLD_BITNUM_DATAREF		5
#define OPTFLD_BITNUM_BUFOVFL		6
#define OPTFLD_BITNUM_ENTRYID		7
#define OPTFLD_BITNUM_CONFREV		8
#define OPTFLD_BITNUM_SUBSEQNUM		9	/* segmentation in 61850-8-1*/

/* Flags to pass as "rcb_type" arg to mvlu_create_rpt_ctrl.	*/
/* Saved in "rcb_type" parameter of MVLU_RPT_CTRL.		*/
#define RCB_TYPE_UCA			0
#define RCB_TYPE_IEC_BRCB		1
#define RCB_TYPE_IEC_URCB		2

/* Flags to pass as "buftim_action" arg to mvlu_create_rpt_ctrl.	*/
/* Saved in "buftim_action" parameter of MVLU_RPT_CTRL.			*/
#define MVLU_RPT_BUFTIM_REPLACE		0
#define MVLU_RPT_BUFTIM_SEND_NOW	1

/* Basic Report Control Block data */
typedef struct
  {
  ST_BOOLEAN RptEna;
  ST_BOOLEAN Resv;		/* Used only for 61850 URCB.	*/
  ST_CHAR    RptID[MVL61850_MAX_RPTID_LEN+1];
  /* NOTE: DatSetNa is shorter for UCA, but bigger buffer shouldn't hurt.*/
  ST_CHAR    DatSetNa[MVL61850_MAX_OBJREF_LEN+1];
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];		/* BVstring9 - need 2 bytes	*/
    } OptFlds;
  ST_UINT32 BufTim;
  ST_UINT16 Trgs;
  ST_UINT8  SqNum;		/* Used for UCA	& 61850 URCB	*/
  ST_UINT16 SqNumInt16u;	/* Used for 61850 BRCB		*/
  struct     /* BVstring */
    {
    ST_INT16 len;
    ST_UCHAR data[1];		/* BVstring8 - need 1 byte	*/
    } TrgOps;
  ST_UINT32 RBEPd;
  ST_UINT32 IntgPd;
  ST_UINT32 ConfRev;		/* Used only for 61850 BRCB/URCB.	*/
  ST_UCHAR EntryID[8];		/* Used only for 61850 BRCB (Ostring8).	*/
  MMS_BTIME6 TimeofEntry;	/* Used only for 61850 BRCB.	*/
  } MVLU_BASRCB;

/* UCA Report Client control */
typedef struct
  {
  DBL_LNK l;				/* Internal use			*/
  MVL_NET_INFO *netInfo;
  struct mvlu_rpt_ctrl *rpt_ctrl;	/* report control		*/
  MVLU_BASRCB basrcb;			/* report data			*/

/* Transmit timing control						*/
  ST_DOUBLE next_integ_rpt_time;
  ST_DOUBLE next_rbe_rpt_time;
  ST_DOUBLE buf_time_done;
  ST_BOOLEAN integ_scan_in_progress;

/* Data state control */
  ST_UINT16 numTrgs;
  ST_UINT8 *reasons_data;	/* array of reasons 	*/
  ST_UINT8 *changed_flags;	/* bitstring 		*/
  ST_UINT8 *segmented_inclusion;/* inclusion bitstring for segmented rpt*/
  MVL_IND_PEND *scan_read_ind;	/* Indication to pass to u_mvl_read_ind for scan*/
  } MVLU_RPT_CLIENT;

/************************************************************************/
/* Structures for saving Buffered report data.				*/
/************************************************************************/
/* VAR_DATA - data for one variable of a Report Dataset.		*/
typedef struct var_data
  {
  ST_VOID *data_ptr;		/* ptr to raw MMS Variable data		*/
				/* (allocated)				*/
  ST_INT data_len;		/* length of raw MMS Variable data	*/
  ST_UINT8 reason_for_incl;	/* reason for inclusion			*/
  } VAR_DATA;

/* BUFLIST_ENTRY - data for one buffered rpt (stored on linked list).	*/
/* Data in this struct usually changes with each Report, so must be	*/
/* saved in the buffer. Other data may be taken directly from the RCB	*/
/* when a Report is sent.						*/
typedef struct buflist_entry
  {
  /* CRITICAL: First 2 parameters used to add this struct to linked	*/
  /* lists using list_add_last, etc.					*/
  struct buflist_entry *next;		/* CRITICAL: DON'T MOVE.	*/
  struct buflist_entry *prev;		/* CRITICAL: DON'T MOVE.	*/
  ST_UCHAR EntryID[8];		/* Rpt EntryID (Ostring8)		*/
  MMS_BTIME6 TimeOfEntry;	/* Rpt TimeOfEntry			*/
  ST_INT num_var;		/* Num of var in var_data array		*/
  VAR_DATA *var_data;		/* Ptr to array of structs, one for each*/
				/* var (allocated)			*/
  ST_INT *asn1_len_array;	/* Array of ASN.1 lengths, one for each	*/
				/* var in Dataset (allocated)		*/
  ST_INT cur_va_index;		/* Index to next var in Dataset to send	*/
				/* (used when segmenting)		*/
  ST_UINT16 SubSeqNum;		/* SubSeqNum of next segment to send	*/
  } BUFLIST_ENTRY;

/*	MVL61850_BRCB_CTRL	*/
typedef struct
  {
  /* Optional parameters to send in rpt (if appropriate OptFlds bit set).*/
  ST_BOOLEAN BufOvfl;
  /* Internal parameters				*/
  BUFLIST_ENTRY *rpt_list;	/* Linked list of buffered reports	*/
  BUFLIST_ENTRY *rpt_list_next;	/* Next rpt to send from "rpt_list"	*/
				/* (NULL if list empty or all sent)	*/
  ST_INT rpt_count;		/* count of entries in "rpt_list"	*/
				/* once buffer's full, shouldn't change much*/
  ST_UINT rpts_lost_count;	/* # rpts lost because of overflow	*/
  ST_INT brcb_bufsize;
  ST_INT cur_bufsize;
  ST_BOOLEAN enabled_once;	/* TRUE if BRCB was enabled at least once*/
  ST_UCHAR lastSentEntryID[8];
  } MVL61850_BRCB_CTRL;

/* TypeIDs for special report types created by mvlu_rpt_init_types.	*/
typedef struct
  {
  ST_INT mmsbool;	/* named so not confused with C++ 'bool' type	*/
  ST_INT int8u;		/* for SqNum			*/
  ST_INT int16u;
  ST_INT int32u;
  ST_INT vstring65;	/* for RptID			*/
  ST_INT btime6;	/* for EntryTime		*/
  ST_INT ostring8;	/* for EntryID			*/
  ST_INT vstring32;	/* for RptId			*/
  ST_INT bvstring6;	/* for TrgOps (IEC)		*/
  ST_INT bvstring8;	/* for OptFlds,TrgOps (UCA)	*/
  ST_INT bvstring10;	/* for OptFlds (IEC)		*/
  ST_INT bstr6;		/* for Reason (IEC)		*/
  ST_INT bstr8;		/* for Reason (UCA)		*/
  ST_INT vstring129;	/* for ObjectReference (IEC)	*/
  } MVLU_RPT_TYPEIDS;

/* For backward compatibility ... do not use */
#define MVLU_SEQNUM_MASK  MVLU_SQNUM_MASK

#define MVLU_MAX_RPTID_LEN  65
#define MVLU_MAX_OUTDAT_LEN  65


/*	MVLU_RPT_CTRL	*/
typedef struct mvlu_rpt_ctrl
  {
  DBL_LNK l;			/* Internal use	*/

/* Active clients */

/* NOTE: "only_client" for 61850 only.	*/
  MVLU_RPT_CLIENT only_client;	/* exactly 1. Don't need list		*/

/* NOTE: "num_rpt_clients", "rpt_client_list", "common_basrcb" for UCA only.*/
  ST_INT num_rpt_clients;
  MVLU_RPT_CLIENT *rpt_client_list;

/* basrcb data for passive read clients */
  MVLU_BASRCB common_basrcb;
  ST_CHAR *basrcb_name;

/* Used in read/write indication functions in finding the report ctrl	*/
  RUNTIME_TYPE *rcbRtHead;
  MVL_VAR_ASSOC *base_va;

/* Used to support different report schemes	*/
  ST_INT rcb_type;	/* RCB_TYPE_UCA, RCB_TYPE_IEC_BRCB, etc.	*/

/* Action to be taken if var changes twice before buftim expires	*/
  ST_INT buftim_action;		/* MVLU_RPT_BUFTIM_REPLACE/SEND_NOW	*/

/* The information below is used internally by MVLU			*/
  MVL_NVLIST_CTRL *dsNvl;	/* The base dataSet for the report	*/
  MVL_NVLIST_CTRL rptNvl;	/* The NVL used to send the InfoRpt	*/
  RUNTIME_TYPE incRt;		/* Used in building the inclusion_va	*/
  ST_INT maxNumRptVars;		/* Max vars allowed in report.		*/
  MVLU_RPT_TYPEIDS rpt_typeids;	/* Types needed for reports.		*/
  ST_INT inclusion_typeid;	/* One more special type.		*/
  MVL61850_BRCB_CTRL brcbCtrl;	/* Used only for 61850 BRCB.		*/
  ST_DOUBLE scan_rate;		/* Scan rate in milliseconds		*/
  ST_DOUBLE next_scan_start;	/* Time for next scan			*/
  } MVLU_RPT_CTRL;

extern MVLU_RPT_CTRL *mvlu_rpt_ctrl_list;	/* List of only UCA RCBs.*/
extern MVLU_RPT_CTRL *mvl61850_rpt_ctrl_list;	/* List of only 61850 RCBs.*/

/* UCA VA Scan Control */
typedef struct
  {
  DBL_LNK l;				/* Internal use			*/
  ST_BOOLEAN enable;
  ST_DOUBLE scan_period;
  ST_DOUBLE next_scan_start;
  ST_BOOLEAN saturated;
  ST_INT num_va_changes;

  ST_INT num_scan_va;
  MVL_VAR_ASSOC **scan_va;
  ST_INT num_va_read_pend;

  MVL_IND_PEND indCtrl;
  MVL_COMM_EVENT commEvent;
  MVL_SCOPE *scan_va_scope;		/* ptr to array of structs.	*/
  ST_VOID *usr;		/* user assignable pointer to use in scan callbacks*/
  } MVLU_RPT_SCAN_CTRL;
extern MVLU_RPT_SCAN_CTRL *mvlu_rpt_scan_list;


/* Report Service */
ST_VOID mvlu_rpt_service (ST_VOID);

/* Report Variable Scanning */
//MVLU_RPT_SCAN_CTRL *mvlu_rpt_create_scan_ctrl (ST_INT numScanVa);
MVLU_RPT_SCAN_CTRL *mvlu_rpt_create_scan_ctrl2 (
	MVL_NVLIST_CTRL *nvl,
	ST_RET (*scan_done_fun) (struct mvl_ind_pend *ind_pend),
	ST_UINT report_scan_rate);	/* report scan rate (millisec)	*/
ST_VOID mvlu_rpt_destroy_scan_ctrl (MVLU_RPT_SCAN_CTRL *scanCtrl);
ST_VOID mvlu_rpt_va_scan (ST_VOID);
ST_VOID mvlu_rpt_scan_read (MVLU_RPT_SCAN_CTRL *scanCtrl);

/* Asynchronous Change Reporting */
ST_VOID mvlu_rpt_va_change (MVL_VAR_ASSOC *va,
			    ST_UCHAR reason,
			    ST_VOID *new_data);
//by Leixt--
ST_VOID mvlu_rpt_va_change_ex (MVL_VAR_ASSOC *va,
			    ST_UCHAR reason,
			    MVLU_RPT_CTRL *rptCtrl);
//----------

/* Creating Report Dataset NVL's */
MVL_NVLIST_CTRL *mvlu_derive_rpt_ds (ST_CHAR *domName, ST_CHAR *nvlName,
				     ST_INT numNodes, ST_CHAR **nodeNames);

/* Structure Element name derivation */
ST_RET mvlu_derive_ds_va_names (ST_CHAR *domName,
       			        ST_INT numNodes, ST_CHAR **nodeNames,
				ST_INT *numObjNamesOut,
				OBJECT_NAME **objNameTblOut,
				ST_CHAR **nameBufOut);


/* Report Control Create/Free  */
/* NOTE: The "buftim_action" arg may be set to
 * MVLU_RPT_BUFTIM_REPLACE or MVLU_RPT_BUFTIM_SEND_NOW.
 * This arg is only used in the case when buffer
 * time (BufTim) is used, and a second data change is detected for the
 * same "va", before the BufTim expires. To satisfy the requirements of
 * IEC61850-7-2, the caller must set this flag to indicate whether to
 * replace the buffered value with the new value and continue timing
 * (MVLU_RPT_BUFTIM_REPLACE), OR to send a report immediately with the
 * buffered value, save the new value in the buffer, and restart the timer
 * (MVLU_RPT_BUFTIM_SEND_NOW).
 */
MVLU_RPT_CTRL *mvlu_create_rpt_ctrl (ST_CHAR *basrcbName,
			MVL_NVLIST_CTRL *dsNvl,
			MVL_VAR_ASSOC *base_va,
			ST_INT rcb_type,
			ST_INT buftim_action,	/* MVLU_RPT_BUFTIM_*	*/
			ST_INT brcb_bufsize,	/* for BRCB only	*/
			ST_UINT32 ConfRev);	/* for BRCB/URCB only	*/
ST_VOID mvlu_free_rpt_ctrl (MVLU_RPT_CTRL *rptCtrl);

/* Main reporting functions for IEC 61850 only.		*/
MVLU_RPT_CTRL *mvl61850_create_rpt_ctrl (ST_CHAR *basrcbName,
			MVL_NVLIST_CTRL *dsNvl,
			MVL_VAR_ASSOC *base_va,
			ST_INT rcb_type,
			ST_INT buftim_action,	/* MVLU_RPT_BUFTIM_*	*/
			ST_INT brcb_bufsize,	/* for BRCB only	*/
			ST_UINT32 ConfRev);	/* for BRCB/URCB only	*/
ST_VOID mvl61850_free_rpt_ctrl (MVLU_RPT_CTRL *rptCtrl);
ST_VOID mvl61850_rpt_service (ST_VOID);
ST_RET mvl61850_rpt_dataset_create (MVLU_RPT_CTRL *rptCtrl,
			MVL_NVLIST_CTRL *dsNvl);
ST_VOID mvl61850_rpt_dataset_destroy (MVLU_RPT_CTRL *rptCtrl);

/************************************************************************/
/*			mvlu_integrity_scan_destroy			*/
/* Free temporary MVL_IND_PEND allocated by mvlu_integrity_scan_read.	*/
/************************************************************************/
ST_VOID mvlu_integrity_scan_destroy (MVL_IND_PEND *indCtrl);

/*
 *			mvlu_integrity_scan_read
 * This function "BEGINS" the scan of ALL data for one Report DataSet (NVL).
 * It is called automatically when an Integrity Report or a
 * General Interrogation Report needs to be sent. This is much more
 * efficient than constantly scanning.
 * - It allocates & initializes a temporary MVL_IND_PEND structure.
 * - It calls "u_mvl_read_ind" to begin the scan.
 * - The scan may complete synchronously or asynchronously.
 * - When the scan completes, the funct pointed to by "scan_done_fun" arg
 *   is called to build the report and cleanup.
 * CRITICAL: Function pointed to by "scan_done_fun" must call
 * "mvlu_integrity_scan_destroy" to free temporary MVL_IND_PEND struct.
 */

ST_VOID mvlu_integrity_scan_read (MVLU_RPT_CLIENT *rptClient,
			ST_VOID (*scan_va_done_fun)(MVL_IND_PEND *indCtrl,
					MVL_VAR_ASSOC *va),
			ST_RET (*scan_done_fun)(MVL_IND_PEND *indCtrl)
			);

MVL_IND_PEND *mvlu_setup_scan_read (MVL_NVLIST_CTRL *nvl,
			ST_VOID (*scan_va_done_fun)(MVL_IND_PEND *indCtrl,
					MVL_VAR_ASSOC *va),
			ST_RET (*scan_done_fun)(MVL_IND_PEND *indCtrl)
			);

/************************************************************************/
/*			mvlu_integrity_timeout				*/
/* Check for Integrity period timeout. If timeout occurred, start	*/
/* integrity scan.							*/
/* RETURNS: SD_TRUE if IntgPd is set and timeout occurred		*/
/*          SD_FALSE otherwise						*/
/************************************************************************/
ST_RET mvlu_integrity_timeout (MVLU_RPT_CLIENT *rptClient, ST_DOUBLE timeNow);

/* Pointer to one of these functions passed to "mvlu_integrity_scan_read",
 * saved in "usr_done_fun" in MVL_IND_PEND struct.  Called when scan completes.
 */
ST_RET mvlu_integrity_scan_done (MVL_IND_PEND *indCtrl);
ST_RET mvlu_gi_scan_done (MVL_IND_PEND *indCtrl);

/* Pointer to one of these functions passed to "mvlu_integrity_scan_read",
 * stored in global var. Called when each va read completes.
 */
ST_VOID mvlu_integrity_scan_va_done (MVL_IND_PEND *indCtrl, MVL_VAR_ASSOC *va);
ST_VOID mvlu_gi_scan_va_done (MVL_IND_PEND *indCtrl, MVL_VAR_ASSOC *va);

extern ST_VOID (*_mvlu_rpt_disconnect_rcvd_fun)(MVL_NET_INFO *netInfo);

MVL_NVLIST_CTRL *mvlu_resolve_uca_nvl (MVL_NVLIST_CTRL *ucaNvl,
				       OBJECT_NAME *scopeSel);

/* Defines for UCA/IEC report type, "rpt_type" arg to "mvlu_send_report"*/
#define MVLU_RPT_TYPE_INTEGRITY_OR_GI	0
#define MVLU_RPT_TYPE_RBE		1

ST_RET mvlu_send_report (MVLU_RPT_CLIENT *rptClient, ST_INT rpt_type);

/* u_mvlu_rpt_time_get - User callback function to set accurate time
 * that UCA/IEC report is built, called by "mvlu_send_report" or
 * "mvl61850_rcb_build" when report is being built.
 */
ST_VOID u_mvlu_rpt_time_get (MMS_BTIME6 *TimeOfEntry);

/* Misc. Helper Functions */
ST_INT mvlu_rpt_get_va_index (MVLU_RPT_CTRL *rptCtrl, MVL_VAR_ASSOC *va);
MVLU_BASRCB *_mvlu_get_rd_rcb (MVLU_RD_VA_CTRL *mvluRdVaCtrl,
				MVLU_RPT_CLIENT **rptClientOut);
MVLU_BASRCB *_mvlu_get_wr_rcb (MVLU_WR_VA_CTRL *mvluWrVaCtrl,
				      MVLU_RPT_CLIENT **rptClientOut);
MVLU_BASRCB *mvl61850_get_rcb (MVL_VAR_ASSOC *baseVa,
	RUNTIME_TYPE *rt,
	MVLU_RPT_CLIENT **rptClientOut);

ST_VOID _mvlu_rpt_disconnect_rcvd (MVL_NET_INFO *netInfo);
ST_RET mvlu_rpt_find_typeids (MVLU_RPT_TYPEIDS *rpt_typeids);
ST_RET mvlu_rpt_rcb_type_find (ST_INT type_id, ST_CHAR *basrcbName,
	RUNTIME_TYPE **rcbHeadOut, ST_INT *numRtOut);

/* MVLU Internal Use */
#define MMSOP_MVLU_RPT_VA	200
#define MMSOP_MVLU_GOOSE_UPDATE	201
#define MMSOP_RDWR_USR_HANDLED	202


ST_RET mvlu_find_uca_var (RUNTIME_TYPE **rtIo, ST_INT *numRtIo,
			 ST_CHAR *varName);


/************************************************************************/
/************************************************************************/
/* SBO HANDLING ELEMENTS						*/

#define SBO_SELECT_TIMEOUT 	30	/* seconds		       	*/
#define MAX_NUM_SBO_PEND 	10  	/* Number of SBOs to be pending	*/
#define MAX_SBO_NAME_SIZE   	66

typedef struct mvl_sbo_ctrl
  {
  ST_BOOLEAN in_use;	      	 	/* control element management	*/
  ST_BOOLEAN use_ms_timer;		/* if TRUE, use expire_time_ms below*/
  ST_CHAR sbo_var[MAX_SBO_NAME_SIZE+1];
  MVL_NET_INFO *net_info;	 	/* Connection ID		*/
  time_t expire_time;	 		/* SELECT expiration time	*/
  ST_DOUBLE expire_time_ms; 		/* SELECT expiration time in ms	*/
  } MVL_SBO_CTRL;


ST_VOID u_mvl_sbo_operate (MVL_SBO_CTRL *sboSelect,
		    	   MVLU_WR_VA_CTRL *mvluWrVaCtrl);

ST_VOID mvlu_clr_pend_sbo (MVL_NET_INFO *net_info);

MVL_SBO_CTRL *mvlu_sbo_chk_state (ST_CHAR *sboName,
				     MVL_NET_INFO *net_info);
ST_VOID mvlu_sbo_chk_timers (ST_VOID);
ST_VOID mvlu_sbo_ctrl_free (MVL_SBO_CTRL *sboCtrl);
MVL_SBO_CTRL *initSboCtrl (MVL_NET_INFO *net_info,
	ST_CHAR *sbo_name,
	ST_UINT32 sboTimeout,
	ST_BOOLEAN use_ms_timer);

/************************************************************************/
/************************************************************************/
/* IEC-61850 functions							*/
/************************************************************************/

/*
 *			mvl61850_brcb_client_service
 *
 * Check the BRCB state and, if necessary,
 * encode, queue, AND/OR send IEC "Buffered" reports.
 */
ST_VOID mvl61850_brcb_client_service (MVLU_RPT_CTRL *rptCtrl,
			MVLU_RPT_CLIENT *rptClient,
			ST_DOUBLE timeNow);

/**
 *			mvl61850_urcb_client_service
 *
 * Check the URCB state and, if necessary,
 * encode AND send IEC "Unbuffered" reports.
 */
ST_VOID mvl61850_urcb_client_service (MVLU_RPT_CTRL *rptCtrl,
			MVLU_RPT_CLIENT *rptClient,
			ST_DOUBLE timeNow);

ST_RET mvlu_rpt_ready (MVLU_RPT_CLIENT *rptClient, ST_INT rpt_type);
ST_RET mvl61850_urcb_rpt_send (MVLU_RPT_CTRL *rptCtrl,
	MVLU_RPT_CLIENT *rptClient,
	ST_INT rpt_type);
ST_RET mvl61850_brcb_rpt_save (MVLU_RPT_CLIENT *rptClient);
ST_RET mvl61850_brcb_rpt_send (MVLU_RPT_CTRL *rptCtrl,
	MVLU_RPT_CLIENT *rptClient,
	BUFLIST_ENTRY *buflist_entry,
	ST_BOOLEAN *all_seg_done);
ST_VOID mvl61850_brcb_entryid_init (MVLU_RPT_CTRL *rptCtrl, ST_UINT8 *EntryID);

ST_VOID mvl61850_brcb_rpt_lists_clean (MVL61850_BRCB_CTRL *brcbCtrl);

/* Internal IEC 61850 reporting functions (not called by user).	*/
ST_RET mvl61850_mk_rptid (MVLU_RPT_CTRL *rptCtrl, ST_CHAR *RptID, size_t max_len);
ST_VOID mvl61850_mk_dataref (MVL_VAR_ASSOC *va, MVL_SCOPE *va_scope,
	ST_CHAR *databuf, ST_INT maxlen);
ST_VOID mvl61850_rcb_cleanup (MVLU_RPT_CLIENT *rptClient);
ST_RET mvl61850_brcb_rpt_set_entryid (MVLU_RPT_CLIENT *rptClient, ST_UCHAR *EntryID);
ST_VOID mvl61850_rcb_chk_state (MVLU_RPT_CTRL *rptCtrl,
	MVLU_RPT_CLIENT *rptClient,
	ST_DOUBLE timeNow);
ST_BOOLEAN chk_seg_needed (MVLU_RPT_CLIENT *rptClient,
			ST_INT *asn1_len_array,
			ST_INT cur_va_index,	/* input arg	*/
			ST_INT *next_va_index);	/* output arg	*/

/************************************************************************/
/* IEC 61850 "Control Model" functions.					*/
/************************************************************************/
ST_VOID mvl61850_sbo_create_sboname (MVL_VAR_ASSOC *va, MVL_SCOPE *va_scope,
		      ST_CHAR *sboName);

MVL_SBO_CTRL *mvl61850_ctl_chk_sbo (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
MVL_SBO_CTRL *mvl61850_ctl_chk_sbow (MVLU_WR_VA_CTRL *mvluWrVaCtrl);

ST_RET mvl61850_ctl_chk_state (MVLU_WR_VA_CTRL *mvluWrVaCtrl);

ST_RET mvl61850_ctl_lastapplerror_create (ST_VOID);
ST_RET mvl61850_ctl_lastapplerror_send (MVL_NET_INFO *net_info,
	MVL61850_LAST_APPL_ERROR *last_appl_error);
ST_RET mvl61850_ctl_command_termination (MVL_NET_INFO *net_info, ST_CHAR *oper_ref,
              ST_RET status, MVL61850_LAST_APPL_ERROR *last_appl_error);

/* These callback functions must be supplied by user.		*/
ST_VOID u_mvl61850_ctl_oper_begin (ST_CHAR *oper_ref);
ST_VOID u_mvl61850_ctl_oper_end (MVL_NET_INFO *net_info, ST_CHAR *oper_ref, MVL_VAR_ASSOC *base_var);

ST_RET mvl61850_mkname_ctlmodel (ST_CHAR *var_name, ST_CHAR *flatname, size_t flatname_len);

/************************************************************************/
/* Miscellaneous helper functions					*/
/************************************************************************/
ST_VOID mvlu_trim_branch_name (ST_CHAR *branch_name);
ST_RET mvlu_find_comp_type (ST_INT base_type_id, ST_CHAR *flat_name,
			RUNTIME_TYPE **sub_rt_type,		/* out	*/
			ST_INT *sub_rt_num);			/* out	*/

ST_RET mvlu_get_leaf_val_int8 (MVL_VAR_ASSOC *base_va, ST_CHAR *flatname, ST_INT8 *data);
ST_RET mvlu_get_leaf_val_int32 (MVL_VAR_ASSOC *base_va, ST_CHAR *flatname, ST_INT32 *data);
ST_RET mvlu_get_leaf_val_int_any (MVL_VAR_ASSOC *base_va, ST_CHAR *flatname, ST_INT32 *data);
ST_RET mvlu_get_leaf_val_uint32 (MVL_VAR_ASSOC *base_va, ST_CHAR *flatname, ST_UINT32 *data);
ST_RET mvlu_get_leaf_val_boolean (MVL_VAR_ASSOC *base_va, ST_CHAR *flatname, ST_BOOLEAN *data);
ST_RET mvlu_get_leaf_val_bvstring (MVL_VAR_ASSOC *base_va, ST_CHAR *flatname,
                                   MMS_BVSTRING *data, ST_INT max_num_bits);
ST_VOID *mvlu_get_leaf_data_ptr (MVL_VAR_ASSOC *base_va, ST_CHAR *flatname, RUNTIME_TYPE **rt_type);
ST_RET _rcb_writable (MVLU_BASRCB *rcb,	MVLU_RPT_CLIENT *rptClient,
	MVLU_WR_VA_CTRL *mvluWrVaCtrl);

/************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* MVL_UCA_INCLUDED */


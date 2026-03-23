#ifndef SUICACSE_H

#define SUICACSE_H

/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*		1988 - 2005, All Rights Reserved			*/
/*									*/
/* MODULE NAME : suicacse.h						*/
/* PRODUCT(S)  : SUIC							*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/* This module contains SUIC definitions and external declarations for	*/
/* global SUIC variables. This module should be included with user	*/
/* functions that need to interface with SUIC				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 07/11/05  EJV     31    Mv find_*_dib_entry from marb_def.h (user funs)*/
/*			   Add DIB_xxx macros to access DIB_ENTRY fields.*/
/*			   Moved dib_match_* funs to use w/MMSEASE_MOSI	*/
/* 06/24/05  EJV     30    Moved s_chk_resource here from marben_a.h	*/
/* 04/11/05  EJV     29    Move DIRECTORY_SUPPORT under MARBEN code.	*/
/*			   Added MMSEASE_MOSI to inc lean_a.h (clearer)	*/
/* 03/23/05  JRB     28    Move APP_REF to asn1r so only apps using SUIC*/
/*			   need this file.				*/
/* 03/22/05  JRB     27    Make MARBEN the default stack.		*/
/* 06/14/04  EJV     26    Rem MAP30_ACSE (mds.h includes lber.h that	*/
/*			     conflicts on AIX, see note).		*/
/* 06/09/04  EJV     25    Removed obsolete REDUCED_STACK, ADD_COT7_EXT,*/
/*			   ADD_RS_EXT defines.				*/
/* 04/20/04  EJV     24    Added back s_free_part_security_info.	*/
/* 10/21/03  EJV     23    Del s_free_part_security_info.		*/
/* 10/13/03  EJV     22    Changed defined(vms) to defined(__VMS)	*/
/* 06/25/03  EJV     21    Added MAP30_ACSE def before mds.h include	*/
/* 06/16/03  EJV     20    Renamed ACSE_FLOW_PRINT to ACSE_DIB_PRINT.	*/
/*			   Alligned comments in DIB_ENTRY		*/
/*			   Added DIB_MATCH_CTRL and related defs, funcs	*/
/* 06/13/03  EJV     19    Del unused ACSE_xxx_PRINT_TYPEs. Made log 	*/
/*			    masks 2 bytes. Added ACSE_FLOW_PRINT.	*/
/* 06/13/03  EJV     18    Added SUIC_LIB (mds.h needed only in SUIC)	*/
/* 05/20/03  EJV     17    Added encryptCtrl to dib_entry.		*/
/*			   Added encryptSet to CHAN_INFO.		*/
/* 05/01/03  ASK     16    Change security protos to use S_SEC_SPARAMS  */
/* 04/11/03  EJV     15    Reversed commenting out ssec.h for MMS_LITE.	*/
/* 04/02/03  EJV     14    Moved authenticate fields to s_chan_info.	*/
/*			   Added s_set_auth_info() proto.		*/
/*			   Commented out ssec.h for MMS_LITE (for now).	*/
/* 03/31/03  EJV     13    Removed SECURITY_SUPPORT code (not used).	*/
/*			   Added undef _WINDOWS below include mds.h.	*/
/*			   Del obsolete s_block() (UNIX only)		*/
/*                           and s_comm_disable, s_comm_enable.		*/
/*			   Removed SE_... related to SECURITY_SUPPORT.	*/
/* 02/20/03  JRB     12    Del PSOS code.				*/
/* 11/12/02  EJV     11    ASS_INFO: ACSE_AUTH_ENABLED code always enabl*/
/* 11/04/02  EJV     10    ASS_INFO: added ACSE_AUTH_ENABLED,		*/
/*			     Added proto s_clear_auth;			*/
/* 01/08/02  EJV     09    Keep MARBEN undefined: not needed in MMS-Lite*/
/* 12/14/01  EJV     08    Del code for unsupported platforms & hardware*/
/* 04/26/99  DSF     07    Security related changes			*/
/* 02/09/98  RKR     06    Made ChannelTypeToUse perm part of DIB_ENTRY */ 
/* 11/13/97  DSF     05    Changed APP_REF_FORM defines to be consistent*/
/*			   with ASS_INFO				*/
/* 09/26/97  DSF     04    Added ACSE_ABORT_PRINT			*/
/* 08/13/97  DSF     03    AR Name management support			*/
/* 07/29/97  DSF     02    Security Attack stuff			*/
/* 07/29/97  DSF     01    APP_REF stuff moved here			*/
/* 04/11/97  DSF   7.00    MMSEASE 7.0 release. See MODLS70.DOC for	*/
/*			   history.					*/
/************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif
									  
#include "glberror.h"
#include "asn1r.h"
#include "dibmatch.h"

#include "slog.h"
#include "acseauth.h"
#include "ssec.h"		/* Security include file		*/

/************************************************************************/
/* Defines that all SUICs should use. Must be before other #includes	*/
/************************************************************************/

/* Transport provider definitions */
#define TP4		0
#define TCP		1

/* Selector size limits */
#define MAX_P_SEL	16
#define MAX_S_SEL	16
#define MAX_T_SEL	32
#define MAX_N_SEL	20

#define IP_ADDR_LEN	4
#define HOST_NAME_LEN	64

#define RFC1006_PORT	102

#define MAX_NAME_LEN		64
#define MAX_HOST_LEN		32

#define TAG_MNGT_ADDR		0
#define TAG_MNGT_HOST		1

/************************************************************************/
/* This define represents the maximum number of channels.		*/

extern ST_INT s_max_chan;	/* actual number of suic channels used	*/

extern ST_INT s_msgsize;		/* max transfer data size		*/

/************************************************************************/
/* Select the board type here						*/
/* These defines are used in the sample source code to make use of	*/
/* board specific operations, such as status or debug displays. 	*/

/** #define DECNP5 **/
/** #define MARBEN **/

			/* Now select the stack specific include file	*/
#if defined(LEAN_T)  || defined(MMSEASE_MOSI)
 #include "lean_a.h"

#elif defined(DECNP5)
 #define MAX_SUIC_CHAN 200
 #include "decnp5_a.h"		/* OpenVMS */

#else
 /* Default stack is MARBEN. Define it now, if makefile didn't.	*/
 #if !defined(MARBEN)
  #define MARBEN
 #endif
 #include "marben_a.h"		/* MARBEN				*/

#define DIRECTORY_SUPPORT	(defined (X500_SUPPORT) || defined (LDAP_SUPPORT))
#endif


#include "gen_list.h"

/************************************************************************/
/************************************************************************/
/* Error code definitions						*/
/* These codes are returned when a SUIC command function detects an	*/
/* error condition.							*/
/************************************************************************/

#define SE_CPU_ALLOC  		0x0B01		/* Memory allocation error	*/
#define SE_CHAN_ERR   		0x0B02		/* Invalid channel number	*/
#define SE_QUE_FULL   		0x0B03		/* SUIC send queue full		*/
#define SE_CHAN_CTRL  		0x0B04		/* Channel control error	*/
#define SE_CTRL_ALLOC		0x0B05		/* control block alloc error	*/
#define SE_INSFRES		0x0B06		/* insufficient SUIC resources	*/
#define SE_NAMENOTFOUND		0x0B07		/* name not found in local DIB	*/
#define SE_CHANNOTREG		0x0B08		/* channel not registered	*/
#define SE_NOPARAM		0x0B09		/* mandatory param missing	*/
#define SE_INVPARAM		0x0B0A		/* invalid param supplied	*/
#define SE_INVPDU		0x0B0B		/* invalid PDU encounetred	*/
#define SE_INVASN		0x0B0C		/* invalid ASN specified	*/
#define SE_INVTSN		0x0B0D 		/* invalid TSN specified	*/
#define SE_INVCTXT		0x0B0E		/* invalid AP context specified	*/
#define SE_INVPCI		0x0B0F		/* invalid PCI specified	*/
#define SE_INVOBJID		0x0B10		/* invalid OBJECT IDENTIFIER	*/
#define SE_SIMPLY_ENC		0x0B11		/* simply encoded data		*/
#define SE_MSGSIZETOOBIG	0x0B12		/* user-set s_smgsize too big   */
#define SE_NOLLP	        0x0B13		/* your LLP isn't up 		*/
#define SE_NOT_BOUND		0x0B14		/* not bound to a DSA		*/
#define SE_MDS_UNEXPECTED	0x0B15		/* unexpected MDS result	*/
#define SE_MDS_INVALID_SYNTAX	0x0B16		/* invalid attribute syntax	*/
#define SE_BAD_MECH_NAME	0x0B17		/* unrecognized authentication mechanism name */
#define SE_ACTIVATE		0x0B1C		/* Name activation problem	*/
#define SE_DEACTIVATE		0x0B1D		/* Name deactivation problem	*/


/************************************************************************/
/* SUIC Debug mechanism variables, functions.				*/
/************************************************************************/

#define ACSE_IND_PRINT		0x0001
#define ACSE_CNF_PRINT		0x0002
#define ACSE_ERR_PRINT		0x0004
#define ACSE_DEC_PRINT		0x0008

#if defined(__VMS)
#define OSAK_PRINT		0x0010
#define OSAK_DEB		0x0020
#endif
#define ACSE_NERR_PRINT		0x0040
#define ACSE_ABORT_PRINT	0x0080
#define ACSE_DIB_PRINT		0x0100

extern ST_UINT s_debug_sel;
extern ST_VOID (*s_menu_fun) (ST_VOID);

/************************************************************************/
/* The variable below is set to exception code when exceptions occur.	*/
/************************************************************************/

extern ST_INT s_err;	        /* set when SUIC exception detected	*/
extern ST_INT s_map_err;       /* set when E_SUBSYS id used            */

/************************************************************************/
/* Exception code definitions						*/
/************************************************************************/

#define SX_INTERNAL     	0x0F01  	/* internal SUIC error          */
#define SX_CPU_ALLOC    	0x0F02		/* memory allocation error	*/
#define SX_CTRL_ALLOC   	0x0F03		/* control block alloc error	*/
#define SX_NOCTRL		0x0F04		/* Out of control blocks	*/
#define SX_NODATA		0x0F05		/* Out of data buffers		*/
#define SX_QUE_FULL   		0x0F06		/* SUIC send queue full		*/
#define SX_INVPDU		0x0F07		/* invalid PDU data field	*/
#define SX_INVCHAN		0x0F08		/* invalid channel number	*/
#define SX_BADCB		0x0F09		/* unknown CB from board	*/
#define SX_ENCERR		0x0F0A		/* ASN.1 encode error		*/
#define SX_CTRL_FREE		0x0F0B		/* control block free error	*/
#define SX_DATA_FREE		0x0F0C		/* data buffer free error	*/
#define SX_DATABUF_OVRFLW       0x0F0D     	/* data being received  	*/
                                        	/* exceeds s_msgsize            */

/************************************************************************/
/* SUIC state masks							*/
/************************************************************************/

#define SM_CHAN_REG		0x0001	/* channel registered		*/
#define SM_ASS_REQ_PEND		0x0002	/* associate request pending	*/
#define SM_LISTEN		0x0004	/* listen outstanding		*/
#define SM_ASS_ACTIVE		0x0008	/* association active		*/
#define SM_CANLISTEN_PEND	0x0010	/* cancel pending		*/
#define SM_REL_REQ_PEND		0x0020	/* release request pending	*/
#define SM_ABT_REQ_PEND		0x0040	/* abort request pending	*/
#define SM_P_ABORT              0x0080  /* Issue P-Abort to User        */
#define SM_ASS_IND_RCVD         0x0100  /* associate Indication received*/
#define SM_ASS_RSP_PEND         0x0200  /* associate response pending   */
#define SM_ASS_REJ_PEND         0x0400  /* associate reject pending     */
#define SM_REL_IND_RCVD         0x0800  /* release indication received  */
#define SM_REL_RSP_PEND         0x1000  /* release response pending     */
#define SM_MDS_READ_PEND        0x2000  /* MDS read request pending	*/


/************************************************************************/
/* The structure below is used to save the various info about the	*/
/* state of the channels on a per-channel basis.			*/
/* This structure is used to pass data.					*/
/************************************************************************/

/* NOTE: The ACSE_AUTH_ENABLED code is used in MMS-EASE and MMS-LITE	*/
/*       based products to provide password or 'other' authorization	*/
/*       capability.							*/

struct s_chan_info
{
  ST_LONG reserved;		/* reserved for SUIC			*/

  ST_CHAR *name;			/* local name				*/

  ST_INT transport;		/* TP4 vs. TCP/IP			*/

  ST_UINT AP_ctxt_mask;		/* application context name mask   	*/

  ST_BOOLEAN AP_title_pres;		/* present flag				*/
  MMS_OBJ_ID AP_title;		/* AP title    				*/ 
  ST_BOOLEAN AP_inv_id_pres;		/* present flag				*/
  ST_INT32 AP_invoke_id;		/* AP invocation ID    			*/
  ST_BOOLEAN AE_qual_pres;		/* present flag				*/
  ST_INT32 AE_qual;			/* AE qualifier    			*/
  ST_BOOLEAN AE_inv_id_pres;		/* present flag				*/
  ST_INT32 AE_invoke_id;		/* AE invocation ID    			*/

  ST_INT p_sel_len;		/* P-selector length			*/
  ST_UCHAR p_sel[MAX_P_SEL];	/* P-selector				*/
  ST_INT s_sel_len;		/* S-selector length			*/
  ST_UCHAR s_sel[MAX_T_SEL];	/* S-selector				*/
  ST_INT t_sel_len;		/* T-selector length			*/
  ST_UCHAR t_sel[MAX_T_SEL];	/* T-selector				*/
  ST_INT net_addr_len;		/* Network address length		*/
  ST_UCHAR net_addr[MAX_N_SEL];	/* Network address			*/
  ST_CHAR  ip_addr[HOST_NAME_LEN + 1];	/* TCP/IP dotted decimal or host name 	*/
  ST_INT port;			/* TCP/IP port number			*/

  ST_CHAR *part_name;		/* partner name				*/
  ST_INT part_transport;	/* TP4 vs. TCP/IP			*/

  ST_UINT part_AP_ctxt_mask;	/* partner application context name mask*/

  ST_BOOLEAN part_AP_title_pres;	/* present flag				*/
  MMS_OBJ_ID part_AP_title;	/* partner AP title    			*/
  ST_BOOLEAN p_AP_inv_id_pres; 	/* present flag				*/
  ST_INT32 part_AP_invoke_id; 	/* partner AP invocation ID    		*/
  ST_BOOLEAN part_AE_qual_pres;	/* present flag				*/
  ST_INT32 part_AE_qual;		/* partner AE qualifier   		*/
  ST_BOOLEAN p_AE_inv_id_pres; 	/* present flag				*/
  ST_INT32 part_AE_invoke_id; 	/* partner AE invocation ID		*/

  ST_INT part_p_sel_len;		/* P-selector length			*/
  ST_UCHAR part_p_sel[MAX_P_SEL];	/* P-selector				*/
  ST_INT part_s_sel_len;		/* S-selector length			*/
  ST_UCHAR part_s_sel[MAX_T_SEL];	/* S-selector				*/
  ST_INT part_t_sel_len;		/* T-selector length			*/
  ST_UCHAR part_t_sel[MAX_T_SEL];	/* T-selector				*/
  ST_INT part_net_addr_len;		/* Network address length	*/
  ST_UCHAR part_net_addr[MAX_N_SEL];	/* Network address		*/
  ST_CHAR  part_ip_addr[HOST_NAME_LEN + 1];/* TCP/IP dotted decimal or host name */
  ST_INT part_port;			/* TCP/IP port number			*/

  ST_INT state_mask;		/* association state mask		*/

/*#if defined(ACSE_AUTH_ENABLED) */
  ACSE_AUTH_INFO authInfo;		/* local authentication info		*/

  ACSE_AUTH_INFO partAuthInfo;		/* partner authentication info		*/
					/* valid after s_associate_ind or	*/
					/* s_associate_cnf called. 		*/
  ST_BOOLEAN         encryptSet;	/* encryption info set flag		*/ 
  S_SEC_ENCRYPT_CTRL encryptCtrl;	/* encryption info			*/ 
/*#endif*/ /* ACSE_AUTH_ENABLED */

#ifdef DECNP5
  ST_BOOLEAN already_gave_buffers;	/* OSAK doesn't need any more buffers.	*/
#endif
} ;

typedef struct s_chan_info CHAN_INFO;

extern CHAN_INFO *s_chan_info;


/************************************************************************/
/* The structure below is used to save the various info about the	*/
/* state of the association on a channel-by-channel basis.		*/
/* This structure is used to receive data.				*/
/************************************************************************/

struct acse_ar_info
  {
  ST_LONG reserved1;	             	/* reserved for provider use    */
  ST_CHAR *ar_name;	         	/* local name                   */
  ST_INT transport;			/* TP4 vs. TCP/IP		*/

  ST_UINT AP_ctxt_mask;	           	/* reserved for provider use	*/
  ST_INT AP_title_form;          	/* 0 == form 1, 1 == form 2	*/
  ST_BOOLEAN AP_title_pres;          	/* present flag                 */
  MMS_OBJ_ID AP_title;          	/* AP title                     */
  ST_BOOLEAN AP_inv_id_pres;         	/* present flag                 */
  ST_INT32 AP_invoke_id;            	/* AP invocation ID             */
  ST_BOOLEAN AE_qual_pres;           	/* present flag                 */
  ST_INT32 AE_qual;                 	/* AE qualifier                 */
  ST_BOOLEAN AE_inv_id_pres;         	/* present flag                 */
  ST_INT32 AE_invoke_id;            	/* AE invocation ID             */

  ST_INT p_sel_len;			/* P-selector length		*/
  ST_UCHAR p_sel[MAX_P_SEL];		/* P-selector			*/
  ST_INT s_sel_len;			/* S-selector length		*/
  ST_UCHAR s_sel[MAX_T_SEL];		/* S-selector			*/
  ST_INT t_sel_len;			/* T-selector length		*/
  ST_UCHAR t_sel[MAX_T_SEL];		/* T-selector			*/
  ST_INT net_addr_len;			/* Network address length	*/
  ST_UCHAR net_addr[MAX_N_SEL];		/* Network address		*/
  ST_CHAR  ip_addr[HOST_NAME_LEN + 1];	/* TCP/IP dotted decimal or host name 	*/

  ST_BOOLEAN part_name_found;        	/* partner name found in DIB     */
  ST_CHAR *part_ar_name;        		/* partner name                 */
  ST_UINT part_AP_ctxt_mask;		/* reserved for provider	*/
  ST_INT part_AP_title_form;          	/* 0 == form 1, 1 == form 2	*/
  ST_BOOLEAN part_AP_title_pres;     	/* present flag                 */
  MMS_OBJ_ID part_AP_title;     	/* partner AP title             */
  ST_BOOLEAN part_AP_inv_id_pres;       	/* present flag                 */
  ST_INT32 part_AP_invoke_id;       	/* partner AP invocation ID     */
  ST_BOOLEAN part_AE_qual_pres;      	/* present flag                 */
  ST_INT32 part_AE_qual;            	/* partner AE qualifier         */
  ST_BOOLEAN part_AE_inv_id_pres;       	/* present flag                 */
  ST_INT32 part_AE_invoke_id;       	/* partner AE invocation ID     */
  ST_INT pci_mask;               	/* reserved for provider	*/

  ST_INT part_p_sel_len;			/* P-selector length		*/
  ST_UCHAR part_p_sel[MAX_P_SEL];		/* P-selector			*/
  ST_INT part_s_sel_len;			/* S-selector length		*/
  ST_UCHAR part_s_sel[MAX_T_SEL];		/* S-selector			*/
  ST_INT part_t_sel_len;			/* T-selector length		*/
  ST_UCHAR part_t_sel[MAX_T_SEL];		/* T-selector			*/
  ST_INT part_net_addr_len;		/* Network address length	*/
  ST_UCHAR part_net_addr[MAX_N_SEL];	/* Network address		*/
  ST_CHAR part_ip_addr[HOST_NAME_LEN + 1];	/* TCP/IP dotted decimal or host name 	*/
  };
typedef struct acse_ar_info ACSE_AR_INFO;	/* used by MMS		*/
typedef struct acse_ar_info ASS_INFO;		/* used by SUIC		*/

extern ASS_INFO *s_ass_info;


/************************************************************************/
/* The structure below is used to represent Abstract Syntax Names that	*/
/* may be used by the application.					*/
/************************************************************************/

extern MMS_OBJ_ID *asn_table;

#define ASN_USER_BASE	3	/* where user-defined names begin	*/

/************************************************************************/
/* The structure below is used to represent Transfer Syntax Names that	*/
/* may be used by the application.					*/
/************************************************************************/

extern MMS_OBJ_ID *tsn_table;

#define TSN_USER_BASE	1	/* where user-defined names begin	*/

/************************************************************************/
/* The structure below is used to represent Application Context Names 	*/
/* that	may be used by the application.					*/
/************************************************************************/

extern MMS_OBJ_ID *context_table;


#define CTXT_USER_BASE	4	/* where user-defined contexts begin	*/

/************************************************************************/
/* The following are the default masks					*/
/************************************************************************/

/* AP Context names							*/
#define SM_ISO_MMS_AP_CTXT	0x01
#define SM_MAP_MMS_AP_CTXT	0x02
#define SM_PRIVATE_AP_CTXT	0x04
#define SM_ISO_MMS_IS_AP_CTXT	0x08

/* Abstract Syntax names						*/
#define SM_ISO_MMS_ASN		0x01
#define SM_MAP_MMS_ASN		0x02
#define SM_PRIVATE_ASN		0x04

/* Transfer Syntax names						*/
#define SM_ASN1_TSN		0x01

/************************************************************************/
/* The structure below is used to identify components of the presenta-	*/
/* tion context list (both definition and result)			*/
/************************************************************************/

struct pc_def
{
  ST_INT result;	/* result, used on response only		*/
  ST_INT pci;		/* pci, used only on confirms/indications	*/
			/* This field must not be modified by the user	*/
  ST_UINT asn_mask;	/* abstract syntax name mask			*/
  ST_UINT tsn_mask;	/* transfer syntax name mask			*/
} ;

typedef struct pc_def PC_DEF;


/************************************************************************/
/* The structure below is used to represent the user data list before	*/
/* presentation contexts have been negotiated				*/
/************************************************************************/

struct u_data
{
  ST_INT list_index;	/* for request/indication, this refers to an	*/
			/* index into pc_deflist whose entry represents	*/
			/* presentation context on which data is to be	*/
			/* carried.  For response/confirm, this refers	*/
			/* to an index into result list			*/
  ST_UINT tsn_mask;	/* transfer syntax name mask			*/
  ST_INT u_data_len;	/* user data length				*/
  ST_CHAR *user_data;	/* pointer to user data				*/
} ;

typedef struct u_data U_DATA;


/************************************************************************/
/* The structure below is used to represent the user data list after	*/
/* presentation contexts have been negotiated				*/
/************************************************************************/

struct trans_data
{
                        /* This is really asn_mask                      */
  ST_UINT pci_mask;	/* mask representing index into pci_table	*/
  ST_INT len;		/* data length					*/
  ST_CHAR *data;	/* pointer to data				*/
} ;

typedef struct trans_data TRANS_DATA;


/************************************************************************/
/* The structure below is used to save Directory and other information	*/
/* about local and remote AE's read in from DIB file			*/
/************************************************************************/

#if defined (MARBEN) || defined (DECNP5)

#ifndef DIB_ENTRY_DEFINED
#define DIB_ENTRY_DEFINED

struct dib_entry
{
  DBL_LNK lnk;				/* link pointer				*/

  ST_LONG reserved;			/* reserved field			*/
  ST_LONG reserved2;			/* reserved field			*/
#if defined (MARBEN) && defined (_WIN32)
  ST_INT mngt_tag;			/* management operation tag		*/
  ST_CHAR host_name[MAX_HOST_LEN + 1];
  ST_CHAR *comment;
#endif
#if DIRECTORY_SUPPORT
  ST_CHAR *name;			/* user-defined ASCII character string	*/
#else
  ST_CHAR name[MAX_NAME_LEN + 1];	/* user-defined ASCII character string	*/
#endif
  ST_BOOLEAN local;			/* local or remote name			*/
#ifdef MARBEN
  ST_BOOLEAN sharable;			/* shared flag (local names only)	*/
#endif
  ST_INT transport;			/* transport provider: TP4 vs. TCP	*/
  ST_BOOLEAN AP_title_pres;		/* present flag				*/
  MMS_OBJ_ID AP_title; 			/* AP title    				*/
  ST_BOOLEAN AP_inv_id_pres;		/* present flag				*/
  ST_INT32 AP_invoke_id;		/* AP invocation ID    			*/
  ST_BOOLEAN AE_qual_pres;		/* present flag				*/
  ST_INT32 AE_qual;			/* AE qualifier    			*/
  ST_BOOLEAN AE_inv_id_pres;		/* present flag				*/
  ST_INT32 AE_invoke_id;		/* AE invocation ID    			*/
  ST_INT p_sel_len;			/* P-selector length			*/
  ST_UCHAR p_sel[MAX_P_SEL];		/* P-selector				*/
  ST_INT s_sel_len;			/* S-selector length			*/
  ST_UCHAR s_sel[MAX_T_SEL];		/* S-selector				*/
  ST_INT t_sel_len;			/* T-selector length			*/
  ST_UCHAR t_sel[MAX_T_SEL];		/* T-selector				*/
  ST_INT net_addr_len;			/* Network address length		*/
  ST_UCHAR net_addr[MAX_N_SEL];		/* Network address			*/
  ST_INT port;				/* TCP/IP port number			*/
  ST_CHAR ip_addr[HOST_NAME_LEN + 1];	/* TCP/IP dotted decimal or host name	*/

/*#if defined(ACSE_AUTH_ENABLED) */
  S_SEC_ENCRYPT_CTRL encryptCtrl;	/* encryption info			*/ 
/*#endif*/ /* ACSE_AUTH_ENABLED */

/*#ifdef PRODUCT_ONLY_VMS_ALPHA  */
  ST_INT ChannelTypeToUse; 
/*#endif                         */
} ;

typedef struct dib_entry DIB_ENTRY;


/************************************************************************/
#if defined (MARBEN)
#if defined (_WIN32)

typedef struct
  {
  ST_CHAR host_name[MAX_HOST_LEN + 1];
  ST_INT net_addr_len;		/* Network address length		*/
  ST_UCHAR net_addr[MAX_N_SEL];	/* Network address			*/
  ST_CHAR ip_addr[HOST_NAME_LEN + 1];	/* TCP/IP dotted decimal or host name	*/
  } HOSTNAME_INFO;

#endif	/* defined (_WIN32) */
#endif  /* defined (MARBEN) */

/************************************************************************/
/* Variables used for reading DIB file					*/

extern ST_BOOLEAN s_manual_dib_load;         /* User to set DIB Table        */
extern ST_INT num_dib_entries;           /* Number of entries            */
extern DIB_ENTRY *dib_table;            /* Pointer to dib table         */

#endif	/* !DIB_ENTRY_DEFINED	*/
#endif  /* defined MARBEN || DECNP5 */

#define TYPE_ORIGINAL		0
#define TYPE_UNIVERSAL		1
extern ST_INT s_activate_type;		/* local name activation type	*/


/************************************************************************/
/************************************************************************/
/* The structure below is used to identify PCI				*/
/* Used by s_lookup_pci ().						*/
/************************************************************************/

struct pc
{
  ST_INT asn_index;	/* index into asn_table				*/
  ST_INT tsn_index;	/* index into tsn_table				*/
} ;

typedef struct pc PC;

/************************************************************************/

ST_RET s_start (ST_VOID);
ST_VOID s_end (ST_VOID);

extern ST_VOID (*s_event_notify) (ST_VOID);
extern ST_VOID (*s_usr_nap) (ST_VOID);

extern ST_CHAR *(*s_send_priv_data) (ST_INT *);

ST_BOOLEAN s_serve (ST_VOID);

ST_BOOLEAN s_read_mail (ST_VOID);
ST_VOID s_send_mail (ST_VOID);

ST_INT s_lookup_pci (ST_INT chan, ST_INT pci_mask, PC *pc_arr);


/* User defined 'done' functions                                        */

ST_VOID s_activate_done (ST_CHAR *name, ST_RET retcode);
ST_VOID s_deactivate_done (ST_CHAR *name, ST_RET retcode);
ST_VOID s_listen_done (ST_INT chan, ST_RET retcode);
ST_VOID s_canlisten_done (ST_INT chan, ST_RET retcode);
ST_VOID s_assreq_done (ST_INT chan, ST_RET retcode);
ST_VOID s_assrsp_done (ST_INT chan, ST_RET retcode);
ST_VOID s_relreq_done (ST_INT chan, ST_RET retcode);
ST_VOID s_relrsp_done (ST_INT chan, ST_RET retcode);
ST_VOID s_u_abort_done (ST_INT chan, ST_RET retcode);
ST_VOID s_transfer_done (ST_INT chan, ST_RET retcode);
ST_VOID s_receive_done (ST_INT chan, ST_RET retcode);


/* User defined 'indication' functions                                  */

ST_VOID s_associate_ind (ST_INT chan, 
			 ST_INT num_pc_defs, PC_DEF *pc_deflist, 
			 ST_INT num_u_data, U_DATA *u_data_list,
			 ST_BOOLEAN matched);
ST_VOID s_associate_cnf (ST_INT chan,
			 ST_INT num_result, PC_DEF *result_list,
			 ST_INT num_u_data, U_DATA *u_data_list, 
			 ST_RET retcode);
ST_VOID s_release_ind (ST_INT chan, ST_INT reason, 
		       ST_INT num_u_data, TRANS_DATA *u_data_list);
ST_VOID s_release_cnf (ST_INT chan, ST_INT reason,
		       ST_INT num_u_data, TRANS_DATA *u_data_list);
ST_VOID s_u_abort_ind (ST_INT chan, ST_INT reason,
		       ST_INT num_u_data, TRANS_DATA *u_data_list);
ST_VOID s_p_abort_ind (ST_INT chan, ST_INT reason);
ST_VOID s_transfer_ind (ST_INT chan, 
			ST_INT num_trans, TRANS_DATA *data,
			ST_BOOLEAN eom);

/* SUIC command functions						*/

ST_RET s_reg_title (ST_INT chan, ST_CHAR *name);
ST_RET s_activate (ST_CHAR *name);
ST_RET s_deactivate (ST_CHAR *name);
ST_RET s_load_part_info (ST_INT chan, ST_CHAR *name);
ST_RET s_listen (ST_INT chan, ST_UINT ap_context_mask);
ST_RET s_cancel_listen (ST_INT chan);
ST_RET s_associate_req (ST_INT chan, ST_UINT ap_context_mask,
			ST_INT num_pc_defs, PC_DEF *pc_deflist,
			ST_INT num_u_data, U_DATA *u_data_list);
ST_RET s_associate_rsp (ST_INT chan, ST_UINT ap_context_mask,
			ST_INT reason, ST_INT num_result, PC_DEF *result_list,
			ST_INT num_u_data, U_DATA *u_data_list);
ST_RET s_release_req (ST_INT chan, ST_INT reason, 
		      ST_INT num_u_data, TRANS_DATA *u_data_list);
ST_RET s_release_rsp (ST_INT chan, ST_INT reason, 
		      ST_INT num_u_data, TRANS_DATA *u_data_list);
ST_RET s_u_abort (ST_INT chan, ST_INT reason, 
		  ST_INT num_u_data, TRANS_DATA *u_data_list);
ST_RET s_receive (ST_INT chan);
ST_RET s_transfer_req (ST_INT chan,
		       ST_INT num_trans, TRANS_DATA *data, ST_BOOLEAN eom);
ST_VOID s_free_databuf (ST_CHAR *buf);
ST_VOID s_except (ST_INT except_code);

ST_RET s_set_ap_title (ST_CHAR *name, ST_BOOLEAN en, MMS_OBJ_ID *ap_title);
ST_RET s_set_ae_qual (ST_CHAR *name, ST_BOOLEAN en, ST_INT32 ae_qual);
ST_RET s_set_ap_invoke (ST_CHAR *name, ST_BOOLEAN en, ST_INT32 ap_invoke);
ST_RET s_set_ae_invoke (ST_CHAR *name, ST_BOOLEAN en, ST_INT32 ae_invoke);

ST_UINT s_install_ap_ctxt (MMS_OBJ_ID *ap_ctxt);
ST_UINT s_install_asn (MMS_OBJ_ID *asn);
ST_UINT s_install_tsn (MMS_OBJ_ID *tsn);

ST_VOID s_perror (ST_RET errcode);
ST_VOID s_perror_log (FILE *logfile, ST_RET errcode);
ST_VOID s_perror_str (ST_CHAR *errbuf, ST_INT max_len, ST_RET errcode);

ST_BOOLEAN s_chk_idle (ST_VOID);

APP_REF *s_find_proc (ST_CHAR *arname);
ST_INT s_find_arname (APP_REF *app_ref_ptr, ST_BOOLEAN match_ae_qual,
	ST_CHAR *ar_ptr);
ST_RET s_find_paddr (ACSE_AR_INFO *ar_info, ST_CHAR *ar_ptr);

ST_RET s_chk_resource (ST_INT chan, ST_INT *out_size, 
     		       ST_INT *pend_size, ST_LONG *mem_size);


/* ---------------------- DIB_ENTRY_DEFINED start -----------------------------	*/
#if defined (DIB_ENTRY_DEFINED)

ST_RET s_add_rem_arname (DIB_ENTRY *dib);
ST_RET s_del_rem_arname (ST_CHAR *name);
ST_RET s_mod_rem_arname (DIB_ENTRY *dib);
ST_RET s_get_rem_arname (ST_CHAR *name, DIB_ENTRY *dib);
#if defined (MARBEN) && defined (_WIN32)
ST_RET s_create_hostname (HOSTNAME_INFO *info);
#endif

#if defined (MARBEN)
/* these are user functions (moved from marb_def.h here)			*/
ST_RET init_dirser (ST_VOID);
DIB_ENTRY *find_dib_entry (ST_CHAR *name);
DIB_ENTRY *find_loc_dib_entry (ST_CHAR *name);
DIB_ENTRY *find_rem_dib_entry (ST_CHAR *name);
#endif  /* defined (MARBEN) */

/* Since the MMS-EASE can run over Marben SUIC or LITE Stack we have to deal	*/
/* with different DIB_ENTRY structures. To make the same code work both	ways	*/
/* field access macros should do the trick.					*/

#if defined(MMSEASE_MOSI)
#define DIB_PSEL_LEN(de)	((de)->pres_addr.psel_len)
#define DIB_PSEL(de)		((de)->pres_addr.psel)
#define DIB_SSEL_LEN(de)	((de)->pres_addr.ssel_len)
#define DIB_SSEL(de)		((de)->pres_addr.ssel)
#define DIB_TSEL_LEN(de)	((de)->pres_addr.tsel_len)
#define DIB_TSEL(de)		((de)->pres_addr.tsel)
#define DIB_TP_TYPE(de)		((de)->pres_addr.tp_type)
#define DIB_NSAP_LEN(de)	((de)->pres_addr.nsap_len)
#define DIB_NSAP(de)		((de)->pres_addr.netAddr.nsap)
#define DIB_IPADDR_ULONG(de,f)	((de)->pres_addr.netAddr.ip)
#define DIB_PORT(de)		((de)->pres_addr.port)
/* following defs values are different between MARBEN and MMSEASE_MOSI		*/
#define DIB_TP_TYPE_TCP		TP_TYPE_TCP
#define DIB_TP_TYPE_TP4		TP_TYPE_TP4

#elif defined(MARBEN)
/* NOTE: casting some of the fields to be the same as in MMS-LITE PRES_ADDR	*/
#define DIB_PSEL_LEN(de)	((ST_UINT)(de)->p_sel_len)
#define DIB_PSEL(de)		((de)->p_sel)
#define DIB_SSEL_LEN(de)	((ST_UINT)(de)->s_sel_len)
#define DIB_SSEL(de)		((de)->s_sel)
#define DIB_TSEL_LEN(de)	((ST_UINT)(de)->t_sel_len)
#define DIB_TSEL(de)		((de)->t_sel)
#define DIB_TP_TYPE(de)		((de)->transport)
#define DIB_NSAP_LEN(de)	((ST_UINT)(de)->net_addr_len)
#define DIB_NSAP(de)		((de)->net_addr)
#define DIB_IPADDR_ULONG(de,f)	(convertIPAddr ((de)->ip_addr,f))
#define DIB_PORT(de)		((ST_UINT16)(ST_UINT)(de)->port)
/* following defs values are different between MARBEN and MMSEASE_MOSI		*/
#define DIB_TP_TYPE_TCP		TCP
#define DIB_TP_TYPE_TP4		TP4
#endif  /* defined (MARBEN) */


#if defined (MARBEN) || defined(MMSEASE_MOSI)
/************************************************************************/
/* General address matching defines, control, functions			*/

ST_RET dib_match_remote_ar (DIB_MATCH_CTRL *matchCtrl, ST_INT chan, 
			    DIB_ENTRY **dib_entry_out);
ST_RET dib_match_local_ar  (DIB_MATCH_CTRL *matchCtrl, ST_INT chan, 
			    DIB_ENTRY **dib_entry_out);
ST_INT dib_cmp_local_addr  (DIB_MATCH_CTRL *matchCtrl, ST_INT chan, 
			    DIB_ENTRY *dib_entry);
ST_INT dib_cmp_remote_addr (DIB_MATCH_CTRL *matchCtrl, ST_INT chan, 
			    DIB_ENTRY *dib_entry);
#endif /* defined (MARBEN) || defined(MMSEASE_MOSI) */

#endif  /* DIB_ENTRY_DEFINED */
/* ---------------------- DIB_ENTRY_DEFINED end -------------------------------	*/


/* ---------------------- security functions ---------------------------------- */
ST_RET s_set_security_info (ST_INT chan, S_SEC_SPARAMS *secParams);
ST_RET s_get_security_info (ST_INT chan, S_SEC_SPARAMS *secParams);
ST_RET s_free_security_info (ST_INT chan);
ST_RET s_free_part_security_info (ST_INT chan);

#if defined(SUIC_LIB)
/* SUIC_LIB is defined in compilation of SUIC lib, we do not need to compile	*/
/* the mds.h in other libs!							*/
/* The MAP30_ACSE define was deleted from here as it brings the lber.h that	*/
/* defines sockbuf that conflicts with "/usr/include/sys/socketvar.h" on AIX.	*/
/* In application code if X.500 Directory or LDAP support is needed the user	*/
/* code will have to include this piece of code (in DIRECTORY_SUPPORT define).	*/
#if DIRECTORY_SUPPORT
#include "mds.h"
#ifdef _WIN32
/* NOTE: the mds.h includes ldap.h including msdos.h. The last file defines	*/
/*       _WINDOWS (and other system defines: __MSDOS__, WINDOWS...) that we	*/
/*       probably want to keep undefined.					*/
#undef _WINDOWS
#undef __MSDOS__
#endif  /* _WIN32 */

#endif  /* DIRECTORY_SUPPORT */
#endif  /* SUIC_LIB */

#ifdef __cplusplus
}
#endif
									  
#endif	/* SUICACSE_H */

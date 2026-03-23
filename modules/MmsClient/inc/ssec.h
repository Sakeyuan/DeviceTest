/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*      (c) Copyright Systems Integration Specialists Company, Inc.,    */
/*      	 2003 - 2006, All Rights Reserved                       */
/*                                                                      */
/* MODULE NAME : ssec.h		                                        */
/* PRODUCT(S)  :                                                        */
/*                                                                      */
/* MODULE DESCRIPTION : This module provides user defines for SISCO's	*/
/*			Security Extensions for MMS-EASE, MMS-EASE Lite,*/
/*			ICCP, AXS4-MMS, AXS4-ICCP products.		*/
/*                                                                      */
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :                            */
/*                                                                      */
/* MODIFICATION LOG :                                                   */
/*  Date     Who   Rev     Comments                                     */
/* --------  ---  ------   -------------------------------------------  */
/* 08/28/06  EJV    78     MMS-LITE SECURE: chg version to 1.10.	*/
/* 03/02/06  EJV    77     Chg S_SEC_VERSION_STR to 1.10 (VS .NET 2005)	*/
/* 01/04/06  EJV    76     Added DLLs incompatibility comments.		*/
/* 10/25/05  EJV    75     Chg S_SEC_LITESECURE_NAME to fit identify	*/
/* 09/22/05  EJV    74     Any new build use S_SEC_VERSION_STR 1.04	*/
/* 08/09/05  EJV    73     MMS-LITE SECURE: chg version to 1.0050.	*/
/*			   Add extern LocalCertStorePath,CACertStorePath*/
/* 02/25/05  MDE    72     Added sSecAssocConfChkEx			*/
/* 01/31/05  ASK    71     Fix ST_MUTEX_SEM_SSEC to compile on QNX 	*/
/* 01/18/05  ASK    70     Chg ver back to 1.03 for (Win release) 	*/
/* 01/11/05  ASK    69     Added ST_MUTEX_SEM_SSEC for non-Windows  	*/
/* 01/10/05  ASK    68     Added ST_MUTEX_SEM_SSEC struct to ensure  	*/
/*			   alignment between S_SEC_CFG between 		*/
/*			   secman.dll and calling application		*/
/* 01/06/05  ASK    67     Temporarily Chg ver to 1.0260 for Symantec	*/
/*			   release.					*/
/* 09/29/04  EJV    66     Chg ver to 1.03 for (Win release)		*/
/* 09/02/04  EJV    65     Added S_SEC_PATH for sun.			*/
/* 08/24/04  EJV    64     Chg from WIN32 to _WIN32.			*/
/*			   Chg ver to 1.0251 for Windows ICCP-SECURE.	*/
/* 04/08/04  EJV    63     _AIX: added S_SEC_PATH.			*/
/*			   Chg ver to 1.02 for (AIX release)		*/
/* 04/01/04  EJV    62     Chg ver to 1.0051 for (AIX beta)		*/
/* 03/30/04  ASK    61     Added secManLckEnd proto 			*/
/*			   Added ssleCertFileToText proto for AIX	*/
/* 03/12/04  ASK    60     Added ssleCertFileToXml proto for AIX	*/
/* 03/10/04  EJV    59     Corr ver to 1.0050 for (AIX beta)		*/
/* 03/05/04  MDE    58     Added AE Title for AR Security mode		*/
/* 02/16/04  EJV    57     Chg S_SEC_DEF_SSL_PORT to 3782.		*/
/*			   Added S_SEC_PORT_DELIM_CHAR.			*/
/*			   Chg ver to 1.0150 for (AIX beta)		*/
/* 02/09/04  EJV    56     Changed S_SEC_LITESECURE_NAME.		*/
/* 01/16/04  EJV    55     Del forward reference to DIB_MATCH_CTRL.	*/
/*			   Added _WIN32 for dllimport secManCfgChange.	*/
/* 01/12/04  EJV    54     Added secManCfgChange proto for MMS_LITE	*/
/* 12/04/03  ASK    53     Added secManCfgChange proto			*/
/* 10/31/03  ASK    52	   Rem CName type 'Unknown'			*/
/* 10/21/03  EJV    51	   Rem sSecFreeSecParam, sSecFreePartSecParam	*/
/* 10/20/03  ASK    50	   Added params to sSecUpdate, added 		*/
/*                         secManGetDebugSel proto, added 		*/
/*			   crlDropExisting to cfg		 	*/
/* 10/16/03  ASK    49	   Added sSecEnd and stopSSLEngine protos,	*/
/*			   Chg ver to 1.00				*/
/* 10/10/03  MDE    48     Added crlCheckTime				*/
/* 09/30/03  EJV    47     MMS-LITE: added S_SEC_LITESECURE_VERSION_STR */
/*			     and S_SEC_LITESECURE_NAME.			*/
/*			   Redefined macros SECLOG..._ to SEC_LOG_...	*/
/*			   Added S_SEC_SSLE_LOG_DATA, S_SEC_SOCK_LOG_TX,*/
/*			     S_SEC_SOCK_LOG_RX (reworked numbers).	*/
/*			   Chg secLogMasks from ST_ULONG to ST_UINT.	*/
/*			   MMS_LITE: Added global secManCfgXmlFile	*/
/* 09/29/03  EJV    46     Chg ver to 0.9955 (snap.exe fix)		*/
/* 08/25/03  EJV    45     Moved protos with GEN_SOCK to ssec_int.h	*/
/* 08/21/03  ASK    44     Add clearTime to S_MACE_INFO struct. Chg some*/
/*			   protos to pass this to verify time sig	*/
/* 08/21/03  EJV    43     Added setGenSockSSL, ssecGetCipherSuite,	*/
/*                           sSecGetCertId, sSecGetCertCtrl protos.	*/
/*                         Chg ver to 0.9954				*/
/* 07/28/03  EJV    42     Chg MMS_LITE protos.				*/
/* 07/18/03  ASK    41     Add software lock protos from secmanlck.c	*/
/* 07/16/03  MDE    40     Changes to appAuthRequired values		*/
/* 07/14/03  ASK    39     Add sSecUpdate and sslUpdate protos	 	*/
/* 06/30/03  ASK    38     Added secManAccessCfg and secManReleaseCfg 	*/
/*			   protos. #include glbsem.h. Add mutex to	*/
/* 			   S_SEC_CONFIG	struct.				*/
/* 06/26/03  EJV    37     Chg GSOCK_... to SOCK_... log macros		*/
/* 06/25/03  EJV    36     Chg ver to 0.9953				*/
/* 06/24/03  ASK    35     Added dynamic config API func protos	 	*/
/* 06/20/03  EJV    34     Added SNAP_EXIT_EVENT_NAME.			*/
/* 06/20/03  ASK    33	   add S_SEC_EVENT_REKEY_FAILURE define         */ 
/* 06/19/03  MDE    32     Added rekeying to S_CERT_CTRL 		*/
/* 06/16/03  EJV    31     Del m_match.h, s_match.h; added suicacse.h;	*/
/*			   Changed M_MATCH_CTRL to DIB_MATCH_CTRL.	*/
/* 06/12/03  MDE    30     sSecAssocConfChk added srcChkDest parameter.	*/
/* 06/12/03  MDE    29     Fixed up MMS_LITE over Marben		*/
/* 06/12/03  MDE    28     Added M_MATCH support			*/
/* 05/27/03  EJV    27     Chg ver to 0.9952				*/
/* 05/27/03  EJV    26     sSecAssocIndChk added parameter srcChkDest.	*/
/* 05/27/03  EJV    25     S_SEC_PORT_DELIM_STR chg to '+' for compatib.*/
/* 05/23/03  ASK    24     Changed secManLog to secManEventLog. Added	*/
/*                         event define S_SEC_EVENT_SSL_FAILURE. Change */
/*			   sSecPrintSrlNum to secManPrintSrlNum.	*/
/* 05/14/03  MDE    23     Fixed up rekey parameters			*/
/* 05/09/03  MDE    22     Corrected S_CIPHER_0C04xx, _0D02xx to use MD5*/
/* 05/06/03  ASK    21     Add sSecUsrStart proto, changed secManStart  */
/*                         and startSSLEngine protos for new logging.   */
/* 05/01/03  ASK    20     Change to use S_SEC_SPARAMS for SUIC 	*/
/* 04/30/03  ASK    19     Add public key to S_CERT_INFO. Changed 	*/			
/*			   S_SEC_MAX_SIGNED_TIME_LEN to 128 bytes. 	*/
/*			   Added protos for new signing time functions. */
/*			   Added sSecCmpIssuer proto.			*/
/* 04/29/03  EJV    18     Added S_SEC_MAX_IP_ADDR_LEN			*/
/*			   Chg ver to 0.9951				*/
/* 04/21/03  MDE    17     Added cipher suites				*/
/* 04/18/03  MDE    16     S_SEC_CONFIG changes				*/
/* 04/18/03  MDE    15     Added S_APP_AUTHREQ_xxx defines 		*/
/* 04/18/03  MDE    14     Added Masks for Cipher Suite elements 	*/
/* 04/17/03  EJV    13     Moved asn1log.h.				*/
/* 04/16/03  EJV    12     Added version string.			*/
/* 04/15/03  JRB    11     Add forward ref for mvl_net_info.		*/
/* 04/15/03  ASK    10     Added sSecPrintSrlNum proto.			*/
/* 04/11/03  EJV    09     sSecAuthChk: changed ret to ST_RET		*/
/* 04/10/03  EJV    08     Added sSecCmpCertId proto.			*/
/* 04/10/03  MDE    07     Added ArSec support				*/
/* 04/09/03  MDE    06     Merged ssecusr.c function protos		*/
/* 04/09/03  MDE    05     Added AR security context declarations	*/
/* 04/08/03  EJV    05     Added defs for all log masks in secLogMasks.	*/
/*			   Changed secLogMasks to ST_ULONG.		*/
/* 04/07/03  EJV    04     Added protos from ssecusr.c			*/
/* 04/04/03  ASK    03     Changed serial number format. Added 		*/
/*			   SECLOG_DATA and SECLOG_DEBUG masks. Added 	*/
/*			   startSSLEngine proto.			*/
/* 03/04/03  EJV    02     Added IPAddr string parsing tokens           */
/* 02/21/03  MDE    01     Created                                      */
/************************************************************************/

#ifndef S_SEC_INCLUDED
#define S_SEC_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "glbsem.h"
#include "acseauth.h"
#include "gen_list.h"
#include "asn1r.h"
#include "dibmatch.h"

#if !defined(MMS_LITE) || defined(MAP30_ACSE)
/* for MMS-EASE, MMS-EASE Lite based products over Marben Stack */
#define S_SEC_VERSION_STR	"1.10"
#else
/* for MMS-EASE Lite products over LEAN-T Stack */
#define S_SEC_LITESECURE_NAME		"MMS-LITE-SECURE"
#define S_SEC_LITESECURE_VERSION_STR	"1.10"
#endif

#if !defined(MMS_LITE) || defined(MAP30_ACSE)
/* for MMS-EASE, MMS-EASE Lite based products over Marben Stack */
#if !defined(_WIN32)
/* Security installation path on UNIX systems is fixed but diff on each system */
#if defined(_AIX)
#define S_SEC_PATH	"/usr/lpp/osill2/security"
#else  /* other UNIX systems */
#define S_SEC_PATH	"/usr/osill2/security"
#endif
#endif /* !defined(_WIN32) */
#endif



/************************************************************************/
/************************************************************************/
/* NOTES ON CERTIFICATE NAME MATCHING 					*/
/* This sSec API has a number of functions that must match certificates	*/
/* based on a S_CERT_ID data structure. In all cases the matching 	*/
/* process works as follows:						*/
/*									*/
/*   The matching can be based on certificate number, subject,		*/
/*   issuer, or any combination of these as specified in the certId.	*/
/*   For instance, the following specifications are valid:		*/
/*	1. Serial Number only						*/
/*	2. Subject only							*/
/*	3. Issuer only							*/
/*	4. Subject and Issuer						*/
/*	5. Subject and Serial Number					*/
/*	6. Issuer and Serial Number					*/
/*	7. Subject, Issuer, Serial Number				*/

/* Note that the all elements of the input 'certId' must be present and	*/
/* match exactly in the local certificate. That is, all elements of the	*/
/* certificate name must be present and in the specified order.		*/

/************************************************************************/
/************************************************************************/
#define SEC_LOG_ERR		0x00000001
#define SEC_LOG_NERR		0x00000002
#define SEC_LOG_FLOW		0x00000004
#define SEC_LOG_DATA  		0x00000008
#define SEC_LOG_DEBUG 		0x00000010

extern ST_UINT sec_debug_sel;

/************************************************************************/
/*			LOGGING						*/
/* The logging masks defined here are used to set the secLogMasks field	*/
/* in the S_SEC_CONFIG (defined below). The application can set the	*/
/* proper module logging masks by examining the secLogMasks.		*/
/* Note that ERR logging is set by default to ON in all modules.	*/
/* The name of masks have been copied here and prefixed with S_SEC_...	*/
/* for easy reference.							*/

/* log masks for sec_debug_sel (ssec.h) */
#define S_SEC_SEC_LOG_NERR		0x00000001
#define S_SEC_SEC_LOG_FLOW		0x00000002
#define S_SEC_SEC_LOG_DATA		0x00000004
#define S_SEC_SEC_LOG_DEBUG		0x00000008
/* log masks for ssle_debug_sel (sslEngine.h) */
#define S_SEC_SSLE_LOG_NERR		0x00000010
#define S_SEC_SSLE_LOG_FLOW		0x00000020 
#define S_SEC_SSLE_LOG_DATA		0x00000040 
#define S_SEC_SSLE_LOG_DEBUG		0x00000080 
/* log masks for snap_debug_sel (snaplog.h) */
#define S_SEC_SNAP_LOG_NERR		0x00000100
#define S_SEC_SNAP_LOG_FLOW		0x00000200
/* log masks for sock_debug_sel (gensock2.h) */
#define S_SEC_SOCK_LOG_NERR		0x00000400
#define S_SEC_SOCK_LOG_FLOW		0x00000800
#define S_SEC_SOCK_LOG_TX		0x00001000
#define S_SEC_SOCK_LOG_RX		0x00002000
/* log masks for sx_debug_sel (sx_defs.h) */
#define S_SEC_SX_LOG_NERR 		0x00004000
#define S_SEC_SX_LOG_DEC  		0x00008000
#define S_SEC_SX_LOG_ENC  		0x00010000
#define S_SEC_SX_LOG_FLOW  		0x00020000
#define S_SEC_SX_LOG_DEBUG 		0x00040000
/* log masks for asn1_debug_sel (asn1r.h) */
#define S_SEC_ASN1_LOG_NERR		0x00080000
#define S_SEC_ASN1_LOG_DEC		0x00100000
#define S_SEC_ASN1_LOG_ENC		0x00200000
/* log masks for gs_debug_sel (glbsem.h) */
#define S_SEC_GS_LOG_NERR 		0x00400000 
#define S_SEC_GS_LOG_FLOW 		0x00800000 
/* log masks for chk_debug_en (mem_chk.h) */
#define S_SEC_MEM_LOG_CALLOC		0x01000000
#define S_SEC_MEM_LOG_MALLOC		0x02000000 
#define S_SEC_MEM_LOG_REALLOC		0x04000000 
#define S_SEC_MEM_LOG_FREE		0x08000000 
/* the rest of bits are used for memory debugging flags: */
#define S_SEC_m_check_list_enable	0x10000000
#define S_SEC_m_find_node_enable	0x20000000
#define S_SEC_m_no_realloc_smaller	0x40000000 
/*					0x80000000 free */

/************************************************************************/
/* SNAP Startup Event Names */

#if defined(_WIN32)
#define SNAP_STARTED_EVENT_NAME 	"snap.started"
#define SNAP_RUNNING_EVENT_NAME		"snap.running"
#define SNAP_EXIT_EVENT_NAME		"snap.exit"
#endif

/************************************************************************/
/* Allowed authType values */

#define S_SEC_AUTHTYPE_NONE		0
#define S_SEC_AUTHTYPE_CERTIFICATE	1
#define S_SEC_AUTHTYPE_SYMMETRIC	2

/************************************************************************/
/* General Defines */

/* Maximum signed time data size */
#define S_SEC_MAX_SIGNED_TIME_LEN 128

/* Help in sizing the asn1 buffer (really more like 25 ...) */
#define S_SEC_ASN1_BUF_OH 50

/* Maximum size of the certificate serial number (in bytes) */
#define S_SEC_MAX_SERIAL_LEN 64

/************************************************************************/
/* MACE decode error codes */

#define MACE_ASN1_INCOMPLETE			0x9102
#define MACE_ASN1_SYMMETRIC_NOT_SUPPORTED	0x9103

/************************************************************************/
/* Default Ports							*/

/* SSL Port */
#define S_SEC_DEF_SSL_PORT		3782

/* IPC Ports */
#define S_SEC_DEF_STACK_PORT		10042
#define S_SEC_DEF_SNAP_PORT		10043
#define S_SEC_DEF_SNAP_CONTROL_PORT	10044
#define S_SEC_DEF_SNAP_MONITOR_PORT	10045


/************************************************************************/
/* Remote address and security info formatting tokens			*/

#define S_SEC_IP_ADDR_DELIM_STR	"SSL:"
#define S_SEC_PORT_DELIM_STR	"+"
#define S_SEC_PORT_DELIM_CHAR	'+'	/*  same as above but in ' '	*/
#define S_SEC_CIPHER_DELIM_STR	"+"
#define S_SEC_CERT_ID_DELIM_STR	","

#define S_SEC_MAX_IP_ADDR_LEN	20

/************************************************************************/
/* Security Subsystem Error Codes */

#define S_SEC_ERR_VALIDITY_TOOSOON             0xA001
#define S_SEC_ERR_VALIDITY_EXPIRED             0xA002
#define S_SEC_ERR_CNAME_TYPE_UNKNOWN           0xA003
#define S_SEC_ERR_CNAME_MISSING                0xA004
#define S_SEC_ERR_CNAME_EXTRA                  0xA005
#define S_SEC_ERR_CNAME_MISMATCH               0xA006
#define S_SEC_ERR_TIME_SEAL_INVALID            0xA007
#define S_SEC_ERR_TIME_SEAL_TIME_WINDOW        0xA008

/************************************************************************/
/* Cipher Suite Selection Defines */

#define S_MAX_ALLOWED_CIPHER_SUITES     49

/* Masks for Cipher Suite elements */
#define S_KEYX_MASK           0xff0000
#define S_CRYPT_MASK          0x00ff00
#define S_HASH_MASK           0x0000ff


/* Key Exchange Algorithms */
#define S_KEYX_NONE           0x000000
#define S_KEYX_NULL           0x010000
#define S_KEYX_RSA            0x020000
#define S_KEYX_RSA_EX         0x030000
#define S_KEYX_DH_DSS         0x040000
#define S_KEYX_DH_DSS_EX      0x050000
#define S_KEYX_DH_RSA         0x060000
#define S_KEYX_DH_RSA_EX      0x070000
#define S_KEYX_DHE_DSS        0x080000
#define S_KEYX_DHE_DSS_EX     0x090000
#define S_KEYX_DHE_RSA        0x0A0000
#define S_KEYX_DHE_RSA_EX     0x0B0000
#define S_KEYX_DH_ANON        0x0C0000
#define S_KEYX_DH_ANON_EX     0x0D0000
#define S_KEYX_FORTEZZA_DMS   0x0E0000

/* Encryption Algorithms */
#define S_CRYPT_NONE          0x000000
#define S_CRYPT_NULL          0x000100
#define S_CRYPT_RC4_40        0x000200
#define S_CRYPT_RC4_56        0x000300
#define S_CRYPT_RC4_128       0x000400
#define S_CRYPT_RC2_CBC_40    0x000500
#define S_CRYPT_IDEA_CBC      0x000600
#define S_CRYPT_DES40_CBC     0x000700
#define S_CRYPT_DES_CBC       0x000800
#define S_CRYPT_3DES_EDE_CBC  0x000900
#define S_CRYPT_FORTEZZA_CBC  0x000A00
#define S_CRYPT_AES_128_CBC   0x000B00
#define S_CRYPT_AES_256_CBC   0x000C00

/* Hash Algorithms */
#define S_HASH_NONE           0x000000
#define S_HASH_NULL           0x000001
#define S_HASH_MD5            0x000002
#define S_HASH_SHA            0x000003

/* Cipher Suite Seletion */
#define S_CIPHER_NOSSL	      0x000000
#define S_CIPHER_ANY          0xFFFFFF

/* 49 Cipher Suites are defined by SSL 3.0 and TLS 1.0 */
/* Bit fields:		  Key Exchange		Encryption		Hash	*/
#define S_CIPHER_NONE    (S_KEYX_NONE         | S_CRYPT_NONE          | S_HASH_NONE)
#define S_CIPHER_010103  (S_KEYX_NULL         | S_CRYPT_NULL          | S_HASH_SHA)
#define S_CIPHER_020102  (S_KEYX_RSA          | S_CRYPT_NULL          | S_HASH_MD5)
#define S_CIPHER_020103  (S_KEYX_RSA          | S_CRYPT_NULL          | S_HASH_SHA)
#define S_CIPHER_020402  (S_KEYX_RSA          | S_CRYPT_RC4_128       | S_HASH_MD5)
#define S_CIPHER_020403  (S_KEYX_RSA          | S_CRYPT_RC4_128       | S_HASH_SHA)
#define S_CIPHER_020603  (S_KEYX_RSA          | S_CRYPT_IDEA_CBC      | S_HASH_SHA)
#define S_CIPHER_020803  (S_KEYX_RSA          | S_CRYPT_DES_CBC       | S_HASH_SHA)
#define S_CIPHER_020903  (S_KEYX_RSA          | S_CRYPT_3DES_EDE_CBC  | S_HASH_SHA)
#define S_CIPHER_020B03  (S_KEYX_RSA          | S_CRYPT_AES_128_CBC   | S_HASH_SHA)
#define S_CIPHER_020C03  (S_KEYX_RSA          | S_CRYPT_AES_256_CBC   | S_HASH_SHA)
#define S_CIPHER_030202  (S_KEYX_RSA_EX       | S_CRYPT_RC4_40        | S_HASH_MD5)
#define S_CIPHER_030303  (S_KEYX_RSA_EX       | S_CRYPT_RC4_56        | S_HASH_SHA)
#define S_CIPHER_030502  (S_KEYX_RSA_EX       | S_CRYPT_RC2_CBC_40    | S_HASH_MD5)
#define S_CIPHER_030703  (S_KEYX_RSA_EX       | S_CRYPT_DES40_CBC     | S_HASH_SHA)
#define S_CIPHER_030803  (S_KEYX_RSA_EX       | S_CRYPT_DES_CBC       | S_HASH_SHA)
#define S_CIPHER_040803  (S_KEYX_DH_DSS       | S_CRYPT_DES_CBC       | S_HASH_SHA)
#define S_CIPHER_040903  (S_KEYX_DH_DSS       | S_CRYPT_3DES_EDE_CBC  | S_HASH_SHA)
#define S_CIPHER_040B03  (S_KEYX_DH_DSS       | S_CRYPT_AES_128_CBC   | S_HASH_SHA)
#define S_CIPHER_040C03  (S_KEYX_DH_DSS       | S_CRYPT_AES_256_CBC   | S_HASH_SHA)
#define S_CIPHER_050703  (S_KEYX_DH_DSS_EX    | S_CRYPT_DES40_CBC     | S_HASH_SHA)
#define S_CIPHER_060803  (S_KEYX_DH_RSA       | S_CRYPT_DES_CBC       | S_HASH_SHA)
#define S_CIPHER_060903  (S_KEYX_DH_RSA       | S_CRYPT_3DES_EDE_CBC  | S_HASH_SHA)
#define S_CIPHER_060B03  (S_KEYX_DH_RSA       | S_CRYPT_AES_128_CBC   | S_HASH_SHA)
#define S_CIPHER_060C03  (S_KEYX_DH_RSA       | S_CRYPT_AES_256_CBC   | S_HASH_SHA)
#define S_CIPHER_070703  (S_KEYX_DH_RSA_EX    | S_CRYPT_DES40_CBC     | S_HASH_SHA)
#define S_CIPHER_080403  (S_KEYX_DHE_DSS      | S_CRYPT_RC4_128       | S_HASH_SHA)
#define S_CIPHER_080803  (S_KEYX_DHE_DSS      | S_CRYPT_DES_CBC       | S_HASH_SHA)
#define S_CIPHER_080903  (S_KEYX_DHE_DSS      | S_CRYPT_3DES_EDE_CBC  | S_HASH_SHA)
#define S_CIPHER_090303  (S_KEYX_DHE_DSS_EX   | S_CRYPT_RC4_56        | S_HASH_SHA)
#define S_CIPHER_090703  (S_KEYX_DHE_DSS_EX   | S_CRYPT_DES40_CBC     | S_HASH_SHA)
#define S_CIPHER_090803  (S_KEYX_DHE_DSS_EX   | S_CRYPT_DES_CBC       | S_HASH_SHA)
#define S_CIPHER_080B03  (S_KEYX_DHE_DSS      | S_CRYPT_AES_128_CBC   | S_HASH_SHA)
#define S_CIPHER_080C03  (S_KEYX_DHE_DSS      | S_CRYPT_AES_256_CBC   | S_HASH_SHA)
#define S_CIPHER_0A0803  (S_KEYX_DHE_RSA      | S_CRYPT_DES_CBC       | S_HASH_SHA)
#define S_CIPHER_0A0903  (S_KEYX_DHE_RSA      | S_CRYPT_3DES_EDE_CBC  | S_HASH_SHA)
#define S_CIPHER_0A0B03  (S_KEYX_DHE_RSA      | S_CRYPT_AES_128_CBC   | S_HASH_SHA)
#define S_CIPHER_0A0C03  (S_KEYX_DHE_RSA      | S_CRYPT_AES_256_CBC   | S_HASH_SHA)
#define S_CIPHER_0B0703  (S_KEYX_DHE_RSA_EX   | S_CRYPT_DES40_CBC     | S_HASH_SHA)
#define S_CIPHER_0C0402  (S_KEYX_DH_ANON      | S_CRYPT_RC4_128       | S_HASH_MD5)
#define S_CIPHER_0C0803  (S_KEYX_DH_ANON      | S_CRYPT_DES_CBC       | S_HASH_SHA)
#define S_CIPHER_0C0903  (S_KEYX_DH_ANON      | S_CRYPT_3DES_EDE_CBC  | S_HASH_SHA)
#define S_CIPHER_0C0B03  (S_KEYX_DH_ANON      | S_CRYPT_AES_128_CBC   | S_HASH_SHA)
#define S_CIPHER_0C0C03  (S_KEYX_DH_ANON      | S_CRYPT_AES_256_CBC   | S_HASH_SHA)
#define S_CIPHER_0D0202  (S_KEYX_DH_ANON_EX   | S_CRYPT_RC4_40        | S_HASH_MD5)
#define S_CIPHER_0D0703  (S_KEYX_DH_ANON_EX   | S_CRYPT_DES40_CBC     | S_HASH_SHA)
#define S_CIPHER_0E0103  (S_KEYX_FORTEZZA_DMS | S_CRYPT_NULL          | S_HASH_SHA)
#define S_CIPHER_0E0403  (S_KEYX_FORTEZZA_DMS | S_CRYPT_RC4_128       | S_HASH_SHA)
#define S_CIPHER_0E0A03  (S_KEYX_FORTEZZA_DMS | S_CRYPT_FORTEZZA_CBC  | S_HASH_SHA)

/************************************************************************/
/* Certificate Names                                                    */

/* nameType defines */
#define S_CERT_NAME_TYPE_ANY                	0
#define S_CERT_NAME_TYPE_COMMON_NAME            1
#define S_CERT_NAME_TYPE_COUNTRY                2
#define S_CERT_NAME_TYPE_STATE_OR_PROVINCE      3
#define S_CERT_NAME_TYPE_LOCALITY               4
#define S_CERT_NAME_TYPE_ORGANIZATION           5
#define S_CERT_NAME_TYPE_EMAIL                  6
#define S_CERT_NAME_TYPE_ORGANIZATIONAL_UNIT    7

/* A name in a certificate is a list of names and nane types            */
typedef struct
  {
  DBL_LNK l;
  ST_INT nameType;
  ST_CHAR *nameText;
  } S_CERT_NAME;


/************************************************************************/
/* Identifying a Certificate */

#define S_SERIAL_NUM_NONE -1

typedef struct
  {
  /* Note: adding/removing fields to/from this struct will make older	*/
  /* !!!   applications incompatible with new security DLLs.		*/
  ST_INT       serialLen;	 /* 0 == wildcard  			*/
  ST_UCHAR     serialNumber[S_SEC_MAX_SERIAL_LEN]; /* reverse from mmc	*/
  S_CERT_NAME *issuerCName;      /* NULL  == wildcard  			*/
  S_CERT_NAME *subjectCName;	 /* NULL  == wildcard  			*/
  } S_CERT_ID;


/************************************************************************/
/* Certificate BLOB, X.509 format                                       */

typedef struct
  {
  /* Note: adding/removing fields to/from this struct will make older	*/
  /* !!!   applications incompatible with new security DLLs.		*/
  ST_INT    certDataLen;
  ST_UCHAR *certData;
  } S_CERT_BLOB;

/************************************************************************/
/* Signed Time								*/

typedef struct
  {
  /* Note: adding/removing fields to/from this struct will make older	*/
  /* !!!   applications incompatible with new security DLLs.		*/
  ST_INT    signedTimeLen;
  ST_UCHAR *signedTimeData;
  } S_SIGNED_TIME;

/************************************************************************/
/* MACE authentication information */

typedef struct
  {
  ST_INT authType;
  union
    {
    struct
      {
      S_CERT_BLOB certBlob; 
      time_t signedTimeT; 
      
      /* UTC NULL-terminated time string to be verified */
      ST_UCHAR clearTime[S_SEC_MAX_SIGNED_TIME_LEN];
      /* UTC time string signed by the sender */
      S_SIGNED_TIME signedTime;
      
      } certBased;
    struct
      {
      ST_INT placeHolder;
      } symmetric;
    } u; 
  } S_MACE_INFO;
  

/************************************************************************/
/************************************************************************/
/* Certificate Content Information */

typedef struct
  {
  /* Note: adding/removing fields to/from this struct will make older	*/
  /*       applications incompatible with new security DLLs.		*/
  ST_INT version;
  S_CERT_ID certId;
  struct 
    {
    time_t validNotBefore;
    time_t validNotAfter;
    } validity;

#if 0
  struct
    {
    ST_INT publicKeyAlgorithm;
    ST_INT algorithmIdentifier;
    } algorithms;
#endif
  
  ST_UCHAR *publicKey;
  ST_INT publicKeyLen;
  } S_CERT_INFO;


/************************************************************************/
/************************************************************************/
/* Security Configuration 						*/
/************************************************************************/

/* List of Certificate ID's */
typedef struct
  {
  DBL_LNK l;
  ST_CHAR   *certName;		/* Null if no associated name */
  S_CERT_ID  certId;

/* Rekey Control. These override the global rekey parameters if != 0 	*/
/* They apply only to remote certificates				*/
  ST_LONG  maxTransactionsPerKey;
  time_t   maxTimePerKey;
  ST_INT   rekeyTimeout;			/* In seconds */

/* Internal use */
  ST_INT     cfgId;		
  } S_CERT_CTRL;

/************************************************************************/
/* AR Security Mapping Defines */

/* appAuthRequired defines */
/* These defines come into play only if 'Remote AR Security' is not	*/
/* found for an incoming connection					*/

/* 'Remote AR Security' is required; reject all other indications 	*/
#define  S_APP_AUTHREQ_AR_SEC			0
/* A configured MACE certificate is required				*/
#define  S_APP_AUTHREQ_MACE			1
/* A configured MACE certificate is required and encryption is required	*/
#define  S_APP_AUTHREQ_MACE_ENCRYPTED		2
/* Encryption is required						*/
#define  S_APP_AUTHREQ_ENCRYPTED		3
/* There are no requirements; all connections are acceptable		*/
#define  S_APP_AUTHREQ_NONE			4



#define S_AR_AUTH_MODE_AETITLE		0
#define S_AR_AUTH_MODE_MACE		1
#define S_AR_AUTH_MODE_SSL		2
/* For backward compatibility only */
#define S_AR_AUTH_MODE_NONE		S_AR_AUTH_MODE_AETITLE

/* Note that the Local is used to select the local MACE certificate for	*/
/* connections to a remote with arAuthMode == S_AR_AUTH_MODE_MACE	*/
typedef struct
  {
  DBL_LNK l;
  ST_CHAR   *arName;		/* Local or Remote AR Name 		*/
  S_CERT_CTRL *maceCert;	/* NULL if none configured 		*/

/* User */
  ST_VOID *usr;
  } S_SEC_LOC_AR;

/* Remote AR Security Configuration 					*/
/* Note that the Remote is used to determine the ACSE authentication	*/
/* and encryption to be used for both calling and called connections,	*/
/* and is used in identifying the remote for called connections		*/
typedef struct
  {
  DBL_LNK l;
  ST_CHAR   *arName;		/* Local or Remote AR Name 		*/

  /* Authentication */
  ST_INT     arAuthMode;

/* Authentication Certificate:	*/
/*  arAuthMode == S_AR_AUTH_MODE_MACE   : Remote MACE cert 		*/
/*  arAuthMode == S_AR_AUTH_MODE_SSL    : Remote SSL cert  		*/
/*  arAuthMode == S_AR_AUTH_MODE_NONE   : NULL	 			*/
  S_CERT_CTRL *authCert;

/* Encryption */
  ST_INT     encryptMode;
  ST_UINT16  sslPort;		 /* For S_SEC_ENCRYPT_SSL 		*/

/* User */
  ST_VOID *usr;
  } S_SEC_REM_AR;

#if defined(_WIN32)
/* Placeholder struct kept only for compatibility purposes with older
 * applications. Used in main S_SEC_CFG struct below. 
 */
typedef struct 
  {
  ST_INT		mutexType;	/* GS_MUTEX_UNNAMED (_NAMED)	*/
  union
    {
    HANDLE		hMutex;		/* for named mutex		*/
    CRITICAL_SECTION    cs;		/* for unnamed mutex	       	*/
    } u; 
  } ST_MUTEX_SEM_SSEC;
#else
#define ST_MUTEX_SEM_SSEC ST_MUTEX_SEM
#endif 

/************************************************************************/
/**** Main Configuration Structure ****/

#define S_SSL_MAX_LISTEN_PORTS          10
typedef struct
  {
  /* Note: adding/removing fields to/from this struct will make older	*/
  /* !!!   applications incompatible with new security DLLs.		*/

  /****** General Configuration ******/
  ST_BOOLEAN secureModeEnabled;

  /* Old struct kept around for alignment purposes with old(er) apps */
  ST_MUTEX_SEM_SSEC obsoleteCfgMutex;
  
  /****** MACE Level Configuration ******/
  /* Time Signature Window */
  time_t timeSealWindow;

  /****** Certificate Lists ******/
  /* Remote Certificates and associated AR Names */
  S_CERT_CTRL *sslRemoteCertList;

  /* Local Certificates and associated AR Names */
  S_CERT_CTRL *sslLocalCertList;

  /* Acceptable CA Certificates */
  S_CERT_CTRL *sslTrustedCaCertList;
  
  /****** SSL Configuration ******/
  /* Local Certificate to be used */
  S_CERT_CTRL *sslLocalCertCtrl;

  /* Listen Port Numbers */
  ST_INT numSslListenPorts;
  ST_UINT16 sslListenPorts[S_SSL_MAX_LISTEN_PORTS];

  /* Allowed Ciphers, ordered by preference */
  ST_INT numAllowedCipherSuites;
  ST_INT allowedCipherSuites[S_MAX_ALLOWED_CIPHER_SUITES];

  /* Flags */
  ST_BOOLEAN certAuthCalling;
  ST_BOOLEAN certAuthCalled;
  ST_BOOLEAN encryptReqCalling;
  ST_BOOLEAN encryptReqCalled;

  /* Rekey Control */
  ST_LONG  maxTransactionsPerKey;
  time_t   maxTimePerKey;
  ST_INT   rekeyTimeout;			/* In seconds */

  /* CRL Control */
  ST_INT crlCheckTime;				/* In minutes */
  ST_BOOLEAN crlDropExisting;
  
  /****** Application Configuation */
  ST_INT appAuthRequired;
  DIB_MATCH_CTRL dibMatch;

  /* Well Known AR Names */
  S_SEC_LOC_AR *secLocArList;
  S_SEC_REM_AR *secRemArList;

  /****** SNAP Configuation */
  /* Default SSL Calling Port Number */
  ST_UINT16 defCallingSslPort;

  /* Misc */
  ST_UINT maxCalling;
  ST_UINT maxCalled;
  ST_INT cpuAffinity;

  /* Calling connection timeout, used by SNAP. Default 10000ms		*/
  ST_INT callingConnectTimeout;	/* In milliseconds */

  /****** IPC: SNAP/Stack Ports & IP Addresses */
  ST_CHAR *stackIPAddress;
  ST_UINT16 stackListenPort;

  ST_CHAR  *snapIPAddress;
  ST_UINT16 snapListenPort;
  ST_UINT16 snapControlListenPort;
  ST_UINT16 snapMonitorListenPort;

  /* SNAP/STACK Connect-to-Ctrl timeout, bidirectional. Default 500ms 	*/
  ST_INT snapStackCtrlTimeout;	/* In milliseconds */

  /****** Security Logging ******/
  ST_INT   secEventLogTimeStampMode;
  ST_INT   secEventLogFileSize;
  ST_CHAR *secEventLogFile;
  ST_INT   diagLogTimeStampMode;
  ST_INT   diagLogFileSize;
  ST_CHAR *diagLogFileName;
  ST_UINT  secLogMasks;
  } S_SEC_CONFIG;


/************************************************************************/
/************************************************************************/

#define S_SEC_ENCRYPT_NONE	0
#define S_SEC_ENCRYPT_SSL	1
typedef struct
  {
  ST_INT   encryptMode;
  union
    {
    struct 
      {
      ST_UINT16    port;
      ST_BOOLEAN   sslCertMatched;    /* The Subject-to-CertId succeded */
      S_CERT_CTRL *sslCert;	      /* The matched SSL cert ctrl	*/	
      ST_INT       cipherSuite;	      /* Cipher suite in use		*/
      } ssl;
    } u;
  } S_SEC_ENCRYPT_CTRL;

/* Struct passed back and forth to SUIC */
typedef struct
  {
  ACSE_AUTH_INFO *authInfo;
  ACSE_AUTH_INFO *partAuthInfo;	 
  S_SEC_ENCRYPT_CTRL *encryptCtrl;
  } S_SEC_SPARAMS;

/************************************************************************/

/* Application Level Authentication Check Result */
typedef struct
  {
/* Encryption in use */
  S_SEC_ENCRYPT_CTRL encryptInfo;

/* Authentication in use */
  ST_INT authPres;
  ST_INT mechType;
  union
    {
    struct
      {
      ST_BOOLEAN   timeSealOk;          /* Timeseal not reused, in window */
      ST_BOOLEAN   maceCertTimeValid;   /* Certificate validity times OK  */
      ST_BOOLEAN   maceCertIssuerOk;    /* The issuer is in the OK list   */
      ST_BOOLEAN   maceCertMatched;     /* The Subject-to-CertId succeded */
      S_CERT_CTRL *maceCert;	        /* The matched MACE cert ctrl	  */
      } certBased;
    struct
      {
      ST_INT placeHolder;
      } symmetric;
    struct
      {
      ST_INT placeHolder2;
      } passsword;
    } u; 
  } S_SEC_AUTHCHK_RSLT;

/************************************************************************/
/* Look up configured security information by AR Name */
ST_RET sSecRemArNameToArSec (ST_CHAR *arName, S_SEC_REM_AR **arSecOut);
ST_RET sSecLocArNameToArSec (ST_CHAR *arName, S_SEC_LOC_AR **arSecOut);

/************************************************************************/
/* These functions can be used to select and examine SSL level info	*/
/* for the selected connection						*/
#if defined(MMS_LITE) && !defined(MAP30_ACSE)
/* ssecusr.c functions */
struct mvl_net_info;					/* forward reference	*/
ST_RET sSecAssocIndChk (struct mvl_net_info *cc, DIB_MATCH_CTRL *matchCtrl, 
			S_SEC_REM_AR **arSecOut, S_SEC_AUTHCHK_RSLT *srcChkDest);
ST_RET sSecAssocConfChkEx (struct mvl_net_info *cc, DIB_MATCH_CTRL *matchCtrl,
                           S_SEC_REM_AR *remArSec, S_SEC_AUTHCHK_RSLT *srcChkDest);
ST_RET sSecAuthChk (struct mvl_net_info *cc, S_SEC_AUTHCHK_RSLT *srcChkDest);
ST_RET sSecGetSecParam (struct mvl_net_info *cc, S_SEC_SPARAMS *secParams);
ST_RET sSecFreeSecParam (ACSE_AUTH_INFO *authInfo);
ST_RET sSecFreePartSecParam (struct mvl_net_info *cc);

/* For backward compatability */
#define sSecAssocConfChk(cc,remArSec,secChkDest)   sSecAssocConfChkEx(cc,NULL,remArSec,secChkDest)
#else
/* ssecusr.c functions */
ST_RET sSecAssocIndChk (ST_INT chan, DIB_MATCH_CTRL *matchCtrl, 
			S_SEC_REM_AR **arSecOut, S_SEC_AUTHCHK_RSLT *srcChkDest);
ST_RET sSecAssocConfChkEx (ST_INT chan, DIB_MATCH_CTRL *matchCtrl,
			   S_SEC_REM_AR *remArSec, S_SEC_AUTHCHK_RSLT *srcChkDest);
ST_INT sSecAuthChk (ST_INT chan, S_SEC_AUTHCHK_RSLT *srcChkDest);
ST_RET sSecSetSecParam (ST_INT chan, S_SEC_SPARAMS *secParams);
ST_RET sSecGetSecParam (ST_INT chan, S_SEC_SPARAMS *secParams);

/* For backward compatability */
#define sSecAssocConfChk(chan,remArSec,secChkDest) sSecAssocConfChkEx(chan,NULL,remArSec,secChkDest)
#endif



/************************************************************************/
/************************************************************************/
/************************************************************************/
/* Initialize/Terminate 						*/

ST_RET sSecUsrStart (S_SEC_CONFIG **secCfgOut);
ST_RET sSecUsrEnd (ST_VOID);
ST_RET sSecStart (S_SEC_CONFIG **secCfg);
ST_RET sSecEnd (ST_VOID);

/* Configuration */
/* Used by configuration app to get SEC_MAN config information */
ST_CHAR *secManGetXmlCfg (ST_VOID);
ST_RET secManSetXmlCfg (ST_CHAR *pw, ST_CHAR *xmlCfg);
ST_RET secManExportLocalCerts (ST_CHAR *pw, ST_INT *destFile);

/* Used by app to reload security components */
ST_RET sSecUpdate(S_SEC_CONFIG *currCfg, S_SEC_CONFIG *newCfg);

/************************************************************************/
/* MACE Authentication 							*/

/* Create/Free MACE Authentication Information for a local CertId	*/
ST_RET sSecMaceAuthInfoCreate (S_CERT_ID *certId, ACSE_AUTH_INFO *authInfo);

ST_VOID sSecMaceAuthInfoFree (ACSE_AUTH_INFO *auth_info);

/* Decode MACE Authentication Information */
ST_RET sSecMaceAuthInfoDec (ACSE_AUTH_INFO *authInfo, 
			    S_MACE_INFO **maceInfoOut, 
			    S_CERT_INFO **certInfoOut);
ST_VOID sSecFreeCertInfo (S_CERT_INFO *certInfo);

/************************************************************************/
/************************************************************************/
/* Finding things in the Security Configuration				*/

/**** Find configured local CertCtrl for given certName ****/
ST_RET sSecCertNameToLocCertCtrl (ST_CHAR *certName, S_CERT_CTRL **certCtrlOut);

/**** Find configured remote CertCtrl for given certName ****/
ST_RET sSecCertNameToRemCertCtrl (ST_CHAR *certName, S_CERT_CTRL **certCtrlOut);

/**** Find configured remote CertCtrl for given CertId ****/
ST_RET sSecCertIdToRemCertCtrl (S_CERT_ID *certId, S_CERT_CTRL **certCtrlOut);

/**** Find configured remote CertCtrl for given cfgId ****/
ST_RET sSecCertCfgIdToRemCertCtrl (ST_INT cfgId, S_CERT_CTRL **CertCtrlOut);

/************************************************************************/
/************************************************************************/
/************************************************************************/
/**** Certificate Blob Handling ****/

/* Retrieve local Certificate Blob from Certifcate Store */
ST_RET sSecGetLocalCert (S_CERT_ID *certId, S_CERT_BLOB *certDataOut);

/* Decoding a Certificate blob */
ST_RET sSecCertDec (S_CERT_BLOB *certBlob, S_CERT_INFO **certInfoOut);

/************************************************************************/
/**** Signed Time Handling ****/

/* Verify a Signed Time	signature				*/
ST_RET sSecSignedTimeVerify (S_CERT_INFO *remCert, S_SIGNED_TIME *signedTime, ST_UCHAR *clearTime);

/* Sign a time_t 						*/
ST_RET sSecSignTimeT (S_CERT_ID *localCert, S_SIGNED_TIME *signedTime, time_t timeToSign);

/************************************************************************/
/**** MACE ASN.1 Encode/Decode ****/

/* Encode MACE ACSE Authentication */
ST_RET sSecMaceAsn1Enc (S_MACE_INFO *maceInfo, 
                        ST_CHAR *asn1Buf, ST_INT asn1BufLen,
                        ST_CHAR **maceAsn1Out, ST_INT *maceAsn1LenOut);

/* Decode Certificate based ACSE Authentication */
ST_RET sSecMaceAsn1Dec (ST_CHAR *maceAsn1, ST_INT maceAsn1Len, 
					    S_MACE_INFO **maceInfoOut);

/************************************************************************/
/**** Remote Certificate Validity Checking ****/

/* Make sure the certificate issuer is OK */
ST_RET sSecChkIssuer (S_CERT_INFO *certInfo);

/* Make sure the certificate validity times are OK */
ST_RET sSecChkValidityTimes (S_CERT_INFO *certInfo);

/* Validate a MACE time seal */
ST_RET sSecChkTimeSeal (S_CERT_INFO *remCert, 
			time_t signedTimeT, 
			ST_UCHAR *clearTime,
			S_SIGNED_TIME *signedTime);


/************************************************************************/
/************************************************************************/
/************************************************************************/
/* Common functions declarations					*/

/**** Compare remote cert issuer names with ones that we trust ****/
ST_BOOLEAN sSecCmpIssuer (S_CERT_ID *remCert, S_CERT_ID *trustedCert);
/**** Compare two CertIds ****/
ST_BOOLEAN sSecCmpCertId (S_CERT_ID *certId1, S_CERT_ID *certId2);

/* Export a certificate to XML */
#if !defined(_WIN32)
ST_INT ssleCertFileToXml (ST_CHAR *fileName, ST_CHAR *buf, ST_INT bufLen, ST_CHAR *pass);
#endif

/* Export a certificate to Text */
#if !defined(_WIN32)
ST_INT ssleCertFileToText (ST_CHAR *fileName, ST_CHAR *buf, ST_INT bufLen, ST_CHAR *pass);
#endif

/************************************************************************/
/************************************************************************/
/************************************************************************/
/* secMan Declarations							*/
/************************************************************************/

/* Set log masks */
ST_UINT* secManGetDebugSel();

/* Start/Stop */
ST_RET secManStart (S_SEC_CONFIG **secCfg, ST_VOID *secLog);
ST_RET secManEnd (ST_VOID);

/* Start the SSL Engine in ssec.lib (genssl.c) */
ST_RET startSSLEngine(S_SEC_CONFIG *sSecCfg, ST_VOID *secLog);
/* Stop the SSL Engine in ssec.lib (genssl.c) */
ST_RET stopSSLEngine();
/* Called by SNAP to reload the security configuration (genssl.c) */
ST_RET sslUpdate();

/* Used by SNAP and user apps to get the configuration. 
 * The release function MUST be called when the app is done using the 
 * configuration.
 */
ST_RET secManAccessCfg (S_SEC_CONFIG **secCfgOut);
ST_RET secManReleaseCfg (ST_VOID);

/* Used by the stack to get the configuration */
ST_RET secManAccessCfgByStack (S_SEC_CONFIG **secCfgOut);

/* Dynamic Configuration functions */
ST_BOOLEAN secManChkNewCfgAvail();
ST_RET secManLoadCfg(S_SEC_CONFIG *secCfgOut);
ST_RET secManUpdateCfg(S_SEC_CONFIG *currCfg, S_SEC_CONFIG *newCfg);
ST_RET secManFreeCfg(S_SEC_CONFIG *secCfg);

#if !defined(MMS_LITE) || defined(MAP30_ACSE)
#if defined (_WIN32)
/* Called by app or SecCfg to signal change in configuration file */
__declspec(dllimport) ST_VOID WINAPI secManCfgChange(ST_VOID);
#endif
#else  /* MMS_LITE */
ST_VOID secManCfgChange(ST_VOID);
#endif /* MMS_LITE */

#if !defined(MMS_LITE) || defined(MAP30_ACSE)
/* Software Lock access */
ST_RET secManLckStart();
ST_VOID secManLckEnd();
ST_RET secManLckCheck();
#else
/* MMS_LITE */
extern ST_CHAR *secManCfgXmlFile;
#endif

#if !defined(_WIN32)
/* If needed these paths can be changed by app before sSecStart() is called	*/
extern ST_CHAR LocalCertStorePath[256];		/* defaults to CERT_STORE_LOCAL	*/
extern ST_CHAR    CACertStorePath[256];		/* defaults to CERT_STORE_CA	*/
#endif /* !defined(_WIN32) */

/* Logging */
/* destLog defines */
#define S_SEC_LOGTYPE_NONE		0
#define S_SEC_LOGTYPE_DIAG		1
#define S_SEC_LOGTYPE_SECURITY		2

/* eventType defines */
#define S_SEC_EVENT_NO_CIPHERS		1
#define S_SEC_EVENT_UNKNOWN_CA		2
#define S_SEC_EVENT_UNKNOWN_REMOTE	3
#define S_SEC_EVENT_SSL_FAILURE		4
#define S_SEC_EVENT_REKEY_FAILURE	5

typedef struct
  {
  /* Note: adding/removing fields to/from this struct will make older	*/
  /* !!!   applications incompatible with new security DLLs.		*/
  ST_INT destLog;	 	/* Select Diagnoistic or Security log	*/

  /* This section needs work */
  ST_BOOLEAN logSystemEvent;	/* Log to System event system		*/
  ST_INT eventType;	
  ST_INT8 numArgs;
  ST_CHAR *eventArgs[32];

  ST_BOOLEAN logToSlog;		/* Log to SLOG file 			*/
  ST_INT logType; 		/* Standard SLOG information		*/
  ST_CHAR *SD_CONST logTypeStr; 
  ST_CHAR *SD_CONST sourceFile; 
  ST_INT lineNum;
  ST_INT bufLen; 
  ST_CHAR *buf;
  } S_SEC_EVENT;

/* Logging to Event Viewer via secman.dll */
ST_VOID secManEventLog (S_SEC_EVENT *secEvent, S_CERT_INFO *cert);

/**** Output the serial number as a string ****/
ST_VOID secManPrintSrlNum (S_CERT_ID *certId, ST_CHAR *outBuf);

/* Log configuration to diagnostic log */
ST_VOID secManLogCfg ();

/* Clone the log file */
ST_VOID secManCloneLog (ST_INT logType);

/************************************************************************/
/************************************************************************/
/* Log Macros								*/

/* Log type strings */
extern SD_CONST ST_CHAR *SD_CONST _sec_err_logstr;
extern SD_CONST ST_CHAR *SD_CONST _sec_nerr_logstr;
extern SD_CONST ST_CHAR *SD_CONST _sec_flow_logstr;
extern SD_CONST ST_CHAR *SD_CONST _sec_data_logstr;
extern SD_CONST ST_CHAR *SD_CONST _sec_debug_logstr;

#define SECLOG_ERR0(a) \
	SLOG_0 (sec_debug_sel & SEC_LOG_ERR, _sec_err_logstr, a)
#define SECLOG_ERR1(a,b) \
	SLOG_1 (sec_debug_sel & SEC_LOG_ERR, _sec_err_logstr, a,b)
#define SECLOG_ERR2(a,b,c) \
	SLOG_2 (sec_debug_sel & SEC_LOG_ERR, _sec_err_logstr, a,b,c)
#define SECLOG_ERR3(a,b,c,d) \
	SLOG_3 (sec_debug_sel & SEC_LOG_ERR, _sec_err_logstr, a,b,c,d)

#define SECLOG_CERR0(a) \
	SLOGC_0 (sec_debug_sel & SEC_LOG_ERR,a)
#define SECLOG_CERR1(a,b) \
	SLOGC_1 (sec_debug_sel & SEC_LOG_ERR,a,b)
#define SECLOG_CERR2(a,b,c) \
	SLOGC_2 (sec_debug_sel & SEC_LOG_ERR,a,b,c)

#define SECLOG_NERR0(a) \
	SLOG_0 (sec_debug_sel & SEC_LOG_NERR, _sec_nerr_logstr, a)
#define SECLOG_NERR1(a,b) \
	SLOG_1 (sec_debug_sel & SEC_LOG_NERR, _sec_nerr_logstr, a,b)
#define SECLOG_NERR2(a,b,c) \
	SLOG_2 (sec_debug_sel & SEC_LOG_NERR, _sec_nerr_logstr, a,b,c)
#define SECLOG_NERR3(a,b,c,d) \
	SLOG_3 (sec_debug_sel & SEC_LOG_NERR, _sec_nerr_logstr, a,b,c,d)

#define SECLOG_FLOW0(a) \
	SLOG_0 (sec_debug_sel & SEC_LOG_FLOW, _sec_flow_logstr, a)
#define SECLOG_FLOW1(a,b) \
	SLOG_1 (sec_debug_sel & SEC_LOG_FLOW, _sec_flow_logstr, a,b)
#define SECLOG_FLOW2(a,b,c) \
	SLOG_2 (sec_debug_sel & SEC_LOG_FLOW, _sec_flow_logstr, a,b,c)
#define SECLOG_FLOW3(a,b,c,d) \
	SLOG_3 (sec_debug_sel & SEC_LOG_FLOW, _sec_flow_logstr, a,b,c,d)

#define SECLOG_CFLOW0(a) \
	SLOGC_0 (sec_debug_sel & SEC_LOG_FLOW,a)

/************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* S_SEC_INCLUDED */
/************************************************************************/

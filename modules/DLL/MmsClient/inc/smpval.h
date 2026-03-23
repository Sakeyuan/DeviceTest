/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	2006-2006, All Rights Reserved.					*/
/*									*/
/*		    PROPRIETARY AND CONFIDENTIAL			*/
/*									*/
/* MODULE NAME : smpval.h 						*/
/* PRODUCT(S)  : 	 						*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*	Structures, functions for sending/receiving IEC 61850 Sampled	*/
/*	Value messages (according to IEC 61850-9-2).			*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 08/09/06  JRB     02    Fix svID len (Vstring65).			*/
/*			   Change DatSet to Vstring129 (ObjectReference)*/
/* 03/17/05  JRB     01    Created					*/
/************************************************************************/
#ifndef SMPVAL_INCLUDED
#define SMPVAL_INCLUDED

#include "asn1r.h"			/* need MMS_UTC_TIME	*/
#include "ethertyp.h"			/* need ETYPE_INFO	*/

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_SMPVAL_SVID_LEN	65	/* 61850 MsvID, UsvID len	*/
#define MAX_SMPVAL_OBJREF_LEN	129	/* 61850 ObjectReference len	*/
#define MAX_SMPVAL_SECURITY_LEN	20	/* max len of security info	*/

/* Bit numbers in OptFlds bitstring (configured by SmvOpts in SCL file)	*/
#define SVOPT_BITNUM_SMPRATE	0
#define SVOPT_BITNUM_REFRTM	1
#define SVOPT_BITNUM_SMPSYNCH	2

/************************************************************************/
/* STRUCTURE DEFINITIONS						*/
/************************************************************************/
typedef struct
  {
  ST_UINT8 *SamplePtr;		/* pointer to "Sample" data		*/
  ST_INT SampleLen;		/* length of "Sample" data in bytes	*/
  ST_CHAR svID [MAX_SMPVAL_SVID_LEN+1];	/* MsvID or UsvID - Vstring65	*/
  ST_BOOLEAN DatSetPres;	/* is "DatSet" present in ASDU?	*/
  ST_CHAR DatSet [MAX_SMPVAL_OBJREF_LEN+1];	/* Vstring129 (ObjectReference)*/
						/* (Optional)		 */
  ST_UINT16 SmpCnt;
  ST_UINT32 ConfRev;
  ST_BOOLEAN SmpSynch;
  ST_BOOLEAN RefrTmPres;	/* is "RefrTm" present in ASDU?	*/
  MMS_UTC_TIME RefrTm;		/* Optional			*/
  ST_BOOLEAN SmpRatePres;	/* is "SmpRate" present in ASDU?	*/
  ST_UINT16 SmpRate;		/* Optional			*/
  } SMPVAL_ASDU;

typedef struct
  {
  ST_UINT16 numASDU;	/* Num of ASDU concatenated into one APDU	*/
  SMPVAL_ASDU *asduArray;	/* array of "numASDU" structs		*/
				/* allocated by smpval_msg_create OR	*/
				/* allocated during decode		*/
  ST_UCHAR securityBuf [MAX_SMPVAL_SECURITY_LEN];	/* security info*/
  ST_UINT securityLen;		/* len of security info			*/
  }SMPVAL_MSG;


/************************************************************************/
/* Functions for sending SMPVAL messages.				*/
/************************************************************************/
SMPVAL_MSG *smpval_msg_create (
	ST_UINT numASDU);	/* Num of ASDU concatenated into one APDU*/

ST_VOID smpval_msg_destroy (SMPVAL_MSG *smpvalMsg);

/* Updates data stored for one ASDU to be sent in a SMPVAL message	*/
ST_RET smpval_asdu_data_update (
	SMPVAL_MSG *smpvalMsg,	/* SMPVAL msg info structure		*/
	ST_INT asduIdx,		/* index into array of ASDU for this SMPVAL msg*/
	ST_UINT8 *SamplePtr,	/* pointer to data			*/
	ST_INT SampleLen,	/* length of data in bytes		*/
	ST_CHAR *svID,
	ST_INT SmpCnt,
	ST_BOOLEAN DatSetPres,	/* SD_TRUE if optional DatSet should be sent*/
	ST_CHAR *DatSet,	/* Optional (chk DatSetPres arg)	*/
	ST_UINT32 ConfRev,
	ST_BOOLEAN SmpSynch,
	ST_BOOLEAN RefrTmPres,	/* SD_TRUE if optional RefrTm should be sent*/
	MMS_UTC_TIME *RefrTm,	/* Optional (chk_RefrTmPres arg)	*/
	ST_BOOLEAN SmpRatePres,	/* SD_TRUE if optional SmpRate should be sent*/
	ST_UINT16 SmpRate);	/* Optional (chk SmpRatePres arg)	*/

/* Encodes complete SMPVAL message (APDU plus Ethertype header).	  	*/
/* RETURNS: ptr to start of encoded message (or NULL on error)		*/
ST_UCHAR *smpval_msg_encode (
	SMPVAL_MSG *smpvalMsg,	/* SMPVAL msg info structure		*/
	ETYPE_INFO *etypeInfo,	/* Ethertype info	*/
	ST_UCHAR *asn1DataBuf,	/* buffer to encode in	*/
	ST_INT asn1DataBufLen,	/* len of buffer	*/
	ST_INT *asn1DataLenOut);/* ptr to len encoded   */
ST_RET smpval_msg_send (
	SMPVAL_MSG *smpvalMsg,	/* SMPVAL msg info structure		*/
	ETYPE_INFO *etypeInfo,	/* Ethertype info	*/
	ST_UCHAR *dstMac);	/* Destination (Multicast) MAC address	*/

/************************************************************************/
/* Functions for receiving SMPVAL messages.				*/
/************************************************************************/
/* Decode SMPVAL message and fill in SMPVAL_MSG struct.*/
SMPVAL_MSG *smpval_msg_decode (
	SN_UNITDATA *sn_req,	/* message to decode			*/
	ETYPE_INFO *etypeInfo);	/* where to store decoded Ethertype info*/

/* Must be called to free structure returned from smpval_msg_decode.	*/
ST_VOID smpval_msg_free (SMPVAL_MSG *smpvalMsg);

/************************************************************************/
/* Utility functions							*/
/************************************************************************/
/* Copies data from source to destination but reverses the order of the	*/
/* bytes (i.e. converts Big-Endian to Little-Endian or vice versa).	*/
ST_VOID reverse_bytes (
	ST_UINT8 *dst,		/* ptr to destination buffer	*/
	ST_UINT8 *src,		/* ptr to source buffer		*/
	ST_INT numbytes);	/* number of bytes to copy	*/

#ifdef __cplusplus
}
#endif
#endif 		/* included	*/

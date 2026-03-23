#ifndef _LLCIO_H
#define _LLCIO_H

/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*		1994, All Rights Reserved 				*/
/*									*/
/* MODULE NAME : llcio.h						*/
/* PRODUCT(S)  : osillc.sys 						*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 05/21/98  IKE    03     Converted to 7.0 Data types, removed 	*/
/*			   underscores so it can be compiled		*/
/* 11/02/95  DSF    02     Enhanced to retrieve stats information	*/
/* 12/08/94  DSF    01     Added SET_OFFSET				*/
/* 03/10/94  DSF    	   Initial Release				*/
/************************************************************************/

/*
** User Functions
*/

int LlcOpen (char *Name);
int LlcClose (int fd);
int LlcWrite (int fd, char *buffer, int size);
int LlcRead (int fd, char *buffer, int size);
int LlcIoctl (int fd, void *pArg, int size);




/*
**	IOCTL Management
*/

/*
** LLC Driver IOCTL requests
*/


#define LLC_ADD_MULTI				1
#define LLC_DEL_MULTI				2
#define LLC_GET_HW_ADDR				3
#define LLC_SET_FRAME_FILTER			4
#define LLC_BIND_LSAP				5
#define LLC_UNBIND_LSAP				6
#define LLC_TRACE_ON				7
#define LLC_TRACE_OFF				8
#define LLC_DEBUG_ON				9
#define LLC_DEBUG_OFF				10
#define LLC_GET_PROTO_STATS			11
#define LLC_GET_MAC_STATS			12
#define LLC_ARM_SIGNAL				13
#define LLC_ARM_POST				15
#define LLC_GET_EMB_PHYS_ADDR			16
#define LLC_SET_WRITE_CONFIRM_FLAG		17
#define LLC_GET_DEBUG 				18
#define LLC_POST_BUFS				19
#define LLC_SET_OFFSET				20
#define LLC_GET_MAC_CHARS			21
#define LLC_CLEAR_MAC_STATS			22
#define LLC_CLEAR_PROTO_STATS			23


/*
** LLC Driver IOCTL Errors
*/

#define LLCERR_NO_ERROR			0
#define LLCERR_LSAP_BOUND		1
#define LLCERR_LSAP_NOTBOUND		2
#define LLCERR_ILLEGAL_OPERATION	3
#define LLCERR_UNKNOWN_COMMAND		4

#define MAX_HWADDR_SIZE	12

typedef struct
  {
  int Opcode;
  int Status;
  } LLCGENERICIOCTL;


typedef struct
  {
  int Opcode;
  int Status;
  int cSize;
  char Multicast[MAX_HWADDR_SIZE];
  } LLCADDMULTI;

typedef struct
  {
  int Opcode;
  int Status;
  int cSize;
  char Multicast[MAX_HWADDR_SIZE];
  } LLCDELMULTI;

typedef struct
  {
  int Opcode;
  int Status;
  int cSize;
  char HwAddr[MAX_HWADDR_SIZE];
  } LLCGETHWADDR;

typedef struct
  {
  int Opcode;
  int Status;
  unsigned Lsap;
  } LLCBINDLSAP;

typedef struct
  {
  int Opcode;
  int Status;
  } LLCUNBINDLSAP;

typedef struct
  {
  int Opcode;
  int Status;
  long EmbPhysAddr;
  long EmbSize;
  } LLCGETEMBPHYSADDR;

typedef struct
  {
  int Opcode;
  int Status;
  char far *pfWriteConfirm;
  } LLCSETWRITECONFIRMFLAG;

typedef struct
  {
  int Opcode;
  int Status;
  int VxDID;
  } LLCARMPOST;

typedef struct
  {
  int Opcode;
  int Status;
  long offset;
  } LLCSETOFFSET;


typedef struct tagUSERBUFDESC
  {
  struct tagUSERBUFDESC far *Next;
  char far *pBuf;
  int cBufSize;
  int cDataSize;
  } USERBUFDESC;

typedef struct
  {
  int Opcode;
  int Status;
  USERBUFDESC far *pBufDesc;
  } LLCPOSTBUFS;

typedef struct
  {
  int Opcode;
  int Status;
  int MessageNum;
  int Parm1;
  int Parm2;
  int Parm3;
  } LLCGETDEBUG;


/*
** NDIS Protocol Driver Stats
*/

typedef struct 
  {
  long nFramesReceived;
  long nReceiveLookaheadReceived;
  long nReceiveChainReceived;
  long nFramesDiscardedNotRecognized;
  long nFramesDiscardedOutOfResources;
  long nTransferDataFailed;
  long nTransmitChainIssued;
  long nTransmitChainFailed;
  long nFramesDelivered;			/* DOS only */
  } LLCPROTOSTATS;

typedef struct
  {
  int Opcode;
  int Status;
  LLCPROTOSTATS ProtoStats;
  } LLCGETPROTOSTATS;

typedef struct
  {
  int Opcode;
  int Status;
  } LLCCLEARPROTOSTATS;

/*
** NDIS MAC Driver Characteristics
*/

typedef struct 			/* structure for MAC service specific info */
  {
  int	cSize;		/* length of the characteristic table	*/
  char		TypeName[16];	/* name of the MAC type (eg. 802.3...)	*/
  int		cStationAddr;	/* length of station address (MAC)	*/
  char		PermMACAddr[16];	/* hardware default MAC address		*/
  char		CurrMACAddr[16];	/* current MAC address in use		*/
  long         	FunctionAddr;	/* current functional address of adapter */
  long 		reserved; 	/* pointer to multicast table 		*/
  long		LinkSpeed;	/* link speed bits/sec			*/
  long		fMAC;		/* flags of capabilities			*/
  int		MaxFrameSize;	/* maximum MAC frame which can be sent	*/
  long		TotalTxSpace;	/* total transmit buffer space		*/
  int		cTxBlockSize;	/* size of allocated transmission blocks */
  long		TotalRxSpace;	/*total reception buffer space		*/
  int		cRxBlockSize;	/*reception buffer alloc blk size	*/
  char		VendorID[3];	/*vendor IEEE ID			*/
  char		VendorAdapterDesc; /*vendor adapter description		*/
  long		reserved2;	/*pointer to vendor serial number	*/
  int		IRQLevel;	/*interrupt level			*/
  int		TransmitQueueDepth;
  int		nMaxDataBlocks;
  } LLCMACCHARS;	

typedef struct
  {
  int Opcode;
  int Status;
  LLCMACCHARS MacChars;
  } LLCGETMACCHARS;

typedef struct
  {
  int		cSize;		   		/*size of table					*/
  long		LastDiagTime;			/*seconds since 1-1-1970 of diags		*/
  long		MACStatus;			/*mac status, this is a bit mask		*/
  						/* Bits 0-2:	0 - Hardware Not Installed	*/
						/*		1 - Hardware Failed Pwrup Diags */
						/*		2 - Hardware Failed CNFG Prob	*/
						/*		3 - Hardware Faulted		*/
						/*		4 - Hardware Marginally Operat	*/
						/*		7 - Fully Operational		*/
						/* Bit 3:	MAC BOUND			*/
						/* Bit 4:	MAC OPEN			*/
						/* Bit 5:	DIAG_IN_PROGRESS		*/
  int		CurrPacketFilter;		/* Bit 1:	Directed and Multicast Group	*/
  						/* Bit 2:	Broadcast			*/
						/* Bit 3:	Promiscuous			*/
						/* Bit 4:	All Source Routing		*/
  long 		reserved;			/*pointer to media specific stats		*/
  long	   	LastClearTime;			/*seconds since 1-1-1970			*/
  long		nOkFramesReceived;		/*total frames received ok			*/
  long		nCrcErrorFrames;		/*total frames received with crc errors		*/
  long		nBytesReceived;			/*total number of bytes recieved		*/
  long		nFramesDiscarded;		/*total number of frames discarded		*/
  long		nMulticastFramesReceived;	/*total number of multicast frames rxd OK	*/
  long		nBroadcastFramesReceived;	/*total number of broadcast frames rxd OK	*/
  long		reserved1;
  long		reserved2;
  long		reserved3;
  long		reserved4;
  long		reserved5;
  long		nFramesDiscardedHwError;	/*total number of frames discarded due to HW err*/
  long		nFramesTransmittedOk;		/*total number of frames transmitted OK		*/
  long		nBytesTransimittedOk;		/*total number of bytes transmitted OK		*/
  long		nMulticastFramesTransmitted;	/*total number of multicast transmitted		*/
  long		nBroadcastFramesTransmitted;	/*total broadcast frame transmitted		*/
  long		reserved6;
  long		reserved7;
  long		nFramesNotTransmittedTimeout;	/*total frames not transmitted due to timeout	*/
  long		nFramesNotTransmittedHwError;	/*total frames not transmitted due to HW ERR	*/
  } LLCMACSTATS;

typedef struct
  {
  int Opcode;
  int Status;
  LLCMACSTATS MacStats;
  } LLCGETMACSTATS;

typedef struct
  {
  int Opcode;
  int Status;
  } LLCCLEARMACSTATS;

typedef union
  {
  LLCADDMULTI 			AddMulti;
  LLCDELMULTI 			DelMulti;
  LLCGETHWADDR 			GetHwAddr;
  LLCBINDLSAP 			BindLsap;
  LLCUNBINDLSAP  		UnBindLsap;
  LLCGETEMBPHYSADDR		GetEmbPhysAddr;
  LLCSETWRITECONFIRMFLAG	SetWriteConfirmFlag;
  LLCPOSTBUFS 			PostBufs;
  LLCARMPOST 			ArmPost;
  LLCGETDEBUG 			GetDebug;
  LLCSETOFFSET 			SetOffset;
  LLCGETMACCHARS		GetMacChars;
  LLCGETMACSTATS		GetMacStats;
  LLCCLEARMACSTATS		ClearMacStats;
  LLCGETPROTOSTATS		GetProtoStats;
  LLCCLEARPROTOSTATS		ClearProtoStats;
  } LLCIOCTL;



/*
** Function prototypes
*/

int llc_getstats (LLCMACCHARS *MacChars,
		  LLCMACSTATS *MacStats,
		  LLCPROTOSTATS *ProtoStats);
void llc_clearstats ();


#endif

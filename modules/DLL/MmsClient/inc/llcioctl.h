/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*		1996, All Rights Reserved				*/
/*									*/
/* MODULE NAME : llcioctl.c						*/
/* PRODUCT(S)  : OSI LLC NDIS 3.1 VxD					*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 06/16/97  DSF    05     Added stats					*/
/* 09/10/96  DSF    04     Added Length field to SET_MULTI		*/
/* 09/05/96  DSF    03     Added SET_FILTER				*/
/* 08/14/96  DSF    02     Added Transmit Completion object		*/
/* 04/01/96  DSF    01     Initial Release				*/
/*									*/
/************************************************************************/

#define IOCTL_BASE			0x8100
#define	IOCTL_GET_PHYS_ADDR		(IOCTL_BASE + 1)
#define	IOCTL_SET_MULTI			(IOCTL_BASE + 2)
#define	IOCTL_ARM_EVENT			(IOCTL_BASE + 3)
#define	IOCTL_SEND			(IOCTL_BASE + 4)
#define	IOCTL_RECEIVE			(IOCTL_BASE + 5)
#define	IOCTL_ARM_COMPLETE		(IOCTL_BASE + 6)
#define	IOCTL_SET_FILTER		(IOCTL_BASE + 7)
#define	IOCTL_GET_STATS			(IOCTL_BASE + 8)


#define PHYS_ADDR_LENGTH		6
typedef struct _GET_PHYS_ADDR
  {
  UINT Status;
  char PhysAddr[PHYS_ADDR_LENGTH];
  } GET_PHYS_ADDR;


typedef struct _SET_MULTI
  {
  UINT Status;
  UINT Length;
  char MultiAddr[2 * PHYS_ADDR_LENGTH];
  } SET_MULTI;

typedef struct _SET_FILTER
  {
  UINT Status;
  } SET_FILTER;

typedef struct _ARM_EVENT
  {
  UINT Status;
  HANDLE EventHandle;
  } ARM_EVENT;

typedef struct _ARM_COMPLETE
  {
  UINT Status;
  HANDLE CompleteHandle;
  } ARM_COMPLETE;

#if !defined (GET_STATS_DEFINED)
typedef struct _MAC_STATS
  {
  ULONG HardwareStatus;
  ULONG MaxLookahead;
  ULONG MaxFrameSize;
  ULONG LinkSpeed;
  ULONG TransmitBufferSpace;
  ULONG ReceiveBufferSpace;
  ULONG TransmitBlockSize;
  ULONG ReceiveBlockSize;
  ULONG MaximumTotalSize;
  ULONG MacOptions;
  ULONG ConnectStatus;
  ULONG XmitOk;
  ULONG RcvOk;
  ULONG XmitError;
  ULONG RcvError;
  ULONG RcvNoBuffer;
  ULONG RcvCrcError;
  ULONG TransmitQueueLength;
  } MAC_STATS;

typedef struct _PROTO_STATS
  {
  ULONG XmitOk;
  ULONG RcvOk;
  ULONG XmitError;
  ULONG RcvError;
  ULONG RcvUnknown;
  ULONG XmitInd;
  ULONG RcvInd;
  ULONG AllocError;
  } PROTO_STATS;

typedef struct _USER_STATS
  {
  ULONG XmitOk;
  ULONG RcvOk;
  ULONG XmitError;
  ULONG RcvError;
  ULONG RcvUnknown;
  } USER_STATS;

typedef struct _GET_STATS
  {
  UINT Status;
  MAC_STATS mac;
  PROTO_STATS proto;
  USER_STATS user;
  } GET_STATS;

#define GET_STATS_DEFINED
#endif

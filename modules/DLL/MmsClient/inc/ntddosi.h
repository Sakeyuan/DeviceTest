/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,       */
/*		1996, All Rights Reserved                               */
/*                                                                      */
/* MODULE NAME : osillc.h                                               */
/* PRODUCT(S)  : OSI LLC NDIS 3.0 Device Driver for NT                  */
/*	                                                                */
/* MODULE DESCRIPTION :                                                 */
/*                                                                      */
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :                            */
/*                                                                      */
/* MODIFICATION LOG :                                                   */
/*  Date     Who   Rev			Comments                        */
/* --------  ---  ------   -------------------------------------------	*/
/* 05/13/98  DSF    05     Added SeqNumber field to PACKET_BLOCK	*/
/* 05/07/98  DSF    04     The size of PACKET_BLOCK is now user-settable*/
/* 06/19/97  DSF    03     Added Stats                                  */
/* 09/10/96  DSF    02     Used Length field in SET_MULTI               */
/* 05/22/96  DSF    01     Initial Release                              */
/*                                                                      */
/************************************************************************/

#ifndef __NTDDOSILLC
#define __NTDDOSILLC

#if defined (_NTDDK_)
#include <devioctl.h>
#else
#include <winioctl.h>
#endif

#pragma pack(1)

//
// standard 802.3 defines (not defined elsewhere)
//
#define ETH_LENGTH_OF_HEADER		14
#define ETH_MINIMUM_LENGTH_OF_DATA	46
#define ETH_MAXIMUM_LENGTH_OF_DATA	1500
#define ETH_LENGTH_OF_FRAME			1514


// max number of packets that will be returned at a time
#define OSILLC_MAX_RXPACKETS	10

typedef struct _NT_PACKET_DATA
{
	ULONG	Length;
	UCHAR	Data[ETH_LENGTH_OF_FRAME];
} NT_PACKET_DATA, * PNT_PACKET_DATA;

typedef struct _NT_PACKET_BLOCK
{
	ULONG	NumberOfPackets;
	ULONG	SeqNumber;
	NT_PACKET_DATA PacketData[1];
} NT_PACKET_BLOCK, * PNT_PACKET_BLOCK;


#if 0
typedef struct _NT_ARM_EVENT
{
	UINT Status;
} NT_ARM_EVENT;
#endif


typedef struct _PACKET_OID_DATA
{
    ULONG           Oid;
    ULONG           Length;
    UCHAR           Data[1];
} PACKET_OID_DATA, * PPACKET_OID_DATA;


#if !defined (GET_STATS_DEFINED)
typedef struct _GET_STATS
{
	ULONG XmitOk;
	ULONG RcvOk;
	ULONG XmitError;
	ULONG RcvError;
	ULONG RcvUnknown;
	ULONG XmitInd;
	ULONG RcvInd;
	ULONG AllocError;
} GET_STATS;

#define GET_STATS_DEFINED
#endif

// base for IOCTLs
#define FILE_DEVICE_PROTOCOL			0x8000

#define OSILLC_CONTROL_CODE(request, method) \
		CTL_CODE(FILE_DEVICE_PROTOCOL, request, method, FILE_ANY_ACCESS)

#define IOCTL_OSILLC_QUERY_OID			OSILLC_CONTROL_CODE(0, METHOD_BUFFERED)
#define IOCTL_OSILLC_SET_OID			OSILLC_CONTROL_CODE(1, METHOD_BUFFERED)
#define IOCTL_OSILLC_GET_STATS			OSILLC_CONTROL_CODE(2, METHOD_BUFFERED)
#define IOCTL_OSILLC_SET_EVENT			OSILLC_CONTROL_CODE(3, METHOD_BUFFERED)
#define IOCTL_OSILLC_CLEAR_EVENT		OSILLC_CONTROL_CODE(4, METHOD_BUFFERED)
#define IOCTL_OSILLC_GET_MACNAME		OSILLC_CONTROL_CODE(5, METHOD_BUFFERED)
#define IOCTL_OSILLC_ARM_EVENT			OSILLC_CONTROL_CODE(6, METHOD_BUFFERED)
#define IOCTL_OSILLC_RESET				OSILLC_CONTROL_CODE(7, METHOD_BUFFERED)

#define IOCTL_OSILLC_GET_PACKETS		OSILLC_CONTROL_CODE(8, METHOD_OUT_DIRECT)
#define IOCTL_OSILLC_SEND_PACKETS		OSILLC_CONTROL_CODE(9, METHOD_IN_DIRECT)

#endif

#pragma pack()

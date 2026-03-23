/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	1998-2006 All Rights Reserved					*/
/*									*/
/* MODULE NAME : event.c						*/
/* PRODUCT(S)  : MMSEASE-LITE						*/
/*									*/
/* MODULE DESCRIPTION :							*/
/*	Event handling functions.					*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*	wait_any_event ()						*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev     Comments					*/
/* --------  ---  ------   -------------------------------------------  */
/* 11/01/06  JRB    09     Go back to gs_wait_mult_event_sem for WIN32	*/
/*			   (Ethernet interface code fixed so don't	*/
/*			   need to use WaitForMultipleObjectsEx).	*/
/* 04/20/05  JRB    08     Add header files (included indirectly before).*/
/* 07/07/04  JRB    07     Del #ifdef MOSI. May need a_get_event_handles*/
/*			   added to stack lib if non-MOSI stack used.	*/
/* 10/23/03  JRB    06     Call a_get_event_handles_unix for default system.*/
/* 05/17/02  JRB    05     Put back old code for PHARLAP_ETS, PharLap	*/
/* 			   doesn't have "Wait..Ex".			*/
/* 04/10/00  JRB    04     Del "select.h". See "sysincs.h".		*/
/* 04/06/00  JRB    03     Use WaitForMultipleObjectsEx for WIN32:	*/
/*			   CRITICAL for ethernet driver interface.	*/
/* 08/05/99  JRB    02     Use a_get_ev.., gs_wait.. for WIN32.		*/
/*			   Use hTcpEvent for OS2.			*/
/* 11/10/98  JRB    01     Created					*/
/************************************************************************/
/* 更改记录：
 2007-03-20 施江涛  wait_any_event 中屏蔽对stdin的响应,否则在终端中有任何输入,程序都响应,
                        因此在终端中看到mmsserver线程一致处于ready状态。
*/


#include "glbtypes.h"
#include "sysincs.h"
#include "mmsdefs.h"
#include "glbsem.h"
#include "acse2usr.h"

#include <assert.h>

#if defined (_WIN32)
/************************************************************************/
/*                          wait_any_event				*/
/* Windows version (also works for PHARLAP_ETS).			*/
/************************************************************************/

ST_VOID wait_any_event (ST_LONG max_ms_delay)
  {
ST_EVENT_SEM *EventArray;
ST_INT NumEntries;
ST_BOOLEAN activity [4];	// 2->4, leixt 2013.3.

  EventArray = a_get_event_handles (&NumEntries);

  /* Make sure there is at least 1 event to wait on. If not, probably	*/
  /* because library not compiled with correct switches.		*/
  assert (NumEntries > 0);

  /* If this fails, size of "activity" array must be increased.		*/
  assert (NumEntries <= 4);		// 2->4, leixt 2013.3.
  gs_wait_mult_event_sem (NumEntries, EventArray, activity, max_ms_delay);

  /* Something woke us up. Don't care if it was event or timeout.	*/
  /* Just return to main loop to attempt processing.			*/
  return;
  }

#elif defined (__OS2__)

/************************************************************************/
/*                          wait_any_event				*/
/* DEBUG: not tested but should work on OS/2.				*/
/************************************************************************/

ST_VOID wait_any_event (ST_LONG max_ms_delay)
  {
#define MMS_EVENT_SEM_ID	0
static SEMRECORD sems[2];
static HMUX hMux;
APIRET apiret;
ST_ULONG post_count;
ST_ULONG semId;

  /* This function only waits on the MMS event. To wait on other events	*/
  /* also, add to the "sems" array.					*/

  if (hMux == NULL)
    {
    sems[0].hsemCur = (void *) hTcpEvent;
    sems[0].ulUser = MMS_EVENT_SEM_ID;
    apiret = DosCreateMuxWaitSem (NULL, &hMux, 1, sems, DCMW_WAIT_ANY);
    if (apiret != NO_ERROR)
      {
      printf ("\n DosCreateMuxWaitSem failed, rc = %d",apiret);
      hMux = NULL;
      }
    return;	/* Just return. New event so no one has signaled it yet.*/
    }

  /* Wait on the MMS Event Semaphore.		*/

  apiret = DosWaitMuxWaitSem (hMux, max_ms_delay, &semId);

  if (apiret == NO_ERROR)
    {
    if (semId == MMS_EVENT_SEM_ID) /* MMS event			*/
      {
      gs_reset_event_sem (hTcpEvent);	/* OS2 requires reset	*/
      }
    }
  else if (apiret != ERROR_TIMEOUT)
    {
    printf ("\n DosWaitMuxWaitSem error, apiret = %d",apiret);
    }
  }

#elif defined(MSDOS) || defined(__MSDOS__)

/************************************************************************/
/*                          wait_any_event				*/
/************************************************************************/

ST_VOID wait_any_event (ST_LONG max_ms_delay)
  {
  return;
  }
#else	/* All other systems	*/

/************************************************************************/
/*                          wait_any_event				*/
/************************************************************************/
ST_VOID wait_any_event (ST_LONG max_ms_delay)
  {
  struct timeval stTimeVal;
  fd_set readfds;
  fd_set writefds;
  fd_set exceptfds;
  int    nfds=0;
  int *fd_array;	/* ptr to array of handles on which to wait	*/
  int num_entries;	/* num of entries in fd_array.			*/
  int j;		/* loop index	*/

  FD_ZERO (&readfds);
  FD_ZERO (&writefds);
  FD_ZERO (&exceptfds);
//FD_SET (0, &readfds);		/* select on "stdin"	*/ // Del 2007-03-20 不知有何用,会导致在终端中有输入时进行处理的问题

  /* Ask ACSE for array of handles on which to wait.	*/
  fd_array = a_get_event_handles_unix (&num_entries);

  for (j = 0; j < num_entries; j++)
    {
    FD_SET (fd_array[j], &readfds);
    nfds = max (nfds,fd_array[j]);
    }
  nfds++;	/* must be 1 greater than max handle.	*/

  /* If you want to wait for other events too, add more FD_SET calls,	*/
  /* and recompute "nfds" (or just set it to FD_SETSIZE).		*/

  max_ms_delay *= 1000; /*** Convert to micro seconds ***/
  stTimeVal.tv_sec  = max_ms_delay / 1000000;
  stTimeVal.tv_usec = max_ms_delay % 1000000;

  nfds = select (nfds, &readfds, &writefds, &exceptfds, &stTimeVal);
  }

#endif		/* All other systems		*/


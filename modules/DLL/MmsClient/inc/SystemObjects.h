/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*		2001 - 2004, All Rights Reserved			*/
/*									*/
/* MODULE NAME : SystemObjects.h					*/
/* PRODUCT(S)  : 							*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/* Wrapper objects for system objects					*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 11/13/06  DSF     42    Added Initialize and TerminateTimerSupport ()*/
/* 10/26/06  DSF     41    Forward declare Lock				*/
/* 10/25/06  DSF     40    GetOwner () only supported for WIN32		*/
/* 08/14/06  DSF     39    Added Thread2				*/
/* 05/25/06  DSF     38    Fixed a one-shot timer bug in Timer::Stop ()	*/
/* 02/13/06  DSF     37    Migrate to VS.NET 2005			*/
/* 06/13/05  DSF     36    Protected access to Thread::Start and	*/
/*			   Terminate					*/
/* 06/10/05  DSF     35    Added mutex tracking				*/
/* 06/04/05  DSF     34    Protected access to Timer::Start and Stop	*/
/* 05/20/05  DSF     33    Bumped up the number of timer worker threads	*/
/* 04/01/05  DSF     32    Added Timer::SetName ()			*/
/* 03/18/05  DSF     31    Use _SASSERTE				*/
/* 02/17/05  DSF     30    Added GetOwner ()				*/
/* 01/10/05  DSF     29    Block Timer::Stop () until termination event	*/
/*			   is signalled					*/
/* 09/09/04  EJV     28    sun warning when last line doesn't have NL.	*/
/*			   sun warning when last enum is followed by ','*/
/*			   sun error if namespace{} is followed by ';'	*/
/* 07/23/04  DSF     27    Thread::Start () now waits until the thread	*/
/*			   starts running				*/
/* 07/15/04  DSF     26    Timer resolution again			*/
/* 06/30/04  DSF     25    Set timer resolution to the maximum of 100ms	*/
/*			   and timer interval divided by 4		*/
/* 06/17/04  DSF     24    Added Timer::Initialize ()			*/
/* 05/10/04  DSF     23    gs_timer_cleanup () now takes an argument	*/
/*			   Added DLL Termination methods		*/
/* 02/02/03  DSF     22    Added Thread::DestroyOnExit			*/
/* 11/19/03  DSF     21    Added Timer::Cleanup				*/
/* 10/23/03  DSF     20    Don't catch Thread or Timer exceptions	*/
/*			   Block Timer::Stop until current Run finishes	*/
/* 07/28/03  DSF     19    Make SelfTerminate public			*/
/* 06/12/03  DSF     18    Added named objects				*/
/*			   Call SelfTerminate when Thread::Run returns	*/
/* 05/20/03  DSF     17    Don't start a timer if already running	*/
/*			   Add GetInterval ()				*/
/* 05/13/03  DSF     16    Trap Run exceptions				*/
/* 03/21/03  DSF     15    Added SISCO namespace			*/
/* 11/18/02  DSF     14    Virtualized some of the methods		*/
/* 08/02/02  DSF     13	   Fixed Mutex					*/
/* 08/01/02  DSF     12    Added SetThreadName				*/
/* 07/23/02  DSF     12    Set timer resolution if necessary		*/
/* 07/19/02  DSF     11    Added Events.WaitAll and Events.size		*/
/* 06/29/02  DSF     10    Added Block method				*/
/* 06/24/02  DSF     09    Fixed a memory leak				*/
/* 06/21/02  DSF     08    Added Attach methods				*/
/* 12/04/01  DSF     07    Fixed Mutex/Lock problems			*/
/* 12/03/01  DSF     06    Allow event and mutex handles to be passed 	*/
/*			   in to Event and Mutex constructors		*/
/* 11/12/01  DSF     05    Events now holds a vector of Event pointers	*/
/* 11/12/01  DSF     04    Thread Terminate () fixes			*/
/* 11/09/01  DSF     03    Added SelfTerminate () to Thread class	*/
/* 10/31/01  EJV     02    Added ST_THREAD_CALL_CONV to entryPoint();	*/
/*			   Added return before ST_THREAD_RET_VAL.	*/
/* 08/08/01  DSF     01    Module created				*/
/************************************************************************/

#ifndef _SYSTEM_OBJECTS_H
#define _SYSTEM_OBJECTS_H

#if defined (_WIN32)
#if !defined (_CRT_SECURE_NO_DEPRECATE)
#define _CRT_SECURE_NO_DEPRECATE
#endif
#if defined (_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES)
#undef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#endif
#pragma warning(disable : 4786 4800)
#include <windows.h>
#endif

#if defined (DEBUG_NEW_MFC)
#include "glbtypes.h"
#include "sysincs.h"
#include "mem_chk.h"

#include <vector>
#include <list>
#include <string>
using namespace std;

#define new DEBUG_NEW
#undef THIS_FILE
#define THIS_FILE __FILE__

#else

#include <vector>
#include <list>
#include <string>
using namespace std;

#include "glbtypes.h"
#include "sysincs.h"
#include "mem_chk.h"

#endif

#include "slog.h"
#include "gen_list.h"
#include "glbsem.h"

#define thisFileName	__FILE__

#if defined (TRACK_MUTEX)
#if !defined (_WIN32)
#error Mutex Tracking supported for WIN32 only!
#endif
#include "CallStack.h"
using namespace SISCO::CallStack;
#endif

namespace SISCO
{

namespace SystemObjects
{

/************************************************************************/
/*			Mutex Object					*/
/************************************************************************/

class Mutex
  {
public:
  Mutex (bool create = true) : m_local (true), m_count (0), m_created (false) 
    {
    if (create)
      Create ();
    }
  Mutex (const string& name, bool create = true) : m_local (true), m_count (0), m_name (name), m_created (false)
    {
    if (create)
      Create ();
    }
  Mutex (ST_MUTEX_SEM& mutex) : m_local (false), m_count (0), m_mutex (mutex), m_created (true) {}
  
  void SetName (const string& name, bool create = true) 
    {
    m_name = name;
    if (create)
      Create ();
    }
  
  void Create ()
    {
    if (m_created)
      return;

    if (m_name.empty ())
      {      
      VERIFY (gs_mutex_create (&m_mutex) == SD_SUCCESS);
      }
    else
      {
      VERIFY (gs_named_mutex_create (&m_mutex, (ST_CHAR *) m_name.c_str ()) == SD_SUCCESS);
      }
    m_created = true;
    }
    
  void Attach (ST_MUTEX_SEM& mutex)
    {
    Release ();
    if (m_local && m_created)
      gs_mutex_destroy (&m_mutex);
    m_local = false;
    m_created = true;
    m_mutex = mutex;
    }
      
  virtual ~Mutex () 
    {
    Release ();
    if (m_local && m_created)
      gs_mutex_destroy (&m_mutex);
    }

  bool Acquire (long timeout = -1) 
    {
    _SASSERTE (m_created);
    ST_RET ret = gs_mutex_get_tm (&m_mutex, timeout);
    if (ret == SD_SUCCESS)
      {
      m_count++;
#if defined (TRACK_MUTEX)
      Stack stack;
      GetCallStack (GetCurrentThreadId (), stack);
      m_tracker.push_back (stack);
#endif
      }
    return ret == SD_SUCCESS;
    }
    
  void Release ()
    {
    if (m_count)
      {
      m_count--;
#if defined (TRACK_MUTEX)
      m_tracker.pop_back ();
#endif
      gs_mutex_free (&m_mutex);
      }
    }
    
#if defined (_WIN32)
  ST_THREAD_ID GetOwner () {return m_mutex.owner;}
#else
  ST_THREAD_ID GetOwner () {return (ST_THREAD_ID) -1;}
#endif
  
protected:
  ST_MUTEX_SEM	m_mutex;
  bool		m_created;
  
private:
  string	m_name;
  bool	       	m_local;
  int		m_count;
#if defined (TRACK_MUTEX)
  typedef list<Stack> Tracker;
  Tracker	m_tracker;
#endif
  };


/************************************************************************/
/*			NullMutex Object				*/
/* Dummy Mutex class							*/
/************************************************************************/

class NullMutex
  {
public:
  NullMutex () {Acquire ();}
  ~NullMutex () {Release ();}

  bool Acquire (long timeout = -1) {return true;}
  void Release () {}
  
private:
  NullMutex (const NullMutex&);
  NullMutex& operator= (const NullMutex&);
  };

/************************************************************************/
/*			Event Object					*/
/************************************************************************/

class Event
  {
public:  
  Event (bool manual = false, bool create = true) : m_local (true), m_manual (manual), m_created (false)
    {
    if (create)
      Create ();
    }
  Event (const string& name, bool manual = false, bool create = true) : 
  	m_local (true), m_manual (manual), m_name (name), m_created (false)
    {
    if (create)
      Create ();
    }
  Event (ST_EVENT_SEM& event) : m_local (false), m_event (event), m_manual (false), m_created (true) {}

  void SetName (const string& name, bool create = true) 
    {
    m_name = name;
    if (create)
      Create ();
    }
  
  void Create ()
    {
    if (m_created)
      return;

    if (m_name.empty ())      
      {
      VERIFY (m_event = gs_get_event_sem ((ST_BOOLEAN) m_manual));
      }
    else
      {
      VERIFY (m_event = gs_get_named_event_sem ((ST_CHAR *) m_name.c_str (), (ST_BOOLEAN) m_manual));
      }
    m_created = true;
    }
    
  Event& Clone (Event& evt)
    {
    m_manual = evt.IsManual ();
    VERIFY (m_event = gs_get_event_sem ((ST_BOOLEAN) m_manual));
    return *this;
    }
  
  void Attach (ST_EVENT_SEM& event)
    {
    if (m_local)
      gs_free_event_sem (m_event);
      
    m_local = false;
    m_event = event;
    m_created = true;
    }
    
  ~Event ()
    {
    if (m_local && m_created)
      gs_free_event_sem (m_event);
    }
    
  enum WaitReturn
    {
    waitFailed = -2,
    waitTimeout = -1,
    waitSuccess = 0
    };
    
  void Set () {gs_signal_event_sem (m_event);}
  void Reset () {gs_reset_event_sem (m_event);}
  WaitReturn Wait (long timeout = -1) 
    {
    WaitReturn waitRet;
    ST_RET ret = gs_wait_event_sem (m_event, timeout);
    switch (ret)
      {
      case SD_SUCCESS: waitRet = waitSuccess; break;
      case SD_TIMEOUT: waitRet = waitTimeout; break;
      default: waitRet = waitFailed; break;
      }
    return waitRet;
    }
  ST_EVENT_SEM GetEvent () {return m_event;}
  bool IsManual () const {return m_manual;}
  
private:
  string	m_name;
  ST_EVENT_SEM	m_event;
  bool	       	m_local;
  bool	       	m_manual;
  bool		m_created;
  };
  
/************************************************************************/
/*			Events Object					*/
/************************************************************************/

class Events
  {
public:

  void Add (Event *pEvent) {m_events.push_back (pEvent);}
  Event::WaitReturn Wait (long timeout = -1);
  Event::WaitReturn WaitAll (long timeout = -1);
  vector<Event *>::size_type size () {return m_events.size ();}
  
private:
  vector<Event *> 	m_events;
  };


/************************************************************************/
/*			Lock Object					*/
/************************************************************************/

template <typename T = Mutex>
class Lock
  {
public:
  Lock (T& t) : m_t (t), m_owned (false)
    {
    Acquire ();
    }
  ~Lock ()
    {
    Release ();
    }
    
  void Acquire () 
    {
    m_t.Acquire ();
    m_owned = true;
    }
  void Release ()
    {
    if (m_owned)
      m_t.Release ();
    }

private:
  T& 		m_t;
  bool		m_owned;

  Lock ();  
  Lock (const Lock&);
  void operator= (const Lock&);
  };

/************************************************************************/
/*			Timer Object					*/
/************************************************************************/

typedef int TimerType;
const TimerType TIMER_TYPE_ONESHOT = SD_TIMER_ONESHOT;
const TimerType TIMER_TYPE_PERIODIC = SD_TIMER_PERIODIC;

template<TimerType timerType = TIMER_TYPE_PERIODIC>
class Timer
  {
public:  
  Timer () : m_pTimer (NULL), m_interval (0), m_inProgress (false) {}
  virtual ~Timer () {Stop ();}

  void SetName (const string& name) {m_name = name;}
  string GetName () {return m_name;}
  
  bool IsRunning () {return m_pTimer != NULL;}
  
  void Pend () {m_inProgress = true;}
  void Unpend () {m_inProgress = false;}
  bool IsPend () {return m_inProgress;}
      
  void SetInterval (long interval) {m_interval = interval;}
  long GetInterval () {return m_interval;}
  virtual void Start () 
    {
    _SASSERTE (m_interval > 0);
    Lock<> guard (m_mutex);
    if (m_pTimer)
      return;
    ST_ULONG timerRes = gs_timer_get_resolution ();
    if ((m_interval < (long) timerRes) && (m_interval >= 10))
      gs_timer_set_resolution (m_interval);
    m_pTimer = gs_timer_start (timerType, m_interval, entryPoint, this);
    _SASSERTE (m_pTimer);
    m_pTimer->event = m_termEvent.GetEvent ();
    }
  virtual void Stop () 
    {
    Lock<> guard (m_mutex);
    if (m_pTimer)
      {
      while (m_inProgress)
        Block (1000);
      if (m_inProgress || timerType == TIMER_TYPE_PERIODIC)
        {
        gs_timer_end (m_pTimer);
        m_termEvent.Wait ();
        }
      }
    m_pTimer = NULL;
    }
    
  static void Initialize ()
    {
    gs_timer_init (GS_TIMER_WORKER_MIN, 128);
    }
    
  static void Cleanup ()
    {
    long timeout = -1;
#if defined (_WIN32) && defined (_DLL)
    if (IsDLLTerminating ())
      timeout = 1000;
#endif
    gs_timer_cleanup (timeout);
    }
    
protected:
  virtual void Run () = 0;
  
private:
  GS_TIMER	*m_pTimer;
  long		m_interval;
  bool		m_inProgress;
  Event		m_termEvent;
  string	m_name;
  Mutex		m_mutex;
  
  static void 	entryPoint (void *arg)
    {
    Timer *pTimer = static_cast<Timer *> (arg);
    if ((pTimer->IsRunning () == false) || pTimer->IsPend ())
      return;
      
    pTimer->Pend ();
    pTimer->Run ();
    pTimer->Unpend ();
    };
  };

inline void InitializeTimerSupport ()
  {
  Timer<>::Initialize ();
  }
inline void TerminateTimerSupport ()
  {
  Timer<>::Cleanup ();
  }
  
/************************************************************************/
/*			Thread Object					*/
/************************************************************************/

class ThreadTermCallback
  {
public:
  ThreadTermCallback () {}
  virtual ~ThreadTermCallback () {}
  
  virtual void OnTerminate () = 0;
  };

class Thread
  {
public: 
  Thread (); 
  virtual ~Thread () 
    {
    Terminate ();
    }

  void DestroyOnExit (bool destroyOnExit = true) {m_destroyOnExit = destroyOnExit;}
  bool IsDestroyOnExit () {return m_destroyOnExit;}
  
  void SetTermCallback (ThreadTermCallback *pTermCallback) {m_pTermCallback = pTermCallback;}
  ThreadTermCallback *GetTermCallback () {return m_pTermCallback;}
  
#if defined (_WIN32)
  static DWORD GetTlsIndex () {return m_tlsIndex;}
#endif
  
  virtual bool Start ();
  virtual bool Wait (long timeout = -1);

  // Must be called prior to Start ()
  void SetThreadName (const string& name) {m_name = name;}
  string GetThreadName () {return m_name;}
  // Internal function
  void InstallThreadName ();
  
  void SetStartEvent () {_SASSERTE (m_pStartEvent); m_pStartEvent->Set ();}
  Event *GetStartEvent () const {return m_pStartEvent;}

  void SetTermEvent () {_SASSERTE (m_pTermEvent); m_pTermEvent->Set ();}
  Event *GetTermEvent () const {return m_pTermEvent;}

  virtual bool SelfTerminate () {m_h = 0; return true;}
  virtual bool Terminate ();
  bool IsTerminating () {return m_terminating;}
  bool IsTerminated () {return m_terminated;}
  
  ST_THREAD_HANDLE GetHandle () {return m_h;}  
  ST_THREAD_ID GetID () {return m_id;}  
  
protected:
  virtual void Run () = 0;
  
  ST_THREAD_HANDLE	m_h;
  ST_THREAD_ID		m_id;
  Event			*m_pTermEvent;
  Event			*m_pStartEvent;
  string		m_name;
  bool			m_terminating;
  bool			m_terminated;
  bool			m_destroyOnExit;
  ThreadTermCallback	*m_pTermCallback;
  Mutex			m_mutex;
#if defined (_WIN32)
  static DWORD		m_tlsIndex;
#endif

private:
  static ST_THREAD_RET 	ST_THREAD_CALL_CONV entryPoint (void *arg)
    {
    Thread *pThread = static_cast<Thread *> (arg);
#if defined (_WIN32)
    if (m_tlsIndex == TLS_OUT_OF_INDEXES)
      m_tlsIndex = TlsAlloc ();
    TlsSetValue (m_tlsIndex, (LPVOID) pThread);
#endif
    pThread->InstallThreadName ();
    pThread->GetStartEvent ()->Set ();
    pThread->Run ();
    if (!pThread->IsTerminating ())
      pThread->SelfTerminate ();
    if (pThread->GetTermCallback ())
      pThread->GetTermCallback ()->OnTerminate ();
    if (pThread->IsDestroyOnExit ())
      delete pThread;
    return ST_THREAD_RET_VAL;
    };
  };
  
class Thread2 : public Thread
  {
public:
  Thread2 () {}
  virtual ~Thread2 () {}

  virtual bool Start ();

protected:
  virtual void Run () {}
  virtual bool Run2 () = 0;

private:
  static ST_THREAD_RET 	ST_THREAD_CALL_CONV entryPoint (void *arg)
    {
    Thread2 *pThread = static_cast<Thread2 *> (arg);
#if defined (_WIN32)
    if (m_tlsIndex == TLS_OUT_OF_INDEXES)
      m_tlsIndex = TlsAlloc ();
    TlsSetValue (m_tlsIndex, (LPVOID) pThread);
#endif
    pThread->InstallThreadName ();
    pThread->GetStartEvent ()->Set ();
    if (pThread->Run2 ())
      {
      if (!pThread->IsTerminating ())
        pThread->SelfTerminate ();
      if (pThread->GetTermCallback ())
        pThread->GetTermCallback ()->OnTerminate ();
      if (pThread->IsDestroyOnExit ())
        delete pThread;
      }
    return ST_THREAD_RET_VAL;
    };
  };
  
/************************************************************************/
/*			ThreadPool Object				*/
/************************************************************************/

template <typename T, int numThreads = 1>
class ThreadPool
  {
private:
  vector<T>	m_threads;
  
  ThreadPool ();
  
public:
  ThreadPool (T& t);
  virtual ~ThreadPool () {Terminate ();}

    
  virtual void Start () {for_each (m_threads.begin (), m_threads.end (), mem_fun_ref (&Thread::Start));}
  virtual void Terminate () {for_each (m_threads.begin (), m_threads.end (), mem_fun_ref (&Thread::Terminate));}
  };

template <typename T, int numThreads>
ThreadPool<T, numThreads>::ThreadPool (T& t)
  {
  
  T tClone (t);
  for (int i = 0; i < numThreads; i++)
    {
    m_threads.push_back (tClone);
    }
  }
  
// Methods
void Block (long period);

#if defined (_WIN32) && defined (_DLL)
void DLLTerminating ();
bool IsDLLTerminating ();
#endif

}

}

#endif  /* _SYSTEM_OBJECTS_H */

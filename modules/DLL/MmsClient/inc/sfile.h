/*****************************************************************************/
/* SISCO SOFTWARE MODULE HEADER **********************************************/
/*****************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,            */
/*            2006 All Rights Reserved                                       */
/*                                                                           */
/* MODULE NAME : sfile.h                                                     */
/* PRODUCT(S)  : USPS support                                                */
/*                                                                           */
/* MODULE DESCRIPTION:                                                       */
/*   Header file for USPS directory access functions                         */
/*                                                                           */
/* MODIFICATION LOG:                                                         */
/*   Date    Who  Rev  Comments                                              */
/* --------  ---  ---  ----------------------------------------------------- */
/* 10/13/06  RLH   01  Created                                               */
/*****************************************************************************/


#ifndef _SFILE_H_DF7F67C9_1325_4EF8_9BA6_9242CFCEB6D2_
#define _SFILE_H_DF7F67C9_1325_4EF8_9BA6_9242CFCEB6D2_

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif


#ifdef _WIN32
    #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0401
    #endif
#include <windows.h>
#define S_FILE_DIR_RESOURCE     HANDLE

#else /* unix */
#include <dirent.h>
#define S_FILE_DIR_RESOURCE     DIR *

#endif


#include "glbtypes.h"
#include "gen_list.h"

typedef union
  {
  ST_CHAR                   default_len [1024];

#ifdef MAX_PATH
  ST_CHAR                   max_path_len [MAX_PATH];
#endif

#ifdef _MAX_PATH
  ST_CHAR                   _max_path_len [_MAX_PATH];
#endif

  } S_FILE_DIR_NAME_UNION;


#define S_FILE_DIR_NAME_MAXLEN  (sizeof (S_FILE_DIR_NAME_UNION))


typedef struct              s_file_dir_entry
  {
  DBL_LNK                   l;
  ST_CHAR *                 fileName;
  time_t                    fileTime;
  ST_LONG                   st_size;

  /* Next sorted; NULL for last */
  struct s_file_dir_entry * next;
  } S_FILE_DIR_ENTRY;

typedef S_FILE_DIR_ENTRY *  P_S_FILE_DIR_ENTRY;

typedef struct
  {
  /* Status, updated by sFileDirGetStats   */
  ST_LONG                   numDirs;
  ST_LONG                   numFiles;
  ST_LONG                   totalFileSize;

  /* Directory Listing, updated by sFileGetDirList */
  ST_LONG                   numEntries;
  S_FILE_DIR_ENTRY *        sFileDirEntryList;      /* Unsorted */
  S_FILE_DIR_ENTRY **       sFileDirEntrySorted;    /* Sorted */

  /* User fields */
  S_FILE_DIR_ENTRY *        lastEntryReturned;
  ST_LONG                   seekFileMatch;
  ST_CHAR *                 prevFileMatchName;

  /* Internal fields */
  ST_BOOLEAN                sortedByName;
  } S_FILE_CONTEXT;


S_FILE_CONTEXT *            sFileAllocContext ();

ST_VOID                     sFileFreeContext (
  S_FILE_CONTEXT *          /*O*/ sFileContext);

ST_RET                      sFileDirGetStats (
  S_FILE_CONTEXT *          /*O*/ sFileContext,
  ST_CHAR *                 /*I*/ dirPath);

ST_RET                      sFileGetDirList (
  S_FILE_CONTEXT *          /*O*/ sFileContext,
  ST_CHAR *                 /*I*/ dirPath);

ST_RET                      sFileSortByName (
  S_FILE_CONTEXT *          /*O*/ sFileContext);

S_FILE_DIR_ENTRY *          sFileFindDirEntry (
  S_FILE_CONTEXT *          /*I*/ sFileContext,
  ST_CHAR *                 /*I*/ fileName);


#endif /* _SFILE_H_DF7F67C9_1325_4EF8_9BA6_9242CFCEB6D2_ */


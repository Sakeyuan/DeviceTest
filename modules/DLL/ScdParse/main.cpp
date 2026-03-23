
#include "stdafx.h"
#include "parse.h"
#include "interface.h"

typedef int(*func_GetScdIedList)(IED_LIST *iedList, char *scdFilePath);
typedef int(*func_GetScdIedInfo)(char *iedName, SCL_INFO *iedInfo, char *scdFilePath);
typedef int(*func_GetScd61850Info)(char *iedName, ALL_61850_INFO *all61850Info, char *scdFilePath);
typedef int(*func_SaveScdIedInfo)(char *iedName, char *scdFilePath, char *saveFilePath);


int main()
{

}


#include "stdafx.h"
#include "interface.h"


typedef int(*func_ConnStatus)(void);
typedef int(*func_OpenServer)(char *ServerIP);
typedef void(*func_CloseServer)();
typedef int(*func_StartReport)(HWND hwnd);

typedef int(*func_GetNameList)(NAME_LIST *NameList);
//typedef int(*func_GetVarsList)(VARS_LIST *VarsList);

typedef int(*func_GetYxInfo)(YX_INFO yx_info[], char *DsName, char *LdName);
typedef int(*func_GetYcInfo)(YC_INFO yc_info[], char *DsName, char *LdName);
typedef int(*func_GetYkInfo)(YK_INFO yk_info[], char *DsName, char *LdName);
typedef int(*func_GetDzInfo)(DZ_INFO dz_info[], char *DsName, char *LdName);

typedef int(*func_GetYcValue)(char *DomName, char *VarName, int YcType, float *YcMag, float *YcAng);
typedef int(*func_GetYxValue)(char *DomName, char *VarName, int YxType, ST_UINT8 *YxStat);
typedef int(*func_GetQuality)(char *DomName, char *VarName, unsigned short *Quality);
typedef int(*func_GetYc)(char *DomName, char *VarName, float *YcMag, float *YcAng, unsigned short *Quality);
typedef int(*func_GetYx)(char *DomName, char *VarName, int YxType, ST_UINT8 *YxStat, unsigned short *Quality);
typedef int(*func_ExecuteYk)(char *DomName, char *VarName, int YkValue, int YkModel);

typedef int(*func_GetRcbInfo)(RCB_INFO rcb_info[]);
typedef int(*func_GetRcbValue)(char *DomName, char *VarName, char *ItemName, RCB_INFO *rcb_info);
typedef int(*func_EnableRcb)(char *DomName, char *VarName, int RcbStat);

typedef int(*func_GetLcbInfo)(LCB_INFO lcb_info[]);
typedef int(*func_GetLcbValue)(char *DomName, char *VarName, char *ItemName, LCB_INFO *lcb_info);
typedef int(*func_GetLogList)(LOG_LIST log_list[]);
typedef int(*func_GetLogStat)(char *LDName, char *LogName, LOG_STAT log_stat);
//typedef int(*func_GetLog)(char *LDName, char *LogName, int StartDay, int StartMs, UINT64 StartID, int LogNum, LOG_INFO log_info[]);
typedef int(*func_GetLog)(char *LDName, char *LogName, byte Mode, int StartDay, int StartMs, int StopDay, int StopMs, UINT64 StartID, int LogNum, LOG_INFO log_info[], byte *more);

typedef int(*func_GetDzq)(char *DomName, char *VarName, BYTE *dzq);
typedef int(*func_SetDzq)(char *DomName, char *VarName, BYTE dzq);
//typedef int(*func_ReadDzValue)(DZ_INFO dz_info[], int dz_num);
typedef int(*func_ConfirmDzEdit)(char *DomName, char *VarName);
typedef int(*func_ReadDz)(DZ_INFO dz_info[], int dz_num);



int main()
{
	char ipaddr[20] = "222.111.112.100";
	//char ipaddr[20] = "192.168.253.3";
	int  i, ret;
//	NAME_LIST NameList;
//	VARS_LIST VarsList;
/*
	ST_INT			yx_num;							//遥信通道数
	YX_INFO			yx_info[MAX_YX_NUM];			//遥信信息表
	
	ST_INT			yc_num;							//遥测通道数
	YC_INFO			yc_info[MAX_YC_NUM];			//遥测信息表
	
	ST_INT			yk_num;							//遥控通道数
	YK_INFO			yk_info[MAX_YK_NUM];			//遥控信息表
	
	ST_INT			dz_num;							//定值个数
	DZ_INFO			dz_info[MAX_DZ_NUM];			//定值信息表

	ST_INT			rcb_num;						//遥控通道数
	RCB_INFO		rcb_info[MAX_RCB_NUM];			//遥控信息表
	
	ST_INT			lcb_num;						//日志控制块数
	LCB_INFO		lcb_info[MAX_LCB_NUM];			//日志控制块信息表
	LCB_INFO		lcb_info2;

	ST_INT			log_num;						//日志目录数
	LOG_LIST		log_list[MAX_LOG_LIST];			//日志目录表

	LOG_STAT		log_stat;
	LOG_INFO		log_info[MAX_LOG_INFO];

	float fVal;
	ST_UINT8 bVal;
*/
	func_ConnStatus		ConnStatus;
	func_OpenServer		OpenServer;
	func_CloseServer	CloseServer, test;
	func_StartReport	StartReport;

	func_GetNameList	GetNameList;
//	func_GetVarsList	GetVarsList;
	func_GetYxInfo		GetYxInfo;
	func_GetYcInfo		GetYcInfo;
	func_GetYkInfo		GetYkInfo;
	func_GetDzInfo		GetDzInfo;

	func_GetYcValue		GetYcValue;
	func_GetYxValue		GetYxValue;
	func_GetQuality		GetQuality;
	func_GetYc			GetYc;
	func_GetYx			GetYx;
	func_ExecuteYk		ExecuteYk, CancelYk;

	func_GetRcbInfo		GetRcbInfo;
	func_GetRcbValue	GetRcbValue, SetRcbValue;
	func_EnableRcb		EnableRcb;

	func_GetLcbInfo		GetLcbInfo;
	func_GetLcbValue	GetLcbValue, SetLcbValue;
	func_GetLogList		GetLogList;
	func_GetLogStat		GetLogStat;
	func_GetLog			GetLog;

	func_GetDzq			GetDzAct;//, ReadDzEdit;
	func_SetDzq			SetDzAct;//, SetDzEdit;
//	func_DzValue		ReadDzValue, SetDzValue;
//	func_ConfirmDzEdit	ConfirmDzEdit;
	func_ReadDz			ReadDz, DownDz;
	

	float mag = 0, ang = 0;
	unsigned short q = 0;


	HINSTANCE hDll = LoadLibrary("MmsClient.dll");

//	test = (func_CloseServer)GetProcAddress(hDll, "test");
	
	ConnStatus = (func_ConnStatus)GetProcAddress(hDll, "ConnStatus");
	OpenServer = (func_OpenServer)GetProcAddress(hDll, "OpenServer");
	CloseServer = (func_CloseServer)GetProcAddress(hDll, "CloseServer");
	StartReport = (func_StartReport)GetProcAddress(hDll, "StartReport");

	GetNameList = (func_GetNameList)GetProcAddress(hDll, "GetNameList");
//	GetVarsList = (func_GetVarsList)GetProcAddress(hDll, "GetVarsList");
	GetYxInfo = (func_GetYxInfo)GetProcAddress(hDll, "GetYxInfo");
	GetYcInfo = (func_GetYcInfo)GetProcAddress(hDll, "GetYcInfo");
	GetYkInfo = (func_GetYkInfo)GetProcAddress(hDll, "GetYkInfo");
	GetDzInfo = (func_GetDzInfo)GetProcAddress(hDll, "GetDzInfo");

	GetYcValue = (func_GetYcValue)GetProcAddress(hDll, "GetYcValue");
	GetYxValue = (func_GetYxValue)GetProcAddress(hDll, "GetYxValue");
	GetQuality = (func_GetQuality)GetProcAddress(hDll, "GetQuality");
	GetYc = (func_GetYc)GetProcAddress(hDll, "GetYc");
	GetYx = (func_GetYx)GetProcAddress(hDll, "GetYx");
	ExecuteYk = (func_ExecuteYk)GetProcAddress(hDll, "ExecuteYk");
	CancelYk = (func_ExecuteYk)GetProcAddress(hDll, "CancelYk");

	GetRcbInfo = (func_GetRcbInfo)GetProcAddress(hDll, "GetRcbInfo");
	GetRcbValue = (func_GetRcbValue)GetProcAddress(hDll, "GetRcbValue");
	SetRcbValue = (func_GetRcbValue)GetProcAddress(hDll, "SetRcbValue");
	EnableRcb = (func_EnableRcb)GetProcAddress(hDll, "EnableRcb");

	GetLcbInfo = (func_GetLcbInfo)GetProcAddress(hDll, "GetLcbInfo");
	GetLcbValue = (func_GetLcbValue)GetProcAddress(hDll, "GetLcbValue");
	SetLcbValue = (func_GetLcbValue)GetProcAddress(hDll, "SetLcbValue");
	GetLogList = (func_GetLogList)GetProcAddress(hDll, "GetLogList");
	GetLogStat = (func_GetLogStat)GetProcAddress(hDll, "GetLogStat");
	GetLog = (func_GetLog)GetProcAddress(hDll, "GetLog");

	GetDzAct = (func_GetDzq)GetProcAddress(hDll, "GetDzAct");
	SetDzAct = (func_SetDzq)GetProcAddress(hDll, "SetDzAct");
//	ReadDzEdit = (func_ReadDzq)GetProcAddress(hDll, "ReadDzEdit");
//	ReadDzValue = (func_DzValue)GetProcAddress(hDll, "ReadDzValue");
//	SetDzEdit = (func_SetDzq)GetProcAddress(hDll, "SetDzEdit");
//	SetDzValue = (func_DzValue)GetProcAddress(hDll, "SetDzValue");
//	ConfirmDzEdit = (func_ConfirmDzEdit)GetProcAddress(hDll, "ConfirmDzEdit");
	ReadDz = (func_ReadDz)GetProcAddress(hDll, "ReadDz");
	DownDz = (func_ReadDz)GetProcAddress(hDll, "DownDz");


	ret = OpenServer(ipaddr);
	if( ret != 0 ) return ret;

	//ret = GetYc("PRS7741MEAS", "MMXU1$MX$U$phsA$cVal$mag$f", &mag, &ang, &q);
	//ret = GetQuality("PRS7741LD0", "CHKGGIO1$ST$Alm01", &q);
	//ret = GetQuality("PRS7741CTRL", "CBCSWI1$ST$Pos", &q);
	//ret = GetQuality("PRS7741MEAS", "MMXU1$MX$U$phsA", &q);

//	test();
//	lcb_num = GetLcbInfo(lcb_info);

//	lcb_info2.TrgOps = 0x60;
//	lcb_info2.IntgPd = 100;
//	lcb_info[0].var_name[2] = 'f';
//	ret = SetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "TrgOps", &lcb_info2);
//	ret = SetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "IntgPd", &lcb_info2);

/*
	ret = GetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "", &lcb_info[0]);
	ret = GetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "LogEna", &lcb_info2);
	ret = GetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "LogRef", &lcb_info2);
	ret = GetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "DatSet", &lcb_info2);
	ret = GetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "OldEntrTm", &lcb_info2);
	ret = GetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "OldEnt", &lcb_info2);
	ret = GetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "NewEntrTm", &lcb_info2);
	ret = GetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "NewEnt", &lcb_info2);
	ret = GetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "TrgOps", &lcb_info2);
	ret = GetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "IntgPd", &lcb_info2);

	lcb_info2.log_enable = 0;
	lcb_info2.TrgOps = 0x60;
	lcb_info2.IntgPd = 100;
//	ret = SetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "LogEna", &lcb_info2);
//	ret = SetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "LogRef", &lcb_info2);
//	ret = SetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "DatSet", &lcb_info2);
//	ret = SetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "OldEntrTm", &lcb_info2);
//	ret = SetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "OldEnt", &lcb_info2);
	ret = SetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "NewEntrTm", &lcb_info2);
	ret = SetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "NewEnt", &lcb_info2);
	ret = SetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "TrgOps", &lcb_info2);
	ret = SetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, "IntgPd", &lcb_info2);
*/

//	lcb_info[0].log_enable=0;
//	lcb_info[0].TrgOps = 96;
//	lcb_info[0].IntgPd = 1000;
//	ret = SetLcbValue(lcb_info[0].dom_name, lcb_info[0].var_name, &lcb_info[0]);

//	rcb_num = GetRcbInfo(rcb_info);

//	rcb_info[0].OptFlds = 19517;
//	ret = SetRcbValue(rcb_info[0].dom_name, rcb_info[0].var_name, "OptFlds", rcb_info);
	
//	if( ret != 0 ) return ret;

//	ret = StartReport( );

//	ret = EnableRcb(rcb_info[0].dom_name, rcb_info[0].var_name, 1);
//	ret = EnableRcb(rpt_info[162].dom_name, rpt_info[162].var_name, 0);

//	ret = ExecuteYk("TEMPLATECTRL", "CBCSWI1$CO$Pos", 1, 4);

//	ret = GetNameList(&NameList);

	int st0 = 0;
	
	while(1)
	{
		int st = ConnStatus();
		if (st != st0)
		{
			st0 = st;
			printf("Conn: %d\r\n", st);
		}

//		int rt = GetYc("PS11011PROT", "PDIF1$MX$A1$phsA$cVal$mag$f", &mag, &ang, &q);
//		printf("YC: %d  %f\r\n", ret, mag);

		Sleep(1000);
	}

//	yx_num = GetYxInfo(yx_info, NULL, NULL);
//	yc_num = GetYcInfo(yc_info, "dsMgrChlInfo","MGR");
//	yc_num = GetYcInfo(yc_info, "", "");
//	yk_num = GetYkInfo(yk_info, NULL, NULL);
//	dz_num = GetDzInfo(dz_info, NULL, NULL);
//	ret = SetDzAct(dz_info[0].dom_name,dz_info[0].var_name,2);

//	ret = DownDz(dz_info, dz_num);

//	lcb_num = GetLcbInfo(lcb_info);
//	log_num = GetLogList(log_list);

//	ret = GetLogStat(log_list[0].ld_name, log_list[0].log_name, log_stat);
/*
	BYTE mode=2;
	int day1=11926, ms1=19118693, day2=0, ms2=0, num=0;
	UINT64 id=0;
	BYTE more=0;

	log_list[0].ld_name[2] = 'f';
	ret = GetLog(log_list[0].ld_name, log_list[0].log_name, mode, day1,ms1,day2,ms2,id,num, log_info, &more);
	while( ret>0 && more )
	{
		ret = GetLog(log_list[0].ld_name, log_list[0].log_name, mode, day1,ms1,day2,ms2,id,num, log_info, &more);
	}
	ret = GetLog(log_list[0].ld_name, log_list[0].log_name, 0, day1,ms1,day2,ms2,id,num, log_info, &more);
*/
//	ret = GetLog(log_list[0].ld_name, log_list[0].log_name, 11926, 19118693, 16, 5000, log_info);
//	ret = GetLog(log_list[1].ld_name, log_list[1].log_name, 0,0,0,30, log_info);

//	ret = GetVarsList(&VarsList);

/*
	BYTE b1, b2;
//	ret = ReadDzAct(dzk_info.dom_name,dzk_info.var_name,&b1);
//	ret = ReadDzEdit(dzk_info.dom_name,dzk_info.var_name,&b2);
//	ret = ReadDzValue(dz_info, dz_num);
//	ret = SetDzEdit(dzk_info.dom_name,dzk_info.var_name,2);

	ret = SetDzAct(&dzk_info, 3);
	ret = ReadDz(dz_info, dz_num);
	dz_info[0].dz_fValue = 258.3697;
	dz_info[3].dz_fValue = 0.9514;
	dz_info[4].dz_iValue = 498;
	dz_info[5].dz_bValue = 1;
	dz_info[6].dz_bValue = 0;
	dz_info[7].dz_bValue = 0;
	dz_info[8].dz_bValue = 1;
//	ret = SetDzValue(dz_info, dz_num);
	ret = DownDz(&dzk_info, dz_info, dz_num);
*/

//	ret = CancelYk("TEMPLATECTRL", "QG1CSWI1$CO$Pos", 0);
//	ret = ExecuteYk("TEMPLATECTRL", "QG1CSWI1$CO$Pos", 0);

//	ret = ExecuteYk("PRS7741CTRL", "TYXGGIO4$CO$DPYX10", 1, 4);
//	ret = ExecuteYk("TEMPLATEPROT", "LLN0$CO$EnaRES05", 0);

//	for(i=0;i<3;i++)
//	{
//		ret = ExecuteYk("PRS_753NAPROT", "LLN0$CO$FuncEna1", 0);
//		Sleep(500000);
/*
		ret = ExecuteYk("TEMPLATECTRL", "QG1CSWI1$CO$Pos", 1);
		ret = ExecuteYk("TEMPLATECTRL", "QG1CSWI1$CO$Pos", 0);
		Sleep(5000);
		ret = ExecuteYk("TEMPLATECTRL", "QG1CSWI1$CO$Pos", 1);
		Sleep(5000);
		ret = ExecuteYk("TEMPLATECTRL", "QG1CSWI1$CO$Pos", 0);
		Sleep(5000);
		ret = ExecuteYk("TEMPLATECTRL", "QG1CSWI1$CO$Pos", 1);
		Sleep(5000);
		ret = ExecuteYk("TEMPLATECTRL", "QG1CSWI1$CO$Pos", 0);
*/
//	}


/*
//============================================================
	FILE *fp =NULL;
	int i, m=0;
	
	if( (fp = fopen("all.txt", "w")) == NULL ) return -1;
	
	for( i = 0; i < NameList.da_num; i++ )
	{
		fprintf(fp, "%s\n", NameList.da_info[i].name);
		m++;
	}
	
	fprintf(fp, "%d\n", m);
	fclose(fp);
//============================================================
*/

//============================================================
/*
	FILE *fp =NULL;
	
	if( (fp = fopen("var.txt", "w")) == NULL ) return -1;
	
	for( i = 0; i < yx_num; i++ )
	{
		fprintf(fp, "%4d  %s  %s  %s\n", yx_info[i].id, yx_info[i].dom_name, yx_info[i].var_name, yx_info[i].name);
	}
	fprintf(fp, "\n");

	for( i = 0; i < yc_num; i++ )
	{
		fprintf(fp, "%4d  %s  %s  %s\n", yc_info[i].id, yc_info[i].dom_name, yc_info[i].var_name, yc_info[i].name);
	}
	fprintf(fp, "\n");
	
	for( i = 0; i < yk_num; i++ )
	{
		fprintf(fp, "%4d  %s  %s  %s\n", yk_info[i].id, yk_info[i].dom_name, yk_info[i].var_name, yk_info[i].name);
	}
	fprintf(fp, "\n");
	
	for( i = 0; i < dz_num; i++ )
	{
		fprintf(fp, "%4d  %s  %s  %s\n", dz_info[i].id, dz_info[i].dom_name, dz_info[i].var_name, dz_info[i].name);
	}
	fprintf(fp, "\n");
	
	fclose(fp);
*/
//============================================================

	//CloseServer();
	return 0;
}

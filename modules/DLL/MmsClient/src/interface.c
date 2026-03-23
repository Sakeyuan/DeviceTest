
#include <string.h>

#include "glbtypes.h"
#include "lean_a.h"
#include "gb2utf8.h"

#include "mvl_acse.h"
#include "clntobj.h"
#include "interface.h"
#include "client.h"


#define		MMS_SERVER_NAME		"remote1"
#define		TIMEOUT_SECONDS		15


//HWND			mainWnd;

ST_CHAR			osicfgxml[] = "osicfg.xml";
ST_BOOLEAN		init_done = SD_FALSE;
MVL_CFG_INFO	mvlCfg;
MVL_NET_INFO	*clientNetInfo = NULL;

ST_BOOLEAN		connected = SD_FALSE;		//连接标志

NAME_LIST		name_list;					//对象目录表
ST_BOOLEAN		name_done = SD_FALSE;		//对象目录表是否已经获取

int				type_id_mx[5] = { -1, -1, -1, -1, -1 };	//遥测类型
int				type_id_oper[2] = { -1, -1 };			//遥控执行类型（遥控、遥调）
int				type_id_cancel[2] = { -1, -1 };			//遥控取消类型
int				type_id_lcb = -1;						//日志控制块类型
int				type_id_rcb_br = -1;					//缓存报告控制块类型
int				type_id_rcb_rp = -1;					//非缓存报告控制块类型

func_rpt_process rpt_process = NULL;		//报告处理回调函数


extern ST_BOOLEAN stopWait;

extern MVL_NET_INFO *connectToServer(ST_CHAR *serverARName);
extern ST_RET disconnectFromServer(MVL_NET_INFO *clientNetInfo);
extern ST_RET waitReqDone(MVL_REQ_PEND *req, ST_INT timeout);
extern ST_VOID doCommService();

extern ST_RET named_var_read(MVL_NET_INFO *netInfo, ST_CHAR *varName,
						ST_INT scope, ST_CHAR *domName,
						ST_INT type_id, ST_VOID *dataDest, ST_INT timeOut);
extern ST_RET named_var_write(MVL_NET_INFO *netInfo, ST_CHAR *varName,
						ST_INT scope, ST_CHAR *domName,
						ST_INT type_id,	ST_VOID *dataSrc, ST_INT timeOut);


int SaveListToFile();



void init_name_list()
{
	if( name_list.ld_info ) free(name_list.ld_info);
	if( name_list.da_info ) free(name_list.da_info);
	if( name_list.ds_info ) free(name_list.ds_info);
	if( name_list.dsm_info ) free(name_list.dsm_info);

	memset(&name_list, 0, sizeof(NAME_LIST));
}

int dsm_index(char *varName, char *dsName, char *ldName)
{
	int ret, i, ds_id, ld_id;

	ret = -1;
	for( i = 0; i < name_list.dsm_num; i++ )
	{
		if( !strcmp(varName, name_list.dsm_info[i].name) )
		{
			ds_id = name_list.dsm_info[i].uid;
			ld_id = name_list.ds_info[ds_id].uid;

			if( dsName == NULL || (ldName == NULL && strstr(name_list.ds_info[ds_id].name, dsName))
				|| (strstr(name_list.ds_info[ds_id].name, dsName) && strstr(name_list.ld_info[ld_id].name, ldName)) )
			{
				ret = i;
				break;
			}
		}
	}

	return ret;
}

//获取指定对象的type_id
int get_type_id(char *DomName, char *VarName)
{
	int type_id, ret;
	
	GETVAR_REQ_INFO	getvar_req;
	MVL_REQ_PEND	*reqCtrl;
	VAR_ACC_TSPEC	*type_spec;
	
	if( clientNetInfo == NULL ) return -1;
	
	getvar_req.req_tag = GETVAR_NAME;
	getvar_req.name.object_tag = DOM_SPEC;
	getvar_req.name.domain_id = DomName;
	getvar_req.name.obj_name.item_id = VarName;
	
	ret = mvla_getvar (clientNetInfo, &getvar_req, &reqCtrl);
	if(ret == SD_SUCCESS)
		ret = waitReqDone(reqCtrl, TIMEOUT_SECONDS);
	
	if(ret != SD_SUCCESS) 
	{
		mvl_free_req_ctrl (reqCtrl);
		return -2;
	}
	
	type_spec = &(reqCtrl->u.getvar.resp_info->type_spec);
	type_id = mvl_type_id_create (NULL, type_spec->data, type_spec->len);
	mvl_free_req_ctrl (reqCtrl);
	
	return type_id;
}

//获取指定对象的type_spec
MVL_REQ_PEND	*reqCtrl_type = NULL;

VAR_ACC_TSPEC* get_type_spec(char *DomName, char *VarName)
{
	int ret;
	
	GETVAR_REQ_INFO	getvar_req;
	VAR_ACC_TSPEC	*type_spec;
	
	if( clientNetInfo == NULL ) return NULL;
	
	if(reqCtrl_type != NULL)
	{
		mvl_free_req_ctrl(reqCtrl_type);
		reqCtrl_type = NULL;
	}

	getvar_req.req_tag = GETVAR_NAME;
	getvar_req.name.object_tag = DOM_SPEC;
	getvar_req.name.domain_id = DomName;
	getvar_req.name.obj_name.item_id = VarName;

	ret = mvla_getvar (clientNetInfo, &getvar_req, &reqCtrl_type);
	if(ret == SD_SUCCESS)
		ret = waitReqDone(reqCtrl_type, TIMEOUT_SECONDS);
	
	if(ret != SD_SUCCESS) 
		return NULL;
	
	type_spec = &(reqCtrl_type->u.getvar.resp_info->type_spec);
	return type_spec;
}

//获取对象目录列表，获取成功将name_done置为SD_TRUE，结果存放name_list
int get_name_list()
{
	int   i, j, k, num, ret;

	ST_CHAR **nptr;
	NAMELIST_REQ_INFO getnam_req;
	NAMELIST_RESP_INFO *getnam_resp;
	MVL_REQ_PEND *reqCtrl;
	
	GETVLIST_REQ_INFO getvlist_req;
	GETVLIST_RESP_INFO *getvlist_resp;
	VARIABLE_LIST *  variable_list;
	MVL_REQ_PEND *reqCtrltemp;

//	VAR_ACC_TSPEC	*type_spec;
//	ST_INT			type_id = -1;

	if( name_done )	return 0;	//不重复获取
	
	init_name_list();
	
	if( clientNetInfo == NULL ) return -1;

	getnam_req.cs_objclass_pres = SD_FALSE;
	
	getnam_req.obj.mms_class = MMS_CLASS_DOM;
	getnam_req.objscope = VMD_SPEC;
	getnam_req.cont_after_pres = SD_FALSE;
  
	//循环获取LD列表
	while(1)
	{
		ret = mvla_getnam (clientNetInfo, &getnam_req, &reqCtrl);	//从服务器获取LD列表
		if( ret == SD_SUCCESS )
			ret = waitReqDone(reqCtrl, TIMEOUT_SECONDS);

		if( ret != SD_SUCCESS ) break;

		getnam_resp = reqCtrl->u.getnam.resp_info;
		nptr = (ST_CHAR **)(getnam_resp + 1);

		num = name_list.ld_num + getnam_resp->num_names;
		name_list.ld_info = (NAME_INFO *)realloc(name_list.ld_info, num * sizeof(NAME_INFO));

		for( i = 0; i < getnam_resp->num_names; i++ )	//获取的LD列表存放name_list.ld_info
		{
			name_list.ld_info[name_list.ld_num + i].id = name_list.ld_num + i;
			strcpy(name_list.ld_info[name_list.ld_num + i].name, nptr[i]);
			name_list.ld_info[name_list.ld_num + i].uid = 0;
		}
		name_list.ld_num = num;	//获取到的LD计数存放name_list.ld_num
		
		if( getnam_resp->more_follows )	//后续还有，继续循环获取
		{
			getnam_req.cont_after_pres = SD_TRUE;
			strcpy(getnam_req.continue_after, nptr[getnam_resp->num_names - 1]);
			mvl_free_req_ctrl(reqCtrl);
		}
		else	//后续没有了，退出循环
		{
			mvl_free_req_ctrl(reqCtrl);
			break;
		}
    }

	//对每个LD条目，获取该LD下的对象目录
	for( j = 0; j < name_list.ld_num; j++ )
	{
		getnam_req.objscope = DOM_SPEC;
		strcpy(getnam_req.dname, name_list.ld_info[j].name);
		getnam_req.obj.mms_class = MMS_CLASS_VAR;
		getnam_req.cont_after_pres = SD_FALSE;

		//循环获取DA列表
		while(1)
		{
			ret = mvla_getnam(clientNetInfo, &getnam_req, &reqCtrl);	//从服务器获取DA列表
			if( ret == SD_SUCCESS )
				ret = waitReqDone (reqCtrl, TIMEOUT_SECONDS);
			
			if( ret != SD_SUCCESS ) break;

			getnam_resp = reqCtrl->u.getnam.resp_info;
			nptr = (ST_CHAR **) (getnam_resp + 1);
			
			num = name_list.da_num + getnam_resp->num_names;
			name_list.da_info = (NAME_INFO *)realloc(name_list.da_info, num * sizeof(NAME_INFO));

			for( i = 0; i < getnam_resp->num_names; i++ )	//获取的DA列表存放name_list.da_info
			{
				name_list.da_info[name_list.da_num + i].id = name_list.da_num + i;
				strcpy(name_list.da_info[name_list.da_num + i].name, nptr[i]);
				name_list.da_info[name_list.da_num + i].uid = name_list.ld_info[j].id;
//get_var_type(name_list.ld_info[j].name, nptr[i]);
			}
			name_list.da_num = num;	//获取到的DA计数存放name_list.da_num
			
			if( getnam_resp->more_follows )	//后续还有，继续循环获取
			{
				getnam_req.cont_after_pres = SD_TRUE;
				strcpy(getnam_req.continue_after, nptr[getnam_resp->num_names - 1]);
				mvl_free_req_ctrl(reqCtrl);
			}
			else	//后续没有了，退出循环
			{
				mvl_free_req_ctrl(reqCtrl);
				break;
			}
		}

		getnam_req.obj.mms_class = MMS_CLASS_VARLIST;	
		getnam_req.cont_after_pres = SD_FALSE;

		//循环获取数据集列表
		while(1)
		{
			ret = mvla_getnam(clientNetInfo, &getnam_req, &reqCtrl);	//从服务器获取DataSet列表
			if( ret == SD_SUCCESS )
				ret = waitReqDone(reqCtrl, TIMEOUT_SECONDS);
			
			if( ret != SD_SUCCESS ) break;

			getnam_resp = reqCtrl->u.getnam.resp_info;
			nptr = (ST_CHAR **) (getnam_resp + 1);
			
			num = name_list.ds_num + getnam_resp->num_names;
			name_list.ds_info = (NAME_INFO *)realloc(name_list.ds_info, num * sizeof(NAME_INFO));

			for( i = 0; i < getnam_resp->num_names; i++ )	//获取的DataSet列表存放name_list.ds_info
			{
				name_list.ds_info[name_list.ds_num + i].id = name_list.ds_num + i;
				strcpy(name_list.ds_info[name_list.ds_num + i].name, nptr[i]);
				name_list.ds_info[name_list.ds_num + i].uid = name_list.ld_info[j].id;

				//==== 获取数据集成员列表 =============================================
				getvlist_req.vl_name.object_tag = DOM_SPEC;
				getvlist_req.vl_name.domain_id = name_list.ld_info[j].name;
				getvlist_req.vl_name.obj_name.item_id = nptr[i];

				ret = mvl_getvlist(clientNetInfo, &getvlist_req, &reqCtrltemp);	//从服务器获取DataSet Member列表
				if( ret == SD_SUCCESS )
					ret = waitReqDone(reqCtrltemp, TIMEOUT_SECONDS);

				if( ret != SD_SUCCESS ) break;

				getvlist_resp = reqCtrltemp->u.getvlist.resp_info;
				variable_list = (VARIABLE_LIST *)(getvlist_resp + 1);

				name_list.dsm_info = (NAME_INFO *)realloc(name_list.dsm_info, (name_list.dsm_num + getvlist_resp->num_of_variables) * sizeof(NAME_INFO));

				for( k = 0; k < getvlist_resp->num_of_variables; k++ )	//获取的DataSet Member列表存放name_list.dsm_info
				{
					name_list.dsm_info[name_list.dsm_num + k].id = name_list.dsm_num + k;
					strcpy(name_list.dsm_info[name_list.dsm_num + k].name, variable_list[k].var_spec.vs.name.obj_name.item_id);
					name_list.dsm_info[name_list.dsm_num + k].uid = name_list.ds_info[name_list.ds_num + i].id;
				}
				name_list.dsm_num += getvlist_resp->num_of_variables;	//获取到的DataSet Member计数存放name_list.dsm_num

				mvl_free_req_ctrl (reqCtrltemp);
				//===================================================================//
			}
			name_list.ds_num = num;	//获取到的DataSet计数存放name_list.ds_num
				
			if( getnam_resp->more_follows )	//后续还有，继续循环获取
			{
				getnam_req.cont_after_pres = SD_TRUE;
				strcpy(getnam_req.continue_after, nptr[getnam_resp->num_names - 1]);
				mvl_free_req_ctrl (reqCtrl);
			}
			else	//后续没有了，退出循环
			{
				mvl_free_req_ctrl (reqCtrl);
				break;
			}
		}
	}

#if defined(_DEBUG)
	SaveListToFile();
#endif

	name_done = SD_TRUE;
	return 0;
}

//获取变量类型，返回类型标识，小于0为出错码
int get_var_type(char *DomName, char *VarName)
{
	int ret;
	int type_id;
	
	GETVAR_REQ_INFO	getvar_req;
	MVL_REQ_PEND	*reqCtrl;
	VAR_ACC_TSPEC	*type_spec;
	
	if( clientNetInfo == NULL ) return -1;
	
	getvar_req.req_tag = GETVAR_NAME;
	getvar_req.name.domain_id = DomName;
	getvar_req.name.object_tag = DOM_SPEC;
	getvar_req.name.obj_name.item_id = VarName;
	
	ret = mvla_getvar (clientNetInfo, &getvar_req, &reqCtrl);
	if(ret == SD_SUCCESS)
		ret = waitReqDone(reqCtrl, TIMEOUT_SECONDS);
	
	if(ret != SD_SUCCESS) 
	{
		mvl_free_req_ctrl (reqCtrl);
		return -2;
	}
	
	type_spec = &(reqCtrl->u.getvar.resp_info->type_spec);

	type_id = mvl_type_id_create (NULL, type_spec->data, type_spec->len);
	mvl_free_req_ctrl (reqCtrl);
	if(type_id < 0) return -4;

	return type_id;
}

UINT _stdcall event_proc(LPVOID lParam)
{
	while( connected )
	{
		doCommService();
		Sleep(20);
	}

	return 0;
}

//===============================================================================
// 接口函数
//===============================================================================

// 获取与服务器的连接状态
int __stdcall ConnStatus()
{
	if (clientNetInfo == NULL) return 0;
	if (clientNetInfo->conn_active) return 1;
	return 0;
}

// 关闭服务器（断开与服务器的连接）
void __stdcall CloseServer()
{
	if( clientNetInfo == NULL ) return;

	stopWait = SD_TRUE;
	disconnectFromServer(clientNetInfo);
	clientNetInfo = NULL;

	connected = SD_FALSE;
	Sleep(300);

	dyn_mem_ptr_statistics(0);
	mvl_end_acse();
	dyn_mem_ptr_status();
	
	name_done = SD_FALSE;
	rpt_process = NULL;
}

// 打开服务器（建立与服务器的连接）
int __stdcall OpenServer(char *ServerIP, func_rpt_process fun)
{
	ST_RET			ret;
	ST_ULONG		ipAddr;
	UINT			tID;
	
	if( ServerIP == NULL )
	{
		return -1;
	}
	
	ipAddr = inet_addr(ServerIP);
	if( ipAddr == htonl(INADDR_NONE) )
	{
		return -2;
	}
	
	if( init_done == SD_FALSE )
	{
		if( (ret = stimeInit()) != SD_SUCCESS )
		{
			return -3;
		}
		
		ret = osicfgx(osicfgxml, NULL, 0, &mvlCfg);
		if( ret != SD_SUCCESS )
		{
			return -4;
		}
		
		if( rem_dib_table == NULL )
		{
			return -40;
		}
		
		init_done = SD_TRUE;
	}
	
	strcpy(rem_dib_table->name, MMS_SERVER_NAME);
	rem_dib_table->pres_addr.netAddr.ip = ipAddr;
	
	ret = mvl_start_acse(&mvlCfg);
	if( ret != SD_SUCCESS )
    {
		return -5;
    }
	
	if( clientNetInfo )
	{
		CloseServer();
	}

	connected = SD_TRUE;
	_beginthreadex(NULL, 0, event_proc, NULL, 0, &tID);

	clientNetInfo = connectToServer(rem_dib_table->name);
	if( clientNetInfo == NULL )
	{
		connected = SD_FALSE;
		mvl_end_acse();
		return -6;
	}
	
	name_done = SD_FALSE;

	rpt_process = fun;
	return 0;
}

// 获取61850对象目录表
int __stdcall GetNameList(NAME_LIST *NameList)
{
	int   ret;
	
	ret = get_name_list();
	if( ret != 0 )	return ret;

	memcpy(NameList, &name_list, sizeof(NAME_LIST));
	return 0;
}

// 获取遥信信息表
int __stdcall GetYxInfo(YX_INFO yx_info[], char *dsName, char *ldName)
{
	int i, k, uid, uid0, ret, num;
	char tmps[MAX_NAME_LEN];
	ST_UINT16 UniStr[512];
	ST_UINT8 type;
//	ST_UCHAR UniStr[512];
	ST_BOOLEAN bVal;
	ST_UINT8 tVal;
	ST_INT32 iVal;
	ST_FLOAT fVal;

	ret = get_name_list();
	if( ret != 0 )	return ret;

	num = 0;

	//从对象目录表name_list中解析出遥信信息
	for( i = 0; i < name_list.da_num; i++ )
	{
		uid = name_list.da_info[i].uid;

		if( strstr(name_list.da_info[i].name, "$ST$") )
		{
			strcpy(tmps, name_list.da_info[i].name);
			type = 0;
			k = -1;
			if( strstr(tmps, "$general") )
			{
				k = strstr(tmps, "$general") - tmps;
				type = 9;
			}
			else if( strstr(tmps, "$stVal") )
			{
				k = strstr(tmps, "$stVal") - tmps;
			}
			
			if( k>=0 )
			{
				tmps[k] = '\0';
				k = dsm_index(tmps, dsName, ldName);
				if(k<0) k = dsm_index(name_list.da_info[i].name, dsName, ldName);
				
				if( k>=0 )
				{
					uid0 = name_list.dsm_info[k].uid;
					
					if( !strstr(name_list.ds_info[uid0].name, "GOOSE") 
						&& !strstr(name_list.da_info[i].name,"SKYSGAPC") && !strstr(name_list.da_info[i].name,"SKSTGGIO")
						&& !strstr(name_list.da_info[i].name,"FltNum") && !strstr(name_list.da_info[i].name,"FltLoop") )
					{
//						strcpy(yx_info[num].ds_name, name_list.ds_info[name_list.dsm_info[k].uid].name);
						strcpy(yx_info[num].var_name, name_list.da_info[i].name);
						strcpy(yx_info[num].dom_name, name_list.ld_info[uid].name);
//						yx_info[num].var_type = get_var_type(yx_info[num].dom_name, yx_info[num].var_name);
						memset(yx_info[num].name, 0, MAX_NAME_LEN);
						yx_info[num].yx_type = type;
						yx_info[num].yx_stat = 0;
						yx_info[num].id = num + 1;
						
						//从服务器获取遥信名称
						memcpy(strstr(tmps, "$ST$"), "$DC$", 4);
						strcat(tmps, "$dU");
						ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, yx_info[num].dom_name, UNICODE_STRING255_TYPEID, &UniStr, TIMEOUT_SECONDS);
						if( ret == 0 )
						{
							uni2gb(UniStr, yx_info[num].name, MAX_NAME_LEN );
						}
						
						if( type == 0 )
						{
							//从服务器获取单点遥信状态值
							ret = named_var_read(clientNetInfo, yx_info[num].var_name, DOM_SPEC, yx_info[num].dom_name, BOOLEAN_TYPEID, &bVal, TIMEOUT_SECONDS);
							if( ret == 0 )
							{
								yx_info[num].yx_type = 1;
								yx_info[num].yx_stat = bVal;
							}
							else
							{
								//从服务器获取双点遥信状态值
								ret = named_var_read(clientNetInfo, yx_info[num].var_name, DOM_SPEC, yx_info[num].dom_name, BSTR2_TYPEID, &tVal, TIMEOUT_SECONDS);
								if( ret == 0 )
								{
									yx_info[num].yx_type = 2;
									yx_info[num].yx_stat = (tVal >> 6);
								}
								else
								{
									//从服务器获取整数遥信值
									ret = named_var_read(clientNetInfo, yx_info[num].var_name, DOM_SPEC, yx_info[num].dom_name, INT32_TYPEID, &iVal, TIMEOUT_SECONDS);
									if( ret == 0 )
									{
										yx_info[num].yx_type = 3;
										yx_info[num].yx_iValue = iVal;
									}
									else
									{
										ret = named_var_read(clientNetInfo, yx_info[num].var_name, DOM_SPEC, yx_info[num].dom_name, FLOAT32_TYPEID, &fVal, TIMEOUT_SECONDS);
										if( ret == 0 )
										{
											yx_info[num].yx_type = 4;
											yx_info[num].yx_fValue = fVal;
										}
									}
								}
							}
						}

						num++;
						if( num >= MAX_YX_NUM ) break;
					}
				}
			}
		}
	}

	return num;
}

// 获取遥测信息表
int __stdcall GetYcInfo(YC_INFO yc_info[], char *dsName, char *ldName)
{
	int i, j, k, uid, ret, num;
	char tmps[MAX_NAME_LEN], tmps1[MAX_NAME_LEN];
	ST_UINT16 UniStr[512];
	ST_UINT8 type;
//	ST_UCHAR UniStr[512];
	ST_FLOAT fVal;
	
	ret = get_name_list();
	if( ret != 0 )	return ret;
	
	num = 0;
	
	//从对象目录表name_list中解析出遥测信息
	for( i = 0; i < name_list.da_num; i++ )
	{
		uid = name_list.da_info[i].uid;

		if( strstr(name_list.da_info[i].name, "$MX$") )
		{
			strcpy(tmps, name_list.da_info[i].name);
			type = 0;
			k = -1;
			if( strstr(tmps, "$subCVal$mag$f") )
				k = strstr(tmps, "$subCVal$mag$f") - tmps;
			else if( strstr(tmps, "$cVal$mag$f") )
				k = strstr(tmps, "$cVal$mag$f") - tmps;
			else if( strstr(tmps, "$mag$f") )
				k = strstr(tmps, "$mag$f") - tmps;
			else if( strstr(tmps, "$instMag$i") )
			{
				k = strstr(tmps, "$instMag$i") - tmps;
				type = 1;
			}
			
			if( k>=0 )
			{
				tmps[k] = '\0';
				k = dsm_index(tmps, dsName, ldName);
				if(k<0) k = dsm_index(name_list.da_info[i].name, dsName, ldName);
				
				if( k>=0 )
				{
//					strcpy(yc_info[num].ds_name, name_list.ds_info[name_list.dsm_info[k].uid].name);
					strcpy(yc_info[num].var_name, name_list.da_info[i].name);
					strcpy(yc_info[num].dom_name, name_list.ld_info[uid].name);
					memset(yc_info[num].name, 0, MAX_NAME_LEN);
					yc_info[num].yc_type = 0;
					yc_info[num].yc_mag = 0.0;
					yc_info[num].yc_ang = 0.0;
					yc_info[num].id = num + 1;
					
					if( type == 0 )
					{
						strcpy(tmps1, name_list.da_info[i].name);
						memcpy(strstr(tmps1, "$mag$f"), "$ang$f", 6);
						for( j = i+1; j < name_list.da_num; j++ )
						{
							if( !strcmp(tmps1, name_list.da_info[j].name) )	//有相角
							{
								yc_info[num].yc_type = 1;
								break;
							}
						}
					}
					
					//从服务器获取遥测名称
					strcpy(tmps1, tmps);
					memcpy(strstr(tmps1, "$MX$"), "$DC$", 4);
/*
					if( strstr(tmps1, "$cVal") )
					{
						j = strstr(tmps1, "$cVal") - tmps1;
						tmps1[j] = '\0';
					}
*/
					strcat(tmps1, "$dU");
					ret = named_var_read(clientNetInfo, tmps1, DOM_SPEC, yc_info[num].dom_name, UNICODE_STRING255_TYPEID, &UniStr, TIMEOUT_SECONDS);
					if( ret == 0 )
					{
						uni2gb(UniStr, yc_info[num].name, MAX_NAME_LEN );
					}
					
					//从服务器获取遥测幅值
					ret = named_var_read(clientNetInfo, yc_info[num].var_name, DOM_SPEC, yc_info[num].dom_name, FLOAT32_TYPEID, &fVal, TIMEOUT_SECONDS);
					if( ret == 0 )
					{
						yc_info[num].yc_mag = fVal;
					}
					
					//从服务器获取遥测相角
					if( yc_info[num].yc_type == 1 )
					{
						strcpy(tmps1, yc_info[num].var_name);
						memcpy(strstr(tmps1, "$mag$f"), "$ang$f", 6);
						ret = named_var_read(clientNetInfo, tmps1, DOM_SPEC, yc_info[num].dom_name, FLOAT32_TYPEID, &fVal, TIMEOUT_SECONDS);
						if( ret == 0 )
						{
							yc_info[num].yc_ang = fVal;
						}
					}

					num++;
					if( num >= MAX_YC_NUM ) break;
				}
			}
		}
	}
	
	return num;
}

// 获取遥控信息表
int __stdcall GetYkInfo(YK_INFO yk_info[], char *dsName, char *ldName)
{
	int i, k, uid, ret, num;
	char tmps[MAX_NAME_LEN], tmps1[MAX_NAME_LEN];
	ST_UINT16 UniStr[512];
//	ST_UCHAR UniStr[512];
	ST_INT8	 ctlModel;
	
	ret = get_name_list();
	if( ret != 0 )	return ret;
	
	num = 0;
	
	//从对象目录表name_list中解析出遥控信息
	for( i = 0; i < name_list.da_num; i++ )
	{
		uid = name_list.da_info[i].uid;
		
		if( strstr(name_list.da_info[i].name, "$CO$") )
		{
			if( strstr(name_list.da_info[i].name, "$Oper$ctlVal") &&
				!strstr(name_list.da_info[i].name,"SKYSGAPC") && !strstr(name_list.da_info[i].name,"SKSTGGIO") )
			{
				strcpy(tmps, name_list.da_info[i].name);
				k = strstr(tmps, "$Oper$ctlVal") - tmps;
				tmps[k] = '\0';

				strcpy(tmps1, tmps);
				memcpy(strstr(tmps1, "$CO$"), "$ST$", 4);

				k = dsm_index(tmps1, dsName, ldName);
				if( k>=0 )
				{
//					strcpy(yk_info[num].ds_name, name_list.ds_info[name_list.dsm_info[k].uid].name);
					strcpy(yk_info[num].var_name, name_list.da_info[i].name);
					strcpy(yk_info[num].dom_name, name_list.ld_info[uid].name);
					memset(yk_info[num].name, 0, MAX_NAME_LEN);
					yk_info[num].id = num + 1;
					
					//获取遥控名称
					strcpy(tmps1, tmps);
					memcpy(strstr(tmps1, "$CO$"), "$DC$", 4);
					strcat(tmps1, "$dU");
					ret = named_var_read(clientNetInfo, tmps1, DOM_SPEC, yk_info[num].dom_name, UNICODE_STRING255_TYPEID, &UniStr, TIMEOUT_SECONDS);
					if( ret == 0 )
					{
						uni2gb(UniStr, yk_info[num].name, MAX_NAME_LEN );
					}

					//获取遥控模型
					strcpy(tmps1, tmps);
					memcpy(strstr(tmps1, "$CO$"), "$CF$", 4);
					strcat(tmps1, "$ctlModel");
					ret = named_var_read(clientNetInfo, tmps1, DOM_SPEC, yk_info[num].dom_name, INT8_TYPEID, &ctlModel, TIMEOUT_SECONDS);
					if( ret == 0 )
					{
						yk_info[num].yk_model = ctlModel;
					}

					num++;
					if( num >= MAX_YK_NUM ) break;
				}
			}
		}
	}
	
	return num;
}

/*
// 获取61850对象信息表
int GetVarsList(VARS_LIST *VarsList)
{
	int   ret;
	
	ret = get_vars_list();
	if( ret != 0 )	return ret;
	
	memcpy(VarsList, &vars_list, sizeof(VARS_LIST));
	return 0;
}
*/

// 读取遥信值（状态值）
int __stdcall GetYxValue(char *DomName, char *VarName, int YxType, BYTE *YxStat)
{
	int ret;
	ST_BOOLEAN bVal;
	ST_UINT8 tVal;
	
	if( clientNetInfo == NULL ) return -1;
	
	if( YxType == 2 )	//双点遥信
	{
		//从服务器获取双点遥信状态值
		ret = named_var_read(clientNetInfo, VarName, DOM_SPEC, DomName, BSTR2_TYPEID, &tVal, TIMEOUT_SECONDS);
		if( ret != 0 ) return -2;
		
		*YxStat = (tVal >> 6);
	}
	else	//单点遥信、保护遥信
	{
		//从服务器获取单点遥信状态值
		ret = named_var_read(clientNetInfo, VarName, DOM_SPEC, DomName, BOOLEAN_TYPEID, &bVal, TIMEOUT_SECONDS);
		if( ret != 0 ) return -2;
		
		*YxStat = bVal;
	}
	
	return 0;
}

// 读取遥测值（幅值和相角）
int __stdcall GetYcValue(char *DomName, char *VarName, int YcType, float *YcMag, float *YcAng)
{
	int ret;
	ST_FLOAT fVal;
	char tmps[MAX_NAME_LEN];

	if( clientNetInfo == NULL ) return -1;
	
	//从服务器读取遥测幅值
	ret = named_var_read(clientNetInfo, VarName, DOM_SPEC, DomName, FLOAT32_TYPEID, &fVal, TIMEOUT_SECONDS);
	if( ret != 0 ) return -2;

	*YcMag = fVal;

	if( YcType == 1 && strstr(VarName, "$mag$f") )	//有相角
	{
		strcpy(tmps, VarName);
		memcpy(strstr(tmps, "$mag$f"), "$ang$f", 6);

		//从服务器读取遥测相角
		ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, FLOAT32_TYPEID, &fVal, TIMEOUT_SECONDS);
		if( ret != 0 ) return -3;
		
		*YcAng = fVal;
	}

	return 0;
}

WORD qValue(Quality_TDEF *q)
{
	int i;
	WORD value = 0;
/*
	for (i=0; i<16; i++)
	{
		if (q->data_1[i/8] & (1 << (i & 7)))
			value &= (1 << (15 - i));
	}
*/
	value |= (q->data_1[0] >> 6);

	for (i = 0; i < 6; i++)
	{
		if (q->data_1[0] & (1 << i))
			value |= (1 << (7 - i));
	}
	
	for (i = 3; i < 8; i++)
	{
		if (q->data_1[1] & (1 << i))
			value |= (1 << (15 - i));
	}

	return value;
}

Quality_TDEF* qStruct(WORD Quality)
{
	int i;
	static Quality_TDEF q;

	q.len_1 = 13;
	q.data_1[0] = 0;
	q.data_1[1] = 0;

	q.data_1[0] |= ((Quality & 0x03) << 6);

	for (i = 2; i < 8; i++)
	{
		if (Quality & (1 << i))
			q.data_1[0] |= (1 << (7 - i));
	}
	
	for (i = 8; i < 13; i++)
	{
		if (Quality & (1 << i))
			q.data_1[1] |= (1 << (15 - i));
	}

	return &q;
}

// 读取品质值
int __stdcall GetQuality(char *DomName, char *VarName, WORD *Quality)
{
	int ret, k;
	Quality_TDEF qVal;
	char tmps[MAX_NAME_LEN];
	
	if( clientNetInfo == NULL ) return -1;

	strcpy(tmps, VarName);
	k = -1;
	if( strstr(tmps, "$stVal") )
		k = strstr(tmps, "$stVal") - tmps;
	else if( strstr(tmps, "$subCVal$mag$f") )
		k = strstr(tmps, "$subCVal$mag$f") - tmps;
	else if( strstr(tmps, "$cVal$mag$f") )
		k = strstr(tmps, "$cVal$mag$f") - tmps;
	else if( strstr(tmps, "$mag$f") )
		k = strstr(tmps, "$mag$f") - tmps;
	else if( strstr(tmps, "$instMag$i") )
		k = strstr(tmps, "$instMag$i") - tmps;

	if( k >= 0 ) tmps[k] = '\0';
	
	strcat(tmps, "$q");

	ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, Quality_TYPEID, &qVal, TIMEOUT_SECONDS);
	if( ret != 0 ) return -2;
		
	*Quality = qValue(&qVal);
	return 0;
}

// 读取遥信
int __stdcall GetYx(char *DomName, char *VarName, int YxType, BYTE *YxStat, WORD *Quality)
{
	int ret, k;
	SPS_ST_TDEF spsVal;
	DPS_ST_TDEF dpsVal;
	char tmps[MAX_NAME_LEN];
	
	if( clientNetInfo == NULL ) return -1;

	strcpy(tmps, VarName);
	k = -1;
	if( strstr(tmps, "$stVal") )
		k = strstr(tmps, "$stVal") - tmps;

	if( k >= 0 ) tmps[k] = '\0';
	
	if( YxType == 2 )	//双点遥信
	{
		ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, DPS_ST_TYPEID, &dpsVal, TIMEOUT_SECONDS);
		if( ret != 0 ) return -2;
		
		*YxStat = (dpsVal.stVal[0] >> 6);
		*Quality = qValue(&dpsVal.q);
	}
	else	//单点遥信、保护遥信
	{
		ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, SPS_ST_TYPEID, &spsVal, TIMEOUT_SECONDS);
		if( ret != 0 ) return -2;
		
		*YxStat = spsVal.stVal;
		*Quality = qValue(&spsVal.q);
	}
	
	return 0;
}

// 读取遥测
int __stdcall GetYc(char *DomName, char *VarName, float *YcMag, float *YcAng, WORD *Quality)
{
	int ret, k, m, i;
	char tmps[MAX_NAME_LEN];
	Quality_TDEF *qVal;

	RUNTIME_TYPE	*rt_out;
	ST_INT			num_rt_out;
	ST_UCHAR		buf[200], *p;
	
	if( clientNetInfo == NULL ) return -1;

	strcpy(tmps, VarName);
	k = -1;
	m = 0;
	if( strstr(tmps, "$cVal$mag$f") )
	{
		k = strstr(tmps, "$cVal$mag$f") - tmps;
		m = 1;
	}
	else if( strstr(tmps, "$mag$f") )
	{
		k = strstr(tmps, "$mag$f") - tmps;
		m = 2;
	}
	else if( strstr(tmps, "$instMag$f") )
	{
		k = strstr(tmps, "$instMag$f") - tmps;
		m = 3;
	}
	else if( strstr(tmps, "$instMag$i") )
	{
		k = strstr(tmps, "$instMag$i") - tmps;
		m = 4;
	}

	if( k >= 0 ) tmps[k] = '\0';

	if( type_id_mx[m] < 0 ) type_id_mx[m] = get_type_id(DomName, tmps);
	if( type_id_mx[m] < 0 ) return -3;

	ret = mvl_get_runtime (type_id_mx[m], &rt_out, &num_rt_out);
	if(ret != SD_SUCCESS) return -4;
	
	ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, type_id_mx[m], buf, TIMEOUT_SECONDS);
	if( ret != 0 ) return -2;
		
	*YcMag = 0;
	*YcAng = 0;
	*Quality = 0;

	m = 0;
	p = buf;
	for( i=0; i<num_rt_out; i++ )
	{
		if( rt_out[i].comp_name_ptr == NULL ) continue;

		if( !stricmp(rt_out[i].comp_name_ptr, "mag") )
			m = 1;
		else if( !stricmp(rt_out[i].comp_name_ptr, "ang") )
			m = 2;
		else if( !stricmp(rt_out[i].comp_name_ptr, "f") )
		{
			if( m == 1 ) *YcMag = *(ST_FLOAT *)p;
			else if( m == 2 ) *YcAng = *(ST_FLOAT *)p;
		}
		else if( !stricmp(rt_out[i].comp_name_ptr, "i") )
			*YcMag = *(ST_INT *)p;
		else if( !stricmp(rt_out[i].comp_name_ptr, "q") )
		{
			qVal = (Quality_TDEF *)p;
			*Quality = qValue(qVal);
		}

		p = p + rt_out[i].el_size;
	}

	return 0;
}

// 设置遥信取代
int __stdcall SetYx(char *DomName, char *VarName, int YxType, BYTE YxStat, WORD Quality, BYTE SubEna)
{
	int				ret, k;
	ST_BOOLEAN		ena;
	SPS_SV_TDEF		spsVal;
	DPS_SV_TDEF		dpsVal;
	Quality_TDEF	*q;
	char			tmps[MAX_NAME_LEN];
	
	if( clientNetInfo == NULL ) return -1;

	strcpy(tmps, VarName);
	memcpy(strstr(tmps, "$ST$"), "$SV$", 4);
	
	k = -1;
	if( strstr(tmps, "$stVal") )
		k = strstr(tmps, "$stVal") - tmps;
	
	if( k < 0 ) return -2;

	tmps[k] = '\0';

	q = qStruct(Quality);
	
	if( !SubEna )
	{
		ena = FALSE;
		strcat(tmps, "$subEna");
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, BOOLEAN_TYPEID, &ena, TIMEOUT_SECONDS);
	}
	else if( YxType == 2 )	//双点遥信
	{
		memset(&dpsVal, 0, sizeof(SPS_SV_TDEF));
		dpsVal.subEna = TRUE;
		dpsVal.subVal[0] = (YxStat << 6);
		memcpy(&dpsVal.subQ, q, sizeof(Quality_TDEF));

		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, DPS_SV_TYPEID, &dpsVal, TIMEOUT_SECONDS);
	}
	else if( YxType == 1 )	//单点遥信
	{
		memset(&spsVal, 0, sizeof(SPS_SV_TDEF));
		spsVal.subEna = TRUE;
		spsVal.subVal = YxStat;
		memcpy(&spsVal.subQ, q, sizeof(Quality_TDEF));
	
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, SPS_SV_TYPEID, &spsVal, TIMEOUT_SECONDS);
	}
	else return -9;
	
	if( ret != 0 ) return -3;
	return 0;
}

// 设置遥测取代
int __stdcall SetYc(char *DomName, char *VarName, float YcMag, float YcAng, WORD Quality, BYTE SubEna)
{
	int ret, k, m, i;
	ST_BOOLEAN		ena;
	MV_SV_TDEF		mvVal;
	CMV_SV_TDEF		cmvVal;
	Quality_TDEF	*q;
	char			tmps[MAX_NAME_LEN];

	if( clientNetInfo == NULL ) return -1;

	strcpy(tmps, VarName);
	memcpy(strstr(tmps, "$MX$"), "$SV$", 4);

	k = -1;
	m = 0;
	if( strstr(tmps, "$cVal$mag$f") )
	{
		k = strstr(tmps, "$cVal$mag$f") - tmps;
		m = 1;
	}
	else if( strstr(tmps, "$mag$f") )
	{
		k = strstr(tmps, "$mag$f") - tmps;
		m = 2;
	}
	else if( strstr(tmps, "$instMag$f") )
	{
		k = strstr(tmps, "$instMag$f") - tmps;
		m = 3;
	}
	else if( strstr(tmps, "$instMag$i") )
	{
		k = strstr(tmps, "$instMag$i") - tmps;
		m = 4;
	}

	if( k < 0 ) return -2;

	tmps[k] = '\0';

	q = qStruct(Quality);

	if( !SubEna )
	{
		ena = FALSE;
		strcat(tmps, "$subEna");
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, BOOLEAN_TYPEID, &ena, TIMEOUT_SECONDS);
	}
	else if(m == 1)
	{
		memset(&cmvVal, 0, sizeof(CMV_SV_TDEF));
		cmvVal.subEna = SubEna;
		cmvVal.subCVal.mag.f = YcMag;
		cmvVal.subCVal.ang.f = YcAng;
		memcpy(&cmvVal.subQ, q, sizeof(Quality_TDEF));
		
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, CMV_SV_TYPEID, &cmvVal, TIMEOUT_SECONDS);
	}
	else if(m == 2)
	{
		memset(&mvVal, 0, sizeof(MV_SV_TDEF));
		mvVal.subEna = SubEna;
		mvVal.subMag.f = YcMag;
		memcpy(&mvVal.subQ, q, sizeof(Quality_TDEF));
		
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, MV_SV_TYPEID, &mvVal, TIMEOUT_SECONDS);
	}
	else return -9;

	if( ret != 0 ) return -3;
	return 0;
}


int _yk(char *DomName, char *VarName, int YkValue, int OpType, int Check)	
	//YkValue: 遥控值（0 遥分，1 遥合；10 遥停，11 遥升，12 遥降）
	//OpType : 操作类型（0 遥控选择，1 遥控执行，2 遥控取消）
{
	int i, k, type, ret;
	int type_id;
	char tmps[MAX_NAME_LEN];
	char VarName_SBOw[MAX_NAME_LEN], VarName_Oper[MAX_NAME_LEN], VarName_Cancel[MAX_NAME_LEN];
	
	RUNTIME_TYPE	*rt_out;
	ST_INT			num_rt_out;
	ST_UCHAR		buf[200], *p;
	
	
	if( clientNetInfo == NULL ) return -1;
	if( YkValue != 0 && YkValue != 1 && YkValue != 10 && YkValue != 11 && YkValue != 12 ) return -9;
	if( OpType < 0 || OpType > 2 ) return -9;

	type = 0;
	if( YkValue >= 10 ) type = 1;

	strcpy(tmps, VarName);
	if( strstr(tmps, "$SBOw$ctlVal") )
	{
		k = strstr(tmps, "$SBOw$ctlVal") - tmps;
		tmps[k] = '\0';
	}
	if( strstr(tmps, "$Oper$ctlVal") )
	{
		k = strstr(tmps, "$Oper$ctlVal") - tmps;
		tmps[k] = '\0';
	}

	strcpy(VarName_SBOw, tmps);
	strcat(VarName_SBOw, "$SBOw");
	strcpy(VarName_Oper, tmps);
	strcat(VarName_Oper, "$Oper");
	strcpy(VarName_Cancel, tmps);
	strcat(VarName_Cancel, "$Cancel");
	
	if( OpType<2 )
	{
		if( type_id_oper[type] < 0 ) type_id_oper[type] = get_type_id(DomName, VarName_Oper);
		type_id = type_id_oper[type];
	}
	else
	{
		if( type_id_cancel[type] < 0 ) type_id_cancel[type] = get_type_id(DomName, VarName_Cancel);
		type_id = type_id_cancel[type];
	}

	if(type_id < 0) return -4;
	
	ret = mvl_get_runtime (type_id, &rt_out, &num_rt_out);
	if(ret != SD_SUCCESS) return -4;
	
	memset(buf, 0, 200);
	p = buf;
	
	for(i=0; i<num_rt_out; i++)
	{
		if(rt_out[i].comp_name_ptr==NULL) continue;
		
		if(!stricmp(rt_out[i].comp_name_ptr, "ctlVal"))
		{
			if(type==0)
				*(ST_UCHAR *)p = YkValue;
			else
			{
				//*(ST_UCHAR *)p = 6;
				//*(ST_UCHAR *)(p+1) = (YkValue - 10) << 6;
				*(ST_UCHAR *)p = ((YkValue - 10) << 6);
			}
		}
		else if(!stricmp(rt_out[i].comp_name_ptr, "setMag"))
			*(ST_FLOAT *)p = (ST_FLOAT)YkValue;
		else if(!stricmp(rt_out[i].comp_name_ptr, "Test"))
			*(ST_UCHAR *)p = 0;
		else if(!stricmp(rt_out[i].comp_name_ptr, "orCat"))
			*(ST_UCHAR *)p = 2;
		else if(!stricmp(rt_out[i].comp_name_ptr, "orIdent"))
		{
			*(ST_UCHAR *)p = 1;
			*(ST_UCHAR *)(p+2) = 0x20;
		}
		else if(!stricmp(rt_out[i].comp_name_ptr, "Check"))
		{
			*(ST_UCHAR *)p = 2;
			*(ST_UCHAR *)(p+2) = (Check << 6);
		}
		p = p + rt_out[i].el_size;
	}
	

	if( OpType==0 )
	{
		//遥控选择
		ret = named_var_write(clientNetInfo, VarName_SBOw, DOM_SPEC, DomName, type_id, buf, TIMEOUT_SECONDS);
		if( ret != 0 ) return -5;
	}
	else if( OpType==1 )
	{
		//遥控执行
		ret = named_var_write(clientNetInfo, VarName_Oper, DOM_SPEC, DomName, type_id, buf, TIMEOUT_SECONDS);
		if( ret != 0 ) return -6;
	}
	else
	{
		//遥控取消
		ret = named_var_write(clientNetInfo, VarName_Cancel, DOM_SPEC, DomName, type_id, buf, TIMEOUT_SECONDS);
		if( ret != 0 ) return -9;
	}

	return 0;
}

// 执行遥控
int __stdcall ExecuteYk(char *DomName, char *VarName, int YkValue, int YkModel, int Check)
{
	int ret = 0;

	if( YkModel < 1 || YkModel > 4 ) YkModel = 4;

	if( YkModel == 2 || YkModel == 4 )
		ret = _yk(DomName, VarName, YkValue, 0, Check);

	if( ret == 0 ) 
		ret = _yk(DomName, VarName, YkValue, 1, Check);
	
	return ret;
}

// 取消遥控（选择后取消）
int __stdcall CancelYk(char *DomName, char *VarName, int YkValue, int Check)
{
	int ret;
	
	ret = _yk(DomName, VarName, YkValue, 0, Check);
	if( ret==0 ) 
		ret = _yk(DomName, VarName, YkValue, 2, Check);
	
	return ret;
}

// 遥控选择
int __stdcall YkSelect(char *DomName, char *VarName, int YkValue, int Check)
{
	return _yk(DomName, VarName, YkValue, 0, Check);
}

// 遥控执行
int __stdcall YkOperate(char *DomName, char *VarName, int YkValue, int YkModel, int Check)
{
	return _yk(DomName, VarName, YkValue, 1, Check);
}

// 遥控取消
int __stdcall YkCancel(char *DomName, char *VarName, int YkValue, int Check)
{
	return _yk(DomName, VarName, YkValue, 2, Check);
}


// 获取定值信息表（dz_info的第一条记录为定值控制块信息）
int __stdcall GetDzInfo(DZ_INFO dz_info[], char *dsName, char *ldName)
{
	int i, k, uid, ret, num;
	BYTE dz_type;
	char tmps[MAX_NAME_LEN], tmps1[MAX_NAME_LEN];
	ST_UINT16 UniStr[512];
//	ST_UCHAR UniStr[512];
	ST_UCHAR bVal;
	ST_INT32 iVal;
	ST_FLOAT fVal;
	ST_UINT32 uVal;
	
	ret = get_name_list();
	if( ret != 0 )	return ret;
	
	num = 0;
	
	//从对象目录表name_list中解析出定值信息
	for( i = 0; i < name_list.da_num; i++ )
	{
		uid = name_list.da_info[i].uid;
		
		if( strstr(name_list.da_info[i].name, "$SP$SGCB$NumOfSG") )
		{
			//定值控制块
			strcpy(tmps, name_list.da_info[i].name);
			k = strstr(tmps, "$NumOfSG") - tmps;
			tmps[k] = '\0';
			
			strcpy(dz_info[0].var_name, tmps);
			strcpy(dz_info[0].dom_name, name_list.ld_info[uid].name);
			dz_info[0].dz_iValue = 0;
			dz_info[0].id = 0;
			
			//获取定值区个数
			strcpy(tmps, dz_info[0].var_name);
			strcat(tmps, "$NumOfSG");
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, dz_info[0].dom_name, INT8U_TYPEID, &bVal, TIMEOUT_SECONDS);
			if( ret == 0 ) dz_info[0].dz_type = bVal;

			//获取当前定值区
			strcpy(tmps, dz_info[0].var_name);
			strcat(tmps, "$ActSG");
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, dz_info[0].dom_name, INT8U_TYPEID, &bVal, TIMEOUT_SECONDS);
			if( ret == 0 ) dz_info[0].dz_bValue = bVal;
		}
		else if( strstr(name_list.da_info[i].name, "$SG$") || strstr(name_list.da_info[i].name, "$SP$") )
		{
			strcpy(tmps, name_list.da_info[i].name);
			k = -1;
			dz_type = 0;
			if( strstr(tmps, "$setMag$f") )
			{
				k = strstr(tmps, "$setMag$f") - tmps;
				dz_type = 3;
			}
			else if( strstr(tmps, "$setVal") )
			{
				k = strstr(tmps, "$setVal") - tmps;
				dz_type = 1;
			}
			
			if( k>=0 )
			{
				tmps[k] = '\0';

				k = dsm_index(tmps, dsName, ldName);
				if( k>=0 )
				{
					num++;
					if( num >= MAX_DZ_NUM ) break;

//					strcpy(dz_info[num].ds_name, name_list.ds_info[name_list.dsm_info[k].uid].name);
					strcpy(dz_info[num].var_name, name_list.da_info[i].name);
					strcpy(dz_info[num].dom_name, name_list.ld_info[uid].name);
					memset(dz_info[num].name, 0, MAX_NAME_LEN);
					dz_info[num].dz_type = dz_type;
					dz_info[num].dz_bValue = 0;
					dz_info[num].dz_iValue = 0;
					dz_info[num].dz_fValue = 0.0;
					memset(dz_info[num].dz_sValue, 0, MAX_NAME_LEN);
					dz_info[num].dz_minVal = -999999.0;
					dz_info[num].dz_maxVal = -999999.0;
					dz_info[num].dz_stepSize = -999999.0;
					dz_info[num].id = num;
					
					//获取定值名称
					strcpy(tmps1, tmps);
					if( strstr(name_list.da_info[i].name, "$SG$") )
						memcpy(strstr(tmps1, "$SG$"), "$DC$", 4);
					else
						memcpy(strstr(tmps1, "$SP$"), "$DC$", 4);

					strcat(tmps1, "$dU");
					ret = named_var_read(clientNetInfo, tmps1, DOM_SPEC, dz_info[num].dom_name, UNICODE_STRING255_TYPEID, &UniStr, TIMEOUT_SECONDS);
					if( ret == 0 )
					{
						uni2gb(UniStr, dz_info[num].name, MAX_NAME_LEN );
					}

					//获取定值值
					if( dz_type == 1 )
					{
						ret = named_var_read(clientNetInfo, dz_info[num].var_name, DOM_SPEC, dz_info[num].dom_name, BOOLEAN_TYPEID, &bVal, TIMEOUT_SECONDS);
						if( ret==0 )
						{
							dz_info[num].dz_bValue = bVal;
						}
						else
						{
							ret = named_var_read(clientNetInfo, dz_info[num].var_name, DOM_SPEC, dz_info[num].dom_name, INT32_TYPEID, &iVal, TIMEOUT_SECONDS);
							if( ret==0 )
							{
								dz_type = 2;
								dz_info[num].dz_type = 2;
								dz_info[num].dz_iValue = iVal;
							}
							else
							{
								ret = named_var_read(clientNetInfo, dz_info[num].var_name, DOM_SPEC, dz_info[num].dom_name, UNICODE_STRING255_TYPEID, &UniStr, TIMEOUT_SECONDS);
								if( ret==0 )
								{
									dz_type = 4;
									dz_info[num].dz_type = 4;
									uni2gb(UniStr, dz_info[num].dz_sValue, MAX_NAME_LEN );
								}
							}
						}
					}
					else if( dz_type == 3 )
					{
						ret = named_var_read(clientNetInfo, dz_info[num].var_name, DOM_SPEC, dz_info[num].dom_name, FLOAT32_TYPEID, &fVal, TIMEOUT_SECONDS);
						if( ret==0 )
						{
							dz_info[num].dz_fValue = fVal;
						}
					}
					
					if( strstr(name_list.da_info[i].name, "$SG$") )
					{
						//获取定值单位
						strcpy(tmps1, tmps);
						memcpy(strstr(tmps1, "$SG$"), "$CF$", 4);
						strcat(tmps1, "$units$SIUnit");
						ret = named_var_read(clientNetInfo, tmps1, DOM_SPEC, dz_info[num].dom_name, INT32_TYPEID, &iVal, TIMEOUT_SECONDS);
						if( ret == 0 ) dz_info[num].dz_unit = iVal;
						
						//获取定值最大值、最小值、步长值
						if( dz_type == 2 )
						{
							memcpy(strstr(tmps, "$SG$"), "$CF$", 4);

							strcpy(tmps1, tmps);
							strcat(tmps1, "$minVal");
							ret = named_var_read(clientNetInfo, tmps1, DOM_SPEC, dz_info[num].dom_name, INT32_TYPEID, &iVal, TIMEOUT_SECONDS);
							if( ret == 0 ) dz_info[num].dz_minVal = (float)iVal;
							
							strcpy(tmps1, tmps);
							strcat(tmps1, "$maxVal");
							ret = named_var_read(clientNetInfo, tmps1, DOM_SPEC, dz_info[num].dom_name, INT32_TYPEID, &iVal, TIMEOUT_SECONDS);
							if( ret == 0 ) dz_info[num].dz_maxVal = (float)iVal;
							
							strcpy(tmps1, tmps);
							strcat(tmps1, "$stepSize");
							ret = named_var_read(clientNetInfo, tmps1, DOM_SPEC, dz_info[num].dom_name, INT32U_TYPEID, &uVal, TIMEOUT_SECONDS);
							if( ret == 0 ) dz_info[num].dz_stepSize = (float)uVal;
						}
						else if( dz_type == 3 )
						{
							memcpy(strstr(tmps, "$SG$"), "$CF$", 4);
							
							strcpy(tmps1, tmps);
							strcat(tmps1, "$minVal$f");
							ret = named_var_read(clientNetInfo, tmps1, DOM_SPEC, dz_info[num].dom_name, FLOAT32_TYPEID, &fVal, TIMEOUT_SECONDS);
							if( ret == 0 ) dz_info[num].dz_minVal = fVal;
							
							strcpy(tmps1, tmps);
							strcat(tmps1, "$maxVal$f");
							ret = named_var_read(clientNetInfo, tmps1, DOM_SPEC, dz_info[num].dom_name, FLOAT32_TYPEID, &fVal, TIMEOUT_SECONDS);
							if( ret == 0 ) dz_info[num].dz_maxVal = fVal;
							
							strcpy(tmps1, tmps);
							strcat(tmps1, "$stepSize$f");
							ret = named_var_read(clientNetInfo, tmps1, DOM_SPEC, dz_info[num].dom_name, FLOAT32_TYPEID, &fVal, TIMEOUT_SECONDS);
							if( ret == 0 ) dz_info[num].dz_stepSize = fVal;
						}
					}
				}
			}
		}
	}
	
	return num;
}

// 读取活动定值区号
int __stdcall GetDzAct(char *DomName, char *VarName, BYTE *DzAct)
{
	int ret;
	char tmps[MAX_NAME_LEN];
	ST_UCHAR bVal;
	
	if( clientNetInfo == NULL ) return -1;
	
	strcpy(tmps, VarName);
	strcat(tmps, "$ActSG");
	ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, INT8U_TYPEID, &bVal, TIMEOUT_SECONDS);
	if( ret != 0 ) return -2;

	*DzAct = bVal;
	return 0;
}

// 设置活动定值区
int __stdcall SetDzAct(char *DomName, char *VarName, BYTE DzAct)
{
	int ret;
	char tmps[MAX_NAME_LEN];
	
	if( clientNetInfo == NULL ) return -1;
	
	strcpy(tmps, VarName);
	strcat(tmps, "$ActSG");
	ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, INT8U_TYPEID, &DzAct, TIMEOUT_SECONDS);
	if( ret != 0 ) return -2;
	
	return 0;
}

// 读取编辑定值区号
int __stdcall GetDzEdit(char *DomName, char *VarName, BYTE *DzEdit)
{
	int ret;
	char tmps[MAX_NAME_LEN];
	ST_UCHAR bVal;
	
	if( clientNetInfo == NULL ) return -1;
	
	strcpy(tmps, VarName);
	strcat(tmps, "$EditSG");
	ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, INT8U_TYPEID, &bVal, TIMEOUT_SECONDS);
	if( ret != 0 ) return -2;
	
	*DzEdit = bVal;
	return 0;
}

// 设置编辑定值区
int __stdcall SetDzEdit(char *DomName, char *VarName, BYTE DzEdit)
{
	int ret;
	char tmps[MAX_NAME_LEN];
	
	if( clientNetInfo == NULL ) return -1;
	
	strcpy(tmps, VarName);
	strcat(tmps, "$EditSG");
	ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, INT8U_TYPEID, &DzEdit, TIMEOUT_SECONDS);
	if( ret != 0 ) return -2;
	
	return 0;
}

// 修改定值确认
int __stdcall ConfirmDzEdit(char *DomName, char *VarName)
{
	int ret;
	char tmps[MAX_NAME_LEN];
	BYTE bConf = 1;
	
	if( clientNetInfo == NULL ) return -1;
	
	strcpy(tmps, VarName);
	strcat(tmps, "$CnfEdit");
	ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, BOOLEAN_TYPEID, &bConf, TIMEOUT_SECONDS);
	if( ret != 0 ) return -2;
	
	return 0;
}

// 读取定值（dzq：要读取定值的定值区号，dzq=0时读取当前活动区的定值；dz_info：定值记录块，第一条记录为定值控制块信息；dz_num：定值记录个数）
int __stdcall GetDzValue(BYTE dzq, DZ_INFO dz_info[], int dz_num)
{
	int i, ret;
	char var_name[MAX_NAME_LEN], dom_name[MAX_NAME_LEN];
	ST_UINT16 UniStr[512];
//	ST_UCHAR UniStr[512];
	
	if( clientNetInfo == NULL ) return -1;
	if( dzq > dz_info[0].dz_type ) return -2;

	if( dzq > 0 )
	{
		ret = SetDzEdit(dz_info[0].dom_name, dz_info[0].var_name, dzq);
		if( ret != 0 ) return -3;
	}

	for( i=1; i<=dz_num; i++ )
	{
		strcpy(var_name, dz_info[i].var_name);
		strcpy(dom_name, dz_info[i].dom_name);

		if( dzq > 0 )
		{
			memcpy(strstr(var_name, "$SG$"), "$SE$", 4);
		}

		if( dz_info[i].dz_type == 1 )
		{
			ret = named_var_read(clientNetInfo, var_name, DOM_SPEC, dom_name, BOOLEAN_TYPEID, &dz_info[i].dz_bValue, TIMEOUT_SECONDS);
		}
		else if( dz_info[i].dz_type == 2 )
		{
			ret = named_var_read(clientNetInfo, var_name, DOM_SPEC, dom_name, INT32_TYPEID, &dz_info[i].dz_iValue, TIMEOUT_SECONDS);
		}
		else if( dz_info[i].dz_type == 3 )
		{
			ret = named_var_read(clientNetInfo, var_name, DOM_SPEC, dom_name, FLOAT32_TYPEID, &dz_info[i].dz_fValue, TIMEOUT_SECONDS);
		}
		else if( dz_info[i].dz_type == 4 )
		{
			ret = named_var_read(clientNetInfo, var_name, DOM_SPEC, dom_name, UNICODE_STRING255_TYPEID, &UniStr, TIMEOUT_SECONDS);
			if( ret == 0 )
			{
				uni2gb(UniStr, dz_info[i].dz_sValue, MAX_NAME_LEN );
			}
		}

		if( ret != 0 ) return -4;
	}

	return 0;
}

// 修改定值（dzq：要修改定值的定值区号，dzq=0时修改当前活动区的定值；dz_info：定值记录块，第一条记录为定值控制块信息；dz_num：定值记录个数）
int __stdcall SetDzValue(BYTE dzq, DZ_INFO dz_info[], int dz_num)
{
	int i, ret;
	char var_name[MAX_NAME_LEN], dom_name[MAX_NAME_LEN];
	ST_UINT16 UniStr[512];
	BYTE dzq_edit;
	
	if( clientNetInfo == NULL ) return -1;
	//if( dzq > dz_info[0].dz_type ) return -2;
	if( dzq != 31 && dzq > dz_info[0].dz_type ) return -2;	//南网规定特殊31区

	if( dz_info[0].dz_type > 0 )	//有定值区控制块，设置定值编辑区
	{
		dzq_edit = dzq;
		if( dzq_edit == 0 )
		{
			ret = GetDzAct(dz_info[0].dom_name, dz_info[0].var_name, &dzq_edit);
			if( ret != 0 ) return -3;
		}

		ret = SetDzEdit(dz_info[0].dom_name, dz_info[0].var_name, dzq_edit);
		if( ret != 0 ) return -4;
	}

	for( i=1; i<=dz_num; i++ )
	{
		strcpy(var_name, dz_info[i].var_name);
		strcpy(dom_name, dz_info[i].dom_name);
		
		if( strstr(var_name, "$SG$") )
			memcpy(strstr(var_name, "$SG$"), "$SE$", 4);

		if( dz_info[i].dz_type == 1 )
		{
			ret = named_var_write(clientNetInfo, var_name, DOM_SPEC, dom_name, BOOLEAN_TYPEID, &dz_info[i].dz_bValue, TIMEOUT_SECONDS);
		}
		else if( dz_info[i].dz_type == 2 )
		{
			ret = named_var_write(clientNetInfo, var_name, DOM_SPEC, dom_name, INT32_TYPEID, &dz_info[i].dz_iValue, TIMEOUT_SECONDS);
		}
		else if( dz_info[i].dz_type == 3 )
		{
			ret = named_var_write(clientNetInfo, var_name, DOM_SPEC, dom_name, FLOAT32_TYPEID, &dz_info[i].dz_fValue, TIMEOUT_SECONDS);
		}
		else if( dz_info[i].dz_type == 4 )
		{
			gb2uni(dz_info[i].dz_sValue, UniStr, MAX_NAME_LEN );
			ret = named_var_write(clientNetInfo, var_name, DOM_SPEC, dom_name, UNICODE_STRING255_TYPEID, &UniStr, TIMEOUT_SECONDS);
		}
		
		if( ret != 0 ) return -(10+i);
	}
	
	if( dz_info[0].dz_type > 0 )	//有定值区控制块，确认编辑区定值写入
	{
		ret = ConfirmDzEdit(dz_info[0].dom_name, dz_info[0].var_name);
		if( ret != 0 ) return -5;
	}

	return 0;
}

/*
	net_info = (MVL_NET_INFO*)acsi_ctrl_table[nACSI].pnet_info;
	memset(parse_info,0,sizeof(parse_info));  // 必须清零
	//注：WriteSG()中如果chk_calloc中不加256会导致释放时报错，具体原因不明，因此相应的ReadSG()也加了容错处理
	req_info = (READ_REQ_INFO*) chk_calloc (1, sizeof(READ_REQ_INFO)+SETNUMMAX*sizeof(VARIABLE_LIST)+256);
	req_info->va_spec.var_acc_tag = VAR_ACC_VARLIST;
	vl = (VARIABLE_LIST*) (req_info + 1);
	

	for(int i=0; i<dz_num; i++)
	{
		if( VarNumNo >= SETNUMMAX )
		{
			// Send read request.
			req_info->va_spec.num_of_variables = VarNumNo;
			ret = mvla_read_variables(net_info, req_info, VarNumNo, parse_info, &reqCtrl);
			if (ret == SD_SUCCESS)    ret = waitReqDone(reqCtrl, timeOut, nACSI);
			mvl_free_req_ctrl (reqCtrl);
			
			VarNumNo = 0;
			memset(parse_info,0,sizeof(parse_info));  // 必须清零
			req_info->va_spec.var_acc_tag = VAR_ACC_VARLIST;
			vl = (VARIABLE_LIST *) (req_info + 1);
		}
		
		_snprintf(SetName, NAMESIZE-1, "%s", SGCB.pSG[i]->mmsVARName);
		pLDName = strchr(SetName, '/');
		if(pLDName==NULL)	continue;   //跳过
		
		*pLDName = 0;
		mmsVarName = pLDName+1;
		
		if(-1!=zone)
		{
			//读编辑定值，将$SG$换成$SE$	
			p = strstr(mmsVarName,"$SG$");
			*(p+2) = 'E';
		}
		strcpy(varName[VarNumNo],mmsVarName);
		
		if(strstr(SGCB.pSG[i]->DataType,"BOOL")){
			type_id = BOOLEAN_TYPEID;
		}else if(strstr(SGCB.pSG[i]->DataType,"INT")){
			type_id = INT32_TYPEID;
		}else if(strstr(SGCB.pSG[i]->DataType,"UINT")){
			type_id = INT32U_TYPEID;
		}else if(strstr(SGCB.pSG[i]->DataType,"FLOAT")){
			type_id = FLOAT32_TYPEID;
		}
		
		if(-1 != type_id)
		{
			//named_var_read(net_info,mmsVarName,DOM_SPEC,SetName,type_id, &SGCB.pSG[i]->Value.l, timeOut);
			named_vars_read_Add(&vl[VarNumNo], &parse_info[VarNumNo], SetName,
				DOM_SPEC, varName[VarNumNo], type_id, &SGCB.pSG[i]->Value.l);
			VarNumNo++;
		}
	}
	// Send read request.
	if( VarNumNo > 0 )
	{
		req_info->va_spec.num_of_variables = VarNumNo;
		ret = mvla_read_variables(net_info, req_info, VarNumNo, parse_info, &reqCtrl);
		if( ret==SD_SUCCESS )
			ret=waitReqDone(reqCtrl, timeOut, nACSI);
		mvl_free_req_ctrl(reqCtrl);
	}
	chk_free (req_info);
*/


// 获取日志控制块属性值
int __stdcall GetLcbValue(char *DomName, char *VarName, char *ItemName, LCB_INFO *lcb_info)
{
	int				i, j, ret;
	RUNTIME_TYPE	*rt_out;
	ST_INT			num_rt_out;
	ST_UCHAR		buf[200], *p;
	MMS_BTIME6		tm, *ptm;
	MMS_BVSTRING	bs, *pbs;
	tagDWord_Byte8	tdw8;
	char			tmps[MAX_NAME_LEN];
	char			tmpbuf[MAX_NAME_LEN];
	BOOLEAN			LogEna;
	UINT32			IntgPd;
	OCTET_STRING8_TDEF entID;

	if( clientNetInfo == NULL ) return -1;

	if( ItemName == NULL ||  ItemName == "" )
	{
		if( type_id_lcb < 0 ) type_id_lcb = mvl_type_id_create (NULL, lcb_info->type_spec_data, lcb_info->type_spec_len);	//get_type_id(DomName, VarName);
		if( type_id_lcb < 0 ) return -3;
		
		ret = mvl_get_runtime (type_id_lcb, &rt_out, &num_rt_out);
		if(ret != SD_SUCCESS) return -4;

		ret = named_var_read(clientNetInfo, VarName, DOM_SPEC, DomName, type_id_lcb, buf, TIMEOUT_SECONDS);

		p = buf;
		for(i=0; i<num_rt_out; i++)
		{
			if(rt_out[i].comp_name_ptr==NULL) continue;
			
			if(!stricmp(rt_out[i].comp_name_ptr, "LogEna"))
				lcb_info->log_enable = *(ST_UCHAR *)p;
			else if(!stricmp(rt_out[i].comp_name_ptr, "LogRef"))
				memcpy(lcb_info->log_ref, p, rt_out[i].el_size);
			else if(!stricmp(rt_out[i].comp_name_ptr, "DatSet"))
				memcpy(lcb_info->ds_name, p, rt_out[i].el_size);
			else if(!stricmp(rt_out[i].comp_name_ptr, "OldEntrTm"))
			{
				ptm = (MMS_BTIME6*)p;
				lcb_info->oldest_day = ptm->day;
				lcb_info->oldest_ms = ptm->ms;
			}
			else if(!stricmp(rt_out[i].comp_name_ptr, "NewEntrTm"))
			{
				ptm = (MMS_BTIME6*)p;
				lcb_info->newest_day = ptm->day;
				lcb_info->newest_ms = ptm->ms;
			}
			else if(!stricmp(rt_out[i].comp_name_ptr, "OldEnt"))
			{
				for( j=0; j<8; j++ ) tdw8.cByte[j] = *(p+7-j);
				lcb_info->oldest_id = tdw8.uInt64;
			}
			else if(!stricmp(rt_out[i].comp_name_ptr, "NewEnt"))
			{
				for( j=0; j<8; j++ ) tdw8.cByte[j] = *(p+7-j);
				lcb_info->newest_id = tdw8.uInt64;
			}
			else if(!stricmp(rt_out[i].comp_name_ptr, "TrgOps"))
			{
				pbs = (MMS_BVSTRING*)p;
				lcb_info->TrgOps = pbs->data[0];
			}
			else if(!stricmp(rt_out[i].comp_name_ptr, "IntgPd"))
				lcb_info->IntgPd = *(ST_UINT *)p;

			p = p + rt_out[i].el_size;
		}
	}
	else
	{
		strcpy(tmps, VarName);
		strcat(tmps, "$");
		strcat(tmps, ItemName);
		
		if( !stricmp(ItemName, "LogEna") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, BOOLEAN_TYPEID, &LogEna, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				lcb_info->log_enable = LogEna;
			}
		}
		else if( !stricmp(ItemName, "LogRef") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, VISIBLE_STRING255_TYPEID, tmpbuf, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				strcpy(lcb_info->log_ref, tmpbuf);
			}
		}
		else if( !stricmp(ItemName, "DatSet") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, VISIBLE_STRING255_TYPEID, tmpbuf, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				strcpy(lcb_info->ds_name, tmpbuf);
			}
		}
		else if( !stricmp(ItemName, "OldEntrTm") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, BTIME6_TYPEID, &tm, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				lcb_info->oldest_day = tm.day;
				lcb_info->oldest_ms = tm.ms;
			}
		}
		else if( !stricmp(ItemName, "NewEntrTm") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, BTIME6_TYPEID, &tm, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				lcb_info->newest_day = tm.day;
				lcb_info->newest_ms = tm.ms;
			}
		}
		else if( !stricmp(ItemName, "OldEnt") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, OCTET_STRING8_TYPEID, &entID, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				for( j=0; j<8; j++ ) tdw8.cByte[j] = entID.data_1[7-j];
				lcb_info->oldest_id = tdw8.uInt64;
			}
		}
		else if( !stricmp(ItemName, "NewEnt") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, OCTET_STRING8_TYPEID, &entID, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				for( j=0; j<8; j++ ) tdw8.cByte[j] = entID.data_1[7-j];
				lcb_info->newest_id = tdw8.uInt64;
			}
		}
		else if( !stricmp(ItemName, "TrgOps") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, RTYP_BVSTR6_TYPEID, &bs, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				lcb_info->TrgOps = bs.data[0];
			}
		}
		else if( !stricmp(ItemName, "IntgPd") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, INT32U_TYPEID, &IntgPd, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				lcb_info->IntgPd = IntgPd;
			}
		}
		else
		{
			ret = -9;
		}
	}

	return ret;
}

// 设置日志控制块属性值
int __stdcall SetLcbValue(char *DomName, char *VarName, char *ItemName, LCB_INFO *lcb_info)
{
	int				j, ret;
	MMS_BTIME6		tm;
	MMS_BVSTRING	bs;
	tagDWord_Byte8	tdw8;
	char			tmps[MAX_NAME_LEN];
	OCTET_STRING8_TDEF entID;
	
	if( clientNetInfo == NULL ) return -1;

	strcpy(tmps, VarName);
	strcat(tmps, "$");
	strcat(tmps, ItemName);

	if( !stricmp(ItemName, "LogEna") )
	{
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, BOOLEAN_TYPEID, &lcb_info->log_enable, TIMEOUT_SECONDS);
	}
	else if( !stricmp(ItemName, "LogRef") )
	{
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, VISIBLE_STRING255_TYPEID, &lcb_info->log_ref, TIMEOUT_SECONDS);
	}
	else if( !stricmp(ItemName, "DatSet") )
	{
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, VISIBLE_STRING255_TYPEID, &lcb_info->ds_name, TIMEOUT_SECONDS);
	}
	else if( !stricmp(ItemName, "OldEntrTm") )
	{
		tm.day = lcb_info->oldest_day;
		tm.ms = lcb_info->oldest_ms;
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, BTIME6_TYPEID, &tm, TIMEOUT_SECONDS);
	}
	else if( !stricmp(ItemName, "NewEntrTm") )
	{
		tm.day = lcb_info->newest_day;
		tm.ms = lcb_info->newest_ms;
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, BTIME6_TYPEID, &tm, TIMEOUT_SECONDS);
	}
	else if( !stricmp(ItemName, "OldEnt") )
	{
		tdw8.uInt64 = lcb_info->oldest_id;
		for( j=0; j<8; j++ ) entID.data_1[7-j] = tdw8.cByte[j];
		entID.len_1 = 8;
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, OCTET_STRING8_TYPEID, &entID, TIMEOUT_SECONDS);
	}
	else if( !stricmp(ItemName, "NewEnt") )
	{
		tdw8.uInt64 = lcb_info->newest_id;
		for( j=0; j<8; j++ ) entID.data_1[7-j] = tdw8.cByte[j];
		entID.len_1 = 8;
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, OCTET_STRING8_TYPEID, &entID, TIMEOUT_SECONDS);
	}
	else if( !stricmp(ItemName, "TrgOps") )
	{
		bs.data[0] = lcb_info->TrgOps;
		bs.len = 6;
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, RTYP_BVSTR6_TYPEID, &bs, TIMEOUT_SECONDS);
	}
	else if( !stricmp(ItemName, "IntgPd") )
	{
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, INT32U_TYPEID, &lcb_info->IntgPd, TIMEOUT_SECONDS);
	}
	else
	{
		ret = -9;
	}

	return ret;
}

// 获取日志控制块信息
int __stdcall GetLcbInfo(LCB_INFO lcb_info[])
{
	int i, uid, ret, num;
	char *pstr;
	VAR_ACC_TSPEC* type_spec;
	
	ret = get_name_list();
	if( ret != 0 )	return ret;
	
	num = 0;
	
	//从对象目录表name_list中解析出日志目录
	for( i = 0; i < name_list.da_num; i++ )
	{
		uid = name_list.da_info[i].uid;
		
		pstr = strstr(name_list.da_info[i].name, "$LG$");
		if( pstr )
		{
			pstr += 4;
			if( strchr(pstr, '$') == NULL )
			{
				strcpy(lcb_info[num].var_name, name_list.da_info[i].name);
				strcpy(lcb_info[num].dom_name, name_list.ld_info[uid].name);
				lcb_info[num].id = num + 1;
				
				type_spec = get_type_spec(lcb_info[num].dom_name, lcb_info[num].var_name);
				lcb_info[num].type_spec_len = type_spec->len;
				memcpy(lcb_info[num].type_spec_data, type_spec->data, type_spec->len);

				GetLcbValue(lcb_info[num].dom_name, lcb_info[num].var_name, NULL, &lcb_info[num]);
				
				num++;
				if( num >= MAX_LCB_NUM ) break;
			}
		}
	}
	
	return num;
}

//获取日志目录表
int __stdcall GetLogList(LOG_LIST log_list[])
{
	int   i, j, num, ret;

	ST_CHAR **nptr;
	NAMELIST_REQ_INFO getnam_req;
	NAMELIST_RESP_INFO *getnam_resp;
	MVL_REQ_PEND *reqCtrl;

	NAME_LIST ld_list;

	memset(&ld_list, 0, sizeof(NAME_LIST));

	if( clientNetInfo == NULL ) return -1;

	getnam_req.cs_objclass_pres = SD_FALSE;
	getnam_req.obj.mms_class = MMS_CLASS_DOM;
	getnam_req.objscope = VMD_SPEC;
	getnam_req.cont_after_pres = SD_FALSE;
  
	//循环获取LD列表
	while(1)
	{
		ret = mvla_getnam (clientNetInfo, &getnam_req, &reqCtrl);	//从服务器获取LD列表
		if( ret == SD_SUCCESS )
			ret = waitReqDone(reqCtrl, TIMEOUT_SECONDS);

		if( ret != SD_SUCCESS ) break;

		getnam_resp = reqCtrl->u.getnam.resp_info;
		nptr = (ST_CHAR **)(getnam_resp + 1);

		num = ld_list.ld_num + getnam_resp->num_names;
		ld_list.ld_info = (NAME_INFO *)realloc(ld_list.ld_info, num * sizeof(NAME_INFO));

		for( i = 0; i < getnam_resp->num_names; i++ )
		{
			ld_list.ld_info[ld_list.ld_num + i].id = ld_list.ld_num + i;
			strcpy(ld_list.ld_info[ld_list.ld_num + i].name, nptr[i]);
			ld_list.ld_info[ld_list.ld_num + i].uid = 0;
		}
		ld_list.ld_num = num;
		
		if( getnam_resp->more_follows )	//后续还有，继续循环获取
		{
			getnam_req.cont_after_pres = SD_TRUE;
			strcpy(getnam_req.continue_after, nptr[getnam_resp->num_names - 1]);
			mvl_free_req_ctrl(reqCtrl);
		}
		else	//后续没有了，退出循环
		{
			mvl_free_req_ctrl(reqCtrl);
			break;
		}
    }

	num = 0;

	//对每个LD条目，获取该LD下的日志目录
	for( j = 0; j < ld_list.ld_num; j++ )
	{
		getnam_req.objscope = DOM_SPEC;
		strcpy(getnam_req.dname, ld_list.ld_info[j].name);
		getnam_req.obj.mms_class = MMS_CLASS_JOU;
		getnam_req.cont_after_pres = SD_FALSE;

		//循环获取LOG列表
		while(1)
		{
			ret = mvla_getnam(clientNetInfo, &getnam_req, &reqCtrl);	//从服务器获取LOG列表
			if( ret == SD_SUCCESS )
				ret = waitReqDone (reqCtrl, TIMEOUT_SECONDS);
			
			if( ret != SD_SUCCESS ) break;

			getnam_resp = reqCtrl->u.getnam.resp_info;
			nptr = (ST_CHAR **) (getnam_resp + 1);
			
			for( i = 0; i < getnam_resp->num_names; i++ )
			{
				log_list[num].id = num + 1;
				strcpy(log_list[num].ld_name, ld_list.ld_info[j].name);
				strcpy(log_list[num].log_name, nptr[i]);
				num++;
				if( num >= MAX_LOG_LIST ) break;
			}
			if( num >= MAX_LOG_LIST ) break;
			
			if( getnam_resp->more_follows )	//后续还有，继续循环获取
			{
				getnam_req.cont_after_pres = SD_TRUE;
				strcpy(getnam_req.continue_after, nptr[getnam_resp->num_names - 1]);
				mvl_free_req_ctrl(reqCtrl);
			}
			else	//后续没有了，退出循环
			{
				mvl_free_req_ctrl(reqCtrl);
				break;
			}
		}
	}

	return num;
}

//获取日志状态
int __stdcall GetLogStat(char *LDName, char *LogName, LOG_STAT log_stat)
{
	int   ret;

	JSTAT_REQ_INFO jstat_req;
	MVL_REQ_PEND *reqCtrl;
	JSTAT_RESP_INFO *jstat_resp;
	MVL_JOURNAL_ENTRY *jou_entry;


	if( clientNetInfo == NULL ) return -1;

	memset(&jstat_req, 0, sizeof(JSTAT_REQ_INFO));
	jstat_req.jou_name.object_tag = DOM_SPEC;
	jstat_req.jou_name.domain_id = LDName;
	jstat_req.jou_name.obj_name.item_id = LogName;

	ret = mvla_jstat(clientNetInfo, &jstat_req, &reqCtrl);
	if( ret == SD_SUCCESS )
		ret = waitReqDone(reqCtrl, TIMEOUT_SECONDS);
	
	if( ret != SD_SUCCESS ) return -2;
	
	jstat_resp = reqCtrl->u.jstat.resp_info;
	jou_entry = (MVL_JOURNAL_ENTRY *) (jstat_resp + 1);

	log_stat.current_id = jstat_resp->cur_entries;
	log_stat.mms_deletable = jstat_resp->mms_deletable;

	return 0;
}


int		LastLogDay, LastLogMs;
UINT64	LastLogID;

//获取日志内容（mode 获取方式：位1 指定时间及条目号之后，位2 指定起始时间，位3 指定终止时间，位4 指定起始条目号，位5 指定条目数）
//    每次调用读取一次，如有后续则more置1再次调用。上次调用获取的最后条目时间、条目号保存在LastLogDay、LastLogMs和LastLogID
int __stdcall GetLog(char *LDName, char *LogName, byte Mode, int StartDay, int StartMs, int StopDay, int StopMs, UINT64 StartID, int LogNum, LOG_INFO log_info[], byte *more)
{
	int   j, k, ret, num;
	tagDWord_Byte8 tdw8;
	
	JREAD_REQ_INFO jread_req;
	MVL_REQ_PEND *reqCtrl;
	MVL_JREAD_RESP_INFO *jread_resp;
	MVL_JOURNAL_ENTRY *jou_entry;
	MMS_BTOD *occur_time;
	
	if( clientNetInfo == NULL ) return -1;
	
	tdw8.uInt64 = 0;
	num = 0;

	memset(&jread_req, 0, sizeof(JREAD_REQ_INFO));
	jread_req.jou_name.object_tag = DOM_SPEC;
	jread_req.jou_name.domain_id = LDName;
	jread_req.jou_name.obj_name.item_id = LogName;

	if( (Mode & 1) != 0 )	//位1
	{
		jread_req.sa_entry_pres = SD_TRUE;
		jread_req.time_spec.form = MMS_BTOD6;
		jread_req.time_spec.day = StartDay;
		jread_req.time_spec.ms = StartMs;
		tdw8.uInt64 = StartID;
		jread_req.entry_spec_len = 8;
		jread_req.entry_spec = (ST_UCHAR*)calloc(8, sizeof(ST_UCHAR));
		for( k=0; k<8; k++ ) jread_req.entry_spec[k] = tdw8.cByte[7-k];
	}
	else
	{
		if( (Mode & 2) != 0 )	//位2
		{
			jread_req.range_start_pres = SD_TRUE;
			jread_req.start_tag = 0;
			jread_req.start_time.form = MMS_BTOD6;
			jread_req.start_time.day = StartDay;
			jread_req.start_time.ms = StartMs;
		}
		else if( (Mode & 8) != 0 )	//位4
		{
			jread_req.range_start_pres = SD_TRUE;
			jread_req.start_tag = 1;
			tdw8.uInt64 = StartID;
			jread_req.start_entry_len = 8;
			jread_req.start_entry = (ST_UCHAR*)calloc(8, sizeof(ST_UCHAR));
			for( k=0; k<8; k++ ) jread_req.start_entry[k] = tdw8.cByte[7-k];
		}

		if( (Mode & 4) != 0 )	//位3
		{
			jread_req.range_stop_pres = SD_TRUE;
			jread_req.stop_tag = 0;
			jread_req.end_time.form = MMS_BTOD6;
			jread_req.end_time.day = StopDay;
			jread_req.end_time.ms = StopMs;
		}
		else if( (Mode & 16) != 0 )	//位5
		{
			jread_req.range_stop_pres = SD_TRUE;
			jread_req.stop_tag = 1;
			jread_req.num_of_entries = LogNum;
		}
	}

	if( *more )
	{
		jread_req.sa_entry_pres = SD_TRUE;
		jread_req.time_spec.form = MMS_BTOD6;
		jread_req.time_spec.day = LastLogDay;
		jread_req.time_spec.ms = LastLogMs;
		tdw8.uInt64 = LastLogID;
		jread_req.entry_spec_len = 8;
		jread_req.entry_spec = (ST_UCHAR*)calloc(8, sizeof(ST_UCHAR));
		for( k=0; k<8; k++ ) jread_req.entry_spec[k] = tdw8.cByte[7-k];
	}

	ret = mvla_jread(clientNetInfo, &jread_req, &reqCtrl);
	if( ret == SD_SUCCESS )
		ret = waitReqDone(reqCtrl, 2*TIMEOUT_SECONDS);
	else
		ret = -2;
/*	
	if (ret == SD_SUCCESS)
	{
		if( reqCtrl->result != SD_SUCCESS )
		{
			ret = -100 - reqCtrl->event->u.mms.pdu[reqCtrl->event->u.mms.pdu_len - 1];
		}
	}
*/
	if( ret != SD_SUCCESS ) return ret;

	jread_resp = reqCtrl->u.jread.resp_info;
	jou_entry = (MVL_JOURNAL_ENTRY *) (jread_resp + 1);

	for( j = 0; j < jread_resp->num_of_jou_entry; j++ )
	{
		occur_time = &jou_entry->occur_time;
		for( k=0; k<8; k++ ) tdw8.cByte[k] = jou_entry->entry_id[7-k];

		log_info[num].id = tdw8.uInt64;
		log_info[num].day = jou_entry->occur_time.day;
		log_info[num].ms = jou_entry->occur_time.ms;
		strcpy(log_info[num].dom_name, jou_entry->ef.data.evcon_name.domain_id);
		strcpy(log_info[num].var_name, jou_entry->ef.data.evcon_name.obj_name.item_id);
		strcpy(log_info[num].var_ref, jou_entry->ef.data.list_of_var->var_tag);
		log_info[num].var_data_len = jou_entry->ef.data.list_of_var->value_spec.len;
		memcpy(log_info[num].var_data, jou_entry->ef.data.list_of_var->value_spec.data, log_info[num].var_data_len);

		num++;
		jou_entry++;
	}

	if( jread_resp->more_follows )	//后续还有
	{
		LastLogDay = occur_time->day;
		LastLogMs = occur_time->ms;
		LastLogID = tdw8.uInt64;
		*more = 1;
	}
	else	//后续没有了
	{
		*more = 0;
	}

	mvl_free_req_ctrl(reqCtrl);

	return num;
}


// 获取报告控制块属性值
int __stdcall GetRcbValue(char *DomName, char *VarName, char *ItemName, RCB_INFO *rcb_info)
{
	BOOLEAN br = FALSE;

	int				i, j, ret, len, type_id;
	RUNTIME_TYPE	*rt_out;
	ST_INT			num_rt_out;
	ST_UCHAR		buf[500], *p;
	MMS_BTIME6		tm, *ptm;
	MMS_BVSTRING	bs, *pbs;
	tagDWord_Byte8	tdw8;
	char			tmps[MAX_NAME_LEN];
	char			tmpbuf[MAX_NAME_LEN];
	BOOLEAN			RptEna, Resv, GI, PurgeBuf;
	ST_UINT32		ConfRev, BufTm, IntgPd;
	ST_UINT16		SqNum;
	OCTET_STRING8_TDEF entID;

	if( clientNetInfo == NULL ) return -1;

	if( strstr(VarName, "$BR$") ) br = TRUE;
	if( br )
		type_id = type_id_rcb_br;
	else
		type_id = type_id_rcb_rp;

	if( ItemName == NULL ||  ItemName == "" )
	{
		//if( type_id < 0 ) type_id = mvl_type_id_create (NULL, rcb_info->type_spec_data, rcb_info->type_spec_len);	//get_type_id(DomName, VarName);
		if( type_id < 0 ) type_id = get_type_id(DomName, VarName);
		if( type_id < 0 ) return -3;
		
		if( br )
			type_id_rcb_br = type_id;
		else
			type_id_rcb_rp = type_id;

		ret = mvl_get_runtime (type_id, &rt_out, &num_rt_out);
		if(ret != SD_SUCCESS) return -4;

		ret = named_var_read(clientNetInfo, VarName, DOM_SPEC, DomName, type_id, buf, TIMEOUT_SECONDS);
		if(ret != SD_SUCCESS) return -5;

		p = buf;
		for(i=0; i<num_rt_out; i++)
		{
			if(rt_out[i].comp_name_ptr==NULL) continue;
			
			len = rt_out[i].el_size;
			if(len > MAX_NAME_LEN) len = MAX_NAME_LEN;

			if(!stricmp(rt_out[i].comp_name_ptr, "RptID"))
				memcpy(rcb_info->RptID, p, len);
			else if(!stricmp(rt_out[i].comp_name_ptr, "RptEna"))
				rcb_info->RptEna = *(ST_UCHAR *)p;
			else if(!stricmp(rt_out[i].comp_name_ptr, "Resv"))
				rcb_info->Resv = *(ST_UCHAR *)p;
			else if(!stricmp(rt_out[i].comp_name_ptr, "DatSet"))
				memcpy(rcb_info->DatSet, p, len);
			else if(!stricmp(rt_out[i].comp_name_ptr, "ConfRev"))
				rcb_info->ConfRev = *(ST_UINT32 *)p;
			else if(!stricmp(rt_out[i].comp_name_ptr, "OptFlds"))
				rcb_info->OptFlds = *(ST_UINT16 *)(p+2);
			else if(!stricmp(rt_out[i].comp_name_ptr, "BufTm"))
				rcb_info->BufTm = *(ST_UINT32 *)p;
			else if(!stricmp(rt_out[i].comp_name_ptr, "SqNum"))
				rcb_info->SqNum = *(ST_UINT16 *)p;
			else if(!stricmp(rt_out[i].comp_name_ptr, "TrgOps"))
			{
				pbs = (MMS_BVSTRING*)p;
				rcb_info->TrgOps = pbs->data[0];
			}
			else if(!stricmp(rt_out[i].comp_name_ptr, "IntgPd"))
				rcb_info->IntgPd = *(ST_UINT32 *)p;
			else if(!stricmp(rt_out[i].comp_name_ptr, "GI"))
				rcb_info->GI = *(ST_UCHAR *)p;
			else if(!stricmp(rt_out[i].comp_name_ptr, "PurgeBuf"))
				rcb_info->PurgeBuf = *(ST_UCHAR *)p;
			else if(!stricmp(rt_out[i].comp_name_ptr, "EntryID"))
			{
				for( j=0; j<8; j++ ) tdw8.cByte[j] = *(p+7-j);
				rcb_info->entry_id = tdw8.uInt64;
			}
			else if(!stricmp(rt_out[i].comp_name_ptr, "TimeofEntry"))
			{
				ptm = (MMS_BTIME6*)p;
				rcb_info->entry_day = ptm->day;
				rcb_info->entry_ms = ptm->ms;
			}

			p = p + rt_out[i].el_size;
		}
	}
	else
	{
		strcpy(tmps, VarName);
		strcat(tmps, "$");
		strcat(tmps, ItemName);
		
		if( !stricmp(ItemName, "RptID") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, VISIBLE_STRING255_TYPEID, tmpbuf, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				strcpy(rcb_info->RptID, tmpbuf);
			}
		}
		else if( !stricmp(ItemName, "RptEna") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, BOOLEAN_TYPEID, &RptEna, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				rcb_info->RptEna = RptEna;
			}
		}
		else if( !stricmp(ItemName, "Resv") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, BOOLEAN_TYPEID, &Resv, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				rcb_info->Resv = Resv;
			}
		}
		else if( !stricmp(ItemName, "DatSet") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, VISIBLE_STRING255_TYPEID, tmpbuf, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				strcpy(rcb_info->DatSet, tmpbuf);
			}
		}
		else if( !stricmp(ItemName, "ConfRev") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, INT32U_TYPEID, &ConfRev, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				rcb_info->ConfRev = ConfRev;
			}
		}
		else if( !stricmp(ItemName, "OptFlds") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, RTYP_BVSTR10_TYPEID, tmpbuf, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				rcb_info->OptFlds = *(ST_UINT16 *)(&tmpbuf[2]);
			}
		}
		else if( !stricmp(ItemName, "BufTm") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, INT32U_TYPEID, &BufTm, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				rcb_info->BufTm = BufTm;
			}
		}
		else if( !stricmp(ItemName, "SqNum") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, INT16U_TYPEID, &SqNum, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				rcb_info->SqNum = SqNum;
			}
		}
		else if( !stricmp(ItemName, "TrgOps") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, RTYP_BVSTR6_TYPEID, &bs, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				rcb_info->TrgOps = bs.data[0];
			}
		}
		else if( !stricmp(ItemName, "IntgPd") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, INT32U_TYPEID, &IntgPd, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				rcb_info->IntgPd = IntgPd;
			}
		}
		else if( !stricmp(ItemName, "GI") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, BOOLEAN_TYPEID, &GI, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				rcb_info->GI = GI;
			}
		}
		else if( !stricmp(ItemName, "PurgeBuf") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, BOOLEAN_TYPEID, &PurgeBuf, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				rcb_info->PurgeBuf = PurgeBuf;
			}
		}
		else if( !stricmp(ItemName, "EntryID") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, OCTET_STRING8_TYPEID, &entID, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				for( j=0; j<8; j++ ) tdw8.cByte[j] = entID.data_1[7-j];
				rcb_info->entry_id = tdw8.uInt64;
			}
		}
		else if( !stricmp(ItemName, "TimeofEntry") )
		{
			ret = named_var_read(clientNetInfo, tmps, DOM_SPEC, DomName, BTIME6_TYPEID, &tm, TIMEOUT_SECONDS);
			if( ret==0 )
			{
				rcb_info->entry_day = tm.day;
				rcb_info->entry_ms = tm.ms;
			}
		}
		else
		{
			ret = -9;
		}
	}

	return ret;
}

// 设置报告控制块属性值
int __stdcall SetRcbValue(char *DomName, char *VarName, char *ItemName, RCB_INFO *rcb_info)
{
	int				j, ret;
	MMS_BTIME6		tm;
	MMS_BVSTRING	bs;
	ST_UINT32		ui;
	tagDWord_Byte8	tdw8;
	char			tmps[MAX_NAME_LEN];
	
	if( clientNetInfo == NULL ) return -1;
	
	strcpy(tmps, VarName);
	strcat(tmps, "$");
	strcat(tmps, ItemName);
	
	if( !stricmp(ItemName, "RptEna") )
	{
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, BOOLEAN_TYPEID, &rcb_info->RptEna, TIMEOUT_SECONDS);
	}
	else if( !stricmp(ItemName, "RptID") )
	{
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, VISIBLE_STRING255_TYPEID, &rcb_info->RptID, TIMEOUT_SECONDS);
	}
	else if( !stricmp(ItemName, "Resv") )
	{
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, BOOLEAN_TYPEID, &rcb_info->Resv, TIMEOUT_SECONDS);
	}
	else if( !stricmp(ItemName, "DatSet") )
	{
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, VISIBLE_STRING255_TYPEID, &rcb_info->DatSet, TIMEOUT_SECONDS);
	}
	else if( !stricmp(ItemName, "OptFlds") )
	{
		ui = 10 + 65536 * rcb_info->OptFlds;
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, RTYP_BVSTR10_TYPEID, &ui, TIMEOUT_SECONDS);
	}
	else if( !stricmp(ItemName, "BufTm") )
	{
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, INT16U_TYPEID, &rcb_info->BufTm, TIMEOUT_SECONDS);
	}
	else if( !stricmp(ItemName, "TrgOps") )
	{
		bs.data[0] = rcb_info->TrgOps;
		bs.len = 6;
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, RTYP_BVSTR6_TYPEID, &bs, TIMEOUT_SECONDS);
	}
	else if( !stricmp(ItemName, "IntgPd") )
	{
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, INT32U_TYPEID, &rcb_info->IntgPd, TIMEOUT_SECONDS);
	}
	else if( !stricmp(ItemName, "GI") )
	{
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, BOOLEAN_TYPEID, &rcb_info->GI, TIMEOUT_SECONDS);
	}
	else if( !stricmp(ItemName, "PurgeBuf") )
	{
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, BOOLEAN_TYPEID, &rcb_info->PurgeBuf, TIMEOUT_SECONDS);
	}
	else
	{
		ret = -9;
	}
	
	return ret;
}

// 获取报告控制块信息表
int __stdcall GetRcbInfo(RCB_INFO rcb_info[])
{
	int i, uid, ret, num;
	char *pstr;
	VAR_ACC_TSPEC* type_spec;
	
	ret = get_name_list();
	if( ret != 0 )	return ret;
	
	num = 0;
	
	//从对象目录表name_list中解析出报告信息
	for( i = 0; i < name_list.da_num; i++ )
	{
		uid = name_list.da_info[i].uid;
		
		pstr = strstr(name_list.da_info[i].name, "$BR$");
		if( !pstr ) pstr = strstr(name_list.da_info[i].name, "$RP$");

		if( pstr )
		{
			pstr += 4;
			if( strchr(pstr, '$') == NULL )
			{
				strcpy(rcb_info[num].var_name, name_list.da_info[i].name);
				strcpy(rcb_info[num].dom_name, name_list.ld_info[uid].name);
				rcb_info[num].id = num + 1;

				type_spec = get_type_spec(rcb_info[num].dom_name, rcb_info[num].var_name);
				rcb_info[num].type_spec_len = type_spec->len;
				memcpy(rcb_info[num].type_spec_data, type_spec->data, type_spec->len);
				
				GetRcbValue(rcb_info[num].dom_name, rcb_info[num].var_name, NULL, &rcb_info[num]);
				
				num++;
				if( num >= MAX_RCB_NUM ) break;
			}
		}
	}
	
	return num;
}

// 报告控制块启用或禁用（enable = 1 或 0 ）
int __stdcall EnableRcb(char *DomName, char *VarName, int RcbStat)
{
	int ret = 0;
	BOOLEAN br = FALSE;
	char tmps[MAX_NAME_LEN];

	char RptID[MAX_NAME_LEN];
	ST_BOOLEAN Resv = TRUE;
	ST_UINT32 IntgPd = 2000;
	ST_UINT16 OptFlds = 0x8078;
	ST_UCHAR TrgOps = 0x6c;
	ST_BOOLEAN RptEna;

	WR_INFO wrInfo[8];
	ST_CHAR var_name[8][MAX_NAME_LEN];

	ST_UINT32 uiOptFlds;
	MMS_BVSTRING bsTrgOps;
	ST_INT i;

	if( clientNetInfo == NULL ) return -1;
	
	if( strstr(VarName, "$BR$") ) br = TRUE;

	if( RcbStat )
	{
		i = 0;

		sprintf (var_name[i], "%s$RptID", VarName);
		wrInfo[i].var_name = var_name[i];
		wrInfo[i].type_id = VISIBLE_STRING255_TYPEID;
		sprintf (RptID, "%s/%s", DomName, VarName);
		wrInfo[i].data_src = &RptID;
		i++;

		if( !br )
		{
			sprintf (var_name[i], "%s$Resv", VarName);
			wrInfo[i].var_name = var_name[i];
			wrInfo[i].type_id = BOOLEAN_TYPEID;
			wrInfo[i].data_src = &Resv;
			i++;
		}

		sprintf (var_name[i], "%s$IntgPd", VarName);
		wrInfo[i].var_name = var_name[i];
		wrInfo[i].type_id = INT32U_TYPEID;
		if(br) IntgPd = 0;
		wrInfo[i].data_src = &IntgPd;
		i++;
		
		sprintf (var_name[i], "%s$OptFlds", VarName);
		wrInfo[i].var_name = var_name[i];
		wrInfo[i].type_id = RTYP_BVSTR10_TYPEID;
		uiOptFlds = 10 + 65536 * OptFlds;
		wrInfo[i].data_src = &uiOptFlds;
		i++;
		
		sprintf (var_name[i], "%s$TrgOps", VarName);
		wrInfo[i].var_name = var_name[i];
		wrInfo[i].type_id = RTYP_BVSTR6_TYPEID;
		if(br) TrgOps = 0x64;
		bsTrgOps.data[0] = TrgOps;
		bsTrgOps.len = 6;
		wrInfo[i].data_src = &bsTrgOps;
		i++;
		
		ret = named_var_write_multi(clientNetInfo, wrInfo, i, DOM_SPEC, DomName, TIMEOUT_SECONDS);

		if (ret == SD_SUCCESS)
		{
			strcpy(tmps, VarName);
			strcat(tmps, "$RptEna");
			RptEna = TRUE;
			ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, BOOLEAN_TYPEID, &RptEna, TIMEOUT_SECONDS);
		}
	}
	else
	{
		strcpy(tmps, VarName);
		strcat(tmps, "$RptEna");
		RptEna = FALSE;
		ret = named_var_write(clientNetInfo, tmps, DOM_SPEC, DomName, BOOLEAN_TYPEID, &RptEna, TIMEOUT_SECONDS);
	}

	return ret;
}


int SaveListToFile()
{
	FILE *fp =NULL;
	int i, uid;
	
	if( (fp = fopen("mmm.txt", "w")) == NULL ) return -1;
	
	for( i = 0; i < name_list.ld_num; i++ )
	{
		fprintf(fp, "%6d  %s\n", name_list.ld_info[i].id, name_list.ld_info[i].name);
	}
	fprintf(fp, "\n");

	for( i = 0; i < name_list.da_num; i++ )
	{
		fprintf(fp, "%6d  %6d  %s\n", name_list.da_info[i].uid, name_list.da_info[i].id, name_list.da_info[i].name);
	}
	fprintf(fp, "\n");
	
	for( i = 0; i < name_list.ds_num; i++ )
	{
		fprintf(fp, "%6d  %6d  %s\n", name_list.ds_info[i].uid, name_list.ds_info[i].id, name_list.ds_info[i].name);
	}
	fprintf(fp, "\n");
	
	for( i = 0; i < name_list.dsm_num; i++ )
	{
		uid = name_list.dsm_info[i].uid;
		{
			fprintf(fp, "%6d  %6d  %6d  %s\n", name_list.ds_info[uid].uid, uid, name_list.dsm_info[i].id, name_list.dsm_info[i].name);
		}
	}
	
	fclose(fp);
	return 0;
}

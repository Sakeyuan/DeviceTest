
#pragma warning(disable:4786)

#include <string>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#include "interface.h"
#include "parse.h"

#ifdef __cplusplus  
extern "C" {
#endif   


// 双向链表添加结点（前插入）
void list_add_first (DBL_LNK **head, DBL_LNK *node)
{
	DBL_LNK *tail;
	
	if( node == NULL ) return;
	
	if( *head == NULL )
    {
		node->next = node;
		node->prev = node;
    }
	else
    {
		tail = (*head)->prev;
		node->next = *head;
		node->prev = tail;
		tail->next = node;
		(*head)->prev = node;
    }
	*head = node;
}

/*====================================================================================
接口函数：GetScdIedList  获取ICD、SCD文件中全部IED列表信息
======================================================================================
参数：
　　iedList			IED列表信息表
　　scdFilePath		SCD文件路径名
返回：
　　> 0	IED总数
======================================================================================*/
int GetScdIedList(IED_LIST *iedList, char *scdFilePath)
{
	IED_LIST *ied = iedList;
	int iedCount = 0;

	int ret = ParseSCD(NULL, scdFilePath);
	if( ret < 0 ) return ret;

	for( vector<CIED>::iterator it = CSCDIEDList.begin(); it < CSCDIEDList.end(); it++ )
	{
		CIED* pIED = &(*it);
		
		if (strstr(pIED->strAPName, "S1") == NULL) continue;	//忽略无S1节点的IED

		memset(ied, 0, sizeof(IED_LIST));

		ied->id = pIED->nId;
		strcpy(ied->name, pIED->strName);
//		strcpy(ied->desc, pIED->strDesc);
		strcpy(ied->desc, UTF_8Decode(pIED->strDesc).c_str());
		strcpy(ied->type, pIED->strType);
		strcpy(ied->configVersion, pIED->strCFGVersion);
		strcpy(ied->manufacturer, pIED->strManufacture);

		//填充A网B网IP地址及子网掩码
		int k=0;
		for (int i=0; i<CSCDNetConfigList.size(); i++)
		{
			CNetConfig* pNetConfig = &CSCDNetConfigList.at(i);
			if (strcmp(pNetConfig->chNetType, "MMS")) continue;

			k++;
			vector<CCommConfig>::iterator it_comm = CSCDCommConfigList.begin() + pNetConfig->nStart - 1;
			while( it_comm < CSCDCommConfigList.end() )
			{
				CCommConfig* pCommConfig = &(*it_comm);
				if (pCommConfig->nIdSubNet != pNetConfig->nId) break;

				if (!strcmp(pCommConfig->strIEDName, ied->name))
				{
					if (k==1)
					{
						strcpy(ied->strIPAddr1, pCommConfig->strIPAdder);
						strcpy(ied->strIPSubnet1, pCommConfig->strIP_Subnet);
					}
					else if (k==2)
					{
						strcpy(ied->strIPAddr2, pCommConfig->strIPAdder);
						strcpy(ied->strIPSubnet2, pCommConfig->strIP_Subnet);
					}

					break;
				}

				it_comm++;
			}
		}

		iedCount++;
		ied++;
	}

	return iedCount;
}

/*====================================================================================
接口函数：GetScdIedInfo  获取ICD、SCD文件中指定IED的配置信息
======================================================================================
参数：
　　iedName			IED名称。设为NULL则表示获取第一个IED的信息
　　iedInfo			IED配置信息，其结构SCL_INFO与仿真装置MMS服务模块中定义相同
　　scdFilePath		SCD文件路径名
返回：
　　0  成功，<0  错误码
======================================================================================*/
int GetScdIedInfo(char *iedName, SCL_INFO *iedInfo, char *scdFilePath)
{
	int ret;

	memset(iedInfo, 0, sizeof(SCL_INFO));

	if( iedName == NULL )
	{
		ret = ParseSCD("", scdFilePath);
	}
	else
	{
		ret = ParseSCD(iedName, scdFilePath);
	}
	if( ret < 0 ) return ret;

	CIED* pIED = &(*CSCDIEDList.begin());

	strcpy(iedInfo->iedName, pIED->strName);
	strcpy(iedInfo->Header.id, pIED->strType);
	iedInfo->Header.nameStructure = 0;

	// LDevice
	iedInfo->ldHead = NULL;
	vector<CLD>::iterator it_ld = CSCDLDList.begin() + pIED->nStart - 1;
	while( it_ld < CSCDLDList.end() )
	{
		CLD *pLD = &(*it_ld);
		if( pLD && pLD->nIdIED != pIED->nId ) break;

		if (strcmp(pLD->strAPName, "S1"))
		{
			it_ld++;
			continue;
		}

		SCL_LD *scl_ld = (SCL_LD *)calloc(1, sizeof(SCL_LD));
		strcpy(scl_ld->inst, pLD->strName);
		strcpy(scl_ld->domName, iedInfo->iedName);
		strcat(scl_ld->domName, pLD->strName);

		if( strlen(pLD->strDesc) > 0 )
		{
			scl_ld->desc = (ST_CHAR *)malloc(strlen(pLD->strDesc) + 1);
			strcpy(scl_ld->desc, pLD->strDesc);
		}
		
		// LN0, LN
		scl_ld->lnHead = NULL;
		vector<CLNinst>::iterator it_ln = CSCDLNinstList.begin() + pLD->nStart - 1;
		while( it_ln < CSCDLNinstList.end() )
		{
			CLNinst *pLNinst = &(*it_ln);
			if( pLNinst->nIdLD != pLD->nId ) break;

			SCL_LN *scl_ln = (SCL_LN *)calloc(1, sizeof(SCL_LN));
			strcpy(scl_ln->prefix, pLNinst->prefix);
			strcpy(scl_ln->inst, pLNinst->strInst);
			strcpy(scl_ln->lnClass, pLNinst->lnClass);
			strcpy(scl_ln->lnType, pLNinst->lnType);
			strcpy(scl_ln->varName, pLNinst->prefix);
			strcat(scl_ln->varName, pLNinst->lnClass);
			strcat(scl_ln->varName, pLNinst->strInst);

			if( strlen(pLNinst->strDesc) > 0 )
			{
				scl_ln->desc = (ST_CHAR *)malloc(strlen(pLNinst->strDesc) + 1);
				strcpy(scl_ln->desc, pLNinst->strDesc);
			}

			scl_ln->bHasSBCB = false;

			if( pLNinst->nType == 0 )
			{
				// DataSet
				scl_ln->datasetHead = NULL;
				vector<CDataSet>::iterator it_ds = CSCDDataSetList.begin() + pLNinst->nStart_LN0[0] - 1;
				while( it_ds < CSCDDataSetList.end() )
				{
					CDataSet *pDataSet = &(*it_ds);
					if( pDataSet->nIdLNinst != pLNinst->nId ) break;

					SCL_DATASET *scl_dataset = (SCL_DATASET *)calloc(1, sizeof(SCL_DATASET));
					strcpy(scl_dataset->name, pDataSet->strName);
					
					if( strlen(pDataSet->strDesc) > 0 )
					{
						scl_dataset->desc = (ST_CHAR *)malloc(strlen(pDataSet->strDesc) + 1);
						strcpy(scl_dataset->desc, pDataSet->strDesc);
					}
					
					// FCDA
					scl_dataset->fcdaHead = NULL;
					vector<CDsMember>::iterator it_dsm = CSCDDsMemberList.begin() + pDataSet->nStart - 1;
					while( it_dsm < CSCDDsMemberList.end() )
					{
						CDsMember *pDsMember = &(*it_dsm);
						if( pDsMember->nDsId != pDataSet->nId ) break;

						SCL_FCDA *scl_fcda = (SCL_FCDA *)calloc(1, sizeof(SCL_FCDA));
						strcpy(scl_fcda->ldInst, pDsMember->strLdInst);
						strcpy(scl_fcda->prefix, pDsMember->strPrefix);
						strcpy(scl_fcda->lnInst, pDsMember->strLnInst);
						strcpy(scl_fcda->lnClass, pDsMember->strLnClass);
						strcpy(scl_fcda->doName, pDsMember->strDoName);
						strcpy(scl_fcda->daName, pDsMember->strDaName);
						strcpy(scl_fcda->fc, pDsMember->strFC);
						strcpy(scl_fcda->domName, iedInfo->iedName);
						strcat(scl_fcda->domName, pDsMember->strLdInst);
						
						list_add_first((DBL_LNK **)(&scl_dataset->fcdaHead), (DBL_LNK *)scl_fcda);
						
						it_dsm++;
					}

					list_add_first((DBL_LNK **)(&scl_ln->datasetHead), (DBL_LNK *)scl_dataset);
					
					it_ds++;
				}

				// ReportControl
				scl_ln->rcbHead = NULL;
				vector<CRptCtrl>::iterator it_rpt = CSCDRptCtrlList.begin() + pLNinst->nStart_LN0[1] - 1;
				while( it_rpt < CSCDRptCtrlList.end() )
				{
					CRptCtrl *pRptCtrl = &(*it_rpt);
					if( pRptCtrl->nIdLNinst != pLNinst->nId ) break;

					SCL_RCB *scl_rcb = (SCL_RCB *)calloc(1, sizeof(SCL_RCB));
					strcpy(scl_rcb->name, pRptCtrl->strName);
					strcpy(scl_rcb->rptID, pRptCtrl->strRptID);
					strcpy(scl_rcb->datSet, CSCDDataSetList.at(pRptCtrl->nIdDS-1).strName);
					scl_rcb->intgPd = pRptCtrl->nIntgPd;
					scl_rcb->confRev = pRptCtrl->nConfRev;
					scl_rcb->bufTime= pRptCtrl->nBufTime;
					scl_rcb->buffered = pRptCtrl->isBuffered;
					scl_rcb->maxClient= pRptCtrl->nMax;
					scl_rcb->TrgOps[0] = pRptCtrl->bTrgOps << 3;
					scl_rcb->OptFlds[0] = pRptCtrl->bOptFields >> 1;
					scl_rcb->OptFlds[1] = (pRptCtrl->bOptFields & 0x01) << 6;

					if( strlen(pRptCtrl->strDesc) > 0 )
					{
						scl_rcb->desc = (ST_CHAR *)malloc(strlen(pRptCtrl->strDesc) + 1);
						strcpy(scl_rcb->desc, pRptCtrl->strDesc);
					}

					list_add_first((DBL_LNK **)(&scl_ln->rcbHead), (DBL_LNK *)scl_rcb);
					
					it_rpt++;
				}
  
				// GSEControl, SampledValueControl
				scl_ln->gcbHead = NULL;
				scl_ln->svcbHead = NULL;
				vector<CLLNO>::iterator it_gse = CSCDLLNOList.begin() + pLNinst->nStart_LN0[2] - 1;
				while( it_gse < CSCDLLNOList.end() )
				{
					CLLNO *pLLNO = &(*it_gse);
					if( pLLNO->nIdLNinst != pLNinst->nId ) break;

					if( pLLNO->nNumofSGs > 0) scl_ln->bHasSBCB = true;

					if( pLLNO->nType == 1 )
					{
						SCL_GCB *scl_gcb = (SCL_GCB *)calloc(1, sizeof(SCL_GCB));
						strcpy(scl_gcb->name, pLLNO->strName);
						strcpy(scl_gcb->appID, pLLNO->strAppID);
						strcpy(scl_gcb->datSet, CSCDDataSetList.at(pLLNO->nDsID-1).strName);
						scl_gcb->confRev = pLLNO->nConfRev;
						scl_gcb->isGoose = pLLNO->isGoose;

						if( strlen(pLLNO->strDesc) > 0 )
						{
							scl_gcb->desc = (ST_CHAR *)malloc(strlen(pLLNO->strDesc) + 1);
							strcpy(scl_gcb->desc, pLLNO->strDesc);
						}

						list_add_first((DBL_LNK **)(&scl_ln->gcbHead), (DBL_LNK *)scl_gcb);
					}
					else if( pLLNO->nType == 2 )
					{
						SCL_SVCB *scl_svcb = (SCL_SVCB *)calloc(1, sizeof(SCL_SVCB));
						strcpy(scl_svcb->name, pLLNO->strName);
						strcpy(scl_svcb->smvID, pLLNO->strAppID);
						strcpy(scl_svcb->datSet, CSCDDataSetList.at(pLLNO->nDsID-1).strName);
						scl_svcb->confRev = pLLNO->nConfRev;
						scl_svcb->smpRate = pLLNO->nSmpRate;
						scl_svcb->nofASDU = pLLNO->nNofASDU;
						scl_svcb->multicast = pLLNO->isMulticast;
						scl_svcb->securityPres = (pLLNO->bSmvOpts >> 1) & 0x01;
						scl_svcb->dataRefPres = pLLNO->bSmvOpts & 0x01;
						scl_svcb->OptFlds[0] = pLLNO->bSmvOpts >> 2 << 4;
						
						if( strlen(pLLNO->strDesc) > 0 )
						{
							scl_svcb->desc = (ST_CHAR *)malloc(strlen(pLLNO->strDesc) + 1);
							strcpy(scl_svcb->desc, pLLNO->strDesc);
						}
						
						list_add_first((DBL_LNK **)(&scl_ln->svcbHead), (DBL_LNK *)scl_svcb);
					}
					
					it_gse++;
				}
			}

			// DOI, SDI, DAI
			scl_ln->daiHead = NULL;
			scl_ln->rwHead = NULL;
			vector<CDOI>::iterator it = CSCDDOIList.begin() + pLNinst->nStart - 1;
			while( it < CSCDDOIList.end() )
			{
				CDOI *pDOI = &(*it);
				if( pDOI->nIdLNinst != pLNinst->nId ) break;

				bool existDAI = false;

				vector<CDAI>::iterator it_dai = CSCDDAIList.begin() + pDOI->nStart - 1;
				while( it_dai < CSCDDAIList.end() )
				{
					CDAI *pDAI = &(*it_dai);
					if( pDAI->nIdDOI != pDOI->nId ) break;

					existDAI = true;

					SCL_DAI *scl_dai = (SCL_DAI *)calloc(1, sizeof(SCL_DAI));
					strcpy(scl_dai->flattened, pDOI->strName);
					strcat(scl_dai->flattened, "$");
					strcat(scl_dai->flattened, pDAI->daiName);

					strcpy(scl_dai->sAddr, pDAI->strSaddr);

					if( strlen(pDAI->valKind) > 0 )
						strcpy(scl_dai->valKind, pDAI->valKind);
					else
						strcpy(scl_dai->valKind, "Set");

					if( strlen(pDAI->val) > 0 )
					{
						scl_dai->Val = (ST_CHAR *)malloc(strlen(pDAI->val) + 1);
						strcpy(scl_dai->Val, pDAI->val);
					}
				
					list_add_first((DBL_LNK **)(&scl_ln->daiHead), (DBL_LNK *)scl_dai);
/*				
					if( strlen(pDAI->strSaddr) > 0 )
					{
						SCL_rwFun *scl_rwfun = (SCL_rwFun *)calloc(1, sizeof(SCL_rwFun));
						strcpy(scl_rwfun->doRef, pDOI->strName);
						strcat(scl_rwfun->doRef, "$");

						if( strchr(pDAI->daiName, '$') == NULL )
						{
							strcat(scl_rwfun->doRef, pDAI->daiName);
						}
						else
						{
							char tempstr[MAX_IDENT_LEN] = {0};
							strncpy(tempstr, pDAI->daiName, strchr(pDAI->daiName, '$') - pDAI->daiName + 1);
							strcat(scl_rwfun->doRef, tempstr);
						}

						strcat(scl_rwfun->doRef, "|");
						strcat(scl_rwfun->doRef, pDAI->strSaddr);

						list_add_first((DBL_LNK **)(&scl_ln->rwHead), (DBL_LNK *)scl_rwfun);
					}
*/
					it_dai++;
				}

				if( !existDAI )
				{
					SCL_DAI *scl_dai = (SCL_DAI *)calloc(1, sizeof(SCL_DAI));
					strcpy(scl_dai->flattened, pDOI->strName);
					strcat(scl_dai->flattened, "$dU");
					
					strcpy(scl_dai->valKind, "Set");
										
					list_add_first((DBL_LNK **)(&scl_ln->daiHead), (DBL_LNK *)scl_dai);
				}

				it++;
			}

			list_add_first((DBL_LNK **)(&scl_ld->lnHead), (DBL_LNK *)scl_ln);
			
			it_ln++;
		}

		list_add_first((DBL_LNK **)(&iedInfo->ldHead), (DBL_LNK *)scl_ld);
		
		it_ld++;
	}

	// LNodeType
	iedInfo->lnTypeHead = NULL;
	for( vector<CLnType>::iterator it_ln = CSCDLnTypeList.begin(); it_ln < CSCDLnTypeList.end(); it_ln++ )
	{
		CLnType *pLnType = &(*it_ln);
		if (!pLnType->used) continue;
		
		SCL_LNTYPE *scl_lnType = (SCL_LNTYPE *)calloc(1, sizeof(SCL_LNTYPE));
		strcpy(scl_lnType->id, pLnType->strType);
		strcpy(scl_lnType->lnClass, pLnType->strLnclass);
		
		// DO
		scl_lnType->doHead = NULL;
		vector<CLnMember>::iterator it = CSCDLnMemberList.begin() + pLnType->nStart - 1;
		while( it < CSCDLnMemberList.end() )
		{
			CLnMember *pLnMember = &(*it);
			if( pLnMember->nLnType_id != pLnType->nId ) break;

			SCL_DO *scl_do = (SCL_DO *)calloc(1, sizeof(SCL_DO));
			strcpy(scl_do->name, pLnMember->strDoName);
			strcpy(scl_do->type, pLnMember->strType);
			
			list_add_first((DBL_LNK **)(&scl_lnType->doHead), (DBL_LNK *)scl_do);
			
			it++;
		}
		
		list_add_first((DBL_LNK **)(&iedInfo->lnTypeHead), (DBL_LNK *)scl_lnType);
	}

	// DOType
	iedInfo->doTypeHead = NULL;
	for( vector<CDoType>::iterator it_do = CSCDDoTypeList.begin(); it_do < CSCDDoTypeList.end(); it_do++ )
	{
		CDoType *pDoType = &(*it_do);
		if (!pDoType->used) continue;
		
		SCL_DOTYPE *scl_doType = (SCL_DOTYPE *)calloc(1, sizeof(SCL_DOTYPE));
		strcpy(scl_doType->id, pDoType->strType);
		strcpy(scl_doType->cdc, pDoType->strCDCName);
		
		// DA, SDO
		scl_doType->daHead = NULL;
		vector<CDoMember>::iterator it = CSCDDoMemberList.begin() + pDoType->nStart - 1;
		while( it < CSCDDoMemberList.end() )
		{
			CDoMember *pDoMember = &(*it);
			if( pDoMember->nDotype_id != pDoType->nId ) break;

			SCL_DA *scl_da = (SCL_DA *)calloc(1, sizeof(SCL_DA));
			strcpy(scl_da->name, pDoMember->strDaName);
			strcpy(scl_da->bType, pDoMember->strBType);
			strcpy(scl_da->type, pDoMember->strType);
			strcpy(scl_da->fc, pDoMember->strFC);
			scl_da->dchg = pDoMember->bDchg;
			scl_da->qchg = pDoMember->bQchg;
			scl_da->dupd = pDoMember->bDupd;
			scl_da->objtype = pDoMember->nKind;
			
			list_add_first((DBL_LNK **)(&scl_doType->daHead), (DBL_LNK *)scl_da);
			
			it++;
		}
		
		list_add_first((DBL_LNK **)(&iedInfo->doTypeHead), (DBL_LNK *)scl_doType);
	}
	
	// DAType
	iedInfo->daTypeHead = NULL;
	for( vector<CDaType>::iterator it_da = CSCDDaTypeList.begin(); it_da < CSCDDaTypeList.end(); it_da++ )
	{
		CDaType *pDaType = &(*it_da);
		if (!pDaType->used) continue;
		
		SCL_DATYPE *scl_daType = (SCL_DATYPE *)calloc(1, sizeof(SCL_DATYPE));
		strcpy(scl_daType->id, pDaType->strName);
		
		scl_daType->bdaHead =NULL;
		vector<CDaMember>::iterator it = CSCDDaMemberList.begin() + pDaType->nStart - 1;
		while( it < CSCDDaMemberList.end() )
		{
			CDaMember *pDaMember = &(*it);
			if( pDaMember->nDaType_id != pDaType->nId ) break;

			SCL_BDA *scl_bda = (SCL_BDA *)calloc(1, sizeof(SCL_BDA));
			strcpy(scl_bda->name, pDaMember->strName);
			strcpy(scl_bda->bType, pDaMember->strBType);
			strcpy(scl_bda->type, pDaMember->strType);
			
			list_add_first((DBL_LNK **)(&scl_daType->bdaHead), (DBL_LNK *)scl_bda);
			
			it++;
		}
		
		list_add_first((DBL_LNK **)(&iedInfo->daTypeHead), (DBL_LNK *)scl_daType);
	}
	
	// EnumType
	iedInfo->enumTypeHead = NULL;
	for( vector<CEnumType>::iterator it_enum = CSCDEnumTypeList.begin(); it_enum < CSCDEnumTypeList.end(); it_enum++ )
	{
		CEnumType *pEnumType = &(*it_enum);
		if (!pEnumType->used) continue;
		
		SCL_ENUMTYPE *scl_enumType = (SCL_ENUMTYPE *)calloc(1, sizeof(SCL_ENUMTYPE));
		strcpy(scl_enumType->id, pEnumType->strName);
		
		// EnumVal
		scl_enumType->enumvalHead = NULL;
		vector<CEnumMember>::iterator it = CSCDEnumMemberList.begin() + pEnumType->nStart - 1;
		while( it < CSCDEnumMemberList.end() )
		{
			CEnumMember *pEnumMember = &(*it);
			if( pEnumMember->nEnumType_id != pEnumType->nId ) break;

			SCL_ENUMVAL *scl_enumVal = (SCL_ENUMVAL *)calloc(1, sizeof(SCL_ENUMVAL));
			strcpy(scl_enumVal->EnumVal, pEnumMember->strName);
			scl_enumVal->ord = pEnumMember->nValue;
			
			list_add_first((DBL_LNK **)(&scl_enumType->enumvalHead), (DBL_LNK *)scl_enumVal);

			it++;
		}
		
		list_add_first((DBL_LNK **)(&iedInfo->enumTypeHead), (DBL_LNK *)scl_enumType);
	}
	
	iedInfo->subnetHead = NULL;
	iedInfo->brcb_bufsize = BRCB_BUF_SIZE;
	iedInfo->ld_create_done = false;
	iedInfo->datatype_create_done = false;

	return 0;
}

/*====================================================================================
接口函数：GetScd61850Info  获取ICD、SCD文件中指定IED的61850对象信息
======================================================================================
参数：
　　iedName			IED名称。设为NULL则表示获取第一个IED的信息
　　all61850Info	61850对象信息
　　scdFilePath		SCD文件路径名
返回：
　　0  成功，<0  错误码
======================================================================================*/
int GetScd61850Info(char *iedName, ALL_61850_INFO *all61850Info, char *scdFilePath)
{
	int i, j, ret;

	if( iedName == NULL )
	{
		ret = ParseSCD("", scdFilePath);
	}
	else
	{
		ret = ParseSCD(iedName, scdFilePath);
	}
	if( ret < 0 ) return ret;
	
	// IED List
	all61850Info->ied_num = CSCDIEDList.size();
	all61850Info->ied_list = (IED_LIST *)calloc(all61850Info->ied_num, sizeof(IED_LIST));

	IED_LIST *ied_list = all61850Info->ied_list;

	for (i=0; i<CSCDIEDList.size(); i++)
	{
		CIED* pIED = &CSCDIEDList.at(i);
		
		ied_list->id = pIED->nId;
		strcpy(ied_list->name, pIED->strName);
		strcpy(ied_list->desc, pIED->strDesc);
		strcpy(ied_list->type, pIED->strType);
		strcpy(ied_list->configVersion, pIED->strCFGVersion);
		strcpy(ied_list->manufacturer, pIED->strManufacture);

		ied_list++;
	}
/*
FILE *fp;
if( iedName == NULL )
{
	fp = fopen("doi.txt", "w");
}
else
{
	char fname[100];
	strcpy(fname, iedName);
	strcat(fname, ".txt");
	fp = fopen(fname, "w");
}
*/
	// 遥信、遥测、遥控、定值、事件
	int yx_num = 0;
	int yc_num = 0;
	int yk_num = 0;
	int dz_num = 0;
	int sj_num = 0;

	for (vector<CDOI>::iterator it = CSCDDOIList.begin(); it < CSCDDOIList.end(); it++)
	{
		CDOI *pDOI = &(*it);
//fprintf(fp, "DOI: %d  %d  %d  %s  %s %d\n", pDOI->nId, pDOI->nIdLNinst, pDOI->doiType, pDOI->strName, pDOI->strDesc, pDOI->doiType);
		if (strcmp(CSCDLDList.at(pDOI->nIdLD-1).strAPName, "S1")) continue;
		if (!strcmp(pDOI->str_dU, "")) continue;

		if (pDOI->doiType & (1<<12) || pDOI->doiType & (1<<13))		//定值
		{
			if (pDOI->nDsMember <= 0) continue;		//过滤掉未关联数据集成员的对象
			//if (!strcmp(CSCDDsMemberList.at(pDOI->nDsMember-1).strFC, "SP")) continue;	//暂过滤掉SP
		}

		if (pDOI->doiType == 0 //|| !strcmp(pDOI->strDesc, "") //2016.6.13.
			|| !strcmp(pDOI->strName, "Beh")
			|| !strcmp(pDOI->strName, "Health")
			|| !strcmp(pDOI->strName, "PhyHealth")
			|| !strcmp(pDOI->strName, "Mod")
			|| !strcmp(pDOI->strName, "NamPlt")
			|| !strcmp(pDOI->strName, "PhyName")
			|| !strcmp(pDOI->strName, "PhyNam")
			|| !strcmp(pDOI->strName, "Proxy")
			//|| !strcmp(pDOI->strName, "LEDRs")
			) continue;

		if (pDOI->doiType & 1) yx_num++;
		if (pDOI->doiType & 2) sj_num++;
		if (pDOI->doiType & (1<<4) || pDOI->doiType & (1<<5) || pDOI->doiType & (1<<6)) yc_num++;
		if (pDOI->doiType & (1<<8) || pDOI->doiType & (1<<9)) yk_num++;
		if (pDOI->doiType & (1<<12) || pDOI->doiType & (1<<13)) dz_num++;
		if (pDOI->doiType & (1<<7))
		{
			vector<CDAI>::iterator it_dai = CSCDDAIList.begin() + pDOI->nStart - 1;
			while( it_dai < CSCDDAIList.end() )
			{
				CDAI *pDAI = &(*it_dai);
				if (pDAI->nIdDOI != pDOI->nId) break;
//fprintf(fp, "  DAI: %d  %d  %s  %s  %s\n", pDAI->nId, pDAI->nIdDOI, pDAI->daiName, pDAI->valKind, pDAI->val);
			
				if (strstr(pDAI->daiName, "$cVal$mag$f")) yc_num++;
				it_dai++;
			}
		}
	}
//fclose(fp);

	all61850Info->yx_info = (YX_INFO *)calloc(yx_num, sizeof(YX_INFO));
	all61850Info->yc_info = (YC_INFO *)calloc(yc_num, sizeof(YC_INFO));
	all61850Info->yk_info = (YK_INFO *)calloc(yk_num, sizeof(YK_INFO));
	all61850Info->dz_info = (DZ_INFO *)calloc(dz_num, sizeof(DZ_INFO));
	all61850Info->sj_info = (SJ_INFO *)calloc(sj_num, sizeof(SJ_INFO));
	all61850Info->dzq_info = (DZ_INFO *)calloc(all61850Info->ied_num, sizeof(DZ_INFO));
	
	YX_INFO *yx_info = all61850Info->yx_info;
	YC_INFO *yc_info = all61850Info->yc_info;
	YK_INFO *yk_info = all61850Info->yk_info;
	DZ_INFO *dz_info = all61850Info->dz_info;
	SJ_INFO *sj_info = all61850Info->sj_info;
	
	all61850Info->yk_num = 0;
	all61850Info->yc_num = 0;
	all61850Info->yx_num = 0;
	all61850Info->dz_num = 0;
	all61850Info->sj_num = 0;

	char tempPath0[200];
	char tempPath[200];
	char tempName[100];

	for (vector<CLLNO>::iterator it1 = CSCDLLNOList.begin(); it1 < CSCDLLNOList.end(); it1++)
	{
		CLLNO *pLLNO = &(*it1);
		if (pLLNO->nNumofSGs < 0) continue;

		strcpy(tempPath, CSCDIEDList.at(pLLNO->nIdIED-1).strName);
		strcat(tempPath, CSCDLDList.at(pLLNO->nIdLD-1).strName);
		strcat(tempPath, "/");
		
		strcat(tempPath, CSCDLNinstList.at(pLLNO->nIdLNinst-1).prefix);
		strcat(tempPath, CSCDLNinstList.at(pLLNO->nIdLNinst-1).lnClass);
		strcat(tempPath, CSCDLNinstList.at(pLLNO->nIdLNinst-1).strInst);
		strcat(tempPath, "$SP$SGCB");

		DZ_INFO *dzq_info = all61850Info->dzq_info + pLLNO->nIdIED - 1;
		strcpy(dzq_info->strMmsVarName, tempPath);
		dzq_info->nID = pLLNO->nNumofSGs;
		dzq_info->nIED = pLLNO->nIdIED;
		dzq_info->nType = pLLNO->nActSG;
	}

	for (vector<CDOI>::iterator it = CSCDDOIList.begin(); it < CSCDDOIList.end(); it++)
	{
		CDOI *pDOI = &(*it);
		if (strcmp(CSCDLDList.at(pDOI->nIdLD-1).strAPName, "S1")) continue;
		if (!strcmp(pDOI->str_dU, "")) continue;
		
		if (pDOI->doiType & (1<<12) || pDOI->doiType & (1<<13))		//定值
		{
			if (pDOI->nDsMember <= 0) continue;		//过滤掉未关联数据集成员的对象
			//if (!strcmp(CSCDDsMemberList.at(pDOI->nDsMember-1).strFC, "SP")) continue;	//暂过滤掉SP
		}

		if (pDOI->doiType == 0 //|| !strcmp(pDOI->strDesc, "") //2016.6.13.
			|| !strcmp(pDOI->strName, "Beh")
			|| !strcmp(pDOI->strName, "Health")
			|| !strcmp(pDOI->strName, "PhyHealth")
			|| !strcmp(pDOI->strName, "Mod")
			|| !strcmp(pDOI->strName, "NamPlt")
			|| !strcmp(pDOI->strName, "PhyName")
			|| !strcmp(pDOI->strName, "PhyNam")
			|| !strcmp(pDOI->strName, "Proxy")
			//|| !strcmp(pDOI->strName, "LEDRs")
			) continue;


		// 拼接引用串
		strcpy(tempPath0, CSCDIEDList.at(pDOI->nIdIED-1).strName);
//		strcat(tempPath0, "/");		//2015.6.8. 
		strcat(tempPath0, CSCDLDList.at(pDOI->nIdLD-1).strName);
		strcat(tempPath0, "/");

		strcat(tempPath0, CSCDLNinstList.at(pDOI->nIdLNinst-1).prefix);
		strcat(tempPath0, CSCDLNinstList.at(pDOI->nIdLNinst-1).lnClass);
		strcat(tempPath0, CSCDLNinstList.at(pDOI->nIdLNinst-1).strInst);

		if (pDOI->doiType & 1)	//遥信
		{
			strcpy(tempPath, tempPath0);
			strcat(tempPath, "$ST$");
			strcat(tempPath, pDOI->strName);
			strcat(tempPath, "$stVal");
			
			strcpy(yx_info->strMmsVarName, tempPath);
			//strcpy(yx_info->strName, pDOI->str_dU);
			strcpy(yx_info->strName, UTF_8Decode(pDOI->str_dU).c_str());
			yx_info->nDataType = pDOI->nDataType;
			yx_info->nIED = pDOI->nIdIED;

			if (pDOI->nDataType == ENUM_TYPE_CODEENUM)
				yx_info->nType = 2;
			else if (pDOI->nDataType == ENUM_TYPE_INT)
				yx_info->nType = 3;
			else if (pDOI->nDataType == ENUM_TYPE_FLOAT)
				yx_info->nType = 4;
			else
				yx_info->nType = 1;

			if (pDOI->nDsMember > 0)
			{
				strcpy(yx_info->strDataSetName, CSCDDataSetList.at(CSCDDsMemberList.at(pDOI->nDsMember-1).nDsId-1).strName);
			}
			
			yx_info++;
			all61850Info->yx_num++;
		}

		if (pDOI->doiType & 2)	//事件
		{
			strcpy(tempPath, tempPath0);
			strcat(tempPath, "$ST$");
			strcat(tempPath,  pDOI->strName);
			strcat(tempPath, "$general");
			
			strcpy(sj_info->strMmsVarName, tempPath);
			//strcpy(sj_info->strName, pDOI->str_dU);
			strcpy(sj_info->strName, UTF_8Decode(pDOI->str_dU).c_str());
			sj_info->nDataType = pDOI->nDataType;
			sj_info->nIED = pDOI->nIdIED;

			if (pDOI->nDsMember > 0)
			{
				strcpy(sj_info->strDataSetName, CSCDDataSetList.at(CSCDDsMemberList.at(pDOI->nDsMember-1).nDsId-1).strName);
			}
			
			sj_info++;
			all61850Info->sj_num++;
		}

		if (pDOI->doiType & (1<<4) || pDOI->doiType & (1<<5) || pDOI->doiType & (1<<6))	//遥测
		{
			strcpy(tempPath, tempPath0);
			strcat(tempPath, "$MX$");
			strcat(tempPath, pDOI->strName);

			yc_info->nType = 0;
			if (pDOI->doiType & (1<<4))
			{
				strcat(tempPath, "$mag$f");
			}
			else if (pDOI->doiType & (1<<5))
			{
				strcat(tempPath, "$cVal$mag$f");
				yc_info->nType = 1;
			}
			else if (pDOI->doiType & (1<<6))
			{
				strcat(tempPath, "$instMag$i");
			}

			strcpy(yc_info->strMmsVarName, tempPath);
			//strcpy(yc_info->strName, pDOI->str_dU);
			strcpy(yc_info->strName, UTF_8Decode(pDOI->str_dU).c_str());
			yc_info->nDataType = pDOI->nDataType;
			yc_info->nIED = pDOI->nIdIED;

			if (pDOI->nDsMember > 0)
			{
				strcpy(yc_info->strDataSetName, CSCDDataSetList.at(CSCDDsMemberList.at(pDOI->nDsMember-1).nDsId-1).strName);
			}
			
			yc_info++;
			all61850Info->yc_num++;
		}

		if (pDOI->doiType & (1<<8) || pDOI->doiType & (1<<9))	//遥控
		{
			strcpy(tempPath, tempPath0);
			strcat(tempPath, "$CO$");
			strcat(tempPath, pDOI->strName);
			if (pDOI->doiType & (1<<8)) strcat(tempPath, "$SBOw$ctlVal");
			else
			if (pDOI->doiType & (1<<9)) strcat(tempPath, "$Oper$ctlVal");
			
			strcpy(yk_info->strMmsVarName, tempPath);
			//strcpy(yk_info->strName, pDOI->str_dU);
			strcpy(yk_info->strName, UTF_8Decode(pDOI->str_dU).c_str());

			if (!strcmp(pDOI->str_ctlModel, "direct-with-normal-security") || !strcmp(pDOI->str_ctlModel, "1"))
				yk_info->nCtlModel = 1;
			else if (!strcmp(pDOI->str_ctlModel, "sbo-with-normal-security") || !strcmp(pDOI->str_ctlModel, "2"))
				yk_info->nCtlModel = 2;
			else if (!strcmp(pDOI->str_ctlModel, "direct-with-enhanced-security") || !strcmp(pDOI->str_ctlModel, "3"))
				yk_info->nCtlModel = 3;
			else if (!strcmp(pDOI->str_ctlModel, "sbo-with-enhanced-security") || !strcmp(pDOI->str_ctlModel, "4"))
				yk_info->nCtlModel = 4;
			else
				yk_info->nCtlModel = 0;

			yk_info->nIED = pDOI->nIdIED;
			
			yk_info++;
			all61850Info->yk_num++;
		}

		if (pDOI->doiType & (1<<12) || pDOI->doiType & (1<<13))	//定值
		{
			strcpy(tempPath, tempPath0);
			if (pDOI->nDsMember>0 && !strcmp(CSCDDsMemberList.at(pDOI->nDsMember-1).strFC, "SP"))
				strcat(tempPath, "$SP$");
			else
				strcat(tempPath, "$SG$");
			strcat(tempPath, pDOI->strName);
			if (pDOI->doiType & (1<<12)) strcat(tempPath, "$setVal");
			else
			if (pDOI->doiType & (1<<13)) strcat(tempPath, "$setMag$f");
				
			strcpy(dz_info->strMmsVarName, tempPath);
			//strcpy(dz_info->strName, pDOI->str_dU);
			strcpy(dz_info->strName, UTF_8Decode(pDOI->str_dU).c_str());
			dz_info->nDataType = pDOI->nDataType;
			dz_info->nIED = pDOI->nIdIED;

			if (pDOI->nDataType == ENUM_TYPE_BOOLEAN)
				dz_info->nType = 1;
			else if (pDOI->nDataType == ENUM_TYPE_INT)
				dz_info->nType = 2;
			else if (pDOI->nDataType == ENUM_TYPE_FLOAT)
				dz_info->nType = 3;
			else if (pDOI->nDataType == ENUM_TYPE_VISIBLESTRING)
				dz_info->nType = 4;
			else
				dz_info->nType = 0;

			if (pDOI->nDsMember > 0)
			{
				strcpy(dz_info->strDataSetName, CSCDDataSetList.at(CSCDDsMemberList.at(pDOI->nDsMember-1).nDsId-1).strName);
			}
			
			dz_info++;
			all61850Info->dz_num++;
		}

		if (pDOI->doiType & (1<<7))	//遥测（包含多点）
		{
			vector<CDAI>::iterator it_dai = CSCDDAIList.begin() + pDOI->nStart - 1;
			while( it_dai < CSCDDAIList.end() )
			{
				CDAI *pDAI = &(*it_dai);
				if (pDAI->nIdDOI != pDOI->nId) break;
				
				if (strstr(pDAI->daiName, "$cVal$mag$f"))
				{
					strcpy(tempPath, tempPath0);
					strcat(tempPath, "$MX$");
					strcat(tempPath, pDOI->strName);
					strcat(tempPath, "$");
					strcat(tempPath, pDAI->daiName);

					strcpy(yc_info->strMmsVarName, tempPath);

					strcpy(tempName, pDAI->daiName);
					strcpy(strstr(tempName, "$cVal$mag$f"), "\0");
					strcat(tempName, "$dU");
					vector<CDAI>::iterator it_dai_1 = CSCDDAIList.begin() + pDOI->nStart - 1;
					while( it_dai_1 < CSCDDAIList.end() )
					{
						CDAI *pDAI_1 = &(*it_dai_1);
						if (pDAI_1->nIdDOI != pDOI->nId) break;
						
						if (!strcmp(pDAI_1->daiName, tempName))
							//strcpy(yc_info->strName, pDAI_1->val);
							strcpy(yc_info->strName, UTF_8Decode(pDAI_1->val).c_str());
							
						it_dai_1++;
					}
					
					yc_info->nDataType = ENUM_TYPE_FLOAT;
					yc_info->nIED = pDOI->nIdIED;
					yc_info->nType = 1;

					if (pDAI->nDsMember > 0)
					{
						strcpy(yc_info->strDataSetName, CSCDDataSetList.at(CSCDDsMemberList.at(pDAI->nDsMember-1).nDsId-1).strName);
					}
				
					if (strcmp(yc_info->strName, ""))
					{
						yc_info++;
						all61850Info->yc_num++;
					}
				}

				it_dai++;
			}
		}

	}

	// 设置nChannel字段
	j = -1;
	for( i=0; i<all61850Info->yc_num; i++ )
	{
		if( all61850Info->yc_info[i].nIED != j )
		{
			j = all61850Info->yc_info[i].nIED;
			all61850Info->yc_info[i].nChannel = 1;
		}
		else
		{
			all61850Info->yc_info[i].nChannel = all61850Info->yc_info[i-1].nChannel + 1;
		}
	}
	
	j = -1;
	for( i=0; i<all61850Info->yx_num; i++ )
	{
		if( all61850Info->yx_info[i].nIED != j )
		{
			j = all61850Info->yx_info[i].nIED;
			all61850Info->yx_info[i].nChannel = 1;
		}
		else
		{
			all61850Info->yx_info[i].nChannel = all61850Info->yx_info[i-1].nChannel + 1;
		}
	}
	
	j = -1;
	for( i=0; i<all61850Info->yk_num; i++ )
	{
		if( all61850Info->yk_info[i].nIED != j )
		{
			j = all61850Info->yk_info[i].nIED;
			all61850Info->yk_info[i].nChannel = 1;
		}
		else
		{
			all61850Info->yk_info[i].nChannel = all61850Info->yk_info[i-1].nChannel + 1;
		}
	}
	
	j = -1;
	for( i=0; i<all61850Info->dz_num; i++ )
	{
		if( all61850Info->dz_info[i].nIED != j )
		{
			j = all61850Info->dz_info[i].nIED;
			all61850Info->dz_info[i].nID = 1;
		}
		else
		{
			all61850Info->dz_info[i].nID = all61850Info->dz_info[i-1].nID + 1;
		}
	}
	
	j = -1;
	for( i=0; i<all61850Info->sj_num; i++ )
	{
		if( all61850Info->sj_info[i].nIED != j )
		{
			j = all61850Info->sj_info[i].nIED;
			all61850Info->sj_info[i].nChannel = 1;
		}
		else
		{
			all61850Info->sj_info[i].nChannel = all61850Info->sj_info[i-1].nChannel + 1;
		}
	}

	return 0;	
}

/*====================================================================================
接口函数：SaveScdIedInfo  解析ICD、SCD文件将指定IED的配置信息存为文件
======================================================================================
参数：
　　iedName			IED名称。设为NULL则表示获取第一个IED的信息
　　scdFilePath		SCD文件路径名
　　saveFilePath	解析文件保存路径名
返回：
　　0  成功，<0  错误码
======================================================================================*/
int SaveScdIedInfo(char *iedName, char *scdFilePath, char *saveFilePath)
{
	SCL_INFO scl_Info;
	char buf[MAX_DESC_LEN+1]; 

	int ret = GetScdIedInfo(iedName, &scl_Info, scdFilePath);
	if (ret != 0) return ret;

//	string fname = UTF_8Decode(saveFilePath);
//	FILE* fp = fopen(fname.c_str(), "wb");
	FILE* fp = fopen(saveFilePath, "wb");
	if (fp == NULL) return -6;

	fwrite(&scl_Info, sizeof(SCL_INFO), 1, fp);

	SCL_LNTYPE* scl_lnType = scl_Info.lnTypeHead;
	while (scl_lnType != NULL)
	{
		fputc(1, fp);
		fwrite(scl_lnType, sizeof(SCL_LNTYPE), 1, fp);

		SCL_DO* scl_do = scl_lnType->doHead;
		while (scl_do != NULL)
		{
			fputc(2, fp);
			fwrite(scl_do, sizeof(SCL_DO), 1, fp);
			
			scl_do = (SCL_DO *)scl_do->next;
			if (scl_do == scl_lnType->doHead) break;
		}

		scl_lnType = (SCL_LNTYPE *)scl_lnType->next;
		if (scl_lnType == scl_Info.lnTypeHead) break;
	}
	
	SCL_DOTYPE* scl_doType = scl_Info.doTypeHead;
	while (scl_doType != NULL)
	{
		fputc(3, fp);
		fwrite(scl_doType, sizeof(SCL_DOTYPE), 1, fp);
		
		SCL_DA *scl_da = scl_doType->daHead;
		while (scl_da != NULL)
		{
			fputc(4, fp);
			fwrite(scl_da, sizeof(SCL_DA), 1, fp);
			
			scl_da = (SCL_DA *)scl_da->l.next;
			if (scl_da == scl_doType->daHead) break;
		}
		
		scl_doType = (SCL_DOTYPE *)scl_doType->next;
		if (scl_doType == scl_Info.doTypeHead) break;
	}

	SCL_DATYPE* scl_daType = scl_Info.daTypeHead;
	while (scl_daType != NULL)
	{
		fputc(5, fp);
		fwrite(scl_daType, sizeof(SCL_DATYPE), 1, fp);
		
		SCL_BDA* scl_bda = scl_daType->bdaHead;
		while (scl_bda != NULL)
		{
			fputc(6, fp);
			fwrite(scl_bda, sizeof(SCL_BDA), 1, fp);
			
			scl_bda = (SCL_BDA *)scl_bda->l.next;
			if (scl_bda == scl_daType->bdaHead) break;
		}
		
		scl_daType = (SCL_DATYPE *)scl_daType->l.next;
		if (scl_daType == scl_Info.daTypeHead) break;
	}

	SCL_ENUMTYPE* scl_enumType = scl_Info.enumTypeHead;
	while (scl_enumType != NULL)
	{
		fputc(7, fp);
		fwrite(scl_enumType, sizeof(SCL_ENUMTYPE), 1, fp);
		
		SCL_ENUMVAL* scl_enumVal = scl_enumType->enumvalHead;
		while (scl_enumVal != NULL)
		{
			fputc(8, fp);
			fwrite(scl_enumVal, sizeof(SCL_ENUMVAL), 1, fp);
			
			scl_enumVal = (SCL_ENUMVAL *)scl_enumVal->l.next;
			if (scl_enumVal == scl_enumType->enumvalHead) break;
		}
		
		scl_enumType = (SCL_ENUMTYPE *)scl_enumType->l.next;
		if (scl_enumType == scl_Info.enumTypeHead) break;
	}

	SCL_LD* scl_ld = scl_Info.ldHead;
	while (scl_ld != NULL)
	{
		fputc(10, fp);
		fwrite(scl_ld, sizeof(SCL_LD), 1, fp);

		if (scl_ld->desc != NULL)
		{
			memset(buf, 0, MAX_DESC_LEN+1);
			strcpy(buf, scl_ld->desc);
			fputc(20, fp);
			fwrite(buf, MAX_DESC_LEN+1, 1, fp);
		}

		SCL_LN* scl_ln = scl_ld->lnHead;
		while (scl_ln != NULL)
		{
			fputc(11, fp);
			fwrite(scl_ln, sizeof(SCL_LN), 1, fp);
		
			if (scl_ln->desc != NULL)
			{
				memset(buf, 0, MAX_DESC_LEN+1);
				strcpy(buf, scl_ln->desc);
				fputc(21, fp);
				fwrite(buf, MAX_DESC_LEN+1, 1, fp);
			}

			SCL_DAI* scl_dai = scl_ln->daiHead;
			while (scl_dai != NULL)
			{
				fputc(12, fp);
				fwrite(scl_dai, sizeof(SCL_DAI), 1, fp);

				if (scl_dai->Val != NULL)
				{
					memset(buf, 0, MAX_DESC_LEN+1);
					strcpy(buf, scl_dai->Val);
					fputc(22, fp);
					fwrite(buf, MAX_DESC_LEN+1, 1, fp);
				}
				
				scl_dai = (SCL_DAI *)scl_dai->l.next;
				if (scl_dai == scl_ln->daiHead) break;
			}

			SCL_DATASET* scl_dataSet = scl_ln->datasetHead;
			while (scl_dataSet != NULL)
			{
				fputc(13, fp);
				fwrite(scl_dataSet, sizeof(SCL_DATASET), 1, fp);
				
				if (scl_dataSet->desc != NULL)
				{
					memset(buf, 0, MAX_DESC_LEN+1);
					strcpy(buf, scl_dataSet->desc);
					fputc(23, fp);
					fwrite(buf, MAX_DESC_LEN+1, 1, fp);
				}
				
				SCL_FCDA* scl_fcda = scl_dataSet->fcdaHead;
				while (scl_fcda != NULL)
				{
					fputc(33, fp);
					fwrite(scl_fcda, sizeof(SCL_FCDA), 1, fp);
					
					scl_fcda = (SCL_FCDA *)scl_fcda->l.next;
					if (scl_fcda == scl_dataSet->fcdaHead) break;
				}

				scl_dataSet = (SCL_DATASET *)scl_dataSet->l.next;
				if (scl_dataSet == scl_ln->datasetHead) break;
			}
			
			SCL_RCB* scl_rcb = scl_ln->rcbHead;
			while (scl_rcb != NULL)
			{
				fputc(14, fp);
				fwrite(scl_rcb, sizeof(SCL_RCB), 1, fp);

				if (scl_rcb->desc != NULL)
				{
					memset(buf, 0, MAX_DESC_LEN+1);
					strcpy(buf, scl_rcb->desc);
					fputc(24, fp);
					fwrite(buf, MAX_DESC_LEN+1, 1, fp);
				}

				scl_rcb = (SCL_RCB *)scl_rcb->l.next;
				if (scl_rcb == scl_ln->rcbHead) break;
			}

			SCL_LCB* scl_lcb = scl_ln->lcbHead;
			while (scl_lcb != NULL)
			{
				fputc(15, fp);
				fwrite(scl_lcb, sizeof(SCL_LCB), 1, fp);
				
				if (scl_lcb->desc != NULL)
				{
					memset(buf, 0, MAX_DESC_LEN+1);
					strcpy(buf, scl_lcb->desc);
					fputc(25, fp);
					fwrite(buf, MAX_DESC_LEN+1, 1, fp);
				}
				
				scl_lcb = (SCL_LCB *)scl_lcb->l.next;
				if (scl_lcb == scl_ln->lcbHead) break;
			}

			SCL_GCB* scl_gcb = scl_ln->gcbHead;
			while (scl_gcb != NULL)
			{
				fputc(16, fp);
				fwrite(scl_gcb, sizeof(SCL_GCB), 1, fp);
				
				if (scl_gcb->desc != NULL)
				{
					memset(buf, 0, MAX_DESC_LEN+1);
					strcpy(buf, scl_gcb->desc);
					fputc(26, fp);
					fwrite(buf, MAX_DESC_LEN+1, 1, fp);
				}
				
				scl_gcb = (SCL_GCB *)scl_gcb->l.next;
				if (scl_gcb == scl_ln->gcbHead) break;
			}

			SCL_SVCB* scl_svcb = scl_ln->svcbHead;
			while (scl_svcb != NULL)
			{
				fputc(17, fp);
				fwrite(scl_svcb, sizeof(SCL_SVCB), 1, fp);
				
				if (scl_svcb->desc != NULL)
				{
					memset(buf, 0, MAX_DESC_LEN+1);
					strcpy(buf, scl_svcb->desc);
					fputc(27, fp);
					fwrite(buf, MAX_DESC_LEN+1, 1, fp);
				}
				
				scl_svcb = (SCL_SVCB *)scl_svcb->l.next;
				if (scl_svcb == scl_ln->svcbHead) break;
			}

			scl_ln = (SCL_LN *)scl_ln->l.next;
			if (scl_ln == scl_ld->lnHead) break;
		}
		
		scl_ld = (SCL_LD *)scl_ld->l.next;
		if (scl_ld == scl_Info.ldHead) break;
	}

	fclose(fp);
	return 0;
}

//从保存的文件载入IED配置信息
int LoadScdIedInfo(SCL_INFO *scl_Info, char *loadFilePath)
{
	SCL_LNTYPE *scl_lnType;
	SCL_DO *scl_do;
	SCL_DOTYPE *scl_doType;
	SCL_DA *scl_da;
	SCL_DATYPE *scl_daType;
	SCL_BDA *scl_bda;
	SCL_ENUMTYPE *scl_enumType;
	SCL_ENUMVAL *scl_enumVal;

	SCL_LD *scl_ld;
	SCL_LN *scl_ln;
	SCL_DAI *scl_dai;
	SCL_DATASET *scl_dataSet;
	SCL_FCDA *scl_fcda;
	SCL_RCB *scl_rcb;
	SCL_LCB *scl_lcb;
	SCL_GCB *scl_gcb;
	SCL_SVCB *scl_svcb;
	
	char buf[MAX_DESC_LEN+1]; 
	int ch;
	int ret = 0;
	
	FILE* fp = fopen(loadFilePath, "rb");
	fread(scl_Info, sizeof(SCL_INFO), 1, fp);
	scl_Info->subnetHead = NULL;
	scl_Info->lnTypeHead = NULL;
	scl_Info->doTypeHead = NULL;
	scl_Info->daTypeHead = NULL;
	scl_Info->enumTypeHead = NULL;
	scl_Info->ldHead = NULL;

	while((ch = fgetc(fp)) != EOF)
	{
		switch (ch)
		{
		case 1:
			scl_lnType = (SCL_LNTYPE *)calloc(1, sizeof(SCL_LNTYPE));
			fread(scl_lnType, sizeof(SCL_LNTYPE), 1, fp);
			scl_lnType->doHead = NULL;
			list_add_first((DBL_LNK **)(&scl_Info->lnTypeHead), (DBL_LNK *)scl_lnType);
			break;
		case 2:
			scl_do = (SCL_DO *)calloc(1, sizeof(SCL_DO));
			fread(scl_do, sizeof(SCL_DO), 1, fp);
			if (scl_lnType != NULL)
				list_add_first((DBL_LNK **)(&scl_lnType->doHead), (DBL_LNK *)scl_do);
			break;
		case 3:
			scl_doType = (SCL_DOTYPE *)calloc(1, sizeof(SCL_DOTYPE));
			fread(scl_doType, sizeof(SCL_DOTYPE), 1, fp);
			scl_doType->daHead = NULL;
			list_add_first((DBL_LNK **)(&scl_Info->doTypeHead), (DBL_LNK *)scl_doType);
			break;
		case 4:
			scl_da = (SCL_DA *)calloc(1, sizeof(SCL_DA));
			fread(scl_da, sizeof(SCL_DA), 1, fp);
			if (scl_doType != NULL)
				list_add_first((DBL_LNK **)(&scl_doType->daHead), (DBL_LNK *)scl_da);
			break;
		case 5:
			scl_daType = (SCL_DATYPE *)calloc(1, sizeof(SCL_DATYPE));
			fread(scl_daType, sizeof(SCL_DATYPE), 1, fp);
			scl_daType->bdaHead = NULL;
			list_add_first((DBL_LNK **)(&scl_Info->daTypeHead), (DBL_LNK *)scl_daType);
			break;
		case 6:
			scl_bda = (SCL_BDA *)calloc(1, sizeof(SCL_BDA));
			fread(scl_bda, sizeof(SCL_BDA), 1, fp);
			if (scl_daType != NULL)
				list_add_first((DBL_LNK **)(&scl_daType->bdaHead), (DBL_LNK *)scl_bda);
			break;
		case 7:
			scl_enumType = (SCL_ENUMTYPE *)calloc(1, sizeof(SCL_ENUMTYPE));
			fread(scl_enumType, sizeof(SCL_ENUMTYPE), 1, fp);
			scl_enumType->enumvalHead = NULL;
			list_add_first((DBL_LNK **)(&scl_Info->enumTypeHead), (DBL_LNK *)scl_enumType);
			break;
		case 8:
			scl_enumVal = (SCL_ENUMVAL *)calloc(1, sizeof(SCL_ENUMVAL));
			fread(scl_enumVal, sizeof(SCL_ENUMVAL), 1, fp);
			if (scl_enumType != NULL)
				list_add_first((DBL_LNK **)(&scl_enumType->enumvalHead), (DBL_LNK *)scl_enumVal);
			break;
		case 10:
			scl_ld = (SCL_LD *)calloc(1, sizeof(SCL_LD));
			fread(scl_ld, sizeof(SCL_LD), 1, fp);
			scl_ld->lnHead = NULL;
			scl_ld->desc = NULL;
			list_add_first((DBL_LNK **)(&scl_Info->ldHead), (DBL_LNK *)scl_ld);
			break;
		case 20:
			fread(buf, MAX_DESC_LEN+1, 1, fp);
			if (scl_ld != NULL)
			{
				scl_ld->desc = (ST_CHAR *)malloc(strlen(buf) + 1);
				strcpy(scl_ld->desc, buf);
			}
			break;
		case 11:
			scl_ln = (SCL_LN *)calloc(1, sizeof(SCL_LN));
			fread(scl_ln, sizeof(SCL_LN), 1, fp);
			scl_ln->daiHead = NULL;
			scl_ln->datasetHead = NULL;
			scl_ln->rcbHead = NULL;
			scl_ln->lcbHead = NULL;
			scl_ln->gcbHead = NULL;
			scl_ln->svcbHead = NULL;
			scl_ln->rwHead = NULL;
			scl_ln->desc = NULL;
			if (scl_ld != NULL)
				list_add_first((DBL_LNK **)(&scl_ld->lnHead), (DBL_LNK *)scl_ln);
			break;
		case 21:
			fread(buf, MAX_DESC_LEN+1, 1, fp);
			if (scl_ln != NULL)
			{
				scl_ln->desc = (ST_CHAR *)malloc(strlen(buf) + 1);
				strcpy(scl_ln->desc, buf);
			}
			break;
		case 12:
			scl_dai = (SCL_DAI *)calloc(1, sizeof(SCL_DAI));
			fread(scl_dai, sizeof(SCL_DAI), 1, fp);
			scl_dai->Val = NULL;
			if (scl_ln != NULL)
				list_add_first((DBL_LNK **)(&scl_ln->daiHead), (DBL_LNK *)scl_dai);
			break;
		case 22:
			fread(buf, MAX_DESC_LEN+1, 1, fp);
			if (scl_dai != NULL)
			{
				scl_dai->Val = (ST_CHAR *)malloc(strlen(buf) + 1);
				strcpy(scl_dai->Val, buf);
			}
			break;
		case 13:
			scl_dataSet = (SCL_DATASET *)calloc(1, sizeof(SCL_DATASET));
			fread(scl_dataSet, sizeof(SCL_DATASET), 1, fp);
			scl_dataSet->fcdaHead = NULL;
			scl_dataSet->desc = NULL;
			if (scl_ln != NULL)
				list_add_first((DBL_LNK **)(&scl_ln->datasetHead), (DBL_LNK *)scl_dataSet);
			break;
		case 23:
			fread(buf, MAX_DESC_LEN+1, 1, fp);
			if (scl_dataSet != NULL)
			{
				scl_dataSet->desc = (ST_CHAR *)malloc(strlen(buf) + 1);
				strcpy(scl_dataSet->desc, buf);
			}
			break;
		case 33:
			scl_fcda = (SCL_FCDA *)calloc(1, sizeof(SCL_FCDA));
			fread(scl_fcda, sizeof(SCL_FCDA), 1, fp);
			if (scl_dataSet != NULL)
				list_add_first((DBL_LNK **)(&scl_dataSet->fcdaHead), (DBL_LNK *)scl_fcda);
			break;
		case 14:
			scl_rcb = (SCL_RCB *)calloc(1, sizeof(SCL_RCB));
			fread(scl_rcb, sizeof(SCL_RCB), 1, fp);
			scl_rcb->desc = NULL;
			if (scl_ln != NULL)
				list_add_first((DBL_LNK **)(&scl_ln->rcbHead), (DBL_LNK *)scl_rcb);
			break;
		case 24:
			fread(buf, MAX_DESC_LEN+1, 1, fp);
			if (scl_rcb != NULL)
			{
				scl_rcb->desc = (ST_CHAR *)malloc(strlen(buf) + 1);
				strcpy(scl_rcb->desc, buf);
			}
			break;
		case 15:
			scl_lcb = (SCL_LCB *)calloc(1, sizeof(SCL_LCB));
			fread(scl_lcb, sizeof(SCL_LCB), 1, fp);
			scl_lcb->desc = NULL;
			if (scl_ln != NULL)
				list_add_first((DBL_LNK **)(&scl_ln->lcbHead), (DBL_LNK *)scl_lcb);
			break;
		case 25:
			fread(buf, MAX_DESC_LEN+1, 1, fp);
			if (scl_lcb != NULL)
			{
				scl_lcb->desc = (ST_CHAR *)malloc(strlen(buf) + 1);
				strcpy(scl_lcb->desc, buf);
			}
			break;
		case 16:
			scl_gcb = (SCL_GCB *)calloc(1, sizeof(SCL_GCB));
			fread(scl_gcb, sizeof(SCL_GCB), 1, fp);
			scl_gcb->desc = NULL;
			if (scl_ln != NULL)
				list_add_first((DBL_LNK **)(&scl_ln->gcbHead), (DBL_LNK *)scl_gcb);
			break;
		case 26:
			fread(buf, MAX_DESC_LEN+1, 1, fp);
			if (scl_rcb != NULL)
			{
				scl_gcb->desc = (ST_CHAR *)malloc(strlen(buf) + 1);
				strcpy(scl_gcb->desc, buf);
			}
			break;
		case 17:
			scl_svcb = (SCL_SVCB *)calloc(1, sizeof(SCL_SVCB));
			fread(scl_svcb, sizeof(SCL_SVCB), 1, fp);
			scl_svcb->desc = NULL;
			if (scl_ln != NULL)
				list_add_first((DBL_LNK **)(&scl_ln->svcbHead), (DBL_LNK *)scl_svcb);
			break;
		case 27:
			fread(buf, MAX_DESC_LEN+1, 1, fp);
			if (scl_svcb != NULL)
			{
				scl_svcb->desc = (ST_CHAR *)malloc(strlen(buf) + 1);
				strcpy(scl_svcb->desc, buf);
			}
			break;
		default:
			ret = -1;
		}

		if (ret) break;
	}
	
	fclose(fp);
	return ret;
}


#ifdef __cplusplus   
}  
#endif  

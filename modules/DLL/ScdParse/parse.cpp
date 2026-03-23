
#pragma warning(disable:4786)

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "parse.h"


vector<CLnType>				CSCDLnTypeList;
vector<CLnMember>			CSCDLnMemberList;
vector<CDoType>				CSCDDoTypeList;
vector<CDoMember>			CSCDDoMemberList;
vector<CDaType>				CSCDDaTypeList;
vector<CDaMember>			CSCDDaMemberList;
vector<CEnumType>			CSCDEnumTypeList;
vector<CEnumMember>			CSCDEnumMemberList;

vector<CIED>				CSCDIEDList;
vector<CLD>					CSCDLDList;
vector<CLNinst>				CSCDLNinstList;
vector<CDOI>				CSCDDOIList;
vector<CDAI>				CSCDDAIList;
vector<CDataSet>			CSCDDataSetList;
vector<CDsMember>			CSCDDsMemberList;
vector<CRptCtrl>			CSCDRptCtrlList;
vector<CLLNO>				CSCDLLNOList;

vector<CNetConfig>			CSCDNetConfigList;    
vector<CCommConfig>			CSCDCommConfigList;
vector<CHeaderConfig>		CSCDHeaderConfigList;
vector<CHistoryConfig>		CSCDHistoryConfigList;


TiXmlDocument	*Scd_Doc = NULL;
char			Scd_File[512];
char			Ied_Name[64];
bool			DataType_Done = false;


//初始化列表（kind：0 全部列表，1 DataType部分列表，2 IED部分列表, 3 其他部分列表）
void ClearSCDList(int kind)
{
	if( kind == 0 || kind == 1 )
	{
		CSCDLnTypeList.clear();
		CSCDLnMemberList.clear();
		CSCDDoTypeList.clear();
		CSCDDoMemberList.clear();
		CSCDDaTypeList.clear();
		CSCDDaMemberList.clear();
		CSCDEnumTypeList.clear();
		CSCDEnumMemberList.clear();
	}

	if( kind == 0 || kind == 2 )
	{
		CSCDIEDList.clear();
		CSCDLDList.clear();
		CSCDLNinstList.clear();
		CSCDDOIList.clear();
		CSCDDAIList.clear();
		CSCDDataSetList.clear();
		CSCDDsMemberList.clear();
		CSCDRptCtrlList.clear();
		CSCDLLNOList.clear();
	}

	if( kind == 0 || kind == 3 )
	{
		CSCDNetConfigList.clear();
		CSCDCommConfigList.clear();
		CSCDHeaderConfigList.clear();
		CSCDHistoryConfigList.clear();
	}
}

//标记DataType使用标志
int MarkDataTypeUsed()
{
	int i;

	//清标志
	for (i=0; i<CSCDLnTypeList.size(); i++)
	{
		CSCDLnTypeList.at(i).used = false;
	}
	for (i=0; i<CSCDDoTypeList.size(); i++)
	{
		CSCDDoTypeList.at(i).used = false;
	}
	for (i=0; i<CSCDDaTypeList.size(); i++)
	{
		CSCDDaTypeList.at(i).used = false;
	}
	for (i=0; i<CSCDEnumTypeList.size(); i++)
	{
		CSCDEnumTypeList.at(i).used = false;
	}

	//LN,LN0中用到的LNodeType
	for (vector<CLNinst>::iterator it1 = CSCDLNinstList.begin(); it1 < CSCDLNinstList.end(); it1++)
	{
		CLNinst* pLNinst = &(*it1);
		if (pLNinst->nLnType_id<1 || pLNinst->nLnType_id>CSCDLnTypeList.size()) return -11;
		CSCDLnTypeList.at(pLNinst->nLnType_id - 1).used = true;
	}

	//DOI中用到的DOType
	for (vector<CDOI>::iterator it2 = CSCDDOIList.begin(); it2 < CSCDDOIList.end(); it2++)
	{
		CDOI* pDOI = &(*it2);
		if (pDOI->nIdDotype<1 || pDOI->nIdDotype>CSCDDoTypeList.size()) return -12;
		CSCDDoTypeList.at(pDOI->nIdDotype - 1).used = true;
	}

	//DO中用到的DOType
	for (vector<CLnMember>::iterator it3 = CSCDLnMemberList.begin(); it3 < CSCDLnMemberList.end(); it3++)
	{
		CLnMember* pLnMember = &(*it3);
		if (pLnMember->nLnType_id<1 || pLnMember->nLnType_id>CSCDLnTypeList.size()) return -13;
		if (CSCDLnTypeList.at(pLnMember->nLnType_id - 1).used)
		{
			if (pLnMember->nDoType_id<1 || pLnMember->nDoType_id>CSCDDoTypeList.size()) return -14;
			CSCDDoTypeList.at(pLnMember->nDoType_id - 1).used = true;
		}
	}

	//SDO中用到的DOType
	for (vector<CDoMember>::iterator it4 = CSCDDoMemberList.begin(); it4 < CSCDDoMemberList.end(); it4++)
	{
		CDoMember* pDoMember = &(*it4);
		if (pDoMember->nDotype_id<1 || pDoMember->nDotype_id>CSCDDoTypeList.size()) return -15;
		if (CSCDDoTypeList.at(pDoMember->nDotype_id - 1).used)
		{
			if (pDoMember->nKind == 1)	//SDO
			{
				if (pDoMember->nType_id<1 || pDoMember->nType_id>CSCDDoTypeList.size()) return -16;
				CSCDDoTypeList.at(pDoMember->nType_id - 1).used = true;
			}
		}
	}

	//DA中用到的DAType,EnumType
	for (vector<CDoMember>::iterator it4 = CSCDDoMemberList.begin(); it4 < CSCDDoMemberList.end(); it4++)
	{
		CDoMember* pDoMember = &(*it4);
		if (pDoMember->nDotype_id<1 || pDoMember->nDotype_id>CSCDDoTypeList.size()) return -17;
		if (CSCDDoTypeList.at(pDoMember->nDotype_id - 1).used)
		{
			if (pDoMember->nKind == 0)	//DA
			{
				if (!strcmp(pDoMember->strBType, "Struct"))
				{
					CSCDDaTypeList.at(pDoMember->nType_id - 1).used = true;
				}
				else if (!strcmp(pDoMember->strBType, "Enum"))
				{
					CSCDEnumTypeList.at(pDoMember->nType_id - 1).used = true;
				}
			}
		}
	}
	
	//BDA中用到的DAType
	for (vector<CDaMember>::iterator it5 = CSCDDaMemberList.begin(); it5 < CSCDDaMemberList.end(); it5++)
	{
		CDaMember* pDaMember = &(*it5);
		if (pDaMember->nDaType_id<1 || pDaMember->nDaType_id>CSCDDaTypeList.size()) return -18;
		if (CSCDDaTypeList.at(pDaMember->nDaType_id - 1).used)
		{
			if (!strcmp(pDaMember->strBType, "Struct"))
			{
				CSCDDaTypeList.at(pDaMember->nType_id - 1).used = true;
			}
		}
	}
	
	//BDA中用到的EnumType
	for (vector<CDaMember>::iterator it5 = CSCDDaMemberList.begin(); it5 < CSCDDaMemberList.end(); it5++)
	{
		CDaMember* pDaMember = &(*it5);
		if (pDaMember->nDaType_id<1 || pDaMember->nDaType_id>CSCDDaTypeList.size()) return -19;
		if (CSCDDaTypeList.at(pDaMember->nDaType_id - 1).used)
		{
			if (!strcmp(pDaMember->strBType, "Enum"))
			{
				CSCDEnumTypeList.at(pDaMember->nType_id - 1).used = true;
			}
		}
	}
/*
	int n1=0, n2=0, n3=0, n4=0;
	for (i=0; i<CSCDLnTypeList.size(); i++)
	{
		if (CSCDLnTypeList.at(i).used) n1++;
	}
	for (i=0; i<CSCDDoTypeList.size(); i++)
	{
		if (CSCDDoTypeList.at(i).used) n2++;
	}
	for (i=0; i<CSCDDaTypeList.size(); i++)
	{
		if (CSCDDaTypeList.at(i).used) n3++;
	}
	for (i=0; i<CSCDEnumTypeList.size(); i++)
	{
		if (CSCDEnumTypeList.at(i).used) n4++;
	}
*/
	return 0;
}

//解析EnumType部分
bool ParseEnumType(TiXmlElement* pDataTypeTemplatesElement)
{
	TiXmlElement* pEnumTypeElement = pDataTypeTemplatesElement->FirstChildElement("EnumType");
    CEnumType *pEnumType;
	
    while (pEnumTypeElement)
	{
        pEnumType = (CEnumType *)calloc(1, sizeof(CEnumType));
		pEnumType->nId = CSCDEnumTypeList.size() + 1;
		pEnumType->nStart = CSCDEnumMemberList.size() + 1;

		if (pEnumTypeElement->Attribute("id"))
		{
			strcpy(pEnumType->strName,pEnumTypeElement->Attribute("id"));
		}
		
		TiXmlElement* pEnumValElement = pEnumTypeElement->FirstChildElement("EnumVal");
		while (pEnumValElement)
		{
			CEnumMember *pEnumMember = (CEnumMember *)calloc(1, sizeof(CEnumMember));
			pEnumMember->nId = CSCDEnumMemberList.size() + 1;
			pEnumMember->nEnumType_id = pEnumType->nId;

			if (pEnumValElement->GetText())
			{
				strcpy(pEnumMember->strName,pEnumValElement->GetText());
			}
			pEnumMember->nValue = -1;
			if (pEnumValElement->Attribute("ord"))
			{
				pEnumMember->nValue = atoi(pEnumValElement->Attribute("ord"));
			}
			
			CSCDEnumMemberList.push_back(*pEnumMember);
			free(pEnumMember);
			
			pEnumValElement = pEnumValElement->NextSiblingElement("EnumVal");
		}
		
		CSCDEnumTypeList.push_back(*pEnumType);
        free(pEnumType);
		
		pEnumTypeElement = pEnumTypeElement->NextSiblingElement("EnumType");
	}
	
	return true;
}


//解析DAType部分
bool ParseDAType(TiXmlElement* pDataTypeTemplatesElement)
{
	TiXmlElement* pDATypeElement = pDataTypeTemplatesElement->FirstChildElement("DAType");
	while (pDATypeElement)
	{
		CDaType *pDaType = (CDaType *)calloc(1, sizeof(CDaType));
		pDaType->nId = CSCDDaTypeList.size() + 1;
		pDaType->nStart = CSCDDaMemberList.size() + 1;

		if (pDATypeElement->Attribute("id"))
		{
			strcpy(pDaType->strName,pDATypeElement->Attribute("id"));
		}
		
		TiXmlElement* pBDAElement = pDATypeElement->FirstChildElement("BDA");
		while (pBDAElement)
		{
			CDaMember *pDaMember = (CDaMember *)calloc(1, sizeof(CDaMember));
			pDaMember->nId = CSCDDaMemberList.size() + 1;
			pDaMember->nDaType_id = pDaType->nId;
			pDaMember->nType_id = -1;

			if (pBDAElement->Attribute("name"))
			{
				strcpy(pDaMember->strName,pBDAElement->Attribute("name"));
			}
			if (pBDAElement->Attribute("bType"))
			{
				strcpy(pDaMember->strBType,pBDAElement->Attribute("bType"));
			}
			if (pBDAElement->Attribute("type"))
			{
				strcpy(pDaMember->strType,pBDAElement->Attribute("type"));
			}

			if( !strcmp(pDaMember->strBType, "Struct") )	//bType为Struct
			{
				pDaMember->nType_id = -2; //先标记为-2，找到后更新
			}
			else if( !strcmp(pDaMember->strBType, "Enum") )	//bType为Enum
			{
				for (vector<CEnumType>::iterator enIter=CSCDEnumTypeList.begin(); enIter!=CSCDEnumTypeList.end(); ++enIter)
				{
					if( !strcmp(enIter->strName, pDaMember->strType) )
					{
						pDaMember->nType_id = enIter->nId;
						break;
					}
				}
			}
			
			CSCDDaMemberList.push_back(*pDaMember);
			free(pDaMember);
			
			pBDAElement = pBDAElement->NextSiblingElement("BDA");
		}
		
		CSCDDaTypeList.push_back(*pDaType);
		free(pDaType);
		
		pDATypeElement = pDATypeElement->NextSiblingElement("DAType");
	}

	//BDA查找引用的DAType，更新nType_id字段值
	for (vector<CDaMember>::iterator mdoIter=CSCDDaMemberList.begin(); mdoIter!=CSCDDaMemberList.end(); ++mdoIter)
	{
		if( mdoIter->nType_id == -2 )
		{
			for (vector<CDaType>::iterator doIter=CSCDDaTypeList.begin(); doIter!=CSCDDaTypeList.end(); ++doIter)
			{
				if( !strcmp(doIter->strName, mdoIter->strType) )
				{
					mdoIter->nType_id = doIter->nId;
					break;
				}
			}
		}
	}
	
	return true;
}

//解析DOType部分
bool ParseDOType(TiXmlElement* pDataTypeTemplatesElement)
{
	TiXmlElement* pDOTypeElement = pDataTypeTemplatesElement->FirstChildElement("DOType");
	while (pDOTypeElement)
	{
		CDoType *pDoType = (CDoType *)calloc(1, sizeof(CDoType));
		pDoType->nId = CSCDDoTypeList.size() + 1;
		pDoType->nStart = CSCDDoMemberList.size() + 1;

		if (pDOTypeElement->Attribute("id"))
		{
			strcpy(pDoType->strType,pDOTypeElement->Attribute("id"));
		}
		if (pDOTypeElement->Attribute("cdc"))
		{
			strcpy(pDoType->strCDCName,pDOTypeElement->Attribute("cdc"));
		}
		if (pDOTypeElement->Attribute("desc"))
		{
			strcpy(pDoType->strDesc,pDOTypeElement->Attribute("desc"));
		}
		
		//DA
		TiXmlElement* pDAElement = pDOTypeElement->FirstChildElement("DA");
		while (pDAElement)
		{
			CDoMember *pDoMember = (CDoMember *)calloc(1, sizeof(CDoMember));
			pDoMember->nId = CSCDDoMemberList.size() + 1;
			pDoMember->nDotype_id = pDoType->nId;
			pDoMember->nKind = 0;
			pDoMember->nType_id = -1;

			if (pDAElement->Attribute("name"))
			{
				strcpy(pDoMember->strDaName,pDAElement->Attribute("name"));
			}
			if (pDAElement->Attribute("bType"))
			{
				strcpy(pDoMember->strBType,pDAElement->Attribute("bType"));
			}
			if (pDAElement->Attribute("type"))
			{
				strcpy(pDoMember->strType,pDAElement->Attribute("type"));
			}
			if (pDAElement->Attribute("fc"))
			{
				strcpy(pDoMember->strFC,pDAElement->Attribute("fc"));
			}

			pDoMember->bDchg = false;
			pDoMember->bQchg = false;
			pDoMember->bDupd = false;
			if (pDAElement->Attribute("dchg"))
			{
				if( !strcmp(pDAElement->Attribute("dchg"), "true") ) pDoMember->bDchg = true;
			}
			if (pDAElement->Attribute("qchg"))
			{
				if( !strcmp(pDAElement->Attribute("qchg"), "true") ) pDoMember->bQchg = true;
			}
			if (pDAElement->Attribute("dupd"))
			{
				if( !strcmp(pDAElement->Attribute("dupd"), "true") ) pDoMember->bDupd = true;
			}
			
			if( !strcmp(pDoMember->strBType,"Struct") )	//bType为Struct
			{
				for (vector<CDaType>::iterator daTypeIter=CSCDDaTypeList.begin(); daTypeIter!=CSCDDaTypeList.end(); ++daTypeIter)
				{
					if (strcmp(daTypeIter->strName,pDAElement->Attribute("type"))==0)
					{
						pDoMember->nType_id = daTypeIter->nId;
						break;
					}
				}
			}
			else if( !strcmp(pDoMember->strBType, "Enum") )	//bType为Enum
			{
				for (vector<CEnumType>::iterator enIter=CSCDEnumTypeList.begin(); enIter!=CSCDEnumTypeList.end(); ++enIter)
				{
					if( !strcmp(enIter->strName, pDoMember->strType) )
					{
						pDoMember->nType_id = enIter->nId;
						break;
					}
				}
			}

			CSCDDoMemberList.push_back(*pDoMember);
			free(pDoMember);
			
			pDAElement = pDAElement->NextSiblingElement("DA");
		}
		
		//SDO
		TiXmlElement* pSDOElement = pDOTypeElement->FirstChildElement("SDO");
		while (pSDOElement)
		{
			CDoMember *pDoMember = (CDoMember *)calloc(1, sizeof(CDoMember));
			pDoMember->nId = CSCDDoMemberList.size() + 1;
			pDoMember->nDotype_id = pDoType->nId;
			pDoMember->nKind = 1;
			pDoMember->nType_id = -2;	//先标记为-2，找到后更新

			if (pSDOElement->Attribute("name"))
			{
				strcpy(pDoMember->strDaName,pSDOElement->Attribute("name"));
			}
			if (pSDOElement->Attribute("type"))
			{
				strcpy(pDoMember->strType,pSDOElement->Attribute("type"));
			}
			
			CSCDDoMemberList.push_back(*pDoMember);
			free(pDoMember);
			
			pSDOElement = pSDOElement->NextSiblingElement("SDO");
		}
		
		CSCDDoTypeList.push_back(*pDoType);
		free(pDoType);
		
		pDOTypeElement = pDOTypeElement->NextSiblingElement("DOType");
	}

	//SDO查找引用的DOType，更新nType_id字段值
	for (vector<CDoMember>::iterator mdoIter=CSCDDoMemberList.begin(); mdoIter!=CSCDDoMemberList.end(); ++mdoIter)
	{
		if( mdoIter->nType_id == -2 )
		{
			for (vector<CDoType>::iterator doIter=CSCDDoTypeList.begin(); doIter!=CSCDDoTypeList.end(); ++doIter)
			{
				if( !strcmp(doIter->strType, mdoIter->strType) )
				{
					mdoIter->nType_id = doIter->nId;
					break;
				}
			}
		}
	}

	return true;
}


//解析LNodeType部分
bool ParseLNodeType(TiXmlElement* pDataTypeTemplatesElement)
{
	TiXmlElement* pLNodeTypeElement = pDataTypeTemplatesElement->FirstChildElement("LNodeType");
	while (pLNodeTypeElement)
	{
		CLnType *pLnType = (CLnType *)calloc(1, sizeof(CLnType));
		pLnType->nId = CSCDLnTypeList.size() + 1;
		pLnType->nStart = CSCDLnMemberList.size() + 1;

		if (pLNodeTypeElement->Attribute("desc"))
		{
			strcpy(pLnType->strDesc,pLNodeTypeElement->Attribute("desc"));
		}
		if (pLNodeTypeElement->Attribute("lnClass"))
		{
			strcpy(pLnType->strLnclass,pLNodeTypeElement->Attribute("lnClass"));
		}
		if (pLNodeTypeElement->Attribute("id"))
		{
			strcpy(pLnType->strType,pLNodeTypeElement->Attribute("id"));
		}
		
		// DO
		TiXmlElement* pDOElement = pLNodeTypeElement->FirstChildElement("DO");
		while (pDOElement)
		{
			CLnMember *pLnMember = (CLnMember *)calloc(1, sizeof(CLnMember));
			pLnMember->nId = CSCDLnMemberList.size() + 1;
			pLnMember->nLnType_id = pLnType->nId;
			pLnMember->nDoType_id = -1;

			vector<CDoType>::iterator doTypeIter;
			for (doTypeIter=CSCDDoTypeList.begin(); doTypeIter!=CSCDDoTypeList.end(); ++doTypeIter)
			{
				if (strcmp(doTypeIter->strType,pDOElement->Attribute("type"))==0)
				{
					pLnMember->nDoType_id = doTypeIter->nId;
					break;
				}
			}

			if (pDOElement->Attribute("name"))
			{
				strcpy(pLnMember->strDoName,pDOElement->Attribute("name"));
			}
			if (pDOElement->Attribute("type"))
			{
				strcpy(pLnMember->strType,pDOElement->Attribute("type"));
			}
			if (pDOElement->Attribute("desc"))
			{
				strcpy(pLnMember->strDoDesc,pDOElement->Attribute("desc"));
			}
			
			CSCDLnMemberList.push_back(*pLnMember);
			free(pLnMember);
			
			pDOElement = pDOElement->NextSiblingElement("DO");
		}
		
		CSCDLnTypeList.push_back(*pLnType);
		free(pLnType);
		
		pLNodeTypeElement = pLNodeTypeElement->NextSiblingElement("LNodeType");
	}
	
	return true;
}

//解析DataTypeTemplates部分
bool ParseDataTypeTemplates(TiXmlElement* pSCLElement)
{
	TiXmlElement* pDataTypeTemplatesElement = pSCLElement->FirstChildElement("DataTypeTemplates");
	
	if (!pDataTypeTemplatesElement)
	{
		return false;
	}
	
	//解析EnumType部分
	ParseEnumType(pDataTypeTemplatesElement);
	
	//解析DAType部分
	ParseDAType(pDataTypeTemplatesElement);
	
	//解析DOType部分
	ParseDOType(pDataTypeTemplatesElement);
	
	//解析LNodeType部分
	ParseLNodeType(pDataTypeTemplatesElement);
	
	return true;
}

//解析DOI部分
bool ParseDOI(TiXmlElement *pLNElement, const int nIEDID, const int nLDID, const int nLNinstID, const int nLnTypeID)
{
	// DOI
	TiXmlElement *pDOIElement = pLNElement->FirstChildElement("DOI");
	while (pDOIElement)
	{
		//获取DOI的name属性所属的DOTypeID
		int nDoTypeID = -1;
		if (pDOIElement->Attribute("name"))
		{
			vector<CLnMember>::iterator lmIter = CSCDLnMemberList.begin();
			for( lmIter; lmIter != CSCDLnMemberList.end(); lmIter++ )
			{
				if( nLnTypeID == lmIter->nLnType_id && strcmp(lmIter->strDoName,pDOIElement->Attribute("name")) == 0 )
				{
					nDoTypeID = lmIter->nDoType_id;
					break;
				}
			}
		}

		CDOI *pDOI = (CDOI *)calloc(1, sizeof(CDOI));
		pDOI->nId = CSCDDOIList.size() + 1;
		pDOI->nStart = CSCDDAIList.size() + 1;
		pDOI->nIdIED = nIEDID;
		pDOI->nIdLD = nLDID;
		pDOI->nIdLNinst = nLNinstID;
		pDOI->nDsMember = -1;
		pDOI->nIdDotype = nDoTypeID;
		pDOI->doiType = 0;
		pDOI->nDataType = -1;
		
		if (pDOIElement->Attribute("name"))
		{
			strcpy(pDOI->strName,pDOIElement->Attribute("name"));
		}
		
		if (pDOIElement->Attribute("desc"))
		{
			strcpy(pDOI->strDesc,pDOIElement->Attribute("desc"));
		}

		TiXmlElement *pDAIElement = pDOIElement->FirstChildElement("DAI");
		TiXmlElement *pSDIElement = pDOIElement->FirstChildElement("SDI");
		
		// DAI
		while (pDAIElement)
		{   
			CDAI *pDAI = (CDAI *)calloc(1, sizeof(CDAI));
			pDAI->nId = CSCDDAIList.size() + 1;
//			pDAI->nIdIED = nIEDID;
//			pDAI->nIdLD = nLDID;
//			pDAI->nIdLNinst = nLNinstID;
			pDAI->nIdDOI = pDOI->nId;

			if (pDAIElement->Attribute("name"))
			{
				strcpy(pDAI->daiName,pDAIElement->Attribute("name"));
			}

			if (pDAIElement->Attribute("sAddr"))
			{
				strcpy(pDAI->strSaddr,pDAIElement->Attribute("sAddr"));
			}

			if (pDAIElement->Attribute("valKind"))
			{
				strcpy(pDAI->valKind,pDAIElement->Attribute("valKind"));
			}
			
			TiXmlElement *pValElement = pDAIElement->FirstChildElement("Val");
			if (pValElement)
			{
				if (pValElement->GetText())
				{
					strcpy(pDAI->val,pValElement->GetText());
				}
			}

			if (!strcmp(pDAI->daiName, "dU"))
			{
				strcpy(pDOI->str_dU, pDAI->val);
			}
			if (!strcmp(pDAI->daiName, "ctlModel"))
			{
				strcpy(pDOI->str_ctlModel, pDAI->val);
			}

			if (!strcmp(pDAI->daiName, "stVal")) pDOI->doiType |= 1;
			else if (!strcmp(pDAI->daiName, "general")) pDOI->doiType |= 2;
			else if (!strcmp(pDAI->daiName, "setVal")) pDOI->doiType |= (1<<12);
				
			CSCDDAIList.push_back(*pDAI);
			free(pDAI);

			pDAIElement = pDAIElement->NextSiblingElement("DAI");
		}
		
		while (pSDIElement)
		{
			TiXmlElement *pSDIDAIElement = pSDIElement->FirstChildElement("DAI");

			// SDI->DAI
			while (pSDIDAIElement)
			{
				CDAI *pDAI = (CDAI *)calloc(1, sizeof(CDAI));
				pDAI->nId = CSCDDAIList.size() + 1;
//				pDAI->nIdIED = nIEDID;
//				pDAI->nIdLD = nLDID;
//				pDAI->nIdLNinst = nLNinstID;
				pDAI->nIdDOI = pDOI->nId;

				if (pSDIElement->Attribute("name"))
				{
					strcpy(pDAI->daiName,pSDIElement->Attribute("name"));
				}
				if (pSDIDAIElement->Attribute("name"))
				{
					strcat(pDAI->daiName,"$");
					strcat(pDAI->daiName,pSDIDAIElement->Attribute("name"));
				}

				if (pSDIDAIElement->Attribute("sAddr"))
				{
					strcpy(pDAI->strSaddr,pSDIDAIElement->Attribute("sAddr"));
				}

				if (pSDIDAIElement->Attribute("valKind"))
				{
					strcat(pDAI->valKind,pSDIDAIElement->Attribute("valKind"));
				}

				TiXmlElement *pValElement = pSDIDAIElement->FirstChildElement("Val");
				if (pValElement)
				{
					if (pValElement->GetText())
					{
						strcpy(pDAI->val,pValElement->GetText());
					}
				}
					
				if (!strcmp(pDAI->daiName, "mag$f")) pDOI->doiType |= (1<<4);
				else if (!strcmp(pDAI->daiName, "instMag$i")) pDOI->doiType |= (1<<6);
				else if (!strcmp(pDAI->daiName, "SBOw$ctlVal")) pDOI->doiType |= (1<<8);
				else if (!strcmp(pDAI->daiName, "Oper$ctlVal")) pDOI->doiType |= (1<<9);
				else if (!strcmp(pDAI->daiName, "Cancel$ctlVal")) pDOI->doiType |= (1<<10);
				else if (!strcmp(pDAI->daiName, "setMag$f")) pDOI->doiType |= (1<<13);

				CSCDDAIList.push_back(*pDAI);
				free(pDAI);

				pSDIDAIElement = pSDIDAIElement->NextSiblingElement("DAI");
			}
			
			TiXmlElement *pSSDIElement = pSDIElement->FirstChildElement("SDI");
			while (pSSDIElement)
			{
				TiXmlElement *pSSDIDAIElement = pSSDIElement->FirstChildElement("DAI");

				// SDI->SDI->DAI
				while (pSSDIDAIElement)
				{
					CDAI *pDAI = (CDAI *)calloc(1, sizeof(CDAI));
					pDAI->nId = CSCDDAIList.size() + 1;
//					pDAI->nIdIED = nIEDID;
//					pDAI->nIdLD = nLDID;
//					pDAI->nIdLNinst = nLNinstID;
					pDAI->nIdDOI = pDOI->nId;

					if (pSDIElement->Attribute("name"))
					{
						strcpy(pDAI->daiName,pSDIElement->Attribute("name"));
					}
					if (pSSDIElement->Attribute("name"))
					{
						strcat(pDAI->daiName,"$");
						strcat(pDAI->daiName,pSSDIElement->Attribute("name"));
					}
					if (pSSDIDAIElement->Attribute("name"))
					{
						strcat(pDAI->daiName,"$");
						strcat(pDAI->daiName,pSSDIDAIElement->Attribute("name"));
					}
					
					if (pSSDIDAIElement->Attribute("sAddr"))
					{
						strcpy(pDAI->strSaddr,pSSDIDAIElement->Attribute("sAddr"));
					}
					
					if (pSSDIDAIElement->Attribute("valKind"))
					{
						strcat(pDAI->valKind,pSSDIDAIElement->Attribute("valKind"));
					}

					TiXmlElement *pValElement = pSSDIDAIElement->FirstChildElement("Val");
					if (pValElement)
					{
						if (pValElement->GetText())
						{
							strcpy(pDAI->val,pValElement->GetText());
						}
					}

					if (!strcmp(pDAI->daiName, "cVal$mag$f")) pDOI->doiType |= (1<<5);
					
					CSCDDAIList.push_back(*pDAI);
					free(pDAI);
					
					pSSDIDAIElement = pSSDIDAIElement->NextSiblingElement("DAI");
				}
				
				TiXmlElement *pSSSDIElement = pSSDIElement->FirstChildElement("SDI");
				while (pSSSDIElement)
				{
					TiXmlElement *pSSSDIDAIElement = pSSSDIElement->FirstChildElement("DAI");

					// SDI->SDI->SDI->DAI
					while (pSSSDIDAIElement)
					{
						CDAI *pDAI = (CDAI *)calloc(1, sizeof(CDAI));
						pDAI->nId = CSCDDAIList.size() + 1;
//						pDAI->nIdIED = nIEDID;
//						pDAI->nIdLD = nLDID;
//						pDAI->nIdLNinst = nLNinstID;
						pDAI->nIdDOI = pDOI->nId;

						if (pSDIElement->Attribute("name"))
						{
							strcpy(pDAI->daiName,pSDIElement->Attribute("name"));
						}
						if (pSSDIElement->Attribute("name"))
						{
							strcat(pDAI->daiName,"$");
							strcat(pDAI->daiName,pSSDIElement->Attribute("name"));
						}
						if (pSSSDIElement->Attribute("name"))
						{
							strcat(pDAI->daiName,"$");
							strcat(pDAI->daiName,pSSSDIElement->Attribute("name"));
						}
						if (pSSSDIDAIElement->Attribute("name"))
						{
							strcat(pDAI->daiName,"$");
							strcat(pDAI->daiName,pSSSDIDAIElement->Attribute("name"));
						}
						
						if (pSSSDIDAIElement->Attribute("sAddr"))
						{
							strcpy(pDAI->strSaddr,pSSSDIDAIElement->Attribute("sAddr"));
						}

						if (pSSSDIDAIElement->Attribute("valKind"))
						{
							strcat(pDAI->valKind,pSSSDIDAIElement->Attribute("valKind"));
						}

						TiXmlElement *pValElement = pSSSDIDAIElement->FirstChildElement("Val");
						if (pValElement)
						{
							if (pValElement->GetText())
							{
								strcpy(pDAI->val,pValElement->GetText());
							}
						}
						
						if (strstr(pDAI->daiName, "$cVal$mag$f")) pDOI->doiType |= (1<<7);

						CSCDDAIList.push_back(*pDAI);
						free(pDAI);
						
						pSSSDIDAIElement = pSSSDIDAIElement->NextSiblingElement("DAI");
					}
					pSSSDIElement = pSSSDIElement->NextSiblingElement("SDI");
				}
				pSSDIElement = pSSDIElement->NextSiblingElement("SDI");
			}			
			pSDIElement = pSDIElement->NextSiblingElement("SDI");
		}

		//根据DoType填充nDataType，并补充DAI
		if (pDOI->nIdDotype > 0)
		{
			int doiType = 0;

			vector<CDoMember>::iterator it = CSCDDoMemberList.begin() + CSCDDoTypeList.at(pDOI->nIdDotype-1).nStart - 1;
			while( it < CSCDDoMemberList.end() )
			{
				CDoMember *pDoMember = &(*it);
				if (pDoMember->nDotype_id != pDOI->nIdDotype) break;

				if (pDoMember->nKind == 1)	//SDO
				{
					if (pDoMember->nType_id > 0 && (pDOI->doiType&(1<<7)) == 0)
					{
						vector<CDoMember>::iterator it1 = CSCDDoMemberList.begin() + CSCDDoTypeList.at(pDoMember->nType_id-1).nStart - 1;
						while( it1 < CSCDDoMemberList.end() )
						{
							CDoMember *pDoMember1 = &(*it1);
							if (pDoMember1->nDotype_id != pDoMember->nType_id) break;

							if (!strcmp(pDoMember1->strDaName, "cVal"))
							{
								CDAI *pDAI = (CDAI *)calloc(1, sizeof(CDAI));
								pDAI->nId = CSCDDAIList.size() + 1;
								pDAI->nIdDOI = pDOI->nId;
								
								strcpy(pDAI->daiName, pDoMember->strDaName);
								strcat(pDAI->daiName, "$cVal$mag$f");
								doiType |= (1<<7);
								
								CSCDDAIList.push_back(*pDAI);
								free(pDAI);
							}

							it1++;
						}
					}
				}
				else	//DA
				{
					if (!strcmp(pDoMember->strDaName, "stVal"))
					{
						if (!strcmp(pDoMember->strBType, "Dbpos"))
							pDOI->nDataType = ENUM_TYPE_CODEENUM;
						else
							pDOI->nDataType = ENUM_TYPE_BOOLEAN;

						if ((pDOI->doiType&1) == 0)
						{
							CDAI *pDAI = (CDAI *)calloc(1, sizeof(CDAI));
							pDAI->nId = CSCDDAIList.size() + 1;
							pDAI->nIdDOI = pDOI->nId;
							
							strcpy(pDAI->daiName, "stVal");
							pDOI->doiType |= 1;
							
							CSCDDAIList.push_back(*pDAI);
							free(pDAI);
						}
					}
					else if (!strcmp(pDoMember->strDaName, "general"))
					{
						pDOI->nDataType = ENUM_TYPE_BOOLEAN;

						if ((pDOI->doiType&2) == 0)
						{
							CDAI *pDAI = (CDAI *)calloc(1, sizeof(CDAI));
							pDAI->nId = CSCDDAIList.size() + 1;
							pDAI->nIdDOI = pDOI->nId;
							
							strcpy(pDAI->daiName, "general");
							pDOI->doiType |= 2;
							
							CSCDDAIList.push_back(*pDAI);
							free(pDAI);
						}
					}
					else if (!strcmp(pDoMember->strDaName, "mag"))
					{
						pDOI->nDataType = ENUM_TYPE_FLOAT;
						
						if ((pDOI->doiType&(1<<4)) == 0)
						{
							CDAI *pDAI = (CDAI *)calloc(1, sizeof(CDAI));
							pDAI->nId = CSCDDAIList.size() + 1;
							pDAI->nIdDOI = pDOI->nId;
							
							strcpy(pDAI->daiName, "mag$f");
							pDOI->doiType |= (1<<4);
							
							CSCDDAIList.push_back(*pDAI);
							free(pDAI);
						}
					}
					else if (!strcmp(pDoMember->strDaName, "cVal"))
					{
						pDOI->nDataType = ENUM_TYPE_FLOAT;
						
						if ((pDOI->doiType&(1<<5)) == 0)
						{
							CDAI *pDAI = (CDAI *)calloc(1, sizeof(CDAI));
							pDAI->nId = CSCDDAIList.size() + 1;
							pDAI->nIdDOI = pDOI->nId;
							
							strcpy(pDAI->daiName, "cVal$mag$f");
							pDOI->doiType |= (1<<5);
							
							CSCDDAIList.push_back(*pDAI);
							free(pDAI);
						}
					}
					else if (!strcmp(pDoMember->strDaName, "instMag"))
					{
						pDOI->nDataType = ENUM_TYPE_INT;
						
						if ((pDOI->doiType&(1<<6)) == 0)
						{
							CDAI *pDAI = (CDAI *)calloc(1, sizeof(CDAI));
							pDAI->nId = CSCDDAIList.size() + 1;
							pDAI->nIdDOI = pDOI->nId;
							
							strcpy(pDAI->daiName, "instMag$i");
							pDOI->doiType |= (1<<6);
							
							CSCDDAIList.push_back(*pDAI);
							free(pDAI);
						}
					}
					else if (!strcmp(pDoMember->strDaName, "setVal"))
					{
						if (!strcmp(pDoMember->strBType, "Unicode255"))
							pDOI->nDataType = ENUM_TYPE_VISIBLESTRING;
						else if (!strcmp(pDoMember->strBType, "BOOLEAN"))
							pDOI->nDataType = ENUM_TYPE_BOOLEAN;
						else if (!strcmp(pDoMember->strBType, "INT32"))
							pDOI->nDataType = ENUM_TYPE_INT;
						
						if ((pDOI->doiType&(1<<12)) == 0)
						{
							CDAI *pDAI = (CDAI *)calloc(1, sizeof(CDAI));
							pDAI->nId = CSCDDAIList.size() + 1;
							pDAI->nIdDOI = pDOI->nId;
							
							strcpy(pDAI->daiName, "setVal");
							pDOI->doiType |= (1<<12);
							
							CSCDDAIList.push_back(*pDAI);
							free(pDAI);
						}
					}
					else if (!strcmp(pDoMember->strDaName, "setMag"))
					{
						pDOI->nDataType = ENUM_TYPE_FLOAT;
						
						if ((pDOI->doiType&(1<<13)) == 0)
						{
							CDAI *pDAI = (CDAI *)calloc(1, sizeof(CDAI));
							pDAI->nId = CSCDDAIList.size() + 1;
							pDAI->nIdDOI = pDOI->nId;
							
							strcpy(pDAI->daiName, "setMag$f");
							pDOI->doiType |= (1<<13);
							
							CSCDDAIList.push_back(*pDAI);
							free(pDAI);
						}
					}
					
					if (!strcmp(pDoMember->strDaName, "SBOw") && (pDOI->doiType&(1<<8)) == 0)
					{
						CDAI *pDAI = (CDAI *)calloc(1, sizeof(CDAI));
						pDAI->nId = CSCDDAIList.size() + 1;
						pDAI->nIdDOI = pDOI->nId;
						
						strcpy(pDAI->daiName, "SBOw$ctlVal");
						pDOI->doiType |= (1<<8);
						
						CSCDDAIList.push_back(*pDAI);
						free(pDAI);
					}
					
					if (!strcmp(pDoMember->strDaName, "Oper") && (pDOI->doiType&(1<<9)) == 0)
					{
						CDAI *pDAI = (CDAI *)calloc(1, sizeof(CDAI));
						pDAI->nId = CSCDDAIList.size() + 1;
						pDAI->nIdDOI = pDOI->nId;
						
						strcpy(pDAI->daiName, "Oper$ctlVal");
						pDOI->doiType |= (1<<9);
						
						CSCDDAIList.push_back(*pDAI);
						free(pDAI);
					}
				}

				it++;
			}

			if (doiType&(1<<7))
			{
				pDOI->doiType |= (1<<7);
				if (!strcmp(pDOI->strDesc, "")) strcpy(pDOI->strDesc, pDOI->strName);
			}
		}

		if (!strcmp(pDOI->str_dU, "") && strcmp(pDOI->strDesc, ""))
		{
			strcpy(pDOI->str_dU, pDOI->strDesc);
		}

		CSCDDOIList.push_back(*pDOI);
		free(pDOI);
		
		pDOIElement = pDOIElement->NextSiblingElement("DOI");
	}
	return true;
}

//解析DataSet
bool ParseDataSet(TiXmlElement *pLN0Element, const int nIEDID, const int nLDID, const int nLNinstID)
{
	TiXmlElement *pDataSetElement = pLN0Element->FirstChildElement("DataSet");
	while (pDataSetElement)
	{
		CDataSet *pDataSet = (CDataSet *)calloc(1, sizeof(CDataSet));
		pDataSet->nId = CSCDDataSetList.size() + 1;
		pDataSet->nStart = CSCDDsMemberList.size() + 1;
		pDataSet->nIdIED = nIEDID;
		pDataSet->nIdLD = nLDID;
		pDataSet->nIdLNinst = nLNinstID;

		if (pDataSetElement->Attribute("name"))
		{
			strcpy(pDataSet->strName,pDataSetElement->Attribute("name"));
		}
		if (pDataSetElement->Attribute("desc"))
		{
			strcpy(pDataSet->strDesc,pDataSetElement->Attribute("desc"));
		}
		
		//根据ds的Name属性是否为GOOSE
		int nIsGoose = -1;
		char dsName[MAX_NAME_LEN]={0};
		strcpy(dsName,pDataSet->strName);
		
		int tempI = -1;
		while (dsName[tempI++])
		{
			dsName[tempI] = toupper(dsName[tempI]);
		}
		if (strstr(dsName,"GOOSE") != 0) 
		{
			nIsGoose = 1;
		}
		else
		{
			nIsGoose = 0;
		}
		
		int nSeqMember = 0;
		TiXmlElement *pFCDAElement = pDataSetElement->FirstChildElement("FCDA");						
		while (pFCDAElement)
		{
			CDsMember *pDsMember = (CDsMember *)calloc(1, sizeof(CDsMember));
			pDsMember->nId = CSCDDsMemberList.size() + 1;
			pDsMember->nIdIED = nIEDID;
			pDsMember->nDOI = -1;
			pDsMember->nDAI = -1;
			pDsMember->nDsId = pDataSet->nId;
			pDsMember->nSeqMember = nSeqMember;

			pDsMember->nIsGoose = nIsGoose;
			pDsMember->nAppType = -1;
			pDsMember->nBTypeValue = -1;
			
			if (pFCDAElement->Attribute("daName"))
			{
				strcpy(pDsMember->strDaName,pFCDAElement->Attribute("daName"));
			}
			if (pFCDAElement->Attribute("doName"))
			{
				strcpy(pDsMember->strDoName,pFCDAElement->Attribute("doName"));
			}
			if (pFCDAElement->Attribute("fc"))
			{
				strcpy(pDsMember->strFC,pFCDAElement->Attribute("fc"));
			}
			if (pFCDAElement->Attribute("prefix"))
			{
				strcpy(pDsMember->strPrefix,pFCDAElement->Attribute("prefix"));
			}
			if (pFCDAElement->Attribute("lnClass"))
			{
				strcpy(pDsMember->strLnClass,pFCDAElement->Attribute("lnClass"));
			}
			if (pFCDAElement->Attribute("lnInst"))
			{
				strcpy(pDsMember->strLnInst,pFCDAElement->Attribute("lnInst"));
			}
			if (pFCDAElement->Attribute("ldInst"))
			{
				strcpy(pDsMember->strLdInst,pFCDAElement->Attribute("ldInst"));
			}
			
			vector<CDOI>::iterator doiIter;
			for (doiIter = CSCDDOIList.begin(); doiIter < CSCDDOIList.end(); doiIter++)
			{
				CDOI *pDOI = &(*doiIter);

				if ((pDOI->nIdLD == nLDID)
					&& (strcmp(pDsMember->strPrefix, CSCDLNinstList.at(pDOI->nIdLNinst-1).prefix)==0)
					&& (strcmp(pDsMember->strLnClass, CSCDLNinstList.at(pDOI->nIdLNinst-1).lnClass)==0)
					&& (strcmp(pDsMember->strLnInst, CSCDLNinstList.at(pDOI->nIdLNinst-1).strInst)==0)
					&& (strcmp(pDsMember->strDoName, pDOI->strName) == 0))
				{
					pDOI->nDsMember = pDsMember->nId; 
					pDsMember->nDOI = pDOI->nId;
					break;
				}
			}

			vector<CDAI>::iterator daiIter;
			for (daiIter = CSCDDAIList.begin(); daiIter < CSCDDAIList.end(); daiIter++)
			{
				CDAI *pDAI = &(*daiIter);
				CDOI *pDOI = &CSCDDOIList.at(pDAI->nIdDOI-1);
				
				if ((pDOI->nIdLD == nLDID)
					&& (strcmp(pDsMember->strPrefix, CSCDLNinstList.at(pDOI->nIdLNinst-1).prefix)==0)
					&& (strcmp(pDsMember->strLnClass, CSCDLNinstList.at(pDOI->nIdLNinst-1).lnClass)==0)
					&& (strcmp(pDsMember->strLnInst, CSCDLNinstList.at(pDOI->nIdLNinst-1).strInst)==0))
				{
					char tempStr1[256], tempStr2[256];

					strcpy(tempStr1, pDOI->strName);
					strcat(tempStr1, "$");
					strcat(tempStr1, pDAI->daiName);

					strcpy(tempStr2, pDsMember->strDoName);
					strcat(tempStr2, "$");
					strcat(tempStr2, pDsMember->strDaName);
					for (int i=0; i<strlen(tempStr2); i++)
					{
						if (tempStr2[i] == '.') tempStr2[i] = '$';
					}

					if (strstr(tempStr1, tempStr2) != 0)
					{
						pDAI->nDsMember = pDsMember->nId; 
						pDsMember->nDAI = pDAI->nId;
					}
				}
			}
			
			CSCDDsMemberList.push_back(*pDsMember);
			free(pDsMember);
			
			nSeqMember++;
			pFCDAElement = pFCDAElement->NextSiblingElement("FCDA");
		}
		
		CSCDDataSetList.push_back(*pDataSet);
		free(pDataSet);

		pDataSetElement = pDataSetElement->NextSiblingElement("DataSet");
	}

	return true;
}

//解析ReportControl
bool ParseReportControl(TiXmlElement *pLN0Element, const int nIEDID, const int nLDID, const int nLNinstID)
{
	TiXmlElement *pReportControlElement = pLN0Element->FirstChildElement("ReportControl");
	while (pReportControlElement)
	{
		CRptCtrl *pRptCtrl = (CRptCtrl *)calloc(1, sizeof(CRptCtrl));
		pRptCtrl->nId = CSCDRptCtrlList.size() + 1;
		pRptCtrl->nIdIED = nIEDID;
		pRptCtrl->nIdLD = nLDID;
		pRptCtrl->nIdLNinst = nLNinstID;
		pRptCtrl->nIdDS = -1;
		
		if (pReportControlElement->Attribute("name"))
		{
			strcpy(pRptCtrl->strName,pReportControlElement->Attribute("name"));
		}
		if (pReportControlElement->Attribute("rptID"))
		{
			strcpy(pRptCtrl->strRptID,pReportControlElement->Attribute("rptID"));
		}
		if (pReportControlElement->Attribute("desc"))
		{
			strcpy(pRptCtrl->strDesc,pReportControlElement->Attribute("desc"));
		}
		if (pReportControlElement->Attribute("confRev"))
		{
			pRptCtrl->nConfRev = atoi(pReportControlElement->Attribute("confRev"));
		}
		if (pReportControlElement->Attribute("bufTime"))
		{
			pRptCtrl->nBufTime = atoi(pReportControlElement->Attribute("bufTime"));
		}
		if (pReportControlElement->Attribute("intgPd"))
		{
			pRptCtrl->nIntgPd = atoi(pReportControlElement->Attribute("intgPd"));
		}
		if (pReportControlElement->Attribute("buffered"))
		{
			if( !strcmp(pReportControlElement->Attribute("buffered"),"true") ) pRptCtrl->isBuffered = true;
		}
		if (pReportControlElement->Attribute("datSet"))
		{
			for( vector<CDataSet>::iterator dsIter=CSCDDataSetList.begin(); dsIter!=CSCDDataSetList.end();dsIter++ )
			{
				if( dsIter->nIdIED == nIEDID && dsIter->nIdLD == nLDID 
					&& strcmp(dsIter->strName,pReportControlElement->Attribute("datSet")) == 0 )
				{
					pRptCtrl->nIdDS = dsIter->nId;
				}
			}
		}

		TiXmlElement *pTrgOpsElement = pReportControlElement->FirstChildElement("TrgOps");
		if( pTrgOpsElement )
		{
			if( pTrgOpsElement->Attribute("dchg") )
			{
				if( !strcmp(pTrgOpsElement->Attribute("dchg"),"true") )	pRptCtrl->bTrgOps |= 0x08;
			}
			if( pTrgOpsElement->Attribute("qchg") )
			{
				if( !strcmp(pTrgOpsElement->Attribute("qchg"),"true") )	pRptCtrl->bTrgOps |= 0x04;
			}
			if( pTrgOpsElement->Attribute("dupd") )
			{
				if( !strcmp(pTrgOpsElement->Attribute("dupd"),"true") ) pRptCtrl->bTrgOps |= 0x02;
			}
			if( pTrgOpsElement->Attribute("period") )
			{
				if( !strcmp(pTrgOpsElement->Attribute("period"),"true") ) pRptCtrl->bTrgOps |= 0x01;
			}
		}

		TiXmlElement *pOptFieldsElement = pReportControlElement->FirstChildElement("OptFields");
		if( pOptFieldsElement )
		{
			if( pOptFieldsElement->Attribute("seqNum") )
			{
				if( !strcmp(pOptFieldsElement->Attribute("seqNum"),"true") ) pRptCtrl->bOptFields |= 0x80;
			}
			if( pOptFieldsElement->Attribute("timeStamp") )
			{
				if( !strcmp(pOptFieldsElement->Attribute("timeStamp"),"true") ) pRptCtrl->bOptFields |= 0x40;
			}
			if( pOptFieldsElement->Attribute("reasonCode") )
			{
				if( !strcmp(pOptFieldsElement->Attribute("reasonCode"),"true") ) pRptCtrl->bOptFields |= 0x20;
			}
			if( pOptFieldsElement->Attribute("dataSet") )
			{
				if( !strcmp(pOptFieldsElement->Attribute("dataSet"),"true") ) pRptCtrl->bOptFields |= 0x10;
			}
			if( pOptFieldsElement->Attribute("dataRef") )
			{
				if( !strcmp(pOptFieldsElement->Attribute("dataRef"),"true") ) pRptCtrl->bOptFields |= 0x08;
			}
			if( pOptFieldsElement->Attribute("bufOvfl") )
			{
				if( !strcmp(pOptFieldsElement->Attribute("bufOvfl"),"true") ) pRptCtrl->bOptFields |= 0x04;
			}
			if( pOptFieldsElement->Attribute("entryID") )
			{
				if( !strcmp(pOptFieldsElement->Attribute("entryID"),"true") ) pRptCtrl->bOptFields |= 0x02;
			}
			if( pOptFieldsElement->Attribute("configRef") )
			{
				if( !strcmp(pOptFieldsElement->Attribute("configRef"),"true") ) pRptCtrl->bOptFields |= 0x01;
			}
		}
		
		TiXmlElement *pRptEnabledElement = pReportControlElement->FirstChildElement("RptEnabled");
		if( pRptEnabledElement )
		{
			if (pRptEnabledElement->Attribute("max"))
			{
				pRptCtrl->nMax = atoi(pRptEnabledElement->Attribute("max"));
			}
		}

		CSCDRptCtrlList.push_back(*pRptCtrl);
		free(pRptCtrl);
		
		pReportControlElement = pReportControlElement->NextSiblingElement("ReportControl");
	}
	return true;
}

//解析LN
bool ParseLNPart(TiXmlElement *pLDeviceElement, const int nIEDID, const int nLDID)
{
	TiXmlElement *pLNElement = pLDeviceElement->FirstChildElement("LN");
	while (pLNElement)
	{
		CLNinst *pLNinst = (CLNinst *)calloc(1, sizeof(CLNinst));
		pLNinst->nId = CSCDLNinstList.size() + 1;
		pLNinst->nStart = CSCDDOIList.size() + 1;
		pLNinst->nType = 1;
//		pLNinst->nIdIED = nIEDID;
		pLNinst->nIdLD = nLDID;
		pLNinst->nLnType_id = -1;
		
		//获取LN节点的LNTYPE_ID
		if (pLNElement->Attribute("lnType"))
		{
			strcpy(pLNinst->lnType,pLNElement->Attribute("lnType"));
			
			vector<CLnType>::iterator LTIter=CSCDLnTypeList.begin();
			for (LTIter;LTIter!=CSCDLnTypeList.end(); ++LTIter)
			{
				if (strcmp(LTIter->strType,pLNElement->Attribute("lnType"))==0)
				{
					pLNinst->nLnType_id = LTIter->nId;
					break;
				}
			}
		}
		
		if (pLNElement->Attribute("lnClass"))
		{
			strcpy(pLNinst->lnClass,pLNElement->Attribute("lnClass"));
		}
		if (pLNElement->Attribute("prefix"))
		{
			strcpy(pLNinst->prefix,pLNElement->Attribute("prefix"));
		}
		if (pLNElement->Attribute("inst"))
		{
			strcpy(pLNinst->strInst,pLNElement->Attribute("inst"));
		}
		if (pLNElement->Attribute("desc"))
		{
			strcpy(pLNinst->strDesc,pLNElement->Attribute("desc"));
		}
		
		CSCDLNinstList.push_back(*pLNinst);
		
		//解析DOI部分
		ParseDOI(pLNElement, nIEDID, nLDID, pLNinst->nId, pLNinst->nLnType_id);
		
		free(pLNinst);
		
		pLNElement = pLNElement->NextSiblingElement("LN");
	}
	return true;
}

//解析LN0
bool ParseLN0Part(TiXmlElement *pLDeviceElement, const int nIEDID, const int nLDID)
{
	TiXmlElement *pLN0Element = pLDeviceElement->FirstChildElement("LN0");
	if (pLN0Element)
	{
		CLNinst *pLNinst = (CLNinst *)calloc(1, sizeof(CLNinst));
		pLNinst->nId = CSCDLNinstList.size() + 1;
		pLNinst->nType = 0;
//		pLNinst->nIdIED = nIEDID;
		pLNinst->nIdLD = nLDID;
		pLNinst->nLnType_id = -1;

		int nLNTypeID = -1;

		//获取LN0节点的LNTYPE_ID
		if (pLN0Element->Attribute("lnType"))
		{
			strcpy(pLNinst->lnType,pLN0Element->Attribute("lnType"));

			vector<CLnType>::iterator LTIter=CSCDLnTypeList.begin();
			for (LTIter;LTIter!=CSCDLnTypeList.end(); ++LTIter)
			{
				if (strcmp(LTIter->strType,pLN0Element->Attribute("lnType"))==0)
				{
					nLNTypeID = LTIter->nId;
					break;
				}
			}
		}
		
		pLNinst->nLnType_id = nLNTypeID;
		
		if (pLN0Element->Attribute("lnClass"))
		{
			strcpy(pLNinst->lnClass,pLN0Element->Attribute("lnClass"));
		}
		if (pLN0Element->Attribute("prefix"))
		{
				strcpy(pLNinst->prefix,pLN0Element->Attribute("prefix"));
		}
		if (pLN0Element->Attribute("inst"))
		{
			strcpy(pLNinst->strInst,pLN0Element->Attribute("inst"));
		}
		
		CSCDLNinstList.push_back(*pLNinst);
		free(pLNinst);
		int pn = CSCDLNinstList.size(); //保存该记录的位置，以便之后设置部分字段值

		//解析LN （必须在下列解析之前）
		ParseLNPart(pLDeviceElement,nIEDID,nLDID);

		//设置部分字段值 （由于解析LN时相关容器添加了记录，故下列字段必须在解析LN之后设置）
		pLNinst = &CSCDLNinstList.at(pn-1); 
		pLNinst->nStart = CSCDDOIList.size() + 1;
		pLNinst->nStart_LN0[0] = CSCDDataSetList.size() + 1;
		pLNinst->nStart_LN0[1] = CSCDRptCtrlList.size() + 1;
		pLNinst->nStart_LN0[2] = CSCDLLNOList.size() + 1;

		//解析DOI部分
		ParseDOI(pLN0Element, nIEDID, nLDID, pLNinst->nId, pLNinst->nLnType_id);
		
		//解析DataSet
		ParseDataSet(pLN0Element, nIEDID, nLDID, pLNinst->nId);
		
		//解析ReportControl
		ParseReportControl(pLN0Element, nIEDID, nLDID, pLNinst->nId);
		
		//解析SettingControl,GSEControl,SampledValueControl
		int nNumofSGs = -1;
		int nActSG = -1;
		int nDsSetting_id = -1;
		TiXmlElement *pSettingControlElement = pLN0Element->FirstChildElement("SettingControl");
		if (pSettingControlElement)
		{
			for (vector<CDataSet>::iterator dsIter=CSCDDataSetList.begin(); dsIter!=CSCDDataSetList.end();++dsIter)
			{
				if( dsIter->nIdIED == nIEDID && dsIter->nIdLD == nLDID && strcmp(dsIter->strName,"dsSetting") == 0 )
				{
					nDsSetting_id = dsIter->nId;
				}
			}
			if (pSettingControlElement->Attribute("actSG"))
			{
				nActSG = atoi(pSettingControlElement->Attribute("actSG"));
			}
			if (pSettingControlElement->Attribute("numOfSGs"))
			{
				nNumofSGs = atoi(pSettingControlElement->Attribute("numOfSGs"));
			}
		}
		
		TiXmlElement *pGSEControlElement = pLN0Element->FirstChildElement("GSEControl");
		TiXmlElement *pSampledValueControlElement = pLN0Element->FirstChildElement("SampledValueControl");

		//当GSEControl和SampledValueControl节点都没有时
		if ((!pGSEControlElement) && (!pSampledValueControlElement))
		{
			CLLNO *pLLN0 = (CLLNO *)calloc(1, sizeof(CLLNO));
			pLLN0->nId = CSCDLLNOList.size() + 1;
			pLLN0->nIdIED = nIEDID;
			pLLN0->nIdLD = nLDID;
			pLLN0->nIdLNinst = pLNinst->nId;
			pLLN0->nLnType_id = nLNTypeID;
			pLLN0->nType = 0;
			pLLN0->nDsID = -1;
			pLLN0->nNumofSGs = nNumofSGs;
			pLLN0->nActSG = nActSG;
			pLLN0->nDsSetting_id = nDsSetting_id;
			
			CSCDLLNOList.push_back(*pLLN0);
			free(pLLN0);
		}
		
		//解析GSEControl节点
		while (pGSEControlElement)
		{
			CLLNO *pLLN0 = (CLLNO *)calloc(1, sizeof(CLLNO));
			pLLN0->nId = CSCDLLNOList.size() + 1;
			pLLN0->nIdIED = nIEDID;
			pLLN0->nIdLD = nLDID;
			pLLN0->nIdLNinst = pLNinst->nId;
			pLLN0->nLnType_id = nLNTypeID;
			pLLN0->nType = 1;
			pLLN0->nDsID = -1;
			pLLN0->nNumofSGs = nNumofSGs;
			pLLN0->nActSG = nActSG;
			pLLN0->nDsSetting_id = nDsSetting_id;
			pLLN0->isGoose = true;
			
			if (pGSEControlElement->Attribute("datSet"))
			{
				for (vector<CDataSet>::iterator dsIter=CSCDDataSetList.begin(); dsIter != CSCDDataSetList.end(); ++dsIter)
				{
					if ((strcmp(dsIter->strName,pGSEControlElement->Attribute("datSet"))==0)
                        &&(nIEDID==dsIter->nIdIED)
                        &&(nLDID==dsIter->nIdLD))
					{
						pLLN0->nDsID = dsIter->nId;
						break;
					}
				}
			}
			
			if (pGSEControlElement->Attribute("name"))
			{
				strcpy(pLLN0->strName,pGSEControlElement->Attribute("name"));
			}
			if (pGSEControlElement->Attribute("desc"))
			{
				strcpy(pLLN0->strDesc,pGSEControlElement->Attribute("desc"));
			}
			if (pGSEControlElement->Attribute("appID"))
			{
				strcpy(pLLN0->strAppID,pGSEControlElement->Attribute("appID"));
			}
			if (pGSEControlElement->Attribute("confRev"))
			{
				pLLN0->nConfRev = atoi(pGSEControlElement->Attribute("confRev"));
			}
			if (pGSEControlElement->Attribute("type"))
			{
				if( !strcmp(pGSEControlElement->Attribute("type"),"GSSE") ) pLLN0->isGoose = false;
			}
			
			CSCDLLNOList.push_back(*pLLN0);
			free(pLLN0);
			
			pGSEControlElement = pGSEControlElement->NextSiblingElement("GSEControl");
		}

		//解析SampledValueControl节点
		while (pSampledValueControlElement)
		{
			CLLNO *pLLN0 = (CLLNO *)calloc(1, sizeof(CLLNO));
			pLLN0->nId = CSCDLLNOList.size() + 1;
			pLLN0->nIdIED = nIEDID;
			pLLN0->nIdLD = nLDID;
			pLLN0->nIdLNinst = pLNinst->nId;
			pLLN0->nLnType_id = nLNTypeID;
			pLLN0->nType = 2;
			pLLN0->nDsID = -1;
			pLLN0->nNumofSGs = nNumofSGs;
			pLLN0->nActSG = nActSG;
			pLLN0->nDsSetting_id = nDsSetting_id;
			pLLN0->isMulticast = true;
			
			if (pSampledValueControlElement->Attribute("datSet"))
			{
				for (vector<CDataSet>::iterator dsIter=CSCDDataSetList.begin(); dsIter != CSCDDataSetList.end(); ++dsIter)
				{
					if (strcmp(dsIter->strName,pSampledValueControlElement->Attribute("datSet"))==0
                        &&(nIEDID==dsIter->nIdIED)
                        &&(nLDID==dsIter->nIdLD))
					{
						pLLN0->nDsID = dsIter->nId;
						break;
					}
				}
			}
			
			if (pSampledValueControlElement->Attribute("name"))
			{
				strcpy(pLLN0->strName,pSampledValueControlElement->Attribute("name"));
			}							
			if (pSampledValueControlElement->Attribute("desc"))
			{
				strcpy(pLLN0->strDesc,pSampledValueControlElement->Attribute("desc"));
			}							
			if (pSampledValueControlElement->Attribute("smvID"))
			{
				strcpy(pLLN0->strAppID,pSampledValueControlElement->Attribute("smvID"));
			}
			if (pSampledValueControlElement->Attribute("confRev"))
			{
				pLLN0->nConfRev = atoi(pSampledValueControlElement->Attribute("confRev"));
			}
			if (pSampledValueControlElement->Attribute("smpRate"))
			{
				pLLN0->nSmpRate = atoi(pSampledValueControlElement->Attribute("smpRate"));
			}
			if (pSampledValueControlElement->Attribute("nofASDU"))
			{
				pLLN0->nNofASDU = atoi(pSampledValueControlElement->Attribute("nofASDU"));
			}
			if (pSampledValueControlElement->Attribute("multicast"))
			{
				if( !strcmp(pSampledValueControlElement->Attribute("multicast"),"false") )
					pLLN0->isMulticast = false;
			}
			
			TiXmlElement *pSmvOptsElement = pSampledValueControlElement->FirstChildElement("SmvOpts");
			if( pSmvOptsElement )
			{
				if( pSmvOptsElement->Attribute("sampleRate") )
				{
					if( !strcmp(pSmvOptsElement->Attribute("sampleRate"),"true") ) pLLN0->bSmvOpts |= 0x10;
				}
				if( pSmvOptsElement->Attribute("refreshTime") )
				{
					if( !strcmp(pSmvOptsElement->Attribute("refreshTime"),"true") ) pLLN0->bSmvOpts |= 0x08;
				}
				if( pSmvOptsElement->Attribute("sampleSynchronized") )
				{
					if( !strcmp(pSmvOptsElement->Attribute("sampleSynchronized"),"true") ) pLLN0->bSmvOpts |= 0x04;
				}
				if( pSmvOptsElement->Attribute("security") )
				{
					if( !strcmp(pSmvOptsElement->Attribute("security"),"true") ) pLLN0->bSmvOpts |= 0x02;
				}
				if( pSmvOptsElement->Attribute("dataRef") )
				{
					if( !strcmp(pSmvOptsElement->Attribute("dataRef"),"true") ) pLLN0->bSmvOpts |= 0x01;
				}
			}

			CSCDLLNOList.push_back(*pLLN0);
			free(pLLN0);
			
			pSampledValueControlElement = pSampledValueControlElement->NextSiblingElement("SampledValueControl");
		}
	}
	return true;
}

//解析AccessPoint部分（bAPName为true时只解析APName）
bool ParseAccessPoint(TiXmlElement* pIEDElement,const int nIEDID, int &nAPNum, char *strAPNames, bool bAPName)
{
	TiXmlElement *pAccessPointElement = pIEDElement->FirstChildElement("AccessPoint");
	
	while (pAccessPointElement)
	{
		char strAPName[MAX_DESC_LEN]={0};
		if (pAccessPointElement->Attribute("name"))
		{
			strcpy(strAPName,pAccessPointElement->Attribute("name"));
			strcat(strAPNames,strAPName);
			strcat(strAPNames,"/");
		}

		if (!bAPName)
		{
			TiXmlElement *pServerElement = pAccessPointElement->FirstChildElement("Server");
			if (pServerElement)
			{
				TiXmlElement *pLDeviceElement = pServerElement->FirstChildElement("LDevice");
				while (pLDeviceElement)
				{
					CLD *pLD = (CLD *)calloc(1, sizeof(CLD));
					pLD->nId = CSCDLDList.size() + 1;
					pLD->nStart = CSCDLNinstList.size() + 1;
					pLD->nIdIED = nIEDID;
					
					strcpy(pLD->strAPName,strAPName);
					if (pLDeviceElement->Attribute("inst"))
					{
						strcpy(pLD->strName,pLDeviceElement->Attribute("inst"));
					}
					if (pLDeviceElement->Attribute("desc"))
					{
						strcpy(pLD->strDesc,pLDeviceElement->Attribute("desc"));
					}
					
					//解析LN
					//ParseLNPart(pLDeviceElement,nIEDID,pLD->nId);
					
					//解析LN0
					ParseLN0Part(pLDeviceElement,nIEDID,pLD->nId);
					
					CSCDLDList.push_back(*pLD);
					free(pLD);
					
					pLDeviceElement = pLDeviceElement->NextSiblingElement("LDevice");
				}
			}
		}

		nAPNum ++;
		pAccessPointElement = pAccessPointElement->NextSiblingElement("AccessPoint");
	}
	
	return true;
}

//解析IED部分（iedName为NULL时只解析IED条目，iedName为空时解析第一个IED信息，否则解析指定的IED信息）
bool ParseIED(TiXmlElement* pSCLElement, char *iedName)
{
	bool parseOK = false;
	bool bAPName = true;

	TiXmlElement *pIEDElement = pSCLElement->FirstChildElement("IED");	
	while (pIEDElement)
	{
		CIED *pIED = (CIED *)calloc(1, sizeof(CIED));
		pIED->nId = CSCDIEDList.size() + 1;
		pIED->nStart = CSCDLDList.size() + 1;

		if (pIEDElement->Attribute("name"))
		{
			strcpy(pIED->strName,pIEDElement->Attribute("name"));
		}
		
		if( iedName == NULL || strlen(iedName) == 0 || strcmp(pIED->strName, iedName) == 0 )
		{
			if (pIEDElement->Attribute("desc"))
			{
				strcpy(pIED->strDesc,pIEDElement->Attribute("desc"));
			}
			
			if (pIEDElement->Attribute("configVersion"))
			{
				strcpy(pIED->strCFGVersion,pIEDElement->Attribute("configVersion"));
			}
			
			if (pIEDElement->Attribute("type"))
			{
				strcpy(pIED->strType,pIEDElement->Attribute("type"));
			}
			
			if (pIEDElement->Attribute("manufacturer"))
			{
				strcpy(pIED->strManufacture,pIEDElement->Attribute("manufacturer"));
			}
			
			if( iedName != NULL )
			{
				bAPName = false;
				parseOK = true;
			}

			int nAPNum = 0;
			char strAPNames[MAX_DESC_LEN]={0};
			
			ParseAccessPoint(pIEDElement,pIED->nId,nAPNum,strAPNames,bAPName);
			
			pIED->napNum = nAPNum;
			strcpy(pIED->strAPName,strAPNames);

			CSCDIEDList.push_back(*pIED);
		}

		free(pIED);
		if( parseOK ) break;

		pIEDElement = pIEDElement->NextSiblingElement("IED");
	}

	return (CSCDIEDList.size() > 0);
}


//解析Communication部分
bool ParseCommunication(TiXmlElement* pSCLElement)
{
	TiXmlElement* pCommunicationElement = pSCLElement->FirstChildElement("Communication");
	
	if (pCommunicationElement)
	{
		TiXmlElement* pSubNetworkElement = pCommunicationElement->FirstChildElement("SubNetwork");
		while (pSubNetworkElement)
		{
			CNetConfig *pNetConfig = (CNetConfig *)calloc(1, sizeof(CNetConfig));
			pNetConfig->nId = CSCDNetConfigList.size() + 1;
			pNetConfig->nStart = CSCDCommConfigList.size() + 1;

			if (pSubNetworkElement->Attribute("name"))
			{
				strcpy(pNetConfig->chNetName,pSubNetworkElement->Attribute("name"));
			}
			
			TiXmlElement *pBitRateElement = pSubNetworkElement->FirstChildElement("BitRate");
			if (pBitRateElement)
			{
				if (pBitRateElement->GetText())
				{
					pNetConfig->nBitRate = atoi(pBitRateElement->GetText());
				}
			}
			
			if (pSubNetworkElement->Attribute("type"))
			{
				strcpy(pNetConfig->chNetProtocol,pSubNetworkElement->Attribute("type"));
			}

			if (!strcmp(pNetConfig->chNetProtocol, ""))
			{
				strcpy(pNetConfig->chNetProtocol, pNetConfig->chNetName);
			}
				
			if (strstr(pNetConfig->chNetProtocol,"MMS") != 0)
			{
				strcpy(pNetConfig->chNetType,"MMS");
			}
			else if (strstr(pNetConfig->chNetProtocol,"GOOSE") != 0)
			{
				strcpy(pNetConfig->chNetType,"GOOSE");
			}
			else if (strstr(pNetConfig->chNetProtocol,"SMV") != 0)
			{
				strcpy(pNetConfig->chNetType,"SMV");
			}
			
			TiXmlElement *pConnectedAPElement = pSubNetworkElement->FirstChildElement("ConnectedAP");
			while (pConnectedAPElement)
			{
				char strApName[MAX_DESC_LEN] = {0};
				if (pConnectedAPElement->Attribute("apName"))
				{
					strcpy(strApName,pConnectedAPElement->Attribute("apName"));
				}

				if (!strcmp(pNetConfig->chNetType, ""))
				{
					if (strApName[0] == 'S')
						strcpy(pNetConfig->chNetType,"MMS");
					else if (strApName[0] == 'G')
						strcpy(pNetConfig->chNetType,"GOOSE");
					else if (strApName[0] == 'M')
						strcpy(pNetConfig->chNetType,"SMV");
				}

				if (!strcmp(pNetConfig->chNetType,"MMS"))
				{
					CCommConfig *pCommConfig = (CCommConfig *)calloc(1, sizeof(CCommConfig));
					pCommConfig->nId = CSCDCommConfigList.size() + 1;
					pCommConfig->nIdSubNet = pNetConfig->nId;
					
					pCommConfig->nMaxTime = 0;
					pCommConfig->nMinTime = 0;
					
					if (pConnectedAPElement->Attribute("iedName"))
					{
						strcpy(pCommConfig->strIEDName,pConnectedAPElement->Attribute("iedName"));
					}
					
					if (pConnectedAPElement->Attribute("desc"))
					{
						strcpy(pCommConfig->strConnectedAP,pConnectedAPElement->Attribute("desc"));
					}
					
					if (pConnectedAPElement->Attribute("apName"))
					{
						strcpy(pCommConfig->strApName,pConnectedAPElement->Attribute("apName"));
					}
					
					TiXmlElement *pAddressElement = pConnectedAPElement->FirstChildElement("Address");
					if (pAddressElement)
					{
						TiXmlElement *pPElement = pAddressElement->FirstChildElement("P");
						while (pPElement)
						{							
							if (strcmp(pPElement->Attribute("type"),"OSI-AP-Title") == 0)
							{
								if (pPElement->GetText())
								{
									strcpy(pCommConfig->strOSI_AP_Title,pPElement->GetText());
								}
							}
							else if (strcmp(pPElement->Attribute("type"),"OSI-AE-Qualifier") == 0)
							{
								if (pPElement->GetText())
								{
									strcpy(pCommConfig->strOSI_AE_Qualifier,pPElement->GetText());
								}
							}
							else if (strcmp(pPElement->Attribute("type"),"OSI-PSEL") == 0)
							{
								if (pPElement->GetText())
								{
									strcpy(pCommConfig->strOSI_PSEL,pPElement->GetText());
								}
							}
							else if (strcmp(pPElement->Attribute("type"),"OSI-SSEL") == 0)
							{
								if (pPElement->GetText())
								{
									strcpy(pCommConfig->strOSI_SSEL,pPElement->GetText());
								}
							}
							else if (strcmp(pPElement->Attribute("type"),"OSI-TSEL") == 0)
							{
								if (pPElement->GetText())
								{
									strcpy(pCommConfig->strOSI_TSEL,pPElement->GetText());
								}
							}
							else if (strcmp(pPElement->Attribute("type"),"IP") == 0)
							{
								if (pPElement->GetText())
								{
									strcpy(pCommConfig->strIPAdder,pPElement->GetText());
								}
							}
							else if (strcmp(pPElement->Attribute("type"),"IP-SUBNET") == 0)
							{
								if (pPElement->GetText())
								{
									strcpy(pCommConfig->strIP_Subnet,pPElement->GetText());
								}
							}
							
							pPElement = pPElement->NextSiblingElement("P");
						}
					}

					CSCDCommConfigList.push_back(*pCommConfig);
					free(pCommConfig);
				}
				else if (!strcmp(pNetConfig->chNetType,"GOOSE"))
				{
					TiXmlElement *pGSEElement = pConnectedAPElement->FirstChildElement("GSE");
					while (pGSEElement)
					{
						CCommConfig *pCommConfig = (CCommConfig *)calloc(1, sizeof(CCommConfig));
						pCommConfig->nId = CSCDCommConfigList.size() + 1;
						pCommConfig->nIdSubNet = pNetConfig->nId;
						
						pCommConfig->nMaxTime = 0;
						pCommConfig->nMinTime = 0;
						
						if (pConnectedAPElement->Attribute("iedName"))
						{
							strcpy(pCommConfig->strIEDName,pConnectedAPElement->Attribute("iedName"));
						}
						
						if (pConnectedAPElement->Attribute("desc"))
						{
							strcpy(pCommConfig->strConnectedAP,pConnectedAPElement->Attribute("desc"));
						}
						
						if (pConnectedAPElement->Attribute("apName"))
						{
							strcpy(pCommConfig->strApName,pConnectedAPElement->Attribute("apName"));
						}
						
						if (pGSEElement->Attribute("cbName"))
						{
							strcpy(pCommConfig->strGseOrSmvCbName,pGSEElement->Attribute("cbName"));
						}
						
						if (pGSEElement->Attribute("desc"))
						{
							strcpy(pCommConfig->strGseOrSmvDesc,pGSEElement->Attribute("desc"));
						}
						
						if (pGSEElement->Attribute("ldInst"))
						{
							strcpy(pCommConfig->strLdInst,pGSEElement->Attribute("ldInst"));
						}
						
						TiXmlElement *pAddressElement = pGSEElement->FirstChildElement("Address");
						if (pAddressElement)
						{
							TiXmlElement *pPElement = pAddressElement->FirstChildElement("P");
							while (pPElement)
							{							
								if (strcmp(pPElement->Attribute("type"),"MAC-Address") == 0)
								{
									if (pPElement->GetText())
									{
										strcpy(pCommConfig->strMACAddr,pPElement->GetText());
									}
								}
								else if (strcmp(pPElement->Attribute("type"),"VLAN-ID") == 0)
								{
									if (pPElement->GetText())
									{
										pCommConfig->nVlan_ID = atoi(pPElement->GetText());
									}
								}
								else if (strcmp(pPElement->Attribute("type"),"VLAN-PRIORITY") == 0)
								{
									if (pPElement->GetText())
									{
										pCommConfig->nVLAN_PRIORITY = atoi(pPElement->GetText());
									}
								}
								else if (strcmp(pPElement->Attribute("type"),"APPID") == 0)
								{
									if (pPElement->GetText())
									{
										strcpy(pCommConfig->strAppID,pPElement->GetText());
									}
								}
								
								TiXmlElement *pMinTimeElement = pGSEElement->FirstChildElement("MinTime");
								if (pMinTimeElement)
								{
									if (pMinTimeElement->GetText())
									{
										pCommConfig->nMinTime = atoi(pMinTimeElement->GetText());
									}
								}
								
								TiXmlElement *pMaxTimeElement = pGSEElement->FirstChildElement("MaxTime");
								if (pMaxTimeElement)
								{
									if (pMaxTimeElement->GetText())
									{
										pCommConfig->nMaxTime = atoi(pMaxTimeElement->GetText());
									}
								}
								
								pPElement = pPElement->NextSiblingElement("P");
							}
						}

						CSCDCommConfigList.push_back(*pCommConfig);
						free(pCommConfig);

						pGSEElement = pConnectedAPElement->NextSiblingElement("GSE");
					}
				}
				else if (!strcmp(pNetConfig->chNetType,"SMV"))
				{
					TiXmlElement *pSMVElement = pConnectedAPElement->FirstChildElement("SMV");
					while (pSMVElement)
					{
						CCommConfig *pCommConfig = (CCommConfig *)calloc(1, sizeof(CCommConfig));
						pCommConfig->nId = CSCDCommConfigList.size() + 1;
						
						pCommConfig->nMaxTime = 0;
						pCommConfig->nMinTime = 0;
						
						if (pConnectedAPElement->Attribute("iedName"))
						{
							strcpy(pCommConfig->strIEDName,pConnectedAPElement->Attribute("iedName"));
						}
						
						if (pConnectedAPElement->Attribute("desc"))
						{
							strcpy(pCommConfig->strConnectedAP,pConnectedAPElement->Attribute("desc"));
						}
						
						if (pConnectedAPElement->Attribute("apName"))
						{
							strcpy(pCommConfig->strApName,pConnectedAPElement->Attribute("apName"));
						}
						
						if (pSMVElement->Attribute("cbName"))
						{
							strcpy(pCommConfig->strGseOrSmvCbName,pSMVElement->Attribute("cbName"));
						}
						
						if (pSMVElement->Attribute("desc"))
						{
							strcpy(pCommConfig->strGseOrSmvDesc,pSMVElement->Attribute("desc"));
						}
						
						if (pSMVElement->Attribute("ldInst"))
						{
							strcpy(pCommConfig->strLdInst,pSMVElement->Attribute("ldInst"));
						}
						
						TiXmlElement *pAddressElement = pSMVElement->FirstChildElement("Address");
						if (pAddressElement)
						{
							TiXmlElement *pPElement = pAddressElement->FirstChildElement("P");
							while (pPElement)
							{							
								if (strcmp(pPElement->Attribute("type"),"MAC-Address") == 0)
								{
									if (pPElement->GetText())
									{
										strcpy(pCommConfig->strMACAddr,pPElement->GetText());
									}
								}
								else if (strcmp(pPElement->Attribute("type"),"VLAN-ID") == 0)
								{
									if (pPElement->GetText())
									{
										pCommConfig->nVlan_ID = atoi(pPElement->GetText());
									}
								}
								else if (strcmp(pPElement->Attribute("type"),"VLAN-PRIORITY") == 0)
								{
									if (pPElement->GetText())
									{
										pCommConfig->nVLAN_PRIORITY = atoi(pPElement->GetText());
									}
								}
								else if (strcmp(pPElement->Attribute("type"),"APPID") == 0)
								{
									if (pPElement->GetText())
									{
										strcpy(pCommConfig->strAppID,pPElement->GetText());
									}
								}
								
								TiXmlElement *pMinTimeElement = pSMVElement->FirstChildElement("MinTime");
								if (pMinTimeElement)
								{
									if (pMinTimeElement->GetText())
									{
										pCommConfig->nMinTime = atoi(pMinTimeElement->GetText());
									}
								}
								
								TiXmlElement *pMaxTimeElement = pSMVElement->FirstChildElement("MaxTime");
								if (pMaxTimeElement)
								{
									if (pMaxTimeElement->GetText())
									{
										pCommConfig->nMaxTime = atoi(pMaxTimeElement->GetText());
									}
								}
								
								pPElement = pPElement->NextSiblingElement("P");
							}
						}
						
						CSCDCommConfigList.push_back(*pCommConfig);
						free(pCommConfig);
						
						pSMVElement = pSMVElement->NextSiblingElement("SMV");
					}
				}

				pConnectedAPElement = pConnectedAPElement->NextSiblingElement("ConnectedAP");
			}

			CSCDNetConfigList.push_back(*pNetConfig);
			free(pNetConfig);
			
			pSubNetworkElement = pSubNetworkElement->NextSiblingElement("SubNetwork");
		}
	}
	
	return true;
}

// 解析Header部分
bool ParseHeader(TiXmlElement* pSCLElement)
{
	TiXmlElement* pHeaderElement = pSCLElement->FirstChildElement("Header");
	
	if (!pHeaderElement)
	{
		return false;
	}
	
	CHeaderConfig *pHeaderConfig = (CHeaderConfig *)calloc(1, sizeof(CHeaderConfig));
	pHeaderConfig->nId = CSCDHeaderConfigList.size() + 1;

	if (pHeaderElement->Attribute("id"))
	{
		strcpy(pHeaderConfig->strID,pHeaderElement->Attribute("id"));
	}
	
	if (pHeaderElement->Attribute("nameStructure"))
	{
		strcpy(pHeaderConfig->strNameStruct,pHeaderElement->Attribute("nameStructure"));
	}
	
	if (pHeaderElement->Attribute("revision"))
	{
		strcpy(pHeaderConfig->strRevision,pHeaderElement->Attribute("revision"));
	}
	
	if (pHeaderElement->Attribute("toolID"))
	{
		strcpy(pHeaderConfig->strToolID,pHeaderElement->Attribute("toolID"));
	}
	
	if (pHeaderElement->Attribute("version"))
	{
		strcpy(pHeaderConfig->strVersion,pHeaderElement->Attribute("version"));
	}
	
	CSCDHeaderConfigList.push_back(*pHeaderConfig);
	free(pHeaderConfig);
	
	TiXmlElement *pHistoryElement = pHeaderElement->FirstChildElement("History");
	if (pHistoryElement)
	{
		TiXmlElement *pHitemElement = pHistoryElement->FirstChildElement("Hitem");
		while (pHitemElement)
		{
			CHistoryConfig *pHistoryConfig = (CHistoryConfig *)calloc(1, sizeof(CHistoryConfig));
			pHistoryConfig->nId = CSCDHistoryConfigList.size() + 1;

			if (pHitemElement->Attribute("revision"))
			{
				strcpy(pHistoryConfig->strRevision,pHitemElement->Attribute("revision"));
			}
			
			if (pHitemElement->Attribute("version"))
			{
				strcpy(pHistoryConfig->strVersion,pHitemElement->Attribute("version"));
			}
			
			if (pHitemElement->Attribute("what"))
			{
				strcpy(pHistoryConfig->strWhat,pHitemElement->Attribute("what"));
			}
			
			if (pHitemElement->Attribute("when"))
			{
				strcpy(pHistoryConfig->strWhen,pHitemElement->Attribute("when"));
			}
			
			if (pHitemElement->Attribute("who"))
			{
				strcpy(pHistoryConfig->strWho,pHitemElement->Attribute("who"));
			}
			
			if (pHitemElement->Attribute("why"))
			{
				strcpy(pHistoryConfig->strWhy,pHitemElement->Attribute("why"));
			}
			
			CSCDHistoryConfigList.push_back(*pHistoryConfig);
			free(pHistoryConfig);
			
			pHitemElement = pHitemElement->NextSiblingElement("Hitem");
		}
	}
	
	return true;
}


//解析SCD（iedName为NULL时只解析IED条目，iedName为空时解析第一个IED信息，否则解析指定的IED信息）
int ParseSCD(char *iedName, char *scdFilePath)
{
	if( Scd_Doc == NULL || strcmp(Scd_File, scdFilePath) )
	{
		if( Scd_Doc ) delete Scd_Doc;
		Scd_Doc = new TiXmlDocument();
		if( !Scd_Doc->LoadFile(scdFilePath) ) return -1;
		strcpy(Scd_File, scdFilePath);
		strcpy(Ied_Name, "");
		DataType_Done = false;
	}
	
	TiXmlElement* pSCLElement = Scd_Doc->FirstChildElement( "SCL" );
	
	if( iedName == NULL )	//只解析IED条目
	{
		ClearSCDList(0);

		//解析IED部分
		if (!ParseIED(pSCLElement, NULL)) return -2;

		//解析Communication部分
		if (!ParseCommunication(pSCLElement)) return -5;

		return 0;
	}

	if( !DataType_Done )
	{
		//解析DataTypeTemplates部分
		ClearSCDList(1);
		if (!ParseDataTypeTemplates(pSCLElement)) return -3;
		DataType_Done = true;
	}

	if (!strcmp(Ied_Name, "") || strcmp(Ied_Name, iedName))
	{
		strcpy(Ied_Name, "");
		//解析IED部分
		ClearSCDList(2);
		if (!ParseIED(pSCLElement, iedName)) return -4;
		strcpy(Ied_Name, iedName);
	}

/*
	if( strlen(iedName) == 0 )	//解析全部信息
	{
		ClearSCDList(3);

		//解析Communication部分
		if (!ParseCommunication(pSCLElement)) return -5;
		
		//解析Header部分
		if (!ParseHeader(pSCLElement)) return -6;
	}
*/

	return MarkDataTypeUsed();
}

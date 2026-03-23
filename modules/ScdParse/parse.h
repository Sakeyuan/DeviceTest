#ifndef _PARSE_H_
#define _PARSE_H_


#include <string>
#include <vector>
#include <map>
using namespace std;

#include ".\tinyxml\tinyxml.h"


#define BYTE	unsigned char	
#define	WORD	unsigned short		

#define MAX_CLASS_LEN	32
#define MAX_NAME_LEN	64
#define MAX_DESC_LEN	128
#define MAX_PATH_LEN	256

#define MAX_LEVEL_LEN	128
#define MAX_IP_LEN		20
#define MAX_MAC_LEN		20

#define LEVELSIZE 30 


enum _Basic_Type
{
	ENUM_TYPE_BOOLEAN=0,
		ENUM_TYPE_INT,
		ENUM_TYPE_UNSIGNED,
		ENUM_TYPE_FLOAT,
		ENUM_TYPE_OCTET, 
		ENUM_TYPE_FOCTET,
		ENUM_TYPE_FSTRING,
		ENUM_TYPE_VISIBLESTRING,
		ENUM_TYPE_QUALITY,
		ENUM_TYPE_ENTRYTIME,
		ENUM_TYPE_TIMESTAMP,
		ENUM_TYPE_BTIME6,
		ENUM_TYPE_ENUM,
		ENUM_TYPE_CODEENUM,
		ENUM_TYPE_BCD,
		ENUM_TYPE_UNICODE,
		ENUM_TYPE_BITSTRING,
		ENUM_TYPE_BRCB=0x100,
		ENUM_TYPE_URCB,
		ENUM_TYPE_SGCB,
		ENUM_TYPE_GOCB,
		ENUM_TYPE_LCB,
		ENUM_TYPE_DATASET,
		ENUM_TYPE_MEMBER,
		ENUM_TYPE_SERVER,
		ENUM_TYPE_LD,
		ENUM_TYPE_LN,
		ENUM_TYPE_FC,
		ENUM_TYPE_STRU,
		ENUM_TYPE_ACCESSPT,
		ENUM_TYPE_SUBNET,
		ENUM_TYPE_CONAP,
		ENUM_TYPE_ADDRESS,
		ENUM_TYPE_GSE,
		ENUM_TYPE_SMV
};



//=========================================================
// LNodeType
struct CLnType
{
	int  nId;
	int  nStart;
	char strType[MAX_NAME_LEN];					//id
	char strLnclass[MAX_CLASS_LEN];				//lnClass
	char strDesc[MAX_DESC_LEN];					//desc
	bool used;									//应用标志
};

// DO
struct CLnMember
{
	int  nId;
	int  nLnType_id;							//所属LNodeType号（CLnType.nId）
	int  nDoType_id;							//引用DOType号（CDoType.nId）
	char strDoName[MAX_NAME_LEN];				//name
	char strType[MAX_NAME_LEN];					//type
	char strDoDesc[MAX_DESC_LEN];				//desc
	bool used;									//应用标志
};

// DOType
struct CDoType
{
	int  nId;
	int  nStart;
	char strType[MAX_NAME_LEN];					//id
	char strCDCName[MAX_CLASS_LEN];				//cdc
	char strDesc[MAX_DESC_LEN];					//desc
	bool used;									//应用标志
};

// DA, SDO
struct CDoMember
{
	int  nId;
	int  nDotype_id;							//所属DOType号（CDoType.nId）	
	char strDaName[MAX_CLASS_LEN];				//name
	int  nKind;									//类型（0 DA，1 SDO）
	char strFC[MAX_CLASS_LEN];					//fc
	char strBType[MAX_NAME_LEN];				//bType
	char strType[MAX_NAME_LEN];					//type
	unsigned char bDchg,bQchg,bDupd;			//dchg,qchg,dupd
	int  nType_id;								//DA：bType="Struct"时为引用DAType号（CDaType.nId）
												//    bType="Enum"时为引用EnumType号（CEnumType.nId）
												//SDO：引用DOType号（CDoType.nId）
};

// DAType
struct CDaType
{
	int  nId;
	int  nStart;
    char strName[MAX_NAME_LEN];					//id
	bool used;									//应用标志
};

// BDA
struct CDaMember
{
	int  nId;
	int  nDaType_id;							//所属DAType号（CDaType.nId）
	char strName[MAX_CLASS_LEN];				//name
	char strBType[MAX_NAME_LEN];				//bType
	char strType[MAX_NAME_LEN];					//type
	int  nType_id;								//bType="Struct"时为引用DAType号（CDaType.nId）
												//bType="Enum"时为引用EnumType号（CEnumType.nId）
};

// EnumType
struct CEnumType
{
	int  nId;
	int  nStart;
	char strName[MAX_NAME_LEN];					//id
	bool used;									//应用标志
};

// EnumVal
struct CEnumMember
{
	int  nId;
	int  nEnumType_id;							//所属EnumType号（CEnumType.nId）
	char strName[MAX_NAME_LEN];					//TEXT
	int  nValue;								//ord
};

//=========================================================
// IED
struct CIED
{
	int  nId;
	int  nStart;
	char strName[MAX_NAME_LEN];					//name
	char strDesc[MAX_DESC_LEN];					//desc
	char strType[MAX_NAME_LEN];					//type
	char strCFGVersion[MAX_NAME_LEN];			//configVersion
	char strManufacture[MAX_NAME_LEN];			//manufacturer
	int  napNum;								//包含AccessPoint个数
	char strAPName[MAX_DESC_LEN];				//AccessPoint名称组合串（各名称之间用/分隔）
};

// LDevice
struct CLD
{
	int  nId;
	int  nStart;
	int  nIdIED;								//所属IED号（CIED.nId）
	char strAPName[MAX_DESC_LEN];				//所属AccessPoint之name
	char strName[MAX_NAME_LEN];					//inst
	char strDesc[MAX_DESC_LEN];					//desc
};

// LN, LN0
struct CLNinst
{
	int  nId;
	int  nStart;
	int  nStart_LN0[3];							//[0]DataSet，[1]ReportControl，[2]GSEControl, SampledValueControl
	int  nType;									//类型：0 LN0，1 LN
//	int  nIdIED;								//所属IED号（CIED.nId）
	int  nIdLD;									//所属LDevice号（CLD.nId）
    int  nLnType_id;							//引用LNodeType号（CLnType.nId）
	char lnType[MAX_NAME_LEN];					//lnType
	char lnClass[MAX_CLASS_LEN];				//lnClass
	char prefix[MAX_CLASS_LEN];					//prefix
	char strInst[MAX_NAME_LEN];					//inst
	char strDesc[MAX_DESC_LEN];					//desc
};

// DOI
struct CDOI
{
	int  nId;
	int  nStart;
	int  nIdIED;								//所属IED号（CIED.nId）
	int  nIdLD;									//所属LDevice号（CLD.nId）
	int  nIdLNinst;								//所属LN号（CLNinst.nId）
	int  nDsMember;								//关联FCDA号（CDsMember.nId） 
	int  nIdDotype;								//引用DOType号（CDoType.nId）
	char strName[MAX_NAME_LEN];					//name
	char strDesc[MAX_DESC_LEN];					//desc
	char str_dU[MAX_DESC_LEN];					//下层DAI之dU
	char str_ctlModel[MAX_NAME_LEN];			//下层DAI之ctlModel
	unsigned short doiType;						//DO属性，按位表示：0 stVal, 1 general，
												//					4 mag$f, 5 cVal$mag$f, 6 instMag$i, 7 多点cVal$mag$f
												//                  8 SBOw$ctlVal, 9 Oper$ctlVal, 10 Cancel$ctlVal, 
												//					12 setVal, 13 setMag$f）
	int  nDataType;								//数据类型（_Basic_Type）
};

// DAI, SDI
struct CDAI
{
	int  nId;
//	int  nIdIED;								//所属IED号（CIED.nId）
//	int  nIdLD;									//所属LDevice号（CLD.nId）
//	int  nIdLNinst;								//所属LN号（CLNinst.nId）
	int  nIdDOI;								//所属DOI号（CLNinst.nId）
	int  nDsMember;								//关联FCDA号（CDsMember.nId） 
    char daiName[MAX_DESC_LEN];					//DAI：name
												//SDI->DAI：各级name中间加$拼接
												//SDI->SDI->DAI：各级name中间加$拼接
												//SDI->SDI->SDI->DAI：各级name中间加$拼接
	char strSaddr[MAX_NAME_LEN];				//sAddr
	char valKind[MAX_CLASS_LEN];				//valKind
	char val[MAX_DESC_LEN];						//val
};

// DataSet
struct CDataSet
{
	int  nId;
	int  nStart;
	int  nIdIED;								//所属IED号（CIED.nId）
	int  nIdLD;									//所属LDevice号（CLD.nId）
	int  nIdLNinst;								//所属LN0号（CLNinst.nId）
	char strName[MAX_NAME_LEN];					//name
	char strDesc[MAX_DESC_LEN];					//desc
};

// FCDA
struct CDsMember
{
public:
	int  nId;
	int  nIdIED;								//所属IED号（CIED.nId）
	int  nDsId;									//所属DataSet号（CDataSet.nId）
	int  nDOI;									//关联DOI号（CDOI.nId） 
	int  nDAI;									//关联DAI号（CDAI.nId） 
	int  nSeqMember;							//顺序号（从0开始）
	char strDoName[MAX_NAME_LEN];				//doName
	char strDaName[MAX_NAME_LEN];				//daName
	char strFC[MAX_CLASS_LEN];					//fc
	char strLdInst[MAX_CLASS_LEN];				//ldInst
	char strLnInst[MAX_CLASS_LEN];				//lnInst
	char strLnClass[MAX_CLASS_LEN];				//lnClass
	char strPrefix[MAX_CLASS_LEN];				//prefix
	int  nIsGoose;								//是否GOOSE（1 是，0 否）
	int  nAppType;
	int  nBTypeValue;
	char strLevel[MAX_LEVEL_LEN];
	char strDesc[MAX_DESC_LEN];
	char strSAddr[MAX_DESC_LEN];
};

// ReportControl
struct CRptCtrl
{
	int  nId;
	int  nIdIED;								//所属IED号（CIED.nId）
	int  nIdLD;									//所属LDevice号（CLD.nId）
	int  nIdLNinst;								//所属LN0号（CLNinst.nId）
	char strName[MAX_NAME_LEN];					//name
	char strDesc[MAX_DESC_LEN];					//desc
    char strRptID[MAX_NAME_LEN];				//rptID
	int  nIntgPd;								//intgPd
	int  nConfRev;								//confRev
	bool isBuffered;							//buffered
	int  nBufTime;								//bufTime
	int  nIdDS;									//datSet：引用DataSet号（CDataSet.nId）
	BYTE bTrgOps;								//TrgOps（位3-0分别表示dchg,qchg,dupd,period）
	BYTE bOptFields;							//OptFields（位7-0分别表示seqNum,timeStamp,reasonCode,dataSet,dataRef,bufOvfl,entryID,configRef）
	int  nMax;									//RptEnabled（max）
};

// SettingControl, GSEControl, SampledValueControl
struct CLLNO
{
	int  nId;
	int  nIdIED;								//所属IED号（CIED.nId）
	int  nIdLD;									//所属LDevice号（CLD.nId）
	int  nIdLNinst;								//所属LN0号（CLNinst.nId）
	int  nLnType_id;							//引用LNodeType号（CLnType.nId）
	int  nType;									//类型（0 SettingControl，1 GSEControl，2 SampledValueControl）
	int  nDsID;									//引用DataSet号（CDataSet.nId）datSet
	char strName[MAX_NAME_LEN];					//name
	char strDesc[MAX_DESC_LEN];					//desc
	char strAppID[MAX_NAME_LEN];				//appID
	int  nConfRev;								//confRev
	int  nNumofSGs;								//SettingControl：numOfSGs
	int  nActSG;								//SettingControl：actSG
	int  nDsSetting_id;							//SettingControl：引用DataSet号（CDataSet.nId）"dsSetting"
	bool isGoose;								//GSEControl：是否GOOSE（type值为"GOOSE"或"GSSE"时分别为true和false，默认true）
	int	 nSmpRate;								//SampledValueControl：smpRate
	int	 nNofASDU;								//SampledValueControl：nofASDU
	bool isMulticast;							//SampledValueControl：multicast（默认true）
	BYTE bSmvOpts;								//SampledValueControl：SmvOpts（位4-0分别表示sampleRate,refreshTime,sampleSynchronized,security,dataRef）
};


// SubNetwork
struct CNetConfig
{
	int  nId;
	int  nStart;
	char chNetName[MAX_NAME_LEN];				//name
	char chNetType[MAX_NAME_LEN];				//"MMS"或"SMV"或"GOOSE"
	char chNetProtocol[MAX_NAME_LEN];			//type
	int  nBitRate;								//BitRate
};

// ConnectedAP
struct CCommConfig
{
	//公共部分
	int  nId;
	int  nIdSubNet;								//所属SubNetwork号（CNetConfig.nId）
	char strIEDName[MAX_NAME_LEN];				//iedName
	char strConnectedAP[MAX_DESC_LEN];			//desc
	char strApName[MAX_DESC_LEN];				//apName(S1,G1,...)
	//Address
	char strOSI_AP_Title[MAX_NAME_LEN];			//OSI-AP-Title
	char strOSI_AE_Qualifier[MAX_NAME_LEN];		//OSI-AE-Qualifier
	char strOSI_PSEL[MAX_NAME_LEN];				//OSI-PSEL
	char strOSI_SSEL[MAX_NAME_LEN];				//OSI-SSEL
	char strOSI_TSEL[MAX_NAME_LEN];				//OSI-TSEL
	char strIPAdder[MAX_IP_LEN];				//IP
	char strIP_Subnet[MAX_IP_LEN];				//IP-SUBNET
	//GSE or SMV
	char strGseOrSmvDesc[MAX_DESC_LEN];			//desc
	char strGseOrSmvCbName[MAX_DESC_LEN];		//cbName
	char strLdInst[MAX_CLASS_LEN];				//ldInst
	char strMACAddr[MAX_MAC_LEN];				//MAC-Address
	char strAppID[MAX_NAME_LEN];				//APPID
	int  nVlan_ID;								//VLAN-ID
    int  nVLAN_PRIORITY;						//VLAN-PRIORITY
	int  nMinTime;								//MinTime
	int  nMaxTime;								//MaxTime
};

// Header
struct CHeaderConfig
{
	int  nId;
	char strID[MAX_NAME_LEN];					//id
	char strToolID[MAX_NAME_LEN];				//toolID
	char strRevision[MAX_NAME_LEN];				//revision
	char strVersion[MAX_NAME_LEN];				//version
	char strNameStruct[MAX_NAME_LEN];			//nameStructure
};

// History
struct CHistoryConfig
{
	int  nId;
	char strRevision[MAX_NAME_LEN];				//revision
	char strVersion[MAX_NAME_LEN];				//version
	char strWhat[MAX_DESC_LEN];					//what
	char strWhen[MAX_DESC_LEN];					//when
	char strWho[MAX_DESC_LEN];					//who
	char strWhy[MAX_DESC_LEN];					//why
};


//用于存存储DA在DOTYPE中顺序的结构体
struct daSequence
{
	int nSeqNo;
	char strDaName[MAX_CLASS_LEN];
};


//用于暂存doMemeber表中fc为"CO"的部分信息
struct SBOwInfo
{
	int	 nDoTypeID;								//所属DOType号（CDoType.nId）
	bool bHasSBOw;								//该DOType是否包含SBOw字段
	int	 nDaTypeID;								//该DOType对应的daTypeID
	int	 nDataType;								//该DOType对应的DataType
};


	
//==========================================================

extern vector<CLnType>                     CSCDLnTypeList;
extern vector<CLnMember>                   CSCDLnMemberList;
extern vector<CDoType>                     CSCDDoTypeList;
extern vector<CDoMember>                   CSCDDoMemberList;
extern vector<CDaType>                     CSCDDaTypeList;
extern vector<CDaMember>                   CSCDDaMemberList;
extern vector<CEnumType>                   CSCDEnumTypeList;
extern vector<CEnumMember>                 CSCDEnumMemberList;
extern vector<CIED>                        CSCDIEDList;
extern vector<CLD>                         CSCDLDList;
extern vector<CLNinst>                     CSCDLNinstList;
extern vector<CDOI>                        CSCDDOIList;
extern vector<CDAI>                        CSCDDAIList;
extern vector<CDataSet>                    CSCDDataSetList;
extern vector<CDsMember>                   CSCDDsMemberList;
extern vector<CLLNO>                       CSCDLLNOList;
extern vector<CRptCtrl>                    CSCDRptCtrlList;
extern vector<CNetConfig>                  CSCDNetConfigList;    
extern vector<CCommConfig>                 CSCDCommConfigList;
extern vector<CHeaderConfig>               CSCDHeaderConfigList;
extern vector<CHistoryConfig>              CSCDHistoryConfigList;


extern int ParseSCD(char *iedName, char *scdFilePath);


#endif  /* _PARSE_H_ */

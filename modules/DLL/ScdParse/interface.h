#ifndef _INTERFACE_H_
#define _INTERFACE_H_


#define ST_CHAR    char	
#define ST_INT     signed int		
#define ST_LONG    signed long int     	
#define ST_UCHAR   unsigned char	
#define ST_UINT    unsigned int		
#define ST_ULONG   unsigned long     	
#define ST_VOID    void      		
#define ST_DOUBLE  double		
#define ST_FLOAT   float		

#define ST_INT8    signed char     	
#define ST_INT16   signed short     	
#define ST_INT32   signed long     	
#define ST_INT64   __int64
#define ST_UINT8   unsigned char     	
#define ST_UINT16  unsigned short    	
#define ST_UINT32  unsigned long    	
#define ST_UINT64  unsigned __int64
#define ST_BOOLEAN unsigned char		

#define MAX_NAME_LEN	64
#define MAX_DESC_LEN	128
#define MAX_IP_LEN		20

#define MAX_IDENT_LEN		120	/* length of an Identifier variable	*/
#define CLNP_MAX_LEN_MAC	6	/* Max len of MAC addr		*/
#define MAX_CDC_LEN			50	/* SPS, DPS, etc. (CURVE is longest	predefined CDC but user may define others)*/
#define MAX_VALKIND_LEN		4	/* Spec, Conf, RO, or Set		*/
#define MAX_FC_LEN			2	/* ST, MX, etc.				*/
#define MAX_FLAT_LEN		(MAX_IDENT_LEN*2)


#define SCL_OBJTYPE_DA		0
#define SCL_OBJTYPE_SDO		1
#define BRCB_BUF_SIZE       50000   // 默认BRCB缓存区大小   50k


typedef struct dbl_lnk
{
	/* Note: adding/removing fields to/from this struct will make older	*/
	/* !!!   applications incompatible with new security DLLs.		*/
	struct dbl_lnk *next;
	struct dbl_lnk *prev;
} DBL_LNK;


/************************************************************************/
/* Structures to contain information from "Header" section of SCL.	*/
/************************************************************************/
typedef struct
  {
  /* NOTE: only required elements included here. Add optional elements as needed.*/
  ST_CHAR id            [MAX_IDENT_LEN+1];

  /* Defined values for "nameStructure" attribute	*/
  #define SCL_NAMESTRUCTURE_IEDNAME	0	/* value="IEDName"	*/
  #define SCL_NAMESTRUCTURE_FUNCNAME	1	/* value="FuncName"	*/
  ST_INT nameStructure;
  } SCL_HEADER;

/************************************************************************/
/* Structures to contain information from "Communications" section of SCL.*/
/************************************************************************/
/* Data from "GSE" element (inside "ConnectedAP" element)	*/
typedef struct scl_gse
  {
  /* CRITICAL: First 2 parameters used to add this struct to linked	*/
  /* lists using list_add_last, etc.					*/
  struct scl_gse *next;		/* CRITICAL: DON'T MOVE.	*/
  struct scl_gse *prev;		/* CRITICAL: DON'T MOVE.	*/
  ST_CHAR ldInst[MAX_IDENT_LEN+1];
  ST_CHAR cbName[MAX_IDENT_LEN+1];
  ST_CHAR MAC[CLNP_MAX_LEN_MAC];	/* Multicast MAC address	*/
  ST_UINT APPID;
  ST_UINT VLANPRI;
  } SCL_GSE;

/* Data from "SMV" element (inside "ConnectedAP" element)	*/
typedef struct scl_smv
  {
  /* CRITICAL: First 2 parameters used to add this struct to linked	*/
  /* lists using list_add_last, etc.					*/
  struct scl_smv *next;		/* CRITICAL: DON'T MOVE.	*/
  struct scl_smv *prev;		/* CRITICAL: DON'T MOVE.	*/
  ST_CHAR ldInst[MAX_IDENT_LEN+1];
  ST_CHAR cbName[MAX_IDENT_LEN+1];
  ST_CHAR MAC[CLNP_MAX_LEN_MAC];	/* Multicast MAC address	*/
  ST_UINT APPID;
  ST_UINT VLANPRI;
  } SCL_SMV;

/* Data from "ConnectedAP" element	*/
typedef struct scl_cap
  {
  /* CRITICAL: First 2 parameters used to add this struct to linked	*/
  /* lists using list_add_last, etc.					*/
  struct scl_cap *next;		/* CRITICAL: DON'T MOVE.	*/
  struct scl_cap *prev;		/* CRITICAL: DON'T MOVE.	*/
  ST_CHAR iedName[MAX_IDENT_LEN+1];
  ST_CHAR *desc;		/* description (optional)*/
				/* may be long so allocate if present*/
  ST_CHAR apName[MAX_IDENT_LEN+1];
  SCL_GSE *gseHead;      /* head of list of GSE defs	*/
  SCL_SMV *smvHead;      /* head of list of SMV defs	*/
  } SCL_CAP;

/* Data from "Subnetwork" element	*/
typedef struct scl_subnet
  {
  /* CRITICAL: First 2 parameters used to add this struct to linked	*/
  /* lists using list_add_last, etc.					*/
  struct scl_subnet *next;		/* CRITICAL: DON'T MOVE.	*/
  struct scl_subnet *prev;		/* CRITICAL: DON'T MOVE.	*/
  ST_CHAR name[MAX_IDENT_LEN+1];
  ST_CHAR *desc;		/* description (optional)*/
				/* may be long so allocate if present*/
  ST_CHAR type[MAX_IDENT_LEN+1];
  SCL_CAP *capHead;		/* head of list of ConnectedAP defs	*/
  } SCL_SUBNET;

/************************************************************************/
/* Structures to contain information from "AccessPoint" section of SCL.*/
/************************************************************************/

/* "scl_fcda_add" allocates this struct, fills it in,		*/
/* and adds it to the linked list "fcdaHead" in SCL_DATASET.		*/
typedef struct
  {
  DBL_LNK l;
  ST_CHAR domName[MAX_IDENT_LEN+1];	/* domain name (constructed)	*/
  ST_CHAR ldInst  [MAX_IDENT_LEN+1];
  ST_CHAR prefix  [MAX_IDENT_LEN+1];
  ST_CHAR lnInst  [MAX_IDENT_LEN+1];
  ST_CHAR lnClass [MAX_IDENT_LEN+1];
  ST_CHAR doName  [MAX_IDENT_LEN+1];
  ST_CHAR daName  [MAX_IDENT_LEN+1];
  ST_CHAR fc      [MAX_FC_LEN+1];	/* ST, MX, etc.			*/
  } SCL_FCDA;

// 读写函数及报告信息结构
typedef struct
  {
  DBL_LNK l;
					/* allocate appropriate size buffer*/
  ST_CHAR       doRef[MAX_IDENT_LEN+1];	// 从DO开始,不含LN和FC,以$结束
  ST_UINT       funIndx;        // 函数索引
  ST_INT        IdxinArray;     // 数据索引参数
  ST_INT        EventType;      // 事件类型
  ST_INT        mapIdx;         // map表中的索引,在usermap.c中赋值
  } SCL_rwFun;

/* "scl_dai_add" allocates this struct, fills it in,			*/
/* and adds it to the linked list "daiHead" in SCL_LN.			*/
/* The "flattened" name must be constructed from the "name" & "ix"	*/
/* attribute of the DOI and DAI and possibly the intervening SDI,	*/
/* where "ix" is an array index (we'll need some new flattened name	*/
/* syntax to handle the array index).					*/
/* The "accessControl" attr of DOI is ignored (don't know what it means).*/
/* The "desc" attr of DOI, SDI, & DAI are ignored (not useful).		*/
typedef struct
  {
  DBL_LNK l;
  ST_CHAR flattened[MAX_FLAT_LEN+1];	/* flattened attribute name	*/
					/* constructed from "name" & "ix"*/
					/* from DOI, SDI, & DAI		*/
					// // 从DO开始,不含LN和FC
  ST_CHAR *Val;				/* attribute value text		*/
					/* allocate appropriate size buffer*/
  ST_UINT sGroup;			/* optional Setting Group Number*/
  ST_CHAR sAddr[MAX_IDENT_LEN+1];	/* from DAI			*/
  ST_CHAR valKind[MAX_VALKIND_LEN+1];	/* from DAI			*/
  } SCL_DAI;

/* "scl_dataset_add" allocates this struct,			*/
/* and adds it to the linked list "datasetHead" in SCL_LN.	*/
typedef struct
  {
  DBL_LNK l;
  ST_CHAR name[MAX_IDENT_LEN+1];	/* dataset name		*/
  ST_CHAR *desc;			/* description (optional)*/
					/* may be long so allocate if present*/
  SCL_FCDA *fcdaHead;			/* head of list of FCDA	*/
  } SCL_DATASET;

/* "scl_rcb_add" allocates this struct, fills it in,		*/
/* and adds it to the linked list "rcbHead" in SCL_LN.		*/
typedef struct
  {
  DBL_LNK l;
  ST_CHAR name[MAX_IDENT_LEN+1];
  ST_CHAR *desc;		/* description (optional)*/
				/* may be long so allocate if present*/
  ST_CHAR datSet[MAX_IDENT_LEN+1];
  ST_UINT intgPd;
  ST_CHAR rptID[MAX_IDENT_LEN+1];
  ST_UINT confRev;
  ST_BOOLEAN buffered;		/* TRUE if this is buffered RCB	*/
  ST_UINT bufTime;
  ST_UINT8 TrgOps [1];		/* 8-bit bitstring			*/
				/* Boolean vals from SCL file		*/
				/* (dchg, qchg, dupd, & period)		*/
				/* used to set bits in TrgOps bitstring	*/
  ST_UINT8 OptFlds [2];		/* 9-bit bitstring			*/
				/* Boolean vals from SCL file		*/
				/* (seqNum, timeStamp, dataSet,		*/
				/* reasonCode, dataRef, bufOvfl,	*/
				/* entryID, configRef)			*/
				/* segmentation boolean is ignored	*/
				/* used to set bits in OptFlds bitstring*/
  ST_UINT maxClient;		/* value of "RptEnabled max" attr.	*/
  ST_UINT ScanRate;         // 扫描周期 Add 2007-10-09
  } SCL_RCB;			/* Report Control Block	*/

typedef struct
  {
  /* Counters of different types of BRCB.	*/
  ST_UINT brcb_count_complex;
  ST_UINT brcb_count_ST;
  ST_UINT brcb_count_MX;
  ST_UINT brcb_count_CO;
  ST_UINT brcb_count_SP;
  ST_UINT brcb_count_SG;
  ST_UINT brcb_count_SE;
  ST_UINT brcb_count_SV;
  ST_UINT brcb_count_CF;
  ST_UINT brcb_count_DC;
  ST_UINT brcb_count_EX;

  /* Counters of different types of URCB.	*/
  ST_UINT urcb_count_complex;
  ST_UINT urcb_count_ST;
  ST_UINT urcb_count_MX;
  ST_UINT urcb_count_CO;
  ST_UINT urcb_count_SP;
  ST_UINT urcb_count_SG;
  ST_UINT urcb_count_SE;
  ST_UINT urcb_count_SV;
  ST_UINT urcb_count_CF;
  ST_UINT urcb_count_DC;
  ST_UINT urcb_count_EX;
  } SCL_RCB_COUNTERS;

/************************************************************************/
/*			LOG Control Block				*/
/* "scl_lcb_add" allocates this struct, fills it in,			*/
/* and adds it to the linked list "lcbHead" in SCL_LN.			*/
typedef struct
  {
  DBL_LNK l;
  ST_CHAR name[MAX_IDENT_LEN+1];
  ST_CHAR *desc;		/* description (optional)*/
				/* may be long so allocate if present*/
  ST_CHAR datSet[MAX_IDENT_LEN+1];
  ST_UINT intgPd;
  ST_CHAR logName[MAX_IDENT_LEN+1];
  ST_BOOLEAN logEna;
  ST_BOOLEAN reasonCode;
  ST_UINT8 TrgOps [1];		/* 8-bit bitstring			*/
				/* Boolean vals from SCL file		*/
				/* (dchg, qchg, dupd, & period)		*/
				/* used to set bits in TrgOps bitstring	*/
  } SCL_LCB;

/************************************************************************/
/*			GOOSE Control Block				*/
/* "scl_gcb_add" allocates this struct, fills it in,			*/
/* and adds it to the linked list "gcbHead" in SCL_LN.			*/
typedef struct
  {
  DBL_LNK l;
  ST_CHAR name[MAX_IDENT_LEN+1];
  ST_CHAR *desc;			/* description (optional)*/
					/* may be long so allocate if present*/
  ST_CHAR datSet[MAX_IDENT_LEN+1];	/* for GOOSE only	*/
  ST_UINT confRev;			/* for GOOSE only	*/
  ST_BOOLEAN isGoose;	/* SD_TRUE if "GOOSE", SD_FALSE if "GSSE"*/
  ST_CHAR appID[MAX_IDENT_LEN+1];	/* for GOOSE only	*/
  /* The SCL file may also contain one or more "IEDName" elements to	*/
  /* indicate IEDs that should subscribe for GOOSE data. We have no	*/
  /* way to use this information, so it is ignored.			*/
  } SCL_GCB;

/************************************************************************/
/*			Sampled Value Control Block			*/
/* "scl_parse" allocates this struct and fills it in.			*/
/* "scl_svcb_add" adds it to the linked list "svcbHead" in SCL_LN.	*/
typedef struct
  {
  DBL_LNK l;
  ST_CHAR name[MAX_IDENT_LEN+1];
  ST_CHAR *desc;		/* description (optional)*/
				/* may be long so allocate if present*/
  ST_CHAR datSet[MAX_IDENT_LEN+1];
  ST_CHAR smvID[MAX_IDENT_LEN+1];
  ST_UINT smpRate;
  ST_UINT nofASDU;
  ST_UINT confRev;
  ST_BOOLEAN multicast;		/* TRUE if this is MsvCB		*/
  ST_UINT8 OptFlds [1];		/* 8-bit bitstring			*/
				/* Boolean vals from "SmvOpts" in SCL	*/
				/* (sampleRate, etc.)			*/
				/* used to set bits in this bitstring	*/
  ST_BOOLEAN securityPres;	/* SmvOpts security flag	*/
  ST_BOOLEAN dataRefPres;	/* SmvOpts dataRef flag		*/
  } SCL_SVCB;			/* Sampled Value Control Block	*/

/* "scl_ln_add" allocates this struct, fills it in,		*/
/* and adds it to the linked list "lnHead" in SCL_LD.		*/
typedef struct
  {
  DBL_LNK l;
  ST_CHAR varName[MAX_IDENT_LEN+1];	/* variable name (constructed)	*/
  ST_CHAR *desc;			/* description (optional)*/
					/* may be long so allocate if present*/
  ST_CHAR lnType[MAX_IDENT_LEN+1];	/* LN Type name		*/
  ST_CHAR lnClass[MAX_IDENT_LEN+1];	/* LN Class name	*/
					/* for LN0, must be "LLN0"	*/
  ST_CHAR inst[MAX_IDENT_LEN+1];	/* LN inst name			*/
					/* for LN0, must be "" (empty string)*/
  ST_CHAR prefix[MAX_IDENT_LEN+1];	/* LN prefix name	*/
					/* for LNO, ignored	*/
  SCL_rwFun   *rwHead;		/* head of list of 读写函数信息	*/
  SCL_DAI     *daiHead;		/* head of list of DAI	*/
  SCL_DATASET *datasetHead;	/* head of list of DataSet	*/
  SCL_RCB     *rcbHead;		/* head of list of RCB (Report Control)	*/
  SCL_LCB     *lcbHead;		/* head of list of LCB (Log Control)	*/
  SCL_GCB     *gcbHead;		/* head of list of GCB (GOOSE Control)	*/
  SCL_SVCB    *svcbHead;	/* head of list of SVCB (Sampled Value Control)*/
  ST_BOOLEAN  bHasSBCB;     // 是否有SGCB
  /* NOTE: In LN or LN0: Inputs ignored		*/
  /* NOTE: In LN0: SampledValueControl, SettingControl, SCLControl ignored*/

  ST_INT type_id;		/* Initialized by "scl2_datatype_create_all"*/
//  MVL_VAR_ASSOC *mvl_var_assoc;	/* MVL Variable Association created from LN info*/
  ST_CHAR *mvl_var_assoc;	/* MVL Variable Association created from LN info*/
  } SCL_LN;			/* Logical Node (LN or LN0 in SCL)	*/

/* "scl_ld_create" allocates this struct			*/
/* and adds it to the linked list "ldHead" in SCL_INFO.		*/
typedef struct
  {
  DBL_LNK l;
  ST_CHAR domName[MAX_IDENT_LEN+1];	/* domain name (constructed)	*/
  ST_CHAR *desc;			/* description (optional)*/
					/* may be long so allocate if present*/
  ST_CHAR inst[MAX_IDENT_LEN+1];	/* LD inst name		*/
  SCL_LN *lnHead;			/* head of list of LN	*/
  /* NOTE: AccessControl in LDevice is ignored	*/
  } SCL_LD;			/* Logical Device (LDevice in SCL)*/

/************************************************************************/
/* Structures to contain information from "DataTypeTemplates" section of SCL.*/
/************************************************************************/
/* This structure should be allocated and filled in by the function	*/
/* "scl_lntype_add_do".							*/
typedef struct scl_do
  {
  /* CRITICAL: First 2 parameters used to add this struct to linked	*/
  /* lists using list_add_last, etc.					*/
  struct scl_do *next;			/* CRITICAL: DON'T MOVE.	*/
  struct scl_do *prev;			/* CRITICAL: DON'T MOVE.	*/
  ST_CHAR name[MAX_IDENT_LEN+1];	/* data object name		*/
  ST_CHAR type[MAX_IDENT_LEN+1];	/* data object type		*/
  } SCL_DO;

typedef struct scl_lntype
  {
  /* CRITICAL: First 2 parameters used to add this struct to linked	*/
  /* lists using list_add_last, etc.					*/
  struct scl_lntype *next;		/* CRITICAL: DON'T MOVE.	*/
  struct scl_lntype *prev;		/* CRITICAL: DON'T MOVE.	*/
  ST_CHAR id[MAX_IDENT_LEN+1];			/* name used to reference this LN Type*/
  ST_CHAR lnClass[MAX_IDENT_LEN+1];		/* logical node class		*/
  SCL_DO *doHead;		/* head of list of DO	*/
				/* scl_lntype_add_do adds to list	*/
  ST_INT type_id;		/* Initialized by "scl2_datatype_create_all"*/
  } SCL_LNTYPE;


/* This structure should be allocated and filled in by the function	*/
/* "scl_dotype_add_da" OR "scl_dotype_add_sdo", and possibly modified by the optional	*/
/* function "scl_dotype_add_da_val".					*/
/* NOTE: the same structure must be used for DA or SDO because each must	*/
/* be put on the same linked list in the order they are read from the SCL file.*/
/* Most of the parameters are relevant only for DA elements. They are	*/
/* ignored if this is an SDO (i.e. objtype=SCL_OBJTYPE_SDO).		*/
typedef struct
  {
  DBL_LNK l;
  ST_INT objtype;			/* SCL_OBJTYPE_DA or SCL_OBJTYPE_SDO	*/
  ST_CHAR name[MAX_IDENT_LEN+1];	/* DA or SDO name		*/
  ST_CHAR *desc;			/* description (optional)*/
					/* may be long so allocate if present*/
  ST_CHAR sAddr[MAX_IDENT_LEN+1];	/* for DA only: DA sAddr	*/
  ST_CHAR bType[MAX_IDENT_LEN+1];	/* for DA only: DA bType	*/
  ST_CHAR valKind[MAX_VALKIND_LEN+1];	/* for DA only: Spec, Conf, RO, or Set	*/
  ST_CHAR type[MAX_IDENT_LEN+1];	/* for DA: needed if bType="Struct" or "Enum"*/
					/* for SDO: required		*/
  ST_UINT count;			/* for DA only: num array entries*/
  ST_CHAR fc[MAX_FC_LEN+1];		/* for DA only: functional constraint	*/
  ST_BOOLEAN dchg;			/* for DA only: TrgOp (data change)	*/
  ST_BOOLEAN qchg;			/* for DA only: TrgOp (quality change)	*/
  ST_BOOLEAN dupd;			/* for DA only: TrgOp (data update)	*/

  /* The "Val" and "sGroup" parameters are only set if the SCL file contains the
   * optional "Val" element, in which case "scl_dotype_add_da_val" is called.
   */
  ST_CHAR *Val;				/* for DA only: attribute value text	*/
					/* allocate appropriate size buffer*/
  ST_UINT sGroup;			/* for DA only: optional Setting Group Number*/
  } SCL_DA;

typedef struct scl_dotype
  {
  /* CRITICAL: First 2 parameters used to add this struct to linked	*/
  /* lists using list_add_last, etc.					*/
  struct scl_dotype *next;		/* CRITICAL: DON'T MOVE.	*/
  struct scl_dotype *prev;		/* CRITICAL: DON'T MOVE.	*/
  ST_CHAR id[MAX_IDENT_LEN+1];	/* name used to reference this DO Type	*/
  ST_CHAR cdc[MAX_CDC_LEN+1];	/* CDC name				*/
  SCL_DA *daHead;		/* head of list of DA or SDO		*/
				/* scl_dotype_add_da OR			*/
				/* scl_dotype_add_sdo adds to list	*/
  } SCL_DOTYPE;

/* This structure should be allocated and filled in by the function	*/
/* "scl_datype_add_bda".						*/
typedef struct
  {
  DBL_LNK l;
  ST_CHAR name[MAX_IDENT_LEN+1];		/* data attribute name		*/
  ST_CHAR *desc;			/* description (optional)*/
					/* may be long so allocate if present*/
  ST_CHAR sAddr[MAX_IDENT_LEN+1];		/* for DA only: DA sAddr	*/
  ST_CHAR bType[MAX_IDENT_LEN+1];		/* data attribute type		*/
  ST_CHAR valKind[MAX_VALKIND_LEN+1];		/* Spec, Conf, RO, or Set	*/
  ST_CHAR type[MAX_IDENT_LEN+1];		/* only used if btype="Struct" or "Enum"*/
  ST_UINT count;	/* for DA only: num array entries*/

  /* The "Val" and "sGroup" parameters are only set if the SCL file contains the
   * optional "Val" element, in which case "scl_datype_add_bda_val" is called.
   */
  ST_CHAR *Val;				/* attribute value text		*/
					/* allocate appropriate size buffer*/
  ST_UINT sGroup;			/* optional Setting Group Number*/
  } SCL_BDA;			/* Basic Data Attribute		*/

typedef struct
  {
  DBL_LNK l;
  ST_CHAR id[MAX_IDENT_LEN+1];			/* name used to reference this DA Type*/
  SCL_BDA *bdaHead;		/* head of list of BDA	*/
				/* scl_datype_add_bda adds to list	*/
  } SCL_DATYPE;

/* This structure should be allocated and filled in by the function	*/
/* "scl_enumtype_add_enumval".						*/
typedef struct
  {
  DBL_LNK l;
  ST_INT ord;				/* ord attribute	*/
  ST_CHAR EnumVal[MAX_IDENT_LEN+1];	/* EnumVal element		*/
					/* TRUNCATED if longer than buffer	*/
  } SCL_ENUMVAL;

typedef struct
  {
  DBL_LNK l;
  ST_CHAR id[MAX_IDENT_LEN+1];			/* name used to reference this DA Type*/
  SCL_ENUMVAL *enumvalHead;	/* head of list of EnumVal	*/
				/* scl_enumtype_add_enumval adds to list*/
  } SCL_ENUMTYPE;

/************************************************************************/
/*			SCL_INFO					*/
/* This structure contains all information extracted from the SCL file	*/
/* to be used for MMS-EASE Lite initialization.				*/
/************************************************************************/
typedef struct
{
	ST_CHAR iedName [MAX_IDENT_LEN+1];	/* passed to scl_parse		*/
	
	SCL_HEADER Header;		/* Info from "Header" section of SCL file*/
	
	/* SubNetwork definitions from (from Communication section)		*/
	SCL_SUBNET *subnetHead;	/* head of list of SubNetwork defs	*/
	
	/* Logical Node Type definitions (from DataTypeTemplates section)	*/
	SCL_LNTYPE *lnTypeHead;	/* head of list	of LNodeType defs	*/
	SCL_DOTYPE *doTypeHead;	/* head of list of DOType defs		*/
	SCL_DATYPE *daTypeHead;	/* head of list of DAType defs		*/
	SCL_ENUMTYPE *enumTypeHead;	/* head of list of EnumType defs	*/
	
	/* Logical Device (MMS Domain) definitions (from AccessPoint section)	*/
	SCL_LD *ldHead;		/* head of list of LDevice defs		*/
	
	ST_INT brcb_bufsize;		/* BRCB buffer size			*/
				/* scl2_ld_create_all uses arg to set it*/
	ST_BOOLEAN datatype_create_done;	/* flag set by scl2_datatype_create_all*/
	ST_BOOLEAN ld_create_done;	/* flag set by scl2_ld_create_all*/
} SCL_INFO;



//=======================================================================================
// IED信息表结构
typedef struct
{
	int		id;									//序号
	char	name[MAX_NAME_LEN];					//名称
	char	desc[MAX_DESC_LEN];					//描述
	char	type[MAX_NAME_LEN];					//类型
	char	configVersion[MAX_NAME_LEN];		//版本号
	char	manufacturer[MAX_NAME_LEN];			//制造商
	char	strIPAddr1[MAX_IP_LEN];				//A网IP
	char	strIPSubnet1[MAX_IP_LEN];			//A网SUBNET
	char	strIPAddr2[MAX_IP_LEN];				//B网IP
	char	strIPSubnet2[MAX_IP_LEN];			//B网SUBNET
} IED_LIST;

// 遥测信息表结构
typedef struct
{
	int		nIED;								//所属IED号
	int		nChannel;							//通道号 
    char	strName[MAX_NAME_LEN];				//名称
	int		nType;								//类型 0 普通遥测 1 顺控遥测
	bool	isRlyYc;							//是否为保护测量值
    char	strMmsVarName[MAX_DESC_LEN];		//引用
	char	strDataSetName[MAX_DESC_LEN];		//数据集
	char	strLevel[MAX_NAME_LEN];				//数据集位置
	int		nDataType;							//数据类型    
} YC_INFO;

// 遥信信息表结构
typedef struct
{
	int		nIED;								//所属IED号
	int		nChannel;							//通道号 
    char	strName[MAX_NAME_LEN];				//名称
	int		nType;								//类型 1 单点遥信；2 双点遥信；3 整数；4 浮点数
    char	strMmsVarName[MAX_DESC_LEN];		//引用
	char	strDataSetName[MAX_DESC_LEN];		//数据集
	char	strLevel[MAX_NAME_LEN];				//数据集位置
	char	strQLevel[MAX_NAME_LEN];			//品质数据集位置
	char	strTLevel[MAX_NAME_LEN];			//时间数据集位置
	char	strStValLevel[MAX_NAME_LEN];		//状态数据集位置
	int		nDataType;							//数据类型    
} YX_INFO;

// 遥控信息表结构
typedef struct
{
	int		nIED;								//所属IED号
	int		nChannel;							//通道号 
    char	strName[MAX_NAME_LEN];				//名称
	int		nType;								//类型 0 普通遥控；1 预留；2 顺控遥控；3 顺控遥设
    char	strMmsVarName[MAX_DESC_LEN];		//引用
	int		nDataType;							//数据类型
    int		nCtlModel;							//遥控模型（1 常规直接控制，2 常规选择控制，3 增强直接控制，4 增强选择控制）
} YK_INFO;

// 定值信息表结构
typedef struct
{
	int		nIED;								//所属IED号
	int		nID;								//ID 
    char	strName[MAX_NAME_LEN];				//名称
	int		nType;								//类型 0 未定义，1 投退型，2 整数型，3 浮点型，4 字串型
    char	strMmsVarName[MAX_DESC_LEN];		//引用
	char	strDataSetName[MAX_DESC_LEN];		//数据集
	char	strLevel[MAX_NAME_LEN];				//数据集位置
	int		nDataType;							//数据类型    
} DZ_INFO;

// 事件信息表结构
typedef struct
{
	int		nIED;								//所属IED号
	int		nChannel;							//通道号 
    char	strName[MAX_NAME_LEN];				//名称
    char	strMmsVarName[MAX_DESC_LEN];		//引用
	char	strDataSetName[MAX_DESC_LEN];		//数据集
	char	strLevel[MAX_NAME_LEN];				//数据集位置
	char	strTLevel[MAX_NAME_LEN];			//时间数据集位置
	int		nDataType;							//数据类型    
} SJ_INFO;

// 全部61850对象信息结构
typedef struct
{
	int			ied_num;						//IED总数
	int			yc_num;							//遥测总数
	int			yx_num;							//遥信总数
	int			yk_num;							//遥控总数
	int			dz_num;							//定值总数
	int			sj_num;							//事件总数
	IED_LIST	*ied_list;						//IED信息表
	YC_INFO		*yc_info;						//遥测信息表
	YX_INFO		*yx_info;						//遥信信息表
	YK_INFO		*yk_info;						//遥控信息表
	DZ_INFO		*dz_info;						//定值信息表
	SJ_INFO		*sj_info;						//事件信息表
	DZ_INFO		*dzq_info;						//定值区信息（每个IED一条记录，其nType为定值区个数）
} ALL_61850_INFO;


extern string UTF_8Decode(string str);


#endif  /* _INTERFACE_H_ */

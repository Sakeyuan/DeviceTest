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


// 字和字节联合体数据结构
typedef  union
{
    WORD            wWord;                          // 字
    BYTE            cByte[2];                       // 字节(配合CN_BYTE_LL等使用)
}tagWord_Byte2;

// 双字、字和字节联合体数据结构
typedef  union
{
    DWORD           dwDword;                        // 双字
    WORD            wWord [2];                      // 字  (配合CN_WORD_LO等使用)
    BYTE            cByte [4];                      // 字节(配合CN_BYTE_LL等使用)
}tagDWord_Byte4;

// uint64、双字、字和字节联合体数据结构
typedef union
{
	UINT64			uInt64;
    DWORD           dwDword[2];                     // 双字
    WORD            wWord[4];                       // 字  (配合CN_WORD_LO等使用)
    BYTE            cByte[8];                       // 字节(配合CN_BYTE_LL等使用)
}tagDWord_Byte8;



#define	MAX_IDENT_LEN	64
#define	MAX_NAME_LEN	120

#define MAX_YC_NUM		1000				// 遥测最大个数
#define MAX_YX_NUM		3000				// 遥信最大个数
#define MAX_YK_NUM		1000				// 遥控最大个数
#define MAX_DZ_NUM		2000				// 定值最大个数

#define MAX_RCB_NUM		1000				// 报告控制块最大个数
#define MAX_LCB_NUM		100					// 日志控制块最大个数
#define MAX_LOG_LIST	50					// 日志最大目录数
#define MAX_LOG_INFO	5000				// 日志最大条目数


//=========================================================================
// 61850对象目录表结构
//=========================================================================
typedef struct
{
	int				id;
	char			name[MAX_NAME_LEN];
	int				uid;							//上级目录id
} NAME_INFO;

typedef struct
{
	int				ld_num;							//LD数
	int				da_num;							//DA数
	int				ds_num;							//DataSet数
	int				dsm_num;						//DataSet Member数
	NAME_INFO		*ld_info;						//LD列表
	NAME_INFO		*da_info;						//DA列表，上级目录为LD
	NAME_INFO		*ds_info;						//DataSet列表，上级目录为LD
	NAME_INFO		*dsm_info;						//DataSet Member列表，上级目录为DataSet
} NAME_LIST;


//=========================================================================
// 61850对象信息表结构
//=========================================================================
typedef struct
{
	int				id;								//通道号
	char			name[MAX_NAME_LEN];				//名称
	char			dom_name[MAX_NAME_LEN];
	char			var_name[MAX_NAME_LEN];
	int				var_type;
	BYTE			yc_type;						//类型（有无相角：0 无，1 有）
	float			yc_mag;							//遥测幅值
	float			yc_ang;							//遥测相角
} YC_INFO;	//遥测信息

typedef struct
{
	int				id;								//通道号
	char			name[MAX_NAME_LEN];				//名称
	char			dom_name[MAX_NAME_LEN];
	char			var_name[MAX_NAME_LEN];
	int				var_type;
	BYTE			yx_type;						//类型（1 单点遥信，2 双点遥信，3 整数值，4 浮点值，9 保护遥信）
	BYTE			yx_stat;						//遥信状态值（双点遥信、单点遥信、保护遥信）
	int				yx_iValue;						//遥信值（整数型）
	float			yx_fValue;						//遥信值（浮点型）
} YX_INFO;	//遥信信息

typedef struct
{
	int				id;								//通道号
	char			name[MAX_NAME_LEN];				//名称
	char			dom_name[MAX_NAME_LEN];
	char			var_name[MAX_NAME_LEN];
	int				var_type;
	BYTE			yk_type;						//类型（0 遥控，1 遥调）
	BYTE			yk_model;						//遥控模型（1 常规直接控制，2 常规选择控制，3 增强直接控制，4 增强选择控制）
} YK_INFO;	//遥控信息

typedef struct
{
	int				id;								//ID
	char			name[MAX_NAME_LEN];				//名称
	char			dom_name[MAX_NAME_LEN];
	char			var_name[MAX_NAME_LEN];
	int				var_type;
	BYTE			dz_type;						//类型（0 未定义，1 开关型，2 整数型，3 浮点型，4 字串型）
	int				dz_unit;						//定值单位
	BYTE			dz_bValue;						//定值值（开关型）
	int				dz_iValue;						//定值值（整数型）
	float			dz_fValue;						//定值值（浮点型）
	char			dz_sValue[MAX_NAME_LEN];		//定值值（字串型）
	float			dz_minVal;						//最小值
	float			dz_maxVal;						//最大值
	float			dz_stepSize;					//步长值
} DZ_INFO;	//定值信息（id=0为定值控制块信息，此时dz_type为定值区个数、dz_bValue为当前定值区）

typedef struct
{
	int				id;
	char			dom_name[MAX_NAME_LEN];
	char			var_name[MAX_NAME_LEN];
	char			RptID[MAX_NAME_LEN];			//报告控制块标识符 
	BYTE			RptEna;							//报告使能
	BYTE			Resv;							//是否保留（URCB）
	char			DatSet[MAX_NAME_LEN];			//数据集
	UINT32			ConfRev;						//配置版本号
	WORD			OptFlds;						//选项域
	UINT32			BufTm;							//缓存时间
	WORD			SqNum;							//顺序号
	BYTE			TrgOps;							//触发选项
	UINT32			IntgPd;							//完整性周期
	BYTE			GI;								//是否总召
	BYTE			PurgeBuf;						//是否清除缓存（BRCB）
	UINT64			entry_id;						//报告条目标识（BRCB）
	int				entry_day;						//报告条目时间（BRCB）
	int				entry_ms;
	int				type_spec_len;					//类型数据长度
	char			type_spec_data[256];			//类型数据
} RCB_INFO;	//报告控制块信息

typedef struct
{
	char			dataRef[MAX_NAME_LEN];			//数据报告为控制块标识符（RptID）引用串，控制报告为控制对象引用串
	BYTE			code;							//数据报告为触发报告原因码（reason），控制报告为控制结果码（0 成功，1 错误）
	int				dsmID;							//数据报告的数据集成员号
	int				dataLen;						//数据长度
	BYTE			dataBuf[64];					//数据内容
} RPT_INFO; //报告信息

typedef void (*func_rpt_process)(int kind, RPT_INFO rtp_info[], int cnt);  //报告处理回调函数类型定义


//=========================================================================
// 61850日志结构
//=========================================================================

//日志控制块信息
typedef struct
{
	int				id;
	char			dom_name[MAX_NAME_LEN];
	char			var_name[MAX_NAME_LEN];
	BYTE			log_enable;						//日志使能
	char			log_ref[MAX_NAME_LEN];			//日志引用
	char			ds_name[MAX_NAME_LEN];			//数据集
	int				oldest_day;						//最旧条目时间
	int				oldest_ms;
	UINT64			oldest_id;						//最旧条目标识
	int				newest_day;						//最新条目时间
	int				newest_ms;
	UINT64			newest_id;						//最新条目标识
	BYTE			TrgOps;							//触发选项
	UINT32			IntgPd;							//完整性周期
	int				type_spec_len;					//类型数据长度
	char			type_spec_data[256];			//类型数据
} LCB_INFO;

//日志目录表
typedef struct
{
	int				id;
	char			ld_name[MAX_NAME_LEN];			//逻辑设备名
	char			log_name[MAX_NAME_LEN];			//日志名
} LOG_LIST;

//日志状态
typedef struct
{
	UINT64			current_id;						//当前条目标识
	BYTE			mms_deletable;					//日志是否可删除
} LOG_STAT;

//日志信息
typedef struct
{
	UINT64			id;
	int				day;
	int				ms;
	char			dom_name[MAX_NAME_LEN];			//日志控制块dom_name
	char			var_name[MAX_NAME_LEN];			//日志控制块var_name
	char			var_ref[MAX_NAME_LEN];			//事件对象引用
	BYTE			var_data_len;					//事件数据长度
	BYTE			var_data[64];					//事件数据内容
} LOG_INFO;	


#endif  /* _INTERFACE_H_ */

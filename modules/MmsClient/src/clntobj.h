/*  This file created from input file 'clntobj.odf'
    Leaf Access Parameter (LAP) File: 'Not Used'
	Created Thu Oct 31 21:39:50 2013
*/

#ifndef FOUNDRY_OUTPUT_HEADER_INCLUDED
#define FOUNDRY_OUTPUT_HEADER_INCLUDED

#include "mvl_uca.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************/
/* MVL Type Control Information */
extern MVL_TYPE_CTRL *mvl_type_ctrl;
extern ST_INT mvl_num_types;

/************************************************************************/


/* MVL Type ID's */
#define BOOLEAN_TYPEID		0
#define INT8_TYPEID		1
#define INT16_TYPEID		2
#define INT32_TYPEID		3
#define INT128_TYPEID		4
#define INT8U_TYPEID		5
#define INT16U_TYPEID		6
#define INT32U_TYPEID		7
#define FLOAT32_TYPEID		8
#define FLOAT64_TYPEID		9
#define ENUMERATED8_TYPEID		10
#define ENUMERATED16_TYPEID		11
#define OCTET_STRING8_TYPEID		12
#define OCTET_STRING64_TYPEID		13
#define VISIBLE_STRING255_TYPEID		14
#define VISIBLE_STRING64_TYPEID		15
#define VISIBLE_STRING97_TYPEID		16
#define UTC_TM_TYPEID		17
#define CODED_ENUM2_TYPEID		18
#define UNICODE_STRING255_TYPEID		19
#define TimeStamp_TYPEID		20
#define EntryTime_TYPEID		21
#define Quality_TYPEID		22
#define IDENT_TYPEID		23
#define BOOL_TYPEID		24
#define B2_TYPEID		25
#define D_TYPEID		26
#define DB_TYPEID		27
#define F_TYPEID		28
#define FF_TYPEID		29
#define HL_TYPEID		30
#define HHL_TYPEID		31
#define LL_TYPEID		32
#define LLL_TYPEID		33
#define I_TYPEID		34
#define FI_TYPEID		35
#define O_TYPEID		36
#define Q_TYPEID		37
#define R_TYPEID		38
#define FR_TYPEID		39
#define S_TYPEID		40
#define T_TYPEID		41
#define FT_TYPEID		42
#define PP_TYPEID		43
#define U_TYPEID		44
#define VSTR8_TYPEID		45
#define VSTR16_TYPEID		46
#define VSTR32_TYPEID		47
#define VSTR64_TYPEID		48
#define VSTR65_TYPEID		49
#define VSTR128_TYPEID		50
#define BSTR1_TYPEID		51
#define BSTR2_TYPEID		52
#define BSTR8_TYPEID		53
#define BSTR16_TYPEID		54
#define BSTR32_TYPEID		55
#define VBSTR8_TYPEID		56
#define VBSTR16_TYPEID		57
#define VBSTR32_TYPEID		58
#define INT8S_TYPEID		59
#define INT16S_TYPEID		60
#define INT32S_TYPEID		61
#define FLT32_TYPEID		62
#define FLT64_TYPEID		63
#define BTIME4_TYPEID		64
#define BTIME6_TYPEID		65
#define ENUM8_TYPEID		66
#define ENUM16_TYPEID		67
#define MAG_TYPEID		68
#define ANG_TYPEID		69
#define ACCRPTENA_TYPEID		70
#define ACCRS_TYPEID		71
#define ACCSET_TYPEID		72
#define ACTTAGARR_TYPEID		73
#define ANCESTRY_TYPEID		74
#define ANFMT_TYPEID		75
#define BUFTIM_TYPEID		76
#define CID_TYPEID		77
#define CKTID_TYPEID		78
#define CKTPHS_TYPEID		79
#define CLASS_TYPEID		80
#define COMMADR_TYPEID		81
#define COMMREV_TYPEID		82
#define CONTCURRTG_TYPEID		83
#define COUNT_TYPEID		84
#define CRIRPT_TYPEID		85
#define DATSETNAM_TYPEID		86
#define DESTAE_TYPEID		87
#define DEVFCT_TYPEID		88
#define DEVMDLS_TYPEID		89
#define DOW_TYPEID		90
#define DOWSCHED_TYPEID		91
#define ENABLE_TYPEID		92
#define ENCOPT_TYPEID		93
#define ENROLL_TYPEID		94
#define EORBDESC_TYPEID		95
#define EVACON_TYPEID		96
#define EVACNS_TYPEID		97
#define EVACRI_TYPEID		98
#define EVAFCT_TYPEID		99
#define EVAPAR_TYPEID		100
#define EVTENA_TYPEID		101
#define FLTCURDUR_TYPEID		102
#define FLTCURRTG_TYPEID		103
#define FRZENA_TYPEID		104
#define FRZPD_TYPEID		105
#define FWDPWRHA_TYPEID		106
#define HWREV_TYPEID		107
#define HZRTG_TYPEID		108
#define INDAT_TYPEID		109
#define INTGPD_TYPEID		110
#define LINLENM_TYPEID		111
#define LOC_TYPEID		112
#define LOGENA_TYPEID		113
#define LOGENR_TYPEID		114
#define LOGNAM_TYPEID		115
#define LOGSIZE_TYPEID		116
#define LOGWRP_TYPEID		117
#define MAC_TYPEID		118
#define MDL_TYPEID		119
#define MED_TYPEID		120
#define MXREF_TYPEID		121
#define MXTYP_TYPEID		122
#define NAME_TYPEID		123
#define NEWTIM_TYPEID		124
#define NUMBITS_TYPEID		125
#define NUMPLS_TYPEID		126
#define NUMSMP_TYPEID		127
#define NUMUNIT_TYPEID		128
#define OFFDUR_TYPEID		129
#define OLDTIM_TYPEID		130
#define ONDUR_TYPEID		131
#define OPERDEV_TYPEID		132
#define OPTFLDS_TYPEID		133
#define OUTDAT_TYPEID		134
#define OVRST_TYPEID		135
#define OWN_TYPEID		136
#define PRO_TYPEID		137
#define PWRHA_TYPEID		138
#define QURPTENA_TYPEID		139
#define RBEPD_TYPEID		140
#define RPTENA_TYPEID		141
#define RPTID_TYPEID		142
#define RVSPWRHA_TYPEID		143
#define SBOENA_TYPEID		144
#define SETTIMOUT_TYPEID		145
#define SEQNUM_TYPEID		146
#define SERNUM_TYPEID		147
#define SFTREV_TYPEID		148
#define SMPRATE_TYPEID		149
#define TAGD_TYPEID		150
#define TAGID_TYPEID		151
#define TAGOWN_TYPEID		152
#define TAGTYP_TYPEID		153
#define TEMPRAT_TYPEID		154
#define TEMPRTG_TYPEID		155
#define TIMOFFRZ_TYPEID		156
#define TIMRPTENA_TYPEID		157
#define TRGOPS_TYPEID		158
#define TRGS_TYPEID		159
#define UNITVARRTG_TYPEID		160
#define UNKPWRHA_TYPEID		161
#define USEST_TYPEID		162
#define VARRTG_TYPEID		163
#define VARTG_TYPEID		164
#define VND_TYPEID		165
#define VRTG_TYPEID		166
#define WRNLEV_TYPEID		167
#define WRNST_TYPEID		168
#define PHSTAR_TYPEID		169
#define SBO_TYPEID		170
#define STNUM_TYPEID		171
#define HOLDTIM_TYPEID		172
#define BACKTIM_TYPEID		173
#define PHSID_TYPEID		174
#define DNA_TYPEID		175
#define USERST_TYPEID		176
#define RTYP_BOOL_TYPEID		177
#define RTYP_BTIME6_TYPEID		178
#define RTYP_BSTR6_TYPEID		179
#define RTYP_BSTR8_TYPEID		180
#define RTYP_BSTR9_TYPEID		181
#define RTYP_BVSTR6_TYPEID		182
#define RTYP_BVSTR8_TYPEID		183
#define RTYP_BVSTR10_TYPEID		184
#define RTYP_INT8U_TYPEID		185
#define RTYP_INT16U_TYPEID		186
#define RTYP_OSTR8_TYPEID		187
#define RTYP_VSTR32_TYPEID		188
#define RTYP_VSTR65_TYPEID		189
#define RTYP_INT32U_TYPEID		190
#define AnalogueValue_TYPEID		191
#define ScaledValueConfig_TYPEID		192
#define RangeConfig_TYPEID		193
#define ValWithTrans_TYPEID		194
#define PulseConfig_TYPEID		195
#define Originator_TYPEID		196
#define Unit_TYPEID		197
#define Vector_TYPEID		198
#define Point_TYPEID		199
#define SPS_ST_TYPEID		200
#define SPS_SV_TYPEID		201
#define SPS_DC_TYPEID		202
#define SPS_EX_TYPEID		203
#define DPS_ST_TYPEID		204
#define DPS_SV_TYPEID		205
#define DPS_DC_TYPEID		206
#define DPS_EX_TYPEID		207
#define INS_ST_TYPEID		208
#define INS_SV_TYPEID		209
#define INS_DC_TYPEID		210
#define INS_EX_TYPEID		211
#define ACT_ST_TYPEID		212
#define ACT_CF_TYPEID		213
#define ACT_DC_TYPEID		214
#define ACT_EX_TYPEID		215
#define ACD_ST_TYPEID		216
#define ACD_DC_TYPEID		217
#define ACD_EX_TYPEID		218
#define SEC_ST_TYPEID		219
#define SEC_DC_TYPEID		220
#define SEC_EX_TYPEID		221
#define BCR_ST_TYPEID		222
#define BCR_CF_TYPEID		223
#define BCR_DC_TYPEID		224
#define BCR_EX_TYPEID		225
#define MV_MX_TYPEID		226
#define MV_SV_TYPEID		227
#define MV_CF_TYPEID		228
#define MV_DC_TYPEID		229
#define MV_EX_TYPEID		230
#define CMV_MX_TYPEID		231
#define CMV_SV_TYPEID		232
#define CMV_CF_TYPEID		233
#define CMV_DC_TYPEID		234
#define CMV_EX_TYPEID		235
#define SAV_MX_TYPEID		236
#define SAV_CF_TYPEID		237
#define SAV_DC_TYPEID		238
#define SAV_EX_TYPEID		239
#define WYE_MX_TYPEID		240
#define WYE_SV_TYPEID		241
#define WYE_CF_TYPEID		242
#define WYE_DC_TYPEID		243
#define WYE_EX_TYPEID		244
#define DEL_MX_TYPEID		245
#define DEL_SV_TYPEID		246
#define DEL_CF_TYPEID		247
#define DEL_DC_TYPEID		248
#define DEL_EX_TYPEID		249
#define SEQ_MX_TYPEID		250
#define SEQ_SV_TYPEID		251
#define SEQ_CF_TYPEID		252
#define SEQ_DC_TYPEID		253
#define SEQ_EX_TYPEID		254
#define VectorHMV_TYPEID		255
#define HMV_MX_TYPEID		256
#define HMV_CF_TYPEID		257
#define HMV_DC_TYPEID		258
#define HMV_EX_TYPEID		259
#define VectorHWYE_TYPEID		260
#define HWYE_MX_TYPEID		261
#define HWYE_CF_TYPEID		262
#define HWYE_DC_TYPEID		263
#define HWYE_EX_TYPEID		264
#define VectorHDEL_TYPEID		265
#define HDEL_MX_TYPEID		266
#define HDEL_CF_TYPEID		267
#define HDEL_DC_TYPEID		268
#define HDEL_EX_TYPEID		269
#define Select_TYPEID		270
#define TestStatus_TYPEID		271
#define Cterm_TYPEID		272
#define Check_TYPEID		273
#define CtlModels_TYPEID		274
#define SboClasses_TYPEID		275
#define SPCSelectWithValue_TYPEID		276
#define SPCOperate_TYPEID		277
#define SPCTimeActivatedOperate_TYPEID		278
#define Cancel_TYPEID		279
#define SPC_CO_TYPEID		280
#define SPC_ST_TYPEID		281
#define SPC_SV_TYPEID		282
#define SPC_CF_TYPEID		283
#define SPC_DC_TYPEID		284
#define SPC_EX_TYPEID		285
#define DPCSelectWithValue_TYPEID		286
#define DPCOperate_TYPEID		287
#define DPCTimeActivatedOperate_TYPEID		288
#define DPC_CO_TYPEID		289
#define DPC_ST_TYPEID		290
#define DPC_SV_TYPEID		291
#define DPC_CF_TYPEID		292
#define DPC_DC_TYPEID		293
#define DPC_EX_TYPEID		294
#define INCSelectWithValue_TYPEID		295
#define INCOperate_TYPEID		296
#define INCTimeActivatedOperate_TYPEID		297
#define INC_CO_TYPEID		298
#define INC_ST_TYPEID		299
#define INC_SV_TYPEID		300
#define INC_CF_TYPEID		301
#define INC_DC_TYPEID		302
#define INC_EX_TYPEID		303
#define BSCSelectWithValue_TYPEID		304
#define BSCOperate_TYPEID		305
#define BSCTimeActivatedOperate_TYPEID		306
#define BSC_CO_TYPEID		307
#define BSC_ST_TYPEID		308
#define BSC_SV_TYPEID		309
#define BSC_CF_TYPEID		310
#define BSC_DC_TYPEID		311
#define BSC_EX_TYPEID		312
#define ISCSelectWithValue_TYPEID		313
#define ISCOperate_TYPEID		314
#define ISCTimeActivatedOperate_TYPEID		315
#define ISC_CO_TYPEID		316
#define ISC_ST_TYPEID		317
#define ISC_SV_TYPEID		318
#define ISC_CF_TYPEID		319
#define ISC_DC_TYPEID		320
#define ISC_EX_TYPEID		321
#define APC_MX_TYPEID		322
#define APC_SP_TYPEID		323
#define APC_CF_TYPEID		324
#define APC_DC_TYPEID		325
#define APC_EX_TYPEID		326
#define SPG_SP_TYPEID		327
#define SPG_SG_TYPEID		328
#define SPG_SE_TYPEID		329
#define SPG_DC_TYPEID		330
#define SPG_EX_TYPEID		331
#define ING_SP_TYPEID		332
#define ING_SG_TYPEID		333
#define ING_SE_TYPEID		334
#define ING_CF_TYPEID		335
#define ING_DC_TYPEID		336
#define ING_EX_TYPEID		337
#define ASG_SP_TYPEID		338
#define ASG_SG_TYPEID		339
#define ASG_SE_TYPEID		340
#define ASG_CF_TYPEID		341
#define ASG_DC_TYPEID		342
#define ASG_EX_TYPEID		343
#define CURVE_SP_TYPEID		344
#define CURVE_SG_TYPEID		345
#define CURVE_SE_TYPEID		346
#define CURVE_DC_TYPEID		347
#define CURVE_EX_TYPEID		348
#define DPL_DC_TYPEID		349
#define DPL_EX_TYPEID		350
#define LPL_DC_TYPEID		351
#define LPL_EX_TYPEID		352
#define PointCSD_TYPEID		353
#define CSD_DC_TYPEID		354
#define CSD_EX_TYPEID		355
#define IEC_BRCB_TYPEID		356
#define IEC_URCB_TYPEID		357
#define SGCB_TYPEID			358


/************************************************************************/

/************************************************************************/


/*	Common Strings Index Defines	*/

#ifndef USE_RT_TYPE_2

#define FO_F_STRING_INDEX	 1
#define FO_SCALEFACTOR_STRING_INDEX	 2
#define FO_OFFSET_STRING_INDEX	 3
#define FO_HHLIM_STRING_INDEX	 4
#define FO_HLIM_STRING_INDEX	 5
#define FO_ILIM_STRING_INDEX	 6
#define FO_IILIM_STRING_INDEX	 7
#define FO_MIN_STRING_INDEX	 8
#define FO_MAX_STRING_INDEX	 9
#define FO_POSVAL_STRING_INDEX	 10
#define FO_TRANSIND_STRING_INDEX	 11
#define FO_CMDQUAL_STRING_INDEX	 12
#define FO_ONDUR_STRING_INDEX	 13
#define FO_OFFDUR_STRING_INDEX	 14
#define FO_NUMPIS_STRING_INDEX	 15
#define FO_ORCAT_STRING_INDEX	 16
#define FO_ORIDENT_STRING_INDEX	 17
#define FO_SIUNIT_STRING_INDEX	 18
#define FO_MULTIPLIER_STRING_INDEX	 19
#define FO_MAG_STRING_INDEX	 20
#define FO_ANG_STRING_INDEX	 21
#define FO_XVAL_STRING_INDEX	 22
#define FO_YVAL_STRING_INDEX	 23
#define FO_STVAL_STRING_INDEX	 24
#define FO_Q_STRING_INDEX	 25
#define FO_T_STRING_INDEX	 26
#define FO_SUBENA_STRING_INDEX	 27
#define FO_SUBVAL_STRING_INDEX	 28
#define FO_SUBQ_STRING_INDEX	 29
#define FO_SUBID_STRING_INDEX	 30
#define FO_D_STRING_INDEX	 31
#define FO_CDCNS_STRING_INDEX	 32
#define FO_CDCNAME_STRING_INDEX	 33
#define FO_DATANS_STRING_INDEX	 34
#define FO_GENERAL_STRING_INDEX	 35
#define FO_PHSA_STRING_INDEX	 36
#define FO_PHSB_STRING_INDEX	 37
#define FO_PHSC_STRING_INDEX	 38
#define FO_NEUT_STRING_INDEX	 39
#define FO_OPERTM_STRING_INDEX	 40
#define FO_DIRGENERAL_STRING_INDEX	 41
#define FO_DIRPHSA_STRING_INDEX	 42
#define FO_DIRPHSB_STRING_INDEX	 43
#define FO_DIRPHSC_STRING_INDEX	 44
#define FO_DIRNEUT_STRING_INDEX	 45
#define FO_CNT_STRING_INDEX	 46
#define FO_SEV_STRING_INDEX	 47
#define FO_ADDR_STRING_INDEX	 48
#define FO_ADDRINFO_STRING_INDEX	 49
#define FO_ACTVAL_STRING_INDEX	 50
#define FO_FRVAL_STRING_INDEX	 51
#define FO_FRTM_STRING_INDEX	 52
#define FO_UNITS_STRING_INDEX	 53
#define FO_PULSQTY_STRING_INDEX	 54
#define FO_FRENA_STRING_INDEX	 55
#define FO_STRTM_STRING_INDEX	 56
#define FO_FRPD_STRING_INDEX	 57
#define FO_FRRS_STRING_INDEX	 58
#define FO_INSTMAG_STRING_INDEX	 59
#define FO_RANGE_STRING_INDEX	 60
#define FO_SUBMAG_STRING_INDEX	 61
#define FO_DB_STRING_INDEX	 62
#define FO_ZERODB_STRING_INDEX	 63
#define FO_SVC_STRING_INDEX	 64
#define FO_RANGEC_STRING_INDEX	 65
#define FO_SMPRATE_STRING_INDEX	 66
#define FO_INSTCVAL_STRING_INDEX	 67
#define FO_CVAL_STRING_INDEX	 68
#define FO_SUBCVAL_STRING_INDEX	 69
#define FO_MAGSVC_STRING_INDEX	 70
#define FO_ANGSVC_STRING_INDEX	 71
#define FO_ANGREF_STRING_INDEX	 72
#define FO_NET_STRING_INDEX	 73
#define FO_RES_STRING_INDEX	 74
#define FO_PHSAB_STRING_INDEX	 75
#define FO_PHSBC_STRING_INDEX	 76
#define FO_PHSCA_STRING_INDEX	 77
#define FO_C1_STRING_INDEX	 78
#define FO_C2_STRING_INDEX	 79
#define FO_C3_STRING_INDEX	 80
#define FO_SEQT_STRING_INDEX	 81
#define FO_PHSREF_STRING_INDEX	 82
#define FO_HAR_STRING_INDEX	 83
#define FO_NUMHAR_STRING_INDEX	 84
#define FO_NUMCYCL_STRING_INDEX	 85
#define FO_EVALTM_STRING_INDEX	 86
#define FO_FREQUENCY_STRING_INDEX	 87
#define FO_HVREF_STRING_INDEX	 88
#define FO_RMSCYC_STRING_INDEX	 89
#define FO_PHSAHAR_STRING_INDEX	 90
#define FO_PHSBHAR_STRING_INDEX	 91
#define FO_PHSCHAR_STRING_INDEX	 92
#define FO_NEUTHAR_STRING_INDEX	 93
#define FO_NETHAR_STRING_INDEX	 94
#define FO_RESHAR_STRING_INDEX	 95
#define FO_PHSABHAR_STRING_INDEX	 96
#define FO_PHSBCHAR_STRING_INDEX	 97
#define FO_PHSCAHAR_STRING_INDEX	 98
#define FO_VALUE_STRING_INDEX	 99
#define FO_T_STRING_INDEX	 100
#define FO_TEST_STRING_INDEX	 101
#define FO_CHECK_STRING_INDEX	 102
#define FO_CTERM_STRING_INDEX	 103
#define FO_CTLVAL_STRING_INDEX	 104
#define FO_SBO_STRING_INDEX	 105
#define FO_SBOW_STRING_INDEX	 106
#define FO_OPER_STRING_INDEX	 107
#define FO_OPERTA_STRING_INDEX	 108
#define FO_CANCEL_STRING_INDEX	 109
#define FO_ORIGIN_STRING_INDEX	 110
#define FO_CTLNUM_STRING_INDEX	 111
#define FO_STSELD_STRING_INDEX	 112
#define FO_PULSECONFIG_STRING_INDEX	 113
#define FO_CTLMODEL_STRING_INDEX	 114
#define FO_SBOTIMEOUT_STRING_INDEX	 115
#define FO_SBOCLASS_STRING_INDEX	 116
#define FO_MINVAL_STRING_INDEX	 117
#define FO_MAXVAL_STRING_INDEX	 118
#define FO_STEPSIZE_STRING_INDEX	 119
#define FO_VALWTR_STRING_INDEX	 120
#define FO_PERSISTENT_STRING_INDEX	 121
#define FO_SETMAG_STRING_INDEX	 122
#define FO_SETVAL_STRING_INDEX	 123
#define FO_SETCHARACT_STRING_INDEX	 124
#define FO_SETPARA_STRING_INDEX	 125
#define FO_SETPARB_STRING_INDEX	 126
#define FO_SETPARC_STRING_INDEX	 127
#define FO_SETPARD_STRING_INDEX	 128
#define FO_SETPARE_STRING_INDEX	 129
#define FO_SETPARF_STRING_INDEX	 130
#define FO_VENDOR_STRING_INDEX	 131
#define FO_HWREV_STRING_INDEX	 132
#define FO_SWREV_STRING_INDEX	 133
#define FO_SERNUM_STRING_INDEX	 134
#define FO_MODEL_STRING_INDEX	 135
#define FO_LOCATION_STRING_INDEX	 136
#define FO_CONFIGREV_STRING_INDEX	 137
#define FO_LDNS_STRING_INDEX	 138
#define FO_LNNS_STRING_INDEX	 139
#define FO_XUNIT_STRING_INDEX	 140
#define FO_XD_STRING_INDEX	 141
#define FO_YUNIT_STRING_INDEX	 142
#define FO_YD_STRING_INDEX	 143
#define FO_NUMPTS_STRING_INDEX	 144
#define FO_CRVPTS_STRING_INDEX	 145
#define FO_RPTENA_STRING_INDEX	 146
#define FO_RPTID_STRING_INDEX	 147
#define FO_DATSET_STRING_INDEX	 148
#define FO_CONFREV_STRING_INDEX	 149
#define FO_OPTFLDS_STRING_INDEX	 150
#define FO_BUFTIM_STRING_INDEX	 151
#define FO_SQNUM_STRING_INDEX	 152
#define FO_TRGOPS_STRING_INDEX	 153
#define FO_INTGPD_STRING_INDEX	 154
#define FO_GI_STRING_INDEX	 155
#define FO_PURGEBUF_STRING_INDEX	 156
#define FO_ENTRYID_STRING_INDEX	 157
#define FO_TIMEOFENTRY_STRING_INDEX	 158
#define FO_RESV_STRING_INDEX	 159
#define FO_NUMOFSG_STRING_INDEX	 160
#define FO_ACTSG_STRING_INDEX	 161
#define FO_EDITSG_STRING_INDEX	 162
#define FO_CNFEDIT_STRING_INDEX	 163
#define FO_LACTTIM_STRING_INDEX	 164
#endif


/************************************************************************/
/* TYPEDEFS for MMS TYPES	                                              */
/************************************************************************/

/* Use ":CF", "-notypedefs" in the ODF file to not include this line */
#define USE_MMS_TYPEDEFS

#if defined (USE_MMS_TYPEDEFS)

typedef ST_BOOLEAN BOOLEAN_TDEF;

typedef ST_INT8 INT8_TDEF;

typedef ST_INT16 INT16_TDEF;

typedef ST_INT32 INT32_TDEF;

typedef ST_INT32 INT128_TDEF;

typedef ST_UINT8 INT8U_TDEF;

typedef ST_UINT16 INT16U_TDEF;

typedef ST_UINT32 INT32U_TDEF;

typedef ST_FLOAT FLOAT32_TDEF;

typedef ST_DOUBLE FLOAT64_TDEF;

typedef ST_INT8 ENUMERATED8_TDEF;

typedef ST_INT16 ENUMERATED16_TDEF;

typedef struct     /* OVstring */
  {
  ST_INT16 len_1;
  ST_UCHAR data_1[8];
  }  OCTET_STRING8_TDEF;  /* Octetstring */

typedef struct     /* OVstring */
  {
  ST_INT16 len_1;
  ST_UCHAR data_1[64];
  }  OCTET_STRING64_TDEF;  /* Octetstring */

typedef ST_CHAR VISIBLE_STRING255_TDEF[256];  /* Visible String */

typedef ST_CHAR VISIBLE_STRING64_TDEF[65];  /* Visible String */

typedef ST_CHAR VISIBLE_STRING97_TDEF[98];  /* Visible String */

typedef struct
  {
  ST_UINT32 secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 fraction;
  ST_UINT32 qflags;
  } UTC_TM_TDEF;

typedef ST_UCHAR CODED_ENUM2_TDEF[1];  /* Bitstring */

typedef ST_CHAR UNICODE_STRING255_TDEF[512];

typedef struct
  {
  ST_UINT32 secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 fraction;
  ST_UINT32 qflags;
  } TimeStamp_TDEF;

typedef struct
  {
  ST_INT32 btime6_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 btime6_days;
  } EntryTime_TDEF;

typedef struct     /* BVstring */
  {
  ST_INT16 len_1;
  ST_UCHAR data_1[2];
  }  Quality_TDEF;  /* Bitstring */

typedef ST_CHAR IDENT_TDEF[66];  /* Visible String */

typedef ST_BOOLEAN BOOL_TDEF;

typedef ST_UCHAR B2_TDEF[1];  /* Bitstring */

typedef ST_CHAR D_TDEF[33];  /* Visible String */

typedef ST_UINT16 DB_TDEF;

typedef ST_FLOAT F_TDEF;

typedef ST_FLOAT FF_TDEF;

typedef ST_INT16 HL_TDEF;

typedef ST_INT16 HHL_TDEF;

typedef ST_INT16 LL_TDEF;

typedef ST_INT16 LLL_TDEF;

typedef ST_INT16 I_TDEF;

typedef ST_INT16 FI_TDEF;

typedef ST_FLOAT O_TDEF;

typedef struct     /* BVstring */
  {
  ST_INT16 len_1;
  ST_UCHAR data_1[2];
  }  Q_TDEF;  /* Bitstring */

typedef ST_UINT32 R_TDEF;

typedef ST_UINT32 FR_TDEF;

typedef ST_FLOAT S_TDEF;

typedef struct
  {
  ST_INT32 btime6_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 btime6_days;
  } T_TDEF;

typedef struct
  {
  ST_INT32 btime6_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 btime6_days;
  } FT_TDEF;

typedef ST_BOOLEAN PP_TDEF;

typedef ST_INT16 U_TDEF;

typedef ST_CHAR VSTR8_TDEF[9];  /* Visible String */

typedef ST_CHAR VSTR16_TDEF[17];  /* Visible String */

typedef ST_CHAR VSTR32_TDEF[33];  /* Visible String */

typedef ST_CHAR VSTR64_TDEF[65];  /* Visible String */

typedef ST_CHAR VSTR65_TDEF[66];  /* Visible String */

typedef ST_CHAR VSTR128_TDEF[129];  /* Visible String */

typedef ST_UCHAR BSTR1_TDEF[1];  /* Bitstring */

typedef ST_UCHAR BSTR2_TDEF[1];  /* Bitstring */

typedef ST_UCHAR BSTR8_TDEF[1];  /* Bitstring */

typedef ST_UCHAR BSTR16_TDEF[2];  /* Bitstring */

typedef ST_UCHAR BSTR32_TDEF[4];  /* Bitstring */

typedef struct     /* BVstring */
  {
  ST_INT16 len_1;
  ST_UCHAR data_1[1];
  }  VBSTR8_TDEF;  /* Bitstring */

typedef struct     /* BVstring */
  {
  ST_INT16 len_1;
  ST_UCHAR data_1[2];
  }  VBSTR16_TDEF;  /* Bitstring */

typedef struct     /* BVstring */
  {
  ST_INT16 len_1;
  ST_UCHAR data_1[4];
  }  VBSTR32_TDEF;  /* Bitstring */

typedef ST_INT8 INT8S_TDEF;

typedef ST_INT16 INT16S_TDEF;

typedef ST_INT32 INT32S_TDEF;

typedef ST_FLOAT FLT32_TDEF;

typedef ST_DOUBLE FLT64_TDEF;

typedef ST_INT32  BTIME4_TDEF;  /* Btime4 is one ST_INT32 */

typedef struct
  {
  ST_INT32 btime6_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 btime6_days;
  } BTIME6_TDEF;

typedef ST_INT8 ENUM8_TDEF;

typedef ST_INT16 ENUM16_TDEF;

typedef ST_INT32 MAG_TDEF;

typedef ST_INT32 ANG_TDEF;

typedef ST_BOOLEAN ACCRPTENA_TDEF;

typedef ST_BOOLEAN ACCRS_TDEF;

typedef ST_CHAR ACCSET_TDEF[17];  /* Visible String */

typedef ST_UCHAR ACTTAGARR_TDEF[1];  /* Bitstring */

typedef ST_CHAR ANCESTRY_TDEF[33];  /* Visible String */

typedef ST_CHAR ANFMT_TDEF[7];  /* Visible String */

typedef ST_UINT32 BUFTIM_TDEF;

typedef ST_INT32 CID_TDEF;

typedef ST_CHAR CKTID_TDEF[33];  /* Visible String */

typedef ST_INT8 CKTPHS_TDEF;

typedef ST_CHAR CLASS_TDEF[33];  /* Visible String */

typedef ST_CHAR COMMADR_TDEF[17];  /* Visible String */

typedef ST_CHAR COMMREV_TDEF[9];  /* Visible String */

typedef ST_CHAR CONTCURRTG_TDEF[17];  /* Visible String */

typedef ST_UINT16 COUNT_TDEF;

typedef ST_BOOLEAN CRIRPT_TDEF;

typedef ST_CHAR DATSETNAM_TDEF[17];  /* Visible String */

typedef ST_CHAR DESTAE_TDEF[33];  /* Visible String */

typedef ST_UINT16 DEVFCT_TDEF;

typedef ST_CHAR DEVMDLS_TDEF[129];  /* Visible String */

typedef ST_INT8 DOW_TDEF;

typedef ST_INT32  DOWSCHED_TDEF[6];

typedef ST_BOOLEAN ENABLE_TDEF;

typedef ST_UCHAR ENCOPT_TDEF[1];  /* Bitstring */

typedef ST_CHAR ENROLL_TDEF[33];  /* Visible String */

typedef ST_CHAR EORBDESC_TDEF[65];  /* Visible String */

typedef ST_CHAR EVACON_TDEF[33];  /* Visible String */

typedef ST_CHAR EVACNS_TDEF[33];  /* Visible String */

typedef ST_CHAR EVACRI_TDEF[33];  /* Visible String */

typedef ST_CHAR EVAFCT_TDEF[33];  /* Visible String */

typedef ST_CHAR EVAPAR_TDEF[33];  /* Visible String */

typedef ST_BOOLEAN EVTENA_TDEF;

typedef ST_UINT16 FLTCURDUR_TDEF;

typedef ST_INT16 FLTCURRTG_TDEF;

typedef ST_BOOLEAN FRZENA_TDEF;

typedef ST_UINT32 FRZPD_TDEF;

typedef ST_FLOAT FWDPWRHA_TDEF[31];

typedef ST_CHAR HWREV_TDEF[9];  /* Visible String */

typedef ST_CHAR HZRTG_TDEF[33];  /* Visible String */

typedef ST_CHAR INDAT_TDEF[66];  /* Visible String */

typedef ST_UINT32 INTGPD_TDEF;

typedef ST_UINT16 LINLENM_TDEF;

typedef ST_CHAR LOC_TDEF[129];  /* Visible String */

typedef ST_BOOLEAN LOGENA_TDEF;

typedef ST_CHAR LOGENR_TDEF[33];  /* Visible String */

typedef ST_CHAR LOGNAM_TDEF[33];  /* Visible String */

typedef ST_UINT16 LOGSIZE_TDEF;

typedef ST_BOOLEAN LOGWRP_TDEF;

typedef ST_UINT8 MAC_TDEF;

typedef ST_CHAR MDL_TDEF[33];  /* Visible String */

typedef ST_INT8 MED_TDEF;

typedef ST_INT8 MXREF_TDEF;

typedef ST_INT8 MXTYP_TDEF;

typedef ST_CHAR NAME_TDEF[33];  /* Visible String */

typedef struct
  {
  ST_INT32 btime6_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 btime6_days;
  } NEWTIM_TDEF;

typedef ST_UINT16 NUMBITS_TDEF;

typedef ST_UINT16 NUMPLS_TDEF;

typedef ST_UINT16 NUMSMP_TDEF;

typedef ST_CHAR NUMUNIT_TDEF[33];  /* Visible String */

typedef ST_UINT32 OFFDUR_TDEF;

typedef struct
  {
  ST_INT32 btime6_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 btime6_days;
  } OLDTIM_TDEF;

typedef ST_UINT32 ONDUR_TDEF;

typedef ST_UCHAR OPERDEV_TDEF[1];  /* Bitstring */

typedef struct     /* BVstring */
  {
  ST_INT16 len_1;
  ST_UCHAR data_1[1];
  }  OPTFLDS_TDEF;  /* Bitstring */

typedef ST_CHAR OUTDAT_TDEF[66];  /* Visible String */

typedef ST_BOOLEAN OVRST_TDEF;

typedef ST_CHAR OWN_TDEF[33];  /* Visible String */

typedef ST_INT8 PRO_TDEF;

typedef ST_FLOAT PWRHA_TDEF[31];

typedef ST_BOOLEAN QURPTENA_TDEF;

typedef ST_UINT32 RBEPD_TDEF;

typedef ST_BOOLEAN RPTENA_TDEF;

typedef ST_CHAR RPTID_TDEF[33];  /* Visible String */

typedef ST_FLOAT RVSPWRHA_TDEF[31];

typedef ST_BOOLEAN SBOENA_TDEF;

typedef ST_UINT8 SETTIMOUT_TDEF;

typedef ST_UINT32 SEQNUM_TDEF;

typedef ST_CHAR SERNUM_TDEF[33];  /* Visible String */

typedef ST_CHAR SFTREV_TDEF[9];  /* Visible String */

typedef ST_UINT16 SMPRATE_TDEF;

typedef ST_CHAR TAGD_TDEF[129];  /* Visible String */

typedef ST_UINT8 TAGID_TDEF;

typedef ST_CHAR TAGOWN_TDEF[33];  /* Visible String */

typedef ST_UCHAR TAGTYP_TDEF[1];  /* Bitstring */

typedef ST_CHAR TEMPRAT_TDEF[17];  /* Visible String */

typedef ST_CHAR TEMPRTG_TDEF[17];  /* Visible String */

typedef struct
  {
  ST_INT32 btime6_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 btime6_days;
  } TIMOFFRZ_TDEF;

typedef ST_BOOLEAN TIMRPTENA_TDEF;

typedef ST_UCHAR TRGOPS_TDEF[1];  /* Bitstring */

typedef ST_UINT16 TRGS_TDEF;

typedef ST_CHAR UNITVARRTG_TDEF[33];  /* Visible String */

typedef ST_FLOAT UNKPWRHA_TDEF[31];

typedef ST_BOOLEAN USEST_TDEF;

typedef ST_CHAR VARRTG_TDEF[17];  /* Visible String */

typedef ST_CHAR VARTG_TDEF[17];  /* Visible String */

typedef ST_CHAR VND_TDEF[33];  /* Visible String */

typedef ST_CHAR VRTG_TDEF[17];  /* Visible String */

typedef ST_UINT16 WRNLEV_TDEF;

typedef ST_BOOLEAN WRNST_TDEF;

typedef ST_INT8 PHSTAR_TDEF;

typedef ST_CHAR SBO_TDEF[66];  /* Visible String */

typedef ST_UINT32 STNUM_TDEF;

typedef ST_UINT32 HOLDTIM_TDEF;

typedef ST_UINT32 BACKTIM_TDEF;

typedef ST_UINT16 PHSID_TDEF;

typedef ST_UCHAR DNA_TDEF[8];  /* Bitstring */

typedef struct     /* BVstring */
  {
  ST_INT16 len_1;
  ST_UCHAR data_1[16];
  }  USERST_TDEF;  /* Bitstring */

typedef ST_BOOLEAN RTYP_BOOL_TDEF;

typedef struct
  {
  ST_INT32 btime6_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 btime6_days;
  } RTYP_BTIME6_TDEF;

typedef ST_UCHAR RTYP_BSTR6_TDEF[1];  /* Bitstring */

typedef ST_UCHAR RTYP_BSTR8_TDEF[1];  /* Bitstring */

typedef ST_UCHAR RTYP_BSTR9_TDEF[2];  /* Bitstring */

typedef struct     /* BVstring */
  {
  ST_INT16 len_1;
  ST_UCHAR data_1[1];
  }  RTYP_BVSTR6_TDEF;  /* Bitstring */

typedef struct     /* BVstring */
  {
  ST_INT16 len_1;
  ST_UCHAR data_1[1];
  }  RTYP_BVSTR8_TDEF;  /* Bitstring */

typedef struct     /* BVstring */
  {
  ST_INT16 len_1;
  ST_UCHAR data_1[2];
  }  RTYP_BVSTR10_TDEF;  /* Bitstring */

typedef ST_UINT8 RTYP_INT8U_TDEF;

typedef ST_UINT16 RTYP_INT16U_TDEF;

typedef ST_UCHAR RTYP_OSTR8_TDEF[8];  /* Octetstring */

typedef ST_CHAR RTYP_VSTR32_TDEF[33];  /* Visible String */

typedef ST_CHAR RTYP_VSTR65_TDEF[66];  /* Visible String */

typedef ST_UINT32 RTYP_INT32U_TDEF;

typedef struct
  {
  ST_FLOAT f;
  } AnalogueValue_TDEF;

typedef struct
  {
  ST_FLOAT scaleFactor;
  ST_FLOAT offset;
  } ScaledValueConfig_TDEF;

typedef struct
  {
  struct
    {
    ST_FLOAT f;
    } hhLim;
  struct
    {
    ST_FLOAT f;
    } hLim;
  struct
    {
    ST_FLOAT f;
    } ILim;
  struct
    {
    ST_FLOAT f;
    } IILim;
  struct
    {
    ST_FLOAT f;
    } min;
  struct
    {
    ST_FLOAT f;
    } max;
  } RangeConfig_TDEF;

typedef struct
  {
  ST_INT8 posVal;
  ST_BOOLEAN transInd;
  } ValWithTrans_TDEF;

typedef struct
  {
  ST_INT8 cmdQual;
  ST_UINT32 onDur;
  ST_UINT32 offDur;
  ST_UINT32 numPIs;
  } PulseConfig_TDEF;

typedef struct
  {
  ST_INT8 orCat;
  struct     /* OVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[64];
    } orIdent;
  } Originator_TDEF;

typedef struct
  {
  ST_INT8 SIUnit;
  ST_INT8 multiplier;
  } Unit_TDEF;

typedef struct
  {
  struct
    {
    ST_FLOAT f;
    } mag;
  struct
    {
    ST_FLOAT f;
    } ang;
  } Vector_TDEF;

typedef struct
  {
  ST_FLOAT xVal;
  ST_FLOAT yVal;
  } Point_TDEF;

typedef struct
  {
  ST_BOOLEAN stVal;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  } SPS_ST_TDEF;

typedef struct
  {
  ST_BOOLEAN subEna;
  ST_BOOLEAN subVal;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } subQ;
  ST_CHAR subID[65];
  } SPS_SV_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } SPS_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } SPS_EX_TDEF;

typedef struct
  {
  ST_UCHAR stVal[1];
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  } DPS_ST_TDEF;

typedef struct
  {
  ST_BOOLEAN subEna;
  ST_UCHAR subVal[1];
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } subQ;
  ST_CHAR subID[65];
  } DPS_SV_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } DPS_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } DPS_EX_TDEF;

typedef struct
  {
  ST_INT32 stVal;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  } INS_ST_TDEF;

typedef struct
  {
  ST_BOOLEAN subEna;
  ST_INT32 subVal;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } subQ;
  ST_CHAR subID[65];
  } INS_SV_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } INS_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } INS_EX_TDEF;

typedef struct
  {
  ST_BOOLEAN general;
  ST_BOOLEAN phsA;
  ST_BOOLEAN phsB;
  ST_BOOLEAN phsC;
  ST_BOOLEAN neut;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  } ACT_ST_TDEF;

typedef struct
  {
  ST_UINT32 operTm_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 operTm_fraction;
  ST_UINT32 operTm_qflags;
  } ACT_CF_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } ACT_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } ACT_EX_TDEF;

typedef struct
  {
  ST_BOOLEAN general;
  ST_INT8 dirGeneral;
  ST_BOOLEAN phsA;
  ST_INT8 dirphsA;
  ST_BOOLEAN phsB;
  ST_INT8 dirphsB;
  ST_BOOLEAN phsC;
  ST_INT8 dirphsC;
  ST_BOOLEAN neut;
  ST_INT8 dirNeut;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  } ACD_ST_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } ACD_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } ACD_EX_TDEF;

typedef struct
  {
  ST_UINT32 cnt;
  ST_INT8 sev;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  struct     /* OVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[64];
    } addr;
  ST_CHAR addrInfo[65];
  } SEC_ST_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } SEC_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } SEC_EX_TDEF;

typedef struct
  {
  ST_INT32 actVal;
  ST_INT32 frVal;
  ST_UINT32 frTm_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 frTm_fraction;
  ST_UINT32 frTm_qflags;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  } BCR_ST_TDEF;

typedef struct
  {
  struct
    {
    ST_INT8 SIUnit;
    ST_INT8 multiplier;
    } units;
  ST_FLOAT pulsQty;
  ST_BOOLEAN frEna;
  ST_UINT32 strTm_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 strTm_fraction;
  ST_UINT32 strTm_qflags;
  ST_INT32 frPd;
  ST_BOOLEAN frRs;
  } BCR_CF_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } BCR_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } BCR_EX_TDEF;

typedef struct
  {
  struct
    {
    ST_FLOAT f;
    } instMag;
  struct
    {
    ST_FLOAT f;
    } mag;
  ST_INT8 range;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  } MV_MX_TDEF;

typedef struct
  {
  ST_BOOLEAN subEna;
  struct
    {
    ST_FLOAT f;
    } subMag;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } subQ;
  ST_CHAR subID[65];
  } MV_SV_TDEF;

typedef struct
  {
  struct
    {
    ST_INT8 SIUnit;
    ST_INT8 multiplier;
    } units;
  ST_UINT32 db;
  ST_UINT32 zeroDb;
  struct
    {
    ST_FLOAT scaleFactor;
    ST_FLOAT offset;
    } sVC;
  struct
    {
    struct
      {
      ST_FLOAT f;
      } hhLim;
    struct
      {
      ST_FLOAT f;
      } hLim;
    struct
      {
      ST_FLOAT f;
      } ILim;
    struct
      {
      ST_FLOAT f;
      } IILim;
    struct
      {
      ST_FLOAT f;
      } min;
    struct
      {
      ST_FLOAT f;
      } max;
    } rangeC;
  ST_UINT32 smpRate;
  } MV_CF_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } MV_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } MV_EX_TDEF;

typedef struct
  {
  struct
    {
    struct
      {
      ST_FLOAT f;
      } mag;
    struct
      {
      ST_FLOAT f;
      } ang;
    } instCVal;
  struct
    {
    struct
      {
      ST_FLOAT f;
      } mag;
    struct
      {
      ST_FLOAT f;
      } ang;
    } cVal;
  ST_INT8 range;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  } CMV_MX_TDEF;

typedef struct
  {
  ST_BOOLEAN subEna;
  struct
    {
    struct
      {
      ST_FLOAT f;
      } mag;
    struct
      {
      ST_FLOAT f;
      } ang;
    } subCVal;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } subQ;
  ST_CHAR subID[65];
  } CMV_SV_TDEF;

typedef struct
  {
  struct
    {
    ST_INT8 SIUnit;
    ST_INT8 multiplier;
    } units;
  ST_UINT32 db;
  ST_UINT32 zeroDb;
  struct
    {
    struct
      {
      ST_FLOAT f;
      } hhLim;
    struct
      {
      ST_FLOAT f;
      } hLim;
    struct
      {
      ST_FLOAT f;
      } ILim;
    struct
      {
      ST_FLOAT f;
      } IILim;
    struct
      {
      ST_FLOAT f;
      } min;
    struct
      {
      ST_FLOAT f;
      } max;
    } rangeC;
  struct
    {
    ST_FLOAT scaleFactor;
    ST_FLOAT offset;
    } magSVC;
  struct
    {
    ST_FLOAT scaleFactor;
    ST_FLOAT offset;
    } angSVC;
  ST_INT8 angRef;
  ST_UINT32 smpRate;
  } CMV_CF_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } CMV_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } CMV_EX_TDEF;

typedef struct
  {
  struct
    {
    ST_FLOAT f;
    } instMag;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  } SAV_MX_TDEF;

typedef struct
  {
  struct
    {
    ST_INT8 SIUnit;
    ST_INT8 multiplier;
    } units;
  struct
    {
    ST_FLOAT scaleFactor;
    ST_FLOAT offset;
    } sVC;
  struct
    {
    ST_FLOAT f;
    } min;
  struct
    {
    ST_FLOAT f;
    } max;
  } SAV_CF_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } SAV_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } SAV_EX_TDEF;

typedef struct
  {
  struct
    {
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } instCVal;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } cVal;
    ST_INT8 range;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } q;
    ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
    ST_UINT32 t_fraction;
    ST_UINT32 t_qflags;
    } phsA;
  struct
    {
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } instCVal;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } cVal;
    ST_INT8 range;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } q;
    ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
    ST_UINT32 t_fraction;
    ST_UINT32 t_qflags;
    } phsB;
  struct
    {
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } instCVal;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } cVal;
    ST_INT8 range;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } q;
    ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
    ST_UINT32 t_fraction;
    ST_UINT32 t_qflags;
    } phsC;
  struct
    {
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } instCVal;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } cVal;
    ST_INT8 range;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } q;
    ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
    ST_UINT32 t_fraction;
    ST_UINT32 t_qflags;
    } neut;
  struct
    {
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } instCVal;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } cVal;
    ST_INT8 range;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } q;
    ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
    ST_UINT32 t_fraction;
    ST_UINT32 t_qflags;
    } net;
  struct
    {
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } instCVal;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } cVal;
    ST_INT8 range;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } q;
    ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
    ST_UINT32 t_fraction;
    ST_UINT32 t_qflags;
    } res;
  } WYE_MX_TDEF;

typedef struct
  {
  struct
    {
    ST_BOOLEAN subEna;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } subCVal;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } subQ;
    ST_CHAR subID[65];
    } phsA;
  struct
    {
    ST_BOOLEAN subEna;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } subCVal;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } subQ;
    ST_CHAR subID[65];
    } phsB;
  struct
    {
    ST_BOOLEAN subEna;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } subCVal;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } subQ;
    ST_CHAR subID[65];
    } phsC;
  struct
    {
    ST_BOOLEAN subEna;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } subCVal;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } subQ;
    ST_CHAR subID[65];
    } neut;
  struct
    {
    ST_BOOLEAN subEna;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } subCVal;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } subQ;
    ST_CHAR subID[65];
    } net;
  struct
    {
    ST_BOOLEAN subEna;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } subCVal;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } subQ;
    ST_CHAR subID[65];
    } res;
  } WYE_SV_TDEF;

typedef struct
  {
  struct
    {
    struct
      {
      ST_INT8 SIUnit;
      ST_INT8 multiplier;
      } units;
    ST_UINT32 db;
    ST_UINT32 zeroDb;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } hhLim;
      struct
        {
        ST_FLOAT f;
        } hLim;
      struct
        {
        ST_FLOAT f;
        } ILim;
      struct
        {
        ST_FLOAT f;
        } IILim;
      struct
        {
        ST_FLOAT f;
        } min;
      struct
        {
        ST_FLOAT f;
        } max;
      } rangeC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } magSVC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } angSVC;
    ST_INT8 angRef;
    ST_UINT32 smpRate;
    } phsA;
  struct
    {
    struct
      {
      ST_INT8 SIUnit;
      ST_INT8 multiplier;
      } units;
    ST_UINT32 db;
    ST_UINT32 zeroDb;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } hhLim;
      struct
        {
        ST_FLOAT f;
        } hLim;
      struct
        {
        ST_FLOAT f;
        } ILim;
      struct
        {
        ST_FLOAT f;
        } IILim;
      struct
        {
        ST_FLOAT f;
        } min;
      struct
        {
        ST_FLOAT f;
        } max;
      } rangeC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } magSVC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } angSVC;
    ST_INT8 angRef;
    ST_UINT32 smpRate;
    } phsB;
  struct
    {
    struct
      {
      ST_INT8 SIUnit;
      ST_INT8 multiplier;
      } units;
    ST_UINT32 db;
    ST_UINT32 zeroDb;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } hhLim;
      struct
        {
        ST_FLOAT f;
        } hLim;
      struct
        {
        ST_FLOAT f;
        } ILim;
      struct
        {
        ST_FLOAT f;
        } IILim;
      struct
        {
        ST_FLOAT f;
        } min;
      struct
        {
        ST_FLOAT f;
        } max;
      } rangeC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } magSVC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } angSVC;
    ST_INT8 angRef;
    ST_UINT32 smpRate;
    } phsC;
  struct
    {
    struct
      {
      ST_INT8 SIUnit;
      ST_INT8 multiplier;
      } units;
    ST_UINT32 db;
    ST_UINT32 zeroDb;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } hhLim;
      struct
        {
        ST_FLOAT f;
        } hLim;
      struct
        {
        ST_FLOAT f;
        } ILim;
      struct
        {
        ST_FLOAT f;
        } IILim;
      struct
        {
        ST_FLOAT f;
        } min;
      struct
        {
        ST_FLOAT f;
        } max;
      } rangeC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } magSVC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } angSVC;
    ST_INT8 angRef;
    ST_UINT32 smpRate;
    } neut;
  struct
    {
    struct
      {
      ST_INT8 SIUnit;
      ST_INT8 multiplier;
      } units;
    ST_UINT32 db;
    ST_UINT32 zeroDb;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } hhLim;
      struct
        {
        ST_FLOAT f;
        } hLim;
      struct
        {
        ST_FLOAT f;
        } ILim;
      struct
        {
        ST_FLOAT f;
        } IILim;
      struct
        {
        ST_FLOAT f;
        } min;
      struct
        {
        ST_FLOAT f;
        } max;
      } rangeC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } magSVC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } angSVC;
    ST_INT8 angRef;
    ST_UINT32 smpRate;
    } net;
  struct
    {
    struct
      {
      ST_INT8 SIUnit;
      ST_INT8 multiplier;
      } units;
    ST_UINT32 db;
    ST_UINT32 zeroDb;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } hhLim;
      struct
        {
        ST_FLOAT f;
        } hLim;
      struct
        {
        ST_FLOAT f;
        } ILim;
      struct
        {
        ST_FLOAT f;
        } IILim;
      struct
        {
        ST_FLOAT f;
        } min;
      struct
        {
        ST_FLOAT f;
        } max;
      } rangeC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } magSVC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } angSVC;
    ST_INT8 angRef;
    ST_UINT32 smpRate;
    } res;
  ST_INT8 angRef;
  } WYE_CF_TDEF;

typedef struct
  {
  struct
    {
    ST_CHAR d[256];
    } phsA;
  struct
    {
    ST_CHAR d[256];
    } phsB;
  struct
    {
    ST_CHAR d[256];
    } phsC;
  struct
    {
    ST_CHAR d[256];
    } neut;
  struct
    {
    ST_CHAR d[256];
    } net;
  struct
    {
    ST_CHAR d[256];
    } res;
  ST_CHAR d[256];
  } WYE_DC_TDEF;

typedef struct
  {
  struct
    {
    ST_CHAR cdcNs[256];
    ST_CHAR cdcName[256];
    ST_CHAR dataNs[256];
    } phsA;
  struct
    {
    ST_CHAR cdcNs[256];
    ST_CHAR cdcName[256];
    ST_CHAR dataNs[256];
    } phsB;
  struct
    {
    ST_CHAR cdcNs[256];
    ST_CHAR cdcName[256];
    ST_CHAR dataNs[256];
    } phsC;
  struct
    {
    ST_CHAR cdcNs[256];
    ST_CHAR cdcName[256];
    ST_CHAR dataNs[256];
    } neut;
  struct
    {
    ST_CHAR cdcNs[256];
    ST_CHAR cdcName[256];
    ST_CHAR dataNs[256];
    } net;
  struct
    {
    ST_CHAR cdcNs[256];
    ST_CHAR cdcName[256];
    ST_CHAR dataNs[256];
    } res;
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } WYE_EX_TDEF;

typedef struct
  {
  struct
    {
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } instCVal;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } cVal;
    ST_INT8 range;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } q;
    ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
    ST_UINT32 t_fraction;
    ST_UINT32 t_qflags;
    } phsAB;
  struct
    {
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } instCVal;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } cVal;
    ST_INT8 range;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } q;
    ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
    ST_UINT32 t_fraction;
    ST_UINT32 t_qflags;
    } phsBC;
  struct
    {
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } instCVal;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } cVal;
    ST_INT8 range;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } q;
    ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
    ST_UINT32 t_fraction;
    ST_UINT32 t_qflags;
    } phsCA;
  } DEL_MX_TDEF;

typedef struct
  {
  struct
    {
    ST_BOOLEAN subEna;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } subCVal;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } subQ;
    ST_CHAR subID[65];
    } phsAB;
  struct
    {
    ST_BOOLEAN subEna;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } subCVal;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } subQ;
    ST_CHAR subID[65];
    } phsBC;
  struct
    {
    ST_BOOLEAN subEna;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } subCVal;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } subQ;
    ST_CHAR subID[65];
    } phsCA;
  } DEL_SV_TDEF;

typedef struct
  {
  struct
    {
    struct
      {
      ST_INT8 SIUnit;
      ST_INT8 multiplier;
      } units;
    ST_UINT32 db;
    ST_UINT32 zeroDb;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } hhLim;
      struct
        {
        ST_FLOAT f;
        } hLim;
      struct
        {
        ST_FLOAT f;
        } ILim;
      struct
        {
        ST_FLOAT f;
        } IILim;
      struct
        {
        ST_FLOAT f;
        } min;
      struct
        {
        ST_FLOAT f;
        } max;
      } rangeC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } magSVC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } angSVC;
    ST_INT8 angRef;
    ST_UINT32 smpRate;
    } phsAB;
  struct
    {
    struct
      {
      ST_INT8 SIUnit;
      ST_INT8 multiplier;
      } units;
    ST_UINT32 db;
    ST_UINT32 zeroDb;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } hhLim;
      struct
        {
        ST_FLOAT f;
        } hLim;
      struct
        {
        ST_FLOAT f;
        } ILim;
      struct
        {
        ST_FLOAT f;
        } IILim;
      struct
        {
        ST_FLOAT f;
        } min;
      struct
        {
        ST_FLOAT f;
        } max;
      } rangeC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } magSVC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } angSVC;
    ST_INT8 angRef;
    ST_UINT32 smpRate;
    } phsBC;
  struct
    {
    struct
      {
      ST_INT8 SIUnit;
      ST_INT8 multiplier;
      } units;
    ST_UINT32 db;
    ST_UINT32 zeroDb;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } hhLim;
      struct
        {
        ST_FLOAT f;
        } hLim;
      struct
        {
        ST_FLOAT f;
        } ILim;
      struct
        {
        ST_FLOAT f;
        } IILim;
      struct
        {
        ST_FLOAT f;
        } min;
      struct
        {
        ST_FLOAT f;
        } max;
      } rangeC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } magSVC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } angSVC;
    ST_INT8 angRef;
    ST_UINT32 smpRate;
    } phsCA;
  ST_INT8 angRef;
  } DEL_CF_TDEF;

typedef struct
  {
  struct
    {
    ST_CHAR d[256];
    } phsAB;
  struct
    {
    ST_CHAR d[256];
    } phsBC;
  struct
    {
    ST_CHAR d[256];
    } phsCA;
  ST_CHAR d[256];
  } DEL_DC_TDEF;

typedef struct
  {
  struct
    {
    ST_CHAR cdcNs[256];
    ST_CHAR cdcName[256];
    ST_CHAR dataNs[256];
    } phsAB;
  struct
    {
    ST_CHAR cdcNs[256];
    ST_CHAR cdcName[256];
    ST_CHAR dataNs[256];
    } phsBC;
  struct
    {
    ST_CHAR cdcNs[256];
    ST_CHAR cdcName[256];
    ST_CHAR dataNs[256];
    } phsCA;
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } DEL_EX_TDEF;

typedef struct
  {
  struct
    {
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } instCVal;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } cVal;
    ST_INT8 range;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } q;
    ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
    ST_UINT32 t_fraction;
    ST_UINT32 t_qflags;
    } c1;
  struct
    {
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } instCVal;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } cVal;
    ST_INT8 range;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } q;
    ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
    ST_UINT32 t_fraction;
    ST_UINT32 t_qflags;
    } c2;
  struct
    {
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } instCVal;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } cVal;
    ST_INT8 range;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } q;
    ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
    ST_UINT32 t_fraction;
    ST_UINT32 t_qflags;
    } c3;
  ST_INT8 seqT;
  } SEQ_MX_TDEF;

typedef struct
  {
  struct
    {
    ST_BOOLEAN subEna;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } subCVal;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } subQ;
    ST_CHAR subID[65];
    } c1;
  struct
    {
    ST_BOOLEAN subEna;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } subCVal;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } subQ;
    ST_CHAR subID[65];
    } c2;
  struct
    {
    ST_BOOLEAN subEna;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } mag;
      struct
        {
        ST_FLOAT f;
        } ang;
      } subCVal;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[2];
      } subQ;
    ST_CHAR subID[65];
    } c3;
  } SEQ_SV_TDEF;

typedef struct
  {
  struct
    {
    struct
      {
      ST_INT8 SIUnit;
      ST_INT8 multiplier;
      } units;
    ST_UINT32 db;
    ST_UINT32 zeroDb;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } hhLim;
      struct
        {
        ST_FLOAT f;
        } hLim;
      struct
        {
        ST_FLOAT f;
        } ILim;
      struct
        {
        ST_FLOAT f;
        } IILim;
      struct
        {
        ST_FLOAT f;
        } min;
      struct
        {
        ST_FLOAT f;
        } max;
      } rangeC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } magSVC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } angSVC;
    ST_INT8 angRef;
    ST_UINT32 smpRate;
    } c1;
  struct
    {
    struct
      {
      ST_INT8 SIUnit;
      ST_INT8 multiplier;
      } units;
    ST_UINT32 db;
    ST_UINT32 zeroDb;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } hhLim;
      struct
        {
        ST_FLOAT f;
        } hLim;
      struct
        {
        ST_FLOAT f;
        } ILim;
      struct
        {
        ST_FLOAT f;
        } IILim;
      struct
        {
        ST_FLOAT f;
        } min;
      struct
        {
        ST_FLOAT f;
        } max;
      } rangeC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } magSVC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } angSVC;
    ST_INT8 angRef;
    ST_UINT32 smpRate;
    } c2;
  struct
    {
    struct
      {
      ST_INT8 SIUnit;
      ST_INT8 multiplier;
      } units;
    ST_UINT32 db;
    ST_UINT32 zeroDb;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } hhLim;
      struct
        {
        ST_FLOAT f;
        } hLim;
      struct
        {
        ST_FLOAT f;
        } ILim;
      struct
        {
        ST_FLOAT f;
        } IILim;
      struct
        {
        ST_FLOAT f;
        } min;
      struct
        {
        ST_FLOAT f;
        } max;
      } rangeC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } magSVC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } angSVC;
    ST_INT8 angRef;
    ST_UINT32 smpRate;
    } c3;
  ST_INT8 phsRef;
  } SEQ_CF_TDEF;

typedef struct
  {
  struct
    {
    struct
      {
      ST_INT8 SIUnit;
      ST_INT8 multiplier;
      } units;
    ST_UINT32 db;
    ST_UINT32 zeroDb;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } hhLim;
      struct
        {
        ST_FLOAT f;
        } hLim;
      struct
        {
        ST_FLOAT f;
        } ILim;
      struct
        {
        ST_FLOAT f;
        } IILim;
      struct
        {
        ST_FLOAT f;
        } min;
      struct
        {
        ST_FLOAT f;
        } max;
      } rangeC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } magSVC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } angSVC;
    ST_INT8 angRef;
    ST_UINT32 smpRate;
    } c1;
  struct
    {
    struct
      {
      ST_INT8 SIUnit;
      ST_INT8 multiplier;
      } units;
    ST_UINT32 db;
    ST_UINT32 zeroDb;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } hhLim;
      struct
        {
        ST_FLOAT f;
        } hLim;
      struct
        {
        ST_FLOAT f;
        } ILim;
      struct
        {
        ST_FLOAT f;
        } IILim;
      struct
        {
        ST_FLOAT f;
        } min;
      struct
        {
        ST_FLOAT f;
        } max;
      } rangeC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } magSVC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } angSVC;
    ST_INT8 angRef;
    ST_UINT32 smpRate;
    } c2;
  struct
    {
    struct
      {
      ST_INT8 SIUnit;
      ST_INT8 multiplier;
      } units;
    ST_UINT32 db;
    ST_UINT32 zeroDb;
    struct
      {
      struct
        {
        ST_FLOAT f;
        } hhLim;
      struct
        {
        ST_FLOAT f;
        } hLim;
      struct
        {
        ST_FLOAT f;
        } ILim;
      struct
        {
        ST_FLOAT f;
        } IILim;
      struct
        {
        ST_FLOAT f;
        } min;
      struct
        {
        ST_FLOAT f;
        } max;
      } rangeC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } magSVC;
    struct
      {
      ST_FLOAT scaleFactor;
      ST_FLOAT offset;
      } angSVC;
    ST_INT8 angRef;
    ST_UINT32 smpRate;
    } c3;
  ST_CHAR d[256];
  } SEQ_DC_TDEF;

typedef struct
  {
  struct
    {
    ST_CHAR cdcNs[256];
    ST_CHAR cdcName[256];
    ST_CHAR dataNs[256];
    } c1;
  struct
    {
    ST_CHAR cdcNs[256];
    ST_CHAR cdcName[256];
    ST_CHAR dataNs[256];
    } c2;
  struct
    {
    ST_CHAR cdcNs[256];
    ST_CHAR cdcName[256];
    ST_CHAR dataNs[256];
    } c3;
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } SEQ_EX_TDEF;

typedef struct
  {
  struct
    {
    ST_FLOAT f;
    } mag;
  struct
    {
    ST_FLOAT f;
    } ang;
  } VectorHMV_TDEF[16];

typedef struct
  {
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  struct
    {
    struct
      {
      ST_FLOAT f;
      } mag;
    struct
      {
      ST_FLOAT f;
      } ang;
    } har[16];
  } HMV_MX_TDEF;

typedef struct
  {
  ST_UINT16 numHar;
  ST_UINT16 numCycl;
  ST_UINT16 evalTm;
  struct
    {
    ST_INT8 SIUnit;
    ST_INT8 multiplier;
    } units;
  ST_UINT32 smpRate;
  ST_FLOAT frequency;
  ST_INT8 hvRef;
  ST_UINT16 rmsCyc;
  } HMV_CF_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } HMV_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } HMV_EX_TDEF;

typedef struct
  {
  struct
    {
    ST_FLOAT f;
    } mag;
  struct
    {
    ST_FLOAT f;
    } ang;
  } VectorHWYE_TDEF[16];

typedef struct
  {
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  struct
    {
    struct
      {
      ST_FLOAT f;
      } mag;
    struct
      {
      ST_FLOAT f;
      } ang;
    } phsAHar[16];
  struct
    {
    struct
      {
      ST_FLOAT f;
      } mag;
    struct
      {
      ST_FLOAT f;
      } ang;
    } phsBHar[16];
  struct
    {
    struct
      {
      ST_FLOAT f;
      } mag;
    struct
      {
      ST_FLOAT f;
      } ang;
    } phsCHar[16];
  struct
    {
    struct
      {
      ST_FLOAT f;
      } mag;
    struct
      {
      ST_FLOAT f;
      } ang;
    } neutHar[16];
  struct
    {
    struct
      {
      ST_FLOAT f;
      } mag;
    struct
      {
      ST_FLOAT f;
      } ang;
    } netHar[16];
  struct
    {
    struct
      {
      ST_FLOAT f;
      } mag;
    struct
      {
      ST_FLOAT f;
      } ang;
    } resHar[16];
  } HWYE_MX_TDEF;

typedef struct
  {
  ST_UINT16 numHar;
  ST_UINT16 numCycl;
  ST_UINT16 evalTm;
  struct
    {
    ST_INT8 SIUnit;
    ST_INT8 multiplier;
    } units;
  ST_INT8 angRef;
  ST_UINT32 smpRate;
  ST_FLOAT frequency;
  ST_INT8 hvRef;
  ST_UINT16 rmsCyc;
  } HWYE_CF_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } HWYE_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } HWYE_EX_TDEF;

typedef struct
  {
  struct
    {
    ST_FLOAT f;
    } mag;
  struct
    {
    ST_FLOAT f;
    } ang;
  } VectorHDEL_TDEF[16];

typedef struct
  {
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  struct
    {
    struct
      {
      ST_FLOAT f;
      } mag;
    struct
      {
      ST_FLOAT f;
      } ang;
    } phsABHar[16];
  struct
    {
    struct
      {
      ST_FLOAT f;
      } mag;
    struct
      {
      ST_FLOAT f;
      } ang;
    } phsBCHar[16];
  struct
    {
    struct
      {
      ST_FLOAT f;
      } mag;
    struct
      {
      ST_FLOAT f;
      } ang;
    } phsCAHar[16];
  } HDEL_MX_TDEF;

typedef struct
  {
  ST_UINT16 numHar;
  ST_UINT16 numCycl;
  ST_UINT16 evalTm;
  struct
    {
    ST_INT8 SIUnit;
    ST_INT8 multiplier;
    } units;
  ST_INT8 angRef;
  ST_UINT32 smpRate;
  ST_FLOAT frequency;
  ST_INT8 hvRef;
  ST_UINT16 rmsCyc;
  } HDEL_CF_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } HDEL_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } HDEL_EX_TDEF;

typedef ST_CHAR Select_TDEF[98];  /* Visible String */

typedef ST_BOOLEAN TestStatus_TDEF;

typedef ST_INT8 Cterm_TDEF;

typedef struct     /* BVstring */
  {
  ST_INT16 len_1;
  ST_UCHAR data_1[1];
  }  Check_TDEF;  /* Bitstring */

typedef ST_INT8 CtlModels_TDEF;

typedef ST_INT8 SboClasses_TDEF;

typedef struct
  {
  ST_BOOLEAN Value;
  ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 T_days;
  ST_BOOLEAN Test;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[1];
    } Check;
  } SPCSelectWithValue_TDEF;

typedef struct
  {
  ST_BOOLEAN Value;
  ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 T_days;
  ST_BOOLEAN Test;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[1];
    } Check;
  ST_INT8 Cterm;
  } SPCOperate_TDEF;

typedef struct
  {
  ST_BOOLEAN Value;
  ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 T_days;
  ST_BOOLEAN Test;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[1];
    } Check;
  ST_INT8 Cterm;
  } SPCTimeActivatedOperate_TDEF;

typedef struct
  {
  ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 T_days;
  ST_BOOLEAN Test;
  } Cancel_TDEF;

typedef struct
  {
  ST_BOOLEAN ctlVal;
  ST_CHAR SBO[98];
  struct
    {
    ST_BOOLEAN Value;
    ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
    ST_INT32 T_days;
    ST_BOOLEAN Test;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[1];
      } Check;
    } SBOw;
  struct
    {
    ST_BOOLEAN Value;
    ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
    ST_INT32 T_days;
    ST_BOOLEAN Test;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[1];
      } Check;
    ST_INT8 Cterm;
    } Oper;
  struct
    {
    ST_BOOLEAN Value;
    ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
    ST_INT32 T_days;
    ST_BOOLEAN Test;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[1];
      } Check;
    ST_INT8 Cterm;
    } OperTA;
  struct
    {
    ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
    ST_INT32 T_days;
    ST_BOOLEAN Test;
    } Cancel;
  ST_UINT32 operTm_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 operTm_fraction;
  ST_UINT32 operTm_qflags;
  struct
    {
    ST_INT8 orCat;
    struct     /* OVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[64];
      } orIdent;
    } origin;
  ST_UINT8 ctlNum;
  } SPC_CO_TDEF;

typedef struct
  {
  struct
    {
    ST_INT8 orCat;
    struct     /* OVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[64];
      } orIdent;
    } origin;
  ST_UINT8 ctlNum;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  ST_BOOLEAN stSeld;
  } SPC_ST_TDEF;

typedef struct
  {
  ST_BOOLEAN subEna;
  ST_BOOLEAN subVal;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } subQ;
  ST_CHAR subID[65];
  } SPC_SV_TDEF;

typedef struct
  {
  struct
    {
    ST_INT8 cmdQual;
    ST_UINT32 onDur;
    ST_UINT32 offDur;
    ST_UINT32 numPIs;
    } pulseConfig;
  ST_INT8 ctlModel;
  ST_UINT32 sboTimeout;
  ST_INT8 sboClass;
  } SPC_CF_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } SPC_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } SPC_EX_TDEF;

typedef struct
  {
  ST_BOOLEAN Value;
  ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 T_days;
  ST_BOOLEAN Test;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[1];
    } Check;
  } DPCSelectWithValue_TDEF;

typedef struct
  {
  ST_BOOLEAN Value;
  ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 T_days;
  ST_BOOLEAN Test;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[1];
    } Check;
  ST_INT8 Cterm;
  } DPCOperate_TDEF;

typedef struct
  {
  ST_BOOLEAN Value;
  ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 T_days;
  ST_BOOLEAN Test;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[1];
    } Check;
  ST_INT8 Cterm;
  } DPCTimeActivatedOperate_TDEF;

typedef struct
  {
  ST_BOOLEAN ctlVal;
  ST_CHAR SBO[98];
  struct
    {
    ST_BOOLEAN Value;
    ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
    ST_INT32 T_days;
    ST_BOOLEAN Test;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[1];
      } Check;
    } SBOw;
  struct
    {
    ST_BOOLEAN Value;
    ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
    ST_INT32 T_days;
    ST_BOOLEAN Test;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[1];
      } Check;
    ST_INT8 Cterm;
    } Oper;
  struct
    {
    ST_BOOLEAN Value;
    ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
    ST_INT32 T_days;
    ST_BOOLEAN Test;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[1];
      } Check;
    ST_INT8 Cterm;
    } OperTA;
  struct
    {
    ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
    ST_INT32 T_days;
    ST_BOOLEAN Test;
    } Cancel;
  ST_UINT32 operTm_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 operTm_fraction;
  ST_UINT32 operTm_qflags;
  struct
    {
    ST_INT8 orCat;
    struct     /* OVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[64];
      } orIdent;
    } origin;
  ST_UINT8 ctlNum;
  } DPC_CO_TDEF;

typedef struct
  {
  struct
    {
    ST_INT8 orCat;
    struct     /* OVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[64];
      } orIdent;
    } origin;
  ST_UINT8 ctlNum;
  ST_UCHAR stVal[1];
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  ST_BOOLEAN stSeld;
  } DPC_ST_TDEF;

typedef struct
  {
  ST_BOOLEAN subEna;
  ST_UCHAR subVal[1];
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } subQ;
  ST_CHAR subID[65];
  } DPC_SV_TDEF;

typedef struct
  {
  struct
    {
    ST_INT8 cmdQual;
    ST_UINT32 onDur;
    ST_UINT32 offDur;
    ST_UINT32 numPIs;
    } pulseConfig;
  ST_INT8 ctlModel;
  ST_UINT32 sboTimeout;
  ST_INT8 sboClass;
  } DPC_CF_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } DPC_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } DPC_EX_TDEF;

typedef struct
  {
  ST_INT32 Value;
  ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 T_days;
  ST_BOOLEAN Test;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[1];
    } Check;
  } INCSelectWithValue_TDEF;

typedef struct
  {
  ST_INT32 Value;
  ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 T_days;
  ST_BOOLEAN Test;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[1];
    } Check;
  ST_INT8 Cterm;
  } INCOperate_TDEF;

typedef struct
  {
  ST_INT32 Value;
  ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 T_days;
  ST_BOOLEAN Test;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[1];
    } Check;
  ST_INT8 Cterm;
  } INCTimeActivatedOperate_TDEF;

typedef struct
  {
  ST_INT32 ctlVal;
  ST_UINT32 operTm_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 operTm_fraction;
  ST_UINT32 operTm_qflags;
  struct
    {
    ST_INT8 orCat;
    struct     /* OVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[64];
      } orIdent;
    } origin;
  ST_UINT8 ctlNum;
  } INC_CO_TDEF;

typedef struct
  {
  struct
    {
    ST_INT8 orCat;
    struct     /* OVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[64];
      } orIdent;
    } origin;
  ST_UINT8 ctlNum;
  ST_INT32 stVal;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  ST_BOOLEAN stSeld;
  } INC_ST_TDEF;

typedef struct
  {
  ST_BOOLEAN subEna;
  ST_INT32 subVal;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } subQ;
  ST_CHAR subID[65];
  } INC_SV_TDEF;

typedef struct
  {
  ST_INT8 ctlModel;
  ST_UINT32 sboTimeout;
  ST_INT8 sboClass;
  ST_UINT32 minVal;
  ST_UINT32 maxVal;
  ST_UINT32 stepSize;
  } INC_CF_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } INC_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } INC_EX_TDEF;

typedef struct
  {
  ST_UCHAR Value[1];
  ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 T_days;
  ST_BOOLEAN Test;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[1];
    } Check;
  } BSCSelectWithValue_TDEF;

typedef struct
  {
  ST_UCHAR Value[1];
  ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 T_days;
  ST_BOOLEAN Test;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[1];
    } Check;
  ST_INT8 Cterm;
  } BSCOperate_TDEF;

typedef struct
  {
  ST_UCHAR Value[1];
  ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 T_days;
  ST_BOOLEAN Test;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[1];
    } Check;
  ST_INT8 Cterm;
  } BSCTimeActivatedOperate_TDEF;

typedef struct
  {
  ST_UCHAR ctlVal[1];
  ST_CHAR SBO[98];
  struct
    {
    ST_UCHAR Value[1];
    ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
    ST_INT32 T_days;
    ST_BOOLEAN Test;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[1];
      } Check;
    } SBOw;
  struct
    {
    ST_UCHAR Value[1];
    ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
    ST_INT32 T_days;
    ST_BOOLEAN Test;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[1];
      } Check;
    ST_INT8 Cterm;
    } Oper;
  struct
    {
    ST_UCHAR Value[1];
    ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
    ST_INT32 T_days;
    ST_BOOLEAN Test;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[1];
      } Check;
    ST_INT8 Cterm;
    } OperTA;
  struct
    {
    ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
    ST_INT32 T_days;
    ST_BOOLEAN Test;
    } Cancel;
  ST_UINT32 operTm_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 operTm_fraction;
  ST_UINT32 operTm_qflags;
  struct
    {
    ST_INT8 orCat;
    struct     /* OVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[64];
      } orIdent;
    } origin;
  ST_UINT8 ctlNum;
  } BSC_CO_TDEF;

typedef struct
  {
  struct
    {
    ST_INT8 orCat;
    struct     /* OVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[64];
      } orIdent;
    } origin;
  ST_UINT8 ctlNum;
  struct
    {
    ST_INT8 posVal;
    ST_BOOLEAN transInd;
    } valWTr;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  ST_BOOLEAN stSeld;
  } BSC_ST_TDEF;

typedef struct
  {
  ST_BOOLEAN subEna;
  struct
    {
    ST_INT8 posVal;
    ST_BOOLEAN transInd;
    } subVal;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } subQ;
  ST_CHAR subID[65];
  } BSC_SV_TDEF;

typedef struct
  {
  ST_BOOLEAN persistent;
  ST_INT8 ctlModel;
  ST_UINT32 sboTimeout;
  ST_INT8 sboClass;
  ST_INT8 minVal;
  ST_INT8 maxVal;
  ST_UINT8 stepSize;
  } BSC_CF_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } BSC_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } BSC_EX_TDEF;

typedef struct
  {
  ST_INT8 Value;
  ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 T_days;
  ST_BOOLEAN Test;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[1];
    } Check;
  } ISCSelectWithValue_TDEF;

typedef struct
  {
  ST_INT8 Value;
  ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 T_days;
  ST_BOOLEAN Test;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[1];
    } Check;
  ST_INT8 Cterm;
  } ISCOperate_TDEF;

typedef struct
  {
  ST_INT8 Value;
  ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 T_days;
  ST_BOOLEAN Test;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[1];
    } Check;
  ST_INT8 Cterm;
  } ISCTimeActivatedOperate_TDEF;

typedef struct
  {
  ST_INT8 ctlVal;
  ST_CHAR SBO[98];
  struct
    {
    ST_INT8 Value;
    ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
    ST_INT32 T_days;
    ST_BOOLEAN Test;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[1];
      } Check;
    } SBOw;
  struct
    {
    ST_INT8 Value;
    ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
    ST_INT32 T_days;
    ST_BOOLEAN Test;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[1];
      } Check;
    ST_INT8 Cterm;
    } Oper;
  struct
    {
    ST_INT8 Value;
    ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
    ST_INT32 T_days;
    ST_BOOLEAN Test;
    struct     /* BVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[1];
      } Check;
    ST_INT8 Cterm;
    } OperTA;
  struct
    {
    ST_INT32 T_ms;  /* Btime6 is two ST_INT32 */
    ST_INT32 T_days;
    ST_BOOLEAN Test;
    } Cancel;
  ST_UINT32 operTm_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 operTm_fraction;
  ST_UINT32 operTm_qflags;
  struct
    {
    ST_INT8 orCat;
    struct     /* OVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[64];
      } orIdent;
    } origin;
  ST_UINT8 ctlNum;
  } ISC_CO_TDEF;

typedef struct
  {
  struct
    {
    ST_INT8 orCat;
    struct     /* OVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[64];
      } orIdent;
    } origin;
  ST_UINT8 ctlNum;
  struct
    {
    ST_INT8 posVal;
    ST_BOOLEAN transInd;
    } valWTr;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  ST_BOOLEAN stSeld;
  } ISC_ST_TDEF;

typedef struct
  {
  ST_BOOLEAN subEna;
  struct
    {
    ST_INT8 posVal;
    ST_BOOLEAN transInd;
    } subVal;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } subQ;
  ST_CHAR subID[65];
  } ISC_SV_TDEF;

typedef struct
  {
  ST_INT8 ctlModel;
  ST_UINT32 sboTimeout;
  ST_INT8 sboClass;
  ST_INT8 minVal;
  ST_INT8 maxVal;
  ST_UINT8 stepSize;
  } ISC_CF_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } ISC_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } ISC_EX_TDEF;

typedef struct
  {
  struct
    {
    ST_FLOAT f;
    } setMag;
  struct
    {
    ST_INT8 orCat;
    struct     /* OVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[64];
      } orIdent;
    } origin;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } q;
  ST_UINT32 t_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 t_fraction;
  ST_UINT32 t_qflags;
  } APC_MX_TDEF;

typedef struct
  {
  struct
    {
    ST_FLOAT f;
    } setMag;
  struct
    {
    ST_INT8 orCat;
    struct     /* OVstring */
      {
      ST_INT16 len_1;
      ST_UCHAR data_1[64];
      } orIdent;
    } origin;
  ST_UINT32 operTm_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 operTm_fraction;
  ST_UINT32 operTm_qflags;
  } APC_SP_TDEF;

typedef struct
  {
  ST_INT8 ctlModel;
  struct
    {
    ST_INT8 SIUnit;
    ST_INT8 multiplier;
    } units;
  struct
    {
    ST_FLOAT scaleFactor;
    ST_FLOAT offset;
    } sVC;
  struct
    {
    ST_FLOAT f;
    } minVal;
  struct
    {
    ST_FLOAT f;
    } maxVal;
  struct
    {
    ST_FLOAT f;
    } stepSize;
  } APC_CF_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } APC_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } APC_EX_TDEF;

typedef struct
  {
  ST_BOOLEAN setVal;
  } SPG_SP_TDEF;

typedef struct
  {
  ST_BOOLEAN setVal;
  } SPG_SG_TDEF;

typedef struct
  {
  ST_BOOLEAN setVal;
  } SPG_SE_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } SPG_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } SPG_EX_TDEF;

typedef struct
  {
  ST_INT32 setVal;
  } ING_SP_TDEF;

typedef struct
  {
  ST_INT32 setVal;
  } ING_SG_TDEF;

typedef struct
  {
  ST_INT32 setVal;
  } ING_SE_TDEF;

typedef struct
  {
  ST_INT32 minVal;
  ST_INT32 maxVal;
  ST_UINT32 stepSize;
  } ING_CF_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } ING_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } ING_EX_TDEF;

typedef struct
  {
  struct
    {
    ST_FLOAT f;
    } setMag;
  } ASG_SP_TDEF;

typedef struct
  {
  struct
    {
    ST_FLOAT f;
    } setMag;
  } ASG_SG_TDEF;

typedef struct
  {
  struct
    {
    ST_FLOAT f;
    } setMag;
  } ASG_SE_TDEF;

typedef struct
  {
  struct
    {
    ST_INT8 SIUnit;
    ST_INT8 multiplier;
    } units;
  struct
    {
    ST_FLOAT f;
    } minVal;
  struct
    {
    ST_FLOAT f;
    } maxVal;
  struct
    {
    ST_FLOAT f;
    } stepSize;
  } ASG_CF_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } ASG_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } ASG_EX_TDEF;

typedef struct
  {
  ST_INT8 setCharact;
  ST_FLOAT setParA;
  ST_FLOAT setParB;
  ST_FLOAT setParC;
  ST_FLOAT setParD;
  ST_FLOAT setParE;
  ST_FLOAT setParF;
  } CURVE_SP_TDEF;

typedef struct
  {
  ST_INT8 setCharact;
  ST_FLOAT setParA;
  ST_FLOAT setParB;
  ST_FLOAT setParC;
  ST_FLOAT setParD;
  ST_FLOAT setParE;
  ST_FLOAT setParF;
  } CURVE_SG_TDEF;

typedef struct
  {
  ST_INT8 setCharact;
  ST_FLOAT setParA;
  ST_FLOAT setParB;
  ST_FLOAT setParC;
  ST_FLOAT setParD;
  ST_FLOAT setParE;
  ST_FLOAT setParF;
  } CURVE_SE_TDEF;

typedef struct
  {
  ST_CHAR d[256];
  } CURVE_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } CURVE_EX_TDEF;

typedef struct
  {
  ST_CHAR vendor[256];
  ST_CHAR hwRev[256];
  ST_CHAR swRev[256];
  ST_CHAR serNum[256];
  ST_CHAR model[256];
  ST_CHAR location[256];
  } DPL_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } DPL_EX_TDEF;

typedef struct
  {
  ST_CHAR vendor[256];
  ST_CHAR swRev[256];
  ST_CHAR d[256];
  ST_CHAR configRev[256];
  } LPL_DC_TDEF;

typedef struct
  {
  ST_CHAR ldNs[256];
  ST_CHAR lnNs[256];
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } LPL_EX_TDEF;

typedef struct
  {
  ST_FLOAT xVal;
  ST_FLOAT yVal;
  } PointCSD_TDEF[16];

typedef struct
  {
  struct
    {
    ST_INT8 SIUnit;
    ST_INT8 multiplier;
    } xUnit;
  ST_CHAR xD[256];
  struct
    {
    ST_INT8 SIUnit;
    ST_INT8 multiplier;
    } yUnit;
  ST_CHAR yD[256];
  ST_UINT16 numPts;
  struct
    {
    ST_FLOAT xVal;
    ST_FLOAT yVal;
    } crvPts[16];
  ST_CHAR d[256];
  } CSD_DC_TDEF;

typedef struct
  {
  ST_CHAR cdcNs[256];
  ST_CHAR cdcName[256];
  ST_CHAR dataNs[256];
  } CSD_EX_TDEF;

typedef struct
  {
  ST_BOOLEAN RptEna;
  ST_CHAR RptID[33];
  ST_CHAR DatSet[66];
  ST_UINT32 ConfRev;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } OptFlds;
  ST_UINT32 BufTim;
  ST_UINT8 SqNum;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[1];
    } TrgOps;
  ST_UINT32 IntgPd;
  ST_BOOLEAN GI;
  ST_BOOLEAN PurgeBuf;
  ST_UCHAR EntryID[8];
  ST_INT32 TimeofEntry_ms;  /* Btime6 is two ST_INT32 */
  ST_INT32 TimeofEntry_days;
  } IEC_BRCB_TDEF;

typedef struct
  {
  ST_BOOLEAN RptEna;
  ST_CHAR RptID[33];
  ST_BOOLEAN Resv;
  ST_CHAR DatSet[66];
  ST_UINT32 ConfRev;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } OptFlds;
  ST_UINT32 BufTim;
  ST_UINT8 SqNum;
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[1];
    } TrgOps;
  ST_UINT32 IntgPd;
  ST_BOOLEAN GI;
  } IEC_URCB_TDEF;

typedef struct
  {
  ST_UINT8 NumOfSG;
  ST_UINT8 ActSG;
  ST_UINT8 EditSG;
  ST_BOOLEAN CnfEdit;
  ST_UINT32 LActTim_secs;  /* UTC Time is struct of three ST_UINT32 */
  ST_UINT32 LActTim_fraction;
  ST_UINT32 LActTim_qflags;
  } SGCB_TDEF;

/************************************************************************/
#endif /* if defined (USE_MMS_TYPEDEFS) */
/************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* #ifndef FOUNDRY_OUTPUT_HEADER_INCLUDED */

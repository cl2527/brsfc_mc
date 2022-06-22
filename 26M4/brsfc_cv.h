#ifndef _brsfc_CV_H_
#define _brsfc_CV_H_
#define HOST
#include "GEtypes.h" 
#include "sys/types.h" 
#include "entrypttab.h" 
#include "stddef_ep.h" 
#include "pulsegen.h" 
#include "ca_filt.h" 
#ifdef _INCLUDE_MYTYPES_
#include "mytypes.h" 
#endif
typedef struct
{
  float oprloc;
  float opphasoff;
  float optloc;
  float oprloc_shift;
  float opphasoff_shift;
  float optloc_shift;
  float opfov_freq_scale;
  float opfov_phase_scale;
  float opslthick_scale;
  float oprot[9];
} SCAN_INFO;
typedef struct
{
  float oppsctloc;
  float oppscrloc;
  float oppscphasoff;
  float oppscrot[9];
  int oppsclenx;
  int oppscleny;
  int oppsclenz;
} PSC_INFO;
typedef struct
{
  short slloc;
  short slpass;
  short sltime;
} DATA_ACQ_ORDER;
typedef struct
{
  float rsptloc;
  float rsprloc;
  float rspphasoff;
  int slloc;
} RSP_INFO;
enum
{



  COIL_CONNECTOR_A,
  COIL_CONNECTOR_P1,
  COIL_CONNECTOR_P2,
  COIL_CONNECTOR_P3,
  COIL_CONNECTOR_P4,
  COIL_CONNECTOR_P5,


  NUM_COIL_CONNECTORS,
  NUM_COIL_CONNECTORS_PADDED = 8,



  COIL_CONNECTOR_PORT0 = COIL_CONNECTOR_A,
  COIL_CONNECTOR_PORT1 = COIL_CONNECTOR_P1,
  COIL_CONNECTOR_PORT2 = COIL_CONNECTOR_P2,
  COIL_CONNECTOR_PORT3 = COIL_CONNECTOR_P3,
  COIL_CONNECTOR_PORT4 = COIL_CONNECTOR_P4,
  COIL_CONNECTOR_PORT5 = COIL_CONNECTOR_P5,


  COIL_CONNECTOR_MCRV = NUM_COIL_CONNECTORS,


  NUM_COIL_CONNECTORS_INC_MCRV = NUM_COIL_CONNECTORS + 1
};
enum
{
  COIL_CONNECTOR_MNS_LEGACY_TOP,
  COIL_CONNECTOR_C_LEGACY_BOTTOM,
  COIL_CONNECTOR_PORT_A,
  COIL_CONNECTOR_PORT_B,


  NUM_COIL_CONNECTORS_PRE_HDV
};
enum
{
  COIL_STATE_UNKNOWN,
  COIL_STATE_DISCONNECTED,
  COIL_STATE_CONNECTED,
  COIL_STATE_ID,
  COIL_STATE_COMPLETE,


  NUM_COIL_STATES
};
enum
{
  COIL_INVALID,
  COIL_VALID,


  NUM_COIL_VALID_VALUES
};
enum
{
  COIL_TYPE_TRANSMIT,
  COIL_TYPE_RECEIVE,


  NUM_COIL_TYPE_VALUES
};
enum
{
  BODY_TRANSMIT_DISABLE,
  BODY_TRANSMIT_ENABLE,


  NUM_BODY_TRANSMIT_ENABLE_VALUES
};
enum
{
  TRANSMIT_SELECT_NONE,
  TRANSMIT_SELECT_A,
  TRANSMIT_SELECT_P1,
  TRANSMIT_SELECT_LEGACY_HEAD,
  TRANSMIT_SELECT_LEGACY_MC,
  TRANSMIT_SELECT_1MNS,


  NUM_TRANSMIT_SELECTS
};
enum
{
  MNS_CONVERTER_SELECT_NONE = 0x00000000,
  MNS_CONVERTER_SELECT_A = 0x00000001,
  MNS_CONVERTER_SELECT_MASK = 0x00000001,
};
enum
{
  COIL_ID_TYPE_REQUIRED = 0,
  COIL_ID_TYPE_PRESENCE_ONLY = 1,
  COIL_ID_TYPE_NOT_REQUIRED = 2,


  NUM_COIL_ID_TYPES
};
enum
{






  COIL_INT_FAULT_CHECK_UNSUPPORTED,


  COIL_INT_FAULT_CHECK_SUPPORTED,


  NUM_COIL_INT_FAULT_CHECK_TYPES
};
enum
{
  TX_POS_BODY,
  TX_POS_HEAD,
  TX_POS_EXTREMITY,
  TX_POS_XIPHOID,
  TX_POS_STERN,
  TX_POS_BREAST,
  TX_POS_HEAD_XIPHOID,
  TX_POS_HEAD_BODY,
  TX_POS_NECK,
  NUM_TX_POSITIONS
};
typedef struct CTMEntry
{
  n8 receiverID;
  n8 receiverChannel;
  n16 entryMask;
} CTMEntryType;
typedef struct QuadVolWeight
{
  n8 receiverID;
  n8 receiverChannel;
  n8 pad[2];
  f32 recWeight;
  f32 recPhaseDeg;
} QuadVolWeightType;
typedef struct CTTEntry
{



  s8 logicalCoilName[128];




  s8 clinicalCoilName[32];




  n32 configUID;




  s32 coilConnector;




  n32 isActiveScanConfig;




  CTMEntryType channelTranslationMap[256];




  QuadVolWeightType quadVolReceiveWeights[16];




  n32 numChannels;

} ChannelTransTableEntryType;
enum
{
  NORMAL_COIL,
  F000_COIL,
  FG00_COIL,
  P000_COIL,
  PG00_COIL,
  R000_COIL,
  SERV_COIL
};
typedef struct _INSTALL_COIL_INFO_
{
  char coilCode[(32 + 8)];
  int isInCoilDatabase;
} INSTALL_COIL_INFO;
typedef struct _INSTALL_COIL_CONNECTOR_INFO_
{
  int connector;
  int needsInstall;
  INSTALL_COIL_INFO installCoilInfo[4];
} INSTALL_COIL_CONNECTOR_INFO;
typedef struct coil_config_params
{
  char coilName[16];
  char GEcoilName[24];
  short pureCorrection;
  int maxNumOfReceivers;
  int coilType;
  int txCoilType;
  int fastTGmode;
  int fastTGstartTA;
  int fastTGstartRG;
  int nuclide;
  int tRPAvolumeRecEnable;
  int pureCompatible;
  int aps1StartTA;
  int cflStartTA;
  int cfhSensitiveAnatomy;
  float pureLambda;
  float pureTuningFactorSurface;
  float pureTuningFactorBody;
  float cableLoss;
  float coilLoss;
  float reconScale;
  float autoshimFOV;
  float coilWeights[4][256];
  ChannelTransTableEntryType cttEntry[4];

} COIL_CONFIG_PARAM_TYPE;
typedef struct application_config_param_type
{
  int aps1StartTA;
  int cflStartTA;
  int AScfPatLocChangeRL;
  int AScfPatLocChangeAP;
  int AScfPatLocChangeSI;
  int TGpatLocChangeRL;
  int TGpatLocChangeAP;
  int TGpatLocChangeSI;
  int autoshimFOV;
  int fastTGstartTA;
  int fastTGstartRG;
  int fastTGmode;
  int cfhSensitiveAnatomy;
  int aps1Mod;
  int aps1Plane;
  int pureCompatible;
  int maxFOV;
  int assetThresh;
  int scic_a_used;
  int scic_s_used;
  int scic_c_used;
  float aps1ModFOV;
  float aps1ModPStloc;
  float aps1ModPSrloc;
  float opthickPSMod;
  float pureScale;
  float pureCorrectionThreshold;
  float pureLambda;
  float pureTuningFactorSurface;
  float pureTuningFactorBody;
  float scic_a[7];
  float scic_s[7];
  float scic_c[7];
  int assetSupported;
  float assetValues[3];
  int arcSupported;
  float arcValues[3];
  int sagCalEnabled;
} APPLICATION_CONFIG_PARAM_TYPE;
typedef struct application_config_hdr
{
  int error;
  char clinicalName[32];
  APPLICATION_CONFIG_PARAM_TYPE appConfig;
} APPLICATION_CONFIG_HDR;
typedef struct
{
  s8 coilName[32];
  s32 txIndexPri;


  s32 txIndexSec;


  n32 rxCoilType;

  n32 hubIndex;
  n32 rxNucleus;
  n32 aps1Mod;
  n32 aps1ModPlane;
  n32 coilSepDir;
  s32 assetCalThreshold;
  f32 aps1ModFov;
  f32 aps1ModSlThick;
  f32 aps1ModPsTloc;
  f32 aps1ModPsRloc;
  f32 autoshimFov;
  f32 assetCalMaxFov;
  f32 maxB1Rms;

  n32 pureCompatible;
  f32 pureLambda;
  f32 pureTuningFactorSurface;

  f32 pureTuningFactorBody;

} COIL_INFO;
typedef struct
{
  s32 coilAtten;
  n32 txCoilType;

  n32 txPosition;



  n32 txNucleus;
  n32 txAmp;

  f32 maxB1Peak;

  f32 maxB1Squared;

  f32 cableLoss;
  f32 coilLoss;
  f32 reflCoeffSquared[10];


  f32 reflCoeffMassOffset;
  f32 reflCoeffCurveType;
  f32 exposedMass[8];


  f32 lowSarExposedMass[8];


  f32 jstd[12];

  f32 meanJstd[12];


  f32 separationStdev;

} TX_COIL_INFO;
typedef struct _psd_coil_info_
{
  COIL_INFO imgRcvCoilInfo[10];
  COIL_INFO volRcvCoilInfo[10];
  TX_COIL_INFO txCoilInfo[5];
  int numCoils;

} PSD_COIL_INFO;
typedef struct
{
  int ptype;
  int *attack;
  int *decay;
  int *pw;

  float *amps;
  float *amp;

  float *ampd;

  float *ampe;

  char *gradfile;
  int num;
  float scale;

  int *time;
  int tdelta;

  float powscale;







  float power;
  float powpos;
  float powneg;
  float powabs;
  float amptran;
  int pwm;
  int bridge;


  float intabspwmcurr;


} GRAD_PULSE;
typedef struct
{
  int *pw;
  float *amp;
  float abswidth;
  float effwidth;
  float area;
  float dtycyc;
  float maxpw;
  int num;
  float max_b1;
  float max_int_b1_sq;
  float max_rms_b1;
  float nom_fa;
  float *act_fa;
  float nom_pw;
  float nom_bw;
  unsigned int activity;
  unsigned char reference;
  int isodelay;

  float scale;
  int *res;
  int extgradfile;
  int *exciter;
} RF_PULSE;
typedef struct
{
  int change;
  int newres;
} RF_PULSE_INFO;
typedef struct
{
  int xfull;
  int yfull;
  int zfull;
  float xfs;
  float yfs;
  float zfs;
  int xrt;
  int yrt;
  int zrt;
  int xft;
  int yft;
  int zft;
  float xcc;
  float ycc;
  float zcc;
  float xbeta;
  float ybeta;
  float zbeta;
  float xirms;
  float yirms;
  float zirms;
  float xipeak;
  float yipeak;
  float zipeak;
  float xamptran;
  float yamptran;
  float zamptran;
  float xiavrgabs;
  float yiavrgabs;
  float ziavrgabs;
  float xirmspos;
  float yirmspos;
  float zirmspos;
  float xirmsneg;
  float yirmsneg;
  float zirmsneg;
  float xpwmdc;
  float ypwmdc;
  float zpwmdc;
} PHYS_GRAD;
typedef struct
{
  int x;
  int xy;
  int xz;
  int xyz;
} t_xact;
typedef struct
{
  int y;
  int xy;
  int yz;
  int xyz;
} t_yact;
typedef struct
{
  int z;
  int xz;
  int yz;
  int xyz;
} t_zact;
typedef struct
{
  int xrt;
  int yrt;
  int zrt;
  int xft;
  int yft;
  int zft;
} ramp_t;
typedef struct
{
  int xrt;
  int yrt;
  int zrt;
  int xft;
  int yft;
  int zft;
  ramp_t opt;
  t_xact xrta;
  t_yact yrta;
  t_zact zrta;
  t_xact xfta;
  t_yact yfta;
  t_zact zfta;
  float xbeta;
  float ybeta;
  float zbeta;
  float tx_xyz;
  float ty_xyz;
  float tz_xyz;
  float tx_xy;
  float tx_xz;
  float ty_xy;
  float ty_yz;
  float tz_xz;
  float tz_yz;
  float tx;
  float ty;
  float tz;
  float xfs;
  float yfs;
  float zfs;
  float xirms;
  float yirms;
  float zirms;
  float xipeak;
  float yipeak;
  float zipeak;
  float xamptran;
  float yamptran;
  float zamptran;
  float xiavrgabs;
  float yiavrgabs;
  float ziavrgabs;
  float xirmspos;
  float yirmspos;
  float zirmspos;
  float xirmsneg;
  float yirmsneg;
  float zirmsneg;
  float xpwmdc;
  float ypwmdc;
  float zpwmdc;
} LOG_GRAD;
typedef struct
{
  float xfs;
  float yfs;
  float zfs;
  int xrt;
  int yrt;
  int zrt;
  float xbeta;
  float ybeta;
  float zbeta;
  float xfov;
  float yfov;
  int xres;
  int yres;
  int ileaves;
  float xdis;
  float ydis;
  float zdis;
  float tsp;
  int osamps;
  float fbhw;

  int vvp;
  float pnsf;
  float taratio;
  float zarea;
} OPT_GRAD_INPUT;
typedef struct
{
  float *agxw;
  int *pwgxw;
  int *pwgxwa;
  float *agyb;
  int *pwgyb;
  int *pwgyba;
  float *agzb;
  int *pwgzb;
  int *pwgzba;
  int *frsize;
  int *pwsamp;
  int *pwxgap;
} OPT_GRAD_PARAMS;
struct __GEtimespec
{
  s32 tv_sec;
  s32 tv_nsec;
};
typedef struct __GEtimespec GEtimespec;







typedef unsigned short int dbkey_exam_type;
typedef short int dbkey_magic_type;
typedef short int dbkey_series_type;
typedef int dbkey_image_type;

typedef struct
{
  char su_id[4];
  dbkey_magic_type mg_no;
  dbkey_exam_type ex_no;
  dbkey_series_type se_no;
  dbkey_image_type im_no;
} DbKey;
typedef char OP_NMRID_TYPE[12];

typedef struct
{

  n16 rev;
  n16 length;

  OP_NMRID_TYPE req_nmrid;
  OP_NMRID_TYPE resp_nmrid;
  n16 opcode;
  n16 packet_type;
  n16 seq_num;
  n32 status;

} OP_HDR1_TYPE;
typedef struct _OP_HDR_TYPE
{

  s8 rev;
  s8 endian;
  n16 length;

  OP_NMRID_TYPE req_nmrid;
  OP_NMRID_TYPE resp_nmrid;
  n16 opcode;
  n16 packet_type;
  n16 seq_num;
  n16 pad;
  n32 status;

} OP_HDR_TYPE;
typedef struct _OP_RECN_READY_TYPE
{
  DbKey dbkey;
  s32 seq_number;
  GEtimespec time_stamp;
  s32 run_no;
  s32 prep_flag;
  n32 patient_checksum;
} OP_RECN_READY_TYPE;
typedef struct _OP_RECN_READY_PACK_TYPE
{
  OP_HDR_TYPE hdr;
  OP_RECN_READY_TYPE req;
} OP_RECN_READY_PACK_TYPE;
typedef struct
{
  s32 somes32bitint;
  n16 somen16bitint;
  char somechar;
  unsigned long someulong;
  float somefloat;
} OP_RECN_FOO_TYPE;
typedef struct
{
  OP_HDR_TYPE hdr;
  OP_RECN_FOO_TYPE req;
} OP_RECN_FOO_PACK_TYPE;
typedef struct _OP_RECN_START_TYPE
{
  s32 seq_number;
  GEtimespec time_stamp;
} OP_RECN_START_TYPE;
typedef struct _OP_RECN_START_PACK_TYPE
{
  OP_HDR_TYPE hdr;
  OP_RECN_START_TYPE req;
} OP_RECN_START_PACK_TYPE;
typedef struct
{
  s32 seq_number;
  s32 status;
  s32 aborted_pass_num;

} OP_RECN_SCAN_STOPPED_TYPE;
typedef struct
{
  OP_HDR_TYPE hdr;
  OP_RECN_SCAN_STOPPED_TYPE req;
} OP_RECN_SCAN_STOPPED_PACK_TYPE;
typedef struct
{
  DbKey dbkey;
  s32 seq_number;
  char scan_initiator[12];
} OP_RECN_STOP_TYPE;
typedef struct
{
  OP_HDR_TYPE hdr;
  OP_RECN_STOP_TYPE req;
} OP_RECN_STOP_PACK_TYPE;
typedef struct
{
  s32 seq_number;
} OP_RECN_IM_ALLOC_TYPE;
typedef struct
{
  OP_HDR_TYPE hdr;
  OP_RECN_IM_ALLOC_TYPE req;
} OP_RECN_IM_ALLOC_PACK_TYPE;
typedef struct
{
  s32 seq_number;
} OP_RECN_SCAN_STARTED_TYPE;
typedef struct
{
  OP_HDR_TYPE hdr;
  OP_RECN_SCAN_STARTED_TYPE req;
} OP_RECN_SCAN_STARTED_PACK_TYPE;
typedef struct
{
  s32 table_size;
  s32 block_size;
  s32 first_entry_index;
  s32 table[256];
} OP_VIEWTABLE_UPDATE_TYPE;
typedef struct
{
  OP_HDR_TYPE hdr;
  OP_VIEWTABLE_UPDATE_TYPE pkt;
} OP_VIEWTABLE_UPDATE_PACK_TYPE;
typedef struct
{
  n64 mrhdr;
  n64 pixelhdr;
  n64 pixeldata;
  n64 raw_offset;
  n64 raw_receivers;
  n64 pixeldata3;
} MROR_ADDR_BLOCK;
typedef struct
{
  OP_HDR_TYPE hdr;
  MROR_ADDR_BLOCK mrab;
} MROR_ADDR_BLOCK_PKT;
typedef struct
{
  n32 recon_ts;
} MROR_RETRIEVAL_DONE_TYPE;
typedef struct
{
  OP_HDR_TYPE hdr;
  MROR_RETRIEVAL_DONE_TYPE retrieve_done;

} __attribute__ ((__may_alias__)) MROR_ADDR_BLOCK_PACK_TYPE;
typedef struct
{
  s32 exam_number;
  s32 calib_flag;
} SCAN_CALIB_INFO_TYPE;
typedef struct
{
  OP_HDR_TYPE hdr;
  SCAN_CALIB_INFO_TYPE info;
} SCAN_CALIB_INFO_PACK_TYPE;
typedef struct _OP_RECN_SIZE_CHECK_TYPE
{
  n64 total_bam_size;
  n64 total_disk_size;
} OP_RECN_SIZE_CHECK_TYPE;
typedef struct _OP_RECN_SIZE_CHECK_PACK_TYPE
{
  OP_HDR_TYPE hdr;
  OP_RECN_SIZE_CHECK_TYPE req;
} OP_RECN_SIZE_CHECK_PACK_TYPE;
typedef struct
{
  s32 exam_number;
} EXAM_SCAN_DONE_TYPE;
typedef struct
{
  OP_HDR_TYPE hdr;
  EXAM_SCAN_DONE_TYPE info;
} EXAM_SCAN_DONE_PACK_TYPE;
typedef struct _POSITION_DETECTION_DONE_TYPE
{
  n32 object_detected;
  f32 object_si_position_mm;
  f32 right_most_voxel_mm;
  f32 anterior_most_voxel_mm;
  f32 superior_most_voxel_mm;
  n32 checksum;
} POSITION_DETECTION_DONE_TYPE;
typedef struct _POSITION_DETECTION_DONE_PACK_TYPE
{
  OP_HDR_TYPE hdr;
  POSITION_DETECTION_DONE_TYPE info;
} POSITION_DETECTION_DONE_PACK_TYPE;
typedef enum CARDIAC_GATE_TYPE
{
  CARDIAC_GATE_TYPE_MIN = 0,
  CARDIAC_GATE_TYPE_NONE = 0,
  CARDIAC_GATE_TYPE_ECG = 1,
  CARDIAC_GATE_TYPE_PG = 2,
  CARDIAC_GATE_TYPE_MAX = 2
} CARDIAC_GATE_TYPE_E;
typedef char EXTERN_FILENAME[80];
typedef char *EXTERN_FILENAME2;
typedef struct
{
  int ysign;
  int yoffs;
} PHASE_OFF;
typedef struct
{
  float rsppsctloc;
  float rsppscrloc;
  float rsppscphasoff;
  long rsppscrot[10];
  int rsppsclenx;
  int rsppscleny;
  int rsppsclenz;
} RSP_PSC_INFO;
typedef struct
{
  float opgirthick;
  float opgirtloc;
  float opgirrot[9];
} GIR_INFO;
typedef struct zy_exp
{
  n16 view;
  n16 slice;
  n16 echo;
  n16 heat;
  n16 flags;
} ZY_EXPORT;
typedef enum VIEWORDER_MODE
{
  VIEWSHARING_OFF = 0,
  DISCO_ORDER = 1
} VIEWORDER_MODE_E;
typedef enum REG_VIEWORDER_MODE
{
  REGULAR = 0,
  INTERLEAVE = 1
} REG_VIEWORDER_MODE_E;
typedef enum REGION_ORDER_MODE
{
  CENTER_REGION_FIRST = 0,
  OUTER_REGION_FIRST = 1
} REGION_ORDER_MODE_E;
typedef struct cal_param
{
  INT shape;
  INT phaseCutoffUpper;
  INT phaseCutoffLower;
  INT sliceCutoffUpper;
  INT sliceCutoffLower;

  FLOAT phaseRadius;
  FLOAT sliceRadius;
  FLOAT phaseOrigin;
  FLOAT sliceOrigin;
} CAL_PARAM;
typedef struct param4d
{
  VIEWORDER_MODE_E vieworder_mode;
  float aregion_fraction;
  int num_outer_regions;
  int num_sub_regions;
  int smoothec;
  int views_per_region[32];
  float num_transition_fraction;
  int reverse_first_region_flag;
  int regViewOrderMode;
  int nr_of_segA;
} PARAM4D;
typedef struct spiral_view
{
  short phase;
  short slice;
  short leaf;
} SPIRAL_VIEW;
typedef struct slaboff
{
  int zsign;
  int zoffs;
} SLAB_OFF;
typedef enum CYLR_RF_TYPE
{
  CYLR_CONSTANT_DENSITY = 0,
  CYLR_VARIABLE_DENSITY_SR75,
  CYLR_VARIABLE_DENSITY_SR107,
  CYLR_VARIABLE_DENSITY_SR118,
  CYLR_VARIABLE_DENSITY_SR145,
  CYLR_VARIABLE_DENSITY_SR190,
  NUM_CYLR_RF_TYPE
} CYLR_RF_TYPE_E;
typedef enum e_ktsamp
{
  KT_MODE = 0,
  VDKT_MODE = 1,
  ARC_MODE = 2,
} t_ktsamp;
typedef struct
{
  short len;
  short *ky;
  short *kz;
  float *kr;
  short *ki;
} ViewTable_kyz;
typedef enum e_cgatetype
{

  TYPECG = 1,
  TYPPG
} t_cgatetype;
typedef enum e_fcineim
{
  LINEAR = 1,
  NNEIGHBOR
} t_fcineim;
typedef enum e_fcinent
{
  SYSDIAS = 1,
  UNIFORM
} t_fcinent;
#define PSD_NAME_LEN 32
#define HOST_NAME_LEN 32
#define TIME_STAMP_LEN 32
#define _BRSFC_CV_ASSET_MAX_SLQUANT
#define _BRSFC_CV_B1CAL_MODE
#define _BRSFC_CV_CFHXRES
#define _BRSFC_CV_CFLXRES
#define _BRSFC_CV_CHEMSATPULSE
#define _BRSFC_CV_COMPLETEECHOLOOP_FLAG
#define _BRSFC_CV_COMPOSITERMS_METHOD
#define _BRSFC_CV_DATA_ACQ_ORDER_ENTRIES
#define _BRSFC_CV_DD_CHANNELS
#define _BRSFC_CV_DD_DEBUG
#define _BRSFC_CV_DD_DELAY
#define _BRSFC_CV_DD_NCH
#define _BRSFC_CV_FSVAR
#define _BRSFC_CV_FTGACQ1
#define _BRSFC_CV_FTGACQ2
#define _BRSFC_CV_FTGAU
#define _BRSFC_CV_FTGECHO1BW
#define _BRSFC_CV_FTGFOV
#define _BRSFC_CV_FTGOPSLTHICKZ1
#define _BRSFC_CV_FTGOPSLTHICKZ2
#define _BRSFC_CV_FTGOPSLTHICKZ3
#define _BRSFC_CV_FTGSLTHK
#define _BRSFC_CV_FTGTAU1
#define _BRSFC_CV_FTGTAU2
#define _BRSFC_CV_FTGTECHO
#define _BRSFC_CV_FTGTESTPULSE
#define _BRSFC_CV_FTGXMTADD
#define _BRSFC_CV_FTGXRES
#define _BRSFC_CV_GAM
#define _BRSFC_CV_IRINCFH
#define _BRSFC_CV_PSAMP_DERATE_FACTOR
#define _BRSFC_CV_PSASAMP_DERATE_FACTOR
#define _BRSFC_CV_PSASSR_DERATE_FACTOR
#define _BRSFC_CV_PSCFH_SHIMVOL_DEBUG
#define _BRSFC_CV_PSCS_SAT
#define _BRSFC_CV_PSDEBUGSTATE
#define _BRSFC_CV_PSFIELD_STRENGTH
#define _BRSFC_CV_PSIR
#define _BRSFC_CV_PSMT
#define _BRSFC_CV_PSOFF90
#define _BRSFC_CV_PSPHASOFF
#define _BRSFC_CV_PSPHASOFF_MOD
#define _BRSFC_CV_PSRLOC
#define _BRSFC_CV_PSRLOC_MOD
#define _BRSFC_CV_PSSLICE_IND
#define _BRSFC_CV_PSSLICE_NUM
#define _BRSFC_CV_PSSR_DERATE_FACTOR
#define _BRSFC_CV_PSTEST_SLAB
#define _BRSFC_CV_PSTLOC
#define _BRSFC_CV_PSTLOC_MOD
#define _BRSFC_CV_PSTRIGGER
#define _BRSFC_CV_POSGZSSFHCOMB
#define _BRSFC_CV_POSRFS5FPH
#define _BRSFC_CV_POSRFSSF
#define _BRSFC_CV_POSRFSSFH
#define _BRSFC_CV_RF
#define _BRSFC_CV_SAR_BODYNV_WEIGHT_LIM
#define _BRSFC_CV_SATRELAXERS
#define _BRSFC_CV_T1F
#define _BRSFC_CV_T2F
#define _BRSFC_CV_TG_RECORD
#define _BRSFC_CV_TGLIMIT
#define _BRSFC_CV_TGOPSLTHICK
#define _BRSFC_CV_TGOPSLTHICKX
#define _BRSFC_CV_TGOPSLTHICKY
#define _BRSFC_CV_TGSPF
#define _BRSFC_CV_TR_PASS
#define _BRSFC_CV_TR_PASS3D
#define _BRSFC_CV_TR_SLOP
#define _BRSFC_CV_XTGACQ1
#define _BRSFC_CV_XTGECHO1BW
#define _BRSFC_CV_XTGFOV
#define _BRSFC_CV_XTGTAU1
#define _BRSFC_CV_XTGXRES
#define _BRSFC_CV__FIRSTCV
#define _BRSFC_CV__LASTCV
#define _BRSFC_CV__LASTTGTEX
#define _BRSFC_CV_ATEOPT_FLAG
#define _BRSFC_CV_ATROPT_FLAG
#define _BRSFC_CV_A_BASE
#define _BRSFC_CV_A_BASE2
#define _BRSFC_CV_A_BASE_MAX
#define _BRSFC_CV_A_BASE_PROJ_DEPHASER
#define _BRSFC_CV_A_COMB
#define _BRSFC_CV_A_COMB2
#define _BRSFC_CV_A_DELTA
#define _BRSFC_CV_A_DELTA2
#define _BRSFC_CV_A_END
#define _BRSFC_CV_A_END2
#define _BRSFC_CV_A_GK
#define _BRSFC_CV_A_GX1
#define _BRSFC_CV_A_GX1_FRAC
#define _BRSFC_CV_A_GX1_FULL
#define _BRSFC_CV_A_GX1A
#define _BRSFC_CV_A_GX1AS
#define _BRSFC_CV_A_GX1B
#define _BRSFC_CV_A_GX1BFTG
#define _BRSFC_CV_A_GX1BXTG
#define _BRSFC_CV_A_GX1CFH
#define _BRSFC_CV_A_GX1D
#define _BRSFC_CV_A_GX1D_FRAC
#define _BRSFC_CV_A_GX1D_FULL
#define _BRSFC_CV_A_GX1DTG
#define _BRSFC_CV_A_GX1FTG
#define _BRSFC_CV_A_GX1MON
#define _BRSFC_CV_A_GX1MPS1
#define _BRSFC_CV_A_GX1RS
#define _BRSFC_CV_A_GX1TM
#define _BRSFC_CV_A_GX1U
#define _BRSFC_CV_A_GX1U_FRAC
#define _BRSFC_CV_A_GX1U_FULL
#define _BRSFC_CV_A_GX2
#define _BRSFC_CV_A_GX2DTG
#define _BRSFC_CV_A_GX2FTG
#define _BRSFC_CV_A_GX2RS
#define _BRSFC_CV_A_GX2TEST
#define _BRSFC_CV_A_GXB
#define _BRSFC_CV_A_GXBRSFC1
#define _BRSFC_CV_A_GXBRSFC2
#define _BRSFC_CV_A_GXFC
#define _BRSFC_CV_A_GXFC_FRAC
#define _BRSFC_CV_A_GXFC_FULL
#define _BRSFC_CV_A_GXFCD
#define _BRSFC_CV_A_GXFCD_FRAC
#define _BRSFC_CV_A_GXFCD_FULL
#define _BRSFC_CV_A_GXFCMON
#define _BRSFC_CV_A_GXFCU
#define _BRSFC_CV_A_GXFCU_FRAC
#define _BRSFC_CV_A_GXFCU_FULL
#define _BRSFC_CV_A_GXFLPK
#define _BRSFC_CV_A_GXFLPKA
#define _BRSFC_CV_A_GXFLPKB
#define _BRSFC_CV_A_GXFLPVENC
#define _BRSFC_CV_A_GXFLPVENCA
#define _BRSFC_CV_A_GXFLPVENCB
#define _BRSFC_CV_A_GXHYST1
#define _BRSFC_CV_A_GXHYST2
#define _BRSFC_CV_A_GXKAS
#define _BRSFC_CV_A_GXKBSDTG
#define _BRSFC_CV_A_GXKBSRS
#define _BRSFC_CV_A_GXKCS
#define _BRSFC_CV_A_GXKDTG
#define _BRSFC_CV_A_GXKFS
#define _BRSFC_CV_A_GXKILL
#define _BRSFC_CV_A_GXKRCVN
#define _BRSFC_CV_A_GXKRS
#define _BRSFC_CV_A_GXKS
#define _BRSFC_CV_A_GXKSE1
#define _BRSFC_CV_A_GXKSE2
#define _BRSFC_CV_A_GXKSE3
#define _BRSFC_CV_A_GXKSE4
#define _BRSFC_CV_A_GXKSE5
#define _BRSFC_CV_A_GXKSE6
#define _BRSFC_CV_A_GXKSP
#define _BRSFC_CV_A_GXKSSF
#define _BRSFC_CV_A_GXKSX1
#define _BRSFC_CV_A_GXKSX2
#define _BRSFC_CV_A_GXKSY1
#define _BRSFC_CV_A_GXKSY2
#define _BRSFC_CV_A_GXKSZ1
#define _BRSFC_CV_A_GXKSZ2
#define _BRSFC_CV_A_GXRF1TM
#define _BRSFC_CV_A_GXRF2CFH
#define _BRSFC_CV_A_GXRFSX1
#define _BRSFC_CV_A_GXRFSX2
#define _BRSFC_CV_A_GXSPIRAL
#define _BRSFC_CV_A_GXSPIRAL2
#define _BRSFC_CV_A_GXSPOIL
#define _BRSFC_CV_A_GXSPOIL2
#define _BRSFC_CV_A_GXW
#define _BRSFC_CV_A_GXW1FTG
#define _BRSFC_CV_A_GXW1XTG
#define _BRSFC_CV_A_GXW2
#define _BRSFC_CV_A_GXW2DTG
#define _BRSFC_CV_A_GXW2FTG
#define _BRSFC_CV_A_GXW2RS
#define _BRSFC_CV_A_GXWAS
#define _BRSFC_CV_A_GXWDTG
#define _BRSFC_CV_A_GXWEX
#define _BRSFC_CV_A_GXWMON
#define _BRSFC_CV_A_GXWMPS1
#define _BRSFC_CV_A_GXWRS
#define _BRSFC_CV_A_GY1
#define _BRSFC_CV_A_GY1A
#define _BRSFC_CV_A_GY1AS
#define _BRSFC_CV_A_GY1ASA
#define _BRSFC_CV_A_GY1ASB
#define _BRSFC_CV_A_GY1B
#define _BRSFC_CV_A_GY1CFH
#define _BRSFC_CV_A_GY1DTG
#define _BRSFC_CV_A_GY1DTGA
#define _BRSFC_CV_A_GY1DTGB
#define _BRSFC_CV_A_GY1MON
#define _BRSFC_CV_A_GY1MPS1
#define _BRSFC_CV_A_GY1R
#define _BRSFC_CV_A_GY1RA
#define _BRSFC_CV_A_GY1RAS
#define _BRSFC_CV_A_GY1RASA
#define _BRSFC_CV_A_GY1RASB
#define _BRSFC_CV_A_GY1RB
#define _BRSFC_CV_A_GY1RDTG
#define _BRSFC_CV_A_GY1RDTGA
#define _BRSFC_CV_A_GY1RDTGB
#define _BRSFC_CV_A_GY1RRS
#define _BRSFC_CV_A_GY1RRSA
#define _BRSFC_CV_A_GY1RRSB
#define _BRSFC_CV_A_GY1RS
#define _BRSFC_CV_A_GY1RSA
#define _BRSFC_CV_A_GY1RSB
#define _BRSFC_CV_A_GY1TM
#define _BRSFC_CV_A_GY2DTG
#define _BRSFC_CV_A_GY2DTGA
#define _BRSFC_CV_A_GY2DTGB
#define _BRSFC_CV_A_GY2RS
#define _BRSFC_CV_A_GY2RSA
#define _BRSFC_CV_A_GY2RSB
#define _BRSFC_CV_A_GYB
#define _BRSFC_CV_A_GYBRSFC1
#define _BRSFC_CV_A_GYBRSFC2
#define _BRSFC_CV_A_GYCYLR
#define _BRSFC_CV_A_GYCYLRTIPUP
#define _BRSFC_CV_A_GYFE
#define _BRSFC_CV_A_GYFE1
#define _BRSFC_CV_A_GYFE2
#define _BRSFC_CV_A_GYFLPK
#define _BRSFC_CV_A_GYFLPKA
#define _BRSFC_CV_A_GYFLPKB
#define _BRSFC_CV_A_GYFLPVENC
#define _BRSFC_CV_A_GYFLPVENCA
#define _BRSFC_CV_A_GYFLPVENCB
#define _BRSFC_CV_A_GYHYST1
#define _BRSFC_CV_A_GYHYST2
#define _BRSFC_CV_A_GYKCFH
#define _BRSFC_CV_A_GYKCFL
#define _BRSFC_CV_A_GYKCS
#define _BRSFC_CV_A_GYKFS
#define _BRSFC_CV_A_GYKILL
#define _BRSFC_CV_A_GYKRCVN
#define _BRSFC_CV_A_GYKS
#define _BRSFC_CV_A_GYKSE1
#define _BRSFC_CV_A_GYKSE2
#define _BRSFC_CV_A_GYKSE3
#define _BRSFC_CV_A_GYKSE4
#define _BRSFC_CV_A_GYKSE5
#define _BRSFC_CV_A_GYKSE6
#define _BRSFC_CV_A_GYKSP
#define _BRSFC_CV_A_GYKSSF
#define _BRSFC_CV_A_GYKSX1
#define _BRSFC_CV_A_GYKSX2
#define _BRSFC_CV_A_GYKSY1
#define _BRSFC_CV_A_GYKSY2
#define _BRSFC_CV_A_GYKSZ1
#define _BRSFC_CV_A_GYKSZ2
#define _BRSFC_CV_A_GYKXTGL
#define _BRSFC_CV_A_GYKXTGR
#define _BRSFC_CV_A_GYRF0KCFH
#define _BRSFC_CV_A_GYRF1MON
#define _BRSFC_CV_A_GYRF1MPS1
#define _BRSFC_CV_A_GYRF1TM
#define _BRSFC_CV_A_GYRF1XTG
#define _BRSFC_CV_A_GYRF2CFH
#define _BRSFC_CV_A_GYRF2LMON
#define _BRSFC_CV_A_GYRF2MON
#define _BRSFC_CV_A_GYRF2RMON
#define _BRSFC_CV_A_GYRF3CFH
#define _BRSFC_CV_A_GYRFMONTIPUP
#define _BRSFC_CV_A_GYRFSY1
#define _BRSFC_CV_A_GYRFSY2
#define _BRSFC_CV_A_GYSPIRAL
#define _BRSFC_CV_A_GYSPIRAL2
#define _BRSFC_CV_A_GYSPOIL
#define _BRSFC_CV_A_GYSPOIL2
#define _BRSFC_CV_A_GZ1
#define _BRSFC_CV_A_GZ1AS
#define _BRSFC_CV_A_GZ1CFL
#define _BRSFC_CV_A_GZ1D
#define _BRSFC_CV_A_GZ1DTG
#define _BRSFC_CV_A_GZ1FTG
#define _BRSFC_CV_A_GZ1MON
#define _BRSFC_CV_A_GZ1MPS1
#define _BRSFC_CV_A_GZ1RS
#define _BRSFC_CV_A_GZ1S
#define _BRSFC_CV_A_GZ1U
#define _BRSFC_CV_A_GZ1XTG
#define _BRSFC_CV_A_GZ2BFTG
#define _BRSFC_CV_A_GZ2FTG
#define _BRSFC_CV_A_GZ2XTG
#define _BRSFC_CV_A_GZ3FTG
#define _BRSFC_CV_A_GZBRSFC1
#define _BRSFC_CV_A_GZBRSFC1ECHO1
#define _BRSFC_CV_A_GZBRSFC1ECHO2
#define _BRSFC_CV_A_GZBRSFC2
#define _BRSFC_CV_A_GZCOMB
#define _BRSFC_CV_A_GZCOMBA
#define _BRSFC_CV_A_GZCOMBB
#define _BRSFC_CV_A_GZCOMBHTR
#define _BRSFC_CV_A_GZCOMBHTRA
#define _BRSFC_CV_A_GZCOMBHTRB
#define _BRSFC_CV_A_GZCYLR
#define _BRSFC_CV_A_GZCYLRTIPUP
#define _BRSFC_CV_A_GZFC
#define _BRSFC_CV_A_GZFCBASE
#define _BRSFC_CV_A_GZFCCOMB
#define _BRSFC_CV_A_GZFCD
#define _BRSFC_CV_A_GZFCEND
#define _BRSFC_CV_A_GZFCU
#define _BRSFC_CV_A_GZFLPK
#define _BRSFC_CV_A_GZFLPKA
#define _BRSFC_CV_A_GZFLPKB
#define _BRSFC_CV_A_GZFLPVENC
#define _BRSFC_CV_A_GZFLPVENCA
#define _BRSFC_CV_A_GZFLPVENCB
#define _BRSFC_CV_A_GZK
#define _BRSFC_CV_A_GZKAS
#define _BRSFC_CV_A_GZKBASE
#define _BRSFC_CV_A_GZKBSDTG
#define _BRSFC_CV_A_GZKBSRS
#define _BRSFC_CV_A_GZKCOMB
#define _BRSFC_CV_A_GZKCS
#define _BRSFC_CV_A_GZKDTG
#define _BRSFC_CV_A_GZKEND
#define _BRSFC_CV_A_GZKFS
#define _BRSFC_CV_A_GZKGIR01
#define _BRSFC_CV_A_GZKGIR02
#define _BRSFC_CV_A_GZKILL
#define _BRSFC_CV_A_GZKILLER
#define _BRSFC_CV_A_GZKMON
#define _BRSFC_CV_A_GZKMONTIPUP
#define _BRSFC_CV_A_GZKRCVN
#define _BRSFC_CV_A_GZKRFFRIR
#define _BRSFC_CV_A_GZKRS
#define _BRSFC_CV_A_GZKS
#define _BRSFC_CV_A_GZKS5FP
#define _BRSFC_CV_A_GZKSP
#define _BRSFC_CV_A_GZKSSF
#define _BRSFC_CV_A_GZP
#define _BRSFC_CV_A_GZPA
#define _BRSFC_CV_A_GZPB
#define _BRSFC_CV_A_GZPHTR
#define _BRSFC_CV_A_GZPHTRA
#define _BRSFC_CV_A_GZPHTRB
#define _BRSFC_CV_A_GZPTM
#define _BRSFC_CV_A_GZRF0
#define _BRSFC_CV_A_GZRF0CFH
#define _BRSFC_CV_A_GZRF0K
#define _BRSFC_CV_A_GZRF1
#define _BRSFC_CV_A_GZRF1_SS_MAX
#define _BRSFC_CV_A_GZRF1AS
#define _BRSFC_CV_A_GZRF1CFH
#define _BRSFC_CV_A_GZRF1CFL
#define _BRSFC_CV_A_GZRF1DTG
#define _BRSFC_CV_A_GZRF1FTG
#define _BRSFC_CV_A_GZRF1HTR
#define _BRSFC_CV_A_GZRF1MON
#define _BRSFC_CV_A_GZRF1MPS1
#define _BRSFC_CV_A_GZRF1RS
#define _BRSFC_CV_A_GZRF1S
#define _BRSFC_CV_A_GZRF1TEMP
#define _BRSFC_CV_A_GZRF1XTG
#define _BRSFC_CV_A_GZRF2FTG
#define _BRSFC_CV_A_GZRF2LCFH
#define _BRSFC_CV_A_GZRF2LMPS1
#define _BRSFC_CV_A_GZRF2MPS1
#define _BRSFC_CV_A_GZRF2RCFH
#define _BRSFC_CV_A_GZRF2RMPS1
#define _BRSFC_CV_A_GZRF2XTG
#define _BRSFC_CV_A_GZRF3FTG
#define _BRSFC_CV_A_GZRF3LCFH
#define _BRSFC_CV_A_GZRF3RCFH
#define _BRSFC_CV_A_GZRF4CFH
#define _BRSFC_CV_A_GZRF4LCFH
#define _BRSFC_CV_A_GZRF4RCFH
#define _BRSFC_CV_A_GZRFFRIR
#define _BRSFC_CV_A_GZRFGIR01
#define _BRSFC_CV_A_GZRFGIR02
#define _BRSFC_CV_A_GZRFS5FPH
#define _BRSFC_CV_A_GZRFSE1
#define _BRSFC_CV_A_GZRFSE2
#define _BRSFC_CV_A_GZRFSE3
#define _BRSFC_CV_A_GZRFSE4
#define _BRSFC_CV_A_GZRFSE5
#define _BRSFC_CV_A_GZRFSE6
#define _BRSFC_CV_A_GZRFSSFH
#define _BRSFC_CV_A_GZRFSZ1
#define _BRSFC_CV_A_GZRFSZ2
#define _BRSFC_CV_A_GZS5FPHCOMB
#define _BRSFC_CV_A_GZSSFHCOMB
#define _BRSFC_CV_A_GZVLW
#define _BRSFC_CV_A_HARD180
#define _BRSFC_CV_A_HST
#define _BRSFC_CV_A_NOMCYL
#define _BRSFC_CV_A_OMEGA_HS_RFCSSAT
#define _BRSFC_CV_A_OMEGA_IR0
#define _BRSFC_CV_A_OMEGA_RFFRIR
#define _BRSFC_CV_A_OMEGA_RFGIR01
#define _BRSFC_CV_A_OMEGA_RFGIR02
#define _BRSFC_CV_A_OMEGARF0CFH
#define _BRSFC_CV_A_PH180
#define _BRSFC_CV_A_POSTGXW1FTG
#define _BRSFC_CV_A_RF0
#define _BRSFC_CV_A_RF0CFH
#define _BRSFC_CV_A_RF1
#define _BRSFC_CV_A_RF180
#define _BRSFC_CV_A_RF1AS
#define _BRSFC_CV_A_RF1CFH
#define _BRSFC_CV_A_RF1CFL
#define _BRSFC_CV_A_RF1DTG
#define _BRSFC_CV_A_RF1FTG
#define _BRSFC_CV_A_RF1HTR
#define _BRSFC_CV_A_RF1MON
#define _BRSFC_CV_A_RF1MPS1
#define _BRSFC_CV_A_RF1RS
#define _BRSFC_CV_A_RF1TM
#define _BRSFC_CV_A_RF1XTG
#define _BRSFC_CV_A_RF2CFH
#define _BRSFC_CV_A_RF2FTG
#define _BRSFC_CV_A_RF2MON
#define _BRSFC_CV_A_RF2MPS1
#define _BRSFC_CV_A_RF2XTG
#define _BRSFC_CV_A_RF3CFH
#define _BRSFC_CV_A_RF3FTG
#define _BRSFC_CV_A_RF3XTG
#define _BRSFC_CV_A_RF4CFH
#define _BRSFC_CV_A_RF4XTG
#define _BRSFC_CV_A_RF90
#define _BRSFC_CV_A_RFBDTG
#define _BRSFC_CV_A_RFBRS
#define _BRSFC_CV_A_RFCSSAT
#define _BRSFC_CV_A_RFCSSATCFH
#define _BRSFC_CV_A_RFCYLR
#define _BRSFC_CV_A_RFCYLRTIPUP
#define _BRSFC_CV_A_RFFLP180
#define _BRSFC_CV_A_RFFLP180_THE
#define _BRSFC_CV_A_RFFLP90
#define _BRSFC_CV_A_RFFLP90_THE
#define _BRSFC_CV_A_RFFLP90R
#define _BRSFC_CV_A_RFFLP90R_THE
#define _BRSFC_CV_A_RFFRIR
#define _BRSFC_CV_A_RFFS
#define _BRSFC_CV_A_RFGIR01
#define _BRSFC_CV_A_RFGIR02
#define _BRSFC_CV_A_RFMONTIPUP
#define _BRSFC_CV_A_RFS5FPH
#define _BRSFC_CV_A_RFSE1
#define _BRSFC_CV_A_RFSE2
#define _BRSFC_CV_A_RFSE3
#define _BRSFC_CV_A_RFSE4
#define _BRSFC_CV_A_RFSE5
#define _BRSFC_CV_A_RFSE6
#define _BRSFC_CV_A_RFSSF
#define _BRSFC_CV_A_RFSSFH
#define _BRSFC_CV_A_RFSX1
#define _BRSFC_CV_A_RFSX2
#define _BRSFC_CV_A_RFSY1
#define _BRSFC_CV_A_RFSY2
#define _BRSFC_CV_A_RFSZ1
#define _BRSFC_CV_A_RFSZ2
#define _BRSFC_CV_A_RFTIPUP
#define _BRSFC_CV_A_SDIXON
#define _BRSFC_CV_A_SDIXON2
#define _BRSFC_CV_A_THCYLR
#define _BRSFC_CV_A_THCYLRTIPUP
#define _BRSFC_CV_A_THETARF1
#define _BRSFC_CV_A_XDIXON
#define _BRSFC_CV_A_YDIXON
#define _BRSFC_CV_A_ZDIXON
#define _BRSFC_CV_AB1_ENABLE
#define _BRSFC_CV_ABSPOWER_LX
#define _BRSFC_CV_ABSPOWER_LY
#define _BRSFC_CV_ABSPOWER_LZ
#define _BRSFC_CV_ABSPOWER_PX
#define _BRSFC_CV_ABSPOWER_PY
#define _BRSFC_CV_ABSPOWER_PZ
#define _BRSFC_CV_ACCEL_KT_CAL_STRIDE
#define _BRSFC_CV_ACCEL_OUTER2CAL_FACTOR
#define _BRSFC_CV_ACCEL_PH_DEFSTRIDE
#define _BRSFC_CV_ACCEL_PH_STRIDE
#define _BRSFC_CV_ACCEL_PHASERES
#define _BRSFC_CV_ACCEL_SL_DEFSTRIDE
#define _BRSFC_CV_ACCEL_SL_STRIDE
#define _BRSFC_CV_ACGD_LITE_TARGET
#define _BRSFC_CV_ACQ_DATA_ONLY
#define _BRSFC_CV_ACQ_TYPE
#define _BRSFC_CV_ACQS
#define _BRSFC_CV_ACQUIRE_TYPE
#define _BRSFC_CV_ACT_AREGION_FRACTION
#define _BRSFC_CV_ACT_ECHOFRAC
#define _BRSFC_CV_ACT_HTR
#define _BRSFC_CV_ACT_NAVGATE_TR
#define _BRSFC_CV_ACT_SCAMP
#define _BRSFC_CV_ACT_SRATE
#define _BRSFC_CV_ACT_SRATE_X
#define _BRSFC_CV_ACT_SRATE_Y
#define _BRSFC_CV_ACT_SRATE_Z
#define _BRSFC_CV_ACT_TE
#define _BRSFC_CV_ACT_TE2
#define _BRSFC_CV_ACT_TE_CYLR
#define _BRSFC_CV_ACT_TR
#define _BRSFC_CV_ADD_SLICEREADGAP
#define _BRSFC_CV_ADD_TETIME
#define _BRSFC_CV_ADJ_ACT_TR
#define _BRSFC_CV_ALLOW_UGFSF
#define _BRSFC_CV_ALPHA_RF0
#define _BRSFC_CV_ALPHA_RF0CFH
#define _BRSFC_CV_ALPHA_RF1
#define _BRSFC_CV_ALPHA_RF1AS
#define _BRSFC_CV_ALPHA_RF1CFH
#define _BRSFC_CV_ALPHA_RF1CFL
#define _BRSFC_CV_ALPHA_RF1FTG
#define _BRSFC_CV_ALPHA_RF1MON
#define _BRSFC_CV_ALPHA_RF1MPS1
#define _BRSFC_CV_ALPHA_RF1TM
#define _BRSFC_CV_ALPHA_RF1XTG
#define _BRSFC_CV_ALPHA_RF2CFH
#define _BRSFC_CV_ALPHA_RF2FTG
#define _BRSFC_CV_ALPHA_RF2MON
#define _BRSFC_CV_ALPHA_RF2MPS1
#define _BRSFC_CV_ALPHA_RF2XTG
#define _BRSFC_CV_ALPHA_RF3CFH
#define _BRSFC_CV_ALPHA_RF3FTG
#define _BRSFC_CV_ALPHA_RF3XTG
#define _BRSFC_CV_ALPHA_RF4CFH
#define _BRSFC_CV_ALPHA_RF4XTG
#define _BRSFC_CV_ALPHA_RFCSSAT
#define _BRSFC_CV_ALPHA_RFFRIR
#define _BRSFC_CV_ALPHA_RFGIR01
#define _BRSFC_CV_ALPHA_RFGIR02
#define _BRSFC_CV_ALPHA_RFMONTIPUP
#define _BRSFC_CV_ALPHA_RFSE1
#define _BRSFC_CV_ALPHA_RFSE2
#define _BRSFC_CV_ALPHA_RFSE3
#define _BRSFC_CV_ALPHA_RFSE4
#define _BRSFC_CV_ALPHA_RFSE5
#define _BRSFC_CV_ALPHA_RFSE6
#define _BRSFC_CV_ALPHA_RFSX1
#define _BRSFC_CV_ALPHA_RFSX2
#define _BRSFC_CV_ALPHA_RFSY1
#define _BRSFC_CV_ALPHA_RFSY2
#define _BRSFC_CV_ALPHA_RFSZ1
#define _BRSFC_CV_ALPHA_RFSZ2
#define _BRSFC_CV_AMP_FLPVENC_LIMIT
#define _BRSFC_CV_AMP_FLPVENC_MAX
#define _BRSFC_CV_AMPTRANS_LX
#define _BRSFC_CV_AMPTRANS_LY
#define _BRSFC_CV_AMPTRANS_LZ
#define _BRSFC_CV_AMPTRANS_PX
#define _BRSFC_CV_AMPTRANS_PY
#define _BRSFC_CV_AMPTRANS_PZ
#define _BRSFC_CV_ANNE_CHANNEL_PERCENTAGE
#define _BRSFC_CV_ANNE_INTENSITY_THRES
#define _BRSFC_CV_ANNE_MASK_DILATION_LENGTH
#define _BRSFC_CV_ANNEFACT_C3_RECON_FLAG
#define _BRSFC_CV_ANNEFACT_REDUCTION_FLAG
#define _BRSFC_CV_AP_FLOW
#define _BRSFC_CV_APHASES_MAX
#define _BRSFC_CV_APODIZE_LEVEL_FLAG
#define _BRSFC_CV_APP_GRAD_TYPE
#define _BRSFC_CV_APX_COMPATIBLE
#define _BRSFC_CV_APX_CVEVAL_COUNTER
#define _BRSFC_CV_ARC_CAL_ECHO
#define _BRSFC_CV_ARC_DEBUG_FILES
#define _BRSFC_CV_ARC_EQUANT
#define _BRSFC_CV_ARC_FLAG
#define _BRSFC_CV_ARC_MAXNETACCEL
#define _BRSFC_CV_ARC_NETACCEL
#define _BRSFC_CV_ARC_PACK_BAM
#define _BRSFC_CV_ARC_PH_CALWIDTH
#define _BRSFC_CV_ARC_PH_INTACCEL
#define _BRSFC_CV_ARC_PH_MAXNETACCEL
#define _BRSFC_CV_ARC_PH_MAXSTRIDE
#define _BRSFC_CV_ARC_PH_MINCALWIDTH
#define _BRSFC_CV_ARC_PH_NETACCEL
#define _BRSFC_CV_ARC_PH_RECLIMSTRIDE
#define _BRSFC_CV_ARC_PH_RECSTRIDE
#define _BRSFC_CV_ARC_PH_STRIDE
#define _BRSFC_CV_ARC_PH_USERSTRIDE
#define _BRSFC_CV_ARC_RECLIMNETACCEL
#define _BRSFC_CV_ARC_RECNETACCEL
#define _BRSFC_CV_ARC_RESEARCH_FLAG
#define _BRSFC_CV_ARC_SL_CALWIDTH
#define _BRSFC_CV_ARC_SL_INTACCEL
#define _BRSFC_CV_ARC_SL_MAXNETACCEL
#define _BRSFC_CV_ARC_SL_MAXSTRIDE
#define _BRSFC_CV_ARC_SL_MINCALWIDTH
#define _BRSFC_CV_ARC_SL_NETACCEL
#define _BRSFC_CV_ARC_SL_RECLIMSTRIDE
#define _BRSFC_CV_ARC_SL_RECSTRIDE
#define _BRSFC_CV_ARC_SL_STRIDE
#define _BRSFC_CV_ARC_SL_USERSTRIDE
#define _BRSFC_CV_ARC_SYN_PTS
#define _BRSFC_CV_AREA_DE
#define _BRSFC_CV_AREA_FLPK
#define _BRSFC_CV_AREA_FLPVENC_STD
#define _BRSFC_CV_AREA_GX1
#define _BRSFC_CV_AREA_GX2
#define _BRSFC_CV_AREA_GXFC
#define _BRSFC_CV_AREA_GXKCS
#define _BRSFC_CV_AREA_GXKFS
#define _BRSFC_CV_AREA_GXKRCVN
#define _BRSFC_CV_AREA_GXKS
#define _BRSFC_CV_AREA_GXKSE1
#define _BRSFC_CV_AREA_GXKSE2
#define _BRSFC_CV_AREA_GXKSE3
#define _BRSFC_CV_AREA_GXKSE4
#define _BRSFC_CV_AREA_GXKSE5
#define _BRSFC_CV_AREA_GXKSE6
#define _BRSFC_CV_AREA_GXKSSF
#define _BRSFC_CV_AREA_GXKSX1
#define _BRSFC_CV_AREA_GXKSX2
#define _BRSFC_CV_AREA_GXKSY1
#define _BRSFC_CV_AREA_GXKSY2
#define _BRSFC_CV_AREA_GXKSZ1
#define _BRSFC_CV_AREA_GXKSZ2
#define _BRSFC_CV_AREA_GXW
#define _BRSFC_CV_AREA_GXWAS
#define _BRSFC_CV_AREA_GXWEX
#define _BRSFC_CV_AREA_GY1GRAD
#define _BRSFC_CV_AREA_GY1TABLE
#define _BRSFC_CV_AREA_GYAKFS
#define _BRSFC_CV_AREA_GYAKSSF
#define _BRSFC_CV_AREA_GYKCFH
#define _BRSFC_CV_AREA_GYKCFL
#define _BRSFC_CV_AREA_GYKCS
#define _BRSFC_CV_AREA_GYKFS
#define _BRSFC_CV_AREA_GYKRCVN
#define _BRSFC_CV_AREA_GYKS
#define _BRSFC_CV_AREA_GYKSE1
#define _BRSFC_CV_AREA_GYKSE2
#define _BRSFC_CV_AREA_GYKSE3
#define _BRSFC_CV_AREA_GYKSE4
#define _BRSFC_CV_AREA_GYKSE5
#define _BRSFC_CV_AREA_GYKSE6
#define _BRSFC_CV_AREA_GYKSSF
#define _BRSFC_CV_AREA_GYKSX1
#define _BRSFC_CV_AREA_GYKSX2
#define _BRSFC_CV_AREA_GYKSY1
#define _BRSFC_CV_AREA_GYKSY2
#define _BRSFC_CV_AREA_GYKSZ1
#define _BRSFC_CV_AREA_GYKSZ2
#define _BRSFC_CV_AREA_GZ1
#define _BRSFC_CV_AREA_GZ1AS
#define _BRSFC_CV_AREA_GZFC
#define _BRSFC_CV_AREA_GZK
#define _BRSFC_CV_AREA_GZKCS
#define _BRSFC_CV_AREA_GZKFS
#define _BRSFC_CV_AREA_GZKGIR01
#define _BRSFC_CV_AREA_GZKGIR02
#define _BRSFC_CV_AREA_GZKMON
#define _BRSFC_CV_AREA_GZKMONTIPUP
#define _BRSFC_CV_AREA_GZKRCVN
#define _BRSFC_CV_AREA_GZKS
#define _BRSFC_CV_AREA_GZKS5FP
#define _BRSFC_CV_AREA_GZKSSF
#define _BRSFC_CV_AREA_GZRF0K
#define _BRSFC_CV_AREA_HST
#define _BRSFC_CV_AREA_KILLERX
#define _BRSFC_CV_AREA_KILLERY
#define _BRSFC_CV_AREA_KILLERZ
#define _BRSFC_CV_AREA_READRAMPAS
#define _BRSFC_CV_AREA_RF1
#define _BRSFC_CV_AREA_RF11
#define _BRSFC_CV_AREA_RFFS
#define _BRSFC_CV_AREA_RFSE1
#define _BRSFC_CV_AREA_RFSE2
#define _BRSFC_CV_AREA_RFSE3
#define _BRSFC_CV_AREA_RFSE4
#define _BRSFC_CV_AREA_RFSE5
#define _BRSFC_CV_AREA_RFSE6
#define _BRSFC_CV_AREA_RFSSF
#define _BRSFC_CV_AREA_RFSSFH
#define _BRSFC_CV_AREA_RFSX1
#define _BRSFC_CV_AREA_RFSX2
#define _BRSFC_CV_AREA_RFSY1
#define _BRSFC_CV_AREA_RFSY2
#define _BRSFC_CV_AREA_RFSZ1
#define _BRSFC_CV_AREA_RFSZ2
#define _BRSFC_CV_AREA_SPOILERX
#define _BRSFC_CV_AREA_SPOILERY
#define _BRSFC_CV_AREA_SPOILERZ
#define _BRSFC_CV_AREA_XTGYKILLER
#define _BRSFC_CV_AREA_XTGZKILLER
#define _BRSFC_CV_AREGION_FRACTION
#define _BRSFC_CV_ARR_CHECK
#define _BRSFC_CV_AS_DDA
#define _BRSFC_CV_AS_NEWGEO
#define _BRSFC_CV_ASBASELINE
#define _BRSFC_CV_ASFLIP
#define _BRSFC_CV_ASFOV
#define _BRSFC_CV_ASLENAP
#define _BRSFC_CV_ASLENRL
#define _BRSFC_CV_ASLENSI
#define _BRSFC_CV_ASLOCAP
#define _BRSFC_CV_ASLOCRL
#define _BRSFC_CV_ASLOCSI
#define _BRSFC_CV_ASLOGGRD
#define _BRSFC_CV_ASOBL_DEBUG
#define _BRSFC_CV_ASPIR_FA_SCALING_FLAG
#define _BRSFC_CV_ASPIR_FLAG
#define _BRSFC_CV_ASPIR_OVERRIDE
#define _BRSFC_CV_ASPTSIZE
#define _BRSFC_CV_ASRHBLANK
#define _BRSFC_CV_ASSET_FACTOR
#define _BRSFC_CV_ASSET_SUPPORTED_DIRECTION
#define _BRSFC_CV_ASSETPH_FLAG
#define _BRSFC_CV_ASSETSL_FACTOR
#define _BRSFC_CV_ASSETSL_FLAG
#define _BRSFC_CV_ASSETSL_MIN_OPVTHICK
#define _BRSFC_CV_ASSLQUANT
#define _BRSFC_CV_ASSLTHICK
#define _BRSFC_CV_ASX_KILLER_AREA
#define _BRSFC_CV_ASXRES
#define _BRSFC_CV_ASYMMATRIX
#define _BRSFC_CV_ASYRES
#define _BRSFC_CV_ASZ_KILLER_AREA
#define _BRSFC_CV_ATTENLEN
#define _BRSFC_CV_ATTENLENGTH
#define _BRSFC_CV_AUDIBLE_LOOP
#define _BRSFC_CV_AUTOADVTOSCN
#define _BRSFC_CV_AUTOCAL_MODE
#define _BRSFC_CV_AUTOLOCK
#define _BRSFC_CV_AUTOPARAMS_DEBUG
#define _BRSFC_CV_AVAIL_RRTIME
#define _BRSFC_CV_AVAIL_IMAGE_TIME
#define _BRSFC_CV_AVAIL_PWGX1AS
#define _BRSFC_CV_AVAIL_PWGZ1AS
#define _BRSFC_CV_AVAIL_TEMP
#define _BRSFC_CV_AVE_GRADY_GY1_SCALE
#define _BRSFC_CV_AVE_GRADZ_GZCOMB_SCALE
#define _BRSFC_CV_AVE_GRADZ_GZP_SCALE
#define _BRSFC_CV_AVECRUSHPEPOWSCALE_FOR_SBM_XFD
#define _BRSFC_CV_AVMAX_DDA
#define _BRSFC_CV_AVMAXACCEL_CS_STRIDE
#define _BRSFC_CV_AVMAXACCEL_KT_STRIDE
#define _BRSFC_CV_AVMAXACCEL_MB_STRIDE
#define _BRSFC_CV_AVMAXACCEL_PH_STRIDE
#define _BRSFC_CV_AVMAXACCEL_SL_STRIDE
#define _BRSFC_CV_AVMAXACCEL_T_STRIDE
#define _BRSFC_CV_AVMAXACQS
#define _BRSFC_CV_AVMAXALLOWEDRESCANTIME
#define _BRSFC_CV_AVMAXAPHASES
#define _BRSFC_CV_AVMAXBSPTI
#define _BRSFC_CV_AVMAXBVAL
#define _BRSFC_CV_AVMAXBVALSTAB
#define _BRSFC_CV_AVMAXDIFNEXT2
#define _BRSFC_CV_AVMAXDIFNEXTAB
#define _BRSFC_CV_AVMAXETL
#define _BRSFC_CV_AVMAXFLIP
#define _BRSFC_CV_AVMAXFOV
#define _BRSFC_CV_AVMAXFPHASES
#define _BRSFC_CV_AVMAXNAVACCWIN
#define _BRSFC_CV_AVMAXNAVAUTOTRIGTIME
#define _BRSFC_CV_AVMAXNAVMAXINTERVAL
#define _BRSFC_CV_AVMAXNAVPSCTIME
#define _BRSFC_CV_AVMAXNAVRRMEASTIME
#define _BRSFC_CV_AVMAXNECHO
#define _BRSFC_CV_AVMAXNEX
#define _BRSFC_CV_AVMAXNSEG
#define _BRSFC_CV_AVMAXNSHOTS
#define _BRSFC_CV_AVMAXNSPOKES
#define _BRSFC_CV_AVMAXNUMBVALS
#define _BRSFC_CV_AVMAXNUMSYNBVALS
#define _BRSFC_CV_AVMAXOVERSAMPLINGFACTOR
#define _BRSFC_CV_AVMAXOVL
#define _BRSFC_CV_AVMAXPHASEFOV
#define _BRSFC_CV_AVMAXPHASES
#define _BRSFC_CV_AVMAXPHASSETFAC
#define _BRSFC_CV_AVMAXRBW
#define _BRSFC_CV_AVMAXRBW2
#define _BRSFC_CV_AVMAXRBW_SYSTEM
#define _BRSFC_CV_AVMAXREP_ACTIVE
#define _BRSFC_CV_AVMAXREP_REST
#define _BRSFC_CV_AVMAXSLASSETFAC
#define _BRSFC_CV_AVMAXSLDELAY
#define _BRSFC_CV_AVMAXSLICECNT
#define _BRSFC_CV_AVMAXSLQUANT
#define _BRSFC_CV_AVMAXSLSPACE
#define _BRSFC_CV_AVMAXSLTHICK
#define _BRSFC_CV_AVMAXSYNBVALSTAB
#define _BRSFC_CV_AVMAXT2PREPTE
#define _BRSFC_CV_AVMAXTDEL1
#define _BRSFC_CV_AVMAXTE
#define _BRSFC_CV_AVMAXTE2
#define _BRSFC_CV_AVMAXTI
#define _BRSFC_CV_AVMAXTISSUET1
#define _BRSFC_CV_AVMAXTLABEL
#define _BRSFC_CV_AVMAXTOUCHAMP
#define _BRSFC_CV_AVMAXTOUCHCYC
#define _BRSFC_CV_AVMAXTOUCHFREQ
#define _BRSFC_CV_AVMAXTOUCHMEGFREQ
#define _BRSFC_CV_AVMAXTOUCHTPHASES
#define _BRSFC_CV_AVMAXTPHASES
#define _BRSFC_CV_AVMAXTR
#define _BRSFC_CV_AVMAXTRECOVERY
#define _BRSFC_CV_AVMAXTRICKSDEL
#define _BRSFC_CV_AVMAXTSEQ
#define _BRSFC_CV_AVMAXVENC
#define _BRSFC_CV_AVMAXVEST
#define _BRSFC_CV_AVMAXVQUANT
#define _BRSFC_CV_AVMAXVSPHASES
#define _BRSFC_CV_AVMAXXRES
#define _BRSFC_CV_AVMAXYRES
#define _BRSFC_CV_AVMIN_DDA
#define _BRSFC_CV_AVMINACCEL_CS_STRIDE
#define _BRSFC_CV_AVMINACCEL_KT_STRIDE
#define _BRSFC_CV_AVMINACCEL_MB_STRIDE
#define _BRSFC_CV_AVMINACCEL_PH_STRIDE
#define _BRSFC_CV_AVMINACCEL_SL_STRIDE
#define _BRSFC_CV_AVMINACCEL_T_STRIDE
#define _BRSFC_CV_AVMINALLOWEDRESCANTIME
#define _BRSFC_CV_AVMINAPHASES
#define _BRSFC_CV_AVMINBSPTI
#define _BRSFC_CV_AVMINBVAL
#define _BRSFC_CV_AVMINBVALSTAB
#define _BRSFC_CV_AVMINDIFNEXT2
#define _BRSFC_CV_AVMINDIFNEXTAB
#define _BRSFC_CV_AVMINDPHASES
#define _BRSFC_CV_AVMINETL
#define _BRSFC_CV_AVMINFLIP
#define _BRSFC_CV_AVMINFOV
#define _BRSFC_CV_AVMINFPHASES
#define _BRSFC_CV_AVMINNAVACCWIN
#define _BRSFC_CV_AVMINNAVAUTOTRIGTIME
#define _BRSFC_CV_AVMINNAVMAXINTERVAL
#define _BRSFC_CV_AVMINNAVPSCTIME
#define _BRSFC_CV_AVMINNAVRRMEASTIME
#define _BRSFC_CV_AVMINNECHO
#define _BRSFC_CV_AVMINNEX
#define _BRSFC_CV_AVMINNSEG
#define _BRSFC_CV_AVMINNSHOTS
#define _BRSFC_CV_AVMINNSPOKES
#define _BRSFC_CV_AVMINNUMBVALS
#define _BRSFC_CV_AVMINNUMSYNBVALS
#define _BRSFC_CV_AVMINOVERSAMPLINGFACTOR
#define _BRSFC_CV_AVMINPHASEFOV
#define _BRSFC_CV_AVMINPHASES
#define _BRSFC_CV_AVMINPHASSETFAC
#define _BRSFC_CV_AVMINRBW
#define _BRSFC_CV_AVMINRBW2
#define _BRSFC_CV_AVMINREP_ACTIVE
#define _BRSFC_CV_AVMINREP_REST
#define _BRSFC_CV_AVMINRTTSEQ
#define _BRSFC_CV_AVMINSLASSETFAC
#define _BRSFC_CV_AVMINSLDELAY
#define _BRSFC_CV_AVMINSLICECNT
#define _BRSFC_CV_AVMINSLQUANT
#define _BRSFC_CV_AVMINSLSPACE
#define _BRSFC_CV_AVMINSLTHICK
#define _BRSFC_CV_AVMINSYNBVALSTAB
#define _BRSFC_CV_AVMINT2PREPTE
#define _BRSFC_CV_AVMINTDEL1
#define _BRSFC_CV_AVMINTE
#define _BRSFC_CV_AVMINTE2
#define _BRSFC_CV_AVMINTI
#define _BRSFC_CV_AVMINTISSUET1
#define _BRSFC_CV_AVMINTLABEL
#define _BRSFC_CV_AVMINTOUCHAMP
#define _BRSFC_CV_AVMINTOUCHCYC
#define _BRSFC_CV_AVMINTOUCHFREQ
#define _BRSFC_CV_AVMINTOUCHMEGFREQ
#define _BRSFC_CV_AVMINTOUCHTPHASES
#define _BRSFC_CV_AVMINTPHASES
#define _BRSFC_CV_AVMINTR
#define _BRSFC_CV_AVMINTRECOVERY
#define _BRSFC_CV_AVMINTRICKSDEL
#define _BRSFC_CV_AVMINTSCAN
#define _BRSFC_CV_AVMINTSEQ
#define _BRSFC_CV_AVMINVENC
#define _BRSFC_CV_AVMINVEST
#define _BRSFC_CV_AVMINVSPHASES
#define _BRSFC_CV_AVMINXRES
#define _BRSFC_CV_AVMINYRES
#define _BRSFC_CV_AVROUND
#define _BRSFC_CV_B1DERATE_FLAG
#define _BRSFC_CV_B1MAX_SCALE
#define _BRSFC_CV_B_VALUE_3IN1
#define _BRSFC_CV_B_VALUE_SINGLE
#define _BRSFC_CV_BALANCED_FE
#define _BRSFC_CV_BASELINE
#define _BRSFC_CV_BD_INDEX
#define _BRSFC_CV_BF_RFSCALE
#define _BRSFC_CV_BLANK
#define _BRSFC_CV_BRAVA_FLAG
#define _BRSFC_CV_BRAVO_FATSAT
#define _BRSFC_CV_BRAVO_FLAG
#define _BRSFC_CV_BREAK_FLAG
#define _BRSFC_CV_BREASTCOIL_FLAG
#define _BRSFC_CV_BREAST_SPSP_FLAG
#define _BRSFC_CV_BRIDGE_GXW2_GXWEX_3DDE
#define _BRSFC_CV_BRS_2D_FIESTA_RF_FLAG
#define _BRSFC_CV_BRS_2DFLAG
#define _BRSFC_CV_BRS_ALPHA
#define _BRSFC_CV_BRS_ALPHA_CENTER
#define _BRSFC_CV_BRS_AREAMODE
#define _BRSFC_CV_BRS_BLIPFLAG
#define _BRSFC_CV_BRS_DAQDEL
#define _BRSFC_CV_BRS_DAQDELOFF
#define _BRSFC_CV_BRS_DAQDELOFF_ZOOM
#define _BRSFC_CV_BRS_DDAHBS
#define _BRSFC_CV_BRS_DEBUG_VIEWORD
#define _BRSFC_CV_BRS_DOFRACZ
#define _BRSFC_CV_BRS_ECHO_WAIT
#define _BRSFC_CV_BRS_EXCITE_GRAD
#define _BRSFC_CV_BRS_EXNO
#define _BRSFC_CV_BRS_EXTRA_ESP
#define _BRSFC_CV_BRS_EXTRA_LEN
#define _BRSFC_CV_BRS_EXTRAWAIT
#define _BRSFC_CV_BRS_FAST_REC_LPF
#define _BRSFC_CV_BRS_FILTDEL
#define _BRSFC_CV_BRS_FLEX
#define _BRSFC_CV_BRS_FOV0
#define _BRSFC_CV_BRS_FOV1
#define _BRSFC_CV_BRS_FOV2
#define _BRSFC_CV_BRS_FOVPOW
#define _BRSFC_CV_BRS_FRACZ_FACT
#define _BRSFC_CV_BRS_FS_SLICE
#define _BRSFC_CV_BRS_FSPREP_FLAG
#define _BRSFC_CV_BRS_FW_TE_STEP
#define _BRSFC_CV_BRS_FWFLAG
#define _BRSFC_CV_BRS_GATEDDAS
#define _BRSFC_CV_BRS_GMAX
#define _BRSFC_CV_BRS_GRAD_DERATE
#define _BRSFC_CV_BRS_GRAD_POWSCALE
#define _BRSFC_CV_BRS_GRADLEN
#define _BRSFC_CV_BRS_GRADLEN2
#define _BRSFC_CV_BRS_GSLEW
#define _BRSFC_CV_BRS_GZVL_AREA_BASE
#define _BRSFC_CV_BRS_GZVL_DELTE
#define _BRSFC_CV_BRS_GZVL_FLAG
#define _BRSFC_CV_BRS_LEAFGROUP
#define _BRSFC_CV_BRS_LEAFLEN
#define _BRSFC_CV_BRS_LEAFSKIP
#define _BRSFC_CV_BRS_M1NULL
#define _BRSFC_CV_BRS_MAPDEL
#define _BRSFC_CV_BRS_MAPDEL_ACT
#define _BRSFC_CV_BRS_MATRIXSIZE_CENTER
#define _BRSFC_CV_BRS_ME_FLAG
#define _BRSFC_CV_BRS_MFA_FLAG
#define _BRSFC_CV_BRS_MFA_NUM
#define _BRSFC_CV_BRS_MFA_SCHEDULE
#define _BRSFC_CV_BRS_MIN_ESP
#define _BRSFC_CV_BRS_MRA_FLAG
#define _BRSFC_CV_BRS_NFOLDS
#define _BRSFC_CV_BRS_NPHASES
#define _BRSFC_CV_BRS_NUMLEAVES
#define _BRSFC_CV_BRS_NUMLEAVES_ACQ
#define _BRSFC_CV_BRS_OPTI
#define _BRSFC_CV_BRS_PM_NUMLEAVES
#define _BRSFC_CV_BRS_PM_TYPE
#define _BRSFC_CV_BRS_PREIRDEL
#define _BRSFC_CV_BRS_PSC
#define _BRSFC_CV_BRS_PSC_PROT_NO
#define _BRSFC_CV_BRS_PSC_USE_TRACKER
#define _BRSFC_CV_BRS_RAMPLENGTH
#define _BRSFC_CV_BRS_RAMPLENGTH2
#define _BRSFC_CV_BRS_READOUTDELAY
#define _BRSFC_CV_BRS_REALTIME
#define _BRSFC_CV_BRS_RECRATIO
#define _BRSFC_CV_BRS_RHRECON
#define _BRSFC_CV_BRS_RSCALE
#define _BRSFC_CV_BRS_RSPSKP
#define _BRSFC_CV_BRS_S5FP
#define _BRSFC_CV_BRS_SAMPFACT
#define _BRSFC_CV_BRS_SAMPFACT_CENTER
#define _BRSFC_CV_BRS_SCANTYPE
#define _BRSFC_CV_BRS_SHIM_FLAG
#define _BRSFC_CV_BRS_SHIM_UPDATE_TYPE
#define _BRSFC_CV_BRS_SHIM_X
#define _BRSFC_CV_BRS_SHIM_Y
#define _BRSFC_CV_BRS_SHIM_Z
#define _BRSFC_CV_BRS_SLEWMAX
#define _BRSFC_CV_BRS_SSFP_FLAG
#define _BRSFC_CV_BRS_TYPE
#define _BRSFC_CV_BRS_USE_MIN_SEQGRAD
#define _BRSFC_CV_BRS_VIEWORD
#define _BRSFC_CV_BRS_VIEWSTOCENTER
#define _BRSFC_CV_BRS_XAREA
#define _BRSFC_CV_BRS_XAREA2
#define _BRSFC_CV_BRS_XBLIPAREA
#define _BRSFC_CV_BRS_XTARGET
#define _BRSFC_CV_BRS_XX
#define _BRSFC_CV_BRS_XY
#define _BRSFC_CV_BRS_YAREA
#define _BRSFC_CV_BRS_YAREA2
#define _BRSFC_CV_BRS_YBLIPAREA
#define _BRSFC_CV_BRS_YTARGET
#define _BRSFC_CV_BRS_YX
#define _BRSFC_CV_BRS_YY
#define _BRSFC_CV_BRS_ZAREA
#define _BRSFC_CV_BRS_ZSEG
#define _BRSFC_CV_BRS_ZTARGET
#define _BRSFC_CV_BRS_ZVPS
#define _BRSFC_CV_BRSFC_FLAG
#define _BRSFC_CV_BRSFC_LONGFC
#define _BRSFC_CV_BRSFMX
#define _BRSFC_CV_BRSFMY
#define _BRSFC_CV_BRSFMZ
#define _BRSFC_CV_BTEMP_DEBUG
#define _BRSFC_CV_BTEMP_MONITOR
#define _BRSFC_CV_BURSTREPS
#define _BRSFC_CV_BW_RF0
#define _BRSFC_CV_BW_RF1
#define _BRSFC_CV_BW_RF1AS
#define _BRSFC_CV_BW_RF1MON
#define _BRSFC_CV_BW_RF2MON
#define _BRSFC_CV_BW_RFFRIR
#define _BRSFC_CV_BW_RFGIR01
#define _BRSFC_CV_BW_RFGIR02
#define _BRSFC_CV_BW_RFMONTIPUP
#define _BRSFC_CV_BW_RFSSFH
#define _BRSFC_CV_CAL3D_FLAG
#define _BRSFC_CV_CAL3D_INTERLEAVE
#define _BRSFC_CV_CAL3D_NEX1
#define _BRSFC_CV_CAL3D_NEX2
#define _BRSFC_CV_CAL3D_NEX3
#define _BRSFC_CV_CAL3D_NEX_MODE
#define _BRSFC_CV_CAL3D_PASS_SET
#define _BRSFC_CV_CAL3D_PAUSE_STEP
#define _BRSFC_CV_CAL3D_PHASES
#define _BRSFC_CV_CAL3D_STATE
#define _BRSFC_CV_CAL3D_STATE1
#define _BRSFC_CV_CAL3D_STATE2
#define _BRSFC_CV_CAL3D_STATE3
#define _BRSFC_CV_CALREGION
#define _BRSFC_CV_CAL_KY_KTARC
#define _BRSFC_CV_CAL_KZ_KTARC
#define _BRSFC_CV_CAL_SHAPE
#define _BRSFC_CV_CALC_RATE
#define _BRSFC_CV_CALIBRATIONPOINTS
#define _BRSFC_CV_CCS_DEAD
#define _BRSFC_CV_CCS_RELAXERS
#define _BRSFC_CV_CCS_RELAXSEQTIME
#define _BRSFC_CV_CCS_RELAXTIME
#define _BRSFC_CV_CENTRIC_FLAG
#define _BRSFC_CV_CERDTYPE
#define _BRSFC_CV_CFBBTRANSMITSELECT
#define _BRSFC_CV_CFDUALDRIVECAPABLE
#define _BRSFC_CV_CFELLIPTICDRIVEENABLE
#define _BRSFC_CV_CFMNSCONVERTERSELECT
#define _BRSFC_CV_CFNBTRANSMITSELECT
#define _BRSFC_CV_CFOPTIMALSNRRECON
#define _BRSFC_CV_CFVIRTUALCHANNELRECON
#define _BRSFC_CV_CFACCEL_CS_MAXSTRIDE
#define _BRSFC_CV_CFACCEL_PH_MAXSTRIDE
#define _BRSFC_CV_CFACCEL_SL_MAXSTRIDE
#define _BRSFC_CV_CFACQTODISKSIZE
#define _BRSFC_CV_CFBBMOD
#define _BRSFC_CV_CFBDCABLETGLIMIT
#define _BRSFC_CV_CFBLLR
#define _BRSFC_CV_CFBPDL
#define _BRSFC_CV_CFBPSL
#define _BRSFC_CV_CFBPV
#define _BRSFC_CV_CFBQPC
#define _BRSFC_CV_CFBWMIN
#define _BRSFC_CV_CFBWMIN1
#define _BRSFC_CV_CFCABLEBW
#define _BRSFC_CV_CFCABLEFREQ
#define _BRSFC_CV_CFCABLETG
#define _BRSFC_CV_CFCARDDELAY
#define _BRSFC_CV_CFCERDTYPE
#define _BRSFC_CV_CFCFTDEL
#define _BRSFC_CV_CFCGAIN
#define _BRSFC_CV_CFCOILAC_RXA
#define _BRSFC_CV_CFCOILAC_RXB
#define _BRSFC_CV_CFCOILAC_RXC
#define _BRSFC_CV_CFCOILAC_RYA
#define _BRSFC_CV_CFCOILAC_RYB
#define _BRSFC_CV_CFCOILAC_RYC
#define _BRSFC_CV_CFCOILAC_RZA
#define _BRSFC_CV_CFCOILAC_RZB
#define _BRSFC_CV_CFCOILAC_RZC
#define _BRSFC_CV_CFCOILAC_FFTPOINTS
#define _BRSFC_CV_CFCOILAC_GAIN
#define _BRSFC_CV_CFCOILAC_LUMPL2X
#define _BRSFC_CV_CFCOILAC_LUMPL2Y
#define _BRSFC_CV_CFCOILAC_LUMPL2Z
#define _BRSFC_CV_CFCOILAC_LUMPL4X
#define _BRSFC_CV_CFCOILAC_LUMPL4Y
#define _BRSFC_CV_CFCOILAC_LUMPL4Z
#define _BRSFC_CV_CFCOILAC_LUMPR1X
#define _BRSFC_CV_CFCOILAC_LUMPR1Y
#define _BRSFC_CV_CFCOILAC_LUMPR1Z
#define _BRSFC_CV_CFCOILAC_LUMPR3X
#define _BRSFC_CV_CFCOILAC_LUMPR3Y
#define _BRSFC_CV_CFCOILAC_LUMPR3Z
#define _BRSFC_CV_CFCOILAC_LUMPR5X
#define _BRSFC_CV_CFCOILAC_LUMPR5Y
#define _BRSFC_CV_CFCOILAC_LUMPR5Z
#define _BRSFC_CV_CFCOILAC_POWER
#define _BRSFC_CV_CFCOILAC_POWER_1AXIS
#define _BRSFC_CV_CFCOILAC_POWER_BURST
#define _BRSFC_CV_CFCOILAC_TEMP_BASE_BURST
#define _BRSFC_CV_CFCOILAC_TEMP_LIMIT_BURST
#define _BRSFC_CV_CFCOILAC_TIMECONSTANT_BURST
#define _BRSFC_CV_CFCOILAC_TIMERES
#define _BRSFC_CV_CFCOILAC_XGAIN
#define _BRSFC_CV_CFCOILAC_YGAIN
#define _BRSFC_CV_CFCOILAC_ZGAIN
#define _BRSFC_CV_CFCOILDC_LX
#define _BRSFC_CV_CFCOILDC_LY
#define _BRSFC_CV_CFCOILDC_LZ
#define _BRSFC_CV_CFCOILDC_RX
#define _BRSFC_CV_CFCOILDC_RY
#define _BRSFC_CV_CFCOILDC_RZ
#define _BRSFC_CV_CFCOILDC_GAIN
#define _BRSFC_CV_CFCOILQAC_A0
#define _BRSFC_CV_CFCOILQAC_A1
#define _BRSFC_CV_CFCOILQAC_A2
#define _BRSFC_CV_CFCOILQAC_A3
#define _BRSFC_CV_CFCOILQAC_A4
#define _BRSFC_CV_CFCOILQAC_A5
#define _BRSFC_CV_CFCOILQAC_A6
#define _BRSFC_CV_CFCOILQAC_XCOEF
#define _BRSFC_CV_CFCOILQAC_YCOEF
#define _BRSFC_CV_CFCOILQAC_ZCOEF
#define _BRSFC_CV_CFCOILQAC_CONST
#define _BRSFC_CV_CFCOILQAC_HEAT_CONST
#define _BRSFC_CV_CFCOILQAC_HEAT_MAXTIME
#define _BRSFC_CV_CFCOILQAC_HEAT_SLOPE
#define _BRSFC_CV_CFCOILQAC_MAXTIME
#define _BRSFC_CV_CFCOILSHLD
#define _BRSFC_CV_CFCOILSWITCHMETHOD
#define _BRSFC_CV_CFCOMPRESS
#define _BRSFC_CV_CFDBDTDX
#define _BRSFC_CV_CFDBDTDY
#define _BRSFC_CV_CFDBDTDZ
#define _BRSFC_CV_CFDBDTPER
#define _BRSFC_CV_CFDBDTPER2
#define _BRSFC_CV_CFDBDTPER_CONT
#define _BRSFC_CV_CFDBDTPER_MAX
#define _BRSFC_CV_CFDBDTPER_NORM
#define _BRSFC_CV_CFDBDTTS
#define _BRSFC_CV_CFDBDTTYPE
#define _BRSFC_CV_CFDBMAX
#define _BRSFC_CV_CFDERATINGFACTORRTSAR
#define _BRSFC_CV_CFDFM
#define _BRSFC_CV_CFDFMDX
#define _BRSFC_CV_CFDFMR1
#define _BRSFC_CV_CFDFMTG
#define _BRSFC_CV_CFDPPERICN
#define _BRSFC_CV_CFFALL2X0
#define _BRSFC_CV_CFFALL2X0FW
#define _BRSFC_CV_CFFALL2Y0
#define _BRSFC_CV_CFFALL2Y0FW
#define _BRSFC_CV_CFFALL2Z0
#define _BRSFC_CV_CFFALL2Z0FW
#define _BRSFC_CV_CFFASTPRESCAN
#define _BRSFC_CV_CFFIELD
#define _BRSFC_CV_CFGBURSTIME
#define _BRSFC_CV_CFGCOILTYPE
#define _BRSFC_CV_CFGCONTIRMS
#define _BRSFC_CV_CFGMAX_ARTHIGH
#define _BRSFC_CV_CFGMAX_ARTMEDIUM
#define _BRSFC_CV_CFGMAX_ARTMEDIUMOPT
#define _BRSFC_CV_CFGOVBODY
#define _BRSFC_CV_CFGPEAKIRMS
#define _BRSFC_CV_CFGPMPOW
#define _BRSFC_CV_CFGRADAMP
#define _BRSFC_CV_CFGRADCOIL
#define _BRSFC_CV_CFH_CRUSHER_AREA
#define _BRSFC_CV_CFH_DDA
#define _BRSFC_CV_CFH_EACH
#define _BRSFC_CV_CFH_EC_POSITION
#define _BRSFC_CV_CFH_FOV
#define _BRSFC_CV_CFH_NEWGEO
#define _BRSFC_CV_CFH_NEWMODE
#define _BRSFC_CV_CFH_NEX
#define _BRSFC_CV_CFH_RF1FREQ
#define _BRSFC_CV_CFH_RF2FREQ
#define _BRSFC_CV_CFH_RF3FREQ
#define _BRSFC_CV_CFH_RF4FREQ
#define _BRSFC_CV_CFH_SLQUANT
#define _BRSFC_CV_CFH_STEAM_FLAG
#define _BRSFC_CV_CFH_TDAQ
#define _BRSFC_CV_CFH_TI
#define _BRSFC_CV_CFH_TR
#define _BRSFC_CV_CFHIR_KILLER_AREA
#define _BRSFC_CV_CFHLLR
#define _BRSFC_CV_CFHLOGGRD
#define _BRSFC_CV_CFHOBL_DEBUG
#define _BRSFC_CV_CFHPDL
#define _BRSFC_CV_CFHPSL
#define _BRSFC_CV_CFHPV
#define _BRSFC_CV_CFHQPC
#define _BRSFC_CV_CFHSCALE
#define _BRSFC_CV_CFHTDEL
#define _BRSFC_CV_CFHWGUT
#define _BRSFC_CV_CFHWRFUT
#define _BRSFC_CV_CFHWSSPUT
#define _BRSFC_CV_CFL_DDA
#define _BRSFC_CV_CFL_NEX
#define _BRSFC_CV_CFL_TDAQ
#define _BRSFC_CV_CFL_TR
#define _BRSFC_CV_CFLCOIL
#define _BRSFC_CV_CFLINFRQ
#define _BRSFC_CV_CFLLOGGRD
#define _BRSFC_CV_CFLOSS
#define _BRSFC_CV_CFLSCALE
#define _BRSFC_CV_CFMAXAVE
#define _BRSFC_CV_CFMAXAVEPM
#define _BRSFC_CV_CFMAXB1REF
#define _BRSFC_CV_CFMAXB1RMSHEAD
#define _BRSFC_CV_CFMAXBW
#define _BRSFC_CV_CFMAXCAVE
#define _BRSFC_CV_CFMAXCPEAK
#define _BRSFC_CV_CFMAXEPEAK
#define _BRSFC_CV_CFMAXEXTREMITY
#define _BRSFC_CV_CFMAXHAVE
#define _BRSFC_CV_CFMAXPEAK
#define _BRSFC_CV_CFMGPS
#define _BRSFC_CV_CFNUMARTLEVELS
#define _BRSFC_CV_CFNUMICN
#define _BRSFC_CV_CFNUMRCVRS
#define _BRSFC_CV_CFOPENMAGNET
#define _BRSFC_CV_CFOPTION
#define _BRSFC_CV_CFPICTURE
#define _BRSFC_CV_CFPMGS
#define _BRSFC_CV_CFPSDGRADDLY
#define _BRSFC_CV_CFPSDRFDLY
#define _BRSFC_CV_CFPSDRFDLYX
#define _BRSFC_CV_CFPSDRFDLYY
#define _BRSFC_CV_CFPSDRFDLYZ
#define _BRSFC_CV_CFPURE_FILTERING_MODE
#define _BRSFC_CV_CFPWRMONREFLMEAS
#define _BRSFC_CV_CFPWRMONTYP
#define _BRSFC_CV_CFRACCOIL
#define _BRSFC_CV_CFRAMPDIR
#define _BRSFC_CV_CFRAMPDIR_TGT
#define _BRSFC_CV_CFRCOIL
#define _BRSFC_CV_CFREALTIME
#define _BRSFC_CV_CFRECEIVEROFFSETFREQ
#define _BRSFC_CV_CFRECEIVERSWITCHTYPE
#define _BRSFC_CV_CFRECEIVERTYPE
#define _BRSFC_CV_CFRECVEND
#define _BRSFC_CV_CFRECVST
#define _BRSFC_CV_CFRFMAXATTENUATION
#define _BRSFC_CV_CFRFACT
#define _BRSFC_CV_CFRFAMPFTCONST
#define _BRSFC_CV_CFRFAMPFTLINEAR
#define _BRSFC_CV_CFRFAMPFTQUADRATIC
#define _BRSFC_CV_CFRFAMPTYP
#define _BRSFC_CV_CFRFBOARDTYPE
#define _BRSFC_CV_CFRFMAPB
#define _BRSFC_CV_CFRFMAPH
#define _BRSFC_CV_CFRFMAPS
#define _BRSFC_CV_CFRFMDCB
#define _BRSFC_CV_CFRFMDCH
#define _BRSFC_CV_CFRFMDCS
#define _BRSFC_CV_CFRFMINBLANK
#define _BRSFC_CV_CFRFMINBLANKTORCV
#define _BRSFC_CV_CFRFMINUNBLK
#define _BRSFC_CV_CFRFMPEB
#define _BRSFC_CV_CFRFMPEH
#define _BRSFC_CV_CFRFMPES
#define _BRSFC_CV_CFRFMPWB
#define _BRSFC_CV_CFRFMPWH
#define _BRSFC_CV_CFRFMPWS
#define _BRSFC_CV_CFRFRAPB
#define _BRSFC_CV_CFRFRAPCW
#define _BRSFC_CV_CFRFRAPH
#define _BRSFC_CV_CFRFRAPS
#define _BRSFC_CV_CFRFUNBLANK
#define _BRSFC_CV_CFRFUPA
#define _BRSFC_CV_CFRFUPD
#define _BRSFC_CV_CFRHR
#define _BRSFC_CV_CFRINF
#define _BRSFC_CV_CFRMP2XFS
#define _BRSFC_CV_CFRMP2XFSFW
#define _BRSFC_CV_CFRMP2YFS
#define _BRSFC_CV_CFRMP2YFSFW
#define _BRSFC_CV_CFRMP2ZFS
#define _BRSFC_CV_CFRMP2ZFSFW
#define _BRSFC_CV_CFSCOUTSCANACT
#define _BRSFC_CV_CFSDLIM
#define _BRSFC_CV_CFSLEW_ARTHIGH
#define _BRSFC_CV_CFSLEW_ARTMEDIUM
#define _BRSFC_CV_CFSLEW_ARTMEDIUMOPT
#define _BRSFC_CV_CFSPECTROPMCAL
#define _BRSFC_CV_CFSRMODE
#define _BRSFC_CV_CFSRMODEACT
#define _BRSFC_CV_CFSRMODECONV
#define _BRSFC_CV_CFSWGUT
#define _BRSFC_CV_CFSWRFUT
#define _BRSFC_CV_CFSWSSPUT
#define _BRSFC_CV_CFSYSTEMMAXFOV
#define _BRSFC_CV_CFTABLEANGLEX
#define _BRSFC_CV_CFTABLEANGLEY
#define _BRSFC_CV_CFTABLEANGLEZ
#define _BRSFC_CV_CFTABLEMAXACCEL
#define _BRSFC_CV_CFTABLEMAXDECEL
#define _BRSFC_CV_CFTABLEMAXSPEED
#define _BRSFC_CV_CFTABLEOFFSETX
#define _BRSFC_CV_CFTABLEOFFSETY
#define _BRSFC_CV_CFTABLEOFFSETZ
#define _BRSFC_CV_CFTPSNPROC
#define _BRSFC_CV_CFTPSPROCTYPE
#define _BRSFC_CV_CFTPSSIZE
#define _BRSFC_CV_CFTRNEW
#define _BRSFC_CV_CFTUNING
#define _BRSFC_CV_CFVHR
#define _BRSFC_CV_CFXAMPTRAN
#define _BRSFC_CV_CFXASM
#define _BRSFC_CV_CFXBETA
#define _BRSFC_CV_CFXCC
#define _BRSFC_CV_CFXFA
#define _BRSFC_CV_CFXFD_POWER_LIMIT
#define _BRSFC_CV_CFXFD_TEMP_LIMIT
#define _BRSFC_CV_CFXFS
#define _BRSFC_CV_CFXFULL
#define _BRSFC_CV_CFXGASM
#define _BRSFC_CV_CFXGD_IGBTTEMPLIMIT
#define _BRSFC_CV_CFXGD_BUSBARTEMPLIMIT
#define _BRSFC_CV_CFXGD_CABLEIRMSLIMIT
#define _BRSFC_CV_CFXGD_CABLEIRMSLIMIT_BURST
#define _BRSFC_CV_CFXGD_CABLETIMECONSTANT_BURST
#define _BRSFC_CV_CFXGD_CHOKEPOWERLIMIT
#define _BRSFC_CV_CFXGD_TIMERES
#define _BRSFC_CV_CFXGRAM
#define _BRSFC_CV_CFXIAVRGABS
#define _BRSFC_CV_CFXIPEAK
#define _BRSFC_CV_CFXIRMS
#define _BRSFC_CV_CFXIRMSNEG
#define _BRSFC_CV_CFXIRMSPOS
#define _BRSFC_CV_CFXMGRAMPOW
#define _BRSFC_CV_CFXNUMPOWER
#define _BRSFC_CV_CFXPS_AVGHVPWRLIMIT
#define _BRSFC_CV_CFXPS_AVGLVPWRLIMIT
#define _BRSFC_CV_CFXPS_AVGPDULIMIT
#define _BRSFC_CV_CFXPWMDC
#define _BRSFC_CV_CFXRDELAY
#define _BRSFC_CV_CFXRSAT
#define _BRSFC_CV_CFXSERIES
#define _BRSFC_CV_CFXVPWM
#define _BRSFC_CV_CFXVSAT
#define _BRSFC_CV_CFYAMPTRAN
#define _BRSFC_CV_CFYASM
#define _BRSFC_CV_CFYBETA
#define _BRSFC_CV_CFYCC
#define _BRSFC_CV_CFYFA
#define _BRSFC_CV_CFYFS
#define _BRSFC_CV_CFYFULL
#define _BRSFC_CV_CFYGASM
#define _BRSFC_CV_CFYGRAM
#define _BRSFC_CV_CFYIAVRGABS
#define _BRSFC_CV_CFYIPEAK
#define _BRSFC_CV_CFYIRMS
#define _BRSFC_CV_CFYIRMSNEG
#define _BRSFC_CV_CFYIRMSPOS
#define _BRSFC_CV_CFYMGRAMPOW
#define _BRSFC_CV_CFYNUMPOWER
#define _BRSFC_CV_CFYPWMDC
#define _BRSFC_CV_CFYRDELAY
#define _BRSFC_CV_CFYRSAT
#define _BRSFC_CV_CFYSERIES
#define _BRSFC_CV_CFYVPWM
#define _BRSFC_CV_CFYVSAT
#define _BRSFC_CV_CFZAMPTRAN
#define _BRSFC_CV_CFZASM
#define _BRSFC_CV_CFZBETA
#define _BRSFC_CV_CFZCC
#define _BRSFC_CV_CFZFA
#define _BRSFC_CV_CFZFS
#define _BRSFC_CV_CFZFULL
#define _BRSFC_CV_CFZGASM
#define _BRSFC_CV_CFZGRAM
#define _BRSFC_CV_CFZIAVRGABS
#define _BRSFC_CV_CFZIPEAK
#define _BRSFC_CV_CFZIRMS
#define _BRSFC_CV_CFZIRMSNEG
#define _BRSFC_CV_CFZIRMSPOS
#define _BRSFC_CV_CFZMGRAMPOW
#define _BRSFC_CV_CFZNUMPOWER
#define _BRSFC_CV_CFZOOMLIM_CTL
#define _BRSFC_CV_CFZOOMLIM_FOV
#define _BRSFC_CV_CFZOOMLIM_OFC
#define _BRSFC_CV_CFZPWMDC
#define _BRSFC_CV_CFZRDELAY
#define _BRSFC_CV_CFZRSAT
#define _BRSFC_CV_CFZSERIES
#define _BRSFC_CV_CFZVPWM
#define _BRSFC_CV_CFZVSAT
#define _BRSFC_CV_CGATE_DDA
#define _BRSFC_CV_CHANNEL_COMBINE_MODE
#define _BRSFC_CV_CHANNEL_COMPRESSION
#define _BRSFC_CV_CHEMFREQ
#define _BRSFC_CV_CHEMSAT_ACQ
#define _BRSFC_CV_CHEMSAT_DDA
#define _BRSFC_CV_CHEMSCALE
#define _BRSFC_CV_CHEMSEQ0
#define _BRSFC_CV_CHEMSEQS
#define _BRSFC_CV_CHKSUM_RAMPDIR
#define _BRSFC_CV_CHKSUM_RAMPDIR_TGT
#define _BRSFC_CV_CHKSUM_RHDACQCTRL
#define _BRSFC_CV_CHKSUM_RHDACQCTRL_VIEW
#define _BRSFC_CV_CHKSUM_SCANINFO
#define _BRSFC_CV_CHKSUM_SCANINFO_VIEW
#define _BRSFC_CV_CHOPLET
#define _BRSFC_CV_CINE3D_ARRLIMIT
#define _BRSFC_CV_CINE3D_FLAG
#define _BRSFC_CV_CINE3D_FULLKVIEWS
#define _BRSFC_CV_CINE3D_FULLKVIEWS_CAL
#define _BRSFC_CV_CINE3D_KTSAMP_MODE
#define _BRSFC_CV_CINE3D_MAXSLQUANT
#define _BRSFC_CV_CINE3D_MINSLQUANT
#define _BRSFC_CV_CINE3D_NUM_SEGS_EST
#define _BRSFC_CV_CINE3D_TARGETEDPHASES_MAX
#define _BRSFC_CV_CINE3D_TOTALVIEWS_EST
#define _BRSFC_CV_CINE3D_YZ_ORDER
#define _BRSFC_CV_CINE_CHOPLET
#define _BRSFC_CV_CINV16_ISO_DELAY
#define _BRSFC_CV_COEFF_PW_TG
#define _BRSFC_CV_COIL_MAP_2_FILTER_WIDTH
#define _BRSFC_CV_COIL_MAP_SMOOTH_FACTOR
#define _BRSFC_CV_COILSW_DATA
#define _BRSFC_CV_COILSW_DS
#define _BRSFC_CV_COILSW_OC
#define _BRSFC_CV_COLL_PREFLS
#define _BRSFC_CV_COMBINED_COIL_MAP_THRES
#define _BRSFC_CV_COMBO_MODE
#define _BRSFC_CV_COMPOSITEON
#define _BRSFC_CV_COMPTIPUPON
#define _BRSFC_CV_CONFIG_UPDATE_MODE
#define _BRSFC_CV_CONT_DEBUG
#define _BRSFC_CV_CONT_FLAG
#define _BRSFC_CV_CORR_FACTOR_X
#define _BRSFC_CV_CORR_FACTOR_Y
#define _BRSFC_CV_CORR_FACTOR_Z
#define _BRSFC_CV_CORR_MODE
#define _BRSFC_CV_CORR_X
#define _BRSFC_CV_CORR_Y
#define _BRSFC_CV_CORR_Z
#define _BRSFC_CV_COUNT_GRD_WAIT
#define _BRSFC_CV_COUNT_RFUPD
#define _BRSFC_CV_CS_FLAG
#define _BRSFC_CV_CS_SAT
#define _BRSFC_CV_CS_SATSTART
#define _BRSFC_CV_CS_SATSTART_MIN
#define _BRSFC_CV_CS_SATTIME
#define _BRSFC_CV_CSAT_RFUPA
#define _BRSFC_CV_CSAT_SYS_TYPE
#define _BRSFC_CV_CSI_GRID_ON
#define _BRSFC_CV_CSW_TIME_SSI
#define _BRSFC_CV_CSW_TR
#define _BRSFC_CV_CSW_WAIT_BEFORE
#define _BRSFC_CV_CSW_WAIT_SETHUBINDEXIMM
#define _BRSFC_CV_CSW_WAIT_SETRCVPORTIMM
#define _BRSFC_CV_CSWEIGHT
#define _BRSFC_CV_CSXKILLERFLAG
#define _BRSFC_CV_CSZKILLERFLAG
#define _BRSFC_CV_CURR_EFF
#define _BRSFC_CV_CUTCORNER_FLAG
#define _BRSFC_CV_CUTPOSTLOBES
#define _BRSFC_CV_CV_RFUPA
#define _BRSFC_CV_CVLOCK
#define _BRSFC_CV_CYC_RF0
#define _BRSFC_CV_CYC_RF0CFH
#define _BRSFC_CV_CYC_RF1
#define _BRSFC_CV_CYC_RF1_PRE
#define _BRSFC_CV_CYC_RF1_TEMP
#define _BRSFC_CV_CYC_RF1AS
#define _BRSFC_CV_CYC_RF1CFH
#define _BRSFC_CV_CYC_RF1CFL
#define _BRSFC_CV_CYC_RF1DTG
#define _BRSFC_CV_CYC_RF1FTG
#define _BRSFC_CV_CYC_RF1HTR
#define _BRSFC_CV_CYC_RF1MON
#define _BRSFC_CV_CYC_RF1MPS1
#define _BRSFC_CV_CYC_RF1RS
#define _BRSFC_CV_CYC_RF1TM
#define _BRSFC_CV_CYC_RF1XTG
#define _BRSFC_CV_CYC_RF2
#define _BRSFC_CV_CYC_RF2CFH
#define _BRSFC_CV_CYC_RF2FTG
#define _BRSFC_CV_CYC_RF2MON
#define _BRSFC_CV_CYC_RF2MPS1
#define _BRSFC_CV_CYC_RF2XTG
#define _BRSFC_CV_CYC_RF3CFH
#define _BRSFC_CV_CYC_RF3FTG
#define _BRSFC_CV_CYC_RF4CFH
#define _BRSFC_CV_CYC_RFCSSAT
#define _BRSFC_CV_CYC_RFFRIR
#define _BRSFC_CV_CYC_RFGIR01
#define _BRSFC_CV_CYC_RFGIR02
#define _BRSFC_CV_CYC_RFMONTIPUP
#define _BRSFC_CV_CYC_RFS
#define _BRSFC_CV_CYC_RFSE1
#define _BRSFC_CV_CYC_RFSE2
#define _BRSFC_CV_CYC_RFSE3
#define _BRSFC_CV_CYC_RFSE4
#define _BRSFC_CV_CYC_RFSE5
#define _BRSFC_CV_CYC_RFSE6
#define _BRSFC_CV_CYC_RFSX1
#define _BRSFC_CV_CYC_RFSX2
#define _BRSFC_CV_CYC_RFSY1
#define _BRSFC_CV_CYC_RFSY2
#define _BRSFC_CV_CYC_RFSZ1
#define _BRSFC_CV_CYC_RFSZ2
#define _BRSFC_CV_CYLR_DTHETA
#define _BRSFC_CV_CYLR_MANOFF
#define _BRSFC_CV_CYLR_RF_TYPE
#define _BRSFC_CV_CYLR_SKEW
#define _BRSFC_CV_CYLR_XOFF
#define _BRSFC_CV_CYLR_YOFF
#define _BRSFC_CV_D3DTR
#define _BRSFC_CV_DAB_OFFSET
#define _BRSFC_CV_DAB_PACKET
#define _BRSFC_CV_DABOUT_LENGTH
#define _BRSFC_CV_DATA_TYPE
#define _BRSFC_CV_DBDT_DEBUG
#define _BRSFC_CV_DBDT_DISABLE
#define _BRSFC_CV_DBDT_MODE
#define _BRSFC_CV_DBDT_OPTION_KEY_STATUS
#define _BRSFC_CV_DBDTLEVEL_OPT
#define _BRSFC_CV_DDA
#define _BRSFC_CV_DDA_DELAY
#define _BRSFC_CV_DDA_ONE_SECOND
#define _BRSFC_CV_DDA_TRIGGER_DELAY_DISDAQS
#define _BRSFC_CV_DDA_TRIGGER_DELAY_SILENT_COUNTDOWN
#define _BRSFC_CV_DE3D_FLAG
#define _BRSFC_CV_DEBUG
#define _BRSFC_CV_DEBUG_CARD_SIM
#define _BRSFC_CV_DEBUG_DBDT
#define _BRSFC_CV_DEBUG_GIR
#define _BRSFC_CV_DEBUG_GRAD_SPEC
#define _BRSFC_CV_DEBUG_MONLOC
#define _BRSFC_CV_DEBUG_MONROT
#define _BRSFC_CV_DEBUG_MONROTPHI
#define _BRSFC_CV_DEBUG_NAV
#define _BRSFC_CV_DEBUG_ORDER
#define _BRSFC_CV_DEBUG_SCALE
#define _BRSFC_CV_DEBUG_SCAN
#define _BRSFC_CV_DEBUG_SHIMVOL_SLICE
#define _BRSFC_CV_DEBUG_SP_AGP
#define _BRSFC_CV_DEBUG_SP_RTP
#define _BRSFC_CV_DEBUG_TDEL
#define _BRSFC_CV_DEBUG_VIEWTAB
#define _BRSFC_CV_DECIMATION
#define _BRSFC_CV_DELAY3DRECON_FLAG
#define _BRSFC_CV_DELAY_DDA
#define _BRSFC_CV_DELAY_EC_FLAG
#define _BRSFC_CV_DELAY_EC_FRAMES
#define _BRSFC_CV_DELAY_EC_PERIOD
#define _BRSFC_CV_DELAY_QUIET_DDA
#define _BRSFC_CV_DELAY_QUIET_TIME
#define _BRSFC_CV_DELAY_RFHUBSEL
#define _BRSFC_CV_DELTF
#define _BRSFC_CV_DERATE_ACGD
#define _BRSFC_CV_DERATE_GXWEX
#define _BRSFC_CV_DERATEB1_NV_FACTOR
#define _BRSFC_CV_DERATEB1_BODY_FACTOR
#define _BRSFC_CV_DERATEB1_DEFAULT
#define _BRSFC_CV_DERATEB1_DIR
#define _BRSFC_CV_DERATEB1_MIN
#define _BRSFC_CV_DERATEB1_NONITEROPT
#define _BRSFC_CV_DERATEB1_OPT
#define _BRSFC_CV_DETECTOR_MODE
#define _BRSFC_CV_DEX
#define _BRSFC_CV_DF
#define _BRSFC_CV_DFG
#define _BRSFC_CV_DFSCALE
#define _BRSFC_CV_DISABLE_EXCITER_UNBLANK
#define _BRSFC_CV_DISCO_1ECHO_FLAG
#define _BRSFC_CV_DISCO_FLAG
#define _BRSFC_CV_DISCO_NPHASES
#define _BRSFC_CV_DISCODDA
#define _BRSFC_CV_DISCRETIONARYB1RMS
#define _BRSFC_CV_DISCRETIONARYPEAKB1
#define _BRSFC_CV_DISCRETIONARYAVE
#define _BRSFC_CV_DISCRETIONARYHAVE
#define _BRSFC_CV_DITHER_ON
#define _BRSFC_CV_DITHER_VALUE
#define _BRSFC_CV_DIX_FREQ
#define _BRSFC_CV_DIX_TIMEAS
#define _BRSFC_CV_DNAV_WIN_BARATIO
#define _BRSFC_CV_DO_MAXRBW_CHECK_IN_CVEVAL
#define _BRSFC_CV_DOBASELINES
#define _BRSFC_CV_DTG_DDA
#define _BRSFC_CV_DTG_ESP
#define _BRSFC_CV_DTG_ISO_DELAY
#define _BRSFC_CV_DTG_OFF90
#define _BRSFC_CV_DTGLOGGRD
#define _BRSFC_CV_DTGPHORDER
#define _BRSFC_CV_DTGSPGR_FLAG
#define _BRSFC_CV_DTGT_EXA
#define _BRSFC_CV_DTGT_EXB
#define _BRSFC_CV_DTI_PLUS_FLAG
#define _BRSFC_CV_DUMMY_PW
#define _BRSFC_CV_DUMMYRF_SSITIME
#define _BRSFC_CV_DUMMYRF_TIME
#define _BRSFC_CV_DUMP_CHANNEL_COMP_OPTIMAL_RECON
#define _BRSFC_CV_DUTYCYCLE_SCALE
#define _BRSFC_CV_DYNTG_B1FACTOR
#define _BRSFC_CV_DYNTG_BASELINE
#define _BRSFC_CV_DYNTG_ETL
#define _BRSFC_CV_DYNTG_FLIPANGLE
#define _BRSFC_CV_DYNTG_FOV
#define _BRSFC_CV_DYNTG_PTSIZE
#define _BRSFC_CV_DYNTG_SLQUANT
#define _BRSFC_CV_DYNTG_SLTHICK
#define _BRSFC_CV_DYNTG_XRES
#define _BRSFC_CV_DYNTG_YRES
#define _BRSFC_CV_E2_DELAY_DTG
#define _BRSFC_CV_E2_DELAY_RS
#define _BRSFC_CV_EC3_ITERATION_METHOD
#define _BRSFC_CV_EC3_ITERATIONS
#define _BRSFC_CV_ECG_CONT_DDA_FLAG
#define _BRSFC_CV_ECG_DDA
#define _BRSFC_CV_ECG_DDA_DELAY
#define _BRSFC_CV_ECHO1BW
#define _BRSFC_CV_ECHO1BWAS
#define _BRSFC_CV_ECHO1BWCFH
#define _BRSFC_CV_ECHO1BWCFL
#define _BRSFC_CV_ECHO1BWDTG
#define _BRSFC_CV_ECHO1BWRCVN
#define _BRSFC_CV_ECHO1BWRS
#define _BRSFC_CV_ECHO1MONBW
#define _BRSFC_CV_ECHO2BW
#define _BRSFC_CV_ECHO_SORT_DIR
#define _BRSFC_CV_ECHOINT
#define _BRSFC_CV_EEFF
#define _BRSFC_CV_EEPF
#define _BRSFC_CV_EFF_CFH_TE
#define _BRSFC_CV_EG_PHASERES
#define _BRSFC_CV_ELAVA_FLAG
#define _BRSFC_CV_ELLIPT_DEBUG_FILES
#define _BRSFC_CV_ELLIPT_FLAG
#define _BRSFC_CV_ENABLE_ALPHA
#define _BRSFC_CV_ENABLE_SBM
#define _BRSFC_CV_ENABLFRACDEC
#define _BRSFC_CV_ENCODE
#define _BRSFC_CV_ENCODE2
#define _BRSFC_CV_ENCODE_GROUP
#define _BRSFC_CV_END_GYCYLRA
#define _BRSFC_CV_END_GYCYLRATIPUP
#define _BRSFC_CV_END_GZCYLRA
#define _BRSFC_CV_END_GZCYLRATIPUP
#define _BRSFC_CV_END_SEGMENT_DELAY
#define _BRSFC_CV_ENDVIEW_IAMP
#define _BRSFC_CV_ENDVIEW_IAMPAS
#define _BRSFC_CV_ENDVIEW_IAMPDTG
#define _BRSFC_CV_ENDVIEW_IAMPRS
#define _BRSFC_CV_ENDVIEW_SCALE
#define _BRSFC_CV_ENDVIEW_SCALEAS
#define _BRSFC_CV_ENDVIEW_SCALEDTG
#define _BRSFC_CV_ENDVIEW_SCALERS
#define _BRSFC_CV_ENDVIEWZ_IAMP
#define _BRSFC_CV_ENDVIEWZ_SCALE
#define _BRSFC_CV_ENFORCE_CAL_FOR_CHANNEL_COMBINE
#define _BRSFC_CV_ENFORCE_DBDTOPT
#define _BRSFC_CV_ENFORCE_INRANGETR
#define _BRSFC_CV_ENFORCE_MINSEQSEG
#define _BRSFC_CV_ENHANCED_NAV_FLAG
#define _BRSFC_CV_EPI_IR_ON
#define _BRSFC_CV_EQUANT
#define _BRSFC_CV_ESP
#define _BRSFC_CV_ESP_MSDE
#define _BRSFC_CV_ETHICK
#define _BRSFC_CV_EXNEX
#define _BRSFC_CV_EXSAT1_DIST
#define _BRSFC_CV_EXSAT1_NORMTH_A
#define _BRSFC_CV_EXSAT1_NORMTH_R
#define _BRSFC_CV_EXSAT1_NORMTH_S
#define _BRSFC_CV_EXSAT2_DIST
#define _BRSFC_CV_EXSAT2_NORMTH_A
#define _BRSFC_CV_EXSAT2_NORMTH_R
#define _BRSFC_CV_EXSAT2_NORMTH_S
#define _BRSFC_CV_EXSAT3_DIST
#define _BRSFC_CV_EXSAT3_NORMTH_A
#define _BRSFC_CV_EXSAT3_NORMTH_R
#define _BRSFC_CV_EXSAT3_NORMTH_S
#define _BRSFC_CV_EXSAT4_DIST
#define _BRSFC_CV_EXSAT4_NORMTH_A
#define _BRSFC_CV_EXSAT4_NORMTH_R
#define _BRSFC_CV_EXSAT4_NORMTH_S
#define _BRSFC_CV_EXSAT5_DIST
#define _BRSFC_CV_EXSAT5_NORMTH_A
#define _BRSFC_CV_EXSAT5_NORMTH_R
#define _BRSFC_CV_EXSAT5_NORMTH_S
#define _BRSFC_CV_EXSAT6_DIST
#define _BRSFC_CV_EXSAT6_NORMTH_A
#define _BRSFC_CV_EXSAT6_NORMTH_R
#define _BRSFC_CV_EXSAT6_NORMTH_S
#define _BRSFC_CV_EXSATTHICK1
#define _BRSFC_CV_EXSATTHICK2
#define _BRSFC_CV_EXSATTHICK3
#define _BRSFC_CV_EXSATTHICK4
#define _BRSFC_CV_EXSATTHICK5
#define _BRSFC_CV_EXSATTHICK6
#define _BRSFC_CV_EXTRARRLIMIT
#define _BRSFC_CV_EXTRASCALE
#define _BRSFC_CV_EXTRAS
#define _BRSFC_CV_EXTRASPECIAL_FLAG
#define _BRSFC_CV_EXTRASPECIAL_SEQ_ORDER_FLAG
#define _BRSFC_CV_FA_SCALE_DEBUG
#define _BRSFC_CV_FAST_XTR
#define _BRSFC_CV_FASTPRESCAN
#define _BRSFC_CV_FATFLAG
#define _BRSFC_CV_FATT1
#define _BRSFC_CV_FAT_DELTA
#define _BRSFC_CV_FAT_FLAG
#define _BRSFC_CV_FAT_OFFSET
#define _BRSFC_CV_FATKILLER_FLAG
#define _BRSFC_CV_FC_DEBUG
#define _BRSFC_CV_FCINEIM
#define _BRSFC_CV_FCINENT
#define _BRSFC_CV_FECHO_FACTOR
#define _BRSFC_CV_FERMI_R_FACTOR
#define _BRSFC_CV_FERMI_RC
#define _BRSFC_CV_FERMI_W_FACTOR
#define _BRSFC_CV_FERMI_WC
#define _BRSFC_CV_FERMR_COEF_1024
#define _BRSFC_CV_FF4ERROR
#define _BRSFC_CV_FIELD_STRENGTH
#define _BRSFC_CV_FIELDSTRENGTH
#define _BRSFC_CV_FIESTA_GATED_DDA
#define _BRSFC_CV_FIESTA_GATED_FLAT_DDA
#define _BRSFC_CV_FIESTA_GATED_RAMP_DDA
#define _BRSFC_CV_FIESTA_GATED_RAMP_DOWN
#define _BRSFC_CV_FIESTA_KILLER_FLAG
#define _BRSFC_CV_FIESTA_RAMPUP_TYPE
#define _BRSFC_CV_FILTER_CFH_FID
#define _BRSFC_CV_FILTER_CFL_FID
#define _BRSFC_CV_FILTER_ECHO1
#define _BRSFC_CV_FILTER_ECHO1AS
#define _BRSFC_CV_FILTER_ECHO1DTG
#define _BRSFC_CV_FILTER_ECHO1FTG
#define _BRSFC_CV_FILTER_ECHO1MON
#define _BRSFC_CV_FILTER_ECHO1MPS1
#define _BRSFC_CV_FILTER_ECHO1RS
#define _BRSFC_CV_FILTER_ECHO1TM
#define _BRSFC_CV_FILTER_ECHO1XTG
#define _BRSFC_CV_FILTER_ECHO2
#define _BRSFC_CV_FILTER_ECHO2FTG
#define _BRSFC_CV_FILTER_RCVN_FID
#define _BRSFC_CV_FILTERSLOT1
#define _BRSFC_CV_FILTERSLOT2
#define _BRSFC_CV_FIRSTSERIESFLAG
#define _BRSFC_CV_FIRST_PREPSCAN
#define _BRSFC_CV_FIRST_SCAN
#define _BRSFC_CV_FIX_FERMI
#define _BRSFC_CV_FL_WIDTH_X_FRAC
#define _BRSFC_CV_FL_WIDTH_X_FULL
#define _BRSFC_CV_FLEXTE_FLAG
#define _BRSFC_CV_FLEXTR_FLAG
#define _BRSFC_CV_FLIP_HARD180
#define _BRSFC_CV_FLIP_PCTAS
#define _BRSFC_CV_FLIP_RF0
#define _BRSFC_CV_FLIP_RF0CFH
#define _BRSFC_CV_FLIP_RF1
#define _BRSFC_CV_FLIP_RF180
#define _BRSFC_CV_FLIP_RF1AS
#define _BRSFC_CV_FLIP_RF1CFH
#define _BRSFC_CV_FLIP_RF1CFL
#define _BRSFC_CV_FLIP_RF1DTG
#define _BRSFC_CV_FLIP_RF1FTG
#define _BRSFC_CV_FLIP_RF1MON
#define _BRSFC_CV_FLIP_RF1MPS1
#define _BRSFC_CV_FLIP_RF1RS
#define _BRSFC_CV_FLIP_RF1TM
#define _BRSFC_CV_FLIP_RF1XTG
#define _BRSFC_CV_FLIP_RF2CFH
#define _BRSFC_CV_FLIP_RF2FTG
#define _BRSFC_CV_FLIP_RF2MON
#define _BRSFC_CV_FLIP_RF2MPS1
#define _BRSFC_CV_FLIP_RF2XTG
#define _BRSFC_CV_FLIP_RF3CFH
#define _BRSFC_CV_FLIP_RF3FTG
#define _BRSFC_CV_FLIP_RF3XTG
#define _BRSFC_CV_FLIP_RF4CFH
#define _BRSFC_CV_FLIP_RF4XTG
#define _BRSFC_CV_FLIP_RF90
#define _BRSFC_CV_FLIP_RFBDTG
#define _BRSFC_CV_FLIP_RFBRS
#define _BRSFC_CV_FLIP_RFCSSAT
#define _BRSFC_CV_FLIP_RFCSSAT_NOSCALE
#define _BRSFC_CV_FLIP_RFCSSATCFH
#define _BRSFC_CV_FLIP_RFCYLR
#define _BRSFC_CV_FLIP_RFCYLR_NAVSAT
#define _BRSFC_CV_FLIP_RFCYLRTIPUP
#define _BRSFC_CV_FLIP_RFFLP180
#define _BRSFC_CV_FLIP_RFFLP90
#define _BRSFC_CV_FLIP_RFFLP90R
#define _BRSFC_CV_FLIP_RFFRIR
#define _BRSFC_CV_FLIP_RFFS
#define _BRSFC_CV_FLIP_RFGIR01
#define _BRSFC_CV_FLIP_RFGIR02
#define _BRSFC_CV_FLIP_RFMON_NAVSAT
#define _BRSFC_CV_FLIP_RFMONTIPUP
#define _BRSFC_CV_FLIP_RFS5FPH
#define _BRSFC_CV_FLIP_RFSE1
#define _BRSFC_CV_FLIP_RFSE2
#define _BRSFC_CV_FLIP_RFSE3
#define _BRSFC_CV_FLIP_RFSE4
#define _BRSFC_CV_FLIP_RFSE5
#define _BRSFC_CV_FLIP_RFSE6
#define _BRSFC_CV_FLIP_RFSSF
#define _BRSFC_CV_FLIP_RFSSFH
#define _BRSFC_CV_FLIP_RFSX1
#define _BRSFC_CV_FLIP_RFSX2
#define _BRSFC_CV_FLIP_RFSY1
#define _BRSFC_CV_FLIP_RFSY2
#define _BRSFC_CV_FLIP_RFSZ1
#define _BRSFC_CV_FLIP_RFSZ2
#define _BRSFC_CV_FLIP_RFTIPUP
#define _BRSFC_CV_FLOW4D_FLAG
#define _BRSFC_CV_FLOW_COMP_TYPE
#define _BRSFC_CV_FLOW_WDTH_X
#define _BRSFC_CV_FLOW_WDTH_Y
#define _BRSFC_CV_FLOW_WDTH_Z
#define _BRSFC_CV_FLOWPOS1X
#define _BRSFC_CV_FLOWPOS1Y
#define _BRSFC_CV_FLOWPOS1Z
#define _BRSFC_CV_FLOWPOS2X
#define _BRSFC_CV_FLOWPOS2Y
#define _BRSFC_CV_FLOWPOS2Z
#define _BRSFC_CV_FN
#define _BRSFC_CV_FNECHO_FRAC
#define _BRSFC_CV_FNECHO_LIM
#define _BRSFC_CV_FORCE_GRADOPT_LOOP_BREAK
#define _BRSFC_CV_FOV_ADVISORY_IGNORE_MSLICES
#define _BRSFC_CV_FOV_FACTOR
#define _BRSFC_CV_FOV_FREQ_SCALE
#define _BRSFC_CV_FOV_LIM_MPS
#define _BRSFC_CV_FOV_PHASE_SCALE
#define _BRSFC_CV_FOV_SCALING
#define _BRSFC_CV_FRAC_RF
#define _BRSFC_CV_FRACT_ECHO_ANNEFACT_REDUCTION
#define _BRSFC_CV_FREQSIGN
#define _BRSFC_CV_FREQ_SCALE
#define _BRSFC_CV_FS_2PI
#define _BRSFC_CV_FS_PCFIESTA_FLAG
#define _BRSFC_CV_FS_PI
#define _BRSFC_CV_FTG_DDA
#define _BRSFC_CV_FTGSCALE
#define _BRSFC_CV_FTGTR
#define _BRSFC_CV_FTMRA_DEBUG
#define _BRSFC_CV_FTMRA_DFSAT_FLAG
#define _BRSFC_CV_FTMRA_ENABLE_FLAG
#define _BRSFC_CV_FTMRA_EXSAT_FLAG
#define _BRSFC_CV_FTMRA_FLAG
#define _BRSFC_CV_FTMRA_HARD180_ACT
#define _BRSFC_CV_FTMRA_SAT_FLAG
#define _BRSFC_CV_FULLTE_FLAG
#define _BRSFC_CV_GATED_DDA
#define _BRSFC_CV_GATING
#define _BRSFC_CV_GENVIEW_ELLIPT_CAL
#define _BRSFC_CV_GENVIEW_FOVVTHICK_SCALE
#define _BRSFC_CV_GENVIEW_MAXAPHASE
#define _BRSFC_CV_GENVIEW_TOTALVIEWS
#define _BRSFC_CV_GET_FULLECHO
#define _BRSFC_CV_GIR_NEWGEO
#define _BRSFC_CV_GIR_OBL_DEBUG
#define _BRSFC_CV_GIR_RFISO1
#define _BRSFC_CV_GIR_RFISO2
#define _BRSFC_CV_GIR_START
#define _BRSFC_CV_GIR_TD0
#define _BRSFC_CV_GIR_TIME
#define _BRSFC_CV_GIR_TIME_DAQ
#define _BRSFC_CV_GIR_TIME_EVAL
#define _BRSFC_CV_GIRLOGGRD
#define _BRSFC_CV_GLDELAYF
#define _BRSFC_CV_GLIMIT
#define _BRSFC_CV_GLIMIT_X
#define _BRSFC_CV_GLIMIT_Y
#define _BRSFC_CV_GLIMIT_Z
#define _BRSFC_CV_GOLDEN_RATIO_FLAG
#define _BRSFC_CV_GRADCHOKEFLAG
#define _BRSFC_CV_GRADCOILMETHOD
#define _BRSFC_CV_GRADDCSAFEMETHOD
#define _BRSFC_CV_GRADDRIVERMETHOD
#define _BRSFC_CV_GRADHEATFILE
#define _BRSFC_CV_GRADHEATFLAG
#define _BRSFC_CV_GRADHEATMETHOD
#define _BRSFC_CV_GRADOPT_GX2
#define _BRSFC_CV_GRADOPT_PITER_COUNT
#define _BRSFC_CV_GRADOPT_PTOR
#define _BRSFC_CV_GRADOPT_PWEIGHT
#define _BRSFC_CV_GRADOPT_TE
#define _BRSFC_CV_GRADOPT_TEFACTOR
#define _BRSFC_CV_GRADOPT_TEFACTOR_MAX
#define _BRSFC_CV_GRADOPT_TEFACTOR_MIN
#define _BRSFC_CV_GRADOPT_TRFACTOR
#define _BRSFC_CV_GRADOPT_TRFACTOR_MAX
#define _BRSFC_CV_GRADOPT_TRFACTOR_MIN
#define _BRSFC_CV_GRADOPT_ATETR_METHOD
#define _BRSFC_CV_GRADOPT_CONVERGENCE_FLAG
#define _BRSFC_CV_GRADOPT_FLAG
#define _BRSFC_CV_GRADOPT_ITER_COUNT
#define _BRSFC_CV_GRADOPT_NONCONV_TOR
#define _BRSFC_CV_GRADOPT_NONCONV_TOR_LIMIT
#define _BRSFC_CV_GRADOPT_POWEROPT_FLAG
#define _BRSFC_CV_GRADOPT_POWERTE
#define _BRSFC_CV_GRADOPT_POWERTR
#define _BRSFC_CV_GRADOPT_RATIO
#define _BRSFC_CV_GRADOPT_RUN_FLAG
#define _BRSFC_CV_GRADOPT_SCALE
#define _BRSFC_CV_GRADOPT_SCALE_MAX
#define _BRSFC_CV_GRADOPT_SCALE_MIN
#define _BRSFC_CV_GRADOPT_SLEWRATE
#define _BRSFC_CV_GRADOPT_SLEWRATE_LIMIT
#define _BRSFC_CV_GRADOPT_SLEWRATE_TMP
#define _BRSFC_CV_GRADOPT_TOR
#define _BRSFC_CV_GRADOPT_WEIGHT
#define _BRSFC_CV_GRAD_INTENSITY_THRES
#define _BRSFC_CV_GRAD_SPEC_CHANGE_FLAG
#define _BRSFC_CV_GRAD_SPEC_CTRL
#define _BRSFC_CV_GRADIENT_MODE
#define _BRSFC_CV_GRID_FOV_FACTOR
#define _BRSFC_CV_GSAT_SCALE
#define _BRSFC_CV_GSCALE_HARD180
#define _BRSFC_CV_GSCALE_KILL
#define _BRSFC_CV_GSCALE_OMEGA_HS_RFCSSAT
#define _BRSFC_CV_GSCALE_OMEGA_IR0
#define _BRSFC_CV_GSCALE_OMEGA_RFFRIR
#define _BRSFC_CV_GSCALE_OMEGA_RFGIR01
#define _BRSFC_CV_GSCALE_OMEGA_RFGIR02
#define _BRSFC_CV_GSCALE_OMEGARF0CFH
#define _BRSFC_CV_GSCALE_RF0
#define _BRSFC_CV_GSCALE_RF0CFH
#define _BRSFC_CV_GSCALE_RF1
#define _BRSFC_CV_GSCALE_RF1AS
#define _BRSFC_CV_GSCALE_RF1CFH
#define _BRSFC_CV_GSCALE_RF1CFL
#define _BRSFC_CV_GSCALE_RF1DTG
#define _BRSFC_CV_GSCALE_RF1FTG
#define _BRSFC_CV_GSCALE_RF1MON
#define _BRSFC_CV_GSCALE_RF1MPS1
#define _BRSFC_CV_GSCALE_RF1RS
#define _BRSFC_CV_GSCALE_RF1TM
#define _BRSFC_CV_GSCALE_RF1XTG
#define _BRSFC_CV_GSCALE_RF2FTG
#define _BRSFC_CV_GSCALE_RF2MON
#define _BRSFC_CV_GSCALE_RF2MPS1
#define _BRSFC_CV_GSCALE_RF2XTG
#define _BRSFC_CV_GSCALE_RF3FTG
#define _BRSFC_CV_GSCALE_RF3XTG
#define _BRSFC_CV_GSCALE_RF4XTG
#define _BRSFC_CV_GSCALE_RF90
#define _BRSFC_CV_GSCALE_RFCSSAT
#define _BRSFC_CV_GSCALE_RFFLP180
#define _BRSFC_CV_GSCALE_RFFLP180_THE
#define _BRSFC_CV_GSCALE_RFFLP90
#define _BRSFC_CV_GSCALE_RFFLP90_THE
#define _BRSFC_CV_GSCALE_RFFLP90R
#define _BRSFC_CV_GSCALE_RFFLP90R_THE
#define _BRSFC_CV_GSCALE_RFFRIR
#define _BRSFC_CV_GSCALE_RFGIR01
#define _BRSFC_CV_GSCALE_RFGIR02
#define _BRSFC_CV_GSCALE_RFMONTIPUP
#define _BRSFC_CV_GSCALE_RFSE1
#define _BRSFC_CV_GSCALE_RFSE2
#define _BRSFC_CV_GSCALE_RFSE3
#define _BRSFC_CV_GSCALE_RFSE4
#define _BRSFC_CV_GSCALE_RFSE5
#define _BRSFC_CV_GSCALE_RFSE6
#define _BRSFC_CV_GSCALE_RFSX1
#define _BRSFC_CV_GSCALE_RFSX2
#define _BRSFC_CV_GSCALE_RFSY1
#define _BRSFC_CV_GSCALE_RFSY2
#define _BRSFC_CV_GSCALE_RFSZ1
#define _BRSFC_CV_GSCALE_RFSZ2
#define _BRSFC_CV_GSCALE_RFTIPUP
#define _BRSFC_CV_GXFCTARGET
#define _BRSFC_CV_GXWEX_BRIDGE
#define _BRSFC_CV_GXWEX_ON
#define _BRSFC_CV_GXWEX_TARGET
#define _BRSFC_CV_GXWEX_TARGET_HFDSLITE
#define _BRSFC_CV_GXWEX_TARGET_HFDSLITE_VALUE_3DDE
#define _BRSFC_CV_GYFCTARGET
#define _BRSFC_CV_GYKCS_MAX
#define _BRSFC_CV_GZ1_FIRST_MOMENT
#define _BRSFC_CV_GZ1_ZERO_MOMENT
#define _BRSFC_CV_GZ_TIME
#define _BRSFC_CV_GZFCTARGET
#define _BRSFC_CV_GZPTIME
#define _BRSFC_CV_GZTYPE
#define _BRSFC_CV_HAD_SAT
#define _BRSFC_CV_HARD180TIME
#define _BRSFC_CV_HEADNECK_POS_SCAN
#define _BRSFC_CV_HEART3D_FLAG
#define _BRSFC_CV_HIGHER_DBDT_FLAG
#define _BRSFC_CV_HIRES_RECON
#define _BRSFC_CV_HIST_WAIT_TIME
#define _BRSFC_CV_HRF1A
#define _BRSFC_CV_HRF1B
#define _BRSFC_CV_HST_FLAG
#define _BRSFC_CV_HST_LENGTH
#define _BRSFC_CV_IA_CINE3D
#define _BRSFC_CV_IA_COILSW_OFF
#define _BRSFC_CV_IA_COILSW_ON
#define _BRSFC_CV_IA_CONTRFHUBSEL
#define _BRSFC_CV_IA_CONTRFSEL
#define _BRSFC_CV_IA_DDDIQ
#define _BRSFC_CV_IA_DDPHASE
#define _BRSFC_CV_IA_DE
#define _BRSFC_CV_IA_DTREG
#define _BRSFC_CV_IA_DTREGPASS
#define _BRSFC_CV_IA_ENDGYCYLRA
#define _BRSFC_CV_IA_ENDGYCYLRATIPUP
#define _BRSFC_CV_IA_ENDGZCYLRA
#define _BRSFC_CV_IA_ENDGZCYLRATIPUP
#define _BRSFC_CV_IA_GX1
#define _BRSFC_CV_IA_GX1AS
#define _BRSFC_CV_IA_GX1BFTG
#define _BRSFC_CV_IA_GX1BXTG
#define _BRSFC_CV_IA_GX1CFH
#define _BRSFC_CV_IA_GX1D
#define _BRSFC_CV_IA_GX1DTG
#define _BRSFC_CV_IA_GX1FED
#define _BRSFC_CV_IA_GX1FEN
#define _BRSFC_CV_IA_GX1FEU
#define _BRSFC_CV_IA_GX1FTG
#define _BRSFC_CV_IA_GX1MON
#define _BRSFC_CV_IA_GX1MPS1
#define _BRSFC_CV_IA_GX1RS
#define _BRSFC_CV_IA_GX1TM
#define _BRSFC_CV_IA_GX1U
#define _BRSFC_CV_IA_GX1WA
#define _BRSFC_CV_IA_GX1WB
#define _BRSFC_CV_IA_GX2
#define _BRSFC_CV_IA_GX2DTG
#define _BRSFC_CV_IA_GX2FED
#define _BRSFC_CV_IA_GX2FEN
#define _BRSFC_CV_IA_GX2FEU
#define _BRSFC_CV_IA_GX2FTG
#define _BRSFC_CV_IA_GX2RS
#define _BRSFC_CV_IA_GX2TEST
#define _BRSFC_CV_IA_GXB
#define _BRSFC_CV_IA_GXBRSFC1
#define _BRSFC_CV_IA_GXBRSFC2
#define _BRSFC_CV_IA_GXFC
#define _BRSFC_CV_IA_GXFCD
#define _BRSFC_CV_IA_GXFCMON
#define _BRSFC_CV_IA_GXFCU
#define _BRSFC_CV_IA_GXFLPK
#define _BRSFC_CV_IA_GXFLPKWA
#define _BRSFC_CV_IA_GXFLPKWB
#define _BRSFC_CV_IA_GXFLPVENC
#define _BRSFC_CV_IA_GXFLPVENCWA
#define _BRSFC_CV_IA_GXFLPVENCWB
#define _BRSFC_CV_IA_GXHYST1
#define _BRSFC_CV_IA_GXHYST2
#define _BRSFC_CV_IA_GXKAS
#define _BRSFC_CV_IA_GXKBSDTG
#define _BRSFC_CV_IA_GXKBSRS
#define _BRSFC_CV_IA_GXKCS
#define _BRSFC_CV_IA_GXKDTG
#define _BRSFC_CV_IA_GXKFS
#define _BRSFC_CV_IA_GXKILL
#define _BRSFC_CV_IA_GXKRCVN
#define _BRSFC_CV_IA_GXKRS
#define _BRSFC_CV_IA_GXKS
#define _BRSFC_CV_IA_GXKSE1
#define _BRSFC_CV_IA_GXKSE2
#define _BRSFC_CV_IA_GXKSE3
#define _BRSFC_CV_IA_GXKSE4
#define _BRSFC_CV_IA_GXKSE5
#define _BRSFC_CV_IA_GXKSE6
#define _BRSFC_CV_IA_GXKSP
#define _BRSFC_CV_IA_GXKSSF
#define _BRSFC_CV_IA_GXKSX1
#define _BRSFC_CV_IA_GXKSX2
#define _BRSFC_CV_IA_GXKSY1
#define _BRSFC_CV_IA_GXKSY2
#define _BRSFC_CV_IA_GXKSZ1
#define _BRSFC_CV_IA_GXKSZ2
#define _BRSFC_CV_IA_GXRF1TM
#define _BRSFC_CV_IA_GXRF2CFH
#define _BRSFC_CV_IA_GXRFSX1
#define _BRSFC_CV_IA_GXRFSX2
#define _BRSFC_CV_IA_GXSPIRAL
#define _BRSFC_CV_IA_GXSPIRAL2
#define _BRSFC_CV_IA_GXSPOIL
#define _BRSFC_CV_IA_GXSPOIL2
#define _BRSFC_CV_IA_GXW
#define _BRSFC_CV_IA_GXW1FTG
#define _BRSFC_CV_IA_GXW1XTG
#define _BRSFC_CV_IA_GXW2
#define _BRSFC_CV_IA_GXW2DTG
#define _BRSFC_CV_IA_GXW2FTG
#define _BRSFC_CV_IA_GXW2RS
#define _BRSFC_CV_IA_GXWAS
#define _BRSFC_CV_IA_GXWDTG
#define _BRSFC_CV_IA_GXWEX
#define _BRSFC_CV_IA_GXWMON
#define _BRSFC_CV_IA_GXWMPS1
#define _BRSFC_CV_IA_GXWRS
#define _BRSFC_CV_IA_GY1
#define _BRSFC_CV_IA_GY1AS
#define _BRSFC_CV_IA_GY1ASWA
#define _BRSFC_CV_IA_GY1ASWB
#define _BRSFC_CV_IA_GY1CFH
#define _BRSFC_CV_IA_GY1DTG
#define _BRSFC_CV_IA_GY1DTGWA
#define _BRSFC_CV_IA_GY1DTGWB
#define _BRSFC_CV_IA_GY1FED
#define _BRSFC_CV_IA_GY1FEN
#define _BRSFC_CV_IA_GY1FEU
#define _BRSFC_CV_IA_GY1MON
#define _BRSFC_CV_IA_GY1MPS1
#define _BRSFC_CV_IA_GY1R
#define _BRSFC_CV_IA_GY1RAS
#define _BRSFC_CV_IA_GY1RASWA
#define _BRSFC_CV_IA_GY1RASWB
#define _BRSFC_CV_IA_GY1RDTG
#define _BRSFC_CV_IA_GY1RDTGWA
#define _BRSFC_CV_IA_GY1RDTGWB
#define _BRSFC_CV_IA_GY1RRS
#define _BRSFC_CV_IA_GY1RRSWA
#define _BRSFC_CV_IA_GY1RRSWB
#define _BRSFC_CV_IA_GY1RS
#define _BRSFC_CV_IA_GY1RSWA
#define _BRSFC_CV_IA_GY1RSWB
#define _BRSFC_CV_IA_GY1RWA
#define _BRSFC_CV_IA_GY1RWB
#define _BRSFC_CV_IA_GY1TM
#define _BRSFC_CV_IA_GY1WA
#define _BRSFC_CV_IA_GY1WB
#define _BRSFC_CV_IA_GY2DTG
#define _BRSFC_CV_IA_GY2DTGWA
#define _BRSFC_CV_IA_GY2DTGWB
#define _BRSFC_CV_IA_GY2FED
#define _BRSFC_CV_IA_GY2FEN
#define _BRSFC_CV_IA_GY2FEU
#define _BRSFC_CV_IA_GY2RS
#define _BRSFC_CV_IA_GY2RSWA
#define _BRSFC_CV_IA_GY2RSWB
#define _BRSFC_CV_IA_GYB
#define _BRSFC_CV_IA_GYBRSFC1
#define _BRSFC_CV_IA_GYBRSFC2
#define _BRSFC_CV_IA_GYCYLR
#define _BRSFC_CV_IA_GYCYLRTIPUP
#define _BRSFC_CV_IA_GYFE
#define _BRSFC_CV_IA_GYFE1
#define _BRSFC_CV_IA_GYFE2
#define _BRSFC_CV_IA_GYFLPK
#define _BRSFC_CV_IA_GYFLPKWA
#define _BRSFC_CV_IA_GYFLPKWB
#define _BRSFC_CV_IA_GYFLPVENC
#define _BRSFC_CV_IA_GYFLPVENCWA
#define _BRSFC_CV_IA_GYFLPVENCWB
#define _BRSFC_CV_IA_GYHYST1
#define _BRSFC_CV_IA_GYHYST2
#define _BRSFC_CV_IA_GYKCFH
#define _BRSFC_CV_IA_GYKCFL
#define _BRSFC_CV_IA_GYKCS
#define _BRSFC_CV_IA_GYKCS_MAX
#define _BRSFC_CV_IA_GYKFS
#define _BRSFC_CV_IA_GYKILL
#define _BRSFC_CV_IA_GYKRCVN
#define _BRSFC_CV_IA_GYKSE1
#define _BRSFC_CV_IA_GYKSE2
#define _BRSFC_CV_IA_GYKSE3
#define _BRSFC_CV_IA_GYKSE4
#define _BRSFC_CV_IA_GYKSE5
#define _BRSFC_CV_IA_GYKSE6
#define _BRSFC_CV_IA_GYKSP
#define _BRSFC_CV_IA_GYKSSF
#define _BRSFC_CV_IA_GYKSX1
#define _BRSFC_CV_IA_GYKSX2
#define _BRSFC_CV_IA_GYKSY1
#define _BRSFC_CV_IA_GYKSY2
#define _BRSFC_CV_IA_GYKSZ1
#define _BRSFC_CV_IA_GYKSZ2
#define _BRSFC_CV_IA_GYKXTGL
#define _BRSFC_CV_IA_GYKXTGR
#define _BRSFC_CV_IA_GYRF0KCFH
#define _BRSFC_CV_IA_GYRF1MON
#define _BRSFC_CV_IA_GYRF1MPS1
#define _BRSFC_CV_IA_GYRF1TM
#define _BRSFC_CV_IA_GYRF1XTG
#define _BRSFC_CV_IA_GYRF2CFH
#define _BRSFC_CV_IA_GYRF2LMON
#define _BRSFC_CV_IA_GYRF2MON
#define _BRSFC_CV_IA_GYRF2RMON
#define _BRSFC_CV_IA_GYRF3CFH
#define _BRSFC_CV_IA_GYRFMONTIPUP
#define _BRSFC_CV_IA_GYRFSY1
#define _BRSFC_CV_IA_GYRFSY2
#define _BRSFC_CV_IA_GYSPIRAL
#define _BRSFC_CV_IA_GYSPIRAL2
#define _BRSFC_CV_IA_GYSPOIL
#define _BRSFC_CV_IA_GYSPOIL2
#define _BRSFC_CV_IA_GZ1
#define _BRSFC_CV_IA_GZ1AS
#define _BRSFC_CV_IA_GZ1CFL
#define _BRSFC_CV_IA_GZ1D
#define _BRSFC_CV_IA_GZ1DTG
#define _BRSFC_CV_IA_GZ1FED
#define _BRSFC_CV_IA_GZ1FEN
#define _BRSFC_CV_IA_GZ1FEU
#define _BRSFC_CV_IA_GZ1FTG
#define _BRSFC_CV_IA_GZ1MON
#define _BRSFC_CV_IA_GZ1MPS1
#define _BRSFC_CV_IA_GZ1RS
#define _BRSFC_CV_IA_GZ1S
#define _BRSFC_CV_IA_GZ1U
#define _BRSFC_CV_IA_GZ1XTG
#define _BRSFC_CV_IA_GZ2BFTG
#define _BRSFC_CV_IA_GZ2FED
#define _BRSFC_CV_IA_GZ2FEN
#define _BRSFC_CV_IA_GZ2FEU
#define _BRSFC_CV_IA_GZ2FTG
#define _BRSFC_CV_IA_GZ2XTG
#define _BRSFC_CV_IA_GZ3FTG
#define _BRSFC_CV_IA_GZBRSFC1
#define _BRSFC_CV_IA_GZBRSFC1ECHO1
#define _BRSFC_CV_IA_GZBRSFC1ECHO2
#define _BRSFC_CV_IA_GZBRSFC2
#define _BRSFC_CV_IA_GZCOMB
#define _BRSFC_CV_IA_GZCOMBHTR
#define _BRSFC_CV_IA_GZCOMBHTRWA
#define _BRSFC_CV_IA_GZCOMBHTRWB
#define _BRSFC_CV_IA_GZCOMBWA
#define _BRSFC_CV_IA_GZCOMBWB
#define _BRSFC_CV_IA_GZCYLR
#define _BRSFC_CV_IA_GZCYLRTIPUP
#define _BRSFC_CV_IA_GZFCBASE
#define _BRSFC_CV_IA_GZFCCOMB
#define _BRSFC_CV_IA_GZFCD
#define _BRSFC_CV_IA_GZFCEND
#define _BRSFC_CV_IA_GZFCU
#define _BRSFC_CV_IA_GZFLPK
#define _BRSFC_CV_IA_GZFLPKWA
#define _BRSFC_CV_IA_GZFLPKWB
#define _BRSFC_CV_IA_GZFLPVENC
#define _BRSFC_CV_IA_GZFLPVENCWA
#define _BRSFC_CV_IA_GZFLPVENCWB
#define _BRSFC_CV_IA_GZK
#define _BRSFC_CV_IA_GZKAS
#define _BRSFC_CV_IA_GZKBSDTG
#define _BRSFC_CV_IA_GZKBSRS
#define _BRSFC_CV_IA_GZKCS
#define _BRSFC_CV_IA_GZKDTG
#define _BRSFC_CV_IA_GZKFS
#define _BRSFC_CV_IA_GZKGIR01
#define _BRSFC_CV_IA_GZKGIR02
#define _BRSFC_CV_IA_GZKILL
#define _BRSFC_CV_IA_GZKILLER
#define _BRSFC_CV_IA_GZKMON
#define _BRSFC_CV_IA_GZKMONTIPUP
#define _BRSFC_CV_IA_GZKRCVN
#define _BRSFC_CV_IA_GZKRFFRIR
#define _BRSFC_CV_IA_GZKRS
#define _BRSFC_CV_IA_GZKS
#define _BRSFC_CV_IA_GZKS5FP
#define _BRSFC_CV_IA_GZKSP
#define _BRSFC_CV_IA_GZKSSF
#define _BRSFC_CV_IA_GZP
#define _BRSFC_CV_IA_GZPHTR
#define _BRSFC_CV_IA_GZPHTRWA
#define _BRSFC_CV_IA_GZPHTRWB
#define _BRSFC_CV_IA_GZPTM
#define _BRSFC_CV_IA_GZPWA
#define _BRSFC_CV_IA_GZPWB
#define _BRSFC_CV_IA_GZRF0
#define _BRSFC_CV_IA_GZRF0CFH
#define _BRSFC_CV_IA_GZRF0K
#define _BRSFC_CV_IA_GZRF1
#define _BRSFC_CV_IA_GZRF1_TEMP
#define _BRSFC_CV_IA_GZRF1AS
#define _BRSFC_CV_IA_GZRF1CFH
#define _BRSFC_CV_IA_GZRF1CFL
#define _BRSFC_CV_IA_GZRF1DTG
#define _BRSFC_CV_IA_GZRF1FTG
#define _BRSFC_CV_IA_GZRF1HTR
#define _BRSFC_CV_IA_GZRF1MON
#define _BRSFC_CV_IA_GZRF1MPS1
#define _BRSFC_CV_IA_GZRF1RS
#define _BRSFC_CV_IA_GZRF1S
#define _BRSFC_CV_IA_GZRF1XTG
#define _BRSFC_CV_IA_GZRF2FTG
#define _BRSFC_CV_IA_GZRF2LCFH
#define _BRSFC_CV_IA_GZRF2LMPS1
#define _BRSFC_CV_IA_GZRF2MPS1
#define _BRSFC_CV_IA_GZRF2RCFH
#define _BRSFC_CV_IA_GZRF2RMPS1
#define _BRSFC_CV_IA_GZRF2XTG
#define _BRSFC_CV_IA_GZRF3FTG
#define _BRSFC_CV_IA_GZRF3LCFH
#define _BRSFC_CV_IA_GZRF3RCFH
#define _BRSFC_CV_IA_GZRF4CFH
#define _BRSFC_CV_IA_GZRF4LCFH
#define _BRSFC_CV_IA_GZRF4RCFH
#define _BRSFC_CV_IA_GZRFFRIR
#define _BRSFC_CV_IA_GZRFGIR01
#define _BRSFC_CV_IA_GZRFGIR02
#define _BRSFC_CV_IA_GZRFS5FPH
#define _BRSFC_CV_IA_GZRFSE1
#define _BRSFC_CV_IA_GZRFSE2
#define _BRSFC_CV_IA_GZRFSE3
#define _BRSFC_CV_IA_GZRFSE4
#define _BRSFC_CV_IA_GZRFSE5
#define _BRSFC_CV_IA_GZRFSE6
#define _BRSFC_CV_IA_GZRFSSFH
#define _BRSFC_CV_IA_GZRFSZ1
#define _BRSFC_CV_IA_GZRFSZ2
#define _BRSFC_CV_IA_GZS5FPHCOMB
#define _BRSFC_CV_IA_GZSSFHCOMB
#define _BRSFC_CV_IA_GZVLW
#define _BRSFC_CV_IA_HARD180
#define _BRSFC_CV_IA_OMEGA_HS_RFCSSAT
#define _BRSFC_CV_IA_OMEGA_IR0
#define _BRSFC_CV_IA_OMEGA_RFFRIR
#define _BRSFC_CV_IA_OMEGA_RFGIR01
#define _BRSFC_CV_IA_OMEGA_RFGIR02
#define _BRSFC_CV_IA_OMEGARF0CFH
#define _BRSFC_CV_IA_PH180
#define _BRSFC_CV_IA_PHS_RF3XTG
#define _BRSFC_CV_IA_PHS_RF4XTG
#define _BRSFC_CV_IA_POSTGXW1FTG
#define _BRSFC_CV_IA_RCVRBL
#define _BRSFC_CV_IA_RCVRBL2
#define _BRSFC_CV_IA_RF0
#define _BRSFC_CV_IA_RF0CFH
#define _BRSFC_CV_IA_RF1
#define _BRSFC_CV_IA_RF180
#define _BRSFC_CV_IA_RF1_TEMP
#define _BRSFC_CV_IA_RF1AS
#define _BRSFC_CV_IA_RF1CFH
#define _BRSFC_CV_IA_RF1CFL
#define _BRSFC_CV_IA_RF1DTG
#define _BRSFC_CV_IA_RF1FTG
#define _BRSFC_CV_IA_RF1HTR
#define _BRSFC_CV_IA_RF1MON
#define _BRSFC_CV_IA_RF1MPS1
#define _BRSFC_CV_IA_RF1RS
#define _BRSFC_CV_IA_RF1TM
#define _BRSFC_CV_IA_RF1XTG
#define _BRSFC_CV_IA_RF2CFH
#define _BRSFC_CV_IA_RF2FTG
#define _BRSFC_CV_IA_RF2MON
#define _BRSFC_CV_IA_RF2MPS1
#define _BRSFC_CV_IA_RF2XTG
#define _BRSFC_CV_IA_RF3CFH
#define _BRSFC_CV_IA_RF3FTG
#define _BRSFC_CV_IA_RF3XTG
#define _BRSFC_CV_IA_RF4CFH
#define _BRSFC_CV_IA_RF4XTG
#define _BRSFC_CV_IA_RF90
#define _BRSFC_CV_IA_RFBDTG
#define _BRSFC_CV_IA_RFBDTG_THETA
#define _BRSFC_CV_IA_RFBRS
#define _BRSFC_CV_IA_RFBRS_THETA
#define _BRSFC_CV_IA_RFCSSAT
#define _BRSFC_CV_IA_RFCSSATCFH
#define _BRSFC_CV_IA_RFCYLR
#define _BRSFC_CV_IA_RFCYLRTIPUP
#define _BRSFC_CV_IA_RFFLP180
#define _BRSFC_CV_IA_RFFLP180_THE
#define _BRSFC_CV_IA_RFFLP90
#define _BRSFC_CV_IA_RFFLP90_THE
#define _BRSFC_CV_IA_RFFLP90R
#define _BRSFC_CV_IA_RFFLP90R_THE
#define _BRSFC_CV_IA_RFFRIR
#define _BRSFC_CV_IA_RFFS
#define _BRSFC_CV_IA_RFGIR01
#define _BRSFC_CV_IA_RFGIR02
#define _BRSFC_CV_IA_RFMONTIPUP
#define _BRSFC_CV_IA_RFS5FPH
#define _BRSFC_CV_IA_RFSE1
#define _BRSFC_CV_IA_RFSE2
#define _BRSFC_CV_IA_RFSE3
#define _BRSFC_CV_IA_RFSE4
#define _BRSFC_CV_IA_RFSE5
#define _BRSFC_CV_IA_RFSE6
#define _BRSFC_CV_IA_RFSSF
#define _BRSFC_CV_IA_RFSSFH
#define _BRSFC_CV_IA_RFSX1
#define _BRSFC_CV_IA_RFSX2
#define _BRSFC_CV_IA_RFSY1
#define _BRSFC_CV_IA_RFSY2
#define _BRSFC_CV_IA_RFSZ1
#define _BRSFC_CV_IA_RFSZ2
#define _BRSFC_CV_IA_RFTIPUP
#define _BRSFC_CV_IA_SDIXON
#define _BRSFC_CV_IA_SDIXON2
#define _BRSFC_CV_IA_STGYCYLRA
#define _BRSFC_CV_IA_STGYCYLRATIPUP
#define _BRSFC_CV_IA_STGZCYLRA
#define _BRSFC_CV_IA_STGZCYLRATIPUP
#define _BRSFC_CV_IA_THCYLR
#define _BRSFC_CV_IA_THCYLRTIPUP
#define _BRSFC_CV_IA_THETARF1
#define _BRSFC_CV_IA_XDIXON
#define _BRSFC_CV_IA_YDIXON
#define _BRSFC_CV_IA_ZDIXON
#define _BRSFC_CV_IDEAL_DEBUG
#define _BRSFC_CV_IDEAL_ECHO_MODE
#define _BRSFC_CV_IDEAL_FLAG
#define _BRSFC_CV_IDEAL_MAX
#define _BRSFC_CV_IDEAL_MAX_IM
#define _BRSFC_CV_IDEAL_MAX_LOCS
#define _BRSFC_CV_IDEAL_MIN
#define _BRSFC_CV_IDEAL_MIN_TE
#define _BRSFC_CV_IDEAL_NECHO
#define _BRSFC_CV_IDEAL_NO_MAG_IM
#define _BRSFC_CV_IDEAL_OPT_TE
#define _BRSFC_CV_IDEAL_PW
#define _BRSFC_CV_IDEAL_SHIFT1
#define _BRSFC_CV_IDEAL_SHIFT2
#define _BRSFC_CV_IDEAL_SHIFT3
#define _BRSFC_CV_IDEAL_SHIFT_MAX
#define _BRSFC_CV_IDEAL_TE1
#define _BRSFC_CV_IDEAL_TE2
#define _BRSFC_CV_IDEAL_TE3
#define _BRSFC_CV_IDEALIQ_ENABLE_HIGHER_FLIP
#define _BRSFC_CV_IDEALIQ_ESP
#define _BRSFC_CV_IDEALIQ_FLAG
#define _BRSFC_CV_IDEALIQ_NSHOTS
#define _BRSFC_CV_IDEALIQ_OPTFA
#define _BRSFC_CV_IDEALIQ_PC_DDA
#define _BRSFC_CV_IDEALIQ_PC_DIMENSION
#define _BRSFC_CV_IDEALIQ_PC_EXTRA_TR
#define _BRSFC_CV_IDEALIQ_PC_FLAG
#define _BRSFC_CV_IDEALIQ_PC_YLINES
#define _BRSFC_CV_IDEALIQ_PC_YLOWER
#define _BRSFC_CV_IDEALIQ_PC_YUPPER
#define _BRSFC_CV_IDEALIQ_PC_ZLINES
#define _BRSFC_CV_IDEALIQ_PC_ZLOWER
#define _BRSFC_CV_IDEALIQ_PC_ZUPPER
#define _BRSFC_CV_IDEALIQ_PS_ECHO
#define _BRSFC_CV_IDEALIQ_PW
#define _BRSFC_CV_IFIR_DNAV_FLAG
#define _BRSFC_CV_IFIR_DUMMY_PE
#define _BRSFC_CV_IFIR_FLAG
#define _BRSFC_CV_IFIR_FRIR_FLAG
#define _BRSFC_CV_IFIR_POSITION
#define _BRSFC_CV_IFIR_STIR_FLAG
#define _BRSFC_CV_IFIR_VTHICK
#define _BRSFC_CV_IH_IDEALDBG_CV1
#define _BRSFC_CV_IH_IDEALDBG_CV10
#define _BRSFC_CV_IH_IDEALDBG_CV11
#define _BRSFC_CV_IH_IDEALDBG_CV12
#define _BRSFC_CV_IH_IDEALDBG_CV13
#define _BRSFC_CV_IH_IDEALDBG_CV14
#define _BRSFC_CV_IH_IDEALDBG_CV15
#define _BRSFC_CV_IH_IDEALDBG_CV16
#define _BRSFC_CV_IH_IDEALDBG_CV17
#define _BRSFC_CV_IH_IDEALDBG_CV18
#define _BRSFC_CV_IH_IDEALDBG_CV19
#define _BRSFC_CV_IH_IDEALDBG_CV2
#define _BRSFC_CV_IH_IDEALDBG_CV20
#define _BRSFC_CV_IH_IDEALDBG_CV21
#define _BRSFC_CV_IH_IDEALDBG_CV22
#define _BRSFC_CV_IH_IDEALDBG_CV23
#define _BRSFC_CV_IH_IDEALDBG_CV24
#define _BRSFC_CV_IH_IDEALDBG_CV25
#define _BRSFC_CV_IH_IDEALDBG_CV26
#define _BRSFC_CV_IH_IDEALDBG_CV27
#define _BRSFC_CV_IH_IDEALDBG_CV28
#define _BRSFC_CV_IH_IDEALDBG_CV29
#define _BRSFC_CV_IH_IDEALDBG_CV3
#define _BRSFC_CV_IH_IDEALDBG_CV30
#define _BRSFC_CV_IH_IDEALDBG_CV31
#define _BRSFC_CV_IH_IDEALDBG_CV32
#define _BRSFC_CV_IH_IDEALDBG_CV4
#define _BRSFC_CV_IH_IDEALDBG_CV5
#define _BRSFC_CV_IH_IDEALDBG_CV6
#define _BRSFC_CV_IH_IDEALDBG_CV7
#define _BRSFC_CV_IH_IDEALDBG_CV8
#define _BRSFC_CV_IH_IDEALDBG_CV9
#define _BRSFC_CV_IHBSOFFSETFREQ
#define _BRSFC_CV_IHBSPTI
#define _BRSFC_CV_IHCARDT1MAP_HB_PATTERN
#define _BRSFC_CV_IHDIXONIPTE
#define _BRSFC_CV_IHDIXONOOPTE
#define _BRSFC_CV_IHDIXONTE
#define _BRSFC_CV_IHEESP
#define _BRSFC_CV_IHESP
#define _BRSFC_CV_IHFCINEIM
#define _BRSFC_CV_IHFCINENT
#define _BRSFC_CV_IHFLIP
#define _BRSFC_CV_IHINPLANEXRES
#define _BRSFC_CV_IHINPLANEYRES
#define _BRSFC_CV_IHLABELTIME
#define _BRSFC_CV_IHMAXTDELPHASE
#define _BRSFC_CV_IHNEGSCANSPACING
#define _BRSFC_CV_IHNEW_SERIES
#define _BRSFC_CV_IHNEX
#define _BRSFC_CV_IHOFFSETFREQ
#define _BRSFC_CV_IHPOSTLABELDELAY
#define _BRSFC_CV_IHRBWPERPIX
#define _BRSFC_CV_IHTAGFA
#define _BRSFC_CV_IHTAGOR
#define _BRSFC_CV_IHTDEL1
#define _BRSFC_CV_IHTE1
#define _BRSFC_CV_IHTE10
#define _BRSFC_CV_IHTE11
#define _BRSFC_CV_IHTE12
#define _BRSFC_CV_IHTE13
#define _BRSFC_CV_IHTE14
#define _BRSFC_CV_IHTE15
#define _BRSFC_CV_IHTE16
#define _BRSFC_CV_IHTE2
#define _BRSFC_CV_IHTE3
#define _BRSFC_CV_IHTE4
#define _BRSFC_CV_IHTE5
#define _BRSFC_CV_IHTE6
#define _BRSFC_CV_IHTE7
#define _BRSFC_CV_IHTE8
#define _BRSFC_CV_IHTE9
#define _BRSFC_CV_IHTI
#define _BRSFC_CV_IHTR
#define _BRSFC_CV_IHVBW1
#define _BRSFC_CV_IHVBW10
#define _BRSFC_CV_IHVBW11
#define _BRSFC_CV_IHVBW12
#define _BRSFC_CV_IHVBW13
#define _BRSFC_CV_IHVBW14
#define _BRSFC_CV_IHVBW15
#define _BRSFC_CV_IHVBW16
#define _BRSFC_CV_IHVBW2
#define _BRSFC_CV_IHVBW3
#define _BRSFC_CV_IHVBW4
#define _BRSFC_CV_IHVBW5
#define _BRSFC_CV_IHVBW6
#define _BRSFC_CV_IHVBW7
#define _BRSFC_CV_IHVBW8
#define _BRSFC_CV_IHVBW9
#define _BRSFC_CV_IMAGENUM
#define _BRSFC_CV_IMAXECTRICKSVIEW
#define _BRSFC_CV_INIT_XTG_DEADTIME
#define _BRSFC_CV_INITIALIZE_GRADOPT
#define _BRSFC_CV_INITIALIZE_SCALE
#define _BRSFC_CV_INITNEWGEO
#define _BRSFC_CV_INTER_NECHO
#define _BRSFC_CV_INTERMITTANT_CHEMSAT
#define _BRSFC_CV_INTSLAB_FLAG
#define _BRSFC_CV_INVERTPHASE
#define _BRSFC_CV_IPG_TRIGTEST
#define _BRSFC_CV_IR_SEQTIME_ADJUST
#define _BRSFC_CV_IRDISDACQS
#define _BRSFC_CV_IRFREQ
#define _BRSFC_CV_IRMSX
#define _BRSFC_CV_IRMSY
#define _BRSFC_CV_IRMSZ
#define _BRSFC_CV_IRPREP_FLAG
#define _BRSFC_CV_IRSCALE
#define _BRSFC_CV_ISI_DONE
#define _BRSFC_CV_ISI_EXTRA
#define _BRSFC_CV_ISI_EXTRA_GIR
#define _BRSFC_CV_ISI_FLAG
#define _BRSFC_CV_ISI_GIRDELAY
#define _BRSFC_CV_ISI_SATDELAY
#define _BRSFC_CV_ISI_SLICEEXTRA
#define _BRSFC_CV_ISIBIT
#define _BRSFC_CV_ISO_DELAY
#define _BRSFC_CV_ISO_DELAY_FRAC
#define _BRSFC_CV_ISO_DELAY_RFFLP90
#define _BRSFC_CV_ISO_DELAY_RFFLP90R
#define _BRSFC_CV_JSTD_EXPONENT_NV
#define _BRSFC_CV_JSTD_EXPONENT_BODY
#define _BRSFC_CV_JSTD_MULTIPLIER_NV
#define _BRSFC_CV_JSTD_MULTIPLIER_BODY
#define _BRSFC_CV_K_IDEAL_PI
#define _BRSFC_CV_KACQ_UID_WASHIN
#define _BRSFC_CV_KAISER_RAMPLEN
#define _BRSFC_CV_KBAND_WIDTH
#define _BRSFC_CV_KERNEL_REGIONS
#define _BRSFC_CV_KERNEL_REGIONS_MAX
#define _BRSFC_CV_KERNEL_REGIONS_MIN
#define _BRSFC_CV_KILLER01_TIME
#define _BRSFC_CV_KILLER02_TIME
#define _BRSFC_CV_KILLER_AXIS
#define _BRSFC_CV_KREWIND_FLAG
#define _BRSFC_CV_KRFERMECORR_FACTOR
#define _BRSFC_CV_KTARC_FLAG
#define _BRSFC_CV_LAVA_AVE_MODE
#define _BRSFC_CV_LAVA_FLAG
#define _BRSFC_CV_LINESTODISCARD
#define _BRSFC_CV_LLIMTE1
#define _BRSFC_CV_LLIMTE2
#define _BRSFC_CV_LLIMTE3
#define _BRSFC_CV_LOCAL_TG
#define _BRSFC_CV_LOCPOSITION_RFGIR01
#define _BRSFC_CV_LOCPOSITION_RFGIR02
#define _BRSFC_CV_LOGGRD
#define _BRSFC_CV_LOOK_FOR_TRIG
#define _BRSFC_CV_LOOPDELAY
#define _BRSFC_CV_LOOPDELAY2
#define _BRSFC_CV_LP_MODE
#define _BRSFC_CV_LP_STRETCH
#define _BRSFC_CV_LX_PWMTIME
#define _BRSFC_CV_LY_PWMTIME
#define _BRSFC_CV_LZ_PWMTIME
#define _BRSFC_CV_MAG_CREATE
#define _BRSFC_CV_MAG_MASK
#define _BRSFC_CV_MASKPOINTS
#define _BRSFC_CV_MASK_PHASE_FLAG
#define _BRSFC_CV_MASK_REGIONS
#define _BRSFC_CV_MASK_REGIONS_MAX
#define _BRSFC_CV_MASK_REGIONS_MIN
#define _BRSFC_CV_MASKV_FTMRA_FLAG
#define _BRSFC_CV_MAXGRADRES
#define _BRSFC_CV_MAXSERIESTIME
#define _BRSFC_CV_MAX_AREA_GXWEX
#define _BRSFC_CV_MAX_ASPIR_FA
#define _BRSFC_CV_MAX_AVG_TIME
#define _BRSFC_CV_MAX_BAMSLICE
#define _BRSFC_CV_MAX_FF_ERROR
#define _BRSFC_CV_MAX_NAVGATE_TR
#define _BRSFC_CV_MAX_PENCODES
#define _BRSFC_CV_MAX_REGSAR
#define _BRSFC_CV_MAX_RESP_WAIT
#define _BRSFC_CV_MAX_SATSAR
#define _BRSFC_CV_MAX_SEQSAR
#define _BRSFC_CV_MAX_SEQSAR_ORIG
#define _BRSFC_CV_MAX_SEQSAR_PREPOFF
#define _BRSFC_CV_MAX_SEQSARMON
#define _BRSFC_CV_MAX_SLICESAR_PREPOFF
#define _BRSFC_CV_MAX_SLQUANT
#define _BRSFC_CV_MAX_SS_FA
#define _BRSFC_CV_MAX_TDEL1_TIME
#define _BRSFC_CV_MAXB1_RF1
#define _BRSFC_CV_MAXKILLER_TIME
#define _BRSFC_CV_MAXPC_COR
#define _BRSFC_CV_MAXPC_DEBUG
#define _BRSFC_CV_MAXPC_POINTS
#define _BRSFC_CV_MAXX
#define _BRSFC_CV_MAXY
#define _BRSFC_CV_MEASURED_TG
#define _BRSFC_CV_MEDAL_AUTOTE_FLAG
#define _BRSFC_CV_MEDAL_AUTOTELOCK_FLAG
#define _BRSFC_CV_MEDAL_ECHO_MODE
#define _BRSFC_CV_MEDAL_ENH_FLAG
#define _BRSFC_CV_MEDAL_ETL
#define _BRSFC_CV_MEDAL_FLAG
#define _BRSFC_CV_MEDAL_FLEXECHO_ORDER_FLAG
#define _BRSFC_CV_MEDAL_FREQ_AVE
#define _BRSFC_CV_MEDAL_FREQ_MAX
#define _BRSFC_CV_MEDAL_FREQ_MIN
#define _BRSFC_CV_MEDAL_FW_FREQ_AVE
#define _BRSFC_CV_MEDAL_FW_FREQ_LLIMIT
#define _BRSFC_CV_MEDAL_FW_FREQ_ULIMIT
#define _BRSFC_CV_MEDAL_IP_TE
#define _BRSFC_CV_MEDAL_IP_TE_MAX
#define _BRSFC_CV_MEDAL_IP_TE_MIN
#define _BRSFC_CV_MEDAL_IP_TE_MINUS
#define _BRSFC_CV_MEDAL_IP_TE_PLUS
#define _BRSFC_CV_MEDAL_K_IP_PI
#define _BRSFC_CV_MEDAL_K_OOP_PI
#define _BRSFC_CV_MEDAL_MAX
#define _BRSFC_CV_MEDAL_MAX_XRES
#define _BRSFC_CV_MEDAL_MIN
#define _BRSFC_CV_MEDAL_MULTITR_FLAG
#define _BRSFC_CV_MEDAL_NECHO
#define _BRSFC_CV_MEDAL_OOP_TE
#define _BRSFC_CV_MEDAL_OOP_TE_MAX
#define _BRSFC_CV_MEDAL_OOP_TE_MIN
#define _BRSFC_CV_MEDAL_OOP_TE_MINUS
#define _BRSFC_CV_MEDAL_OOP_TE_PLUS
#define _BRSFC_CV_MEDAL_PI_AVE
#define _BRSFC_CV_MEDAL_PI_MAX
#define _BRSFC_CV_MEDAL_PI_MIN
#define _BRSFC_CV_MEDAL_PW
#define _BRSFC_CV_MEDAL_SHIFT1
#define _BRSFC_CV_MEDAL_SHIFT2
#define _BRSFC_CV_MEDAL_SHIFT_MAX
#define _BRSFC_CV_MEDAL_TE1
#define _BRSFC_CV_MEDAL_TE1_UPPER
#define _BRSFC_CV_MEDAL_TE2
#define _BRSFC_CV_MEDAL_TE2_UPPER
#define _BRSFC_CV_MERGE_DEFAULTTE
#define _BRSFC_CV_MERGE_ECHOINDEX
#define _BRSFC_CV_MERGE_FLAG
#define _BRSFC_CV_MERGE_MIN_ECHOES
#define _BRSFC_CV_MERGE_MINTR
#define _BRSFC_CV_MERGE_SATWEIGHT
#define _BRSFC_CV_MERGE_TARGETTE
#define _BRSFC_CV_MILD_NOTE_SUPPORT
#define _BRSFC_CV_MIN180TE
#define _BRSFC_CV_MIN_DELAY_SEC
#define _BRSFC_CV_MIN_DELAY_TIME
#define _BRSFC_CV_MIN_DTGTE
#define _BRSFC_CV_MIN_END_SEGMENT_DELAY
#define _BRSFC_CV_MIN_MONTR
#define _BRSFC_CV_MIN_PENCODES
#define _BRSFC_CV_MIN_RFAMPCPBLTY
#define _BRSFC_CV_MIN_RFAMPCPBLTY_PREPOFF
#define _BRSFC_CV_MIN_RFAVGPOW
#define _BRSFC_CV_MIN_RFAVGPOW_PREPOFF
#define _BRSFC_CV_MIN_RFDYCC
#define _BRSFC_CV_MIN_RFDYCC_PREPOFF
#define _BRSFC_CV_MIN_RFRMSB1
#define _BRSFC_CV_MIN_RFRMSB1_PREPOFF
#define _BRSFC_CV_MIN_RSTE
#define _BRSFC_CV_MIN_SEGMENT_TR
#define _BRSFC_CV_MIN_SEQ1
#define _BRSFC_CV_MIN_SEQ2
#define _BRSFC_CV_MIN_SEQ2_ECHO2
#define _BRSFC_CV_MIN_SEQ2_ECHO3
#define _BRSFC_CV_MIN_SEQ2_ECHO4
#define _BRSFC_CV_MIN_SEQ3
#define _BRSFC_CV_MIN_SEQGRAD
#define _BRSFC_CV_MIN_SEQRFAMP
#define _BRSFC_CV_MIN_SEQRFAMP_PREPOFF
#define _BRSFC_CV_MIN_SEQRFAMPMON
#define _BRSFC_CV_MIN_SEQX
#define _BRSFC_CV_MIN_SEQXZ
#define _BRSFC_CV_MIN_SLQUANT
#define _BRSFC_CV_MIN_SPECIRTI
#define _BRSFC_CV_MIN_TDEL1_FIESTA
#define _BRSFC_CV_MIN_TDEL1_TIME
#define _BRSFC_CV_MIN_TEFE
#define _BRSFC_CV_MIN_TEGY
#define _BRSFC_CV_MIN_TEGZ
#define _BRSFC_CV_MIN_TENFE
#define _BRSFC_CV_MIN_TI
#define _BRSFC_CV_MIN_TSEQ_IRPREP
#define _BRSFC_CV_MINIMIZE_RFUNBLANK_TIME
#define _BRSFC_CV_MINPCFLATTOP
#define _BRSFC_CV_MINPH_ISO_DELAY
#define _BRSFC_CV_MINSEQBUSBAR_T
#define _BRSFC_CV_MINSEQBUSBARMON_T
#define _BRSFC_CV_MINSEQCABLE_MAXPOW_T
#define _BRSFC_CV_MINSEQCABLE_T
#define _BRSFC_CV_MINSEQCABLEBURST_T
#define _BRSFC_CV_MINSEQCABLEMON_T
#define _BRSFC_CV_MINSEQCHOKE_T
#define _BRSFC_CV_MINSEQCOIL_ESP
#define _BRSFC_CV_MINSEQCOIL_T
#define _BRSFC_CV_MINSEQCOILBURST_T
#define _BRSFC_CV_MINSEQCOILMON_T
#define _BRSFC_CV_MINSEQGPM_MAXPOW_T
#define _BRSFC_CV_MINSEQGPM_T
#define _BRSFC_CV_MINSEQGRAM_T
#define _BRSFC_CV_MINSEQGRDDRV_CASE_T
#define _BRSFC_CV_MINSEQGRDDRV_T
#define _BRSFC_CV_MINSEQGRDDRVMON_T
#define _BRSFC_CV_MINSEQGRDDRVX_T
#define _BRSFC_CV_MINSEQGRDDRVXMON_T
#define _BRSFC_CV_MINSEQGRDDRVY_T
#define _BRSFC_CV_MINSEQGRDDRVYMON_T
#define _BRSFC_CV_MINSEQGRDDRVZ_T
#define _BRSFC_CV_MINSEQGRDDRVZMON_T
#define _BRSFC_CV_MINSEQPWM_X
#define _BRSFC_CV_MINSEQPWM_Y
#define _BRSFC_CV_MINSEQPWM_Z
#define _BRSFC_CV_MINSEQRF_CAL
#define _BRSFC_CV_MKGSPEC_EPI2_FLAG
#define _BRSFC_CV_MKGSPEC_FLAG
#define _BRSFC_CV_MKGSPEC_X_GMAX_FLAG
#define _BRSFC_CV_MKGSPEC_X_SR_FLAG
#define _BRSFC_CV_MKGSPEC_Y_GMAX_FLAG
#define _BRSFC_CV_MKGSPEC_Y_SR_FLAG
#define _BRSFC_CV_MKGSPEC_Z_GMAX_FLAG
#define _BRSFC_CV_MKGSPEC_Z_SR_FLAG
#define _BRSFC_CV_MLEVON
#define _BRSFC_CV_MON_ACQFOV
#define _BRSFC_CV_MON_ANGLE
#define _BRSFC_CV_MON_DABDELAY
#define _BRSFC_CV_MON_FCOMP
#define _BRSFC_CV_MON_FOV
#define _BRSFC_CV_MON_LOC
#define _BRSFC_CV_MON_NAVGS
#define _BRSFC_CV_MON_RUN_SETRCVPORTIMM
#define _BRSFC_CV_MON_SSI_TIME
#define _BRSFC_CV_MON_TR
#define _BRSFC_CV_MON_TR_NAV
#define _BRSFC_CV_MON_TR_WAIT
#define _BRSFC_CV_MON_TRIGGER_DELAY
#define _BRSFC_CV_MON_VTHICK
#define _BRSFC_CV_MON_VTHICKY
#define _BRSFC_CV_MON_VTHICKZ
#define _BRSFC_CV_MON_XRES
#define _BRSFC_CV_MONAVE_SAR
#define _BRSFC_CV_MONCAVE_SAR
#define _BRSFC_CV_MONITOR_AXIS
#define _BRSFC_CV_MONITOR_PAGE
#define _BRSFC_CV_MONITOR_TEST
#define _BRSFC_CV_MONLOC_SHIFT
#define _BRSFC_CV_MONLOGGRD
#define _BRSFC_CV_MONNEWGEO
#define _BRSFC_CV_MONOBL_DEBUG
#define _BRSFC_CV_MONOBL_METHOD
#define _BRSFC_CV_MONPEAK_SAR
#define _BRSFC_CV_MONPHYGRD
#define _BRSFC_CV_MONROT_PHI
#define _BRSFC_CV_MONWRITECTRL
#define _BRSFC_CV_MOTSA_OVRHD
#define _BRSFC_CV_MPH_FLAG
#define _BRSFC_CV_MPS1RF1_INST
#define _BRSFC_CV_MPSFOV
#define _BRSFC_CV_MSDE_DDA
#define _BRSFC_CV_MSDE_FLAG
#define _BRSFC_CV_MSDE_RATE
#define _BRSFC_CV_MSDE_RFFLP180_TYPE
#define _BRSFC_CV_MSDE_RFFLP90_TYPE
#define _BRSFC_CV_MSDE_TYPE
#define _BRSFC_CV_MSDE_VENC_POLARITY
#define _BRSFC_CV_MSDE_VENC_WAIT_FLAG
#define _BRSFC_CV_MULTIECHO_FLAG
#define _BRSFC_CV_MULTI_CHANNEL
#define _BRSFC_CV_MYFREQ_OFF
#define _BRSFC_CV_MYPHASE_OFF
#define _BRSFC_CV_MYSLICE_OFF
#define _BRSFC_CV_N_HARD180
#define _BRSFC_CV_N_OMEGA_HS_RFCSSAT
#define _BRSFC_CV_N_OMEGA_IR0
#define _BRSFC_CV_N_OMEGA_RFFRIR
#define _BRSFC_CV_N_OMEGA_RFGIR01
#define _BRSFC_CV_N_OMEGA_RFGIR02
#define _BRSFC_CV_N_OMEGARF0CFH
#define _BRSFC_CV_N_RF90
#define _BRSFC_CV_N_RFFLP180
#define _BRSFC_CV_N_RFFLP180_THE
#define _BRSFC_CV_N_RFFLP90
#define _BRSFC_CV_N_RFFLP90_THE
#define _BRSFC_CV_N_RFFLP90R
#define _BRSFC_CV_N_RFFLP90R_THE
#define _BRSFC_CV_N_RFTIPUP
#define _BRSFC_CV_NAV_1ST_FACTOR
#define _BRSFC_CV_NAV_ALG
#define _BRSFC_CV_NAV_ANGLE_ADJ
#define _BRSFC_CV_NAV_AVAIRRTIME
#define _BRSFC_CV_NAV_CHANNEL
#define _BRSFC_CV_NAV_CHEMDDA
#define _BRSFC_CV_NAV_COILSEL_INDEX
#define _BRSFC_CV_NAV_COILSEL_TR
#define _BRSFC_CV_NAV_DDA
#define _BRSFC_CV_NAV_DEBUG_FLAG
#define _BRSFC_CV_NAV_DIR
#define _BRSFC_CV_NAV_DUAL_MODE
#define _BRSFC_CV_NAV_DUMP_TIME
#define _BRSFC_CV_NAV_IRPREP_FLAG
#define _BRSFC_CV_NAV_LAST_FACTOR
#define _BRSFC_CV_NAV_LINEAR_RAMP_DOWN
#define _BRSFC_CV_NAV_LINEAR_RAMP_UP
#define _BRSFC_CV_NAV_MIN_TSEQ_IRPREP
#define _BRSFC_CV_NAV_NORMALIZATION
#define _BRSFC_CV_NAV_NREPS
#define _BRSFC_CV_NAV_PAUSE_AFTER_PRESCAN
#define _BRSFC_CV_NAV_PRESCAN_TR
#define _BRSFC_CV_NAV_SAVE_RAW_DATA
#define _BRSFC_CV_NAV_SCANTIME_REFRESH
#define _BRSFC_CV_NAV_SCANTIME_REFRESH_PTS
#define _BRSFC_CV_NAV_SR
#define _BRSFC_CV_NAV_SS
#define _BRSFC_CV_NAV_TEST
#define _BRSFC_CV_NAV_TIME_PER_SEG
#define _BRSFC_CV_NAV_TIME_PER_YVIEW
#define _BRSFC_CV_NAV_TIME_PER_ZSEGMENT
#define _BRSFC_CV_NAV_TIMING_FLAG
#define _BRSFC_CV_NAV_TIPUP_RATIO
#define _BRSFC_CV_NAV_TSEQ_IRPREP
#define _BRSFC_CV_NAV_TYPE
#define _BRSFC_CV_NAV_WAIT_FLAG
#define _BRSFC_CV_NAV_WINDOW
#define _BRSFC_CV_NAVEND_TIME
#define _BRSFC_CV_NAVGATE_DDA
#define _BRSFC_CV_NAVGATE_FLAG
#define _BRSFC_CV_NAVGATE_TARGET_TR
#define _BRSFC_CV_NAVGS
#define _BRSFC_CV_NAVIGATORCYL_FLAG
#define _BRSFC_CV_NAVIGATOR_FLAG
#define _BRSFC_CV_NAVKY_SEGMENTS
#define _BRSFC_CV_NAVKY_VIEWS_PER_SEGMENT
#define _BRSFC_CV_NAVKZ_VIEWS_PER_SEGMENT
#define _BRSFC_CV_NAVSAT_FLAG
#define _BRSFC_CV_NAVSCALE
#define _BRSFC_CV_NAVSEG_WEIGHT
#define _BRSFC_CV_NAVSEGMENT_DDA
#define _BRSFC_CV_NAVTRIG_FACTOR
#define _BRSFC_CV_NAVTRIG_FLAG
#define _BRSFC_CV_NAVTRIG_TARGET_TR
#define _BRSFC_CV_NAVTRIG_WAIT_BEFORE_IMAGING
#define _BRSFC_CV_NAVTRIG_WAITTIME
#define _BRSFC_CV_NBW_SSRF
#define _BRSFC_CV_NCVADJUSTEDDELAY
#define _BRSFC_CV_NCVGATEMAXWAIT
#define _BRSFC_CV_NEGPOWERX
#define _BRSFC_CV_NEGPOWERY
#define _BRSFC_CV_NEGPOWERZ
#define _BRSFC_CV_NEGX
#define _BRSFC_CV_NEGY
#define _BRSFC_CV_NEGZ
#define _BRSFC_CV_NEW_VIEW
#define _BRSFC_CV_NEX
#define _BRSFC_CV_NEX_SAVE
#define _BRSFC_CV_NFLOW4D
#define _BRSFC_CV_NOFERMI
#define _BRSFC_CV_NOGRAD
#define _BRSFC_CV_NON_TETIME
#define _BRSFC_CV_NON_TETIME_MON
#define _BRSFC_CV_NOP
#define _BRSFC_CV_NOPE
#define _BRSFC_CV_NOSWITCH_COIL
#define _BRSFC_CV_NOSWITCH_COIL_PSC
#define _BRSFC_CV_NOSWITCH_SLAB
#define _BRSFC_CV_NOSWITCH_SLAB_PSC
#define _BRSFC_CV_NR_OF_SEGA
#define _BRSFC_CV_NR_OF_SEGMENTS
#define _BRSFC_CV_NREPS
#define _BRSFC_CV_NS3D_FLAG
#define _BRSFC_CV_NSEG_PER_NAV_TR
#define _BRSFC_CV_NSEGMENTS
#define _BRSFC_CV_NUM_AUDIBLES
#define _BRSFC_CV_NUM_AUTOTR_CVEVAL_ITER
#define _BRSFC_CV_NUM_AVG_BLINE
#define _BRSFC_CV_NUM_BASELINE_PTS
#define _BRSFC_CV_NUM_DUMMY_SEGMENTEDTR
#define _BRSFC_CV_NUM_FILTER_SLOTS
#define _BRSFC_CV_NUM_IMAGES
#define _BRSFC_CV_NUM_MASK_REGIONS
#define _BRSFC_CV_NUM_OUTER_LOOPS
#define _BRSFC_CV_NUM_REGIONS
#define _BRSFC_CV_NUM_RF1LOBE
#define _BRSFC_CV_NUM_RFFLP180
#define _BRSFC_CV_NUM_SATS
#define _BRSFC_CV_NUM_SHOT
#define _BRSFC_CV_NUM_SLICE_RR
#define _BRSFC_CV_NUM_SUB_REGIONS
#define _BRSFC_CV_NUM_THROWAWAYS
#define _BRSFC_CV_NUM_TRANSITION_FRACTION
#define _BRSFC_CV_NUM_VIEWS_PER_NAV_TR
#define _BRSFC_CV_NUM_VIRCHAN
#define _BRSFC_CV_NUMPTS2PASS
#define _BRSFC_CV_NUMRECV
#define _BRSFC_CV_NUMSATRAMP
#define _BRSFC_CV_OBL_DEBUG
#define _BRSFC_CV_OBL_METHOD
#define _BRSFC_CV_OBLIQUE_MONPLANE
#define _BRSFC_CV_OBLMETHOD_DBDT_FLAG
#define _BRSFC_CV_ODDNEX_NPW
#define _BRSFC_CV_OEFF
#define _BRSFC_CV_OEPF
#define _BRSFC_CV_OFF90
#define _BRSFC_CV_OFF90AS
#define _BRSFC_CV_OFF90MINOR
#define _BRSFC_CV_OFF_GZVLW
#define _BRSFC_CV_OFF_HARD180
#define _BRSFC_CV_OFF_OMEGA_HS_RFCSSAT
#define _BRSFC_CV_OFF_OMEGA_IR0
#define _BRSFC_CV_OFF_OMEGA_RFFRIR
#define _BRSFC_CV_OFF_OMEGA_RFGIR01
#define _BRSFC_CV_OFF_OMEGA_RFGIR02
#define _BRSFC_CV_OFF_OMEGARF0CFH
#define _BRSFC_CV_OFF_RF0
#define _BRSFC_CV_OFF_RF0CFH
#define _BRSFC_CV_OFF_RF1
#define _BRSFC_CV_OFF_RF1AS
#define _BRSFC_CV_OFF_RF1CFH
#define _BRSFC_CV_OFF_RF1CFL
#define _BRSFC_CV_OFF_RF1FTG
#define _BRSFC_CV_OFF_RF1MON
#define _BRSFC_CV_OFF_RF1MPS1
#define _BRSFC_CV_OFF_RF1TM
#define _BRSFC_CV_OFF_RF1XTG
#define _BRSFC_CV_OFF_RF2CFH
#define _BRSFC_CV_OFF_RF2FTG
#define _BRSFC_CV_OFF_RF2MON
#define _BRSFC_CV_OFF_RF2MPS1
#define _BRSFC_CV_OFF_RF2XTG
#define _BRSFC_CV_OFF_RF3CFH
#define _BRSFC_CV_OFF_RF3FTG
#define _BRSFC_CV_OFF_RF3XTG
#define _BRSFC_CV_OFF_RF4CFH
#define _BRSFC_CV_OFF_RF4XTG
#define _BRSFC_CV_OFF_RF90
#define _BRSFC_CV_OFF_RFCSSAT
#define _BRSFC_CV_OFF_RFFLP180
#define _BRSFC_CV_OFF_RFFLP180_THE
#define _BRSFC_CV_OFF_RFFLP90
#define _BRSFC_CV_OFF_RFFLP90_THE
#define _BRSFC_CV_OFF_RFFLP90R
#define _BRSFC_CV_OFF_RFFLP90R_THE
#define _BRSFC_CV_OFF_RFFRIR
#define _BRSFC_CV_OFF_RFFS
#define _BRSFC_CV_OFF_RFGIR01
#define _BRSFC_CV_OFF_RFGIR02
#define _BRSFC_CV_OFF_RFMONTIPUP
#define _BRSFC_CV_OFF_RFS5FPH
#define _BRSFC_CV_OFF_RFSE1
#define _BRSFC_CV_OFF_RFSE2
#define _BRSFC_CV_OFF_RFSE3
#define _BRSFC_CV_OFF_RFSE4
#define _BRSFC_CV_OFF_RFSE5
#define _BRSFC_CV_OFF_RFSE6
#define _BRSFC_CV_OFF_RFSSF
#define _BRSFC_CV_OFF_RFSSFH
#define _BRSFC_CV_OFF_RFSX1
#define _BRSFC_CV_OFF_RFSX2
#define _BRSFC_CV_OFF_RFSY1
#define _BRSFC_CV_OFF_RFSY2
#define _BRSFC_CV_OFF_RFSZ1
#define _BRSFC_CV_OFF_RFSZ2
#define _BRSFC_CV_OFF_RFTIPUP
#define _BRSFC_CV_OFF_THETARF1
#define _BRSFC_CV_OFFSET
#define _BRSFC_CV_OFFSET_RFGIR01
#define _BRSFC_CV_OFFSET_RFGIR02
#define _BRSFC_CV_OGSFMAX
#define _BRSFC_CV_OGSFMIN
#define _BRSFC_CV_OGSFX1
#define _BRSFC_CV_OGSFX2
#define _BRSFC_CV_OGSFX2_LIMIT_MIN
#define _BRSFC_CV_OGSFXW
#define _BRSFC_CV_OGSFXWEX
#define _BRSFC_CV_OGSFY
#define _BRSFC_CV_OGSFYK
#define _BRSFC_CV_OGSFZ
#define _BRSFC_CV_OGSFZK
#define _BRSFC_CV_OGSF_LIMIT_MAX
#define _BRSFC_CV_OGSF_LIMIT_MIN
#define _BRSFC_CV_OLD_PHASE
#define _BRSFC_CV_OMEGA_AMP
#define _BRSFC_CV_OMEGA_SCALE
#define _BRSFC_CV_OP3DCINE_FIESTA
#define _BRSFC_CV_OP3DCINE_SPGR
#define _BRSFC_CV_OP3DGRADWARP
#define _BRSFC_CV_OP4DFLOW
#define _BRSFC_CV_OPET
#define _BRSFC_CV_OPAB1
#define _BRSFC_CV_OPACCEL_CS_STRIDE
#define _BRSFC_CV_OPACCEL_KT_STRIDE
#define _BRSFC_CV_OPACCEL_MB_STRIDE
#define _BRSFC_CV_OPACCEL_PH_STRIDE
#define _BRSFC_CV_OPACCEL_SL_STRIDE
#define _BRSFC_CV_OPACCEL_T_STRIDE
#define _BRSFC_CV_OPACQO
#define _BRSFC_CV_OPACS
#define _BRSFC_CV_OPADVGATE
#define _BRSFC_CV_OPALLOWEDRESCANTIME
#define _BRSFC_CV_OPANATOMY
#define _BRSFC_CV_OPAPA
#define _BRSFC_CV_OPAPCSIIS
#define _BRSFC_CV_OPAPFLOW
#define _BRSFC_CV_OPAPHASES
#define _BRSFC_CV_OPARC
#define _BRSFC_CV_OPARR
#define _BRSFC_CV_OPARRMON
#define _BRSFC_CV_OPASCALCFOV
#define _BRSFC_CV_OPASL
#define _BRSFC_CV_OPASLPREP
#define _BRSFC_CV_OPASSET
#define _BRSFC_CV_OPASSETCAL
#define _BRSFC_CV_OPASSETSCAN
#define _BRSFC_CV_OPAUTO3DGRADWARP
#define _BRSFC_CV_OPAUTOBTI
#define _BRSFC_CV_OPAUTODIFNEXT2
#define _BRSFC_CV_OPAUTODIFNUMT2
#define _BRSFC_CV_OPAUTOETL
#define _BRSFC_CV_OPAUTOFLIP
#define _BRSFC_CV_OPAUTONECHO
#define _BRSFC_CV_OPAUTONEX
#define _BRSFC_CV_OPAUTONUMBVALS
#define _BRSFC_CV_OPAUTORBW
#define _BRSFC_CV_OPAUTOSLDELAY
#define _BRSFC_CV_OPAUTOSLQUANT
#define _BRSFC_CV_OPAUTOSUBTRACT
#define _BRSFC_CV_OPAUTOTDEL1
#define _BRSFC_CV_OPAUTOTE
#define _BRSFC_CV_OPAUTOTI
#define _BRSFC_CV_OPAUTOTISSUET1
#define _BRSFC_CV_OPAUTOTR
#define _BRSFC_CV_OPAUTOVPS
#define _BRSFC_CV_OPAXIAL_SLICE
#define _BRSFC_CV_OPBC
#define _BRSFC_CV_OPBILATERAL
#define _BRSFC_CV_OPBLIM
#define _BRSFC_CV_OPBRAVA
#define _BRSFC_CV_OPBRAVO
#define _BRSFC_CV_OPBREASTMRS
#define _BRSFC_CV_OPBREATHHOLD
#define _BRSFC_CV_OPBSP
#define _BRSFC_CV_OPBSPTI
#define _BRSFC_CV_OPBURSTMODE
#define _BRSFC_CV_OPBVAL
#define _BRSFC_CV_OPBWRT
#define _BRSFC_CV_OPCALDELAY
#define _BRSFC_CV_OPCALMODE
#define _BRSFC_CV_OPCALREQUIRED
#define _BRSFC_CV_OPCARDSEQ
#define _BRSFC_CV_OPCCSAT
#define _BRSFC_CV_OPCFSEL
#define _BRSFC_CV_OPCGATE
#define _BRSFC_CV_OPCGATETYPE
#define _BRSFC_CV_OPCHRATE
#define _BRSFC_CV_OPCINEIR
#define _BRSFC_CV_OPCLOCS
#define _BRSFC_CV_OPCMON
#define _BRSFC_CV_OPCOAX
#define _BRSFC_CV_OPCOLLAPSE
#define _BRSFC_CV_OPCOMPRESSEDSENSING
#define _BRSFC_CV_OPCONTRAST
#define _BRSFC_CV_OPCORONAL_SLICE
#define _BRSFC_CV_OPCOSMIC
#define _BRSFC_CV_OPCPHASES
#define _BRSFC_CV_OPCS
#define _BRSFC_CV_OPCUBE
#define _BRSFC_CV_OPDDA
#define _BRSFC_CV_OPDEPREP
#define _BRSFC_CV_OPDFAX3IN1
#define _BRSFC_CV_OPDFAXALL
#define _BRSFC_CV_OPDFAXTETRA
#define _BRSFC_CV_OPDFAXX
#define _BRSFC_CV_OPDFAXY
#define _BRSFC_CV_OPDFAXZ
#define _BRSFC_CV_OPDFM
#define _BRSFC_CV_OPDFMPRESCAN
#define _BRSFC_CV_OPDFSATHICK1
#define _BRSFC_CV_OPDFSATHICK2
#define _BRSFC_CV_OPDFSATHICK3
#define _BRSFC_CV_OPDFSATHICK4
#define _BRSFC_CV_OPDFSATHICK5
#define _BRSFC_CV_OPDFSATHICK6
#define _BRSFC_CV_OPDIFFUSE
#define _BRSFC_CV_OPDIFNEXT2
#define _BRSFC_CV_OPDIFNUMBVALUES
#define _BRSFC_CV_OPDIFNUMDIRS
#define _BRSFC_CV_OPDIFNUMT2
#define _BRSFC_CV_OPDIFPROCTYPE
#define _BRSFC_CV_OPDISCO
#define _BRSFC_CV_OPDIXON
#define _BRSFC_CV_OPDIXPROC
#define _BRSFC_CV_OPDOSE
#define _BRSFC_CV_OPDOUBLEIR
#define _BRSFC_CV_OPDRIVEMODE
#define _BRSFC_CV_OPDUALSPINECHO
#define _BRSFC_CV_OPDYNAPLAN
#define _BRSFC_CV_OPDYNAPLAN_MASK_PHASE
#define _BRSFC_CV_OPDYNAPLAN_NPHASES
#define _BRSFC_CV_OPDYNTG
#define _BRSFC_CV_OPECTRICKS
#define _BRSFC_CV_OPENTRY
#define _BRSFC_CV_OPEPI
#define _BRSFC_CV_OPETL
#define _BRSFC_CV_OPEXAMNUM
#define _BRSFC_CV_OPEXCITEMODE
#define _BRSFC_CV_OPEXOR
#define _BRSFC_CV_OPEXSATHICK1
#define _BRSFC_CV_OPEXSATHICK2
#define _BRSFC_CV_OPEXSATHICK3
#define _BRSFC_CV_OPEXSATHICK4
#define _BRSFC_CV_OPEXSATHICK5
#define _BRSFC_CV_OPEXSATHICK6
#define _BRSFC_CV_OPEXSATLEN1
#define _BRSFC_CV_OPEXSATLEN2
#define _BRSFC_CV_OPEXSATLEN3
#define _BRSFC_CV_OPEXSATLEN4
#define _BRSFC_CV_OPEXSATLEN5
#define _BRSFC_CV_OPEXSATLEN6
#define _BRSFC_CV_OPEXSATLOC1
#define _BRSFC_CV_OPEXSATLOC2
#define _BRSFC_CV_OPEXSATLOC3
#define _BRSFC_CV_OPEXSATLOC4
#define _BRSFC_CV_OPEXSATLOC5
#define _BRSFC_CV_OPEXSATLOC6
#define _BRSFC_CV_OPEXSATMASK
#define _BRSFC_CV_OPEXSATOFF1
#define _BRSFC_CV_OPEXSATOFF2
#define _BRSFC_CV_OPEXSATOFF3
#define _BRSFC_CV_OPEXSATOFF4
#define _BRSFC_CV_OPEXSATOFF5
#define _BRSFC_CV_OPEXSATOFF6
#define _BRSFC_CV_OPEXSATPARAL
#define _BRSFC_CV_OPFMRIPDTYPE
#define _BRSFC_CV_OPFAST
#define _BRSFC_CV_OPFAT
#define _BRSFC_CV_OPFATCL
#define _BRSFC_CV_OPFATWATER
#define _BRSFC_CV_OPFCAXIS
#define _BRSFC_CV_OPFCINE
#define _BRSFC_CV_OPFCOMP
#define _BRSFC_CV_OPFLAIR
#define _BRSFC_CV_OPFLAXALL
#define _BRSFC_CV_OPFLAXX
#define _BRSFC_CV_OPFLAXXA
#define _BRSFC_CV_OPFLAXY
#define _BRSFC_CV_OPFLAXYA
#define _BRSFC_CV_OPFLAXZ
#define _BRSFC_CV_OPFLAXZA
#define _BRSFC_CV_OPFLIP
#define _BRSFC_CV_OPFLRECON
#define _BRSFC_CV_OPFLUOROTRIGGER
#define _BRSFC_CV_OPFMRI
#define _BRSFC_CV_OPFOV
#define _BRSFC_CV_OPFPHASES
#define _BRSFC_CV_OPFR
#define _BRSFC_CV_OPFREQFOV
#define _BRSFC_CV_OPFULLTRAIN
#define _BRSFC_CV_OPFUS
#define _BRSFC_CV_OPGIRMODE
#define _BRSFC_CV_OPGRADMODE
#define _BRSFC_CV_OPGRX
#define _BRSFC_CV_OPGRXROI
#define _BRSFC_CV_OPHARMONIZE
#define _BRSFC_CV_OPHEADSCOUT
#define _BRSFC_CV_OPHOECC
#define _BRSFC_CV_OPHRATE
#define _BRSFC_CV_OPHREP
#define _BRSFC_CV_OPHYDRO
#define _BRSFC_CV_OPIDEALIQ
#define _BRSFC_CV_OPILEAVE
#define _BRSFC_CV_OPIMODE
#define _BRSFC_CV_OPINHANCE
#define _BRSFC_CV_OPINHSFLOW
#define _BRSFC_CV_OPINIT_STATE
#define _BRSFC_CV_OPINITTRIGDELAY
#define _BRSFC_CV_OPINRANGETR
#define _BRSFC_CV_OPINRANGETRMAX
#define _BRSFC_CV_OPINRANGETRMIN
#define _BRSFC_CV_OPIRMODE
#define _BRSFC_CV_OPIRPREP
#define _BRSFC_CV_OPJRMODE
#define _BRSFC_CV_OPLANDMARK
#define _BRSFC_CV_OPLAVA
#define _BRSFC_CV_OPLENAP
#define _BRSFC_CV_OPLENRL
#define _BRSFC_CV_OPLENSI
#define _BRSFC_CV_OPLOADPROTOCOL
#define _BRSFC_CV_OPLOCAP
#define _BRSFC_CV_OPLOCRL
#define _BRSFC_CV_OPLOCSI
#define _BRSFC_CV_OPMAGC
#define _BRSFC_CV_OPMAGIC
#define _BRSFC_CV_OPMART
#define _BRSFC_CV_OPMASK
#define _BRSFC_CV_OPMAVRIC
#define _BRSFC_CV_OPMB
#define _BRSFC_CV_OPMEDAL
#define _BRSFC_CV_OPMER2
#define _BRSFC_CV_OPMERGE
#define _BRSFC_CV_OPMINTEDIF
#define _BRSFC_CV_OPMONFOV
#define _BRSFC_CV_OPMONTHICK
#define _BRSFC_CV_OPMPH
#define _BRSFC_CV_OPMPHASES
#define _BRSFC_CV_OPMPRAGE
#define _BRSFC_CV_OPMSDE
#define _BRSFC_CV_OPMSDEAXX
#define _BRSFC_CV_OPMSDEAXY
#define _BRSFC_CV_OPMSDEAXZ
#define _BRSFC_CV_OPMT
#define _BRSFC_CV_OPMULTISTATION
#define _BRSFC_CV_OPNAV
#define _BRSFC_CV_OPNAVACCWIN
#define _BRSFC_CV_OPNAVAUTOACCWIN
#define _BRSFC_CV_OPNAVAUTOTRIGTIME
#define _BRSFC_CV_OPNAVMAXINTERVAL
#define _BRSFC_CV_OPNAVPSCPAUSE
#define _BRSFC_CV_OPNAVPSCTIME
#define _BRSFC_CV_OPNAVRRMEAS
#define _BRSFC_CV_OPNAVRRMEASRR
#define _BRSFC_CV_OPNAVRRMEASTIME
#define _BRSFC_CV_OPNAVSIGENHANCE
#define _BRSFC_CV_OPNAVSLTRACK
#define _BRSFC_CV_OPNAVTYPE
#define _BRSFC_CV_OPNBH
#define _BRSFC_CV_OPNCOILS
#define _BRSFC_CV_OPNECHO
#define _BRSFC_CV_OPNEWGEO
#define _BRSFC_CV_OPNEX
#define _BRSFC_CV_OPNNEX
#define _BRSFC_CV_OPNOPWRAP
#define _BRSFC_CV_OPNOSTATIONS
#define _BRSFC_CV_OPNRR
#define _BRSFC_CV_OPNRR_DDA
#define _BRSFC_CV_OPNSEG
#define _BRSFC_CV_OPNSHOTS
#define _BRSFC_CV_OPNSPOKES
#define _BRSFC_CV_OPNUMBVALS
#define _BRSFC_CV_OPNUMGIR
#define _BRSFC_CV_OPNUMGROUPS
#define _BRSFC_CV_OPNUMSYNBVALS
#define _BRSFC_CV_OPOBPLANE
#define _BRSFC_CV_OPOVERSAMPLINGFACTOR
#define _BRSFC_CV_OPOVL
#define _BRSFC_CV_OPPDGM_STR
#define _BRSFC_CV_OPPHASECYCLE
#define _BRSFC_CV_OPPHASEFOV
#define _BRSFC_CV_OPPHASEIMAGE
#define _BRSFC_CV_OPPHASES
#define _BRSFC_CV_OPPHCOR
#define _BRSFC_CV_OPPHSEN
#define _BRSFC_CV_OPPHYSPLANE
#define _BRSFC_CV_OPPLANE
#define _BRSFC_CV_OPPOMP
#define _BRSFC_CV_OPPOS
#define _BRSFC_CV_OPPOSTLABELDELAY
#define _BRSFC_CV_OPPRESCANOPT
#define _BRSFC_CV_OPPROJECT
#define _BRSFC_CV_OPPROMO
#define _BRSFC_CV_OPPROP
#define _BRSFC_CV_OPPROTRXMODE
#define _BRSFC_CV_OPPSCAPA
#define _BRSFC_CV_OPPSCSHIMTG
#define _BRSFC_CV_OPPSCVQUANT
#define _BRSFC_CV_OPPSD_TRIG
#define _BRSFC_CV_OPPSEQ
#define _BRSFC_CV_OPPTSIZE
#define _BRSFC_CV_OPPURE
#define _BRSFC_CV_OPPURECAL
#define _BRSFC_CV_OPQUICKSTEP
#define _BRSFC_CV_OPRAMPDIR
#define _BRSFC_CV_OPRBW
#define _BRSFC_CV_OPRBW2
#define _BRSFC_CV_OPREALTIME
#define _BRSFC_CV_OPRECT
#define _BRSFC_CV_OPREP_ACTIVE
#define _BRSFC_CV_OPREP_REST
#define _BRSFC_CV_OPRESEARCH
#define _BRSFC_CV_OPRGCALMODE
#define _BRSFC_CV_OPRLCSIIS
#define _BRSFC_CV_OPRLFLOW
#define _BRSFC_CV_OPRTARR
#define _BRSFC_CV_OPRTB0
#define _BRSFC_CV_OPRTBC
#define _BRSFC_CV_OPRTCARDSEQ
#define _BRSFC_CV_OPRTCGATE
#define _BRSFC_CV_OPRTPOINT
#define _BRSFC_CV_OPRTRATE
#define _BRSFC_CV_OPRTREP
#define _BRSFC_CV_OPRTTDEL1
#define _BRSFC_CV_OPRTTSEQ
#define _BRSFC_CV_OPSAGITTAL_SLICE
#define _BRSFC_CV_OPSARBURST
#define _BRSFC_CV_OPSARMODE
#define _BRSFC_CV_OPSAT
#define _BRSFC_CV_OPSATMASK
#define _BRSFC_CV_OPSATX
#define _BRSFC_CV_OPSATXLOC1
#define _BRSFC_CV_OPSATXLOC2
#define _BRSFC_CV_OPSATXTHICK
#define _BRSFC_CV_OPSATY
#define _BRSFC_CV_OPSATYLOC1
#define _BRSFC_CV_OPSATYLOC2
#define _BRSFC_CV_OPSATYTHICK
#define _BRSFC_CV_OPSATZ
#define _BRSFC_CV_OPSATZLOC1
#define _BRSFC_CV_OPSATZLOC2
#define _BRSFC_CV_OPSATZTHICK
#define _BRSFC_CV_OPSAVEDF
#define _BRSFC_CV_OPSCIC
#define _BRSFC_CV_OPSEPARATESYNB
#define _BRSFC_CV_OPSEPSERIES
#define _BRSFC_CV_OPSERIESNUM
#define _BRSFC_CV_OPSERIESSAVE
#define _BRSFC_CV_OPSICSIIS
#define _BRSFC_CV_OPSIFLOW
#define _BRSFC_CV_OPSILENT
#define _BRSFC_CV_OPSILENTLEVEL
#define _BRSFC_CV_OPSILENTMR
#define _BRSFC_CV_OPSLBLANK
#define _BRSFC_CV_OPSLDELAY
#define _BRSFC_CV_OPSLICE_ORDER
#define _BRSFC_CV_OPSLICECNT
#define _BRSFC_CV_OPSLINKY
#define _BRSFC_CV_OPSLLOCS
#define _BRSFC_CV_OPSLQUANT
#define _BRSFC_CV_OPSLSPACE
#define _BRSFC_CV_OPSLTHICK
#define _BRSFC_CV_OPSLZIP2
#define _BRSFC_CV_OPSLZIP4
#define _BRSFC_CV_OPSMARTPREP
#define _BRSFC_CV_OPSPECIR
#define _BRSFC_CV_OPSPF
#define _BRSFC_CV_OPSPIRAL
#define _BRSFC_CV_OPSQUARE
#define _BRSFC_CV_OPSRPREP
#define _BRSFC_CV_OPSSFSE
#define _BRSFC_CV_OPSSRF
#define _BRSFC_CV_OPSTATION
#define _BRSFC_CV_OPSTRESS
#define _BRSFC_CV_OPSWAN
#define _BRSFC_CV_OPSWIFT
#define _BRSFC_CV_OPT1FLAIR
#define _BRSFC_CV_OPT1MAP
#define _BRSFC_CV_OPT2FLAIR
#define _BRSFC_CV_OPT2MAP
#define _BRSFC_CV_OPT2PREP
#define _BRSFC_CV_OPT2PREPTE
#define _BRSFC_CV_OPTABENT
#define _BRSFC_CV_OPTAGANGLE
#define _BRSFC_CV_OPTAGGING
#define _BRSFC_CV_OPTAGSPC
#define _BRSFC_CV_OPTDEL1
#define _BRSFC_CV_OPTE
#define _BRSFC_CV_OPTE2
#define _BRSFC_CV_OPTEFW
#define _BRSFC_CV_OPTENSOR
#define _BRSFC_CV_OPTI
#define _BRSFC_CV_OPTIMAL_CHANNEL_COMBINE
#define _BRSFC_CV_OPTISSUET1
#define _BRSFC_CV_OPTLABEL
#define _BRSFC_CV_OPTLRDRF
#define _BRSFC_CV_OPTOUCH
#define _BRSFC_CV_OPTOUCHAMP
#define _BRSFC_CV_OPTOUCHAX
#define _BRSFC_CV_OPTOUCHCYC
#define _BRSFC_CV_OPTOUCHFREQ
#define _BRSFC_CV_OPTOUCHMEGFREQ
#define _BRSFC_CV_OPTOUCHTPHASES
#define _BRSFC_CV_OPTPHASES
#define _BRSFC_CV_OPTR
#define _BRSFC_CV_OPTRACQ
#define _BRSFC_CV_OPTRECOVERY
#define _BRSFC_CV_OPTRICKSDEL
#define _BRSFC_CV_OPTRICKSPAUSE
#define _BRSFC_CV_OPTRIP
#define _BRSFC_CV_OPTSEQ
#define _BRSFC_CV_OPUSER0
#define _BRSFC_CV_OPUSER1
#define _BRSFC_CV_OPUSER10
#define _BRSFC_CV_OPUSER11
#define _BRSFC_CV_OPUSER12
#define _BRSFC_CV_OPUSER13
#define _BRSFC_CV_OPUSER14
#define _BRSFC_CV_OPUSER15
#define _BRSFC_CV_OPUSER16
#define _BRSFC_CV_OPUSER17
#define _BRSFC_CV_OPUSER18
#define _BRSFC_CV_OPUSER19
#define _BRSFC_CV_OPUSER2
#define _BRSFC_CV_OPUSER20
#define _BRSFC_CV_OPUSER21
#define _BRSFC_CV_OPUSER22
#define _BRSFC_CV_OPUSER23
#define _BRSFC_CV_OPUSER24
#define _BRSFC_CV_OPUSER25
#define _BRSFC_CV_OPUSER26
#define _BRSFC_CV_OPUSER27
#define _BRSFC_CV_OPUSER28
#define _BRSFC_CV_OPUSER29
#define _BRSFC_CV_OPUSER3
#define _BRSFC_CV_OPUSER30
#define _BRSFC_CV_OPUSER31
#define _BRSFC_CV_OPUSER32
#define _BRSFC_CV_OPUSER33
#define _BRSFC_CV_OPUSER34
#define _BRSFC_CV_OPUSER35
#define _BRSFC_CV_OPUSER36
#define _BRSFC_CV_OPUSER37
#define _BRSFC_CV_OPUSER38
#define _BRSFC_CV_OPUSER39
#define _BRSFC_CV_OPUSER4
#define _BRSFC_CV_OPUSER40
#define _BRSFC_CV_OPUSER41
#define _BRSFC_CV_OPUSER42
#define _BRSFC_CV_OPUSER43
#define _BRSFC_CV_OPUSER44
#define _BRSFC_CV_OPUSER45
#define _BRSFC_CV_OPUSER46
#define _BRSFC_CV_OPUSER47
#define _BRSFC_CV_OPUSER48
#define _BRSFC_CV_OPUSER5
#define _BRSFC_CV_OPUSER6
#define _BRSFC_CV_OPUSER7
#define _BRSFC_CV_OPUSER8
#define _BRSFC_CV_OPUSER9
#define _BRSFC_CV_OPUSER_USAGE_TAG
#define _BRSFC_CV_OPVBW
#define _BRSFC_CV_OPVENC
#define _BRSFC_CV_OPVENOUS
#define _BRSFC_CV_OPVEST
#define _BRSFC_CV_OPVIBRANT
#define _BRSFC_CV_OPVIEW_ORDER
#define _BRSFC_CV_OPVPS
#define _BRSFC_CV_OPVQUANT
#define _BRSFC_CV_OPVRG
#define _BRSFC_CV_OPVSPHASES
#define _BRSFC_CV_OPVTHICK
#define _BRSFC_CV_OPWARMUP
#define _BRSFC_CV_OPWATER
#define _BRSFC_CV_OPWEIGHT
#define _BRSFC_CV_OPXRES
#define _BRSFC_CV_OPYRES
#define _BRSFC_CV_OPZIP1024
#define _BRSFC_CV_OPZIP512
#define _BRSFC_CV_OPZOOM_COIL_IND
#define _BRSFC_CV_OPZOOM_DIST_AX
#define _BRSFC_CV_OPZOOM_DIST_COR
#define _BRSFC_CV_OPZOOM_DIST_SAG
#define _BRSFC_CV_OPZOOM_FOV_XY
#define _BRSFC_CV_OPZOOM_FOV_Z
#define _BRSFC_CV_OSFPR_FLAG
#define _BRSFC_CV_OSFP_DDA
#define _BRSFC_CV_OSFP_DEBUG
#define _BRSFC_CV_OSFP_DELAY_FACTOR
#define _BRSFC_CV_OSFP_FLAG
#define _BRSFC_CV_OSFP_WEIGHT
#define _BRSFC_CV_OSFP_WEIGHT_ACT
#define _BRSFC_CV_OSFP_WEIGHT_GRAD
#define _BRSFC_CV_OSFPSD_FLAG
#define _BRSFC_CV_OVERRIDE_OPCALREQUIRED
#define _BRSFC_CV_PASS_THRU_MODE
#define _BRSFC_CV_PASSTIME
#define _BRSFC_CV_PAUSE_AFTER_MASK_FLAG
#define _BRSFC_CV_PC_CONST
#define _BRSFC_CV_PC_MODE
#define _BRSFC_CV_PCFIESTA_FLAG
#define _BRSFC_CV_PCFIESTA_RF
#define _BRSFC_CV_PE_ACQ1
#define _BRSFC_CV_PE_ACQ2
#define _BRSFC_CV_PE_ON
#define _BRSFC_CV_PEAKPHASEINDEX
#define _BRSFC_CV_PER_GX1
#define _BRSFC_CV_PER_GY1
#define _BRSFC_CV_PER_GY1R
#define _BRSFC_CV_PER_GZCOMB
#define _BRSFC_CV_PER_GZCOMBHTR
#define _BRSFC_CV_PER_GZP
#define _BRSFC_CV_PER_GZPHTR
#define _BRSFC_CV_PER_GZVLW
#define _BRSFC_CV_PFKR_FLAG
#define _BRSFC_CV_PFKR_FRACTION
#define _BRSFC_CV_PFKR_FRACTION_ACT
#define _BRSFC_CV_PFKR_YZ_ENABLE
#define _BRSFC_CV_PFKR_YZ_FLAG
#define _BRSFC_CV_PFKY_FRACTION
#define _BRSFC_CV_PFKY_TOTAL_UNACCEL
#define _BRSFC_CV_PFKYZ2KR_FLAG
#define _BRSFC_CV_PFKZ_FLAG
#define _BRSFC_CV_PFKZ_FRACTION
#define _BRSFC_CV_PFKZ_FRACTION_MIN
#define _BRSFC_CV_PFKZ_HNOVER
#define _BRSFC_CV_PFKZ_REVERSE_SEQ
#define _BRSFC_CV_PFKZ_SEGMENTS
#define _BRSFC_CV_PFKZ_TOTAL
#define _BRSFC_CV_PFKZ_TOTAL_UNACCEL
#define _BRSFC_CV_PFKZ_VIEWS_PER_SEGMENT
#define _BRSFC_CV_PFKZ_VPS_MAX
#define _BRSFC_CV_PG_BETA
#define _BRSFC_CV_PGEN_FOR_DBDT_OPT
#define _BRSFC_CV_PHASE_COL
#define _BRSFC_CV_PHASE_COR
#define _BRSFC_CV_PHASE_CYCLES
#define _BRSFC_CV_PHASE_ORDER
#define _BRSFC_CV_PHASE_RFFLP180
#define _BRSFC_CV_PHASEFOVGT1_FLAG
#define _BRSFC_CV_PHASERES
#define _BRSFC_CV_PHMASK
#define _BRSFC_CV_PHORDER
#define _BRSFC_CV_PHYGRD
#define _BRSFC_CV_PHYS_REC_RESOLUTION
#define _BRSFC_CV_PHYS_RECORD_CHANNELSEL
#define _BRSFC_CV_PHYS_RECORD_FLAG
#define _BRSFC_CV_PI1STSHIMB
#define _BRSFC_CV_PI2DMDE
#define _BRSFC_CV_PI3DGRADWARPNUB
#define _BRSFC_CV_PI_NEG_SP
#define _BRSFC_CV_PI_PIPHASFOVNUB
#define _BRSFC_CV_PIACCEL_CS_STEP
#define _BRSFC_CV_PIACCEL_CS_STRIDE
#define _BRSFC_CV_PIACCEL_CSEDIT
#define _BRSFC_CV_PIACCEL_CSNUB
#define _BRSFC_CV_PIACCEL_CSVAL2
#define _BRSFC_CV_PIACCEL_CSVAL3
#define _BRSFC_CV_PIACCEL_CSVAL4
#define _BRSFC_CV_PIACCEL_CSVAL5
#define _BRSFC_CV_PIACCEL_CSVAL6
#define _BRSFC_CV_PIACCEL_KT_STEP
#define _BRSFC_CV_PIACCEL_KT_STRIDE
#define _BRSFC_CV_PIACCEL_KTEDIT
#define _BRSFC_CV_PIACCEL_KTNUB
#define _BRSFC_CV_PIACCEL_KTVAL2
#define _BRSFC_CV_PIACCEL_KTVAL3
#define _BRSFC_CV_PIACCEL_KTVAL4
#define _BRSFC_CV_PIACCEL_KTVAL5
#define _BRSFC_CV_PIACCEL_KTVAL6
#define _BRSFC_CV_PIACCEL_MB_STEP
#define _BRSFC_CV_PIACCEL_MB_STRIDE
#define _BRSFC_CV_PIACCEL_MBEDIT
#define _BRSFC_CV_PIACCEL_MBNUB
#define _BRSFC_CV_PIACCEL_MBVAL2
#define _BRSFC_CV_PIACCEL_MBVAL3
#define _BRSFC_CV_PIACCEL_MBVAL4
#define _BRSFC_CV_PIACCEL_MBVAL5
#define _BRSFC_CV_PIACCEL_MBVAL6
#define _BRSFC_CV_PIACCEL_PH_STEP
#define _BRSFC_CV_PIACCEL_PH_STRIDE
#define _BRSFC_CV_PIACCEL_PHEDIT
#define _BRSFC_CV_PIACCEL_PHNUB
#define _BRSFC_CV_PIACCEL_PHVAL2
#define _BRSFC_CV_PIACCEL_PHVAL3
#define _BRSFC_CV_PIACCEL_PHVAL4
#define _BRSFC_CV_PIACCEL_PHVAL5
#define _BRSFC_CV_PIACCEL_PHVAL6
#define _BRSFC_CV_PIACCEL_SL_STEP
#define _BRSFC_CV_PIACCEL_SL_STRIDE
#define _BRSFC_CV_PIACCEL_SLEDIT
#define _BRSFC_CV_PIACCEL_SLNUB
#define _BRSFC_CV_PIACCEL_SLVAL2
#define _BRSFC_CV_PIACCEL_SLVAL3
#define _BRSFC_CV_PIACCEL_SLVAL4
#define _BRSFC_CV_PIACCEL_SLVAL5
#define _BRSFC_CV_PIACCEL_SLVAL6
#define _BRSFC_CV_PIACCEL_T_STEP
#define _BRSFC_CV_PIACCEL_T_STRIDE
#define _BRSFC_CV_PIACCEL_TEDIT
#define _BRSFC_CV_PIACCEL_TNUB
#define _BRSFC_CV_PIACCEL_TOTAL_STRIDE
#define _BRSFC_CV_PIACCEL_TVAL2
#define _BRSFC_CV_PIACCEL_TVAL3
#define _BRSFC_CV_PIACCEL_TVAL4
#define _BRSFC_CV_PIACCEL_TVAL5
#define _BRSFC_CV_PIACCEL_TVAL6
#define _BRSFC_CV_PIACCELSCRN
#define _BRSFC_CV_PIACQNUB
#define _BRSFC_CV_PIACSDEFVAL
#define _BRSFC_CV_PIACSNUB
#define _BRSFC_CV_PIACSVAL2
#define _BRSFC_CV_PIACSVAL3
#define _BRSFC_CV_PIACSVAL4
#define _BRSFC_CV_PIACSVAL5
#define _BRSFC_CV_PIACSVAL6
#define _BRSFC_CV_PIACTIM
#define _BRSFC_CV_PIADDINUB
#define _BRSFC_CV_PIADDSCANNUB
#define _BRSFC_CV_PIADDSCANTYPE
#define _BRSFC_CV_PIADVISE
#define _BRSFC_CV_PIADVT2MAP
#define _BRSFC_CV_PIAIT
#define _BRSFC_CV_PIALLOWEDRESCANTIMENUB
#define _BRSFC_CV_PIAMNUB
#define _BRSFC_CV_PIAPCSI
#define _BRSFC_CV_PIAPHASDEFVAL
#define _BRSFC_CV_PIAPHASENUB
#define _BRSFC_CV_PIAPHASEVAL2
#define _BRSFC_CV_PIAPHASEVAL3
#define _BRSFC_CV_PIAPHASEVAL4
#define _BRSFC_CV_PIAPX
#define _BRSFC_CV_PIAPXPRFACC
#define _BRSFC_CV_PIAPXPRFRES
#define _BRSFC_CV_PIAPXPRFSTEPNUB
#define _BRSFC_CV_PIAPXPRFSTEPVAL1
#define _BRSFC_CV_PIAPXPRFSTEPVAL2
#define _BRSFC_CV_PIARCCOILRESTRICT
#define _BRSFC_CV_PIASAR
#define _BRSFC_CV_PIASSETOVERRIDE
#define _BRSFC_CV_PIASSETSCRN
#define _BRSFC_CV_PIAUTOBSPTI
#define _BRSFC_CV_PIAUTOETL
#define _BRSFC_CV_PIAUTOFA
#define _BRSFC_CV_PIAUTOIRBANDS
#define _BRSFC_CV_PIAUTONAVTRACKER
#define _BRSFC_CV_PIAUTOPAUSE
#define _BRSFC_CV_PIAUTOPHASENUB
#define _BRSFC_CV_PIAUTOSTEP
#define _BRSFC_CV_PIAUTOTI
#define _BRSFC_CV_PIAUTOTRMODE
#define _BRSFC_CV_PIAUTOVOICE
#define _BRSFC_CV_PIB1RMS
#define _BRSFC_CV_PIBBANDFILT
#define _BRSFC_CV_PIBREATHHOLDNUB
#define _BRSFC_CV_PIBSPTIDEFVAL
#define _BRSFC_CV_PIBSPTINUB
#define _BRSFC_CV_PIBSPTIVAL2
#define _BRSFC_CV_PIBSPTIVAL3
#define _BRSFC_CV_PIBSPTIVAL4
#define _BRSFC_CV_PIBSPTIVAL5
#define _BRSFC_CV_PIBSPTIVAL6
#define _BRSFC_CV_PIBURSTCOOLTIME
#define _BRSFC_CV_PIBURSTMODE
#define _BRSFC_CV_PIBVAL2
#define _BRSFC_CV_PIBVAL3
#define _BRSFC_CV_PIBVAL4
#define _BRSFC_CV_PIBVALSTAB
#define _BRSFC_CV_PIBVNUB
#define _BRSFC_CV_PICALMODE
#define _BRSFC_CV_PICALMODENUB
#define _BRSFC_CV_PICASAR
#define _BRSFC_CV_PICCSAT_OBL
#define _BRSFC_CV_PICCSATNUB
#define _BRSFC_CV_PICHEMSATOPT
#define _BRSFC_CV_PICHOP
#define _BRSFC_CV_PICINEIPROT
#define _BRSFC_CV_PICLCKCNT
#define _BRSFC_CV_PICOILFASTSWITCHREQUIRED
#define _BRSFC_CV_PICONTRASTWARNING
#define _BRSFC_CV_PICS
#define _BRSFC_CV_PICSIFOV
#define _BRSFC_CV_PICSIMODE
#define _BRSFC_CV_PIDBDTPER
#define _BRSFC_CV_PIDBDTTS
#define _BRSFC_CV_PIDDANUB
#define _BRSFC_CV_PIDEFADDIMG
#define _BRSFC_CV_PIDEFALLOWEDRESCANTIME
#define _BRSFC_CV_PIDEFARR
#define _BRSFC_CV_PIDEFBVAL
#define _BRSFC_CV_PIDEFCALDELAY
#define _BRSFC_CV_PIDEFEXCITEMODE
#define _BRSFC_CV_PIDEFFCAXIS
#define _BRSFC_CV_PIDEFFLAX
#define _BRSFC_CV_PIDEFFLRC
#define _BRSFC_CV_PIDEFNAVACCWIN
#define _BRSFC_CV_PIDEFNAVAUTOACCWIN
#define _BRSFC_CV_PIDEFNAVAUTOTRIGTIME
#define _BRSFC_CV_PIDEFNAVMAXINTERVAL
#define _BRSFC_CV_PIDEFNAVPSCPAUSE
#define _BRSFC_CV_PIDEFNAVPSCTIME
#define _BRSFC_CV_PIDEFNAVRRMEAS
#define _BRSFC_CV_PIDEFNAVRRMEASTIME
#define _BRSFC_CV_PIDEFNAVSIGENHANCE
#define _BRSFC_CV_PIDEFNAVSLTRACK
#define _BRSFC_CV_PIDEFNAVTYPE
#define _BRSFC_CV_PIDEFNBH
#define _BRSFC_CV_PIDEFOVL
#define _BRSFC_CV_PIDEFPHASSET
#define _BRSFC_CV_PIDEFPOSTLABELDELAY
#define _BRSFC_CV_PIDEFPROJ
#define _BRSFC_CV_PIDEFRAMP
#define _BRSFC_CV_PIDEFRBW
#define _BRSFC_CV_PIDEFRTREP
#define _BRSFC_CV_PIDEFSLASSET
#define _BRSFC_CV_PIDEFSLQ
#define _BRSFC_CV_PIDEFTOUCHAMP
#define _BRSFC_CV_PIDEFTOUCHAX
#define _BRSFC_CV_PIDEFTOUCHCYC
#define _BRSFC_CV_PIDEFTOUCHFREQ
#define _BRSFC_CV_PIDEFTOUCHMEGFREQ
#define _BRSFC_CV_PIDEFTOUCHTPHASES
#define _BRSFC_CV_PIDFMONFOV
#define _BRSFC_CV_PIDFMONTHICK
#define _BRSFC_CV_PIDIATDEL1
#define _BRSFC_CV_PIDIFAVGNEX
#define _BRSFC_CV_PIDIFAXNUB
#define _BRSFC_CV_PIDIFFMODE
#define _BRSFC_CV_PIDIFFPROCTYPE
#define _BRSFC_CV_PIDIFNEXT2NUB
#define _BRSFC_CV_PIDIFNEXT2VAL2
#define _BRSFC_CV_PIDIFNEXT2VAL3
#define _BRSFC_CV_PIDIFNEXT2VAL4
#define _BRSFC_CV_PIDIFNEXT2VAL5
#define _BRSFC_CV_PIDIFNEXT2VAL6
#define _BRSFC_CV_PIDIFNEXTAB
#define _BRSFC_CV_PIDIFNUMDIRSDEFVAL
#define _BRSFC_CV_PIDIFNUMDIRSNUB
#define _BRSFC_CV_PIDIFNUMDIRSVAL2
#define _BRSFC_CV_PIDIFNUMDIRSVAL3
#define _BRSFC_CV_PIDIFNUMDIRSVAL4
#define _BRSFC_CV_PIDIFNUMT2DEFVAL
#define _BRSFC_CV_PIDIFNUMT2NUB
#define _BRSFC_CV_PIDIFNUMT2VAL2
#define _BRSFC_CV_PIDIFNUMT2VAL3
#define _BRSFC_CV_PIDIFNUMT2VAL4
#define _BRSFC_CV_PIDIFPAGE
#define _BRSFC_CV_PIDIFRECNUB
#define _BRSFC_CV_PIDIXPROC
#define _BRSFC_CV_PIDLTIME
#define _BRSFC_CV_PIDMODE
#define _BRSFC_CV_PIDOSHIM
#define _BRSFC_CV_PIDOTG
#define _BRSFC_CV_PIDRIVEMODENUB
#define _BRSFC_CV_PIDUALSPINECHONUB
#define _BRSFC_CV_PIDYNTGNUB
#define _BRSFC_CV_PIECHDEFVAL
#define _BRSFC_CV_PIECHNUB
#define _BRSFC_CV_PIECHVAL2
#define _BRSFC_CV_PIECHVAL3
#define _BRSFC_CV_PIECHVAL4
#define _BRSFC_CV_PIECHVAL5
#define _BRSFC_CV_PIECHVAL6
#define _BRSFC_CV_PIEFFBLADEWIDTH
#define _BRSFC_CV_PIEFFBLADEWIDTHDEFVAL
#define _BRSFC_CV_PIEFFBLADEWIDTHNUB
#define _BRSFC_CV_PIESAR
#define _BRSFC_CV_PIESP
#define _BRSFC_CV_PIETLNUB
#define _BRSFC_CV_PIETLVAL2
#define _BRSFC_CV_PIETLVAL3
#define _BRSFC_CV_PIETLVAL4
#define _BRSFC_CV_PIETLVAL5
#define _BRSFC_CV_PIETLVAL6
#define _BRSFC_CV_PIETR
#define _BRSFC_CV_PIEXCITEMODENUB
#define _BRSFC_CV_PIFAMODE
#define _BRSFC_CV_PIFANUB
#define _BRSFC_CV_PIFAVAL2
#define _BRSFC_CV_PIFAVAL3
#define _BRSFC_CV_PIFAVAL4
#define _BRSFC_CV_PIFAVAL5
#define _BRSFC_CV_PIFAVAL6
#define _BRSFC_CV_PIFCINEDEFVAL
#define _BRSFC_CV_PIFCINENUB
#define _BRSFC_CV_PIFCINEVAL2
#define _BRSFC_CV_PIFCINEVAL3
#define _BRSFC_CV_PIFCINEVAL4
#define _BRSFC_CV_PIFILT4
#define _BRSFC_CV_PIFILT5
#define _BRSFC_CV_PIFILT6
#define _BRSFC_CV_PIFILT7
#define _BRSFC_CV_PIFLANUB
#define _BRSFC_CV_PIFLOSUP
#define _BRSFC_CV_PIFLRCNUB
#define _BRSFC_CV_PIFMRISCRN
#define _BRSFC_CV_PIFORKVRGF
#define _BRSFC_CV_PIFOVNUB
#define _BRSFC_CV_PIFOVVAL2
#define _BRSFC_CV_PIFOVVAL3
#define _BRSFC_CV_PIFOVVAL4
#define _BRSFC_CV_PIFOVVAL5
#define _BRSFC_CV_PIFOVVAL6
#define _BRSFC_CV_PIFPHASENUB
#define _BRSFC_CV_PIFPHASEVAL2
#define _BRSFC_CV_PIFPHASEVAL3
#define _BRSFC_CV_PIFPHASEVAL4
#define _BRSFC_CV_PIFPHASEVAL5
#define _BRSFC_CV_PIFPHASEVAL6
#define _BRSFC_CV_PIFRACTECHO
#define _BRSFC_CV_PIFRAMERATE
#define _BRSFC_CV_PIFRAMERATENUB
#define _BRSFC_CV_PIFREQFOVNUB
#define _BRSFC_CV_PIFSEFCNUB
#define _BRSFC_CV_PIGEOSROT
#define _BRSFC_CV_PIGIRDEFTHICK
#define _BRSFC_CV_PIGIRMODE
#define _BRSFC_CV_PIGIRSCRN
#define _BRSFC_CV_PIGRADCOIL
#define _BRSFC_CV_PIHARMONIZENUB
#define _BRSFC_CV_PIHOECCNUB
#define _BRSFC_CV_PIHOECCVIS
#define _BRSFC_CV_PIHREPNUB
#define _BRSFC_CV_PIHREPVAL2
#define _BRSFC_CV_PIHREPVAL3
#define _BRSFC_CV_PIHREPVAL4
#define _BRSFC_CV_PIHREPVAL5
#define _BRSFC_CV_PIHREPVAL6
#define _BRSFC_CV_PIHSAR
#define _BRSFC_CV_PIIMAGES
#define _BRSFC_CV_PIIMGOPTLIST
#define _BRSFC_CV_PIIMGOPTVAL2
#define _BRSFC_CV_PIIMGOPTVAL3
#define _BRSFC_CV_PIIMGOPTVAL4
#define _BRSFC_CV_PIINITSTATNUB
#define _BRSFC_CV_PIINPLANERES
#define _BRSFC_CV_PIINRANGETRMAX
#define _BRSFC_CV_PIINRANGETRMIN
#define _BRSFC_CV_PIINVERTFNUB
#define _BRSFC_CV_PIINVERTFVIS
#define _BRSFC_CV_PIISIL
#define _BRSFC_CV_PIISNUB
#define _BRSFC_CV_PIISVAL2
#define _BRSFC_CV_PIISVAL3
#define _BRSFC_CV_PIISVAL4
#define _BRSFC_CV_PIISVAL5
#define _BRSFC_CV_PIISVAL6
#define _BRSFC_CV_PIISVALDEF
#define _BRSFC_CV_PIKT
#define _BRSFC_CV_PILANDMARK
#define _BRSFC_CV_PILOCNUB
#define _BRSFC_CV_PILOCVAL2
#define _BRSFC_CV_PILOCVAL3
#define _BRSFC_CV_PILOCVAL4
#define _BRSFC_CV_PILOCVAL5
#define _BRSFC_CV_PILOCVAL6
#define _BRSFC_CV_PIMB
#define _BRSFC_CV_PIMINTEDIFDEF
#define _BRSFC_CV_PIMINTEDIFNUB
#define _BRSFC_CV_PIMIXTIME
#define _BRSFC_CV_PIMONFOVNUB
#define _BRSFC_CV_PIMONFOVVAL2
#define _BRSFC_CV_PIMONFOVVAL3
#define _BRSFC_CV_PIMONFOVVAL4
#define _BRSFC_CV_PIMONITOR
#define _BRSFC_CV_PIMONTHICKNUB
#define _BRSFC_CV_PIMONTHICKVAL2
#define _BRSFC_CV_PIMONTHICKVAL3
#define _BRSFC_CV_PIMONTHICKVAL4
#define _BRSFC_CV_PIMPHSCRN
#define _BRSFC_CV_PIMRSAPS1
#define _BRSFC_CV_PIMRSAPS10
#define _BRSFC_CV_PIMRSAPS11
#define _BRSFC_CV_PIMRSAPS12
#define _BRSFC_CV_PIMRSAPS13
#define _BRSFC_CV_PIMRSAPS14
#define _BRSFC_CV_PIMRSAPS15
#define _BRSFC_CV_PIMRSAPS2
#define _BRSFC_CV_PIMRSAPS3
#define _BRSFC_CV_PIMRSAPS4
#define _BRSFC_CV_PIMRSAPS5
#define _BRSFC_CV_PIMRSAPS6
#define _BRSFC_CV_PIMRSAPS7
#define _BRSFC_CV_PIMRSAPS8
#define _BRSFC_CV_PIMRSAPS9
#define _BRSFC_CV_PIMRSAPSFLG
#define _BRSFC_CV_PIMSCAN
#define _BRSFC_CV_PIMSDEAXNUB
#define _BRSFC_CV_PIMULTIGROUP
#define _BRSFC_CV_PIMULTISLAB
#define _BRSFC_CV_PIMULTISTATION
#define _BRSFC_CV_PINAVACCWINNUB
#define _BRSFC_CV_PINAVACCWINVAL2
#define _BRSFC_CV_PINAVACCWINVAL3
#define _BRSFC_CV_PINAVACCWINVAL4
#define _BRSFC_CV_PINAVAUTOACCWINNUB
#define _BRSFC_CV_PINAVAUTOTRIGTIMENUB
#define _BRSFC_CV_PINAVAUTOTRIGTIMEVAL2
#define _BRSFC_CV_PINAVAUTOTRIGTIMEVAL3
#define _BRSFC_CV_PINAVAUTOTRIGTIMEVAL4
#define _BRSFC_CV_PINAVMAXINTERVALNUB
#define _BRSFC_CV_PINAVMAXINTERVALVAL2
#define _BRSFC_CV_PINAVMAXINTERVALVAL3
#define _BRSFC_CV_PINAVMAXINTERVALVAL4
#define _BRSFC_CV_PINAVMAXRR
#define _BRSFC_CV_PINAVPSCPAUSENUB
#define _BRSFC_CV_PINAVPSCTIMENUB
#define _BRSFC_CV_PINAVPSCTIMEVAL2
#define _BRSFC_CV_PINAVPSCTIMEVAL3
#define _BRSFC_CV_PINAVPSCTIMEVAL4
#define _BRSFC_CV_PINAVRRADJUST
#define _BRSFC_CV_PINAVRRMEASMAXSL
#define _BRSFC_CV_PINAVRRMEASNUB
#define _BRSFC_CV_PINAVRRMEASRTREP
#define _BRSFC_CV_PINAVRRMEASTIMENUB
#define _BRSFC_CV_PINAVRRMEASTIMEVAL2
#define _BRSFC_CV_PINAVRRMEASTIMEVAL3
#define _BRSFC_CV_PINAVRRMEASTIMEVAL4
#define _BRSFC_CV_PINAVSIGENHANCENUB
#define _BRSFC_CV_PINAVSLTRACKNUB
#define _BRSFC_CV_PINAVTYPENUB
#define _BRSFC_CV_PINBH
#define _BRSFC_CV_PINBHNUB
#define _BRSFC_CV_PINECHO
#define _BRSFC_CV_PINEX
#define _BRSFC_CV_PINEXNUB
#define _BRSFC_CV_PINEXVAL2
#define _BRSFC_CV_PINEXVAL3
#define _BRSFC_CV_PINEXVAL4
#define _BRSFC_CV_PINEXVAL5
#define _BRSFC_CV_PINEXVAL6
#define _BRSFC_CV_PINOADC
#define _BRSFC_CV_PINOFREQOFFSET
#define _BRSFC_CV_PINOLR
#define _BRSFC_CV_PINSEGNUB
#define _BRSFC_CV_PINSEGVAL2
#define _BRSFC_CV_PINSEGVAL3
#define _BRSFC_CV_PINSEGVAL4
#define _BRSFC_CV_PINSEGVAL5
#define _BRSFC_CV_PINSLICES
#define _BRSFC_CV_PINSPOKESDEFVAL
#define _BRSFC_CV_PINSPOKESNUB
#define _BRSFC_CV_PINSPOKESSTEP
#define _BRSFC_CV_PINSPOKESVAL2
#define _BRSFC_CV_PINSPOKESVAL3
#define _BRSFC_CV_PINSPOKESVAL4
#define _BRSFC_CV_PINSPOKESVAL5
#define _BRSFC_CV_PINSPOKESVAL6
#define _BRSFC_CV_PINUMARTLEVELS
#define _BRSFC_CV_PINUMBNUB
#define _BRSFC_CV_PINUMBVAL2
#define _BRSFC_CV_PINUMBVAL3
#define _BRSFC_CV_PINUMBVAL4
#define _BRSFC_CV_PINUMBVAL5
#define _BRSFC_CV_PINUMBVAL6
#define _BRSFC_CV_PINUMGIR
#define _BRSFC_CV_PINUMSYNBNUB
#define _BRSFC_CV_PINUMSYNBVAL2
#define _BRSFC_CV_PINUMSYNBVAL3
#define _BRSFC_CV_PINUMSYNBVAL4
#define _BRSFC_CV_PINUMSYNBVAL5
#define _BRSFC_CV_PINUMSYNBVAL6
#define _BRSFC_CV_PIOVERLAP
#define _BRSFC_CV_PIOVERSAMPLINGFACTORDEFVAL
#define _BRSFC_CV_PIOVERSAMPLINGFACTORNUB
#define _BRSFC_CV_PIOVERSAMPLINGFACTORVAL2
#define _BRSFC_CV_PIOVERSAMPLINGFACTORVAL3
#define _BRSFC_CV_PIOVERSAMPLINGFACTORVAL4
#define _BRSFC_CV_PIOVERSAMPLINGFACTORVAL5
#define _BRSFC_CV_PIOVERSAMPLINGFACTORVAL6
#define _BRSFC_CV_PIOVLNUB
#define _BRSFC_CV_PIPAUNUB
#define _BRSFC_CV_PIPAUTYPE
#define _BRSFC_CV_PIPAUVAL2
#define _BRSFC_CV_PIPAUVAL3
#define _BRSFC_CV_PIPAUVAL4
#define _BRSFC_CV_PIPAUVAL5
#define _BRSFC_CV_PIPAUVAL6
#define _BRSFC_CV_PIPCTOVL
#define _BRSFC_CV_PIPDHS_ACTIVE
#define _BRSFC_CV_PIPHASEIMAGENUB
#define _BRSFC_CV_PIPHASEIMAGEVAL2
#define _BRSFC_CV_PIPHASEIMAGEVAL3
#define _BRSFC_CV_PIPHASEIMAGEVAL4
#define _BRSFC_CV_PIPHASENUB
#define _BRSFC_CV_PIPHASFOVNUB
#define _BRSFC_CV_PIPHASFOVNUB2
#define _BRSFC_CV_PIPHASFOVVAL1
#define _BRSFC_CV_PIPHASFOVVAL2
#define _BRSFC_CV_PIPHASFOVVAL3
#define _BRSFC_CV_PIPHASFOVVAL4
#define _BRSFC_CV_PIPHASFOVVAL5
#define _BRSFC_CV_PIPHASFOVVAL6
#define _BRSFC_CV_PIPHASSETNUB
#define _BRSFC_CV_PIPHASSETVAL1
#define _BRSFC_CV_PIPHASSETVAL2
#define _BRSFC_CV_PIPHASSETVAL3
#define _BRSFC_CV_PIPHASSETVAL4
#define _BRSFC_CV_PIPHSLNUB
#define _BRSFC_CV_PIPOSTLABELDELAY2
#define _BRSFC_CV_PIPOSTLABELDELAY3
#define _BRSFC_CV_PIPOSTLABELDELAY4
#define _BRSFC_CV_PIPOSTLABELDELAY5
#define _BRSFC_CV_PIPOSTLABELDELAY6
#define _BRSFC_CV_PIPOSTLABELDELAYNUB
#define _BRSFC_CV_PIPROJNUB
#define _BRSFC_CV_PIPSAR
#define _BRSFC_CV_PIPSCDEF
#define _BRSFC_CV_PIPSCOPTNUB
#define _BRSFC_CV_PIPSCSHIMTGNUB
#define _BRSFC_CV_PIPSCVOL
#define _BRSFC_CV_PIPSDTRIGNUB
#define _BRSFC_CV_PIPURE
#define _BRSFC_CV_PIRAMPNUB
#define _BRSFC_CV_PIRBWPAGE
#define _BRSFC_CV_PIRBWPERPIX
#define _BRSFC_CV_PIRCB2NUB
#define _BRSFC_CV_PIRCB2VAL2
#define _BRSFC_CV_PIRCB2VAL3
#define _BRSFC_CV_PIRCB2VAL4
#define _BRSFC_CV_PIRCB2VAL5
#define _BRSFC_CV_PIRCB2VAL6
#define _BRSFC_CV_PIRCBNUB
#define _BRSFC_CV_PIRCBVAL2
#define _BRSFC_CV_PIRCBVAL3
#define _BRSFC_CV_PIRCBVAL4
#define _BRSFC_CV_PIRCBVAL5
#define _BRSFC_CV_PIRCBVAL6
#define _BRSFC_CV_PIRECONLAG
#define _BRSFC_CV_PIREPACTIVENUB
#define _BRSFC_CV_PIREPRESTNUB
#define _BRSFC_CV_PIRESOL
#define _BRSFC_CV_PIRLCSI
#define _BRSFC_CV_PIROIGRX
#define _BRSFC_CV_PIRTAIT
#define _BRSFC_CV_PIRTB0NUB
#define _BRSFC_CV_PIRTB0VIS
#define _BRSFC_CV_PIRTETR
#define _BRSFC_CV_PIRTPOINTNUB
#define _BRSFC_CV_PIRTPOINTVAL2
#define _BRSFC_CV_PIRTPOINTVAL3
#define _BRSFC_CV_PIRTPOINTVAL4
#define _BRSFC_CV_PIRTPOINTVAL5
#define _BRSFC_CV_PIRTPOINTVAL6
#define _BRSFC_CV_PIRTRATENUB
#define _BRSFC_CV_PIRTREPNUB
#define _BRSFC_CV_PIRTREPVAL2
#define _BRSFC_CV_PIRTREPVAL3
#define _BRSFC_CV_PIRTREPVAL4
#define _BRSFC_CV_PIRTREPVAL5
#define _BRSFC_CV_PIRTREPVAL6
#define _BRSFC_CV_PIRTRIGWINNUB
#define _BRSFC_CV_PIRTSEQNUB
#define _BRSFC_CV_PIRTTSEQ
#define _BRSFC_CV_PIRTWINDEFVAL
#define _BRSFC_CV_PIRTWINVAL2
#define _BRSFC_CV_PIRTWINVAL3
#define _BRSFC_CV_PIRTWINVAL4
#define _BRSFC_CV_PIRTWINVAL5
#define _BRSFC_CV_PIRTWINVAL6
#define _BRSFC_CV_PISATNUB
#define _BRSFC_CV_PISATTHICK
#define _BRSFC_CV_PISATTHICKX
#define _BRSFC_CV_PISATTHICKY
#define _BRSFC_CV_PISATTHICKZ
#define _BRSFC_CV_PISAVEINTER
#define _BRSFC_CV_PISCAN_DISTANCE_TOH
#define _BRSFC_CV_PISCANCENTER
#define _BRSFC_CV_PISCRAN
#define _BRSFC_CV_PISCTIM
#define _BRSFC_CV_PISCTIM1
#define _BRSFC_CV_PISCTIM2
#define _BRSFC_CV_PISCTIM3
#define _BRSFC_CV_PISCTIM4
#define _BRSFC_CV_PISCTIM5
#define _BRSFC_CV_PISCTIM6
#define _BRSFC_CV_PISEPARATESYNBNUB
#define _BRSFC_CV_PISERPERPH
#define _BRSFC_CV_PISETUP
#define _BRSFC_CV_PISHIM2
#define _BRSFC_CV_PISHLDCTRL
#define _BRSFC_CV_PISHOTNUB
#define _BRSFC_CV_PISHOTVAL2
#define _BRSFC_CV_PISHOTVAL3
#define _BRSFC_CV_PISHOTVAL4
#define _BRSFC_CV_PISHOTVAL5
#define _BRSFC_CV_PISHOTVAL6
#define _BRSFC_CV_PISICSI
#define _BRSFC_CV_PISILENTMR
#define _BRSFC_CV_PISIOVERLAP
#define _BRSFC_CV_PISLASSETNUB
#define _BRSFC_CV_PISLASSETVAL1
#define _BRSFC_CV_PISLASSETVAL2
#define _BRSFC_CV_PISLASSETVAL3
#define _BRSFC_CV_PISLASSETVAL4
#define _BRSFC_CV_PISLBLANK
#define _BRSFC_CV_PISLDELNUB
#define _BRSFC_CV_PISLDELVAL3
#define _BRSFC_CV_PISLDELVAL4
#define _BRSFC_CV_PISLDELVAL5
#define _BRSFC_CV_PISLDELVAL6
#define _BRSFC_CV_PISLICEORDNUB
#define _BRSFC_CV_PISLQNUB
#define _BRSFC_CV_PISLQUANT
#define _BRSFC_CV_PISLQVAL2
#define _BRSFC_CV_PISLQVAL3
#define _BRSFC_CV_PISLQVAL4
#define _BRSFC_CV_PISLQVAL5
#define _BRSFC_CV_PISLTHICKLABEL
#define _BRSFC_CV_PISLTHICKSTEP
#define _BRSFC_CV_PISMODE
#define _BRSFC_CV_PISPECPRESCAN
#define _BRSFC_CV_PISPSSUPNUB
#define _BRSFC_CV_PISTNUB
#define _BRSFC_CV_PISTVAL2
#define _BRSFC_CV_PISTVAL3
#define _BRSFC_CV_PISTVAL4
#define _BRSFC_CV_PISTVAL5
#define _BRSFC_CV_PISTVAL6
#define _BRSFC_CV_PISUPNUB
#define _BRSFC_CV_PISWAPFC
#define _BRSFC_CV_PISYNBVALSTAB
#define _BRSFC_CV_PISYSTDEL1
#define _BRSFC_CV_PIT2PREPTEDEFVAL
#define _BRSFC_CV_PIT2PREPTENUB
#define _BRSFC_CV_PIT2PREPTEVAL2
#define _BRSFC_CV_PIT2PREPTEVAL3
#define _BRSFC_CV_PIT2PREPTEVAL4
#define _BRSFC_CV_PIT2PREPTEVAL5
#define _BRSFC_CV_PIT2PREPTEVAL6
#define _BRSFC_CV_PITABLEMAXACCEL
#define _BRSFC_CV_PITABLEMAXDECEL
#define _BRSFC_CV_PITABLEMAXSPEED
#define _BRSFC_CV_PITABLEPOSITION
#define _BRSFC_CV_PITAGANGLEDEFVAL
#define _BRSFC_CV_PITAGANGLENUB
#define _BRSFC_CV_PITAGANGLEVAL2
#define _BRSFC_CV_PITAGANGLEVAL3
#define _BRSFC_CV_PITAGANGLEVAL4
#define _BRSFC_CV_PITAGANGLEVAL5
#define _BRSFC_CV_PITAGANGLEVAL6
#define _BRSFC_CV_PITAGGING
#define _BRSFC_CV_PITAGSPCDEFVAL
#define _BRSFC_CV_PITAGSPCVAL2
#define _BRSFC_CV_PITAGSPCVAL3
#define _BRSFC_CV_PITAGSPCVAL4
#define _BRSFC_CV_PITBH
#define _BRSFC_CV_PITBHLAST
#define _BRSFC_CV_PITDEL1
#define _BRSFC_CV_PITDEL1NUB
#define _BRSFC_CV_PITDEL1TYPE
#define _BRSFC_CV_PITE1NUB
#define _BRSFC_CV_PITE1VAL2
#define _BRSFC_CV_PITE1VAL3
#define _BRSFC_CV_PITE1VAL4
#define _BRSFC_CV_PITE1VAL5
#define _BRSFC_CV_PITE1VAL6
#define _BRSFC_CV_PITE2NUB
#define _BRSFC_CV_PITE2TYPE
#define _BRSFC_CV_PITE2VAL2
#define _BRSFC_CV_PITE2VAL3
#define _BRSFC_CV_PITE2VAL4
#define _BRSFC_CV_PITE2VAL5
#define _BRSFC_CV_PITE2VAL6
#define _BRSFC_CV_PITETR
#define _BRSFC_CV_PITETYPE
#define _BRSFC_CV_PITFEEXTRA
#define _BRSFC_CV_PITIDEFVAL
#define _BRSFC_CV_PITINUB
#define _BRSFC_CV_PITISSUET1DEFVAL
#define _BRSFC_CV_PITISSUET1NUB
#define _BRSFC_CV_PITISSUET1VAL2
#define _BRSFC_CV_PITISSUET1VAL3
#define _BRSFC_CV_PITISSUET1VAL4
#define _BRSFC_CV_PITISSUET1VAL5
#define _BRSFC_CV_PITITLE
#define _BRSFC_CV_PITITYPE
#define _BRSFC_CV_PITIVAL2
#define _BRSFC_CV_PITIVAL3
#define _BRSFC_CV_PITIVAL4
#define _BRSFC_CV_PITIVAL5
#define _BRSFC_CV_PITIVAL6
#define _BRSFC_CV_PITLABELDEFVAL
#define _BRSFC_CV_PITLABELNUB
#define _BRSFC_CV_PITLABELSTEP
#define _BRSFC_CV_PITLABELVAL2
#define _BRSFC_CV_PITLABELVAL3
#define _BRSFC_CV_PITLABELVAL4
#define _BRSFC_CV_PITOUCH
#define _BRSFC_CV_PITOUCHAMP
#define _BRSFC_CV_PITOUCHAMPNUB
#define _BRSFC_CV_PITOUCHAMPVAL2
#define _BRSFC_CV_PITOUCHAMPVAL3
#define _BRSFC_CV_PITOUCHAMPVAL4
#define _BRSFC_CV_PITOUCHAXNUB
#define _BRSFC_CV_PITOUCHAXVAL2
#define _BRSFC_CV_PITOUCHAXVAL3
#define _BRSFC_CV_PITOUCHAXVAL4
#define _BRSFC_CV_PITOUCHAXVAL5
#define _BRSFC_CV_PITOUCHCYC
#define _BRSFC_CV_PITOUCHCYCNUB
#define _BRSFC_CV_PITOUCHCYCVAL2
#define _BRSFC_CV_PITOUCHCYCVAL3
#define _BRSFC_CV_PITOUCHCYCVAL4
#define _BRSFC_CV_PITOUCHFREQ
#define _BRSFC_CV_PITOUCHFREQNUB
#define _BRSFC_CV_PITOUCHFREQVAL2
#define _BRSFC_CV_PITOUCHFREQVAL3
#define _BRSFC_CV_PITOUCHFREQVAL4
#define _BRSFC_CV_PITOUCHMEGFREQNUB
#define _BRSFC_CV_PITOUCHMEGFREQVAL2
#define _BRSFC_CV_PITOUCHMEGFREQVAL3
#define _BRSFC_CV_PITOUCHMEGFREQVAL4
#define _BRSFC_CV_PITOUCHMENC
#define _BRSFC_CV_PITOUCHTPHASES
#define _BRSFC_CV_PITOUCHTPHASESNUB
#define _BRSFC_CV_PITOUCHTPHASESVAL2
#define _BRSFC_CV_PITOUCHTPHASESVAL3
#define _BRSFC_CV_PITOUCHTPHASESVAL4
#define _BRSFC_CV_PITPHASENUB
#define _BRSFC_CV_PITPHASEVAL2
#define _BRSFC_CV_PITPHASEVAL3
#define _BRSFC_CV_PITPHASEVAL4
#define _BRSFC_CV_PITPHASEVAL5
#define _BRSFC_CV_PITPHASEVAL6
#define _BRSFC_CV_PITR
#define _BRSFC_CV_PITRACQNUB
#define _BRSFC_CV_PITRACQVAL2
#define _BRSFC_CV_PITRACQVAL3
#define _BRSFC_CV_PITRACQVAL4
#define _BRSFC_CV_PITRACQVAL5
#define _BRSFC_CV_PITRACQVAL6
#define _BRSFC_CV_PITRECOVERYDEFVAL
#define _BRSFC_CV_PITRECOVERYNUB
#define _BRSFC_CV_PITRECOVERYSTEP
#define _BRSFC_CV_PITRECOVERYVAL2
#define _BRSFC_CV_PITRECOVERYVAL3
#define _BRSFC_CV_PITRECOVERYVAL4
#define _BRSFC_CV_PITRECOVERYVAL5
#define _BRSFC_CV_PITRECOVERYVAL6
#define _BRSFC_CV_PITRES
#define _BRSFC_CV_PITRES2
#define _BRSFC_CV_PITRES2NUB
#define _BRSFC_CV_PITRESNUB
#define _BRSFC_CV_PITRICKSDELNUB
#define _BRSFC_CV_PITRICKSDELVAL3
#define _BRSFC_CV_PITRICKSDELVAL4
#define _BRSFC_CV_PITRICKSDELVAL5
#define _BRSFC_CV_PITRICKSDELVAL6
#define _BRSFC_CV_PITRIGWINNUB
#define _BRSFC_CV_PITRNUB
#define _BRSFC_CV_PITRVAL2
#define _BRSFC_CV_PITRVAL3
#define _BRSFC_CV_PITRVAL4
#define _BRSFC_CV_PITRVAL5
#define _BRSFC_CV_PITRVAL6
#define _BRSFC_CV_PITSAR
#define _BRSFC_CV_PITSCAN
#define _BRSFC_CV_PITSEQ
#define _BRSFC_CV_PITSEQNUB
#define _BRSFC_CV_PITSEQTYPE
#define _BRSFC_CV_PITSLICE
#define _BRSFC_CV_PITSP1
#define _BRSFC_CV_PITSP2
#define _BRSFC_CV_PIUSET
#define _BRSFC_CV_PIUSET2
#define _BRSFC_CV_PIVASCOP
#define _BRSFC_CV_PIVELNUB
#define _BRSFC_CV_PIVESTNUB
#define _BRSFC_CV_PIVEXTRAS
#define _BRSFC_CV_PIVIEWORDERNUB
#define _BRSFC_CV_PIVIEWS
#define _BRSFC_CV_PIVIEWSEG
#define _BRSFC_CV_PIVPSDEF
#define _BRSFC_CV_PIVSPHASENUB
#define _BRSFC_CV_PIVSPHASEVAL2
#define _BRSFC_CV_PIVSPHASEVAL3
#define _BRSFC_CV_PIVSPHASEVAL4
#define _BRSFC_CV_PIVSPHASEVAL5
#define _BRSFC_CV_PIVSPHASEVAL6
#define _BRSFC_CV_PIVSSCAN
#define _BRSFC_CV_PIXMTBAND
#define _BRSFC_CV_PIXRESNUB
#define _BRSFC_CV_PIXRESVAL2
#define _BRSFC_CV_PIXRESVAL3
#define _BRSFC_CV_PIXRESVAL4
#define _BRSFC_CV_PIXRESVAL5
#define _BRSFC_CV_PIXRESVAL6
#define _BRSFC_CV_PIYRESNUB
#define _BRSFC_CV_PIYRESVAL2
#define _BRSFC_CV_PIYRESVAL3
#define _BRSFC_CV_PIYRESVAL4
#define _BRSFC_CV_PIYRESVAL5
#define _BRSFC_CV_PIYRESVAL6
#define _BRSFC_CV_PIZMULT
#define _BRSFC_CV_PIZOOM_INDEX
#define _BRSFC_CV_POS_HARD180
#define _BRSFC_CV_POS_MOMENT_START
#define _BRSFC_CV_POS_MSDE_START
#define _BRSFC_CV_POS_RFGIR01
#define _BRSFC_CV_POS_RFGIR02
#define _BRSFC_CV_POS_START
#define _BRSFC_CV_POS_START_FRIR
#define _BRSFC_CV_POS_START_GZK
#define _BRSFC_CV_POS_START_IR
#define _BRSFC_CV_POS_START_IR_MIN
#define _BRSFC_CV_POS_START_KILLER_RFGIR01
#define _BRSFC_CV_POS_START_KILLER_RFGIR02
#define _BRSFC_CV_POS_START_RFGIR01
#define _BRSFC_CV_POS_START_RFGIR02
#define _BRSFC_CV_POSPOWERX
#define _BRSFC_CV_POSPOWERY
#define _BRSFC_CV_POSPOWERZ
#define _BRSFC_CV_POST_LOBES
#define _BRSFC_CV_POST_OSFP_WEIGHT
#define _BRSFC_CV_POWERX
#define _BRSFC_CV_POWERY
#define _BRSFC_CV_POWERZ
#define _BRSFC_CV_PRE_LOBES
#define _BRSFC_CV_PRE_PASS
#define _BRSFC_CV_PRE_RCVN_TR
#define _BRSFC_CV_PRE_SLICE
#define _BRSFC_CV_PREDICTED_TG
#define _BRSFC_CV_PREMID_RF90
#define _BRSFC_CV_PREP_DDA
#define _BRSFC_CV_PRESSCFH
#define _BRSFC_CV_PRESSCFH_CGATE
#define _BRSFC_CV_PRESSCFH_CTRL
#define _BRSFC_CV_PRESSCFH_DEBUG
#define _BRSFC_CV_PRESSCFH_FOV
#define _BRSFC_CV_PRESSCFH_FOV_RATIO
#define _BRSFC_CV_PRESSCFH_IR_NOSELECT
#define _BRSFC_CV_PRESSCFH_IR_SLTHICK
#define _BRSFC_CV_PRESSCFH_MINFOV_RATIO
#define _BRSFC_CV_PRESSCFH_MINTE
#define _BRSFC_CV_PRESSCFH_OUTRANGE
#define _BRSFC_CV_PRESSCFH_OVERRIDE
#define _BRSFC_CV_PRESSCFH_PFOV
#define _BRSFC_CV_PRESSCFH_PFOV_RATIO
#define _BRSFC_CV_PRESSCFH_SLAB_RATIO
#define _BRSFC_CV_PRESSCFH_SLICE
#define _BRSFC_CV_PRESSCFH_SLTHICK
#define _BRSFC_CV_PRESSCFH_WAIT_RF12
#define _BRSFC_CV_PRESSCFH_WAIT_RF23
#define _BRSFC_CV_PRESSCFH_WAIT_RF34
#define _BRSFC_CV_PREVENT_SCAN_UNDER_EMUL
#define _BRSFC_CV_PRODUCT_RF
#define _BRSFC_CV_PROFILE_OPVTHICK
#define _BRSFC_CV_PROJECT
#define _BRSFC_CV_PS1_NEWGEO
#define _BRSFC_CV_PS1_RXCOIL
#define _BRSFC_CV_PS1_TR
#define _BRSFC_CV_PS1LOGGRD
#define _BRSFC_CV_PS1OBL_DEBUG
#define _BRSFC_CV_PS1SCALE
#define _BRSFC_CV_PS2_DDA
#define _BRSFC_CV_PS2_DDA_CAL3D
#define _BRSFC_CV_PS2_DDA_TIME_CAL3D
#define _BRSFC_CV_PS_CRUSHER_AREA
#define _BRSFC_CV_PSCAHEAD
#define _BRSFC_CV_PSD_BOARD_TYPE
#define _BRSFC_CV_PSD_CARD_HDWR_DELAY
#define _BRSFC_CV_PSD_GRD_WAIT
#define _BRSFC_CV_PSD_MANTRIG
#define _BRSFC_CV_PSD_PSCSHIM
#define _BRSFC_CV_PSD_PSCTG
#define _BRSFC_CV_PSD_RF_WAIT
#define _BRSFC_CV_PSD_STARTTA_OVERRIDE
#define _BRSFC_CV_PSD_TAPS
#define _BRSFC_CV_PSD_TARGETSCALE
#define _BRSFC_CV_PSD_TOL_VALUE
#define _BRSFC_CV_PSD_ZERO
#define _BRSFC_CV_PSDCRUCIAL_DEBUG
#define _BRSFC_CV_PSDDEBUGCODE
#define _BRSFC_CV_PSDDEBUGCODE2
#define _BRSFC_CV_PSDTIME_RFGIR01
#define _BRSFC_CV_PSDTIME_RFGIR01_ISO
#define _BRSFC_CV_PSDTIME_RFGIR02
#define _BRSFC_CV_PSDTIME_RFGIR02_ISO
#define _BRSFC_CV_PULSEPOS
#define _BRSFC_CV_PURE_MIX_TX_SCALE
#define _BRSFC_CV_PW1_EFF
#define _BRSFC_CV_PW2_EFF
#define _BRSFC_CV_PW_ACQDTG1
#define _BRSFC_CV_PW_ACQRS1
#define _BRSFC_CV_PW_BSRF
#define _BRSFC_CV_PW_CONSTANT
#define _BRSFC_CV_PW_CONTRFHUBSEL
#define _BRSFC_CV_PW_CONTRFSEL
#define _BRSFC_CV_PW_CSW_WAIT
#define _BRSFC_CV_PW_DIX_SSPPOST
#define _BRSFC_CV_PW_DIX_SSPPRE
#define _BRSFC_CV_PW_DIX_XPRE
#define _BRSFC_CV_PW_DRCV
#define _BRSFC_CV_PW_GATE_ISI
#define _BRSFC_CV_PW_GKS
#define _BRSFC_CV_PW_GX1
#define _BRSFC_CV_PW_GX1_FRAC
#define _BRSFC_CV_PW_GX1_FULL
#define _BRSFC_CV_PW_GX1A
#define _BRSFC_CV_PW_GX1A_FRAC
#define _BRSFC_CV_PW_GX1A_FULL
#define _BRSFC_CV_PW_GX1AS
#define _BRSFC_CV_PW_GX1ASA
#define _BRSFC_CV_PW_GX1ASD
#define _BRSFC_CV_PW_GX1BFTG
#define _BRSFC_CV_PW_GX1BFTGA
#define _BRSFC_CV_PW_GX1BFTGD
#define _BRSFC_CV_PW_GX1BXTG
#define _BRSFC_CV_PW_GX1BXTGA
#define _BRSFC_CV_PW_GX1BXTGD
#define _BRSFC_CV_PW_GX1CFH
#define _BRSFC_CV_PW_GX1CFHA
#define _BRSFC_CV_PW_GX1CFHD
#define _BRSFC_CV_PW_GX1D
#define _BRSFC_CV_PW_GX1D_FRAC
#define _BRSFC_CV_PW_GX1D_FULL
#define _BRSFC_CV_PW_GX1DTG
#define _BRSFC_CV_PW_GX1DTGA
#define _BRSFC_CV_PW_GX1DTGD
#define _BRSFC_CV_PW_GX1F
#define _BRSFC_CV_PW_GX1FTG
#define _BRSFC_CV_PW_GX1FTGA
#define _BRSFC_CV_PW_GX1FTGD
#define _BRSFC_CV_PW_GX1MON
#define _BRSFC_CV_PW_GX1MONA
#define _BRSFC_CV_PW_GX1MOND
#define _BRSFC_CV_PW_GX1MPS1
#define _BRSFC_CV_PW_GX1MPS1A
#define _BRSFC_CV_PW_GX1MPS1D
#define _BRSFC_CV_PW_GX1RS
#define _BRSFC_CV_PW_GX1RSA
#define _BRSFC_CV_PW_GX1RSD
#define _BRSFC_CV_PW_GX1TM
#define _BRSFC_CV_PW_GX1TMA
#define _BRSFC_CV_PW_GX1TMD
#define _BRSFC_CV_PW_GX2
#define _BRSFC_CV_PW_GX2A
#define _BRSFC_CV_PW_GX2D
#define _BRSFC_CV_PW_GX2DTG
#define _BRSFC_CV_PW_GX2DTGA
#define _BRSFC_CV_PW_GX2DTGD
#define _BRSFC_CV_PW_GX2FTG
#define _BRSFC_CV_PW_GX2FTGA
#define _BRSFC_CV_PW_GX2FTGD
#define _BRSFC_CV_PW_GX2RS
#define _BRSFC_CV_PW_GX2RSA
#define _BRSFC_CV_PW_GX2RSD
#define _BRSFC_CV_PW_GX2TEST
#define _BRSFC_CV_PW_GX2TESTA
#define _BRSFC_CV_PW_GX2TESTD
#define _BRSFC_CV_PW_GXB
#define _BRSFC_CV_PW_GXBA
#define _BRSFC_CV_PW_GXBD
#define _BRSFC_CV_PW_GXBRSFC1
#define _BRSFC_CV_PW_GXBRSFC1A
#define _BRSFC_CV_PW_GXBRSFC1D
#define _BRSFC_CV_PW_GXBRSFC2
#define _BRSFC_CV_PW_GXBRSFC2A
#define _BRSFC_CV_PW_GXBRSFC2D
#define _BRSFC_CV_PW_GXFC
#define _BRSFC_CV_PW_GXFC_FRAC
#define _BRSFC_CV_PW_GXFC_FULL
#define _BRSFC_CV_PW_GXFCA
#define _BRSFC_CV_PW_GXFCA_FRAC
#define _BRSFC_CV_PW_GXFCA_FULL
#define _BRSFC_CV_PW_GXFCD
#define _BRSFC_CV_PW_GXFCD_FRAC
#define _BRSFC_CV_PW_GXFCD_FULL
#define _BRSFC_CV_PW_GXFCMON
#define _BRSFC_CV_PW_GXFCMONA
#define _BRSFC_CV_PW_GXFCMOND
#define _BRSFC_CV_PW_GXFLPK
#define _BRSFC_CV_PW_GXFLPKA
#define _BRSFC_CV_PW_GXFLPKD
#define _BRSFC_CV_PW_GXFLPVENC
#define _BRSFC_CV_PW_GXFLPVENCA
#define _BRSFC_CV_PW_GXFLPVENCD
#define _BRSFC_CV_PW_GXHYST1
#define _BRSFC_CV_PW_GXHYST1A
#define _BRSFC_CV_PW_GXHYST1D
#define _BRSFC_CV_PW_GXHYST2
#define _BRSFC_CV_PW_GXHYST2A
#define _BRSFC_CV_PW_GXHYST2D
#define _BRSFC_CV_PW_GXKAS
#define _BRSFC_CV_PW_GXKASA
#define _BRSFC_CV_PW_GXKASD
#define _BRSFC_CV_PW_GXKBSDTG
#define _BRSFC_CV_PW_GXKBSDTGA
#define _BRSFC_CV_PW_GXKBSDTGD
#define _BRSFC_CV_PW_GXKBSRS
#define _BRSFC_CV_PW_GXKBSRSA
#define _BRSFC_CV_PW_GXKBSRSD
#define _BRSFC_CV_PW_GXKCS
#define _BRSFC_CV_PW_GXKCSA
#define _BRSFC_CV_PW_GXKCSD
#define _BRSFC_CV_PW_GXKDTG
#define _BRSFC_CV_PW_GXKDTGA
#define _BRSFC_CV_PW_GXKDTGD
#define _BRSFC_CV_PW_GXKFS
#define _BRSFC_CV_PW_GXKFSA
#define _BRSFC_CV_PW_GXKFSD
#define _BRSFC_CV_PW_GXKILL
#define _BRSFC_CV_PW_GXKILLA
#define _BRSFC_CV_PW_GXKILLD
#define _BRSFC_CV_PW_GXKRCVN
#define _BRSFC_CV_PW_GXKRCVNA
#define _BRSFC_CV_PW_GXKRCVND
#define _BRSFC_CV_PW_GXKRS
#define _BRSFC_CV_PW_GXKRSA
#define _BRSFC_CV_PW_GXKRSD
#define _BRSFC_CV_PW_GXKS
#define _BRSFC_CV_PW_GXKSA
#define _BRSFC_CV_PW_GXKSD
#define _BRSFC_CV_PW_GXKSE1
#define _BRSFC_CV_PW_GXKSE1A
#define _BRSFC_CV_PW_GXKSE1D
#define _BRSFC_CV_PW_GXKSE2
#define _BRSFC_CV_PW_GXKSE2A
#define _BRSFC_CV_PW_GXKSE2D
#define _BRSFC_CV_PW_GXKSE3
#define _BRSFC_CV_PW_GXKSE3A
#define _BRSFC_CV_PW_GXKSE3D
#define _BRSFC_CV_PW_GXKSE4
#define _BRSFC_CV_PW_GXKSE4A
#define _BRSFC_CV_PW_GXKSE4D
#define _BRSFC_CV_PW_GXKSE5
#define _BRSFC_CV_PW_GXKSE5A
#define _BRSFC_CV_PW_GXKSE5D
#define _BRSFC_CV_PW_GXKSE6
#define _BRSFC_CV_PW_GXKSE6A
#define _BRSFC_CV_PW_GXKSE6D
#define _BRSFC_CV_PW_GXKSP
#define _BRSFC_CV_PW_GXKSPA
#define _BRSFC_CV_PW_GXKSPD
#define _BRSFC_CV_PW_GXKSSF
#define _BRSFC_CV_PW_GXKSSFA
#define _BRSFC_CV_PW_GXKSSFD
#define _BRSFC_CV_PW_GXKSX1
#define _BRSFC_CV_PW_GXKSX1A
#define _BRSFC_CV_PW_GXKSX1D
#define _BRSFC_CV_PW_GXKSX2
#define _BRSFC_CV_PW_GXKSX2A
#define _BRSFC_CV_PW_GXKSX2D
#define _BRSFC_CV_PW_GXKSY1
#define _BRSFC_CV_PW_GXKSY1A
#define _BRSFC_CV_PW_GXKSY1D
#define _BRSFC_CV_PW_GXKSY2
#define _BRSFC_CV_PW_GXKSY2A
#define _BRSFC_CV_PW_GXKSY2D
#define _BRSFC_CV_PW_GXKSZ1
#define _BRSFC_CV_PW_GXKSZ1A
#define _BRSFC_CV_PW_GXKSZ1D
#define _BRSFC_CV_PW_GXKSZ2
#define _BRSFC_CV_PW_GXKSZ2A
#define _BRSFC_CV_PW_GXKSZ2D
#define _BRSFC_CV_PW_GXRF1TM
#define _BRSFC_CV_PW_GXRF1TMA
#define _BRSFC_CV_PW_GXRF1TMD
#define _BRSFC_CV_PW_GXRF2CFH
#define _BRSFC_CV_PW_GXRF2CFHA
#define _BRSFC_CV_PW_GXRF2CFHD
#define _BRSFC_CV_PW_GXRFSX1
#define _BRSFC_CV_PW_GXRFSX1A
#define _BRSFC_CV_PW_GXRFSX1D
#define _BRSFC_CV_PW_GXRFSX2
#define _BRSFC_CV_PW_GXRFSX2A
#define _BRSFC_CV_PW_GXRFSX2D
#define _BRSFC_CV_PW_GXSPIRAL
#define _BRSFC_CV_PW_GXSPIRAL2
#define _BRSFC_CV_PW_GXSPOIL
#define _BRSFC_CV_PW_GXSPOIL2
#define _BRSFC_CV_PW_GXSPOIL2A
#define _BRSFC_CV_PW_GXSPOIL2D
#define _BRSFC_CV_PW_GXSPOILA
#define _BRSFC_CV_PW_GXSPOILD
#define _BRSFC_CV_PW_GXW
#define _BRSFC_CV_PW_GXW1FTG
#define _BRSFC_CV_PW_GXW1FTGA
#define _BRSFC_CV_PW_GXW1FTGD
#define _BRSFC_CV_PW_GXW1XTG
#define _BRSFC_CV_PW_GXW1XTGA
#define _BRSFC_CV_PW_GXW1XTGD
#define _BRSFC_CV_PW_GXW2
#define _BRSFC_CV_PW_GXW2A
#define _BRSFC_CV_PW_GXW2D
#define _BRSFC_CV_PW_GXW2DTG
#define _BRSFC_CV_PW_GXW2DTGA
#define _BRSFC_CV_PW_GXW2DTGD
#define _BRSFC_CV_PW_GXW2FTG
#define _BRSFC_CV_PW_GXW2FTGA
#define _BRSFC_CV_PW_GXW2FTGD
#define _BRSFC_CV_PW_GXW2FTGLEFT
#define _BRSFC_CV_PW_GXW2RS
#define _BRSFC_CV_PW_GXW2RSA
#define _BRSFC_CV_PW_GXW2RSD
#define _BRSFC_CV_PW_GXW_FRAC
#define _BRSFC_CV_PW_GXW_FULL
#define _BRSFC_CV_PW_GXWA
#define _BRSFC_CV_PW_GXWA_FRAC
#define _BRSFC_CV_PW_GXWA_FULL
#define _BRSFC_CV_PW_GXWAS
#define _BRSFC_CV_PW_GXWASA
#define _BRSFC_CV_PW_GXWASD
#define _BRSFC_CV_PW_GXWD
#define _BRSFC_CV_PW_GXWD_FRAC
#define _BRSFC_CV_PW_GXWD_FULL
#define _BRSFC_CV_PW_GXWD_TEMP
#define _BRSFC_CV_PW_GXWDTG
#define _BRSFC_CV_PW_GXWDTGA
#define _BRSFC_CV_PW_GXWDTGD
#define _BRSFC_CV_PW_GXWEX
#define _BRSFC_CV_PW_GXWEX1
#define _BRSFC_CV_PW_GXWEXA
#define _BRSFC_CV_PW_GXWEXD
#define _BRSFC_CV_PW_GXWEXMAX
#define _BRSFC_CV_PW_GXWL
#define _BRSFC_CV_PW_GXWMON
#define _BRSFC_CV_PW_GXWMONA
#define _BRSFC_CV_PW_GXWMOND
#define _BRSFC_CV_PW_GXWMPS1
#define _BRSFC_CV_PW_GXWMPS1A
#define _BRSFC_CV_PW_GXWMPS1D
#define _BRSFC_CV_PW_GXWR
#define _BRSFC_CV_PW_GXWRS
#define _BRSFC_CV_PW_GXWRSA
#define _BRSFC_CV_PW_GXWRSD
#define _BRSFC_CV_PW_GY1
#define _BRSFC_CV_PW_GY1_TOT
#define _BRSFC_CV_PW_GY1A
#define _BRSFC_CV_PW_GY1AS
#define _BRSFC_CV_PW_GY1AS_TOT
#define _BRSFC_CV_PW_GY1ASA
#define _BRSFC_CV_PW_GY1ASD
#define _BRSFC_CV_PW_GY1CFH
#define _BRSFC_CV_PW_GY1CFHA
#define _BRSFC_CV_PW_GY1CFHD
#define _BRSFC_CV_PW_GY1D
#define _BRSFC_CV_PW_GY1DTG
#define _BRSFC_CV_PW_GY1DTGA
#define _BRSFC_CV_PW_GY1DTGD
#define _BRSFC_CV_PW_GY1F
#define _BRSFC_CV_PW_GY1MON
#define _BRSFC_CV_PW_GY1MONA
#define _BRSFC_CV_PW_GY1MOND
#define _BRSFC_CV_PW_GY1MPS1
#define _BRSFC_CV_PW_GY1MPS1A
#define _BRSFC_CV_PW_GY1MPS1D
#define _BRSFC_CV_PW_GY1R
#define _BRSFC_CV_PW_GY1R_TOT
#define _BRSFC_CV_PW_GY1RA
#define _BRSFC_CV_PW_GY1RAS
#define _BRSFC_CV_PW_GY1RASA
#define _BRSFC_CV_PW_GY1RASD
#define _BRSFC_CV_PW_GY1RD
#define _BRSFC_CV_PW_GY1RDTG
#define _BRSFC_CV_PW_GY1RDTGA
#define _BRSFC_CV_PW_GY1RDTGD
#define _BRSFC_CV_PW_GY1RF
#define _BRSFC_CV_PW_GY1RRS
#define _BRSFC_CV_PW_GY1RRSA
#define _BRSFC_CV_PW_GY1RRSD
#define _BRSFC_CV_PW_GY1RS
#define _BRSFC_CV_PW_GY1RSA
#define _BRSFC_CV_PW_GY1RSD
#define _BRSFC_CV_PW_GY1TM
#define _BRSFC_CV_PW_GY1TMA
#define _BRSFC_CV_PW_GY1TMD
#define _BRSFC_CV_PW_GY2DTG
#define _BRSFC_CV_PW_GY2DTGA
#define _BRSFC_CV_PW_GY2DTGD
#define _BRSFC_CV_PW_GY2RS
#define _BRSFC_CV_PW_GY2RSA
#define _BRSFC_CV_PW_GY2RSD
#define _BRSFC_CV_PW_GYB
#define _BRSFC_CV_PW_GYBA
#define _BRSFC_CV_PW_GYBD
#define _BRSFC_CV_PW_GYBRSFC1
#define _BRSFC_CV_PW_GYBRSFC1A
#define _BRSFC_CV_PW_GYBRSFC1D
#define _BRSFC_CV_PW_GYBRSFC2
#define _BRSFC_CV_PW_GYBRSFC2A
#define _BRSFC_CV_PW_GYBRSFC2D
#define _BRSFC_CV_PW_GYCYLR
#define _BRSFC_CV_PW_GYCYLRA
#define _BRSFC_CV_PW_GYCYLRATIPUP
#define _BRSFC_CV_PW_GYCYLRTIPUP
#define _BRSFC_CV_PW_GYFE
#define _BRSFC_CV_PW_GYFE1
#define _BRSFC_CV_PW_GYFE1A
#define _BRSFC_CV_PW_GYFE1D
#define _BRSFC_CV_PW_GYFE2
#define _BRSFC_CV_PW_GYFE2A
#define _BRSFC_CV_PW_GYFE2D
#define _BRSFC_CV_PW_GYFEA
#define _BRSFC_CV_PW_GYFED
#define _BRSFC_CV_PW_GYFLPK
#define _BRSFC_CV_PW_GYFLPKA
#define _BRSFC_CV_PW_GYFLPKD
#define _BRSFC_CV_PW_GYFLPVENC
#define _BRSFC_CV_PW_GYFLPVENCA
#define _BRSFC_CV_PW_GYFLPVENCD
#define _BRSFC_CV_PW_GYHYST1
#define _BRSFC_CV_PW_GYHYST1A
#define _BRSFC_CV_PW_GYHYST1D
#define _BRSFC_CV_PW_GYHYST2
#define _BRSFC_CV_PW_GYHYST2A
#define _BRSFC_CV_PW_GYHYST2D
#define _BRSFC_CV_PW_GYKCFH
#define _BRSFC_CV_PW_GYKCFHA
#define _BRSFC_CV_PW_GYKCFHD
#define _BRSFC_CV_PW_GYKCFL
#define _BRSFC_CV_PW_GYKCFLA
#define _BRSFC_CV_PW_GYKCFLD
#define _BRSFC_CV_PW_GYKCS
#define _BRSFC_CV_PW_GYKCSA
#define _BRSFC_CV_PW_GYKCSD
#define _BRSFC_CV_PW_GYKFS
#define _BRSFC_CV_PW_GYKFSA
#define _BRSFC_CV_PW_GYKFSD
#define _BRSFC_CV_PW_GYKILL
#define _BRSFC_CV_PW_GYKILLA
#define _BRSFC_CV_PW_GYKILLD
#define _BRSFC_CV_PW_GYKRCVN
#define _BRSFC_CV_PW_GYKRCVNA
#define _BRSFC_CV_PW_GYKRCVND
#define _BRSFC_CV_PW_GYKS
#define _BRSFC_CV_PW_GYKSA
#define _BRSFC_CV_PW_GYKSD
#define _BRSFC_CV_PW_GYKSE1
#define _BRSFC_CV_PW_GYKSE1A
#define _BRSFC_CV_PW_GYKSE1D
#define _BRSFC_CV_PW_GYKSE2
#define _BRSFC_CV_PW_GYKSE2A
#define _BRSFC_CV_PW_GYKSE2D
#define _BRSFC_CV_PW_GYKSE3
#define _BRSFC_CV_PW_GYKSE3A
#define _BRSFC_CV_PW_GYKSE3D
#define _BRSFC_CV_PW_GYKSE4
#define _BRSFC_CV_PW_GYKSE4A
#define _BRSFC_CV_PW_GYKSE4D
#define _BRSFC_CV_PW_GYKSE5
#define _BRSFC_CV_PW_GYKSE5A
#define _BRSFC_CV_PW_GYKSE5D
#define _BRSFC_CV_PW_GYKSE6
#define _BRSFC_CV_PW_GYKSE6A
#define _BRSFC_CV_PW_GYKSE6D
#define _BRSFC_CV_PW_GYKSP
#define _BRSFC_CV_PW_GYKSPA
#define _BRSFC_CV_PW_GYKSPD
#define _BRSFC_CV_PW_GYKSSF
#define _BRSFC_CV_PW_GYKSSFA
#define _BRSFC_CV_PW_GYKSSFD
#define _BRSFC_CV_PW_GYKSX1
#define _BRSFC_CV_PW_GYKSX1A
#define _BRSFC_CV_PW_GYKSX1D
#define _BRSFC_CV_PW_GYKSX2
#define _BRSFC_CV_PW_GYKSX2A
#define _BRSFC_CV_PW_GYKSX2D
#define _BRSFC_CV_PW_GYKSY1
#define _BRSFC_CV_PW_GYKSY1A
#define _BRSFC_CV_PW_GYKSY1D
#define _BRSFC_CV_PW_GYKSY2
#define _BRSFC_CV_PW_GYKSY2A
#define _BRSFC_CV_PW_GYKSY2D
#define _BRSFC_CV_PW_GYKSZ1
#define _BRSFC_CV_PW_GYKSZ1A
#define _BRSFC_CV_PW_GYKSZ1D
#define _BRSFC_CV_PW_GYKSZ2
#define _BRSFC_CV_PW_GYKSZ2A
#define _BRSFC_CV_PW_GYKSZ2D
#define _BRSFC_CV_PW_GYKXTGL
#define _BRSFC_CV_PW_GYKXTGLA
#define _BRSFC_CV_PW_GYKXTGLD
#define _BRSFC_CV_PW_GYKXTGR
#define _BRSFC_CV_PW_GYKXTGRA
#define _BRSFC_CV_PW_GYKXTGRD
#define _BRSFC_CV_PW_GYRF0KCFH
#define _BRSFC_CV_PW_GYRF0KCFHA
#define _BRSFC_CV_PW_GYRF0KCFHD
#define _BRSFC_CV_PW_GYRF1MON
#define _BRSFC_CV_PW_GYRF1MONA
#define _BRSFC_CV_PW_GYRF1MOND
#define _BRSFC_CV_PW_GYRF1MPS1
#define _BRSFC_CV_PW_GYRF1MPS1A
#define _BRSFC_CV_PW_GYRF1MPS1D
#define _BRSFC_CV_PW_GYRF1TM
#define _BRSFC_CV_PW_GYRF1TMA
#define _BRSFC_CV_PW_GYRF1TMD
#define _BRSFC_CV_PW_GYRF1XTG
#define _BRSFC_CV_PW_GYRF1XTGA
#define _BRSFC_CV_PW_GYRF1XTGD
#define _BRSFC_CV_PW_GYRF2CFH
#define _BRSFC_CV_PW_GYRF2CFHA
#define _BRSFC_CV_PW_GYRF2CFHD
#define _BRSFC_CV_PW_GYRF2LMON
#define _BRSFC_CV_PW_GYRF2LMONA
#define _BRSFC_CV_PW_GYRF2LMOND
#define _BRSFC_CV_PW_GYRF2MON
#define _BRSFC_CV_PW_GYRF2MONA
#define _BRSFC_CV_PW_GYRF2MOND
#define _BRSFC_CV_PW_GYRF2RMON
#define _BRSFC_CV_PW_GYRF2RMONA
#define _BRSFC_CV_PW_GYRF2RMOND
#define _BRSFC_CV_PW_GYRF3CFH
#define _BRSFC_CV_PW_GYRF3CFHA
#define _BRSFC_CV_PW_GYRF3CFHD
#define _BRSFC_CV_PW_GYRFMONTIPUP
#define _BRSFC_CV_PW_GYRFMONTIPUPA
#define _BRSFC_CV_PW_GYRFMONTIPUPD
#define _BRSFC_CV_PW_GYRFSY1
#define _BRSFC_CV_PW_GYRFSY1A
#define _BRSFC_CV_PW_GYRFSY1D
#define _BRSFC_CV_PW_GYRFSY2
#define _BRSFC_CV_PW_GYRFSY2A
#define _BRSFC_CV_PW_GYRFSY2D
#define _BRSFC_CV_PW_GYSPIRAL
#define _BRSFC_CV_PW_GYSPIRAL2
#define _BRSFC_CV_PW_GYSPOIL
#define _BRSFC_CV_PW_GYSPOIL2
#define _BRSFC_CV_PW_GYSPOIL2A
#define _BRSFC_CV_PW_GYSPOIL2D
#define _BRSFC_CV_PW_GYSPOILA
#define _BRSFC_CV_PW_GYSPOILD
#define _BRSFC_CV_PW_GZ1
#define _BRSFC_CV_PW_GZ1A
#define _BRSFC_CV_PW_GZ1AS
#define _BRSFC_CV_PW_GZ1ASA
#define _BRSFC_CV_PW_GZ1ASD
#define _BRSFC_CV_PW_GZ1CFL
#define _BRSFC_CV_PW_GZ1CFLA
#define _BRSFC_CV_PW_GZ1CFLD
#define _BRSFC_CV_PW_GZ1D
#define _BRSFC_CV_PW_GZ1DTG
#define _BRSFC_CV_PW_GZ1DTGA
#define _BRSFC_CV_PW_GZ1DTGD
#define _BRSFC_CV_PW_GZ1FTG
#define _BRSFC_CV_PW_GZ1FTGA
#define _BRSFC_CV_PW_GZ1FTGD
#define _BRSFC_CV_PW_GZ1MON
#define _BRSFC_CV_PW_GZ1MONA
#define _BRSFC_CV_PW_GZ1MOND
#define _BRSFC_CV_PW_GZ1MPS1
#define _BRSFC_CV_PW_GZ1MPS1A
#define _BRSFC_CV_PW_GZ1MPS1D
#define _BRSFC_CV_PW_GZ1RS
#define _BRSFC_CV_PW_GZ1RSA
#define _BRSFC_CV_PW_GZ1RSD
#define _BRSFC_CV_PW_GZ1S
#define _BRSFC_CV_PW_GZ1SA
#define _BRSFC_CV_PW_GZ1SD
#define _BRSFC_CV_PW_GZ1XTG
#define _BRSFC_CV_PW_GZ1XTGA
#define _BRSFC_CV_PW_GZ1XTGD
#define _BRSFC_CV_PW_GZ2BFTG
#define _BRSFC_CV_PW_GZ2BFTGA
#define _BRSFC_CV_PW_GZ2BFTGD
#define _BRSFC_CV_PW_GZ2FTG
#define _BRSFC_CV_PW_GZ2FTGA
#define _BRSFC_CV_PW_GZ2FTGD
#define _BRSFC_CV_PW_GZ2XTG
#define _BRSFC_CV_PW_GZ2XTGA
#define _BRSFC_CV_PW_GZ2XTGD
#define _BRSFC_CV_PW_GZ3FTG
#define _BRSFC_CV_PW_GZ3FTGA
#define _BRSFC_CV_PW_GZ3FTGD
#define _BRSFC_CV_PW_GZBRSFC1
#define _BRSFC_CV_PW_GZBRSFC1A
#define _BRSFC_CV_PW_GZBRSFC1D
#define _BRSFC_CV_PW_GZBRSFC1ECHO1
#define _BRSFC_CV_PW_GZBRSFC1ECHO1A
#define _BRSFC_CV_PW_GZBRSFC1ECHO1D
#define _BRSFC_CV_PW_GZBRSFC1ECHO2
#define _BRSFC_CV_PW_GZBRSFC1ECHO2A
#define _BRSFC_CV_PW_GZBRSFC1ECHO2D
#define _BRSFC_CV_PW_GZBRSFC2
#define _BRSFC_CV_PW_GZBRSFC2A
#define _BRSFC_CV_PW_GZBRSFC2D
#define _BRSFC_CV_PW_GZCOMB
#define _BRSFC_CV_PW_GZCOMB_TOT
#define _BRSFC_CV_PW_GZCOMBA
#define _BRSFC_CV_PW_GZCOMBD
#define _BRSFC_CV_PW_GZCOMBF
#define _BRSFC_CV_PW_GZCOMBHTR
#define _BRSFC_CV_PW_GZCOMBHTRA
#define _BRSFC_CV_PW_GZCOMBHTRD
#define _BRSFC_CV_PW_GZCOMBHTRF
#define _BRSFC_CV_PW_GZCYLR
#define _BRSFC_CV_PW_GZCYLRA
#define _BRSFC_CV_PW_GZCYLRATIPUP
#define _BRSFC_CV_PW_GZCYLRTIPUP
#define _BRSFC_CV_PW_GZFC
#define _BRSFC_CV_PW_GZFCA
#define _BRSFC_CV_PW_GZFCD
#define _BRSFC_CV_PW_GZFLPK
#define _BRSFC_CV_PW_GZFLPKA
#define _BRSFC_CV_PW_GZFLPKD
#define _BRSFC_CV_PW_GZFLPVENC
#define _BRSFC_CV_PW_GZFLPVENCA
#define _BRSFC_CV_PW_GZFLPVENCD
#define _BRSFC_CV_PW_GZK
#define _BRSFC_CV_PW_GZKA
#define _BRSFC_CV_PW_GZKAS
#define _BRSFC_CV_PW_GZKASA
#define _BRSFC_CV_PW_GZKASD
#define _BRSFC_CV_PW_GZKBSDTG
#define _BRSFC_CV_PW_GZKBSDTGA
#define _BRSFC_CV_PW_GZKBSDTGD
#define _BRSFC_CV_PW_GZKBSRS
#define _BRSFC_CV_PW_GZKBSRSA
#define _BRSFC_CV_PW_GZKBSRSD
#define _BRSFC_CV_PW_GZKCS
#define _BRSFC_CV_PW_GZKCSA
#define _BRSFC_CV_PW_GZKCSD
#define _BRSFC_CV_PW_GZKD
#define _BRSFC_CV_PW_GZKDTG
#define _BRSFC_CV_PW_GZKDTGA
#define _BRSFC_CV_PW_GZKDTGD
#define _BRSFC_CV_PW_GZKFS
#define _BRSFC_CV_PW_GZKFSA
#define _BRSFC_CV_PW_GZKFSD
#define _BRSFC_CV_PW_GZKGIR01
#define _BRSFC_CV_PW_GZKGIR01A
#define _BRSFC_CV_PW_GZKGIR01D
#define _BRSFC_CV_PW_GZKGIR02
#define _BRSFC_CV_PW_GZKGIR02A
#define _BRSFC_CV_PW_GZKGIR02D
#define _BRSFC_CV_PW_GZKILL
#define _BRSFC_CV_PW_GZKILLA
#define _BRSFC_CV_PW_GZKILLD
#define _BRSFC_CV_PW_GZKILLER
#define _BRSFC_CV_PW_GZKILLERA
#define _BRSFC_CV_PW_GZKILLERD
#define _BRSFC_CV_PW_GZKMON
#define _BRSFC_CV_PW_GZKMONA
#define _BRSFC_CV_PW_GZKMOND
#define _BRSFC_CV_PW_GZKMONTIPUP
#define _BRSFC_CV_PW_GZKMONTIPUPA
#define _BRSFC_CV_PW_GZKMONTIPUPD
#define _BRSFC_CV_PW_GZKRCVN
#define _BRSFC_CV_PW_GZKRCVNA
#define _BRSFC_CV_PW_GZKRCVND
#define _BRSFC_CV_PW_GZKRFFRIR
#define _BRSFC_CV_PW_GZKRFFRIRA
#define _BRSFC_CV_PW_GZKRFFRIRD
#define _BRSFC_CV_PW_GZKRS
#define _BRSFC_CV_PW_GZKRSA
#define _BRSFC_CV_PW_GZKRSD
#define _BRSFC_CV_PW_GZKS
#define _BRSFC_CV_PW_GZKS5FP
#define _BRSFC_CV_PW_GZKS5FPA
#define _BRSFC_CV_PW_GZKS5FPD
#define _BRSFC_CV_PW_GZKSA
#define _BRSFC_CV_PW_GZKSD
#define _BRSFC_CV_PW_GZKSP
#define _BRSFC_CV_PW_GZKSPA
#define _BRSFC_CV_PW_GZKSPD
#define _BRSFC_CV_PW_GZKSSF
#define _BRSFC_CV_PW_GZKSSFA
#define _BRSFC_CV_PW_GZKSSFD
#define _BRSFC_CV_PW_GZP
#define _BRSFC_CV_PW_GZPA
#define _BRSFC_CV_PW_GZPD
#define _BRSFC_CV_PW_GZPF
#define _BRSFC_CV_PW_GZPHTR
#define _BRSFC_CV_PW_GZPHTRA
#define _BRSFC_CV_PW_GZPHTRD
#define _BRSFC_CV_PW_GZPHTRF
#define _BRSFC_CV_PW_GZPTM
#define _BRSFC_CV_PW_GZPTMA
#define _BRSFC_CV_PW_GZPTMD
#define _BRSFC_CV_PW_GZRF0
#define _BRSFC_CV_PW_GZRF0A
#define _BRSFC_CV_PW_GZRF0CFH
#define _BRSFC_CV_PW_GZRF0CFHA
#define _BRSFC_CV_PW_GZRF0CFHD
#define _BRSFC_CV_PW_GZRF0D
#define _BRSFC_CV_PW_GZRF0K
#define _BRSFC_CV_PW_GZRF0KA
#define _BRSFC_CV_PW_GZRF0KD
#define _BRSFC_CV_PW_GZRF1
#define _BRSFC_CV_PW_GZRF1A
#define _BRSFC_CV_PW_GZRF1A_TEMP
#define _BRSFC_CV_PW_GZRF1AS
#define _BRSFC_CV_PW_GZRF1ASA
#define _BRSFC_CV_PW_GZRF1ASD
#define _BRSFC_CV_PW_GZRF1CFH
#define _BRSFC_CV_PW_GZRF1CFHA
#define _BRSFC_CV_PW_GZRF1CFHD
#define _BRSFC_CV_PW_GZRF1CFL
#define _BRSFC_CV_PW_GZRF1CFLA
#define _BRSFC_CV_PW_GZRF1CFLD
#define _BRSFC_CV_PW_GZRF1D
#define _BRSFC_CV_PW_GZRF1D_TEMP
#define _BRSFC_CV_PW_GZRF1DTG
#define _BRSFC_CV_PW_GZRF1DTGA
#define _BRSFC_CV_PW_GZRF1DTGD
#define _BRSFC_CV_PW_GZRF1FTG
#define _BRSFC_CV_PW_GZRF1FTGA
#define _BRSFC_CV_PW_GZRF1FTGD
#define _BRSFC_CV_PW_GZRF1HTR
#define _BRSFC_CV_PW_GZRF1HTRA
#define _BRSFC_CV_PW_GZRF1HTRD
#define _BRSFC_CV_PW_GZRF1LOBE
#define _BRSFC_CV_PW_GZRF1MON
#define _BRSFC_CV_PW_GZRF1MONA
#define _BRSFC_CV_PW_GZRF1MOND
#define _BRSFC_CV_PW_GZRF1MPS1
#define _BRSFC_CV_PW_GZRF1MPS1A
#define _BRSFC_CV_PW_GZRF1MPS1D
#define _BRSFC_CV_PW_GZRF1RS
#define _BRSFC_CV_PW_GZRF1RSA
#define _BRSFC_CV_PW_GZRF1RSD
#define _BRSFC_CV_PW_GZRF1S
#define _BRSFC_CV_PW_GZRF1SA
#define _BRSFC_CV_PW_GZRF1SD
#define _BRSFC_CV_PW_GZRF1XTG
#define _BRSFC_CV_PW_GZRF1XTGA
#define _BRSFC_CV_PW_GZRF1XTGD
#define _BRSFC_CV_PW_GZRF2FTG
#define _BRSFC_CV_PW_GZRF2FTGA
#define _BRSFC_CV_PW_GZRF2FTGD
#define _BRSFC_CV_PW_GZRF2LCFH
#define _BRSFC_CV_PW_GZRF2LCFHA
#define _BRSFC_CV_PW_GZRF2LCFHD
#define _BRSFC_CV_PW_GZRF2LMPS1
#define _BRSFC_CV_PW_GZRF2LMPS1A
#define _BRSFC_CV_PW_GZRF2LMPS1D
#define _BRSFC_CV_PW_GZRF2MPS1
#define _BRSFC_CV_PW_GZRF2MPS1A
#define _BRSFC_CV_PW_GZRF2MPS1D
#define _BRSFC_CV_PW_GZRF2RCFH
#define _BRSFC_CV_PW_GZRF2RCFHA
#define _BRSFC_CV_PW_GZRF2RCFHD
#define _BRSFC_CV_PW_GZRF2RMPS1
#define _BRSFC_CV_PW_GZRF2RMPS1A
#define _BRSFC_CV_PW_GZRF2RMPS1D
#define _BRSFC_CV_PW_GZRF2XTG
#define _BRSFC_CV_PW_GZRF2XTGA
#define _BRSFC_CV_PW_GZRF2XTGD
#define _BRSFC_CV_PW_GZRF3FTG
#define _BRSFC_CV_PW_GZRF3FTGA
#define _BRSFC_CV_PW_GZRF3FTGD
#define _BRSFC_CV_PW_GZRF3LCFH
#define _BRSFC_CV_PW_GZRF3LCFHA
#define _BRSFC_CV_PW_GZRF3LCFHD
#define _BRSFC_CV_PW_GZRF3RCFH
#define _BRSFC_CV_PW_GZRF3RCFHA
#define _BRSFC_CV_PW_GZRF3RCFHD
#define _BRSFC_CV_PW_GZRF4CFH
#define _BRSFC_CV_PW_GZRF4CFHA
#define _BRSFC_CV_PW_GZRF4CFHD
#define _BRSFC_CV_PW_GZRF4LCFH
#define _BRSFC_CV_PW_GZRF4LCFHA
#define _BRSFC_CV_PW_GZRF4LCFHD
#define _BRSFC_CV_PW_GZRF4RCFH
#define _BRSFC_CV_PW_GZRF4RCFHA
#define _BRSFC_CV_PW_GZRF4RCFHD
#define _BRSFC_CV_PW_GZRFFRIR
#define _BRSFC_CV_PW_GZRFFRIRA
#define _BRSFC_CV_PW_GZRFFRIRD
#define _BRSFC_CV_PW_GZRFGIR01
#define _BRSFC_CV_PW_GZRFGIR01A
#define _BRSFC_CV_PW_GZRFGIR01D
#define _BRSFC_CV_PW_GZRFGIR02
#define _BRSFC_CV_PW_GZRFGIR02A
#define _BRSFC_CV_PW_GZRFGIR02D
#define _BRSFC_CV_PW_GZRFS5FPH
#define _BRSFC_CV_PW_GZRFS5FPHA
#define _BRSFC_CV_PW_GZRFS5FPHD
#define _BRSFC_CV_PW_GZRFSE1
#define _BRSFC_CV_PW_GZRFSE1A
#define _BRSFC_CV_PW_GZRFSE1D
#define _BRSFC_CV_PW_GZRFSE2
#define _BRSFC_CV_PW_GZRFSE2A
#define _BRSFC_CV_PW_GZRFSE2D
#define _BRSFC_CV_PW_GZRFSE3
#define _BRSFC_CV_PW_GZRFSE3A
#define _BRSFC_CV_PW_GZRFSE3D
#define _BRSFC_CV_PW_GZRFSE4
#define _BRSFC_CV_PW_GZRFSE4A
#define _BRSFC_CV_PW_GZRFSE4D
#define _BRSFC_CV_PW_GZRFSE5
#define _BRSFC_CV_PW_GZRFSE5A
#define _BRSFC_CV_PW_GZRFSE5D
#define _BRSFC_CV_PW_GZRFSE6
#define _BRSFC_CV_PW_GZRFSE6A
#define _BRSFC_CV_PW_GZRFSE6D
#define _BRSFC_CV_PW_GZRFSSFH
#define _BRSFC_CV_PW_GZRFSSFHA
#define _BRSFC_CV_PW_GZRFSSFHD
#define _BRSFC_CV_PW_GZRFSZ1
#define _BRSFC_CV_PW_GZRFSZ1A
#define _BRSFC_CV_PW_GZRFSZ1D
#define _BRSFC_CV_PW_GZRFSZ2
#define _BRSFC_CV_PW_GZRFSZ2A
#define _BRSFC_CV_PW_GZRFSZ2D
#define _BRSFC_CV_PW_GZS5FPHCOMB
#define _BRSFC_CV_PW_GZS5FPHCOMBA
#define _BRSFC_CV_PW_GZS5FPHCOMBD
#define _BRSFC_CV_PW_GZSSFHCOMB
#define _BRSFC_CV_PW_GZSSFHCOMBA
#define _BRSFC_CV_PW_GZSSFHCOMBD
#define _BRSFC_CV_PW_GZVLMIN
#define _BRSFC_CV_PW_GZVLW
#define _BRSFC_CV_PW_HARD180
#define _BRSFC_CV_PW_HST
#define _BRSFC_CV_PW_ISI7
#define _BRSFC_CV_PW_ISI_CARDIACSAT
#define _BRSFC_CV_PW_ISI_GIR1
#define _BRSFC_CV_PW_ISI_GIRE01
#define _BRSFC_CV_PW_ISI_GIRE02
#define _BRSFC_CV_PW_ISI_GIRK01
#define _BRSFC_CV_PW_ISI_GIRK02
#define _BRSFC_CV_PW_ISI_SATE1
#define _BRSFC_CV_PW_ISI_SATE2
#define _BRSFC_CV_PW_ISI_SATE3
#define _BRSFC_CV_PW_ISI_SATE4
#define _BRSFC_CV_PW_ISI_SATE5
#define _BRSFC_CV_PW_ISI_SATE6
#define _BRSFC_CV_PW_ISI_SATEK1
#define _BRSFC_CV_PW_ISI_SATEK2
#define _BRSFC_CV_PW_ISI_SATEK3
#define _BRSFC_CV_PW_ISI_SATEK4
#define _BRSFC_CV_PW_ISI_SATEK5
#define _BRSFC_CV_PW_ISI_SATEK6
#define _BRSFC_CV_PW_ISI_SATX1
#define _BRSFC_CV_PW_ISI_SATX2
#define _BRSFC_CV_PW_ISI_SATXK1
#define _BRSFC_CV_PW_ISI_SATXK2
#define _BRSFC_CV_PW_ISI_SATY1
#define _BRSFC_CV_PW_ISI_SATY2
#define _BRSFC_CV_PW_ISI_SATYK1
#define _BRSFC_CV_PW_ISI_SATYK2
#define _BRSFC_CV_PW_ISI_SATZ1
#define _BRSFC_CV_PW_ISI_SATZ2
#define _BRSFC_CV_PW_ISI_SATZK1
#define _BRSFC_CV_PW_ISI_SATZK2
#define _BRSFC_CV_PW_ISI_SLICE1
#define _BRSFC_CV_PW_ISI_SLICE2
#define _BRSFC_CV_PW_ISIGIR
#define _BRSFC_CV_PW_ISISAT
#define _BRSFC_CV_PW_ISISLICE
#define _BRSFC_CV_PW_MAPS1
#define _BRSFC_CV_PW_MAPS2
#define _BRSFC_CV_PW_MAPX
#define _BRSFC_CV_PW_MAPY
#define _BRSFC_CV_PW_MAPZ
#define _BRSFC_CV_PW_MPOMEGA_TD0
#define _BRSFC_CV_PW_MPRHO_TD0
#define _BRSFC_CV_PW_MPSSP_TD0
#define _BRSFC_CV_PW_MPTHETA_TD0
#define _BRSFC_CV_PW_MPX_TD0
#define _BRSFC_CV_PW_MPY_TD0
#define _BRSFC_CV_PW_MPZ_TD0
#define _BRSFC_CV_PW_NOMCYL
#define _BRSFC_CV_PW_OMEGA_HS_RFCSSAT
#define _BRSFC_CV_PW_OMEGA_IR0
#define _BRSFC_CV_PW_OMEGA_RFFRIR
#define _BRSFC_CV_PW_OMEGA_RFGIR01
#define _BRSFC_CV_PW_OMEGA_RFGIR02
#define _BRSFC_CV_PW_OMEGARF0CFH
#define _BRSFC_CV_PW_POSTGXW1FTG
#define _BRSFC_CV_PW_POSTGXW1FTGA
#define _BRSFC_CV_PW_POSTGXW1FTGD
#define _BRSFC_CV_PW_RAMPX
#define _BRSFC_CV_PW_RAMPY
#define _BRSFC_CV_PW_RAMPZ
#define _BRSFC_CV_PW_RCVN_WAIT
#define _BRSFC_CV_PW_RF0
#define _BRSFC_CV_PW_RF0CFH
#define _BRSFC_CV_PW_RF1
#define _BRSFC_CV_PW_RF180
#define _BRSFC_CV_PW_RF1_FULL
#define _BRSFC_CV_PW_RF1_PRE
#define _BRSFC_CV_PW_RF1AS
#define _BRSFC_CV_PW_RF1CFH
#define _BRSFC_CV_PW_RF1CFL
#define _BRSFC_CV_PW_RF1DTG
#define _BRSFC_CV_PW_RF1FTG
#define _BRSFC_CV_PW_RF1HTR
#define _BRSFC_CV_PW_RF1MON
#define _BRSFC_CV_PW_RF1MPS1
#define _BRSFC_CV_PW_RF1RS
#define _BRSFC_CV_PW_RF1TM
#define _BRSFC_CV_PW_RF1XTG
#define _BRSFC_CV_PW_RF2CFH
#define _BRSFC_CV_PW_RF2FTG
#define _BRSFC_CV_PW_RF2MON
#define _BRSFC_CV_PW_RF2MPS1
#define _BRSFC_CV_PW_RF2XTG
#define _BRSFC_CV_PW_RF3CFH
#define _BRSFC_CV_PW_RF3FTG
#define _BRSFC_CV_PW_RF3XTG
#define _BRSFC_CV_PW_RF4CFH
#define _BRSFC_CV_PW_RF4XTG
#define _BRSFC_CV_PW_RF90
#define _BRSFC_CV_PW_RFBDTG
#define _BRSFC_CV_PW_RFBRS
#define _BRSFC_CV_PW_RFCSSAT
#define _BRSFC_CV_PW_RFCSSATCFH
#define _BRSFC_CV_PW_RFCYLR
#define _BRSFC_CV_PW_RFCYLRTIPUP
#define _BRSFC_CV_PW_RFFLP180
#define _BRSFC_CV_PW_RFFLP180_THE
#define _BRSFC_CV_PW_RFFLP90
#define _BRSFC_CV_PW_RFFLP90_THE
#define _BRSFC_CV_PW_RFFLP90R
#define _BRSFC_CV_PW_RFFLP90R_THE
#define _BRSFC_CV_PW_RFFRIR
#define _BRSFC_CV_PW_RFFS
#define _BRSFC_CV_PW_RFGIR01
#define _BRSFC_CV_PW_RFGIR02
#define _BRSFC_CV_PW_RFMONTIPUP
#define _BRSFC_CV_PW_RFS
#define _BRSFC_CV_PW_RFS5FPH
#define _BRSFC_CV_PW_RFSE1
#define _BRSFC_CV_PW_RFSE2
#define _BRSFC_CV_PW_RFSE3
#define _BRSFC_CV_PW_RFSE4
#define _BRSFC_CV_PW_RFSE5
#define _BRSFC_CV_PW_RFSE6
#define _BRSFC_CV_PW_RFSSF
#define _BRSFC_CV_PW_RFSSFH
#define _BRSFC_CV_PW_RFSX1
#define _BRSFC_CV_PW_RFSX2
#define _BRSFC_CV_PW_RFSY1
#define _BRSFC_CV_PW_RFSY2
#define _BRSFC_CV_PW_RFSZ1
#define _BRSFC_CV_PW_RFSZ2
#define _BRSFC_CV_PW_RFTIPUP
#define _BRSFC_CV_PW_ROT_SLICE1
#define _BRSFC_CV_PW_ROT_SLICE2
#define _BRSFC_CV_PW_ROT_UPDATE_CARDIACSAT
#define _BRSFC_CV_PW_ROT_UPDATE_E1
#define _BRSFC_CV_PW_ROT_UPDATE_E2
#define _BRSFC_CV_PW_ROT_UPDATE_E3
#define _BRSFC_CV_PW_ROT_UPDATE_E4
#define _BRSFC_CV_PW_ROT_UPDATE_E5
#define _BRSFC_CV_PW_ROT_UPDATE_E6
#define _BRSFC_CV_PW_ROT_UPDATE_EK1
#define _BRSFC_CV_PW_ROT_UPDATE_EK2
#define _BRSFC_CV_PW_ROT_UPDATE_EK3
#define _BRSFC_CV_PW_ROT_UPDATE_EK4
#define _BRSFC_CV_PW_ROT_UPDATE_EK5
#define _BRSFC_CV_PW_ROT_UPDATE_EK6
#define _BRSFC_CV_PW_ROT_UPDATE_GIR
#define _BRSFC_CV_PW_ROT_UPDATE_GIRE01
#define _BRSFC_CV_PW_ROT_UPDATE_GIRK01
#define _BRSFC_CV_PW_ROT_UPDATE_GIRK02
#define _BRSFC_CV_PW_ROT_UPDATE_RFGIR02
#define _BRSFC_CV_PW_ROT_UPDATE_X1
#define _BRSFC_CV_PW_ROT_UPDATE_X2
#define _BRSFC_CV_PW_ROT_UPDATE_XK1
#define _BRSFC_CV_PW_ROT_UPDATE_XK2
#define _BRSFC_CV_PW_ROT_UPDATE_Y1
#define _BRSFC_CV_PW_ROT_UPDATE_Y2
#define _BRSFC_CV_PW_ROT_UPDATE_YK1
#define _BRSFC_CV_PW_ROT_UPDATE_YK2
#define _BRSFC_CV_PW_ROT_UPDATE_Z1
#define _BRSFC_CV_PW_ROT_UPDATE_Z2
#define _BRSFC_CV_PW_ROT_UPDATE_ZK1
#define _BRSFC_CV_PW_ROT_UPDATE_ZK2
#define _BRSFC_CV_PW_ROTSLICE
#define _BRSFC_CV_PW_ROTUPDATE
#define _BRSFC_CV_PW_ROTUPDATE_GIR
#define _BRSFC_CV_PW_RTICFH
#define _BRSFC_CV_PW_SATRAMPX
#define _BRSFC_CV_PW_SATRAMPY
#define _BRSFC_CV_PW_SATRAMPZ
#define _BRSFC_CV_PW_SDIXON
#define _BRSFC_CV_PW_SDIXON2
#define _BRSFC_CV_PW_SS_RAMPZ
#define _BRSFC_CV_PW_STICFH
#define _BRSFC_CV_PW_THCYLR
#define _BRSFC_CV_PW_THCYLRTIPUP
#define _BRSFC_CV_PW_THETARF1
#define _BRSFC_CV_PW_XDELAY
#define _BRSFC_CV_PW_XDIXON
#define _BRSFC_CV_PW_XRESPGATE
#define _BRSFC_CV_PW_XTICFH
#define _BRSFC_CV_PW_Y_CCS_NULL
#define _BRSFC_CV_PW_YDIXON
#define _BRSFC_CV_PW_YTICFH
#define _BRSFC_CV_PW_ZDIXON
#define _BRSFC_CV_PW_ZTICFH
#define _BRSFC_CV_PX_PWMTIME
#define _BRSFC_CV_PY_PWMTIME
#define _BRSFC_CV_PZ_PWMTIME
#define _BRSFC_CV_QUICKSTEP_FLAG
#define _BRSFC_CV_RADFB_FLAG
#define _BRSFC_CV_RATIO_RFFLP90
#define _BRSFC_CV_RATIO_RFFLP90R
#define _BRSFC_CV_RAWDATA
#define _BRSFC_CV_RAWMODE
#define _BRSFC_CV_RBW
#define _BRSFC_CV_RCVN_DDA
#define _BRSFC_CV_RCVN_FLAG
#define _BRSFC_CV_RCVN_LOOPS
#define _BRSFC_CV_RCVN_NEX
#define _BRSFC_CV_RCVN_TDAQ
#define _BRSFC_CV_RCVN_TR
#define _BRSFC_CV_RCVN_XRES
#define _BRSFC_CV_RCVNLOGGRD
#define _BRSFC_CV_RCVR_UB_OFF
#define _BRSFC_CV_RD_EXT_DTG
#define _BRSFC_CV_RD_EXT_RS
#define _BRSFC_CV_RDA_MON
#define _BRSFC_CV_READ_AXIS
#define _BRSFC_CV_READ_COL
#define _BRSFC_CV_READMONLOC
#define _BRSFC_CV_REC_MODE
#define _BRSFC_CV_RECON_1024
#define _BRSFC_CV_RECON_IMAG_IMAGE
#define _BRSFC_CV_RECON_MAG_IMAGE
#define _BRSFC_CV_RECON_PHA_IMAGE
#define _BRSFC_CV_RECON_QMAG_IMAGE
#define _BRSFC_CV_RECTFOV_NPW_SUPPORT
#define _BRSFC_CV_REFOCUS
#define _BRSFC_CV_REGVIEWORDERMODE
#define _BRSFC_CV_REGION_ORDER_MODE
#define _BRSFC_CV_REILLY_MODE
#define _BRSFC_CV_RES_DEPHASE
#define _BRSFC_CV_RES_DUMMYRF
#define _BRSFC_CV_RES_GX1
#define _BRSFC_CV_RES_GXSPIRAL
#define _BRSFC_CV_RES_GXSPIRAL2
#define _BRSFC_CV_RES_GY1
#define _BRSFC_CV_RES_GY1R
#define _BRSFC_CV_RES_GYCYLR
#define _BRSFC_CV_RES_GYCYLRA
#define _BRSFC_CV_RES_GYCYLRATIPUP
#define _BRSFC_CV_RES_GYCYLRTIPUP
#define _BRSFC_CV_RES_GYSPIRAL
#define _BRSFC_CV_RES_GYSPIRAL2
#define _BRSFC_CV_RES_GZCOMB
#define _BRSFC_CV_RES_GZCOMBHTR
#define _BRSFC_CV_RES_GZCYLR
#define _BRSFC_CV_RES_GZCYLRA
#define _BRSFC_CV_RES_GZCYLRATIPUP
#define _BRSFC_CV_RES_GZCYLRTIPUP
#define _BRSFC_CV_RES_GZP
#define _BRSFC_CV_RES_GZPHTR
#define _BRSFC_CV_RES_GZRF0
#define _BRSFC_CV_RES_GZRF0CFH
#define _BRSFC_CV_RES_GZRF1
#define _BRSFC_CV_RES_GZRFFRIR
#define _BRSFC_CV_RES_GZRFGIR01
#define _BRSFC_CV_RES_GZRFGIR02
#define _BRSFC_CV_RES_GZVLW
#define _BRSFC_CV_RES_HARD180
#define _BRSFC_CV_RES_OMEGA_HS_RFCSSAT
#define _BRSFC_CV_RES_OMEGA_IR0
#define _BRSFC_CV_RES_OMEGA_RFFRIR
#define _BRSFC_CV_RES_OMEGA_RFGIR01
#define _BRSFC_CV_RES_OMEGA_RFGIR02
#define _BRSFC_CV_RES_OMEGARF0CFH
#define _BRSFC_CV_RES_RF0
#define _BRSFC_CV_RES_RF0CFH
#define _BRSFC_CV_RES_RF1
#define _BRSFC_CV_RES_RF180
#define _BRSFC_CV_RES_RF1_FULL
#define _BRSFC_CV_RES_RF1_TEMP
#define _BRSFC_CV_RES_RF1AS
#define _BRSFC_CV_RES_RF1CFH
#define _BRSFC_CV_RES_RF1CFL
#define _BRSFC_CV_RES_RF1DTG
#define _BRSFC_CV_RES_RF1FTG
#define _BRSFC_CV_RES_RF1HTR
#define _BRSFC_CV_RES_RF1MON
#define _BRSFC_CV_RES_RF1MPS1
#define _BRSFC_CV_RES_RF1RS
#define _BRSFC_CV_RES_RF1TM
#define _BRSFC_CV_RES_RF1XTG
#define _BRSFC_CV_RES_RF2CFH
#define _BRSFC_CV_RES_RF2FTG
#define _BRSFC_CV_RES_RF2MON
#define _BRSFC_CV_RES_RF2MPS1
#define _BRSFC_CV_RES_RF2XTG
#define _BRSFC_CV_RES_RF3CFH
#define _BRSFC_CV_RES_RF3FTG
#define _BRSFC_CV_RES_RF3XTG
#define _BRSFC_CV_RES_RF4CFH
#define _BRSFC_CV_RES_RF4XTG
#define _BRSFC_CV_RES_RF90
#define _BRSFC_CV_RES_RFBDTG
#define _BRSFC_CV_RES_RFBRS
#define _BRSFC_CV_RES_RFCSSAT
#define _BRSFC_CV_RES_RFCYLR
#define _BRSFC_CV_RES_RFCYLRTIPUP
#define _BRSFC_CV_RES_RFFLP180
#define _BRSFC_CV_RES_RFFLP180_THE
#define _BRSFC_CV_RES_RFFLP90
#define _BRSFC_CV_RES_RFFLP90_THE
#define _BRSFC_CV_RES_RFFLP90R
#define _BRSFC_CV_RES_RFFLP90R_THE
#define _BRSFC_CV_RES_RFFRIR
#define _BRSFC_CV_RES_RFFS
#define _BRSFC_CV_RES_RFGIR01
#define _BRSFC_CV_RES_RFGIR02
#define _BRSFC_CV_RES_RFMONTIPUP
#define _BRSFC_CV_RES_RFS5FPH
#define _BRSFC_CV_RES_RFSE1
#define _BRSFC_CV_RES_RFSE2
#define _BRSFC_CV_RES_RFSE3
#define _BRSFC_CV_RES_RFSE4
#define _BRSFC_CV_RES_RFSE5
#define _BRSFC_CV_RES_RFSE6
#define _BRSFC_CV_RES_RFSSF
#define _BRSFC_CV_RES_RFSSFH
#define _BRSFC_CV_RES_RFSX1
#define _BRSFC_CV_RES_RFSX2
#define _BRSFC_CV_RES_RFSY1
#define _BRSFC_CV_RES_RFSY2
#define _BRSFC_CV_RES_RFSZ1
#define _BRSFC_CV_RES_RFSZ2
#define _BRSFC_CV_RES_RFTIPUP
#define _BRSFC_CV_RES_THCYLR
#define _BRSFC_CV_RES_THCYLRTIPUP
#define _BRSFC_CV_RES_THETARF1
#define _BRSFC_CV_RES_THETARFBDTG
#define _BRSFC_CV_RES_THETARFBRS
#define _BRSFC_CV_RESP_CENTK_PERCENT
#define _BRSFC_CV_RESP_DDA
#define _BRSFC_CV_RESP_GATE_TRIG_SW
#define _BRSFC_CV_RESP_NEX
#define _BRSFC_CV_RESPDC
#define _BRSFC_CV_RESPGATE_FLAG
#define _BRSFC_CV_RESPSEQCORE
#define _BRSFC_CV_RETROPC_EXTRA
#define _BRSFC_CV_REVERSELOOPORDER_FLAG
#define _BRSFC_CV_REVERSE_CENTRIC_FLAG
#define _BRSFC_CV_REVERSE_ELLIPT_FLAG
#define _BRSFC_CV_REVERSE_FIRST_REGION_FLAG
#define _BRSFC_CV_REVERSE_VIEWS
#define _BRSFC_CV_REWINDER_FLAG
#define _BRSFC_CV_REWINDING_TIME
#define _BRSFC_CV_RF0_PHASE
#define _BRSFC_CV_RF0_PULSE_TYPE
#define _BRSFC_CV_RF1_PULSE_TYPE
#define _BRSFC_CV_RF1DTG_SCALE
#define _BRSFC_CV_RF1DTG_TYPE
#define _BRSFC_CV_RF1MON_SHIFT
#define _BRSFC_CV_RF1RS_SCALE
#define _BRSFC_CV_RF1RS_TYPE
#define _BRSFC_CV_RF2MON_SHIFT
#define _BRSFC_CV_RF_SCALE_FAC
#define _BRSFC_CV_RFB1OPT_COUNTER
#define _BRSFC_CV_RFB1OPT_FLAG
#define _BRSFC_CV_RFCONF
#define _BRSFC_CV_RFFRIR_PHASE
#define _BRSFC_CV_RFGIR01_PHASE
#define _BRSFC_CV_RFGIR01_START
#define _BRSFC_CV_RFGIR01_TIME
#define _BRSFC_CV_RFGIR01_TYPE
#define _BRSFC_CV_RFGIR01_WAIT
#define _BRSFC_CV_RFGIR02_PHASE
#define _BRSFC_CV_RFGIR02_START
#define _BRSFC_CV_RFGIR02_TIME
#define _BRSFC_CV_RFGIR02_TYPE
#define _BRSFC_CV_RFGIR02_WAIT
#define _BRSFC_CV_RFSAFETYOPT_TIMEFLAG
#define _BRSFC_CV_RFSHIM_B1FACTOR
#define _BRSFC_CV_RFSHIM_BASELINE
#define _BRSFC_CV_RFSHIM_ETL
#define _BRSFC_CV_RFSHIM_FLIPANGLE
#define _BRSFC_CV_RFSHIM_FOV
#define _BRSFC_CV_RFSHIM_PTSIZE
#define _BRSFC_CV_RFSHIM_SLQUANT
#define _BRSFC_CV_RFSHIM_SLTHICK
#define _BRSFC_CV_RFSHIM_XRES
#define _BRSFC_CV_RFSHIM_YRES
#define _BRSFC_CV_RFSLOT_HARD180
#define _BRSFC_CV_RFSLOT_OMEGA_HS_RFCSSAT
#define _BRSFC_CV_RFSLOT_OMEGA_IR0
#define _BRSFC_CV_RFSLOT_OMEGA_RFFRIR
#define _BRSFC_CV_RFSLOT_OMEGA_RFGIR01
#define _BRSFC_CV_RFSLOT_OMEGA_RFGIR02
#define _BRSFC_CV_RFSLOT_OMEGARF0CFH
#define _BRSFC_CV_RFSLOT_RF90
#define _BRSFC_CV_RFSLOT_RFFLP180
#define _BRSFC_CV_RFSLOT_RFFLP180_THE
#define _BRSFC_CV_RFSLOT_RFFLP90
#define _BRSFC_CV_RFSLOT_RFFLP90_THE
#define _BRSFC_CV_RFSLOT_RFFLP90R
#define _BRSFC_CV_RFSLOT_RFFLP90R_THE
#define _BRSFC_CV_RFSLOT_RFTIPUP
#define _BRSFC_CV_RFTYPE
#define _BRSFC_CV_RFUPACV
#define _BRSFC_CV_RGFEATURE_ENABLE
#define _BRSFC_CV_RH2DSCALE
#define _BRSFC_CV_RH3DGW_INTERPTYPE
#define _BRSFC_CV_RH3DSCALE
#define _BRSFC_CV_RH3DWINA
#define _BRSFC_CV_RH3DWINQ
#define _BRSFC_CV_RH3DWINTYPE
#define _BRSFC_CV_RHFILLMAPLSW
#define _BRSFC_CV_RHFILLMAPMSW
#define _BRSFC_CV_RH_IME_CLARIVIEW_EDGE
#define _BRSFC_CV_RH_IME_CLARIVIEW_FOCUS
#define _BRSFC_CV_RH_IME_CLARIVIEW_SMOOTH
#define _BRSFC_CV_RH_IME_CLARIVIEW_TYPE
#define _BRSFC_CV_RH_IME_DEFINEFILTER_NR
#define _BRSFC_CV_RH_IME_DEFINEFILTER_SH
#define _BRSFC_CV_RH_IME_SCIC_EDGE
#define _BRSFC_CV_RH_IME_SCIC_ENABLE
#define _BRSFC_CV_RH_IME_SCIC_FOCUS
#define _BRSFC_CV_RH_IME_SCIC_GAUSS
#define _BRSFC_CV_RH_IME_SCIC_REDUCTION
#define _BRSFC_CV_RH_IME_SCIC_SMOOTH
#define _BRSFC_CV_RH_IME_SCIC_THRESHOLD
#define _BRSFC_CV_RH_LOW_PASS_NEX_FILTER_WIDTH
#define _BRSFC_CV_RH_RC_ENHANCE_ENABLE
#define _BRSFC_CV_RHALPHA
#define _BRSFC_CV_RHALT
#define _BRSFC_CV_RHAPFOV
#define _BRSFC_CV_RHAPHASES
#define _BRSFC_CV_RHAPP
#define _BRSFC_CV_RHAPP_OPTION
#define _BRSFC_CV_RHASL_PERF_WEIGHTED_SCALE
#define _BRSFC_CV_RHASSET
#define _BRSFC_CV_RHASSET_R
#define _BRSFC_CV_RHASSET_ALT_CAL
#define _BRSFC_CV_RHASSET_CALTHRESH
#define _BRSFC_CV_RHASSET_LOCALTX
#define _BRSFC_CV_RHASSET_PHASES
#define _BRSFC_CV_RHASSET_SLWRAP
#define _BRSFC_CV_RHASSET_TORSO
#define _BRSFC_CV_RHASSETSL_R
#define _BRSFC_CV_RHB0MAP
#define _BRSFC_CV_RHBLANK
#define _BRSFC_CV_RHBLINE
#define _BRSFC_CV_RHBP_CORR
#define _BRSFC_CV_RHCAL_NEX_VECTOR
#define _BRSFC_CV_RHCAL_OPTIONS
#define _BRSFC_CV_RHCAL_PASS_SET_VECTOR
#define _BRSFC_CV_RHCAL_WEIGHT_VECTOR
#define _BRSFC_CV_RHCALMODE
#define _BRSFC_CV_RHCHANNEL_COMBINE_FILTER_BETA
#define _BRSFC_CV_RHCHANNEL_COMBINE_FILTER_TYPE
#define _BRSFC_CV_RHCHANNEL_COMBINE_FILTER_WIDTH
#define _BRSFC_CV_RHCHANNEL_COMBINE_METHOD
#define _BRSFC_CV_RHCLIPMAX
#define _BRSFC_CV_RHCLIPMIN
#define _BRSFC_CV_RHCOILNO
#define _BRSFC_CV_RHCORRELATIONTHRESHOLD
#define _BRSFC_CV_RHCPHASES
#define _BRSFC_CV_RHCRRTIME
#define _BRSFC_CV_RHCS_CONSISTENCY
#define _BRSFC_CV_RHCS_FACTOR
#define _BRSFC_CV_RHCS_FLAG
#define _BRSFC_CV_RHCS_MAXITER
#define _BRSFC_CV_RHCS_PH_STRIDE
#define _BRSFC_CV_RHCS_SL_STRIDE
#define _BRSFC_CV_RHCTR
#define _BRSFC_CV_RHDAB0E
#define _BRSFC_CV_RHDAB0S
#define _BRSFC_CV_RHDACQCTRL
#define _BRSFC_CV_RHDATACQ
#define _BRSFC_CV_RHDAVIEWSPERBLADE
#define _BRSFC_CV_RHDAXRES
#define _BRSFC_CV_RHDAYRES
#define _BRSFC_CV_RHDBGRECON
#define _BRSFC_CV_RHDDAOVER
#define _BRSFC_CV_RHDENSITYFACTOR
#define _BRSFC_CV_RHDF
#define _BRSFC_CV_RHDFM
#define _BRSFC_CV_RHDFMDEBUG
#define _BRSFC_CV_RHDFMNAVSPERPASS
#define _BRSFC_CV_RHDFMNAVSPERVIEW
#define _BRSFC_CV_RHDFMPTSIZE
#define _BRSFC_CV_RHDFMRBW
#define _BRSFC_CV_RHDFMTHRESHOLD
#define _BRSFC_CV_RHDFMXRES
#define _BRSFC_CV_RHDIFNEXT2
#define _BRSFC_CV_RHDISKACQCTRL
#define _BRSFC_CV_RHDISPFOV
#define _BRSFC_CV_RHDOFFSET
#define _BRSFC_CV_RHDPTYPE
#define _BRSFC_CV_RHDWNAVCOEFF
#define _BRSFC_CV_RHDWNAVCOR
#define _BRSFC_CV_RHDWNAVCORECHO
#define _BRSFC_CV_RHDWNAVESHOT
#define _BRSFC_CV_RHDWNAVEVIEW
#define _BRSFC_CV_RHDWNAVSSHOT
#define _BRSFC_CV_RHDWNAVSVIEW
#define _BRSFC_CV_RHDWNAVVIEW
#define _BRSFC_CV_RHECH2SKIP
#define _BRSFC_CV_RHECHOPC_CTRL
#define _BRSFC_CV_RHECHOPC_EXTRA_BOT
#define _BRSFC_CV_RHECHOPC_PRIMARY_YFIRST
#define _BRSFC_CV_RHECHOPC_REVERSE_YFIRST
#define _BRSFC_CV_RHECHOPC_YLINES
#define _BRSFC_CV_RHECHOPC_YXFITORDER
#define _BRSFC_CV_RHECHOPC_ZLINES
#define _BRSFC_CV_RHECTRICKS_INPUT_REGIONS
#define _BRSFC_CV_RHECTRICKS_NUM_REGIONS
#define _BRSFC_CV_RHESP
#define _BRSFC_CV_RHETL
#define _BRSFC_CV_RHEXCITERFREQS
#define _BRSFC_CV_RHEXCITERUSAGE
#define _BRSFC_CV_RHEXECCTRL
#define _BRSFC_CV_RHEXTRA_FRAMES_BOT
#define _BRSFC_CV_RHEXTRA_FRAMES_TOP
#define _BRSFC_CV_RHFAST_REC
#define _BRSFC_CV_RHFATWATER
#define _BRSFC_CV_RHFCINEARW
#define _BRSFC_CV_RHFCINEMODE
#define _BRSFC_CV_RHFDCTRL
#define _BRSFC_CV_RHFEEXTRA
#define _BRSFC_CV_RHFERME
#define _BRSFC_CV_RHFERMR
#define _BRSFC_CV_RHFERMW
#define _BRSFC_CV_RHFIESTA
#define _BRSFC_CV_RHFLIPFILTER
#define _BRSFC_CV_RHFORMAT
#define _BRSFC_CV_RHFREQSCALE
#define _BRSFC_CV_RHFRSIZE
#define _BRSFC_CV_RHGRADMODE
#define _BRSFC_CV_RHGRIDCONTROL
#define _BRSFC_CV_RHHDBESTKY
#define _BRSFC_CV_RHHEOVER
#define _BRSFC_CV_RHHERAWFLT
#define _BRSFC_CV_RHHERAWFLT_BEFAMP
#define _BRSFC_CV_RHHERAWFLT_BEFNTRAN
#define _BRSFC_CV_RHHERAWFLT_BEFNWIN
#define _BRSFC_CV_RHHERAWFLT_HPFAMP
#define _BRSFC_CV_RHHNITER
#define _BRSFC_CV_RHHNOVER
#define _BRSFC_CV_RHHOEC_FIT_ORDER
#define _BRSFC_CV_RHHOECC
#define _BRSFC_CV_RHILEAVES
#define _BRSFC_CV_RHIMSIZE
#define _BRSFC_CV_RHINCRPASS
#define _BRSFC_CV_RHINITPASS
#define _BRSFC_CV_RHKACQ_UID
#define _BRSFC_CV_RHKT_CAL_FACTOR
#define _BRSFC_CV_RHKT_CALWIDTH_PH
#define _BRSFC_CV_RHKT_CALWIDTH_SL
#define _BRSFC_CV_RHKT_FACTOR
#define _BRSFC_CV_RHKYDIR
#define _BRSFC_CV_RHLCFIESTA
#define _BRSFC_CV_RHLCFIESTA_PHASE
#define _BRSFC_CV_RHLEFT_BLANK
#define _BRSFC_CV_RHMAXCOEF1A
#define _BRSFC_CV_RHMAXCOEF1B
#define _BRSFC_CV_RHMAXCOEF1C
#define _BRSFC_CV_RHMAXCOEF1D
#define _BRSFC_CV_RHMAXCOEF2A
#define _BRSFC_CV_RHMAXCOEF2B
#define _BRSFC_CV_RHMAXCOEF2C
#define _BRSFC_CV_RHMAXCOEF2D
#define _BRSFC_CV_RHMAXCOEF3A
#define _BRSFC_CV_RHMAXCOEF3B
#define _BRSFC_CV_RHMAXCOEF3C
#define _BRSFC_CV_RHMAXCOEF3D
#define _BRSFC_CV_RHMAXGRAD
#define _BRSFC_CV_RHMB_FACTOR
#define _BRSFC_CV_RHMB_SLICE_FOV_SHIFT_FACTOR
#define _BRSFC_CV_RHMB_SLICE_ORDER_SIGN
#define _BRSFC_CV_RHMEDAL_DOWN_KERNEL_SIZE
#define _BRSFC_CV_RHMEDAL_ECHO_ORDER
#define _BRSFC_CV_RHMEDAL_ENDING_SLICE
#define _BRSFC_CV_RHMEDAL_MODE
#define _BRSFC_CV_RHMEDAL_NSTACK_SIZE
#define _BRSFC_CV_RHMEDAL_PARAM
#define _BRSFC_CV_RHMEDAL_SMOOTH_KERNEL_SIZE
#define _BRSFC_CV_RHMEDAL_STARTING_SLICE
#define _BRSFC_CV_RHMEDAL_UP_KERNEL_SIZE
#define _BRSFC_CV_RHMETH
#define _BRSFC_CV_RHMETHOD
#define _BRSFC_CV_RHMOTIONCOMP
#define _BRSFC_CV_RHMPHASETYPE
#define _BRSFC_CV_RHNAVS
#define _BRSFC_CV_RHNCOILLIMIT
#define _BRSFC_CV_RHNCOILSEL
#define _BRSFC_CV_RHNCYCLES_CINE
#define _BRSFC_CV_RHNECHO
#define _BRSFC_CV_RHNEW_WND_LEVEL_FLAG
#define _BRSFC_CV_RHNEX
#define _BRSFC_CV_RHNEX_UNACQUIRED
#define _BRSFC_CV_RHNFRAMES
#define _BRSFC_CV_RHNONCART_DUAL_TRAJ
#define _BRSFC_CV_RHNONCART_GRID_FACTOR
#define _BRSFC_CV_RHNONCART_TRAJ_KMAX_RATIO
#define _BRSFC_CV_RHNONCART_TRAJ_MERGE_END
#define _BRSFC_CV_RHNONCART_TRAJ_MERGE_START
#define _BRSFC_CV_RHNONCART_TRAJ_MODE
#define _BRSFC_CV_RHNPASSES
#define _BRSFC_CV_RHNPHASES
#define _BRSFC_CV_RHNPOMP
#define _BRSFC_CV_RHNPWFACTOR
#define _BRSFC_CV_RHNREFSLICES
#define _BRSFC_CV_RHNSLICES
#define _BRSFC_CV_RHNSPOKES_HIGHRES
#define _BRSFC_CV_RHNSPOKES_LOWRES
#define _BRSFC_CV_RHNTRAN
#define _BRSFC_CV_RHNUMCOILCONFIGS
#define _BRSFC_CV_RHNUMBVALS
#define _BRSFC_CV_RHNUMDIFDIRS
#define _BRSFC_CV_RHNUMSLABS
#define _BRSFC_CV_RHNVIRCCHANNEL
#define _BRSFC_CV_RHNWIN
#define _BRSFC_CV_RHOSCANS
#define _BRSFC_CV_RHOVERSAMPLINGFACTOR
#define _BRSFC_CV_RHOVL
#define _BRSFC_CV_RHPASFRAME
#define _BRSFC_CV_RHPC_RATIONALSCALE
#define _BRSFC_CV_RHPC_REF_SKIP
#define _BRSFC_CV_RHPC_REF_START
#define _BRSFC_CV_RHPC_REF_STOP
#define _BRSFC_CV_RHPCBESTKY
#define _BRSFC_CV_RHPCCOIL
#define _BRSFC_CV_RHPCCON
#define _BRSFC_CV_RHPCCONFITWT
#define _BRSFC_CV_RHPCCONFIX
#define _BRSFC_CV_RHPCCONNORM
#define _BRSFC_CV_RHPCCONNPTS
#define _BRSFC_CV_RHPCCONORDER
#define _BRSFC_CV_RHPCCONSLOPE
#define _BRSFC_CV_RHPCCTRL
#define _BRSFC_CV_RHPCDISCBEG
#define _BRSFC_CV_RHPCDISCEND
#define _BRSFC_CV_RHPCDISCMID
#define _BRSFC_CV_RHPCEXTCORR
#define _BRSFC_CV_RHPCFITORIG
#define _BRSFC_CV_RHPCGRAPH
#define _BRSFC_CV_RHPCILEAVE
#define _BRSFC_CV_RHPCINVFT
#define _BRSFC_CV_RHPCLIN
#define _BRSFC_CV_RHPCLINAVG
#define _BRSFC_CV_RHPCLINFITWT
#define _BRSFC_CV_RHPCLINFIX
#define _BRSFC_CV_RHPCLINNORM
#define _BRSFC_CV_RHPCLINNPTS
#define _BRSFC_CV_RHPCLINORDER
#define _BRSFC_CV_RHPCLINSLOPE
#define _BRSFC_CV_RHPCMAG
#define _BRSFC_CV_RHPCMULTEGRP
#define _BRSFC_CV_RHPCSHOTFIRST
#define _BRSFC_CV_RHPCSHOTLAST
#define _BRSFC_CV_RHPCSNORE
#define _BRSFC_CV_RHPCSPACIAL
#define _BRSFC_CV_RHPCSPACIAL_DYNAMIC
#define _BRSFC_CV_RHPCTEMPORAL
#define _BRSFC_CV_RHPCTEST
#define _BRSFC_CV_RHPCTHRESPCT
#define _BRSFC_CV_RHPCTHRESPTS
#define _BRSFC_CV_RHPHASESCALE
#define _BRSFC_CV_RHPHSEN_PIXEL_OFFSET
#define _BRSFC_CV_RHPOSITION_DETECTION
#define _BRSFC_CV_RHPROPELLERCTRL
#define _BRSFC_CV_RHPTSIZE
#define _BRSFC_CV_RHPURE
#define _BRSFC_CV_RHPURE_BLUR
#define _BRSFC_CV_RHPURE_BLUR_ENABLE
#define _BRSFC_CV_RHPURE_CAL_REAPODIZATION
#define _BRSFC_CV_RHPURE_DERIVED_CAL_FRACTION
#define _BRSFC_CV_RHPURE_FILTERING_MODE
#define _BRSFC_CV_RHPURE_LAMBDA
#define _BRSFC_CV_RHPURE_MIX_ALPHA
#define _BRSFC_CV_RHPURE_MIX_ANISO_BLUR
#define _BRSFC_CV_RHPURE_MIX_ANISO_DILATE_DIST
#define _BRSFC_CV_RHPURE_MIX_ANISO_ERODE_DIST
#define _BRSFC_CV_RHPURE_MIX_BLUR
#define _BRSFC_CV_RHPURE_MIX_BLUR_ENABLE
#define _BRSFC_CV_RHPURE_MIX_DILATE_DIST
#define _BRSFC_CV_RHPURE_MIX_ERODE_DIST
#define _BRSFC_CV_RHPURE_MIX_EXP_WT
#define _BRSFC_CV_RHPURE_MIX_LAMBDA
#define _BRSFC_CV_RHPURE_MIX_OTSU_CLASS_QTY
#define _BRSFC_CV_RHPURE_MIX_TUNING_FACTOR_BODY
#define _BRSFC_CV_RHPURE_MIX_TUNING_FACTOR_SURFACE
#define _BRSFC_CV_RHPURE_SCALE_FACTOR
#define _BRSFC_CV_RHPURE_TUNING_FACTOR_BODY
#define _BRSFC_CV_RHPURE_TUNING_FACTOR_SURFACE
#define _BRSFC_CV_RHPURECHANNEL
#define _BRSFC_CV_RHPUREFILTER
#define _BRSFC_CV_RHRADIUSA
#define _BRSFC_CV_RHRADIUSB
#define _BRSFC_CV_RHRAWSIZE
#define _BRSFC_CV_RHRAWSIZEVIEW
#define _BRSFC_CV_RHRC3DCINECTRL
#define _BRSFC_CV_RHRC_CARDT1MAP_CTRL
#define _BRSFC_CV_RHRC_MOCO_CTRL
#define _BRSFC_CV_RHRCCTRL
#define _BRSFC_CV_RHRCDIXPROC
#define _BRSFC_CV_RHRCIDEAL
#define _BRSFC_CV_RHRCIDEALCTRL
#define _BRSFC_CV_RHRCMAVRIC_BIN_SEPARATION
#define _BRSFC_CV_RHRCMAVRIC_CONTROL
#define _BRSFC_CV_RHRCMAVRIC_IMAGE
#define _BRSFC_CV_RHRCXRES
#define _BRSFC_CV_RHRCYRES
#define _BRSFC_CV_RHRECON
#define _BRSFC_CV_RHRECV_FREQ_E
#define _BRSFC_CV_RHRECV_FREQ_S
#define _BRSFC_CV_RHREF
#define _BRSFC_CV_RHREFFRAMEP
#define _BRSFC_CV_RHREFFRAMES
#define _BRSFC_CV_RHREPS
#define _BRSFC_CV_RHRETRO_CONTROL
#define _BRSFC_CV_RHRIGHT_BLANK
#define _BRSFC_CV_RHRLFOV
#define _BRSFC_CV_RHROTATIONTHRESHOLD
#define _BRSFC_CV_RHSCANCENT
#define _BRSFC_CV_RHSCANFOV
#define _BRSFC_CV_RHSCNFRAME
#define _BRSFC_CV_RHSHIFTTHRESHOLD
#define _BRSFC_CV_RHSIFOV
#define _BRSFC_CV_RHSLBLANK
#define _BRSFC_CV_RHSLEWMAX
#define _BRSFC_CV_RHSNRNOISE
#define _BRSFC_CV_RHSPECCSIDIMS
#define _BRSFC_CV_RHSPECRESCSIX
#define _BRSFC_CV_RHSPECRESCSIY
#define _BRSFC_CV_RHSPECRESCSIZ
#define _BRSFC_CV_RHSPECROILENX
#define _BRSFC_CV_RHSPECROILENY
#define _BRSFC_CV_RHSPECROILENZ
#define _BRSFC_CV_RHSPECROILOCX
#define _BRSFC_CV_RHSPECROILOCY
#define _BRSFC_CV_RHSPECROILOCZ
#define _BRSFC_CV_RHSPECWIDTH
#define _BRSFC_CV_RHSSPSAVE
#define _BRSFC_CV_RHSWIFTENABLE
#define _BRSFC_CV_RHTE
#define _BRSFC_CV_RHTE2
#define _BRSFC_CV_RHTEDIFF
#define _BRSFC_CV_RHTRICKSTYPE
#define _BRSFC_CV_RHTSAMP
#define _BRSFC_CV_RHTYPE
#define _BRSFC_CV_RHTYPE1
#define _BRSFC_CV_RHUDASAVE
#define _BRSFC_CV_RHUSER0
#define _BRSFC_CV_RHUSER1
#define _BRSFC_CV_RHUSER10
#define _BRSFC_CV_RHUSER11
#define _BRSFC_CV_RHUSER12
#define _BRSFC_CV_RHUSER13
#define _BRSFC_CV_RHUSER14
#define _BRSFC_CV_RHUSER15
#define _BRSFC_CV_RHUSER16
#define _BRSFC_CV_RHUSER17
#define _BRSFC_CV_RHUSER18
#define _BRSFC_CV_RHUSER19
#define _BRSFC_CV_RHUSER2
#define _BRSFC_CV_RHUSER20
#define _BRSFC_CV_RHUSER21
#define _BRSFC_CV_RHUSER22
#define _BRSFC_CV_RHUSER23
#define _BRSFC_CV_RHUSER24
#define _BRSFC_CV_RHUSER25
#define _BRSFC_CV_RHUSER26
#define _BRSFC_CV_RHUSER27
#define _BRSFC_CV_RHUSER28
#define _BRSFC_CV_RHUSER29
#define _BRSFC_CV_RHUSER3
#define _BRSFC_CV_RHUSER30
#define _BRSFC_CV_RHUSER31
#define _BRSFC_CV_RHUSER32
#define _BRSFC_CV_RHUSER33
#define _BRSFC_CV_RHUSER34
#define _BRSFC_CV_RHUSER35
#define _BRSFC_CV_RHUSER36
#define _BRSFC_CV_RHUSER37
#define _BRSFC_CV_RHUSER38
#define _BRSFC_CV_RHUSER39
#define _BRSFC_CV_RHUSER4
#define _BRSFC_CV_RHUSER40
#define _BRSFC_CV_RHUSER41
#define _BRSFC_CV_RHUSER42
#define _BRSFC_CV_RHUSER43
#define _BRSFC_CV_RHUSER44
#define _BRSFC_CV_RHUSER45
#define _BRSFC_CV_RHUSER46
#define _BRSFC_CV_RHUSER47
#define _BRSFC_CV_RHUSER48
#define _BRSFC_CV_RHUSER5
#define _BRSFC_CV_RHUSER6
#define _BRSFC_CV_RHUSER7
#define _BRSFC_CV_RHUSER8
#define _BRSFC_CV_RHUSER9
#define _BRSFC_CV_RHUSER_USAGE_TAG
#define _BRSFC_CV_RHUTCTRL
#define _BRSFC_CV_RHVCOEFXA
#define _BRSFC_CV_RHVCOEFXB
#define _BRSFC_CV_RHVCOEFXC
#define _BRSFC_CV_RHVCOEFXD
#define _BRSFC_CV_RHVCOEFYA
#define _BRSFC_CV_RHVCOEFYB
#define _BRSFC_CV_RHVCOEFYC
#define _BRSFC_CV_RHVCOEFYD
#define _BRSFC_CV_RHVCOEFZA
#define _BRSFC_CV_RHVCOEFZB
#define _BRSFC_CV_RHVCOEFZC
#define _BRSFC_CV_RHVCOEFZD
#define _BRSFC_CV_RHVENC
#define _BRSFC_CV_RHVIBRANT
#define _BRSFC_CV_RHVIEWSHARING3D
#define _BRSFC_CV_RHVIRCOILCHANNELS
#define _BRSFC_CV_RHVIRCOILTYPE
#define _BRSFC_CV_RHVIRCOILUNIF
#define _BRSFC_CV_RHVIRCPOLICY
#define _BRSFC_CV_RHVIRSENSTYPE
#define _BRSFC_CV_RHVMCOEF1
#define _BRSFC_CV_RHVMCOEF2
#define _BRSFC_CV_RHVMCOEF3
#define _BRSFC_CV_RHVMCOEF4
#define _BRSFC_CV_RHVPS
#define _BRSFC_CV_RHVQUANT
#define _BRSFC_CV_RHVRGF
#define _BRSFC_CV_RHVRGFXRES
#define _BRSFC_CV_RHVTYPE
#define _BRSFC_CV_RHVVSAIMGS
#define _BRSFC_CV_RHVVSGENDER
#define _BRSFC_CV_RHVVSTR
#define _BRSFC_CV_RHWIENER
#define _BRSFC_CV_RHWIENERA
#define _BRSFC_CV_RHWIENERB
#define _BRSFC_CV_RHWIENERESP
#define _BRSFC_CV_RHWIENERT2
#define _BRSFC_CV_RHWND_HIGH_HIST
#define _BRSFC_CV_RHWND_IMAGE_HIST_AREA
#define _BRSFC_CV_RHWND_LOWER_HIST
#define _BRSFC_CV_RHXOFF
#define _BRSFC_CV_RHYOFF
#define _BRSFC_CV_RHZEROPH
#define _BRSFC_CV_RHZIPFACT
#define _BRSFC_CV_RL_FLOW
#define _BRSFC_CV_ROT_DELAY
#define _BRSFC_CV_ROT_DELAY_GIR
#define _BRSFC_CV_ROTATEFLAG
#define _BRSFC_CV_RS_DDA
#define _BRSFC_CV_RS_ESP
#define _BRSFC_CV_RS_ISO_DELAY
#define _BRSFC_CV_RS_OFF90
#define _BRSFC_CV_RSAMP_TIME
#define _BRSFC_CV_RSAXIAL_FLAG
#define _BRSFC_CV_RSLOGGRD
#define _BRSFC_CV_RSPHORDER
#define _BRSFC_CV_RSSPGR_FLAG
#define _BRSFC_CV_RST_EXA
#define _BRSFC_CV_RST_EXB
#define _BRSFC_CV_RTCA_INSTEPS_FLIP
#define _BRSFC_CV_RTCA_INSTEPS_FOV
#define _BRSFC_CV_RTCA_INSTEPS_SLTHICK
#define _BRSFC_CV_RTCA_MAX_FLIP
#define _BRSFC_CV_RTCA_MAX_FOV
#define _BRSFC_CV_RTCA_MAX_SLTHICK
#define _BRSFC_CV_RTCA_MIN_FLIP
#define _BRSFC_CV_RTCA_MIN_FOV
#define _BRSFC_CV_RTCA_MIN_SLABTHICK
#define _BRSFC_CV_RTCA_MIN_SLTHICK
#define _BRSFC_CV_RTIA3D_BUFFERS
#define _BRSFC_CV_RTIA3D_EFF_SLABTHICK
#define _BRSFC_CV_RTIA3D_IRP_FLAG
#define _BRSFC_CV_RTIA3D_ORIGINAL_FLIP
#define _BRSFC_CV_RTIA3D_ORIGINAL_FOV
#define _BRSFC_CV_RTIA3D_ORIGINAL_SLTHICK
#define _BRSFC_CV_RTIA3D_PASS
#define _BRSFC_CV_RTIA3D_PHORDER
#define _BRSFC_CV_RTIA3D_REPEAT_VIEWS
#define _BRSFC_CV_RTIA3D_RESTRICTED_NAV_FLAG
#define _BRSFC_CV_RTIA3D_SAT_FLIP
#define _BRSFC_CV_RTIA3D_SAT_POS
#define _BRSFC_CV_RTIA3D_SAT_VIEWS
#define _BRSFC_CV_RTIA3D_SLICE_THINNING_FACTOR
#define _BRSFC_CV_RTIA3D_THKSLAB_PROJ_ENABLE_FLAG
#define _BRSFC_CV_RTIA3D_THKSLAB_PROJ_FLAG
#define _BRSFC_CV_RTIA3D_TURBO
#define _BRSFC_CV_RTIA_FIRST_SCAN_FLAG
#define _BRSFC_CV_RTIA_FOV_FREQ_SCALE
#define _BRSFC_CV_RTIA_FOV_PHASE_SCALE
#define _BRSFC_CV_RTIA_INIT_PHASOFF
#define _BRSFC_CV_RTIA_INIT_RLOC
#define _BRSFC_CV_RTIA_INIT_TLOC
#define _BRSFC_CV_RTIA_ORIG_PHASOFF
#define _BRSFC_CV_RTIA_ORIG_RLOC
#define _BRSFC_CV_RTIA_ORIG_TLOC
#define _BRSFC_CV_RTIA_REL_FOV_FREQ_SCALE
#define _BRSFC_CV_RTIA_REL_FOV_PHASE_SCALE
#define _BRSFC_CV_RTIA_SATGAPZNEG
#define _BRSFC_CV_RTIA_SATGAPZPOS
#define _BRSFC_CV_RTIA_SLTHICK_SCALE
#define _BRSFC_CV_RTPEND_QUIET_DDA
#define _BRSFC_CV_RTPRESULTWAIT
#define _BRSFC_CV_RTSAR_ENABLE_FLAG
#define _BRSFC_CV_RTSAR_FIRST_SERIES_FLAG
#define _BRSFC_CV_RUN_EVAL_FROM_GET_FLAG
#define _BRSFC_CV_RVSSLICEENC
#define _BRSFC_CV_S5FPHAREA
#define _BRSFC_CV_SAMPLEDPOINTS
#define _BRSFC_CV_SAR_AMP
#define _BRSFC_CV_SAR_CORRECTION_FACTOR
#define _BRSFC_CV_SAR_CYCLE
#define _BRSFC_CV_SAR_WIDTH
#define _BRSFC_CV_SAT_TGLIMIT
#define _BRSFC_CV_SAT_DDA
#define _BRSFC_CV_SAT_DEBUG
#define _BRSFC_CV_SAT_NEWGEO
#define _BRSFC_CV_SAT_OBL_DEBUG
#define _BRSFC_CV_SAT_PULSE_TYPE
#define _BRSFC_CV_SAT_REPS
#define _BRSFC_CV_SAT_ROT_DF_NUM
#define _BRSFC_CV_SAT_ROT_EX_NUM
#define _BRSFC_CV_SAT_ROT_INDEX
#define _BRSFC_CV_SATGAPXNEG
#define _BRSFC_CV_SATGAPXPOS
#define _BRSFC_CV_SATGAPYNEG
#define _BRSFC_CV_SATGAPYPOS
#define _BRSFC_CV_SATGAPZNEG
#define _BRSFC_CV_SATGAPZPOS
#define _BRSFC_CV_SATLOCE1
#define _BRSFC_CV_SATLOCE2
#define _BRSFC_CV_SATLOCE3
#define _BRSFC_CV_SATLOCE4
#define _BRSFC_CV_SATLOCE5
#define _BRSFC_CV_SATLOCE6
#define _BRSFC_CV_SATLOGGRD
#define _BRSFC_CV_SATSPACE1
#define _BRSFC_CV_SATSPACE2
#define _BRSFC_CV_SATSPACE3
#define _BRSFC_CV_SATSPACE4
#define _BRSFC_CV_SATSPACE5
#define _BRSFC_CV_SATSPACE6
#define _BRSFC_CV_SATSPACEX1
#define _BRSFC_CV_SATSPACEX2
#define _BRSFC_CV_SATSPACEY1
#define _BRSFC_CV_SATSPACEY2
#define _BRSFC_CV_SATSPACEZ1
#define _BRSFC_CV_SATSPACEZ2
#define _BRSFC_CV_SATTHICKDFX
#define _BRSFC_CV_SATTHICKDFY
#define _BRSFC_CV_SATTHICKDFZ
#define _BRSFC_CV_SATTHICKX1
#define _BRSFC_CV_SATTHICKX2
#define _BRSFC_CV_SATTHICKY1
#define _BRSFC_CV_SATTHICKY2
#define _BRSFC_CV_SATTHICKZ1
#define _BRSFC_CV_SATTHICKZ2
#define _BRSFC_CV_SATVIEW
#define _BRSFC_CV_SATXLOCNEG
#define _BRSFC_CV_SATXLOCPOS
#define _BRSFC_CV_SATYLOCNEG
#define _BRSFC_CV_SATYLOCPOS
#define _BRSFC_CV_SATZLOCA
#define _BRSFC_CV_SATZLOCB
#define _BRSFC_CV_SATZLOCNEG
#define _BRSFC_CV_SATZLOCPOS
#define _BRSFC_CV_SAVE_CFXFULL
#define _BRSFC_CV_SAVE_CFXIPEAK
#define _BRSFC_CV_SAVE_CFYFULL
#define _BRSFC_CV_SAVE_CFYIPEAK
#define _BRSFC_CV_SAVE_CFZFULL
#define _BRSFC_CV_SAVE_CFZIPEAK
#define _BRSFC_CV_SAVE_FFT
#define _BRSFC_CV_SAVE_GMAX
#define _BRSFC_CV_SAVE_GRADOPT_TEFACTOR
#define _BRSFC_CV_SAVE_GRADOPT_TRFACTOR
#define _BRSFC_CV_SAVE_GRADOPT_RATIO
#define _BRSFC_CV_SAVE_GRADOPT_SCALE
#define _BRSFC_CV_SAVE_GRAD_SPEC_FLAG
#define _BRSFC_CV_SAVE_OGSFX1
#define _BRSFC_CV_SAVE_OGSFX2
#define _BRSFC_CV_SAVE_OGSFXWEX
#define _BRSFC_CV_SAVE_OGSFY
#define _BRSFC_CV_SAVE_OGSFYK
#define _BRSFC_CV_SAVE_OGSFZ
#define _BRSFC_CV_SAVE_RAMPTIME
#define _BRSFC_CV_SAVE_SRATE
#define _BRSFC_CV_SAVEDATA
#define _BRSFC_CV_SAVEINTER
#define _BRSFC_CV_SBM_BAK_PITSCAN
#define _BRSFC_CV_SBM_CVS_CHANGED
#define _BRSFC_CV_SBM_CVS_OLD
#define _BRSFC_CV_SBM_DDA
#define _BRSFC_CV_SBM_DDA_MAX
#define _BRSFC_CV_SBM_DDA_MIN
#define _BRSFC_CV_SBM_DEBUG
#define _BRSFC_CV_SBM_DUMMY_NUM
#define _BRSFC_CV_SBM_FLAG
#define _BRSFC_CV_SBM_GRADIENT_METHOD
#define _BRSFC_CV_SBM_GX1_SCALE
#define _BRSFC_CV_SBM_GXW_SCALE
#define _BRSFC_CV_SBM_GXWEX_SCALE
#define _BRSFC_CV_SBM_GY1_SCALE
#define _BRSFC_CV_SBM_GY1R_SCALE
#define _BRSFC_CV_SBM_GZCOMB_SCALE
#define _BRSFC_CV_SBM_GZP_SCALE
#define _BRSFC_CV_SBM_MARGIN
#define _BRSFC_CV_SBM_MPS2_IMAGING_NUM
#define _BRSFC_CV_SBM_PITSCAN_CHANGED
#define _BRSFC_CV_SBM_PITSCAN_LIMIT
#define _BRSFC_CV_SBM_PITSCAN_OLD
#define _BRSFC_CV_SBM_SMARTDERATING_FACTOR
#define _BRSFC_CV_SBM_SUM_DUMMY
#define _BRSFC_CV_SBM_TIME_LIMIT
#define _BRSFC_CV_SBM_TIME_LIMIT_MAX
#define _BRSFC_CV_SBM_TIME_LIMIT_MIN
#define _BRSFC_CV_SBM_TIME_LIMIT_RATIO
#define _BRSFC_CV_SBM_WAITING_TIME
#define _BRSFC_CV_SBM_Y_NUM
#define _BRSFC_CV_SBM_Z_NUM
#define _BRSFC_CV_SCALE_FAC
#define _BRSFC_CV_SCALE_TR
#define _BRSFC_CV_SCALE_TR_GRAD
#define _BRSFC_CV_SCANCLOCKTIME
#define _BRSFC_CV_SCANRCVR
#define _BRSFC_CV_SCANRF1_INST
#define _BRSFC_CV_SCANRF1TM_INST
#define _BRSFC_CV_SCANSAT0
#define _BRSFC_CV_SCANSATINT
#define _BRSFC_CV_SCPTRG
#define _BRSFC_CV_SEED
#define _BRSFC_CV_SEEDDEF
#define _BRSFC_CV_SEG_DEBUG
#define _BRSFC_CV_SEG_FOUNDVPS_FLAG
#define _BRSFC_CV_SEG_SORT_DIR
#define _BRSFC_CV_SEG_TOTALPES
#define _BRSFC_CV_SEG_VPS_MAX
#define _BRSFC_CV_SEG_VPS_MIN
#define _BRSFC_CV_SEG_VPS_RANGE
#define _BRSFC_CV_SEG_VPS_TARGET
#define _BRSFC_CV_SEGMENT_TR
#define _BRSFC_CV_SEGMENTED_FLAG
#define _BRSFC_CV_SEP3D
#define _BRSFC_CV_SEQ3DDUMMYTR
#define _BRSFC_CV_SEQ3DTR
#define _BRSFC_CV_SEQENTRYINDEX
#define _BRSFC_CV_SEQ_NECHO
#define _BRSFC_CV_SEQ_TYPE
#define _BRSFC_CV_SERVICEMODE
#define _BRSFC_CV_SET_REALTIME_ROTMAT
#define _BRSFC_CV_SHOW_RTFILTS
#define _BRSFC_CV_SI_FLOW
#define _BRSFC_CV_SIFSETWOKEY
#define _BRSFC_CV_SIGMA1
#define _BRSFC_CV_SIGMA2
#define _BRSFC_CV_SIGRAMMODE
#define _BRSFC_CV_SILENT_MODE
#define _BRSFC_CV_SILENT_SLEW_RATE
#define _BRSFC_CV_SIMULATION
#define _BRSFC_CV_SKIP_INITIALIZE_DBDTOPT
#define _BRSFC_CV_SKIP_MINSEQSEG
#define _BRSFC_CV_SKIP_NAVIGATOR_PRESCAN
#define _BRSFC_CV_SKIP_ROTMAT_SEARCH
#define _BRSFC_CV_SKIP_WAVEFORM_ROTMAT_CHECK
#define _BRSFC_CV_SL_PER_CHEM
#define _BRSFC_CV_SLAB_FACT
#define _BRSFC_CV_SLAB_WRAP_CORR
#define _BRSFC_CV_SLABTRACKING_FLAG
#define _BRSFC_CV_SLDELAY
#define _BRSFC_CV_SLDELTIME
#define _BRSFC_CV_SLFREQ
#define _BRSFC_CV_SLICE_COL
#define _BRSFC_CV_SLICE_DDA
#define _BRSFC_CV_SLICE_ORDER
#define _BRSFC_CV_SLICE_SIZE
#define _BRSFC_CV_SLICECNT
#define _BRSFC_CV_SLICEZP
#define _BRSFC_CV_SLORDER
#define _BRSFC_CV_SLQ_SHOTS
#define _BRSFC_CV_SLQUANT1
#define _BRSFC_CV_SLQUANT_PER_TRIG
#define _BRSFC_CV_SLTHICK_RFGIR01
#define _BRSFC_CV_SLTHICK_RFGIR02
#define _BRSFC_CV_SLTHICK_SCALE
#define _BRSFC_CV_SMARTPREPEDRFLAG
#define _BRSFC_CV_SMARTP_RTPEND_WAIT
#define _BRSFC_CV_SMARTPREP_FLAG
#define _BRSFC_CV_SMARTPREP_WAS_ON
#define _BRSFC_CV_SMOOTHEC
#define _BRSFC_CV_SP_FIRST_SCAN
#define _BRSFC_CV_SP_SAT
#define _BRSFC_CV_SP_SATCARD_LOC
#define _BRSFC_CV_SP_SATEND
#define _BRSFC_CV_SP_SATSTART
#define _BRSFC_CV_SP_SATTIME
#define _BRSFC_CV_SPECDWELLS
#define _BRSFC_CV_SPECIR_DELAY
#define _BRSFC_CV_SPECIR_FLAG
#define _BRSFC_CV_SPECIR_TI
#define _BRSFC_CV_SPECIRSOL
#define _BRSFC_CV_SPECNAVS
#define _BRSFC_CV_SPECNEX
#define _BRSFC_CV_SPECNUC
#define _BRSFC_CV_SPECPTS
#define _BRSFC_CV_SPECSOLREPS
#define _BRSFC_CV_SPECWIDTH
#define _BRSFC_CV_SPGR_FLAG
#define _BRSFC_CV_SPLIT_DAB
#define _BRSFC_CV_SPREP_DEBUG_FLAG
#define _BRSFC_CV_SPREP_SAVE_RAW_DATA
#define _BRSFC_CV_SPREP_TIMING_FLAG
#define _BRSFC_CV_SPSAT_HOST_DEBUG
#define _BRSFC_CV_SPSAT_RFUPA
#define _BRSFC_CV_SPSAT_SYS_TYPE
#define _BRSFC_CV_SPSP_MIN_OPVTHICK
#define _BRSFC_CV_SR_FLPVENC_LIMIT
#define _BRSFC_CV_SRATE
#define _BRSFC_CV_SRATE_X
#define _BRSFC_CV_SRATE_Y
#define _BRSFC_CV_SRATE_Z
#define _BRSFC_CV_SRDERATE
#define _BRSFC_CV_SS_CONVOLUTION_FLAG
#define _BRSFC_CV_SS_FA_SCALE_DEBUG
#define _BRSFC_CV_SS_FA_SCALING_FLAG
#define _BRSFC_CV_SS_MAXOFF
#define _BRSFC_CV_SS_MAXOFFEX
#define _BRSFC_CV_SS_MIN_SLTHK
#define _BRSFC_CV_SS_MINSLTHK1
#define _BRSFC_CV_SS_OVERRIDE
#define _BRSFC_CV_SS_PSD_SLTHICK
#define _BRSFC_CV_SS_REWINDER_FLAG
#define _BRSFC_CV_SS_RF1
#define _BRSFC_CV_SS_RF_WAIT
#define _BRSFC_CV_SSFAT
#define _BRSFC_CV_SSFAT_FREQ
#define _BRSFC_CV_SSFAT_KAISER
#define _BRSFC_CV_SSFAT_NULLB
#define _BRSFC_CV_SSFAT_RAMP
#define _BRSFC_CV_SSFAT_RFSPOIL
#define _BRSFC_CV_SSFAT_ROTATE
#define _BRSFC_CV_SSFAT_VO
#define _BRSFC_CV_SSFHAREA
#define _BRSFC_CV_SSFP_FLAG
#define _BRSFC_CV_SSFP_SYMMETRY_FLAG
#define _BRSFC_CV_SSFSE_IR_ON
#define _BRSFC_CV_SSP_PWISI7
#define _BRSFC_CV_SSZCHOP
#define _BRSFC_CV_START_GYCYLRA
#define _BRSFC_CV_START_GYCYLRATIPUP
#define _BRSFC_CV_START_GZCYLRA
#define _BRSFC_CV_START_GZCYLRATIPUP
#define _BRSFC_CV_STD_AMP
#define _BRSFC_CV_STEAM_PG_GAP
#define _BRSFC_CV_STOPWATCHFLAG
#define _BRSFC_CV_STRE_FLAG
#define _BRSFC_CV_SUN_DONE_FLAG
#define _BRSFC_CV_SUN_SUCCESS_FLAG1
#define _BRSFC_CV_SUN_SUCCESS_FLAG2
#define _BRSFC_CV_SWAN_FLAG
#define _BRSFC_CV_SWANFIRSTTE
#define _BRSFC_CV_SWAP_FAT_CS
#define _BRSFC_CV_SWAP_MON_ZY
#define _BRSFC_CV_SWAP_MONPLANE
#define _BRSFC_CV_SYSTEM_TYPE
#define _BRSFC_CV_T1FLAIR_FLAG
#define _BRSFC_CV_T2PK_AREA
#define _BRSFC_CV_T2PK_DELAY
#define _BRSFC_CV_T2PREP_FLAG
#define _BRSFC_CV_T2PREP_NUM180
#define _BRSFC_CV_T2PREP_RATE
#define _BRSFC_CV_T2PREP_T180
#define _BRSFC_CV_T2PREP_TSEQ
#define _BRSFC_CV_T_EXA
#define _BRSFC_CV_T_EXA_CYLR
#define _BRSFC_CV_T_EXAAS
#define _BRSFC_CV_T_EXB
#define _BRSFC_CV_T_EXB_CYLR
#define _BRSFC_CV_T_RD1A
#define _BRSFC_CV_T_RD1A_FRAC
#define _BRSFC_CV_T_RD1A_FULL
#define _BRSFC_CV_T_RDB
#define _BRSFC_CV_T_RDB_CYLR
#define _BRSFC_CV_T_RDB_FRAC
#define _BRSFC_CV_T_RDB_FULL
#define _BRSFC_CV_T_SLICE2READ
#define _BRSFC_CV_T_SLICEREADGAP
#define _BRSFC_CV_TA_180SP
#define _BRSFC_CV_TABLEACCEL
#define _BRSFC_CV_TABLEDECEL
#define _BRSFC_CV_TABLESPEED
#define _BRSFC_CV_TARG_DR
#define _BRSFC_CV_TARG_DR_RAMP
#define _BRSFC_CV_TARGET_CFH_CRUSHER
#define _BRSFC_CV_TARGET_CFH_CRUSHER2
#define _BRSFC_CV_TARGET_TI
#define _BRSFC_CV_TB_180SP
#define _BRSFC_CV_TD0
#define _BRSFC_CV_TD0AS
#define _BRSFC_CV_TD0DTG
#define _BRSFC_CV_TD0RS
#define _BRSFC_CV_TDAQ
#define _BRSFC_CV_TDEL1_TIME
#define _BRSFC_CV_TDEL1_TMP
#define _BRSFC_CV_TE_180SP
#define _BRSFC_CV_TE_AS
#define _BRSFC_CV_TE_TIME
#define _BRSFC_CV_TEMP_FACTOR
#define _BRSFC_CV_TEMP_FLOAT
#define _BRSFC_CV_TEMP_GRD
#define _BRSFC_CV_TEMP_RES_RF1AS
#define _BRSFC_CV_TEMP_RES_RF1CFH
#define _BRSFC_CV_TEMP_RES_RF1CFL
#define _BRSFC_CV_TEMP_RES_RF1FTG
#define _BRSFC_CV_TEMP_RES_RF1MON
#define _BRSFC_CV_TEMP_RES_RF2FTG
#define _BRSFC_CV_TEMP_RES_RF2MON
#define _BRSFC_CV_TEMP_RES_RF2MPS1
#define _BRSFC_CV_TEMP_RES_RF2XTG
#define _BRSFC_CV_TEMP_RES_RF3FTG
#define _BRSFC_CV_TEMP_RES_RFMONTIPUP
#define _BRSFC_CV_TEMP_RES_RFSE1
#define _BRSFC_CV_TEMP_RES_RFSE2
#define _BRSFC_CV_TEMP_RES_RFSE3
#define _BRSFC_CV_TEMP_RES_RFSE4
#define _BRSFC_CV_TEMP_RES_RFSE5
#define _BRSFC_CV_TEMP_RES_RFSE6
#define _BRSFC_CV_TEMP_RES_RFSX1
#define _BRSFC_CV_TEMP_RES_RFSX2
#define _BRSFC_CV_TEMP_RES_RFSY1
#define _BRSFC_CV_TEMP_RES_RFSY2
#define _BRSFC_CV_TEMP_RES_RFSZ1
#define _BRSFC_CV_TEMP_RES_RFSZ2
#define _BRSFC_CV_TEMP_RF
#define _BRSFC_CV_TFE_EXTRA
#define _BRSFC_CV_TG_1_2_PW
#define _BRSFC_CV_TG_AXIAL
#define _BRSFC_CV_TG_KILLER_AXIS
#define _BRSFC_CV_TG_READ_AXIS
#define _BRSFC_CV_TGCAP
#define _BRSFC_CV_TGFOV
#define _BRSFC_CV_TGWINDOW
#define _BRSFC_CV_THETA
#define _BRSFC_CV_THETATYPE
#define _BRSFC_CV_THICKPS_MOD
#define _BRSFC_CV_THK_RF0
#define _BRSFC_CV_THK_RF0CFH
#define _BRSFC_CV_THK_RF1
#define _BRSFC_CV_THK_RF1AS
#define _BRSFC_CV_THK_RF1CFH
#define _BRSFC_CV_THK_RF1CFL
#define _BRSFC_CV_THK_RF1FTG
#define _BRSFC_CV_THK_RF1MON
#define _BRSFC_CV_THK_RF1TM
#define _BRSFC_CV_THK_RF2FTG
#define _BRSFC_CV_THK_RF2MON
#define _BRSFC_CV_THK_RF2MPS1
#define _BRSFC_CV_THK_RF2XTG
#define _BRSFC_CV_THK_RF3FTG
#define _BRSFC_CV_THK_RFFRIR
#define _BRSFC_CV_THK_RFGIR01
#define _BRSFC_CV_THK_RFGIR02
#define _BRSFC_CV_THK_RFMONTIPUP
#define _BRSFC_CV_THK_RFSE1
#define _BRSFC_CV_THK_RFSE2
#define _BRSFC_CV_THK_RFSE3
#define _BRSFC_CV_THK_RFSE4
#define _BRSFC_CV_THK_RFSE5
#define _BRSFC_CV_THK_RFSE6
#define _BRSFC_CV_THK_RFSX1
#define _BRSFC_CV_THK_RFSX2
#define _BRSFC_CV_THK_RFSY1
#define _BRSFC_CV_THK_RFSY2
#define _BRSFC_CV_THK_RFSZ1
#define _BRSFC_CV_THK_RFSZ2
#define _BRSFC_CV_THREEDPKTDLY
#define _BRSFC_CV_TI_RFGIR01
#define _BRSFC_CV_TI_RFGIR02
#define _BRSFC_CV_TIME_BETWEEN_RFFLP180_VENC
#define _BRSFC_CV_TIME_BETWEEN_RFFLP90_VENC
#define _BRSFC_CV_TIME_BETWEEN_VENC1_2
#define _BRSFC_CV_TIME_BETWEEN_VENC2_3
#define _BRSFC_CV_TIME_BETWEEN_VENC_RFFLP180
#define _BRSFC_CV_TIME_BETWEEN_VENC_RFFLP90R
#define _BRSFC_CV_TIME_FSPREP
#define _BRSFC_CV_TIME_KILLER
#define _BRSFC_CV_TIME_PGEN
#define _BRSFC_CV_TIME_S5FPPREP
#define _BRSFC_CV_TIME_SEQWAIT
#define _BRSFC_CV_TIME_SPOILER
#define _BRSFC_CV_TIME_SSFPREP
#define _BRSFC_CV_TIME_SSI
#define _BRSFC_CV_TIME_SSI_PRE
#define _BRSFC_CV_TIME_SSIAS
#define _BRSFC_CV_TIME_SSIDTG
#define _BRSFC_CV_TIME_SSIRS
#define _BRSFC_CV_TIME_WAIT2
#define _BRSFC_CV_TIME_WAIT3
#define _BRSFC_CV_TIME_WAIT4
#define _BRSFC_CV_TIMEFCX
#define _BRSFC_CV_TIMEFCY
#define _BRSFC_CV_TIMEFCZ
#define _BRSFC_CV_TIMEFCZ_ECHO1
#define _BRSFC_CV_TLEAD
#define _BRSFC_CV_TLEAD_CYLNAV
#define _BRSFC_CV_TLEAD_MONITOR
#define _BRSFC_CV_TLEAD_MONTIPUP
#define _BRSFC_CV_TLEADAS
#define _BRSFC_CV_TLEADCS
#define _BRSFC_CV_TLEADDTG
#define _BRSFC_CV_TLEADRS
#define _BRSFC_CV_TM_AXIS
#define _BRSFC_CV_TM_DISDAQS
#define _BRSFC_CV_TM_FLAG
#define _BRSFC_CV_TM_FLIP
#define _BRSFC_CV_TM_LOCSTEP
#define _BRSFC_CV_TM_NEX
#define _BRSFC_CV_TM_NS
#define _BRSFC_CV_TM_POS_START
#define _BRSFC_CV_TM_PREPSLICE_FLAG
#define _BRSFC_CV_TM_SCALE
#define _BRSFC_CV_TM_SLTHICK
#define _BRSFC_CV_TM_SPIRAL_DELAY
#define _BRSFC_CV_TM_TIME
#define _BRSFC_CV_TM_XLOC
#define _BRSFC_CV_TM_YLOC
#define _BRSFC_CV_TMIN
#define _BRSFC_CV_TMIN_MON
#define _BRSFC_CV_TMIN_MONTIPUP
#define _BRSFC_CV_TMIN_REDUCED
#define _BRSFC_CV_TMIN_SATOFF
#define _BRSFC_CV_TMIN_TOTAL
#define _BRSFC_CV_TMPBW
#define _BRSFC_CV_TMPBW1
#define _BRSFC_CV_TNS_LEN
#define _BRSFC_CV_TNSLENGTH
#define _BRSFC_CV_TOF_LOWFLIP_ASSET_FLAG
#define _BRSFC_CV_TOPOFHEAD
#define _BRSFC_CV_TOTAL_ACQ_POINTS
#define _BRSFC_CV_TOTAL_ACQ_REGIONS
#define _BRSFC_CV_TOTAL_AREA_GX
#define _BRSFC_CV_TOTAL_AREA_GXFC
#define _BRSFC_CV_TOTAL_AREA_GZ
#define _BRSFC_CV_TOTAL_AREA_GZFC
#define _BRSFC_CV_TOTAL_QUIET_DDA
#define _BRSFC_CV_TOTALECREGIONS
#define _BRSFC_CV_TR_AS
#define _BRSFC_CV_TR_DTG
#define _BRSFC_CV_TR_PAD
#define _BRSFC_CV_TR_PREP_RS
#define _BRSFC_CV_TR_RS
#define _BRSFC_CV_TRACK_FLAG
#define _BRSFC_CV_TRACKER_QUANT
#define _BRSFC_CV_TRANSPOSE_MONLOC
#define _BRSFC_CV_TRICKS_CHECK
#define _BRSFC_CV_TRICKS_DEBUG
#define _BRSFC_CV_TRICKS_DELAY
#define _BRSFC_CV_TRICKS_FLAG
#define _BRSFC_CV_TRICKS_INDEX
#define _BRSFC_CV_TRICKS_INDEX2
#define _BRSFC_CV_TRICKS_MASK_TIME
#define _BRSFC_CV_TRICKS_MAXECHO
#define _BRSFC_CV_TRICKS_MAXPHASES
#define _BRSFC_CV_TRICKS_MAXSERIES
#define _BRSFC_CV_TRICKS_MINECHO
#define _BRSFC_CV_TRICKS_STOP
#define _BRSFC_CV_TRICKS_TRANSITION_VIEWS
#define _BRSFC_CV_TRICKSDDA
#define _BRSFC_CV_TRIG_APS2
#define _BRSFC_CV_TRIG_MPS2
#define _BRSFC_CV_TRIG_PRESCAN
#define _BRSFC_CV_TRIG_SCAN
#define _BRSFC_CV_TRIGGERSTATE
#define _BRSFC_CV_TRIGGER_DELAY_SILENT_COUNTDOWN
#define _BRSFC_CV_TRIGGER_DELAY_WOSP
#define _BRSFC_CV_TRUENEX
#define _BRSFC_CV_TSAMP
#define _BRSFC_CV_TSEQ_GZK
#define _BRSFC_CV_TSEQ_IRPREP
#define _BRSFC_CV_TSEQ_MSDE
#define _BRSFC_CV_TSEQ_PREP_FRIR
#define _BRSFC_CV_TSP
#define _BRSFC_CV_TURBO_CEMRA_ENABLE
#define _BRSFC_CV_TURBO_CEMRA_FLAG
#define _BRSFC_CV_TURBO_FLAG
#define _BRSFC_CV_TWAITT2PREP
#define _BRSFC_CV_UGFSF_FLAG
#define _BRSFC_CV_UGFSF_FLAT_DDA
#define _BRSFC_CV_UGFSF_LINEAR_RAMP_DOWN
#define _BRSFC_CV_UGFSF_RAMP_DDA
#define _BRSFC_CV_UGFSF_SHOT_DELAY
#define _BRSFC_CV_UGFSF_SLICE_DDA
#define _BRSFC_CV_UGFSF_SLICE_ORDER_FLAG
#define _BRSFC_CV_UGFSF_VIEW_ORDER_FLAG
#define _BRSFC_CV_COILINFO_TGT
#define _BRSFC_CV_VOLRECCOILINFO_TGT
#define _BRSFC_CV_DATA_ACQ_ORDER
#define _BRSFC_CV_GIR_INFO
#define _BRSFC_CV_GRADX
#define _BRSFC_CV_GRADY
#define _BRSFC_CV_GRADZ
#define _BRSFC_CV_PHASE_OFF
#define _BRSFC_CV_PRESSCFH_INFO
#define _BRSFC_CV_PSC_INFO
#define _BRSFC_CV_PSD_FILT_SPEC
#define _BRSFC_CV_RFPULSE
#define _BRSFC_CV_RFPULSEINFO
#define _BRSFC_CV_ASRSP_INFO
#define _BRSFC_CV_DTGRSP_INFO
#define _BRSFC_CV_MON_RSP_INFO2
#define _BRSFC_CV_MON_RSP_INFO
#define _BRSFC_CV_RSP_INFO
#define _BRSFC_CV_RSRSP_INFO
#define _BRSFC_CV_RSP_PSC_INFO
#define _BRSFC_CV_ASSCAN_INFO
#define _BRSFC_CV_SCAN_INFO
#define _BRSFC_CV_SCAN_INFO_BASE
#define _BRSFC_CV_SLAB_OFF
#define _BRSFC_CV_BRS_VIEWTAB
#define _BRSFC_CV_TXCOILINFO_TGT
#define _BRSFC_CV_HGZSSFN
#define _BRSFC_CV_PIAMVAL1
#define _BRSFC_CV_PIAMVAL2
#define _BRSFC_CV_PIAMVAL3
#define _BRSFC_CV_PIAMVAL4
#define _BRSFC_CV_PIAMVAL5
#define _BRSFC_CV_PIAMVAL6
#define _BRSFC_CV_PIDFIRECVAL2
#define _BRSFC_CV_PIDFIRECVAL3
#define _BRSFC_CV_PIDFIRECVAL4
#define _BRSFC_CV_PIDFIRECVAL5
#define _BRSFC_CV_PIDIFAXVAL1
#define _BRSFC_CV_PIDIFAXVAL2
#define _BRSFC_CV_PIDIFAXVAL3
#define _BRSFC_CV_PIDIFAXVAL4
#define _BRSFC_CV_PIDIFAXVAL5
#define _BRSFC_CV_PIDIFAXVAL6
#define _BRSFC_CV_PIDIFRECVAL1
#define _BRSFC_CV_PITRECOVERYLABEL
#define _BRSFC_CV_SSGZFILE
#define _BRSFC_CV_SSRFFILE
#define _BRSFC_CV_BODY_SAR_TABLE
#define _BRSFC_CV_BRS_MFA_ANGLES
#define _BRSFC_CV_EG_SAT_ROT
#define _BRSFC_CV_EXTREMITY_SAR_TABLE
#define _BRSFC_CV_FLP_VENC_X
#define _BRSFC_CV_FLP_VENC_Y
#define _BRSFC_CV_FLP_VENC_Z
#define _BRSFC_CV_HEAD_SAR_TABLE
#define _BRSFC_CV_OSFP_VFA
#define _BRSFC_CV_RATIO_RFFLP180
#define _BRSFC_CV_RFGIR01_INFO
#define _BRSFC_CV_RFGIR02_INFO
#define _BRSFC_CV_RHDIFFUSION_GRAD_AMP
#define _BRSFC_CV_ROTMATRIX
#define _BRSFC_CV_XYZ_BASE
#define _BRSFC_CV_PSFREQ_OFFSET
#define _BRSFC_CV_PHASEDONESCHEDULE
#define _BRSFC_CV_REGIONSCHEDULE
#define _BRSFC_CV_REGIONSSCHEDULE
#define _BRSFC_CV_ARCPHASEREMAPTABLE
#define _BRSFC_CV_ARCSLICEREMAPTABLE
#define _BRSFC_CV_BRS_JUMPTAB
#define _BRSFC_CV_BRS_SAVROT
#define _BRSFC_CV_BRS_XGRAD2
#define _BRSFC_CV_BRS_XGRAD
#define _BRSFC_CV_BRS_YGRAD2
#define _BRSFC_CV_BRS_YGRAD
#define _BRSFC_CV_CUM_REGS_PER_PHASE
#define _BRSFC_CV_CUM_VIEWS_PER_REGION
#define _BRSFC_CV_ECTRICKS_KERNEL_REGIONS
#define _BRSFC_CV_ECTRICKS_MASK_REGIONS
#define _BRSFC_CV_EXTRASPECIAL_SLICE
#define _BRSFC_CV_IA_GZVLWA
#define _BRSFC_CV_IA_GZVLWB
#define _BRSFC_CV_IA_RF1_OSFP
#define _BRSFC_CV_OFF_RFCSZ
#define _BRSFC_CV_OFF_RFCSZ_BASE
#define _BRSFC_CV_PW_GZVL
#define _BRSFC_CV_PW_GZVLA
#define _BRSFC_CV_PW_GZVLD
#define _BRSFC_CV_REGS_PER_PHASE
#define _BRSFC_CV_SAT_ROT_EX_INDICES
#define _BRSFC_CV_SLICETAB
#define _BRSFC_CV_VOLUMETAB2
#define _BRSFC_CV_VOLUMETAB
#define _BRSFC_CV_ZFCTAB
#define _BRSFC_CV_ZFCTAB_ECHO1
#define _BRSFC_CV_PSROT
#define _BRSFC_CV_PSROT_MOD
#define _BRSFC_CV_DTGRSPROT
#define _BRSFC_CV_IPG_ALLOC_INSTR
#define _BRSFC_CV_NAV_CHANNEL_BIT
#define _BRSFC_CV_NAVSCM_CHANNEL_BIT
#define _BRSFC_CV_RFGIR01_ROT_INFO
#define _BRSFC_CV_RFGIR02_ROT_INFO
#define _BRSFC_CV_RSP_PSROT
#define _BRSFC_CV_RSPROT
#define _BRSFC_CV_RSPROT_BASE
#define _BRSFC_CV_RSPROT_GIR
#define _BRSFC_CV_RSPROT_MONITOR
#define _BRSFC_CV_RSPTRIGGER
#define _BRSFC_CV_RSRSPROT
#define _BRSFC_CV_SAT_ROT_MATRICES
#define _BRSFC_CV_MCBIAS_INFO
#define _BRSFC_CV_ASLIMGTAB
#define _BRSFC_CV_ASLNEXTAB
#define _BRSFC_CV_ULIMTE1
#define _BRSFC_CV_ULIMTE2
#define _BRSFC_CV_ULIMTE3
#define _BRSFC_CV_UNACCEL_DAYRES
#define _BRSFC_CV_UNACCEL_RHNFRAMES
#define _BRSFC_CV_UNIPOLAR_FLAG
#define _BRSFC_CV_UPMXDISABLE
#define _BRSFC_CV_USEFIRSTECHOCOMP
#define _BRSFC_CV_USE_DBDT_OPT
#define _BRSFC_CV_USE_ECG_SCANCORE
#define _BRSFC_CV_USE_ERMES
#define _BRSFC_CV_USE_MYSCAN
#define _BRSFC_CV_USE_SLR_INV
#define _BRSFC_CV_USEVENC
#define _BRSFC_CV_VAL15_LOCK
#define _BRSFC_CV_VALID_DECIMATION
#define _BRSFC_CV_VALID_MAX_RBW
#define _BRSFC_CV_VALID_RBW
#define _BRSFC_CV_VALUE_SYSTEM_FLAG
#define _BRSFC_CV_VAS_OVRHD
#define _BRSFC_CV_VAST_MODE
#define _BRSFC_CV_VAST_SYMM
#define _BRSFC_CV_VELOCITY_3IN1
#define _BRSFC_CV_VELOCITY_SINGLE
#define _BRSFC_CV_VELOCITY_VENC
#define _BRSFC_CV_VENC_DIRECTION_BITMASK
#define _BRSFC_CV_VENC_POLARITY_MODE
#define _BRSFC_CV_VIBRANT_FLAG
#define _BRSFC_CV_VIBRANTXV_FLAG
#define _BRSFC_CV_VIEW_PER_SHOT
#define _BRSFC_CV_VIEW_TO_CENTER
#define _BRSFC_CV_VIEWOFFS
#define _BRSFC_CV_VIEWS_PER_SEGMENT
#define _BRSFC_CV_VIEWSHD_NUM
#define _BRSFC_CV_VIEWSPERREGION
#define _BRSFC_CV_VOL_RATIO_EST_REQ
#define _BRSFC_CV_VOL_SCALE_CONSTRAINT_TYPE
#define _BRSFC_CV_VOL_SCALE_TYPE
#define _BRSFC_CV_VOL_SHIFT_CONSTRAINT_TYPE
#define _BRSFC_CV_VOL_SHIFT_TYPE
#define _BRSFC_CV_VRG_SAT
#define _BRSFC_CV_VRGFSAMP
#define _BRSFC_CV_VRGSAT
#define _BRSFC_CV_VSTRTE_FLAG
#define _BRSFC_CV_W_Z1
#define _BRSFC_CV_W_ZFC
#define _BRSFC_CV_WAITTIME
#define _BRSFC_CV_WAIT_FLPK
#define _BRSFC_CV_WAIT_PTS
#define _BRSFC_CV_WG_CFH_RF3
#define _BRSFC_CV_WG_CFH_RF4
#define _BRSFC_CV_WG_CSW_WAIT
#define _BRSFC_CV_WG_DIX_SSPPOST
#define _BRSFC_CV_WG_DIX_SSPPRE
#define _BRSFC_CV_WG_DIX_XPRE
#define _BRSFC_CV_WG_DUMMYRF
#define _BRSFC_CV_WG_GATE_ISI
#define _BRSFC_CV_WG_GX1
#define _BRSFC_CV_WG_GX1AS
#define _BRSFC_CV_WG_GX1BFTG
#define _BRSFC_CV_WG_GX1BXTG
#define _BRSFC_CV_WG_GX1CFH
#define _BRSFC_CV_WG_GX1DTG
#define _BRSFC_CV_WG_GX1FTG
#define _BRSFC_CV_WG_GX1MON
#define _BRSFC_CV_WG_GX1MPS1
#define _BRSFC_CV_WG_GX1RS
#define _BRSFC_CV_WG_GX1TM
#define _BRSFC_CV_WG_GX2
#define _BRSFC_CV_WG_GX2DTG
#define _BRSFC_CV_WG_GX2FTG
#define _BRSFC_CV_WG_GX2RS
#define _BRSFC_CV_WG_GX2TEST
#define _BRSFC_CV_WG_GXB
#define _BRSFC_CV_WG_GXBRSFC1
#define _BRSFC_CV_WG_GXBRSFC2
#define _BRSFC_CV_WG_GXFC
#define _BRSFC_CV_WG_GXFCMON
#define _BRSFC_CV_WG_GXFLPK
#define _BRSFC_CV_WG_GXFLPVENC
#define _BRSFC_CV_WG_GXHYST1
#define _BRSFC_CV_WG_GXHYST2
#define _BRSFC_CV_WG_GXKAS
#define _BRSFC_CV_WG_GXKBSDTG
#define _BRSFC_CV_WG_GXKBSRS
#define _BRSFC_CV_WG_GXKCS
#define _BRSFC_CV_WG_GXKDTG
#define _BRSFC_CV_WG_GXKFS
#define _BRSFC_CV_WG_GXKILL
#define _BRSFC_CV_WG_GXKRCVN
#define _BRSFC_CV_WG_GXKRS
#define _BRSFC_CV_WG_GXKS
#define _BRSFC_CV_WG_GXKSE1
#define _BRSFC_CV_WG_GXKSE2
#define _BRSFC_CV_WG_GXKSE3
#define _BRSFC_CV_WG_GXKSE4
#define _BRSFC_CV_WG_GXKSE5
#define _BRSFC_CV_WG_GXKSE6
#define _BRSFC_CV_WG_GXKSP
#define _BRSFC_CV_WG_GXKSSF
#define _BRSFC_CV_WG_GXKSX1
#define _BRSFC_CV_WG_GXKSX2
#define _BRSFC_CV_WG_GXKSY1
#define _BRSFC_CV_WG_GXKSY2
#define _BRSFC_CV_WG_GXKSZ1
#define _BRSFC_CV_WG_GXKSZ2
#define _BRSFC_CV_WG_GXRF2CFH
#define _BRSFC_CV_WG_GXSPOIL
#define _BRSFC_CV_WG_GXSPOIL2
#define _BRSFC_CV_WG_GXW
#define _BRSFC_CV_WG_GXW1FTG
#define _BRSFC_CV_WG_GXW1XTG
#define _BRSFC_CV_WG_GXW2
#define _BRSFC_CV_WG_GXW2DTG
#define _BRSFC_CV_WG_GXW2FTG
#define _BRSFC_CV_WG_GXW2RS
#define _BRSFC_CV_WG_GXWAS
#define _BRSFC_CV_WG_GXWDTG
#define _BRSFC_CV_WG_GXWEX
#define _BRSFC_CV_WG_GXWMON
#define _BRSFC_CV_WG_GXWMPS1
#define _BRSFC_CV_WG_GXWRS
#define _BRSFC_CV_WG_GY1
#define _BRSFC_CV_WG_GY1AS
#define _BRSFC_CV_WG_GY1CFH
#define _BRSFC_CV_WG_GY1DTG
#define _BRSFC_CV_WG_GY1MON
#define _BRSFC_CV_WG_GY1MPS1
#define _BRSFC_CV_WG_GY1R
#define _BRSFC_CV_WG_GY1RAS
#define _BRSFC_CV_WG_GY1RDTG
#define _BRSFC_CV_WG_GY1RRS
#define _BRSFC_CV_WG_GY1RS
#define _BRSFC_CV_WG_GY1TM
#define _BRSFC_CV_WG_GY2DTG
#define _BRSFC_CV_WG_GY2RS
#define _BRSFC_CV_WG_GYB
#define _BRSFC_CV_WG_GYBRSFC1
#define _BRSFC_CV_WG_GYBRSFC2
#define _BRSFC_CV_WG_GYCYLR
#define _BRSFC_CV_WG_GYCYLRA
#define _BRSFC_CV_WG_GYCYLRATIPUP
#define _BRSFC_CV_WG_GYCYLRTIPUP
#define _BRSFC_CV_WG_GYFE1
#define _BRSFC_CV_WG_GYFE2
#define _BRSFC_CV_WG_GYFLPK
#define _BRSFC_CV_WG_GYFLPVENC
#define _BRSFC_CV_WG_GYHYST1
#define _BRSFC_CV_WG_GYHYST2
#define _BRSFC_CV_WG_GYKCFH
#define _BRSFC_CV_WG_GYKCFL
#define _BRSFC_CV_WG_GYKCS
#define _BRSFC_CV_WG_GYKFS
#define _BRSFC_CV_WG_GYKILL
#define _BRSFC_CV_WG_GYKRCVN
#define _BRSFC_CV_WG_GYKSE1
#define _BRSFC_CV_WG_GYKSE2
#define _BRSFC_CV_WG_GYKSE3
#define _BRSFC_CV_WG_GYKSE4
#define _BRSFC_CV_WG_GYKSE5
#define _BRSFC_CV_WG_GYKSE6
#define _BRSFC_CV_WG_GYKSP
#define _BRSFC_CV_WG_GYKSSF
#define _BRSFC_CV_WG_GYKSX1
#define _BRSFC_CV_WG_GYKSX2
#define _BRSFC_CV_WG_GYKSY1
#define _BRSFC_CV_WG_GYKSY2
#define _BRSFC_CV_WG_GYKSZ1
#define _BRSFC_CV_WG_GYKSZ2
#define _BRSFC_CV_WG_GYKXTGL
#define _BRSFC_CV_WG_GYKXTGR
#define _BRSFC_CV_WG_GYRF0KCFH
#define _BRSFC_CV_WG_GYRF1MON
#define _BRSFC_CV_WG_GYRF1MPS1
#define _BRSFC_CV_WG_GYRF1TM
#define _BRSFC_CV_WG_GYRF1XTG
#define _BRSFC_CV_WG_GYRF2CFH
#define _BRSFC_CV_WG_GYRF2LMON
#define _BRSFC_CV_WG_GYRF2RMON
#define _BRSFC_CV_WG_GYRF3CFH
#define _BRSFC_CV_WG_GYSPOIL
#define _BRSFC_CV_WG_GYSPOIL2
#define _BRSFC_CV_WG_GZ1
#define _BRSFC_CV_WG_GZ1AS
#define _BRSFC_CV_WG_GZ1CFL
#define _BRSFC_CV_WG_GZ1DTG
#define _BRSFC_CV_WG_GZ1FTG
#define _BRSFC_CV_WG_GZ1MON
#define _BRSFC_CV_WG_GZ1MPS1
#define _BRSFC_CV_WG_GZ1RS
#define _BRSFC_CV_WG_GZ1S
#define _BRSFC_CV_WG_GZ1XTG
#define _BRSFC_CV_WG_GZ2BFTG
#define _BRSFC_CV_WG_GZ2FTG
#define _BRSFC_CV_WG_GZ2XTG
#define _BRSFC_CV_WG_GZ3FTG
#define _BRSFC_CV_WG_GZBRSFC1
#define _BRSFC_CV_WG_GZBRSFC1ECHO1
#define _BRSFC_CV_WG_GZBRSFC1ECHO2
#define _BRSFC_CV_WG_GZBRSFC2
#define _BRSFC_CV_WG_GZCOMB
#define _BRSFC_CV_WG_GZCOMBHTR
#define _BRSFC_CV_WG_GZCYLR
#define _BRSFC_CV_WG_GZCYLRA
#define _BRSFC_CV_WG_GZCYLRATIPUP
#define _BRSFC_CV_WG_GZCYLRTIPUP
#define _BRSFC_CV_WG_GZFLPK
#define _BRSFC_CV_WG_GZFLPVENC
#define _BRSFC_CV_WG_GZK
#define _BRSFC_CV_WG_GZKAS
#define _BRSFC_CV_WG_GZKBSDTG
#define _BRSFC_CV_WG_GZKBSRS
#define _BRSFC_CV_WG_GZKCS
#define _BRSFC_CV_WG_GZKDTG
#define _BRSFC_CV_WG_GZKFS
#define _BRSFC_CV_WG_GZKGIR01
#define _BRSFC_CV_WG_GZKGIR02
#define _BRSFC_CV_WG_GZKILL
#define _BRSFC_CV_WG_GZKILLER
#define _BRSFC_CV_WG_GZKMON
#define _BRSFC_CV_WG_GZKMONTIPUP
#define _BRSFC_CV_WG_GZKRCVN
#define _BRSFC_CV_WG_GZKRFFRIR
#define _BRSFC_CV_WG_GZKRS
#define _BRSFC_CV_WG_GZKS
#define _BRSFC_CV_WG_GZKS5FP
#define _BRSFC_CV_WG_GZKSP
#define _BRSFC_CV_WG_GZKSSF
#define _BRSFC_CV_WG_GZP
#define _BRSFC_CV_WG_GZPHTR
#define _BRSFC_CV_WG_GZPTM
#define _BRSFC_CV_WG_GZRF0K
#define _BRSFC_CV_WG_GZRF1
#define _BRSFC_CV_WG_GZRF1DTG
#define _BRSFC_CV_WG_GZRF1HTR
#define _BRSFC_CV_WG_GZRF1MPS1
#define _BRSFC_CV_WG_GZRF1RS
#define _BRSFC_CV_WG_GZRF1S
#define _BRSFC_CV_WG_GZRF1XTG
#define _BRSFC_CV_WG_GZRF2LCFH
#define _BRSFC_CV_WG_GZRF2LMPS1
#define _BRSFC_CV_WG_GZRF2RCFH
#define _BRSFC_CV_WG_GZRF2RMPS1
#define _BRSFC_CV_WG_GZRF3LCFH
#define _BRSFC_CV_WG_GZRF3RCFH
#define _BRSFC_CV_WG_GZRF4CFH
#define _BRSFC_CV_WG_GZRF4LCFH
#define _BRSFC_CV_WG_GZRF4RCFH
#define _BRSFC_CV_WG_GZRFS5FPH
#define _BRSFC_CV_WG_GZRFSSFH
#define _BRSFC_CV_WG_GZS5FPHCOMB
#define _BRSFC_CV_WG_GZSSFHCOMB
#define _BRSFC_CV_WG_HARD180
#define _BRSFC_CV_WG_ISI7
#define _BRSFC_CV_WG_ISI_CARDIACSAT
#define _BRSFC_CV_WG_ISI_GIR1
#define _BRSFC_CV_WG_ISI_GIRE01
#define _BRSFC_CV_WG_ISI_GIRE02
#define _BRSFC_CV_WG_ISI_GIRK01
#define _BRSFC_CV_WG_ISI_GIRK02
#define _BRSFC_CV_WG_ISI_SATE1
#define _BRSFC_CV_WG_ISI_SATE2
#define _BRSFC_CV_WG_ISI_SATE3
#define _BRSFC_CV_WG_ISI_SATE4
#define _BRSFC_CV_WG_ISI_SATE5
#define _BRSFC_CV_WG_ISI_SATE6
#define _BRSFC_CV_WG_ISI_SATEK1
#define _BRSFC_CV_WG_ISI_SATEK2
#define _BRSFC_CV_WG_ISI_SATEK3
#define _BRSFC_CV_WG_ISI_SATEK4
#define _BRSFC_CV_WG_ISI_SATEK5
#define _BRSFC_CV_WG_ISI_SATEK6
#define _BRSFC_CV_WG_ISI_SATX1
#define _BRSFC_CV_WG_ISI_SATX2
#define _BRSFC_CV_WG_ISI_SATXK1
#define _BRSFC_CV_WG_ISI_SATXK2
#define _BRSFC_CV_WG_ISI_SATY1
#define _BRSFC_CV_WG_ISI_SATY2
#define _BRSFC_CV_WG_ISI_SATYK1
#define _BRSFC_CV_WG_ISI_SATYK2
#define _BRSFC_CV_WG_ISI_SATZ1
#define _BRSFC_CV_WG_ISI_SATZ2
#define _BRSFC_CV_WG_ISI_SATZK1
#define _BRSFC_CV_WG_ISI_SATZK2
#define _BRSFC_CV_WG_ISI_SLICE1
#define _BRSFC_CV_WG_ISI_SLICE2
#define _BRSFC_CV_WG_MAPS1
#define _BRSFC_CV_WG_MAPS2
#define _BRSFC_CV_WG_MAPX
#define _BRSFC_CV_WG_MAPY
#define _BRSFC_CV_WG_MAPZ
#define _BRSFC_CV_WG_MPOMEGA_TD0
#define _BRSFC_CV_WG_MPRHO_TD0
#define _BRSFC_CV_WG_MPSSP_TD0
#define _BRSFC_CV_WG_MPTHETA_TD0
#define _BRSFC_CV_WG_MPX_TD0
#define _BRSFC_CV_WG_MPY_TD0
#define _BRSFC_CV_WG_MPZ_TD0
#define _BRSFC_CV_WG_OMEGA_HS_RFCSSAT
#define _BRSFC_CV_WG_OMEGA_IR0
#define _BRSFC_CV_WG_OMEGA_RFFRIR
#define _BRSFC_CV_WG_OMEGA_RFGIR01
#define _BRSFC_CV_WG_OMEGA_RFGIR02
#define _BRSFC_CV_WG_OMEGARF0CFH
#define _BRSFC_CV_WG_POSTGXW1FTG
#define _BRSFC_CV_WG_RCVN_WAIT
#define _BRSFC_CV_WG_RF0
#define _BRSFC_CV_WG_RF0CFH
#define _BRSFC_CV_WG_RF1
#define _BRSFC_CV_WG_RF180
#define _BRSFC_CV_WG_RF1AS
#define _BRSFC_CV_WG_RF1CFH
#define _BRSFC_CV_WG_RF1CFL
#define _BRSFC_CV_WG_RF1DTG
#define _BRSFC_CV_WG_RF1FTG
#define _BRSFC_CV_WG_RF1HTR
#define _BRSFC_CV_WG_RF1MON
#define _BRSFC_CV_WG_RF1MPS1
#define _BRSFC_CV_WG_RF1RS
#define _BRSFC_CV_WG_RF1TM
#define _BRSFC_CV_WG_RF1XTG
#define _BRSFC_CV_WG_RF2CFH
#define _BRSFC_CV_WG_RF2FTG
#define _BRSFC_CV_WG_RF2MON
#define _BRSFC_CV_WG_RF2MPS1
#define _BRSFC_CV_WG_RF2XTG
#define _BRSFC_CV_WG_RF3CFH
#define _BRSFC_CV_WG_RF3FTG
#define _BRSFC_CV_WG_RF3XTG
#define _BRSFC_CV_WG_RF4CFH
#define _BRSFC_CV_WG_RF4XTG
#define _BRSFC_CV_WG_RF90
#define _BRSFC_CV_WG_RFBDTG
#define _BRSFC_CV_WG_RFBRS
#define _BRSFC_CV_WG_RFCSSAT
#define _BRSFC_CV_WG_RFCYLR
#define _BRSFC_CV_WG_RFCYLRTIPUP
#define _BRSFC_CV_WG_RFFLP180
#define _BRSFC_CV_WG_RFFLP180_THE
#define _BRSFC_CV_WG_RFFLP90
#define _BRSFC_CV_WG_RFFLP90_THE
#define _BRSFC_CV_WG_RFFLP90R
#define _BRSFC_CV_WG_RFFLP90R_THE
#define _BRSFC_CV_WG_RFFRIR
#define _BRSFC_CV_WG_RFFS
#define _BRSFC_CV_WG_RFGIR01
#define _BRSFC_CV_WG_RFGIR02
#define _BRSFC_CV_WG_RFMONTIPUP
#define _BRSFC_CV_WG_RFS5FPH
#define _BRSFC_CV_WG_RFSE1
#define _BRSFC_CV_WG_RFSE2
#define _BRSFC_CV_WG_RFSE3
#define _BRSFC_CV_WG_RFSE4
#define _BRSFC_CV_WG_RFSE5
#define _BRSFC_CV_WG_RFSE6
#define _BRSFC_CV_WG_RFSSF
#define _BRSFC_CV_WG_RFSSFH
#define _BRSFC_CV_WG_RFSX1
#define _BRSFC_CV_WG_RFSX2
#define _BRSFC_CV_WG_RFSY1
#define _BRSFC_CV_WG_RFSY2
#define _BRSFC_CV_WG_RFSZ1
#define _BRSFC_CV_WG_RFSZ2
#define _BRSFC_CV_WG_RFTIPUP
#define _BRSFC_CV_WG_ROT_SLICE1
#define _BRSFC_CV_WG_ROT_SLICE2
#define _BRSFC_CV_WG_ROT_UPDATE_CARDIACSAT
#define _BRSFC_CV_WG_ROT_UPDATE_E1
#define _BRSFC_CV_WG_ROT_UPDATE_E2
#define _BRSFC_CV_WG_ROT_UPDATE_E3
#define _BRSFC_CV_WG_ROT_UPDATE_E4
#define _BRSFC_CV_WG_ROT_UPDATE_E5
#define _BRSFC_CV_WG_ROT_UPDATE_E6
#define _BRSFC_CV_WG_ROT_UPDATE_EK1
#define _BRSFC_CV_WG_ROT_UPDATE_EK2
#define _BRSFC_CV_WG_ROT_UPDATE_EK3
#define _BRSFC_CV_WG_ROT_UPDATE_EK4
#define _BRSFC_CV_WG_ROT_UPDATE_EK5
#define _BRSFC_CV_WG_ROT_UPDATE_EK6
#define _BRSFC_CV_WG_ROT_UPDATE_GIR
#define _BRSFC_CV_WG_ROT_UPDATE_GIRE01
#define _BRSFC_CV_WG_ROT_UPDATE_GIRK01
#define _BRSFC_CV_WG_ROT_UPDATE_GIRK02
#define _BRSFC_CV_WG_ROT_UPDATE_RFGIR02
#define _BRSFC_CV_WG_ROT_UPDATE_X1
#define _BRSFC_CV_WG_ROT_UPDATE_X2
#define _BRSFC_CV_WG_ROT_UPDATE_XK1
#define _BRSFC_CV_WG_ROT_UPDATE_XK2
#define _BRSFC_CV_WG_ROT_UPDATE_Y1
#define _BRSFC_CV_WG_ROT_UPDATE_Y2
#define _BRSFC_CV_WG_ROT_UPDATE_YK1
#define _BRSFC_CV_WG_ROT_UPDATE_YK2
#define _BRSFC_CV_WG_ROT_UPDATE_Z1
#define _BRSFC_CV_WG_ROT_UPDATE_Z2
#define _BRSFC_CV_WG_ROT_UPDATE_ZK1
#define _BRSFC_CV_WG_ROT_UPDATE_ZK2
#define _BRSFC_CV_WG_RTICFH
#define _BRSFC_CV_WG_SDIXON
#define _BRSFC_CV_WG_SDIXON2
#define _BRSFC_CV_WG_STICFH
#define _BRSFC_CV_WG_THCYLR
#define _BRSFC_CV_WG_THCYLRTIPUP
#define _BRSFC_CV_WG_THETARFBDTG
#define _BRSFC_CV_WG_THETARFBRS
#define _BRSFC_CV_WG_XDELAY
#define _BRSFC_CV_WG_XDIXON
#define _BRSFC_CV_WG_XRESPGATE
#define _BRSFC_CV_WG_XTICFH
#define _BRSFC_CV_WG_Y_CCS_NULL
#define _BRSFC_CV_WG_YDIXON
#define _BRSFC_CV_WG_YTICFH
#define _BRSFC_CV_WG_ZDIXON
#define _BRSFC_CV_WG_ZTICFH
#define _BRSFC_CV_WHICHSS
#define _BRSFC_CV_WRITE_SPINFO
#define _BRSFC_CV_XA2S
#define _BRSFC_CV_XFD_POWER_LIMIT
#define _BRSFC_CV_XFD_TEMP_LIMIT
#define _BRSFC_CV_XGD_OPTIMIZATION
#define _BRSFC_CV_XKILLER_SET
#define _BRSFC_CV_XLFOV_FLAG
#define _BRSFC_CV_XMTADD
#define _BRSFC_CV_XMTADDAPS1
#define _BRSFC_CV_XMTADDCFH
#define _BRSFC_CV_XMTADDCFL
#define _BRSFC_CV_XMTADDFTG
#define _BRSFC_CV_XMTADDRCVN
#define _BRSFC_CV_XMTADDREF
#define _BRSFC_CV_XMTADDSCAN
#define _BRSFC_CV_XMTADDXTG
#define _BRSFC_CV_XMTADDAS
#define _BRSFC_CV_XMTADDDTG
#define _BRSFC_CV_XMTADDRS
#define _BRSFC_CV_XMTLOGAS
#define _BRSFC_CV_XRES
#define _BRSFC_CV_XRES2USE
#define _BRSFC_CV_XRES_ANN_OFF
#define _BRSFC_CV_XRES_ANN_ON
#define _BRSFC_CV_XTG_DDA
#define _BRSFC_CV_XTG_DISABLED
#define _BRSFC_CV_XTG_OFFRES_FREQ
#define _BRSFC_CV_XTG_VOLRECCOIL
#define _BRSFC_CV_XTGSCALE
#define _BRSFC_CV_XTGTR
#define _BRSFC_CV_XTR_OFFSET
#define _BRSFC_CV_YA2S
#define _BRSFC_CV_YFE_TIME
#define _BRSFC_CV_YFOV_ASPECT
#define _BRSFC_CV_YOFFS1
#define _BRSFC_CV_YRES_PHASE
#define _BRSFC_CV_ZA2S
#define _BRSFC_CV_ZCHOP
#define _BRSFC_CV_ZGMN_TYPE
#define _BRSFC_CV_ZKILLER_FLAG
#define _BRSFC_CV_ZOFFS
#define _BRSFC_CV_ZOFFS1
#define _BRSFC_CV_ZREWIND_FLAG
#define _BRSFC_CV_ZSIGN
#define _BRSFC_CV_ZSLAB
#define _BRSFC_CV_ZY_EXPORT_DEBUG_FILES
#define _BRSFC_CV_ZY_SLICES
#define _BRSFC_CV_ZY_VIEWS
typedef struct {
  char psd_name[255]; 
  char host_name[32]; 
  char time_stamp[32]; 
  char sha1sum[48]; 
  int ASSET_MAX_SLQUANT ;
  int B1Cal_mode ;
  int CFHxres ;
  int CFLxres ;
  int ChemSatPulse ;
  int CompleteEchoLoop_flag ;
  int CompositeRMS_method ;
  int DATA_ACQ_ORDER_ENTRIES ;
  int DD_channels ;
  int DD_debug ;
  int DD_delay ;
  int DD_nCh ;
  int FSvar ;
  int FTGacq1 ;
  int FTGacq2 ;
  float FTGau ;
  float FTGecho1bw ;
  float FTGfov ;
  float FTGopslthickz1 ;
  float FTGopslthickz2 ;
  float FTGopslthickz3 ;
  float FTGslthk ;
  int FTGtau1 ;
  int FTGtau2 ;
  float FTGtecho ;
  int FTGtestpulse ;
  float FTGxmtadd ;
  int FTGxres ;
  float GAM ;
  int IRinCFH ;
  float PSamp_derate_factor ;
  float PSasamp_derate_factor ;
  float PSassr_derate_factor ;
  int PScfh_shimvol_debug ;
  int PScs_sat ;
  int PSdebugstate ;
  int PSfield_strength ;
  int PSir ;
  int PSmt ;
  int PSoff90 ;
  float PSphasoff ;
  float PSphasoff_mod ;
  float PSrloc ;
  float PSrloc_mod ;
  int PSslice_ind ;
  int PSslice_num ;
  float PSsr_derate_factor ;
  int PStest_slab ;
  float PStloc ;
  float PStloc_mod ;
  int PStrigger ;
  int PosGzssfhcomb ;
  int Posrfs5fph ;
  int Posrfssf ;
  int Posrfssfh ;
  float Rf ;
  float SAR_bodyNV_weight_lim ;
  int SatRelaxers ;
  float T1f ;
  float T2f ;
  int TG_record ;
  int TGlimit ;
  float TGopslthick ;
  float TGopslthickx ;
  float TGopslthicky ;
  int TGspf ;
  int TR_PASS ;
  int TR_PASS3D ;
  int TR_SLOP ;
  int XTGacq1 ;
  float XTGecho1bw ;
  float XTGfov ;
  int XTGtau1 ;
  int XTGxres ;
  long int _firstcv ;
  long int _lastcv ;
  long int _lasttgtex ;
  int aTEopt_flag ;
  int aTRopt_flag ;
  float a_base ;
  float a_base2 ;
  float a_base_max ;
  float a_base_proj_dephaser ;
  float a_comb ;
  float a_comb2 ;
  float a_delta ;
  float a_delta2 ;
  float a_end ;
  float a_end2 ;
  float a_gk ;
  float a_gx1 ;
  float a_gx1_frac ;
  float a_gx1_full ;
  float a_gx1a ;
  float a_gx1as ;
  float a_gx1b ;
  float a_gx1bftg ;
  float a_gx1bxtg ;
  float a_gx1cfh ;
  float a_gx1d ;
  float a_gx1d_frac ;
  float a_gx1d_full ;
  float a_gx1dtg ;
  float a_gx1ftg ;
  float a_gx1mon ;
  float a_gx1mps1 ;
  float a_gx1rs ;
  float a_gx1tm ;
  float a_gx1u ;
  float a_gx1u_frac ;
  float a_gx1u_full ;
  float a_gx2 ;
  float a_gx2dtg ;
  float a_gx2ftg ;
  float a_gx2rs ;
  float a_gx2test ;
  float a_gxb ;
  float a_gxbrsfc1 ;
  float a_gxbrsfc2 ;
  float a_gxfc ;
  float a_gxfc_frac ;
  float a_gxfc_full ;
  float a_gxfcd ;
  float a_gxfcd_frac ;
  float a_gxfcd_full ;
  float a_gxfcmon ;
  float a_gxfcu ;
  float a_gxfcu_frac ;
  float a_gxfcu_full ;
  float a_gxflpk ;
  float a_gxflpka ;
  float a_gxflpkb ;
  float a_gxflpvenc ;
  float a_gxflpvenca ;
  float a_gxflpvencb ;
  float a_gxhyst1 ;
  float a_gxhyst2 ;
  float a_gxkas ;
  float a_gxkbsdtg ;
  float a_gxkbsrs ;
  float a_gxkcs ;
  float a_gxkdtg ;
  float a_gxkfs ;
  float a_gxkill ;
  float a_gxkrcvn ;
  float a_gxkrs ;
  float a_gxks ;
  float a_gxkse1 ;
  float a_gxkse2 ;
  float a_gxkse3 ;
  float a_gxkse4 ;
  float a_gxkse5 ;
  float a_gxkse6 ;
  float a_gxksp ;
  float a_gxkssf ;
  float a_gxksx1 ;
  float a_gxksx2 ;
  float a_gxksy1 ;
  float a_gxksy2 ;
  float a_gxksz1 ;
  float a_gxksz2 ;
  float a_gxrf1tm ;
  float a_gxrf2cfh ;
  float a_gxrfsx1 ;
  float a_gxrfsx2 ;
  float a_gxspiral ;
  float a_gxspiral2 ;
  float a_gxspoil ;
  float a_gxspoil2 ;
  float a_gxw ;
  float a_gxw1ftg ;
  float a_gxw1xtg ;
  float a_gxw2 ;
  float a_gxw2dtg ;
  float a_gxw2ftg ;
  float a_gxw2rs ;
  float a_gxwas ;
  float a_gxwdtg ;
  float a_gxwex ;
  float a_gxwmon ;
  float a_gxwmps1 ;
  float a_gxwrs ;
  float a_gy1 ;
  float a_gy1a ;
  float a_gy1as ;
  float a_gy1asa ;
  float a_gy1asb ;
  float a_gy1b ;
  float a_gy1cfh ;
  float a_gy1dtg ;
  float a_gy1dtga ;
  float a_gy1dtgb ;
  float a_gy1mon ;
  float a_gy1mps1 ;
  float a_gy1r ;
  float a_gy1ra ;
  float a_gy1ras ;
  float a_gy1rasa ;
  float a_gy1rasb ;
  float a_gy1rb ;
  float a_gy1rdtg ;
  float a_gy1rdtga ;
  float a_gy1rdtgb ;
  float a_gy1rrs ;
  float a_gy1rrsa ;
  float a_gy1rrsb ;
  float a_gy1rs ;
  float a_gy1rsa ;
  float a_gy1rsb ;
  float a_gy1tm ;
  float a_gy2dtg ;
  float a_gy2dtga ;
  float a_gy2dtgb ;
  float a_gy2rs ;
  float a_gy2rsa ;
  float a_gy2rsb ;
  float a_gyb ;
  float a_gybrsfc1 ;
  float a_gybrsfc2 ;
  float a_gycylr ;
  float a_gycylrtipup ;
  float a_gyfe ;
  float a_gyfe1 ;
  float a_gyfe2 ;
  float a_gyflpk ;
  float a_gyflpka ;
  float a_gyflpkb ;
  float a_gyflpvenc ;
  float a_gyflpvenca ;
  float a_gyflpvencb ;
  float a_gyhyst1 ;
  float a_gyhyst2 ;
  float a_gykcfh ;
  float a_gykcfl ;
  float a_gykcs ;
  float a_gykfs ;
  float a_gykill ;
  float a_gykrcvn ;
  float a_gyks ;
  float a_gykse1 ;
  float a_gykse2 ;
  float a_gykse3 ;
  float a_gykse4 ;
  float a_gykse5 ;
  float a_gykse6 ;
  float a_gyksp ;
  float a_gykssf ;
  float a_gyksx1 ;
  float a_gyksx2 ;
  float a_gyksy1 ;
  float a_gyksy2 ;
  float a_gyksz1 ;
  float a_gyksz2 ;
  float a_gykxtgl ;
  float a_gykxtgr ;
  float a_gyrf0kcfh ;
  float a_gyrf1mon ;
  float a_gyrf1mps1 ;
  float a_gyrf1tm ;
  float a_gyrf1xtg ;
  float a_gyrf2cfh ;
  float a_gyrf2lmon ;
  float a_gyrf2mon ;
  float a_gyrf2rmon ;
  float a_gyrf3cfh ;
  float a_gyrfmontipup ;
  float a_gyrfsy1 ;
  float a_gyrfsy2 ;
  float a_gyspiral ;
  float a_gyspiral2 ;
  float a_gyspoil ;
  float a_gyspoil2 ;
  float a_gz1 ;
  float a_gz1as ;
  float a_gz1cfl ;
  float a_gz1d ;
  float a_gz1dtg ;
  float a_gz1ftg ;
  float a_gz1mon ;
  float a_gz1mps1 ;
  float a_gz1rs ;
  float a_gz1s ;
  float a_gz1u ;
  float a_gz1xtg ;
  float a_gz2bftg ;
  float a_gz2ftg ;
  float a_gz2xtg ;
  float a_gz3ftg ;
  float a_gzbrsfc1 ;
  float a_gzbrsfc1echo1 ;
  float a_gzbrsfc1echo2 ;
  float a_gzbrsfc2 ;
  float a_gzcomb ;
  float a_gzcomba ;
  float a_gzcombb ;
  float a_gzcombhtr ;
  float a_gzcombhtra ;
  float a_gzcombhtrb ;
  float a_gzcylr ;
  float a_gzcylrtipup ;
  float a_gzfc ;
  float a_gzfcbase ;
  float a_gzfccomb ;
  float a_gzfcd ;
  float a_gzfcend ;
  float a_gzfcu ;
  float a_gzflpk ;
  float a_gzflpka ;
  float a_gzflpkb ;
  float a_gzflpvenc ;
  float a_gzflpvenca ;
  float a_gzflpvencb ;
  float a_gzk ;
  float a_gzkas ;
  float a_gzkbase ;
  float a_gzkbsdtg ;
  float a_gzkbsrs ;
  float a_gzkcomb ;
  float a_gzkcs ;
  float a_gzkdtg ;
  float a_gzkend ;
  float a_gzkfs ;
  float a_gzkgir01 ;
  float a_gzkgir02 ;
  float a_gzkill ;
  float a_gzkiller ;
  float a_gzkmon ;
  float a_gzkmontipup ;
  float a_gzkrcvn ;
  float a_gzkrffrir ;
  float a_gzkrs ;
  float a_gzks ;
  float a_gzks5fp ;
  float a_gzksp ;
  float a_gzkssf ;
  float a_gzp ;
  float a_gzpa ;
  float a_gzpb ;
  float a_gzphtr ;
  float a_gzphtra ;
  float a_gzphtrb ;
  float a_gzptm ;
  float a_gzrf0 ;
  float a_gzrf0cfh ;
  float a_gzrf0k ;
  float a_gzrf1 ;
  float a_gzrf1_ss_max ;
  float a_gzrf1as ;
  float a_gzrf1cfh ;
  float a_gzrf1cfl ;
  float a_gzrf1dtg ;
  float a_gzrf1ftg ;
  float a_gzrf1htr ;
  float a_gzrf1mon ;
  float a_gzrf1mps1 ;
  float a_gzrf1rs ;
  float a_gzrf1s ;
  float a_gzrf1temp ;
  float a_gzrf1xtg ;
  float a_gzrf2ftg ;
  float a_gzrf2lcfh ;
  float a_gzrf2lmps1 ;
  float a_gzrf2mps1 ;
  float a_gzrf2rcfh ;
  float a_gzrf2rmps1 ;
  float a_gzrf2xtg ;
  float a_gzrf3ftg ;
  float a_gzrf3lcfh ;
  float a_gzrf3rcfh ;
  float a_gzrf4cfh ;
  float a_gzrf4lcfh ;
  float a_gzrf4rcfh ;
  float a_gzrffrir ;
  float a_gzrfgir01 ;
  float a_gzrfgir02 ;
  float a_gzrfs5fph ;
  float a_gzrfse1 ;
  float a_gzrfse2 ;
  float a_gzrfse3 ;
  float a_gzrfse4 ;
  float a_gzrfse5 ;
  float a_gzrfse6 ;
  float a_gzrfssfh ;
  float a_gzrfsz1 ;
  float a_gzrfsz2 ;
  float a_gzs5fphcomb ;
  float a_gzssfhcomb ;
  float a_gzvlw ;
  float a_hard180 ;
  float a_hst ;
  float a_nomcyl ;
  float a_omega_hs_rfcssat ;
  float a_omega_ir0 ;
  float a_omega_rffrir ;
  float a_omega_rfgir01 ;
  float a_omega_rfgir02 ;
  float a_omegarf0cfh ;
  float a_ph180 ;
  float a_postgxw1ftg ;
  float a_rf0 ;
  float a_rf0cfh ;
  float a_rf1 ;
  float a_rf180 ;
  float a_rf1as ;
  float a_rf1cfh ;
  float a_rf1cfl ;
  float a_rf1dtg ;
  float a_rf1ftg ;
  float a_rf1htr ;
  float a_rf1mon ;
  float a_rf1mps1 ;
  float a_rf1rs ;
  float a_rf1tm ;
  float a_rf1xtg ;
  float a_rf2cfh ;
  float a_rf2ftg ;
  float a_rf2mon ;
  float a_rf2mps1 ;
  float a_rf2xtg ;
  float a_rf3cfh ;
  float a_rf3ftg ;
  float a_rf3xtg ;
  float a_rf4cfh ;
  float a_rf4xtg ;
  float a_rf90 ;
  float a_rfbdtg ;
  float a_rfbrs ;
  float a_rfcssat ;
  float a_rfcssatcfh ;
  float a_rfcylr ;
  float a_rfcylrtipup ;
  float a_rfflp180 ;
  float a_rfflp180_the ;
  float a_rfflp90 ;
  float a_rfflp90_the ;
  float a_rfflp90r ;
  float a_rfflp90r_the ;
  float a_rffrir ;
  float a_rffs ;
  float a_rfgir01 ;
  float a_rfgir02 ;
  float a_rfmontipup ;
  float a_rfs5fph ;
  float a_rfse1 ;
  float a_rfse2 ;
  float a_rfse3 ;
  float a_rfse4 ;
  float a_rfse5 ;
  float a_rfse6 ;
  float a_rfssf ;
  float a_rfssfh ;
  float a_rfsx1 ;
  float a_rfsx2 ;
  float a_rfsy1 ;
  float a_rfsy2 ;
  float a_rfsz1 ;
  float a_rfsz2 ;
  float a_rftipup ;
  float a_sdixon ;
  float a_sdixon2 ;
  float a_thcylr ;
  float a_thcylrtipup ;
  float a_thetarf1 ;
  float a_xdixon ;
  float a_ydixon ;
  float a_zdixon ;
  int ab1_enable ;
  float abspower_lx ;
  float abspower_ly ;
  float abspower_lz ;
  float abspower_px ;
  float abspower_py ;
  float abspower_pz ;
  int accel_kt_cal_stride ;
  int accel_outer2cal_factor ;
  float accel_ph_defstride ;
  float accel_ph_stride ;
  int accel_phaseres ;
  float accel_sl_defstride ;
  float accel_sl_stride ;
  float acgd_lite_target ;
  int acq_data_only ;
  int acq_type ;
  int acqs ;
  int acquire_type ;
  float act_aregion_fraction ;
  float act_echofrac ;
  int act_htr ;
  int act_navgate_tr ;
  float act_scamp ;
  float act_srate ;
  float act_srate_x ;
  float act_srate_y ;
  float act_srate_z ;
  int act_te ;
  int act_te2 ;
  int act_te_cylr ;
  int act_tr ;
  int add_slicereadgap ;
  int add_tetime ;
  int adj_act_tr ;
  int allow_ugfsf ;
  float alpha_rf0 ;
  float alpha_rf0cfh ;
  float alpha_rf1 ;
  float alpha_rf1as ;
  float alpha_rf1cfh ;
  float alpha_rf1cfl ;
  float alpha_rf1ftg ;
  float alpha_rf1mon ;
  float alpha_rf1mps1 ;
  float alpha_rf1tm ;
  float alpha_rf1xtg ;
  float alpha_rf2cfh ;
  float alpha_rf2ftg ;
  float alpha_rf2mon ;
  float alpha_rf2mps1 ;
  float alpha_rf2xtg ;
  float alpha_rf3cfh ;
  float alpha_rf3ftg ;
  float alpha_rf3xtg ;
  float alpha_rf4cfh ;
  float alpha_rf4xtg ;
  float alpha_rfcssat ;
  float alpha_rffrir ;
  float alpha_rfgir01 ;
  float alpha_rfgir02 ;
  float alpha_rfmontipup ;
  float alpha_rfse1 ;
  float alpha_rfse2 ;
  float alpha_rfse3 ;
  float alpha_rfse4 ;
  float alpha_rfse5 ;
  float alpha_rfse6 ;
  float alpha_rfsx1 ;
  float alpha_rfsx2 ;
  float alpha_rfsy1 ;
  float alpha_rfsy2 ;
  float alpha_rfsz1 ;
  float alpha_rfsz2 ;
  float amp_flpvenc_limit ;
  float amp_flpvenc_max ;
  float amptrans_lx ;
  float amptrans_ly ;
  float amptrans_lz ;
  float amptrans_px ;
  float amptrans_py ;
  float amptrans_pz ;
  float anne_channel_percentage ;
  float anne_intensity_thres ;
  int anne_mask_dilation_length ;
  int annefact_c3_recon_flag ;
  int annefact_reduction_flag ;
  int ap_flow ;
  int aphases_max ;
  int apodize_level_flag ;
  int app_grad_type ;
  int apx_compatible ;
  int apx_cveval_counter ;
  int arc_cal_echo ;
  int arc_debug_files ;
  int arc_equant ;
  int arc_flag ;
  float arc_maxnetaccel ;
  float arc_netaccel ;
  int arc_pack_bam ;
  int arc_ph_calwidth ;
  int arc_ph_intaccel ;
  float arc_ph_maxnetaccel ;
  float arc_ph_maxstride ;
  int arc_ph_mincalwidth ;
  float arc_ph_netaccel ;
  float arc_ph_reclimstride ;
  float arc_ph_recstride ;
  float arc_ph_stride ;
  float arc_ph_userstride ;
  float arc_reclimnetaccel ;
  float arc_recnetaccel ;
  int arc_research_flag ;
  int arc_sl_calwidth ;
  int arc_sl_intaccel ;
  float arc_sl_maxnetaccel ;
  float arc_sl_maxstride ;
  int arc_sl_mincalwidth ;
  float arc_sl_netaccel ;
  float arc_sl_reclimstride ;
  float arc_sl_recstride ;
  float arc_sl_stride ;
  float arc_sl_userstride ;
  int arc_syn_pts ;
  float area_de ;
  float area_flpk ;
  float area_flpvenc_std ;
  float area_gx1 ;
  float area_gx2 ;
  float area_gxfc ;
  float area_gxkcs ;
  float area_gxkfs ;
  float area_gxkrcvn ;
  float area_gxks ;
  float area_gxkse1 ;
  float area_gxkse2 ;
  float area_gxkse3 ;
  float area_gxkse4 ;
  float area_gxkse5 ;
  float area_gxkse6 ;
  float area_gxkssf ;
  float area_gxksx1 ;
  float area_gxksx2 ;
  float area_gxksy1 ;
  float area_gxksy2 ;
  float area_gxksz1 ;
  float area_gxksz2 ;
  float area_gxw ;
  float area_gxwas ;
  float area_gxwex ;
  float area_gy1grad ;
  float area_gy1table ;
  float area_gyakfs ;
  float area_gyakssf ;
  float area_gykcfh ;
  float area_gykcfl ;
  float area_gykcs ;
  float area_gykfs ;
  float area_gykrcvn ;
  float area_gyks ;
  float area_gykse1 ;
  float area_gykse2 ;
  float area_gykse3 ;
  float area_gykse4 ;
  float area_gykse5 ;
  float area_gykse6 ;
  float area_gykssf ;
  float area_gyksx1 ;
  float area_gyksx2 ;
  float area_gyksy1 ;
  float area_gyksy2 ;
  float area_gyksz1 ;
  float area_gyksz2 ;
  float area_gz1 ;
  float area_gz1as ;
  float area_gzfc ;
  float area_gzk ;
  float area_gzkcs ;
  float area_gzkfs ;
  float area_gzkgir01 ;
  float area_gzkgir02 ;
  float area_gzkmon ;
  float area_gzkmontipup ;
  float area_gzkrcvn ;
  float area_gzks ;
  float area_gzks5fp ;
  float area_gzkssf ;
  float area_gzrf0k ;
  float area_hst ;
  float area_killerx ;
  float area_killery ;
  float area_killerz ;
  float area_readrampas ;
  float area_rf1 ;
  float area_rf11 ;
  float area_rffs ;
  float area_rfse1 ;
  float area_rfse2 ;
  float area_rfse3 ;
  float area_rfse4 ;
  float area_rfse5 ;
  float area_rfse6 ;
  float area_rfssf ;
  float area_rfssfh ;
  float area_rfsx1 ;
  float area_rfsx2 ;
  float area_rfsy1 ;
  float area_rfsy2 ;
  float area_rfsz1 ;
  float area_rfsz2 ;
  float area_spoilerx ;
  float area_spoilery ;
  float area_spoilerz ;
  float area_xtgykiller ;
  float area_xtgzkiller ;
  float aregion_fraction ;
  int arr_check ;
  int as_dda ;
  int as_newgeo ;
  int asbaseline ;
  float asflip ;
  float asfov ;
  float aslenap ;
  float aslenrl ;
  float aslensi ;
  float aslocap ;
  float aslocrl ;
  float aslocsi ;
  LOG_GRAD asloggrd ;
  int asobl_debug ;
  int aspir_fa_scaling_flag ;
  int aspir_flag ;
  int aspir_override ;
  int asptsize ;
  int asrhblank ;
  float asset_factor ;
  int asset_supported_direction ;
  int assetph_flag ;
  float assetsl_factor ;
  int assetsl_flag ;
  float assetsl_min_opvthick ;
  int asslquant ;
  float asslthick ;
  float asx_killer_area ;
  int asxres ;
  int asymmatrix ;
  int asyres ;
  float asz_killer_area ;
  int attenlen ;
  int attenlength ;
  int audible_loop ;
  int autoadvtoscn ;
  int autocal_mode ;
  int autolock ;
  int autoparams_debug ;
  float avail_RRtime ;
  int avail_image_time ;
  int avail_pwgx1as ;
  int avail_pwgz1as ;
  int avail_temp ;
  float ave_grady_gy1_scale ;
  float ave_gradz_gzcomb_scale ;
  float ave_gradz_gzp_scale ;
  int avecrushpepowscale_for_SBM_XFD ;
  float avmax_dda ;
  float avmaxaccel_cs_stride ;
  float avmaxaccel_kt_stride ;
  float avmaxaccel_mb_stride ;
  float avmaxaccel_ph_stride ;
  float avmaxaccel_sl_stride ;
  float avmaxaccel_t_stride ;
  int avmaxacqs ;
  int avmaxallowedrescantime ;
  int avmaxaphases ;
  int avmaxbspti ;
  int avmaxbval ;
  float avmaxbvalstab ;
  float avmaxdifnext2 ;
  int avmaxdifnextab ;
  int avmaxetl ;
  float avmaxflip ;
  float avmaxfov ;
  int avmaxfphases ;
  float avmaxnavaccwin ;
  int avmaxnavautotrigtime ;
  int avmaxnavmaxinterval ;
  int avmaxnavpsctime ;
  int avmaxnavrrmeastime ;
  int avmaxnecho ;
  float avmaxnex ;
  int avmaxnseg ;
  int avmaxnshots ;
  int avmaxnspokes ;
  int avmaxnumbvals ;
  int avmaxnumsynbvals ;
  float avmaxoversamplingfactor ;
  int avmaxovl ;
  float avmaxphasefov ;
  int avmaxphases ;
  float avmaxphassetfac ;
  float avmaxrbw ;
  float avmaxrbw2 ;
  float avmaxrbw_system ;
  float avmaxrep_active ;
  float avmaxrep_rest ;
  float avmaxslassetfac ;
  int avmaxsldelay ;
  int avmaxslicecnt ;
  int avmaxslquant ;
  float avmaxslspace ;
  float avmaxslthick ;
  float avmaxsynbvalstab ;
  int avmaxt2prepte ;
  int avmaxtdel1 ;
  int avmaxte ;
  int avmaxte2 ;
  int avmaxti ;
  int avmaxtissuet1 ;
  int avmaxtlabel ;
  int avmaxtouchamp ;
  int avmaxtouchcyc ;
  int avmaxtouchfreq ;
  int avmaxtouchmegfreq ;
  int avmaxtouchtphases ;
  int avmaxtphases ;
  int avmaxtr ;
  int avmaxtrecovery ;
  int avmaxtricksdel ;
  int avmaxtseq ;
  float avmaxvenc ;
  float avmaxvest ;
  int avmaxvquant ;
  int avmaxvsphases ;
  int avmaxxres ;
  int avmaxyres ;
  float avmin_dda ;
  float avminaccel_cs_stride ;
  float avminaccel_kt_stride ;
  float avminaccel_mb_stride ;
  float avminaccel_ph_stride ;
  float avminaccel_sl_stride ;
  float avminaccel_t_stride ;
  int avminallowedrescantime ;
  int avminaphases ;
  int avminbspti ;
  int avminbval ;
  float avminbvalstab ;
  float avmindifnext2 ;
  int avmindifnextab ;
  int avmindphases ;
  int avminetl ;
  float avminflip ;
  float avminfov ;
  int avminfphases ;
  float avminnavaccwin ;
  int avminnavautotrigtime ;
  int avminnavmaxinterval ;
  int avminnavpsctime ;
  int avminnavrrmeastime ;
  int avminnecho ;
  float avminnex ;
  int avminnseg ;
  int avminnshots ;
  int avminnspokes ;
  int avminnumbvals ;
  int avminnumsynbvals ;
  float avminoversamplingfactor ;
  float avminphasefov ;
  int avminphases ;
  float avminphassetfac ;
  float avminrbw ;
  float avminrbw2 ;
  float avminrep_active ;
  float avminrep_rest ;
  int avminrttseq ;
  float avminslassetfac ;
  int avminsldelay ;
  int avminslicecnt ;
  int avminslquant ;
  float avminslspace ;
  float avminslthick ;
  float avminsynbvalstab ;
  int avmint2prepte ;
  int avmintdel1 ;
  int avminte ;
  int avminte2 ;
  int avminti ;
  int avmintissuet1 ;
  int avmintlabel ;
  int avmintouchamp ;
  int avmintouchcyc ;
  int avmintouchfreq ;
  int avmintouchmegfreq ;
  int avmintouchtphases ;
  int avmintphases ;
  int avmintr ;
  int avmintrecovery ;
  int avmintricksdel ;
  float avmintscan ;
  int avmintseq ;
  float avminvenc ;
  float avminvest ;
  int avminvsphases ;
  int avminxres ;
  int avminyres ;
  int avround ;
  int b1derate_flag ;
  float b1max_scale ;
  float b_value_3in1 ;
  float b_value_single ;
  int balanced_FE ;
  int baseline ;
  int bd_index ;
  int bf_rfscale ;
  int blank ;
  int brava_flag ;
  int bravo_fatsat ;
  int bravo_flag ;
  int break_flag ;
  int breastCoil_flag ;
  int breast_spsp_flag ;
  int bridge_gxw2_gxwex_3dde ;
  int brs_2d_fiesta_rf_flag ;
  int brs_2dflag ;
  float brs_alpha ;
  float brs_alpha_center ;
  int brs_areamode ;
  int brs_blipflag ;
  float brs_daqdel ;
  float brs_daqdeloff ;
  float brs_daqdeloff_zoom ;
  int brs_ddahbs ;
  int brs_debug_vieword ;
  int brs_dofracz ;
  int brs_echo_wait ;
  int brs_excite_grad ;
  int brs_exno ;
  int brs_extra_esp ;
  int brs_extra_len ;
  int brs_extrawait ;
  int brs_fast_rec_lpf ;
  float brs_filtdel ;
  int brs_flex ;
  float brs_fov0 ;
  float brs_fov1 ;
  float brs_fov2 ;
  float brs_fovpow ;
  float brs_fracz_fact ;
  int brs_fs_slice ;
  int brs_fsprep_flag ;
  int brs_fw_te_step ;
  int brs_fwflag ;
  int brs_gateddas ;
  float brs_gmax ;
  float brs_grad_derate ;
  float brs_grad_powscale ;
  int brs_gradlen ;
  int brs_gradlen2 ;
  float brs_gslew ;
  float brs_gzvl_area_base ;
  int brs_gzvl_delte ;
  int brs_gzvl_flag ;
  int brs_leafgroup ;
  int brs_leaflen ;
  int brs_leafskip ;
  int brs_m1null ;
  int brs_mapdel ;
  int brs_mapdel_act ;
  float brs_matrixsize_center ;
  int brs_me_flag ;
  int brs_mfa_flag ;
  int brs_mfa_num ;
  int brs_mfa_schedule ;
  int brs_min_esp ;
  int brs_mra_flag ;
  int brs_nfolds ;
  int brs_nphases ;
  int brs_numleaves ;
  int brs_numleaves_acq ;
  int brs_opti ;
  int brs_pm_numleaves ;
  int brs_pm_type ;
  int brs_preirdel ;
  int brs_psc ;
  int brs_psc_prot_no ;
  int brs_psc_use_tracker ;
  int brs_ramplength ;
  int brs_ramplength2 ;
  int brs_readoutdelay ;
  int brs_realtime ;
  float brs_recratio ;
  int brs_rhrecon ;
  float brs_rscale ;
  int brs_rspskp ;
  int brs_s5fp ;
  float brs_sampfact ;
  float brs_sampfact_center ;
  int brs_scantype ;
  int brs_shim_flag ;
  int brs_shim_update_type ;
  int brs_shim_x ;
  int brs_shim_y ;
  int brs_shim_z ;
  int brs_slewmax ;
  int brs_ssfp_flag ;
  int brs_type ;
  int brs_use_min_seqgrad ;
  int brs_vieword ;
  int brs_viewstocenter ;
  float brs_xarea ;
  float brs_xarea2 ;
  float brs_xbliparea ;
  float brs_xtarget ;
  float brs_xx ;
  float brs_xy ;
  float brs_yarea ;
  float brs_yarea2 ;
  float brs_ybliparea ;
  float brs_ytarget ;
  float brs_yx ;
  float brs_yy ;
  float brs_zarea ;
  int brs_zseg ;
  float brs_ztarget ;
  int brs_zvps ;
  int brsfc_flag ;
  int brsfc_longfc ;
  float brsfmx ;
  float brsfmy ;
  float brsfmz ;
  int btemp_debug ;
  int btemp_monitor ;
  int burstreps ;
  int bw_rf0 ;
  int bw_rf1 ;
  int bw_rf1as ;
  int bw_rf1mon ;
  int bw_rf2mon ;
  int bw_rffrir ;
  int bw_rfgir01 ;
  int bw_rfgir02 ;
  int bw_rfmontipup ;
  int bw_rfssfh ;
  int cal3d_flag ;
  int cal3d_interleave ;
  int cal3d_nex1 ;
  int cal3d_nex2 ;
  int cal3d_nex3 ;
  int cal3d_nex_mode ;
  int cal3d_pass_set ;
  int cal3d_pause_step ;
  int cal3d_phases ;
  int cal3d_state ;
  int cal3d_state1 ;
  int cal3d_state2 ;
  int cal3d_state3 ;
  CAL_PARAM calRegion ;
  int cal_ky_ktarc ;
  int cal_kz_ktarc ;
  int cal_shape ;
  int calc_rate ;
  int calibrationPoints ;
  float ccs_dead ;
  int ccs_relaxers ;
  int ccs_relaxseqtime ;
  int ccs_relaxtime ;
  int centric_flag ;
  int cerdtype ;
  int cfBbTransmitSelect ;
  int cfDualDriveCapable ;
  int cfEllipticDriveEnable ;
  int cfMnsConverterSelect ;
  int cfNbTransmitSelect ;
  int cfOptimalSnrRecon ;
  int cfVirtualChannelRecon ;
  float cfaccel_cs_maxstride ;
  float cfaccel_ph_maxstride ;
  float cfaccel_sl_maxstride ;
  n64 cfacqtodisksize ;
  int cfbbmod ;
  int cfbdcabletglimit ;
  float cfbllr ;
  float cfbpdl ;
  float cfbpsl ;
  float cfbpv ;
  float cfbqpc ;
  int cfbwmin ;
  int cfbwmin1 ;
  int cfcablebw ;
  int cfcablefreq ;
  int cfcabletg ;
  int cfcarddelay ;
  int cfcerdtype ;
  int cfcftdel ;
  float cfcgain ;
  float cfcoilAC_RxA ;
  float cfcoilAC_RxB ;
  float cfcoilAC_RxC ;
  float cfcoilAC_RyA ;
  float cfcoilAC_RyB ;
  float cfcoilAC_RyC ;
  float cfcoilAC_RzA ;
  float cfcoilAC_RzB ;
  float cfcoilAC_RzC ;
  int cfcoilAC_fftpoints ;
  float cfcoilAC_gain ;
  float cfcoilAC_lumpL2x ;
  float cfcoilAC_lumpL2y ;
  float cfcoilAC_lumpL2z ;
  float cfcoilAC_lumpL4x ;
  float cfcoilAC_lumpL4y ;
  float cfcoilAC_lumpL4z ;
  float cfcoilAC_lumpR1x ;
  float cfcoilAC_lumpR1y ;
  float cfcoilAC_lumpR1z ;
  float cfcoilAC_lumpR3x ;
  float cfcoilAC_lumpR3y ;
  float cfcoilAC_lumpR3z ;
  float cfcoilAC_lumpR5x ;
  float cfcoilAC_lumpR5y ;
  float cfcoilAC_lumpR5z ;
  float cfcoilAC_power ;
  float cfcoilAC_power_1axis ;
  float cfcoilAC_power_burst ;
  float cfcoilAC_temp_base_burst ;
  float cfcoilAC_temp_limit_burst ;
  float cfcoilAC_timeconstant_burst ;
  float cfcoilAC_timeres ;
  float cfcoilAC_xgain ;
  float cfcoilAC_ygain ;
  float cfcoilAC_zgain ;
  float cfcoilDC_Lx ;
  float cfcoilDC_Ly ;
  float cfcoilDC_Lz ;
  float cfcoilDC_Rx ;
  float cfcoilDC_Ry ;
  float cfcoilDC_Rz ;
  float cfcoilDC_gain ;
  float cfcoilQAC_A0 ;
  float cfcoilQAC_A1 ;
  float cfcoilQAC_A2 ;
  float cfcoilQAC_A3 ;
  float cfcoilQAC_A4 ;
  float cfcoilQAC_A5 ;
  float cfcoilQAC_A6 ;
  float cfcoilQAC_Xcoef ;
  float cfcoilQAC_Ycoef ;
  float cfcoilQAC_Zcoef ;
  float cfcoilQAC_const ;
  float cfcoilQAC_heat_const ;
  float cfcoilQAC_heat_maxtime ;
  float cfcoilQAC_heat_slope ;
  float cfcoilQAC_maxtime ;
  int cfcoilshld ;
  int cfcoilswitchmethod ;
  int cfcompress ;
  float cfdbdtdx ;
  float cfdbdtdy ;
  float cfdbdtdz ;
  float cfdbdtper ;
  float cfdbdtper2 ;
  float cfdbdtper_cont ;
  float cfdbdtper_max ;
  float cfdbdtper_norm ;
  float cfdbdtts ;
  int cfdbdttype ;
  int cfdbmax ;
  float cfderatingFactorRTSAR ;
  int cfdfm ;
  int cfdfmDX ;
  int cfdfmR1 ;
  int cfdfmTG ;
  int cfdppericn ;
  int cffall2x0 ;
  int cffall2x0fw ;
  int cffall2y0 ;
  int cffall2y0fw ;
  int cffall2z0 ;
  int cffall2z0fw ;
  int cffastprescan ;
  int cffield ;
  float cfgburstime ;
  int cfgcoiltype ;
  float cfgcontirms ;
  float cfgmax_arthigh ;
  float cfgmax_artmedium ;
  float cfgmax_artmediumopt ;
  int cfgovbody ;
  float cfgpeakirms ;
  float cfgpmpow ;
  int cfgradamp ;
  int cfgradcoil ;
  float cfh_crusher_area ;
  int cfh_dda ;
  int cfh_each ;
  float cfh_ec_position ;
  float cfh_fov ;
  int cfh_newgeo ;
  int cfh_newmode ;
  int cfh_nex ;
  float cfh_rf1freq ;
  float cfh_rf2freq ;
  float cfh_rf3freq ;
  float cfh_rf4freq ;
  int cfh_slquant ;
  int cfh_steam_flag ;
  int cfh_tdaq ;
  int cfh_ti ;
  int cfh_tr ;
  float cfhir_killer_area ;
  float cfhllr ;
  LOG_GRAD cfhloggrd ;
  int cfhobl_debug ;
  float cfhpdl ;
  float cfhpsl ;
  float cfhpv ;
  float cfhqpc ;
  float cfhscale ;
  int cfhtdel ;
  int cfhwgut ;
  int cfhwrfut ;
  int cfhwssput ;
  int cfl_dda ;
  int cfl_nex ;
  int cfl_tdaq ;
  int cfl_tr ;
  float cflcoil ;
  float cflinfrq ;
  LOG_GRAD cflloggrd ;
  float cfloss ;
  float cflscale ;
  float cfmaxave ;
  float cfmaxavepm ;
  float cfmaxb1ref ;
  float cfmaxb1rmshead ;
  float cfmaxbw ;
  float cfmaxcave ;
  float cfmaxcpeak ;
  float cfmaxepeak ;
  float cfmaxextremity ;
  float cfmaxhave ;
  float cfmaxpeak ;
  float cfmgps ;
  int cfnumartlevels ;
  int cfnumicn ;
  int cfnumrcvrs ;
  int cfopenmagnet ;
  int cfoption ;
  int cfpicture ;
  float cfpmgs ;
  int cfpsdgraddly ;
  int cfpsdrfdly ;
  int cfpsdrfdlyx ;
  int cfpsdrfdlyy ;
  int cfpsdrfdlyz ;
  int cfpure_filtering_mode ;
  int cfpwrmonreflmeas ;
  int cfpwrmontyp ;
  float cfraccoil ;
  int cframpdir ;
  int cframpdir_tgt ;
  float cfrcoil ;
  int cfrealtime ;
  int cfreceiveroffsetfreq ;
  int cfreceiverswitchtype ;
  int cfreceivertype ;
  int cfrecvend ;
  int cfrecvst ;
  int cfrfMaxAttenuation ;
  int cfrfact ;
  float cfrfampftconst ;
  float cfrfampftlinear ;
  float cfrfampftquadratic ;
  int cfrfamptyp ;
  int cfrfboardtype ;
  int cfrfmapb ;
  int cfrfmaph ;
  int cfrfmaps ;
  float cfrfmdcb ;
  float cfrfmdch ;
  float cfrfmdcs ;
  int cfrfminblank ;
  int cfrfminblanktorcv ;
  int cfrfminunblk ;
  float cfrfmpeb ;
  float cfrfmpeh ;
  float cfrfmpes ;
  int cfrfmpwb ;
  int cfrfmpwh ;
  int cfrfmpws ;
  int cfrfrapb ;
  int cfrfrapcw ;
  int cfrfraph ;
  int cfrfraps ;
  int cfrfunblank ;
  int cfrfupa ;
  int cfrfupd ;
  float cfrhr ;
  float cfrinf ;
  int cfrmp2xfs ;
  int cfrmp2xfsfw ;
  int cfrmp2yfs ;
  int cfrmp2yfsfw ;
  int cfrmp2zfs ;
  int cfrmp2zfsfw ;
  int cfscoutscanact ;
  float cfsdlim ;
  float cfslew_arthigh ;
  float cfslew_artmedium ;
  float cfslew_artmediumopt ;
  float cfspectroPMcal ;
  int cfsrmode ;
  float cfsrmodeact ;
  float cfsrmodeconv ;
  int cfswgut ;
  int cfswrfut ;
  int cfswssput ;
  float cfsystemmaxfov ;
  float cftableanglex ;
  float cftableangley ;
  float cftableanglez ;
  int cftablemaxaccel ;
  int cftablemaxdecel ;
  int cftablemaxspeed ;
  float cftableoffsetx ;
  float cftableoffsety ;
  float cftableoffsetz ;
  int cftpsnproc ;
  int cftpsproctype ;
  float cftpssize ;
  int cftrnew ;
  int cftuning ;
  float cfvhr ;
  float cfxamptran ;
  int cfxasm ;
  float cfxbeta ;
  float cfxcc ;
  float cfxfa ;
  float cfxfd_power_limit ;
  float cfxfd_temp_limit ;
  float cfxfs ;
  int cfxfull ;
  int cfxgasm ;
  float cfxgd_IGBTtemplimit ;
  float cfxgd_busbartemplimit ;
  float cfxgd_cableirmslimit ;
  float cfxgd_cableirmslimit_burst ;
  float cfxgd_cabletimeconstant_burst ;
  float cfxgd_chokepowerlimit ;
  float cfxgd_timeres ;
  int cfxgram ;
  float cfxiavrgabs ;
  float cfxipeak ;
  float cfxirms ;
  float cfxirmsneg ;
  float cfxirmspos ;
  float cfxmgrampow ;
  int cfxnumpower ;
  float cfxps_avghvpwrlimit ;
  float cfxps_avglvpwrlimit ;
  float cfxps_avgpdulimit ;
  float cfxpwmdc ;
  int cfxrdelay ;
  float cfxrsat ;
  int cfxseries ;
  float cfxvpwm ;
  float cfxvsat ;
  float cfyamptran ;
  int cfyasm ;
  float cfybeta ;
  float cfycc ;
  float cfyfa ;
  float cfyfs ;
  int cfyfull ;
  int cfygasm ;
  int cfygram ;
  float cfyiavrgabs ;
  float cfyipeak ;
  float cfyirms ;
  float cfyirmsneg ;
  float cfyirmspos ;
  float cfymgrampow ;
  int cfynumpower ;
  float cfypwmdc ;
  int cfyrdelay ;
  float cfyrsat ;
  int cfyseries ;
  float cfyvpwm ;
  float cfyvsat ;
  float cfzamptran ;
  int cfzasm ;
  float cfzbeta ;
  float cfzcc ;
  float cfzfa ;
  float cfzfs ;
  int cfzfull ;
  int cfzgasm ;
  int cfzgram ;
  float cfziavrgabs ;
  float cfzipeak ;
  float cfzirms ;
  float cfzirmsneg ;
  float cfzirmspos ;
  float cfzmgrampow ;
  int cfznumpower ;
  int cfzoomlim_ctl ;
  int cfzoomlim_fov ;
  int cfzoomlim_ofc ;
  float cfzpwmdc ;
  int cfzrdelay ;
  float cfzrsat ;
  int cfzseries ;
  float cfzvpwm ;
  float cfzvsat ;
  int cgate_dda ;
  int channel_combine_mode ;
  int channel_compression ;
  int chemfreq ;
  int chemsat_acq ;
  int chemsat_dda ;
  float chemscale ;
  int chemseq0 ;
  int chemseqs ;
  int chksum_rampdir ;
  int chksum_rampdir_tgt ;
  n32 chksum_rhdacqctrl ;
  int chksum_rhdacqctrl_view ;
  n32 chksum_scaninfo ;
  int chksum_scaninfo_view ;
  int choplet ;
  float cine3d_arrlimit ;
  int cine3d_flag ;
  int cine3d_fullkviews ;
  int cine3d_fullkviews_cal ;
  int cine3d_ktsamp_mode ;
  int cine3d_maxslquant ;
  int cine3d_minslquant ;
  int cine3d_num_segs_est ;
  int cine3d_targetedphases_max ;
  int cine3d_totalviews_est ;
  int cine3d_yz_order ;
  int cine_choplet ;
  int cinv16_iso_delay ;
  float coeff_pw_tg ;
  float coil_map_2_filter_width ;
  float coil_map_smooth_factor ;
  int coilsw_data ;
  int coilsw_ds ;
  int coilsw_oc ;
  int coll_prefls ;
  float combined_coil_map_thres ;
  int combo_mode ;
  int compositeon ;
  int comptipupon ;
  int config_update_mode ;
  int cont_debug ;
  int cont_flag ;
  float corr_factor_x ;
  float corr_factor_y ;
  float corr_factor_z ;
  int corr_mode ;
  int corr_x ;
  int corr_y ;
  int corr_z ;
  int count_grd_wait ;
  int count_rfupd ;
  int cs_flag ;
  int cs_sat ;
  int cs_satstart ;
  int cs_satstart_min ;
  int cs_sattime ;
  int csat_rfupa ;
  int csat_sys_type ;
  int csi_grid_on ;
  int csw_time_ssi ;
  int csw_tr ;
  int csw_wait_before ;
  int csw_wait_sethubindeximm ;
  int csw_wait_setrcvportimm ;
  int csweight ;
  int csxkillerFlag ;
  int cszkillerFlag ;
  float curr_eff ;
  int cutcorner_flag ;
  int cutpostlobes ;
  int cv_rfupa ;
  int cvlock ;
  float cyc_rf0 ;
  float cyc_rf0cfh ;
  float cyc_rf1 ;
  float cyc_rf1_pre ;
  float cyc_rf1_temp ;
  float cyc_rf1as ;
  float cyc_rf1cfh ;
  float cyc_rf1cfl ;
  float cyc_rf1dtg ;
  float cyc_rf1ftg ;
  float cyc_rf1htr ;
  float cyc_rf1mon ;
  float cyc_rf1mps1 ;
  float cyc_rf1rs ;
  float cyc_rf1tm ;
  float cyc_rf1xtg ;
  float cyc_rf2 ;
  float cyc_rf2cfh ;
  float cyc_rf2ftg ;
  float cyc_rf2mon ;
  float cyc_rf2mps1 ;
  float cyc_rf2xtg ;
  float cyc_rf3cfh ;
  float cyc_rf3ftg ;
  float cyc_rf4cfh ;
  float cyc_rfcssat ;
  float cyc_rffrir ;
  float cyc_rfgir01 ;
  float cyc_rfgir02 ;
  float cyc_rfmontipup ;
  float cyc_rfs ;
  float cyc_rfse1 ;
  float cyc_rfse2 ;
  float cyc_rfse3 ;
  float cyc_rfse4 ;
  float cyc_rfse5 ;
  float cyc_rfse6 ;
  float cyc_rfsx1 ;
  float cyc_rfsx2 ;
  float cyc_rfsy1 ;
  float cyc_rfsy2 ;
  float cyc_rfsz1 ;
  float cyc_rfsz2 ;
  float cylr_dtheta ;
  int cylr_manoff ;
  int cylr_rf_type ;
  float cylr_skew ;
  float cylr_xoff ;
  float cylr_yoff ;
  int d3dtr ;
  int dab_offset ;
  int dab_packet ;
  int dabout_length ;
  int data_type ;
  int dbdt_debug ;
  int dbdt_disable ;
  int dbdt_mode ;
  int dbdt_option_key_status ;
  int dbdtlevel_opt ;
  int dda ;
  int dda_delay ;
  int dda_one_second ;
  int dda_trigger_delay_disdaqs ;
  int dda_trigger_delay_silent_countdown ;
  int de3d_flag ;
  int debug ;
  int debug_card_sim ;
  int debug_dbdt ;
  int debug_gir ;
  int debug_grad_spec ;
  int debug_monloc ;
  int debug_monrot ;
  int debug_monrotphi ;
  int debug_nav ;
  int debug_order ;
  int debug_scale ;
  int debug_scan ;
  int debug_shimvol_slice ;
  int debug_sp_agp ;
  int debug_sp_rtp ;
  int debug_tdel ;
  int debug_viewtab ;
  int decimation ;
  int delay3Drecon_flag ;
  int delay_dda ;
  int delay_ec_flag ;
  int delay_ec_frames ;
  int delay_ec_period ;
  int delay_quiet_dda ;
  int delay_quiet_time ;
  int delay_rfhubsel ;
  float deltf ;
  int derate_ACGD ;
  int derate_gxwex ;
  float derateb1_NV_factor ;
  float derateb1_body_factor ;
  float derateb1_default ;
  int derateb1_dir ;
  float derateb1_min ;
  float derateb1_noniteropt ;
  float derateb1_opt ;
  int detector_mode ;
  int dex ;
  int df ;
  float dfg ;
  float dfscale ;
  int disable_exciter_unblank ;
  int disco_1echo_flag ;
  int disco_flag ;
  int disco_nphases ;
  int discodda ;
  float discretionaryB1rms ;
  float discretionaryPeakB1 ;
  float discretionaryave ;
  float discretionaryhave ;
  int dither_on ;
  int dither_value ;
  float dix_freq ;
  int dix_timeas ;
  float dnav_win_BAratio ;
  int do_maxrbw_check_in_cveval ;
  int dobaselines ;
  int dtg_dda ;
  int dtg_esp ;
  int dtg_iso_delay ;
  int dtg_off90 ;
  LOG_GRAD dtgloggrd ;
  int dtgphorder ;
  int dtgspgr_flag ;
  int dtgt_exa ;
  int dtgt_exb ;
  int dti_plus_flag ;
  int dummy_pw ;
  int dummyrf_ssitime ;
  int dummyrf_time ;
  int dump_channel_comp_optimal_recon ;
  float dutycycle_scale ;
  float dynTG_b1factor ;
  int dynTG_baseline ;
  int dynTG_etl ;
  float dynTG_flipangle ;
  float dynTG_fov ;
  int dynTG_ptsize ;
  int dynTG_slquant ;
  float dynTG_slthick ;
  int dynTG_xres ;
  int dynTG_yres ;
  int e2_delay_dtg ;
  int e2_delay_rs ;
  int ec3_iteration_method ;
  int ec3_iterations ;
  int ecg_cont_dda_flag ;
  int ecg_dda ;
  int ecg_dda_delay ;
  float echo1bw ;
  float echo1bwas ;
  float echo1bwcfh ;
  float echo1bwcfl ;
  float echo1bwdtg ;
  float echo1bwrcvn ;
  float echo1bwrs ;
  float echo1monbw ;
  float echo2bw ;
  int echo_sort_dir ;
  int echoint ;
  int eeff ;
  int eepf ;
  int eff_cfh_te ;
  int eg_phaseres ;
  int elava_flag ;
  int ellipt_debug_files ;
  int ellipt_flag ;
  int enable_alpha ;
  int enable_sbm ;
  int enablfracdec ;
  float encode ;
  float encode2 ;
  int encode_group ;
  float end_gycylra ;
  float end_gycylratipup ;
  float end_gzcylra ;
  float end_gzcylratipup ;
  int end_segment_delay ;
  int endview_iamp ;
  int endview_iampas ;
  int endview_iampdtg ;
  int endview_iamprs ;
  float endview_scale ;
  float endview_scaleas ;
  float endview_scaledtg ;
  float endview_scalers ;
  int endviewz_iamp ;
  float endviewz_scale ;
  int enforce_cal_for_channel_combine ;
  int enforce_dbdtopt ;
  int enforce_inrangetr ;
  int enforce_minseqseg ;
  int enhanced_nav_flag ;
  int epi_ir_on ;
  int equant ;
  int esp ;
  int esp_msde ;
  float ethick ;
  int exnex ;
  float exsat1_dist ;
  float exsat1_normth_A ;
  float exsat1_normth_R ;
  float exsat1_normth_S ;
  float exsat2_dist ;
  float exsat2_normth_A ;
  float exsat2_normth_R ;
  float exsat2_normth_S ;
  float exsat3_dist ;
  float exsat3_normth_A ;
  float exsat3_normth_R ;
  float exsat3_normth_S ;
  float exsat4_dist ;
  float exsat4_normth_A ;
  float exsat4_normth_R ;
  float exsat4_normth_S ;
  float exsat5_dist ;
  float exsat5_normth_A ;
  float exsat5_normth_R ;
  float exsat5_normth_S ;
  float exsat6_dist ;
  float exsat6_normth_A ;
  float exsat6_normth_R ;
  float exsat6_normth_S ;
  float exsatthick1 ;
  float exsatthick2 ;
  float exsatthick3 ;
  float exsatthick4 ;
  float exsatthick5 ;
  float exsatthick6 ;
  int extraRRlimit ;
  float extraScale ;
  int extras ;
  int extraspecial_flag ;
  int extraspecial_seq_order_flag ;
  int fa_scale_debug ;
  int fast_xtr ;
  int fastprescan ;
  int fatFlag ;
  int fatT1 ;
  float fat_delta ;
  int fat_flag ;
  int fat_offset ;
  int fatkiller_flag ;
  int fc_debug ;
  int fcineim ;
  int fcinent ;
  float fecho_factor ;
  float fermi_r_factor ;
  float fermi_rc ;
  float fermi_w_factor ;
  float fermi_wc ;
  int fermr_coef_1024 ;
  float ff4error ;
  int field_strength ;
  float fieldstrength ;
  int fiesta_gated_dda ;
  int fiesta_gated_flat_dda ;
  int fiesta_gated_ramp_dda ;
  int fiesta_gated_ramp_down ;
  int fiesta_killer_flag ;
  int fiesta_rampup_type ;
  int filter_cfh_fid ;
  int filter_cfl_fid ;
  int filter_echo1 ;
  int filter_echo1as ;
  int filter_echo1dtg ;
  int filter_echo1ftg ;
  int filter_echo1mon ;
  int filter_echo1mps1 ;
  int filter_echo1rs ;
  int filter_echo1tm ;
  int filter_echo1xtg ;
  int filter_echo2 ;
  int filter_echo2ftg ;
  int filter_rcvn_fid ;
  int filterslot1 ;
  int filterslot2 ;
  int firstSeriesFlag ;
  STATUS first_prepscan ;
  STATUS first_scan ;
  int fix_fermi ;
  float fl_width_x_frac ;
  float fl_width_x_full ;
  int flexte_flag ;
  int flextr_flag ;
  float flip_hard180 ;
  float flip_pctas ;
  float flip_rf0 ;
  float flip_rf0cfh ;
  float flip_rf1 ;
  float flip_rf180 ;
  float flip_rf1as ;
  float flip_rf1cfh ;
  float flip_rf1cfl ;
  float flip_rf1dtg ;
  float flip_rf1ftg ;
  float flip_rf1mon ;
  float flip_rf1mps1 ;
  float flip_rf1rs ;
  float flip_rf1tm ;
  float flip_rf1xtg ;
  float flip_rf2cfh ;
  float flip_rf2ftg ;
  float flip_rf2mon ;
  float flip_rf2mps1 ;
  float flip_rf2xtg ;
  float flip_rf3cfh ;
  float flip_rf3ftg ;
  float flip_rf3xtg ;
  float flip_rf4cfh ;
  float flip_rf4xtg ;
  float flip_rf90 ;
  float flip_rfbdtg ;
  float flip_rfbrs ;
  float flip_rfcssat ;
  float flip_rfcssat_noscale ;
  float flip_rfcssatcfh ;
  float flip_rfcylr ;
  float flip_rfcylr_navsat ;
  float flip_rfcylrtipup ;
  float flip_rfflp180 ;
  float flip_rfflp90 ;
  float flip_rfflp90r ;
  float flip_rffrir ;
  float flip_rffs ;
  float flip_rfgir01 ;
  float flip_rfgir02 ;
  float flip_rfmon_navsat ;
  float flip_rfmontipup ;
  float flip_rfs5fph ;
  float flip_rfse1 ;
  float flip_rfse2 ;
  float flip_rfse3 ;
  float flip_rfse4 ;
  float flip_rfse5 ;
  float flip_rfse6 ;
  float flip_rfssf ;
  float flip_rfssfh ;
  float flip_rfsx1 ;
  float flip_rfsx2 ;
  float flip_rfsy1 ;
  float flip_rfsy2 ;
  float flip_rfsz1 ;
  float flip_rfsz2 ;
  float flip_rftipup ;
  int flow4D_flag ;
  int flow_comp_type ;
  float flow_wdth_x ;
  float flow_wdth_y ;
  float flow_wdth_z ;
  int flowpos1x ;
  int flowpos1y ;
  int flowpos1z ;
  int flowpos2x ;
  int flowpos2y ;
  int flowpos2z ;
  float fn ;
  float fnecho_frac ;
  float fnecho_lim ;
  int force_gradOpt_loop_break ;
  int fov_advisory_ignore_mslices ;
  float fov_factor ;
  float fov_freq_scale ;
  float fov_lim_mps ;
  float fov_phase_scale ;
  float fov_scaling ;
  int frac_rf ;
  float fract_echo_annefact_reduction ;
  int freqSign ;
  float freq_scale ;
  int fs_2pi ;
  int fs_pcfiesta_flag ;
  int fs_pi ;
  int ftg_dda ;
  float ftgscale ;
  int ftgtr ;
  int ftmra_debug ;
  int ftmra_dfsat_flag ;
  int ftmra_enable_flag ;
  int ftmra_exsat_flag ;
  int ftmra_flag ;
  int ftmra_hard180_act ;
  int ftmra_sat_flag ;
  int fullte_flag ;
  int gated_dda ;
  int gating ;
  int genview_ellipt_cal ;
  float genview_fovVthick_scale ;
  int genview_maxaphase ;
  int genview_totalviews ;
  int get_fullecho ;
  int gir_newgeo ;
  int gir_obl_debug ;
  int gir_rfiso1 ;
  int gir_rfiso2 ;
  int gir_start ;
  int gir_td0 ;
  int gir_time ;
  int gir_time_daq ;
  int gir_time_eval ;
  LOG_GRAD girloggrd ;
  float gldelayf ;
  float glimit ;
  float glimit_x ;
  float glimit_y ;
  float glimit_z ;
  int golden_ratio_flag ;
  int gradChokeFlag ;
  int gradCoilMethod ;
  int gradDCsafeMethod ;
  int gradDriverMethod ;
  int gradHeatFile ;
  int gradHeatFlag ;
  int gradHeatMethod ;
  int gradOpt_GX2 ;
  int gradOpt_Piter_count ;
  float gradOpt_Ptor ;
  float gradOpt_Pweight ;
  int gradOpt_TE ;
  float gradOpt_TEfactor ;
  float gradOpt_TEfactor_Max ;
  float gradOpt_TEfactor_Min ;
  float gradOpt_TRfactor ;
  float gradOpt_TRfactor_Max ;
  float gradOpt_TRfactor_Min ;
  int gradOpt_aTETR_method ;
  int gradOpt_convergence_flag ;
  int gradOpt_flag ;
  int gradOpt_iter_count ;
  float gradOpt_nonconv_tor ;
  float gradOpt_nonconv_tor_limit ;
  int gradOpt_powerOpt_flag ;
  float gradOpt_powerTE ;
  float gradOpt_powerTR ;
  float gradOpt_ratio ;
  int gradOpt_run_flag ;
  float gradOpt_scale ;
  float gradOpt_scale_Max ;
  float gradOpt_scale_Min ;
  float gradOpt_slewRate ;
  float gradOpt_slewRate_limit ;
  float gradOpt_slewRate_tmp ;
  float gradOpt_tor ;
  float gradOpt_weight ;
  float grad_intensity_thres ;
  int grad_spec_change_flag ;
  int grad_spec_ctrl ;
  int gradient_mode ;
  int grid_fov_factor ;
  float gsat_scale ;
  float gscale_hard180 ;
  float gscale_kill ;
  float gscale_omega_hs_rfcssat ;
  float gscale_omega_ir0 ;
  float gscale_omega_rffrir ;
  float gscale_omega_rfgir01 ;
  float gscale_omega_rfgir02 ;
  float gscale_omegarf0cfh ;
  float gscale_rf0 ;
  float gscale_rf0cfh ;
  float gscale_rf1 ;
  float gscale_rf1as ;
  float gscale_rf1cfh ;
  float gscale_rf1cfl ;
  float gscale_rf1dtg ;
  float gscale_rf1ftg ;
  float gscale_rf1mon ;
  float gscale_rf1mps1 ;
  float gscale_rf1rs ;
  float gscale_rf1tm ;
  float gscale_rf1xtg ;
  float gscale_rf2ftg ;
  float gscale_rf2mon ;
  float gscale_rf2mps1 ;
  float gscale_rf2xtg ;
  float gscale_rf3ftg ;
  float gscale_rf3xtg ;
  float gscale_rf4xtg ;
  float gscale_rf90 ;
  float gscale_rfcssat ;
  float gscale_rfflp180 ;
  float gscale_rfflp180_the ;
  float gscale_rfflp90 ;
  float gscale_rfflp90_the ;
  float gscale_rfflp90r ;
  float gscale_rfflp90r_the ;
  float gscale_rffrir ;
  float gscale_rfgir01 ;
  float gscale_rfgir02 ;
  float gscale_rfmontipup ;
  float gscale_rfse1 ;
  float gscale_rfse2 ;
  float gscale_rfse3 ;
  float gscale_rfse4 ;
  float gscale_rfse5 ;
  float gscale_rfse6 ;
  float gscale_rfsx1 ;
  float gscale_rfsx2 ;
  float gscale_rfsy1 ;
  float gscale_rfsy2 ;
  float gscale_rfsz1 ;
  float gscale_rfsz2 ;
  float gscale_rftipup ;
  float gxfctarget ;
  int gxwex_bridge ;
  int gxwex_on ;
  float gxwex_target ;
  float gxwex_target_hfdslite ;
  float gxwex_target_hfdslite_value_3dde ;
  float gyfctarget ;
  int gykcs_max ;
  float gz1_first_moment ;
  float gz1_zero_moment ;
  int gz_time ;
  float gzfctarget ;
  int gzptime ;
  int gztype ;
  int had_sat ;
  int hard180time ;
  int headneck_pos_scan ;
  int heart3d_flag ;
  int higher_dbdt_flag ;
  int hires_recon ;
  int hist_wait_time ;
  int hrf1a ;
  int hrf1b ;
  int hst_flag ;
  int hst_length ;
  int ia_cine3d ;
  int ia_coilsw_off ;
  int ia_coilsw_on ;
  int ia_contrfhubsel ;
  int ia_contrfsel ;
  int ia_dDDIQ ;
  int ia_ddphase ;
  int ia_de ;
  int ia_dtreg ;
  int ia_dtregpass ;
  int ia_endgycylra ;
  int ia_endgycylratipup ;
  int ia_endgzcylra ;
  int ia_endgzcylratipup ;
  int ia_gx1 ;
  int ia_gx1as ;
  int ia_gx1bftg ;
  int ia_gx1bxtg ;
  int ia_gx1cfh ;
  int ia_gx1d ;
  int ia_gx1dtg ;
  int ia_gx1fed ;
  int ia_gx1fen ;
  int ia_gx1feu ;
  int ia_gx1ftg ;
  int ia_gx1mon ;
  int ia_gx1mps1 ;
  int ia_gx1rs ;
  int ia_gx1tm ;
  int ia_gx1u ;
  int ia_gx1wa ;
  int ia_gx1wb ;
  int ia_gx2 ;
  int ia_gx2dtg ;
  int ia_gx2fed ;
  int ia_gx2fen ;
  int ia_gx2feu ;
  int ia_gx2ftg ;
  int ia_gx2rs ;
  int ia_gx2test ;
  int ia_gxb ;
  int ia_gxbrsfc1 ;
  int ia_gxbrsfc2 ;
  int ia_gxfc ;
  int ia_gxfcd ;
  int ia_gxfcmon ;
  int ia_gxfcu ;
  int ia_gxflpk ;
  int ia_gxflpkwa ;
  int ia_gxflpkwb ;
  int ia_gxflpvenc ;
  int ia_gxflpvencwa ;
  int ia_gxflpvencwb ;
  int ia_gxhyst1 ;
  int ia_gxhyst2 ;
  int ia_gxkas ;
  int ia_gxkbsdtg ;
  int ia_gxkbsrs ;
  int ia_gxkcs ;
  int ia_gxkdtg ;
  int ia_gxkfs ;
  int ia_gxkill ;
  int ia_gxkrcvn ;
  int ia_gxkrs ;
  int ia_gxks ;
  int ia_gxkse1 ;
  int ia_gxkse2 ;
  int ia_gxkse3 ;
  int ia_gxkse4 ;
  int ia_gxkse5 ;
  int ia_gxkse6 ;
  int ia_gxksp ;
  int ia_gxkssf ;
  int ia_gxksx1 ;
  int ia_gxksx2 ;
  int ia_gxksy1 ;
  int ia_gxksy2 ;
  int ia_gxksz1 ;
  int ia_gxksz2 ;
  int ia_gxrf1tm ;
  int ia_gxrf2cfh ;
  int ia_gxrfsx1 ;
  int ia_gxrfsx2 ;
  int ia_gxspiral ;
  int ia_gxspiral2 ;
  int ia_gxspoil ;
  int ia_gxspoil2 ;
  int ia_gxw ;
  int ia_gxw1ftg ;
  int ia_gxw1xtg ;
  int ia_gxw2 ;
  int ia_gxw2dtg ;
  int ia_gxw2ftg ;
  int ia_gxw2rs ;
  int ia_gxwas ;
  int ia_gxwdtg ;
  int ia_gxwex ;
  int ia_gxwmon ;
  int ia_gxwmps1 ;
  int ia_gxwrs ;
  int ia_gy1 ;
  int ia_gy1as ;
  int ia_gy1aswa ;
  int ia_gy1aswb ;
  int ia_gy1cfh ;
  int ia_gy1dtg ;
  int ia_gy1dtgwa ;
  int ia_gy1dtgwb ;
  int ia_gy1fed ;
  int ia_gy1fen ;
  int ia_gy1feu ;
  int ia_gy1mon ;
  int ia_gy1mps1 ;
  int ia_gy1r ;
  int ia_gy1ras ;
  int ia_gy1raswa ;
  int ia_gy1raswb ;
  int ia_gy1rdtg ;
  int ia_gy1rdtgwa ;
  int ia_gy1rdtgwb ;
  int ia_gy1rrs ;
  int ia_gy1rrswa ;
  int ia_gy1rrswb ;
  int ia_gy1rs ;
  int ia_gy1rswa ;
  int ia_gy1rswb ;
  int ia_gy1rwa ;
  int ia_gy1rwb ;
  int ia_gy1tm ;
  int ia_gy1wa ;
  int ia_gy1wb ;
  int ia_gy2dtg ;
  int ia_gy2dtgwa ;
  int ia_gy2dtgwb ;
  int ia_gy2fed ;
  int ia_gy2fen ;
  int ia_gy2feu ;
  int ia_gy2rs ;
  int ia_gy2rswa ;
  int ia_gy2rswb ;
  int ia_gyb ;
  int ia_gybrsfc1 ;
  int ia_gybrsfc2 ;
  int ia_gycylr ;
  int ia_gycylrtipup ;
  int ia_gyfe ;
  int ia_gyfe1 ;
  int ia_gyfe2 ;
  int ia_gyflpk ;
  int ia_gyflpkwa ;
  int ia_gyflpkwb ;
  int ia_gyflpvenc ;
  int ia_gyflpvencwa ;
  int ia_gyflpvencwb ;
  int ia_gyhyst1 ;
  int ia_gyhyst2 ;
  int ia_gykcfh ;
  int ia_gykcfl ;
  int ia_gykcs ;
  int ia_gykcs_max ;
  int ia_gykfs ;
  int ia_gykill ;
  int ia_gykrcvn ;
  int ia_gykse1 ;
  int ia_gykse2 ;
  int ia_gykse3 ;
  int ia_gykse4 ;
  int ia_gykse5 ;
  int ia_gykse6 ;
  int ia_gyksp ;
  int ia_gykssf ;
  int ia_gyksx1 ;
  int ia_gyksx2 ;
  int ia_gyksy1 ;
  int ia_gyksy2 ;
  int ia_gyksz1 ;
  int ia_gyksz2 ;
  int ia_gykxtgl ;
  int ia_gykxtgr ;
  int ia_gyrf0kcfh ;
  int ia_gyrf1mon ;
  int ia_gyrf1mps1 ;
  int ia_gyrf1tm ;
  int ia_gyrf1xtg ;
  int ia_gyrf2cfh ;
  int ia_gyrf2lmon ;
  int ia_gyrf2mon ;
  int ia_gyrf2rmon ;
  int ia_gyrf3cfh ;
  int ia_gyrfmontipup ;
  int ia_gyrfsy1 ;
  int ia_gyrfsy2 ;
  int ia_gyspiral ;
  int ia_gyspiral2 ;
  int ia_gyspoil ;
  int ia_gyspoil2 ;
  int ia_gz1 ;
  int ia_gz1as ;
  int ia_gz1cfl ;
  int ia_gz1d ;
  int ia_gz1dtg ;
  int ia_gz1fed ;
  int ia_gz1fen ;
  int ia_gz1feu ;
  int ia_gz1ftg ;
  int ia_gz1mon ;
  int ia_gz1mps1 ;
  int ia_gz1rs ;
  int ia_gz1s ;
  int ia_gz1u ;
  int ia_gz1xtg ;
  int ia_gz2bftg ;
  int ia_gz2fed ;
  int ia_gz2fen ;
  int ia_gz2feu ;
  int ia_gz2ftg ;
  int ia_gz2xtg ;
  int ia_gz3ftg ;
  int ia_gzbrsfc1 ;
  int ia_gzbrsfc1echo1 ;
  int ia_gzbrsfc1echo2 ;
  int ia_gzbrsfc2 ;
  int ia_gzcomb ;
  int ia_gzcombhtr ;
  int ia_gzcombhtrwa ;
  int ia_gzcombhtrwb ;
  int ia_gzcombwa ;
  int ia_gzcombwb ;
  int ia_gzcylr ;
  int ia_gzcylrtipup ;
  int ia_gzfcbase ;
  int ia_gzfccomb ;
  int ia_gzfcd ;
  int ia_gzfcend ;
  int ia_gzfcu ;
  int ia_gzflpk ;
  int ia_gzflpkwa ;
  int ia_gzflpkwb ;
  int ia_gzflpvenc ;
  int ia_gzflpvencwa ;
  int ia_gzflpvencwb ;
  int ia_gzk ;
  int ia_gzkas ;
  int ia_gzkbsdtg ;
  int ia_gzkbsrs ;
  int ia_gzkcs ;
  int ia_gzkdtg ;
  int ia_gzkfs ;
  int ia_gzkgir01 ;
  int ia_gzkgir02 ;
  int ia_gzkill ;
  int ia_gzkiller ;
  int ia_gzkmon ;
  int ia_gzkmontipup ;
  int ia_gzkrcvn ;
  int ia_gzkrffrir ;
  int ia_gzkrs ;
  int ia_gzks ;
  int ia_gzks5fp ;
  int ia_gzksp ;
  int ia_gzkssf ;
  int ia_gzp ;
  int ia_gzphtr ;
  int ia_gzphtrwa ;
  int ia_gzphtrwb ;
  int ia_gzptm ;
  int ia_gzpwa ;
  int ia_gzpwb ;
  int ia_gzrf0 ;
  int ia_gzrf0cfh ;
  int ia_gzrf0k ;
  int ia_gzrf1 ;
  float ia_gzrf1_temp ;
  int ia_gzrf1as ;
  int ia_gzrf1cfh ;
  int ia_gzrf1cfl ;
  int ia_gzrf1dtg ;
  int ia_gzrf1ftg ;
  int ia_gzrf1htr ;
  int ia_gzrf1mon ;
  int ia_gzrf1mps1 ;
  int ia_gzrf1rs ;
  int ia_gzrf1s ;
  int ia_gzrf1xtg ;
  int ia_gzrf2ftg ;
  int ia_gzrf2lcfh ;
  int ia_gzrf2lmps1 ;
  int ia_gzrf2mps1 ;
  int ia_gzrf2rcfh ;
  int ia_gzrf2rmps1 ;
  int ia_gzrf2xtg ;
  int ia_gzrf3ftg ;
  int ia_gzrf3lcfh ;
  int ia_gzrf3rcfh ;
  int ia_gzrf4cfh ;
  int ia_gzrf4lcfh ;
  int ia_gzrf4rcfh ;
  int ia_gzrffrir ;
  int ia_gzrfgir01 ;
  int ia_gzrfgir02 ;
  int ia_gzrfs5fph ;
  int ia_gzrfse1 ;
  int ia_gzrfse2 ;
  int ia_gzrfse3 ;
  int ia_gzrfse4 ;
  int ia_gzrfse5 ;
  int ia_gzrfse6 ;
  int ia_gzrfssfh ;
  int ia_gzrfsz1 ;
  int ia_gzrfsz2 ;
  int ia_gzs5fphcomb ;
  int ia_gzssfhcomb ;
  int ia_gzvlw ;
  int ia_hard180 ;
  int ia_omega_hs_rfcssat ;
  int ia_omega_ir0 ;
  int ia_omega_rffrir ;
  int ia_omega_rfgir01 ;
  int ia_omega_rfgir02 ;
  int ia_omegarf0cfh ;
  int ia_ph180 ;
  int ia_phs_rf3xtg ;
  int ia_phs_rf4xtg ;
  int ia_postgxw1ftg ;
  int ia_rcvrbl ;
  int ia_rcvrbl2 ;
  int ia_rf0 ;
  int ia_rf0cfh ;
  int ia_rf1 ;
  int ia_rf180 ;
  float ia_rf1_temp ;
  int ia_rf1as ;
  int ia_rf1cfh ;
  int ia_rf1cfl ;
  int ia_rf1dtg ;
  int ia_rf1ftg ;
  int ia_rf1htr ;
  int ia_rf1mon ;
  int ia_rf1mps1 ;
  int ia_rf1rs ;
  int ia_rf1tm ;
  int ia_rf1xtg ;
  int ia_rf2cfh ;
  int ia_rf2ftg ;
  int ia_rf2mon ;
  int ia_rf2mps1 ;
  int ia_rf2xtg ;
  int ia_rf3cfh ;
  int ia_rf3ftg ;
  int ia_rf3xtg ;
  int ia_rf4cfh ;
  int ia_rf4xtg ;
  int ia_rf90 ;
  int ia_rfbdtg ;
  int ia_rfbdtg_theta ;
  int ia_rfbrs ;
  int ia_rfbrs_theta ;
  int ia_rfcssat ;
  int ia_rfcssatcfh ;
  int ia_rfcylr ;
  int ia_rfcylrtipup ;
  int ia_rfflp180 ;
  int ia_rfflp180_the ;
  int ia_rfflp90 ;
  int ia_rfflp90_the ;
  int ia_rfflp90r ;
  int ia_rfflp90r_the ;
  int ia_rffrir ;
  int ia_rffs ;
  int ia_rfgir01 ;
  int ia_rfgir02 ;
  int ia_rfmontipup ;
  int ia_rfs5fph ;
  int ia_rfse1 ;
  int ia_rfse2 ;
  int ia_rfse3 ;
  int ia_rfse4 ;
  int ia_rfse5 ;
  int ia_rfse6 ;
  int ia_rfssf ;
  int ia_rfssfh ;
  int ia_rfsx1 ;
  int ia_rfsx2 ;
  int ia_rfsy1 ;
  int ia_rfsy2 ;
  int ia_rfsz1 ;
  int ia_rfsz2 ;
  int ia_rftipup ;
  int ia_sdixon ;
  int ia_sdixon2 ;
  int ia_stgycylra ;
  int ia_stgycylratipup ;
  int ia_stgzcylra ;
  int ia_stgzcylratipup ;
  int ia_thcylr ;
  int ia_thcylrtipup ;
  int ia_thetarf1 ;
  int ia_xdixon ;
  int ia_ydixon ;
  int ia_zdixon ;
  int ideal_debug ;
  int ideal_echo_mode ;
  int ideal_flag ;
  int ideal_max ;
  int ideal_max_im ;
  int ideal_max_locs ;
  int ideal_min ;
  int ideal_min_te ;
  int ideal_necho ;
  int ideal_no_mag_im ;
  int ideal_opt_te ;
  int ideal_pw ;
  int ideal_shift1 ;
  int ideal_shift2 ;
  int ideal_shift3 ;
  int ideal_shift_max ;
  int ideal_te1 ;
  int ideal_te2 ;
  int ideal_te3 ;
  int idealiq_enable_higher_flip ;
  int idealiq_esp ;
  int idealiq_flag ;
  int idealiq_nshots ;
  int idealiq_optfa ;
  int idealiq_pc_dda ;
  int idealiq_pc_dimension ;
  int idealiq_pc_extra_TR ;
  int idealiq_pc_flag ;
  int idealiq_pc_ylines ;
  int idealiq_pc_ylower ;
  int idealiq_pc_yupper ;
  int idealiq_pc_zlines ;
  int idealiq_pc_zlower ;
  int idealiq_pc_zupper ;
  int idealiq_ps_echo ;
  int idealiq_pw ;
  int ifir_dnav_flag ;
  int ifir_dummy_pe ;
  int ifir_flag ;
  int ifir_frir_flag ;
  float ifir_position ;
  int ifir_stir_flag ;
  float ifir_vthick ;
  float ih_idealdbg_cv1 ;
  float ih_idealdbg_cv10 ;
  float ih_idealdbg_cv11 ;
  float ih_idealdbg_cv12 ;
  float ih_idealdbg_cv13 ;
  float ih_idealdbg_cv14 ;
  float ih_idealdbg_cv15 ;
  float ih_idealdbg_cv16 ;
  float ih_idealdbg_cv17 ;
  float ih_idealdbg_cv18 ;
  float ih_idealdbg_cv19 ;
  float ih_idealdbg_cv2 ;
  float ih_idealdbg_cv20 ;
  float ih_idealdbg_cv21 ;
  float ih_idealdbg_cv22 ;
  float ih_idealdbg_cv23 ;
  float ih_idealdbg_cv24 ;
  float ih_idealdbg_cv25 ;
  float ih_idealdbg_cv26 ;
  float ih_idealdbg_cv27 ;
  float ih_idealdbg_cv28 ;
  float ih_idealdbg_cv29 ;
  float ih_idealdbg_cv3 ;
  float ih_idealdbg_cv30 ;
  float ih_idealdbg_cv31 ;
  float ih_idealdbg_cv32 ;
  float ih_idealdbg_cv4 ;
  float ih_idealdbg_cv5 ;
  float ih_idealdbg_cv6 ;
  float ih_idealdbg_cv7 ;
  float ih_idealdbg_cv8 ;
  float ih_idealdbg_cv9 ;
  int ihbsoffsetfreq ;
  int ihbspti ;
  int ihcardt1map_hb_pattern ;
  int ihdixonipte ;
  int ihdixonoopte ;
  int ihdixonte ;
  int iheesp ;
  float ihesp ;
  int ihfcineim ;
  int ihfcinent ;
  float ihflip ;
  float ihinplanexres ;
  float ihinplaneyres ;
  int ihlabeltime ;
  int ihmaxtdelphase ;
  int ihnegscanspacing ;
  int ihnew_series ;
  float ihnex ;
  int ihoffsetfreq ;
  int ihpostlabeldelay ;
  float ihrbwperpix ;
  float ihtagfa ;
  float ihtagor ;
  int ihtdel1 ;
  int ihte1 ;
  int ihte10 ;
  int ihte11 ;
  int ihte12 ;
  int ihte13 ;
  int ihte14 ;
  int ihte15 ;
  int ihte16 ;
  int ihte2 ;
  int ihte3 ;
  int ihte4 ;
  int ihte5 ;
  int ihte6 ;
  int ihte7 ;
  int ihte8 ;
  int ihte9 ;
  int ihti ;
  int ihtr ;
  float ihvbw1 ;
  float ihvbw10 ;
  float ihvbw11 ;
  float ihvbw12 ;
  float ihvbw13 ;
  float ihvbw14 ;
  float ihvbw15 ;
  float ihvbw16 ;
  float ihvbw2 ;
  float ihvbw3 ;
  float ihvbw4 ;
  float ihvbw5 ;
  float ihvbw6 ;
  float ihvbw7 ;
  float ihvbw8 ;
  float ihvbw9 ;
  int imagenum ;
  int imaxectricksview ;
  int init_xtg_deadtime ;
  int initialize_gradOpt ;
  int initialize_scale ;
  int initnewgeo ;
  int inter_necho ;
  int intermittant_chemsat ;
  int intslab_flag ;
  int invertphase ;
  int ipg_trigtest ;
  int ir_seqtime_adjust ;
  int irdisdacqs ;
  int irfreq ;
  float irmsx ;
  float irmsy ;
  float irmsz ;
  int irprep_flag ;
  float irscale ;
  int isi_done ;
  int isi_extra ;
  int isi_extra_gir ;
  int isi_flag ;
  int isi_girdelay ;
  int isi_satdelay ;
  int isi_sliceextra ;
  short int isibit ;
  int iso_delay ;
  float iso_delay_frac ;
  int iso_delay_rfflp90 ;
  int iso_delay_rfflp90r ;
  float jstd_exponent_NV ;
  float jstd_exponent_body ;
  float jstd_multiplier_NV ;
  float jstd_multiplier_body ;
  int k_ideal_pi ;
  int kacq_uid_washin ;
  int kaiser_ramplen ;
  int kband_width ;
  int kernel_regions ;
  int kernel_regions_max ;
  int kernel_regions_min ;
  int killer01_time ;
  int killer02_time ;
  WF_PROCESSOR killer_axis ;
  int krewind_flag ;
  float krfermecorr_factor ;
  int ktarc_flag ;
  int lava_ave_mode ;
  int lava_flag ;
  int linestodiscard ;
  int llimte1 ;
  int llimte2 ;
  int llimte3 ;
  int local_tg ;
  float locposition_rfgir01 ;
  float locposition_rfgir02 ;
  LOG_GRAD loggrd ;
  int look_for_trig ;
  int loopdelay ;
  int loopdelay2 ;
  int lp_mode ;
  float lp_stretch ;
  int lx_pwmtime ;
  int ly_pwmtime ;
  int lz_pwmtime ;
  int mag_create ;
  int mag_mask ;
  int maskPoints ;
  int mask_phase_flag ;
  int mask_regions ;
  int mask_regions_max ;
  int mask_regions_min ;
  int maskv_ftmra_flag ;
  int maxGradRes ;
  float maxSeriesTime ;
  float max_area_gxwex ;
  float max_aspir_fa ;
  int max_avg_time ;
  int max_bamslice ;
  float max_ff_error ;
  int max_navgate_tr ;
  int max_pencodes ;
  int max_regsar ;
  int max_resp_wait ;
  int max_satsar ;
  int max_seqsar ;
  int max_seqsar_orig ;
  int max_seqsar_prepoff ;
  int max_seqsarmon ;
  int max_slicesar_prepoff ;
  int max_slquant ;
  float max_ss_fa ;
  int max_tdel1_time ;
  float maxb1_rf1 ;
  int maxkiller_time ;
  int maxpc_cor ;
  int maxpc_debug ;
  int maxpc_points ;
  int maxx ;
  int maxy ;
  int measured_TG ;
  int medal_autote_flag ;
  int medal_autotelock_flag ;
  int medal_echo_mode ;
  int medal_enh_flag ;
  int medal_etl ;
  int medal_flag ;
  int medal_flexecho_order_flag ;
  float medal_freq_ave ;
  float medal_freq_max ;
  float medal_freq_min ;
  float medal_fw_freq_ave ;
  float medal_fw_freq_llimit ;
  float medal_fw_freq_ulimit ;
  int medal_ip_te ;
  int medal_ip_te_max ;
  int medal_ip_te_min ;
  int medal_ip_te_minus ;
  int medal_ip_te_plus ;
  int medal_k_ip_pi ;
  int medal_k_oop_pi ;
  int medal_max ;
  int medal_max_xres ;
  int medal_min ;
  int medal_multitr_flag ;
  int medal_necho ;
  int medal_oop_te ;
  int medal_oop_te_max ;
  int medal_oop_te_min ;
  int medal_oop_te_minus ;
  int medal_oop_te_plus ;
  int medal_pi_ave ;
  int medal_pi_max ;
  int medal_pi_min ;
  int medal_pw ;
  int medal_shift1 ;
  int medal_shift2 ;
  int medal_shift_max ;
  int medal_te1 ;
  int medal_te1_upper ;
  int medal_te2 ;
  int medal_te2_upper ;
  int merge_defaultTE ;
  float merge_echoIndex ;
  int merge_flag ;
  int merge_min_echoes ;
  int merge_mintr ;
  float merge_satweight ;
  int merge_targetTE ;
  int mild_note_support ;
  int min180te ;
  float min_delay_sec ;
  int min_delay_time ;
  int min_dtgte ;
  int min_end_segment_delay ;
  int min_montr ;
  int min_pencodes ;
  int min_rfampcpblty ;
  int min_rfampcpblty_prepoff ;
  int min_rfavgpow ;
  int min_rfavgpow_prepoff ;
  int min_rfdycc ;
  int min_rfdycc_prepoff ;
  int min_rfrmsb1 ;
  int min_rfrmsb1_prepoff ;
  int min_rste ;
  int min_segment_tr ;
  int min_seq1 ;
  int min_seq2 ;
  int min_seq2_echo2 ;
  int min_seq2_echo3 ;
  int min_seq2_echo4 ;
  int min_seq3 ;
  int min_seqgrad ;
  int min_seqrfamp ;
  int min_seqrfamp_prepoff ;
  int min_seqrfampmon ;
  int min_seqx ;
  int min_seqxz ;
  int min_slquant ;
  int min_specirti ;
  int min_tdel1_fiesta ;
  int min_tdel1_time ;
  int min_tefe ;
  int min_tegy ;
  int min_tegz ;
  int min_tenfe ;
  int min_ti ;
  int min_tseq_irprep ;
  int minimize_RFunblank_time ;
  int minpcflattop ;
  int minph_iso_delay ;
  int minseqbusbar_t ;
  int minseqbusbarmon_t ;
  int minseqcable_maxpow_t ;
  int minseqcable_t ;
  int minseqcableburst_t ;
  int minseqcablemon_t ;
  int minseqchoke_t ;
  int minseqcoil_esp ;
  int minseqcoil_t ;
  int minseqcoilburst_t ;
  int minseqcoilmon_t ;
  int minseqgpm_maxpow_t ;
  int minseqgpm_t ;
  int minseqgram_t ;
  int minseqgrddrv_case_t ;
  int minseqgrddrv_t ;
  int minseqgrddrvmon_t ;
  int minseqgrddrvx_t ;
  int minseqgrddrvxmon_t ;
  int minseqgrddrvy_t ;
  int minseqgrddrvymon_t ;
  int minseqgrddrvz_t ;
  int minseqgrddrvzmon_t ;
  int minseqpwm_x ;
  int minseqpwm_y ;
  int minseqpwm_z ;
  int minseqrf_cal ;
  int mkgspec_epi2_flag ;
  int mkgspec_flag ;
  int mkgspec_x_gmax_flag ;
  int mkgspec_x_sr_flag ;
  int mkgspec_y_gmax_flag ;
  int mkgspec_y_sr_flag ;
  int mkgspec_z_gmax_flag ;
  int mkgspec_z_sr_flag ;
  int mlevon ;
  float mon_acqfov ;
  float mon_angle ;
  int mon_dabdelay ;
  int mon_fcomp ;
  float mon_fov ;
  SCAN_INFO mon_loc ;
  int mon_navgs ;
  int mon_run_setrcvportimm ;
  int mon_ssi_time ;
  int mon_tr ;
  int mon_tr_nav ;
  int mon_tr_wait ;
  int mon_trigger_delay ;
  float mon_vthick ;
  float mon_vthicky ;
  float mon_vthickz ;
  int mon_xres ;
  float monave_sar ;
  float moncave_sar ;
  int monitor_axis ;
  int monitor_page ;
  int monitor_test ;
  float monloc_shift ;
  LOG_GRAD monloggrd ;
  int monnewgeo ;
  int monobl_debug ;
  int monobl_method ;
  float monpeak_sar ;
  PHYS_GRAD monphygrd ;
  float monrot_phi ;
  int monwritectrl ;
  int motsa_ovrhd ;
  int mph_flag ;
  int mps1rf1_inst ;
  float mpsfov ;
  int msde_dda ;
  int msde_flag ;
  float msde_rate ;
  int msde_rfflp180_type ;
  int msde_rfflp90_type ;
  int msde_type ;
  int msde_venc_polarity ;
  int msde_venc_wait_flag ;
  int multiEcho_flag ;
  int multi_channel ;
  float myfreq_off ;
  float myphase_off ;
  float myslice_off ;
  int n_hard180 ;
  int n_omega_hs_rfcssat ;
  int n_omega_ir0 ;
  int n_omega_rffrir ;
  int n_omega_rfgir01 ;
  int n_omega_rfgir02 ;
  int n_omegarf0cfh ;
  int n_rf90 ;
  int n_rfflp180 ;
  int n_rfflp180_the ;
  int n_rfflp90 ;
  int n_rfflp90_the ;
  int n_rfflp90r ;
  int n_rfflp90r_the ;
  int n_rftipup ;
  float nav_1st_factor ;
  int nav_alg ;
  int nav_angle_adj ;
  int nav_avaiRRtime ;
  int nav_channel ;
  int nav_chemdda ;
  int nav_coilsel_index ;
  int nav_coilsel_tr ;
  int nav_dda ;
  int nav_debug_flag ;
  int nav_dir ;
  int nav_dual_mode ;
  int nav_dump_time ;
  int nav_irprep_flag ;
  float nav_last_factor ;
  int nav_linear_ramp_down ;
  int nav_linear_ramp_up ;
  int nav_min_tseq_irprep ;
  int nav_normalization ;
  int nav_nreps ;
  int nav_pause_after_prescan ;
  int nav_prescan_tr ;
  int nav_save_raw_data ;
  int nav_scantime_refresh ;
  int nav_scantime_refresh_pts ;
  int nav_sr ;
  int nav_ss ;
  int nav_test ;
  int nav_time_per_seg ;
  int nav_time_per_yview ;
  int nav_time_per_zsegment ;
  int nav_timing_flag ;
  float nav_tipup_ratio ;
  int nav_tseq_irprep ;
  int nav_type ;
  int nav_wait_flag ;
  float nav_window ;
  int navend_time ;
  int navgate_dda ;
  int navgate_flag ;
  int navgate_target_tr ;
  int navgs ;
  int navigatorCYL_flag ;
  int navigator_flag ;
  int navky_segments ;
  int navky_views_per_segment ;
  int navkz_views_per_segment ;
  int navsat_flag ;
  float navscale ;
  float navseg_weight ;
  int navsegment_dda ;
  float navtrig_factor ;
  int navtrig_flag ;
  int navtrig_target_tr ;
  int navtrig_wait_before_imaging ;
  int navtrig_waittime ;
  float nbw_ssrf ;
  int ncvAdjustedDelay ;
  int ncvGateMaxWait ;
  float negpowerx ;
  float negpowery ;
  float negpowerz ;
  int negx ;
  int negy ;
  int negz ;
  STATUS new_view ;
  int nex ;
  int nex_save ;
  int nflow4D ;
  int nofermi ;
  int nograd ;
  int non_tetime ;
  int non_tetime_mon ;
  float nop ;
  int nope ;
  int noswitch_coil ;
  int noswitch_coil_psc ;
  int noswitch_slab ;
  int noswitch_slab_psc ;
  int nr_of_segA ;
  int nr_of_segments ;
  int nreps ;
  int ns3d_flag ;
  int nseg_per_nav_tr ;
  int nsegments ;
  int num_audibles ;
  int num_autotr_cveval_iter ;
  int num_avg_bline ;
  int num_baseline_pts ;
  int num_dummy_segmentedTR ;
  int num_filter_slots ;
  int num_images ;
  int num_mask_regions ;
  int num_outer_loops ;
  int num_regions ;
  int num_rf1lobe ;
  int num_rfflp180 ;
  int num_sats ;
  int num_shot ;
  int num_slice_rr ;
  int num_sub_regions ;
  int num_throwaways ;
  float num_transition_fraction ;
  int num_views_per_nav_tr ;
  int num_virchan ;
  int numpts2pass ;
  int numrecv ;
  int numsatramp ;
  int obl_debug ;
  int obl_method ;
  int oblique_monplane ;
  int oblmethod_dbdt_flag ;
  int oddnex_npw ;
  int oeff ;
  int oepf ;
  int off90 ;
  int off90as ;
  int off90minor ;
  int off_gzvlw ;
  int off_hard180 ;
  int off_omega_hs_rfcssat ;
  int off_omega_ir0 ;
  int off_omega_rffrir ;
  int off_omega_rfgir01 ;
  int off_omega_rfgir02 ;
  int off_omegarf0cfh ;
  int off_rf0 ;
  int off_rf0cfh ;
  int off_rf1 ;
  int off_rf1as ;
  int off_rf1cfh ;
  int off_rf1cfl ;
  int off_rf1ftg ;
  int off_rf1mon ;
  int off_rf1mps1 ;
  int off_rf1tm ;
  int off_rf1xtg ;
  int off_rf2cfh ;
  int off_rf2ftg ;
  int off_rf2mon ;
  int off_rf2mps1 ;
  int off_rf2xtg ;
  int off_rf3cfh ;
  int off_rf3ftg ;
  int off_rf3xtg ;
  int off_rf4cfh ;
  int off_rf4xtg ;
  int off_rf90 ;
  int off_rfcssat ;
  int off_rfflp180 ;
  int off_rfflp180_the ;
  int off_rfflp90 ;
  int off_rfflp90_the ;
  int off_rfflp90r ;
  int off_rfflp90r_the ;
  int off_rffrir ;
  int off_rffs ;
  int off_rfgir01 ;
  int off_rfgir02 ;
  int off_rfmontipup ;
  int off_rfs5fph ;
  int off_rfse1 ;
  int off_rfse2 ;
  int off_rfse3 ;
  int off_rfse4 ;
  int off_rfse5 ;
  int off_rfse6 ;
  int off_rfssf ;
  int off_rfssfh ;
  int off_rfsx1 ;
  int off_rfsx2 ;
  int off_rfsy1 ;
  int off_rfsy2 ;
  int off_rfsz1 ;
  int off_rfsz2 ;
  int off_rftipup ;
  int off_thetarf1 ;
  int offset ;
  int offset_rfgir01 ;
  int offset_rfgir02 ;
  float ogsfMax ;
  float ogsfMin ;
  float ogsfX1 ;
  float ogsfX2 ;
  float ogsfX2_limit_Min ;
  float ogsfXw ;
  float ogsfXwex ;
  float ogsfY ;
  float ogsfYk ;
  float ogsfZ ;
  float ogsfZk ;
  float ogsf_limit_Max ;
  float ogsf_limit_Min ;
  int old_phase ;
  float omega_amp ;
  float omega_scale ;
  int op3dcine_fiesta ;
  int op3dcine_spgr ;
  int op3dgradwarp ;
  int op4dflow ;
  int opET ;
  int opab1 ;
  float opaccel_cs_stride ;
  int opaccel_kt_stride ;
  int opaccel_mb_stride ;
  float opaccel_ph_stride ;
  float opaccel_sl_stride ;
  float opaccel_t_stride ;
  int opacqo ;
  int opacs ;
  int opadvgate ;
  int opallowedrescantime ;
  int opanatomy ;
  int opapa ;
  float opapcsiis ;
  int opapflow ;
  int opaphases ;
  int oparc ;
  int oparr ;
  int oparrmon ;
  int opascalcfov ;
  int opasl ;
  int opaslprep ;
  int opasset ;
  int opassetcal ;
  int opassetscan ;
  int opauto3dgradwarp ;
  int opautobti ;
  int opautodifnext2 ;
  int opautodifnumt2 ;
  int opautoetl ;
  int opautoflip ;
  int opautonecho ;
  int opautonex ;
  int opautonumbvals ;
  int opautorbw ;
  int opautosldelay ;
  int opautoslquant ;
  int opautosubtract ;
  int opautotdel1 ;
  int opautote ;
  int opautoti ;
  int opautotissuet1 ;
  int opautotr ;
  int opautovps ;
  int opaxial_slice ;
  int opbc ;
  int opbilateral ;
  int opblim ;
  int opbrava ;
  int opbravo ;
  int opbreastmrs ;
  int opbreathhold ;
  int opbsp ;
  int opbspti ;
  int opburstmode ;
  int opbval ;
  int opbwrt ;
  int opcaldelay ;
  int opcalmode ;
  int opcalrequired ;
  int opcardseq ;
  int opccsat ;
  int opcfsel ;
  int opcgate ;
  int opcgatetype ;
  int opchrate ;
  int opcineir ;
  int opclocs ;
  int opcmon ;
  int opcoax ;
  int opcollapse ;
  int opcompressedsensing ;
  int opcontrast ;
  int opcoronal_slice ;
  int opcosmic ;
  int opcphases ;
  int opcs ;
  int opcube ;
  int opdda ;
  int opdeprep ;
  int opdfax3in1 ;
  int opdfaxall ;
  int opdfaxtetra ;
  int opdfaxx ;
  int opdfaxy ;
  int opdfaxz ;
  int opdfm ;
  int opdfmprescan ;
  float opdfsathick1 ;
  float opdfsathick2 ;
  float opdfsathick3 ;
  float opdfsathick4 ;
  float opdfsathick5 ;
  float opdfsathick6 ;
  int opdiffuse ;
  float opdifnext2 ;
  int opdifnumbvalues ;
  int opdifnumdirs ;
  int opdifnumt2 ;
  int opdifproctype ;
  int opdisco ;
  int opdixon ;
  int opdixproc ;
  float opdose ;
  int opdoubleir ;
  int opdrivemode ;
  int opdualspinecho ;
  int opdynaplan ;
  int opdynaplan_mask_phase ;
  int opdynaplan_nphases ;
  int opdyntg ;
  int opectricks ;
  int opentry ;
  int opepi ;
  int opetl ;
  int opexamnum ;
  int opexcitemode ;
  int opexor ;
  float opexsathick1 ;
  float opexsathick2 ;
  float opexsathick3 ;
  float opexsathick4 ;
  float opexsathick5 ;
  float opexsathick6 ;
  int opexsatlen1 ;
  int opexsatlen2 ;
  int opexsatlen3 ;
  int opexsatlen4 ;
  int opexsatlen5 ;
  int opexsatlen6 ;
  float opexsatloc1 ;
  float opexsatloc2 ;
  float opexsatloc3 ;
  float opexsatloc4 ;
  float opexsatloc5 ;
  float opexsatloc6 ;
  int opexsatmask ;
  int opexsatoff1 ;
  int opexsatoff2 ;
  int opexsatoff3 ;
  int opexsatoff4 ;
  int opexsatoff5 ;
  int opexsatoff6 ;
  int opexsatparal ;
  int opfMRIPDTYPE ;
  int opfast ;
  int opfat ;
  int opfatcl ;
  int opfatwater ;
  int opfcaxis ;
  int opfcine ;
  int opfcomp ;
  int opflair ;
  int opflaxall ;
  int opflaxx ;
  int opflaxxa ;
  int opflaxy ;
  int opflaxya ;
  int opflaxz ;
  int opflaxza ;
  float opflip ;
  int opflrecon ;
  int opfluorotrigger ;
  int opfmri ;
  float opfov ;
  int opfphases ;
  int opfr ;
  float opfreqfov ;
  int opfulltrain ;
  int opfus ;
  int opgirmode ;
  int opgradmode ;
  int opgrx ;
  int opgrxroi ;
  int opharmonize ;
  int opheadscout ;
  int ophoecc ;
  int ophrate ;
  int ophrep ;
  int ophydro ;
  int opidealiq ;
  int opileave ;
  int opimode ;
  int opinhance ;
  int opinhsflow ;
  int opinit_state ;
  float opinittrigdelay ;
  int opinrangetr ;
  int opinrangetrmax ;
  int opinrangetrmin ;
  int opirmode ;
  int opirprep ;
  int opjrmode ;
  int oplandmark ;
  int oplava ;
  float oplenap ;
  float oplenrl ;
  float oplensi ;
  int oploadprotocol ;
  float oplocap ;
  float oplocrl ;
  float oplocsi ;
  int opmagc ;
  int opmagic ;
  int opmart ;
  int opmask ;
  int opmavric ;
  int opmb ;
  int opmedal ;
  int opmer2 ;
  int opmerge ;
  int opmintedif ;
  float opmonfov ;
  float opmonthick ;
  int opmph ;
  int opmphases ;
  int opmprage ;
  int opmsde ;
  int opmsdeaxx ;
  int opmsdeaxy ;
  int opmsdeaxz ;
  int opmt ;
  int opmultistation ;
  int opnav ;
  float opnavaccwin ;
  int opnavautoaccwin ;
  int opnavautotrigtime ;
  int opnavmaxinterval ;
  int opnavpscpause ;
  int opnavpsctime ;
  int opnavrrmeas ;
  int opnavrrmeasrr ;
  int opnavrrmeastime ;
  int opnavsigenhance ;
  int opnavsltrack ;
  int opnavtype ;
  int opnbh ;
  int opncoils ;
  int opnecho ;
  int opnewgeo ;
  float opnex ;
  int opnnex ;
  int opnopwrap ;
  int opnostations ;
  int opnrr ;
  int opnrr_dda ;
  int opnseg ;
  int opnshots ;
  int opnspokes ;
  int opnumbvals ;
  int opnumgir ;
  int opnumgroups ;
  int opnumsynbvals ;
  int opobplane ;
  float opoversamplingfactor ;
  int opovl ;
  int oppdgm_str ;
  int opphasecycle ;
  float opphasefov ;
  int opphaseimage ;
  int opphases ;
  int opphcor ;
  int opphsen ;
  int opphysplane ;
  int opplane ;
  int oppomp ;
  int oppos ;
  float oppostlabeldelay ;
  int opprescanopt ;
  int opproject ;
  int oppromo ;
  int opprop ;
  int opprotRxMode ;
  int oppscapa ;
  int oppscshimtg ;
  int oppscvquant ;
  int oppsd_trig ;
  int oppseq ;
  int opptsize ;
  int oppure ;
  int oppurecal ;
  int opquickstep ;
  int oprampdir ;
  float oprbw ;
  float oprbw2 ;
  int oprealtime ;
  int oprect ;
  int oprep_active ;
  int oprep_rest ;
  int opresearch ;
  int oprgcalmode ;
  float oprlcsiis ;
  int oprlflow ;
  int oprtarr ;
  int oprtb0 ;
  int oprtbc ;
  int oprtcardseq ;
  int oprtcgate ;
  int oprtpoint ;
  int oprtrate ;
  int oprtrep ;
  int oprttdel1 ;
  int oprttseq ;
  int opsagittal_slice ;
  int opsarburst ;
  int opsarmode ;
  int opsat ;
  int opsatmask ;
  int opsatx ;
  float opsatxloc1 ;
  float opsatxloc2 ;
  float opsatxthick ;
  int opsaty ;
  float opsatyloc1 ;
  float opsatyloc2 ;
  float opsatythick ;
  int opsatz ;
  float opsatzloc1 ;
  float opsatzloc2 ;
  float opsatzthick ;
  int opsavedf ;
  int opscic ;
  int opseparatesynb ;
  int opsepseries ;
  int opseriesnum ;
  int opseriessave ;
  float opsicsiis ;
  int opsiflow ;
  int opsilent ;
  int opsilentlevel ;
  int opsilentmr ;
  int opslblank ;
  int opsldelay ;
  int opslice_order ;
  int opslicecnt ;
  int opslinky ;
  int opsllocs ;
  int opslquant ;
  float opslspace ;
  float opslthick ;
  int opslzip2 ;
  int opslzip4 ;
  int opsmartprep ;
  int opspecir ;
  int opspf ;
  int opspiral ;
  int opsquare ;
  int opsrprep ;
  int opssfse ;
  int opssrf ;
  int opstation ;
  int opstress ;
  int opswan ;
  int opswift ;
  int opt1flair ;
  int opt1map ;
  int opt2flair ;
  int opt2map ;
  int opt2prep ;
  int opt2prepte ;
  int optabent ;
  float optagangle ;
  int optagging ;
  int optagspc ;
  int optdel1 ;
  int opte ;
  int opte2 ;
  int optefw ;
  int optensor ;
  int opti ;
  int optimal_channel_combine ;
  int optissuet1 ;
  int optlabel ;
  int optlrdrf ;
  int optouch ;
  int optouchamp ;
  int optouchax ;
  int optouchcyc ;
  int optouchfreq ;
  int optouchmegfreq ;
  int optouchtphases ;
  int optphases ;
  int optr ;
  int optracq ;
  int optrecovery ;
  int optricksdel ;
  int optrickspause ;
  int optrip ;
  int optseq ;
  float opuser0 ;
  float opuser1 ;
  float opuser10 ;
  float opuser11 ;
  float opuser12 ;
  float opuser13 ;
  float opuser14 ;
  float opuser15 ;
  float opuser16 ;
  float opuser17 ;
  float opuser18 ;
  float opuser19 ;
  float opuser2 ;
  float opuser20 ;
  float opuser21 ;
  float opuser22 ;
  float opuser23 ;
  float opuser24 ;
  float opuser25 ;
  float opuser26 ;
  float opuser27 ;
  float opuser28 ;
  float opuser29 ;
  float opuser3 ;
  float opuser30 ;
  float opuser31 ;
  float opuser32 ;
  float opuser33 ;
  float opuser34 ;
  float opuser35 ;
  float opuser36 ;
  float opuser37 ;
  float opuser38 ;
  float opuser39 ;
  float opuser4 ;
  float opuser40 ;
  float opuser41 ;
  float opuser42 ;
  float opuser43 ;
  float opuser44 ;
  float opuser45 ;
  float opuser46 ;
  float opuser47 ;
  float opuser48 ;
  float opuser5 ;
  float opuser6 ;
  float opuser7 ;
  float opuser8 ;
  float opuser9 ;
  int opuser_usage_tag ;
  int opvbw ;
  float opvenc ;
  int opvenous ;
  float opvest ;
  int opvibrant ;
  int opview_order ;
  int opvps ;
  int opvquant ;
  int opvrg ;
  int opvsphases ;
  float opvthick ;
  int opwarmup ;
  int opwater ;
  float opweight ;
  int opxres ;
  int opyres ;
  int opzip1024 ;
  int opzip512 ;
  int opzoom_coil_ind ;
  float opzoom_dist_ax ;
  float opzoom_dist_cor ;
  float opzoom_dist_sag ;
  float opzoom_fov_xy ;
  float opzoom_fov_z ;
  int osfpR_flag ;
  int osfp_dda ;
  int osfp_debug ;
  float osfp_delay_factor ;
  int osfp_flag ;
  float osfp_weight ;
  float osfp_weight_act ;
  float osfp_weight_grad ;
  int osfpsd_flag ;
  int override_opcalrequired ;
  int pass_thru_mode ;
  int passtime ;
  int pause_after_mask_flag ;
  float pc_const ;
  int pc_mode ;
  int pcfiesta_flag ;
  int pcfiesta_rf ;
  int pe_acq1 ;
  int pe_acq2 ;
  int pe_on ;
  int peakPhaseIndex ;
  int per_gx1 ;
  int per_gy1 ;
  int per_gy1r ;
  int per_gzcomb ;
  int per_gzcombhtr ;
  int per_gzp ;
  int per_gzphtr ;
  int per_gzvlw ;
  int pfkr_flag ;
  float pfkr_fraction ;
  float pfkr_fraction_act ;
  int pfkr_yz_enable ;
  int pfkr_yz_flag ;
  float pfky_fraction ;
  int pfky_total_unaccel ;
  int pfkyz2kr_flag ;
  int pfkz_flag ;
  float pfkz_fraction ;
  float pfkz_fraction_min ;
  int pfkz_hnover ;
  int pfkz_reverse_seq ;
  int pfkz_segments ;
  int pfkz_total ;
  int pfkz_total_unaccel ;
  int pfkz_views_per_segment ;
  int pfkz_vps_max ;
  float pg_beta ;
  int pgen_for_dbdt_opt ;
  int phase_col ;
  int phase_cor ;
  int phase_cycles ;
  int phase_order ;
  int phase_rfflp180 ;
  int phasefovgt1_flag ;
  int phaseres ;
  int phmask ;
  int phorder ;
  PHYS_GRAD phygrd ;
  int phys_rec_resolution ;
  int phys_record_channelsel ;
  int phys_record_flag ;
  int pi1stshimb ;
  int pi2dmde ;
  int pi3dgradwarpnub ;
  int pi_neg_sp ;
  int pi_piphasfovnub ;
  float piaccel_cs_step ;
  float piaccel_cs_stride ;
  int piaccel_csedit ;
  int piaccel_csnub ;
  float piaccel_csval2 ;
  float piaccel_csval3 ;
  float piaccel_csval4 ;
  float piaccel_csval5 ;
  float piaccel_csval6 ;
  int piaccel_kt_step ;
  int piaccel_kt_stride ;
  int piaccel_ktedit ;
  int piaccel_ktnub ;
  int piaccel_ktval2 ;
  int piaccel_ktval3 ;
  int piaccel_ktval4 ;
  int piaccel_ktval5 ;
  int piaccel_ktval6 ;
  int piaccel_mb_step ;
  int piaccel_mb_stride ;
  int piaccel_mbedit ;
  int piaccel_mbnub ;
  int piaccel_mbval2 ;
  int piaccel_mbval3 ;
  int piaccel_mbval4 ;
  int piaccel_mbval5 ;
  int piaccel_mbval6 ;
  float piaccel_ph_step ;
  float piaccel_ph_stride ;
  int piaccel_phedit ;
  int piaccel_phnub ;
  float piaccel_phval2 ;
  float piaccel_phval3 ;
  float piaccel_phval4 ;
  float piaccel_phval5 ;
  float piaccel_phval6 ;
  float piaccel_sl_step ;
  float piaccel_sl_stride ;
  int piaccel_sledit ;
  int piaccel_slnub ;
  float piaccel_slval2 ;
  float piaccel_slval3 ;
  float piaccel_slval4 ;
  float piaccel_slval5 ;
  float piaccel_slval6 ;
  float piaccel_t_step ;
  float piaccel_t_stride ;
  int piaccel_tedit ;
  int piaccel_tnub ;
  float piaccel_total_stride ;
  float piaccel_tval2 ;
  float piaccel_tval3 ;
  float piaccel_tval4 ;
  float piaccel_tval5 ;
  float piaccel_tval6 ;
  int piaccelscrn ;
  int piacqnub ;
  int piacsdefval ;
  int piacsnub ;
  int piacsval2 ;
  int piacsval3 ;
  int piacsval4 ;
  int piacsval5 ;
  int piacsval6 ;
  int piactim ;
  int piaddinub ;
  int piaddscannub ;
  int piaddscantype ;
  int piadvise ;
  int piadvt2map ;
  int piait ;
  int piallowedrescantimenub ;
  int piamnub ;
  int piapcsi ;
  int piaphasdefval ;
  int piaphasenub ;
  int piaphaseval2 ;
  int piaphaseval3 ;
  int piaphaseval4 ;
  int piapx ;
  int piapxprfacc ;
  int piapxprfres ;
  int piapxprfstepnub ;
  int piapxprfstepval1 ;
  int piapxprfstepval2 ;
  int piarccoilrestrict ;
  float piasar ;
  int piassetoverride ;
  int piassetscrn ;
  int piautobspti ;
  int piautoetl ;
  int piautofa ;
  int piautoirbands ;
  int piautonavtracker ;
  int piautopause ;
  int piautophasenub ;
  int piautostep ;
  int piautoti ;
  int piautotrmode ;
  int piautovoice ;
  float pib1rms ;
  int pibbandfilt ;
  int pibreathholdnub ;
  int pibsptidefval ;
  int pibsptinub ;
  int pibsptival2 ;
  int pibsptival3 ;
  int pibsptival4 ;
  int pibsptival5 ;
  int pibsptival6 ;
  float piburstcooltime ;
  int piburstmode ;
  int pibval2 ;
  int pibval3 ;
  int pibval4 ;
  int pibvalstab ;
  int pibvnub ;
  int picalmode ;
  int picalmodenub ;
  float picasar ;
  int piccsat_obl ;
  int piccsatnub ;
  int pichemsatopt ;
  int pichop ;
  int picineiprot ;
  int piclckcnt ;
  int picoilfastswitchrequired ;
  int picontrastwarning ;
  int pics ;
  int picsifov ;
  int picsimode ;
  float pidbdtper ;
  float pidbdtts ;
  int piddanub ;
  int pidefaddimg ;
  int pidefallowedrescantime ;
  int pidefarr ;
  int pidefbval ;
  int pidefcaldelay ;
  int pidefexcitemode ;
  int pideffcaxis ;
  int pidefflax ;
  int pidefflrc ;
  int pidefnavaccwin ;
  int pidefnavautoaccwin ;
  int pidefnavautotrigtime ;
  int pidefnavmaxinterval ;
  int pidefnavpscpause ;
  int pidefnavpsctime ;
  int pidefnavrrmeas ;
  int pidefnavrrmeastime ;
  int pidefnavsigenhance ;
  int pidefnavsltrack ;
  int pidefnavtype ;
  int pidefnbh ;
  int pidefovl ;
  float pidefphasset ;
  float pidefpostlabeldelay ;
  int pidefproj ;
  int pideframp ;
  float pidefrbw ;
  int pidefrtrep ;
  float pidefslasset ;
  int pidefslq ;
  int pideftouchamp ;
  int pideftouchax ;
  int pideftouchcyc ;
  int pideftouchfreq ;
  int pideftouchmegfreq ;
  int pideftouchtphases ;
  float pidfmonfov ;
  float pidfmonthick ;
  int pidiatdel1 ;
  float pidifavgnex ;
  int pidifaxnub ;
  int pidiffmode ;
  int pidiffproctype ;
  int pidifnext2nub ;
  float pidifnext2val2 ;
  float pidifnext2val3 ;
  float pidifnext2val4 ;
  float pidifnext2val5 ;
  float pidifnext2val6 ;
  int pidifnextab ;
  int pidifnumdirsdefval ;
  int pidifnumdirsnub ;
  int pidifnumdirsval2 ;
  int pidifnumdirsval3 ;
  int pidifnumdirsval4 ;
  int pidifnumt2defval ;
  int pidifnumt2nub ;
  int pidifnumt2val2 ;
  int pidifnumt2val3 ;
  int pidifnumt2val4 ;
  int pidifpage ;
  int pidifrecnub ;
  int pidixproc ;
  int pidltime ;
  int pidmode ;
  int pidoshim ;
  int pidotg ;
  int pidrivemodenub ;
  int pidualspinechonub ;
  int pidyntgnub ;
  int piechdefval ;
  int piechnub ;
  int piechval2 ;
  int piechval3 ;
  int piechval4 ;
  int piechval5 ;
  int piechval6 ;
  int pieffbladewidth ;
  int pieffbladewidthdefval ;
  int pieffbladewidthnub ;
  float piesar ;
  int piesp ;
  int pietlnub ;
  int pietlval2 ;
  int pietlval3 ;
  int pietlval4 ;
  int pietlval5 ;
  int pietlval6 ;
  int pietr ;
  int piexcitemodenub ;
  int pifamode ;
  int pifanub ;
  int pifaval2 ;
  int pifaval3 ;
  int pifaval4 ;
  int pifaval5 ;
  int pifaval6 ;
  int pifcinedefval ;
  int pifcinenub ;
  int pifcineval2 ;
  int pifcineval3 ;
  int pifcineval4 ;
  int pifilt4 ;
  int pifilt5 ;
  int pifilt6 ;
  int pifilt7 ;
  int piflanub ;
  int piflosup ;
  int piflrcnub ;
  int pifmriscrn ;
  int piforkvrgf ;
  int pifovnub ;
  float pifovval2 ;
  float pifovval3 ;
  float pifovval4 ;
  float pifovval5 ;
  float pifovval6 ;
  int pifphasenub ;
  int pifphaseval2 ;
  int pifphaseval3 ;
  int pifphaseval4 ;
  int pifphaseval5 ;
  int pifphaseval6 ;
  float pifractecho ;
  float piframerate ;
  int piframeratenub ;
  int pifreqfovnub ;
  int pifsefcnub ;
  int pigeosrot ;
  float pigirdefthick ;
  int pigirmode ;
  int pigirscrn ;
  int pigradcoil ;
  int piharmonizenub ;
  int pihoeccnub ;
  int pihoeccvis ;
  int pihrepnub ;
  int pihrepval2 ;
  int pihrepval3 ;
  int pihrepval4 ;
  int pihrepval5 ;
  int pihrepval6 ;
  float pihsar ;
  int piimages ;
  int piimgoptlist ;
  int piimgoptval2 ;
  int piimgoptval3 ;
  int piimgoptval4 ;
  int piinitstatnub ;
  int piinplaneres ;
  int piinrangetrmax ;
  int piinrangetrmin ;
  int piinvertfnub ;
  int piinvertfvis ;
  int piisil ;
  int piisnub ;
  float piisval2 ;
  float piisval3 ;
  float piisval4 ;
  float piisval5 ;
  float piisval6 ;
  float piisvaldef ;
  int pikt ;
  float pilandmark ;
  int pilocnub ;
  int pilocval2 ;
  int pilocval3 ;
  int pilocval4 ;
  int pilocval5 ;
  int pilocval6 ;
  int pimb ;
  int pimintedifdef ;
  int pimintedifnub ;
  int pimixtime ;
  int pimonfovnub ;
  float pimonfovval2 ;
  float pimonfovval3 ;
  float pimonfovval4 ;
  int pimonitor ;
  int pimonthicknub ;
  float pimonthickval2 ;
  float pimonthickval3 ;
  float pimonthickval4 ;
  int pimphscrn ;
  int pimrsaps1 ;
  int pimrsaps10 ;
  int pimrsaps11 ;
  int pimrsaps12 ;
  int pimrsaps13 ;
  int pimrsaps14 ;
  int pimrsaps15 ;
  int pimrsaps2 ;
  int pimrsaps3 ;
  int pimrsaps4 ;
  int pimrsaps5 ;
  int pimrsaps6 ;
  int pimrsaps7 ;
  int pimrsaps8 ;
  int pimrsaps9 ;
  int pimrsapsflg ;
  float pimscan ;
  int pimsdeaxnub ;
  int pimultigroup ;
  int pimultislab ;
  int pimultistation ;
  int pinavaccwinnub ;
  int pinavaccwinval2 ;
  int pinavaccwinval3 ;
  int pinavaccwinval4 ;
  int pinavautoaccwinnub ;
  int pinavautotrigtimenub ;
  int pinavautotrigtimeval2 ;
  int pinavautotrigtimeval3 ;
  int pinavautotrigtimeval4 ;
  int pinavmaxintervalnub ;
  int pinavmaxintervalval2 ;
  int pinavmaxintervalval3 ;
  int pinavmaxintervalval4 ;
  float pinavmaxrr ;
  int pinavpscpausenub ;
  int pinavpsctimenub ;
  int pinavpsctimeval2 ;
  int pinavpsctimeval3 ;
  int pinavpsctimeval4 ;
  int pinavrradjust ;
  int pinavrrmeasmaxsl ;
  int pinavrrmeasnub ;
  int pinavrrmeasrtrep ;
  int pinavrrmeastimenub ;
  int pinavrrmeastimeval2 ;
  int pinavrrmeastimeval3 ;
  int pinavrrmeastimeval4 ;
  int pinavsigenhancenub ;
  int pinavsltracknub ;
  int pinavtypenub ;
  int pinbh ;
  int pinbhnub ;
  int pinecho ;
  int pinex ;
  int pinexnub ;
  float pinexval2 ;
  float pinexval3 ;
  float pinexval4 ;
  float pinexval5 ;
  float pinexval6 ;
  int pinoadc ;
  int pinofreqoffset ;
  int pinolr ;
  int pinsegnub ;
  int pinsegval2 ;
  int pinsegval3 ;
  int pinsegval4 ;
  int pinsegval5 ;
  int pinslices ;
  int pinspokesdefval ;
  int pinspokesnub ;
  int pinspokesstep ;
  int pinspokesval2 ;
  int pinspokesval3 ;
  int pinspokesval4 ;
  int pinspokesval5 ;
  int pinspokesval6 ;
  int pinumartlevels ;
  int pinumbnub ;
  int pinumbval2 ;
  int pinumbval3 ;
  int pinumbval4 ;
  int pinumbval5 ;
  int pinumbval6 ;
  int pinumgir ;
  int pinumsynbnub ;
  int pinumsynbval2 ;
  int pinumsynbval3 ;
  int pinumsynbval4 ;
  int pinumsynbval5 ;
  int pinumsynbval6 ;
  int pioverlap ;
  float pioversamplingfactordefval ;
  int pioversamplingfactornub ;
  float pioversamplingfactorval2 ;
  float pioversamplingfactorval3 ;
  float pioversamplingfactorval4 ;
  float pioversamplingfactorval5 ;
  float pioversamplingfactorval6 ;
  int piovlnub ;
  int pipaunub ;
  int pipautype ;
  int pipauval2 ;
  int pipauval3 ;
  int pipauval4 ;
  int pipauval5 ;
  int pipauval6 ;
  int pipctovl ;
  int pipdhs_active ;
  int piphaseimagenub ;
  int piphaseimageval2 ;
  int piphaseimageval3 ;
  int piphaseimageval4 ;
  int piphasenub ;
  int piphasfovnub ;
  int piphasfovnub2 ;
  float piphasfovval1 ;
  float piphasfovval2 ;
  float piphasfovval3 ;
  float piphasfovval4 ;
  float piphasfovval5 ;
  float piphasfovval6 ;
  int piphassetnub ;
  float piphassetval1 ;
  float piphassetval2 ;
  float piphassetval3 ;
  float piphassetval4 ;
  int piphslnub ;
  float pipostlabeldelay2 ;
  float pipostlabeldelay3 ;
  float pipostlabeldelay4 ;
  float pipostlabeldelay5 ;
  float pipostlabeldelay6 ;
  int pipostlabeldelaynub ;
  int piprojnub ;
  float pipsar ;
  int pipscdef ;
  int pipscoptnub ;
  int pipscshimtgnub ;
  int pipscvol ;
  int pipsdtrignub ;
  int pipure ;
  int pirampnub ;
  int pirbwpage ;
  int pirbwperpix ;
  int pircb2nub ;
  float pircb2val2 ;
  float pircb2val3 ;
  float pircb2val4 ;
  float pircb2val5 ;
  float pircb2val6 ;
  int pircbnub ;
  float pircbval2 ;
  float pircbval3 ;
  float pircbval4 ;
  float pircbval5 ;
  float pircbval6 ;
  float pireconlag ;
  int pirepactivenub ;
  int pireprestnub ;
  int piresol ;
  int pirlcsi ;
  int piroigrx ;
  int pirtait ;
  int pirtb0nub ;
  int pirtb0vis ;
  int pirtetr ;
  int pirtpointnub ;
  int pirtpointval2 ;
  int pirtpointval3 ;
  int pirtpointval4 ;
  int pirtpointval5 ;
  int pirtpointval6 ;
  int pirtratenub ;
  int pirtrepnub ;
  int pirtrepval2 ;
  int pirtrepval3 ;
  int pirtrepval4 ;
  int pirtrepval5 ;
  int pirtrepval6 ;
  int pirtrigwinnub ;
  int pirtseqnub ;
  int pirttseq ;
  int pirtwindefval ;
  int pirtwinval2 ;
  int pirtwinval3 ;
  int pirtwinval4 ;
  int pirtwinval5 ;
  int pirtwinval6 ;
  int pisatnub ;
  int pisatthick ;
  int pisatthickx ;
  int pisatthicky ;
  int pisatthickz ;
  int pisaveinter ;
  float piscan_distance_toh ;
  float piscancenter ;
  int piscran ;
  int pisctim ;
  float pisctim1 ;
  float pisctim2 ;
  float pisctim3 ;
  float pisctim4 ;
  float pisctim5 ;
  float pisctim6 ;
  int piseparatesynbnub ;
  int piserperph ;
  int pisetup ;
  int pishim2 ;
  int pishldctrl ;
  int pishotnub ;
  int pishotval2 ;
  int pishotval3 ;
  int pishotval4 ;
  int pishotval5 ;
  int pishotval6 ;
  int pisicsi ;
  int pisilentmr ;
  int pisioverlap ;
  int pislassetnub ;
  float pislassetval1 ;
  float pislassetval2 ;
  float pislassetval3 ;
  float pislassetval4 ;
  int pislblank ;
  int pisldelnub ;
  int pisldelval3 ;
  int pisldelval4 ;
  int pisldelval5 ;
  int pisldelval6 ;
  int pisliceordnub ;
  int pislqnub ;
  int pislquant ;
  int pislqval2 ;
  int pislqval3 ;
  int pislqval4 ;
  int pislqval5 ;
  int pislthicklabel ;
  float pislthickstep ;
  int pismode ;
  int pispecprescan ;
  int pispssupnub ;
  int pistnub ;
  float pistval2 ;
  float pistval3 ;
  float pistval4 ;
  float pistval5 ;
  float pistval6 ;
  int pisupnub ;
  int piswapfc ;
  int pisynbvalstab ;
  int pisystdel1 ;
  int pit2preptedefval ;
  int pit2preptenub ;
  int pit2prepteval2 ;
  int pit2prepteval3 ;
  int pit2prepteval4 ;
  int pit2prepteval5 ;
  int pit2prepteval6 ;
  int pitablemaxaccel ;
  int pitablemaxdecel ;
  int pitablemaxspeed ;
  float pitableposition ;
  float pitagangledefval ;
  int pitaganglenub ;
  float pitagangleval2 ;
  float pitagangleval3 ;
  float pitagangleval4 ;
  float pitagangleval5 ;
  float pitagangleval6 ;
  int pitagging ;
  int pitagspcdefval ;
  int pitagspcval2 ;
  int pitagspcval3 ;
  int pitagspcval4 ;
  float pitbh ;
  float pitbhlast ;
  int pitdel1 ;
  int pitdel1nub ;
  int pitdel1type ;
  int pite1nub ;
  int pite1val2 ;
  int pite1val3 ;
  int pite1val4 ;
  int pite1val5 ;
  int pite1val6 ;
  int pite2nub ;
  int pite2type ;
  int pite2val2 ;
  int pite2val3 ;
  int pite2val4 ;
  int pite2val5 ;
  int pite2val6 ;
  int pitetr ;
  int pitetype ;
  int pitfeextra ;
  int pitidefval ;
  int pitinub ;
  int pitissuet1defval ;
  int pitissuet1nub ;
  int pitissuet1val2 ;
  int pitissuet1val3 ;
  int pitissuet1val4 ;
  int pitissuet1val5 ;
  int pititle ;
  int pititype ;
  int pitival2 ;
  int pitival3 ;
  int pitival4 ;
  int pitival5 ;
  int pitival6 ;
  int pitlabeldefval ;
  int pitlabelnub ;
  int pitlabelstep ;
  int pitlabelval2 ;
  int pitlabelval3 ;
  int pitlabelval4 ;
  int pitouch ;
  int pitouchamp ;
  int pitouchampnub ;
  int pitouchampval2 ;
  int pitouchampval3 ;
  int pitouchampval4 ;
  int pitouchaxnub ;
  int pitouchaxval2 ;
  int pitouchaxval3 ;
  int pitouchaxval4 ;
  int pitouchaxval5 ;
  int pitouchcyc ;
  int pitouchcycnub ;
  int pitouchcycval2 ;
  int pitouchcycval3 ;
  int pitouchcycval4 ;
  int pitouchfreq ;
  int pitouchfreqnub ;
  int pitouchfreqval2 ;
  int pitouchfreqval3 ;
  int pitouchfreqval4 ;
  int pitouchmegfreqnub ;
  int pitouchmegfreqval2 ;
  int pitouchmegfreqval3 ;
  int pitouchmegfreqval4 ;
  float pitouchmenc ;
  int pitouchtphases ;
  int pitouchtphasesnub ;
  int pitouchtphasesval2 ;
  int pitouchtphasesval3 ;
  int pitouchtphasesval4 ;
  int pitphasenub ;
  int pitphaseval2 ;
  int pitphaseval3 ;
  int pitphaseval4 ;
  int pitphaseval5 ;
  int pitphaseval6 ;
  int pitr ;
  int pitracqnub ;
  int pitracqval2 ;
  int pitracqval3 ;
  int pitracqval4 ;
  int pitracqval5 ;
  int pitracqval6 ;
  int pitrecoverydefval ;
  int pitrecoverynub ;
  int pitrecoverystep ;
  int pitrecoveryval2 ;
  int pitrecoveryval3 ;
  int pitrecoveryval4 ;
  int pitrecoveryval5 ;
  int pitrecoveryval6 ;
  float pitres ;
  float pitres2 ;
  int pitres2nub ;
  int pitresnub ;
  int pitricksdelnub ;
  int pitricksdelval3 ;
  int pitricksdelval4 ;
  int pitricksdelval5 ;
  int pitricksdelval6 ;
  int pitrigwinnub ;
  int pitrnub ;
  int pitrval2 ;
  int pitrval3 ;
  int pitrval4 ;
  int pitrval5 ;
  int pitrval6 ;
  float pitsar ;
  float pitscan ;
  int pitseq ;
  int pitseqnub ;
  int pitseqtype ;
  float pitslice ;
  int pitsp1 ;
  int pitsp2 ;
  int piuset ;
  int piuset2 ;
  int pivascop ;
  int pivelnub ;
  int pivestnub ;
  int pivextras ;
  int piviewordernub ;
  int piviews ;
  int piviewseg ;
  int pivpsdef ;
  int pivsphasenub ;
  int pivsphaseval2 ;
  int pivsphaseval3 ;
  int pivsphaseval4 ;
  int pivsphaseval5 ;
  int pivsphaseval6 ;
  float pivsscan ;
  int pixmtband ;
  int pixresnub ;
  int pixresval2 ;
  int pixresval3 ;
  int pixresval4 ;
  int pixresval5 ;
  int pixresval6 ;
  int piyresnub ;
  int piyresval2 ;
  int piyresval3 ;
  int piyresval4 ;
  int piyresval5 ;
  int piyresval6 ;
  int pizmult ;
  int pizoom_index ;
  int pos_hard180 ;
  int pos_moment_start ;
  int pos_msde_start ;
  int pos_rfgir01 ;
  int pos_rfgir02 ;
  int pos_start ;
  int pos_start_frir ;
  int pos_start_gzk ;
  int pos_start_ir ;
  int pos_start_ir_min ;
  int pos_start_killer_rfgir01 ;
  int pos_start_killer_rfgir02 ;
  int pos_start_rfgir01 ;
  int pos_start_rfgir02 ;
  float pospowerx ;
  float pospowery ;
  float pospowerz ;
  int post_lobes ;
  float post_osfp_weight ;
  float powerx ;
  float powery ;
  float powerz ;
  int pre_lobes ;
  int pre_pass ;
  int pre_rcvn_tr ;
  int pre_slice ;
  int predicted_TG ;
  int premid_rf90 ;
  int prep_dda ;
  int presscfh ;
  int presscfh_cgate ;
  int presscfh_ctrl ;
  int presscfh_debug ;
  float presscfh_fov ;
  float presscfh_fov_ratio ;
  int presscfh_ir_noselect ;
  float presscfh_ir_slthick ;
  float presscfh_minfov_ratio ;
  int presscfh_minte ;
  int presscfh_outrange ;
  int presscfh_override ;
  float presscfh_pfov ;
  float presscfh_pfov_ratio ;
  float presscfh_slab_ratio ;
  float presscfh_slice ;
  float presscfh_slthick ;
  int presscfh_wait_rf12 ;
  int presscfh_wait_rf23 ;
  int presscfh_wait_rf34 ;
  int prevent_scan_under_emul ;
  int product_rf ;
  float profile_opvthick ;
  int project ;
  int ps1_newgeo ;
  int ps1_rxcoil ;
  int ps1_tr ;
  LOG_GRAD ps1loggrd ;
  int ps1obl_debug ;
  float ps1scale ;
  int ps2_dda ;
  int ps2_dda_cal3d ;
  int ps2_dda_time_cal3d ;
  float ps_crusher_area ;
  int pscahead ;
  int psd_board_type ;
  int psd_card_hdwr_delay ;
  int psd_grd_wait ;
  int psd_mantrig ;
  int psd_pscshim ;
  int psd_psctg ;
  int psd_rf_wait ;
  int psd_startta_override ;
  int psd_taps ;
  float psd_targetscale ;
  int psd_tol_value ;
  float psd_zero ;
  int psdcrucial_debug ;
  int psddebugcode ;
  int psddebugcode2 ;
  int psdtime_rfgir01 ;
  int psdtime_rfgir01_iso ;
  int psdtime_rfgir02 ;
  int psdtime_rfgir02_iso ;
  int pulsepos ;
  float pure_mix_tx_scale ;
  int pw1_eff ;
  int pw2_eff ;
  int pw_acqdtg1 ;
  int pw_acqrs1 ;
  int pw_bsrf ;
  int pw_constant ;
  int pw_contrfhubsel ;
  int pw_contrfsel ;
  int pw_csw_wait ;
  int pw_dix_ssppost ;
  int pw_dix_ssppre ;
  int pw_dix_xpre ;
  int pw_drcv ;
  int pw_gate_isi ;
  int pw_gks ;
  int pw_gx1 ;
  int pw_gx1_frac ;
  int pw_gx1_full ;
  int pw_gx1a ;
  int pw_gx1a_frac ;
  int pw_gx1a_full ;
  int pw_gx1as ;
  int pw_gx1asa ;
  int pw_gx1asd ;
  int pw_gx1bftg ;
  int pw_gx1bftga ;
  int pw_gx1bftgd ;
  int pw_gx1bxtg ;
  int pw_gx1bxtga ;
  int pw_gx1bxtgd ;
  int pw_gx1cfh ;
  int pw_gx1cfha ;
  int pw_gx1cfhd ;
  int pw_gx1d ;
  int pw_gx1d_frac ;
  int pw_gx1d_full ;
  int pw_gx1dtg ;
  int pw_gx1dtga ;
  int pw_gx1dtgd ;
  int pw_gx1f ;
  int pw_gx1ftg ;
  int pw_gx1ftga ;
  int pw_gx1ftgd ;
  int pw_gx1mon ;
  int pw_gx1mona ;
  int pw_gx1mond ;
  int pw_gx1mps1 ;
  int pw_gx1mps1a ;
  int pw_gx1mps1d ;
  int pw_gx1rs ;
  int pw_gx1rsa ;
  int pw_gx1rsd ;
  int pw_gx1tm ;
  int pw_gx1tma ;
  int pw_gx1tmd ;
  int pw_gx2 ;
  int pw_gx2a ;
  int pw_gx2d ;
  int pw_gx2dtg ;
  int pw_gx2dtga ;
  int pw_gx2dtgd ;
  int pw_gx2ftg ;
  int pw_gx2ftga ;
  int pw_gx2ftgd ;
  int pw_gx2rs ;
  int pw_gx2rsa ;
  int pw_gx2rsd ;
  int pw_gx2test ;
  int pw_gx2testa ;
  int pw_gx2testd ;
  int pw_gxb ;
  int pw_gxba ;
  int pw_gxbd ;
  int pw_gxbrsfc1 ;
  int pw_gxbrsfc1a ;
  int pw_gxbrsfc1d ;
  int pw_gxbrsfc2 ;
  int pw_gxbrsfc2a ;
  int pw_gxbrsfc2d ;
  int pw_gxfc ;
  int pw_gxfc_frac ;
  int pw_gxfc_full ;
  int pw_gxfca ;
  int pw_gxfca_frac ;
  int pw_gxfca_full ;
  int pw_gxfcd ;
  int pw_gxfcd_frac ;
  int pw_gxfcd_full ;
  int pw_gxfcmon ;
  int pw_gxfcmona ;
  int pw_gxfcmond ;
  int pw_gxflpk ;
  int pw_gxflpka ;
  int pw_gxflpkd ;
  int pw_gxflpvenc ;
  int pw_gxflpvenca ;
  int pw_gxflpvencd ;
  int pw_gxhyst1 ;
  int pw_gxhyst1a ;
  int pw_gxhyst1d ;
  int pw_gxhyst2 ;
  int pw_gxhyst2a ;
  int pw_gxhyst2d ;
  int pw_gxkas ;
  int pw_gxkasa ;
  int pw_gxkasd ;
  int pw_gxkbsdtg ;
  int pw_gxkbsdtga ;
  int pw_gxkbsdtgd ;
  int pw_gxkbsrs ;
  int pw_gxkbsrsa ;
  int pw_gxkbsrsd ;
  int pw_gxkcs ;
  int pw_gxkcsa ;
  int pw_gxkcsd ;
  int pw_gxkdtg ;
  int pw_gxkdtga ;
  int pw_gxkdtgd ;
  int pw_gxkfs ;
  int pw_gxkfsa ;
  int pw_gxkfsd ;
  int pw_gxkill ;
  int pw_gxkilla ;
  int pw_gxkilld ;
  int pw_gxkrcvn ;
  int pw_gxkrcvna ;
  int pw_gxkrcvnd ;
  int pw_gxkrs ;
  int pw_gxkrsa ;
  int pw_gxkrsd ;
  int pw_gxks ;
  int pw_gxksa ;
  int pw_gxksd ;
  int pw_gxkse1 ;
  int pw_gxkse1a ;
  int pw_gxkse1d ;
  int pw_gxkse2 ;
  int pw_gxkse2a ;
  int pw_gxkse2d ;
  int pw_gxkse3 ;
  int pw_gxkse3a ;
  int pw_gxkse3d ;
  int pw_gxkse4 ;
  int pw_gxkse4a ;
  int pw_gxkse4d ;
  int pw_gxkse5 ;
  int pw_gxkse5a ;
  int pw_gxkse5d ;
  int pw_gxkse6 ;
  int pw_gxkse6a ;
  int pw_gxkse6d ;
  int pw_gxksp ;
  int pw_gxkspa ;
  int pw_gxkspd ;
  int pw_gxkssf ;
  int pw_gxkssfa ;
  int pw_gxkssfd ;
  int pw_gxksx1 ;
  int pw_gxksx1a ;
  int pw_gxksx1d ;
  int pw_gxksx2 ;
  int pw_gxksx2a ;
  int pw_gxksx2d ;
  int pw_gxksy1 ;
  int pw_gxksy1a ;
  int pw_gxksy1d ;
  int pw_gxksy2 ;
  int pw_gxksy2a ;
  int pw_gxksy2d ;
  int pw_gxksz1 ;
  int pw_gxksz1a ;
  int pw_gxksz1d ;
  int pw_gxksz2 ;
  int pw_gxksz2a ;
  int pw_gxksz2d ;
  int pw_gxrf1tm ;
  int pw_gxrf1tma ;
  int pw_gxrf1tmd ;
  int pw_gxrf2cfh ;
  int pw_gxrf2cfha ;
  int pw_gxrf2cfhd ;
  int pw_gxrfsx1 ;
  int pw_gxrfsx1a ;
  int pw_gxrfsx1d ;
  int pw_gxrfsx2 ;
  int pw_gxrfsx2a ;
  int pw_gxrfsx2d ;
  int pw_gxspiral ;
  int pw_gxspiral2 ;
  int pw_gxspoil ;
  int pw_gxspoil2 ;
  int pw_gxspoil2a ;
  int pw_gxspoil2d ;
  int pw_gxspoila ;
  int pw_gxspoild ;
  int pw_gxw ;
  int pw_gxw1ftg ;
  int pw_gxw1ftga ;
  int pw_gxw1ftgd ;
  int pw_gxw1xtg ;
  int pw_gxw1xtga ;
  int pw_gxw1xtgd ;
  int pw_gxw2 ;
  int pw_gxw2a ;
  int pw_gxw2d ;
  int pw_gxw2dtg ;
  int pw_gxw2dtga ;
  int pw_gxw2dtgd ;
  int pw_gxw2ftg ;
  int pw_gxw2ftga ;
  int pw_gxw2ftgd ;
  int pw_gxw2ftgleft ;
  int pw_gxw2rs ;
  int pw_gxw2rsa ;
  int pw_gxw2rsd ;
  int pw_gxw_frac ;
  int pw_gxw_full ;
  int pw_gxwa ;
  int pw_gxwa_frac ;
  int pw_gxwa_full ;
  int pw_gxwas ;
  int pw_gxwasa ;
  int pw_gxwasd ;
  int pw_gxwd ;
  int pw_gxwd_frac ;
  int pw_gxwd_full ;
  int pw_gxwd_temp ;
  int pw_gxwdtg ;
  int pw_gxwdtga ;
  int pw_gxwdtgd ;
  int pw_gxwex ;
  int pw_gxwex1 ;
  int pw_gxwexa ;
  int pw_gxwexd ;
  int pw_gxwexmax ;
  int pw_gxwl ;
  int pw_gxwmon ;
  int pw_gxwmona ;
  int pw_gxwmond ;
  int pw_gxwmps1 ;
  int pw_gxwmps1a ;
  int pw_gxwmps1d ;
  int pw_gxwr ;
  int pw_gxwrs ;
  int pw_gxwrsa ;
  int pw_gxwrsd ;
  int pw_gy1 ;
  int pw_gy1_tot ;
  int pw_gy1a ;
  int pw_gy1as ;
  int pw_gy1as_tot ;
  int pw_gy1asa ;
  int pw_gy1asd ;
  int pw_gy1cfh ;
  int pw_gy1cfha ;
  int pw_gy1cfhd ;
  int pw_gy1d ;
  int pw_gy1dtg ;
  int pw_gy1dtga ;
  int pw_gy1dtgd ;
  int pw_gy1f ;
  int pw_gy1mon ;
  int pw_gy1mona ;
  int pw_gy1mond ;
  int pw_gy1mps1 ;
  int pw_gy1mps1a ;
  int pw_gy1mps1d ;
  int pw_gy1r ;
  int pw_gy1r_tot ;
  int pw_gy1ra ;
  int pw_gy1ras ;
  int pw_gy1rasa ;
  int pw_gy1rasd ;
  int pw_gy1rd ;
  int pw_gy1rdtg ;
  int pw_gy1rdtga ;
  int pw_gy1rdtgd ;
  int pw_gy1rf ;
  int pw_gy1rrs ;
  int pw_gy1rrsa ;
  int pw_gy1rrsd ;
  int pw_gy1rs ;
  int pw_gy1rsa ;
  int pw_gy1rsd ;
  int pw_gy1tm ;
  int pw_gy1tma ;
  int pw_gy1tmd ;
  int pw_gy2dtg ;
  int pw_gy2dtga ;
  int pw_gy2dtgd ;
  int pw_gy2rs ;
  int pw_gy2rsa ;
  int pw_gy2rsd ;
  int pw_gyb ;
  int pw_gyba ;
  int pw_gybd ;
  int pw_gybrsfc1 ;
  int pw_gybrsfc1a ;
  int pw_gybrsfc1d ;
  int pw_gybrsfc2 ;
  int pw_gybrsfc2a ;
  int pw_gybrsfc2d ;
  int pw_gycylr ;
  int pw_gycylra ;
  int pw_gycylratipup ;
  int pw_gycylrtipup ;
  int pw_gyfe ;
  int pw_gyfe1 ;
  int pw_gyfe1a ;
  int pw_gyfe1d ;
  int pw_gyfe2 ;
  int pw_gyfe2a ;
  int pw_gyfe2d ;
  int pw_gyfea ;
  int pw_gyfed ;
  int pw_gyflpk ;
  int pw_gyflpka ;
  int pw_gyflpkd ;
  int pw_gyflpvenc ;
  int pw_gyflpvenca ;
  int pw_gyflpvencd ;
  int pw_gyhyst1 ;
  int pw_gyhyst1a ;
  int pw_gyhyst1d ;
  int pw_gyhyst2 ;
  int pw_gyhyst2a ;
  int pw_gyhyst2d ;
  int pw_gykcfh ;
  int pw_gykcfha ;
  int pw_gykcfhd ;
  int pw_gykcfl ;
  int pw_gykcfla ;
  int pw_gykcfld ;
  int pw_gykcs ;
  int pw_gykcsa ;
  int pw_gykcsd ;
  int pw_gykfs ;
  int pw_gykfsa ;
  int pw_gykfsd ;
  int pw_gykill ;
  int pw_gykilla ;
  int pw_gykilld ;
  int pw_gykrcvn ;
  int pw_gykrcvna ;
  int pw_gykrcvnd ;
  int pw_gyks ;
  int pw_gyksa ;
  int pw_gyksd ;
  int pw_gykse1 ;
  int pw_gykse1a ;
  int pw_gykse1d ;
  int pw_gykse2 ;
  int pw_gykse2a ;
  int pw_gykse2d ;
  int pw_gykse3 ;
  int pw_gykse3a ;
  int pw_gykse3d ;
  int pw_gykse4 ;
  int pw_gykse4a ;
  int pw_gykse4d ;
  int pw_gykse5 ;
  int pw_gykse5a ;
  int pw_gykse5d ;
  int pw_gykse6 ;
  int pw_gykse6a ;
  int pw_gykse6d ;
  int pw_gyksp ;
  int pw_gykspa ;
  int pw_gykspd ;
  int pw_gykssf ;
  int pw_gykssfa ;
  int pw_gykssfd ;
  int pw_gyksx1 ;
  int pw_gyksx1a ;
  int pw_gyksx1d ;
  int pw_gyksx2 ;
  int pw_gyksx2a ;
  int pw_gyksx2d ;
  int pw_gyksy1 ;
  int pw_gyksy1a ;
  int pw_gyksy1d ;
  int pw_gyksy2 ;
  int pw_gyksy2a ;
  int pw_gyksy2d ;
  int pw_gyksz1 ;
  int pw_gyksz1a ;
  int pw_gyksz1d ;
  int pw_gyksz2 ;
  int pw_gyksz2a ;
  int pw_gyksz2d ;
  int pw_gykxtgl ;
  int pw_gykxtgla ;
  int pw_gykxtgld ;
  int pw_gykxtgr ;
  int pw_gykxtgra ;
  int pw_gykxtgrd ;
  int pw_gyrf0kcfh ;
  int pw_gyrf0kcfha ;
  int pw_gyrf0kcfhd ;
  int pw_gyrf1mon ;
  int pw_gyrf1mona ;
  int pw_gyrf1mond ;
  int pw_gyrf1mps1 ;
  int pw_gyrf1mps1a ;
  int pw_gyrf1mps1d ;
  int pw_gyrf1tm ;
  int pw_gyrf1tma ;
  int pw_gyrf1tmd ;
  int pw_gyrf1xtg ;
  int pw_gyrf1xtga ;
  int pw_gyrf1xtgd ;
  int pw_gyrf2cfh ;
  int pw_gyrf2cfha ;
  int pw_gyrf2cfhd ;
  int pw_gyrf2lmon ;
  int pw_gyrf2lmona ;
  int pw_gyrf2lmond ;
  int pw_gyrf2mon ;
  int pw_gyrf2mona ;
  int pw_gyrf2mond ;
  int pw_gyrf2rmon ;
  int pw_gyrf2rmona ;
  int pw_gyrf2rmond ;
  int pw_gyrf3cfh ;
  int pw_gyrf3cfha ;
  int pw_gyrf3cfhd ;
  int pw_gyrfmontipup ;
  int pw_gyrfmontipupa ;
  int pw_gyrfmontipupd ;
  int pw_gyrfsy1 ;
  int pw_gyrfsy1a ;
  int pw_gyrfsy1d ;
  int pw_gyrfsy2 ;
  int pw_gyrfsy2a ;
  int pw_gyrfsy2d ;
  int pw_gyspiral ;
  int pw_gyspiral2 ;
  int pw_gyspoil ;
  int pw_gyspoil2 ;
  int pw_gyspoil2a ;
  int pw_gyspoil2d ;
  int pw_gyspoila ;
  int pw_gyspoild ;
  int pw_gz1 ;
  int pw_gz1a ;
  int pw_gz1as ;
  int pw_gz1asa ;
  int pw_gz1asd ;
  int pw_gz1cfl ;
  int pw_gz1cfla ;
  int pw_gz1cfld ;
  int pw_gz1d ;
  int pw_gz1dtg ;
  int pw_gz1dtga ;
  int pw_gz1dtgd ;
  int pw_gz1ftg ;
  int pw_gz1ftga ;
  int pw_gz1ftgd ;
  int pw_gz1mon ;
  int pw_gz1mona ;
  int pw_gz1mond ;
  int pw_gz1mps1 ;
  int pw_gz1mps1a ;
  int pw_gz1mps1d ;
  int pw_gz1rs ;
  int pw_gz1rsa ;
  int pw_gz1rsd ;
  int pw_gz1s ;
  int pw_gz1sa ;
  int pw_gz1sd ;
  int pw_gz1xtg ;
  int pw_gz1xtga ;
  int pw_gz1xtgd ;
  int pw_gz2bftg ;
  int pw_gz2bftga ;
  int pw_gz2bftgd ;
  int pw_gz2ftg ;
  int pw_gz2ftga ;
  int pw_gz2ftgd ;
  int pw_gz2xtg ;
  int pw_gz2xtga ;
  int pw_gz2xtgd ;
  int pw_gz3ftg ;
  int pw_gz3ftga ;
  int pw_gz3ftgd ;
  int pw_gzbrsfc1 ;
  int pw_gzbrsfc1a ;
  int pw_gzbrsfc1d ;
  int pw_gzbrsfc1echo1 ;
  int pw_gzbrsfc1echo1a ;
  int pw_gzbrsfc1echo1d ;
  int pw_gzbrsfc1echo2 ;
  int pw_gzbrsfc1echo2a ;
  int pw_gzbrsfc1echo2d ;
  int pw_gzbrsfc2 ;
  int pw_gzbrsfc2a ;
  int pw_gzbrsfc2d ;
  int pw_gzcomb ;
  int pw_gzcomb_tot ;
  int pw_gzcomba ;
  int pw_gzcombd ;
  int pw_gzcombf ;
  int pw_gzcombhtr ;
  int pw_gzcombhtra ;
  int pw_gzcombhtrd ;
  int pw_gzcombhtrf ;
  int pw_gzcylr ;
  int pw_gzcylra ;
  int pw_gzcylratipup ;
  int pw_gzcylrtipup ;
  int pw_gzfc ;
  int pw_gzfca ;
  int pw_gzfcd ;
  int pw_gzflpk ;
  int pw_gzflpka ;
  int pw_gzflpkd ;
  int pw_gzflpvenc ;
  int pw_gzflpvenca ;
  int pw_gzflpvencd ;
  int pw_gzk ;
  int pw_gzka ;
  int pw_gzkas ;
  int pw_gzkasa ;
  int pw_gzkasd ;
  int pw_gzkbsdtg ;
  int pw_gzkbsdtga ;
  int pw_gzkbsdtgd ;
  int pw_gzkbsrs ;
  int pw_gzkbsrsa ;
  int pw_gzkbsrsd ;
  int pw_gzkcs ;
  int pw_gzkcsa ;
  int pw_gzkcsd ;
  int pw_gzkd ;
  int pw_gzkdtg ;
  int pw_gzkdtga ;
  int pw_gzkdtgd ;
  int pw_gzkfs ;
  int pw_gzkfsa ;
  int pw_gzkfsd ;
  int pw_gzkgir01 ;
  int pw_gzkgir01a ;
  int pw_gzkgir01d ;
  int pw_gzkgir02 ;
  int pw_gzkgir02a ;
  int pw_gzkgir02d ;
  int pw_gzkill ;
  int pw_gzkilla ;
  int pw_gzkilld ;
  int pw_gzkiller ;
  int pw_gzkillera ;
  int pw_gzkillerd ;
  int pw_gzkmon ;
  int pw_gzkmona ;
  int pw_gzkmond ;
  int pw_gzkmontipup ;
  int pw_gzkmontipupa ;
  int pw_gzkmontipupd ;
  int pw_gzkrcvn ;
  int pw_gzkrcvna ;
  int pw_gzkrcvnd ;
  int pw_gzkrffrir ;
  int pw_gzkrffrira ;
  int pw_gzkrffrird ;
  int pw_gzkrs ;
  int pw_gzkrsa ;
  int pw_gzkrsd ;
  int pw_gzks ;
  int pw_gzks5fp ;
  int pw_gzks5fpa ;
  int pw_gzks5fpd ;
  int pw_gzksa ;
  int pw_gzksd ;
  int pw_gzksp ;
  int pw_gzkspa ;
  int pw_gzkspd ;
  int pw_gzkssf ;
  int pw_gzkssfa ;
  int pw_gzkssfd ;
  int pw_gzp ;
  int pw_gzpa ;
  int pw_gzpd ;
  int pw_gzpf ;
  int pw_gzphtr ;
  int pw_gzphtra ;
  int pw_gzphtrd ;
  int pw_gzphtrf ;
  int pw_gzptm ;
  int pw_gzptma ;
  int pw_gzptmd ;
  int pw_gzrf0 ;
  int pw_gzrf0a ;
  int pw_gzrf0cfh ;
  int pw_gzrf0cfha ;
  int pw_gzrf0cfhd ;
  int pw_gzrf0d ;
  int pw_gzrf0k ;
  int pw_gzrf0ka ;
  int pw_gzrf0kd ;
  int pw_gzrf1 ;
  int pw_gzrf1a ;
  int pw_gzrf1a_temp ;
  int pw_gzrf1as ;
  int pw_gzrf1asa ;
  int pw_gzrf1asd ;
  int pw_gzrf1cfh ;
  int pw_gzrf1cfha ;
  int pw_gzrf1cfhd ;
  int pw_gzrf1cfl ;
  int pw_gzrf1cfla ;
  int pw_gzrf1cfld ;
  int pw_gzrf1d ;
  int pw_gzrf1d_temp ;
  int pw_gzrf1dtg ;
  int pw_gzrf1dtga ;
  int pw_gzrf1dtgd ;
  int pw_gzrf1ftg ;
  int pw_gzrf1ftga ;
  int pw_gzrf1ftgd ;
  int pw_gzrf1htr ;
  int pw_gzrf1htra ;
  int pw_gzrf1htrd ;
  int pw_gzrf1lobe ;
  int pw_gzrf1mon ;
  int pw_gzrf1mona ;
  int pw_gzrf1mond ;
  int pw_gzrf1mps1 ;
  int pw_gzrf1mps1a ;
  int pw_gzrf1mps1d ;
  int pw_gzrf1rs ;
  int pw_gzrf1rsa ;
  int pw_gzrf1rsd ;
  int pw_gzrf1s ;
  int pw_gzrf1sa ;
  int pw_gzrf1sd ;
  int pw_gzrf1xtg ;
  int pw_gzrf1xtga ;
  int pw_gzrf1xtgd ;
  int pw_gzrf2ftg ;
  int pw_gzrf2ftga ;
  int pw_gzrf2ftgd ;
  int pw_gzrf2lcfh ;
  int pw_gzrf2lcfha ;
  int pw_gzrf2lcfhd ;
  int pw_gzrf2lmps1 ;
  int pw_gzrf2lmps1a ;
  int pw_gzrf2lmps1d ;
  int pw_gzrf2mps1 ;
  int pw_gzrf2mps1a ;
  int pw_gzrf2mps1d ;
  int pw_gzrf2rcfh ;
  int pw_gzrf2rcfha ;
  int pw_gzrf2rcfhd ;
  int pw_gzrf2rmps1 ;
  int pw_gzrf2rmps1a ;
  int pw_gzrf2rmps1d ;
  int pw_gzrf2xtg ;
  int pw_gzrf2xtga ;
  int pw_gzrf2xtgd ;
  int pw_gzrf3ftg ;
  int pw_gzrf3ftga ;
  int pw_gzrf3ftgd ;
  int pw_gzrf3lcfh ;
  int pw_gzrf3lcfha ;
  int pw_gzrf3lcfhd ;
  int pw_gzrf3rcfh ;
  int pw_gzrf3rcfha ;
  int pw_gzrf3rcfhd ;
  int pw_gzrf4cfh ;
  int pw_gzrf4cfha ;
  int pw_gzrf4cfhd ;
  int pw_gzrf4lcfh ;
  int pw_gzrf4lcfha ;
  int pw_gzrf4lcfhd ;
  int pw_gzrf4rcfh ;
  int pw_gzrf4rcfha ;
  int pw_gzrf4rcfhd ;
  int pw_gzrffrir ;
  int pw_gzrffrira ;
  int pw_gzrffrird ;
  int pw_gzrfgir01 ;
  int pw_gzrfgir01a ;
  int pw_gzrfgir01d ;
  int pw_gzrfgir02 ;
  int pw_gzrfgir02a ;
  int pw_gzrfgir02d ;
  int pw_gzrfs5fph ;
  int pw_gzrfs5fpha ;
  int pw_gzrfs5fphd ;
  int pw_gzrfse1 ;
  int pw_gzrfse1a ;
  int pw_gzrfse1d ;
  int pw_gzrfse2 ;
  int pw_gzrfse2a ;
  int pw_gzrfse2d ;
  int pw_gzrfse3 ;
  int pw_gzrfse3a ;
  int pw_gzrfse3d ;
  int pw_gzrfse4 ;
  int pw_gzrfse4a ;
  int pw_gzrfse4d ;
  int pw_gzrfse5 ;
  int pw_gzrfse5a ;
  int pw_gzrfse5d ;
  int pw_gzrfse6 ;
  int pw_gzrfse6a ;
  int pw_gzrfse6d ;
  int pw_gzrfssfh ;
  int pw_gzrfssfha ;
  int pw_gzrfssfhd ;
  int pw_gzrfsz1 ;
  int pw_gzrfsz1a ;
  int pw_gzrfsz1d ;
  int pw_gzrfsz2 ;
  int pw_gzrfsz2a ;
  int pw_gzrfsz2d ;
  int pw_gzs5fphcomb ;
  int pw_gzs5fphcomba ;
  int pw_gzs5fphcombd ;
  int pw_gzssfhcomb ;
  int pw_gzssfhcomba ;
  int pw_gzssfhcombd ;
  int pw_gzvlmin ;
  int pw_gzvlw ;
  int pw_hard180 ;
  int pw_hst ;
  int pw_isi7 ;
  int pw_isi_cardiacsat ;
  int pw_isi_gir1 ;
  int pw_isi_gire01 ;
  int pw_isi_gire02 ;
  int pw_isi_girk01 ;
  int pw_isi_girk02 ;
  int pw_isi_sate1 ;
  int pw_isi_sate2 ;
  int pw_isi_sate3 ;
  int pw_isi_sate4 ;
  int pw_isi_sate5 ;
  int pw_isi_sate6 ;
  int pw_isi_satek1 ;
  int pw_isi_satek2 ;
  int pw_isi_satek3 ;
  int pw_isi_satek4 ;
  int pw_isi_satek5 ;
  int pw_isi_satek6 ;
  int pw_isi_satx1 ;
  int pw_isi_satx2 ;
  int pw_isi_satxk1 ;
  int pw_isi_satxk2 ;
  int pw_isi_saty1 ;
  int pw_isi_saty2 ;
  int pw_isi_satyk1 ;
  int pw_isi_satyk2 ;
  int pw_isi_satz1 ;
  int pw_isi_satz2 ;
  int pw_isi_satzk1 ;
  int pw_isi_satzk2 ;
  int pw_isi_slice1 ;
  int pw_isi_slice2 ;
  int pw_isigir ;
  int pw_isisat ;
  int pw_isislice ;
  int pw_maps1 ;
  int pw_maps2 ;
  int pw_mapx ;
  int pw_mapy ;
  int pw_mapz ;
  int pw_mpomega_td0 ;
  int pw_mprho_td0 ;
  int pw_mpssp_td0 ;
  int pw_mptheta_td0 ;
  int pw_mpx_td0 ;
  int pw_mpy_td0 ;
  int pw_mpz_td0 ;
  int pw_nomcyl ;
  int pw_omega_hs_rfcssat ;
  int pw_omega_ir0 ;
  int pw_omega_rffrir ;
  int pw_omega_rfgir01 ;
  int pw_omega_rfgir02 ;
  int pw_omegarf0cfh ;
  int pw_postgxw1ftg ;
  int pw_postgxw1ftga ;
  int pw_postgxw1ftgd ;
  int pw_rampx ;
  int pw_rampy ;
  int pw_rampz ;
  int pw_rcvn_wait ;
  int pw_rf0 ;
  int pw_rf0cfh ;
  int pw_rf1 ;
  int pw_rf180 ;
  int pw_rf1_full ;
  int pw_rf1_pre ;
  int pw_rf1as ;
  int pw_rf1cfh ;
  int pw_rf1cfl ;
  int pw_rf1dtg ;
  int pw_rf1ftg ;
  int pw_rf1htr ;
  int pw_rf1mon ;
  int pw_rf1mps1 ;
  int pw_rf1rs ;
  int pw_rf1tm ;
  int pw_rf1xtg ;
  int pw_rf2cfh ;
  int pw_rf2ftg ;
  int pw_rf2mon ;
  int pw_rf2mps1 ;
  int pw_rf2xtg ;
  int pw_rf3cfh ;
  int pw_rf3ftg ;
  int pw_rf3xtg ;
  int pw_rf4cfh ;
  int pw_rf4xtg ;
  int pw_rf90 ;
  int pw_rfbdtg ;
  int pw_rfbrs ;
  int pw_rfcssat ;
  int pw_rfcssatcfh ;
  int pw_rfcylr ;
  int pw_rfcylrtipup ;
  int pw_rfflp180 ;
  int pw_rfflp180_the ;
  int pw_rfflp90 ;
  int pw_rfflp90_the ;
  int pw_rfflp90r ;
  int pw_rfflp90r_the ;
  int pw_rffrir ;
  int pw_rffs ;
  int pw_rfgir01 ;
  int pw_rfgir02 ;
  int pw_rfmontipup ;
  int pw_rfs ;
  int pw_rfs5fph ;
  int pw_rfse1 ;
  int pw_rfse2 ;
  int pw_rfse3 ;
  int pw_rfse4 ;
  int pw_rfse5 ;
  int pw_rfse6 ;
  int pw_rfssf ;
  int pw_rfssfh ;
  int pw_rfsx1 ;
  int pw_rfsx2 ;
  int pw_rfsy1 ;
  int pw_rfsy2 ;
  int pw_rfsz1 ;
  int pw_rfsz2 ;
  int pw_rftipup ;
  int pw_rot_slice1 ;
  int pw_rot_slice2 ;
  int pw_rot_update_cardiacsat ;
  int pw_rot_update_e1 ;
  int pw_rot_update_e2 ;
  int pw_rot_update_e3 ;
  int pw_rot_update_e4 ;
  int pw_rot_update_e5 ;
  int pw_rot_update_e6 ;
  int pw_rot_update_ek1 ;
  int pw_rot_update_ek2 ;
  int pw_rot_update_ek3 ;
  int pw_rot_update_ek4 ;
  int pw_rot_update_ek5 ;
  int pw_rot_update_ek6 ;
  int pw_rot_update_gir ;
  int pw_rot_update_gire01 ;
  int pw_rot_update_girk01 ;
  int pw_rot_update_girk02 ;
  int pw_rot_update_rfgir02 ;
  int pw_rot_update_x1 ;
  int pw_rot_update_x2 ;
  int pw_rot_update_xk1 ;
  int pw_rot_update_xk2 ;
  int pw_rot_update_y1 ;
  int pw_rot_update_y2 ;
  int pw_rot_update_yk1 ;
  int pw_rot_update_yk2 ;
  int pw_rot_update_z1 ;
  int pw_rot_update_z2 ;
  int pw_rot_update_zk1 ;
  int pw_rot_update_zk2 ;
  int pw_rotslice ;
  int pw_rotupdate ;
  int pw_rotupdate_gir ;
  int pw_rticfh ;
  int pw_satrampx ;
  int pw_satrampy ;
  int pw_satrampz ;
  int pw_sdixon ;
  int pw_sdixon2 ;
  int pw_ss_rampz ;
  int pw_sticfh ;
  int pw_thcylr ;
  int pw_thcylrtipup ;
  int pw_thetarf1 ;
  int pw_xdelay ;
  int pw_xdixon ;
  int pw_xrespgate ;
  int pw_xticfh ;
  int pw_y_ccs_null ;
  int pw_ydixon ;
  int pw_yticfh ;
  int pw_zdixon ;
  int pw_zticfh ;
  int px_pwmtime ;
  int py_pwmtime ;
  int pz_pwmtime ;
  int quickstep_flag ;
  int radfb_flag ;
  float ratio_rfflp90 ;
  float ratio_rfflp90r ;
  int rawdata ;
  int rawmode ;
  float rbw ;
  int rcvn_dda ;
  int rcvn_flag ;
  int rcvn_loops ;
  int rcvn_nex ;
  int rcvn_tdaq ;
  int rcvn_tr ;
  int rcvn_xres ;
  LOG_GRAD rcvnloggrd ;
  int rcvr_ub_off ;
  int rd_ext_dtg ;
  int rd_ext_rs ;
  int rda_mon ;
  WF_PROCESSOR read_axis ;
  int read_col ;
  int readmonloc ;
  int rec_mode ;
  int recon_1024 ;
  int recon_imag_image ;
  int recon_mag_image ;
  int recon_pha_image ;
  int recon_qmag_image ;
  int rectfov_npw_support ;
  float refocus ;
  int regViewOrderMode ;
  int region_order_mode ;
  int reilly_mode ;
  int res_dephase ;
  int res_dummyrf ;
  int res_gx1 ;
  int res_gxspiral ;
  int res_gxspiral2 ;
  int res_gy1 ;
  int res_gy1r ;
  int res_gycylr ;
  int res_gycylra ;
  int res_gycylratipup ;
  int res_gycylrtipup ;
  int res_gyspiral ;
  int res_gyspiral2 ;
  int res_gzcomb ;
  int res_gzcombhtr ;
  int res_gzcylr ;
  int res_gzcylra ;
  int res_gzcylratipup ;
  int res_gzcylrtipup ;
  int res_gzp ;
  int res_gzphtr ;
  int res_gzrf0 ;
  int res_gzrf0cfh ;
  int res_gzrf1 ;
  int res_gzrffrir ;
  int res_gzrfgir01 ;
  int res_gzrfgir02 ;
  int res_gzvlw ;
  int res_hard180 ;
  int res_omega_hs_rfcssat ;
  int res_omega_ir0 ;
  int res_omega_rffrir ;
  int res_omega_rfgir01 ;
  int res_omega_rfgir02 ;
  int res_omegarf0cfh ;
  int res_rf0 ;
  int res_rf0cfh ;
  int res_rf1 ;
  int res_rf180 ;
  int res_rf1_full ;
  int res_rf1_temp ;
  int res_rf1as ;
  int res_rf1cfh ;
  int res_rf1cfl ;
  int res_rf1dtg ;
  int res_rf1ftg ;
  int res_rf1htr ;
  int res_rf1mon ;
  int res_rf1mps1 ;
  int res_rf1rs ;
  int res_rf1tm ;
  int res_rf1xtg ;
  int res_rf2cfh ;
  int res_rf2ftg ;
  int res_rf2mon ;
  int res_rf2mps1 ;
  int res_rf2xtg ;
  int res_rf3cfh ;
  int res_rf3ftg ;
  int res_rf3xtg ;
  int res_rf4cfh ;
  int res_rf4xtg ;
  int res_rf90 ;
  int res_rfbdtg ;
  int res_rfbrs ;
  int res_rfcssat ;
  int res_rfcylr ;
  int res_rfcylrtipup ;
  int res_rfflp180 ;
  int res_rfflp180_the ;
  int res_rfflp90 ;
  int res_rfflp90_the ;
  int res_rfflp90r ;
  int res_rfflp90r_the ;
  int res_rffrir ;
  int res_rffs ;
  int res_rfgir01 ;
  int res_rfgir02 ;
  int res_rfmontipup ;
  int res_rfs5fph ;
  int res_rfse1 ;
  int res_rfse2 ;
  int res_rfse3 ;
  int res_rfse4 ;
  int res_rfse5 ;
  int res_rfse6 ;
  int res_rfssf ;
  int res_rfssfh ;
  int res_rfsx1 ;
  int res_rfsx2 ;
  int res_rfsy1 ;
  int res_rfsy2 ;
  int res_rfsz1 ;
  int res_rfsz2 ;
  int res_rftipup ;
  int res_thcylr ;
  int res_thcylrtipup ;
  int res_thetarf1 ;
  int res_thetarfbdtg ;
  int res_thetarfbrs ;
  int resp_centk_percent ;
  int resp_dda ;
  int resp_gate_trig_sw ;
  int resp_nex ;
  float respdc ;
  int respgate_flag ;
  int respseqcore ;
  int retropc_extra ;
  int reverseLoopOrder_flag ;
  int reverse_centric_flag ;
  int reverse_ellipt_flag ;
  int reverse_first_region_flag ;
  int reverse_views ;
  int rewinder_flag ;
  int rewinding_time ;
  float rf0_phase ;
  int rf0_pulse_type ;
  int rf1_pulse_type ;
  float rf1dtg_scale ;
  int rf1dtg_type ;
  float rf1mon_shift ;
  float rf1rs_scale ;
  int rf1rs_type ;
  float rf2mon_shift ;
  float rf_scale_fac ;
  int rfb1opt_counter ;
  int rfb1opt_flag ;
  int rfconf ;
  float rffrir_phase ;
  float rfgir01_phase ;
  int rfgir01_start ;
  int rfgir01_time ;
  int rfgir01_type ;
  int rfgir01_wait ;
  float rfgir02_phase ;
  int rfgir02_start ;
  int rfgir02_time ;
  int rfgir02_type ;
  int rfgir02_wait ;
  int rfsafetyopt_timeflag ;
  float rfshim_b1factor ;
  int rfshim_baseline ;
  int rfshim_etl ;
  float rfshim_flipangle ;
  float rfshim_fov ;
  int rfshim_ptsize ;
  int rfshim_slquant ;
  float rfshim_slthick ;
  int rfshim_xres ;
  int rfshim_yres ;
  int rfslot_hard180 ;
  int rfslot_omega_hs_rfcssat ;
  int rfslot_omega_ir0 ;
  int rfslot_omega_rffrir ;
  int rfslot_omega_rfgir01 ;
  int rfslot_omega_rfgir02 ;
  int rfslot_omegarf0cfh ;
  int rfslot_rf90 ;
  int rfslot_rfflp180 ;
  int rfslot_rfflp180_the ;
  int rfslot_rfflp90 ;
  int rfslot_rfflp90_the ;
  int rfslot_rfflp90r ;
  int rfslot_rfflp90r_the ;
  int rfslot_rftipup ;
  int rftype ;
  int rfupacv ;
  int rgfeature_enable ;
  float rh2dscale ;
  int rh3dgw_interptype ;
  float rh3dscale ;
  float rh3dwina ;
  float rh3dwinq ;
  int rh3dwintype ;
  int rhFillMapLSW ;
  int rhFillMapMSW ;
  float rh_ime_clariview_edge ;
  float rh_ime_clariview_focus ;
  float rh_ime_clariview_smooth ;
  int rh_ime_clariview_type ;
  int rh_ime_definefilter_nr ;
  int rh_ime_definefilter_sh ;
  float rh_ime_scic_edge ;
  int rh_ime_scic_enable ;
  float rh_ime_scic_focus ;
  float rh_ime_scic_gauss ;
  float rh_ime_scic_reduction ;
  float rh_ime_scic_smooth ;
  float rh_ime_scic_threshold ;
  float rh_low_pass_nex_filter_width ;
  int rh_rc_enhance_enable ;
  float rhalpha ;
  int rhalt ;
  int rhapfov ;
  int rhaphases ;
  int rhapp ;
  int rhapp_option ;
  int rhasl_perf_weighted_scale ;
  int rhasset ;
  float rhasset_R ;
  int rhasset_alt_cal ;
  int rhasset_calthresh ;
  int rhasset_localTx ;
  int rhasset_phases ;
  float rhasset_slwrap ;
  int rhasset_torso ;
  float rhassetsl_R ;
  int rhb0map ;
  int rhblank ;
  int rhbline ;
  int rhbp_corr ;
  int rhcal_nex_vector ;
  int rhcal_options ;
  int rhcal_pass_set_vector ;
  int rhcal_weight_vector ;
  int rhcalmode ;
  float rhchannel_combine_filter_beta ;
  int rhchannel_combine_filter_type ;
  float rhchannel_combine_filter_width ;
  int rhchannel_combine_method ;
  float rhclipmax ;
  float rhclipmin ;
  int rhcoilno ;
  float rhcorrelationThreshold ;
  int rhcphases ;
  float rhcrrtime ;
  float rhcs_consistency ;
  float rhcs_factor ;
  int rhcs_flag ;
  int rhcs_maxiter ;
  int rhcs_ph_stride ;
  int rhcs_sl_stride ;
  float rhctr ;
  int rhdab0e ;
  int rhdab0s ;
  int rhdacqctrl ;
  int rhdatacq ;
  int rhdaviewsPerBlade ;
  int rhdaxres ;
  int rhdayres ;
  int rhdbgrecon ;
  int rhddaover ;
  float rhdensityfactor ;
  int rhdf ;
  int rhdfm ;
  int rhdfmdebug ;
  int rhdfmnavsperpass ;
  int rhdfmnavsperview ;
  int rhdfmptsize ;
  float rhdfmrbw ;
  float rhdfmthreshold ;
  int rhdfmxres ;
  int rhdifnext2 ;
  int rhdiskacqctrl ;
  float rhdispfov ;
  float rhdoffset ;
  int rhdptype ;
  float rhdwnavcoeff ;
  int rhdwnavcor ;
  int rhdwnavcorecho ;
  int rhdwnaveshot ;
  int rhdwnaveview ;
  int rhdwnavsshot ;
  int rhdwnavsview ;
  int rhdwnavview ;
  int rhech2skip ;
  int rhechopc_ctrl ;
  int rhechopc_extra_bot ;
  int rhechopc_primary_yfirst ;
  int rhechopc_reverse_yfirst ;
  int rhechopc_ylines ;
  int rhechopc_yxfitorder ;
  int rhechopc_zlines ;
  int rhectricks_input_regions ;
  int rhectricks_num_regions ;
  int rhesp ;
  int rhetl ;
  int rhexciterfreqs ;
  int rhexciterusage ;
  int rhexecctrl ;
  int rhextra_frames_bot ;
  int rhextra_frames_top ;
  int rhfast_rec ;
  int rhfatwater ;
  int rhfcinearw ;
  int rhfcinemode ;
  int rhfdctrl ;
  int rhfeextra ;
  float rhferme ;
  float rhfermr ;
  float rhfermw ;
  int rhfiesta ;
  int rhflipfilter ;
  int rhformat ;
  float rhfreqscale ;
  int rhfrsize ;
  int rhgradmode ;
  int rhgridcontrol ;
  int rhhdbestky ;
  int rhheover ;
  int rhherawflt ;
  float rhherawflt_befamp ;
  float rhherawflt_befntran ;
  float rhherawflt_befnwin ;
  float rhherawflt_hpfamp ;
  int rhhniter ;
  int rhhnover ;
  int rhhoec_fit_order ;
  int rhhoecc ;
  int rhileaves ;
  int rhimsize ;
  int rhincrpass ;
  int rhinitpass ;
  int rhkacq_uid ;
  int rhkt_cal_factor ;
  int rhkt_calwidth_ph ;
  int rhkt_calwidth_sl ;
  int rhkt_factor ;
  int rhkydir ;
  int rhlcfiesta ;
  float rhlcfiesta_phase ;
  int rhleft_blank ;
  float rhmaxcoef1a ;
  float rhmaxcoef1b ;
  float rhmaxcoef1c ;
  float rhmaxcoef1d ;
  float rhmaxcoef2a ;
  float rhmaxcoef2b ;
  float rhmaxcoef2c ;
  float rhmaxcoef2d ;
  float rhmaxcoef3a ;
  float rhmaxcoef3b ;
  float rhmaxcoef3c ;
  float rhmaxcoef3d ;
  float rhmaxgrad ;
  int rhmb_factor ;
  int rhmb_slice_fov_shift_factor ;
  int rhmb_slice_order_sign ;
  int rhmedal_down_kernel_size ;
  int rhmedal_echo_order ;
  int rhmedal_ending_slice ;
  int rhmedal_mode ;
  int rhmedal_nstack_size ;
  float rhmedal_param ;
  int rhmedal_smooth_kernel_size ;
  int rhmedal_starting_slice ;
  int rhmedal_up_kernel_size ;
  int rhmeth ;
  int rhmethod ;
  int rhmotioncomp ;
  int rhmphasetype ;
  int rhnavs ;
  int rhncoillimit ;
  int rhncoilsel ;
  int rhncycles_cine ;
  int rhnecho ;
  int rhnew_wnd_level_flag ;
  int rhnex ;
  int rhnex_unacquired ;
  int rhnframes ;
  int rhnoncart_dual_traj ;
  float rhnoncart_grid_factor ;
  int rhnoncart_traj_kmax_ratio ;
  int rhnoncart_traj_merge_end ;
  int rhnoncart_traj_merge_start ;
  int rhnoncart_traj_mode ;
  int rhnpasses ;
  int rhnphases ;
  int rhnpomp ;
  float rhnpwfactor ;
  int rhnrefslices ;
  int rhnslices ;
  int rhnspokes_highres ;
  int rhnspokes_lowres ;
  float rhntran ;
  int rhnumCoilConfigs ;
  int rhnumbvals ;
  int rhnumdifdirs ;
  int rhnumslabs ;
  int rhnvircchannel ;
  float rhnwin ;
  int rhoscans ;
  float rhoversamplingfactor ;
  int rhovl ;
  int rhpasframe ;
  int rhpc_rationalscale ;
  int rhpc_ref_skip ;
  int rhpc_ref_start ;
  int rhpc_ref_stop ;
  float rhpcbestky ;
  int rhpccoil ;
  int rhpccon ;
  int rhpcconfitwt ;
  int rhpcconfix ;
  int rhpcconnorm ;
  int rhpcconnpts ;
  int rhpcconorder ;
  float rhpcconslope ;
  int rhpcctrl ;
  int rhpcdiscbeg ;
  int rhpcdiscend ;
  int rhpcdiscmid ;
  int rhpcextcorr ;
  int rhpcfitorig ;
  int rhpcgraph ;
  int rhpcileave ;
  int rhpcinvft ;
  int rhpclin ;
  int rhpclinavg ;
  int rhpclinfitwt ;
  int rhpclinfix ;
  int rhpclinnorm ;
  int rhpclinnpts ;
  int rhpclinorder ;
  float rhpclinslope ;
  int rhpcmag ;
  int rhpcmultegrp ;
  int rhpcshotfirst ;
  int rhpcshotlast ;
  int rhpcsnore ;
  int rhpcspacial ;
  int rhpcspacial_dynamic ;
  int rhpctemporal ;
  int rhpctest ;
  int rhpcthrespct ;
  int rhpcthrespts ;
  float rhphasescale ;
  int rhphsen_pixel_offset ;
  int rhposition_detection ;
  int rhpropellerCtrl ;
  int rhptsize ;
  int rhpure ;
  float rhpure_blur ;
  int rhpure_blur_enable ;
  float rhpure_cal_reapodization ;
  float rhpure_derived_cal_fraction ;
  int rhpure_filtering_mode ;
  float rhpure_lambda ;
  float rhpure_mix_alpha ;
  int rhpure_mix_aniso_blur ;
  int rhpure_mix_aniso_dilate_dist ;
  int rhpure_mix_aniso_erode_dist ;
  float rhpure_mix_blur ;
  int rhpure_mix_blur_enable ;
  int rhpure_mix_dilate_dist ;
  int rhpure_mix_erode_dist ;
  float rhpure_mix_exp_wt ;
  float rhpure_mix_lambda ;
  int rhpure_mix_otsu_class_qty ;
  float rhpure_mix_tuning_factor_body ;
  float rhpure_mix_tuning_factor_surface ;
  float rhpure_scale_factor ;
  float rhpure_tuning_factor_body ;
  float rhpure_tuning_factor_surface ;
  int rhpurechannel ;
  int rhpurefilter ;
  float rhradiusa ;
  float rhradiusb ;
  n64 rhrawsize ;
  int rhrawsizeview ;
  int rhrc3dcinectrl ;
  int rhrc_cardt1map_ctrl ;
  int rhrc_moco_ctrl ;
  int rhrcctrl ;
  int rhrcdixproc ;
  int rhrcideal ;
  int rhrcidealctrl ;
  int rhrcmavric_bin_separation ;
  int rhrcmavric_control ;
  int rhrcmavric_image ;
  int rhrcxres ;
  int rhrcyres ;
  int rhrecon ;
  float rhrecv_freq_e ;
  float rhrecv_freq_s ;
  int rhref ;
  int rhrefframep ;
  int rhrefframes ;
  int rhreps ;
  int rhretro_control ;
  int rhright_blank ;
  int rhrlfov ;
  float rhrotationThreshold ;
  float rhscancent ;
  float rhscanfov ;
  int rhscnframe ;
  float rhshiftThreshold ;
  int rhsifov ;
  int rhslblank ;
  float rhslewmax ;
  int rhsnrnoise ;
  int rhspeccsidims ;
  int rhspecrescsix ;
  int rhspecrescsiy ;
  int rhspecrescsiz ;
  float rhspecroilenx ;
  float rhspecroileny ;
  float rhspecroilenz ;
  float rhspecroilocx ;
  float rhspecroilocy ;
  float rhspecroilocz ;
  float rhspecwidth ;
  int rhsspsave ;
  int rhswiftenable ;
  int rhte ;
  int rhte2 ;
  int rhtediff ;
  int rhtrickstype ;
  float rhtsamp ;
  int rhtype ;
  int rhtype1 ;
  int rhudasave ;
  float rhuser0 ;
  float rhuser1 ;
  float rhuser10 ;
  float rhuser11 ;
  float rhuser12 ;
  float rhuser13 ;
  float rhuser14 ;
  float rhuser15 ;
  float rhuser16 ;
  float rhuser17 ;
  float rhuser18 ;
  float rhuser19 ;
  float rhuser2 ;
  float rhuser20 ;
  float rhuser21 ;
  float rhuser22 ;
  float rhuser23 ;
  float rhuser24 ;
  float rhuser25 ;
  float rhuser26 ;
  float rhuser27 ;
  float rhuser28 ;
  float rhuser29 ;
  float rhuser3 ;
  float rhuser30 ;
  float rhuser31 ;
  float rhuser32 ;
  float rhuser33 ;
  float rhuser34 ;
  float rhuser35 ;
  float rhuser36 ;
  float rhuser37 ;
  float rhuser38 ;
  float rhuser39 ;
  float rhuser4 ;
  float rhuser40 ;
  float rhuser41 ;
  float rhuser42 ;
  float rhuser43 ;
  float rhuser44 ;
  float rhuser45 ;
  float rhuser46 ;
  float rhuser47 ;
  float rhuser48 ;
  float rhuser5 ;
  float rhuser6 ;
  float rhuser7 ;
  float rhuser8 ;
  float rhuser9 ;
  int rhuser_usage_tag ;
  int rhutctrl ;
  float rhvcoefxa ;
  float rhvcoefxb ;
  float rhvcoefxc ;
  float rhvcoefxd ;
  float rhvcoefya ;
  float rhvcoefyb ;
  float rhvcoefyc ;
  float rhvcoefyd ;
  float rhvcoefza ;
  float rhvcoefzb ;
  float rhvcoefzc ;
  float rhvcoefzd ;
  float rhvenc ;
  int rhvibrant ;
  int rhviewSharing3D ;
  int rhvircoilchannels ;
  int rhvircoiltype ;
  int rhvircoilunif ;
  int rhvircpolicy ;
  int rhvirsenstype ;
  float rhvmcoef1 ;
  float rhvmcoef2 ;
  float rhvmcoef3 ;
  float rhvmcoef4 ;
  int rhvps ;
  int rhvquant ;
  int rhvrgf ;
  int rhvrgfxres ;
  int rhvtype ;
  int rhvvsaimgs ;
  int rhvvsgender ;
  int rhvvstr ;
  int rhwiener ;
  float rhwienera ;
  float rhwienerb ;
  float rhwieneresp ;
  float rhwienert2 ;
  float rhwnd_high_hist ;
  int rhwnd_image_hist_area ;
  float rhwnd_lower_hist ;
  float rhxoff ;
  float rhyoff ;
  float rhzeroph ;
  float rhzipfact ;
  int rl_flow ;
  int rot_delay ;
  int rot_delay_gir ;
  int rotateflag ;
  int rs_dda ;
  int rs_esp ;
  int rs_iso_delay ;
  int rs_off90 ;
  int rsamp_time ;
  int rsaxial_flag ;
  LOG_GRAD rsloggrd ;
  int rsphorder ;
  int rsspgr_flag ;
  int rst_exa ;
  int rst_exb ;
  int rtca_insteps_flip ;
  int rtca_insteps_fov ;
  float rtca_insteps_slthick ;
  float rtca_max_flip ;
  float rtca_max_fov ;
  float rtca_max_slthick ;
  float rtca_min_flip ;
  float rtca_min_fov ;
  float rtca_min_slabthick ;
  float rtca_min_slthick ;
  int rtia3d_buffers ;
  float rtia3d_eff_slabthick ;
  int rtia3d_irp_flag ;
  int rtia3d_original_flip ;
  int rtia3d_original_fov ;
  int rtia3d_original_slthick ;
  int rtia3d_pass ;
  int rtia3d_phorder ;
  int rtia3d_repeat_views ;
  int rtia3d_restricted_nav_flag ;
  float rtia3d_sat_flip ;
  float rtia3d_sat_pos ;
  int rtia3d_sat_views ;
  float rtia3d_slice_thinning_factor ;
  int rtia3d_thkslab_proj_enable_flag ;
  int rtia3d_thkslab_proj_flag ;
  int rtia3d_turbo ;
  int rtia_first_scan_flag ;
  float rtia_fov_freq_scale ;
  float rtia_fov_phase_scale ;
  float rtia_init_phasoff ;
  float rtia_init_rloc ;
  float rtia_init_tloc ;
  float rtia_orig_phasoff ;
  float rtia_orig_rloc ;
  float rtia_orig_tloc ;
  float rtia_rel_fov_freq_scale ;
  float rtia_rel_fov_phase_scale ;
  float rtia_satgapzneg ;
  float rtia_satgapzpos ;
  float rtia_slthick_scale ;
  int rtpend_quiet_dda ;
  int rtpresultwait ;
  int rtsar_enable_flag ;
  int rtsar_first_series_flag ;
  int run_eval_from_get_flag ;
  int rvssliceenc ;
  float s5fpharea ;
  int sampledPoints ;
  int sar_amp ;
  float sar_correction_factor ;
  int sar_cycle ;
  int sar_width ;
  int sat_TGlimit ;
  int sat_dda ;
  int sat_debug ;
  int sat_newgeo ;
  int sat_obl_debug ;
  int sat_pulse_type ;
  int sat_reps ;
  int sat_rot_df_num ;
  int sat_rot_ex_num ;
  int sat_rot_index ;
  float satgapxneg ;
  float satgapxpos ;
  float satgapyneg ;
  float satgapypos ;
  float satgapzneg ;
  float satgapzpos ;
  float satloce1 ;
  float satloce2 ;
  float satloce3 ;
  float satloce4 ;
  float satloce5 ;
  float satloce6 ;
  LOG_GRAD satloggrd ;
  float satspace1 ;
  float satspace2 ;
  float satspace3 ;
  float satspace4 ;
  float satspace5 ;
  float satspace6 ;
  float satspacex1 ;
  float satspacex2 ;
  float satspacey1 ;
  float satspacey2 ;
  float satspacez1 ;
  float satspacez2 ;
  float satthickdfx ;
  float satthickdfy ;
  float satthickdfz ;
  float satthickx1 ;
  float satthickx2 ;
  float satthicky1 ;
  float satthicky2 ;
  float satthickz1 ;
  float satthickz2 ;
  int satview ;
  float satxlocneg ;
  float satxlocpos ;
  float satylocneg ;
  float satylocpos ;
  float satzloca ;
  float satzlocb ;
  float satzlocneg ;
  float satzlocpos ;
  int save_cfxfull ;
  float save_cfxipeak ;
  int save_cfyfull ;
  float save_cfyipeak ;
  int save_cfzfull ;
  float save_cfzipeak ;
  int save_fft ;
  float save_gmax ;
  float save_gradOpt_TEfactor ;
  float save_gradOpt_TRfactor ;
  float save_gradOpt_ratio ;
  float save_gradOpt_scale ;
  int save_grad_spec_flag ;
  float save_ogsfX1 ;
  float save_ogsfX2 ;
  float save_ogsfXwex ;
  float save_ogsfY ;
  float save_ogsfYk ;
  float save_ogsfZ ;
  int save_ramptime ;
  float save_srate ;
  int savedata ;
  int saveinter ;
  float sbm_bak_pitscan ;
  int sbm_cvs_changed ;
  int sbm_cvs_old ;
  int sbm_dda ;
  int sbm_dda_max ;
  int sbm_dda_min ;
  int sbm_debug ;
  int sbm_dummy_num ;
  int sbm_flag ;
  int sbm_gradient_method ;
  float sbm_gx1_scale ;
  float sbm_gxw_scale ;
  float sbm_gxwex_scale ;
  float sbm_gy1_scale ;
  float sbm_gy1r_scale ;
  float sbm_gzcomb_scale ;
  float sbm_gzp_scale ;
  float sbm_margin ;
  int sbm_mps2_imaging_num ;
  int sbm_pitscan_changed ;
  float sbm_pitscan_limit ;
  float sbm_pitscan_old ;
  float sbm_smartderating_factor ;
  float sbm_sum_dummy ;
  float sbm_time_limit ;
  float sbm_time_limit_max ;
  float sbm_time_limit_min ;
  float sbm_time_limit_ratio ;
  float sbm_waiting_time ;
  int sbm_y_num ;
  int sbm_z_num ;
  float scale_fac ;
  float scale_tr ;
  float scale_tr_grad ;
  float scanclocktime ;
  int scanrcvr ;
  int scanrf1_inst ;
  int scanrf1tm_inst ;
  int scansat0 ;
  int scansatint ;
  int scptrg ;
  int seed ;
  int seeddef ;
  int seg_debug ;
  int seg_foundvps_flag ;
  int seg_sort_dir ;
  int seg_totalPEs ;
  int seg_vps_max ;
  int seg_vps_min ;
  int seg_vps_range ;
  int seg_vps_target ;
  int segment_tr ;
  int segmented_flag ;
  int sep3d ;
  int seq3ddummytr ;
  int seq3dtr ;
  int seqEntryIndex ;
  int seq_necho ;
  int seq_type ;
  int serviceMode ;
  int set_realtime_rotmat ;
  int show_rtfilts ;
  int si_flow ;
  int sifsetwokey ;
  float sigma1 ;
  float sigma2 ;
  int sigrammode ;
  int silent_mode ;
  float silent_slew_rate ;
  int simulation ;
  int skip_initialize_dbdtopt ;
  int skip_minseqseg ;
  int skip_navigator_prescan ;
  int skip_rotmat_search ;
  int skip_waveform_rotmat_check ;
  int sl_per_chem ;
  float slab_fact ;
  int slab_wrap_corr ;
  int slabtracking_flag ;
  int sldelay ;
  int sldeltime ;
  int slfreq ;
  int slice_col ;
  int slice_dda ;
  int slice_order ;
  int slice_size ;
  int slicecnt ;
  int slicezp ;
  int slorder ;
  int slq_shots ;
  int slquant1 ;
  int slquant_per_trig ;
  float slthick_rfgir01 ;
  float slthick_rfgir02 ;
  float slthick_scale ;
  int smartPrepEdrFlag ;
  int smartp_rtpend_wait ;
  int smartprep_flag ;
  int smartprep_was_on ;
  int smoothec ;
  int sp_first_scan ;
  int sp_sat ;
  int sp_satcard_loc ;
  int sp_satend ;
  int sp_satstart ;
  int sp_sattime ;
  int specdwells ;
  int specir_delay ;
  int specir_flag ;
  int specir_ti ;
  int specirsol ;
  int specnavs ;
  int specnex ;
  int specnuc ;
  int specpts ;
  int specsolreps ;
  int specwidth ;
  int spgr_flag ;
  int split_dab ;
  int sprep_debug_flag ;
  int sprep_save_raw_data ;
  int sprep_timing_flag ;
  int spsat_host_debug ;
  int spsat_rfupa ;
  int spsat_sys_type ;
  float spsp_min_opvthick ;
  float sr_flpvenc_limit ;
  float srate ;
  float srate_x ;
  float srate_y ;
  float srate_z ;
  float srderate ;
  int ss_convolution_flag ;
  int ss_fa_scale_debug ;
  int ss_fa_scaling_flag ;
  float ss_maxoff ;
  int ss_maxoffex ;
  float ss_min_slthk ;
  float ss_minslthk1 ;
  int ss_override ;
  float ss_psd_slthick ;
  int ss_rewinder_flag ;
  int ss_rf1 ;
  int ss_rf_wait ;
  int ssfat ;
  int ssfat_freq ;
  int ssfat_kaiser ;
  int ssfat_nullb ;
  int ssfat_ramp ;
  int ssfat_rfspoil ;
  int ssfat_rotate ;
  int ssfat_vo ;
  float ssfharea ;
  int ssfp_flag ;
  int ssfp_symmetry_flag ;
  int ssfse_ir_on ;
  int ssp_pwisi7 ;
  int sszchop ;
  float start_gycylra ;
  float start_gycylratipup ;
  float start_gzcylra ;
  float start_gzcylratipup ;
  float std_amp ;
  int steam_pg_gap ;
  int stopwatchFlag ;
  int stre_flag ;
  int sun_done_flag ;
  int sun_success_flag1 ;
  int sun_success_flag2 ;
  int swan_flag ;
  int swanfirstTE ;
  int swap_fat_cs ;
  int swap_mon_zy ;
  int swap_monplane ;
  int system_type ;
  int t1flair_flag ;
  float t2pk_area ;
  int t2pk_delay ;
  int t2prep_flag ;
  int t2prep_num180 ;
  float t2prep_rate ;
  int t2prep_t180 ;
  int t2prep_tseq ;
  int t_exa ;
  int t_exa_cylr ;
  int t_exaas ;
  int t_exb ;
  int t_exb_cylr ;
  int t_rd1a ;
  int t_rd1a_frac ;
  int t_rd1a_full ;
  int t_rdb ;
  int t_rdb_cylr ;
  int t_rdb_frac ;
  int t_rdb_full ;
  int t_slice2read ;
  int t_slicereadgap ;
  int ta_180sp ;
  int tableaccel ;
  int tabledecel ;
  int tablespeed ;
  float targ_dr ;
  float targ_dr_ramp ;
  float target_cfh_crusher ;
  float target_cfh_crusher2 ;
  int target_ti ;
  int tb_180sp ;
  int td0 ;
  int td0as ;
  int td0dtg ;
  int td0rs ;
  int tdaq ;
  int tdel1_time ;
  int tdel1_tmp ;
  int te_180sp ;
  int te_as ;
  int te_time ;
  float temp_factor ;
  float temp_float ;
  int temp_grd ;
  int temp_res_rf1as ;
  int temp_res_rf1cfh ;
  int temp_res_rf1cfl ;
  int temp_res_rf1ftg ;
  int temp_res_rf1mon ;
  int temp_res_rf2ftg ;
  int temp_res_rf2mon ;
  int temp_res_rf2mps1 ;
  int temp_res_rf2xtg ;
  int temp_res_rf3ftg ;
  int temp_res_rfmontipup ;
  int temp_res_rfse1 ;
  int temp_res_rfse2 ;
  int temp_res_rfse3 ;
  int temp_res_rfse4 ;
  int temp_res_rfse5 ;
  int temp_res_rfse6 ;
  int temp_res_rfsx1 ;
  int temp_res_rfsx2 ;
  int temp_res_rfsy1 ;
  int temp_res_rfsy2 ;
  int temp_res_rfsz1 ;
  int temp_res_rfsz2 ;
  int temp_rf ;
  int tfe_extra ;
  int tg_1_2_pw ;
  int tg_axial ;
  WF_PROCESSOR tg_killer_axis ;
  WF_PROCESSOR tg_read_axis ;
  int tgcap ;
  float tgfov ;
  int tgwindow ;
  float theta ;
  int thetatype ;
  float thickPS_mod ;
  float thk_rf0 ;
  float thk_rf0cfh ;
  float thk_rf1 ;
  float thk_rf1as ;
  float thk_rf1cfh ;
  float thk_rf1cfl ;
  float thk_rf1ftg ;
  float thk_rf1mon ;
  float thk_rf1tm ;
  float thk_rf2ftg ;
  float thk_rf2mon ;
  float thk_rf2mps1 ;
  float thk_rf2xtg ;
  float thk_rf3ftg ;
  float thk_rffrir ;
  float thk_rfgir01 ;
  float thk_rfgir02 ;
  float thk_rfmontipup ;
  float thk_rfse1 ;
  float thk_rfse2 ;
  float thk_rfse3 ;
  float thk_rfse4 ;
  float thk_rfse5 ;
  float thk_rfse6 ;
  float thk_rfsx1 ;
  float thk_rfsx2 ;
  float thk_rfsy1 ;
  float thk_rfsy2 ;
  float thk_rfsz1 ;
  float thk_rfsz2 ;
  int threedpktdly ;
  int ti_rfgir01 ;
  int ti_rfgir02 ;
  int time_between_rfflp180_venc ;
  int time_between_rfflp90_venc ;
  int time_between_venc1_2 ;
  int time_between_venc2_3 ;
  int time_between_venc_rfflp180 ;
  int time_between_venc_rfflp90r ;
  int time_fsprep ;
  int time_killer ;
  int time_pgen ;
  int time_s5fpprep ;
  int time_seqwait ;
  int time_spoiler ;
  int time_ssfprep ;
  int time_ssi ;
  int time_ssi_pre ;
  int time_ssias ;
  int time_ssidtg ;
  int time_ssirs ;
  int time_wait2 ;
  int time_wait3 ;
  int time_wait4 ;
  int timefcx ;
  int timefcy ;
  int timefcz ;
  int timefcz_echo1 ;
  int tlead ;
  int tlead_cylnav ;
  int tlead_monitor ;
  int tlead_montipup ;
  int tleadas ;
  int tleadcs ;
  int tleaddtg ;
  int tleadrs ;
  int tm_axis ;
  int tm_disdaqs ;
  int tm_flag ;
  float tm_flip ;
  float tm_locstep ;
  int tm_nex ;
  int tm_ns ;
  int tm_pos_start ;
  int tm_prepslice_flag ;
  float tm_scale ;
  float tm_slthick ;
  int tm_spiral_delay ;
  int tm_time ;
  float tm_xloc ;
  float tm_yloc ;
  int tmin ;
  int tmin_mon ;
  int tmin_montipup ;
  int tmin_reduced ;
  int tmin_satoff ;
  int tmin_total ;
  float tmpbw ;
  float tmpbw1 ;
  int tns_len ;
  int tnslength ;
  int tof_lowflip_asset_flag ;
  POSITION_DETECTION_DONE_TYPE topofhead ;
  int total_acq_points ;
  int total_acq_regions ;
  float total_area_gx ;
  float total_area_gxfc ;
  float total_area_gz ;
  float total_area_gzfc ;
  int total_quiet_dda ;
  int totalecregions ;
  int tr_as ;
  int tr_dtg ;
  int tr_pad ;
  int tr_prep_rs ;
  int tr_rs ;
  int track_flag ;
  int tracker_quant ;
  int transpose_monloc ;
  int tricks_check ;
  int tricks_debug ;
  int tricks_delay ;
  int tricks_flag ;
  int tricks_index ;
  int tricks_index2 ;
  float tricks_mask_time ;
  int tricks_maxecho ;
  int tricks_maxphases ;
  int tricks_maxseries ;
  int tricks_minecho ;
  int tricks_stop ;
  int tricks_transition_views ;
  int tricksdda ;
  int trig_aps2 ;
  int trig_mps2 ;
  int trig_prescan ;
  int trig_scan ;
  LONG triggerState ;
  int trigger_delay_silent_countdown ;
  int trigger_delay_wosp ;
  float truenex ;
  int tsamp ;
  int tseq_gzk ;
  int tseq_irprep ;
  int tseq_msde ;
  int tseq_prep_frir ;
  float tsp ;
  int turbo_cemra_enable ;
  int turbo_cemra_flag ;
  int turbo_flag ;
  int twaitt2prep ;
  int ugfsf_flag ;
  int ugfsf_flat_dda ;
  int ugfsf_linear_ramp_down ;
  int ugfsf_ramp_dda ;
  int ugfsf_shot_delay ;
  int ugfsf_slice_dda ;
  int ugfsf_slice_order_flag ;
  int ugfsf_view_order_flag ;
  COIL_INFO coilInfo_tgt[10] ;
  COIL_INFO volRecCoilInfo_tgt[10] ;
  DATA_ACQ_ORDER data_acq_order[2048] ;
  GIR_INFO gir_info[2] ;
  GRAD_PULSE gradx[15] ;
  GRAD_PULSE grady[24] ;
  GRAD_PULSE gradz[26] ;
  PHASE_OFF phase_off[2048] ;
  PSC_INFO presscfh_info[5] ;
  PSC_INFO psc_info[5] ;
  PSD_FILTER_GEN psd_filt_spec[16] ;
  RF_PULSE rfpulse[53] ;
  RF_PULSE_INFO rfpulseInfo[53] ;
  RSP_INFO asrsp_info[3] ;
  RSP_INFO dtgrsp_info[5] ;
  RSP_INFO mon_rsp_info2[1] ;
  RSP_INFO mon_rsp_info[1] ;
  RSP_INFO rsp_info[2048] ;
  RSP_INFO rsrsp_info[1] ;
  RSP_PSC_INFO rsp_psc_info[5] ;
  SCAN_INFO asscan_info[3] ;
  SCAN_INFO scan_info[2048] ;
  SCAN_INFO scan_info_base[1] ;
  SLAB_OFF slab_off[256] ;
  SPIRAL_VIEW brs_viewtab[131072] ;
  TX_COIL_INFO txCoilInfo_tgt[5] ;
  char hgzssfn[40] ;
  char piamval1[8] ;
  char piamval2[8] ;
  char piamval3[8] ;
  char piamval4[8] ;
  char piamval5[8] ;
  char piamval6[8] ;
  char pidfirecval2[30] ;
  char pidfirecval3[30] ;
  char pidfirecval4[30] ;
  char pidfirecval5[30] ;
  char pidifaxval1[7] ;
  char pidifaxval2[7] ;
  char pidifaxval3[7] ;
  char pidifaxval4[7] ;
  char pidifaxval5[7] ;
  char pidifaxval6[7] ;
  char pidifrecval1[30] ;
  char pitrecoverylabel[32] ;
  char ssgzfile[40] ;
  char ssrffile[40] ;
  float body_sar_table[360] ;
  float brs_mfa_angles[24] ;
  float eg_sat_rot[6][9] ;
  float extremity_sar_table[360] ;
  float flp_venc_x[8] ;
  float flp_venc_y[8] ;
  float flp_venc_z[8] ;
  float head_sar_table[360] ;
  float osfp_vfa[512] ;
  float ratio_rfflp180[4] ;
  float rfgir01_info[2][9] ;
  float rfgir02_info[2][9] ;
  float rhdiffusion_grad_amp[512][3] ;
  float rotmatrix[9] ;
  float xyz_base[2048][3] ;
  int PSfreq_offset[20] ;
  int PhaseDoneSchedule[513] ;
  int RegionSchedule[100] ;
  int RegionsSchedule[4561] ;
  int arcPhaseRemapTable[1025] ;
  int arcSliceRemapTable[2048] ;
  int brs_jumptab[1024] ;
  int brs_savrot[4096][9] ;
  int brs_xgrad2[16384] ;
  int brs_xgrad[16384] ;
  int brs_ygrad2[16384] ;
  int brs_ygrad[16384] ;
  int cum_regs_per_phase[513] ;
  int cum_views_per_region[32] ;
  int ectricks_kernel_regions[16] ;
  int ectricks_mask_regions[8] ;
  int extraspecial_slice[2048] ;
  int ia_gzvlwa[2048] ;
  int ia_gzvlwb[2048] ;
  int ia_rf1_osfp[512] ;
  int off_rfcsz[1] ;
  int off_rfcsz_base[2048] ;
  int pw_gzvl[2048] ;
  int pw_gzvla[2048] ;
  int pw_gzvld[2048] ;
  int regs_per_phase[513] ;
  int sat_rot_ex_indices[7] ;
  int slicetab[2048] ;
  int volumetab2[2048] ;
  int volumetab[2048] ;
  int zfctab[2048] ;
  int zfctab_echo1[2048] ;
  long int PSrot[1][9] ;
  long int PSrot_mod[1][9] ;
  long int dtgrsprot[5][9] ;
  long int ipg_alloc_instr[9] ;
  long int nav_channel_bit[4] ;
  long int navscm_channel_bit[4] ;
  long int rfgir01_rot_info[2][9] ;
  long int rfgir02_rot_info[2][9] ;
  long int rsp_PSrot[5][9] ;
  long int rsprot[4096][9] ;
  long int rsprot_base[4096][9] ;
  long int rsprot_gir[5][9] ;
  long int rsprot_monitor[1][9] ;
  long int rsptrigger[4096] ;
  long int rsrsprot[1][9] ;
  long int sat_rot_matrices[14][9] ;
  n32 mcbias_info[3] ;
  short int aslimgtab[3] ;
  short int aslnextab[3] ;
  int ulimte1 ;
  int ulimte2 ;
  int ulimte3 ;
  int unaccel_dayres ;
  int unaccel_rhnframes ;
  int uniPolar_flag ;
  int upmxdisable ;
  int useFirstEchoComp ;
  int use_dbdt_opt ;
  int use_ecg_scancore ;
  int use_ermes ;
  int use_myscan ;
  int use_slr_inv ;
  float usevenc ;
  int val15_lock ;
  float valid_decimation ;
  float valid_max_rbw ;
  float valid_rbw ;
  int value_system_flag ;
  int vas_ovrhd ;
  int vast_mode ;
  int vast_symm ;
  float velocity_3in1 ;
  float velocity_single ;
  float velocity_venc ;
  int venc_direction_bitmask ;
  int venc_polarity_mode ;
  int vibrant_flag ;
  int vibrantxv_flag ;
  int view_per_shot ;
  int view_to_center ;
  int viewoffs ;
  int views_per_segment ;
  int viewshd_num ;
  int viewsperregion ;
  float vol_ratio_est_req ;
  int vol_scale_constraint_type ;
  int vol_scale_type ;
  int vol_shift_constraint_type ;
  int vol_shift_type ;
  int vrg_sat ;
  int vrgfsamp ;
  int vrgsat ;
  int vstrte_flag ;
  int w_z1 ;
  int w_zfc ;
  int waitTime ;
  int wait_flpk ;
  int wait_pts ;
  int wg_cfh_rf3 ;
  int wg_cfh_rf4 ;
  int wg_csw_wait ;
  int wg_dix_ssppost ;
  int wg_dix_ssppre ;
  int wg_dix_xpre ;
  int wg_dummyrf ;
  int wg_gate_isi ;
  int wg_gx1 ;
  int wg_gx1as ;
  int wg_gx1bftg ;
  int wg_gx1bxtg ;
  int wg_gx1cfh ;
  int wg_gx1dtg ;
  int wg_gx1ftg ;
  int wg_gx1mon ;
  int wg_gx1mps1 ;
  int wg_gx1rs ;
  int wg_gx1tm ;
  int wg_gx2 ;
  int wg_gx2dtg ;
  int wg_gx2ftg ;
  int wg_gx2rs ;
  int wg_gx2test ;
  int wg_gxb ;
  int wg_gxbrsfc1 ;
  int wg_gxbrsfc2 ;
  int wg_gxfc ;
  int wg_gxfcmon ;
  int wg_gxflpk ;
  int wg_gxflpvenc ;
  int wg_gxhyst1 ;
  int wg_gxhyst2 ;
  int wg_gxkas ;
  int wg_gxkbsdtg ;
  int wg_gxkbsrs ;
  int wg_gxkcs ;
  int wg_gxkdtg ;
  int wg_gxkfs ;
  int wg_gxkill ;
  int wg_gxkrcvn ;
  int wg_gxkrs ;
  int wg_gxks ;
  int wg_gxkse1 ;
  int wg_gxkse2 ;
  int wg_gxkse3 ;
  int wg_gxkse4 ;
  int wg_gxkse5 ;
  int wg_gxkse6 ;
  int wg_gxksp ;
  int wg_gxkssf ;
  int wg_gxksx1 ;
  int wg_gxksx2 ;
  int wg_gxksy1 ;
  int wg_gxksy2 ;
  int wg_gxksz1 ;
  int wg_gxksz2 ;
  int wg_gxrf2cfh ;
  int wg_gxspoil ;
  int wg_gxspoil2 ;
  int wg_gxw ;
  int wg_gxw1ftg ;
  int wg_gxw1xtg ;
  int wg_gxw2 ;
  int wg_gxw2dtg ;
  int wg_gxw2ftg ;
  int wg_gxw2rs ;
  int wg_gxwas ;
  int wg_gxwdtg ;
  int wg_gxwex ;
  int wg_gxwmon ;
  int wg_gxwmps1 ;
  int wg_gxwrs ;
  int wg_gy1 ;
  int wg_gy1as ;
  int wg_gy1cfh ;
  int wg_gy1dtg ;
  int wg_gy1mon ;
  int wg_gy1mps1 ;
  int wg_gy1r ;
  int wg_gy1ras ;
  int wg_gy1rdtg ;
  int wg_gy1rrs ;
  int wg_gy1rs ;
  int wg_gy1tm ;
  int wg_gy2dtg ;
  int wg_gy2rs ;
  int wg_gyb ;
  int wg_gybrsfc1 ;
  int wg_gybrsfc2 ;
  int wg_gycylr ;
  int wg_gycylra ;
  int wg_gycylratipup ;
  int wg_gycylrtipup ;
  int wg_gyfe1 ;
  int wg_gyfe2 ;
  int wg_gyflpk ;
  int wg_gyflpvenc ;
  int wg_gyhyst1 ;
  int wg_gyhyst2 ;
  int wg_gykcfh ;
  int wg_gykcfl ;
  int wg_gykcs ;
  int wg_gykfs ;
  int wg_gykill ;
  int wg_gykrcvn ;
  int wg_gykse1 ;
  int wg_gykse2 ;
  int wg_gykse3 ;
  int wg_gykse4 ;
  int wg_gykse5 ;
  int wg_gykse6 ;
  int wg_gyksp ;
  int wg_gykssf ;
  int wg_gyksx1 ;
  int wg_gyksx2 ;
  int wg_gyksy1 ;
  int wg_gyksy2 ;
  int wg_gyksz1 ;
  int wg_gyksz2 ;
  int wg_gykxtgl ;
  int wg_gykxtgr ;
  int wg_gyrf0kcfh ;
  int wg_gyrf1mon ;
  int wg_gyrf1mps1 ;
  int wg_gyrf1tm ;
  int wg_gyrf1xtg ;
  int wg_gyrf2cfh ;
  int wg_gyrf2lmon ;
  int wg_gyrf2rmon ;
  int wg_gyrf3cfh ;
  int wg_gyspoil ;
  int wg_gyspoil2 ;
  int wg_gz1 ;
  int wg_gz1as ;
  int wg_gz1cfl ;
  int wg_gz1dtg ;
  int wg_gz1ftg ;
  int wg_gz1mon ;
  int wg_gz1mps1 ;
  int wg_gz1rs ;
  int wg_gz1s ;
  int wg_gz1xtg ;
  int wg_gz2bftg ;
  int wg_gz2ftg ;
  int wg_gz2xtg ;
  int wg_gz3ftg ;
  int wg_gzbrsfc1 ;
  int wg_gzbrsfc1echo1 ;
  int wg_gzbrsfc1echo2 ;
  int wg_gzbrsfc2 ;
  int wg_gzcomb ;
  int wg_gzcombhtr ;
  int wg_gzcylr ;
  int wg_gzcylra ;
  int wg_gzcylratipup ;
  int wg_gzcylrtipup ;
  int wg_gzflpk ;
  int wg_gzflpvenc ;
  int wg_gzk ;
  int wg_gzkas ;
  int wg_gzkbsdtg ;
  int wg_gzkbsrs ;
  int wg_gzkcs ;
  int wg_gzkdtg ;
  int wg_gzkfs ;
  int wg_gzkgir01 ;
  int wg_gzkgir02 ;
  int wg_gzkill ;
  int wg_gzkiller ;
  int wg_gzkmon ;
  int wg_gzkmontipup ;
  int wg_gzkrcvn ;
  int wg_gzkrffrir ;
  int wg_gzkrs ;
  int wg_gzks ;
  int wg_gzks5fp ;
  int wg_gzksp ;
  int wg_gzkssf ;
  int wg_gzp ;
  int wg_gzphtr ;
  int wg_gzptm ;
  int wg_gzrf0k ;
  int wg_gzrf1 ;
  int wg_gzrf1dtg ;
  int wg_gzrf1htr ;
  int wg_gzrf1mps1 ;
  int wg_gzrf1rs ;
  int wg_gzrf1s ;
  int wg_gzrf1xtg ;
  int wg_gzrf2lcfh ;
  int wg_gzrf2lmps1 ;
  int wg_gzrf2rcfh ;
  int wg_gzrf2rmps1 ;
  int wg_gzrf3lcfh ;
  int wg_gzrf3rcfh ;
  int wg_gzrf4cfh ;
  int wg_gzrf4lcfh ;
  int wg_gzrf4rcfh ;
  int wg_gzrfs5fph ;
  int wg_gzrfssfh ;
  int wg_gzs5fphcomb ;
  int wg_gzssfhcomb ;
  int wg_hard180 ;
  int wg_isi7 ;
  int wg_isi_cardiacsat ;
  int wg_isi_gir1 ;
  int wg_isi_gire01 ;
  int wg_isi_gire02 ;
  int wg_isi_girk01 ;
  int wg_isi_girk02 ;
  int wg_isi_sate1 ;
  int wg_isi_sate2 ;
  int wg_isi_sate3 ;
  int wg_isi_sate4 ;
  int wg_isi_sate5 ;
  int wg_isi_sate6 ;
  int wg_isi_satek1 ;
  int wg_isi_satek2 ;
  int wg_isi_satek3 ;
  int wg_isi_satek4 ;
  int wg_isi_satek5 ;
  int wg_isi_satek6 ;
  int wg_isi_satx1 ;
  int wg_isi_satx2 ;
  int wg_isi_satxk1 ;
  int wg_isi_satxk2 ;
  int wg_isi_saty1 ;
  int wg_isi_saty2 ;
  int wg_isi_satyk1 ;
  int wg_isi_satyk2 ;
  int wg_isi_satz1 ;
  int wg_isi_satz2 ;
  int wg_isi_satzk1 ;
  int wg_isi_satzk2 ;
  int wg_isi_slice1 ;
  int wg_isi_slice2 ;
  int wg_maps1 ;
  int wg_maps2 ;
  int wg_mapx ;
  int wg_mapy ;
  int wg_mapz ;
  int wg_mpomega_td0 ;
  int wg_mprho_td0 ;
  int wg_mpssp_td0 ;
  int wg_mptheta_td0 ;
  int wg_mpx_td0 ;
  int wg_mpy_td0 ;
  int wg_mpz_td0 ;
  int wg_omega_hs_rfcssat ;
  int wg_omega_ir0 ;
  int wg_omega_rffrir ;
  int wg_omega_rfgir01 ;
  int wg_omega_rfgir02 ;
  int wg_omegarf0cfh ;
  int wg_postgxw1ftg ;
  int wg_rcvn_wait ;
  int wg_rf0 ;
  int wg_rf0cfh ;
  int wg_rf1 ;
  int wg_rf180 ;
  int wg_rf1as ;
  int wg_rf1cfh ;
  int wg_rf1cfl ;
  int wg_rf1dtg ;
  int wg_rf1ftg ;
  int wg_rf1htr ;
  int wg_rf1mon ;
  int wg_rf1mps1 ;
  int wg_rf1rs ;
  int wg_rf1tm ;
  int wg_rf1xtg ;
  int wg_rf2cfh ;
  int wg_rf2ftg ;
  int wg_rf2mon ;
  int wg_rf2mps1 ;
  int wg_rf2xtg ;
  int wg_rf3cfh ;
  int wg_rf3ftg ;
  int wg_rf3xtg ;
  int wg_rf4cfh ;
  int wg_rf4xtg ;
  int wg_rf90 ;
  int wg_rfbdtg ;
  int wg_rfbrs ;
  int wg_rfcssat ;
  int wg_rfcylr ;
  int wg_rfcylrtipup ;
  int wg_rfflp180 ;
  int wg_rfflp180_the ;
  int wg_rfflp90 ;
  int wg_rfflp90_the ;
  int wg_rfflp90r ;
  int wg_rfflp90r_the ;
  int wg_rffrir ;
  int wg_rffs ;
  int wg_rfgir01 ;
  int wg_rfgir02 ;
  int wg_rfmontipup ;
  int wg_rfs5fph ;
  int wg_rfse1 ;
  int wg_rfse2 ;
  int wg_rfse3 ;
  int wg_rfse4 ;
  int wg_rfse5 ;
  int wg_rfse6 ;
  int wg_rfssf ;
  int wg_rfssfh ;
  int wg_rfsx1 ;
  int wg_rfsx2 ;
  int wg_rfsy1 ;
  int wg_rfsy2 ;
  int wg_rfsz1 ;
  int wg_rfsz2 ;
  int wg_rftipup ;
  int wg_rot_slice1 ;
  int wg_rot_slice2 ;
  int wg_rot_update_cardiacsat ;
  int wg_rot_update_e1 ;
  int wg_rot_update_e2 ;
  int wg_rot_update_e3 ;
  int wg_rot_update_e4 ;
  int wg_rot_update_e5 ;
  int wg_rot_update_e6 ;
  int wg_rot_update_ek1 ;
  int wg_rot_update_ek2 ;
  int wg_rot_update_ek3 ;
  int wg_rot_update_ek4 ;
  int wg_rot_update_ek5 ;
  int wg_rot_update_ek6 ;
  int wg_rot_update_gir ;
  int wg_rot_update_gire01 ;
  int wg_rot_update_girk01 ;
  int wg_rot_update_girk02 ;
  int wg_rot_update_rfgir02 ;
  int wg_rot_update_x1 ;
  int wg_rot_update_x2 ;
  int wg_rot_update_xk1 ;
  int wg_rot_update_xk2 ;
  int wg_rot_update_y1 ;
  int wg_rot_update_y2 ;
  int wg_rot_update_yk1 ;
  int wg_rot_update_yk2 ;
  int wg_rot_update_z1 ;
  int wg_rot_update_z2 ;
  int wg_rot_update_zk1 ;
  int wg_rot_update_zk2 ;
  int wg_rticfh ;
  int wg_sdixon ;
  int wg_sdixon2 ;
  int wg_sticfh ;
  int wg_thcylr ;
  int wg_thcylrtipup ;
  int wg_thetarfbdtg ;
  int wg_thetarfbrs ;
  int wg_xdelay ;
  int wg_xdixon ;
  int wg_xrespgate ;
  int wg_xticfh ;
  int wg_y_ccs_null ;
  int wg_ydixon ;
  int wg_yticfh ;
  int wg_zdixon ;
  int wg_zticfh ;
  int whichss ;
  int write_spinfo ;
  float xa2s ;
  float xfd_power_limit ;
  float xfd_temp_limit ;
  int xgd_optimization ;
  int xkiller_set ;
  int xlFOV_flag ;
  float xmtadd ;
  float xmtaddAPS1 ;
  float xmtaddCFH ;
  float xmtaddCFL ;
  float xmtaddFTG ;
  float xmtaddRCVN ;
  float xmtaddRef ;
  float xmtaddScan ;
  float xmtaddXTG ;
  float xmtaddas ;
  float xmtadddtg ;
  float xmtaddrs ;
  float xmtlogas ;
  int xres ;
  int xres2use ;
  int xres_ann_off ;
  int xres_ann_on ;
  int xtg_dda ;
  int xtg_disabled ;
  int xtg_offres_freq ;
  int xtg_volRecCoil ;
  float xtgscale ;
  int xtgtr ;
  int xtr_offset ;
  float ya2s ;
  int yfe_time ;
  float yfov_aspect ;
  int yoffs1 ;
  int yres_phase ;
  float za2s ;
  int zchop ;
  int zgmn_type ;
  int zkiller_flag ;
  int zoffs ;
  int zoffs1 ;
  int zrewind_flag ;
  int zsign ;
  float zslab ;
  int zy_export_debug_files ;
  int zy_slices ;
  int zy_views ;
} cv_type;
int write_cvs(char *filename);
#endif

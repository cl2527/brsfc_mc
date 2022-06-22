/*
 * GE Healthcare
 * Copyright (C) 2006 The General Electric Company
 *
 * efgre3d_support.h
 *
 * Language : ANSI C
 * Author   : Charles Michelich
 * Date     : May 11, 2006
 */

#ifndef efgre3d_support_h
#define efgre3d_support_h

/* Header files to satisfy types used in this file */
#include "stddef_ep.h" /* for STATUS, INT, FLOAT */
#include "3dgre_support.h" /* for ZY_EXPORT */

/*-------------------- Defines and type definitions -------------------- */

/* define some phase acquisition order parameters */
#define SEQUENTIAL 0
#define CENTRIC 1
#define REVERSE_CENTRIC 2
#define REVERSE_SEQUENTIAL 3

/* Enumerated value for encode group */
#define ENCODE_GROUP_NONE 0
#define ENCODE_GROUP_ZY 1
#define ENCODE_GROUP_YZ 2

/* Enumerated value for CAL_PARAM shape field */
#define CROSS_CAL 0
#define BOX_CAL 1
#define ELLIPTICAL_CAL 2

#define PHASETHENSLICE 0
#define SLICETHENPHASE 1

/* ARC_UNUSED_ENCODE: Value for unused view and slices in
                      phRemapTable and slRemapTable */
#define ARC_UNUSED_ENCODE -1

/* Bit fields of arc_pack_bam and packBamFlag */
#define BAM_PACK_Y 0x0001
#define BAM_PACK_Z 0x0002
#define BAM_REDUCE_Y 0x0004
#define BAM_REDUCE_Z 0x0008

/* Enumeration for the view ordering scheme */
typedef enum VIEWORDER_MODE
{
    VIEWSHARING_OFF = 0, /* this means view-sharing disabled */
    DISCO_ORDER = 1
} VIEWORDER_MODE_E;

typedef enum REG_VIEWORDER_MODE
{
    REGULAR = 0, /* this non-interleave */
    INTERLEAVE = 1
} REG_VIEWORDER_MODE_E;

typedef enum REGION_ORDER_MODE
{
    CENTER_REGION_FIRST = 0, /* A B1 A B2 A B3 A B1 ... */
    OUTER_REGION_FIRST = 1 /* B1 A B2 A B3 A B1 A ... */
} REGION_ORDER_MODE_E;

/* Calibration region related parameters for writeKacq() and
   generateZyExport() */
typedef struct cal_param {
    INT shape;            /* Calibration shape */
    INT phaseCutoffUpper; /* First phase encode in cal region (0-based) */
    INT phaseCutoffLower; /* Last phase encode in cal region (0-based) */
    INT sliceCutoffUpper; /* First slice encode in cal region (0-based) */
    INT sliceCutoffLower; /* Last slice encode in cal region (0-based) */
    /* The following fields are for .shape == ELLIPTICAL_CAL */
    FLOAT phaseRadius;    /* Inclusive y ellipse radius (# of encodes) */
    FLOAT sliceRadius;    /* Inclusive z ellipse radius (# of encodes) */
    FLOAT phaseOrigin;    /* y ellipse origin (0-based index) */
    FLOAT sliceOrigin;    /* z ellipse origin (0-based index) */
} CAL_PARAM;

#define MAX_NUM_REGIONS 32
typedef struct param4d {
    VIEWORDER_MODE_E vieworder_mode;
    float aregion_fraction;
    int num_outer_regions;
    int num_sub_regions;
    int smoothec;
    int views_per_region[MAX_NUM_REGIONS];
    float num_transition_fraction;
    int reverse_first_region_flag;
    int regViewOrderMode;
    int nr_of_segA;
} PARAM4D;

/* Bit-masks for flags fields for ZY_EXPORT structure */
#define ZY_FLAGS_XZ_DONE    0x0001
#define ZY_FLAGS_CAL        0x0002
#define ZY_FLAGS_SAMPLED    0x0004
#define ZY_FLAGS_MASK       0x0008
#define ZY_FLAGS_SEG_START  0x0010

/* SVBranch HCSDM00092046  Initial promote to support SBM */
#define HEAT_NEX1           0x0020
#define HEAT_NEX2           0x0040
#define HEAT_NEX3           0x0080
#define HEAT_NEX4           0x0100
#define HEAT_NEX5           0x0200
#define HEAT_NEX6           0x0400


/* ----------------------Host and Target functions --------------------- */ 
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */

STATUS
copyKacqToMrraw(const CHAR *kacqFilenameSrc, const CHAR *kacqPath,
                const CHAR *kacqFilenameDst);

STATUS
writeKacq(const INT kx_peak_pos,
          const INT unaccelPhases,
          const INT unaccelSlices,
          const ZY_EXPORT *zy_export,
          const INT sampledPoints,
          const INT calibrationPoints,
          const INT maskPoints,
          const INT nEchoes,
          const INT nTemporalPhases,
          const INT dayres,
          const INT calEcho,
          const CAL_PARAM calRegion,
          const INT noSortFlag,
          const INT packBamFlag,
          const INT *phRemapTable,
          const INT *slRemapTable,
          const INT copyKacqToMrrawFlag,
          const INT kacqUid,
          const INT maxRy,
          const INT maxRz,
          const INT pfkr_yz_flag,
          const INT nr_of_segments,
          const INT views_per_segment,
          const PARAM4D *param4d);
/* ------------------------ Host only functions ------------------------ */
#ifdef HOST_TGT

STATUS
arcPackBam(INT *phRemapTable, INT *packedPhases,
           INT *slRemapTable, INT *packedSlices,
           const ZY_EXPORT *zyExport, const INT zyExportLength,
           const INT unaccelPhases, const INT unaccelSlices);

INT
calcPfkyzTotalUnaccel(const INT pfkPoints, const INT cutoffLower, const INT cutoffUpper,
                const FLOAT outerReductionFactor);

INT
calcAccelEncodeNum(const INT cutoffLower, const INT cutoffUpper, 
                   const INT unaccelEncodes, const FLOAT outerReductionFactor); 
 
STATUS
crossCalBoundary(INT *cutoffLower, INT *cutoffUpper,
                 const FLOAT orFactor, const INT upperLimit);

STATUS
generateZyExport(ZY_EXPORT * zy_export,
                 int * delay_ec_framesIO,
                 const int zy_views,
                 const int zy_slices,
                 const int ellipt_flag,
                 const int reverse_ellipt_flag,
                 const int radfb_flag,
                 const float fn,
                 const int pfky_total_unaccel,
                 const int pfkz_flag,
                 const int pfkz_total_unaccel,
                 const int pfkz_total,
                 const int pfkz_segments,
                 const int pfkz_views_per_segment,
                 const int pfkr_flag,
                 const float pfkr_fraction,
                 const int pfkr_yz_flag,
                 const int echo_sort_dir,
                 const int seg_sort_dir,
                 const float yFov,
                 const float zFov,
                 const int phaseres,
                 const int equant,
                 const int delay_ec_flag,
                 const int segmented_flag,
                 const int nr_of_segments,
                 const int views_per_segment,
                 const int encode_group,
                 const int phorder,
                 const int viewoffs,
                 const int rhnframes,
                 const int rhhnover,
                 const int slorder,
                 const int nsegments,
                 const int chemseqs,
                 const int chemseq0,
                 const int linestodiscard,
                 const int arc_flag,
                 const CAL_PARAM calRegion,
                 const float arc_ph_stride,
                 const float arc_sl_stride,
                 const int tricks_flag,
                 const int tricks_mask_regions,
                 const int tricks_transition_views,
                 const int ellipt_debug_files,
                 int *extraspecial_slice,
                 PARAM4D *param4d);

STATUS
setArcCalParams(CAL_PARAM *calMinRegion,
                int *cal_shape,
                int *arc_ph_mincalwidth,
                int *arc_sl_mincalwidth,
                int *arc_ph_calwidth,
                int *arc_sl_calwidth,
                int *arc_ph_callower,
                int *arc_ph_calupper, 
                int *arc_sl_callower,
                int *arc_sl_calupper, 
                const float arc_ph_maxstride,
                const float arc_sl_maxstride,
                const int user_arc_ph_calwidth,
                const int user_arc_sl_calwidth,
                const int user_cal_shape,
                const int ctrl_calparams_flag,
                const int fullPhase,
                const int fullSlice,
                int research_flag);

STATUS
splitArcFactor(const float opgem_factor,
               const float fullPhase, 
               const float fullSlice, 
               const int cal_shape, 
               const float phLimit, 
               const float slLimit, 
               const float arc_maxnetaccel, 
               const float arc_recnetaccel, 
               const float arc_reclimnetaccel, 
               const float arc_phmaxslreclim_netaccel, 
               const float arc_ph_maxnetaccel, 
               const float arc_sl_maxnetaccel, 
               const float arc_ph_recstride, 
               const float arc_sl_recstride,                
               const float arc_ph_reclimstride, 
               const float arc_sl_reclimstride, 
               const float arc_ph_recnetaccel, 
               const float arc_sl_recnetaccel, 
               const float arc_ph_reclimnetaccel, 
               const float arc_sl_reclimnetaccel, 
               const int opautogem_factor,
               const int arc_ph_intaccel,
               const int arc_sl_intaccel,
               const int calibrationPoints,
               const int arc_ph_mincalwidth,
               const int arc_sl_mincalwidth,
               float *arc_netaccel, 
               float *arc_ph_factor, 
               float *arc_ph_stride, 
               float *arc_sl_factor, 
               float *arc_sl_stride,
               int *arc_ph_calwidth, 
               int *arc_sl_calwidth);


STATUS
setMaxArcFactor(const float phLimit,
                const float slLimit,
                const float phRecStride,
                const float slRecStride,
                const float phRecLimStride,
                const float slRecLimStride,
                const float fullPhase,
                const float fullSlice,
                const CAL_PARAM calMinRegion,
                float *arc_phmaxslrec_netaccel,
                float *arc_maxnetaccel,
                float *arc_ph_maxnetaccel,
                float *arc_sl_maxnetaccel,
                float *arc_recnetaccel,
                float *arc_reclimnetaccel,
                float *arc_ph_recnetaccel,
                float *arc_sl_recnetaccel,
                float *arc_ph_reclimnetaccel,
                float *arc_sl_reclimnetaccel);


STATUS
setAutoArcFactor(const float phLimit,
                 const float slLimit,
                 const int higherOuterAccel,
                 float *arc_ph_recstride,
                 float *arc_sl_recstride,
                 float *arc_ph_reclimstride,
                 float *arc_sl_reclimstride);

STATUS
walkSamplingPattern(int *sampledPoints, 
                    int *sampledPointsNoMask,
                    int *calibrationPoints,
                    int *maskPoints,
                    const int zy_views,
                    const int zy_slices,
                    const float fn,
                    const int pfky_total_unaccel,
                    const float pfkz_fraction,
                    const int pfkz_total_unaccel,
                    const float pfkr_fraction,
                    const float yFov,
                    const float zFov,
                    const int phaseres,
                    const int equant,
                    const int arc_flag,
                    const CAL_PARAM calRegion,
                    const float arc_ph_stride,
                    const float arc_sl_stride);

FLOAT
calcTargetAmp(const FLOAT targetArea,
              const FLOAT slewRate,
              const INT targetDuration,
              const FLOAT targetAmpMin,
              const FLOAT targetAmpMax,
              const FLOAT startAmp,
              const FLOAT endAmp,
              const INT bridge_flag);

FLOAT
calcTargetAmp2(const FLOAT targetArea1,
               const FLOAT targetArea2,
               const FLOAT slewRate,
               const INT targetDuration,
               const FLOAT targetAmpMin,
               const FLOAT targetAmpMax);

INT
calcDuration(const FLOAT targetArea,
             const FLOAT slewRate,
             const INT bridge_flag,
             const FLOAT startAmp,
             const FLOAT endAmp,
             const FLOAT targetAmp);

FLOAT
calcPower(const FLOAT targetArea,
          const FLOAT slewRate,
          const INT bridge_flag,
          const FLOAT startAmp,
          const FLOAT endAmp,
          const FLOAT targetAmp);

STATUS
setOptimizedGradientScalingFactor (const FLOAT a_gx1,
                                   const INT pw_gx1a,
                                   const INT pw_gx1,
                                   const INT pw_gx1d,
                                   const FLOAT a_gxfc,
                                   const INT pw_gxfca,
                                   const INT pw_gxfc,
                                   const INT pw_gxfcd,
                                   const FLOAT a_gxw,
                                   const INT pw_gxwa,
                                   const INT pw_gxw,
                                   const INT pw_gxwd,
                                   const FLOAT a_gxwex,
                                   const INT pw_gxwexa,
                                   const INT pw_gxwex,
                                   const INT pw_gxwexd,
                                   const FLOAT a_gy1a,
                                   const INT pw_gy1a,
                                   const INT pw_gy1_tot,
                                   const FLOAT a_gy1ra,
                                   const INT pw_gy1ra,
                                   const INT pw_gy1r_tot,
                                   const FLOAT a_gzrf1,
                                   const INT pw_gzrf1d,
                                   const FLOAT a_gz1,
                                   const INT pw_gz1a,
                                   const INT pw_gz1,
                                   const INT pw_gz1d,
                                   const FLOAT a_gzcomba,
                                   const INT pw_gzcomba,
                                   const INT pw_gzcomb,
                                   const INT pw_gzcombd,
                                   const INT pw_gzcomb_tot,
                                   const FLOAT a_gzpa,
                                   const INT pw_gzpa,
                                   const INT pw_gzp,
                                   const INT pw_gzpd,
                                   const INT gzptime,
                                   const INT phaseres,
                                   const FLOAT opfov,
                                   const FLOAT opphasefov,
                                   const FLOAT fov_phase_scale,
                                   const FLOAT asset_factor,
                                   const FLOAT nop,
                                   const INT equant,
                                   const FLOAT ethick,
                                   const FLOAT refocus,
                                   const INT aTEopt_flag,
                                   const INT aTRopt_flag,
                                   const INT gxwex_bridge,
                                   const FLOAT fecho_factor,
                                   const FLOAT GAM,
                                   const INT opfcomp,
                                   const FLOAT ogsfMin,
                                   const FLOAT ogsfMax,
                                   const FLOAT xTargetAmp,
                                   const FLOAT yTargetAmp,
                                   const FLOAT zTargetAmp,
                                   const FLOAT xkTargetAmp,
                                   const FLOAT ykTargetAmp,
                                   const FLOAT zkTargetAmp,
                                   const FLOAT slewRate,
                                   const INT method,
                                   const INT gradOpt_flag,    /* SVBranch HCSDM00100058 Set ogsf* based on gradOpt_flag */
                                   FLOAT *ogsfX1,
                                   FLOAT *ogsfXw,
                                   FLOAT *ogsfXwex,
                                   FLOAT *ogsfY,
                                   FLOAT *ogsfYk,
                                   FLOAT *ogsfZ,
                                   FLOAT *ogsfZk,
                                   FLOAT *powerTE,
                                   FLOAT *powerTR);

STATUS
calcMedalMaxXresMinFov( const float fov,
                        const float rbw,
                        const int cfsrmode,
                        const int cffield, 
                        const int cfgcoiltype,
                        const int axialBipolarVibrantDeFlag,
                        const int medalAutoTeFlag,
                        const int firstModeFlag,
                        const int silent,                /* SVBranch GEHmr04241 Dual Echo support ART */
                        const int silentlevel,
                        int * maxXres,
                        float * minFOV);

STATUS
isRefRegionValid(const int y_lower, 
                 const int y_upper,
                 const int z_lower,
                 const int z_upper,
                 const int zy_views,
                 const int zy_slices,
                 const float fn,
                 const int pfky_total_unaccel,
                 const float pfkz_fraction,
                 const int pfkz_total_unaccel,
                 const float pfkr_fraction,
                 const float yFov,
                 const float zFov,
                 const int phaseres,
                 const int equant,
                 const int arc_flag,
                 const CAL_PARAM calRegion);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HOST_TGT */

/* ------------------------ Target only functions ---------------------- */
#ifdef MGD_TGT

INT
arcGetDabEncode(const INT encode, const INT packBamFlag, const INT *remapTable);

STATUS
tricksWriteReconFiles( const int * regionSchedule,
                       const int regionScheduleLength,
                       const int maskRegions,
                       const ZY_EXPORT * zyExport,
                       const int zyExportLength);

#endif /* MGD_TGT */

#endif /* efgre3d_support_h */

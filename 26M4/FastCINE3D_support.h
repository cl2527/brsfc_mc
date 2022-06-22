/*
 * Copyright (c) 2016 by General Electric Company. All Rights Reserved.
 */

/**
 * \file FastCINE3D_support.h
 *
 * This is the header file for FastCINE3d support routines.
 *
 * @author  Peng Lai/ Ann Shimakawa
 * @since 26.0
 */

/*
 * Comments:
 * Date (dd mmm yyyy) Author (or Initials)
 * Comment
 *
 * 10 Mar 2016  PL/ AS
 * HCSDM00397174 Initial version.
 *
 */

#ifndef FastCINE3D_support_h
#define FastCINE3D_support_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Fast CINE kt samp mode  */
typedef enum e_ktsamp {
    KT_MODE       =  0,   /* kt mode  */
    VDKT_MODE     =  1,   /* Variable Density kt */
    ARC_MODE      =  2,   /* ARC */
} t_ktsamp;

/*note the short-integer limit; max(ky*kz)=65535*/
typedef struct
{
    short len;
    short *ky; /*view*/
    short *kz; /*slice*/
    float *kr; /*k-space radius*/
    short *ki; /*center-out index*/
} ViewTable_kyz;

/* number of acquired phases (APHASE)  */
/* note that this number affects  viewtable generation
 *    and associated structures            */
#define MAX_APHASE_3DCINE 32

/* number of reconstruced phases (CPHASE) */
#define MAX_CPHASE_3DCINE 64 

#define MAXACCEL_VDKT 15
#define MAXACCEL_KT  10
#define VDKT_INNER_FACTOR 0.5
#define VDKT_OUTER_FACTOR  1.25
#define VDKT_RING_SIZE  500.0
#define RESP_CENTK_MIN 9

#define pi 3.14159265

/************ genview routines ****************/
STATUS fcine_genvieworder_ktARC( int start_totalviews, int start_maxAphase,
       int accel_ktStride, int accel_ktSride_cal, int Cal_ky, int Cal_kz,
       int NkzLines, int NkyLines,  float fovVthickScale,
       int ViewsPerSeg,  int ElliptCal, int cutCorner,
       int RespPerCent, int respNex, int yz_sort_order,
       int ktsamp_mode, int kbandWidth, int kRewFlag,
       int *cine3dTotalviews, int *cine3dMaxAphases, ViewTable_kyz *pviewtable_kt );
STATUS fcine_prepviewtable_fullk(short Nky, short Nkz, short cal_ky, short cal_kz, int KTsamp_mode,
           float fov_vthick_scale, int ElliptFlag, int cutCorner, int resp_perC, int ktStride, int ktStride_cal,
           ViewTable_kyz* pViewOrder_vdkt, ViewTable_kyz* pViewOrder_vdkt_outer, ViewTable_kyz* pViewOrder_vdkt_cal,
           short* krOffset_vdkt_outer, short* krOffset_vdkt_cal, short* krAccel_vdkt_outer, short* krAccel_vdkt_cal);
STATUS fcine_genacceltable_vdkt(short * krAccel_vdkt, short * krOffset_vdkt, int accel,
                int accelLower, int accelUpper, short vieworder_len);

STATUS sortviews_vdkt(short * ky_sort, short * kz_sort, float * kr_sort,
     short * ki_sort, short num_views, short * kr_Accel,
     short yres, short zres, short * kr_offset);

void sort_vectors_mod(
                      int  index_start, /*  I  */
                      int  index_end,   /*  I  */
                      float* a,         /* I/O */
                      float* b,         /* I/O */
                      short* c,         /* I/O */
                      short* d,         /* I/O */
                      short* e          /* I/O */
);
short fcine_genkmask_ktARC(short *maskKTarc, short Nky, short Nkz, short cal_ky, short cal_kz, short t_index,
                           int ktStride, int ktStride_cal, int ElliptFlag, int cutCorner);
short fcine_genkmask_vdktARC(short *maskKTarc, short Nky, short Nkz, short t_index,
                             ViewTable_kyz* pViewOrder_vdkt_outer, ViewTable_kyz* pViewOrder_vdkt_cal,
                             short* pkrOffset_vdkt_outer, short* pkrOffset_vdkt_cal,
                             short* pkrAccel_vdkt_outer, short* pkrAccel_vdkt_cal,
                             short* pktShift_vdkt);

STATUS fcine_genrespmap(float *kr_list, short * rTraj, float * respFactor, short nCentKramp, short nCentKrect, float resp_para);
void fcine_OptiKrShift_vdktARC(short *ktShift);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

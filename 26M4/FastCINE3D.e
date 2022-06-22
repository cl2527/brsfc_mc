/*
 * Copyright (c) 2016 by General Electric Company. All Rights Reserved.
 */

/*
 * \file FastCINE3D.e
 *
 * 3DCINE / 4DFLOW with kt ARC for
 * time-resolved imaging using
 * variable-density viewtable with
 * k-t acceleration.
 *
 * @author  Peng Lai, Ann Shimakawa
 * @since 26.0
 */

/*
 * Comments:
 * Date (dd mmm yyyy) Author (or Initials)
 * Comment
 *
 * 10 Mar 2016  PL/ AS
 * HCSDM00397174 Initial version.
 */

@host fcine3d_global
#include "FastCINE3D.h"
#define GZKAREA_4DFLOW 1143.0

/* Cardiac Gating type */
typedef enum e_cgatetype {
    /* zero is OFF */
    TYPECG = 1,   /* ECG */
    TYPPG         /* Peripheral */
} t_cgatetype;

/* Fast CINE Interpolation Method */
typedef enum e_fcineim {
    LINEAR = 1,   /* Linear */
    NNEIGHBOR     /* Nearest Neighbor */
} t_fcineim;

/* Fast CINE Normalization type */
typedef enum e_fcinent {
    SYSDIAS = 1,  /* Systole-Diastole */
    UNIFORM       /* Uniform */
} t_fcinent;

/* Default number of phases to recontruct */
const INT FCINE_PHASE_DEF = 20;

/* Default arrhythmia rejection window */
const INT FCINE_ARW_DEF = 50;   /* +/-50% */

/* Maximum number of ky-lines for 3DCINE */
const INT FCINE_MAX_YRES = 420;

/* Maximum number of kx-points for 3DCINE */
const INT FCINE_MAX_XRES = 420;

/* Maximum number of slices/slab for 3DCINE */
const INT FCINE_MAX_SLQUANT = 120;

/* Maximum number of images for 3DCINE/4DFLow */
const INT FCINE_MAX_IMAGES= 50000;

/* Maximum VRE memory size */
const s64 MaxVREDataSize = 6000000000LL;

/* Define maximum latency for PAC trigger_delay update */
/* up to 4 TRs to ensure correct trigger_delay */
const INT FCINE_PAC_UPDATE_DELAY = 4;  

/* Define maximum trigger delay used to detect */
/* a trigger delay update from SPU     */
/* note that trigger delay units from SPU are in ms */
const INT FCINE_TRIGGER_DELAY_MAX = 10000;

/* Define criterion used to detected PAC latency trigger_delay update */
/* Correct minimum trigger delay is less than (max VCG delay + 1 TR)=~100ms  */
/* note that trigger delay units from SPU are in ms */
const INT FCINE_TRIGGER_DELAY_LIMIT = 100; 


/*********************************************************************
 *                      FASTCINE3D.E HOST SECTION                      *
 *                                                                   *
 * Write here the code unique to the Host PSD process. The followine *
 * functions must be declared here: cvinit(), cveval(), cvcheck(),   *
 * and predownload().                                                *
 *********************************************************************/


@cv fcine3d_cv
/*********************************************************************
 *                      FASTCINE3D.E CV SECTION                        *
 *                                                                   *
 * Standard C variables of _limited_ types common for both the Host  *
 * and IPG PSD processes. Declare here all the simple types, e.g,    *
 * int, float, and C structures containing the min and max values,   *
 * and ID description, etc.                                          *
 *                                                                   *
 * NOTE FOR Lx:                                                      *
 * Since the architectures between the Host and the IPG sides are    *
 * different, the memory alignment for certain types varies. Hence,  *
 * the following types are "forbidden": short, char, and double.     *
 *********************************************************************/
int cine3d_flag = 0 with {0,1,0,VIS,"flag to enable cine 3d acquisition",};
int flow4D_flag = 0 with {0,1,0,VIS,"flag to enable 4DFlow  acquisition",};
int ktarc_flag = 1 with {0,1,1,INVIS,"flag to enable kt ARC  acquisition -  ON for 3cdine/4dflow",};
/*****************************************/
int balanced_FE = -1 with {-1, 1, -1,VIS,"Flow encoding mode: 0-simple, -1-modified simple, 1-balanced",};
int cine3d_minslquant = 1 with {1,,0,INVIS,"minimum slices/slab for cine3d ",};
int cine3d_maxslquant = 1 with {1,,0,INVIS,"maximum slices/slab for cine3d ",};
int cgate_dda = 2 with {0,128,2,VIS,"number of ECGs used as disdaqs",};

/* Retrospective post processing CV's */
int fcineim = 2 with {
    0, 2, 2, VIS, "Fast CINE interpolation method "
                  "(0=None, 1=Linear, 2=Nearest Neighbor).",
};
int fcinent = 1 with {
    0, 2, 1, VIS, "Fast CINE normalization type "
                  "(0=None, 1=Systole-Diastole, 2=Uniform).",
};

/* variable density k-t sampling cv's */
int cine3d_ktsamp_mode = 0 with {0,2,1,VIS,"kt sampling mode (0: k-t; 1: VariDensity k-t; 2: ARC)",};

/* flag for kat ARC acquisition */
int accel_kt_cal_stride = 2 with {1,4,2,VIS,"kt ARC ACS acceleration",};
int accel_outer2cal_factor = 3 with {1,5,3,VIS,"reduction factor of kt ARC outer to ACS acceleration",};
int cal_ky_ktarc = 16 with {12,32,16,VIS,"kt ARC CAL width along ky",};
int cal_kz_ktarc = 16 with {4,32,16,VIS,"kt ARC CAL width along kz",};
int cutcorner_flag = 1 with {0,1,1,VIS,"flag for k-space corner cutting",};

/* virtual coil for reconstruction */
int num_virchan = 8 with {1,128,8,VIS,"Number of virtual coils for reconstruction",};

/* for smooth k-space trajectory */
int kband_width = 2 with {1,10,2,VIS,"k-space subband width for smooth trajectory",};
int krewind_flag =  1 with {0,1,1,VIS,"flag for rewinding k-space trajectory",};
int cine3d_yz_order = 1 with {0,1,1,VIS,"Enable YZ order instead of ZY order",};

/* for respiratory nex mode and scan time calculations */
int resp_nex = 1 with {1,10,1,VIS,"NEX used for center of k-space -- from U/I",};
int resp_centk_percent = 10 with {0,100,10,VIS," percentage of kspace oversampled with NEX",};

/* Fast CINE variables  */
int aphases_max = 1 with {1, 512, 16, VIS, "Max number of acquired phases.",};

int cine3d_targetedphases_max = 10 with {1, 32, 10, INVIS, "Max number of acquired phases.",};
int cine3d_totalviews_est = 512 with {1,,512, INVIS, "Estimted total views  for host functions ",};
int cine3d_fullkviews  = 512 with {1,, 512, INVIS, "number of views for unaccelerated scan per phase",};
int cine3d_fullkviews_cal  = 512 with {1, , 512, INVIS, "number of Hyperkat cal views per phase ",};
int cine3d_num_segs_est  = 512 with {1, , 512, INVIS, "Estimted total segments for host functions ",};
float cine3d_arrlimit = 0.5 with {0.0, 10.0 , 0.5, VIS, "fraction of total views allowed for arrythmias",};

/*  variables for genview_ktarc */
int genview_totalviews  = 512 with {1, , 512, INVIS, " initial estimate number of view for Hyperkat viewtab generation",};
int genview_maxaphase  = 512 with {1, , 512, INVIS, "  Initial estimate of acq phases for Hyperkat viewtab generation",};
int genview_ellipt_cal  = 1 with {0,1,0, INVIS, " elliptical cal flag for Hyperkat viewtab generation ",};
float genview_fovVthick_scale = 1.0 with {0.0, ,1.0, INVIS, "normalization factor for k-space distance calc in Hyperkat viewtab generation  ",};

/** CVs for flow encoding **/
int nflow4D = 1 with {1,4,1, INVIS, " number of flow encodes for 4dflow ",};
/* for complete flow encoding acquisition 4*/
int CompleteEchoLoop_flag = 1 with {0,1,1,VIS,"flag for noninterrupted flow encoding echo loop",};

/* for phase contrast flow encode   - taken from 3dpchon.e */
int negx = 0 with {0,1,0, INVIS, " logic for inverted x grad ",};
int negy = 0 with {0,1,0, INVIS, " logic for inverted y grad ",};
int negz = 0 with {0,1,0, INVIS, " logic for inverted z grad ",};
int opflaxxa = 0 with {0,,0,INVIS, "X grad flow encode",};
int opflaxya = 0 with {0,,0,INVIS, "Y grad flow encode",};
int opflaxza = 0 with {0,,0,INVIS, "Z grad flow encode",};
float usevenc = 0 with {0,,0,INVIS, "peak flow encode velocity" ,};

float pc_const = 1.0 with {,,,INVIS, "useful constant for phase contrast" ,};   
float scale_fac = 1.0 with {,,,INVIS, "Scale factor for phase contrast images" ,};
int minpcflattop = 4 with {,,,INVIS, "minimum flattop of flow encode gradient" ,};
float gxfctarget = 1.0 with {,,,INVIS, "Target amplitude for flow encode X gradient" ,};
float gyfctarget =1.0 with {,,,INVIS, "Target amplitude for flow encode Y gradient" ,};
float gzfctarget =1.0 with {,,,INVIS, "Target amplitude for flow encode Z gradient" ,};    
int pw_rampx = 4 with {,,,INVIS, "Max ramp time for X  flow encode gradient" ,};
int pw_rampy = 4 with {,,,INVIS, "Max Ramp time for Y  flow encode gradient" ,};
int pw_rampz = 4 with {,,,INVIS, "Max ramp time for Z  flow encode gradient" ,};

/***use the target derating to reduce the gradient heating***/
float targ_dr = 0.8 with {0.1,1.0,0.5,VIS,"Derating factor for flow-encoding gradients",};
float  targ_dr_ramp = 2.0 with {1.0,5.0,1.0,VIS,"Scaling factor for min ramp time on Flow Encoding Gradients",};

int w_z1 = 4 with {,,,INVIS, "z1 flow encode gradient widthj" ,};
int w_zfc = 4 with {,,,INVIS, "zfc flow encode gradient width" ,};

float flow_wdth_z = 1.0 with {,,,INVIS, "fixed area for z flow enc: 'w' in ASL Tech note 90-08" ,};
float flow_wdth_x = 1.0 with {,,,INVIS, "fixed area for x flow enc: 'w' in ASL Tech note 90-08" ,};
float flow_wdth_y = 1.0 with {,,,INVIS, "fixed area for y flow enc: 'w' in ASL Tech note 90-08" ,};
float fl_width_x_full  = 1.0 with {,,,INVIS, "fixed area for x flow enc: full TE" ,};
float fl_width_x_frac  = 1.0 with {,,,INVIS, "fixed area for x flow enc: Frac TE" ,};

int min_tegy  = 4 with {,,,INVIS, "Minimum TE on Y grad" ,};
int min_tegz = 4 with {,,,INVIS, "Minimum TE on Z grad" ,};

int gz_time = 4 with {,,,INVIS, "Flow & spatial  encode time require for Z grad" ,};
int yfe_time = 4 with {,,,INVIS, "Flow & spatial encode time require for Y grad" ,};

/* gradient waveform variables */
int pw_gyfe, pw_gyfea, pw_gyfed;
float a_gz1u, a_gzfcd, a_gx1u, a_gxfcu, a_gx1d, a_gxfcd, a_gyfe;
float a_gx1u_full, a_gx1u_frac,a_gx1d_full, a_gx1d_frac;
float a_gxfcu_full, a_gxfcu_frac,a_gxfcd_full, a_gxfcd_frac;
float a_gz1d, a_gzfcu;

float a_gzfcbase, a_gzfccomb, a_gzfcend, act_scamp;
float a_gzkbase, a_gzkcomb, a_gzkend;

int ia_gyfe, ia_gz1u, ia_gz1d, ia_gzfcu, ia_gzfcd, ia_gx1u,ia_gx1d;
int ia_gx1feu, ia_gx1fed, ia_gx1fen, ia_gx2feu, ia_gxfcd, ia_gxfcu;
int ia_gx2fed,ia_gx2fen, ia_gy1feu, ia_gy1fed, ia_gy1fen, ia_gy2feu;
int ia_gy2fed, ia_gy2fen, ia_gz1feu, ia_gz1fed, ia_gz1fen, ia_gz2feu;
int ia_gz2fed, ia_gz2fen, ia_gzfccomb, ia_gzfcbase, ia_gzfcend;


@host fcine3d_cvinit
if(cine3d_flag) 
{
    int numRec = 0, Hyperk_max_4dflow = 0, Hyperk_max_3dcine = 0, Hyperk_max =  0;

    /* Activate Fast CINE by redefining max val */
    cvmax(opfcine,1);
    opfcine = PSD_ON;
   
    /* set defaults for cardiac gating/cine page */
    pihrepnub=0;       
    cvdef(ophrep,1);

    piviewseg = 0;
    cvmin(opvps, 1 );
    opautovps = PSD_ON;


    /* Trigger delay */
    pitdel1nub = 0;       /* bitmap for pulldown menu  */

    piaccel_slnub = 0;               /*turn off all EXCEPT HyperKat*/
    piaccel_phnub = 0;

    numRec = (rhdab0e-rhdab0s+1);    /* determine hyperkat limits */
    if (numRec > 16 )
    {
        Hyperk_max_4dflow = 8;
        Hyperk_max_3dcine = 9;
    }
    else
    {
        Hyperk_max_4dflow = 6;
        Hyperk_max_3dcine = 8;
    }
    num_virchan = IMin(2, 8, numRec);

    Hyperk_max = ((flow4D_flag) ?  Hyperk_max_4dflow : Hyperk_max_3dcine);

    avmaxaccel_kt_stride = (float)Hyperk_max;
    avminaccel_kt_stride = 1.0; 
    cvdef(opaccel_kt_stride, (int)avmaxaccel_kt_stride);
    cvmin(opaccel_kt_stride, 1);
    cvmax(opaccel_kt_stride,  Hyperk_max);  
    piaccel_kt_stride = _opaccel_kt_stride.defval;    /* Displayed temporal acceleration */

    /* inter-seq. delay, not used */
    pitseqnub=0;                        /* gray out */
    optseq = 1;
    setexist(optseq,PSD_ON);

    /*  U/I values set after acceleration is defined*/
    /* Catch over-ranges in PSD with error messages */
    avmaxphases = MAX_CPHASE_3DCINE;
    avminphases = 1;
    cvdef(opcphases, 20);
    cvmax(opcphases, MAX_CPHASE_3DCINE);
    cvmin(opcphases,  1);
    pifcinedefval =  _opcphases.defval;

    avminaphases = 1;
    avmaxaphases = MAX_APHASE_3DCINE;
    cvdef(opaphases, 12 );
    cvmax(opaphases, MAX_APHASE_3DCINE);
    cvmin(opaphases, 1);
    piaphasdefval =  _opaphases.defval;

    cvdef( oparr, FCINE_ARW_DEF );
    pidefarr = FCINE_ARW_DEF;
    oparrmon = arr_check;
    piadvcard = (1<<PSD_ADVMAXPHASES) +  (1<<PSD_ADVAVAILIMGTIME);

} else {

    cvmax(opfcine,0);   /* turn off UI for reconstructed phases and acquired phases */
    cvoverride(opfcine,PSD_OFF,PSD_FIX_OFF,PSD_EXIST_ON);

    cvoverride(opvps,1,PSD_FIX_OFF,PSD_EXIST_ON);

    piaccel_ktnub = 0;		/* reset defaults from epic.h */
    piaccel_kt_stride = 1;     
    cvoverride(opaccel_kt_stride, 1,PSD_FIX_OFF,PSD_EXIST_ON);
  
    pifcinenub = 0;
    avminphases = 1;
    cvmin(opcphases,  1);
    cvoverride(opcphases,1 ,PSD_FIX_OFF,PSD_EXIST_OFF);

    piaphasenub = 0;
    avminaphases = 1;
    cvmin(opaphases, 1);
    cvoverride(opaphases, 1,PSD_FIX_OFF,PSD_EXIST_OFF);

    oparrmon = 0; 
    piautophasenub = 1;
    opautovps = PSD_OFF;
}


@host fcine3d_cvevalinit
if ( cine3d_flag )
{   int temp_int = 0;

    piaccelscrn = PSD_ON;            /* turn on Accleration Tab */
    piaccel_slnub = 0;               /* turn off all EXCEPT HyperKat*/
    piaccel_phnub = 0;   

    accel_ph_defstride = 1.0;        /* Default (initial) phase acceleration.*/
    accel_sl_defstride = 1.0;        /* Default (initial) slice acceleration.*/

    piaccel_mbnub = 0;
    piaccel_csnub = 0;

    cvdef(opaccel_kt_stride, (int)avmaxaccel_kt_stride);
    piaccel_ktnub =  5;    /* Bitmask for temporal acceleration menu.*/
    piaccel_kt_stride = _opaccel_kt_stride.defval;    /* Displayed temporal acceleration */
    piaccel_ktedit = 1;    /* Temporal UI Edit mode 0: Only UI pulldown 1:User can Rx Ph Accel */
    piaccel_ktval2 = (int)avmaxaccel_kt_stride - 3;    /* Temporal acceleration menu item 3 */
    piaccel_ktval3 = (int)avmaxaccel_kt_stride - 2;    /* Temporal acceleration menu item 4 */
    piaccel_ktval4 = (int)avmaxaccel_kt_stride - 1;    /* Temporal acceleration menu item 5 */
    piaccel_ktval5 = (int)avmaxaccel_kt_stride;        /* Temporal acceleration menu item 6 */
 
    picineiprot = 0;

    /* treat acq as ARC with no acceleration for full sampling */
    if(exist(opaccel_kt_stride) == 1)
    {
        cine3d_ktsamp_mode = ARC_MODE;
    } else
    {
       cine3d_ktsamp_mode = VDKT_MODE;
    }

    if ( (cine3d_ktsamp_mode == KT_MODE) || (cine3d_ktsamp_mode == VDKT_MODE) )
    {   int kt_aphase=0;
        if (cine3d_ktsamp_mode == VDKT_MODE)
        {
             kt_aphase=2;
        }
        else
        {
            kt_aphase=0;
        }
        avminaphases = exist(opaccel_kt_stride) + kt_aphase;
    }
    else
    {
       avminaphases = 1;
    }
    cvmin(opaphases, avminaphases);
    temp_int = IMax(2, avminaphases, 12);
    cvdef(opaphases, temp_int);
    piaphasenub = 5;
    piaphasdefval = _opaphases.defval;
    piaphaseval2 = avminaphases;
    piaphaseval3 = 16;
    piaphaseval4 = 20;

    piautophasenub = 0;

    avminphases = IMax(2, avminaphases, exist(opaphases));
    cvmin(opcphases, avminphases);
    temp_int = IMax(2, avminphases, 20);
    cvdef(opcphases, temp_int);
    pifcinenub = 3;
    pifcinedefval = _opcphases.defval;
    pifcineval2   = avminphases;
    pifcineval3   = 20 ;
    pifcineval4   = 25;
   
    /* allow multi-slab */
    pimultislab = PSD_ON;
    pimultigroup = PSD_OFF;

    if (flow4D_flag) 
    {
       /* ***********************************************
           Vascular related calculations are done here
        ********************************************* */
        cvdef(opvenc, 200.0);

        negx = (opflaxx & 8)? PSD_ON:PSD_OFF;
        negy = (opflaxy & 8)? PSD_ON:PSD_OFF;
        negz = (opflaxz & 8)? PSD_ON:PSD_OFF;
        opflaxxa = opflaxx - 8*negx;
        opflaxya = opflaxy - 8*negy;
        opflaxza = opflaxz - 8*negz;
        usevenc = exist(opvenc);
        pc_const = (1e12)*10.0/((FLOAT)GAM*usevenc);

        maxpc_cor = PSD_ON;  /* turn on maxwell correction */
       /*****************************/
    } 
    else 
    {
        pc_const = 0.0;
        maxpc_cor = PSD_OFF;
    }

    if(exist(opnex) > 1)   /* center k-space NEX-ing */
    {
        resp_centk_percent = IMin(2, 100, (INT)exist(opuser16));
        resp_nex = IMax(2, 2, (INT)exist(opnex));
    }
    else
    {
        resp_centk_percent = (exist(oprtcgate) == PSD_ON)? 100:0;
        resp_nex = 1;
    }

    piuset &= ~use23;
    cvoverride(opuser23,100.0,PSD_FIX_ON,PSD_EXIST_ON);
}

@host fcine3d_cveval
if ( cine3d_flag )
{   int cine3d_temp_int=0, avail_imagetime=0;

    if (exist(opvquant) > 1) {
       piovlnub = 3;   /* overlap slices bit map */
    } else {
       piovlnub = 0;
    }
    pidefslq = 24;
    pipctovl = 2;
    pidefovl = 0; 

    cine3d_minslquant = 2*( ceil(sqrt(exist(opaccel_kt_stride))) + 2 );
    cine3d_maxslquant = FCINE_MAX_SLQUANT;
    cvmin(opslquant, cine3d_minslquant);

    pidefarr = (nflow4D > 1)? 30:20;

    piait = (INT)((60.0 / (FLOAT)exist(ophrate)) * 10000.0 *
                  (FLOAT)(100 + exist(oparr)));

    avmaxphases = MAX_CPHASE_3DCINE;

    avail_RRtime  =  (INT)( (60.0 / (FLOAT)(exist(ophrate))) *
                            1000000.0 );

    pisupnub = 0;  /* disable fat sat for now */
    pichemsatopt = 0;
    oparrmon = arr_check;
   /*calculate the uppler limit of num of phases with vps=1*/
   /* arr_check from VAST.e -> opuser3 */
    if (arr_check == PSD_ON)
    {
        avail_imagetime  =  (INT)( (60.0 / (FLOAT)(exist(ophrate))) *
                                  1000000.0 * (1.0 + exist(oparr)*0.01));
        cine3d_arrlimit = exist(opuser5)/ (100.0 - exist(opuser5) ) ;
    } 
    else
    {
        avail_imagetime  =  (INT)( (60.0 / (FLOAT)(exist(ophrate))) *
                                      1000000.0 * 1.25);
        cine3d_arrlimit = 0.5; /* not used - reset to default */
    }
    cine3d_targetedphases_max = IMin(2, MAX_APHASE_3DCINE, IMax(2, 1, (INT)((FLOAT)avail_imagetime / (FLOAT)(act_tr*nflow4D))));
   
    avmaxaphases = cine3d_targetedphases_max;
    cvmax(opaphases, avmaxaphases);

    /* no center acceleration for ARC */
    if ( (cine3d_ktsamp_mode == KT_MODE) || (cine3d_ktsamp_mode == VDKT_MODE) )
    {
        cal_kz_ktarc = IMin(2, 16, pfkz_total);
        cal_ky_ktarc = 16;
        accel_kt_cal_stride = IMax(2, 1, (int)(opaccel_kt_stride/accel_outer2cal_factor));
    }
    else
    {
        cal_kz_ktarc = IMin(2, 24, pfkz_total);
        cal_ky_ktarc = 24;
        accel_kt_cal_stride = 1;
    }

    /* calculate views per seg based on User-selected # of acquired phases */
    /* Include fat sat into calculation */
    cine3d_temp_int = IMax( 2, 1, (INT)((60000000.0 / ((FLOAT)(exist(ophrate)*exist(opaphases))))
                 / ((FLOAT)(act_tr*nflow4D)) + 0.5) );   /* new VPS based on aphases */

    cvdef(opvps, cine3d_temp_int);
    pivpsdef = cine3d_temp_int;
    cvoverride(opvps,cine3d_temp_int, PSD_FIX_ON, PSD_EXIST_ON);

    /* post temporal resolution */
    pitres = (INT)(60000000.0 / ((FLOAT)exist(ophrate)*(FLOAT)exist(opaphases)) + 0.5);
    aphases_max =  IMax(2, 1, (INT)ceil((FLOAT)avail_imagetime / (FLOAT)(exist(opvps)*act_tr*nflow4D)));
}

@host fcine3d_cvcheck

if( cine3d_flag )
{
    int temp_int=0, numImages = 0;
    int calKSize=0, outKSize=0;
    s64 chKDataSize=0, rawKDataSize=0, sensMapSize=0, aphImageSize=0, ovlImageSize=0;

    /* check for multi-channel receive */
    if (rhdab0s == rhdab0e)
    {
        epic_error( 0, " Please select Phased Array coil before selecting 3DCINE / 4DFLOW.",
                        0, EE_ARGS(0));
        return FAILURE;
    }

    /* checking acquisisiton size against VRE memory limits */
    calKSize = cal_ky_ktarc * cal_kz_ktarc;
    outKSize =  rhdayres * exist(opslquant);

    chKDataSize = (s64)rhdaxres * (s64)(calKSize / accel_kt_cal_stride + (outKSize - calKSize) / exist(opaccel_kt_stride)) * 
      (s64)(exist(opvquant) * nflow4D * exist(opaphases));

    temp_int = (rhdab0e - rhdab0s + 1);
    rawKDataSize = chKDataSize * (s64)(temp_int);

    sensMapSize = (s64)(rhimsize * rhimsize) * (s64)(exist(opslquant) * (opslzip2? 2:1)) * (s64)num_virchan;

    aphImageSize = (s64)(rhimsize * rhimsize) * (s64)(exist(opslquant) * (opslzip2? 2:1)) * (s64)(nflow4D * exist(opaphases));

    if(exist(opvquant) > 1)
    {
        ovlImageSize = (s64)(rhimsize * rhimsize / 4) * (s64)(exist(opslquant) * (opslzip2? 2:1)) * (s64)(nflow4D * (exist(opcphases)+1) * (exist(opvquant) - 1) )
           + (s64)(rhimsize * rhimsize) * (s64)(exist(opovl) * (opslzip2? 2:1)) * (s64)(nflow4D * exist(opaphases));
    }
    else
    {
        ovlImageSize = 0;
    }

    if( ((rawKDataSize + sensMapSize + aphImageSize + ovlImageSize) > MaxVREDataSize) &&
           existcv(opxres) && existcv(opyres) && existcv(opslquant) && 
           existcv(opaccel_kt_stride)  && existcv(opvquant) )
    {
        epic_error( use_ermes, "Not enough memory for a scan this size.  Reduce the scan size.",
                       EM_PSD_SCAN_SIZE, EE_ARGS(0) );

        return FAILURE;
    }

    numImages = ((exist(opslquant)-opslblank*2) * exist(opvquant) * (opslzip2? 2:1)
               - (exist(opovl)*(opslzip2? 2:1)*(exist(opvquant)-1))) * (exist(opcphases)+1) * nflow4D;
    if ( (numImages > FCINE_MAX_IMAGES)
                && existcv(opslquant) && existcv(opcphases) && existcv(opvquant) )
    {
        epic_error(use_ermes,"Maximum number of images exceeded (%d images/scan). Please reduce number of images per scan.",
                   EM_PSD_MAX_IMAGES_PER_SCAN,EE_ARGS(1),INT_ARG,FCINE_MAX_IMAGES);
        return ADVISORY_FAILURE;
    }

   
    if ( ( ((exist(opyres) * (INT)nop) > FCINE_MAX_YRES) || ((exist(opyres)*exist(opphasefov)) > FCINE_MAX_YRES) )
                && existcv(opyres) && existcv(opphasefov) && existcv(opnopwrap) )
    {
        epic_error(use_ermes,"The phase encoding steps must be decreased to %d for the current prescription.",
                   EM_PSD_YRES_OUT_OF_RANGE,EE_ARGS(1),INT_ARG,FCINE_MAX_YRES/(int)nop);
        return ADVISORY_FAILURE;
    }

    if ( (exist(opxres) > FCINE_MAX_XRES)  && existcv(opxres) )
    {
        epic_error(use_ermes,"The frequency encoding steps must be decreased to %d for the current prescription.",
                   EM_PSD_XRES_OUT_OF_RANGE,EE_ARGS(1),INT_ARG,FCINE_MAX_XRES);
        return ADVISORY_FAILURE;
    }

    avmaxovl = (int)((float)(exist(opslquant)-2*pislblank)/2.0);
    if( (exist(opvquant) > 1) && (exist(opovl)>avmaxovl) && existcv(opovl) && existcv(opslquant) && existcv(opvquant) )
    {
            epic_error(use_ermes, "The number of overlap locations selected must be reduced to %d for the current prescription.",
                       EM_PSD_OVLSLQ_OUT_OF_RANGE, EE_ARGS(1), INT_ARG, avmaxovl);
           return FAILURE;
    }

    if( (exist(opaccel_kt_stride)> (int)avmaxaccel_kt_stride) && existcv(opaccel_kt_stride)  )
    {
            epic_error(use_ermes, "The maximum acceleration factor is %4.2f. Please select a smaller value.",
                       EM_PSD_GEM_INVALID_ACCEL, EE_ARGS(1), FLOAT_ARG, avmaxaccel_kt_stride);

           return ADVISORY_FAILURE;
    }

    if( (exist(opaphases) <  avminaphases) && existcv(opaphases) && existcv(opaccel_kt_stride)  )
    {
        epic_error( 0, "Increase Acquired phases. Minimum is  %d",
                        0, EE_ARGS(1),
                        INT_ARG, avminaphases);
        return FAILURE;
    }

    
    if( (exist(opaphases) > avmaxaphases) && existcv(opaphases) && existcv(opte) )
    {
        epic_error( 0, "Max acquired phases = %d. Reduce acquired phases and/or verify heart rate.",
                        0, EE_ARGS(1),
                        INT_ARG,  avmaxaphases);
        return FAILURE;
    }

    if( (exist(opcphases) <  avminphases) && existcv(opcphases) && existcv(opaphases)  )
    {
        epic_error( 0, "Number of acquired phases cannot exceed number of reconstructed phases.",
                        0, EE_ARGS(0));
        return FAILURE;
    }

    if( (exist(opcphases) >  avmaxphases) && existcv(ophrate) && existcv(opcphases)  )
    {
        epic_error( 0, "Reduce number of Reconstruced Phases.",
                        0, EE_ARGS(0));
        return FAILURE;
    }
    
    if( ((exist(opnex) < 1.0 ) || (fn < 1.0)) && existcv(opnex) )
    {
        epic_error( use_ermes,
               "%s is incompatible with %s.",
                EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                STRING_ARG, "3DCINE / 4DFLOW",
                STRING_ARG, "Fractional NEX " );
        return FAILURE;
    }
    if ( (resp_nex > _resp_nex.maxval)  && existcv(opnex) )
    {
        epic_error( use_ermes, "The selected number of excitations is not valid for the current prescription.",
                    EM_PSD_NEX_OUT_OF_RANGE, EE_ARGS(0) );
        return FAILURE;
    }

    if ( ((rhnframes+rhhnover)* pfkz_total >= 32767 ) && existcv(opslquant) && existcv(opyres))
    {
        epic_error(use_ermes,"Not enough memory for a scan this size.  Reduce the scan size.",
                   EM_PSD_SCAN_SIZE, (0));
        return FAILURE;
    }  /* HCSDM00439726 */

    if ( (cine3d_totalviews_est >= 32767 ) && existcv(opslquant) && existcv(opyres) && existcv(opnex) )
    {
        epic_error(use_ermes,"Not enough memory for a scan this size.  Reduce the scan size.",
                   EM_PSD_SCAN_SIZE, (0));
        return FAILURE;
    }  /* HCSDM00439726 */

} /* end cine3d_flag check */

@host fcine3d_scantime

/* Correct scan time for kt ARC scancore*/
if (cine3d_flag)
{
    /*estimate the total num of views and calibration data per phase*/
   if (fcine_estnviews_fullk(rhnframes+rhhnover, pfkz_total, cal_ky_ktarc, cal_kz_ktarc,
        &cine3d_fullkviews, &cine3d_fullkviews_cal) != SUCCESS )
   {
        epic_error(use_ermes,supfailfmt,EM_PSD_SUPPORT_FAILURE,
                   EE_ARGS(1),STRING_ARG,"fcine_estnviews");
        return FAILURE;
   }

    /*estimate total views before actuall view order has been generated*/
    cine3d_totalviews_est = (INT)ceil((float)cine3d_fullkviews/(float)opaccel_kt_stride +
        (float)cine3d_fullkviews_cal*(1.0/(float)accel_kt_cal_stride -
         1.0/(float)opaccel_kt_stride));

    /*account for multinex acq */
    if(resp_nex > 1) {
        cine3d_totalviews_est += (INT)ceil(cine3d_totalviews_est * (float)resp_centk_percent / 100.0 * (float)(resp_nex-1));
    }

    if (0==exist(opslicecnt))
    {
    pidmode = PSD_CLOCK_CARDIAC;
    } else {
        pidmode = PSD_CLOCK_CARDPAUSE;
    }
    piviews = (INT)ceil((float)cine3d_totalviews_est/(float)opvps * opvquant);
    avmintscan = (double)(piviews + cgate_dda*opvquant)*(60.0s/exist(ophrate));
    pitslice = avmintscan/opvquant;
    
    /*estimate number of cardiac cycles for recon*/
    /*slightly over estimate to set the upper limit in recon*/
    cine3d_num_segs_est = (INT)ceil((double)cine3d_totalviews_est / (double)opvps * 1.1);
}  /* end cine3d_flag check */

@host fcine3d_calcPulse
if (flow4D_flag) 
{
    short ia_gzfc=0;

    ia_gyfe = (SHORT) (a_gyfe*max_pg_iamp/loggrd.ty);

    ia_gz1u = (SHORT) ((-1.0)*a_gz1u*max_pg_iamp/loggrd.tz);
    ia_gz1d = (SHORT) ((-1.0)*a_gz1d*max_pg_iamp/loggrd.tz);

    ia_gxfcu =  (SHORT) ((-1.0)*a_gxfcu*max_pg_iamp/loggrd.tx);
    ia_gxfcd =  (SHORT) ((-1.0)*a_gxfcd*max_pg_iamp/loggrd.tx);
    ia_gx1u = (SHORT) (a_gx1u*max_pg_iamp/loggrd.tx);
    ia_gx1d = (SHORT) (a_gx1d*max_pg_iamp/loggrd.tx);

    ia_gz1u = (SHORT) ((-1.0)*a_gz1u*max_pg_iamp/loggrd.tz);
    ia_gz1d = (SHORT) ((-1.0)*a_gz1d*max_pg_iamp/loggrd.tz);
    ia_gzfcu = (SHORT)(a_gzfcu*max_pg_iamp/loggrd.tz);
    ia_gzfcd = (SHORT)(a_gzfcd*max_pg_iamp/loggrd.tz);

    /*  "u" means "up" or "positive" flow encoding (may be positive or null).
        "d" means "down" or "negative" flow encoding (may be negative or null).
        "n" means no flow encoding (may or may not be null).
        Note u and d reverse if the logical axis is negated due to 8 in opflax. */
    ia_gx1feu = negx? ia_gx1u : ia_gx1d;
    ia_gx1fed = negx? ia_gx1d : ia_gx1u;
    ia_gx1fen = ia_gx1u;

    ia_gx2feu = negx? ia_gxfcu : ia_gxfcd;
    ia_gx2fed = negx? ia_gxfcd : ia_gxfcu;
    ia_gx2fen = ia_gxfcu;

    ia_gy1feu = negy? ia_gyfe :(-ia_gyfe);
    ia_gy1fed = negy? (-ia_gyfe) : ia_gyfe;
    ia_gy1fen = 0;

    ia_gy2feu = negy? (-ia_gyfe) : ia_gyfe;
    ia_gy2fed = negy? ia_gyfe : (-ia_gyfe);
    ia_gy2fen = 0;


    /*  Since constant lobe on z comes first, its signs are reversed as
        compared wit x to achieve same flow encoding.   */
    ia_gz1feu = negz? ia_gz1d :ia_gz1u;
    ia_gz1fed = negz? ia_gz1u :ia_gz1d;
    ia_gz1fen = ia_gz1u;

    ia_gz2feu = negz? ia_gzfcd :ia_gzfcu;
    ia_gz2fed = negz? ia_gzfcu :ia_gzfcd;
    ia_gz2fen = ia_gzfcu;

    ia_gz1 = (SHORT) ((-1.0)*a_gz1*max_pg_iamp/loggrd.tz);
    ia_gzfc = (SHORT) (fabs(a_gzfc*max_pg_iamp/loggrd.tz) );
    ia_gx1 = (SHORT) (fabs(a_gx1)*max_pg_iamp/loggrd.tx);
    ia_gxfc = (SHORT) ((-1.0)*a_gxfc*max_pg_iamp/loggrd.tx);
} /* end flow4d_flag check */

@host fcine3d_rdout_FlowEnc
    if (flow4D_flag) 
    {
       a_gx1u = (fullte_flag ? a_gx1u_full: a_gx1u_frac);
       a_gx1d = (fullte_flag ? a_gx1d_full: a_gx1d_frac);

       a_gxfcu = (fullte_flag ? a_gxfcu_full: a_gxfcu_frac);
       a_gxfcd = (fullte_flag ? a_gxfcd_full: a_gxfcd_frac);

       flow_wdth_x = (fullte_flag ? fl_width_x_full : fl_width_x_frac);

    } /* end flow4d_flag check */

@host fcine3d_gy1_gy1r_FlowEnc
    if (flow4D_flag == PSD_ON) 
    {
        float area_rampy = 0.0;
        float area_yfe = 0.0;
        float delta_my = 0.0;
        float w_yfea = 0.0;

        /* phase contrast lobes for logical y */
        /* Solve for width of bipolar lobe assuming that it is a trapezoid.
           If it turns out to be a triangle, we will still use same width,
           without slew rate limited ramps. */
        if ((existcv(opxres)!=PSD_OFF) && (opflaxya!=0))
        {
            delta_my = 0.5*pc_const;
        }
        else
        {
            delta_my = 0.0;
        }
        area_rampy = (FLOAT)pw_rampy*gyfctarget;

        w_yfea = 0.5*(((FLOAT)pw_rampy - (FLOAT)pw_gy1_tot) + sqrt(((FLOAT)pw_rampy
                                                                + (FLOAT)pw_gy1_tot)*((FLOAT)pw_rampy + (FLOAT)pw_gy1_tot)
                                                               + 2.0*delta_my/gyfctarget));
        area_yfe = 0.5*delta_my/(w_yfea + (FLOAT)pw_gy1_tot);

        /* true: gyfe is a trapezoid, false: a triangle */
        if (area_yfe > (area_rampy+gyfctarget*(float)minpcflattop))
        {
            pw_gyfe = RUP_GRD((INT)ceil((double)(area_yfe/gyfctarget - (FLOAT)pw_rampy)));
            pw_gyfea = RUP_GRD(pw_rampy);
            pw_gyfed = RUP_GRD(pw_rampy);
        }
        else
        {
            pw_gyfe = minpcflattop;
            pw_gyfea = RUP_GRD((INT) (w_yfea/2.0));
            pw_gyfed = pw_gyfea;
        }

        /* This next expression is designed to account for roundoff due to divisibility
           by ramp resolution, 4 us boundaries, and other causes.  */

        a_gyfe = area_yfe/(FLOAT)(pw_gyfea + pw_gyfe);

        if (delta_my == 0.0)  /* no flow encoding on Y */
        {
            pw_gyfe = GRAD_UPDATE_TIME;
            pw_gyfea = GRAD_UPDATE_TIME;
            pw_gyfed = GRAD_UPDATE_TIME;
            a_gyfe = 0.0;
        }

        yfe_time = 2*pw_gyfe + 4*pw_gyfea;
        pw_gyfe1a = pw_gyfea;
        pw_gyfe1 = pw_gyfe;
        pw_gyfe1d = pw_gyfea;
        pw_gyfe2a = pw_gyfea;
        pw_gyfe2 = pw_gyfe;
        pw_gyfe2d = pw_gyfea;

        a_gyfe1 = a_gyfe;
        a_gyfe2 = -a_gyfe;
    } /* end flow4d_flag check */

@host fcine3d_gzrf1_FlowEnc
if (flow4D_flag == PSD_ON) 
    {
    float area_rampz =0.0,moment_z =0.0, area_encode =0.0, discrim_z =0.0;
    float discrim_z2=0.0,delta_mz=0.0,z_term=0.0, zterm2=0.0; 
    float area_zs1=0.0, area_zfc2=0.0, area_zfcm=0.0, area_zfcu=0.0, area_zfc2d=0.0;
    float area_zfcd=0.0, area_z1u=0.0, area_z1d=0.0;

    /******************************************
      Z rephaser  and flow comp
     ******************************************/

    /* use  flow4D_flag (set to 1) since flow encoding is three lobed
       solution and is closer to flow comp grass */
    /* useful constant for phase contrast */
    flow_wdth_z = (FLOAT)(iso_delay);

    /* this corresponds to a0 in asl note 89-08 */
    area_zs1 = a_gzrf1*(0.5*(FLOAT)pw_gzrf1d + flow_wdth_z);

    /* this corresponds to m1 in asl note 89-08 */
    moment_z = a_gzrf1*(0.33333*(FLOAT)(pw_gzrf1d*pw_gzrf1d)
                        + flow_wdth_z*(0.5*flow_wdth_z + (FLOAT)pw_gzrf1d));
    area_rampz = (FLOAT)pw_rampz*gzfctarget;
    area_encode = 5.0*(1e6)*(FLOAT)(equant - 1)/((FLOAT)GAM*(FLOAT)ethick);

    /* useful term in minimum TE solution for flow encoding */
    z_term = area_zs1 + 2.0 * area_rampz + area_encode;

    /* If we are not encoding on logical z, collapse delta_mz to zero.
       use existcv opnex is one way of determining whether physical
       to logical translation is done. */

    if ((existcv(opxres)!=PSD_OFF) && (opflaxza!=0))
        delta_mz = 0.5*pc_const;
    else
        delta_mz = 0.0;
    discrim_z = z_term*z_term + 8.0*delta_mz*gzfctarget;


    /* 2 sided solution (straddle flow-comp symmetrically) */
    zterm2 = 0.5 * area_encode + area_rampz;
    discrim_z2 = zterm2*zterm2+ 2.0*(2.0*gzfctarget*(moment_z + 0.5*delta_mz)
                                     + area_zs1*area_zs1 + area_zs1*area_rampz);
    area_zfc2 = 0.5*(sqrt(discrim_z2) - zterm2);
    /* here m stands for minimum TE */
    area_zfcm = 0.25*(sqrt(discrim_z) - z_term);
    area_zfcu = (FLOAT)(exist(opfcomp)? area_zfc2:area_zfcm);

    /*  area_zfcd is just the negative of area_zfcu in the min te solution.
        Therefore if one is a trapezoid, the other is too.  In the 2-sided
        solution  area_zfcd is less in absolute value, so if "u" is a trapezoid,
        then "d" is  too. */

    if(area_zfcu + area_encode> (area_rampz+gzfctarget*(float)minpcflattop))
        /* true: gzfc lobe is a trapezoid, false: gzfc lobe is a triangle */
    {
        pw_gzfc = RUP_GRD((INT)ceil((double)((area_zfcu+area_encode)/gzfctarget - pw_rampz)));
        pw_gzfca = RUP_GRD(pw_rampz);
        pw_gzfcd = RUP_GRD(pw_rampz);
    }
    else
    {
        pw_gzfc = minpcflattop;
        pw_gzfca = RUP_GRD((INT)ceil((double)(((area_zfcu+area_encode)/gzfctarget +
                                               pw_rampz - pw_gzfc)/2.0)));
        pw_gzfcd = pw_gzfca;
    }
    w_zfc = pw_gzfca + pw_gzfcd + pw_gzfc;
    a_gzfcu = area_zfcu/(FLOAT)(pw_gzfca + pw_gzfc);

    /*  In 3d phase contrast the sum of velocity encode and volume encode are
        done rspvar */
    a_gzfcbase = a_gzfcu;
    a_gzfccomb = area_encode/(FLOAT)(pw_gzfca + pw_gzfc);
    a_gzfcend = -area_encode/(FLOAT)(pw_gzfca + pw_gzfc);
    a_gzfc    =  a_gzfccomb + a_gzfcu;

   /* area_z1d is not just the negative of area_ziu in the min te solution.
       For simplicity if u is a trapezoid, we will force d to be, even though a
       triangle may work. If us ia triangle, then d is a triangle also, since
       abs(area_z1d) < area_z1u. */

    area_z1u = area_zs1 + area_zfcu;
    if (area_z1u > (area_rampz+gzfctarget*(float)minpcflattop))
    {
        pw_gz1 = RUP_GRD((INT)ceil((double)(area_z1u/gzfctarget - pw_rampz)));
        pw_gz1a = RUP_GRD(pw_rampz);
        pw_gz1d = RUP_GRD(pw_rampz);
    }
    else
    {
        pw_gz1 = minpcflattop;
        pw_gz1a = RUP_GRD((INT)ceil((double)(((area_z1u/gzfctarget +
                                               (pw_rampz - pw_gz1))/2.0))));
        pw_gz1d = pw_gz1a;
    }
    w_z1 = pw_gz1a + pw_gz1d + pw_gz1;

    /* this next expression is designed to account for roundoff due to
       divisibility by ramp resolution. 4 us boundaries, and other causes */
    a_gz1u = area_z1u/(FLOAT)(pw_gz1a + pw_gz1);

    /* With known w_z1, solve for a_gzfcd. In minimum TE case, it is just the
       negative of a_gzfcu. In the two_sided case, it is an expression. */
    area_zfc2d = (2.0*moment_z - delta_mz + area_zs1*(FLOAT)w_z1)/(FLOAT)(w_z1 + w_zfc);
    area_zfcd = (FLOAT)(exist(opfcomp)?area_zfc2d :(-1)*area_zfcu);
    a_gzfcd = area_zfcd/(FLOAT)(pw_gzfca + pw_gzfc);

    /* note a_gz1d may be negative */
    area_z1d = area_zs1 + area_zfcd;
    a_gz1d = area_z1d/(FLOAT)(pw_gz1a + pw_gz1);
    a_gz1 = a_gz1u;

    gz_time = pw_gzrf1d + w_z1 + w_zfc;
} /* end flow4d_flag check */

@host fcine3d_setPulseParams
{ 
    /* Initialize some constants for flow encoding calcs */
    gxfctarget = loggrd.tx_xyz;
    gyfctarget = loggrd.ty_xyz;
    gzfctarget = loggrd.tz_xyz;
    minpcflattop = GRAD_UPDATE_TIME;

    /* Initialize some constants for flow encoding calcs */
    pw_rampx = RUP_GRD((int)((float)xrt * targ_dr_ramp));
    pw_rampy = RUP_GRD((int)((float)yrt * targ_dr_ramp));
    pw_rampz = RUP_GRD((int)((float)zrt * targ_dr_ramp));

    /* Only derate for SR20, SR77, and SR120 systems ***/
    /* MRIhc41015: use opflax* instead of exist(opflax*) */
    if (pcflowtarget(opflaxx,opflaxy,opflaxz,
                     targ_dr,&gxfctarget,&gyfctarget,&gzfctarget, &loggrd,
                     ((cfsrmode!=PSD_SR17) &&(existcv(opnex)!=PSD_OFF))) == FAILURE)
    {
        epic_error(use_ermes,supfailfmt,EM_PSD_SUPPORT_FAILURE,
                   EE_ARGS(1),STRING_ARG,"pcflowtarget");
        return FAILURE;
    }

}

@host fcine3d_predownload
if (cine3d_flag)
{

    if ( ((exist(opphasefov) <  0.50001) && (exist(opphasefov) >  0.49999))
        ||  ((exist(opphasefov) <  0.25001) && (exist(opphasefov) >  0.24999)) )
    {
         _opphasefov.fixedflag = PSD_OFF;
         opphasefov +=0.001;
         _opphasefov.fixedflag = PSD_ON;
    }

    rhtype1 = RHTYP3DM;
    /* DWR - remove number of receivers from this calc for 12.0 */
    rhrawsize= (int)((float)(opslquant*opcphases*
                             (1+(rhbline*rawdata)+rhnframes+rhhnover)*2
                             *rhnecho*rhfrsize*rhptsize)
                     *((float)(exnex*(1-rawdata))+(truenex*(float)rawdata)));
    if (exist(opvquant) > 1)
    {
        rhovl = slicezp * exist(opovl);
    } else {
        rhovl = 0;
    }

    rhinitpass = opvquant;

    fcineim = (cine3d_ktsamp_mode == ARC_MODE)? LINEAR:NNEIGHBOR; /*use Linear for ARC and Nearest Neighbor for k-t*/

    /* Update image header variables */
    ihfcineim = fcineim;   /* interpolation method */
    ihfcinent = fcinent;   /* normalization type */

    /* set raw header values as the last part of predownload */
    /* Set CINE raw header info */
    rhtype     |= RHTYPCINE;
    rhaphases   = exist(opaphases);
    rhcphases   = exist(opcphases);
    rhctr = (FLOAT)act_tr / 1000000.0;  /* from usec to sec */
    rhcrrtime   = 60.0 / (FLOAT)exist(ophrate);  /* also in sec */

    /* Set Fast CINE raw header info */
    rhvps       = exist(opvps);
    rhnslices   = exist(opslquant) * exist(opvquant);
    rhfcinearw  = exist(oparr);
    rhfcinemode = FCINE_ON;

    if ( LINEAR == fcineim )
    {
        /* Linear Interpolation */
        rhfcinemode += FCINE_LI;
    } else if ( NNEIGHBOR == fcineim )
    {
        /* Nearest Neighbor */
        rhfcinemode += FCINE_NN;
    } else {
        /* Invalid Interpolation Method */
        return FAILURE;
    }
    if ( !(exist(optagging) == PSD_ON) )
    {
        /* Allow wrap around if not Tagging */
        rhfcinemode += FCINE_WRAP;
    }
    /* Check for Peripheral Gating and Normalization Type */
    if ( TYPPG == exist(opcgatetype) || UNIFORM == fcinent )
    {
        /* Use uniform normalization */
        rhfcinemode += FCINE_UNIFORM;
    }

    /* Set 3D Cine control bit */
    rhrc3dcinectrl |= CINE3D_ACQ;
    rhrc3dcinectrl |= ((ktarc_flag)? CINE3D_KAT_ARC:0);
    rhrc3dcinectrl |= ((CompleteEchoLoop_flag & (nflow4D > 1))? CINE3D_COMPLETE_ECHO_LOOP:0);
    rhrc3dcinectrl |= ( (cine3d_ktsamp_mode == ARC_MODE) ? 0 : CINE3D_PREVIEW_RECON);
    rhrc3dcinectrl |= (cine3d_ktsamp_mode << 5);
    rhncycles_cine = cine3d_num_segs_est;

    /* Set kat ARC header info */
    rhkt_factor = opaccel_kt_stride;
    rhkt_cal_factor = accel_kt_cal_stride;
    rhkt_calwidth_ph = cal_ky_ktarc;
    rhkt_calwidth_sl = cal_kz_ktarc;

    /* Set GCC coil compression header info */
    rhnvircchannel = num_virchan;

    if (flow4D_flag == PSD_ON ) 
    {
          rhtype &= ~RHTYPFRACTECHO;
          rhhniter = 0;  /* does not support homodyne */
    }
    else  
    {
         rhtype |= ((xres != exist(opxres))? RHTYPFRACTECHO:0);
         rhhniter = 1;
    }

    /* set some variables used for viewtable generation */
    genview_totalviews =  (INT)ceil((float)cine3d_fullkviews/(float)opaccel_kt_stride + (float)cine3d_fullkviews_cal*(1.0/(float)accel_kt_cal_stride - 1.0/(float)opaccel_kt_stride));

    genview_maxaphase = IMin(2, opaccel_kt_stride*accel_kt_cal_stride, aphases_max);
    if(cal_shape == ELLIPTICAL_CAL)
    {
        genview_ellipt_cal = 1;
    } else if(cal_shape == BOX_CAL)
    {
        genview_ellipt_cal = 0;
    } else
    {
        epic_error(use_ermes, supfailfmt,
                   EM_PSD_SUPPORT_FAILURE, EE_ARGS(1),
                   STRING_ARG, "3DCINE genviewtab: cal_shape");
        return FAILURE;
    }

    genview_fovVthick_scale = (float)(opfov*opphasefov*nop) / (float)(opslthick*opslquant);

    
} /* end cine3d_flag check */
else
{
    rhrc3dcinectrl = 0;   /* turn off 3dcine recon */
    rhfcinemode = FCINE_OFF;

    rhtype     &= ~RHTYPCINE;  /* clear cine bit */

    ihfcineim = 0;   /* interpolation method */
    ihfcinent = 0;   /* normalization type */
}


@host fcine3d_hostsupport
/*
 *  mintefgrePC
 *
 *  Type: Function
 *
 *  Description:
 *    Flow encoding calculations lifted from 3dphcon.
 *    algorithm derived in ASL tech note 89-08
 */
STATUS
mintefgrePC( int *Minte,
             int *Rd1a,
             int *Rd1b,
             int *tfeextra,
             int *a_pwgxw,
             int *d_pwgxw,
             float *amp_gx1u,
             float *amp_gx1d,
             int *a_pwgx1,
             int *c_pwgx1,
             int *d_pwgx1,
             float *amp_gxfcu,
             float *amp_gxfcd,
             int *a_pwgxfc,
             int *c_pwgxfc,
             int *d_pwgxfc,
             float *fl_width,
             float fecho_factor,
             int c_pwgxwl,
             int c_pwgxw,
             int c_pwgxwr,
             float ampgxw,
             int Trf1b,
             float PhConst,
             int minseq1,
             int minseq3 )
{
    int minTegx=0, minTegy=0, minTegz=0, mintetmp=0;  /* for min te calcs */
    float area_rampx=0.0, moment_x=0.0, delta_mx=0.0, area_xw=0.0;
    float x_term=0.0, discrim_x=0.0, discrim_x2=0.0, area_x1_2=0.0, area_x1_2d=0.0;
    float area_x1m=0.0, area_x1u=0.0, area_x1d=0.0, area_xfcu=0.0, area_xfcd=0.0;
    int rd1atmp=0, rdbtmp=0;
    int a_pwgx1tmp=0, c_pwgx1tmp=0, d_pwgx1tmp=0;
    float ampgx1utmp=0.0, ampgx1dtmp=0.0;
    float fl_widthtmp=0.0;
    int a_pwgxwtmp=0, d_pwgxwtmp=0;
    int a_pwgxfctmp=0;
    int c_pwgxfctmp=0;
    int d_pwgxfctmp=0;
    float ampgxfcutmp=0.0, ampgxfcdtmp=0.0;
    int c_pwgxwfull=0;
    int misc_daqtime=0;
    int w_x1=0, w_xfc=0;

    c_pwgxwfull = (INT)(((FLOAT)c_pwgxw)/fecho_factor);
    /* Time to center of echo from start of readout */
    rd1atmp = c_pwgxwl + (INT)( (fecho_factor - 0.5) *
                                    (c_pwgxwfull) );
    /* Time from center of echo to end of readout */
    /* get the flow encoding values for logical X, Y, and Z */
    rdbtmp = c_pwgxw + c_pwgxwr + c_pwgxwl - rd1atmp;


    if (optramp(&a_pwgxwtmp, ampgxw, (ogsfXw*loggrd.tx_xyz), (RUP_GRD((int) (ogsfXw*xrt))), TYPDEF) == FAILURE)
    {
        epic_error(use_ermes, supfailfmt,
                   EM_PSD_SUPPORT_FAILURE, EE_ARGS(1),
                   STRING_ARG, "optramp (for pwgxwtmp)");
        return FAILURE;
    }

    misc_daqtime = attenlength + tnslength + IMax(2, DABSETUP, (XTRSETLNG + XTR_length[bd_index] + DAB_length[bd_index])) +
                   RBA_length[bd_index] + psd_grd_wait;

    d_pwgxwtmp = a_pwgxwtmp;

    /******************************************
      X rephaser and flow comp

     ******************************************/
    fl_widthtmp = (FLOAT)(rd1atmp); /* this cv corresponds to "W" in ASL tech note 89-08 */

    /* this next corresponds to "A0" in ASL tech note 89-08 */
    area_xw = ampgxw*(0.5*(FLOAT)a_pwgxwtmp + fl_widthtmp);

    moment_x = ampgxw*(0.333333*(FLOAT)(a_pwgxwtmp*a_pwgxwtmp) +
                      fl_widthtmp*(0.5*fl_widthtmp+(FLOAT)a_pwgxwtmp));
    area_rampx = (FLOAT)pw_rampx*gxfctarget;
    x_term = area_xw + 2.0*area_rampx;

    /* If we are not encoding on logical x, collapse delta_mx to zero.
       The existence of opnex is one way of determining whether the
       physical to logical translation is done. */
    if ((existcv(opxres)!=PSD_OFF) && (opflaxxa!=0))
        delta_mx = 0.5*PhConst;
    else
        delta_mx = 0.0;
    discrim_x = x_term*x_term + 8.0*delta_mx*gxfctarget;


    /* 2-sided solution (straddle flow comp symmetrically) */
    discrim_x2 = area_rampx * area_rampx + 2.0*(2.0*gxfctarget *(moment_x+0.5*delta_mx)
                                                + area_xw*area_xw + area_xw*area_rampx);
    area_x1_2 = 0.5 * (sqrt(discrim_x2) - area_rampx);

    /* Here "m" stands for minimum TE */
    area_x1m = 0.25*(sqrt(discrim_x) - x_term);
    area_x1u = (FLOAT)(exist(opfcomp)? area_x1_2 :area_x1m);

    /* area_x1d is just the negative of area_x1u in the min te solution
       Therefore if one is a trapezoid, the other is too.  In the 2-sided
       solution area_x1d is less in aboslute value, so if "u" is a trapezoid,
       then "d" is too. */
    if (area_x1u > (area_rampx+gxfctarget*minpcflattop))
    {
        c_pwgx1tmp = RUP_GRD((INT)ceil((double)(area_x1u/gxfctarget - pw_rampx)));
        a_pwgx1tmp = RUP_GRD(pw_rampx);
        d_pwgx1tmp = RUP_GRD(pw_rampx);
    }
    else
    {
        c_pwgx1tmp = minpcflattop;
        a_pwgx1tmp = RUP_GRD((INT)ceil((double)((area_x1u/gxfctarget+
                                             (pw_rampx-c_pwgx1tmp))/2.0)));
        d_pwgx1tmp = a_pwgx1tmp;
    }

    /* This next expression is designed to account for roundoff due to
       divisibility by ramp resolution, 4us boundaries and other causes. */
    ampgx1utmp = area_x1u/(FLOAT)(a_pwgx1tmp + c_pwgx1tmp);

    if ((delta_mx == 0.0) && (opfcomp == PSD_OFF))
    {
        c_pwgx1tmp = GRAD_UPDATE_TIME;
        a_pwgx1tmp = GRAD_UPDATE_TIME;
        d_pwgx1tmp = GRAD_UPDATE_TIME;
        ampgx1utmp = 0.0;
    }

    w_x1 = c_pwgx1tmp + a_pwgx1tmp + d_pwgx1tmp;

    /* Caution: "1" and "fc" reverse meaning from z calculation. */

    /* area_xfcd is not just the negative of area_xfcu in the min te solution.
       For simplicity if u is a trapezoid, we will force d to be, even though a
       triangle may work. I f us ia triangle, then d is a triangle also, since
       abs(area_xfcd) < area_xfcu. */
    area_xfcu = area_xw + area_x1u;
    /* true: gxfc is a trapezoid, false: a triangle */
    if (area_xfcu > (area_rampx+gxfctarget*minpcflattop))
    {
        c_pwgxfctmp = RUP_GRD((INT)ceil((double)(area_xfcu/gxfctarget - pw_rampx)));
        a_pwgxfctmp = RUP_GRD(pw_rampx);
        d_pwgxfctmp = RUP_GRD(pw_rampx);

    }
    else
    {
        c_pwgxfctmp = minpcflattop;
        a_pwgxfctmp = RUP_GRD((INT)ceil((double)((area_xfcu/gxfctarget
                                              + pw_rampx - c_pwgxfctmp)/2.0)));
        d_pwgxfctmp = a_pwgxfctmp;

    }
    w_xfc = c_pwgxfctmp + a_pwgxfctmp  + d_pwgxfctmp;

    /* This next expression is designed to account for roundoff due to divisibility
       by ramp resolution, 4us boundaries, and other causes. */
    ampgxfcutmp = area_xfcu/(FLOAT)(a_pwgxfctmp+c_pwgxfctmp);

    /* Now that w_xfc is known, solve for a_gx1d. In minimum TE case, it is just the
       negative of a_gx1u.  In the two_sided case, it is an expression. */
    area_x1_2d = (2.0*moment_x -delta_mx + area_xw*(FLOAT)w_xfc)/(FLOAT)(w_xfc + w_x1);
    area_x1d = (FLOAT)(exist(opfcomp)?area_x1_2d :(-1)*area_x1u);
    ampgx1dtmp = area_x1d/(FLOAT)(a_pwgx1tmp+c_pwgx1tmp);
    /* Note a_xfcd may be negative */
    area_xfcd = area_xw + area_x1d;
    ampgxfcdtmp = area_xfcd/(FLOAT)(a_pwgxfctmp+c_pwgxfctmp);

    minTegx = Trf1b + w_x1 + w_xfc + GRAD_UPDATE_TIME +
                a_pwgxwtmp + rd1atmp;
    minTegy = minseq3 + GRAD_UPDATE_TIME +
                   rd1atmp;
    minTegz = minseq1 + GRAD_UPDATE_TIME +
                   rd1atmp;

    mintetmp = IMax(3, minTegx, minTegy, minTegz);

    *Rd1a = rd1atmp;
    *Rd1b = rdbtmp;
    *fl_width = fl_widthtmp;
    *a_pwgxw = a_pwgxwtmp;
    *d_pwgxw = d_pwgxwtmp;
    *amp_gx1u = ampgx1utmp;
    *amp_gx1d = ampgx1dtmp;
    *a_pwgx1 = a_pwgx1tmp;
    *c_pwgx1 = c_pwgx1tmp;
    *d_pwgx1 = d_pwgx1tmp;
    *amp_gxfcu  = ampgxfcutmp;
    *amp_gxfcd  = ampgxfcdtmp;
    *a_pwgxfc = a_pwgxfctmp;
    *c_pwgxfc = c_pwgxfctmp;
    *d_pwgxfc = d_pwgxfctmp;

    *Minte = RUP_GRD(mintetmp);

    return SUCCESS;
}   /* end mintefgrePC() */

/* generate initial viewtable for the entire k-space */
STATUS fcine_estnviews_fullk(short Nky, short Nkz, short cal_ky, short cal_kz,
        int *fullkviews, int *fullkvviews_cal)
{
    short nky=0, nkz=0, cal_ky_sta=0, cal_ky_end=0, cal_kz_sta=0, cal_kz_end=0, in_CalData=0;
    float cent_ky=0.0, cent_kz=0.0, cent_ky_cal=0.0, cent_kz_cal=0.0, kr=0.0, in_kmask_thresh=0.0;
    int est_fullkviews=0, est_fullkviews_cal=0;

    extern int cal_shape;
    extern int cutcorner_flag;


    if ( (Nky == 0) || (Nkz == 0) || (cal_ky==0) || (cal_kz==0) )
    {
        return FAILURE;
    }
    cent_ky = (float)(Nky-1.0)/2.0;
    cent_kz = (float)(Nkz-1.0)/2.0;
    cent_ky_cal = (float)(cal_ky-1.0)/2.0;
    cent_kz_cal = (float)(cal_kz-1.0)/2.0;
    cal_ky_sta = ceil(cent_ky) - ceil(cal_ky/2);
    cal_ky_end = cal_ky_sta + cal_ky - 1;
    cal_kz_sta = ceil(cent_kz) - ceil(cal_kz/2);
    cal_kz_end = cal_kz_sta + cal_kz - 1;
    in_kmask_thresh = 1.0;

    est_fullkviews = 0;
    est_fullkviews_cal = 0;

    for (nkz=0; nkz<Nkz; nkz++)
    {
        for ( nky=0; nky<Nky; nky++)
        {
            in_CalData = 0;

            if ((nkz >= cal_kz_sta) && (nkz <= cal_kz_end) && (nky >= cal_ky_sta) && (nky <= cal_ky_end))
            {
                if(cal_shape == ELLIPTICAL_CAL)
                {
                    kr = pow((float)(nky-cent_ky)/((float)cent_ky_cal+0.5), 2) + pow((float)(nkz-cent_kz)/((float)cent_kz_cal+0.5), 2);

                    if(kr <= 1.0)
                        in_CalData = 1;
                }
                else
                {
                    in_CalData = 1;
                }
            }

            if(in_CalData == 1)
            {
                ++est_fullkviews_cal;
                ++est_fullkviews;
            }
            else
            {
                if(cutcorner_flag)
                {
                    kr = pow((float)(nky-cent_ky)/((float)cent_ky+0.5), 2) + pow((float)(nkz-cent_kz)/((float)cent_kz+0.5), 2);

                    if (kr > in_kmask_thresh)
                        continue;
                }

                ++est_fullkviews;
            }
        }
    }
    *fullkviews = est_fullkviews;
    *fullkvviews_cal = est_fullkviews_cal;

    return SUCCESS;
}  /** end fcine_estnviews_fullk **/



@pg fcine3d_PGvars
/*********************************************************************
 *                   FASTCINE.E PULSEGEN SECTION                     *
 *                                                                   *
 * Write here the functional code that loads hardware sequencer      *
 * memory with data that will allow it to play out the sequence.     *
 * These functions call pulse generation macros previously defined   *
 * with @pulsedef, and must return SUCCESS or FAILURE.               *
 *********************************************************************/

/* CINE stuff */
static INT echo1cine;          /* Waveform index for the echo1 cine pulse */
LONG pos_isi;

INT trigger_delay = 0;
/* Delay from ECG trigger to the beginning of data acquisition (roughly) */
#ifdef IPG
static INT addtrig_ssidelay = 0;
static INT addtrig_isidelay = 0;
#endif

ViewTable_kyz viewtable_kt[60]; /* ktARC viewtable */

LONG get_pos_isi7(void)
{
    return pbegallssp(&isi7, 0);
}

@pg fcine3d_pulsegen
/*
 *  fcine_pulsegen
 *
 *  Type: Function
 *
 *  Description:
 *    Create CINE packet used for Fast CINE acquisition.
 *    Note that this packet is SEPARATE from the DAB packet
 *    which is re-purposed as a CINE packet in 2D FastCINE 
 *    
 */

if (cine3d_flag)
{
      int PosCINE3D;

      INT pack_ix = 0;
      switch (psd_board_type)
      {
         case PSDCERD:
         case PSDDVMR:
            pack_ix = PSD_XCVR2;
         break;

      }

      PosCINE3D = pbegallssp(&rf1, 0) - DAB_length[pack_ix] ;

      DAB_bits[pack_ix][1] = SSPOC + DCINEOC;                                                   
      DAB_bits[pack_ix][7] = SSPD;

      SSPPACKET(cine3d, PosCINE3D, DAB_length[pack_ix], DAB_bits[pack_ix], 0);

      getwave( &echo1cine, &cine3d );


#ifdef IPG
    addtrig_ssidelay = (INT)((FLOAT)act_tr/1ms + 0.5);
    pos_isi = get_pos_isi7();
    addtrig_isidelay = (INT)((FLOAT)(act_tr-pos_isi)/1ms + 0.5);
#endif /* IPG */
}


@pg fcine3d_genviewtable
if(cine3d_flag)

{
#ifdef IPG
    if( fcine_genvieworder_ktARC( genview_totalviews, genview_maxaphase,
       opaccel_kt_stride, accel_kt_cal_stride, cal_ky_ktarc, cal_kz_ktarc,
       (rhnframes+rhhnover), pfkz_total, genview_fovVthick_scale,
       opvps, genview_ellipt_cal, cutcorner_flag,
       resp_centk_percent, resp_nex, cine3d_yz_order,
       cine3d_ktsamp_mode, kband_width, krewind_flag,
       &cine3d_totalviews, &max_mapphases, viewtable_kt ) == FAILURE )
    {
           psdexit(EM_PSD_ROUTINE_FAILURE,0,"","Failure in Viewtable Generation",
               PSD_ARG_STRING," fcine_genvieworder_ktARC",0);
    }

    cine3d_num_views_skip = (cine3d_totalviews>cine3d_totalviews_est)? (int)((cine3d_totalviews - cine3d_totalviews_est)/(2*opvps))*opvps:0;
    cine3d_totalviews -= cine3d_num_views_skip*2;

    cine3d_num_segs = IMin(2, rhncycles_cine, (INT)ceil((double)cine3d_totalviews / (double)opvps));

    /* Adapt arrhythmia tolarence to scan time */
     cine3d_extraRRlimit = IMax(2, 11, (INT)((float)cine3d_num_segs * cine3d_arrlimit)) * opvquant;
#endif
}

@rspvar fcine3d_rspvar
int segment;
int look_for_trigger;
int minTrigDelay, minTrigDelayCurr, minTrigDelayNew, maxTrigDelay, cycleDuration, act_tr_ms;
int max_trs;    /* the maximum # of TRs can play for a RT buffer */
int n_tr; /* number TR's per R-R interval (segment) */
int clock_count; /* debug */
int cine3d_totalviews;
int cine3d_num_segs;
int cine3d_num_views_skip;
int cine3d_extraRRlimit;
int max_mapphases;
int enable_arrcheck;

@rsp fcine3d_rsp
/*********************************************************************
 *                     FASTCINE.E RSP SECTION                        *
 *                                                                   *
 * Write here the functional code for the real time processing (IPG  *
 * side). You may declare standard C variables, but of limited types *
 * short, int, long, float, double, and 1D arrays of those types.    *
 *********************************************************************/
/*
 * Local global variables
 */

/* Arrhythmia stuff */
/* static LONG arrhythmiaState;*/      /* current arrhythmia state */
/* static LONG oldArrhythmiaState;*/   /* previous arrhythmia state */

INT arrhythmiaCount;     /* current count of arrhythmias in a pass */
INT arrhythmiaOccurred;  /* flag to indicate that an arrhythmia occured */
INT arrhythmiaTotal;     /* total number of arrhythmias that have occured */

/*TKF - 3D CINE support */
extern int * spui_dpr_arryth_occur_p;
extern int * spui_dpr_time_frm_trig_p;
extern int * spui_dpr_trig_occur_p;

int ampx[4], ampy[4], ampz[4]; /* for debugging */
/* ampij[k]: i = logical axis, j = bipolar lobe, k = flow echo */
short ampx1[4], ampx2[4];
short ampy1[4], ampy2[4];
short ampz1[4], ampz2[4];


/*** PRIVATE FUNCTIONS  ***/
@rsp fcine3d_support
/*******************

***********************/
/* 4DFlow & 3D CINE ***/
/*
 * fgre_loaddab_cine
 *
 * Wrapper function for fgre_loaddab_echo1_rfhub with hub index and R1
 * index switching off.
 *
 */

STATUS
fgre_loaddab_cine(  LONG Ky,
                    LONG Kz,
                    LONG Phase,
                    LONG ViewInCycle,
                    LONG echo,
                    LONG triggerDelay,
                    TYPDAB_PACKETS acqon_flag)
{
    LONG hubIndex = 0;
    LONG r1Index = 0;
    LONG hubctrlmask = 0;
    STATUS status;
    status =  fgre_loaddab_cine_rfhub(  Ky,
                                        Kz,
                                        Phase,
                                        ViewInCycle,
                                        echo,
                                        triggerDelay,
                                        acqon_flag,
                                        hubIndex,
                                        r1Index,
                                        hubctrlmask );

    return status;
}

/*
 *  fgre_loaddab_cine_rfhub
 *
 *  Type: Function
 *
 *  Description:
 *    This function is an optimization of loaddab where a ctrlmask of
 *    PSD_LOAD_DAB_ALL is assumed.  echo1 is assumed as the pulse.
 *    A more generic optimization of loaddab would include a pulse
 *    parameter to specifiy which DAB packet to load.
 *    Another generic optimization might call sspload instead of
 *    ssploadrsp, but it would be better to do the parameter checking
 *    once during pulsegen rather than in every sequence preparation.
 *    Arguments are:
 *      LONG Ky;                    -> Ky
 *      LONG Kz;                    -> Kz
 *      LONG Phase;                 -> current phase
 *      LONG ViewInCycle;           -> nTR in current HB
 *      LONG echo;                  -> echo
 *      LONG triggerDelay;          -> trigger Delay  (from spu)
 *      TYPDAB_PACKETS acqon_flag;  -> Acquisition on/off
 *      LONG hubIndex;              -> Hub index to use
 *      LONG r1Index;               -> R1 index to use
 *      LONG hubctrlmask;           -> Mask to control if hubIndex
 *                                     and R1 index are applied
 *
 */

STATUS
fgre_loaddab_cine_rfhub (  LONG Ky,
                           LONG Kz,
                           LONG Phase,
                           LONG ViewInCycle,
                           LONG echo,
                           LONG triggerDelay,
                           TYPDAB_PACKETS acqon_flag,
                           LONG hubIndex,
                           LONG r1Index,
                           LONG hubctrlmask)

{
    SHORT dabbits;
    SHORT rbabits;
    SHORT dabis_data[12];
    LONG  ssp_ix=0;

    switch( psd_board_type ) {
    case PSDCERD:
    case PSDDVMR:
        ssp_ix = 2;
        break;
    }

    if ( acqon_flag == DABON ) {
        dabbits = DABDC;
        rbabits = RDC;
    } else {
        dabbits = 0;
        rbabits = 0;
    }

    /* Add DABON/DABOFF to the DAB packet */
    ssploadrsp( (SHORT *)&dabbits,
                (INT)echo1dab,
                (SHORT)1,
                (HW_DIRECTION)TOHARDWARE,
                (SSP_S_ATTRIB)SSPS1 );

    /* RBA pulse is the associated pulse of the XTR pulse which is the */
    /* associated pulse of the DAB pulse which is passed in */
    ssploadrsp( (SHORT *)&rbabits,
                (INT)( echo1rbarsp + 0 ),
                (SHORT)1,
                (HW_DIRECTION)TOHARDWARE,
                (SSP_S_ATTRIB)SSPS1 );

    /* Prepare an array with the 6 new DAB packet bytes. */
    /* Only the lower 8 bits of each array element are used. */
    dabis_data[ 0 ] = (SHORT)( Ky >> 8 );
    dabis_data[ 1 ] = (SHORT)Ky;

    dabis_data[ 2 ] = (SHORT)( Kz >> 8 );
    dabis_data[ 3 ] = (SHORT)Kz;

    dabis_data[ 4 ] = (SHORT)( Phase >> 8 );
    dabis_data[ 5 ] = (SHORT)Phase;

    dabis_data[ 6 ] = (SHORT)( ViewInCycle >> 8 );
    dabis_data[ 7 ] = (SHORT)ViewInCycle;

    dabis_data[ 8 ] = (SHORT)echo;
/***     dabis_data[ 9 ] ==> unused      ***/

    dabis_data[ 10 ] = (SHORT)( triggerDelay >> 8 );;
    dabis_data[ 11] = (SHORT)triggerDelay;
    /* Add the 12 bytes to the DAB packet */
    ssploadrsp( (SHORT *)dabis_data,
                (INT)( echo1dab + ssp_ix ),
                (SHORT)12,
                (HW_DIRECTION)TOHARDWARE,
                (SSP_S_ATTRIB)SSPS1 );


    /* We use setwamp command to change the tag bit for the SSP data.
     * sspload() interface functions provided by the AGP would not
     * support changing the SSP Tag bits - The PSDs have to use
     * setwamp() functions instead. (as per MRIge68262)
     */
    /* MRIhc21427 */

    /*
     * SSP commands for coil and R1 switching only available on DV
     * receive chain
     */
    if( PSDDVMR == psd_board_type )
    {
        if( hubctrlmask & PSD_LOAD_DAB_HUB )
        {
            /* Set coil configuration change */
            dabbits = SSPOC + RFHUBSEL;
            setwamp (dabbits, pecho1xtr, PSD_HUB_SELECT_OFFSET);

            dabbits = SSPD + HUBIND + hubIndex;
            setwamp (dabbits, pecho1xtr, PSD_HUB_SELECT_OFFSET+1);
        }
        else if( hubctrlmask & PSD_LOAD_DAB_HUB_RESET )
        {
            /* Clear coil configuration change */
            dabbits = SSPNOP;
            setwamp (dabbits, pecho1xtr, PSD_HUB_SELECT_OFFSET);

            dabbits = SSPNOP;
            setwamp (dabbits, pecho1xtr, PSD_HUB_SELECT_OFFSET+1);
        }
        if( hubctrlmask & PSD_LOAD_DAB_R1 )
        {
            /* Set R1 change */
            dabbits = SSPOC + RFHUBSEL;
            setwamp (dabbits, pecho1xtr, PSD_HUB_SELECT_OFFSET+2);

            dabbits = SSPD + R1IND + r1Index -1;
            setwamp (dabbits, pecho1xtr, PSD_HUB_SELECT_OFFSET+3);
        }
        else if( hubctrlmask & PSD_LOAD_DAB_R1_RESET )
        {
            /* Clear R1 change */
            dabbits = SSPNOP;
            setwamp (dabbits, pecho1xtr, PSD_HUB_SELECT_OFFSET+2);

            dabbits = SSPNOP;
            setwamp (dabbits, pecho1xtr, PSD_HUB_SELECT_OFFSET+3);
        }
    }

    return SUCCESS;
}   /* end fgre_loaddab_cine_rfhub() */

/*
 *  loadfcine3D
 *
 *  Type: Private Function
 *
 *  Description:
 *    This routine will change cine fields in the programmable bits array.
 *    The following fields will be changed: arrithymia, operation, previous
 *    view, frame slices [1-4], delay, and frame slice 1's number.
 *
 *    The values are added to the bits array by SSPEXTLOAD and SSPLOAD
 *    commands.  The bits array already exist in memory.
 *
 *    Arguments are:
 *      INT arr                   -> Arrhythmia flag (short)
 *      INT op                    -> Multi-NEX operation (short)
 *      INT n_tr                  -> Number of TRs (long)
 *      TYPDAB_PACKETS acqon_flag -> Acquisition on/off
 */
STATUS
loadfcine3D( const INT arr,        /* arrhythmia */
           const INT op,         /* multi-NEX dabop */
           const INT minTrig,    /* minimum trigger delay */
           const INT n_tr,       /* # of TR's */
           const INT cycDur,    /* cycle duration */
           const INT extra_views,    /* what is this? */
           const TYPDAB_PACKETS acqon_flag )
{
    short cinebits;
    short cine_data[PSD_CINESSP_FSLICE_OFFSET + 2 /* words */];

%ifdef DEBUG
    {
        static CHAR *func_name = "loadfcine3D";
        CHAR tmpname[50];

        if ( NULL == pulse->pulsename ) {
            strcpy( tmpname, "" );
        } else {
            strcpy( tmpname, pulse->pulsename );
        }

        fprintf( stderr,"%s(): pulsename: %s  arr: %d op: %d offset: %d\n",
                 func_name, tmpname, arr, op, pview );
        fprintf( stderr,"      --# TRs: %d\n", n_tr );
        fprintf( stderr,"      --trigger delay: %d, slice #: %d, acqon: %d \n",
                 delay, n_slice, acqon_flag );
        fflush(stderr);
    }
%endif /* DEBUG */
    /* Turn CINE on or off */
    if ( acqon_flag == DABON ) {
        cinebits =  SSPDS + DABDC;  /* fix for DV25 target use */
    } else {
        cinebits = 0;
    }

    /* Add parameters to the CINE packet */
    cine_data[PSD_CINESSP_DC_OFFSET]         = cinebits;
    cine_data[PSD_CINESSP_DC_OFFSET + 1]     = (short)DCINEOC;
    cine_data[PSD_CINESSP_ARR_OFFSET]        = (short)arr;
    cine_data[PSD_CINESSP_OP_OFFSET]         = (short)op;
    cine_data[PSD_CINESSP_PVIEW_OFFSET]      = (short)(minTrig >> 8);
    cine_data[PSD_CINESSP_PVIEW_OFFSET + 1]  = (short)minTrig;
    cine_data[PSD_CINESSP_FRAME_OFFSET]      = (short)(n_tr >> 8);
    cine_data[PSD_CINESSP_FRAME_OFFSET + 1]  = (short)n_tr;
    cine_data[PSD_CINESSP_FRAME_OFFSET + 2]  = (short)(cycDur >> 8);
    cine_data[PSD_CINESSP_FRAME_OFFSET + 3]  = (short) (cycDur);
    cine_data[PSD_CINESSP_DELAY_OFFSET]      = (short)(extra_views >> 8);
    cine_data[PSD_CINESSP_DELAY_OFFSET + 1]  = (short)(extra_views);

    ssploadrsp( cine_data,
               (long)(echo1cine + PSD_CINESSP_DC_OFFSET),
               (short)14,
               (short)TOHARDWARE,
               (short)SSPS1 );

    return SUCCESS;
}   /* end loadfcine3D() */


STATUS
turnoff_isi7( void )
{
    long psd_ctrl;

    getctrl( &psd_ctrl, &isi7, 0 );
    /* PSD bits based on binary representation of the ISI
     * vector 6 = 110; 7 = 111 */
    psd_ctrl &= ~( PSD_ISI1_BIT | PSD_ISI2_BIT | PSD_ISI0_BIT );
    setctrl( psd_ctrl, &isi7, 0 );
    return SUCCESS;
}  /* end turnoff_isi7() */


/********************** PLAYDISDAQ ROUTINE ************************/
STATUS PlayDisdaqCine(int NumDisdaqs)
{
    int ndisdaq;

    /* Make sure sequence is played with echo1 and d3d dab packets
       turned off */
    fgre_loaddab_cine(0, 0, 0, 0, 0, 0, DABOFF);
    /* Load CINE packet  after 1st startseq to keep the cine cycle information */
    look_for_trigger = FALSE;
    for (ndisdaq = 0; ndisdaq< NumDisdaqs; ndisdaq++)
    {
        spoil();
        startseq((SHORT)slabindex,(SHORT)MAY_PAUSE);

        /* Chopper logic */
        chop_phase = -chop_phase;
    }
    look_for_trigger=TRUE;

    return SUCCESS;
}

/********************* WaitForECGTrigger  ***********************/
STATUS WaitForECGTrigCine(void)
{ 
    boffset(off_seqcore);
    look_for_trigger = FALSE;
    while (trigger_detected == FALSE)
    {
       /* Get the new ECG trigger state and compare with old */
        trigger_detected = gettrigoccur();

        spoil(); 
        startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);

    }
    trigger_detected = FALSE;
    look_for_trigger = TRUE;

    return SUCCESS;
}

/*
 *  check_trigger
 *
 *  Type: Private Function
 *
 *  Description:
 *    Compare new trigger against old trigger value. If they differ, a
 *    trigger has occured. If a trigger has occured, compare the new
 *    and old arrhythmia values. If these differ, an arrhythmia has
 *    occurred.
 *    Logic is supported to turn the trigger detection or the arrhytmia
 *    detection ON/OFF.
 */
static void
check_trigger( void )
{
    /* from Echotrain.e */
    /* RSPVAR */
    /* extern int rspungated; */

    /* Get the new ECG trigger state */
    /* Do trigger check only if requested (i.e., exclude Ungated Mode) */
    if ( look_for_trig ) {

        /* Default values */
        trigger_detected   = FALSE;
        arrhythmiaOccurred = FALSE;

        /* Get the new ECG trigger state and compare with old */
        trigger_detected = gettrigoccur();
        if ( trigger_detected == TRUE ) {
            /* Update trigger counter */
            ++trigger_count;

            /* Do arrhythmia check only if requested */
            if( enable_arrcheck ) {
                /* Check for arrhythmias */
                arrhythmiaOccurred = *spui_dpr_arryth_occur_p;
                if ( arrhythmiaOccurred == TRUE ) {
                    /* Update arrhythmia counter */
                    ++arrhythmiaCount;
                }
            }
        }
    }

    return;
}   /* end check_trigger() */


/*
 *  fcine_isiupdate
 *
 *  Type: Function
 *
 *  Description:
 *    ISI interrupt callback function. It checks for triggers
 *    detected by the SPU and sent through a dual port RAM (DPR)
 *    location.
 *
 *    Lastly, the time delay from the last valid ECG trigger is calculated
 *    in usec.
 */
void fcine_isiupdate( void )
{
    check_trigger();

    /* Get delay from trigger, increment by time from trigger
       detection to actual updating of the waveforms  */
    trigger_delay = *spui_dpr_time_frm_trig_p + addtrig_isidelay;

    isi_done = TRUE;

    return;
}   /* end fcine_isiupdate() */


/*
 *  check_arrhythmia
 *
 *  Type: Static Function
 *
 *  Description:
 *    This function gets called only when an arrhytmia has been detected.
 *    It will update the arrhythmiaOccurred flag and the arrhythmia
 *    counter. If the counter exceeds the maximum number of arrhythmias
 *    allowed per scan, it will abort the execution. Otherwise, it will
 *    return without failure.
 */
STATUS
check_arrhythmia( void )
{
    /* Check maximun number of arrhythmias allowed */
     if  (arrhythmiaCount > cine3d_extraRRlimit)  {
        psdexit( EM_PSD_ARRYTHMIA_ABORT, 0, "",
                 "psd scan entry point", PSD_ARG_INT,
                 arrhythmiaCount, 0 );
        /* NOTREACHED */
    }

    return SUCCESS;
}   /* end check_arrhythmia() */

/*
 *
 *  setCineCycleOn
 *
 *  Type: Static Function
 *
 *  Description:
 *    This function uses the provided flag to decided whether to turn the
 *    data acquisition ON or OFF through the RBA pulse.
 */
STATUS
setCineCycleOn( const TYPDAB_PACKETS acqon_flag)
{
    short cinebits;

    if ( acqon_flag == DABON ) {
        cinebits =  SSPDS + DABDC;  /* fix for DV25 target use */
    } else {
        cinebits = 0;
    }

    ssploadrsp( &cinebits,
               (long)(echo1cine + PSD_CINESSP_DC_OFFSET),
               (short)1,
               (short)TOHARDWARE,
               (short)SSPS1 );

    return SUCCESS;
}   /* end setacqon() */

@rsp fcine3d_psdinit
/*
 *  fcine3D_psdinit
 *  	- set isi/ssi vectors
 * 	- initialize trigger delyas
 *	- set ordering for flow encoding gradients if flow4D
 *
 */

    if ( cine3d_flag )
    {
        INT sl;

        isivector(psdisivector, fcine_isiupdate, (short)FALSE);
        ssivector(setfastcardtrig, (short)FALSE);

        /* Initialize the RSP trigger array */
        for (sl=0 ; sl<opvquant; sl++)
        {
            rsptrigger[sl] = TRIG_INTERN;
        }
        settriggerarray( opvquant, rsptrigger );

        minTrigDelayCurr = FCINE_TRIGGER_DELAY_MAX;  /* init trigger delay values to maximum values  */
        minTrigDelayNew = FCINE_TRIGGER_DELAY_MAX;
        maxTrigDelay = 0;
        act_tr_ms = (INT)((FLOAT)act_tr/1ms + 0.5);

        /* flow encoding loading */
        /* note that this section supports "balanced" flow encoding (balanced_FE=1) 
           which is NOT supported in recon. Default flow encoding is modified simple 4point
           or balanced_FE=-1.  Simple 4point is used if balanced_FE=0 */

        if (flow4D_flag == PSD_ON) {
            ampx1[0] = ia_gx1fed;  /* Flow echo A has everything inverted ("down") */
            ampx2[0] = ia_gx2fed;
            ampy1[0] = ia_gy1fed;
            ampy2[0] = ia_gy2fed;
            ampz1[0] = ia_gz1fed;
            ampz2[0] = ia_gz2fed;

            ampx[0] = -1;   /* for debugging */
            ampy[0] = -1;
            ampz[0] = -1;
            for (i = 1; i <= 3; i++)
            {
                ampx1[i] = ia_gx1fed;
                ampx2[i] = ia_gx2fed;
                ampy1[i] = ia_gy1fed;
                ampy2[i] = ia_gy2fed;
                ampz1[i] = ia_gz1fed;
                ampz2[i] = ia_gz2fed;

                ampx[i] = -1;   /* for debugging */
                ampy[i] = -1;
                ampz[i] = -1;

            }
            if ((opflaxxa == 4)  || ((balanced_FE==1) && (opflaxxa == 2)) ) /*  Flow echo B has positive R/L only */
            {
                ampx1[1] = ia_gx1feu;
                ampx2[1] = ia_gx2feu;
                ampx[1] = 1;
                if (balanced_FE == -1) {
                    ampx1[2] = ampx1[1];
                    ampx2[2] = ampx2[1];
                    ampx[2] = 1;

                    ampx1[3] = ampx1[2];
                    ampx2[3] = ampx2[2];
                    ampx[3] = 1;

                }
            }
            if ((opflaxya == 4) || ((balanced_FE==1) && (opflaxya == 2)) )
            {
                ampy1[1] = ia_gy1feu;
                ampy2[1] = ia_gy2feu;

                ampy[1] = 1;
                if (balanced_FE == -1) {
                    ampy1[2] = ampy1[1];
                    ampy2[2] = ampy2[1];
                    ampy[2] = 1;

                    ampy1[3] = ampy1[2];
                    ampy2[3] = ampy2[2];
                    ampy[3] = 1;

                }
            }
            if ((opflaxza == 4) || ((balanced_FE==1) && (opflaxza== 2)) )
            {
                ampz1[1] = ia_gz1feu;
                ampz2[1] = ia_gz2feu;
                ampz[1] = 1;

                if (balanced_FE == -1) {
                    ampz1[2] = ampz1[1];
                    ampz2[2] = ampz2[1];
                    ampz[2] = 1;

                    ampz1[3] = ampz1[2];
                    ampz2[3] = ampz2[2];
                    ampz[3] = 1;

                }
            }
            if ( ((balanced_FE!=1) && (opflaxxa == 2))  || ((balanced_FE==1) && !(opflaxxa == 2)) )/*  Flow echo C has positive A/P only */
            {
                ampx1[2] = ia_gx1feu;
                ampx2[2] = ia_gx2feu;

                ampx[2] = 1;
                if (balanced_FE == -1) {
                    ampx1[3] = ampx1[2];
                    ampx2[3] = ampx2[2];
                    ampx[3] = 1;
                }


            }
            if ( ((balanced_FE!=1) && (opflaxya == 2)) || ((balanced_FE==1) && !(opflaxya == 2)) )
            {
                ampy1[2] = ia_gy1feu;
                ampy2[2] = ia_gy2feu;

                ampy[2] = 1;
                if (balanced_FE == -1) {
                    ampy1[3] = ampy1[2];
                    ampy2[3] = ampy2[2];
                    ampy[3] = 1;
                }
            }
            if ( ((balanced_FE!=1) && (opflaxza == 2)) || ((balanced_FE==1) && !(opflaxza == 2)) )
            {
                ampz1[2] = ia_gz1feu;
                ampz2[2] = ia_gz2feu;

                ampz[2] = 1;
                if (balanced_FE == -1) {
                    ampz1[3] = ampz1[2];
                    ampz2[3] = ampz2[2];
                    ampz[3] = 1;
                }
            }
            if ((opflaxxa == 1) || ((balanced_FE==1) && (opflaxxa == 2)) ) /*  Flow echo D has positive S/I only */
            {
                ampx1[3] = ia_gx1feu;
                ampx2[3] = ia_gx2feu;

                ampx[3] = 1;

            }
            if ((opflaxya == 1) || ((balanced_FE==1) && (opflaxya == 2)) )
            {
                ampy1[3] = ia_gy1feu;
                ampy2[3] = ia_gy2feu;

                ampy[3] = 1;

            }
            if ((opflaxza == 1) || ((balanced_FE==1) && (opflaxza == 2)) )
            {
                ampz1[3] = ia_gz1feu;
                ampz2[3] = ia_gz2feu;

                ampz[3] = 1;

            }

           if ( (rspent == L_MPS2) || (rspent == L_APS2))
           {
             /* initialize gradients to values for first flow encode. */
                setiamp(ampx1[0], &gx1,0);
                setiampt(ampx2[0], &gxfc,0);
                setiampt(ampy1[0], &gyfe1,0);
                setiampt(ampy2[0], &gyfe2,0);
                setiampt(ampz1[0], &gz1, 0);
                setiamp(ampz2[0]+volumetab[0], &gzcomb,0);
             /*  waveform segment.  */
           }

        }  /* end flow4D_flag */
    }  /* end cine3d_flag */
/************** end fcine3d_psdinit ******************/


/**************scan core **********************/
@rsp fcine3d_scancore

void fcine_getviewtable_ktARC( int *dabview, int *slice, short nt, int nv )
{
    short viewtable_index, viewtable_view;

    viewtable_index = nt%max_mapphases;

    viewtable_view = (short)(IMin(2, nv+cine3d_num_views_skip, viewtable_kt[viewtable_index].len-1));

    *dabview = (INT)(viewtable_kt[viewtable_index].ky[viewtable_view]);
    *slice = (INT)(viewtable_kt[viewtable_index].kz[viewtable_view]);

}

/* scancore for 3dcine / 4dflow with kt ARC */
STATUS scancore_fcine_ssfp_ktARC( void )
{
    /* Modified scancore for 3D cine with kt sampling.
       No ky or kz loop. View ordering performed in 2D [ky,kz] plane
       for corner cutting, flexible resolution, vps and trajectory selection.
    */

    /* gating variables */
    int trigger_ecg = 0;
    int DelayedTrigger_flag = 0;

    /* added for complete echo loop ( CompleteEchoLoop_flag)*/
    int NTR_hbt = 0;

    /* local vairables for fast cine */
    TYPDAB_PACKETS cine_dabstate; /* DABON/DABOFF */
    TYPDAB_PACKETS dabstate; /* DABON/DABOFF */

    short phase_index = 0;
    short view_index = 0;
    short echo_index = 0;

    /*to store the arrhythmia flag for the current cycle for cycle ssp packet*/
    /*note: we need this seperate flag, because arrhythmiaOccurred gets reset every TR by check_trigger()*/
    int isArrhythmiaCycle = 0;

    printdbg("Starting scancore_fcine_ssfp_ktARC", debugstate);

    arrhythmiaCount = 0;         /* reinitialize arrhythmia count for entire scan*/

    for (slabindex=0; slabindex<slabquant; slabindex++)
    {
        boffset(off_seqcore);

        dabop = DABSTORE;
        setfrequency(receive_freq1[slabindex], &echo1, 0);
        setfrequency(rf1_freq[slabindex], &rf1, scanrf1_inst);
        setiamp(ia_rf1, &rf1, scanrf1_inst);

        dabecho = 0;
        trigger_ecg = TRIG_INTERN;
        dabslice = 0;
        exphase = 0; /* initialize */

        /* Compute the max number of tr's can play out before overrun realtime buffer.
           this code was derived from TPS scan_prep.c when it calcs the size of RT buffer
           to malloc  DWR */

        /* Set ECG trigger status */
        trigger_count = 0;


        look_for_trig   = TRUE;    /* look for first ECG trigger */

        /* Turn acquisition OFF */
        dabstate = DABOFF; /* turn off data acquisition */
        /* Turn OFF CINE packet - initialize */
        cine_dabstate = DABOFF;
        loadfcine3D( 0, /* arrhythmia */
                         0,              /* multi-NEX operation */
                         0,       /* minimum trigger delay */
                         0,            /* # of TR's */
                         0,          /* cycle duration */
                         0,               /*  extra views */
                         DABOFF );    /* DABOFF */

        fgre_loaddab_cine(0, 0, 0, 0, 0, 0, DABOFF);

        fgre_loaddab_3d(0, DABOFF);

        /* to be consistent with first kt view & slice in imaging for reducing eddy currents with Fiesta */
        fcine_getviewtable_ktARC( &dabview, &slice, 0, 0 );
        fgre_setiamp(volumetab[slice], &gzcomb);
        if ( zrewind_flag )
            fgre_setiamp(volumetab2[slice], &gzp);
        fgre_setiamp(-viewtable[dabview+1], &gy1);
        if (rewinder_flag)
            fgre_setiamp(-viewtable[dabview+1], &gy1r);

        if (flow4D_flag == PSD_ON) {
            setiamp(ampx1[0], &gx1,0);
            setiampt(ampx2[0], &gxfc,0);
            setiampt(ampy1[0], &gyfe1,0);
            setiampt(ampy2[0], &gyfe2,0);
            setiampt(ampz1[0], &gz1, 0);
            setiamp(ampz2[0]+volumetab[0],&gzcomb, 0);
        }
        enable_arrcheck = FALSE;    /* no arrhythmia checking for DDA */

        for (slice = -cgate_dda; slice <= -1; slice++)
        {
            if (debug_card_sim)
                trigger_detected = TRUE;
            else
                trigger_detected = FALSE;
            WaitForECGTrigCine(); /* use efgre3d trigger*/
        }   /* End disdaqs */
        /* turn data acquisition back on after next trigger */
        dabstate = DABON;

        /* added for complete echo loop */
        DelayedTrigger_flag = FALSE;
        n_tr = 0;
        /*initialize trigger delay in a new cycle*/
        minTrigDelayNew = FCINE_TRIGGER_DELAY_MAX;
        enable_arrcheck = arr_check;    /* check for arrhythmias */

        for (segment = 0; segment<cine3d_num_segs; segment++)
        {
            INT segment_offset;

            /* if there are cgate_dda's then trigger was detected, if not
                then look for the next valid trigger */
            if (FALSE == trigger_detected)
            {
                /* turn off data acquisition */
                fgre_loaddab_cine(0, 0, 0, 0, 0, 0, DABOFF);
                setCineCycleOn(DABOFF);

                WaitForECGTrigCine(); /* use efgre3d trigger*/
               
                setCineCycleOn(cine_dabstate);
 
            }

            arrhythmiaOccurred = FALSE;
            isArrhythmiaCycle = FALSE;

            /* reset max trigger delay */
            maxTrigDelay = 0;
            cycleDuration = 0;

            /* Trigger detected, Start counting TR's */
            trigger_detected = FALSE;  /* reset flag */
            /* turn on data acquisition */

            for(phase_index=0; phase_index<aphases_max; phase_index++)
            {
                segment_offset = segment * opvps;

                for(view_index=0; view_index<opvps; view_index++)
                {
                    if (intermittant_chemsat != 0)
                    {
                        if ( (flow4D_flag == PSD_ON) || (view_index == 0) )
                        {
                           ChemPrep();
                           setCineCycleOn(DABOFF);
                           PlayDisdaqCine(chemsat_dda); 
                           setCineCycleOn(cine_dabstate);
                        }
                    }

                    view = segment_offset + view_index;

                    fcine_getviewtable_ktARC( &dabview, &slice, phase_index, view );

                    /* for 3DCINE, dabview starts from 0, instead of 1 in viewtab[]*/
                    /* INDEX TO PHASE SHOULD BE SLAB 0 */
                    yres_phase = phase_off[slabindex].ysign *
                            ((dabview * phase_off[slabindex].yoffs + 3L*FS_PI)%FS_2PI-FS_PI);

                    fgre_setiamp(-viewtable[dabview+1], &gy1); /* dabview now starts from 0*/
                    if (rewinder_flag) {
                            fgre_setiamp(-viewtable[dabview+1], &gy1r);
                    }
                    dabslice = slice;
                    /* grab the slab phase offset */

                    if(rvssliceenc)
                    {
                        slab_phase = slab_off[slabindex].zsign * ((equant-1-slice) * slab_off[slabindex].zoffs);
                    } 
                    else 
                    {
                        slab_phase = slab_off[slabindex].zsign * (slice * slab_off[slabindex].zoffs);
                    }

                    fgre_setiamp(volumetab[dabslice], &gzcomb);
                    if (zrewind_flag) {
                        fgre_setiamp(volumetab2[dabslice], &gzp);
                    }
                    /* add flow/echo loop */
                    for(echo_index=0; echo_index<nflow4D; echo_index++)
                    {
                        if (flow4D_flag)
                        {
                            setiamp(ampx1[echo_index], &gx1,0);
                            setiampt(ampx2[echo_index], &gxfc,0);
                            setiampt(ampy1[echo_index], &gyfe1,0);
                            setiampt(ampy2[echo_index], &gyfe2,0);
                            setiampt(ampz1[echo_index], &gz1, 0);
                            setiamp(ampz2[echo_index]+volumetab[dabslice], &gzcomb, 0);
                        }

                        spoil();

                        /* update new cycle min trigger delay in case of unset or abnormal value*/
                        /* Expected trigger delay immediately after trigger detection is */
                        /* less than (max VCG delay + 1 TR)=~100ms (where SPU reports trigger_delay in ms) */
                        /* if minTrigDelayNew  > FCINE_TRIGGER_DELAY_LIMIT,  PAC missed trigger_delay update. */
                        /* The NEXT TR will update the minTrigDelayNew to the correct trigger_delay  */

                        minTrigDelayNew = (minTrigDelayNew>FCINE_TRIGGER_DELAY_LIMIT)? trigger_delay : minTrigDelayNew;

                        /* keep track of max trigger delay. delay update for a few TR's to address potential PAC latency.*/
                        if ((trigger_delay > maxTrigDelay) && (n_tr >= FCINE_PAC_UPDATE_DELAY))
                        {
                             maxTrigDelay = trigger_delay;
                        }

                        fgre_loaddab_cine(dabview, dabslice, phase_index, n_tr, echo_index, trigger_delay, dabstate);

                        isi_done = FALSE;

                        startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);

                        /* Turn trigger sync OFF */
                        syncoff(&seqcore);

                        while(FALSE==isi_done)
                        {
                            continue;
                        }

                        /* increment counter */
                        n_tr++;

                        /* *********************************** */
                        /* if the fcine packet was enabled,    */
                        /*   turn if off for the next sequence */
                        if ( DABON == cine_dabstate  )
                        {
                            cine_dabstate = DABOFF;
                            /* Load CINE packet */
                            loadfcine3D( isArrhythmiaCycle, /* arrhythmia */
                                         dabop,              /* multi-NEX operation */
                                         minTrigDelayCurr,       /* minimum trigger delay */
                                         NTR_hbt,            /* # of TR's */
                                         cycleDuration,          /* cycle duration */
                                         n_tr,               /*  extra views */
                                         cine_dabstate );    /* DABOFF*/

                        }

                        /* Check for trigger and mini arrhythmia */
                        if ( TRUE == trigger_detected )
                        {
                            /* record the cycle duration and start counting for a new cycle*/
                            NTR_hbt = n_tr;
                            n_tr = 0;
                            isArrhythmiaCycle = arrhythmiaOccurred;

                            /*use the the trigger_delay in the new cycle for more accurate cycleDuration*/
                            minTrigDelayCurr = minTrigDelayNew;
                            minTrigDelayNew = trigger_delay;

                            /* Check for short arrhythmia */
                            if ( TRUE == arrhythmiaOccurred ) {
                                /* Trigger was detected  */
                                /* Check for maximum count */
                                check_arrhythmia();
                                /*Reacquire segment when arrhythmiaOccurred */
                                --segment;
				DelayedTrigger_flag = FALSE;   
                            }
                            else 
                            {
                                /* Trigger was detected  */
                                /* Decrement clock */
                                setfastcardecgtrig();

                                /*Delay trigger only for normal cycle. In case short arrythmia, restart new phase cycle immediately*/
                                if((nflow4D > 1) && CompleteEchoLoop_flag)
                                {
                                    DelayedTrigger_flag = TRUE;
                                }
                                else
                                {
                                    DelayedTrigger_flag = FALSE;
                                }
                            }

                            if(!DelayedTrigger_flag)
                                goto breakout;
                        } /* trigger_detected */
                    } /* end echo encode loop */

                    if(DelayedTrigger_flag)
                        goto breakout;
                } /* end view encode loop */
            } /* end opaphase loop  */
            /* If we got here, this must be a long arrhythmia */
            /*   arrhythmiaOccurred = TRUE; */
            /* no trigger was detected  */
            /* wait for trig in excitation loop  */
            /*Reacquire segment when arrhythmiaOccurred*/

            /*unset new cycle min trigger delay in case of no trigger detection*/
            minTrigDelayCurr = minTrigDelayNew;
            minTrigDelayNew = FCINE_TRIGGER_DELAY_MAX;

            if( enable_arrcheck )
            {
                arrhythmiaOccurred = TRUE;
                arrhythmiaCount++;       /*  update arrhythmia counter */
                check_arrhythmia();      /*  check for arrhythmia count */

                /* Reacquire segment when arrhythmiaOccurred */
                --segment;
            }
            else 
            {
                /* Decrement clock */
                setfastcardecgtrig();
            }
            

            /*use acq duration as the cycle duration in case of long arrhythmia*/
            /*no extra views in case of long arrhythmia*/
            NTR_hbt = n_tr;
            n_tr = 0;
            isArrhythmiaCycle = arrhythmiaOccurred;

            /* reset trigger to wait for next valid trigger */
            trigger_detected = FALSE;

breakout:

            /* Come here if ECG trigger or arrhythmia detected */
            cine_dabstate = DABON;  /* Send CINE packet */

            /* pass [ky,kz] for the first view to SSP */
            /* fcine_getviewtable_ktARC( &dabview, &slice, 0, segment_offset ); */

            /* calculate cycle duration based on min/maxTrigDelay and triggering mode */
            /* if minTrigDelayNew  > FCINE_TRIGGER_DELAY_LIMIT,  PAC missed trigger_delay update.   */
            /* use the previous cycle minTrigDelay to estimate cycleDuration          */
            /* Recon will check CineView trigger delay to keep temporal integrity     */

            /* in case of long arrthymia, use current cycle min trigger delay instead and that is the best we can do*/

            minTrigDelay = ((TYPPG == opcgatetype) || (minTrigDelayNew > FCINE_TRIGGER_DELAY_LIMIT))? minTrigDelayCurr:minTrigDelayNew;

            cycleDuration = maxTrigDelay - minTrigDelay + act_tr_ms;

            /* Load CINE packet */
            loadfcine3D( isArrhythmiaCycle, /* arrhythmia */
                        dabop,              /* multi-NEX operation */
                        minTrigDelayCurr,       /* minimum trigger delay */
                        NTR_hbt,            /* # of TR's */
                        cycleDuration,          /* cycle duration */
                        n_tr,               /*  extra views */
                        cine_dabstate );    /* DABON */

            /*a valid trigger was detected and delayed, so skip waiting for the next trigger*/
            if(DelayedTrigger_flag)
            {
                DelayedTrigger_flag = FALSE;
                trigger_detected = TRUE;
            }
        } /* end segment loop */
        
        /* Play out one more sequence to flush out the last CINE packet */
        fgre_loaddab_cine(dabview, dabslice, phase_index, n_tr, echo_index, trigger_delay, DABOFF);
        startseq( (SHORT)slabindex, MAY_PAUSE );

        /* pass packet logic */
        boffset(off_seqpass);

        if(slabindex == slabquant-1)
        {
            pause = MAY_PAUSE;
            /* Set DAB pass packet to end of scan */
            setwamp(SSPD + DABPASS + DABSCAN, &pass_pulse, 2);
            printdbg("  End of Scan and Pass", debugstate);
        } else {
            if (((slabindex+1) % slicecnt)==0)
            {    
                pause = MUST_PAUSE;     /* pause if desired */
            } 
            else 
            {
                pause = AUTO_PAUSE;     /* or if required */
            }
            /* Set DAB pass packet to end of pass */
            setwamp(SSPD + DABPASS, &pass_pulse, 2);
            printdbg("  End of Pass", debugstate);
        }

        /* don't load last 3d packet */
        load3d(&d3dpass,0,DABOFF);

        sp_sat_index = 0;
        startseq(0,(SHORT)pause);
    } /*   end of slabindex loop */

    printdbg("Returning from 3dcine scancore with ktARC", debugstate);
    return SUCCESS;
}


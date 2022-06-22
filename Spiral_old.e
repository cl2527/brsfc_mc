@global SpiralGlobal
#include "vx_rcmd.h"
#include "psc.h"
#include "fprint_psc_protocol.h"
#define MAX_LEAF_LEN 16384
#define RAMP_LENGTH 100
#define gr (sqrt(5)-1)/2
#define IRINT(f) ((((f)-(int)(f)) < 0.5) ? ((int) (f)) : (1+(int)(f)))


/* Spiral Types */
#define BRS_SPIELMAN 0
#define BRS_SPIELMAN_DUAL 1
#define BRS_HARGREAVES 2
#define BRS_HARGREAVES_INV 3

/* View Orders */
#define BRS_PERIPHERAL 0
#define BRS_BO_PERIPHERAL 2 /* BOXU 2009.09.16 */
#define BRS_BO_LIVER 4 /* BOXU 2009.09.25 */
#define BRS_2D 3 /* BOXU 2012.4.26 */
#define BRS_CINE 6
#define BRS_CORONARY 11
#define BRS_CORONARY_SHIFT 12
#define BRS_PERIPHERAL_REL_PRIME 13

/* BMK 2006.07.26 */
#define RDB_SUPPORT_RDS 524288
#define RDB_INITPATH_RDS 1048576

#define BRS_MFA_NUM_MAX (24)
#ifdef PSD_HW
#define BRS_CONFIG_FILE "/usr/g/bin/brsfc.cfg"
#else
#define BRS_CONFIG_FILE "brsfc.cfg"
#endif

/*******************************************************/

@host SpiralCV
float brs_daqdeloff = 5.0 with {,,5.0,VIS,"gradient delay offset",};
float brs_daqdeloff_zoom = 5.0 with {,,5.0,VIS,"zoom gradient delay offset",};
float brs_daqdel = 0.0 with {,,0,VIS,"gradient delay vs readout",};
int brs_type = 3 with {0,,3,VIS, "spiral type to use",};
int brs_numleaves = 48 with {0,,48,VIS, "desired number of spiral leaves",};
int brs_numleaves_acq = 48 with {0,,48,VIS, "acquired number of spiral leaves",};
int brs_nphases = 1 with {1,32,1,VIS, "number of temporal phases",};
int brs_leaflen = 2048 with {0,MAX_LEAF_LEN,2048,VIS, "length of spiral leaves",};
int brs_gradlen = 2048 with {0,MAX_LEAF_LEN,2048, VIS, "length of spiral readout gradient",};
int brs_scantype = 0 with {0,,0,VIS,"type of spiral scan to run",};
float brs_alpha = 2 with {0,,2,VIS, "oversampling factor at center of k-space",};
float brs_sampfact = 0.67 with {0,,0.67,VIS,"sampling factor to use at the edge of k-space",};
float brs_gmax = 2.2 with {0,,2.2,VIS,"maximum gradient strength",};
float brs_gslew = 10300 with {0,,10300,VIS,"maximum gradient slew rate",};
int brs_slewmax = 10300 with {0,,10300,VIS,"maximum slewrate for spiral",};
float brs_matrixsize_center = 64 with {,,64,VIS,"oversampled center matrix size",};
float brs_alpha_center = 4 with {,,4,VIS,"oversampled center alpha value",};
float brs_sampfact_center = 2 with {,,2,VIS,"oversampled center sampling factor",};
float brs_fov1 = 0 with {,,0,VIS,"F1 coefficient for Hargreaves spiral",};
float brs_fov2 = 0 with {,,0,VIS,"F2 coefficient for Hargreaves spiral",};
float brs_fov0 = 1 with {0,,0,VIS,"F0 coefficient for Hargreaves spiral (multiplies FOV)",};
float brs_rscale = 4.0 with {1.0,,4.0,VIS,"multiplicative factor for modified hargreaves spiral",};
float brs_fovpow = 2.0 with {1.0,,2.0,VIS,"power of r to use for modified hargreaves spiral",};
float brs_xarea = 0 with {,,0,VIS,"area under x waveform",};
float brs_yarea = 0 with {,,0,VIS,"area under y waveform",};
float brs_zarea = 0 with {,,0,VIS,"area under z waveform",};
int brs_ramplength = 100 with {1,,,VIS,"length of ramp back to zero gradient",};
int brs_mapdel = 0 with {0,,0,VIS,"map delay for phase maps",};
int brs_extrawait = 200us with {0,,200us,VIS,"extra time for wait statements after rf1",};  /* was previously 200us */
float brs_xtarget = 0 with {,,0,VIS,"x gradient target",};
float brs_ytarget = 0 with {,,0,VIS,"y gradient target",};
float brs_ztarget = 0 with {,,0,VIS,"z gradient target",};
float brs_filtdel = 0.0 with {,,0,VIS,"filter delay",};
int brs_fast_rec_lpf = 1 with {1,5,1,VIS,"fast receiver lpf",};
int brs_vieword = 4 with {,,4,VIS,"spiral view ordering",};   /* BOXU 2009.10.07 */
int brs_dofracz = 0 with {0,1,0,VIS,"do fractional kz encoding",};
float brs_fracz_fact = 1.0 with {0.5,1.0,1.0,VIS,"fraction by which to decrease z encodes",};
int brs_nfolds = 4 with {0, ,4, VIS, "number of folds in spiral view order",};
int brs_leafskip = 2 with {0,,2,VIS,"leaf step size for cardiac scans",};
int brs_leafgroup = 3 with {1,,3,VIS,"number of leaves to group together for cine",};
int brs_fs_slice = 0 with {,,0,VIS,"slice to play out fatsat on",};
int brs_debug_vieword = 0 with {0,1,9,VIS,"print out the vieworder",};
int brs_m1null = 0 with {0,1,0,VIS,"null first order moments",};
int brs_s5fp = 0 with {0,1,0,VIS,"use McVeigh style fat saturtion",};
int brs_gateddas = 8 with {0,,8,VIS,"disdaqs after the IRPrep stuff",};
int brs_preirdel = 1000 with {1000,,1000,VIS,"delay before the IR pulse is played out",};
int brs_viewstocenter = 2 with {0,,2,VIS,"views from start of acquisition to center of k-space",};
float brs_recratio = 1 with {1,,1,VIS,"ratio of sampled waveform to generated waveform",};
int brs_ddahbs = 0 with {0,,0,VIS,"number of disdaq heartbeats gated non-cine scans",};
int brs_realtime = 0 with {0,1,0,VIS,"use realtime data server",};  /* BMK 2006.07.26 */
int df = 200;   /* frequency shift of fat, BMK 2006.09.08 */
int brs_fsprep_flag = 0 with {0,1,0,VIS,"use conventional fatsat with spiral",}; /* BMK 2006.09.08 */
int brs_opti = 7000 with {0,,,VIS,"opti to use for optspecir",};
int golden_ratio_flag = 1 with {0,1,1,VIS,"golden ratio flag",}; /* BOXU 2010.09.28 */
int brs_mra_flag = 0 with {0,1,0,VIS,"MRA flag",}; /* BOXU 2010.12.15 */
int brs_shim_flag = 0 with {0,1,0,VIS,"brs set shim",};
int brs_shim_x = 0 with {,,,VIS,"brs x shim value",};
int brs_shim_y = 0 with {,,,VIS,"brs y shim value",};
int brs_shim_z = 0 with {,,,VIS,"brs z shim value",};
int brs_shim_update_type = 0 with {,,,VIS,"brs shim update type",}; 
int brs_psc = 0 with {0,3,0,VIS,"brs fixed prescan (0=off 1=mask 2=dynamic 3=subtract)",}; 
int brs_psc_prot_no = 1 with {1,,1,VIS,"brs fixed prescan protocol number",};
int brs_psc_use_tracker = 0 with {0,1,0,VIS,"brs fixed prescan use tracker for contrast/subtract",}; 
int brs_exno = 1 with {,,1,VIS,"current exam number", };
int brs_rhrecon = 69 with {0,,69,VIS,"brs rhrecon number",};

int brs_2dflag = 0 with {0,1,0,VIS,"2d flag for spiral",};
int res_rf1_full;		/* resolution of a full sinc rf1 pulse */
/* fractional RF vars */
int frac_rf;      /* true if slice thickness < 1.01mm */
int post_lobes = 0 with {
    0, , 0, VISONLY, "number of lobes before center lobe", 
};
int pre_lobes = 0 with {
    0, , 0, VISONLY, "number of lobes after center lobe", 
};
int cutpostlobes = 0 with {
    0, , 0, VISONLY, "number of lobes cut after center lobe (frac RF)", 
};
int pw1_eff;     /* pulse width of a single lobe */
int pw_rf1_full;  /* pulse width of standard rf pulse (3.2ms) */


int brs_ssfp_flag = 0 with {0, 1, 0, VIS, "BRS FIESTA Mode (0=off, 1=on)",};
/*
 * There are two RF pulses available for the FIESTA 2D technique: a Half
 * SINC (Gaussian) pulse and a Time BandWidth (TBW) pulse.  The selection
 * is determined by the fiesta_rf_flag CV.  By default, it is turned OFF
 * indicating that the SINC pulse is the one to use.  When the flag is
 * ON, the TBW pulse will be used.
 */
int brs_2d_fiesta_rf_flag = 0 with {
    0, 1, 0, VIS, "Set RF Pulse for FIESTA (0=Half SINC (Gaussian), 1=Time BandWidth (TBW))",
};

int brs_pm_type = 0 with {0,,3,VIS, "phase map 0=OFF 1=SELFGEN 2=ADD2NDECHO",};
int brs_pm_numleaves = 0 with {0,,,VIS, "number of extra leaves for field map generation",};
int brs_ramplength2 = 100 with {1,,,VIS,"length of ramp back to zero gradient",};
float brs_xarea2 = 0 with {,,0,VIS,"area under x waveform",};
float brs_yarea2 = 0 with {,,0,VIS,"area under y waveform",};
int brs_gradlen2 = 2048 with {0,MAX_LEAF_LEN,2048, VIS, "length of 2nd spiral readout gradient",};
int brs_mapdel_act = 0 with {0,,0,VIS,"map delay for phase maps (actual)",};

int brs_fwflag = 0 with {0,1,0,VIS,"fat/water imaging flag",};
int brs_fw_te_step = 20 with {0,,0,VIS,"fat/water imaging TE step size (us)",};

int brs_flex = 0 with {0,1,0,VIS,"dual echo fat/water separation",};

int brs_mfa_flag = 0 with {0,1,0,VIS,"flag for multiple flip angle spiral",};
int brs_mfa_schedule = 0 with {0,,0,VIS,"multiple flip angle schedule",};
int brs_mfa_num = 0 with {0,BRS_MFA_NUM_MAX,0,VIS,"number of multiple flip angle",};

float brs_grad_powscale = 1.0 with {0.0,,1.0,VIS,"spiral gradient powscale",};
int brs_use_min_seqgrad = 1 with {0,1,1,VIS,"include min_seqgrad in tmin calc",};
float brs_grad_derate = 0.66 with {0.0,,0.66,VIS,"spiral max gradient derating",};

int brs_excite_grad = 2 with {0,2,2,VIS,"rotate excitation 0=x 1=y 2=z",};


int brs_gzvl_flag = 0 with {0,1,0,VIS,"flag for variable length slice encoding",};
float brs_gzvl_area_base = 0 with {,,,VIS, "default area of gzcomb trap before scaling",};
int brs_echo_wait = 0 with {0, ,0,VIS,"extra wait needed for echo shifting",};
int brs_gzvl_delte = 0 with { , , ,VIS, "te time reduction for variable length slice encoding", };


float a_gzvlw = 0 with {,,,VIS, " amplitude of variable length slice encoding ",};
int ia_gzvlw = 0 with {,,,VIS, " amplitude of variable length slice encoding ",};
int pw_gzvlw = 0 with {0,,,VIS, " maximal pulse width of variable length slice encoding ",};
int pw_gzvlmin = 0 with {0,,,VIS, " minimal pulse width of variable length slice encoding ",};
int off_gzvlw = 0;
int res_gzvlw = 0;
int per_gzvlw = 0;
int brs_me_flag = 0 with {0,1,0,VIS,"Multi-echo flag",}; /* BOXU 2011.12.16 */
int brs_min_esp = 0 with {0,,0,VIS,"minimal echo spacing (us) in multi-echo",}; /* BOXU 2010.12.26 */
int brs_extra_esp = 16us with {0,,16us,VIS,"extra echo spacing in multi-echo",};
int brs_extra_len = 0 with {0,,0,VIS,"extra spiral points at the beginning of the spiral",};
int brs_readoutdelay = 8 with {0,,8,VIS,"Delay of spiral readout",};
float brs_xbliparea = 1.0 with {,,1.0, VIS, "area of the x blip gradient;",};
float brs_ybliparea = 1.0 with {,,1.0, VIS, "area of the y blip gradient;",};
float brs_xx = 1.0 with {,,1.0, VIS, "scale xspiral on x gradient;",};
float brs_yx = 1.0 with {,,1.0, VIS, "scale yspiral on x gradient;",};
float brs_yy = 1.0 with {,,1.0, VIS, "scale yspiral on y gradient;",};
float brs_xy = 1.0 with {,,1.0, VIS, "scale xspiral on y gradient;",};
int brs_blipflag = 0 with {0,1,0, VIS, "Apply blip gradient 1, otherwise 0",};
int brs_areamode = 1 with {0,1,1, VIS, "Compute brs_area in 0: old way, 1: new way",};
int hst_flag = 0 with {0,1,0,VIS,"flag for hysteresis correction for readout gradients",};
float a_hst = 3.0 with {-10.0,10.0,3.0,VIS,"gradient amp. for hysteresis correction",};
int pw_hst = 8 with {8,4000,8, VIS, "Flat-top of hysteresis gradient",};
float area_hst;
int hst_length;
int brsfc_flag = 1 with {0,1,1,VIS,"flag for spiral flow compensation",};
int brsfc_longfc = 1 with {0,1,1,VIS,"flag for long z flow compensation",};
int flowpos1x = 0 with {0,,0,VIS,"position of the 1st x spiral flow compensation gradient",};
int flowpos1y = 0 with {0,,0,VIS,"position of the 1st y spiral flow compensation gradient",};
int flowpos1z = 0 with {0,,0,VIS,"position of the 1st z spiral flow compensation gradient",};
int flowpos2x = 0 with {0,,0,VIS,"position of the 2nd x spiral flow compensation gradient",};
int flowpos2y = 0 with {0,,0,VIS,"position of the 2nd y spiral flow compensation gradient",};
int flowpos2z = 0 with {0,,0,VIS,"position of the 2nd z spiral flow compensation gradient",};
int timefcx = 0 with {0,,0,VIS,"Duration of the x spiral flow compensation gradient",};
int timefcy = 0 with {0,,0,VIS,"Duration of the y spiral flow compensation gradient",};
int timefcz = 0 with {0,,0,VIS,"Duration of the z spiral flow compensation gradient",};
int timefcz_echo1 = 0 with {0,,0,VIS,"Duration of the 1st z spiral flow compensation gradient",};
float brsfmx = 0.0 with {,,0.0, VIS, "First moment sum of x spiral gradient",};
float brsfmy = 0.0 with {,,0.0, VIS, "First moment sum of y spiral gradient",};
float brsfmz = 0.0 with {,,0.0, VIS, "First moment sum of z slice selection and phasae encoding gradient",};
int fc_debug = 0 with {0,,0,VIS,"debug for flow compensation gradient",};
int useFirstEchoComp = 0 with {0,1,0,VIS,"use flow compensation for the first echo",};

/*******************************************************/

@host SpiralHostVars
#include <libconfig.h>
int config_lookup_float32(const config_t *config,
  const char *path, float *value);

FILTER_INFO *echo2_filt ;         
FILTER_INFO echo2_rtfilt, echo2_rtfilt_frac; 

float brs_grad[2*MAX_LEAF_LEN];

/* host variables to determine if spiral should be regenerated */
float prev_gmax;
float prev_gslew;
int prev_xres;
float prev_fov;
float prev_alpha;
int prev_numleaves;
float prev_sampfact;
float prev_alpha_center;
float prev_sampfact_center;
float prev_rbw;
int prev_brs_type;
int prev_matrixsize_center;
float prev_rscale;
float prev_fovpow;
float prev_slew;
float prev_recratio;
int prev_pm_type;
int prev_mapdel;
float prev_extra_len;
int prev_brs_areamode;
int avail_flow_time;
/*******************************************************/

@host SpiralIPG
SPIRAL_VIEW brs_viewtab[131072]={{0,0,0}};
int brs_jumptab[1024]={0};
int brs_xgrad[MAX_LEAF_LEN]={0};
int brs_ygrad[MAX_LEAF_LEN]={0};
int brs_xgrad2[MAX_LEAF_LEN]={0};
int brs_ygrad2[MAX_LEAF_LEN]={0};
int brs_savrot[TRIG_ROT_MAX][9]={{0}};
float rotmatrix[9]={0};
float brs_mfa_angles[BRS_MFA_NUM_MAX]={0};

int pw_gzvla[MAXSLQUANT3D]={0};  /* array of attack ramp lengths */
int pw_gzvl[MAXSLQUANT3D]={0};   /* array of flat top lengths */
int pw_gzvld[MAXSLQUANT3D]={0};  /* array of decay ramp lengths */
int ia_gzvlwa[MAXSLQUANT3D]={0}; /* array of flat top starting amplitude */
int ia_gzvlwb[MAXSLQUANT3D]={0}; /* array of flat top ending amplitude */

int zfctab[MAX_SLICE3D];
int zfctab_echo1[MAX_SLICE3D];

/*******************************************************/

@host SpiralInit1

#if ESEMAJOR >= 27
#define PSD_NAME get_psd_name()
#else
#define PSD_NAME psd_name
#endif
    if (NULL != strstr(PSD_NAME,"brsmra")) {
      brs_mra_flag = 1;
    } else {
      brs_mra_flag = 0;
    }
    
    if (NULL != strstr(PSD_NAME,"brs2d")) {
      brs_2dflag = 1;
      cvoverride(brs_vieword,BRS_2D,PSD_FIX_ON,PSD_EXIST_ON);
    }

    if (NULL != strstr(PSD_NAME,"brsflex")) {
      brs_flex = 1;
    }
    
    if (NULL != strstr(PSD_NAME,"brsmfa")) {
      brs_mfa_flag = 1;
      cvoverride(opmph,PSD_ON,PSD_FIX_ON,PSD_EXIST_ON);
    }
    /*set default name brsfc to enable multiEcho option, JL 04072021*/
    /*if (NULL != strstr(PSD_NAME, "brsfc")) {*/
    if (NULL != strstr(PSD_NAME, "brsme")) {
      brs_me_flag = 1;
    } else {
      brs_me_flag = 0;
    }


    if( PSD_SSFP == exist(oppseq) )
    {
        /* Turn FIESTA mode ON */
        cvoverride(brs_ssfp_flag, PSD_ON, PSD_FIX_ON, PSD_EXIST_ON);
    }

/*************************************************************/ 

@host SpiralInit2
    if (lava_flag) {
      if (brs_2dflag) {
        cvoverride(opspecir, PSD_OFF, PSD_FIX_ON, PSD_EXIST_ON);
      } else {
        if (brs_ssfp_flag) {
          _opspecir.fixedflag = 0;
        } else if (brs_mra_flag){
          cvoverride(opspecir, PSD_OFF, PSD_FIX_ON, PSD_EXIST_ON);
        } else if (brs_flex){
          cvoverride(opspecir, PSD_OFF, PSD_FIX_ON, PSD_EXIST_ON);
        } else if (brs_me_flag){
          cvoverride(opspecir, PSD_OFF, PSD_FIX_ON, PSD_EXIST_ON);
        } else {
          cvoverride(opspecir, PSD_ON, PSD_FIX_ON, PSD_EXIST_ON);
        }
      }
    }
    if (brs_mfa_flag) {
      cvoverride(opmph,PSD_ON,PSD_FIX_ON,PSD_EXIST_ON);
    }

/*************************************************************/ 

@host SpiralInit
if (BRS)
{
    FILE *fin;
    float f_temp;
#ifdef PSD_HW
    fin = fopen("/usr/g/mrraw/kressler/brs_daqdel.dat", "r");
#else
    fin = fopen("daqdel.dat", "r");
#endif
    if (fin != NULL)
    {
        fscanf(fin, "%f", &f_temp);
        brs_daqdeloff = f_temp;
        fscanf(fin, "%f", &f_temp);
        brs_daqdeloff_zoom = f_temp;
        fclose(fin);
    }

    cvmax(opvquant, 1);

    if(-1 == (brs_exno = get_exam_number())) brs_exno = 1;
}

/*************************************************************/ 
@host SpiralSetEchoes
if (brs_flex) {
  avmaxnecho = 2;
  cvmax(opnecho, avmaxnecho);
  cvdef(opnecho, 2);          
  cvoverride(opnecho, 2, PSD_FIX_ON, PSD_EXIST_ON);
  piechnub = 0;
#if ESEMAJOR >= 15
  piechdefval = 1;   /* default value */
#endif
} 
/*************************************************************/ 

@host SpiralForceLava
    if (brs_mra_flag || brs_2dflag || brs_ssfp_flag || brs_flex) {
      cvoverride(lava_flag, PSD_ON, PSD_FIX_ON, PSD_EXIST_ON);
    }

/*******************************************************/

@host Spiral_eval_def

STATUS SetZFlowComp()
{
  INT tz1;
  INT tz2; 
  INT tz3;
  FLOAT AZ1;
  FLOAT AZ2;
  FLOAT AZ3;
  INT widthdiff;
  INT inc;
  INT countslice;
  FLOAT a_gzcomb_tmp;
  FLOAT brsfmz_tmp;
  FLOAT zfc_scale;
  FLOAT zfc_ratio;
  float tz=loggrd.tz;
  /*int   rtz=loggrd.zrt;*/
  int rtz = phygrd.zrt; 

  FILE *fp = fopen("brsfc.txt", "a"); 
  fprintf_timestamp(fp); 
  fshowf(fp, tz); 
  fshowi(fp, rtz); 
  fshowi(fp, phygrd.zrt); 
  fclose(fp); 
  
  brs_zarea = 0.0;
  inc = 4;

  AZ1 = (float)(iso_delay + pw_gzrf1d/2)*a_gzrf1;
  AZ2 = (float)(pw_gz1a + pw_gz1)*a_gz1;
  AZ3 = (float)(pw_gzcomba + pw_gzcomb)*-a_end;
  
  tz1 = esp;
  tz2 = esp;
  tz3 = esp;      
  brsfmz = AZ1*(float)tz1 + AZ2*(float)tz2 + AZ3*(float)tz3;



  if (amppwgmnbrs(brs_zarea, brsfmz, 0.0, 0.0, avail_flow_time,
        loggrd.zbeta, tz, rtz, MIN_PLATEAU_TIME,
        &a_gzbrsfc1, &pw_gzbrsfc1a, &pw_gzbrsfc1, &pw_gzbrsfc1d, 
        &a_gzbrsfc2, &pw_gzbrsfc2a, &pw_gzbrsfc2, &pw_gzbrsfc2d)== FAILURE) 
    return FAILURE;
  timefcz = (pw_gzbrsfc1a + pw_gzbrsfc1 + pw_gzbrsfc1d) + (pw_gzbrsfc2a + pw_gzbrsfc2 + pw_gzbrsfc2d);

  if (brsfc_longfc)
  {
    widthdiff =  timefcz - (IMax(2, timefcx, timefcy) + brs_ramplength*4us + brs_extra_esp);
    while ( (widthdiff > inc) || ((widthdiff < -inc) && (brs_extra_esp > inc)) )
    {
      if (widthdiff > inc)
      {
        brs_extra_esp += inc;
        tz1 += inc;
        tz2 += inc; 
        tz3 += inc;
      }
      else if (widthdiff < -inc)
      {
        brs_extra_esp -= inc;
        tz1 -= inc;
        tz2 -= inc; 
        tz3 -= inc;
      }
      brsfmz = AZ1*(float)tz1 + AZ2*(float)tz2 + AZ3*(float)tz3;
      if (amppwgmnbrs(brs_zarea, brsfmz, 0.0, 0.0, avail_flow_time,
            loggrd.zbeta, tz, rtz, MIN_PLATEAU_TIME,
            &a_gzbrsfc1, &pw_gzbrsfc1a, &pw_gzbrsfc1, &pw_gzbrsfc1d, 
            &a_gzbrsfc2, &pw_gzbrsfc2a, &pw_gzbrsfc2, &pw_gzbrsfc2d)== FAILURE) 
        return FAILURE;
      timefcz = (pw_gzbrsfc1a + pw_gzbrsfc1 + pw_gzbrsfc1d) + (pw_gzbrsfc2a + pw_gzbrsfc2 + pw_gzbrsfc2d);
      widthdiff = timefcz - (IMax(2, timefcx, timefcy) + brs_ramplength*4us + brs_extra_esp);
    } 
  }
  else
  {
    brs_extra_esp = 16us;
    if ( timefcz > (IMax(2, timefcx, timefcy) + brs_ramplength*4us + brs_extra_esp) )
    {
      pw_gzbrsfc1 = RDN_GRD((IMax(2, timefcx, timefcy) + brs_ramplength*4us + brs_extra_esp - 4*pw_gzbrsfc1a)/2);
      pw_gzbrsfc2 = pw_gzbrsfc1;
    }
  }
  zfc_scale =  ((float)(pw_gzbrsfc1a+pw_gzbrsfc1)*a_gzbrsfc1 * (float)(pw_gzbrsfc1a+pw_gzbrsfc1/2)*2.0) / brsfmz;

  for (countslice = 0; countslice < equant; countslice++)
  {
    a_gzcomb_tmp  = (float)countslice*(a_comb - a_end)/(float)(equant-1) - a_comb;
    AZ3 = (float)(pw_gzcomba + pw_gzcomb)*a_gzcomb_tmp;
    brsfmz_tmp = AZ1*(float)tz1 + AZ2*(float)tz2 + AZ3*(float)tz3;
    zfc_ratio = brsfmz_tmp/brsfmz;
    if (fabs(zfc_ratio) < fabs(zfc_scale))
      zfctab[countslice] = zfc_ratio/zfc_scale*a_gzbrsfc1 /loggrd.tz *max_pg_iamp;
    else
      zfctab[countslice] = ((zfc_ratio>0)?1:-1) * a_gzbrsfc1 /loggrd.tz *max_pg_iamp;
  }
  if (fc_debug)
  {
    FILE *fp;
    fp = fopen("zfctab.txt", "w");
    for (countslice = 0; countslice < equant; countslice++)          
      fprintf(fp,"zfctab[%03d] = %d \n", countslice, zfctab[countslice]);
    fclose(fp);
  }
  return SUCCESS;
}

STATUS SetZFlowCompEcho1()
{
  INT tz1;
  INT tz2; 
  INT tz3;
  FLOAT AZ1;
  FLOAT AZ2;
  FLOAT AZ3;
  FLOAT FMZ1;
  INT inc;
  INT countslice;
  FLOAT a_gzcomb_tmp;
  FLOAT brsfmz_tmp;
  FLOAT zfc_scale;
  FLOAT zfc_ratio;
  /*FILE *fp;*/
  brs_zarea = 0.0;
  inc = 4;

  AZ1 = (float)(iso_delay + pw_gzrf1d/2)*a_gzrf1;
  AZ2 = (float)(pw_gz1a + pw_gz1)*a_gz1;
  AZ3 = (float)(pw_gzcomba + pw_gzcomb)*-a_end;
  FMZ1 = (float)(3*iso_delay*iso_delay + 6*iso_delay*pw_gzrf1d + 2*pw_gzrf1d*pw_gzrf1d) * a_gzrf1/6.0;
  tz1 = brs_readoutdelay + (pw_gz1a + pw_gz1 + pw_gz1d) + (pw_gzcomba + pw_gzcomb + pw_gzcombd);
  tz2 = brs_readoutdelay + pw_gzcomba + pw_gzcomb + pw_gzcombd;
  tz3 = brs_readoutdelay;      
  brsfmz = FMZ1 + AZ1*(float)tz1 + AZ2*(float)(pw_gz1a+pw_gz1/2+tz2) + AZ3*(float)(pw_gzcomba+pw_gzcomb/2+tz3);

  if (amppwgmnbrs(brs_zarea, brsfmz, 0.0, 0.0, avail_flow_time,
        loggrd.zbeta, loggrd.tz, loggrd.zrt, MIN_PLATEAU_TIME,
        &a_gzbrsfc1echo1, &pw_gzbrsfc1echo1a, &pw_gzbrsfc1echo1, &pw_gzbrsfc1echo1d, 
        &a_gzbrsfc1echo2, &pw_gzbrsfc1echo2a, &pw_gzbrsfc1echo2, &pw_gzbrsfc1echo2d)== FAILURE) 
    return FAILURE;
  timefcz_echo1 = (pw_gzbrsfc1echo1a + pw_gzbrsfc1echo1 + pw_gzbrsfc1echo1d) + (pw_gzbrsfc1echo2a + pw_gzbrsfc1echo2 + pw_gzbrsfc1echo2d);
  
  while ( timefcz_echo1 > brs_readoutdelay )
  {
    brs_readoutdelay += inc;
    tz1 += inc;
    tz2 += inc;
    tz3 += inc;
    brsfmz = FMZ1 + AZ1*(float)tz1 + AZ2*(float)(pw_gz1a+pw_gz1/2+tz2) + AZ3*(float)(pw_gzcomba+pw_gzcomb/2+tz3);

    if (amppwgmnbrs(brs_zarea, brsfmz, 0.0, 0.0, avail_flow_time,
        loggrd.zbeta, loggrd.tz, loggrd.zrt, MIN_PLATEAU_TIME,
        &a_gzbrsfc1echo1, &pw_gzbrsfc1echo1a, &pw_gzbrsfc1echo1, &pw_gzbrsfc1echo1d, 
        &a_gzbrsfc1echo2, &pw_gzbrsfc1echo2a, &pw_gzbrsfc1echo2, &pw_gzbrsfc1echo2d)== FAILURE) 
    timefcz_echo1 = (pw_gzbrsfc1echo1a + pw_gzbrsfc1echo1 + pw_gzbrsfc1echo1d) + (pw_gzbrsfc1echo2a + pw_gzbrsfc1echo2 + pw_gzbrsfc1echo2d);
  }
  zfc_scale =  (float)(pw_gzbrsfc1echo1a+pw_gzbrsfc1echo1)*a_gzbrsfc1echo1 * (float)(pw_gzbrsfc1echo1a+pw_gzbrsfc1echo1/2)*2.0 / brsfmz;
  
  for (countslice = 0; countslice < equant; countslice++)
  {
    a_gzcomb_tmp  = (float)countslice*(a_comb - a_end)/(float)(equant-1) - a_comb;
    AZ3 = (float)(pw_gzcomba + pw_gzcomb)*a_gzcomb_tmp;
    brsfmz_tmp = FMZ1 + AZ1*(float)tz1 + AZ2*(float)(pw_gz1a+pw_gz1/2+tz2) + AZ3*(float)(pw_gzcomba+pw_gzcomb/2+tz3);
    zfc_ratio = brsfmz_tmp/brsfmz;
    if (fabs(zfc_ratio) < fabs(zfc_scale))
      zfctab_echo1[countslice] = zfc_ratio/zfc_scale*a_gzbrsfc1echo1 /loggrd.tz *max_pg_iamp;
    else
      zfctab_echo1[countslice] = ((zfc_ratio>0)? 1:-1) * a_gzbrsfc1echo1 /loggrd.tz *max_pg_iamp; 
  }
  if (fc_debug)
  {
    FILE *fp1, *fp2;
    fp1 = fopen("zfctab_echo1.txt", "w");
    fp2 = fopen("volumetab.txt","w");
    for (countslice = 0; countslice < equant; countslice++)    
    {
      fprintf(fp1,"zfctab_echo1[%03d] = %d \n", countslice, zfctab_echo1[countslice]);
      fprintf(fp2,"volumetab[%d] = %d \n", countslice, (int)(((float)countslice*(a_comb - a_end)/(float)(equant-1) - a_comb)/loggrd.tz*max_pg_iamp));
    }
    fclose(fp1);
    fclose(fp2);

  }
  return SUCCESS;
}

@host SpiralEval1

if (BRS)
{
    s64 avail_bam;
    int max_phases;
    s64 phase_size;
    struct stat st;

    cfsrmodeact = cfsrmode;

    /* default testing values, change later */

    cvmod( opuser0, 0, 0, 0.0, "Scan type, 0 = standard, 1 = PMRA, 3 = Cine", 0, "" );

    if (opcgate)
    {
        cvdef(opuser0, 3);
    }
    opuser0 = _opuser0.defval;
    piuset |= use0;
    brs_scantype = (int)exist(opuser0);

    cvmod( opuser17, 0, 1, 0, "Do fractional kz encoding", 0, "" );
    opuser17 = _opuser17.defval;
    piuset |= use17;
    brs_dofracz = exist(opuser17);
    if (brs_dofracz)
    {
        brs_fracz_fact = 0.625;
    } else {
        brs_fracz_fact = 1.0;
    }


    cvdesc(opuser5, "Number of leaves in spiral");
    cvmin(opuser5, 1);
    cvmax(opuser5, exist(opxres));
    piuset |= use5;
    opuser5 = brs_numleaves;
    cvdef(opuser5, brs_numleaves);
    brs_numleaves = (int)exist(opuser5);
    brs_numleaves_acq = (int)(ceil(brs_numleaves*asset_factor));

    /*cvdesc(opuser16, "prescribed echo spacing (us) in multi-echo");
    cvmin(opuser16, brs_min_esp);
    cvmax(opuser16, 50ms);
    piuset |= use16;
    
    if (brsfc_flag)
      brs_min_esp = (brs_gradlen+brs_ramplength)*4us + 
        IMax(2,timefcx, timefcy) +
        hst_flag*hst_length*2 + brs_extra_esp;
    else
      brs_min_esp = (brs_gradlen+brs_ramplength)*4us + 
        pw_gxspoila + pw_gxspoil + pw_gxspoild + 
        hst_flag*hst_length*2 + brs_extra_esp;

    opuser16 = brs_min_esp;
    cvdef(opuser16, brs_min_esp);
    if ( (int)exist(opuser16) < brs_min_esp)
      opuser16 = brs_min_esp;
    esp = (int)exist(opuser16);*/


#ifdef OLD
    cvmod( opuser1, 0, 1, 0, "Use raw data server", 0, "" );   /* BMK 2006.07.26 */
    opuser1 = _opuser1.defval;
    piuset |= use1;
    brs_realtime = (int)opuser1;
#else
    cvmod( opuser1, 0, 2, 0, "rotate excitation 0=OFF 1=x 2=y", 0, "" ); 
    opuser1 = _opuser1.defval;
    piuset |= use1;
    brs_excite_grad = (2+(int)opuser1)%3;
    
#endif

    
    phase_size = (s64)opvquant*(s64)opslquant*(s64)brs_numleaves_acq
                *(s64)(2*exist(opnecho))*(s64)brs_leaflen
                *(s64)(cfrecvend - cfrecvst + 1)*(s64)opptsize*(s64)(exnex);
    avail_bam = (s64)cftpssize - phase_size;
    /*max_phases = IMin(3,(int)(avail_bam/phase_size),
                        131072/(brs_numleaves_acq*opslquant),
                        _rhnframes.maxval/brs_numleaves_acq);
     */
    max_phases = IMin(2,(int)(avail_bam/phase_size),_rhnframes.maxval/brs_numleaves_acq);
    if (max_phases<1) max_phases=1;
/*
    showll(phase_size);
    showi(opvquant);
    showi(opslquant);
    showi(brs_numleaves_acq);
    showi(exist(opnecho));
    showi(opnecho);
    showi(brs_leaflen);
    showi(cfrecvend - cfrecvst + 1);
    showi(opptsize);
    showi(exnex);
    showll(avail_bam);
    showf(cftpssize);
    showi(max_phases);
    showll(avail_bam/phase_size);
    showi(131072/(brs_numleaves_acq*opslquant));
    showi(_rhnframes.maxval);
    fflush(stdout);
*/
    if (brs_realtime)   /* BMK 2006.07.26 */
        max_phases = 100000;      

    if (!(opcgate && ((brs_vieword == 6) || (brs_vieword == 11) || (brs_vieword == 12))))
    {
        if (brs_mfa_flag) {
          /* default values, will read them from config file later */
          brs_mfa_num = 1;
          brs_mfa_angles[0] = opflip;
          /*brs_nphases = 1;*/
          cvmod( opuser3, 0.0,1000.0, 0.0, "Flip angle schedule", 0, "" );
          piuset |= use3;
          opuser3 = _opuser3.defval;
          brs_mfa_schedule = (int)exist(opuser3);
        } else {
          cvmod( opuser3, 1, max_phases, 1, "Number of phases", 0, "" );
          cvmax(brs_nphases, max_phases);
          piuset |= use3;
          opuser3 = _opuser3.defval;
          brs_nphases = (int)exist(opuser3);
        }
    } else {
        /* will autocalculate later */
        piuset &= ~use3;
        
        /* BMK 2007.07.07 */
        cvmod( opuser3, 0, 0, 0, "Number of phases", 0, "" );
        opuser3 = 0;
        cvoverride(opuser3, 0, PSD_FIX_OFF, PSD_FIX_OFF);
    }
    


/*    cvdesc(opuser7, "Spiral Type");
    cvmin(opuser7, 3);
    cvmax(opuser7, 3);
    piuset |= use7;
    opuser7 = brs_type;
    cvdef(opuser7, brs_type);
    brs_type = (int)exist(opuser7);*/


    /*if (!ssfp_flag)
    {*/
        cvdesc(opuser7, "TE diff for phasemaps (ms)");
        cvmin(opuser7, 0);
        cvmax(opuser7, 10);
        piuset |= use7;
        opuser7 = (float)brs_mapdel/1000.0;
        cvdef(opuser7, (float)brs_mapdel/1000.0);
        brs_mapdel = (((int)(exist(opuser7)*1000))/4)*4;
        if ((brs_mapdel>0) && (PM_OFF == brs_pm_type)) {
          brs_pm_type = PM_SELFGEN;
        }
        if (0 == brs_mapdel) {
          brs_pm_type = PM_OFF;
        }
    /*}
    else
    {
        brs_mapdel = 0;
    }*/



    if (opcgate)
    {
        cvdef(opuser8, 12);
    }
    else
    {
        cvdef(opuser8, 13);
    }
    cvdesc(opuser8, "View Order");
    cvmin(opuser8, 0);
    cvmax(opuser8, 13);
    piuset |= use8;
    opuser8 = brs_vieword;
    cvdef(opuser8, brs_vieword);
    brs_vieword = (int)exist(opuser8);


    cvdesc(opuser9, "Alpha");
    cvmin(opuser9,1);
    piuset |= use9;
    opuser9 = brs_alpha;
    cvdef(opuser9, brs_alpha);
    brs_alpha = exist(opuser9);


    /*cvdesc(opuser10, "Sampling Factor");
    cvmin(opuser10, 0.1);*/

    cvmod( opuser10, 0.1, 100, 0.67, "Sampling Factor", 0, "" );   /* BMK 2007.07.07 */
    piuset |= use10;
    opuser10 = brs_sampfact;
    cvdef(opuser10, brs_sampfact);
    brs_sampfact = exist(opuser10);


#ifdef UNDEF
    piuset |= use18;
    cvmin(opuser18,1);
    cvmax(opuser18,brs_numleaves);
    cvdef(opuser18,1);   /* BMK 2007.07.07 */
    opuser18 = brs_leafskip;
    if (brs_vieword == 6) {
        cvdesc(opuser18, "size of step through leaves for cine");
        opuser18 = brs_leafskip;
        cvdef(opuser18, brs_leafskip);
        brs_leafskip = (int)exist(opuser18);
    } else if ((brs_vieword == 11) || (brs_vieword == 12)) {
        cvdesc(opuser18, "number of leaves to acquire per trigger");
        opuser18 = brs_leafgroup;
        cvdef(opuser18, brs_leafgroup);
        brs_leafgroup = (int)exist(opuser18);
    } else if (brs_vieword == 13) {
        cvdesc(opuser18, "size of step through leaves");
        opuser18 = brs_leafskip;
        cvdef(opuser18, brs_leafskip);
        brs_leafskip = (int)exist(opuser18);
    }
#endif

    piuset |= use18;
    cvmin(opuser18,0);
    cvmax(opuser18,3);
    cvdef(opuser18,0);
    cvdesc(opuser18, "0=OFF 1=MASK 2=CONTRAST 3=SUBTRACT");
    brs_psc = (int)opuser18;

    enable_tracker();

#ifdef UNDEF
    if (ssfp_flag)
    {
        piuset |= use19;
        cvmod( opuser19, 0, 3, 0, "Do fatsat (0=off, 1=a/2, 2=k-ramp, 3=s5fp", 0, "");
        if (ssfp_flag) {
            if ((int)opuser19 == 1) {
                ssfat = 1;
                ssfat_kaiser = 0;
                brs_s5fp = 0;
            } else if ((int)opuser19 == 2) {
                ssfat = 1;
                ssfat_kaiser = 1;
                brs_s5fp = 0;
            } else if ((int)opuser19 == 3){
                ssfat = 0;
                ssfat_kaiser = 0;
                brs_s5fp = 1;
            } else {
                ssfat = 0;
                ssfat_kaiser = 0;
                brs_s5fp = 0;
            }
        } 
    } else if (brs_scantype == 2)  /* BMK 2006.09.09 */
    {
        piuset |= use19;
        cvmod( opuser19, 0, 1, 0, "Do fatsat (0=off, 1=on", 0, "");
	      if ((int)opuser19 == 0)
	        brs_fsprep_flag = 0;
	      else
	        brs_fsprep_flag = 1;
    }
    else
    {
        /* piuset &= ~use19; */
        piuset |= use19;
        cvmod( opuser19, 0, 1, 0, "Use all data for 1 phase (0=No, 1=Yes)", 0, "");
    }
#endif
    if ((2 == brs_scantype)&&(!ssfp_flag)) {
      piuset |= use19;
      cvmod( opuser19, 0, 1, 0, "Do fatsat (0=off, 1=on", 0, "");
	    if ((int)opuser19 == 0)
	      brs_fsprep_flag = 0;
	    else
	      brs_fsprep_flag = 1;
    } else {
      piuset |= use19;
      cvmod( opuser19, 0, 1, 0, "Use all data for 1 phase (0=No, 1=Yes)", 0, "");
    }

    /* BMK 2006.07.05 */
    /* for irprep sequences, play one heartbeat of dummy acquisitions */
    /* at the beginning of the scan */
    if ((opcgate) && (2 == brs_scantype) && (irprep_flag))
    {
        brs_ddahbs = 2;
    } else {
        brs_ddahbs = 0;
    }

    /* BMK 2006.07.06 */
    /* attempt to activate the ophrep CV control for gated scans */
    if ((opcgate) && (2 == brs_scantype))
    {
        cvmax(ophrep, 2);               
        pihrepnub=1 + 2 + 4;		/* Bitmask for hrep buttons */
        pihrepval2=1;		/* Button 2 value */
        pihrepval3=2;		/* Button 3 value */
        cvdef(ophrep,1);
    }

    if (0 == stat(BRS_CONFIG_FILE, &st)) {
      config_t cfg, *cf;
      
      cf = &cfg;
      config_init(cf);
      
      if (!config_read_file(cf, BRS_CONFIG_FILE)) {
        fprintf(stderr, "%s:%d - %s\n",
        config_error_file(cf),
        config_error_line(cf),
        config_error_text(cf));
        config_destroy(cf);
        epic_error(use_ermes, "Errors found in %s", EM_PSD_SUPPORT_FAILURE, 1,
                   STRING_ARG, BRS_CONFIG_FILE);
        return(FAILURE);
      }
     
      config_lookup_int(cf, "rhrecon", &brs_rhrecon);
      config_lookup_int(cf, "psc_use_tracker", &brs_psc_use_tracker);

      config_lookup_float32(cf, "daqdeloff", &brs_daqdeloff); 
      config_lookup_float32(cf, "daqdeloff_zoom", &brs_daqdeloff_zoom);

      if (brs_mfa_flag) {
        const config_setting_t *schedule;
        char schedule_name[255];
        /*
        int fcmp(const void *f1, const void *f2) {
          return (*(float*)f1>*(float*)f2)?1:-1;
        }
        */
        
        snprintf(schedule_name, sizeof(schedule_name), 
                "mfa.schedule%d", brs_mfa_schedule);
        if (NULL != (schedule = config_lookup(cf, schedule_name))) {
          int i, count;
          
          count = config_setting_length(schedule);
          if ((count > BRS_MFA_NUM_MAX) || (count < 1)) {
            epic_error(use_ermes, "Invalid number of flip angles in schedule (%s)", 
                      EM_PSD_SUPPORT_FAILURE, 1, STRING_ARG, BRS_CONFIG_FILE);
            return(FAILURE);
          }
          brs_mfa_num = count;
          float max_flip=0;
          for (i = 0; i < brs_mfa_num; i++) {
            brs_mfa_angles[i]=config_setting_get_float_elem(schedule, i);
            if (brs_mfa_angles[i]>max_flip) {
              max_flip = brs_mfa_angles[i];
            }
          }
          /*opflip = max_flip;*/
          cvoverride(opflip, max_flip, PSD_FIX_ON, PSD_EXIST_ON);
          /*qsort(brs_mfa_angles, brs_mfa_num, sizeof(float), fcmp);*/
        }
      }
      config_destroy(cf);
    }

    if (brs_mfa_flag) {
      cvoverride(opfphases, brs_mfa_num, PSD_FIX_ON, PSD_EXIST_ON);
      setexist(slicecnt,1);
    }  
    /* BOXU 2012.03.21 */
    /* Hysteresis gradient setup */
    if (hst_flag)
    {
      a_hst = FMin(3,cfxfs,cfyfs,cfzfs)/(1.05*sqrt(2.0));

      pw_gxhyst1a = RUP_GRD ((int)(((float)loggrd.xrt*sqrt(2.0)*fabs(a_hst))/loggrd.tx_xy));
      pw_gyhyst1a = RUP_GRD ((int)((sqrt(2.0)*fabs(a_hst) * (float)loggrd.yrt)/loggrd.ty_xy));
      pw_gxhyst2a = pw_gxhyst1a;
      pw_gyhyst2a = pw_gyhyst1a;

      pw_gxhyst1 = pw_hst;
      pw_gyhyst1 = pw_hst;
      pw_gxhyst2 = pw_hst;
      pw_gyhyst2 = pw_hst;

      pw_gxhyst1d = pw_gxhyst1a;
      pw_gyhyst1d = pw_gyhyst1a;
      pw_gxhyst2d = pw_gxhyst2a;
      pw_gyhyst2d = pw_gyhyst2a;

      area_hst = (float)(pw_gxhyst1a + pw_gxhyst1) * a_hst;

      a_gxhyst1 = a_hst;
      a_gyhyst1 = a_hst;
      a_gxhyst2 = -a_hst;
      a_gyhyst2 = -a_hst;

      ia_gxhyst1 = a_gxhyst1*max_pg_iamp/loggrd.tx;
      ia_gyhyst1 = a_gyhyst1*max_pg_iamp/loggrd.ty;
      ia_gxhyst2 = a_gxhyst2*max_pg_iamp/loggrd.tx;
      ia_gyhyst2 = a_gyhyst2*max_pg_iamp/loggrd.ty;

      hst_length = pw_gxhyst1a + pw_gxhyst1 + pw_gxhyst1d;
    }
    else
    {
      a_hst = 0;
      hst_length = 0;
    }
}

/*******************************************************/
@host SpiralEval2


if (BRS)
{
  FLOAT max_rbw, act_rbw;
  calcvalidrbw(oprbw, &act_rbw, &max_rbw, &valid_decimation, OVERWRITE_OPRBW, 0);
  if ( (fabs(prev_gmax - brs_gmax) > 1.e-6) ||
      (fabs(prev_gslew - brs_gslew) > 1.e-6) ||
      (opxres != prev_xres) || (prev_numleaves != brs_numleaves) ||
      (fabs(prev_fov - opfov) > 1.e-6) ||
      (fabs(prev_alpha - brs_alpha) > 1.e-6) ||
      (fabs(prev_sampfact - brs_sampfact) > 1.e-6) ||
      (fabs(prev_alpha_center - brs_alpha_center) > 1.e-6) ||
      (fabs(prev_sampfact_center - brs_sampfact_center) > 1.e-6) ||
      (fabs(oprbw - prev_rbw) > 1.e-6) ||
      (brs_type != prev_brs_type) ||
      (!(floatsAlmostEqualEpsilons(brs_matrixsize_center, prev_matrixsize_center,2))) ||
      (fabs(brs_rscale - prev_rscale) > 1.e-6) ||
      (fabs(brs_fovpow - prev_fovpow) > 1.e-6) ||
      (fabs(cfxfs - prev_gmax) > 1.e-6) || 
      (fabs(cfsrmode - prev_slew) > 1.e-6) || 
      (fabs(brs_recratio - prev_recratio) > 1.e-6)||
      (brs_pm_type != prev_pm_type) || 
      (brs_mapdel != prev_mapdel) ||
      (fabs(brs_extra_len - prev_extra_len) > 1.e-6) ||
      (fabs(brs_areamode - prev_brs_areamode) > 1.e-6) ||
      (fabs(brs_recratio - prev_recratio) > 1.e-6))
  {
        genspiral2(opxres,
                   brs_alpha,
                   brs_alpha_center,
                   brs_numleaves,
                   brs_sampfact,
                   brs_sampfact_center,
                   brs_matrixsize_center,
                   oprbw,
                   brs_recratio,
                   opfov,
                   brs_rscale,
                   brs_fovpow,
                   brs_type,
                   brs_grad_derate,
                   &brs_gslew,
                   brs_grad,
                   &_brs_gradlen, /* pass cv struct */
                   &brs_fov0,
                   &brs_fov1,
                   &brs_fov2,
                   &brs_xarea,
                   &brs_yarea,
                   brs_xgrad,
                   brs_ygrad,
                   &brs_ramplength); 
        if (PM_ADDECHO == brs_pm_type) {
          brs_gradlen2 = brs_gradlen - brs_mapdel/4;
          setexist(brs_gradlen2, 1);
          truncate_waveform(brs_xgrad, 
                            brs_ygrad,
                            brs_xgrad2,
                            brs_ygrad2,
                            brs_gradlen2,
                            brs_gslew, 
                            &brs_ramplength2,
                            &brs_xarea2,
                            &brs_yarea2);
        }
        prev_gmax = brs_gmax;
        prev_gslew = brs_gslew;
        prev_xres = opxres;
        prev_numleaves = brs_numleaves;
        prev_fov = opfov;
        prev_alpha = brs_alpha;
        prev_sampfact = brs_sampfact;
        prev_alpha_center = brs_alpha_center;
        prev_sampfact_center = brs_sampfact_center;
        prev_rbw = oprbw;
        prev_brs_type = brs_type;
        prev_matrixsize_center = brs_matrixsize_center;
        prev_rscale = brs_rscale;
        prev_fovpow = brs_fovpow;
        prev_gmax = cfxfs;
        prev_slew = cfsrmode;
        prev_recratio = brs_recratio;
        prev_pm_type = brs_pm_type; 
        prev_mapdel = brs_mapdel; 
        prev_extra_len = brs_extra_len;
        prev_brs_areamode = brs_areamode;
  }

#define SAVETOFILE(str) \
  do {\
    FILE *fp = fopen("brsfc.txt", "a"); \
    fprintf_timestamp(fp); \
    fprintf(fp, "%s\n", str); \
    fshowf(fp, tx); \
    fshowf(fp, ty); \
    fshowi(fp, rtx); \
    fshowi(fp, phygrd.xrt); \
    fclose(fp); \
  } while (0);    

  if ((opetl > 1) && (brsfc_flag==1))
  {
    if (1) {
      float ty=loggrd.ty_xy/sqrt(2.0)/1.05;
      float tx=loggrd.tx_xy/sqrt(2.0)/1.05;
      int rtx=loggrd.xrt;
      int rty=loggrd.yrt;
      (void)rty;
      SAVETOFILE("old");
    }

      float ty=loggrd.ty_xyz;
      float tx=loggrd.tx_xyz;
      /*int rtx=loggrd.xrta.xyz;
      int rty=loggrd.yrta.xyz;*/
      int rtx=phygrd.xrt;
      int rty=phygrd.yrt;

      SAVETOFILE("new");
#undef SAVETOFILE

      avail_flow_time = 100000;

      if (amppwgmnbrs(brs_yarea, brsfmy, 0.0, 0.0, avail_flow_time,
            loggrd.ybeta, ty , rty, MIN_PLATEAU_TIME,
            &a_gybrsfc1, &pw_gybrsfc1a, &pw_gybrsfc1, &pw_gybrsfc1d, 
            &a_gybrsfc2, &pw_gybrsfc2a, &pw_gybrsfc2, &pw_gybrsfc2d)== FAILURE) 
        return FAILURE;

      if (amppwgmnbrs(brs_xarea, brsfmx, 0.0, 0.0, avail_flow_time,
            loggrd.xbeta, tx, rtx, MIN_PLATEAU_TIME,
            &a_gxbrsfc1, &pw_gxbrsfc1a, &pw_gxbrsfc1, &pw_gxbrsfc1d, 
            &a_gxbrsfc2, &pw_gxbrsfc2a, &pw_gxbrsfc2, &pw_gxbrsfc2d)== FAILURE)
        return FAILURE;

      timefcx = (pw_gxbrsfc1a + pw_gxbrsfc1 + pw_gxbrsfc1d) + (pw_gxbrsfc2a + pw_gxbrsfc2 + pw_gxbrsfc2d); 
      timefcy = (pw_gybrsfc1a + pw_gybrsfc1 + pw_gybrsfc1d) + (pw_gybrsfc2a + pw_gybrsfc2 + pw_gybrsfc2d);

      if(useFirstEchoComp)
        SetZFlowCompEcho1();
      SetZFlowComp();
  }
  else
  {
    brs_readoutdelay = 8us;
    brs_extra_esp = 16us;
    pw_gzbrsfc1a = 0;
    pw_gzbrsfc1 = 0;
    pw_gzbrsfc1d = 0;
    pw_gzbrsfc2a = 0;
    pw_gzbrsfc2 = 0;
    pw_gzbrsfc2d = 0;
    pw_gzbrsfc1echo1a = 0;
    pw_gzbrsfc1echo1 = 0;
    pw_gzbrsfc1echo1d = 0;
    pw_gzbrsfc1echo2a = 0;
    pw_gzbrsfc1echo2 = 0;
    pw_gzbrsfc1echo2d = 0;
  }

    _brs_leaflen.fixedflag = 0;
    brs_leaflen = brs_gradlen * cfswgut*2*oprbw/1000;
    setexist(brs_leaflen, 1);

    /* BMK 2006.06.22 */
    irdisdacqs = 0;
    brs_viewstocenter = ((int)((float)opslquant*brs_fracz_fact) - opslquant/2) * brs_leafgroup; /* BMK 2006.07.07, added multiplication by brs_leafgroup */
}

/*******************************************************/
@host Spiral2DRF_2    
    if (brs_2dflag) {
        /* code to run after scalerfpulses */
        /* Calculate and round up pw_rf1_full from the scaled value */
        pw_rf1_full = (int)((double)pw_rf1 / (1.0 - ((double)cutpostlobes /
                                                     (4.0 * (double)cyc_rf1))));
        pw_rf1_full = RUP_RF(pw_rf1_full);
        pw1_eff = (int)((float)pw_rf1_full / (4.0f * cyc_rf1));
        t_exb = (post_lobes + 1) * pw1_eff;
        bw_rf1 = (int)(4.0f * cyc_rf1 / ((float)pw_rf1_full / (float)1.0s));

        /* Reset resolutions of full and fractional based on new pulse widths */
        res_rf1_full = (int)(pw_rf1_full / RF_UPDATE_TIME);
        res_rf1 = (int)(pw_rf1 / RF_UPDATE_TIME);
    
        iso_delay = t_exb;
    }
    
/*************************************************************/ 

@host SpiralHost

/*
#if ESEMAJOR == 15
void cv_cnv_endian_CAL_PARAM(CAL_PARAM *c){
  return;
}
#endif
*/
int config_lookup_float32(const config_t *config,
  const char *path, float *value)
{
  double tmp; 
  if (CONFIG_TRUE == config_lookup_float(config, path, &tmp)) { 
    *value = tmp;
    return CONFIG_TRUE;
  } 
  return CONFIG_FALSE;
} 
        

void fprintf_timestamp(FILE *fp) {
  time_t now_epoch = time(NULL);
  struct tm now;
  localtime_r(&now_epoch, &now);
  fprintf(fp, "\n%d/%d/%d %d:%d:%d\n",
      now.tm_mday,
      now.tm_mon+1,
      now.tm_year,
      now.tm_hour,
      now.tm_min,
      now.tm_sec);
}

STATUS enable_tracker(void) {
  if (brs_psc_use_tracker) {
    if (   (DYNA_CONTRAST==brs_psc) 
        || (DYNA_SUBTRACT==brs_psc) ) {
      pimonitor = 1;
    } else {
      pimonitor = 0;
    }
  }
  return SUCCESS;
}

STATUS set_spiral_spoilers (void) {
  set_spiral_spoilers_aux (brs_xarea, 
                           brs_yarea,
                           &a_gxspoil,
                           &pw_gxspoila,
                           &pw_gxspoil,
                           &pw_gxspoild,
                           &a_gyspoil,
                           &pw_gyspoila,
                           &pw_gyspoil,
                           &pw_gyspoild);
  if (PM_ADDECHO == brs_pm_type) {
    set_spiral_spoilers_aux (brs_xarea2, 
                             brs_yarea2,
                             &a_gxspoil2,
                             &pw_gxspoil2a,
                             &pw_gxspoil2,
                             &pw_gxspoil2d,
                             &a_gyspoil2,
                             &pw_gyspoil2a,
                             &pw_gyspoil2,
                             &pw_gyspoil2d);
  }
  return SUCCESS;
}

STATUS set_spiral_spoilers_aux (float xarea, 
                                float yarea,
                                float *a_xspoil,
                                int   *pw_xspoila,
                                int   *pw_xspoil,
                                int   *pw_xspoild,
                                float *a_yspoil,
                                int   *pw_yspoila,
                                int   *pw_yspoil,
                                int   *pw_yspoild) 
{
  /* calculate spoilers used for spiral scan, BMK 2006.03.20 */
  float xspoilderate;
  float yspoilderate;
	float xtarg; 
	float ytarg;
  float xfract;
  float yfract;

  /* hopefully better rewinders, BMK 2006.04.11 */
  xfract = 1.0/sqrt(1.0 + (yarea*yarea)/(xarea*xarea));    
  yfract = sqrt(1.0-xfract*xfract);

  if (opplane == PSD_OBL) {
    xspoilderate = sqrt(2.0)/xfract;
    yspoilderate = sqrt(2.0)/yfract;
  } else {
    xspoilderate = 1./xfract;
    yspoilderate = 1./yfract;
  }
#ifdef BOXU
  xtarg = cfxfs/xspoilderate;
  ytarg = cfyfs/yspoilderate;
#else
  xtarg = cfxfs/xspoilderate*brs_grad_derate;
  ytarg = cfyfs/yspoilderate*brs_grad_derate;
#endif

  /*printf("loggrd.tx_xyz = %f, loggrd.xrta.xyz = %d\n",  loggrd.tx_xyz, loggrd.xrta.xyz);*/
  if ((amppwgrad(-brs_xarea, xtarg,
                 0.0 /* start amp */, 0.0 /* end amp */,
                 phygrd.xrt, MIN_PLATEAU_TIME, &a_gxspoil,
                 &pw_gxspoila, &pw_gxspoil, &pw_gxspoild))==FAILURE) {
    epic_error(use_ermes,supfailfmt,EM_PSD_SUPPORT_FAILURE,
        1,STRING_ARG,"amppwgrad:gxspoil");
    return FAILURE;
  }

  if ((amppwgrad(-brs_yarea, ytarg,
                 0.0 /* start amp */, 0.0 /* end amp */,
                 phygrd.yrt, MIN_PLATEAU_TIME, &a_gyspoil,
                 &pw_gyspoila, &pw_gyspoil, &pw_gyspoild))==FAILURE) {
    epic_error(use_ermes,supfailfmt,EM_PSD_SUPPORT_FAILURE,
        1,STRING_ARG,"amppwgrad:gyspoil");
    return FAILURE;
  }

  return SUCCESS;
}

STATUS set_gzvl_params() {
  if (brs_gzvl_flag) {
    FILE *fp = NULL;
    float target = loggrd.tz;
    int slice;
    
    a_gzvlw = loggrd.tz;
    ia_gzvlw = a_gzvlw * max_pg_iamp / (loggrd.tz);
    /*pw_gzvlw = pw_gzcomb_tot;*/
    pw_gzvlw = 0;
   
    brs_gzvl_area_base = 0.5*(float)pw_gzcomba*a_gzcomba +
        0.5*(float)pw_gzcomb*(a_gzcomba + a_gzcombb) +
        0.5*(float)pw_gzcombd*a_gzcombb;
 
    fp = fopen("gzvl.txt", "a");
    fprintf_timestamp(fp);

    fshowf(fp, brs_gzvl_area_base);
    fshowf(fp, target);
    fshowi(fp, zrt);
    /* we store the "no slice encode" (just refocus) in */
    /* an extra waveform                                */
    for(slice=0; slice<equant+1; slice++) 
    {
      float area, frac, aa, ab;
      int pwa, pw, pwd;
      
      /*
      GRAD_PULSE gp = { G_ARBTRAP, (int *)&pwa, (int *)&pwd, (int *)&pw, 
        (float *)NULL, (float *)&aa, (float *)&ab, 
        (float *)NULL, NULL, 1, 1.0, (int *)NULL , 0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0.0};
      */
      
      if (equant == slice) frac = 0.5;
      else                 frac=(float)slice/(float)(equant-1);
      
      area = -brs_gzvl_area_base * ((1.0-frac)*a_comb+frac*a_end)/a_comb;
    
      /*
      area = ((float)slice*(a_comb - a_end)/
             (float)(equant-1) - a_comb);
      */ 

      /*if ((amppwgradmethod(&gp, area, target, 
              0.0 , 0.0 ,
              zrt, MIN_PLATEAU_TIME))==FAILURE) {
        return FAILURE;
      }*/
      /*if ((amppwgradmethod(&gp, area, target, 
              0.0, 0.0, zrt, pw_gzcomb))==FAILURE) {
        return FAILURE;
      }
      */
      if (FAILURE == amppwtpe(&aa, &ab, &pw, &pwa, &pwd, target, zrt, fabs(area))) {
        return FAILURE;
      }


      pw_gzvla[slice]=pwa;
      pw_gzvl[slice]=pw;
      pw_gzvld[slice]=pwd;
      ia_gzvlwa[slice] = (aa / target) * MAX_PG_IAMP;
      if (area<0) ia_gzvlwa[slice] *= -1;
      ia_gzvlwb[slice] = (ab / target) * MAX_PG_IAMP;
      if (area<0) ia_gzvlwb[slice] *= -1;
      if (pwa+pw+pwd>pw_gzvlw) pw_gzvlw = pwa + pw + pwd;
      
      fprintf(fp, "slice=%d area=%f pwa=%d pw=%d pwd=%d aa=%f ab=%f\n",
                   slice, area, pwa, pw, pwd, aa, ab);
    }
    pw_gzvlmin = pw_gzvlw;
    for (slice = 0; slice<equant+1; slice++) {
      int pwtot = pw_gzvla[slice]+pw_gzvl[slice]+pw_gzvld[slice];
      if (pwtot<pw_gzvlmin) pw_gzvlmin = pwtot;
    }
    
    per_gzvlw = (GRAD_UPDATE_TIME);
    res_gzvlw = pw_gzvlw/per_gzvlw;
    brs_echo_wait = pw_gzvlw - pw_gzvlmin;
    fclose(fp);
  } else {
  }
  return SUCCESS;
}

/*************************************************************/ 

@host Spiral2DRF
  if (brs_2dflag) {
    if (brs_ssfp_flag) {
      if( PSD_OFF == brs_2d_fiesta_rf_flag ) {
          /*
           * This is a 3.5ms half SINC pulse (no side lobes) with a 90
           * degree nominal flip angle, a nominal bandwidth of 571 Hz,
           * and a max B1 of 0.0398.  The initial pulse width is set
           * to 480us to achieve the shorter TRs.  This is the default
           * RF pulse for the FIESTA 2D technique.
           */
          rfpulse[RF1_SLOT].abswidth = SAR_ABS_SINC05;
          rfpulse[RF1_SLOT].area     = SAR_ASINC05;
          rfpulse[RF1_SLOT].effwidth = SAR_PSINC05;
          rfpulse[RF1_SLOT].dtycyc   = SAR_DTYCYC_SINC05;
          rfpulse[RF1_SLOT].maxpw    = SAR_MAXPW_SINC05;
          rfpulse[RF1_SLOT].max_b1   = SAR_MAXB1_SINC05;
          rfpulse[RF1_SLOT].max_int_b1_sq = SAR_MAX_INT_B1_SQ_SINC05;
          rfpulse[RF1_SLOT].max_rms_b1 = SAR_MAX_RMS_B1_SINC05; 
          rfpulse[RF1_SLOT].nom_pw   = 3.5ms;
          rfpulse[RF1_SLOT].nom_bw   = 571.0;
          rfpulse[RF1_SLOT].nom_fa   = 90.0;
          rfpulse[RF1_SLOT].act_fa   = &flip_rf1;
          rfpulse[RF1_SLOT].activity = PSD_APS2_ON + PSD_MPS2_ON + PSD_SCAN_ON;
          rfpulse[RF1_SLOT].num = 1;

          pw_rf1_full = 480us;
          pw_rf1 = 480us;

      } else {

          /*
           * This alternate RF pulse is a 500us Time BandWidth (TBW)
           * pulse with truncated tails, a 90 degree nominal flip
           * angle, a nominal bandwidth of 4 KHz, and a max B1 of
           * 0.197458.
           */
          rfpulse[RF1_SLOT].abswidth = 0.5947;
          rfpulse[RF1_SLOT].area     = 0.5947;
          rfpulse[RF1_SLOT].effwidth = 0.4440;
          rfpulse[RF1_SLOT].dtycyc   = 1.0;
          rfpulse[RF1_SLOT].maxpw    = 1.0;
          rfpulse[RF1_SLOT].max_b1   = 0.197458;
          rfpulse[RF1_SLOT].max_int_b1_sq = 0.00865607;
          rfpulse[RF1_SLOT].max_rms_b1 = 0.131576; 
          rfpulse[RF1_SLOT].nom_pw   = 500us;
          rfpulse[RF1_SLOT].nom_bw   = 4000.0;
          rfpulse[RF1_SLOT].nom_fa   = 90.0;
          rfpulse[RF1_SLOT].act_fa   = &flip_rf1;
          rfpulse[RF1_SLOT].activity = PSD_APS2_ON + PSD_MPS2_ON + PSD_SCAN_ON;
          rfpulse[RF1_SLOT].num = 1;

          pw_rf1_full = 500us;
          pw_rf1 = 500us;

      }

      gscale_rf1 = 1.00; /* Don't Widen the pulse */
      cyc_rf1 = 0.5;     /* No. of sinc cycles for RF1 */

      pw1_eff = pw_rf1 / (int)(4.0f * cyc_rf1);

      res_rf1 = (int)(pw_rf1 / RF_UPDATE_TIME);
      res_rf1_full = (int)(pw_rf1_full / RF_UPDATE_TIME);

      cutpostlobes = 0;
      pre_lobes = 0;
      post_lobes = 0;

      /* offset to where real 90 occurs */
      off90 = 0;
      t_exb = pw1_eff;
      /* bandwidth of rf1 */
      bw_rf1 = (int)(4.0f * cyc_rf1 / ((float)pw_rf1_full / (float)1.0s));
        
    } else {
      rfpulse[RF1_SLOT].abswidth = SAR_ABS_TRUNC1;
      rfpulse[RF1_SLOT].area = SAR_ATRUNC1;
      rfpulse[RF1_SLOT].effwidth = SAR_PTRUNC1;
      rfpulse[RF1_SLOT].dtycyc = SAR_DTYCYC_TRUNC1;
      rfpulse[RF1_SLOT].maxpw= SAR_MAXPW_TRUNC1;
      rfpulse[RF1_SLOT].max_b1 = MAX_B1_TRUNC1_24_90;
      rfpulse[RF1_SLOT].nom_fa = 90.0;
      rfpulse[RF1_SLOT].act_fa = &flip_rf1; /* MRIge30667 */
      rfpulse[RF1_SLOT].nom_bw = 1250.0;
      rfpulse[RF1_SLOT].activity = PSD_APS2_ON + PSD_MPS2_ON + PSD_SCAN_ON;
      rfpulse[RF1_SLOT].nom_pw = 2.4ms; /* MRIge66555 */
      
      gscale_rf1 = 1.00; /* Don't Widen the pulse*/
      cyc_rf1 = 1.0; /* No. of sinc cycles for RF1 */
      frac_rf = 1; /* always use frac. rf */
      
      /* MRIge66555 - only for ECHOTRAIN with opslthick > minph_limit
       since RTIA pulses are now used for regular fgre so that
       truncated sinc1 of 1.5ms is no longer valid */
      pw_rf1_full = 800us;
      res_rf1_full = pw_rf1_full / RF_UPDATE_TIME;
      
      cutpostlobes = frac_rf;
      pre_lobes = (int)(2.0 * cyc_rf1) - 1;
      post_lobes = ((int)(2.0 * cyc_rf1) - 1) - cutpostlobes;
      
      pw1_eff = pw_rf1_full / (int)(4.0f * cyc_rf1);
      t_exb = (post_lobes + 1) * pw1_eff;
      bw_rf1 = (int)(4.0f * cyc_rf1 / ((float)pw_rf1_full / (float)1.0s));
      
      /* Redefine pulse width and resolution of RF based on fract.
       RF calcs */
      pw_rf1 = pw_rf1_full - (cutpostlobes * pw1_eff);
      res_rf1 = pw_rf1 / RF_UPDATE_TIME;
    }
  }


/*************************************************************/ 

@host Spiral_gzrf1_params
  if (brs_2dflag) {
    t_exa = pw_gzrf1a + (pre_lobes + 1) * pw1_eff;
  }

  if (2 != brs_excite_grad) {
    pw_gzrf1sa = pw_gzrf1a;
    pw_gzrf1sd = pw_gzrf1d;
    pw_gzrf1s  = pw_gzrf1;
     a_gzrf1s  =  a_gzrf1;
  }
/*************************************************************/ 

@host Spiral_gzcomb_params
  if (BRS)   /* BMK 2007.06.26 */
  {
    TempVar = (loggrd.tz<(loggrd.tz/endviewz_scale))?loggrd.tz:(loggrd.tz/endviewz_scale);
  }

  if (brs_2dflag) {
    refocus = a_gzrf1 * (0.5 * (FLOAT)pw_gzrf1d +
                                  (FLOAT)(off90 + t_exb) );
  }


  if (brs_excite_grad != 2) {
    double targ=loggrd.tz;
    int risetime=loggrd.zrt;
    if ( 0 == brs_excite_grad) { targ = loggrd.tx_xz; risetime=loggrd.xrt;}
    if ( 1 == brs_excite_grad) { targ = loggrd.ty_yz; risetime=loggrd.yrt;}
    if ((amppwgradmethod(&gradz[GZ1_SLOT], -refocus, targ,
                         0.0 /* start amp */, 0.0 /* end amp */,
                         risetime, MIN_PLATEAU_TIME))==FAILURE) {
        epic_error(use_ermes,supfailfmt,EM_PSD_SUPPORT_FAILURE,
                   EE_ARGS(1),STRING_ARG,"amppwgradmethod:gz1");
        return FAILURE;
    }
    pw_gz1sa = pw_gz1a;
    pw_gz1sd = pw_gz1d;
    pw_gz1s  = pw_gz1;
     a_gz1s  =  a_gz1;
    
    refocus = 0.0;
  }

/*************************************************************/ 
@host SpiralPredownload
if (BRS)
{
    brs_genviewtab(brs_numleaves_acq,
                   brs_nphases,
                   opslquant,
                   brs_vieword,
                   brs_nfolds,
                   brs_leafskip,
                   brs_leafgroup,
                   brs_dofracz,
                   brs_fracz_fact,
                   1 /*brs_debug_vieword*/,
                   &brs_fs_slice,
                   brs_jumptab,
                   brs_viewtab);

    /*rhrecon = 69;*/       /* BOXU 2009.10.07 */
    rhrecon = brs_rhrecon;

    rhexecctrl = 2;
    autolock = 1;
    phys_record_flag = PSD_ON;

    rhuser2 = brs_type;
    rhuser3 = (brs_type == 2) ? brs_fov1 : brs_alpha;
    rhuser4 = (brs_type == 2) ? brs_fov2 : brs_sampfact;
    rhuser5 = brs_leaflen;
    rhuser6 = brs_numleaves;
    rhuser7 = brs_gmax;
    rhuser8 = brs_gslew;
    rhuser9 = cfswgut;
    rhuser12 = golden_ratio_flag;  /*  BOXU 2010.09.28  */
    rhuser13 = brs_numleaves_acq;
    rhuser16 = brs_nphases;
    rhuser17 = rsp_info[0].rsprloc;
    rhuser18 = rsp_info[0].rspphasoff;
    rhuser19 = brs_mapdel_act;
    rhuser20 = brs_gradlen;
    rhuser21 = brs_vieword;
    if (brs_type == 2)
        rhuser23 = brs_fov0;
    else if (brs_type == 3) {
        rhuser22 = brs_rscale;
        rhuser23 = brs_fovpow;
    } else {
        rhuser22 = brs_matrixsize_center;
        rhuser23 = brs_alpha_center;
        rhuser24 = brs_sampfact_center;
    }
    /*
    rhuser25 = brs_dofracz ? (int)(opslquant*brs_fracz_fact) : (int)opslquant;
    */
    rhuser25 = pfkz_total;
    rhuser27 = brs_nfolds;
    
    rhuser28 = 0; /* pmtype */
    
    if (ssfat)
        rhuser29 = 2;
    if (ssfat && ssfat_kaiser)
        rhuser30 = time_ssfprep + kaiser_ramplen*act_tr;
    else if (ssfat)
        rhuser30 = time_ssfprep;
    else if (brs_s5fp)
        rhuser30 = time_s5fpprep;
    rhuser31 = opxres;

    rhuser32 = (brs_psc) ? brs_psc_prot_no : 0;

    rhuser33 = (brs_fwflag) ? brs_fw_te_step : 0;

    rhuser34 = brs_pm_type;
    rhuser35 = brs_pm_numleaves;
    rhuser36 = brs_extra_len; /* 2013-7-14 BOXU */

    rhcphases = opcphases;

    rhuser10 = brs_recratio;
    if (BRS_PERIPHERAL_REL_PRIME == brs_vieword)
    {
        rhuser11 = brs_leafskip;
    }

    if (brs_psc > DYNA_OFF) {
      /* save relevant imaging parameters to file */
      if (-1 == fprint_psc_protocol((char*)PSC_PROTOCOL)) {
        epic_error(use_ermes, "%s failed", EM_PSD_SUPPORT_FAILURE, 1,
                   STRING_ARG, "fprint_psc_protocol");
        return FAILURE;
      }
      if (DYNA_MASK == brs_psc) {
        int no = psc_store_protocol((char*)PSC_PROTOCOL, brs_exno);
        if (no < 1) {
          epic_error(use_ermes, "%s failed", EM_PSD_SUPPORT_FAILURE, 1,
                   STRING_ARG, "psc_store_protocol");
          return FAILURE;
        }
        brs_psc_prot_no = no;
      }
      if ((DYNA_CONTRAST == brs_psc) || (DYNA_SUBTRACT == brs_psc)) {
        int no = psc_find_protocol((char*)PSC_PROTOCOL, brs_exno);
        if (no < 1) {
          epic_error(use_ermes, "No valid mask found (%s failed)", EM_PSD_SUPPORT_FAILURE, 1,
                   STRING_ARG, "psc_find_protocol (please acquire MASK) ");
          return FAILURE;
        }
        brs_psc_prot_no = no;
      }
      /* check that sdc's rhosts file allows agp to rlogin 
         to host */
      if (-1 == check_rhosts_file()) {
        epic_error(use_ermes, 
          "Unable to set up .rhosts file for sdc (%s failed)",
          EM_PSD_SUPPORT_FAILURE, 1, STRING_ARG, "check_rhosts_file");
        return FAILURE;
      }
    }

}

/*************************************************************/ 
@host SpiralRotations
/* needs to be done before scalerotmats but after orderslice */
if (BRS)
{
  long mon_loc_rot[9];
  long real_rot[9];
  int i;
  float monitor_loc[3], slab_loc[3];

  /* grab the rotation array before we play with it for spiral rotations */
  for (i = 0; i < opvquant; i++) {
    for (j = 0; j < 9; j++) {
      brs_savrot[i][j] = rsprot[i][j];
    }
  }

  /* arterial phase selection tracker stuff */
  monitor_loc[0] = mon_loc.oprloc;
  monitor_loc[1] = mon_loc.opphasoff;
  monitor_loc[2] = mon_loc.optloc;

  slab_loc[0] = 0.0;
  slab_loc[1] = 0.0;
  slab_loc[2] = 0.0;

  for (i=0; i<9; i++) 
  { 
    /* mon_loc.oprot is an array of shorts
     * CalcRotationMatrix wants arrays of longs
     */
    mon_loc_rot[i] = (long) mon_loc.oprot[i];
    real_rot[i] = 0;
  }
  /* for opentry = 1 (head first) reverse x and z */
  real_rot[0] = (2 == opentry)? max_pg_iamp : -max_pg_iamp;
  real_rot[4] = max_pg_iamp;
  real_rot[8] = (2 == opentry)? max_pg_iamp : -max_pg_iamp;
  
  /*CalcRotationMatrix(mon_loc_rot, rsprot[0], rotmatrix, 0);*/
  CalcRotationMatrix(mon_loc_rot, real_rot, rotmatrix, 0);
  RotateMat(monitor_loc, rotmatrix, slab_loc);
  rhuser46 = slab_loc[0];
  rhuser47 = slab_loc[1];
  rhuser48 = slab_loc[2];
}
@pg SpiralPG

int echo2dab;
WF_PULSE *echo2rba;
int echo2rbarsp;
int rf2frqrsp, echo2xtrrsp;
WF_PULSE_ADDR prf2frq, pecho2xtr, rec_unblank2;
short amp_gzrf1, amp_gzrf1s, amp_gz1, amp_gz1s;

WF_PULSE pulseptr[MAXSLQUANT3D];
WF_HW_WAVEFORM_PTR gzvlp[MAXSLQUANT3D];
WF_PULSE gzvlw = INITPULSE;

#if ESEMAJOR<27
float epsilon__ = -1.0;

double  fclean(double x)
{
    static float        y;
    y = x;
    return y;   /* prevents optimisation */
}

float floatsEpsilon()
{
  if (epsilon__ < 0.0) {
    static float feps = 1.0;
    while ( fclean(1.0+feps) > 1.0 ) feps = 0.5*feps;
    epsilon__ = 2.0*feps;
  }
  return epsilon__;
}
short floatsAlmostEqualEpsilons( const float a,
                                 const float b,
                                 const unsigned int neps )
{
  return fabs(a-b) < neps*floatsEpsilon();  
}
#endif

/*
 *  stretch_pulse
 *
 *  Type: Function
 *
 *  Description:
 *    This routine allocates enough waveform memory to store the rf
 *    pulse.  Also, for the rf pulse in the given slot, check if it
 *    was scaled.  If it was, then set new resolution and stretch
 *    external pulse.
 */
STATUS
stretch_pulse( const INT slot,
               CHAR *extname,
               const RF_PULSE_INFO rfInfo[],
               INT *res,
               short **wavespace )
{
    short *temp_wave_space;

    /* Create some RHO waveform space, read in the
       pulse to local mem, and then move the local mem
       to the reserved RHO mem. */
    temp_wave_space = (short*)AllocNode( (*res) * sizeof(short) );
#ifdef IPG
    /* Only read external file if filename is provided */
    uextwave( temp_wave_space, (short)(*res), extname );
#endif

    /* Stretch rf pw, if needed */
    if( rfInfo[slot].change == PSD_ON )
    {
        *wavespace = (short*)AllocNode( rfInfo[slot].newres * sizeof(short) );
        stretchpulse( *res, (INT)(rfInfo[slot].newres),
                      temp_wave_space, *wavespace );
        *res = (INT)(rfInfo[slot].newres);
        FreeNode( temp_wave_space );
    }
    else
    {
        *wavespace = temp_wave_space;
    }

    return SUCCESS;
}   /* end stretch_pulse() */

void create_gz1(int pos)
{
        /* BRS ZGRAD ==> (WF_PROCESSOR)brs_excite_grad */
        TRAPEZOID((WF_PROCESSOR)brs_excite_grad,gz1,pos,0,TYPNDEF, loggrd);
}

void create_gz1s(int pos)
{
        /* BRS ZGRAD ==> (WF_PROCESSOR)brs_excite_grad */
        TRAPEZOID((WF_PROCESSOR)((brs_excite_grad+1)%2),gz1s,pos,0,TYPNDEF, loggrd);
}

void create_gzvl(int pos, int idx)
{
  s16 *gzvlw_mem = NULL;
  int slice;
  
  pulsename(&gzvlw,"gzvlw");
  createreserve(&gzvlw, ZGRAD, res_gzvlw);
  createinstr(&gzvlw, pos, pw_gzvlw, ia_gzvlw);
  setwave(gzvlp[0], &gzvlw, idx);

  if (idx > 0) {
    /* we have already created the waveforms below */
    return;
  }

  gzvlw_mem = (s16 *)AllocNode( res_gzvlw*sizeof(s16));

  getbeta(&pg_beta, ZGRAD, &loggrd);

  for(slice = 0; slice<equant+1; slice++) {
    s16 gzvlw_indx = 0;
    char instrname[16];

    /* Up ramp */
    uramp( (&gzvlw_mem[gzvlw_indx]), (pw_gzvla[slice]/per_gzvlw), (short) 0, ia_gzvlwa[slice] , pg_beta);
    /* Clear EOW */
    gzvlw_indx = pw_gzvla[slice]/per_gzvlw;
    gzvlw_mem[gzvlw_indx-1] &= ~WEOS_BIT;

    /* Top const */
    uramp((&gzvlw_mem[gzvlw_indx]), (pw_gzvl[slice]/per_gzvlw), ia_gzvlwa[slice], ia_gzvlwb[slice], pg_beta);
    /* Clear EOW */
    gzvlw_indx = ((pw_gzvla[slice] + pw_gzvl[slice]) / per_gzvlw );
    gzvlw_mem[gzvlw_indx-1] &= ~WEOS_BIT;
    
    /* Decay Ramp */
    uramp( (&gzvlw_mem[gzvlw_indx]), (pw_gzvld[slice]/per_gzvlw), ia_gzvlwb[slice], (short) 0, pg_beta );
    gzvlw_indx = ((pw_gzvla[slice] + pw_gzvl[slice] + pw_gzvld[slice]) / per_gzvlw );
    if (res_gzvlw > gzvlw_indx) {
      /* Clear EOW */
      gzvlw_mem[gzvlw_indx-1] &= ~WEOS_BIT;
      /* Trailing edge of zeros */
      uramp( (&gzvlw_mem[gzvlw_indx]), res_gzvlw - gzvlw_indx, (short)0, (short)0, pg_beta );
    }

    /* Move user pulse into waveform mem */
    gzvlw_mem[res_gzvlw-1] |= WEOS_BIT;  
    sprintf(instrname, "gzvl%d", slice);
    pulsename(&pulseptr[slice], instrname);
    createreserve(&pulseptr[slice], ZGRAD, res_gzvlw);
    movewaveimm(gzvlw_mem, &pulseptr[slice], (long)0, (short)(res_gzvlw),TOHARDWARE);
    gzvlp[slice]=pulseptr[slice].wave_addr;
  }      
  FreeNode( gzvlw_mem );


}

STATUS brs_gzvl_adjust_te()
{
  if (brs_gzvl_flag) {
    int daqpos = (int)brs_daqdel;
    int end_of_rf1 = 0; /* relative */
    
    int position = end_of_rf1-pw_gzrf1a-psd_rf_wait-pw_rf1;
    int rf1_to_posreadout_gzcomb 
       = RUP_GRD(position + t_exa + te_time - t_rd1a);
    
    /* extra 4us to make room for maps1 */
    int end_of_rec_unblank = end_of_rf1 + rfupd + 4us;
    int PosXtrPkt = RUP_GRD(end_of_rec_unblank + 4us); 
    
    int rf1_to_posreadout_gvzl 
      = RUP_GRD( IMax(2, PosXtrPkt 
            + (XTR_length[bd_index]+XTRSETLNG)
            - (daqpos+psd_grd_wait)
            , RUP_GRD(end_of_rf1 - psd_rf_wait
              + pw_gzrf1d + pw_gzvlmin))
          );
    brs_gzvl_delte = rf1_to_posreadout_gzcomb - rf1_to_posreadout_gvzl;
    te_time -= brs_gzvl_delte;
    non_tetime += brs_gzvl_delte;
  }
  return SUCCESS;
}

STATUS GenerateSpoil(int position)
{
  TRAPEZOID(XGRAD, gxspoil, RUP_GRD(position+pw_gxspiral+pw_gxspoila),0,TYPNDEF,loggrd);  
  TRAPEZOID(YGRAD, gyspoil, RUP_GRD(position+pw_gyspiral+pw_gyspoila),0,TYPNDEF,loggrd); 
  return SUCCESS;
}

STATUS GenerateSpiral(int position)
{
    int i;
    short ibuf[MAX_LEAF_LEN];  
    INTWAVE(XGRAD, gxspiral, position, loggrd.xfs, brs_gradlen+brs_ramplength, brs_xgrad, loggrd);
    INTWAVE(YGRAD, gyspiral, position, loggrd.yfs, brs_gradlen+brs_ramplength, brs_ygrad, loggrd);

    if (0==brsfc_flag)
      GenerateSpoil(position);
    return SUCCESS;
}

STATUS GenerateSpiral2(int position)
{
    int i;
    short ibuf[MAX_LEAF_LEN];  
    INTWAVE(XGRAD, gxspiral2, position, loggrd.xfs, brs_gradlen2+brs_ramplength2, brs_xgrad2, loggrd);
    INTWAVE(YGRAD, gyspiral2, position, loggrd.yfs, brs_gradlen2+brs_ramplength2, brs_ygrad2, loggrd);
    return SUCCESS;
}


STATUS FlowCompXY(int position1x, int position1y, int position2x, int position2y)
{    
  TRAPEZOID(XGRAD, gxbrsfc1, position1x, 0, TYPNDEF, loggrd);  
  TRAPEZOID(XGRAD, gxbrsfc2, position2x, 0, TYPNDEF, loggrd);
  TRAPEZOID(YGRAD, gybrsfc1, position1y, 0, TYPNDEF, loggrd); 
  TRAPEZOID(YGRAD, gybrsfc2, position2y, 0, TYPNDEF, loggrd); 
  return SUCCESS;
}

STATUS FlowCompZ(int position1z, int position2z)
{    
  TRAPEZOID(ZGRAD, gzbrsfc1, position1z, 0, TYPNDEF, loggrd);  
  TRAPEZOID(ZGRAD, gzbrsfc2, position2z, 0, TYPNDEF, loggrd);
   return SUCCESS;
}

STATUS FlowCompZecho1(int position1z, int position2z)
{    
  TRAPEZOID(ZGRAD, gzbrsfc1echo1, position1z, 0, TYPNDEF, loggrd);  
  TRAPEZOID(ZGRAD, gzbrsfc1echo2, position2z, 0, TYPNDEF, loggrd);
  return SUCCESS;
}

STATUS HystGrad(int pos_hyst)
{
    TRAPEZOID(XGRAD, gxhyst1, pos_hyst, 0, TYPNDEF, loggrd);
    TRAPEZOID(YGRAD, gyhyst1, pos_hyst, 0, TYPNDEF, loggrd);
    TRAPEZOID(XGRAD, gxhyst2, pos_hyst+hst_length, 0, TYPNDEF, loggrd);
    TRAPEZOID(YGRAD, gyhyst2, pos_hyst+hst_length, 0, TYPNDEF, loggrd);
    return SUCCESS;
}

STATUS BlipGrad(int pos_blip)
{
  TRAPEZOID(XGRAD, gxb, pos_blip, brs_xbliparea,,loggrd);
  TRAPEZOID(YGRAD, gyb, pos_blip, brs_ybliparea,,loggrd);
  return SUCCESS;
}



@rsp SpiralRSP
int leafoffset;
int jumpno;
short acquired_viewtab_raw[196608];
int acqindex;
float golden_ratio_angle;
int brs_last_view;
short gx_hyst; /* Gx table for reverse rotated values */
short gy_hyst; /* Gy table for reverse rotated values */
int brs_fwdel;
int rsp_echo_wait;

STATUS set_gz_encode(int sl, int idx)
{
  if (brs_gzvl_flag) {
    int s = (-1==sl) ? equant : sl;
    setwave(gzvlp[s],&gzvlw,idx);
    rsp_echo_wait = pw_gzvla[s] + pw_gzvl[s] + pw_gzvld[s] - pw_gzvlmin; 
  } else {
    if (-1 == sl) {
      short temp_short = (short)(max_pg_iamp*(-a_base/loggrd.tz)); /* set up zero slice encode */
      setiamp(temp_short,&gzcomb,idx);	          /* (just refocus) */
    } else {
      setiamp(volumetab[sl], &gzcomb, idx);
    }
    rsp_echo_wait = 0;
  }
  if (-1 == sl) {
    short temp_short = (short)(max_pg_iamp*(a_base2/loggrd.tz)); /* set up zero rewinder */
    if (zrewind_flag) {
      setiamp(temp_short,&gzp,idx);		  /* (just killer) */
    }
  } else {
    setiamp(volumetab2[sl], &gzp, idx);
  }
  return SUCCESS;
}

STATUS
brs_set_echo1frequency( INT freq,
                    INT n_inst )
{
    setfrequency( freq, &echo1, n_inst );
    if (PM_ADDECHO == brs_pm_type) {
      setfrequency( freq, &echo2, n_inst );
    }
#if ESEMAJOR >= 15
    if (opetl>=2) {
       int echoindex;
       for(echoindex=1; echoindex<(opetl-1); echoindex+=2) {
          setfrequency( freq, &(echo2toN[echoindex]), n_inst );
       }
    }
#endif
    return SUCCESS;
}   /* end set_echo1frequency() */

STATUS spiral_psdinit(void)
{
  ssfat_num = 0;
  ssfatexphase = 0;
  ResetGoldenRatio();
  
  if (brs_shim_flag) {
    short brs_shim[3]={brs_shim_x, brs_shim_y, brs_shim_z};
    printf("Setting shim to %d %d %d\n", brs_shim[0],
            brs_shim[1], brs_shim[2]);
    setshimimm(brs_shim, brs_shim_update_type );
  }

  if (L_SCAN == rspent) {
    if (DYNA_MASK == brs_psc) {
      if (-1 == save_prescan_params(brs_exno, brs_psc_prot_no)) {
         psdexit(EM_PSD_ROUTINE_FAILURE, 0,"", "save_prescan_params failed",
                 PSD_ARG_STRING,"save_prescan_params",0);
      }
    } else if ((DYNA_CONTRAST == brs_psc) || (DYNA_SUBTRACT == brs_psc)) {
      if (-1 == load_prescan_params(brs_exno, brs_psc_prot_no)) {
         psdexit(EM_PSD_ROUTINE_FAILURE, 0,"", "load_prescan_params failed",
                 PSD_ARG_STRING,"load_prescan_params",0);
      }
    }
  }
  return SUCCESS;

}

STATUS spiral_ps2core(void)
{
    short rfchop;

    rfchop = 1;

    /* Initialize yres_phase and slab_phase to zero */
    yres_phase = 0;
    slab_phase = 0;

    /* Chop the receiver in APS2/MPS2 */
    chop_phase = -1;

    printdbg("Starting ps2core",debugstate);

    set_gz_encode(-1, 0);

    ShiftTE(0);

    /* 3d oblique - changed sliceindex to slabindex - latha@mr */
    /* Need to set this to the prescan slab */
    slabindex = rspesl;
    sp_sat_index = slabindex;

    setfrequency(rf1_freq[slabindex],&rf1,scanrf1_inst);
    /*setfrequency(receive_freq1[slabindex], &echo1, 0);*/
    brs_set_echo1frequency(receive_freq1[slabindex], 0);
    /* end 3d oblique - latha@mr */

    slice  = 0;               /* slices indexed from 0 instead of 1 */
    spgr_count = 1;           /*initialize spgr counter */ 

    /* BMK 2007.06.27 */
#if ESEMAJOR >= 14
    fgre_loaddab_echo1(slice, dabecho, dabop, dabview, DABOFF);
#else
    fgre_loaddab_echo1(slice, dabecho, dabop, dabview,
                       DABOFF, PSD_LOAD_DAB_ALL);
#endif
    if (opetl>=2) {
        fgre_loaddab_echo2(slice, (dabecho+1), (opetl-1), nshots, dabop, dabview, DABOFF);
    }/* BOXU 2011.12.14 */


    rotate_spiral(0,0,0.0);

    /* collect disdaq views */
    for (view = -rspdda; view < 0; view++)
    {
        spoil();
        startseq((SHORT)slabindex,(SHORT)MAY_PAUSE); /* 3d oblique - made sliceindex as 0 - latha@mr */
        syncoff(&seqcore);

        /* Chop exciter even during ps2 disdaqs to make sure that dynamic 
           equilibrium is maintained */
        chop_phase = -chop_phase;
    }

    rspskp = 1;

    /* start view loop */
    for (view = 1; view <= rspvus; view++)
    {
        if ((view%rspskp) == 0) {
            acq_echo1 = DABON;
        } else {
            acq_echo1 = DABOFF;
        }
        if (opetl>=2) acq_echo2 = DABOFF; /* BOXU 2011.12.14 */

#if ESEMAJOR >= 14   /* BMK 2007.06.27 */
        fgre_loaddab_echo1(slice, dabecho, dabop, dabview, acq_echo1);
#else
        fgre_loaddab_echo1(slice, dabecho, dabop, dabview,
                           acq_echo1,PSD_LOAD_DAB_ALL);
#endif
        if (opetl>=2) 
        {
            fgre_loaddab_echo2(slice, (dabecho+1), (opetl-1), nshots, dabop, dabview, acq_echo2);
        }/* BOXU 2011.12.14 */

        /* start excitation loop */	
        for (excitation = 1; excitation <= rspnex; excitation++)
        {
            if((excitation == rspnex) || (rspent == L_APS2)) {
                attenlockoff(&attenuator_key);
            } else {
                attenlockon(&attenuator_key);
            }

            spoil();

            startseq(slabindex, (SHORT)MAY_PAUSE);

            syncoff(&seqcore);

            /* Chopper logic */
            chop_phase = -chop_phase;
        } /* excitation loop */
    } /* view loop */
    printdbg("Returning from spiral_ps2core",debugstate);
    return SUCCESS;
}


/* BOXU 2010.09.28   golden ratio angles  */
/*void cal_golden_angle(int numleaves, float **gr_pointer){
    float golden_value;
    int i;
    float *tmp;

    *gr_pointer = (float *)malloc(numleaves*sizeof(float));
    tmp = *gr_pointer;
    golden_value = (sqrt(5)+1)/2;
    for (i = 0; i < numleaves; i++){
        *tmp++ = ( i*golden_value - floor(i*golden_value) ) * 2.0 * M_PI;
    }

}*/
/*******************************************/
STATUS sethystamp(float cphi, float sphi)
{
  int count_echo;
  gx_hyst = ( a_hst*cphi + a_hst*sphi)*max_pg_iamp/loggrd.tx;
  gy_hyst = (-a_hst*sphi + a_hst*cphi)*max_pg_iamp/loggrd.ty;

  for(count_echo=1;count_echo<opetl;count_echo++)
  {
    setiampt( gx_hyst, &gxhyst1, count_echo);
    setiampt( gy_hyst, &gyhyst1, count_echo);
    setiampt(-gx_hyst, &gxhyst2, count_echo);
    setiampt(-gy_hyst, &gyhyst2, count_echo);
  }
  return SUCCESS;
}
/* BMK 2004.12.15 */
void rotate_spiral(int leaf, int slab, float additional)
{ 
  long rotmtx[1][9];
  int i;
  float phi;
  float cphi, sphi;
  float gxb_scale, gyb_scale;
  int count_echo;

  if (golden_ratio_flag){   /*  BOXU 2010.9.28 */
    if ( view != brs_last_view) {
      golden_ratio_angle += gr;
      if (brs_fwflag) {
        brs_fwdel += brs_fw_te_step;
      }
    }
    golden_ratio_angle -= floor(golden_ratio_angle);
    phi = golden_ratio_angle * 2.0 * M_PI;
  } else {
    phi = 2.0 * M_PI * leaf/(float)brs_numleaves_acq;
  }

  brs_last_view = view;

  cphi = cos(phi+additional);
  sphi = sin(phi+additional);

  if (hst_flag)
    sethystamp(cphi, sphi);

  if (brs_blipflag)
  {
    /*
    gxb_scale = cphi*cphi*brs_xx - sphi*cphi*(brs_yy-brs_yx) + sphi*sphi*brs_xy;
    gyb_scale = cphi*cphi*brs_yy - sphi*cphi*(brs_xy-brs_xx) + sphi*sphi*brs_yx;*/
    gxb_scale = brs_xx;
    gyb_scale = brs_yy;
    for(count_echo=0;count_echo<opetl-1;count_echo++) /* there are only opetl-1 blip gradient */
    {
      setiampt((int)((float)ia_gxb*gxb_scale), &gxb, count_echo);
      setiampt((int)((float)ia_gyb*gyb_scale), &gyb, count_echo);
    }
  }

  for (i = 0; i < 9; i += 3) {
    rotmtx[0][i] = (int)(  cphi*brs_savrot[slab][i] 
                         + sphi*brs_savrot[slab][i+1]);
    rotmtx[0][i+1] = (int)( -sphi*brs_savrot[slab][i]
                           + cphi*brs_savrot[slab][i+1]);
    rotmtx[0][i+2] = brs_savrot[slab][i+2];
  }

  scalerotmats(rotmtx, &loggrd, &phygrd, 1, 0);
  setrotate(rotmtx[0], slab);
  

  /* [  cos(a) sin(a) ]  [ 1 ]
   * [ -sin(a) sin(a) ]  [ 0 ]
   */
  if (0==brs_excite_grad) {
    /* rotate excitation gradients back */
    /* gzrf1 is on X, gzrf1s is on Y */
    setiampt((int)(  cphi * (float)amp_gzrf1) , &gzrf1 , 0);
    setiampt((int)(  cphi * (float)amp_gz1)   , &gz1   , 0);
    setiampt((int)( -sphi * (float)amp_gzrf1s), &gzrf1s, 0);
    setiampt((int)( -sphi * (float)amp_gz1s)  , &gz1s  , 0);
  }
  /* [  cos(a) sin(a) ]  [ 0 ]
   * [ -sin(a) sin(a) ]  [ 1 ]
   */
  if (1==brs_excite_grad) {
    /* rotate excitation gradients back */
    /* gzrf1 is on Y, gzrf1s is on X */
    setiampt((int)(  sphi * (float)amp_gzrf1s), &gzrf1s, 0);
    setiampt((int)(  sphi * (float)amp_gz1s)  , &gz1s  , 0);
    setiampt((int)(  cphi * (float)amp_gzrf1) , &gzrf1 , 0);
    setiampt((int)(  cphi * (float)amp_gz1)   , &gz1   , 0);
  }
}

STATUS PlayHTR(float scale)
{
  int temp_rf1;

  temp_rf1 = (int)(scale*(float)ia_rf1htr);
  boffset(off_seqhtrcore);
  setiamp(temp_rf1, &rf1htr, 0);
  exphase = (exphase + 4L*FS_PI) % FS_2PI - FS_PI;
  setiphase(exphase, &rf1htr, 0);
  set_gz_encode(0, 0);
  startseq((SHORT)slabindex,(SHORT)MAY_PAUSE);
  boffset(off_seqcore);

  return SUCCESS;
}
        
STATUS ShiftTE(int period)
{
  int len, len2;

  if ((PM_SELFGEN==brs_pm_type) || brs_flex) {
    len = period;
    len2 = brs_mapdel - period;
  } else {
    len = 0;
    len2 = 0;
  }
  setperiod(rsp_echo_wait+len+4us, &mapx, 0);
  setperiod(rsp_echo_wait+len+4us, &mapy, 0);
  setperiod(len+4us, &mapz, 0);
  setperiod(rsp_echo_wait+len+4us, &maps1, 0);
  setperiod(len2+4us, &maps2, 0);
  
  return SUCCESS;
}

STATUS ResetGoldenRatio()
{
  golden_ratio_angle = 0.0;
  brs_last_view = brs_viewtab[0].leaf;
  return SUCCESS;
}

STATUS play_pass_pkt()
{
  boffset(off_seqpass);

  /* pass gets set in spiral_scancore_phase */
  if(pass == (acqs-1)) {
    /* Set DAB pass packet to end of scan */
    setwamp(SSPD + DABPASS + DABSCAN, &pass_pulse, 2);
    printdbg("  End of Scan and Pass", debugstate);

    pause = MAY_PAUSE;
    /* If last pass, subtract sldetime part included in passtime
       MRIge57698 ....no sldelay for last acq  -agilandk@mr*/
    if  (mph_flag == PSD_ON ) {
      /* Auto Voice  04/18/2005 YI */
      setperiod ( (long)pass_seqtime_def, &seqpass, 0 ) ;
    }
  } else {
    /* Set DAB pass packet to end of pass */
    setwamp(SSPD + DABPASS, &pass_pulse, 2);
    printdbg("  End of Pass", debugstate);

    if (((pass+1) % slicecnt)==0) {
      pause = MUST_PAUSE;     /* pause if desired */
      setperiod ( (long)pass_seqtime_def, &seqpass, 0 ) ; /* Auto Voice  04/18/2005 YI */
    } else {
      pause = AUTO_PAUSE;     /* or if required */
      /* Auto Voice  04/18/2005 YI */
      if (mph_flag == PSD_ON ) {
        if(slicecnt == acqs) { /* MRIhc08979  08/05/2005 YI */
          setperiod ( (long)pass_seqtime_mph, &seqpass, 0 ) ;
        } else {
          setperiod ( (long)pass_seqtime_def, &seqpass, 0 ) ;
        }
      }
    }
  }
  startseq(0,(SHORT)pause);
  boffset(off_seqcore);
#ifdef PSD_HW   /* Auto Voice */
  if ((mph_flag == 1) && (pass != acqs-1) && (slicecnt == acqs)) { 
    broadcast_autovoice_timing(0, sldelay/1ms, TRUE, TRUE);
  }
#endif

  /* MRIhc08979  08/05/2005 YI */
  if (( sldeltime > 10s) && (pass != acqs -1) && (slicecnt == acqs) ) {
    /* sldeltime> 10 only if mph_flag = 1, hence implied*/
    /* no scandelay1 for the last acq. MRIge57698 */
    scandelay1();
  }


  return SUCCESS;
}
  
STATUS write_cine_out()
{
  if (brs_scantype == 3) {   /* BMK 2006.07.27 */  
    FILE *viewfile;
    int i;
    SPIRAL_VIEW *acquired_viewtab;
    
    acquired_viewtab = (SPIRAL_VIEW *)acquired_viewtab_raw;

    boffset(off_seqdelay3);
    setperiod(3000ms, &seqdelay3, 0);
    startseq((SHORT)0, (SHORT)MAY_PAUSE);

#ifdef PSD_HW
    viewfile = fopen("/usr/g/mrraw/cine_out.txt", "w");
#else
    viewfile = fopen("cine_out.txt", "w");
#endif

    for (i = 0; i < acqindex; i++) {
      if (acquired_viewtab[i].slice == -1)
        fprintf(viewfile, "triggered\n");
      else if (acquired_viewtab[i].slice == -2)
        fprintf(viewfile, "fatsat\n");
      else if (acquired_viewtab[i].slice == -3)
        fprintf(viewfile, "disdaq\n");
      else 
        fprintf(viewfile, "%d %d %d\n", acquired_viewtab[i].slice, acquired_viewtab[i].phase, acquired_viewtab[i].leaf); 
    } 
    fclose(viewfile);
  } 
  return SUCCESS;
}

/* ungated spiral scancore */
STATUS spiral_scancore()
{
  int phaseindex;

#ifdef PSD_HW   /* Auto Voice */
  if(!smartprep_flag) {
    broadcast_autovoice_timing(0, trigger_delay_silent_countdown/1ms, FALSE, TRUE);
  }
#endif
 
  for (phaseindex = 0;phaseindex <opfphases ;phaseindex++) {
    if (brs_mfa_flag) {
      float scale = brs_mfa_angles[phaseindex]/opflip;
      setiamp((int)(scale*(float)ia_rf1), &rf1, 0);
    }
    spiral_scancore_phase(phaseindex);

    play_pass_pkt();
  
  }
    
  write_cine_out();

  return SUCCESS;
}

  




/* ungated spiral scancore */
STATUS spiral_scancore_phase(int phaseindex)
{
    int ddcount;
    int tphase;
    int numacqs;
    int acqcount;
    int i, Te, Tr;
    int trigstate;
    float KaiserRamp[6]={0.057, 0.2328, 0.5000, 0.7672, 0.9425, 1.000};
#ifndef PSD_HW    
    FILE *views_fp = fopen("brs_views.txt","w");
#endif
    int flex_necho = 1; 
    pass = phaseindex;    
    slab_phase = 0;
    int count_echo;

   

#ifdef PSD_HW
    settrigger((short) TRIG_INTERN, (short) 0);
#endif

    boffset(off_seqcore);
    dabop = DABSTORE;

    /* disdaqs section */
    /* kaiser ramp up for ssfp */
    /******************    BOXU  2009.09.25  ******************/
    /*if (ssfp_flag)*/
    if (0)
    {
        for (i = 0; i < 6; i++)
        {
            spoil();

            view = 0;
            slice = 0;

            dabview = view + 1;
            dabecho = 0;
            dabslice = opslquant/2;

            setfrequency(rf1_freq[slabindex],&rf1,scanrf1_inst); /* 3doblique - latha@mr */
            /*setfrequency(receive_freq1[slabindex],&echo1,0);*/ /* 3d oblique - latha@mr */
            brs_set_echo1frequency(receive_freq1[slabindex], 0);
            
            set_gz_encode(dabslice, 0);
    
            acq_echo1 = DABOFF;
#if ESEMAJOR >= 14   /* BMK 2007.06.27 */
            fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);
#else
            fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview,
                       acq_echo1,PSD_LOAD_DAB_ALL);
#endif

            rotate_spiral(view, slabindex, 0.0);

            setiamp((int)(KaiserRamp[i]*ia_rf1), &rf1, 0);

            startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);

            syncoff(&seqcore);
        }

    }
    ddcount = disdaqs;
    while(ddcount <= -1)
    {

	      /*****  BOXU 2010.02.11 *****/	
	      if( pfkz_flag && specir_flag ) {
	        if( ((-ddcount) % pfkz_views_per_segment) == 0 ) {
            /* CRT ************************************* Pascal 02/21/11 */
            setrotate(rsprot[0], slabindex);  
		        if (brs_ssfp_flag) {
              PlayHTR(1.0);
              PlayHTR(0.5);
              KillerRsp();
            }
            ChemPrep();
            if (brs_ssfp_flag) {
              PlayHTR(0.5);
            }
	        }
		    }
        /************************/
        
        /*if(tm_prepslice_flag)
          tm_prepslice();*/
        if (brs_flex) flex_necho = opnecho;

        for(dabecho=0; dabecho<flex_necho; dabecho++) {
          if (ddcount < -pfkz_total) {
            view = 0;
            slice = 0;
            dabview = view + 1;
            dabslice = opslquant/2;
            acq_echo1 = DABOFF;
            if (opetl>=2)
              acq_echo2 = DABOFF;  /* BOXU 2011.12.14 */
          } else {
            view = 0;
            slice = brs_viewtab[pfkz_total+ddcount].slice;
            dabview = 0; /* put in the baseline */
            dabslice = slice;
            acq_echo1 = DABON;
            acq_echo2 = DABON;   /* BOXU 2011.12.14 */
            setiamp(0, &gxspiral, 0);
            setiamp(0, &gyspiral, 0);
  
            if (opetl>=2)
            {
              for(count_echo=1;count_echo<opetl;count_echo++)
              {
                setiamp(0, &gxspiral, count_echo);
                setiamp(0, &gyspiral, count_echo);
              }
            }
            if (brs_2dflag)
            {
              set_gz_encode(-1, 0); /* just refocus */
            }
          }
  

          setfrequency(rf1_freq[slabindex],&rf1,scanrf1_inst); /* 3doblique - latha@mr */
          setfrequency(receive_freq1[slabindex],&echo1,0); /* 3d oblique - latha@mr */
          /*if (opetl>=2)
            {
            set_echo2frequency(receive_freq2[slabindex], 0); 
            }*/
          if (opetl>=2)
          {
            for(count_echo=0;count_echo<(opetl-1);count_echo++)
              setfrequency(receive_freq1[slabindex],&(echo2toN[count_echo]),0);
          }
          /* BOXU 2011.12.14 */

          /* BOXU 2011.12.14 */
          
          if (brs_2dflag)
          {
            set_gz_encode(-1, 0);
          }
          else
          {
            set_gz_encode(dabslice, 0);
          }
     
          yres_phase = 0;
  
          /* grab the slab phase offset */
          if (brs_2dflag) {
            slab_phase = 0;
          } else {
            slab_phase = slab_off[slabindex].zsign * 
                      ((dabslice * slab_off[slabindex].zoffs +
                       3L*FS_PI)%FS_2PI-FS_PI);
          }
          spoil();
  
     
#if ESEMAJOR >= 14   /* BMK 2007.06.27 */
          fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);
#else
          fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview,
                         acq_echo1,PSD_LOAD_DAB_ALL);
#endif
          if (opetl>=2)
          {
            fgre_loaddab_echo2(dabslice, (dabecho+1), (opetl-1), nshots, dabop, dabview, acq_echo2);
          }   /* BOXU 2011.12.14 */
          if (brs_flex)
            ShiftTE(brs_mapdel*dabecho);
          else
            ShiftTE(brs_mapdel);

          rotate_spiral(view, slabindex, 0.0);
  
          startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);
  
          syncoff(&seqcore);

        } /* dabecho loop */

        ddcount++;

    }
    setiamp(ia_gxspiral, &gxspiral, 0);
    setiamp(ia_gyspiral, &gyspiral, 0);
    

    if(brs_blipflag)
    {
      for(count_echo=0;count_echo<opetl-1;count_echo++) /* there are only opetl-1 blip gradient */
      {
        setiampt(ia_gxb, &gxb, count_echo);
        setiampt(ia_gyb, &gyb, count_echo);
      }
    }
    if (brs_2dflag)
    {
      set_gz_encode(-1, 0);
    }
    
    /***************** BOXU 2009.09.15 *****************/
    /*****************  BOXU 2009.09.25   add brs_vieword ==4  ***/
    if (brs_vieword == 2 || brs_vieword == 4){	    
	    numacqs = brs_nphases * brs_numleaves_acq * pfkz_total;
      if (PM_ADDECHO == brs_pm_type)
        numacqs += brs_pm_numleaves * pfkz_total;
    } else {
      numacqs = brs_nphases * brs_numleaves_acq * (int)((float)opslquant*brs_fracz_fact);
    }
    acqcount = -1;
    leafoffset = 0;
    jumpno = 0;
    acqindex = 0;

    trigstate = gettrigoccur();
    trigstate = FALSE;

    if (opcgate)
    {
        while (trigstate == FALSE)
        {
            spoil();
            startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);
            trigstate = gettrigoccur();
        }
    }

    trigstate = FALSE;

    ResetGoldenRatio();
    if (brs_fwflag) {
      brs_fwdel = -(brs_numleaves_acq-1)*brs_fw_te_step;
    }
    
    while ((-1 != brs_getviews(&view, &tphase, &slice, &acqcount, 
                               trigstate, numacqs, &Te, &Tr)))
    {
	    /*******************  BOXU 2009.09.25   *******/
	    if( pfkz_flag && specir_flag ) {
	        if( (acqcount % pfkz_views_per_segment) == 0 ) {
		        /*SpecIRChemPrep();*/
            /* CRT ************************************* Pascal 02/21/11 */
            setrotate(rsprot[0], slabindex);  
		        if (brs_ssfp_flag) {
              PlayHTR(1.0);
              PlayHTR(0.5);
              KillerRsp();
            }
            ChemPrep();
            if (brs_ssfp_flag) {
              PlayHTR(0.5);
            
            }
	        }
	    }
        /***********************************************/
      /*if (tm_prepslice_flag) 
        tm_prepslice();*/
      if (brs_flex) flex_necho = opnecho;

      for(dabecho=0; dabecho<flex_necho; dabecho++) {
        if (0==Tr) 
          boffset(off_seqcore);
        else 
          boffset(off_seqcore2);
        
        if (!brs_realtime)    /* BMK 2006.07.26 */
        {
          if (0==Tr) {
            dabview = (view + 1) + brs_numleaves_acq*tphase;
          } else {
            dabview = brs_numleaves_acq * brs_nphases + view + 1;
          }
        } else {
            dabview = view + 1;
        }
        /*printf("view: %d \n", view);*/
        dabop = DABSTORE;
        dabslice = slice;
        
        if (brsfc_flag && opetl >1 && useFirstEchoComp)
        {
          setiampt(zfctab_echo1[dabslice],&gzbrsfc1echo1,0);
          setiampt(-zfctab_echo1[dabslice],&gzbrsfc1echo2,0);
        }

        if (opetl>=2)
        {
          for(count_echo=1;count_echo<opetl;count_echo++)
          {
            setiamp(ia_gxspiral, &gxspiral, count_echo);
            setiamp(ia_gyspiral, &gyspiral, count_echo);
            if (brsfc_flag)
            {
              setiampt(zfctab[dabslice],&gzbrsfc1,count_echo-1);
              setiampt(-zfctab[dabslice],&gzbrsfc2,count_echo-1);
            }
          }
        }

        
        if (brs_2dflag)
        {
          set_gz_encode(-1, Tr);
        }
        else
        {
          set_gz_encode(dabslice, Tr);
        }
#ifdef OLD
        if (view%2) {
            setperiod(brs_mapdel+4us, &mapx, 0);
            setperiod(brs_mapdel+4us, &mapy, 0);
            /*setperiod(brs_mapdel+4us, &mapz, 0);*/
            setperiod(brs_mapdel+4us, &maps1, 0);
            setperiod(4us, &maps2, 0);
        } else {
            setperiod(4us, &mapx, 0);
            setperiod(4us, &mapy, 0);
            /*setperiod(4us, &mapz, 0);*/
            setperiod(4us, &maps1, 0);
            setperiod(brs_mapdel+4us, &maps2, 0);
        }
#endif
        if (brs_fwflag) {
          int fwdel_act = (brs_fwdel > 0)? brs_fwdel : 0;
          setperiod(rsp_echo_wait+fwdel_act+4us, &mapx, 0);
          setperiod(rsp_echo_wait+fwdel_act+4us, &mapy, 0);
          setperiod(fwdel_act+4us, &mapz, 0);
          setperiod(rsp_echo_wait+fwdel_act+4us, &maps1, 0);
          setperiod(4us, &maps2, 0);
        } if (brs_flex) {
            ShiftTE(brs_mapdel*dabecho);
        } else {
          if (Te) {
            ShiftTE(brs_mapdel);
          } else {
            ShiftTE(0);
          }
        } 

        yres_phase = 0;

        /* grab the slab phase offset */
        if (brs_2dflag) {
          slab_phase = 0;
        } else {
          slab_phase = slab_off[slabindex].zsign * 
            ((dabslice * slab_off[slabindex].zoffs +
              3L*FS_PI)%FS_2PI-FS_PI);
        }
        spoil();

        acq_echo1 = DABON;
        if (opetl>=2)
          acq_echo2 = DABON;  /* BOXU 2011.12.14 */

        rotate_spiral(view, slabindex, 0.0);

#ifndef PSD_HW
        fprintf(views_fp, "slice %04d\tview %04d\tdabview %04d\tgr %.8f\n", 
               slice, view, dabview, golden_ratio_angle);
        fflush(views_fp);
#endif

#if ESEMAJOR >= 14    /* BMK 2007.06.27 */
        fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);
#else
        fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview,
                          acq_echo1,PSD_LOAD_DAB_ALL);
#endif
        if (opetl>=2)
        {
            fgre_loaddab_echo2(dabslice, (dabecho+1), (opetl-1), nshots, dabop, dabview, acq_echo2);
        }   /* BOXU 2011.12.14 */

        startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);

        trigstate = gettrigoccur();
      }
    }
    
#ifndef PSD_HW 
    fclose(views_fp);
#endif
    boffset(off_seqdelay3);
    setperiod(3000ms, &seqdelay3, 0);
    startseq((SHORT)0, (SHORT)MAY_PAUSE);


    if (brs_scantype == 3) {   /* BMK 2006.07.27 */  
      FILE *viewfile;
      SPIRAL_VIEW *acquired_viewtab;

      acquired_viewtab = (SPIRAL_VIEW *)acquired_viewtab_raw;

#ifdef PSD_HW
        viewfile = fopen("/usr/g/mrraw/cine_out.txt", "w");
#else
        viewfile = fopen("cine_out.txt", "w");
#endif

        for (i = 0; i < acqindex; i++) {
            if (acquired_viewtab[i].slice == -1)
                fprintf(viewfile, "triggered\n");
            else if (acquired_viewtab[i].slice == -2)
                fprintf(viewfile, "fatsat\n");
            else if (acquired_viewtab[i].slice == -3)
                fprintf(viewfile, "disdaq\n");
            else 
                fprintf(viewfile, "%d %d %d\n", acquired_viewtab[i].slice, acquired_viewtab[i].phase, acquired_viewtab[i].leaf); 
        } 
        fclose(viewfile);
    } 


    boffset(off_seqpass);

    /* Set DAB pass packet to end of scan */
    setwamp(SSPD + DABPASS + DABSCAN, &pass_pulse, 2);
    printdbg("  End of Scan and Pass", debugstate);
    pause = MAY_PAUSE;

    startseq(0,(SHORT)pause);

    boffset(off_seqcore);



    return SUCCESS;
}

int brs_getviews(int *view, int *tphase, int *slice, int *acqcount, 
                 int trigstate, int nacqs, int *te, int *tr)
{
    int nextview;
    SPIRAL_VIEW *acquired_viewtab;
    int fatsatnext;
    int prev_prepfs;

    acquired_viewtab = (SPIRAL_VIEW *)acquired_viewtab_raw;
    fatsatnext = 0;
    prev_prepfs = 0;

    *te = 0;
    *tr = 0;


    /**trigstate = gettrigoccur();*/

    if (!opcgate)
    {
        int index;
        (*acqcount)++;
        if (*acqcount >= nacqs)   /* BMK 2006.07.10, changed to >= from > */
            return -1;
        if (PM_ADDECHO == brs_pm_type) {
          int start_pm_leaf = nacqs - brs_pm_numleaves*pfkz_total;
          if (*acqcount == start_pm_leaf ) 
            ResetGoldenRatio(); 
          if (*acqcount >= start_pm_leaf ) { 
            index = *acqcount - start_pm_leaf;
            *tr = 1;
          } else {
            index = *acqcount;
            *tr = 0;
          }
        } else {
          index = *acqcount;
        }
        *view = brs_viewtab[index].leaf;
        *tphase = brs_viewtab[index].phase;
        *slice = brs_viewtab[index].slice;
        if (PM_SELFGEN == brs_pm_type) *te = (*view)%2;
        
    } else {
        if (((*slice) == 0) && (brs_s5fp) && ((*view)%brs_leafgroup == brs_leafgroup-1) && ((brs_vieword == 11) || (brs_vieword == 12)) )
            prev_prepfs = 1;
        if (trigstate)
        {
            acquired_viewtab[acqindex].slice = -1;
            acquired_viewtab[acqindex].phase = -1;
            acquired_viewtab[acqindex].leaf = -1;            
            acqindex++;

            jumpno++;
            nextview = brs_jumptab[jumpno];
            if (BRS_CINE == brs_vieword)
            {
                leafoffset = (2*brs_numleaves_acq - brs_viewtab[nextview].leaf + (brs_viewtab[*acqcount].leaf + leafoffset)%brs_numleaves_acq +1)%brs_numleaves_acq;
            } else {
                leafoffset = 0;
            }
        } else {
            nextview = *(acqcount)+1;
        }

        if ((*acqcount > nacqs) || (nextview < 0)) 
            return -1;

        *acqcount = nextview;
        *view = (brs_viewtab[*acqcount].leaf + leafoffset)%brs_numleaves_acq;
        *tphase = brs_viewtab[*acqcount].phase;
        *slice = brs_viewtab[*acqcount].slice;

        if (brs_s5fp && (brs_viewtab[*acqcount+1].slice == brs_fs_slice) && (((brs_viewtab[*acqcount+1].leaf + leafoffset)%brs_numleaves_acq)%brs_leafgroup == 0))
        {
            fatsatnext = 1;
        }

        if (((*slice) == brs_fs_slice) && (ssfat) && ((*view)%brs_leafgroup == 0))
        {
            setrotate(rsprot[0], slabindex);  /* BMK 2006.04.04 */
            SSfatRsp(0);
            acquired_viewtab[acqindex].slice = -2;
            acquired_viewtab[acqindex].phase = -2;
            acquired_viewtab[acqindex].leaf = -2;            
            acqindex++;
        }

        if (((*slice) == brs_fs_slice) && (brs_s5fp) && ((*view)%brs_leafgroup == 0))
        {
            if ((trigstate) && (*acqcount != 0) && ((brs_vieword == 12) || (brs_vieword == 11)) && (!prev_prepfs))
            {
                acq_echo1 = DABON;
                dabslice = 0;   /* acquire outermost */
                if (!brs_realtime)   /* BMK 2006.07.26 */
                    dabview = (brs_viewtab[*acqcount-1].phase*brs_numleaves_acq) + *view;   /* acquire last leaf from the previous frame */
                else
                    dabview = *view;
                acquired_viewtab[acqindex].slice = 0;
                acquired_viewtab[acqindex].phase = brs_viewtab[*acqcount-1].phase;
                acquired_viewtab[acqindex].leaf = *view-1;            
                acqindex++;

                rotate_spiral(*view-1, slabindex, 0.0);
#if ESEMAJOR >= 14    /* BMK 2007.06.27 */
                fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);
#else
                fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview,
                               acq_echo1,PSD_LOAD_DAB_ALL);
#endif
                setiamp((int)((3.0*opflip + 90.0)/(4.0*flip_rf1)*ia_rf1), &rf1, 0);
                spoil();
                startseq((SHORT)slabindex,(SHORT)MAY_PAUSE);
                syncoff(&seqcore);
            }
            else if ((*acqcount == 0) && (brs_s5fp) && ((brs_vieword == 11) || (brs_vieword == 12)))
            {
	        acq_echo1 = DABOFF;
#if ESEMAJOR >= 14   /* BMK 2007.06.27 */
                fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);
#else
                fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview,
                               acq_echo1,PSD_LOAD_DAB_ALL);
#endif
                setiamp((int)((3.0*opflip + 90.0)/(4.0*flip_rf1)*ia_rf1), &rf1, 0);
                spoil();
                acquired_viewtab[acqindex].slice = -3;
                acquired_viewtab[acqindex].phase = -3;
                acquired_viewtab[acqindex].leaf = -3;            
                acqindex++;
                startseq((SHORT)slabindex,(SHORT)MAY_PAUSE);
                syncoff(&seqcore);
                
            }
            
            setrotate(rsprot[0], slabindex);
            S5FPRsp();
            acquired_viewtab[acqindex].slice = -2;
            acquired_viewtab[acqindex].phase = -2;
            acquired_viewtab[acqindex].leaf = -2;            
            acqindex++;

            setiamp((int)(opflip/flip_rf1*ia_rf1), &rf1, 0);
        }

        if (fatsatnext)
        {
            setiamp((int)((3.0*opflip + 90.0)/(4.0*flip_rf1)*ia_rf1), &rf1, 0);
        }

        acquired_viewtab[acqindex].slice = *slice;
        acquired_viewtab[acqindex].phase = *tphase;
        acquired_viewtab[acqindex].leaf = *view;
        acqindex++;

    }

    return 0;
}

STATUS spiral_gate_scancore()
{
    int ddcount;
    int tphase;
    int numacqs;
    int i;
    int trigstate;
    int acqslquant;
    int ddahbacqs;
    int hbnum;


    slab_phase = 0;
    ddcount = 0;

    boffset(off_seqcore);


    acqslquant = (int)(((float)opslquant) * brs_fracz_fact);
    numacqs = brs_nphases * brs_numleaves_acq * (int)((float)opslquant*brs_fracz_fact);
    acqindex = 0;

    trigstate = gettrigoccur();
    trigstate = FALSE;

    hbnum = ophrep - 1;   /* BMK 2006.07.05 */

    tphase = 0;

    /* BMK 2006.07.05 */
    /* do disdacq heartbeats */
    ddahbacqs = brs_leafgroup * (int)((float)opslquant*brs_fracz_fact) * brs_ddahbs;
    for (acqindex = 0; acqindex < ddahbacqs; acqindex++)
    {
        if ((acqindex % (acqslquant * brs_leafgroup)) == 0){
            boffset(off_seqdelay3);
            setperiod(optr, &seqdelay3, 0);
            for (hbnum = 0; hbnum < ophrep; hbnum++)
            {
                while (trigstate == FALSE)
                {
                    startseq((SHORT)0, (SHORT)MAY_PAUSE);
                    trigstate = gettrigoccur();
                }
                trigstate = FALSE;
                if (0 == ddcount)
                    hbnum = ophrep;  /* shortcut for first heartbeat */
            }

            ddcount++;

            /* delay before starting disdaqs */
            if (!irprep_flag) 
            {
                boffset(off_seqdelay3);
                setperiod(optdel1 - optr*(brs_gateddas+brs_viewstocenter) - brs_fsprep_flag * time_fsprep, &seqdelay3, 0);  /* BMK 2006.09.08 */
                startseq((SHORT)0, (SHORT)MAY_PAUSE);
            }

            if (irprep_flag)
                IRPrep();

	    /* BMK 2006.09.08 */
	    /*if (brs_fsprep_flag)
		  FSprepRsp();*/
            
            boffset(off_seqcore);

            /* disdaqs before we start acquisition */
            acq_echo1 = DABOFF;
#if ESEMAJOR >= 14   /* BMK 2007.06.27 */
            fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);
#else
            fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview,
                       acq_echo1,PSD_LOAD_DAB_ALL);
#endif
            for (i = 0; i < brs_gateddas; i++)
            {
                spoil();
                startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);
            }
            trigstate = FALSE;

	    /* BMK 2006.09.09 */
	    if (brs_fsprep_flag)
	    {
		  FSprepRsp();
		  boffset(off_seqcore);
	    }
            

        }

        
        dabview = 0;
        dabop = DABSTORE;
        dabslice = 0;
        dabecho = 0;

        set_gz_encode(dabslice, 0);

        ShiftTE(0);

        yres_phase = 0;

        /* grab the slab phase offset */
        slab_phase = slab_off[slabindex].zsign * 
                    ((dabslice * slab_off[slabindex].zoffs +
                     3L*FS_PI)%FS_2PI-FS_PI);

        spoil();

        acq_echo1 = DABOFF;

#if ESEMAJOR >= 14   /* BMK 2007.06.27 */
        fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);
#else
        fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview,
                          acq_echo1,PSD_LOAD_DAB_ALL);
#endif

        startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);

        /*trigstate = gettrigoccur();
        if (TRUE == trigstate); 
        {
            if (hbnum < (ophrep - 1))
            {
                trigstate = FALSE;
                hbnum++;
            } 
        }*/  /* BMK 2006.07.08 */
    }
    /* end disdacq heartbeats */


    for (acqindex = 0; acqindex < numacqs; acqindex++)
    {
        if ((acqindex % (acqslquant * brs_leafgroup)) == 0){
            boffset(off_seqdelay3);
            setperiod(optr, &seqdelay3, 0);
            for (hbnum = 0; hbnum < ophrep; hbnum++)
            {
                while (trigstate == FALSE)
                {
                    startseq((SHORT)0, (SHORT)MAY_PAUSE);
                    trigstate = gettrigoccur();
                }
                trigstate = FALSE;
                if ((0 == acqindex) && (0 == ddcount))
                    hbnum = ophrep;   /* shortcut for first heartbeat */
            }

            /* delay before starting disdaqs */
            if (!irprep_flag) 
            {
                boffset(off_seqdelay3);
                setperiod(optdel1 - optr*(brs_gateddas+brs_viewstocenter) - brs_fsprep_flag * time_fsprep, &seqdelay3, 0);   /* BMK 2006.09.08 */
                startseq((SHORT)0, (SHORT)MAY_PAUSE);
            }

            if (irprep_flag)
                IRPrep();

	    /* BMK 2006.09.08 */
	    /*if (brs_fsprep_flag)
		  FSprepRsp();*/

            
            boffset(off_seqcore);

            /* disdaqs before we start acquisition */
            acq_echo1 = DABOFF;
#if ESEMAJOR >= 14    /* BMK 2007.06.27 */
            fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);
#else
            fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview,
                       acq_echo1,PSD_LOAD_DAB_ALL);
#endif
            for (i = 0; i < brs_gateddas; i++)
            {
                spoil();
                startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);
            }
            trigstate = FALSE;
            
	    /* BMK 2006.09.09 */
	    if (brs_fsprep_flag)
	    {
		  FSprepRsp();
		  boffset(off_seqcore);
	    }

        }

        view = brs_viewtab[acqindex].leaf;
        slice = brs_viewtab[acqindex].slice;
        
        dabview = (view + 1) + brs_numleaves_acq*tphase;
        dabop = DABSTORE;
        dabslice = slice;
        dabecho = 0;

        set_gz_encode(dabslice, 0);

        if (view%2) {
            ShiftTE(brs_mapdel);
        } else {
            ShiftTE(0);
        }

        yres_phase = 0;

        /* grab the slab phase offset */
        slab_phase = slab_off[slabindex].zsign * 
                    ((dabslice * slab_off[slabindex].zoffs +
                     3L*FS_PI)%FS_2PI-FS_PI);

        spoil();

        acq_echo1 = DABON;

        rotate_spiral(view, slabindex, 0.0);

#if ESEMAJOR >= 14
        fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);
#else
        fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview,
                          acq_echo1,PSD_LOAD_DAB_ALL);
#endif

        startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);

        /*trigstate = gettrigoccur();
        if (TRUE == trigstate);   
        {
            if (hbnum < (ophrep - 1))
            {
                trigstate = FALSE;
                hbnum++;
            } 
        } */  /* BMK 2006.07.08 */
    }
    
    boffset(off_seqdelay3);
    setperiod(3000ms, &seqdelay3, 0);
    startseq((SHORT)0, (SHORT)MAY_PAUSE);

    boffset(off_seqpass);

    /* Set DAB pass packet to end of scan */
    setwamp(SSPD + DABPASS + DABSCAN, &pass_pulse, 2);
    printdbg("  End of Scan and Pass", debugstate);
    pause = MAY_PAUSE;

    startseq(0,(SHORT)pause);

    boffset(off_seqcore);

    return SUCCESS;
}

STATUS spiral_gate_ps2core(void)
{
    short rfchop;

    int acqslquant;
    int i;
    int trigstate;

    acqslquant = (int)(((float)opslquant) * brs_fracz_fact);

    rfchop = 1;

    /* Initialize yres_phase and slab_phase to zero */
    yres_phase = 0;
    slab_phase = 0;

    /* Chop the receiver in APS2/MPS2 */
    chop_phase = -1;

    printdbg("Starting ps2core",debugstate);

    set_gz_encode(-1, 0);

    ShiftTE(0);

    /* 3d oblique - changed sliceindex to slabindex - latha@mr */
    /* Need to set this to the prescan slab */
    slabindex = rspesl;
    sp_sat_index = slabindex;

    setfrequency(rf1_freq[slabindex],&rf1,scanrf1_inst);
    /*setfrequency(receive_freq1[slabindex], &echo1, 0);*/
    brs_set_echo1frequency(receive_freq1[slabindex], 0);
    /* end 3d oblique - latha@mr */

    slice  = 0;               /* slices indexed from 0 instead of 1 */
    spgr_count = 1;           /*initialize spgr counter */ 

#if ESEMAJOR >= 14
    fgre_loaddab_echo1(slice, dabecho, dabop, dabview, DABOFF);
#else
    fgre_loaddab_echo1(slice, dabecho, dabop, dabview,
                       DABOFF, PSD_LOAD_DAB_ALL);
#endif

    rotate_spiral(0,0,0.0);

    trigstate = gettrigoccur();
    trigstate = FALSE;



    /* start view loop */
    for (view = 1; view <= rspvus; view++)
    {
        /* start excitation loop */	
        for (excitation = 1; excitation <= rspnex; excitation++)
        {
            if((excitation == rspnex) || (rspent == L_APS2)) {
                attenlockoff(&attenuator_key);
            } else {
                attenlockon(&attenuator_key);
            }
            
            if (((((view-1)) % (acqslquant * brs_leafgroup)) == 0) && (excitation == 1)){
                boffset(off_seqdelay3);
                setperiod(optr, &seqdelay3, 0);
                while (trigstate == FALSE)
                {
                    startseq((SHORT)0, (SHORT)MAY_PAUSE);
                    trigstate = gettrigoccur();
                    trigstate = gettrigoccur();
                }

                /* delay before starting disdaqs */
                if (!irprep_flag) 
                {
                    boffset(off_seqdelay3);
                    setperiod(optdel1 - optr*(brs_gateddas+brs_viewstocenter), &seqdelay3, 0);
                    startseq((SHORT)0, (SHORT)MAY_PAUSE);
                }

                if (irprep_flag)
                    IRPrep();
		    
                /* BMK 2006.09.08 */
		/* if (brs_fsprep_flag)
		    FSprepRsp(); */
            
                boffset(off_seqcore);

                /* disdaqs before we start acquisition */
                acq_echo1 = DABOFF;
#if ESEMAJOR >= 14    /* BMK 2007.06.27 */
                fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);
#else
                fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview,
                       acq_echo1,PSD_LOAD_DAB_ALL);
#endif
                for (i = 0; i < brs_gateddas; i++)
                {
                    spoil();
                    startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);
                }
                trigstate = FALSE;

	        /* BMK 2006.09.09 */
	        if (brs_fsprep_flag)
	        {
		    FSprepRsp();
		    boffset(off_seqcore);
	        }
            }   

            boffset(off_seqcore);
        
            acq_echo1 = DABON;

#if ESEMAJOR >= 14    /* BMK 2007.06.27 */
             fgre_loaddab_echo1(slice, dabecho, dabop, dabview, acq_echo1);
#else
             fgre_loaddab_echo1(slice, dabecho, dabop, dabview,
                           acq_echo1,PSD_LOAD_DAB_ALL);
#endif

            spoil();

            startseq(slabindex, (SHORT)MAY_PAUSE);

            syncoff(&seqcore);

            /* Chopper logic */
            chop_phase = -chop_phase;
        } /* excitation loop */
    } /* view loop */
    printdbg("Returning from spiral_ps2core",debugstate);
    return SUCCESS;
}


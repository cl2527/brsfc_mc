/*
use CSM rf waveform to generate Fat Sat preparation
rfpulse structure is bypassed here
*/

@cv SSfatCV

int ssfat_rotate = 0 with {0,1,0,VIS,"rotate fatsat spoilers between adjacent fatsats",};  /* BMK 2005.08.25 */
int ssfat_rfspoil = 1 with {0,1,1,VIS,"do rf spoiling on fatsat",};  /* BMK 2005.08.25 */
int ssfat = 0 with {0,1,0, VIS, "Use fat suppression for ssinversion",}; 
int ssfat_freq = 50 with {,,50,VIS, "Number of TRs between each fat sup pulse",}; 
int ssfat_vo = 0 with {0,1,0,VIS, "Adjusted (centric) view ordering for fat suppression",};
int ssfat_nullb=0 with {0,,0,VIS, "Position of k space center for (centric) view ordering for fat suppression",};
int ssfat_ramp =0 with {0,,0,VIS, "Number of linear ramping up pulses after fat sat (0=disable)",};
int ssfat_kaiser = 0 with {0,1,0,VIS,"Do Kaiser ramp after fatsat",};


float Rf = 0.6 with {0.0,1.0,0.6, VIS, "maximal relative fat signal before occurrence of new fat sat (between 0 and 1)",};
float T1f = 250000.0 with {,,250000.0, VIS, "T1 of fat",};
float T2f = 60000.0 with {,,60000.0, VIS, "T2 of fat",};

int Posrfssfh = 276 with {276,,276, INVIS, "begin of rfss",}; 
int PosGzssfhcomb;
int Posrfssf;

int ia_rfssfh;
float a_rfssfh;
float flip_rfssfh;
int pw_rfssfh;
int off_rfssfh;
int bw_rfssfh;
float ssfharea;
float area_rfssfh;

int kaiser_ramplen = 6 with {1,,6,VIS,"length of kaiser ramp", };

/* int FSvar; */  /* BMK 2005.06.10 */

int time_ssfprep;

float area_gxkssf;
float area_gykssf;
float area_gyakssf;
float area_gzkssf;


int ia_rfssf;
float a_rfssf;
float flip_rfssf;
int pw_rfssf;
int off_rfssf;

float area_rfssf, area_rf11;

@host SSfatEval

STATUS SSfatEval(void)
{
  flip_rfssfh = flip_rf1;
  
  /*pw_rfssfh = 500us; */

  /* BMK 2005.06.10 */
  pw_rfssfh = pw_rf1;
  
  /*res_rfssfh = 250;
  area_rf11 = 0.4121;
  area_rfssfh = area_rf11;
  bw_rfssfh = 6000*500.0/pw_rfssfh;*/

  /* BMK 2005.06.10 */
  res_rfssfh = res_rf1;
  area_rf11 = rfpulse[RF1_SLOT].area;
  area_rfssfh = rfpulse[RF1_SLOT].area;
  bw_rfssfh = (int)rfpulse[RF1_SLOT].nom_bw*rfpulse[RF1_SLOT].nom_pw/pw_rf1;  
  
  off_rfssfh = 0;
  
  
  
  
  pw_rfssf = 16ms;

  area_gxkssf=3450;
  area_gykssf=3450;
  area_gzkssf=3450;

  amppwgrad(area_gxkssf, cfxfs/sqrt(3), 0.0, 0.0,phygrd.xrt,MIN_PLATEAU_TIME,
	&a_gxkssf, &pw_gxkssfa, &pw_gxkssf, &pw_gxkssfd);
  ia_gxkssf = (a_gxkssf / (cfxfs/sqrt(3))) * MAX_PG_IAMP;

  amppwgrad(area_gykssf, cfyfs/sqrt(3), 0.0, 0.0,phygrd.yrt,MIN_PLATEAU_TIME,
	&a_gykssf, &pw_gykssfa, &pw_gykssf, &pw_gykssfd);
  ia_gykssf = (a_gykssf/(cfyfs/sqrt(3))) * MAX_PG_IAMP;

  amppwgrad(area_gzkssf, cfzfs/sqrt(3), 0.0, 0.0,phygrd.zrt,MIN_PLATEAU_TIME,
	&a_gzkssf, &pw_gzkssfa, &pw_gzkssf, &pw_gzkssfd);
  ia_gzkssf = (a_gzkssf/(cfzfs/sqrt(3))) * MAX_PG_IAMP;

  /*time_ssfprep = 1ms + pw_rfssf + pw_gzkssfa + pw_gzkssf + pw_gzkssfd + time_ssi;*/

  flip_rfssf = 105;

  res_rfssf = RES_RFCSM;

  area_rf11 = rfpulse[RF1_SLOT].area;
  area_rfssf = SAR_CSM_AREA;

  ia_rfssf = (int)( (float)(ia_rf1)*(flip_rfssf/flip_rf1)
	*(area_rf11/area_rfssf)*((float)(pw_rf1)/(float)(pw_rfssf)) );

  /* BMK 2006.03.23 */
  if (cffield == B0_30000)
      off_rfssf = -440;
  else
      off_rfssf = -220;

  return SUCCESS;
}

@host calcSSfatPulseParams

ia_rfssfh = (int)( (float)(ia_rf1)*(flip_rfssfh/flip_rf1)
	    *(area_rf11/area_rfssfh)*((float)(pw_rf1)/(float)(pw_rfssfh)) );

  pw_gzrfssfh = pw_rfssfh;
    if (ampslice(&a_gzrfssfh, bw_rf1, opvthick, gscale_rf1, TYPDEF) == FAILURE) {
        epic_error(use_ermes,"ampslice for gzrfssfh failure",
                   EM_PSD_SUPPORT_FAILURE,1,STRING_ARG,"amplice (for gzrfssfh)");
        return FAILURE;
    }

    /* make the 3d rf excitation slab thinner than phase encoded volume */
    a_gzrfssfh = a_gzrfssfh * slab_fact * exist(opslquant) / 
        IMax(2, 1, exist(opslquant) - 2*rhslblank);

    if (optramp(&pw_gzrfssfha, a_gzrfssfh, loggrd.tz, zrt, TYPDEF) == FAILURE) { 
        return FAILURE;
    }

    if (optramp(&pw_gzrfssfhd, a_gzrfssfh, loggrd.tz_xyz, zrt, TYPDEF) == FAILURE) {
        return FAILURE;
    }


      ssfharea =- a_gzrfssfh * (0.5 * (pw_gzrfssfha + pw_gzrfssfhd) + pw_gzrfssfh )  ;
      amppwgrad(ssfharea, loggrd.tz_xyz, 0.0, 0.0, loggrd.zrt, 0,  &a_gzssfhcomb, &pw_gzssfhcomba, &pw_gzssfhcomb,
                                  &pw_gzssfhcombd);

@host SSfatScanTime
      
      calcSSfatFreq();
      if (ssfat==1){
	    avmintscan += floor(
		  (float)((rhnframes+rhhnover)*opslquant)/(float)ssfat_freq
			   )*(time_ssfprep+ssfat_ramp*act_tr);

      }


@host calcSSfatFreq

STATUS calcSSfatFreq(void)
{
      float alpha;	/* opflip in radians */
      float beta;	/* off resonance in radians per TR */
      float Sf;		/* signal of fat */
      float lamf;	/* exponential signal growth factor for fat */
     
      /* do nothing if ssinversion=0 */
      if (ssfat==0) return SUCCESS;
      
            
      alpha=DEG_TO_RAD*((float) opflip);
      beta = (float)off_rfssf/1000.0*act_tr*2*FPI;
      Sf=.5*sqrt(T2f/T1f);
      
      lamf=exp(-(float)act_tr/T1f) * SQ(cos(.5*alpha)) + exp(-(float)act_tr/T2f) * SQ(sin(.5*alpha));
      

      ssfat_freq     = ceil(log(1-Rf)/log(lamf));
}

@pg SSfatPG

STATUS SSfatPG(void)
{
    short *fs_wave_space;
    char rhoFile[256];
	int crusherlength;

    /*Posrfssfh = IMax(2,pos_start+pw_gzrfssfha+psd_rf_wait,276);*/
    Posrfssfh = pos_start+pw_gzrfssfha+psd_rf_wait;

#ifdef SSFAT_DEBUG
	printf("Starting SSfatPG\n");
	printf("For alpha pulse, Posrfssfh = %d\n", Posrfssfh);
#endif

    makealpha(Posrfssfh);
    
    /* alpha/2 pulse *********************************************************************/
    
    Posrfssfh =  RUP_GRD(Posrfssfh + IMax(2, act_tr/2, pw_gzrfssfh + pw_gzrfssfhd - psd_rf_wait));

#ifdef SSFAT_DEBUG
	printf("For first alpha/2 pulse, Posrfssfh = %d\n", Posrfssfh);
#endif

    makealpha(Posrfssfh);

    
     /*fat sat **************************************************************************/
    
    Posrfssf = RUP_GRD(Posrfssfh + pw_gzrfssfh + pw_gzrfssfhd + 1ms);
    
#ifdef SSFAT_DEBUG
	printf("For fatsat pulse, Posrfssfh = %d\n", Posrfssfh);
#endif

    SPACESAVER(RHO, rfssf, res_rfssf);

    /* addrfbits(&rfssf, off_rfssf, Posrfssf, pw_rfssf); */
    {
#if ESEMAJOR >= 22
        int rfupa_time = abs(rfupa);
#else
        int rfupa_time = abs(rfupacv);
#endif
        fastAddrfbits(&rfssf, off_rfssf,  Posrfssf, pw_rfssf, rfupa_time);  /* BMK 2005.08.30 */
    }
    createinstr(&rfssf, Posrfssf, pw_rfssf, ia_rfssf);
    strcpy(rhoFile, "rfcsm.rho");

    fs_wave_space = (short *)AllocNode(res_rfssf*sizeof(short));
    uextwave(fs_wave_space,res_rfssf,rhoFile);


    movewaveimm(fs_wave_space, &rfssf, (int)0, res_rfssf, TOHARDWARE);
    FreeNode(fs_wave_space);
 
#ifdef SSFAT_DEBUG
	printf("Position for start of fatsat x crusher:  %d\n", RUP_GRD(pend(&rfssf, "rfssf", 0) + pw_gxkssfa - psd_rf_wait));
	printf("Position for start of fatsat y crusher:  %d\n", RUP_GRD(pend(&rfssf, "rfssf", 0) + pw_gykssfa - psd_rf_wait));
	printf("Position for start of fatsat z crusher:  %d\n", RUP_GRD(pend(&rfssf, "rfssf", 0) + pw_gzkssfa - psd_rf_wait));
#endif

    TRAPEZOID( YGRAD, gykssf, RUP_GRD(pend(&rfssf, "rfssf", 0) + pw_gykssfa
 	    - psd_rf_wait), area_gykssf, TYPNDEF,loggrd ); 

    TRAPEZOID( XGRAD, gxkssf, RUP_GRD(pend(&rfssf, "rfssf", 0) + pw_gxkssfa
 	    - psd_rf_wait), area_gxkssf, TYPNDEF,loggrd );

    TRAPEZOID( ZGRAD, gzkssf, RUP_GRD(pend(&rfssf, "rfssf", 0) + pw_gzkssfa
 	    - psd_rf_wait), area_gzkssf, TYPNDEF,loggrd );

    /*alpha/2 pulse *********************************************************************/
    
    crusherlength = IMax(3, pw_gxkssfa+pw_gxkssf+pw_gxkssfd, pw_gykssfa+pw_gykssf+pw_gzkssfd, pw_gzkssfa+pw_gzkssf+pw_gzkssfd);
    if ((ssfat_ramp==0) && (ssfat_kaiser == 0)) {  /* BMK 2005.06.15 */
      Posrfssfh = RUP_GRD(pend(&rfssf, "rfssf", 0) + crusherlength + psd_rf_wait + pw_gzrfssfha);
      makealpha(Posrfssfh);
#ifdef SSFAT_DEBUG
      printf("Position for last alpha/2 pulse:  %d\n", Posrfssfh);
#endif
      time_ssfprep = RUP_GRD(Posrfssfh + act_tr/2 - time_ssi - pos_start - pw_gzrf1a - psd_rf_wait);
    } else {
      time_ssfprep = RUP_GRD(pend(&rfssf, "rfssf", 0) + crusherlength );
    }

#ifdef SSFAT_DEBUG
	printf("Length of ssfat sequence:  %d\n", time_ssfprep);
#endif
      
    
   
    SEQLENGTH(seqssfprep, time_ssfprep, seqssfprep);
    
    attenflagon(&seqssfprep, 0);

    return SUCCESS;
} 


STATUS makealpha(int pos)
{				/* Only one macro call allowed */ 
    short *fs_wave_spaceh, *temp_wave_spaceh;
    char rhoFileh[256];
    int temp_res;
    int rfssfhfrqrsp;
    WF_PULSE_ADDR prfssfhfrq;

    /* BMK 2005.06.10 */
    /*strcpy(rhoFileh,"tbw3_01_001_pm_250.rho"); */
    switch (rf1_pulse_type){
/*        case RF_TBW2_1_01 :  
            strcpy(rhoFileh, "tbw2_1_01.rho");
            break;*/
        case RF_3D_600US_01P_01S_10KHZ :
            strcpy(rhoFileh, "rf3d_600us_01p_01s_10khz.rho");
            break; 
        case RF_TB3_01_001_250:
        default:
            strcpy(rhoFileh, "tbw3_01_001_pm_250.rho");
            break;     
    }
 
    temp_wave_spaceh = (short *)AllocNode(res_rfssfh*sizeof(short));

#ifdef IPG
      uextwave(temp_wave_spaceh,res_rfssfh,rhoFileh);
#endif

    temp_res = res_rfssfh;
    if (rfpulseInfo[RF1_SLOT].change==PSD_ON)
    {
      fs_wave_spaceh = (short *)AllocNode(rfpulseInfo[RF1_SLOT].newres*sizeof(short));
      stretchpulse((int)res_rfssfh,(int)rfpulseInfo[RF1_SLOT].newres,temp_wave_spaceh,fs_wave_spaceh);
      res_rfssfh = rfpulseInfo[RF1_SLOT].newres;
      FreeNode(temp_wave_spaceh);
    }
    else
      fs_wave_spaceh = temp_wave_spaceh;

    SPACESAVER(RHO, rfssfh, res_rfssfh);
    /* BMK 2005.06.10 */
    {
#if ESEMAJOR >= 22
        int rfupa_time = abs(rfupa);
#else
        int rfupa_time = abs(rfupacv);
#endif
        fastAddrfbits(&rfssfh, off_rfssfh,  pos, pw_rfssfh, rfupa_time);
    }
    /*addrfbits(&rfssfh, off_rfssfh,  pos, pw_rfssfh);*/
    createinstr(&rfssfh,pos, pw_rfssfh, ia_rfssfh);


    movewaveimm(fs_wave_spaceh, &rfssfh, (int)0, res_rfssfh, TOHARDWARE);
    FreeNode(fs_wave_spaceh);
    getssppulse(&prfssfhfrq, &rfssfh, "frq", 0);
    getwave(&rfssfhfrqrsp, prfssfhfrq);
 
    if (rfpulseInfo[RF1_SLOT].change==PSD_ON)
      res_rfssfh = temp_res;

     TRAPEZOID(ZGRAD,
	    gzrfssfh,
	    RUP_GRD(pos - psd_rf_wait),
	    0,
	    TYPNDEF,
	    loggrd);

  TRAPEZOID(ZGRAD,
	    gzssfhcomb,
	    RUP_GRD(pos - psd_rf_wait + pw_gzrfssfh + pw_gzrfssfhd /*+ gz_end_time*/ + pw_gzssfhcomba),
	    0,
	    TYPNDEF,
	    loggrd);  /* BMK 2005.06.10 */



  return SUCCESS;
} /* end makealpha() */

@rsp SSfatRsp
STATUS SSfatRsp(int frame)
{
  int luview;
  float KaiserRamp[6]={0.057, 0.2328, 0.5000, 0.7672, 0.9425, 1.000};  /* BMK 2005.06.15 */
  
  if (ssfat == 0) return SUCCESS;

  if (frame%ssfat_freq==0){
      boffset(off_seqssfprep);

      setiphase(exphase, &rfssfh, 1);
      exphase = (exphase +  4L*FS_PI) % FS_2PI  - FS_PI;
      setiphase(exphase, &rfssfh, 0);
      if ((ssfat_ramp==0) && (ssfat_kaiser == 0))  /* BMK 2005.06.15 */
	    setiphase(exphase, &rfssfh, 2);
      else if (!ssfat_rfspoil)
	    exphase = (exphase +  4L*FS_PI) % FS_2PI  - FS_PI;

      if (ssfat_rfspoil)   /* BMK 2006.04.04 */
      {
           exphase += (spgr_count++) * seed;
           exphase =  (exphase + 3L*FS_PI)%FS_2PI - FS_PI;
           if (!ssfat_kaiser && !ssfat_ramp)
                setiphase(exphase, &rfssfh, 2);
      } 


      setfrequency(rf1_freq[slabindex],&rfssfh,0); 
      setfrequency(rf1_freq[slabindex],&rfssfh,1);
      if ((ssfat_ramp==0) && (ssfat_kaiser == 0)) setfrequency(rf1_freq[slabindex],&rfssfh,2);

      /*setiamp(ia_rfssfh, &rfssfh, 0);*/
      setiamp(ia_rfssfh/2, &rfssfh, 1);
      if ((ssfat_ramp==0) && (ssfat_kaiser == 0)) setiamp(ia_rfssfh/2, &rfssfh, 2);


  
      setfrequency((int)(off_rfssf/TARDIS_FREQ_RES), &rfssf, 0);
      /*rfon(&rfssf,0);
      setiamp(ia_rfssf, &rfssf, 0);*/

      if (ssfat_rotate) {  /* BMK 2005.08.25 */
         int xamp, yamp, zamp;
         xamp = 0;
         yamp = 0;
         zamp = 0;
         if (ssfat_num%3 == 0) 
            xamp = ia_gxkssf;
         else if (ssfat_num%3 == 1)
            yamp = ia_gykssf;
         else
            zamp = ia_gzkssf;
         setiampt(xamp, &gxkssf, 0);
         setiampt(yamp, &gykssf, 0);
         setiampt(zamp, &gzkssf, 0);
         ssfat_num++;
      }

      if (ssfat_rfspoil) {  /* BMK 2005.08.25 */
         /*ssfatexphase += (ssfat_num++) * seeddef;
         ssfatexphase = (ssfatexphase + 3L*FS_PI)%FS_2PI - FS_PI;
         setiphase(ssfatexphase, &rfssf, 0);
         setiampt(0, &gxkssf, 0);
         setiampt(0, &gykssf, 0);
         setiampt(ia_gzkssf, &gzkssf, 0);*/

         setiphase(exphase, &rfssf, 0);  /* BMK 2006.04.04 */
         setiampt(ia_gzkssf, &gzkssf, 0);
      }

      if ((!ssfat_rfspoil) && (!ssfat_rotate)) {
         setiampt(ia_gxkssf, &gxkssf, 0);
         setiampt(ia_gykssf, &gykssf, 0);
         setiampt(ia_gzkssf, &gzkssf, 0);
      } 

      startseq((short)slabindex,(SHORT)MAY_PAUSE);
      syncoff(&seqssfprep);
      boffset(off_seqcore);
      if (ssfat_ramp>0){
	    /* do linear ramping up*/
            
            /* BMK 2005.06.10, noslice and nophase stuff deleted */

	    acq_echo1 = DABOFF;
#if ESEMAJOR >= 14   /* BMK 2007.06.27 */
	    fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);
#else
	    fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview,
                               acq_echo1,PSD_LOAD_DAB_ALL);
#endif
	    
	    /*load3d(&d3d, 0, DABOFF);*/   /* BMK 2005.06.15 */
	    for (luview = - ssfat_ramp; luview < 0; luview++) {
	          spoil();
		  /*setiamp(((ssfat_ramp+1+luview)*ia_rf1)/10, &rf1, 0);*/  /* BMK 2005.06.15 */
		  setiamp(((ssfat_ramp+1+luview)*ia_rf1)/ssfat_ramp, &rf1, 0);

		  startseq((SHORT)slabindex,(SHORT)MAY_PAUSE);
		  syncoff(&seqcore);
	    };  /* End disdaqs */
      }
      if (ssfat_kaiser){  /* BMK 2005.06.15 */
	    /* do kaiser ramping up*/

	    acq_echo1 = DABOFF;
#if ESEMAJOR >= 14  /* BMK 2007.06.27 */
	    fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);
#else
	    fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview,
                               acq_echo1,PSD_LOAD_DAB_ALL);
#endif
	    
	    for (luview = 0; luview < kaiser_ramplen; luview++) {
	          spoil();
		  if (luview < 6)
		      setiamp((int)(KaiserRamp[luview]*ia_rf1), &rf1, 0);
                  else
		      setiamp((int)(KaiserRamp[5]*ia_rf1), &rf1, 0);

		  startseq((SHORT)slabindex,(SHORT)MAY_PAUSE);
		  syncoff(&seqcore);
	    };  /* End disdaqs */
	    setiamp(ia_rf1, &rf1, 0);
      }

  }
      return SUCCESS;
}



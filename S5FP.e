/* McVeigh style fat saturation using fact that fat should
   be 180 deg out of phase from water for most ssfp sequences */

@cv S5FPcv

int ia_rfs5fph;
float a_rfs5fph;
float flip_rfs5fph;
float area_gzks5fp;
float s5fpharea;
int off_rfs5fph;
int pw_rfs5fph;

int Posrfs5fph;

int time_s5fpprep;

@host S5FPEval

STATUS S5FPEval(void) {
    flip_rfs5fph = flip_rf1;
    area_gzks5fp = 1000;

    pw_rfs5fph = pw_rf1;

    res_rfs5fph = res_rf1;

    amppwgrad(area_gzks5fp, loggrd.tz, 0.0, 0.0, loggrd.xrt, MIN_PLATEAU_TIME,
            &a_gzks5fp, &pw_gzks5fpa, &pw_gzks5fp, &pw_gzks5fpd);
    ia_gzks5fp = (a_gzks5fp / loggrd.tz) * MAX_PG_IAMP;

    off_rfs5fph = 0;
    
    return SUCCESS;
}



@host calcS5FPPulseParams

ia_rfs5fph = ia_rf1;

  pw_gzrfs5fph = pw_rfs5fph;
    if (ampslice(&a_gzrfs5fph, bw_rf1, opvthick, gscale_rf1, TYPDEF) == FAILURE) {
        epic_error(use_ermes,"ampslice for gzrfs5fph failure",
                   EM_PSD_SUPPORT_FAILURE,1,STRING_ARG,"amplice (for gzrfs5fph)");
        return FAILURE;
    }

    /* make the 3d rf excitation slab thinner than phase encoded volume */
    a_gzrfs5fph = a_gzrfs5fph * slab_fact * exist(opslquant) / 
        IMax(2, 1, exist(opslquant) - 2*rhslblank);

    if (optramp(&pw_gzrfs5fpha, a_gzrfs5fph, loggrd.tz, zrt, TYPDEF) == FAILURE) { 
        return FAILURE;
    }

    if (optramp(&pw_gzrfs5fphd, a_gzrfs5fph, loggrd.tz_xyz, zrt, TYPDEF) == FAILURE) {
        return FAILURE;
    }


      s5fpharea =- a_gzrfs5fph * (0.5 * (pw_gzrfs5fpha + pw_gzrfs5fphd) + pw_gzrfs5fph )  ;
      amppwgrad(s5fpharea, loggrd.tz_xyz, 0.0, 0.0, loggrd.zrt, 0,  &a_gzs5fphcomb, &pw_gzs5fphcomba, &pw_gzs5fphcomb,
                                  &pw_gzs5fphcombd);



@pg S5FPPG

STATUS S5FPPG(void)
{
    int crusherlength;
    int poscrusher;

    /* 0.25alpha + 0.75*90.0 pulse */
    Posrfs5fph = pos_start+pw_gzrfs5fpha+psd_rf_wait;
    makealphas5fp(Posrfs5fph);


    /* 45.0 pulse */
    Posrfs5fph =  RUP_GRD(Posrfs5fph + IMax(2, act_tr/2, pw_gzrfs5fph + pw_gzrfs5fphd - psd_rf_wait));
    makealphas5fp(Posrfs5fph);

    /* crusher */
    poscrusher = Posrfs5fph + pw_gzrfs5fph + pw_gzrfs5fphd + pw_gzs5fphcomba + pw_gzs5fphcomb + pw_gzs5fphcombd;
    TRAPEZOID( ZGRAD, gzks5fp, RUP_GRD(poscrusher + pw_gzks5fpa
 	    - psd_rf_wait), area_gzks5fp, TYPNDEF,loggrd );

    crusherlength = pw_gzks5fpa+pw_gzks5fp+pw_gzks5fpd;


    /* following alpha/2 pulse */
    Posrfs5fph = RUP_GRD(poscrusher + crusherlength + psd_rf_wait + pw_gzrfs5fpha);
    makealphas5fp(Posrfs5fph);

    time_s5fpprep = RUP_GRD(Posrfs5fph + act_tr/2 - time_ssi - pos_start - pw_gzrf1a - psd_rf_wait);

    SEQLENGTH(seqs5fpprep, time_s5fpprep, seqs5fpprep);
    
    attenflagon(&seqs5fpprep, 0);

    return SUCCESS;
}


STATUS makealphas5fp(int pos)
{				/* Only one macro call allowed */ 
    short *fs_wave_spaceh, *temp_wave_spaceh;
    char rhoFileh[256];
    int temp_res;
    int rfs5fphfrqrsp;
    WF_PULSE_ADDR prfs5fphfrq;

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
 
    temp_wave_spaceh = (short *)AllocNode(res_rfs5fph*sizeof(short));

#ifdef IPG
      uextwave(temp_wave_spaceh,res_rfs5fph,rhoFileh);
#endif

    temp_res = res_rfs5fph;
    if (rfpulseInfo[RF1_SLOT].change==PSD_ON)
    {
      fs_wave_spaceh = (short *)AllocNode(rfpulseInfo[RF1_SLOT].newres*sizeof(short));
      stretchpulse((int)res_rfs5fph,(int)rfpulseInfo[RF1_SLOT].newres,temp_wave_spaceh,fs_wave_spaceh);
      res_rfs5fph = rfpulseInfo[RF1_SLOT].newres;
      FreeNode(temp_wave_spaceh);
    }
    else
      fs_wave_spaceh = temp_wave_spaceh;

    SPACESAVER(RHO, rfs5fph, res_rfs5fph);
    {
#if ESEMAJOR >= 22
        int rfupa_time = abs(rfupa);
#else
        int rfupa_time = abs(rfupacv);
#endif
        fastAddrfbits(&rfs5fph, off_rfs5fph,  pos, pw_rfs5fph, rfupa_time);
    }
    createinstr(&rfs5fph,pos, pw_rfs5fph, ia_rfs5fph);


    movewaveimm(fs_wave_spaceh, &rfs5fph, (int)0, res_rfs5fph, TOHARDWARE);
    FreeNode(fs_wave_spaceh);
    getssppulse(&prfs5fphfrq, &rfs5fph, "frq", 0);
    getwave(&rfs5fphfrqrsp, prfs5fphfrq);
 
    if (rfpulseInfo[RF1_SLOT].change==PSD_ON)
      res_rfs5fph = temp_res;

     TRAPEZOID(ZGRAD,
	    gzrfs5fph,
	    RUP_GRD(pos - psd_rf_wait),
	    0,
	    TYPNDEF,
	    loggrd);

  TRAPEZOID(ZGRAD,
	    gzs5fphcomb,
	    RUP_GRD(pos - psd_rf_wait + pw_gzrfs5fph + pw_gzrfs5fphd + pw_gzs5fphcomba),
	    0,
	    TYPNDEF,
	    loggrd);  



  return SUCCESS;
} /* end makealphas5fp() */



@rsp S5FPRsp
STATUS S5FPRsp()
{
    if (brs_s5fp == 0) return SUCCESS;

    boffset(off_seqs5fpprep);

    setiphase(exphase, &rfs5fph, 1);
    exphase = (exphase +  4L*FS_PI) % FS_2PI  - FS_PI;
    setiphase(exphase, &rfs5fph, 0);

    /* spoil for fatsat */
    exphase += (spgr_count++) * seed;
    exphase = (exphase + 3L*FS_PI)%FS_2PI - FS_PI;
    setiphase(exphase, &rfs5fph, 2);

    setfrequency(rf1_freq[slabindex],&rfs5fph,0); 
    setfrequency(rf1_freq[slabindex],&rfs5fph,1);
    setfrequency(rf1_freq[slabindex],&rfs5fph,2);

    /*setiamp((int)(((opflip/90.0*ia_rfs5fph) + (3.0*ia_rfs5fph))/4.0), &rfs5fph, 0);
    setiamp(ia_rfs5fph/2, &rfs5fph, 1);
    setiamp((int)((opflip/90.0)*ia_rfs5fph/2), &rfs5fph, 2);*/

    setiamp((int)((opflip + 3.0*90.0)/(4.0*flip_rfs5fph)*ia_rfs5fph), &rfs5fph, 0);
    setiamp((int)(45.0*ia_rfs5fph/flip_rfs5fph), &rfs5fph, 1);
    setiamp((int)(opflip*ia_rfs5fph/(2.0*flip_rfs5fph)), &rfs5fph, 2);

    startseq((short)slabindex,(SHORT)MAY_PAUSE);
    syncoff(&seqs5fpprep);
    boffset(off_seqcore);

    return SUCCESS;
}


/*************************************************************/ 
/*                                                           */
/* Spiral Trajectory Mapping inline file                     */
/* Bo Xu Feb 2012                                            */
/*                                                           */
/*************************************************************/ 

/*************************************************************/ 
/* Control variables                                         */
/*************************************************************/ 
@host tmCV

int tm_flag = 0 with {0, 1, 0, VIS, "Use trajectory mapping or not (0=No 1=Yes)",};
int tm_time = 20ms with {0, 200ms, 20ms, VIS, "Trajectory mapping sequence time",};
float tm_slthick = 1.0 with {0, , 1.0, VIS, "slice thickness in trajectory mapping",};
float tm_flip = 90.0 with {0, , 90.0, VIS, "flip angle in trajectory mapping",};
int tm_pos_start = 1ms with {0, , 1ms, VIS, "trajectory mapping sequence start time",};
float tm_xloc = -70.0 with {-480,480 , -70.0, VIS, "yz slice location in x direction",};
float tm_yloc = -70.0 with {-480,480 , -70.0, VIS, "xz slice location in y direction",};
float tm_locstep = 20.0 with {-480,480 , 20.0, VIS, "step size when use mode 1",};
int scanrf1tm_inst = 0 with {0, , 0, VIS, "instance of rf1tm pulse",};
int tm_disdaqs = 10 with {, , 10, VIS, "trajectory mapping disdaqs",};
int tm_nex = 16 with {, , 16, VIS, "nex of trajectory mapping",};
int tm_spiral_delay = 1ms with {, , 1ms, VIS, "spiral starting point delay with respect to slice selection gradient",};
int tm_axis = 0 with {0, 1, 0, VIS, "0: x axis; 1 y axis;",};
int tm_ns = 8 with {0,20, 8, VIS, "number of slices",};
int tm_prepslice_flag = 0 with {0, 1, 0, VIS, "0: x axis; 1 y axis;",};
float tm_scale = 1.0 with {, ,1.0, VIS, "blip gradient scale used;",};

@host tmeval
/*  when do trajectory mapping, brsfc_flag should be set to 0 */
tm_slthick = 1.0;
pw_rf1tm = 4.8ms;
a_rf1tm = 1.0;
thk_rf1tm = tm_slthick;
res_rf1tm = 480;
cyc_rf1tm = 1;
flip_rf1tm = tm_flip;
pw_gxrf1tm = 4800;
ia_rf1tm = max_pg_iamp*(*rfpulse[RF1TM_SLOT].amp);

rfpulse[RF1TM_SLOT].abswidth = SAR_ABS_TRUNC1;
rfpulse[RF1TM_SLOT].area     = SAR_ATRUNC1;
rfpulse[RF1TM_SLOT].effwidth = SAR_PTRUNC1;
rfpulse[RF1TM_SLOT].dtycyc   = SAR_DTYCYC_TRUNC1;
rfpulse[RF1TM_SLOT].maxpw    = SAR_MAXPW_TRUNC1;
rfpulse[RF1TM_SLOT].max_b1   = MAX_B1_TRUNC1_24_90;
rfpulse[RF1TM_SLOT].max_int_b1_sq = MAX_INT_B1_SQ_SINC1_90;
rfpulse[RF1TM_SLOT].max_rms_b1 = MAX_RMS_B1_SINC1_90;
rfpulse[RF1TM_SLOT].nom_pw   = 2400.0;
rfpulse[RF1TM_SLOT].nom_bw   = 1250.0;
rfpulse[RF1TM_SLOT].nom_fa   = 90.0;


@host tmPredownload

pw_gyrf1tm = pw_gxrf1tm;
pw_gyrf1tma = pw_gxrf1tma;
pw_gyrf1tmd = pw_gxrf1tmd;
a_gyrf1tm = a_gxrf1tm;


@host tmHostVars
STATUS tmPG(void);
STATUS tm_scancore();
STATUS set_tm_xgrad();
STATUS set_tm_ygrad();
STATUS zero_tm_xgrad();
STATUS zero_tm_ygrad();


@pg tmPG

int *rf1tmx_freq;
int *rf1tmy_freq;


WF_PULSE *echo2toNtm;
STATUS tm_prepslice();

STATUS
tmPG(void)
{
  WF_PULSE *echo1tmrba;
  WF_PULSE_ADDR rec_unblank_tm;
  WF_PULSE_ADDR pecho1tmxtr;

  int echo2toNtmdab[MAX_ECHOES];
  int echo2toNtmrba[MAX_ECHOES];
  WF_PULSE_ADDR *p_echo2toNtmrba;
  WF_PULSE_ADDR *p_echo2toNtmxtr;


  int PosGx1tm;
  int PosGxbtm;
  int PosGybtm;
  int PosGzptm;
  int PosReadoutWindow_tm;
  int PosHyst;
  int echo1tmdab;
  int echo1tmxtrrsp, echo1tmrbarsp;
  int PosTemp;
  int PosDabPkt;
  int PosXtrPkt;
  int PosTnsOff;
  int DabSetUp;
  int daqpos;
  int echoindex;

  INT PosDabPkt2toN;
  INT PosXtrPkt2toN;
  INT PosReadoutWindow2toN_tm;

  daqpos = brs_daqdel;
  
  SLICESELX(rf1tm, tm_pos_start, pw_rf1tm,thk_rf1tm, flip_rf1tm, cyc_rf1tm,,loggrd);

  scanrf1tm_inst = rf1tm.ninsts-1;

  TRAPEZOID(YGRAD, gyrf1tm, tm_pos_start, 1, TYPNDEF, loggrd);

  PosGx1tm = RUP_GRD(tm_pos_start +  pw_gxrf1tm + pw_gxrf1tmd + pw_gx1tma);

  TRAPEZOID(XGRAD, gx1tm, PosGx1tm, (int)(-0.5*a_gxrf1tm*(pw_rf1tm+pw_gxrf1tmd)),, loggrd );
  TRAPEZOID(YGRAD, gy1tm, PosGx1tm, (int)(-0.5*a_gxrf1tm*(pw_rf1tm+pw_gxrf1tmd)),, loggrd );

  PosReadoutWindow_tm = RUP_GRD(PosGx1tm + pw_gx1tm + pw_gx1tmd) + tm_spiral_delay;

  GenerateSpiral(PosReadoutWindow_tm);
  if (hst_flag)
  {
    PosHyst = RUP_GRD(pend(&gxspoild, "gxspoild",opetl)+pw_gxhyst1a);
    HystGrad(PosHyst);
  }

  getssppulse(&rec_unblank_tm, &rf1tm, "ubr", 0);
  PosDabPkt = RUP_GRD(pendallssp(rec_unblank_tm, 0));

  PosTemp = PosReadoutWindow_tm;

  if ( (PosTemp - XTRSETLNG) < (PosDabPkt+DAB_length[bd_index]) )
  {
    PosTemp = RUP_GRD(PosDabPkt + DAB_length[bd_index] + XTRSETLNG);
  }
  PosXtrPkt = RUP_GRD(PosReadoutWindow_tm+daqpos+psd_grd_wait-XTR_length[bd_index]-XTRSETLNG);  
  if (PosXtrPkt < (PosTemp - XTRSETLNG + DIM_length) )
  {
    PosXtrPkt = RUP_GRD(PosTemp - XTRSETLNG + DIM_length);
  }
  DabSetUp = IMax(2,DABSETUP,(XTRSETLNG+XTR_length[bd_index]+DAB_length[bd_index]));
  if (opetl>=2)
  {
    PosDabPkt = RUP_GRD(PosReadoutWindow_tm+daqpos+psd_grd_wait-DabSetUp);
  }

  ACQUIREDATA(echo1tm, RUP_GRD(PosReadoutWindow_tm + daqpos + psd_grd_wait),
      PosDabPkt, PosXtrPkt, DABNORM);
  getssppulse(&echo1tmrba, &echo1tm, "rba",0);

  if(opetl>=2)
  {
    char pulse_name[20];
    echo2toNtm = (WF_PULSE *)AllocNode(opetl*sizeof(WF_PULSE));
    p_echo2toNtmrba = (WF_PULSE_ADDR *)AllocNode(opetl*sizeof(WF_PULSE_ADDR));
    p_echo2toNtmxtr = (WF_PULSE_ADDR *)AllocNode(opetl*sizeof(WF_PULSE_ADDR));

    for(echoindex=0; echoindex < (opetl-1); echoindex++) 
    {
      PosDabPkt2toN = RUP_GRD(PosDabPkt + esp + echoindex*esp);
      PosReadoutWindow2toN_tm = RUP_GRD(PosReadoutWindow_tm + esp + echoindex*esp);
      PosXtrPkt2toN = RUP_GRD(PosXtrPkt + esp + echoindex*esp);

      if (brs_blipflag)
      {
        PosGxbtm = PosReadoutWindow2toN_tm - (pw_gxb + pw_gxbd) - 0.2ms;
        PosGybtm = PosReadoutWindow2toN_tm - (pw_gyb + pw_gybd) - 0.2ms;
        BlipGrad(IMin(2,PosGxbtm, PosGybtm));
      }

      GenerateSpiral(PosReadoutWindow2toN_tm);
      if (hst_flag)
      {
        PosHyst = RUP_GRD(pend(&gxspoild, "gxspoild",echoindex+1+opetl)+pw_gxhyst1a);
        HystGrad(PosHyst);
      }

      sprintf(pulse_name,"echo2toNtm%d",echoindex);
      pulsename(&(echo2toNtm[echoindex]),pulse_name);

      acqq(&(echo2toNtm[echoindex]), (long) (PosReadoutWindow2toN_tm+daqpos+psd_grd_wait), (long) PosDabPkt2toN,(long)(PosXtrPkt2toN),filter_echo1,(TYPDAB_PACKETS)DABNORM);

      getssppulse(&(p_echo2toNtmrba[echoindex]), &(echo2toNtm[echoindex]), "rba", 0);
      getssppulse(&(p_echo2toNtmxtr[echoindex]), &(echo2toNtm[echoindex]), "xtr", 0);
    }
  }

  getwave(&echo1tmrbarsp,echo1tmrba);
  TNSON(e1entns_tm,pendallssp(echo1tmrba, 0));
  if (opetl>=2)
    PosTnsOff = RUP_GRD(pendallssp(p_echo2toNtmrba[opetl-2],0) + pw_gxspiral);
  else
    PosTnsOff = RUP_GRD(pendallssp(echo1tmrba, 0) +  pw_gxspiral);
  TNSOFF(e1distns_tm,PosTnsOff);

  attenflagon(&echo1tm,0);
  getwave(&echo1tmdab, &echo1tm);
  getssppulse(&pecho1tmxtr, &echo1tm, "xtr", 0);
  getwave(&echo1tmxtrrsp, pecho1tmxtr);


  if(opetl>=2) 
  {
    for(echoindex=0; echoindex <(opetl-1); echoindex++) 
    {
      getwave(&(echo2toNtmdab[echoindex]), &(echo2toNtm[echoindex]));
      getwave(&(echo2toNtmrba[echoindex]), p_echo2toNtmrba[echoindex]);
    }
  }
  if (opetl>=2)
    PosGzptm = RUP_GRD(PosReadoutWindow2toN_tm + pw_gxspiral + pw_gxspoila + pw_gzptma);
  else
    PosGzptm = RUP_GRD(PosReadoutWindow_tm + pw_gxspiral + pw_gxspoila + pw_gzptma);

  TRAPEZOID(ZGRAD, gzptm, PosGzptm, 4000,,loggrd);

  tm_time = RUP_GRD(tm_pos_start + 
      pw_gxrf1tm + pw_gxrf1tmd + 
      pw_gx1tma + pw_gx1tm + pw_gx1tmd + tm_spiral_delay +
      pw_gxspiral +
      esp*(opetl-1) +
      IMax(2,pw_gzptma + pw_gzptm +  pw_gzptmd, (pw_gxspoila + pw_gxspoil + pw_gxspoild) + hst_length*2*hst_flag ))
      + 0.5ms;

  SEQLENGTH(tmcore, tm_time, tmcore);

  return SUCCESS;
}

@rspvar tmRSPVAR
int spgr_count_tm;


@rsp tmRSP

TYPDAB_PACKETS acq_echo1tm;
TYPDAB_PACKETS acq_echo2toNtm;

STATUS sethystamp_tm(float cphi, float sphi, int axis)
{
  /* axis 0 x spiral measurement, axis 1 y spiral measurement */
  int count_echo;
  float a_hstx;
  float a_hsty;

  if(0==axis)
  {
    a_hstx = a_hst;
    a_hsty = 0.0;
  }
  else
  {
    a_hstx = 0.0;
    a_hsty = a_hst;
  }

  gx_hyst = ( a_hstx*cphi + a_hsty*sphi)*max_pg_iamp/loggrd.tx;
  gy_hyst = (-a_hstx*sphi + a_hsty*cphi)*max_pg_iamp/loggrd.ty;

  for(count_echo=0;count_echo<opetl;count_echo++)
    {
      setiampt( gx_hyst, &gxhyst1, count_echo+opetl);
      setiampt( gy_hyst, &gyhyst1, count_echo+opetl);
      setiampt(-gx_hyst, &gxhyst2, count_echo+opetl);
      setiampt(-gy_hyst, &gyhyst2, count_echo+opetl);
    }
  
  return SUCCESS;
}
void rotate_spiral_base(int slab, float angle, int axis)
{
  float cphi, sphi;
  int i;
  long rotmtx[1][9];

  
  cphi = cos(angle);
  sphi = sin(angle);
  /*
  if (fabs(angle-0.0) > 0.2)
  {
    cphi = 0.0;
    sphi = 1.0;
  }
  else
  {
    cphi = 1.0;
    sphi = 0.0;
  }*/

  if (hst_flag)
    sethystamp_tm(cphi,sphi,axis);

  for (i = 0; i < 9; i += 3) {
    rotmtx[0][i] = (int)(  cphi*brs_savrot[slab][i] 
                         + sphi*brs_savrot[slab][i+1]);
    rotmtx[0][i+1] = (int)( -sphi*brs_savrot[slab][i]
                           + cphi*brs_savrot[slab][i+1]);
    rotmtx[0][i+2] = brs_savrot[slab][i+2];
  }

  scalerotmats(rotmtx, &loggrd, &phygrd, 1, 0);
  setrotate(rotmtx[0], slab);
}

STATUS zero_tm_ygrad()
{
  int count_echo;
  setiampt(0, &gyrf1tm, 0);
  setiampt(0, &gy1tm, 0);
  for(count_echo=0;count_echo<opetl;count_echo++)
  {
    setiamp(0, &gyspiral, opetl+count_echo);
    setiampt(0, &gyspoil, opetl+count_echo);
  }
  if(brs_blipflag)
  {
    for(count_echo=0;count_echo<opetl-1;count_echo++) /* there are only opetl-1 blip gradient */
      setiampt(0, &gyb, count_echo+opetl-1);
  }
  return SUCCESS;
}

STATUS zero_tm_xgrad()
{
  int count_echo;
  setiampt(0, &gxrf1tm, 0);
  setiampt(0, &gx1tm, 0);
  for(count_echo=0;count_echo<opetl;count_echo++)
  {
    setiamp(0, &gxspiral, opetl+count_echo);
    setiampt(0, &gxspoil, opetl+count_echo);
  }
  if(brs_blipflag)
  {
    for(count_echo=0;count_echo<opetl-1;count_echo++) /* there are only opetl-1 blip gradient */
      setiampt(0, &gxb, count_echo+opetl-1);
  }
  return SUCCESS;
}
STATUS set_tm_xgrad()
{
  int count_echo;
  setiampt(ia_gxrf1tm, &gxrf1tm, 0);
  setiampt(ia_gx1tm, &gx1tm, 0);
  setiampt(ia_gzptm, &gzptm, 0);
  for(count_echo=0;count_echo<opetl;count_echo++)
  {
    setiamp(ia_gxspiral, &gxspiral, opetl+count_echo);
    setiampt(ia_gxspoil, &gxspoil, opetl+count_echo);
  }
  if (brs_blipflag)
  {
    for(count_echo=0;count_echo<opetl-1;count_echo++) /* there are only opetl-1 blip gradient */
      setiampt((int)((float)ia_gxb*tm_scale), &gxb, count_echo+opetl-1);
  }
  return SUCCESS;
}
STATUS set_tm_ygrad()
{
  int count_echo;
  setiampt(ia_gyrf1tm, &gyrf1tm, 0);
  setiampt(ia_gy1tm, &gy1tm, 0);
  for(count_echo=0;count_echo<opetl;count_echo++)
  {
    setiamp(ia_gyspiral, &gyspiral, opetl+count_echo);
    setiampt(ia_gyspoil, &gyspoil, opetl+count_echo);
  }
  if (brs_blipflag)
  {
    for(count_echo=0;count_echo<opetl-1;count_echo++) /* there are only opetl-1 blip gradient */
      setiampt((int)((float)ia_gyb*tm_scale), &gyb, count_echo+opetl-1);
  }
  return SUCCESS;
}


STATUS tm_scancore()
{
  int count_nex;
  int count_view;
  int count_echo;
  int i;
  int receive_freq_tm;
  int exphase_tm;
  int rcphase_tm;
  int acqmode; /* 1:x-0, 2:y-90, 3:y-0, 4:x-90 */
  int modepos[4]={1,4,3,2};
  float scaleblip[4];
  scaleblip[0] = brs_xx;
  scaleblip[1] = brs_yx;
  scaleblip[2] = brs_yy;
  scaleblip[3] = brs_xy;

  rf1tmx_freq = (int *)AllocNode(tm_ns*sizeof(int));
  rf1tmy_freq = (int *)AllocNode(tm_ns*sizeof(int));

  for(i=0;i<tm_ns;i++)
  {
    rf1tmx_freq[i] = (int)(GAM * a_gxrf1tm * (tm_xloc+i*tm_locstep) / (10 * TARDIS_FREQ_RES));
    rf1tmy_freq[i] = (int)(GAM * a_gyrf1tm * (tm_yloc+i*tm_locstep) / (10 * TARDIS_FREQ_RES));
  }

  spgr_count_tm = 1;

  dabop = DABSTORE;
  dabecho = 0;
  dabslice = 0;
  acq_echo1tm = DABOFF;
  acq_echo2toNtm = DABOFF;
  /*receive_freq_tm = TARDIS_FREQ_OFFSET/TARDIS_FREQ_RES;*/
  receive_freq_tm = (int)((float)cfreceiveroffsetfreq / TARDIS_FREQ_RES);
  
  setfrequency(receive_freq_tm,&echo1tm,0);
  
  if (opetl>=2)
  {
    for(count_echo=0;count_echo<(opetl-1);count_echo++)
      setfrequency(receive_freq_tm,&(echo2toNtm[count_echo]),0);
  }

  setiampt(ia_gzptm, &gzptm, 0);
  for(acqmode=1; acqmode<5; acqmode++)
  {
    boffset(off_tmcore);
    
    if(acqmode<3)
      tm_axis =0;
    else
      tm_axis =1;
    if (acqmode==1 || acqmode==4)
    {
      set_tm_xgrad();
      zero_tm_ygrad();
    }
    else if (acqmode==2 || acqmode==3)
    {
      zero_tm_xgrad();
      set_tm_ygrad();
    }
    tm_scale = scaleblip[acqmode-1];
    for (count_nex = -tm_disdaqs; count_nex < tm_nex*2; count_nex++)
    {
      if (count_nex>-1)
      {
        acq_echo1tm = DABON;
        if (opetl>=2)
          acq_echo2toNtm = DABON;
        dabslice = count_nex;
      }
      if (count_nex>tm_nex-1) /* Acquire the reference signal at the end*/
      {
        for(count_echo=0;count_echo<opetl;count_echo++)
        {
          setiamp(0, &gxspiral, opetl+count_echo);
          setiamp(0, &gyspiral, opetl+count_echo);
          setiampt(0, &gxspoil, opetl+count_echo);
          setiampt(0, &gyspoil, opetl+count_echo);
        }
        if (brs_blipflag)
        {
          for(count_echo=0;count_echo<opetl-1;count_echo++) /* there are only opetl-1 blip gradient */
          {
            setiampt(0, &gxb, count_echo+opetl-1);
            setiampt(0, &gyb, count_echo+opetl-1);
          }
        }
      }

      for (count_view = 0; count_view < tm_ns; count_view++)
      {
        if(acqmode==2)
          dabview = 1 + (modepos[acqmode-1]-1)*tm_ns + (tm_ns-count_view-1);
        else
          dabview = 1 + (modepos[acqmode-1]-1)*tm_ns + count_view;
        
        if(acqmode==1)
          setfrequency(rf1tmx_freq[count_view],&rf1tm,scanrf1tm_inst);
        else if (acqmode==2)
          setfrequency(rf1tmx_freq[tm_ns-count_view-1],&rf1tm,scanrf1tm_inst);
        else if (acqmode==3 || acqmode==4)
          setfrequency(rf1tmy_freq[count_view],&rf1tm,scanrf1tm_inst);
        
        {
          exphase_tm += (spgr_count_tm++) * seed;
          exphase_tm = (exphase_tm + 3L*FS_PI)%FS_2PI - FS_PI;
          rcphase_tm = (exphase_tm + 3L*FS_PI) % FS_2PI - FS_PI;
          if( chop_phase == PSD_ON ) {
            /* Add PI to receiver phase */
            rcphase_tm = (rcphase_tm + 4L*FS_PI)%FS_2PI - FS_PI;
          }
          setiphase(exphase_tm, &rf1tm, scanrf1tm_inst);
          setiphase(rcphase_tm, &echo1tm, 0);
        }
        
        if (opetl>=2)
        {
          for(count_echo=0;count_echo<(opetl-1);count_echo++)
            setiphase(rcphase_tm, &(echo2toNtm[count_echo]), 0);
        }

        if(acqmode==1 || acqmode==3)
          rotate_spiral_base(0, 0.25*M_PI, tm_axis);
        else if (acqmode==2 || acqmode==4)
          rotate_spiral_base(0, -0.25*M_PI, tm_axis);

        loaddab(&echo1tm, dabslice, dabecho, dabop, dabview, acq_echo1tm, PSD_LOAD_DAB_ALL);
        if(opetl>=2)
        {
          for(count_echo=0;count_echo<(opetl-1);count_echo++)
            loaddab(&(echo2toNtm[count_echo]), dabslice, count_echo+1, dabop, dabview, acq_echo2toNtm, PSD_LOAD_DAB_ALL);
        }
        startseq((SHORT)0, (SHORT)MAY_PAUSE);
        syncoff(&tmcore);
      }
    }
    boffset(off_seqdelay3);
    setperiod(5000ms, &seqdelay3, 0);
    startseq((SHORT)0, (SHORT)MAY_PAUSE);
    
  }
  
  boffset(off_seqdelay3);
  setperiod(1000ms, &seqdelay3, 0);
  startseq((SHORT)0, (SHORT)MAY_PAUSE);

  boffset(off_seqpass);
  setwamp(SSPD + DABPASS + DABSCAN, &pass_pulse, 2);
  startseq(0,(SHORT)MAY_PAUSE);

  return SUCCESS;
}


STATUS tm_prepslice()  /* This function is used to see the slice location*/
{
  int receive_freq_tm;
  int exphase_tm;
  int rcphase_tm;
  int i;
  

  rf1tmx_freq[0] = (int)(GAM * a_gxrf1tm * tm_xloc / (10 * TARDIS_FREQ_RES));
  rf1tmy_freq[0] = (int)(GAM * a_gyrf1tm * tm_yloc / (10 * TARDIS_FREQ_RES));
  /*receive_freq_tm = TARDIS_FREQ_OFFSET/TARDIS_FREQ_RES;*/
  receive_freq_tm = (int)((float)cfreceiveroffsetfreq / TARDIS_FREQ_RES);
  setfrequency(receive_freq_tm,&echo1tm,0);
 
  settrigger((short) TRIG_INTERN, (short) 0);
  boffset(off_tmcore);

  dabop = DABSTORE;
  dabecho = 0;
  dabslice = 0;
  dabview = 0;
  acq_echo1tm = DABOFF;

  for(i=0;i<2;i++)
  {
    if (i==0)
    {
      setfrequency(rf1tmx_freq[0],&rf1tm,scanrf1tm_inst); 
      set_tm_xgrad();
      zero_tm_ygrad();
    }
    else
    {
      setfrequency(rf1tmy_freq[0],&rf1tm,scanrf1tm_inst); 
      set_tm_ygrad();
      zero_tm_xgrad();
    }

    {
      exphase_tm = 0;
      exphase_tm = (exphase_tm + 3L*FS_PI)%FS_2PI - FS_PI;
      rcphase_tm = (exphase_tm + 3L*FS_PI) % FS_2PI - FS_PI;
      if( chop_phase == PSD_ON ) {
        /* Add PI to receiver phase */
        rcphase_tm = (rcphase_tm + 4L*FS_PI)%FS_2PI - FS_PI;
      }
      setiphase(exphase_tm, &rf1tm, scanrf1tm_inst);
      setiphase(rcphase_tm, &echo1tm, 0);
    }

    rotate_spiral_base(0, 0.0, i);
    loaddab(&echo1tm, dabslice, dabecho, dabop, dabview, acq_echo1tm, PSD_LOAD_DAB_ALL);
    startseq((SHORT)0, (SHORT)MAY_PAUSE);
    syncoff(&tmcore);
  }

  boffset(off_seqcore);
  return SUCCESS;
}

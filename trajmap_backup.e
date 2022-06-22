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

int tm_flag = 1 with {0, 1, 1, VIS, "Use trajectory mapping or not (0=No 1=Yes)",};
int tm_time = 20ms with {0, 30ms, 20ms, VIS, "Trajectory mapping sequence time",};
float tm_opslthick = 1.0 with {0, , 1.0, VIS, "slice thickness in trajectory mapping",};
float tm_opflip = 80.0 with {0, , 80, VIS, "flip angle in trajectory mapping",};
int tm_pos_start = 1ms with {0, , 1ms, VIS, "trajectory mapping sequence start time",};
float tm_xloc = 40.0 with {-480,480 , 40, VIS, "yz slice location in x direction",};
float tm_yloc = 40.0 with {-480,480 , 40, VIS, "xz slice location in y direction",};
int scanrf1tm_inst = 0 with {0, , 0, VIS, "instance of rf1tm pulse",};
int tm_disdaqs_ref = 0 with {, , 0, VIS, "trajectory mapping disdaqs for reference scan",};
int tm_disdaqs_main = 0 with {, , 0, VIS, "trajectory mapping disdaqs for main scan",};
int tm_nex = 15 with {, , 15, VIS, "nex of trajectory mapping",};
int nangle = 12 with {, , 12, VIS, "number of angles measured in trajectory mapping",};


@host tmeval

tm_opslthick = 1.0;
pw_rf1tm = 3.2ms;
a_rf1tm = 1.0;
thk_rf1tm = tm_opslthick;
res_rf1tm = 320;
cyc_rf1tm = 1;
flip_rf1tm = tm_opflip;
pw_gxrf1tm = 3200;


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


nangle = brs_numleaves;

@host tmPredownload


pw_gyrf1tm = pw_gxrf1tm;
pw_gyrf1tma = pw_gxrf1tma;
pw_gyrf1tmd = pw_gxrf1tmd;
a_gyrf1tm = a_gxrf1tm;


@host tmHostVars
STATUS tmPG(void);
STATUS tm_scancore();


@pg tmPG

STATUS
tmPG(void)
{
  WF_PULSE *echo1tmrba;
  WF_PULSE_ADDR rec_unblank_tm;
  WF_PULSE_ADDR pecho1tmxtr;

  int PosGx1tm;
  int PosGxptm;
  int PosReadoutWindow_tm;
  int echo1tmdab;
  int echo1tmxtrrsp, echo1tmrbarsp;
  int PosTemp;
  int PosDabPkt;
  int PosXtrPkt;
  int PosTnsOff;
  int daqpos; 

  daqpos = brs_daqdel;
  
  SLICESELX(rf1tm, tm_pos_start, pw_rf1tm,thk_rf1tm, flip_rf1tm, cyc_rf1tm,,loggrd);

  scanrf1tm_inst = rf1tm.ninsts-1;

  TRAPEZOID(YGRAD, gyrf1tm, tm_pos_start, 1, TYPNDEF, loggrd);

  PosGx1tm = RUP_GRD(tm_pos_start +  pw_gxrf1tm + pw_gxrf1tmd + pw_gx1tma);

  TRAPEZOID(XGRAD, gx1tm, PosGx1tm, (int)(-0.5*a_gxrf1tm*(pw_rf1tm+pw_gxrf1tmd)),, loggrd );
  TRAPEZOID(YGRAD, gy1tm, PosGx1tm, (int)(-0.5*a_gxrf1tm*(pw_rf1tm+pw_gxrf1tmd)),, loggrd );

  PosReadoutWindow_tm = RUP_GRD(PosGx1tm + pw_gx1tm + pw_gx1tmd);

  GenerateSpiral(PosReadoutWindow_tm);
  /*printf("spiral start = %d s \n", PosReadoutWindow_tm);*/

  getssppulse(&rec_unblank_tm, &rf1tm, "ubr", 0);
  PosDabPkt = RUP_GRD(pendallssp(rec_unblank_tm, 0));

  /*printf("PosDabPkt = %d s \n", PosDabPkt);*/
  PosTemp = PosReadoutWindow_tm;

  if ( (PosTemp - XTRSETLNG) < (PosDabPkt+DAB_length[bd_index]) )
  {
    PosTemp = RUP_GRD(PosDabPkt + DAB_length[bd_index] + XTRSETLNG);
  }

  PosXtrPkt = RUP_GRD(PosReadoutWindow_tm+daqpos+psd_grd_wait-XTR_length[bd_index]-XTRSETLNG);  
  /*printf("PlsXtrPkt = %d s \n", PosXtrPkt);*/
  if (PosXtrPkt < (PosTemp - XTRSETLNG + DIM_length) )
  {
    PosXtrPkt = RUP_GRD(PosTemp - XTRSETLNG + DIM_length);
  }
/*
  printf("PosXtrPkt = %d s \n", PosXtrPkt);
*/
  ACQUIREDATA(echo1tm, RUP_GRD(PosReadoutWindow_tm + daqpos + psd_grd_wait - 16us),
      PosDabPkt, PosXtrPkt, DABNORM);


  getssppulse(&echo1tmrba, &echo1tm, "rba",0);
  getwave(&echo1tmrbarsp,echo1tmrba);
  TNSON(e1entns_tm,pendallssp(echo1tmrba, 0));

  PosTnsOff = RUP_GRD(pendallssp(echo1tmrba, 0) + pw_gxspiral);
  TNSOFF(e1distns_tm,PosTnsOff);

  getwave(&echo1tmdab, &echo1tm);

  getssppulse(&pecho1tmxtr, &echo1tm, "xtr", 0);
  getwave(&echo1tmxtrrsp, pecho1tmxtr);

  PosGxptm = RUP_GRD(PosReadoutWindow_tm + pw_gxspiral + (pw_gxspoila + pw_gxspoil + pw_gxspoild) + pw_gxptma);
  /*printf("PosGzptm = %d s \n", PosGzptm);*/
  TRAPEZOID(XGRAD, gxptm, PosGxptm, 2000,,loggrd);
  TRAPEZOID(YGRAD, gyptm, PosGxptm, 2000,,loggrd);

  tm_time = RUP_GRD(tm_pos_start + 
      pw_gxrf1tm + pw_gxrf1tmd + 
      pw_gx1tma + pw_gx1tm + pw_gx1tmd +
      pw_gxspiral + (pw_gxspoila + pw_gxspoil + pw_gxspoild) + pw_gxptma + pw_gxptm +  pw_gxptmd ) + 1ms;


  SEQLENGTH(tmcore, tm_time, tmcore);

  return SUCCESS;
}


@rsp tmRSP

TYPDAB_PACKETS acq_echo1tm;

void rotate_spiral_base(int slab, float angle)
{
  float cphi, sphi;
  int i;
  long rotmtx[1][9];

  cphi = cos(angle);
  sphi = sin(angle);

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



STATUS tm_scancore()
{
  int count;
  int i;
  int rf1tmx_freq;
  int rf1tmy_freq;
  int receive_freq_tm;
  int golden_ratio_flag_tmp;
  int exphase_tm;
  int rcphase_tm;
  int count_view;
  float tm_angle[nangle];
  float tmp;
  float phi;
  
  tmp = 0;
  for (i = 0; i<nangle; i++)
  {
    tm_angle[i] = phi;
    tmp += gr;
    tmp -= floor(tmp);
    phi = tmp * 2.0 * M_PI;
  }
 /* 
  golden_ratio_flag_tmp = golden_ratio_flag;
  golden_ratio_flag = 0;
  */

  rf1tmx_freq = (int)(GAM * a_gxrf1tm * tm_xloc / (10 * TARDIS_FREQ_RES));
  rf1tmy_freq = (int)(GAM * a_gyrf1tm * tm_yloc / (10 * TARDIS_FREQ_RES));
  receive_freq_tm = TARDIS_FREQ_OFFSET/TARDIS_FREQ_RES;


  settrigger((short) TRIG_INTERN, (short) 0);

  boffset(off_tmcore);
  dabop = DABSTORE;
  dabecho = 0;
  
  setfrequency(receive_freq_tm,&echo1tm,0);


  for (count_view = 0; count_view < nangle; count_view++)
  {
    acq_echo1tm = DABOFF;
    dabview = count_view+1;

    for (i = 0; i < 2; i++)
    {

      if (i==0)
      {
        setfrequency(rf1tmx_freq,&rf1tm,scanrf1tm_inst); 
        setiampt(ia_gxrf1tm, &gxrf1tm, 0);
        setiampt(ia_gx1tm, &gx1tm, 0);
        setiampt(ia_gxptm, &gxptm, 0);
        setiampt(ia_gxspoil, &gxspoil, 1);

        setiampt(0, &gyrf1tm, 0);
        setiampt(0, &gy1tm, 0);
        setiampt(0, &gyspoil, 1);
        setiampt(0, &gyptm, 0);

        setiamp(ia_gxspiral, &gxspiral, 1);
        setiamp(0, &gyspiral, 1);
      }
      else
      {
        setfrequency(rf1tmy_freq,&rf1tm,scanrf1tm_inst); 

        setiampt(0, &gxrf1tm, 0);
        setiampt(0, &gx1tm, 0);
        setiampt(0, &gxspoil, 1);
        setiampt(0, &gxptm, 0);

        setiampt(ia_gyrf1tm, &gyrf1tm, 0);
        setiampt(ia_gy1tm, &gy1tm, 0);
        setiampt(ia_gyspoil, &gyspoil, 1);
        setiampt(ia_gyptm, &gyptm, 0);

        setiamp(0, &gxspiral, 1);
        setiamp(ia_gyspiral, &gyspiral, 1);
      }
      
      for (count = 0; count < tm_nex+tm_disdaqs_main; count++)
      {
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

        if (count > tm_disdaqs_main-1)
        {
          acq_echo1tm = DABON;
          dabslice = i*(tm_nex+1) + count - tm_disdaqs_main + 2;
        }

        loaddab(&echo1tm, dabslice, dabecho, dabop, dabview, acq_echo1tm, PSD_LOAD_DAB_ALL);
        startseq((SHORT)0, (SHORT)MAY_PAUSE);
        syncoff(&tmcore);
      }


      setiamp(0, &gxspiral, 1);
      setiamp(0, &gyspiral, 1);
      acq_echo1tm = DABOFF;
      dabslice = i*(tm_nex+1);

      for(count=0; count<tm_disdaqs_ref+1; count++)
      {
        /* take the useful part(hopefull) from spoil() */
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

        if (count==tm_disdaqs_ref)
          acq_echo1tm = DABON;
        loaddab(&echo1tm, dabslice, dabecho, dabop, dabview,acq_echo1tm, PSD_LOAD_DAB_ALL);
        startseq(0, (SHORT)MAY_PAUSE);
        syncoff(&tmcore);
      }
    }
    rotate_spiral_base(0, tm_angle[count_view]);
  }
 
  
  boffset(off_seqdelay3);
  setperiod(1000ms, &seqdelay3, 0);
  startseq((SHORT)0, (SHORT)MAY_PAUSE);

  boffset(off_seqpass);
  setwamp(SSPD + DABPASS + DABSCAN, &pass_pulse, 2);
  startseq(0,(SHORT)MAY_PAUSE);

  return SUCCESS;
}

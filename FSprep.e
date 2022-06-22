/*
use CSM rf waveform to generate Fat Sat preparation
rfpulse structure is bypassed here
*/

@cv FSprepCV

int FSvar;

int time_fsprep;

float area_gxkfs;
float area_gykfs;
float area_gyakfs;
float area_gzkfs;

/* creating rf waveform directly, so need to declare these */
int ia_rffs;
float a_rffs;
float flip_rffs;
int pw_rffs;
int off_rffs;

float area_rffs, area_rf1;

@host FSprepEval

STATUS FSprepEval(void)
{
  pw_rffs = 16ms;

  area_gxkfs = 3450;
  area_gykfs = 3450;
  area_gzkfs = 3450;

  amppwgrad(area_gxkfs, loggrd.tx_xyz/sqrt(2), 0.0, 0.0,loggrd.xrt,MIN_PLATEAU_TIME,
	&a_gxkfs, &pw_gxkfsa, &pw_gxkfs, &pw_gxkfsd);
  ia_gxkfs = (a_gxkfs / loggrd.tx_xyz)* MAX_PG_IAMP;

  amppwgrad(area_gykfs, loggrd.ty_xyz/sqrt(2), 0.0, 0.0,loggrd.yrt,MIN_PLATEAU_TIME,
	&a_gykfs, &pw_gykfsa, &pw_gykfs, &pw_gykfsd);
  ia_gykfs = (a_gykfs / loggrd.ty_xyz)* MAX_PG_IAMP;

  amppwgrad(area_gzkfs, loggrd.tz_xyz/sqrt(2), 0.0, 0.0,loggrd.zrt,MIN_PLATEAU_TIME,
	&a_gzkfs, &pw_gzkfsa, &pw_gzkfs, &pw_gzkfsd);
  ia_gzkfs = (a_gzkfs / loggrd.tz_xyz) * MAX_PG_IAMP;

  time_fsprep = 1ms + pw_rffs + pw_gzkfsa + pw_gzkfs + pw_gzkfsd + time_ssi;

  flip_rffs = 105;

  res_rffs = RES_RFCSM;

  area_rf1 = rfpulse[RF1_SLOT].area;
  area_rffs = SAR_CSM_AREA;

  ia_rffs = (int)( (float)(ia_rf1)*(flip_rffs/flip_rf1)
	*(area_rf1/area_rffs)*((float)(pw_rf1)/(float)(pw_rffs)) );

  off_rffs = -df; /* df is set is n3d.e - TDN */

  return SUCCESS;
}


@pg FSprepPG
STATUS FSprepPG(void)
{
    short *fs_wave_space;
    char rhoFile[256];

    SPACESAVER(RHO, rffs, res_rffs);
    addrfbits(&rffs, off_rffs, 1ms, pw_rffs);
    createinstr(&rffs, 1ms, pw_rffs, ia_rffs);
    strcpy(rhoFile, "rfcsm.rho");

    fs_wave_space = (short *)AllocNode(res_rffs*sizeof(short));
    uextwave(fs_wave_space,res_rffs,rhoFile);


    movewaveimm(fs_wave_space, &rffs, (int)0, res_rffs, TOHARDWARE);
    FreeNode(fs_wave_space);
 
    TRAPEZOID( YGRAD, gykfs, RUP_GRD(pend(&rffs, "rffs", 0) + pw_gykfsa
 	    - psd_rf_wait), area_gykfs, TYPNDEF,loggrd ); 

    TRAPEZOID( XGRAD, gxkfs, RUP_GRD(pend(&rffs, "rffs", 0) + pw_gxkfsa
 	    - psd_rf_wait), area_gxkfs, TYPNDEF,loggrd );

    TRAPEZOID( ZGRAD, gzkfs, RUP_GRD(pend(&rffs, "rffs", 0) + pw_gzkfsa
 	    - psd_rf_wait), area_gzkfs, TYPNDEF,loggrd );

    SEQLENGTH(seqfsprep, time_fsprep, seqfsprep);

    attenflagon(&seqfsprep, 0);

    return SUCCESS;
} 


@rsp FSprepRsp
STATUS FSprepRsp(void)
{
  boffset(off_seqfsprep);

  setfrequency((int)(off_rffs/TARDIS_FREQ_RES), &rffs, 0);
  rfon(&rffs,0);
  setiamp(ia_rffs, &rffs, 0);

  setiampt(ia_gxkfs, &gxkfs, 0);
  setiampt(ia_gykfs, &gykfs, 0);
  setiampt(ia_gzkfs, &gzkfs, 0);

  startseq((short)slabindex,(SHORT)MAY_PAUSE);

  return SUCCESS;
}

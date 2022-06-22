@cv SpoilerCV

float gscale_kill = 0.6; /* killer gradient scaling factor to avoid gradient overrange */
int time_spoiler;
float area_spoilerx = 3500.0;
float area_spoilery = 3500.0;
float area_spoilerz = 3500.0;

/* CRT ************************************* TDN 05/20/07 */
int time_killer;
/*float area_killerz = 15000.0;*/
float area_killerz = 3500.0;
float area_killerx = 3500.0;
float area_killery = 3500.0;
/*************************************************************/


@host SpoilerEval

STATUS SpoilerEval(void)
{
  if ((opexsatmask == 0) || (opexsatmask == 8)) {
    area_spoilerx = 0.0;
    area_spoilery = GYSATKILLER;
    area_spoilerz = 0.0;
  }

  if (opexsatmask == 40) {
    area_spoilerx = 0.0;
    area_spoilery = GYSATKILLER/2.0;
    area_spoilerz = -GYSATKILLER;   
  }

  if (opexsatmask == 12) {
    area_spoilerx = GYSATKILLER;
    area_spoilery = 0.0;
    area_spoilerz = GYSATKILLER;   
  }

  if (opexsatmask == 60) {
    area_spoilerx = GYSATKILLER;
    area_spoilery = GYSATKILLER;
    area_spoilerz = GYSATKILLER;   
  }

  /* CRT added gscale_kill - TDN 05/20/07 */
  if (!floatsAlmostEqualEpsilons(area_spoilerx, 0.0, 2)) {  
    amppwgrad(area_spoilerx, loggrd.tx_xyz*gscale_kill, 0.0, 0.0, loggrd.xrt, MIN_PLATEAU_TIME,
  	      &a_gxksp, &pw_gxkspa, &pw_gxksp, &pw_gxkspd);
    ia_gxksp = (a_gxksp / loggrd.tx_xyz) * MAX_PG_IAMP;
  }

  if (!floatsAlmostEqualEpsilons(area_spoilery, 0.0, 2)) { 
    amppwgrad(area_spoilery, loggrd.ty_xyz*gscale_kill, 0.0, 0.0, loggrd.yrt, MIN_PLATEAU_TIME,
  	      &a_gyksp, &pw_gykspa, &pw_gyksp, &pw_gykspd);
    ia_gyksp = (a_gyksp / loggrd.ty_xyz) * MAX_PG_IAMP;
  }

  if (!floatsAlmostEqualEpsilons(area_spoilerz, 0.0, 2)) { 
    amppwgrad(area_spoilerz, loggrd.tz_xyz*gscale_kill, 0.0, 0.0, loggrd.zrt, MIN_PLATEAU_TIME,
  	      &a_gzksp, &pw_gzkspa, &pw_gzksp, &pw_gzkspd);
    ia_gzksp = (a_gzksp / loggrd.tz_xyz) * MAX_PG_IAMP;
  }

  time_spoiler = 1ms + IMax(3, pw_gxkspa + pw_gxksp + pw_gxkspd,
                               pw_gykspa + pw_gyksp + pw_gykspd,
                               pw_gzkspa + pw_gzksp + pw_gzkspd) + time_ssi;
  if (time_spoiler < 3ms) time_spoiler = 3ms;

  return SUCCESS;
}

/* CRT ************************************* TDN 05/20/07 */
STATUS KillerEval(void)
{
  if (!floatsAlmostEqualEpsilons(area_killerx, 0.0, 2)) { 
    amppwgrad(area_killerx, loggrd.tx_xyz*gscale_kill, 0.0, 0.0, loggrd.xrt, MIN_PLATEAU_TIME,
	      &a_gxkill, &pw_gxkilla, &pw_gxkill, &pw_gxkilld);
    ia_gxkill = (a_gxkill / loggrd.tx_xyz) * MAX_PG_IAMP;
  }

  if (!floatsAlmostEqualEpsilons(area_killery, 0.0, 2)) { 
    amppwgrad(area_killery, loggrd.ty_xyz*gscale_kill, 0.0, 0.0, loggrd.yrt, MIN_PLATEAU_TIME,
	      &a_gykill, &pw_gykilla, &pw_gykill, &pw_gykilld);
    ia_gykill = (a_gykill / loggrd.ty_xyz) * MAX_PG_IAMP;
  }

  if (!floatsAlmostEqualEpsilons(area_killerz, 0.0, 2)) { 
    amppwgrad(area_killerz, loggrd.tz_xyz*gscale_kill, 0.0, 0.0, loggrd.zrt, MIN_PLATEAU_TIME,
	      &a_gzkill, &pw_gzkilla, &pw_gzkill, &pw_gzkilld);
    ia_gzkill = (a_gzkill / loggrd.tz_xyz) * MAX_PG_IAMP;
  }

  time_killer = 1ms + IMax(3, pw_gxkilla + pw_gxkill + pw_gxkilld,
                              pw_gykilla + pw_gykill + pw_gykilld,
                              pw_gzkilla + pw_gzkill + pw_gzkilld) + time_ssi;
  if (time_killer < 3ms) time_killer = 3ms;

  return SUCCESS;
}
/*************************************************************/


@pg SpoilerPG

STATUS SpoilerPG(void)
{
  if (!floatsAlmostEqualEpsilons(area_spoilerx, 0.0, 2)) {    
    TRAPEZOID(XGRAD, gxksp, RUP_GRD(1ms+pw_gxkfsa), area_spoilerx, TYPNDEF, loggrd); 
  }

  if (!floatsAlmostEqualEpsilons(area_spoilery, 0.0, 2)) { 
    TRAPEZOID(YGRAD, gyksp, RUP_GRD(1ms+pw_gykfsa), area_spoilery, TYPNDEF, loggrd);
  }

  if (!floatsAlmostEqualEpsilons(area_spoilerz, 0.0, 2)) { 
    TRAPEZOID(ZGRAD, gzksp, RUP_GRD(1ms+pw_gzkfsa), area_spoilerz, TYPNDEF, loggrd);
  }

  SEQLENGTH(seqspoiler, time_spoiler, seqspoiler);
  attenflagon(&seqspoiler, 0);

  return SUCCESS;
} 

/* CRT ************************************* TDN 05/20/07 */
STATUS KillerPG(void)
{
  if (!floatsAlmostEqualEpsilons(area_killerx, 0.0, 2)) { 
    TRAPEZOID(XGRAD, gxkill, RUP_GRD(1ms+pw_gxkilla), area_killerx, TYPNDEF, loggrd);
  }

  if (!floatsAlmostEqualEpsilons(area_killery, 0.0, 2)) { 
    TRAPEZOID(YGRAD, gykill, RUP_GRD(1ms+pw_gykilla), area_killery, TYPNDEF, loggrd);
  }

  if (!floatsAlmostEqualEpsilons(area_killerz, 0.0, 2)) { 
    TRAPEZOID(ZGRAD, gzkill, RUP_GRD(1ms+pw_gzkilla), area_killerz, TYPNDEF, loggrd);
  }

  SEQLENGTH(seqkiller, time_killer, seqkiller);
  attenflagon(&seqkiller, 0);

  return SUCCESS;
} 
/*************************************************************/

@rsp SpoilerRsp

STATUS SpoilerRsp(void)
{
  boffset(off_seqspoiler);

  /* CRT ************************************* TDN 05/20/07 */
  if (!floatsAlmostEqualEpsilons(area_spoilerx, 0.0, 2)) setiampt(ia_gxksp, &gxksp, 0);
  if (!floatsAlmostEqualEpsilons(area_spoilery, 0.0, 2)) setiampt(ia_gyksp, &gyksp, 0);
  if (!floatsAlmostEqualEpsilons(area_spoilerz, 0.0, 2)) setiampt(ia_gzksp, &gzksp, 0);
  /*************************************************************/

  startseq(0, (SHORT)MAY_PAUSE);
  return SUCCESS;
}

/* CRT ************************************* TDN 05/20/07 */
STATUS KillerRsp(void)
{
  boffset(off_seqkiller);

  if (!floatsAlmostEqualEpsilons(area_killerx, 0.0, 2)) setiampt(ia_gxkill, &gxkill, 0);
  if (!floatsAlmostEqualEpsilons(area_killery, 0.0, 2)) setiampt(ia_gykill, &gykill, 0);
  if (!floatsAlmostEqualEpsilons(area_killerz, 0.0, 2)) setiampt(ia_gzkill, &gzkill, 0);

  startseq(0, (SHORT)MAY_PAUSE);
  return SUCCESS;
}
/*************************************************************/

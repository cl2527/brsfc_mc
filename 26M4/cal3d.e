/*
 * Copyright (c) 2012 by General Electric Company. All Rights Reserved.
 */

/**
 * \file cal3d.e
 *
 * This is the EPIC inline file for 3D GRE calibration.
 *
 * 3D GRE calibration uses the concept of a "pass set", which is a group
 * of acquisitions from different coil modes performed sequentially with
 * identical scan parameters. Practically, a pass set includes a surface
 * array acquisition and possibly a body coil acquisition. Depending on
 * the calibration mode, single or multiple pass sets may be acquired.
 * Up to 3 pass sets are supported, but only up to 2 are used in
 * product.
 *
 * Looping over acquisitions from each coil in each pass set occurs in
 * the phase loop. However, the scan is considered to be multi-pass, not
 * multi-phase, from a reconstruction perspective.
 *
 * @author Ty Cashen
 * @since 24.0
 */

/*
 * Comments:
 * Date (dd mmm yyyy) Author (or Initials)
 * Comment
 *
 * 30 Jul 2012 TAC
 * HCSDM00136783 Initial version.
 *
 * 14 Oct 2013 TAC
 * HCSDM00243656 Fixed R1/R2 to prevent k-space overrange in body coil
 * acquisition.
 *
 * 11 Sep 2014 TAC
 * HCSDM00308045 Added support for sagittal calibration.
 *
 * 14 Mar 2016 TAC
 * HCSDM00398032 Implemented interleaved calibration.
 * 
 * 10 Aug 2016 GJ
 * HCSDM00416801 Update pistval2 to be more appropriate for slice-zip.
 */


@cv cal3d_cv
int cal3d_flag = 0 with {0, 1, 0, INVIS, "Enable 3D Cal scan",};

int cal3d_interleave = 0 with {0, 1, 0, VIS, "Enable interleaved 3D Cal scan",};

/* Total num of phases acquired, including PURE acquisition. */
int cal3d_phases = 3 with {1, 6, 3, VIS, "Total num of phases acquired for 3D Cal",};
int cal3d_pass_set = 1 with {1, 3, 1, VIS, "Total num of pass set for 3D Cal",};

/* cal3d_state[n]: state for the nth pass set where 1 specifies only a
 * surface array acquisition and 2 specifies both surface array and body
 * coil acquisitions */
int cal3d_state = 1 with {1, 2, 1, VIS, "State for current interleaved pass set",};
int cal3d_state1 = 2 with {1, 2, 2, VIS, "State for 1st pass set",};
int cal3d_state2 = 1 with {1, 2, 1, VIS, "State for 2nd pass set",};
int cal3d_state3 = 1 with {1, 2, 1, VIS, "State for 3rd pass set",};

/* cal3d_nex[n]: NEX value for the nth pass set */
int cal3d_nex1 = 2 with {1, 99, 2, VIS, "NEX for 1st pass set",};
int cal3d_nex2 = 0 with {0, 99, 0, VIS, "NEX for 2nd pass set",};
int cal3d_nex3 = 0 with {0, 99, 0, VIS, "NEX for 3rd pass set",};

int cal3d_pause_step = 0 with {0, , 0, VIS, "Pause step size multi-NEX CAL in us",};
int cal3d_nex_mode = 0 with {0, 1, 0, VIS, "3d cal opnex mode, 0-min, 1-max.",};

int ASSET_MAX_SLQUANT = 32;


@host cal3d_cvinit
if ((0 < exist(opassetcal)) || (0 < exist(oppurecal)))
{
    cal3d_flag = PSD_ON;
}
else
{
    cal3d_flag = PSD_OFF;
}

if (cal3d_flag)
{
    cvoverride(vstrte_flag, PSD_OFF, PSD_FIX_ON, PSD_EXIST_ON);

    cvmax(rhasset, 11);

    picalmodenub = 1;

    pidefcaldelay = 5s;

    pimultislab = PSD_OFF;
    pimultigroup = PSD_OFF;

    /* multiphase and cal are not compatible */
    cvoverride(mph_flag, PSD_OFF, PSD_FIX_ON, PSD_EXIST_ON);

    /* ARC and cal are not compatible */
    cvoverride(arc_flag, PSD_OFF, PSD_FIX_ON, PSD_EXIST_ON);
    cvoverride(arc_research_flag, PSD_OFF, PSD_FIX_ON, PSD_EXIST_ON);

    pite1nub = 0;

    /* allow only one echo */
    piechnub = 0;
    pinecho = 1;
    cvoverride(opnecho, 1, PSD_FIX_ON, PSD_EXIST_ON);

    cvoverride(opasset, ASSET_REG_CAL, PSD_FIX_ON, PSD_EXIST_ON);

    if ((PSD_OFF == !checkOptionKey(SOK_ASSET)) && (PSD_OFF == !checkOptionKey(SOK_ASSET91)))
    {
        epic_error( use_ermes, "%s is not available without the option key.", EM_PSD_FEATURE_OPTION_KEY, EE_ARGS(1), STRING_ARG, "ASSET Calibration" );
        return FAILURE;
    }

    opslblank = 2;
    cvmax(opslthick, 30.0);
    cvmin(opxres, CAL_ACQ_MATRIX);
    cvmin(opyres, CAL_ACQ_MATRIX);
    cvdef(opxres, _opxres.minval);
    cvdef(opyres, _opyres.minval);
    cvoverride(opxres, CAL_ACQ_MATRIX, PSD_FIX_ON, PSD_EXIST_ON);
    cvoverride(opyres, CAL_ACQ_MATRIX, PSD_FIX_ON, PSD_EXIST_ON);
    xres = exist(opxres);
  
    cvdef(oprbw, 62.5);
    cvoverride(oprbw, 62.5, PSD_FIX_ON,PSD_EXIST_ON);

    opimode = PSD_3D;
    cvdef(opimode,PSD_3D);
    cvoverride(opimode, PSD_3D, PSD_FIX_ON,PSD_EXIST_ON);

    cvoverride(opautote, PSD_MINTEFULL, PSD_FIX_ON, PSD_EXIST_ON);
}
else
{
    picalmodenub = 0;
}

if (cal3d_flag)
{
    /* Check for invalid imaging options */
    /* enable EDR,ZIP2 with 3dCal, need recon turn on options */
    if ( exist(opfcomp) || exist(opnopwrap) || exist(oppomp) || 
        exist(opsquare) || exist(opscic) || exist(opexor) || exist(opblim) || 
        exist(opmt) || exist(opirmode) || exist(opcgate) || exist(oprtcgate) || 
        exist(optlrdrf) || exist(opirprep) || exist(opdeprep) || exist(opmph) || 
        exist(opfulltrain) || exist(opcmon) || exist(opzip1024) || exist(opzip512) || 
        exist(opslzip4) || exist(opsmartprep) || exist(opbsp) || 
        exist(opmultistation) || exist(oprealtime) || exist(opt2prep) || 
        exist(opssrf) || exist(opphsen) || exist(opfluorotrigger) || exist(opassetscan) )
    {
        epic_error( use_ermes, "ASSET Calib and PURE reference scan is not compatible with other imaging options (except Fast )", EM_PSD_ASSET_CAL_OPTIONS_INCOMPATIBLE, EE_ARGS(0) );
        return FAILURE;
    }
}

if (cal3d_flag && (TRM_ZOOM_COIL == exist(opgradmode)))
{
        epic_error( use_ermes, "ASSET Calibration is not supported with ZOOM gradient mode.", EM_PSD_ASSET_ZOOM_INCOMPATIBLE, EE_ARGS(0) );
        return ADVISORY_FAILURE;
}

if (cal3d_flag && !((PSD_AXIAL == exist(opplane)) || (PSD_SAG == exist(opplane))))
{
        epic_error( use_ermes, "%s plane must be selected for %s.",
                    EM_PSD_PLANE_SELECTION, EE_ARGS(2), STRING_ARG, "Axial or sagittal",
                    STRING_ARG, "ASSET or PURE Calibration");
        return FAILURE;
}

if ( cal3d_flag && existcv(opslquant) && ((exist(opslquant)-(2*exist(opslblank))) > ASSET_MAX_SLQUANT) )
{
        avmaxslquant = ASSET_MAX_SLQUANT;
        epic_error( use_ermes, "Maximum number of slices is %d.", EM_PSD_MAX_SLICE, EE_ARGS(1), INT_ARG, avmaxslquant );
        return ADVISORY_FAILURE;
}


@host cal3d_cveval
if (cal3d_flag)
{
    cvoverride(vstrte_flag, PSD_OFF, PSD_FIX_ON, PSD_EXIST_ON);
}

if (cal3d_flag)
{
    if (!((PSD_AXIAL == exist(opplane)) || (PSD_SAG == exist(opplane))))
    {
        epic_error( use_ermes, "%s plane must be selected for %s.",
                    EM_PSD_PLANE_SELECTION, EE_ARGS(2), STRING_ARG, "Axial or sagittal",
                    STRING_ARG, "ASSET or PURE Calibration");
        return FAILURE;
    }

    if (1 < exist(opncoils))
    {
        epic_error(use_ermes, "%s is not compatible with %s.", EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                   STRING_ARG, "SwiFT coil configuration",
                   STRING_ARG, "3D calibration");
        return FAILURE;
    }

    rfb1opt_flag = 1;
    opslblank = 2;
    pioverlap = 1;
    pichemsatopt = 0;
    pisupnub = 0;

    /* 3D Gradwarp */
    op3dgradwarp = PSD_OFF;
    opauto3dgradwarp = PSD_OFF;
    pi3dgradwarpnub = 0;

    pititle = 0;

    cvoverride(opsldelay, IMax(2, _opsldelay.minval, opcaldelay), PSD_FIX_ON, PSD_EXIST_ON);

    int psc_nex = 1;
    if (1 == cal3d_nex_mode)
    {
        psc_nex = IMax(3, cal3d_nex1, cal3d_nex2, cal3d_nex3);
    }
    else
    {
        psc_nex = IMin(3, cal3d_nex1>0?cal3d_nex1:99, cal3d_nex2>0?cal3d_nex2:99, cal3d_nex3>0?cal3d_nex3:99);
    }
    psc_nex = IMax(2, psc_nex, 1); /* lower bounded by 1 */
    /* opnex = psc_nex; */
    cvoverride(opnex, psc_nex, PSD_FIX_OFF,PSD_EXIST_ON);
}

if (cal3d_flag && (B0_30000 == cffield) && (act_te < min_tenfe))
{
    epic_error( 0, "Please increase slice thickness.", 0, EE_ARGS(0) );
    return FAILURE;
}

@host cal3d_cveval_prescan
/* HCSDM00243656 */
if (cal3d_flag)
{
    oprgcalmode = RG_CAL_MODE_AUTO;
}

@host cal3d_cveval1_opfphases
if (cal3d_flag) 
{
    cal3d_pass_set = (cal3d_nex1>0?1:0) + (cal3d_nex2>0?1:0) + (cal3d_nex3>0?1:0);
    cal3d_phases = (cal3d_nex1>0?cal3d_state1:0) + (cal3d_nex2>0?cal3d_state2:0) + (cal3d_nex3>0?cal3d_state3:0);

    _opfphases.fixedflag = 0;
    if (cal3d_interleave)
    {
        opfphases = cal3d_pass_set;
    }
    else
    {
        opfphases = cal3d_phases;
    }
    _opfphases.fixedflag = 1;
    setexist(opfphases,PSD_ON);
}

@host cal3d_cveval1
if (cal3d_flag)
{
    int cal3d_fov = coilInfo[0].assetCalMaxFov;
    cvdef(opfov, cal3d_fov);
    opfov = cal3d_fov;

    /* calculate the isotropic slice thickness */
    float cal3d_slthick = opfov*1.0/CAL_ACQ_MATRIX;

    /*HCSDM00416801 Update pistval2 to be more appropriate for slice-zip.
      Copy following code from cvcheck() in efgre3d.e.*/
    if ((((int)(10.0*cal3d_slthick + 0.5) % slicezp) != 0) && (exist(opslzip2) || exist(opslzip4))) 
    {
        float temp_slthick_zip;

        temp_slthick_zip = (0.1*(float)slicezp)*(float)((int)((10.0/(float)slicezp)*(cal3d_slthick+0.05*(float)slicezp)+0.001));

        /* If the nearest slice thickness is out of range, round the
         * opposite direction. */
        if (temp_slthick_zip < avminslthick)
        {
            temp_slthick_zip += 0.1*(float)slicezp;
        }
        if (temp_slthick_zip > avmaxslthick)
        {
            temp_slthick_zip -= 0.1*(float)slicezp;
        }

        cal3d_slthick = temp_slthick_zip;
    }

    cvdef(opslthick, cal3d_slthick);
    opslthick = cal3d_slthick;

    pircbnub = 0;

    pite1nub = 0;

    piechnub = 0;
    pinecho = 1;

    pistnub = 2;
    pistval2 = cal3d_slthick;

    pixresnub = 0;
    piyresnub = 0;

    piphasfovnub = 0;
    piphasfovnub2 = 0;
    cvoverride(opphasefov,1.0,PSD_FIX_ON,PSD_EXIST_ON);

    pifovnub = 2;
    pifovval2 = cal3d_fov;

    rhimsize = exist(opxres);
    if (rhimsize < 64 )
    {
        rhimsize = 64;
    }
    rhrcxres = rhimsize;
    rhrcyres = rhimsize * (1 + opnopwrap) * (exist(opphasefov));

    pifanub =  0;

    /* pinexnub = 1 + 2; */
    pinexnub = 0;
    pinexval2 = 1;
    
    char attribute_codeMeaning[ATTRIBUTE_RESULT_SIZE] = "";
    getAnatomyAttributeCached(exist(opanatomy), ATTRIBUTE_CODE_MEANING, attribute_codeMeaning);

    if ((isDVSystem() || isKizunaSystem()) && (B0_30000 == cffield) && exist(oppurecal) &&
        ( (isCategoryMatchForAnatomy(exist(opanatomy), ATTRIBUTE_CATEGORY_CHEST) && strcmp(attribute_codeMeaning, "Breast")) || isCategoryMatchForAnatomy(exist(opanatomy), ATTRIBUTE_CATEGORY_ABDOMEN) || isCategoryMatchForAnatomy(exist(opanatomy), ATTRIBUTE_CATEGORY_PELVIS)))
    {
        cal3d_interleave = 1;
    }
    else
    {
        cal3d_interleave = 0;
    }


    if (exist(oppurecal))
    {
        cal3d_state1 = 2;
    }
    else
    {
        cal3d_state1 = 1;
        cal3d_state2 = 1;
        cal3d_state3 = 1;
    }

    switch (exist(opcalmode))
    {
        case CAL_MODE_FREEBREATHING:
            cal3d_nex1 = 6;
            cal3d_nex2 = 0;
            cal3d_nex3 = 0;

            break;

        case CAL_MODE_BREATHHOLD_FREEBREATHING:
            cal3d_nex1 = 2;
            cal3d_nex2 = 6;
            cal3d_nex3 = 0;

            break;

        case CAL_MODE_STANDARD:
        default:
            cal3d_nex1 = 2;
            cal3d_nex2 = 0;
            cal3d_nex3 = 0;

            break;
    }
}

if (cal3d_flag)
{
    /* sldeltime is reserved for multi-phases scan in efgre3d.e to
     * control waiting time between phases */
    cvoverride(sldeltime, 0, PSD_FIX_ON, PSD_EXIST_ON); 

    if (1 == exist(opfphases))
    {
        sldelay = TR_PASS; /* interslice delay */
    }
    else
    {
        sldelay = (int)(opsldelay);
    }

    /* actual delay time after TR_PASS */
    cal3d_pause_step = IMax(2, (sldelay - TR_PASS), 0);
}

if (cal3d_flag)
{
    seq_type = TYPF3DMPH;
    rhinitpass = opfphases;
}


@host cal3d_cveval1_avmintscan
if (cal3d_flag)
{
    avmintscan = (float)act_tr
                  * (cal3d_state1*cal3d_nex1+cal3d_state2*cal3d_nex2+cal3d_state3*cal3d_nex3)
                 * ((float)(exist(opslquant)
                 * eg_phaseres*exist(opphasefov))*pfkr_fraction) 
               + TR_PASS*opfphases 
               + (cal3d_nex2>0?1:0)*cal3d_pause_step;
}

@host cal3d_cvcheck_slquant
if (cal3d_flag)
{
    if ( existcv(opslquant) && ((exist(opslquant)-(2*(exist(opslblank)))) > ASSET_MAX_SLQUANT) )
    {
        avmaxslquant = ASSET_MAX_SLQUANT;
        epic_error( use_ermes, "Maximum number of slices is %d.",
                    EM_PSD_MAX_SLICE, EE_ARGS(1), INT_ARG, avmaxslquant );
        return FAILURE;
    }
}


@host cal3d_predownload
/* PURE CAL */
/* Adjust Fermi Radius and Width for ASSET */
if (cal3d_flag)
{
    fermi_rc = (float)(12.0 / exist(opxres));   /* rhfermr = 12 (was 14) */
    fermi_wc = (float)(2.0 / 10.0);    /* rhfermw = 2 (was 4) */

    rhasset = ASSET_REG_CAL; /* Tell recon the scan is a regularized calibration. */
    rhimsize = 64;
    rhrcxres = 64;
    rhrcyres = 64;

    /* apodization parameters */
    rhfermr = 12;
    rhfermw = 2;
    rh3dwintype = 1.0;
    rh3dwina = 0.59; /* Value was calculated to match Fermi window. */
    rh3dwinq = 0.27; /* Value was calcualted to match Fermi window. */
 
    rh2dscale = 10.0; /* Without scaling, body coil signal is too low, and quantization noise becomes significant. */

    rhcalmode = cal3d_interleave;

    /* rhcal_pass_set_vector: calibration pass set vector where the
     * first digit specifies the number of pass sets and subsequent
     * digits specify the number of acquisitions for each pass set
     *
     * rhcal_nex_vector: calibration pass set NEX vector where the first
     * digit specifies the number of pass sets and subsequent pairs of
     * digits specify the NEX values for each pass set
     *
     * rhcal_weight_vector: calibration pass set weight vector where the
     * first digit specifies the number of pass sets and subsequent
     * pairs of digits specify the weighting percentages for each pass
     * set */
    rhcal_pass_set_vector = cal3d_pass_set;
    rhcal_nex_vector      = cal3d_pass_set;
    rhcal_weight_vector   = cal3d_pass_set;

    if ( cal3d_nex1 > 0 )
    {
        rhcal_pass_set_vector = rhcal_pass_set_vector * 10 + cal3d_state1;
        rhcal_nex_vector = rhcal_nex_vector * 100 + cal3d_nex1;
        rhcal_weight_vector = rhcal_weight_vector * 100 + (int)(99.0/cal3d_pass_set);
    }
    if ( cal3d_nex2 > 0 )
    {
        rhcal_pass_set_vector = rhcal_pass_set_vector * 10 + cal3d_state2;
        rhcal_nex_vector = rhcal_nex_vector * 100 + cal3d_nex2;
        rhcal_weight_vector = rhcal_weight_vector * 100 + (int)(99.0/cal3d_pass_set);
    }
    if ( cal3d_nex3 > 0 )
    {
        rhcal_pass_set_vector = rhcal_pass_set_vector * 10 + cal3d_state3;
        rhcal_nex_vector = rhcal_nex_vector * 100 + cal3d_nex3;
        rhcal_weight_vector = rhcal_weight_vector * 100 + (int)(99.0/cal3d_pass_set);
    }

    rhslblank = opslblank * slicezp;

    cvoverride(rhpure, 1, PSD_FIX_ON, PSD_EXIST_ON);

    rhimsize = exist(opxres);
    if (rhimsize < 64 )
    {
        rhimsize = 64;
    }
    xres = exist(opxres);
    rhrcxres = rhimsize;
    rhrcyres = rhimsize * (1 + opnopwrap) * (exist(opphasefov));
}

/* PURE CAL should be treated as multiphase scan */
if (cal3d_flag)
{

    ihtr = act_tr + ((TRIG_LINE == gating) ? TR_SLOP : 0);
    if ( vstrte_flag )
    {
        ihtr = (int) 100.0*floor(ihtr/100.0);
    }
    free(ihtdeltab);
    ihtdeltab = (int *)malloc(opslquant*opvquant*opfphases*slicezp*sizeof(int));
    exportaddr(ihtdeltab, (int)(opslquant*opvquant*opfphases*slicezp*sizeof(int)));
    for (i = 0; i < opslquant*opvquant*opfphases; i++)
    {
      ihtdeltab[i*slicezp] = (1*slquant1) * act_tr*((float)nreps/(float)rhnslices)+ 1*(float)(sldelay); 
      for (j=1;j<slicezp;j++)
      {
          ihtdeltab[i*slicezp+j] = ihtdeltab[i*slicezp];
      }
    }
}

/* Replicating slices for PURE CAL */
if (cal3d_flag)
{
    for (i = 0; i < opslquant * opfphases; i++)
    {
        data_acq_order[i].slloc  = data_acq_order[i%opslquant].slloc;
        data_acq_order[i].slpass = (int)floor(i/opslquant);
        data_acq_order[i].sltime = data_acq_order[i%opslquant].sltime;
    }
}


@host cal3d_predownload_nex
if (cal3d_flag)
{
    ihnex = exist(opnex);
    pinex = exist(opnex);
}


@rsp cal3d_rsp
enum coils {body_coil, surface_array};
enum coils coil_previous = surface_array;


@rsp cal3d_scancore_phase

/* Switch coils for PURE */
if (cal3d_flag && !cal3d_interleave)
{
    enum coils coil_current;
    int phasecount = 0;

    /* For current phase, determine NEX and coil. */
    rspnex = cal3d_nex1;

    if (phaseindex == phasecount)
    {
        coil_current = surface_array;
    }
    else if ((2 == cal3d_state1) && (phaseindex == phasecount+1))
    {
        coil_current = body_coil;
    }
    else
    {
        phasecount += cal3d_state1;

        rspnex = cal3d_nex2;

        if (phaseindex == phasecount)
        {
             coil_current = surface_array;
        }
        else if ((2 == cal3d_state2) && (phaseindex == phasecount+1))
        {
             coil_current = body_coil;
        }
        else
        {
             phasecount += cal3d_state2;

             rspnex = cal3d_nex3;

             if (phaseindex == phasecount)
             {
                  coil_current = surface_array;
             }
             else if ((2 == cal3d_state3) && (phaseindex == phasecount+1))
             {
                  coil_current = body_coil;
             }
             else
             {
                  return FAILURE;
             }
        }
    }

    /* If necessary, switch coil. */
    if ((coil_current == body_coil) && (coil_previous == surface_array))
    {
        if (coilInfo_tgt[0].hubIndex != volRecCoilInfo_tgt[0].hubIndex)
        {
             if (FAILURE == CoilSwitchSetCoil(volRecCoilInfo_tgt[0], 1))
             {
                  return FAILURE;
             }
             boffset(off_seqcore);
             printf("switch to body coil\n");
        }
    }
    else if ((coil_current == surface_array) && (coil_previous == body_coil))
    {
        if (FAILURE == CoilSwitchSetCoil(coilInfo_tgt[0], 1))
        {
             return FAILURE;
        }
        boffset(off_seqcore);
        printf("switch to surface coil\n");
    }

    coil_previous = coil_current;
}
else if (cal3d_flag && cal3d_interleave)
{
    switch (phaseindex)
    {
        case 2:
            cal3d_state = cal3d_state3;
            rspnex = cal3d_nex3;

            break;

        case 1:
            cal3d_state = cal3d_state2;
            rspnex = cal3d_nex2;

            break;

        case 0:
        default:
            cal3d_state = cal3d_state1;
            rspnex = cal3d_nex1;

            break;
    }
}


@rsp cal3d_scancore_pause
/* no delay time for the last acq, and for pure coil switch */ 
if (cal3d_flag)
{
    if (((!cal3d_interleave && ((pass+1) == cal3d_state1)) || (cal3d_interleave && (0 == pass))) &&
        (0 < cal3d_nex2) && (slicecnt == acqs))
    {
        pause = MAY_PAUSE;
        setperiod((long)cal3d_pause_step, &seqpass, 0);
    }
    else
    {
        pause = MAY_PAUSE;
        setperiod((long)pass_seqtime_def, &seqpass, 0);
    }

#ifdef PSD_HW
    if (((!cal3d_interleave && ((pass+1) == cal3d_state1)) || (cal3d_interleave && (0 == pass))) &&
        (slicecnt == acqs))
    {
        broadcast_scan_end_for_autovoice();
    }
#endif
}


@host cal3d_cvevaliopts
if (cal3d_flag)
{
    disable_ioption(PSD_IOPT_NOP_WRAP);
    disable_ioption(PSD_IOPT_CARD_GATE);
    disable_ioption(PSD_IOPT_MPH);
    disable_ioption(PSD_IOPT_SQR_PIX);
    disable_ioption(PSD_IOPT_RESP_TRIG);
    disable_ioption(PSD_IOPT_ASSET);
    disable_ioption(PSD_IOPT_ZIP_1024);
    disable_ioption(PSD_IOPT_ZIP_512);
    disable_ioption(PSD_IOPT_SLZIP_X4);
    disable_ioption(PSD_IOPT_MULTI_STATION);
    disable_ioption(PSD_IOPT_FLUORO);
    disable_ioption(PSD_IOPT_NAV);
    disable_ioption(PSD_IOPT_SMART_PREP);
    disable_ioption(PSD_IOPT_IR_PREP);
    disable_ioption(PSD_IOPT_DYNPL);
    disable_ioption(PSD_IOPT_FLOW_COMP);
    disable_ioption(PSD_IOPT_IDEAL);
    disable_ioption(PSD_IOPT_ARC);
    disable_ioption(PSD_IOPT_MILDNOTE);
    disable_ioption(PSD_IOPT_SSRF);
    disable_ioption(PSD_IOPT_MSDE);

    set_required_disabled_option( PSD_IOPT_SLZIP_X2 );
    set_required_disabled_option( PSD_IOPT_EDR );
}


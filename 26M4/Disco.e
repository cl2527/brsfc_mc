/*
 * Copyright (c) 2014 by General Electric Company. All Rights Reserved.
 */

/**
 * \file Disco.e
 *
 * DIfferential Subsampling with Cartesian Ordering (DISCO) is similar
 * to a multiphase scan but with better temporal resolution using
 * partial k-space acquisition for each phase.
 *
 * @author Manojkumar Saranathan/Dan Rettmann/Kang Wang/Ty Cashen
 * @since 25.0
 */

/*
 * Comments:
 * Date (dd mmm yyyy) Author (or Initials)
 * Comment
 *
 * 24 Feb 2014 DWR/KW/TAC
 * HCSDM00264720 Initial version.
 */


@host DiscoGlobal
#include "disco_support.h"

#define MAX_NUM_SUB_REGIONS 8
/*
 * Total regions in schedule is derived from generate_region_schedule() looping, assuming num_regions=2,
 * worst case is when num_sub_regions=MAX_NUM_SUB_REGIONS:
 * (mask total#Regions) + (min#ViewSharedPhases * num_regions) + ((PHASES_MAX-min#ViewSharedPhases) * total#Regions)
 */
#define MAX_REGION_SCHEDULE_LENGTH ((MAX_NUM_SUB_REGIONS+1) + (MAX_NUM_SUB_REGIONS*2) + ((PHASES_MAX-MAX_NUM_SUB_REGIONS)*(MAX_NUM_SUB_REGIONS+1)))


@host DiscoIpgexport
/* Note that a number of variables used by DISCO are shared with 
   TricksIpgexport in Tricks.e. Only new ones are declared here. */

/* Cumulative version of views_per_region for start and end indices of regions */
int cum_views_per_region[MAX_NUM_REGIONS];
int cum_regs_per_phase[PHASES_MAX+1];
int regs_per_phase[PHASES_MAX+1];
int RegionsSchedule[MAX_REGION_SCHEDULE_LENGTH];
int PhaseDoneSchedule[PHASES_MAX+1];


@cv DiscoCv
int disco_flag = 0 with {0, 1, 0, VIS, "0=off, 1=on" , };
int disco_1echo_flag = 0 with {0, 1, 0, VIS, "DISCO single echo mode: 0=off, 1=on" , };
int kacq_uid_washin = 0 with {, , 0, INVIS, "UID for DISCO DynaPlan Wash-in" , };

/* introduce a new variable to represent total number phases (including mask) for DynaPlan and non-DynaPlan mode */
int disco_nphases = PHASES_MIN with {PHASES_MIN, PHASES_MAX+1, PHASES_MIN, INVIS, "total number of DISCO phases" , }; 
int peakPhaseIndex = 0 with {0, PHASES_MAX+1, 0, INVIS, "peak phase index (1-based) in DISCO with variable temporal update rate" , };

int num_regions = 2 with {2, 2, 2 ,INVIS, "The # of DISCO regions before subdivision",};
int num_sub_regions = 3 with {2, MAX_NUM_SUB_REGIONS, 3, VIS, "Number of B sub-regions", };  /* 3 = A B1 A B2 A B3 */
float aregion_fraction = 0.16 with {0.05, 0.5, 0.16, VIS, "Fraction of k-space for the central A region", };
float act_aregion_fraction = 0.16 with {0.05, 1.0, 0.16, INVIS, "Actual fraction of k-space for the central A region", };
int combo_mode = 0 with {0, 2, 0, VIS, "View sharing: 0=backward, 1=nearest neighbor, 2=forward", };
int num_mask_regions = 4 with {3, 11, 4, INVIS, "The number of unique regions that constitute k-space",}; 
int total_acq_regions = 3 with {3, , 3, INVIS,"The total number of regions acquired for all phases",};
int discodda = 250 with {0, , 250, VIS, "Number of disdacqs to play before first phase",};
int total_acq_points = 0 with {0, , 0, INVIS, "The total number of points acquired for all phases",};
float num_transition_fraction = 0.5 with {0.0, 1.0, 0.5, INVIS, "Fraction of A region to use for transition between B back to center of A: 0=EC, 1=reverse EC", }; 
int mask_phase_flag = 1 with {0, 1, 1 ,INVIS, "first phase is pre-contrast mask or not: 1=Yes, 0=No",};
int pause_after_mask_flag = 1 with {0, 1, 1 ,INVIS, "pause after pre-contrast mask: 1=Yes, 0=No",};
int region_order_mode = CENTER_REGION_FIRST with {CENTER_REGION_FIRST, OUTER_REGION_FIRST, CENTER_REGION_FIRST ,INVIS, "0=center region first; 1=outer region first",};
int reverse_first_region_flag = 0 with {0, 1, 0 ,INVIS, "reverse the view-order of the first region of the scan or after pause: 1=Yes, 0=No",};

int nr_of_segA = 1 with {1, , 1, INVIS, "Number of segments in A region",};
int regViewOrderMode = REGULAR with {REGULAR, INTERLEAVE, REGULAR, INVIS, "view-order within a region: 0=regular(non-interleave), 1=interleave",};
float dnav_win_BAratio = 2.0 with {1.0, 100.0, 2.0, VIS, "acceptance window ratio between outer and central region",};

@host GenerateSchedule
if (disco_flag)
{
    int ii = 0;
    if (2 == num_regions)
    {
        cvmax(num_mask_regions, 1 + _num_sub_regions.maxval);
    }
    else
    {
        cvmax(num_mask_regions, (_num_regions.maxval * (_num_regions.maxval + 1)) / 2);
    }

    mask_phase_flag = (exist(opdynaplan) || !smartprep_flag) ? 1: 0;

    if (PSD_OFF == mask_phase_flag)
    {
        cvoverride(pause_after_mask_flag, PSD_OFF, PSD_FIX_OFF, PSD_EXIST_ON);
    }
    else
    {
        pause_after_mask_flag = PSD_ON;
    }

    region_order_mode = CENTER_REGION_FIRST;
    reverse_first_region_flag = (OUTER_REGION_FIRST == region_order_mode);

    /* Format is num_regions, num_mask_regions, num_kernel_regions and then the kernel */
    generate_region_schedule( num_regions, num_sub_regions,
                              disco_nphases, mask_phase_flag, (OUTER_REGION_FIRST == region_order_mode), reverse_first_region_flag,
                              &num_mask_regions, &total_acq_regions,
                              RegionsSchedule, MAX_REGION_SCHEDULE_LENGTH, peakPhaseIndex, regs_per_phase );
    for (ii = 0; ii < disco_nphases; ii++)
    {
        if (0 == ii)
        {
            cum_regs_per_phase[ii] = regs_per_phase[ii];
        }
        else
        {
            cum_regs_per_phase[ii] = cum_regs_per_phase[ii-1] + regs_per_phase[ii];
        }
    }
}


@host ScanTime
if (disco_flag)
{
    float pfr = 0, dda_time = 0;
    int i = 0;

    discodda = dda_one_second; /* always one second */
    pitslice = sampledPoints*act_tr*((medal_flag && medal_multitr_flag)?medal_necho:1);  /* Save one full phase time */ 
    dda_time = discodda * act_tr;

    if (segmented_flag)
    {
        act_aregion_fraction = (float)nr_of_segA / (float)nr_of_segments;
    }
    else
    {
        act_aregion_fraction = aregion_fraction;
    }

    pfr = act_aregion_fraction;
    if (2 == num_regions)
    {
        pfr += (1-act_aregion_fraction)/num_sub_regions;
    }
    else
    {
        for (i = 2; i <= num_regions; i++)
        {
            pfr += (1-act_aregion_fraction)/(i*(num_regions-1));
        }
    }

    if (exist(opdynaplan))
    {
        pimscan = dda_time + pitslice;
        avmintscan = pimscan;
        pivsscan = dda_time + (peakPhaseIndex - mask_phase_flag - 1)*pitslice*pfr;
    }
    else
    {
        if (mask_phase_flag)
        {
            pimscan = dda_time + pitslice;
            avmintscan = dda_time*(PSD_ON == pause_after_mask_flag) + (disco_nphases-1)*pitslice*pfr; /* does not include mask time */
        }
        else
        {
            pimscan = 0;
            avmintscan = disco_nphases*pitslice*pfr + dda_time;
        }
    }

    pitres = pitslice*pfr;
}


@host DiscoCheck
if (disco_flag)
{
    if (exist(opsat))
    {
        epic_error(use_ermes,
                   "%s is incompatible with %s.",
                   EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                   STRING_ARG, "SAT",
                   STRING_ARG, "DISCO");
        return FAILURE;
    }

    if(medal_echo_mode)
    {
        epic_error(use_ermes,
                   "%s is incompatible with %s.",
                   EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                   STRING_ARG, "MEDAL sequential echo mode",
                   STRING_ARG, "DISCO");
        return FAILURE;
    }

    if ((CENTER_REGION_FIRST == region_order_mode) && (PSD_ON == reverse_first_region_flag))
    {
        epic_error(use_ermes,
                   "%s is incompatible with %s.",
                   EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                   STRING_ARG, "reverse DISCO first region view order",
                   STRING_ARG, "acquire center region first");
        return FAILURE;
    }

    if (reverse_first_region_flag && (num_regions != 2))
    {
        epic_error(use_ermes,
                   "%s is incompatible with %s.",
                   EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                   STRING_ARG, "reverse DISCO first region view order",
                   STRING_ARG, "num_regions != 2");
        return FAILURE;
    }

    if (navgate_flag && (num_regions != 2))
    {
        epic_error(use_ermes,
                   "%s is incompatible with %s.",
                   EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                   STRING_ARG, "Navigator DISCO",
                   STRING_ARG, "number of regions not equal to 2");
        return FAILURE;
    }

    if (navgate_flag && (!segmented_flag))
    {
        epic_error(use_ermes,
                   "%s is incompatible with %s.",
                   EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                   STRING_ARG, "Navigator DISCO",
                   STRING_ARG, "segmentation off");
        return FAILURE;
    }

    if (segmented_flag && (!navgate_flag))
    {
        epic_error(use_ermes,
                   "%s is incompatible with %s.",
                   EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                   STRING_ARG, "segmentation DISCO",
                   STRING_ARG, "Navigator off");
        return FAILURE;
    }

    if (navgate_flag && nav_dual_mode)
    {
        epic_error(use_ermes,
                   "%s is incompatible with %s.",
                   EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                   STRING_ARG, "Navigator DISCO",
                   STRING_ARG, "Navigator dual mode");
        return FAILURE;
    }
}


@host DiscoPredownload
if (disco_flag)
{
    FILE * fp = NULL;

    char zy_datafile[BUFSIZ] = "Sorted_arr_ZYSORT";
#ifndef SIM
    char psddata_path[BUFSIZ] = "/usr/g/psddata/";
#else
    char psddata_path[BUFSIZ] = "./";
#endif
    char filename[BUFSIZ]; 
    int i = 0;
    int status = 0;
    TRICKS_ZY_ORDER * reconZyOrder;

    /* Calculating cum_views_per_region so we do not have to pass param4d to IPG */
    for (i = 0; i < num_mask_regions + (PSD_ON == reverse_first_region_flag); i++)
    {
        if (0 == i) /* Central A region */ 
        {
            cum_views_per_region[i] = param4d.views_per_region[i]; 
        }
        else
        {
            cum_views_per_region[i] = cum_views_per_region[i-1] + param4d.views_per_region[i];
        } 
    }

    /* Compute the total number of acquired points */
    total_acq_points = 0;
    for (i = 0; i < total_acq_regions; i++)
    {
        total_acq_points += param4d.views_per_region[RegionsSchedule[i]];
    }
 
    status = writeVsc3DConfig( num_regions, num_mask_regions, total_acq_regions,
                               param4d.views_per_region,
                               RegionsSchedule, PhaseDoneSchedule,
                               disco_nphases, mask_phase_flag, (OUTER_REGION_FIRST == region_order_mode), reverse_first_region_flag, combo_mode, peakPhaseIndex,
                               rhkacq_uid );
    if (FAILURE == status)
    {
        epic_error( use_ermes, "Unable to write the file %s",
                    EM_PSD_DFM_TABLE_OPEN_ERROR, EE_ARGS(1),
                    STRING_ARG, filename );
        return FAILURE;
    }
    if (exist(opdynaplan))
    {
        /* for DynaPlan, write the non-view-share and view-share versions
         * However, do not overwrite RegionsSchedule and PhaseDoneSchedule
         */
        int TmpPhaseDoneSchedule[PHASES_MAX+1];

        /* non-view-share */
        status = writeVsc3DConfig( num_regions, num_mask_regions, num_mask_regions,
                param4d.views_per_region,
                RegionsSchedule, TmpPhaseDoneSchedule,
                1, mask_phase_flag, (OUTER_REGION_FIRST == region_order_mode), reverse_first_region_flag, combo_mode, 0, rhkacq_uid );
        if (FAILURE == status)
        {
            epic_error( use_ermes, "Unable to write the file %s",
                    EM_PSD_DFM_TABLE_OPEN_ERROR, EE_ARGS(1),
                    STRING_ARG, filename );
            return FAILURE;
        }

        /* view-share */
        status = writeVsc3DConfig( num_regions, num_mask_regions, opvsphases*num_regions,
                param4d.views_per_region,
                &RegionsSchedule[num_mask_regions], TmpPhaseDoneSchedule,
                opvsphases, 0, (OUTER_REGION_FIRST == region_order_mode), reverse_first_region_flag, combo_mode, 0, kacq_uid_washin );
        if (FAILURE == status)
        {
            epic_error( use_ermes, "Unable to write the file %s",
                    EM_PSD_DFM_TABLE_OPEN_ERROR, EE_ARGS(1),
                    STRING_ARG, filename );
            return FAILURE;
        }
    }

    /* Write Sorted_arr_ZYSORT with a unique id to ensure recon is reading right one */
    {
        reconZyOrder = (TRICKS_ZY_ORDER *)malloc(sizeof(TRICKS_ZY_ORDER)*sampledPoints);
        if (NULL == reconZyOrder)
        {
            printf("DISCO:WriteZYexport: Failure allocating reconZyOrder\n");
            free(reconZyOrder);
            return FAILURE;
        }

        for (i = 0; i < sampledPoints; i++)
        {
            reconZyOrder[i].view = zy_export[i].view;
            reconZyOrder[i].slice = zy_export[i].slice;
        }

        sprintf(filename, "%s%s.%d", psddata_path, zy_datafile, rhkacq_uid);     
        fp = fopen(filename, "wb");
        if (sampledPoints != (int)(fwrite(reconZyOrder, sizeof(TRICKS_ZY_ORDER), sampledPoints, fp)))
        {
            epic_error( use_ermes, "Unable to write the file %s",
                        EM_PSD_DFM_TABLE_OPEN_ERROR, EE_ARGS(1),
                        STRING_ARG, filename );
            free(reconZyOrder);
            return FAILURE;
        }
        fclose(fp);
        if (exist(opdynaplan))
        {
            sprintf(filename, "%s%s.%d", psddata_path, zy_datafile, kacq_uid_washin);     
            fp = fopen(filename, "wb");
            if (sampledPoints != (int)fwrite(reconZyOrder, sizeof(TRICKS_ZY_ORDER), sampledPoints, fp))
            {
                epic_error( use_ermes, "Unable to write the file %s",
                        EM_PSD_DFM_TABLE_OPEN_ERROR, EE_ARGS(1),
                        STRING_ARG, filename );
                free(reconZyOrder);
                return FAILURE;
            }
            fclose(fp);
        }
        free(reconZyOrder);
    }

    rhnslices = exist(opslquant) * exist(opfphases); /* Set rhnslices correctly */
    rhrawsize = total_acq_points * (n64)rhnecho * (n64)rhfrsize * (n64)(2*rhptsize); 
    rhdacqctrl |= RHDC_RAWDATA; /* Using RAWDATA mode to compress BAM and save space */
    rhviewSharing3D = TRUE; /* Tell recon to do 3D view sharing */
    
    if (autolock)
    {
        /* Copy files to /usr/g/mrraw, similar to kacq file */
        sprintf(filename, "%s.%d", zy_datafile, rhkacq_uid);
        copyKacqToMrraw(filename, psddata_path, filename);
        sprintf(filename, "%s.%d", zy_datafile, kacq_uid_washin);
        copyKacqToMrraw(filename, psddata_path, filename);

        sprintf(filename, "%s.%d", "vsc3d.cfg", rhkacq_uid);
        copyKacqToMrraw(filename, psddata_path, filename);
        sprintf(filename, "%s.%d", "vsc3d.cfg", kacq_uid_washin);
        copyKacqToMrraw(filename, psddata_path, filename);

        /* Ensure recon all pass so that pfile gets saved > 11 phases */
        rhtype1 |= RHTYP1RCALLPASS;
    }
    
    /* TDEL changes */
    free(ihtdeltab);
    ihtdeltab = (int *)malloc(opslquant*opvquant*slicezp*sizeof(int));
    exportaddr(ihtdeltab, (int)(opslquant*opvquant*slicezp*sizeof(int)));

    for (i = 0; i < opvquant*opslquant; i++) 
    {
        ihtdeltab[i*slicezp] = pitres;

        for (j = 1; j < slicezp; j++) 
        {
            ihtdeltab[i*slicezp+j] = ihtdeltab[i*slicezp];
        } 
    }
}
else
{
    rhviewSharing3D = FALSE;
}


@pg DiscoPhaseDonePkt
if(disco_flag)
{    
    /* Initialize the bits array. Better here than in sspinit(). */
    TREG_bits[0] = SSPDS + DABDC;
    TREG_bits[1] = SSPOC + DTREGOC;
    TREG_bits[2] = SSPD;
    TREG_bits[3] = SSPD;
    TREG_bits[4] = 0;

    SSPPACKET(ddphase, PosTemp+TREG_start+DIM_length, TREG_length, TREG_bits, 0);
    ddphase.tag = SSPTREG;
}


@rsp DiscoCore
STATUS
discocore( void )
{
    char psddbgstr[256] = "";
    int cntvus;     /* Flag for collecting central views in Oddnes NPW case */
    int rspsat=0;   /* Counter for deciding after which slices SAT plays    */
    int si;  /* Superindex for elliptical-centric*/
    int si_inc;  /* Superindex increment step size */

    int region_index = 0;
    int start_region, end_region;
    int startsi, endsi;
    int phasenum = opdynaplan ? currentPhase_dynaplan : 0;
    int additional_phase_done_needed = (phasenum >= disco_nphases);
    int inner_echo; /* to support multiple TR */
    int pre_dixtime, post_dixtime; /* to support multiple TR */
    int dixon_necho=1;
        
    int pre_segment_flag = PSD_OFF;
    int post_segment_flag = PSD_OFF;
    int seg_view_indx = 0;
    int nav_iter = 0;

    printdbg("Starting discocore", debugstate);
    sprintf(psddbgstr, "Start discocore with currentPhase_dynaplan = %d/%d\n", currentPhase_dynaplan, disco_nphases);
    printdbg(psddbgstr, debugstate);

#ifdef PSD_HW   /* Auto Voice */
    if (!smartprep_flag)
    {
        broadcast_autovoice_timing(0, trigger_delay_silent_countdown/1ms, FALSE, TRUE);
    }
#endif
    scandelay0();

    if (trigger_delay_wosp > 0)
    {
        if (opdynaplan)
        {
            reset_clock();
        }
        else
        {
            setscantimestop();
        }
    }
#ifdef PSD_HW
    if (opdynaplan)
    {
        if (1 == currentPhase_dynaplan)
        {
            setscantimeimm(pidmode, pivsscan, piviews, pitslice, opslicecnt);
            setscantimestart();
            setscantimeauto();   /* return clock to auto */
        }
    }
    else
    {
        /* need to do setscantimeimm again because AutoVoice may change scanner clock */
        if (mask_phase_flag)
        {
            if (pause_after_mask_flag)
            {
                setscantimeimm(pidmode, pimscan, piviews, pitslice, opslicecnt);
            }
            else
            {
                /* if mask ON, but no pause, then show total scan time */
                setscantimeimm(pidmode, avmintscan + pimscan, piviews, pitslice, opslicecnt);
            }
        }
        else
        {
            setscantimeimm(pidmode, avmintscan, piviews, pitslice, opslicecnt);
        }
        setscantimestart();
        setscantimeauto();   /* return clock to auto */
    }
#endif

    slabindex = 0;
    phaseindex = 0;
    pass = 0;

    view =  zy_export[0].view;
    slice = zy_export[0].slice;

    /* to support multiple TR */
    if(medal_flag && medal_multitr_flag)
    {
        post_dixtime = (GRAD_UPDATE_TIME + medal_pw - medal_shift1);
        pre_dixtime = (GRAD_UPDATE_TIME + medal_shift1);
        setperiod(post_dixtime, &dix_ssppost, 0);
        setperiod(pre_dixtime, &dix_xpre,0 );
        setperiod(pre_dixtime, &dix_ssppre,0);
        dixon_necho = medal_necho;
    }

    dabview = view + 1;
    dabslice = slice;
    setfrequency(rf1_freq[slabindex],&rf1,scanrf1_inst);
    set_echo1frequency(receive_freq1[slabindex], 0);
    if (opetl >= 2)
    {
        set_echo2frequency(receive_freq2[slabindex], 0);
    }

    setiamp(volumetab[dabslice], &gzcomb, 0);

    if (zrewind_flag)
    {
        setiamp(volumetab2[dabslice], &gzp, 0);
    }

    acq_echo1 = DABOFF;
    if (opetl>=2)
    {
        acq_echo2 = DABOFF;
    }

    setiamp(-viewtable[dabview], &gy1, 0);

    if (rewinder_flag)
    {
        setiamp(-viewtable[dabview], &gy1r, 0);
    }

    fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);
    if (opetl>=2)
    {
        fgre_loaddab_echo2(dabslice, (dabecho+1), (opetl-1), nshots, dabop, dabview, acq_echo2);
    }

    /* not sending 3D packets, these will be initiated by recon */
    load3d(&d3d, 0, DABOFF);

    /* Initialize yres_phase and slab_phase to zero */
    yres_phase = 0;
    slab_phase = 0;

    /* collect disdaq views */
    fgre_loadtreg(&ddphase, region_index, DABOFF);
    PlayDisdaqIntleave(discodda);

    si_inc = 1;       

    if (opdynaplan)
    {
        if ((0 == currentPhase_dynaplan) || (currentPhase_dynaplan >= disco_nphases)) /* Mask or Scan button pushed after completion */
        {
            start_region = 0;
            end_region = cum_regs_per_phase[0];
        }
        else if (1 == currentPhase_dynaplan) /* start of wash-in phases */
        {
            start_region = cum_regs_per_phase[currentPhase_dynaplan - 1];
            end_region = cum_regs_per_phase[peakPhaseIndex - 1 - mask_phase_flag];
        }
        else
        {
            start_region = cum_regs_per_phase[currentPhase_dynaplan - 1];
            end_region = cum_regs_per_phase[currentPhase_dynaplan];

        }
    }
    else
    {
        start_region = 0;
        end_region = total_acq_regions;
    }

    for ( region_index = start_region; region_index < end_region; region_index++)
    {
        if (RegionsSchedule[region_index] == 0)
        {
            startsi = 0;
            endsi = cum_views_per_region[RegionsSchedule[region_index]];
        }
        else
        {
            startsi = cum_views_per_region[RegionsSchedule[region_index]-1];
            endsi = cum_views_per_region[RegionsSchedule[region_index]];
        }

        for (si = startsi; si < endsi; si++)
        {
            /* Navigator Disco related calculation */
            if (segmented_flag)
            {
                if (zy_export[si].flags & ZY_FLAGS_SEG_START)
                {
                    pre_segment_flag = PSD_ON;
                    seg_view_indx = 0;
                }
                else
                {
                    pre_segment_flag = PSD_OFF;
                    seg_view_indx++;
                }

                if ((si == endsi - 1) || (zy_export[si+1].flags & ZY_FLAGS_SEG_START))
                {
                    post_segment_flag = PSD_ON;
                }
                else
                {
                    post_segment_flag = PSD_OFF;
                }

                if (navgate_flag && pre_segment_flag)
                {
                    result = 0;
                    if (nav_iter < nav_ss)
                    {
                        nav_active = 0;
                    }
                    else
                    {
                        nav_active = 1; /* single mode only */
                    }

                    if (RegionsSchedule[region_index] == 0) /* A region */
                    {
                        dnav_win_factor = 1.0;
                    }
                    else
                    {
                        dnav_win_factor = dnav_win_BAratio;
                    }

                    NavigatorPlayGate();

                    if (navsegment_dda != 0)
                    {
                        PlayDisdaqIntleave(navsegment_dda);
                    }

                    nav_iter++;
                }
            }

            view =  zy_export[si].view;
            slice = zy_export[si].slice;

            /* viewcount and slicecount are used to mimic the old view-slice loop
               order. They are used to determine when the sat pulses are played
               out. */

            slicecount = si % rspslq;
            viewcount = si / rspslq;

            if (debugstate==1)
            {
                sprintf(psddbgstr, "  View=%4d", view);
            }
            printdbg(psddbgstr, debugstate);

            dabview = view + 1;
            save_dabview=dabview;

            dabslice = slice;

            dabop = DABSTORE;      /* store xcvr data */

            setiamp(-viewtable[dabview], &gy1, 0);

            if (rewinder_flag)
            {
                setiamp(-viewtable[dabview], &gy1r, 0);
            }

            cntvus = 0;     /* Initialize flag for Oddnes NPW */

            for (excitation = 1; (excitation<=rspnex) && (cntvus<1); excitation++)
            {
                /* Condition to turn cntvus flag on/off */
                if ( (oddnex_npw == 1) &&
                     (excitation == (rspnex - 1)) &&
                     ((save_dabview <= (rspvus/4)) ||
                      (save_dabview > (3*rspvus/4))) )
                {
                    cntvus = 1;
                }
                else
                {
                    cntvus = 0;
                }

                if (debugstate==1)
                {
                    sprintf(psddbgstr,"    Excitation=%6d", excitation);
                }
                printdbg(psddbgstr, debugstate);

                if (slicecount == 0)
                {
                    rspsat = scansat0;      /* Initialize 1st SAT buffer */
                }

                for (inner_echo = 0; inner_echo < inter_necho; inner_echo++)
                {
                    if (medal_flag && medal_multitr_flag)
                    {
                        /* medal_echo_mode not supported, doesn't make sense for fast multiphase application */
                        if (0 == inner_echo)
                        {
                            post_dixtime = (GRAD_UPDATE_TIME + medal_pw - medal_shift1);
                            pre_dixtime = (GRAD_UPDATE_TIME + medal_shift1);
                        }
                        else
                        {
                            post_dixtime = (GRAD_UPDATE_TIME + medal_pw - medal_shift2);
                            pre_dixtime = (GRAD_UPDATE_TIME + medal_shift2);
                        }

                        setperiod(post_dixtime, &dix_ssppost, 0);
                        setperiod(pre_dixtime, &dix_xpre, 0);
                        setperiod(pre_dixtime, &dix_ssppre, 0);
                    }

                    slice = zy_export[si].slice;   
                    dabslice = slice;
                    save_dabslice = dabslice;

                    if (debugstate==1)
                    {
                        sprintf(psddbgstr, "      Slice=%6d", slice);
                    }
                    printdbg(psddbgstr, debugstate);

                    /* set amp of gzcomb and gzp for dummy rf */
                    setiamp(volumetab[save_dabslice], &gzcomb, 0);   

                    if (zrewind_flag)
                    {
                        setiamp(volumetab2[save_dabslice], &gzp, 0);
                    }

                    for (slabindex=0; slabindex<slabquant; slabindex++)
                    {
                        sp_sat_index = slabindex;
                        setfrequency(rf1_freq[slabindex],&rf1,scanrf1_inst);
                        set_echo1frequency(receive_freq1[slabindex], 0);
                        if (opetl >= 2)
                        {
                            set_echo2frequency(receive_freq2[slabindex], 0);
                        }

                        /* calculate the phase offset for the slice and view */
                        /* correct phase offset calculation */
                        yres_phase = phase_off[slabindex].ysign *
                            (((save_dabview-1) * phase_off[slabindex].yoffs + 3L*FS_PI)%FS_2PI-FS_PI);

                        /* grab the slab phase offset */
                        slab_phase = slab_off[slabindex].zsign *
                            ((save_dabslice * slab_off[slabindex].zoffs + 3L*FS_PI)%FS_2PI-FS_PI);

                        spoil();

                        if (navgate_flag && !result)
                        { 
                            /* turn data acquisition off if outside of nav acceptance window */
                            fgre_loadtreg(&ddphase, phasenum, DABOFF);
                            acq_echo1 = DABOFF;
                            if (opetl>=2)
                            {
                                acq_echo2 = DABOFF;
                            }
                        }
                        else
                        {
                            /* turn data acquisition on */
                            acq_echo1 = DABON;
                            if (opetl>=2)
                            {
                                acq_echo2 = DABON;
                            }
                        }

                        fgre_loaddab_echo1_rfhub(dabslice, dabecho, dabop,
                                dabview, acq_echo1,
                                coilInfo_tgt[slabindex].hubIndex,
                                0, PSD_LOAD_DAB_HUB);
                        if (opetl>=2)
                        {
                            fgre_loaddab_echo2(dabslice, (dabecho+1), (opetl-1), nshots, dabop, dabview, acq_echo2);
                        }

                        printdbg("      Before startseq", debugstate);

                        /* if last view of region check if need to send phase done */
                        if ( (si == (endsi-1)) &&  /* && last view */
                                (excitation == rspnex) && /* && last excitation */
                                (slabindex == (slabquant-1)) && /* && last slab */
                                (inner_echo == (dixon_necho-1)) && /* and last echo MS */
                                !(navgate_flag && !result) )
                        {
                            /* acquire last view of region */
                            startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);

                            /* turn off DAB */
                            fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, DABOFF);
                            if (opetl>=2)
                            {
                                fgre_loaddab_echo2(dabslice, (dabecho+1), (opetl-1), nshots, dabop, dabview, DABOFF);
                            }

                            /* Send any phase done packets that may be ready */                                
                            while ( (additional_phase_done_needed && (region_index == end_region - 1)) ||
                                    ((phasenum < disco_nphases) && (PhaseDoneSchedule[phasenum] <= region_index)) )
                            {
                                /* Use as Phase done packet rather than region done as in TRICKS */
                                fgre_loadtreg(&ddphase, phasenum, DABON);
                                {
                                    char tempstr[200] = "";
                                    sprintf(tempstr,"Sending remaining phase done before pause -- region_indx=%d, phasenum=%d, disco_nphases=%d\n",
                                            region_index, phasenum, disco_nphases );
                                    printdbg(tempstr,debugstate);
                                }
                                /* send phase done packet */
                                startseq((SHORT)slabindex,(SHORT)MAY_PAUSE);

                                phasenum++;
                                additional_phase_done_needed = 0;
                            }

                            /* done sending phase done packets */
                            fgre_loadtreg(&ddphase, 0 , DABOFF);

                            /* determine if need to pause */
                            if ( !opdynaplan && mask_phase_flag && pause_after_mask_flag &&
                                    (phasenum < disco_nphases) && (region_index == (num_mask_regions-1)) )
                            {
                                if (navgate_flag)
                                {
                                    hbs_left = total_acq_points / views_per_segment - nr_of_segments;
                                    setscantimeimm(pidmode,discodda*act_tr+act_navgate_tr*hbs_left/curr_eff,hbs_left,pitslice,opslicecnt);
                                }
                                else
                                {
                                    setscantimeimm(pidmode,avmintscan,piviews,pitslice,opslicecnt);
                                }
                                startseq((SHORT)slabindex,(SHORT)MUST_PAUSE);
                                PlayDisdaqIntleave(discodda);
                            }
                        }
                        else
                        {
                            startseq((SHORT)slabindex,(SHORT)MAY_PAUSE);
                        }

                        printdbg("      After startseq", debugstate);
                    } /*slabindex*/

                } /* end inner_echo loop */

                dabop = DABADD;   /* add xcvr data */

            } /* end excitation loop */

            /* make view numbers consistent */
            if (segmented_flag && post_segment_flag)
            {
                int diff_views = (views_per_segment - seg_view_indx - 1) * rspnex * inter_necho * slabquant;

                if (diff_views > 0)
                {
                    char tempstr[200] = "";
                    sprintf(tempstr, "%d Disdaq, region_index=%d\n", diff_views, region_index);
                    PlayDisdaqIntleave(diff_views);
                    printdbg(tempstr,debugstate);
                }
            }

            if (navgate_flag && post_segment_flag && !result)
            {
                /* rejecting current segment */
                char tempstr[200] = "";
                si -= (seg_view_indx + 1);
                sprintf(tempstr,"%d-view rewinding, new si=%d\n", seg_view_indx + 1, si);
                printdbg(tempstr,debugstate);
            }

        } /* end viewsperregion(si) loop*/

    } /* end region_index loop */

    /* pass packet logic */
    boffset(off_seqpass);

    /* Turn off phase done packet */
    fgre_loadtreg(&ddphase, 0 , DABOFF);

    /* Only one pass for DISCO */
    /* Set DAB pass packet to end of scan */
    setwamp(SSPD + DABPASS + DABSCAN, &pass_pulse, 2);
    printdbg("  End of Scan and Pass", debugstate);
    pause = MAY_PAUSE;
    startseq(0,(SHORT)pause);

    boffset(off_seqcore);

    printdbg("Returning from discocore", debugstate);
    return SUCCESS;
} /* End discocore */


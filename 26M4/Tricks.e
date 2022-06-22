/*
 * GEMSBG C source File
 * Copyright (C) 2003 The General Electric Company
 *
 * File Name :  Tricks.e
 *
 * Language  :  ANSI-C / EPIC
 *
 * Developers:  KasiViswanathan Agilandam 
 *              Venkat Ramanan
 *
 * Synopsis:
 *     3D Elliptic-Centric Time Resolved Imaging of Contrast KineticS 
 *     ( 3D- ECTRICKS )
 *
 * Description:
 *     This is similar to a multiphase scan but with better temporal
 *     resolution using partial k-space acquisition at each phase.
 *     Each phase is then interpolated to reconstruct the whole 
 *     k-space, then subtracted from the mask, and a MIP is produced.
 *
 * References:
 *      Time-Resolved Contrast-Enhanced 3D MR Angiography- F.R.Korosec, 
 *      R.Frayne, T.M.Grist, C.A.Mistretta - MRM 36:345-351 (1996)
 *     
*/

/*
   Do not edit anything above this line
*/

/* *********************************************************************
Author       Date         Description

Venkat     Dec,17,2003    MRIge90521: Initial Version for 12.0. Created from the 
                          code already present in 11.0-M4.

Venkat     Jan,30,2004    MRIge91178: Changes for simultaneous
                          acquisition/recon  (overlap TRICKS).

Venkat     Mar,12,2004    MRIge91727: Changes for supporting > 1024 im/ser

Venkat     May,17,2004    MRIge92801: Initialise the tricks variables with some
                          good defaults.

Venkat     July,9,2004    MRIge92819,MRIge93309: correct calculation of tricksdda

Venkat     Aug,10,2004    Increase tricks delay time to 60 sec.

Venkat     Sep,29,2004    MRIhc03442: Prevent tricksdda from being negative.

Venkat     Jun,14,2005    MRIhc07934: Implement interleaved multislab Tricks for
                          PV-Application (SWIFT).

Venkat     Jul,10,2005    MRIhc07934: Changes for coil-switching for SWIFT.

Venkat     Jul,22,2005    MRIhc08627: DABOFF for dda.

Venkat     Jul,22,2005    MRIhc08720: Fixed nuisance msg by fixing OFF.

Ikezaki    Aug,29/2005    YMSmr07536: Fixed PSD process termination
                          with large #phases.

Venkat     Nov,10,2005    MRIhc11224: Bit checking for rhtrickstype

CRM        Dec,16,2005    MRIhc11224: Use tricks_common.h for rhtrickstype bits.

CRM        Jan,10,2006    MRIhc11224: Don't allow both sub and unsubtracted
                          output option to be selected without selecting a
                          subtraction method.

CRM        Feb,07,2006    MRIhc13033: Add SwiFT support for single connector 
                          PV Coil using scn provided biasEnable and 
                          switchSelects.

CRM        Feb,22,2006    MRIhc13151: Make sure that TRICKS kernel has been
                          read successfully before starting cveval.
                          
TS        July 24, 2006   MRIhc15304: Changes for HDv related to coil switching.             

CRM        Sep,18,2006    MRIhc16278: Write new structure to communicate
                          encode order to TRICKS recon.
          
CRM        Jan, 1, 2007   MRIhc31929 - Use new loaddab function for SwiFT
                          coil switching 
 
EB/VSN/CRM Mar,12,2007    MRIhc10955: TRICKS enhancement for HD Lower Leg
                          coil to minimize eddy-current effects due to
                          inter-region jumps.

CRM & VSN  Mar,15,2007    MRIhc10955: Corrected pitres value. Removed acqs from
                          avmintscan and mask time calculations.

EB & VSN   Apr,10,2008    MRIhc35702: Enabled IB enhancement based on the opfov >= 40 

KA         Jun,18,2009    GEHmr01503: Fast coil switch support for SV.

VSN/VAK    12/31/2009     MRIhc46886: SV to DV Apps Sync Up

SW         05/19/2011     MRIhc56991: Set rhtype1 correctly when trick_flag is off 
 
*/



/* Epic preprocessor doesn't like @ipgexport -Venkat */
@host TricksIpgexport

/* Elliptic Centric TRICKS */
int totalecregions;
int mask_regions;
int kernel_regions;
int viewsperregion;
int mask_regions_min = 2;
int mask_regions_max = 8;
int kernel_regions_min = 2;
int kernel_regions_max = 16;
int tricks_minecho = 2;
int tricks_maxecho = 16;
int tricks_maxphases;
int tricks_maxseries=48;
int RegionSchedule[100];
int ectricks_mask_regions[8];
int ectricks_kernel_regions[16];
int imaxectricksview;
int tricks_index;
int tricks_index2;
int tricks_check;
float tricks_mask_time;

@host TricksGlobal
#include "tricks_common.h"
#define MASTER_RCVRS 0x0008
#define SLAVE_RCVRS 0x0004
#define ALL_RCVRS (MASTER_RCVRS|SLAVE_RCVRS)

@host TricksHostVars
int tricksReadKernelNeeded = PSD_ON;
int isboth=0;

@cv TricksCv

int tricks_flag = 0 with {0, 1, 0, INVIS, "Flag for TRICKS.",};
int tricks_stop = 0 with {0, 1, 0, INVIS, "Flag for TRICKS Hard Pause.",};
int tricks_delay = 1000ms with {0ms,60s,1000ms, INVIS, "Time for disdaqs for TRICKS after mask",};
int tricksdda;
int tricks_transition_views = 0 with {0, ,0, INVIS, "Number of views in TRICKS transition regions",};
int tricks_debug=0;

/* PV App */
int intslab_flag = 0 with {0,1,0,VIS,"Interleaved slab acquisition (SWIFT)(0=off, 1=on)",};
int dabout_length = 20 with { 0, 100, 20, VIS, "DABOUT3 length for coil bias-switch", };

int noswitch_coil = 0 with{ 0,1,0,VIS,"No coil switch (sotf)"};
int noswitch_slab = 0 with{ 0,1,0,VIS,"No slab switch (sotf)"};

int coilsw_ds = (SLAVE_RCVRS); /*(0x0008:Master,Rcv 1-8,RRF | 0x0004:Slave,Rcv 9-16,IRF)*/
int coilsw_oc = DREG;
int coilsw_data= DABOUT3; /* 0x0004 seems to work */

@host  DefVals

    if( PSD_ON == tricks_flag ){

        /* pimultislab is ON for both SWIFT/Tricks
           GraphicRx shud take care of this.
        */

        if( intslab_flag )
        {
            pimultislab = PSD_ON;
            picoilfastswitchrequired = 1;
        }
        else
        {
            pimultislab = PSD_OFF;
            picoilfastswitchrequired = 0;
        }

        avmaxnecho = tricks_maxecho;
        cvmin(optphases, 1);
        cvmax(optphases, 512);
        cvdef(optphases, 1);
        errorstring(optphases,"Temporal output phases is out of range");

        pitricksdelnub = 6;
        pitricksdelval3 = 3s;
        pitricksdelval4 = 5s;
        pitricksdelval5 = 10s;
        pitricksdelval6 = 30s;
        errorstring(optricksdel,"Tricks delay is out of range");

        /* some good defaults for mask and kernel MRIge92801*/
        mask_regions = 4;
        kernel_regions = 6;

        for( tricks_index = 0; tricks_index < mask_regions; ++tricks_index ) {
            ectricks_mask_regions[tricks_index] = tricks_index;
        }
        ectricks_kernel_regions[0] = 0;
        ectricks_kernel_regions[1] = 1;
        ectricks_kernel_regions[2] = 0;
        ectricks_kernel_regions[3] = 2;
        ectricks_kernel_regions[4] = 0;
        ectricks_kernel_regions[5] = 3;
    }
    else {
        picoilfastswitchrequired = 0; 
    }



@host ReadKernelFileCvinit

     /* ECTRICKS */
    if( PSD_ON == tricks_flag )
    {
        /* MRIhc13151: Save whether or not the TRICKS kernel read was
           successfully. If kernel read was not successfull in cvinit(), try
           again in cveval, just in case scan calls cveval() alone. */

        tricksReadKernelNeeded = PSD_ON;

        status = tricks_read_kernel_file();
        if (SUCCESS != status) 
        {
            return status;
        }

        tricksReadKernelNeeded = PSD_OFF;
    }

@host ReadKernelFileCveval
   
    /* ECTRICKS */
    if( (PSD_ON == tricks_flag)  && (PSD_ON == tricksReadKernelNeeded) )
    {
        /* MRIhc13151: Save whether or not the TRICKS kernel read was
           successfully. If kernel read was not successfull in cvinit(), try
           again in cveval, just in case scan calls cveval() alone. */

        tricksReadKernelNeeded = PSD_ON;

        status = tricks_read_kernel_file();
        if (SUCCESS != status) 
        {
            return status;
        }

        tricksReadKernelNeeded = PSD_OFF;
    }

@host GenerateSchedule

    /* ECTRICKS */
    if( tricks_flag == PSD_ON ) {
        if( exist(optrickspause) == PSD_ON ) {
            /*MRIhc08720*/
            if(optricksdel < (1s*exist(opvquant)) )
            {
                _optricksdel.fixedflag = FALSE;
                optricksdel = 1s*exist(opvquant);
            }
            cvdef(optricksdel, 1s*exist(opvquant));
            cvmin(optricksdel,1s*exist(opvquant));
            avmintricksdel = 1s*exist(opvquant);
            tricks_stop = PSD_ON;
        } else {
            cvmin(optricksdel,0s);
            avmintricksdel = 0s;
            tricks_stop = PSD_OFF;
        }
        avmaxtricksdel = 60s;
        cvmax(optricksdel,60s);

        /* YMSmr07536  08/29/2005 YI  moved here to avoid PSD process termination */
        /* The maximum number of images per scan is DAT_ACQ_MAX,
           including overlap and kissoff slices. */
        if( existcv(optphases) && (exist(optphases) > avmaxtphases) ) {
            epic_error( use_ermes,
                        "The number of phases must be decreased to %d.",
                        EM_PSD_NUM_PASS_OUT_OF_RANGE, EE_ARGS(1),
                        INT_ARG, avmaxtphases );
            return FAILURE;
        }

        for( tricks_index = 0; tricks_index < kernel_regions; ++tricks_index ) {
            tricks_check = 0;
            for( tricks_index2 = 0; tricks_index2 < mask_regions; ++tricks_index2 ) {
                if( ectricks_kernel_regions[tricks_index] == ectricks_mask_regions[tricks_index2] ) {
                    tricks_check = 1;
                }
            }
            if( tricks_check == 0 ) {
                epic_error( use_ermes,
                            "%s is incompatible with %s.",
                            EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                            STRING_ARG, "Kernel_Regions",
                            STRING_ARG, "Mask_Regions" );
                return FAILURE;
            }
        }

        /* Check for optphases Advisory....total images exceeding is caught later */
        /* tempmaxtphases is less 1 to accomodate for mask acquistion */
        /* take the minimum of the 2 namely tricks_maxphases and tempmaxtphases */
        /*
         * 1024 im/ser -Venkat
        */

        viewsperregion = ((slquant1*(rhhnover+rhnframes))/mask_regions);

        tricks_index = ((int)((float)((float)(exist(optphases)-1)/(float)mask_regions)+0.99)+2);
        cvmax(opnecho, tricks_index);
        cvdef(opnecho, tricks_index);
        cvoverride(opnecho, tricks_index, PSD_FIX_ON, PSD_EXIST_ON);

        totalecregions = exist(opnecho) * mask_regions;
        /* pull down for phases dynamically done here */
        tricks_index = (((avmaxtphases-1)/mask_regions)+1);
        if( tricks_index < 7 ){
            pitphasenub = tricks_index;
        }else{
            pitphasenub = 6;
        }

        /* filling this as 3-different segments for better understanding */
        for( tricks_index = 0; tricks_index < mask_regions; ++tricks_index ) {
            RegionSchedule[tricks_index] = ectricks_mask_regions[tricks_index];
        }

        if( exist(opnecho) > tricks_minecho ) {
            for( tricks_index = mask_regions; tricks_index < (exist(opnecho) - 1) * mask_regions; ++tricks_index ) {
                tricks_index2 = (tricks_index-mask_regions)%kernel_regions;
                RegionSchedule[tricks_index] = ectricks_kernel_regions[tricks_index2];
            }
        }

        for( tricks_index = 0; tricks_index < mask_regions; ++tricks_index ) {
            tricks_index2 = ((exist(opnecho) - 1) * mask_regions) + tricks_index;
            RegionSchedule[tricks_index2] = ectricks_mask_regions[tricks_index];
        }
        /* set the phases pull down depending on the mask_regions */
        pitphaseval2 = (mask_regions)+1;
        pitphaseval3 = (mask_regions*2)+1;
        pitphaseval4 = (mask_regions*3)+1;
        pitphaseval5 = (mask_regions*4)+1;
        pitphaseval6 = (mask_regions*5)+1;

        pitricksdelnub = 6;
        pitricksdelval3 = 3s;
        pitricksdelval4 = 5s;
        pitricksdelval5 = 10s;
        pitricksdelval6 = 30s;

        tricks_delay = exist(optricksdel);
    } 
    /* END ECTRICKS */



@host PhaseorderFlag

        if( PSD_ON  == tricks_flag ) {
            /* MRIhc10955: For HD Lower Leg coil, enable enhancement to
               minimize the eddy-current effect due to inter-regional jump */

            int enable_tricks_transition;
           
            /* MRIhc35702 - Enabling tricks transition based on FOV */
            if(exist(opfov) >= 400) {
                enable_tricks_transition = 1;
            }
            else
            {
                enable_tricks_transition = 0;
            }

            if (enable_tricks_transition) {
                tricks_transition_views = 24;
            } else {
                tricks_transition_views = 0;
            }

            /* Run Elliptic TRICKS as default */
            ellipt_flag = 1;
        }



@host SetSeqtype

     /* ECTRICKS */
    if( PSD_ON == tricks_flag ) {
        seq_type = TYPF3D;
    }



@host Rheval

    if( tricks_flag == PSD_ON ) {
        rhnecho = 1;

        rhvtype = VASCULAR+COLLAPSE_Z;  
        /* MRIge82977 : Initialise vas_ovrhd for TRICKS-Venkat*/
        vas_ovrhd = rhimsize*rhimsize*4;

        /* why do we need this? revisit -Venkat */
        pinexnub = 1 + 2 + 4 + 8;
        pinexval2 = 0.5;
        pinexval3 = 0.75;
        pinexval4 = 1;

        tricksdda = (int)(((float)tricks_delay/1s)*dda_one_second);

        tricksdda = tricksdda/exist(opvquant);

        if (tricksdda < 0)
        {
            tricksdda = 0;
        }

        /* Initialize rh CVs for use in maxslquanttps during cveval */
        rhectricks_num_regions = mask_regions;
        rhectricks_input_regions = totalecregions;

        isboth = (rhtrickstype & TRICKS_BOTH_SUB_AND_UNSUB) ? 1 : 0;

        rhnpasses = exist(opvquant)*(exist(optphases) + 1) +
                    (isboth ? exist(optphases)*exist(opvquant):0);
        rhnslices = exist(opslquant)*rhnpasses;

    }



@host Setacqs

    if( tricks_flag == PSD_ON ) {
        acqs = 1;
    }

@host ScanTime

    /* EC TRICKS overwrite the time */ /* MRIhc10955 */
    if( PSD_ON == tricks_flag ) {
        avmintscan = (float)act_tr * acqs * opvquant * (( sat_dda + baseline) +
                                             (int)( (float)(exist(opslquant)*(truenex + (float)dex) + 2*num_sats) *
                                                    (float)(rhnframes+rhhnover) ) * (exist(opnecho)-1) )
            + passtime + act_tr*acqs*tricksdda*opvquant;
        tricks_mask_time = (float)((gating == TRIG_INTERN) ? act_tr : (act_tr + TR_SLOP))
            * acqs * opvquant * ( (dda+ slice_dda*exist(opslquant) + sat_dda + baseline) +
                       (int)( (float)(exist(opslquant)*(truenex + (float)dex) + 2*num_sats) *
                              (float)(rhnframes+rhhnover) ) );
        pimscan = tricks_mask_time;
        pitres  = (avmintscan - tricks_delay - passtime)/(totalecregions-mask_regions);
        imaxectricksview  = (rhnframes+rhhnover);
    }

@host TricksCheck
    /*
     * ECTRICKS and SWIFT checks
     */
    if( PSD_ON == tricks_flag ) {
        if( existcv(optricksdel) && ((exist(optricksdel) > avmaxtricksdel) 
                    || (exist(optricksdel) < avmintricksdel)) ) {
            epic_error( use_ermes,
                        "%s is out of range.",
                        EM_PSD_CV_OUT_OF_RANGE, EE_ARGS(1),
                        STRING_ARG, "Tricks delay time" );
            return FAILURE;
        }

        if( existcv(opnecho) && (exist(opnecho) > avmaxnecho) ) {
            epic_error( use_ermes,
                        "The number of phases must be decreased to %d.",
                        EM_PSD_NUM_PASS_OUT_OF_RANGE, EE_ARGS(1),
                        INT_ARG, avmaxtphases );
            return FAILURE;
        }
        if( existcv(opt2prep) && (PSD_ON == exist(opt2prep)) ) {
            epic_error( use_ermes,
                        "%s is incompatible with %s.",
                        EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                        STRING_ARG, "ECTRICKS",
                        STRING_ARG, "T2Prep" );
            return FAILURE;
        }
        if( existcv(oprtcgate) && (PSD_ON == exist(oprtcgate)) ) {
            epic_error( use_ermes,
                        "%s is incompatible with %s.",
                        EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                        STRING_ARG, "ECTRICKS",
                        STRING_ARG, "Respiratory Gating" );
            return FAILURE;
        }
        if( existcv(opcgate) && (PSD_ON == exist(opcgate)) ) {
            epic_error( use_ermes,
                        "%s is incompatible with %s.",
                        EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                        STRING_ARG, "ECTRICKS",
                        STRING_ARG, "Cardiac Gating" );
            return FAILURE;
        }
        if( existcv(opvquant) && (exist(opvquant) >= 2) && (intslab_flag ==
                    PSD_OFF) ) {
            epic_error( use_ermes,
                        "%s is incompatible with %s.",
                        EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                        STRING_ARG, "ECTRICKS",
                        STRING_ARG, "2 or more slabs" );
            return FAILURE;
        }
        if( existcv(opmultistation) && (PSD_ON == exist(opmultistation)) ) {
            epic_error( use_ermes,
                        "%s is incompatible with %s.",
                        EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                        STRING_ARG, "ECTRICKS",
                        STRING_ARG, "MultiSation" );
            return FAILURE;
        }
        if( existcv(opfluorotrigger) && (PSD_ON == exist(opfluorotrigger)) ) {
            epic_error( use_ermes,
                        "%s is incompatible with %s.",
                        EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                        STRING_ARG, "ECTRICKS",
                        STRING_ARG, "Fluoro Trigger" );
            return FAILURE;
        }
        if( PSD_ON == specir_flag ) {
            epic_error( use_ermes,
                        "%s is incompatible with %s.",
                        EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                        STRING_ARG, "ECTRICKS",
                        STRING_ARG, "SPECIAL" );
            return FAILURE;
        }
        if( PSD_ON == smartprep_flag ) {
            epic_error( use_ermes,
                        "%s is incompatible with %s.",
                        EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                        STRING_ARG, "ECTRICKS",
                        STRING_ARG, "SmartPrep" );
            return FAILURE;
        }
        if( existcv(opnopwrap) && (PSD_ON == exist(opnopwrap)) ) {
            epic_error( use_ermes,
                        "%s is incompatible with %s.",
                        EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                        STRING_ARG, "ECTRICKS",
                        STRING_ARG, "No Phase Wrap" );
            return FAILURE;
        }
        if( existcv(opmph) && (PSD_ON == exist(opmph)) ) {
            epic_error( use_ermes,
                        "%s is incompatible with %s.",
                        EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                        STRING_ARG, "ECTRICKS",
                        STRING_ARG, "Multi Phase imaging option" );
            return FAILURE;
        }

        /* YMSmr09105  05/09/2006 YI */
        if( (exist(opnex) > 1) && existcv(opnex) ){
            epic_error( use_ermes, "The selected number of excitations is not valid for the current prescription.", EM_PSD_NEX_OUT_OF_RANGE, EE_ARGS(0) );
            avmaxnex = 1;
            return ADVISORY_FAILURE;
        }
    }
    /* end ECTRICKS */



@host TricksPredownload

    if (intslab_flag && tricks_flag && (opvquant > 1))
    {
        int midslice1=0;
        int midslice2=0;

        midslice1 = opslquant/2;
        midslice2 = midslice1 + opslquant;

        if(tricks_debug)
        {
            printf("mid1=%d, mid2=%d\n",midslice1, midslice2);
        }

        /* Right of the patient always get higher tloc
         * And, the first slab should be on the left.
         * --Venkat */
        if ( scan_info[midslice1].optloc > scan_info[midslice2].optloc )
        {
            epic_warning("Pl. make sure that the first slab is"
                         " on the left of the patient");
            /*
            epic_error( 0,"Pl. make sure that the first slab is prescribed"
                         " on the right of the patient",0,0);

            return FAILURE;
             */
        }

        for (i = 0; i < opslquant * opvquant; i++) {

            if( i >= (opslquant*opvquant)/2 )
            {
                if( noswitch_slab )
                {
                    data_acq_order[i].slloc = data_acq_order[i%opslquant].slloc;
                }
            }

        }

    }

    if(PSD_ON == tricks_flag) 
    {
        if(intslab_flag)
        {
            rhnumCoilConfigs = opncoils;
            rhswiftenable = 3;
        }
        else
        {
            rhnumCoilConfigs = 1;
            rhswiftenable = 0;
        }
    }
    else
    {
        /* Set to default values if using TRICKS/SwiFT series to
           create another efgre3d based protocol */
        rhnumCoilConfigs = 0;
        rhswiftenable = 0;
    }

    if( PSD_ON == tricks_flag )
    {
        int tricks_transition_delay = 0;

        if(intslab_flag)
        {
            ihtr *= 2;
        }

        /* Check validity of rhtrickstype
           (1) Only one subtraction technique specified
           (2) Read and generate rawdata are not specified at the same time 
           (3) A subtraction type must be selected if recon both selected */
        if( ((rhtrickstype & TRICKS_KSPACE_SUBTRACT) &&
             (rhtrickstype & TRICKS_MAGNITUDE_IMAGE_SUBTRACT)) ||
            ((rhtrickstype & TRICKS_KSPACE_SUBTRACT) &&
             (rhtrickstype & TRICKS_COMPLEX_IMAGE_SUBTRACT)) ||
            ((rhtrickstype & TRICKS_MAGNITUDE_IMAGE_SUBTRACT) &&
             (rhtrickstype & TRICKS_COMPLEX_IMAGE_SUBTRACT)) ||
            ((rhtrickstype & TRICKS_TYPE_GENERATE_RAWDATA) &&
             (rhtrickstype & TRICKS_TYPE_READ_RAWDATA)) || 
            ((rhtrickstype & TRICKS_BOTH_SUB_AND_UNSUB) && 
             !((rhtrickstype & TRICKS_KSPACE_SUBTRACT) ||
             (rhtrickstype & TRICKS_MAGNITUDE_IMAGE_SUBTRACT) ||
             (rhtrickstype & TRICKS_COMPLEX_IMAGE_SUBTRACT))) )
        {
            epic_error( use_ermes, "%s is out of range",
             EM_PSD_CV_OUT_OF_RANGE, 1, STRING_ARG, "rhtrickstype");
            return FAILURE;
        }
        
        isboth = (rhtrickstype & TRICKS_BOTH_SUB_AND_UNSUB) ? 1 : 0;

        /* irrespective of whether we use pvapp set rhnumslabs*/
        rhnumslabs = exist(opvquant);

        rhnpasses = exist(opvquant)*(exist(optphases) + 1) + 
                    (isboth ? exist(optphases)*exist(opvquant):0);
        rhnslices = exist(opslquant)*rhnpasses;

        pinecho = 1;
        setexist(pinecho,1);
        rhtype1 |= (RHTYP3DM | RHTYPECTRICKS);
 
        if (pfkz_flag || pfkr_flag || (ACCEL_ARC == rhasset))
        {
            rhtype1 |= RHTYP1BAM0FILL;
        }

        /* ECTRICKS Fill Zero for Mask and tricks_delay for First Phase */
        free(ihtdeltab);
        /* 1024 Venkat
        */
        ihtdeltab = (int *)malloc(opslquant*opvquant*slicezp*sizeof(int));
        exportaddr(ihtdeltab, (int)(opslquant*opvquant*slicezp*sizeof(int)));

        /* MRIhc10955: Account for transition delay in ihdeltab */
        tricks_transition_delay = (tricks_transition_views * act_tr * opvquant);

        /* fill in the values for the 2nd post contrast phase */
        for (i = 0; i < opvquant*opslquant; i++) 
        {
            ihtdeltab[i*slicezp] = tricks_delay + tricks_transition_delay +
                ( ((float)((opvquant*opslquant)/mask_regions))*(act_tr*(rhhnover+rhnframes)) );

            for (j=1;j<slicezp;j++) 
            {
                ihtdeltab[i*slicezp+j] = ihtdeltab[i*slicezp];
            } /* j */
        } /* i */
    }
    else
    { 
        rhtype1 &= ~RHTYPECTRICKS;
    }

    /* > 1024 im/ser -Venkat*/
    if ( (tricks_flag)==PSD_ON)
    {
        rhformat |= RHF_SINGLE_PHASE_INFO;
        rhmphasetype = 0;               /* Not sequential multiphase*/
        rhnphases = (isboth+1)*exist(optphases) + 1; /* No of phases in a multiphase scan*/

        rhrawsize = (n64)opvquant * rhrawsize;
    }


@host TricksEntrytab
    {
        if (PSD_ON == intslab_flag)
        {
            /* Automatically disable coil switching if transmit coils don't match */
            int txIndexPri = coilInfo[0].txIndexPri;
            int txIndexSec = coilInfo[0].txIndexSec;
            noswitch_coil = 0;

            for (i=1; i < opncoils; i++)
            {
                if ((coilInfo[i].txIndexPri != txIndexPri) || 
                    (coilInfo[i].txIndexSec != txIndexSec))
                {
                    noswitch_coil = 1;
                    printf("Tx coils do not match for all SwiFT coil configuration.  Disabling switching!\n");
                }
            }

            noswitch_coil_psc = noswitch_coil;

            if ( tricks_debug ) 
            {
                printf("noswitch_coil=%d\n", noswitch_coil);
            }
        }

        if( intslab_flag && (COIL_SWITCH_DABOUT_DM & cfcoilswitchmethod) )
        {
            /* When using the driver module to do coil switching, tell the
             * driver module which hub index to use for the secondary
             * coil */
            entry_point_table[L_SCAN].epGeneralBankIndex2 = (n8)coilInfo[1].hubIndex;
        }
        else
        {
            /* Default to make second index match first */
            entry_point_table[L_SCAN].epGeneralBankIndex2 = entry_point_table[L_SCAN].epGeneralBankIndex;
        }
    }

@pg TricksPgvars
INT coilsw_length = 4;
short coilsw[4]={ SSPDS , SSPOC|DREG, SSPD, SSPDS };

@rspvar TricksRspvars

/*TRICKS testing for overlap-Venkat*/
/* Declare everything here than in EpicConf() since TREG_bits
 * is not recognized by pgen_on_host -Venkat */
short TREG_length=TREG_LENGTH;
short TREG_bits[TREG_LENGTH];
int  TREG_start=0;
int tf=0;
int save_dabview,save_dabslice;
/*End TRICKS*/

@pg TricksRegPkt

    /*testing for overlap TRICKS-Venkat*/
    if(tricks_flag == PSD_ON)
    {
        /*initialize the bits array. Better here than in sspinit()*/

        TREG_bits[0] = SSPDS + DABDC;
        TREG_bits[1] = SSPOC + DTREGOC;
        TREG_bits[2] = SSPD;
        TREG_bits[3] = SSPD;
        TREG_bits[4] = 0;
        SSPPACKET(dtreg,PosReadoutWindow+TREG_start+DIM_length-XTRSETLNG,TREG_length,TREG_bits,0);
        dtreg.tag=SSPTREG;
    }

    /*coil switch --Venkat */
    /* Switch on DABOUT3 for sometime (dabout_length)
     * near the end of rcv --Venkat
     */
    if(tricks_flag && intslab_flag && (COIL_SWITCH_DABOUT_DM & cfcoilswitchmethod))
    {
                                                                                                       
        coilsw[0]= ( SSPDS | (short)coilsw_ds );
        coilsw[1]= ( SSPOC | (short)coilsw_oc );
                                                                                                       
        coilsw[2]=  SSPD ;
                                                                                                       
        if( tricks_debug )
        {
            printf("0=%i, 1=%i,2=%i,3=%i\n",
                    coilsw[0],coilsw[1],coilsw[2],coilsw[3]);
        }
                                                                                                       
        /* switch on */
        SSPPACKET(coilsw_on,
                pendallssp(echo1rba, 0) + pw_gxw-coilsw_length-dabout_length,
                coilsw_length, coilsw,0);
                                                                                                       
        /* switch off */
        coilsw[2]=SSPD;
        SSPPACKET(coilsw_off,
                pendallssp(echo1rba, 0) + pw_gxw-coilsw_length,
                coilsw_length, coilsw,0);
                                                                                                       
    }
 
@pg TricksRegPassPkt

    /* testing for overlap TRICKS -venkat*/
    if(tricks_flag == PSD_ON)
    {
        SSPPACKET(dtregpass,PosTemp+TREG_start+DIM_length,TREG_length,TREG_bits,0);
        dtregpass.tag=SSPTREG;
    }
 
@pg WriteZYexport
/* Tricks.e WriteZYexport */

    if( PSD_ON == tricks_flag )
    {
        if( FAILURE == tricksWriteReconFiles( RegionSchedule, totalecregions,
                                              mask_regions, zy_export,
                                              (rhnframes+rhhnover) * opslquant) )
        {
            return FAILURE;
        }
    }

@rsp TricksCore

int switch_right = 0;
int switch_left = 0;

STATUS
ectrickscore( void )
{
    char psddbgstr[256] = "";
    int cntvus;     /* Flag for collecting central views in Oddnes NPW case */
    int rspsat=0;   /* Counter for deciding after which slices SAT plays    */
    int si;  /* Superindex for elliptical-centric*/
    int si_inc;  /* DCZ: Superindex increment step size */
    int slice_index; /* DCZ */
    int slice_num; /* DCZ: number of slices within slice_index loop */

    int tot_view_indx = 0;           /* Tricks One Pass Looping Index */
    int region_index = 0;
    int reg_view_indx;
    int slab_num=0;
    LONG ctrlmask =0;

    printdbg("Starting ectrickscore", debugstate);

    setmask_clock();
    slabindex = 0;
    phaseindex = 0;

    /* No multi-phase and Multi-slab is allowed for ECTRICKS....those
       loops are deleted. */

    pass = slabindex + phaseindex*slabquant; /* 3d oblique - latha@mr */

    view =  zy_export[0].view;
    slice = zy_export[0].slice;

    dabview = view + 1;

    dabslice = slice;
    setfrequency(rf1_freq[slabindex],&rf1,scanrf1_inst);
    setfrequency(receive_freq1[slabindex],&echo1,0);


    setiamp(volumetab[dabslice], &gzcomb, 0);

    if (zrewind_flag) {
        setiamp(volumetab2[dabslice], &gzp, 0);
    }

    acq_echo1 = DABOFF;

    setiamp(-viewtable[dabview], &gy1, 0);

    if (rewinder_flag) {
        setiamp(-viewtable[dabview], &gy1r, 0);
    }

    fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);
    load3d(&d3d, 0, DABOFF);

    /* Initialize yres_phase and slab_phase to zero */
    yres_phase = 0;
    slab_phase = 0;
    

    /* PV app Venkat*/
    if (!intslab_flag)
    {
        slabquant = 1;
    }

    if(intslab_flag && (COIL_SWITCH_DABOUT_DM & cfcoilswitchmethod))
    {
        if(noswitch_coil)
        {
            printf("nosw\n");
            setwamp(SSPD, &coilsw_on, 2);
        }
        else
        {
            setwamp(SSPD+coilsw_data, &coilsw_on, 2);
        }
    }

    /* collect disdaq views */
    fgre_loadtreg(&dtreg, region_index, DABOFF);
    PlayDisdaqIntleave(dda);
    
    /* slice_dda is always 0 for non-specir scans
     * Just to make sure -Venkat*/
    slice_dda = 0;

    /* no baselines are collected in fgre3D */

    /* replace view and slice loop with single "superindex" loop.  This
       enables the elliptical centric case, but is used for standard looping also
       to avoid "if" statements. zy_export is loaded in predownload. */

    si_inc = 1;       /* DCZ */
    slice_num = 1;

    for ( region_index = 0; region_index < totalecregions; region_index++) {

        reg_view_indx=0;

        for (si = RegionSchedule[region_index] * viewsperregion;
             si < (RegionSchedule[region_index] + 1) * viewsperregion;
             si++) {
            reg_view_indx=reg_view_indx+1;
            if( (region_index == mask_regions) && (reg_view_indx == 1) ){
                setscantimemanual();
                setscantimestop();
                setscantimeimm(pidmode,pitscan,piviews,pitslice,opslicecnt); 
                setscantimeauto();
                setscantimestart();
            }


            view =  zy_export[si].view;
            slice = zy_export[si].slice;
            if (view <= imaxectricksview) {

                /* viewcount and slicecount are used to mimic the old view-slice loop
                   order. They are used to determine when the sat pulses are played
                   out. */

                slicecount = si % rspslq;
                viewcount = si / rspslq;

                if (debugstate==1) {
                    sprintf(psddbgstr, "  View=%6d", view);
                }
                printdbg(psddbgstr, debugstate);

                dabview = view + 1;
                save_dabview=dabview;

                dabslice = slice;

                dabop = DABSTORE;      /* store xcvr data */

                setiamp(-viewtable[dabview], &gy1, 0);

                if (rewinder_flag) {
                    setiamp(-viewtable[dabview], &gy1r, 0);
                }
                /* Set flag to determine when respiratory gating should be enabled */
                if (slicecount == 0) {
                    first_slice = PSD_ON;
                } else {
                    first_slice = PSD_OFF;
                }


                cntvus = 0;     /* Initialize flag for Oddnes NPW */


                for (excitation = 1; (excitation<=rspnex) && (cntvus<1); excitation++) {

                    /* Condition to turn cntvus flag on/off */
                    if ( (oddnex_npw == 1) &&
                         (excitation == (rspnex - 1)) &&
                         ((save_dabview <= (rspvus/4)) ||
                          (save_dabview > (3*rspvus/4))) ) {
                        cntvus = 1;
                    } else {
                        cntvus = 0;
                    }

                    if (debugstate==1) {
                        sprintf(psddbgstr,"    Excitation=%6d",
                                excitation);
                    }
                    printdbg(psddbgstr, debugstate);

                    if (slicecount == 0) {
                        rspsat = scansat0;      /* Initialize 1st SAT buffer */
                    }


                    for (slice_index = 0; slice_index < slice_num; slice_index ++) {

                        slice = zy_export[si+slice_index].slice;   /* DCZ */
                        dabslice = slice;
                        save_dabslice = dabslice;

                        if (debugstate==1) {
                            sprintf(psddbgstr, "      Slice=%6d", slice);
                        }
                        printdbg(psddbgstr, debugstate);

                        /* set amp of gzcomb and gzp for dummy rf */
                        setiamp(volumetab[save_dabslice], &gzcomb, 0);   /* DCZ */

                        if (zrewind_flag) {
                            setiamp(volumetab2[save_dabslice], &gzp, 0);
                        }

                        if (debugstate==1) {
                            sprintf(psddbgstr, "      Slice=%6d", slice);
                        }
                        printdbg(psddbgstr, debugstate);

                        for (slabindex=0; slabindex<slabquant; slabindex++) {

                            if (PSD_OFF == noswitch_slab)
                            {
                                slab_num = slabindex;
                            }
                            else
                            {
                                slab_num = 0;
                            }

                            if (PSD_OFF == noswitch_coil)
                            {
                                ctrlmask = PSD_LOAD_DAB_HUB;
                            }
                            else
                            {
                                ctrlmask = 0;
                            }
 
                            sp_sat_index = slab_num;
                            setfrequency(rf1_freq[slab_num],&rf1,scanrf1_inst);
                            setfrequency(receive_freq1[slab_num],&echo1,0);

                            /* calculate the phase offset for the slice and view */
                            /* correct phase offset calculation MRIge82896-Venkat*/
                            yres_phase = phase_off[slab_num].ysign *
                                (((save_dabview-1) * phase_off[slab_num].yoffs +
                                  3L*FS_PI)%FS_2PI-FS_PI);

                            /* grab the slab phase offset */
                            slab_phase = slab_off[slab_num].zsign *
                                ((save_dabslice * slab_off[slab_num].zoffs +
                                  3L*FS_PI)%FS_2PI-FS_PI);

                            spoil();

                            /* Do some tricks to fool the recon.  */
                            /* Add 1 to dabview to prevent nex-table error
                             * MRIge82414-Venkat */
                            dabview  = (tot_view_indx % (rhnframes+rhhnover)) + 1;
                            dabecho  = (tot_view_indx / (rhnframes+rhhnover)) % rhnecho;
                            dabslice = (slabindex*rspslq) + 
                                (tot_view_indx / ((rhnframes+rhhnover) * rhnecho));

                            /* turn data acquisition on */
                            acq_echo1 = DABON;
                            
                            /* MRIhc18005: Switch the coil if ctrlmask
                             * is set to PSD_LOAD_DAB_HUB */
                            fgre_loaddab_echo1_rfhub(dabslice, dabecho, dabop,
                                                     dabview, acq_echo1,
                                                     coilInfo_tgt[slabindex].hubIndex,
                                                     0, ctrlmask);

                            /*
                             * For DABOUT fast coil switching set the
                             * appropriate bits in the filter select
                             * packet to inform the DRF & acquisition that
                             * the hub index is switching
                             */ 
                            if( intslab_flag && (PSD_OFF == noswitch_coil) &&
                                ( COIL_SWITCH_FILTER_SELECT_HUB_INDEX & cfcoilswitchmethod ) )
                            {
                                int dabhubmask = DABOUTHUBINDEX_NOSWITCH;

                                if( 0 == slabindex )
                                {
                                    dabhubmask = DABOUTHUBINDEX_PRIMARY ; 
                                }
                                else if( 1 == slabindex )
                                {
                                    dabhubmask = DABOUTHUBINDEX_SECONDARY;
                                }

                                setdaboutcoilswitchhubindex(&echo1, dabhubmask, cfcoilswitchmethod);

                            }


                            /*Testing for overlap -Venkat*/

                            if( ((tot_view_indx % viewsperregion) == 0) && ( tot_view_indx != 0) && 
                                    (excitation == 1) && (slabindex == slabquant-1) )
                            {
                                tf=DABON;
                                fgre_loadtreg(&dtreg, region_index, tf);
                                {
                                    char tempstr[200] = "";
                                    sprintf(tempstr,"Region number %d over-- reg_view_indx=%d, tot_view_indx=%d tf=%s\n",
                                            region_index, reg_view_indx, tot_view_indx,((tf == DABON)? "DABON" : "DABOFF") );
                                    printdbg(tempstr,tricks_debug);
                                }

                            }
                            else
                            {

                                tf=DABOFF;
                                fgre_loadtreg(&dtreg, 0 , tf);
                            }


                            printdbg("      Before startseq", debugstate);


                            if( (region_index == mask_regions) && (reg_view_indx == 1) && (excitation == 1) 
                                    && (tricksdda != 0 ) && (slabindex == (slabquant-1)) )
                            {
                                if( tricks_stop == 1)
                                {
                                    startseq((SHORT)slab_num,(SHORT)MUST_PAUSE);
                                    tf=DABOFF;
                                    fgre_loadtreg(&dtreg, 0 , tf);
#ifdef PSD_HW
                                    {
                                        char tempstr[200] = "";
                                        sprintf(tempstr,"stop = 1, reg_view_indx=%d, tot_view_indx=%d tf=%s\n",
                                                reg_view_indx, tot_view_indx,((tf == DABON)? "DABON" : "DABOFF") );
                                        printdbg(tempstr,tricks_debug);
                                    }
#endif
                                    if( tricksdda > 0)
                                        PlayDisdaqIntleave(tricksdda);
                                }
                                else if (tricks_stop == 0)
                                {
                                    startseq((SHORT)slab_num,(SHORT)MAY_PAUSE);
                                    tf=DABOFF;
                                    fgre_loadtreg(&dtreg, 0 , tf);
#ifdef PSD_HW
                                    {
                                        char tempstr[200] = "";
                                        sprintf(tempstr,"stop = 0, reg_view_indx=%d, tot_view_indx=%d tf=%s\n",
                                                reg_view_indx, tot_view_indx,((tf == DABON)? "DABON" : "DABOFF") );
                                        printdbg(tempstr,tricks_debug);
                                    }
#endif
                                    if( tricksdda > 0)
                                        PlayDisdaqIntleave(tricksdda);
                                }
                                else
                                {
                                    /*should not enter here*/
#ifdef PSD_HW
                                    printdbg(" INVALID value for tricks_stop! ", tricks_debug);
#endif
                                    startseq((SHORT)slab_num,(SHORT)MAY_PAUSE);
                                }
                            }
                            else
                            {
                                startseq((SHORT)slab_num,(SHORT)MAY_PAUSE);
                            }
                            printdbg("      After startseq", debugstate);
                        } /*slabindex*/

                    } /* DCZ: end of slice_index loop */

                    dabop = DABADD;      /* add xcvr data */

                } /* end excitation loop */

            } /* if view <= imaxectricksview */
            tot_view_indx++;

        } /* end viewsperregion loop*/
    } /* end region_index loop */

    /* Send the remaining 3D packets. */

    /* pass packet logic */
    boffset(off_seqpass);

    load3d(&d3dpass, 0, DABOFF);

    if(pass == (acqs-1)) {
        /* Set DAB pass packet to end of scan */
        setwamp(SSPD + DABPASS + DABSCAN, &pass_pulse, 2);
        printdbg("  End of Scan and Pass", debugstate);

        pause = MAY_PAUSE;
    } else {

        /* Set DAB pass packet to end of pass */
        setwamp(SSPD + DABPASS, &pass_pulse, 2);
        printdbg("  End of Pass", debugstate);

        if (((pass+1) % slicecnt)==0) {
            pause = MUST_PAUSE;     /* pause if desired */
        } else {
            pause = AUTO_PAUSE;     /* or if required */
        }
    }

    /* testing for overlap -Venkat*/
    if( ((tot_view_indx % viewsperregion) == 0) && ( tot_view_indx != 0) )
    {
        if( tricks_debug )
        {
            char tempstr[200] = "";
            sprintf(tempstr,"For Venkat: Tricks last_reg_packet=%d\n", region_index);
            printdbg(tempstr,tricks_debug);
        }

        tf=DABON;
        fgre_loadtreg( &dtregpass, region_index, tf);
    }


    startseq(0,(SHORT)pause);

    boffset(off_seqcore);



    printdbg("Returning from ectrickscore", debugstate);
    return SUCCESS;
} /* End ectrickscore */

/* set the appropriate bits in the bits pulse 
   testing for overlap -venkat*/
STATUS
fgre_loadtreg( WF_PULSE_ADDR pulse, LONG view,
                TYPDAB_PACKETS acqon_flag )
{
    short acqbits=0;

   /* Add the parameters to the Tricks REGion packet */

   if (acqon_flag == DABON)
      acqbits = DABDC;
   else 
      acqbits = 0;

   sspload(&acqbits, pulse, 0, 1, (HW_DIRECTION)TOHARDWARE, (SSP_S_ATTRIB)SSPS1);
   
   /* Move the view bits to hardware */
   sspextload(&view, pulse, 2, 1, (HW_DIRECTION)TOHARDWARE, (SSP_S_ATTRIB)SSPS2);

   return SUCCESS;
}

/********************** PlayDisdaqIntleave ROUTINE ************************/
STATUS PlayDisdaqIntleave(int NumDisdaqs)
{
    int ndisdaq;

    int dview=0;
    int dslice=0;
    int idx_slab=0;
    int i=0;

    dview =  zy_export[0].view + 1;
    dslice = zy_export[0].slice;

    /* Play gradients during disdaqs*/
    setiamp(-viewtable[dview], &gy1, 0);

    if (rewinder_flag) {
        setiamp(-viewtable[dview], &gy1r, 0);
    }

    setiamp(volumetab[dslice], &gzcomb, 0);

    if (zrewind_flag) {
        setiamp(volumetab2[dslice], &gzp, 0);
    }



    /* Make sure sequence is played with echo1 and d3d dab packets
       turned off ( Make sure again.MRIhc08627)*/
    load3d(&d3d, view-1, DABOFF);
    fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, DABOFF);
    if (opetl>=2)
    {
        fgre_loaddab_echo2(dabslice, (dabecho+1), (opetl-1), nshots, dabop, dabview, DABOFF);
    }

    if(tricks_debug)
    {
        for( i=0;i<slabquant;i++)
        {
            {
                char tempstr[200] = "";
                sprintf(tempstr,"NumDisdaqs=%d,rf1_freq[%d]=%d, receive_freq1[%d]=%d\n",
                        NumDisdaqs,i,rf1_freq[i],i,receive_freq1[i]);
                printdbg(tempstr,tricks_debug);
            }

        }
    }

    printdbg("st\n", tricks_debug);
    for (ndisdaq = 0; ndisdaq< NumDisdaqs; ndisdaq++)
    {
        for (idx_slab = 0; idx_slab < slabquant; idx_slab++) {
            sp_sat_index = idx_slab;
            setfrequency(rf1_freq[idx_slab],&rf1,scanrf1_inst);
            setfrequency(receive_freq1[idx_slab],&echo1,0);

            spoil();

            if(ndisdaq==0)
            {
                char tempstr[200] = "";
                sprintf(tempstr,"inside disdaq, idx_slab=%d ",idx_slab);
                printdbg(tempstr,tricks_debug);
            }
            
            startseq((SHORT)idx_slab,(SHORT)MAY_PAUSE);

            /* Chopper logic */
            chop_phase = -chop_phase;
        }

    }
    printdbg("end\n", tricks_debug);

    return SUCCESS;
}   

@host TricksHostFunctions

/* tricks_read_kernel_file

   Description: Read TRICKS kernel from file

   Inputs:
     none

   Outputs: 
     return variable indicating status of function

   Global Inputs:
     CV: use_ermes
     IPGEXPORT: mask_regions_min
     IPGEXPORT: mask_regions_max
     IPGEXPORT: kernel_regions_min
     IPGEXPORT: kernel_regions_max

   Global Outputs:
     CV: avmintphases
     CV: avmaxtphases
     IPGEXPORT: ectricks_mask_regions[];
     IPGEXPORT: ectricks_kernel_regions[];
     IPGEXPORT: mask_regions
     IPGEXPORT: kernel_regions
     IPGEXPORT: tricks_maxphases

*/

STATUS
tricks_read_kernel_file(void)
{
    FILE *kernel_file;
    char kernel_datafile[BUFSIZ] = "ec-tricks-kernel";
#ifndef SIM
    char kernel_datapath[BUFSIZ] = "/usr/g/bin/";
#else /* SIM */
    char kernel_datapath[BUFSIZ] = "./";
#endif /* !SIM */
    char filestring[BUFSIZ];
    int dummy_read;
    int tricks_index;
    
    strcpy(filestring, kernel_datapath);
    strcat(filestring, kernel_datafile);
    
    if ( ( kernel_file = fopen(filestring, "r")) == NULL)
    {
        system("pwd  >> /usr/g/service/log/no-kernelfile ");
        system("ls -l /usr/g/bin/ec-tricks-* >> /usr/g/service/log/no-kernelfile ");
        system("date >> /usr/g/service/log/no-kernelfile ");
        
        epic_error( use_ermes, "Unable to open the file %s",
                    EM_PSD_DFM_TABLE_OPEN_ERROR, EE_ARGS(1),
                    STRING_ARG, filestring );
        return FAILURE;
    }
    
    /* read mask_regions and kernel_regions seperately */
    
    fscanf( kernel_file, "%d", &mask_regions );
    /* check if the mask_regions are ok */
    if( mask_regions < mask_regions_min )
    {
        epic_error( use_ermes,
                    "%s is incompatible with %s.",
                    EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                    STRING_ARG, "ECTRICKS",
                    STRING_ARG, "Mask Regions Less than 2" );
        fclose(kernel_file);
        return FAILURE;
    }
    if( mask_regions > mask_regions_max )
    {
        epic_error( use_ermes,
                    "%s is incompatible with %s.",
                    EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                    STRING_ARG, "ECTRICKS",
                    STRING_ARG, "Number of Mask Regions" );
        fclose(kernel_file);
        return FAILURE;
    }
    
    /* fill mask_regions as continous integers  I don't know whether
       mask can be something else as of now */
    for( tricks_index = 0; tricks_index < mask_regions; ++tricks_index )
    {
        ectricks_mask_regions[tricks_index] = tricks_index;
    }
    
    fscanf( kernel_file, "%d", &kernel_regions );
    /* check if the kernel_regions are ok */
    if( kernel_regions < kernel_regions_min )
    {
        epic_error( use_ermes,
                    "%s is incompatible with %s.",
                    EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                    STRING_ARG, "ECTRICKS",
                    STRING_ARG, "Kernel Regions Less than 2" );
        fclose(kernel_file);
        return FAILURE;
    }
    if( kernel_regions > kernel_regions_max )
    {
        epic_error( use_ermes,
                    "%s is incompatible with %s.",
                    EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                    STRING_ARG, "ECTRICKS",
                    STRING_ARG, "Number of Kernel Regions" );
        fclose(kernel_file);
        return FAILURE;
    }

    for( tricks_index = 0; tricks_index < kernel_regions; ++tricks_index )
    {
        fscanf(kernel_file, "%d", &dummy_read);
        ectricks_kernel_regions[tricks_index] = dummy_read;
    }

    fclose(kernel_file);

    /* tricks_maxphases is constrained by tricks_maxecho. 2-echoes are reserved
       for mask and repeat so that has to be subtracted */
    tricks_maxphases = ((tricks_maxecho * mask_regions) - (2 * mask_regions));
    avmaxtphases = IMin(2,tricks_maxphases,tricks_maxseries);
    avmintphases = 1;

    return SUCCESS;
}

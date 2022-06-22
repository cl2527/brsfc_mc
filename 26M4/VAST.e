/*
 * GE Medical Systems
 * Copyright (C) 2001-2003 The General Electric Company
 *
 * VAST.e
 *
 * Contains the epic code to support variable temporal ECG gating and
 * sampling.
 *
 * A brief description of the routines in this module:
 *    VASTCvnit: initialization, to be invoked by cvinit(). 
 *    VASTCveval: to be invoked by cveval(). 
 *    VASTPulsegen: create a dummy sequence, invoked by pulsegen()
 *    VASTRspInit:  rsp initializations, to be invoked by psdinit()
 *
 * Language : ANSI C
 * Author   : Thomas Foo
 * Date     : 03-Mar-2001
 */
/* do not edit anything above this line */

/*
	Date        Author  Comments
____________________________________________________________________________

        3-Mar-2001   TKF     Initial port from 8.2.5CDP3 prototype to 84M4.

       18-June-2001  TKF     Fixed rf calibration for IRPREP and rf1
                             for more accurate calculation of the SAR
			     estimates.  Scale the rf amplitude by
                             the ratio of TR and cardiac interval for IRPREP
                             and by the product (pe_acq2*TR/RRtime) for the
                             rf1 pulse.

       20-July-2001  TKF     Added new acquisition order for MDE.
                             Changed gated_dda to 4 from 2.
			     Changed IR pulse to a non-selective IR.

			    Added a new variable, phase_order
			    to describe how the views are to be segmented.
			    phase_order = 0 : starts from the
			                      rhnframes-rhhnover boundary
					      and proceeds through the center
					      of k-space in one segment,
					      and then from the boundary to
					      the edge of k-space in the next
					      segment. This was the option used
					      in the initial evaluations.

			   phase_order = 1 : simple reverse sequential.
			                     Starts from the edge of the
					     overscan region and proceeds to
					     the edge of the high spatial
					     frequency edge of k-space.
					     
			   phase_order = 2 : Interleaved.
			                     Starts from the high k edge of the
					     data set and proceeds to
					     the center and overscan region.
					     Sequential order for the
					     first (pe_acq2-pe_acq1) views
					     and then interleaved with a
					     spacing of num_outer_loop views.
					     Gives a smoother k-space weighting.
			   phase_order = 3 : Reversed interleaved.
			                     Starts from the edge of the
					     overscan region and proceeds to
					     the center and the high spatial
					     frequency k-space edge.
					     Sequential order for the
					     last (pe_acq2-pe_acq1) views
					     otherwise interleaved with a
					     spacing of num_outer_loop views.
					     Gives a smoother k-space weighting.
			 

22-July-2002  TKF   ramping fiesta dda doesn't help.
                    added fiesta_gated_dda = 20 
		    added pe_acq1 range check

8-Aug-2002    TKF   With gated_dda = 4 null point was 30-50 msec ahead of
		    the 2D sequence.  With gated_dda = 10, null point was
		    50 msec behind the 2D result.  6 gated_ddas with TR of 4
		    gives a 30-80 msec shift backwards.  So, to compromise
		    split the difference. Set gated_dda = 6.

06-Mar-2003   ALP   Initial baseline in 11.0 for EXCITE2 release. Code currently
                    supports 3D MDE and 3D fatsat fiesta with VAST loop 
                    ordering.
                    Gated_dda set back to 4 to sync up inversion times with 2d MDE.  
                    Error handling for min/max tdel.
                    Removed calc_ramp_flip (ramped flip not used).
                    Added code for scaling IR RF and grad pulses.
                    Added code to scale TR from minseqrfamp and maqseqsar based on 
                    available imaging time and actual RF playtime.

28-Mar-2003   RJF/  Integrating Navigator gating support for fiesta and gre. 
              PL    Fiesta and GRE supports SpecIR, and GRE supports IrPrep for MDE.

06-Jun-2003   PL    MRIge81824: Add ASSET support for 3D MDE and fatsat gated
                    FIESTA

10-Jun-2003   PL    MRIge84678: Added missing hbs_left initialization in
                    vast_fiesta_scancore.

13-Jun-2003   RJF   MRIge85217, MRIge85584, MRIge85579, MRIge85587, MRIge85592
                    MRIge83354. Addressing Trigger Delay related error loops, 
                    major code clean up in vast_timing. Also addresses issues with 
                    incorrect trigger delays than prescribed, and navigator missing triggers.

13-Jun-2003   PL    MRIge85079, MRIge84321 - Fixed trigger logic to prevent ECG 
                    triggerring on every view when dda_delay is 0.  

30-Jun-2003   PL    MRIge85740 - Added efficiency calculation to count down clock
                    Move code from VASTcvinit to VASTcveval.

21-Jul-2003   PL    Change default opti value.

24-Sep-2003   PL    MRIge84994 - Added missing half-alpha, half-TR sequence and
                    disdaqs to vast_fiesta_core for non-specIR case.

21-Oct-2003   PL    MRIge89462 - Added arrhthmia check logic for 3D FIESTA Gated.

03-Nov-2003   PL/   MRIge87434 (MRIge85584 MRIge83354) - Added logic for
              GFN   the use of an auto trigger delay selection through
                    opautotdel1.

26-Apr-2005   ARI/  MRIhc07115 - Navigator enhancements:
              MF    implementing new LSQ algorithm for NAV

05-May-2005   ARI   MRIhc07063 - Navigator enhancements:
                    writing NAV data into file

03-Jun-2005   ARI/  MRIhc07226 - Navigator enhancements:
              MF    slab tracking & cylindrical NAV

08-Jun-2005   TV/   MRIhc00673 - Scale min_rfavgpow;min_rfrmsb1;minseqgrddrv_t
	      HAD   minseqgram_t; minseqgpm_t; minseqcoil_t; min_rfdycc to
		    account for dead time in Gated scans

15-Dec-2005   CRM   MRIhc12606 - Added missing include file for logMsg().

21-Nov-2005   YI    YMSmr08150 - Fixed over current problem on HFD-S-lite
                    with FIESTA Gating protocol.

11-Jan-2006   MF    MRIhc12741 - Fix navigator direction reversal problem    

13-Jan-2006   KA    Replaced alpha pulse with  ramp up pulses and dda pulses.
                    Also added ramp down pulses. These modifications are applied to
                    HDe only.

12-Apr-2006   ARI   MRIhc14923 - Remove GRAM model.

11-Aug-2006   ARI   MRIhc17027 - Fixed min_seqgrad calculation for gated scans.

30-May-2007   SW    MRIhc23978 - Enable dda for 3D Gated Fiesta when specir_flag is off.

14-Aug-2008   YS    YMSmr11766,YMSmr11861 - Fiesta sequence was not set-up correctly on HDe2 system. So, added boffset(off_seqcore).

04-Sep-2008   SW    MRIhc39688 - Add the vast_ifir_scancore() based on Naoyuki Takei's
                                 prototype.

18-Sep-2008   YS    YMSmr12248 - Added setscantimestart() to count down scan time every 1 sec.

02-Feb-2009   SW    MRIhc41778 - Scale minseqbusbar_t to account for dead time in Gated scans

28-Aug-2009   MM    GEHmr01998 - IFIR GraphicRx Enhancement

06-Nov-2009   SW    MRIhc46122  - 3D Heart feature promotion with code clean up.

13-Nov-2009   SW    MRIhc46289  - Add rhhnover in the TI/TDEL calculation.

12/31/2009  VSN/VAK MRIhc46886 : SV to DV Apps Sync Up

15-Jan-2010   JX    MRIhc47133 - 3D Heart RR pulldown menu update.

03-Dec-2010   JX    MRIhc53952 - NavSat for 3dHeart FS FIESTA with cylin nav on 1.5T.


19-Aug-2011   NB    HCSDM00092825 : Code cleanup and changes related to RTP on VRE for HD23

22-Apr-2014   YT    HCSDM00282488 : Added support for KIZUNA gradient thermal models

28-Jan-2015   YT    HCSDM00327996 : Removed disp_x component from slab_phase for slab tracking
                                    because disp_x is added in spoil() in HCSDM00183121 fix.
*/

@global VASTglobal
#include "VAST.h"
#define HEADFIRST 1
#define MAX_NAV_HREP 12

/* set up for ECG trigger TKF */
LONG triggerState;

@inline SlabTracking.e SlabTrackGlobal  /* MRIhc07226: navTRACK */



@cv VASTcv
int vast_mode = 0 with {0,1,0,VIS,"VAST acquisition mode for 3D MDE/FS FIESTA",};
int debug_card_sim = 0 with {0,1,0,VIS,"simulate cardiac gating",};  
int pe_acq1 = 32 with {1,,32,VIS,"number of phase encodes to acquire per RR within gated_pelim1",};
int pe_acq2 = 64 with {1,,64,VIS,"number of phase encodes to acquire per RR within gated_pelim2",};
int max_pencodes;
int min_pencodes;
int num_outer_loops = 1 with {1,32,1,INVIS,"number of times outer-loop iterates",};
int tdel1_time = 0;
int dda_delay = 0 with {0,,,VIS,"number of dummy rf pulses to make up delay time after trig",};
int gated_dda = 4 with {0,,4,VIS,"number of disdaqs for gre gated (non-cont) acqs",};
int fiesta_gated_dda = 20 with {0,,20,VIS,"number of disdaqs for fiesta gated (non-cont) acqs",};
int fiesta_gated_ramp_dda = 15 with {0,,15,INVIS,"number of disdaqs for fiesta ramp up",};
int fiesta_gated_flat_dda = 5 with {0,,5,INVIS,"number of disdaqs for fiesta after ramp up and before data acq.",};
int fiesta_gated_ramp_down = 5 with {0,,5,INVIS,"number of disdaqs for fiesta ramp down",};
int vast_symm = 0 with {0,1,0, INVIS, " 2RR vast symmetry: 0=VAST, 1=non-VAST",};
int phase_order = 3 with {0, 4, 3, INVIS, " MDE/FIESTA gated phase order: 0=sym from break,1=rev sequential, 2=interleaved, 3= rev seq intl VAST, 4 = seq intl non VAST",};
int slice_order = 0 with {0, 1, 1, INVIS, " 3D FIESTA/FGRE gated slice order: 0=Sequential, 1=Center out",};
float avail_RRtime = 0 with {0,,0,VIS,"available image time per RR interval",};
int enable_alpha = 1 with {0,1,1,VIS,"Enable/disable the prep: 1/2 alpha 1/2 TR sequence",};  
int min_tdel1_time = 10ms;
int max_tdel1_time = 10ms;
int tdel1_tmp;
int arr_check = 0 with {0, 1, 0, INVIS, "Arrhythmia check flag: 0=OFF, 1=ON",};
int min_tdel1_fiesta = 200ms; /* YMSmr08388  12/21/2005 YI */
float rf_scale_fac;
float scale_tr;
float scale_tr_grad; /* YMSmr08150 11/21/2005 YI */
@inline SlabTracking.e SlabTrackCV  /* MRIhc07226: navTRACK */

int ifir_dummy_pe = 0 with {0,100,0,INVIS,"number of dummy echo for Inh-3DIFIR",};

int heart3d_flag = 0 with {0,1,0,INVIS,"3D Heart feature flag (0=OFF, 1=ON)",};

@host VASTcvinit
    /* Increase max ophrep (heartbeats per TR) to 12 */
    cvmax(ophrep,MAX_NAV_HREP); 
    if(value_system_flag){
        enable_alpha = 0;
        fiesta_gated_dda = fiesta_gated_ramp_dda + fiesta_gated_flat_dda;
    } 
    else if(heart3d_flag)
    {
        enable_alpha = 0;
        fiesta_gated_dda = 10;
    }
    else 
    {
        enable_alpha = 1;
        fiesta_gated_dda = 20;
    }

@host VASTcveval

    if (ifir_flag && (exist(oprtrep)>1))
    {
       ifir_dummy_pe = 20;
    } else {
       ifir_dummy_pe = 0;
    }
					   
    if( (exist(opcgate) == PSD_ON) && (vast_mode == PSD_ON) ) 
    {
        if (heart3d_flag)
        { 
            piovlnub = 3;   /* overlap slices bit map */
            pidefslq = 24;  
            pipctovl = 4;
        }

        pitrigwinnub = 63;  /* Bitmask for Trigger Window buttons */
        piphasenub   = 0;   /* Bitmask for Phase buttons */
        piphslnub    = 0;   /* Bitmask for Phases/Slices feedback fields */
        piviewseg    = 0;   /* Bitmask for views per segment field. */    
        oparrmon=0;			/* disable oparrmon */    
        piadvcard = (1<<PSD_ADVAVAILIMGTIME) + (1<<PSD_ADVISEQDELAY) ;
    
        /* TKF use ophrep to control segmentation */
        cvmax(ophrep, MAX_NAV_HREP);    /* Allow up to 12 RR for imaging
                                           subjects with high heart rates */
        pihrepnub=1 + 2 + 4 + 8;		/* Bitmask for hrep buttons */
        if ((exist(opasset)) && (exist(opnex)<=0.75)) {
            pihrepval2=1;		/* Button 2 value */
            pihrepval3=2;		/* Button 3 value */
            pihrepval4=3;               /* Button 4 value */
        } else if (exist(opnex)>0.75) {
            pihrepval2=2;		/* Button 2 value */
            pihrepval3=4;		/* Button 3 value */
            pihrepval4=6;               /* Button 4 value */
        } else {
            pihrepval2=2;		/* Button 2 value */
            pihrepval3=3;		/* Button 3 value */
            pihrepval4=4;               /* Button 4 value */
        }
        cvdef(ophrep,3);
    
        /* Arrhythmia rejection window */
        pifcinenub = -1;       /* change label to Arrhythmia */

        if( arr_check ) {
            cvdef(oparr, 5);
            pidefarr = 5;   
        } else {
            cvdef(oparr, 10);
            pidefarr = 10;   
        }       

        /* Trigger delay */
        pitdel1nub  = 7;    /* bitmap for pulldown menu  */
        cvdef(optdel1, 250ms);
        optdel1 = _optdel1.defval;
        avmintdel1 = 1ms;

        /* 
           vast uses gated_ddas for disdaqs, not irdisdacqs. 
           Make sure timing calcs are right by setting this cv to 0.
           See min_ti and tseq_irprep calcs for VAST to see the impact. - RJF
         */
        /* Fiesta does not use gated_dda but Navigator.e does */
        if( ssfp_flag ) {
            gated_dda = 0;
        } else {
            gated_dda = 4;
        }
        irdisdacqs = 0; 
        avail_RRtime  =  (60.0 / (FLOAT)(exist(ophrate))) *1000000.0;

    	if ((PSD_ON == navgate_flag) || ( 1==exist(opnex)) || 
            (heart3d_flag && ((PSD_GE==exist(oppseq)) || (PSD_SPGR==exist(oppseq))))) {
            /* (MRIhc07226) Change vast_symm from 0 to 1, only matters for 2RR. 
         	 * Always symmetric for > 2RR. VAST is mostly usefull with low-yres. 
         	 * For yres=128+16, pe_acq1=32 & pe_acq2=112 highly assymetric. 
             */
             vast_symm = 1;
    	}

        if (exist(ophrep) == 2) 
        {
            if (0 == vast_symm)
            {
                pe_acq1 = IMax(2,rhhnover * 2,32);
            } else {
                pe_acq1 = (rhnframes + rhhnover)/2;
            }
    
            pe_acq2 = (rhnframes + rhhnover) - pe_acq1;
    
            /* range check */ 
            if (pe_acq1 > pe_acq2) {
                pe_acq1 = (rhnframes + rhhnover)/2;
                pe_acq2 = pe_acq1;
            }
    
            num_outer_loops = (1 + ceil((float)((rhnframes + rhhnover) - pe_acq1)/(float)pe_acq2));
        } else  {
            /* allows for greater segmentation */
            num_outer_loops = exist(ophrep);
            pe_acq1 = ceil((float)(rhnframes + rhhnover)/(float)(num_outer_loops));
            pe_acq2 = pe_acq1;
    
            /* regular rev seg intl MS */
            if (phase_order == 4) {
                pe_acq2 = (rhnframes + rhhnover)/num_outer_loops;
                pe_acq1 = pe_acq2;
            }
        } 
    
        max_pencodes = IMax(2,pe_acq1,pe_acq2);
        min_pencodes = IMin(2,pe_acq1,pe_acq2);

        /* MRIhc12741 This fixes the problem where Nav direction is reversed when 
         * tracker is prescribed from the Coronal localizer instead of Saggital
         */		
        /* Assume to be feet first if it is not head first */
        if (((float)rsprot_monitor[0][6]<=0 && (HEADFIRST!=exist(opentry))) || 
            ((float)rsprot_monitor[0][6]>=0 && (HEADFIRST==exist(opentry))))
        {
            nav_dir = 1;    /*ascending edge Saggital*/
        } else {
            nav_dir = -1;   /*descending edge Coronal*/
        }
    } 
    else if (ifir_flag)
    {
        gated_dda = 0;

        avail_RRtime = (60.0 / (FLOAT)(exist(oprtrate))) * 1000000.0;

        /* Limit avail_RRtime to 5s to avoil scale too much in the SAR
         * calculation.
         */
        if (avail_RRtime > 5.0*1000000.0) avail_RRtime = 5.0*1000000.0;

        num_outer_loops = exist(oprtrep);
        pe_acq1 = (int)ceil((float)(rhnframes + rhhnover)/(float)(num_outer_loops));
        pe_acq2 = pe_acq1;

        max_pencodes = pe_acq1 + ifir_dummy_pe;
        min_pencodes = pe_acq1 + ifir_dummy_pe;
    }

@host VASTsetseqtype
    if(heart3d_flag && vast_mode && (exist(opvquant)>1) && existcv(opvquant))
    {
        seq_type = TYP3DMSNCAT;
    }

@host VASTtiming    
    if( (exist(opcgate) == PSD_ON) && (vast_mode == PSD_ON) ) 
    {
        int RR_time;
        int t_systole;
    
        /* Make sure actual TR is not negative or zero */
        if( act_tr <= 0 ) {
            epic_error( 0, "Unknown error (act_tr = 0).  Please repeat last selection.", 0, EE_ARGS(0), 0 );
            return FAILURE;
        }
    
        piviews = num_outer_loops*pfkz_total_unaccel*((int)(0.5 + opnex))*exist(opvquant);
    
        pidmode = PSD_CLOCK_CARDIAC;
        piclckcnt = 1;
    
        avmintscan = piviews*(60.0s/exist(ophrate));
        pitslice = avmintscan/exist(opvquant);
        pitscan = avmintscan;
        pisctim1 = pitscan;
    
        /* check to see if the acquisition goes across an RR interval */
        RR_time = (int)(60s/(float) exist(ophrate));
        /* Equation is from Circulation 1968, p149-159
         * Using S1S2 insteat of QS2 since R peak is at S1 
         */
        t_systole = (int)(456.0 - (1.8*(float) exist(ophrate)))*1ms;
        /* mid-diastole */
        if (2==exist(opcgatetype))
        {   /* PG, based on empirical result */
            tdel1_tmp = (int) (RR_time/2); 
        } 
        else 
        {   /* ECG */
            tdel1_tmp = (int) ( (RR_time+t_systole)/2 ); 
        }
        advroundup(&tdel1_tmp);
    
        /* MS default to systole 300 ms for MDE */
        if( irprep_flag && (!heart3d_flag) ) {
            tdel1_tmp = 300ms; 
        }  
    
        /* Calculate min/max trigger delay times */
        max_tdel1_time = (int)( ((float)RR_time * (100.0-exist(oparr))/100.0) - 1ms 
                                - (max_pencodes-rhhnover/num_outer_loops)*act_tr 
                                - ((value_system_flag ? 1 : 0)*fiesta_gated_ramp_down*act_tr)
                                - (navsat_flag * tmin_montipup)
                                - (fiesta_killer_flag*tseq_gzk) 
                                - (navgate_flag*(!slabtracking_flag)*mon_navgs*mon_tr)
                                + t_exa );
    
        min_tdel1_time = (int)( irprep_flag*exist(opti) + t_exa + 1ms +
                       (!irprep_flag)*(ssfp_flag*(enable_alpha+fiesta_gated_dda+rhhnover/num_outer_loops)*act_tr 
                                     + (!ssfp_flag)*(gated_dda+rhhnover/num_outer_loops)*act_tr 
                                     + specir_flag*cs_sattime
                                     + t2prep_flag*t2prep_tseq 
                                     + slabtracking_flag*mon_navgs*mon_tr) );

        advrounddown(&max_tdel1_time);
        advroundup(&min_tdel1_time);
    
        if( tdel1_tmp > max_tdel1_time ) {
            pitdel1 = max_tdel1_time;
        } else {
            pitdel1 = tdel1_tmp;
        }
    
        if( pitdel1 < min_tdel1_time ) {
            pitdel1 = min_tdel1_time;
        }
    
        avmintdel1 = min_tdel1_time;
        avmaxtdel1 = max_tdel1_time;

        /* YMSmr07282  08/04/2005 YI  to avoid ghosting on FIESTA */
        if(value_system_flag == VALUE_SYSTEM_HDE) {
            if(ssfp_flag && !specir_flag) {
                avmintdel1 = pitdel1;
            }
        }
    
        /*
         * Override Trigger Delay value if user prescribes
         * Minimum or Recommended
         */
        if( existcv(opautotdel1) ) {
            if( PSD_TDEL1_MINIMUM == exist(opautotdel1) ) {
                cvdef(optdel1, avmintdel1);
                cvoverride(optdel1, _optdel1.defval, PSD_FIX_ON, PSD_EXIST_ON);
            } else if( PSD_TDEL1_RECOMMENDED == exist(opautotdel1) ) {
                cvdef(optdel1, pitdel1);
                cvoverride(optdel1, _optdel1.defval, PSD_FIX_ON, PSD_EXIST_ON);
            }
        }
    
        tdel1_time = (exist(optdel1) - min_tdel1_time);
    
        /* If there is no prep sequence, there is no TI, hence we have to
           manually push to alpha pulse out to get the desired TDEL. Do this
           by playing out dda_delay number of disdaqs when the trigger occurs.
           This is also required for non fatSat fiesta to get the desired tdel.
           -RJF, 11.0 */
        dda_delay = (int)(tdel1_time / act_tr);
    
    } 
    else 
    {
        tdel1_time = 0;

        if (ifir_flag) 
        {	
            pidmode = PSD_CLOCK_CARDIAC;
            piclckcnt = 1;
            piviews = num_outer_loops * exist(opslquant);
            avmintscan = (float)(piviews * (60.0s/(float)exist(oprtrate)));
														       
            pitslice = avmintscan;
            pitscan = pitslice;
            pisctim1 = pitscan;
        }
    }

@host VASTcvcheck
    if( (exist(opcgate) == PSD_ON) && (vast_mode == PSD_ON) ) 
    {
	    /* (MRIhc07226) May need to take away check condition of ophrep to allow 1RR and >3RR */
        if( existcv(ophrep) && exist(ophrep) == 1 && (opasset == PSD_OFF) ) {
            epic_error( 0, "ASSET and 0.5 NEX  must be selected for #RR = 1", 0, EE_ARGS(0), 0);
            return FAILURE;
        }
    
        if( existcv(ophrep) && exist(ophrep) > MAX_NAV_HREP ) {
            epic_error( use_ermes, "# RR > %d is incompatible with %s",
                        EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                        INT_ARG, MAX_NAV_HREP,
                        STRING_ARG, "this mode" );
            return FAILURE;
        }

        /* Make sure FIESTA with FAT SAT is showing an advisory text indicating
           special must be selected. This must be done early enough to avoid
           trigger delay related error loops. A similar check is efgre3d.e is
           required to handle non-vast mode. */
        if( (PSD_ON == ssfp_flag) && (exist(opfat) == PSD_ON) ) {
          epic_error( use_ermes, "SPECIAL must be selected for FAT Suppression in 3D FIESTA.", 
                      EM_PSD_3DFIESTA_FATSAT, EE_ARGS(0) );
            return FAILURE;
        }
    
        /* Make sure the attempt to do FAT SAT with IRPrep is handled with
           a nice exit, rather than creating error loops with trigger delay out
           of range. */
        if( (irprep_flag == PSD_ON) && (exist(opfat) == PSD_ON) && existcv(opfat) ) {
            epic_error( use_ermes, "%s is incompatible with %s",
                        EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                        STRING_ARG, "FAT Suppression",
                        STRING_ARG, "IRPrep" );
            return FAILURE;
        }
    
        /* When too many views are requested, maxtdel can go negative trying to
           accomodate this. Handle this case and throw an error right away.
           Reducing TI will not help in this case. */
        if( (avmaxtdel1 < 0 ) && existcv(optdel1) && existcv(opyres) ) {
          epic_error( use_ermes, "Insufficient imaging time. Lower Y Res, TR, or increase # RR.", 
                      EM_PSD_VAST_TDEL_OUT_OF_RANGE1, EE_ARGS(0) );
            return FAILURE;
        }
    
        /*  The case below can occur when TI requested may be too high
            and can be resolved by lowering TI or reducing the number of
            views to be collected in the RR interval (reduce yres or go to
            3 RR  or reducing TR - RJF */
        if( (avmaxtdel1 < avmintdel1 ) &&  existcv(optdel1) && existcv(opyres) ) {
            epic_error( use_ermes, "Insufficient imaging time. Lower TI, Y Res, TR, or increase # RR.", 
                        EM_PSD_VAST_TDEL_OUT_OF_RANGE2, EE_ARGS(0) );
            return FAILURE;
        }

        /* YMSmr08388  12/21/2005 YI */
        if( (exist(optdel1)<min_tdel1_fiesta) && existcv(optdel1) && existcv(opyres) && 
            (VALUE_SYSTEM_HDE == value_system_flag) && ssfp_flag && !specir_flag ) {
            epic_error( use_ermes, "Insufficient imaging time. Lower TI, Y Res, TR, or increase # RR.", 
                        EM_PSD_VAST_TDEL_OUT_OF_RANGE2, EE_ARGS(0) );
            return FAILURE;
        }

        /* Check trigger delay for out of range cases */
        if( existcv(opyres) && existcv(optdel1) && ( exist(optdel1) > avmaxtdel1 ) ) {
            epic_error( use_ermes, "Decrease trigger delay to %d ms, decrease Y Res, or increase # RR.", 
                      EM_PSD_VAST_TDEL_OUT_OF_RANGE3,EE_ARGS(1),INT_ARG,(int)(ceil((double)avmaxtdel1/1000.0)));
            return FAILURE;
        }

        if( tdel1_time < 0 && existcv(optdel1) && existcv(opyres) ) { 
            epic_error( use_ermes, "Trigger Delay must be increased to %d ms.", 
                      EM_PSD_TD_OUT_OF_RANGE4, EE_ARGS(1), INT_ARG, avmintdel1 / 1000 );
            return FAILURE;
        }

        /* (MRIhc07226) Add check for slab tracking */
        if((PSD_OFF == navtrig_flag) && (PSD_OFF == navgate_flag) && slabtracking_flag) {
            epic_error( use_ermes, "%s must be used with %s",
                        EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                        STRING_ARG, "Slab Tracking",
                        STRING_ARG, "non-Navigator" );
            return FAILURE;
        }

        avmaxovl = (int)((float)(exist(opslquant)-2*exist(opslblank))/2.0);

        if( (exist(opovl)>avmaxovl) && existcv(opovl) && existcv(opslquant) )
        {
            epic_error(use_ermes, "The number of overlap locations selected must be reduced to %d for the current prescription.",
                       EM_PSD_OVLSLQ_OUT_OF_RANGE, EE_ARGS(1), INT_ARG, avmaxovl);
           return FAILURE; 
        }

        if( existcv(ophrep) && (0!=(exist(ophrep)%2)) && (exist(opnex)>0.75) ) {
            epic_error( use_ermes, "%s is incompatible with %s",
                        EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                        STRING_ARG, "1NEX with center Ky ordering",
                        STRING_ARG, "odd #RR" );
            return FAILURE;
        }

        if( irprep_flag && t2prep_flag )
        {
            epic_error( use_ermes, "%s is incompatible with %s",
                        EM_PSD_INCOMPATIBLE, EE_ARGS(2),
                        STRING_ARG, "IRPrep",
                        STRING_ARG, "T2Prep" );
            return FAILURE;
        }
    }

@host VAST_scaleKillergrad
    if (vast_mode && fiesta_killer_flag)
    {
        float grad_scale_fac;
        int phase_num;
				    
        phase_num = max_pencodes + ssfp_flag * (enable_alpha + fiesta_gated_dda);
        grad_scale_fac = 1.0/(float)phase_num;
        if ( (grad_scale_fac <= 0) || (grad_scale_fac > 1) ) {
            grad_scale_fac = 1.0;
        }
        gradz[GZK_SLOT].scale = grad_scale_fac;
    }

@host VAST_scaleTR
    if( ((exist(opcgate)==PSD_ON) || ifir_flag) && (vast_mode == PSD_ON) && (debug_scale == PSD_OFF) )
    {
	    int temp_tr;
    
        temp_tr = IMax(2, min_seqrfamp, max_seqsar);
        /* add 1 for the prep sequence alpha pulse */
        scale_tr = (float)( (max_pencodes + ssfp_flag * (enable_alpha+fiesta_gated_dda) +
                               (!ssfp_flag) * gated_dda) * (float)temp_tr / (float)avail_RRtime);

        if ( (scale_tr <= 0) || (scale_tr > 1) )
        {
            scale_tr = 1;
        }

        /* YMSmr08150, GEHmr02619 */
        if((cfgradamp == 8919) || (cfgradamp == 8905)||(cfgradamp == 8907)||((int)(10000 * cfxfs / cfrmp2xfs)<70)) {
            scale_tr_grad = 1.0;
        } else {
            scale_tr_grad = scale_tr;
        }
        min_seqrfamp = (int) (scale_tr*min_seqrfamp);
        max_seqsar = (int) (scale_tr*max_seqsar);
	
        /* MRIhc00673: use scale_tr factor to account for dead time in gated scans. */
        min_rfavgpow = (int) (scale_tr*min_rfavgpow);
        min_rfrmsb1 = (int) (scale_tr*min_rfrmsb1);
        min_rfdycc = (int) (scale_tr*min_rfdycc);
        min_rfampcpblty = (int) (scale_tr*min_rfampcpblty);

        /* MRIhc17027 : copied from minseq. only perform scaling if get_cvs_changed */
        if ( ( PSD_ON == exist(oprealtime) ) ||
             ( PSD_ON == gradHeatFlag ) ||
             ( FALSE == skip_minseqseg ) )
        {
            /* In SSSD (cfgradamp = 5550), scale_tr_grad is not applied to minseq*
               for short thermal time constant components (less than about 1sec) */

            if (5550 != cfgradamp)
            {
                minseqgrddrv_t = (int) (minseqgrddrv_t*scale_tr_grad); /* YMSmr08150 */
            }

            if (5550 == cfgradamp)
            {
                minseqgrddrv_case_t = (int) (minseqgrddrv_case_t*scale_tr_grad);
                minseqcable_maxpow_t = (int) (minseqcable_maxpow_t*scale_tr_grad);
            }

            minseqgpm_t    = (int) (scale_tr_grad*minseqgpm_t);    /* YMSmr08150 */
            minseqcable_t  = (int) (minseqcable_t*scale_tr_grad);  /* MRIhc17027 */
            minseqcoil_t   = (int) (minseqcoil_t*scale_tr_grad);   /* YMSmr08150 */
            minseqchoke_t  = (int) (minseqchoke_t*scale_tr_grad);  /* MRIhc17027 */
            minseqbusbar_t  = (int) (minseqbusbar_t*scale_tr_grad);  /* MRIhc41778 */

            if (5550 == cfgradamp)
            {
                min_seqgrad = IMax(7, minseqgrddrv_t, minseqgrddrv_case_t,
                                      minseqgpm_t, minseqgpm_maxpow_t,
                                      minseqcable_t, minseqcable_maxpow_t,
                                      minseqcoil_t);
            }
            else
            {
                min_seqgrad    = IMax(6, minseqcoil_t, minseqgrddrv_t, minseqgpm_t,
                                         minseqcable_t, minseqbusbar_t, minseqchoke_t);
            }
        }
    }

@host VASTPredownload
    if ( heart3d_flag )
    {
        if (exist(opvquant) > 1)
        {
            rhovl = slicezp * exist(opovl);
        } else {
            rhovl = 0;
        }
        motsa_ovrhd = rhovl * rhimsize * rhimsize * sizeof(float);
        rhtype1 |= (RHTYP3DM | RHTYPMAXOVL);
        if (pfkz_flag || pfkr_flag || (ACCEL_ARC == rhasset))
        {
            rhtype1 |= RHTYP1BAM0FILL;
        }
        vas_ovrhd = motsa_ovrhd + 3904;
        rhvtype = VASCULAR;
    }

@rsp VASTrsp
#ifdef PSD_HW
/* Needed for printdbg(). To see output, agpTraceOptions must be invoked
   from the AGP window. To enable screen output, the options listed via
   agpTraceStats() must not include 0x20. Subtract 0x20 (32) from the
   current options and use as the input to agpTraceOptions. */
#include <pgen_tmpl.h>
#endif /* PSD_HW */

#ifdef PSD_HW
/* Needed for Navigator testing (MRIhc07063) */
#include "clockApi.h"
/* Needed for logMsg() (MRIhc12606) */
#include "logLib.h"
#endif

@inline SlabTracking.e SlabTrackVariables  /* MRIhc07226: navTRACK */

@rspvar VASTrspvar
int pe_index;
int z_index;
int ncard_delay;


@rsp VASTpsdinit
    /* ****************************************************************** */
    /* view acquisition order changes for variable temporal sampling VAST */
    /* ****************************************************************** */
    if( (vast_mode == PSD_ON) && (opcgate == PSD_ON) ) 
    {
        int k;
        int j;
        int start_view;
        int view_lim1;

        if( opnex == 0.5 )
        {
            /* starts from rhhnover to a bit past ky=0
               on first pass through and then from the
               same point to the edge of k-space on the
               second pass */
            switch( phase_order )
            {
                case 0: /* sequential from break */
                    for( i = 0; i < pe_acq1; ++i ) {
                        viewtab[i] = ((rspvus - pe_acq1 + i) % rspvus) + 1;
                    }
                    for( i = pe_acq1; i < (num_outer_loops * pe_acq2); ++i ) {
                        if( i < rspvus ) {
                            viewtab[i] = (rspvus  - i) % rspvus;
                        } else {
                            viewtab[i] = 0;
                        }
                    }
                    break;
                case 1:  /* reverse sequential */
                    for( i = 0; i < (num_outer_loops * pe_acq2); ++i ) {
                        if( i < rspvus ) {
                            viewtab[i] = (rspvus  - i) % rspvus;
                        } else {
                            viewtab[i] = 0;
                        }
                    }
                    break;
                case 2: /* segmented interleaved */
                    /* half nex only */
                    start_view = (pe_acq2 - pe_acq1) * (num_outer_loops - 1);
                    view_lim1 = start_view/(num_outer_loops - 1);
    
                    i = 0;
                    /* low temporal acquisition views */
                    for( k = 0; k < (num_outer_loops - 1); ++k ) {
                        /* first part of acquisition */
                        for( j = 0; j < view_lim1; ++j ) {
                            viewtab[i] = ((k + j*(num_outer_loops - 1)%rspvus) 
                                          + 1);
                            ++i;
                        }
                        /* second part of acquisition */
                        for( j = view_lim1; j <pe_acq2; ++j ) {
			    /* MRIhc07226: may need to remove minus (-) in the front (?) */
                            viewtab[i] = -(((k + (j-view_lim1)*num_outer_loops +
                                             start_view)%rspvus) 
                                           + 1);
                            ++i;
                        }
                    }
                    /* high temporal resolution views */
                    k = num_outer_loops - 1;
                    for( j = 0; j < view_lim1; ++j ) {
                        viewtab[i] = k + start_view + 1;
                        ++i;
                    }
                    for( j = view_lim1; j < pe_acq2; ++j ) {
                        viewtab[i] = (((k + (j-view_lim1)*num_outer_loops +
                                        start_view)%rspvus) 
                                      + 1);
                        ++i;
                    }
                    break;
                case 3: /* reversed segmented interleaved */
                    /* half nex only */
                    if( num_outer_loops != 1 ) {
                        start_view = (pe_acq2 - pe_acq1) * (num_outer_loops - 1);
                        view_lim1 = start_view/(num_outer_loops - 1);
                    } else {
                        start_view = 0;
                        view_lim1 = 0;
                    }
    
                    /* first part of acquisition */
                    i = 0;
                    for( j = 0; j < pe_acq1; ++j ) {
                        viewtab[i] = (rspvus - (num_outer_loops*j));
                        ++i;
                    }
                    for( j = 0; j < view_lim1; ++j ) {
                        viewtab[i] = 0;   /* zeros out excess views */
                        ++i;
                    }
                    /* second part of acquisition */
                    for( k = 1; k < num_outer_loops; ++k ) {
                        int temp_view;
    
                        for( j = 0; j < pe_acq1; ++j ) {
                            viewtab[i] = rspvus - (num_outer_loops*j)- k;
                            ++i;
                        }
                        temp_view = rspvus - (num_outer_loops*(pe_acq1-1)) - k;
                        for( j = 1; j <= view_lim1; ++j ) {
                            viewtab[i] = temp_view - (num_outer_loops - 1)*j;
                            ++i;
                        }
                    }
                    break;
                case 4: /* non VAST reversed segmented interleaved */
                    for( i = 0; i < num_outer_loops; ++i ) {
                        for( j = 0; j < pe_acq2; ++j ) {
                            viewtab[i*pe_acq2+j] = (rspvus -i -j*num_outer_loops);
                        }
                    }
                    break;
            }  /* phase_order */
        } else {
            /* opnex != 0.5 */
   
            if (heart3d_flag)
            {
                for( i = 0; i < num_outer_loops/2; ++i)
                {
                    for( j = 0; j < pe_acq2; ++j )
                    {
                        viewtab[(i*2)*pe_acq2+j] = (rspvus/2 - i - j*num_outer_loops/2);
                        viewtab[(i*2+1)*pe_acq2+j] = (rspvus/2 + i + 1 + j*num_outer_loops/2);
                    }
                }
            } else { 
                for( i = 0; i < pe_acq1; ++i ) {
                    viewtab[i] = (pe_acq1/2) +  (rspvus/2) - i; /* central views */
                }
                for( i = pe_acq1; i < (num_outer_loops*pe_acq2); ++i ) {
                    if( i< rspvus ) {
                        viewtab[i] = ( (((pe_acq1 + rspvus)/2) + (i - pe_acq1) ) % rspvus) + 1;
                    } else {
                        viewtab[i] = 0;
                    }
                }
            }
        }
    
        /* range check */
        for( i = 0; i < (num_outer_loops*pe_acq2); ++i ) {
            if( (viewtab[i] < 0) || (viewtab[i]>rspvus) ) {
                viewtab[i] = 0;
            }
        }

        switch (slice_order)
        {
            case 0: /* Sequential */
                for (i=0; i<rspslq; i++)
                {
                    slicetab[i]=i;
                }
                break;
            case 1: /* Center Out */
                if (pfkz_flag)
                {
                    int mid_slq = pfkz_total_unaccel - equant/2;
                    for (i=0; i<mid_slq; i++)
                    {
                        slicetab[i*2] = equant/2+i;
                        slicetab[i*2+1] = equant/2-1-i;
                    }
                    for (i=mid_slq*2; i<pfkz_total_unaccel; i++)
                    {
                        slicetab[i]=pfkz_total_unaccel-1-i;
                    }
                } else {
                    for (i=0; i<equant/2; i++)
                    {
                        slicetab[i*2] = equant/2+i;
                        slicetab[i*2+1] = equant/2-1-i;
                    }
                }
                break;
        }
    } 
    else if (ifir_flag)
    {
        int i=0;
        int view_current=0;

        if(1==num_outer_loops)
        {
           for(i=0; i<pe_acq1; i++)
           {
                view_current=rhnframes+rhhnover-i;
                if((view_current<0) || (view_current>(rhnframes+rhhnover)))
                {
                   view_current=0;
                }
                viewtab[i]=view_current;
           }
        } 
        else if(2==num_outer_loops)
        {
           for(i=0; i<pe_acq1; i++)
           {
                view_current=rhnframes+rhhnover-rhnframes/2-i;
                if((view_current<0) || (view_current>(rhnframes+rhhnover)))
                {
                   view_current=0;
                }
                viewtab[i]=view_current;
           }

           for(i=pe_acq1; i<num_outer_loops*pe_acq1;i++)
           {
                view_current=rhnframes+rhhnover-rhnframes/2+(i-pe_acq1)+1;
                if((view_current<0) || (view_current>(rhnframes+rhhnover)))
                {
                    view_current=0;
                }
                viewtab[i]=view_current;
           }
        }              
    }

@rsp VASTcore
/* Core for Breath-hold or Nav gated CAI or MDE modes MS */

@inline SlabTracking.e SlabTrackCore  /* MRIhc07226: navTRACK */

STATUS
#ifdef __STDC__ 
vast_gre_scancore( void )
#else /* !__STDC__ */
vast_gre_scancore()
#endif /* __STDC__ */
{
    /* This is a revised scancore that was designed to minimize the
       transition artifacts from having multiple view updates.  This
       approach uses a reversed loop acquisition order that puts the
       views in the inner loop (as in fastcard-mp) in an interleaved
       view acquisition order.  The interleaving steps are defined in
       the phase_ordering() call and is set to the minimum number
       of view encodes acquired per RR interval.  Note that the 
       slice encoding remains the same in each RR interval and that
       minimizes artifacts in the slice direction.   - TKF 12 Jan 2001 */

    /* new MDE acquisition order scheme to minimize
       transisition in the in-plane views.  The acquisition scheme
       now takes the full k-space in  RR intervals per slice encoding.
       Also dummy rf pulses are played out for the lower 
       phase encode values to maintain the same number of rf pulses
       per RR interval - TKF 20 July, 2001 */

    /* new mode that acquires the data at the end of the acquisition.
       Works now for interleaved mode where the data for the
       first view of the high temporal frequency segment is
       repeatedly acquired and then updated after (pe_acq2-pe_acq1)
       views.  - TKF 10 Aug, 2001 */

    /* gating variables */
    int view_start,i;
    int hbs_left;

    int view_accepted = 0;
    int view_rejected = 0;

    int trigger_ecg;

    /* MRIhc07063 - Create file handle for navigator data in VAST-GRE */
    if ( (PSD_ON == navgate_flag) && (nav_test>3) )
    {
#ifdef PSD_HW
        mgd_clock_gettime (HOST_TIME_OF_DAY, &host_clock);
        seconds = host_clock.tv_sec ;
#endif
        sprintf(nav_filename,"/usr/g/service/log/navtest_data.%d", seconds);
    }
    
    printdbg("Starting vast_gre_scancore", debugstate);
   
    trig_phase = 0.0;

    sliceindex = 0;	/* Location in slice table */
    slice = sliceindex;

    setfrequency(receive_freq1[sliceindex], &echo1, 0);

    /* We don't want to chop the exciter */
    chop_phase = 0;

    dabecho = 0;
    dabslice = 0;
    dabop = 0;

    /*MF MULTISLAB FGRE add for arr_check*/
    triggerState = gettrigoccur();
    trigger_detected = FALSE;
    look_for_trig    = TRUE;
    num_trig = 0;

    if(heart3d_flag)
    {
        rspslq = pfkz_total_unaccel;
    }
    
    hbs_left = rspslq*num_outer_loops*slabquant;
    scantime = pitslice*hbs_left/(float)(rspslq*num_outer_loops);
    setscantimeimm(pidmode, scantime, hbs_left,pitslice,opslicecnt);

    for (slabindex=0; slabindex<slabquant; slabindex++)
    {
        pass = slabindex;

        /* ******************** */
        /* collect disdaq views */
        /* ******************** */

        dabview = viewtab[0];
        /* set slice encode to first value */
        setiamp(volumetab[0], &gzcomb, 0);

        if(zrewind_flag)
        {
            setiamp(volumetab2[0], &gzp, 0);
        }

        setiamp(-viewtable[dabview], &gy1, 0);

        if (rewinder_flag) 
        {
            setiamp(-viewtable[dabview], &gy1r, 0);
        }

        acq_echo1 = DABOFF;
        fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);
        load3d(&d3d, 0, DABOFF);
        setfrequency(rf1_freq[slabindex], &rf1, scanrf1_inst);

        /* Initialize yres_phase and slab_phase to zero */
        yres_phase = 0;
        slab_phase = 0;
        boffset(off_seqcore);

@inline SlabTracking.e SlabTrackBaselinePhase  /* MRIhc07226: navTRACK */
@inline SlabTracking.e SlabTrackGetLogicalDisp /* MRIhc07226: navTRACK */

        if ((PSD_ON == navgate_flag) && (0==slabindex)) 
        {
            /* initialize deltapix to 0 at the beginning (MRIhc07115) */ 
            navigator_set_deltapixel(0.0);
            navigator_reset_iter(1); 
            NavigatorPlayContRf(1,0);
            navigator_reset_iter(0); 

            /* Navigator Prescan */ 
            NavigatorPlayContRf(nav_ss+nav_dda-1,1);

            /* Navigator computations */ 
            /* nav_window, max_nav_phase and min_nav_phase 
               are calculated from the Navigator Prescan. RJF */

            test_rtwin = fabs(nav_window);

            settrigger((short)TRIG_INTERN, (short)slabindex);
            scopeoff(&seqhistdelay);
            boffset(off_seqhistdelay);
            startseq(slabindex, (SHORT)MAY_PAUSE);
            get_navigator_histogram( &trig_phase );

            /* More start seqs to give time for the histogram to complete */
            startseq(slabindex, (SHORT)MAY_PAUSE);
            test_rtpoint = trig_phase;    	    
            tmpcurrthresh = trig_phase;  /* initialization (MRIhc07115) */
            scopeon(&seqcore);
            boffset(off_seqcore);
            NavigatorPlayContRf(nav_ss,0);
            reset_for_scan();
        }

        /* ************************************ */
        /* no baselines are collected in fgre3D */
        /* ************************************ */

        /* acquire all k-y phase encoding lines as close together as possible  */

        for (sliceindex=0; sliceindex<rspslq; sliceindex++)
        {   /* grab the slab phase offset */
            slice = slicetab[sliceindex];

            if(heart3d_flag && rvssliceenc)
            {
                slab_phase = slab_off[slabindex].zsign * ((equant-1-slice) * slab_off[slabindex].zoffs);
            } else {
                slab_phase = slab_off[slabindex].zsign * (slice * slab_off[slabindex].zoffs);
            }

            setiamp(volumetab[slice], &gzcomb, 0);
            if (zrewind_flag) 
            {
                setiamp(volumetab2[slice], &gzp, 0);
            }

            view_start = 0;   /* initialize starting view */

            for (z_index=0; z_index < num_outer_loops; z_index++) 
            {
                dabop = DABSTORE;	/* store xcvr data */

                settrigger((short)TRIG_ECG, (short)slabindex);

                /* MRIhc07226: use standalone trigger delay block 
                 * instead of adding tdel1_time to irprep sequence etc */  
                if (debug_card_sim || (trigger_detected == TRUE)) 
                {
                    trigger_ecg = TRIG_INTERN;
                    trigger_detected = TRUE;
                } else {
                    trigger_ecg = TRIG_ECG;
                    trigger_detected = FALSE;
                }
                acq_echo1 = DABOFF;
                fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);

@inline SlabTracking.e SlabTrackTriggerDelayFGRE3D  /* MRIhc07226: navTRACK */

                /* update deltapix if currthresh is changed (MRIhc07115) */
                if (PSD_ON == navgate_flag) 
                {
                    if (nav_currthresh != tmpcurrthresh)
                    {
                        tmpcurrthresh = nav_currthresh;
                        /* MF MRIhc12741 */
                        navigator_set_deltapixel(nav_dir*(trig_phase-tmpcurrthresh));
                    }
                }

                /* T2PREP */
                if (t2prep_flag)
                {
                    boffset(off_seqt2prep);
                    startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);
                    settrigger((SHORT)TRIG_INTERN, (SHORT)slabindex);
                    boffset(off_seqcore);
                }

                if (irprep_flag)
                {
                    IRPrep();
                    settrigger((short)TRIG_INTERN, (short)slabindex );
                    scopeoff(&seqcore);
                }
                
                /* Move navigator pulse to the front if slabtracking is ON (MRIhc07226) */
                if (slabtracking_flag) 
                { 
                    if (irprep_flag)
                    {   
                        NavigatorTipUp();
                    } 

                    /* play navigator seq and get displacement */
                    get_navigator_phase(0, mon_tr, &ref_phase0);
                    reset_for_scan();
                }

@inline SlabTracking.e SlabTrackGetDisplacement  /* MRIhc07226: navTRACK */

                /* Chem Prep Play this after IR Prep since TIs are shorter */
                if (specir_flag) 
                {   
                    SpecIRChemPrep();
                    settrigger((short)TRIG_INTERN, (short)slabindex);
                    scopeoff(&seqcore);
                }

                boffset(off_seqcore);

                exphase = 0;

                /* play out the maximum number of lines but
                   turn off data acquisition if it exceeds the
                   required number of lines for the corresponding
                   z_index */
                for (pe_index = -gated_dda; pe_index < pe_acq2; pe_index++) 
                {
                    if (pe_index == -gated_dda + 1)
                    {
                        settrigger((short)TRIG_INTERN, (short)slabindex);
                        scopeoff(&seqcore);
                    }
                    /* index to viewtab may exceed rspvus */
                    if (pe_index < 0)
                    {
                        dabview = viewtab[view_start];
                        acq_echo1 = DABOFF;
                    } else {
                        dabview = viewtab[view_start + pe_index];
                        if (dabview == 0) {
                            dabview = viewtab[view_start];
                            acq_echo1 = DABOFF;
                        } else {
                            acq_echo1 = DABON;
                        }
                    }

                    setiamp(-viewtable[dabview], &gy1, 0);
                    if (rewinder_flag) 
                    {
                        setiamp(-viewtable[dabview], &gy1r, 0);
                    }

                    /* calculate the phase offset for the slice and view */
                    /* INDEX TO PHASE SHOULD BE SLAB 0 */

                    yres_phase = phase_off[slabindex].ysign*((dabview-1)*
                                                             phase_off[slabindex].yoffs);

                    /* (MRIhc07226) Update phases here for slab tracking */
                    if (slabtracking_flag)
                    { 		    
                        yres_phase = yres_phase+(int)(nav_corr_phase_y*disp_y);
                        slab_phase = slab_phase+(int)(nav_corr_phase_z*disp_z); 
                    }

                    spoil();

                    /* (MRIhc07226) Slab tracking: restore yres_phase and slab_phase after spoil */
                    if (slabtracking_flag) 
                    {
                        yres_phase = yres_phase-(int)(nav_corr_phase_y*disp_y);
                        slab_phase = slab_phase-(int)(nav_corr_phase_z*disp_z);
                    }

                    setiamp(ia_rf1, &rf1, scanrf1_inst);

                    fgre_loaddab_echo1(slice, dabecho, dabop, dabview, acq_echo1);

                    startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);

                    /* (MRIhc07226) Slab tracking: add arr_check here */
                    if (arr_check)
                    {
                        triggerState = gettrigoccur();
                        if( triggerState == TRUE )
                        {
                            trigger_detected = TRUE;
                        }

                        if( trigger_detected ) 
                        {
                            ++num_trig;
                        }
                    }

                } /* end pe_index loop */

                /* increment view to start of next block */
                view_start += pe_acq2;  

                if (PSD_ON == navgate_flag) 
                {
                    /* (MRIhc07226) Play nav pulse at the back if slabtracking_flag is OFF */	
                    if (!slabtracking_flag) 
                    {	
                        get_navigator_phase(0, mon_tr, &ref_phase0);
                    }

                    test_rtpoint = nav_currthresh;
                    test_rtwin = nav_currwindow;

                    low_limit = test_rtpoint - test_rtwin;
                    high_limit = test_rtpoint + test_rtwin;

                    if ((ref_phase0 > low_limit) && (ref_phase0 < high_limit)) 
                    {
                        hbs_left--;
                        view_accepted++;
                    } else {
                        z_index-=1;
                        view_start -= pe_acq2;
                        view_rejected++;
                    }

                    reset_for_scan();

                    curr_eff = (float)(view_accepted) / (view_accepted+view_rejected);
                    scantime = pitslice*hbs_left/(float)(rspslq*num_outer_loops);

                    if (curr_eff > 0) 
                    {
                        scantime /= curr_eff;
                    } else {
                        /* assume 30% efficiency */
                        scantime /= 0.3;
                    }
                }
                else
                {
                    hbs_left--;
                    scantime = pitslice*hbs_left/(float)(rspslq*num_outer_loops);
                }
                setscantimeimm(pidmode, scantime, hbs_left,pitslice,opslicecnt);

                if ((PSD_ON == navsat_flag) && (PSD_ON == navgate_flag) && (PSD_ON == slabtracking_flag))
                {
                    NavigatorSat();
                }

            } /* end z-loop */
        } /* end slice loop */

        /* 3d packets must be played out at the end */
        /* initiate the 3D packets */

        boffset(off_seq3d);
        scopeoff(&seq3d);

        for (view=1;view<=rspvus; view++) 
        {
            load3d(&d3dset,view,(TYPDAB_PACKETS)DABON);
            startseq(0,(SHORT)MAY_PAUSE);
        }

        /* pass packet logic */
        scopeoff(&seqpass);
        boffset(off_seqpass);

        if(pass == (acqs-1)) 
        {
            /* Set DAB pass packet to end of scan */
            setwamp(SSPD + DABPASS + DABSCAN, &pass_pulse, 2);
        } else {
            /* Set DAB pass packet to end of pass */
            setwamp(SSPD + DABPASS, &pass_pulse, 2);
        }

        if (pass == (acqs-1)) 
        {
            pause = MAY_PAUSE;
        } else {
            if (((pass+1) % slicecnt)==0)
            {
                pause = MUST_PAUSE;	/* pause if desired */
            } else { 
                pause = AUTO_PAUSE;	/* or if required */
            }
        }
        /* load last 3d packet */
        load3d(&d3dpass,viewtab[rspvus-1],DABOFF);
        sp_sat_index = 0;
        startseq(0,(SHORT)pause);
    } /* slab loop */
    return SUCCESS;
}   /* end vast_gre_scancore() */



@rsp VASTcore_fiesta3d
STATUS
#ifdef __STDC__ 
vast_fiesta_scancore( void )
#else /* !__STDC__ */
vast_fiesta_scancore()
#endif /* __STDC__ */
{
    /* This core is a VAST acquisition scheme for gated fatsat fiesta */
    int trigger_ecg;
    int view_start;
    int receiver_phase;
    int i; 
    int rf1_amp_scale;
    int hbs_left;

    int view_accepted = 0;  /* number of view accepted*/
    int view_rejected = 0;  /* number of view rejected*/

@inline SlabTracking.e SlabTrackVariables  /* MRIhc07226: navTRACK */

    if (heart3d_flag)
    {
        rspslq = pfkz_total_unaccel;
    }

    /* MRIhc07063 - Create file handle for navigator data in VAST-FIESTA */
    if ( (PSD_ON == navgate_flag) & (nav_test>3) )
    {
#ifdef PSD_HW
    	mgd_clock_gettime (HOST_TIME_OF_DAY, &host_clock);
    	seconds = host_clock.tv_sec ;
#endif
    	sprintf(nav_filename,"/usr/g/service/log/navtest_data.%d", seconds);
    }

    printdbg("Starting vast_fiesta_scancore", debugstate);

    if(value_system_flag)
    {
        rf1_amp_scale = (int)((float)ia_rf1/(float)fiesta_gated_ramp_dda);
    }
    else
    {
        rf1_amp_scale = (int)((float)ia_rf1/(float)fiesta_gated_dda);
    }

    scopeoff(&seqcore);
    boffset(off_seqcore);

    psd_index = slabquant - 1;
    pass = 0;

    hbs_left = rspslq*num_outer_loops*slabquant;
    scantime = pitslice*hbs_left/(float)(rspslq*num_outer_loops);
    setscantimeimm(pidmode, scantime, hbs_left,pitslice,opslicecnt);

    for (slabindex = 0; slabindex < slabquant; slabindex++)
    {
        pass = slabindex;
        setfrequency(receive_freq1[slabindex], &echo1, 0);
        setfrequency(rf1_freq[slabindex], &rf1, scanrf1_inst);
        setiamp(ia_rf1, &rf1, scanrf1_inst);
        if(enable_alpha)
        {
            setfrequency(rf1_freq[slabindex],&rf1htr,scanrf1_inst); /* 3doblique - latha@mr */
            setiamp(ia_rf1htr, &rf1htr, scanrf1_inst);
        }

        dabecho = 0;
        dabslice = 0;
        exphase = 0; /* initialize */

        triggerState = gettrigoccur();
        trigger_detected = FALSE;
        look_for_trig    = TRUE;
        num_trig = 0;

        acq_echo1 = DABOFF;
        fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);
        fgre_loaddab_3d(0, DABOFF);

        dabview = viewtab[0];
        /* set slice encode to first value */
        setiamp(volumetab[0], &gzcomb, 0);
        if (zrewind_flag) 
        {
            setiamp(volumetab2[0], &gzp, 0);
        }

        setiamp(-viewtable[dabview], &gy1, 0);
        if (rewinder_flag) 
        {
            setiamp(-viewtable[dabview], &gy1r, 0);
        }

        /* MS  Half alpha Half TR */
        if(enable_alpha)
        {
            setiamp(volumetab[0], &gzcombhtr, 0);
            setiamp(volumetab2[0], &gzphtr, 0);
            ia_gzrf1htr = ia_gzrf1;
        }

        /* acquire all the low spatial frequency data first */
        view_start = 0;
        dabop = 0;

@inline SlabTracking.e SlabTrackBaselinePhase  /* MRIhc07226: navTRACK */
@inline SlabTracking.e SlabTrackGetLogicalDisp /* MRIhc07226: navTRACK */

        if ((PSD_ON == navgate_flag) && (0==slabindex)) 
        {
    	    /* initialize deltapix to 0 at the beginning (MRIhc07115) */ 
            navigator_set_deltapixel(0.0);
            navigator_reset_iter(1);
            NavigatorPlayContRf(1,0);
            navigator_reset_iter(0); 
            /* Navigator Prescan */ 
            NavigatorPlayContRf(nav_ss+nav_dda-1,1);

            /* Navigator computations */ 

            test_rtwin = fabs(nav_window);

            settrigger((short)TRIG_INTERN, (short)slabindex);
            scopeoff(&seqhistdelay);
            boffset(off_seqhistdelay);
            startseq(slabindex, (SHORT)MAY_PAUSE);
            get_navigator_histogram(&trig_phase);

            test_rtpoint = trig_phase;
            tmpcurrthresh = trig_phase;  /* initialization (MRIhc07115) */
            scopeon(&seqcore);
            boffset(off_seqcore);
            NavigatorPlayContRf(nav_ss,0);
            reset_for_scan();
        }

        /* acquire all k-y phase encoding lines as close together as possible  */

        for (sliceindex = 0; sliceindex < rspslq; sliceindex++) 
        {
            slice = slicetab[sliceindex];

            if (heart3d_flag && rvssliceenc)
            {
                slab_phase = slab_off[slabindex].zsign * ((equant-1-slice) * slab_off[slabindex].zoffs);
            } else {
                slab_phase = slab_off[slabindex].zsign * (slice * slab_off[slabindex].zoffs);
            }

            setiamp(volumetab[slice], &gzcomb, 0);
        if (zrewind_flag) 
        {
            setiamp(volumetab2[slice], &gzp, 0);
        }

            view_start = 0;

            for (z_index=0; z_index < num_outer_loops; z_index++) 
            {
                if (debug_card_sim || (trigger_detected == TRUE)) {
                    trigger_ecg = TRIG_INTERN;
                    trigger_detected = TRUE;
                } else {
                    trigger_ecg = TRIG_ECG;
                    trigger_detected = FALSE;
                }

                /* (MRIhc07226) Initialize exphase for each RR */
                exphase =0;

                acq_echo1 = DABOFF;
                fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);

                /* Turn off Gz/Gy gradient in the transient state */
                if (heart3d_flag)
                {
                    setiamp((short)(max_pg_iamp*(-a_base/loggrd.tz)), &gzcomb,0);
                    setiamp((short)(max_pg_iamp*(a_base2/loggrd.tz)), &gzp,0);     
                    setiamp(0, &gy1, 0);
                    setiamp(0, &gy1r, 0);
                }

                /* Trigger Delay Block */
                if( arr_check ) 
                {
                    ncard_delay = dda_delay - num_trig;
                    if( ncard_delay < 0 ) 
                    {
                        ncard_delay = dda_delay;
                        trigger_ecg = TRIG_ECG;
                    }
                    num_trig = 0; /* reset arr trig count */
                    settrigger((short)trigger_ecg, (short)slabindex);

                    boffset(off_seqcarddelay);
                    startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);
                    settrigger((short)TRIG_INTERN, (short)slabindex);

                    /* reinitialize trigger */
                    triggerState = gettrigoccur();
                    trigger_detected = FALSE; /* reset trigger */

                    for( i = 1; i < ncard_delay; ++i ) {
                        startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);
                    }
                } else {
                    trigger_detected = FALSE; /* reset trigger */
                    settrigger((short)trigger_ecg, (short)slabindex);

                    /* (MRIhc07226) Add slab tracking flag because NAV is played in the front */
                    boffset(off_seqcarddelay);
                    startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);
                    settrigger((short)TRIG_INTERN, (short)slabindex);

                    for( i = 1; i < dda_delay; ++i ) {
                        startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);
                    }
                }
                /* End Trigger Delay Block */

                /* update deltapix if currthresh is changed (MRIhc07115) */
                if (PSD_ON == navgate_flag) 
                {
                    if (nav_currthresh != tmpcurrthresh) 
                    {
                        tmpcurrthresh = nav_currthresh;
                        /* MF MRIhc12741 */
                        navigator_set_deltapixel(nav_dir*(trig_phase-tmpcurrthresh));
                    }
                }

                /* T2PREP */
                if (t2prep_flag)
                {
                    boffset(off_seqt2prep);
                    startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);
                    settrigger((SHORT)TRIG_INTERN, (SHORT)slabindex);
                    boffset(off_seqcore);
                }

                /* Move navigator to the front if slab tracking is ON (MRIhc07226) */
                if (slabtracking_flag) 
                { 
                    /* play navigator seq and get displacement */
                    get_navigator_phase(0, mon_tr, &ref_phase0);
                    reset_for_scan();
                }

@inline SlabTracking.e SlabTrackGetDisplacement  /* MRIhc07226: navTRACK */

                /* (MRIhc07226) Add slab tracking flag because NAV is played in the front */
                if (specir_flag) 
                {
                    SpecIRChemPrep();
                }
               
                settrigger((short)TRIG_INTERN, (short)slabindex);
                scopeoff(&seqcore);
                boffset(off_seqcore);
                
                if (enable_alpha) {
                     scopeoff(&seqhtrcore);
                     boffset(off_seqhtrcore);
                     exphase ^= 0x8000;
                     setiphase(exphase, &rf1htr, scanrf1_inst);
                     startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);
                     boffset(off_seqcore);
                }
 
                for (i=1;i<=fiesta_gated_dda;i++) 
                {
                    int temp_rf1_amp;
                    if (fiesta_rampup_type > 0) 
                    {
                        if(value_system_flag) 
                        {
                            if(i<=fiesta_gated_ramp_dda) 
                            { /* ramp up */
                                temp_rf1_amp = rf1_amp_scale * i;
                            } else { /* flat dda */
                                temp_rf1_amp = ia_rf1;
                            }
                        } else if (heart3d_flag) {
                            if (1 == fiesta_rampup_type) 
                            {
                                temp_rf1_amp = (int)( (float)ia_rf1 * (float)i
                                                       / (float)fiesta_gated_dda );
                            }
                            else if (2 == fiesta_rampup_type) 
                            {
                                temp_rf1_amp = (int)( (float)ia_rf1 / 
		                                          ( 1 + exp((fiesta_gated_dda/2.0-(float)i)/(0.1*fiesta_gated_dda))));
                            }
                            else
                            {
                                temp_rf1_amp = (int)( 0.5 * (float)ia_rf1 
                                                  * (1 - cos(M_PI*i/fiesta_gated_dda)));
                            }
                        } else {
                            temp_rf1_amp = rf1_amp_scale * i;
                        }
                    } else {
                        temp_rf1_amp = ia_rf1;
                    } 
                    setiamp(temp_rf1_amp, &rf1, scanrf1_inst);
                    exphase ^= 0x8000;
                    fgre_setiphase(rf1frqrsp,exphase);
                    startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);
                    scopeoff(&seqcore);
                }

                if(heart3d_flag)
                {
                    setiamp(volumetab[slice], &gzcomb, 0);
                    setiamp(volumetab2[slice], &gzp, 0);
                }

                acq_echo1 = DABON;
                for (pe_index = 0; pe_index < pe_acq2; pe_index++) 
                {
                    if (pe_index == 1) {
                        settrigger((short)TRIG_INTERN, (short)slabindex);
                        scopeoff(&seqcore);
                    }

                    dabview = viewtab[view_start + pe_index];
                    if (dabview >0 ) {
                        acq_echo1 = DABON;
                        setiamp(-viewtable[dabview], &gy1, 0);
                    if (rewinder_flag) 
                    {
                        setiamp(-viewtable[dabview], &gy1r, 0);
                    }
                    } else {
                        /* if view is dummy turn acq off but phaseencodes not zero */
                        acq_echo1 = DABOFF;
                        setiamp(-viewtable[20], &gy1, 0);
                    if (rewinder_flag) 
                    {
                        setiamp(-viewtable[20], &gy1r, 0);
                    }
                }

                    /* calculate the phase offset for the slice and view */
                    /* INDEX TO PHASE SHOULD BE SLAB INDEX */
                    yres_phase = phase_off[slabindex].ysign*((dabview-1)*
                                                 phase_off[slabindex].yoffs);

                    exphase ^= 0x8000;
                    fgre_setiphase(rf1frqrsp,exphase);

                    if (slabtracking_flag)
                    {
                        /* (MRIhc07226) Subtract corr_phase here for slab tracking */
                        receiver_phase = ((int)(yres_phase + slab_phase + exphase + 
                                          nav_corr_phase_z*disp_z + nav_corr_phase_y*disp_y +
                                          nav_corr_phase_x*disp_x)) & 0xFFF0;
                    } else {
                        receiver_phase = (yres_phase + slab_phase + exphase ) & 0xFFF0;
                    }

                    fgre_setiphase(echo1xtrrsp,receiver_phase);

                    fgre_loaddab_echo1(slice, dabecho, dabop, dabview, acq_echo1);

                    startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);

                    if( arr_check ) {
                        triggerState = gettrigoccur();
                        if( triggerState == TRUE ) {
                            trigger_detected = TRUE;
                        }
                        if( trigger_detected ) {
                            ++num_trig;
                        }
                    }
                } /* end pe_index loop */

                view_start +=pe_acq2; /*increment view to start of next block*/

                if(value_system_flag) 
                {
                    acq_echo1 = DABOFF;
                    fgre_loaddab_echo1(dabslice, dabecho, dabop, dabview, acq_echo1);

                    for (i=1;i<=fiesta_gated_ramp_down;i++) 
                    {
                        int temp_rf1_amp, rf1_amp_scale;

                    rf1_amp_scale = (int)(ia_rf1/fiesta_gated_ramp_down);
                    temp_rf1_amp = ia_rf1 - rf1_amp_scale * i;

                        setiamp(temp_rf1_amp, &rf1, scanrf1_inst);

                        exphase ^= 0x8000;
                        fgre_setiphase(rf1frqrsp,exphase);

                        startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);
                    }
                    setiamp(ia_rf1, &rf1, scanrf1_inst); /* restore rf1 amp */
                }

                if (PSD_ON == navgate_flag) 
                {
                    /* (MRIhc07226) Play navigator pulse at the back if slabtracking_flag is OFF */
                    if (!slabtracking_flag) {
                        get_navigator_phase(0, mon_tr, &ref_phase0);
                    }
		
                    /* Modify limits if warranted (NDG) */
                    test_rtpoint = nav_currthresh;
                    test_rtwin = nav_currwindow;

                    low_limit = test_rtpoint - test_rtwin;
                    high_limit = test_rtpoint + test_rtwin;

                    if ((ref_phase0 > low_limit) && (ref_phase0 < high_limit)) {
                        hbs_left--; 
                        view_accepted++;
                    } else {
                        z_index-=1;
                        view_start -= pe_acq2;
                        view_rejected++;
                    }

                    reset_for_scan();

                    curr_eff = (float)(view_accepted) /
                               (view_accepted+view_rejected);
                    scantime = pitslice*hbs_left/(float)(rspslq*num_outer_loops);

                    if (curr_eff > 0) {
                        scantime /= curr_eff;
                    } else {
                        /* assume 30% efficiency */
                        scantime /= 0.3;
                    }
                } /* navigator */
                else
                {
                    hbs_left--;
                    scantime = pitslice*hbs_left/(float)(rspslq*num_outer_loops);
                }
                setscantimeimm(pidmode, scantime, hbs_left,pitslice,opslicecnt);

                if (fiesta_killer_flag) 
                {
                    boffset(off_seqgzk);
                    scopeoff(&seqgzk);
                    startseq((SHORT)slabindex, (SHORT)MAY_PAUSE);
                }

                if ((PSD_ON == navsat_flag) && (PSD_ON == navgate_flag) && (PSD_ON == slabtracking_flag))
                {
                    NavigatorSat();
                }

            } /* end outer loop */
        } /* end slice-loop */

        /* 3d packets must be played out at the end */
        /* initiate the 3D packets */
        boffset(off_seq3d);
        for (view=1;view<=rspvus; view++) 
        {
            load3d(&d3dset,view,(TYPDAB_PACKETS)DABON);
            startseq(slabindex,(SHORT)MAY_PAUSE);
        }

        /* pass packet logic */
        boffset(off_seqpass);

        if(pass == (acqs-1)) {
            /* Set DAB pass packet to end of scan */
            setwamp(SSPD + DABPASS + DABSCAN, &pass_pulse, 2);
            printdbg("  End of Scan and Pass", debugstate);
        } else {
            /* Set DAB pass packet to end of pass */
            setwamp(SSPD + DABPASS, &pass_pulse, 2);
            printdbg("  End of Pass", debugstate);
        }

        if (pass == (acqs-1)) {
            pause = MAY_PAUSE;
        } else {			/* if not last pass */
            if (((pass+1) % slicecnt)==0) {
                pause = MUST_PAUSE;	/* pause if desired */
            } else {
                pause = AUTO_PAUSE;	/* or if required */
            }
        }

        /* don't load last 3d packet */
        load3d(&d3dpass,0,DABOFF);

        sp_sat_index = 0;

        startseq(0,(SHORT)pause);
    } /* slabindex loop */

    printdbg("Returning from vast_fiesta_scancore", debugstate);
    return SUCCESS;
}   /* end vast_fiesta_scancore() */

STATUS
#ifdef __STDC__ 
vast_ifir_scancore( void )
#else /* !__STDC__ */
vast_ifir_scancore()
#endif /* __STDC__ */
{
    /* This core is a VAST acquisition scheme for gated fatsat fiesta */
    int view_start;
    int receiver_phase;
    int i; 
    int temp_rf1_amp;
    int hbs_left;
  
    printdbg("Starting vast_ifir_scancore", debugstate); 

    scopeoff(&seqcore);
    boffset(off_seqcore);

    psd_index = slabquant - 1;
    pass = 0;

    setfrequency(receive_freq1[0], &echo1, 0);
    setfrequency(rf1_freq[0], &rf1, scanrf1_inst);
    setiamp(ia_rf1, &rf1, scanrf1_inst);

    dabecho = 0;
    dabslice = 0;
    exphase = 0; /* initialize */

    hbs_left = rspslq*num_outer_loops;

    acq_echo1 = DABOFF;

    /* set slice encode to first value */
    setiamp(volumetab[0], &gzcomb, 0);
    if (zrewind_flag) 
    {
        setiamp(volumetab2[0], &gzp, 0);
    }

    dabview = viewtab[0];
    setiamp(-viewtable[dabview], &gy1, 0);
    if (rewinder_flag) 
    {
        setiamp(-viewtable[dabview], &gy1r, 0);
    } 

    dabop = DABSTORE;

    fgre_loaddab_echo1(dabslice,dabecho,dabop,dabview,acq_echo1);
    fgre_loaddab_3d(0, DABOFF);

    for (sliceindex = 0; sliceindex < rspslq; sliceindex++)
    {
        view_start = 0;

        for (z_index=0; z_index < num_outer_loops; z_index++) 
        {
            exphase = 0;

            acq_echo1 = DABOFF;
            fgre_loaddab_echo1(0, 0, 0, 0, DABOFF);

            /* Resp Trigger */
            if (oprtcgate == PSD_ON)
            {
                boffset(off_seqwait_dum);
                settrigger((short) TRIG_RESP, (short) 0);
                startseq(0, (SHORT) MAY_PAUSE);
                boffset(off_seqcore);
            }
            else if ((PSD_ON == navtrig_flag) && (L_SCAN == rspent))
            {
                NavigatorPlayTrig();
            }

            /* IFIR GRx */
            settrigger((short) TRIG_INTERN, (short) 0);
            
            if (opgirmode == PSD_GIRMANUAL)
            {
                boffset(off_seqgir);
                startseq(0, (SHORT) MAY_PAUSE);
                boffset(off_seqcore);
            }
            else if (irprep_flag)
            {
                IRPrep();
            }

            if ((PSD_ON == navtrig_flag) && (PSD_ON == ifir_dnav_flag))
            {
                /* play navigator seq and get displacement */
                get_navigator_phase(0, mon_tr, &ref_phase0);
                reset_for_scan();
            }
    
@inline SlabTracking.e SlabTrackGetDisplacement  /* MRIhc07226: navTRACK */

            settrigger((short)TRIG_INTERN, (short)0);

            if (sp_sat)
            {
               SatPrep(); 
            }

            if (specir_flag) { 
                SpecIRChemPrep();
            }

            scopeoff(&seqcore);
            boffset(off_seqcore);

            for (i=1;i<=fiesta_gated_dda;i++)
            {
                if (1 == fiesta_rampup_type) 
                {
                    temp_rf1_amp = (int)( (float)ia_rf1 * (float)i
                                / (float)fiesta_gated_dda );
                }
                else if (2 == fiesta_rampup_type) 
                {
                    temp_rf1_amp = (int)( (float)ia_rf1 / 
                               ( 1 + exp((fiesta_gated_dda/2.0-(float)i)/(0.1*fiesta_gated_dda))));
                }
                else if (3 == fiesta_rampup_type)
                {
                    temp_rf1_amp = (int)( 0.5 * (float)ia_rf1 
                           * (1 - cos(M_PI*i/fiesta_gated_dda)));
                }
                else 
                {
                    temp_rf1_amp = ia_rf1;
                }
                setiamp(temp_rf1_amp, &rf1, scanrf1_inst);

                exphase ^= 0x8000;
                fgre_setiphase(rf1frqrsp,exphase);

                setiamp(0, &gy1, 0);
                if (rewinder_flag) 
                {
                    setiamp(0, &gy1r, 0);
                }

                setiamp((short)(max_pg_iamp*(-a_base/loggrd.tz)),&gzcomb,0);
                if (zrewind_flag) 
                {
                    setiamp((short)(max_pg_iamp*(a_base2/loggrd.tz)),&gzp,0);
                }

                fgre_loaddab_echo1(0, 0, 0, 0, DABOFF);
                startseq((SHORT)0, (SHORT)MAY_PAUSE);
                scopeoff(&seqcore);
            }

            for (pe_index = -ifir_dummy_pe; pe_index < pe_acq1; pe_index++) 
            {
                setiamp(ia_rf1, &rf1, scanrf1_inst);

                if (pe_index < 0 ) {
                    dabview = 0;
                    slice = 0;
                } else {
                    dabview = viewtab[view_start + pe_index];
                    slice = sliceindex;
                }
                if (dabview > 0) {
                    acq_echo1 = DABON;
                    setiamp(-viewtable[dabview], &gy1, 0);
                    if (rewinder_flag) 
                    {
                        setiamp(-viewtable[dabview], &gy1r, 0);
                    }
                    setiamp(volumetab[slice], &gzcomb, 0);
                    if (zrewind_flag) 
                    {
                        setiamp(volumetab2[slice], &gzp, 0);
                    } 
                    slab_phase = slab_off[0].zsign * (slice * slab_off[0].zoffs);
                } else {
                    /* if view is dummy turn acq off */
                    acq_echo1 = DABOFF;
                    setiamp(0, &gy1, 0);
                    if (rewinder_flag) 
                    {
                        setiamp(0, &gy1r, 0);
                    } 
                    setiamp((short)(max_pg_iamp*(-a_base/loggrd.tz)),&gzcomb,0);
                    if (zrewind_flag) 
                    {
                        setiamp((short)(max_pg_iamp*(a_base2/loggrd.tz)),&gzp,0);
                    }
                    slab_phase = 0;
                }

                /* calculate the phase offset for the slice and view */
                /* INDEX TO PHASE SHOULD BE SLAB 0 */
                yres_phase = phase_off[0].ysign*((dabview-1)*
                                                 phase_off[0].yoffs);

                exphase ^= 0x8000;
                fgre_setiphase(rf1frqrsp,exphase);

                if (ifir_dnav_flag && slabtracking_flag)
                {
                    /* (MRIhc07226) Subtract corr_phase here for slab tracking */
                    receiver_phase = ((int)(yres_phase + slab_phase + exphase +
                                      nav_corr_phase_z*disp_z + nav_corr_phase_y*disp_y +
                                      nav_corr_phase_x*disp_x)) & 0xFFF0;
                } else {
                    receiver_phase = (yres_phase + slab_phase + exphase ) & 0xFFF0;
                }
                fgre_setiphase(echo1xtrrsp,receiver_phase);

                fgre_loaddab_echo1(slice,dabecho,dabop,dabview,acq_echo1);

                startseq((SHORT)0, (SHORT)MAY_PAUSE);

            } /* end pe_index loop */

            view_start += pe_acq1;

            if (fiesta_killer_flag) { /* IQ improvement MM */

                boffset(off_seqgzk);
                scopeoff(&seqgzk);
                startseq((SHORT)0, (SHORT)MAY_PAUSE);
            }

            if (ifir_frir_flag)
            { /*IFIR STIR*/
                 boffset(off_seqfrir);
                 scopeoff(&seqfrir);
                 startseq((SHORT)0, (SHORT)MAY_PAUSE);
            }

            hbs_left--;
            scantime = pitscan*hbs_left/(float)(rspslq*num_outer_loops);
            if (PSD_OFF == navtrig_flag) {
                setscantimeimm(PSD_CLOCK_CARDIAC, scantime, hbs_left,pitslice,opslicecnt);
                if (value_system_flag) {
                    setscantimestart(); /* YMSmr12248 : YS */
                }
            }

        } /* end outer loop */
    } /* end slice-loop */

    /* 3d packets must be played out at the end */
    /* initiate the 3D packets */
    boffset(off_seq3d);
    for (view=1;view<=rspvus; view++) {
        load3d(&d3dset,view,(TYPDAB_PACKETS)DABON);
        startseq(0,(SHORT)MAY_PAUSE);
    }

    /* pass packet logic */
    boffset(off_seqpass);

    if(pass == (acqs-1)) {
        /* Set DAB pass packet to end of scan */
        setwamp(SSPD + DABPASS + DABSCAN, &pass_pulse, 2);
        printdbg("  End of Scan and Pass", debugstate);
    } else {
        /* Set DAB pass packet to end of pass */
        setwamp(SSPD + DABPASS, &pass_pulse, 2);
        printdbg("  End of Pass", debugstate);
    }

    if (pass == (acqs-1)) {
        pause = MAY_PAUSE;
    } else {			/* if not last pass */
        if (((pass+1) % slicecnt)==0) {
            pause = MUST_PAUSE;	/* pause if desired */
        } else {
            pause = AUTO_PAUSE;	/* or if required */
        }
    }

    /* don't load last 3d packet */
    load3d(&d3dpass,0,DABOFF);

    sp_sat_index = 0;

    startseq(0,(SHORT)pause);

    printdbg("Returning from vast_ifir_scancore", debugstate);

    return SUCCESS;
} /* end vast_ifir_scancore() */

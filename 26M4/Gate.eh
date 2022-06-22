#define GATE_DEBUG

/*@Start***********************************************************/
/* GEMSBG C source File
 * Copyright (C) 1997 The General Electric Company
 *
 *      File Name:  @gate.e@
 *      Developer:  Jie Shen
 *
 * $Source: gate.e $
 * $Revision: 1.0 $  $Date: 10/24/97 20:14:42 $
 *
 */

/* sccs 1.0 Initial version of CV1 -JFS */
/*@Synopsis  
  Contains the epic code to support combined ECG and respiratory gating
  */

/*@Description
  A brief description of the routines in this module:

	GateCvnit: initialization, to be invoked by cvinit(). 

	GateCveval: to be invoked by cveval(). 

	GatePulsegen: create a dummy sequence, invoked by pulsegen()

	GateRspInit:  rsp initializations, to be invoked by psdinit()

	GateWaitForValidTrig: rsp routine, to be invoked by scancore()

	Date        Author  Comments
____________________________________________________________________________

        24-Nov-97   JFS      Initial coding 
sccs1.2 13-Feb-98   JFS      Added display of view count
sccs1.3 19-Feb-98   JFS      Cleaned up GateCvinit
sccs1.4 06-Mar-98   JFS      Added CV extraRRlimit. PSD quits when # of 
                             arrhythmias > extraRRlimit. Added code to
                             to determine what caused the time out.

sccs1.5 13-Mar-98   JFS      Changed trigger window to arrhythmia rejection window
sccs1.6 26-Mar-98   JFS      MRIge45152: Removed ecgScale as the effect of arrhythmia 
                             window size on scan time is hard to estimate.
sccs1.7 01-Apr-98   JFS      MRIge45152: multiply respScale to pitscan to get the scan
                             time without respiratory gating.
sccs1.8 06-Apr-98   JFS      MRIge45313: Corrected the calculation of minimum trigger delay
       MRIge45172: Disabled resync to ECG to make time-out work, and added check for
       resp rate (the resp phase still rolls along without a valid resp trigger).
                             
sccs1.9 09-Apr-98   JFS      MRIge45172: there was about 10 seconds delay between the resp.
       rate dropping to zero and the detection of invalid resp. trigger by SPU. So abort 
       as soon as the SPU detects an invalid resp. trigger. 

       MRIge45336: Set respiratory window start (gate.respMin) to 0 and end (gate.respMax)
       to 4095 when oprtarr==0, regardless of oprtpoint, to make oprtarr=0 different from
       oprtarr=100.

sccs1.10 28-Apr-98  JFS      MRIge45583: when optdel1 was set to RR cycle time, optdel1 was
       changed to 0 in GateCveval and caused a download failure. The fix was to remove the 
       changes to optdel1, but the actual delay to be used, ncvAdjustedDelay, was still
       adjusted to be less than RR cycle time. 

sccs1.10 11-Jun-98  JFS      MRIge46182: Recalculate scan time; scanTimePerSeg is passed
       from the main PSD.

        19-Jan-1998 GFN      MRIge49784: Converted all function definitions to
                             ANSI.
        02/15/99    JAP      Modified to support pulsegen on the host.

        04/29/99    LR	      MRIge52972 - set the default value of pirtrigwinnub to 5. 
  
        08/03/01    RJF      Removed references to pgen_rsp_global.h for MGD.
                             This file in MGD would redefine SSP. A new file will 
                             be used as the RSP/pgen interface when gating is introduced. 
 
        06/14/01    NDG      MRIge67029 - Change to minimum cardiac delay advisory value. Blow away dda based calculation for navigators.
        07/24/01    NDG      MRIge68079 - Limit the maximum cardiac delay time.
        07/26/01    NDG      MRIge68154 - Total scan time (on scan screen) needs to change for navs.
        05/14/03    PL       MRIge82182 - Since navigators use vast_mode
                             exclusively, remove avail_card_time logic
*/

/*@End*********************************************************/

@global

#define GATE_ISI_START  500us
#define GATE_ISI_LEN	1000us
#define GATE_ISI_NUM	6

@cv
int ncvAdjustedDelay = 0;
int ncvGateMaxWait = 10s with {0,120s,10s,INVIS,"Max time to wait before time-out",};

int extraRRlimit = 10 with {
    0, 100, 4, VIS, "Extra RR periods allowed per scan", 
};



@host
STATUS
GateCvinit( void )
{
  if ( (exist(opcgate) == PSD_OFF) || (vast_mode == PSD_ON) ) {
     return SUCCESS;
  }

  /* initialize gating cvs */
  piadvcard = (1<<PSD_ADVISEQDELAY) + (1<<PSD_ADVEFFTR) +
      (1<<PSD_ADVMAXPHASES) + 
      (1<<PSD_ADVMAXSCANLOCS) + (1<<PSD_ADVAVAILIMGTIME);

  oparrmon=0;			/* disable oparrmon */

  /* # of RR intervals, not used */		
  pihrepnub=0;			/* gray out */		
  ophrep = 1;			

  /* Arrhythmia rejection window */
  pifcinenub    = -1;       /* change label to Arrhythmia */
  oparr = 20;			

  /* Trigger delay */
  pitdel1nub = 63;     /* bitmap for pulldown menu  */
  optdel1 = 10ms;        /* default to ms */

  /* inter-seq. delay, not used */
  pitseqnub=0;		 	/* gray out */
  optseq = 1;       		

  /* Cardiac phases */
  piphasenub=0;             /* gray out */	

  /* views per segment */
  piviewseg=0;		  /* grayed out */
  opvps = 1;
  setexist(opvps, PSD_ON);
  cvmin(opvps,1);	

  /* The following are flags for Respiratory triggering */
  if (exist(oprtcgate) == PSD_OFF){
     return SUCCESS;
  }

  /* # of Resp intervals */
  pirtrepnub = 0;      /* gray out */
  oprtrep = 1;
  setexist(oprtrep, PSD_ON);

  /* Resp. trigger point */
  pirtpointnub=30;     /* bitmap for pulldown menu  */
  oprtpoint = 15;      /* default to 15% */
  setexist(oprtpoint, PSD_ON);

  /* Resp. trigger window */
  pirtrigwinnub=5;		/* bitmap for pulldown menu  */
  oprtarr = 10;			/* default to 15% */
  setexist(oprtarr, PSD_ON);

  /* Resp. inter-seq. delay, not used */
  pirtseqnub=0;      /* gray out */
  setexist(oprttseq, PSD_ON);
  
  return SUCCESS; 
}


/*****************************************************************/
STATUS
GateCveval( int nSeg,
            float scanTimePerSeg )
{
    int periodsPerSeg;	/* # of nRrTime per segment */
    float respScale = 1.0; /* scaling factor for pitscan when resp. gating is also on */
    int nRrTime, nAdjustedDelay;
    int nPrepTime = 0;
    psd_card_hdwr_delay = 10ms;

    if ( (exist(opcgate) == PSD_OFF) || (vast_mode == PSD_ON) ) {
        return SUCCESS;
    }

    /* Validate optdel1 (from trigger to data acquisition) */
    nRrTime = 60.0e6/(float)(ophrate<=10 ? 10 : ophrate);

    /* calculate preparation time */
    if( !navigator_flag ) {
        nPrepTime = dda * exist(optr);
    }
    if( existcv(opti) && ((PSD_ON == irprep_flag) || (PSD_ON == specir_flag)) ){
        nPrepTime += exist(opti) + (int)(pw_gzrf0 / 2) + pw_gzrf0a;
    }

    /* Add new preparation sequences to this prep time (NDG) */
    if( navigator_flag ) {
        nPrepTime += psd_card_hdwr_delay + tlead + t_exa + GRAD_UPDATE_TIME;
    }

    /* calculate addjusted delay (trigger to prep sequence) */
    nAdjustedDelay = exist(optdel1) - nPrepTime;
    while( nAdjustedDelay < 0 ) {
        nAdjustedDelay += nRrTime;
    }

    nAdjustedDelay %= nRrTime;

    ncvAdjustedDelay = nAdjustedDelay;


    /* Set user interface values (min and recommended delays) */
    pitdel1nub = 3;		
    avmintdel1 = nPrepTime;  /* minimum trigger delay */
    pitdel1 = nPrepTime;     /* recommended value of optdel1 */
    cvmin(optdel1, 1000); 	/* trigger delay */

    ihtdel1 = optdel1;

    pidmode = PSD_CLOCK_CARDIAC;

    /* Calculate total scan time */
    respScale = exist(oprtcgate) ? (1.- 0.01*oprtarr) : 1.0;
    respScale = respScale<0.001 ? 1.0 : respScale; /* guard against underflow */

    nSeg = nSeg>0 ? nSeg : 1;
    periodsPerSeg = ceilf(scanTimePerSeg/nRrTime);  /* ceiling */
    scanTimePerSeg = periodsPerSeg * nRrTime;

    if (!navigator_flag)
        pitscan =  nSeg * scanTimePerSeg/(respScale);
    else
        pitscan = ((float)(rhnframes + rhhnover)/curr_eff + nav_dda + nav_ss) * 60.0s/(float)ophrate + 4*hist_wait_time;

    return SUCCESS;
} /* GateCveval() */


@rspvar
int trigCount = 0;
int arrhyCount = 0;
int DCTimeOffset = 0; 
#ifdef GATE_DEBUG
int countDelay = 0;
float avgDelay = 0.0;
float maxDelay = 0.0;
int mindelay=0;
int maxdelay=0;
#endif /* GATE_DEBUG */

int rspLoopCount=0;

@rsp
 
/*********************************************************************/
/* Defines data structure used for gating 			*/

#define	GATE_REACQUIRE	2
#define GATE_RESP	1	/* flag to enable respirtory gating */
#define GATE_CARD	2	/* flag to enable cardiac gating */
#define GATE_ARRHY	4	/* flag to enable arrhythmia rejection */
#define GATE_PLAY_DISDAQ  8	
#define GATE_DUMMY_SEQ_TR  4000	/* 4 msec */
#define GATE_RESYNC_ECG 0	/* MRIge45172: 1-resync to ECG,0-report time out */
#define GATE_RESP_RATE_MIN 3	/* minimum respiratory rate required for resp gating */



@pg 

struct gateStruct {
  int	flags;		/* enable flags */
  int	maxWait;	/* time (in TRs) to wait before time-out */

  int	respMin;	/* start phase of valid respiratory window */
  int	respMax;	/* end phase of valid respiratory window */

  int	minDelay;	/* minimum delay in msec (SPU time resolution) */
  int	maxDelay;	/* maximum delay in msec (SPU time resolution) */
  int	dummySeqTime;	/* length in usec of dummy sequence */

  int	oldTrigState;	/* old trigger state */
  int	trigCount;	/* # of triggers received so far */
  int	lastValidTrig;	/* last valid trigger # */
  int	oldArrhyState;	/* old arrhythmia state */
  int	lastArrhyTrig;	/* last arrhythmia trigger # */

  /* SPU interface */
  int* pSpuiTrigCount;   /* to spui_dpr_time_frm_trig_p, delay in ms since last trigger */
  int* pSpuiTrigOccur;   /* points to spui_dpr_trig_occur_p to SPUI_DPR_TRIG_OCCUR_P */
  int* pSpuiArrhyOccur;  /* points to SPUI_DPR_ARRYTH_OCCUR_P */
} gate;

/************************************************************************/
/* It should be called within pulsegen */
STATUS
GatePulsegen( int seqtime )
{

  if (seqtime < 1ms) return FAILURE;


  gate.dummySeqTime = seqtime;
  WAIT(SSP, gate_isi, GATE_ISI_START, GATE_ISI_LEN);
  SEQLENGTH(seqgate, RUP_GRD(gate.dummySeqTime), seqgate);
  return SUCCESS;
}


@rsp 
/************************************************************************/
/*
It should be called within scan entry before entering view or slice loops
*/

int trigger_detected;
int arrhythmiaOccurred;

extern int * spui_dpr_time_frm_trig_p;
extern int * spui_dpr_arryth_occur_p;
extern int * spui_dpr_effective_tr_p;


STATUS
GateRspInit( int options )
{
   int rrTime;

   /* sanity checks */
   int minDCTimeOffset = 0;      /* msec */
   int maxDCTimeOffset = 60000;  /* msec */

#ifdef GATE_DEBUG
   countDelay = 0;
   avgDelay = 0.0;
   maxDelay = 0.0;
   mindelay=0;
   maxdelay=0;
#endif

   trigCount = 0;
   arrhyCount = 0;

   gate.flags = options;
   gate.flags |= arr_check*GATE_ARRHY;	/* enable arrhythmia rejection via user CV3 */
   gate.flags = (opcgate==PSD_ON) ? (gate.flags|GATE_CARD)  
				  	: (gate.flags&(~GATE_CARD));
   gate.flags = (oprtcgate==PSD_ON) ? (gate.flags|GATE_RESP) 
				 	: (gate.flags&(~GATE_RESP));

   /* check some variables */
   gate.dummySeqTime = gate.dummySeqTime>1000 ? gate.dummySeqTime : 1000 ;
   gate.maxWait = ncvGateMaxWait/gate.dummySeqTime;

   gate.respMin = 0;    /* for oprtarr = 0 */
   gate.respMax = 4095;
   if ((gate.flags & GATE_RESP) && (oprtarr != 0)) { /* MRIge45336 added oprtarr!=0 */
      gate.respMin = (oprtpoint * 4095) / 100; /* starting resp. trigger value */
      gate.respMax = (((oprtpoint + (100 - oprtarr))%100) * 4095)/100;
   }

   rrTime =  60.0e6/(float)(ophrate<=10 ? 10 : ophrate);
   
   #ifdef HW_IO
   if(spui_dpr_effective_tr_p)
   {
        DCTimeOffset = *spui_dpr_effective_tr_p * 1000; /* msec to usec */
   }
   #endif

   DCTimeOffset = (DCTimeOffset < minDCTimeOffset ? minDCTimeOffset : DCTimeOffset);
   DCTimeOffset = (DCTimeOffset > maxDCTimeOffset ? maxDCTimeOffset : DCTimeOffset);
   gate.minDelay = ncvAdjustedDelay - gate.dummySeqTime;  /* in usec */
   gate.minDelay = (gate.minDelay< DCTimeOffset ? DCTimeOffset : gate.minDelay) ;
   gate.maxDelay = gate.minDelay + 2*gate.dummySeqTime;  /* in usec */
   if (gate.maxDelay>rrTime){
      gate.maxDelay = rrTime;
      gate.minDelay = gate.maxDelay - 2*gate.dummySeqTime ;
   }

   gate.pSpuiTrigCount = spui_dpr_time_frm_trig_p;
   gate.pSpuiArrhyOccur = spui_dpr_arryth_occur_p;

   gate.trigCount = 0;
   gate.lastValidTrig = 0; 
   gate.lastArrhyTrig = 0;

   trigger_detected = FALSE;

   return SUCCESS;
} /* GateRspInit() */


/**********************************************************/
static long
GetInfoFromSpu( void )
{

  trigger_detected = gettrigoccur();
     
  if ( trigger_detected == TRUE ) {
     gate.trigCount++;
     trigCount = gate.trigCount;        /* user/debug info. */
  }

  arrhythmiaOccurred = FALSE;
  #ifdef HW_IO
  if(spui_dpr_arryth_occur_p) {
        arrhythmiaOccurred = *spui_dpr_arryth_occur_p;
  }
  #endif

  if ( arrhythmiaOccurred == TRUE ) {
     gate.lastArrhyTrig = gate.trigCount;
     arrhyCount++;

     if ((gate.flags & GATE_ARRHY) && arrhyCount>extraRRlimit)
        psdexit(EM_PSD_ARRYTHMIA_ABORT, 0, "", "GetInfoFromSpu",
                                     PSD_ARG_INT, arrhyCount, 0 );
  }

  return((long)(*gate.pSpuiTrigCount * 1000));  /* msec to usec */
}


/**********************************************************/
/* Wait until a valid gate is detected or until time out.
   Returns SUCCESS if a valid gate is detected.
	   FAILURE if time out
	   GATE_REACQUIRE if arrthymia detected
*/
STATUS
GateWaitForValidTrig( void )
{
  STATUS status = SUCCESS;
  int counter, validGate;
  int reacquireTrigMax;
  int delay;
  short gatePhase, gateRespRate;
  short oldtrig;
  const short gateSlice = 0;

#ifdef GATE_DEBUG
mindelay = gate.minDelay;
maxdelay = gate.maxDelay;
#endif

  if (!(gate.flags&GATE_RESP || gate.flags&GATE_CARD))
  	return SUCCESS;

  if (gate.flags & GATE_PLAY_DISDAQ)
  {
     loaddab(&echo1,0,0,0,0, DABOFF, PSD_LOAD_DAB_ACQON|PSD_LOAD_DAB_ACQON_RBA);
     boffset(off_seqcore);
  } else {
     boffset(off_seqgate); 
  }

  /* change to TRIG_INTERN */
  gettrigger(&oldtrig, gateSlice);
  if (oldtrig != (short)TRIG_INTERN)
     settrigger((short)TRIG_INTERN, gateSlice);

  /* loop until valid gate detected or time-out */
  /* Get delay after last trigger and update trig & arrhythmic counts */
  delay = GetInfoFromSpu();		/* required to update gate.trigCount */
  reacquireTrigMax = gate.trigCount + 1;	 

  for (counter=0; counter<=gate.maxWait; counter++)
  {
     validGate = 1;

     /* check ECG gating */
     if (validGate && (gate.flags & GATE_CARD)) { 
  	delay = GetInfoFromSpu();

	validGate = (delay<=gate.maxDelay && delay>=gate.minDelay ? 1 : 0 );

	if (gate.flags & GATE_ARRHY) {  
	  validGate = (validGate && gate.trigCount>gate.lastArrhyTrig);

	  /* set re-acquire flag if arrythmia occurred during last data acquisition */
	  if (gate.lastArrhyTrig>=gate.lastValidTrig && gate.lastArrhyTrig<=reacquireTrigMax)
    	    status = GATE_REACQUIRE;
	}

     }

     /* check respiratory gating */
     if (validGate && (gate.flags & GATE_RESP) ) {	
        getrespphase(&gatePhase);
	validGate = (gate.respMax>gate.respMin) ?
		(gatePhase>=gate.respMin && gatePhase <= gate.respMax) :
		(gatePhase>=gate.respMin || gatePhase <= gate.respMax) ;

        getresprate(&gateRespRate);   /* MRIge45172 */
        if (gateRespRate < GATE_RESP_RATE_MIN)
            psdexit(EM_PSD_NO_RESP_RATE, 0, "", "GateWaitForValidTrig - Time out", 0 );
     }

     if (validGate) break;

     /* no valid gate dectected yet */
     if (gate.flags & GATE_PLAY_DISDAQ) {
	spoil(); 
	chop_phase = -chop_phase;
     } else if (delay>gate.maxDelay && GATE_RESYNC_ECG)	
	settrigger((short)TRIG_ECG, gateSlice);  /* trigger off ECG */
     else
    	settrigger((short)TRIG_INTERN, gateSlice);

     startseq(gateSlice,(SHORT)MAY_PAUSE);   

  } /* for (counter<=gate.MaxWait) */

  boffset(off_seqcore);

  rspLoopCount = counter;	/* for debugging */
  if (counter > gate.maxWait) {	/* time out */
    status = FAILURE;
    psdexit(EM_PSD_NO_HRATE,0,"","GateWaitForValidTrig - Time out",PSD_ARG_INT, counter, 0);
  } else
    gate.lastValidTrig = gate.trigCount;

  settrigger((short)TRIG_INTERN, gateSlice);

#ifdef GATE_DEBUG
  maxDelay = maxDelay>delay ? maxDelay : delay;
  avgDelay = (avgDelay*countDelay + delay)/(countDelay+1);
  countDelay++;
#endif
  return status;
} /* GateWaitForValidTrig() */

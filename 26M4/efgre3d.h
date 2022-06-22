/*
 * GE Medical Systems
 * Copyright (C) 1999 The General Electric Company
 *  
 * efgre3d.h
 *
 * This file is the include file for efgre3d.e. This has both the host and ipg parts.
 * Later this has to be bifurcated into two parts which will go in to the host and
 * ipg parts respectively.
 *  
 * Language : ANSI C
 * Author   : Gabriel Fernandez
 * Date     : 25/Nov/1998
 */
/* do not edit anything above this line */

/*
 Version      Date      Author      Description
------------------------------------------------------------------------------
 1.0       25-Nov-1998  CMC         Added the host and ipg parts.
 3.0       04-Dec-1998  CMC         Added void in the arguemnt of GateCvinit.
           15-Feb-1999  JAP         Changed prototype for reset_for_scan.
           06-Apr-1999  JAP         Added calcPulseParams().
           09-Apr-1999  GFN         Removed functions already provided by
                                    psd_proto.h.
           05-Mar-2003  KVA         Added ectrickscore MRIge81518
           11-Feb-2004  SVR         Added fgre_loadtreg().
           15-Dec-2005  CRM         MRIhc12606 - Removed unused argument to
                                    ugfsf_view_order().
           15-Sep-2006  TS          MRIhc18005 - Changed fgre_loaddab_echo1 
                                    and echo2 to add R1 and Hub index control            
           07-Jan-2008  CRM         MRIhc31929 - Add loaddab wrapper functions
                                    for compatibility with previous releases.
           25-Sep-2010  KA          MRIhc52512 - Added new argument for number
                                    of shots in fgre_loaddab_echo2 functions.
           02-Jun-2011  KA          MRIhc56341 - Added isReferenceLine().

*/

#ifndef	efgre3d_h
#define efgre3d_h

/* Functions defined in Gate.eh */
STATUS GateCvinit(void);
STATUS GateCveval(int nSeg, float scanTimePerSeg);
STATUS GatePulsegen(int seqtime);
STATUS GateRspInit(int options);
STATUS GateWaitForValidTrig(void);

/* ANSI declarations for efgre3d.e */

/* Host Part */
void myscan3d(void);
STATUS cveval1(void);
STATUS satact_f3d(void);
STATUS saterr_f3d(void);
STATUS mintefgre(int *Minte, int *Rd1a, int *Rd1b, int *tfeextra, int *a_pwgxw, int *d_pwgxw,
                 float *ampgx1, int *a_pwgx1, int *c_pwgx1, int *d_pwgx1, float *ampgxfc, int *a_pwgxfc,
                 int *c_pwgxfc, int *d_pwgxfc, float fecho_factor, int c_pwgxwl, int c_pwgxw,
                 int c_pwgxwr, float ampgxw, int Trf1b, int fctype, int minseq1, int minseq3 );
STATUS fwphase(INT *actte,INT *fullteflag,INT mintefe,INT mintenfe,INT Llimte1,INT Llimte2,
               INT Llimte3,INT Ulimte1,INT Ulimte2,INT Ulimte3);
STATUS turbofilter(FILTER_INFO *echo1rtf, FLOAT bandwidth, INT outputs, FLOAT *bw_tmp);
void calc_xresfn(int *Xres, float *Fnecholim, int OPxres, float *Act_Echofrac);
STATUS setburstmode(int burstmode);
void dump_filter(PSD_FILTER_GEN *spec);

STATUS arc_init( void );
STATUS bravo_init ( void );
STATUS cosmic_init( void );
STATUS labrava_init( void );
STATUS quickstep_init( void );
STATUS multiEcho_init( void );
STATUS vstrte_init ( void );
STATUS multiEcho_eval( void );
STATUS ftmra_satact_on( void );
STATUS scale_grad( void );
STATUS SpecIRSlorder( int *num_alphas, int *alpha0 );
STATUS ftmra_satact_off( void );
int calc_optimal_fa_idealiq( int TR );
STATUS disco_init( void );
STATUS cine3d_init( void );
float calc_nav_eff( const float window );
void SaveGradOptCoefficients( void );
void RestoreGradOptCoefficients( void );
STATUS sat_flip_gre(float T1, float T2s, float *satflip, float Tcross, float TR, float exflip);

/* IPG Part */
void ssisat( void );
STATUS spoil(void);
void IRPrep(void);
STATUS SatPrep(void);
STATUS ChemPrep(void);
STATUS SpecIRChemPrep(void);
STATUS PlayDisdaq(int NumDisdaqs);
STATUS PlayDisdaqIntleave(int NumDisdaqs);
STATUS set_clock_for_total_trigger_delay_time(void);
STATUS play_trigger_delay_silent_countdown(void);
STATUS reset_clock(void);
STATUS setmask_clock(void);
STATUS scandelay0(void);
STATUS scandelay1(void);
STATUS scandelay2(void);
STATUS osfp_prep(int flag);
STATUS delay_end_segment(void);
STATUS execute_slice_loop(int ntimes,int flag);
void reset_for_scan(void);

/* SVBranch Smart Burst Mode */
void sbm_dummy(void);
int irslice(int index);

STATUS fgre_loaddab_3d( long view, TYPDAB_PACKETS acqon_flag);
STATUS fgre_loadtreg( WF_PULSE_ADDR pulse, LONG view, TYPDAB_PACKETS acqon_flag);
STATUS fgre_setiamp( INT amplitude, WF_PULSE_ADDR pulse );
STATUS fgre_setiphase(INT pulse, LONG phase);
STATUS fgre_loaddab_echo1( LONG slice, LONG echo, LONG oper, LONG view,
                           TYPDAB_PACKETS acqon_flag );
STATUS fgre_loaddab_echo1_rfhub( LONG slice, LONG echo, LONG oper, LONG view, 
                                 TYPDAB_PACKETS acqon_flag, LONG hubIndex,
                                 LONG r1Index, LONG hubctrlmask );
STATUS fgre_loaddab_echo2( LONG slice, LONG startecho, LONG numecho, LONG nshots,
                           LONG oper, LONG view, TYPDAB_PACKETS acqon_flag );
STATUS fgre_loaddab_echo2_rfhub( LONG slice, LONG startecho, LONG numecho, LONG nshots,
                                 LONG oper, LONG view, TYPDAB_PACKETS acqon_flag,
                                 LONG hubIndex, LONG r1Index, LONG hubctrlmask );
STATUS fgre_loaddab_echoN( LONG slice, LONG echo, LONG etl_echo, LONG oper, LONG view,
                           TYPDAB_PACKETS acqon_flag );
STATUS fgre_loaddab_echoN_rfhub( LONG slice, LONG echo, LONG etl_echo, LONG oper, LONG view,
                                 TYPDAB_PACKETS acqon_flag, LONG hubIndex,
                                 LONG r1Index, LONG hubctrlmask );

STATUS RTIA_spoil(void);
STATUS scancore(void);
STATUS scancore_ZY(void);
STATUS ugfsf_view_order(INT *dab_view, const INT curshot, const INT num_sht, const INT curview,
                        const INT tot_vus, const INT full_ky_view,
                        const INT view2center, const INT vieworder_flag);
STATUS set_zero_encode(void);
STATUS ectrickscore(void);
STATUS discocore(void);
STATUS ecg_scancore_YZ(void);
STATUS ecg_scancore_ZY(void);
STATUS scancoreRTIA_2D(void);
STATUS scancoreRTIA_3D(void);
void load_SmartPrep_RTPtask(void);
STATUS ps2core(void);
STATUS set_rf1frequency(INT freq,  LONG n_inst);
STATUS set_echo1frequency(INT freq, INT n_inst);
STATUS set_echo2frequency( INT freq, INT n_inst);
STATUS PlayHard180(void);
STATUS multiphase(void);
#ifdef PSD_IPG_DEBUG
void psdisiupdate( void );
#endif /* PSD_IPG_DEBUG */
STATUS testcore(void);
STATUS isReferenceLine(int view, int slice);
void dummylinks();
STATUS SWIFT_coilsw(int rightorleft, SEQUENCE_ENTRIES seqoffset);
#endif /* efgre3d_h */


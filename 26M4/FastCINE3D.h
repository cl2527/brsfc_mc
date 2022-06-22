/*
 * Copyright (c) 2016 by General Electric Company. All Rights Reserved.
 */

/*
 * \file FastCINE3D.e
 *
 * 3DCINE / 4DFLOW with kt ARC for
 * time-resolved imaging using
 * variable-density viewtable with
 * k-t acceleration .
 *
 * @author  Peng Lai, Ann Shimakawa
 * @since 26.0
 */

/*
 * Comments:
 * Date (dd mmm yyyy) Author (or Initials)
 * Comment
 *
 * 10 Mar 2016  PL/ AS
 * HCSDM00397174 Initial version.
 */

#ifndef	FastCINE3D_h
#define FastCINE3D_h

#include "FastCINE3D_support.h"


/* Host Part */
STATUS mintefgrePC(int *Minte,int *Rd1a, int *Rd1b, int *tfeextra, int *a_pwgxw, int *d_pwgxw, 
              float *amp_gx1u, float *amp_gx1d, int *a_pwgx1, int *c_pwgx1, int *d_pwgx1,
              float *amp_gxfcu, float *amp_gxfcd, int *a_pwgxfc, int *c_pwgxfc, int *d_pwgxfc,
	      float *fl_width,  float fecho_factor,  int c_pwgxwl, int c_pwgxw, int c_pwgxwr, 
              float ampgxw,  int Trf1b, float PhConst, INT minseq1, INT minseq3 );

STATUS fcine_estnviews_fullk(short Nky, short Nkz, short cal_ky, short cal_kz,
        int *fullkviews, int *fullkvviews_cal);


/* IPG Part */

LONG get_pos_isi7(void);
STATUS turnoff_isi7(void);

STATUS fgre_loaddab_cine( LONG Ky, LONG Kz, LONG Phase, LONG viewInCycle, LONG echo,
                           LONG triggerDelay ,TYPDAB_PACKETS acqon_flag );
STATUS fgre_loaddab_cine_rfhub( LONG Ky, LONG Kz, LONG Phase, LONG viewInCycle, LONG echo,
                                 LONG triggerDelay, TYPDAB_PACKETS acqon_flag, LONG hubIndex,
                                 LONG r1Index, LONG hubctrlmask );

STATUS loadfcine3D( const INT arr, const INT op, const INT minTrig, const INT n_tr,   
		const INT cycDur, const INT extra_views,const TYPDAB_PACKETS acqon_flag );
STATUS setCineCycleOn( const TYPDAB_PACKETS acqon_flag);
LONG get_pos_isi7(void);
STATUS WaitForECGTrigCine(void);
STATUS check_arrhythmia( void );       
void fcine_ssiupdate( void );
void fcine_isiupdate( void );
void fcine_getviewtable_ktARC( int *dabview, int *slice, short nt, int view );
STATUS scancore_fcine_ssfp_ktARC( void );


#endif /* FastCINE3D_h */


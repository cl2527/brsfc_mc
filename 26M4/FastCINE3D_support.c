/*
 * Copyright (c) 2016 by General Electric Company. All Rights Reserved.
 */

/*
 * \file FastCINE3D_support.c
 *
 *  This is the source file for FastCINE3D  support routines.
 * 
 * @author Peng Lai / Ann Shimakawa 
 * @since 26.0
 */

/*
 * Comments:
 * Date (dd mmm yyyy) Author (or Initials)
 * Comment
 *
 * 10 Mar 2016  PL/ AS
 * HCSDM00397174 Initial version.
 *
 */

#include "support_decl.h"
#include "efgre3d_support.h"
#include "FastCINE3D_support.h"
#include "stddef_ep.h"

#include <epic_struct.h>
#if defined(MGD_TGT) && defined(PSD_HW)
#include "valuesMGD.h"
#endif /* MGD_TGT && PSD_HW */
#include <pgen_tmpl.h>
#include <epicfuns.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#if defined(IPG_TGT) || defined(MGD_TGT)

/*
 *  fcine_genacceltable_vdkt
 *
 * Generate kspace ring-specific acceleration factors for
 * variable-density kt sampling so net acceleration matches U/I selection
 *
 *  @param[out] short* krAccel_vdkt - acceleration factors of k-space rings from center to outer
 *  @param[out] short* krOffset_vdkt - offsets for k-space rings in the view table from center to outer
 *  @param[in]  int accel - net acceleratoin factor
 *  @param[in]  int accelLower - lower boundary of variable density acceleraton
 *  @param[in]  int accelUper - upper boundary of variable density acceleration
 *  @param[in]  int vieworder_len - total number of views in a k-space region
 *  @return status of function (SUCCESS or FAILURE)
 */
STATUS fcine_genacceltable_vdkt(short* krAccel_vdkt, short* krOffset_vdkt, int accel, int accelLower, int accelUpper, short vieworder_len)
{
    int i=0, n=0;
    int accel_sta=0, accel_end=0, accel_adjust=0, adjust_range=0, adjust_needed=0;
    float val1=0.0, val2=0.0, kr=0.0, slope_kr=0.0, trans_kr=0.0;
    
    accel_sta = IMin(2, accel, accelLower);
    accel_end = IMax(2, accel, IMin(2, accelUpper, 2*accel-accel_sta));
    accel_sta = (accel==accel_end)? accel:accel_sta;
    
    accel_adjust = 0;
    adjust_range = accel - accel_sta;
    
    while(accel_adjust <= adjust_range)
    {
        memset(krOffset_vdkt, 0, 20*sizeof(short));
        memset(krAccel_vdkt, 0, 20*sizeof(short));
        
        adjust_needed = 0;
        
        n = accel_end - accel_sta + 1;
        for(val1=val2=0.0, i=0, kr=(float)accel_sta; kr<=(float)accel_end; ++i, kr+=1.0)
        {
            val1 += 1.0/kr;
            val2 += ((float)i - ((float)n-1.0)/2.0) / kr;
        }
        slope_kr = (1.0/(float)accel - val1/(float)n) / val2;
        trans_kr = 1.0/(float)n - ((float)n-1.0)/2.0*slope_kr;
        
        krOffset_vdkt[0] = 0;
        for(i=0, val1=0.0; i<n; i++)
        {
            krAccel_vdkt[i] = accel_sta + i;
            
            val2 = trans_kr + (float)i*slope_kr;
            if(val2 <= 0.0)
            {
                adjust_needed = 1;
                break;
            }
            
            val1 += val2;
            
            krOffset_vdkt[i+1] = floor(val1 * (float)vieworder_len + 0.5);
        }
        
        if(adjust_needed == 0)
        {
            krOffset_vdkt[n] = vieworder_len;
            krOffset_vdkt[n+1] = -1; /*set boundary*/
            
            break;
        }
        else
        {
            ++accel_adjust;
            
            accel_sta = IMin(2, accel, accelLower);
            accel_end = IMax(2, accel, IMin(2, accelUpper, 2*accel-accel_sta));
            accel_sta = (accel==accel_end)? accel:accel_sta;
        }
    }
    
    if(accel_adjust > adjust_range)
    {
        printf("fcine_genacceltable_vdkt: failed to calculate vdkt acceleration range.\n");
        
        return FAILURE;
    }
    
    return SUCCESS;
}

/*
 *  fcine_genkmask_vdktARC
 *
 *  Generate variable-density kt sampling mask for a specific cardiac phase
 *
 *  @param[out] short* maskKTarc - [ky,kz] sampling mask at t_index
 *  @param[in]  short Nky - phase encoding / ky size
 *  @param[in]  short Nkz - slice encoding / kz size
 *  @param[in]  short t_index - cardiac phase number
 *  @param[in]  ViewTable_kyz* pViewOrder_vdkt_outer - pre-sorted k-space rings in outer k-space
 *  @param[in]  ViewTable_kyz* pViewOrder_vdkt_cal - pre-sorted k-space rings in calibration k-space
 *  @param[in]  short* pkrOffset_vdkt_outer - offsets to outer k-space rings in pViewOrder_vdkt_outer
 *  @param[in]  short* pkrOffset_vdkt_cal - offsets to calibration k-space rings in pViewOrder_vdkt_cal
 *  @param[in]  short* pkrAccel_vdkt_outer - acceleration factors of outer k-space rings
 *  @param[in]  short* pkrAccel_vdkt_cal - acceleration factor of calibration k-space rings
 *  @param[in]  short* pktShift_vdkt - view shifting at each cardiac phase for time-shifted sampling
 *  @return     short totalviews - total number of sampled views at the current cardiac phase
 */
short fcine_genkmask_vdktARC(short *maskKTarc, short Nky, short Nkz, short t_index,
                             ViewTable_kyz* pViewOrder_vdkt_outer, ViewTable_kyz* pViewOrder_vdkt_cal,
                             short* pkrOffset_vdkt_outer, short* pkrOffset_vdkt_cal, 
                             short* pkrAccel_vdkt_outer, short* pkrAccel_vdkt_cal, 
                             short* pktShift_vdkt)
{
    int nseg=0, accel=0, off_t=0, off_kr=0, nview=0, ind=0, centky=0, centkz=0;
    short totalviews = 0;
    float len_subring=0.0;
    
    centky = (int)(Nky/2.0);
    centkz = (int)(Nkz/2.0);
    
    for(nseg=0; pkrOffset_vdkt_outer[nseg+1]>0; ++nseg)
    {
        accel = pkrAccel_vdkt_outer[nseg];
        if(accel < 1) 
        {
            break;
        } 
        off_t = pktShift_vdkt[(accel-1)*MAXACCEL_VDKT + t_index%accel];
        
        len_subring = (float)(pkrOffset_vdkt_outer[nseg+1] - pkrOffset_vdkt_outer[nseg]) / (float)accel;
        
        for(nview=0; nview<=len_subring; ++nview)
        {
            off_kr = pktShift_vdkt[(accel-1)*MAXACCEL_VDKT + (nview + off_t)%accel];
            ind = pkrOffset_vdkt_outer[nseg] + nview + (int)((float)off_kr * len_subring + 0.5);
            ind = pViewOrder_vdkt_outer->kz[ind] * Nky + pViewOrder_vdkt_outer->ky[ind];
            
            if(maskKTarc[ind] == 0)
            {
                maskKTarc[ind] = 1;
                ++totalviews;
            }
        }
    }
    
    for(nseg=0; pkrOffset_vdkt_cal[nseg+1]>0; ++nseg)
    {
        accel = pkrAccel_vdkt_cal[nseg];
        if(accel < 1)
        {
            break;
        } 
        off_t = pktShift_vdkt[(accel-1)*MAXACCEL_VDKT + t_index%accel];
        
        len_subring = (float)(pkrOffset_vdkt_cal[nseg+1] - pkrOffset_vdkt_cal[nseg]) / (float)accel;
        
        for(nview=0; nview<=len_subring; ++nview)
        {
            off_kr = pktShift_vdkt[(accel-1)*MAXACCEL_VDKT + (nview + off_t)%accel];
            ind = pkrOffset_vdkt_cal[nseg] + nview + (int)((float)off_kr * len_subring + 0.5);
            ind = pViewOrder_vdkt_cal->kz[ind] * Nky + pViewOrder_vdkt_cal->ky[ind];
            
            if(maskKTarc[ind] == 0)
            {
                maskKTarc[ind] = 1;
                ++totalviews;
            }
        }
    }
    
    /* center k-space always sampled*/
    ind = centkz * Nky + centky;
    if(maskKTarc[ind] == 0)
    {
        maskKTarc[ind] = 1;
        ++totalviews;
    }
    
    return totalviews;
}

/*
 *  fcine_genvieworder_ktARC
 *
 *  Generate viewtable containing view order for 3D cine with kt ARC
 *  Currently support only full NEX along ky or kz
 *
 *  @param[in]  int start_totalviews - starting estimate for total views in the k-space (without NEX)
 *  @param[in]  int start_maxAphase - starting estimate for max aphase
 *  @param[in]  int accel_ktStride -  HyperKat acceleration (from U/I) or net acceleration in outer k-space
 *  @param[in]  int accel_ktStride_cal - net acceleration in calibration region
 *  @param[in]  int Cal_ky - calibration size along ky
 *  @param[in]  int Cal_kz - calibration size along kz
 *  @param[in]  int NkyLines - phase encoding / ky size
 *  @param[in]  int NkzLines - slice encoding / kz size
 *  @param[in]  float fovVthickScale - kz / ky normalization factor for k-space distance calculation
 *  @param[in]  int ViewsPerSeg - views per segment
 *  @param[in]  int ElliptCal - elliptical cal shape flag
 *  @param[in]  int cutCorner - elliptical k-space sampling flag
 *  @param[in]  int RespPerCent - kspace area for resp-nex in %
 *  @param[in]  int respNex - net NEX factor in RespPerCent area
 *  @param[in]  int yz_sort_order - ky or kz first view order
 *  @param[in]  int ktsamp_mode - kt Sample mode (KT_MODE, VDKT_MODE, ARC_MODE)
 *  @param[in]  int kBandWidth - width of each k-space band for sorting in view ordering
 *  @param[in]  int kRewFlag - revinding view order flag
 *  @param[out]  INT* cine3dTotalviews - total number of views in a cardiac phase
 *  @param[out]  INT* cine3dMaxAphases - number of cardiac phases in pviewtable_kt
 *  @param[out]  ViewTable_kyz* pviewtable_kt - outcome view table for ktARC sampling
 *  @return status of function (SUCCESS or FAILURE)
 */
STATUS fcine_genvieworder_ktARC( int start_totalviews, int start_maxAphase, 
       int accel_ktStride, int accel_ktStride_cal, int Cal_ky, int Cal_kz,
       int NkyLines, int NkzLines,  float fovVthickScale,
       int ViewsPerSeg,  int ElliptCal, int cutCorner, 
       int RespPerCent, int respNex, int yz_sort_order,
       int ktsamp_mode, int kbandWidth, int kRewFlag, 
       INT *cine3dTotalviews, INT *cine3dMaxAphases, ViewTable_kyz* pviewtable_kt )
{
    short ndim1=0, ndim2=0;
    short nt=0, nv=0, nk1=0, nk2=0, nk2b=0, maskoffset=0, offset=0;
    float *viewtable_k1, *viewtable_k2;
    short *mask_ktarc, *maskpos, *r_traj;
    short round_segs=0, round_totalviews=0, fullk_views=0, fullk_segs=0;
    short nk1_ran[2], nk2b_ran[2], nk_inc[2], nk1_opt=0, nk2b_opt=0;
    float *y_list, *z_list;
    
    /* center k-space multi-nex acq */
    float *RespFactor;
    short NCentKRect=0, NCentKRamp=0, pcal_ky=0, pcal_kz=0;
    int k_nex=0, nrep=0, ref_ind=0;
    
    /*optimal k-t shift for variable density kt sampling */
    short *ktShift_vdkt;

    /*  sorted kykz list for variable density kt sampling  */
    ViewTable_kyz ViewOrder_vdkt, ViewOrder_vdkt_outer, ViewOrder_vdkt_cal;
    short krOffset_vdkt_outer[20], krOffset_vdkt_cal[20], krAccel_vdkt_outer[20], krAccel_vdkt_cal[20];
    
    NCentKRamp = 0;
    NCentKRect = 0;
    fullk_views = 0;
    RespFactor = NULL;
    ktShift_vdkt = NULL;
    
    ViewOrder_vdkt_outer.len = 0;
    ViewOrder_vdkt_cal.len = 0;
    
    ViewOrder_vdkt_cal.ky = NULL;
    ViewOrder_vdkt_cal.kz = NULL;
    ViewOrder_vdkt_outer.ky = NULL;
    ViewOrder_vdkt_outer.kz = NULL;
    
    r_traj = NULL;
    maskpos = NULL;
    mask_ktarc = NULL;

    viewtable_k1 = NULL;
    viewtable_k2 = NULL;
    y_list = NULL;
    z_list = NULL;
    
    for(nt=0; nt<MAX_APHASE_3DCINE; nt++)
    {
        pviewtable_kt[nt].len = 0;
    }
    for (nt=0; nt<20; nt++)
    {
        krOffset_vdkt_outer[nt]=0;
        krOffset_vdkt_cal[nt]=0;
        krAccel_vdkt_outer[nt]=0;
        krAccel_vdkt_cal[nt]=0;
    }

    /* estimate totalviews without center k-space respiratory gating or nex */
    
    pcal_kz= (short)(IMin(2, Cal_kz, NkzLines));
    pcal_ky = (short)Cal_ky;
    
    ndim1 = (yz_sort_order)? (NkyLines):NkzLines;
    ndim2 = (yz_sort_order)? NkzLines:(NkyLines);

    
    /* ARC sampling */
    /* generate view-ordered full kspace sampling table */
    if( (ktsamp_mode==VDKT_MODE) || ((RespPerCent > 0) && (RespPerCent < 100)))
    {

        if(fcine_prepviewtable_fullk(NkyLines, NkzLines, pcal_ky, pcal_kz,  ktsamp_mode,
             fovVthickScale, ElliptCal, cutCorner,  RespPerCent, accel_ktStride, accel_ktStride_cal, 
             &ViewOrder_vdkt, &ViewOrder_vdkt_outer, &ViewOrder_vdkt_cal, krOffset_vdkt_outer, krOffset_vdkt_cal, 
             krAccel_vdkt_outer, krAccel_vdkt_cal) == FAILURE)
        {
            return FAILURE;
        }
    }
    
    /* generate sorted trajectory for phase-by-phase view sorting */
    if((RespPerCent > 0) && (RespPerCent < 100))
    {
        fullk_views = ViewOrder_vdkt.len;
        fullk_segs = (short)ceil( (float)fullk_views / (float)ViewsPerSeg );
        
        r_traj = (short*)AllocNode(fullk_views * sizeof(short));
        if (NULL == r_traj)
        {
            printf(" genviewOrder: Unable to allocate memory (AllocNode) for r_traj!\n");
            return FAILURE;
        }

        maskpos = (short*)AllocNode(fullk_views * sizeof(short));
        if (NULL == maskpos)
        {
            printf(" genviewOrder: Unable to allocate memory (AllocNode) for maskpos!\n");
            return FAILURE;
        }

        
        /*find out the center-out kr trajetory & the corresponding offset in 2D k-space mask*/
        for(nk1 = 0; nk1 < fullk_views; ++nk1)
        {
            nk2 = ViewOrder_vdkt.ki[nk1];
            
            r_traj[nk2] = nk1;
            maskpos[nk2] = ViewOrder_vdkt.kz[nk1] * (NkyLines) + ViewOrder_vdkt.ky[nk1];
        }
        
        /*extend the center k-space region to 2x along ky & kz and linearly ramp-down the respiratory factor*/
        /*NCentKRamp must >= NCentKRect*/
        NCentKRect = (short)((float)RespPerCent / 100.0 * (float)start_totalviews);
        NCentKRamp = (short)((float)IMin(2, 100, 2*RespPerCent) / 100.0 * (float)start_totalviews);
        
        if(NCentKRect > RESP_CENTK_MIN)
        {
            RespFactor = (float*)AllocNode(NCentKRamp*sizeof(float));
            if (NULL == RespFactor)
            {
                printf(" genviewOrder: Unable to allocate memory (AllocNode) for RespFactor!\n");
                return FAILURE;
            }
            if (fcine_genrespmap(ViewOrder_vdkt.kr, r_traj, RespFactor, NCentKRamp, NCentKRect, 
                    (float)respNex) == FAILURE)
            {
                return FAILURE;
            }
        }
        else
            NCentKRect = NCentKRamp = 0;
        
        FreeNode(ViewOrder_vdkt.kr);
        FreeNode(ViewOrder_vdkt.ki);
    }
    else if(RespPerCent == 100)

    {
        NCentKRect = NCentKRamp = start_totalviews;
        fullk_views = ndim1 * ndim2; /*include all locations for nex*/
    }
    
    /* Initial estimate for total views per phase does not include temporal k-space criteria for view selection   */
    /* Estimate is  w/in 10%, therefore, to ensure sufficient memory for each phase, memory allocation            */
    /* increased by 20% the number of views / phase to allocate sufficient 					  */
 
    round_totalviews = (short)((start_totalviews + NCentKRect*(respNex-1)) * 1.2);
    round_segs = (short)ceil( (float)round_totalviews / (float)ViewsPerSeg );
    round_totalviews = (short) ( round_segs * ViewsPerSeg );
    
    y_list = (float*)AllocNode(round_totalviews*sizeof(float));
    if (NULL == y_list)
    {
        printf(" genviewOrder: Unable to allocate memory (AllocNode) for y_list!\n");
        return FAILURE;
    }
    z_list = (float*)AllocNode(round_totalviews*sizeof(float));
    if (NULL == z_list)
    {
        printf(" genviewOrder: Unable to allocate memory (AllocNode) for z_list!\n");
        return FAILURE;
    }
 
    /* for ARC, reference to viewtable at nt=0 for all nt's.*/
    *cine3dMaxAphases = (ktsamp_mode == ARC_MODE)? 1:start_maxAphase;
    mask_ktarc = (short*)AllocNode(ndim1*ndim2*sizeof(short));
    if (NULL == mask_ktarc)
    {
        printf(" genviewOrder: Unable to allocate memory (AllocNode) for mask_ktarc!\n");
        return FAILURE;
    }

    
    /* ARC sampling; for ARC, viewtable is generated only for nt=0 and used for all nt's.*/
    for (nt=0, *cine3dTotalviews = 0; nt< *cine3dMaxAphases; nt++)
    {
        memset( mask_ktarc, 0, ndim1*ndim2*sizeof(short) );
        
        if(ktsamp_mode == VDKT_MODE)
        {
            if(ktShift_vdkt == NULL)
            {
                /* find optimal ktshift for vdkt */
                ktShift_vdkt = (short*)AllocNode(MAXACCEL_VDKT*MAXACCEL_VDKT*sizeof(short));
                if (NULL == ktShift_vdkt)
                {
                    printf(" genviewOrder: Unable to allocate memory (AllocNode) for ktShift_vdkt!\n");
                    return FAILURE;
                }
                fcine_OptiKrShift_vdktARC(ktShift_vdkt);
            }
            
            pviewtable_kt[nt].len = fcine_genkmask_vdktARC(mask_ktarc, NkyLines, NkzLines, nt, &ViewOrder_vdkt_outer, &ViewOrder_vdkt_cal, krOffset_vdkt_outer, krOffset_vdkt_cal, krAccel_vdkt_outer, krAccel_vdkt_cal, ktShift_vdkt);
        }
        else
        {
            pviewtable_kt[nt].len = fcine_genkmask_ktARC(mask_ktarc, NkyLines, NkzLines, pcal_ky, pcal_kz, nt,
				accel_ktStride, accel_ktStride_cal, ElliptCal, cutCorner);
        }
        
        if(NCentKRamp > 0)
        {
            for(nk1=0, nv=0; (nv<NCentKRamp) && (nk1<fullk_views); ++nk1)
            {
                nk2 = (RespPerCent == 100)? nk1:maskpos[nk1];
                
                if(mask_ktarc[nk2] == 1)
                {
                    mask_ktarc[nk2] = (RespPerCent < 100)? (short)RespFactor[nv++]:respNex;
                }
            }
        }
        
        viewtable_k1 = (yz_sort_order)? y_list:z_list;
        viewtable_k2 = (yz_sort_order)? z_list:y_list;
        
        nk1_ran[0] = 0;
        nk1_ran[1] = ndim1-1;
        nk2b_ran[0] = 0;
        nk2b_ran[1] = kbandWidth-1;
        nk_inc[0] = 1;
        nk_inc[1] = -1;
       
 
        for (nk2=0, nv=0, k_nex=0; nk2<ndim2; nk2+=kbandWidth)
        {
            nk1_opt = (kRewFlag)? ((INT)floor((double)nk2/(double)kbandWidth)%2):0;
            
            for (nk1=nk1_ran[nk1_opt]; nk1*nk_inc[nk1_opt]<=nk1_ran[1-nk1_opt]*nk_inc[nk1_opt]; nk1+=nk_inc[nk1_opt])
            {
                nk2b_opt = (kRewFlag)? (nk1%2):0;
                
                for (nk2b=nk2b_ran[nk2b_opt]; nk2b*nk_inc[nk2b_opt]<=nk2b_ran[1-nk2b_opt]*nk_inc[nk2b_opt]; nk2b+=nk_inc[nk2b_opt])
                {

                    if ( ( (nk2+nk2b) >= ndim2 ) || ( (nk2+nk2b) < 0 ) )
                        continue;
                    
                    maskoffset = (yz_sort_order)? ((nk2+nk2b)*ndim1+nk1):((nk2+nk2b)+nk1*ndim2);
    
                    if (mask_ktarc[maskoffset] != 0)
                    {
                        viewtable_k1[nv] = nk1;
                        viewtable_k2[nv] = nk2+nk2b;
                        ++nv;
    
                        /*determine the respiratory factor based on average of the segment */
                        if(NCentKRamp > 0)
                        {
                            k_nex += mask_ktarc[maskoffset];
                            
                            if(nv%ViewsPerSeg == 0)
                            {
                                ref_ind = nv - ViewsPerSeg;
                                k_nex = (int)((float)k_nex / (float)ViewsPerSeg + 0.5);
                                
                                for(nrep=0; nrep < (k_nex-1); ++nrep)
                                    for(offset=0; offset<ViewsPerSeg; ++offset, ++nv)
                                    {
                                        viewtable_k1[nv] = viewtable_k1[ref_ind + offset];
                                        viewtable_k2[nv] = viewtable_k2[ref_ind + offset];
                                    }
                                
                                k_nex = 0;
                            }
                        }
                    }
                }
            }
        }
        
        pviewtable_kt[nt].ky = (short *)AllocNode( nv * sizeof(short) );
        if (NULL == pviewtable_kt[nt].ky)
        {
            printf(" genviewOrder: Unable to allocate memory (AllocNode) for pviewtable_kt[nt].ky!\n");
            return FAILURE;
        }

        pviewtable_kt[nt].kz = (short *)AllocNode( nv * sizeof(short) );
        if (NULL == pviewtable_kt[nt].kz)
        {
            printf(" genviewOrder: Unable to allocate memory (AllocNode) for pviewtable_kt[nt].kz!\n");
            return FAILURE;
        }

        pviewtable_kt[nt].len = (short)nv;
        
        for(nk1=0; nk1 < nv; ++nk1)
        {
            pviewtable_kt[nt].ky[nk1] = (short)(y_list[nk1]);
            pviewtable_kt[nt].kz[nk1] = (short)(z_list[nk1]);
        }
        
        *cine3dTotalviews = IMax( 2, *cine3dTotalviews, pviewtable_kt[nt].len );
    }
    
    FreeNode(mask_ktarc);
    
    FreeNode(y_list);
    FreeNode(z_list);
    
    /* free vdkt vieworder tables */
    if(ViewOrder_vdkt.ky != NULL)
    {
        FreeNode(ViewOrder_vdkt.ky);
        FreeNode(ViewOrder_vdkt.kz);
        
        ViewOrder_vdkt.len = 0;
        ViewOrder_vdkt_outer.len = 0;
        ViewOrder_vdkt_cal.len = 0;
    }
    
    if(r_traj != NULL)
    {
        FreeNode(r_traj);
        FreeNode(maskpos);
    }
    
    if(RespFactor != NULL)
    {
        FreeNode(RespFactor);
    }
    
    if(ktShift_vdkt != NULL)
    {
        FreeNode(ktShift_vdkt);
    }
    
    return SUCCESS;
}

/*
 *  fcine_prepviewtable_fullk
 *
 *  Generate initial viewtable for the entire k-space with radius and theta sorting
 *
 *  @param[in]  short Nky - phase encoding / ky size
 *  @param[in]  short Nkz - slice encoding / kz size
 *  @param[in]  short cal_ky - calibration size along ky
 *  @param[in]  short cal_kz - calibration size along kz
 *  @param[in]  int KTsamp_mode - kt sampling mode (KT_MODE, VDKT_MODE, ARC_MODE)
 *  @param[in]  float fov_vthick_scale - kz / ky normalization factor for k-space distance calculation
 *  @param[in]  int ElliptFlag - elliptical cal shape flag
 *  @param[in]  int CutCorner - elliptical k-space sampling flag
 *  @param[in]  int resp_perC - kspace area for resp-nex in %
 *  @param[in]  int ktStride - HyperKat acceleration (from U/I) or net acceleration in outer k-space
 *  @param[in]  int ktStride_cal - net acceleration in calibration region
 *  @param[out] ViewTable_kyz* pViewOrder_vdkt - outcome view table for the entire k-space
 *  @param[out] ViewTable_kyz* pViewOrder_vdkt_outer - outer k-space views in pViewOrder_vdkt
 *  @param[out] ViewTable_kyz* pViewOrder_vdkt_cal - calibration views in pViewOrder_vdkt
 *  @param[out] short* krOffset_vdkt_outer - offsets for outer k-space rings from center to outer
 *  @param[out] short* krOffset_vdkt_cal - offsets for calibration k-space rings from center to outer
 *  @param[out] short* krAccel_vdkt_outer - acceleration factors of outer k-space rings from center to outer
 *  @param[out] short* krAccel_vdkt_cal - acceleration factors of calibration k-space rings from center to outer
 *  @return status of function (SUCCESS or FAILURE)
 */
STATUS fcine_prepviewtable_fullk(short Nky, short Nkz, short cal_ky, short cal_kz, int KTsamp_mode,
           float fov_vthick_scale, int ElliptFlag, int CutCorner, int resp_perC, int ktStride, int ktStride_cal, 
           ViewTable_kyz* pViewOrder_vdkt, ViewTable_kyz* pViewOrder_vdkt_outer, ViewTable_kyz* pViewOrder_vdkt_cal,
           short* krOffset_vdkt_outer, short* krOffset_vdkt_cal, short* krAccel_vdkt_outer, short* krAccel_vdkt_cal)
{
    short nky=0, nkz=0, ind_k=0, ind_k_cal=0, ind_beg=0, ind_end=0, cal_ky_sta=0, cal_ky_end=0, cal_kz_sta=0;
    short  cal_kz_end=0, in_CalData=0, nSel;
    float cent_ky=0.0, cent_kz=0.0, cent_ky_cal=0.0, cent_kz_cal=0.0, ky=0.0, kz=0.0, kr=0.0, kr_cal=0.0;
    float kr_norm=0.0, in_kmask_thresh=0.0;
    int accel_lower=0, accel_upper=0;
    short NRing_cal=0, NRing_full=0, nRing=0;
    ViewTable_kyz ViewTable_Rings; /*view table indexed into subrings*/
    float Factor_kzky=0.0, kyUnit=0.0, kzUnit=0.0, krScale=0.0, krScale_cal=0.0;
    int nEdge=0, nTgt=0, nOutOfBox=0, kOff=0;
    static const int kyIncr[] = {0, -1, 0, 1};
    static const int kzIncr[] = {-1, 0, 1, 0};
    int kyCorner[4], kzCorner[4];
    float fkyCorner[4], fkzCorner[4], kyExpand[4], kzExpand[4];
    short *kyzScanMask, *RingStartPos, *RingEndPos;
    
    cent_ky = (float)(Nky-1.0)/2.0;
    cent_kz = (float)(Nkz-1.0)/2.0;
    cent_ky_cal = (float)(cal_ky-1.0)/2.0;
    cent_kz_cal = (float)(cal_kz-1.0)/2.0;
    cal_ky_sta = ceil(cent_ky) - ceil(cal_ky/2);
    cal_ky_end = cal_ky_sta + cal_ky - 1;
    cal_kz_sta = ceil(cent_kz) - ceil(cal_kz/2);
    cal_kz_end = cal_kz_sta + cal_kz - 1;
    in_kmask_thresh = 1.0;
    
    /* determine kz-ky scaling factor based on FOV along z & y */

    Factor_kzky = fov_vthick_scale; 
    Factor_kzky = (Factor_kzky > 2.0f)? 2.0f:Factor_kzky;
    Factor_kzky = (Factor_kzky < 0.5f)? 0.5f:Factor_kzky;
    
    kyUnit = (Factor_kzky >= 1)? 1.0f:Factor_kzky;
    kzUnit = (Factor_kzky >= 1)? 1.0/Factor_kzky:1.0f;
    
    NRing_cal = (int)ceil((float)(cal_kz*cal_ky) / VDKT_RING_SIZE);
    NRing_full = (int)ceil((float)(Nkz*Nky) / VDKT_RING_SIZE);
    
    kyCorner[0] = ceil(cent_ky)+1; kyCorner[1] = ceil(cent_ky)+1; kyCorner[2] = ceil(cent_ky)-1; kyCorner[3] = ceil(cent_ky)-1;
    kzCorner[0] = ceil(cent_kz)+1; kzCorner[1] = ceil(cent_kz)-1; kzCorner[2] = ceil(cent_kz)-1; kzCorner[3] = ceil(cent_kz)+1;
    fkyCorner[0] = ceil(cent_ky)+1; fkyCorner[1] = ceil(cent_ky)+1; fkyCorner[2] = ceil(cent_ky)-1; fkyCorner[3] = ceil(cent_ky)-1;
    fkzCorner[0] = ceil(cent_kz)+1; fkzCorner[1] = ceil(cent_kz)-1; fkzCorner[2] = ceil(cent_kz)-1; fkzCorner[3] = ceil(cent_kz)+1;
    kyExpand[0] = kyUnit; kyExpand[1] = kyUnit; kyExpand[2] = -kyUnit; kyExpand[3] = -kyUnit;
    kzExpand[0] = kzUnit; kzExpand[1] = -kzUnit; kzExpand[2] = -kzUnit; kzExpand[3] =  kzUnit;
    
    kyzScanMask = (short *)AllocNode(Nkz*Nky * sizeof(short));
    if (NULL == kyzScanMask)
    {
        printf(" prepviewTab: Unable to allocate memory (AllocNode) for kyzScanMask!\n");
        return FAILURE;
    }

    memset(kyzScanMask, 0, Nkz*Nky * sizeof(short));
    
    RingStartPos = (short *)AllocNode(NRing_full * sizeof(short));
    if (NULL == RingStartPos)
    {
        printf(" prepviewTab: Unable to allocate memory (AllocNode) for RingStartPos!\n");
        return FAILURE;
    }

    RingEndPos = (short *)AllocNode(NRing_full * sizeof(short));
    if (NULL == RingEndPos)
    {
        printf(" prepviewTab: Unable to allocate memory (AllocNode) for RingEndPos!\n");
        return FAILURE;
    }
    
    for(nRing=0; nRing<NRing_full; ++nRing)
    {
        RingStartPos[nRing] = -1;
        RingEndPos[nRing] = 0;
    }
    
    ViewTable_Rings.ky = (short *)AllocNode(Nkz*Nky * sizeof(short));
    if (NULL == ViewTable_Rings.ky)
    {
        printf(" prepviewTab: Unable to allocate memory (AllocNode) for ViewTable_Rings.ky!\n");
        return FAILURE;
    }
    ViewTable_Rings.kz = (short *)AllocNode(Nkz*Nky * sizeof(short));
    if (NULL == ViewTable_Rings.kz)
    {
        printf(" prepviewTab: Unable to allocate memory (AllocNode) for ViewTable_Rings.kz!\n");
        return FAILURE;
    }
    ViewTable_Rings.kr = (float *)AllocNode(Nkz*Nky * sizeof(float));
    if (NULL == ViewTable_Rings.kr)
    {
        printf(" prepviewTab: Unable to allocate memory (AllocNode) for ViewTable_Rings.kr!\n");
        return FAILURE;
    }
    ViewTable_Rings.ki = (short *)AllocNode(Nkz*Nky * sizeof(short));
    if (NULL == ViewTable_Rings.ki)
    {
        printf(" prepviewTab: Unable to allocate memory (AllocNode) for ViewTable_Rings.ki!\n");
        return FAILURE;
    }
    
    ViewTable_Rings.ky[0] = ceil(cent_ky);
    ViewTable_Rings.kz[0] = ceil(cent_kz);
    ViewTable_Rings.kr[0] = 0;
    ViewTable_Rings.ki[0] = 0;
    ViewTable_Rings.len = ind_k_cal = ind_k = 1;
    RingStartPos[nRing] = 0;
    
    Factor_kzky *= Factor_kzky; /*to skip square below*/
    
    krScale_cal = cent_ky_cal*cent_ky_cal*Factor_kzky + cent_kz_cal*cent_kz_cal;
    krScale_cal = (float)NRing_cal / krScale_cal;
    krScale = cent_ky*cent_ky*Factor_kzky + cent_kz*cent_kz;
    krScale = (float)NRing_full / krScale;
    
    while(TRUE)
    {
        for(nEdge=0; nEdge<4; ++nEdge)
        {
            nTgt = (nEdge+1)%4;
            nky = kyCorner[nEdge];
            nkz = kzCorner[nEdge];
            
            while((nky != kyCorner[nTgt]) || (nkz != kzCorner[nTgt]))
            {
                kOff = nkz*Nky + nky;
                
                if(kyzScanMask[kOff] == 0)
                {
                    kyzScanMask[kOff] = 1;
                   
                    ky = (float)(nky + (float)(rand()%1001-500)/1200.0 - cent_ky);
                    kz = (float)(nkz + (float)(rand()%1001-500)/1200.0 - cent_kz);

                    kr_norm = ky*ky + kz*kz*Factor_kzky;
                    
                    ky /= (float)cent_ky+0.5;
                    kz /= (float)cent_kz+0.5;
                    kr = ky*ky + kz*kz; /*Skipping sqrt() is ok for sorting purposes, also needed for subring*/
                    
                    in_CalData = 0;
                    
                    if ((nkz >= cal_kz_sta) && (nkz <= cal_kz_end) && (nky >= cal_ky_sta) && (nky <= cal_ky_end))
                    {
                        if(ElliptFlag==1)
                        {
                            ky = (float)(nky-cent_ky)/((float)cent_ky_cal+0.5);
                            kz = (float)(nkz-cent_kz)/((float)cent_kz_cal+0.5);
                            kr_cal = ky*ky + kz*kz;
                            
                            if(kr_cal <= 1.0)
                                in_CalData = 1;
                        }
                        else  /* Box Cal */
                        {
                            in_CalData = 1;
                        }
                    }
                    
                    if(in_CalData == 1)
                    {
                        nRing = IMin(2, NRing_cal-1, (int)(kr_norm * krScale_cal));
                        
                        ++ind_k_cal;
                    }
                    else
                    {
                        if(CutCorner==1)
                        {
                            if (kr > in_kmask_thresh)
                                continue;
                        }
                        
                        nRing = IMin(2, NRing_full-1, IMax(2, NRing_cal, (int)(kr_norm * krScale)));
                        
                        ++ind_k;
                    }
                    
                    /*record start index and size of each subring*/
                    if(RingStartPos[nRing] == -1)
                    {
                        RingStartPos[nRing] = ViewTable_Rings.len;
                    } 
                    RingEndPos[nRing] = ViewTable_Rings.len;
                    
                    ViewTable_Rings.ky[ViewTable_Rings.len] = nky;
                    ViewTable_Rings.kz[ViewTable_Rings.len] = nkz;
                    ViewTable_Rings.kr[ViewTable_Rings.len] = kr_norm; /*use global kr, instead of kr_cal for cal data*/
                    ViewTable_Rings.ki[ViewTable_Rings.len++] = nRing;
                }
                
                nky = nky + kyIncr[nEdge];
                nkz = nkz + kzIncr[nEdge];
            }
        }
        
        for(nEdge=0, nOutOfBox=0; nEdge<4; ++nEdge)
        {
            fkyCorner[nEdge] += kyExpand[nEdge];
            fkzCorner[nEdge] += kzExpand[nEdge];
            
            if(((fkyCorner[nEdge] < 0) || (fkyCorner[nEdge] >= Nky)) && ((fkzCorner[nEdge] < 0) || (fkzCorner[nEdge] >= Nkz)))
                ++nOutOfBox;
            
            kyCorner[nEdge] = IMax(2, 0, IMin(2, Nky-1, (int)fkyCorner[nEdge]));
            kzCorner[nEdge] = IMax(2, 0, IMin(2, Nkz-1, (int)fkzCorner[nEdge]));
        }
        
        if((nOutOfBox == 4) || (ViewTable_Rings.len >= Nky*Nkz))
            break;
    }
    
    FreeNode(kyzScanMask);
    
    pViewOrder_vdkt->len = ind_k_cal + ind_k;
    pViewOrder_vdkt_cal->len = ind_k_cal;
    pViewOrder_vdkt_outer->len = ind_k;
    pViewOrder_vdkt->ky = (short *)AllocNode(pViewOrder_vdkt->len * sizeof(short));
    if (NULL == pViewOrder_vdkt->ky)
    {
        printf(" prepviewTab: Unable to allocate memory (AllocNode) for pViewOrder_vdkt->ky!\n");
        return FAILURE;
    }
    pViewOrder_vdkt->kz = (short *)AllocNode(pViewOrder_vdkt->len * sizeof(short));
    if (NULL == pViewOrder_vdkt->kz)
    {
        printf(" prepviewTab: Unable to allocate memory (AllocNode) for pViewOrder_vdkt->kz!\n");
        return FAILURE;
    }
    pViewOrder_vdkt->kr = (float *)AllocNode(pViewOrder_vdkt->len * sizeof(float));
    if (NULL == pViewOrder_vdkt->kr)
    {
        printf(" prepviewTab: Unable to allocate memory (AllocNode) for pViewOrder_vdkt->kr!\n");
        return FAILURE;
    }
    
    pViewOrder_vdkt_cal->ky = pViewOrder_vdkt->ky;
    pViewOrder_vdkt_cal->kz = pViewOrder_vdkt->kz;
    pViewOrder_vdkt_cal->kr = pViewOrder_vdkt->kr;
    pViewOrder_vdkt_outer->ky = pViewOrder_vdkt->ky + pViewOrder_vdkt_cal->len;
    pViewOrder_vdkt_outer->kz = pViewOrder_vdkt->kz + pViewOrder_vdkt_cal->len;
    pViewOrder_vdkt_outer->kr = pViewOrder_vdkt->kr + pViewOrder_vdkt_cal->len;
    
    for(nRing=0, ind_beg=0, ind_end=0; nRing < NRing_full; ++nRing)
    {
        for(ind_k=RingStartPos[nRing], nSel=0; (ind_k <= RingEndPos[nRing]); ++ind_k)
        {
            if(ViewTable_Rings.ki[ind_k] == nRing)
            {
                pViewOrder_vdkt->ky[ind_end] = ViewTable_Rings.ky[ind_k];
                pViewOrder_vdkt->kz[ind_end] = ViewTable_Rings.kz[ind_k];
                pViewOrder_vdkt->kr[ind_end++] = ViewTable_Rings.kr[ind_k];
                ++nSel;
            }
        }
        
        sort_vectors_mod(ind_beg, ind_end-1, pViewOrder_vdkt->kr, NULL, pViewOrder_vdkt->ky, pViewOrder_vdkt->kz, NULL);
        
        ind_beg = ind_end;
    }
    
    FreeNode(RingStartPos);
    FreeNode(RingEndPos);
    FreeNode(ViewTable_Rings.ky);
    FreeNode(ViewTable_Rings.kz);
    FreeNode(ViewTable_Rings.kr);
    FreeNode(ViewTable_Rings.ki);
    
    if((resp_perC > 0) && (resp_perC < 100))
    {
        pViewOrder_vdkt->ki = (short *)AllocNode(pViewOrder_vdkt->len * sizeof(short));
        if (NULL == pViewOrder_vdkt->ki)
        {
            printf(" prepviewTab: Unable to allocate memory (AllocNode) for pViewOrder_vdkt->ki!\n");
            return FAILURE;
        }

        pViewOrder_vdkt_cal->ki = pViewOrder_vdkt->ki;
        pViewOrder_vdkt_outer->ki = pViewOrder_vdkt->ki + pViewOrder_vdkt_cal->len;
        
        /*record the current order sorted from center to outer k-space*/
        for(ind_k = 0; ind_k < pViewOrder_vdkt->len; ++ind_k)
        {
            pViewOrder_vdkt->ki[ind_k] = ind_k;
        }
    }
    else
    {
        pViewOrder_vdkt->ki = NULL;
        pViewOrder_vdkt_cal->ki = NULL;
        pViewOrder_vdkt_outer->ki = NULL;
    }
    
    
    if( KTsamp_mode == VDKT_MODE) /*needed only for variable density sampling*/
    {
        accel_lower = IMax(2, 1, (int)((float)ktStride_cal * VDKT_INNER_FACTOR + 0.5));
        accel_upper = IMax(2, ktStride_cal, IMin(2, (int)((float)ktStride_cal *  VDKT_OUTER_FACTOR + 0.5), 
                  (int)((float)ktStride * VDKT_INNER_FACTOR + 0.5)));
        
        if(fcine_genacceltable_vdkt(krAccel_vdkt_cal, krOffset_vdkt_cal, ktStride_cal, accel_lower, accel_upper, pViewOrder_vdkt_cal->len) == FAILURE)
            return FAILURE;
        
        accel_lower = IMin(2, ktStride, IMax(2, accel_upper, (int)((float)ktStride * VDKT_INNER_FACTOR + 0.5)));
        accel_upper = (int)((float)ktStride *  VDKT_OUTER_FACTOR + 0.5);
        
        if(fcine_genacceltable_vdkt(krAccel_vdkt_outer, krOffset_vdkt_outer, ktStride, accel_lower, accel_upper, pViewOrder_vdkt_outer->len) == FAILURE)
        {
            return FAILURE;
        } 
        /* sort outer k-space views*/
        if (sortviews_vdkt(pViewOrder_vdkt_outer->ky, pViewOrder_vdkt_outer->kz, pViewOrder_vdkt_outer->kr, pViewOrder_vdkt_outer->ki, pViewOrder_vdkt_outer->len, krAccel_vdkt_outer, Nky, Nkz, krOffset_vdkt_outer) == FAILURE)
        {
            return FAILURE;
        }
        
        /* sort cal k-space views*/
        if (sortviews_vdkt(pViewOrder_vdkt_cal->ky, pViewOrder_vdkt_cal->kz, pViewOrder_vdkt_cal->kr, pViewOrder_vdkt_cal->ki, pViewOrder_vdkt_cal->len, krAccel_vdkt_cal, Nky, Nkz, krOffset_vdkt_cal) == FAILURE)
        {
            return FAILURE;
        }

    }
    
    /*kr still needed for center NEX*/
    if((resp_perC <= 0) || (resp_perC>= 100))
    {
        FreeNode(pViewOrder_vdkt->kr);
    }
    
    return SUCCESS;
}

/*
 *  sort_vectors_mod
 * 
 * sort vectors in increasing order. 
 * Taken from DV24 ARC_3dfse.e routine but changed to modified-bubble sort.
 *
 *  @param[in]  int index_start - staring index
 *  @param[in]  int index_end   - ending index
 *  @param[in/out]  float* a   - array of float values to be ordered ascending
 *  @param[in/out]  float* b   - array of float values to be ordered ascending
 *  @param[in/out]  short* c   - array of short values to be ordered ascending
 *  @param[in/out]  short* d   - array of short values to be ordered ascending
 *  @param[in/out]  short* e   - array of short values to be ordered ascending
 */

void sort_vectors_mod(
                      int  index_start, /*  I  */
                      int  index_end,   /*  I  */
                      float* a,         /* I/O */
                      float* b,         /* I/O */
                      short* c,         /* I/O */
                      short* d,         /* I/O */
                      short* e          /* I/O */
)
{
    int   i=0,j=0;
    float ftmp=0.0;
    short stmp=0;
    int swapflag = 1;

    for (i=0; (i<(index_end-index_start)) && (swapflag != 0); i++)
    {
        swapflag = 0;

        for (j=index_start; j<index_end-i; j++)
        {
            if(a[j+1] < a[j])
            {
                ftmp    = a[j];
                a[j]   = a[j+1];
                a[j+1] = ftmp;

                if (b!=NULL) {
                    ftmp    = b[j];
                    b[j]   = b[j+1];
                    b[j+1] = ftmp;
                }

                if (c!=NULL) {
                    stmp    = c[j];
                    c[j]   = c[j+1];
                    c[j+1] = stmp;
                }

                if (d!=NULL) {
                    stmp    = d[j];
                    d[j]   = d[j+1];
                    d[j+1] = stmp;
                }

                if (e!=NULL) {
                    stmp    = e[j];
                    e[j]   = e[j+1];
                    e[j+1] = stmp;
                }

                swapflag = 1;
            }
        }
    }
}

/*
 *  fcine_genkmask_ktARC
 *
 *  Generate uniform-density kt sampling maks for a specific cardiac phase
 *
 *  @param[out] short* maskKTarc -
 *  @param[in]  short Nky - phase encoding / ky size
 *  @param[in]  short Nkz - slice encoding / kz size
 *  @param[in]  short cal_ky - calibration size along ky
 *  @param[in]  short cal_kz - calibration size along kz
 *  @param[in]  short t_index - cardiac phase number
 *  @param[in]  int ktStride -  HyperKat acceleration (from U/I) or net acceleration in outer k-space
 *  @param[in]  int ktStride_cal - acceleration in calibration region
 *  @param[in]  int ElliptFlag - elliptical calibration flag
 *  @param[in]  int CutCorner - elliptical k-space sampling flag
 *  @return     short totalviews - total number of views at the current cardiac phase
 */
short fcine_genkmask_ktARC(short *maskKTarc, short Nky, short Nkz, short cal_ky, short cal_kz, short t_index,
			   int ktStride, int ktStride_cal, int ElliptFlag, int CutCorner)
{
    short nky=0, nkz=0, cal_ky_sta=0, cal_ky_end=0, cal_kz_sta=0, cal_kz_end=0;
    float cent_ky=0.0, cent_kz=0.0, cent_ky_cal=0.0, cent_kz_cal=0.0, ky=0.0, kz=0.0, in_kmask_thresh=0.0;
    short nt_pat=0, nt_pat_cal=0, nky_pat=0, nkz_pat=0, on_ktgrid=0, in_kmask=0, in_caldata=0;
    short totalviews=0;
    
    /* hard coded kt sampling pattern based on offline optimization with accel up to 10x        */
    /* Optimal tshift_ky/kz determined by minimizing the overall sampling gaps in k-t space for */
    /* all time points within a 3-phase time window (current phase, left-neighbor phase and     */
    /* right-neighbor phase)                                                                    */

    const unsigned short kmask[55] = {1, 1, 1, 1, 1, 1, 5, 0, 5, 0, 1, 1, 1, 1, 1, 9, 0, 9, 0, 9, 0, 1, 1, 1, 1, 1, 1, 1, 17, 0, 17, 0, 17, 0, 17, 0, 73, 0, 0, 73, 0, 0, 73, 0, 0, 33, 0, 33, 0, 33, 0, 33, 0, 33, 0};
    const unsigned char tshift_ky[55] = {0, 0, 1, 0, 1, 2, 0, 1, 0, 1, 0, 2, 4, 1, 3, 0, 1, 2, 0, 1, 2, 0, 2, 4, 6, 1, 3, 5, 0, 2, 0, 1, 3, 1, 3, 2, 0, 1, 2, 0, 2, 0, 2, 1, 1, 0, 2, 3, 0, 1, 3, 4, 1, 2, 4};
    const unsigned char tshift_kz[55] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 2, 2, 0, 1, 1, 0, 2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    const int accel_offset[10] = {0, 1, 3, 6, 10, 15, 21, 28, 36, 45};
    
    if((ktStride > MAXACCEL_KT) || (ktStride_cal >  MAXACCEL_KT))
    {
        psdexit( 0, 0, "", "ktARC acceleration exceeds limits.", PSD_ARG_INT, (int)(0), 0 );

        return 0;
    }

    cent_ky = (float)(Nky-1.0)/2.0;
    cent_kz = (float)(Nkz-1.0)/2.0;
    cent_ky_cal = (float)(cal_ky-1.0)/2.0;
    cent_kz_cal = (float)(cal_kz-1.0)/2.0;
    cal_ky_sta = ceil(cent_ky) - ceil(cal_ky/2);
    cal_ky_end = cal_ky_sta + cal_ky - 1;
    cal_kz_sta = ceil(cent_kz) - ceil(cal_kz/2);
    cal_kz_end = cal_kz_sta + cal_kz - 1;
    nt_pat = t_index%ktStride;
    nt_pat_cal = t_index%ktStride_cal;
    in_kmask_thresh = 1.0;
    
    totalviews = 0;
    
    for (nkz=0; nkz<Nkz; nkz++)
        for (nky=0; nky<Nky; nky++)
        {
            if (CutCorner==1)
            {
                ky = (float)(nky-cent_ky)/((float)cent_ky+0.5);
                kz = (float)(nkz-cent_kz)/((float)cent_kz+0.5);
                in_kmask = ((ky*ky + kz*kz) <= in_kmask_thresh)? 1:0;
            }
            else
                in_kmask = 1;
            
            if (in_kmask)
            {
                if(ktStride <= 1)
                    on_ktgrid = 1; /*full k-space sampling*/
                else
                {
                    if ( (nky>=cal_ky_sta) && (nky<=cal_ky_end) && (nkz>=cal_kz_sta) && (nkz<=cal_kz_end) )
                    {
                        if (ElliptFlag == 1)
                        {
                            ky = (float)(nky-cent_ky)/((float)cent_ky_cal+0.5);
                            kz = (float)(nkz-cent_kz)/((float)cent_kz_cal+0.5);
                            in_caldata = ((ky*ky + kz*kz) <= 1.0)? 1:0;
                        }
                        else
                            in_caldata = 1;
                    }
                    else
                        in_caldata = 0;
                    
                    if(in_caldata == 1)
                    {
                        nky_pat = ( nky + ktStride_cal - tshift_ky[accel_offset[ktStride_cal-1]+nt_pat_cal] - cal_ky_sta ) % ktStride_cal;
                        nkz_pat = ( nkz + ktStride_cal - tshift_kz[accel_offset[ktStride_cal-1]+nt_pat_cal] - cal_kz_sta ) % ktStride_cal;
                        
                        on_ktgrid = (((kmask[accel_offset[ktStride_cal-1]+nkz_pat] >> nky_pat) & 0x0001) != 0)? 1:0;
                    }
                    else
                    {
                        nky_pat = ( nky + ktStride - tshift_ky[accel_offset[ktStride-1]+nt_pat] ) % ktStride;
                        nkz_pat = ( nkz + ktStride - tshift_kz[accel_offset[ktStride-1]+nt_pat] ) % ktStride;
                        
                        on_ktgrid = (((kmask[accel_offset[ktStride-1]+nkz_pat] >> nky_pat) & 0x0001) != 0)? 1:0;
                    }
                }
                
                if ( on_ktgrid )
                {
                    maskKTarc[nkz*Nky+nky] = 1;
                    totalviews++;
                }
            }
        }
    
    return totalviews;
}

/*
 *  fcine_genrespmap
 *
 *  Generate variable density NEX sampling scheme
 *
 *  @param[in]  float* kr_list - k-space radius of views in the entire k-space
 *  @param[in]  short* rtraj - index to kr_list with increasing radius
 *  @param[out] float* respFactor - outcome variable density NEX factors from center outwards
 *  @param[in]  short nCentKramp - number of center k-space views with variable density NEX
 *  @param[in]  short nCentKrect - equivalent number of center k-space views with uniform NEX
 *  @param[in]  float resp_para - NEX factor
 *  @return status of function (SUCCESS or FAILURE)
 *
 */
STATUS fcine_genrespmap(float* kr_list, short* rTraj, float* respFactor, short nCentKramp, short nCentKrect, float resp_para)
{
    int nk=0;
    float FactorSum=0.0;
    float r_coef=0.0, r_coef_prev=0.0;
    float* r_ratio_array;
    
    r_ratio_array = (float*)AllocNode((nCentKramp+1) * sizeof(float));
    if (NULL ==  r_ratio_array)
    {
        printf(" genrespMap: Unable to allocate memory (AllocNode) for  r_ratio_array!\n");
        return FAILURE;
    }

    r_ratio_array[nCentKramp] = 0.0;
    r_coef_prev = 0.0;
    
    memset(respFactor, 0, nCentKramp*sizeof(float));
    
    /* subtract 1 from net to calcuate the extra data acquisition for nex/gating*/
    resp_para -= 1.0;
    
    /*total added resp acq to be allocated for nCentKramp k-space locations*/
    FactorSum = ceil(resp_para * (float)nCentKrect);
    
    for(nk = nCentKramp-1; nk>=0; --nk)
    {
        r_coef = (kr_list[rTraj[nk]] > 0)? 1.0/sqrt(kr_list[rTraj[nk]]):2;
        
        r_ratio_array[nk] = r_coef + r_ratio_array[nk+1];
        
        if(nk < nCentKramp-1)
            r_ratio_array[nk+1] = r_coef_prev / r_ratio_array[nk+1];
        
        r_coef_prev = r_coef;
    }
    
    r_ratio_array[0] = r_coef_prev / r_ratio_array[0];
    
    for(nk = 0; nk < nCentKramp; ++nk)
    {
        /*assign a factor based on the kr-related ratio in the remaining k-space locations*/
        if(nk < RESP_CENTK_MIN)
            respFactor[nk] = resp_para;
        else
        {
            respFactor[nk] = (float)FactorSum * r_ratio_array[nk];
            respFactor[nk] = (respFactor[nk] > resp_para)? resp_para:respFactor[nk];
            
            /*for nex, respFactor is integer*/
            /*max with the average respFactor for the remaining k-space to avoid  respFactor jiterring from center to outer k-space*/
            respFactor[nk] = IMax(2, (short)(respFactor[nk] + 0.5), (short)ceil((float)FactorSum / (float)(nCentKramp - nk)));
        }
        
        FactorSum -= respFactor[nk];
        
        if(FactorSum <= 0)
            break;
    }
    
    for(nk = 0; nk < nCentKramp; ++nk)
    {
        respFactor[nk] += 1.0;
    }
    
    FreeNode(r_ratio_array);

    return SUCCESS;
}

/*
 *  fcine_OptiKrShift_vdktARC
 *
 *  Calculate the optimal t-shift in k-space for variable dentiy kt sampling with different accelerations
 *  Optimization Criteria: maximize the temporal correlation between 3 adjacent time neighbors
 *
 *  @param[out] short *ktShift - view shifting at different time points
 */

void fcine_OptiKrShift_vdktARC(short *ktShift)
{
    int nacc=0, pos=0, pos_orig=0, noff=0, nt=0;
    short mask[MAXACCEL_VDKT];
    
    memset(ktShift, 0, MAXACCEL_VDKT*MAXACCEL_VDKT*sizeof(short));
    
    for(nacc=2; nacc<MAXACCEL_VDKT; ++nacc)
    {
        memset(mask, 0, MAXACCEL_VDKT*sizeof(short));
        
        for(pos=0, nt=0; nt<nacc; ++nt)
        {
            noff = 0;
            pos_orig = pos;
            
            while(mask[pos] != 0)
            {
                pos = (int)(pos_orig + pow(-1,noff%2)*(int)(1 + noff/2)) % nacc;
                ++noff;
            }
            
            ktShift[(nacc-1)*MAXACCEL_VDKT+nt] = pos;
            mask[pos] = 1;
            
            pos = (int)(pos + nacc/3.0 + 0.5) % nacc;
        }
    }
}

/*
 *   sortviews_vdkt
 *
 *  Sort each k-space ring separately with increasig theta in each k-space subring
 *
 *  @param[in/out] short * ky_sort - original ky list as input and sorted ky list as output
 *  @param[in/out] short * kz_sort - original kz list as input and sorted kz list as output
 *  @param[in/out] float * kr_sort - original radius list as input and sorted radius list as output
 *  @param[in/out] short * ki_sort - original index list as input and sorted index list as output
 *  @param[in]  short num_views - number of views to be sorted
 *  @param[in]  short * kr_Accel - acceleration factors in k-space rings from center to outer
 *  @param[in]  short yres - phase encoding / ky size
 *  @param[in]  short zres - slice encoding / kz size
 *  @param[in]  short * kr_offset - offsets to k-space rings in the view list
 *  @return status of function (SUCCESS or FAILURE)
 *  
 */

STATUS sortviews_vdkt(short * ky_sort, short * kz_sort, float * kr_sort, short * ki_sort, short num_views, short * kr_Accel, short yres, short zres, short * kr_offset)
{
    int   nseg=0, nview=0, nsub=0;
    int   index_start=0, index_end=0, num_subring=0;
    float len_subring=0.0;
    
    float y=0.0, z=0.0;
    float ycenter = ((float)yres-1.0)/2.0;
    float zcenter = ((float)zres-1.0)/2.0;
    
    float* ks_list;
    
    /* allocate data structures */
    ks_list = (float*)AllocNode(num_views * sizeof(float));
    if (NULL == ks_list)
    {
        printf(" sortviewVdkt: Unable to allocate memory (AllocNode) for ks_list!\n");
        return FAILURE;
    }

    /* calcuate radius and theta */
    for(nview=0; nview<num_views; nview++)
    {
        y = (float)ky_sort[nview] + (float)(rand()%1001-500)/1200.0 - ycenter;
        z = (float)kz_sort[nview] + (float)(rand()%1001-500)/1200.0 - zcenter;
        
        /*replaced atan2() with faster signed y^2/r^2. enough for sorting purposes*/
        if(kr_sort[nview] == 0)
        {
            ks_list[nview] = 0;
        }
        else if(z >= 0)
        {
            ks_list[nview] = 1 - ((y>=0.0)? 1.0:-1.0)*y*y/kr_sort[nview]; /*[0,2]*/
        }
        else
        {
            ks_list[nview] = 3 + ((y>=0.0)? 1.0:-1.0)*y*y/kr_sort[nview]; /*[2,4]*/
        }
    }
    
    /* k-space views r-sorted in prepviewtable_fullk()*/
    /* perform angular sorting for each kr ring */
    for (nseg=0; kr_offset[nseg+1]>0; nseg++)
    {
        /* dividing a ring into # of Accel subrings for even k-space sampling */
        num_subring = kr_Accel[nseg];
        len_subring = (float)(kr_offset[nseg+1] - kr_offset[nseg]) / (float)num_subring;
        
        for (nsub=0; nsub<num_subring; ++nsub)
        {
            index_start = kr_offset[nseg] + (int)((float)nsub * len_subring + 0.5);
            index_end = kr_offset[nseg] + (int)(((float)nsub+1.0) * len_subring + 0.5) -1 ;
            
            sort_vectors_mod(index_start, index_end, ks_list, kr_sort, ky_sort, kz_sort, ki_sort);
        }
    }
    
    /* free data structures */
    FreeNode(ks_list); 
    return SUCCESS;
}
#endif /* IPG_TGT or MGD_TGT only */

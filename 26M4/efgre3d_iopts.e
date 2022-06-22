@host AllSupportedIopts
#include <psdiopt.h>
int is_vast_on(void);

int sequence_iopts[] = {
    PSD_IOPT_CARD_GATE,
    PSD_IOPT_NOP_WRAP,
    PSD_IOPT_EDR,
    PSD_IOPT_MPH,
    PSD_IOPT_SQR_PIX,
    PSD_IOPT_RESP_TRIG,
    PSD_IOPT_ASSET,
    PSD_IOPT_ZIP_1024,
    PSD_IOPT_ZIP_512,
    PSD_IOPT_SLZIP_X2,
    PSD_IOPT_SLZIP_X4,
    PSD_IOPT_MULTI_STATION,
    PSD_IOPT_FLUORO,
    PSD_IOPT_NAV,
    PSD_IOPT_SMART_PREP,
    PSD_IOPT_IR_PREP,
    PSD_IOPT_DYNPL,
    PSD_IOPT_MILDNOTE,
    PSD_IOPT_FLOW_COMP,
    PSD_IOPT_IDEAL,
    PSD_IOPT_ARC,
    PSD_IOPT_T2_PREP,
    PSD_IOPT_SSRF,
    PSD_IOPT_FLEX,
    PSD_IOPT_MSDE
};

typedef enum feature_bits {
    FIESTA_E,
    PHASE_CYCLE_E,
    TIME_OF_FLIGHT_E,
    TRICKS_E,
    VIBRANT_E,
    SLICE_ASSET_E,
    BRAVA_E,
    VIBRANT_AXIAL_E,  
    NAVIGATOR_E,
    FLUORO_E,
    LAVA_E,
    PHASE_ASSET_E,
    IRPREP_E,
    CGATE_E,
    VAST_E,
    RESPTRIG_E,
    SMARTPREP_E,
    COSMIC_E,
    BRAVO_E,
    SWIFT_E,
    VIBRANTXV_E,
    MERGE_E,
    MEDAL_E,
    MULTI_ECHO_E,
    QUICKSTEP_E,
    MSDE_E
} feature_bit_e;

#define FIESTA (long)(1 << FIESTA_E)
#define PHASE_CYCLE (long)(1 << PHASE_CYCLE_E)
#define TIME_OF_FLIGHT (long)(1 << TIME_OF_FLIGHT_E)
#define TRICKS (long)(1 << TRICKS_E)
#define VIBRANT (long)(1 << VIBRANT_E)
#define SLICE_ASSET (long)(1 << SLICE_ASSET_E)
#define BRAVA (long)(1 << BRAVA_E)
#define VIBRANT_AXIAL (long)(1 << VIBRANT_AXIAL_E)
#define NAVIGATOR (long)(1 << NAVIGATOR_E)
#define FLUORO (long)(1 << FLUORO_E)
#define LAVA (long)(1 << LAVA_E)
#define PHASE_ASSET (long)(1 << PHASE_ASSET_E)
#define IRPREP (long)(1 << IRPREP_E)
#define CGATE (long)(1 << CGATE_E)
#define VAST (long)(1 << VAST_E)
#define RESPTRIG (long)(1 << RESPTRIG_E)
#define SMARTPREP (long)(1 << SMARTPREP_E)
#define COSMIC  (long)(1 << COSMIC_E)
#define BRAVO (long)(1 << BRAVO_E)
#define SWIFT (long)(1 << SWIFT_E)
#define VIBRANTXV (long)(1 << VIBRANTXV_E)
#define MERGE (long)(1 << MERGE_E)
#define MEDAL (long)(1 << MEDAL_E)
#define MULTI_ECHO (long)(1 << MULTI_ECHO_E)
#define QUICKSTEP (long)(1 << QUICKSTEP_E)
#define MSDE (long)(1 << MSDE_E)
long feature_flag = 0;

@host ImagingOptionFunctions
void
psd_init_iopts( void )
{
    int numopts = sizeof(sequence_iopts) / sizeof(int);

    psd_init_iopt_activity();

    activate_iopt_list( numopts, sequence_iopts );
    enable_iopt_list( numopts, sequence_iopts );

    set_incompatible( PSD_IOPT_SMART_PREP, PSD_IOPT_NAV );
    set_incompatible( PSD_IOPT_SMART_PREP, PSD_IOPT_T2_PREP );
    set_incompatible( PSD_IOPT_SMART_PREP, PSD_IOPT_RESP_TRIG );
    set_incompatible( PSD_IOPT_SMART_PREP, PSD_IOPT_FLUORO );
    set_incompatible( PSD_IOPT_SMART_PREP, PSD_IOPT_CARD_GATE );

    set_incompatible( PSD_IOPT_FLUORO, PSD_IOPT_T2_PREP );
    set_incompatible( PSD_IOPT_FLUORO, PSD_IOPT_RESP_TRIG );
    set_incompatible( PSD_IOPT_FLUORO, PSD_IOPT_CARD_GATE );

    set_incompatible( PSD_IOPT_MULTI_STATION, PSD_IOPT_CARD_GATE );
    set_incompatible( PSD_IOPT_MULTI_STATION, PSD_IOPT_RESP_TRIG );
    set_incompatible( PSD_IOPT_MULTI_STATION, PSD_IOPT_NAV );

    set_incompatible( PSD_IOPT_IR_PREP, PSD_IOPT_T2_PREP );

    set_incompatible( PSD_IOPT_MPH, PSD_IOPT_CARD_GATE );
    set_incompatible( PSD_IOPT_MPH, PSD_IOPT_RESP_TRIG );

    set_incompatible( PSD_IOPT_ASSET, PSD_IOPT_ZIP_1024 );

    set_incompatible( PSD_IOPT_NAV, PSD_IOPT_RESP_TRIG );

    set_incompatible( PSD_IOPT_DYNPL, PSD_IOPT_MPH );
    set_incompatible( PSD_IOPT_DYNPL, PSD_IOPT_CARD_GATE );
    set_incompatible( PSD_IOPT_DYNPL, PSD_IOPT_RESP_TRIG );
    set_incompatible( PSD_IOPT_DYNPL, PSD_IOPT_MULTI_STATION );

    set_incompatible( PSD_IOPT_ARC, PSD_IOPT_RESP_TRIG );

    if (!((exist(op3dcine_fiesta)==PSD_ON) ||
        (exist(op3dcine_spgr) == PSD_ON) ||
        (exist(op4dflow)==PSD_ON) ) )
    {
        set_incompatible( PSD_IOPT_ARC, PSD_IOPT_CARD_GATE );
    }

    set_incompatible( PSD_IOPT_IDEAL, PSD_IOPT_CARD_GATE );
    set_incompatible( PSD_IOPT_IDEAL, PSD_IOPT_FLUORO );
    set_incompatible( PSD_IOPT_IDEAL, PSD_IOPT_MULTI_STATION );
    set_incompatible( PSD_IOPT_IDEAL, PSD_IOPT_SMART_PREP );
    set_incompatible( PSD_IOPT_IDEAL, PSD_IOPT_NAV );
    set_incompatible( PSD_IOPT_IDEAL, PSD_IOPT_FLOW_COMP );
    /* MRIhc22542 */
    set_incompatible( PSD_IOPT_IDEAL, PSD_IOPT_MPH );
    if(idealiq_flag)
    {
        set_incompatible( PSD_IOPT_IDEAL, PSD_IOPT_ASSET );
    }
    else
    {
        set_incompatible( PSD_IOPT_IDEAL, PSD_IOPT_ARC );
    }
    /* MRIhc26928 */
    set_incompatible( PSD_IOPT_IDEAL, PSD_IOPT_DYNPL);
    /* MRIhc29535 */
    set_incompatible( PSD_IOPT_IDEAL, PSD_IOPT_RESP_TRIG);
    if(value_system_flag || idealiq_flag) 
    {
        set_incompatible( PSD_IOPT_IDEAL, PSD_IOPT_ZIP_1024);
        set_incompatible( PSD_IOPT_IDEAL, PSD_IOPT_SLZIP_X4);
    }

    if(NON_VALUE_SYSTEM == value_system_flag)
    {
        set_incompatible( PSD_IOPT_MILDNOTE, PSD_IOPT_NAV );
        set_incompatible( PSD_IOPT_MILDNOTE, PSD_IOPT_SMART_PREP );
        set_incompatible( PSD_IOPT_MILDNOTE, PSD_IOPT_FLUORO );
    }

    /* Water Excitation */
    set_incompatible( PSD_IOPT_SSRF, PSD_IOPT_IDEAL );
    set_incompatible( PSD_IOPT_SSRF, PSD_IOPT_CARD_GATE );
    set_incompatible( PSD_IOPT_SSRF, PSD_IOPT_NAV );
    set_incompatible( PSD_IOPT_SSRF, PSD_IOPT_RESP_TRIG );
    set_incompatible( PSD_IOPT_SSRF, PSD_IOPT_IR_PREP );
    set_incompatible( PSD_IOPT_SSRF, PSD_IOPT_FLUORO );

    /* FLEX */
    set_incompatible( PSD_IOPT_FLEX, PSD_IOPT_ASSET );
    set_incompatible( PSD_IOPT_FLEX, PSD_IOPT_IDEAL );
    set_incompatible( PSD_IOPT_FLEX, PSD_IOPT_SSRF );
    if (PSD_OFF == exist(oplava)) 
    {   /* if not LAVA lock out Flex from Mstation */  
        set_incompatible( PSD_IOPT_FLEX, PSD_IOPT_MULTI_STATION ); 
    }
    set_incompatible( PSD_IOPT_MSDE, PSD_IOPT_IDEAL );
    set_incompatible( PSD_IOPT_MSDE, PSD_IOPT_NAV );
    set_incompatible( PSD_IOPT_MSDE, PSD_IOPT_T2_PREP );
    set_incompatible( PSD_IOPT_MSDE, PSD_IOPT_RESP_TRIG );
    set_incompatible( PSD_IOPT_MSDE, PSD_IOPT_CARD_GATE );
    set_incompatible( PSD_IOPT_MSDE, PSD_IOPT_ASSET );
    set_incompatible( PSD_IOPT_MSDE, PSD_IOPT_IR_PREP );
    set_incompatible( PSD_IOPT_MSDE, PSD_IOPT_FLOW_COMP );
    set_incompatible( PSD_IOPT_MSDE, PSD_IOPT_MULTI_STATION );
    set_incompatible( PSD_IOPT_MSDE, PSD_IOPT_SMART_PREP );
    set_incompatible( PSD_IOPT_MSDE, PSD_IOPT_FLUORO );

    return;
}

STATUS
cvsetfeatures( void )
{

    feature_flag = 0;

#ifdef PSD_HW
    SmartPrepKey = !checkOptionKey( SOK_SMARTPREP );
    SPECIALKey = !checkOptionKey( SOK_SPECIAL );
    BREAST2Key = !checkOptionKey( SOK_BREAST2 ); 
    VIBRANTDEKey = !checkOptionKey( SOK_VIBRANTDE );
    LAVAKey = !checkOptionKey( SOK_LAVA );
    LAVAXVKey = !checkOptionKey( SOK_LAVAXV );
    BRAVOKey = !checkOptionKey( SOK_BRAVO );
    COSMICKey = !checkOptionKey( SOK_COSMIC3D );
    LAVADEKey = !checkOptionKey( SOK_LAVADE );
    QUICKSTEPKey = !checkOptionKey( SOK_QUICKSTEP );
    MERGEKey = !checkOptionKey( SOK_MERGE3D );
    if( PSD_ON == idealiq_flag )
    {
        IDEAL3DKey = Present;
    }
    else
    {
        IDEAL3DKey = !checkOptionKey( SOK_IDEAL );
    }
    UltraFastKey = !checkOptionKey( SOK_USHORTTR ); 
    ftMRAKey = !checkOptionKey( SOK_FTMRA );
    FiestaKey = !checkOptionKey( SOK_FIESTA3D ); 
    FiestaCKey = !checkOptionKey( SOK_FIESTAC );
    ASSETKey = !checkOptionKey( SOK_ASSET ); 
    ARCKey = !checkOptionKey( SOK_ARC ); 
    TRICKSKey = !checkOptionKey( SOK_TRICKS );
    if( SmartPrepKey == Present ) { 
        MultiStationKey = !checkOptionKey( SOK_SPREP99 );
    } else {
        MultiStationKey = Absent;
    }
    SWAN3DKey = !checkOptionKey( SOK_SWAN3D );
    BODYNAVKey = !checkOptionKey( SOK_BODYNAV );
    PhaseImageKey = !checkOptionKey( SOK_PHASEIMG );
    DISCOKey = !checkOptionKey( SOK_DISCO );
    VESSELVIEWKey = !checkOptionKey( SOK_VESSELVIEW );
#else /* !PSD_HW */
    SmartPrepKey = Present;
    SPECIALKey = Present;
    BREAST2Key = Present;
    VIBRANTDEKey = Present;
    LAVAKey = Present;
    LAVAXVKey = Present;
    BRAVOKey = Present;
    COSMICKey = Present;
    LAVADEKey = Present;
    QUICKSTEPKey = Present;
    MERGEKey = Present;
    IDEAL3DKey = Present;
    MultiStationKey = Present;
    UltraFastKey = Present;
    ftMRAKey = Present;
    FiestaKey = Present;
    FiestaCKey = Present;
    ASSETKey = Present;
    ARCKey = Present; 
    TRICKSKey = Present;
    SWAN3DKey = Present;
    BODYNAVKey = Present;
    PhaseImageKey = Present;
    DISCOKey = Present;
    VESSELVIEWKey = Present;
#endif /* PSD_HW */

    if( PSD_SSFP == exist(oppseq) )
    {
        feature_flag |= FIESTA;
    }

    if( PSD_ON == exist(opphasecycle) )
    {
        feature_flag |= PHASE_CYCLE | FIESTA;
    }

    if( PSD_ON == exist(opcosmic) )
    {
        feature_flag |= COSMIC | FIESTA;
    }

    if( (PSD_TOF == exist(oppseq)) || (PSD_TOFSP == exist(oppseq)) ) 
    {
        feature_flag |= TIME_OF_FLIGHT ;
    }

    if( exist(opectricks) == PSD_ON)
    {
        feature_flag |= TRICKS;
    }

    if( exist(opswift) == PSD_ON)
    {
        feature_flag |= SWIFT;
    }

    if( exist(opsmartprep) == PSD_ON )
    {
        feature_flag |= SMARTPREP;
    }

    if( (PSD_SPGR == exist(oppseq)) &&
        ((existcv(opplane) && (PSD_SAG == exist(opplane))) && !aspir_override) &&
        (existcv(opvibrant) && (PSD_ON == exist(opvibrant))) )  
    {
        feature_flag |= VIBRANT ;
    }

    if( (exist(opvibrant)==PSD_ON) 
        && (((PSD_AXIAL == exist(opplane)) && existcv(opplane)) || aspir_override) )
    {
        feature_flag |= BRAVA;
    }

    if ( arc_flag && (feature_flag & BRAVA) )
    {
        feature_flag |= VIBRANTXV;
    }

    if( exist(opnav) == PSD_ON )
    {
        feature_flag |= NAVIGATOR;
    }

    if( (exist(opfluorotrigger)==PSD_ON) )
    {
        feature_flag |= FLUORO;
    }

    if( (exist(oplava)==PSD_ON) )
    {
        feature_flag |= LAVA;
    }

    if( (exist(opmerge)==PSD_ON) || (exist(opswan)==PSD_ON) )
    {
        feature_flag |= MERGE;
    }

    if( multiEcho_flag==PSD_ON )
    {
        feature_flag |= MULTI_ECHO;
    }

    /* MRIhc25800: Add medal_flag here for 3D Dual Echo */
    if( (exist(opmedal)==PSD_ON) || (PSD_ON == de3d_flag) )
    {
        feature_flag |= MEDAL;
    }

    if( (exist(opquickstep)==PSD_ON) )
    {
        feature_flag |= QUICKSTEP;
    }

    if( existcv(opasset) && (exist(opassetscan) == PSD_ON))
    {
        feature_flag |= PHASE_ASSET;
    }

    if( (exist(opirprep) == PSD_ON) )
    {
        feature_flag |= IRPREP;
    }

    if( (exist(opcgate) != PSD_OFF) )
    {
        feature_flag |= CGATE;
    }

    /* YMSmr08077 & MRIhc12595 12/14/2005 YI & CRM */
    if( (PSD_ON == is_vast_on()) )
    {
        feature_flag |= VAST;
    }

    if( (exist(oprtcgate) == PSD_ON) )
    {
        feature_flag |= RESPTRIG;
    }

    if( PSD_ON == exist(opbravo) )
    {
        feature_flag |= BRAVO;
    }

    if( PSD_ON == exist(opmsde) )
    {
        feature_flag |= MSDE;
    }

    if((cffield < B0_15000)||(cffield > B0_30000))
    {
        disable_ioption(PSD_IOPT_IDEAL);
        disable_ioption(PSD_IOPT_FLEX);
    }

    return SUCCESS;
}

STATUS
cvfeatureiopts( void )
{
    psd_init_iopts();


    if (exist(op4dflow) == PSD_ON)  
    {
        activate_ioption( PSD_IOPT_FLOW_COMP );
        enable_ioption( PSD_IOPT_FLOW_COMP );
    } else 
    {
       deactivate_ioption( PSD_IOPT_FLOW_COMP );
    }

    deactivate_ioption( PSD_IOPT_ARC );
    deactivate_ioption( PSD_IOPT_T2_PREP );
    deactivate_ioption( PSD_IOPT_FLEX );
 
    /* SV Branch HCSDM00337799 Mulan does not support SSRF on efgre3d sequences.*/
    if ((VALUE_SYSTEM_SVEM == value_system_flag) ||
        (VALUE_SYSTEM_SVDM == value_system_flag) )
    {
        deactivate_ioption( PSD_IOPT_SSRF );
    }

    if( Absent == VESSELVIEWKey )
    {
        deactivate_ioption( PSD_IOPT_MSDE );
    }
    else
    {
        if( (PSD_SPGR == exist(oppseq)) && !(exist(op3dcine_spgr) == PSD_ON))
        {
            activate_ioption( PSD_IOPT_ARC );
            if( feature_flag & MSDE )
            {
                set_required_disabled_option( PSD_IOPT_EDR );
                enable_ioption( PSD_IOPT_ARC );
            }
            else
            {
                disable_ioption( PSD_IOPT_ARC );
            }
        }
        else
        {
            deactivate_ioption( PSD_IOPT_MSDE );
        }
    }

    if( feature_flag & FIESTA )
    {
        deactivate_ioption( PSD_IOPT_SMART_PREP );
        deactivate_ioption( PSD_IOPT_SSRF );
        deactivate_ioption( PSD_IOPT_MSDE );

        if(ifir_flag) 
        {
           set_required_disabled_option( PSD_IOPT_IR_PREP );
           if(B0_30000 == cffield)
           {
               set_required_disabled_option( PSD_IOPT_RESP_TRIG );
           }

           set_incompatible( PSD_IOPT_IR_PREP, PSD_IOPT_CARD_GATE );
           set_incompatible( PSD_IOPT_IR_PREP, PSD_IOPT_NOP_WRAP );
           set_incompatible( PSD_IOPT_NAV, PSD_IOPT_FLUORO );
           set_incompatible( PSD_IOPT_NAV, PSD_IOPT_MPH );
           set_incompatible( PSD_IOPT_NAV, PSD_IOPT_DYNPL );
           if(PSD_OFF == value_system_flag)
           {
               deactivate_ioption( PSD_IOPT_MILDNOTE );  
           }
           /* SVBranch HCSDM00276910  IFIR should not support FT and MPh imaging option */
           deactivate_ioption(PSD_IOPT_FLUORO);
           deactivate_ioption(PSD_IOPT_MPH);
        } else {
           deactivate_ioption( PSD_IOPT_IR_PREP );
        }

        deactivate_ioption( PSD_IOPT_IDEAL );

      
        if (heart3d_flag)
        {
           deactivate_ioption( PSD_IOPT_MILDNOTE );
        }
 
        if ( feature_flag & PHASE_CYCLE )
        {
           deactivate_ioption( PSD_IOPT_FLUORO );
           deactivate_ioption( PSD_IOPT_CARD_GATE );
           deactivate_ioption( PSD_IOPT_MULTI_STATION );
           deactivate_ioption( PSD_IOPT_RESP_TRIG );
           deactivate_ioption( PSD_IOPT_NAV );
           if( !value_system_flag ) /* FIESTA-C  06/10/2005 YI; MRIhc10432 */
           {
               deactivate_ioption( PSD_IOPT_ASSET );
               activate_ioption( PSD_IOPT_ARC );
               enable_ioption( PSD_IOPT_ARC );
           }
        }

        if ( feature_flag & COSMIC )
        {
           activate_ioption( PSD_IOPT_ARC );
           enable_ioption( PSD_IOPT_ARC );
           deactivate_ioption( PSD_IOPT_FLUORO );
           deactivate_ioption( PSD_IOPT_CARD_GATE );
           deactivate_ioption( PSD_IOPT_MULTI_STATION );
           deactivate_ioption( PSD_IOPT_RESP_TRIG );
           deactivate_ioption( PSD_IOPT_NAV );
           deactivate_ioption( PSD_IOPT_ASSET );
           deactivate_ioption( PSD_IOPT_MPH );
           deactivate_ioption( PSD_IOPT_DYNPL );
           if (PSD_OFF == value_system_flag)
           {
               deactivate_ioption( PSD_IOPT_MILDNOTE ); 
           } 
        }

        if ( feature_flag & CGATE)
        {
           disable_ioption( PSD_IOPT_NOP_WRAP );
        }
    }

    /* SVBranch HCSDM00136616, instead of checking heart3d_flag, now check if heart3d option key exist.*/
    if((((B0_15000==cffield) && (feature_flag & FIESTA)) || (B0_15000<cffield)) && 
       (Present == !checkOptionKey( SOK_HEART3D )))
    {
        activate_ioption( PSD_IOPT_T2_PREP );
        if((PSD_ON == exist(opcgate)))
        {
            enable_ioption( PSD_IOPT_T2_PREP );
        }
    }

    if( feature_flag & TIME_OF_FLIGHT ) 
    {
        deactivate_ioption( PSD_IOPT_SSRF );
        deactivate_ioption( PSD_IOPT_NAV );
        deactivate_ioption( PSD_IOPT_IDEAL );
        deactivate_ioption( PSD_IOPT_MSDE );
        if (PSD_OFF == value_system_flag)
        {
            activate_ioption( PSD_IOPT_ARC );
            enable_ioption( PSD_IOPT_ARC );
            deactivate_ioption( PSD_IOPT_MILDNOTE ); 
        }  

        if( PSD_ON == turbo_cemra_flag )
        {
            disable_ioption( PSD_IOPT_CARD_GATE );
            disable_ioption( PSD_IOPT_RESP_TRIG );
            disable_ioption( PSD_IOPT_IR_PREP );
        }
    }

    if( feature_flag & (CGATE | RESPTRIG) )
    {
        deactivate_ioption( PSD_IOPT_SSRF );
        disable_ioption( PSD_IOPT_MPH );
        disable_ioption( PSD_IOPT_MULTI_STATION );
    }

    if( feature_flag & NAVIGATOR )
    {
        deactivate_ioption( PSD_IOPT_SSRF );
        disable_ioption( PSD_IOPT_RESP_TRIG ); 
        disable_ioption( PSD_IOPT_IDEAL );
        deactivate_ioption( PSD_IOPT_MPH );

        if( ( feature_flag & ( LAVA | MEDAL ) ) || de3d_flag || ifir_flag )
        {
            disable_ioption( PSD_IOPT_CARD_GATE );
        } else { /* HCSDM00178912 */
            set_forcing( PSD_IOPT_NAV, PSD_IOPT_CARD_GATE );
        }
    }

    if( feature_flag & TRICKS )
    {
        deactivate_ioption( PSD_IOPT_SSRF );
        deactivate_ioption( PSD_IOPT_CARD_GATE );
        deactivate_ioption( PSD_IOPT_RESP_TRIG );
        deactivate_ioption( PSD_IOPT_T2_PREP );
        deactivate_ioption( PSD_IOPT_IR_PREP );
        deactivate_ioption( PSD_IOPT_MULTI_STATION );
        deactivate_ioption( PSD_IOPT_SMART_PREP );
        deactivate_ioption( PSD_IOPT_FLUORO );
        deactivate_ioption( PSD_IOPT_NOP_WRAP );
        deactivate_ioption( PSD_IOPT_MPH );
        deactivate_ioption( PSD_IOPT_DYNPL );
        deactivate_ioption( PSD_IOPT_IDEAL );
        deactivate_ioption( PSD_IOPT_NAV );
        deactivate_ioption( PSD_IOPT_MSDE );
        if (PSD_OFF == value_system_flag)
        {
           deactivate_ioption( PSD_IOPT_MILDNOTE ); 
        } 
    }

    if( feature_flag & SWIFT )
    {
        deactivate_ioption( PSD_IOPT_SSRF );
        deactivate_ioption( PSD_IOPT_CARD_GATE );
        deactivate_ioption( PSD_IOPT_RESP_TRIG );
        deactivate_ioption( PSD_IOPT_T2_PREP );
        deactivate_ioption( PSD_IOPT_IR_PREP );
        deactivate_ioption( PSD_IOPT_MULTI_STATION );
        deactivate_ioption( PSD_IOPT_SMART_PREP );
        deactivate_ioption( PSD_IOPT_FLUORO );
        deactivate_ioption( PSD_IOPT_NOP_WRAP );
        deactivate_ioption( PSD_IOPT_MPH );
        deactivate_ioption( PSD_IOPT_DYNPL );
        deactivate_ioption( PSD_IOPT_IDEAL );
        deactivate_ioption( PSD_IOPT_MSDE );
        if (PSD_OFF == value_system_flag)
        {
            deactivate_ioption( PSD_IOPT_MILDNOTE ); 
        } 
        deactivate_ioption( PSD_IOPT_NAV );
    }

    if( feature_flag & FLUORO )
    {
        disable_ioption( PSD_IOPT_SSRF );
        disable_ioption( PSD_IOPT_CARD_GATE );
        disable_ioption( PSD_IOPT_RESP_TRIG );
        disable_ioption( PSD_IOPT_T2_PREP );
        disable_ioption( PSD_IOPT_SMART_PREP );
        disable_ioption( PSD_IOPT_IDEAL );
    }

    if( feature_flag & SMARTPREP )
    {
        disable_ioption( PSD_IOPT_CARD_GATE );
        disable_ioption( PSD_IOPT_RESP_TRIG );
        disable_ioption( PSD_IOPT_T2_PREP );
        disable_ioption( PSD_IOPT_FLUORO );
        set_disallowed_option( PSD_IOPT_NAV );
        disable_ioption( PSD_IOPT_IDEAL );
    }

    if( feature_flag & LAVA)
    {
        activate_ioption( PSD_IOPT_ARC );
        enable_ioption( PSD_IOPT_ARC );
        if (Present == LAVADEKey)
        {
            activate_ioption( PSD_IOPT_FLEX );
            enable_ioption( PSD_IOPT_FLEX );
        }
        deactivate_ioption( PSD_IOPT_CARD_GATE );
        deactivate_ioption( PSD_IOPT_RESP_TRIG );
        deactivate_ioption( PSD_IOPT_T2_PREP );
        deactivate_ioption( PSD_IOPT_IR_PREP );
        deactivate_ioption( PSD_IOPT_IDEAL );
        deactivate_ioption( PSD_IOPT_MSDE );
        if (PSD_OFF == value_system_flag)
        {
             deactivate_ioption( PSD_IOPT_MILDNOTE ); 
        } 
    }

    if( feature_flag & (BRAVA | VIBRANT | VIBRANT_AXIAL) )
    {
        activate_ioption( PSD_IOPT_ARC );

        /* VIBRANT-XV support */
        /* ZZ: Added ARC support for Sag VIBRANT with ASPIR on both 1.5T
         * and 3T*/
        if ( ((feature_flag & BRAVA) && (B0_30000 == cffield)) 
             || ( (PSD_SAG == opplane) && aspir_override && (feature_flag & BRAVA) ) )
        {
            enable_ioption( PSD_IOPT_ARC );
        }
        else
        {
            set_disallowed_option( PSD_IOPT_ARC );
            disable_ioption( PSD_IOPT_ARC );
        }
        
        if (Present == VIBRANTDEKey)
        {
            activate_ioption( PSD_IOPT_FLEX );
            enable_ioption( PSD_IOPT_FLEX );
        }
        deactivate_ioption( PSD_IOPT_CARD_GATE );
        deactivate_ioption( PSD_IOPT_RESP_TRIG );
        deactivate_ioption( PSD_IOPT_T2_PREP );
        deactivate_ioption( PSD_IOPT_IR_PREP );
        deactivate_ioption( PSD_IOPT_FLUORO );
        deactivate_ioption( PSD_IOPT_MULTI_STATION );
        deactivate_ioption( PSD_IOPT_ZIP_1024 );
        deactivate_ioption( PSD_IOPT_SLZIP_X4 );
        deactivate_ioption( PSD_IOPT_SMART_PREP );
        deactivate_ioption( PSD_IOPT_NAV );
        deactivate_ioption( PSD_IOPT_IDEAL );
        deactivate_ioption( PSD_IOPT_MSDE );
        /* SV Branch HCSDM00337799 Mulan does not support SSRF on efgre3d sequences.*/
        if(( VALUE_SYSTEM_SVEM == value_system_flag ) ||
           ( VALUE_SYSTEM_SVDM == value_system_flag ))
        {
            deactivate_ioption( PSD_IOPT_SSRF );
        }

        /*  MRIhc34181 */
        if ( feature_flag & (BRAVA | VIBRANT_AXIAL) )
        {
           disable_ioption( PSD_IOPT_SQR_PIX );
        }
        if (PSD_OFF == value_system_flag)
        {
            deactivate_ioption( PSD_IOPT_MILDNOTE ); 
        } 
    }

    /*ZZ: BRAVA with aspir_override for Sag VIBRANT ASPIR*/
    if( (feature_flag & VIBRANT) 
        || ((feature_flag & BRAVA) && aspir_override && (PSD_SAG == opplane)) )
    {
        set_compatible( PSD_IOPT_ASSET, PSD_IOPT_NOP_WRAP );
    }    
    else
    { 
        set_incompatible( PSD_IOPT_ASSET, PSD_IOPT_NOP_WRAP );
    }

    if( feature_flag & BRAVO )
    {
        deactivate_ioption( PSD_IOPT_SSRF );
        deactivate_ioption( PSD_IOPT_ASSET );
        activate_ioption( PSD_IOPT_ARC );
        enable_ioption( PSD_IOPT_ARC );
        deactivate_ioption( PSD_IOPT_CARD_GATE );
        deactivate_ioption( PSD_IOPT_SQR_PIX );
        deactivate_ioption( PSD_IOPT_RESP_TRIG );
        deactivate_ioption( PSD_IOPT_MULTI_STATION );
        deactivate_ioption( PSD_IOPT_FLUORO );
        deactivate_ioption( PSD_IOPT_NAV );
        deactivate_ioption( PSD_IOPT_SMART_PREP );
        deactivate_ioption( PSD_IOPT_DYNPL );
        deactivate_ioption( PSD_IOPT_IDEAL );
        set_required_disabled_option( PSD_IOPT_IR_PREP );
        deactivate_ioption( PSD_IOPT_MSDE );
    }

    if( feature_flag & MEDAL )
    {
        if( value_system_flag != VALUE_SYSTEM_HDE ) /* YMSmr11392: HDe2 uses ASSET for 3DDE */
        {
            if (de3d_flag)
            {
                deactivate_ioption( PSD_IOPT_ASSET );
            }
            activate_ioption( PSD_IOPT_ARC );
            enable_ioption( PSD_IOPT_ARC );
        }

        if (de3d_flag)
        {
            deactivate_ioption( PSD_IOPT_SSRF );
            deactivate_ioption( PSD_IOPT_IDEAL );
            deactivate_ioption( PSD_IOPT_MULTI_STATION );
        }
        deactivate_ioption( PSD_IOPT_CARD_GATE );
        deactivate_ioption( PSD_IOPT_RESP_TRIG );

        /* SVBranch GEHmr04241: Activate ART on Dual Echo (HDsv). */
        if(( value_system_flag != VALUE_SYSTEM_SVEM ) &&
           ( value_system_flag != VALUE_SYSTEM_SVDM ))
        {
            deactivate_ioption( PSD_IOPT_MILDNOTE );
        }

        deactivate_ioption( PSD_IOPT_IR_PREP );
        deactivate_ioption( PSD_IOPT_MSDE );

        if ( (PSD_OFF == exist(opmedal)) || (PSD_ON == exist(opvibrant)) )
        {  /* 3D Dual Echo  or VIBRANT-Flex */
            deactivate_ioption( PSD_IOPT_FLUORO );
            deactivate_ioption( PSD_IOPT_SMART_PREP );
        }
        if ( PSD_ON == exist(opvibrant) ) 
        {
            deactivate_ioption( PSD_IOPT_NAV );
        }
    }

    if ( (strstr(coilInfo[0].coilName, "R_BREAST") != NULL) ||
         (strstr(coilInfo[0].coilName, "L_BREAST") != NULL) ||
         (strstr(coilInfo[0].coilName, "BreastLeft") != NULL) ||
         (strstr(coilInfo[0].coilName, "BreastRight") != NULL) ||
         (strstr(coilInfo[0].coilName, "7Ch BreastL") != NULL) ||
         (strstr(coilInfo[0].coilName, "7Ch BreastR") != NULL) ||
         (strstr(coilInfo[0].coilName, "breast L") != NULL) ||
         (strstr(coilInfo[0].coilName, "breast R") != NULL) ||
         (strstr(coilInfo[0].coilName, "BrstL") != NULL) ||
         (strstr(coilInfo[0].coilName, "BrstR") != NULL) ||
         (strstr(coilInfo[0].coilName, "BREASTPA R") != NULL) ||
         (strstr(coilInfo[0].coilName, "BREASTPA L") != NULL) )
    {
        disable_ioption( PSD_IOPT_ASSET );
    }

    if( (feature_flag & MERGE) || (feature_flag & MULTI_ECHO) )
    {
        deactivate_ioption( PSD_IOPT_NAV );
        deactivate_ioption( PSD_IOPT_ZIP_1024 );
        deactivate_ioption( PSD_IOPT_IR_PREP );
        deactivate_ioption( PSD_IOPT_CARD_GATE );
        deactivate_ioption( PSD_IOPT_RESP_TRIG );
        deactivate_ioption( PSD_IOPT_T2_PREP );
        deactivate_ioption( PSD_IOPT_IR_PREP );
        deactivate_ioption( PSD_IOPT_FLUORO );
        deactivate_ioption( PSD_IOPT_MULTI_STATION );
        deactivate_ioption( PSD_IOPT_ZIP_1024 );
        deactivate_ioption( PSD_IOPT_SMART_PREP );
        deactivate_ioption( PSD_IOPT_MPH );
        deactivate_ioption( PSD_IOPT_DYNPL );
        deactivate_ioption( PSD_IOPT_MSDE );
        if( idealiq_flag )
        {
            deactivate_ioption( PSD_IOPT_SSRF );
            deactivate_ioption( PSD_IOPT_ASSET );
            activate_ioption( PSD_IOPT_ARC );
            enable_ioption( PSD_IOPT_ARC );
            deactivate_ioption( PSD_IOPT_SLZIP_X4 );
        }
        else if ( PSD_ON == exist(opmerge) )
        {
            activate_ioption( PSD_IOPT_ARC );
            enable_ioption( PSD_IOPT_ARC );
            activate_ioption( PSD_IOPT_FLOW_COMP );
            enable_ioption( PSD_IOPT_FLOW_COMP );
            deactivate_ioption( PSD_IOPT_IDEAL );
        }
        else
        {
            activate_ioption( PSD_IOPT_FLOW_COMP );
            enable_ioption( PSD_IOPT_FLOW_COMP );
            deactivate_ioption( PSD_IOPT_IDEAL );
        }
        if( value_system_flag == PSD_OFF )
        {
            if (PSD_OFF == exist(opswan)) 
               deactivate_ioption( PSD_IOPT_MILDNOTE );
        }
    }

    if( feature_flag & QUICKSTEP )
    {
        activate_ioption( PSD_IOPT_ARC );
        enable_ioption( PSD_IOPT_ARC );
        deactivate_ioption( PSD_IOPT_SSRF );
        deactivate_ioption( PSD_IOPT_NAV );
        deactivate_ioption( PSD_IOPT_MILDNOTE );
        deactivate_ioption( PSD_IOPT_ZIP_1024 );
        deactivate_ioption( PSD_IOPT_IR_PREP );
        deactivate_ioption( PSD_IOPT_CARD_GATE );
        deactivate_ioption( PSD_IOPT_RESP_TRIG );
        deactivate_ioption( PSD_IOPT_T2_PREP );
        deactivate_ioption( PSD_IOPT_IR_PREP );
        deactivate_ioption( PSD_IOPT_ZIP_1024 );
        deactivate_ioption( PSD_IOPT_SMART_PREP );
        deactivate_ioption( PSD_IOPT_IDEAL );
        deactivate_ioption( PSD_IOPT_ASSET );
        deactivate_ioption( PSD_IOPT_MSDE );
    }

    if( disco_flag )
    { 
        deactivate_ioption( PSD_IOPT_FLUORO );
        deactivate_ioption( PSD_IOPT_IDEAL );
        deactivate_ioption( PSD_IOPT_ASSET );
        set_required_disabled_option( PSD_IOPT_EDR );
        disable_ioption( PSD_IOPT_MPH );
        set_disallowed_option( PSD_IOPT_MPH );
        activate_ioption( PSD_IOPT_FLEX );
        enable_ioption( PSD_IOPT_FLEX );
        deactivate_ioption( PSD_IOPT_MSDE );

        /* the following are for single echo mode */
        if( PSD_OFF == exist(opmedal) )
        {
            activate_ioption( PSD_IOPT_ARC );
            enable_ioption( PSD_IOPT_ARC );
            deactivate_ioption( PSD_IOPT_ASSET );
            deactivate_ioption( PSD_IOPT_IR_PREP );
            deactivate_ioption( PSD_IOPT_CARD_GATE );
            deactivate_ioption( PSD_IOPT_RESP_TRIG );
            deactivate_ioption( PSD_IOPT_MILDNOTE );
            disable_ioption( PSD_IOPT_NAV );
        }
    }

    if(checkOptionKey( SOK_MPHVAR ))
    {
        deactivate_ioption( PSD_IOPT_DYNPL );
    }

    if(!mild_note_support)
    {
        deactivate_ioption( PSD_IOPT_MILDNOTE );
    }

    if(exist(opmultistation) != PSD_OFF)
    {
        deactivate_ioption( PSD_IOPT_DYNPL );
    }

    if (exist(opvquant) > 1)
    {
        disable_ioption( PSD_IOPT_FLEX );
    }

    if( (Absent == ftMRAKey) && !(feature_flag & QUICKSTEP) )
    {
        disable_ioption (PSD_IOPT_FLUORO);
    }

    /* YMSmr11374 */
    if( value_system_flag == VALUE_SYSTEM_HDE )
    {
        deactivate_ioption( PSD_IOPT_ARC );
    }
    if ( arc_research_flag)
    {
        set_required_disabled_option(PSD_IOPT_ARC);
    }

    if ( (exist(op3dcine_fiesta)==PSD_ON) ||
        (exist(op3dcine_spgr) == PSD_ON) ||
        (exist(op4dflow)==PSD_ON) )
    {
        deactivate_ioption( PSD_IOPT_ASSET );
        set_required_disabled_option(PSD_IOPT_ARC);
        set_required_disabled_option(PSD_IOPT_EDR);
        set_required_disabled_option(PSD_IOPT_CARD_GATE);

        deactivate_ioption( PSD_IOPT_SMART_PREP );
        deactivate_ioption( PSD_IOPT_SSRF );
        deactivate_ioption( PSD_IOPT_IR_PREP );

        deactivate_ioption( PSD_IOPT_IDEAL );
        deactivate_ioption( PSD_IOPT_T2_PREP );
        deactivate_ioption( PSD_IOPT_SQR_PIX );
        deactivate_ioption( PSD_IOPT_FLUORO );
        deactivate_ioption( PSD_IOPT_MULTI_STATION );
        deactivate_ioption( PSD_IOPT_RESP_TRIG );
        deactivate_ioption( PSD_IOPT_NAV );
        deactivate_ioption( PSD_IOPT_MPH );
        deactivate_ioption( PSD_IOPT_DYNPL );
        deactivate_ioption( PSD_IOPT_MILDNOTE );
        deactivate_ioption( PSD_IOPT_ZIP_1024 );
        deactivate_ioption( PSD_IOPT_SLZIP_X4 );

        if (!(exist(op4dflow)==PSD_ON))
        {
            deactivate_ioption( PSD_IOPT_NOP_WRAP );
        }

    }

    if( Absent == BODYNAVKey )
    { 
        if( (feature_flag & (LAVA | MEDAL)) || de3d_flag ) 
        {
            deactivate_ioption( PSD_IOPT_NAV );
        }
        else if( ifir_flag )
        {
            disable_ioption ( PSD_IOPT_NAV );
            deactivate_ioption( PSD_IOPT_NAV );
            set_required_disabled_option( PSD_IOPT_RESP_TRIG );
        }
    }

    if( Absent == NavigatorKey )
    {
        if( ((PSD_GE == exist(oppseq)) || (PSD_SPGR == exist(oppseq)) || (PSD_SSFP == exist(oppseq))) 
            && !de3d_flag && !(feature_flag & (LAVA | MEDAL)) && !ifir_flag )
        {
            deactivate_ioption( PSD_IOPT_NAV );
        }
    }

    if( (Absent == BODYNAVKey) && (Absent == NavigatorKey) )
    {
        deactivate_ioption( PSD_IOPT_NAV );
    }

    return SUCCESS;
}

STATUS
cvevaliopts( void )
{
    if( ((exist(opstation) > 1) && existcv(opstation))
        || ((rhfrsize < 128) && (exist(opsmartprep) == PSD_OFF)) )
    {
        disable_ioption( PSD_IOPT_SMART_PREP );
    }

    if( (existcv(opxres) && exist(opxres) > 512) ||
        (existcv(opyres) && exist(opyres) > 512) )
    {
        disable_ioption(PSD_IOPT_ZIP_512);
        disable_ioption(PSD_IOPT_NOP_WRAP);
        disable_ioption(PSD_IOPT_ASSET);
    }

    /* MRIhc00484 *//* FIESTA-C  06/10/2005 YI */
    if((exist(opnex) > 1) && (pc_mode == PC_BASIC)) 
    {
        disable_ioption(PSD_IOPT_ASSET);
    }

    /* SVBranch HCSDM00104560	Lock NPW with SWAN phase imaging */
    if((PSD_ON == existcv(opphaseimage)) && (PSD_ON == exist(opphaseimage)) && (PSD_ON == swan_flag))
    {
        disable_ioption(PSD_IOPT_NOP_WRAP);
    }


    if(ugfsf_flag) {
        disable_ioption(PSD_IOPT_FLUORO);
        disable_ioption(PSD_IOPT_MULTI_STATION);
    }

    if(Absent == IDEAL3DKey)
    {
       disable_ioption(PSD_IOPT_IDEAL);
    }
    
    /* MRIhc32862 -- slice ASSET for breast coil is only supported by 
       3D Fast SPGR or VIBRANT mode. Lock out slice ASSET for other modes until
       it is tested later.
     */
    if ( !(feature_flag & VIBRANT) 
         && !( aspir_override && (PSD_SAG == opplane) && (feature_flag & BRAVA))  )
    {
        if ( ((strstr( coilInfo[0].coilName, "BREAST") != NULL) ||
             (strstr( coilInfo[0].coilName, "Breast") != NULL)) && 
             ((exist(opplane) == PSD_SAG) || ((exist(opplane) == PSD_OBL) && 
             (exist(opobplane) == PSD_SAG))) )
        {                                     
            disable_ioption( PSD_IOPT_ASSET );
        }   
    }
  
    /*  MRIhc34181 */
    if ( (feature_flag & VIBRANT) && (exist(opspecir) == PSD_ON) )
    {
        disable_ioption( PSD_IOPT_SQR_PIX );
    }

    if (arc_research_flag)
    {
        set_required_disabled_option( PSD_IOPT_ARC );
    }

    if (headneck_pos_scan)
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
        disable_ioption(PSD_IOPT_SSRF);
        disable_ioption(PSD_IOPT_MSDE);

        set_required_disabled_option( PSD_IOPT_MILDNOTE );
        set_required_disabled_option( PSD_IOPT_SLZIP_X2 );
        set_required_disabled_option( PSD_IOPT_EDR );
    }

@inline cal3d.e cal3d_cvevaliopts

    return SUCCESS;
}

/* is_vast_on
   
   Description:
   This function returns a flag (PSD_ON or PSD_OFF) indicating whether
   all of the conditions to enable VAST mode are satisfied.

   Inputs:
   CVs and options keys are the only inputs to the function.

   Outputs:
   return value is PSD_ON or PSD_OFF
   No global variables are changed by this function.
   
*/
/* YMSmr08077 & MRIhc12595 12/14/2005 YI & CRM */
int
is_vast_on( void )
{
    int vast_flag = PSD_OFF;

    /* MRIhc48389 03/15/2010 JX */
    heart3d_flag = PSD_OFF;

#ifdef PSD_HW
    FSFiestaKey = !checkOptionKey( SOK_FIESTA3DFS );
    NavigatorKey = !checkOptionKey( SOK_NAVIGATOR );
    MDEKey = !checkOptionKey( SOK_DELENHMT3D ); 
    Heart3DKey = !checkOptionKey( SOK_HEART3D );
#else /* !PSD_HW */
    FSFiestaKey = Present;
    MDEKey = Present;
    NavigatorKey = Present;
    Heart3DKey = Present;
#endif /* PSD_HW */
    
    /* MRIge84180, MRIge85378 -- Enable VAST mode for gated 3D FIESTA */
    if( (PSD_ON == exist(opcgate)) && (PSD_OFF == exist(oprtcgate)) && (exist(op3dcine_fiesta)==PSD_OFF) 
       && (exist(op3dcine_spgr) == PSD_OFF) && (exist(op4dflow)==PSD_OFF) ) 
    {
        if( (PSD_GE == exist(oppseq)) || (PSD_SPGR == exist(oppseq)) )
        {
            if( ((Present == MDEKey) && (PSD_ON == (irprep_flag))) ||
                (Present == Heart3DKey) )
            {
                vast_flag = PSD_ON;
            }        
        }
        else if( PSD_ON == ssfp_flag )
        {
            if( (Present == FSFiestaKey) && (PSD_OFF == pcfiesta_flag) )
            {
                vast_flag = PSD_ON;
            }
        }

        if( (Present == NavigatorKey) && (PSD_ON == exist(opnav)) )
        {
            vast_flag = PSD_ON;
        }

        if( ((Present == Heart3DKey) || ((Present == MDEKey) && (PSD_ON == (irprep_flag)))) && vast_flag )
        {
            heart3d_flag = PSD_ON;
        }
    }

    if( ifir_flag )
    {
        vast_flag = PSD_ON;
    }

    return vast_flag;
}

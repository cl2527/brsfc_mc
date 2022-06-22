#ifndef _SPIRAL_H_
#define _SPIRAL_H_

#define DYNA_OFF      0
#define DYNA_MASK     1
#define DYNA_CONTRAST 2
#define DYNA_SUBTRACT 3

#define PM_OFF     0
#define PM_SELFGEN 1
#define PM_ADDECHO 2

/* view table data structure for spiral scans */
typedef struct spiral_view {
    short phase;
    short slice;
    short leaf;
} SPIRAL_VIEW;
#if ESEMAJOR<27
float floatsEpsilon();
short floatsAlmostEqualEpsilons( const float a, const float b, const unsigned int neps);
#endif
void fprintf_timestamp(FILE *fp);
STATUS enable_tracker(void);
STATUS set_spiral_spoilers(void);
STATUS set_spiral_spoilers_aux (float xarea, 
                                float yarea,
                                float *a_xspoil,
                                int   *pw_xspoila,
                                int   *pw_xspoil,
                                int   *pw_xspoild,
                                float *a_yspoil,
                                int   *pw_yspoila,
                                int   *pw_yspoil,
                                int   *pw_yspoild);
STATUS set_gzvl_params();
STATUS brs_gzvl_adjust_te();

#if ESEMAJOR >= 15
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
void cv_cnv_endian_CAL_PARAM(CAL_PARAM *c);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

STATUS
stretch_pulse( const INT slot,
               CHAR *extname,
               const RF_PULSE_INFO rfInfo[],
               INT *res,
               short **wavespace );
void create_gzvl(int pos, int idx);
STATUS set_gz_encode(int sl, int idx);

void rotate_spiral(int view, int slabindex, float additional);
STATUS spiral_ps2core();
STATUS PlayHTR(float scale);
STATUS ShiftTE(int period);
STATUS ResetGoldenRatio();
STATUS play_pass_pkt();
STATUS write_cine_out();
STATUS spiral_scancore();
STATUS spiral_scancore_phase(int phaseindex);
STATUS spiral_gate_scancore();
STATUS spiral_gate_ps2core();
void brs_genviewtab(int nleaves, 
                    int nphases,
                    int slquant,
                    int vieword,
                    int nfolds,
                    int leafskip,
                    int leafgroup,
                    int dofracz,
                    int fracz_fact,
                    int debug,
                    int centerkz,
                    int * fs_slice,
                    int * jumptab,
                    int * rzseg,
                    int * rzvps,
                    SPIRAL_VIEW *vt);
int brs_getviews(int *view, int *tphase, int *slice, int *acqcount, 
                 int trigstate, int nacqs, int *Te, int *Tr);


#endif

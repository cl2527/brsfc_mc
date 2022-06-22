#ifndef __VDS_H__
#define __VDS_H__
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
void calc_vds(double slewmax, double gradmax, double Tgsample, double Tdsample, int Ninterleaves, double *fov, int numfov, double krmax, int ngmax, double **xgrad, double **ygrad, int *numgrad);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

#ifndef __VDS_INV_H__
#define __VDS_INV_H__
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
void calc_vds_inv(double slewmax, double gradmax, double Tgsample,double Tdsample, int Ninterleaves, double *fov, double fovpow, double krmax, double rscale, int ngmax, double **xgrad, double **ygrad, int *numgrad);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

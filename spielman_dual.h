#ifndef __SPIELMAN_DUAL_H__
#define __SPIELMAN_DUAL_H__
/*#include<stdio.h>
#include<stdlib.h>
#include<math.h>
*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
void spielman_dual(float gmax, float slewmax, int xres, int xres2, float fov, float alpha, float alpha2, int nl, float dt, int gradork, float sampfact, float sampfact2, float *outarray, int *length);
void spielman_dual_calcgrad(float *workarray, double gamma, double lambda, double omega, double alpha, double tau, double dtau, double dphi);
double find2slewstart(double desired, double slewmax, double gmax, double gamma, double lambda, double omega, double alpha);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#ifndef __SPIELMAN_H__
#define __SPIELMAN_H__
/*#include<stdio.h>
#include<stdlib.h>
#include<math.h>
*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
void spielman(float gmax, float slewmax, int xres, float fov, float alpha, int nl, float dt, int gradork, float sampfact, float *outarray, int *length);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#ifndef _ROTATION_H_
#define _ROTATION_H_

float detMatrix(float *A);
void PrintMat(long * A, FILE * fp);
STATUS RotateMat(float * x, float * A, float *y);
STATUS CalcRotationMatrix(long *rot_src, long *rot_dest, 
                          float *trans, int calcrot_debug);

#endif

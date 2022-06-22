/*************************************************************/ 
/* Rotation matrix functions                                 */
/*************************************************************/

@host RotationPredownload

/* calculates the maxtrix determinant  
 * A is an 9 element array of floats
 */
float detMatrix(float *A)
{
  int i,j;
  float factor1, factor2, result=0.0;
  for(i=0; i<3; i++) {
    factor1 = 1.0;
    factor2 = 1.0;
    for(j=0; j<3; j++){
      factor1 *= A[3*j+(j+i)%3];
      factor2 *= A[3*j+(2-j+i)%3];
    }
    result += factor1 - factor2;
  }
  return result;
}

/* calculates the vector y = A .x where
 *   x,y   are vectors (array of 3 floats);
 *   A     is a rotation matrix (array of 9 floats)
 */
STATUS RotateMat(float * x, float * A, float *y)
{
  int i,j;
  for (i=0; i<3; i++) {
    y[i]=0;
    for (j=0;j<3;j++) y[i] += A[3*i+j]*x[j];
  }
  return SUCCESS;
}

/* prints matrix A to file fp
 * A is matrix of 9 long ints
 */
void PrintMat(long * A, FILE * fp)
{
  int i,j;
  
  for (i=0; i< 3; i++)
  {
    for (j=0; j<2; j++) fprintf(fp, "%ld\t", A[3*i+j]);
    fprintf(fp, "%ld\n", A[3*i+2]);
  }
}

/* Given a plane with rotation matrix rot_src.
 * Given a second plane with rotation matrix rot_dest
 * CalcRotationMatrix will calculate the transformation
 * matrix trans that will transform a vector V from the first
 * plane to the second : W = trans.V
 *   - rot_src and rot_dest are GE style rotation matrices before
 *     they are being scaled with scalerotmats
 *   - trans is an actual rotation matrix (|det(trans)|=1) with 
 *     float elements
 */

STATUS CalcRotationMatrix(long *rot_src, long *rot_dest, 
                          float *trans, int calcrot_debug)
{
  float frot_src[9], frot_dest[9], ifrot_dest[9];
  float drot_src, drot_dest;
  int i =0, j=0, k=0;
  FILE *fp;
  
  for (i=0; i<9; i++){
    frot_src[i] = (float)rot_src[i];
    frot_dest[i] = (float)rot_dest[i];
  }
  drot_src = powf(detMatrix(frot_src), 1.0/3.0);
  if (floatsAlmostEqualEpsilons(drot_src, 0.0, 2)) drot_src = 1.0;
  drot_dest = powf(detMatrix(frot_dest), 1.0/3.0);
  if (floatsAlmostEqualEpsilons(drot_dest, 0.0, 2)) drot_dest = 1.0;
  for(i=0;i<9;i++)
  {
    frot_src[i]  /=  drot_src;
    frot_dest[i] /=  drot_dest;
  } 
 
  ifrot_dest[0] = -frot_dest[5] * frot_dest[7] + frot_dest[4] * frot_dest[8];
  ifrot_dest[1] =  frot_dest[2] * frot_dest[7] - frot_dest[1] * frot_dest[8];
  ifrot_dest[2] = -frot_dest[2] * frot_dest[4] + frot_dest[1] * frot_dest[5];
  ifrot_dest[3] =  frot_dest[5] * frot_dest[6] - frot_dest[3] * frot_dest[8];
  ifrot_dest[4] = -frot_dest[2] * frot_dest[6] + frot_dest[0] * frot_dest[8];
  ifrot_dest[5] =  frot_dest[2] * frot_dest[3] - frot_dest[0] * frot_dest[5];
  ifrot_dest[6] = -frot_dest[4] * frot_dest[6] + frot_dest[3] * frot_dest[7];
  ifrot_dest[7] =  frot_dest[1] * frot_dest[6] - frot_dest[0] * frot_dest[7];
  ifrot_dest[8] = -frot_dest[1] * frot_dest[3] + frot_dest[0] * frot_dest[4];
  for(i=0; i<9;i++)
  {
    trans[i] = 0.0;
    for(j=0; j<3; j++) trans[i] += ifrot_dest[3*(i/3)+j] * frot_src[3*j+(i%3)];  
  }
    
  
  if (calcrot_debug)
  {
    fp = fopen(DEBUGFILE(calcrot.debug), "w");
    fprintf(fp, "frot_src\n");
    for(i=0; i< 3; i++)
    {
      for(j=0; j < 3; j++) fprintf(fp,"%f\t", frot_src[3*i+j]);
      fprintf(fp, "\n");
    }
    fprintf(fp, "frot_dest %d\n", k);
    for(i=0; i< 3; i++)
    {
      for(j=0; j < 3; j++) fprintf(fp,"%f\t", frot_dest[3*i+j]);
      fprintf(fp, "\n");
    }
    fprintf(fp, "ifrot_dest %d\n", k);
    for(i=0; i< 3; i++)\
    {
      for(j=0; j < 3; j++) fprintf(fp,"%f\t", ifrot_dest[3*i+j]);
      fprintf(fp, "\n");
    }
    fclose(fp);
  }
  
 
  return(SUCCESS); 
}

/* copies of predownload functions above 
 * for use in rsp
 */
@rsp RotationRsp


/* calculates the vector y = A .x where
 *   x,y   are vectors (array of 3 floats);
 *   A     is a rotation matrix (array of 9 floats)
 */
STATUS RotateMat(float * x, float * A, float *y)
{
  int i,j;
  for (i=0; i<3; i++) {
    y[i]=0;
    for (j=0;j<3;j++) y[i] += A[3*i+j]*x[j];
  }
  return SUCCESS;
}

/* prints matrix A to file fp
 * A is matrix of 9 long ints
 */
void PrintMat(long * A, FILE * fp)
{
  int i,j;
  
  for (i=0; i< 3; i++)
  {
    for (j=0; j<2; j++) fprintf(fp, "%ld\t", A[3*i+j]);
    fprintf(fp, "%ld\n", A[3*i+2]);
  }
}


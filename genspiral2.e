@host headers
#include "spielman.h"
#include "spielman_dual.h"
#include "vds.h"
#include "vds_inv.h"
/*
void spielman(float gmax, float slewmax, int xres, float fov, float alpha, int nl, float dt, int gradork, float sampfact, float *outarray, int *length);
*/
void genspiral2(int   xres, 
                float alpha, 
                float alpha_center,
                int   numleaves,
                float sampfact,
                float sampfact_center,
                float matrixsize_center,
                float rbw, 
                float recratio,
                float pFOV,
                float rscale,
                float fovpow,
                int   type,
                float grad_derate, 
                float *gslew,
                float *grad,
                _cvint *gradlen,
                float *fov0,
                float *fov1,
                float *fov2,
                float *xarea,
                float *yarea,
                int   *xgrad,
                int   *ygrad,
                int   *ramplength);

/* INPUT   
      opxres           -> xres
      brs_alpha        -> alpha
      brs_alpha_center -> alpha_center
      brs_numleaves    -> numleaves
      brs_sampfact     -> sampfact
      brs_sampfact_center -> sampfact_center
      brs_matrixsize_center -> matrixsize_center
      oprbw            -> rbw
      brs_recratio     -> recratio
      opfov            -> pFOV
      brs_rscale       -> rscale
      brs_fovpow       -> fovpow
      brs_type         -> type
   OUTPUT
      brs_gslew        -> *gslew
      brs_grad         -> *grad
      brs_gradlen      -> *gradlen ( type _cvint !!!!! )
      brs_fov0         -> *fov0
      brs_fov1         -> *fov1
      brs_fov2         -> *fov2
      brs_xarea        -> *xarea
      brs_yarea        -> *yarea
      brs_xgrad        -> *xgrad
      brs_ygrad        -> *ygrad
      brs_ramplength   -> *ramplength
 */

void genramp(
             int   *xgrad,
             int   *ygrad,
             int   length,
             float gslew,
             int   *ramplength,
             float *xarea,
             float *yarea
            );
float compute_area(int *waveform, int length);
void mark_end(int *waveform, int length);
void truncate_waveform(int    *xin, 
                       int    *yin,
                       int    *xout,
                       int    *yout,
                       int    length,
                       float  gslew, 
                       int    *ramplength,
                       float  *xarea,
                       float  *yarea);


@host functions
void genspiral2(int   xres, 
                float alpha, 
                float alpha_center,
                int   numleaves,
                float sampfact,
                float sampfact_center,
                float matrixsize_center,
                float rbw, 
                float recratio,
                float pFOV,
                float rscale,
                float fovpow,
                int   type,
                float grad_derate, 
                float *gslew,
                float *grad,
                _cvint *gradlen,
                float *fov0,
                float *fov1,
                float *fov2,
                float *xarea,
                float *yarea,
                int   *xgrad,
                int   *ygrad,
                int   *ramplength)
{
	int length;
	int i;
	float maxgrad;
	double *gx, *gy;
	double fov[3];

	gx = NULL;
	gy = NULL;
	maxgrad = cfxfs;

  brs_gmax = loggrd.xfs * grad_derate;
#if ESEMAJOR >= 24
  brs_slewmax = cfsrmodeact*100;
#else  
  brs_slewmax = (cfsrmodeact > 103) ? 10300 : cfsrmodeact*100;
#endif  
  *gslew = brs_slewmax;

	switch(type) {
		case 0:  /* Spielman variable density spiral */
      *gslew = (0.83*brs_slewmax>7700) ? 7700 : 0.83*brs_slewmax; 
			spielman(brs_gmax, *gslew, xres, pFOV/10.0, alpha, numleaves,
               cfswgut*(1.0e-6), 0, sampfact, grad, &length);
			*(gradlen->addr) = length;
			gradlen->existflag = 1;
			break;
		
    case 1:  /* Spielman variable dual density spiral */
			spielman_dual(brs_gmax, *gslew, matrixsize_center, xres, 
                    pFOV/10.0, alpha_center, alpha, numleaves, 
                    cfswgut*(1.0e-6), 0, sampfact_center, sampfact, 
                    grad, &length);
			*(gradlen->addr) = length;
			gradlen->existflag = 1;
			break;
		
    case 2:  /* hargreaves variable density spiral */
		  *fov0 = alpha;
			fov[0] = (*fov0)*pFOV/10.0;
			fov[1] = *fov1;
			*fov2 = (sampfact*pFOV/10.0-fov[0])/
                  (xres*xres/(4.0*pFOV*pFOV/100.0));
			fov[2] = *fov2;
			calc_vds(*gslew, brs_gmax, (1.0/(2.0*rbw*1000.0))/10.0, 
               1.0/(2.0*rbw*1000.0/recratio), numleaves, fov, 3, 
               xres/(2.0*pFOV/10.0), 1048576, &gx, &gy, &length);
			length = (int)(length / 
                       ((cfswgut*(1.0e-6))/((1.0/(2.0*rbw*1000.0))/10.0))
                     + 0.5);
			length = ((int)(length/4))*4;
			if (length > MAX_LEAF_LEN-RAMP_LENGTH)
				length = MAX_LEAF_LEN-RAMP_LENGTH;
			*(gradlen->addr) = length;
			gradlen->existflag = 1;
			break;
      
		case 3:  /* modified hargreaves variable density spiral */
			fov[1] = (pFOV/10.0*alpha - pFOV/10.0*sampfact)/
                (1.0 - 1.0/(pow(rscale,fovpow)+1.0));
			fov[0] = pFOV/10.0*alpha - fov[1];

			calc_vds_inv(*gslew, brs_gmax, (1.0/(2.0*rbw*1000.0))/10.0,
                   1.0/(2.0*rbw*1000.0/recratio), numleaves, fov, 
                   alpha, xres/(2.0*pFOV/10.0), rscale, 1048576, 
                   &gx, &gy, &length);
			length = (int)(length / 
                        ((cfswgut*(1.0e-6))/((1.0/(2.0*rbw*1000.0))/10.0))
                     + 0.5);
			length = ((int)(length/4))*4;
			if (length > MAX_LEAF_LEN-RAMP_LENGTH)
				length = MAX_LEAF_LEN-RAMP_LENGTH;
			gradlen->fixedflag = 0;
			*(gradlen->addr) = length;
			gradlen->existflag = 1;
			break;
	}


	if ((type == 0) || (type == 1))
	{
		for(i = 0; i < length; i++)
		{
			if (grad[2*i]   >  maxgrad) grad[2*i]   =  maxgrad;
			if (grad[2*i]   < -maxgrad) grad[2*i]   = -maxgrad;
			if (grad[2*i+1] >  maxgrad) grad[2*i+1] =  maxgrad;
			if (grad[2*i+1] < -maxgrad)	grad[2*i+1] = -maxgrad;

			xgrad[i] = ((int)(grad[i*2]*32767/maxgrad)) & 0xfffffffe;
			ygrad[i] = ((int)(grad[i*2+1]*32767/maxgrad)) & 0xfffffffe;
		}
	} else if ((type == 2) || (type == 3)) 
	{
		int downsamp = (int)((cfswgut*(1.0e-6))/((1.0/(2.0*rbw*1000.0))/10.0) + 0.5);
		for(i = 0; i < length; i++)
		{
			if (gx[downsamp*i] >  maxgrad) gx[downsamp*i] =  maxgrad;
			if (gx[downsamp*i] < -maxgrad) gx[downsamp*i] = -maxgrad;
			if (gy[downsamp*i] >  maxgrad) gy[downsamp*i] =  maxgrad;
			if (gy[downsamp*i] < -maxgrad) gy[downsamp*i] = -maxgrad;

			xgrad[i] = ((int)(gx[i*downsamp]*32767/maxgrad)) & 0xfffffffe;
			ygrad[i] = ((int)(gy[i*downsamp]*32767/maxgrad)) & 0xfffffffe;
		}
		if (gx != NULL) free(gx);
		if (gy != NULL)	free(gy);
	}

  *xarea = compute_area(xgrad, length);
  *yarea = compute_area(ygrad, length);
  genramp(xgrad, ygrad, length, *gslew, ramplength, xarea, yarea);
  *xarea *= cfswgut*maxgrad/32767;
  *yarea *= cfswgut*maxgrad/32767;
  mark_end(xgrad, length + *ramplength);
  mark_end(ygrad, length + *ramplength);

}

void genramp(
             int   *xgrad,
             int   *ygrad,
             int   length,
             float gslew,
             int   *ramplength,
             float *xarea,
             float *yarea
            )
{
	float t_ramplength;
	float maxgrad = cfxfs;
  int length2, i;
	float incx;
	float incy;
  
  
  t_ramplength = sqrt(  xgrad[length-1]*xgrad[length-1]
                      + ygrad[length-1]*ygrad[length-1])
                 * maxgrad/32767.0/(gslew) * 1.0e6 / cfswgut;
	*ramplength = (int)ceilf(t_ramplength);

	length2 = length + *ramplength;
	
  incx = (float)xgrad[length-1]/(*ramplength);
	incy = (float)ygrad[length-1]/(*ramplength);

	for (i = length; i < length2; i++) {
		xgrad[i] = ((int)(xgrad[length-1] - incx*(i - length))) & 0xfffffffe;
		ygrad[i] = ((int)(ygrad[length-1] - incy*(i - length))) & 0xfffffffe;
	}

	*xarea += compute_area(xgrad+length-1, length2-length+1);
	*yarea += compute_area(ygrad+length-1, length2-length+1);

}

float compute_area(int *waveform, int length)
{
  int area = 0;
  int i;
  for(i = 1; i < length; i++) {
	  area += 0.5*(waveform[i] + waveform[i-1]);
	}
  return area;
}

void mark_end(int *waveform, int length)
{
  waveform[length-1] = waveform[length-1] | 0x01;
}

void truncate_waveform(int    *xin, 
                       int    *yin,
                       int    *xout,
                       int    *yout,
                       int    length,
                       float  gslew, 
                       int    *ramplength,
                       float  *xarea,
                       float  *yarea)
{
  int i;
	float maxgrad = cfxfs;
  for (i=0; i<length; i++) {
    xout[i]=xin[i];
    yout[i]=yin[i];
  } 
  *xarea = compute_area(xout, length);
  *yarea = compute_area(yout, length);
  genramp(xout, yout, length, gslew, ramplength, xarea, yarea);
  *xarea *= cfswgut*maxgrad/32767;
  *yarea *= cfswgut*maxgrad/32767;
  mark_end(xout, length + *ramplength);
  mark_end(yout, length + *ramplength);
 
}
                       

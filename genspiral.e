@host headers
#include "spielman.h"
#include "spielman_dual.h"
#include "vds.h"
#include "vds_inv.h"

/*
void spielman(float gmax, float slewmax, int xres, float fov, float alpha, int nl, float dt, int gradork, float sampfact, float *outarray, int *length);
*/
void genspiral();


@host functions
void genspiral()
{
	int length;
	int length2;
	float incx;
	float incy;
	int i;
	float maxgrad;
	/*float mag;
	int iinc;*/
	double *gx, *gy;
	double fov[3];

	gx = NULL;
	gy = NULL;
	maxgrad = cfxfs;

  brs_gmax = loggrd.xfs;
  brs_slewmax = (cfsrmodeact > 103) ? 10300 : cfsrmodeact*100;
  brs_gslew = brs_slewmax;

	switch(brs_type) {
		case 0:  /* Spielman variable density spiral */
                        brs_gslew = (0.83*brs_slewmax>7700) ? 7700 : 0.83*brs_slewmax; 
			spielman(brs_gmax, brs_gslew, opxres, opfov/10.0, brs_alpha, brs_numleaves, cfswgut*(1.0e-6), 0, brs_sampfact, brs_grad, &length);
			brs_gradlen = length;
			setexist(brs_gradlen, 1);
			break;
		case 1:  /* Spielman variable dual density spiral */
			spielman_dual(brs_gmax, brs_gslew, brs_matrixsize_center, opxres, opfov/10.0, brs_alpha_center, brs_alpha, brs_numleaves, cfswgut*(1.0e-6), 0, brs_sampfact_center, brs_sampfact, brs_grad, &length);
			brs_gradlen = length;
			setexist(brs_gradlen, 1);
			break;
		case 2:  /* hargreaves variable density spiral */
		    brs_fov0 = brs_alpha;
			fov[0] = brs_fov0*opfov/10.0;
			fov[1] = brs_fov1;
			brs_fov2 = (brs_sampfact*opfov/10.0-fov[0])/(opxres*opxres/(4.0*opfov*opfov/100.0));
			fov[2] = brs_fov2;
			calc_vds(brs_gslew, brs_gmax, (1.0/(2.0*oprbw*1000.0))/10.0, 1.0/(2.0*oprbw*1000.0/brs_recratio), brs_numleaves, fov, 3, opxres/(2.0*opfov/10.0), 1048576, &gx, &gy, &length);
			length = (int)(length / ((cfswgut*(1.0e-6))/((1.0/(2.0*oprbw*1000.0))/10.0)) + 0.5);
			length = ((int)(length/4))*4;
			if (length > MAX_LEAF_LEN-RAMP_LENGTH)
				length = MAX_LEAF_LEN-RAMP_LENGTH;
			brs_gradlen = length;
			setexist(brs_gradlen, 1);
			break;
		case 3:  /* modified hargreaves variable density spiral */
			fov[1] = (opfov/10.0*brs_alpha - opfov/10.0*brs_sampfact)/(1.0 - 1.0/(pow(brs_rscale,brs_fovpow)+1.0));
			fov[0] = opfov/10.0*brs_alpha - fov[1];

			/*printf("fov[0] = %f, fov[1] = %f\n", fov[0], fov[1]);*/  /*BOXU*/
			calc_vds_inv(brs_gslew, brs_gmax, (1.0/(2.0*oprbw*1000.0))/10.0, 1.0/(2.0*oprbw*1000.0/brs_recratio), brs_numleaves, fov, brs_alpha, opxres/(2.0*opfov/10.0), brs_rscale, 1048576, &gx, &gy, &length);
			/*BOXU printf("length = %d\n", length);*/
			length = (int)(length / ((cfswgut*(1.0e-6))/((1.0/(2.0*oprbw*1000.0))/10.0)) + 0.5);
			length = ((int)(length/4))*4;
      length = length + brs_extra_len;
			if (length > MAX_LEAF_LEN-RAMP_LENGTH)
				length = MAX_LEAF_LEN-RAMP_LENGTH;
			_brs_gradlen.fixedflag = 0;
			brs_gradlen = length;
			setexist(brs_gradlen, 1);
			break;
	}

	/*length2 = length+RAMP_LENGTH;*/

	brs_xarea = 0;
	brs_yarea = 0;
	if ((brs_type == 0) || (brs_type == 1))
	{
		for(i = 0; i < length; i++)
		{
			if (brs_grad[2*i] > maxgrad)
				brs_grad[2*i] = maxgrad;
			if (brs_grad[2*i] < -maxgrad)
				brs_grad[2*i] = -maxgrad;
			if (brs_grad[2*i+1] > maxgrad)
				brs_grad[2*i+1] = maxgrad;
			if (brs_grad[2*i+1] < -maxgrad)
				brs_grad[2*i+1] = -maxgrad;

			brs_xgrad[i] = ((int)(brs_grad[i*2]*32767/maxgrad)) & 0xfffffffe;
			brs_ygrad[i] = ((int)(brs_grad[i*2+1]*32767/maxgrad)) & 0xfffffffe;

      if (0==brs_areamode)
      {
        if (i > 0) {
          brs_xarea += (brs_xgrad[i] + brs_xgrad[i-1])/2;
          brs_yarea += (brs_ygrad[i] + brs_ygrad[i-1])/2;
        }
      }
      else
      {
          brs_xarea += brs_xgrad[i];
          brs_yarea += brs_ygrad[i];
      }

		}
	} else if ((brs_type == 2) || (brs_type == 3)) 
	{
		int downsamp = (int)((cfswgut*(1.0e-6))/((1.0/(2.0*oprbw*1000.0))/10.0) + 0.5);
    /*printf("downsamp = %d \n", downsamp);
    printf("maxgrad = %f \n", maxgrad);
    printf("gamma = %f \n", GAM);*/
		for(i = 0; i < length; i++)
		{
      if (i>brs_extra_len-1)
      {
        if (gx[downsamp*(i-brs_extra_len)] > maxgrad)
          gx[downsamp*(i-brs_extra_len)] = maxgrad;
        if (gx[downsamp*(i-brs_extra_len)] < -maxgrad)
          gx[downsamp*(i-brs_extra_len)] = -maxgrad;
        if (gy[downsamp*(i-brs_extra_len)] > maxgrad)
          gy[downsamp*(i-brs_extra_len)] = maxgrad;
        if (gy[downsamp*(i-brs_extra_len)] < -maxgrad)
          gy[downsamp*(i-brs_extra_len)] = -maxgrad;
      }

      if (i < brs_extra_len)
      {
        brs_xgrad[i] = ((int)(0*32767/maxgrad)) & 0xfffffffe;
			  brs_ygrad[i] = ((int)(0*32767/maxgrad)) & 0xfffffffe;
      }
      else
      {
			  brs_xgrad[i] = ((int)(gx[(i-brs_extra_len)*downsamp]*32767/maxgrad)) & 0xfffffffe;
			  brs_ygrad[i] = ((int)(gy[(i-brs_extra_len)*downsamp]*32767/maxgrad)) & 0xfffffffe;
      }

      if (0==brs_areamode)
      {
        if (i > 0) {
          brs_xarea += (brs_xgrad[i] + brs_xgrad[i-1])/2;
          brs_yarea += (brs_ygrad[i] + brs_ygrad[i-1])/2;
        }
      }
      else
      {
          brs_xarea += brs_xgrad[i];
          brs_yarea += brs_ygrad[i];
      }
		}
		if (gx != NULL)
			free(gx);
		if (gy != NULL)
			free(gy);
	}
  /*printf("spiral x area %f\n", (float)brs_xarea/32767.0 * maxgrad*GAM*4e-6);
    printf("spiral y area %f\n", (float)brs_yarea/32767.0 * maxgrad *GAM*4e-6);*/
  /*printf("spiral total area %f\n", hypotf((float)brs_xarea*cfswgut*maxgrad/32767.0, (float)brs_yarea*cfswgut*maxgrad/32767.0));*/
  /*printf("spiral end grad x %f\n", (float)brs_xgrad[length-1]*maxgrad/32767.0);
    printf("spiral end grad y %f\n", (float)brs_ygrad[length-1]*maxgrad/32767.0);
    printf("spiral end grad magnitude %f\n", hypotf((float)brs_xgrad[length-1]*maxgrad/32767.0, (float)brs_ygrad[length-1]*maxgrad/32767.0)); */

	float t_ramplength;
	t_ramplength = sqrt(brs_xgrad[length-1]*brs_xgrad[length-1]+brs_ygrad[length-1]*brs_ygrad[length-1])*maxgrad/32767.0/brs_gslew * 1.0e6 / cfswgut;
	brs_ramplength = (int)ceilf(t_ramplength);
	//printf("t_ramplength:  %f\n", t_ramplength);
	//BOXU printf("optimal ramp length:  %d\n", brs_ramplength);

	length2 = length + brs_ramplength;
	incx = (float)brs_xgrad[length-1]/brs_ramplength;
	incy = (float)brs_ygrad[length-1]/brs_ramplength;

	for (i = length; i < length2; i++) {
		brs_xgrad[i] = ((int)(brs_xgrad[length-1] - incx*(i - length))) & 0xfffffffe;
		brs_ygrad[i] = ((int)(brs_ygrad[length-1] - incy*(i - length))) & 0xfffffffe;

    if (0==brs_areamode)
      {
        brs_xarea += (brs_xgrad[i] + brs_xgrad[i-1])/2;
        brs_yarea += (brs_ygrad[i] + brs_ygrad[i-1])/2;
      }
      else
      {
          brs_xarea += brs_xgrad[i];
          brs_yarea += brs_ygrad[i];
      }
	}

	brs_xgrad[length2-1] = brs_xgrad[length2-1] | 0x01;
	brs_ygrad[length2-1] = brs_ygrad[length2-1] | 0x01;

  brsfmx = 0.0;
  brsfmy = 0.0;
  for (i = 1; i < length2+1; i++) 
  {
    brsfmx += -i*4*brs_xgrad[length2-i];
    brsfmy += -i*4*brs_ygrad[length2-i];
	}
  brsfmx = (float)(brsfmx *cfswgut*maxgrad/32767.0);
  brsfmy = (float)(brsfmy *cfswgut*maxgrad/32767.0);

	brs_xarea = brs_xarea*cfswgut*maxgrad/32767.0;
	brs_yarea = brs_yarea*cfswgut*maxgrad/32767.0;
  
  gradfile = fopen("gradx", "w");
	fwrite(brs_xgrad, sizeof(int), length2, gradfile);
	fclose(gradfile);
	
	gradfile = fopen("grady", "w");
	fwrite(brs_ygrad, sizeof(int), length2, gradfile);
	fclose(gradfile);
  
}

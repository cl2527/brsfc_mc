#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*#include <iostream>

using namespace std;*/

void spielman(float gmax, float slewmax, int xres, float fov, float alpha, int nl, float dt, int gradork, float sampfact, float *outarray, int *length)
{
/* Generate a variable density spiral
 * Created by Kressler 10/26/04
 * Based on Kim, MRM 50:214-219 (2003)
 *
 * gmax = maximum gradient amplitude
 * slewmax = maximum slew rate
 * xres = desired matrix size
 * fov = desired field of view
 * alpha = oversampling factor at center of k-space
 * nl = number oof leaves
 * gradork = generate gradient or k-space waveforms (0 = gradient, 1 = k-space)
 * outarray = output array for gradients or k-space data
 * length = length of generated waveform
*/
	double gamma;
	double n;
	double lambda;
	double omega;
	double Ts2a;
	double Tea;
	double Tes;
	double stop1;
	double gampstart;
	double tauprev;
	double t;
	double tau;
	int i;
	float *workarray;
	double Ts2apreround;
	double phi;
	double dtaudt;


	gamma = 4.257e3;
	n = 1.0/(1.0-pow(1.0-2.0*nl/(sampfact*xres), 1.0/alpha));  /* number of turns of spiral to make */
	lambda = (double)xres/(2.0*fov);
	omega = 2.0*M_PI*n;

	Ts2a = pow(gmax*gamma / (lambda*omega / (alpha/2.0+1.0) * pow((alpha/2.0+1.0)*sqrt(slewmax*gamma/(lambda*omega*omega)), (alpha+1)/(alpha/2+1))), (alpha+2)/alpha);  /* time to switch from slew limited to amplitude limited */

	Tea = 1/(gamma*gmax/(lambda*omega)*(alpha+1)); /* ending time of amplitude regime */

	Tes = 1/((alpha/2.0+1.0)*sqrt(slewmax*gamma/(lambda*omega*omega))); /* ending time of slew regime */

	gampstart = pow((gmax*gamma)/(lambda*omega), 1.0/alpha) * pow(slewmax*gamma/(lambda*omega*omega), -(alpha+1)/(alpha*(alpha+2)))
				* pow((alpha/2+1)*Ts2a, (alpha+1)/(alpha+2)) / (alpha+1);
	

	printf("Tes = %f\n", Tes);
	printf("Tea = %f\n", Tea);
	printf("Ts2a = %f\n", Ts2a);
	printf("gampstart = %f\n", gampstart);
	
	Ts2apreround = Ts2a;
	
	Ts2a = floor(Ts2a/dt)*dt;   /* round everything down to the nearest increment of dt */
	Tea = floor(Tea/dt)*dt;
	Tes = floor(Tes/dt)*dt;

	phi = omega * (pow(sqrt(slewmax*gamma/(lambda*omega*omega))*(alpha/2+1)*Ts2apreround,1/(alpha/2+1)) - pow(gamma*gmax/(lambda*omega)*(alpha+1)*(gampstart), 1/(alpha+1)));
	printf("phi = %f\n", phi);

	if (Tes < Ts2a)
		stop1 = Tes;
	else
		stop1 = Ts2a;

	/* time for first point of amplitude limited regime 
	 * necessary to produce a continuously increasing tau
	 * and thus a smoothly varying gradient waveform 
	 * This is the part the Kim paper gets wrong, as it just starts
	 * at Ts2a for the gradient amplitude limited regime */
	/*gampstart = pow(sqrt(slewmax*gamma/(lambda*omega*omega)) * (alpha/2+1) * Ts2a, (alpha+1)/(alpha/2+1))/(gamma*gmax/(lambda*omega)*(alpha+1));*/ 


	if (Tes<Ts2a)
		*length = (int)(Tes/dt+.5);
	else
		*length = (int)(Ts2a/dt + (Tea-gampstart)/dt + .5);
	*length = (*length/4)*4;

  if (NULL == outarray) {
  	for (t = 0, i = 0; t <= stop1; t+=dt,i++)  /* slew-rate limited section */
  	{
  	}
  	if (Ts2a < Tes) {
  		for (t = gampstart+dt-(Ts2apreround-Ts2a); t < Tea; t+=dt, i++)
  		{
  		}
  	}
  	*length = (i/4)*4;
    return;
  }

  workarray = outarray;

	tauprev = 0;
	
	for (t = 0, i = 0; t <= stop1; t+=dt,i++)  /* slew-rate limited section */
	{
		tau = pow(sqrt(slewmax*gamma/(lambda*omega*omega))*(alpha/2+1)*t,1/(alpha/2+1));
		if (gradork)
		{
			workarray[2*i] = lambda*pow(tau,alpha)*cos(omega*tau-phi);
			workarray[2*i+1] = lambda*pow(tau,alpha)*sin(omega*tau-phi);
		} else {
			dtaudt = pow(slewmax*gamma/(lambda*omega*omega), 1.0/(alpha+2)) 
               * pow((alpha/2+1)*t, 1/(alpha/2+1)-1);
			workarray[2*i] = lambda * (alpha*pow(tau, alpha-1)*cos(omega*tau-phi) 
                                 - omega*pow(tau,alpha)*sin(omega*tau-phi) ) 
                              * dtaudt/gamma;
			workarray[2*i+1] = lambda * (alpha*pow(tau, alpha-1)*sin(omega*tau-phi) 
                                   + omega*pow(tau,alpha)*cos(omega*tau-phi) )
                                * dtaudt/gamma;
		}		
		tauprev = tau;
	}
	if (Ts2a < Tes) {
		for (t = gampstart+dt-(Ts2apreround-Ts2a); t < Tea; t+=dt, i++)
		{
			tau = pow(gamma*gmax/(lambda*omega)*(alpha+1)*t, 1.0/(alpha+1));
			if (gradork)
			{
				workarray[2*i] = lambda*pow(tau,alpha)*cos(omega*tau - phi);
				workarray[2*i+1] = lambda*pow(tau,alpha)*sin(omega*tau - phi);
			} else {
				dtaudt = pow(gmax*gamma/(lambda*omega), 1.0/(alpha+1)) 
                 * pow((alpha+1)*t, 1.0/(alpha+1)-1);
				workarray[2*i] = lambda * (alpha*pow(tau, alpha-1)*cos(omega*tau-phi) 
                                   - omega*pow(tau,alpha)*sin(omega*tau-phi) ) 
                                * dtaudt/gamma;
				workarray[2*i+1] = lambda * (alpha*pow(tau, alpha-1)*sin(omega*tau-phi)
                                     + omega*pow(tau,alpha)*cos(omega*tau-phi))
                                  * dtaudt/gamma;
			}		
			tauprev = tau;
		}
	}
	*length = (i/4)*4;
	workarray[0] = 0;
	workarray[1] = 0;
}

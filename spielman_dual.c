#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <spielman_dual.h>

void spielman_dual(float gmax, float slewmax, int xres, int xres2, float fov, float alpha, float alpha2, int nl, float dt, int gradork, float sampfact, float sampfact2, float *workarray, int *length)
{
/* Generate a variable dual-density spiral
 * Created by Kressler 03/02/2005
 * Based on Kim, MRM 50:214-219 (2003)
 *
 * gmax = maximum gradient amplitude
 * slewmax = maximum slew rate
 * xres = desired matrix size for inner k-space
 * xres2 = desired matrix size for outer k-space
 * fov = desired field of view
 * alpha = oversampling factor at center of inner k-space
 * alpha2 = oversampling factor at center of outer k-space
 * nl = number of leaves
 * gradork = generate gradient or k-space waveforms (0 = gradient, 1 = k-space)
 * sampfact = sampling factor at outer edge of inner k-space
 * sampfact2 = sampling factor at outer edge of outer k-space
 * outarray = output array for gradients or k-space data
 * length = length of generated waveform
*/


/* for now, we'll be lazy and assume that the inner trajectory always ends in slew regime, 
 * outer always begins in slew regime.  this should usually be the case.  should generalize
 * to the other three possibilities later
*/

	double gamma;
	double n;
	double lambda;
	double omega;
	double Ts2a;
	double Tea;
	double Tes;
	double stop1;

	double n2;
	double lambda2;
	double omega2;
	double Ts2a2;
	double Tea2;
	double Tes2;
	double stop2;
	double gampstart2;

	double spiral2start;
	double phi;
	double dtaudt;

	double t;
	double tau;
	int i;

	float temp1[2];
	float temp2[2];
	double gend1[2];
	double absgend1;
	double Tespreround;
	double Ts2a2preround;
	double tau2start;
	double taues;
	double tprev;
	


	gamma = 4.257e3;
	n = 1.0/(1.0-pow(1.0-2.0*nl/(sampfact*xres), 1.0/alpha));  /* number of turns of spiral to make */
	lambda = (double)xres/(2.0*fov);
	omega = 2.0*M_PI*n;

	n2 = 1.0/(1.0-pow(1.0-2.0*nl/(sampfact2*xres2), 1.0/alpha2));  /* number of turns of spiral to make */
	lambda2 = (double)xres2/(2.0*fov);
	omega2 = 2.0*M_PI*n2;


	Ts2a = pow(gmax*gamma / (lambda*omega / (alpha/2.0+1.0) * pow((alpha/2.0+1.0)*sqrt(slewmax*gamma/(lambda*omega*omega)), (alpha+1)/(alpha/2+1))), (alpha+2)/alpha);  /* time to switch from slew limited to amplitude limited */

	Ts2a2 = pow(gmax*gamma / (lambda2*omega2 / (alpha2/2.0+1.0) * pow((alpha2/2.0+1.0)*sqrt(slewmax*gamma/(lambda2*omega2*omega2)), (alpha2+1)/(alpha2/2+1))), (alpha2+2)/alpha2);  /* time to switch from slew limited to amplitude limited */


	Tea = 1.0/(gamma*gmax/(lambda*omega)*(alpha+1)); /* ending time of amplitude regime */
	Tea2 = 1.0/(gamma*gmax/(lambda2*omega2)*(alpha2+1)); /* ending time of amplitude regime */

	Tes = 1.0/((alpha/2.0+1.0)*sqrt(slewmax*gamma/(lambda*omega*omega))); /* ending time of slew regime */
	Tes2 = 1.0/((alpha2/2.0+1.0)*sqrt(slewmax*gamma/(lambda2*omega2*omega2))); /* ending time of slew regime */

	Tespreround = Tes;
	Ts2a2preround = Ts2a2;


	/* time for first point of amplitude limited regime 
	 * necessary to produce a continuously increasing tau
	 * and thus a smoothly varying gradient waveform 
	 * This is the part the Kim paper gets wrong, as it just starts
	 * at Ts2a for the gradient amplitude limited regime */
	gampstart2 = pow((gmax*gamma)/(lambda2*omega2), 1.0/alpha2) * pow(slewmax*gamma/(lambda2*omega2*omega2), -(alpha2+1.0)/(alpha2*(alpha2+2)))
				* pow((alpha2/2.0+1.0)*Ts2a2, (alpha2+1.0)/(alpha2+2.0)) / (alpha2+1.0);

	Ts2a = floor(Ts2a/dt)*dt;   /* round everything down to the nearest increment of dt */
	Tea = floor(Tea/dt)*dt;
	Tes = floor(Tes/dt)*dt;

	Ts2a2 = floor(Ts2a2/dt)*dt;   /* round everything down to the nearest increment of dt */
	Tea2 = floor(Tea2/dt)*dt;
	Tes2 = floor(Tes2/dt)*dt;

	taues = pow(sqrt(slewmax*gamma/(lambda*omega*omega))*(alpha/2.0+1.0)*(Tes),1.0/(alpha/2.0+1.0));
	dtaudt = pow(slewmax*gamma/(lambda*omega*omega), 1.0/(alpha+2.0)) * pow((alpha/2.0+1.0)*(Tes), 1.0/(alpha/2.0+1.0)-1.0);
	tau = taues;
	gend1[0] = lambda * (alpha*pow(tau, alpha-1.0)*cos(omega*tau) - omega*pow(tau,alpha)*sin(omega*tau)) * dtaudt/gamma;
	gend1[1] = lambda * (alpha*pow(tau, alpha-1.0)*sin(omega*tau) + omega*pow(tau,alpha)*cos(omega*tau)) * dtaudt/gamma;

	absgend1 = sqrt(gend1[0]*gend1[0] + gend1[1]*gend1[1]);
	
	/*spiral2start = pow(gamma/(lambda2*omega2)*absgend1, (alpha2+2.0)/alpha2) * pow(lambda2*omega2*omega2/(slewmax*gamma), (alpha2+1.0)/alpha2) / (alpha2/2.0+1.0);*/
	spiral2start = find2slewstart(absgend1, slewmax, gmax, gamma, lambda2, omega2, alpha2);


	/*printf("Tes = %f\n", Tes);
	printf("Tea = %f\n", Tea);
	printf("Ts2a = %f\n", Ts2a);
	printf("Tes2 = %f\n", Tes2);
	printf("Tea2 = %f\n", Tea2);
	printf("Ts2a2 = %f\n", Ts2a2);
	printf("gampstart2 = %f\n", gampstart2);

	printf("spiral2start = %f\n", spiral2start);*/

	spielman_dual_calcgrad(temp1, gamma, lambda, omega, alpha, tau, dtaudt, 0);

	tau2start = pow(sqrt(slewmax*gamma/(lambda2*omega2*omega2))*(alpha2/2.0+1.0)*(spiral2start),1.0/(alpha2/2.0+1.0));
	dtaudt = pow(slewmax*gamma/(lambda2*omega2*omega2), 1.0/(alpha2+2.0)) * pow((alpha2/2.0+1.0)*spiral2start, 1.0/(alpha2/2.0+1.0)-1.0);

	spielman_dual_calcgrad(temp2, gamma, lambda2, omega2, alpha2, tau2start, dtaudt, 0);


	/*printf("temp1[0] = %f, temp1[1] = %f, temp2[0] = %f, temp2[1] = %f\n", temp1[0], temp1[1], temp2[0], temp2[1]);*/
	phi = -atan2(temp1[1], temp1[0]) + atan2(temp2[1], temp2[0]);
	/*phi = -(omega*taues - omega2*tau2start)+0.0077799;*/
	/*printf("phi:  %f\n", phi);

	printf("omega: %f, omega2: %f\n", omega, omega2);*/




	if (Tes < Ts2a)
		stop1 = Tes+dt/2.0;
	else {
		printf("Error, can't do amp limited on inner spiral\n");
		exit(1);
	}

	if (Tes2 < Ts2a2)
		stop2 = Tes2;
	else
		stop2 = Ts2a2;

  if (NULL == workarray) {
  	for (t = dt, i = 1; t < stop1; t+=dt, i++) {}  /* slew-rate limited section */
  	for (t = spiral2start+dt; t <= stop2; t+=dt, i++) {}  /* slew-rate limited section,second spiral */
  	tprev = t-dt;
  	if (Ts2a2 < Tes2) {
  		for (t = gampstart2 + dt - (Ts2a2-tprev); t < Tea2; t+=dt, i++) {}
  	}
  	*length = (i/4)*4;
    return; 
  } 

	workarray[0] = 0;
	workarray[1] = 0;

	for (t = dt, i = 1; t < stop1; t+=dt, i++)  /* slew-rate limited section */
	{
		tau = pow(sqrt(slewmax*gamma/(lambda*omega*omega))*(alpha/2.0+1.0)*t,1.0/(alpha/2.0+1.0));
		dtaudt = pow(slewmax*gamma/(lambda*omega*omega), 1.0/(alpha+2.0)) * pow((alpha/2.0+1.0)*t, 1.0/(alpha/2.0+1.0)-1.0);
		if (gradork && (i != 0))
		{
			spielman_dual_calcgrad(temp1, gamma, lambda, omega, alpha, tau, dtaudt, 0);
			workarray[2*i] = workarray[2*(i-1)] + gamma*temp1[0]*dt;
			workarray[2*i+1] = workarray[2*(i-1)+1] + gamma*temp1[1]*dt;
		} else {
			spielman_dual_calcgrad(&(workarray[2*i]), gamma, lambda, omega, alpha, tau, dtaudt, 0);
		}		
	}
	/*printf("%d\n", i); */
	
	for (t = spiral2start+dt; t <= stop2; t+=dt, i++)  /* slew-rate limited section,second spiral */
	{
		tau = pow(sqrt(slewmax*gamma/(lambda2*omega2*omega2))*(alpha2/2.0+1.0)*t,1.0/(alpha2/2.0+1.0));
		dtaudt = pow(slewmax*gamma/(lambda2*omega2*omega2), 1.0/(alpha2+2.0)) * pow((alpha2/2.0+1.0)*t, 1.0/(alpha2/2.0+1.0)-1.0);
		if (gradork)
		{
			spielman_dual_calcgrad(temp1, gamma, lambda2, omega2, alpha2, tau, dtaudt, phi);
			workarray[2*i] = workarray[2*(i-1)] + gamma*temp1[0]*dt;
			workarray[2*i+1] = workarray[2*(i-1)+1] + gamma*temp1[1]*dt;
		} else {
			spielman_dual_calcgrad(&(workarray[2*i]), gamma, lambda2, omega2, alpha2, tau, dtaudt, phi);
		}		
	}
	/*printf("%d\n", i);*/
	tprev = t-dt;

	phi -= omega2 * (pow(sqrt(slewmax*gamma/(lambda2*omega2*omega2))*(alpha2/2.0+1.0)*tprev,1.0/(alpha2/2.0+1.0)) - pow(gamma*gmax/(lambda2*omega2)*(alpha2+1.0)*(gampstart2-(Ts2a2-tprev)), 1.0/(alpha2+1.0)));

	if (Ts2a2 < Tes2) {
		for (t = gampstart2 + dt - (Ts2a2-tprev); t < Tea2; t+=dt, i++)
		{
			tau = pow(gamma*gmax/(lambda2*omega2)*(alpha2+1.0)*t, 1.0/(alpha2+1.0));
			dtaudt = pow(gmax*gamma/(lambda2*omega2), 1.0/(alpha2+1.0)) * pow((alpha2+1.0)*t, 1.0/(alpha2+1.0)-1.0);
			if (gradork)
			{
				spielman_dual_calcgrad(temp1, gamma, lambda2, omega2, alpha2, tau, dtaudt, phi);
				workarray[2*i] = workarray[2*(i-1)] + gamma*temp1[0]*dt;
				workarray[2*i+1] = workarray[2*(i-1)+1] + gamma*temp1[1]*dt;
			} else {
				spielman_dual_calcgrad(&(workarray[2*i]), gamma, lambda2, omega2, alpha2, tau, dtaudt, phi);
			}		
		}
	}

	*length = (i/4)*4;

	workarray[0] = 0;
	workarray[1] = 0;
}

void spielman_dual_calcgrad(float *workarray, double gamma, double lambda, double omega, double alpha, double tau, double dtaudt, double dphi)
{

	workarray[0] = lambda * (alpha*pow(tau, alpha-1.0)*cos(omega*tau-dphi) - omega*pow(tau,alpha)*sin(omega*tau-dphi)) * dtaudt/gamma;
	workarray[1] = lambda * (alpha*pow(tau, alpha-1.0)*sin(omega*tau-dphi) + omega*pow(tau,alpha)*cos(omega*tau-dphi)) * dtaudt/gamma;
}

double find2slewstart(double desired, double slewmax, double gmax, double gamma, double lambda, double omega, double alpha)
{
	double error;
	double time;
	double amp;
	double prevtime;
	double prevamp;
	double preverr;
	double step;
	double tau; 
	double dtaudt;

	/* initial guess, from approximate solution */
	time = pow(gamma/(lambda*omega)*desired, (alpha+2.0)/alpha) * pow(lambda*omega*omega/(slewmax*gamma), (alpha+1.0)/alpha) / (alpha/2.0+1.0);

	/*printf("initial guess for spiral2start %f\n", time);*/

	tau = pow(sqrt(slewmax*gamma/(lambda*omega*omega))*(alpha/2.0+1.0)*time,1.0/(alpha/2.0+1.0));
	dtaudt = pow(slewmax*gamma/(lambda*omega*omega), 1.0/(alpha+2.0)) * pow((alpha/2.0+1.0)*time, 1.0/(alpha/2.0+1.0)-1.0);
	amp = lambda/gamma * pow(tau, alpha-1) * sqrt(alpha*alpha + omega*omega*tau*tau) * dtaudt;
	prevtime = time;
	prevamp = amp;
	
	error = amp - desired;
	preverr = error;
	if (error > 0)
		step = -1e-6;
	else
		step = 1e-6;

	while (fabs(error) > 1e-10)
	{
		while (((preverr > 0.0) && (error > 0.0)) || ((preverr < 0.0) && (error < 0.0)))
		{
			prevtime = time;
			preverr = error;
			prevamp = amp;
			time += step;
			tau = pow(sqrt(slewmax*gamma/(lambda*omega*omega))*(alpha/2.0+1.0)*time,1.0/(alpha/2.0+1.0));
			dtaudt = pow(slewmax*gamma/(lambda*omega*omega), 1.0/(alpha+2.0)) * pow((alpha/2.0+1.0)*time, 1.0/(alpha/2.0+1.0)-1.0);
			amp = lambda/gamma * pow(tau, alpha-1) * sqrt(alpha*alpha + omega*omega*tau*tau) * dtaudt;
			error = amp - desired;
			//printf("error %f, desired %f, magnitude %f, time %f\n", error, desired, amp, time);
		}
		step = step*(-0.1);
		preverr = -preverr; /* kludge so we'll go back into the loop */
	}
	return time;
}

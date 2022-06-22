/*@Start***********************************************************/
/* GEMSBG C source File
 * Copyright (C) 1990 The General Electric Company
 *
 *	File Name:  amppwgmn.c
 *	Developer:  Jim Mitchell
 *
 * $Source: amppwgmn.c $
 * $Revision: 1.7 $  $Date: 8/25/98 08:01:28 $
 */

/*@Synopsis 
  Optimizes the amplitudes and pulse widths of 2 gradient
  moment nulling pulses for minimum total pulse width
  given net area and first moment inputs.
*/     

/*@Description

This routine calculates the pulse attack, decay, pulse width and
amplitude of a bipolar flow comp pulse pair gradient.  This routine
will set the amplitude of the flow comp pulses to the maximum for the
x gradient and minimize the pulse widths.  If the time of the pulse
is longer than than avail_time the routine returns failure.

Type and Call:
_____________

STATUS
amppwgmnbrs(ref_area, ref_moment, encode_area, moment_area,
         max_allowable_time, beta, targetamp, ramp2target,
		 minconstpw, &a_gmn1,&pw_gmn1a,&pw_gmn1,&pw_gmn1d,
         &a_gmn2,&pw_gmn2a,&pw_gmn2,&pw_gmn2d)

Passed Parameters:
__________________
(I: for input parameter, O: for output parameter)

(I)	DOUBLE ref_area: net area of other pulses to consider (gauss*us/cm)

(I)	DOUBLE ref_moment: net 1st moment of other pulses to
        consider (gauss*us^2/cm)

(I)	DOUBLE encode_area: Area of the maximum phase encoding pulse to be added
        to the second gradient moment nulling/encoding pulse (gauss*us/cm)

(I)	DOUBLE moment_area: Net desired first moment of the composite pulses
        (gauss*us^2/cm)

(I)	INT avail_time: The maximum time in microseconds availible for
	the two gradient moment nulling/encoding pulses, gmn1 an gmn2.
        If no time constraint is needed, pass in a very large number,
        like 1 sec.  If the sum of the pulse widths exceeds this
        value FAILURE is returned.

(I)	DOUBLE beta:  The beta factor for the gradient that specifies
        the linear portion of ramps (may not be = to 1.0 if shaped
        gradient ramps are being used)

(I)	DOUBLE targetamp: The maximum allowable gradient amplitude for
        the first and second gradient moment nulling/encoding pulses

(I)	DOUBLE ramp2target: The time in microseconds to slew to targetamp

(I)	INT minconstpw: The minimum allowable time for the constant part
        of a trapezoid pulse

(O)	FLOAT *a_gmn1: The address of the amplitude of the first
  	pulse played adjacent to the reference pulse.

(O)	INT  *pw_gmn1a: The address of the pulse width of the first
  	pulse attack ramp played adjacent to the reference pulse.

(O)	INT  *pw_gmn1: The address of the pulse width of the first
  	pulse constant section played adjacent to the reference pulse.

(O)	INT  *pw_gmn1d: The address of the pulse width of the first
  	pulse decay ramp played adjacent to the reference pulse.

(O)	FLOAT *a_gmn2: The address of the amplitude of the second
  	pulse played adjacent to the first pulse.

(O)	INT  *pw_gmn2a: The address of the pulse width of the second
  	pulse attack ramp played adjacent to the first pulse.

(O)	INT  *pw_gmn2: The address of the pulse width of the second
  	pulse constant section played adjacent to the first pulse. 

(O)	INT  *pw_gmn2d: The address of the pulse width of the second
  	pulse decay ramp played adjacent to the first pulse.
*/

/*@End*********************************************************/

/* Revision History

   Author	Date		Change
   JDM          1/26/94         Generalized amppwgxfcmin 
   PL          04/19/94         Generalized further
   PL          09/14/94         Fix expression for triangular A2 case
   RJL         07/05/95         Added printARGS capability
   RJL         07/10/95         Removed printARGS capability
   GFN         09/25/1997       Removed unsafe datatypes from the interface.
                                Made code ANSI compatible.
   GFN         12/17/1997       Removed extern declaration for printf and
                                included stdio.h/stdioLib.h.
   Thayer      07-Jun-2000      Conditionally compiled conditionally used vars:
                                net_moment, M1, M2.
*******************************/

/*
#include <math.h>
#ifndef HW_IO
#include <stdio.h>
#else
#include <stdioLib.h>
#endif

#include "support_decl.h"
*/
@host fcbrs

STATUS 
#ifdef __STDC__
amppwgmnbrs( DOUBLE ref_area,
          DOUBLE ref_moment,
          DOUBLE encode_area,
          DOUBLE moment_area,
          INT max_allowable_time,
          DOUBLE beta,
          DOUBLE targetamp,
          INT ramp2target,
          INT minconstpw,
          FLOAT *a_gmn1,
          INT *pw_gmn1a,
          INT *pw_gmn1,
          INT *pw_gmn1d,
          FLOAT *a_gmn2,
          INT *pw_gmn2a,
          INT *pw_gmn2,
          INT *pw_gmn2d )
#else /* !__STDC__ */
amppwgmnbrs( ref_area, ref_moment, encode_area, moment_area, max_allowable_time, beta, targetamp, ramp2target, minconstpw, a_gmn1, pw_gmn1a, pw_gmn1, pw_gmn1d, a_gmn2, pw_gmn2a, pw_gmn2, pw_gmn2d )
    DOUBLE ref_area;
    DOUBLE ref_moment;
    DOUBLE encode_area;
    DOUBLE moment_area;
    INT max_allowable_time;
    DOUBLE beta;
    DOUBLE targetamp;
    INT ramp2target;
    INT minconstpw;
    FLOAT *a_gmn1;
    INT *pw_gmn1a;
    INT *pw_gmn1;
    INT *pw_gmn1d;
    FLOAT *a_gmn2;
    INT *pw_gmn2a;
    INT *pw_gmn2;
    INT *pw_gmn2d;
#endif /* __STDC__ */
{
  FLOAT AR, A1, A2;  /* Zeroth moments for pulses (areas) */
  FLOAT MR;          /* First moments for pulses */
  /*FLOAT M1, M2;*/      /* First moments for pulses */
  FLOAT AT;          /* Maximum area of a triangle pulse */
  FLOAT AE, ME;      /* Temporary variables for encode_area and moment_area */
  /*FLOAT net_moment;*/  /* net first moment computed after algorithm runs through */
  INT total_time;
  FLOAT tmp_A2;
  FLOAT reverseflag;
  FLOAT tp;
  FLOAT tr;
  
  reverseflag = 1.0;
  AR = ref_area;
  MR = ref_moment;
  AE = 0.0;
  ME = 0.0;
  tr = (FLOAT)ramp2target;

  if (fabs(AR)> 1.e-6)
  {
    if (AR > 0)
    {
      AR = -AR;
      MR = -MR;
      reverseflag = -1.0;
    }

    tp = floorf((MR/AR - tr)*2.0);
    if ( (tp >= 8.0) && ((tp+tr)*targetamp > (-AR)) )
    {
      /*targetamp = -AR/(tp+tr);*/
      A2 = -AR;
      A1 = 0.0;

      amppwgrad(A2,targetamp,0.0,0.0,ramp2target,
          minconstpw,a_gmn2,pw_gmn2a,pw_gmn2,pw_gmn2d);

      *a_gmn1 = 0.0;
      *pw_gmn1a = 0;
      *pw_gmn1 =  RUP_GRD(MR/AR - (float)*pw_gmn2a*0.5 - ramp2target);
      *pw_gmn1d = 0;

    }
    else
    {
      AT = targetamp * (FLOAT)ramp2target;

      tmp_A2 = AT*AT + 2.0*(-AT*AR + AR*AR + 2.0*targetamp*MR);

      if( tmp_A2 < (AT*AT*8.0 + 2.0*(FLOAT)minconstpw*targetamp)  ) 
      {
        FLOAT a;
        FLOAT b;
        FLOAT c;
        FLOAT targetamp1;
        FLOAT targetamp2;

        a = 2.0 * (tr+(FLOAT)minconstpw) * (2.0*tr+(FLOAT)minconstpw);
        b = AR*tr - 2.0*MR;
        c = -AR*AR;
        targetamp1 = 0.5*(-b - sqrt(b*b-4.0*a*c))/a;
        targetamp2 = 0.5*(-b + sqrt(b*b-4.0*a*c))/a;

        if(targetamp1>0)
        {
          if(targetamp2>targetamp1)
            targetamp = targetamp1;
        }
        else
          targetamp = targetamp2;

        AT = targetamp * tr;
        A2 = -AT - (FLOAT)minconstpw*targetamp;

      }
      else
      {
        A2 = 0.5*(AT-sqrt(tmp_A2));
      }

      A1 = -(AR + A2); /* balance zeroth moment */

      amppwgrad(A1,targetamp,0.0,0.0,ramp2target,
          minconstpw,a_gmn1,pw_gmn1a,pw_gmn1,pw_gmn1d);

      amppwgrad((A2+AE),targetamp,0.0,0.0,ramp2target,
          minconstpw,a_gmn2,pw_gmn2a,pw_gmn2,pw_gmn2d);
    }
  }
  else
  {
    if (MR < 0)
    {
      MR = -MR;
      reverseflag = -1.0;
    }
    AT = targetamp * (FLOAT)ramp2target;
    if ( MR < AT * (FLOAT)ramp2target*2.0)   
    {
      targetamp = targetamp * (MR / (AT * (FLOAT)ramp2target*2.0 ));
      A1 = targetamp * (FLOAT)ramp2target;
      A2 = -A1;
    }
    else
    {
      tp  = 0.5 * (-3.0*tr + sqrt(tr*tr + 4.0*MR/targetamp));
      A1 = targetamp * (tr+tp);
      A2 = -A1;
    }
    amppwgrad(A1,targetamp,0.0,0.0,ramp2target,
        minconstpw,a_gmn1,pw_gmn1a,pw_gmn1,pw_gmn1d);

    amppwgrad(A2,targetamp,0.0,0.0,ramp2target,
        minconstpw,a_gmn2,pw_gmn2a,pw_gmn2,pw_gmn2d);
  }
  
    /* Compute the moments of the resulting pulses here */
    /* 
       calctrap1stmom(&M1,*a_gmn1,*pw_gmn1d,*pw_gmn1,*pw_gmn1a,0.0);
       calctrap1stmom(&M2,*a_gmn2,*pw_gmn2d,*pw_gmn2,*pw_gmn2a,
       (FLOAT)((*pw_gmn1a)+(*pw_gmn1)+(*pw_gmn1d)));

       net_moment = MR + M1 + ME + M2;*/

    *a_gmn1 = *a_gmn1*reverseflag;
    *a_gmn2 = *a_gmn2*reverseflag;

  /*
     printf("a_gmn1 = %f \n", *a_gmn1);
     printf("pw_gmn1a = %d \n", *pw_gmn1a);
     printf("pw_gmn1 = %d \n", *pw_gmn1);
     printf("pw_gmn1d = %d \n", *pw_gmn1d);

     printf("a_gmn2 = %f \n", *a_gmn2);
     printf("pw_gmn2a = %d \n", *pw_gmn2a);
     printf("pw_gmn2 = %d \n", *pw_gmn2);
     printf("pw_gmn2d = %d \n", *pw_gmn2d);


     printf("M1 = %f \n", M1);
     printf("M2 = %f \n", M2);
     printf("A1= %f \n", A1);
     printf("A2= %f \n", A2);
     printf("\n\n");

     printf("Net zero moment is %g \n",A1+A2+AR+AE);
     printf("Net first moment is %g \n",net_moment);
     fflush(stdout);*/

  total_time = (*pw_gmn2a) + (*pw_gmn2) + (*pw_gmn2d) +
               (*pw_gmn1a) + (*pw_gmn1) + (*pw_gmn1d);

 if (total_time > max_allowable_time){
   epic_error(0,"total time (%d) > avail_time (%d)",0,
              EE_ARGS(2),INT_ARG,total_time,INT_ARG,max_allowable_time);
   return FAILURE;
 }
 else
   return SUCCESS;  
  
}

STATUS 
#ifdef __STDC__
calctrap1stmom( FLOAT *moment,
                DOUBLE ampl,
                INT attack,
                INT plateau,
                INT decay,
                DOUBLE timeref )
#else /* !__STDC__ */
calctrap1stmom( moment, ampl, attack, plateau, decay, timeref )
    FLOAT *moment;
    DOUBLE ampl;
    INT attack;
    INT plateau;
    INT decay;
    DOUBLE timeref;
#endif /* __STDC__ */
{
  FLOAT fattack = (FLOAT)attack;
  FLOAT fplateau = (FLOAT)plateau;
  FLOAT fdecay = (FLOAT)decay;
  FLOAT area;

  /* The first moment of a trapezoid with attack, ta, decay,
     td, plateau pulse width, tp, and amplitude A about the
     time point corresponding to the start of the attack is 

     A * (ta/2*(2*ta/3) + tb*(ta+tb/2) + td/2*(ta+tb+td/3))

     The preceeding equation is found by multiplying the area
     of each piece of the trapezoid by its moment arm.  The
     moment arm of a ramp is 2/3 of the way up the ramp (or
     1/3 of the way down a ramp).  The moment arm of a constant
     is the middle of the constant.
  */
  
  *moment = ampl*(fattack*fattack/3.0 +
	      fplateau*(fattack+0.5*fplateau) +
	      0.5*fdecay*(fattack+fplateau+fdecay/3.0));

  if (timeref != 0.0) {
    area = ampl*(fplateau+0.5*(fattack+fdecay));
    *moment += area*timeref;
  }
return SUCCESS;
}


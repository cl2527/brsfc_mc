#define GXFCMON_SLOT 0
#define GX1MON_SLOT 1
#define GXWMON_SLOT 2
#define GXMON_FREE 3

#define GYRF2LMON_SLOT 0
#define GYRF2RMON_SLOT 1
#define GYRF2MON_SLOT 2
#define GYCYLRA_SLOT 3
#define GYCYLR_SLOT 4
#define GYRF1MON_SLOT 5
#define GY1MON_SLOT 6
#define GYMON_FREE 7

#define GZRF1MON_SLOT 0
#define GZ1MON_SLOT 1
#define GZKMON_SLOT 2
#define GZCYLRA_SLOT 3
#define GZCYLR_SLOT 4
#define GZMON_FREE 5

GRAD_PULSE gradxmon[GXMON_FREE] = { 
  /* GRADX 0 - GXFCMON */
  {
    G_TRAP, 
    (int *)&pw_gxfcmona, 
    (int *)&pw_gxfcmond, 
    (int *)&pw_gxfcmon, 
    (FLOAT *)NULL,
    (FLOAT *)&a_gxfcmon, 
    (FLOAT *)NULL,
    (FLOAT *)NULL,
    (char *)NULL,
    0,
    1.0,
    (int *)NULL,
    0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0,
    0,
    0.0 /* intabspwmcurr */
  },
  /* GRADX 1 - GX1MON */
  {
    G_TRAP, 
    (int *)&pw_gx1mona, 
    (int *)&pw_gx1mond, 
    (int *)&pw_gx1mon,
    (FLOAT *)NULL, 
    (FLOAT *)&a_gx1mon,
    (FLOAT *)NULL,
    (FLOAT *)NULL, 
    (char *)NULL,
    0,
    1.0,
    (int *)NULL,
    0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0,
    0,
    0.0 /* intabspwmcurr */
  },
  /* GRADX 2 - GXWMON */
  {
    G_TRAP,
    (int*)&pw_gxwmona,
    (int*)&pw_gxwmond,
    (int*)&pw_gxwmon,
    (FLOAT *)NULL,
    (FLOAT *)&a_gxwmon,
    (FLOAT *)NULL,
    (FLOAT *)NULL,
    (char *)NULL,
    0,
    1.0,
    (int *)NULL ,
    0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0,
    0,
    0.0 /* intabspwmcurr */
  }
};

 
GRAD_PULSE gradymon[GYMON_FREE] = { 
  /* GRADY 0 - GYRF2LMON */
  {
    G_TRAP,
    (int *)&pw_gyrf2lmona, 
    (int *)&pw_gyrf2lmond, 
    (int *)&pw_gyrf2lmon,
    (FLOAT *)&psd_zero, 
    (FLOAT *)&a_gyrf2lmon,
    (FLOAT *)&a_gyrf2lmon,
    (FLOAT *)&a_gyrf2mon,
    (char *)NULL, 
    0,
    1.0,
    (int *)NULL,
    0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0,
    1,
    0.0 /* intabspwmcurr */
  },
  /* GRADY 1 - GYRF2RMON*/
  {
    G_TRAP,
    (int *)&pw_gyrf2rmona, 
    (int *)&pw_gyrf2rmond, 
    (int *)&pw_gyrf2rmon,
    (FLOAT *)&a_gyrf2mon, 
    (FLOAT *)&a_gyrf2rmon,
    (FLOAT *)&a_gyrf2rmon,
    (FLOAT *)&psd_zero,
    (char *)NULL, 
    0,
    1.0,
    (int *)NULL,
    0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0,
    1,
    0.0 /* intabspwmcurr */
  },
  /* GRADY 2 - GYRF2MON */
  {
    G_TRAP,
    (int *)&pw_gyrf2mona,
    (int *)&pw_gyrf2mond,
    (int *)&pw_gyrf2mon,
    (FLOAT *)NULL, 
    (FLOAT *)&a_gyrf2mon,
    (FLOAT *)NULL,
    (FLOAT *)NULL, 
    (char *)NULL, 
    0,
    1.0,
    (int *)NULL,
    0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0,
    2,
    0.0 /* intabspwmcurr */
  },
  /* GRADY 3 - GYCYLRA */
  { 
    G_RAMP,
    (int *)NULL,
    (int *)NULL,
    (int *)&pw_gycylra,
    (float *)NULL,
    (float *)&end_gycylra,
    (float *)NULL,
    (float *)NULL,
    (char *)NULL,
    0,
    1.0,
    (int *)NULL,
    0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0,
    0,
    0.0 /* intabspwmcurr */
  },
  /* GRADY 4 - GYCYLR */
  { 
    G_SIN,
    (int *)NULL,
    (int *)NULL,
    (int *)&pw_gycylr,
    (float *)NULL,
    (float *)&a_gycylr,
    (float *)NULL,
    (float *)NULL,
    (char *)NULL,
    0,
    1.0,
    (int *)NULL,
    0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0,
    0,
    0.0 /* intabspwmcurr */
  },
  /* GRADY 5 - GYRF1MON */
  {
    G_TRAP, (int *)&pw_gyrf1mona, 
    (int *)&pw_gyrf1mond,
    (int *)&pw_gyrf1mon, 
    (FLOAT *)NULL,
    (FLOAT *)&a_gyrf1mon,
    (FLOAT *)NULL,
    (FLOAT *)NULL, 
    (char *)NULL, 
    0,
    1.0,
    (int *)NULL,
    0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0,
    0,
    0.0 /* intabspwmcurr */
  },
  /* GRADY 6 - GY1MON */
  {
    G_TRAP, 
    (int *)&pw_gy1mona, 
    (int *)&pw_gy1mond,
    (int *)&pw_gy1mon,
    (FLOAT *)NULL, 
    (FLOAT *)&a_gy1mon,
    (FLOAT *)NULL,
    (FLOAT *)NULL, 
    (char *)NULL, 
    0,
    1.0,
    (int *)NULL,
    0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0,
    0,
    0.0 /* intabspwmcurr */
  }
};


GRAD_PULSE gradzmon[GZMON_FREE] = { 
  /* GRADZ 0 - GZRF1MON */
  {
    G_TRAP, 
    (int *)&pw_gzrf1mona, 
    (int *)&pw_gzrf1mond,
    (int *)&pw_gzrf1mon, 
    (FLOAT *)NULL,
    (FLOAT *)&a_gzrf1mon,
    (FLOAT *)NULL,
    (FLOAT *)NULL, 
    (char *)NULL, 
    0,
    1.0,
    (int *)NULL,
    0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0,
    0,
    0.0 /* intabspwmcurr */
  },
  /* GRADZ 1 - GZ1MON */
  {
    G_TRAP, 
    (int *)&pw_gz1mona, 
    (int *)&pw_gz1mond,
    (int *)&pw_gz1mon,
    (FLOAT *)NULL, 
    (FLOAT *)&a_gz1mon,
    (FLOAT *)NULL,
    (FLOAT *)NULL, 
    (char *)NULL, 
    0,
    1.0,
    (int *)NULL,
    0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0,
    0,
    0.0 /* intabspwmcurr */
  },
  /* GRADZ 2 - GZKMON */
  { G_TRAP,
    (int *)&pw_gzkmona, 
    (int *)&pw_gzkmond,
    (int *)&pw_gzkmon,
    (FLOAT *)NULL, 
    (FLOAT *)&a_gzkmon,
    (FLOAT *)NULL,
    (FLOAT *)NULL, 
    (char *)NULL, 
    0,
    1.0,
    (int *)NULL,
    0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0,
    0,
    0.0 /* intabspwmcurr */
  },
  /* GRADZ 3 - GZCYLRA */
  { 
    G_RAMP,
    (int *)NULL,
    (int *)NULL,
    (int *)&pw_gzcylra,
    (float *)NULL,
    (float *)&end_gzcylra,
    (float *)NULL,
    (float *)NULL,
    (char *)NULL,
    0,
    1.0,
    (int *)NULL,
    0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0,
    0,
    0.0 /* intabspwmcurr */
  },
  /* GRADZ 4 - GZCYLR */
  { 
    G_SIN,
    (int *)NULL,
    (int *)NULL,
    (int *)&pw_gzcylr,
    (float *)NULL,
    (float *)&a_gzcylr,
    (float *)NULL,
    (float *)NULL,
    (char *)NULL,
    0,
    1.0,
    (int *)NULL,
    0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0,
    0,
    0.0 /* intabspwmcurr */
  }
};
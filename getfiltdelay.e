
/*
     float      *delay_val;  / * output delay values (usec) * /
     int       fastrec;      / * If 1, then read fast recvr low pass filter vals * /
     int       lpf;          / * Fast rec low pass freq:
                               1=100kHz,2=200kHz,3=300kHz,4=400kHz,5=500kHz * /
*/
STATUS getfiltdelay(FLOAT      *delay_val,
		    INT         fastrec,
		    INT         lpf)
{
 
  STATUS status;     /* flag to return or exit */
 
  char infilename[80]="delay.dat";
  char basefilename[80];
  char inputstring[80];
  FILE *fp; /* , *fopen(), *fclose(); */


  float f1delay=0.0;
  float f2delay=0.0;
  float f3delay=0.0;
  float f4delay=0.0;
  float f5delay=0.0;
  float fstdelay=0.0;
  float stddelay=0.0;
  float filter_delay=0.0;
 
  int i;
 
  float temp[15];
  int notdone, numlines;
 
  status = SUCCESS;
 
#ifdef ERMES_DEBUG
  strcpy(basefilename, infilename);
#else
  {
    char pathname[80]="/usr/g/bin/";
    strcpy(basefilename, pathname);
    strcat(basefilename, infilename);
  }
#endif

    /* MRIge69516 SXZ*/
	switch(opgradmode){
		case TRM_BODY_COIL:
			strcat(basefilename,WHOLE_SUFFIX);
			break;
		case TRM_ZOOM_COIL:
			strcat(basefilename,ZOOM_SUFFIX);
			break;
		default:
			break;
	}


  if ((fp = fopen(basefilename, "r")) == NULL)
    {
      for (i=0;i<15;i++)
        temp[i]=0.0;
    }
  else
    {
      notdone = 1;
      numlines = 0;
      i = 0;
      while (notdone)
        {
          fgets(inputstring, 80, fp);
          numlines++;
          if (inputstring[0] != '#')
            sscanf(inputstring, "%f", &(temp[i++]));
          if (i > 14 || numlines > 39 || inputstring[0] == '\0')
            notdone = 0;
        }
 
      f1delay = temp[8];
      f2delay = temp[9];
      f3delay = temp[10];
      f4delay = temp[11];
      f5delay = temp[12];
      fstdelay = temp[13];
      stddelay = temp[14];
 
      fclose(fp);
    }
 
  if (fastrec == 1)
    {
      switch (lpf)
        {
        case 1:
          filter_delay = f1delay;
          break;
        case 2:
          filter_delay = f2delay;
          break;
        case 3:
          filter_delay = f3delay;
          break;
        case 4:
          filter_delay = f4delay;
           break;
        case 5:
          filter_delay = f5delay;
          break;
        }
      *delay_val = filter_delay + fstdelay;
    } else {
      *delay_val = stddelay;
    }
 
  return status;
}
 

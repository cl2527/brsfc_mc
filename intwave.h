/* Macro to make a nice gradient pulse 
 *	waveform is passed to macro 
 * 
 * rev 0	1/23/99	 
 */ 
 
@pulsedef 
 
INTWAVE(int_wgname, int_name, int_pos, int_amp, int_res, int_wave, int_loggrd){ 
  
cv:{ 
  float   a_$[int_name]; 
  int    ia_$[int_name]; 
  int    pw_$[int_name]; 
  int   res_$[int_name]; 
} 
  
insert: cvinit =>{ 
} 
  
insert: predownload =>{ 
{ 
  float target; 
  
  a_$[int_name] = $[int_amp]; 
  res_$[int_name] = $[int_res]; 
  gettarget(&target, $[int_wgname], &$[int_loggrd]); 
  ia_$[int_name] = (a_$[int_name] / target) * MAX_PG_IAMP; 
  pw_$[int_name] = (int) res_$[int_name] * GRAD_UPDATE_TIME; 
} 
} 
  
var:{ 
  
  WF_PULSE $[int_name] = INITPULSE; 
} 
  
subst:{ 
  { 
    pulsename(&$[int_name],"$[int_name]"); 				/* assigns a name and storage for a pulse structure */
    createreserve(&$[int_name], $[int_wgname], res_$[int_name]); 	/* makes additional memory buffer to change waveform */
    for (i=0; i<res_$[int_name]; i++) 
      ibuf[i] = $[int_wave][i]; 
    movewaveimm(ibuf,&$[int_name],(int)0,res_$[int_name],TOHARDWARE); 	/* moves user memory to waveform generator */
    setweos(EOS_DEAD,&$[int_name],res_$[int_name]-1); 			/* set the end of sequence of a waveform */
    createinstr(&$[int_name],(LONG)($[int_pos]), pw_$[int_name],ia_$[int_name]); /* places instruction on waveform seq queue*/
  } 
} 
} 

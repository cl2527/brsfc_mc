#include <stdio.h>
#include <brsfc_cv.h>
#include <brsfc_cv_printer.h>
#include "fprint_psc_protocol.h"
extern int opentry;
extern int oppos;
extern int opplane;
extern int opimode;
extern int oppseq;
extern char psd_name[];
extern int oppure;
extern int opscic;
extern float opuser0;
extern float opuser1;
extern float opuser5;
extern float opuser7;
extern float opuser8;
extern float opuser9;
extern float opuser10;
extern float opuser19;
extern float opflip;
extern int opnecho;
extern float opfov;
extern int opslquant;
extern float opslthick;
extern SCAN_INFO scan_info[];
extern float piscancenter;
extern int opxres;
extern int opyres;
extern int opspf;
extern float oprbw;
extern int opspecir;
extern int oplava;
extern int lava_flag;
extern int optr;
int fprint_psc_protocol(char *file)
{
  FILE *fp = NULL;
  extern int print_brsfc_num_significant_digits;
  
  print_brsfc_num_significant_digits = 6;

  if (NULL == (fp = fopen(file, "w"))) return -1; 
  print_brsfc_int(fp, "opentry", 0, &(opentry),1);
  print_brsfc_int(fp, "oppos", 0, &(oppos),1);
  print_brsfc_int(fp, "opplane", 0, &(opplane),1);
  print_brsfc_int(fp, "opimode", 0, &(opimode),1);
  print_brsfc_int(fp, "oppseq", 0, &(oppseq),1);
  print_brsfc_char(fp, "psd_name", 0, (psd_name),255);
  print_brsfc_int(fp, "oppure", 0, &(oppure),1);
  print_brsfc_int(fp, "opscic", 0, &(opscic),1);
  print_brsfc_float(fp, "opuser0", 0, &(opuser0),1);
  print_brsfc_float(fp, "opuser1", 0, &(opuser1),1);
  print_brsfc_float(fp, "opuser5", 0, &(opuser5),1);
  print_brsfc_float(fp, "opuser7", 0, &(opuser7),1);
  print_brsfc_float(fp, "opuser8", 0, &(opuser8),1);
  print_brsfc_float(fp, "opuser9", 0, &(opuser9),1);
  print_brsfc_float(fp, "opuser10", 0, &(opuser10),1);
  print_brsfc_float(fp, "opuser19", 0, &(opuser19),1);
  print_brsfc_float(fp, "opflip", 0, &(opflip),1);
  print_brsfc_int(fp, "opnecho", 0, &(opnecho),1);
  print_brsfc_float(fp, "opfov", 0, &(opfov),1);
  print_brsfc_int(fp, "opslquant", 0, &(opslquant),1);
  print_brsfc_float(fp, "opslthick", 0, &(opslthick),1);
  print_brsfc_SCAN_INFO(fp, "scan_info", 0, (scan_info),1);
  print_brsfc_float(fp, "piscancenter", 0, &(piscancenter),1);
  print_brsfc_int(fp, "opxres", 0, &(opxres),1);
  print_brsfc_int(fp, "opyres", 0, &(opyres),1);
  print_brsfc_int(fp, "opspf", 0, &(opspf),1);
  print_brsfc_float(fp, "oprbw", 0, &(oprbw),1);
  print_brsfc_int(fp, "opspecir", 0, &(opspecir),1);
  print_brsfc_int(fp, "oplava", 0, &(oplava),1);
  print_brsfc_int(fp, "lava_flag", 0, &(lava_flag),1);
  print_brsfc_int(fp, "optr", 0, &(optr),1);
  fclose(fp);
  print_brsfc_num_significant_digits = 0;
  return 0;
}

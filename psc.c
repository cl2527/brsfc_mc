#define _GNU_SOURCE
#ifdef BLABLA
#include <cstdio>
#include <cstdlib>
#else
#include <stdio.h>
#include <stdlib.h>
#endif
#include <vx_rcmd.h>
#include <string.h>
#include "psc.h"
#include "debug.h"

#ifndef WEXITSTATUS
#define WEXITSTATUS(status)   (((status) & 0xff00) >> 8)
#endif

#ifdef HOST_TGT
#include <sys/types.h>
#include <sys/stat.h>
#endif

  
#ifdef HOST_TGT
FILE *popen(const char *command, const char *type);

int ppclose(FILE **fp)
{
  int status = pclose(*fp);
  *fp=NULL;
  return status;
}
#endif

int cmp(char *file1, char *file2)
{
  FILE *fp1=NULL, *fp2=NULL;
  int c1, c2;

  int cleanup(int status) {
    if (NULL != fp1) fclose(fp1);
    if (NULL != fp2) fclose(fp2);
    return status;
  }

  if (NULL == (fp1 = fopen(file1, "r"))) return cleanup(-1);
  if (NULL == (fp2 = fopen(file2, "r"))) return cleanup(-1);

  do {
      c1 = fgetc(fp1); c2 = fgetc(fp2);
      if (c1 != c2) return cleanup(-1);
  } while (c1 != EOF);

  return cleanup(0); 

}

int cp(char *src, char *dest)
{
  FILE *fp1=NULL, *fp2=NULL;
  int c;

  int cleanup(int status) {
    if (NULL != fp1) fclose(fp1);
    if (NULL != fp2) fclose(fp2);
    return status;
  }

  if (NULL == (fp1 = fopen(src, "r"))) return cleanup(-1);
  if (NULL == (fp2 = fopen(dest, "w"))) return cleanup(-1);

  while (EOF != ( c = fgetc(fp1) ) ){
      if (EOF == fputc(c, fp2)) return cleanup(-1);
  }

  return cleanup(0); 

}

int file_exist(char *file)
{
#ifdef HOST_TGT
  struct stat st;
  return (0 == stat(file, &st));
#else
  file = file;
  return 1;
#endif
}

#if ESEMAJOR >= 16
# define  IFCC_EXNO_LOC 4
#else
# define  IFCC_EXNO_LOC 8
#endif

#ifdef OLD
int get_exam_number(void)
{
#if defined(HOST_TGT) && !defined(SIM)
  FILE *fp = NULL;
  char cmdstr[256];
  char examstr[128];
  int exam;

  int cleanup(int status) {
    if (NULL != fp) {if (-1 == pclose(fp)) status = -1;}
    return status;
  }

  sprintf(cmdstr, "/bin/awk '/Exam Number:/{exno=$%d} \
          END{print exno}' /usr/g/service/log/ifcc.out", 
          IFCC_EXNO_LOC);
  shows(cmdstr);
  if (NULL == (fp = popen(cmdstr, "r"))) return cleanup(-1);
  showi(1);
  if (NULL == fgets(examstr, sizeof(examstr), fp)) return cleanup(-1);
  shows(examstr);
  if (-1 == pclose(&fp)) return cleanup(-1);
  showi(2);
  if (1 != sscanf(examstr, "%d", &exam)) return cleanup(-1);
  showi(exam);
  if ((exam<1)||(exam>65535)) return cleanup(-1);
  return cleanup(exam);
#else
  return 12345;
#endif
}
#endif


int get_exam_number(void)
{
#if defined(HOST_TGT) && !defined(SIM)
  FILE *fp = NULL;
  char IFCC[64]="/usr/g/service/log/ifcc.out";
  char *lineptr=NULL;
  size_t n=0;
  int i, exam = -1;

  if (NULL == (fp = fopen(IFCC, "r"))) {
    exam = -1;
  } else {
    while(-1 != getline(&lineptr, &n, fp)) {
      if (NULL != strstr(lineptr, "Exam Number:")) {
        //shows(lineptr);
        i=0;
        char *token=NULL;
        char *search=" \t";
        token = strtok(lineptr, search);
        while(NULL != token) {
          i++;
          //showi(i);
          //printf(">>%s<<\n", token);
          if (IFCC_EXNO_LOC == i) break;
          token = strtok(NULL, search);
        }
        if (IFCC_EXNO_LOC == i) {
          if (1 != sscanf(token, "%d", &exam)) exam = -1;
        }
      }
    }
    fclose(fp); fp=NULL;
    if (NULL != lineptr) {free(lineptr); lineptr = NULL;}
  }
  return exam;
#else
  return 12345;
#endif
}




int check_rhosts_file(void)
{
#if defined(HOST_TGT) && !defined(SIM)
  FILE *fp = NULL;
  char *lineptr=NULL;
  size_t n=0;
  char RHOSTS[64]="/export/home/sdc/.rhosts";
  int add_aps = 1;
  int add_agp = 1;
  int do_chmod = 0;

  if (NULL == (fp = fopen(RHOSTS, "r"))) {
    do_chmod = 1;
  } else {
    while(-1 != getline(&lineptr, &n, fp)) {
      if (NULL != strstr(lineptr, "aps aps")) add_aps = 0;
      if (NULL != strstr(lineptr, "agp agp")) add_agp = 0;
    }
    fclose(fp); fp=NULL;
    if (NULL != lineptr) {free(lineptr); lineptr = NULL;}
  }

  if (add_aps || add_agp) {
    if (NULL != (fp = fopen(RHOSTS, "a"))) {
      if (add_aps) fprintf(fp, "aps aps\n");
      if (add_agp) fprintf(fp, "agp agp\n");
      fclose(fp); fp=NULL;
    } else {
      return -1;
    }
  }
  if (do_chmod) {
    if (0 != chmod(RHOSTS, S_IRUSR | S_IWUSR)) {
      return -1;
    }
  }
#endif  
  return 0;
}

int run_command(char * remote_command)
{
#ifdef MGD_TGT
  char output[256+1]={'\0'};
  if(-1 == vx_rcmd("host", remote_command, output, 256)) return -1;
  if(NULL!=strstr(output,"ERROR")) return -1;
  return 0;
#elif HOST_TGT
  int status;
  if (-1 == (status = system(remote_command))) return -1;
  if (0 != WEXITSTATUS(status)) return -1;
  return 0;
#endif      
}

#if ESEMAJOR >= 26
static int run_atp_command(char* command)
{
  FILE *fp = NULL;
  if (NULL == (fp = fopen(ATPCMD, "w"))) return 1;
  fprintf(fp, "%s\n", command);
  fclose(fp); 
  return 0;
}
int save_prescan_params(int exno, int prot_no)
{
  char command[256];
  sprintf(command, "save_prescan_params %d %d", exno, prot_no);
  return run_atp_command(command);
}

int load_prescan_params(int exno, int prot_no)
{
  char command[256];
  sprintf(command, "load_prescan_params %d %d", exno, prot_no); 
  return run_atp_command(command);
}
#else
int save_prescan_params(int exno, int prot_no)
{
  char command[256];
  sprintf(command, ATPDIR "save_prescan_params %d %d", exno, prot_no);
  return run_command(command);
}

int load_prescan_params(int exno, int prot_no)
{
  char command[256];
  sprintf(command, "/usr/bin/screen -d -m "
              ATPDIR "load_prescan_params %d %d", exno, prot_no); 
  return run_command(command);
}
#endif

int psc_store_protocol(char *protocolfile, int exno)
{
#if defined(HOST_TGT) 
  char syscmd[256];
  char filename[256]="";
  char prevfile[256]="";
  int num=0;

  if (! file_exist(protocolfile)) return -1;

  sprintf(syscmd, "mkdir -p %s/%d", ARCHIVEDIR, exno);
  system(syscmd);

  do {
    strcpy(prevfile, filename);
    num++;
    sprintf(filename, "%s/%d/psc_protocol.%d.txt", ARCHIVEDIR, exno, num);
  } while (file_exist(filename));

  if (strlen(prevfile)>0) {
    if (0 == cmp(prevfile, protocolfile)) {
      /* use previous file instead*/
      return num-1;
    }
  }
  cp(protocolfile, filename);
  return num;
#else
  protocolfile = protocolfile;
  exno = exno;
  return 1;
#endif
}

int psc_find_protocol(char *protocolfile, int exno)
{
#if defined(HOST_TGT) 
  char syscmd[256];
  char filename[256]="";
  int num=0;

  if (! file_exist(protocolfile)) return -1;

  sprintf(syscmd, "mkdir -p %s/%d", ARCHIVEDIR, exno);
  system(syscmd);
    
  num=0;
  do {
    num++;
    sprintf(filename, "%s/%d/psc_protocol.%d.txt", ARCHIVEDIR, exno, num);
  } while (file_exist(filename));
  num--;
  
  for(;num>0;num--) {
    sprintf(filename, "%s/%d/psc_protocol.%d.txt", ARCHIVEDIR, exno, num);
    if(! file_exist(filename)) break;
    if (0 == cmp(filename, protocolfile)) return num;
  }
  return -1;
#else
  protocolfile = protocolfile;
  exno = exno;
  return 1;
#endif
}

#ifdef SIM
int 
vx_rcmd(char *host, char *command, char *output, int outputn)
{
  return 0;
}

#else

#include "vxWorks.h"
#ifdef STDIOLIBMISSING
extern int      printf (const char *, ...);
#else
#include "stdioLib.h"
#endif
#include "vx_rcmd.h"

extern int fioRead (int fd, char *buffer, int maxbytes);
extern void printErrno( int eno );
extern int rcmd (char *host, int remotePort, char *localuser,
          char *remoteUser, char *cmd, int * fd2p); 
extern int close(int fd);
extern char *strncpy(char *dest, const char *src, size_t n);

#define OK              0
#define ERROR           (-1)

int 
vx_rcmd(char *host, char *command, char *output, int outputn)
{
  int sockfd;
  int n;
  char nextChar;
  int outn;
 
  sockfd = rcmd(host, 514, "agp", "sdc", command, (int *) NULL);
  if (sockfd == ERROR)
  {
    strncpy(output, "RCMD ERROR", outputn);
    /*printErrno(errno);*/
    return(ERROR);
  }
  
  printf("rcmd output:\n");
  outn = 0;
  n = fioRead((int)sockfd, (char *)&nextChar, (int)1);
  while (n==1)
  {
    printf("%c", nextChar);
    if (outn<outputn) output[outn]=nextChar; 
    outn++;
    n = fioRead((int)sockfd, (char *)&nextChar, (int)1);
  }
  close(sockfd);
 
  return(OK);
}
#endif

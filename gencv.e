@host gencvPredownload
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
  int gzwrite_cvs(char *file);
#ifdef __cplusplus
}
#endif /* __cplusplus */

static void * gzwrite_cvs_thread(void *arg)
{
  extern int gzwrite_cvs(char *file);
  gzwrite_cvs(cvsfile);
  pthread_exit((void*)0);
}

STATUS gencv(void)
{
      struct stat buf;
      pthread_t thread;   
#ifdef PSD_HW
#define CVSPATH "/usr/g/psddata/cvs"
#else
#define CVSPATH "/tmp/cvs"
#endif
      if (-1 ==  stat(CVSPATH, &buf)) {
        if (-1 == mkdir(CVSPATH, 0777)) {
           epic_error(use_ermes, "%s %s failed", EM_PSD_SUPPORT_FAILURE,
                   EE_ARGS(2), STRING_ARG, "mkdir", STRING_ARG, CVSPATH);
           return FAILURE;
        }
        chmod(CVSPATH, 0777);
      }
#if ESEMAJOR >= 22
      sprintf(cvsfile, "%s/cvs.%d.txt.gz", CVSPATH, (int)rhkacq_uid);
#elif ESEMAJOR >= 15
      sprintf(cvsfile, "%s/cvs.%d.txt.gz", CVSPATH, (int)rhuser37);
#else
      sprintf(cvsfile, "%s/cvs.%d.txt.gz", CVSPATH, (int)opuser37);
#endif

      if (0 != pthread_create(&thread, NULL, gzwrite_cvs_thread, NULL))
      {
        epic_error(use_ermes, "%s failed", EM_PSD_SUPPORT_FAILURE,
                   EE_ARGS(1), STRING_ARG, "gzwrite_cvs");
        return FAILURE;
      }
      return SUCCESS;
}

#include <string.h>
#include "brs_cv.h"
#include "brs_cv_reader.h"
#include "brs_cv_printer.h"
#include "check_brs_cv.h"
int check_cv_type(char *file)
{
  char sha1sum[ARRAYSIZE_cv_type_sha1sum];
  FILE *fp = NULL;
  int cleanup(int line) { 
    if (NULL != fp) fclose(fp);
    if (line) {
      printf("Error in file %s on line %d\n", __FILE__, line);
    }
    return 1;
  }
  if (NULL == file) return cleanup(__LINE__);
  if (NULL == (fp = fopen(file, "r"))) return cleanup(__LINE__);
  if (0 != fseek(fp, OFFSETOF_cv_type_sha1sum, SEEK_SET)) return cleanup(__LINE__) ;
  if (1 != fread(sha1sum, ARRAYSIZE_cv_type_sha1sum, 1, fp)) return cleanup(__LINE__);
  if (0 != strncmp(SHA1SUM, sha1sum, SHA1LEN)) return cleanup(__LINE__);
  cleanup(0);
  return 0;
}

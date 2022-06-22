#include <stdlib.h>
#include "brs_cv.h"
#include "brs_cv_reader.h"
#include "brs_cv_printer.h"
#include "check_brs_cv.h"
int main(int argc, char **argv)
{
  cv_type * cv=NULL;
  char *raw = NULL;
  FILE *fp = NULL;
 int cleanup(int line) {
    if (NULL != fp) fclose(fp);
    if (NULL != raw) free(raw);
    if (line) {
      printf("Error on line %d\n", line);
    }
    return 1;
  }
  if (argc < 2) return cleanup(__LINE__);
  if (0 != check_cv_type(argv[1])) return cleanup(__LINE__); 
  cv = (cv_type *)malloc(sizeof(cv_type));
  raw = (char *) malloc(SIZEOF_cv_type);
  if (NULL == (fp = fopen(argv[1], "r"))) return cleanup(__LINE__);
  if (1 != fread(raw, SIZEOF_cv_type, 1, fp)) return cleanup(__LINE__);
  fill_brs_cv_type(raw, cv, 1);
  print_brs_cv_type(stdout, argv[1], 0, cv, 1);
  cleanup(0);return 0;
}

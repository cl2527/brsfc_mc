/*************************************************************/
/*                                                           */
/* Copyright (C) 2011 Weil Cornell Medical College           */
/*                                                           */
/*  Author: Pascal Spincemaille                              */
/*                                                           */
/*************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <alloca.h>
#include "brsfc_cv.h"
#include "brsfc_cv_reader.h"
#include "brsfc_cv_printer.h"

int print_brsfc_num_significant_digits = 0;

void print_brsfc_int(FILE * fp, char *str, int indent, int * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%d ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_int32_t(FILE * fp, char *str, int indent, int32_t * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%d ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_unsigned_char(FILE * fp, char *str, int indent, unsigned char * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%c ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_signed_char(FILE * fp, char *str, int indent, signed char * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%c ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_n32(FILE * fp, char *str, int indent, n32 * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%ld ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_s32(FILE * fp, char *str, int indent, s32 * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%ld ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_double(FILE * fp, char *str, int indent, double * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%g ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_short(FILE * fp, char *str, int indent, short * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%d ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_float(FILE * fp, char *str, int indent, float * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      if ( print_brsfc_num_significant_digits > 0 ) {
        char fmt[16];
        sprintf(fmt, "%%.%dg ", print_brsfc_num_significant_digits);
        fprintf(fp, fmt, val[i]);
      } else {
        fprintf(fp, "%f ", val[i]);
      }
    }
  fprintf(fp, "\n");
}

void print_brsfc_long(FILE * fp, char *str, int indent, long * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%ld ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_unsigned_long_int(FILE * fp, char *str, int indent, unsigned long int * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%ld ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_u_int64_t(FILE * fp, char *str, int indent, u_int64_t * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%lld ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_int64_t(FILE * fp, char *str, int indent, int64_t * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%lld ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_unsigned_short(FILE * fp, char *str, int indent, unsigned short * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%d ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_unsigned_long(FILE * fp, char *str, int indent, unsigned long * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%ld ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_long_int(FILE * fp, char *str, int indent, long int * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%ld ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_unsigned_int(FILE * fp, char *str, int indent, unsigned int * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%d ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_int16_t(FILE * fp, char *str, int indent, int16_t * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%d ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_unsigned_short_int(FILE * fp, char *str, int indent, unsigned short int * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%d ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_u_int16_t(FILE * fp, char *str, int indent, u_int16_t * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%d ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_char(FILE * fp, char *str, int indent, char * val, int n)
{
  int i, len, templen, j;

  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  if ((2<(len=strlen(str))) && 
      ((0 == strncmp(str+len-3, "uid", 3)) ||
       (0 == strncmp(str+len-3, "UID", 3))   )) {
    char *temp, *istr;
    temp = (char *)alloca(sizeof(char)*3*n);
    j = 0;
    for (i=0, istr=val; i<n; i++, istr++) {
      char t1 = (*istr & 0xf0) >> 4;
      char t2 = *istr & 0x0f;
      temp[j] = t1; j++;
      temp[j] = t2; j++;
    }
    templen = j;
    for (i=0, istr=temp; i<templen; i++, istr++) {
      if (*istr == 0x0b) fprintf(fp, ".");
      else if (*istr == 0x00) break;
      else fprintf(fp, "%c", '0' + (*istr - 1));
    }
  } else {
    for (i=0; i<n; i++) {
      if ('\0'==val[i]) break;
      if (!isprint(val[i])) break;
      fprintf(fp, "%c", val[i]);
    }
  }
  fprintf(fp, "\n");
}

void print_brsfc_signed_short_int(FILE * fp, char *str, int indent, signed short int * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%d ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_u_int32_t(FILE * fp, char *str, int indent, u_int32_t * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%d ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_short_int(FILE * fp, char *str, int indent, short int * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%d ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_signed_int(FILE * fp, char *str, int indent, signed int * val, int n)
{
  int i;
  char str2[20];
  sprintf(str2, "%%%ds = ", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
    for (i=0; i<n; i++) {
      fprintf(fp, "%d ", val[i]);
    }
  fprintf(fp, "\n");
}

void print_brsfc_ptrdiff_t(FILE * fp, char *str, int indent, ptrdiff_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, str2, indent, (long int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_size_t(FILE * fp, char *str, int indent, size_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_long_unsigned_int
    print_brsfc_long_unsigned_int(fp, str2, indent, (long unsigned int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_wchar_t(FILE * fp, char *str, int indent, wchar_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, str2, indent, (int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_int8_t(FILE * fp, char *str, int indent, int8_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_signed_char
    print_brsfc_signed_char(fp, str2, indent, (signed char *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_uint8_t(FILE * fp, char *str, int indent, uint8_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_char
    print_brsfc_unsigned_char(fp, str2, indent, (unsigned char *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_uint16_t(FILE * fp, char *str, int indent, uint16_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_short_int
    print_brsfc_unsigned_short_int(fp, str2, indent, (unsigned short int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_uint32_t(FILE * fp, char *str, int indent, uint32_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_int
    print_brsfc_unsigned_int(fp, str2, indent, (unsigned int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_uint64_t(FILE * fp, char *str, int indent, uint64_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_long_int
    print_brsfc_unsigned_long_int(fp, str2, indent, (unsigned long int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_int_least8_t(FILE * fp, char *str, int indent, int_least8_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_signed_char
    print_brsfc_signed_char(fp, str2, indent, (signed char *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_int_least16_t(FILE * fp, char *str, int indent, int_least16_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_short_int
    print_brsfc_short_int(fp, str2, indent, (short int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_int_least32_t(FILE * fp, char *str, int indent, int_least32_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, str2, indent, (int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_int_least64_t(FILE * fp, char *str, int indent, int_least64_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, str2, indent, (long int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_uint_least8_t(FILE * fp, char *str, int indent, uint_least8_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_char
    print_brsfc_unsigned_char(fp, str2, indent, (unsigned char *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_uint_least16_t(FILE * fp, char *str, int indent, uint_least16_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_short_int
    print_brsfc_unsigned_short_int(fp, str2, indent, (unsigned short int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_uint_least32_t(FILE * fp, char *str, int indent, uint_least32_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_int
    print_brsfc_unsigned_int(fp, str2, indent, (unsigned int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_uint_least64_t(FILE * fp, char *str, int indent, uint_least64_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_long_int
    print_brsfc_unsigned_long_int(fp, str2, indent, (unsigned long int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_int_fast8_t(FILE * fp, char *str, int indent, int_fast8_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_signed_char
    print_brsfc_signed_char(fp, str2, indent, (signed char *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_int_fast16_t(FILE * fp, char *str, int indent, int_fast16_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, str2, indent, (long int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_int_fast32_t(FILE * fp, char *str, int indent, int_fast32_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, str2, indent, (long int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_int_fast64_t(FILE * fp, char *str, int indent, int_fast64_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, str2, indent, (long int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_uint_fast8_t(FILE * fp, char *str, int indent, uint_fast8_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_char
    print_brsfc_unsigned_char(fp, str2, indent, (unsigned char *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_uint_fast16_t(FILE * fp, char *str, int indent, uint_fast16_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_long_int
    print_brsfc_unsigned_long_int(fp, str2, indent, (unsigned long int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_uint_fast32_t(FILE * fp, char *str, int indent, uint_fast32_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_long_int
    print_brsfc_unsigned_long_int(fp, str2, indent, (unsigned long int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_uint_fast64_t(FILE * fp, char *str, int indent, uint_fast64_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_long_int
    print_brsfc_unsigned_long_int(fp, str2, indent, (unsigned long int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_intptr_t(FILE * fp, char *str, int indent, intptr_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, str2, indent, (long int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_uintptr_t(FILE * fp, char *str, int indent, uintptr_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_long_int
    print_brsfc_unsigned_long_int(fp, str2, indent, (unsigned long int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_intmax_t(FILE * fp, char *str, int indent, intmax_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, str2, indent, (long int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_uintmax_t(FILE * fp, char *str, int indent, uintmax_t * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_long_int
    print_brsfc_unsigned_long_int(fp, str2, indent, (unsigned long int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_s8(FILE * fp, char *str, int indent, s8 * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int8_t
    print_brsfc_int8_t(fp, str2, indent, (int8_t *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_n8(FILE * fp, char *str, int indent, n8 * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_uint8_t
    print_brsfc_uint8_t(fp, str2, indent, (uint8_t *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_s16(FILE * fp, char *str, int indent, s16 * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int16_t
    print_brsfc_int16_t(fp, str2, indent, (int16_t *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_n16(FILE * fp, char *str, int indent, n16 * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_uint16_t
    print_brsfc_uint16_t(fp, str2, indent, (uint16_t *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_s64(FILE * fp, char *str, int indent, s64 * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int64_t
    print_brsfc_int64_t(fp, str2, indent, (int64_t *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_n64(FILE * fp, char *str, int indent, n64 * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_uint64_t
    print_brsfc_uint64_t(fp, str2, indent, (uint64_t *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_f32(FILE * fp, char *str, int indent, f32 * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_float
    print_brsfc_float(fp, str2, indent, (float *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_f64(FILE * fp, char *str, int indent, f64 * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_double
    print_brsfc_double(fp, str2, indent, (double *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_ulong(FILE * fp, char *str, int indent, ulong * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_long_int
    print_brsfc_unsigned_long_int(fp, str2, indent, (unsigned long int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_ushort(FILE * fp, char *str, int indent, ushort * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_short_int
    print_brsfc_unsigned_short_int(fp, str2, indent, (unsigned short int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_uint(FILE * fp, char *str, int indent, uint * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_int
    print_brsfc_unsigned_int(fp, str2, indent, (unsigned int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_struct_timespec(FILE * fp, char *str, int indent, struct timespec * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "tv_nsec", indent + 1, &(val[i].tv_nsec), 1);
#endif
  }
}

void print_brsfc_power_monitor_table_t(FILE * fp, char *str, int indent, power_monitor_table_t * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_s16
    print_brsfc_s16(fp, "pmPredictSAR", indent + 1, &(val[i].pmPredictSAR), 1);
#endif
#ifdef SIZEOF_s16
    print_brsfc_s16(fp, "pmContinuousUpdate", indent + 1, &(val[i].pmContinuousUpdate), 1);
#endif
  }
}

void print_brsfc_entry_point_table_t(FILE * fp, char *str, int indent, entry_point_table_t * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_char
    print_brsfc_char(fp, "epname", indent + 1, (char *)(val[i].epname), (16));
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "epamph", indent + 1, &(val[i].epamph), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "epampb", indent + 1, &(val[i].epampb), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "epamps", indent + 1, &(val[i].epamps), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "epampc", indent + 1, &(val[i].epampc), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "epwidthh", indent + 1, &(val[i].epwidthh), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "epwidthb", indent + 1, &(val[i].epwidthb), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "epwidths", indent + 1, &(val[i].epwidths), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "epwidthc", indent + 1, &(val[i].epwidthc), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "epdcycleh", indent + 1, &(val[i].epdcycleh), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "epdcycleb", indent + 1, &(val[i].epdcycleb), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "epdcycles", indent + 1, &(val[i].epdcycles), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "epdcyclec", indent + 1, &(val[i].epdcyclec), 1);
#endif
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, "epsmode", indent + 1, &(val[i].epsmode), 1);
#endif
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, "epfilter", indent + 1, &(val[i].epfilter), 1);
#endif
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, "eprcvrband", indent + 1, &(val[i].eprcvrband), 1);
#endif
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, "eprcvrinput", indent + 1, &(val[i].eprcvrinput), 1);
#endif
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, "eprcvrbias", indent + 1, &(val[i].eprcvrbias), 1);
#endif
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, "eptrdriver", indent + 1, &(val[i].eptrdriver), 1);
#endif
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, "epfastrec", indent + 1, &(val[i].epfastrec), 1);
#endif
#ifdef SIZEOF_s16
    print_brsfc_s16(fp, "epxmtadd", indent + 1, &(val[i].epxmtadd), 1);
#endif
#ifdef SIZEOF_s16
    print_brsfc_s16(fp, "epprexres", indent + 1, &(val[i].epprexres), 1);
#endif
#ifdef SIZEOF_s16
    print_brsfc_s16(fp, "epshldctrl", indent + 1, &(val[i].epshldctrl), 1);
#endif
#ifdef SIZEOF_s16
    print_brsfc_s16(fp, "epgradcoil", indent + 1, &(val[i].epgradcoil), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "eppkpower", indent + 1, &(val[i].eppkpower), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "epseqtime", indent + 1, &(val[i].epseqtime), 1);
#endif
#ifdef SIZEOF_s16
    print_brsfc_s16(fp, "epstartrec", indent + 1, &(val[i].epstartrec), 1);
#endif
#ifdef SIZEOF_s16
    print_brsfc_s16(fp, "ependrec", indent + 1, &(val[i].ependrec), 1);
#endif
#ifdef SIZEOF_power_monitor_table_t
    print_brsfc_power_monitor_table_t(fp, "eppmtable", indent + 1, &(val[i].eppmtable), 1);
#endif
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, "epGeneralBankIndex", indent + 1, &(val[i].epGeneralBankIndex), 1);
#endif
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, "epGeneralBankIndex2", indent + 1, &(val[i].epGeneralBankIndex2), 1);
#endif
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, "epR1BankIndex", indent + 1, &(val[i].epR1BankIndex), 1);
#endif
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, "epNbTransmitSelect", indent + 1, &(val[i].epNbTransmitSelect), 1);
#endif
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, "epBbTransmitSelect", indent + 1, &(val[i].epBbTransmitSelect), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "epMnsConverterSelect", indent + 1, &(val[i].epMnsConverterSelect), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "epRxCoilType", indent + 1, &(val[i].epRxCoilType), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "epxgd_cableirmsmax", indent + 1, &(val[i].epxgd_cableirmsmax), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "epcoilAC_powersum", indent + 1, &(val[i].epcoilAC_powersum), 1);
#endif
  }
}

void print_brsfc_ENTRY_POINT_TABLE(FILE * fp, char *str, int indent, ENTRY_POINT_TABLE * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_entry_point_table_t
    print_brsfc_entry_point_table_t(fp, str2, indent, (entry_point_table_t *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_ENTRY_PNT_TABLE(FILE * fp, char *str, int indent, ENTRY_PNT_TABLE * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_entry_point_table_t
    print_brsfc_entry_point_table_t(fp, str2, indent, (entry_point_table_t *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_CHAR(FILE * fp, char *str, int indent, CHAR * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_char
    print_brsfc_char(fp, str2, indent, (char *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_SHORT(FILE * fp, char *str, int indent, SHORT * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_s16
    print_brsfc_s16(fp, str2, indent, (s16 *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_INT(FILE * fp, char *str, int indent, INT * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, str2, indent, (int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_LONG(FILE * fp, char *str, int indent, LONG * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_INT
    print_brsfc_INT(fp, str2, indent, (INT *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_FLOAT(FILE * fp, char *str, int indent, FLOAT * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, str2, indent, (f32 *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_DOUBLE(FILE * fp, char *str, int indent, DOUBLE * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_f64
    print_brsfc_f64(fp, str2, indent, (f64 *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_UCHAR(FILE * fp, char *str, int indent, UCHAR * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, str2, indent, (n8 *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_USHORT(FILE * fp, char *str, int indent, USHORT * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, str2, indent, (n16 *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_UINT(FILE * fp, char *str, int indent, UINT * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_int
    print_brsfc_unsigned_int(fp, str2, indent, (unsigned int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_ULONG(FILE * fp, char *str, int indent, ULONG * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_UINT
    print_brsfc_UINT(fp, str2, indent, (UINT *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_STATUS(FILE * fp, char *str, int indent, STATUS * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, str2, indent, (int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_t_axis(FILE * fp, char *str, int indent, t_axis * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_t_fopen_mode(FILE * fp, char *str, int indent, t_fopen_mode * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc__G_fpos64_t(FILE * fp, char *str, int indent, _G_fpos64_t * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
  }
}

void print_brsfc_struct__IO_marker(FILE * fp, char *str, int indent, struct _IO_marker  * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, "_pos", indent + 1, &(val[i]._pos), 1);
#endif
  }
}

void print_brsfc_datavalue(FILE * fp, char *str, int indent, datavalue * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_float
    print_brsfc_float(fp, str2, indent, (float *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_GRADIENT_COIL_E(FILE * fp, char *str, int indent, GRADIENT_COIL_E * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_PSD_BOARD_TYPE_E(FILE * fp, char *str, int indent, PSD_BOARD_TYPE_E * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_GRADIENT_COIL_METHOD_E(FILE * fp, char *str, int indent, GRADIENT_COIL_METHOD_E * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_POWER_IN_HEAT_CALC_E(FILE * fp, char *str, int indent, POWER_IN_HEAT_CALC_E * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_WF_HARDWARE_TYPE(FILE * fp, char *str, int indent, WF_HARDWARE_TYPE * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_HW_DIRECTION(FILE * fp, char *str, int indent, HW_DIRECTION * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_SSP_S_ATTRIB(FILE * fp, char *str, int indent, SSP_S_ATTRIB * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_TYPDAB_PACKETS(FILE * fp, char *str, int indent, TYPDAB_PACKETS * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_TYPACQ_PASS(FILE * fp, char *str, int indent, TYPACQ_PASS * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_WF_PROCESSOR(FILE * fp, char *str, int indent, WF_PROCESSOR * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_WF_HW_WAVEFORM_PTR(FILE * fp, char *str, int indent, WF_HW_WAVEFORM_PTR * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_long
    print_brsfc_long(fp, str2, indent, (long *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_WF_HW_INSTR_PTR(FILE * fp, char *str, int indent, WF_HW_INSTR_PTR * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_long
    print_brsfc_long(fp, str2, indent, (long *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_WF_INSTR_HDR(FILE * fp, char *str, int indent, WF_INSTR_HDR * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_WF_HW_INSTR_PTR
    print_brsfc_WF_HW_INSTR_PTR(fp, "wf_instr_ptr", indent + 1, &(val[i].wf_instr_ptr), 1);
#endif
#ifdef SIZEOF_long
    print_brsfc_long(fp, "amplitude", indent + 1, &(val[i].amplitude), 1);
#endif
#ifdef SIZEOF_long
    print_brsfc_long(fp, "period", indent + 1, &(val[i].period), 1);
#endif
#ifdef SIZEOF_long
    print_brsfc_long(fp, "start", indent + 1, &(val[i].start), 1);
#endif
#ifdef SIZEOF_long
    print_brsfc_long(fp, "end", indent + 1, &(val[i].end), 1);
#endif
#ifdef SIZEOF_long
    print_brsfc_long(fp, "entry_group", indent + 1, &(val[i].entry_group), 1);
#endif
  }
}

void print_brsfc_CONST_EXT(FILE * fp, char *str, int indent, CONST_EXT * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_short
    print_brsfc_short(fp, "amplitude", indent + 1, &(val[i].amplitude), 1);
#endif
  }
}

void print_brsfc_HADAMARD_EXT(FILE * fp, char *str, int indent, HADAMARD_EXT * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_short
    print_brsfc_short(fp, "amplitude", indent + 1, &(val[i].amplitude), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "separation", indent + 1, &(val[i].separation), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "nsinc_cycles", indent + 1, &(val[i].nsinc_cycles), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha", indent + 1, &(val[i].alpha), 1);
#endif
  }
}

void print_brsfc_RAMP_EXT(FILE * fp, char *str, int indent, RAMP_EXT * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_short
    print_brsfc_short(fp, "start_amplitude", indent + 1, &(val[i].start_amplitude), 1);
#endif
#ifdef SIZEOF_short
    print_brsfc_short(fp, "end_amplitude", indent + 1, &(val[i].end_amplitude), 1);
#endif
  }
}

void print_brsfc_SINC_EXT(FILE * fp, char *str, int indent, SINC_EXT * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_short
    print_brsfc_short(fp, "amplitude", indent + 1, &(val[i].amplitude), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "nsinc_cycles", indent + 1, &(val[i].nsinc_cycles), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha", indent + 1, &(val[i].alpha), 1);
#endif
  }
}

void print_brsfc_SINUSOID_EXT(FILE * fp, char *str, int indent, SINUSOID_EXT * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_short
    print_brsfc_short(fp, "amplitude", indent + 1, &(val[i].amplitude), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "start_phase", indent + 1, &(val[i].start_phase), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "phase_length", indent + 1, &(val[i].phase_length), 1);
#endif
#ifdef SIZEOF_short
    print_brsfc_short(fp, "offset", indent + 1, &(val[i].offset), 1);
#endif
  }
}

void print_brsfc_WF_PULSE_EXT(FILE * fp, char *str, int indent, WF_PULSE_EXT * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_CONST_EXT
    print_brsfc_CONST_EXT(fp, "constext", indent + 1, &(val[i].constext), 1);
#endif
#ifdef SIZEOF_HADAMARD_EXT
    print_brsfc_HADAMARD_EXT(fp, "hadamard", indent + 1, &(val[i].hadamard), 1);
#endif
#ifdef SIZEOF_RAMP_EXT
    print_brsfc_RAMP_EXT(fp, "ramp", indent + 1, &(val[i].ramp), 1);
#endif
#ifdef SIZEOF_SINC_EXT
    print_brsfc_SINC_EXT(fp, "sinc", indent + 1, &(val[i].sinc), 1);
#endif
#ifdef SIZEOF_SINUSOID_EXT
    print_brsfc_SINUSOID_EXT(fp, "sinusoid", indent + 1, &(val[i].sinusoid), 1);
#endif
  }
}

void print_brsfc_WF_PULSE_TYPES(FILE * fp, char *str, int indent, WF_PULSE_TYPES * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_WF_PGMTAG(FILE * fp, char *str, int indent, WF_PGMTAG * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_WF_PGMREUSE(FILE * fp, char *str, int indent, WF_PGMREUSE * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_WF_PULSE(FILE * fp, char *str, int indent, WF_PULSE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_long
    print_brsfc_long(fp, "ninsts", indent + 1, &(val[i].ninsts), 1);
#endif
#ifdef SIZEOF_WF_HW_WAVEFORM_PTR
    print_brsfc_WF_HW_WAVEFORM_PTR(fp, "wave_addr", indent + 1, &(val[i].wave_addr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "board_type", indent + 1, &(val[i].board_type), 1);
#endif
#ifdef SIZEOF_WF_PGMREUSE
    print_brsfc_WF_PGMREUSE(fp, "reusep", indent + 1, &(val[i].reusep), 1);
#endif
#ifdef SIZEOF_WF_PGMTAG
    print_brsfc_WF_PGMTAG(fp, "tag", indent + 1, &(val[i].tag), 1);
#endif
#ifdef SIZEOF_long
    print_brsfc_long(fp, "addtag", indent + 1, &(val[i].addtag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "id", indent + 1, &(val[i].id), 1);
#endif
#ifdef SIZEOF_long
    print_brsfc_long(fp, "ctrlfield", indent + 1, &(val[i].ctrlfield), 1);
#endif
#ifdef SIZEOF_WF_PROCESSOR
    print_brsfc_WF_PROCESSOR(fp, "wavegen_type", indent + 1, &(val[i].wavegen_type), 1);
#endif
#ifdef SIZEOF_WF_PULSE_TYPES
    print_brsfc_WF_PULSE_TYPES(fp, "type", indent + 1, &(val[i].type), 1);
#endif
#ifdef SIZEOF_short
    print_brsfc_short(fp, "resolution", indent + 1, &(val[i].resolution), 1);
#endif
  }
}

void print_brsfc_WF_INSTR_QUEUE(FILE * fp, char *str, int indent, WF_INSTR_QUEUE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
  }
}

void print_brsfc_SEQUENCE_ENTRIES(FILE * fp, char *str, int indent, SEQUENCE_ENTRIES * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_long
    print_brsfc_long(fp, str2, indent, (long *)val[i], (9));
#endif
  }
}

void print_brsfc_SEQUENCE_LIST(FILE * fp, char *str, int indent, SEQUENCE_LIST * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_long
    print_brsfc_long(fp, "time", indent + 1, &(val[i].time), 1);
#endif
  }
}

void print_brsfc_exciterSelection(FILE * fp, char *str, int indent, exciterSelection * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_receiverSelection(FILE * fp, char *str, int indent, receiverSelection * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_demodSelection(FILE * fp, char *str, int indent, demodSelection * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_navSelection(FILE * fp, char *str, int indent, navSelection * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_struct_EXT_CERD_PARAMS(FILE * fp, char *str, int indent, struct EXT_CERD_PARAMS * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "alg", indent + 1, &(val[i].alg), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "demod", indent + 1, &(val[i].demod), 1);
#endif
  }
}

void print_brsfc_PSD_FILTER_GEN(FILE * fp, char *str, int indent, PSD_FILTER_GEN * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_f64
    print_brsfc_f64(fp, "filfrq", indent + 1, &(val[i].filfrq), 1);
#endif
#ifdef SIZEOF_struct_EXT_CERD_PARAMS
    print_brsfc_struct_EXT_CERD_PARAMS(fp, "cerd", indent + 1, &(val[i].cerd), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "taps", indent + 1, &(val[i].taps), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "outputs", indent + 1, &(val[i].outputs), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "prefills", indent + 1, &(val[i].prefills), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "filter_slot", indent + 1, &(val[i].filter_slot), 1);
#endif
  }
}

void print_brsfc_SCAN_INFO(FILE * fp, char *str, int indent, SCAN_INFO * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_float
    print_brsfc_float(fp, "oprloc", indent + 1, &(val[i].oprloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opphasoff", indent + 1, &(val[i].opphasoff), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "optloc", indent + 1, &(val[i].optloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "oprloc_shift", indent + 1, &(val[i].oprloc_shift), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opphasoff_shift", indent + 1, &(val[i].opphasoff_shift), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "optloc_shift", indent + 1, &(val[i].optloc_shift), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opfov_freq_scale", indent + 1, &(val[i].opfov_freq_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opfov_phase_scale", indent + 1, &(val[i].opfov_phase_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opslthick_scale", indent + 1, &(val[i].opslthick_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "oprot", indent + 1, (float *)(val[i].oprot), (9));
#endif
  }
}

void print_brsfc_PSC_INFO(FILE * fp, char *str, int indent, PSC_INFO * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_float
    print_brsfc_float(fp, "oppsctloc", indent + 1, &(val[i].oppsctloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "oppscrloc", indent + 1, &(val[i].oppscrloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "oppscphasoff", indent + 1, &(val[i].oppscphasoff), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "oppscrot", indent + 1, (float *)(val[i].oppscrot), (9));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oppsclenx", indent + 1, &(val[i].oppsclenx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oppscleny", indent + 1, &(val[i].oppscleny), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oppsclenz", indent + 1, &(val[i].oppsclenz), 1);
#endif
  }
}

void print_brsfc_DATA_ACQ_ORDER(FILE * fp, char *str, int indent, DATA_ACQ_ORDER * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_short
    print_brsfc_short(fp, "slloc", indent + 1, &(val[i].slloc), 1);
#endif
#ifdef SIZEOF_short
    print_brsfc_short(fp, "slpass", indent + 1, &(val[i].slpass), 1);
#endif
#ifdef SIZEOF_short
    print_brsfc_short(fp, "sltime", indent + 1, &(val[i].sltime), 1);
#endif
  }
}

void print_brsfc_RSP_INFO(FILE * fp, char *str, int indent, RSP_INFO * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rsptloc", indent + 1, &(val[i].rsptloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rsprloc", indent + 1, &(val[i].rsprloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rspphasoff", indent + 1, &(val[i].rspphasoff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "slloc", indent + 1, &(val[i].slloc), 1);
#endif
  }
}

void print_brsfc_CTMEntryType(FILE * fp, char *str, int indent, CTMEntryType * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, "receiverID", indent + 1, &(val[i].receiverID), 1);
#endif
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, "receiverChannel", indent + 1, &(val[i].receiverChannel), 1);
#endif
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, "entryMask", indent + 1, &(val[i].entryMask), 1);
#endif
  }
}

void print_brsfc_QuadVolWeightType(FILE * fp, char *str, int indent, QuadVolWeightType * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, "receiverID", indent + 1, &(val[i].receiverID), 1);
#endif
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, "receiverChannel", indent + 1, &(val[i].receiverChannel), 1);
#endif
#ifdef SIZEOF_n8
    print_brsfc_n8(fp, "pad", indent + 1, (n8 *)(val[i].pad), (2));
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "recWeight", indent + 1, &(val[i].recWeight), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "recPhaseDeg", indent + 1, &(val[i].recPhaseDeg), 1);
#endif
  }
}

void print_brsfc_ChannelTransTableEntryType(FILE * fp, char *str, int indent, ChannelTransTableEntryType * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_s8
    print_brsfc_s8(fp, "logicalCoilName", indent + 1, (s8 *)(val[i].logicalCoilName), (128));
#endif
#ifdef SIZEOF_s8
    print_brsfc_s8(fp, "clinicalCoilName", indent + 1, (s8 *)(val[i].clinicalCoilName), (32));
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "configUID", indent + 1, &(val[i].configUID), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "coilConnector", indent + 1, &(val[i].coilConnector), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "isActiveScanConfig", indent + 1, &(val[i].isActiveScanConfig), 1);
#endif
#ifdef SIZEOF_CTMEntryType
    print_brsfc_CTMEntryType(fp, "channelTranslationMap", indent + 1, (CTMEntryType *)(val[i].channelTranslationMap), (256));
#endif
#ifdef SIZEOF_QuadVolWeightType
    print_brsfc_QuadVolWeightType(fp, "quadVolReceiveWeights", indent + 1, (QuadVolWeightType *)(val[i].quadVolReceiveWeights), (16));
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "numChannels", indent + 1, &(val[i].numChannels), 1);
#endif
  }
}

void print_brsfc_INSTALL_COIL_INFO(FILE * fp, char *str, int indent, INSTALL_COIL_INFO * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_char
    print_brsfc_char(fp, "coilCode", indent + 1, (char *)(val[i].coilCode), ((32 + 8)));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "isInCoilDatabase", indent + 1, &(val[i].isInCoilDatabase), 1);
#endif
  }
}

void print_brsfc_INSTALL_COIL_CONNECTOR_INFO(FILE * fp, char *str, int indent, INSTALL_COIL_CONNECTOR_INFO * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, "connector", indent + 1, &(val[i].connector), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "needsInstall", indent + 1, &(val[i].needsInstall), 1);
#endif
#ifdef SIZEOF_INSTALL_COIL_INFO
    print_brsfc_INSTALL_COIL_INFO(fp, "installCoilInfo", indent + 1, (INSTALL_COIL_INFO *)(val[i].installCoilInfo), (4));
#endif
  }
}

void print_brsfc_COIL_CONFIG_PARAM_TYPE(FILE * fp, char *str, int indent, COIL_CONFIG_PARAM_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_char
    print_brsfc_char(fp, "coilName", indent + 1, (char *)(val[i].coilName), (16));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "GEcoilName", indent + 1, (char *)(val[i].GEcoilName), (24));
#endif
#ifdef SIZEOF_short
    print_brsfc_short(fp, "pureCorrection", indent + 1, &(val[i].pureCorrection), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "maxNumOfReceivers", indent + 1, &(val[i].maxNumOfReceivers), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "coilType", indent + 1, &(val[i].coilType), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "txCoilType", indent + 1, &(val[i].txCoilType), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fastTGmode", indent + 1, &(val[i].fastTGmode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fastTGstartTA", indent + 1, &(val[i].fastTGstartTA), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fastTGstartRG", indent + 1, &(val[i].fastTGstartRG), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nuclide", indent + 1, &(val[i].nuclide), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tRPAvolumeRecEnable", indent + 1, &(val[i].tRPAvolumeRecEnable), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pureCompatible", indent + 1, &(val[i].pureCompatible), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "aps1StartTA", indent + 1, &(val[i].aps1StartTA), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cflStartTA", indent + 1, &(val[i].cflStartTA), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfhSensitiveAnatomy", indent + 1, &(val[i].cfhSensitiveAnatomy), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pureLambda", indent + 1, &(val[i].pureLambda), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pureTuningFactorSurface", indent + 1, &(val[i].pureTuningFactorSurface), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pureTuningFactorBody", indent + 1, &(val[i].pureTuningFactorBody), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cableLoss", indent + 1, &(val[i].cableLoss), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "coilLoss", indent + 1, &(val[i].coilLoss), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "reconScale", indent + 1, &(val[i].reconScale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "autoshimFOV", indent + 1, &(val[i].autoshimFOV), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "coilWeights", indent + 1, (float *)(val[i].coilWeights), (4)*(256));
#endif
#ifdef SIZEOF_ChannelTransTableEntryType
    print_brsfc_ChannelTransTableEntryType(fp, "cttEntry", indent + 1, (ChannelTransTableEntryType *)(val[i].cttEntry), (4));
#endif
  }
}

void print_brsfc_APPLICATION_CONFIG_PARAM_TYPE(FILE * fp, char *str, int indent, APPLICATION_CONFIG_PARAM_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, "aps1StartTA", indent + 1, &(val[i].aps1StartTA), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cflStartTA", indent + 1, &(val[i].cflStartTA), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "AScfPatLocChangeRL", indent + 1, &(val[i].AScfPatLocChangeRL), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "AScfPatLocChangeAP", indent + 1, &(val[i].AScfPatLocChangeAP), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "AScfPatLocChangeSI", indent + 1, &(val[i].AScfPatLocChangeSI), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "TGpatLocChangeRL", indent + 1, &(val[i].TGpatLocChangeRL), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "TGpatLocChangeAP", indent + 1, &(val[i].TGpatLocChangeAP), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "TGpatLocChangeSI", indent + 1, &(val[i].TGpatLocChangeSI), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "autoshimFOV", indent + 1, &(val[i].autoshimFOV), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fastTGstartTA", indent + 1, &(val[i].fastTGstartTA), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fastTGstartRG", indent + 1, &(val[i].fastTGstartRG), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fastTGmode", indent + 1, &(val[i].fastTGmode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfhSensitiveAnatomy", indent + 1, &(val[i].cfhSensitiveAnatomy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "aps1Mod", indent + 1, &(val[i].aps1Mod), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "aps1Plane", indent + 1, &(val[i].aps1Plane), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pureCompatible", indent + 1, &(val[i].pureCompatible), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "maxFOV", indent + 1, &(val[i].maxFOV), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "assetThresh", indent + 1, &(val[i].assetThresh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "scic_a_used", indent + 1, &(val[i].scic_a_used), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "scic_s_used", indent + 1, &(val[i].scic_s_used), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "scic_c_used", indent + 1, &(val[i].scic_c_used), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "aps1ModFOV", indent + 1, &(val[i].aps1ModFOV), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "aps1ModPStloc", indent + 1, &(val[i].aps1ModPStloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "aps1ModPSrloc", indent + 1, &(val[i].aps1ModPSrloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opthickPSMod", indent + 1, &(val[i].opthickPSMod), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pureScale", indent + 1, &(val[i].pureScale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pureCorrectionThreshold", indent + 1, &(val[i].pureCorrectionThreshold), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pureLambda", indent + 1, &(val[i].pureLambda), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pureTuningFactorSurface", indent + 1, &(val[i].pureTuningFactorSurface), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pureTuningFactorBody", indent + 1, &(val[i].pureTuningFactorBody), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "scic_a", indent + 1, (float *)(val[i].scic_a), (7));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "scic_s", indent + 1, (float *)(val[i].scic_s), (7));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "scic_c", indent + 1, (float *)(val[i].scic_c), (7));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "assetSupported", indent + 1, &(val[i].assetSupported), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "assetValues", indent + 1, (float *)(val[i].assetValues), (3));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "arcSupported", indent + 1, &(val[i].arcSupported), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arcValues", indent + 1, (float *)(val[i].arcValues), (3));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sagCalEnabled", indent + 1, &(val[i].sagCalEnabled), 1);
#endif
  }
}

void print_brsfc_APPLICATION_CONFIG_HDR(FILE * fp, char *str, int indent, APPLICATION_CONFIG_HDR * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, "error", indent + 1, &(val[i].error), 1);
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "clinicalName", indent + 1, (char *)(val[i].clinicalName), (32));
#endif
#ifdef SIZEOF_APPLICATION_CONFIG_PARAM_TYPE
    print_brsfc_APPLICATION_CONFIG_PARAM_TYPE(fp, "appConfig", indent + 1, &(val[i].appConfig), 1);
#endif
  }
}

void print_brsfc_COIL_INFO(FILE * fp, char *str, int indent, COIL_INFO * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_s8
    print_brsfc_s8(fp, "coilName", indent + 1, (s8 *)(val[i].coilName), (32));
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "txIndexPri", indent + 1, &(val[i].txIndexPri), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "txIndexSec", indent + 1, &(val[i].txIndexSec), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "rxCoilType", indent + 1, &(val[i].rxCoilType), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "hubIndex", indent + 1, &(val[i].hubIndex), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "rxNucleus", indent + 1, &(val[i].rxNucleus), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "aps1Mod", indent + 1, &(val[i].aps1Mod), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "aps1ModPlane", indent + 1, &(val[i].aps1ModPlane), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "coilSepDir", indent + 1, &(val[i].coilSepDir), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "assetCalThreshold", indent + 1, &(val[i].assetCalThreshold), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "aps1ModFov", indent + 1, &(val[i].aps1ModFov), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "aps1ModSlThick", indent + 1, &(val[i].aps1ModSlThick), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "aps1ModPsTloc", indent + 1, &(val[i].aps1ModPsTloc), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "aps1ModPsRloc", indent + 1, &(val[i].aps1ModPsRloc), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "autoshimFov", indent + 1, &(val[i].autoshimFov), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "assetCalMaxFov", indent + 1, &(val[i].assetCalMaxFov), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "maxB1Rms", indent + 1, &(val[i].maxB1Rms), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "pureCompatible", indent + 1, &(val[i].pureCompatible), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "pureLambda", indent + 1, &(val[i].pureLambda), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "pureTuningFactorSurface", indent + 1, &(val[i].pureTuningFactorSurface), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "pureTuningFactorBody", indent + 1, &(val[i].pureTuningFactorBody), 1);
#endif
  }
}

void print_brsfc_TX_COIL_INFO(FILE * fp, char *str, int indent, TX_COIL_INFO * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "coilAtten", indent + 1, &(val[i].coilAtten), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "txCoilType", indent + 1, &(val[i].txCoilType), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "txPosition", indent + 1, &(val[i].txPosition), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "txNucleus", indent + 1, &(val[i].txNucleus), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "txAmp", indent + 1, &(val[i].txAmp), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "maxB1Peak", indent + 1, &(val[i].maxB1Peak), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "maxB1Squared", indent + 1, &(val[i].maxB1Squared), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "cableLoss", indent + 1, &(val[i].cableLoss), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "coilLoss", indent + 1, &(val[i].coilLoss), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "reflCoeffSquared", indent + 1, (f32 *)(val[i].reflCoeffSquared), (10));
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "reflCoeffMassOffset", indent + 1, &(val[i].reflCoeffMassOffset), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "reflCoeffCurveType", indent + 1, &(val[i].reflCoeffCurveType), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "exposedMass", indent + 1, (f32 *)(val[i].exposedMass), (8));
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "lowSarExposedMass", indent + 1, (f32 *)(val[i].lowSarExposedMass), (8));
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "jstd", indent + 1, (f32 *)(val[i].jstd), (12));
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "meanJstd", indent + 1, (f32 *)(val[i].meanJstd), (12));
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "separationStdev", indent + 1, &(val[i].separationStdev), 1);
#endif
  }
}

void print_brsfc_PSD_COIL_INFO(FILE * fp, char *str, int indent, PSD_COIL_INFO * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_COIL_INFO
    print_brsfc_COIL_INFO(fp, "imgRcvCoilInfo", indent + 1, (COIL_INFO *)(val[i].imgRcvCoilInfo), (10));
#endif
#ifdef SIZEOF_COIL_INFO
    print_brsfc_COIL_INFO(fp, "volRcvCoilInfo", indent + 1, (COIL_INFO *)(val[i].volRcvCoilInfo), (10));
#endif
#ifdef SIZEOF_TX_COIL_INFO
    print_brsfc_TX_COIL_INFO(fp, "txCoilInfo", indent + 1, (TX_COIL_INFO *)(val[i].txCoilInfo), (5));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "numCoils", indent + 1, &(val[i].numCoils), 1);
#endif
  }
}

void print_brsfc_GRAD_PULSE(FILE * fp, char *str, int indent, GRAD_PULSE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ptype", indent + 1, &(val[i].ptype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num", indent + 1, &(val[i].num), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "scale", indent + 1, &(val[i].scale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tdelta", indent + 1, &(val[i].tdelta), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "powscale", indent + 1, &(val[i].powscale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "power", indent + 1, &(val[i].power), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "powpos", indent + 1, &(val[i].powpos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "powneg", indent + 1, &(val[i].powneg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "powabs", indent + 1, &(val[i].powabs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "amptran", indent + 1, &(val[i].amptran), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pwm", indent + 1, &(val[i].pwm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "bridge", indent + 1, &(val[i].bridge), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "intabspwmcurr", indent + 1, &(val[i].intabspwmcurr), 1);
#endif
  }
}

void print_brsfc_RF_PULSE(FILE * fp, char *str, int indent, RF_PULSE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_float
    print_brsfc_float(fp, "abswidth", indent + 1, &(val[i].abswidth), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "effwidth", indent + 1, &(val[i].effwidth), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area", indent + 1, &(val[i].area), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "dtycyc", indent + 1, &(val[i].dtycyc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "maxpw", indent + 1, &(val[i].maxpw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num", indent + 1, &(val[i].num), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "max_b1", indent + 1, &(val[i].max_b1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "max_int_b1_sq", indent + 1, &(val[i].max_int_b1_sq), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "max_rms_b1", indent + 1, &(val[i].max_rms_b1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "nom_fa", indent + 1, &(val[i].nom_fa), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "nom_pw", indent + 1, &(val[i].nom_pw), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "nom_bw", indent + 1, &(val[i].nom_bw), 1);
#endif
#ifdef SIZEOF_unsigned_int
    print_brsfc_unsigned_int(fp, "activity", indent + 1, &(val[i].activity), 1);
#endif
#ifdef SIZEOF_unsigned_char
    print_brsfc_unsigned_char(fp, "reference", indent + 1, &(val[i].reference), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "isodelay", indent + 1, &(val[i].isodelay), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "scale", indent + 1, &(val[i].scale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "extgradfile", indent + 1, &(val[i].extgradfile), 1);
#endif
  }
}

void print_brsfc_RF_PULSE_INFO(FILE * fp, char *str, int indent, RF_PULSE_INFO * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, "change", indent + 1, &(val[i].change), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "newres", indent + 1, &(val[i].newres), 1);
#endif
  }
}

void print_brsfc_PHYS_GRAD(FILE * fp, char *str, int indent, PHYS_GRAD * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xfull", indent + 1, &(val[i].xfull), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "yfull", indent + 1, &(val[i].yfull), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zfull", indent + 1, &(val[i].zfull), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xfs", indent + 1, &(val[i].xfs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "yfs", indent + 1, &(val[i].yfs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zfs", indent + 1, &(val[i].zfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xrt", indent + 1, &(val[i].xrt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "yrt", indent + 1, &(val[i].yrt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zrt", indent + 1, &(val[i].zrt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xft", indent + 1, &(val[i].xft), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "yft", indent + 1, &(val[i].yft), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zft", indent + 1, &(val[i].zft), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xcc", indent + 1, &(val[i].xcc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ycc", indent + 1, &(val[i].ycc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zcc", indent + 1, &(val[i].zcc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xbeta", indent + 1, &(val[i].xbeta), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ybeta", indent + 1, &(val[i].ybeta), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zbeta", indent + 1, &(val[i].zbeta), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xirms", indent + 1, &(val[i].xirms), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "yirms", indent + 1, &(val[i].yirms), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zirms", indent + 1, &(val[i].zirms), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xipeak", indent + 1, &(val[i].xipeak), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "yipeak", indent + 1, &(val[i].yipeak), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zipeak", indent + 1, &(val[i].zipeak), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xamptran", indent + 1, &(val[i].xamptran), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "yamptran", indent + 1, &(val[i].yamptran), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zamptran", indent + 1, &(val[i].zamptran), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xiavrgabs", indent + 1, &(val[i].xiavrgabs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "yiavrgabs", indent + 1, &(val[i].yiavrgabs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ziavrgabs", indent + 1, &(val[i].ziavrgabs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xirmspos", indent + 1, &(val[i].xirmspos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "yirmspos", indent + 1, &(val[i].yirmspos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zirmspos", indent + 1, &(val[i].zirmspos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xirmsneg", indent + 1, &(val[i].xirmsneg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "yirmsneg", indent + 1, &(val[i].yirmsneg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zirmsneg", indent + 1, &(val[i].zirmsneg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xpwmdc", indent + 1, &(val[i].xpwmdc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ypwmdc", indent + 1, &(val[i].ypwmdc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zpwmdc", indent + 1, &(val[i].zpwmdc), 1);
#endif
  }
}

void print_brsfc_t_xact(FILE * fp, char *str, int indent, t_xact * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, "x", indent + 1, &(val[i].x), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xy", indent + 1, &(val[i].xy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xz", indent + 1, &(val[i].xz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xyz", indent + 1, &(val[i].xyz), 1);
#endif
  }
}

void print_brsfc_t_yact(FILE * fp, char *str, int indent, t_yact * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, "y", indent + 1, &(val[i].y), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xy", indent + 1, &(val[i].xy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "yz", indent + 1, &(val[i].yz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xyz", indent + 1, &(val[i].xyz), 1);
#endif
  }
}

void print_brsfc_t_zact(FILE * fp, char *str, int indent, t_zact * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, "z", indent + 1, &(val[i].z), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xz", indent + 1, &(val[i].xz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "yz", indent + 1, &(val[i].yz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xyz", indent + 1, &(val[i].xyz), 1);
#endif
  }
}

void print_brsfc_ramp_t(FILE * fp, char *str, int indent, ramp_t * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xrt", indent + 1, &(val[i].xrt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "yrt", indent + 1, &(val[i].yrt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zrt", indent + 1, &(val[i].zrt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xft", indent + 1, &(val[i].xft), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "yft", indent + 1, &(val[i].yft), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zft", indent + 1, &(val[i].zft), 1);
#endif
  }
}

void print_brsfc_LOG_GRAD(FILE * fp, char *str, int indent, LOG_GRAD * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xrt", indent + 1, &(val[i].xrt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "yrt", indent + 1, &(val[i].yrt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zrt", indent + 1, &(val[i].zrt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xft", indent + 1, &(val[i].xft), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "yft", indent + 1, &(val[i].yft), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zft", indent + 1, &(val[i].zft), 1);
#endif
#ifdef SIZEOF_ramp_t
    print_brsfc_ramp_t(fp, "opt", indent + 1, &(val[i].opt), 1);
#endif
#ifdef SIZEOF_t_xact
    print_brsfc_t_xact(fp, "xrta", indent + 1, &(val[i].xrta), 1);
#endif
#ifdef SIZEOF_t_yact
    print_brsfc_t_yact(fp, "yrta", indent + 1, &(val[i].yrta), 1);
#endif
#ifdef SIZEOF_t_zact
    print_brsfc_t_zact(fp, "zrta", indent + 1, &(val[i].zrta), 1);
#endif
#ifdef SIZEOF_t_xact
    print_brsfc_t_xact(fp, "xfta", indent + 1, &(val[i].xfta), 1);
#endif
#ifdef SIZEOF_t_yact
    print_brsfc_t_yact(fp, "yfta", indent + 1, &(val[i].yfta), 1);
#endif
#ifdef SIZEOF_t_zact
    print_brsfc_t_zact(fp, "zfta", indent + 1, &(val[i].zfta), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xbeta", indent + 1, &(val[i].xbeta), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ybeta", indent + 1, &(val[i].ybeta), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zbeta", indent + 1, &(val[i].zbeta), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tx_xyz", indent + 1, &(val[i].tx_xyz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ty_xyz", indent + 1, &(val[i].ty_xyz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tz_xyz", indent + 1, &(val[i].tz_xyz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tx_xy", indent + 1, &(val[i].tx_xy), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tx_xz", indent + 1, &(val[i].tx_xz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ty_xy", indent + 1, &(val[i].ty_xy), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ty_yz", indent + 1, &(val[i].ty_yz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tz_xz", indent + 1, &(val[i].tz_xz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tz_yz", indent + 1, &(val[i].tz_yz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tx", indent + 1, &(val[i].tx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ty", indent + 1, &(val[i].ty), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tz", indent + 1, &(val[i].tz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xfs", indent + 1, &(val[i].xfs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "yfs", indent + 1, &(val[i].yfs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zfs", indent + 1, &(val[i].zfs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xirms", indent + 1, &(val[i].xirms), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "yirms", indent + 1, &(val[i].yirms), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zirms", indent + 1, &(val[i].zirms), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xipeak", indent + 1, &(val[i].xipeak), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "yipeak", indent + 1, &(val[i].yipeak), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zipeak", indent + 1, &(val[i].zipeak), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xamptran", indent + 1, &(val[i].xamptran), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "yamptran", indent + 1, &(val[i].yamptran), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zamptran", indent + 1, &(val[i].zamptran), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xiavrgabs", indent + 1, &(val[i].xiavrgabs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "yiavrgabs", indent + 1, &(val[i].yiavrgabs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ziavrgabs", indent + 1, &(val[i].ziavrgabs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xirmspos", indent + 1, &(val[i].xirmspos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "yirmspos", indent + 1, &(val[i].yirmspos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zirmspos", indent + 1, &(val[i].zirmspos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xirmsneg", indent + 1, &(val[i].xirmsneg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "yirmsneg", indent + 1, &(val[i].yirmsneg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zirmsneg", indent + 1, &(val[i].zirmsneg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xpwmdc", indent + 1, &(val[i].xpwmdc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ypwmdc", indent + 1, &(val[i].ypwmdc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zpwmdc", indent + 1, &(val[i].zpwmdc), 1);
#endif
  }
}

void print_brsfc_OPT_GRAD_INPUT(FILE * fp, char *str, int indent, OPT_GRAD_INPUT * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xfs", indent + 1, &(val[i].xfs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "yfs", indent + 1, &(val[i].yfs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zfs", indent + 1, &(val[i].zfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xrt", indent + 1, &(val[i].xrt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "yrt", indent + 1, &(val[i].yrt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zrt", indent + 1, &(val[i].zrt), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xbeta", indent + 1, &(val[i].xbeta), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ybeta", indent + 1, &(val[i].ybeta), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zbeta", indent + 1, &(val[i].zbeta), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xfov", indent + 1, &(val[i].xfov), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "yfov", indent + 1, &(val[i].yfov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xres", indent + 1, &(val[i].xres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "yres", indent + 1, &(val[i].yres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ileaves", indent + 1, &(val[i].ileaves), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xdis", indent + 1, &(val[i].xdis), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ydis", indent + 1, &(val[i].ydis), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zdis", indent + 1, &(val[i].zdis), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tsp", indent + 1, &(val[i].tsp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "osamps", indent + 1, &(val[i].osamps), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fbhw", indent + 1, &(val[i].fbhw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "vvp", indent + 1, &(val[i].vvp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pnsf", indent + 1, &(val[i].pnsf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "taratio", indent + 1, &(val[i].taratio), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zarea", indent + 1, &(val[i].zarea), 1);
#endif
  }
}

void print_brsfc_OPT_GRAD_PARAMS(FILE * fp, char *str, int indent, OPT_GRAD_PARAMS * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
  }
}

void print_brsfc_dbkey_exam_type(FILE * fp, char *str, int indent, dbkey_exam_type * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_unsigned_short_int
    print_brsfc_unsigned_short_int(fp, str2, indent, (unsigned short int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_dbkey_magic_type(FILE * fp, char *str, int indent, dbkey_magic_type * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_short_int
    print_brsfc_short_int(fp, str2, indent, (short int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_dbkey_series_type(FILE * fp, char *str, int indent, dbkey_series_type * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_short_int
    print_brsfc_short_int(fp, str2, indent, (short int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_dbkey_image_type(FILE * fp, char *str, int indent, dbkey_image_type * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, str2, indent, (int *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_DbKey(FILE * fp, char *str, int indent, DbKey * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_char
    print_brsfc_char(fp, "su_id", indent + 1, (char *)(val[i].su_id), (4));
#endif
#ifdef SIZEOF_dbkey_magic_type
    print_brsfc_dbkey_magic_type(fp, "mg_no", indent + 1, &(val[i].mg_no), 1);
#endif
#ifdef SIZEOF_dbkey_exam_type
    print_brsfc_dbkey_exam_type(fp, "ex_no", indent + 1, &(val[i].ex_no), 1);
#endif
#ifdef SIZEOF_dbkey_series_type
    print_brsfc_dbkey_series_type(fp, "se_no", indent + 1, &(val[i].se_no), 1);
#endif
#ifdef SIZEOF_dbkey_image_type
    print_brsfc_dbkey_image_type(fp, "im_no", indent + 1, &(val[i].im_no), 1);
#endif
  }
}

void print_brsfc_OP_NMRID_TYPE(FILE * fp, char *str, int indent, OP_NMRID_TYPE * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_char
    print_brsfc_char(fp, str2, indent, (char *)val[i], (12));
#endif
  }
}

void print_brsfc_OP_HDR1_TYPE(FILE * fp, char *str, int indent, OP_HDR1_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, "rev", indent + 1, &(val[i].rev), 1);
#endif
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, "length", indent + 1, &(val[i].length), 1);
#endif
#ifdef SIZEOF_OP_NMRID_TYPE
    print_brsfc_OP_NMRID_TYPE(fp, "req_nmrid", indent + 1, &(val[i].req_nmrid), 1);
#endif
#ifdef SIZEOF_OP_NMRID_TYPE
    print_brsfc_OP_NMRID_TYPE(fp, "resp_nmrid", indent + 1, &(val[i].resp_nmrid), 1);
#endif
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, "opcode", indent + 1, &(val[i].opcode), 1);
#endif
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, "packet_type", indent + 1, &(val[i].packet_type), 1);
#endif
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, "seq_num", indent + 1, &(val[i].seq_num), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "status", indent + 1, &(val[i].status), 1);
#endif
  }
}

void print_brsfc_OP_HDR_TYPE(FILE * fp, char *str, int indent, OP_HDR_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_s8
    print_brsfc_s8(fp, "rev", indent + 1, &(val[i].rev), 1);
#endif
#ifdef SIZEOF_s8
    print_brsfc_s8(fp, "endian", indent + 1, &(val[i].endian), 1);
#endif
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, "length", indent + 1, &(val[i].length), 1);
#endif
#ifdef SIZEOF_OP_NMRID_TYPE
    print_brsfc_OP_NMRID_TYPE(fp, "req_nmrid", indent + 1, &(val[i].req_nmrid), 1);
#endif
#ifdef SIZEOF_OP_NMRID_TYPE
    print_brsfc_OP_NMRID_TYPE(fp, "resp_nmrid", indent + 1, &(val[i].resp_nmrid), 1);
#endif
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, "opcode", indent + 1, &(val[i].opcode), 1);
#endif
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, "packet_type", indent + 1, &(val[i].packet_type), 1);
#endif
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, "seq_num", indent + 1, &(val[i].seq_num), 1);
#endif
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, "pad", indent + 1, &(val[i].pad), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "status", indent + 1, &(val[i].status), 1);
#endif
  }
}

void print_brsfc_OP_RECN_READY_TYPE(FILE * fp, char *str, int indent, OP_RECN_READY_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_DbKey
    print_brsfc_DbKey(fp, "dbkey", indent + 1, &(val[i].dbkey), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "seq_number", indent + 1, &(val[i].seq_number), 1);
#endif
#ifdef SIZEOF_GEtimespec
    print_brsfc_GEtimespec(fp, "time_stamp", indent + 1, &(val[i].time_stamp), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "run_no", indent + 1, &(val[i].run_no), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "prep_flag", indent + 1, &(val[i].prep_flag), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "patient_checksum", indent + 1, &(val[i].patient_checksum), 1);
#endif
  }
}

void print_brsfc_OP_RECN_READY_PACK_TYPE(FILE * fp, char *str, int indent, OP_RECN_READY_PACK_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_OP_HDR_TYPE
    print_brsfc_OP_HDR_TYPE(fp, "hdr", indent + 1, &(val[i].hdr), 1);
#endif
#ifdef SIZEOF_OP_RECN_READY_TYPE
    print_brsfc_OP_RECN_READY_TYPE(fp, "req", indent + 1, &(val[i].req), 1);
#endif
  }
}

void print_brsfc_OP_RECN_FOO_TYPE(FILE * fp, char *str, int indent, OP_RECN_FOO_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "somes32bitint", indent + 1, &(val[i].somes32bitint), 1);
#endif
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, "somen16bitint", indent + 1, &(val[i].somen16bitint), 1);
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "somechar", indent + 1, &(val[i].somechar), 1);
#endif
#ifdef SIZEOF_unsigned_long
    print_brsfc_unsigned_long(fp, "someulong", indent + 1, &(val[i].someulong), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "somefloat", indent + 1, &(val[i].somefloat), 1);
#endif
  }
}

void print_brsfc_OP_RECN_FOO_PACK_TYPE(FILE * fp, char *str, int indent, OP_RECN_FOO_PACK_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_OP_HDR_TYPE
    print_brsfc_OP_HDR_TYPE(fp, "hdr", indent + 1, &(val[i].hdr), 1);
#endif
#ifdef SIZEOF_OP_RECN_FOO_TYPE
    print_brsfc_OP_RECN_FOO_TYPE(fp, "req", indent + 1, &(val[i].req), 1);
#endif
  }
}

void print_brsfc_OP_RECN_START_TYPE(FILE * fp, char *str, int indent, OP_RECN_START_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "seq_number", indent + 1, &(val[i].seq_number), 1);
#endif
#ifdef SIZEOF_GEtimespec
    print_brsfc_GEtimespec(fp, "time_stamp", indent + 1, &(val[i].time_stamp), 1);
#endif
  }
}

void print_brsfc_OP_RECN_START_PACK_TYPE(FILE * fp, char *str, int indent, OP_RECN_START_PACK_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_OP_HDR_TYPE
    print_brsfc_OP_HDR_TYPE(fp, "hdr", indent + 1, &(val[i].hdr), 1);
#endif
#ifdef SIZEOF_OP_RECN_START_TYPE
    print_brsfc_OP_RECN_START_TYPE(fp, "req", indent + 1, &(val[i].req), 1);
#endif
  }
}

void print_brsfc_OP_RECN_SCAN_STOPPED_TYPE(FILE * fp, char *str, int indent, OP_RECN_SCAN_STOPPED_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "seq_number", indent + 1, &(val[i].seq_number), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "status", indent + 1, &(val[i].status), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "aborted_pass_num", indent + 1, &(val[i].aborted_pass_num), 1);
#endif
  }
}

void print_brsfc_OP_RECN_SCAN_STOPPED_PACK_TYPE(FILE * fp, char *str, int indent, OP_RECN_SCAN_STOPPED_PACK_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_OP_HDR_TYPE
    print_brsfc_OP_HDR_TYPE(fp, "hdr", indent + 1, &(val[i].hdr), 1);
#endif
#ifdef SIZEOF_OP_RECN_SCAN_STOPPED_TYPE
    print_brsfc_OP_RECN_SCAN_STOPPED_TYPE(fp, "req", indent + 1, &(val[i].req), 1);
#endif
  }
}

void print_brsfc_OP_RECN_STOP_TYPE(FILE * fp, char *str, int indent, OP_RECN_STOP_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_DbKey
    print_brsfc_DbKey(fp, "dbkey", indent + 1, &(val[i].dbkey), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "seq_number", indent + 1, &(val[i].seq_number), 1);
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "scan_initiator", indent + 1, (char *)(val[i].scan_initiator), (12));
#endif
  }
}

void print_brsfc_OP_RECN_STOP_PACK_TYPE(FILE * fp, char *str, int indent, OP_RECN_STOP_PACK_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_OP_HDR_TYPE
    print_brsfc_OP_HDR_TYPE(fp, "hdr", indent + 1, &(val[i].hdr), 1);
#endif
#ifdef SIZEOF_OP_RECN_STOP_TYPE
    print_brsfc_OP_RECN_STOP_TYPE(fp, "req", indent + 1, &(val[i].req), 1);
#endif
  }
}

void print_brsfc_OP_RECN_IM_ALLOC_TYPE(FILE * fp, char *str, int indent, OP_RECN_IM_ALLOC_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "seq_number", indent + 1, &(val[i].seq_number), 1);
#endif
  }
}

void print_brsfc_OP_RECN_IM_ALLOC_PACK_TYPE(FILE * fp, char *str, int indent, OP_RECN_IM_ALLOC_PACK_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_OP_HDR_TYPE
    print_brsfc_OP_HDR_TYPE(fp, "hdr", indent + 1, &(val[i].hdr), 1);
#endif
#ifdef SIZEOF_OP_RECN_IM_ALLOC_TYPE
    print_brsfc_OP_RECN_IM_ALLOC_TYPE(fp, "req", indent + 1, &(val[i].req), 1);
#endif
  }
}

void print_brsfc_OP_RECN_SCAN_STARTED_TYPE(FILE * fp, char *str, int indent, OP_RECN_SCAN_STARTED_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "seq_number", indent + 1, &(val[i].seq_number), 1);
#endif
  }
}

void print_brsfc_OP_RECN_SCAN_STARTED_PACK_TYPE(FILE * fp, char *str, int indent, OP_RECN_SCAN_STARTED_PACK_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_OP_HDR_TYPE
    print_brsfc_OP_HDR_TYPE(fp, "hdr", indent + 1, &(val[i].hdr), 1);
#endif
#ifdef SIZEOF_OP_RECN_SCAN_STARTED_TYPE
    print_brsfc_OP_RECN_SCAN_STARTED_TYPE(fp, "req", indent + 1, &(val[i].req), 1);
#endif
  }
}

void print_brsfc_OP_VIEWTABLE_UPDATE_TYPE(FILE * fp, char *str, int indent, OP_VIEWTABLE_UPDATE_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "table_size", indent + 1, &(val[i].table_size), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "block_size", indent + 1, &(val[i].block_size), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "first_entry_index", indent + 1, &(val[i].first_entry_index), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "table", indent + 1, (s32 *)(val[i].table), (256));
#endif
  }
}

void print_brsfc_OP_VIEWTABLE_UPDATE_PACK_TYPE(FILE * fp, char *str, int indent, OP_VIEWTABLE_UPDATE_PACK_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_OP_HDR_TYPE
    print_brsfc_OP_HDR_TYPE(fp, "hdr", indent + 1, &(val[i].hdr), 1);
#endif
#ifdef SIZEOF_OP_VIEWTABLE_UPDATE_TYPE
    print_brsfc_OP_VIEWTABLE_UPDATE_TYPE(fp, "pkt", indent + 1, &(val[i].pkt), 1);
#endif
  }
}

void print_brsfc_MROR_ADDR_BLOCK(FILE * fp, char *str, int indent, MROR_ADDR_BLOCK * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_n64
    print_brsfc_n64(fp, "mrhdr", indent + 1, &(val[i].mrhdr), 1);
#endif
#ifdef SIZEOF_n64
    print_brsfc_n64(fp, "pixelhdr", indent + 1, &(val[i].pixelhdr), 1);
#endif
#ifdef SIZEOF_n64
    print_brsfc_n64(fp, "pixeldata", indent + 1, &(val[i].pixeldata), 1);
#endif
#ifdef SIZEOF_n64
    print_brsfc_n64(fp, "raw_offset", indent + 1, &(val[i].raw_offset), 1);
#endif
#ifdef SIZEOF_n64
    print_brsfc_n64(fp, "raw_receivers", indent + 1, &(val[i].raw_receivers), 1);
#endif
#ifdef SIZEOF_n64
    print_brsfc_n64(fp, "pixeldata3", indent + 1, &(val[i].pixeldata3), 1);
#endif
  }
}

void print_brsfc_MROR_ADDR_BLOCK_PKT(FILE * fp, char *str, int indent, MROR_ADDR_BLOCK_PKT * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_OP_HDR_TYPE
    print_brsfc_OP_HDR_TYPE(fp, "hdr", indent + 1, &(val[i].hdr), 1);
#endif
#ifdef SIZEOF_MROR_ADDR_BLOCK
    print_brsfc_MROR_ADDR_BLOCK(fp, "mrab", indent + 1, &(val[i].mrab), 1);
#endif
  }
}

void print_brsfc_MROR_RETRIEVAL_DONE_TYPE(FILE * fp, char *str, int indent, MROR_RETRIEVAL_DONE_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "recon_ts", indent + 1, &(val[i].recon_ts), 1);
#endif
  }
}

void print_brsfc_SCAN_CALIB_INFO_TYPE(FILE * fp, char *str, int indent, SCAN_CALIB_INFO_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "exam_number", indent + 1, &(val[i].exam_number), 1);
#endif
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "calib_flag", indent + 1, &(val[i].calib_flag), 1);
#endif
  }
}

void print_brsfc_SCAN_CALIB_INFO_PACK_TYPE(FILE * fp, char *str, int indent, SCAN_CALIB_INFO_PACK_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_OP_HDR_TYPE
    print_brsfc_OP_HDR_TYPE(fp, "hdr", indent + 1, &(val[i].hdr), 1);
#endif
#ifdef SIZEOF_SCAN_CALIB_INFO_TYPE
    print_brsfc_SCAN_CALIB_INFO_TYPE(fp, "info", indent + 1, &(val[i].info), 1);
#endif
  }
}

void print_brsfc_OP_RECN_SIZE_CHECK_TYPE(FILE * fp, char *str, int indent, OP_RECN_SIZE_CHECK_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_n64
    print_brsfc_n64(fp, "total_bam_size", indent + 1, &(val[i].total_bam_size), 1);
#endif
#ifdef SIZEOF_n64
    print_brsfc_n64(fp, "total_disk_size", indent + 1, &(val[i].total_disk_size), 1);
#endif
  }
}

void print_brsfc_OP_RECN_SIZE_CHECK_PACK_TYPE(FILE * fp, char *str, int indent, OP_RECN_SIZE_CHECK_PACK_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_OP_HDR_TYPE
    print_brsfc_OP_HDR_TYPE(fp, "hdr", indent + 1, &(val[i].hdr), 1);
#endif
#ifdef SIZEOF_OP_RECN_SIZE_CHECK_TYPE
    print_brsfc_OP_RECN_SIZE_CHECK_TYPE(fp, "req", indent + 1, &(val[i].req), 1);
#endif
  }
}

void print_brsfc_EXAM_SCAN_DONE_TYPE(FILE * fp, char *str, int indent, EXAM_SCAN_DONE_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_s32
    print_brsfc_s32(fp, "exam_number", indent + 1, &(val[i].exam_number), 1);
#endif
  }
}

void print_brsfc_EXAM_SCAN_DONE_PACK_TYPE(FILE * fp, char *str, int indent, EXAM_SCAN_DONE_PACK_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_OP_HDR_TYPE
    print_brsfc_OP_HDR_TYPE(fp, "hdr", indent + 1, &(val[i].hdr), 1);
#endif
#ifdef SIZEOF_EXAM_SCAN_DONE_TYPE
    print_brsfc_EXAM_SCAN_DONE_TYPE(fp, "info", indent + 1, &(val[i].info), 1);
#endif
  }
}

void print_brsfc_POSITION_DETECTION_DONE_TYPE(FILE * fp, char *str, int indent, POSITION_DETECTION_DONE_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "object_detected", indent + 1, &(val[i].object_detected), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "object_si_position_mm", indent + 1, &(val[i].object_si_position_mm), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "right_most_voxel_mm", indent + 1, &(val[i].right_most_voxel_mm), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "anterior_most_voxel_mm", indent + 1, &(val[i].anterior_most_voxel_mm), 1);
#endif
#ifdef SIZEOF_f32
    print_brsfc_f32(fp, "superior_most_voxel_mm", indent + 1, &(val[i].superior_most_voxel_mm), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "checksum", indent + 1, &(val[i].checksum), 1);
#endif
  }
}

void print_brsfc_POSITION_DETECTION_DONE_PACK_TYPE(FILE * fp, char *str, int indent, POSITION_DETECTION_DONE_PACK_TYPE * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_OP_HDR_TYPE
    print_brsfc_OP_HDR_TYPE(fp, "hdr", indent + 1, &(val[i].hdr), 1);
#endif
#ifdef SIZEOF_POSITION_DETECTION_DONE_TYPE
    print_brsfc_POSITION_DETECTION_DONE_TYPE(fp, "info", indent + 1, &(val[i].info), 1);
#endif
  }
}

void print_brsfc_CARDIAC_GATE_TYPE_E(FILE * fp, char *str, int indent, CARDIAC_GATE_TYPE_E * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_EXTERN_FILENAME(FILE * fp, char *str, int indent, EXTERN_FILENAME * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_char
    print_brsfc_char(fp, str2, indent, (char *)val[i], (80));
#endif
  }
}

void print_brsfc_PHASE_OFF(FILE * fp, char *str, int indent, PHASE_OFF * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ysign", indent + 1, &(val[i].ysign), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "yoffs", indent + 1, &(val[i].yoffs), 1);
#endif
  }
}

void print_brsfc_RSP_PSC_INFO(FILE * fp, char *str, int indent, RSP_PSC_INFO * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rsppsctloc", indent + 1, &(val[i].rsppsctloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rsppscrloc", indent + 1, &(val[i].rsppscrloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rsppscphasoff", indent + 1, &(val[i].rsppscphasoff), 1);
#endif
#ifdef SIZEOF_long
    print_brsfc_long(fp, "rsppscrot", indent + 1, (long *)(val[i].rsppscrot), (10));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rsppsclenx", indent + 1, &(val[i].rsppsclenx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rsppscleny", indent + 1, &(val[i].rsppscleny), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rsppsclenz", indent + 1, &(val[i].rsppsclenz), 1);
#endif
  }
}

void print_brsfc_GIR_INFO(FILE * fp, char *str, int indent, GIR_INFO * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opgirthick", indent + 1, &(val[i].opgirthick), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opgirtloc", indent + 1, &(val[i].opgirtloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opgirrot", indent + 1, (float *)(val[i].opgirrot), (9));
#endif
  }
}

void print_brsfc_ZY_EXPORT(FILE * fp, char *str, int indent, ZY_EXPORT * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, "view", indent + 1, &(val[i].view), 1);
#endif
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, "slice", indent + 1, &(val[i].slice), 1);
#endif
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, "echo", indent + 1, &(val[i].echo), 1);
#endif
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, "heat", indent + 1, &(val[i].heat), 1);
#endif
#ifdef SIZEOF_n16
    print_brsfc_n16(fp, "flags", indent + 1, &(val[i].flags), 1);
#endif
  }
}

void print_brsfc_VIEWORDER_MODE_E(FILE * fp, char *str, int indent, VIEWORDER_MODE_E * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_REG_VIEWORDER_MODE_E(FILE * fp, char *str, int indent, REG_VIEWORDER_MODE_E * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_REGION_ORDER_MODE_E(FILE * fp, char *str, int indent, REGION_ORDER_MODE_E * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_CAL_PARAM(FILE * fp, char *str, int indent, CAL_PARAM * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_INT
    print_brsfc_INT(fp, "shape", indent + 1, &(val[i].shape), 1);
#endif
#ifdef SIZEOF_INT
    print_brsfc_INT(fp, "phaseCutoffUpper", indent + 1, &(val[i].phaseCutoffUpper), 1);
#endif
#ifdef SIZEOF_INT
    print_brsfc_INT(fp, "phaseCutoffLower", indent + 1, &(val[i].phaseCutoffLower), 1);
#endif
#ifdef SIZEOF_INT
    print_brsfc_INT(fp, "sliceCutoffUpper", indent + 1, &(val[i].sliceCutoffUpper), 1);
#endif
#ifdef SIZEOF_INT
    print_brsfc_INT(fp, "sliceCutoffLower", indent + 1, &(val[i].sliceCutoffLower), 1);
#endif
#ifdef SIZEOF_FLOAT
    print_brsfc_FLOAT(fp, "phaseRadius", indent + 1, &(val[i].phaseRadius), 1);
#endif
#ifdef SIZEOF_FLOAT
    print_brsfc_FLOAT(fp, "sliceRadius", indent + 1, &(val[i].sliceRadius), 1);
#endif
#ifdef SIZEOF_FLOAT
    print_brsfc_FLOAT(fp, "phaseOrigin", indent + 1, &(val[i].phaseOrigin), 1);
#endif
#ifdef SIZEOF_FLOAT
    print_brsfc_FLOAT(fp, "sliceOrigin", indent + 1, &(val[i].sliceOrigin), 1);
#endif
  }
}

void print_brsfc_PARAM4D(FILE * fp, char *str, int indent, PARAM4D * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_VIEWORDER_MODE_E
    print_brsfc_VIEWORDER_MODE_E(fp, "vieworder_mode", indent + 1, &(val[i].vieworder_mode), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "aregion_fraction", indent + 1, &(val[i].aregion_fraction), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_outer_regions", indent + 1, &(val[i].num_outer_regions), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_sub_regions", indent + 1, &(val[i].num_sub_regions), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "smoothec", indent + 1, &(val[i].smoothec), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "views_per_region", indent + 1, (int *)(val[i].views_per_region), (32));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "num_transition_fraction", indent + 1, &(val[i].num_transition_fraction), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "reverse_first_region_flag", indent + 1, &(val[i].reverse_first_region_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "regViewOrderMode", indent + 1, &(val[i].regViewOrderMode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nr_of_segA", indent + 1, &(val[i].nr_of_segA), 1);
#endif
  }
}

void print_brsfc_SPIRAL_VIEW(FILE * fp, char *str, int indent, SPIRAL_VIEW * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_short
    print_brsfc_short(fp, "phase", indent + 1, &(val[i].phase), 1);
#endif
#ifdef SIZEOF_short
    print_brsfc_short(fp, "slice", indent + 1, &(val[i].slice), 1);
#endif
#ifdef SIZEOF_short
    print_brsfc_short(fp, "leaf", indent + 1, &(val[i].leaf), 1);
#endif
  }
}

void print_brsfc_SLAB_OFF(FILE * fp, char *str, int indent, SLAB_OFF * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zsign", indent + 1, &(val[i].zsign), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zoffs", indent + 1, &(val[i].zoffs), 1);
#endif
  }
}

void print_brsfc_CYLR_RF_TYPE_E(FILE * fp, char *str, int indent, CYLR_RF_TYPE_E * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_t_ktsamp(FILE * fp, char *str, int indent, t_ktsamp * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_ViewTable_kyz(FILE * fp, char *str, int indent, ViewTable_kyz * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_short
    print_brsfc_short(fp, "len", indent + 1, &(val[i].len), 1);
#endif
  }
}

void print_brsfc_t_cgatetype(FILE * fp, char *str, int indent, t_cgatetype * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_t_fcineim(FILE * fp, char *str, int indent, t_fcineim * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_t_fcinent(FILE * fp, char *str, int indent, t_fcinent * val, int n)
{
  int i;

  char str2[strlen(str)+21];
  for (i=0; i<n; i++) {
    if (1==n) 
      sprintf(str2, "%s", str);
    else
      sprintf(str2, "%s[%d]", str, i);
#ifdef SIZEOF_int_
    print_brsfc_int_(fp, str2, indent, (int  *)&(val[i]), 1);
#endif
  }
}

void print_brsfc_cv_type(FILE * fp, char *str, int indent, cv_type * val, int n)
{
  int i;
  char str2[20], str3[24];

  sprintf(str2, "%%%ds = \n", 3*indent+(int)strlen(str));
  sprintf(str3, "%%%ds[%%d] = \n", 3*indent+(int)strlen(str));
  fprintf(fp, str2, str);
  for (i=0; i<n; i++) {
    if (1<n) 
      fprintf(fp, str3, str, i);
#ifdef SIZEOF_char
    print_brsfc_char(fp, "psd_name", indent + 1, (char *)(val[i].psd_name), (255));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "host_name", indent + 1, (char *)(val[i].host_name), (32));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "time_stamp", indent + 1, (char *)(val[i].time_stamp), (32));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "sha1sum", indent + 1, (char *)(val[i].sha1sum), (48));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ASSET_MAX_SLQUANT", indent + 1, &(val[i].ASSET_MAX_SLQUANT), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "B1Cal_mode", indent + 1, &(val[i].B1Cal_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "CFHxres", indent + 1, &(val[i].CFHxres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "CFLxres", indent + 1, &(val[i].CFLxres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ChemSatPulse", indent + 1, &(val[i].ChemSatPulse), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "CompleteEchoLoop_flag", indent + 1, &(val[i].CompleteEchoLoop_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "CompositeRMS_method", indent + 1, &(val[i].CompositeRMS_method), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "DATA_ACQ_ORDER_ENTRIES", indent + 1, &(val[i].DATA_ACQ_ORDER_ENTRIES), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "DD_channels", indent + 1, &(val[i].DD_channels), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "DD_debug", indent + 1, &(val[i].DD_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "DD_delay", indent + 1, &(val[i].DD_delay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "DD_nCh", indent + 1, &(val[i].DD_nCh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "FSvar", indent + 1, &(val[i].FSvar), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "FTGacq1", indent + 1, &(val[i].FTGacq1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "FTGacq2", indent + 1, &(val[i].FTGacq2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "FTGau", indent + 1, &(val[i].FTGau), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "FTGecho1bw", indent + 1, &(val[i].FTGecho1bw), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "FTGfov", indent + 1, &(val[i].FTGfov), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "FTGopslthickz1", indent + 1, &(val[i].FTGopslthickz1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "FTGopslthickz2", indent + 1, &(val[i].FTGopslthickz2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "FTGopslthickz3", indent + 1, &(val[i].FTGopslthickz3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "FTGslthk", indent + 1, &(val[i].FTGslthk), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "FTGtau1", indent + 1, &(val[i].FTGtau1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "FTGtau2", indent + 1, &(val[i].FTGtau2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "FTGtecho", indent + 1, &(val[i].FTGtecho), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "FTGtestpulse", indent + 1, &(val[i].FTGtestpulse), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "FTGxmtadd", indent + 1, &(val[i].FTGxmtadd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "FTGxres", indent + 1, &(val[i].FTGxres), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "GAM", indent + 1, &(val[i].GAM), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "IRinCFH", indent + 1, &(val[i].IRinCFH), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "PSamp_derate_factor", indent + 1, &(val[i].PSamp_derate_factor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "PSasamp_derate_factor", indent + 1, &(val[i].PSasamp_derate_factor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "PSassr_derate_factor", indent + 1, &(val[i].PSassr_derate_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "PScfh_shimvol_debug", indent + 1, &(val[i].PScfh_shimvol_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "PScs_sat", indent + 1, &(val[i].PScs_sat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "PSdebugstate", indent + 1, &(val[i].PSdebugstate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "PSfield_strength", indent + 1, &(val[i].PSfield_strength), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "PSir", indent + 1, &(val[i].PSir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "PSmt", indent + 1, &(val[i].PSmt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "PSoff90", indent + 1, &(val[i].PSoff90), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "PSphasoff", indent + 1, &(val[i].PSphasoff), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "PSphasoff_mod", indent + 1, &(val[i].PSphasoff_mod), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "PSrloc", indent + 1, &(val[i].PSrloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "PSrloc_mod", indent + 1, &(val[i].PSrloc_mod), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "PSslice_ind", indent + 1, &(val[i].PSslice_ind), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "PSslice_num", indent + 1, &(val[i].PSslice_num), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "PSsr_derate_factor", indent + 1, &(val[i].PSsr_derate_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "PStest_slab", indent + 1, &(val[i].PStest_slab), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "PStloc", indent + 1, &(val[i].PStloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "PStloc_mod", indent + 1, &(val[i].PStloc_mod), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "PStrigger", indent + 1, &(val[i].PStrigger), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "PosGzssfhcomb", indent + 1, &(val[i].PosGzssfhcomb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "Posrfs5fph", indent + 1, &(val[i].Posrfs5fph), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "Posrfssf", indent + 1, &(val[i].Posrfssf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "Posrfssfh", indent + 1, &(val[i].Posrfssfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "Rf", indent + 1, &(val[i].Rf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "SAR_bodyNV_weight_lim", indent + 1, &(val[i].SAR_bodyNV_weight_lim), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "SatRelaxers", indent + 1, &(val[i].SatRelaxers), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "T1f", indent + 1, &(val[i].T1f), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "T2f", indent + 1, &(val[i].T2f), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "TG_record", indent + 1, &(val[i].TG_record), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "TGlimit", indent + 1, &(val[i].TGlimit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "TGopslthick", indent + 1, &(val[i].TGopslthick), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "TGopslthickx", indent + 1, &(val[i].TGopslthickx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "TGopslthicky", indent + 1, &(val[i].TGopslthicky), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "TGspf", indent + 1, &(val[i].TGspf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "TR_PASS", indent + 1, &(val[i].TR_PASS), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "TR_PASS3D", indent + 1, &(val[i].TR_PASS3D), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "TR_SLOP", indent + 1, &(val[i].TR_SLOP), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "XTGacq1", indent + 1, &(val[i].XTGacq1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "XTGecho1bw", indent + 1, &(val[i].XTGecho1bw), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "XTGfov", indent + 1, &(val[i].XTGfov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "XTGtau1", indent + 1, &(val[i].XTGtau1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "XTGxres", indent + 1, &(val[i].XTGxres), 1);
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "_firstcv", indent + 1, &(val[i]._firstcv), 1);
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "_lastcv", indent + 1, &(val[i]._lastcv), 1);
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "_lasttgtex", indent + 1, &(val[i]._lasttgtex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "aTEopt_flag", indent + 1, &(val[i].aTEopt_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "aTRopt_flag", indent + 1, &(val[i].aTRopt_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_base", indent + 1, &(val[i].a_base), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_base2", indent + 1, &(val[i].a_base2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_base_max", indent + 1, &(val[i].a_base_max), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_base_proj_dephaser", indent + 1, &(val[i].a_base_proj_dephaser), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_comb", indent + 1, &(val[i].a_comb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_comb2", indent + 1, &(val[i].a_comb2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_delta", indent + 1, &(val[i].a_delta), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_delta2", indent + 1, &(val[i].a_delta2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_end", indent + 1, &(val[i].a_end), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_end2", indent + 1, &(val[i].a_end2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gk", indent + 1, &(val[i].a_gk), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1", indent + 1, &(val[i].a_gx1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1_frac", indent + 1, &(val[i].a_gx1_frac), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1_full", indent + 1, &(val[i].a_gx1_full), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1a", indent + 1, &(val[i].a_gx1a), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1as", indent + 1, &(val[i].a_gx1as), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1b", indent + 1, &(val[i].a_gx1b), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1bftg", indent + 1, &(val[i].a_gx1bftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1bxtg", indent + 1, &(val[i].a_gx1bxtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1cfh", indent + 1, &(val[i].a_gx1cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1d", indent + 1, &(val[i].a_gx1d), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1d_frac", indent + 1, &(val[i].a_gx1d_frac), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1d_full", indent + 1, &(val[i].a_gx1d_full), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1dtg", indent + 1, &(val[i].a_gx1dtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1ftg", indent + 1, &(val[i].a_gx1ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1mon", indent + 1, &(val[i].a_gx1mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1mps1", indent + 1, &(val[i].a_gx1mps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1rs", indent + 1, &(val[i].a_gx1rs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1tm", indent + 1, &(val[i].a_gx1tm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1u", indent + 1, &(val[i].a_gx1u), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1u_frac", indent + 1, &(val[i].a_gx1u_frac), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx1u_full", indent + 1, &(val[i].a_gx1u_full), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx2", indent + 1, &(val[i].a_gx2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx2dtg", indent + 1, &(val[i].a_gx2dtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx2ftg", indent + 1, &(val[i].a_gx2ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx2rs", indent + 1, &(val[i].a_gx2rs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gx2test", indent + 1, &(val[i].a_gx2test), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxb", indent + 1, &(val[i].a_gxb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxbrsfc1", indent + 1, &(val[i].a_gxbrsfc1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxbrsfc2", indent + 1, &(val[i].a_gxbrsfc2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxfc", indent + 1, &(val[i].a_gxfc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxfc_frac", indent + 1, &(val[i].a_gxfc_frac), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxfc_full", indent + 1, &(val[i].a_gxfc_full), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxfcd", indent + 1, &(val[i].a_gxfcd), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxfcd_frac", indent + 1, &(val[i].a_gxfcd_frac), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxfcd_full", indent + 1, &(val[i].a_gxfcd_full), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxfcmon", indent + 1, &(val[i].a_gxfcmon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxfcu", indent + 1, &(val[i].a_gxfcu), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxfcu_frac", indent + 1, &(val[i].a_gxfcu_frac), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxfcu_full", indent + 1, &(val[i].a_gxfcu_full), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxflpk", indent + 1, &(val[i].a_gxflpk), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxflpka", indent + 1, &(val[i].a_gxflpka), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxflpkb", indent + 1, &(val[i].a_gxflpkb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxflpvenc", indent + 1, &(val[i].a_gxflpvenc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxflpvenca", indent + 1, &(val[i].a_gxflpvenca), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxflpvencb", indent + 1, &(val[i].a_gxflpvencb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxhyst1", indent + 1, &(val[i].a_gxhyst1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxhyst2", indent + 1, &(val[i].a_gxhyst2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxkas", indent + 1, &(val[i].a_gxkas), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxkbsdtg", indent + 1, &(val[i].a_gxkbsdtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxkbsrs", indent + 1, &(val[i].a_gxkbsrs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxkcs", indent + 1, &(val[i].a_gxkcs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxkdtg", indent + 1, &(val[i].a_gxkdtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxkfs", indent + 1, &(val[i].a_gxkfs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxkill", indent + 1, &(val[i].a_gxkill), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxkrcvn", indent + 1, &(val[i].a_gxkrcvn), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxkrs", indent + 1, &(val[i].a_gxkrs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxks", indent + 1, &(val[i].a_gxks), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxkse1", indent + 1, &(val[i].a_gxkse1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxkse2", indent + 1, &(val[i].a_gxkse2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxkse3", indent + 1, &(val[i].a_gxkse3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxkse4", indent + 1, &(val[i].a_gxkse4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxkse5", indent + 1, &(val[i].a_gxkse5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxkse6", indent + 1, &(val[i].a_gxkse6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxksp", indent + 1, &(val[i].a_gxksp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxkssf", indent + 1, &(val[i].a_gxkssf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxksx1", indent + 1, &(val[i].a_gxksx1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxksx2", indent + 1, &(val[i].a_gxksx2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxksy1", indent + 1, &(val[i].a_gxksy1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxksy2", indent + 1, &(val[i].a_gxksy2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxksz1", indent + 1, &(val[i].a_gxksz1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxksz2", indent + 1, &(val[i].a_gxksz2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxrf1tm", indent + 1, &(val[i].a_gxrf1tm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxrf2cfh", indent + 1, &(val[i].a_gxrf2cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxrfsx1", indent + 1, &(val[i].a_gxrfsx1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxrfsx2", indent + 1, &(val[i].a_gxrfsx2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxspiral", indent + 1, &(val[i].a_gxspiral), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxspiral2", indent + 1, &(val[i].a_gxspiral2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxspoil", indent + 1, &(val[i].a_gxspoil), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxspoil2", indent + 1, &(val[i].a_gxspoil2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxw", indent + 1, &(val[i].a_gxw), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxw1ftg", indent + 1, &(val[i].a_gxw1ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxw1xtg", indent + 1, &(val[i].a_gxw1xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxw2", indent + 1, &(val[i].a_gxw2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxw2dtg", indent + 1, &(val[i].a_gxw2dtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxw2ftg", indent + 1, &(val[i].a_gxw2ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxw2rs", indent + 1, &(val[i].a_gxw2rs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxwas", indent + 1, &(val[i].a_gxwas), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxwdtg", indent + 1, &(val[i].a_gxwdtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxwex", indent + 1, &(val[i].a_gxwex), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxwmon", indent + 1, &(val[i].a_gxwmon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxwmps1", indent + 1, &(val[i].a_gxwmps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gxwrs", indent + 1, &(val[i].a_gxwrs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1", indent + 1, &(val[i].a_gy1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1a", indent + 1, &(val[i].a_gy1a), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1as", indent + 1, &(val[i].a_gy1as), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1asa", indent + 1, &(val[i].a_gy1asa), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1asb", indent + 1, &(val[i].a_gy1asb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1b", indent + 1, &(val[i].a_gy1b), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1cfh", indent + 1, &(val[i].a_gy1cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1dtg", indent + 1, &(val[i].a_gy1dtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1dtga", indent + 1, &(val[i].a_gy1dtga), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1dtgb", indent + 1, &(val[i].a_gy1dtgb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1mon", indent + 1, &(val[i].a_gy1mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1mps1", indent + 1, &(val[i].a_gy1mps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1r", indent + 1, &(val[i].a_gy1r), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1ra", indent + 1, &(val[i].a_gy1ra), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1ras", indent + 1, &(val[i].a_gy1ras), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1rasa", indent + 1, &(val[i].a_gy1rasa), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1rasb", indent + 1, &(val[i].a_gy1rasb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1rb", indent + 1, &(val[i].a_gy1rb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1rdtg", indent + 1, &(val[i].a_gy1rdtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1rdtga", indent + 1, &(val[i].a_gy1rdtga), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1rdtgb", indent + 1, &(val[i].a_gy1rdtgb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1rrs", indent + 1, &(val[i].a_gy1rrs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1rrsa", indent + 1, &(val[i].a_gy1rrsa), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1rrsb", indent + 1, &(val[i].a_gy1rrsb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1rs", indent + 1, &(val[i].a_gy1rs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1rsa", indent + 1, &(val[i].a_gy1rsa), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1rsb", indent + 1, &(val[i].a_gy1rsb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy1tm", indent + 1, &(val[i].a_gy1tm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy2dtg", indent + 1, &(val[i].a_gy2dtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy2dtga", indent + 1, &(val[i].a_gy2dtga), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy2dtgb", indent + 1, &(val[i].a_gy2dtgb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy2rs", indent + 1, &(val[i].a_gy2rs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy2rsa", indent + 1, &(val[i].a_gy2rsa), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gy2rsb", indent + 1, &(val[i].a_gy2rsb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyb", indent + 1, &(val[i].a_gyb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gybrsfc1", indent + 1, &(val[i].a_gybrsfc1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gybrsfc2", indent + 1, &(val[i].a_gybrsfc2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gycylr", indent + 1, &(val[i].a_gycylr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gycylrtipup", indent + 1, &(val[i].a_gycylrtipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyfe", indent + 1, &(val[i].a_gyfe), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyfe1", indent + 1, &(val[i].a_gyfe1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyfe2", indent + 1, &(val[i].a_gyfe2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyflpk", indent + 1, &(val[i].a_gyflpk), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyflpka", indent + 1, &(val[i].a_gyflpka), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyflpkb", indent + 1, &(val[i].a_gyflpkb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyflpvenc", indent + 1, &(val[i].a_gyflpvenc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyflpvenca", indent + 1, &(val[i].a_gyflpvenca), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyflpvencb", indent + 1, &(val[i].a_gyflpvencb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyhyst1", indent + 1, &(val[i].a_gyhyst1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyhyst2", indent + 1, &(val[i].a_gyhyst2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gykcfh", indent + 1, &(val[i].a_gykcfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gykcfl", indent + 1, &(val[i].a_gykcfl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gykcs", indent + 1, &(val[i].a_gykcs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gykfs", indent + 1, &(val[i].a_gykfs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gykill", indent + 1, &(val[i].a_gykill), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gykrcvn", indent + 1, &(val[i].a_gykrcvn), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyks", indent + 1, &(val[i].a_gyks), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gykse1", indent + 1, &(val[i].a_gykse1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gykse2", indent + 1, &(val[i].a_gykse2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gykse3", indent + 1, &(val[i].a_gykse3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gykse4", indent + 1, &(val[i].a_gykse4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gykse5", indent + 1, &(val[i].a_gykse5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gykse6", indent + 1, &(val[i].a_gykse6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyksp", indent + 1, &(val[i].a_gyksp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gykssf", indent + 1, &(val[i].a_gykssf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyksx1", indent + 1, &(val[i].a_gyksx1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyksx2", indent + 1, &(val[i].a_gyksx2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyksy1", indent + 1, &(val[i].a_gyksy1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyksy2", indent + 1, &(val[i].a_gyksy2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyksz1", indent + 1, &(val[i].a_gyksz1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyksz2", indent + 1, &(val[i].a_gyksz2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gykxtgl", indent + 1, &(val[i].a_gykxtgl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gykxtgr", indent + 1, &(val[i].a_gykxtgr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyrf0kcfh", indent + 1, &(val[i].a_gyrf0kcfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyrf1mon", indent + 1, &(val[i].a_gyrf1mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyrf1mps1", indent + 1, &(val[i].a_gyrf1mps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyrf1tm", indent + 1, &(val[i].a_gyrf1tm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyrf1xtg", indent + 1, &(val[i].a_gyrf1xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyrf2cfh", indent + 1, &(val[i].a_gyrf2cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyrf2lmon", indent + 1, &(val[i].a_gyrf2lmon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyrf2mon", indent + 1, &(val[i].a_gyrf2mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyrf2rmon", indent + 1, &(val[i].a_gyrf2rmon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyrf3cfh", indent + 1, &(val[i].a_gyrf3cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyrfmontipup", indent + 1, &(val[i].a_gyrfmontipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyrfsy1", indent + 1, &(val[i].a_gyrfsy1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyrfsy2", indent + 1, &(val[i].a_gyrfsy2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyspiral", indent + 1, &(val[i].a_gyspiral), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyspiral2", indent + 1, &(val[i].a_gyspiral2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyspoil", indent + 1, &(val[i].a_gyspoil), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gyspoil2", indent + 1, &(val[i].a_gyspoil2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gz1", indent + 1, &(val[i].a_gz1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gz1as", indent + 1, &(val[i].a_gz1as), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gz1cfl", indent + 1, &(val[i].a_gz1cfl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gz1d", indent + 1, &(val[i].a_gz1d), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gz1dtg", indent + 1, &(val[i].a_gz1dtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gz1ftg", indent + 1, &(val[i].a_gz1ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gz1mon", indent + 1, &(val[i].a_gz1mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gz1mps1", indent + 1, &(val[i].a_gz1mps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gz1rs", indent + 1, &(val[i].a_gz1rs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gz1s", indent + 1, &(val[i].a_gz1s), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gz1u", indent + 1, &(val[i].a_gz1u), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gz1xtg", indent + 1, &(val[i].a_gz1xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gz2bftg", indent + 1, &(val[i].a_gz2bftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gz2ftg", indent + 1, &(val[i].a_gz2ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gz2xtg", indent + 1, &(val[i].a_gz2xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gz3ftg", indent + 1, &(val[i].a_gz3ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzbrsfc1", indent + 1, &(val[i].a_gzbrsfc1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzbrsfc1echo1", indent + 1, &(val[i].a_gzbrsfc1echo1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzbrsfc1echo2", indent + 1, &(val[i].a_gzbrsfc1echo2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzbrsfc2", indent + 1, &(val[i].a_gzbrsfc2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzcomb", indent + 1, &(val[i].a_gzcomb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzcomba", indent + 1, &(val[i].a_gzcomba), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzcombb", indent + 1, &(val[i].a_gzcombb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzcombhtr", indent + 1, &(val[i].a_gzcombhtr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzcombhtra", indent + 1, &(val[i].a_gzcombhtra), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzcombhtrb", indent + 1, &(val[i].a_gzcombhtrb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzcylr", indent + 1, &(val[i].a_gzcylr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzcylrtipup", indent + 1, &(val[i].a_gzcylrtipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzfc", indent + 1, &(val[i].a_gzfc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzfcbase", indent + 1, &(val[i].a_gzfcbase), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzfccomb", indent + 1, &(val[i].a_gzfccomb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzfcd", indent + 1, &(val[i].a_gzfcd), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzfcend", indent + 1, &(val[i].a_gzfcend), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzfcu", indent + 1, &(val[i].a_gzfcu), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzflpk", indent + 1, &(val[i].a_gzflpk), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzflpka", indent + 1, &(val[i].a_gzflpka), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzflpkb", indent + 1, &(val[i].a_gzflpkb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzflpvenc", indent + 1, &(val[i].a_gzflpvenc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzflpvenca", indent + 1, &(val[i].a_gzflpvenca), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzflpvencb", indent + 1, &(val[i].a_gzflpvencb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzk", indent + 1, &(val[i].a_gzk), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkas", indent + 1, &(val[i].a_gzkas), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkbase", indent + 1, &(val[i].a_gzkbase), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkbsdtg", indent + 1, &(val[i].a_gzkbsdtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkbsrs", indent + 1, &(val[i].a_gzkbsrs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkcomb", indent + 1, &(val[i].a_gzkcomb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkcs", indent + 1, &(val[i].a_gzkcs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkdtg", indent + 1, &(val[i].a_gzkdtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkend", indent + 1, &(val[i].a_gzkend), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkfs", indent + 1, &(val[i].a_gzkfs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkgir01", indent + 1, &(val[i].a_gzkgir01), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkgir02", indent + 1, &(val[i].a_gzkgir02), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkill", indent + 1, &(val[i].a_gzkill), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkiller", indent + 1, &(val[i].a_gzkiller), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkmon", indent + 1, &(val[i].a_gzkmon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkmontipup", indent + 1, &(val[i].a_gzkmontipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkrcvn", indent + 1, &(val[i].a_gzkrcvn), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkrffrir", indent + 1, &(val[i].a_gzkrffrir), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkrs", indent + 1, &(val[i].a_gzkrs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzks", indent + 1, &(val[i].a_gzks), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzks5fp", indent + 1, &(val[i].a_gzks5fp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzksp", indent + 1, &(val[i].a_gzksp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzkssf", indent + 1, &(val[i].a_gzkssf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzp", indent + 1, &(val[i].a_gzp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzpa", indent + 1, &(val[i].a_gzpa), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzpb", indent + 1, &(val[i].a_gzpb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzphtr", indent + 1, &(val[i].a_gzphtr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzphtra", indent + 1, &(val[i].a_gzphtra), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzphtrb", indent + 1, &(val[i].a_gzphtrb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzptm", indent + 1, &(val[i].a_gzptm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf0", indent + 1, &(val[i].a_gzrf0), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf0cfh", indent + 1, &(val[i].a_gzrf0cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf0k", indent + 1, &(val[i].a_gzrf0k), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf1", indent + 1, &(val[i].a_gzrf1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf1_ss_max", indent + 1, &(val[i].a_gzrf1_ss_max), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf1as", indent + 1, &(val[i].a_gzrf1as), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf1cfh", indent + 1, &(val[i].a_gzrf1cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf1cfl", indent + 1, &(val[i].a_gzrf1cfl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf1dtg", indent + 1, &(val[i].a_gzrf1dtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf1ftg", indent + 1, &(val[i].a_gzrf1ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf1htr", indent + 1, &(val[i].a_gzrf1htr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf1mon", indent + 1, &(val[i].a_gzrf1mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf1mps1", indent + 1, &(val[i].a_gzrf1mps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf1rs", indent + 1, &(val[i].a_gzrf1rs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf1s", indent + 1, &(val[i].a_gzrf1s), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf1temp", indent + 1, &(val[i].a_gzrf1temp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf1xtg", indent + 1, &(val[i].a_gzrf1xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf2ftg", indent + 1, &(val[i].a_gzrf2ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf2lcfh", indent + 1, &(val[i].a_gzrf2lcfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf2lmps1", indent + 1, &(val[i].a_gzrf2lmps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf2mps1", indent + 1, &(val[i].a_gzrf2mps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf2rcfh", indent + 1, &(val[i].a_gzrf2rcfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf2rmps1", indent + 1, &(val[i].a_gzrf2rmps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf2xtg", indent + 1, &(val[i].a_gzrf2xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf3ftg", indent + 1, &(val[i].a_gzrf3ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf3lcfh", indent + 1, &(val[i].a_gzrf3lcfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf3rcfh", indent + 1, &(val[i].a_gzrf3rcfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf4cfh", indent + 1, &(val[i].a_gzrf4cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf4lcfh", indent + 1, &(val[i].a_gzrf4lcfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrf4rcfh", indent + 1, &(val[i].a_gzrf4rcfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrffrir", indent + 1, &(val[i].a_gzrffrir), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrfgir01", indent + 1, &(val[i].a_gzrfgir01), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrfgir02", indent + 1, &(val[i].a_gzrfgir02), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrfs5fph", indent + 1, &(val[i].a_gzrfs5fph), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrfse1", indent + 1, &(val[i].a_gzrfse1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrfse2", indent + 1, &(val[i].a_gzrfse2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrfse3", indent + 1, &(val[i].a_gzrfse3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrfse4", indent + 1, &(val[i].a_gzrfse4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrfse5", indent + 1, &(val[i].a_gzrfse5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrfse6", indent + 1, &(val[i].a_gzrfse6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrfssfh", indent + 1, &(val[i].a_gzrfssfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrfsz1", indent + 1, &(val[i].a_gzrfsz1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzrfsz2", indent + 1, &(val[i].a_gzrfsz2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzs5fphcomb", indent + 1, &(val[i].a_gzs5fphcomb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzssfhcomb", indent + 1, &(val[i].a_gzssfhcomb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_gzvlw", indent + 1, &(val[i].a_gzvlw), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_hard180", indent + 1, &(val[i].a_hard180), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_hst", indent + 1, &(val[i].a_hst), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_nomcyl", indent + 1, &(val[i].a_nomcyl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_omega_hs_rfcssat", indent + 1, &(val[i].a_omega_hs_rfcssat), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_omega_ir0", indent + 1, &(val[i].a_omega_ir0), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_omega_rffrir", indent + 1, &(val[i].a_omega_rffrir), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_omega_rfgir01", indent + 1, &(val[i].a_omega_rfgir01), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_omega_rfgir02", indent + 1, &(val[i].a_omega_rfgir02), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_omegarf0cfh", indent + 1, &(val[i].a_omegarf0cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_ph180", indent + 1, &(val[i].a_ph180), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_postgxw1ftg", indent + 1, &(val[i].a_postgxw1ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf0", indent + 1, &(val[i].a_rf0), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf0cfh", indent + 1, &(val[i].a_rf0cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf1", indent + 1, &(val[i].a_rf1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf180", indent + 1, &(val[i].a_rf180), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf1as", indent + 1, &(val[i].a_rf1as), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf1cfh", indent + 1, &(val[i].a_rf1cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf1cfl", indent + 1, &(val[i].a_rf1cfl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf1dtg", indent + 1, &(val[i].a_rf1dtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf1ftg", indent + 1, &(val[i].a_rf1ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf1htr", indent + 1, &(val[i].a_rf1htr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf1mon", indent + 1, &(val[i].a_rf1mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf1mps1", indent + 1, &(val[i].a_rf1mps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf1rs", indent + 1, &(val[i].a_rf1rs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf1tm", indent + 1, &(val[i].a_rf1tm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf1xtg", indent + 1, &(val[i].a_rf1xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf2cfh", indent + 1, &(val[i].a_rf2cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf2ftg", indent + 1, &(val[i].a_rf2ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf2mon", indent + 1, &(val[i].a_rf2mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf2mps1", indent + 1, &(val[i].a_rf2mps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf2xtg", indent + 1, &(val[i].a_rf2xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf3cfh", indent + 1, &(val[i].a_rf3cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf3ftg", indent + 1, &(val[i].a_rf3ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf3xtg", indent + 1, &(val[i].a_rf3xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf4cfh", indent + 1, &(val[i].a_rf4cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf4xtg", indent + 1, &(val[i].a_rf4xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rf90", indent + 1, &(val[i].a_rf90), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfbdtg", indent + 1, &(val[i].a_rfbdtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfbrs", indent + 1, &(val[i].a_rfbrs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfcssat", indent + 1, &(val[i].a_rfcssat), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfcssatcfh", indent + 1, &(val[i].a_rfcssatcfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfcylr", indent + 1, &(val[i].a_rfcylr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfcylrtipup", indent + 1, &(val[i].a_rfcylrtipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfflp180", indent + 1, &(val[i].a_rfflp180), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfflp180_the", indent + 1, &(val[i].a_rfflp180_the), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfflp90", indent + 1, &(val[i].a_rfflp90), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfflp90_the", indent + 1, &(val[i].a_rfflp90_the), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfflp90r", indent + 1, &(val[i].a_rfflp90r), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfflp90r_the", indent + 1, &(val[i].a_rfflp90r_the), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rffrir", indent + 1, &(val[i].a_rffrir), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rffs", indent + 1, &(val[i].a_rffs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfgir01", indent + 1, &(val[i].a_rfgir01), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfgir02", indent + 1, &(val[i].a_rfgir02), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfmontipup", indent + 1, &(val[i].a_rfmontipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfs5fph", indent + 1, &(val[i].a_rfs5fph), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfse1", indent + 1, &(val[i].a_rfse1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfse2", indent + 1, &(val[i].a_rfse2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfse3", indent + 1, &(val[i].a_rfse3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfse4", indent + 1, &(val[i].a_rfse4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfse5", indent + 1, &(val[i].a_rfse5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfse6", indent + 1, &(val[i].a_rfse6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfssf", indent + 1, &(val[i].a_rfssf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfssfh", indent + 1, &(val[i].a_rfssfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfsx1", indent + 1, &(val[i].a_rfsx1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfsx2", indent + 1, &(val[i].a_rfsx2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfsy1", indent + 1, &(val[i].a_rfsy1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfsy2", indent + 1, &(val[i].a_rfsy2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfsz1", indent + 1, &(val[i].a_rfsz1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rfsz2", indent + 1, &(val[i].a_rfsz2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_rftipup", indent + 1, &(val[i].a_rftipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_sdixon", indent + 1, &(val[i].a_sdixon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_sdixon2", indent + 1, &(val[i].a_sdixon2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_thcylr", indent + 1, &(val[i].a_thcylr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_thcylrtipup", indent + 1, &(val[i].a_thcylrtipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_thetarf1", indent + 1, &(val[i].a_thetarf1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_xdixon", indent + 1, &(val[i].a_xdixon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_ydixon", indent + 1, &(val[i].a_ydixon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "a_zdixon", indent + 1, &(val[i].a_zdixon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ab1_enable", indent + 1, &(val[i].ab1_enable), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "abspower_lx", indent + 1, &(val[i].abspower_lx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "abspower_ly", indent + 1, &(val[i].abspower_ly), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "abspower_lz", indent + 1, &(val[i].abspower_lz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "abspower_px", indent + 1, &(val[i].abspower_px), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "abspower_py", indent + 1, &(val[i].abspower_py), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "abspower_pz", indent + 1, &(val[i].abspower_pz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "accel_kt_cal_stride", indent + 1, &(val[i].accel_kt_cal_stride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "accel_outer2cal_factor", indent + 1, &(val[i].accel_outer2cal_factor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "accel_ph_defstride", indent + 1, &(val[i].accel_ph_defstride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "accel_ph_stride", indent + 1, &(val[i].accel_ph_stride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "accel_phaseres", indent + 1, &(val[i].accel_phaseres), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "accel_sl_defstride", indent + 1, &(val[i].accel_sl_defstride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "accel_sl_stride", indent + 1, &(val[i].accel_sl_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "acgd_lite_target", indent + 1, &(val[i].acgd_lite_target), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "acq_data_only", indent + 1, &(val[i].acq_data_only), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "acq_type", indent + 1, &(val[i].acq_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "acqs", indent + 1, &(val[i].acqs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "acquire_type", indent + 1, &(val[i].acquire_type), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "act_aregion_fraction", indent + 1, &(val[i].act_aregion_fraction), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "act_echofrac", indent + 1, &(val[i].act_echofrac), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "act_htr", indent + 1, &(val[i].act_htr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "act_navgate_tr", indent + 1, &(val[i].act_navgate_tr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "act_scamp", indent + 1, &(val[i].act_scamp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "act_srate", indent + 1, &(val[i].act_srate), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "act_srate_x", indent + 1, &(val[i].act_srate_x), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "act_srate_y", indent + 1, &(val[i].act_srate_y), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "act_srate_z", indent + 1, &(val[i].act_srate_z), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "act_te", indent + 1, &(val[i].act_te), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "act_te2", indent + 1, &(val[i].act_te2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "act_te_cylr", indent + 1, &(val[i].act_te_cylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "act_tr", indent + 1, &(val[i].act_tr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "add_slicereadgap", indent + 1, &(val[i].add_slicereadgap), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "add_tetime", indent + 1, &(val[i].add_tetime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "adj_act_tr", indent + 1, &(val[i].adj_act_tr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "allow_ugfsf", indent + 1, &(val[i].allow_ugfsf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf0", indent + 1, &(val[i].alpha_rf0), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf0cfh", indent + 1, &(val[i].alpha_rf0cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf1", indent + 1, &(val[i].alpha_rf1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf1as", indent + 1, &(val[i].alpha_rf1as), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf1cfh", indent + 1, &(val[i].alpha_rf1cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf1cfl", indent + 1, &(val[i].alpha_rf1cfl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf1ftg", indent + 1, &(val[i].alpha_rf1ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf1mon", indent + 1, &(val[i].alpha_rf1mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf1mps1", indent + 1, &(val[i].alpha_rf1mps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf1tm", indent + 1, &(val[i].alpha_rf1tm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf1xtg", indent + 1, &(val[i].alpha_rf1xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf2cfh", indent + 1, &(val[i].alpha_rf2cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf2ftg", indent + 1, &(val[i].alpha_rf2ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf2mon", indent + 1, &(val[i].alpha_rf2mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf2mps1", indent + 1, &(val[i].alpha_rf2mps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf2xtg", indent + 1, &(val[i].alpha_rf2xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf3cfh", indent + 1, &(val[i].alpha_rf3cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf3ftg", indent + 1, &(val[i].alpha_rf3ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf3xtg", indent + 1, &(val[i].alpha_rf3xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf4cfh", indent + 1, &(val[i].alpha_rf4cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rf4xtg", indent + 1, &(val[i].alpha_rf4xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rfcssat", indent + 1, &(val[i].alpha_rfcssat), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rffrir", indent + 1, &(val[i].alpha_rffrir), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rfgir01", indent + 1, &(val[i].alpha_rfgir01), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rfgir02", indent + 1, &(val[i].alpha_rfgir02), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rfmontipup", indent + 1, &(val[i].alpha_rfmontipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rfse1", indent + 1, &(val[i].alpha_rfse1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rfse2", indent + 1, &(val[i].alpha_rfse2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rfse3", indent + 1, &(val[i].alpha_rfse3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rfse4", indent + 1, &(val[i].alpha_rfse4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rfse5", indent + 1, &(val[i].alpha_rfse5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rfse6", indent + 1, &(val[i].alpha_rfse6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rfsx1", indent + 1, &(val[i].alpha_rfsx1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rfsx2", indent + 1, &(val[i].alpha_rfsx2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rfsy1", indent + 1, &(val[i].alpha_rfsy1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rfsy2", indent + 1, &(val[i].alpha_rfsy2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rfsz1", indent + 1, &(val[i].alpha_rfsz1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "alpha_rfsz2", indent + 1, &(val[i].alpha_rfsz2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "amp_flpvenc_limit", indent + 1, &(val[i].amp_flpvenc_limit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "amp_flpvenc_max", indent + 1, &(val[i].amp_flpvenc_max), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "amptrans_lx", indent + 1, &(val[i].amptrans_lx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "amptrans_ly", indent + 1, &(val[i].amptrans_ly), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "amptrans_lz", indent + 1, &(val[i].amptrans_lz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "amptrans_px", indent + 1, &(val[i].amptrans_px), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "amptrans_py", indent + 1, &(val[i].amptrans_py), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "amptrans_pz", indent + 1, &(val[i].amptrans_pz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "anne_channel_percentage", indent + 1, &(val[i].anne_channel_percentage), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "anne_intensity_thres", indent + 1, &(val[i].anne_intensity_thres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "anne_mask_dilation_length", indent + 1, &(val[i].anne_mask_dilation_length), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "annefact_c3_recon_flag", indent + 1, &(val[i].annefact_c3_recon_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "annefact_reduction_flag", indent + 1, &(val[i].annefact_reduction_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ap_flow", indent + 1, &(val[i].ap_flow), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "aphases_max", indent + 1, &(val[i].aphases_max), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "apodize_level_flag", indent + 1, &(val[i].apodize_level_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "app_grad_type", indent + 1, &(val[i].app_grad_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "apx_compatible", indent + 1, &(val[i].apx_compatible), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "apx_cveval_counter", indent + 1, &(val[i].apx_cveval_counter), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "arc_cal_echo", indent + 1, &(val[i].arc_cal_echo), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "arc_debug_files", indent + 1, &(val[i].arc_debug_files), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "arc_equant", indent + 1, &(val[i].arc_equant), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "arc_flag", indent + 1, &(val[i].arc_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_maxnetaccel", indent + 1, &(val[i].arc_maxnetaccel), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_netaccel", indent + 1, &(val[i].arc_netaccel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "arc_pack_bam", indent + 1, &(val[i].arc_pack_bam), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "arc_ph_calwidth", indent + 1, &(val[i].arc_ph_calwidth), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "arc_ph_intaccel", indent + 1, &(val[i].arc_ph_intaccel), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_ph_maxnetaccel", indent + 1, &(val[i].arc_ph_maxnetaccel), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_ph_maxstride", indent + 1, &(val[i].arc_ph_maxstride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "arc_ph_mincalwidth", indent + 1, &(val[i].arc_ph_mincalwidth), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_ph_netaccel", indent + 1, &(val[i].arc_ph_netaccel), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_ph_reclimstride", indent + 1, &(val[i].arc_ph_reclimstride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_ph_recstride", indent + 1, &(val[i].arc_ph_recstride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_ph_stride", indent + 1, &(val[i].arc_ph_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_ph_userstride", indent + 1, &(val[i].arc_ph_userstride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_reclimnetaccel", indent + 1, &(val[i].arc_reclimnetaccel), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_recnetaccel", indent + 1, &(val[i].arc_recnetaccel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "arc_research_flag", indent + 1, &(val[i].arc_research_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "arc_sl_calwidth", indent + 1, &(val[i].arc_sl_calwidth), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "arc_sl_intaccel", indent + 1, &(val[i].arc_sl_intaccel), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_sl_maxnetaccel", indent + 1, &(val[i].arc_sl_maxnetaccel), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_sl_maxstride", indent + 1, &(val[i].arc_sl_maxstride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "arc_sl_mincalwidth", indent + 1, &(val[i].arc_sl_mincalwidth), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_sl_netaccel", indent + 1, &(val[i].arc_sl_netaccel), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_sl_reclimstride", indent + 1, &(val[i].arc_sl_reclimstride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_sl_recstride", indent + 1, &(val[i].arc_sl_recstride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_sl_stride", indent + 1, &(val[i].arc_sl_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "arc_sl_userstride", indent + 1, &(val[i].arc_sl_userstride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "arc_syn_pts", indent + 1, &(val[i].arc_syn_pts), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_de", indent + 1, &(val[i].area_de), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_flpk", indent + 1, &(val[i].area_flpk), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_flpvenc_std", indent + 1, &(val[i].area_flpvenc_std), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gx1", indent + 1, &(val[i].area_gx1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gx2", indent + 1, &(val[i].area_gx2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxfc", indent + 1, &(val[i].area_gxfc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxkcs", indent + 1, &(val[i].area_gxkcs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxkfs", indent + 1, &(val[i].area_gxkfs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxkrcvn", indent + 1, &(val[i].area_gxkrcvn), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxks", indent + 1, &(val[i].area_gxks), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxkse1", indent + 1, &(val[i].area_gxkse1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxkse2", indent + 1, &(val[i].area_gxkse2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxkse3", indent + 1, &(val[i].area_gxkse3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxkse4", indent + 1, &(val[i].area_gxkse4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxkse5", indent + 1, &(val[i].area_gxkse5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxkse6", indent + 1, &(val[i].area_gxkse6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxkssf", indent + 1, &(val[i].area_gxkssf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxksx1", indent + 1, &(val[i].area_gxksx1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxksx2", indent + 1, &(val[i].area_gxksx2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxksy1", indent + 1, &(val[i].area_gxksy1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxksy2", indent + 1, &(val[i].area_gxksy2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxksz1", indent + 1, &(val[i].area_gxksz1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxksz2", indent + 1, &(val[i].area_gxksz2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxw", indent + 1, &(val[i].area_gxw), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxwas", indent + 1, &(val[i].area_gxwas), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gxwex", indent + 1, &(val[i].area_gxwex), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gy1grad", indent + 1, &(val[i].area_gy1grad), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gy1table", indent + 1, &(val[i].area_gy1table), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gyakfs", indent + 1, &(val[i].area_gyakfs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gyakssf", indent + 1, &(val[i].area_gyakssf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gykcfh", indent + 1, &(val[i].area_gykcfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gykcfl", indent + 1, &(val[i].area_gykcfl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gykcs", indent + 1, &(val[i].area_gykcs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gykfs", indent + 1, &(val[i].area_gykfs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gykrcvn", indent + 1, &(val[i].area_gykrcvn), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gyks", indent + 1, &(val[i].area_gyks), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gykse1", indent + 1, &(val[i].area_gykse1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gykse2", indent + 1, &(val[i].area_gykse2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gykse3", indent + 1, &(val[i].area_gykse3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gykse4", indent + 1, &(val[i].area_gykse4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gykse5", indent + 1, &(val[i].area_gykse5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gykse6", indent + 1, &(val[i].area_gykse6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gykssf", indent + 1, &(val[i].area_gykssf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gyksx1", indent + 1, &(val[i].area_gyksx1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gyksx2", indent + 1, &(val[i].area_gyksx2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gyksy1", indent + 1, &(val[i].area_gyksy1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gyksy2", indent + 1, &(val[i].area_gyksy2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gyksz1", indent + 1, &(val[i].area_gyksz1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gyksz2", indent + 1, &(val[i].area_gyksz2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gz1", indent + 1, &(val[i].area_gz1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gz1as", indent + 1, &(val[i].area_gz1as), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gzfc", indent + 1, &(val[i].area_gzfc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gzk", indent + 1, &(val[i].area_gzk), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gzkcs", indent + 1, &(val[i].area_gzkcs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gzkfs", indent + 1, &(val[i].area_gzkfs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gzkgir01", indent + 1, &(val[i].area_gzkgir01), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gzkgir02", indent + 1, &(val[i].area_gzkgir02), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gzkmon", indent + 1, &(val[i].area_gzkmon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gzkmontipup", indent + 1, &(val[i].area_gzkmontipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gzkrcvn", indent + 1, &(val[i].area_gzkrcvn), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gzks", indent + 1, &(val[i].area_gzks), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gzks5fp", indent + 1, &(val[i].area_gzks5fp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gzkssf", indent + 1, &(val[i].area_gzkssf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_gzrf0k", indent + 1, &(val[i].area_gzrf0k), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_hst", indent + 1, &(val[i].area_hst), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_killerx", indent + 1, &(val[i].area_killerx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_killery", indent + 1, &(val[i].area_killery), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_killerz", indent + 1, &(val[i].area_killerz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_readrampas", indent + 1, &(val[i].area_readrampas), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_rf1", indent + 1, &(val[i].area_rf1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_rf11", indent + 1, &(val[i].area_rf11), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_rffs", indent + 1, &(val[i].area_rffs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_rfse1", indent + 1, &(val[i].area_rfse1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_rfse2", indent + 1, &(val[i].area_rfse2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_rfse3", indent + 1, &(val[i].area_rfse3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_rfse4", indent + 1, &(val[i].area_rfse4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_rfse5", indent + 1, &(val[i].area_rfse5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_rfse6", indent + 1, &(val[i].area_rfse6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_rfssf", indent + 1, &(val[i].area_rfssf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_rfssfh", indent + 1, &(val[i].area_rfssfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_rfsx1", indent + 1, &(val[i].area_rfsx1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_rfsx2", indent + 1, &(val[i].area_rfsx2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_rfsy1", indent + 1, &(val[i].area_rfsy1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_rfsy2", indent + 1, &(val[i].area_rfsy2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_rfsz1", indent + 1, &(val[i].area_rfsz1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_rfsz2", indent + 1, &(val[i].area_rfsz2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_spoilerx", indent + 1, &(val[i].area_spoilerx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_spoilery", indent + 1, &(val[i].area_spoilery), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_spoilerz", indent + 1, &(val[i].area_spoilerz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_xtgykiller", indent + 1, &(val[i].area_xtgykiller), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "area_xtgzkiller", indent + 1, &(val[i].area_xtgzkiller), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "aregion_fraction", indent + 1, &(val[i].aregion_fraction), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "arr_check", indent + 1, &(val[i].arr_check), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "as_dda", indent + 1, &(val[i].as_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "as_newgeo", indent + 1, &(val[i].as_newgeo), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "asbaseline", indent + 1, &(val[i].asbaseline), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "asflip", indent + 1, &(val[i].asflip), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "asfov", indent + 1, &(val[i].asfov), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "aslenap", indent + 1, &(val[i].aslenap), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "aslenrl", indent + 1, &(val[i].aslenrl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "aslensi", indent + 1, &(val[i].aslensi), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "aslocap", indent + 1, &(val[i].aslocap), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "aslocrl", indent + 1, &(val[i].aslocrl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "aslocsi", indent + 1, &(val[i].aslocsi), 1);
#endif
#ifdef SIZEOF_LOG_GRAD
    print_brsfc_LOG_GRAD(fp, "asloggrd", indent + 1, &(val[i].asloggrd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "asobl_debug", indent + 1, &(val[i].asobl_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "aspir_fa_scaling_flag", indent + 1, &(val[i].aspir_fa_scaling_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "aspir_flag", indent + 1, &(val[i].aspir_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "aspir_override", indent + 1, &(val[i].aspir_override), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "asptsize", indent + 1, &(val[i].asptsize), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "asrhblank", indent + 1, &(val[i].asrhblank), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "asset_factor", indent + 1, &(val[i].asset_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "asset_supported_direction", indent + 1, &(val[i].asset_supported_direction), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "assetph_flag", indent + 1, &(val[i].assetph_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "assetsl_factor", indent + 1, &(val[i].assetsl_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "assetsl_flag", indent + 1, &(val[i].assetsl_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "assetsl_min_opvthick", indent + 1, &(val[i].assetsl_min_opvthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "asslquant", indent + 1, &(val[i].asslquant), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "asslthick", indent + 1, &(val[i].asslthick), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "asx_killer_area", indent + 1, &(val[i].asx_killer_area), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "asxres", indent + 1, &(val[i].asxres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "asymmatrix", indent + 1, &(val[i].asymmatrix), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "asyres", indent + 1, &(val[i].asyres), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "asz_killer_area", indent + 1, &(val[i].asz_killer_area), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "attenlen", indent + 1, &(val[i].attenlen), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "attenlength", indent + 1, &(val[i].attenlength), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "audible_loop", indent + 1, &(val[i].audible_loop), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "autoadvtoscn", indent + 1, &(val[i].autoadvtoscn), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "autocal_mode", indent + 1, &(val[i].autocal_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "autolock", indent + 1, &(val[i].autolock), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "autoparams_debug", indent + 1, &(val[i].autoparams_debug), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avail_RRtime", indent + 1, &(val[i].avail_RRtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avail_image_time", indent + 1, &(val[i].avail_image_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avail_pwgx1as", indent + 1, &(val[i].avail_pwgx1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avail_pwgz1as", indent + 1, &(val[i].avail_pwgz1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avail_temp", indent + 1, &(val[i].avail_temp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ave_grady_gy1_scale", indent + 1, &(val[i].ave_grady_gy1_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ave_gradz_gzcomb_scale", indent + 1, &(val[i].ave_gradz_gzcomb_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ave_gradz_gzp_scale", indent + 1, &(val[i].ave_gradz_gzp_scale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avecrushpepowscale_for_SBM_XFD", indent + 1, &(val[i].avecrushpepowscale_for_SBM_XFD), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmax_dda", indent + 1, &(val[i].avmax_dda), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxaccel_cs_stride", indent + 1, &(val[i].avmaxaccel_cs_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxaccel_kt_stride", indent + 1, &(val[i].avmaxaccel_kt_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxaccel_mb_stride", indent + 1, &(val[i].avmaxaccel_mb_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxaccel_ph_stride", indent + 1, &(val[i].avmaxaccel_ph_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxaccel_sl_stride", indent + 1, &(val[i].avmaxaccel_sl_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxaccel_t_stride", indent + 1, &(val[i].avmaxaccel_t_stride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxacqs", indent + 1, &(val[i].avmaxacqs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxallowedrescantime", indent + 1, &(val[i].avmaxallowedrescantime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxaphases", indent + 1, &(val[i].avmaxaphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxbspti", indent + 1, &(val[i].avmaxbspti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxbval", indent + 1, &(val[i].avmaxbval), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxbvalstab", indent + 1, &(val[i].avmaxbvalstab), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxdifnext2", indent + 1, &(val[i].avmaxdifnext2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxdifnextab", indent + 1, &(val[i].avmaxdifnextab), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxetl", indent + 1, &(val[i].avmaxetl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxflip", indent + 1, &(val[i].avmaxflip), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxfov", indent + 1, &(val[i].avmaxfov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxfphases", indent + 1, &(val[i].avmaxfphases), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxnavaccwin", indent + 1, &(val[i].avmaxnavaccwin), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxnavautotrigtime", indent + 1, &(val[i].avmaxnavautotrigtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxnavmaxinterval", indent + 1, &(val[i].avmaxnavmaxinterval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxnavpsctime", indent + 1, &(val[i].avmaxnavpsctime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxnavrrmeastime", indent + 1, &(val[i].avmaxnavrrmeastime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxnecho", indent + 1, &(val[i].avmaxnecho), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxnex", indent + 1, &(val[i].avmaxnex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxnseg", indent + 1, &(val[i].avmaxnseg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxnshots", indent + 1, &(val[i].avmaxnshots), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxnspokes", indent + 1, &(val[i].avmaxnspokes), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxnumbvals", indent + 1, &(val[i].avmaxnumbvals), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxnumsynbvals", indent + 1, &(val[i].avmaxnumsynbvals), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxoversamplingfactor", indent + 1, &(val[i].avmaxoversamplingfactor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxovl", indent + 1, &(val[i].avmaxovl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxphasefov", indent + 1, &(val[i].avmaxphasefov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxphases", indent + 1, &(val[i].avmaxphases), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxphassetfac", indent + 1, &(val[i].avmaxphassetfac), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxrbw", indent + 1, &(val[i].avmaxrbw), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxrbw2", indent + 1, &(val[i].avmaxrbw2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxrbw_system", indent + 1, &(val[i].avmaxrbw_system), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxrep_active", indent + 1, &(val[i].avmaxrep_active), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxrep_rest", indent + 1, &(val[i].avmaxrep_rest), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxslassetfac", indent + 1, &(val[i].avmaxslassetfac), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxsldelay", indent + 1, &(val[i].avmaxsldelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxslicecnt", indent + 1, &(val[i].avmaxslicecnt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxslquant", indent + 1, &(val[i].avmaxslquant), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxslspace", indent + 1, &(val[i].avmaxslspace), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxslthick", indent + 1, &(val[i].avmaxslthick), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxsynbvalstab", indent + 1, &(val[i].avmaxsynbvalstab), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxt2prepte", indent + 1, &(val[i].avmaxt2prepte), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxtdel1", indent + 1, &(val[i].avmaxtdel1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxte", indent + 1, &(val[i].avmaxte), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxte2", indent + 1, &(val[i].avmaxte2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxti", indent + 1, &(val[i].avmaxti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxtissuet1", indent + 1, &(val[i].avmaxtissuet1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxtlabel", indent + 1, &(val[i].avmaxtlabel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxtouchamp", indent + 1, &(val[i].avmaxtouchamp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxtouchcyc", indent + 1, &(val[i].avmaxtouchcyc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxtouchfreq", indent + 1, &(val[i].avmaxtouchfreq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxtouchmegfreq", indent + 1, &(val[i].avmaxtouchmegfreq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxtouchtphases", indent + 1, &(val[i].avmaxtouchtphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxtphases", indent + 1, &(val[i].avmaxtphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxtr", indent + 1, &(val[i].avmaxtr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxtrecovery", indent + 1, &(val[i].avmaxtrecovery), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxtricksdel", indent + 1, &(val[i].avmaxtricksdel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxtseq", indent + 1, &(val[i].avmaxtseq), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxvenc", indent + 1, &(val[i].avmaxvenc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmaxvest", indent + 1, &(val[i].avmaxvest), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxvquant", indent + 1, &(val[i].avmaxvquant), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxvsphases", indent + 1, &(val[i].avmaxvsphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxxres", indent + 1, &(val[i].avmaxxres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmaxyres", indent + 1, &(val[i].avmaxyres), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmin_dda", indent + 1, &(val[i].avmin_dda), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminaccel_cs_stride", indent + 1, &(val[i].avminaccel_cs_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminaccel_kt_stride", indent + 1, &(val[i].avminaccel_kt_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminaccel_mb_stride", indent + 1, &(val[i].avminaccel_mb_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminaccel_ph_stride", indent + 1, &(val[i].avminaccel_ph_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminaccel_sl_stride", indent + 1, &(val[i].avminaccel_sl_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminaccel_t_stride", indent + 1, &(val[i].avminaccel_t_stride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminallowedrescantime", indent + 1, &(val[i].avminallowedrescantime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminaphases", indent + 1, &(val[i].avminaphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminbspti", indent + 1, &(val[i].avminbspti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminbval", indent + 1, &(val[i].avminbval), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminbvalstab", indent + 1, &(val[i].avminbvalstab), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmindifnext2", indent + 1, &(val[i].avmindifnext2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmindifnextab", indent + 1, &(val[i].avmindifnextab), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmindphases", indent + 1, &(val[i].avmindphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminetl", indent + 1, &(val[i].avminetl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminflip", indent + 1, &(val[i].avminflip), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminfov", indent + 1, &(val[i].avminfov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminfphases", indent + 1, &(val[i].avminfphases), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminnavaccwin", indent + 1, &(val[i].avminnavaccwin), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminnavautotrigtime", indent + 1, &(val[i].avminnavautotrigtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminnavmaxinterval", indent + 1, &(val[i].avminnavmaxinterval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminnavpsctime", indent + 1, &(val[i].avminnavpsctime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminnavrrmeastime", indent + 1, &(val[i].avminnavrrmeastime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminnecho", indent + 1, &(val[i].avminnecho), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminnex", indent + 1, &(val[i].avminnex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminnseg", indent + 1, &(val[i].avminnseg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminnshots", indent + 1, &(val[i].avminnshots), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminnspokes", indent + 1, &(val[i].avminnspokes), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminnumbvals", indent + 1, &(val[i].avminnumbvals), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminnumsynbvals", indent + 1, &(val[i].avminnumsynbvals), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminoversamplingfactor", indent + 1, &(val[i].avminoversamplingfactor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminphasefov", indent + 1, &(val[i].avminphasefov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminphases", indent + 1, &(val[i].avminphases), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminphassetfac", indent + 1, &(val[i].avminphassetfac), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminrbw", indent + 1, &(val[i].avminrbw), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminrbw2", indent + 1, &(val[i].avminrbw2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminrep_active", indent + 1, &(val[i].avminrep_active), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminrep_rest", indent + 1, &(val[i].avminrep_rest), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminrttseq", indent + 1, &(val[i].avminrttseq), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminslassetfac", indent + 1, &(val[i].avminslassetfac), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminsldelay", indent + 1, &(val[i].avminsldelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminslicecnt", indent + 1, &(val[i].avminslicecnt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminslquant", indent + 1, &(val[i].avminslquant), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminslspace", indent + 1, &(val[i].avminslspace), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminslthick", indent + 1, &(val[i].avminslthick), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminsynbvalstab", indent + 1, &(val[i].avminsynbvalstab), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmint2prepte", indent + 1, &(val[i].avmint2prepte), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmintdel1", indent + 1, &(val[i].avmintdel1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminte", indent + 1, &(val[i].avminte), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminte2", indent + 1, &(val[i].avminte2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminti", indent + 1, &(val[i].avminti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmintissuet1", indent + 1, &(val[i].avmintissuet1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmintlabel", indent + 1, &(val[i].avmintlabel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmintouchamp", indent + 1, &(val[i].avmintouchamp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmintouchcyc", indent + 1, &(val[i].avmintouchcyc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmintouchfreq", indent + 1, &(val[i].avmintouchfreq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmintouchmegfreq", indent + 1, &(val[i].avmintouchmegfreq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmintouchtphases", indent + 1, &(val[i].avmintouchtphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmintphases", indent + 1, &(val[i].avmintphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmintr", indent + 1, &(val[i].avmintr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmintrecovery", indent + 1, &(val[i].avmintrecovery), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmintricksdel", indent + 1, &(val[i].avmintricksdel), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avmintscan", indent + 1, &(val[i].avmintscan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avmintseq", indent + 1, &(val[i].avmintseq), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminvenc", indent + 1, &(val[i].avminvenc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "avminvest", indent + 1, &(val[i].avminvest), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminvsphases", indent + 1, &(val[i].avminvsphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminxres", indent + 1, &(val[i].avminxres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avminyres", indent + 1, &(val[i].avminyres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "avround", indent + 1, &(val[i].avround), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "b1derate_flag", indent + 1, &(val[i].b1derate_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "b1max_scale", indent + 1, &(val[i].b1max_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "b_value_3in1", indent + 1, &(val[i].b_value_3in1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "b_value_single", indent + 1, &(val[i].b_value_single), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "balanced_FE", indent + 1, &(val[i].balanced_FE), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "baseline", indent + 1, &(val[i].baseline), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "bd_index", indent + 1, &(val[i].bd_index), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "bf_rfscale", indent + 1, &(val[i].bf_rfscale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "blank", indent + 1, &(val[i].blank), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brava_flag", indent + 1, &(val[i].brava_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "bravo_fatsat", indent + 1, &(val[i].bravo_fatsat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "bravo_flag", indent + 1, &(val[i].bravo_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "break_flag", indent + 1, &(val[i].break_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "breastCoil_flag", indent + 1, &(val[i].breastCoil_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "breast_spsp_flag", indent + 1, &(val[i].breast_spsp_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "bridge_gxw2_gxwex_3dde", indent + 1, &(val[i].bridge_gxw2_gxwex_3dde), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_2d_fiesta_rf_flag", indent + 1, &(val[i].brs_2d_fiesta_rf_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_2dflag", indent + 1, &(val[i].brs_2dflag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_alpha", indent + 1, &(val[i].brs_alpha), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_alpha_center", indent + 1, &(val[i].brs_alpha_center), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_areamode", indent + 1, &(val[i].brs_areamode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_blipflag", indent + 1, &(val[i].brs_blipflag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_daqdel", indent + 1, &(val[i].brs_daqdel), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_daqdeloff", indent + 1, &(val[i].brs_daqdeloff), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_daqdeloff_zoom", indent + 1, &(val[i].brs_daqdeloff_zoom), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_ddahbs", indent + 1, &(val[i].brs_ddahbs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_debug_vieword", indent + 1, &(val[i].brs_debug_vieword), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_dofracz", indent + 1, &(val[i].brs_dofracz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_echo_wait", indent + 1, &(val[i].brs_echo_wait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_excite_grad", indent + 1, &(val[i].brs_excite_grad), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_exno", indent + 1, &(val[i].brs_exno), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_extra_esp", indent + 1, &(val[i].brs_extra_esp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_extra_len", indent + 1, &(val[i].brs_extra_len), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_extrawait", indent + 1, &(val[i].brs_extrawait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_fast_rec_lpf", indent + 1, &(val[i].brs_fast_rec_lpf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_filtdel", indent + 1, &(val[i].brs_filtdel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_flex", indent + 1, &(val[i].brs_flex), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_fov0", indent + 1, &(val[i].brs_fov0), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_fov1", indent + 1, &(val[i].brs_fov1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_fov2", indent + 1, &(val[i].brs_fov2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_fovpow", indent + 1, &(val[i].brs_fovpow), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_fracz_fact", indent + 1, &(val[i].brs_fracz_fact), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_fs_slice", indent + 1, &(val[i].brs_fs_slice), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_fsprep_flag", indent + 1, &(val[i].brs_fsprep_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_fw_te_step", indent + 1, &(val[i].brs_fw_te_step), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_fwflag", indent + 1, &(val[i].brs_fwflag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_gateddas", indent + 1, &(val[i].brs_gateddas), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_gmax", indent + 1, &(val[i].brs_gmax), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_grad_derate", indent + 1, &(val[i].brs_grad_derate), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_grad_powscale", indent + 1, &(val[i].brs_grad_powscale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_gradlen", indent + 1, &(val[i].brs_gradlen), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_gradlen2", indent + 1, &(val[i].brs_gradlen2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_gslew", indent + 1, &(val[i].brs_gslew), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_gzvl_area_base", indent + 1, &(val[i].brs_gzvl_area_base), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_gzvl_delte", indent + 1, &(val[i].brs_gzvl_delte), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_gzvl_flag", indent + 1, &(val[i].brs_gzvl_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_leafgroup", indent + 1, &(val[i].brs_leafgroup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_leaflen", indent + 1, &(val[i].brs_leaflen), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_leafskip", indent + 1, &(val[i].brs_leafskip), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_m1null", indent + 1, &(val[i].brs_m1null), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_mapdel", indent + 1, &(val[i].brs_mapdel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_mapdel_act", indent + 1, &(val[i].brs_mapdel_act), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_matrixsize_center", indent + 1, &(val[i].brs_matrixsize_center), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_me_flag", indent + 1, &(val[i].brs_me_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_mfa_flag", indent + 1, &(val[i].brs_mfa_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_mfa_num", indent + 1, &(val[i].brs_mfa_num), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_mfa_schedule", indent + 1, &(val[i].brs_mfa_schedule), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_min_esp", indent + 1, &(val[i].brs_min_esp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_mra_flag", indent + 1, &(val[i].brs_mra_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_nfolds", indent + 1, &(val[i].brs_nfolds), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_nphases", indent + 1, &(val[i].brs_nphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_numleaves", indent + 1, &(val[i].brs_numleaves), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_numleaves_acq", indent + 1, &(val[i].brs_numleaves_acq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_opti", indent + 1, &(val[i].brs_opti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_pm_numleaves", indent + 1, &(val[i].brs_pm_numleaves), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_pm_type", indent + 1, &(val[i].brs_pm_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_preirdel", indent + 1, &(val[i].brs_preirdel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_psc", indent + 1, &(val[i].brs_psc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_psc_prot_no", indent + 1, &(val[i].brs_psc_prot_no), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_psc_use_tracker", indent + 1, &(val[i].brs_psc_use_tracker), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_ramplength", indent + 1, &(val[i].brs_ramplength), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_ramplength2", indent + 1, &(val[i].brs_ramplength2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_readoutdelay", indent + 1, &(val[i].brs_readoutdelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_realtime", indent + 1, &(val[i].brs_realtime), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_recratio", indent + 1, &(val[i].brs_recratio), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_rhrecon", indent + 1, &(val[i].brs_rhrecon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_rscale", indent + 1, &(val[i].brs_rscale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_rspskp", indent + 1, &(val[i].brs_rspskp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_s5fp", indent + 1, &(val[i].brs_s5fp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_sampfact", indent + 1, &(val[i].brs_sampfact), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_sampfact_center", indent + 1, &(val[i].brs_sampfact_center), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_scantype", indent + 1, &(val[i].brs_scantype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_shim_flag", indent + 1, &(val[i].brs_shim_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_shim_update_type", indent + 1, &(val[i].brs_shim_update_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_shim_x", indent + 1, &(val[i].brs_shim_x), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_shim_y", indent + 1, &(val[i].brs_shim_y), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_shim_z", indent + 1, &(val[i].brs_shim_z), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_slewmax", indent + 1, &(val[i].brs_slewmax), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_ssfp_flag", indent + 1, &(val[i].brs_ssfp_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_type", indent + 1, &(val[i].brs_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_use_min_seqgrad", indent + 1, &(val[i].brs_use_min_seqgrad), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_vieword", indent + 1, &(val[i].brs_vieword), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_viewstocenter", indent + 1, &(val[i].brs_viewstocenter), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_xarea", indent + 1, &(val[i].brs_xarea), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_xarea2", indent + 1, &(val[i].brs_xarea2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_xbliparea", indent + 1, &(val[i].brs_xbliparea), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_xtarget", indent + 1, &(val[i].brs_xtarget), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_xx", indent + 1, &(val[i].brs_xx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_xy", indent + 1, &(val[i].brs_xy), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_yarea", indent + 1, &(val[i].brs_yarea), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_yarea2", indent + 1, &(val[i].brs_yarea2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_ybliparea", indent + 1, &(val[i].brs_ybliparea), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_ytarget", indent + 1, &(val[i].brs_ytarget), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_yx", indent + 1, &(val[i].brs_yx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_yy", indent + 1, &(val[i].brs_yy), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_zarea", indent + 1, &(val[i].brs_zarea), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_zseg", indent + 1, &(val[i].brs_zseg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_ztarget", indent + 1, &(val[i].brs_ztarget), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_zvps", indent + 1, &(val[i].brs_zvps), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brsfc_flag", indent + 1, &(val[i].brsfc_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brsfc_longfc", indent + 1, &(val[i].brsfc_longfc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brsfmx", indent + 1, &(val[i].brsfmx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brsfmy", indent + 1, &(val[i].brsfmy), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brsfmz", indent + 1, &(val[i].brsfmz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "btemp_debug", indent + 1, &(val[i].btemp_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "btemp_monitor", indent + 1, &(val[i].btemp_monitor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "burstreps", indent + 1, &(val[i].burstreps), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "bw_rf0", indent + 1, &(val[i].bw_rf0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "bw_rf1", indent + 1, &(val[i].bw_rf1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "bw_rf1as", indent + 1, &(val[i].bw_rf1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "bw_rf1mon", indent + 1, &(val[i].bw_rf1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "bw_rf2mon", indent + 1, &(val[i].bw_rf2mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "bw_rffrir", indent + 1, &(val[i].bw_rffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "bw_rfgir01", indent + 1, &(val[i].bw_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "bw_rfgir02", indent + 1, &(val[i].bw_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "bw_rfmontipup", indent + 1, &(val[i].bw_rfmontipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "bw_rfssfh", indent + 1, &(val[i].bw_rfssfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cal3d_flag", indent + 1, &(val[i].cal3d_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cal3d_interleave", indent + 1, &(val[i].cal3d_interleave), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cal3d_nex1", indent + 1, &(val[i].cal3d_nex1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cal3d_nex2", indent + 1, &(val[i].cal3d_nex2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cal3d_nex3", indent + 1, &(val[i].cal3d_nex3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cal3d_nex_mode", indent + 1, &(val[i].cal3d_nex_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cal3d_pass_set", indent + 1, &(val[i].cal3d_pass_set), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cal3d_pause_step", indent + 1, &(val[i].cal3d_pause_step), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cal3d_phases", indent + 1, &(val[i].cal3d_phases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cal3d_state", indent + 1, &(val[i].cal3d_state), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cal3d_state1", indent + 1, &(val[i].cal3d_state1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cal3d_state2", indent + 1, &(val[i].cal3d_state2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cal3d_state3", indent + 1, &(val[i].cal3d_state3), 1);
#endif
#ifdef SIZEOF_CAL_PARAM
    print_brsfc_CAL_PARAM(fp, "calRegion", indent + 1, &(val[i].calRegion), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cal_ky_ktarc", indent + 1, &(val[i].cal_ky_ktarc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cal_kz_ktarc", indent + 1, &(val[i].cal_kz_ktarc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cal_shape", indent + 1, &(val[i].cal_shape), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "calc_rate", indent + 1, &(val[i].calc_rate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "calibrationPoints", indent + 1, &(val[i].calibrationPoints), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ccs_dead", indent + 1, &(val[i].ccs_dead), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ccs_relaxers", indent + 1, &(val[i].ccs_relaxers), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ccs_relaxseqtime", indent + 1, &(val[i].ccs_relaxseqtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ccs_relaxtime", indent + 1, &(val[i].ccs_relaxtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "centric_flag", indent + 1, &(val[i].centric_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cerdtype", indent + 1, &(val[i].cerdtype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfBbTransmitSelect", indent + 1, &(val[i].cfBbTransmitSelect), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfDualDriveCapable", indent + 1, &(val[i].cfDualDriveCapable), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfEllipticDriveEnable", indent + 1, &(val[i].cfEllipticDriveEnable), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfMnsConverterSelect", indent + 1, &(val[i].cfMnsConverterSelect), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfNbTransmitSelect", indent + 1, &(val[i].cfNbTransmitSelect), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfOptimalSnrRecon", indent + 1, &(val[i].cfOptimalSnrRecon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfVirtualChannelRecon", indent + 1, &(val[i].cfVirtualChannelRecon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfaccel_cs_maxstride", indent + 1, &(val[i].cfaccel_cs_maxstride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfaccel_ph_maxstride", indent + 1, &(val[i].cfaccel_ph_maxstride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfaccel_sl_maxstride", indent + 1, &(val[i].cfaccel_sl_maxstride), 1);
#endif
#ifdef SIZEOF_n64
    print_brsfc_n64(fp, "cfacqtodisksize", indent + 1, &(val[i].cfacqtodisksize), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfbbmod", indent + 1, &(val[i].cfbbmod), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfbdcabletglimit", indent + 1, &(val[i].cfbdcabletglimit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfbllr", indent + 1, &(val[i].cfbllr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfbpdl", indent + 1, &(val[i].cfbpdl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfbpsl", indent + 1, &(val[i].cfbpsl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfbpv", indent + 1, &(val[i].cfbpv), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfbqpc", indent + 1, &(val[i].cfbqpc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfbwmin", indent + 1, &(val[i].cfbwmin), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfbwmin1", indent + 1, &(val[i].cfbwmin1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfcablebw", indent + 1, &(val[i].cfcablebw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfcablefreq", indent + 1, &(val[i].cfcablefreq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfcabletg", indent + 1, &(val[i].cfcabletg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfcarddelay", indent + 1, &(val[i].cfcarddelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfcerdtype", indent + 1, &(val[i].cfcerdtype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfcftdel", indent + 1, &(val[i].cfcftdel), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcgain", indent + 1, &(val[i].cfcgain), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_RxA", indent + 1, &(val[i].cfcoilAC_RxA), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_RxB", indent + 1, &(val[i].cfcoilAC_RxB), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_RxC", indent + 1, &(val[i].cfcoilAC_RxC), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_RyA", indent + 1, &(val[i].cfcoilAC_RyA), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_RyB", indent + 1, &(val[i].cfcoilAC_RyB), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_RyC", indent + 1, &(val[i].cfcoilAC_RyC), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_RzA", indent + 1, &(val[i].cfcoilAC_RzA), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_RzB", indent + 1, &(val[i].cfcoilAC_RzB), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_RzC", indent + 1, &(val[i].cfcoilAC_RzC), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfcoilAC_fftpoints", indent + 1, &(val[i].cfcoilAC_fftpoints), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_gain", indent + 1, &(val[i].cfcoilAC_gain), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_lumpL2x", indent + 1, &(val[i].cfcoilAC_lumpL2x), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_lumpL2y", indent + 1, &(val[i].cfcoilAC_lumpL2y), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_lumpL2z", indent + 1, &(val[i].cfcoilAC_lumpL2z), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_lumpL4x", indent + 1, &(val[i].cfcoilAC_lumpL4x), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_lumpL4y", indent + 1, &(val[i].cfcoilAC_lumpL4y), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_lumpL4z", indent + 1, &(val[i].cfcoilAC_lumpL4z), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_lumpR1x", indent + 1, &(val[i].cfcoilAC_lumpR1x), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_lumpR1y", indent + 1, &(val[i].cfcoilAC_lumpR1y), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_lumpR1z", indent + 1, &(val[i].cfcoilAC_lumpR1z), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_lumpR3x", indent + 1, &(val[i].cfcoilAC_lumpR3x), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_lumpR3y", indent + 1, &(val[i].cfcoilAC_lumpR3y), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_lumpR3z", indent + 1, &(val[i].cfcoilAC_lumpR3z), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_lumpR5x", indent + 1, &(val[i].cfcoilAC_lumpR5x), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_lumpR5y", indent + 1, &(val[i].cfcoilAC_lumpR5y), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_lumpR5z", indent + 1, &(val[i].cfcoilAC_lumpR5z), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_power", indent + 1, &(val[i].cfcoilAC_power), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_power_1axis", indent + 1, &(val[i].cfcoilAC_power_1axis), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_power_burst", indent + 1, &(val[i].cfcoilAC_power_burst), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_temp_base_burst", indent + 1, &(val[i].cfcoilAC_temp_base_burst), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_temp_limit_burst", indent + 1, &(val[i].cfcoilAC_temp_limit_burst), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_timeconstant_burst", indent + 1, &(val[i].cfcoilAC_timeconstant_burst), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_timeres", indent + 1, &(val[i].cfcoilAC_timeres), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_xgain", indent + 1, &(val[i].cfcoilAC_xgain), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_ygain", indent + 1, &(val[i].cfcoilAC_ygain), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilAC_zgain", indent + 1, &(val[i].cfcoilAC_zgain), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilDC_Lx", indent + 1, &(val[i].cfcoilDC_Lx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilDC_Ly", indent + 1, &(val[i].cfcoilDC_Ly), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilDC_Lz", indent + 1, &(val[i].cfcoilDC_Lz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilDC_Rx", indent + 1, &(val[i].cfcoilDC_Rx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilDC_Ry", indent + 1, &(val[i].cfcoilDC_Ry), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilDC_Rz", indent + 1, &(val[i].cfcoilDC_Rz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilDC_gain", indent + 1, &(val[i].cfcoilDC_gain), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilQAC_A0", indent + 1, &(val[i].cfcoilQAC_A0), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilQAC_A1", indent + 1, &(val[i].cfcoilQAC_A1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilQAC_A2", indent + 1, &(val[i].cfcoilQAC_A2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilQAC_A3", indent + 1, &(val[i].cfcoilQAC_A3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilQAC_A4", indent + 1, &(val[i].cfcoilQAC_A4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilQAC_A5", indent + 1, &(val[i].cfcoilQAC_A5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilQAC_A6", indent + 1, &(val[i].cfcoilQAC_A6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilQAC_Xcoef", indent + 1, &(val[i].cfcoilQAC_Xcoef), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilQAC_Ycoef", indent + 1, &(val[i].cfcoilQAC_Ycoef), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilQAC_Zcoef", indent + 1, &(val[i].cfcoilQAC_Zcoef), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilQAC_const", indent + 1, &(val[i].cfcoilQAC_const), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilQAC_heat_const", indent + 1, &(val[i].cfcoilQAC_heat_const), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilQAC_heat_maxtime", indent + 1, &(val[i].cfcoilQAC_heat_maxtime), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilQAC_heat_slope", indent + 1, &(val[i].cfcoilQAC_heat_slope), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfcoilQAC_maxtime", indent + 1, &(val[i].cfcoilQAC_maxtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfcoilshld", indent + 1, &(val[i].cfcoilshld), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfcoilswitchmethod", indent + 1, &(val[i].cfcoilswitchmethod), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfcompress", indent + 1, &(val[i].cfcompress), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfdbdtdx", indent + 1, &(val[i].cfdbdtdx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfdbdtdy", indent + 1, &(val[i].cfdbdtdy), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfdbdtdz", indent + 1, &(val[i].cfdbdtdz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfdbdtper", indent + 1, &(val[i].cfdbdtper), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfdbdtper2", indent + 1, &(val[i].cfdbdtper2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfdbdtper_cont", indent + 1, &(val[i].cfdbdtper_cont), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfdbdtper_max", indent + 1, &(val[i].cfdbdtper_max), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfdbdtper_norm", indent + 1, &(val[i].cfdbdtper_norm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfdbdtts", indent + 1, &(val[i].cfdbdtts), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfdbdttype", indent + 1, &(val[i].cfdbdttype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfdbmax", indent + 1, &(val[i].cfdbmax), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfderatingFactorRTSAR", indent + 1, &(val[i].cfderatingFactorRTSAR), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfdfm", indent + 1, &(val[i].cfdfm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfdfmDX", indent + 1, &(val[i].cfdfmDX), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfdfmR1", indent + 1, &(val[i].cfdfmR1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfdfmTG", indent + 1, &(val[i].cfdfmTG), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfdppericn", indent + 1, &(val[i].cfdppericn), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cffall2x0", indent + 1, &(val[i].cffall2x0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cffall2x0fw", indent + 1, &(val[i].cffall2x0fw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cffall2y0", indent + 1, &(val[i].cffall2y0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cffall2y0fw", indent + 1, &(val[i].cffall2y0fw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cffall2z0", indent + 1, &(val[i].cffall2z0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cffall2z0fw", indent + 1, &(val[i].cffall2z0fw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cffastprescan", indent + 1, &(val[i].cffastprescan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cffield", indent + 1, &(val[i].cffield), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfgburstime", indent + 1, &(val[i].cfgburstime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfgcoiltype", indent + 1, &(val[i].cfgcoiltype), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfgcontirms", indent + 1, &(val[i].cfgcontirms), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfgmax_arthigh", indent + 1, &(val[i].cfgmax_arthigh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfgmax_artmedium", indent + 1, &(val[i].cfgmax_artmedium), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfgmax_artmediumopt", indent + 1, &(val[i].cfgmax_artmediumopt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfgovbody", indent + 1, &(val[i].cfgovbody), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfgpeakirms", indent + 1, &(val[i].cfgpeakirms), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfgpmpow", indent + 1, &(val[i].cfgpmpow), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfgradamp", indent + 1, &(val[i].cfgradamp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfgradcoil", indent + 1, &(val[i].cfgradcoil), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfh_crusher_area", indent + 1, &(val[i].cfh_crusher_area), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfh_dda", indent + 1, &(val[i].cfh_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfh_each", indent + 1, &(val[i].cfh_each), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfh_ec_position", indent + 1, &(val[i].cfh_ec_position), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfh_fov", indent + 1, &(val[i].cfh_fov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfh_newgeo", indent + 1, &(val[i].cfh_newgeo), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfh_newmode", indent + 1, &(val[i].cfh_newmode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfh_nex", indent + 1, &(val[i].cfh_nex), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfh_rf1freq", indent + 1, &(val[i].cfh_rf1freq), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfh_rf2freq", indent + 1, &(val[i].cfh_rf2freq), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfh_rf3freq", indent + 1, &(val[i].cfh_rf3freq), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfh_rf4freq", indent + 1, &(val[i].cfh_rf4freq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfh_slquant", indent + 1, &(val[i].cfh_slquant), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfh_steam_flag", indent + 1, &(val[i].cfh_steam_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfh_tdaq", indent + 1, &(val[i].cfh_tdaq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfh_ti", indent + 1, &(val[i].cfh_ti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfh_tr", indent + 1, &(val[i].cfh_tr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfhir_killer_area", indent + 1, &(val[i].cfhir_killer_area), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfhllr", indent + 1, &(val[i].cfhllr), 1);
#endif
#ifdef SIZEOF_LOG_GRAD
    print_brsfc_LOG_GRAD(fp, "cfhloggrd", indent + 1, &(val[i].cfhloggrd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfhobl_debug", indent + 1, &(val[i].cfhobl_debug), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfhpdl", indent + 1, &(val[i].cfhpdl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfhpsl", indent + 1, &(val[i].cfhpsl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfhpv", indent + 1, &(val[i].cfhpv), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfhqpc", indent + 1, &(val[i].cfhqpc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfhscale", indent + 1, &(val[i].cfhscale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfhtdel", indent + 1, &(val[i].cfhtdel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfhwgut", indent + 1, &(val[i].cfhwgut), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfhwrfut", indent + 1, &(val[i].cfhwrfut), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfhwssput", indent + 1, &(val[i].cfhwssput), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfl_dda", indent + 1, &(val[i].cfl_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfl_nex", indent + 1, &(val[i].cfl_nex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfl_tdaq", indent + 1, &(val[i].cfl_tdaq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfl_tr", indent + 1, &(val[i].cfl_tr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cflcoil", indent + 1, &(val[i].cflcoil), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cflinfrq", indent + 1, &(val[i].cflinfrq), 1);
#endif
#ifdef SIZEOF_LOG_GRAD
    print_brsfc_LOG_GRAD(fp, "cflloggrd", indent + 1, &(val[i].cflloggrd), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfloss", indent + 1, &(val[i].cfloss), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cflscale", indent + 1, &(val[i].cflscale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfmaxave", indent + 1, &(val[i].cfmaxave), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfmaxavepm", indent + 1, &(val[i].cfmaxavepm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfmaxb1ref", indent + 1, &(val[i].cfmaxb1ref), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfmaxb1rmshead", indent + 1, &(val[i].cfmaxb1rmshead), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfmaxbw", indent + 1, &(val[i].cfmaxbw), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfmaxcave", indent + 1, &(val[i].cfmaxcave), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfmaxcpeak", indent + 1, &(val[i].cfmaxcpeak), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfmaxepeak", indent + 1, &(val[i].cfmaxepeak), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfmaxextremity", indent + 1, &(val[i].cfmaxextremity), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfmaxhave", indent + 1, &(val[i].cfmaxhave), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfmaxpeak", indent + 1, &(val[i].cfmaxpeak), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfmgps", indent + 1, &(val[i].cfmgps), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfnumartlevels", indent + 1, &(val[i].cfnumartlevels), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfnumicn", indent + 1, &(val[i].cfnumicn), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfnumrcvrs", indent + 1, &(val[i].cfnumrcvrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfopenmagnet", indent + 1, &(val[i].cfopenmagnet), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfoption", indent + 1, &(val[i].cfoption), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfpicture", indent + 1, &(val[i].cfpicture), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfpmgs", indent + 1, &(val[i].cfpmgs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfpsdgraddly", indent + 1, &(val[i].cfpsdgraddly), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfpsdrfdly", indent + 1, &(val[i].cfpsdrfdly), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfpsdrfdlyx", indent + 1, &(val[i].cfpsdrfdlyx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfpsdrfdlyy", indent + 1, &(val[i].cfpsdrfdlyy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfpsdrfdlyz", indent + 1, &(val[i].cfpsdrfdlyz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfpure_filtering_mode", indent + 1, &(val[i].cfpure_filtering_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfpwrmonreflmeas", indent + 1, &(val[i].cfpwrmonreflmeas), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfpwrmontyp", indent + 1, &(val[i].cfpwrmontyp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfraccoil", indent + 1, &(val[i].cfraccoil), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cframpdir", indent + 1, &(val[i].cframpdir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cframpdir_tgt", indent + 1, &(val[i].cframpdir_tgt), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfrcoil", indent + 1, &(val[i].cfrcoil), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrealtime", indent + 1, &(val[i].cfrealtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfreceiveroffsetfreq", indent + 1, &(val[i].cfreceiveroffsetfreq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfreceiverswitchtype", indent + 1, &(val[i].cfreceiverswitchtype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfreceivertype", indent + 1, &(val[i].cfreceivertype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrecvend", indent + 1, &(val[i].cfrecvend), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrecvst", indent + 1, &(val[i].cfrecvst), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfMaxAttenuation", indent + 1, &(val[i].cfrfMaxAttenuation), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfact", indent + 1, &(val[i].cfrfact), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfrfampftconst", indent + 1, &(val[i].cfrfampftconst), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfrfampftlinear", indent + 1, &(val[i].cfrfampftlinear), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfrfampftquadratic", indent + 1, &(val[i].cfrfampftquadratic), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfamptyp", indent + 1, &(val[i].cfrfamptyp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfboardtype", indent + 1, &(val[i].cfrfboardtype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfmapb", indent + 1, &(val[i].cfrfmapb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfmaph", indent + 1, &(val[i].cfrfmaph), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfmaps", indent + 1, &(val[i].cfrfmaps), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfrfmdcb", indent + 1, &(val[i].cfrfmdcb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfrfmdch", indent + 1, &(val[i].cfrfmdch), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfrfmdcs", indent + 1, &(val[i].cfrfmdcs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfminblank", indent + 1, &(val[i].cfrfminblank), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfminblanktorcv", indent + 1, &(val[i].cfrfminblanktorcv), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfminunblk", indent + 1, &(val[i].cfrfminunblk), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfrfmpeb", indent + 1, &(val[i].cfrfmpeb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfrfmpeh", indent + 1, &(val[i].cfrfmpeh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfrfmpes", indent + 1, &(val[i].cfrfmpes), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfmpwb", indent + 1, &(val[i].cfrfmpwb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfmpwh", indent + 1, &(val[i].cfrfmpwh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfmpws", indent + 1, &(val[i].cfrfmpws), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfrapb", indent + 1, &(val[i].cfrfrapb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfrapcw", indent + 1, &(val[i].cfrfrapcw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfraph", indent + 1, &(val[i].cfrfraph), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfraps", indent + 1, &(val[i].cfrfraps), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfunblank", indent + 1, &(val[i].cfrfunblank), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfupa", indent + 1, &(val[i].cfrfupa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrfupd", indent + 1, &(val[i].cfrfupd), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfrhr", indent + 1, &(val[i].cfrhr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfrinf", indent + 1, &(val[i].cfrinf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrmp2xfs", indent + 1, &(val[i].cfrmp2xfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrmp2xfsfw", indent + 1, &(val[i].cfrmp2xfsfw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrmp2yfs", indent + 1, &(val[i].cfrmp2yfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrmp2yfsfw", indent + 1, &(val[i].cfrmp2yfsfw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrmp2zfs", indent + 1, &(val[i].cfrmp2zfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfrmp2zfsfw", indent + 1, &(val[i].cfrmp2zfsfw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfscoutscanact", indent + 1, &(val[i].cfscoutscanact), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfsdlim", indent + 1, &(val[i].cfsdlim), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfslew_arthigh", indent + 1, &(val[i].cfslew_arthigh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfslew_artmedium", indent + 1, &(val[i].cfslew_artmedium), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfslew_artmediumopt", indent + 1, &(val[i].cfslew_artmediumopt), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfspectroPMcal", indent + 1, &(val[i].cfspectroPMcal), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfsrmode", indent + 1, &(val[i].cfsrmode), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfsrmodeact", indent + 1, &(val[i].cfsrmodeact), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfsrmodeconv", indent + 1, &(val[i].cfsrmodeconv), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfswgut", indent + 1, &(val[i].cfswgut), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfswrfut", indent + 1, &(val[i].cfswrfut), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfswssput", indent + 1, &(val[i].cfswssput), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfsystemmaxfov", indent + 1, &(val[i].cfsystemmaxfov), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cftableanglex", indent + 1, &(val[i].cftableanglex), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cftableangley", indent + 1, &(val[i].cftableangley), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cftableanglez", indent + 1, &(val[i].cftableanglez), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cftablemaxaccel", indent + 1, &(val[i].cftablemaxaccel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cftablemaxdecel", indent + 1, &(val[i].cftablemaxdecel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cftablemaxspeed", indent + 1, &(val[i].cftablemaxspeed), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cftableoffsetx", indent + 1, &(val[i].cftableoffsetx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cftableoffsety", indent + 1, &(val[i].cftableoffsety), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cftableoffsetz", indent + 1, &(val[i].cftableoffsetz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cftpsnproc", indent + 1, &(val[i].cftpsnproc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cftpsproctype", indent + 1, &(val[i].cftpsproctype), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cftpssize", indent + 1, &(val[i].cftpssize), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cftrnew", indent + 1, &(val[i].cftrnew), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cftuning", indent + 1, &(val[i].cftuning), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfvhr", indent + 1, &(val[i].cfvhr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxamptran", indent + 1, &(val[i].cfxamptran), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfxasm", indent + 1, &(val[i].cfxasm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxbeta", indent + 1, &(val[i].cfxbeta), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxcc", indent + 1, &(val[i].cfxcc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxfa", indent + 1, &(val[i].cfxfa), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxfd_power_limit", indent + 1, &(val[i].cfxfd_power_limit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxfd_temp_limit", indent + 1, &(val[i].cfxfd_temp_limit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxfs", indent + 1, &(val[i].cfxfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfxfull", indent + 1, &(val[i].cfxfull), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfxgasm", indent + 1, &(val[i].cfxgasm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxgd_IGBTtemplimit", indent + 1, &(val[i].cfxgd_IGBTtemplimit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxgd_busbartemplimit", indent + 1, &(val[i].cfxgd_busbartemplimit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxgd_cableirmslimit", indent + 1, &(val[i].cfxgd_cableirmslimit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxgd_cableirmslimit_burst", indent + 1, &(val[i].cfxgd_cableirmslimit_burst), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxgd_cabletimeconstant_burst", indent + 1, &(val[i].cfxgd_cabletimeconstant_burst), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxgd_chokepowerlimit", indent + 1, &(val[i].cfxgd_chokepowerlimit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxgd_timeres", indent + 1, &(val[i].cfxgd_timeres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfxgram", indent + 1, &(val[i].cfxgram), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxiavrgabs", indent + 1, &(val[i].cfxiavrgabs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxipeak", indent + 1, &(val[i].cfxipeak), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxirms", indent + 1, &(val[i].cfxirms), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxirmsneg", indent + 1, &(val[i].cfxirmsneg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxirmspos", indent + 1, &(val[i].cfxirmspos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxmgrampow", indent + 1, &(val[i].cfxmgrampow), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfxnumpower", indent + 1, &(val[i].cfxnumpower), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxps_avghvpwrlimit", indent + 1, &(val[i].cfxps_avghvpwrlimit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxps_avglvpwrlimit", indent + 1, &(val[i].cfxps_avglvpwrlimit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxps_avgpdulimit", indent + 1, &(val[i].cfxps_avgpdulimit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxpwmdc", indent + 1, &(val[i].cfxpwmdc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfxrdelay", indent + 1, &(val[i].cfxrdelay), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxrsat", indent + 1, &(val[i].cfxrsat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfxseries", indent + 1, &(val[i].cfxseries), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxvpwm", indent + 1, &(val[i].cfxvpwm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfxvsat", indent + 1, &(val[i].cfxvsat), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfyamptran", indent + 1, &(val[i].cfyamptran), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfyasm", indent + 1, &(val[i].cfyasm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfybeta", indent + 1, &(val[i].cfybeta), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfycc", indent + 1, &(val[i].cfycc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfyfa", indent + 1, &(val[i].cfyfa), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfyfs", indent + 1, &(val[i].cfyfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfyfull", indent + 1, &(val[i].cfyfull), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfygasm", indent + 1, &(val[i].cfygasm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfygram", indent + 1, &(val[i].cfygram), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfyiavrgabs", indent + 1, &(val[i].cfyiavrgabs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfyipeak", indent + 1, &(val[i].cfyipeak), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfyirms", indent + 1, &(val[i].cfyirms), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfyirmsneg", indent + 1, &(val[i].cfyirmsneg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfyirmspos", indent + 1, &(val[i].cfyirmspos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfymgrampow", indent + 1, &(val[i].cfymgrampow), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfynumpower", indent + 1, &(val[i].cfynumpower), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfypwmdc", indent + 1, &(val[i].cfypwmdc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfyrdelay", indent + 1, &(val[i].cfyrdelay), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfyrsat", indent + 1, &(val[i].cfyrsat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfyseries", indent + 1, &(val[i].cfyseries), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfyvpwm", indent + 1, &(val[i].cfyvpwm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfyvsat", indent + 1, &(val[i].cfyvsat), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfzamptran", indent + 1, &(val[i].cfzamptran), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfzasm", indent + 1, &(val[i].cfzasm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfzbeta", indent + 1, &(val[i].cfzbeta), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfzcc", indent + 1, &(val[i].cfzcc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfzfa", indent + 1, &(val[i].cfzfa), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfzfs", indent + 1, &(val[i].cfzfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfzfull", indent + 1, &(val[i].cfzfull), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfzgasm", indent + 1, &(val[i].cfzgasm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfzgram", indent + 1, &(val[i].cfzgram), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfziavrgabs", indent + 1, &(val[i].cfziavrgabs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfzipeak", indent + 1, &(val[i].cfzipeak), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfzirms", indent + 1, &(val[i].cfzirms), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfzirmsneg", indent + 1, &(val[i].cfzirmsneg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfzirmspos", indent + 1, &(val[i].cfzirmspos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfzmgrampow", indent + 1, &(val[i].cfzmgrampow), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfznumpower", indent + 1, &(val[i].cfznumpower), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfzoomlim_ctl", indent + 1, &(val[i].cfzoomlim_ctl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfzoomlim_fov", indent + 1, &(val[i].cfzoomlim_fov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfzoomlim_ofc", indent + 1, &(val[i].cfzoomlim_ofc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfzpwmdc", indent + 1, &(val[i].cfzpwmdc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfzrdelay", indent + 1, &(val[i].cfzrdelay), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfzrsat", indent + 1, &(val[i].cfzrsat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cfzseries", indent + 1, &(val[i].cfzseries), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfzvpwm", indent + 1, &(val[i].cfzvpwm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cfzvsat", indent + 1, &(val[i].cfzvsat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cgate_dda", indent + 1, &(val[i].cgate_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "channel_combine_mode", indent + 1, &(val[i].channel_combine_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "channel_compression", indent + 1, &(val[i].channel_compression), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "chemfreq", indent + 1, &(val[i].chemfreq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "chemsat_acq", indent + 1, &(val[i].chemsat_acq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "chemsat_dda", indent + 1, &(val[i].chemsat_dda), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "chemscale", indent + 1, &(val[i].chemscale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "chemseq0", indent + 1, &(val[i].chemseq0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "chemseqs", indent + 1, &(val[i].chemseqs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "chksum_rampdir", indent + 1, &(val[i].chksum_rampdir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "chksum_rampdir_tgt", indent + 1, &(val[i].chksum_rampdir_tgt), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "chksum_rhdacqctrl", indent + 1, &(val[i].chksum_rhdacqctrl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "chksum_rhdacqctrl_view", indent + 1, &(val[i].chksum_rhdacqctrl_view), 1);
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "chksum_scaninfo", indent + 1, &(val[i].chksum_scaninfo), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "chksum_scaninfo_view", indent + 1, &(val[i].chksum_scaninfo_view), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "choplet", indent + 1, &(val[i].choplet), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cine3d_arrlimit", indent + 1, &(val[i].cine3d_arrlimit), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cine3d_flag", indent + 1, &(val[i].cine3d_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cine3d_fullkviews", indent + 1, &(val[i].cine3d_fullkviews), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cine3d_fullkviews_cal", indent + 1, &(val[i].cine3d_fullkviews_cal), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cine3d_ktsamp_mode", indent + 1, &(val[i].cine3d_ktsamp_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cine3d_maxslquant", indent + 1, &(val[i].cine3d_maxslquant), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cine3d_minslquant", indent + 1, &(val[i].cine3d_minslquant), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cine3d_num_segs_est", indent + 1, &(val[i].cine3d_num_segs_est), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cine3d_targetedphases_max", indent + 1, &(val[i].cine3d_targetedphases_max), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cine3d_totalviews_est", indent + 1, &(val[i].cine3d_totalviews_est), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cine3d_yz_order", indent + 1, &(val[i].cine3d_yz_order), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cine_choplet", indent + 1, &(val[i].cine_choplet), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cinv16_iso_delay", indent + 1, &(val[i].cinv16_iso_delay), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "coeff_pw_tg", indent + 1, &(val[i].coeff_pw_tg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "coil_map_2_filter_width", indent + 1, &(val[i].coil_map_2_filter_width), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "coil_map_smooth_factor", indent + 1, &(val[i].coil_map_smooth_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "coilsw_data", indent + 1, &(val[i].coilsw_data), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "coilsw_ds", indent + 1, &(val[i].coilsw_ds), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "coilsw_oc", indent + 1, &(val[i].coilsw_oc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "coll_prefls", indent + 1, &(val[i].coll_prefls), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "combined_coil_map_thres", indent + 1, &(val[i].combined_coil_map_thres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "combo_mode", indent + 1, &(val[i].combo_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "compositeon", indent + 1, &(val[i].compositeon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "comptipupon", indent + 1, &(val[i].comptipupon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "config_update_mode", indent + 1, &(val[i].config_update_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cont_debug", indent + 1, &(val[i].cont_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cont_flag", indent + 1, &(val[i].cont_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "corr_factor_x", indent + 1, &(val[i].corr_factor_x), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "corr_factor_y", indent + 1, &(val[i].corr_factor_y), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "corr_factor_z", indent + 1, &(val[i].corr_factor_z), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "corr_mode", indent + 1, &(val[i].corr_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "corr_x", indent + 1, &(val[i].corr_x), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "corr_y", indent + 1, &(val[i].corr_y), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "corr_z", indent + 1, &(val[i].corr_z), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "count_grd_wait", indent + 1, &(val[i].count_grd_wait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "count_rfupd", indent + 1, &(val[i].count_rfupd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cs_flag", indent + 1, &(val[i].cs_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cs_sat", indent + 1, &(val[i].cs_sat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cs_satstart", indent + 1, &(val[i].cs_satstart), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cs_satstart_min", indent + 1, &(val[i].cs_satstart_min), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cs_sattime", indent + 1, &(val[i].cs_sattime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "csat_rfupa", indent + 1, &(val[i].csat_rfupa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "csat_sys_type", indent + 1, &(val[i].csat_sys_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "csi_grid_on", indent + 1, &(val[i].csi_grid_on), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "csw_time_ssi", indent + 1, &(val[i].csw_time_ssi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "csw_tr", indent + 1, &(val[i].csw_tr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "csw_wait_before", indent + 1, &(val[i].csw_wait_before), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "csw_wait_sethubindeximm", indent + 1, &(val[i].csw_wait_sethubindeximm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "csw_wait_setrcvportimm", indent + 1, &(val[i].csw_wait_setrcvportimm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "csweight", indent + 1, &(val[i].csweight), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "csxkillerFlag", indent + 1, &(val[i].csxkillerFlag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cszkillerFlag", indent + 1, &(val[i].cszkillerFlag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "curr_eff", indent + 1, &(val[i].curr_eff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cutcorner_flag", indent + 1, &(val[i].cutcorner_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cutpostlobes", indent + 1, &(val[i].cutpostlobes), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cv_rfupa", indent + 1, &(val[i].cv_rfupa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cvlock", indent + 1, &(val[i].cvlock), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf0", indent + 1, &(val[i].cyc_rf0), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf0cfh", indent + 1, &(val[i].cyc_rf0cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf1", indent + 1, &(val[i].cyc_rf1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf1_pre", indent + 1, &(val[i].cyc_rf1_pre), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf1_temp", indent + 1, &(val[i].cyc_rf1_temp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf1as", indent + 1, &(val[i].cyc_rf1as), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf1cfh", indent + 1, &(val[i].cyc_rf1cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf1cfl", indent + 1, &(val[i].cyc_rf1cfl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf1dtg", indent + 1, &(val[i].cyc_rf1dtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf1ftg", indent + 1, &(val[i].cyc_rf1ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf1htr", indent + 1, &(val[i].cyc_rf1htr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf1mon", indent + 1, &(val[i].cyc_rf1mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf1mps1", indent + 1, &(val[i].cyc_rf1mps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf1rs", indent + 1, &(val[i].cyc_rf1rs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf1tm", indent + 1, &(val[i].cyc_rf1tm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf1xtg", indent + 1, &(val[i].cyc_rf1xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf2", indent + 1, &(val[i].cyc_rf2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf2cfh", indent + 1, &(val[i].cyc_rf2cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf2ftg", indent + 1, &(val[i].cyc_rf2ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf2mon", indent + 1, &(val[i].cyc_rf2mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf2mps1", indent + 1, &(val[i].cyc_rf2mps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf2xtg", indent + 1, &(val[i].cyc_rf2xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf3cfh", indent + 1, &(val[i].cyc_rf3cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf3ftg", indent + 1, &(val[i].cyc_rf3ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rf4cfh", indent + 1, &(val[i].cyc_rf4cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rfcssat", indent + 1, &(val[i].cyc_rfcssat), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rffrir", indent + 1, &(val[i].cyc_rffrir), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rfgir01", indent + 1, &(val[i].cyc_rfgir01), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rfgir02", indent + 1, &(val[i].cyc_rfgir02), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rfmontipup", indent + 1, &(val[i].cyc_rfmontipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rfs", indent + 1, &(val[i].cyc_rfs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rfse1", indent + 1, &(val[i].cyc_rfse1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rfse2", indent + 1, &(val[i].cyc_rfse2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rfse3", indent + 1, &(val[i].cyc_rfse3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rfse4", indent + 1, &(val[i].cyc_rfse4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rfse5", indent + 1, &(val[i].cyc_rfse5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rfse6", indent + 1, &(val[i].cyc_rfse6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rfsx1", indent + 1, &(val[i].cyc_rfsx1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rfsx2", indent + 1, &(val[i].cyc_rfsx2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rfsy1", indent + 1, &(val[i].cyc_rfsy1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rfsy2", indent + 1, &(val[i].cyc_rfsy2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rfsz1", indent + 1, &(val[i].cyc_rfsz1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cyc_rfsz2", indent + 1, &(val[i].cyc_rfsz2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cylr_dtheta", indent + 1, &(val[i].cylr_dtheta), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cylr_manoff", indent + 1, &(val[i].cylr_manoff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cylr_rf_type", indent + 1, &(val[i].cylr_rf_type), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cylr_skew", indent + 1, &(val[i].cylr_skew), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cylr_xoff", indent + 1, &(val[i].cylr_xoff), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "cylr_yoff", indent + 1, &(val[i].cylr_yoff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "d3dtr", indent + 1, &(val[i].d3dtr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dab_offset", indent + 1, &(val[i].dab_offset), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dab_packet", indent + 1, &(val[i].dab_packet), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dabout_length", indent + 1, &(val[i].dabout_length), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "data_type", indent + 1, &(val[i].data_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dbdt_debug", indent + 1, &(val[i].dbdt_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dbdt_disable", indent + 1, &(val[i].dbdt_disable), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dbdt_mode", indent + 1, &(val[i].dbdt_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dbdt_option_key_status", indent + 1, &(val[i].dbdt_option_key_status), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dbdtlevel_opt", indent + 1, &(val[i].dbdtlevel_opt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dda", indent + 1, &(val[i].dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dda_delay", indent + 1, &(val[i].dda_delay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dda_one_second", indent + 1, &(val[i].dda_one_second), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dda_trigger_delay_disdaqs", indent + 1, &(val[i].dda_trigger_delay_disdaqs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dda_trigger_delay_silent_countdown", indent + 1, &(val[i].dda_trigger_delay_silent_countdown), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "de3d_flag", indent + 1, &(val[i].de3d_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "debug", indent + 1, &(val[i].debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "debug_card_sim", indent + 1, &(val[i].debug_card_sim), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "debug_dbdt", indent + 1, &(val[i].debug_dbdt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "debug_gir", indent + 1, &(val[i].debug_gir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "debug_grad_spec", indent + 1, &(val[i].debug_grad_spec), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "debug_monloc", indent + 1, &(val[i].debug_monloc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "debug_monrot", indent + 1, &(val[i].debug_monrot), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "debug_monrotphi", indent + 1, &(val[i].debug_monrotphi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "debug_nav", indent + 1, &(val[i].debug_nav), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "debug_order", indent + 1, &(val[i].debug_order), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "debug_scale", indent + 1, &(val[i].debug_scale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "debug_scan", indent + 1, &(val[i].debug_scan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "debug_shimvol_slice", indent + 1, &(val[i].debug_shimvol_slice), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "debug_sp_agp", indent + 1, &(val[i].debug_sp_agp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "debug_sp_rtp", indent + 1, &(val[i].debug_sp_rtp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "debug_tdel", indent + 1, &(val[i].debug_tdel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "debug_viewtab", indent + 1, &(val[i].debug_viewtab), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "decimation", indent + 1, &(val[i].decimation), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "delay3Drecon_flag", indent + 1, &(val[i].delay3Drecon_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "delay_dda", indent + 1, &(val[i].delay_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "delay_ec_flag", indent + 1, &(val[i].delay_ec_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "delay_ec_frames", indent + 1, &(val[i].delay_ec_frames), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "delay_ec_period", indent + 1, &(val[i].delay_ec_period), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "delay_quiet_dda", indent + 1, &(val[i].delay_quiet_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "delay_quiet_time", indent + 1, &(val[i].delay_quiet_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "delay_rfhubsel", indent + 1, &(val[i].delay_rfhubsel), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "deltf", indent + 1, &(val[i].deltf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "derate_ACGD", indent + 1, &(val[i].derate_ACGD), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "derate_gxwex", indent + 1, &(val[i].derate_gxwex), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "derateb1_NV_factor", indent + 1, &(val[i].derateb1_NV_factor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "derateb1_body_factor", indent + 1, &(val[i].derateb1_body_factor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "derateb1_default", indent + 1, &(val[i].derateb1_default), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "derateb1_dir", indent + 1, &(val[i].derateb1_dir), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "derateb1_min", indent + 1, &(val[i].derateb1_min), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "derateb1_noniteropt", indent + 1, &(val[i].derateb1_noniteropt), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "derateb1_opt", indent + 1, &(val[i].derateb1_opt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "detector_mode", indent + 1, &(val[i].detector_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dex", indent + 1, &(val[i].dex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "df", indent + 1, &(val[i].df), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "dfg", indent + 1, &(val[i].dfg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "dfscale", indent + 1, &(val[i].dfscale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "disable_exciter_unblank", indent + 1, &(val[i].disable_exciter_unblank), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "disco_1echo_flag", indent + 1, &(val[i].disco_1echo_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "disco_flag", indent + 1, &(val[i].disco_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "disco_nphases", indent + 1, &(val[i].disco_nphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "discodda", indent + 1, &(val[i].discodda), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "discretionaryB1rms", indent + 1, &(val[i].discretionaryB1rms), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "discretionaryPeakB1", indent + 1, &(val[i].discretionaryPeakB1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "discretionaryave", indent + 1, &(val[i].discretionaryave), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "discretionaryhave", indent + 1, &(val[i].discretionaryhave), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dither_on", indent + 1, &(val[i].dither_on), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dither_value", indent + 1, &(val[i].dither_value), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "dix_freq", indent + 1, &(val[i].dix_freq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dix_timeas", indent + 1, &(val[i].dix_timeas), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "dnav_win_BAratio", indent + 1, &(val[i].dnav_win_BAratio), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "do_maxrbw_check_in_cveval", indent + 1, &(val[i].do_maxrbw_check_in_cveval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dobaselines", indent + 1, &(val[i].dobaselines), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dtg_dda", indent + 1, &(val[i].dtg_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dtg_esp", indent + 1, &(val[i].dtg_esp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dtg_iso_delay", indent + 1, &(val[i].dtg_iso_delay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dtg_off90", indent + 1, &(val[i].dtg_off90), 1);
#endif
#ifdef SIZEOF_LOG_GRAD
    print_brsfc_LOG_GRAD(fp, "dtgloggrd", indent + 1, &(val[i].dtgloggrd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dtgphorder", indent + 1, &(val[i].dtgphorder), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dtgspgr_flag", indent + 1, &(val[i].dtgspgr_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dtgt_exa", indent + 1, &(val[i].dtgt_exa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dtgt_exb", indent + 1, &(val[i].dtgt_exb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dti_plus_flag", indent + 1, &(val[i].dti_plus_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dummy_pw", indent + 1, &(val[i].dummy_pw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dummyrf_ssitime", indent + 1, &(val[i].dummyrf_ssitime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dummyrf_time", indent + 1, &(val[i].dummyrf_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dump_channel_comp_optimal_recon", indent + 1, &(val[i].dump_channel_comp_optimal_recon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "dutycycle_scale", indent + 1, &(val[i].dutycycle_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "dynTG_b1factor", indent + 1, &(val[i].dynTG_b1factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dynTG_baseline", indent + 1, &(val[i].dynTG_baseline), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dynTG_etl", indent + 1, &(val[i].dynTG_etl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "dynTG_flipangle", indent + 1, &(val[i].dynTG_flipangle), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "dynTG_fov", indent + 1, &(val[i].dynTG_fov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dynTG_ptsize", indent + 1, &(val[i].dynTG_ptsize), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dynTG_slquant", indent + 1, &(val[i].dynTG_slquant), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "dynTG_slthick", indent + 1, &(val[i].dynTG_slthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dynTG_xres", indent + 1, &(val[i].dynTG_xres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "dynTG_yres", indent + 1, &(val[i].dynTG_yres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "e2_delay_dtg", indent + 1, &(val[i].e2_delay_dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "e2_delay_rs", indent + 1, &(val[i].e2_delay_rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ec3_iteration_method", indent + 1, &(val[i].ec3_iteration_method), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ec3_iterations", indent + 1, &(val[i].ec3_iterations), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ecg_cont_dda_flag", indent + 1, &(val[i].ecg_cont_dda_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ecg_dda", indent + 1, &(val[i].ecg_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ecg_dda_delay", indent + 1, &(val[i].ecg_dda_delay), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "echo1bw", indent + 1, &(val[i].echo1bw), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "echo1bwas", indent + 1, &(val[i].echo1bwas), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "echo1bwcfh", indent + 1, &(val[i].echo1bwcfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "echo1bwcfl", indent + 1, &(val[i].echo1bwcfl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "echo1bwdtg", indent + 1, &(val[i].echo1bwdtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "echo1bwrcvn", indent + 1, &(val[i].echo1bwrcvn), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "echo1bwrs", indent + 1, &(val[i].echo1bwrs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "echo1monbw", indent + 1, &(val[i].echo1monbw), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "echo2bw", indent + 1, &(val[i].echo2bw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "echo_sort_dir", indent + 1, &(val[i].echo_sort_dir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "echoint", indent + 1, &(val[i].echoint), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "eeff", indent + 1, &(val[i].eeff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "eepf", indent + 1, &(val[i].eepf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "eff_cfh_te", indent + 1, &(val[i].eff_cfh_te), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "eg_phaseres", indent + 1, &(val[i].eg_phaseres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "elava_flag", indent + 1, &(val[i].elava_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ellipt_debug_files", indent + 1, &(val[i].ellipt_debug_files), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ellipt_flag", indent + 1, &(val[i].ellipt_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "enable_alpha", indent + 1, &(val[i].enable_alpha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "enable_sbm", indent + 1, &(val[i].enable_sbm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "enablfracdec", indent + 1, &(val[i].enablfracdec), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "encode", indent + 1, &(val[i].encode), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "encode2", indent + 1, &(val[i].encode2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "encode_group", indent + 1, &(val[i].encode_group), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "end_gycylra", indent + 1, &(val[i].end_gycylra), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "end_gycylratipup", indent + 1, &(val[i].end_gycylratipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "end_gzcylra", indent + 1, &(val[i].end_gzcylra), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "end_gzcylratipup", indent + 1, &(val[i].end_gzcylratipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "end_segment_delay", indent + 1, &(val[i].end_segment_delay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "endview_iamp", indent + 1, &(val[i].endview_iamp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "endview_iampas", indent + 1, &(val[i].endview_iampas), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "endview_iampdtg", indent + 1, &(val[i].endview_iampdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "endview_iamprs", indent + 1, &(val[i].endview_iamprs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "endview_scale", indent + 1, &(val[i].endview_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "endview_scaleas", indent + 1, &(val[i].endview_scaleas), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "endview_scaledtg", indent + 1, &(val[i].endview_scaledtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "endview_scalers", indent + 1, &(val[i].endview_scalers), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "endviewz_iamp", indent + 1, &(val[i].endviewz_iamp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "endviewz_scale", indent + 1, &(val[i].endviewz_scale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "enforce_cal_for_channel_combine", indent + 1, &(val[i].enforce_cal_for_channel_combine), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "enforce_dbdtopt", indent + 1, &(val[i].enforce_dbdtopt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "enforce_inrangetr", indent + 1, &(val[i].enforce_inrangetr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "enforce_minseqseg", indent + 1, &(val[i].enforce_minseqseg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "enhanced_nav_flag", indent + 1, &(val[i].enhanced_nav_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "epi_ir_on", indent + 1, &(val[i].epi_ir_on), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "equant", indent + 1, &(val[i].equant), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "esp", indent + 1, &(val[i].esp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "esp_msde", indent + 1, &(val[i].esp_msde), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ethick", indent + 1, &(val[i].ethick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "exnex", indent + 1, &(val[i].exnex), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat1_dist", indent + 1, &(val[i].exsat1_dist), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat1_normth_A", indent + 1, &(val[i].exsat1_normth_A), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat1_normth_R", indent + 1, &(val[i].exsat1_normth_R), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat1_normth_S", indent + 1, &(val[i].exsat1_normth_S), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat2_dist", indent + 1, &(val[i].exsat2_dist), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat2_normth_A", indent + 1, &(val[i].exsat2_normth_A), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat2_normth_R", indent + 1, &(val[i].exsat2_normth_R), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat2_normth_S", indent + 1, &(val[i].exsat2_normth_S), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat3_dist", indent + 1, &(val[i].exsat3_dist), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat3_normth_A", indent + 1, &(val[i].exsat3_normth_A), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat3_normth_R", indent + 1, &(val[i].exsat3_normth_R), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat3_normth_S", indent + 1, &(val[i].exsat3_normth_S), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat4_dist", indent + 1, &(val[i].exsat4_dist), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat4_normth_A", indent + 1, &(val[i].exsat4_normth_A), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat4_normth_R", indent + 1, &(val[i].exsat4_normth_R), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat4_normth_S", indent + 1, &(val[i].exsat4_normth_S), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat5_dist", indent + 1, &(val[i].exsat5_dist), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat5_normth_A", indent + 1, &(val[i].exsat5_normth_A), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat5_normth_R", indent + 1, &(val[i].exsat5_normth_R), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat5_normth_S", indent + 1, &(val[i].exsat5_normth_S), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat6_dist", indent + 1, &(val[i].exsat6_dist), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat6_normth_A", indent + 1, &(val[i].exsat6_normth_A), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat6_normth_R", indent + 1, &(val[i].exsat6_normth_R), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsat6_normth_S", indent + 1, &(val[i].exsat6_normth_S), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsatthick1", indent + 1, &(val[i].exsatthick1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsatthick2", indent + 1, &(val[i].exsatthick2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsatthick3", indent + 1, &(val[i].exsatthick3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsatthick4", indent + 1, &(val[i].exsatthick4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsatthick5", indent + 1, &(val[i].exsatthick5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "exsatthick6", indent + 1, &(val[i].exsatthick6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "extraRRlimit", indent + 1, &(val[i].extraRRlimit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "extraScale", indent + 1, &(val[i].extraScale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "extras", indent + 1, &(val[i].extras), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "extraspecial_flag", indent + 1, &(val[i].extraspecial_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "extraspecial_seq_order_flag", indent + 1, &(val[i].extraspecial_seq_order_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fa_scale_debug", indent + 1, &(val[i].fa_scale_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fast_xtr", indent + 1, &(val[i].fast_xtr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fastprescan", indent + 1, &(val[i].fastprescan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fatFlag", indent + 1, &(val[i].fatFlag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fatT1", indent + 1, &(val[i].fatT1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fat_delta", indent + 1, &(val[i].fat_delta), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fat_flag", indent + 1, &(val[i].fat_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fat_offset", indent + 1, &(val[i].fat_offset), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fatkiller_flag", indent + 1, &(val[i].fatkiller_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fc_debug", indent + 1, &(val[i].fc_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fcineim", indent + 1, &(val[i].fcineim), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fcinent", indent + 1, &(val[i].fcinent), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fecho_factor", indent + 1, &(val[i].fecho_factor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fermi_r_factor", indent + 1, &(val[i].fermi_r_factor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fermi_rc", indent + 1, &(val[i].fermi_rc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fermi_w_factor", indent + 1, &(val[i].fermi_w_factor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fermi_wc", indent + 1, &(val[i].fermi_wc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fermr_coef_1024", indent + 1, &(val[i].fermr_coef_1024), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ff4error", indent + 1, &(val[i].ff4error), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "field_strength", indent + 1, &(val[i].field_strength), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fieldstrength", indent + 1, &(val[i].fieldstrength), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fiesta_gated_dda", indent + 1, &(val[i].fiesta_gated_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fiesta_gated_flat_dda", indent + 1, &(val[i].fiesta_gated_flat_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fiesta_gated_ramp_dda", indent + 1, &(val[i].fiesta_gated_ramp_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fiesta_gated_ramp_down", indent + 1, &(val[i].fiesta_gated_ramp_down), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fiesta_killer_flag", indent + 1, &(val[i].fiesta_killer_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fiesta_rampup_type", indent + 1, &(val[i].fiesta_rampup_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "filter_cfh_fid", indent + 1, &(val[i].filter_cfh_fid), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "filter_cfl_fid", indent + 1, &(val[i].filter_cfl_fid), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "filter_echo1", indent + 1, &(val[i].filter_echo1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "filter_echo1as", indent + 1, &(val[i].filter_echo1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "filter_echo1dtg", indent + 1, &(val[i].filter_echo1dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "filter_echo1ftg", indent + 1, &(val[i].filter_echo1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "filter_echo1mon", indent + 1, &(val[i].filter_echo1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "filter_echo1mps1", indent + 1, &(val[i].filter_echo1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "filter_echo1rs", indent + 1, &(val[i].filter_echo1rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "filter_echo1tm", indent + 1, &(val[i].filter_echo1tm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "filter_echo1xtg", indent + 1, &(val[i].filter_echo1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "filter_echo2", indent + 1, &(val[i].filter_echo2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "filter_echo2ftg", indent + 1, &(val[i].filter_echo2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "filter_rcvn_fid", indent + 1, &(val[i].filter_rcvn_fid), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "filterslot1", indent + 1, &(val[i].filterslot1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "filterslot2", indent + 1, &(val[i].filterslot2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "firstSeriesFlag", indent + 1, &(val[i].firstSeriesFlag), 1);
#endif
#ifdef SIZEOF_STATUS
    print_brsfc_STATUS(fp, "first_prepscan", indent + 1, &(val[i].first_prepscan), 1);
#endif
#ifdef SIZEOF_STATUS
    print_brsfc_STATUS(fp, "first_scan", indent + 1, &(val[i].first_scan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fix_fermi", indent + 1, &(val[i].fix_fermi), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fl_width_x_frac", indent + 1, &(val[i].fl_width_x_frac), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fl_width_x_full", indent + 1, &(val[i].fl_width_x_full), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "flexte_flag", indent + 1, &(val[i].flexte_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "flextr_flag", indent + 1, &(val[i].flextr_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_hard180", indent + 1, &(val[i].flip_hard180), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_pctas", indent + 1, &(val[i].flip_pctas), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf0", indent + 1, &(val[i].flip_rf0), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf0cfh", indent + 1, &(val[i].flip_rf0cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf1", indent + 1, &(val[i].flip_rf1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf180", indent + 1, &(val[i].flip_rf180), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf1as", indent + 1, &(val[i].flip_rf1as), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf1cfh", indent + 1, &(val[i].flip_rf1cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf1cfl", indent + 1, &(val[i].flip_rf1cfl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf1dtg", indent + 1, &(val[i].flip_rf1dtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf1ftg", indent + 1, &(val[i].flip_rf1ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf1mon", indent + 1, &(val[i].flip_rf1mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf1mps1", indent + 1, &(val[i].flip_rf1mps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf1rs", indent + 1, &(val[i].flip_rf1rs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf1tm", indent + 1, &(val[i].flip_rf1tm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf1xtg", indent + 1, &(val[i].flip_rf1xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf2cfh", indent + 1, &(val[i].flip_rf2cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf2ftg", indent + 1, &(val[i].flip_rf2ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf2mon", indent + 1, &(val[i].flip_rf2mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf2mps1", indent + 1, &(val[i].flip_rf2mps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf2xtg", indent + 1, &(val[i].flip_rf2xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf3cfh", indent + 1, &(val[i].flip_rf3cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf3ftg", indent + 1, &(val[i].flip_rf3ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf3xtg", indent + 1, &(val[i].flip_rf3xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf4cfh", indent + 1, &(val[i].flip_rf4cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf4xtg", indent + 1, &(val[i].flip_rf4xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rf90", indent + 1, &(val[i].flip_rf90), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfbdtg", indent + 1, &(val[i].flip_rfbdtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfbrs", indent + 1, &(val[i].flip_rfbrs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfcssat", indent + 1, &(val[i].flip_rfcssat), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfcssat_noscale", indent + 1, &(val[i].flip_rfcssat_noscale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfcssatcfh", indent + 1, &(val[i].flip_rfcssatcfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfcylr", indent + 1, &(val[i].flip_rfcylr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfcylr_navsat", indent + 1, &(val[i].flip_rfcylr_navsat), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfcylrtipup", indent + 1, &(val[i].flip_rfcylrtipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfflp180", indent + 1, &(val[i].flip_rfflp180), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfflp90", indent + 1, &(val[i].flip_rfflp90), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfflp90r", indent + 1, &(val[i].flip_rfflp90r), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rffrir", indent + 1, &(val[i].flip_rffrir), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rffs", indent + 1, &(val[i].flip_rffs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfgir01", indent + 1, &(val[i].flip_rfgir01), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfgir02", indent + 1, &(val[i].flip_rfgir02), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfmon_navsat", indent + 1, &(val[i].flip_rfmon_navsat), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfmontipup", indent + 1, &(val[i].flip_rfmontipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfs5fph", indent + 1, &(val[i].flip_rfs5fph), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfse1", indent + 1, &(val[i].flip_rfse1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfse2", indent + 1, &(val[i].flip_rfse2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfse3", indent + 1, &(val[i].flip_rfse3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfse4", indent + 1, &(val[i].flip_rfse4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfse5", indent + 1, &(val[i].flip_rfse5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfse6", indent + 1, &(val[i].flip_rfse6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfssf", indent + 1, &(val[i].flip_rfssf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfssfh", indent + 1, &(val[i].flip_rfssfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfsx1", indent + 1, &(val[i].flip_rfsx1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfsx2", indent + 1, &(val[i].flip_rfsx2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfsy1", indent + 1, &(val[i].flip_rfsy1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfsy2", indent + 1, &(val[i].flip_rfsy2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfsz1", indent + 1, &(val[i].flip_rfsz1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rfsz2", indent + 1, &(val[i].flip_rfsz2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flip_rftipup", indent + 1, &(val[i].flip_rftipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "flow4D_flag", indent + 1, &(val[i].flow4D_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "flow_comp_type", indent + 1, &(val[i].flow_comp_type), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flow_wdth_x", indent + 1, &(val[i].flow_wdth_x), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flow_wdth_y", indent + 1, &(val[i].flow_wdth_y), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flow_wdth_z", indent + 1, &(val[i].flow_wdth_z), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "flowpos1x", indent + 1, &(val[i].flowpos1x), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "flowpos1y", indent + 1, &(val[i].flowpos1y), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "flowpos1z", indent + 1, &(val[i].flowpos1z), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "flowpos2x", indent + 1, &(val[i].flowpos2x), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "flowpos2y", indent + 1, &(val[i].flowpos2y), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "flowpos2z", indent + 1, &(val[i].flowpos2z), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fn", indent + 1, &(val[i].fn), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fnecho_frac", indent + 1, &(val[i].fnecho_frac), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fnecho_lim", indent + 1, &(val[i].fnecho_lim), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "force_gradOpt_loop_break", indent + 1, &(val[i].force_gradOpt_loop_break), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fov_advisory_ignore_mslices", indent + 1, &(val[i].fov_advisory_ignore_mslices), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fov_factor", indent + 1, &(val[i].fov_factor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fov_freq_scale", indent + 1, &(val[i].fov_freq_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fov_lim_mps", indent + 1, &(val[i].fov_lim_mps), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fov_phase_scale", indent + 1, &(val[i].fov_phase_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fov_scaling", indent + 1, &(val[i].fov_scaling), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "frac_rf", indent + 1, &(val[i].frac_rf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "fract_echo_annefact_reduction", indent + 1, &(val[i].fract_echo_annefact_reduction), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "freqSign", indent + 1, &(val[i].freqSign), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "freq_scale", indent + 1, &(val[i].freq_scale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fs_2pi", indent + 1, &(val[i].fs_2pi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fs_pcfiesta_flag", indent + 1, &(val[i].fs_pcfiesta_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fs_pi", indent + 1, &(val[i].fs_pi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ftg_dda", indent + 1, &(val[i].ftg_dda), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ftgscale", indent + 1, &(val[i].ftgscale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ftgtr", indent + 1, &(val[i].ftgtr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ftmra_debug", indent + 1, &(val[i].ftmra_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ftmra_dfsat_flag", indent + 1, &(val[i].ftmra_dfsat_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ftmra_enable_flag", indent + 1, &(val[i].ftmra_enable_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ftmra_exsat_flag", indent + 1, &(val[i].ftmra_exsat_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ftmra_flag", indent + 1, &(val[i].ftmra_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ftmra_hard180_act", indent + 1, &(val[i].ftmra_hard180_act), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ftmra_sat_flag", indent + 1, &(val[i].ftmra_sat_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "fullte_flag", indent + 1, &(val[i].fullte_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gated_dda", indent + 1, &(val[i].gated_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gating", indent + 1, &(val[i].gating), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "genview_ellipt_cal", indent + 1, &(val[i].genview_ellipt_cal), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "genview_fovVthick_scale", indent + 1, &(val[i].genview_fovVthick_scale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "genview_maxaphase", indent + 1, &(val[i].genview_maxaphase), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "genview_totalviews", indent + 1, &(val[i].genview_totalviews), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "get_fullecho", indent + 1, &(val[i].get_fullecho), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gir_newgeo", indent + 1, &(val[i].gir_newgeo), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gir_obl_debug", indent + 1, &(val[i].gir_obl_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gir_rfiso1", indent + 1, &(val[i].gir_rfiso1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gir_rfiso2", indent + 1, &(val[i].gir_rfiso2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gir_start", indent + 1, &(val[i].gir_start), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gir_td0", indent + 1, &(val[i].gir_td0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gir_time", indent + 1, &(val[i].gir_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gir_time_daq", indent + 1, &(val[i].gir_time_daq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gir_time_eval", indent + 1, &(val[i].gir_time_eval), 1);
#endif
#ifdef SIZEOF_LOG_GRAD
    print_brsfc_LOG_GRAD(fp, "girloggrd", indent + 1, &(val[i].girloggrd), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gldelayf", indent + 1, &(val[i].gldelayf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "glimit", indent + 1, &(val[i].glimit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "glimit_x", indent + 1, &(val[i].glimit_x), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "glimit_y", indent + 1, &(val[i].glimit_y), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "glimit_z", indent + 1, &(val[i].glimit_z), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "golden_ratio_flag", indent + 1, &(val[i].golden_ratio_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gradChokeFlag", indent + 1, &(val[i].gradChokeFlag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gradCoilMethod", indent + 1, &(val[i].gradCoilMethod), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gradDCsafeMethod", indent + 1, &(val[i].gradDCsafeMethod), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gradDriverMethod", indent + 1, &(val[i].gradDriverMethod), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gradHeatFile", indent + 1, &(val[i].gradHeatFile), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gradHeatFlag", indent + 1, &(val[i].gradHeatFlag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gradHeatMethod", indent + 1, &(val[i].gradHeatMethod), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gradOpt_GX2", indent + 1, &(val[i].gradOpt_GX2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gradOpt_Piter_count", indent + 1, &(val[i].gradOpt_Piter_count), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_Ptor", indent + 1, &(val[i].gradOpt_Ptor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_Pweight", indent + 1, &(val[i].gradOpt_Pweight), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gradOpt_TE", indent + 1, &(val[i].gradOpt_TE), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_TEfactor", indent + 1, &(val[i].gradOpt_TEfactor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_TEfactor_Max", indent + 1, &(val[i].gradOpt_TEfactor_Max), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_TEfactor_Min", indent + 1, &(val[i].gradOpt_TEfactor_Min), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_TRfactor", indent + 1, &(val[i].gradOpt_TRfactor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_TRfactor_Max", indent + 1, &(val[i].gradOpt_TRfactor_Max), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_TRfactor_Min", indent + 1, &(val[i].gradOpt_TRfactor_Min), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gradOpt_aTETR_method", indent + 1, &(val[i].gradOpt_aTETR_method), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gradOpt_convergence_flag", indent + 1, &(val[i].gradOpt_convergence_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gradOpt_flag", indent + 1, &(val[i].gradOpt_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gradOpt_iter_count", indent + 1, &(val[i].gradOpt_iter_count), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_nonconv_tor", indent + 1, &(val[i].gradOpt_nonconv_tor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_nonconv_tor_limit", indent + 1, &(val[i].gradOpt_nonconv_tor_limit), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gradOpt_powerOpt_flag", indent + 1, &(val[i].gradOpt_powerOpt_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_powerTE", indent + 1, &(val[i].gradOpt_powerTE), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_powerTR", indent + 1, &(val[i].gradOpt_powerTR), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_ratio", indent + 1, &(val[i].gradOpt_ratio), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gradOpt_run_flag", indent + 1, &(val[i].gradOpt_run_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_scale", indent + 1, &(val[i].gradOpt_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_scale_Max", indent + 1, &(val[i].gradOpt_scale_Max), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_scale_Min", indent + 1, &(val[i].gradOpt_scale_Min), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_slewRate", indent + 1, &(val[i].gradOpt_slewRate), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_slewRate_limit", indent + 1, &(val[i].gradOpt_slewRate_limit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_slewRate_tmp", indent + 1, &(val[i].gradOpt_slewRate_tmp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_tor", indent + 1, &(val[i].gradOpt_tor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gradOpt_weight", indent + 1, &(val[i].gradOpt_weight), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "grad_intensity_thres", indent + 1, &(val[i].grad_intensity_thres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "grad_spec_change_flag", indent + 1, &(val[i].grad_spec_change_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "grad_spec_ctrl", indent + 1, &(val[i].grad_spec_ctrl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gradient_mode", indent + 1, &(val[i].gradient_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "grid_fov_factor", indent + 1, &(val[i].grid_fov_factor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gsat_scale", indent + 1, &(val[i].gsat_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_hard180", indent + 1, &(val[i].gscale_hard180), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_kill", indent + 1, &(val[i].gscale_kill), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_omega_hs_rfcssat", indent + 1, &(val[i].gscale_omega_hs_rfcssat), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_omega_ir0", indent + 1, &(val[i].gscale_omega_ir0), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_omega_rffrir", indent + 1, &(val[i].gscale_omega_rffrir), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_omega_rfgir01", indent + 1, &(val[i].gscale_omega_rfgir01), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_omega_rfgir02", indent + 1, &(val[i].gscale_omega_rfgir02), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_omegarf0cfh", indent + 1, &(val[i].gscale_omegarf0cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf0", indent + 1, &(val[i].gscale_rf0), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf0cfh", indent + 1, &(val[i].gscale_rf0cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf1", indent + 1, &(val[i].gscale_rf1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf1as", indent + 1, &(val[i].gscale_rf1as), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf1cfh", indent + 1, &(val[i].gscale_rf1cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf1cfl", indent + 1, &(val[i].gscale_rf1cfl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf1dtg", indent + 1, &(val[i].gscale_rf1dtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf1ftg", indent + 1, &(val[i].gscale_rf1ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf1mon", indent + 1, &(val[i].gscale_rf1mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf1mps1", indent + 1, &(val[i].gscale_rf1mps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf1rs", indent + 1, &(val[i].gscale_rf1rs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf1tm", indent + 1, &(val[i].gscale_rf1tm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf1xtg", indent + 1, &(val[i].gscale_rf1xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf2ftg", indent + 1, &(val[i].gscale_rf2ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf2mon", indent + 1, &(val[i].gscale_rf2mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf2mps1", indent + 1, &(val[i].gscale_rf2mps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf2xtg", indent + 1, &(val[i].gscale_rf2xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf3ftg", indent + 1, &(val[i].gscale_rf3ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf3xtg", indent + 1, &(val[i].gscale_rf3xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf4xtg", indent + 1, &(val[i].gscale_rf4xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rf90", indent + 1, &(val[i].gscale_rf90), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfcssat", indent + 1, &(val[i].gscale_rfcssat), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfflp180", indent + 1, &(val[i].gscale_rfflp180), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfflp180_the", indent + 1, &(val[i].gscale_rfflp180_the), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfflp90", indent + 1, &(val[i].gscale_rfflp90), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfflp90_the", indent + 1, &(val[i].gscale_rfflp90_the), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfflp90r", indent + 1, &(val[i].gscale_rfflp90r), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfflp90r_the", indent + 1, &(val[i].gscale_rfflp90r_the), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rffrir", indent + 1, &(val[i].gscale_rffrir), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfgir01", indent + 1, &(val[i].gscale_rfgir01), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfgir02", indent + 1, &(val[i].gscale_rfgir02), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfmontipup", indent + 1, &(val[i].gscale_rfmontipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfse1", indent + 1, &(val[i].gscale_rfse1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfse2", indent + 1, &(val[i].gscale_rfse2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfse3", indent + 1, &(val[i].gscale_rfse3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfse4", indent + 1, &(val[i].gscale_rfse4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfse5", indent + 1, &(val[i].gscale_rfse5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfse6", indent + 1, &(val[i].gscale_rfse6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfsx1", indent + 1, &(val[i].gscale_rfsx1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfsx2", indent + 1, &(val[i].gscale_rfsx2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfsy1", indent + 1, &(val[i].gscale_rfsy1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfsy2", indent + 1, &(val[i].gscale_rfsy2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfsz1", indent + 1, &(val[i].gscale_rfsz1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rfsz2", indent + 1, &(val[i].gscale_rfsz2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gscale_rftipup", indent + 1, &(val[i].gscale_rftipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gxfctarget", indent + 1, &(val[i].gxfctarget), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gxwex_bridge", indent + 1, &(val[i].gxwex_bridge), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gxwex_on", indent + 1, &(val[i].gxwex_on), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gxwex_target", indent + 1, &(val[i].gxwex_target), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gxwex_target_hfdslite", indent + 1, &(val[i].gxwex_target_hfdslite), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gxwex_target_hfdslite_value_3dde", indent + 1, &(val[i].gxwex_target_hfdslite_value_3dde), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gyfctarget", indent + 1, &(val[i].gyfctarget), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gykcs_max", indent + 1, &(val[i].gykcs_max), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gz1_first_moment", indent + 1, &(val[i].gz1_first_moment), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gz1_zero_moment", indent + 1, &(val[i].gz1_zero_moment), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gz_time", indent + 1, &(val[i].gz_time), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "gzfctarget", indent + 1, &(val[i].gzfctarget), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gzptime", indent + 1, &(val[i].gzptime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "gztype", indent + 1, &(val[i].gztype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "had_sat", indent + 1, &(val[i].had_sat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "hard180time", indent + 1, &(val[i].hard180time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "headneck_pos_scan", indent + 1, &(val[i].headneck_pos_scan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "heart3d_flag", indent + 1, &(val[i].heart3d_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "higher_dbdt_flag", indent + 1, &(val[i].higher_dbdt_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "hires_recon", indent + 1, &(val[i].hires_recon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "hist_wait_time", indent + 1, &(val[i].hist_wait_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "hrf1a", indent + 1, &(val[i].hrf1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "hrf1b", indent + 1, &(val[i].hrf1b), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "hst_flag", indent + 1, &(val[i].hst_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "hst_length", indent + 1, &(val[i].hst_length), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_cine3d", indent + 1, &(val[i].ia_cine3d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_coilsw_off", indent + 1, &(val[i].ia_coilsw_off), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_coilsw_on", indent + 1, &(val[i].ia_coilsw_on), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_contrfhubsel", indent + 1, &(val[i].ia_contrfhubsel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_contrfsel", indent + 1, &(val[i].ia_contrfsel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_dDDIQ", indent + 1, &(val[i].ia_dDDIQ), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_ddphase", indent + 1, &(val[i].ia_ddphase), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_de", indent + 1, &(val[i].ia_de), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_dtreg", indent + 1, &(val[i].ia_dtreg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_dtregpass", indent + 1, &(val[i].ia_dtregpass), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_endgycylra", indent + 1, &(val[i].ia_endgycylra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_endgycylratipup", indent + 1, &(val[i].ia_endgycylratipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_endgzcylra", indent + 1, &(val[i].ia_endgzcylra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_endgzcylratipup", indent + 1, &(val[i].ia_endgzcylratipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1", indent + 1, &(val[i].ia_gx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1as", indent + 1, &(val[i].ia_gx1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1bftg", indent + 1, &(val[i].ia_gx1bftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1bxtg", indent + 1, &(val[i].ia_gx1bxtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1cfh", indent + 1, &(val[i].ia_gx1cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1d", indent + 1, &(val[i].ia_gx1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1dtg", indent + 1, &(val[i].ia_gx1dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1fed", indent + 1, &(val[i].ia_gx1fed), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1fen", indent + 1, &(val[i].ia_gx1fen), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1feu", indent + 1, &(val[i].ia_gx1feu), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1ftg", indent + 1, &(val[i].ia_gx1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1mon", indent + 1, &(val[i].ia_gx1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1mps1", indent + 1, &(val[i].ia_gx1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1rs", indent + 1, &(val[i].ia_gx1rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1tm", indent + 1, &(val[i].ia_gx1tm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1u", indent + 1, &(val[i].ia_gx1u), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1wa", indent + 1, &(val[i].ia_gx1wa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx1wb", indent + 1, &(val[i].ia_gx1wb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx2", indent + 1, &(val[i].ia_gx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx2dtg", indent + 1, &(val[i].ia_gx2dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx2fed", indent + 1, &(val[i].ia_gx2fed), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx2fen", indent + 1, &(val[i].ia_gx2fen), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx2feu", indent + 1, &(val[i].ia_gx2feu), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx2ftg", indent + 1, &(val[i].ia_gx2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx2rs", indent + 1, &(val[i].ia_gx2rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gx2test", indent + 1, &(val[i].ia_gx2test), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxb", indent + 1, &(val[i].ia_gxb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxbrsfc1", indent + 1, &(val[i].ia_gxbrsfc1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxbrsfc2", indent + 1, &(val[i].ia_gxbrsfc2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxfc", indent + 1, &(val[i].ia_gxfc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxfcd", indent + 1, &(val[i].ia_gxfcd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxfcmon", indent + 1, &(val[i].ia_gxfcmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxfcu", indent + 1, &(val[i].ia_gxfcu), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxflpk", indent + 1, &(val[i].ia_gxflpk), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxflpkwa", indent + 1, &(val[i].ia_gxflpkwa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxflpkwb", indent + 1, &(val[i].ia_gxflpkwb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxflpvenc", indent + 1, &(val[i].ia_gxflpvenc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxflpvencwa", indent + 1, &(val[i].ia_gxflpvencwa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxflpvencwb", indent + 1, &(val[i].ia_gxflpvencwb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxhyst1", indent + 1, &(val[i].ia_gxhyst1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxhyst2", indent + 1, &(val[i].ia_gxhyst2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxkas", indent + 1, &(val[i].ia_gxkas), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxkbsdtg", indent + 1, &(val[i].ia_gxkbsdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxkbsrs", indent + 1, &(val[i].ia_gxkbsrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxkcs", indent + 1, &(val[i].ia_gxkcs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxkdtg", indent + 1, &(val[i].ia_gxkdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxkfs", indent + 1, &(val[i].ia_gxkfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxkill", indent + 1, &(val[i].ia_gxkill), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxkrcvn", indent + 1, &(val[i].ia_gxkrcvn), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxkrs", indent + 1, &(val[i].ia_gxkrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxks", indent + 1, &(val[i].ia_gxks), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxkse1", indent + 1, &(val[i].ia_gxkse1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxkse2", indent + 1, &(val[i].ia_gxkse2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxkse3", indent + 1, &(val[i].ia_gxkse3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxkse4", indent + 1, &(val[i].ia_gxkse4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxkse5", indent + 1, &(val[i].ia_gxkse5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxkse6", indent + 1, &(val[i].ia_gxkse6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxksp", indent + 1, &(val[i].ia_gxksp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxkssf", indent + 1, &(val[i].ia_gxkssf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxksx1", indent + 1, &(val[i].ia_gxksx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxksx2", indent + 1, &(val[i].ia_gxksx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxksy1", indent + 1, &(val[i].ia_gxksy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxksy2", indent + 1, &(val[i].ia_gxksy2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxksz1", indent + 1, &(val[i].ia_gxksz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxksz2", indent + 1, &(val[i].ia_gxksz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxrf1tm", indent + 1, &(val[i].ia_gxrf1tm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxrf2cfh", indent + 1, &(val[i].ia_gxrf2cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxrfsx1", indent + 1, &(val[i].ia_gxrfsx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxrfsx2", indent + 1, &(val[i].ia_gxrfsx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxspiral", indent + 1, &(val[i].ia_gxspiral), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxspiral2", indent + 1, &(val[i].ia_gxspiral2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxspoil", indent + 1, &(val[i].ia_gxspoil), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxspoil2", indent + 1, &(val[i].ia_gxspoil2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxw", indent + 1, &(val[i].ia_gxw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxw1ftg", indent + 1, &(val[i].ia_gxw1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxw1xtg", indent + 1, &(val[i].ia_gxw1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxw2", indent + 1, &(val[i].ia_gxw2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxw2dtg", indent + 1, &(val[i].ia_gxw2dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxw2ftg", indent + 1, &(val[i].ia_gxw2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxw2rs", indent + 1, &(val[i].ia_gxw2rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxwas", indent + 1, &(val[i].ia_gxwas), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxwdtg", indent + 1, &(val[i].ia_gxwdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxwex", indent + 1, &(val[i].ia_gxwex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxwmon", indent + 1, &(val[i].ia_gxwmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxwmps1", indent + 1, &(val[i].ia_gxwmps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gxwrs", indent + 1, &(val[i].ia_gxwrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1", indent + 1, &(val[i].ia_gy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1as", indent + 1, &(val[i].ia_gy1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1aswa", indent + 1, &(val[i].ia_gy1aswa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1aswb", indent + 1, &(val[i].ia_gy1aswb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1cfh", indent + 1, &(val[i].ia_gy1cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1dtg", indent + 1, &(val[i].ia_gy1dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1dtgwa", indent + 1, &(val[i].ia_gy1dtgwa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1dtgwb", indent + 1, &(val[i].ia_gy1dtgwb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1fed", indent + 1, &(val[i].ia_gy1fed), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1fen", indent + 1, &(val[i].ia_gy1fen), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1feu", indent + 1, &(val[i].ia_gy1feu), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1mon", indent + 1, &(val[i].ia_gy1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1mps1", indent + 1, &(val[i].ia_gy1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1r", indent + 1, &(val[i].ia_gy1r), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1ras", indent + 1, &(val[i].ia_gy1ras), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1raswa", indent + 1, &(val[i].ia_gy1raswa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1raswb", indent + 1, &(val[i].ia_gy1raswb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1rdtg", indent + 1, &(val[i].ia_gy1rdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1rdtgwa", indent + 1, &(val[i].ia_gy1rdtgwa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1rdtgwb", indent + 1, &(val[i].ia_gy1rdtgwb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1rrs", indent + 1, &(val[i].ia_gy1rrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1rrswa", indent + 1, &(val[i].ia_gy1rrswa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1rrswb", indent + 1, &(val[i].ia_gy1rrswb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1rs", indent + 1, &(val[i].ia_gy1rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1rswa", indent + 1, &(val[i].ia_gy1rswa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1rswb", indent + 1, &(val[i].ia_gy1rswb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1rwa", indent + 1, &(val[i].ia_gy1rwa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1rwb", indent + 1, &(val[i].ia_gy1rwb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1tm", indent + 1, &(val[i].ia_gy1tm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1wa", indent + 1, &(val[i].ia_gy1wa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy1wb", indent + 1, &(val[i].ia_gy1wb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy2dtg", indent + 1, &(val[i].ia_gy2dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy2dtgwa", indent + 1, &(val[i].ia_gy2dtgwa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy2dtgwb", indent + 1, &(val[i].ia_gy2dtgwb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy2fed", indent + 1, &(val[i].ia_gy2fed), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy2fen", indent + 1, &(val[i].ia_gy2fen), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy2feu", indent + 1, &(val[i].ia_gy2feu), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy2rs", indent + 1, &(val[i].ia_gy2rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy2rswa", indent + 1, &(val[i].ia_gy2rswa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gy2rswb", indent + 1, &(val[i].ia_gy2rswb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyb", indent + 1, &(val[i].ia_gyb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gybrsfc1", indent + 1, &(val[i].ia_gybrsfc1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gybrsfc2", indent + 1, &(val[i].ia_gybrsfc2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gycylr", indent + 1, &(val[i].ia_gycylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gycylrtipup", indent + 1, &(val[i].ia_gycylrtipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyfe", indent + 1, &(val[i].ia_gyfe), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyfe1", indent + 1, &(val[i].ia_gyfe1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyfe2", indent + 1, &(val[i].ia_gyfe2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyflpk", indent + 1, &(val[i].ia_gyflpk), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyflpkwa", indent + 1, &(val[i].ia_gyflpkwa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyflpkwb", indent + 1, &(val[i].ia_gyflpkwb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyflpvenc", indent + 1, &(val[i].ia_gyflpvenc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyflpvencwa", indent + 1, &(val[i].ia_gyflpvencwa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyflpvencwb", indent + 1, &(val[i].ia_gyflpvencwb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyhyst1", indent + 1, &(val[i].ia_gyhyst1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyhyst2", indent + 1, &(val[i].ia_gyhyst2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gykcfh", indent + 1, &(val[i].ia_gykcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gykcfl", indent + 1, &(val[i].ia_gykcfl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gykcs", indent + 1, &(val[i].ia_gykcs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gykcs_max", indent + 1, &(val[i].ia_gykcs_max), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gykfs", indent + 1, &(val[i].ia_gykfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gykill", indent + 1, &(val[i].ia_gykill), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gykrcvn", indent + 1, &(val[i].ia_gykrcvn), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gykse1", indent + 1, &(val[i].ia_gykse1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gykse2", indent + 1, &(val[i].ia_gykse2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gykse3", indent + 1, &(val[i].ia_gykse3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gykse4", indent + 1, &(val[i].ia_gykse4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gykse5", indent + 1, &(val[i].ia_gykse5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gykse6", indent + 1, &(val[i].ia_gykse6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyksp", indent + 1, &(val[i].ia_gyksp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gykssf", indent + 1, &(val[i].ia_gykssf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyksx1", indent + 1, &(val[i].ia_gyksx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyksx2", indent + 1, &(val[i].ia_gyksx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyksy1", indent + 1, &(val[i].ia_gyksy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyksy2", indent + 1, &(val[i].ia_gyksy2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyksz1", indent + 1, &(val[i].ia_gyksz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyksz2", indent + 1, &(val[i].ia_gyksz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gykxtgl", indent + 1, &(val[i].ia_gykxtgl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gykxtgr", indent + 1, &(val[i].ia_gykxtgr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyrf0kcfh", indent + 1, &(val[i].ia_gyrf0kcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyrf1mon", indent + 1, &(val[i].ia_gyrf1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyrf1mps1", indent + 1, &(val[i].ia_gyrf1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyrf1tm", indent + 1, &(val[i].ia_gyrf1tm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyrf1xtg", indent + 1, &(val[i].ia_gyrf1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyrf2cfh", indent + 1, &(val[i].ia_gyrf2cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyrf2lmon", indent + 1, &(val[i].ia_gyrf2lmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyrf2mon", indent + 1, &(val[i].ia_gyrf2mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyrf2rmon", indent + 1, &(val[i].ia_gyrf2rmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyrf3cfh", indent + 1, &(val[i].ia_gyrf3cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyrfmontipup", indent + 1, &(val[i].ia_gyrfmontipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyrfsy1", indent + 1, &(val[i].ia_gyrfsy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyrfsy2", indent + 1, &(val[i].ia_gyrfsy2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyspiral", indent + 1, &(val[i].ia_gyspiral), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyspiral2", indent + 1, &(val[i].ia_gyspiral2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyspoil", indent + 1, &(val[i].ia_gyspoil), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gyspoil2", indent + 1, &(val[i].ia_gyspoil2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz1", indent + 1, &(val[i].ia_gz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz1as", indent + 1, &(val[i].ia_gz1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz1cfl", indent + 1, &(val[i].ia_gz1cfl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz1d", indent + 1, &(val[i].ia_gz1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz1dtg", indent + 1, &(val[i].ia_gz1dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz1fed", indent + 1, &(val[i].ia_gz1fed), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz1fen", indent + 1, &(val[i].ia_gz1fen), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz1feu", indent + 1, &(val[i].ia_gz1feu), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz1ftg", indent + 1, &(val[i].ia_gz1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz1mon", indent + 1, &(val[i].ia_gz1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz1mps1", indent + 1, &(val[i].ia_gz1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz1rs", indent + 1, &(val[i].ia_gz1rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz1s", indent + 1, &(val[i].ia_gz1s), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz1u", indent + 1, &(val[i].ia_gz1u), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz1xtg", indent + 1, &(val[i].ia_gz1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz2bftg", indent + 1, &(val[i].ia_gz2bftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz2fed", indent + 1, &(val[i].ia_gz2fed), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz2fen", indent + 1, &(val[i].ia_gz2fen), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz2feu", indent + 1, &(val[i].ia_gz2feu), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz2ftg", indent + 1, &(val[i].ia_gz2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz2xtg", indent + 1, &(val[i].ia_gz2xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gz3ftg", indent + 1, &(val[i].ia_gz3ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzbrsfc1", indent + 1, &(val[i].ia_gzbrsfc1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzbrsfc1echo1", indent + 1, &(val[i].ia_gzbrsfc1echo1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzbrsfc1echo2", indent + 1, &(val[i].ia_gzbrsfc1echo2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzbrsfc2", indent + 1, &(val[i].ia_gzbrsfc2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzcomb", indent + 1, &(val[i].ia_gzcomb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzcombhtr", indent + 1, &(val[i].ia_gzcombhtr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzcombhtrwa", indent + 1, &(val[i].ia_gzcombhtrwa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzcombhtrwb", indent + 1, &(val[i].ia_gzcombhtrwb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzcombwa", indent + 1, &(val[i].ia_gzcombwa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzcombwb", indent + 1, &(val[i].ia_gzcombwb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzcylr", indent + 1, &(val[i].ia_gzcylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzcylrtipup", indent + 1, &(val[i].ia_gzcylrtipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzfcbase", indent + 1, &(val[i].ia_gzfcbase), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzfccomb", indent + 1, &(val[i].ia_gzfccomb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzfcd", indent + 1, &(val[i].ia_gzfcd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzfcend", indent + 1, &(val[i].ia_gzfcend), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzfcu", indent + 1, &(val[i].ia_gzfcu), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzflpk", indent + 1, &(val[i].ia_gzflpk), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzflpkwa", indent + 1, &(val[i].ia_gzflpkwa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzflpkwb", indent + 1, &(val[i].ia_gzflpkwb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzflpvenc", indent + 1, &(val[i].ia_gzflpvenc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzflpvencwa", indent + 1, &(val[i].ia_gzflpvencwa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzflpvencwb", indent + 1, &(val[i].ia_gzflpvencwb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzk", indent + 1, &(val[i].ia_gzk), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzkas", indent + 1, &(val[i].ia_gzkas), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzkbsdtg", indent + 1, &(val[i].ia_gzkbsdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzkbsrs", indent + 1, &(val[i].ia_gzkbsrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzkcs", indent + 1, &(val[i].ia_gzkcs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzkdtg", indent + 1, &(val[i].ia_gzkdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzkfs", indent + 1, &(val[i].ia_gzkfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzkgir01", indent + 1, &(val[i].ia_gzkgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzkgir02", indent + 1, &(val[i].ia_gzkgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzkill", indent + 1, &(val[i].ia_gzkill), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzkiller", indent + 1, &(val[i].ia_gzkiller), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzkmon", indent + 1, &(val[i].ia_gzkmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzkmontipup", indent + 1, &(val[i].ia_gzkmontipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzkrcvn", indent + 1, &(val[i].ia_gzkrcvn), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzkrffrir", indent + 1, &(val[i].ia_gzkrffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzkrs", indent + 1, &(val[i].ia_gzkrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzks", indent + 1, &(val[i].ia_gzks), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzks5fp", indent + 1, &(val[i].ia_gzks5fp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzksp", indent + 1, &(val[i].ia_gzksp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzkssf", indent + 1, &(val[i].ia_gzkssf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzp", indent + 1, &(val[i].ia_gzp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzphtr", indent + 1, &(val[i].ia_gzphtr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzphtrwa", indent + 1, &(val[i].ia_gzphtrwa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzphtrwb", indent + 1, &(val[i].ia_gzphtrwb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzptm", indent + 1, &(val[i].ia_gzptm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzpwa", indent + 1, &(val[i].ia_gzpwa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzpwb", indent + 1, &(val[i].ia_gzpwb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf0", indent + 1, &(val[i].ia_gzrf0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf0cfh", indent + 1, &(val[i].ia_gzrf0cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf0k", indent + 1, &(val[i].ia_gzrf0k), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf1", indent + 1, &(val[i].ia_gzrf1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ia_gzrf1_temp", indent + 1, &(val[i].ia_gzrf1_temp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf1as", indent + 1, &(val[i].ia_gzrf1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf1cfh", indent + 1, &(val[i].ia_gzrf1cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf1cfl", indent + 1, &(val[i].ia_gzrf1cfl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf1dtg", indent + 1, &(val[i].ia_gzrf1dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf1ftg", indent + 1, &(val[i].ia_gzrf1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf1htr", indent + 1, &(val[i].ia_gzrf1htr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf1mon", indent + 1, &(val[i].ia_gzrf1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf1mps1", indent + 1, &(val[i].ia_gzrf1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf1rs", indent + 1, &(val[i].ia_gzrf1rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf1s", indent + 1, &(val[i].ia_gzrf1s), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf1xtg", indent + 1, &(val[i].ia_gzrf1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf2ftg", indent + 1, &(val[i].ia_gzrf2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf2lcfh", indent + 1, &(val[i].ia_gzrf2lcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf2lmps1", indent + 1, &(val[i].ia_gzrf2lmps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf2mps1", indent + 1, &(val[i].ia_gzrf2mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf2rcfh", indent + 1, &(val[i].ia_gzrf2rcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf2rmps1", indent + 1, &(val[i].ia_gzrf2rmps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf2xtg", indent + 1, &(val[i].ia_gzrf2xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf3ftg", indent + 1, &(val[i].ia_gzrf3ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf3lcfh", indent + 1, &(val[i].ia_gzrf3lcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf3rcfh", indent + 1, &(val[i].ia_gzrf3rcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf4cfh", indent + 1, &(val[i].ia_gzrf4cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf4lcfh", indent + 1, &(val[i].ia_gzrf4lcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrf4rcfh", indent + 1, &(val[i].ia_gzrf4rcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrffrir", indent + 1, &(val[i].ia_gzrffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrfgir01", indent + 1, &(val[i].ia_gzrfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrfgir02", indent + 1, &(val[i].ia_gzrfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrfs5fph", indent + 1, &(val[i].ia_gzrfs5fph), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrfse1", indent + 1, &(val[i].ia_gzrfse1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrfse2", indent + 1, &(val[i].ia_gzrfse2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrfse3", indent + 1, &(val[i].ia_gzrfse3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrfse4", indent + 1, &(val[i].ia_gzrfse4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrfse5", indent + 1, &(val[i].ia_gzrfse5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrfse6", indent + 1, &(val[i].ia_gzrfse6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrfssfh", indent + 1, &(val[i].ia_gzrfssfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrfsz1", indent + 1, &(val[i].ia_gzrfsz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzrfsz2", indent + 1, &(val[i].ia_gzrfsz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzs5fphcomb", indent + 1, &(val[i].ia_gzs5fphcomb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzssfhcomb", indent + 1, &(val[i].ia_gzssfhcomb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzvlw", indent + 1, &(val[i].ia_gzvlw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_hard180", indent + 1, &(val[i].ia_hard180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_omega_hs_rfcssat", indent + 1, &(val[i].ia_omega_hs_rfcssat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_omega_ir0", indent + 1, &(val[i].ia_omega_ir0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_omega_rffrir", indent + 1, &(val[i].ia_omega_rffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_omega_rfgir01", indent + 1, &(val[i].ia_omega_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_omega_rfgir02", indent + 1, &(val[i].ia_omega_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_omegarf0cfh", indent + 1, &(val[i].ia_omegarf0cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_ph180", indent + 1, &(val[i].ia_ph180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_phs_rf3xtg", indent + 1, &(val[i].ia_phs_rf3xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_phs_rf4xtg", indent + 1, &(val[i].ia_phs_rf4xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_postgxw1ftg", indent + 1, &(val[i].ia_postgxw1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rcvrbl", indent + 1, &(val[i].ia_rcvrbl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rcvrbl2", indent + 1, &(val[i].ia_rcvrbl2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf0", indent + 1, &(val[i].ia_rf0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf0cfh", indent + 1, &(val[i].ia_rf0cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf1", indent + 1, &(val[i].ia_rf1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf180", indent + 1, &(val[i].ia_rf180), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ia_rf1_temp", indent + 1, &(val[i].ia_rf1_temp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf1as", indent + 1, &(val[i].ia_rf1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf1cfh", indent + 1, &(val[i].ia_rf1cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf1cfl", indent + 1, &(val[i].ia_rf1cfl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf1dtg", indent + 1, &(val[i].ia_rf1dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf1ftg", indent + 1, &(val[i].ia_rf1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf1htr", indent + 1, &(val[i].ia_rf1htr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf1mon", indent + 1, &(val[i].ia_rf1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf1mps1", indent + 1, &(val[i].ia_rf1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf1rs", indent + 1, &(val[i].ia_rf1rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf1tm", indent + 1, &(val[i].ia_rf1tm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf1xtg", indent + 1, &(val[i].ia_rf1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf2cfh", indent + 1, &(val[i].ia_rf2cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf2ftg", indent + 1, &(val[i].ia_rf2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf2mon", indent + 1, &(val[i].ia_rf2mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf2mps1", indent + 1, &(val[i].ia_rf2mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf2xtg", indent + 1, &(val[i].ia_rf2xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf3cfh", indent + 1, &(val[i].ia_rf3cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf3ftg", indent + 1, &(val[i].ia_rf3ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf3xtg", indent + 1, &(val[i].ia_rf3xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf4cfh", indent + 1, &(val[i].ia_rf4cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf4xtg", indent + 1, &(val[i].ia_rf4xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf90", indent + 1, &(val[i].ia_rf90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfbdtg", indent + 1, &(val[i].ia_rfbdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfbdtg_theta", indent + 1, &(val[i].ia_rfbdtg_theta), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfbrs", indent + 1, &(val[i].ia_rfbrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfbrs_theta", indent + 1, &(val[i].ia_rfbrs_theta), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfcssat", indent + 1, &(val[i].ia_rfcssat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfcssatcfh", indent + 1, &(val[i].ia_rfcssatcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfcylr", indent + 1, &(val[i].ia_rfcylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfcylrtipup", indent + 1, &(val[i].ia_rfcylrtipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfflp180", indent + 1, &(val[i].ia_rfflp180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfflp180_the", indent + 1, &(val[i].ia_rfflp180_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfflp90", indent + 1, &(val[i].ia_rfflp90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfflp90_the", indent + 1, &(val[i].ia_rfflp90_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfflp90r", indent + 1, &(val[i].ia_rfflp90r), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfflp90r_the", indent + 1, &(val[i].ia_rfflp90r_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rffrir", indent + 1, &(val[i].ia_rffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rffs", indent + 1, &(val[i].ia_rffs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfgir01", indent + 1, &(val[i].ia_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfgir02", indent + 1, &(val[i].ia_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfmontipup", indent + 1, &(val[i].ia_rfmontipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfs5fph", indent + 1, &(val[i].ia_rfs5fph), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfse1", indent + 1, &(val[i].ia_rfse1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfse2", indent + 1, &(val[i].ia_rfse2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfse3", indent + 1, &(val[i].ia_rfse3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfse4", indent + 1, &(val[i].ia_rfse4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfse5", indent + 1, &(val[i].ia_rfse5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfse6", indent + 1, &(val[i].ia_rfse6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfssf", indent + 1, &(val[i].ia_rfssf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfssfh", indent + 1, &(val[i].ia_rfssfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfsx1", indent + 1, &(val[i].ia_rfsx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfsx2", indent + 1, &(val[i].ia_rfsx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfsy1", indent + 1, &(val[i].ia_rfsy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfsy2", indent + 1, &(val[i].ia_rfsy2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfsz1", indent + 1, &(val[i].ia_rfsz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rfsz2", indent + 1, &(val[i].ia_rfsz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rftipup", indent + 1, &(val[i].ia_rftipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_sdixon", indent + 1, &(val[i].ia_sdixon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_sdixon2", indent + 1, &(val[i].ia_sdixon2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_stgycylra", indent + 1, &(val[i].ia_stgycylra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_stgycylratipup", indent + 1, &(val[i].ia_stgycylratipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_stgzcylra", indent + 1, &(val[i].ia_stgzcylra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_stgzcylratipup", indent + 1, &(val[i].ia_stgzcylratipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_thcylr", indent + 1, &(val[i].ia_thcylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_thcylrtipup", indent + 1, &(val[i].ia_thcylrtipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_thetarf1", indent + 1, &(val[i].ia_thetarf1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_xdixon", indent + 1, &(val[i].ia_xdixon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_ydixon", indent + 1, &(val[i].ia_ydixon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_zdixon", indent + 1, &(val[i].ia_zdixon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_debug", indent + 1, &(val[i].ideal_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_echo_mode", indent + 1, &(val[i].ideal_echo_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_flag", indent + 1, &(val[i].ideal_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_max", indent + 1, &(val[i].ideal_max), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_max_im", indent + 1, &(val[i].ideal_max_im), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_max_locs", indent + 1, &(val[i].ideal_max_locs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_min", indent + 1, &(val[i].ideal_min), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_min_te", indent + 1, &(val[i].ideal_min_te), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_necho", indent + 1, &(val[i].ideal_necho), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_no_mag_im", indent + 1, &(val[i].ideal_no_mag_im), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_opt_te", indent + 1, &(val[i].ideal_opt_te), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_pw", indent + 1, &(val[i].ideal_pw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_shift1", indent + 1, &(val[i].ideal_shift1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_shift2", indent + 1, &(val[i].ideal_shift2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_shift3", indent + 1, &(val[i].ideal_shift3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_shift_max", indent + 1, &(val[i].ideal_shift_max), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_te1", indent + 1, &(val[i].ideal_te1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_te2", indent + 1, &(val[i].ideal_te2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ideal_te3", indent + 1, &(val[i].ideal_te3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "idealiq_enable_higher_flip", indent + 1, &(val[i].idealiq_enable_higher_flip), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "idealiq_esp", indent + 1, &(val[i].idealiq_esp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "idealiq_flag", indent + 1, &(val[i].idealiq_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "idealiq_nshots", indent + 1, &(val[i].idealiq_nshots), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "idealiq_optfa", indent + 1, &(val[i].idealiq_optfa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "idealiq_pc_dda", indent + 1, &(val[i].idealiq_pc_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "idealiq_pc_dimension", indent + 1, &(val[i].idealiq_pc_dimension), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "idealiq_pc_extra_TR", indent + 1, &(val[i].idealiq_pc_extra_TR), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "idealiq_pc_flag", indent + 1, &(val[i].idealiq_pc_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "idealiq_pc_ylines", indent + 1, &(val[i].idealiq_pc_ylines), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "idealiq_pc_ylower", indent + 1, &(val[i].idealiq_pc_ylower), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "idealiq_pc_yupper", indent + 1, &(val[i].idealiq_pc_yupper), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "idealiq_pc_zlines", indent + 1, &(val[i].idealiq_pc_zlines), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "idealiq_pc_zlower", indent + 1, &(val[i].idealiq_pc_zlower), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "idealiq_pc_zupper", indent + 1, &(val[i].idealiq_pc_zupper), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "idealiq_ps_echo", indent + 1, &(val[i].idealiq_ps_echo), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "idealiq_pw", indent + 1, &(val[i].idealiq_pw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ifir_dnav_flag", indent + 1, &(val[i].ifir_dnav_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ifir_dummy_pe", indent + 1, &(val[i].ifir_dummy_pe), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ifir_flag", indent + 1, &(val[i].ifir_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ifir_frir_flag", indent + 1, &(val[i].ifir_frir_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ifir_position", indent + 1, &(val[i].ifir_position), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ifir_stir_flag", indent + 1, &(val[i].ifir_stir_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ifir_vthick", indent + 1, &(val[i].ifir_vthick), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv1", indent + 1, &(val[i].ih_idealdbg_cv1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv10", indent + 1, &(val[i].ih_idealdbg_cv10), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv11", indent + 1, &(val[i].ih_idealdbg_cv11), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv12", indent + 1, &(val[i].ih_idealdbg_cv12), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv13", indent + 1, &(val[i].ih_idealdbg_cv13), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv14", indent + 1, &(val[i].ih_idealdbg_cv14), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv15", indent + 1, &(val[i].ih_idealdbg_cv15), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv16", indent + 1, &(val[i].ih_idealdbg_cv16), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv17", indent + 1, &(val[i].ih_idealdbg_cv17), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv18", indent + 1, &(val[i].ih_idealdbg_cv18), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv19", indent + 1, &(val[i].ih_idealdbg_cv19), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv2", indent + 1, &(val[i].ih_idealdbg_cv2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv20", indent + 1, &(val[i].ih_idealdbg_cv20), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv21", indent + 1, &(val[i].ih_idealdbg_cv21), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv22", indent + 1, &(val[i].ih_idealdbg_cv22), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv23", indent + 1, &(val[i].ih_idealdbg_cv23), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv24", indent + 1, &(val[i].ih_idealdbg_cv24), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv25", indent + 1, &(val[i].ih_idealdbg_cv25), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv26", indent + 1, &(val[i].ih_idealdbg_cv26), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv27", indent + 1, &(val[i].ih_idealdbg_cv27), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv28", indent + 1, &(val[i].ih_idealdbg_cv28), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv29", indent + 1, &(val[i].ih_idealdbg_cv29), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv3", indent + 1, &(val[i].ih_idealdbg_cv3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv30", indent + 1, &(val[i].ih_idealdbg_cv30), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv31", indent + 1, &(val[i].ih_idealdbg_cv31), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv32", indent + 1, &(val[i].ih_idealdbg_cv32), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv4", indent + 1, &(val[i].ih_idealdbg_cv4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv5", indent + 1, &(val[i].ih_idealdbg_cv5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv6", indent + 1, &(val[i].ih_idealdbg_cv6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv7", indent + 1, &(val[i].ih_idealdbg_cv7), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv8", indent + 1, &(val[i].ih_idealdbg_cv8), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ih_idealdbg_cv9", indent + 1, &(val[i].ih_idealdbg_cv9), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihbsoffsetfreq", indent + 1, &(val[i].ihbsoffsetfreq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihbspti", indent + 1, &(val[i].ihbspti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihcardt1map_hb_pattern", indent + 1, &(val[i].ihcardt1map_hb_pattern), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihdixonipte", indent + 1, &(val[i].ihdixonipte), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihdixonoopte", indent + 1, &(val[i].ihdixonoopte), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihdixonte", indent + 1, &(val[i].ihdixonte), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "iheesp", indent + 1, &(val[i].iheesp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihesp", indent + 1, &(val[i].ihesp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihfcineim", indent + 1, &(val[i].ihfcineim), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihfcinent", indent + 1, &(val[i].ihfcinent), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihflip", indent + 1, &(val[i].ihflip), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihinplanexres", indent + 1, &(val[i].ihinplanexres), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihinplaneyres", indent + 1, &(val[i].ihinplaneyres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihlabeltime", indent + 1, &(val[i].ihlabeltime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihmaxtdelphase", indent + 1, &(val[i].ihmaxtdelphase), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihnegscanspacing", indent + 1, &(val[i].ihnegscanspacing), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihnew_series", indent + 1, &(val[i].ihnew_series), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihnex", indent + 1, &(val[i].ihnex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihoffsetfreq", indent + 1, &(val[i].ihoffsetfreq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihpostlabeldelay", indent + 1, &(val[i].ihpostlabeldelay), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihrbwperpix", indent + 1, &(val[i].ihrbwperpix), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihtagfa", indent + 1, &(val[i].ihtagfa), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihtagor", indent + 1, &(val[i].ihtagor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihtdel1", indent + 1, &(val[i].ihtdel1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihte1", indent + 1, &(val[i].ihte1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihte10", indent + 1, &(val[i].ihte10), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihte11", indent + 1, &(val[i].ihte11), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihte12", indent + 1, &(val[i].ihte12), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihte13", indent + 1, &(val[i].ihte13), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihte14", indent + 1, &(val[i].ihte14), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihte15", indent + 1, &(val[i].ihte15), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihte16", indent + 1, &(val[i].ihte16), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihte2", indent + 1, &(val[i].ihte2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihte3", indent + 1, &(val[i].ihte3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihte4", indent + 1, &(val[i].ihte4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihte5", indent + 1, &(val[i].ihte5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihte6", indent + 1, &(val[i].ihte6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihte7", indent + 1, &(val[i].ihte7), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihte8", indent + 1, &(val[i].ihte8), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihte9", indent + 1, &(val[i].ihte9), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihti", indent + 1, &(val[i].ihti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ihtr", indent + 1, &(val[i].ihtr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihvbw1", indent + 1, &(val[i].ihvbw1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihvbw10", indent + 1, &(val[i].ihvbw10), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihvbw11", indent + 1, &(val[i].ihvbw11), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihvbw12", indent + 1, &(val[i].ihvbw12), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihvbw13", indent + 1, &(val[i].ihvbw13), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihvbw14", indent + 1, &(val[i].ihvbw14), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihvbw15", indent + 1, &(val[i].ihvbw15), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihvbw16", indent + 1, &(val[i].ihvbw16), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihvbw2", indent + 1, &(val[i].ihvbw2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihvbw3", indent + 1, &(val[i].ihvbw3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihvbw4", indent + 1, &(val[i].ihvbw4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihvbw5", indent + 1, &(val[i].ihvbw5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihvbw6", indent + 1, &(val[i].ihvbw6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihvbw7", indent + 1, &(val[i].ihvbw7), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihvbw8", indent + 1, &(val[i].ihvbw8), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ihvbw9", indent + 1, &(val[i].ihvbw9), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "imagenum", indent + 1, &(val[i].imagenum), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "imaxectricksview", indent + 1, &(val[i].imaxectricksview), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "init_xtg_deadtime", indent + 1, &(val[i].init_xtg_deadtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "initialize_gradOpt", indent + 1, &(val[i].initialize_gradOpt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "initialize_scale", indent + 1, &(val[i].initialize_scale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "initnewgeo", indent + 1, &(val[i].initnewgeo), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "inter_necho", indent + 1, &(val[i].inter_necho), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "intermittant_chemsat", indent + 1, &(val[i].intermittant_chemsat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "intslab_flag", indent + 1, &(val[i].intslab_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "invertphase", indent + 1, &(val[i].invertphase), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ipg_trigtest", indent + 1, &(val[i].ipg_trigtest), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ir_seqtime_adjust", indent + 1, &(val[i].ir_seqtime_adjust), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "irdisdacqs", indent + 1, &(val[i].irdisdacqs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "irfreq", indent + 1, &(val[i].irfreq), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "irmsx", indent + 1, &(val[i].irmsx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "irmsy", indent + 1, &(val[i].irmsy), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "irmsz", indent + 1, &(val[i].irmsz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "irprep_flag", indent + 1, &(val[i].irprep_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "irscale", indent + 1, &(val[i].irscale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "isi_done", indent + 1, &(val[i].isi_done), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "isi_extra", indent + 1, &(val[i].isi_extra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "isi_extra_gir", indent + 1, &(val[i].isi_extra_gir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "isi_flag", indent + 1, &(val[i].isi_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "isi_girdelay", indent + 1, &(val[i].isi_girdelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "isi_satdelay", indent + 1, &(val[i].isi_satdelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "isi_sliceextra", indent + 1, &(val[i].isi_sliceextra), 1);
#endif
#ifdef SIZEOF_short_int
    print_brsfc_short_int(fp, "isibit", indent + 1, &(val[i].isibit), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "iso_delay", indent + 1, &(val[i].iso_delay), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "iso_delay_frac", indent + 1, &(val[i].iso_delay_frac), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "iso_delay_rfflp90", indent + 1, &(val[i].iso_delay_rfflp90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "iso_delay_rfflp90r", indent + 1, &(val[i].iso_delay_rfflp90r), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "jstd_exponent_NV", indent + 1, &(val[i].jstd_exponent_NV), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "jstd_exponent_body", indent + 1, &(val[i].jstd_exponent_body), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "jstd_multiplier_NV", indent + 1, &(val[i].jstd_multiplier_NV), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "jstd_multiplier_body", indent + 1, &(val[i].jstd_multiplier_body), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "k_ideal_pi", indent + 1, &(val[i].k_ideal_pi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "kacq_uid_washin", indent + 1, &(val[i].kacq_uid_washin), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "kaiser_ramplen", indent + 1, &(val[i].kaiser_ramplen), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "kband_width", indent + 1, &(val[i].kband_width), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "kernel_regions", indent + 1, &(val[i].kernel_regions), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "kernel_regions_max", indent + 1, &(val[i].kernel_regions_max), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "kernel_regions_min", indent + 1, &(val[i].kernel_regions_min), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "killer01_time", indent + 1, &(val[i].killer01_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "killer02_time", indent + 1, &(val[i].killer02_time), 1);
#endif
#ifdef SIZEOF_WF_PROCESSOR
    print_brsfc_WF_PROCESSOR(fp, "killer_axis", indent + 1, &(val[i].killer_axis), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "krewind_flag", indent + 1, &(val[i].krewind_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "krfermecorr_factor", indent + 1, &(val[i].krfermecorr_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ktarc_flag", indent + 1, &(val[i].ktarc_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "lava_ave_mode", indent + 1, &(val[i].lava_ave_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "lava_flag", indent + 1, &(val[i].lava_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "linestodiscard", indent + 1, &(val[i].linestodiscard), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "llimte1", indent + 1, &(val[i].llimte1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "llimte2", indent + 1, &(val[i].llimte2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "llimte3", indent + 1, &(val[i].llimte3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "local_tg", indent + 1, &(val[i].local_tg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "locposition_rfgir01", indent + 1, &(val[i].locposition_rfgir01), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "locposition_rfgir02", indent + 1, &(val[i].locposition_rfgir02), 1);
#endif
#ifdef SIZEOF_LOG_GRAD
    print_brsfc_LOG_GRAD(fp, "loggrd", indent + 1, &(val[i].loggrd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "look_for_trig", indent + 1, &(val[i].look_for_trig), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "loopdelay", indent + 1, &(val[i].loopdelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "loopdelay2", indent + 1, &(val[i].loopdelay2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "lp_mode", indent + 1, &(val[i].lp_mode), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "lp_stretch", indent + 1, &(val[i].lp_stretch), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "lx_pwmtime", indent + 1, &(val[i].lx_pwmtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ly_pwmtime", indent + 1, &(val[i].ly_pwmtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "lz_pwmtime", indent + 1, &(val[i].lz_pwmtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mag_create", indent + 1, &(val[i].mag_create), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mag_mask", indent + 1, &(val[i].mag_mask), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "maskPoints", indent + 1, &(val[i].maskPoints), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mask_phase_flag", indent + 1, &(val[i].mask_phase_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mask_regions", indent + 1, &(val[i].mask_regions), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mask_regions_max", indent + 1, &(val[i].mask_regions_max), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mask_regions_min", indent + 1, &(val[i].mask_regions_min), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "maskv_ftmra_flag", indent + 1, &(val[i].maskv_ftmra_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "maxGradRes", indent + 1, &(val[i].maxGradRes), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "maxSeriesTime", indent + 1, &(val[i].maxSeriesTime), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "max_area_gxwex", indent + 1, &(val[i].max_area_gxwex), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "max_aspir_fa", indent + 1, &(val[i].max_aspir_fa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "max_avg_time", indent + 1, &(val[i].max_avg_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "max_bamslice", indent + 1, &(val[i].max_bamslice), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "max_ff_error", indent + 1, &(val[i].max_ff_error), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "max_navgate_tr", indent + 1, &(val[i].max_navgate_tr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "max_pencodes", indent + 1, &(val[i].max_pencodes), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "max_regsar", indent + 1, &(val[i].max_regsar), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "max_resp_wait", indent + 1, &(val[i].max_resp_wait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "max_satsar", indent + 1, &(val[i].max_satsar), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "max_seqsar", indent + 1, &(val[i].max_seqsar), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "max_seqsar_orig", indent + 1, &(val[i].max_seqsar_orig), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "max_seqsar_prepoff", indent + 1, &(val[i].max_seqsar_prepoff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "max_seqsarmon", indent + 1, &(val[i].max_seqsarmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "max_slicesar_prepoff", indent + 1, &(val[i].max_slicesar_prepoff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "max_slquant", indent + 1, &(val[i].max_slquant), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "max_ss_fa", indent + 1, &(val[i].max_ss_fa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "max_tdel1_time", indent + 1, &(val[i].max_tdel1_time), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "maxb1_rf1", indent + 1, &(val[i].maxb1_rf1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "maxkiller_time", indent + 1, &(val[i].maxkiller_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "maxpc_cor", indent + 1, &(val[i].maxpc_cor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "maxpc_debug", indent + 1, &(val[i].maxpc_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "maxpc_points", indent + 1, &(val[i].maxpc_points), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "maxx", indent + 1, &(val[i].maxx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "maxy", indent + 1, &(val[i].maxy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "measured_TG", indent + 1, &(val[i].measured_TG), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_autote_flag", indent + 1, &(val[i].medal_autote_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_autotelock_flag", indent + 1, &(val[i].medal_autotelock_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_echo_mode", indent + 1, &(val[i].medal_echo_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_enh_flag", indent + 1, &(val[i].medal_enh_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_etl", indent + 1, &(val[i].medal_etl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_flag", indent + 1, &(val[i].medal_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_flexecho_order_flag", indent + 1, &(val[i].medal_flexecho_order_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "medal_freq_ave", indent + 1, &(val[i].medal_freq_ave), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "medal_freq_max", indent + 1, &(val[i].medal_freq_max), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "medal_freq_min", indent + 1, &(val[i].medal_freq_min), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "medal_fw_freq_ave", indent + 1, &(val[i].medal_fw_freq_ave), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "medal_fw_freq_llimit", indent + 1, &(val[i].medal_fw_freq_llimit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "medal_fw_freq_ulimit", indent + 1, &(val[i].medal_fw_freq_ulimit), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_ip_te", indent + 1, &(val[i].medal_ip_te), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_ip_te_max", indent + 1, &(val[i].medal_ip_te_max), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_ip_te_min", indent + 1, &(val[i].medal_ip_te_min), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_ip_te_minus", indent + 1, &(val[i].medal_ip_te_minus), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_ip_te_plus", indent + 1, &(val[i].medal_ip_te_plus), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_k_ip_pi", indent + 1, &(val[i].medal_k_ip_pi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_k_oop_pi", indent + 1, &(val[i].medal_k_oop_pi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_max", indent + 1, &(val[i].medal_max), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_max_xres", indent + 1, &(val[i].medal_max_xres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_min", indent + 1, &(val[i].medal_min), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_multitr_flag", indent + 1, &(val[i].medal_multitr_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_necho", indent + 1, &(val[i].medal_necho), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_oop_te", indent + 1, &(val[i].medal_oop_te), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_oop_te_max", indent + 1, &(val[i].medal_oop_te_max), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_oop_te_min", indent + 1, &(val[i].medal_oop_te_min), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_oop_te_minus", indent + 1, &(val[i].medal_oop_te_minus), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_oop_te_plus", indent + 1, &(val[i].medal_oop_te_plus), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_pi_ave", indent + 1, &(val[i].medal_pi_ave), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_pi_max", indent + 1, &(val[i].medal_pi_max), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_pi_min", indent + 1, &(val[i].medal_pi_min), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_pw", indent + 1, &(val[i].medal_pw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_shift1", indent + 1, &(val[i].medal_shift1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_shift2", indent + 1, &(val[i].medal_shift2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_shift_max", indent + 1, &(val[i].medal_shift_max), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_te1", indent + 1, &(val[i].medal_te1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_te1_upper", indent + 1, &(val[i].medal_te1_upper), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_te2", indent + 1, &(val[i].medal_te2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "medal_te2_upper", indent + 1, &(val[i].medal_te2_upper), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "merge_defaultTE", indent + 1, &(val[i].merge_defaultTE), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "merge_echoIndex", indent + 1, &(val[i].merge_echoIndex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "merge_flag", indent + 1, &(val[i].merge_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "merge_min_echoes", indent + 1, &(val[i].merge_min_echoes), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "merge_mintr", indent + 1, &(val[i].merge_mintr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "merge_satweight", indent + 1, &(val[i].merge_satweight), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "merge_targetTE", indent + 1, &(val[i].merge_targetTE), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mild_note_support", indent + 1, &(val[i].mild_note_support), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min180te", indent + 1, &(val[i].min180te), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "min_delay_sec", indent + 1, &(val[i].min_delay_sec), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_delay_time", indent + 1, &(val[i].min_delay_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_dtgte", indent + 1, &(val[i].min_dtgte), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_end_segment_delay", indent + 1, &(val[i].min_end_segment_delay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_montr", indent + 1, &(val[i].min_montr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_pencodes", indent + 1, &(val[i].min_pencodes), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_rfampcpblty", indent + 1, &(val[i].min_rfampcpblty), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_rfampcpblty_prepoff", indent + 1, &(val[i].min_rfampcpblty_prepoff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_rfavgpow", indent + 1, &(val[i].min_rfavgpow), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_rfavgpow_prepoff", indent + 1, &(val[i].min_rfavgpow_prepoff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_rfdycc", indent + 1, &(val[i].min_rfdycc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_rfdycc_prepoff", indent + 1, &(val[i].min_rfdycc_prepoff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_rfrmsb1", indent + 1, &(val[i].min_rfrmsb1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_rfrmsb1_prepoff", indent + 1, &(val[i].min_rfrmsb1_prepoff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_rste", indent + 1, &(val[i].min_rste), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_segment_tr", indent + 1, &(val[i].min_segment_tr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_seq1", indent + 1, &(val[i].min_seq1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_seq2", indent + 1, &(val[i].min_seq2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_seq2_echo2", indent + 1, &(val[i].min_seq2_echo2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_seq2_echo3", indent + 1, &(val[i].min_seq2_echo3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_seq2_echo4", indent + 1, &(val[i].min_seq2_echo4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_seq3", indent + 1, &(val[i].min_seq3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_seqgrad", indent + 1, &(val[i].min_seqgrad), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_seqrfamp", indent + 1, &(val[i].min_seqrfamp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_seqrfamp_prepoff", indent + 1, &(val[i].min_seqrfamp_prepoff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_seqrfampmon", indent + 1, &(val[i].min_seqrfampmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_seqx", indent + 1, &(val[i].min_seqx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_seqxz", indent + 1, &(val[i].min_seqxz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_slquant", indent + 1, &(val[i].min_slquant), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_specirti", indent + 1, &(val[i].min_specirti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_tdel1_fiesta", indent + 1, &(val[i].min_tdel1_fiesta), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_tdel1_time", indent + 1, &(val[i].min_tdel1_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_tefe", indent + 1, &(val[i].min_tefe), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_tegy", indent + 1, &(val[i].min_tegy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_tegz", indent + 1, &(val[i].min_tegz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_tenfe", indent + 1, &(val[i].min_tenfe), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_ti", indent + 1, &(val[i].min_ti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "min_tseq_irprep", indent + 1, &(val[i].min_tseq_irprep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minimize_RFunblank_time", indent + 1, &(val[i].minimize_RFunblank_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minpcflattop", indent + 1, &(val[i].minpcflattop), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minph_iso_delay", indent + 1, &(val[i].minph_iso_delay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqbusbar_t", indent + 1, &(val[i].minseqbusbar_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqbusbarmon_t", indent + 1, &(val[i].minseqbusbarmon_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqcable_maxpow_t", indent + 1, &(val[i].minseqcable_maxpow_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqcable_t", indent + 1, &(val[i].minseqcable_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqcableburst_t", indent + 1, &(val[i].minseqcableburst_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqcablemon_t", indent + 1, &(val[i].minseqcablemon_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqchoke_t", indent + 1, &(val[i].minseqchoke_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqcoil_esp", indent + 1, &(val[i].minseqcoil_esp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqcoil_t", indent + 1, &(val[i].minseqcoil_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqcoilburst_t", indent + 1, &(val[i].minseqcoilburst_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqcoilmon_t", indent + 1, &(val[i].minseqcoilmon_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqgpm_maxpow_t", indent + 1, &(val[i].minseqgpm_maxpow_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqgpm_t", indent + 1, &(val[i].minseqgpm_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqgram_t", indent + 1, &(val[i].minseqgram_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqgrddrv_case_t", indent + 1, &(val[i].minseqgrddrv_case_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqgrddrv_t", indent + 1, &(val[i].minseqgrddrv_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqgrddrvmon_t", indent + 1, &(val[i].minseqgrddrvmon_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqgrddrvx_t", indent + 1, &(val[i].minseqgrddrvx_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqgrddrvxmon_t", indent + 1, &(val[i].minseqgrddrvxmon_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqgrddrvy_t", indent + 1, &(val[i].minseqgrddrvy_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqgrddrvymon_t", indent + 1, &(val[i].minseqgrddrvymon_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqgrddrvz_t", indent + 1, &(val[i].minseqgrddrvz_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqgrddrvzmon_t", indent + 1, &(val[i].minseqgrddrvzmon_t), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqpwm_x", indent + 1, &(val[i].minseqpwm_x), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqpwm_y", indent + 1, &(val[i].minseqpwm_y), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqpwm_z", indent + 1, &(val[i].minseqpwm_z), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "minseqrf_cal", indent + 1, &(val[i].minseqrf_cal), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mkgspec_epi2_flag", indent + 1, &(val[i].mkgspec_epi2_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mkgspec_flag", indent + 1, &(val[i].mkgspec_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mkgspec_x_gmax_flag", indent + 1, &(val[i].mkgspec_x_gmax_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mkgspec_x_sr_flag", indent + 1, &(val[i].mkgspec_x_sr_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mkgspec_y_gmax_flag", indent + 1, &(val[i].mkgspec_y_gmax_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mkgspec_y_sr_flag", indent + 1, &(val[i].mkgspec_y_sr_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mkgspec_z_gmax_flag", indent + 1, &(val[i].mkgspec_z_gmax_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mkgspec_z_sr_flag", indent + 1, &(val[i].mkgspec_z_sr_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mlevon", indent + 1, &(val[i].mlevon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "mon_acqfov", indent + 1, &(val[i].mon_acqfov), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "mon_angle", indent + 1, &(val[i].mon_angle), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mon_dabdelay", indent + 1, &(val[i].mon_dabdelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mon_fcomp", indent + 1, &(val[i].mon_fcomp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "mon_fov", indent + 1, &(val[i].mon_fov), 1);
#endif
#ifdef SIZEOF_SCAN_INFO
    print_brsfc_SCAN_INFO(fp, "mon_loc", indent + 1, &(val[i].mon_loc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mon_navgs", indent + 1, &(val[i].mon_navgs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mon_run_setrcvportimm", indent + 1, &(val[i].mon_run_setrcvportimm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mon_ssi_time", indent + 1, &(val[i].mon_ssi_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mon_tr", indent + 1, &(val[i].mon_tr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mon_tr_nav", indent + 1, &(val[i].mon_tr_nav), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mon_tr_wait", indent + 1, &(val[i].mon_tr_wait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mon_trigger_delay", indent + 1, &(val[i].mon_trigger_delay), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "mon_vthick", indent + 1, &(val[i].mon_vthick), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "mon_vthicky", indent + 1, &(val[i].mon_vthicky), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "mon_vthickz", indent + 1, &(val[i].mon_vthickz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mon_xres", indent + 1, &(val[i].mon_xres), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "monave_sar", indent + 1, &(val[i].monave_sar), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "moncave_sar", indent + 1, &(val[i].moncave_sar), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "monitor_axis", indent + 1, &(val[i].monitor_axis), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "monitor_page", indent + 1, &(val[i].monitor_page), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "monitor_test", indent + 1, &(val[i].monitor_test), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "monloc_shift", indent + 1, &(val[i].monloc_shift), 1);
#endif
#ifdef SIZEOF_LOG_GRAD
    print_brsfc_LOG_GRAD(fp, "monloggrd", indent + 1, &(val[i].monloggrd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "monnewgeo", indent + 1, &(val[i].monnewgeo), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "monobl_debug", indent + 1, &(val[i].monobl_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "monobl_method", indent + 1, &(val[i].monobl_method), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "monpeak_sar", indent + 1, &(val[i].monpeak_sar), 1);
#endif
#ifdef SIZEOF_PHYS_GRAD
    print_brsfc_PHYS_GRAD(fp, "monphygrd", indent + 1, &(val[i].monphygrd), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "monrot_phi", indent + 1, &(val[i].monrot_phi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "monwritectrl", indent + 1, &(val[i].monwritectrl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "motsa_ovrhd", indent + 1, &(val[i].motsa_ovrhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mph_flag", indent + 1, &(val[i].mph_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "mps1rf1_inst", indent + 1, &(val[i].mps1rf1_inst), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "mpsfov", indent + 1, &(val[i].mpsfov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "msde_dda", indent + 1, &(val[i].msde_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "msde_flag", indent + 1, &(val[i].msde_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "msde_rate", indent + 1, &(val[i].msde_rate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "msde_rfflp180_type", indent + 1, &(val[i].msde_rfflp180_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "msde_rfflp90_type", indent + 1, &(val[i].msde_rfflp90_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "msde_type", indent + 1, &(val[i].msde_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "msde_venc_polarity", indent + 1, &(val[i].msde_venc_polarity), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "msde_venc_wait_flag", indent + 1, &(val[i].msde_venc_wait_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "multiEcho_flag", indent + 1, &(val[i].multiEcho_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "multi_channel", indent + 1, &(val[i].multi_channel), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "myfreq_off", indent + 1, &(val[i].myfreq_off), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "myphase_off", indent + 1, &(val[i].myphase_off), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "myslice_off", indent + 1, &(val[i].myslice_off), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "n_hard180", indent + 1, &(val[i].n_hard180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "n_omega_hs_rfcssat", indent + 1, &(val[i].n_omega_hs_rfcssat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "n_omega_ir0", indent + 1, &(val[i].n_omega_ir0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "n_omega_rffrir", indent + 1, &(val[i].n_omega_rffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "n_omega_rfgir01", indent + 1, &(val[i].n_omega_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "n_omega_rfgir02", indent + 1, &(val[i].n_omega_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "n_omegarf0cfh", indent + 1, &(val[i].n_omegarf0cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "n_rf90", indent + 1, &(val[i].n_rf90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "n_rfflp180", indent + 1, &(val[i].n_rfflp180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "n_rfflp180_the", indent + 1, &(val[i].n_rfflp180_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "n_rfflp90", indent + 1, &(val[i].n_rfflp90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "n_rfflp90_the", indent + 1, &(val[i].n_rfflp90_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "n_rfflp90r", indent + 1, &(val[i].n_rfflp90r), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "n_rfflp90r_the", indent + 1, &(val[i].n_rfflp90r_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "n_rftipup", indent + 1, &(val[i].n_rftipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "nav_1st_factor", indent + 1, &(val[i].nav_1st_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_alg", indent + 1, &(val[i].nav_alg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_angle_adj", indent + 1, &(val[i].nav_angle_adj), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_avaiRRtime", indent + 1, &(val[i].nav_avaiRRtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_channel", indent + 1, &(val[i].nav_channel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_chemdda", indent + 1, &(val[i].nav_chemdda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_coilsel_index", indent + 1, &(val[i].nav_coilsel_index), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_coilsel_tr", indent + 1, &(val[i].nav_coilsel_tr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_dda", indent + 1, &(val[i].nav_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_debug_flag", indent + 1, &(val[i].nav_debug_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_dir", indent + 1, &(val[i].nav_dir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_dual_mode", indent + 1, &(val[i].nav_dual_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_dump_time", indent + 1, &(val[i].nav_dump_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_irprep_flag", indent + 1, &(val[i].nav_irprep_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "nav_last_factor", indent + 1, &(val[i].nav_last_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_linear_ramp_down", indent + 1, &(val[i].nav_linear_ramp_down), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_linear_ramp_up", indent + 1, &(val[i].nav_linear_ramp_up), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_min_tseq_irprep", indent + 1, &(val[i].nav_min_tseq_irprep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_normalization", indent + 1, &(val[i].nav_normalization), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_nreps", indent + 1, &(val[i].nav_nreps), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_pause_after_prescan", indent + 1, &(val[i].nav_pause_after_prescan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_prescan_tr", indent + 1, &(val[i].nav_prescan_tr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_save_raw_data", indent + 1, &(val[i].nav_save_raw_data), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_scantime_refresh", indent + 1, &(val[i].nav_scantime_refresh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_scantime_refresh_pts", indent + 1, &(val[i].nav_scantime_refresh_pts), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_sr", indent + 1, &(val[i].nav_sr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_ss", indent + 1, &(val[i].nav_ss), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_test", indent + 1, &(val[i].nav_test), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_time_per_seg", indent + 1, &(val[i].nav_time_per_seg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_time_per_yview", indent + 1, &(val[i].nav_time_per_yview), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_time_per_zsegment", indent + 1, &(val[i].nav_time_per_zsegment), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_timing_flag", indent + 1, &(val[i].nav_timing_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "nav_tipup_ratio", indent + 1, &(val[i].nav_tipup_ratio), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_tseq_irprep", indent + 1, &(val[i].nav_tseq_irprep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_type", indent + 1, &(val[i].nav_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nav_wait_flag", indent + 1, &(val[i].nav_wait_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "nav_window", indent + 1, &(val[i].nav_window), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "navend_time", indent + 1, &(val[i].navend_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "navgate_dda", indent + 1, &(val[i].navgate_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "navgate_flag", indent + 1, &(val[i].navgate_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "navgate_target_tr", indent + 1, &(val[i].navgate_target_tr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "navgs", indent + 1, &(val[i].navgs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "navigatorCYL_flag", indent + 1, &(val[i].navigatorCYL_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "navigator_flag", indent + 1, &(val[i].navigator_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "navky_segments", indent + 1, &(val[i].navky_segments), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "navky_views_per_segment", indent + 1, &(val[i].navky_views_per_segment), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "navkz_views_per_segment", indent + 1, &(val[i].navkz_views_per_segment), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "navsat_flag", indent + 1, &(val[i].navsat_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "navscale", indent + 1, &(val[i].navscale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "navseg_weight", indent + 1, &(val[i].navseg_weight), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "navsegment_dda", indent + 1, &(val[i].navsegment_dda), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "navtrig_factor", indent + 1, &(val[i].navtrig_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "navtrig_flag", indent + 1, &(val[i].navtrig_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "navtrig_target_tr", indent + 1, &(val[i].navtrig_target_tr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "navtrig_wait_before_imaging", indent + 1, &(val[i].navtrig_wait_before_imaging), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "navtrig_waittime", indent + 1, &(val[i].navtrig_waittime), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "nbw_ssrf", indent + 1, &(val[i].nbw_ssrf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ncvAdjustedDelay", indent + 1, &(val[i].ncvAdjustedDelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ncvGateMaxWait", indent + 1, &(val[i].ncvGateMaxWait), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "negpowerx", indent + 1, &(val[i].negpowerx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "negpowery", indent + 1, &(val[i].negpowery), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "negpowerz", indent + 1, &(val[i].negpowerz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "negx", indent + 1, &(val[i].negx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "negy", indent + 1, &(val[i].negy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "negz", indent + 1, &(val[i].negz), 1);
#endif
#ifdef SIZEOF_STATUS
    print_brsfc_STATUS(fp, "new_view", indent + 1, &(val[i].new_view), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nex", indent + 1, &(val[i].nex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nex_save", indent + 1, &(val[i].nex_save), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nflow4D", indent + 1, &(val[i].nflow4D), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nofermi", indent + 1, &(val[i].nofermi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nograd", indent + 1, &(val[i].nograd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "non_tetime", indent + 1, &(val[i].non_tetime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "non_tetime_mon", indent + 1, &(val[i].non_tetime_mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "nop", indent + 1, &(val[i].nop), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nope", indent + 1, &(val[i].nope), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "noswitch_coil", indent + 1, &(val[i].noswitch_coil), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "noswitch_coil_psc", indent + 1, &(val[i].noswitch_coil_psc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "noswitch_slab", indent + 1, &(val[i].noswitch_slab), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "noswitch_slab_psc", indent + 1, &(val[i].noswitch_slab_psc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nr_of_segA", indent + 1, &(val[i].nr_of_segA), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nr_of_segments", indent + 1, &(val[i].nr_of_segments), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nreps", indent + 1, &(val[i].nreps), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ns3d_flag", indent + 1, &(val[i].ns3d_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nseg_per_nav_tr", indent + 1, &(val[i].nseg_per_nav_tr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "nsegments", indent + 1, &(val[i].nsegments), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_audibles", indent + 1, &(val[i].num_audibles), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_autotr_cveval_iter", indent + 1, &(val[i].num_autotr_cveval_iter), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_avg_bline", indent + 1, &(val[i].num_avg_bline), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_baseline_pts", indent + 1, &(val[i].num_baseline_pts), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_dummy_segmentedTR", indent + 1, &(val[i].num_dummy_segmentedTR), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_filter_slots", indent + 1, &(val[i].num_filter_slots), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_images", indent + 1, &(val[i].num_images), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_mask_regions", indent + 1, &(val[i].num_mask_regions), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_outer_loops", indent + 1, &(val[i].num_outer_loops), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_regions", indent + 1, &(val[i].num_regions), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_rf1lobe", indent + 1, &(val[i].num_rf1lobe), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_rfflp180", indent + 1, &(val[i].num_rfflp180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_sats", indent + 1, &(val[i].num_sats), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_shot", indent + 1, &(val[i].num_shot), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_slice_rr", indent + 1, &(val[i].num_slice_rr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_sub_regions", indent + 1, &(val[i].num_sub_regions), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_throwaways", indent + 1, &(val[i].num_throwaways), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "num_transition_fraction", indent + 1, &(val[i].num_transition_fraction), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_views_per_nav_tr", indent + 1, &(val[i].num_views_per_nav_tr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "num_virchan", indent + 1, &(val[i].num_virchan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "numpts2pass", indent + 1, &(val[i].numpts2pass), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "numrecv", indent + 1, &(val[i].numrecv), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "numsatramp", indent + 1, &(val[i].numsatramp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "obl_debug", indent + 1, &(val[i].obl_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "obl_method", indent + 1, &(val[i].obl_method), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oblique_monplane", indent + 1, &(val[i].oblique_monplane), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oblmethod_dbdt_flag", indent + 1, &(val[i].oblmethod_dbdt_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oddnex_npw", indent + 1, &(val[i].oddnex_npw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oeff", indent + 1, &(val[i].oeff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oepf", indent + 1, &(val[i].oepf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off90", indent + 1, &(val[i].off90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off90as", indent + 1, &(val[i].off90as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off90minor", indent + 1, &(val[i].off90minor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_gzvlw", indent + 1, &(val[i].off_gzvlw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_hard180", indent + 1, &(val[i].off_hard180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_omega_hs_rfcssat", indent + 1, &(val[i].off_omega_hs_rfcssat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_omega_ir0", indent + 1, &(val[i].off_omega_ir0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_omega_rffrir", indent + 1, &(val[i].off_omega_rffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_omega_rfgir01", indent + 1, &(val[i].off_omega_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_omega_rfgir02", indent + 1, &(val[i].off_omega_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_omegarf0cfh", indent + 1, &(val[i].off_omegarf0cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf0", indent + 1, &(val[i].off_rf0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf0cfh", indent + 1, &(val[i].off_rf0cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf1", indent + 1, &(val[i].off_rf1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf1as", indent + 1, &(val[i].off_rf1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf1cfh", indent + 1, &(val[i].off_rf1cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf1cfl", indent + 1, &(val[i].off_rf1cfl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf1ftg", indent + 1, &(val[i].off_rf1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf1mon", indent + 1, &(val[i].off_rf1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf1mps1", indent + 1, &(val[i].off_rf1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf1tm", indent + 1, &(val[i].off_rf1tm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf1xtg", indent + 1, &(val[i].off_rf1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf2cfh", indent + 1, &(val[i].off_rf2cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf2ftg", indent + 1, &(val[i].off_rf2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf2mon", indent + 1, &(val[i].off_rf2mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf2mps1", indent + 1, &(val[i].off_rf2mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf2xtg", indent + 1, &(val[i].off_rf2xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf3cfh", indent + 1, &(val[i].off_rf3cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf3ftg", indent + 1, &(val[i].off_rf3ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf3xtg", indent + 1, &(val[i].off_rf3xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf4cfh", indent + 1, &(val[i].off_rf4cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf4xtg", indent + 1, &(val[i].off_rf4xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rf90", indent + 1, &(val[i].off_rf90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfcssat", indent + 1, &(val[i].off_rfcssat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfflp180", indent + 1, &(val[i].off_rfflp180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfflp180_the", indent + 1, &(val[i].off_rfflp180_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfflp90", indent + 1, &(val[i].off_rfflp90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfflp90_the", indent + 1, &(val[i].off_rfflp90_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfflp90r", indent + 1, &(val[i].off_rfflp90r), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfflp90r_the", indent + 1, &(val[i].off_rfflp90r_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rffrir", indent + 1, &(val[i].off_rffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rffs", indent + 1, &(val[i].off_rffs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfgir01", indent + 1, &(val[i].off_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfgir02", indent + 1, &(val[i].off_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfmontipup", indent + 1, &(val[i].off_rfmontipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfs5fph", indent + 1, &(val[i].off_rfs5fph), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfse1", indent + 1, &(val[i].off_rfse1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfse2", indent + 1, &(val[i].off_rfse2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfse3", indent + 1, &(val[i].off_rfse3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfse4", indent + 1, &(val[i].off_rfse4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfse5", indent + 1, &(val[i].off_rfse5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfse6", indent + 1, &(val[i].off_rfse6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfssf", indent + 1, &(val[i].off_rfssf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfssfh", indent + 1, &(val[i].off_rfssfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfsx1", indent + 1, &(val[i].off_rfsx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfsx2", indent + 1, &(val[i].off_rfsx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfsy1", indent + 1, &(val[i].off_rfsy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfsy2", indent + 1, &(val[i].off_rfsy2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfsz1", indent + 1, &(val[i].off_rfsz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfsz2", indent + 1, &(val[i].off_rfsz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rftipup", indent + 1, &(val[i].off_rftipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_thetarf1", indent + 1, &(val[i].off_thetarf1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "offset", indent + 1, &(val[i].offset), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "offset_rfgir01", indent + 1, &(val[i].offset_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "offset_rfgir02", indent + 1, &(val[i].offset_rfgir02), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ogsfMax", indent + 1, &(val[i].ogsfMax), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ogsfMin", indent + 1, &(val[i].ogsfMin), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ogsfX1", indent + 1, &(val[i].ogsfX1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ogsfX2", indent + 1, &(val[i].ogsfX2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ogsfX2_limit_Min", indent + 1, &(val[i].ogsfX2_limit_Min), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ogsfXw", indent + 1, &(val[i].ogsfXw), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ogsfXwex", indent + 1, &(val[i].ogsfXwex), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ogsfY", indent + 1, &(val[i].ogsfY), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ogsfYk", indent + 1, &(val[i].ogsfYk), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ogsfZ", indent + 1, &(val[i].ogsfZ), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ogsfZk", indent + 1, &(val[i].ogsfZk), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ogsf_limit_Max", indent + 1, &(val[i].ogsf_limit_Max), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ogsf_limit_Min", indent + 1, &(val[i].ogsf_limit_Min), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "old_phase", indent + 1, &(val[i].old_phase), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "omega_amp", indent + 1, &(val[i].omega_amp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "omega_scale", indent + 1, &(val[i].omega_scale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "op3dcine_fiesta", indent + 1, &(val[i].op3dcine_fiesta), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "op3dcine_spgr", indent + 1, &(val[i].op3dcine_spgr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "op3dgradwarp", indent + 1, &(val[i].op3dgradwarp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "op4dflow", indent + 1, &(val[i].op4dflow), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opET", indent + 1, &(val[i].opET), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opab1", indent + 1, &(val[i].opab1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opaccel_cs_stride", indent + 1, &(val[i].opaccel_cs_stride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opaccel_kt_stride", indent + 1, &(val[i].opaccel_kt_stride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opaccel_mb_stride", indent + 1, &(val[i].opaccel_mb_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opaccel_ph_stride", indent + 1, &(val[i].opaccel_ph_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opaccel_sl_stride", indent + 1, &(val[i].opaccel_sl_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opaccel_t_stride", indent + 1, &(val[i].opaccel_t_stride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opacqo", indent + 1, &(val[i].opacqo), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opacs", indent + 1, &(val[i].opacs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opadvgate", indent + 1, &(val[i].opadvgate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opallowedrescantime", indent + 1, &(val[i].opallowedrescantime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opanatomy", indent + 1, &(val[i].opanatomy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opapa", indent + 1, &(val[i].opapa), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opapcsiis", indent + 1, &(val[i].opapcsiis), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opapflow", indent + 1, &(val[i].opapflow), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opaphases", indent + 1, &(val[i].opaphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oparc", indent + 1, &(val[i].oparc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oparr", indent + 1, &(val[i].oparr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oparrmon", indent + 1, &(val[i].oparrmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opascalcfov", indent + 1, &(val[i].opascalcfov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opasl", indent + 1, &(val[i].opasl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opaslprep", indent + 1, &(val[i].opaslprep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opasset", indent + 1, &(val[i].opasset), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opassetcal", indent + 1, &(val[i].opassetcal), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opassetscan", indent + 1, &(val[i].opassetscan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opauto3dgradwarp", indent + 1, &(val[i].opauto3dgradwarp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautobti", indent + 1, &(val[i].opautobti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautodifnext2", indent + 1, &(val[i].opautodifnext2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautodifnumt2", indent + 1, &(val[i].opautodifnumt2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautoetl", indent + 1, &(val[i].opautoetl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautoflip", indent + 1, &(val[i].opautoflip), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautonecho", indent + 1, &(val[i].opautonecho), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautonex", indent + 1, &(val[i].opautonex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautonumbvals", indent + 1, &(val[i].opautonumbvals), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautorbw", indent + 1, &(val[i].opautorbw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautosldelay", indent + 1, &(val[i].opautosldelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautoslquant", indent + 1, &(val[i].opautoslquant), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautosubtract", indent + 1, &(val[i].opautosubtract), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautotdel1", indent + 1, &(val[i].opautotdel1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautote", indent + 1, &(val[i].opautote), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautoti", indent + 1, &(val[i].opautoti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautotissuet1", indent + 1, &(val[i].opautotissuet1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautotr", indent + 1, &(val[i].opautotr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opautovps", indent + 1, &(val[i].opautovps), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opaxial_slice", indent + 1, &(val[i].opaxial_slice), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opbc", indent + 1, &(val[i].opbc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opbilateral", indent + 1, &(val[i].opbilateral), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opblim", indent + 1, &(val[i].opblim), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opbrava", indent + 1, &(val[i].opbrava), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opbravo", indent + 1, &(val[i].opbravo), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opbreastmrs", indent + 1, &(val[i].opbreastmrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opbreathhold", indent + 1, &(val[i].opbreathhold), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opbsp", indent + 1, &(val[i].opbsp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opbspti", indent + 1, &(val[i].opbspti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opburstmode", indent + 1, &(val[i].opburstmode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opbval", indent + 1, &(val[i].opbval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opbwrt", indent + 1, &(val[i].opbwrt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcaldelay", indent + 1, &(val[i].opcaldelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcalmode", indent + 1, &(val[i].opcalmode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcalrequired", indent + 1, &(val[i].opcalrequired), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcardseq", indent + 1, &(val[i].opcardseq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opccsat", indent + 1, &(val[i].opccsat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcfsel", indent + 1, &(val[i].opcfsel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcgate", indent + 1, &(val[i].opcgate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcgatetype", indent + 1, &(val[i].opcgatetype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opchrate", indent + 1, &(val[i].opchrate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcineir", indent + 1, &(val[i].opcineir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opclocs", indent + 1, &(val[i].opclocs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcmon", indent + 1, &(val[i].opcmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcoax", indent + 1, &(val[i].opcoax), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcollapse", indent + 1, &(val[i].opcollapse), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcompressedsensing", indent + 1, &(val[i].opcompressedsensing), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcontrast", indent + 1, &(val[i].opcontrast), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcoronal_slice", indent + 1, &(val[i].opcoronal_slice), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcosmic", indent + 1, &(val[i].opcosmic), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcphases", indent + 1, &(val[i].opcphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcs", indent + 1, &(val[i].opcs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opcube", indent + 1, &(val[i].opcube), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdda", indent + 1, &(val[i].opdda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdeprep", indent + 1, &(val[i].opdeprep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdfax3in1", indent + 1, &(val[i].opdfax3in1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdfaxall", indent + 1, &(val[i].opdfaxall), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdfaxtetra", indent + 1, &(val[i].opdfaxtetra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdfaxx", indent + 1, &(val[i].opdfaxx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdfaxy", indent + 1, &(val[i].opdfaxy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdfaxz", indent + 1, &(val[i].opdfaxz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdfm", indent + 1, &(val[i].opdfm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdfmprescan", indent + 1, &(val[i].opdfmprescan), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opdfsathick1", indent + 1, &(val[i].opdfsathick1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opdfsathick2", indent + 1, &(val[i].opdfsathick2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opdfsathick3", indent + 1, &(val[i].opdfsathick3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opdfsathick4", indent + 1, &(val[i].opdfsathick4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opdfsathick5", indent + 1, &(val[i].opdfsathick5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opdfsathick6", indent + 1, &(val[i].opdfsathick6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdiffuse", indent + 1, &(val[i].opdiffuse), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opdifnext2", indent + 1, &(val[i].opdifnext2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdifnumbvalues", indent + 1, &(val[i].opdifnumbvalues), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdifnumdirs", indent + 1, &(val[i].opdifnumdirs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdifnumt2", indent + 1, &(val[i].opdifnumt2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdifproctype", indent + 1, &(val[i].opdifproctype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdisco", indent + 1, &(val[i].opdisco), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdixon", indent + 1, &(val[i].opdixon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdixproc", indent + 1, &(val[i].opdixproc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opdose", indent + 1, &(val[i].opdose), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdoubleir", indent + 1, &(val[i].opdoubleir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdrivemode", indent + 1, &(val[i].opdrivemode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdualspinecho", indent + 1, &(val[i].opdualspinecho), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdynaplan", indent + 1, &(val[i].opdynaplan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdynaplan_mask_phase", indent + 1, &(val[i].opdynaplan_mask_phase), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdynaplan_nphases", indent + 1, &(val[i].opdynaplan_nphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opdyntg", indent + 1, &(val[i].opdyntg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opectricks", indent + 1, &(val[i].opectricks), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opentry", indent + 1, &(val[i].opentry), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opepi", indent + 1, &(val[i].opepi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opetl", indent + 1, &(val[i].opetl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opexamnum", indent + 1, &(val[i].opexamnum), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opexcitemode", indent + 1, &(val[i].opexcitemode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opexor", indent + 1, &(val[i].opexor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opexsathick1", indent + 1, &(val[i].opexsathick1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opexsathick2", indent + 1, &(val[i].opexsathick2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opexsathick3", indent + 1, &(val[i].opexsathick3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opexsathick4", indent + 1, &(val[i].opexsathick4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opexsathick5", indent + 1, &(val[i].opexsathick5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opexsathick6", indent + 1, &(val[i].opexsathick6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opexsatlen1", indent + 1, &(val[i].opexsatlen1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opexsatlen2", indent + 1, &(val[i].opexsatlen2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opexsatlen3", indent + 1, &(val[i].opexsatlen3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opexsatlen4", indent + 1, &(val[i].opexsatlen4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opexsatlen5", indent + 1, &(val[i].opexsatlen5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opexsatlen6", indent + 1, &(val[i].opexsatlen6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opexsatloc1", indent + 1, &(val[i].opexsatloc1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opexsatloc2", indent + 1, &(val[i].opexsatloc2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opexsatloc3", indent + 1, &(val[i].opexsatloc3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opexsatloc4", indent + 1, &(val[i].opexsatloc4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opexsatloc5", indent + 1, &(val[i].opexsatloc5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opexsatloc6", indent + 1, &(val[i].opexsatloc6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opexsatmask", indent + 1, &(val[i].opexsatmask), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opexsatoff1", indent + 1, &(val[i].opexsatoff1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opexsatoff2", indent + 1, &(val[i].opexsatoff2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opexsatoff3", indent + 1, &(val[i].opexsatoff3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opexsatoff4", indent + 1, &(val[i].opexsatoff4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opexsatoff5", indent + 1, &(val[i].opexsatoff5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opexsatoff6", indent + 1, &(val[i].opexsatoff6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opexsatparal", indent + 1, &(val[i].opexsatparal), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opfMRIPDTYPE", indent + 1, &(val[i].opfMRIPDTYPE), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opfast", indent + 1, &(val[i].opfast), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opfat", indent + 1, &(val[i].opfat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opfatcl", indent + 1, &(val[i].opfatcl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opfatwater", indent + 1, &(val[i].opfatwater), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opfcaxis", indent + 1, &(val[i].opfcaxis), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opfcine", indent + 1, &(val[i].opfcine), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opfcomp", indent + 1, &(val[i].opfcomp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opflair", indent + 1, &(val[i].opflair), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opflaxall", indent + 1, &(val[i].opflaxall), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opflaxx", indent + 1, &(val[i].opflaxx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opflaxxa", indent + 1, &(val[i].opflaxxa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opflaxy", indent + 1, &(val[i].opflaxy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opflaxya", indent + 1, &(val[i].opflaxya), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opflaxz", indent + 1, &(val[i].opflaxz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opflaxza", indent + 1, &(val[i].opflaxza), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opflip", indent + 1, &(val[i].opflip), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opflrecon", indent + 1, &(val[i].opflrecon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opfluorotrigger", indent + 1, &(val[i].opfluorotrigger), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opfmri", indent + 1, &(val[i].opfmri), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opfov", indent + 1, &(val[i].opfov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opfphases", indent + 1, &(val[i].opfphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opfr", indent + 1, &(val[i].opfr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opfreqfov", indent + 1, &(val[i].opfreqfov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opfulltrain", indent + 1, &(val[i].opfulltrain), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opfus", indent + 1, &(val[i].opfus), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opgirmode", indent + 1, &(val[i].opgirmode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opgradmode", indent + 1, &(val[i].opgradmode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opgrx", indent + 1, &(val[i].opgrx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opgrxroi", indent + 1, &(val[i].opgrxroi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opharmonize", indent + 1, &(val[i].opharmonize), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opheadscout", indent + 1, &(val[i].opheadscout), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ophoecc", indent + 1, &(val[i].ophoecc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ophrate", indent + 1, &(val[i].ophrate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ophrep", indent + 1, &(val[i].ophrep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ophydro", indent + 1, &(val[i].ophydro), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opidealiq", indent + 1, &(val[i].opidealiq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opileave", indent + 1, &(val[i].opileave), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opimode", indent + 1, &(val[i].opimode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opinhance", indent + 1, &(val[i].opinhance), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opinhsflow", indent + 1, &(val[i].opinhsflow), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opinit_state", indent + 1, &(val[i].opinit_state), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opinittrigdelay", indent + 1, &(val[i].opinittrigdelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opinrangetr", indent + 1, &(val[i].opinrangetr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opinrangetrmax", indent + 1, &(val[i].opinrangetrmax), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opinrangetrmin", indent + 1, &(val[i].opinrangetrmin), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opirmode", indent + 1, &(val[i].opirmode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opirprep", indent + 1, &(val[i].opirprep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opjrmode", indent + 1, &(val[i].opjrmode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oplandmark", indent + 1, &(val[i].oplandmark), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oplava", indent + 1, &(val[i].oplava), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "oplenap", indent + 1, &(val[i].oplenap), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "oplenrl", indent + 1, &(val[i].oplenrl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "oplensi", indent + 1, &(val[i].oplensi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oploadprotocol", indent + 1, &(val[i].oploadprotocol), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "oplocap", indent + 1, &(val[i].oplocap), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "oplocrl", indent + 1, &(val[i].oplocrl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "oplocsi", indent + 1, &(val[i].oplocsi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmagc", indent + 1, &(val[i].opmagc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmagic", indent + 1, &(val[i].opmagic), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmart", indent + 1, &(val[i].opmart), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmask", indent + 1, &(val[i].opmask), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmavric", indent + 1, &(val[i].opmavric), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmb", indent + 1, &(val[i].opmb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmedal", indent + 1, &(val[i].opmedal), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmer2", indent + 1, &(val[i].opmer2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmerge", indent + 1, &(val[i].opmerge), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmintedif", indent + 1, &(val[i].opmintedif), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opmonfov", indent + 1, &(val[i].opmonfov), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opmonthick", indent + 1, &(val[i].opmonthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmph", indent + 1, &(val[i].opmph), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmphases", indent + 1, &(val[i].opmphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmprage", indent + 1, &(val[i].opmprage), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmsde", indent + 1, &(val[i].opmsde), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmsdeaxx", indent + 1, &(val[i].opmsdeaxx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmsdeaxy", indent + 1, &(val[i].opmsdeaxy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmsdeaxz", indent + 1, &(val[i].opmsdeaxz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmt", indent + 1, &(val[i].opmt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opmultistation", indent + 1, &(val[i].opmultistation), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnav", indent + 1, &(val[i].opnav), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opnavaccwin", indent + 1, &(val[i].opnavaccwin), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnavautoaccwin", indent + 1, &(val[i].opnavautoaccwin), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnavautotrigtime", indent + 1, &(val[i].opnavautotrigtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnavmaxinterval", indent + 1, &(val[i].opnavmaxinterval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnavpscpause", indent + 1, &(val[i].opnavpscpause), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnavpsctime", indent + 1, &(val[i].opnavpsctime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnavrrmeas", indent + 1, &(val[i].opnavrrmeas), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnavrrmeasrr", indent + 1, &(val[i].opnavrrmeasrr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnavrrmeastime", indent + 1, &(val[i].opnavrrmeastime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnavsigenhance", indent + 1, &(val[i].opnavsigenhance), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnavsltrack", indent + 1, &(val[i].opnavsltrack), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnavtype", indent + 1, &(val[i].opnavtype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnbh", indent + 1, &(val[i].opnbh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opncoils", indent + 1, &(val[i].opncoils), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnecho", indent + 1, &(val[i].opnecho), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnewgeo", indent + 1, &(val[i].opnewgeo), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opnex", indent + 1, &(val[i].opnex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnnex", indent + 1, &(val[i].opnnex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnopwrap", indent + 1, &(val[i].opnopwrap), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnostations", indent + 1, &(val[i].opnostations), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnrr", indent + 1, &(val[i].opnrr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnrr_dda", indent + 1, &(val[i].opnrr_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnseg", indent + 1, &(val[i].opnseg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnshots", indent + 1, &(val[i].opnshots), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnspokes", indent + 1, &(val[i].opnspokes), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnumbvals", indent + 1, &(val[i].opnumbvals), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnumgir", indent + 1, &(val[i].opnumgir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnumgroups", indent + 1, &(val[i].opnumgroups), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opnumsynbvals", indent + 1, &(val[i].opnumsynbvals), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opobplane", indent + 1, &(val[i].opobplane), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opoversamplingfactor", indent + 1, &(val[i].opoversamplingfactor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opovl", indent + 1, &(val[i].opovl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oppdgm_str", indent + 1, &(val[i].oppdgm_str), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opphasecycle", indent + 1, &(val[i].opphasecycle), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opphasefov", indent + 1, &(val[i].opphasefov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opphaseimage", indent + 1, &(val[i].opphaseimage), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opphases", indent + 1, &(val[i].opphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opphcor", indent + 1, &(val[i].opphcor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opphsen", indent + 1, &(val[i].opphsen), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opphysplane", indent + 1, &(val[i].opphysplane), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opplane", indent + 1, &(val[i].opplane), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oppomp", indent + 1, &(val[i].oppomp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oppos", indent + 1, &(val[i].oppos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "oppostlabeldelay", indent + 1, &(val[i].oppostlabeldelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opprescanopt", indent + 1, &(val[i].opprescanopt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opproject", indent + 1, &(val[i].opproject), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oppromo", indent + 1, &(val[i].oppromo), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opprop", indent + 1, &(val[i].opprop), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opprotRxMode", indent + 1, &(val[i].opprotRxMode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oppscapa", indent + 1, &(val[i].oppscapa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oppscshimtg", indent + 1, &(val[i].oppscshimtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oppscvquant", indent + 1, &(val[i].oppscvquant), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oppsd_trig", indent + 1, &(val[i].oppsd_trig), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oppseq", indent + 1, &(val[i].oppseq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opptsize", indent + 1, &(val[i].opptsize), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oppure", indent + 1, &(val[i].oppure), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oppurecal", indent + 1, &(val[i].oppurecal), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opquickstep", indent + 1, &(val[i].opquickstep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oprampdir", indent + 1, &(val[i].oprampdir), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "oprbw", indent + 1, &(val[i].oprbw), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "oprbw2", indent + 1, &(val[i].oprbw2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oprealtime", indent + 1, &(val[i].oprealtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oprect", indent + 1, &(val[i].oprect), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oprep_active", indent + 1, &(val[i].oprep_active), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oprep_rest", indent + 1, &(val[i].oprep_rest), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opresearch", indent + 1, &(val[i].opresearch), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oprgcalmode", indent + 1, &(val[i].oprgcalmode), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "oprlcsiis", indent + 1, &(val[i].oprlcsiis), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oprlflow", indent + 1, &(val[i].oprlflow), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oprtarr", indent + 1, &(val[i].oprtarr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oprtb0", indent + 1, &(val[i].oprtb0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oprtbc", indent + 1, &(val[i].oprtbc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oprtcardseq", indent + 1, &(val[i].oprtcardseq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oprtcgate", indent + 1, &(val[i].oprtcgate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oprtpoint", indent + 1, &(val[i].oprtpoint), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oprtrate", indent + 1, &(val[i].oprtrate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oprtrep", indent + 1, &(val[i].oprtrep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oprttdel1", indent + 1, &(val[i].oprttdel1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "oprttseq", indent + 1, &(val[i].oprttseq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsagittal_slice", indent + 1, &(val[i].opsagittal_slice), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsarburst", indent + 1, &(val[i].opsarburst), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsarmode", indent + 1, &(val[i].opsarmode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsat", indent + 1, &(val[i].opsat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsatmask", indent + 1, &(val[i].opsatmask), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsatx", indent + 1, &(val[i].opsatx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opsatxloc1", indent + 1, &(val[i].opsatxloc1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opsatxloc2", indent + 1, &(val[i].opsatxloc2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opsatxthick", indent + 1, &(val[i].opsatxthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsaty", indent + 1, &(val[i].opsaty), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opsatyloc1", indent + 1, &(val[i].opsatyloc1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opsatyloc2", indent + 1, &(val[i].opsatyloc2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opsatythick", indent + 1, &(val[i].opsatythick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsatz", indent + 1, &(val[i].opsatz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opsatzloc1", indent + 1, &(val[i].opsatzloc1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opsatzloc2", indent + 1, &(val[i].opsatzloc2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opsatzthick", indent + 1, &(val[i].opsatzthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsavedf", indent + 1, &(val[i].opsavedf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opscic", indent + 1, &(val[i].opscic), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opseparatesynb", indent + 1, &(val[i].opseparatesynb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsepseries", indent + 1, &(val[i].opsepseries), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opseriesnum", indent + 1, &(val[i].opseriesnum), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opseriessave", indent + 1, &(val[i].opseriessave), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opsicsiis", indent + 1, &(val[i].opsicsiis), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsiflow", indent + 1, &(val[i].opsiflow), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsilent", indent + 1, &(val[i].opsilent), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsilentlevel", indent + 1, &(val[i].opsilentlevel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsilentmr", indent + 1, &(val[i].opsilentmr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opslblank", indent + 1, &(val[i].opslblank), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsldelay", indent + 1, &(val[i].opsldelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opslice_order", indent + 1, &(val[i].opslice_order), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opslicecnt", indent + 1, &(val[i].opslicecnt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opslinky", indent + 1, &(val[i].opslinky), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsllocs", indent + 1, &(val[i].opsllocs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opslquant", indent + 1, &(val[i].opslquant), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opslspace", indent + 1, &(val[i].opslspace), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opslthick", indent + 1, &(val[i].opslthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opslzip2", indent + 1, &(val[i].opslzip2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opslzip4", indent + 1, &(val[i].opslzip4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsmartprep", indent + 1, &(val[i].opsmartprep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opspecir", indent + 1, &(val[i].opspecir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opspf", indent + 1, &(val[i].opspf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opspiral", indent + 1, &(val[i].opspiral), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsquare", indent + 1, &(val[i].opsquare), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opsrprep", indent + 1, &(val[i].opsrprep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opssfse", indent + 1, &(val[i].opssfse), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opssrf", indent + 1, &(val[i].opssrf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opstation", indent + 1, &(val[i].opstation), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opstress", indent + 1, &(val[i].opstress), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opswan", indent + 1, &(val[i].opswan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opswift", indent + 1, &(val[i].opswift), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opt1flair", indent + 1, &(val[i].opt1flair), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opt1map", indent + 1, &(val[i].opt1map), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opt2flair", indent + 1, &(val[i].opt2flair), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opt2map", indent + 1, &(val[i].opt2map), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opt2prep", indent + 1, &(val[i].opt2prep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opt2prepte", indent + 1, &(val[i].opt2prepte), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optabent", indent + 1, &(val[i].optabent), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "optagangle", indent + 1, &(val[i].optagangle), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optagging", indent + 1, &(val[i].optagging), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optagspc", indent + 1, &(val[i].optagspc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optdel1", indent + 1, &(val[i].optdel1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opte", indent + 1, &(val[i].opte), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opte2", indent + 1, &(val[i].opte2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optefw", indent + 1, &(val[i].optefw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optensor", indent + 1, &(val[i].optensor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opti", indent + 1, &(val[i].opti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optimal_channel_combine", indent + 1, &(val[i].optimal_channel_combine), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optissuet1", indent + 1, &(val[i].optissuet1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optlabel", indent + 1, &(val[i].optlabel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optlrdrf", indent + 1, &(val[i].optlrdrf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optouch", indent + 1, &(val[i].optouch), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optouchamp", indent + 1, &(val[i].optouchamp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optouchax", indent + 1, &(val[i].optouchax), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optouchcyc", indent + 1, &(val[i].optouchcyc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optouchfreq", indent + 1, &(val[i].optouchfreq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optouchmegfreq", indent + 1, &(val[i].optouchmegfreq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optouchtphases", indent + 1, &(val[i].optouchtphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optphases", indent + 1, &(val[i].optphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optr", indent + 1, &(val[i].optr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optracq", indent + 1, &(val[i].optracq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optrecovery", indent + 1, &(val[i].optrecovery), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optricksdel", indent + 1, &(val[i].optricksdel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optrickspause", indent + 1, &(val[i].optrickspause), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optrip", indent + 1, &(val[i].optrip), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "optseq", indent + 1, &(val[i].optseq), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser0", indent + 1, &(val[i].opuser0), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser1", indent + 1, &(val[i].opuser1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser10", indent + 1, &(val[i].opuser10), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser11", indent + 1, &(val[i].opuser11), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser12", indent + 1, &(val[i].opuser12), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser13", indent + 1, &(val[i].opuser13), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser14", indent + 1, &(val[i].opuser14), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser15", indent + 1, &(val[i].opuser15), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser16", indent + 1, &(val[i].opuser16), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser17", indent + 1, &(val[i].opuser17), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser18", indent + 1, &(val[i].opuser18), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser19", indent + 1, &(val[i].opuser19), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser2", indent + 1, &(val[i].opuser2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser20", indent + 1, &(val[i].opuser20), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser21", indent + 1, &(val[i].opuser21), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser22", indent + 1, &(val[i].opuser22), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser23", indent + 1, &(val[i].opuser23), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser24", indent + 1, &(val[i].opuser24), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser25", indent + 1, &(val[i].opuser25), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser26", indent + 1, &(val[i].opuser26), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser27", indent + 1, &(val[i].opuser27), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser28", indent + 1, &(val[i].opuser28), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser29", indent + 1, &(val[i].opuser29), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser3", indent + 1, &(val[i].opuser3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser30", indent + 1, &(val[i].opuser30), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser31", indent + 1, &(val[i].opuser31), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser32", indent + 1, &(val[i].opuser32), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser33", indent + 1, &(val[i].opuser33), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser34", indent + 1, &(val[i].opuser34), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser35", indent + 1, &(val[i].opuser35), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser36", indent + 1, &(val[i].opuser36), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser37", indent + 1, &(val[i].opuser37), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser38", indent + 1, &(val[i].opuser38), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser39", indent + 1, &(val[i].opuser39), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser4", indent + 1, &(val[i].opuser4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser40", indent + 1, &(val[i].opuser40), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser41", indent + 1, &(val[i].opuser41), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser42", indent + 1, &(val[i].opuser42), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser43", indent + 1, &(val[i].opuser43), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser44", indent + 1, &(val[i].opuser44), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser45", indent + 1, &(val[i].opuser45), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser46", indent + 1, &(val[i].opuser46), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser47", indent + 1, &(val[i].opuser47), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser48", indent + 1, &(val[i].opuser48), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser5", indent + 1, &(val[i].opuser5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser6", indent + 1, &(val[i].opuser6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser7", indent + 1, &(val[i].opuser7), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser8", indent + 1, &(val[i].opuser8), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opuser9", indent + 1, &(val[i].opuser9), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opuser_usage_tag", indent + 1, &(val[i].opuser_usage_tag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opvbw", indent + 1, &(val[i].opvbw), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opvenc", indent + 1, &(val[i].opvenc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opvenous", indent + 1, &(val[i].opvenous), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opvest", indent + 1, &(val[i].opvest), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opvibrant", indent + 1, &(val[i].opvibrant), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opview_order", indent + 1, &(val[i].opview_order), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opvps", indent + 1, &(val[i].opvps), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opvquant", indent + 1, &(val[i].opvquant), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opvrg", indent + 1, &(val[i].opvrg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opvsphases", indent + 1, &(val[i].opvsphases), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opvthick", indent + 1, &(val[i].opvthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opwarmup", indent + 1, &(val[i].opwarmup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opwater", indent + 1, &(val[i].opwater), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opweight", indent + 1, &(val[i].opweight), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opxres", indent + 1, &(val[i].opxres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opyres", indent + 1, &(val[i].opyres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opzip1024", indent + 1, &(val[i].opzip1024), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opzip512", indent + 1, &(val[i].opzip512), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "opzoom_coil_ind", indent + 1, &(val[i].opzoom_coil_ind), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opzoom_dist_ax", indent + 1, &(val[i].opzoom_dist_ax), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opzoom_dist_cor", indent + 1, &(val[i].opzoom_dist_cor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opzoom_dist_sag", indent + 1, &(val[i].opzoom_dist_sag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opzoom_fov_xy", indent + 1, &(val[i].opzoom_fov_xy), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "opzoom_fov_z", indent + 1, &(val[i].opzoom_fov_z), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "osfpR_flag", indent + 1, &(val[i].osfpR_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "osfp_dda", indent + 1, &(val[i].osfp_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "osfp_debug", indent + 1, &(val[i].osfp_debug), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "osfp_delay_factor", indent + 1, &(val[i].osfp_delay_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "osfp_flag", indent + 1, &(val[i].osfp_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "osfp_weight", indent + 1, &(val[i].osfp_weight), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "osfp_weight_act", indent + 1, &(val[i].osfp_weight_act), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "osfp_weight_grad", indent + 1, &(val[i].osfp_weight_grad), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "osfpsd_flag", indent + 1, &(val[i].osfpsd_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "override_opcalrequired", indent + 1, &(val[i].override_opcalrequired), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pass_thru_mode", indent + 1, &(val[i].pass_thru_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "passtime", indent + 1, &(val[i].passtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pause_after_mask_flag", indent + 1, &(val[i].pause_after_mask_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pc_const", indent + 1, &(val[i].pc_const), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pc_mode", indent + 1, &(val[i].pc_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pcfiesta_flag", indent + 1, &(val[i].pcfiesta_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pcfiesta_rf", indent + 1, &(val[i].pcfiesta_rf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pe_acq1", indent + 1, &(val[i].pe_acq1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pe_acq2", indent + 1, &(val[i].pe_acq2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pe_on", indent + 1, &(val[i].pe_on), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "peakPhaseIndex", indent + 1, &(val[i].peakPhaseIndex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "per_gx1", indent + 1, &(val[i].per_gx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "per_gy1", indent + 1, &(val[i].per_gy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "per_gy1r", indent + 1, &(val[i].per_gy1r), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "per_gzcomb", indent + 1, &(val[i].per_gzcomb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "per_gzcombhtr", indent + 1, &(val[i].per_gzcombhtr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "per_gzp", indent + 1, &(val[i].per_gzp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "per_gzphtr", indent + 1, &(val[i].per_gzphtr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "per_gzvlw", indent + 1, &(val[i].per_gzvlw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pfkr_flag", indent + 1, &(val[i].pfkr_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pfkr_fraction", indent + 1, &(val[i].pfkr_fraction), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pfkr_fraction_act", indent + 1, &(val[i].pfkr_fraction_act), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pfkr_yz_enable", indent + 1, &(val[i].pfkr_yz_enable), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pfkr_yz_flag", indent + 1, &(val[i].pfkr_yz_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pfky_fraction", indent + 1, &(val[i].pfky_fraction), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pfky_total_unaccel", indent + 1, &(val[i].pfky_total_unaccel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pfkyz2kr_flag", indent + 1, &(val[i].pfkyz2kr_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pfkz_flag", indent + 1, &(val[i].pfkz_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pfkz_fraction", indent + 1, &(val[i].pfkz_fraction), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pfkz_fraction_min", indent + 1, &(val[i].pfkz_fraction_min), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pfkz_hnover", indent + 1, &(val[i].pfkz_hnover), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pfkz_reverse_seq", indent + 1, &(val[i].pfkz_reverse_seq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pfkz_segments", indent + 1, &(val[i].pfkz_segments), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pfkz_total", indent + 1, &(val[i].pfkz_total), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pfkz_total_unaccel", indent + 1, &(val[i].pfkz_total_unaccel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pfkz_views_per_segment", indent + 1, &(val[i].pfkz_views_per_segment), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pfkz_vps_max", indent + 1, &(val[i].pfkz_vps_max), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pg_beta", indent + 1, &(val[i].pg_beta), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pgen_for_dbdt_opt", indent + 1, &(val[i].pgen_for_dbdt_opt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "phase_col", indent + 1, &(val[i].phase_col), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "phase_cor", indent + 1, &(val[i].phase_cor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "phase_cycles", indent + 1, &(val[i].phase_cycles), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "phase_order", indent + 1, &(val[i].phase_order), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "phase_rfflp180", indent + 1, &(val[i].phase_rfflp180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "phasefovgt1_flag", indent + 1, &(val[i].phasefovgt1_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "phaseres", indent + 1, &(val[i].phaseres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "phmask", indent + 1, &(val[i].phmask), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "phorder", indent + 1, &(val[i].phorder), 1);
#endif
#ifdef SIZEOF_PHYS_GRAD
    print_brsfc_PHYS_GRAD(fp, "phygrd", indent + 1, &(val[i].phygrd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "phys_rec_resolution", indent + 1, &(val[i].phys_rec_resolution), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "phys_record_channelsel", indent + 1, &(val[i].phys_record_channelsel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "phys_record_flag", indent + 1, &(val[i].phys_record_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pi1stshimb", indent + 1, &(val[i].pi1stshimb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pi2dmde", indent + 1, &(val[i].pi2dmde), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pi3dgradwarpnub", indent + 1, &(val[i].pi3dgradwarpnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pi_neg_sp", indent + 1, &(val[i].pi_neg_sp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pi_piphasfovnub", indent + 1, &(val[i].pi_piphasfovnub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_cs_step", indent + 1, &(val[i].piaccel_cs_step), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_cs_stride", indent + 1, &(val[i].piaccel_cs_stride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_csedit", indent + 1, &(val[i].piaccel_csedit), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_csnub", indent + 1, &(val[i].piaccel_csnub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_csval2", indent + 1, &(val[i].piaccel_csval2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_csval3", indent + 1, &(val[i].piaccel_csval3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_csval4", indent + 1, &(val[i].piaccel_csval4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_csval5", indent + 1, &(val[i].piaccel_csval5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_csval6", indent + 1, &(val[i].piaccel_csval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_kt_step", indent + 1, &(val[i].piaccel_kt_step), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_kt_stride", indent + 1, &(val[i].piaccel_kt_stride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_ktedit", indent + 1, &(val[i].piaccel_ktedit), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_ktnub", indent + 1, &(val[i].piaccel_ktnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_ktval2", indent + 1, &(val[i].piaccel_ktval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_ktval3", indent + 1, &(val[i].piaccel_ktval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_ktval4", indent + 1, &(val[i].piaccel_ktval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_ktval5", indent + 1, &(val[i].piaccel_ktval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_ktval6", indent + 1, &(val[i].piaccel_ktval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_mb_step", indent + 1, &(val[i].piaccel_mb_step), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_mb_stride", indent + 1, &(val[i].piaccel_mb_stride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_mbedit", indent + 1, &(val[i].piaccel_mbedit), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_mbnub", indent + 1, &(val[i].piaccel_mbnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_mbval2", indent + 1, &(val[i].piaccel_mbval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_mbval3", indent + 1, &(val[i].piaccel_mbval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_mbval4", indent + 1, &(val[i].piaccel_mbval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_mbval5", indent + 1, &(val[i].piaccel_mbval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_mbval6", indent + 1, &(val[i].piaccel_mbval6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_ph_step", indent + 1, &(val[i].piaccel_ph_step), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_ph_stride", indent + 1, &(val[i].piaccel_ph_stride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_phedit", indent + 1, &(val[i].piaccel_phedit), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_phnub", indent + 1, &(val[i].piaccel_phnub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_phval2", indent + 1, &(val[i].piaccel_phval2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_phval3", indent + 1, &(val[i].piaccel_phval3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_phval4", indent + 1, &(val[i].piaccel_phval4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_phval5", indent + 1, &(val[i].piaccel_phval5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_phval6", indent + 1, &(val[i].piaccel_phval6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_sl_step", indent + 1, &(val[i].piaccel_sl_step), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_sl_stride", indent + 1, &(val[i].piaccel_sl_stride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_sledit", indent + 1, &(val[i].piaccel_sledit), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_slnub", indent + 1, &(val[i].piaccel_slnub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_slval2", indent + 1, &(val[i].piaccel_slval2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_slval3", indent + 1, &(val[i].piaccel_slval3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_slval4", indent + 1, &(val[i].piaccel_slval4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_slval5", indent + 1, &(val[i].piaccel_slval5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_slval6", indent + 1, &(val[i].piaccel_slval6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_t_step", indent + 1, &(val[i].piaccel_t_step), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_t_stride", indent + 1, &(val[i].piaccel_t_stride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_tedit", indent + 1, &(val[i].piaccel_tedit), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccel_tnub", indent + 1, &(val[i].piaccel_tnub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_total_stride", indent + 1, &(val[i].piaccel_total_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_tval2", indent + 1, &(val[i].piaccel_tval2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_tval3", indent + 1, &(val[i].piaccel_tval3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_tval4", indent + 1, &(val[i].piaccel_tval4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_tval5", indent + 1, &(val[i].piaccel_tval5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piaccel_tval6", indent + 1, &(val[i].piaccel_tval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaccelscrn", indent + 1, &(val[i].piaccelscrn), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piacqnub", indent + 1, &(val[i].piacqnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piacsdefval", indent + 1, &(val[i].piacsdefval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piacsnub", indent + 1, &(val[i].piacsnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piacsval2", indent + 1, &(val[i].piacsval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piacsval3", indent + 1, &(val[i].piacsval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piacsval4", indent + 1, &(val[i].piacsval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piacsval5", indent + 1, &(val[i].piacsval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piacsval6", indent + 1, &(val[i].piacsval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piactim", indent + 1, &(val[i].piactim), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaddinub", indent + 1, &(val[i].piaddinub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaddscannub", indent + 1, &(val[i].piaddscannub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaddscantype", indent + 1, &(val[i].piaddscantype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piadvise", indent + 1, &(val[i].piadvise), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piadvt2map", indent + 1, &(val[i].piadvt2map), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piait", indent + 1, &(val[i].piait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piallowedrescantimenub", indent + 1, &(val[i].piallowedrescantimenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piamnub", indent + 1, &(val[i].piamnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piapcsi", indent + 1, &(val[i].piapcsi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaphasdefval", indent + 1, &(val[i].piaphasdefval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaphasenub", indent + 1, &(val[i].piaphasenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaphaseval2", indent + 1, &(val[i].piaphaseval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaphaseval3", indent + 1, &(val[i].piaphaseval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piaphaseval4", indent + 1, &(val[i].piaphaseval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piapx", indent + 1, &(val[i].piapx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piapxprfacc", indent + 1, &(val[i].piapxprfacc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piapxprfres", indent + 1, &(val[i].piapxprfres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piapxprfstepnub", indent + 1, &(val[i].piapxprfstepnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piapxprfstepval1", indent + 1, &(val[i].piapxprfstepval1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piapxprfstepval2", indent + 1, &(val[i].piapxprfstepval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piarccoilrestrict", indent + 1, &(val[i].piarccoilrestrict), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piasar", indent + 1, &(val[i].piasar), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piassetoverride", indent + 1, &(val[i].piassetoverride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piassetscrn", indent + 1, &(val[i].piassetscrn), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piautobspti", indent + 1, &(val[i].piautobspti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piautoetl", indent + 1, &(val[i].piautoetl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piautofa", indent + 1, &(val[i].piautofa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piautoirbands", indent + 1, &(val[i].piautoirbands), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piautonavtracker", indent + 1, &(val[i].piautonavtracker), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piautopause", indent + 1, &(val[i].piautopause), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piautophasenub", indent + 1, &(val[i].piautophasenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piautostep", indent + 1, &(val[i].piautostep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piautoti", indent + 1, &(val[i].piautoti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piautotrmode", indent + 1, &(val[i].piautotrmode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piautovoice", indent + 1, &(val[i].piautovoice), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pib1rms", indent + 1, &(val[i].pib1rms), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pibbandfilt", indent + 1, &(val[i].pibbandfilt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pibreathholdnub", indent + 1, &(val[i].pibreathholdnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pibsptidefval", indent + 1, &(val[i].pibsptidefval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pibsptinub", indent + 1, &(val[i].pibsptinub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pibsptival2", indent + 1, &(val[i].pibsptival2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pibsptival3", indent + 1, &(val[i].pibsptival3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pibsptival4", indent + 1, &(val[i].pibsptival4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pibsptival5", indent + 1, &(val[i].pibsptival5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pibsptival6", indent + 1, &(val[i].pibsptival6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piburstcooltime", indent + 1, &(val[i].piburstcooltime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piburstmode", indent + 1, &(val[i].piburstmode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pibval2", indent + 1, &(val[i].pibval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pibval3", indent + 1, &(val[i].pibval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pibval4", indent + 1, &(val[i].pibval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pibvalstab", indent + 1, &(val[i].pibvalstab), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pibvnub", indent + 1, &(val[i].pibvnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "picalmode", indent + 1, &(val[i].picalmode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "picalmodenub", indent + 1, &(val[i].picalmodenub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "picasar", indent + 1, &(val[i].picasar), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piccsat_obl", indent + 1, &(val[i].piccsat_obl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piccsatnub", indent + 1, &(val[i].piccsatnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pichemsatopt", indent + 1, &(val[i].pichemsatopt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pichop", indent + 1, &(val[i].pichop), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "picineiprot", indent + 1, &(val[i].picineiprot), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piclckcnt", indent + 1, &(val[i].piclckcnt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "picoilfastswitchrequired", indent + 1, &(val[i].picoilfastswitchrequired), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "picontrastwarning", indent + 1, &(val[i].picontrastwarning), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pics", indent + 1, &(val[i].pics), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "picsifov", indent + 1, &(val[i].picsifov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "picsimode", indent + 1, &(val[i].picsimode), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pidbdtper", indent + 1, &(val[i].pidbdtper), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pidbdtts", indent + 1, &(val[i].pidbdtts), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piddanub", indent + 1, &(val[i].piddanub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefaddimg", indent + 1, &(val[i].pidefaddimg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefallowedrescantime", indent + 1, &(val[i].pidefallowedrescantime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefarr", indent + 1, &(val[i].pidefarr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefbval", indent + 1, &(val[i].pidefbval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefcaldelay", indent + 1, &(val[i].pidefcaldelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefexcitemode", indent + 1, &(val[i].pidefexcitemode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pideffcaxis", indent + 1, &(val[i].pideffcaxis), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefflax", indent + 1, &(val[i].pidefflax), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefflrc", indent + 1, &(val[i].pidefflrc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefnavaccwin", indent + 1, &(val[i].pidefnavaccwin), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefnavautoaccwin", indent + 1, &(val[i].pidefnavautoaccwin), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefnavautotrigtime", indent + 1, &(val[i].pidefnavautotrigtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefnavmaxinterval", indent + 1, &(val[i].pidefnavmaxinterval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefnavpscpause", indent + 1, &(val[i].pidefnavpscpause), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefnavpsctime", indent + 1, &(val[i].pidefnavpsctime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefnavrrmeas", indent + 1, &(val[i].pidefnavrrmeas), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefnavrrmeastime", indent + 1, &(val[i].pidefnavrrmeastime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefnavsigenhance", indent + 1, &(val[i].pidefnavsigenhance), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefnavsltrack", indent + 1, &(val[i].pidefnavsltrack), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefnavtype", indent + 1, &(val[i].pidefnavtype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefnbh", indent + 1, &(val[i].pidefnbh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefovl", indent + 1, &(val[i].pidefovl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pidefphasset", indent + 1, &(val[i].pidefphasset), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pidefpostlabeldelay", indent + 1, &(val[i].pidefpostlabeldelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefproj", indent + 1, &(val[i].pidefproj), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pideframp", indent + 1, &(val[i].pideframp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pidefrbw", indent + 1, &(val[i].pidefrbw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefrtrep", indent + 1, &(val[i].pidefrtrep), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pidefslasset", indent + 1, &(val[i].pidefslasset), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidefslq", indent + 1, &(val[i].pidefslq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pideftouchamp", indent + 1, &(val[i].pideftouchamp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pideftouchax", indent + 1, &(val[i].pideftouchax), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pideftouchcyc", indent + 1, &(val[i].pideftouchcyc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pideftouchfreq", indent + 1, &(val[i].pideftouchfreq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pideftouchmegfreq", indent + 1, &(val[i].pideftouchmegfreq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pideftouchtphases", indent + 1, &(val[i].pideftouchtphases), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pidfmonfov", indent + 1, &(val[i].pidfmonfov), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pidfmonthick", indent + 1, &(val[i].pidfmonthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidiatdel1", indent + 1, &(val[i].pidiatdel1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pidifavgnex", indent + 1, &(val[i].pidifavgnex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidifaxnub", indent + 1, &(val[i].pidifaxnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidiffmode", indent + 1, &(val[i].pidiffmode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidiffproctype", indent + 1, &(val[i].pidiffproctype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidifnext2nub", indent + 1, &(val[i].pidifnext2nub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pidifnext2val2", indent + 1, &(val[i].pidifnext2val2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pidifnext2val3", indent + 1, &(val[i].pidifnext2val3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pidifnext2val4", indent + 1, &(val[i].pidifnext2val4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pidifnext2val5", indent + 1, &(val[i].pidifnext2val5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pidifnext2val6", indent + 1, &(val[i].pidifnext2val6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidifnextab", indent + 1, &(val[i].pidifnextab), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidifnumdirsdefval", indent + 1, &(val[i].pidifnumdirsdefval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidifnumdirsnub", indent + 1, &(val[i].pidifnumdirsnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidifnumdirsval2", indent + 1, &(val[i].pidifnumdirsval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidifnumdirsval3", indent + 1, &(val[i].pidifnumdirsval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidifnumdirsval4", indent + 1, &(val[i].pidifnumdirsval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidifnumt2defval", indent + 1, &(val[i].pidifnumt2defval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidifnumt2nub", indent + 1, &(val[i].pidifnumt2nub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidifnumt2val2", indent + 1, &(val[i].pidifnumt2val2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidifnumt2val3", indent + 1, &(val[i].pidifnumt2val3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidifnumt2val4", indent + 1, &(val[i].pidifnumt2val4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidifpage", indent + 1, &(val[i].pidifpage), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidifrecnub", indent + 1, &(val[i].pidifrecnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidixproc", indent + 1, &(val[i].pidixproc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidltime", indent + 1, &(val[i].pidltime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidmode", indent + 1, &(val[i].pidmode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidoshim", indent + 1, &(val[i].pidoshim), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidotg", indent + 1, &(val[i].pidotg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidrivemodenub", indent + 1, &(val[i].pidrivemodenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidualspinechonub", indent + 1, &(val[i].pidualspinechonub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pidyntgnub", indent + 1, &(val[i].pidyntgnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piechdefval", indent + 1, &(val[i].piechdefval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piechnub", indent + 1, &(val[i].piechnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piechval2", indent + 1, &(val[i].piechval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piechval3", indent + 1, &(val[i].piechval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piechval4", indent + 1, &(val[i].piechval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piechval5", indent + 1, &(val[i].piechval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piechval6", indent + 1, &(val[i].piechval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pieffbladewidth", indent + 1, &(val[i].pieffbladewidth), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pieffbladewidthdefval", indent + 1, &(val[i].pieffbladewidthdefval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pieffbladewidthnub", indent + 1, &(val[i].pieffbladewidthnub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piesar", indent + 1, &(val[i].piesar), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piesp", indent + 1, &(val[i].piesp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pietlnub", indent + 1, &(val[i].pietlnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pietlval2", indent + 1, &(val[i].pietlval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pietlval3", indent + 1, &(val[i].pietlval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pietlval4", indent + 1, &(val[i].pietlval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pietlval5", indent + 1, &(val[i].pietlval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pietlval6", indent + 1, &(val[i].pietlval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pietr", indent + 1, &(val[i].pietr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piexcitemodenub", indent + 1, &(val[i].piexcitemodenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifamode", indent + 1, &(val[i].pifamode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifanub", indent + 1, &(val[i].pifanub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifaval2", indent + 1, &(val[i].pifaval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifaval3", indent + 1, &(val[i].pifaval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifaval4", indent + 1, &(val[i].pifaval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifaval5", indent + 1, &(val[i].pifaval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifaval6", indent + 1, &(val[i].pifaval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifcinedefval", indent + 1, &(val[i].pifcinedefval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifcinenub", indent + 1, &(val[i].pifcinenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifcineval2", indent + 1, &(val[i].pifcineval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifcineval3", indent + 1, &(val[i].pifcineval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifcineval4", indent + 1, &(val[i].pifcineval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifilt4", indent + 1, &(val[i].pifilt4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifilt5", indent + 1, &(val[i].pifilt5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifilt6", indent + 1, &(val[i].pifilt6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifilt7", indent + 1, &(val[i].pifilt7), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piflanub", indent + 1, &(val[i].piflanub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piflosup", indent + 1, &(val[i].piflosup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piflrcnub", indent + 1, &(val[i].piflrcnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifmriscrn", indent + 1, &(val[i].pifmriscrn), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piforkvrgf", indent + 1, &(val[i].piforkvrgf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifovnub", indent + 1, &(val[i].pifovnub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pifovval2", indent + 1, &(val[i].pifovval2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pifovval3", indent + 1, &(val[i].pifovval3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pifovval4", indent + 1, &(val[i].pifovval4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pifovval5", indent + 1, &(val[i].pifovval5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pifovval6", indent + 1, &(val[i].pifovval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifphasenub", indent + 1, &(val[i].pifphasenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifphaseval2", indent + 1, &(val[i].pifphaseval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifphaseval3", indent + 1, &(val[i].pifphaseval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifphaseval4", indent + 1, &(val[i].pifphaseval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifphaseval5", indent + 1, &(val[i].pifphaseval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifphaseval6", indent + 1, &(val[i].pifphaseval6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pifractecho", indent + 1, &(val[i].pifractecho), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piframerate", indent + 1, &(val[i].piframerate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piframeratenub", indent + 1, &(val[i].piframeratenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifreqfovnub", indent + 1, &(val[i].pifreqfovnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pifsefcnub", indent + 1, &(val[i].pifsefcnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pigeosrot", indent + 1, &(val[i].pigeosrot), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pigirdefthick", indent + 1, &(val[i].pigirdefthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pigirmode", indent + 1, &(val[i].pigirmode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pigirscrn", indent + 1, &(val[i].pigirscrn), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pigradcoil", indent + 1, &(val[i].pigradcoil), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piharmonizenub", indent + 1, &(val[i].piharmonizenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pihoeccnub", indent + 1, &(val[i].pihoeccnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pihoeccvis", indent + 1, &(val[i].pihoeccvis), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pihrepnub", indent + 1, &(val[i].pihrepnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pihrepval2", indent + 1, &(val[i].pihrepval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pihrepval3", indent + 1, &(val[i].pihrepval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pihrepval4", indent + 1, &(val[i].pihrepval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pihrepval5", indent + 1, &(val[i].pihrepval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pihrepval6", indent + 1, &(val[i].pihrepval6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pihsar", indent + 1, &(val[i].pihsar), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piimages", indent + 1, &(val[i].piimages), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piimgoptlist", indent + 1, &(val[i].piimgoptlist), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piimgoptval2", indent + 1, &(val[i].piimgoptval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piimgoptval3", indent + 1, &(val[i].piimgoptval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piimgoptval4", indent + 1, &(val[i].piimgoptval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piinitstatnub", indent + 1, &(val[i].piinitstatnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piinplaneres", indent + 1, &(val[i].piinplaneres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piinrangetrmax", indent + 1, &(val[i].piinrangetrmax), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piinrangetrmin", indent + 1, &(val[i].piinrangetrmin), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piinvertfnub", indent + 1, &(val[i].piinvertfnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piinvertfvis", indent + 1, &(val[i].piinvertfvis), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piisil", indent + 1, &(val[i].piisil), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piisnub", indent + 1, &(val[i].piisnub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piisval2", indent + 1, &(val[i].piisval2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piisval3", indent + 1, &(val[i].piisval3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piisval4", indent + 1, &(val[i].piisval4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piisval5", indent + 1, &(val[i].piisval5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piisval6", indent + 1, &(val[i].piisval6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piisvaldef", indent + 1, &(val[i].piisvaldef), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pikt", indent + 1, &(val[i].pikt), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pilandmark", indent + 1, &(val[i].pilandmark), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pilocnub", indent + 1, &(val[i].pilocnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pilocval2", indent + 1, &(val[i].pilocval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pilocval3", indent + 1, &(val[i].pilocval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pilocval4", indent + 1, &(val[i].pilocval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pilocval5", indent + 1, &(val[i].pilocval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pilocval6", indent + 1, &(val[i].pilocval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimb", indent + 1, &(val[i].pimb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimintedifdef", indent + 1, &(val[i].pimintedifdef), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimintedifnub", indent + 1, &(val[i].pimintedifnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimixtime", indent + 1, &(val[i].pimixtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimonfovnub", indent + 1, &(val[i].pimonfovnub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pimonfovval2", indent + 1, &(val[i].pimonfovval2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pimonfovval3", indent + 1, &(val[i].pimonfovval3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pimonfovval4", indent + 1, &(val[i].pimonfovval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimonitor", indent + 1, &(val[i].pimonitor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimonthicknub", indent + 1, &(val[i].pimonthicknub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pimonthickval2", indent + 1, &(val[i].pimonthickval2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pimonthickval3", indent + 1, &(val[i].pimonthickval3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pimonthickval4", indent + 1, &(val[i].pimonthickval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimphscrn", indent + 1, &(val[i].pimphscrn), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimrsaps1", indent + 1, &(val[i].pimrsaps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimrsaps10", indent + 1, &(val[i].pimrsaps10), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimrsaps11", indent + 1, &(val[i].pimrsaps11), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimrsaps12", indent + 1, &(val[i].pimrsaps12), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimrsaps13", indent + 1, &(val[i].pimrsaps13), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimrsaps14", indent + 1, &(val[i].pimrsaps14), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimrsaps15", indent + 1, &(val[i].pimrsaps15), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimrsaps2", indent + 1, &(val[i].pimrsaps2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimrsaps3", indent + 1, &(val[i].pimrsaps3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimrsaps4", indent + 1, &(val[i].pimrsaps4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimrsaps5", indent + 1, &(val[i].pimrsaps5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimrsaps6", indent + 1, &(val[i].pimrsaps6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimrsaps7", indent + 1, &(val[i].pimrsaps7), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimrsaps8", indent + 1, &(val[i].pimrsaps8), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimrsaps9", indent + 1, &(val[i].pimrsaps9), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimrsapsflg", indent + 1, &(val[i].pimrsapsflg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pimscan", indent + 1, &(val[i].pimscan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimsdeaxnub", indent + 1, &(val[i].pimsdeaxnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimultigroup", indent + 1, &(val[i].pimultigroup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimultislab", indent + 1, &(val[i].pimultislab), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pimultistation", indent + 1, &(val[i].pimultistation), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavaccwinnub", indent + 1, &(val[i].pinavaccwinnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavaccwinval2", indent + 1, &(val[i].pinavaccwinval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavaccwinval3", indent + 1, &(val[i].pinavaccwinval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavaccwinval4", indent + 1, &(val[i].pinavaccwinval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavautoaccwinnub", indent + 1, &(val[i].pinavautoaccwinnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavautotrigtimenub", indent + 1, &(val[i].pinavautotrigtimenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavmaxintervalnub", indent + 1, &(val[i].pinavmaxintervalnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavmaxintervalval2", indent + 1, &(val[i].pinavmaxintervalval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavmaxintervalval3", indent + 1, &(val[i].pinavmaxintervalval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavmaxintervalval4", indent + 1, &(val[i].pinavmaxintervalval4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pinavmaxrr", indent + 1, &(val[i].pinavmaxrr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavpscpausenub", indent + 1, &(val[i].pinavpscpausenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavpsctimenub", indent + 1, &(val[i].pinavpsctimenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavrradjust", indent + 1, &(val[i].pinavrradjust), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavrrmeasmaxsl", indent + 1, &(val[i].pinavrrmeasmaxsl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavrrmeasnub", indent + 1, &(val[i].pinavrrmeasnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavrrmeasrtrep", indent + 1, &(val[i].pinavrrmeasrtrep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavrrmeastimenub", indent + 1, &(val[i].pinavrrmeastimenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavsigenhancenub", indent + 1, &(val[i].pinavsigenhancenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavsltracknub", indent + 1, &(val[i].pinavsltracknub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinavtypenub", indent + 1, &(val[i].pinavtypenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinbh", indent + 1, &(val[i].pinbh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinbhnub", indent + 1, &(val[i].pinbhnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinecho", indent + 1, &(val[i].pinecho), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinex", indent + 1, &(val[i].pinex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinexnub", indent + 1, &(val[i].pinexnub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pinexval2", indent + 1, &(val[i].pinexval2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pinexval3", indent + 1, &(val[i].pinexval3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pinexval4", indent + 1, &(val[i].pinexval4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pinexval5", indent + 1, &(val[i].pinexval5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pinexval6", indent + 1, &(val[i].pinexval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinoadc", indent + 1, &(val[i].pinoadc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinofreqoffset", indent + 1, &(val[i].pinofreqoffset), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinolr", indent + 1, &(val[i].pinolr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinsegnub", indent + 1, &(val[i].pinsegnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinsegval2", indent + 1, &(val[i].pinsegval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinsegval3", indent + 1, &(val[i].pinsegval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinsegval4", indent + 1, &(val[i].pinsegval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinsegval5", indent + 1, &(val[i].pinsegval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinslices", indent + 1, &(val[i].pinslices), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinspokesdefval", indent + 1, &(val[i].pinspokesdefval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinspokesnub", indent + 1, &(val[i].pinspokesnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinspokesstep", indent + 1, &(val[i].pinspokesstep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinspokesval2", indent + 1, &(val[i].pinspokesval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinspokesval3", indent + 1, &(val[i].pinspokesval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinspokesval4", indent + 1, &(val[i].pinspokesval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinspokesval5", indent + 1, &(val[i].pinspokesval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinspokesval6", indent + 1, &(val[i].pinspokesval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinumartlevels", indent + 1, &(val[i].pinumartlevels), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinumbnub", indent + 1, &(val[i].pinumbnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinumbval2", indent + 1, &(val[i].pinumbval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinumbval3", indent + 1, &(val[i].pinumbval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinumbval4", indent + 1, &(val[i].pinumbval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinumbval5", indent + 1, &(val[i].pinumbval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinumbval6", indent + 1, &(val[i].pinumbval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinumgir", indent + 1, &(val[i].pinumgir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinumsynbnub", indent + 1, &(val[i].pinumsynbnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinumsynbval2", indent + 1, &(val[i].pinumsynbval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinumsynbval3", indent + 1, &(val[i].pinumsynbval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinumsynbval4", indent + 1, &(val[i].pinumsynbval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinumsynbval5", indent + 1, &(val[i].pinumsynbval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pinumsynbval6", indent + 1, &(val[i].pinumsynbval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pioverlap", indent + 1, &(val[i].pioverlap), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pioversamplingfactordefval", indent + 1, &(val[i].pioversamplingfactordefval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pioversamplingfactornub", indent + 1, &(val[i].pioversamplingfactornub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pioversamplingfactorval2", indent + 1, &(val[i].pioversamplingfactorval2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pioversamplingfactorval3", indent + 1, &(val[i].pioversamplingfactorval3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pioversamplingfactorval4", indent + 1, &(val[i].pioversamplingfactorval4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pioversamplingfactorval5", indent + 1, &(val[i].pioversamplingfactorval5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pioversamplingfactorval6", indent + 1, &(val[i].pioversamplingfactorval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piovlnub", indent + 1, &(val[i].piovlnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pipaunub", indent + 1, &(val[i].pipaunub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pipautype", indent + 1, &(val[i].pipautype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pipauval2", indent + 1, &(val[i].pipauval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pipauval3", indent + 1, &(val[i].pipauval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pipauval4", indent + 1, &(val[i].pipauval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pipauval5", indent + 1, &(val[i].pipauval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pipauval6", indent + 1, &(val[i].pipauval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pipctovl", indent + 1, &(val[i].pipctovl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pipdhs_active", indent + 1, &(val[i].pipdhs_active), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piphaseimagenub", indent + 1, &(val[i].piphaseimagenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piphaseimageval2", indent + 1, &(val[i].piphaseimageval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piphaseimageval3", indent + 1, &(val[i].piphaseimageval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piphaseimageval4", indent + 1, &(val[i].piphaseimageval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piphasenub", indent + 1, &(val[i].piphasenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piphasfovnub", indent + 1, &(val[i].piphasfovnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piphasfovnub2", indent + 1, &(val[i].piphasfovnub2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piphasfovval1", indent + 1, &(val[i].piphasfovval1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piphasfovval2", indent + 1, &(val[i].piphasfovval2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piphasfovval3", indent + 1, &(val[i].piphasfovval3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piphasfovval4", indent + 1, &(val[i].piphasfovval4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piphasfovval5", indent + 1, &(val[i].piphasfovval5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piphasfovval6", indent + 1, &(val[i].piphasfovval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piphassetnub", indent + 1, &(val[i].piphassetnub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piphassetval1", indent + 1, &(val[i].piphassetval1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piphassetval2", indent + 1, &(val[i].piphassetval2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piphassetval3", indent + 1, &(val[i].piphassetval3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piphassetval4", indent + 1, &(val[i].piphassetval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piphslnub", indent + 1, &(val[i].piphslnub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pipostlabeldelay2", indent + 1, &(val[i].pipostlabeldelay2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pipostlabeldelay3", indent + 1, &(val[i].pipostlabeldelay3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pipostlabeldelay4", indent + 1, &(val[i].pipostlabeldelay4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pipostlabeldelay5", indent + 1, &(val[i].pipostlabeldelay5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pipostlabeldelay6", indent + 1, &(val[i].pipostlabeldelay6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pipostlabeldelaynub", indent + 1, &(val[i].pipostlabeldelaynub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piprojnub", indent + 1, &(val[i].piprojnub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pipsar", indent + 1, &(val[i].pipsar), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pipscdef", indent + 1, &(val[i].pipscdef), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pipscoptnub", indent + 1, &(val[i].pipscoptnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pipscshimtgnub", indent + 1, &(val[i].pipscshimtgnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pipscvol", indent + 1, &(val[i].pipscvol), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pipsdtrignub", indent + 1, &(val[i].pipsdtrignub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pipure", indent + 1, &(val[i].pipure), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirampnub", indent + 1, &(val[i].pirampnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirbwpage", indent + 1, &(val[i].pirbwpage), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirbwperpix", indent + 1, &(val[i].pirbwperpix), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pircb2nub", indent + 1, &(val[i].pircb2nub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pircb2val2", indent + 1, &(val[i].pircb2val2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pircb2val3", indent + 1, &(val[i].pircb2val3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pircb2val4", indent + 1, &(val[i].pircb2val4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pircb2val5", indent + 1, &(val[i].pircb2val5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pircb2val6", indent + 1, &(val[i].pircb2val6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pircbnub", indent + 1, &(val[i].pircbnub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pircbval2", indent + 1, &(val[i].pircbval2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pircbval3", indent + 1, &(val[i].pircbval3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pircbval4", indent + 1, &(val[i].pircbval4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pircbval5", indent + 1, &(val[i].pircbval5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pircbval6", indent + 1, &(val[i].pircbval6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pireconlag", indent + 1, &(val[i].pireconlag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirepactivenub", indent + 1, &(val[i].pirepactivenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pireprestnub", indent + 1, &(val[i].pireprestnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piresol", indent + 1, &(val[i].piresol), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirlcsi", indent + 1, &(val[i].pirlcsi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piroigrx", indent + 1, &(val[i].piroigrx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtait", indent + 1, &(val[i].pirtait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtb0nub", indent + 1, &(val[i].pirtb0nub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtb0vis", indent + 1, &(val[i].pirtb0vis), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtetr", indent + 1, &(val[i].pirtetr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtpointnub", indent + 1, &(val[i].pirtpointnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtpointval2", indent + 1, &(val[i].pirtpointval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtpointval3", indent + 1, &(val[i].pirtpointval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtpointval4", indent + 1, &(val[i].pirtpointval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtpointval5", indent + 1, &(val[i].pirtpointval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtpointval6", indent + 1, &(val[i].pirtpointval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtratenub", indent + 1, &(val[i].pirtratenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtrepnub", indent + 1, &(val[i].pirtrepnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtrepval2", indent + 1, &(val[i].pirtrepval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtrepval3", indent + 1, &(val[i].pirtrepval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtrepval4", indent + 1, &(val[i].pirtrepval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtrepval5", indent + 1, &(val[i].pirtrepval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtrepval6", indent + 1, &(val[i].pirtrepval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtrigwinnub", indent + 1, &(val[i].pirtrigwinnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtseqnub", indent + 1, &(val[i].pirtseqnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirttseq", indent + 1, &(val[i].pirttseq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtwindefval", indent + 1, &(val[i].pirtwindefval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtwinval2", indent + 1, &(val[i].pirtwinval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtwinval3", indent + 1, &(val[i].pirtwinval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtwinval4", indent + 1, &(val[i].pirtwinval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtwinval5", indent + 1, &(val[i].pirtwinval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pirtwinval6", indent + 1, &(val[i].pirtwinval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisatnub", indent + 1, &(val[i].pisatnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisatthick", indent + 1, &(val[i].pisatthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisatthickx", indent + 1, &(val[i].pisatthickx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisatthicky", indent + 1, &(val[i].pisatthicky), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisatthickz", indent + 1, &(val[i].pisatthickz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisaveinter", indent + 1, &(val[i].pisaveinter), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piscan_distance_toh", indent + 1, &(val[i].piscan_distance_toh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "piscancenter", indent + 1, &(val[i].piscancenter), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piscran", indent + 1, &(val[i].piscran), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisctim", indent + 1, &(val[i].pisctim), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pisctim1", indent + 1, &(val[i].pisctim1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pisctim2", indent + 1, &(val[i].pisctim2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pisctim3", indent + 1, &(val[i].pisctim3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pisctim4", indent + 1, &(val[i].pisctim4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pisctim5", indent + 1, &(val[i].pisctim5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pisctim6", indent + 1, &(val[i].pisctim6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piseparatesynbnub", indent + 1, &(val[i].piseparatesynbnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piserperph", indent + 1, &(val[i].piserperph), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisetup", indent + 1, &(val[i].pisetup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pishim2", indent + 1, &(val[i].pishim2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pishldctrl", indent + 1, &(val[i].pishldctrl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pishotnub", indent + 1, &(val[i].pishotnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pishotval2", indent + 1, &(val[i].pishotval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pishotval3", indent + 1, &(val[i].pishotval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pishotval4", indent + 1, &(val[i].pishotval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pishotval5", indent + 1, &(val[i].pishotval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pishotval6", indent + 1, &(val[i].pishotval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisicsi", indent + 1, &(val[i].pisicsi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisilentmr", indent + 1, &(val[i].pisilentmr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisioverlap", indent + 1, &(val[i].pisioverlap), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pislassetnub", indent + 1, &(val[i].pislassetnub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pislassetval1", indent + 1, &(val[i].pislassetval1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pislassetval2", indent + 1, &(val[i].pislassetval2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pislassetval3", indent + 1, &(val[i].pislassetval3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pislassetval4", indent + 1, &(val[i].pislassetval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pislblank", indent + 1, &(val[i].pislblank), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisldelnub", indent + 1, &(val[i].pisldelnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisldelval3", indent + 1, &(val[i].pisldelval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisldelval4", indent + 1, &(val[i].pisldelval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisldelval5", indent + 1, &(val[i].pisldelval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisldelval6", indent + 1, &(val[i].pisldelval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisliceordnub", indent + 1, &(val[i].pisliceordnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pislqnub", indent + 1, &(val[i].pislqnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pislquant", indent + 1, &(val[i].pislquant), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pislqval2", indent + 1, &(val[i].pislqval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pislqval3", indent + 1, &(val[i].pislqval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pislqval4", indent + 1, &(val[i].pislqval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pislqval5", indent + 1, &(val[i].pislqval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pislthicklabel", indent + 1, &(val[i].pislthicklabel), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pislthickstep", indent + 1, &(val[i].pislthickstep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pismode", indent + 1, &(val[i].pismode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pispecprescan", indent + 1, &(val[i].pispecprescan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pispssupnub", indent + 1, &(val[i].pispssupnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pistnub", indent + 1, &(val[i].pistnub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pistval2", indent + 1, &(val[i].pistval2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pistval3", indent + 1, &(val[i].pistval3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pistval4", indent + 1, &(val[i].pistval4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pistval5", indent + 1, &(val[i].pistval5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pistval6", indent + 1, &(val[i].pistval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisupnub", indent + 1, &(val[i].pisupnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piswapfc", indent + 1, &(val[i].piswapfc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisynbvalstab", indent + 1, &(val[i].pisynbvalstab), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pisystdel1", indent + 1, &(val[i].pisystdel1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pit2preptedefval", indent + 1, &(val[i].pit2preptedefval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pit2preptenub", indent + 1, &(val[i].pit2preptenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pit2prepteval2", indent + 1, &(val[i].pit2prepteval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pit2prepteval3", indent + 1, &(val[i].pit2prepteval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pit2prepteval4", indent + 1, &(val[i].pit2prepteval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pit2prepteval5", indent + 1, &(val[i].pit2prepteval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pit2prepteval6", indent + 1, &(val[i].pit2prepteval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitablemaxaccel", indent + 1, &(val[i].pitablemaxaccel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitablemaxdecel", indent + 1, &(val[i].pitablemaxdecel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitablemaxspeed", indent + 1, &(val[i].pitablemaxspeed), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pitableposition", indent + 1, &(val[i].pitableposition), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pitagangledefval", indent + 1, &(val[i].pitagangledefval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitaganglenub", indent + 1, &(val[i].pitaganglenub), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pitagangleval2", indent + 1, &(val[i].pitagangleval2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pitagangleval3", indent + 1, &(val[i].pitagangleval3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pitagangleval4", indent + 1, &(val[i].pitagangleval4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pitagangleval5", indent + 1, &(val[i].pitagangleval5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pitagangleval6", indent + 1, &(val[i].pitagangleval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitagging", indent + 1, &(val[i].pitagging), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitagspcdefval", indent + 1, &(val[i].pitagspcdefval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitagspcval2", indent + 1, &(val[i].pitagspcval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitagspcval3", indent + 1, &(val[i].pitagspcval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitagspcval4", indent + 1, &(val[i].pitagspcval4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pitbh", indent + 1, &(val[i].pitbh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pitbhlast", indent + 1, &(val[i].pitbhlast), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitdel1", indent + 1, &(val[i].pitdel1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitdel1nub", indent + 1, &(val[i].pitdel1nub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitdel1type", indent + 1, &(val[i].pitdel1type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pite1nub", indent + 1, &(val[i].pite1nub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pite1val2", indent + 1, &(val[i].pite1val2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pite1val3", indent + 1, &(val[i].pite1val3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pite1val4", indent + 1, &(val[i].pite1val4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pite1val5", indent + 1, &(val[i].pite1val5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pite1val6", indent + 1, &(val[i].pite1val6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pite2nub", indent + 1, &(val[i].pite2nub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pite2type", indent + 1, &(val[i].pite2type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pite2val2", indent + 1, &(val[i].pite2val2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pite2val3", indent + 1, &(val[i].pite2val3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pite2val4", indent + 1, &(val[i].pite2val4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pite2val5", indent + 1, &(val[i].pite2val5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pite2val6", indent + 1, &(val[i].pite2val6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitetr", indent + 1, &(val[i].pitetr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitetype", indent + 1, &(val[i].pitetype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitfeextra", indent + 1, &(val[i].pitfeextra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitidefval", indent + 1, &(val[i].pitidefval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitinub", indent + 1, &(val[i].pitinub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitissuet1defval", indent + 1, &(val[i].pitissuet1defval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitissuet1nub", indent + 1, &(val[i].pitissuet1nub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitissuet1val2", indent + 1, &(val[i].pitissuet1val2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitissuet1val3", indent + 1, &(val[i].pitissuet1val3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitissuet1val4", indent + 1, &(val[i].pitissuet1val4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitissuet1val5", indent + 1, &(val[i].pitissuet1val5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pititle", indent + 1, &(val[i].pititle), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pititype", indent + 1, &(val[i].pititype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitival2", indent + 1, &(val[i].pitival2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitival3", indent + 1, &(val[i].pitival3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitival4", indent + 1, &(val[i].pitival4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitival5", indent + 1, &(val[i].pitival5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitival6", indent + 1, &(val[i].pitival6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitlabeldefval", indent + 1, &(val[i].pitlabeldefval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitlabelnub", indent + 1, &(val[i].pitlabelnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitlabelstep", indent + 1, &(val[i].pitlabelstep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitlabelval2", indent + 1, &(val[i].pitlabelval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitlabelval3", indent + 1, &(val[i].pitlabelval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitlabelval4", indent + 1, &(val[i].pitlabelval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouch", indent + 1, &(val[i].pitouch), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchamp", indent + 1, &(val[i].pitouchamp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchampnub", indent + 1, &(val[i].pitouchampnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchampval2", indent + 1, &(val[i].pitouchampval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchampval3", indent + 1, &(val[i].pitouchampval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchampval4", indent + 1, &(val[i].pitouchampval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchaxnub", indent + 1, &(val[i].pitouchaxnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchaxval2", indent + 1, &(val[i].pitouchaxval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchaxval3", indent + 1, &(val[i].pitouchaxval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchaxval4", indent + 1, &(val[i].pitouchaxval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchaxval5", indent + 1, &(val[i].pitouchaxval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchcyc", indent + 1, &(val[i].pitouchcyc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchcycnub", indent + 1, &(val[i].pitouchcycnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchcycval2", indent + 1, &(val[i].pitouchcycval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchcycval3", indent + 1, &(val[i].pitouchcycval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchcycval4", indent + 1, &(val[i].pitouchcycval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchfreq", indent + 1, &(val[i].pitouchfreq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchfreqnub", indent + 1, &(val[i].pitouchfreqnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchfreqval2", indent + 1, &(val[i].pitouchfreqval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchfreqval3", indent + 1, &(val[i].pitouchfreqval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchfreqval4", indent + 1, &(val[i].pitouchfreqval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchmegfreqnub", indent + 1, &(val[i].pitouchmegfreqnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchmegfreqval2", indent + 1, &(val[i].pitouchmegfreqval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchmegfreqval3", indent + 1, &(val[i].pitouchmegfreqval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchmegfreqval4", indent + 1, &(val[i].pitouchmegfreqval4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pitouchmenc", indent + 1, &(val[i].pitouchmenc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchtphases", indent + 1, &(val[i].pitouchtphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchtphasesnub", indent + 1, &(val[i].pitouchtphasesnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchtphasesval2", indent + 1, &(val[i].pitouchtphasesval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchtphasesval3", indent + 1, &(val[i].pitouchtphasesval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitouchtphasesval4", indent + 1, &(val[i].pitouchtphasesval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitphasenub", indent + 1, &(val[i].pitphasenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitphaseval2", indent + 1, &(val[i].pitphaseval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitphaseval3", indent + 1, &(val[i].pitphaseval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitphaseval4", indent + 1, &(val[i].pitphaseval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitphaseval5", indent + 1, &(val[i].pitphaseval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitphaseval6", indent + 1, &(val[i].pitphaseval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitr", indent + 1, &(val[i].pitr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitracqnub", indent + 1, &(val[i].pitracqnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitracqval2", indent + 1, &(val[i].pitracqval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitracqval3", indent + 1, &(val[i].pitracqval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitracqval4", indent + 1, &(val[i].pitracqval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitracqval5", indent + 1, &(val[i].pitracqval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitracqval6", indent + 1, &(val[i].pitracqval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitrecoverydefval", indent + 1, &(val[i].pitrecoverydefval), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitrecoverynub", indent + 1, &(val[i].pitrecoverynub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitrecoverystep", indent + 1, &(val[i].pitrecoverystep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitrecoveryval2", indent + 1, &(val[i].pitrecoveryval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitrecoveryval3", indent + 1, &(val[i].pitrecoveryval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitrecoveryval4", indent + 1, &(val[i].pitrecoveryval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitrecoveryval5", indent + 1, &(val[i].pitrecoveryval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitrecoveryval6", indent + 1, &(val[i].pitrecoveryval6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pitres", indent + 1, &(val[i].pitres), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pitres2", indent + 1, &(val[i].pitres2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitres2nub", indent + 1, &(val[i].pitres2nub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitresnub", indent + 1, &(val[i].pitresnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitricksdelnub", indent + 1, &(val[i].pitricksdelnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitricksdelval3", indent + 1, &(val[i].pitricksdelval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitricksdelval4", indent + 1, &(val[i].pitricksdelval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitricksdelval5", indent + 1, &(val[i].pitricksdelval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitricksdelval6", indent + 1, &(val[i].pitricksdelval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitrigwinnub", indent + 1, &(val[i].pitrigwinnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitrnub", indent + 1, &(val[i].pitrnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitrval2", indent + 1, &(val[i].pitrval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitrval3", indent + 1, &(val[i].pitrval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitrval4", indent + 1, &(val[i].pitrval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitrval5", indent + 1, &(val[i].pitrval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitrval6", indent + 1, &(val[i].pitrval6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pitsar", indent + 1, &(val[i].pitsar), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pitscan", indent + 1, &(val[i].pitscan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitseq", indent + 1, &(val[i].pitseq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitseqnub", indent + 1, &(val[i].pitseqnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitseqtype", indent + 1, &(val[i].pitseqtype), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pitslice", indent + 1, &(val[i].pitslice), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitsp1", indent + 1, &(val[i].pitsp1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pitsp2", indent + 1, &(val[i].pitsp2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piuset", indent + 1, &(val[i].piuset), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piuset2", indent + 1, &(val[i].piuset2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pivascop", indent + 1, &(val[i].pivascop), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pivelnub", indent + 1, &(val[i].pivelnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pivestnub", indent + 1, &(val[i].pivestnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pivextras", indent + 1, &(val[i].pivextras), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piviewordernub", indent + 1, &(val[i].piviewordernub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piviews", indent + 1, &(val[i].piviews), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piviewseg", indent + 1, &(val[i].piviewseg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pivpsdef", indent + 1, &(val[i].pivpsdef), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pivsphasenub", indent + 1, &(val[i].pivsphasenub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pivsphaseval2", indent + 1, &(val[i].pivsphaseval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pivsphaseval3", indent + 1, &(val[i].pivsphaseval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pivsphaseval4", indent + 1, &(val[i].pivsphaseval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pivsphaseval5", indent + 1, &(val[i].pivsphaseval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pivsphaseval6", indent + 1, &(val[i].pivsphaseval6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pivsscan", indent + 1, &(val[i].pivsscan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pixmtband", indent + 1, &(val[i].pixmtband), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pixresnub", indent + 1, &(val[i].pixresnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pixresval2", indent + 1, &(val[i].pixresval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pixresval3", indent + 1, &(val[i].pixresval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pixresval4", indent + 1, &(val[i].pixresval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pixresval5", indent + 1, &(val[i].pixresval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pixresval6", indent + 1, &(val[i].pixresval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piyresnub", indent + 1, &(val[i].piyresnub), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piyresval2", indent + 1, &(val[i].piyresval2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piyresval3", indent + 1, &(val[i].piyresval3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piyresval4", indent + 1, &(val[i].piyresval4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piyresval5", indent + 1, &(val[i].piyresval5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "piyresval6", indent + 1, &(val[i].piyresval6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pizmult", indent + 1, &(val[i].pizmult), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pizoom_index", indent + 1, &(val[i].pizoom_index), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pos_hard180", indent + 1, &(val[i].pos_hard180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pos_moment_start", indent + 1, &(val[i].pos_moment_start), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pos_msde_start", indent + 1, &(val[i].pos_msde_start), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pos_rfgir01", indent + 1, &(val[i].pos_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pos_rfgir02", indent + 1, &(val[i].pos_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pos_start", indent + 1, &(val[i].pos_start), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pos_start_frir", indent + 1, &(val[i].pos_start_frir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pos_start_gzk", indent + 1, &(val[i].pos_start_gzk), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pos_start_ir", indent + 1, &(val[i].pos_start_ir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pos_start_ir_min", indent + 1, &(val[i].pos_start_ir_min), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pos_start_killer_rfgir01", indent + 1, &(val[i].pos_start_killer_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pos_start_killer_rfgir02", indent + 1, &(val[i].pos_start_killer_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pos_start_rfgir01", indent + 1, &(val[i].pos_start_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pos_start_rfgir02", indent + 1, &(val[i].pos_start_rfgir02), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pospowerx", indent + 1, &(val[i].pospowerx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pospowery", indent + 1, &(val[i].pospowery), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pospowerz", indent + 1, &(val[i].pospowerz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "post_lobes", indent + 1, &(val[i].post_lobes), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "post_osfp_weight", indent + 1, &(val[i].post_osfp_weight), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "powerx", indent + 1, &(val[i].powerx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "powery", indent + 1, &(val[i].powery), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "powerz", indent + 1, &(val[i].powerz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pre_lobes", indent + 1, &(val[i].pre_lobes), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pre_pass", indent + 1, &(val[i].pre_pass), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pre_rcvn_tr", indent + 1, &(val[i].pre_rcvn_tr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pre_slice", indent + 1, &(val[i].pre_slice), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "predicted_TG", indent + 1, &(val[i].predicted_TG), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "premid_rf90", indent + 1, &(val[i].premid_rf90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "prep_dda", indent + 1, &(val[i].prep_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "presscfh", indent + 1, &(val[i].presscfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "presscfh_cgate", indent + 1, &(val[i].presscfh_cgate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "presscfh_ctrl", indent + 1, &(val[i].presscfh_ctrl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "presscfh_debug", indent + 1, &(val[i].presscfh_debug), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "presscfh_fov", indent + 1, &(val[i].presscfh_fov), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "presscfh_fov_ratio", indent + 1, &(val[i].presscfh_fov_ratio), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "presscfh_ir_noselect", indent + 1, &(val[i].presscfh_ir_noselect), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "presscfh_ir_slthick", indent + 1, &(val[i].presscfh_ir_slthick), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "presscfh_minfov_ratio", indent + 1, &(val[i].presscfh_minfov_ratio), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "presscfh_minte", indent + 1, &(val[i].presscfh_minte), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "presscfh_outrange", indent + 1, &(val[i].presscfh_outrange), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "presscfh_override", indent + 1, &(val[i].presscfh_override), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "presscfh_pfov", indent + 1, &(val[i].presscfh_pfov), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "presscfh_pfov_ratio", indent + 1, &(val[i].presscfh_pfov_ratio), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "presscfh_slab_ratio", indent + 1, &(val[i].presscfh_slab_ratio), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "presscfh_slice", indent + 1, &(val[i].presscfh_slice), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "presscfh_slthick", indent + 1, &(val[i].presscfh_slthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "presscfh_wait_rf12", indent + 1, &(val[i].presscfh_wait_rf12), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "presscfh_wait_rf23", indent + 1, &(val[i].presscfh_wait_rf23), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "presscfh_wait_rf34", indent + 1, &(val[i].presscfh_wait_rf34), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "prevent_scan_under_emul", indent + 1, &(val[i].prevent_scan_under_emul), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "product_rf", indent + 1, &(val[i].product_rf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "profile_opvthick", indent + 1, &(val[i].profile_opvthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "project", indent + 1, &(val[i].project), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ps1_newgeo", indent + 1, &(val[i].ps1_newgeo), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ps1_rxcoil", indent + 1, &(val[i].ps1_rxcoil), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ps1_tr", indent + 1, &(val[i].ps1_tr), 1);
#endif
#ifdef SIZEOF_LOG_GRAD
    print_brsfc_LOG_GRAD(fp, "ps1loggrd", indent + 1, &(val[i].ps1loggrd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ps1obl_debug", indent + 1, &(val[i].ps1obl_debug), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ps1scale", indent + 1, &(val[i].ps1scale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ps2_dda", indent + 1, &(val[i].ps2_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ps2_dda_cal3d", indent + 1, &(val[i].ps2_dda_cal3d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ps2_dda_time_cal3d", indent + 1, &(val[i].ps2_dda_time_cal3d), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ps_crusher_area", indent + 1, &(val[i].ps_crusher_area), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pscahead", indent + 1, &(val[i].pscahead), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "psd_board_type", indent + 1, &(val[i].psd_board_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "psd_card_hdwr_delay", indent + 1, &(val[i].psd_card_hdwr_delay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "psd_grd_wait", indent + 1, &(val[i].psd_grd_wait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "psd_mantrig", indent + 1, &(val[i].psd_mantrig), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "psd_pscshim", indent + 1, &(val[i].psd_pscshim), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "psd_psctg", indent + 1, &(val[i].psd_psctg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "psd_rf_wait", indent + 1, &(val[i].psd_rf_wait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "psd_startta_override", indent + 1, &(val[i].psd_startta_override), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "psd_taps", indent + 1, &(val[i].psd_taps), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "psd_targetscale", indent + 1, &(val[i].psd_targetscale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "psd_tol_value", indent + 1, &(val[i].psd_tol_value), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "psd_zero", indent + 1, &(val[i].psd_zero), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "psdcrucial_debug", indent + 1, &(val[i].psdcrucial_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "psddebugcode", indent + 1, &(val[i].psddebugcode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "psddebugcode2", indent + 1, &(val[i].psddebugcode2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "psdtime_rfgir01", indent + 1, &(val[i].psdtime_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "psdtime_rfgir01_iso", indent + 1, &(val[i].psdtime_rfgir01_iso), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "psdtime_rfgir02", indent + 1, &(val[i].psdtime_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "psdtime_rfgir02_iso", indent + 1, &(val[i].psdtime_rfgir02_iso), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pulsepos", indent + 1, &(val[i].pulsepos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "pure_mix_tx_scale", indent + 1, &(val[i].pure_mix_tx_scale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw1_eff", indent + 1, &(val[i].pw1_eff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw2_eff", indent + 1, &(val[i].pw2_eff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_acqdtg1", indent + 1, &(val[i].pw_acqdtg1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_acqrs1", indent + 1, &(val[i].pw_acqrs1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_bsrf", indent + 1, &(val[i].pw_bsrf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_constant", indent + 1, &(val[i].pw_constant), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_contrfhubsel", indent + 1, &(val[i].pw_contrfhubsel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_contrfsel", indent + 1, &(val[i].pw_contrfsel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_csw_wait", indent + 1, &(val[i].pw_csw_wait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_dix_ssppost", indent + 1, &(val[i].pw_dix_ssppost), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_dix_ssppre", indent + 1, &(val[i].pw_dix_ssppre), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_dix_xpre", indent + 1, &(val[i].pw_dix_xpre), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_drcv", indent + 1, &(val[i].pw_drcv), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gate_isi", indent + 1, &(val[i].pw_gate_isi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gks", indent + 1, &(val[i].pw_gks), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1", indent + 1, &(val[i].pw_gx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1_frac", indent + 1, &(val[i].pw_gx1_frac), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1_full", indent + 1, &(val[i].pw_gx1_full), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1a", indent + 1, &(val[i].pw_gx1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1a_frac", indent + 1, &(val[i].pw_gx1a_frac), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1a_full", indent + 1, &(val[i].pw_gx1a_full), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1as", indent + 1, &(val[i].pw_gx1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1asa", indent + 1, &(val[i].pw_gx1asa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1asd", indent + 1, &(val[i].pw_gx1asd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1bftg", indent + 1, &(val[i].pw_gx1bftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1bftga", indent + 1, &(val[i].pw_gx1bftga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1bftgd", indent + 1, &(val[i].pw_gx1bftgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1bxtg", indent + 1, &(val[i].pw_gx1bxtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1bxtga", indent + 1, &(val[i].pw_gx1bxtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1bxtgd", indent + 1, &(val[i].pw_gx1bxtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1cfh", indent + 1, &(val[i].pw_gx1cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1cfha", indent + 1, &(val[i].pw_gx1cfha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1cfhd", indent + 1, &(val[i].pw_gx1cfhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1d", indent + 1, &(val[i].pw_gx1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1d_frac", indent + 1, &(val[i].pw_gx1d_frac), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1d_full", indent + 1, &(val[i].pw_gx1d_full), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1dtg", indent + 1, &(val[i].pw_gx1dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1dtga", indent + 1, &(val[i].pw_gx1dtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1dtgd", indent + 1, &(val[i].pw_gx1dtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1f", indent + 1, &(val[i].pw_gx1f), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1ftg", indent + 1, &(val[i].pw_gx1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1ftga", indent + 1, &(val[i].pw_gx1ftga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1ftgd", indent + 1, &(val[i].pw_gx1ftgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1mon", indent + 1, &(val[i].pw_gx1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1mona", indent + 1, &(val[i].pw_gx1mona), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1mond", indent + 1, &(val[i].pw_gx1mond), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1mps1", indent + 1, &(val[i].pw_gx1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1mps1a", indent + 1, &(val[i].pw_gx1mps1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1mps1d", indent + 1, &(val[i].pw_gx1mps1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1rs", indent + 1, &(val[i].pw_gx1rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1rsa", indent + 1, &(val[i].pw_gx1rsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1rsd", indent + 1, &(val[i].pw_gx1rsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1tm", indent + 1, &(val[i].pw_gx1tm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1tma", indent + 1, &(val[i].pw_gx1tma), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx1tmd", indent + 1, &(val[i].pw_gx1tmd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx2", indent + 1, &(val[i].pw_gx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx2a", indent + 1, &(val[i].pw_gx2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx2d", indent + 1, &(val[i].pw_gx2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx2dtg", indent + 1, &(val[i].pw_gx2dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx2dtga", indent + 1, &(val[i].pw_gx2dtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx2dtgd", indent + 1, &(val[i].pw_gx2dtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx2ftg", indent + 1, &(val[i].pw_gx2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx2ftga", indent + 1, &(val[i].pw_gx2ftga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx2ftgd", indent + 1, &(val[i].pw_gx2ftgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx2rs", indent + 1, &(val[i].pw_gx2rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx2rsa", indent + 1, &(val[i].pw_gx2rsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx2rsd", indent + 1, &(val[i].pw_gx2rsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx2test", indent + 1, &(val[i].pw_gx2test), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx2testa", indent + 1, &(val[i].pw_gx2testa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gx2testd", indent + 1, &(val[i].pw_gx2testd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxb", indent + 1, &(val[i].pw_gxb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxba", indent + 1, &(val[i].pw_gxba), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxbd", indent + 1, &(val[i].pw_gxbd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxbrsfc1", indent + 1, &(val[i].pw_gxbrsfc1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxbrsfc1a", indent + 1, &(val[i].pw_gxbrsfc1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxbrsfc1d", indent + 1, &(val[i].pw_gxbrsfc1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxbrsfc2", indent + 1, &(val[i].pw_gxbrsfc2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxbrsfc2a", indent + 1, &(val[i].pw_gxbrsfc2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxbrsfc2d", indent + 1, &(val[i].pw_gxbrsfc2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxfc", indent + 1, &(val[i].pw_gxfc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxfc_frac", indent + 1, &(val[i].pw_gxfc_frac), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxfc_full", indent + 1, &(val[i].pw_gxfc_full), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxfca", indent + 1, &(val[i].pw_gxfca), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxfca_frac", indent + 1, &(val[i].pw_gxfca_frac), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxfca_full", indent + 1, &(val[i].pw_gxfca_full), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxfcd", indent + 1, &(val[i].pw_gxfcd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxfcd_frac", indent + 1, &(val[i].pw_gxfcd_frac), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxfcd_full", indent + 1, &(val[i].pw_gxfcd_full), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxfcmon", indent + 1, &(val[i].pw_gxfcmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxfcmona", indent + 1, &(val[i].pw_gxfcmona), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxfcmond", indent + 1, &(val[i].pw_gxfcmond), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxflpk", indent + 1, &(val[i].pw_gxflpk), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxflpka", indent + 1, &(val[i].pw_gxflpka), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxflpkd", indent + 1, &(val[i].pw_gxflpkd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxflpvenc", indent + 1, &(val[i].pw_gxflpvenc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxflpvenca", indent + 1, &(val[i].pw_gxflpvenca), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxflpvencd", indent + 1, &(val[i].pw_gxflpvencd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxhyst1", indent + 1, &(val[i].pw_gxhyst1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxhyst1a", indent + 1, &(val[i].pw_gxhyst1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxhyst1d", indent + 1, &(val[i].pw_gxhyst1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxhyst2", indent + 1, &(val[i].pw_gxhyst2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxhyst2a", indent + 1, &(val[i].pw_gxhyst2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxhyst2d", indent + 1, &(val[i].pw_gxhyst2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkas", indent + 1, &(val[i].pw_gxkas), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkasa", indent + 1, &(val[i].pw_gxkasa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkasd", indent + 1, &(val[i].pw_gxkasd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkbsdtg", indent + 1, &(val[i].pw_gxkbsdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkbsdtga", indent + 1, &(val[i].pw_gxkbsdtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkbsdtgd", indent + 1, &(val[i].pw_gxkbsdtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkbsrs", indent + 1, &(val[i].pw_gxkbsrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkbsrsa", indent + 1, &(val[i].pw_gxkbsrsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkbsrsd", indent + 1, &(val[i].pw_gxkbsrsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkcs", indent + 1, &(val[i].pw_gxkcs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkcsa", indent + 1, &(val[i].pw_gxkcsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkcsd", indent + 1, &(val[i].pw_gxkcsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkdtg", indent + 1, &(val[i].pw_gxkdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkdtga", indent + 1, &(val[i].pw_gxkdtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkdtgd", indent + 1, &(val[i].pw_gxkdtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkfs", indent + 1, &(val[i].pw_gxkfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkfsa", indent + 1, &(val[i].pw_gxkfsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkfsd", indent + 1, &(val[i].pw_gxkfsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkill", indent + 1, &(val[i].pw_gxkill), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkilla", indent + 1, &(val[i].pw_gxkilla), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkilld", indent + 1, &(val[i].pw_gxkilld), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkrcvn", indent + 1, &(val[i].pw_gxkrcvn), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkrcvna", indent + 1, &(val[i].pw_gxkrcvna), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkrcvnd", indent + 1, &(val[i].pw_gxkrcvnd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkrs", indent + 1, &(val[i].pw_gxkrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkrsa", indent + 1, &(val[i].pw_gxkrsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkrsd", indent + 1, &(val[i].pw_gxkrsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxks", indent + 1, &(val[i].pw_gxks), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksa", indent + 1, &(val[i].pw_gxksa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksd", indent + 1, &(val[i].pw_gxksd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse1", indent + 1, &(val[i].pw_gxkse1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse1a", indent + 1, &(val[i].pw_gxkse1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse1d", indent + 1, &(val[i].pw_gxkse1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse2", indent + 1, &(val[i].pw_gxkse2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse2a", indent + 1, &(val[i].pw_gxkse2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse2d", indent + 1, &(val[i].pw_gxkse2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse3", indent + 1, &(val[i].pw_gxkse3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse3a", indent + 1, &(val[i].pw_gxkse3a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse3d", indent + 1, &(val[i].pw_gxkse3d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse4", indent + 1, &(val[i].pw_gxkse4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse4a", indent + 1, &(val[i].pw_gxkse4a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse4d", indent + 1, &(val[i].pw_gxkse4d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse5", indent + 1, &(val[i].pw_gxkse5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse5a", indent + 1, &(val[i].pw_gxkse5a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse5d", indent + 1, &(val[i].pw_gxkse5d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse6", indent + 1, &(val[i].pw_gxkse6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse6a", indent + 1, &(val[i].pw_gxkse6a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkse6d", indent + 1, &(val[i].pw_gxkse6d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksp", indent + 1, &(val[i].pw_gxksp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkspa", indent + 1, &(val[i].pw_gxkspa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkspd", indent + 1, &(val[i].pw_gxkspd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkssf", indent + 1, &(val[i].pw_gxkssf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkssfa", indent + 1, &(val[i].pw_gxkssfa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxkssfd", indent + 1, &(val[i].pw_gxkssfd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksx1", indent + 1, &(val[i].pw_gxksx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksx1a", indent + 1, &(val[i].pw_gxksx1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksx1d", indent + 1, &(val[i].pw_gxksx1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksx2", indent + 1, &(val[i].pw_gxksx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksx2a", indent + 1, &(val[i].pw_gxksx2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksx2d", indent + 1, &(val[i].pw_gxksx2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksy1", indent + 1, &(val[i].pw_gxksy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksy1a", indent + 1, &(val[i].pw_gxksy1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksy1d", indent + 1, &(val[i].pw_gxksy1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksy2", indent + 1, &(val[i].pw_gxksy2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksy2a", indent + 1, &(val[i].pw_gxksy2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksy2d", indent + 1, &(val[i].pw_gxksy2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksz1", indent + 1, &(val[i].pw_gxksz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksz1a", indent + 1, &(val[i].pw_gxksz1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksz1d", indent + 1, &(val[i].pw_gxksz1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksz2", indent + 1, &(val[i].pw_gxksz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksz2a", indent + 1, &(val[i].pw_gxksz2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxksz2d", indent + 1, &(val[i].pw_gxksz2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxrf1tm", indent + 1, &(val[i].pw_gxrf1tm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxrf1tma", indent + 1, &(val[i].pw_gxrf1tma), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxrf1tmd", indent + 1, &(val[i].pw_gxrf1tmd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxrf2cfh", indent + 1, &(val[i].pw_gxrf2cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxrf2cfha", indent + 1, &(val[i].pw_gxrf2cfha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxrf2cfhd", indent + 1, &(val[i].pw_gxrf2cfhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxrfsx1", indent + 1, &(val[i].pw_gxrfsx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxrfsx1a", indent + 1, &(val[i].pw_gxrfsx1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxrfsx1d", indent + 1, &(val[i].pw_gxrfsx1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxrfsx2", indent + 1, &(val[i].pw_gxrfsx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxrfsx2a", indent + 1, &(val[i].pw_gxrfsx2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxrfsx2d", indent + 1, &(val[i].pw_gxrfsx2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxspiral", indent + 1, &(val[i].pw_gxspiral), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxspiral2", indent + 1, &(val[i].pw_gxspiral2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxspoil", indent + 1, &(val[i].pw_gxspoil), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxspoil2", indent + 1, &(val[i].pw_gxspoil2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxspoil2a", indent + 1, &(val[i].pw_gxspoil2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxspoil2d", indent + 1, &(val[i].pw_gxspoil2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxspoila", indent + 1, &(val[i].pw_gxspoila), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxspoild", indent + 1, &(val[i].pw_gxspoild), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw", indent + 1, &(val[i].pw_gxw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw1ftg", indent + 1, &(val[i].pw_gxw1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw1ftga", indent + 1, &(val[i].pw_gxw1ftga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw1ftgd", indent + 1, &(val[i].pw_gxw1ftgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw1xtg", indent + 1, &(val[i].pw_gxw1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw1xtga", indent + 1, &(val[i].pw_gxw1xtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw1xtgd", indent + 1, &(val[i].pw_gxw1xtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw2", indent + 1, &(val[i].pw_gxw2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw2a", indent + 1, &(val[i].pw_gxw2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw2d", indent + 1, &(val[i].pw_gxw2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw2dtg", indent + 1, &(val[i].pw_gxw2dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw2dtga", indent + 1, &(val[i].pw_gxw2dtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw2dtgd", indent + 1, &(val[i].pw_gxw2dtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw2ftg", indent + 1, &(val[i].pw_gxw2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw2ftga", indent + 1, &(val[i].pw_gxw2ftga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw2ftgd", indent + 1, &(val[i].pw_gxw2ftgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw2ftgleft", indent + 1, &(val[i].pw_gxw2ftgleft), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw2rs", indent + 1, &(val[i].pw_gxw2rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw2rsa", indent + 1, &(val[i].pw_gxw2rsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw2rsd", indent + 1, &(val[i].pw_gxw2rsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw_frac", indent + 1, &(val[i].pw_gxw_frac), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxw_full", indent + 1, &(val[i].pw_gxw_full), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwa", indent + 1, &(val[i].pw_gxwa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwa_frac", indent + 1, &(val[i].pw_gxwa_frac), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwa_full", indent + 1, &(val[i].pw_gxwa_full), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwas", indent + 1, &(val[i].pw_gxwas), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwasa", indent + 1, &(val[i].pw_gxwasa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwasd", indent + 1, &(val[i].pw_gxwasd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwd", indent + 1, &(val[i].pw_gxwd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwd_frac", indent + 1, &(val[i].pw_gxwd_frac), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwd_full", indent + 1, &(val[i].pw_gxwd_full), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwd_temp", indent + 1, &(val[i].pw_gxwd_temp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwdtg", indent + 1, &(val[i].pw_gxwdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwdtga", indent + 1, &(val[i].pw_gxwdtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwdtgd", indent + 1, &(val[i].pw_gxwdtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwex", indent + 1, &(val[i].pw_gxwex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwex1", indent + 1, &(val[i].pw_gxwex1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwexa", indent + 1, &(val[i].pw_gxwexa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwexd", indent + 1, &(val[i].pw_gxwexd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwexmax", indent + 1, &(val[i].pw_gxwexmax), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwl", indent + 1, &(val[i].pw_gxwl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwmon", indent + 1, &(val[i].pw_gxwmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwmona", indent + 1, &(val[i].pw_gxwmona), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwmond", indent + 1, &(val[i].pw_gxwmond), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwmps1", indent + 1, &(val[i].pw_gxwmps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwmps1a", indent + 1, &(val[i].pw_gxwmps1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwmps1d", indent + 1, &(val[i].pw_gxwmps1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwr", indent + 1, &(val[i].pw_gxwr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwrs", indent + 1, &(val[i].pw_gxwrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwrsa", indent + 1, &(val[i].pw_gxwrsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gxwrsd", indent + 1, &(val[i].pw_gxwrsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1", indent + 1, &(val[i].pw_gy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1_tot", indent + 1, &(val[i].pw_gy1_tot), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1a", indent + 1, &(val[i].pw_gy1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1as", indent + 1, &(val[i].pw_gy1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1as_tot", indent + 1, &(val[i].pw_gy1as_tot), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1asa", indent + 1, &(val[i].pw_gy1asa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1asd", indent + 1, &(val[i].pw_gy1asd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1cfh", indent + 1, &(val[i].pw_gy1cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1cfha", indent + 1, &(val[i].pw_gy1cfha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1cfhd", indent + 1, &(val[i].pw_gy1cfhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1d", indent + 1, &(val[i].pw_gy1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1dtg", indent + 1, &(val[i].pw_gy1dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1dtga", indent + 1, &(val[i].pw_gy1dtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1dtgd", indent + 1, &(val[i].pw_gy1dtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1f", indent + 1, &(val[i].pw_gy1f), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1mon", indent + 1, &(val[i].pw_gy1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1mona", indent + 1, &(val[i].pw_gy1mona), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1mond", indent + 1, &(val[i].pw_gy1mond), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1mps1", indent + 1, &(val[i].pw_gy1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1mps1a", indent + 1, &(val[i].pw_gy1mps1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1mps1d", indent + 1, &(val[i].pw_gy1mps1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1r", indent + 1, &(val[i].pw_gy1r), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1r_tot", indent + 1, &(val[i].pw_gy1r_tot), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1ra", indent + 1, &(val[i].pw_gy1ra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1ras", indent + 1, &(val[i].pw_gy1ras), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1rasa", indent + 1, &(val[i].pw_gy1rasa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1rasd", indent + 1, &(val[i].pw_gy1rasd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1rd", indent + 1, &(val[i].pw_gy1rd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1rdtg", indent + 1, &(val[i].pw_gy1rdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1rdtga", indent + 1, &(val[i].pw_gy1rdtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1rdtgd", indent + 1, &(val[i].pw_gy1rdtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1rf", indent + 1, &(val[i].pw_gy1rf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1rrs", indent + 1, &(val[i].pw_gy1rrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1rrsa", indent + 1, &(val[i].pw_gy1rrsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1rrsd", indent + 1, &(val[i].pw_gy1rrsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1rs", indent + 1, &(val[i].pw_gy1rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1rsa", indent + 1, &(val[i].pw_gy1rsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1rsd", indent + 1, &(val[i].pw_gy1rsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1tm", indent + 1, &(val[i].pw_gy1tm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1tma", indent + 1, &(val[i].pw_gy1tma), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy1tmd", indent + 1, &(val[i].pw_gy1tmd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy2dtg", indent + 1, &(val[i].pw_gy2dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy2dtga", indent + 1, &(val[i].pw_gy2dtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy2dtgd", indent + 1, &(val[i].pw_gy2dtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy2rs", indent + 1, &(val[i].pw_gy2rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy2rsa", indent + 1, &(val[i].pw_gy2rsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gy2rsd", indent + 1, &(val[i].pw_gy2rsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyb", indent + 1, &(val[i].pw_gyb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyba", indent + 1, &(val[i].pw_gyba), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gybd", indent + 1, &(val[i].pw_gybd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gybrsfc1", indent + 1, &(val[i].pw_gybrsfc1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gybrsfc1a", indent + 1, &(val[i].pw_gybrsfc1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gybrsfc1d", indent + 1, &(val[i].pw_gybrsfc1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gybrsfc2", indent + 1, &(val[i].pw_gybrsfc2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gybrsfc2a", indent + 1, &(val[i].pw_gybrsfc2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gybrsfc2d", indent + 1, &(val[i].pw_gybrsfc2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gycylr", indent + 1, &(val[i].pw_gycylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gycylra", indent + 1, &(val[i].pw_gycylra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gycylratipup", indent + 1, &(val[i].pw_gycylratipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gycylrtipup", indent + 1, &(val[i].pw_gycylrtipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyfe", indent + 1, &(val[i].pw_gyfe), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyfe1", indent + 1, &(val[i].pw_gyfe1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyfe1a", indent + 1, &(val[i].pw_gyfe1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyfe1d", indent + 1, &(val[i].pw_gyfe1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyfe2", indent + 1, &(val[i].pw_gyfe2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyfe2a", indent + 1, &(val[i].pw_gyfe2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyfe2d", indent + 1, &(val[i].pw_gyfe2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyfea", indent + 1, &(val[i].pw_gyfea), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyfed", indent + 1, &(val[i].pw_gyfed), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyflpk", indent + 1, &(val[i].pw_gyflpk), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyflpka", indent + 1, &(val[i].pw_gyflpka), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyflpkd", indent + 1, &(val[i].pw_gyflpkd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyflpvenc", indent + 1, &(val[i].pw_gyflpvenc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyflpvenca", indent + 1, &(val[i].pw_gyflpvenca), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyflpvencd", indent + 1, &(val[i].pw_gyflpvencd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyhyst1", indent + 1, &(val[i].pw_gyhyst1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyhyst1a", indent + 1, &(val[i].pw_gyhyst1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyhyst1d", indent + 1, &(val[i].pw_gyhyst1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyhyst2", indent + 1, &(val[i].pw_gyhyst2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyhyst2a", indent + 1, &(val[i].pw_gyhyst2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyhyst2d", indent + 1, &(val[i].pw_gyhyst2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykcfh", indent + 1, &(val[i].pw_gykcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykcfha", indent + 1, &(val[i].pw_gykcfha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykcfhd", indent + 1, &(val[i].pw_gykcfhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykcfl", indent + 1, &(val[i].pw_gykcfl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykcfla", indent + 1, &(val[i].pw_gykcfla), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykcfld", indent + 1, &(val[i].pw_gykcfld), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykcs", indent + 1, &(val[i].pw_gykcs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykcsa", indent + 1, &(val[i].pw_gykcsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykcsd", indent + 1, &(val[i].pw_gykcsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykfs", indent + 1, &(val[i].pw_gykfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykfsa", indent + 1, &(val[i].pw_gykfsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykfsd", indent + 1, &(val[i].pw_gykfsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykill", indent + 1, &(val[i].pw_gykill), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykilla", indent + 1, &(val[i].pw_gykilla), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykilld", indent + 1, &(val[i].pw_gykilld), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykrcvn", indent + 1, &(val[i].pw_gykrcvn), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykrcvna", indent + 1, &(val[i].pw_gykrcvna), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykrcvnd", indent + 1, &(val[i].pw_gykrcvnd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyks", indent + 1, &(val[i].pw_gyks), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksa", indent + 1, &(val[i].pw_gyksa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksd", indent + 1, &(val[i].pw_gyksd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse1", indent + 1, &(val[i].pw_gykse1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse1a", indent + 1, &(val[i].pw_gykse1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse1d", indent + 1, &(val[i].pw_gykse1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse2", indent + 1, &(val[i].pw_gykse2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse2a", indent + 1, &(val[i].pw_gykse2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse2d", indent + 1, &(val[i].pw_gykse2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse3", indent + 1, &(val[i].pw_gykse3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse3a", indent + 1, &(val[i].pw_gykse3a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse3d", indent + 1, &(val[i].pw_gykse3d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse4", indent + 1, &(val[i].pw_gykse4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse4a", indent + 1, &(val[i].pw_gykse4a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse4d", indent + 1, &(val[i].pw_gykse4d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse5", indent + 1, &(val[i].pw_gykse5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse5a", indent + 1, &(val[i].pw_gykse5a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse5d", indent + 1, &(val[i].pw_gykse5d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse6", indent + 1, &(val[i].pw_gykse6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse6a", indent + 1, &(val[i].pw_gykse6a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykse6d", indent + 1, &(val[i].pw_gykse6d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksp", indent + 1, &(val[i].pw_gyksp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykspa", indent + 1, &(val[i].pw_gykspa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykspd", indent + 1, &(val[i].pw_gykspd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykssf", indent + 1, &(val[i].pw_gykssf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykssfa", indent + 1, &(val[i].pw_gykssfa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykssfd", indent + 1, &(val[i].pw_gykssfd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksx1", indent + 1, &(val[i].pw_gyksx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksx1a", indent + 1, &(val[i].pw_gyksx1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksx1d", indent + 1, &(val[i].pw_gyksx1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksx2", indent + 1, &(val[i].pw_gyksx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksx2a", indent + 1, &(val[i].pw_gyksx2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksx2d", indent + 1, &(val[i].pw_gyksx2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksy1", indent + 1, &(val[i].pw_gyksy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksy1a", indent + 1, &(val[i].pw_gyksy1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksy1d", indent + 1, &(val[i].pw_gyksy1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksy2", indent + 1, &(val[i].pw_gyksy2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksy2a", indent + 1, &(val[i].pw_gyksy2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksy2d", indent + 1, &(val[i].pw_gyksy2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksz1", indent + 1, &(val[i].pw_gyksz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksz1a", indent + 1, &(val[i].pw_gyksz1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksz1d", indent + 1, &(val[i].pw_gyksz1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksz2", indent + 1, &(val[i].pw_gyksz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksz2a", indent + 1, &(val[i].pw_gyksz2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyksz2d", indent + 1, &(val[i].pw_gyksz2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykxtgl", indent + 1, &(val[i].pw_gykxtgl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykxtgla", indent + 1, &(val[i].pw_gykxtgla), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykxtgld", indent + 1, &(val[i].pw_gykxtgld), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykxtgr", indent + 1, &(val[i].pw_gykxtgr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykxtgra", indent + 1, &(val[i].pw_gykxtgra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gykxtgrd", indent + 1, &(val[i].pw_gykxtgrd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf0kcfh", indent + 1, &(val[i].pw_gyrf0kcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf0kcfha", indent + 1, &(val[i].pw_gyrf0kcfha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf0kcfhd", indent + 1, &(val[i].pw_gyrf0kcfhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf1mon", indent + 1, &(val[i].pw_gyrf1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf1mona", indent + 1, &(val[i].pw_gyrf1mona), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf1mond", indent + 1, &(val[i].pw_gyrf1mond), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf1mps1", indent + 1, &(val[i].pw_gyrf1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf1mps1a", indent + 1, &(val[i].pw_gyrf1mps1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf1mps1d", indent + 1, &(val[i].pw_gyrf1mps1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf1tm", indent + 1, &(val[i].pw_gyrf1tm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf1tma", indent + 1, &(val[i].pw_gyrf1tma), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf1tmd", indent + 1, &(val[i].pw_gyrf1tmd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf1xtg", indent + 1, &(val[i].pw_gyrf1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf1xtga", indent + 1, &(val[i].pw_gyrf1xtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf1xtgd", indent + 1, &(val[i].pw_gyrf1xtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf2cfh", indent + 1, &(val[i].pw_gyrf2cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf2cfha", indent + 1, &(val[i].pw_gyrf2cfha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf2cfhd", indent + 1, &(val[i].pw_gyrf2cfhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf2lmon", indent + 1, &(val[i].pw_gyrf2lmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf2lmona", indent + 1, &(val[i].pw_gyrf2lmona), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf2lmond", indent + 1, &(val[i].pw_gyrf2lmond), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf2mon", indent + 1, &(val[i].pw_gyrf2mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf2mona", indent + 1, &(val[i].pw_gyrf2mona), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf2mond", indent + 1, &(val[i].pw_gyrf2mond), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf2rmon", indent + 1, &(val[i].pw_gyrf2rmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf2rmona", indent + 1, &(val[i].pw_gyrf2rmona), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf2rmond", indent + 1, &(val[i].pw_gyrf2rmond), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf3cfh", indent + 1, &(val[i].pw_gyrf3cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf3cfha", indent + 1, &(val[i].pw_gyrf3cfha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrf3cfhd", indent + 1, &(val[i].pw_gyrf3cfhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrfmontipup", indent + 1, &(val[i].pw_gyrfmontipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrfmontipupa", indent + 1, &(val[i].pw_gyrfmontipupa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrfmontipupd", indent + 1, &(val[i].pw_gyrfmontipupd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrfsy1", indent + 1, &(val[i].pw_gyrfsy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrfsy1a", indent + 1, &(val[i].pw_gyrfsy1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrfsy1d", indent + 1, &(val[i].pw_gyrfsy1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrfsy2", indent + 1, &(val[i].pw_gyrfsy2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrfsy2a", indent + 1, &(val[i].pw_gyrfsy2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyrfsy2d", indent + 1, &(val[i].pw_gyrfsy2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyspiral", indent + 1, &(val[i].pw_gyspiral), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyspiral2", indent + 1, &(val[i].pw_gyspiral2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyspoil", indent + 1, &(val[i].pw_gyspoil), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyspoil2", indent + 1, &(val[i].pw_gyspoil2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyspoil2a", indent + 1, &(val[i].pw_gyspoil2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyspoil2d", indent + 1, &(val[i].pw_gyspoil2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyspoila", indent + 1, &(val[i].pw_gyspoila), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gyspoild", indent + 1, &(val[i].pw_gyspoild), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1", indent + 1, &(val[i].pw_gz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1a", indent + 1, &(val[i].pw_gz1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1as", indent + 1, &(val[i].pw_gz1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1asa", indent + 1, &(val[i].pw_gz1asa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1asd", indent + 1, &(val[i].pw_gz1asd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1cfl", indent + 1, &(val[i].pw_gz1cfl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1cfla", indent + 1, &(val[i].pw_gz1cfla), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1cfld", indent + 1, &(val[i].pw_gz1cfld), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1d", indent + 1, &(val[i].pw_gz1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1dtg", indent + 1, &(val[i].pw_gz1dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1dtga", indent + 1, &(val[i].pw_gz1dtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1dtgd", indent + 1, &(val[i].pw_gz1dtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1ftg", indent + 1, &(val[i].pw_gz1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1ftga", indent + 1, &(val[i].pw_gz1ftga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1ftgd", indent + 1, &(val[i].pw_gz1ftgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1mon", indent + 1, &(val[i].pw_gz1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1mona", indent + 1, &(val[i].pw_gz1mona), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1mond", indent + 1, &(val[i].pw_gz1mond), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1mps1", indent + 1, &(val[i].pw_gz1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1mps1a", indent + 1, &(val[i].pw_gz1mps1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1mps1d", indent + 1, &(val[i].pw_gz1mps1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1rs", indent + 1, &(val[i].pw_gz1rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1rsa", indent + 1, &(val[i].pw_gz1rsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1rsd", indent + 1, &(val[i].pw_gz1rsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1s", indent + 1, &(val[i].pw_gz1s), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1sa", indent + 1, &(val[i].pw_gz1sa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1sd", indent + 1, &(val[i].pw_gz1sd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1xtg", indent + 1, &(val[i].pw_gz1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1xtga", indent + 1, &(val[i].pw_gz1xtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz1xtgd", indent + 1, &(val[i].pw_gz1xtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz2bftg", indent + 1, &(val[i].pw_gz2bftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz2bftga", indent + 1, &(val[i].pw_gz2bftga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz2bftgd", indent + 1, &(val[i].pw_gz2bftgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz2ftg", indent + 1, &(val[i].pw_gz2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz2ftga", indent + 1, &(val[i].pw_gz2ftga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz2ftgd", indent + 1, &(val[i].pw_gz2ftgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz2xtg", indent + 1, &(val[i].pw_gz2xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz2xtga", indent + 1, &(val[i].pw_gz2xtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz2xtgd", indent + 1, &(val[i].pw_gz2xtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz3ftg", indent + 1, &(val[i].pw_gz3ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz3ftga", indent + 1, &(val[i].pw_gz3ftga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gz3ftgd", indent + 1, &(val[i].pw_gz3ftgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzbrsfc1", indent + 1, &(val[i].pw_gzbrsfc1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzbrsfc1a", indent + 1, &(val[i].pw_gzbrsfc1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzbrsfc1d", indent + 1, &(val[i].pw_gzbrsfc1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzbrsfc1echo1", indent + 1, &(val[i].pw_gzbrsfc1echo1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzbrsfc1echo1a", indent + 1, &(val[i].pw_gzbrsfc1echo1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzbrsfc1echo1d", indent + 1, &(val[i].pw_gzbrsfc1echo1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzbrsfc1echo2", indent + 1, &(val[i].pw_gzbrsfc1echo2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzbrsfc1echo2a", indent + 1, &(val[i].pw_gzbrsfc1echo2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzbrsfc1echo2d", indent + 1, &(val[i].pw_gzbrsfc1echo2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzbrsfc2", indent + 1, &(val[i].pw_gzbrsfc2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzbrsfc2a", indent + 1, &(val[i].pw_gzbrsfc2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzbrsfc2d", indent + 1, &(val[i].pw_gzbrsfc2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzcomb", indent + 1, &(val[i].pw_gzcomb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzcomb_tot", indent + 1, &(val[i].pw_gzcomb_tot), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzcomba", indent + 1, &(val[i].pw_gzcomba), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzcombd", indent + 1, &(val[i].pw_gzcombd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzcombf", indent + 1, &(val[i].pw_gzcombf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzcombhtr", indent + 1, &(val[i].pw_gzcombhtr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzcombhtra", indent + 1, &(val[i].pw_gzcombhtra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzcombhtrd", indent + 1, &(val[i].pw_gzcombhtrd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzcombhtrf", indent + 1, &(val[i].pw_gzcombhtrf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzcylr", indent + 1, &(val[i].pw_gzcylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzcylra", indent + 1, &(val[i].pw_gzcylra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzcylratipup", indent + 1, &(val[i].pw_gzcylratipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzcylrtipup", indent + 1, &(val[i].pw_gzcylrtipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzfc", indent + 1, &(val[i].pw_gzfc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzfca", indent + 1, &(val[i].pw_gzfca), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzfcd", indent + 1, &(val[i].pw_gzfcd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzflpk", indent + 1, &(val[i].pw_gzflpk), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzflpka", indent + 1, &(val[i].pw_gzflpka), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzflpkd", indent + 1, &(val[i].pw_gzflpkd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzflpvenc", indent + 1, &(val[i].pw_gzflpvenc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzflpvenca", indent + 1, &(val[i].pw_gzflpvenca), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzflpvencd", indent + 1, &(val[i].pw_gzflpvencd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzk", indent + 1, &(val[i].pw_gzk), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzka", indent + 1, &(val[i].pw_gzka), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkas", indent + 1, &(val[i].pw_gzkas), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkasa", indent + 1, &(val[i].pw_gzkasa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkasd", indent + 1, &(val[i].pw_gzkasd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkbsdtg", indent + 1, &(val[i].pw_gzkbsdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkbsdtga", indent + 1, &(val[i].pw_gzkbsdtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkbsdtgd", indent + 1, &(val[i].pw_gzkbsdtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkbsrs", indent + 1, &(val[i].pw_gzkbsrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkbsrsa", indent + 1, &(val[i].pw_gzkbsrsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkbsrsd", indent + 1, &(val[i].pw_gzkbsrsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkcs", indent + 1, &(val[i].pw_gzkcs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkcsa", indent + 1, &(val[i].pw_gzkcsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkcsd", indent + 1, &(val[i].pw_gzkcsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkd", indent + 1, &(val[i].pw_gzkd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkdtg", indent + 1, &(val[i].pw_gzkdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkdtga", indent + 1, &(val[i].pw_gzkdtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkdtgd", indent + 1, &(val[i].pw_gzkdtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkfs", indent + 1, &(val[i].pw_gzkfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkfsa", indent + 1, &(val[i].pw_gzkfsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkfsd", indent + 1, &(val[i].pw_gzkfsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkgir01", indent + 1, &(val[i].pw_gzkgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkgir01a", indent + 1, &(val[i].pw_gzkgir01a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkgir01d", indent + 1, &(val[i].pw_gzkgir01d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkgir02", indent + 1, &(val[i].pw_gzkgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkgir02a", indent + 1, &(val[i].pw_gzkgir02a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkgir02d", indent + 1, &(val[i].pw_gzkgir02d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkill", indent + 1, &(val[i].pw_gzkill), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkilla", indent + 1, &(val[i].pw_gzkilla), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkilld", indent + 1, &(val[i].pw_gzkilld), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkiller", indent + 1, &(val[i].pw_gzkiller), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkillera", indent + 1, &(val[i].pw_gzkillera), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkillerd", indent + 1, &(val[i].pw_gzkillerd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkmon", indent + 1, &(val[i].pw_gzkmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkmona", indent + 1, &(val[i].pw_gzkmona), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkmond", indent + 1, &(val[i].pw_gzkmond), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkmontipup", indent + 1, &(val[i].pw_gzkmontipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkmontipupa", indent + 1, &(val[i].pw_gzkmontipupa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkmontipupd", indent + 1, &(val[i].pw_gzkmontipupd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkrcvn", indent + 1, &(val[i].pw_gzkrcvn), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkrcvna", indent + 1, &(val[i].pw_gzkrcvna), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkrcvnd", indent + 1, &(val[i].pw_gzkrcvnd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkrffrir", indent + 1, &(val[i].pw_gzkrffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkrffrira", indent + 1, &(val[i].pw_gzkrffrira), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkrffrird", indent + 1, &(val[i].pw_gzkrffrird), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkrs", indent + 1, &(val[i].pw_gzkrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkrsa", indent + 1, &(val[i].pw_gzkrsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkrsd", indent + 1, &(val[i].pw_gzkrsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzks", indent + 1, &(val[i].pw_gzks), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzks5fp", indent + 1, &(val[i].pw_gzks5fp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzks5fpa", indent + 1, &(val[i].pw_gzks5fpa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzks5fpd", indent + 1, &(val[i].pw_gzks5fpd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzksa", indent + 1, &(val[i].pw_gzksa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzksd", indent + 1, &(val[i].pw_gzksd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzksp", indent + 1, &(val[i].pw_gzksp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkspa", indent + 1, &(val[i].pw_gzkspa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkspd", indent + 1, &(val[i].pw_gzkspd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkssf", indent + 1, &(val[i].pw_gzkssf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkssfa", indent + 1, &(val[i].pw_gzkssfa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzkssfd", indent + 1, &(val[i].pw_gzkssfd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzp", indent + 1, &(val[i].pw_gzp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzpa", indent + 1, &(val[i].pw_gzpa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzpd", indent + 1, &(val[i].pw_gzpd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzpf", indent + 1, &(val[i].pw_gzpf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzphtr", indent + 1, &(val[i].pw_gzphtr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzphtra", indent + 1, &(val[i].pw_gzphtra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzphtrd", indent + 1, &(val[i].pw_gzphtrd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzphtrf", indent + 1, &(val[i].pw_gzphtrf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzptm", indent + 1, &(val[i].pw_gzptm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzptma", indent + 1, &(val[i].pw_gzptma), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzptmd", indent + 1, &(val[i].pw_gzptmd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf0", indent + 1, &(val[i].pw_gzrf0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf0a", indent + 1, &(val[i].pw_gzrf0a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf0cfh", indent + 1, &(val[i].pw_gzrf0cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf0cfha", indent + 1, &(val[i].pw_gzrf0cfha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf0cfhd", indent + 1, &(val[i].pw_gzrf0cfhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf0d", indent + 1, &(val[i].pw_gzrf0d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf0k", indent + 1, &(val[i].pw_gzrf0k), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf0ka", indent + 1, &(val[i].pw_gzrf0ka), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf0kd", indent + 1, &(val[i].pw_gzrf0kd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1", indent + 1, &(val[i].pw_gzrf1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1a", indent + 1, &(val[i].pw_gzrf1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1a_temp", indent + 1, &(val[i].pw_gzrf1a_temp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1as", indent + 1, &(val[i].pw_gzrf1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1asa", indent + 1, &(val[i].pw_gzrf1asa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1asd", indent + 1, &(val[i].pw_gzrf1asd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1cfh", indent + 1, &(val[i].pw_gzrf1cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1cfha", indent + 1, &(val[i].pw_gzrf1cfha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1cfhd", indent + 1, &(val[i].pw_gzrf1cfhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1cfl", indent + 1, &(val[i].pw_gzrf1cfl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1cfla", indent + 1, &(val[i].pw_gzrf1cfla), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1cfld", indent + 1, &(val[i].pw_gzrf1cfld), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1d", indent + 1, &(val[i].pw_gzrf1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1d_temp", indent + 1, &(val[i].pw_gzrf1d_temp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1dtg", indent + 1, &(val[i].pw_gzrf1dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1dtga", indent + 1, &(val[i].pw_gzrf1dtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1dtgd", indent + 1, &(val[i].pw_gzrf1dtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1ftg", indent + 1, &(val[i].pw_gzrf1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1ftga", indent + 1, &(val[i].pw_gzrf1ftga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1ftgd", indent + 1, &(val[i].pw_gzrf1ftgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1htr", indent + 1, &(val[i].pw_gzrf1htr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1htra", indent + 1, &(val[i].pw_gzrf1htra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1htrd", indent + 1, &(val[i].pw_gzrf1htrd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1lobe", indent + 1, &(val[i].pw_gzrf1lobe), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1mon", indent + 1, &(val[i].pw_gzrf1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1mona", indent + 1, &(val[i].pw_gzrf1mona), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1mond", indent + 1, &(val[i].pw_gzrf1mond), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1mps1", indent + 1, &(val[i].pw_gzrf1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1mps1a", indent + 1, &(val[i].pw_gzrf1mps1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1mps1d", indent + 1, &(val[i].pw_gzrf1mps1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1rs", indent + 1, &(val[i].pw_gzrf1rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1rsa", indent + 1, &(val[i].pw_gzrf1rsa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1rsd", indent + 1, &(val[i].pw_gzrf1rsd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1s", indent + 1, &(val[i].pw_gzrf1s), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1sa", indent + 1, &(val[i].pw_gzrf1sa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1sd", indent + 1, &(val[i].pw_gzrf1sd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1xtg", indent + 1, &(val[i].pw_gzrf1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1xtga", indent + 1, &(val[i].pw_gzrf1xtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf1xtgd", indent + 1, &(val[i].pw_gzrf1xtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2ftg", indent + 1, &(val[i].pw_gzrf2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2ftga", indent + 1, &(val[i].pw_gzrf2ftga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2ftgd", indent + 1, &(val[i].pw_gzrf2ftgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2lcfh", indent + 1, &(val[i].pw_gzrf2lcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2lcfha", indent + 1, &(val[i].pw_gzrf2lcfha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2lcfhd", indent + 1, &(val[i].pw_gzrf2lcfhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2lmps1", indent + 1, &(val[i].pw_gzrf2lmps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2lmps1a", indent + 1, &(val[i].pw_gzrf2lmps1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2lmps1d", indent + 1, &(val[i].pw_gzrf2lmps1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2mps1", indent + 1, &(val[i].pw_gzrf2mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2mps1a", indent + 1, &(val[i].pw_gzrf2mps1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2mps1d", indent + 1, &(val[i].pw_gzrf2mps1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2rcfh", indent + 1, &(val[i].pw_gzrf2rcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2rcfha", indent + 1, &(val[i].pw_gzrf2rcfha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2rcfhd", indent + 1, &(val[i].pw_gzrf2rcfhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2rmps1", indent + 1, &(val[i].pw_gzrf2rmps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2rmps1a", indent + 1, &(val[i].pw_gzrf2rmps1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2rmps1d", indent + 1, &(val[i].pw_gzrf2rmps1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2xtg", indent + 1, &(val[i].pw_gzrf2xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2xtga", indent + 1, &(val[i].pw_gzrf2xtga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf2xtgd", indent + 1, &(val[i].pw_gzrf2xtgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf3ftg", indent + 1, &(val[i].pw_gzrf3ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf3ftga", indent + 1, &(val[i].pw_gzrf3ftga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf3ftgd", indent + 1, &(val[i].pw_gzrf3ftgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf3lcfh", indent + 1, &(val[i].pw_gzrf3lcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf3lcfha", indent + 1, &(val[i].pw_gzrf3lcfha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf3lcfhd", indent + 1, &(val[i].pw_gzrf3lcfhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf3rcfh", indent + 1, &(val[i].pw_gzrf3rcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf3rcfha", indent + 1, &(val[i].pw_gzrf3rcfha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf3rcfhd", indent + 1, &(val[i].pw_gzrf3rcfhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf4cfh", indent + 1, &(val[i].pw_gzrf4cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf4cfha", indent + 1, &(val[i].pw_gzrf4cfha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf4cfhd", indent + 1, &(val[i].pw_gzrf4cfhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf4lcfh", indent + 1, &(val[i].pw_gzrf4lcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf4lcfha", indent + 1, &(val[i].pw_gzrf4lcfha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf4lcfhd", indent + 1, &(val[i].pw_gzrf4lcfhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf4rcfh", indent + 1, &(val[i].pw_gzrf4rcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf4rcfha", indent + 1, &(val[i].pw_gzrf4rcfha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrf4rcfhd", indent + 1, &(val[i].pw_gzrf4rcfhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrffrir", indent + 1, &(val[i].pw_gzrffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrffrira", indent + 1, &(val[i].pw_gzrffrira), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrffrird", indent + 1, &(val[i].pw_gzrffrird), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfgir01", indent + 1, &(val[i].pw_gzrfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfgir01a", indent + 1, &(val[i].pw_gzrfgir01a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfgir01d", indent + 1, &(val[i].pw_gzrfgir01d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfgir02", indent + 1, &(val[i].pw_gzrfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfgir02a", indent + 1, &(val[i].pw_gzrfgir02a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfgir02d", indent + 1, &(val[i].pw_gzrfgir02d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfs5fph", indent + 1, &(val[i].pw_gzrfs5fph), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfs5fpha", indent + 1, &(val[i].pw_gzrfs5fpha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfs5fphd", indent + 1, &(val[i].pw_gzrfs5fphd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse1", indent + 1, &(val[i].pw_gzrfse1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse1a", indent + 1, &(val[i].pw_gzrfse1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse1d", indent + 1, &(val[i].pw_gzrfse1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse2", indent + 1, &(val[i].pw_gzrfse2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse2a", indent + 1, &(val[i].pw_gzrfse2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse2d", indent + 1, &(val[i].pw_gzrfse2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse3", indent + 1, &(val[i].pw_gzrfse3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse3a", indent + 1, &(val[i].pw_gzrfse3a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse3d", indent + 1, &(val[i].pw_gzrfse3d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse4", indent + 1, &(val[i].pw_gzrfse4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse4a", indent + 1, &(val[i].pw_gzrfse4a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse4d", indent + 1, &(val[i].pw_gzrfse4d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse5", indent + 1, &(val[i].pw_gzrfse5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse5a", indent + 1, &(val[i].pw_gzrfse5a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse5d", indent + 1, &(val[i].pw_gzrfse5d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse6", indent + 1, &(val[i].pw_gzrfse6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse6a", indent + 1, &(val[i].pw_gzrfse6a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfse6d", indent + 1, &(val[i].pw_gzrfse6d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfssfh", indent + 1, &(val[i].pw_gzrfssfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfssfha", indent + 1, &(val[i].pw_gzrfssfha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfssfhd", indent + 1, &(val[i].pw_gzrfssfhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfsz1", indent + 1, &(val[i].pw_gzrfsz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfsz1a", indent + 1, &(val[i].pw_gzrfsz1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfsz1d", indent + 1, &(val[i].pw_gzrfsz1d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfsz2", indent + 1, &(val[i].pw_gzrfsz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfsz2a", indent + 1, &(val[i].pw_gzrfsz2a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzrfsz2d", indent + 1, &(val[i].pw_gzrfsz2d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzs5fphcomb", indent + 1, &(val[i].pw_gzs5fphcomb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzs5fphcomba", indent + 1, &(val[i].pw_gzs5fphcomba), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzs5fphcombd", indent + 1, &(val[i].pw_gzs5fphcombd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzssfhcomb", indent + 1, &(val[i].pw_gzssfhcomb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzssfhcomba", indent + 1, &(val[i].pw_gzssfhcomba), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzssfhcombd", indent + 1, &(val[i].pw_gzssfhcombd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzvlmin", indent + 1, &(val[i].pw_gzvlmin), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzvlw", indent + 1, &(val[i].pw_gzvlw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_hard180", indent + 1, &(val[i].pw_hard180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_hst", indent + 1, &(val[i].pw_hst), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi7", indent + 1, &(val[i].pw_isi7), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_cardiacsat", indent + 1, &(val[i].pw_isi_cardiacsat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_gir1", indent + 1, &(val[i].pw_isi_gir1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_gire01", indent + 1, &(val[i].pw_isi_gire01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_gire02", indent + 1, &(val[i].pw_isi_gire02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_girk01", indent + 1, &(val[i].pw_isi_girk01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_girk02", indent + 1, &(val[i].pw_isi_girk02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_sate1", indent + 1, &(val[i].pw_isi_sate1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_sate2", indent + 1, &(val[i].pw_isi_sate2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_sate3", indent + 1, &(val[i].pw_isi_sate3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_sate4", indent + 1, &(val[i].pw_isi_sate4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_sate5", indent + 1, &(val[i].pw_isi_sate5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_sate6", indent + 1, &(val[i].pw_isi_sate6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_satek1", indent + 1, &(val[i].pw_isi_satek1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_satek2", indent + 1, &(val[i].pw_isi_satek2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_satek3", indent + 1, &(val[i].pw_isi_satek3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_satek4", indent + 1, &(val[i].pw_isi_satek4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_satek5", indent + 1, &(val[i].pw_isi_satek5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_satek6", indent + 1, &(val[i].pw_isi_satek6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_satx1", indent + 1, &(val[i].pw_isi_satx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_satx2", indent + 1, &(val[i].pw_isi_satx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_satxk1", indent + 1, &(val[i].pw_isi_satxk1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_satxk2", indent + 1, &(val[i].pw_isi_satxk2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_saty1", indent + 1, &(val[i].pw_isi_saty1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_saty2", indent + 1, &(val[i].pw_isi_saty2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_satyk1", indent + 1, &(val[i].pw_isi_satyk1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_satyk2", indent + 1, &(val[i].pw_isi_satyk2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_satz1", indent + 1, &(val[i].pw_isi_satz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_satz2", indent + 1, &(val[i].pw_isi_satz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_satzk1", indent + 1, &(val[i].pw_isi_satzk1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_satzk2", indent + 1, &(val[i].pw_isi_satzk2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_slice1", indent + 1, &(val[i].pw_isi_slice1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isi_slice2", indent + 1, &(val[i].pw_isi_slice2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isigir", indent + 1, &(val[i].pw_isigir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isisat", indent + 1, &(val[i].pw_isisat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_isislice", indent + 1, &(val[i].pw_isislice), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_maps1", indent + 1, &(val[i].pw_maps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_maps2", indent + 1, &(val[i].pw_maps2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_mapx", indent + 1, &(val[i].pw_mapx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_mapy", indent + 1, &(val[i].pw_mapy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_mapz", indent + 1, &(val[i].pw_mapz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_mpomega_td0", indent + 1, &(val[i].pw_mpomega_td0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_mprho_td0", indent + 1, &(val[i].pw_mprho_td0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_mpssp_td0", indent + 1, &(val[i].pw_mpssp_td0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_mptheta_td0", indent + 1, &(val[i].pw_mptheta_td0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_mpx_td0", indent + 1, &(val[i].pw_mpx_td0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_mpy_td0", indent + 1, &(val[i].pw_mpy_td0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_mpz_td0", indent + 1, &(val[i].pw_mpz_td0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_nomcyl", indent + 1, &(val[i].pw_nomcyl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_omega_hs_rfcssat", indent + 1, &(val[i].pw_omega_hs_rfcssat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_omega_ir0", indent + 1, &(val[i].pw_omega_ir0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_omega_rffrir", indent + 1, &(val[i].pw_omega_rffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_omega_rfgir01", indent + 1, &(val[i].pw_omega_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_omega_rfgir02", indent + 1, &(val[i].pw_omega_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_omegarf0cfh", indent + 1, &(val[i].pw_omegarf0cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_postgxw1ftg", indent + 1, &(val[i].pw_postgxw1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_postgxw1ftga", indent + 1, &(val[i].pw_postgxw1ftga), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_postgxw1ftgd", indent + 1, &(val[i].pw_postgxw1ftgd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rampx", indent + 1, &(val[i].pw_rampx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rampy", indent + 1, &(val[i].pw_rampy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rampz", indent + 1, &(val[i].pw_rampz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rcvn_wait", indent + 1, &(val[i].pw_rcvn_wait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf0", indent + 1, &(val[i].pw_rf0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf0cfh", indent + 1, &(val[i].pw_rf0cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf1", indent + 1, &(val[i].pw_rf1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf180", indent + 1, &(val[i].pw_rf180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf1_full", indent + 1, &(val[i].pw_rf1_full), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf1_pre", indent + 1, &(val[i].pw_rf1_pre), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf1as", indent + 1, &(val[i].pw_rf1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf1cfh", indent + 1, &(val[i].pw_rf1cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf1cfl", indent + 1, &(val[i].pw_rf1cfl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf1dtg", indent + 1, &(val[i].pw_rf1dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf1ftg", indent + 1, &(val[i].pw_rf1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf1htr", indent + 1, &(val[i].pw_rf1htr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf1mon", indent + 1, &(val[i].pw_rf1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf1mps1", indent + 1, &(val[i].pw_rf1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf1rs", indent + 1, &(val[i].pw_rf1rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf1tm", indent + 1, &(val[i].pw_rf1tm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf1xtg", indent + 1, &(val[i].pw_rf1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf2cfh", indent + 1, &(val[i].pw_rf2cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf2ftg", indent + 1, &(val[i].pw_rf2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf2mon", indent + 1, &(val[i].pw_rf2mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf2mps1", indent + 1, &(val[i].pw_rf2mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf2xtg", indent + 1, &(val[i].pw_rf2xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf3cfh", indent + 1, &(val[i].pw_rf3cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf3ftg", indent + 1, &(val[i].pw_rf3ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf3xtg", indent + 1, &(val[i].pw_rf3xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf4cfh", indent + 1, &(val[i].pw_rf4cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf4xtg", indent + 1, &(val[i].pw_rf4xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rf90", indent + 1, &(val[i].pw_rf90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfbdtg", indent + 1, &(val[i].pw_rfbdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfbrs", indent + 1, &(val[i].pw_rfbrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfcssat", indent + 1, &(val[i].pw_rfcssat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfcssatcfh", indent + 1, &(val[i].pw_rfcssatcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfcylr", indent + 1, &(val[i].pw_rfcylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfcylrtipup", indent + 1, &(val[i].pw_rfcylrtipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfflp180", indent + 1, &(val[i].pw_rfflp180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfflp180_the", indent + 1, &(val[i].pw_rfflp180_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfflp90", indent + 1, &(val[i].pw_rfflp90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfflp90_the", indent + 1, &(val[i].pw_rfflp90_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfflp90r", indent + 1, &(val[i].pw_rfflp90r), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfflp90r_the", indent + 1, &(val[i].pw_rfflp90r_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rffrir", indent + 1, &(val[i].pw_rffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rffs", indent + 1, &(val[i].pw_rffs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfgir01", indent + 1, &(val[i].pw_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfgir02", indent + 1, &(val[i].pw_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfmontipup", indent + 1, &(val[i].pw_rfmontipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfs", indent + 1, &(val[i].pw_rfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfs5fph", indent + 1, &(val[i].pw_rfs5fph), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfse1", indent + 1, &(val[i].pw_rfse1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfse2", indent + 1, &(val[i].pw_rfse2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfse3", indent + 1, &(val[i].pw_rfse3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfse4", indent + 1, &(val[i].pw_rfse4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfse5", indent + 1, &(val[i].pw_rfse5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfse6", indent + 1, &(val[i].pw_rfse6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfssf", indent + 1, &(val[i].pw_rfssf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfssfh", indent + 1, &(val[i].pw_rfssfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfsx1", indent + 1, &(val[i].pw_rfsx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfsx2", indent + 1, &(val[i].pw_rfsx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfsy1", indent + 1, &(val[i].pw_rfsy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfsy2", indent + 1, &(val[i].pw_rfsy2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfsz1", indent + 1, &(val[i].pw_rfsz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rfsz2", indent + 1, &(val[i].pw_rfsz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rftipup", indent + 1, &(val[i].pw_rftipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_slice1", indent + 1, &(val[i].pw_rot_slice1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_slice2", indent + 1, &(val[i].pw_rot_slice2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_cardiacsat", indent + 1, &(val[i].pw_rot_update_cardiacsat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_e1", indent + 1, &(val[i].pw_rot_update_e1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_e2", indent + 1, &(val[i].pw_rot_update_e2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_e3", indent + 1, &(val[i].pw_rot_update_e3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_e4", indent + 1, &(val[i].pw_rot_update_e4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_e5", indent + 1, &(val[i].pw_rot_update_e5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_e6", indent + 1, &(val[i].pw_rot_update_e6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_ek1", indent + 1, &(val[i].pw_rot_update_ek1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_ek2", indent + 1, &(val[i].pw_rot_update_ek2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_ek3", indent + 1, &(val[i].pw_rot_update_ek3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_ek4", indent + 1, &(val[i].pw_rot_update_ek4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_ek5", indent + 1, &(val[i].pw_rot_update_ek5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_ek6", indent + 1, &(val[i].pw_rot_update_ek6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_gir", indent + 1, &(val[i].pw_rot_update_gir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_gire01", indent + 1, &(val[i].pw_rot_update_gire01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_girk01", indent + 1, &(val[i].pw_rot_update_girk01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_girk02", indent + 1, &(val[i].pw_rot_update_girk02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_rfgir02", indent + 1, &(val[i].pw_rot_update_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_x1", indent + 1, &(val[i].pw_rot_update_x1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_x2", indent + 1, &(val[i].pw_rot_update_x2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_xk1", indent + 1, &(val[i].pw_rot_update_xk1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_xk2", indent + 1, &(val[i].pw_rot_update_xk2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_y1", indent + 1, &(val[i].pw_rot_update_y1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_y2", indent + 1, &(val[i].pw_rot_update_y2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_yk1", indent + 1, &(val[i].pw_rot_update_yk1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_yk2", indent + 1, &(val[i].pw_rot_update_yk2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_z1", indent + 1, &(val[i].pw_rot_update_z1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_z2", indent + 1, &(val[i].pw_rot_update_z2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_zk1", indent + 1, &(val[i].pw_rot_update_zk1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rot_update_zk2", indent + 1, &(val[i].pw_rot_update_zk2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rotslice", indent + 1, &(val[i].pw_rotslice), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rotupdate", indent + 1, &(val[i].pw_rotupdate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rotupdate_gir", indent + 1, &(val[i].pw_rotupdate_gir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_rticfh", indent + 1, &(val[i].pw_rticfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_satrampx", indent + 1, &(val[i].pw_satrampx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_satrampy", indent + 1, &(val[i].pw_satrampy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_satrampz", indent + 1, &(val[i].pw_satrampz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_sdixon", indent + 1, &(val[i].pw_sdixon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_sdixon2", indent + 1, &(val[i].pw_sdixon2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_ss_rampz", indent + 1, &(val[i].pw_ss_rampz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_sticfh", indent + 1, &(val[i].pw_sticfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_thcylr", indent + 1, &(val[i].pw_thcylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_thcylrtipup", indent + 1, &(val[i].pw_thcylrtipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_thetarf1", indent + 1, &(val[i].pw_thetarf1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_xdelay", indent + 1, &(val[i].pw_xdelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_xdixon", indent + 1, &(val[i].pw_xdixon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_xrespgate", indent + 1, &(val[i].pw_xrespgate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_xticfh", indent + 1, &(val[i].pw_xticfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_y_ccs_null", indent + 1, &(val[i].pw_y_ccs_null), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_ydixon", indent + 1, &(val[i].pw_ydixon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_yticfh", indent + 1, &(val[i].pw_yticfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_zdixon", indent + 1, &(val[i].pw_zdixon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_zticfh", indent + 1, &(val[i].pw_zticfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "px_pwmtime", indent + 1, &(val[i].px_pwmtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "py_pwmtime", indent + 1, &(val[i].py_pwmtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pz_pwmtime", indent + 1, &(val[i].pz_pwmtime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "quickstep_flag", indent + 1, &(val[i].quickstep_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "radfb_flag", indent + 1, &(val[i].radfb_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ratio_rfflp90", indent + 1, &(val[i].ratio_rfflp90), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ratio_rfflp90r", indent + 1, &(val[i].ratio_rfflp90r), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rawdata", indent + 1, &(val[i].rawdata), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rawmode", indent + 1, &(val[i].rawmode), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rbw", indent + 1, &(val[i].rbw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rcvn_dda", indent + 1, &(val[i].rcvn_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rcvn_flag", indent + 1, &(val[i].rcvn_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rcvn_loops", indent + 1, &(val[i].rcvn_loops), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rcvn_nex", indent + 1, &(val[i].rcvn_nex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rcvn_tdaq", indent + 1, &(val[i].rcvn_tdaq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rcvn_tr", indent + 1, &(val[i].rcvn_tr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rcvn_xres", indent + 1, &(val[i].rcvn_xres), 1);
#endif
#ifdef SIZEOF_LOG_GRAD
    print_brsfc_LOG_GRAD(fp, "rcvnloggrd", indent + 1, &(val[i].rcvnloggrd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rcvr_ub_off", indent + 1, &(val[i].rcvr_ub_off), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rd_ext_dtg", indent + 1, &(val[i].rd_ext_dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rd_ext_rs", indent + 1, &(val[i].rd_ext_rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rda_mon", indent + 1, &(val[i].rda_mon), 1);
#endif
#ifdef SIZEOF_WF_PROCESSOR
    print_brsfc_WF_PROCESSOR(fp, "read_axis", indent + 1, &(val[i].read_axis), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "read_col", indent + 1, &(val[i].read_col), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "readmonloc", indent + 1, &(val[i].readmonloc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rec_mode", indent + 1, &(val[i].rec_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "recon_1024", indent + 1, &(val[i].recon_1024), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "recon_imag_image", indent + 1, &(val[i].recon_imag_image), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "recon_mag_image", indent + 1, &(val[i].recon_mag_image), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "recon_pha_image", indent + 1, &(val[i].recon_pha_image), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "recon_qmag_image", indent + 1, &(val[i].recon_qmag_image), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rectfov_npw_support", indent + 1, &(val[i].rectfov_npw_support), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "refocus", indent + 1, &(val[i].refocus), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "regViewOrderMode", indent + 1, &(val[i].regViewOrderMode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "region_order_mode", indent + 1, &(val[i].region_order_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "reilly_mode", indent + 1, &(val[i].reilly_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_dephase", indent + 1, &(val[i].res_dephase), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_dummyrf", indent + 1, &(val[i].res_dummyrf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gx1", indent + 1, &(val[i].res_gx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gxspiral", indent + 1, &(val[i].res_gxspiral), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gxspiral2", indent + 1, &(val[i].res_gxspiral2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gy1", indent + 1, &(val[i].res_gy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gy1r", indent + 1, &(val[i].res_gy1r), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gycylr", indent + 1, &(val[i].res_gycylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gycylra", indent + 1, &(val[i].res_gycylra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gycylratipup", indent + 1, &(val[i].res_gycylratipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gycylrtipup", indent + 1, &(val[i].res_gycylrtipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gyspiral", indent + 1, &(val[i].res_gyspiral), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gyspiral2", indent + 1, &(val[i].res_gyspiral2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gzcomb", indent + 1, &(val[i].res_gzcomb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gzcombhtr", indent + 1, &(val[i].res_gzcombhtr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gzcylr", indent + 1, &(val[i].res_gzcylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gzcylra", indent + 1, &(val[i].res_gzcylra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gzcylratipup", indent + 1, &(val[i].res_gzcylratipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gzcylrtipup", indent + 1, &(val[i].res_gzcylrtipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gzp", indent + 1, &(val[i].res_gzp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gzphtr", indent + 1, &(val[i].res_gzphtr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gzrf0", indent + 1, &(val[i].res_gzrf0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gzrf0cfh", indent + 1, &(val[i].res_gzrf0cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gzrf1", indent + 1, &(val[i].res_gzrf1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gzrffrir", indent + 1, &(val[i].res_gzrffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gzrfgir01", indent + 1, &(val[i].res_gzrfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gzrfgir02", indent + 1, &(val[i].res_gzrfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_gzvlw", indent + 1, &(val[i].res_gzvlw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_hard180", indent + 1, &(val[i].res_hard180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_omega_hs_rfcssat", indent + 1, &(val[i].res_omega_hs_rfcssat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_omega_ir0", indent + 1, &(val[i].res_omega_ir0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_omega_rffrir", indent + 1, &(val[i].res_omega_rffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_omega_rfgir01", indent + 1, &(val[i].res_omega_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_omega_rfgir02", indent + 1, &(val[i].res_omega_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_omegarf0cfh", indent + 1, &(val[i].res_omegarf0cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf0", indent + 1, &(val[i].res_rf0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf0cfh", indent + 1, &(val[i].res_rf0cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf1", indent + 1, &(val[i].res_rf1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf180", indent + 1, &(val[i].res_rf180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf1_full", indent + 1, &(val[i].res_rf1_full), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf1_temp", indent + 1, &(val[i].res_rf1_temp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf1as", indent + 1, &(val[i].res_rf1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf1cfh", indent + 1, &(val[i].res_rf1cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf1cfl", indent + 1, &(val[i].res_rf1cfl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf1dtg", indent + 1, &(val[i].res_rf1dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf1ftg", indent + 1, &(val[i].res_rf1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf1htr", indent + 1, &(val[i].res_rf1htr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf1mon", indent + 1, &(val[i].res_rf1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf1mps1", indent + 1, &(val[i].res_rf1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf1rs", indent + 1, &(val[i].res_rf1rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf1tm", indent + 1, &(val[i].res_rf1tm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf1xtg", indent + 1, &(val[i].res_rf1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf2cfh", indent + 1, &(val[i].res_rf2cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf2ftg", indent + 1, &(val[i].res_rf2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf2mon", indent + 1, &(val[i].res_rf2mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf2mps1", indent + 1, &(val[i].res_rf2mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf2xtg", indent + 1, &(val[i].res_rf2xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf3cfh", indent + 1, &(val[i].res_rf3cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf3ftg", indent + 1, &(val[i].res_rf3ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf3xtg", indent + 1, &(val[i].res_rf3xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf4cfh", indent + 1, &(val[i].res_rf4cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf4xtg", indent + 1, &(val[i].res_rf4xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rf90", indent + 1, &(val[i].res_rf90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfbdtg", indent + 1, &(val[i].res_rfbdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfbrs", indent + 1, &(val[i].res_rfbrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfcssat", indent + 1, &(val[i].res_rfcssat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfcylr", indent + 1, &(val[i].res_rfcylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfcylrtipup", indent + 1, &(val[i].res_rfcylrtipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfflp180", indent + 1, &(val[i].res_rfflp180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfflp180_the", indent + 1, &(val[i].res_rfflp180_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfflp90", indent + 1, &(val[i].res_rfflp90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfflp90_the", indent + 1, &(val[i].res_rfflp90_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfflp90r", indent + 1, &(val[i].res_rfflp90r), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfflp90r_the", indent + 1, &(val[i].res_rfflp90r_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rffrir", indent + 1, &(val[i].res_rffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rffs", indent + 1, &(val[i].res_rffs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfgir01", indent + 1, &(val[i].res_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfgir02", indent + 1, &(val[i].res_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfmontipup", indent + 1, &(val[i].res_rfmontipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfs5fph", indent + 1, &(val[i].res_rfs5fph), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfse1", indent + 1, &(val[i].res_rfse1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfse2", indent + 1, &(val[i].res_rfse2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfse3", indent + 1, &(val[i].res_rfse3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfse4", indent + 1, &(val[i].res_rfse4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfse5", indent + 1, &(val[i].res_rfse5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfse6", indent + 1, &(val[i].res_rfse6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfssf", indent + 1, &(val[i].res_rfssf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfssfh", indent + 1, &(val[i].res_rfssfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfsx1", indent + 1, &(val[i].res_rfsx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfsx2", indent + 1, &(val[i].res_rfsx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfsy1", indent + 1, &(val[i].res_rfsy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfsy2", indent + 1, &(val[i].res_rfsy2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfsz1", indent + 1, &(val[i].res_rfsz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rfsz2", indent + 1, &(val[i].res_rfsz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_rftipup", indent + 1, &(val[i].res_rftipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_thcylr", indent + 1, &(val[i].res_thcylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_thcylrtipup", indent + 1, &(val[i].res_thcylrtipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_thetarf1", indent + 1, &(val[i].res_thetarf1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_thetarfbdtg", indent + 1, &(val[i].res_thetarfbdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "res_thetarfbrs", indent + 1, &(val[i].res_thetarfbrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "resp_centk_percent", indent + 1, &(val[i].resp_centk_percent), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "resp_dda", indent + 1, &(val[i].resp_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "resp_gate_trig_sw", indent + 1, &(val[i].resp_gate_trig_sw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "resp_nex", indent + 1, &(val[i].resp_nex), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "respdc", indent + 1, &(val[i].respdc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "respgate_flag", indent + 1, &(val[i].respgate_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "respseqcore", indent + 1, &(val[i].respseqcore), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "retropc_extra", indent + 1, &(val[i].retropc_extra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "reverseLoopOrder_flag", indent + 1, &(val[i].reverseLoopOrder_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "reverse_centric_flag", indent + 1, &(val[i].reverse_centric_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "reverse_ellipt_flag", indent + 1, &(val[i].reverse_ellipt_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "reverse_first_region_flag", indent + 1, &(val[i].reverse_first_region_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "reverse_views", indent + 1, &(val[i].reverse_views), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rewinder_flag", indent + 1, &(val[i].rewinder_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rewinding_time", indent + 1, &(val[i].rewinding_time), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rf0_phase", indent + 1, &(val[i].rf0_phase), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rf0_pulse_type", indent + 1, &(val[i].rf0_pulse_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rf1_pulse_type", indent + 1, &(val[i].rf1_pulse_type), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rf1dtg_scale", indent + 1, &(val[i].rf1dtg_scale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rf1dtg_type", indent + 1, &(val[i].rf1dtg_type), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rf1mon_shift", indent + 1, &(val[i].rf1mon_shift), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rf1rs_scale", indent + 1, &(val[i].rf1rs_scale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rf1rs_type", indent + 1, &(val[i].rf1rs_type), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rf2mon_shift", indent + 1, &(val[i].rf2mon_shift), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rf_scale_fac", indent + 1, &(val[i].rf_scale_fac), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfb1opt_counter", indent + 1, &(val[i].rfb1opt_counter), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfb1opt_flag", indent + 1, &(val[i].rfb1opt_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfconf", indent + 1, &(val[i].rfconf), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rffrir_phase", indent + 1, &(val[i].rffrir_phase), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rfgir01_phase", indent + 1, &(val[i].rfgir01_phase), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfgir01_start", indent + 1, &(val[i].rfgir01_start), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfgir01_time", indent + 1, &(val[i].rfgir01_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfgir01_type", indent + 1, &(val[i].rfgir01_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfgir01_wait", indent + 1, &(val[i].rfgir01_wait), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rfgir02_phase", indent + 1, &(val[i].rfgir02_phase), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfgir02_start", indent + 1, &(val[i].rfgir02_start), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfgir02_time", indent + 1, &(val[i].rfgir02_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfgir02_type", indent + 1, &(val[i].rfgir02_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfgir02_wait", indent + 1, &(val[i].rfgir02_wait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfsafetyopt_timeflag", indent + 1, &(val[i].rfsafetyopt_timeflag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rfshim_b1factor", indent + 1, &(val[i].rfshim_b1factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfshim_baseline", indent + 1, &(val[i].rfshim_baseline), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfshim_etl", indent + 1, &(val[i].rfshim_etl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rfshim_flipangle", indent + 1, &(val[i].rfshim_flipangle), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rfshim_fov", indent + 1, &(val[i].rfshim_fov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfshim_ptsize", indent + 1, &(val[i].rfshim_ptsize), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfshim_slquant", indent + 1, &(val[i].rfshim_slquant), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rfshim_slthick", indent + 1, &(val[i].rfshim_slthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfshim_xres", indent + 1, &(val[i].rfshim_xres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfshim_yres", indent + 1, &(val[i].rfshim_yres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfslot_hard180", indent + 1, &(val[i].rfslot_hard180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfslot_omega_hs_rfcssat", indent + 1, &(val[i].rfslot_omega_hs_rfcssat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfslot_omega_ir0", indent + 1, &(val[i].rfslot_omega_ir0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfslot_omega_rffrir", indent + 1, &(val[i].rfslot_omega_rffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfslot_omega_rfgir01", indent + 1, &(val[i].rfslot_omega_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfslot_omega_rfgir02", indent + 1, &(val[i].rfslot_omega_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfslot_omegarf0cfh", indent + 1, &(val[i].rfslot_omegarf0cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfslot_rf90", indent + 1, &(val[i].rfslot_rf90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfslot_rfflp180", indent + 1, &(val[i].rfslot_rfflp180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfslot_rfflp180_the", indent + 1, &(val[i].rfslot_rfflp180_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfslot_rfflp90", indent + 1, &(val[i].rfslot_rfflp90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfslot_rfflp90_the", indent + 1, &(val[i].rfslot_rfflp90_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfslot_rfflp90r", indent + 1, &(val[i].rfslot_rfflp90r), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfslot_rfflp90r_the", indent + 1, &(val[i].rfslot_rfflp90r_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfslot_rftipup", indent + 1, &(val[i].rfslot_rftipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rftype", indent + 1, &(val[i].rftype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rfupacv", indent + 1, &(val[i].rfupacv), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rgfeature_enable", indent + 1, &(val[i].rgfeature_enable), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rh2dscale", indent + 1, &(val[i].rh2dscale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rh3dgw_interptype", indent + 1, &(val[i].rh3dgw_interptype), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rh3dscale", indent + 1, &(val[i].rh3dscale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rh3dwina", indent + 1, &(val[i].rh3dwina), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rh3dwinq", indent + 1, &(val[i].rh3dwinq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rh3dwintype", indent + 1, &(val[i].rh3dwintype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhFillMapLSW", indent + 1, &(val[i].rhFillMapLSW), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhFillMapMSW", indent + 1, &(val[i].rhFillMapMSW), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rh_ime_clariview_edge", indent + 1, &(val[i].rh_ime_clariview_edge), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rh_ime_clariview_focus", indent + 1, &(val[i].rh_ime_clariview_focus), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rh_ime_clariview_smooth", indent + 1, &(val[i].rh_ime_clariview_smooth), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rh_ime_clariview_type", indent + 1, &(val[i].rh_ime_clariview_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rh_ime_definefilter_nr", indent + 1, &(val[i].rh_ime_definefilter_nr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rh_ime_definefilter_sh", indent + 1, &(val[i].rh_ime_definefilter_sh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rh_ime_scic_edge", indent + 1, &(val[i].rh_ime_scic_edge), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rh_ime_scic_enable", indent + 1, &(val[i].rh_ime_scic_enable), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rh_ime_scic_focus", indent + 1, &(val[i].rh_ime_scic_focus), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rh_ime_scic_gauss", indent + 1, &(val[i].rh_ime_scic_gauss), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rh_ime_scic_reduction", indent + 1, &(val[i].rh_ime_scic_reduction), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rh_ime_scic_smooth", indent + 1, &(val[i].rh_ime_scic_smooth), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rh_ime_scic_threshold", indent + 1, &(val[i].rh_ime_scic_threshold), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rh_low_pass_nex_filter_width", indent + 1, &(val[i].rh_low_pass_nex_filter_width), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rh_rc_enhance_enable", indent + 1, &(val[i].rh_rc_enhance_enable), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhalpha", indent + 1, &(val[i].rhalpha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhalt", indent + 1, &(val[i].rhalt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhapfov", indent + 1, &(val[i].rhapfov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhaphases", indent + 1, &(val[i].rhaphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhapp", indent + 1, &(val[i].rhapp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhapp_option", indent + 1, &(val[i].rhapp_option), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhasl_perf_weighted_scale", indent + 1, &(val[i].rhasl_perf_weighted_scale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhasset", indent + 1, &(val[i].rhasset), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhasset_R", indent + 1, &(val[i].rhasset_R), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhasset_alt_cal", indent + 1, &(val[i].rhasset_alt_cal), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhasset_calthresh", indent + 1, &(val[i].rhasset_calthresh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhasset_localTx", indent + 1, &(val[i].rhasset_localTx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhasset_phases", indent + 1, &(val[i].rhasset_phases), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhasset_slwrap", indent + 1, &(val[i].rhasset_slwrap), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhasset_torso", indent + 1, &(val[i].rhasset_torso), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhassetsl_R", indent + 1, &(val[i].rhassetsl_R), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhb0map", indent + 1, &(val[i].rhb0map), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhblank", indent + 1, &(val[i].rhblank), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhbline", indent + 1, &(val[i].rhbline), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhbp_corr", indent + 1, &(val[i].rhbp_corr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhcal_nex_vector", indent + 1, &(val[i].rhcal_nex_vector), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhcal_options", indent + 1, &(val[i].rhcal_options), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhcal_pass_set_vector", indent + 1, &(val[i].rhcal_pass_set_vector), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhcal_weight_vector", indent + 1, &(val[i].rhcal_weight_vector), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhcalmode", indent + 1, &(val[i].rhcalmode), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhchannel_combine_filter_beta", indent + 1, &(val[i].rhchannel_combine_filter_beta), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhchannel_combine_filter_type", indent + 1, &(val[i].rhchannel_combine_filter_type), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhchannel_combine_filter_width", indent + 1, &(val[i].rhchannel_combine_filter_width), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhchannel_combine_method", indent + 1, &(val[i].rhchannel_combine_method), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhclipmax", indent + 1, &(val[i].rhclipmax), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhclipmin", indent + 1, &(val[i].rhclipmin), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhcoilno", indent + 1, &(val[i].rhcoilno), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhcorrelationThreshold", indent + 1, &(val[i].rhcorrelationThreshold), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhcphases", indent + 1, &(val[i].rhcphases), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhcrrtime", indent + 1, &(val[i].rhcrrtime), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhcs_consistency", indent + 1, &(val[i].rhcs_consistency), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhcs_factor", indent + 1, &(val[i].rhcs_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhcs_flag", indent + 1, &(val[i].rhcs_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhcs_maxiter", indent + 1, &(val[i].rhcs_maxiter), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhcs_ph_stride", indent + 1, &(val[i].rhcs_ph_stride), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhcs_sl_stride", indent + 1, &(val[i].rhcs_sl_stride), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhctr", indent + 1, &(val[i].rhctr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdab0e", indent + 1, &(val[i].rhdab0e), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdab0s", indent + 1, &(val[i].rhdab0s), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdacqctrl", indent + 1, &(val[i].rhdacqctrl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdatacq", indent + 1, &(val[i].rhdatacq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdaviewsPerBlade", indent + 1, &(val[i].rhdaviewsPerBlade), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdaxres", indent + 1, &(val[i].rhdaxres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdayres", indent + 1, &(val[i].rhdayres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdbgrecon", indent + 1, &(val[i].rhdbgrecon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhddaover", indent + 1, &(val[i].rhddaover), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhdensityfactor", indent + 1, &(val[i].rhdensityfactor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdf", indent + 1, &(val[i].rhdf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdfm", indent + 1, &(val[i].rhdfm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdfmdebug", indent + 1, &(val[i].rhdfmdebug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdfmnavsperpass", indent + 1, &(val[i].rhdfmnavsperpass), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdfmnavsperview", indent + 1, &(val[i].rhdfmnavsperview), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdfmptsize", indent + 1, &(val[i].rhdfmptsize), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhdfmrbw", indent + 1, &(val[i].rhdfmrbw), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhdfmthreshold", indent + 1, &(val[i].rhdfmthreshold), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdfmxres", indent + 1, &(val[i].rhdfmxres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdifnext2", indent + 1, &(val[i].rhdifnext2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdiskacqctrl", indent + 1, &(val[i].rhdiskacqctrl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhdispfov", indent + 1, &(val[i].rhdispfov), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhdoffset", indent + 1, &(val[i].rhdoffset), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdptype", indent + 1, &(val[i].rhdptype), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhdwnavcoeff", indent + 1, &(val[i].rhdwnavcoeff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdwnavcor", indent + 1, &(val[i].rhdwnavcor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdwnavcorecho", indent + 1, &(val[i].rhdwnavcorecho), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdwnaveshot", indent + 1, &(val[i].rhdwnaveshot), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdwnaveview", indent + 1, &(val[i].rhdwnaveview), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdwnavsshot", indent + 1, &(val[i].rhdwnavsshot), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdwnavsview", indent + 1, &(val[i].rhdwnavsview), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhdwnavview", indent + 1, &(val[i].rhdwnavview), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhech2skip", indent + 1, &(val[i].rhech2skip), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhechopc_ctrl", indent + 1, &(val[i].rhechopc_ctrl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhechopc_extra_bot", indent + 1, &(val[i].rhechopc_extra_bot), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhechopc_primary_yfirst", indent + 1, &(val[i].rhechopc_primary_yfirst), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhechopc_reverse_yfirst", indent + 1, &(val[i].rhechopc_reverse_yfirst), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhechopc_ylines", indent + 1, &(val[i].rhechopc_ylines), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhechopc_yxfitorder", indent + 1, &(val[i].rhechopc_yxfitorder), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhechopc_zlines", indent + 1, &(val[i].rhechopc_zlines), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhectricks_input_regions", indent + 1, &(val[i].rhectricks_input_regions), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhectricks_num_regions", indent + 1, &(val[i].rhectricks_num_regions), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhesp", indent + 1, &(val[i].rhesp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhetl", indent + 1, &(val[i].rhetl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhexciterfreqs", indent + 1, &(val[i].rhexciterfreqs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhexciterusage", indent + 1, &(val[i].rhexciterusage), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhexecctrl", indent + 1, &(val[i].rhexecctrl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhextra_frames_bot", indent + 1, &(val[i].rhextra_frames_bot), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhextra_frames_top", indent + 1, &(val[i].rhextra_frames_top), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhfast_rec", indent + 1, &(val[i].rhfast_rec), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhfatwater", indent + 1, &(val[i].rhfatwater), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhfcinearw", indent + 1, &(val[i].rhfcinearw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhfcinemode", indent + 1, &(val[i].rhfcinemode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhfdctrl", indent + 1, &(val[i].rhfdctrl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhfeextra", indent + 1, &(val[i].rhfeextra), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhferme", indent + 1, &(val[i].rhferme), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhfermr", indent + 1, &(val[i].rhfermr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhfermw", indent + 1, &(val[i].rhfermw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhfiesta", indent + 1, &(val[i].rhfiesta), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhflipfilter", indent + 1, &(val[i].rhflipfilter), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhformat", indent + 1, &(val[i].rhformat), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhfreqscale", indent + 1, &(val[i].rhfreqscale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhfrsize", indent + 1, &(val[i].rhfrsize), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhgradmode", indent + 1, &(val[i].rhgradmode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhgridcontrol", indent + 1, &(val[i].rhgridcontrol), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhhdbestky", indent + 1, &(val[i].rhhdbestky), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhheover", indent + 1, &(val[i].rhheover), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhherawflt", indent + 1, &(val[i].rhherawflt), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhherawflt_befamp", indent + 1, &(val[i].rhherawflt_befamp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhherawflt_befntran", indent + 1, &(val[i].rhherawflt_befntran), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhherawflt_befnwin", indent + 1, &(val[i].rhherawflt_befnwin), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhherawflt_hpfamp", indent + 1, &(val[i].rhherawflt_hpfamp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhhniter", indent + 1, &(val[i].rhhniter), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhhnover", indent + 1, &(val[i].rhhnover), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhhoec_fit_order", indent + 1, &(val[i].rhhoec_fit_order), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhhoecc", indent + 1, &(val[i].rhhoecc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhileaves", indent + 1, &(val[i].rhileaves), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhimsize", indent + 1, &(val[i].rhimsize), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhincrpass", indent + 1, &(val[i].rhincrpass), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhinitpass", indent + 1, &(val[i].rhinitpass), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhkacq_uid", indent + 1, &(val[i].rhkacq_uid), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhkt_cal_factor", indent + 1, &(val[i].rhkt_cal_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhkt_calwidth_ph", indent + 1, &(val[i].rhkt_calwidth_ph), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhkt_calwidth_sl", indent + 1, &(val[i].rhkt_calwidth_sl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhkt_factor", indent + 1, &(val[i].rhkt_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhkydir", indent + 1, &(val[i].rhkydir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhlcfiesta", indent + 1, &(val[i].rhlcfiesta), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhlcfiesta_phase", indent + 1, &(val[i].rhlcfiesta_phase), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhleft_blank", indent + 1, &(val[i].rhleft_blank), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhmaxcoef1a", indent + 1, &(val[i].rhmaxcoef1a), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhmaxcoef1b", indent + 1, &(val[i].rhmaxcoef1b), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhmaxcoef1c", indent + 1, &(val[i].rhmaxcoef1c), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhmaxcoef1d", indent + 1, &(val[i].rhmaxcoef1d), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhmaxcoef2a", indent + 1, &(val[i].rhmaxcoef2a), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhmaxcoef2b", indent + 1, &(val[i].rhmaxcoef2b), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhmaxcoef2c", indent + 1, &(val[i].rhmaxcoef2c), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhmaxcoef2d", indent + 1, &(val[i].rhmaxcoef2d), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhmaxcoef3a", indent + 1, &(val[i].rhmaxcoef3a), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhmaxcoef3b", indent + 1, &(val[i].rhmaxcoef3b), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhmaxcoef3c", indent + 1, &(val[i].rhmaxcoef3c), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhmaxcoef3d", indent + 1, &(val[i].rhmaxcoef3d), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhmaxgrad", indent + 1, &(val[i].rhmaxgrad), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhmb_factor", indent + 1, &(val[i].rhmb_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhmb_slice_fov_shift_factor", indent + 1, &(val[i].rhmb_slice_fov_shift_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhmb_slice_order_sign", indent + 1, &(val[i].rhmb_slice_order_sign), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhmedal_down_kernel_size", indent + 1, &(val[i].rhmedal_down_kernel_size), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhmedal_echo_order", indent + 1, &(val[i].rhmedal_echo_order), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhmedal_ending_slice", indent + 1, &(val[i].rhmedal_ending_slice), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhmedal_mode", indent + 1, &(val[i].rhmedal_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhmedal_nstack_size", indent + 1, &(val[i].rhmedal_nstack_size), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhmedal_param", indent + 1, &(val[i].rhmedal_param), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhmedal_smooth_kernel_size", indent + 1, &(val[i].rhmedal_smooth_kernel_size), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhmedal_starting_slice", indent + 1, &(val[i].rhmedal_starting_slice), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhmedal_up_kernel_size", indent + 1, &(val[i].rhmedal_up_kernel_size), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhmeth", indent + 1, &(val[i].rhmeth), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhmethod", indent + 1, &(val[i].rhmethod), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhmotioncomp", indent + 1, &(val[i].rhmotioncomp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhmphasetype", indent + 1, &(val[i].rhmphasetype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnavs", indent + 1, &(val[i].rhnavs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhncoillimit", indent + 1, &(val[i].rhncoillimit), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhncoilsel", indent + 1, &(val[i].rhncoilsel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhncycles_cine", indent + 1, &(val[i].rhncycles_cine), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnecho", indent + 1, &(val[i].rhnecho), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnew_wnd_level_flag", indent + 1, &(val[i].rhnew_wnd_level_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnex", indent + 1, &(val[i].rhnex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnex_unacquired", indent + 1, &(val[i].rhnex_unacquired), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnframes", indent + 1, &(val[i].rhnframes), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnoncart_dual_traj", indent + 1, &(val[i].rhnoncart_dual_traj), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhnoncart_grid_factor", indent + 1, &(val[i].rhnoncart_grid_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnoncart_traj_kmax_ratio", indent + 1, &(val[i].rhnoncart_traj_kmax_ratio), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnoncart_traj_merge_end", indent + 1, &(val[i].rhnoncart_traj_merge_end), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnoncart_traj_merge_start", indent + 1, &(val[i].rhnoncart_traj_merge_start), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnoncart_traj_mode", indent + 1, &(val[i].rhnoncart_traj_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnpasses", indent + 1, &(val[i].rhnpasses), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnphases", indent + 1, &(val[i].rhnphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnpomp", indent + 1, &(val[i].rhnpomp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhnpwfactor", indent + 1, &(val[i].rhnpwfactor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnrefslices", indent + 1, &(val[i].rhnrefslices), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnslices", indent + 1, &(val[i].rhnslices), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnspokes_highres", indent + 1, &(val[i].rhnspokes_highres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnspokes_lowres", indent + 1, &(val[i].rhnspokes_lowres), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhntran", indent + 1, &(val[i].rhntran), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnumCoilConfigs", indent + 1, &(val[i].rhnumCoilConfigs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnumbvals", indent + 1, &(val[i].rhnumbvals), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnumdifdirs", indent + 1, &(val[i].rhnumdifdirs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnumslabs", indent + 1, &(val[i].rhnumslabs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhnvircchannel", indent + 1, &(val[i].rhnvircchannel), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhnwin", indent + 1, &(val[i].rhnwin), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhoscans", indent + 1, &(val[i].rhoscans), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhoversamplingfactor", indent + 1, &(val[i].rhoversamplingfactor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhovl", indent + 1, &(val[i].rhovl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpasframe", indent + 1, &(val[i].rhpasframe), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpc_rationalscale", indent + 1, &(val[i].rhpc_rationalscale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpc_ref_skip", indent + 1, &(val[i].rhpc_ref_skip), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpc_ref_start", indent + 1, &(val[i].rhpc_ref_start), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpc_ref_stop", indent + 1, &(val[i].rhpc_ref_stop), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhpcbestky", indent + 1, &(val[i].rhpcbestky), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpccoil", indent + 1, &(val[i].rhpccoil), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpccon", indent + 1, &(val[i].rhpccon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcconfitwt", indent + 1, &(val[i].rhpcconfitwt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcconfix", indent + 1, &(val[i].rhpcconfix), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcconnorm", indent + 1, &(val[i].rhpcconnorm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcconnpts", indent + 1, &(val[i].rhpcconnpts), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcconorder", indent + 1, &(val[i].rhpcconorder), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhpcconslope", indent + 1, &(val[i].rhpcconslope), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcctrl", indent + 1, &(val[i].rhpcctrl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcdiscbeg", indent + 1, &(val[i].rhpcdiscbeg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcdiscend", indent + 1, &(val[i].rhpcdiscend), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcdiscmid", indent + 1, &(val[i].rhpcdiscmid), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcextcorr", indent + 1, &(val[i].rhpcextcorr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcfitorig", indent + 1, &(val[i].rhpcfitorig), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcgraph", indent + 1, &(val[i].rhpcgraph), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcileave", indent + 1, &(val[i].rhpcileave), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcinvft", indent + 1, &(val[i].rhpcinvft), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpclin", indent + 1, &(val[i].rhpclin), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpclinavg", indent + 1, &(val[i].rhpclinavg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpclinfitwt", indent + 1, &(val[i].rhpclinfitwt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpclinfix", indent + 1, &(val[i].rhpclinfix), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpclinnorm", indent + 1, &(val[i].rhpclinnorm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpclinnpts", indent + 1, &(val[i].rhpclinnpts), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpclinorder", indent + 1, &(val[i].rhpclinorder), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhpclinslope", indent + 1, &(val[i].rhpclinslope), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcmag", indent + 1, &(val[i].rhpcmag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcmultegrp", indent + 1, &(val[i].rhpcmultegrp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcshotfirst", indent + 1, &(val[i].rhpcshotfirst), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcshotlast", indent + 1, &(val[i].rhpcshotlast), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcsnore", indent + 1, &(val[i].rhpcsnore), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcspacial", indent + 1, &(val[i].rhpcspacial), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcspacial_dynamic", indent + 1, &(val[i].rhpcspacial_dynamic), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpctemporal", indent + 1, &(val[i].rhpctemporal), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpctest", indent + 1, &(val[i].rhpctest), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcthrespct", indent + 1, &(val[i].rhpcthrespct), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpcthrespts", indent + 1, &(val[i].rhpcthrespts), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhphasescale", indent + 1, &(val[i].rhphasescale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhphsen_pixel_offset", indent + 1, &(val[i].rhphsen_pixel_offset), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhposition_detection", indent + 1, &(val[i].rhposition_detection), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpropellerCtrl", indent + 1, &(val[i].rhpropellerCtrl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhptsize", indent + 1, &(val[i].rhptsize), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpure", indent + 1, &(val[i].rhpure), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhpure_blur", indent + 1, &(val[i].rhpure_blur), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpure_blur_enable", indent + 1, &(val[i].rhpure_blur_enable), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhpure_cal_reapodization", indent + 1, &(val[i].rhpure_cal_reapodization), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhpure_derived_cal_fraction", indent + 1, &(val[i].rhpure_derived_cal_fraction), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpure_filtering_mode", indent + 1, &(val[i].rhpure_filtering_mode), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhpure_lambda", indent + 1, &(val[i].rhpure_lambda), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhpure_mix_alpha", indent + 1, &(val[i].rhpure_mix_alpha), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpure_mix_aniso_blur", indent + 1, &(val[i].rhpure_mix_aniso_blur), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpure_mix_aniso_dilate_dist", indent + 1, &(val[i].rhpure_mix_aniso_dilate_dist), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpure_mix_aniso_erode_dist", indent + 1, &(val[i].rhpure_mix_aniso_erode_dist), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhpure_mix_blur", indent + 1, &(val[i].rhpure_mix_blur), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpure_mix_blur_enable", indent + 1, &(val[i].rhpure_mix_blur_enable), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpure_mix_dilate_dist", indent + 1, &(val[i].rhpure_mix_dilate_dist), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpure_mix_erode_dist", indent + 1, &(val[i].rhpure_mix_erode_dist), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhpure_mix_exp_wt", indent + 1, &(val[i].rhpure_mix_exp_wt), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhpure_mix_lambda", indent + 1, &(val[i].rhpure_mix_lambda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpure_mix_otsu_class_qty", indent + 1, &(val[i].rhpure_mix_otsu_class_qty), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhpure_mix_tuning_factor_body", indent + 1, &(val[i].rhpure_mix_tuning_factor_body), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhpure_mix_tuning_factor_surface", indent + 1, &(val[i].rhpure_mix_tuning_factor_surface), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhpure_scale_factor", indent + 1, &(val[i].rhpure_scale_factor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhpure_tuning_factor_body", indent + 1, &(val[i].rhpure_tuning_factor_body), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhpure_tuning_factor_surface", indent + 1, &(val[i].rhpure_tuning_factor_surface), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpurechannel", indent + 1, &(val[i].rhpurechannel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhpurefilter", indent + 1, &(val[i].rhpurefilter), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhradiusa", indent + 1, &(val[i].rhradiusa), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhradiusb", indent + 1, &(val[i].rhradiusb), 1);
#endif
#ifdef SIZEOF_n64
    print_brsfc_n64(fp, "rhrawsize", indent + 1, &(val[i].rhrawsize), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhrawsizeview", indent + 1, &(val[i].rhrawsizeview), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhrc3dcinectrl", indent + 1, &(val[i].rhrc3dcinectrl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhrc_cardt1map_ctrl", indent + 1, &(val[i].rhrc_cardt1map_ctrl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhrc_moco_ctrl", indent + 1, &(val[i].rhrc_moco_ctrl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhrcctrl", indent + 1, &(val[i].rhrcctrl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhrcdixproc", indent + 1, &(val[i].rhrcdixproc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhrcideal", indent + 1, &(val[i].rhrcideal), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhrcidealctrl", indent + 1, &(val[i].rhrcidealctrl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhrcmavric_bin_separation", indent + 1, &(val[i].rhrcmavric_bin_separation), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhrcmavric_control", indent + 1, &(val[i].rhrcmavric_control), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhrcmavric_image", indent + 1, &(val[i].rhrcmavric_image), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhrcxres", indent + 1, &(val[i].rhrcxres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhrcyres", indent + 1, &(val[i].rhrcyres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhrecon", indent + 1, &(val[i].rhrecon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhrecv_freq_e", indent + 1, &(val[i].rhrecv_freq_e), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhrecv_freq_s", indent + 1, &(val[i].rhrecv_freq_s), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhref", indent + 1, &(val[i].rhref), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhrefframep", indent + 1, &(val[i].rhrefframep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhrefframes", indent + 1, &(val[i].rhrefframes), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhreps", indent + 1, &(val[i].rhreps), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhretro_control", indent + 1, &(val[i].rhretro_control), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhright_blank", indent + 1, &(val[i].rhright_blank), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhrlfov", indent + 1, &(val[i].rhrlfov), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhrotationThreshold", indent + 1, &(val[i].rhrotationThreshold), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhscancent", indent + 1, &(val[i].rhscancent), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhscanfov", indent + 1, &(val[i].rhscanfov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhscnframe", indent + 1, &(val[i].rhscnframe), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhshiftThreshold", indent + 1, &(val[i].rhshiftThreshold), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhsifov", indent + 1, &(val[i].rhsifov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhslblank", indent + 1, &(val[i].rhslblank), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhslewmax", indent + 1, &(val[i].rhslewmax), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhsnrnoise", indent + 1, &(val[i].rhsnrnoise), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhspeccsidims", indent + 1, &(val[i].rhspeccsidims), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhspecrescsix", indent + 1, &(val[i].rhspecrescsix), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhspecrescsiy", indent + 1, &(val[i].rhspecrescsiy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhspecrescsiz", indent + 1, &(val[i].rhspecrescsiz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhspecroilenx", indent + 1, &(val[i].rhspecroilenx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhspecroileny", indent + 1, &(val[i].rhspecroileny), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhspecroilenz", indent + 1, &(val[i].rhspecroilenz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhspecroilocx", indent + 1, &(val[i].rhspecroilocx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhspecroilocy", indent + 1, &(val[i].rhspecroilocy), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhspecroilocz", indent + 1, &(val[i].rhspecroilocz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhspecwidth", indent + 1, &(val[i].rhspecwidth), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhsspsave", indent + 1, &(val[i].rhsspsave), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhswiftenable", indent + 1, &(val[i].rhswiftenable), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhte", indent + 1, &(val[i].rhte), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhte2", indent + 1, &(val[i].rhte2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhtediff", indent + 1, &(val[i].rhtediff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhtrickstype", indent + 1, &(val[i].rhtrickstype), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhtsamp", indent + 1, &(val[i].rhtsamp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhtype", indent + 1, &(val[i].rhtype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhtype1", indent + 1, &(val[i].rhtype1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhudasave", indent + 1, &(val[i].rhudasave), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser0", indent + 1, &(val[i].rhuser0), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser1", indent + 1, &(val[i].rhuser1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser10", indent + 1, &(val[i].rhuser10), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser11", indent + 1, &(val[i].rhuser11), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser12", indent + 1, &(val[i].rhuser12), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser13", indent + 1, &(val[i].rhuser13), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser14", indent + 1, &(val[i].rhuser14), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser15", indent + 1, &(val[i].rhuser15), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser16", indent + 1, &(val[i].rhuser16), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser17", indent + 1, &(val[i].rhuser17), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser18", indent + 1, &(val[i].rhuser18), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser19", indent + 1, &(val[i].rhuser19), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser2", indent + 1, &(val[i].rhuser2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser20", indent + 1, &(val[i].rhuser20), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser21", indent + 1, &(val[i].rhuser21), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser22", indent + 1, &(val[i].rhuser22), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser23", indent + 1, &(val[i].rhuser23), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser24", indent + 1, &(val[i].rhuser24), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser25", indent + 1, &(val[i].rhuser25), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser26", indent + 1, &(val[i].rhuser26), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser27", indent + 1, &(val[i].rhuser27), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser28", indent + 1, &(val[i].rhuser28), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser29", indent + 1, &(val[i].rhuser29), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser3", indent + 1, &(val[i].rhuser3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser30", indent + 1, &(val[i].rhuser30), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser31", indent + 1, &(val[i].rhuser31), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser32", indent + 1, &(val[i].rhuser32), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser33", indent + 1, &(val[i].rhuser33), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser34", indent + 1, &(val[i].rhuser34), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser35", indent + 1, &(val[i].rhuser35), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser36", indent + 1, &(val[i].rhuser36), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser37", indent + 1, &(val[i].rhuser37), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser38", indent + 1, &(val[i].rhuser38), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser39", indent + 1, &(val[i].rhuser39), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser4", indent + 1, &(val[i].rhuser4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser40", indent + 1, &(val[i].rhuser40), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser41", indent + 1, &(val[i].rhuser41), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser42", indent + 1, &(val[i].rhuser42), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser43", indent + 1, &(val[i].rhuser43), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser44", indent + 1, &(val[i].rhuser44), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser45", indent + 1, &(val[i].rhuser45), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser46", indent + 1, &(val[i].rhuser46), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser47", indent + 1, &(val[i].rhuser47), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser48", indent + 1, &(val[i].rhuser48), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser5", indent + 1, &(val[i].rhuser5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser6", indent + 1, &(val[i].rhuser6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser7", indent + 1, &(val[i].rhuser7), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser8", indent + 1, &(val[i].rhuser8), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhuser9", indent + 1, &(val[i].rhuser9), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhuser_usage_tag", indent + 1, &(val[i].rhuser_usage_tag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhutctrl", indent + 1, &(val[i].rhutctrl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhvcoefxa", indent + 1, &(val[i].rhvcoefxa), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhvcoefxb", indent + 1, &(val[i].rhvcoefxb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhvcoefxc", indent + 1, &(val[i].rhvcoefxc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhvcoefxd", indent + 1, &(val[i].rhvcoefxd), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhvcoefya", indent + 1, &(val[i].rhvcoefya), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhvcoefyb", indent + 1, &(val[i].rhvcoefyb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhvcoefyc", indent + 1, &(val[i].rhvcoefyc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhvcoefyd", indent + 1, &(val[i].rhvcoefyd), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhvcoefza", indent + 1, &(val[i].rhvcoefza), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhvcoefzb", indent + 1, &(val[i].rhvcoefzb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhvcoefzc", indent + 1, &(val[i].rhvcoefzc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhvcoefzd", indent + 1, &(val[i].rhvcoefzd), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhvenc", indent + 1, &(val[i].rhvenc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhvibrant", indent + 1, &(val[i].rhvibrant), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhviewSharing3D", indent + 1, &(val[i].rhviewSharing3D), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhvircoilchannels", indent + 1, &(val[i].rhvircoilchannels), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhvircoiltype", indent + 1, &(val[i].rhvircoiltype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhvircoilunif", indent + 1, &(val[i].rhvircoilunif), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhvircpolicy", indent + 1, &(val[i].rhvircpolicy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhvirsenstype", indent + 1, &(val[i].rhvirsenstype), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhvmcoef1", indent + 1, &(val[i].rhvmcoef1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhvmcoef2", indent + 1, &(val[i].rhvmcoef2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhvmcoef3", indent + 1, &(val[i].rhvmcoef3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhvmcoef4", indent + 1, &(val[i].rhvmcoef4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhvps", indent + 1, &(val[i].rhvps), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhvquant", indent + 1, &(val[i].rhvquant), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhvrgf", indent + 1, &(val[i].rhvrgf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhvrgfxres", indent + 1, &(val[i].rhvrgfxres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhvtype", indent + 1, &(val[i].rhvtype), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhvvsaimgs", indent + 1, &(val[i].rhvvsaimgs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhvvsgender", indent + 1, &(val[i].rhvvsgender), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhvvstr", indent + 1, &(val[i].rhvvstr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhwiener", indent + 1, &(val[i].rhwiener), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhwienera", indent + 1, &(val[i].rhwienera), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhwienerb", indent + 1, &(val[i].rhwienerb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhwieneresp", indent + 1, &(val[i].rhwieneresp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhwienert2", indent + 1, &(val[i].rhwienert2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhwnd_high_hist", indent + 1, &(val[i].rhwnd_high_hist), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rhwnd_image_hist_area", indent + 1, &(val[i].rhwnd_image_hist_area), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhwnd_lower_hist", indent + 1, &(val[i].rhwnd_lower_hist), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhxoff", indent + 1, &(val[i].rhxoff), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhyoff", indent + 1, &(val[i].rhyoff), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhzeroph", indent + 1, &(val[i].rhzeroph), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhzipfact", indent + 1, &(val[i].rhzipfact), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rl_flow", indent + 1, &(val[i].rl_flow), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rot_delay", indent + 1, &(val[i].rot_delay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rot_delay_gir", indent + 1, &(val[i].rot_delay_gir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rotateflag", indent + 1, &(val[i].rotateflag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rs_dda", indent + 1, &(val[i].rs_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rs_esp", indent + 1, &(val[i].rs_esp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rs_iso_delay", indent + 1, &(val[i].rs_iso_delay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rs_off90", indent + 1, &(val[i].rs_off90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rsamp_time", indent + 1, &(val[i].rsamp_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rsaxial_flag", indent + 1, &(val[i].rsaxial_flag), 1);
#endif
#ifdef SIZEOF_LOG_GRAD
    print_brsfc_LOG_GRAD(fp, "rsloggrd", indent + 1, &(val[i].rsloggrd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rsphorder", indent + 1, &(val[i].rsphorder), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rsspgr_flag", indent + 1, &(val[i].rsspgr_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rst_exa", indent + 1, &(val[i].rst_exa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rst_exb", indent + 1, &(val[i].rst_exb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtca_insteps_flip", indent + 1, &(val[i].rtca_insteps_flip), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtca_insteps_fov", indent + 1, &(val[i].rtca_insteps_fov), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtca_insteps_slthick", indent + 1, &(val[i].rtca_insteps_slthick), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtca_max_flip", indent + 1, &(val[i].rtca_max_flip), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtca_max_fov", indent + 1, &(val[i].rtca_max_fov), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtca_max_slthick", indent + 1, &(val[i].rtca_max_slthick), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtca_min_flip", indent + 1, &(val[i].rtca_min_flip), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtca_min_fov", indent + 1, &(val[i].rtca_min_fov), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtca_min_slabthick", indent + 1, &(val[i].rtca_min_slabthick), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtca_min_slthick", indent + 1, &(val[i].rtca_min_slthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtia3d_buffers", indent + 1, &(val[i].rtia3d_buffers), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtia3d_eff_slabthick", indent + 1, &(val[i].rtia3d_eff_slabthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtia3d_irp_flag", indent + 1, &(val[i].rtia3d_irp_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtia3d_original_flip", indent + 1, &(val[i].rtia3d_original_flip), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtia3d_original_fov", indent + 1, &(val[i].rtia3d_original_fov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtia3d_original_slthick", indent + 1, &(val[i].rtia3d_original_slthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtia3d_pass", indent + 1, &(val[i].rtia3d_pass), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtia3d_phorder", indent + 1, &(val[i].rtia3d_phorder), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtia3d_repeat_views", indent + 1, &(val[i].rtia3d_repeat_views), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtia3d_restricted_nav_flag", indent + 1, &(val[i].rtia3d_restricted_nav_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtia3d_sat_flip", indent + 1, &(val[i].rtia3d_sat_flip), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtia3d_sat_pos", indent + 1, &(val[i].rtia3d_sat_pos), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtia3d_sat_views", indent + 1, &(val[i].rtia3d_sat_views), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtia3d_slice_thinning_factor", indent + 1, &(val[i].rtia3d_slice_thinning_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtia3d_thkslab_proj_enable_flag", indent + 1, &(val[i].rtia3d_thkslab_proj_enable_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtia3d_thkslab_proj_flag", indent + 1, &(val[i].rtia3d_thkslab_proj_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtia3d_turbo", indent + 1, &(val[i].rtia3d_turbo), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtia_first_scan_flag", indent + 1, &(val[i].rtia_first_scan_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtia_fov_freq_scale", indent + 1, &(val[i].rtia_fov_freq_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtia_fov_phase_scale", indent + 1, &(val[i].rtia_fov_phase_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtia_init_phasoff", indent + 1, &(val[i].rtia_init_phasoff), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtia_init_rloc", indent + 1, &(val[i].rtia_init_rloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtia_init_tloc", indent + 1, &(val[i].rtia_init_tloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtia_orig_phasoff", indent + 1, &(val[i].rtia_orig_phasoff), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtia_orig_rloc", indent + 1, &(val[i].rtia_orig_rloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtia_orig_tloc", indent + 1, &(val[i].rtia_orig_tloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtia_rel_fov_freq_scale", indent + 1, &(val[i].rtia_rel_fov_freq_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtia_rel_fov_phase_scale", indent + 1, &(val[i].rtia_rel_fov_phase_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtia_satgapzneg", indent + 1, &(val[i].rtia_satgapzneg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtia_satgapzpos", indent + 1, &(val[i].rtia_satgapzpos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rtia_slthick_scale", indent + 1, &(val[i].rtia_slthick_scale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtpend_quiet_dda", indent + 1, &(val[i].rtpend_quiet_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtpresultwait", indent + 1, &(val[i].rtpresultwait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtsar_enable_flag", indent + 1, &(val[i].rtsar_enable_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rtsar_first_series_flag", indent + 1, &(val[i].rtsar_first_series_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "run_eval_from_get_flag", indent + 1, &(val[i].run_eval_from_get_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "rvssliceenc", indent + 1, &(val[i].rvssliceenc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "s5fpharea", indent + 1, &(val[i].s5fpharea), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sampledPoints", indent + 1, &(val[i].sampledPoints), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sar_amp", indent + 1, &(val[i].sar_amp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sar_correction_factor", indent + 1, &(val[i].sar_correction_factor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sar_cycle", indent + 1, &(val[i].sar_cycle), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sar_width", indent + 1, &(val[i].sar_width), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sat_TGlimit", indent + 1, &(val[i].sat_TGlimit), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sat_dda", indent + 1, &(val[i].sat_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sat_debug", indent + 1, &(val[i].sat_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sat_newgeo", indent + 1, &(val[i].sat_newgeo), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sat_obl_debug", indent + 1, &(val[i].sat_obl_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sat_pulse_type", indent + 1, &(val[i].sat_pulse_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sat_reps", indent + 1, &(val[i].sat_reps), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sat_rot_df_num", indent + 1, &(val[i].sat_rot_df_num), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sat_rot_ex_num", indent + 1, &(val[i].sat_rot_ex_num), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sat_rot_index", indent + 1, &(val[i].sat_rot_index), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satgapxneg", indent + 1, &(val[i].satgapxneg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satgapxpos", indent + 1, &(val[i].satgapxpos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satgapyneg", indent + 1, &(val[i].satgapyneg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satgapypos", indent + 1, &(val[i].satgapypos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satgapzneg", indent + 1, &(val[i].satgapzneg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satgapzpos", indent + 1, &(val[i].satgapzpos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satloce1", indent + 1, &(val[i].satloce1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satloce2", indent + 1, &(val[i].satloce2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satloce3", indent + 1, &(val[i].satloce3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satloce4", indent + 1, &(val[i].satloce4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satloce5", indent + 1, &(val[i].satloce5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satloce6", indent + 1, &(val[i].satloce6), 1);
#endif
#ifdef SIZEOF_LOG_GRAD
    print_brsfc_LOG_GRAD(fp, "satloggrd", indent + 1, &(val[i].satloggrd), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satspace1", indent + 1, &(val[i].satspace1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satspace2", indent + 1, &(val[i].satspace2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satspace3", indent + 1, &(val[i].satspace3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satspace4", indent + 1, &(val[i].satspace4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satspace5", indent + 1, &(val[i].satspace5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satspace6", indent + 1, &(val[i].satspace6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satspacex1", indent + 1, &(val[i].satspacex1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satspacex2", indent + 1, &(val[i].satspacex2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satspacey1", indent + 1, &(val[i].satspacey1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satspacey2", indent + 1, &(val[i].satspacey2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satspacez1", indent + 1, &(val[i].satspacez1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satspacez2", indent + 1, &(val[i].satspacez2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satthickdfx", indent + 1, &(val[i].satthickdfx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satthickdfy", indent + 1, &(val[i].satthickdfy), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satthickdfz", indent + 1, &(val[i].satthickdfz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satthickx1", indent + 1, &(val[i].satthickx1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satthickx2", indent + 1, &(val[i].satthickx2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satthicky1", indent + 1, &(val[i].satthicky1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satthicky2", indent + 1, &(val[i].satthicky2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satthickz1", indent + 1, &(val[i].satthickz1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satthickz2", indent + 1, &(val[i].satthickz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "satview", indent + 1, &(val[i].satview), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satxlocneg", indent + 1, &(val[i].satxlocneg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satxlocpos", indent + 1, &(val[i].satxlocpos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satylocneg", indent + 1, &(val[i].satylocneg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satylocpos", indent + 1, &(val[i].satylocpos), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satzloca", indent + 1, &(val[i].satzloca), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satzlocb", indent + 1, &(val[i].satzlocb), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satzlocneg", indent + 1, &(val[i].satzlocneg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "satzlocpos", indent + 1, &(val[i].satzlocpos), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "save_cfxfull", indent + 1, &(val[i].save_cfxfull), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "save_cfxipeak", indent + 1, &(val[i].save_cfxipeak), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "save_cfyfull", indent + 1, &(val[i].save_cfyfull), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "save_cfyipeak", indent + 1, &(val[i].save_cfyipeak), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "save_cfzfull", indent + 1, &(val[i].save_cfzfull), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "save_cfzipeak", indent + 1, &(val[i].save_cfzipeak), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "save_fft", indent + 1, &(val[i].save_fft), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "save_gmax", indent + 1, &(val[i].save_gmax), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "save_gradOpt_TEfactor", indent + 1, &(val[i].save_gradOpt_TEfactor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "save_gradOpt_TRfactor", indent + 1, &(val[i].save_gradOpt_TRfactor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "save_gradOpt_ratio", indent + 1, &(val[i].save_gradOpt_ratio), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "save_gradOpt_scale", indent + 1, &(val[i].save_gradOpt_scale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "save_grad_spec_flag", indent + 1, &(val[i].save_grad_spec_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "save_ogsfX1", indent + 1, &(val[i].save_ogsfX1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "save_ogsfX2", indent + 1, &(val[i].save_ogsfX2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "save_ogsfXwex", indent + 1, &(val[i].save_ogsfXwex), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "save_ogsfY", indent + 1, &(val[i].save_ogsfY), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "save_ogsfYk", indent + 1, &(val[i].save_ogsfYk), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "save_ogsfZ", indent + 1, &(val[i].save_ogsfZ), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "save_ramptime", indent + 1, &(val[i].save_ramptime), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "save_srate", indent + 1, &(val[i].save_srate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "savedata", indent + 1, &(val[i].savedata), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "saveinter", indent + 1, &(val[i].saveinter), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_bak_pitscan", indent + 1, &(val[i].sbm_bak_pitscan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sbm_cvs_changed", indent + 1, &(val[i].sbm_cvs_changed), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sbm_cvs_old", indent + 1, &(val[i].sbm_cvs_old), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sbm_dda", indent + 1, &(val[i].sbm_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sbm_dda_max", indent + 1, &(val[i].sbm_dda_max), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sbm_dda_min", indent + 1, &(val[i].sbm_dda_min), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sbm_debug", indent + 1, &(val[i].sbm_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sbm_dummy_num", indent + 1, &(val[i].sbm_dummy_num), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sbm_flag", indent + 1, &(val[i].sbm_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sbm_gradient_method", indent + 1, &(val[i].sbm_gradient_method), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_gx1_scale", indent + 1, &(val[i].sbm_gx1_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_gxw_scale", indent + 1, &(val[i].sbm_gxw_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_gxwex_scale", indent + 1, &(val[i].sbm_gxwex_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_gy1_scale", indent + 1, &(val[i].sbm_gy1_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_gy1r_scale", indent + 1, &(val[i].sbm_gy1r_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_gzcomb_scale", indent + 1, &(val[i].sbm_gzcomb_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_gzp_scale", indent + 1, &(val[i].sbm_gzp_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_margin", indent + 1, &(val[i].sbm_margin), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sbm_mps2_imaging_num", indent + 1, &(val[i].sbm_mps2_imaging_num), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sbm_pitscan_changed", indent + 1, &(val[i].sbm_pitscan_changed), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_pitscan_limit", indent + 1, &(val[i].sbm_pitscan_limit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_pitscan_old", indent + 1, &(val[i].sbm_pitscan_old), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_smartderating_factor", indent + 1, &(val[i].sbm_smartderating_factor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_sum_dummy", indent + 1, &(val[i].sbm_sum_dummy), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_time_limit", indent + 1, &(val[i].sbm_time_limit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_time_limit_max", indent + 1, &(val[i].sbm_time_limit_max), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_time_limit_min", indent + 1, &(val[i].sbm_time_limit_min), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_time_limit_ratio", indent + 1, &(val[i].sbm_time_limit_ratio), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sbm_waiting_time", indent + 1, &(val[i].sbm_waiting_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sbm_y_num", indent + 1, &(val[i].sbm_y_num), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sbm_z_num", indent + 1, &(val[i].sbm_z_num), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "scale_fac", indent + 1, &(val[i].scale_fac), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "scale_tr", indent + 1, &(val[i].scale_tr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "scale_tr_grad", indent + 1, &(val[i].scale_tr_grad), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "scanclocktime", indent + 1, &(val[i].scanclocktime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "scanrcvr", indent + 1, &(val[i].scanrcvr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "scanrf1_inst", indent + 1, &(val[i].scanrf1_inst), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "scanrf1tm_inst", indent + 1, &(val[i].scanrf1tm_inst), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "scansat0", indent + 1, &(val[i].scansat0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "scansatint", indent + 1, &(val[i].scansatint), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "scptrg", indent + 1, &(val[i].scptrg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "seed", indent + 1, &(val[i].seed), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "seeddef", indent + 1, &(val[i].seeddef), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "seg_debug", indent + 1, &(val[i].seg_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "seg_foundvps_flag", indent + 1, &(val[i].seg_foundvps_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "seg_sort_dir", indent + 1, &(val[i].seg_sort_dir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "seg_totalPEs", indent + 1, &(val[i].seg_totalPEs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "seg_vps_max", indent + 1, &(val[i].seg_vps_max), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "seg_vps_min", indent + 1, &(val[i].seg_vps_min), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "seg_vps_range", indent + 1, &(val[i].seg_vps_range), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "seg_vps_target", indent + 1, &(val[i].seg_vps_target), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "segment_tr", indent + 1, &(val[i].segment_tr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "segmented_flag", indent + 1, &(val[i].segmented_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sep3d", indent + 1, &(val[i].sep3d), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "seq3ddummytr", indent + 1, &(val[i].seq3ddummytr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "seq3dtr", indent + 1, &(val[i].seq3dtr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "seqEntryIndex", indent + 1, &(val[i].seqEntryIndex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "seq_necho", indent + 1, &(val[i].seq_necho), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "seq_type", indent + 1, &(val[i].seq_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "serviceMode", indent + 1, &(val[i].serviceMode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "set_realtime_rotmat", indent + 1, &(val[i].set_realtime_rotmat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "show_rtfilts", indent + 1, &(val[i].show_rtfilts), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "si_flow", indent + 1, &(val[i].si_flow), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sifsetwokey", indent + 1, &(val[i].sifsetwokey), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sigma1", indent + 1, &(val[i].sigma1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sigma2", indent + 1, &(val[i].sigma2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sigrammode", indent + 1, &(val[i].sigrammode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "silent_mode", indent + 1, &(val[i].silent_mode), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "silent_slew_rate", indent + 1, &(val[i].silent_slew_rate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "simulation", indent + 1, &(val[i].simulation), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "skip_initialize_dbdtopt", indent + 1, &(val[i].skip_initialize_dbdtopt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "skip_minseqseg", indent + 1, &(val[i].skip_minseqseg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "skip_navigator_prescan", indent + 1, &(val[i].skip_navigator_prescan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "skip_rotmat_search", indent + 1, &(val[i].skip_rotmat_search), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "skip_waveform_rotmat_check", indent + 1, &(val[i].skip_waveform_rotmat_check), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sl_per_chem", indent + 1, &(val[i].sl_per_chem), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "slab_fact", indent + 1, &(val[i].slab_fact), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "slab_wrap_corr", indent + 1, &(val[i].slab_wrap_corr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "slabtracking_flag", indent + 1, &(val[i].slabtracking_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sldelay", indent + 1, &(val[i].sldelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sldeltime", indent + 1, &(val[i].sldeltime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "slfreq", indent + 1, &(val[i].slfreq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "slice_col", indent + 1, &(val[i].slice_col), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "slice_dda", indent + 1, &(val[i].slice_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "slice_order", indent + 1, &(val[i].slice_order), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "slice_size", indent + 1, &(val[i].slice_size), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "slicecnt", indent + 1, &(val[i].slicecnt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "slicezp", indent + 1, &(val[i].slicezp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "slorder", indent + 1, &(val[i].slorder), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "slq_shots", indent + 1, &(val[i].slq_shots), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "slquant1", indent + 1, &(val[i].slquant1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "slquant_per_trig", indent + 1, &(val[i].slquant_per_trig), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "slthick_rfgir01", indent + 1, &(val[i].slthick_rfgir01), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "slthick_rfgir02", indent + 1, &(val[i].slthick_rfgir02), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "slthick_scale", indent + 1, &(val[i].slthick_scale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "smartPrepEdrFlag", indent + 1, &(val[i].smartPrepEdrFlag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "smartp_rtpend_wait", indent + 1, &(val[i].smartp_rtpend_wait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "smartprep_flag", indent + 1, &(val[i].smartprep_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "smartprep_was_on", indent + 1, &(val[i].smartprep_was_on), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "smoothec", indent + 1, &(val[i].smoothec), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sp_first_scan", indent + 1, &(val[i].sp_first_scan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sp_sat", indent + 1, &(val[i].sp_sat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sp_satcard_loc", indent + 1, &(val[i].sp_satcard_loc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sp_satend", indent + 1, &(val[i].sp_satend), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sp_satstart", indent + 1, &(val[i].sp_satstart), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sp_sattime", indent + 1, &(val[i].sp_sattime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "specdwells", indent + 1, &(val[i].specdwells), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "specir_delay", indent + 1, &(val[i].specir_delay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "specir_flag", indent + 1, &(val[i].specir_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "specir_ti", indent + 1, &(val[i].specir_ti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "specirsol", indent + 1, &(val[i].specirsol), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "specnavs", indent + 1, &(val[i].specnavs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "specnex", indent + 1, &(val[i].specnex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "specnuc", indent + 1, &(val[i].specnuc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "specpts", indent + 1, &(val[i].specpts), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "specsolreps", indent + 1, &(val[i].specsolreps), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "specwidth", indent + 1, &(val[i].specwidth), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "spgr_flag", indent + 1, &(val[i].spgr_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "split_dab", indent + 1, &(val[i].split_dab), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sprep_debug_flag", indent + 1, &(val[i].sprep_debug_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sprep_save_raw_data", indent + 1, &(val[i].sprep_save_raw_data), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sprep_timing_flag", indent + 1, &(val[i].sprep_timing_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "spsat_host_debug", indent + 1, &(val[i].spsat_host_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "spsat_rfupa", indent + 1, &(val[i].spsat_rfupa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "spsat_sys_type", indent + 1, &(val[i].spsat_sys_type), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "spsp_min_opvthick", indent + 1, &(val[i].spsp_min_opvthick), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "sr_flpvenc_limit", indent + 1, &(val[i].sr_flpvenc_limit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "srate", indent + 1, &(val[i].srate), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "srate_x", indent + 1, &(val[i].srate_x), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "srate_y", indent + 1, &(val[i].srate_y), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "srate_z", indent + 1, &(val[i].srate_z), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "srderate", indent + 1, &(val[i].srderate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ss_convolution_flag", indent + 1, &(val[i].ss_convolution_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ss_fa_scale_debug", indent + 1, &(val[i].ss_fa_scale_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ss_fa_scaling_flag", indent + 1, &(val[i].ss_fa_scaling_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ss_maxoff", indent + 1, &(val[i].ss_maxoff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ss_maxoffex", indent + 1, &(val[i].ss_maxoffex), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ss_min_slthk", indent + 1, &(val[i].ss_min_slthk), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ss_minslthk1", indent + 1, &(val[i].ss_minslthk1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ss_override", indent + 1, &(val[i].ss_override), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ss_psd_slthick", indent + 1, &(val[i].ss_psd_slthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ss_rewinder_flag", indent + 1, &(val[i].ss_rewinder_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ss_rf1", indent + 1, &(val[i].ss_rf1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ss_rf_wait", indent + 1, &(val[i].ss_rf_wait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ssfat", indent + 1, &(val[i].ssfat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ssfat_freq", indent + 1, &(val[i].ssfat_freq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ssfat_kaiser", indent + 1, &(val[i].ssfat_kaiser), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ssfat_nullb", indent + 1, &(val[i].ssfat_nullb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ssfat_ramp", indent + 1, &(val[i].ssfat_ramp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ssfat_rfspoil", indent + 1, &(val[i].ssfat_rfspoil), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ssfat_rotate", indent + 1, &(val[i].ssfat_rotate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ssfat_vo", indent + 1, &(val[i].ssfat_vo), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ssfharea", indent + 1, &(val[i].ssfharea), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ssfp_flag", indent + 1, &(val[i].ssfp_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ssfp_symmetry_flag", indent + 1, &(val[i].ssfp_symmetry_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ssfse_ir_on", indent + 1, &(val[i].ssfse_ir_on), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ssp_pwisi7", indent + 1, &(val[i].ssp_pwisi7), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sszchop", indent + 1, &(val[i].sszchop), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "start_gycylra", indent + 1, &(val[i].start_gycylra), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "start_gycylratipup", indent + 1, &(val[i].start_gycylratipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "start_gzcylra", indent + 1, &(val[i].start_gzcylra), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "start_gzcylratipup", indent + 1, &(val[i].start_gzcylratipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "std_amp", indent + 1, &(val[i].std_amp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "steam_pg_gap", indent + 1, &(val[i].steam_pg_gap), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "stopwatchFlag", indent + 1, &(val[i].stopwatchFlag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "stre_flag", indent + 1, &(val[i].stre_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sun_done_flag", indent + 1, &(val[i].sun_done_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sun_success_flag1", indent + 1, &(val[i].sun_success_flag1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sun_success_flag2", indent + 1, &(val[i].sun_success_flag2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "swan_flag", indent + 1, &(val[i].swan_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "swanfirstTE", indent + 1, &(val[i].swanfirstTE), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "swap_fat_cs", indent + 1, &(val[i].swap_fat_cs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "swap_mon_zy", indent + 1, &(val[i].swap_mon_zy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "swap_monplane", indent + 1, &(val[i].swap_monplane), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "system_type", indent + 1, &(val[i].system_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t1flair_flag", indent + 1, &(val[i].t1flair_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "t2pk_area", indent + 1, &(val[i].t2pk_area), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t2pk_delay", indent + 1, &(val[i].t2pk_delay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t2prep_flag", indent + 1, &(val[i].t2prep_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t2prep_num180", indent + 1, &(val[i].t2prep_num180), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "t2prep_rate", indent + 1, &(val[i].t2prep_rate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t2prep_t180", indent + 1, &(val[i].t2prep_t180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t2prep_tseq", indent + 1, &(val[i].t2prep_tseq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t_exa", indent + 1, &(val[i].t_exa), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t_exa_cylr", indent + 1, &(val[i].t_exa_cylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t_exaas", indent + 1, &(val[i].t_exaas), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t_exb", indent + 1, &(val[i].t_exb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t_exb_cylr", indent + 1, &(val[i].t_exb_cylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t_rd1a", indent + 1, &(val[i].t_rd1a), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t_rd1a_frac", indent + 1, &(val[i].t_rd1a_frac), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t_rd1a_full", indent + 1, &(val[i].t_rd1a_full), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t_rdb", indent + 1, &(val[i].t_rdb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t_rdb_cylr", indent + 1, &(val[i].t_rdb_cylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t_rdb_frac", indent + 1, &(val[i].t_rdb_frac), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t_rdb_full", indent + 1, &(val[i].t_rdb_full), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t_slice2read", indent + 1, &(val[i].t_slice2read), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "t_slicereadgap", indent + 1, &(val[i].t_slicereadgap), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ta_180sp", indent + 1, &(val[i].ta_180sp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tableaccel", indent + 1, &(val[i].tableaccel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tabledecel", indent + 1, &(val[i].tabledecel), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tablespeed", indent + 1, &(val[i].tablespeed), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "targ_dr", indent + 1, &(val[i].targ_dr), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "targ_dr_ramp", indent + 1, &(val[i].targ_dr_ramp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "target_cfh_crusher", indent + 1, &(val[i].target_cfh_crusher), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "target_cfh_crusher2", indent + 1, &(val[i].target_cfh_crusher2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "target_ti", indent + 1, &(val[i].target_ti), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tb_180sp", indent + 1, &(val[i].tb_180sp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "td0", indent + 1, &(val[i].td0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "td0as", indent + 1, &(val[i].td0as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "td0dtg", indent + 1, &(val[i].td0dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "td0rs", indent + 1, &(val[i].td0rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tdaq", indent + 1, &(val[i].tdaq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tdel1_time", indent + 1, &(val[i].tdel1_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tdel1_tmp", indent + 1, &(val[i].tdel1_tmp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "te_180sp", indent + 1, &(val[i].te_180sp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "te_as", indent + 1, &(val[i].te_as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "te_time", indent + 1, &(val[i].te_time), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "temp_factor", indent + 1, &(val[i].temp_factor), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "temp_float", indent + 1, &(val[i].temp_float), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_grd", indent + 1, &(val[i].temp_grd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rf1as", indent + 1, &(val[i].temp_res_rf1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rf1cfh", indent + 1, &(val[i].temp_res_rf1cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rf1cfl", indent + 1, &(val[i].temp_res_rf1cfl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rf1ftg", indent + 1, &(val[i].temp_res_rf1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rf1mon", indent + 1, &(val[i].temp_res_rf1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rf2ftg", indent + 1, &(val[i].temp_res_rf2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rf2mon", indent + 1, &(val[i].temp_res_rf2mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rf2mps1", indent + 1, &(val[i].temp_res_rf2mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rf2xtg", indent + 1, &(val[i].temp_res_rf2xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rf3ftg", indent + 1, &(val[i].temp_res_rf3ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rfmontipup", indent + 1, &(val[i].temp_res_rfmontipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rfse1", indent + 1, &(val[i].temp_res_rfse1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rfse2", indent + 1, &(val[i].temp_res_rfse2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rfse3", indent + 1, &(val[i].temp_res_rfse3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rfse4", indent + 1, &(val[i].temp_res_rfse4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rfse5", indent + 1, &(val[i].temp_res_rfse5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rfse6", indent + 1, &(val[i].temp_res_rfse6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rfsx1", indent + 1, &(val[i].temp_res_rfsx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rfsx2", indent + 1, &(val[i].temp_res_rfsx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rfsy1", indent + 1, &(val[i].temp_res_rfsy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rfsy2", indent + 1, &(val[i].temp_res_rfsy2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rfsz1", indent + 1, &(val[i].temp_res_rfsz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_res_rfsz2", indent + 1, &(val[i].temp_res_rfsz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "temp_rf", indent + 1, &(val[i].temp_rf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tfe_extra", indent + 1, &(val[i].tfe_extra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tg_1_2_pw", indent + 1, &(val[i].tg_1_2_pw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tg_axial", indent + 1, &(val[i].tg_axial), 1);
#endif
#ifdef SIZEOF_WF_PROCESSOR
    print_brsfc_WF_PROCESSOR(fp, "tg_killer_axis", indent + 1, &(val[i].tg_killer_axis), 1);
#endif
#ifdef SIZEOF_WF_PROCESSOR
    print_brsfc_WF_PROCESSOR(fp, "tg_read_axis", indent + 1, &(val[i].tg_read_axis), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tgcap", indent + 1, &(val[i].tgcap), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tgfov", indent + 1, &(val[i].tgfov), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tgwindow", indent + 1, &(val[i].tgwindow), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "theta", indent + 1, &(val[i].theta), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "thetatype", indent + 1, &(val[i].thetatype), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thickPS_mod", indent + 1, &(val[i].thickPS_mod), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rf0", indent + 1, &(val[i].thk_rf0), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rf0cfh", indent + 1, &(val[i].thk_rf0cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rf1", indent + 1, &(val[i].thk_rf1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rf1as", indent + 1, &(val[i].thk_rf1as), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rf1cfh", indent + 1, &(val[i].thk_rf1cfh), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rf1cfl", indent + 1, &(val[i].thk_rf1cfl), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rf1ftg", indent + 1, &(val[i].thk_rf1ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rf1mon", indent + 1, &(val[i].thk_rf1mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rf1tm", indent + 1, &(val[i].thk_rf1tm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rf2ftg", indent + 1, &(val[i].thk_rf2ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rf2mon", indent + 1, &(val[i].thk_rf2mon), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rf2mps1", indent + 1, &(val[i].thk_rf2mps1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rf2xtg", indent + 1, &(val[i].thk_rf2xtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rf3ftg", indent + 1, &(val[i].thk_rf3ftg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rffrir", indent + 1, &(val[i].thk_rffrir), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rfgir01", indent + 1, &(val[i].thk_rfgir01), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rfgir02", indent + 1, &(val[i].thk_rfgir02), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rfmontipup", indent + 1, &(val[i].thk_rfmontipup), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rfse1", indent + 1, &(val[i].thk_rfse1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rfse2", indent + 1, &(val[i].thk_rfse2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rfse3", indent + 1, &(val[i].thk_rfse3), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rfse4", indent + 1, &(val[i].thk_rfse4), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rfse5", indent + 1, &(val[i].thk_rfse5), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rfse6", indent + 1, &(val[i].thk_rfse6), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rfsx1", indent + 1, &(val[i].thk_rfsx1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rfsx2", indent + 1, &(val[i].thk_rfsx2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rfsy1", indent + 1, &(val[i].thk_rfsy1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rfsy2", indent + 1, &(val[i].thk_rfsy2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rfsz1", indent + 1, &(val[i].thk_rfsz1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "thk_rfsz2", indent + 1, &(val[i].thk_rfsz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "threedpktdly", indent + 1, &(val[i].threedpktdly), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ti_rfgir01", indent + 1, &(val[i].ti_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ti_rfgir02", indent + 1, &(val[i].ti_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_between_rfflp180_venc", indent + 1, &(val[i].time_between_rfflp180_venc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_between_rfflp90_venc", indent + 1, &(val[i].time_between_rfflp90_venc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_between_venc1_2", indent + 1, &(val[i].time_between_venc1_2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_between_venc2_3", indent + 1, &(val[i].time_between_venc2_3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_between_venc_rfflp180", indent + 1, &(val[i].time_between_venc_rfflp180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_between_venc_rfflp90r", indent + 1, &(val[i].time_between_venc_rfflp90r), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_fsprep", indent + 1, &(val[i].time_fsprep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_killer", indent + 1, &(val[i].time_killer), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_pgen", indent + 1, &(val[i].time_pgen), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_s5fpprep", indent + 1, &(val[i].time_s5fpprep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_seqwait", indent + 1, &(val[i].time_seqwait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_spoiler", indent + 1, &(val[i].time_spoiler), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_ssfprep", indent + 1, &(val[i].time_ssfprep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_ssi", indent + 1, &(val[i].time_ssi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_ssi_pre", indent + 1, &(val[i].time_ssi_pre), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_ssias", indent + 1, &(val[i].time_ssias), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_ssidtg", indent + 1, &(val[i].time_ssidtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_ssirs", indent + 1, &(val[i].time_ssirs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_wait2", indent + 1, &(val[i].time_wait2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_wait3", indent + 1, &(val[i].time_wait3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "time_wait4", indent + 1, &(val[i].time_wait4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "timefcx", indent + 1, &(val[i].timefcx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "timefcy", indent + 1, &(val[i].timefcy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "timefcz", indent + 1, &(val[i].timefcz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "timefcz_echo1", indent + 1, &(val[i].timefcz_echo1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tlead", indent + 1, &(val[i].tlead), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tlead_cylnav", indent + 1, &(val[i].tlead_cylnav), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tlead_monitor", indent + 1, &(val[i].tlead_monitor), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tlead_montipup", indent + 1, &(val[i].tlead_montipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tleadas", indent + 1, &(val[i].tleadas), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tleadcs", indent + 1, &(val[i].tleadcs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tleaddtg", indent + 1, &(val[i].tleaddtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tleadrs", indent + 1, &(val[i].tleadrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tm_axis", indent + 1, &(val[i].tm_axis), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tm_disdaqs", indent + 1, &(val[i].tm_disdaqs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tm_flag", indent + 1, &(val[i].tm_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tm_flip", indent + 1, &(val[i].tm_flip), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tm_locstep", indent + 1, &(val[i].tm_locstep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tm_nex", indent + 1, &(val[i].tm_nex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tm_ns", indent + 1, &(val[i].tm_ns), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tm_pos_start", indent + 1, &(val[i].tm_pos_start), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tm_prepslice_flag", indent + 1, &(val[i].tm_prepslice_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tm_scale", indent + 1, &(val[i].tm_scale), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tm_slthick", indent + 1, &(val[i].tm_slthick), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tm_spiral_delay", indent + 1, &(val[i].tm_spiral_delay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tm_time", indent + 1, &(val[i].tm_time), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tm_xloc", indent + 1, &(val[i].tm_xloc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tm_yloc", indent + 1, &(val[i].tm_yloc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tmin", indent + 1, &(val[i].tmin), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tmin_mon", indent + 1, &(val[i].tmin_mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tmin_montipup", indent + 1, &(val[i].tmin_montipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tmin_reduced", indent + 1, &(val[i].tmin_reduced), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tmin_satoff", indent + 1, &(val[i].tmin_satoff), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tmin_total", indent + 1, &(val[i].tmin_total), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tmpbw", indent + 1, &(val[i].tmpbw), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tmpbw1", indent + 1, &(val[i].tmpbw1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tns_len", indent + 1, &(val[i].tns_len), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tnslength", indent + 1, &(val[i].tnslength), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tof_lowflip_asset_flag", indent + 1, &(val[i].tof_lowflip_asset_flag), 1);
#endif
#ifdef SIZEOF_POSITION_DETECTION_DONE_TYPE
    print_brsfc_POSITION_DETECTION_DONE_TYPE(fp, "topofhead", indent + 1, &(val[i].topofhead), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "total_acq_points", indent + 1, &(val[i].total_acq_points), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "total_acq_regions", indent + 1, &(val[i].total_acq_regions), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "total_area_gx", indent + 1, &(val[i].total_area_gx), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "total_area_gxfc", indent + 1, &(val[i].total_area_gxfc), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "total_area_gz", indent + 1, &(val[i].total_area_gz), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "total_area_gzfc", indent + 1, &(val[i].total_area_gzfc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "total_quiet_dda", indent + 1, &(val[i].total_quiet_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "totalecregions", indent + 1, &(val[i].totalecregions), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tr_as", indent + 1, &(val[i].tr_as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tr_dtg", indent + 1, &(val[i].tr_dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tr_pad", indent + 1, &(val[i].tr_pad), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tr_prep_rs", indent + 1, &(val[i].tr_prep_rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tr_rs", indent + 1, &(val[i].tr_rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "track_flag", indent + 1, &(val[i].track_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tracker_quant", indent + 1, &(val[i].tracker_quant), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "transpose_monloc", indent + 1, &(val[i].transpose_monloc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tricks_check", indent + 1, &(val[i].tricks_check), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tricks_debug", indent + 1, &(val[i].tricks_debug), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tricks_delay", indent + 1, &(val[i].tricks_delay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tricks_flag", indent + 1, &(val[i].tricks_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tricks_index", indent + 1, &(val[i].tricks_index), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tricks_index2", indent + 1, &(val[i].tricks_index2), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tricks_mask_time", indent + 1, &(val[i].tricks_mask_time), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tricks_maxecho", indent + 1, &(val[i].tricks_maxecho), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tricks_maxphases", indent + 1, &(val[i].tricks_maxphases), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tricks_maxseries", indent + 1, &(val[i].tricks_maxseries), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tricks_minecho", indent + 1, &(val[i].tricks_minecho), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tricks_stop", indent + 1, &(val[i].tricks_stop), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tricks_transition_views", indent + 1, &(val[i].tricks_transition_views), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tricksdda", indent + 1, &(val[i].tricksdda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "trig_aps2", indent + 1, &(val[i].trig_aps2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "trig_mps2", indent + 1, &(val[i].trig_mps2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "trig_prescan", indent + 1, &(val[i].trig_prescan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "trig_scan", indent + 1, &(val[i].trig_scan), 1);
#endif
#ifdef SIZEOF_LONG
    print_brsfc_LONG(fp, "triggerState", indent + 1, &(val[i].triggerState), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "trigger_delay_silent_countdown", indent + 1, &(val[i].trigger_delay_silent_countdown), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "trigger_delay_wosp", indent + 1, &(val[i].trigger_delay_wosp), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "truenex", indent + 1, &(val[i].truenex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tsamp", indent + 1, &(val[i].tsamp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tseq_gzk", indent + 1, &(val[i].tseq_gzk), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tseq_irprep", indent + 1, &(val[i].tseq_irprep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tseq_msde", indent + 1, &(val[i].tseq_msde), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "tseq_prep_frir", indent + 1, &(val[i].tseq_prep_frir), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "tsp", indent + 1, &(val[i].tsp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "turbo_cemra_enable", indent + 1, &(val[i].turbo_cemra_enable), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "turbo_cemra_flag", indent + 1, &(val[i].turbo_cemra_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "turbo_flag", indent + 1, &(val[i].turbo_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "twaitt2prep", indent + 1, &(val[i].twaitt2prep), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ugfsf_flag", indent + 1, &(val[i].ugfsf_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ugfsf_flat_dda", indent + 1, &(val[i].ugfsf_flat_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ugfsf_linear_ramp_down", indent + 1, &(val[i].ugfsf_linear_ramp_down), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ugfsf_ramp_dda", indent + 1, &(val[i].ugfsf_ramp_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ugfsf_shot_delay", indent + 1, &(val[i].ugfsf_shot_delay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ugfsf_slice_dda", indent + 1, &(val[i].ugfsf_slice_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ugfsf_slice_order_flag", indent + 1, &(val[i].ugfsf_slice_order_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ugfsf_view_order_flag", indent + 1, &(val[i].ugfsf_view_order_flag), 1);
#endif
#ifdef SIZEOF_COIL_INFO
    print_brsfc_COIL_INFO(fp, "coilInfo_tgt", indent + 1, (COIL_INFO *)(val[i].coilInfo_tgt), (10));
#endif
#ifdef SIZEOF_COIL_INFO
    print_brsfc_COIL_INFO(fp, "volRecCoilInfo_tgt", indent + 1, (COIL_INFO *)(val[i].volRecCoilInfo_tgt), (10));
#endif
#ifdef SIZEOF_DATA_ACQ_ORDER
    print_brsfc_DATA_ACQ_ORDER(fp, "data_acq_order", indent + 1, (DATA_ACQ_ORDER *)(val[i].data_acq_order), (2048));
#endif
#ifdef SIZEOF_GIR_INFO
    print_brsfc_GIR_INFO(fp, "gir_info", indent + 1, (GIR_INFO *)(val[i].gir_info), (2));
#endif
#ifdef SIZEOF_GRAD_PULSE
    print_brsfc_GRAD_PULSE(fp, "gradx", indent + 1, (GRAD_PULSE *)(val[i].gradx), (15));
#endif
#ifdef SIZEOF_GRAD_PULSE
    print_brsfc_GRAD_PULSE(fp, "grady", indent + 1, (GRAD_PULSE *)(val[i].grady), (24));
#endif
#ifdef SIZEOF_GRAD_PULSE
    print_brsfc_GRAD_PULSE(fp, "gradz", indent + 1, (GRAD_PULSE *)(val[i].gradz), (26));
#endif
#ifdef SIZEOF_PHASE_OFF
    print_brsfc_PHASE_OFF(fp, "phase_off", indent + 1, (PHASE_OFF *)(val[i].phase_off), (2048));
#endif
#ifdef SIZEOF_PSC_INFO
    print_brsfc_PSC_INFO(fp, "presscfh_info", indent + 1, (PSC_INFO *)(val[i].presscfh_info), (5));
#endif
#ifdef SIZEOF_PSC_INFO
    print_brsfc_PSC_INFO(fp, "psc_info", indent + 1, (PSC_INFO *)(val[i].psc_info), (5));
#endif
#ifdef SIZEOF_PSD_FILTER_GEN
    print_brsfc_PSD_FILTER_GEN(fp, "psd_filt_spec", indent + 1, (PSD_FILTER_GEN *)(val[i].psd_filt_spec), (16));
#endif
#ifdef SIZEOF_RF_PULSE
    print_brsfc_RF_PULSE(fp, "rfpulse", indent + 1, (RF_PULSE *)(val[i].rfpulse), (53));
#endif
#ifdef SIZEOF_RF_PULSE_INFO
    print_brsfc_RF_PULSE_INFO(fp, "rfpulseInfo", indent + 1, (RF_PULSE_INFO *)(val[i].rfpulseInfo), (53));
#endif
#ifdef SIZEOF_RSP_INFO
    print_brsfc_RSP_INFO(fp, "asrsp_info", indent + 1, (RSP_INFO *)(val[i].asrsp_info), (3));
#endif
#ifdef SIZEOF_RSP_INFO
    print_brsfc_RSP_INFO(fp, "dtgrsp_info", indent + 1, (RSP_INFO *)(val[i].dtgrsp_info), (5));
#endif
#ifdef SIZEOF_RSP_INFO
    print_brsfc_RSP_INFO(fp, "mon_rsp_info2", indent + 1, (RSP_INFO *)(val[i].mon_rsp_info2), (1));
#endif
#ifdef SIZEOF_RSP_INFO
    print_brsfc_RSP_INFO(fp, "mon_rsp_info", indent + 1, (RSP_INFO *)(val[i].mon_rsp_info), (1));
#endif
#ifdef SIZEOF_RSP_INFO
    print_brsfc_RSP_INFO(fp, "rsp_info", indent + 1, (RSP_INFO *)(val[i].rsp_info), (2048));
#endif
#ifdef SIZEOF_RSP_INFO
    print_brsfc_RSP_INFO(fp, "rsrsp_info", indent + 1, (RSP_INFO *)(val[i].rsrsp_info), (1));
#endif
#ifdef SIZEOF_RSP_PSC_INFO
    print_brsfc_RSP_PSC_INFO(fp, "rsp_psc_info", indent + 1, (RSP_PSC_INFO *)(val[i].rsp_psc_info), (5));
#endif
#ifdef SIZEOF_SCAN_INFO
    print_brsfc_SCAN_INFO(fp, "asscan_info", indent + 1, (SCAN_INFO *)(val[i].asscan_info), (3));
#endif
#ifdef SIZEOF_SCAN_INFO
    print_brsfc_SCAN_INFO(fp, "scan_info", indent + 1, (SCAN_INFO *)(val[i].scan_info), (2048));
#endif
#ifdef SIZEOF_SCAN_INFO
    print_brsfc_SCAN_INFO(fp, "scan_info_base", indent + 1, (SCAN_INFO *)(val[i].scan_info_base), (1));
#endif
#ifdef SIZEOF_SLAB_OFF
    print_brsfc_SLAB_OFF(fp, "slab_off", indent + 1, (SLAB_OFF *)(val[i].slab_off), (256));
#endif
#ifdef SIZEOF_SPIRAL_VIEW
    print_brsfc_SPIRAL_VIEW(fp, "brs_viewtab", indent + 1, (SPIRAL_VIEW *)(val[i].brs_viewtab), (131072));
#endif
#ifdef SIZEOF_TX_COIL_INFO
    print_brsfc_TX_COIL_INFO(fp, "txCoilInfo_tgt", indent + 1, (TX_COIL_INFO *)(val[i].txCoilInfo_tgt), (5));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "hgzssfn", indent + 1, (char *)(val[i].hgzssfn), (40));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "piamval1", indent + 1, (char *)(val[i].piamval1), (8));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "piamval2", indent + 1, (char *)(val[i].piamval2), (8));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "piamval3", indent + 1, (char *)(val[i].piamval3), (8));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "piamval4", indent + 1, (char *)(val[i].piamval4), (8));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "piamval5", indent + 1, (char *)(val[i].piamval5), (8));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "piamval6", indent + 1, (char *)(val[i].piamval6), (8));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "pidfirecval2", indent + 1, (char *)(val[i].pidfirecval2), (30));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "pidfirecval3", indent + 1, (char *)(val[i].pidfirecval3), (30));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "pidfirecval4", indent + 1, (char *)(val[i].pidfirecval4), (30));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "pidfirecval5", indent + 1, (char *)(val[i].pidfirecval5), (30));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "pidifaxval1", indent + 1, (char *)(val[i].pidifaxval1), (7));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "pidifaxval2", indent + 1, (char *)(val[i].pidifaxval2), (7));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "pidifaxval3", indent + 1, (char *)(val[i].pidifaxval3), (7));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "pidifaxval4", indent + 1, (char *)(val[i].pidifaxval4), (7));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "pidifaxval5", indent + 1, (char *)(val[i].pidifaxval5), (7));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "pidifaxval6", indent + 1, (char *)(val[i].pidifaxval6), (7));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "pidifrecval1", indent + 1, (char *)(val[i].pidifrecval1), (30));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "pitrecoverylabel", indent + 1, (char *)(val[i].pitrecoverylabel), (32));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "ssgzfile", indent + 1, (char *)(val[i].ssgzfile), (40));
#endif
#ifdef SIZEOF_char
    print_brsfc_char(fp, "ssrffile", indent + 1, (char *)(val[i].ssrffile), (40));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "body_sar_table", indent + 1, (float *)(val[i].body_sar_table), (360));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "brs_mfa_angles", indent + 1, (float *)(val[i].brs_mfa_angles), (24));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "eg_sat_rot", indent + 1, (float *)(val[i].eg_sat_rot), (6)*(9));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "extremity_sar_table", indent + 1, (float *)(val[i].extremity_sar_table), (360));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flp_venc_x", indent + 1, (float *)(val[i].flp_venc_x), (8));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flp_venc_y", indent + 1, (float *)(val[i].flp_venc_y), (8));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "flp_venc_z", indent + 1, (float *)(val[i].flp_venc_z), (8));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "head_sar_table", indent + 1, (float *)(val[i].head_sar_table), (360));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "osfp_vfa", indent + 1, (float *)(val[i].osfp_vfa), (512));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ratio_rfflp180", indent + 1, (float *)(val[i].ratio_rfflp180), (4));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rfgir01_info", indent + 1, (float *)(val[i].rfgir01_info), (2)*(9));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rfgir02_info", indent + 1, (float *)(val[i].rfgir02_info), (2)*(9));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rhdiffusion_grad_amp", indent + 1, (float *)(val[i].rhdiffusion_grad_amp), (512)*(3));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "rotmatrix", indent + 1, (float *)(val[i].rotmatrix), (9));
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xyz_base", indent + 1, (float *)(val[i].xyz_base), (2048)*(3));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "PSfreq_offset", indent + 1, (int *)(val[i].PSfreq_offset), (20));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "PhaseDoneSchedule", indent + 1, (int *)(val[i].PhaseDoneSchedule), (513));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "RegionSchedule", indent + 1, (int *)(val[i].RegionSchedule), (100));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "RegionsSchedule", indent + 1, (int *)(val[i].RegionsSchedule), (4561));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "arcPhaseRemapTable", indent + 1, (int *)(val[i].arcPhaseRemapTable), (1025));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "arcSliceRemapTable", indent + 1, (int *)(val[i].arcSliceRemapTable), (2048));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_jumptab", indent + 1, (int *)(val[i].brs_jumptab), (1024));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_savrot", indent + 1, (int *)(val[i].brs_savrot), (4096)*(9));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_xgrad2", indent + 1, (int *)(val[i].brs_xgrad2), (16384));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_xgrad", indent + 1, (int *)(val[i].brs_xgrad), (16384));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_ygrad2", indent + 1, (int *)(val[i].brs_ygrad2), (16384));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "brs_ygrad", indent + 1, (int *)(val[i].brs_ygrad), (16384));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cum_regs_per_phase", indent + 1, (int *)(val[i].cum_regs_per_phase), (513));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "cum_views_per_region", indent + 1, (int *)(val[i].cum_views_per_region), (32));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ectricks_kernel_regions", indent + 1, (int *)(val[i].ectricks_kernel_regions), (16));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ectricks_mask_regions", indent + 1, (int *)(val[i].ectricks_mask_regions), (8));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "extraspecial_slice", indent + 1, (int *)(val[i].extraspecial_slice), (2048));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzvlwa", indent + 1, (int *)(val[i].ia_gzvlwa), (2048));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_gzvlwb", indent + 1, (int *)(val[i].ia_gzvlwb), (2048));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ia_rf1_osfp", indent + 1, (int *)(val[i].ia_rf1_osfp), (512));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfcsz", indent + 1, (int *)(val[i].off_rfcsz), (1));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "off_rfcsz_base", indent + 1, (int *)(val[i].off_rfcsz_base), (2048));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzvl", indent + 1, (int *)(val[i].pw_gzvl), (2048));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzvla", indent + 1, (int *)(val[i].pw_gzvla), (2048));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "pw_gzvld", indent + 1, (int *)(val[i].pw_gzvld), (2048));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "regs_per_phase", indent + 1, (int *)(val[i].regs_per_phase), (513));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "sat_rot_ex_indices", indent + 1, (int *)(val[i].sat_rot_ex_indices), (7));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "slicetab", indent + 1, (int *)(val[i].slicetab), (2048));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "volumetab2", indent + 1, (int *)(val[i].volumetab2), (2048));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "volumetab", indent + 1, (int *)(val[i].volumetab), (2048));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zfctab", indent + 1, (int *)(val[i].zfctab), (2048));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zfctab_echo1", indent + 1, (int *)(val[i].zfctab_echo1), (2048));
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "PSrot", indent + 1, (long int *)(val[i].PSrot), (1)*(9));
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "PSrot_mod", indent + 1, (long int *)(val[i].PSrot_mod), (1)*(9));
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "dtgrsprot", indent + 1, (long int *)(val[i].dtgrsprot), (5)*(9));
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "ipg_alloc_instr", indent + 1, (long int *)(val[i].ipg_alloc_instr), (9));
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "nav_channel_bit", indent + 1, (long int *)(val[i].nav_channel_bit), (4));
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "navscm_channel_bit", indent + 1, (long int *)(val[i].navscm_channel_bit), (4));
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "rfgir01_rot_info", indent + 1, (long int *)(val[i].rfgir01_rot_info), (2)*(9));
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "rfgir02_rot_info", indent + 1, (long int *)(val[i].rfgir02_rot_info), (2)*(9));
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "rsp_PSrot", indent + 1, (long int *)(val[i].rsp_PSrot), (5)*(9));
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "rsprot", indent + 1, (long int *)(val[i].rsprot), (4096)*(9));
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "rsprot_base", indent + 1, (long int *)(val[i].rsprot_base), (4096)*(9));
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "rsprot_gir", indent + 1, (long int *)(val[i].rsprot_gir), (5)*(9));
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "rsprot_monitor", indent + 1, (long int *)(val[i].rsprot_monitor), (1)*(9));
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "rsptrigger", indent + 1, (long int *)(val[i].rsptrigger), (4096));
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "rsrsprot", indent + 1, (long int *)(val[i].rsrsprot), (1)*(9));
#endif
#ifdef SIZEOF_long_int
    print_brsfc_long_int(fp, "sat_rot_matrices", indent + 1, (long int *)(val[i].sat_rot_matrices), (14)*(9));
#endif
#ifdef SIZEOF_n32
    print_brsfc_n32(fp, "mcbias_info", indent + 1, (n32 *)(val[i].mcbias_info), (3));
#endif
#ifdef SIZEOF_short_int
    print_brsfc_short_int(fp, "aslimgtab", indent + 1, (short int *)(val[i].aslimgtab), (3));
#endif
#ifdef SIZEOF_short_int
    print_brsfc_short_int(fp, "aslnextab", indent + 1, (short int *)(val[i].aslnextab), (3));
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ulimte1", indent + 1, &(val[i].ulimte1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ulimte2", indent + 1, &(val[i].ulimte2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "ulimte3", indent + 1, &(val[i].ulimte3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "unaccel_dayres", indent + 1, &(val[i].unaccel_dayres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "unaccel_rhnframes", indent + 1, &(val[i].unaccel_rhnframes), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "uniPolar_flag", indent + 1, &(val[i].uniPolar_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "upmxdisable", indent + 1, &(val[i].upmxdisable), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "useFirstEchoComp", indent + 1, &(val[i].useFirstEchoComp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "use_dbdt_opt", indent + 1, &(val[i].use_dbdt_opt), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "use_ecg_scancore", indent + 1, &(val[i].use_ecg_scancore), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "use_ermes", indent + 1, &(val[i].use_ermes), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "use_myscan", indent + 1, &(val[i].use_myscan), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "use_slr_inv", indent + 1, &(val[i].use_slr_inv), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "usevenc", indent + 1, &(val[i].usevenc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "val15_lock", indent + 1, &(val[i].val15_lock), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "valid_decimation", indent + 1, &(val[i].valid_decimation), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "valid_max_rbw", indent + 1, &(val[i].valid_max_rbw), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "valid_rbw", indent + 1, &(val[i].valid_rbw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "value_system_flag", indent + 1, &(val[i].value_system_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "vas_ovrhd", indent + 1, &(val[i].vas_ovrhd), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "vast_mode", indent + 1, &(val[i].vast_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "vast_symm", indent + 1, &(val[i].vast_symm), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "velocity_3in1", indent + 1, &(val[i].velocity_3in1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "velocity_single", indent + 1, &(val[i].velocity_single), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "velocity_venc", indent + 1, &(val[i].velocity_venc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "venc_direction_bitmask", indent + 1, &(val[i].venc_direction_bitmask), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "venc_polarity_mode", indent + 1, &(val[i].venc_polarity_mode), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "vibrant_flag", indent + 1, &(val[i].vibrant_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "vibrantxv_flag", indent + 1, &(val[i].vibrantxv_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "view_per_shot", indent + 1, &(val[i].view_per_shot), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "view_to_center", indent + 1, &(val[i].view_to_center), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "viewoffs", indent + 1, &(val[i].viewoffs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "views_per_segment", indent + 1, &(val[i].views_per_segment), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "viewshd_num", indent + 1, &(val[i].viewshd_num), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "viewsperregion", indent + 1, &(val[i].viewsperregion), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "vol_ratio_est_req", indent + 1, &(val[i].vol_ratio_est_req), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "vol_scale_constraint_type", indent + 1, &(val[i].vol_scale_constraint_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "vol_scale_type", indent + 1, &(val[i].vol_scale_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "vol_shift_constraint_type", indent + 1, &(val[i].vol_shift_constraint_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "vol_shift_type", indent + 1, &(val[i].vol_shift_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "vrg_sat", indent + 1, &(val[i].vrg_sat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "vrgfsamp", indent + 1, &(val[i].vrgfsamp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "vrgsat", indent + 1, &(val[i].vrgsat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "vstrte_flag", indent + 1, &(val[i].vstrte_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "w_z1", indent + 1, &(val[i].w_z1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "w_zfc", indent + 1, &(val[i].w_zfc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "waitTime", indent + 1, &(val[i].waitTime), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wait_flpk", indent + 1, &(val[i].wait_flpk), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wait_pts", indent + 1, &(val[i].wait_pts), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_cfh_rf3", indent + 1, &(val[i].wg_cfh_rf3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_cfh_rf4", indent + 1, &(val[i].wg_cfh_rf4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_csw_wait", indent + 1, &(val[i].wg_csw_wait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_dix_ssppost", indent + 1, &(val[i].wg_dix_ssppost), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_dix_ssppre", indent + 1, &(val[i].wg_dix_ssppre), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_dix_xpre", indent + 1, &(val[i].wg_dix_xpre), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_dummyrf", indent + 1, &(val[i].wg_dummyrf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gate_isi", indent + 1, &(val[i].wg_gate_isi), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gx1", indent + 1, &(val[i].wg_gx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gx1as", indent + 1, &(val[i].wg_gx1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gx1bftg", indent + 1, &(val[i].wg_gx1bftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gx1bxtg", indent + 1, &(val[i].wg_gx1bxtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gx1cfh", indent + 1, &(val[i].wg_gx1cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gx1dtg", indent + 1, &(val[i].wg_gx1dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gx1ftg", indent + 1, &(val[i].wg_gx1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gx1mon", indent + 1, &(val[i].wg_gx1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gx1mps1", indent + 1, &(val[i].wg_gx1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gx1rs", indent + 1, &(val[i].wg_gx1rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gx1tm", indent + 1, &(val[i].wg_gx1tm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gx2", indent + 1, &(val[i].wg_gx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gx2dtg", indent + 1, &(val[i].wg_gx2dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gx2ftg", indent + 1, &(val[i].wg_gx2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gx2rs", indent + 1, &(val[i].wg_gx2rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gx2test", indent + 1, &(val[i].wg_gx2test), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxb", indent + 1, &(val[i].wg_gxb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxbrsfc1", indent + 1, &(val[i].wg_gxbrsfc1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxbrsfc2", indent + 1, &(val[i].wg_gxbrsfc2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxfc", indent + 1, &(val[i].wg_gxfc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxfcmon", indent + 1, &(val[i].wg_gxfcmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxflpk", indent + 1, &(val[i].wg_gxflpk), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxflpvenc", indent + 1, &(val[i].wg_gxflpvenc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxhyst1", indent + 1, &(val[i].wg_gxhyst1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxhyst2", indent + 1, &(val[i].wg_gxhyst2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxkas", indent + 1, &(val[i].wg_gxkas), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxkbsdtg", indent + 1, &(val[i].wg_gxkbsdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxkbsrs", indent + 1, &(val[i].wg_gxkbsrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxkcs", indent + 1, &(val[i].wg_gxkcs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxkdtg", indent + 1, &(val[i].wg_gxkdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxkfs", indent + 1, &(val[i].wg_gxkfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxkill", indent + 1, &(val[i].wg_gxkill), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxkrcvn", indent + 1, &(val[i].wg_gxkrcvn), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxkrs", indent + 1, &(val[i].wg_gxkrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxks", indent + 1, &(val[i].wg_gxks), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxkse1", indent + 1, &(val[i].wg_gxkse1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxkse2", indent + 1, &(val[i].wg_gxkse2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxkse3", indent + 1, &(val[i].wg_gxkse3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxkse4", indent + 1, &(val[i].wg_gxkse4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxkse5", indent + 1, &(val[i].wg_gxkse5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxkse6", indent + 1, &(val[i].wg_gxkse6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxksp", indent + 1, &(val[i].wg_gxksp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxkssf", indent + 1, &(val[i].wg_gxkssf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxksx1", indent + 1, &(val[i].wg_gxksx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxksx2", indent + 1, &(val[i].wg_gxksx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxksy1", indent + 1, &(val[i].wg_gxksy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxksy2", indent + 1, &(val[i].wg_gxksy2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxksz1", indent + 1, &(val[i].wg_gxksz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxksz2", indent + 1, &(val[i].wg_gxksz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxrf2cfh", indent + 1, &(val[i].wg_gxrf2cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxspoil", indent + 1, &(val[i].wg_gxspoil), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxspoil2", indent + 1, &(val[i].wg_gxspoil2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxw", indent + 1, &(val[i].wg_gxw), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxw1ftg", indent + 1, &(val[i].wg_gxw1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxw1xtg", indent + 1, &(val[i].wg_gxw1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxw2", indent + 1, &(val[i].wg_gxw2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxw2dtg", indent + 1, &(val[i].wg_gxw2dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxw2ftg", indent + 1, &(val[i].wg_gxw2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxw2rs", indent + 1, &(val[i].wg_gxw2rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxwas", indent + 1, &(val[i].wg_gxwas), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxwdtg", indent + 1, &(val[i].wg_gxwdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxwex", indent + 1, &(val[i].wg_gxwex), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxwmon", indent + 1, &(val[i].wg_gxwmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxwmps1", indent + 1, &(val[i].wg_gxwmps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gxwrs", indent + 1, &(val[i].wg_gxwrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gy1", indent + 1, &(val[i].wg_gy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gy1as", indent + 1, &(val[i].wg_gy1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gy1cfh", indent + 1, &(val[i].wg_gy1cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gy1dtg", indent + 1, &(val[i].wg_gy1dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gy1mon", indent + 1, &(val[i].wg_gy1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gy1mps1", indent + 1, &(val[i].wg_gy1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gy1r", indent + 1, &(val[i].wg_gy1r), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gy1ras", indent + 1, &(val[i].wg_gy1ras), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gy1rdtg", indent + 1, &(val[i].wg_gy1rdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gy1rrs", indent + 1, &(val[i].wg_gy1rrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gy1rs", indent + 1, &(val[i].wg_gy1rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gy1tm", indent + 1, &(val[i].wg_gy1tm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gy2dtg", indent + 1, &(val[i].wg_gy2dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gy2rs", indent + 1, &(val[i].wg_gy2rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyb", indent + 1, &(val[i].wg_gyb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gybrsfc1", indent + 1, &(val[i].wg_gybrsfc1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gybrsfc2", indent + 1, &(val[i].wg_gybrsfc2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gycylr", indent + 1, &(val[i].wg_gycylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gycylra", indent + 1, &(val[i].wg_gycylra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gycylratipup", indent + 1, &(val[i].wg_gycylratipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gycylrtipup", indent + 1, &(val[i].wg_gycylrtipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyfe1", indent + 1, &(val[i].wg_gyfe1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyfe2", indent + 1, &(val[i].wg_gyfe2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyflpk", indent + 1, &(val[i].wg_gyflpk), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyflpvenc", indent + 1, &(val[i].wg_gyflpvenc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyhyst1", indent + 1, &(val[i].wg_gyhyst1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyhyst2", indent + 1, &(val[i].wg_gyhyst2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gykcfh", indent + 1, &(val[i].wg_gykcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gykcfl", indent + 1, &(val[i].wg_gykcfl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gykcs", indent + 1, &(val[i].wg_gykcs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gykfs", indent + 1, &(val[i].wg_gykfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gykill", indent + 1, &(val[i].wg_gykill), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gykrcvn", indent + 1, &(val[i].wg_gykrcvn), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gykse1", indent + 1, &(val[i].wg_gykse1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gykse2", indent + 1, &(val[i].wg_gykse2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gykse3", indent + 1, &(val[i].wg_gykse3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gykse4", indent + 1, &(val[i].wg_gykse4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gykse5", indent + 1, &(val[i].wg_gykse5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gykse6", indent + 1, &(val[i].wg_gykse6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyksp", indent + 1, &(val[i].wg_gyksp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gykssf", indent + 1, &(val[i].wg_gykssf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyksx1", indent + 1, &(val[i].wg_gyksx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyksx2", indent + 1, &(val[i].wg_gyksx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyksy1", indent + 1, &(val[i].wg_gyksy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyksy2", indent + 1, &(val[i].wg_gyksy2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyksz1", indent + 1, &(val[i].wg_gyksz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyksz2", indent + 1, &(val[i].wg_gyksz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gykxtgl", indent + 1, &(val[i].wg_gykxtgl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gykxtgr", indent + 1, &(val[i].wg_gykxtgr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyrf0kcfh", indent + 1, &(val[i].wg_gyrf0kcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyrf1mon", indent + 1, &(val[i].wg_gyrf1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyrf1mps1", indent + 1, &(val[i].wg_gyrf1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyrf1tm", indent + 1, &(val[i].wg_gyrf1tm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyrf1xtg", indent + 1, &(val[i].wg_gyrf1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyrf2cfh", indent + 1, &(val[i].wg_gyrf2cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyrf2lmon", indent + 1, &(val[i].wg_gyrf2lmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyrf2rmon", indent + 1, &(val[i].wg_gyrf2rmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyrf3cfh", indent + 1, &(val[i].wg_gyrf3cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyspoil", indent + 1, &(val[i].wg_gyspoil), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gyspoil2", indent + 1, &(val[i].wg_gyspoil2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gz1", indent + 1, &(val[i].wg_gz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gz1as", indent + 1, &(val[i].wg_gz1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gz1cfl", indent + 1, &(val[i].wg_gz1cfl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gz1dtg", indent + 1, &(val[i].wg_gz1dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gz1ftg", indent + 1, &(val[i].wg_gz1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gz1mon", indent + 1, &(val[i].wg_gz1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gz1mps1", indent + 1, &(val[i].wg_gz1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gz1rs", indent + 1, &(val[i].wg_gz1rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gz1s", indent + 1, &(val[i].wg_gz1s), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gz1xtg", indent + 1, &(val[i].wg_gz1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gz2bftg", indent + 1, &(val[i].wg_gz2bftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gz2ftg", indent + 1, &(val[i].wg_gz2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gz2xtg", indent + 1, &(val[i].wg_gz2xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gz3ftg", indent + 1, &(val[i].wg_gz3ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzbrsfc1", indent + 1, &(val[i].wg_gzbrsfc1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzbrsfc1echo1", indent + 1, &(val[i].wg_gzbrsfc1echo1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzbrsfc1echo2", indent + 1, &(val[i].wg_gzbrsfc1echo2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzbrsfc2", indent + 1, &(val[i].wg_gzbrsfc2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzcomb", indent + 1, &(val[i].wg_gzcomb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzcombhtr", indent + 1, &(val[i].wg_gzcombhtr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzcylr", indent + 1, &(val[i].wg_gzcylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzcylra", indent + 1, &(val[i].wg_gzcylra), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzcylratipup", indent + 1, &(val[i].wg_gzcylratipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzcylrtipup", indent + 1, &(val[i].wg_gzcylrtipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzflpk", indent + 1, &(val[i].wg_gzflpk), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzflpvenc", indent + 1, &(val[i].wg_gzflpvenc), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzk", indent + 1, &(val[i].wg_gzk), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzkas", indent + 1, &(val[i].wg_gzkas), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzkbsdtg", indent + 1, &(val[i].wg_gzkbsdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzkbsrs", indent + 1, &(val[i].wg_gzkbsrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzkcs", indent + 1, &(val[i].wg_gzkcs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzkdtg", indent + 1, &(val[i].wg_gzkdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzkfs", indent + 1, &(val[i].wg_gzkfs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzkgir01", indent + 1, &(val[i].wg_gzkgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzkgir02", indent + 1, &(val[i].wg_gzkgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzkill", indent + 1, &(val[i].wg_gzkill), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzkiller", indent + 1, &(val[i].wg_gzkiller), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzkmon", indent + 1, &(val[i].wg_gzkmon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzkmontipup", indent + 1, &(val[i].wg_gzkmontipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzkrcvn", indent + 1, &(val[i].wg_gzkrcvn), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzkrffrir", indent + 1, &(val[i].wg_gzkrffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzkrs", indent + 1, &(val[i].wg_gzkrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzks", indent + 1, &(val[i].wg_gzks), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzks5fp", indent + 1, &(val[i].wg_gzks5fp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzksp", indent + 1, &(val[i].wg_gzksp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzkssf", indent + 1, &(val[i].wg_gzkssf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzp", indent + 1, &(val[i].wg_gzp), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzphtr", indent + 1, &(val[i].wg_gzphtr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzptm", indent + 1, &(val[i].wg_gzptm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrf0k", indent + 1, &(val[i].wg_gzrf0k), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrf1", indent + 1, &(val[i].wg_gzrf1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrf1dtg", indent + 1, &(val[i].wg_gzrf1dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrf1htr", indent + 1, &(val[i].wg_gzrf1htr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrf1mps1", indent + 1, &(val[i].wg_gzrf1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrf1rs", indent + 1, &(val[i].wg_gzrf1rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrf1s", indent + 1, &(val[i].wg_gzrf1s), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrf1xtg", indent + 1, &(val[i].wg_gzrf1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrf2lcfh", indent + 1, &(val[i].wg_gzrf2lcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrf2lmps1", indent + 1, &(val[i].wg_gzrf2lmps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrf2rcfh", indent + 1, &(val[i].wg_gzrf2rcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrf2rmps1", indent + 1, &(val[i].wg_gzrf2rmps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrf3lcfh", indent + 1, &(val[i].wg_gzrf3lcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrf3rcfh", indent + 1, &(val[i].wg_gzrf3rcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrf4cfh", indent + 1, &(val[i].wg_gzrf4cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrf4lcfh", indent + 1, &(val[i].wg_gzrf4lcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrf4rcfh", indent + 1, &(val[i].wg_gzrf4rcfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrfs5fph", indent + 1, &(val[i].wg_gzrfs5fph), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzrfssfh", indent + 1, &(val[i].wg_gzrfssfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzs5fphcomb", indent + 1, &(val[i].wg_gzs5fphcomb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_gzssfhcomb", indent + 1, &(val[i].wg_gzssfhcomb), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_hard180", indent + 1, &(val[i].wg_hard180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi7", indent + 1, &(val[i].wg_isi7), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_cardiacsat", indent + 1, &(val[i].wg_isi_cardiacsat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_gir1", indent + 1, &(val[i].wg_isi_gir1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_gire01", indent + 1, &(val[i].wg_isi_gire01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_gire02", indent + 1, &(val[i].wg_isi_gire02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_girk01", indent + 1, &(val[i].wg_isi_girk01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_girk02", indent + 1, &(val[i].wg_isi_girk02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_sate1", indent + 1, &(val[i].wg_isi_sate1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_sate2", indent + 1, &(val[i].wg_isi_sate2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_sate3", indent + 1, &(val[i].wg_isi_sate3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_sate4", indent + 1, &(val[i].wg_isi_sate4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_sate5", indent + 1, &(val[i].wg_isi_sate5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_sate6", indent + 1, &(val[i].wg_isi_sate6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_satek1", indent + 1, &(val[i].wg_isi_satek1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_satek2", indent + 1, &(val[i].wg_isi_satek2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_satek3", indent + 1, &(val[i].wg_isi_satek3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_satek4", indent + 1, &(val[i].wg_isi_satek4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_satek5", indent + 1, &(val[i].wg_isi_satek5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_satek6", indent + 1, &(val[i].wg_isi_satek6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_satx1", indent + 1, &(val[i].wg_isi_satx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_satx2", indent + 1, &(val[i].wg_isi_satx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_satxk1", indent + 1, &(val[i].wg_isi_satxk1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_satxk2", indent + 1, &(val[i].wg_isi_satxk2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_saty1", indent + 1, &(val[i].wg_isi_saty1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_saty2", indent + 1, &(val[i].wg_isi_saty2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_satyk1", indent + 1, &(val[i].wg_isi_satyk1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_satyk2", indent + 1, &(val[i].wg_isi_satyk2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_satz1", indent + 1, &(val[i].wg_isi_satz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_satz2", indent + 1, &(val[i].wg_isi_satz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_satzk1", indent + 1, &(val[i].wg_isi_satzk1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_satzk2", indent + 1, &(val[i].wg_isi_satzk2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_slice1", indent + 1, &(val[i].wg_isi_slice1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_isi_slice2", indent + 1, &(val[i].wg_isi_slice2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_maps1", indent + 1, &(val[i].wg_maps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_maps2", indent + 1, &(val[i].wg_maps2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_mapx", indent + 1, &(val[i].wg_mapx), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_mapy", indent + 1, &(val[i].wg_mapy), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_mapz", indent + 1, &(val[i].wg_mapz), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_mpomega_td0", indent + 1, &(val[i].wg_mpomega_td0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_mprho_td0", indent + 1, &(val[i].wg_mprho_td0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_mpssp_td0", indent + 1, &(val[i].wg_mpssp_td0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_mptheta_td0", indent + 1, &(val[i].wg_mptheta_td0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_mpx_td0", indent + 1, &(val[i].wg_mpx_td0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_mpy_td0", indent + 1, &(val[i].wg_mpy_td0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_mpz_td0", indent + 1, &(val[i].wg_mpz_td0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_omega_hs_rfcssat", indent + 1, &(val[i].wg_omega_hs_rfcssat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_omega_ir0", indent + 1, &(val[i].wg_omega_ir0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_omega_rffrir", indent + 1, &(val[i].wg_omega_rffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_omega_rfgir01", indent + 1, &(val[i].wg_omega_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_omega_rfgir02", indent + 1, &(val[i].wg_omega_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_omegarf0cfh", indent + 1, &(val[i].wg_omegarf0cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_postgxw1ftg", indent + 1, &(val[i].wg_postgxw1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rcvn_wait", indent + 1, &(val[i].wg_rcvn_wait), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf0", indent + 1, &(val[i].wg_rf0), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf0cfh", indent + 1, &(val[i].wg_rf0cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf1", indent + 1, &(val[i].wg_rf1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf180", indent + 1, &(val[i].wg_rf180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf1as", indent + 1, &(val[i].wg_rf1as), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf1cfh", indent + 1, &(val[i].wg_rf1cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf1cfl", indent + 1, &(val[i].wg_rf1cfl), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf1dtg", indent + 1, &(val[i].wg_rf1dtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf1ftg", indent + 1, &(val[i].wg_rf1ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf1htr", indent + 1, &(val[i].wg_rf1htr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf1mon", indent + 1, &(val[i].wg_rf1mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf1mps1", indent + 1, &(val[i].wg_rf1mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf1rs", indent + 1, &(val[i].wg_rf1rs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf1tm", indent + 1, &(val[i].wg_rf1tm), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf1xtg", indent + 1, &(val[i].wg_rf1xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf2cfh", indent + 1, &(val[i].wg_rf2cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf2ftg", indent + 1, &(val[i].wg_rf2ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf2mon", indent + 1, &(val[i].wg_rf2mon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf2mps1", indent + 1, &(val[i].wg_rf2mps1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf2xtg", indent + 1, &(val[i].wg_rf2xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf3cfh", indent + 1, &(val[i].wg_rf3cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf3ftg", indent + 1, &(val[i].wg_rf3ftg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf3xtg", indent + 1, &(val[i].wg_rf3xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf4cfh", indent + 1, &(val[i].wg_rf4cfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf4xtg", indent + 1, &(val[i].wg_rf4xtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rf90", indent + 1, &(val[i].wg_rf90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfbdtg", indent + 1, &(val[i].wg_rfbdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfbrs", indent + 1, &(val[i].wg_rfbrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfcssat", indent + 1, &(val[i].wg_rfcssat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfcylr", indent + 1, &(val[i].wg_rfcylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfcylrtipup", indent + 1, &(val[i].wg_rfcylrtipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfflp180", indent + 1, &(val[i].wg_rfflp180), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfflp180_the", indent + 1, &(val[i].wg_rfflp180_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfflp90", indent + 1, &(val[i].wg_rfflp90), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfflp90_the", indent + 1, &(val[i].wg_rfflp90_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfflp90r", indent + 1, &(val[i].wg_rfflp90r), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfflp90r_the", indent + 1, &(val[i].wg_rfflp90r_the), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rffrir", indent + 1, &(val[i].wg_rffrir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rffs", indent + 1, &(val[i].wg_rffs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfgir01", indent + 1, &(val[i].wg_rfgir01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfgir02", indent + 1, &(val[i].wg_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfmontipup", indent + 1, &(val[i].wg_rfmontipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfs5fph", indent + 1, &(val[i].wg_rfs5fph), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfse1", indent + 1, &(val[i].wg_rfse1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfse2", indent + 1, &(val[i].wg_rfse2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfse3", indent + 1, &(val[i].wg_rfse3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfse4", indent + 1, &(val[i].wg_rfse4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfse5", indent + 1, &(val[i].wg_rfse5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfse6", indent + 1, &(val[i].wg_rfse6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfssf", indent + 1, &(val[i].wg_rfssf), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfssfh", indent + 1, &(val[i].wg_rfssfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfsx1", indent + 1, &(val[i].wg_rfsx1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfsx2", indent + 1, &(val[i].wg_rfsx2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfsy1", indent + 1, &(val[i].wg_rfsy1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfsy2", indent + 1, &(val[i].wg_rfsy2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfsz1", indent + 1, &(val[i].wg_rfsz1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rfsz2", indent + 1, &(val[i].wg_rfsz2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rftipup", indent + 1, &(val[i].wg_rftipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_slice1", indent + 1, &(val[i].wg_rot_slice1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_slice2", indent + 1, &(val[i].wg_rot_slice2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_cardiacsat", indent + 1, &(val[i].wg_rot_update_cardiacsat), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_e1", indent + 1, &(val[i].wg_rot_update_e1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_e2", indent + 1, &(val[i].wg_rot_update_e2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_e3", indent + 1, &(val[i].wg_rot_update_e3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_e4", indent + 1, &(val[i].wg_rot_update_e4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_e5", indent + 1, &(val[i].wg_rot_update_e5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_e6", indent + 1, &(val[i].wg_rot_update_e6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_ek1", indent + 1, &(val[i].wg_rot_update_ek1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_ek2", indent + 1, &(val[i].wg_rot_update_ek2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_ek3", indent + 1, &(val[i].wg_rot_update_ek3), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_ek4", indent + 1, &(val[i].wg_rot_update_ek4), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_ek5", indent + 1, &(val[i].wg_rot_update_ek5), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_ek6", indent + 1, &(val[i].wg_rot_update_ek6), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_gir", indent + 1, &(val[i].wg_rot_update_gir), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_gire01", indent + 1, &(val[i].wg_rot_update_gire01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_girk01", indent + 1, &(val[i].wg_rot_update_girk01), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_girk02", indent + 1, &(val[i].wg_rot_update_girk02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_rfgir02", indent + 1, &(val[i].wg_rot_update_rfgir02), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_x1", indent + 1, &(val[i].wg_rot_update_x1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_x2", indent + 1, &(val[i].wg_rot_update_x2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_xk1", indent + 1, &(val[i].wg_rot_update_xk1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_xk2", indent + 1, &(val[i].wg_rot_update_xk2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_y1", indent + 1, &(val[i].wg_rot_update_y1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_y2", indent + 1, &(val[i].wg_rot_update_y2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_yk1", indent + 1, &(val[i].wg_rot_update_yk1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_yk2", indent + 1, &(val[i].wg_rot_update_yk2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_z1", indent + 1, &(val[i].wg_rot_update_z1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_z2", indent + 1, &(val[i].wg_rot_update_z2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_zk1", indent + 1, &(val[i].wg_rot_update_zk1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rot_update_zk2", indent + 1, &(val[i].wg_rot_update_zk2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_rticfh", indent + 1, &(val[i].wg_rticfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_sdixon", indent + 1, &(val[i].wg_sdixon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_sdixon2", indent + 1, &(val[i].wg_sdixon2), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_sticfh", indent + 1, &(val[i].wg_sticfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_thcylr", indent + 1, &(val[i].wg_thcylr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_thcylrtipup", indent + 1, &(val[i].wg_thcylrtipup), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_thetarfbdtg", indent + 1, &(val[i].wg_thetarfbdtg), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_thetarfbrs", indent + 1, &(val[i].wg_thetarfbrs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_xdelay", indent + 1, &(val[i].wg_xdelay), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_xdixon", indent + 1, &(val[i].wg_xdixon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_xrespgate", indent + 1, &(val[i].wg_xrespgate), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_xticfh", indent + 1, &(val[i].wg_xticfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_y_ccs_null", indent + 1, &(val[i].wg_y_ccs_null), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_ydixon", indent + 1, &(val[i].wg_ydixon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_yticfh", indent + 1, &(val[i].wg_yticfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_zdixon", indent + 1, &(val[i].wg_zdixon), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "wg_zticfh", indent + 1, &(val[i].wg_zticfh), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "whichss", indent + 1, &(val[i].whichss), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "write_spinfo", indent + 1, &(val[i].write_spinfo), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xa2s", indent + 1, &(val[i].xa2s), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xfd_power_limit", indent + 1, &(val[i].xfd_power_limit), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xfd_temp_limit", indent + 1, &(val[i].xfd_temp_limit), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xgd_optimization", indent + 1, &(val[i].xgd_optimization), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xkiller_set", indent + 1, &(val[i].xkiller_set), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xlFOV_flag", indent + 1, &(val[i].xlFOV_flag), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xmtadd", indent + 1, &(val[i].xmtadd), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xmtaddAPS1", indent + 1, &(val[i].xmtaddAPS1), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xmtaddCFH", indent + 1, &(val[i].xmtaddCFH), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xmtaddCFL", indent + 1, &(val[i].xmtaddCFL), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xmtaddFTG", indent + 1, &(val[i].xmtaddFTG), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xmtaddRCVN", indent + 1, &(val[i].xmtaddRCVN), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xmtaddRef", indent + 1, &(val[i].xmtaddRef), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xmtaddScan", indent + 1, &(val[i].xmtaddScan), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xmtaddXTG", indent + 1, &(val[i].xmtaddXTG), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xmtaddas", indent + 1, &(val[i].xmtaddas), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xmtadddtg", indent + 1, &(val[i].xmtadddtg), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xmtaddrs", indent + 1, &(val[i].xmtaddrs), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xmtlogas", indent + 1, &(val[i].xmtlogas), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xres", indent + 1, &(val[i].xres), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xres2use", indent + 1, &(val[i].xres2use), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xres_ann_off", indent + 1, &(val[i].xres_ann_off), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xres_ann_on", indent + 1, &(val[i].xres_ann_on), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xtg_dda", indent + 1, &(val[i].xtg_dda), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xtg_disabled", indent + 1, &(val[i].xtg_disabled), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xtg_offres_freq", indent + 1, &(val[i].xtg_offres_freq), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xtg_volRecCoil", indent + 1, &(val[i].xtg_volRecCoil), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "xtgscale", indent + 1, &(val[i].xtgscale), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xtgtr", indent + 1, &(val[i].xtgtr), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "xtr_offset", indent + 1, &(val[i].xtr_offset), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "ya2s", indent + 1, &(val[i].ya2s), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "yfe_time", indent + 1, &(val[i].yfe_time), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "yfov_aspect", indent + 1, &(val[i].yfov_aspect), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "yoffs1", indent + 1, &(val[i].yoffs1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "yres_phase", indent + 1, &(val[i].yres_phase), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "za2s", indent + 1, &(val[i].za2s), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zchop", indent + 1, &(val[i].zchop), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zgmn_type", indent + 1, &(val[i].zgmn_type), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zkiller_flag", indent + 1, &(val[i].zkiller_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zoffs", indent + 1, &(val[i].zoffs), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zoffs1", indent + 1, &(val[i].zoffs1), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zrewind_flag", indent + 1, &(val[i].zrewind_flag), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zsign", indent + 1, &(val[i].zsign), 1);
#endif
#ifdef SIZEOF_float
    print_brsfc_float(fp, "zslab", indent + 1, &(val[i].zslab), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zy_export_debug_files", indent + 1, &(val[i].zy_export_debug_files), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zy_slices", indent + 1, &(val[i].zy_slices), 1);
#endif
#ifdef SIZEOF_int
    print_brsfc_int(fp, "zy_views", indent + 1, &(val[i].zy_views), 1);
#endif
  }
}


#ifndef _PRESCAN_PARAMS_H_
#define _PRESCAN_PARAMS_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define PSC_STRINGIZE(y) #y
#define PSC_FPRINTSTR(fp, a, fmt) fprintf((fp), PSC_STRINGIZE(a = fmt\n), (a))
#  define PSC_FPRINTARRSTR(fp, a, fmt, num) \
     do {                             \
       int __i;                      \
       for (__i=0; __i<num;__i++) {  \
         fprintf((fp), PSC_STRINGIZE(a[%d] = fmt\n), (__i), (a[(__i)])); \
       }                              \
     } while(0)
#  define PSC_FPRINTMATSTR(fp, a, fmt, rows, cols) \
     do {                                      \
       int __i, __j;                           \
       for (__i=0; __i<rows;__i++) {           \
         fprintf((fp), PSC_STRINGIZE(a[%d][] = ),  \
                 (__i));                       \
           for (__j=0; __j<cols;__j++) {       \
             fprintf((fp), PSC_STRINGIZE(fmt),     \
                      (a[(__i)][__j]));        \
             fprintf((fp), " ");               \
           }                                   \
           fprintf((fp), "\n");                \
       }                                       \
     } while(0)


#define psc_print_i(fp, a) PSC_FPRINTSTR(fp,a,%d)
#define psc_print_u(fp, a) PSC_FPRINTSTR(fp,a,%u)
#define psc_print_f(fp, a) PSC_FPRINTSTR(fp,a,%f)
#define psc_print_X(fp, a) PSC_FPRINTSTR(fp,a,%X)
#define psc_print_s(fp, a) PSC_FPRINTSTR(fp,a,%s)
#define psc_print_c(fp, a) PSC_FPRINTSTR(fp,a,%c)
#define psc_print_l(fp, a) PSC_FPRINTSTR(fp,a,%ld)

#define psc_print_arri(fp, a, n) PSC_FPRINTARRSTR(fp,a,%d,n)
#define psc_print_arru(fp, a, n) PSC_FPRINTARRSTR(fp,a,%u,n)
#define psc_print_arrf(fp, a, n) PSC_FPRINTARRSTR(fp,a,%f,n)
#define psc_print_arrX(fp, a, n) PSC_FPRINTARRSTR(fp,a,%X,n)
#define psc_print_arrs(fp, a, n) PSC_FPRINTARRSTR(fp,a,%s,n)
#define psc_print_arrc(fp, a, n) PSC_FPRINTARRSTR(fp,a,%c,n)
#define psc_print_arrl(fp, a, n) PSC_FPRINTARRSTR(fp,a,%ld,n)

int get_exam_number(void);
int check_rhosts_file(void);
int save_prescan_params(int exno, int protno);
int load_prescan_params(int exno, int protno);
int psc_store_protocol(char *protocolfile, int exno);
int psc_find_protocol(char *protocolfile, int exno);
FILE * psc_open_params_img(void);

#ifdef PSD_HW
#define PSC_PROTOCOL "/tmp/psc_protocol.txt"
#define ARCHIVEDIR "/usr/g/mrraw/bo/archive"
#define ATPDIR ARCHIVEDIR "/atp"
#define ATPCMD ATPDIR "/rcmd/atp_rcmd"
#else
#define PSC_PROTOCOL "psc_protocol.txt"
#define ARCHIVEDIR "archive"
#define ATPDIR ""
#define ATPCMD ATPDIR "atp_rcmd"
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

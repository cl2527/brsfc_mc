#!/bin/bash
export ESETOP=${TOPDIR}
ESEMAJOR="$(../esever.sh --major)"
if [ "${ESEMAJOR}" -ge 27 ]
then
  IMAKEFILE=Imakefile.common
else
  IMAKEFILE=Imakefile
fi

PSD=`awk '/PSD = /{print $3}' ${IMAKEFILE}`
funcname=fprint_psc_protocol
print_psc_c=${funcname}.c
print_psc_h=${funcname}.h
psc_protocol=psc_protocol.def

psd=`awk '/PSD =/{print $3}' ${IMAKEFILE}`

echo Generating ${print_psc_c}
echo Generating ${print_psc_h}

cat > ${print_psc_h} << EOS
#ifndef _`basename ${print_psc_h} .h`_h_
#define _`basename ${print_psc_h} .h`_h_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
int ${funcname}(char *file);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
EOS

cat > ${print_psc_c} << EOS
#include <stdio.h>
#include <${psd}_cv.h>
#include <${psd}_cv_printer.h>
#include "${print_psc_h}"
EOS

awk '/[a-zA-Z]/{if(NF==3) {var=$1" "$2; SUF="[];";} else {var=$0; SUF=";";}\
                print "extern " var SUF}' psc_protocol.def >> ${print_psc_c}

cat >> ${print_psc_c} << EOS
int ${funcname}(char *file)
{
  FILE *fp = NULL;
  extern int print_${psd}_num_significant_digits;
  
  print_${psd}_num_significant_digits = 6;

  if (NULL == (fp = fopen(file, "w"))) return -1; 
EOS

awk -v psd=${PSD} '/[a-zA-Z]/{if(NF==3) {num=$3; P="(";} else {num=1; P="&(";} \
                print "  print_" psd "_" $1 "(fp, \"" $2 "\", 0, " P $2 ")," num ");" }' psc_protocol.def >> ${print_psc_c}
if [ "${ESEMAJOR}" -ge 27 ]
then
  sed -i '/psd_name/d' ${print_psc_c}
fi


cat >> ${print_psc_c} << EOS
  fclose(fp);
  print_${psd}_num_significant_digits = 0;
  return 0;
}
EOS


#!/bin/bash
if [ "${ESETOP}" == "" ]
then
  exit 1
fi  

if [ "${ESETOP}" == "/ESE_RX28.0_R05" ]
then
  ESEMAJOR=28
  ESEMINOR=5
  ESETYPE=RX
elif [ "${ESETOP}" == "/ESE_MR29.0_R01" ]
then
  ESEMAJOR=29
  ESEMINOR=4
  ESETYPE=MR
elif [ "${ESETOP}" == "/ESE_DV28.0_R01" ]
then
  ESEMAJOR=28
  ESEMINOR=1
  ESETYPE=M
elif [ "${ESETOP}" == "/ESE_MR28.0_R03" ]
then
  ESEMAJOR=28
  ESEMINOR=3
  ESETYPE=MR
elif [ "${ESETOP}" == "/ESE_RX27.0_R03" ]
then
  ESEMAJOR=27
  ESEMINOR=3
  ESETYPE=RX
elif [ "${ESETOP}" == "/ESE_MP26.0_R01" ]
then
  ESEMAJOR=26
  ESEMINOR=4
  ESETYPE=MP
elif [ "${ESETOP}" == "/ESE_MP26.0_R02" ]
then
  ESEMAJOR=26
  ESEMINOR=5
  ESETYPE=MP
elif [ "${ESETOP}" == "/ESE_DV26.0_R02" ]
then
  ESEMAJOR=26
  ESEMINOR=5
  ESETYPE=M
elif [ "${ESETOP}" == "/ESE_RX27.0_EB" ]
then
  ESEMAJOR=27
  ESEMINOR=1
  ESETYPE=RX
elif [ "${ESETOP}" == "/ESE_DV26.0_EB" ]
then
  ESEMAJOR=26
  ESEMINOR=3
  ESETYPE=M
elif [ "${ESETOP}" == "/ESE_MP26.0_EA" ]
then
  ESEMAJOR=26
  ESEMINOR=1
  ESETYPE=MP
elif [ "${ESETOP}" == "/ESE_DV26.0_R01" ]
then
  ESEMAJOR=26
  ESEMINOR=4
	ESETYPE=M
elif [ "${ESETOP}" == "/ESE_DV25.1_R02" ]
then
  ESEMAJOR=25
  ESEMINOR=6
	ESETYPE=M
elif [ "${ESETOP}" == "/ESE_DV25.0_R02" ]
then
  ESEMAJOR=25
  ESEMINOR=5
	ESETYPE=M
elif [ "${ESETOP}" == "/ESE_DV25.0_R01" ]
then
  ESEMAJOR=25
  ESEMINOR=4
	ESETYPE=M
elif [ "${ESETOP}" == "/ESE_DV24.0_R02" ]
then
  ESEMAJOR=24
  ESEMINOR=5
	ESETYPE=M
elif [ "${ESETOP}" == "/ESE_DV24.0_V01" ]
then
  ESEMAJOR=24
  ESEMINOR=4
	ESETYPE=M
elif [ "${ESETOP}" == "/ESE_DV23_1_V02" ]
then
	ESEMAJOR=23
	ESEMINOR=4
	ESETYPE=M
elif [ "${ESETOP}" == "/ESE_DV22_VO2" ]
then
	ESEMAJOR=22
	ESEMINOR=4
	ESETYPE=M
elif [ "${ESETOP}" == "/ESE_HD23_V02" ]
then
	ESEMAJOR=23
	ESEMINOR=4
	ESETYPE=HD
elif [ "${ESETOP}" == "/ESE_HD23_R03" ]
then
	ESEMAJOR=23
	ESEMINOR=5
	ESETYPE=HD
fi

if [ "${1}" == "" ]
then
  echo ${ESEMAJOR}${ESETYPE}${ESEMINOR}
elif [ "${1}" == "--major" ]
then
  echo ${ESEMAJOR}
elif [ "${1}" == "--minor" ]
then
  echo ${ESEMINOR}
elif [ "${1}" == "--type" ]
then
  echo ${ESETYPE}
fi


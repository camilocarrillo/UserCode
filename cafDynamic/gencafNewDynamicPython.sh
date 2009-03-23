#!/bin/bash
echo Config file $1
if [ -f "$1" ]
then
   file_name=$1
else
echo "File \"$1\" does not exist."
exit 0
fi
export padRUN=`awk 'NR==1' $1`
export storePAD=`awk 'NR==2' $1`
export q=`awk 'NR==3' $1`
export max=`awk 'NR==4' $1`
export cfgtemplate=`awk 'NR==5' $1`
export key=`awk 'NR==6' $1`

export padCURR=`pwd`
echo $padROOTsed
echo $storePAD
echo $max
echo $cfgtemplate

#rm *.cfg
#rm *.lsf
#rm *.root.*
rm corraBatch
touch corraBatch
i=1;
echo Here we go
for line in `head -n $max files`
	do
	export rootfile=`echo $line | awk -F"/" '{print $NF}'`
	export padROOT=`echo $line | sed -e "s|$rootfile||g"`
	echo $line
	echo $padROOT
	echo $rootfile
	sed -e "s|-filename-|$rootfile|g" -e "s|-pad-|$padROOT|g" $cfgtemplate > $rootfile._cfg.py
	sed -e "s|-filename-|$rootfile|g" -e "s|-pad-|$padROOT|g" -e "s|-padtorun-|$padRUN|g" -e "s|-currentpad-|$padCURR|g" -e "s|-storepad-|$storePAD|g" -e "s|-key-|$key|g" ~carrillo/public/for_All/cafDynamic/jobtemplateDynamicPython > $rootfile.lsf
	echo "bsub -q $q -e $rootfile.err -o $rootfile.olsf -J $rootfile $rootfile.lsf" 1>> corraBatch
	let "i=$i+1"
	done
chmod a+x *.lsf
wc -l corraBatch
rfmkdir $storePAD
exit 0

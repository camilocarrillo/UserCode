#!/bin/bash
echo Config file $1
if [ -f "$1" ]
then
   file_name=$1
else
echo "File \"$1\" does not exist."
exit 0
fi

export N=`awk 'NR==1' $1`
export h=`awk 'NR==2' $1`
export padROOT=`awk 'NR==3' $1`
export padSTORE=`awk 'NR==4' $1`
export basename=`awk 'NR==5' $1`
export padtoRUN=`awk 'NR==6' $1`
export Nfiles=`awk 'NR==7' $1`

export currentPAD=`pwd`

rm runBatch
touch runBatch

rm *.cfg
rm *.job
rm *.root.*
i=100;
limit=$[$Nfiles+100]
j=0;
while [ $i -lt $limit ]
	do
	rootfilename=$basename.$i.root
	e=$(echo "scale=2; $j/100.0" | bc)
	echo $e
	sed -e "s|-N-|$N|g" -e "s|-firstrun-|$i|g" -e "s|-eff-|$e|g" -e "s|-rootfilename-|$rootfilename|g" cfgtemplate  > $rootfilename.cfg
	sed -e "s|-padtoRUN-|$padtoRUN|g" -e "s|-rootfilename-|$rootfilename|g" -e "s|-padROOT-|$padROOT|g" -e "s|-padSTORE-|$padSTORE|g" -e "s|-currentPAD-|$currentPAD|g" jobtemplate  > $rootfilename.job
	echo "b"$h" $rootfilename" 1>> runBatch
	i=$[$i+1]
	j=$[$j+1]
	echo $rootfilename
	done

chmod a+x *.job
exit 0

#!/bin/bash
echo Config file $1
if [ -f "$1" ]
then
   file_name=$1
else
echo "File \"$1\" does not exist."
exit 0
fi
export padCASTOR=`awk 'NR==1' $1`
export padtorun=`awk 'NR==2' $1`
export step=`awk 'NR==3' $1`
export q=`awk 'NR==4' $1`
export key=`awk 'NR==5' $1`

export currentpad=`pwd`
export numfiles=`nsls $padCASTOR | grep $key | wc -l`

if [[ $step -eq "-1" ]]
then
 step=$(echo "sqrt($numfiles)" | bc)
 echo Step setted with square root step=$step
fi



ini=1;
fin=1;
rm jobLocal*.lsf
rm corraBatchLocal
rm listoffiles*
rm jobLocal*.olsf
rm jobLocal*.err
rm Local*.root
touch corraBatchLocal
while [ $fin -lt $numfiles ]
	do
	echo "desde" $ini
	let "fin=$ini+$step-1"
	echo "-----hasta" $fin
	sed -e "s|-key-|$key|g" -e "s|-ini-|$ini|g" -e "s|-fin-|$fin|g" -e "s|-padCASTOR-|$padCASTOR|g" -e "s|-step-|$step|g" -e "s|-padtorun-|$padtorun|g" -e "s|-currentpad-|$currentpad|g" ~carrillo/public/for_All/cafDynamic/mergingDynamic/jobtemplateLocalDynamic > jobLocal$ini-$fin.lsf
	echo "bsub -q $q -e jobLocal$ini-$fin.err -o jobLocal$ini-$fin.olsf -J jobLocal$ini-$fin jobLocal$ini-$fin.lsf" 1>> corraBatchLocal
	let "ini=$ini+$step"
	done
sed -e "s|-padCASTOR-|$padCASTOR|g" -e "s|-padtorun-|$padtorun|g" -e "s|-currentpad-|$currentpad|g" ~carrillo/public/for_All/cafDynamic/mergingDynamic/jobLocalFinalTemplate > jobLocalFinal.lsf
chmod a+x *.lsf
echo "Files in CASTOR"
echo "Number of files merged"
echo $fin
exit 0

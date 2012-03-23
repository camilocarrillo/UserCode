#!/bin/bash

i=1
export NumberOfRuns=`cat $1 | wc -l`
echo $NumberOfRuns

export project=`awk -F"=" '{print $2}' $2 | awk 'NR==4'`
export dataset=`awk -F"=" '{print $2}' $2 | awk 'NR==2'`

export numparameters=`cat $2 | wc -l`

if [[ $numparameters -ne 5 ]]
then
   echo "!!! The Number of parameters(lines) is $numparameters and should be 5, (manysimple RunsList DataSetAndReleaseInfo)"    
   exit 0
fi

echo cheking that all the runs are already registered in the dataset
/afs/cern.ch/user/c/carrillo/scripts/checkRunsInDataSet.sh $1 $dataset

while [[ $i -le $NumberOfRuns ]]
do
	export run=`awk 'NR=='$i' {print $1}' $1`
	export run=`echo $run`
	echo "run to analyze $run"
	sed -e "s|-run-|$run|g" $2 > hscp$run.txt
	echo "Calling Simple for run $run (see /tmp/carrillo/hscp$run.txt)"
	/afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/simplehscp.sh hscp$run.txt 1> /tmp/carrillo/hscp$run.txt
	echo "supperfast"
	let "i=$i+1"
done


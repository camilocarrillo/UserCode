#!/bin/bash

i=1
export NumberOfRuns=`cat $1 | wc -l`
echo $NumberOfRuns

export project=`awk -F"=" '{print $2}' $2 | awk 'NR==4'`
export dataset=`awk -F"=" '{print $2}' $2 | awk 'NR==2'`

while [[ $i -le $NumberOfRuns ]]
do
	export run=`awk 'NR=='$i' {print $1}' $1`
	export run=`echo $run`
	echo "Number of runs to analyze $run"
	sed -e "s|-run-|$run|g" $2 > eff$run.txt
	echo "Calling Simple"
	/afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/simple.sh eff$run.txt
	echo "Calling PrepRunAndSet.sh"
	echo "run = $run - dataset=$dataset - project = $project"
	/afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/html/PrepRunAndSet.sh $run $dataset $project
	let "i=$i+1"
done


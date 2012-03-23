#!/bin/bash

i=1
export NumberOfRuns=`cat $1 | wc -l`
echo $NumberOfRuns

export dataset=`awk -F"=" '{print $2}' $2 | awk 'NR==2'`
export queue=`awk -F"=" '{print $2}' $2 | awk 'NR==3'`
export project=`awk -F"=" '{print $2}' $2 | awk 'NR==4'`
export label=`awk -F"=" '{print $2}' $2 | awk 'NR==6'`

echo dataset = $dataset
echo queue = $queue
echo project = $project
echo label = $label


export releasecheck=`echo $LOCALRT | grep CMSSW | wc -l`

echo $releasecheck

if [[ $releasecheck -ne 1 ]]
then
   echo "!!! you have to cmsenv a valid CMSSW area in order to access dbs querys"    
   exit 0
fi



export numparameters=`cat $2 | wc -l`

if [[ $numparameters -ne 6 ]]
then
   echo "!!! The Number of parameters(lines) is $numparameters and should be 6, (manysimple RunsList _DataSetAndReleaseInfo)"    
   exit 0
fi

echo cheking that all the runs are already registered in the dataset
/afs/cern.ch/user/c/carrillo/scripts/checkRunsInDataSet.sh $1 $dataset

while [[ $i -le $NumberOfRuns ]]
do
	export run=`awk 'NR=='$i' {print $1}' $1`
	export run=`echo $run`
	echo "run to analyze $run"
	sed -e "s|-run-|$run|g" $2 > $label-$run.txt
	echo "Calling simpleSpecifyPathFAST for run $run (see /tmp/carrillo/$label-$run.txt)"
	/afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/simpleSpecifyPathFast.sh $label-$run.txt 1> /tmp/carrillo/$label-$run.txt &
	let "i=$i+1"
done

echo Sleeping 30
echo Waiting for queue to be readable
sleep 30

export numrun=`bjobs | grep RUN | grep $queue | wc -l`
export numpend=`bjobs | grep PEND | grep $queue | wc -l`

until [[ $numrun -eq 0 && $numpend -eq 0 ]]
        do  
        export numrun=`bjobs | grep RUN | grep $queue | wc -l`
        export numpend=`bjobs | grep PEND | grep $queue | wc -l`
        let "i=$i+1"
        let "t=i*10"
        echo t=$t s jobs: \| $label \| run=$numrun \| pend=$numpend \|
        sleep 10
        done

echo "all the merged runs are done, please run manysimpleSpecifyPathFAST_justHarvesting.sh"


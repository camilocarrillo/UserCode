#!/bin/bash

i=1
export NumberOfRuns=`cat $1 | wc -l`
echo $NumberOfRuns

export project=`awk -F"=" '{print $2}' $2 | awk 'NR==4'`
export dataset=`awk -F"=" '{print $2}' $2 | awk 'NR==2'`
export label=`awk -F"=" '{print $2}' $2 | awk 'NR==6'`

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
	echo "Calling simpleSpecifyPath for run $run (see /tmp/carrillo/$label-$run.txt)"
	/afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/simpleSpecifyPath.sh $label-$run.txt 1> /tmp/carrillo/$label-$run.txt
	echo "Calling PrepRunAndSet.sh"
	echo "run = $run - dataset=$dataset - project = $project - label = $label"
	/afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/html/PrepRunAndSetSpecifyPath.sh $run $dataset $project $label
	if [ -f "MainIndex.html" ]
	then
	   echo "MainIndex.html exist removing"
 	   rm MainIndex.html
 	fi
	export datasetpath=`echo $dataset | sed -e "s|/|_|g" `
	wget http://cmsrpc402b20.cern.ch/$label/$datasetpath/$run/MainIndex.html
	export sucess=`cat MainIndex.html | grep $run | wc -l`
	echo $sucess
	if [[ $sucess -eq 2 ]]
	then
	   echo "Ready to send the email!"
	   sed -e "s|-run-|$run|g" -e "s|-dataset-|$dataset|g" -e "s|-datasetpath-|$datasetpath|g" -e "s|-label-|$label|g" /afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/html/mailtemplatelabel.txt 1> /tmp/carrillo/text.txt
	   cat /tmp/carrillo/text.txt
	   mail -s "run $run" carrillo < /tmp/carrillo/text.txt
	   #mail -s "run $run" rpc-commissioning < /tmp/carrillo/text.txt
	   #mail -s "plots for run $run" cmsrpc-caf < /tmp/carrillo/text.txt
        else
 	   echo "!!!!!!!!!!!!!!!!!!!!! Problem with Main Index, or cmsrpc402b20 turned off or kerberos token expired, plase try again"
	fi
	let "i=$i+1"
done



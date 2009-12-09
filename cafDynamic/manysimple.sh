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
	echo "run to analyze $run"
	sed -e "s|-run-|$run|g" $2 > eff$run.txt
	echo "Calling Simple for run $run (see /tmp/carrillo/eff$run.txt)"
	/afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/simple.sh eff$run.txt 1> /tmp/carrillo/eff$run.txt
	echo "Calling PrepRunAndSet.sh"
	echo "run = $run - dataset=$dataset - project = $project"
	/afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/html/PrepRunAndSet.sh $run $dataset $project
	if [ -f "MainIndex.html" ]
	then
	   echo "MainIndex.html exist removing"
 	   rm MainIndex.html
 	fi
	export datasetpath=`echo $dataset | sed -e "s|/|_|g"`
	wget http://cmsrpc402b20.cern.ch/efficiency/$datasetpath/$run/MainIndex.html
	export sucess=`cat MainIndex.html | grep $run | wc -l`
	echo $sucess
	if [[ $sucess -eq 2 ]]
	then
	   echo "Ready to send the email!"
	   sed -e "s|-run-|$run|g" -e "s|-dataset-|$dataset|g" -e "s|-datasetpath-|$datasetpath|g" /afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/html/mailtemplate.txt 1> /tmp/carrillo/text.txt
	   cat /tmp/carrillo/text.txt
	   mail -s "run $run" carrillo < /tmp/carrillo/text.txt
	   #mail -s "run $run" rpc-commissioning < /tmp/carrillo/text.txt
	   #mail -s "plots for run $run" cmsrpc-caf < /tmp/carrillo/text.txt
        else
 	   echo "!!!!!!!!!!!!!!!!!!!!! Problem with Main Index, or cmsrpc402b20 turned off or kerberos token expired, plase try again"
	fi
	let "i=$i+1"
done


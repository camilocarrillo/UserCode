#!/bin/bash
echo Config file $1
if [ -f "$1" ]
then
   file_name=$1
else
echo "File \"$1\" with parameters does not exist."
exit 0
fi

export numparameters=`cat $1 | wc -l`

if [[ $numparameters -ne 5 ]]
then
   echo "!!! The Number of short parameters(lines) is $numparameters and  should be 5"
   exit 0
fi

export run=`awk -F"=" '{print $2}' $1 | awk 'NR==1'`
export dataset=`awk -F"=" '{print $2}' $1 | awk 'NR==2'`
export queue=`awk -F"=" '{print $2}' $1 | awk 'NR==3'`
export project=`awk -F"=" '{print $2}' $1 | awk 'NR==4'`
export cfgtemplate=`awk -F"=" '{print $2}' $1 | awk 'NR==5'`

echo "-----LIST OF PARAMETERS-----"
echo run = $run
echo dataset = $dataset
echo queue = $queue
echo project = $project
echo cfgtemplate = $cfgtemplate
echo "-----------------------------"

export home=`echo ~`
export casa=`pwd`
export castor=`echo $CASTOR_HOME`

rm $run.txt

echo $casa/$run > $run.txt
echo $castor/RPCSegmentEff/$run >> $run.txt
echo $dataset >> $run.txt
echo $run >> $run.txt
echo $queue >> $run.txt
echo "2000" >> $run.txt
echo -1 >> $run.txt
echo $project >> $run.txt
echo $cfgtemplate >> $run.txt
echo "Resultsfor$run" >> $run.txt
echo / >> $run.txt
rm files
/afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/DynamicPython.sh $run.txt

#!/bin/bash
echo Starting simpleSpecifyPath.sh
echo Config file $1
if [ -f "$1" ]
then
   file_name=$1
else
echo "File \"$1\" with parameters does not exist."
exit 0
fi

export numparameters=`cat $1 | wc -l`

if [[ $numparameters -ne 6 ]]
then
   echo "!!! The Number of short parameters(lines) is $numparameters and  should be 6"
   exit 0
fi

export run=`awk -F"=" '{print $2}' $1 | awk 'NR==1'`
export dataset=`awk -F"=" '{print $2}' $1 | awk 'NR==2'`
export queue=`awk -F"=" '{print $2}' $1 | awk 'NR==3'`
export project=`awk -F"=" '{print $2}' $1 | awk 'NR==4'`
export cfgtemplate=`awk -F"=" '{print $2}' $1 | awk 'NR==5'`
export label=`awk -F"=" '{print $2}' $1 | awk 'NR==6'`

echo "-----LIST OF PARAMETERS-----"
echo run = $run
echo dataset = $dataset
echo queue = $queue
echo project = $project
echo cfgtemplate = $cfgtemplate
echo label = $label
echo "-----------------------------"

export home=`echo ~`
export casa=`pwd`
export castor=`echo $CASTOR_HOME`

export datasetpath=`echo $dataset | sed -e "s|/|_|g"`

echo datasetpath = $datasetpath

if [ -f "$run.txt" ]
then
   rm $run.txt
fi

echo ~/scratch0/$label/$datasetpath/$run > $run.txt
echo $castor/$label/$datasetpath/$run >> $run.txt
echo $dataset >> $run.txt
echo $run >> $run.txt
echo $queue >> $run.txt
echo "2000" >> $run.txt
echo -1 >> $run.txt
echo $project >> $run.txt
echo $cfgtemplate >> $run.txt
echo $label-$run >> $run.txt
echo / >> $run.txt

export castorExist=`nsls $castor/$label/$datasetpath 2>&1 | grep "No such file" | wc -l`

if [[ $castorExist -eq 1 ]]
then
   echo "path in castor for this dataset doesn't exist, creating the castor folder"
   rfmkdir $castor/$label/
   rfmkdir $castor/$label/$datasetpath/   
fi

if [ -d "/afs/cern.ch/user/c/carrillo/scratch0/$label/$datasetpath/" ];
then
  echo "Data set folder Exist"
else 
  echo "Data set folder doesn't exist, creating folder"
  ls ~/scratch0/$label/$datasetpath/
  mkdir ~/scratch0/$label/
  mkdir ~/scratch0/$label/$datasetpath/
fi

mv $run.txt ~/scratch0/$label/$datasetpath/

cd ~/scratch0/$label/$datasetpath/

if [ -f "files" ]
then
   echo "removing files"
   rm files
fi

echo "Calling dynamic Python"
/afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/DynamicPython.sh $run.txt



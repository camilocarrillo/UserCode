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

export datasetpath=`echo $dataset | sed -e "s|/|_|g"`

if [ -f "$run.txt" ]
then
   rm $run.txt
fi

echo ~/scratch0/$datasetpath/$run > $run.txt
echo $castor/$datasetpath/$run >> $run.txt
echo $dataset >> $run.txt
echo $run >> $run.txt
echo $queue >> $run.txt
echo "2000" >> $run.txt
echo -1 >> $run.txt
echo $project >> $run.txt
echo $cfgtemplate >> $run.txt
echo "eff$run" >> $run.txt
echo "/castor/cern.ch/user/c/carrillo/My_HLT_Skim/$run/" >> $run.txt

export datasetcastorpath=`nsls $castor/$datasetpath | grep "No Such" | wc -l`

if [[ $datasetcastorpadh -eq 1 ]]
then
   echo "path in castor for this dataset doesn't exist, creating the castor folder"
   rfmkdir $castor/$datasetpath   
fi

if [ -d "~/scratch0/$datasetpath/" ]
then
  echo "Data set folder Exist"
else 
  echo "Data set folder doesn't exist, creating folder"
  mkdir ~/scratch0/$datasetpath/
fi

mv $run.txt ~/scratch0/$datasetpath/

cd ~/scratch0/$datasetpath/

if [ -f "files" ]
then
   echo "removing files"
   rm files
fi

##echo "creating files for hlt like for run $run"
nsls My_HLT_Skim/$run/ > files
##/afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/rawtofile

echo "Calling dynamic Python"
/afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/DynamicPython.sh $run.txt

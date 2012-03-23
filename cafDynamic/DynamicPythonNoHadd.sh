#!/bin/bash
echo Config file $1
if [ -f "$1" ]
then
   file_name=$1
else
echo "File \"$1\" does not exist."
exit 0
fi

export numparameters=`cat $1 | wc -l`

if [[ $numparameters -ne 11 ]]
then
   echo "!!! The Number of parameters(lines) is $numparameters and  should be 11"
   exit 0
fi

export wd=`awk 'NR==1' $1`
export castorpad=`awk 'NR==2' $1`
export dataset=`awk 'NR==3' $1`
export run=`awk 'NR==4' $1`
export queue=`awk 'NR==5' $1`
export max=`awk 'NR==6' $1`
export step=`awk 'NR==7' $1` #ac'a raiz cuadrada
export WhereIsTheProject=`awk 'NR==8' $1`
export cfgtemplate=`awk 'NR==9' $1`
export key=`awk 'NR==10' $1`
export firstpartpad=`awk 'NR==11' $1`


echo "-----LIST OF PARAMETERS-----"
echo working Directory $wd
echo castorpad $castorpad
echo dataset $dataset
echo run $run
echo queue $queue
echo max $max
echo step = $step
echo The Project Is In $WhereIsTheProject
echo The cfgtemplate is $cfgtemplate
echo The Key of the jobs is $key
echo The first part of the path $firstpartpad
echo "-----------------------------"


echo Testing cfgtemplate
~carrillo/public/for_All/cafDynamic/testcfgtemplatequality.sh $cfgtemplate

export castorExist=`nsls $castorpad 2>&1 | grep "No such file" | wc -l`

if [[ $castorExist -eq 1 ]]
then
   echo The Castor Folder doesnt exist
   nsls $castorpad
   echo Creating the Folder
   rfmkdir $castorpad
fi

export projectExist=`ls $WhereIsTheProject 2>&1 | grep "No such file" | wc -l`

if [[ $projectExist -eq 1 ]]
then
   echo !!!!!!!!!!! The project doesnt exist
   ls $WhereIsTheProject
   exit 0  
fi

export castorExist=`nsls $castorpad 2>&1 | grep "No such file" | wc -l`

if [[ $castorExist -eq 1 ]]  
then
   echo !!!!!!!!! The Castor folder was not possible to create, perhaps you are missing the dataset folder, create it and run again.
   nsls $castorpad
   exit 0
fi

export foldersInCastor=`nsls $castorpad | wc -l`
echo Found $foldersInCastor files in CASTOR folder

if [[ $foldersInCastor -ne 0 ]]
then
   echo !!!!!!!! The Castor Folder is not empty, please clean it and run again.
   echo $castorpad
   nsls $castorpad
   exit 0
fi

if [ -f "files" ]
then
   echo Found file with list of files, skiping the query to dbs, please be sure that the file files belongs to the run you want to analyze.
   head files
   echo ...
else
   echo "File files (with the list of files) does not exist."
   echo Doing the query to dbs...
   echo The Data Set is $dataset
   echo The Run is $run
   ~carrillo/public/for_All/cafDynamic/aSearchCLI --dbsInst=cms_dbs_prod_global --limit=-1 --input "find file where dataset like $dataset and run = $run" > files
fi

export numfiles=`cat files | grep .root | wc -l`

if [[ $numfiles -eq 0 ]]
then
   echo empty files
   echo !!! The query to the Data Base for Data Set=$dataset and Run=$run was empty please check if DBS is working
   cat files
   exit 0
fi

#if [[ $numfiles -le 10 ]]
#then
#   echo too few files, does not have sense to submit jobs run due low statistics
#   echo $numfiles
#   exit 0
#fi

export firstline=`head -n 1 files`
export fileexist=`nsls $firstpartpad/$firstline 2>&1 | grep "No such file" | wc -l`

if [[ $fileexist -eq 1 ]]
then
   echo !!!!!!!!!!!!!!!! The first file  $firstpartpad/$firstline in files does not exist in CASTOR check your first part path or your file files.
   exit 0
fi

echo The run will be distributed in $numfiles jobs.
mkdir $wd
cat files | grep .root > $wd/files
cd $wd
echo $WhereIsTheProject > parameters
echo $castorpad >> parameters
echo $queue >> parameters
echo $max >> parameters
echo cfgtemplate >> parameters
echo $key >> parameters
sed -e "s|-input-|$firstpartpad-pad--filename-|g" -e "s|-output-|$key.-filename-|g" $cfgtemplate > cfgtemplate
echo "Calling gencafNewDynamicPython"
~carrillo/public/for_All/cafDynamic/gencafNewDynamicPython.sh parameters #creating files for submit the jobs
echo Submiting $key in $numfiles jobs
source corraBatch #submiting jobs


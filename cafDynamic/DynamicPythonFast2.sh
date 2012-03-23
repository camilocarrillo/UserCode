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

if [ -f "files-$key.txt" ]
then
   echo Found file with list of files-$key.txt, skiping the query to dbs, please be sure that the file files-$key.txt belongs to the run you want to analyze.
   echo firstHead
   head files-$key.txt
   echo ...
else
   echo "File files-$key.txt (with the list of files-$key.txt) does not exist."
   echo Doing the query to dbs...
   echo The Data Set is $dataset
   echo The Run is $run
#  ~carrillo/public/for_All/cafDynamic/aSearchCLI --dbsInst=cms_dbs_prod_global --limit=-1 --input 
   dbs search --query find file where dataset like $dataset and run = $run" > files-$key.txt
fi

export numfiles=`cat files-$key.txt | grep .root | wc -l`

if [[ $numfiles -eq 0 ]]
then
   echo empty $PWD/files-$key.txt
   echo !!! The query to the Data Base for Data Set=$dataset and Run=$run was empty please check if DBS is working
   cat files-$key.txt
   exit 0
fi

#if [[ $numfiles -le 10 ]]
#then
#   echo too few files, does not have sense to submit jobs run due low statistics
#   echo $numfiles
#   exit 0
#fi

echo second head
export firstline="head -n 1 files-$key.txt"
export fileexist=`nsls $firstpartpad/$firstline 2>&1 | grep "No such file" | wc -l`

if [[ $fileexist -eq 1 ]]
then
   echo !!!!!!!!!!!!!!!! The first file  $firstpartpad/$firstline in files-$key.txt does not exist in CASTOR check your first part path or your file files-$key-$run.
   exit 0
fi

echo The run will be distributed in $numfiles jobs.
mkdir $wd
cat files-$key.txt | grep .root > $wd/files-$key.txt
cd $wd
echo $WhereIsTheProject > parameters
echo $castorpad >> parameters
echo $queue >> parameters
echo $max >> parameters
echo cfgtemplate >> parameters
echo $key >> parameters
echo files-$key.txt >> parameters
sed -e "s|-input-|$firstpartpad-pad--filename-|g" -e "s|-output-|$key.-filename-|g" $cfgtemplate > cfgtemplate
echo "Calling gencafNewDynamicPythonFast"
~carrillo/public/for_All/cafDynamic/gencafNewDynamicPythonFast.sh parameters #creating files for submit the jobs
echo Submiting $key in $numfiles jobs
source corraBatch #submiting jobs
sleep 10
export numrun=`bjobs | grep RUN | grep $queue | wc -l`
export numpend=`bjobs | grep PEND | grep $queue | wc -l`
warn=0;

export folderexist=`ls ~/public/report/ 2>&1 | grep "No such file" | wc -l`
if [[ $folderexist -eq 1 ]]
	then
	echo "creating ~/public/report/"
	mkdir ~/public/report
fi

echo Checking the status of the submited jobs

until [[ $numrun -eq 0 && $numpend -eq 0 || $numfilesProduced -eq $numfiles ]]
        do
	export numrun=`bjobs | grep RUN | grep $queue | wc -l`
	export numpend=`bjobs | grep PEND | grep $queue | wc -l`
	export numfilesProduced=`nsls $castorpad | wc -l`
	warn=$(($numrun+$numpend+$numfilesProduced-$numfiles))
        sleep 300
	let "i=$i+1"
	let "t=i*10"
	echo t=$t s jobs: \| $key \| run=$numrun \| pend=$numpend \| in Castor=$numfilesProduced of $numfiles \| warn=$warn \|
	~carrillo/public/for_All/cafDynamic/htmline.sh $t $numrun $numpend $numfilesProduced $numfiles $warn $key > ~/public/report/$key.html
        done

export numfilesProduced=`nsls $castorpad | wc -l`
export realnumfiles=`echo $max`
if [[ $numfiles -le $max ]]
then
  export realnumfiles=`echo $numfiles`
fi
let "diff=$realnumfiles-$numfilesProduced"
echo You had $realnumfiles files to analyze and you got $numfilesProduced
if [[ $realnumfiles -ne $numfilesProduced ]]
then
   echo ++++ Warning $diff jobs did not produce a result.
else
   echo all the jobs were done.  
fi
mkdir $wd/merging
cd $wd/merging

if [[ $numfilesProduced -eq 1 ]]
then
   echo !!! The merging was not submited because you just have one file find your results under Castor.
   echo $castorpad
   export singlefile=`nsls $castorpad`
   echo $singlefile
   rfcp $castorpad/$singlefile $castorpad/$key.root
   echo "!!! $key is done with one job find it under $wd, time=$t, files=$numfiles, host=$HOST." > finbash.txt
#   mail 0041762210358@mail2sms.cern.ch < finbash.txt
   cat finbash.txt
   rm finbash.txt
   exit 0
fi

export foldersInCastor=`nsls $castorpad | grep $key | wc -l`

if [[ $foldersInCastor -eq 0 ]]
then
   echo !!! Your Config File is not producing root files, run interactive cmsRun $wd/anyfile.cfg
   nsls $castorpad
   exit 0
fi

if [[ $step -eq "-1" ]]
then 
 step=$(echo "sqrt($foldersInCastor)" | bc)
 echo Step setted with square root step=$step
fi

echo $castorpad > parameters
echo $WhereIsTheProject >> parameters
echo $step >> parameters
echo $queue >> parameters
echo $key >> parameters

~carrillo/public/for_All/cafDynamic/mergingDynamic/genmergeLocalDynamic.sh parameters
echo submiting merging jobs
source corraBatchLocal 

export expectedInCastorLocal=`cat corraBatchLocal | wc -l`
echo MergingFiles for $key with $expectedInCastorLocal jobs in steps of $step

sleep 10
export numrun=`bjobs | grep RUN | grep $queue | wc -l`
export numpend=`bjobs | grep PEND | grep $queue | wc -l`
export filesInCastorLocal=`nsls $castorpad | grep Local | wc -l`

#until [[ $numrun -eq 0 && $numpend -eq 0 || $expectedInCastorLocal -eq $filesInCastorLocal ]]
until [[ $numrun -eq 0 && $numpend -eq 0 ]]
        do
        export numrun=`bjobs | grep RUN | grep $queue | wc -l`
        export numpend=`bjobs | grep PEND | grep $queue | wc -l`
	export filesInCastorLocal=`nsls $castorpad | grep Local | wc -l`        
        warn2=$(($numrun+$numpend+$filesInCastorLocal-$expectedInCastorLocal))
        sleep 300
        let "i=$i+1"
        let "t=i*10"
        echo t=$t s jobs: \| $key \| run=$numrun \| pend=$numpend \| in Castor=$filesInCastorLocal of $expectedInCastorLocal \| warn2=$warn2 \|
	~carrillo/public/for_All/cafDynamic/htmline.sh $t $numrun $numpend $filesInCastorLocal $expectedInCastorLocal $warn2 Merg_$key > ~/public/report/$key.html
        sleep 300
        done

export foldersInCastorLocal=`nsls $castorpad | grep Local | wc -l`
if [[ $foldersInCastorLocal -eq 0 ]]
then
   echo here was a problem in the merging.
   nsls $castorpad
   exit 0
fi

/afs/cern.ch/cms/caf/scripts/cmsbsub -q $queue -e jobLocalFinal.err -o jobLocalFinal.olsf -J jobLocalFinal jobLocalFinal.lsf
echo Submiting Last Merging for $key for $filesInCastorLocal files
sleep 10
export numrun=`bjobs | grep RUN | grep $queue | wc -l`
export numpend=`bjobs | grep PEND | grep $queue | wc -l`
export filesInCastorLocalfinal=`nsls $castorpad | grep Local.root | wc -l`     

until [[ $numrun -eq 0 && $numpend -eq 0 || $filesInCastorLocalfinal -eq 1 ]]
        do  
        export numrun=`bjobs | grep RUN | grep $queue | wc -l`
        export numpend=`bjobs | grep PEND | grep $queue | wc -l`
	export filesInCastorLocalfinal=`nsls $castorpad | grep Local.root | wc -l`     
        let "i=$i+1"
        let "t=i*10"
	echo t=$t s jobs: \| $key \| run=$numrun \| pend=$numpend \| merging $filesInCastor \|
	~carrillo/public/for_All/cafDynamic/htmline.sh $t $numrun $numpend  $numfilesProduced $numfiles $warn Last_Merge_$key > ~/public/report/$key.html
        sleep 300
        done
sleep 120
rfcp $castorpad/Local.root $castorpad/$key.root
echo $castorpad
nsls $castorpad
echo "$key is done, time=$t, files=$numfiles, warning=($warn,$warn2), host=$HOST" > finbash.txt
#mail 0041762210358@mail2sms.cern.ch < finbash.txt
cat finbash.txt
rm finbash.txt
~carrillo/public/for_All/cafDynamic/htmline.sh $t 0 0 $numfilesProduced $numfiles $warn done_$key > ~/public/report/$key.html
sleep 120
echo DONE! Sleeping 2 minutes for $key in Castor

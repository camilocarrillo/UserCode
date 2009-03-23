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
   echo !!! The Castor Folder doesnt exist
   nsls $castorpad
   echo Doing the Folder
   rfmkdir $castorpad
fi

export castorExist=`nsls $castorpad 2>&1 | grep "No such file" | wc -l`

if [[ $castorExist -eq 1 ]]  
then
   echo !!! Please create the castor folder and run again
   nsls $castorpad
   exit 0
fi


export foldersInCastor=`nsls $castorpad | wc -l`
echo Found $foldersInCastor files in CASTOR folder

if [[ $foldersInCastor -ne 0 ]]
then
   echo !!! The Castor Folder Should be empty
   nsls $castorpad
   exit 0
fi
export num=`bjobs | grep $queue | wc -l`
if [[ $numrun -ne 0 ]]
	then
	echo Please wait until your $queue quee is finished
	exit 0
	fi


if [ -f "files" ]
then
   echo Found file with list of files, skiping the query
else
   echo "File files (with the list of files) does not exist."
   echo Doing the query...
   echo The Data Set is $dataset
   echo The Run is $run
   #/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/cruzetDQM/CMSSW_2_0_6/src/Configuration/GlobalRuns/data/aSearchCLI --input "find file where run=$run and dataset=$dataset" --limit -1 > files
   ~carrillo/public/for_All/cafDynamic/aSearchCLI --dbsInst=cms_dbs_prod_global --limit=-1 --input "find file where dataset like $dataset and run = $run" > files

fi

export numfiles=`cat files | grep .root | wc -l`

if [[ $numfiles -eq 0 ]]
then
   echo empty files
   echo !!! The query to the Data Base for Data Set=$dataset and Run=$run was empty
   cat files
   exit 0
fi

export firstline=`head -n 1 files`
export fileexist=`nsls $firstpartpad/$firstline 2>&1 | grep "No such file" | wc -l`

if [[ $fileexist -eq 1 ]]
then
   echo The first file  $firstpartpad/$firstline in files does not exist in CASTOR check your first part path or your file files
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
~carrillo/public/for_All/cafDynamic/gencafNewDynamicPython.sh parameters #creating files for submit the jobs
echo Submiting $key jobs
source corraBatch #submiting jobs
sleep 10
export numrun=`bjobs | grep RUN | grep $queue | wc -l`
export numpend=`bjobs | grep PEND | grep $queue | wc -l`
warn=0;
mkdir ~/public/report/
until [[ $numrun -eq 0 && $numpend -eq 0 || $numfilesProduced -eq $numfiles ]]
        do
	export numrun=`bjobs | grep RUN | grep $queue | wc -l`
	export numpend=`bjobs | grep PEND | grep $queue | wc -l`
	export numfilesProduced=`nsls $castorpad | wc -l`
	warn=$(($numrun+$numpend+$numfilesProduced-$numfiles))
        sleep 10
	let "i=$i+1"
	let "t=i*10"
	echo t=$t s jobs: \| run=$numrun \| pend=$numpend \| in Castor=$numfilesProduced of $numfiles \| warn=$warn \|
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
   echo $diff jobs didnt produce a result.
else
   echo all the jobs were done.  
fi
mkdir $wd/merging
cd $wd/merging

if [[ $numfilesProduced -eq 1 ]]
then
   echo !!! The merging was not submited because you just have one file find your results under Castor or here.
   export singlefile=`nsls $castorpad`
   echo $singlefile
   rfcp $castorpad/$singlefile $wd/$key.root
   echo "!!! $key is done find it under $wd, time=$t, files=$numfiles, host=$HOST." > finbash.txt
   mail 0041762210358@sms.switch.ch < finbash.txt
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
source corraBatchLocal #submiting merging jobs

export expectedInCastorLocal=`cat corraBatchLocal | wc -l`
echo MergingFiles for $key with $expectedInCastorLocal jobs in steps of $step

sleep 10
export numrun=`bjobs | grep RUN | grep $queue | wc -l`
export numpend=`bjobs | grep PEND | grep $queue | wc -l`
export filesInCastorLocal=`nsls $castorpad | grep Local | wc -l`

until [[ $numrun -eq 0 && $numpend -eq 0 || $expectedInCastorLocal -eq $filesInCastorLocal ]]
        do
        export numrun=`bjobs | grep RUN | grep $queue | wc -l`
        export numpend=`bjobs | grep PEND | grep $queue | wc -l`
	export filesInCastorLocal=`nsls $castorpad | grep Local | wc -l`        
        warn2=$(($numrun+$numpend+$filesInCastorLocal-$expectedInCastorLocal))
        sleep 10
        let "i=$i+1"
        let "t=i*10"
        echo t=$t s jobs: \| run=$numrun \| pend=$numpend \| in Castor=$filesInCastorLocal of $expectedInCastorLocal \| warn2=$warn2 \|
	~carrillo/public/for_All/cafDynamic/htmline.sh $t $numrun $numpend $filesInCastorLocal $expectedInCastorLocal $warn2 Merg_$key > ~/public/report/$key.html
        sleep 10
        done

export foldersInCastorLocal=`nsls $castorpad | grep Local | wc -l`
if [[ $foldersInCastorLocal -eq 0 ]]
then
   echo here was a problem in the merging.
   nsls $castorpad
   exit 0
fi

bsub -q $queue -e jobLocalFinal.err -o jobLocalFinal.olsf -J jobLocalFinal jobLocalFinal.lsf
echo Submiting Last Merging for $key for $filesInCastorLocal files
sleep 10
export numrun=`bjobs | grep RUN | grep $queue | wc -l`
export numpend=`bjobs | grep PEND | grep $queue | wc -l`

until [[ $numrun -eq 0 && $numpend -eq 0 || -f Local.root ]]
        do  
        export numrun=`bjobs | grep RUN | grep $queue | wc -l`
        export numpend=`bjobs | grep PEND | grep $queue | wc -l`
        let "i=$i+1"
        let "t=i*10"
	echo t=$t s jobs: \| run=$numrun \| pend=$numpend \| merging $filesInCastor \|
	~carrillo/public/for_All/cafDynamic/htmline.sh $t $numrun $numpend  $numfilesProduced $numfiles $warn Last_Merge_$key > ~/public/report/$key.html
        sleep 10
        done
sleep 10
rfcp $castorpad/Local.root $castorpad/$key.root
rm Local.root
echo "$key is done, time=$t, files=$numfiles, warning=($warn,$warn2), host=$HOST" > finbash.txt
mail 0041762210358@sms.switch.ch < finbash.txt
cat finbash.txt
rm finbash.txt
~carrillo/public/for_All/cafDynamic/htmline.sh $t 0 0 $numfilesProduced $numfiles $warn done$key > ~/public/report/$key.html

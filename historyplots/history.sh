#!/bin/bash
echo Config file $1
if [ -f "$1" ]
then
   file_name=$1
else
echo "File \"$1\" does not exist."
exit 0
fi

i=1

export NumberOfRuns=`cat $1 | wc -l`
echo $NumberOfRuns

while [[ $i -le $NumberOfRuns ]]
do
  export run=`awk 'NR=='$i' {print $1}' $1`
  export run=`echo $run`
  echo "run to bring"

  if [[ -f eff$run.root ]]
      then 
      echo File eff$run.root already exist
  else
      scp carrillo@cmsrpc402b20:/var/www/html/efficiency/_Cosmics_CRAFT09-PromptReco-v1_RECO/$run/eff$run.root .
  fi


  if [[ -f sec$run.root ]]
      then 
      echo File sec$run.root already exist
  else
      scp carrillo@cmsrpc402b20:/var/www/html/efficiency/_Cosmics_CRAFT09-PromptReco-v1_RECO/$run/sec$run.root .
  fi
  
  if [[ -f eff$run.root ]]
      then
      echo Got $run.root
  else
      echo "!!!!!!!!!!!!!!!!!!!!! Problem with $run.root"
  fi

  if [[ -f sec$run.root ]]
      then
      echo Got sec$run.root
  else
      echo "!!!!!!!!!!!!!!!!!!!!! Problem with sec$run.root"
  fi

  let "i=$i+1"
done 

cp $1 runslist.txt

echo Number of runs $i

sed -e "s|-N-|$i|g" ~carrillo/historyplots/history.C > history.C

root history.C

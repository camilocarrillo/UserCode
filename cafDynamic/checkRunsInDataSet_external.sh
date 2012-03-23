#!/bin/bash
echo Config file $1
if [ -f "$1" ]
then
   file_name=$1
else
#echo "File \"$1\" does not exist."
exit 0
fi

export datasetpath=`echo $2 | sed -e "s|/|_|g"`

#echo $2

~carrillo/public/for_All/cafDynamic/aSearchCLI --dbsInst=cms_dbs_prod_global --limit=-1 --input "find run where dataset = $2" > runsIn$datasetpath

export numnoDS=`~carrillo/public/for_All/cafDynamic/comparingUnoMenosDos.sh $1 runsIn$datasetpath | wc -l`

if [[ $numnoDS -ne 0 ]]
then
   echo "!!! Following runs are not in the dataset please delete them from the run list file"
   ~carrillo/public/for_All/cafDynamic/comparingUnoMenosDos.sh $1 runsIn$datasetpath
   sleep 80000
   exit 0
fi





#!/bin/bash
cd /tmp/carrillo/
mkdir prodimages
cd prodimages
if [ -d $1 ]
then
  rm $1 -rf
fi
mkdir $1
cd $1
export datasetpath=`echo $2 | sed -e "s|/|_|g"`
export label=`echo $3`
cp /afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/html/htmltemplates/ -rf .
export rootfiles=`nsls /castor/cern.ch/user/c/carrillo/$label/$datasetpath/$1/$label-$1.root | wc -l`
if [[ $rootfiles -eq 0 ]]
then
   echo There is not merged root file produced, trying to get Local.root
   export local=`nsls /castor/cern.ch/user/c/carrillo/$label/$datasetpath/$1/Local.root | wc -l`
   if [[ $local -eq 0 ]]
   then
      echo Neither root file skipping production of images
      exit 0
   else
      rfcp /castor/cern.ch/user/c/carrillo/$label/$datasetpath/$1/Local.root /castor/cern.ch/user/c/carrillo/$label/$datasetpath/$1/$label-$1.root 
   fi
fi

rfcp /castor/cern.ch/user/c/carrillo/$label/$datasetpath/$1/$label-$1.root .
sed -e "s|-RUN-|$1|g" -e "s|-label-|$label|g" /afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/html/seg2D2label.py > seg2D2.py

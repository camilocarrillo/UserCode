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
cp /afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/html/htmltemplates/ -rf .
rfcp /castor/cern.ch/user/c/carrillo/$datasetpath/$1/eff$1.root .
sed "s|-RUN-|$1|g" /afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/html/seg2D2.py > seg2D2.py

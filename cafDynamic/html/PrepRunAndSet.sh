#!/bin/bash
/afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic//html/prepProdImages.sh $1 $2
cd $3 #this is the location of the project to analyze with seg2D2.py
eval `scramv1 ru -sh`
cd /tmp/carrillo/prodimages/$1/
cmsRun seg2D2.py
htmltemplates/changeRun.sh $1
cd Sides
/tmp/carrillo/prodimages/$1/htmltemplates/rot.sh
cd /tmp/carrillo/
#scp -r prodimages/$1 webrpc@webcms.ba.infn.it:public_html/efficiency/$1

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

if [[ $numparameters -ne 12 ]]
then
   echo "!!! The Number of parameters(lines) is $numparameters and  should be 12"
   exit 0
fi


export HV1=`awk 'NR==1' $1`
export RUN1=`awk 'NR==2' $1`
export HV2=`awk 'NR==3' $1`
export RUN2=`awk 'NR==4' $1`
export HV3=`awk 'NR==5' $1`
export RUN3=`awk 'NR==6' $1`
export HV4=`awk 'NR==7' $1`
export RUN4=`awk 'NR==8' $1`
export HV5=`awk 'NR==9' $1`
export RUN5=`awk 'NR==10' $1`
export HV6=`awk 'NR==11' $1`
export RUN6=`awk 'NR==12' $1`


echo "-----LIST OF PARAMETERS-----"
echo RUN1 $RUN1 HV1 $HV1
echo RUN2 $RUN2 HV2 $HV2
echo RUN3 $RUN3 HV3 $HV3
echo RUN4 $RUN4 HV4 $HV4
echo RUN5 $RUN5 HV5 $HV5
echo RUN6 $RUN6 HV6 $HV6
echo "-----------------------------"

mkdir $HV1
mkdir $HV2
mkdir $HV3
mkdir $HV4
mkdir $HV5
mkdir $HV6

cd $HV1
scp carrillo@cmsrpc402b20:/var/www/html/efficiency/_Cosmics_CRAFT09-PromptReco-v1_RECO/$RUN1/rollYeff.txt .
scp carrillo@cmsrpc402b20:/var/www/html/efficiency/_Cosmics_CRAFT09-PromptReco-v1_RECO/$RUN1/sec$RUN1.root .
cd ../
cd $HV2
scp carrillo@cmsrpc402b20:/var/www/html/efficiency/_Cosmics_CRAFT09-PromptReco-v1_RECO/$RUN2/rollYeff.txt .
scp carrillo@cmsrpc402b20:/var/www/html/efficiency/_Cosmics_CRAFT09-PromptReco-v1_RECO/$RUN2/sec$RUN2.root .
cd ../
cd $HV3
scp carrillo@cmsrpc402b20:/var/www/html/efficiency/_Cosmics_CRAFT09-PromptReco-v1_RECO/$RUN3/rollYeff.txt .
scp carrillo@cmsrpc402b20:/var/www/html/efficiency/_Cosmics_CRAFT09-PromptReco-v1_RECO/$RUN3/sec$RUN3.root .
cd ../
cd $HV4
scp carrillo@cmsrpc402b20:/var/www/html/efficiency/_Cosmics_CRAFT09-PromptReco-v1_RECO/$RUN4/rollYeff.txt .
scp carrillo@cmsrpc402b20:/var/www/html/efficiency/_Cosmics_CRAFT09-PromptReco-v1_RECO/$RUN4/sec$RUN4.root .
cd ../
cd $HV5
scp carrillo@cmsrpc402b20:/var/www/html/efficiency/_Cosmics_CRAFT09-PromptReco-v1_RECO/$RUN5/rollYeff.txt .
scp carrillo@cmsrpc402b20:/var/www/html/efficiency/_Cosmics_CRAFT09-PromptReco-v1_RECO/$RUN5/sec$RUN5.root .
cd ../
cd $HV6
scp carrillo@cmsrpc402b20:/var/www/html/efficiency/_Cosmics_CRAFT09-PromptReco-v1_RECO/$RUN6/rollYeff.txt .
scp carrillo@cmsrpc402b20:/var/www/html/efficiency/_Cosmics_CRAFT09-PromptReco-v1_RECO/$RUN6/sec$RUN6.root .
cd ../

sed -e "s|-RUN1-|$RUN1|g" -e "s|-HV1-|$HV1|g" -e "s|-RUN2-|$RUN2|g" -e "s|-HV2-|$HV2|g" -e "s|-RUN3-|$RUN3|g" -e "s|-HV3-|$HV3|g" -e "s|-RUN4-|$RUN4|g" -e "s|-HV4-|$HV4|g" -e "s|-RUN5-|$RUN5|g" -e "s|-HV5-|$HV5|g" -e "s|-RUN6-|$RUN6|g" -e "s|-HV6-|$HV6|g" /afs/cern.ch/user/c/carrillo/hvscan/GraphAndFittemplate6PointsGeneric.C > GraphAndFittemplate6Points.C

cp /afs/cern.ch/user/c/carrillo/hvscan/index* .

sed -e "s|-RUN1-|$RUN1|g" -e "s|-HV1-|$HV1|g" -e "s|-RUN2-|$RUN2|g" -e "s|-HV2-|$HV2|g" -e "s|-RUN3-|$RUN3|g" -e "s|-HV3-|$HV3|g" -e "s|-RUN4-|$RUN4|g" -e "s|-HV4-|$HV4|g" -e "s|-RUN5-|$RUN5|g" -e "s|-HV5-|$HV5|g" -e "s|-RUN6-|$RUN6|g" -e "s|-HV6-|$HV6|g" /afs/cern.ch/user/c/carrillo/hvscan/index.html > index.html
cp /afs/cern.ch/user/c/carrillo/hvscan/rolls* .
cp /afs/cern.ch/user/c/carrillo/hvscan/dohvscan6P.sh .
cp /afs/cern.ch/user/c/carrillo/hvscan/splitBySide.sh .
sed -e "s|-HV1-|$HV1|g" -e "s|-HV2-|$HV2|g" -e "s|-HV3-|$HV3|g" -e "s|-HV4-|$HV4|g" -e "s|-HV5-|$HV5|g" -e "s|-HV6-|$HV6|g" /afs/cern.ch/user/c/carrillo/hvscan/splitAllBySide.sh > splitAllBySide.sh

chmod +x splitAllBySide.sh

cp /afs/cern.ch/user/c/carrillo/hvscan/genall.txt .
cp /afs/cern.ch/user/c/carrillo/hvscan/genhtml.sh .

./splitAllBySide.sh
./dohvscan6P.sh




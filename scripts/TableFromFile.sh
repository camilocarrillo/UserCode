#!/bin/bash

rm forisa
touch forisa
echo Loop over all the rollseff files

i=100
w=0
while [ $i -lt  200 ]
do
	w=$(echo "scale=2; ($i-100)*5" | bc)
	export all=`cat rollseff.SingleMuon100ptDigisDTyCSCSeg.$i.root.txt | grep TOTAL | awk '{print " 1.0 " $9 " " $11}'`
	echo $w $all
	i=$[$i+1]
done

#Seeing the uncertainity

i=100
w=0

while [ $i -lt  200 ]
do
        w=$(echo "scale=2; ($i-100)*5" | bc)
        export all=`cat rollseff.SingleMuon100ptDigisDTyCSCSeg.$i.root.txt | grep TOTAL | awk '{print " 1.0 " $11 " 0" }'`
        echo $w $all
        i=$[$i+1]
done

#number of predictions

i=100
w=0

while [ $i -lt  200 ]
do
        w=$(echo "scale=2; ($i-100)*5" | bc)
        export all=`cat rollseff.SingleMuon100ptDigisDTyCSCSeg.$i.root.txt | grep TOTAL | awk '{print " 1.0 " $4 " 1" }'`
        echo $w $all
        i=$[$i+1]
done



#cat $file | grep TOTAL | awk '{print $file " 0.1 " $9 " " $11}' >> forisa
#echo from $i we have $w $all

exit 0

#!/bin/bash

j=1;

echo Creating Rolls Simple
cat rollsbarrelMB4.txt | grep Re | awk '{print "r" $2 $4 $6 $8 $10 $12 $14 $16}' > rollssimple
echo Created Rolls simple

echo Creating resultsimple
cat result.txt | grep Re | awk '{print "r" $2 $4 $6 $8 $10 $12 $14 $16}' > resultsimple
echo Created resultsimple

echo Loop over all the rolls in rollssimple

for roll in `cat rollssimple*`
do
	export P=`cat resultsimple | grep $roll | wc -l`
	#echo $P
	if [ $P = "0" ]
	then
	echo $roll
	export hola=`awk 'NR=='$j' {print $0}' rollsbarrelMB4.txt`
	echo $hola 	
	fi
	let "j=$j+1"
done


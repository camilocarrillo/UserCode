#!/bin/bash

j=1;
i=1;

echo Creating Rolls Simple
cat rolls.txt | grep Re | awk '{print "r" $2 $4 $6 $8 $10 $12 $14 $16}' > rollssimple
echo Created Rolls simple

rm ALLSIMP.txt
rm result.txt

echo Creating ALLSIMP.txt
cat rollseff* | grep Re | awk '{print "r" $2 $4 $6 $8 $10 $12 $14 $16 " " $18 " " $20}' > ALLSIMP.txt
echo Created ALLSIMP.txt


echo Loop over all the rolls in rollssimple
for roll in `cat rollssimple*`
do
	cat ALLSIMP.txt | grep $roll | awk '{ print $2 " " $3}' > $roll
	O=0;
	P=0;
	p=0;
	o=0;
	
	#echo Loop over all rows in $roll
	i=1;
	for line in `cat $roll`
        	do
        	export p=`awk 'NR=='$i' {print $1}' $roll`
      		export o=`awk 'NR=='$i' {print $2}' $roll`
	        #echo $p $d
        	P=$(($p+$P))
	        O=$(($o+$O))
		let "i=$i+1"
     	done
	rm $roll

	if [ $P != 0 ]
		then
		E=$(echo "scale=4; $O/$P" | bc)
		e=$(echo "scale=4; sqrt($O/$P*(1.0-$O/$P))" | bc)
		E=$(echo "scale=4; $E*100" | bc)
		#echo $file"	"Predicted = $P"		"Observed = $O"		"Efficiency = $E%  	+/-	 $e%
		#echo $j
		awk 'NR=='$j' {$20="Predicted = '$P' 	Observed = '$O' 	Eff = '$E'% 	+/- 	'$e'%"; print}' rolls.txt >> result.txt
	fi
	let "j=$j+1"
	echo $j
done

rm ALLSIMP.txt
rm rollssimple

./suma >> result.txt

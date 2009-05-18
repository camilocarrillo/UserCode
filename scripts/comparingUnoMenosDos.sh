#!/bin/bash

j=1;

for line in `cat $1`
do
	export P=`cat $2 | grep $line | wc -l`
	#echo $P
	if [ $P = "0" ]
	then
	echo $line
	fi
	let "j=$j+1"
done


#!/bin/bash
for line1 in `cat $1`
do
	bool=0;
	for line2 in `cat $2`
        	do
		if [ $line1 == $line2 ]
		then
			bool=1;
		fi
     	done
	if [ $bool == 0 ]
	then
		echo $line1
	fi
done

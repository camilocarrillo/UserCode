#!/bin/bash
j=1
export lines=`cat $1 | wc -l`
until [[ $j -eq $lines ]] 
    do 
    #echo $j
    export id=`awk 'NR=='$j' {print $1}' $1`
    echo $id
    bkill $id
    let "j=$j+1"
    done
echo "jobs killed $j"
exit 0


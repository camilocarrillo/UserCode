#!/bin/bash
cat indexhead.html > $1.html
j=1
export lines=`cat $1 | wc -l`
until [[ $j -eq $lines ]] 
    do 
    #echo $j
    export roll=`awk 'NR=='$j' {print $1}' $1`
    export wp=`awk 'NR=='$j' {print $2}' $1`
    export emax=`awk 'NR=='$j' {print $3}' $1`
    export qual=`awk 'NR=='$j' {print $4}' $1`
    cp indexLocal.html $roll/index.html
    sed -e "s|-roll-|$roll|g" -e "s|-wp-|$wp|g" -e "s|-emax-|$emax|g" -e "s|-qual-|$qual|g" indexline.html >> $1.html
    #echo $roll
    #echo $wp
    #echo $emax
    #echo $qual
    let "j=$j+1"
    done
cat indextail.html >> $1.html
exit 0

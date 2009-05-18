#!/bin/bash

if [ -f "$1" ]
then
   file_name=$1
else
echo "File \"$1\" does not exist."
exit 0
fi

export compile=`scram b | grep "@@@@" | wc -l`

echo "------------------ $compile"

if [[ $compile -eq 2 ]]
then
   echo "---------------- Compiled... Now Running"
   time cmsRun $1 2>&1 ! /tmp/carrillo/$1.txt
   tail /tmp/carrillo/$1.txt
else 
   echo "Compilation error check your .cc"
   exit 0
fi

exit 0;

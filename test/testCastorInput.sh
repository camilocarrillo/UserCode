#!/bin/bash
if [ -f "$1" ]
then
   echo Confing File Template found and seems to be ok.
else
echo "Config File Template $1 does not exist."
sleep 3200
exit 0
fi
export input=`cat $1 | grep "\-input\-" | wc -l`
export output=`cat $1 | grep "\-output\-" | wc -l`

if [[ $input -ne 1 ]]
then
   echo  "!!! The config file doesn't have the line input"
   sleep 3200
   exit 0
fi

if [[ $output -ne 1 ]]
then
   echo  "!!! The config file doesn't have the line output"
   sleep 3200
   exit 0
fi



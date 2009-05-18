#!/bin/bash
echo Config file $1
if [ -f "$1" ]
then
   file_name=$1
else
echo "File \"$1\" does not exist."
exit 0
fi

export padROOT=`awk 'NR==1' $1`

nsls $padROOT > files 

rm allinone

touch allinone

for rootfile in `cat files`
	do
	echo $rootfile
	echo "\"rfio:$padROOT/$rootfile\"," >> allinone
	done

rm files
exit 0

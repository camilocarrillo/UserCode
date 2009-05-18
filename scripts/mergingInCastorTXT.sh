#!/bin/bash

j=1;
i=1;

rm merged.txt
touch merged.txt
echo Loop over all the files in castor
for file in `nsls $1`
do
  rfcat $1/$file >> merged.txt
done


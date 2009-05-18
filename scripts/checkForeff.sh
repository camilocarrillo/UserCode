#!/bin/bash

j=1;
i=1;

echo Loop over all the files in castor
for file in `cat filesInCastor`
do
  nsls $file/eff$file.root
done


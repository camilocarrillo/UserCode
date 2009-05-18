#!/bin/tcsh


if ($#argv != 1) goto usage
set casa = `pwd`
set run = $1
cd run$run
ls
set lss = `cat filelist | awk -F"/" '{printf "%s\n", $9}' | awk -F"." '{printf "%s\n", $1}'`
foreach file ($lss[*] )
  ls ../rollseff.${file}.root.txt
  cp ../rollseff.${file}.root.txt .
end
exit 0
usage:
echo movefilerub run-number

#!/bin/tcsh
echo $1

cat $1 | grep "W-2" > ! effWm2.txt
echo "-2 Far"
cat effWm2.txt | grep -v "S01" | grep -v "S02" | grep -v "S03" | grep -v "S10" | grep -v "S11" | grep -v "S12" > ! effWm2far.txt
echo "-2 Near"
cat effWm2.txt | grep -v "S04" | grep -v "S05" | grep -v "S06" | grep -v "S07" | grep -v "S08" | grep -v "S09" > ! effWm2near.txt

cat $1 | grep "W-1" > ! effWm1.txt
echo "-1 Far"
cat effWm1.txt | grep -v "S01" | grep -v "S02" | grep -v "S03" | grep -v "S10" | grep -v "S11" | grep -v "S12" > ! effWm1far.txt
echo "-1 Near"
cat effWm1.txt | grep -v "S04" | grep -v "S05" | grep -v "S06" | grep -v "S07" | grep -v "S08" | grep -v "S09" > ! effWm1near.txt

cat $1 | grep "W+0" > ! effW0.txt
echo "0 Far"
cat effW0.txt | grep -v "S01" | grep -v "S02" | grep -v "S03" | grep -v "S10" | grep -v "S11" | grep -v "S12" > ! effW0far.txt
echo "0 Near"
cat effW0.txt | grep -v "S04" | grep -v "S05" | grep -v "S06" | grep -v "S07" | grep -v "S08" | grep -v "S09" > ! effW0near.txt

cat $1 | grep "W+1" > ! effW1.txt
echo "1 Far"
cat effW1.txt | grep -v "S01" | grep -v "S02" | grep -v "S03" | grep -v "S10" | grep -v "S11" | grep -v "S12" > ! effW1far.txt
echo "1 Near"
cat effW1.txt | grep -v "S04" | grep -v "S05" | grep -v "S06" | grep -v "S07" | grep -v "S08" | grep -v "S09" > ! effW1near.txt

cat $1 | grep "W+2" > ! effW2.txt
echo "2 Far"
cat effW2.txt | grep -v "S01" | grep -v "S02" | grep -v "S03" | grep -v "S10" | grep -v "S11" | grep -v "S12" > ! effW2far.txt
echo "2 Near"
cat effW2.txt | grep -v "S04" | grep -v "S05" | grep -v "S06" | grep -v "S07" | grep -v "S08" | grep -v "S09" > ! effW2near.txt


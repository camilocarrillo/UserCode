rm GraphAndFit.C
sed -e "s|-side-|Wm2near|g" -e "s|-N-|101|g" GraphAndFittemplate.C > GraphAndFit.C
root -b GraphAndFit.C
rm GraphAndFit.C
sed -e "s|-side-|Wm2far|g" -e "s|-N-|105|g" GraphAndFittemplate.C > GraphAndFit.C
root -b GraphAndFit.C
rm GraphAndFit.C
sed -e "s|-side-|Wm1near|g" -e "s|-N-|101|g" GraphAndFittemplate.C > GraphAndFit.C
root -b GraphAndFit.C
rm GraphAndFit.C
sed -e "s|-side-|Wm1far|g" -e "s|-N-|105|g" GraphAndFittemplate.C > GraphAndFit.C
root -b GraphAndFit.C
rm GraphAndFit.C
sed -e "s|-side-|W0near|g" -e "s|-N-|101|g" GraphAndFittemplate.C > GraphAndFit.C
root -b GraphAndFit.C
rm GraphAndFit.C
sed -e "s|-side-|W0far|g" -e "s|-N-|105|g" GraphAndFittemplate.C > GraphAndFit.C
root -b GraphAndFit.C
rm GraphAndFit.C
sed -e "s|-side-|W1near|g" -e "s|-N-|101|g" GraphAndFittemplate.C > GraphAndFit.C
root -b GraphAndFit.C
rm GraphAndFit.C
sed -e "s|-side-|W1far|g" -e "s|-N-|105|g" GraphAndFittemplate.C > GraphAndFit.C
root -b GraphAndFit.C
rm GraphAndFit.C
sed -e "s|-side-|W2near|g" -e "s|-N-|101|g" GraphAndFittemplate.C > GraphAndFit.C
root -b GraphAndFit.C
rm GraphAndFit.C
sed -e "s|-side-|W2far|g" -e "s|-N-|105|g" GraphAndFittemplate.C > GraphAndFit.C
root -b GraphAndFit.C
source genall.txt
hadd -f barrel.root effDistro*.root
hadd -f wp.root wp*.root


sed "s|-RUN-|$1|g" htmltemplates/index.html > index.html
sed "s|-RUN-|$1|g" htmltemplates/indexDistro.html > indexDistro.html
sed "s|-RUN-|$1|g" htmltemplates/tmpindex.html > tmpindex.html
sed "s|-RUN-|$1|g" htmltemplates/indexEndCap.html > indexEndCap.html
sed "s|-RUN-|$1|g" htmltemplates/indexDistroEndCap.html > indexDistroEndCap.html
sed "s|-RUN-|$1|g" htmltemplates/tmpindexEndCap.html > tmpindexEndCap.html
sed "s|-RUN-|$1|g" htmltemplates/quality.html > quality.html
sed "s|-RUN-|$1|g" htmltemplates/MainIndex.html > MainIndex.html
sed "s|-RUN-|$1|g" htmltemplates/azimutal.html > azimutal.html
sed "s|-RUN-|$1|g" htmltemplates/azimutalbarrel.html > azimutalbarrel.html
sed "s|-RUN-|$1|g" htmltemplates/cls.html > cls.html
sed "s|-RUN-|$1|g" htmltemplates/ang.html > ang.html
showtags > info.txt
echo $LOCALRT >> info.txt

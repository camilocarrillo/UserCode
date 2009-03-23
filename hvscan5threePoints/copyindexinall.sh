cat indexhead.html > $1.html
for folder in `cat $1`
 do 
 cp index.html $folder
 sed -e "s|-roll-|$folder|g" indexline.html >> $1.html
 done
cat indextail.html >> $1.html


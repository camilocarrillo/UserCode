for i in `\ls -1 | grep RPC`; do cat $i | sed -e 's|RPC|G|g' > `echo $i | sed 's|RPC|G|g'` ; done

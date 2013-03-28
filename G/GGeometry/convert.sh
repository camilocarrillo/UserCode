for i in `\ls -1 | grep rpc`; do cat $i | sed -e 's|RPC|G|g'  | sed -e 's|rpc|g|g' > `echo $i | sed 's|rpc|g|g'` ; done

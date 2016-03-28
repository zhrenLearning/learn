bin/bash
while true
do 
procnum='ps -ef|grep "AsioHttp"|grep -v grep|wc -l'
if [ $procnum -eq 0 ]; then
    /usr/local/src/learnnew/bin/AsioHttp&
fi
   sleep 3000
done

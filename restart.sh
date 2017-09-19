kill -9 `ps -ef|grep getnews|grep -v grep|awk '{print $2}'`
cd ../app/
ldconfig
./getnews &
sleep 5
cd ../getnews

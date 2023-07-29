echo "restarting.............."
dir=$1
server_id=$2
start_time=$3
cp kill.sh $dir
cp myrunServer.sh $dir
cd $dir
./kill.sh
if [ $start_time -eq 0 ]
then
    ./runServer.sh start
else
    ./myrunServer.sh start $server_id $start_time
fi


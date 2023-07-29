echo "restarting.............."
dir=$1
cp kill.sh $dir
cd $dir
./kill.sh
./config_new.sh
./runServer.sh start

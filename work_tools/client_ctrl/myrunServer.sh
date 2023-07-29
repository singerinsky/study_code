#!/bin/bash

# 开发版 启动/停止/重启服务器脚本
# ./runServer.sh stop
# ./runServer.sh start
# ./runServer.sh [...]

# 发行版 启动/停止/重启服务器脚本
# ./runServer.sh dist stop
# ./runServer.sh dist start
# ./runServer.sh [...]

# 启动的服务器列表，按先后顺序排列，同类服务器要放在一起，ID会从STARTNUM开始递增。
SERVERLIST='superserver recordserver publicserver loginserver msgserver msdkserver sceneserver gatewayserver'

# 只把必要的服务器各启一个：
#SERVERLIST='superserver recordserver publicserver loginserver msgserver msdkserver sceneserver gatewayserver'

STARTNUM=1
SERVER_ID=$2
START_TIME=$3
# 如果要在一个账户下开多组服务器，可取消注释这里，赋予不同的 -s 序号，当然也要对应不同的 config/ 配置防止端口冲突。
GROUP="-s ${2}"
#GROUP="-s 156"


# 处理配置表换行符
if not command -v ./tools/dos2unix >/dev/null 2>&1; then 
    echo 'Error: command dos2unix needed.' 
    exit;
fi

exclude=(-not -path './csv/SeaBattleMapData/*')

find ./csv -type f "${exclude[@]}" | xargs ./tools/dos2unix > /dev/null 2>&1
find ./csv -type f "${exclude[@]}" | xargs sed -i -r '/^[,\ ]+$/d'
find ./csv -type f "${exclude[@]}" | xargs sed -i -r '/^[\ ]*$/d'


# 服务器关闭顺序，倒过来
SERVERLIST_REVERSE=
for serv in $SERVERLIST
do
	SERVERLIST_REVERSE=${serv}" "$SERVERLIST_REVERSE
done

# 参数解析
dist=""
action=""
runMode=""
watchDog=""
configpath="./config"
while [ -n "$1" ]
do
    case "$1" in
        dist)
            dist="dist";;
        start)
            action=$1;;
        stop)
            action=$1;;
        heap)
            runMode="heap";;
        asan)
            runMode="asan";;
		dist_asan)
		 	dist="dist";
            runMode="asan";;
		wd)
			watchDog="true";;
		config)
			if [[ $2 == "" ]]; then
    			echo -e "ERROR. config dir not specified. "
    			exit 2
			fi
			echo "configpath:$2"
			configpath=$2;;
        *)
            runMode="default";;
    esac
    shift
done


# 开启服务器
dowork()
{
	INDEX=$STARTNUM
	LASTSERVER=""

	for serv in $SERVERLIST
	do
		# 服务器 ID
		if [[ $serv != $LASTSERVER ]]
		then
			INDEX=1
		else
			INDEX=`expr $INDEX + 1`
		fi
		LASTSERVER=$serv

		# 启动脚本
		if [[ $dist == "dist" ]]
		then
			SERVERS="servers"
		else
			SERVERS=$serv
		fi
		printf -- "\033[32mstarting\033[0m $SERVERS/$serv -d $GROUP -a $INDEX\n"
		if [[ "heap" == $runMode ]]
		then
			#默认以10M为快照间隔
			mkdir -pv heap/$serv
            sleep 0.3
			HEAPPROFILE=heap/$serv/$serv$INDEX HEAP_PROFILE_INUSE_INTERVAL=10485760 ./$SERVERS/$serv -d $GROUP -a $INDEX --config $configpath > heap/$serv/$serv$INDEX.log 2>&1
        elif [[ "asan" = $runMode ]]
        then
			./$SERVERS/$serv -d $GROUP -a $INDEX -z $START_TIME --config $configpath >> logs/${serv}${INDEX}_asan.log 2>&1
		else
            ./$SERVERS/$serv -d $GROUP -a $INDEX -z $START_TIME --config $configpath 
		fi

		# 休息
		sleep 0.3
	done

	if [[ -n "$watchDog" ]]; then
		# 开启WatchDog
		if [[ $dist == "dist" ]]
		then
			python ./tools/ServerWatchDog.py -s "$SERVERLIST" -d $GROUP &
		else
			python ./tools/ServerWatchDog.py -s "$SERVERLIST" &
		fi
	fi

	# 打印启动的进程
	printf -- "\033[93mps x | grep \"server -d $GROUP\"\033[0m\n"
	ps x | grep "server -d $GROUP"
}


# 关闭服务器
stopwork()
{
    #关闭WatchDog
    ps aux | grep "ServerWatchDog" | grep -v "\-g" | awk '{print $2}' | xargs kill -9 2&>/dev/null

	ps ux | grep "superserver" | grep "\-d $GROUP" | sed -e '/grep/d' | awk '{print $2}' | xargs kill -USR1 2&>/dev/null
	printf -- "kill -USR1 to superserver\n"

	# 检查superserver是否停服了
	checksuper

	for serv in $SERVERLIST_REVERSE
	do
		if [[ $dist == "dist" ]]
		then
			SERVERS="servers"
		else
			SERVERS=$serv
		fi
		printf -- "\033[31mstoping\033[0m $SERVERS/$serv\n"
		ps aux | grep "/$serv"  | grep "\-d $GROUP" | sed -e '/grep/d' | awk '{print $2}' | xargs kill -9 2&>/dev/null
		sleep 0.3
	done
}

checksuper()
{
	printf -- "check superserver stop\n"
	while (true)
	do
		ps_out=`ps ux | grep "superserver" | grep "\-d $GROUP" | grep -v 'grep'`
		if [ -n "$ps_out" ];then
			sleep 1	
		else
			printf -- "\033[31msuperserver stopped\n"
			return	
		fi
	done
}

# 输出 开发版|发行版
if [[ $dist == "dist" ]];then
    printf -- "\033[93m\nEnvironment: Production\033[0m\n";
else
    printf -- "\033[93m\nEnvironment: Development\033[0m\n";
fi

# 主逻辑
case $action in
stop)
	stopwork
;;
start)
	dowork
;;
*)
	stopwork
	sleep 0.5
	dowork
;;
esac

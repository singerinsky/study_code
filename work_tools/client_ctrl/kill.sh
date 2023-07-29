#!/bin/bash
###
 # @file: 
 # @copyright: 2012 - 2028 ByteDance. All Rights Reserved
 # @Author: guanlei
 # @Date: 2022-02-15 11:47:16
 # @brief: 作为在运行目录下面检测服务器，关闭服务器的脚本
### 
#

current_execute_dir=`pwd`
process_array=()
USER=`whoami`
ZONELIST='superserver recordserver publicserver loginserver msgserver msdkserver sceneserver gatewayserver'
CROSSLIST='areaserver routeserver crossserver battleserver battleserver publicsocialserver idipserver webproxy'
GROUPLIST='zonegroupserver'
#检测当前目录下启动的服务器进程状态
function check_server_process()
{
    process_id_find=0
    all_process_id_list=`ps -eo user:20,pid:20,cmd:20 | grep ${USER}|grep $1|grep -v grep|awk '{print $2}'`
    OLD_IFS="$IFS"
    IFS=","
    process_array=($all_process_id_list)
    IFS="$OLD_IFS"
    for s in ${process_array[@]}
    do
        process_bin="/proc/"$s"/exe"
        process_bin=`ls ${process_bin} -all`
        result=$(echo $process_bin|grep "${current_execute_dir}")
        if [[ "$result" != "" ]]
        then
            process_id_find=$s
        fi
    done
    if [[ "$process_id_find" == 0 ]]
    then
        echo "Process $1 not running!"
    else
        top -n 1 -p $process_id_find -b|grep $process_id_find|awk '{print $1 " " $12 " " $9 " " $10}'
    fi
}

#检测当前目录下启动的服务器进程状态
function stop_server_process()
{
    process_id_find=0
    all_process_id_list=`ps -eo user:20,pid:20,cmd:20 | grep ${USER}|grep $1|grep -v grep|awk '{print $2}'`
    OLD_IFS="$IFS"
    IFS=","
    process_array=($all_process_id_list)
    IFS="$OLD_IFS"
    for s in ${process_array[@]}
    do
        process_bin="/proc/"$s"/exe"
        process_bin=`ls ${process_bin} -all`
        result=$(echo $process_bin|grep "${current_execute_dir}")
        if [[ "$result" != "" ]]
        then
            process_id_find=$s
        fi
    done
    if [[ "$process_id_find" == 0 ]]
    then
        echo "Process $1 not running!"
    else
        kill -9 $process_id_find
        top -n 1 -p $process_id_find -b|grep $process_id_find|awk '{print $1 " " $12 " " $9 " " $10}'
    fi
}


function format_print()
{
    echo "当前目录运行服务器:"
    echo "进程编号 进程名 CPU MEM"    
}


for serv in $ZONELIST
do
    stop_server_process $serv
done

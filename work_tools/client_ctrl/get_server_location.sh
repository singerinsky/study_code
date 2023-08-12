#!/bin/bash

array_server_ignore=("10.94.26.157" "10.94.26.195")

server_ignore() {
    local target=$1
    shift
    local array=("$@")

    for element in "${array[@]}"
    do
        # 比较元素与目标字符串
        if [ "$element" = "$target" ]; then
            return 0
        fi
    done

    return 1
}


split_string_to_array() {
    local string="$1"  # 传入的字符串
    local total_array_name="$2"  # 总的数组名称
    local append_string="$3"  # 要拼接的字符串

    # 定义数组
    array_name=($string)

    # 使用read命令将字符串通过空格分割并添加到数组中
    #read -ra "$array_name" <<< "$string"
    for element in "${array_name[@]}"
    do
        if [[ -z "$element" ]]; then
            continue
        fi
        server_to_ip[$element]=$append_string
        #eval "${total_array_name}+=(\"${element}#${append_string}\")"
        eval "${total_array_name}+=(\"${element}\")"
        #echo "add"$element
    done
}


#10.94.29.14
#10.253.1.15
# 使用ls命令获取当前目录中包含10的行，保存到数组中
#files=($(ls | grep '10\.94\.29\.'))
files=($(ls | grep '10\.'))
all_server_info=()
declare -A server_to_ip 

# 循环打印数组中的元素
for file in "${files[@]}"
do
    echo "deal with"$file
    if server_ignore "$file" "${array_server_ignore[@]}"; then
        echo "ignore server"$file
    else
        rsync_output=$(ssh $file "ls|grep -E \"opserver[0-9]\" " 2>&1)
        if echo "$rsync_output" | grep -q "denied"; then
            rsync_output=$(ssh game@$file "ls|grep -E \"opserver[0-9]\" " 2>&1)
            if echo "$rsync_output" | grep -q "denied"; then
                echo "can't connect to server"$file
            else
                #echo "IP: "$file
                #echo $rsync_output
                #echo "rsync transfer successful"
                if ! [[ -z "$rsync_output" ]]; then
                    split_string_to_array $rsync_output all_server_info $file
                fi
            fi
        else
            #echo "IP: "$file
            #echo $rsync_output
            if ! [[ -z "$rsync_output" ]]; then
                split_string_to_array $rsync_output all_server_info $file
            fi

            #echo "rsync transfer successful"
        fi

    fi

    #rsync_output=$(rsync -avz get_dir.sh $file: 2>&1)
done


sorted_arr=($(printf "%s\n" "${all_server_info[@]}" | sort -t 'r' -k 1.9n))

# 输出排序结果
for element in "${sorted_arr[@]}"; do
    echo "$element ${server_to_ip[$element]}"
done


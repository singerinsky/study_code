dir=$1
# 使用 find 命令查找目录下所有文件，并按时间排序
file=$(find "$dir" -type f -printf '%T@ %p\n' | sort -n | tail -1 | awk '{print $2}')
# 使用 stat 命令获取文件的详细信息
info=$(stat "$file")
first_line=$(tail -n 1 $file)
echo $first_line|grep -oP '\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2},\d{3}'
#echo $info
# 从信息中提取出修改时间
#time1=$(echo "$info" | awk -F '最近更改：|最近改动：' '{print $2}')
#echo $time1
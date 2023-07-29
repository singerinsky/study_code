package main

import (
    "fmt"
    "regexp"
)

func main() {
    str := "guanlei 10935 3.0 0.1 389760 24068 ? Ssl Apr17 37:31 ./superserver/superserver -d -s 156 -a 1 --config ./config"
    re := regexp.MustCompile("(\d+)\s+-d\s+-s\s+(\d+)") // 创建正则表达式匹配模式
    match := re.FindStringSubmatch(str)                  // 在字符串中查找匹配的内容
    if len(match) == 3 {                                // 提取匹配的数字
        pid := match[1]
        sid := match[2]
        fmt.Println("pid:", pid)
        fmt.Println("sid:", sid)
    }
}

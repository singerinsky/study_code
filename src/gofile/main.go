package main    // 声明 main 包
import (
    "fmt"       // 导入 fmt 包，打印字符串是需要用到
    "os"
    "io"
    "database/sql"
    "github.com/go-sql-driver/mysql"
)

func test_print(){
    point := new(int)
    fmt.Println("test_print")
    *point = 10000
    fmt.Println(*point)
}

func get_map() map[string]string{
    var tmpmap = map[string]string {
        "name":"1",
    }
    return tmpmap
}

func main() {   // 声明 main 主函数
    fmt.Println("Hello World!") // 打印 Hello World!
    f,_:= os.Open("a.txt")
        for {
               buf := make([]byte, 6)
               _, err := f.Read(buf)
               fmt.Println(string(buf))
               if err == io.EOF {
                   break
               }
            }
    var countryCapitalMap map[string]string /*创建集合 */
    countryCapitalMap = make(map[string]string)
    countryCapitalMap["name1"] = "shit"
    fmt.Println(len(countryCapitalMap))
    var tmpmap = get_map()
    fmt.Println(len(tmpmap))
    test_print()
    for i := 0 ;i<10 ;i = i +1{
        fmt.Println(i)
    }
}

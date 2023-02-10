package main    // 声明 main 包
import (
    "fmt"       // 导入 fmt 包，打印字符串是需要用到
    "net"
//    "database/sql"
//    "github.com/go-sql-driver/mysql"
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
    fmt.Println("Start Server!") // 打印 Hello World!

    listener,_:= net.Listen("tcp","127.0.0.1:9898")
    for{
        conn,_:= listener.Accept()
        go process(conn)

    }
}

func process(conn net.Conn){
    defer conn.Close()
    var buf [1024]byte
    for{
        len,_:= conn.Read(buf[:])
        fmt.Printf("recive size:%d",len)
        if len == 0{
            break
        }
        
    }
}

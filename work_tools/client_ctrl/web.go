package main

import (
	"fmt"
	"net/http"
    "os/exec"
    "bytes"
    "regexp"
    "os"
    "strings"
    "html/template"
    "log"
    "database/sql"
    "sort"
    _ "github.com/go-sql-driver/mysql"
    "encoding/json"
)

const (
	host     = "10.94.28.13"
	port     = 3306
	user     = "hhw"
	password = "123456"
	dbname   = "op_"
)

func get_all_account_can_use(server_id string)[]string{
    //fmt.Println("do get account!")
    var all_account []string
	connString := fmt.Sprintf("%s:%s@tcp(%s:%d)/%s?parseTime=true", user, password, host, port, dbname+server_id)
	db, err := sql.Open("mysql", connString)
	if err != nil {
		fmt.Println(err.Error())
		return all_account
	}
    defer db.Close()
    	// 查询数据库
	rows, err := db.Query("SELECT ACCOUNT FROM User WHERE offlinetime IN (SELECT offlinetime  FROM User GROUP BY offlinetime HAVING COUNT(*) > 10)")
	if err != nil {
		fmt.Println(err.Error())
		return all_account
	}
	defer rows.Close()


	// 处理查询结果
	for rows.Next() {
        //fmt.Println("process sql!")
		var account string
		if err := rows.Scan(&account); err != nil {
			log.Println(err.Error())
			continue
		}
        all_account = append(all_account,account)
		//fmt.Printf("name: %s \n", account)
	}
	if err := rows.Err(); err != nil {
		log.Println(err.Error())
		return all_account
	}
    return all_account
}


type ServerPageData struct  {
    Serverlist []ServerInfo
}

type ServerInfo struct {
    Sid string
    Pid string
    Path string
    ServerID string
    CurrentTime string
    BranchName string
    Status int  //0:running ,1:restarting
    PidBeforeRestart     string  //
    AccountList     []string
}



var GServer_info map[string]ServerInfo = make(map[string]ServerInfo)

func getserver_path(pid string)string{
    //fmt.Println("pid"+pid)
    cmd := exec.Command("sh","-c","pwdx "+pid)
    var out bytes.Buffer
    cmd.Stdout  = &out
    cmd.Stderr = os.Stderr
    err := cmd.Start()

    if err != nil {
        fmt.Print("error")
        return ""
    }
    err = cmd.Wait()
    if err != nil {
        fmt.Print("error")
        return ""
    }
    re := regexp.MustCompile(`\d+: (.*)`)
    match := re.FindStringSubmatch(out.String())
    if len(match) > 1 {
        //fmt.Println(match[1])
        return match[1]
    }
    return ""
}

func get_server_ip_address()string{
    cmd := exec.Command("sh","-c","hostname -I")
    var out bytes.Buffer
    cmd.Stdout  = &out
    cmd.Stderr = os.Stderr
    err := cmd.Start()
    if err != nil {
        fmt.Print("error")
        return ""
    }
    err = cmd.Wait()
    if err != nil {
        fmt.Print("error")
        return ""
    }
    return out.String()
}

func getallserver()[]ServerInfo{
    cmd := exec.Command("sh","-c","ps aux|grep superserver")
    var out bytes.Buffer
    var allserver []string
    cmd.Stdout  = &out
    cmd.Stderr = os.Stderr
    err := cmd.Start()

    if err != nil {
        fmt.Print("error")
        var vecServerInfo []ServerInfo
        for _, v:= range GServer_info {
            vecServerInfo = append(vecServerInfo,v)
        }
    
        return vecServerInfo
    }
    err = cmd.Wait()
    for _,line := range strings.Split(out.String(),"\n"){
        //re := regexp.MustCompile(`\d+`) // 创建正则表达式匹配模式
        re := regexp.MustCompile(`\d+`) // 创建正则表达式匹配模式

        match := re.FindAllString(line,-1)    // 在字符串中查找匹配的内容
        if len(match) > 10 && !strings.Contains(line,"grep") {                  // 提取匹配的数字
            pid := match[0]
            //fmt.Println(pid)
            sid := "0"
            sidre := regexp.MustCompile(`-s\s+(\d+)`)

            if sidmatch := sidre.FindStringSubmatch(line); len(sidmatch) > 1 {
                //fmt.Println("The number is:", match[1])
                sid = sidmatch[1]
            }
            path := getserver_path(pid)
            log.Println("The path is:", path)
            allserver=append(allserver,sid)
            now_time := get_current_process_time(path)
            //fmt.Println("now_time is:", now_time)
            server_info := ServerInfo{
                Sid :sid,
                Pid :pid,
                Path :path,
                ServerID:sid,
                CurrentTime:now_time,
            }
            server_info.BranchName = get_branch_name(path)
            fmt.Println("path is:"+ server_info.Path)
            server_info.AccountList = get_all_account_can_use(sid)
            
            GServer_info[sid] = server_info
        }
    }

    var vecServerInfo []ServerInfo
    for _, v:= range GServer_info {
        vecServerInfo = append(vecServerInfo,v)
    }

    return vecServerInfo
}

func get_branch_name(path string) string{

    cmd := exec.Command("/bin/sh","/home/guanlei/workspace/client_ctrl/get_branch_name.sh",path)   
    out, err := cmd.Output()
    if err != nil {
        fmt.Println(err.Error())
        return ""
    }
    //fmt.Println(string(out))
    return string(out)    
}


func get_current_process_time(path string)string{

    cmd := exec.Command("/bin/sh","/home/guanlei/workspace/client_ctrl/get_time.sh",path+"/logs/sceneserver")   
    out, err := cmd.Output()
    if err != nil {
        fmt.Println(err.Error())
    }
    //fmt.Println(string(out))
    //parts := string(out)
    parts := strings.Split(string(out), "+")
    return parts[0]
}


func helloWorld(w http.ResponseWriter, r *http.Request) {
    GServer_info = make(map[string]ServerInfo)
    allserver:=getallserver()

    sort.Slice(allserver,func(a,b int)bool{
        return allserver[a].Sid < allserver[b].Sid
    })

    tpl,_ := template.ParseFiles("index.html")
    data := ServerPageData{
        Serverlist: allserver,//[]string{"111","222"},
    }
    tpl.Execute(w,data)
    //fmt.Println("server info %v",GServer_info)
}


type Response struct {
    Message string `json:"message"`
}

func reboot(w http.ResponseWriter, r *http.Request) {
    paramValue := r.FormValue("serverid")
    starttime := r.FormValue("starttime")
    log.Println("start reboot")
    path:=GServer_info[paramValue].Path
    fmt.Println("restart server in path:"+path+":"+paramValue+":"+starttime)
    cmd := exec.Command("/bin/sh","/home/guanlei/workspace/client_ctrl/restart.sh",path,paramValue,starttime)
    fmt.Println(1)
    //cmd.Start()

    //fmt.Println(2)
    err := cmd.Wait()
    fmt.Println(2)
    //cmd := exec.Command("./restart.sh",path)
    //fmt.Println(3)
    output, err := cmd.Output()
    fmt.Println(3)
    if err != nil {
        log.Println(err)
        log.Println(output)
        log.Println("end reboot")
        fmt.Println(4)
        return
    }
    fmt.Println(5)
    log.Println("end reboot")
    w.Header().Set("Content-Type", "application/json")
    response := Response{Message: fmt.Sprintf("1")}  
    jsonResponse, err := json.Marshal(response)      
    w.Write(jsonResponse)
}

func new_reboot(w http.ResponseWriter, r *http.Request) {
    paramValue := r.FormValue("serverid")
    //fmt.Println("restart server in path:"+GServer_info[paramValue].Path)
    path:=GServer_info[paramValue].Path
    cmd := exec.Command("/bin/sh","/home/guanlei/workspace/client_ctrl/new_restart.sh",path)
    //fmt.Println(1)
    cmd.Start()

    //fmt.Println(2)
    err := cmd.Wait()
    //cmd := exec.Command("./restart.sh",path)
    //fmt.Println(3)
    output, err := cmd.Output()
    if err != nil {
        fmt.Println(4)
        fmt.Println(err)
        fmt.Println(output)
        return
    }
    //fmt.Println(string(output))
}


func luacheck(w http.ResponseWriter, r *http.Request) {
    GServer_info = make(map[string]ServerInfo)
    allserver:=getallserver()

    sort.Slice(allserver,func(a,b int)bool{
        return allserver[a].Sid < allserver[b].Sid
    })

    tpl,_ := template.ParseFiles("luacheck.html")
    data := ServerPageData{
        Serverlist: allserver,//[]string{"111","222"},
    }
    tpl.Execute(w,data)
    //fmt.Println("server info %v",GServer_info)
}


func luacheck_master(w http.ResponseWriter, r *http.Request) {
    GServer_info = make(map[string]ServerInfo)
    allserver:=getallserver()

    sort.Slice(allserver,func(a,b int)bool{
        return allserver[a].Sid < allserver[b].Sid
    })

    tpl,_ := template.ParseFiles("master_html.html")
    data := ServerPageData{
        Serverlist: allserver,//[]string{"111","222"},
    }
    tpl.Execute(w,data)
    //fmt.Println("server info %v",GServer_info)
}

func luacheck_bugfix(w http.ResponseWriter, r *http.Request) {
    GServer_info = make(map[string]ServerInfo)
    allserver:=getallserver()

    sort.Slice(allserver,func(a,b int)bool{
        return allserver[a].Sid < allserver[b].Sid
    })

    tpl,_ := template.ParseFiles("bugfix_html.html")
    data := ServerPageData{
        Serverlist: allserver,//[]string{"111","222"},
    }
    tpl.Execute(w,data)
    //fmt.Println("server info %v",GServer_info)
}

func luacheck_mirror(w http.ResponseWriter, r *http.Request) {
    GServer_info = make(map[string]ServerInfo)
    allserver:=getallserver()

    sort.Slice(allserver,func(a,b int)bool{
        return allserver[a].Sid < allserver[b].Sid
    })

    tpl,_ := template.ParseFiles("mirror_html.html")
    data := ServerPageData{
        Serverlist: allserver,//[]string{"111","222"},
    }
    tpl.Execute(w,data)
    //fmt.Println("server info %v",GServer_info)
}

func luacheck_0531(w http.ResponseWriter, r *http.Request) {
    GServer_info = make(map[string]ServerInfo)
    allserver:=getallserver()

    sort.Slice(allserver,func(a,b int)bool{
        return allserver[a].Sid < allserver[b].Sid
    })

    tpl,_ := template.ParseFiles("0531_html.html")
    data := ServerPageData{
        Serverlist: allserver,//[]string{"111","222"},
    }
    tpl.Execute(w,data)
    //fmt.Println("server info %v",GServer_info)
}



func main() {
    file, err := os.OpenFile("logs.txt", os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0666)
    if err != nil {
        log.Fatal(err)
    }

    log.SetOutput(file)

    log.Println("Content from log package!")

	http.HandleFunc("/", helloWorld)
	http.HandleFunc("/reboot", reboot)
	http.HandleFunc("/get_new_reboot", new_reboot)
    http.HandleFunc("/checklua",luacheck)
    http.HandleFunc("/checklua_0531",luacheck_0531)
    http.HandleFunc("/checklua_bugfix",luacheck_bugfix)
    http.HandleFunc("/checklua_mirror",luacheck_mirror)
    http.HandleFunc("/checklua_master",luacheck_master)
	fmt.Println("Server started at http://localhost:8080\n")
	http.ListenAndServe("0.0.0.0:8081", nil)
}

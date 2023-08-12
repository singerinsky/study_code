#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <string>
#include <mysql.h>
#include "mysql++.h"

class stConnectionInfo
{
public:
    std::string m_strHost;
    uint32_t m_dwPort;
    std::string m_strUser;
    std::string m_strPassword;
    std::string m_strDBName;
    stConnectionInfo() {}
    stConnectionInfo(const char* host, uint32_t port, const char* user,
                     const char* password, const char* dbname)
        : m_strHost(host), m_dwPort(port), m_strUser(user)
        , m_strPassword(password), m_strDBName(dbname)
    {
        m_dwPort = 0;
    }
};

mysqlpp::Connection conn(false);

bool DoMySQLConnection(const stConnectionInfo& info)
{
    if (conn.connect(info.m_strDBName.c_str(),
                     info.m_strHost.c_str(),
                     info.m_strUser.c_str(),
                     info.m_strPassword.c_str()))
    {
        // 创建一个查询对象
        mysqlpp::Query query = conn.query();

        // 执行查询
        mysqlpp::StoreQueryResult result = query.store("SELECT * FROM User limit 1");

        // 遍历查询结果
        if (result)
        {
            // mysqlpp::StoreQueryResult::const_iterator it;
            // for (it = result.begin(); it != result.end(); ++it)
            // {
            //     std::cout << it->at(0).c_str();
            // }
        }
        else
        {
            std::cout << "Query failed: " << query.error() << std::endl;
        }
        return true;
    }
    else
    {
        std::cout << "Connection failed: " << conn.error() << std::endl;
        return false;
    }
}

std::string GetTableDescription(const std::string& strTableName)
{
    mysqlpp::Query query = conn.query("DESCRIBE " + strTableName);
    mysqlpp::StoreQueryResult result = query.store();
    if (result)
    {
        std::cout << result[0][0].c_str();
    }
    return {result[0][0].c_str()};
}

int main(int argc, char** argv)
{
    stConnectionInfo stInfo =
    {"localhost", 3306, "hhw", "123456", "op_157"};
    bool bConnect = DoMySQLConnection(stInfo);
    if (bConnect == false)
    {
        printf("connection failed!\n");
    }
    else
    {
        printf("connection success!\n");
    }
    GetTableDescription("User");
    return 0;
}
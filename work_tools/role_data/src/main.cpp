#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <string>
#include <mysql.h>
#include "mysql++.h"

class stConnectionInfo
{
    std::string m_strHost;
    uint32_t m_dwPort;
    std::string m_strUser;
    std::string m_strPassword;
    std::string m_strDBName;
    stConnectionInfo()
    {
        m_dwPort = 0;
    }
};

void DoMySQLConnection()
{
    mysqlpp::Connection conn(false);
    if (conn.connect("op_157", "localhost", "hhw", "123456"))
    {
        // 创建一个查询对象
        mysqlpp::Query query = conn.query();

        // 执行查询
        mysqlpp::StoreQueryResult result = query.store("SELECT * FROM User");

        // 遍历查询结果
        if (result)
        {
            mysqlpp::StoreQueryResult::const_iterator it;
            for (it = result.begin(); it != result.end(); ++it)
            {
                std::cout << it->at(0).c_str();
            }
        }
        else
        {
            std::cout << "Query failed: " << query.error() << std::endl;
        }
    }
    else
    {
        std::cout << "Connection failed: " << conn.error() << std::endl;
    }
}

int main(int argc, char** argv)
{
    DoMySQLConnection();
    return 0;
}
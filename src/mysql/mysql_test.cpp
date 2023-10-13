#include "../header.h"
#include "mysql/mysql.h"

TEST(MysqlTest, test001) {
  MYSQL *mysql;

  MYSQL_RES *results;

  MYSQL_ROW record;
  // 初始化MySQL连接
  mysql = mysql_init(NULL);
  if (mysql == NULL) {
    fprintf(stderr, "无法初始化MySQL连接\n");
    return;
  }

  // 连接到MySQL服务器
  if (mysql_real_connect(mysql, "10.94.28.13", "hhw", "123456", "op_157", 3306,
                         NULL, 0) == NULL) {
    LOG(INFO) << "无法连接到MySQL服务器" << mysql_error(mysql);
    mysql_close(mysql);
  }

  if (mysql_query(mysql, "select * from User limit 1")) {
    LOG(INFO) << "do query failed!" << mysql_error(mysql);
    mysql_close(mysql);
  }
  LOG(INFO) << "test mysql";
}
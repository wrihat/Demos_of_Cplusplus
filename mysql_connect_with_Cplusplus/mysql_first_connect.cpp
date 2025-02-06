#include <mysql/mysql.h>
#include <iostream>
using namespace std;
int main() {
    MYSQL * conn;
    MYSQL_RES* res;
    MYSQL_ROW row;
    //初始化mysql连接
    conn = mysql_init(NULL);
    if(conn == NULL) {
        cerr<<"mysql_init() failed.\n";
        return EXIT_FAILURE;
    }
    //连接到MySQL数据库
    if(mysql_real_connect(conn, "127.0.0.1", "user", "your_password", NULL, 3306, NULL, 0) == NULL) {
        cerr<<"mysql_real_connect() failed: "<<mysql_error(conn)<<endl;
        return EXIT_FAILURE;
    }
    // 执行查询来获取所有数据库名称
    if(mysql_query(conn, "SHOW DATABASES")) {
        cerr<<"SHOW DATABASES query failed: "<<mysql_error(conn)<<endl;
        mysql_close(conn);
        return EXIT_FAILURE;
    }
    // 对查询的结果进行保存
    res = mysql_store_result(conn);
    cout<<"Databses: "<<endl;
    while((row = mysql_fetch_row(res)) != NULL) {
        cout<<row[0]<<endl;
    }
    mysql_free_result(res);
    mysql_close(conn);

    return EXIT_SUCCESS;
}


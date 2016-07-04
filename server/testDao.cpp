#include<iostream>
#include<stdio.h>
#include<string.h>

#include "mysql/mysql.h"


using namespace std;


int main()

{

  const char *host = "localhost";

  const char *user = "root";

  const char *pass = "123456";

  const char *db   = "lcy";

  MYSQL mysql;

  mysql_init(&mysql);


  if (!mysql_real_connect(&mysql, host, user, pass, db, 0, NULL, 0)) {

    printf("%s", mysql_error(&mysql));

  }

  else {

    printf("YES, Conected succeed!");
    string sql="insert into user(id,pw) values(3,'123');";
    mysql_query(&mysql,sql.c_str());
    
    

  }

  mysql_close(&mysql);

  return 0;

}


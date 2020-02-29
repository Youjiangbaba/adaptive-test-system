#include "sql.h"

int sql_test(void)
{
    QSqlDatabase db=QSqlDatabase::contains("qt_sql_default_connection")?QSqlDatabase::database("qt_sql_default_connection"):QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery query(db);
    db.setDatabaseName("mydb.db");
    db.setUserName("admin");
    db.setPassword("admin");
    if(db.open("admin","admin")){
        query.exec("create table man(id int primary key,name varchar(20))");
        //insert
        query.prepare("insert into man values(?,?)");
        query.bindValue(0,0);
        query.bindValue(1,"Bob");
        if(query.exec()){
            query.prepare("insert into man values(:id,:name)");
            query.bindValue(":id",1);
            query.bindValue(":name","Tom");
            if(query.exec()){
                //select
                if(query.exec("select * from man")){
                    while(query.next()){
                        qDebug()<<QString("id:%1    name:%2").arg(query.value(0).toString()).arg(query.value(1).toString());
                    }
                }
            }
        }
        db.close();
    }
    else{
        qDebug()<<"Error:"<<db.lastError();
    }
    return 0;
}

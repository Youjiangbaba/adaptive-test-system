#include "mainwindow.h"
#include <QApplication>
#include "sql.h"
#include <QThread>
#include "adaptive_questin.h"
SQL_DEAL sql;

#define GET_QUESTIONS_DATA 0//得到题库的参数，1开启！0不开启。只需要开启一次，自己可删除usr_manage.db再执行一遍
QSqlDatabase StudentDatabase;

int main(int argc, char *argv[])
{

    #if GET_QUESTIONS_DATA
        StudentDatabase = sql.create_db();
        StudentDatabase = sql.open_db(StudentDatabase,USRMANAGE,"","");
        StudentDatabase = sql.questions_table(StudentDatabase);
        sql.close_db(StudentDatabase);
    #endif

    //打开数据库，包括一个管理用户登录的表格和若干个学生答题记录的表格 ,以及已经创建的问题表；这里创建登录管理表格（有则不创建）
    StudentDatabase = sql.create_db();
    StudentDatabase = sql.open_db(StudentDatabase,USRMANAGE,"","");
    StudentDatabase = sql.usrmanage_table(StudentDatabase);
    sql.read_usrspwds(StudentDatabase);


////    int scores[] = {90,50,60};
////    adaptive_questin(scores);


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

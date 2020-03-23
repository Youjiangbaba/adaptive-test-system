#ifndef SQL_H
#define SQL_H
#include <QCoreApplication>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>
#include <QMessageBox>
#include <vector>

const QString USRMANAGE = "usr_manage.db";
const QString USRMANAGE_TABLE = "usr_manage";
extern QSqlDatabase StudentDatabase;

extern QList<QString> usrs,pwds;
extern QString this_usrname;

extern QList<QString> question,re_a,re_b,re_c,re_d;
extern std::vector<int> re_right,classes;

extern std::vector<int> out_question_num;

extern QString int2qstr(int _int);
extern int qstr2int(QString qstr);


class SQL_DEAL
{
public:
    QSqlDatabase open_db(QSqlDatabase sqliteDatabase,QString databaseName,QString usr="",QString pwd="");
    void close_db(QSqlDatabase sqliteDatabase);
    QSqlDatabase create_db();

    QSqlDatabase questions_table(QSqlDatabase db);

    QSqlDatabase student_table(QSqlDatabase db,QString student_name);
    QSqlDatabase WriteStudent_table(QSqlDatabase db,QString student_name,int *score);
    void read_questions(QSqlDatabase db,std::vector<int> nums);

    QSqlDatabase usrmanage_table(QSqlDatabase db,QString student_name=USRMANAGE_TABLE);
    void read_usrspwds(QSqlDatabase db);
    QSqlDatabase Write_usrmanage(QSqlDatabase db,QString usr,QString pwd);


private:

};

extern SQL_DEAL sql;


#endif // SQL_H

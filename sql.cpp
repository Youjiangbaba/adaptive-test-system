#include "sql.h"
#include <QDateTime>

#include <QList>
/*
 * 安装可视化工具
 * sudo apt-get install sqlite3 sqlitebrowser
 * sqlitebrowser #open
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

QList<QString> usrs,pwds;//读取并存放用户名、密码

QList<QString> question,re_a,re_b,re_c,re_d;
std::vector<int> re_right,classes;

QString str2qstr(string str){
    return QString::fromStdString(str);
}

QString qstr2sqlstr(QString classes_str){
    classes_str = classes_str.prepend("\"");//在字符串开头位置插入字符串
    classes_str.append("\"");
    return classes_str;
}

QString int2qstr(int _int){
    return QString::number(_int);
}

int qstr2int(QString qstr){
    return qstr.toInt();
}

QSqlDatabase SQL_DEAL::create_db()
{
     QSqlDatabase sqliteDatabase;
     sqliteDatabase=QSqlDatabase::contains("qt_sql_default_connection")\
        ?QSqlDatabase::database("qt_sql_default_connection"):QSqlDatabase::addDatabase("QSQLITE");
     return sqliteDatabase;
}


QSqlDatabase SQL_DEAL::open_db(QSqlDatabase sqliteDatabase,QString databaseName,QString usr,QString pwd)
{
    sqliteDatabase.setDatabaseName(databaseName);
    sqliteDatabase.setUserName(usr);
    sqliteDatabase.setPassword(pwd);
    //检查数据库是否关闭
    bool isOpen         = sqliteDatabase.isOpen();
    //若已经打开数据库
    if (true            == isOpen){
        qDebug() << "数据库已经打开!";
    }
    else{
        //数据库没有打开
        bool openFlag = sqliteDatabase.open(usr,pwd);
        if (false               == openFlag){
            qDebug() << "数据库打开失败!";
        }
        else {
            qDebug() << "数据库文件打开成功!"<<databaseName;
        }
    }
    return sqliteDatabase;
}


QSqlDatabase SQL_DEAL::student_table(QSqlDatabase db,QString student_name)
{
    QSqlQuery query(db);
    QString student_table = "create table student_";
    student_table = student_table.append(student_name);
    student_table = student_table.append(" (id int primary key,data varchar(50), socres int, "
                     "class1 int,class2 int,class3 int)");
    qDebug() << student_table;
    //执行SQL语句; 如果成功则返回true，否则false 已经创建好表名后再创建会报错
    if(!query.exec(student_table)){
        qDebug() << "Error: Fail to create table." << query.lastError();
    }
    else{
        qDebug() << "Table created!";
    }
    return    db;
}

QSqlDatabase SQL_DEAL::usrmanage_table(QSqlDatabase db,QString student_name)
{
    QSqlQuery query(db);
    QString student_table = "create table ";
    student_table = student_table.append(student_name);
    student_table = student_table.append(" (id int primary key,usr varchar(10), pwd varchar(10))");
    qDebug() << student_table;
    //执行SQL语句; 如果成功则返回true，否则false 已经创建好表名后再创建会报错
    if(!query.exec(student_table)){
        qDebug() << "Error: Fail to create table." << query.lastError();
    }
    else{
        qDebug() << "Table created!";
    }
    return    db;
}

//读取并存放用户名、密码
void SQL_DEAL::read_usrspwds(QSqlDatabase db)
{
    QSqlQuery sql_query(db);
    //查询数据
    int id = 0;
    QString usr,pwd;
    QString find_cmd = "select * from ";
    find_cmd.append(USRMANAGE_TABLE);
    sql_query.exec(find_cmd);
    if(!sql_query.exec()){
        qDebug()<<sql_query.lastError();
    }
    else{
        while(sql_query.next()){
            id = sql_query.value(0).toInt();
            usr = sql_query.value(1).toString();
            pwd = sql_query.value(2).toString();
            usrs.append(usr);
            pwds.append(pwd);
        }
    }
    qDebug() << usrs<<pwds;
}

//读取需要的题！输入 序号15个；输出 这次的考卷 QLIST
void SQL_DEAL::read_questions(QSqlDatabase db,std::vector<int> nums)
{
    QSqlQuery sql_query(db);
    //查询数据
    int id = 0;
    QString usr,pwd;
    QString find_cmd = "select * from ";
    find_cmd.append("questions");
    sql_query.exec(find_cmd);
    if(!sql_query.exec()){
        qDebug()<<sql_query.lastError();
    }
    else{
        int count_start = 0;

        while(sql_query.next()){
            id = sql_query.value(0).toInt();

            for (int count = count_start;count < nums.size();count ++){
                if (id == nums[count]){
                    classes.push_back(sql_query.value(1).toInt());
                    question.push_back(sql_query.value(2).toString());
                    re_a.push_back(sql_query.value(3).toString());
                    re_b.push_back(sql_query.value(4).toString());
                    re_c.push_back(sql_query.value(5).toString());
                    re_d.push_back(sql_query.value(6).toString());
                    re_right.push_back(sql_query.value(7).toInt());
                    count_start ++;
                }
            }


        }

    }
}

QSqlDatabase SQL_DEAL::Write_usrmanage(QSqlDatabase db,QString usr,QString pwd)
{
    QSqlQuery sql_query(db);
    //查询数据
    int id = 0;
    QString find_cmd = "select * from ";
    find_cmd.append(USRMANAGE_TABLE);
    sql_query.exec(find_cmd);
    if(!sql_query.exec()){
        qDebug()<<sql_query.lastError();
    }
    else{
        while(sql_query.next()){
            id = sql_query.value(0).toInt();
            qDebug()<<QString("id:%1").arg(id);
        }
    }

    //插入数据
    QString indata;
    QString header = "INSERT INTO "; //= "INSERT INTO student VALUES(ID,\"usr\",\"pwd\")";
    header.append(USRMANAGE_TABLE);
    header.append(" VALUES(");
    indata = header.append(int2qstr(id+1));
    indata.append(",");
    indata.append(qstr2sqlstr(usr));
    indata.append(",");
    indata.append(qstr2sqlstr(pwd));
    indata.append(")");

    qDebug() <<indata;

    if(!sql_query.exec(indata)){
        qDebug() << sql_query.lastError();
    }
    else{
          qDebug() << "inserted ok!";
      }

    return db;
}

// score  : score,c1,c2,c3
QSqlDatabase SQL_DEAL::WriteStudent_table(QSqlDatabase db,QString student_name,int *score)
{
    QSqlQuery sql_query(db);
    //查询数据
    int id = 0;
    QString find_cmd = "select * from ";
    find_cmd.append(student_name);
    sql_query.exec(find_cmd);
    if(!sql_query.exec()){
        qDebug()<<sql_query.lastError();
    }
    else{
        while(sql_query.next()){
            id = sql_query.value(0).toInt();
            qDebug()<<QString("id:%1").arg(id);
        }
    }

    //插入数据
    QDateTime time = QDateTime::currentDateTime();
    QString str_time = time.toString("yyyy-MM-dd hh:mm:ss dddd");

    QString indata;
    QString header = "INSERT INTO "; //= "INSERT INTO student VALUES(\"time\",90,80,100,80,100)";
    header.append(student_name);
    header.append(" VALUES(");
    indata = header.append(int2qstr(id+1));
    indata.append(",");
    indata.append(qstr2sqlstr(str_time));
    indata.append(",");
    indata.append(int2qstr(score[0]));
    indata.append(",");
    indata.append(int2qstr(score[1]));
    indata.append(",");
    indata.append(int2qstr(score[2]));
    indata.append(",");
    indata.append(int2qstr(score[3]));
    indata.append(")");

    qDebug() <<indata;

    if(!sql_query.exec(indata)){
        qDebug() << sql_query.lastError();
    }
    else{
          qDebug() << "inserted ok!";
      }

    return db;
}


//这个函数把外部txt文件的题库读进数据库；外部txt格式见questions.txt
QSqlDatabase SQL_DEAL::questions_table(QSqlDatabase db)
{
    qDebug() << db.isOpen();
    QSqlQuery query(db);
    //SQL操作语句create table 表名 (标题头内容)  questions
    QString questions_table = "create table questions (id int primary key,classes int, question varchar(100), "
                              "A varchar(30),B varchar(30),C varchar(30),D varchar(30),right int)";

    //执行SQL语句; 如果成功则返回true，否则false 已经创建好表名后再创建会报错
    if(!query.exec(questions_table)){
        qDebug() << "Error: Fail to create table." << query.lastError();
    }
    else{
        qDebug() << "Table created!";
    }


    //插入数据
    string file = "../questions.txt";
    ifstream infile;
    infile.open(file.data());   //将文件流对象与文件连接起来
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行
    QString line_data;
    string s;

    QString header,id_str,classes_str,questions_,A_,B_,C_,D_,right_str;
    int _id = 0;
    int _classes = 0;
    int _right = 0;

    while(getline(infile,s))
    {
        line_data = str2qstr(s);
        QList<QString>  lst;
        /*
            格式：类别 问题 选项A 选项B 选项C 选项D 答案
            如：
            2 问题 A.qwer B.萨达大多 C.对的 D.WODS 1
         */
        lst = line_data.split(' ');
        classes_str = lst[0];
        questions_ = lst[1];
        A_ = lst[2];
        B_ = lst[3];
        C_ = lst[4];
        D_ = lst[5];
        right_str = lst[6];

        header = "INSERT INTO questions VALUES(";
        id_str = int2qstr(_id);
        questions_ = qstr2sqlstr(questions_);
        A_ = qstr2sqlstr(A_);
        B_ = qstr2sqlstr(B_);
        C_ = qstr2sqlstr(C_);
        D_ = qstr2sqlstr(D_);




        QString indata; //= "INSERT INTO questions VALUES(1,1,\"1+1=?\",\"111\", \"222\",\"333\",\"444\",2)";
        indata = header.append(id_str);
        indata.append(",");
        indata = indata.append(classes_str);
        indata.append(",");
        indata = indata.append(questions_);
        indata.append(",");
        indata = indata.append(A_);
        indata.append(",");
        indata = indata.append(B_);
        indata.append(",");
        indata = indata.append(C_);
        indata.append(",");
        indata = indata.append(D_);
        indata.append(",");
        indata = indata.append(right_str);
        indata.append(")");

         qDebug() <<indata;

        if(!query.exec(indata)){
            qDebug() << query.lastError();
        }
        else{
              qDebug() << "inserted ok!";
          }

        _id ++;
    }
    infile.close();             //关闭文件输入流

    return db;
}


void SQL_DEAL::close_db(QSqlDatabase sqliteDatabase)
{
    //检查数据库是否关闭
    bool isOpen         = sqliteDatabase.isOpen();
    //若已经打开数据库
    if (true            == isOpen){
        //关闭数据库
        sqliteDatabase.close();
        qDebug() << "数据库打开了, 关闭";
    }
    else{
        // 1.1.2 数据库没有打开
        qDebug() << "数据库没有打开, 什么也不做";
    }
}


////删除数据
//QString delete_cmd;
//QString delete_header = "delete from questions where id = ";
//int delete_id = 4;
//delete_cmd = delete_header.append(int2qstr(delete_id));
//qDebug() << delete_cmd ;
//if(!query.exec(delete_cmd))
//{
//    qDebug()<<query.lastError();
//}
//else
//{
//    qDebug()<<"deleted!";
//}

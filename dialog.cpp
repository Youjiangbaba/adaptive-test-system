#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <iostream>

#include "sql.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_rcancer_clicked()
{
    std::cout << "cancer" <<std::endl;
    this->reject();
}

void Dialog::on_rok_clicked()
{

    std::cout << "ok" <<std::endl;
    QString input_usr =  ui->rusrtext->text();
    QString input_pwd1 =  ui->rpwdtext1->text();
    QString input_pwd2 =  ui->rpwdtext2->text();
    if(input_usr == NULL){
        QMessageBox::critical(0 , "critical message" , "没有输入用户名！", QMessageBox::Ok );
    }
    else{
        if (usrs.indexOf(input_usr) != -1) {
            QMessageBox::critical(0 , "critical message" , "用户名已存在！", QMessageBox::Ok );
        }
        else {
            if (input_pwd1 == input_pwd2){
                //两次密码正确可以进行保存
                //更新数据库
                StudentDatabase = sql.Write_usrmanage(StudentDatabase,input_usr,input_pwd1);
                sql.read_usrspwds(StudentDatabase);
                QMessageBox::information(0 , "information message" , "注册成功！", QMessageBox::Ok );
                this->reject();
            }
            else {
                    QMessageBox::critical(0 , "critical message" , "两次密码不正确！", QMessageBox::Ok );
            }
        }
    }

}

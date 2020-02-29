#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <iostream>
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
    if(ui->rusrtext->text() == NULL){
        QMessageBox::critical(0 , "critical message" , "没有输入用户名！", QMessageBox::Ok );
        //this->reject();
    }
    else {
        //    for (int var = 0; var < total; ++var) {
        //        if(ui->rusrtext->text() == names[var]){
        //            QMessageBox::critical(0 , "critical message" , "用户名已存在！", QMessageBox::Ok );
        //        }
        //    }

        //
        if (ui->rpwdtext1->text() == ui->rpwdtext2->text()){
            //两次密码正确可以进行保存
            this->reject();
        }
        else {
                    QMessageBox::critical(0 , "critical message" , "两次密码不正确！", QMessageBox::Ok );
        }
    }






}

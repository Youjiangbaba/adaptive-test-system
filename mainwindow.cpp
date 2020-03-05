#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include "sql.h"

QString this_usrname = "xx";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_registerPB_clicked()
{
    dialog = new Dialog(this);
    //dialog->setModal(false);
//    /*
//     * 模态对话框（Modal Dialog）与非模态对话框（Modeless Dialog）的概念不是Qt所独有的，在各种不同的平台下都存在。
//     * 又有叫法是称为模式对话框，无模式对话框等。
//     * 所谓模态对话框就是在其没有被关闭之前，用户不能与同一个应用程序的其他窗口进行交互，直到该对话框关闭。
//     * 对于非模态对话框，当被打开时，用户既可选择和该对话框进行交互，也可以选择同应用程序的其他窗口交互。
//    */
    dialog->show();
}

void MainWindow::on_login_clicked()
{
    int index = usrs.indexOf(ui->lusrtext->text());
    if (index == -1){
        QMessageBox::critical(NULL, "critical message" , "用户名不存在！", QMessageBox::Ok );
    }
    else {
        if (ui->lpwdtext->text() == pwds[index]){
            this_usrname = ui->lusrtext->text();

            //创建该用户的表格
            StudentDatabase = sql.student_table(StudentDatabase,this_usrname);

            mm = new MainForm();
            mm ->show();
            this->close();
            delete ui;
        }
        else {
            QMessageBox::critical(NULL, "critical message" , "密码错误，请重新输入！", QMessageBox::Ok );
        }
    }
}

void MainWindow::on_quit_clicked()
{
    this->close();
    delete ui;
}

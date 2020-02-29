#include "mainwindow.h"
#include "ui_mainwindow.h"



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
//    if ((ui->lusrtext->text() == "123")&&(ui->lpwdtext->text() == "123")){
        mm = new MainForm();
        mm ->show();
        this->close();
        delete ui;
//    }
}

void MainWindow::on_quit_clicked()
{
    this->close();
    delete ui;
}

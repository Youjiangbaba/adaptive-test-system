#include "mainform.h"
#include "ui_mainform.h"
#include<QDateTime>
#include <QTimer>
#include <QString>

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    time_t = new QTimer();
    time_t->start(1000);
    connect(time_t,SIGNAL(timeout()),this,SLOT(updateTime()));

}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_startanswerpd_clicked()
{
    maindialog = new MainDialog(this);
    //dialog->setModal(false);
//    /*
//     * 模态对话框（Modal Dialog）与非模态对话框（Modeless Dialog）的概念不是Qt所独有的，在各种不同的平台下都存在。
//     * 又有叫法是称为模式对话框，无模式对话框等。
//     * 所谓模态对话框就是在其没有被关闭之前，用户不能与同一个应用程序的其他窗口进行交互，直到该对话框关闭。
//     * 对于非模态对话框，当被打开时，用户既可选择和该对话框进行交互，也可以选择同应用程序的其他窗口交互。
//    */
    maindialog->show();
}


void MainForm::updateTime()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");

    QString name_str = "某某 ";
    QString show_header = QString("%1 ,欢迎您！现在是北京时间： %2")
                    .arg(name_str).arg(str);
    ui->label->setText(show_header);
}

void MainForm::on_quitsyspd_clicked()
{
    time_t->stop();
    this ->close();
    delete ui;
}

#include "maindialog.h"
#include "ui_maindialog.h"
#include<iostream>
#include <QTimer>
#include <QString>
#include <QMessageBox>
#include<QThread>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    //LOCATION 题目题干、四个选项的位置
    int radio_w = 40,radio_h = 25;
    int text_w = 600, text_h = 50;
    int A_h = 180, add_h = 65;
    int x_radio = 30;
    int x_text = 70;
    ui->textquestion->setGeometry(20,100,700,70);
    ui->radioButton_A->setGeometry(x_radio,A_h,radio_w,radio_h);
    ui->radioButton_B->setGeometry(x_radio,A_h + add_h,radio_w,radio_h);
    ui->radioButton_C->setGeometry(x_radio,A_h + 2*add_h,radio_w,radio_h);
    ui->radioButton_D->setGeometry(x_radio,A_h + 3*add_h,radio_w,radio_h);

    ui->textquestion_A->setGeometry(x_text,A_h,text_w,text_h );
    ui->textquestion_B->setGeometry(x_text,A_h + add_h,text_w,text_h );
    ui->textquestion_C->setGeometry(x_text,A_h + 2*add_h,text_w,text_h );
    ui->textquestion_D->setGeometry(x_text,A_h + 3*add_h,text_w,text_h );

    ui->labeltime->setStyleSheet("color:red;");

    ui->labeltimehead->setText("倒计时5秒后开始作答！  ");
    ui->labeltime->setText(QString::number(5,10));
    ui->nextpb->setEnabled(0);
    ui->completepb->setEnabled(0);

    time1  = new QTimer();
    time1 ->start(1000);
    time_count = max_count;

    connect(time1,SIGNAL(timeout()),this,SLOT(count_time()));    //定时显示

}

MainDialog::~MainDialog()
{
    delete ui;
}


void MainDialog::count_time()
{
    //5秒倒计时
    if (ii > 0){
        ui->labeltimehead->setText("倒计时5秒后开始作答！");
        ui->labeltime->setText(QString::number(ii,10));

        QString status = QString("进度：%1 / %2")
                        .arg(QString::number(0,10)).arg(QString::number(10,10));
        ui->labelprocess->setText(status);

        ii --;
        count_question = 1;
        if (ii == 0){
            //frist question
            ui->textquestion_A->setText(QString::number(count_question,10));
            ui->textquestion_B->setText(QString::number(count_question,10));
            ui->textquestion_C->setText(QString::number(count_question,10));
            ui->textquestion_D->setText(QString::number(count_question,10));
            ui->nextpb->setEnabled(1);
            ui->completepb->setEnabled(1);
        }
    }

    else{
        ui->labeltimehead->setText("本题作答剩余时间/s :");
        //if start_answer : count
        if (time_count > 0)
            ui->labeltime->setNum(--time_count);
        else{
            //超时，下一题
            on_nextpb_clicked();
        }
    }

}


void MainDialog::on_nextpb_clicked()
{

    count_question ++;

    time_count = max_count;
    QString count_str = QString::number(count_question,10);
    QString max_str = QString::number(max_questions,10);

    QString status = QString("进度：%1 / %2")
                    .arg(count_str).arg(max_str);

    ui->labelprocess->setText(status);

    ui->textquestion_A->setText(count_str);
    ui->textquestion_B->setText(count_str);
    ui->textquestion_C->setText(count_str);
    ui->textquestion_D->setText(count_str);

    if (count_question == max_questions){
        ui->nextpb->setEnabled(0);
    }
}

void MainDialog::on_completepb_clicked()
{
    ui->nextpb->setEnabled(1);
    time1 ->stop();

    if(count_question < max_questions){
        QString count_str = QString::number(count_question,10);
        QString max_str = QString::number(max_questions,10);

        QString status = QString("一共%1道题，您只回答了%2道，是否提交？")
                        .arg(max_str).arg(count_str);

        // QMessageBox :  https://www.cnblogs.com/zhoug2020/p/10094855.html
        if (QMessageBox::critical(0 , "critical message" ,status, QMessageBox::Ok|QMessageBox::Cancel ) == 0x00000400)
        {
            QMessageBox::information(0 , "information message" ,"6 points", QMessageBox::Ok);
            this->reject();
            ii = 4;
        }

    }
    else{
        QMessageBox::information(0 , "information message" ,"10 points", QMessageBox::Ok);
        this->reject();
        ii = 4;
    }

}

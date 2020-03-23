#include "maindialog.h"
#include "ui_maindialog.h"
#include<iostream>
#include <QTimer>
#include <QString>
#include <QMessageBox>
#include<QThread>
#include<iostream>
#include "sql.h"

std::vector<int> your_answer(15);
extern std::vector<int> out_question_num;

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

    buttonGroup = new QButtonGroup;
    //第二个参数id可以自行定义
    buttonGroup->addButton(ui->radioButton_A,1);
    buttonGroup->addButton(ui->radioButton_B,2);
    buttonGroup->addButton(ui->radioButton_C,3);
    buttonGroup->addButton(ui->radioButton_D,4);

    QString Show_ = ui->labelname->text();
    Show_.append(this_usrname);
    ui->labelname->setText(Show_);

    //显示出题比例
    QString Show_1 = ui->labelques_class->text();
    Show_1.append(int2qstr(out_question_num[0]));
    Show_1.append(":");
    Show_1.append(int2qstr(out_question_num[1]));
    Show_1.append(":");
    Show_1.append(int2qstr(out_question_num[2]));
    ui->labelques_class->setText(Show_1);
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
                        .arg(QString::number(0,10)).arg(QString::number(max_questions,10));
        ui->labelprocess->setText(status);

        ii --;
        count_question = 1;
        if (ii == 0){
            //frist question
            ui->textquestion->setText(question[count_question-1]);
            ui->textquestion_A->setText(re_a[count_question-1]);
            ui->textquestion_B->setText(re_b[count_question-1]);
            ui->textquestion_C->setText(re_c[count_question-1]);
            ui->textquestion_D->setText(re_d[count_question-1]);
            status = QString("进度：%1 / %2")
                            .arg(QString::number(count_question,10)).arg(QString::number(max_questions,10));
            ui->labelprocess->setText(status);

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
            qDebug() << "time out!";
            on_nextpb_clicked();
        }
    }
}

//这里还没搞好！！没找到清除radio的api，先这样吧！
void MainDialog::groupbutton_init()
{
//    ui->radioButton_A->set;
//    ui->radioButton_A->setChecked(1);
//    ui->radioButton_B->setChecked(1);
//    ui->radioButton_C->setChecked(1);
//    ui->radioButton_D->setChecked(1);
    if( ui->radioButton_A->isChecked())
       ui->radioButton_A->setChecked(0);
    if( ui->radioButton_B->isChecked())
       ui->radioButton_B->setChecked(0);


}
int MainDialog::get_groupbutton()
{
    return buttonGroup->checkedId();
}

int class_scores[] = {0,0,0};
void MainDialog::on_nextpb_clicked()
{
    //qDebug() << get_groupbutton();
    int this_answer = get_groupbutton();
    if (this_answer == re_right[count_question - 1]){
        class_scores[classes[count_question - 1] - 1] ++;
    }
    qDebug() <<re_right[count_question - 1]<< " "<<this_answer;

    groupbutton_init();
    count_question ++;
    time_count = max_count;
    QString count_str = QString::number(count_question,10);
    QString max_str = QString::number(max_questions,10);

    QString status = QString("进度：%1 / %2")
                    .arg(count_str).arg(max_str);

    ui->labelprocess->setText(status);

    //Questions_Index(15);

    ui->textquestion->setText(question[count_question-1]);
    ui->textquestion_A->setText(re_a[count_question-1]);
    ui->textquestion_B->setText(re_b[count_question-1]);
    ui->textquestion_C->setText(re_c[count_question-1]);
    ui->textquestion_D->setText(re_d[count_question-1]);


    if (count_question == max_questions){
        ui->nextpb->setEnabled(0);
    }
}

int scores_15to100(int in_scores){
    return int(float(in_scores)/15*100);
}

void __init__global()
{
    re_a.clear();
    re_b.clear();
    re_c.clear();
    re_d.clear();
    re_right.clear();
    classes.clear();
    question.clear();
    out_question_num.clear();
}

void MainDialog::on_completepb_clicked()
{
    if(count_question < max_questions){
        QString count_str = QString::number(count_question,10);
        QString max_str = QString::number(max_questions,10);

        QString status = QString("一共%1道题，您只回答了%2道，是否提交？")
                        .arg(max_str).arg(count_str);


        // QMessageBox :  https://www.cnblogs.com/zhoug2020/p/10094855.html
        if (QMessageBox::critical(0 , "critical message" ,status, QMessageBox::Ok|QMessageBox::Cancel ) == 0x00000400)
        {
            //提交前的一次答案
            int this_answer = get_groupbutton();
            if (this_answer == re_right[count_question - 1]){
                class_scores[classes[count_question - 1] - 1] ++;
            }
            qDebug() <<re_right[count_question - 1]<< " .  "<<this_answer;


            int scores100 = 0;
            for (int i = 0;i < 3;i++){
                scores100 += class_scores[i];
                class_scores[i] = int(100*class_scores[i]/float(out_question_num[i]));

            }
            scores100 = scores_15to100(scores100);
            //scores100 = scores100 >100?100:scores100;
            QString scores_show = QString("%1 points!").arg(scores100);


            QMessageBox::information(0, "information message" ,scores_show, QMessageBox::Ok);
            this->reject();
            time1 ->stop();
            ui->nextpb->setEnabled(1);
            ii = 4;
            int scores_[] = {0,0,0,0};
            scores_[0] = scores100;
            for (int i = 0;i < 3;i ++){
                scores_[i+1] = class_scores[i];
                class_scores[i] = 0;
            }
            StudentDatabase = sql.WriteStudent_table(StudentDatabase,this_usrname,scores_);
            __init__global();
        }
    }
    else{
        //提交前的一次答案
        int this_answer = get_groupbutton();
        if (this_answer == re_right[count_question - 1]){
            class_scores[classes[count_question - 1] - 1] ++;
        }
        qDebug() <<re_right[count_question - 1]<< " .  "<<this_answer;

        int scores100 = 0;
        for (int i = 0;i < 3;i++){
            scores100 += class_scores[i];
            class_scores[i] = int(100*class_scores[i]/float(out_question_num[i]));
        }
        scores100 = scores_15to100(scores100);
        //scores100 = scores100 >100?100:scores100;
        QString scores_show = QString("%1 points!").arg(scores100);

        QMessageBox::information(NULL , "information message" ,scores_show, QMessageBox::Ok);
        this->reject();
        time1 ->stop();
        ui->nextpb->setEnabled(1);
        ii = 4;
        int scores_[] = {0,0,0,0};
        scores_[0] = scores100;
        for (int i = 0;i < 3;i ++){
            scores_[i+1] = class_scores[i];
            class_scores[i] = 0;
        }
        StudentDatabase = sql.WriteStudent_table(StudentDatabase,this_usrname,scores_);
        __init__global();
    }
}

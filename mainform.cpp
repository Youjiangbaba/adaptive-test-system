#include "mainform.h"
#include "ui_mainform.h"
#include<QDateTime>
#include <QTimer>
#include <QString>
#include <vector>
#include "sql.h"
#include "adaptive_questin.h"

#include <ctime>
#include <iostream>
std::vector<int> out_question_num;

std::vector<int> get_randArry(int lenth)
{
    std::cout << "lenth" <<lenth <<std::endl;
    std::vector<int> nums(lenth);
    srand((int)time(0));  // 产生随机种子  把0换成NULL也行
    for (int i = 0; i < lenth; i++){
        //srand((int)time(0));
        int flag_repeat = 0;
        int this_rand = rand()%(100);
        uint8_t size_nums = nums.size();
        //std::cout <<"nums size:" <<size_nums<<std::endl;
        //这里处理随机出现相同的情况！
        for (int j = 0;j < lenth;j++){
            if (this_rand == nums[j]){
                i--;
                flag_repeat = 1;
                break;
            }
        }

        if (flag_repeat == 0){
            //nums.push_back(this_rand);
            nums[i] = this_rand;
        }
    }
    for(int i = 0;i < nums.size();i++)
        std::cout <<"nums:"<<i<< "  "<< nums[i] <<std::endl;
    return  nums;
}


MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    //table widght
    QStringList headList;
    headList<<"答题时间"<<"分数"<<"A类正确率"<<"B类正确率"<<"C类正确率";
    ui->tableWidget->setColumnCount(5);//设置列数
    ui->tableWidget->setRowCount(100);//设置行数
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应列宽
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
    //ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格不能被编辑
    //ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中效果
    //ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//设置为只能单选
    //ui->tableWidget->verticalHeader()->setVisible(false);   //隐藏列表头
    //ui->tableWidget->horizontalHeader()->setVisible(false); //隐藏行表头
    ui->tableWidget->setHorizontalHeaderLabels(headList);//设置表头
    //ui->tableWidget->setItem(0,0,new QTableWidgetItem(""));
    //qDebug() << ui->tableWidget->item(0,0)->text();//为空获取会报错！！！

    time_t = new QTimer();
    time_t->start(1000);
    connect(time_t,SIGNAL(timeout()),this,SLOT(updateTime()));

    on_updateResult_clicked();
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_startanswerpd_clicked()
{
    //根据上次结果算出比例，并取出这次的题!
    int id = 0;
    int scores_classes[] = {100,100,100};
    qDebug() << "start!" ;

        QSqlQuery sql_query(StudentDatabase);
        //查询数据
        int score;
        int class_a,class_b,class_c;

        QString find_cmd = "select * from student_";
        find_cmd.append(this_usrname);
        sql_query.exec(find_cmd);

        if(!sql_query.exec()){
            qDebug()<<sql_query.lastError();
        }
        else{//已经有过成绩
            while(sql_query.next()){
                scores_classes[0] = sql_query.value(3).toInt();
                scores_classes[1] = sql_query.value(4).toInt();
                scores_classes[2] = sql_query.value(5).toInt();
            }
        }

    out_question_num  = adaptive_questin(scores_classes);
//    for (int kk = 0;kk <3;kk++){
//        get_randArry(5);
//        std::cout << kk<<" "<<out_question_num[kk]<<std::endl;
//    }
    //3.6  18.00 以下有bug，以上调通

    //total 300
    //Questions_Index
    //随机读取题目，存在题库中
    std::vector<int> Questions_Index;
    std::vector<int> mid_;
    for (int i = 0;i < 3;i++){
        int lenth = out_question_num[i];
        std::cout << lenth << std::endl;
        mid_ = get_randArry(lenth);

        for (int count = 0;count < mid_.size();count++){
            Questions_Index.push_back(100*i+mid_[count]);
        }
        mid_.clear();
    }
    std::cout << "size: "<<Questions_Index.size()<<std::endl;
    for (int ll = 0; ll < 15;ll ++)
        std::cout <<"Questions_Index  "<< Questions_Index[ll]<<std::endl;
    //extern QList<QString> question,re_a,re_b,re_c,re_d;
    //extern std::vector<int> re_right,classes;
    sql.read_questions(StudentDatabase,Questions_Index);
    Questions_Index.clear();

    qDebug() <<"std_result"<< re_right<<"  classes: " <<classes;


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

void MainForm::updateItem()
{
//    std::cout << "clicked!"<<std::endl;
//    QSqlQuery sql_query(StudentDatabase);
//    //查询数据
//    int id = 0;//
//    QString time_writed;
//    int score;
//    int class_a,class_b,class_c;

//    QString find_cmd = "select * from student_";
//    find_cmd.append(this_usrname);
//    sql_query.exec(find_cmd);

//    if(!sql_query.exec()){
//        qDebug()<<sql_query.lastError();
//    }
//    else{
//        while(sql_query.next()){
//            id = sql_query.value(0).toInt();
//            time_writed = sql_query.value(1).toString();
//            score = sql_query.value(2).toInt();
//            class_a = sql_query.value(3).toInt();
//            class_b = sql_query.value(4).toInt();
//            class_c = sql_query.value(5).toInt();

//            qDebug() << id << " ..."<< time_writed<< " "<< score<< " "<< class_a;

//            ui->tableWidget->setItem(id-1,0,new QTableWidgetItem(time_writed));
//            ui->tableWidget->setItem(id-1,1,new QTableWidgetItem(int2qstr(score)));
//            ui->tableWidget->setItem(id-1,2,new QTableWidgetItem(int2qstr(class_a)));
//            ui->tableWidget->setItem(id-1,3,new QTableWidgetItem(int2qstr(class_b)));
//            ui->tableWidget->setItem(id-1,4,new QTableWidgetItem(int2qstr(class_c)));
//        }
//        ui->tableWidget->show();
//    }
}

void MainForm::updateTime()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");

    QString name_str = this_usrname;
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

void MainForm::on_updateResult_clicked()
{
    ui->updateResult->setEnabled(0);
    ui->startanswerpd->setEnabled(0);
//    void updateItem();

    std::cout << "clicked!"<<std::endl;
    QSqlQuery sql_query(StudentDatabase);
    //查询数据
    int id = 0;//
    QString time_writed;
    int score;
    int class_a,class_b,class_c;

    QString find_cmd = "select * from student_";
    find_cmd.append(this_usrname);
    sql_query.exec(find_cmd);

    if(!sql_query.exec()){
        qDebug()<<sql_query.lastError();
    }
    else{
        while(sql_query.next()){
            id = sql_query.value(0).toInt();
            time_writed = sql_query.value(1).toString();
            score = sql_query.value(2).toInt();
            class_a = sql_query.value(3).toInt();
            class_b = sql_query.value(4).toInt();
            class_c = sql_query.value(5).toInt();

            //qDebug() << id << " ..."<< time_writed<< " "<< score<< " "<< class_a;

            ui->tableWidget->setItem(id-1,0,new QTableWidgetItem(time_writed));
            ui->tableWidget->setItem(id-1,1,new QTableWidgetItem(int2qstr(score)));
            ui->tableWidget->setItem(id-1,2,new QTableWidgetItem(int2qstr(class_a)));
            ui->tableWidget->setItem(id-1,3,new QTableWidgetItem(int2qstr(class_b)));
            ui->tableWidget->setItem(id-1,4,new QTableWidgetItem(int2qstr(class_c)));
        }
    }

    ui->updateResult->setEnabled(1);
    ui->startanswerpd->setEnabled(1);
    std::cout << "clicked ---!"<<std::endl;
}

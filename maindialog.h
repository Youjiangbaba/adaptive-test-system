#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = nullptr);
    ~MainDialog();

    const int max_count = 100;//一道题多少秒
    int time_count;

    int max_questions = 15;// total道题
    int count_question = 0;

    int ii = 4;

private slots:
    void on_nextpb_clicked();

    void on_completepb_clicked();

    void count_time();

private:
    Ui::MainDialog *ui;

    QTimer *time1;


};

#endif // MAINDIALOG_H

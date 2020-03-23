#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include "maindialog.h"


namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = nullptr);
    ~MainForm();



private slots:
    void on_startanswerpd_clicked();

    void on_quitsyspd_clicked();

    void updateTime();

    void on_updateResult_clicked();

private:

     void updateItem();

    Ui::MainForm *ui;

    MainDialog *maindialog;

    QTimer *time_t;
};

#endif // MAINFORM_H

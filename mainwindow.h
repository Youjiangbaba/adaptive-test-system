#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"

#include "mainform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_registerPB_clicked();

    void on_login_clicked();

    void on_quit_clicked();

private:
    Ui::MainWindow *ui;
    Dialog *dialog;

    MainForm *mm;

};

#endif // MAINWINDOW_H

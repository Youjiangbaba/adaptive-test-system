#include "mainwindow.h"
#include <QApplication>
#include "sql.h"
int main(int argc, char *argv[])
{
    sql_test();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

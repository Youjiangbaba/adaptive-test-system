#include "warn.h"
#include "ui_warn.h"

warn::warn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::warn)
{
    ui->setupUi(this);
    ui->warnlb->setText("warn text!");
}

warn::~warn()
{
    delete ui;
}

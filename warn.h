#ifndef WARN_H
#define WARN_H

#include <QDialog>

namespace Ui {
class warn;
}

class warn : public QDialog
{
    Q_OBJECT

public:
    explicit warn(QWidget *parent = nullptr);
    ~warn();

private:
    Ui::warn *ui;
};

#endif // WARN_H

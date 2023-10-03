#ifndef PERSONALCENTER_H
#define PERSONALCENTER_H

#include <QDialog>

namespace Ui {
class PersonalCenter;
}

class PersonalCenter : public QDialog
{
    Q_OBJECT

public:
    explicit PersonalCenter(QWidget *parent = nullptr);
    ~PersonalCenter();

private:
    Ui::PersonalCenter *ui;
};

#endif // PERSONALCENTER_H

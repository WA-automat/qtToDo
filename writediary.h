#ifndef WRITEDIARY_H
#define WRITEDIARY_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QMessageBox>
#include "diarydetails.h"

namespace Ui {
class WriteDiary;
}

class WriteDiary : public QDialog
{
    Q_OBJECT

public:
    explicit WriteDiary(QWidget *parent = nullptr);
    ~WriteDiary();

private:
    Ui::WriteDiary *ui;
};

#endif // WRITEDIARY_H

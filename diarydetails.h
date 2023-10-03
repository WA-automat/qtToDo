#ifndef DIARYDETAILS_H
#define DIARYDETAILS_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>

namespace Ui {
class DiaryDetails;
}

class DiaryDetails : public QDialog
{
    Q_OBJECT

public:
    explicit DiaryDetails(int id, QWidget *parent = nullptr);
    ~DiaryDetails();

private:
    Ui::DiaryDetails *ui;
};

#endif // DIARYDETAILS_H

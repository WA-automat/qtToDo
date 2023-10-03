#ifndef PERSONALCENTER_H
#define PERSONALCENTER_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QtCharts/QLineSeries>
#include <QtCharts/QtCharts>
#include "diarydetails.h"
#include "diarylistitem.h"

namespace Ui {
class PersonalCenter;
}

class PersonalCenter : public QDialog
{
    Q_OBJECT

public:
    explicit PersonalCenter(QWidget *parent = nullptr);
    void refreshDiaryList(void);
    ~PersonalCenter();

private:
    Ui::PersonalCenter *ui;
};

#endif // PERSONALCENTER_H

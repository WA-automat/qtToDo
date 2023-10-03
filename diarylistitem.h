#ifndef DIARYLISTITEM_H
#define DIARYLISTITEM_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "diarydetails.h"
#include "personalcenter.h"

namespace Ui {
class DiaryListItem;
}

class DiaryListItem : public QWidget
{
    Q_OBJECT

public:
    explicit DiaryListItem(int _id, QWidget *parent = nullptr);
    ~DiaryListItem();

private:
    Ui::DiaryListItem *ui;
    int id;
};

#endif // DIARYLISTITEM_H

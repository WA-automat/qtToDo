#ifndef TODOLISTITEM_H
#define TODOLISTITEM_H

#include <QWidget>
#include <QString>
#include <QDateTime>
#include <QFont>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class ToDoListItem;
}

class ToDoListItem : public QWidget
{
    Q_OBJECT

public:
    explicit ToDoListItem(int _id, QString _content, QDateTime _datetime, QWidget *parent = nullptr);
    ~ToDoListItem();

private:
    Ui::ToDoListItem *ui;
    int id;
    QString content;
    QDateTime datetime;
    bool isFinished;
};

#endif // TODOLISTITEM_H

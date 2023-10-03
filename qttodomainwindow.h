#ifndef QTTODOMAINWINDOW_H
#define QTTODOMAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include <personalcenter.h>
#include <writediary.h>
#include <todolistitem.h>
#include <QSqlQuery>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class QtToDoMainWindow; }
QT_END_NAMESPACE

class QtToDoMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QtToDoMainWindow(QWidget *parent = nullptr);
    ~QtToDoMainWindow();

private:
    Ui::QtToDoMainWindow *ui;
};
#endif // QTTODOMAINWINDOW_H

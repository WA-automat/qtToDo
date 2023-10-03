#include "qttodomainwindow.h"

#include <QDebug>
#include <QApplication>
#include <QSqlDatabase>
#include <QStringList>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
    // 连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("QTtodo.db");
    db.open();

    // 获取数据库中的表名
    QStringList tableNameList = db.tables();
    qDebug() << tableNameList << endl;

    // 判断日记是否建表
    if (!tableNameList.contains("diary")) {
        QSqlQuery query;
        QString createDiaryTableStr = "CREATE TABLE diary \
                (   \
                    id         INTEGER      PRIMARY KEY AUTOINCREMENT,  \
                    title      VARCHAR(100) NOT NULL,   \
                    content    TEXT         NOT NULL,   \
                    createTime DATETIME     NOT NULL    \
                )";
        if (query.exec(createDiaryTableStr)) {
            qDebug() << "创建日记表成功" << endl;
        }
    }

    // 判断待办是否建表
    if (!tableNameList.contains("todoTable")) {
        QSqlQuery query;
        QString createToDoTableStr = "CREATE TABLE todoTable   \
                (   \
                    id         INTEGER      PRIMARY KEY AUTOINCREMENT,  \
                    content    TEXT         NOT NULL,  \
                    deadline   DATETIME     NOT NULL,  \
                    isFinished BOOLEAN      NOT NULL   \
                )";
        if (query.exec(createToDoTableStr)) {
            qDebug() << "创建待办表成功" << endl;
        }
    }


    // 验证建表是否成功
    tableNameList = db.tables();
    qDebug() << tableNameList << endl;

    QApplication a(argc, argv);
    QtToDoMainWindow w;
    w.show();
    return a.exec();
}

#include "diarydetails.h"
#include "ui_diarydetails.h"

DiaryDetails::DiaryDetails(int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiaryDetails)
{
    // 设置 UI
    ui->setupUi(this);
    this->setFixedSize(900, 900);

    // 数据库查询当前日记
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    QSqlQuery query(db);
    query.prepare("select * from diary where id = :id");
    query.bindValue(":id", id);
    query.exec();
    QString title, content;
    QDateTime datetime;
    while (query.next()) {
        title = query.value(1).toString();
        content = query.value(2).toString();
        datetime = query.value(3).toDateTime();
//        qDebug() << title << ' ' << content << ' ' << datetime << endl;
    }

    // 窗口内容
    this->setWindowTitle(title);
    ui->titleLabel->setText(title);
    ui->datetimeLabel->setText(datetime.toString());
    ui->textEdit->setText(content);
}

DiaryDetails::~DiaryDetails()
{
    delete ui;
}

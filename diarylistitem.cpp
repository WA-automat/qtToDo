#include "diarylistitem.h"
#include "ui_diarylistitem.h"

DiaryListItem::DiaryListItem(int _id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiaryListItem),
    id(_id)
{
    // 组件 UI
    ui->setupUi(this);
    this->setFixedSize(1000, 100);
    ui->diaryTitleLabel->setFixedWidth(800);
    ui->diaryTitleLabel->setAlignment(Qt::AlignCenter);
    // 数据库查询当前日记
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    QSqlQuery query(db);
    query.prepare("select * from diary where id = :id");
    query.bindValue(":id", id);
    query.exec();
    QString title;
    while (query.next()) {
        title = query.value(1).toString();
    }

    ui->diaryTitleLabel->setText(title);

    // 展示日记具体内容
    connect(ui->showPushButton, &QPushButton::clicked, this,
            [=]() {
                auto diaryDetailsPage = new DiaryDetails(id);
                diaryDetailsPage->exec();
            }
    );

    // 删除某日记
    connect(ui->removePushButton, &QPushButton::clicked, this,
            [=]() {
                QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
                QSqlQuery query(db);
                query.prepare("delete from diary where id = :id");
                query.bindValue(":id", id);
                query.exec();
                ((PersonalCenter *)(parent))->refreshDiaryList();
            }
    );

}

DiaryListItem::~DiaryListItem()
{
    delete ui;
}

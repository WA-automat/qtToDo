#include "todolistitem.h"
#include "ui_todolistitem.h"

ToDoListItem::ToDoListItem(int _id, QString _content, QDateTime _datetime, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToDoListItem),
    id(_id), content(_content), datetime(_datetime), isFinished(false)
{
    // 设置组件 UI
    ui->setupUi(this);
    this->setFixedSize(1000, 100);
    ui->label->setText(content + " " + datetime.toString());

    // 事件连接
    // 标记是否完成了该待办的两个事件
    // 状态转变事件
    connect(ui->checkBox, &QCheckBox::stateChanged, this,
            [=]() {
                QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
                // 状态转变事件
                if (ui->checkBox->isChecked()) {
                    // 已经完成的待办
                    QFont font = ui->label->font();
                    font.setStrikeOut(true);
                    ui->label->setFont(font);
                    // 修改数据库
                    QSqlQuery query(db);
                    query.prepare("update todoTable set isFinished = 1 where id = :id");
                    query.bindValue(":id", id);
                    query.exec();
                    isFinished = true;
                } else {
                    // 还未完成的待办
                    QFont font = ui->label->font();
                    font.setStrikeOut(false);
                    ui->label->setFont(font);
                    // 修改数据库
                    QSqlQuery query(db);
                    query.prepare("update todoTable set isFinished = 0 where id = :id");
                    query.bindValue(":id", id);
                    query.exec();
                    isFinished = false;
                }
            }
    );

}

ToDoListItem::~ToDoListItem()
{
    delete ui;
}

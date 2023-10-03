#include "writediary.h"
#include "ui_writediary.h"

WriteDiary::WriteDiary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WriteDiary)
{
    // 日记编辑页面 UI
    ui->setupUi(this);
    this->setWindowTitle("写日记");
    this->setFixedSize(1600, 900);

    // 绑定事件
    connect(ui->submitPushButton, &QPushButton::clicked, this,
            [=]() {
                if (ui->titleLineEdit->text() == "") {
                    QMessageBox::warning(this, "警告", "日记标题不能为空");
                    return;
                } else if (ui->textEdit->toPlainText() == "") {
                    QMessageBox::warning(this, "警告", "日记内容不能为空");
                    return;
                }
                QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
                QSqlQuery query(db);
                query.prepare("insert into diary(id, title, content, createTime) values(NULL, :title, :content, :createTime)");
                query.bindValue(":title", ui->titleLineEdit->text());
                query.bindValue(":content", ui->textEdit->toPlainText());
                query.bindValue(":createTime", QDateTime::currentDateTime());
                query.exec();
                // 查询自增 ID
                QString id = query.lastInsertId().toString();
                qDebug() << id << endl;

                this->close();

                // TODO: 打开该日记预览页面
                auto diaryDetailsPage = new DiaryDetails(id.toInt());
                diaryDetailsPage->exec();
            }
    );
}

WriteDiary::~WriteDiary()
{
    delete ui;
}

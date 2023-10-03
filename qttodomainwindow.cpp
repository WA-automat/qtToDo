#include "qttodomainwindow.h"
#include "ui_qttodomainwindow.h"


QtToDoMainWindow::QtToDoMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtToDoMainWindow)
{
    // 获取数据库连接
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
        db.open();
//        qDebug() << "数据库已成功连接" << endl;
    } else {
        this->close();
        QMessageBox::critical(this, "数据库连接失败", "数据库连接失败");
        return;
    }

    // 页面 UI
    ui->setupUi(this);
    this->setWindowTitle("QtToDo");
    this->setFixedSize(2100, 1200);
    ui->personalPushButton->setFixedSize(300, 200);
    ui->writePushButton->setFixedSize(300, 200);
    ui->introduce->setText("\n\nQtToDo: \n\n用于编写待办与日记的开源工具软件。\n\nAuthor: 林泽勋\nsince: 2023.10.3\nVersion: v1.0");
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    // 事件绑定
    // 导航栏事件
    // 退出事件
    connect(ui->actionexit, &QAction::triggered, this,
            [=](){ this->close(); } // 点击退出按钮弹窗退出
    );
    // 导航栏进入个人中心页面
    connect(ui->actionpersonal, &QAction::triggered, this,
            []() {
                auto persenalCenterWidget = new PersonalCenter();
                persenalCenterWidget->exec();
            }
    );
    // 导航栏进入写日记页面
    connect(ui->actionwrite, &QAction::triggered, this,
            []() {
                auto writeDiaryWidget = new WriteDiary();
                writeDiaryWidget->exec();
            }
    );
    // 按钮事件
    // 按钮进入个人中心页面
    connect(ui->personalPushButton, &QPushButton::clicked, this,
            []() {
                auto persenalCenterWidget = new PersonalCenter();
                persenalCenterWidget->exec();
            }
    );
    // 按钮进入写日记页面
    connect(ui->writePushButton, &QPushButton::clicked, this,
            []() {
                auto writeDiaryWidget = new WriteDiary();
                writeDiaryWidget->exec();
            }
    );
    // TODO: lineEdit实现添加待办并存入数据库中
    connect(ui->lineEdit, &QLineEdit::returnPressed, this,
            [=]() {
                // 存入数据库中
                QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
                QSqlQuery query(db);
                query.prepare("insert into todoTable(id, content, deadline, isFinished) values(NULL, :content, :deadline, :isFinished)");
                QString datetime = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm:ss");
                query.bindValue(":content", ui->lineEdit->text());
                query.bindValue(":deadline", datetime);
                query.bindValue(":isFinished", false);
                query.exec();
                // 查询自增 ID
                QString id = query.lastInsertId().toString();

                // 创建一个节点
                auto listWidgetItem = new QListWidgetItem(id);
                listWidgetItem->setSizeHint(QSize(200, 100));

                // 存入列表中
                ui->listWidget->addItem(listWidgetItem);
                ui->listWidget->setItemWidget(listWidgetItem,
                                              new ToDoListItem(
                                                  id.toInt(),
                                                  ui->lineEdit->text(),
                                                  ui->dateTimeEdit->dateTime()
                                                  ));

                // 清空 lineEdit
                ui->lineEdit->setText("");
            }
    );
}

QtToDoMainWindow::~QtToDoMainWindow()
{
    delete ui;
}


#include "personalcenter.h"
#include "ui_personalcenter.h"

PersonalCenter::PersonalCenter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonalCenter)
{
    // 页面 UI
    ui->setupUi(this);
    this->setWindowTitle("个人中心");
    this->setFixedSize(2100, 1200);
    ui->label->setFixedSize(800, 20);
    ui->label->setAlignment(Qt::AlignCenter);
    ui->leftWidget->setFixedSize(800, 1200);
    ui->countWidget->setFixedSize(800, 400);
    ui->todoCount->setFixedSize(300, 200);
    ui->diaryCount->setFixedSize(300, 200);

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    QSqlQuery query;

    // 获取已完成待办数量
    query.prepare("select count(*) from todoTable where isFinished = :isFinished");
    query.bindValue(":isFinished", true);
    query.exec();
    QString times;
    while (query.next()) {
        times = query.value(0).toString();
    }
    ui->todoCount->setText("已完成的待办数量：\n" + times);

    // 获取已编写日记数量
    query.prepare("select count(*) from diary");
    query.exec();
    while (query.next()) {
        times = query.value(0).toString();
    }
    ui->diaryCount->setText("已编写的日记数量：\n" + times);

    // 获取日记列表
    query.prepare("select * from diary");
    query.exec();
    while (query.next()) {
        QString id = query.value(0).toString();
        // 创建一个节点
        auto listWidgetItem = new QListWidgetItem(id, ui->diaryListWidget);
        listWidgetItem->setSizeHint(QSize(200, 100));
        // 存入列表中
        ui->diaryListWidget->addItem(listWidgetItem);
        ui->diaryListWidget->setItemWidget(listWidgetItem,
                                      new DiaryListItem(
                                          id.toInt(),
                                          this
                                          ));
    }

    // 统计图绘制
    QChartView* cview = new QChartView(ui->canvasWidget);
    cview->setFixedSize(800, 600);
    QChart* chart = new QChart();
    chart->setTitle("一周内待办与日记完成（编写）数量");
    cview->setChart(chart);


    // 查询近一周内待办与日记数量
    QLineSeries* todoSeries = new QLineSeries();
    QLineSeries* diarySeries = new QLineSeries();
    chart->addSeries(todoSeries);
    chart->addSeries(diarySeries);

    QHash<QDate, int> todoMp, diaryMp;
    query.prepare("SELECT deadline FROM todoTable WHERE deadline >= date('now', '-7 days') and isFinished = :isFinished");
    query.bindValue(":isFinished", true);
    query.exec();
    while (query.next()) {
        todoMp[query.value(0).toDate()]++;
    }

    // 获取当前时间
    QDate currentDate = QDate::currentDate();
    int mx = 0;
    for (int i = 0; i < 7; i++) {
        todoSeries->append(7 - i, todoMp[currentDate.addDays(-i)]);
        diarySeries->append(7 - i, diaryMp[currentDate.addDays(-i)]);
        mx = std::max(mx, std::max(todoMp[currentDate.addDays(-i)], diaryMp[currentDate.addDays(-i)]));
    }
    //创建坐标轴
    QValueAxis* axisX = new QValueAxis;
    axisX->setRange(1, 7);
    axisX->setLabelFormat("%d");
    chart->addAxis(axisX, Qt::AlignBottom); // 将轴添加到图表中
    todoSeries->attachAxis(axisX); // 将数据系列附加到轴上
    diarySeries->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis;
    axisY->setRange(0, mx);
    axisY->setLabelFormat("%d");
    chart->addAxis(axisY, Qt::AlignLeft); // 将轴添加到图表中
    todoSeries->attachAxis(axisY); // 将数据系列附加到轴上
    diarySeries->attachAxis(axisY);
}

PersonalCenter::~PersonalCenter()
{
    delete ui;
}

void PersonalCenter::refreshDiaryList()
{
    ui->diaryListWidget->clear();
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    QSqlQuery query;

    // 获取已完成待办数量
    query.prepare("select count(*) from todoTable where isFinished = :isFinished");
    query.bindValue(":isFinished", true);
    query.exec();
    QString times;
    while (query.next()) {
        times = query.value(0).toString();
    }
    ui->todoCount->setText("已完成的待办数量：\n" + times);

    // 获取已编写日记数量
    query.prepare("select count(*) from diary");
    query.exec();
    while (query.next()) {
        times = query.value(0).toString();
    }
    ui->diaryCount->setText("已编写的日记数量：\n" + times);

    // 获取日记列表
    query.prepare("select * from diary");
    query.exec();
    while (query.next()) {
        QString id = query.value(0).toString();
        // 创建一个节点
        auto listWidgetItem = new QListWidgetItem(id, ui->diaryListWidget);
        listWidgetItem->setSizeHint(QSize(200, 100));
        // 存入列表中
        ui->diaryListWidget->addItem(listWidgetItem);
        ui->diaryListWidget->setItemWidget(listWidgetItem,
                                      new DiaryListItem(
                                          id.toInt(),
                                          this
                                          ));
    }
}

#include "personalcenter.h"
#include "ui_personalcenter.h"

PersonalCenter::PersonalCenter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonalCenter)
{
    ui->setupUi(this);
    this->setWindowTitle("个人中心");
}

PersonalCenter::~PersonalCenter()
{
    delete ui;
}

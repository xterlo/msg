#include "glavnaya.h"
#include "ui_glavnaya.h"

Glavnaya::Glavnaya(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Glavnaya)
{
    ui->setupUi(this);


}

Glavnaya::~Glavnaya()
{
    delete ui;
}

void Glavnaya::on_pushButton_clicked()
{
    emit firstWindow();
    this->close();
}


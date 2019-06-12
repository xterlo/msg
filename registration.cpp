#include "registration.h"
#include "ui_registration.h"
#include <windows.h>

Registration::Registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_pushButton_2_clicked()
{
    this->close();      // Закрываем окно
    emit firstWindow();

}

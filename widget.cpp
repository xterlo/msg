#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QEventLoop>
#include <QMessageBox>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    downloader = new Downloader();

    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::pr_bar);
    connect(ui->pushButton, &QPushButton::clicked, downloader, &Downloader::getData);
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::end);
    
}

Widget::~Widget()
{
    delete ui;
}

void sleepp(int msec)
{
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, SLOT(quit()));
    loop.exec();
}

void Widget::on_pushButton_2_clicked()
{
    exit(0);
}
void Widget::pr_bar() {
    ui->progressBar->setValue(15);
    sleepp(300);
    ui->progressBar->setValue(25);
    sleepp(300);
    ui->progressBar->setValue(35);
    sleepp(300);
    ui->progressBar->setValue(45);
    sleepp(300);
    ui->progressBar->setValue(65);
    sleepp(300);
    ui->progressBar->setValue(75);
    sleepp(300);
}
void Widget::end() {
    ui->progressBar->setValue(85);
    sleepp(100);
    ui->progressBar->setValue(95);
    sleepp(100);
    ui->progressBar->setValue(100);
    QMessageBox::information(0,"Успешно!", "Обновление завершено!");
    exit(0);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTimer"

void sleep(qint64 msec)
{
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, SLOT(quit()));
    loop.exec();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(15);
    ui->progressBar->setValue(25);
    ui->progressBar->setValue(35);
    ui->progressBar->setValue(45);
    ui->progressBar->setValue(55);
    ui->progressBar->setValue(65);
    ui->progressBar->setValue(75);
    ui->progressBar->setValue(85);
    ui->progressBar->setValue(95);
    ui->progressBar->setValue(100);

}

MainWindow::~MainWindow()
{
    delete ui;
}


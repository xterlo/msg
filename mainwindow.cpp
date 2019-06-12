#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <windows.h>
#include <QMessageBox>
#include <QtDebug>
#include <QDesktopWidget>
#include <string>
#include <QApplication>
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)


{

    ui->setupUi(this);
    const QRect razmer = QApplication::desktop()->screenGeometry();
    int x = razmer.width()/3;
    int y = razmer.height()/3;
    MainWindow::resize(x,y);
    MainWindow::setMaximumSize(x,y);
    MainWindow::setMinimumSize(x,y);
    qDebug()<<razmer;
    ui->password->setText("");
    reg = new Registration();
    connect(reg, &Registration::firstWindow, this, &MainWindow::show);
    glava = new Glavnaya();
    connect(glava, &Glavnaya::firstWindow, this, &MainWindow::show);
    forgot = new ForgotPass();
    connect(forgot, &ForgotPass::firstWindow, this, &MainWindow::show);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_authorization_clicked()
{

    QString login = ui->login->text();
    QString password = ui->password->text();
    if(login=="1" && password == "1")
    {

     QMessageBox::information(this,"NICE","NICE");

     glava->show();
     close();

    }
    else
    {
     QMessageBox::information(this,"NO","NO");

    }

}

void MainWindow::on_reg_clicked()
{
    reg->show();
    close();


}

void MainWindow::on_pushButton_clicked()
{
    forgot->show();
    close();
}

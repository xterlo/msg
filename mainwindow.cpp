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
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)


{

    ui->setupUi(this);
    int x=0;
    int y=0;
    const QRect razmer = QApplication::desktop()->screenGeometry();


        switch (razmer.width())
        {
            case 3840:
                {
                    x = razmer.width()/8;
                    break;
                }
            case 2560:
                {
                    x = razmer.width()/6;
                    break;
                }
            case 2048:
                {
                    x = razmer.width()/5;
                    break;
                }
            case 1920:
                {
                    if(razmer.height() == 1080) x = razmer.width()/4;
                    else x = razmer.width()/5;
                    break;
                }
            case 1768:
                {
                    x = razmer.width()/4;
                    break;
                }
            case 1680:
                {
                    x = razmer.width()/4;
                    break;
                }
            case 1600:
                {
                    x = razmer.width()/4;
                    break;
                }

            case 1366:
                {
                    x = razmer.width()/3;
                    break;
                }
            case 1360:
                {
                    x = razmer.width()/3;
                    break;
                }
            case 1280:
                {
                    x = razmer.width()/3;
                    break;
                }
            case 1176:
                {
                    x = razmer.width()/2;
                    break;
                }
            case 1152:
                {
                    x = razmer.width()/2;
                    break;
                }
            case 1024:
                {
                    x = razmer.width()/2;
                    break;
                }
            case 800:
                {
                    x = razmer.width()/2;
                    break;
                }



        }

        switch(razmer.height())
        {
            case 2160:
                {
                    y = razmer.height()/8;
                    break;
                }
            case 1600:
                {
                    y = razmer.height()/6;
                    break;
                }
            case 1536:
                {
                    y = razmer.height()/5;
                    break;
                }
            case 1440:
                {
                    if(razmer.width()==1920) y =razmer.height()/5;
                    else y = razmer.height()/6;
                    break;
                }
            case 1200:
                {
                    if(razmer.width()==1600) y =razmer.height()/4;
                    else y = razmer.height()/5;
                    break;
                }
            case 1080:
                {
                    y = razmer.height()/4;
                    break;
                }
            case 1050:
                {
                    y = razmer.height()/4;
                    break;
                }
            case 1024:
                {
                    if(razmer.width()==1280) y =razmer.height()/3;
                    y = razmer.height()/4;
                    break;
                }
            case 992:
                {
                    y = razmer.height()/4;
                    break;
                }
            case 960:
                {
                    y = razmer.height()/3;
                    break;
                }
            case 900:
                {
                    y = razmer.height()/4;
                    break;
                }
            case 864:
                {
                    y = razmer.height()/3;
                    break;
                }
            case 800:
                {
                    y = razmer.height()/3;
                    break;
                }
            case 768:
                {
                    y = razmer.height()/3;
                    break;
                }
            case 720:
                {
                    y = razmer.height()/3;
                    break;
                }
            case 664:
                {
                    y = razmer.height()/2;
                    break;
                }
            case 600:
                {
                    y = razmer.height()/2;
                    break;
                }

        }


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
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("my_database");
    db.setUserName("username");
    db.setPassword("password");
    if(!db.open())
        QMessageBox::warning(this,"Error","Unable to connect to the database");


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

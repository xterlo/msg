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
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QCryptographicHash>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)


{

    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
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
        default:
        {
            if(razmer.width()>3840 )x=razmer.width()/9;
            if(razmer.width()<800 )x=razmer.width();
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
            default:
            {
                    if(razmer.width()>2160 )x=razmer.width()/9;
                    if(razmer.width()<600 )x=razmer.height();
                    break;
        }
        }


    MainWindow::resize(x,y);
   // ui->moveWW->pos(0,0);
    ui->moveWW->setMinimumSize(razmer.width(),20);
    MainWindow::setMaximumSize(x,y);
    MainWindow::setMinimumSize(477,259);
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

    if (login == "" or password == "") {
        QMessageBox::warning(this,"Ошибка!","Извините,проверьте корректность заполненных данных!");
    } else {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("95.143.216.174");
    db.setPort(3306);
    db.setDatabaseName("server");
    db.setUserName("server");
    db.setPassword("server");
    if(!db.open()) {
        QMessageBox::warning(this,"Ошибка!","Не удалось подключиться к серверу.\nКод ошибки: 0001");
        //qDebug() <<db.lastError();
    } else {
        QSqlQuery query;
         password = QString(QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Sha1).toHex());
         query.exec("SELECT * FROM users WHERE login='"+login+"' AND password='"+password+"'");
         if (query.last() == false) {
            QMessageBox::warning(this,"Ошибка!","Извините,проверьте корректность заполненных данных!");
         } else {
             query.exec("SELECT active FROM users WHERE login='"+login+"' AND password='"+password+"'");
             int active = query.value(0).toInt();
             if (active == 0) {
                QMessageBox::warning(this,"Ошибка!","Извините,данный пользователь не активирован.Пройдите на почту для активации.");
                //здесь отправка письма на почту и открытие окна активации.
             } else {
             close();
             glava->show();
             }
         }
    }
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



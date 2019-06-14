#include "forgotpass.h"
#include "ui_forgotpass.h"
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <stdio.h>
#include <time.h>
#include <QDebug>
#include <QDesktopWidget>
#include "mainwindow.h"
ForgotPass::ForgotPass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgotPass)
{
    ui->setupUi(this);
   this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    QDesktopWidget *razmer = QApplication::desktop();
    int windowx = razmer->width();
    int windowy = razmer->height();
    ForgotPass::resize(400,160);
    ui->exitbutton->setGeometry(370,0,30,20);
    ui->backbutton->setGeometry(0,0,30,20);

}
ForgotPass::~ForgotPass()
{
    delete ui;
}
void ForgotPass::on_pushButton_clicked()
{
    QString email = ui->email->text();



    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("95.143.216.174");
    db.setPort(3306);
    db.setDatabaseName("server");
    db.setUserName("server");
    db.setPassword("server");
    if(!db.open()) {
        //qDebug() << db.lastError();
        QMessageBox::warning(this,"Ошибка!","Не удалось подключиться к серверу.\nКод ошибки: 0001");
    } else {
        QSqlQuery query;
        query.exec("SELECT * FROM users WHERE email='"+email+"'");
        if (query.last() == false) {
           QMessageBox::warning(this,"Ошибка!","Такого пользователя с данной почтой не существует!");
        } else {
            //query.exec("UPDATE users SET link='"+kode+"' WHERE email='"+email+"'");
            //close()
        }
    }


}
void ForgotPass::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void ForgotPass::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}


void ForgotPass::on_exitbutton_clicked()
{
    close();

}

void ForgotPass::on_backbutton_clicked()
{
     close();
    MainWindow *mainwind = new MainWindow(this);
    mainwind->show();

}

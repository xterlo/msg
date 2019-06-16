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
    QSqlQuery query;
    query.exec("SELECT * FROM users WHERE email='"+email+"'");
    if (query.last() == false) {
        QMessageBox::warning(this,"Ошибка!","Такого пользователя с данной почтой не существует!");
    } else {
        srand(static_cast<unsigned int>(time(0)));
        int aaa = 111 + rand() % 889;
        int bbb = 111 + rand() % 889;
        QString a = QString::number(aaa);
        QString b = QString::number(bbb);
        QString kode = a + b;
        query.exec("UPDATE users SET link='"+kode+"' WHERE email='"+email+"'");
        Smtp* smtp;
        QString name = "Регистрация в мессенжере.";
        QString msg = "Здравствуйте, "+email+".\nДобро пожаловать в наш мессенжер.Используйте код для активации аккаунта!("+kode+")\nС уважением,Команда.";
        smtp = new Smtp("alfaland.online@gmail.com", "MyAlfamail", "smtp.gmail.com", 465);
        smtp->sendMail("alfaland.online@gmail.com", email , name, msg);
        qDebug()<< email << endl << msg << endl << name ;
        close();
        //здесь пусть откроет окно ввода кода и след окном смену окно со сменой пароля.
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

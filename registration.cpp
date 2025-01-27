﻿#include "registration.h"
#include "ui_registration.h"
#include <QMessageBox>
#include <QtDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QCryptographicHash>
#include <QDateTime>
#include "mainwindow.h"
#include "Crypter.h"
static int proverka;
static int proverka1;

Registration::Registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registration)
{

    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    QDesktopWidget *razmer = QApplication::desktop();
    Registration::resize(310,220);
  //  ui->exitbutton->setGeometry(430,0,30,19);
    //ui->backbutton->setGeometry(0,0,30,19);
}

Registration::~Registration()
{
    delete ui;
}
void Registration::keyPressEvent(QKeyEvent *event){
if(event->key()==16777221) Registration::on_pushButton_clicked();
if(event->key()==16777220) Registration::on_pushButton_clicked();
}
void Registration::on_exitbutton_clicked()
{
    close();

}
void Registration::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        checkmouse = false;
    }
    return QWidget::mouseReleaseEvent(event);
}
void Registration::on_backbutton_clicked()
{
     close();
    MainWindow *mainwind = new MainWindow(this);
    mainwind->show();

}

void Registration::on_pushButton_clicked()
{
    QString email = ui->email->text();
    QString login = ui->login->text();
    QString password = ui->password->text();
    QString password_rep = ui->password_rep->text();
    proverka1 = 0;

    if (email.size() < 3  or  email.size()> 64) {
        QMessageBox::warning(this,"Ошибка!","Адрес электронной почты должен включать в себя от 3 до 64 символов.");
        proverka1 = 1;
    }
    if (login.size() < 3  or  login.size()> 64) {
        QMessageBox::warning(this,"Ошибка!","Логин должен включать в себя от 3 до 64 символов.");
        proverka1 = 2;
    }
    if (password.size() < 3  or  password.size()> 64) {
        QMessageBox::warning(this,"Ошибка!","Пароль должен включать в себя от 3 до 64 символов.");
        proverka1 = 3;
    }
    if (proverka1 == 0) {
    if (email == "" or login == "" or password == "" or password_rep == "") {
        QMessageBox::warning(this,"Ошибка!","Извините,проверьте корректность заполненных данных!");
    } else {
        if (password!=password_rep) QMessageBox::warning(this,"Ошибка!","Извините,проверьте корректность заполненных данных!");
        else {
            QSqlQuery query;
            proverka = 0;
            query.exec("SELECT * FROM users WHERE email='"+email+"'");
            if (query.last() == true) {
               QMessageBox::warning(this,"Ошибка!","Извините,введённый Вами почта используется.Попробуйте ещё раз.");
               proverka = 1;
            }
            query.exec("SELECT * FROM users WHERE login='"+login+"'");
            if (query.last() == true) {
               QMessageBox::warning(this,"Ошибка!","Извините,введённый Вами логин используется.Попробуйте ещё раз.");
               proverka = 2;
            }
            if (proverka == 0) {
            srand(static_cast<unsigned int>(time(0)));
            int aaa = 111 + rand() % 889;
            int bbb = 111 + rand() % 889;
            QString a = QString::number(aaa);
            QString b = QString::number(bbb);
            QString kode = a + b;
            QDateTime datetime;
            QDateTime date = datetime.currentDateTime();
            QString hash = QString(QCryptographicHash::hash(login.toLatin1(),QCryptographicHash::Md5).toHex());
            Crypter::setSecretkey(hash);
            password = Crypter::cryptString(password);

            query.prepare("INSERT INTO users (email, login, password, date, link, hash) "
                      "VALUES (?, ?, ?, ?, ?, ?)");
               query.addBindValue(email);
               query.addBindValue(login);
               query.addBindValue(password);
               query.addBindValue(date);
               query.addBindValue(kode);
               query.addBindValue(hash);
               query.exec();
               Smtp* smtp;
               QString name = "Регистрация в мессенжере.";
               QString msg = "Здравствуйте, "+login+".\nДобро пожаловать в наш мессенжер.Используйте код для активации аккаунта!("+kode+")\nС уважением,Команда.";
               smtp = new Smtp("alfaland.online@gmail.com", "MyAlfamail", "smtp.gmail.com", 465);
               smtp->sendMail("alfaland.online@gmail.com", email , name, msg);
               QMessageBox::information(this,"Успех!","Вы успешно зарегистрировались!");
               close();
               MainWindow *mainwind = new MainWindow(this);
               mainwind->show();
            }
         }
     }
    }
}
void Registration::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
    if(m_nMouseClick_X_Coordinate<430 && m_nMouseClick_X_Coordinate>30)
        {
        if(event->button() == Qt::LeftButton && m_nMouseClick_Y_Coordinate<20) checkmouse = true;
            else checkmouse = false;
        }
    else checkmouse = false;
}
void Registration::mouseMoveEvent(QMouseEvent *event) {
    if (checkmouse == true){
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
    }
}


void Registration::on_Mini_clicked()
{
    showMinimized();
}

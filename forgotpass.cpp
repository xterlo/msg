#include "forgotpass.h"
#include "ui_forgotpass.h"
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <stdio.h>
#include <time.h>
#include "QTimer"
#include <QDebug>
#include <QDesktopWidget>
#include "mainwindow.h"
#include <QSettings>


void Sleep(qint64 msec)
{
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, SLOT(quit()));
    loop.exec();
}

ForgotPass::ForgotPass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgotPass)
{
    ui->setupUi(this);
   //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    QDesktopWidget *razmer = QApplication::desktop();
    int windowx = razmer->width();
    int windowy = razmer->height();
    ForgotPass::resize(400,160);
    fpr = new forgotpassrepeat;
    activation = new Activation;
    connect(this, SIGNAL(sendData(QString)), activation, SLOT(emailData(QString)));
    connect(this, SIGNAL(sendData(QString)), fpr, SLOT(emailData(QString)));

}


ForgotPass::~ForgotPass()
{
    delete ui;
}
void ForgotPass::keyPressEvent(QKeyEvent *event){
    if(event->key()==16777221) ForgotPass::on_pushButton_clicked();
    if(event->key()==16777220) ForgotPass::on_pushButton_clicked();
}
void ForgotPass::on_pushButton_clicked()
{
    QString email = ui->email->text();
    emit sendData(ui->email->text());
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
        QString name = "Смена пароля";
        QString msg = "Здравствуйте, "+email+".\nВы запросили смену пароля.Используйте код измения пароля!("+kode+")\nС уважением,Команда.";
        smtp = new Smtp("alfaland.online@gmail.com", "MyAlfamail", "smtp.gmail.com", 465);
        smtp->sendMail("alfaland.online@gmail.com", email , name, msg);
        Sleep(600);
        QSettings settings("HKEY_CURRENT_USER\\Software\\IBM_SOFTWARE",QSettings::NativeFormat);
        settings.clear();
        activation -> show();
        close();
    }
}
void ForgotPass::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
    if(m_nMouseClick_X_Coordinate<370 && m_nMouseClick_X_Coordinate>30)
        {
        if(m_nMouseClick_Y_Coordinate<20) checkmouse = true;
            else checkmouse = false;
        }
    else checkmouse = false;
}
void ForgotPass::mouseMoveEvent(QMouseEvent *event) {
    if (checkmouse == true){
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
    }
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

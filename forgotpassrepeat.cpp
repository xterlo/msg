#include "forgotpassrepeat.h"
#include "ui_forgotpassrepeat.h"
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QCryptographicHash>
#include "mainwindow.h"
static QString email;
forgotpassrepeat::forgotpassrepeat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::forgotpassrepeat)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint );
    forgotpassrepeat::resize(330,150);
}

forgotpassrepeat::~forgotpassrepeat()
{
    delete ui;
}
void forgotpassrepeat::emailData(QString Qmail)
{
   std::string mail = Qmail.toStdString();
   email = mail.c_str();
   qDebug() << mail.c_str();
}
void forgotpassrepeat::on_pushButton_clicked()
{
    QString fpassword = ui->fpass->text();
    QString spassword = ui->spass->text();

    if(fpassword!=spassword) {
        QMessageBox::warning(this,"Ошибка","Пароли не совпадают!");
    } else {
        QSqlQuery query;
        fpassword = QString(QCryptographicHash::hash(fpassword.toLatin1(),QCryptographicHash::Sha1).toHex());
        query.exec("UPDATE users SET password='"+fpassword+"' WHERE email='"+email+"'");
        close();
        MainWindow *mainwind = new MainWindow(this);
        mainwind->show();
    }
}//ds
void forgotpassrepeat::on_exitbutton_clicked()
{
    exit(0);
}
void forgotpassrepeat::keyPressEvent(QKeyEvent *event){
    if(event->key()==16777221) forgotpassrepeat::on_pushButton_clicked();
    if(event->key()==16777220) forgotpassrepeat::on_pushButton_clicked();
}
void forgotpassrepeat::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
        if(m_nMouseClick_Y_Coordinate<20) checkmouse = true;
            else checkmouse = false;
}
void forgotpassrepeat::mouseMoveEvent(QMouseEvent *event) {
    if (checkmouse == true){
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
    }
}



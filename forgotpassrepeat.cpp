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
}

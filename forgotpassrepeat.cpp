#include "forgotpassrepeat.h"
#include "ui_forgotpassrepeat.h"
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDebug>
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

    if(fpassword!=spassword) QMessageBox::warning(this,"Ошибка","Паоли не совпадают!");
    else
    {
        QSqlQuery query;
        query.exec("SELECT * FROM users WHERE email='"+email+"'");
        QSqlRecord recc = query.record();
        query.next();
        query.exec("UPDATE users SET password='"+fpassword+"' WHERE email='"+email+"'");
    }
}

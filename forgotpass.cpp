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

ForgotPass::ForgotPass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgotPass)
{
    ui->setupUi(this);

}
ForgotPass::~ForgotPass()
{
    delete ui;
}
void ForgotPass::on_pushButton_clicked()
{
    QString email = ui->email->text();

    close();

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
        }
    }

    emit firstWindow();
}

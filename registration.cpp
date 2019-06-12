#include "registration.h"
#include "ui_registration.h"
#include <QMessageBox>
#include <QtDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

Registration::Registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_pushButton_2_clicked()
{
    this->close();    
    emit firstWindow();

}

void Registration::on_pushButton_clicked()
{
    QString email = ui->email->text();
    QString login = ui->login->text();
    QString password = ui->password->text();
    QString password_rep = ui->password_rep->text();

    if (email == "" or login == "" or password == "" or password_rep == "") {
        QMessageBox::warning(this,"Ошибка!","Извините,проверьте корректность заполненных данных!");
    } else {
        if (password!=password_rep) QMessageBox::warning(this,"Ошибка!","Извините,проверьте корректность заполненных данных!");
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("95.143.216.174");
        db.setPort(3306);
        db.setDatabaseName("server");
        db.setUserName("server");
        db.setPassword("server");
        if(!db.open()) {
            QMessageBox::warning(this,"Ошибка!","Не удалось подключиться к серверу");
            //qDebug() <<db.lastError();
        } else {
//здесь создание записи
         }
     }
}

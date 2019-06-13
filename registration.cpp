#include "registration.h"
#include "ui_registration.h"
#include <QMessageBox>
#include <QtDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QCryptographicHash>
#include <QDateTime>
static int proverka;
static int proverka1;

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
            QDateTime datetime;
            QDateTime date = datetime.currentDateTime();
            password = QString(QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Sha1).toHex());
            query.prepare("INSERT INTO users (email, login, password,date) "
                      "VALUES (?, ?, ?, ?)");
               query.addBindValue(email);
               query.addBindValue(login);
               query.addBindValue(password);
               query.addBindValue(date);
               query.exec();
               QMessageBox::information(this,"Успех!","Вы успешно зарегистрировались!");
            }
         }
     }
    }
}

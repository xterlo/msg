#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <windows.h>
#include <QMessageBox>
#include <QtDebug>
#include <QDesktopWidget>
#include <string>
#include <QApplication>
#include <iostream>
#include <tchar.h>
#include <QSettings>
#include <QNetworkInterface>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
static QString login;
static QString keyy;
static QString version = "1.0";



using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)


{

    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint );
    MainWindow::resize(415,259);
    ui->exitbutton->setGeometry(385,0,30,19);
    ui->password->setText("");
    regactivation=new Regactivation();
    connect(regactivation, &Regactivation::firstWindow, this, &MainWindow::show);
    reg = new Registration();
    connect(reg, &Registration::firstWindow, this, &MainWindow::show);
    glava = new Glavnaya();
    connect(glava, &Glavnaya::firstWindow, this, &MainWindow::show);
    forgot = new ForgotPass();
    connect(forgot, &ForgotPass::firstWindow, this, &MainWindow::show);
    connect(this, SIGNAL(sendData(QString)), regactivation, SLOT(recieveData(QString)));

    QSettings settings("HKEY_CURRENT_USER\\Software\\IBM_SOFTWARE\\",QSettings::NativeFormat);
    foreach (QString key, settings.allKeys()) {
        if (settings.value(key) != "" ) {
            ui->login->setText(key);
            ui->password->setText("ABCDEFG");
            keyy = settings.value(key).toString();
        }
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}
void sleep(qint64 msec)
{
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, SLOT(quit()));
    loop.exec();
}
void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key()==16777221) MainWindow::on_authorization_clicked();
    if(event->key()==16777220) MainWindow::on_authorization_clicked();
}

void MainWindow::on_authorization_clicked()
{
    emit sendData(ui->login->text());
    login = ui->login->text();
    QString password = ui->password->text();
    bool zp = ui->checkBox->checkState();




    ui->progressBar->setValue(150);
    sleep(100);
    ui->progressBar->setValue(250);

    if (login == "" or password == "") {
        QMessageBox::warning(this,"Ошибка!","Проверьте корректность заполненных данных!");
        ui->progressBar->setValue(0);
    } else {
         QSqlQuery query;

         ui->progressBar->setValue(350);
         sleep(200);
         ui->progressBar->setValue(450);
         sleep(200);
         ui->progressBar->setValue(550);
         sleep(200);

         password = QString(QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Sha1).toHex());

         query.exec("SELECT * FROM users WHERE login='"+login+"' AND password='"+password+"' or (login='"+login+"' AND password='"+keyy+"')");
         if (query.last() == false) {
            QMessageBox::warning(this,"Ошибка!","Проверьте корректность заполненных данных!");
            ui->progressBar->setValue(0);
         } else {
             query.exec("SELECT * FROM users WHERE login='"+login+"' AND password='"+password+"' or (login='"+login+"' AND password='"+keyy+"')");
             QSqlRecord rec = query.record();
             query.next();

             ui->progressBar->setValue(650);
             sleep(200);
             ui->progressBar->setValue(750);
             sleep(200);
             ui->progressBar->setValue(850);
             sleep(200);
             ui->progressBar->setValue(950);

             int active  = query.value(rec.indexOf("active")).toInt();
             if (active == 0) {
                QMessageBox::warning(this,"Ошибка!","Данный пользователь не активирован.Пройдите на почту для активации.");
                ui->progressBar->setValue(0);
                QDateTime datetime;
                QDateTime date = datetime.currentDateTime();
                QString ip = "95.143.216.174";
                query.prepare("INSERT INTO last_attempt (login,ip,date,version) "
                          "VALUES (?, ?, ?, ?)");
                   query.addBindValue(login);
                   query.addBindValue(ip);
                   query.addBindValue(date);
                   query.addBindValue(version);
                   query.exec();
                regactivation->show();
             } else {
             ui->progressBar->setValue(1000);
             sleep(200);
             if (zp == true ) {
                    QSettings settings("HKEY_CURRENT_USER\\Software\\IBM_SOFTWARE\\",QSettings::NativeFormat);
                    settings.setValue(login, password);
                 close();
                 ui->progressBar->setValue(0);
                 glava->show();
                 QDateTime datetime;
                 QDateTime date = datetime.currentDateTime();
                 QString ip = "95.143.216.174";
                 query.prepare("INSERT INTO last_attempt (login,ip,date,version) "
                           "VALUES (?, ?, ?, ?)");
                    query.addBindValue(login);
                    query.addBindValue(ip);
                    query.addBindValue(date);
                    query.addBindValue(version);
                    query.exec();
             } else {
                 QDateTime datetime;
                 QDateTime date = datetime.currentDateTime();
                 QString ip = "95.143.216.174";
                 query.prepare("INSERT INTO last_attempt (login,ip,date,version) "
                           "VALUES (?, ?, ?, ?)");
                    query.addBindValue(login);
                    query.addBindValue(ip);
                    query.addBindValue(date);
                    query.addBindValue(version);
                    query.exec();
                query.exec("SELECT * FROM beta_uses WHERE user='"+login+"'");
                if (query.last() == true) {
                QSettings settings("HKEY_CURRENT_USER\\Software\\IBM_PROFILES\\",QSettings::NativeFormat);
                settings.setValue(login, "1");
                }
                close();
                ui->progressBar->setValue(0);
                glava->show();
                }
             }
         }
    }
}

void MainWindow::on_reg_clicked()
{
    reg->show();
    close();
}

void MainWindow::on_forgot_clicked()
{
    forgot->show();
    close();

}


void MainWindow::on_exitbutton_clicked()
{

    qApp->quit();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
    if(m_nMouseClick_X_Coordinate<385)
        {
        if(m_nMouseClick_Y_Coordinate<20) checkmouse = true;
            else checkmouse = false;
        }
    else checkmouse = false;
}
void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (checkmouse == true){
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
    }
}


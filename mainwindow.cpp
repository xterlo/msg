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




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)


{

    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint );
    QRect screenRect(QApplication::desktop()->screenGeometry());
    QDesktopWidget *razmer = QApplication::desktop();
    //this->resize(razmer->width() * 0.25, razmer->height() * 0.25);
    //MainWindow::resize(480,330);
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
                   query.addBindValue(ipp);
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

                    QDateTime datetime;
                    QDateTime date = datetime.currentDateTime();
                    query.prepare("INSERT INTO last_attempt (login,ip,date,version) "
                              "VALUES (?, ?, ?, ?)");
                       query.addBindValue(login);
                       query.addBindValue(ipp);
                       query.addBindValue(date);
                       query.addBindValue(version);
                       query.exec();
                    close();
                    glava->show();
             } else {
                 QDateTime datetime;
                 QDateTime date = datetime.currentDateTime();
                 QNetworkAccessManager networkManager;

                 QUrl url("https://api.ipify.org");
                 QUrlQuery queryy;
                 queryy.addQueryItem("format", "json");
                 url.setQuery(queryy);

                 QNetworkReply* reply = networkManager.get(QNetworkRequest(url));

                 QObject::connect(reply, &QNetworkReply::finished,
                 [&](){
                 if(reply->error() != QNetworkReply::NoError) {
                 //failure
                 qDebug() << "error: " << reply->error();
                 } else {
                 QJsonObject jsonObject= QJsonDocument::fromJson(reply->readAll()).object();
                 QHostAddress ip(jsonObject["ip"].toString());
                 //do whatever you want with the ip
                 qDebug() << "external ip: " << ip;
                 ipp = ip.toString();
                 qDebug() << ipp;
                 }
                 reply->deleteLater();
                 });
                 query.prepare("INSERT INTO last_attempt (login,ip,date,version) "
                           "VALUES (?, ?, ?, ?)");
                    query.addBindValue(login);
                    query.addBindValue(ipp);
                    query.addBindValue(date);
                    query.addBindValue(version);
                    query.exec();
                query.exec("SELECT * FROM beta_uses WHERE user='"+login+"'");
                if (query.last() == true) {
                QSettings settings("HKEY_CURRENT_USER\\Software\\IBM_PROFILES\\",QSettings::NativeFormat);
                settings.setValue(login, "1");
                }
                close();
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

    exit(0);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
        if(m_nMouseClick_Y_Coordinate<20) checkmouse = true;
            else checkmouse = false;
}
void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (checkmouse == true){
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
    }
}


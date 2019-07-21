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
#include <QNetworkAccessManager>
#include <QNetworkReply>

static QString login;
static QString keyy;
static QString version = "1.0";
static QString ip;



using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)


{

    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint );
    QRect screenRect(QApplication::desktop()->screenGeometry());
    QDesktopWidget *razmer = QApplication::desktop();
    MainWindow::resize(450,120);
    ui->password->setText("");
    regactivation=new Regactivation();
    connect(regactivation, &Regactivation::firstWindow, this, &MainWindow::show);
    reg = new Registration();
    connect(reg, &Registration::firstWindow, this, &MainWindow::show);
    glava = new Glavnaya();
    //glava->show();
    connect(glava, &Glavnaya::firstWindow, this, &MainWindow::show);
    forgot = new ForgotPass();
    connect(forgot, &ForgotPass::firstWindow, this, &MainWindow::show);
    connect(this, SIGNAL(sendData(QString)), regactivation, SLOT(recieveData(QString)));
    connect(this, SIGNAL(sendData(QString)), glava, SLOT(recieveData(QString)));

    QSettings settings("HKEY_CURRENT_USER\\Software\\IBM_SOFTWARE\\",QSettings::NativeFormat);
    foreach (QString key, settings.allKeys()) {
        if (settings.value(key) != "" ) {
            ui->login->setText(key);
            ui->password->setText("ABCDEFG");
            keyy = settings.value(key).toString();
        }
    }
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl("https://api.ipify.org/")));
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    ip = response->readAll();


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_exitbutton_clicked()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
    trayIcon->setToolTip("МЕСЕНГЕР");
    QMenu * menu = new QMenu(this);
    //QAction * viewWindow = new QAction("Развернуть окно", this);
    QAction * quitAction = new QAction("Выход", this);
    //connect(viewWindow, SIGNAL(triggered()), this, SLOT(show()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
    //menu->addAction(viewWindow);
    menu->addAction(quitAction);
    trayIcon->setContextMenu(menu);
    if(checkclosewind==false)trayIcon->show();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
        this->hide();
}
void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason){
    case QSystemTrayIcon::Trigger:

            if(!this->isVisible()){
                this->show();
                trayIcon->hide();
            } else {
                this->hide();
            }

        break;
    default:
        break;
    }
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




    if (login == "" or password == "") {
        QMessageBox::warning(this,"Ошибка!","Проверьте корректность заполненных данных!");
    } else {
         QSqlQuery query;


         password = QString(QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Sha1).toHex());

         query.exec("SELECT * FROM users WHERE login='"+login+"' AND password='"+password+"' or (login='"+login+"' AND password='"+keyy+"')");
         if (query.last() == false) {
            QMessageBox::warning(this,"Ошибка!","Проверьте корректность заполненных данных!");

         } else {
             query.exec("SELECT * FROM users WHERE login='"+login+"' AND password='"+password+"' or (login='"+login+"' AND password='"+keyy+"')");
             QSqlRecord rec = query.record();
             query.next();

             int active  = query.value(rec.indexOf("active")).toInt();
             if (active == 0) {
                QMessageBox::warning(this,"Ошибка!","Данный пользователь не активирован.Пройдите на почту для активации.");
 
                QDateTime datetime;
                QDateTime date = datetime.currentDateTime();
  
                query.prepare("INSERT INTO last_attempt (login,ip,date,version) "
                          "VALUES (?, ?, ?, ?)");
                   query.addBindValue(login);
                   query.addBindValue(ip);
                   query.addBindValue(date);
                   query.addBindValue(version);
                   query.exec();
                regactivation->show();
             } else {

             sleep(200);
             if (zp == true ) {
                    QSettings settings("HKEY_CURRENT_USER\\Software\\IBM_SOFTWARE\\",QSettings::NativeFormat);
                    settings.setValue(login, password);
                 close();
 
                 glava->show();
                 QDateTime datetime;
                 QDateTime date = datetime.currentDateTime();
         
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


void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        checkmouse = false;
    }
    return QWidget::mouseReleaseEvent(event);
}
void MainWindow::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
        if(event->button() == Qt::LeftButton && m_nMouseClick_Y_Coordinate<20) checkmouse = true;
            else checkmouse = false;
}
void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (checkmouse == true){
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
    }
}


void MainWindow::on_Mini_clicked()
{
    MainWindow::showMinimized();
}

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
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QCryptographicHash>
#include <iostream>
#include <QtSql/QSqlRecord>




using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)


{

    ui->setupUi(this);
    QDesktopWidget *razmer = QApplication::desktop();
    int windowx = razmer->width();
    int windowy = razmer->height();
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint );
    MainWindow::resize(415,259);
    ui->exitbutton->setGeometry(385,0,30,20);
    ui->password->setText("");
   // connect(ui->moveWW,SIGNAL(clicked()),this,SLOT(mousePressEvent()));
   // connect(ui->moveWW,SIGNAL(move()),this,SLOT(mouseMoveEvent()));
    activation=new Activation();
    connect(activation, &Activation::firstWindow, this, &MainWindow::show);
    reg = new Registration();
    connect(reg, &Registration::firstWindow, this, &MainWindow::show);
    glava = new Glavnaya();
    connect(glava, &Glavnaya::firstWindow, this, &MainWindow::show);
    forgot = new ForgotPass();
    connect(forgot, &ForgotPass::firstWindow, this, &MainWindow::show);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_authorization_clicked()
{

    QString login = ui->login->text();
    QString password = ui->password->text();

    if (login == "" or password == "") {
        QMessageBox::warning(this,"Ошибка!","Извините,проверьте корректность заполненных данных!");
    } else {
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
         password = QString(QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Sha1).toHex());
         query.exec("SELECT * FROM users WHERE login='"+login+"' AND password='"+password+"'");
         if (query.last() == false) {
            QMessageBox::warning(this,"Ошибка!","Извините,проверьте корректность заполненных данных!");
         } else {
             query.exec("SELECT * FROM users WHERE login='"+login+"' AND password='"+password+"'");
             QSqlRecord rec = query.record();
             query.next();
             int active  = query.value(rec.indexOf("active")).toInt();
             if (active == 0) {
                QMessageBox::warning(this,"Ошибка!","Извините,данный пользователь не активирован.Пройдите на почту для активации.");
                activation->show();
             } else {
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

    qApp->quit();
}
void MainWindow::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}



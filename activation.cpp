#include "activation.h"
#include "ui_activation.h"
#include <string>
#include <QDebug>
#include <QMessageBox>
#include <qdesktopwidget.h>
#include "mainwindow.h"
#include <string>
#include <iostream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
static QString username;
static QString email;

Activation::Activation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Activation)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    QDesktopWidget *razmer = QApplication::desktop();
    Activation::resize(400,175);   
    ui->exitbutton->setGeometry(370,0,30,20);

}

Activation::~Activation()
{
    delete ui;
}

void Activation::recieveData(QString Qnick)
{
   std::string nick = Qnick.toStdString();
   username = nick.c_str();
   qDebug() << nick.c_str();
}
void Activation::emailData(QString Qmail)
{
   std::string mail = Qmail.toStdString();
   email = mail.c_str();
   qDebug() << mail.c_str();
}

void Activation::keyPressEvent(QKeyEvent *event){
    using namespace std;
    QString qfirst = ui->first->text();
    QString qsecond = ui->second->text();
    QString qthird = ui->third->text();
    QString qfourth = ui->fourth->text();
    QString qfifth = ui->fifth->text();
    QString qsixth = ui->sixth->text();
    string first = qfirst.toStdString();
    string second = qsecond.toStdString();
    string third = qthird.toStdString();
    string fourth = qfourth.toStdString();
    string fifth = qfifth.toStdString();
    string sixth = qsixth.toStdString();
    switch(event->key())
    {

        case 48: //0
        {
        string number="0";
        if(strlen(first.c_str())==0)
            {
            ui->first->setText(number.c_str());
            break;
            }
        if(strlen(second.c_str())==0)
            {
            ui->second->setText(number.c_str());
            break;
            }
        if(strlen(third.c_str())==0)
            {
            ui->third->setText(number.c_str());
            break;
            }
        if(strlen(fourth.c_str())==0)
            {
            ui->fourth->setText(number.c_str());
            break;
            }
        if(strlen(fifth.c_str())==0)
            {
            ui->fifth->setText(number.c_str());
            break;
            }
        if(strlen(sixth.c_str())==0)
            {
            ui->sixth->setText(number.c_str());
            break;
            }
        break;
       }
        case 49: //1
            {
            string number = "1";
            if(strlen(first.c_str())==0)
                {
                ui->first->setText(number.c_str());
                break;
                }
            if(strlen(second.c_str())==0)
                {
                ui->second->setText(number.c_str());
                break;
                }
            if(strlen(third.c_str())==0)
                {
                ui->third->setText(number.c_str());
                break;
                }
            if(strlen(fourth.c_str())==0)
                {
                ui->fourth->setText(number.c_str());
                break;
                }
            if(strlen(fifth.c_str())==0)
                {
                ui->fifth->setText(number.c_str());
                break;
                }
            if(strlen(sixth.c_str())==0)
                {
                ui->sixth->setText(number.c_str());
                break;
                }
            break;
            }
        case 50: //2
            {
            string number="2";
            if(strlen(first.c_str())==0)
                {
                ui->first->setText(number.c_str());
                break;
                }
            if(strlen(second.c_str())==0)
                {
                ui->second->setText(number.c_str());
                break;
                }
            if(strlen(third.c_str())==0)
                {
                ui->third->setText(number.c_str());
                break;
                }
            if(strlen(fourth.c_str())==0)
                {
                ui->fourth->setText(number.c_str());
                break;
                }
            if(strlen(fifth.c_str())==0)
                {
                ui->fifth->setText(number.c_str());
                break;
                }
            if(strlen(sixth.c_str())==0)
                {
                ui->sixth->setText(number.c_str());
                break;
                }
            break;
            }
        case 51: //3
            {
            string number="3";
            if(strlen(first.c_str())==0)
                {
                ui->first->setText(number.c_str());
                break;
                }
            if(strlen(second.c_str())==0)
                {
                ui->second->setText(number.c_str());
                break;
                }
            if(strlen(third.c_str())==0)
                {
                ui->third->setText(number.c_str());
                break;
                }
            if(strlen(fourth.c_str())==0)
                {
                ui->fourth->setText(number.c_str());
                break;
                }
            if(strlen(fifth.c_str())==0)
                {
                ui->fifth->setText(number.c_str());
                break;
                }
            if(strlen(sixth.c_str())==0)
                {
                ui->sixth->setText(number.c_str());
                break;
                }
            break;
            }
        case 52: //4
            {
            string number="4";
            if(strlen(first.c_str())==0)
                {
                ui->first->setText(number.c_str());
                break;
                }
            if(strlen(second.c_str())==0)
                {
                ui->second->setText(number.c_str());
                break;
                }
            if(strlen(third.c_str())==0)
                {
                ui->third->setText(number.c_str());
                break;
                }
            if(strlen(fourth.c_str())==0)
                {
                ui->fourth->setText(number.c_str());
                break;
                }
            if(strlen(fifth.c_str())==0)
                {
                ui->fifth->setText(number.c_str());
                break;
                }
            if(strlen(sixth.c_str())==0)
                {
                ui->sixth->setText(number.c_str());
                break;
                }
            break;
           }
        case 53: //5
            {
            string number="5";
            if(strlen(first.c_str())==0)
                {
                ui->first->setText(number.c_str());
                break;
                }
            if(strlen(second.c_str())==0)
                {
                ui->second->setText(number.c_str());
                break;
                }
            if(strlen(third.c_str())==0)
                {
                ui->third->setText(number.c_str());
                break;
                }
            if(strlen(fourth.c_str())==0)
                {
                ui->fourth->setText(number.c_str());
                break;
                }
            if(strlen(fifth.c_str())==0)
                {
                ui->fifth->setText(number.c_str());
                break;
                }
            if(strlen(sixth.c_str())==0)
                {
                ui->sixth->setText(number.c_str());
                break;
                }
            break;
           }
        case 54: //6
            {
            string number="6";
            if(strlen(first.c_str())==0)
                {
                ui->first->setText(number.c_str());
                break;
                }
            if(strlen(second.c_str())==0)
                {
                ui->second->setText(number.c_str());
                break;
                }
            if(strlen(third.c_str())==0)
                {
                ui->third->setText(number.c_str());
                break;
                }
            if(strlen(fourth.c_str())==0)
                {
                ui->fourth->setText(number.c_str());
                break;
                }
            if(strlen(fifth.c_str())==0)
                {
                ui->fifth->setText(number.c_str());
                break;
                }
            if(strlen(sixth.c_str())==0)
                {
                ui->sixth->setText(number.c_str());
                break;
                }
            break;
           }
        case 55: //7
            {
            string number="7";
            if(strlen(first.c_str())==0)
                {
                ui->first->setText(number.c_str());
                break;
                }
            if(strlen(second.c_str())==0)
                {
                ui->second->setText(number.c_str());
                break;
                }
            if(strlen(third.c_str())==0)
                {
                ui->third->setText(number.c_str());
                break;
                }
            if(strlen(fourth.c_str())==0)
                {
                ui->fourth->setText(number.c_str());
                break;
                }
            if(strlen(fifth.c_str())==0)
                {
                ui->fifth->setText(number.c_str());
                break;
                }
            if(strlen(sixth.c_str())==0)
                {
                ui->sixth->setText(number.c_str());
                break;
                }
            break;           }
        case 56: //8
            {
            string number="8";
            if(strlen(first.c_str())==0)
                {
                ui->first->setText(number.c_str());
                break;
                }
            if(strlen(second.c_str())==0)
                {
                ui->second->setText(number.c_str());
                break;
                }
            if(strlen(third.c_str())==0)
                {
                ui->third->setText(number.c_str());
                break;
                }
            if(strlen(fourth.c_str())==0)
                {
                ui->fourth->setText(number.c_str());
                break;
                }
            if(strlen(fifth.c_str())==0)
                {
                ui->fifth->setText(number.c_str());
                break;
                }
            if(strlen(sixth.c_str())==0)
                {
                ui->sixth->setText(number.c_str());
                break;
                }
            break;
           }
        case 57: //9
        {
        string number="9";
        if(strlen(first.c_str())==0)
            {
            ui->first->setText(number.c_str());
            break;
            }
        if(strlen(second.c_str())==0)
            {
            ui->second->setText(number.c_str());
            break;
            }
        if(strlen(third.c_str())==0)
            {
            ui->third->setText(number.c_str());
            break;
            }
        if(strlen(fourth.c_str())==0)
            {
            ui->fourth->setText(number.c_str());
            break;
            }
        if(strlen(fifth.c_str())==0)
            {
            ui->fifth->setText(number.c_str());
            break;
            }
        if(strlen(sixth.c_str())==0)
            {
            ui->sixth->setText(number.c_str());
            break;
            }
        break;
       }
        case 16777219://Backspace
        {
        string number="";
        if(strlen(second.c_str())==0)
            {
            ui->first->setText(number.c_str());
            break;
            }
        if(strlen(third.c_str())==0)
            {
            ui->second->setText(number.c_str());
            break;
            }
        if(strlen(fourth.c_str())==0)
            {
            ui->third->setText(number.c_str());
            break;
            }
        if(strlen(fifth.c_str())==0)
            {
            ui->fourth->setText(number.c_str());
            break;
            }
        if(strlen(sixth.c_str())==0)
            {
            ui->fifth->setText(number.c_str());
            break;
            }
        if(strlen(sixth.c_str())!=0)
            {
            ui->sixth->setText(number.c_str());
            break;
            }
        break;
       }
    }
   QString qcode = ui->first->text()+ui->second->text()+ui->third->text()+ui->fourth->text()+ui->fifth->text()+ui->sixth->text();
   string code = qcode.toStdString();
   qDebug() << code.c_str();

   QSqlQuery query;
   query.exec("SELECT * FROM users WHERE login='"+username+"' AND active='0'");
   QSqlRecord rec = query.record();
   query.next();
   QString kode  = query.value(rec.indexOf("link")).toString();

   query.exec("SELECT * FROM users WHERE email='"+email+"'");
   QSqlRecord recc = query.record();
   query.next();
   QString kode1  = query.value(recc.indexOf("link")).toString();



   if(code.c_str()==kode)
   {
       QMessageBox::information(this,"Успешно!","Ваш Аккаунт активирован!");
       query.exec("UPDATE users SET link='NULL' WHERE login='"+username+"'");
       query.exec("UPDATE users SET active='1' WHERE login='"+username+"'");
       close();

   }

   if(code.c_str()==kode1)
   {
       query.exec("UPDATE users SET link='' WHERE email='"+email+"'");
       close();
       //женя окно со сменой пароля!

   }


   QWidget::keyPressEvent(event);


}
void Activation::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void Activation::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}



void Activation::on_exitbutton_clicked()
{
    close();
    emit firstWindow();
}

void Activation::on_backbutton_clicked()
{
    close();


}

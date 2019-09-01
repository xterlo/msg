#include "glavnaya.h"
#include "ui_glavnaya.h"
#include <QTimer>
#include <QDesktopWidget>
#include <QDebug>
#include <windows.h>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDateTime>
#include "Crypter.h"
#include <QList>
#include <QDateTime>
#include <QMessageBox>
#include <string>
#include <QKeyEvent>
#include <Base64Decoder.h>
#include <lib.h>
static QString nickname;
static QString username;
static int find_nick = 0;
static QString _login;
Glavnaya::Glavnaya(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Glavnaya)
{
    ui->setupUi(this);

    sizew=Glavnaya::size().width();
    sizey=Glavnaya::size().height();
    posx=Glavnaya::pos().x();
    posy=Glavnaya::pos().y();
    QDesktopWidget * screen = QApplication::desktop();
    screen->availableGeometry();
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint );
    ui->pushButton_2->setEnabled(FALSE);
    ui->stroka->setEnabled(FALSE);
    ui->stroka_name->setEnabled(FALSE);

    find = new finder();



    connect(find,SIGNAL(newdialog(QString)),this, SLOT(adddialog(QString)));

    connect(&sql_1, SIGNAL(update()),this, SLOT(updater()));
    connect(&sql_2, SIGNAL(update()),this, SLOT(add()));
    connect(&sql_4, SIGNAL(update()),this, SLOT(upd()));

}
/*void Glavnaya::on_exitbutton_clicked()
{
    trayIconG = new QSystemTrayIcon(this);
    trayIconG->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
    trayIconG->setToolTip("МЕСЕНГЕР");
    QMenu * menu = new QMenu(this);
   // QAction * viewWindow = new QAction("Развернуть окно", this);
    QAction * quitAction = new QAction("Выход", this);
   // connect(viewWindow, SIGNAL(triggered()), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
   // menu->addAction(viewWindow);
    menu->addAction(quitAction);
    trayIconG->setContextMenu(menu);
    trayIconG->show();
    connect(trayIconG, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
        this->hide();
}*/

void Glavnaya::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason){
    case QSystemTrayIcon::Trigger:

            if(!this->isVisible()){
                this->show();
                trayIconG->hide();
            } else {
                this->hide();
            }

        break;
    default:
        break;
    }
}

void Glavnaya::recieveData(QString Qnick)
{
   std::string nick = Qnick.toStdString();
   nickname = nick.c_str();
   sql_1.set_nickname(nickname);
   sql_3.set_nickname(nickname);

   QSqlQuery query;

   query.exec("SELECT * FROM dialogs WHERE client_1='"+nickname+"' OR client_2='"+nickname+"' ORDER BY id DESC");
   query.next();
   QSqlRecord rec = query.record();
   QString id_dia = query.value(rec.indexOf("id")).toString();
   sql_1.set_id_dia(id_dia);

   QStringList msg_array;

   query.exec("SELECT * FROM dialogs WHERE client_1='"+nickname+"' OR client_2='"+nickname+"' ORDER BY id DESC");
   while (query.next()) {
      QSqlRecord rec = query.record();
      QString client_1  = query.value(rec.indexOf("client_1")).toString();
      QString client_2 = query.value(rec.indexOf("client_2")).toString();
      QString id_dia = query.value(rec.indexOf("id")).toString();

      QSqlQuery quu;
      quu.exec("SELECT * FROM msg WHERE id_dia='"+id_dia+"' ORDER BY id DESC");
      quu.next();
      QSqlRecord re = quu.record();
      QString from_user = quu.value(re.indexOf("from_user")).toString();

      if(from_user != nickname) {
         quu.exec("SELECT * FROM users WHERE login='"+from_user+"'");
         quu.next();
         QSqlRecord re = quu.record();
         QString hash = quu.value(re.indexOf("hash")).toString();
         Crypter::setSecretkey(hash);
      } else {
          quu.exec("SELECT * FROM users WHERE login='"+nickname+"'");
          quu.next();
          QSqlRecord re = quu.record();
          QString hash = quu.value(re.indexOf("hash")).toString();
          Crypter::setSecretkey(hash);
      }

      QString last_msg = query.value(rec.indexOf("last_msg")).toString();

      msg_array << last_msg;

      last_msg = Crypter::decryptString(last_msg);

      if (client_1 == nickname) { 
           ui->dialogs->setStyleSheet("QListWidget::item { border-bottom: 1px solid #eaeaea; color: black; }");
           ui->dialogs->addItem(client_2 + "\n" + last_msg);
      } else {
        ui->dialogs->setStyleSheet("QListWidget::item { border-bottom: 1px solid #eaeaea; color: black; }");
        ui->dialogs->addItem(client_1 + "\n" + last_msg);
      }
   }
   sql_1.set_msg_array(msg_array);
   connect(&thread_1, &QThread::started, &sql_1, &sql_query1::checker);
   sql_1.moveToThread(&thread_1);
   sql_1.setRunning(true);
   thread_1.start();
   connect(&thread_3, &QThread::started, &sql_3, &sql_query3::checker);
   sql_3.moveToThread(&thread_3);
   sql_3.setRunning(true);
   thread_3.start();
}

void Glavnaya::updater()
{
    ui->dialogs->clear();

    sql_1.set_nickname(nickname);

    QSqlQuery query;

    query.exec("SELECT * FROM dialogs WHERE client_1='"+nickname+"' OR client_2='"+nickname+"' ORDER BY id DESC");
    query.next();
    QSqlRecord rec = query.record();
    QString id_dia = query.value(rec.indexOf("id")).toString();
    sql_1.set_id_dia(id_dia);

    QStringList msg_array;

    query.exec("SELECT * FROM dialogs WHERE client_1='"+nickname+"' OR client_2='"+nickname+"' ORDER BY id DESC");
    while (query.next()) {
       QSqlRecord rec = query.record();
       QString client_1  = query.value(rec.indexOf("client_1")).toString();
       QString client_2 = query.value(rec.indexOf("client_2")).toString();
       QString id_dia = query.value(rec.indexOf("id")).toString();

       QSqlQuery quu;
       quu.exec("SELECT * FROM msg WHERE id_dia='"+id_dia+"' ORDER BY id DESC");
       quu.next();
       QSqlRecord re = quu.record();
       QString from_user = quu.value(re.indexOf("from_user")).toString();

       if(from_user != nickname) {
          quu.exec("SELECT * FROM users WHERE login='"+from_user+"'");
          quu.next();
          QSqlRecord re = quu.record();
          QString hash = quu.value(re.indexOf("hash")).toString();
          Crypter::setSecretkey(hash);
       } else {
           quu.exec("SELECT * FROM users WHERE login='"+nickname+"'");
           quu.next();
           QSqlRecord re = quu.record();
           QString hash = quu.value(re.indexOf("hash")).toString();
           Crypter::setSecretkey(hash);
       }

       QString last_msg = query.value(rec.indexOf("last_msg")).toString();

       msg_array << last_msg;

       last_msg = Crypter::decryptString(last_msg);

       if (client_1 == nickname) {
            ui->dialogs->setStyleSheet("QListWidget::item { border-bottom: 1px solid #eaeaea; color: black; }");
            ui->dialogs->addItem(client_2 + "\n" + last_msg);
       } else {
         ui->dialogs->setStyleSheet("QListWidget::item { border-bottom: 1px solid #eaeaea; color: black; }");
         ui->dialogs->addItem(client_1 + "\n" + last_msg);
       }
    }
    sql_1.set_msg_array(msg_array);
}

void Glavnaya::add()
{

    QSqlQuery query;

    QSqlQuery pdo_dia;
    pdo_dia.exec("SELECT * FROM dialogs WHERE ((client_1='"+username+"' and client_2='"+nickname+"') or (client_1='"+nickname+"' and client_2='"+username+"'))");
    pdo_dia.next();
    QSqlRecord pdo_dia_rec = pdo_dia.record();
    QString id_dia  = pdo_dia.value(pdo_dia_rec.indexOf("id")).toString();

    query.exec("SELECT * FROM msg WHERE id_dia='"+id_dia+"' ORDER BY id DESC");
    query.next();
    QSqlRecord rec = query.record();
    QString id_msg  = query.value(rec.indexOf("id")).toString();
    QString from_user  = query.value(rec.indexOf("from_user")).toString();
    QString to_user = query.value(rec.indexOf("to_user")).toString();

    QSqlQuery qu;
    QString his_msg_id  = query.value(rec.indexOf("id_msg")).toString();
    QSqlQuery pdo;
    pdo.exec("SELECT * FROM msg_text WHERE id='"+his_msg_id+"'");
    pdo.next();
    QString his_msg = pdo.value(1).toString();

    qu.exec("SELECT * FROM users WHERE login='"+username+"'");
    qu.next();
    QSqlRecord r = qu.record();
    QString his_hash = qu.value(r.indexOf("hash")).toString();
    Crypter::setSecretkey(his_hash);
    his_msg = Crypter::decryptString(his_msg);
    if (from_user != nickname) {

        QHBoxLayout *hl = new QHBoxLayout(this);
        QLabel *msg = new QLabel(this);
        QPushButton *saveposition = new QPushButton(this);
        saveposition->setStyleSheet("QPushButton{background:transparent;}");
        msg->setText(his_msg);
        msg->setStyleSheet("QLabel{"
                                  "background: #FFF;"
                                  "border-width: 2px;"
                                  "border-style: solid;"
                                  "border-color: #EAEAEA;"
                                  "border-top-left-radius: 6px;"
                                  "border-top-right-radius: 6px;"
                                  "border-bottom-right-radius: 6px;"
                                  "border-bottom-left-radius: 6px;"
                                  "}");
        msg->setAlignment(Qt::AlignRight);
        hl->addStretch(0);
        hl->addWidget(msg);
        hl->addStretch(10);
        hl->addWidget(saveposition);
        ui->verticalLayout_3->addLayout(hl);
        ui->verticalLayout_3->addSpacing(10);

        query.exec("UPDATE msg SET isReaded='1' WHERE from_user='"+username+"' and to_user='"+nickname+"'");
    }
}

void Glavnaya::adddialog(QString user)
{
    std::string nick = user.toStdString();
    _login = nick.c_str();

    QSqlQuery query;
    query.exec("SELECT * FROM users WHERE login='"+_login+"'");
    if (query.last() == false) {
        QMessageBox::warning(this,"Ошибка!","Проверьте корректность заполненных данных!");
        find = new finder();
        find->show();
    } else {
    ui->pushButton_2->setEnabled(true);
   // ui->msg->setEnabled(true);
    ui->stroka->setEnabled(true);
    ui->stroka_name->setEnabled(true);
    //ui->msg->clear();
    ui->stroka_name->clear();

    query.exec("SELECT * FROM zaprosy WHERE login='"+_login+"' ORDER BY id DESC");
    query.next();
    QSqlRecord rec = query.record();
    QString date = query.value(rec.indexOf("date")).toString();
    QString time = query.value(rec.indexOf("time")).toString();

    QDate date_now;
    QDate date_;
    date_now = date_now.currentDate();
    date_ = date_.fromString(date, "yyyy-MM-dd");

    QTime time_now;
    time_now = time_now.currentTime();
    if (date_now != date_) {
        ui->stroka_name->setText(_login);
    } else {
        QTime time_;
        time_ = time_.fromString(time);
        time_ = time_.addSecs(300);
        if (time_now > time_) {
            ui->stroka_name->setText(_login);
        } else {
            ui->stroka_name->setText(_login);
        }
    }
    find_nick = 1;
}
}

void Glavnaya::upd()
{
    //ui->msg->clear();

    QSqlQuery pdo_dia;
    pdo_dia.exec("SELECT * FROM dialogs WHERE ((client_1='"+username+"' and client_2='"+nickname+"') or (client_1='"+nickname+"' and client_2='"+username+"'))");
    pdo_dia.next();
    QSqlRecord pdo_dia_rec = pdo_dia.record();
    QString id_dia  = pdo_dia.value(pdo_dia_rec.indexOf("id")).toString();
    sql_2.set_id_dia(id_dia);

    QSqlQuery query;
    query.exec("UPDATE msg SET isReaded='1' WHERE from_user='"+username+"' and to_user='"+nickname+"'");

    query.exec("SELECT * FROM msg WHERE id_dia='"+id_dia+"' and from_user='"+username+"' ORDER BY id DESC");
    query.next();
    QSqlRecord recc = query.record();
    QString msg_last_id = query.value(recc.indexOf("id")).toString();
    sql_2.set_id_msg(msg_last_id);


    query.exec("SELECT * FROM msg WHERE id_dia='"+id_dia+"' ORDER BY id ASC");
    while (query.next()) {
          QSqlRecord rec = query.record();
          QString id_msg  = query.value(rec.indexOf("id")).toString();
          QString from_user  = query.value(rec.indexOf("from_user")).toString();
          QString to_user = query.value(rec.indexOf("to_user")).toString();
          QSqlQuery qu;

          if ((from_user == username) and (from_user != nickname)) {
             QString his_msg_id  = query.value(rec.indexOf("id_msg")).toString();

             QSqlQuery pdo;
             pdo.exec("SELECT * FROM msg_text WHERE id='"+his_msg_id+"'");
             pdo.next();
             QString his_msg = pdo.value(1).toString();

             qu.exec("SELECT * FROM users WHERE login='"+username+"'");
             qu.next();
             QSqlRecord r = qu.record();
             QString his_hash = qu.value(r.indexOf("hash")).toString();
             Crypter::setSecretkey(his_hash);
             his_msg = Crypter::decryptString(his_msg);

             QHBoxLayout *hl = new QHBoxLayout(this);
             QLabel *msg = new QLabel(this);
             QPushButton *saveposition = new QPushButton(this);
             saveposition->setStyleSheet("QPushButton{background:transparent;}");
             msg->setText(his_msg);
             msg->setStyleSheet("QLabel{"
                                       "background: #FFF;"
                                       "border-width: 2px;"
                                       "border-style: solid;"
                                       "border-color: #EAEAEA;"
                                       "border-top-left-radius: 6px;"
                                       "border-top-right-radius: 6px;"
                                       "border-bottom-right-radius: 6px;"
                                       "border-bottom-left-radius: 6px;"
                                       "}");
             msg->setAlignment(Qt::AlignRight);
             hl->addStretch(0);
             hl->addWidget(msg);
             hl->addStretch(10);
             hl->addWidget(saveposition);
             ui->verticalLayout_3->addLayout(hl);
             ui->verticalLayout_3->addSpacing(10);

          } else {
            QString my_msg_id  = query.value(rec.indexOf("id_msg")).toString();
            QSqlQuery pdo;
            pdo.exec("SELECT * FROM msg_text WHERE id='"+my_msg_id+"'");
            pdo.next();
            QString my_msg = pdo.value(1).toString();

            qu.exec("SELECT * FROM users WHERE login='"+nickname+"'");
            qu.next();
            QSqlRecord r = qu.record();
            QString my_hash = qu.value(r.indexOf("hash")).toString();
            Crypter::setSecretkey(my_hash);
            my_msg = Crypter::decryptString(my_msg);
            QString isReaded = query.value(rec.indexOf("isReaded")).toString();
            if (isReaded == "0") {

                QHBoxLayout *hl = new QHBoxLayout(this);
                QLabel *msg = new QLabel(this);
                QLabel *znak = new QLabel(this);
                QPushButton *saveposition = new QPushButton(this);
                saveposition->setStyleSheet("QPushButton{background:transparent;}");
                msg->setText(my_msg);
                znak->setText(" . ");
                znak->setStyleSheet("QLabel { font-size: 10px; }");
                msg->setStyleSheet("QLabel{"
                                          "background: #EAEAEA;"
                                          "border-width: 2px;"
                                          "border-style: solid;"
                                          "border-color: #EAEAEA;"
                                          "border-top-left-radius: 6px;"
                                          "border-top-right-radius: 6px;"
                                          "border-bottom-right-radius: 6px;"
                                          "border-bottom-left-radius: 6px;"
                                          "}");
                znak->setAlignment(Qt::AlignBaseline);
                msg->setAlignment(Qt::AlignRight);
                hl->addStretch(0);
                hl->addWidget(saveposition);
                hl->addStretch(10);
                hl->addWidget(msg);
                hl->addWidget(znak);
                ui->verticalLayout_3->addLayout(hl);
                ui->verticalLayout_3->addSpacing(10);
            } else {

                QHBoxLayout *hl = new QHBoxLayout(this);
                QLabel *msg = new QLabel(this);
                QPushButton *saveposition = new QPushButton(this);
                saveposition->setStyleSheet("QPushButton{background:transparent;}");
                msg->setText(my_msg);
                msg->setStyleSheet("QLabel{"
                                          "background: #EAEAEA;"
                                          "border-width: 2px;"
                                          "border-style: solid;"
                                          "border-color: #EAEAEA;"
                                          "border-top-left-radius: 6px;"
                                          "border-top-right-radius: 6px;"
                                          "border-bottom-right-radius: 6px;"
                                          "border-bottom-left-radius: 6px;"
                                          "}");
                msg->setAlignment(Qt::AlignRight);
                hl->addStretch(0);
                hl->addWidget(saveposition);
                hl->addStretch(10);
                hl->addWidget(msg);
                ui->verticalLayout_3->addLayout(hl);
                ui->verticalLayout_3->addSpacing(10);
            }
            }
   }

}

Glavnaya::~Glavnaya()
{
    delete ui;
}

void Glavnaya::keyPressEvent(QKeyEvent *event){
    qDebug() << event->key();
    if(event->key()==16777221) Glavnaya::on_pushButton_2_clicked();
    if(event->key()==16777220) Glavnaya::on_pushButton_2_clicked();
}

void Glavnaya::mousePressEvent(QMouseEvent *event) {
    QDesktopWidget * screen = QApplication::desktop();
    screen->availableGeometry();
    temp_sizey=0;
    sizew=Glavnaya::size().width();
    sizey=Glavnaya::size().height();
    posx=Glavnaya::pos().x();
    posy=Glavnaya::pos().y();
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
    side=0;
    block =false;
    temp_sizey = posy+sizey;
    temp_sizew = posx+sizew;
   if(event->button() == Qt::LeftButton && m_nMouseClick_Y_Coordinate<20 && m_nMouseClick_Y_Coordinate > 2 && m_nMouseClick_X_Coordinate > 2 && m_nMouseClick_X_Coordinate < Glavnaya::size().width()-2)
        {
           {
           if(checkfull == false)
               {
                 checkmouse = true;
               }

           }

        }
    else checkmouse = false;
   if(event->button() == Qt::LeftButton &&  m_nMouseClick_Y_Coordinate <= 3 && m_nMouseClick_X_Coordinate > 3 && m_nMouseClick_X_Coordinate < Glavnaya::size().width()-3)
   {
       side=1;
       checkmouse=false;
       qDebug()<<"only up";
   }
   if(event->button() == Qt::LeftButton &&  m_nMouseClick_X_Coordinate <= 3 && m_nMouseClick_Y_Coordinate > 3 && m_nMouseClick_Y_Coordinate < Glavnaya::size().height()-3)
   {
       side=2;
       checkmouse=false;
       qDebug()<<"only left";
   }
   if(event->button() == Qt::LeftButton &&  m_nMouseClick_Y_Coordinate > 3 && m_nMouseClick_Y_Coordinate < Glavnaya::size().height()-3 && m_nMouseClick_X_Coordinate > Glavnaya::size().width()-3)
   {
       side=3;
       checkmouse=false;
       qDebug()<<"only right";
   }
   if(event->button() == Qt::LeftButton &&  m_nMouseClick_X_Coordinate > 3 && m_nMouseClick_X_Coordinate < Glavnaya::size().width()-3 && m_nMouseClick_Y_Coordinate > Glavnaya::size().height()-3)
   {
       side=4;
       checkmouse=false;
       qDebug()<<"only down";
   }
}

void Glavnaya::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        checkmouse = false;
    }
    return QWidget::mouseReleaseEvent(event);
}

void Glavnaya::mouseMoveEvent(QMouseEvent *event)
{
    QDesktopWidget * screen = QApplication::desktop();
    screen->availableGeometry();

    if (checkmouse == false)
    {
        int temp_sizeww=Glavnaya::size().width();
        int temp_sizeyy=Glavnaya::size().height();
        int temp_posx=Glavnaya::pos().x();
        int temp_posy=Glavnaya::pos().y();
        qDebug()<<posy<<"TEMP";

        qDebug()<<temp_posy+temp_sizeyy<<"SUKA TEMP";
        switch(side)
        {
            case 1:

                if (temp_sizey!=temp_posy+temp_sizeyy && temp_sizey!=temp_posy+temp_sizeyy-1 && temp_sizey!=temp_posy+temp_sizeyy-2 && temp_sizey-temp_posy+temp_sizeyy-3)
                {
                    block=true;
                    qDebug()<<"BLOCK";
                    setGeometry(posx,temp_posy,sizew,temp_sizeyy);
                }
                if (block==true)
                {
                    if(event->globalY()-temp_posy<=0)
                    {
                        block=false;
                    }
                }
                if (block==false)
                {
                    setGeometry(posx,event->globalY(),sizew,temp_sizey-event->globalY());
                    block =false;
                }
                qDebug() << temp_sizeyy;
                qDebug()<<temp_posy;

                break;

        case 2:
                if (temp_sizew!=temp_posx+temp_sizeww && temp_sizew!=temp_posx+temp_sizeww-1 && temp_sizew!=temp_posx+temp_sizeww-2 && temp_sizew-temp_posx+temp_sizeww-3)
                {
                    block=true;
                    qDebug()<<"BLOCK";
                    setGeometry(temp_posx,posy,temp_sizeww,sizey);
                }
                if (block==true)
                {
                    if(event->globalX()-temp_posx<=0)
                    {
                        block=false;
                    }
                }
                if (block==false)
                {
                    setGeometry(event->globalX(),posy,temp_sizew-event->globalX(),sizey);
                    block =false;
                }


                break;
        case 3:
            setGeometry(posx,posy,event->globalX()-posx,sizey);
            block =false;
            qDebug()<<event->globalY()<<"MOUSE";
            break;
        case 4:
                setGeometry(posx,posy,sizew,event->globalY()-posy);
                block =false;
                qDebug()<<event->globalY()<<"MOUSE";
        default:
            break;
        }
    }

    if (checkmouse == true){
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
    //qDebug() << (event->globalX()-m_nMouseClick_X_Coordinate);
    }

}

void Glavnaya::on_exitbutton_clicked()
{

    exit(0);
}

void Glavnaya::mouseDoubleClickEvent(QMouseEvent *event)
{
    Glavnaya::on_fullscreen_clicked();
}

void Glavnaya::on_fullscreen_clicked()
{
    QDesktopWidget * screen = QApplication::desktop();
    checkmouse = false;
    screen->availableGeometry();
    if(m_nMouseClick_Y_Coordinate<20)
        {
        if (Glavnaya::size().width()==screen->availableGeometry().width() && Glavnaya::size().height()==screen->availableGeometry().height() )
        {
            Glavnaya::setGeometry(posx,posy,sizew,sizey);
            checkfull=false;
        }
        else
        {
            sizew=Glavnaya::size().width();
            sizey=Glavnaya::size().height();
            posx=Glavnaya::pos().x();
            posy=Glavnaya::pos().y();
            Glavnaya::setGeometry(0,0,screen->availableGeometry().width(),screen->availableGeometry().height());
            checkfull=true;
        }
        }
}

void Glavnaya::on_Mini_clicked()
{
    Glavnaya::showMinimized();
}

void Glavnaya::on_dialogs_itemClicked(QListWidgetItem *item)
{
    ui->pushButton_2->setEnabled(TRUE);
    ui->stroka->setEnabled(TRUE);
    ui->stroka_name->setEnabled(TRUE);
    ui->stroka_name->clear();
    ui->nameandsettings->setStyleSheet("QWidget#nameandsettings{"
                                       "background-color:white"
                                       "}");
    ui->msgandphoto->setStyleSheet("QWidget#msgandphoto{"
                                       "background-color:white"
                                       "}");
    QSqlQuery query;

    QStringList dialog = item->text().split("\n");
    username = dialog.first();

    query.exec("UPDATE msg SET isReaded='1' WHERE from_user='"+username+"' and to_user='"+nickname+"'");

    query.exec("SELECT * FROM zaprosy WHERE login='"+username+"' ORDER BY id DESC");
    query.next();
    QSqlRecord rec = query.record();
    QString date = query.value(rec.indexOf("date")).toString();
    QString time = query.value(rec.indexOf("time")).toString();

    QDate date_now;
    QDate date_;
    date_now = date_now.currentDate();
    date_ = date_.fromString(date, "yyyy-MM-dd");

    QTime time_now;
    time_now = time_now.currentTime();
    if (date_now != date_) {
        ui->stroka_name->setText(username);
    } else {
        QTime time_;
        time_ = time_.fromString(time);
        time_ = time_.addSecs(300);
        if (time_now > time_) {
            ui->stroka_name->setText(username);
        } else {
            ui->stroka_name->setText(username);
        }
    }


    QSqlQuery pdo_dia;
    pdo_dia.exec("SELECT * FROM dialogs WHERE ((client_1='"+username+"' and client_2='"+nickname+"') or (client_1='"+nickname+"' and client_2='"+username+"'))");
    pdo_dia.next();
    QSqlRecord pdo_dia_rec = pdo_dia.record();
    QString id_dia  = pdo_dia.value(pdo_dia_rec.indexOf("id")).toString();
    sql_2.set_id_dia(id_dia);

    query.exec("SELECT * FROM msg WHERE id_dia='"+id_dia+"' and from_user='"+username+"' ORDER BY id DESC");
    query.next();
    QSqlRecord recc = query.record();
    QString msg_last_id = query.value(recc.indexOf("id")).toString();
    sql_2.set_id_msg(msg_last_id);


    query.exec("SELECT * FROM msg WHERE id_dia='"+id_dia+"' ORDER BY id ASC");
    while (query.next()) {
          QSqlRecord rec = query.record();
          QString id_msg  = query.value(rec.indexOf("id")).toString();
          QString from_user  = query.value(rec.indexOf("from_user")).toString();
          QString to_user = query.value(rec.indexOf("to_user")).toString();
          QSqlQuery qu;

          if ((from_user == username) and (from_user != nickname)) {
             QString his_msg_id  = query.value(rec.indexOf("id_msg")).toString();

             QSqlQuery pdo;
             pdo.exec("SELECT * FROM msg_text WHERE id='"+his_msg_id+"'");
             pdo.next();
             QString his_msg = pdo.value(1).toString();

             qu.exec("SELECT * FROM users WHERE login='"+username+"'");
             qu.next();
             QSqlRecord r = qu.record();
             QString his_hash = qu.value(r.indexOf("hash")).toString();
             Crypter::setSecretkey(his_hash);
             his_msg = Crypter::decryptString(his_msg);

             QHBoxLayout *hl = new QHBoxLayout(this);
             QLabel *msg = new QLabel(this);
             QPushButton *saveposition = new QPushButton(this);
             saveposition->setStyleSheet("QPushButton{background:transparent;}");
             msg->setText(his_msg);
             msg->setStyleSheet("QLabel{"
                                       "background: #FFF;"
                                       "border-width: 2px;"
                                       "border-style: solid;"
                                       "border-color: #EAEAEA;"
                                       "border-top-left-radius: 6px;"
                                       "border-top-right-radius: 6px;"
                                       "border-bottom-right-radius: 6px;"
                                       "border-bottom-left-radius: 6px;"
                                       "}");
             msg->setAlignment(Qt::AlignRight);
             hl->addStretch(0);
             hl->addWidget(msg);
             hl->addStretch(10);
             hl->addWidget(saveposition);
             ui->verticalLayout_3->addLayout(hl);
             ui->verticalLayout_3->addSpacing(10);

          } else {
            QString my_msg_id  = query.value(rec.indexOf("id_msg")).toString();
            QSqlQuery pdo;
            pdo.exec("SELECT * FROM msg_text WHERE id='"+my_msg_id+"'");
            pdo.next();
            QString my_msg = pdo.value(1).toString();

            qu.exec("SELECT * FROM users WHERE login='"+nickname+"'");
            qu.next();
            QSqlRecord r = qu.record();
            QString my_hash = qu.value(r.indexOf("hash")).toString();
            Crypter::setSecretkey(my_hash);
            my_msg = Crypter::decryptString(my_msg);
            QString isReaded = query.value(rec.indexOf("isReaded")).toString();
            if (isReaded == "0") {
                QHBoxLayout *hl = new QHBoxLayout(this);
                QLabel *msg = new QLabel(this);
                QLabel *znak = new QLabel(this);
                QPushButton *saveposition = new QPushButton(this);
                saveposition->setStyleSheet("QPushButton{background:transparent;}");
                msg->setText(my_msg);
                znak->setText(" . ");
                znak->setStyleSheet("QLabel { font-size: 10px; }");
                msg->setStyleSheet("QLabel{"
                                          "background: #EAEAEA;"
                                          "border-width: 2px;"
                                          "border-style: solid;"
                                          "border-color: #EAEAEA;"
                                          "border-top-left-radius: 6px;"
                                          "border-top-right-radius: 6px;"
                                          "border-bottom-right-radius: 6px;"
                                          "border-bottom-left-radius: 6px;"
                                          "}");
                znak->setAlignment(Qt::AlignBaseline);
                msg->setAlignment(Qt::AlignRight);
                hl->addStretch(0);
                hl->addWidget(saveposition);
                hl->addStretch(10);
                hl->addWidget(msg);
                hl->addWidget(znak);
                ui->verticalLayout_3->addLayout(hl);
                ui->verticalLayout_3->addSpacing(10);

            } else {
                QHBoxLayout *hl = new QHBoxLayout(this);
                QLabel *msg = new QLabel(this);
                QPushButton *saveposition = new QPushButton(this);
                saveposition->setStyleSheet("QPushButton{background:transparent;}");
                msg->setText(my_msg);
                msg->setStyleSheet("QLabel{"
                                          "background: #EAEAEA;"
                                          "border-width: 2px;"
                                          "border-style: solid;"
                                          "border-color: #EAEAEA;"
                                          "border-top-left-radius: 6px;"
                                          "border-top-right-radius: 6px;"
                                          "border-bottom-right-radius: 6px;"
                                          "border-bottom-left-radius: 6px;"
                                          "}");
                msg->setAlignment(Qt::AlignRight);
                hl->addStretch(0);
                hl->addWidget(saveposition);
                hl->addStretch(10);
                hl->addWidget(msg);
                ui->verticalLayout_3->addLayout(hl);
                ui->verticalLayout_3->addSpacing(10);
            }
            }
   }

  connect(&thread_2, &QThread::started, &sql_2, &sql_query2::checker);
  sql_2.moveToThread(&thread_2);
  sql_2.setRunning(true);
  thread_2.start();
}

void Glavnaya::on_pushButton_2_clicked()
{
    QString msgg = ui->stroka->document()->toPlainText();
    if (msgg != "") {
        if (find_nick == 1) {
            QSqlQuery qu;
            qu.exec("SELECT * FROM users WHERE login='"+nickname+"'");
            qu.next();
            QSqlRecord r = qu.record();
            QString my_hash = qu.value(r.indexOf("hash")).toString();

            QHBoxLayout *hl = new QHBoxLayout(this);
            QLabel *msg = new QLabel(this);
            QLabel *znak = new QLabel(this);
            QPushButton *saveposition = new QPushButton(this);
            saveposition->setStyleSheet("QPushButton{background:transparent;}");
            msg->setText(msgg);
            znak->setText(" . ");
            znak->setStyleSheet("QLabel { font-size: 10px; }");
            msg->setStyleSheet("QLabel{"
                                      "background: #EAEAEA;"
                                      "border-width: 2px;"
                                      "border-style: solid;"
                                      "border-color: #EAEAEA;"
                                      "border-top-left-radius: 6px;"
                                      "border-top-right-radius: 6px;"
                                      "border-bottom-right-radius: 6px;"
                                      "border-bottom-left-radius: 6px;"
                                      "}");
            znak->setAlignment(Qt::AlignBaseline);
            msg->setAlignment(Qt::AlignRight);
            hl->addStretch(0);
            hl->addWidget(saveposition);
            hl->addStretch(10);
            hl->addWidget(msg);
            hl->addWidget(znak);
            ui->verticalLayout_3->addLayout(hl);
            ui->verticalLayout_3->addSpacing(10);

            Crypter::setSecretkey(my_hash);
            msgg = Crypter::cryptString(msgg);
            QSqlQuery query;
            query.prepare("INSERT INTO dialogs (client_1, client_2, last_msg) "
                      "VALUES (?, ?, ?)");
               query.addBindValue(nickname);
               query.addBindValue(_login);
               query.addBindValue(msgg);
               query.exec();
            username = _login;
            query.exec("SELECT * FROM dialogs WHERE ((client_1='"+username+"' and client_2='"+nickname+"') or (client_1='"+nickname+"' and client_2='"+username+"'))");
            query.next();
            QString id_dia = query.value(0).toString();
            sql_4.set_id_dia(id_dia);
            query.prepare("INSERT INTO msg_text (text) "
                              "VALUES (?)");
                       query.addBindValue(msgg);
                       query.exec();
            query.exec("SELECT * FROM msg_text WHERE text='"+msgg+"'");
            query.next();
            QString id_msg = query.value(0).toString();
            QDateTime datetime;
            QDateTime date = datetime.currentDateTime();
            query.prepare("INSERT INTO msg (id_dia, from_user, to_user, id_msg, date) "
                      "VALUES (?, ?, ?, ?, ?)");
               query.addBindValue(id_dia);
               query.addBindValue(nickname);
               query.addBindValue(username);
               query.addBindValue(id_msg);
               query.addBindValue(date);
               query.exec();
            query.exec("SELECT * FROM msg WHERE from_user='"+nickname+"' AND to_user='"+username+"' ORDER BY id DESC");
            query.next();
            QSqlRecord rec = query.record();
            QString status = query.value(rec.indexOf("isReaded")).toString();
            sql_4.set_status(status);
            connect(&thread_4, &QThread::started, &sql_4, &sql_query4::checker);
            sql_4.moveToThread(&thread_4);
            sql_4.setRunning(true);
            thread_4.start();
            ui->stroka->document()->setPlainText("");
            find_nick = 2;
        } else {
        QSqlQuery qu;
        qu.exec("SELECT * FROM users WHERE login='"+nickname+"'");
        qu.next();
        QSqlRecord r = qu.record();
        QString my_hash = qu.value(r.indexOf("hash")).toString();

        QHBoxLayout *hl = new QHBoxLayout(this);
        QLabel *msg = new QLabel(this);
        QLabel *znak = new QLabel(this);
        QPushButton *saveposition = new QPushButton(this);
        saveposition->setStyleSheet("QPushButton{background:transparent;}");
        msg->setText(msgg);
        znak->setText(" . ");
        znak->setStyleSheet("QLabel { font-size: 10px; }");
        msg->setStyleSheet("QLabel{"
                                  "background: #EAEAEA;"
                                  "border-width: 2px;"
                                  "border-style: solid;"
                                  "border-color: #EAEAEA;"
                                  "border-top-left-radius: 6px;"
                                  "border-top-right-radius: 6px;"
                                  "border-bottom-right-radius: 6px;"
                                  "border-bottom-left-radius: 6px;"
                                  "}");
        znak->setAlignment(Qt::AlignBaseline);
        msg->setAlignment(Qt::AlignRight);
        hl->addStretch(0);
        hl->addWidget(saveposition);
        hl->addStretch(10);
        hl->addWidget(msg);
        hl->addWidget(znak);
        ui->verticalLayout_3->addLayout(hl);
        ui->verticalLayout_3->addSpacing(10);

        Crypter::setSecretkey(my_hash);
        msgg = Crypter::cryptString(msgg);
        QSqlQuery query;
        query.exec("SELECT * FROM dialogs WHERE ((client_1='"+username+"' and client_2='"+nickname+"') or (client_1='"+nickname+"' and client_2='"+username+"'))");
        query.next();
        QString id_dia = query.value(0).toString();
        sql_4.set_id_dia(id_dia);
        query.prepare("INSERT INTO msg_text (text) "
                          "VALUES (?)");
                   query.addBindValue(msgg);
                   query.exec();
        query.exec("SELECT * FROM msg_text WHERE text='"+msgg+"'");
        query.next();
        QString id_msg = query.value(0).toString();
        QDateTime datetime;
        QDateTime date = datetime.currentDateTime();
        query.prepare("INSERT INTO msg (id_dia, from_user, to_user, id_msg, date) "
                  "VALUES (?, ?, ?, ?, ?)");
           query.addBindValue(id_dia);
           query.addBindValue(nickname);
           query.addBindValue(username);
           query.addBindValue(id_msg);
           query.addBindValue(date);
           query.exec();
        query.exec("UPDATE dialogs SET last_msg='"+msgg+"' WHERE id='"+id_dia+"'");
        query.exec("SELECT * FROM msg WHERE from_user='"+nickname+"' AND to_user='"+username+"' ORDER BY id DESC");
        query.next();
        QSqlRecord rec = query.record();
        QString status = query.value(rec.indexOf("isReaded")).toString();
        sql_4.set_status(status);
        ui->stroka->document()->setPlainText("");
        if (find_nick != 2) {
        connect(&thread_4, &QThread::started, &sql_4, &sql_query4::checker);
        sql_4.moveToThread(&thread_4);
        sql_4.setRunning(true);
        thread_4.start();
        ui->stroka->document()->setPlainText("");
        find_nick = 0;

        }

    }
    }
   /* QFile("C:\\Users\\Xterlo\\AppData\\Local\\Temp\\file.txt").remove();
    encode_file_base64("C:\\Users\\Xterlo\\Pictures\\screenshot.png", "C:\\Users\\Xterlo\\AppData\\Local\\Temp\\file.txt");
    std::ifstream file;
    file.open("C:\\Users\\Xterlo\\AppData\\Local\\Temp\\file.txt", std::ios_base::in);
    std::string test_photo;
    file >> test_photo;
    file.close();
    QFile("C:\\Users\\Xterlo\\AppData\\Local\\Temp\\file.txt").remove();
    ui->msg->document()->setHtml(ui->msg->toHtml() + "<img src='data:image/png;base64,"+test_photo.c_str()+"' width='300' height='300' style='display: block;'>");
*/
}

void Glavnaya::on_openfinder_clicked()
{
    find->show();
}


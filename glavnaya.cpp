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
    ui->msg->setEnabled(FALSE);
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
        ui->msg->setHtml(ui->msg->toHtml() + "<p style='font-size: 10px;'>"+his_msg+"</p>");
        ui->msg->moveCursor(QTextCursor::End);
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
    ui->msg->setEnabled(true);
    ui->stroka->setEnabled(true);
    ui->stroka_name->setEnabled(true);
    ui->msg->clear();
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
        ui->stroka_name->setHtml(ui->stroka_name->toHtml() + "<span style='text-align: center; font-size: 12px;'>"+_login+" <content style='color: grey; font-size: 8px; text-align: center;'>&bull; Offline</content> </span>");
    } else {
        QTime time_;
        time_ = time_.fromString(time);
        time_ = time_.addSecs(300);
        if (time_now > time_) {
            ui->stroka_name->setHtml(ui->stroka_name->toHtml() + "<span style='text-align: center; font-size: 12px;'>"+_login+" <content style='color: grey; font-size: 8px; text-align: center;'>&bull; Offline</content> </span>");
        } else {
            ui->stroka_name->setHtml(ui->stroka_name->toHtml() + "<span style='text-align: center; font-size: 12px;'>"+_login+" <content style='color: green; font-size: 8px; text-align: center;'>&bull; Online</content> </span>");
        }
    }
    find_nick = 1;
}
}

void Glavnaya::upd()
{
    ui->msg->clear();

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
             ui->msg->setHtml(ui->msg->toHtml() + "<p style='font-size: 10px;'>"+his_msg+"</p></br>");
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
                ui->msg->setHtml(ui->msg->toHtml() + "<p style='text-align: right;font-size: 10px;'>"+my_msg+" <content style='color: grey; font-size: 10px;'>&bull;</content></p></br>");
            } else {
                ui->msg->setHtml(ui->msg->toHtml() + "<p style='text-align: right;font-size: 10px;'>"+my_msg+"</p></br>");
            }
            }
   }
ui->msg->moveCursor(QTextCursor::End);
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
    ui->msg->setEnabled(TRUE);
    ui->stroka->setEnabled(TRUE);
    ui->stroka_name->setEnabled(TRUE);
    ui->msg->clear();
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
        ui->stroka_name->setHtml(ui->stroka_name->toHtml() + "<span style='text-align: center; font-size: 12px;'>"+username+" <content style='color: grey; font-size: 8px; text-align: center;'>&bull; Offline</content> </span>");
    } else {
        QTime time_;
        time_ = time_.fromString(time);
        time_ = time_.addSecs(300);
        if (time_now > time_) {
            ui->stroka_name->setHtml(ui->stroka_name->toHtml() + "<span style='text-align: center; font-size: 12px;'>"+username+" <content style='color: grey; font-size: 8px; text-align: center;'>&bull; Offline</content> </span>");
        } else {
            ui->stroka_name->setHtml(ui->stroka_name->toHtml() + "<span style='text-align: center; font-size: 12px;'>"+username+" <content style='color: green; font-size: 8px; text-align: center;'>&bull; Online</content> </span>");
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
             ui->msg->setHtml(ui->msg->toHtml() + "<p style='font-size: 10px;'>"+his_msg+"</p></br>");
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
                ui->msg->setHtml(ui->msg->toHtml() + "<p style='text-align: right;font-size: 10px;'>"+my_msg+" <content style='color: grey; font-size: 10px;'>&bull;</content></p></br>");

            } else {
                ui->msg->setHtml(ui->msg->toHtml() + "<p style='text-align: right;font-size: 10px;'>"+my_msg+"</p></br>");
            }
            }
   }
  ui->msg->moveCursor(QTextCursor::End);
  connect(&thread_2, &QThread::started, &sql_2, &sql_query2::checker);
  sql_2.moveToThread(&thread_2);
  sql_2.setRunning(true);
  thread_2.start();
}

void Glavnaya::on_pushButton_2_clicked()
{
    QString msg = ui->stroka->document()->toPlainText();
    if (msg != "") {
        if (find_nick == 1) {
            QSqlQuery qu;
            qu.exec("SELECT * FROM users WHERE login='"+nickname+"'");
            qu.next();
            QSqlRecord r = qu.record();
            QString my_hash = qu.value(r.indexOf("hash")).toString();
            ui->msg->setHtml(ui->msg->toHtml() + "<p style='text-align: right;font-size: 10px;'>"+msg+" <content style='color: grey; font-size: 10px;'>&bull;</content></p></br>");
            ui->msg->moveCursor(QTextCursor::End);
            Crypter::setSecretkey(my_hash);
            msg = Crypter::cryptString(msg);
            QSqlQuery query;
            query.prepare("INSERT INTO dialogs (client_1, client_2, last_msg) "
                      "VALUES (?, ?, ?)");
               query.addBindValue(nickname);
               query.addBindValue(_login);
               query.addBindValue(msg);
               query.exec();
            username = _login;
            query.exec("SELECT * FROM dialogs WHERE ((client_1='"+username+"' and client_2='"+nickname+"') or (client_1='"+nickname+"' and client_2='"+username+"'))");
            query.next();
            QString id_dia = query.value(0).toString();
            sql_4.set_id_dia(id_dia);
            query.prepare("INSERT INTO msg_text (text) "
                              "VALUES (?)");
                       query.addBindValue(msg);
                       query.exec();
            query.exec("SELECT * FROM msg_text WHERE text='"+msg+"'");
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

        ui->msg->document()->setHtml(ui->msg->toHtml() + "<p style='text-align: right;font-size: 10px;'>"+msg+" <content style='color: grey; font-size: 10px;'>&bull;</content></p></br>");
        ui->msg->setHtml(ui->msg->toHtml()+"<img alt='Scan me!' src='data:image/png;base64,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' style='display: block;'>");
        ui->msg->moveCursor(QTextCursor::End);
        Crypter::setSecretkey(my_hash);
        msg = Crypter::cryptString(msg);
        QSqlQuery query;
        query.exec("SELECT * FROM dialogs WHERE ((client_1='"+username+"' and client_2='"+nickname+"') or (client_1='"+nickname+"' and client_2='"+username+"'))");
        query.next();
        QString id_dia = query.value(0).toString();
        sql_4.set_id_dia(id_dia);
        query.prepare("INSERT INTO msg_text (text) "
                          "VALUES (?)");
                   query.addBindValue(msg);
                   query.exec();
        query.exec("SELECT * FROM msg_text WHERE text='"+msg+"'");
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
        query.exec("UPDATE dialogs SET last_msg='"+msg+"' WHERE id='"+id_dia+"'");
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
}

void Glavnaya::on_openfinder_clicked()
{
    find->show();
}


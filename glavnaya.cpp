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
static QString nickname;
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
}
void Glavnaya::on_exitbutton_clicked()
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
}
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
   QSqlQuery query;
       query.exec("SELECT * FROM dialogs WHERE client_1='"+nickname+"' OR client_2='"+nickname+"'");
       qDebug() << query.last();
       while (query.next()) {
          QSqlRecord rec = query.record();
          QString client_1  = query.value(rec.indexOf("client_1")).toString();
          QString client_2 = query.value(rec.indexOf("client_2")).toString();
          if (client_1 == nickname) {
               QString last_msg  = query.value(rec.indexOf("last_msg")).toString();
               qDebug()<<last_msg;
               //ui->dialogs->addItem(client_2 + "\n" + last_msg);
          }

      }
}
Glavnaya::~Glavnaya()
{
    delete ui;
}


void Glavnaya::mousePressEvent(QMouseEvent *event) {
    QDesktopWidget * screen = QApplication::desktop();
    screen->availableGeometry();
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
    if(event->button() == Qt::LeftButton && m_nMouseClick_Y_Coordinate<20)
        {
           {
           if(checkfull == false)
               {
                 checkmouse = true;
               }

           }

        }
    else checkmouse = false;

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
    if (checkmouse == true){
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);}

}

/*void Glavnaya::on_exitbutton_clicked()
{

    exit(0);
}*/

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

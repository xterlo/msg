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

static QString nickname;
static QString username;
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




}
void Glavnaya::asd()
{
    qDebug()<<"123";
    Sleep(100);
    QString Qnick = nickname;
    ui->msg->clear();
    Glavnaya::recieveData(Qnick);




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
   while (query.next()) {
      QSqlRecord rec = query.record();
      QString client_1  = query.value(rec.indexOf("client_1")).toString();
      QString client_2 = query.value(rec.indexOf("client_2")).toString();
      if (client_1 == nickname) {
           QString last_msg  = query.value(rec.indexOf("last_msg")).toString();
           ui->dialogs->setStyleSheet("QListWidget::item { border-bottom: 1px solid #eaeaea; color: black; }");
           ui->dialogs->addItem(client_2 + "\n" + last_msg);
      } else {
      QString last_msg  = query.value(rec.indexOf("last_msg")).toString();
      ui->dialogs->setStyleSheet("QListWidget::item { border-bottom: 1px solid #eaeaea; color: black; }");
      ui->dialogs->addItem(client_1 + "\n" + last_msg);
      }
      qDebug()<<"2";

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

void Glavnaya::on_dialogs_itemClicked(QListWidgetItem *item)
{
    MySelectedItem=ui->dialogs->currentRow();
    ui->pushButton_2->setEnabled(TRUE);
    ui->msg->setEnabled(TRUE);
    ui->stroka->setEnabled(TRUE);
    ui->msg->clear();

    QStringList dialog = item->text().split("\n");
    username = dialog.first();
    ui->msg->setHtml(ui->msg->toHtml() + "<span style='text-align: center; font-size: 12px;'>"+username+"</span>");

    QSqlQuery pdo_dia;
    pdo_dia.exec("SELECT * FROM dialogs WHERE ((client_1='"+username+"' and client_2='"+nickname+"') or (client_1='"+nickname+"' and client_2='"+username+"'))");
    pdo_dia.next();
    QSqlRecord pdo_dia_rec = pdo_dia.record();
    QString id_dia  = pdo_dia.value(pdo_dia_rec.indexOf("id")).toString();

    QSqlQuery query;
    query.exec("SELECT * FROM msg WHERE id_dia='"+id_dia+"' ORDER BY id ASC");
    while (query.next()) {
          QSqlRecord rec = query.record();
          QString from_user  = query.value(rec.indexOf("from_user")).toString();
          QString to_user = query.value(rec.indexOf("to_user")).toString();
          if ((from_user == username) and (from_user != nickname)) {
             QString his_msg_id  = query.value(rec.indexOf("id_msg")).toString();

             QSqlQuery pdo;
             pdo.exec("SELECT * FROM msg_text WHERE id='"+his_msg_id+"'");
             pdo.next();
             QString his_msg = pdo.value(1).toString();

             ui->msg->setHtml(ui->msg->toHtml() + "<span style='font-size: 10px;'>"+his_msg+"</span></br>");
          } else {
            QString my_msg_id  = query.value(rec.indexOf("id_msg")).toString();
            QSqlQuery pdo;
            pdo.exec("SELECT * FROM msg_text WHERE id='"+my_msg_id+"'");
            pdo.next();
            QString my_msg = pdo.value(1).toString();

            ui->msg->setHtml(ui->msg->toHtml() + "<span style='text-align: right;font-size: 10px;'>"+my_msg+"</span></br>");
            }
   }


}

void Glavnaya::on_pushButton_2_clicked()
{
    QString msg = ui->stroka->text();
    if (msg != "") {
        ui->msg->setHtml(ui->msg->toHtml() + "<span style='text-align: right;font-size: 10px;'>"+msg+"</span></br>");
        QSqlQuery query;
        query.exec("SELECT * FROM dialogs WHERE ((client_1='"+username+"' and client_2='"+nickname+"') or (client_1='"+nickname+"' and client_2='"+username+"'))");
        query.next();
        QString id_dia = query.value(0).toString();
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
        ui->stroka->setText("");
        Glavnaya::asd();

    }
}

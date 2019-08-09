#include "sql_query1.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QThread>
#include "windows.h"
#include "Crypter.h"
static QString msg_a;


sql_query1::sql_query1(QObject *parent) : QObject(parent)
{
}

bool sql_query1::running() const
{
    return m_running;
}
void sql_query1::recievenick(QString nick)
{
    std::string nickk = nick.toStdString();
    nickname = nickk.c_str();
}

void sql_query1::recieveid(QString id_d)
{
    std::string idd = id_d.toStdString();
    id = idd.c_str();
}

void sql_query1::recievemsg(QString msg)
{
    msg_a = msg;
}

void sql_query1::checker()
{
    Sleep(1000);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","db");
    db.setHostName("95.143.216.174");
    db.setPort(3306);
    db.setDatabaseName("server");
    db.setUserName("server");
    db.setPassword("server");
    db.open();
    while(m_running) {  
       QSqlQuery query(QSqlDatabase::database("db"));
       query.exec("SELECT * FROM dialogs WHERE client_1='"+nickname+"' OR client_2='"+nickname+"' ORDER BY id DESC");
       query.next();
       QSqlRecord rec = query.record();
       QString id_dia = query.value(rec.indexOf("id")).toString();
       QString last_msg = query.value(rec.indexOf("last_msg")).toString();
       if((id != id_dia) or (msg_a != last_msg)) {
           emit update();
           break;
       }
       query.next();
    }
    db.close();
    db.removeDatabase("db");
    reload();
}

void sql_query1::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(m_running);
}

void sql_query1::reload()
{
    sql_query1::checker();
}

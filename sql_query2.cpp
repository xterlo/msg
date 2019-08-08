#include "sql_query2.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlResult>
#include <QThread>
#include <QDebug>
#include "windows.h"

sql_query2::sql_query2(QObject *parent) : QObject(parent)
{

}

bool sql_query2::running() const
{
    return m_running;
}
void sql_query2::receiveid(QString idd)
{
    std::string id_d = idd.toStdString();
    id = id_d.c_str();
}

void sql_query2::receiveidd(QString idd)
{
    std::string id_d = idd.toStdString();
    id_msg = id_d.c_str();
}


void sql_query2::checker()
{
    Sleep(1000);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","db1");
    db.setHostName("95.143.216.174");
    db.setPort(3306);
    db.setDatabaseName("server");
    db.setUserName("server");
    db.setPassword("server");
    db.open();
    while(m_running) {
         QSqlQuery query(QSqlDatabase::database("db1"));
         query.exec("SELECT * FROM msg WHERE id_dia='"+id+"' ORDER BY id DESC");
         query.next();
         QSqlRecord rec = query.record();
         QString id_msg_last = query.value(rec.indexOf("id")).toString();
         if (id_msg != id_msg_last) {
             emit update();
             Sleep(200);
             break;
         }
    }
    db.close();
    db.removeDatabase("db1");
    int int_id = id_msg.toInt();
    int_id++;
    id_msg = QString::number(int_id);
    reload();
}

void sql_query2::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(m_running);
}

void sql_query2::reload()
{
    sql_query2::checker();
}

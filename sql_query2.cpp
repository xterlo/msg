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

QString sql_query2::id_dia() const
{
    return m_id_dia;
}

QString sql_query2::id_msg() const
{
    return m_id_msg;
}

void sql_query2::checker()
{
    Sleep(2000);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","db1");
    db.setHostName("95.143.216.174");
    db.setPort(3306);
    db.setDatabaseName("server");
    db.setUserName("server");
    db.setPassword("server");
    db.open();
    while(m_running) {
         QSqlQuery query(QSqlDatabase::database("db1"));
         query.exec("SELECT * FROM msg WHERE id_dia='"+m_id_dia+"' ORDER BY id DESC");
         query.next();
         QSqlRecord rec = query.record();
         QString id_msg_last = query.value(rec.indexOf("id")).toString();
         if (m_id_msg != id_msg_last) {
             emit update();
             break;
         }
    }
    db.close();
    db.removeDatabase("db1");
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

void sql_query2::set_id_dia(QString id_dia)
{
    m_id_dia = id_dia;
}

void sql_query2::set_id_msg(QString id_msg)
{
    m_id_msg = id_msg;
}

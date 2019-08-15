#include "sql_query4.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlResult>
#include <QDebug>

sql_query4::sql_query4(QObject *parent) : QObject(parent)
{

}

bool sql_query4::running() const
{
    return m_running;
}
void sql_query4::recieveid(QString idd)
{
    std::string id_d = idd.toStdString();
    id = id_d.c_str();
}

void sql_query4::recievenick(QString nick)
{
    std::string nickk = nick.toStdString();
    nickname = nickk.c_str();
}

void sql_query4::checker()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","db3");
    db.setHostName("95.143.216.174");
    db.setPort(3306);
    db.setDatabaseName("server");
    db.setUserName("server");
    db.setPassword("server");
    db.open();
    while(m_running) {
         QSqlQuery query(QSqlDatabase::database("db3"));
         query.exec("SELECT * FROM msg WHERE id_dia='"+id+"' ORDER BY id DESC");
         query.next();
         QSqlRecord rec = query.record();
         int isReaded = query.value(rec.indexOf("isReaded")).toInt();
         QString username = query.value(rec.indexOf("from_user")).toString();
         if ((isReaded == 1) and (username != nickname)) {
             emit update();
             break;
         }
    }
    db.close();
    db.removeDatabase("db3");
    reload();
}

void sql_query4::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(m_running);
}

void sql_query4::reload()
{
    sql_query4::checker();
}

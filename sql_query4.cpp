#include "sql_query4.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlResult>
#include <QDebug>
#include "windows.h"

sql_query4::sql_query4(QObject *parent) : QObject(parent)
{

}

bool sql_query4::running() const
{
    return m_running;
}

QString sql_query4::status() const
{
    return m_status;
}

QString sql_query4::id_dia() const
{
    return m_id_dia;
}
void sql_query4::reload()
{
    sql_query4::checker();
}

void sql_query4::set_status(QString status)
{
    m_status = status;
}

void sql_query4::set_id_dia(QString id_dia)
{
    m_id_dia = id_dia;
}

void sql_query4::checker()
{
    Sleep(1000);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","db3");
    db.setHostName("95.143.216.174");
    db.setPort(3306);
    db.setDatabaseName("server");
    db.setUserName("server");
    db.setPassword("server");
    db.open();
    while(m_running ) {
        QSqlQuery query(QSqlDatabase::database("db3"));
        query.exec("SELECT * FROM msg WHERE id_dia='"+m_id_dia+"' ORDER BY id DESC");
        query.next();
        QSqlRecord rec = query.record();
        QString isReaded = query.value(rec.indexOf("isReaded")).toString();
        if (isReaded != m_status) {
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

#include "sql_query3.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlResult>
#include <QThread>
#include <QDebug>
#include "windows.h"
#include <QTime>

sql_query3::sql_query3(QObject *parent) : QObject(parent)
{

}

bool sql_query3::running() const
{
    return m_running;
}

void sql_query3::checker()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","db2");
    db.setHostName("95.143.216.174");
    db.setPort(3306);
    db.setDatabaseName("server");
    db.setUserName("server");
    db.setPassword("server");
    db.open();
    while (m_running) {
        QSqlQuery query(QSqlDatabase::database("db2"));
        QTime time;
        QDate date;
        time = time.currentTime();
        date = date.currentDate();
        query.prepare("INSERT INTO zaprosy (login, date, time) "
                  "VALUES (?, ?, ?)");
           query.addBindValue(nickname);
           query.addBindValue(date);
           query.addBindValue(time);
           query.exec();
           Sleep(60000);
    }
}

void sql_query3::recievenick(QString nick)
{
    std::string nickk = nick.toStdString();
    nickname = nickk.c_str();
}

void sql_query3::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(m_running);
}

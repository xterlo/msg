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
static QStringList msg_a;


sql_query1::sql_query1(QObject *parent) : QObject(parent)
{
}

bool sql_query1::running() const
{
    return m_running;
}

QString sql_query1::id_dia() const
{
    return m_id_dia;
}

QString sql_query1::nickname() const
{
    return m_nickname;
}

QStringList sql_query1::msg_array() const
{
    return m_msg_array;
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

    QStringList msg_array;

    QSqlQuery queryy(QSqlDatabase::database("db"));
    queryy.exec("SELECT * FROM dialogs WHERE client_1='"+m_nickname+"' OR client_2='"+m_nickname+"' ORDER BY id DESC");
    while (queryy.next()) {
            QSqlRecord rec = queryy.record();
            QString last_msg = queryy.value(rec.indexOf("last_msg")).toString();
            msg_array << last_msg;
    }
        while(m_running) {
        QSqlQuery query(QSqlDatabase::database("db"));
        query.exec("SELECT * FROM dialogs WHERE client_1='"+m_nickname+"' OR client_2='"+m_nickname+"' ORDER BY id DESC");
        query.next();
        QSqlRecord rec = query.record();
        QString id_dia = query.value(rec.indexOf("id")).toString();
        if ((m_id_dia != id_dia) or (m_msg_array != msg_array)) {
            emit update();
            msg_array << nullptr;
            msg_a << nullptr;
            break;
        }
        query.next();
        msg_array << nullptr;
        db.close();
        db.removeDatabase("db");
        reload();
        break;
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

void sql_query1::set_id_dia(QString id_dia)
{
    m_id_dia = id_dia;
}

void sql_query1::set_nickname(QString nickname)
{
    m_nickname = nickname;
}

void sql_query1::set_msg_array(QStringList msg_array)
{
    m_msg_array = msg_array;
}

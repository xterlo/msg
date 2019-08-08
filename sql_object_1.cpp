#include "sql_object_1.h"
#include <QDebug>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include "windows.h"
static QString id;
static QString nickname;

sql_object_1::sql_object_1(QObject *parent) : QObject(parent)
{

}

bool sql_object_1::running() const
{
    return m_running;
}

void sql_object_1::update()
{
    count = 0;
    while(m_running) {
        qDebug() << count++;
        m_running = false;
    }
    qDebug() << nickname;
    qDebug() << id;
}

void sql_object_1::restart()
{
    sql_object_1::update();
}

void sql_object_1::setRunning(bool running)
{
    if (m_running == running)
        return;
    m_running = running;
    emit runningChanged(m_running);
}

void sql_object_1::recieveData(QString Qid_dia)
{
    std::string id_dia = Qid_dia.toStdString();
    id = id_dia.c_str();
}

void sql_object_1::recievenick(QString Qnick)
{
    std::string nick = Qnick.toStdString();
    nickname = nick.c_str();
}

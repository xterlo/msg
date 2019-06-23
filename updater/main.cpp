#include "mainwindow.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QMessageBox>
#include <QSettings>
static QString login;
static QString beta_update;


int main(int argc, char *argv[])
{
    QApplication::addLibraryPath("bin/plugins");
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("95.143.216.174");
    db.setPort(3306);
    db.setDatabaseName("server");
    db.setUserName("server");
    db.setPassword("server");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    if(!db.open()) {
        QMessageBox::warning(0,"Ошибка!","Не удалось подключиться к серверу.\nКод ошибки: 0001");
    } else {
        QSettings settings("HKEY_CURRENT_USER\\Software\\IBM_PROFILES\\",QSettings::NativeFormat);
        foreach (QString key, settings.allKeys()) {
            if (settings.value(key) == "1" ) {
                login = key;
                QSqlQuery query;
                query.exec("SELECT * FROM beta_uses WHERE beta_active='1' AND user='"+login+"'");
                if (query.last() == true) {
                    QMessageBox::information(0,"Обновление не требуется","Установлена самая последняя бета версия");
                    w.close();
                } else {
                    query.exec("SELECT * FROM beta_version WHERE active='1' ORDER BY id DESC ");
                    QSqlRecord rec = query.record();
                    query.next();
                    QString version_  = query.value(rec.indexOf("version")).toString();
                    QSettings settings("HKEY_CURRENT_USER\\Software\\IBM_APP\\",QSettings::NativeFormat);
                    QString version = settings.value("version").toString();
                    if (query.last() == true) {
                    if (version != version_) {
                        system("taskkill /IM msg.exe /F");
                        QMessageBox::information(0,"бета обновление","бета обновление");
                        beta_update = 1;
                        //скачиваем beta msg.exe
                        w.close();
                    } else {
                        w.close();
                    }
                }
            }
            }
        }
        if (beta_update != 1) {
        QSqlQuery query;
        query.exec("SELECT * FROM version WHERE active='1' ORDER BY id DESC ");
        QSqlRecord rec = query.record();
        query.next();
        QString version_  = query.value(rec.indexOf("version")).toString();
        QSettings setting("HKEY_CURRENT_USER\\Software\\IBM_APP\\",QSettings::NativeFormat);
        QString version = setting.value("version").toString();
        if (version != version_) {
           system("taskkill /IM msg.exe /F");
           QMessageBox::information(0,"обычное обновление","обычное обновление");
           //скачиваем final msg.exe
           w.close();
         } else {
              w.close();
         }
    }
    }

    return a.exec();
}

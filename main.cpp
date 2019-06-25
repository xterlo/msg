#include "mainwindow.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QSettings>
static QString version = "1.0";
static int beta_user;


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
    }
    else {
        QSettings settings("HKEY_CURRENT_USER\\Software\\IBM_PROFILES\\",QSettings::NativeFormat);
        foreach (QString key, settings.allKeys()) {
           QSqlQuery query;
            if (settings.value(key) != "") {
                beta_user = 1;
                QSqlQuery query;
                query.exec("SELECT * FROM beta_uses WHERE user='"+key+"'");
                QSqlRecord rec = query.record();
                query.next();
                QString active_beta  = query.value(rec.indexOf("active_beta")).toString();
                if (active_beta == "0") {
                    beta_user = 0;
                } else {
                query.exec("SELECT * FROM beta_version WHERE active='1' ORDER BY id DESC ");
                QSqlRecord rec = query.record();
                query.next();
                QString version_  = query.value(rec.indexOf("version")).toString();
                if (query.last() == true) {
                if (version != version_) {
                QMessageBox msgBox;
                 msgBox.setText("Вышла бета версия программы.\nЖелаете обновиться?");
                 msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                 msgBox.setDefaultButton(QMessageBox::Yes);
                 int ret = msgBox.exec();
                 switch (ret) {
                    case QMessageBox::Yes:
                        QMessageBox::information(0,"OK","OK");
                        system("updater.exe");
                        w.close();
                        break;
                    case QMessageBox::No:
                        break;
                 }
            }
            }
               }
        }
        }
        if (beta_user != 1) {
        QSqlQuery query;
        query.exec("SELECT * FROM version WHERE version='"+version+"' AND active='0'");
        if (query.last() == true) {
           QMessageBox::warning(0,"Ошибка!","Необходимо обновить приложение!");
           w.close();
        } else {
        query.exec("SELECT * FROM version WHERE active='1' ORDER BY id DESC ");
        QSqlRecord rec = query.record();
        query.next();
        QString version_  = query.value(rec.indexOf("version")).toString();
        if (version != version_) {
            QMessageBox msgBox;
             msgBox.setText("Вышла новая версия программы.\nЖелаете обновиться?");
             msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
             msgBox.setDefaultButton(QMessageBox::Yes);
             int ret = msgBox.exec();
             switch (ret) {
                case QMessageBox::Yes:
                    QMessageBox::information(0,"OK","OK");
                    system("updater.exe");
                    w.close();
                    break;
                case QMessageBox::No:
                    break;
             }
        }
        }
    }
    QSettings setting("HKEY_CURRENT_USER\\Software\\IBM_APP\\",QSettings::NativeFormat);
    setting.setValue("version", version);

    return a.exec();
}
}

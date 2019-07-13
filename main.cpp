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
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
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
        Smtp* smtp;
        QString name = "Ошибка!";
        QString msg = "Не удалось подключиться к базе данных!";
        smtp = new Smtp("alfaland.online@gmail.com", "MyAlfamail", "smtp.gmail.com", 465);
        smtp->sendMail("alfaland.online@gmail.com", "chabandima2002@gmail.com" , name, msg);
        exit(0);
    }
    QSettings versionn("HKEY_CURRENT_USER\\Software\\IBM_APP\\",QSettings::NativeFormat);
    versionn.setValue("version", version);


    QSettings settings("HKEY_CURRENT_USER\\Software\\IBM_PROFILES\\",QSettings::NativeFormat);
    foreach (QString key, settings.allKeys()) {
        if (settings.value(key) == "1" ) {
            beta_user = 1;
            QString login = key;
            QSqlQuery query;
            query.exec("SELECT * FROM beta_uses WHERE user='"+login+"'");
            if (query.last() == false) {
                settings.setValue(login,"0");
                beta_user = 0;
            } else {
               query.exec("SELECT * FROM beta_uses WHERE active_beta='1' AND user='"+login+"'");
               if (query.last() == true) {
                   QSettings settings("HKEY_CURRENT_USER\\Software\\IBM_APP\\",QSettings::NativeFormat);
                   QString version = settings.value("version").toString();
                   query.exec("SELECT * FROM beta_version WHERE active='1' ORDER BY id DESC");
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
                               system("updater.exe");
                               exit(0);
                               break;
                           case QMessageBox::No:
                               break;
                        }
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
        system("updater.exe");
        exit(0);
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
                    system("updater.exe");
                    exit(0);
                    break;
                case QMessageBox::No:
                    break;
             }
        }
     }
  }
return a.exec();
}

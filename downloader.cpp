#include "downloader.h"
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QMessageBox>
#include <QSettings>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <windows.h>
#include <urlmon.h>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <direct.h>
#include <iomanip>
#include <iostream>
#include "smtp.h"

static QString login;
static QString beta_update;

using namespace std;

Downloader::Downloader(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);

}

void Downloader::getData()
{
        ShowWindow(GetConsoleWindow(), SW_HIDE);
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("95.143.216.174");
        db.setPort(3306);
        db.setDatabaseName("server");
        db.setUserName("server");
        db.setPassword("server");
        if(!db.open()) {
            QMessageBox::warning(0,"Ошибка!","Не удалось подключиться к серверу.\nКод ошибки: 0001");
            Smtp* smtp;
            QString name = "Ошибка!";
            QString msg = "Не удалось подключиться к базе данных!";
            smtp = new Smtp("alfaland.online@gmail.com", "MyAlfamail", "smtp.gmail.com", 465);
            smtp->sendMail("alfaland.online@gmail.com", "chabandima2002@gmail.com" , name, msg);
            exit(0);
        }
        QSettings settings("HKEY_CURRENT_USER\\Software\\IBM_PROFILES\\",QSettings::NativeFormat);
        foreach (QString key, settings.allKeys()) {
            if (settings.value(key) == "1" ) {
                beta_update = 1;
                QString login = key;
                QSqlQuery query;
                query.exec("SELECT * FROM beta_uses WHERE user='"+login+"' AND active_beta='1'");
                query.next();
                if (query.last() == true) {
                QSqlRecord rec = query.record();
                QUrl url(query.value(rec.indexOf("link")).toString());
                system("taskkill /F /IM msg.exe");
                QNetworkRequest request;
                request.setUrl(url);
                manager->get(request);
                } else {
                    QMessageBox::warning(nullptr,"Ошибка!","не разраб");
                    exit(0);
                }
            }
      }
      if (beta_update != 1) {
          QSqlQuery query;
          query.exec("SELECT * FROM version WHERE active='1' ORDER BY id DESC");
          QSqlRecord rec = query.record();
          query.next();
          QUrl url(query.value(rec.indexOf("link")).toString());
          system("taskkill /F /IM msg.exe");
          QNetworkRequest request;
          request.setUrl(url);
          manager->get(request);
      }
}

void Downloader::onResult(QNetworkReply *reply)
{
    if(reply->error()){
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    } else {
        char current_work_dir[FILENAME_MAX];
        _getcwd(current_work_dir, sizeof(current_work_dir));
        string filename = "/msg.exe";
        string fileout = current_work_dir + filename;
        string end = fileout;
        const char* path = end.c_str();

        QFile *file = new QFile(path);
        if(file->open(QFile::WriteOnly)){
            file->write(reply->readAll());
            file->close();
            QMessageBox::information(0,"Успешно!", "Обновление завершено!");
            exit(0);
        }
    }
}

